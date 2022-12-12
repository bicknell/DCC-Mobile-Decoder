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

#ifndef CV_H
#define	CV_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Function prototypes for our exposed functions.
 */
void    cv_write(uint16_t cv, uint8_t value);
uint8_t cv_read(uint16_t cv);
void    cv_factory_defaults(void);
void    cv_check(void);

/*
 * CV name to number mapping so we can use more meaningful names in the code.
 * 
 * CV names taken from: 
 * https://www.nmra.org/sites/default/files/standards/sandrp/pdf/s-9.2.2_decoder_cvs_2012.07.pdf
 */

#define CV_PRIMARY_ADDRESS             1
#define CV_VSTART                      2
#define CV_ACCELERATION_RATE           3
#define CV_DECELERATION_RATE           4
#define CV_VHIGH                       5
#define CV_VMID                        6
#define CV_MANUFACTURER_VERSION        7  /* Manufacturer defined version info */
#define CV_MANUFACTURER_ID             8  /* Values assigned by NMRA */
#define CV_TOTAL_PWM_PERIOD            9
#define CV_EMF_FEEDBACK_CUTOUT        10
#define CV_PACKET_TIME_OUT_VALUE      11
#define CV_POWER_SOURCE_CONVERSION    12
#define CV_ALT_FUNCTION_F1_F8         13
#define CV_ALT_FUNCTION_FL_F9_F12     14
#define CV_DECODER_LOCK_LOW           15
#define CV_DECODER_LOCK_HIGH          16
#define CV_EXTENDED_ADDRESS_LOW       17
#define CV_EXTENDED_ADDRESS_HIGH      18
#define CV_CONSIST_ADDRESS            19
                                          /* Reserved by NMRA for future use */
#define CV_CONSIST_ACTIVE_F1_F8       21
#define CV_CONSIST_ACTIVE_FL_F9_F12   22
#define CV_ACCELERATION_ADJUSTMENT    23
#define CV_DECELERATION_ADJUSTMENT    24
#define CV_SPEED_TABLE                25
                                          /* Reserved by NMRA for future use */
#define CV_AUTOMATIC_STOPPING         27
#define CV_BI_DIRECTIONAL_COMM        28
#define CV_CONFIGURATION_DATA         29
#define CV_ERROR_INFORMATION          30
#define CV_INDEX_HIGH_BYTE            31
#define CV_INDEX_LOW_BYTE             32
#define CV_OUTPUT_LOC_FLF             33
#define CV_OUTPUT_LOC_FLR             34
#define CV_OUTPUT_LOC_FL1             35
#define CV_OUTPUT_LOC_FL2             36
#define CV_OUTPUT_LOC_FL3             37
#define CV_OUTPUT_LOC_FL4             38
#define CV_OUTPUT_LOC_FL5             39
#define CV_OUTPUT_LOC_FL6             40
#define CV_OUTPUT_LOC_FL7             41
#define CV_OUTPUT_LOC_FL8             42
#define CV_OUTPUT_LOC_FL9             43
#define CV_OUTPUT_LOC_FL10            44
#define CV_OUTPUT_LOC_FL11            45
#define CV_OUTPUT_LOC_FL12            46
                                          /* Manufacturer Unique */
#define CV_KICK_START                 65
#define CV_FORWARD_TRIM               66
#define CV_SPEED_TABLE_A              67
#define CV_SPEED_TABLE_B              68
#define CV_SPEED_TABLE_C              69
#define CV_SPEED_TABLE_D              70
#define CV_SPEED_TABLE_E              71
#define CV_SPEED_TABLE_F              72
#define CV_SPEED_TABLE_G              73
#define CV_SPEED_TABLE_H              74
#define CV_SPEED_TABLE_I              75
#define CV_SPEED_TABLE_J              76
#define CV_SPEED_TABLE_K              77
#define CV_SPEED_TABLE_L              78
#define CV_SPEED_TABLE_M              79
#define CV_SPEED_TABLE_N              80
#define CV_SPEED_TABLE_O              81
#define CV_SPEED_TABLE_P              82
#define CV_SPEED_TABLE_Q              83
#define CV_SPEED_TABLE_R              84
#define CV_SPEED_TABLE_S              85
#define CV_SPEED_TABLE_T              86
#define CV_SPEED_TABLE_U              87
#define CV_SPEED_TABLE_V              88
#define CV_SPEED_TABLE_W              89
#define CV_SPEED_TABLE_X              90
#define CV_SPEED_TABLE_Y              91
#define CV_SPEED_TABLE_Z              92
#define CV_SPEED_TABLE_AA             93
#define CV_SPEED_TABLE_AB             94
#define CV_REVERSE_TRIM               95
                                          /* Reserved by NMRA for future use */
#define CV_USER_ID_1                 105
#define CV_USER_ID_2                 106
#define CV_E_MANUFACTURER_ID_LOW     107
#define CV_E_MANUFACTURER_ID_HIGH    108
#define CV_E_MANUFACTURER_VERSION_A  109
#define CV_E_MANUFACTURER_VERSION_B  110
#define CV_E_MANUFACTURER_VERSION_C  111
                                          /* Reserved for manufacturer use */
#define CV_INDEX_START               257
#define CV_INDEX_END                 512
                                          /* Reserved by NMRA for future use */
                                          /* Reserved by NMRA for future use */
#define CV_DECODER_LOAD              892
#define CV_DYNAMIC_FLAGS             893
#define CV_FUEL_COAL                 894
#define CV_WATER                     895
#define CV_SUSI_START                896
#define CV_SUSI_END                 1024

#ifdef	__cplusplus
}
#endif

#endif	/* CV_H */

