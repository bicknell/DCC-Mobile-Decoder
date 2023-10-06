/*
 * This code is subject to the
 * 
 * Creative Commons Attribution-NonCommercial 4.0 International Public License
 * 
 * Please see https://github.com/bicknell/DCC-Mobile-Decoder/LICENSE for full
 * license terms.
 *
 */

/* DESCRIPTION
 *
 * This file contains routines to decode the DCC bit-stream.
 * 
 * It assumes that:
 *     - The DCC input pin has been named IO_DCC in the pin manager.
 *     - TMR2 is used for the DCC signal, set to go off ~65us after the
 *       rising edge of the pulse.
 * 
 */

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "cv.h"
#include "dcc.h"
#include "debug.h"
#include "functions.h"
#include "motor.h"

/*
 * Local variables for the DCC subsystem.
 */
#if DEBUG_PERFORMANCE
static volatile uint32_t   idle_count            = 0;    // Idle cycle counter.
static volatile uint16_t   dcc_interrupts        = 0;    // Number of times DCC_ISR was called.
static volatile uint16_t   dcc_drops             = 0;    // Number of DCC messages dropped.
static volatile uint16_t   dcc_zeros             = 0;    // Number of DCC zeros received.
static volatile uint16_t   dcc_ones              = 0;    // Number of DCC ones received.
static volatile uint16_t   dcc_overrun           = 0;    // Number of DCC messages too long for our buffer.
#endif
// TODO: Move caching to cv.[ch]
static uint8_t             cv_cv29;                      // Memory copy of CV29 so we don't have to read EEPROM.
static uint8_t             cv_cv21;
static uint8_t             cv_cv22;
static uint8_t             dcc_good_packets      = 0;    // Incremented every time we get a good packet.
uint16_t                   dcc_address           = 0;    // Configured DCC address
char                       dcc_mesg[6]           = {0};  // DCC Messages can't be more than 6 bytes per S-9.2.1
uint8_t                    dcc_len               = 0;    // Length of the DCC message.
uint8_t                    dcc_speedsteps        = 0;    // DCC Packet Speed Steps
uint8_t                    dcc_speed             = 0;    // DCC Packet Speed

static uint8_t  dcc_speeds[] = {              // 28 Speed Step Table
    0,    // STOP
    0,    // ESTOP, since we don't do momentum yet can be the same.
    1,
    3,
    5,
    7,
    9,
    11,
    13,
    15,
    17,
    19,
    21,
    23,
    25,
    27,
    0,    // STOP
    0,    // ESTOP, since we don't do momentum yet can be the same.
    2,
    4,
    6,
    8,
    10,
    12,
    14,
    16,
    18,
    20,
    22,
    24,
    26,
    28
};


/*
 * DCC_ISR - The interrupt service routine to read DCC bits off the wire.
 * 
 * Assumptions:
 *     - TMR2 is configured to go off ~80us after the pin has gone high
 *       and call this ISR.
 * 
 * When the DCC input goes high, TMR2 is configured to start and run for
 * approximately 80us.  When it goes off it generates an interrupt and
 * calls this ISR.  The ISR then reads the DCC pin.  If it is still high
 * then it is a DCC zero.  If the pin is now low, it is a DCC one.  This 
 * bit-stream is collected into dcc_bits[] to form the bytes of the message.
 * 
 * The following variables would ordinarily be declared inside the ISR on
 * most platforms.  Due to the way the micro-processor works it is far more
 * efficient to make these "global" variables.  These variables should not
 * be used outside of this function.
 */
static char         dcc_bits[6] = {0};  // DCC Messages can't be more than 6 bytes per S-9.2.1
static uint8_t      dcc_byte    = 0;    // Current byte index into dcc_bits.
static uint8_t      dcc_bit     = 9;    // Current bit index into the byte. 9 = preamble, 8 = bit between bytes
static uint8_t      preamble    = 0;    // Number of preamble bits seen.
void DCC_ISR(void) {
#if DEBUG_PERFORMANCE
    ++dcc_interrupts;
#endif

    // The pin was HIGH, which is a DCC ZERO.
    if (IO_DCC_GetValue()) {
#if DEBUG_PERFORMANCE
        ++dcc_zeros;
#endif
        // Are we in the preamble?
        if (dcc_bit == 9) {
            // 10 or more 1's followed by a 0 means we can transition to the data state.
            if (preamble >= 10) {
                dcc_bit = 7; // Next bit will be the first data bit.
            } else {
                // 0 can't be in the preamble, and if we're not to 10 yet, reset and look again.
                goto reset;
            }
        // Not in preamble, must be data
        } else {
            // Array starts as all 0's so nothing to record.
            // If bit > 0, decrement to the next bit.
            if (dcc_bit) {
                --dcc_bit;
            // If we were at bit 0, increment to the next byte and look for
            // the bit between bytes by setting dcc_bit = 8.
            } else {
                ++dcc_byte;
                dcc_bit = 8;
            }
        }

    // The pin was LOW, which is a DCC ONE.
    } else {
#if DEBUG_PERFORMANCE
        ++dcc_ones;
#endif
        // Are we in the pre-amble?
        if (dcc_bit == 9) {
            // Count bits.
            ++preamble;

        // Not in the pre-amble, recording data.
        } else {
            // 1 between bytes is End of Message
            if (dcc_bit == 8) {
                // See if our message buffer is available.
                if (!dcc_ready) {
                    dcc_mesg[0] = dcc_bits[0];
                    dcc_mesg[1] = dcc_bits[1];
                    dcc_mesg[2] = dcc_bits[2];
                    dcc_mesg[3] = dcc_bits[3];
                    dcc_mesg[4] = dcc_bits[4];
                    dcc_mesg[5] = dcc_bits[5];
                    dcc_len     = dcc_byte;
                    dcc_ready   = 1; // Tell main() to consume the message.
                } else {
                    // Last message hasn't been consumed yet, so this one gets thrown away.
#if DEBUG_PERFORMANCE
                    ++dcc_drops;
#endif
                }
                goto reset;
            // Record the 1
            } else {
                // Array bounds is 0-5, if we get a 1 at 6 we have over-run.
                // Note there are DCC messages longer, but we do not decode
                // them, treating as over-run is ok.
                if (dcc_byte == 6) {
#if DEBUG_PERFORMANCE
                    ++dcc_overrun;
#endif
                    goto reset;
                }
                // Store the 1
                dcc_bits[dcc_byte] |= 1 << dcc_bit;
                // If bit > 0, decrement to the next bit.
                if (dcc_bit) {
                    --dcc_bit;
                // If we were at bit 0, increment to the next byte and look for
                // the bit between bytes by setting dcc_bit = 8.
                } else {
                    ++dcc_byte;
                    dcc_bit = 8;
                }
            }
        }
    }
    
    // We want to call TMR2_StartTimer() here, but that makes the compiler
    // complain about calling a non-reentrant function.
    T2CONbits.TMR2ON = 1;
    return;

reset:
    dcc_bits[0] = 0;
    dcc_bits[1] = 0;
    dcc_bits[2] = 0;
    dcc_bits[3] = 0;
    dcc_bits[4] = 0;
    dcc_bits[5] = 0;
    dcc_byte    = 0;
    dcc_bit     = 9;    // 9 == in preamble
    preamble    = 0;
    
    // We want to call TMR2_StartTimer() here, but that makes the compiler
    // complain about calling a non-reentrant function.
    T2CONbits.TMR2ON = 1;
}

/*
 * dcc_initialize - Called at startup to initialize our DCC information.
 */
void dcc_initialize(void) {
    cv_cv21 = cv_read(CV_CONSIST_ACTIVE_F1_F8);
    cv_cv22 = cv_read(CV_CONSIST_ACTIVE_FL_F9_F12);
    cv_cv29 = cv_read(CV_CONFIGURATION_DATA);
    
    // Extended address?
    if (cv_cv29 & 0x20) {
        dcc_address = ((uint16_t)cv_read(CV_EXTENDED_ADDRESS_HIGH) << 8) | (uint16_t)cv_read(CV_EXTENDED_ADDRESS_LOW);
    } else {
        dcc_address = cv_read(CV_PRIMARY_ADDRESS);
    }
    dcc_ndot = cv_cv29 & 0x01;   
    dcc_consist = cv_read(CV_CONSIST_ADDRESS) & 0x7F;
    dcc_consist_ndot = (cv_read(CV_CONSIST_ADDRESS) & 0x80) >> 7;
}

/*
 * dcc_decode - Called when there is a DCC message from the ISR.
 *
 * Global Variable Inputs:
 *     dcc_mesg[]
 *     dcc_len
 * 
 * Global Variable Outputs:
 *     dcc_functions
 *     dcc_speed_steps
 *     dcc_speed
 *     dcc_direction
 *
 * The following variables would ordinarily be declared inside the function on
 * most platforms.  Due to the way the micro-processor works it is far more
 * efficient to make these "global" variables.  These variables should not
 * be used outside of this function.
 */
static uint16_t pkt_addr;                // DCC address in the packet.
static uint8_t  xor = 0;                 // Stores the xor value.
static uint8_t  i;                       // Loop index counter.
static uint8_t  address_bits;            // How many address bits in the message.
static uint8_t  i_start;                 // Index where instructions start.
static uint16_t cv_address;              // Configuration variable address.
static uint8_t  cv_value;                // Configuration variable value.
static uint8_t  cv_bit;                  // Configuration variable bit position.
static uint8_t  dcc_reset_received = 0;  // Previous packet was DCC Reset, used for entering Service Mode
static uint8_t  dcc_service_mode = 0;    // Are we in service mode?
static uint8_t  dcc_page = 1;            // Page Register, for service mode

void dcc_decode(void) {
    
    // Compute checksum.
    xor = 0;
    for (i = 0; i < dcc_len; ++i) {
        xor ^= dcc_mesg[i];
    }
#if DEBUG_DCC_PACKET
    // Do not print newline if passing, so decode is on the same line.
    printf("Rec %02x %02x %02x %02x %02x %02x (%d) %s",
            dcc_mesg[0], dcc_mesg[1], dcc_mesg[2],
            dcc_mesg[3], dcc_mesg[4], dcc_mesg[5],
            dcc_len, xor ? "FAIL\r\n" : "PASS: ");
#endif
    // If checksum failed nothing to parse.
    if (xor) {
        return;
    }
    // Used to determine if we're getting valid DCC or not.
    ++dcc_good_packets;

    // Broadcast packets are all address 0.
    if (dcc_mesg[0] == 0x00) {
        // Special case, Broadcast Decoder Reset packet. 
        if ((dcc_mesg[1] == 0x00) && (dcc_len == 3)) {
#if DEBUG_DCC_DECODE_BASELINE    
        printf("Baseline: Broadcast decoder reset!\r\n");
#endif
        dcc_speed = 0;
        dcc_speedsteps = 128;
        dcc_direction = DCC_FORWARD;
        motor_control(dcc_speedsteps, dcc_speed, dcc_direction);
        dcc_reset_received = 1;
        // Special case, Broadcast Stop Packet
        } else if (((dcc_mesg[1] & 0xC1) == 0xC1) && (dcc_len == 3)) {
            dcc_speed = 0;
            motor_control(dcc_speedsteps, dcc_speed, dcc_direction);
#if DEBUG_DCC_DECODE_BASELINE    
            printf("Baseline: Broadcast Stop.\r\n");
#endif
        }
        return;
    }
    // Special case, Baseline Idle packet
    if ((dcc_mesg[0] == 0xFF) && (dcc_mesg[1] == 0x00) && (dcc_len == 3)) {
#if DEBUG_DCC_DECODE_NOT_FOR_US
        printf("Baseline: Not us, Idle Packet.\r\n");
#endif
        return;
    // Baseline speed/direction packet
    // Note there are 2-byte extended packets, critical to check the high bit of
    // byte 0 is 0, and the top two bits of byte 1 is 01 to validate it is a baseline
    // packet.
    } else if (((dcc_mesg[0] & 0x80) == 0x00) && ((dcc_mesg[1] & 0xC0) == 0x40) && (dcc_len == 3)) {
        // Decode the pkt_addr
        pkt_addr = dcc_mesg[0] & 0x7F;

        // Do we have a 7 bit pkt_addr configured that matches?
        if ((dcc_consist == pkt_addr) || ((dcc_consist == 0) && (dcc_address == pkt_addr))) {
            dcc_direction = dcc_mesg[1] & 0x20 ? DCC_FORWARD : 'B';
            // 28/128 speed step mode enabled
            if (cv_cv29 & 02) {
                dcc_speedsteps = 28;
                dcc_speed = dcc_speeds[dcc_mesg[1] & 0x1F];
                // 14 speed step mode enabled
            } else {
                dcc_speedsteps = 14;
                dcc_speed = dcc_speeds[dcc_mesg[1] & 0x0F];
                dcc_functions[0] = (dcc_mesg[1] & 0x10) >> 4;
            }
            motor_control(dcc_speedsteps, dcc_speed, dcc_direction);
#if DEBUG_DCC_DECODE_BASELINE
            printf("Baseline: B/%d %d is %c@%d\r\n", dcc_speedsteps, pkt_addr, dcc_direction, dcc_speed);
#endif
        } else {
#if DEBUG_DCC_DECODE_NOT_FOR_US
            printf("Baseline: Not us, for %d\r\n", pkt_addr);
#endif
        }
        return;
    // Must be an S-9.2.1 Extended Packet
    } else {
        // Multi-Function Decoders with 14 bit addresses.
        if ((dcc_mesg[0] & 0xC0) == 0xC0) {  
            pkt_addr = (uint16_t) dcc_mesg[1] | (((uint16_t) dcc_mesg[0] & 0x3F) << 8);
            address_bits = 14;
            i_start = 2;
        // Basic Accessory Decoders with 9 bit addresses and Extended Accessory
        // decoders with 11 bit addresses.
        } else if ((dcc_mesg[0] & 0xC0) == 0x80) {
            pkt_addr = (uint16_t) dcc_mesg[1] | (((uint16_t) dcc_mesg[0] & 0x3F) << 8);
//TODO: 11 bit?
            address_bits = 9;
            i_start = 2;
        // Multi-Function decoders with 7 bit addresses.
        } else if ((dcc_mesg[0] & 0xC0) == 0x00) {
            pkt_addr = (uint16_t) dcc_mesg[0];
            address_bits = 7;
            i_start = 1;
        // Idle Packet
        } else if (dcc_mesg[0] == 0xFF) {
#if DEBUG_DCC_NOT_FOR_US
            printf("Extended: Not for us, Idle Packet.");
#endif
            return;
        }

        // S-9.2.3 Service Mode Section C
        if (dcc_reset_received && ((dcc_mesg[0] & 0x70) == 0x70)) {
            dcc_service_mode = 1;
        } else {
            // Clear it, as we have some other sort of packet now.
            dcc_reset_received = 0;
        }

        // S-9.2.3 Service Mode Section E
        if (dcc_service_mode) {
            // 3 Byte + 0111C000 + Zero High Bit = Address Mode
            if ((dcc_len == 3) && ((dcc_mesg[0] & 0x77) == 0x70) && ((dcc_mesg[1] & 0x80) == 0x00)) {
                // C = 1 Write Address
                if (dcc_mesg[0] & 0x80) {
                    cv_write(CV_CONSIST_ADDRESS, 0);
                    cv_write(CV_PRIMARY_ADDRESS, (uint8_t)dcc_mesg[1]);
                    cv_write(CV_CONFIGURATION_DATA, cv_read(CV_CONFIGURATION_DATA) & ~0x20);
#if DEBUG_DCC_DECODE_SERVICE
                    printf("Address mode write to CV1=%d, consisting off, short address.\r\n", (uint8_t)dcc_mesg[1]);
#endif
                // C = 0 Read Address
                } else {
#if DEBUG_DCC_DECODE_SERVICE
                    printf("Address mode read from CV1=%d; actual %d.\r\n", (uint8_t)dcc_mesg[1], cv_read(CV_PRIMARY_ADDRESS));
#endif
//TODO, read back address.
                }
            // 3 Bytes + 0111CRRR = Page/Register Mode
            } else if ((dcc_len == 3) && ((dcc_mesg[0] & 0x70) == 0x70)) {
                // Page mode is an extension of register mode.  When dcc_page = 1
                // it is a register mode operation using the original 8 values.
                // When dcc_page is set > 1, then the bottom 4 values are indexed
                // by the page number.  This is a clever scheme as the first 
                // 4 registers on page 1 are the same in both, so we can basically
                // just write the code to handle Page mode and it does both.
                switch (dcc_mesg[0] & 0x07) {
                    case 0x00:
                    case 0x01:
                    case 0x02:
                    case 0x03:
                        cv_address = ((dcc_page - 1) * 4) + (dcc_mesg[0] & 0x03) + 1;
                        break;
                    case 0x04: cv_address = 29; break;
                    case 0x05: dcc_page = dcc_mesg[1];
#if DEBUG_DCC_DECODE_SERVICE
                        printf("Setting page regsiter to %d.\r\n", dcc_page);
#endif
                        return;
                        break;
                    case 0x06: cv_address = 7;  break;
                    case 0x07: cv_address = 8;  break;
                }

                // Page/Register Write
                if (dcc_mesg[0] & 0x08) {
#if DEBUG_DCC_DECODE_SERVICE
                    printf("%s Mode Write CV%d=%d (page=%d)\r\n", (dcc_page > 1) ? "Paged" : "Register", cv_address, dcc_mesg[1], dcc_page);
#endif
                    cv_write(cv_address, dcc_mesg[1]);
                // Page / Register Read
                } else {
#if DEBUG_DCC_DECODE_SERVICE
                    printf("%s Mode Read CV%d=%d (page=%d)\r\n", (dcc_page > 1) ? "Paged" : "Register", cv_address, dcc_mesg[1], dcc_page);
#endif
                    if (cv_read(cv_address) == dcc_mesg[1]) {
//TODO: Read it back
                    }
                }
            // 4 Byte + 0111CCAA = Direct Mode
            } else if ((dcc_len == 4) && ((dcc_mesg[0] & 0x70) == 0x70)) {
                cv_address = ((uint16_t) (dcc_mesg[0] & 0x03) << 8) | (uint16_t) dcc_mesg[1];
                ++cv_address; // "The Configuration variable being addressed is the provided 10-bit address plus 1"

                // Write byte
                if ((dcc_mesg[0] & 0x0C) == 0x0C) {
                    cv_write(cv_address, dcc_mesg[2]);
#if DEBUG_DCC_DECODE_SERVICE
                    printf("Direct Mode Write CV%d=%d\r\n", cv_address, dcc_mesg[2]);
#endif
                // Verify Byte
                } else if ((dcc_mesg[0] & 0x0C) == 0x04) {
                    if (cv_read(cv_address) == dcc_mesg[2]) {
//TODO: Read it back
                    }
#if DEBUG_DCC_DECODE_SERVICE
                    printf("Direct Mode Verify CV%d=%d; actual %d\r\n", cv_address, dcc_mesg[2], cv_read(cv_address));
#endif
                // Bit Manipulation
                } else if ((dcc_mesg[0] & 0x0C) == 0x08) {
                    cv_value = (dcc_mesg[2] & 0x08) >> 3;
                    cv_bit = dcc_mesg[2] & 0x07;

                    // Write bit
                    if (dcc_mesg[2] & 0xF0) {
                        // Set bit
                        if (cv_value) {
                            cv_write(cv_address, cv_read(cv_address) | (uint8_t) (1 << cv_bit));
                        // Clear bit
                        } else {
                            cv_write(cv_address, cv_read(cv_address) & (~(1 << cv_bit)));
                        }
                        // This may have changed our address, CV29, etc, reinitialize.
                        dcc_initialize();
#if DEBUG_DCC_DECODE_SERVICE
                                printf("Direct Mode Write Bit CV=%ld, bit=%d, value=%d", cv_address, cv_bit, cv_value);
#endif
                    // Verify bit
                    } else {
#if DEBUG_DCC_DECODE_SERVICE
                        printf("Direct Mode Verify Bit CV=%ld, bit=%d, value=%d, is=%d",
                                cv_address, cv_bit, cv_value, 
                                (cv_read(cv_address) & (1 << cv_bit)) >> cv_bit);
#endif
//TODO read it back to the command station!
                    }
                }
            } else {
#if DEBUG_DCC_DECODE_SERVICE
                printf("Unknown service mode packet.\r\n");
#endif
            }
            // We've fully processed service mode, time to leave.
            return;
        }

        // Does the address match our consist address, our regular address or the broadcast address?
        if ((dcc_consist == pkt_addr) || (dcc_address == pkt_addr) || (pkt_addr == 0x00)) {
#if DEBUG_DCC_DECODE_EXTENDED    
            printf("Extended: ");
#endif 
            // Loop through the instructions starting at i_start.
            // Do not process the checksum byte at the end.
            for (uint8_t i = i_start;i < (dcc_len - 1);++i) {
#if DEBUG_DCC_DECODE_EXTENDED
                // Second (third, fourth), instruction in the packet.
                if (i != i_start) {
                    printf("; (i=%d)", i);
                }
#endif
                // The most common packet is a speed/direction packet, so we
                // place it first as an optimization.
                // S-9.2.1 2.3.2 CCC=001 Advanced Operations Instructions 2-BYTE
                if ((dcc_mesg[i] & 0xE0) == 0x20) {
                    // S-9.2.1 2.3.2.1 GGGGG==11111 128 speed step
                    if ((dcc_mesg[i] & 0x1F) == 0x1F) {
                        // When consisted, we only respond to speed/direction to the consist address.
                        if ((dcc_consist == pkt_addr) || ((dcc_consist == 0) && (dcc_address == pkt_addr))) {
                            dcc_direction = dcc_mesg[i + 1] & 0x80 ? DCC_FORWARD : DCC_REVERSE;
                            dcc_speedsteps = 128;
                            // 0 == STOP, 1 == ESTOP in 128ss mode, otherwise speed
                            dcc_speed = (uint8_t) dcc_mesg[i + 1] & 0x7F;
                            motor_control(dcc_speedsteps, dcc_speed, dcc_direction);
#if DEBUG_DCC_DECODE_SPEED
                            // This really should be DEBUG_DCC_DECODE_ADV_OPS, but practically,
                            // it makes more sense to group with DEBUG_DCC_DECODE_SPEED.
                            printf("E128/%d(%d) %d is %c@%d", address_bits, i, pkt_addr,
                                   dcc_direction, dcc_speed);
#endif
                        } else {
#if DEBUG_DCC_DECODE_NOT_FOR_US
                            printf("Ignoring E128 message for %d, consisted", dcc_address);
#endif
                        }
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.2.2 GGGGG=11101 Zimo East-West Direction Proposal
                    } else if ((dcc_mesg[i] & 0x1F) == 0x1E) {
#if DEBUG_DCC_DECODE_ADV_OPS
                        printf("Reserved for Zimo East-West CCC=001 Advanced Operation");
#endif                
// TODO: How do we know if 2 or 3 byte for the reserved?
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.2.3 GGGGG=11101 Analog Function group
                    } else if ((dcc_mesg[i] & 0x1F) == 0x1D) {
#if DEBUG_DCC_DECODE_ADV_OPS
                        printf("Advanced Operations Analog (%02x, %02x)", dcc_mesg[i+1], dcc_mesg[i+2]);
#endif
                        // Digitrax uses this for F2 variable volume.
                        i+=2; // Increment again, as it was a 3-BYTE instruction
                    // S-9.2.1 2.3.2.4 Reserved for future use.
                    } else {
#if DEBUG_DCC_DECODE_ADV_OPS
                        printf("Reserved for future use CCC=001 Advanced Operation");
#endif                
// TODO: How do we know if 2 or 3 byte for the reserved?
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    }
                // Second most common packet is a FG1 packet, so we place it second
                // as an optimization.
                // S-9.2.1 2.3.4 CCC=100 Function Group One Instruction
                } else if ((dcc_mesg[i] & 0xE0) == 0x80) {
                    // When consisted, we have to look if we should respond or not.
                    if (dcc_consist) {
                        if (dcc_consist == pkt_addr) {
                            if (dcc_direction) {
                                if (cv_cv22 & 0x02) { dcc_functions[0] = (dcc_mesg[i] & 0x10) >> 4; }
                            }else {
                                if (cv_cv22 & 0x01) { dcc_functions[0] = (dcc_mesg[i] & 0x10) >> 4; }
                            }
                            if (cv_cv21 & 0x01) { dcc_functions[1] = (dcc_mesg[i] & 0x01); }
                            if (cv_cv21 & 0x02) { dcc_functions[2] = (dcc_mesg[i] & 0x02) >> 1; }
                            if (cv_cv21 & 0x04) { dcc_functions[3] = (dcc_mesg[i] & 0x04) >> 2; }
                            if (cv_cv21 & 0x08) { dcc_functions[4] = (dcc_mesg[i] & 0x08) >> 3; }
                        } else if (dcc_address == pkt_addr) {
                            if (dcc_direction) {
                                if (!(cv_cv22 & 0x02)) { dcc_functions[0] = (dcc_mesg[i] & 0x10) >> 4; }
                            } else {
                                if (!(cv_cv22 & 0x01)) { dcc_functions[0] = (dcc_mesg[i] & 0x10) >> 4; }
                            }

                            if (!(cv_cv21 & 0x01)) { dcc_functions[1] = (dcc_mesg[i] & 0x01); }
                            if (!(cv_cv21 & 0x02)) { dcc_functions[2] = (dcc_mesg[i] & 0x02) >> 1; }
                            if (!(cv_cv21 & 0x04)) { dcc_functions[3] = (dcc_mesg[i] & 0x04) >> 2; }
                            if (!(cv_cv21 & 0x08)) { dcc_functions[4] = (dcc_mesg[i] & 0x08) >> 3; }                            
                        }
                    // Handle normally.
                    } else {
                        dcc_functions[0] = (dcc_mesg[i] & 0x10) >> 4;
                        dcc_functions[1] = (dcc_mesg[i] & 0x01);
                        dcc_functions[2] = (dcc_mesg[i] & 0x02) >> 1;
                        dcc_functions[3] = (dcc_mesg[i] & 0x04) >> 2;
                        dcc_functions[4] = (dcc_mesg[i] & 0x08) >> 3;
                    }
#if DEBUG_DCC_DECODE_E_FN
                    printf("EFG1/%d(%d) %d is %d%d%d%d%d (0-4)", address_bits, i, pkt_addr, 
                            dcc_functions[0], dcc_functions[1], dcc_functions[2], 
                            dcc_functions[3], dcc_functions[4]);
#endif
                // Third most common packet is a FG2 packet, so we place it third
                // as an optimization.
                // S-9.2.1 2.3.5 CCC=101 Function Group Two Instruction
                } else if ((dcc_mesg[i] & 0xE0) == 0xA0) {
                    if ((dcc_mesg[i] & 0x10) == 0x10) {
                        if (dcc_consist) {
                            if (dcc_consist == pkt_addr) {
                                if (cv_cv21 & 0x10) { dcc_functions[5] = (dcc_mesg[i] & 0x01); }
                                if (cv_cv21 & 0x20) { dcc_functions[6] = (dcc_mesg[i] & 0x02) >> 1; }
                                if (cv_cv21 & 0x40) { dcc_functions[7] = (dcc_mesg[i] & 0x04) >> 2; }
                                if (cv_cv21 & 0x80) { dcc_functions[8] = (dcc_mesg[i] & 0x08) >> 3; }
                            } else if (dcc_address == pkt_addr) {
                                if (!(cv_cv21 & 0x10)) { dcc_functions[5] = (dcc_mesg[i] & 0x01); }
                                if (!(cv_cv21 & 0x20)) { dcc_functions[6] = (dcc_mesg[i] & 0x02) >> 1; }
                                if (!(cv_cv21 & 0x40)) { dcc_functions[7] = (dcc_mesg[i] & 0x04) >> 2; }
                                if (!(cv_cv21 & 0x80)) { dcc_functions[8] = (dcc_mesg[i] & 0x08) >> 3; }                            
                            }
                        // Handle normally.
                        } else {
                            dcc_functions[5]  = (dcc_mesg[i] & 0x01);
                            dcc_functions[6]  = (dcc_mesg[i] & 0x02) >> 1;
                            dcc_functions[7]  = (dcc_mesg[i] & 0x04) >> 2;
                            dcc_functions[8]  = (dcc_mesg[i] & 0x08) >> 3;
                        }
#if DEBUG_DCC_DECODE_E_FN
                        printf("EFG2/%d(%d) %d is %d%d%d%d (5-8)", address_bits, i, pkt_addr, 
                                dcc_functions[5], dcc_functions[6],
                                dcc_functions[7], dcc_functions[8]);
#endif
                    } else {
                        if (dcc_consist) {
                            if (dcc_consist == pkt_addr) {
                                if (cv_cv21 & 0x10) { dcc_functions[9] = (dcc_mesg[i] & 0x01); }
                                if (cv_cv21 & 0x20) { dcc_functions[10] = (dcc_mesg[i] & 0x02) >> 1; }
                                if (cv_cv21 & 0x40) { dcc_functions[11] = (dcc_mesg[i] & 0x04) >> 2; }
                                if (cv_cv21 & 0x80) { dcc_functions[12] = (dcc_mesg[i] & 0x08) >> 3; }
                            } else if (dcc_address == pkt_addr) {
                                if (!(cv_cv21 & 0x10)) { dcc_functions[9] = (dcc_mesg[i] & 0x01); }
                                if (!(cv_cv21 & 0x20)) { dcc_functions[10] = (dcc_mesg[i] & 0x02) >> 1; }
                                if (!(cv_cv21 & 0x40)) { dcc_functions[11] = (dcc_mesg[i] & 0x04) >> 2; }
                                if (!(cv_cv21 & 0x80)) { dcc_functions[12] = (dcc_mesg[i] & 0x08) >> 3; }                            
                            }
                        // Handle normally.
                        } else {
                            dcc_functions[9]  = (dcc_mesg[i] & 0x01);
                            dcc_functions[10] = (dcc_mesg[i] & 0x02) >> 1;
                            dcc_functions[11] = (dcc_mesg[i] & 0x04) >> 2;
                            dcc_functions[12] = (dcc_mesg[i] & 0x08) >> 3;
                        }
#if DEBUG_DCC_DECODE_E_FN
                        printf("EFG2/%d(%d) %d is %d%d%d%d (9-12)", address_bits, i, pkt_addr,
                                dcc_functions[9], dcc_functions[10], 
                                dcc_functions[11], dcc_functions[12]);
#endif
                    }
              
                // S-9.2.1 2.3.1 CCC=000 Decoder and Consist Control Instruction
                } else if ((dcc_mesg[i] & 0xE0) == 0x00) {
#if DEBUG_DCC_DECODE_DECODER
                                printf("Decoder control");
#endif
                    // Only if sent to the base address.
                    if (dcc_address == pkt_addr) {
                        // S-9.2.1 2.3.1.4 CCCG=0001 Consist Control 2-BYTE Message
                        if (dcc_mesg[i] & 0x10) {
                            // TTTT=0010 Set the consist address, normal direction.
                            if ((dcc_mesg[i] & 0x0F) == 0x02) {
                                cv_write(CV_CONSIST_ADDRESS, dcc_mesg[i + 1]);
                                dcc_consist_ndot = DCC_FORWARD;
#if DEBUG_DCC_DECODE_DECODER
                                printf("Set consist dir=f address=%d", dcc_mesg[i + 1]);
#endif
                                //TODO Address is in dcc_mesg[i+1], 0x00 deactivates
                                // TTTT=0011 Set the consist address, reverse direction.
                            } else if ((dcc_mesg[i] & 0x0F) == 0x03) {
                                cv_write(CV_CONSIST_ADDRESS, dcc_mesg[i + 1] & 0x80);
                                dcc_consist_ndot = DCC_REVERSE;
#if DEBUG_DCC_DECODE_DECODER
                                printf("Set consist dir=r address=%d", dcc_mesg[i + 1]);
#endif
                            }
                            dcc_consist = (uint16_t) dcc_mesg[i + 1];
                        // S-9.2.1 2.3.1.1 CCCG=0000 Decoder Control
                        } else {
                            // TTT=000 Digital Decoder Reset
                            if ((dcc_mesg[i] & 0xE) == 0x00) {
                                // F=1 Hard Reset
                                if (dcc_mesg[i] & 0x1) {
                                    // Reset volatile memory.
                                    dcc_speed = 0;
                                    dcc_direction = 0;
                                    dcc_speedsteps = 128;
                                    cv_write(CV_CONSIST_ADDRESS, 0);       // CV19 -> 0
                                    cv_write(CV_CONFIGURATION_DATA, 0x02); // Factory Default Value
                                    cv_write(CV_INDEX_HIGH_BYTE, 0);       // Factory Default Value
                                    cv_write(CV_INDEX_LOW_BYTE, 0);        // Factory Default Value
                                    // Reinitialize the dcc subsystem.
                                    dcc_initialize();
#if DEBUG_DCC_DECODE_DECODER
                                    printf("Hard Reset requested");
#endif     
                                    // F=0 Regular Reset
                                } else {
                                    // Reset volatile memory.
                                    dcc_speed = 0;
                                    dcc_direction = 0;
                                    dcc_speedsteps = 128;
                                    // Reinitialize the dcc subsystem.
                                    dcc_initialize();
#if DEBUG_DCC_DECODE_DECODER
                                    printf("Reset requested");
#endif     
                                }
                                // TTT=001 Factory Test Instruction
                            } else if ((dcc_mesg[i] & 0xE) == 0x01) {
                                //TODO - Implement some test suite?
#if DEBUG_DCC_DECODE_DECODER
                                printf("Factory test requested");
#endif     
                                // S-9.2.1 2.3.1.2 TTT=101 Set Advanced Addressing
                            } else if ((dcc_mesg[i] & 0xE) == 0x06) {
                                // F=1 Long Address in CV17&CV18
                                if (dcc_mesg[i] & 0x01) {
                                    cv_write(CV_CONFIGURATION_DATA, cv_read(CV_CONFIGURATION_DATA) | 0x20);
                                    cv_cv29 = cv_read(CV_CONFIGURATION_DATA);
#if DEBUG_DCC_DECODE_DECODER
                                    printf("Set Advanced Addressing, use CV17/CV18 long address");
#endif     
                                    // F=0 Short Address in CV1
                                } else {
                                    cv_write(CV_CONFIGURATION_DATA, cv_read(CV_CONFIGURATION_DATA) & ~0x20);
                                    cv_cv29 = cv_read(CV_CONFIGURATION_DATA);
#if DEBUG_DCC_DECODE_DECODER
                                    printf("Set Advanced Addressing, use CV1 short address");
#endif     
                                }
                                // S-9.2.1 2.3.1.2 TTT=111 Decoder Acknowledgement Request
                            } else if ((dcc_mesg[i] & 0xE) == 0x0E) {
//TODO
                            }
                        }
                    }
                    ++i; // Increment again, as it was a 2-BYTE instruction
                // S-9.2.1 2.3.3 CCC=010 Speed and Direction Instructions
                } else if ((dcc_mesg[i] & 0xE0) == 0x40) {
                    // When consisted, we only respond to speed/direction to the consist address.
                    if ((dcc_consist == pkt_addr) || ((dcc_consist == 0) && (dcc_address == pkt_addr))) {
                        // 28 speed step reverse
                        dcc_direction = DCC_REVERSE;
                        dcc_speedsteps = 28;
                        dcc_speed = dcc_speeds[dcc_mesg[i] & 0x1F];
                        motor_control(dcc_speedsteps, dcc_speed, dcc_direction);
#if DEBUG_DCC_DECODE_SPEED
                        printf("E28/%d(%d) %d is %c@%d", address_bits, i, pkt_addr, dcc_direction, dcc_speed);
#endif
                    } else {
#if DEBUG_DCC_DECODE_NOT_FOR_US
                        printf("Ignoring E28 message for %d, consisted", dcc_address);
#endif
                    }                    
                // S-9.2.1 2.3.3 CCC=011 Speed and Direction Instructions
                } else if ((dcc_mesg[i] & 0xE0) == 0x60) {
                    // When consisted, we only respond to speed/direction to the consist address.
                    if ((dcc_consist == pkt_addr) || ((dcc_consist == 0) && (dcc_address == pkt_addr))) {

                        // 28 speed step forward
                        dcc_direction = DCC_FORWARD;
                        dcc_speedsteps = 28;
                        dcc_speed = dcc_speeds[dcc_mesg[i] & 0x1F];
                        motor_control(dcc_speedsteps, dcc_speed, dcc_direction);
#if DEBUG_DCC_DECODE_SPEED
                        printf("E28%d(%d) %d is %c@%s", address_bits, i, pkt_addr, dcc_direction, dcc_speed);
#endif
                    } else {
#if DEBUG_DCC_DECODE_NOT_FOR_US
                        printf("Ignoring E28 message for %d, consisted", dcc_address);
#endif
                    }                                      
                // S-9.2.1 2.3.6 CCC=110 Feature Expansion Instruction See TN-3-05
                } else if ((dcc_mesg[i] & 0xE0) == 0xC0) {
//TODO Consist Handling?
#if DEBUG_DCC_DECODE_FEATURE
                                printf("Feature expansion");
#endif
                    // S-9.2.1 2.3.6.1 GGGGG=00000 Binary State Control Instruction Long Form 3-BYTE instruction
                    if ((dcc_mesg[i] & 0x1F) == 0x00) {
#if DEBUG_DCC_DECODE_FEATURE
                        printf("Binary State Control Instruction Long Form, ignored");
#endif
                        i+=2; // Increment again, as it was a 3-BYTE instruction
                    // S-9.2.1 2.3.6.2 GGGGG=00001 Time and Date Command
                    } else if ((dcc_mesg[i] & 0x1F) == 0x01) {
#if DEBUG_DCC_DECODE_FEATURE
                        printf("Time and Date Command, ignored");
#endif
                        i+=3; // Increment again, as it was a 4-BYTE instruction
                    // S-9.2.1 2.3.6.3 GGGGG=00010 System time
                    } else if ((dcc_mesg[i] & 0x1F) == 0x02) {
#if DEBUG_DCC_DECODE_FEATURE
                        printf("System time, ignored");
#endif
                        i+=2; // Increment again, as it was a 3-BYTE instruction
                    // S-9.2.1 2.3.6.4 GGGGG=11101 Binary State Control Instruction Short Form
                    } else if ((dcc_mesg[i] & 0x1F) == 0x1D) {
#if DEBUG_DCC_DECODE_FEATURE
                        printf("Binary State Control Instruction Short Form, ignored");
#endif
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.6.5 GGGGG=11110 F13-F20 Function Control
                    } else if ((dcc_mesg[i] & 0x1F) == 0x1E) {
#if FUNCTION_MAX > 14
                        // TODO: Handle higher functions.
#else
#if DEBUG_DCC_DECODE_FEATURE
                        printf("F13-F20, ignored");
#endif
#endif
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.6.6 GGGGG=11111 F21-F28 Function Control
                    } else if ((dcc_mesg[i] & 0x1F) == 0x1F) {
#if FUNCTION_MAX > 22
                        // TODO: Handle higher functions.
#else
#if DEBUG_DCC_DECODE_FEATURE
                        printf("F21-F28, ignored");
#endif
#endif
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.6.7 GGGGG=11000 F29-F36 Function Control
                    } else if ((dcc_mesg[i] & 0x1F) == 0x18) {
#if FUNCTION_MAX > 30
                        // TODO: Handle higher functions.
#else
#if DEBUG_DCC_DECODE_FEATURE
                        printf("F29-F36, ignored");
#endif
#endif
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.6.8 GGGGG=11001 F37-F44 Function Control
                    } else if ((dcc_mesg[i] & 0x1F) == 0x19) {
#if FUNCTION_MAX > 38
                        // TODO: Handle higher functions.
#else
#if DEBUG_DCC_DECODE_FEATURE
                        printf("F37-F44, ignored");
#endif
#endif
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.6.9 GGGGG=11010 F45-F52 Function Control
                    } else if ((dcc_mesg[i] & 0x1F) == 0x1C) {
#if FUNCTION_MAX > 46
                        // TODO: Handle higher functions.
#else
#if DEBUG_DCC_DECODE_FEATURE
                        printf("F45-F52, ignored");
#endif
#endif
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.6.10 GGGGG=11011 F53-F60 Function Control
                    } else if ((dcc_mesg[i] & 0x1F) == 0x1B) {
#if FUNCTION_MAX > 54
                        // TODO: Handle higher functions.
#else
#if DEBUG_DCC_DECODE_FEATURE
                        printf("F53-F60, ignored");
#endif
#endif
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    // S-9.2.1 2.3.6.11 GGGGG=11100 G61-F68 Function Control
                    } else if ((dcc_mesg[i] & 0x1F) == 0x18) {
#if FUNCTION_MAX > 62
                        // TODO: Handle higher functions.
#else
#if DEBUG_DCC_DECODE_FEATURE
                        printf("G61-F68, ignored");
#endif
#endif
                        ++i; // Increment again, as it was a 2-BYTE instruction
                    }
                // S-9.2.1 2.3.7 CCC=111 Configuration Variable Access Instruction 3-BYTE instruction
                } else if ((dcc_mesg[i] & 0xE0) == 0xE0) {
                    // Only if sent to the base address.
                    if (dcc_address == pkt_addr) {

                        // S-9.2.1 2.3.7.2 Configuration Variable Access Instruction - Short Form
                        if (dcc_mesg[i] & 0x10) {
                            // GGGG=0010 Acceleration Adjustment Value CV23
                            if ((dcc_mesg[i] & 0x0F) == 0x02) {
                                cv_write(CV_ACCELERATION_ADJUSTMENT, dcc_mesg[i + 1]);
#if DEBUG_DCC_DECODE_CV
                                printf("%d Write CV23 Short Form value=%02x", pkt_addr, dcc_mesg[i + 1]);
#endif
                                // GGGG=0011 Deceleration Adjustment Value CV24
                            } else if ((dcc_mesg[i] & 0x0F) == 0x03) {
                                cv_write(CV_DECELERATION_ADJUSTMENT, dcc_mesg[i + 1]);
#if DEBUG_DCC_DECODE_CV
                                printf("%d Write CV24 Short Form value=%02x", pkt_addr, dcc_mesg[i + 1]);
#endif
                                // GGGG=0100 Long Address CV17, CV18, CV29
                            } else if ((dcc_mesg[i] & 0x0F) == 0x04) {
                                cv_write(CV_EXTENDED_ADDRESS_LOW, dcc_mesg[i + 1]);
                                cv_write(CV_EXTENDED_ADDRESS_HIGH, dcc_mesg[i + 2]);
                                // Toggle to extended addressing.
                                cv_write(CV_CONFIGURATION_DATA, cv_read(CV_CONFIGURATION_DATA) | 0x20);
                                cv_cv29 = cv_read(CV_CONFIGURATION_DATA);
#if DEBUG_DCC_DECODE_CV
                                printf("%d Write CV17/CV18/CV29 Short Form new address=%d", pkt_addr, ((uint16_t) dcc_mesg[i + 2] << 8) | (uint16_t) dcc_mesg[i + 1]);
#endif
                                // GGGG=0101 Indexed CVs CV31, CV32
                            } else if ((dcc_mesg[i] & 0x0F) == 0x05) {
                                cv_write(CV_INDEX_HIGH_BYTE, dcc_mesg[i + 1]);
                                cv_write(CV_INDEX_LOW_BYTE, dcc_mesg[i + 2]);
#if DEBUG_DCC_DECODE_CV
                                printf("%d Write CV31/CV32 Short Form %d/%d", pkt_addr, dcc_mesg[i + 1], dcc_mesg[i + 1]);
#endif                            
                                // GGGG=1001 S-9.2.3 Appendix B Service Mode Decoder Lock Instruction
                            } else if ((dcc_mesg[i] & 0x0F) == 0x05) {
                                //TODO NOTE THIS IS A 2-BYTE and thus messes up the addition below!!!
#ifdef DEBUG_DCC_DECODE_CV
                                printf("Service Mode Decoder Lock Requested sent to %d locking address=%d", pkt_addr, dcc_mesg[i + 1]);
#endif      
                            } else {
#ifdef DEBUG_DCC_DECODE_CV
                                printf("CV Access Short Form undefined value %x, ignoring", dcc_mesg[i] & 0x0F);
#endif                            
                            }
                            // S-9.2.1 2.3.7.3 Configuration Variable Access Instruction - Long Form
                        } else {
                            cv_address = ((uint16_t) (dcc_mesg[i] & 0x03) << 8) | (uint16_t) dcc_mesg[i + 1];
                            ++cv_address; // "The Configuration variable being addressed is the provided 10-bit address plus 1"
                            // GG=01 Verify byte
                            if ((dcc_mesg[i] & 0x0C) == 0x04) {
#if DEBUG_DCC_DECODE_CV
                                printf("Verify CV Long Form CV=%d, requested=%02x, is=%02x",
                                        cv_address, dcc_mesg[i + 2], cv_read(cv_address));
#endif
                                //TODO read it back to the command station!
                                // GG=11 Write byte
                            } else if ((dcc_mesg[i] & 0x0C) == 0x0C) {
                                cv_write(cv_address, dcc_mesg[i + 2]);
                                // This may have changed our address, consist, CV29, etc, reinitialize.
                                dcc_initialize();
#if DEBUG_DCC_DECODE_CV
                                printf("%d Write CV Long Form CV=%d, value=%02x", pkt_addr, cv_address, dcc_mesg[i + 2]);
#endif
                                // GG=10 Bit Manipulation
                            } else if ((dcc_mesg[i] & 0x0C) == 0x08) {
                                cv_value = (dcc_mesg[i + 2] & 0x08) >> 3;
                                cv_bit = dcc_mesg[i + 2] & 0x07;
                                // Write bit
                                if (dcc_mesg[i + 2] & 0xF0) {
                                    // Set bit
                                    if (cv_value) {
                                        cv_write(cv_address, cv_read(cv_address) | (uint8_t) (1 << cv_bit));
                                        // Clear bit
                                    } else {
                                        cv_write(cv_address, cv_read(cv_address) & (~(1 << cv_bit)));
                                    }
                                    // This may have changed our address, CV29, etc, reinitialize.
                                    dcc_initialize();
#if DEBUG_DCC_DECODE_CV
                                    printf("Write CV Long Form CV=%ld, bit=%d, value=%d", cv_address, cv_bit, cv_value);
#endif
                                    // Verify bit
                                } else {
#if DEBUG_DCC_DECODE_CV
                                    printf("Verify CV Long Form CV=%ld, bit=%d, value=%d, is=%d",
                                            cv_address, cv_bit, cv_value, 
                                            (cv_read(cv_address) & (1 << cv_bit)) >> cv_bit);
#endif
                                    //TODO read it back to the command station!
                                }
                            }
                        }
                    }
                    i+=2; // Increment again, as it was a 3-BYTE instruction
                }
            }
        } else {
#if DEBUG_DCC_DECODE_NOT_FOR_US
            printf("Extended: Not for us, for %d", pkt_addr);
#endif
        }
#if DEBUG_DCC_DECODE_EXTENDED || DEBUG_DCC_DECODE_DECODER || DEBUG_DCC_DECODE_ADV_OPS || \
    DEBUG_DCC_DECODE_SPEED    || DEBUG_DCC_DECODE_E_FN    || DEBUG_DCC_DECODE_FEATURE || \
    DEBUG_DCC_DECODE_CV
        printf("\r\n");
#endif
    }
}

/*
 * dcc_performance - Print DCC performance measurements.
 * 
 * This is called every 25ms (TMR0) by the main loop to
 * perform period functions.  These include:
 *   - Checking if exiting service mode is warranted.
 *   - Printing performance statistics once per second.
 */
uint8_t dcc_per_second = 39;
uint8_t dcc_good_last = 255;
uint16_t address;
void dcc_periodic(void) {
    
    // This means we've received no valid DCC packets in the last 20ms.
    if (dcc_service_mode && (dcc_good_last == dcc_good_packets)) {
        dcc_service_mode = 0; // Drop out of service mode per S-9.2.3 Section C
        dcc_page = 1;         // Page Register back to default
#if DEBUG_STATUS
        printf("Dropping out of service mode.\r\n");
#endif
    }
    dcc_good_last = dcc_good_packets;
    
    // Timer is every 25 ms, so every 40 timers is once per second.
    // Printing statistics more often is too hard to read.
    --dcc_per_second;
    if (dcc_per_second == 0) {
        dcc_per_second = 39;

#if DEBUG_PERFORMANCE
        // Print how many times the counter was incremented to give us an idea of idle time.
        printf("Perf: %lu/%u/%u (%u, %u)\r\n", idle_count, dcc_interrupts, dcc_drops,
                dcc_zeros, dcc_ones);
        idle_count = 0;
        dcc_interrupts = 0;
        dcc_drops = 0;
        dcc_zeros = 0;
        dcc_ones = 0;
#endif

#if DEBUG_STATUS
        if (dcc_consist) {
            address = dcc_consist;
        } else {
            address = dcc_address;
        }
        printf("%d:%d(%d:%d) is %c@%d/%d Fn=%d%d%d%d%d%d%d%d%d%d%d%d%d\r\n",
                dcc_address, dcc_ndot, dcc_consist, dcc_consist_ndot,
                dcc_direction ? 'R' : 'F', dcc_speed, dcc_speedsteps,
                dcc_functions[0], dcc_functions[1], dcc_functions[2],
            dcc_functions[3], dcc_functions[4], dcc_functions[5],
            dcc_functions[6], dcc_functions[7], dcc_functions[8],
            dcc_functions[9], dcc_functions[10], dcc_functions[11],
            dcc_functions[12]);
#endif
    }
}

/*
 * dcc_idle - Called when there is nothing else to do, can be used for things
 *            like lighting animations.
 */
void dcc_idle(void) {
#if DEBUG_PERFORMANCE
    idle_count++;
#endif
}
