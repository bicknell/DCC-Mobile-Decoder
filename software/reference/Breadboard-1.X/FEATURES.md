# Breadboard-1 Reference Software Features

The software implements the following features:

## DCC Electrical Standards

- Decodes a DCC bit stream compliant with NMRA standard S-9.1.

## DCC Communications Standards

- Interprets the bit steream described in the "General Packet Format"
  in NMRA standard S-9.2.
- Decodes "Baseline Packets" as described in NMRA standard S-9.2.
  - Speed and Direction
    - 14/28 speed step based on CV29 bit 1.
    - F0 if CV29 bit 1 is not set.
  - Reset
  - Idle
  - Broadcast Stop
- Decodes "Extended Packets" as described in NMRA standard S-9.2.1.
  - Section 2.2 Broadcast Commands.
  - Section 2.3 Instruction Packets.
    - Section 2.3.1.1 Decoder Control
      - TTT=000 F=0 Digital Decoder Reset
      - TTT=000 F=1 Digital Decoder Reset - Hard
      - TTT=101 Set Advanced Addressing
    - Section 2.3.1.2 Set Advanced Addressing
    - Section 2.3.1.4 Consist Control
      - Sets consist address (CV19) and direction.
    - Section 2.3.2.1 128 Speed Step Control
      - Decodes 128 speed step speed and direction messages at all times.
    - Section 2.3.3 14/28 Speed and Direction Instructions
      - 14/28 speed step based on CV29 bit 1.
      - F0 if CV29 bit 1 is not set.
    - Section 2.3.4 Function Group One (FL, F1-F4)
      - Includes logic to reference CV21/CV22 when CV19 consisting
        is active.
    - Section 2.3.5 Function Group Two (FL, F1-F4)
      - Includes logic to reference CV21/CV22 when CV19 consisting
        is active.
    - Section 2.3.6
      - Understands the packet format for parsing.
      - No commands under this section are implemented.
    - Section 2.3.7.2 Configuration Variable Access Instruction - Short Form
      - CV23 Acceleration Adjustment
      - CV24 Deceleration Adjustment
      - CV17/CV18/CV29 Long Address ***Does not check for two identical packets.***
      - CV31/CV32 Indexed CVs ***Does not check for two identical packets.***
    - Section 2.3.7.3 Configuration Variable Access Instruction - Long Form
      - GG=01 Verify Byte
        - ***Partially implemented:*** logs debug message only, no readback.
      - GG=11 Write Byte
      - GG=10 Bit Manipulation


## Configuration Values

The following is a list of configuration values implemented by the software.

- CV1 Short Address
  - Valid values are 1-127.
  - Used when CV29 bit 5 is 0.

- CV7 Manufacturer's Version *READ ONLY*
  - Stores the version number of the decoder.
  - Currently always 167.

- CV8 Manufacturer's ID *READ ONLY*
  - Stores the manufacturer's ID number assigned by the NMRA.
  - Currently always 13 for "Public Domain and DIY".

- CV17 Extended/Long Address, Low Byte
  - Always combined with CV18.
  - Valid (combined) values are 1-10239.
  - Used when CV29 bit 5 is 1.

- CV18 Extended/Long Address, High Byte
  - Always combined with CV18.
  - Valid (combined) values are 1-10239.
  - Used when CV29 bit 5 is 1.

- CV19 Consist Address
  - Bits 0-6:
    - When set to 0, consisting is disabled.
    - When set to 1-127, consisting is enabled at that address.
  - Bit 7 NDOT: 0 = Forward, 1 = Reverse

- CV21 Consist Active Functions F1-F8
  - Bit 0 F1 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 1 F2 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 2 F3 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 3 F4 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 4 F5 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 5 F6 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 6 F7 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 7 F8 Controlled by Consist: 0 = No, 1 = Yes

- CV22 Consist Active Functions F0F, F0R, F9-F12
  - Bit 0 FOF Controlled by Consist: 0 = No, 1 = Yes
  - Bit 1 FOR Controlled by Consist: 0 = No, 1 = Yes
  - Bit 2 Unused
  - Bit 3 Unused
  - Bit 4 F9 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 5 F10 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 6 F11 Controlled by Consist: 0 = No, 1 = Yes
  - Bit 7 F12 Controlled by Consist: 0 = No, 1 = Yes

- CV29 Mode Control
  - Bit 0 NDOT: 0 = Forward, 1 = Reverse
  - Bit 1 14/28 Speed Step: 0 = 14 speed step, 1 = 28 speed step.
    - Note that 128 speed step is always active.
  - Bit 5 Addressing: 0 = Short (CV1), 1 = Long (CV17/CV18)
