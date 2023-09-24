# Hardware Features

Generally decoder hardware is rated on:

- Form factor.
- Continuous peak current
  - To the motor
  - To one function
  - To motor plus all functions together.
- Total number of functions.
- Pre-installed LEDs (e.g. headlight, taillight)

## Function Outputs

Function outputs are driven by a MOSFET to allow for high current (100ma)
function outputs at track voltage.

## BackEMF Capable

The hardware enables the microcontroller to measure the BackEMF of the
motor in software.

## Analog Mode

Allows the decoder to operate a DC layout by measuring the track voltage.
