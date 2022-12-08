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

### MOSFET Driven

A MOSFET driven function allows for high current output on the function
driven by track voltage.

### Low Voltage Output

Function outputs 5v, rather than track voltage.  Generally this means
it is driven by the regulator on the board, rather than track voltage.
Typically limited in the amount of current available.

### Logic Level Output

Function outputs 3.3v or 5v logic, direct from the Micro-Controller.
Very limited current is available, and typically this is used only to
interface with additional logic level chips/devices.

### Servo Output

The ability to use multiple function outputs to drive a servo motor.

### "LED" Outputs

No resistor required when attaching LED light sources.  This is generally
an extension of Logic Level Outputs, with an additional resistor on board.

## General Features

### Analog Mode

Allows the decoder to operate a DC layout by measuring the track voltage.

### Capacitor / Energy Storage

Support for adding a large value capacitor for better performance.

## General Features

### Short Circuit protection

### Overload Protection

