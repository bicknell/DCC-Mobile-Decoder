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
#include "mcc_generated_files/mcc.h"
#include "cv.h"
#include "debug.h"

/*
 * cv_write - write a CV value to EEPROM
 * 
 * We don't use the DATAEE routines directly because we need to range-check
 * the CV.  We could receive a write command for a CV out of range.
 */
void cv_write(uint16_t cv, uint8_t value) {
    // We don't support CV's outside of 0-255 today.
    if (cv > 255) {
        return;
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
 */
void cv_factory_defaults(void) {
    // Flash appears to be uninitialized, perhaps a freshly programmed chip.
    // Set the defaults.
#if DEBUG_CV_RESET
    printf("Resetting CV's to factory defaults.\r\n");
    printf("Note: Default settings erase flash on programming.\r\n");
    printf("Note: Project Properties->Conf->PICKit 4->Memories to Program->Preserve EEPROM Memory.\r\n");
#endif
    cv_write(CV_PRIMARY_ADDRESS, 3);              // Short address == 3
    cv_write(CV_VSTART, 0);
    cv_write(CV_ACCELERATION_RATE, 0);
    cv_write(CV_DECELERATION_RATE, 0);
    cv_write(CV_VHIGH, 0);
    cv_write(CV_VMID, 0);
    cv_write(CV_MANUFACTURER_VERSION, 167);       // Magic Cookie Value
    cv_write(CV_MANUFACTURER_ID, 13);             // 13 == Public Domain
    cv_write(CV_TOTAL_PWM_PERIOD, 0);
    cv_write(CV_EMF_FEEDBACK_CUTOUT, 0);
    cv_write(CV_PACKET_TIME_OUT_VALUE, 0);
    cv_write(CV_POWER_SOURCE_CONVERSION, 0);
    cv_write(CV_ALT_FUNCTION_F1_F8, 0);
    cv_write(CV_ALT_FUNCTION_FL_F9_F12, 0);
    cv_write(CV_DECODER_LOCK_LOW, 0);
    cv_write(CV_DECODER_LOCK_HIGH, 0);
    cv_write(CV_EXTENDED_ADDRESS_LOW, 0x00);
    cv_write(CV_EXTENDED_ADDRESS_HIGH, 0x00);
    cv_write(CV_CONSIST_ADDRESS, 0);
    cv_write(CV_CONSIST_ACTIVE_F1_F8, 0xFF);      // All active
    cv_write(CV_CONSIST_ACTIVE_FL_F9_F12, 0x3F);  // All active
    cv_write(CV_ACCELERATION_ADJUSTMENT, 0);
    cv_write(CV_DECELERATION_ADJUSTMENT, 0);
    cv_write(CV_SPEED_TABLE, 0);
    cv_write(CV_AUTOMATIC_STOPPING, 0);
    cv_write(CV_BI_DIRECTIONAL_COMM, 0);
    cv_write(CV_CONFIGURATION_DATA, 0x02);        // Short Address, Vstart/Vmin/Vmax, No Alt Power, 28/128 mode enabled, NDOT Forward
    cv_write(CV_ERROR_INFORMATION, 0);
    cv_write(CV_INDEX_HIGH_BYTE, 0);
    cv_write(CV_INDEX_LOW_BYTE, 0);
    cv_write(CV_OUTPUT_LOC_FLF,  0x01);
    cv_write(CV_OUTPUT_LOC_FLR,  0x02);
    cv_write(CV_OUTPUT_LOC_FL1,  0x04);
    cv_write(CV_OUTPUT_LOC_FL2,  0x08);
    cv_write(CV_OUTPUT_LOC_FL3,  0x10);
    cv_write(CV_OUTPUT_LOC_FL4,  0x04);
    cv_write(CV_OUTPUT_LOC_FL5,  0x08);
    cv_write(CV_OUTPUT_LOC_FL6,  0x10);
    cv_write(CV_OUTPUT_LOC_FL7,  0x20);
    cv_write(CV_OUTPUT_LOC_FL8,  0x40);
    cv_write(CV_OUTPUT_LOC_FL9,  0x10);
    cv_write(CV_OUTPUT_LOC_FL10, 0x20);
    cv_write(CV_OUTPUT_LOC_FL11, 0x40);
    cv_write(CV_OUTPUT_LOC_FL12, 0x80);
    cv_write(CV_KICK_START, 0);
    cv_write(CV_FORWARD_TRIM, 0);
    cv_write(CV_FORWARD_TRIM, 0);
    cv_write(CV_SPEED_TABLE_A, 0);
    cv_write(CV_SPEED_TABLE_B, 0);
    cv_write(CV_SPEED_TABLE_C, 0);
    cv_write(CV_SPEED_TABLE_D, 0);
    cv_write(CV_SPEED_TABLE_E, 0);
    cv_write(CV_SPEED_TABLE_F, 0);
    cv_write(CV_SPEED_TABLE_G, 0);
    cv_write(CV_SPEED_TABLE_H, 0);
    cv_write(CV_SPEED_TABLE_I, 0);
    cv_write(CV_SPEED_TABLE_J, 0);
    cv_write(CV_SPEED_TABLE_K, 0);
    cv_write(CV_SPEED_TABLE_L, 0);
    cv_write(CV_SPEED_TABLE_M, 0);
    cv_write(CV_SPEED_TABLE_N, 0);
    cv_write(CV_SPEED_TABLE_O, 0);
    cv_write(CV_SPEED_TABLE_P, 0);
    cv_write(CV_SPEED_TABLE_Q, 0);
    cv_write(CV_SPEED_TABLE_R, 0);
    cv_write(CV_SPEED_TABLE_S, 0);
    cv_write(CV_SPEED_TABLE_T, 0);
    cv_write(CV_SPEED_TABLE_U, 0);
    cv_write(CV_SPEED_TABLE_V, 0);
    cv_write(CV_SPEED_TABLE_W, 0);
    cv_write(CV_SPEED_TABLE_X, 0);
    cv_write(CV_SPEED_TABLE_Y, 0);
    cv_write(CV_SPEED_TABLE_Z, 0);
    cv_write(CV_SPEED_TABLE_AA, 0);
    cv_write(CV_SPEED_TABLE_AB, 0);
    cv_write(CV_REVERSE_TRIM, 0);
    cv_write(CV_USER_ID_1, 0);
    cv_write(CV_USER_ID_2, 0);
    cv_write(CV_E_MANUFACTURER_ID_LOW, 0);
    cv_write(CV_E_MANUFACTURER_ID_HIGH, 0);
    cv_write(CV_E_MANUFACTURER_VERSION_A, 0);
    cv_write(CV_E_MANUFACTURER_VERSION_B, 0);
    cv_write(CV_E_MANUFACTURER_VERSION_C, 0);
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
}
