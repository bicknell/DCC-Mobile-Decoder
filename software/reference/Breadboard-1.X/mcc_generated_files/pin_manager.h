/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F16Q40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_F1 aliases
#define IO_F1_TRIS                 TRISAbits.TRISA0
#define IO_F1_LAT                  LATAbits.LATA0
#define IO_F1_PORT                 PORTAbits.RA0
#define IO_F1_WPU                  WPUAbits.WPUA0
#define IO_F1_OD                   ODCONAbits.ODCA0
#define IO_F1_ANS                  ANSELAbits.ANSELA0
#define IO_F1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IO_F1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IO_F1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define IO_F1_GetValue()           PORTAbits.RA0
#define IO_F1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IO_F1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define IO_F1_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define IO_F1_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define IO_F1_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define IO_F1_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define IO_F1_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define IO_F1_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set IO_F2 aliases
#define IO_F2_TRIS                 TRISAbits.TRISA1
#define IO_F2_LAT                  LATAbits.LATA1
#define IO_F2_PORT                 PORTAbits.RA1
#define IO_F2_WPU                  WPUAbits.WPUA1
#define IO_F2_OD                   ODCONAbits.ODCA1
#define IO_F2_ANS                  ANSELAbits.ANSELA1
#define IO_F2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define IO_F2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define IO_F2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define IO_F2_GetValue()           PORTAbits.RA1
#define IO_F2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define IO_F2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define IO_F2_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define IO_F2_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define IO_F2_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define IO_F2_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define IO_F2_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define IO_F2_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set IO_F3 aliases
#define IO_F3_TRIS                 TRISAbits.TRISA2
#define IO_F3_LAT                  LATAbits.LATA2
#define IO_F3_PORT                 PORTAbits.RA2
#define IO_F3_WPU                  WPUAbits.WPUA2
#define IO_F3_OD                   ODCONAbits.ODCA2
#define IO_F3_ANS                  ANSELAbits.ANSELA2
#define IO_F3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IO_F3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IO_F3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define IO_F3_GetValue()           PORTAbits.RA2
#define IO_F3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IO_F3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define IO_F3_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define IO_F3_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define IO_F3_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define IO_F3_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define IO_F3_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define IO_F3_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set IO_DCC aliases
#define IO_DCC_TRIS                 TRISAbits.TRISA4
#define IO_DCC_LAT                  LATAbits.LATA4
#define IO_DCC_PORT                 PORTAbits.RA4
#define IO_DCC_WPU                  WPUAbits.WPUA4
#define IO_DCC_OD                   ODCONAbits.ODCA4
#define IO_DCC_ANS                  ANSELAbits.ANSELA4
#define IO_DCC_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define IO_DCC_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define IO_DCC_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define IO_DCC_GetValue()           PORTAbits.RA4
#define IO_DCC_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define IO_DCC_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define IO_DCC_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define IO_DCC_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define IO_DCC_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define IO_DCC_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define IO_DCC_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define IO_DCC_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set IO_BACKEMF aliases
#define IO_BACKEMF_TRIS                 TRISAbits.TRISA5
#define IO_BACKEMF_LAT                  LATAbits.LATA5
#define IO_BACKEMF_PORT                 PORTAbits.RA5
#define IO_BACKEMF_WPU                  WPUAbits.WPUA5
#define IO_BACKEMF_OD                   ODCONAbits.ODCA5
#define IO_BACKEMF_ANS                  ANSELAbits.ANSELA5
#define IO_BACKEMF_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define IO_BACKEMF_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define IO_BACKEMF_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define IO_BACKEMF_GetValue()           PORTAbits.RA5
#define IO_BACKEMF_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_BACKEMF_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define IO_BACKEMF_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define IO_BACKEMF_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define IO_BACKEMF_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define IO_BACKEMF_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define IO_BACKEMF_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define IO_BACKEMF_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set IO_F0R aliases
#define IO_F0R_TRIS                 TRISBbits.TRISB4
#define IO_F0R_LAT                  LATBbits.LATB4
#define IO_F0R_PORT                 PORTBbits.RB4
#define IO_F0R_WPU                  WPUBbits.WPUB4
#define IO_F0R_OD                   ODCONBbits.ODCB4
#define IO_F0R_ANS                  ANSELBbits.ANSELB4
#define IO_F0R_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_F0R_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_F0R_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_F0R_GetValue()           PORTBbits.RB4
#define IO_F0R_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_F0R_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_F0R_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_F0R_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_F0R_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_F0R_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_F0R_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define IO_F0R_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSELB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set IO_F0F aliases
#define IO_F0F_TRIS                 TRISBbits.TRISB6
#define IO_F0F_LAT                  LATBbits.LATB6
#define IO_F0F_PORT                 PORTBbits.RB6
#define IO_F0F_WPU                  WPUBbits.WPUB6
#define IO_F0F_OD                   ODCONBbits.ODCB6
#define IO_F0F_ANS                  ANSELBbits.ANSELB6
#define IO_F0F_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define IO_F0F_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define IO_F0F_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define IO_F0F_GetValue()           PORTBbits.RB6
#define IO_F0F_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define IO_F0F_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define IO_F0F_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define IO_F0F_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define IO_F0F_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define IO_F0F_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define IO_F0F_SetAnalogMode()      do { ANSELBbits.ANSELB6 = 1; } while(0)
#define IO_F0F_SetDigitalMode()     do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSELB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set IO_F4 aliases
#define IO_F4_TRIS                 TRISCbits.TRISC0
#define IO_F4_LAT                  LATCbits.LATC0
#define IO_F4_PORT                 PORTCbits.RC0
#define IO_F4_WPU                  WPUCbits.WPUC0
#define IO_F4_OD                   ODCONCbits.ODCC0
#define IO_F4_ANS                  ANSELCbits.ANSELC0
#define IO_F4_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_F4_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_F4_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_F4_GetValue()           PORTCbits.RC0
#define IO_F4_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_F4_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define IO_F4_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_F4_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_F4_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_F4_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_F4_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define IO_F4_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set IO_F5 aliases
#define IO_F5_TRIS                 TRISCbits.TRISC1
#define IO_F5_LAT                  LATCbits.LATC1
#define IO_F5_PORT                 PORTCbits.RC1
#define IO_F5_WPU                  WPUCbits.WPUC1
#define IO_F5_OD                   ODCONCbits.ODCC1
#define IO_F5_ANS                  ANSELCbits.ANSELC1
#define IO_F5_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define IO_F5_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define IO_F5_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define IO_F5_GetValue()           PORTCbits.RC1
#define IO_F5_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define IO_F5_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define IO_F5_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define IO_F5_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define IO_F5_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define IO_F5_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define IO_F5_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define IO_F5_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set IO_F6 aliases
#define IO_F6_TRIS                 TRISCbits.TRISC2
#define IO_F6_LAT                  LATCbits.LATC2
#define IO_F6_PORT                 PORTCbits.RC2
#define IO_F6_WPU                  WPUCbits.WPUC2
#define IO_F6_OD                   ODCONCbits.ODCC2
#define IO_F6_ANS                  ANSELCbits.ANSELC2
#define IO_F6_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_F6_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_F6_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_F6_GetValue()           PORTCbits.RC2
#define IO_F6_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_F6_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_F6_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_F6_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_F6_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_F6_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_F6_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define IO_F6_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/