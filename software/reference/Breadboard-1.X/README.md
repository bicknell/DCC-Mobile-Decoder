# Breadboard-1 Software

Written in MPLAB X IDE v6.00 using MCC Classic v5.1.17.  Designed to work
with the Breadboard-1 reference implementation hardware.

## Resource Management

Add the following Peripherals in the Resource Management window:

- ADCC - Used to take analog measurements for BackEMF
- CWG1 - Used to generate waveforms for the H-Bridge.
- MEMORY - Used to access the EEPROM memory.
- PWM1_16BIT - Used to generate a PWM signal for the motor.
- TMR0 - Set to fire once a second for statistics.
- TMR2 - Set to fire 65us after being tripped to read the DCC signal.
- UART1 - A serial port output for debugging information.

## Project Properties

- Set our processor, PIC18F16Q40
- XC8 Compiler, Optimizations tab, enable Level 2 optimizations
- If desired, under PICKit4 check "Preserve EEROM Memory" to not clear 
  EEPROM on programming.

## MCC Classic

This project uses MCC Classic to configure the PIC18F chip.  The following is
a walk through of the critical settings.  

***Be sure to hit "Generate" after making any changes.***

### System Module

We want to run the chip at 64Mhz off it's internal oscillator:

- Select the HFINTOSC
- Select 64_Mhz
- Select a clock divider of 1.

### Interrupt Module

The defaults, all unchecked, is fine.

### Pin Grid View

In Pin Grid View, check the following:

- For the ADCC, Pin 2 / RA5 should be connected to ANx (input).
- For CWG1:
  - CWG1A pin 15 RC1
  - CWG1B pin 16 RC0
  - CWG1C pin 5  RC5
  - CWG1D pin 6  RC4
- For OSC, no connections.
- For PWM1_16BIT, none of these are used but MCC complains if they are not connected.
  - PWM1ERS is connected to pin 2 / RA5.
  - PWMIN0 is connected to pin 3 / RA4
  - PWMIN1 is connected to pin 3 / RA4
- Pin Module:
  - Input: pin 3 / RA4
  - Outputs: 19 / RA0, 18 / RA1, 17 / RA2, 13 / RB4, 11 / RB6, 14, RC2, 7 / RC3, 8 / RC6, 9 / RC7
- RESET: RA3
- TMR0: None checked.
- TMR2, T2IN set to pin 3 / RA4.
- UART1:
  - RX1: pin 12 / RB5
  - TX1: pin 10 / RB7

### Pin Module

Name the pins as follows:

- RA0: IO_F5 + Output
- RA1: IO_F6 + Output
- RA2: IO_F1 + Output
- RA3
- RA4: IO_DCC
- RA5: BackEMF + analog
- RB4: IO_F0F + Output
- RB5
- RB6: IO_Unused1 + Output
- RB7
- RC0
- RC1
- RC2: IO_F3 + Output
- RC3: IO_F2 + Output
- RC4
- RC5
- RC6: IO_F4 + Output
- RC7: IO_F0R + Output

### DMA Manager

No configuration

### ADCC 

TBD

### CWG1

Generates the wave form to drive the H-Bridge.

- Check "Enable CWG"
- Input source "PWM1_OUT1"
- Output mode "fwd Full Bridge Mode"
- Clock source "FOSC"

### Memory

- Check "Add DATAEE routines" for EEPROM access functions.

### PWM1_16BIT

Generates the PWM signal fed into CWG1 to control the motor speed.

- Check "Enable PWM"
- Clock selection "FOSC"
- Clock prescaler "1"
- Mode "Left aligned"
- Requested frequency "50khz"

### TMR0

Configured as a once a second timer for statistics.

- Check "Enable Timer"
- Clock prescaler "1:512"
- Clock source "LFINTOSC"
- Requested period "1s"

### TMR2

Triggers when the DCC port goes high, fires 60us later so we can try and read
a DCC bit.

- Check "Enable Timer"
- Control Mode "One shot"
- External reset source "T2INPPS pin"
- Clock source "HFINTOSC"
- Prescaler "1:32"
- Timer period "60us"
- Check "Enable Timer Interrupt"

### UART1 

Used for debugging.  We probably don't need receive, but we have the pin
so it's enabled.

- Check "Enable UART" baud rate "115200"
- Check "Enable transmit"
- Check "Enable receive"
- Check "Redirect stdio to UART"




