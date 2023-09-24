# Breadborad-1 Calculations

## Data Sheets

- Micro-processor: [PIC18F06Q40](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC18F06-16Q40-Data-Sheet-40002216D.pdf)
- H-Bridge MOSFETS: [WSD3045DN](https://datasheet.lcsc.com/lcsc/1912111437_Winsok-Semicon-WSD3045DN_C377868.pdf)
  - DFN3.3x3.3-8-EP1, 1xPNP & 1xNPN, Vdss 30V, Id 18A, Vgs(th) 1.3v min 2.5v max
- Functions MOSFET: [2N7002KD](https://datasheet.lcsc.com/lcsc/2010151636_FUXINSEMI-2N7002KD_C880912.pdf)
  - SOT-363, 2xNPN, Vdss 60V, Rds(on) 5 Ohm, Id 340ma Vgs(th) 1v max 2.5v
- Linear Regulator: [LR8341A-T50](https://datasheet.lcsc.com/lcsc/2105241807_LR-LR8341A-T50_C2829466.pdf)
  - SO-23-3L 5.0V fixed 50V input, 120ma linear regulator
- Diodes: [MSK4010](https://datasheet.lcsc.com/lcsc/1912111437_Shikues-MSK4010_C345958.pdf)
  - SOD-523, 50V, 1A Schottky barrier rectifier diode.

## Power Supply

- **AMS1117 DATASHEET:** C11 & C12 10uF capacitors are the data sheet 
  recommendation for an AMS1117-5.0
  - C11 & C12 0805 50V 10uF X5R 10% are generally available.
- **PROJECT REQUIREMENT:** D11-D14 & C11 must be rated for >= 30V.
  - MSK4010 diodes are rated for 1A.
  - C11 & C12 0805 50V 10uF X5R 10% are generally available.
- **PROJECT REQUIREMENT:** D11-D14 must be rated for >= 1A.
  - MSK4010 diodes are rated for 1A.

## Micro-controller

- **PIC18F25K50 DATASHEET** *Figure 2-1 Recommended Minimum Connections*
  - C21 100nF 20V input power decoupling on pins 16/17
    - 0402 50V 100nF X7R 10% are generally available.
  - C22 100nF 20V Vref+ power decoupling on pin 2 / RA3 for analog comparator.
    - 0402 50V 100nF X7R 10% are generally available.
  - R23 10K / C23 100 nF 20V MCLR hold up circuit.
    - 0402 10K 1% 1/8W are generally available.
    - 0402 50V 100nF X7R 10% are generally available.
  - Note that the QFN28 package chosen for this project has only a single Vdd/Vss pin pair,
    so only C21 is needed for decoupling.
- R21 & R22 form a voltage divider to bring the DCC signal in range of the micro-controller: (Note same as BackEMF below)
  - **PROJECT REQUIREMENT:** Vdrive max = 30v
  - **PROJECT REQUIREMENT:** Vdrive min = 6v
  - **PIC18F25K50 DATASHEET:** *Parameter D001:* Vdd = 5v
  - **PIC18F25K50 DATASHEET:** *Parameter D141:* Input Low Voltage I/O Port Schmitt Trigger Buffer Max 0.2 * Vdd = 1v
  - **CALCULATE:** Voltage divider equation: 5 = (30 * R2) / (R1 + R2)
    - Select R2 = 1.33K (Value needed for diagnostic LEDs)
    - Result: R1 = 6.65K which is an E96 resistor value.
    - Check minimum voltage: (6 * 1330) / (6650 + 1330) = 1v
  - **CALCULATE:** Imax = 30v / ((6650 + 1330) = 3.75ma @ 30V = .112 watts
    - 1/8 Watt resistors are sufficient.
  - 0402 1.33K & 6.65K 1% 1/8W resistors are generally avalable.

## H-Bridge

- Q31-Q32 MOSFETs
  - **PROJECT REQUIREMENT:** Vgs must be < 5V, as the micro-controller only sources 5v.
    - HSM0903 is max 2.5v.
  - **PROJECT REQUIREMENT:** Vds must be >= 30V.
    - HSM0903 is 100V.
  - **PROJECT REQUIREMENT:** Id must be >= 1A.
    - HSM0903 is 3A.
  - R31-R34 Gate resistors limit inrush current:
    - **PROJECT REQUIREMENT:** Micro-controller runs at 5v.
    - **PIC18F25K50 DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sunk per pin
    - **PIC18F25K50 DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sourced per pin
    - **PIC18F25K50 DATASHEET** *29.1 Absolute Maximum Ratings* 110ma max sunk all ports
    - **PIC18F25K50 DATASHEET** *29.1 Absolute Maximum Ratings* 70ma max sourced all ports
    - **CALCULATE:** R = 5v / 0.025ma = 200 Ohm
      - E48 & E96 standard value of 202 Ohm
      - 220 Ohm is a popular value that may be cheaper.
    - 0402 220 1% 1/8W resistors are generally avalable.
- **PROJECT REQUIREMENT:** D31-D33 Snubbing Diodes must be rated for >= 30V.
- R35 & R36 BackEMF sense resistors must put max voltage in the 0-5V range of the
  micro-controller: (Note Same as DCC Dividers Above)
  - **PROJECT REQUIREMENT:** Vdrive max = 30v
  - **PROJECT REQUIREMENT:** Vdrive min = 6v
  - **PIC18F25K50 DATASHEET:** *Parameter D001:* Vdd = 5v
  - **PIC18F25K50 DATASHEET:** *Parameter D141:* Input Low Voltage I/O Port Schmitt Trigger Buffer Max 0.2 * Vdd = 1v
  - **CALCULATE:** Voltage divider equation: 5 = (30 * R2) / (R1 + R2)
    - Select R2 = 1.33K (Value needed for diagnostic LEDs)
    - Result: R1 = 6.65K which is an E96 resistor value.
    - Check minimum voltage: (6 * 1330) / (6650 + 1330) = 1v
  - **CALCULATE:** Imax = 30v / ((6650 + 1330) = 3.75ma @ 30V = .112 watts
    - 1/8 Watt resistors are sufficient.
  - 0402 1.33K & 6.65K 1% 1/8W resistors are generally avalable.
- C31 provides high frequency noise reduction, and is determined experimentally.

## Functions

### F0F/F0R Direct Drive LEDs

- The micro-processor source 5v
- **BZ-C0805-C2-E1 DATASHEET:** Vf of the LED is 2.9v
- Desired current is 5ma.
  - The PIC chip can source 20ma per pin, but we want to stay well under that as the LED is 
    more than bright enough at a lower current.
  - There is also a limit of 100ma chip-wide.
- R = (5 - 2.9) / 0.005 = 420 Ohms
  - 422 Ohms is a stanard E48 and E96 series resistor value.
    - 470 Ohms is an extremely common value that might be cheaper.
    - (5 - 2.9) / 470 = 4.4ma, which is acceptable
    - 0402 470 1% 1/8W resistors are generally available.

### F1-F6 Generic Output

- MOSFET
  - **PROJECT REQUIREMENT:** Vdd = 5v
  - **PROJECT REQUIREMENT:** Vdrive max = 30v
  - **PROJECT REQUIREMENT:** Function Max Current = 100ma
  - Vgs must be < 5V, as the micro-controller only sources 5v.
    - 2N7002KDW is max 2.5v.
  - Vds must be >= 30V.
    - 2N7002KDW is 60V.
  - Id must be >= 100mA.
    - 2N7002KDW is 300ma.
  - Gate resistors limit inrush current:
    - **PIC18F25K50 DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sunk per pin
    - **PIC18F25K50 DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sourced per pin
    - **PIC18F25K50 DATASHEET** *29.1 Absolute Maximum Ratings* 110ma max sunk all ports
    - **PIC18F25K50 DATASHEET** *29.1 Absolute Maximum Ratings* 70ma max sourced all ports
    - **CALCULATE:** R = 5v / 0.025ma = 200 Ohm
      - E48 & E96 standard value of 202 Ohm
      - 220 Ohm is a popular value that may be cheaper.
    - 0402 220 1% 1/8W resistors are generally available.

### Diagnostic LEDs

These are used to aid in development of software without external components, and would not
generally be present on mobile decoders.

- Function LEDs
  - **PROJECT REQUIREMENT:** Vdrive max is 30v
  - **PROJECT REQUIREMENT:** Vdrive min is 6v
  - **BZ-C0805-C2-E1 DATASHEET:** Vf is 2.9v
  - **BZ-C0805-C2-E1 DATASHEET:** Max current is 25ma
    - Calculations based on a 20ma max current to maximize the number of substutable
      LEDs available.
  - **CALCULATE:** R = (30 - 2.9) / 0.020 = 1360
  - **CALCULATE:** Min current @ min voltage: (6 - 2.9) / 1360 = 0.0022
    - LED should still light at 2.2ma
  - 1.33 KOhms is a standard E48 and E96 series resistor value.
    - 0402 1% 1/8W resistors are generally available.
- Motor Direction LED
  - TBD
