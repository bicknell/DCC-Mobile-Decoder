# Breadboard-1

## About

The Breadboard-1 design was created to make development of software as
simple as possible.  The design goals were:

* Fit a standard 400 or 830 tie point breadboard.
* Have a connector for a PICKIT 4 or similar ICSP programmer.
* Operate at a modest power level (generally similar to N sccale).
* Have an easy to understand schmatic, suitable for teaching.
* Have an easy to understand PCB, suitable for teaching.
* Use low cost components.

## Schematic Walkthrough

### Power Supply

Power from the two rails is fed into a bridge rectifier made up of four
discrete diodes D11-D14.  As DCC is a square wave, the output is nearly but not
quite continuous DC power with low ripple.  That power is split off
to drive the motor and functions directly, labeled as +12v (approximate
N scale voltage).  A linear regulator U11 is used to generate +5v for the
micro-processor, and has two support capacitors.

*SCALE SPECIFIC NOTES:* Larger scales will use higher voltages, up to 20v for
G scale.  D11-D14, C11, and U11 must be rated for at least 20% more than the
highest expected voltage.  Larger scales will also draw more current, up to 3A.
D11-D14 must be sized to handle the total current draw.

### Micro-controller

A PIC18F24K50-xML processor is used in this design.  PIC processors require minimal
support components.  C21 is a local bypass capacitor that is placed closed to
the power pins.  C22 and R11 form a hold up circuit for MCLR which must be kept 
high during normal operation.  If MCLR drops, the chip will reset.

The exact pins used for the various inputs and outputs are a factor of two criteria.
On some PIC processors particular peripherals can only be used on specific pins.
On all devices inputs and outputs are moved based on the physical layout of the
chip and shape of the circuit board to make routing easier.

### H-Bridge

The H-Bridge controls the current to the motor.  It is driven by a PWM signal generated
by the micro-controller.  The software generates 4 PWM signals, P1A-P1D, which are used
to control speed and direction.

The H-bridge is simply 4 high power MOSFETs arranged in an H configuration.  This design
uses two discrete dual MOSFET chips which is a common arrangement.  Resistors are placed
on the gate inputs to prevent inrush from damaging the micro-controller. Dodes D31-D24 
are placed across each MOSFET to disapate any reverse current.

In order to calculate BackEMF, a 100nf capacitor C31 is added to reduce signal noise.  The
resistors R33 and R34 then reduce the voltage to an appropriate level for the analog 
input of the micro-controller.  By monitoring this voltage the micro-controller can
calculate the load.

### Functions

This design supports functions F0-F6.

Functions F0F (front headlight) and F0R (rear headlight) are driven directly by the PIC.
In most designs these are fixed lights on the circuit board, so the exact current draw is
known in advance.  The resistors are sized to limit the LEDs to approximately 5ma at 5v.

Functions F1-F6 are designed to be connected to external device in a "common anode"
confuration.  To ease development this particular design provides both an LED and a 
connection for an external device.

+12v power is provided as a common anode source.  The MOSFET connects to ground when turned
on by the micro-processor.  A resistor is provided on the gate of each MOSFET to manage
inrush current.  In most mobile decoders the resistor and diode combination for an indicator
light would be omitted.

### External Connectivity

Two 6-pin 0.1" (2.54mm) pin headers are provided for connectivity to a standard bread board.
The board has been physically designed to connect to the top of a bread board in positions
1-6 across the middle.  

At the top of the board J3 provides a 5 pin ICSP header.  It's physical layout has been
designed so that a PICKIT4 programmer can be plugged in directly and will be face up at
the top of the board.


