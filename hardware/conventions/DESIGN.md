# Hardware Design Requirements

In order to make the designs and resulting hardware accessible the project
has implemented the following guidelines.

## EDA Tooling

- All project files will be in KiCAD 6.x format.
- A schematic, PCB, and populated Symbol Field Table are the minimum to accept
  a new design.
- Supporting material is allowed in the following formats:
  - Plain text or Markdown for documentation.
  - PNG or JPEG for images.
  - Excel in ".xlsx" format for calculators used to generate component values.
- All work shall be done in *metric*.
  - Page size is A4.
  - Units are mm.
  - *EXCEPTION:* Any design targeting compatability with a 400 or 820 tie point
    breadboard shall use inches for the PCB design only, and attempt to use a 
    0.1" grid where possible.

## Microprocessor Choice

The project has standardized on Microchip's PIC18[LF] line of microprocessors,
and all designs will use parts from that line so they can share source code.

For background, here are some of the reasons PIC18[LF] was chosen:

- Parts are generally available worldwide.
- Parts are cost effective, generally around $1 +- $0.35 in quantities 100+.
- Small package, low pin-count parts are available for small scale decoders.
- There are generally multiple pin-compatable processors which can be 
  substutied, increasing overall avilability.
- Many commercial decoders already use the PIC16/PIC18 line.

Where possible designs should maximize the number of pin-compatable PIC18[LF]
chips that will work in an effort to make manufacturing designs cheaper and
faster.

## Schematic Conventions

- Paper should be set to A4, Landscape
- Title shall be the same as the directory name in the project.
- Company shall be set to the URL of the project homepage.
- Comments shall not be used.
- All labels shall be global labels.
- The "bus" function should not be used.
- Use of subsheets is discouraged, use only when necessary and minimize.

### Symbol Conventions

Generally speaking the "Small" international version of symbols should be used:

- Use R_Small for resistors, not R, R_US, R_Small_US.
- Use C_Small or C_Polarized_Small for capacitors, not C, C_Polarized, C_Polarized_US, or 
  C_Polarized_Small_US.
- Use L_Small for inductors, not L
- Use Crystal_*_Small for crystals, not Crystal_*
- Use D_Small for Diodes, not D or D_Filled or D_Small_Filled.

## Target Board Constraints

The project strives to minimize cost and maximize accessibility of the
designs.  As a result the following board constraints are used.

### Preferred

When possible, all designs should use these minimums: (Bold indicates not the default)

- Board Stackup / Physical Stackup
  - 2 layer board
    - **4** is acceptable when a 2 layer is not practical
  - 1.6mm thickness
    - Locomotive specific designs may use a different thickness.
  - FR4
- Board Stackup / Board Finish
  - Leave copper finish set to "None"
- Text and Graphics
  - Silk: **0.2mm**, 1mm, 1mm, **0.2mm**
  - Copper: 0.2mm 1.5mm, 1.5mm, 0.3mm
  - Edge Cuts: 0.1mm
  - Courtyards: 0.05mm
  - Fab Layers: 0.01mm, 1mm, 1mm, 0.15mm
  - Other Layers: **0.2mm**, 1mm, 1mm, **0.2mm**
  - Units: **Milimeters**
  - Units format: 1234 mm
  - Precision: 0.0000
  - Text Position: Outside
  - Keep text aligned: Check
  - Arrow length: 1.27mm
  - Extension line offset: 0.5mm
- Design Rules / Constraints
  - Allow blind/buried vias: unchecked
  - Allow micro vias: unchecked
  - Minimum clearance **0.2mm**
  - Minimum track width: 0.2mm
  - Minimum annular width: **0.2mm**
  - Minimum via diameter: **0.7mm**
  - Copper to hole clearance: 0.25mm
  - Copper to edge clearance: **0.25mm**
  - Mimimum through hole: 0.3mm
  - Hole to hole clearance: 0.25mm
- Design Rules / Pre-defined sizes
  - Track width: **0.2mm, 0.25mm, 0.3mm**
  - Vias: **0.7mm/0.3mm**
- Net Classes:
  - Default: 0.2mm, 0.25mm, **0.7mm**, **0.3mm**, 0.3mm, 0.1mm, 0.2mm, 0.25mm
- Copper Thickness: 1oz
- Components should be placed on 0.05mm grid.

### Minimums

Decoders for small scales may require tigher tolerances.  These are 
absolute minimums for accepted designs: (Bold indicates not the default)

- Board Stackup / Physical Stackup
  - 2 layer board
    - **4** is acceptable when a 2 layer is not practical
  - 1.6mm thickness
    - Locomotive specific designs may use a different thickness.
  - FR4
- Board Stackup / Board Finish
  - Leave copper finish set to "None"
- Text and Graphics
  - Silk: **0.1mm, 0.8mm, 0.8mm, 0.15mm**
  - Copper: 0.2mm 1.5mm, 1.5mm, 0.3mm
  - Edge Cuts: 0.1mm
  - Courtyards: 0.05mm
  - Fab Layers: 0.01mm, 1mm, 1mm, 0.15mm
  - Other Layers: **0.1mm, 0.8mm, 0.8mm, 0.15mm**
  - Units: **Milimeters**
  - Units format: 1234 mm
  - Precision: 0.0000
  - Text Position: Outside
  - Keep text aligned: Check
  - Arrow length: **1mm**
  - Extension line offset: **0.25mm**
- Design Rules / Constraints
  - Allow blind/buried vias: unchecked
  - Allow micro vias: unchecked
  - Minimum clearance **0.1mm**
  - Minimum track width: 0.1mm
  - Minimum annular width: **0.15mm**
  - Minimum via diameter: **0.5mm**
  - Copper to hole clearance: **0.15mm**
  - Copper to edge clearance: **0.2mm**
  - Mimimum through hole: **0.2mm**
  - Hole to hole clearance: **0.2mm**
- Design Rules / Pre-defined sizes
  - Track width: **0.1mm, 0.15mm, 0.2mm, 0.25mm, 0.3mm**
  - Vias: **0.5mm/0.3mm**
- Net Classes:
  - Default: **0.15mm**, **0.15mm**, **0.5mm**, **0.3mm**, 0.3mm, 0.1mm, 0.2mm, 0.25mm
- Copper Thickness: 1oz
- Components should be placed on 0.01mm grid.

## Components

Components should be chosen to maximize availability and minimize cost:

- Choose parts available worldwide.
- Use common parts and values whenever possible.
- Try to minimize parts & values in a single schematic.
  - Some manufacturers charge per value.
  - Some manufacturers charge per part.
- Courtyards shall not overlap.
- Minimum component size is 0402.
  - Smaller scales using the minimum values may use 0201 parts when necessary.
- SOIC and QFP packages are preferred for IC's.
  - Smaller scales using the minimum values may use QFN parts.
  - BGA parts are not acceptable.
- Through hole parts are not allowed unless necessary for mechanical reasons.
- SMT parts should be placed one sided only.
  - Smaller scales using the minimum values may use double sided SMT when necessary.

The Symbol Field Table should have the following fields populated:

- Datasheet: A link to a PDF version of the data sheet.
  - Where available, prefer the manufacturers web site.
  - If the part is a generic passive compoinent, fill in "Generic Passive".
- Value: A short value for the part designed to make the schematic readable.
  - Capacitors: 10uF, 100nF, 40pF
  - Resistors: 100 Ohm, 2K3
  - Transistors: 2N7000, TIP31C
  - IC's: Use MPN
- **Specification**: A long value for the part that fully specifies substutable parts.
  - Capacitors: 10uF 20% X5R 10v 0402, 100nF 10% X7R 100v 0805, 40pF 20% X5R 6v 0201
  - Resistors: 100 Ohm 1% 1/4 Watt 0402, 2K3 0.5% 1/8 Watt 0402
  - Transistors: 2N7000 40V 800mA SOT-323, TIP31C 100V 3A TO-220
  - IC's: Full manufacturer speficiation from data sheet
- **MPN 1**: A manufacturer's part number for a highly available suiable part.
- **MPN 2**: A manufacturer's part number for a highly available suiable part.

All parts shall have two MPN alternatives.  These should generally be chosen for good
worldwide availability.
