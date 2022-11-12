# Naming Convention

## Reference Implementations

Reference implementations are named based on their target application and a sequence
number.  Current target applications include:

* `Breadboard` for reference implmentations that will plug into a 400 or 820 point
  solderless breadboard.
* `Solder` for reference implmentations that contain only solder pads.

## Mobile Decoders

Names will be made up of the following components:

* Manufacturer - One of:
  - `Aristo` - Aristocraft
  - `Athearn`
  - `Atlas`
  - `Kato`
  - `Generic` - NMRA Stanadardized Connectors
* Scale
  - `Z` - 1:220
  - `N` - 1:160
  - `Nn2` - 1:160
  - `Nn3` - 1:160
  - `TT` - 1:120
  - `HO` - 1:87
  - `HOn2` - 1:87
  - `HOn30` - 1:87
  - `HOn3` - 1:87
  - `S` - 1:64
  - `Sn3` - 1:64
  - `O27` - 1:48
  - `O` - 1:45
  - `On2` - 1:45
  - `On30` - 1:45
  - `On3` - 1:45
  - `G` - All variants
  - `NMRA6` - NMRA 6 Pin Generic Connector
  - `NMRA8` - NMRA 6 Pin Generic Connector
  - `JST9` - NMRA 6 Pin Generic Connector
  - `MTC` - NMRA 6 Pin Generic Connector
  - `PLUX` - NMRA 6 Pin Generic Connector
  - `NEXT18` - NMRA 6 Pin Generic Connector
  - `NEXT18S` - NMRA 6 Pin Generic Connector
* Amperage
  - To the nearest 0.1A
* Functions
  - Number of functions supported not including F0.  E.g. F1-F6 = 6
* Locomotive - If designed to fit a specific model, otherwise omitted.
* Iterator - Starts at 1, and incremented if new designs are added.

Example names:

* Athearn-N-1.5A-6-SD60-1 - Fits an N scale Athearn SD60, provides 1.5A peak and 6 functions.
* Atlas-HO-2A-6-GP40-3 - Fits an Atlas HO GP40, provides 2A peak and 6 functions.  Third design.
* Generic-NMRA6-3A-2-1 - Fits a NMRA 6 pin connector, provides 3A peak and 2 functions.
