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

#ifndef DCC_H
#define	DCC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "debug.h"

/*
 * Function prototypes for our exposed functions.
 */
void DCC_ISR(void);
void dcc_initialize(void);
void dcc_decode(void);
void dcc_performance(void);
void dcc_idle(void);

/*
 * Exposed global variables.
 * 
 * TODO: Reduce this list, use proper accessing functions.
 */
uint16_t            my_dcc_address        = 0;    // Configured DCC address
uint8_t             my_dcc_functions[13]  = {0};  // DCC Packet Function State
uint8_t             my_dcc_speedsteps     = 0;    // DCC Packet Speed Steps
uint8_t             my_dcc_speed          = 0;    // DCC Packet Speed
char                my_dcc_direction      = 'F';  // DCC Packet Direction, F == forward, R == reverse
char                dcc_mesg[6]           = {0};  // DCC Messages can't be more than 6 bytes per S-9.2.1
uint8_t             dcc_len               = 0;    // Length of the DCC message.
volatile uint8_t    dcc_ready             = 0;    // DCC Message is ready.


#ifdef	__cplusplus
}
#endif

#endif	/* DCC_H */

