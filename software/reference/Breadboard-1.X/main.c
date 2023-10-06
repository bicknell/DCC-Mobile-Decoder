/*
 * This code is subject to the
 * 
 * Creative Commons Attribution-NonCommercial 4.0 International Public License
 * 
 * Please see https://github.com/bicknell/DCC-Mobile-Decoder/LICENSE for full
 * license terms.
 *
 */

/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F16Q40
        Driver Version    :  2.00
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

/* DESCRIPTION
 *
 * main program loop.
 * 
 * Calls any necessary initialization functions and then begins to forever
 * loop on decoding DCC packets.
 * 
 */

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "cv.h"
#include "dcc.h"
#include "debug.h"
#include "hardware.h"

/*
 *                       Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Call our initalization function in hardware.c to be sure the hardware
    // is configured correctly.
    hardware_initialize();

#if DEBUG_STATUS
    printf("\r\nCompiled on %s at %s using version %0d with flags 0x%04X.\r\n",
           __DATE__, __TIME__, __XC8_VERSION, __OPTIM_FLAGS);
    printf("STATUS = 0x%04x, PCON0 = 0x%04X, PCON1 = 0x%04X.\r\n",
            STATUS, PCON0, PCON1);
#endif
    
    // Make sure the EEPROM data has been configured.
    cv_check();
    
    // Initialize the DCC subsystem based on the CV's configured.
    dcc_initialize();
    
    // Turn on interrupts.
    INTERRUPT_GlobalInterruptEnable();
    
    // Start reading the DCC signal.
    TMR2_StartTimer(); 
        
    while (1)
    {
        // TMR0 is a once per 25ms heartbeat we use for status reporting.
        TMR0_Initialize();
        TMR0_StartTimer();
        
        // Loop until TMR0 goes off.
        while(!TMR0_HasOverflowOccured()) {
            // Did a DCC packet come in?
            if (dcc_ready) {
                dcc_decode();
                // Tell the ISR we've consumed the message and it can store another.
                dcc_ready = 0;
            } else {
                // Is there anything to do during idle time?
                dcc_idle();
            }
        }

        // Control reaches here when TMR0 has gone off.
        // Perform periodic functions every 25ms.
        dcc_periodic();
        function_periodic(); // Perform animations for functions.
    }
}
/**
 End of File
*/
