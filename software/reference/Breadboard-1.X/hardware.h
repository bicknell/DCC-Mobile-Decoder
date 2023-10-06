/* 
 * File:   hardware.h
 * Author: bicknell
 * 
 * Contains mapping to a specific hardware layout.
 *
 * This code is subject to the
 * 
 * Creative Commons Attribution-NonCommercial 4.0 International Public License
 * 
 * Please see https://github.com/bicknell/DCC-Mobile-Decoder/LICENSE for full
 * license terms.
 * 
 * Created on October 5, 2023, 7:11 AM
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
#include "functions.h"    
/*
 * In MCC, the following pin names should be used.  If a particular
 * function is not used the code will automatically adjust.  Unused
 * pins should be set to output and will be driven low by the code.
 * 
 * IO_F0F               Output digital pin controlling the F0F function.
 * IO_F0R               Output digital pin controlling the F0R function.
 * IO_F1                Output digital pin controlling the F1 function.
 * IO_F2                Output digital pin controlling the F2 function.
 * IO_F3                Output digital pin controlling the F3 function.
 * IO_F4                Output digital pin controlling the F4 function.
 * IO_F5                Output digital pin controlling the F5 function.
 * IO_F6                Output digital pin controlling the F6 function.
 * IO_DCC               Input  digital pin with the DCC signal, weak pull up enabled.
 * IO_BACKEMF           Input  analog  pin with the BackEMF voltage, and set to the ADCC.
 * IO_UNUSED1           Output digital pin that is not used.
 * IO_UNUSED2           Output digital pin that is not used.
 * IO_UNUSED3           Output digital pin that is not used.
 * IO_UNUSED4           Output digital pin that is not used.
 * IO_UNUSED5           Output digital pin that is not used.
 * IO_UNUSED6           Output digital pin that is not used.
 * IO_UNUSED7           Output digital pin that is not used.
 * IO_UNUSED8           Output digital pin that is not used.
 * IO_UNUSED9           Output digital pin that is not used.
 * 
 * Additionally the following peripheral pins should be assigned.
 * 
 * ADCC                 Analog to Digital Converter with Computation used to
 *                      measure BackEMF.
 * ADCC ADACT           No pin assigned.
 * ADCC ADGRDA          No pin assigned.
 * ADCC ADGRDB          No pin assigned.
 * ADCC ANx             Input  analog  pin should be enabled on the BackEMF pin.
 *                      Configure ANx mapping below.
 * CWG1                 Complementary Waveform Generator used to generate H-Bridge
 *                      drive signals.
 * CWG1A                Output digital pin for high side left side of H-Bridge.
 * CWG1B                Output digital pin for high side left side of H-Bridge.
 * CWG1C                Output digital pin for high side left side of H-Bridge.
 * CWG1D                Output digital pin for high side left side of H-Bridge.
 * OSC                  Oscillator configuration.
 * OSC CLKOUT           No pin assigned.
 * PWM1_16BIT           PWM Generator connected to CWG1 for H-Bridge drive.
 * PWM1_16BIT PWM11     No pin assigned.
 * PWM1_16BIT PWM12     No pin assigned.
 * PWM1_16BIT PWMIN0    Not used but must be assigned. Assign to IO_DCC input pin.
 * PWM1_16BIT PWMIN1    Not used but must be assigned. Assign to IO_DCC input pin.
 * RESET MCLR           Pin is dedicated to the MCLR function.
 * TMR2                 A ~70us timer triggered by the DCC signal that interrupts
 *                      the program to measure a DCC bit.
 * TMR2 T2IN            Input  digital pin with the DCC signal.  Set to the same
 *                      pin as IO_DCC.  Set interrupt on change to positive 
 *                      (non-inverted DCC signal) or negative (inverted DCC signal).
 * UART1                Used for debugging purposes.
 * UART1 RX1            Input  digital pin for receiving RS-232 data.  Optional.
 * UART1 TX1            Output digital pin for transmitting RS-232 data.
 * UART1 CTS            No pin assigned.
 * UART1 DTS            No pin assigned.
 * UART1 TXDE1          No pin assigned.
 * 
 */


/*
 * All decoders must implement F0F/F0R.
 * All decoders must have a DCC input.
 * All decoders must have a BackEMF input.
 */
#ifndef IO_F0F_PORT
#error IO_F0F must be configured in the pin manager.
#endif
#ifndef IO_F0R_PORT
#error IO_F0R must be configured in the pin manager.
#endif
#ifndef IO_DCC_PORT
#warning IO_DCC must be configured in the pin manager.
#endif
#ifndef IO_BACKEMF_PORT
#warning IO_BACKEMF must be configured in the pin manager.
#endif
    
/*
 * If the hardware does not support additional functions
 * create dummy statements that do nothing.
 */
#ifndef IO_F1_PORT
#define IO_F1_SetHigh() void(0)
#define IO_F1_SetLow()  void(0)
#endif
#ifndef IO_F2_PORT
#define IO_F2_SetHigh() void(0)
#define IO_F2_SetLow()  void(0)
#endif
#ifndef IO_F3_PORT
#define IO_F3_SetHigh() void(0)
#define IO_F3_SetLow()  void(0)
#endif
#ifndef IO_F4_PORT
#define IO_F4_SetHigh() void(0)
#define IO_F4_SetLow()  void(0)
#endif
#ifndef IO_F5_PORT
#define IO_F5_SetHigh() void(0)
#define IO_F5_SetLow()  void(0)
#endif
#ifndef IO_F6_PORT
#define IO_F6_SetHigh() void(0)
#define IO_F6_SetLow()  void(0)
#endif

/*
 * Global variables
 * 
 * WARNING: void * function pointers seem to allocate zero space and not work,
 * which is why these return int.
 */
    int (*hardware_outputs[FUNCTION_MAX])(int);
/*
 * Prototypes
 */
void hardware_initialize(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* HARDWARE_H */

