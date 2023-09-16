# DCC-Mobile-Decoder
DCC Mobile Decoder Reference Implementation Hardware &amp; Software

## About

An open hardware and software implementation of a NMRA DCC compatable
Mobile Decoder using a PIC18 micro-processor.  The project aims to
make available a reference implementation of hardware and software to
facilitate software development, plus one or more decoder designs that
could be used in actual locomotives.

***This project is not yet complete and does not work in its current state.***

At this point the decoder can be connected to a DCC signal (ops mode) and 
correctly interprets speed, direction, functions f0-f12, ops mode CV programming,
and consisting.

Basic motor control has been implemented, but has not been tested with a real
motor.

Path to a working decoder:
  - [ ] Complete Hardware reference design - Breadboard-1. (Est 98% complete.)
  - [ ] Initial basic software for reference design. (Est 85% complete.)
    - CV's:
      - Obtain a manufacturer ID number?
        - Assign version numbers to decoders?
    - DCC Protocol:
      - Test/debug service mode programming, implemented but not tested.
      - Implement the "Factory Test" instruction?  What would it do?
      - Figure out what to send back for S-9.2.1 2.3.1.3 TTT=111 Decoder Acknowledgement Request
      - Pulse the motor for readback when in service mode.
      - Parse 11 bit DCC addresses?  Aren't they accessory decoder only?
      - Figure out if the Zimo East-West is 2 or 3 byte messages.
      - Handle S-9.2.1 2.3.6 CCC=110 Feature Expansion Instruction See TN-3-05
      - Handle S-9.2.3 Appendix B Service Mode Decoder LockA
    - Hardware Control:
      - Implement lighting effects.
      - Implement motor control.
        - Basic forward/reverse.
        - BackEMF adjustment.
        - Analog Mode?
    - Portability:
        - What needs to be done to make a common set of software that can be used
          across multiple decoder designs?
  - [ ] Initial real decoder design. (Proof of concept drafted.)
    - Draft of Wired-N-1A-6-1 has been produced.
    - Needs further mineaturization (e.g. more DFN components), and possible
      removal of gate resistors.
  - [ ] Documentation for above. (Est 60% complete.)

## Layout

* [docs/](docs/) documentation.
* [hardware/](hardware/) contains all materials related to hardware designs.
  This top level folder also includes a full index of the designs available.
  * [hardware/conventions/](hardware/conventions/) has a list of requirements
    for all hardware implementations so they can work with the common software.
  * [hardware/reference/](hardware/reference/) directory contains reference 
    implementations of decoder hardware.  These are designed to be easy to
    understand for teaching purposes, have a physical form factor to make
    them easy to use for prototyping with standard breadboards.  It my be
    possible to use them in locomotives, but that is not the primary purpose.
  * [hardware/decoders/](hardware/decoders/) directory contains specific
    decoders designed for specific applications.
* [software/](software/) contains all materials related to software code and build tools.
  * [software/common/](software/common/) common source code used across all
    decoder implementations.  ***FUTURE***
  * [software/reference/](software/reference/) source code for the reference
    implementation hardware.
  * [software/decoders/](software/decoders/) source code for specific decoders
    in [hardware/decoders/](hardware/decoders/).

## License

Licensed under the **Creative Commons Attribution-NonCommercial 4.0 
International Public License**, see the file [LICENSE](LICENSE) for
complete details.

Licenses for commerical use may be negotiated on a case by case basis.
Please contact project maintainers.  Any commercial terms negotiated
will include:

- A licensing term.
- An annual payments during the term that will be used to support
  the project.
- No royalties.
- A requirement to provide attribution in the instructions and on the
  packaging.

## Contributing

Please help us!

We would like to have a comprehensive library of hardware decoder designs
along with software implementations.  We want to enable everyone to build,
program, and modify their own DCC decoder.

Contributed material must be compatable with our license terms, project
goals, and project standards.

In particular we would like to encourage the following:

- New hardware designs for "drop in" decoders.
- Additional software features that make the software feature competitive
  with commercial decoders.
- Additional documentation to help others learn about DCC implementations.
