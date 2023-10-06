/*
 * This code is subject to the
 * 
 * Creative Commons Attribution-NonCommercial 4.0 International Public License
 * 
 * Please see https://github.com/bicknell/DCC-Mobile-Decoder/LICENSE for full
 * license terms.
 *
 */

/* 
 * File:   motor.h
 * Author: bicknell
 *
 * Created on October 5, 2023, 8:41 AM
 */

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Function prototypes for our exposed functions.
 */
void motor_pwm(void);
void motor_control(uint8_t speedsteps, uint8_t speed, uint8_t direction);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

