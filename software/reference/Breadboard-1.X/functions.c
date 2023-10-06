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
 * This file contains routines to manipulate the motor, functions, and other
 * hardware specific outputs.
 * 
 * Assumptions:
 *     - In MCC pin manager, functions have been named IO_F0R, IO_F0F, IO_F1 - IO_F6
 *     - In MCC CWG has been enabeld and connected to the 4 H-Bridge MOSFETS.
 *     - In MCC PWM1 has been configured as the input for CWG.
 * 
 */

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "cv.h"
#include "dcc.h"
#include "debug.h"
#include "functions.h"
#include "hardware.h"

/*
 * Lighting effects.
 *
 * The unit of time in our loop is 20ms, or 50 per second.
 * Upper 2 bits of each byte are a command:
 */

#define   ON 0x80 // On full
#define HDIM 0x40 // On high dim
#define LDIM 0xC0 // On low dim
#define  OFF 0x00 // Off

#define FUNCTION_EFFECTS 16
#define FUNCTION_STEPS 8

uint8_t function_countdown[FUNCTION_EFFECTS] = {0};
uint8_t function_step[FUNCTION_STEPS] = {0};

/*
 * Lower 6 bytes (0x00 - 0x3F) are a time duration in 25ms units (from TMR0 in main).
 *
 * Known effects:
 * 
 * TODO: Rows 0, 3, 4, 5 work pretty good.
 * TODO: Rows 1, 2, 6, 7 need work.
 * TODO: Rows 8 and 9 don't work -- ditch lights aren't syncronized.
 * TODO: Row 15 - Dim is not yet implemented.
 */
static uint8_t effects[FUNCTION_EFFECTS][FUNCTION_STEPS] = {
    {   ON | 0x3F,   ON | 0x3F,   ON | 0x3F,   ON | 0x3F,   ON | 0x3F,   ON | 0x3F,   ON | 0x3F,   ON | 0x3F },       // Row  0: Continuous On, default
    {   ON | 0x05, HDIM | 0x30,   ON | 0x05, LDIM | 0x30,   ON | 0x05, HDIM | 0x30,   ON | 0x30, LDIM | 0x30 },       // Row  1: Mars Light
    {   ON | 0x02,  OFF | 0x30,   ON | 0x03,  OFF | 0x05,   ON | 0x05,  OFF | 0x3F,   ON | 0x02, OFF  | 0x3F },       // Row  2: Random Flicker
    {   ON | 0x3F,  OFF | 0x3F,   ON | 0x3F,  OFF | 0x3F,   ON | 0x3F,  OFF | 0x3F,   ON | 0x3F,  OFF | 0x3F },       // Row  3: Flashing Headlight
    {   ON | 0x01,  OFF | 0x3F,   ON | 0x01,  OFF | 0x3F,   ON | 0x01,  OFF | 0x3F,   ON | 0x01,  OFF | 0x3F },       // Row  4: Single Pulse Strobe
    {   ON | 0x01,  OFF | 0x02,   ON | 0x01,  OFF | 0x3F,   ON | 0x01,  OFF | 0x02,   ON | 0x01,  OFF | 0x3F },       // Row  5: Double Pulse Strobe
    {   ON | 0x02, HDIM | 0x05, LDIM | 0x05,  OFF | 0x25, LDIM | 0x05, HDIM | 0x05,   ON | 0x02,  ON  | 0x02 },       // Row  6: Rotary Beacon
    {   ON | 0x05, HDIM | 0x15,   ON | 0x05, HDIM | 0x15,   ON | 0x05, HDIM | 0x15,   ON | 0x15, HDIM | 0x15 },       // Row  7: Gyralite
    {   ON | 0x30,  OFF | 0x30,   ON | 0x30,  OFF | 0x30,   ON | 0x30,  OFF | 0x30,   ON | 0x30,  OFF | 0x30 },       // Row  8: Ditch Light Left
    {  OFF | 0x30,   ON | 0x30,  OFF | 0x30,   ON | 0x30,  OFF | 0x30,   ON | 0x30,  OFF | 0x30,   ON | 0x30 },       // Row  9: Ditch Light Right
    {  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F },       // Row 10: Unused
    {  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F },       // Row 11: Unused
    {  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F },       // Row 12: Unused
    {  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F },       // Row 13: Unused
    {  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F,  OFF | 0x3F },       // Row 14: Unused
    { LDIM | 0x3F, LDIM | 0x3F, LDIM | 0x3F, LDIM | 0x3F, LDIM | 0x3F, LDIM | 0x3F, LDIM | 0x3F, LDIM | 0x3F },       // Row 15: Continuous On, DIM 
};

void function_doeffect(int i) {
    if (function_countdown[i]) { // Has the timer expired?
        function_countdown[i]--; // No, decrement
    } else { // Yes, next step.   
        // Get the next timer value;
        function_step[i]++;
        if (function_step[i] > FUNCTION_STEPS) {
            function_step[i] = 0;
        }
        function_countdown[i] = effects[cv_effects[i] & 0x0F][function_step[i]] & 0x3F;
        // Perform the action.
#if DEBUG_FUNCTION
        printf("F%d S%d\r\n", i, function_step[i]);
#endif
        switch (effects[cv_effects[i] & 0x0F][function_step[i]] & 0xC0) {
            case ON: hardware_outputs[i](1);
                break;
            case HDIM: // TODO: connect to high rate PWM
            case LDIM: // TODO: connect to low rate PWM
            case OFF: hardware_outputs[i](0);
                break;
        }
    }
}

void function_effects(uint8_t i) { 
    /*
     * This logic is a real mess but to be a work-a-like with current
     * implementations this is what it takes.  Let's see how clear we
     * can make it....
     */
    if (dcc_functions[i] &&                                      // User has requested on AND
        (((cv_effects[i] & 0x80) == 0) ||                        // (not directional OR
         (my_dcc_direction == ((cv_effects[i] & 0x40) >> 6))) && //  direction matches) AND
        (((cv_effects[i] & 0x20) == 0) ||                        // (always on OR
            dcc_functions[0])                                    //  F0 is also on)
       ) { 
        function_doeffect(i);
    } else { // User has not requested the function to be on.
        hardware_outputs[i](0);
        // Reset effect
        function_countdown[i] = 0;
        function_step[i] = 0;
    }
}

/*
 * function_control sets the output functions as requested from the DCC packet.
 *
 * At the moment we support no lighting effects so this is a very simple function.
 *
 */
void function_control(void) {
    uint8_t i;

    // Functions 0 to 6 are effect capable.
    for (i = 0;i < 7; i++) {
        function_effects(i);
    }
    
    // Functions 7 to 12 are not effects capable, but may have output locations.
    for (; i < 12; i++) {
        if (dcc_functions[i]) { // User requested the function on.
            hardware_outputs[i](1);
        } else {
            hardware_outputs[i](0);
        }
    }
    // Functions higher than 12 are not tied to hardware outputs, but rather
    // are used for things like sound effects and such.
}
