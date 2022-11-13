# Breadborad-1 Calculations

## Power Supply

- **DATASHEET:** C11 & C12 10uF capacitors are the data sheet recommendation for an AMS1117-5.0
- **PROJECT:** D11-D14 & C11 must be rated for >= 30V.
- **PROJECT:** D11-D14 must be rated for >= 1A.

## Micro-controller

- **DATASHEET** *Figure 2-1 Recommended Minimum Connections
  - C21 100nF 20V input power decoupling on pins 16/17
  - C22 100nF 20V Vref+ power decoupling on pin 2 / RA3 for analog comparator.
  - R23 10K / C23 100 nF 20V MCLR hold up circuit.
  - Note that the QFN28 package chosen for this project has only a single Vdd/Vss pin pair,
    so only C21 is needed for decoupling.
- R21 & R22 form a voltage divider to bring the DCC signal in range of the micro-controller: (Note same as BackEMF below)
  - **PROJECT:** Vdrive max = 30v
  - **PROJECT:** Vdrive min = 6v
  - **DATASHEET:** *Parameter D001:* Vdd = 5v
  - **DATASHEET:** *Parameter D141:* Input Low Voltage I/O Port Schmitt Trigger Buffer Max 0.2 * Vdd = 1v
  - **CALCULATE:** Voltage divider equation: 5 = (30 * R2) / (R1 + R2)
    - Select R2 = 1.33K (Value needed for diagnostic LEDs)
    - Result: R1 = 6.65K which is an E96 resistor value.
    - Check minimum voltage: (6 * 1330) / (6650 + 1330) = 1v
  - **CALCULATE:** Imax = 30v / ((6650 + 1330) = 3.75ma @ 30V = .112 watts
    - 1/8 Watt resistors are sufficient.

## H-Bridge

- Q31-Q32 MOSFETs
  - **PROJECT:** Vgs must be < 5V, as the micro-controller only sources 5v.
  - **PROJECT:** Vds must be >= 30V.
  - **PROJECT:** Id must be >= 1A.
  - R31-R34 Gate resistors limit inrush current:
    - **PROJECT:** Micro-controller runs at 5v.
    - **DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sunk per pin
    - **DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sourced per pin
    - **DATASHEET** *29.1 Absolute Maximum Ratings* 110ma max sunk all ports
    - **DATASHEET** *29.1 Absolute Maximum Ratings* 70ma max sourced all ports
    - **CALCULATE:** R = 5v / 0.025ma = 200 Ohm
      - E48 & E96 standard value of 202 Ohm
      - 220 Ohm is a popular value that may be cheaper.
- **PROJECT:** D31-D33 Snubbing Diodes must be rated for >= 30V.
- R35 & R36 BackEMF sense resistors must put max voltage in the 0-5V range of the
  micro-controller: (Note Same as DCC Dividers Above)
  - **PROJECT:** Vdrive max = 30v
  - **PROJECT:** Vdrive min = 6v
  - **DATASHEET:** *Parameter D001:* Vdd = 5v
  - **DATASHEET:** *Parameter D141:* Input Low Voltage I/O Port Schmitt Trigger Buffer Max 0.2 * Vdd = 1v
  - **CALCULATE:** Voltage divider equation: 5 = (30 * R2) / (R1 + R2)
    - Select R2 = 1.33K (Value needed for diagnostic LEDs)
    - Result: R1 = 6.65K which is an E96 resistor value.
    - Check minimum voltage: (6 * 1330) / (6650 + 1330) = 1v
  - **CALCULATE:** Imax = 30v / ((6650 + 1330) = 3.75ma @ 30V = .112 watts
    - 1/8 Watt resistors are sufficient.
- C31 provides high frequency noise reduction, and is determined experimentally.

## Functions

### F0F/F0R Direct Drive LEDs

- The micro-processor source 5v
- **DATASHEET:** Vf of the LED is 2.9v
- Desired current is 5ma.
  - The PIC chip can source 20ma per pin, but we want to stay well under that as the LED is 
    more than bright enough at a lower current.
  - There is also a limit of 100ma chip-wide.
- R = (5 - 2.9) / 0.005 = 420 Ohms
  - 422 Ohms is a stanard E48 and E96 series resistor value.
    - 470 Ohms is an extremely common value that might be cheaper.
    - (5 - 2.9) / 470 = 4.4ma, which is acceptable

### F1-F6 Generic Output

- MOSFET
  - **PROJECT:** Vdd = 5v
  - **PROJECT:** Vdrive max = 30v
  - **PROJECT:** Function Max Current = 100ma
  - Vgs must be < 5V, as the micro-controller only sources 5v.
  - Vds must be >= 30V.
  - Id must be >= 100mA.
  - Gate resistors limit inrush current:
    - **DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sunk per pin
    - **DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sourced per pin
    - **DATASHEET** *29.1 Absolute Maximum Ratings* 110ma max sunk all ports
    - **DATASHEET** *29.1 Absolute Maximum Ratings* 70ma max sourced all ports
    - **CALCULATE:** R = 5v / 0.025ma = 200 Ohm
      - E48 & E96 standard value of 202 Ohm
      - 220 Ohm is a popular value that may be cheaper.

### Diagnostic LEDs

These are used to aid in development of software without external components, and would not
generally be present on mobile decoders.

- Function LEDs
  - **PROJECT:** Vdrive max is 30v
  - **PROJECT:** Vdrive min is 6v
  - **DATASHEET:** Vf is 2.9v
  - **DATASHEET:** Max current is 20ma
  - **CALCULATE:** R = (30 - 2.9) / 0.020 = 1360
  - **CALCULATE:** Min current @ min voltage: (6 - 2.9) / 1360 = 0.0022
    - LED should still light at 2.2ma
  - 1.33 KOhms is a standard E48 and E96 series resistor value.
- Motor Direction LED


