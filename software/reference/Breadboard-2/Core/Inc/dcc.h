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

//#include "debug.h"
//#include "functions.h"
#define FUNCTION_MAX 16

#define DCC_FORWARD   0     // dcc_direction, dcc_not, dcc_consist_ndot
#define DCC_REVERSE   1     // dcc_direction, dcc_not, dcc_consist_ndot
    
/*
 * Function prototypes for our exposed functions.
 */
void DCC_ISR(void);
void dcc_initialize(void);
void dcc_decode(void);
void dcc_periodic(void);
void dcc_idle(void);

/*
 * Exposed global variables.
 * 
 * TODO: Reduce this list, use proper accessing functions.
 */
extern uint8_t             dcc_ndot;    // NDOT
extern uint16_t            dcc_consist;    // Configured consist address
extern uint8_t             dcc_consist_ndot;    // NDOT in consist.
extern uint8_t             dcc_functions[FUNCTION_MAX];  // DCC Packet Function State
extern uint8_t             dcc_direction;    // DCC Packet Direction, 0 == forward, 1 == reverse
extern volatile uint8_t    dcc_ready;    // DCC Message is ready.

#ifdef	__cplusplus
}
#endif

#endif	/* DCC_H */

