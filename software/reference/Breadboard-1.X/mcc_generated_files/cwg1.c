/**
   CWG1 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     cwg1.c
 
   @Summary
     This is the generated driver implementation file for the CWG1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for CWG1.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
         Device            :  PIC18F16Q40
         Driver Version    :  2.11
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
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include "cwg1.h"

/**
  Section: CWG1 APIs
*/

void CWG1_Initialize(void)
{
    // Set the CWG1 to the options selected in PIC10 / PIC12 / PIC16 / PIC18 MCUs

	// CWG1POLA non inverted; CWG1POLC non inverted; CWG1POLB non inverted; CWG1POLD non inverted; 
	CWG1CON1 = 0x00;

	// CWG1DBR 9 to 10; 
	CWG1DBR = 0x09;

	// CWG1DBF 9 to 10; 
	CWG1DBF = 0x09;

	// SHUTDOWN No Auto-shutdown; REN disabled; CWG1LSBD tri-stated; CWG1LSAC tri-stated; 
	CWG1AS0 = 0x14;

	// AS1E disabled; AS0E disabled; AS3E disabled; AS2E disabled; AS5E disabled; AS4E disabled; AS6E disabled; 
	CWG1AS1 = 0x00;

	// CWG1CS FOSC; 
	CWG1CLKCON = 0x00;

	// CWG1STRD disabled; CWG1STRB disabled; CWG1STRC disabled; CWG1STRA disabled; CWG1OVRD low; CWG1OVRA low; CWG1OVRB low; CWG1OVRC low; 
	CWG1STR = 0x00;

	// CWG1ISM PWM1_OUT1; 
	CWG1ISM = 0x02;

	// CWG1LD Buffer_not_loaded; CWG1EN enabled; CWG1MODE Fwd Full bridge mode; 
	CWG1CON0 = 0x82;

}

void CWG1_LoadRiseDeadbandCount(uint8_t dutyValue)
{
    CWG1DBR = dutyValue;
}

void CWG1_LoadFallDeadbandCount(uint8_t dutyValue)
{
    CWG1DBF = dutyValue;
}

void CWG1_LoadBufferEnable(void)
{
    CWG1CON0bits.CWG1LD = 1;
}

bool CWG1_IsModuleEnabled()
{
    return (CWG1CON0bits.CWG1EN);
}

void CWG1_AutoShutdownEventSet()
{
    CWG1AS0bits.SHUTDOWN = 1;
}

void CWG1_AutoShutdownEventClear()
{
    CWG1AS0bits.SHUTDOWN = 0;
}


/**
 End of File
*/