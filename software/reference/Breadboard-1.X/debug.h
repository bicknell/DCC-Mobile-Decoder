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
 * This file contains debug flags used across the code to print debugging 
 * information to the serial port.
 * 
 * Note that printf is fairly resource intensive and so enabling debugging
 * may significantly increase the code size and slow the processor.  However
 * it is still sometimes the most useful way to debug what is happening
 * with the decoder.
 */

#ifndef DEBUG_H
#define	DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdio.h>

/*
 * General Debugging 
 */
#define DEBUG_STATUS                   1  // Output the current decoder status once a second.
#define DEBUG_PERFORMANCE              1  // Collect statistics about performance and display once a second.

/*
 * Debugging of CV operations
 */
#define DEBUG_CV_RESET                 0  // Debug when we reset CV's.
#define DEBUG_CV_RW                    1  // Debug CV read/write operations.
    
/*
 * Debugging of the DCC signal:
 */
#define DEBUG_DCC_PACKET               0  // Dump the packet contents in hexadecimal.
#define DEBUG_DCC_DECODE_BASELINE      0  // Debug S-9.2 baseline packets.
#define DEBUG_DCC_DECODE_EXTENDED      0  // Debug S-9.2.1 instruction parsing
#define DEBUG_DCC_DECODE_DECODER       0  // Debug S-9.2.1 2.3.1 Decoder and Consist Control Instructions
#define DEBUG_DCC_DECODE_ADV_OPS       0  // Debug S-9.2.1 2.3.2 Advanced Operations Instructions
#define DEBUG_DCC_DECODE_SPEED         0  // Debug S-9.2.1 2.3.3 Speed and Direction Instructions
#define DEBUG_DCC_DECODE_E_FN          0  // Debug S-9.2.1 2.3.4/5 Function Group Instructions
#define DEBUG_DCC_DECODE_FEATURE       0  // Debug S-9.2.1 2.3.6 Feature Expansion Instructions
#define DEBUG_DCC_DECODE_CV            0  // Debug S-9.2.1 2.3.7 Configuration Variable Access
#define DEBUG_DCC_DECODE_NOT_FOR_US    0  // Show packets that are not for us (idle, other addresses).

/*
 * Debugging of hardware operations
 */
#define DEBUG_HW_MOTOR                 0  // Debug motor control operations.
#define DEBUG_HW_FUNCTION              0  // Debug function control operations.
    
#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

