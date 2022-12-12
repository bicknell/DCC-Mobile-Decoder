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

/*
 * motor_control is called when we get a DCC speed/direction message
 */
void motor_control(uint8_t speedsteps, uint8_t speed, char direction) {

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

    // Toggling the mode[0] bit of CWG1CON1 changes direction of the full
    // bridge output.
    if (direction == 'F') {
        motor_direction = 0;
        CWG1CON1 = CWG1CON1 & 0xFE;
#if DEBUG_HW_MOTOR
    printf("Setting PWM1 to speed %d/255 forward.\r\n", motor_speed);
#endif

    } else if (direction == 'R') {
        motor_direction = 1;
        CWG1CON1 = CWG1CON1 | 0x01;
#if DEBUG_HW_MOTOR
    printf("Setting PWM1 to speed %d/255 backwards.\r\n", motor_speed);
#endif
    }

}

/*
 * function_control sets the output functions as requested from the DCC packet.
 *
 * At the moment we support no lighting effects so this is a very simple function.
 *
 */
void function_control(void) {

    if (my_dcc_functions[0]) {
        if (my_dcc_direction == 'F') {
            IO_F0F_SetHigh();
            IO_F0R_SetLow();
        } else { // Direction == 'R'
            IO_F0F_SetLow();
            IO_F0R_SetHigh();
        }
    } else { // Off
        IO_F0F_SetLow();
        IO_F0R_SetLow();
    }
    if (my_dcc_functions[1]) { IO_F1_SetHigh(); } else { IO_F1_SetLow(); }
    if (my_dcc_functions[2]) { IO_F2_SetHigh(); } else { IO_F2_SetLow(); }
    if (my_dcc_functions[3]) { IO_F3_SetHigh(); } else { IO_F3_SetLow(); }
    if (my_dcc_functions[4]) { IO_F4_SetHigh(); } else { IO_F4_SetLow(); }
    if (my_dcc_functions[5]) { IO_F5_SetHigh(); } else { IO_F5_SetLow(); }
    if (my_dcc_functions[6]) { IO_F6_SetHigh(); } else { IO_F6_SetLow(); }

    // Functions 7-12 are not implemented in this hardware.
}
