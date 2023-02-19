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
#include "dcc.h"
#include "debug.h"
#include "hardware.h"

/*
 * Variables associated with motor_control, motor_pwm
 */
static uint8_t motor_speed     = 0;   // 0-255 speed of motor
static uint8_t motor_direction = 0;   // 0 = forward, 1 = reverse

// Effects bit array.  
// Each row is an indexable effect.
// Each column is a bit array, 4 bytes per second, 2 seconds of pattern total.
static uint8_t effects[10][8] = {
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },       // Row 0: Continuous On, default
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },       // Row 1: Mars Light
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },       // Row 2: Random Flicker
    { 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 },       // Row 3: Flashing Headlight
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03 },       // Row 4: Single Pulse Strobe
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03 },       // Row 5: Double Pulse Strobe
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },       // Row 6: Rotary Beacon
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },       // Row 7: Gyralite
    { 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 },       // Row 8: Ditch Light Left
    { 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF },       // Row 9: Ditch Light Right
};

/*
 * motor_control is called when we get a DCC speed/direction message
 */
void motor_control(uint8_t speedsteps, uint8_t speed, uint8_t direction) {    
    if (speedsteps == 128) {
        if (speed == 1) {
            // In 128SS mode, a speed of 1 is ESTOP.  Treat the same as stop.
            speed = 0;
        }

        // We don't implement any speed tables yet, so just scale 128SS into 
        // the 256 byte actual speed.
        motor_speed = (uint8_t)(speed << 1);
    } else if (speedsteps == 28) {
        // Technically this makes top speed 252/255, oh well.
        motor_speed = speed * 9;
    } else if (speedsteps == 14) {
        // Technically this makes top speed 252/255, oh well.
        motor_speed = speed * 9;
    }

    PWM1_16BIT_SetSlice1Output2DutyCycleRegister(motor_speed);
    PWM1_16BIT_LoadBufferRegisters();


    // Are we in a consist?
    if (my_dcc_consist) {
        motor_direction = direction ^ (my_dcc_consist_ndot ^ my_dcc_ndot);
    // Not in a consist.
    } else {
        motor_direction = direction ^ my_dcc_ndot;
    }
 
    // Toggling the mode[0] bit of CWG1CON1 changes direction of the full
    // bridge output.
    // Reverse
    if (motor_direction) {
        CWG1CON1 = CWG1CON1 | 0x01;
    // Forward
    } else {
        CWG1CON1 = CWG1CON1 & 0xFE;
    }
#if DEBUG_HW_MOTOR
    printf("Motor PWM %d/255 direction %c.\r\n", motor_speed, motor_direction ? 'R' : 'F');
#endif
}

/*
 * function_control sets the output functions as requested from the DCC packet.
 *
 * At the moment we support no lighting effects so this is a very simple function.
 *
 */
void function_control(void) {
    static uint8_t idx = 0;
    static uint8_t pos = 0x80;
    
    // Functions in the forward direction.
    if (my_dcc_direction == 0) {             // Group by direction, this is forward
        if (my_dcc_functions[0]) {           // User wants F0 On
            if (my_dcc_effects[0] & 0x80) { // Effect is in the forward direction
                if (effects[my_dcc_effects[0] & 0x3F][idx] & pos) { IO_F0F_SetHigh(); } else { IO_F0F_SetLow(); };
                IO_F0R_SetLow();
            }
        } else {
            IO_F0F_SetLow();
        }
        if (my_dcc_functions[1]) {           // User wants F1 On
            if (my_dcc_effects[1] & 0x80) { // Effect is in the forward direction
                if (effects[my_dcc_effects[1] & 0x3F][idx] & pos) { IO_F1_SetHigh(); } else { IO_F1_SetLow(); };
            }
        } else {
            IO_F1_SetLow();
        }
        if (my_dcc_functions[2]) {           // User wants F2 On
            if (my_dcc_effects[2] & 0x80) { // Effect is in the forward direction
                if (effects[my_dcc_effects[2] & 0x3F][idx] & pos) { IO_F2_SetHigh(); } else { IO_F2_SetLow(); };
            }
        } else {
            IO_F2_SetLow();
        }
        if (my_dcc_functions[3]) {           // User wants F3 On
            if (my_dcc_effects[3] & 0x80) { // Effect is in the forward direction
                if (effects[my_dcc_effects[3] & 0x3F][idx] & pos) { IO_F3_SetHigh(); } else { IO_F3_SetLow(); };
            }
        } else {
            IO_F3_SetLow();
        }
        if (my_dcc_functions[4]) {           // User wants F4 On
            if (my_dcc_effects[4] & 0x80) { // Effect is in the forward direction
                if (effects[my_dcc_effects[4] & 0x3F][idx] & pos) { IO_F4_SetHigh(); } else { IO_F4_SetLow(); };
            }
        } else {
            IO_F4_SetLow();
        }
        if (my_dcc_functions[5]) {           // User wants F5 On
            if (my_dcc_effects[5] & 0x80) { // Effect is in the forward direction
                if (effects[my_dcc_effects[5] & 0x3F][idx] & pos) { IO_F5_SetHigh(); } else { IO_F5_SetLow(); };
            }
        } else {
            IO_F5_SetLow();
        }
        if (my_dcc_functions[6]) {           // User wants F6 On
            if (my_dcc_effects[6] & 0x80) { // Effect is in the forward direction
                if (effects[my_dcc_effects[6] & 0x3F][idx] & pos) { IO_F6_SetHigh(); } else { IO_F6_SetLow(); };
            }
        } else {
            IO_F6_SetLow();
        }

    // Functions in the reverse direction.
    } else {
         if (my_dcc_functions[0]) {           // User wants F0 On
            if (my_dcc_effects[0] & 0x40) { // Effect is in the forward direction
                if (effects[my_dcc_effects[0] & 0x3F][idx] & pos) { IO_F0R_SetHigh(); } else { IO_F0R_SetLow(); };
                IO_F0F_SetLow();
            }
        } else {
            IO_F0R_SetLow();
        }
        if (my_dcc_functions[1]) {           // User wants F1 On
            if (my_dcc_effects[1] & 0x40) { // Effect is in the forward direction
                if (effects[my_dcc_effects[1] & 0x3F][idx] & pos) { IO_F1_SetHigh(); } else { IO_F1_SetLow(); };
            }
        } else {
            IO_F1_SetLow();
        }
        if (my_dcc_functions[2]) {           // User wants F2 On
            if (my_dcc_effects[2] & 0x40) { // Effect is in the forward direction
                if (effects[my_dcc_effects[2] & 0x3F][idx] & pos) { IO_F2_SetHigh(); } else { IO_F2_SetLow(); };
            }
        } else {
            IO_F2_SetLow();
        }
        if (my_dcc_functions[3]) {           // User wants F3 On
            if (my_dcc_effects[3] & 0x40) { // Effect is in the forward direction
                if (effects[my_dcc_effects[3] & 0x3F][idx] & pos) { IO_F3_SetHigh(); } else { IO_F3_SetLow(); };
            }
        } else {
            IO_F3_SetLow();
        }
        if (my_dcc_functions[4]) {           // User wants F4 On
            if (my_dcc_effects[4] & 0x40) { // Effect is in the forward direction
                if (effects[my_dcc_effects[4] & 0x3F][idx] & pos) { IO_F4_SetHigh(); } else { IO_F4_SetLow(); };
            }
        } else {
            IO_F4_SetLow();
        }
        if (my_dcc_functions[5]) {           // User wants F5 On
            if (my_dcc_effects[5] & 0x40) { // Effect is in the forward direction
                if (effects[my_dcc_effects[5] & 0x3F][idx] & pos) { IO_F5_SetHigh(); } else { IO_F5_SetLow(); };
            }
        } else {
            IO_F5_SetLow();
        }
        if (my_dcc_functions[6]) {           // User wants F6 On
            if (my_dcc_effects[6] & 0x40) { // Effect is in the forward direction
                if (effects[my_dcc_effects[6] & 0x3F][idx] & pos) { IO_F6_SetHigh(); } else { IO_F6_SetLow(); };
            }
        } else {
            IO_F6_SetLow();
        }
    }
    
    // Increment indexes.
    if (pos == 1) {
        pos = 0x80;
        idx++;
        if (idx > 7) { // MAGIC
            idx = 0;
        }
    } else {
        pos = pos >> 1;
    }
}
