# Documentation

## Project goals

1. Provide a highly documented DCC hardware and software implementation
   suitable for teaching people new to DCC.
   - High quality documentation.
   - Hardware designs that are easy to understand, using commonly available
     components.
   - Software written in an easy to understand manor, well commented including
     references to the relevant NMRA documentation.
   - Be liberal in what is accepted, and conservative in what is sent.  That is,
     try to allow a wider range of inputs than is required and still function
     properly, while making sure outputs are in strict compliance with the 
     specifications.
1. Implement all relevant NMRA DCC __Standards (S)__.
1. Implement as many NMRA DCC __Recomended Practices (RP)__ as practical.
1. Where possible, follow the guidance in NMRA DCC __Technical Note (TN)__,  
   __Technical Information (TI)__, and __Technical Reference (TR)__ documents.
1. Implement decoders that can be used for real world applications.
   - Prioritize "wired" decoder designs that can be used in a wide range of 
     products.
   - Implment locomotive specific designs driven by community interest.
1. Grow a vibrate, open source mobile decoder community.

## NMRA Standards

NMRA standards can be found at the links below:

* [NMRA Standards and Recommended Practices](https://www.nmra.org/index-nmra-standards-and-recommend
ed-practices), in particular section 9.1 contains all of the DCC details.
  * **S-9.1 Electrical Standards for Digital Command Control**
    contains bit timing information, voltages, and other signalling information.
    Also under this section is connector pinouts.  Generally, the hardware interface.
  * **S-9.2 DCC Communications Standard** contains the packet format and command structure.
    Generally, the software interface.

## Feature Lists

The following feature lists document decoder features in marketing terms that
users may see on commercial decoder packaging.  Where particular manufacturers
have trade names for these features, they are listed.

Features implemented by this project are marked as such.  Not all features will
be implemented by this project, these documents serve as general reference material.

* [HARDWARE-FEATURES.md](HARDWARE-FEATURES.md) contains a list of hardware features.
* [SOFTWARE-FEATURES.md](SOFTWARE-FEATURES.md) contains a list of software features.
