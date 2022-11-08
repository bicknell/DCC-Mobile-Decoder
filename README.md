# DCC-Mobile-Decoder
DCC Mobile Decoder Reference Implementation Hardware &amp; Software

## About

An open hardware and software implementation of a NMRA DCC compatable
Mobile Decoder.

## Layout

* [docs/](docs/) documentation.
* [hardware/conventions/](hardware/conventions/) has a list of requirements
  for all hardware implementations so they can work with the common software.
* [hardware/reference/](hardware/reference/) directory contains reference 
  implementations of decoder hardware.  These are designed to be easy to
  understand for teaching purposes, have a physical form factor to make
  them easy to use for prototyping with standard breadboards.  It my be
  possible to use them in locomotives, but that is not the primary purpose.
* [hardware/decoders/](hardware/decoders/) directory contains specific
  decoders designed for specific applications.
* [software/common/](software/common/) common source code used across all
  decoder implementations.  This is the majority of the DCC processing
  code.
* [software/reference/](software/reference/) source code for the reference
  implementation hardware.
* [software/decoders/](software/decoders/) source code for specific decoders
  in [hardware/decoders/](hardware/decoders/).

## License

Licensed under the **Creative Commons Attribution-NonCommercial 4.0 
International Public License**, see the file [LICENSE](LICENSE) for
complete details.

Licenses for commerical use may be negotiated on a case by case basis.
Please contact project maintainers.


