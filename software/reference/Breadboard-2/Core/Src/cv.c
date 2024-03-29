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
 * This file contains routines to manipulate Configuration Variables (CV's),
 * including reading and writing them from device EEPROM.
 * 
 * This device has 512 bytes of EEPROM.  We use the first 256 bytes of that
 * space to store 256 CV values.
 * 
 * Requires the MEMORY module to be loaded in MCC, and the "Add DataEE routines"
 * check box to be checked.
 * 
 */

#include <stdint.h>
#include "cv.h"
#include "debug.h"

/*
 * Exposed global variables.
 */

uint8_t     cv_effects[FUNCTION_MAX]    = {0};  // Cache of effects.

/*
 * Locally scoped variables.
 */
static uint8_t cv_read_only[] = {   // A list of CV's that are read only.
    CV_MANUFACTURER_VERSION,
    CV_MANUFACTURER_ID,
    CV_E_MANUFACTURER_ID_LOW,
    CV_E_MANUFACTURER_ID_HIGH,
    CV_E_MANUFACTURER_VERSION_A,
    CV_E_MANUFACTURER_VERSION_B,
    CV_E_MANUFACTURER_VERSION_C,
    0
};

uint8_t ram_cvs[256];
#define DATAEE_WriteByte(cv, val) ram_cvs[cv] = val
#define DATAEE_ReadByte(cv) ram_cvs[cv]
/*
 * Prototypes for local functions.
 */
void    cv_factory_defaults(void);
void    cv_reset_next_time(void);

/*
 * cv_write - write a CV value to EEPROM
 * 
 * We don't use the DATAEE routines directly because we need to range-check
 * the CV.  We could receive a write command for a CV out of range.
 */
void cv_write(uint16_t cv, uint8_t value) {
    uint8_t *i;
    
    // We don't support CV's outside of 0-255 today.
    if (cv > 255) {
        return;
    }

    // DECODER FACTORY RESET -- Special Case
    // An attempt to set CV8 to 00001000 is supposed to do a full
    // factory reset.  In service mode we may not have power long
    // enough to write all of our CV's, so we simply flag that it
    // needs to be done on the NEXT power up.
    if ((cv == 8) && (value == 0x08)) {
        // Flag so we reset to factory defaults all CV's next boot.
        cv_reset_next_time();
        return;
    }

    // Scan through the list of read only CV's.
    i = cv_read_only;
    while (*i != 0) {
        // If we match, return and don't allow a write.
        if (*i == cv) {
#if DEBUG_CV_RW
    printf("Attempt to write to read only CV %d ignored.\r\n", cv);
#endif
            return;
        }
        ++i;
    }
    DATAEE_WriteByte(cv, value);
#if DEBUG_CV_RW
    printf("Write CV %d=%d\r\n", cv, value);
#endif
}

/*
 * cv_read - read a CV value from EEPROM
 * 
 * We don't use the DATAEE routines directly because we need to range-check
 * the CV.  We could receive a write command for a CV out of range.
 */
uint8_t cv_read(uint16_t cv) {  
    // We don't support CV's outside of 0-255 today.
    if (cv > 255) {
        return 0;
    }
#if DEBUG_CV_RW
    printf("Read CV %d\r\n", cv);
#endif
    return (uint8_t)DATAEE_ReadByte(cv);
}

/*
 * cv_factory_defaults - Reset all CV's to factory default values.
 * 
 * This may be called because our flash is blank (e.g. first programming)
 * or because a decoder reset was commanded by the user.
 * 
 * We don't use cv_write here because cv_write checks for the read-only CV's.
 * If the flash is blank those need to be programmed.
 */
void cv_factory_defaults(void) {
    // Flash appears to be uninitialized, perhaps a freshly programmed chip.
    // Set the defaults.
#if DEBUG_CV_RESET
    printf("Resetting CV's to factory defaults.\r\n");
    printf("Note: Default settings erase flash on programming.\r\n");
    printf("Note: Project Properties->Conf->PICKit 4->Memories to Program->Preserve EEPROM Memory.\r\n");
#endif
    DATAEE_WriteByte(CV_PRIMARY_ADDRESS, 3);              // Short address == 3
    DATAEE_WriteByte(CV_VSTART, 0);
    DATAEE_WriteByte(CV_ACCELERATION_RATE, 0);
    DATAEE_WriteByte(CV_DECELERATION_RATE, 0);
    DATAEE_WriteByte(CV_VHIGH, 0);
    DATAEE_WriteByte(CV_VMID, 0);
// Manufacturer Version Out of Order, See Bottom
// Manufacturer ID Out of Order, See Bottom
    DATAEE_WriteByte(CV_TOTAL_PWM_PERIOD, 0);
    DATAEE_WriteByte(CV_EMF_FEEDBACK_CUTOUT, 0);
    DATAEE_WriteByte(CV_PACKET_TIME_OUT_VALUE, 0);
    DATAEE_WriteByte(CV_POWER_SOURCE_CONVERSION, 0);
    DATAEE_WriteByte(CV_ALT_FUNCTION_F1_F8, 0);
    DATAEE_WriteByte(CV_ALT_FUNCTION_FL_F9_F12, 0);
    DATAEE_WriteByte(CV_DECODER_LOCK_LOW, 0);
    DATAEE_WriteByte(CV_DECODER_LOCK_HIGH, 0);
    DATAEE_WriteByte(CV_EXTENDED_ADDRESS_LOW, 0x00);
    DATAEE_WriteByte(CV_EXTENDED_ADDRESS_HIGH, 0x00);
    DATAEE_WriteByte(CV_CONSIST_ADDRESS, 0);
    DATAEE_WriteByte(CV_CONSIST_ACTIVE_F1_F8, 0xFF);      // All active
    DATAEE_WriteByte(CV_CONSIST_ACTIVE_FL_F9_F12, 0x3F);  // All active
    DATAEE_WriteByte(CV_ACCELERATION_ADJUSTMENT, 0);
    DATAEE_WriteByte(CV_DECELERATION_ADJUSTMENT, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE, 0);
    DATAEE_WriteByte(CV_AUTOMATIC_STOPPING, 0);
    DATAEE_WriteByte(CV_BI_DIRECTIONAL_COMM, 0);
    DATAEE_WriteByte(CV_CONFIGURATION_DATA, 0x02);        // Short Address, Vstart/Vmin/Vmax, No Alt Power, 28/128 mode enabled, NDOT Forward
    DATAEE_WriteByte(CV_ERROR_INFORMATION, 0);
    DATAEE_WriteByte(CV_INDEX_HIGH_BYTE, 0);
    DATAEE_WriteByte(CV_INDEX_LOW_BYTE, 0);
    DATAEE_WriteByte(CV_OUTPUT_LOC_F0F,  0x00);
    DATAEE_WriteByte(CV_OUTPUT_LOC_F0R,  0x01);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL1,  0x02);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL2,  0x03);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL3,  0x04);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL4,  0x05);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL5,  0x06);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL6,  0x07);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL7,  0x08);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL8,  0x09);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL9,  0x0A);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL10, 0x0B);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL11, 0x0C);
    DATAEE_WriteByte(CV_OUTPUT_LOC_FL12, 0x0D);
    DATAEE_WriteByte(CV_KICK_START, 0);
    DATAEE_WriteByte(CV_FORWARD_TRIM, 0);
    DATAEE_WriteByte(CV_FORWARD_TRIM, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_A, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_B, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_C, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_D, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_E, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_F, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_G, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_H, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_I, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_J, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_K, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_L, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_M, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_N, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_O, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_P, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_Q, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_R, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_S, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_T, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_U, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_V, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_W, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_X, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_Y, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_Z, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_AA, 0);
    DATAEE_WriteByte(CV_SPEED_TABLE_AB, 0);
    DATAEE_WriteByte(CV_REVERSE_TRIM, 0);
    DATAEE_WriteByte(CV_USER_ID_1, 0);
    DATAEE_WriteByte(CV_USER_ID_2, 0);
    DATAEE_WriteByte(CV_E_MANUFACTURER_ID_LOW, 0);
    DATAEE_WriteByte(CV_E_MANUFACTURER_ID_HIGH, 0);
    DATAEE_WriteByte(CV_E_MANUFACTURER_VERSION_A, 0);
    DATAEE_WriteByte(CV_E_MANUFACTURER_VERSION_B, 0);
    DATAEE_WriteByte(CV_E_MANUFACTURER_VERSION_C, 0);
    DATAEE_WriteByte(CV_F0_FX, 0x00); // Both directions active, always on.
    DATAEE_WriteByte(CV_F1_FX, 0x00); // Both directions active, always on.
    DATAEE_WriteByte(CV_F2_FX, 0x00); // Both directions active, always on.
    DATAEE_WriteByte(CV_F3_FX, 0x00); // Both directions active, always on.
    DATAEE_WriteByte(CV_F4_FX, 0x00); // Both directions active, always on.
    DATAEE_WriteByte(CV_F5_FX, 0x00); // Both directions active, always on.
    DATAEE_WriteByte(CV_F6_FX, 0x00); // Both directions active, always on.
    
    // The entries above are carefully ordered numerically.
    // These two have been pulled out, because they are used
    // to determine if the flash is programmed, or if a factory
    // reset is required.  If the processor got half way through
    // the list above before losing power we want to re-do it
    // on the next boot.  Thus these are set last to signify "done".
    DATAEE_WriteByte(CV_MANUFACTURER_VERSION, 167);       // Magic Cookie Value
    DATAEE_WriteByte(CV_MANUFACTURER_ID, 13);             // 13 == Public Domain
}

/*
 * cv_reset_next_time - Reset to factory defaults on next boot.
 * 
 * Used when a factory reset service mode packet comes in.
 */
void cv_reset_next_time(void) {
#if DEBUG_CV_RESET
    printf("Setting Manufacturer ID to 255.\r\n");
#endif
    DATAEE_WriteByte(CV_MANUFACTURER_ID, 255);
}

/* 
 * cv_check - Check if CV's are programmed.
 * 
 * When chip is programmed the flash is erased.  If the flash looks empty,
 * program it with factory default values.
 * 
 * This assumes if the manufacturer's version (CV7) and id (CV8) are not set
 * to our expected values that all of flash is blank and we need to set all
 * CV values.
 */
void cv_check(void) {
    // Per https://www.nmra.org/sites/default/files/standards/sandrp/pdf/appendix_a_s-9_2_2_5.pdf
    // Manufacturer ID 13 is for "Public Domain & Do-It-Yourself Decoders".
    // Additionally at this time we don't version decoders, so we use 167
    // as a "magic cookie" in the version number.

    // Check if it looks like flash has been initialized.
//TODO - Get our own manufacturer ID number.
//TODO - Assign version numbers to our decoders.
    if ((cv_read(CV_MANUFACTURER_VERSION) == 167) &&
            (cv_read(CV_MANUFACTURER_ID) == 13)) {
        // Flash is good to go, we hope.  Other checks?
    } else {
        cv_factory_defaults();
    }
    
    // Cache the effects CV's for use in functions.c
    cv_effects[0] = cv_read(CV_F0_FX);
    cv_effects[1] = cv_read(CV_F1_FX);
    cv_effects[2] = cv_read(CV_F2_FX);
    cv_effects[3] = cv_read(CV_F3_FX);
    cv_effects[4] = cv_read(CV_F4_FX);
    cv_effects[5] = cv_read(CV_F5_FX);
    cv_effects[6] = cv_read(CV_F6_FX);
    
}

