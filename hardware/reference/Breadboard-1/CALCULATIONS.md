# Breadborad-1 Calculations

## Data Sheets

- Micro-processor: [PIC18F06Q40](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC18F06-16Q40-Data-Sheet-40002216D.pdf)
- H-Bridge High Side MOSFETS: [NCE2309](https://datasheet.lcsc.com/lcsc/2004201605_Wuxi-NCE-Power-Semiconductor-NCE2309_C502865.pdf)
  - SOT-23, P-Channel, Vdss -60V, Rds(on) 140 mOhm, Id -1.3A, Vgs(th) -2.0v max -2.6v.
  - "2309" is a common P-Channel MOSFET, with many manufactuers having slight variations.
- H-Bridge High Side Driver: [DTC143ZCA](https://datasheet.lcsc.com/lcsc/1809140113_Jiangsu-Changjing-Electronics-Technology-Co---Ltd--DTC143ZCA_C15236.pdf)
  - SOT-23, Vcc 50V, Io 100mA, R1 = 4.7K, R2 = 47K
  - This is a "pre-biased" or "digital" transistor.  It is an NPN transistor with two resistors
    in the same package.  This saves two additional discrete components.  It is used to drive
    the P-Channel MOSFETs.
- H-Bridge Low Side MOSFETS: [DMN6140L-7](https://datasheet.lcsc.com/lcsc/1810101252_Diodes-Incorporated-DMN6140L-7_C156306.pdf)
  - SOT-23, N-Channel, Vdss 60V, Rds(on) 92 mOhm, Id 1.6A, Vgs(th) 1.0v max 3.0v.
  - There is no particular common part number for this part, but a wide variety of similar
    parts is available.
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
  - B5819WS diodes are rated for 40V.
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

- Q31-Q32 High Side MOSFETs
  - **PROJECT REQUIREMENT:** Vgs must be < 6V, the minimum track voltage.
    - NCE2309 is max 2.5v.
  - **PROJECT REQUIREMENT:** Vds must be >= 30V.
    - NCE2309 is 60V.
  - **PROJECT REQUIREMENT:** Id must be >= 1A.
    - NCE2309 is 1.3A.
  - PNP MOSFETs need high side drive
    - R31/R32 are 10K pull ups to keep the PNP FET "off".
    - Q35-Q36 are DTC143ZCA pre-biased transistor to drive to save resistors.
      - Integrated 4.7K on the base input, 47K base to ground.
      - **CALCULATE** Loss due to resistors: I = V/R, 5V / (4.7K + 47k) = 0.1ma to ground.
      - **CALCULATE** Current C-E @30V: I = V / R, 30V / 10K = 3ma
      - **CALCULATE** Transistor Gain = 80, B-E current = 3ma / 80 = 0.0375ma
      - **CALCULATE** Total draw from micro: 0.1ma + 0.0375ma = 0.01375ma
- Q32-Q33 Low Side MOSFETs
  - **PROJECT REQUIREMENT:** Vgs must be < 5V, the micro-controller output voltage.
    - DMN6140L-7 is max 3v.
  - **PROJECT REQUIREMENT:** Vds must be >= 30V.
    - DMN6140L-7 is 60V.
  - **PROJECT REQUIREMENT:** Id must be >= 1A.
    - DMN6140L-7 is 1.6A.
  - R33/R34 Gate resistors limit inrush current:
    - **PROJECT REQUIREMENT:** Micro-controller runs at 5v.
    - **PIC18F06Q40 DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sunk per pin
    - **PIC18F06Q40 DATASHEET** *29.1 Absolute Maximum Ratings* 25ma max sourced per pin
    - **PIC18F06Q40 DATASHEET** *29.1 Absolute Maximum Ratings* 110ma max sunk all ports
    - **PIC18F06Q40 DATASHEET** *29.1 Absolute Maximum Ratings* 70ma max sourced all ports
    - **CALCULATE:** R = 5v / 0.025ma = 200 Ohm
      - E48 & E96 standard value of 202 Ohm
      - 220 Ohm is a popular value that may be cheaper.
    - 0805 220 1% 1/8W resistors are generally avalable.
- R35 & R36 BackEMF sense resistors must put max voltage in the 0-5V range of the
  micro-controller: (Note Same as DCC Dividers Above)
  - **PROJECT REQUIREMENT:** Vdrive max = 30v
  - **PIC18F06Q40 DATASHEET:** *Parameter D001:* Vdd = 5v
  - **CALCULATE:** Voltage divider equation: 5 = (30 * R2) / (R1 + R2)
    - *NOTE:* There are 3 resistors.  One of the uppers will be tied to ground, the
      other to motor voltage based on the direction of the H-Bridge.
    - Select LOWER = 1.33K (Value needed for diagnostic LEDs)
    - Thus R1 = UPPER
    - Thus 1/R2 = 1/UPPER + 1/LOWER, or R2 = UPPER * LOWER / UPPER + LOWER
    - Thus 5 = (30 * ((UPPER * LOWER) / (UPPER + LOWER)) / (UPPER + ((UPPER * LOWER) / (UPPER + LOWER)))
      - Simplified: LOWER = UPPER / 4
    - Select LOWER = 1.33K (Value needed for diagnostic LEDs)
    - Result: UPPER = 5.32K, closest E96 resistor is 5.36K
    - Result: UPPER + LOWER in parallel = 1065 Ohms
  - 0805 1.33K & 5.36K 1% 1/8W resistors are generally avalable.
- C31-C32 provide high frequency noise snubbing, and protect the rest of the 
  Vdrive components from receiving fluctuations from the motor.  Value is a 
  guess.

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

### Dummy Load

When JP61 is installed a 100 Ohm resistor is connected to the motor outputs.  This
enables "readback" functionality without having a motor connected, or generating a
load on a command station when increasing the speed without having a motor attached.

- Dummy load resistor R61
  - **PROJECT REQUIREMENT:** Vdrive max is 30v
  - **PROJECT REQUIREMENT:** Vdrive min is 6v
  - **NMRA Standard S9.2.3:** "Basic acknowledgment is defined by the Digital Decoder providing 
    an increased load (positive-delta) on the programming track of at least 60 mA for 6 ms +/-1 ms."
  - **CALCULATE:** R = V / I
  - **CALCULATE:** 30 / 0.060, R = 500 Ohm
  - **CALCULATE:** 6 / 0.060, R = 100 Ohm
  - 100 Ohms is needed at the lowest voltage, recalcuate at highest.
  - **CALCULATE:** I = V / R
  - **CALCULATE:** 30 / 100 = .300, aka 300ma
  - **CALCULATE:** P = V * I
  - **CALCULATE:** P = 30 * .3, W = 9W
  - A 9W resistor would need to be a wire-wound, 2" long device.  But we can take advantage of the fact
    that readback is only 60ma for 6ma, e.g. a burst.  Many resistors are rated for 5x burst, so
    we consider a 2 Watt 100 Ohm, 5x burst option.
  - 100 Ohm 2 Watt 5% resistors in a 2512 case are readily available.

