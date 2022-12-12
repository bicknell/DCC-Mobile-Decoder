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

#ifndef HARDWARE_H
#define	HARDWARE_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Function prototypes for our exposed functions.
 */
void motor_pwm(void);
void motor_control(uint8_t speedsteps, uint8_t speed, char direction);
void function_control(void);


#ifdef	__cplusplus
}
#endif

#endif	/* HARDWARE_H */

