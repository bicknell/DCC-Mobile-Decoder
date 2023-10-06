/**
  PWM2_16BIT Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm2_16bit.h

  @Summary
    This is the generated header file for the PWM2_16BIT driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for PWM2_16BIT.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F16Q40
        Driver Version    :  1.0.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above or later
        MPLAB             :  MPLAB X 6.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PWM2_16BIT_H
#define PWM2_16BIT_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initializes the PWM2_16BIT module
 *        This routine must be called before any other PWM2_16BIT routine
 * @return None.
 * @param None.
 */
void PWM2_16BIT_Initialize(void);

/**
 * @brief Enables the PWM2_16BIT module
 * @return None.
 * @param None.
 */
void PWM2_16BIT_Enable();

/**
 * @brief Disables the PWM2_16BIT module
 *        In case if one wants to re-initialize PWM2_16BIT, this function
 *        must be called before PWM2_16BIT_Initialize()
 * @return None.
 * @param None.
 */
void PWM2_16BIT_Disable();

/**
 * @brief This routine configures the total PWM2_16BIT period. 
 *        PWM2_16BIT_LoadBufferRegisters() must be called after this API
 * @return None.
 * @param [in] Desired 16-bit PWM2_16BIT period
 * @example void main(void)
 *          {
 *              SYSTEM_Initialize();
 *              
 *              // Change the PWM period
 *              PWM2_16BIT_WritePeriodRegister(0x00FF);
 *              PWM2_16BIT_LoadBufferRegisters();
 *
 *          }
 */
void PWM2_16BIT_WritePeriodRegister(uint16_t periodCount);

/**
 * @brief This routine configures the active period or duty cycle of
 *        slice-1, parameter 1 output. PWM2_16BIT_LoadBufferRegisters() must
 *        be called after this API
 * @return None.
 * @param [in] PWM2S1P1 register value
 * @example void main(void)
 *          {
 *              SYSTEM_Initialize();
 *
 *              // Change the slice-1, parameter-1 output duty cycle
 *              PWM2_16BIT_SetSlice1Output1DutyCycleRegister(0x55);  //33% duty cycle
 *              PWM2_16BIT_LoadBufferRegisters();
 *
 *          }
 */
void PWM2_16BIT_SetSlice1Output1DutyCycleRegister(uint16_t value);

/**
 * @brief This routine configures the active period or duty cycle of
 *        slice-1, parameter 2 output. PWM2_16BIT_LoadBufferRegisters() must
 *        be called after this API
 * @param [in] PWM2S1P2 register value
 * @example void main(void)
 *          {
 *              SYSTEM_Initialize();
 *
 *              // Change the slice-1, parameter-2 output duty cycle
 *              PWM2_16BIT_SetSlice1Output2DutyCycleRegister(0xAA);   //66% duty cycle
 *              PWM2_16BIT_LoadBufferRegisters();
 *
 *          }
 */
void PWM2_16BIT_SetSlice1Output2DutyCycleRegister(uint16_t value);

/**
 * @brief This routine is used to load period or duty cycle registers on the next period event
 *        This API must be called after changing PR/P1/P2 registers
 * @return None
 * @param None
 * @example void main(void)
 *          {
 *              SYSTEM_Initialize();
 *
 *              // Change the slice-1, parameter-2 output duty cycle
 *              PWM2_16BIT_SetSlice1Output2DutyCycleRegister(0xAA);   //66% duty cycle
 *              PWM2_16BIT_LoadBufferRegisters();
 *
 *          }
 */
void PWM2_16BIT_LoadBufferRegisters(void);

/**
 * @brief Interrupt handler for PWM2_16BIT outputs
 * @return None
 * @param None
 */
void PWM2_16BIT_PWMI_ISR(void);

/**
 * @brief Interrupt handler for PWM2_16BIT period
 * @return None
 * @param None
 */
void PWM2_16BIT_PWMPI_ISR(void);

/**
 * @brief Setter for slice 1, parameter 1 out interrupt handler
 * @return None
 * @param None
 * @example 
 *          void Slice1Output1_CustomInterruptHandler(void)
 *          {
 *              //Custom interrupt handler code
 *          }
 *
 *          void main(void)
 *          {
 *              SYSTEM_Initialize();
 *              
 *              //Use custom handler for Slice1Output1 interrupt
 *              PWM2_16BIT_Slice1Output1_SetInterruptHandler(Slice1Output1_CustomInterruptHandler);
 *          }
 */
void PWM2_16BIT_Slice1Output1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @brief Setter for slice 1, parameter 2 out interrupt handler
 * @return None
 * @param None
 * @example 
 *          void Slice1Output2_CustomInterruptHandler(void)
 *          {
 *              //Custom interrupt handler code
 *          }
 *
 *          void main(void)
 *          {
 *              SYSTEM_Initialize();
 *              
 *              //Use custom handler for Slice1Output2 interrupt
 *              PWM2_16BIT_Slice1Output2_SetInterruptHandler(Slice1Output2_CustomInterruptHandler);
 *          }
 */
void PWM2_16BIT_Slice1Output2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @brief Setter for PWM2_16BIT period interrupt handler
 * @return None
 * @param None
 * @example 
 *          void Period_CustomInterruptHandler(void)
 *          {
 *              //Custom interrupt handler code
 *          }
 *
 *          void main(void)
 *          {
 *              SYSTEM_Initialize();
 *              
 *              //Use custom handler for period interrupt
 *              PWM2_16BIT_Period_SetInterruptHandler(Period_CustomInterruptHandler);
 *          }
 */
void PWM2_16BIT_Period_SetInterruptHandler(void (* InterruptHandler)(void));

#endif //PWM2_16BIT_H
