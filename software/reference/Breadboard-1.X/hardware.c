/* 
 * File:   hardware.c
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

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "dcc.h"
#include "debug.h"
#include "hardware.h"

int f0_output(int x) {
    /*
     * F0F / F0R are always direction dependent.
     */
    if (dcc_direction == DCC_FORWARD) {
        if (x) {
            IO_F0F_SetHigh();
        } else {
            IO_F0F_SetLow();
        }
        IO_F0R_SetLow();
    } else {
        if (x) {
            IO_F0R_SetHigh();
        } else {
            IO_F0R_SetLow();
        }
        IO_F0F_SetLow();
    }
    return 0;
}


int f1_output(int x) {
#ifdef IO_F1_PORT
    if (x) {
        IO_F1_SetHigh();
    } else {
        IO_F1_SetLow();
    }
#endif
    return 0;
}

int f2_output(int x) {
#ifdef IO_F2_PORT
    if (x) {
        IO_F2_SetHigh();
    } else {
        IO_F2_SetLow();
    }
#endif
    return 0;
}

int f3_output(int x) {
#ifdef IO_F3_PORT
    if (x) {
        IO_F3_SetHigh();
    } else {
        IO_F3_SetLow();
    }
#endif
    return 0;
}

int f4_output(int x) {
#ifdef IO_F4_PORT
    if (x) {
        IO_F4_SetHigh();
    } else {
        IO_F4_SetLow();
    }
#endif
    return 0;
}

int f5_output(int x) {
#ifdef IO_F5_PORT
    if (x) {
        IO_F5_SetHigh();
    } else {
        IO_F5_SetLow();
    }
#endif
    return 0;
}

int f6_output(int x) {
#ifdef IO_F6_PORT
    if (x) {
        IO_F6_SetHigh();
    } else {
        IO_F6_SetLow();
    }
#endif
    return 0;
}

int dummy_output(int x) {
    return 0;
}

void hardware_initialize(void) {

/*
 * Set all functions to off.
 */
    IO_F0F_SetLow();
    IO_F0R_SetLow();
    IO_F1_SetLow();
    IO_F2_SetLow();
    IO_F3_SetLow();
    IO_F4_SetLow();
    IO_F5_SetLow();
    IO_F6_SetLow();
    
/*
 * Unused pins are set to output and driven low per Microchip's 
 * recommended practices.
 */
#ifdef IO_UNUSED1
    IO_UNUSED1_SetLow();
#endif
#ifdef IO_UNUSED2
    IO_UNUSED2_SetLow();
#endif
#ifdef IO_UNUSED3
    IO_UNUSED3_SetLow();
#endif
#ifdef IO_UNUSED4
    IO_UNUSED4_SetLow();
#endif
#ifdef IO_UNUSED5
    IO_UNUSED5_SetLow();
#endif
#ifdef IO_UNUSED6
    IO_UNUSED6_SetLow();
#endif
#ifdef IO_UNUSED7
    IO_UNUSED7_SetLow();
#endif
#ifdef IO_UNUSED8
    IO_UNUSED8_SetLow();
#endif
#ifdef IO_UNUSED9
    IO_UNUSED9_SetLow();
#endif
        
    // TMR2 is hooked to the DCC input pin, and calls the ISR.
    TMR2_SetInterruptHandler(DCC_ISR);
    
    // Initialize output locations:
    for (int i = 0;i < FUNCTION_MAX;i++) {
        hardware_outputs[i] = dummy_output;
    }
    // TODO: Handle Function Mapping
    hardware_outputs[0] = f0_output;
    hardware_outputs[1] = f1_output;
    hardware_outputs[2] = f2_output;
    hardware_outputs[3] = f3_output;
    hardware_outputs[4] = f4_output;
    hardware_outputs[5] = f5_output;
    hardware_outputs[6] = f6_output;
}