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
 *     - In MCC CWG has been enabled and connected to the 4 H-Bridge MOSFETS.
 *     - In MCC PWM1 has been configured as the input for CWG.
 * 
 */

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "dcc.h"

/*
 * Variables associated with motor_control, motor_pwm
 */
static uint8_t motor_speed     = 0;   // 0-255 speed of motor
static uint8_t motor_direction = 0;   // 0 = forward, 1 = reverse

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

    // PWM takes a 16 bit value, but we only have 8 bits of speed.
    PWM1_16BIT_SetSlice1Output1DutyCycleRegister((uint16_t)motor_speed << 8);
    // Make the PWM re-read the output duty register.
    PWM1_16BIT_LoadBufferRegisters();

    // Are we in a consist?
    if (dcc_consist) {
        // TODO: I don't think this is right, should just be consist_ndot?
        motor_direction = direction ^ (dcc_consist_ndot ^ dcc_ndot);
    // Not in a consist.
    } else {
        motor_direction = direction ^ dcc_ndot;
    }
 
    // Toggling the mode[0] bit of CWG1CON0 changes direction of the full
    // bridge output.
    if (motor_direction) {
        // Reverse
        CWG1CON0 = CWG1CON0 | 0x01;
    } else {
        CWG1CON0 = CWG1CON0 & 0xFE;
        // Forward
    }
#if DEBUG_MOTOR
    printf("Motor PWM %d/255 direction %c.\r\n", motor_speed, motor_direction ? 'R' : 'F');
#endif
}
