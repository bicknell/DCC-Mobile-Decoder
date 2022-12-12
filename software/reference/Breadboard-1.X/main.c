/*
 * This code is subject to the
 * 
 * Creative Commons Attribution-NonCommercial 4.0 International Public License
 * 
 * Please see https://github.com/bicknell/DCC-Mobile-Decoder/LICENSE for full
 * license terms.
 *
 */

/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F16Q40
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/* DESCRIPTION
 *
 * main program loop.
 * 
 * Calls any necessary initialization functions and then begins to forever
 * loop on decoding DCC packets.
 * 
 */

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "cv.h"
#include "dcc.h"
#include "debug.h"


/*
 *                       Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Drive unused pins low, per the data sheet.
    IO_Unused1_SetLow();
    
    // TMR2 is hooked to the DCC input pin, and calls the ISR.
    TMR2_SetInterruptHandler(DCC_ISR);

#if DEBUG_STATUS
    printf("\r\nSystem Boot\r\n");
#endif
    
    // Make sure the EEPROM data has been configured.
    cv_check();
    
    // Initialize the DCC subsystem based on the CV's configured.
    dcc_initialize();
    
    // Turn on interrupts.
    INTERRUPT_GlobalInterruptEnable();
    
    // Start reading the DCC signal.
    TMR2_StartTimer(); 
        
    while (1)
    {
        // TMR0 is a once per second heartbeat we use for status reporting.
        TMR0_Initialize();
        TMR0_StartTimer();
        
        // Wait for TMR0 to go off
        while(!TMR0_HasOverflowOccured()) {
            // Is there anything to do during idle time?
            dcc_idle();
            
            // Did a DCC packet come in?
            if (dcc_ready) {
                uint8_t xor = 0;

                // Compute checksum.
                for (uint8_t idx = 0; idx < dcc_len; ++idx) {
                    xor ^= dcc_mesg[idx];
                }

#if DEBUG_DCC_PACKET
                // Do not print newline if passing, so decode is on the same line.
                printf("Rec %02x %02x %02x %02x %02x %02x (%d) %s",
                        dcc_mesg[0], dcc_mesg[1], dcc_mesg[2],
                        dcc_mesg[3], dcc_mesg[4], dcc_mesg[5],
                        dcc_len, xor ? "FAIL\r\n" : "PASS: ");
#endif
                // If the checksum was good, decode the message.
                if (xor == 0) {
                    dcc_decode();
// This has gotten ugly, need to rethink.
#if DEBUG_DCC_PACKET || DEBUG_DCC_DECODE_BASELINE || DEBUG_DCC_DECODE_EXTENDED || \
    DEBUG_DCC_DECODE_DECODER || DEBUG_DCC_DECODE_ADV_OPS || DEBUG_DCC_DECODE_SPEED || \
    DEBUG_DCC_DECODE_E_FN || DEBUG_DCC_DECODE_FEATURE || DEBUG_DCC_DECODE_CV || \
    DEBUG_DCC_DECODE_E_NOT_FOR_US
                    printf("\r\n");
#endif
                }

                
                // Tell the ISR we've consumed the message and it can store another.
                dcc_ready = 0;
            }
        }
        
        // Control reaches here when TMR0 has gone off.
#if DEBUG_STATUS
        printf("%d is %c@%d/%d Fn=%d%d%d%d%d%d%d%d%d%d%d%d%d\r\n",
                my_dcc_address, my_dcc_direction, my_dcc_speed, my_dcc_speedsteps,
                my_dcc_functions[0], my_dcc_functions[1], my_dcc_functions[2],
                my_dcc_functions[3], my_dcc_functions[4], my_dcc_functions[5],
                my_dcc_functions[6], my_dcc_functions[7], my_dcc_functions[8],
                my_dcc_functions[9], my_dcc_functions[10], my_dcc_functions[11],
                my_dcc_functions[12]);
#endif
        // Print DCC performance statistics and clear, if enabled.
        dcc_performance();
    }
}
/**
 End of File
*/
