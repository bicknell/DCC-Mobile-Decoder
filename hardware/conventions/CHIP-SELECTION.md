# Micro-processor Selection

## Why Microchip PIC?

- Many commercial decoders use Microchip PICs, and since a project goal is to
  educate about how decoders work using the same chip makes sense.
- Microchip has built in features that make motor control simple.
- Chips are available in very small footprints, suitable for N and Z scale.
- Chips are readily available via many sources.
- There are often many pin-compatable options, allowing flexibility when
  ordering hardware.

## Why PIC18F?

A majority of commercial decoders use PIC16 family chips, although some have
started to move to PIC18.  Some of the reasons this project stanadardized on
PIC18F are:

- Faster clock speed, typically 64Mhz v 32Mhz.  This helps us keep all of the
  code in C, rather than assembly.  The extra headroom also should provide 
  less frustration to new developers who may not always choose the most efficient
  method first.
- There are additional assembly instructions specifically designed to make
  C code faster.  This allows us to do more in C, rather than assembly.
- Available in a VQFN 3x3 package for some chips.  For N and Z scale decoders
  it is critical to have very small packages available.

## Which PIC18F chips meet the requirements?

### N, Z, and other small scales.

Small scales need small chips.  Typically this means VQFN packages in 3x3 or 4x4.
The following options are available and are all pin compatable:

| Part Number         | Package | Size | RAM  | Max Clock | Temp       | Format |
| ------------------- | ------- | ---- | ---- | --------- | ---------- | ------ |
| PIC18F16Q40-I/REB   | VQFN-20 | 3x3  | 64k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F16Q40-E/REB   | VQFN-20 | 3x3  | 64k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F16Q40T-I/REB  | VQFN-20 | 3x3  | 64k  | 64Mhz     | -40 - +85  | Tape   |
| PIC18F16Q41-I/REB   | VQFN-20 | 3x3  | 64k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F16Q41-E/REB   | VQFN-20 | 3x3  | 64k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F16Q41T-I/REB  | VQFN-20 | 3x3  | 64k  | 64Mhz     | -40 - +85  | Tape   |
| PIC18F15Q40-I/REB   | VQFN-20 | 3x3  | 32k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F15Q40-E/REB   | VQFN-20 | 3x3  | 32k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F15Q40T-I/REB  | VQFN-20 | 3x3  | 32k  | 64Mhz     | -40 - +85  | Tape   |
| PIC18F15Q41-I/REB   | VQFN-20 | 3x3  | 32k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F15Q41-E/REB   | VQFN-20 | 3x3  | 32k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F15Q41T-I/REB  | VQFN-20 | 3x3  | 32k  | 64Mhz     | -40 - +85  | Tape   |
| PIC18F14Q41-I/REB   | VQFN-20 | 3x3  | 16k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F14Q41-E/REB   | VQFN-20 | 3x3  | 16k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F14Q41T-I/REB  | VQFN-20 | 3x3  | 16k  | 64Mhz     | -40 - +85  | Tape   |

### Larger Scales 

In larger scales a slightly larger chip can provide more I/O pins
and other features.  These are all pin compatable options, note the two
sizes of chips though.

| Part Number         | Package | Size | RAM  | Max Clock | Temp       | Format |
| ------------------- | ------- | ---- | ---- | --------- | ---------- | ------ |
| PIC18F26K40-I/MV    | UQFN-28 | 4x4  | 64k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F26K40-E/MV    | UQFN-28 | 4x4  | 64k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F26K40T-I/MV   | UQFN-28 | 4x4  | 64k  | 64Mhz     | -40 - +85  | Tape   |
| PIC18F25K40-I/MV    | UQFN-28 | 4x4  | 32k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F25K40-E/MV    | UQFN-28 | 4x4  | 32k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F25K40T-I/MV   | UQFN-28 | 4x4  | 32k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F25K42-I/MV    | UQFN-28 | 4x4  | 32k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F25K42-E/MV    | UQFN-28 | 4x4  | 32k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F25K42T-I/MV   | UQFN-28 | 4x4  | 32k  | 64Mhz     | -40 - +85  | Tape   |
| PIC18F26K42-I/MX    | UQFN-28 | 6x6  | 64k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F26K42-E/MX    | UQFN-28 | 6x6  | 64k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F26K42T-I/MX   | UQFN-28 | 6x6  | 64k  | 64Mhz     | -40 - +85  | Tape   |
| PIC18F26K83-I/MX    | UQFN-28 | 6x6  | 64k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F26K83-E/MX    | UQFN-28 | 6x6  | 64k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F26K83T-I/MX   | UQFN-28 | 6x6  | 64k  | 64Mhz     | -40 - +85  | Tape   |
| PIC18F25K83-I/MX    | UQFN-28 | 6x6  | 32k  | 64Mhz     | -40 - +85  | Tray   |
| PIC18F25K83-E/MX    | UQFN-28 | 6x6  | 32k  | 64Mhz     | -40 - +125 | Tray   |
| PIC18F25K83T-I/MX   | UQFN-28 | 6x6  | 32k  | 64Mhz     | -40 - +85  | Tape   |


### Breadboard Designs

For Breadboard designs it can be useful to have USB connectivity.  The following
chips have built in USB hardware.  Note that the tradeoff is a 48Mhz max clock
speed.

| Part Number         | Package | Size | RAM  | Max Clock | Temp       | Format |
| ------------------- | ------- | ---- | ---- | --------- | ---------- | ------ |
| PIC18F25K50-I/ML    | QFN-28  | 6x6  | 32K  | 48Mhz     | -40 - +85  | Tray   |
| PIC18F25K50-E/ML    | QFN-28  | 6x6  | 32K  | 48Mhz     | -40 - +125 | Tray   |
| PIC18F25K50T-I/ML   | QFN-28  | 6x6  | 32K  | 48Mhz     | -40 - +85  | Tape   |
| PIC18F26K22-E/ML    | QFN-28  | 6x6  | 64K  | 48Mhz     | -40 - +125 | Tray   |

## Project Recommendations

In order to maximize the interchangeability the project recommends using the 
following chips for design purposes.  They have been selected from the list 
above, generally are lower-featuered versions so that substuting with a higher
feature version works.  They also have shown good historical availably via the
major vendors.

### N & Z

PIC18F16Q41-I/REB, PIC18F16Q41-E/REB, PIC18F16Q41T-I/REB

This part appears to be more often in stock than other options.  2022-11-25.

### Larger Scales

None of the parts currently show good availability. 2022-11-25.

### Breadboard Designs
