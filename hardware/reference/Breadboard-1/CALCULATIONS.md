# Breadborad-1 Calculations

## Data Sheets

- Micro-processor: [PIC18F06Q40](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC18F06-16Q40-Data-Sheet-40002216D.pdf)
- Motor Driver: [DRV8870DDAR](https://datasheet.lcsc.com/lcsc/1809050151_Texas-Instruments-DRV8870DDAR_C86590.pdf)
  - Max VM: 50v
  - Peak current: 3.6A.
- Functions MOSFET: [2N7002K](https://datasheet.lcsc.com/lcsc/2111241030_Jiangsu-Changjing-Electronics-Technology-Co---Ltd--2N7002K_C2910165.pdf)
  - SOT-23, Vdss 60V, Rds(on) 2.5 Ohm, Id 340ma Vgs(th) 1.3v max 2.5v
  - 2N7002 is a common MOSFET.  Many manufacturers have part numbers that include a suffix
    indicating they are better than the original part in some way.  For the most part,
    any 2N7002 in SOT-23 should work.
- Linear Regulator: [ME6203A50M3G](https://datasheet.lcsc.com/lcsc/1810201512_MICRONE-Nanjing-Micro-One-Elec-ME6203A50M3G_C92717.pdf)
  - SOT-23, LDO Regulator, 40V input, 5v fixed output, 100mA max current.
  - Any SOT-23 linear regulator with the same pinout and similar specs should work fine.
- Diodes: [B5819WS](https://datasheet.lcsc.com/lcsc/1811011616_Shandong-Jingdao-Microelectronics-B5819WS_C169530.pdf)
  - SOD-323, 40V, 1A Schottky barrier rectifier diode.
- Function LEDs: [BZ-C0805-C2-E1](https://datasheet.lcsc.com/lcsc/2106081833_baizou-BZ-C0805-C2-E1_C2833063.pdf)
  - 0805, Bright White, 25ma If Max, Vf (center) 2.9v
- Motor LED: [XL-3227SURSYGC](https://datasheet.lcsc.com/lcsc/2211030000_XINGLIGHT-XL-3227SURSYGC_C965843.pdf)
  - Red/Green LED in a standard 1210 4-pin package.
  - 25mA working current, Vf = 2.0V.

## Power Supply

- **ME6203A50M3G DATASHEET:** C11 & C12 10uF capacitors are the data sheet 
  recommendation for an ME6203A50M3G
  - C11 & C12 0805 50V 10uF X5R 10% are generally available.
- **PROJECT REQUIREMENT:** D11-D14 & C11 must be rated for >= 30V.
  - B5819WS diodes are rated for 1A.
  - C11 & C12 0805 50V 10uF X5R 10% are generally available.
- **PROJECT REQUIREMENT:** D11-D14 must be rated for >= 1A.
  - B5819WS diodes are rated for 1A.

## Micro-controller

- **PIC18F06Q40 DATASHEET** *Figure 4-1 Recommended Minimum Connections*
  - C21 100nF 20V decoupling capacitor.
    - 0805 50V 100nF X7R 10% are generally available.
  - R23 10K / C23 100 nF 20V MCLR hold up circuit.
    - 0805 10K 1% 1/8W are generally available.
    - 0805 50V 100nF X7R 10% are generally available.
- R21 & R22 form a voltage divider to bring the DCC signal in range of the micro-controller: (Note same as BackEMF below)
  - **PROJECT REQUIREMENT:** Vdrive max = 30v
  - **PROJECT REQUIREMENT:** Vdrive min = 6v
  - **PIC18F06Q40 DATASHEET:** *Parameter D001:* Vdd = 5v
  - **PIC18F06Q40 DATASHEET:** *Parameter D141:* Input Low Voltage I/O Port Schmitt Trigger Buffer Max 0.2 * Vdd = 1v
  - **CALCULATE:** Voltage divider equation: 5 = (30 * R2) / (R1 + R2)
    - Select R2 = 1.33K (Value needed for diagnostic LEDs)
    - Result: R1 = 6.65K which is an E96 resistor value.
    - Check minimum voltage: (6 * 1330) / (6650 + 1330) = 1v
  - **CALCULATE:** Imax = 30v / ((6650 + 1330) = 3.75ma @ 30V = .112 watts
    - 1/8 Watt resistors are sufficient.
  - 0805 1.33K & 6.65K 1% 1/8W resistors are generally avalable.

## H-Bridge

- U31 Motor Driver
  - **PROJECT REQUIREMENT:** Must operate on a minimum track voltage of 7 volts.
    - Min VM is 6.5v.
  - **PROJECT REQUIREMENT:** Must operate on a maxium track voltage of 30 volts.
    - Max VM is 50v.
  - **PROJECT REQUIREMENT:** Must operate at 5V logic.
    - Vi is 0 5.5V.
  - **NOTE:** PWM frequency mut be no greater than 100kHz when driving.
- R31, R32, R33 BackEMF sense resistors must put max voltage in the 0-5V range of the
  micro-controller:
  - **PROJECT REQUIREMENT:** Vdrive max = 30v
  - **PROJECT REQUIREMENT:** Vdrive min = 6v
  - **PIC18F06Q40 DATASHEET:** *Parameter D001:* Vdd = 5v
  - **PIC18F06Q40 DATASHEET:** *Parameter D141:* Input Low Voltage I/O Port Schmitt Trigger Buffer Max 0.2 * Vdd = 1v
  - When the motor is driving, one of R31/R32 will be connected to groud (depending on
    direction).  Thus the Resistance to Ground will be 1/R31 + 1/R33 = 1/Rground
  - **CALCULATE:** Voltage divider equation: 5 = (30 * Rground) / (R31 + Rground)
    - Select R33 = 1.33K (Value needed for diagnostic LEDs)
    - Result: R31 = 4.511K, 4.53K is a standard E96 resistor value.
    - **CALCULATE:** 1/Rground = 1/1.33K + 1/4.53k, Rground = 1.03k
    - Check minimum voltage:
      - **CALCULATE:** (6 * 1.03K) / (4.53K + 1.03K) = 1.11v
  - **CALCULATE:** Imax = 30v / (4.53K + 1.03K) = 5.4ma @ 30V = .162 watts
    - 1/4 Watt resistors are necessary..
  - 0805 1.33K & 4.53K 1% 1/4W resistors are generally avalable.

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
    - 0805 470 1% 1/8W resistors are generally available.

### F1-F6 Generic Output

- MOSFET
  - **PROJECT REQUIREMENT:** Vdd = 5v
  - **PROJECT REQUIREMENT:** Vdrive max = 30v
  - **PROJECT REQUIREMENT:** Function Max Current = 100ma
  - Vgs must be < 5V, as the micro-controller only sources 5v.
    - 2N7002K is max 2.5v.
  - Vds must be >= 30V.
    - 2N7002K is 60V.
  - Id must be >= 100mA.
    - 2N7002K is 340ma.
  - Gate resistors limit inrush current:
    - **PIC18F06Q40 DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sunk per pin
    - **PIC18F06Q40 DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sourced per pin
    - **PIC18F06Q40 DATASHEET** *29.1 Absolute Maximum Ratings* 110ma max sunk all ports
    - **PIC18F06Q40 DATASHEET** *29.1 Absolute Maximum Ratings* 70ma max sourced all ports
    - **CALCULATE:** R = 5v / 0.025ma = 200 Ohm
      - E48 & E96 standard value of 202 Ohm
      - 220 Ohm is a popular value that may be cheaper.
    - 0805 220 1% 1/8W resistors are generally available.

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
    - 0805 1% 1/8W resistors are generally available.
- Motor Direction LED
  - **XL-3227SURSYGC DATASHEET** Vf is 2.0v
  - **XL-3227SURSYGC DATASHEET** Max current is 25ma
    - Calculations based on a 20ma max to extend life.
  - **CALCULATE:** R = (30 - 2.0) / 0.020 = 1400
  - **CALCULATE:** Min current @ min voltage: (6 - 2.0) / 1400 = 0.0028
    - LED should still light at 2.8ma
  - 1.40 KOhms is a standard E48 and E96 series resistor value.
    - 0805 1% 1/8W resistors are generally available.
