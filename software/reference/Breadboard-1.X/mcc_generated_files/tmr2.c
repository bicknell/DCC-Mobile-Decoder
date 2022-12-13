/**
  TMR2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr2.c

  @Summary
    This is the generated driver implementation file for the TMR2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR2.
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr2.h"

/**
  Section: Global Variables Definitions
*/

void (*TMR2_InterruptHandler)(void);

/**
  Section: TMR2 APIs
*/

void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

    // T2CS HFINTOSC; 
    T2CLKCON = 0x03;

    // T2PSYNC Not Synchronized; T2MODE Starts at first rising TMR2_ers; T2CKPOL Rising Edge; T2CKSYNC Not Synchronized; 
    T2HLT = 0x0C;

    // T2RSEL T2INPPS pin; 
    T2RST = 0x00;

    // PR2 159; 
    T2PR = 0x9F;

    // TMR2 0; 
    T2TMR = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR3bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE3bits.TMR2IE = 1;

    // Set Default Interrupt Handler
    TMR2_SetInterruptHandler(TMR2_DefaultInterruptHandler);

    // T2CKPS 1:32; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0xD0;
}

void TMR2_ModeSet(TMR2_HLT_MODE mode)
{
   // Configure different types HLT mode
    T2HLTbits.MODE = mode;
}

void TMR2_ExtResetSourceSet(TMR2_HLT_EXT_RESET_SOURCE reset)
{
    //Configure different types of HLT external reset source
    T2RSTbits.RSEL = reset;
}

void TMR2_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

void TMR2_StartTimer(void)
{
    TMR2_Start();
}

void TMR2_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

void TMR2_StopTimer(void)
{
    TMR2_Stop();
}

uint8_t TMR2_Counter8BitGet(void)
{
    uint8_t readVal;

    readVal = TMR2;

    return readVal;
}

uint8_t TMR2_ReadTimer(void)
{
    return TMR2_Counter8BitGet();
}

void TMR2_Counter8BitSet(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;
}

void TMR2_WriteTimer(uint8_t timerVal)
{
    TMR2_Counter8BitSet(timerVal);
}

void TMR2_Period8BitSet(uint8_t periodVal)
{
   PR2 = periodVal;
}

void TMR2_LoadPeriodRegister(uint8_t periodVal)
{
   TMR2_Period8BitSet(periodVal);
}

void TMR2_ISR(void)
{

    // clear the TMR2 interrupt flag
    PIR3bits.TMR2IF = 0;

    if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
    }
}


void TMR2_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR2_InterruptHandler = InterruptHandler;
}

void TMR2_DefaultInterruptHandler(void){
    // add your TMR2 interrupt custom code
    // or set custom function using TMR2_SetInterruptHandler()
}

/**
  End of File
*/