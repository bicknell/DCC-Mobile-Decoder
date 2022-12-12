/**
   CWG1 Generated Driver API Header File
 
   @Company
     Microchip Technology Inc. 

   @File Name
    cwg1.h

   @Summary
     This is the generated header file for the CWG1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This header file provides APIs for driver for CWG1.
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

#ifndef CWG1_H
 #define CWG1_H
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>



#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: CWG1 APIs
*/

/**
  @Summary
    Initializes the CWG1

  @Description
    This routine configures the CWG1 specific control registers

  @Preconditions
    None

  @Returns
    None

  @Param
    None

  @Comment
    

  @Example
    <code>
    CWG1_Initialize();
    </code>
*/
void CWG1_Initialize(void);

/**
  @Summary
    This function would write the rising dead band count into CWG1DBR registers

  @Description
    This function can be used to modify rising dead band count of CWG on the fly

    When module is disabled, the CWG1DBR register is loaded immediately when
    CWG1DBR is written. When module is enabled, then software must set the
    CWG1CON0<LD> bit, and the buffer will be loaded at the next falling edge of
    the CWG input signal.

  @Preconditions
    CWG1_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    value - 6 bit digital rising dead band count to CWG.

  @Example
    <code>
    uint8_t myDutyValue;

    CWG1_Initialize();

    // do something

    CWG1_LoadRiseDeadbandCount(myDutyValue);

    if(CWG1_IsModuleEnabled())
    { // yes
        CWG1_LoadBufferEnable();
    }
    </code>
*/
void CWG1_LoadRiseDeadbandCount(uint8_t dutyValue);

/**
  @Summary
    This function would write the falling dead band count into CWG1DBF registers

  @Description
    This function can be used to modify falling dead band count of CWG on the fly

    When module is disabled, the CWG1DBF register is loaded immediately when
    CWG1DBF is written. When module is enabled, then software must set the
    CWG1CON0<LD> bit, and the buffer will be loaded at the rising edge of CWG
    input signal after the next falling edge (that is, after the falling-edge update.

  @Preconditions
    CWG1_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    value - 6 bit digital falling dead band count to CWG.

  @Example
    <code>
    uint8_t myDutyValue;

    CWG1_Initialize();

    // do something

    CWG1_LoadFallDeadbandCount(myDutyValue);

    if(CWG1_IsModuleEnabled())
    { // yes
        CWG1_LoadBufferEnable();
    }
    </code>
*/
void CWG1_LoadFallDeadbandCount(uint8_t dutyValue);



/**
  @Summary
    This function sets the CWG1CON0<LD> bit

  @Description
    This function enables the CWG1 module to load the buffers on the next
	rising/falling event of the input signal.
	
	The CWG1CON0<LD> bit can only be set after EN = 1 and cannot be set in the same 
	instruction that EN is set.

  @Preconditions
    CWG1_Initialize() function should have been called and the EN bit
	has to be set before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    Refer CWG1_LoadFallDeadbandCount() example.
    </code>
*/
void CWG1_LoadBufferEnable(void);

/**
  @Summary
    Returns CWG1 module enable status

  @Description
    Returns the status of whether the CWG1 module is enabled or not

  @Preconditions
    None

  @Returns
    Returns CWG1 module enable status

  @Param
    None

  @Example
    <code>
    Refer CWG1_LoadFallDeadbandCount() example.
    </code>
*/
bool CWG1_IsModuleEnabled(void);

/**
  @Summary
    Software generated Shutdown event

  @Description
    This function forces the CWG into Shutdown state.

  @Preconditions
    CWG1_Initialize() function should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    CWG1_Initialize();
    
    // do something
    
    CWG1_AutoShutdownEventSet();
    </code>
*/
void CWG1_AutoShutdownEventSet();

/**
  @Summary
    This function makes the CWG to resume its operations from the software
    generated shutdown state.

  @Description
    When auto-restart is disabled, the shutdown state will persist as long as the
    CWG1AS0<SHUTDOWN> bit is set and hence to resume operations, this function should be used.

    However when auto-restart is enabled, the CWG1AS0<SHUTDOWN> bit will be cleared automatically
    and resume operation on the next rising edge event. In that case, there is no
    need to call this function.

  @Preconditions
    CWG1_Initialize() and CWG1_AutoShutdownEventSet() functions should have been called before calling this function

  @Returns
    None

  @Param
    None

  @Example
    <code>
    CWG1_Initialize();
    
    // Do something
    
    CWG1_AutoShutdownEventSet();

    // Do something
    
    CWG1_AutoShutdownEventClear();
    </code>
*/
void CWG1_AutoShutdownEventClear();


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // CWG1_H
/**
 End of File
*/