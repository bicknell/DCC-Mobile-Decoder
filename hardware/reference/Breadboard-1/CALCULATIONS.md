# Breadborad-1 Calculations

## Power Supply

- C11 & C12 10uF capacitors are the data sheet recommendation for an AMS1117-5.0
- D11-D14 & C11 must be rated for >= 30V.
- D11-D14 must be rated for >= 1A.

## Micro-controller

- 100nF is the data sheet recommendation for a decoupling capacitor.
- 1uF & 10K are common values used for MCLR hold up, the exact values are not 
  critical.  This pin must not drop low while in operation, and must be able to
  be pulled low and high by the programmer.

## H-Bridge

- Q31-Q32 MOSFETs
  - Vgs must be < 5V, as the micro-controller only sources 5v.
  - Vds must be >= 30V.
  - Id must be >= 1A.
  - R31-R34 Gate resistors limit inrush current:
    - 5v from micro-controller.
    - 20ma max per pin on micro-controller.
    - R = 5 / 0.020 = 250 Ohms
- D31-D33 Snubbing Diodes must be rated for >= 30V.
- R35 & R36 BackEMF sense resistors must put max voltage in the 0-5V range of the
  micro-controller:
  - Vin = 30v
  - Vout = 5v
  - Voltage divider equation: 5 = (30 * R2) / (R1 + R2)
    - Plug in 1K for R2 and solve, giving 5K for R1.
    - Check minimum voltage: (6 * 1000) / (5000 + 1000) = 1V
- C31 provides high frequency noise reduction, and is determined experimentally.

## Functions

### F0F/F0R Direct Drive LEDs

- The micro-processor source 5ma
- Vf is 2.9v
- Desired current is 5ma.
  - The PIC chip can source 20ma per pin, but we want to stay well under that as the LED is 
    more than bright enough at a lower current.
  - There is also a limit of 100ma chip-wide.
- R = (5 - 2.9) / 0.005 = 420 Ohms
  - 422 Ohms is a stanard E48 and E96 series resistor value.

### F1-F6 Generic Output

- MOSFET
  - Vgs must be < 5V, as the micro-controller only sources 5v.
  - Vds must be >= 30V.
  - Id must be >= 100mA.
  - Gate resistors limit inrush current:
    - 5v from micro-controller.
    - 20ma max per pin on micro-controller.
    - R = 5 / 0.020 = 250 Ohms
- Indicator LEDs
  - Vf is 2.9v
  - Max current is 20ma at max voltage.
    - R = (30 - 2.9) / 0.020 = 1360
  - Min current is 2ma at min voltage
    - (6 - 2.9) / 1360 = 0.0022
  - 1330 KOhms is a standard E48 and E96 series resistor value.


