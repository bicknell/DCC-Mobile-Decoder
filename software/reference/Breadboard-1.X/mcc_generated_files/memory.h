/**
  MEMORY Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    memory.h

  @Summary
    This is the generated header file for the MEMORY driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for MEMORY.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F16Q40
        Driver Version    :  1.1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB             :  MPLAB X 6.00
*******************************************************************************/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef MEMORY_H
#define MEMORY_H

/**
  Section: Included Files
 */

#include <xc.h>
#include <stdint.h>

/**
  Section: Macro Declarations
 */

#define WRITE_FLASH_BLOCKSIZE    256
#define ERASE_FLASH_BLOCKSIZE    256
#define END_FLASH                0x010000


/**
  Section: MEMORY APIs
 */

/**
 * @brief This routine reads one data byte from given address of Program Flash Memory
 * @return Data byte read from given Program Flash Memory address
 * @param [in] Address of Program Flash Memory location to be read
 * @example void main(void)
 *          {
 *              uint8_t readByte;
 *              SYSTEM_Initialize();
 *              readByte = FLASH_ReadByte(0x1FF00);
 *          }
 */
uint8_t FLASH_ReadByte(uint32_t flashAddr);

/**
 * @brief This routine reads one word from given address of Program Flash Memory
 * @return Data word read from given Program Flash Memory address
 * @param [in] Address of Program Flash Memory location to be read
 * @example void main(void)
 *          {
 *              uint16_t readWord;
 *              SYSTEM_Initialize();
 *              readWord = FLASH_ReadByte(0x1FF00);
 *          }
 */
uint16_t FLASH_ReadWord(uint32_t flashAddr);

/**
 * @brief This routine reads one block from given address of Program Flash Memory
 *        into device Buffer RAM
 * @return None
 * @param [in] Starting address of a Program Flash Memory block
 * @example Use case: Read one page from given PFM location into device Buffer RAM using FLASH_ReadPage()
 *                    Transfer the contents of device Buffer RAM to U1TXB using DMA2
 *                    
 *          void main(void)
 *          {   
 *              SYSTEM_Initialize();
 *
 *              //Read one page from PFM into device Buffer RAM
 *              FLASH_ReadPage();
 *
 *              //Initialize DMA2 to copy data from device Buffer RAM to U1TXB register
 *              //Configure source size as 256 and destination size as 1
 *              DMA2_Initialize();
 *          }
 */
void FLASH_ReadPage(uint32_t flashAddr);

/**
 * @brief This routine writes one block of data from Buffer RAM to the given address of Program Flash Memory
 * @return None
 * @param [in] Starting address of a Program Flash Memory block
 * @example Use case: Data received in U1RXB is copied to device Buffer RAM using DMA1.
 *                    Once page-sized data is copied to device Buffer RAM, 
 *                    it will be transferred to PFM using FLASH_WritePage()
 *          void main(void)
 *          {   
 *              SYSTEM_Initialize();
 *
 *              //Initialize DMA1 to copy data from UART receive buffer to device Buffer RAM
 *              //Configure Source size as 1 and destination size as 256 (PFM page size)
 *              DMA1_Initialize();
 *
 *              //Once 256 bytes are copied in device buffer RAM,
 *              //Write the data available in device Buffer RAM to given PFM page
 *              FLASH_WritePage();
 *          }
 */
void FLASH_WritePage(uint32_t flashAddr);

/**
 * @brief This routine writes one word to given address of erased Program Flash Memory location
 * @return None
 * @param [in] Address of erased Program Flash Memory location to be written
 * @param [in] Data word to be written to given address
 * @example void main(void)
 *          {
 *              SYSTEM_Initialize();
 *              FLASH_WriteWord(0x1FF00,0x55AA);
 *          }
 */
void FLASH_WriteWord(uint32_t flashAddr, uint16_t word);

/**
 * @brief This routine writes 128 words from given block start address
 * @return Status of operation
 * @param [in] Starting address of a Program Flash Memory block
 * @param [in] Address of RAM buffer to be copied to Program Flash Memory block
 * @example uint16_t flashWrBufPtr[WRITE_FLASH_BLOCKSIZE] =
 *          {
 *              0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0x2, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0x3, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0x4, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0x5, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0x6, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0x7, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0x8, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0x9, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0xa, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0xb, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0xc, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0xd, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0xe, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0xf, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
 *              0xf, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8
 *          };
 *          void main(void)
 *          {
 *              SYSTEM_Initialize();
 *              FLASH_WriteBlock(0x1FF00,flashWrBufPtr);
 *          }
 */
int8_t FLASH_WriteBlock(uint32_t flashAddr, uint16_t *flashWrBufPtr);

/**
 * @brief This routine erases 128-words block from given address of Program Flash Memory
 * @return None
 * @param [in] Starting address of Program Flash Memory block to be erased
 * @example void main(void)
 *          {
 *              SYSTEM_Initialize();
 *              FLASH_EraseBlock(0x1FF00);
 *          }
 */
void FLASH_EraseBlock(uint32_t flashAddr);

/**
  Section: Data EEPROM Module APIs
 */

/**
 * @brief This routine writes one data byte to given EEPROM address
 * @return None
 * @param [in] Address of EEPROM location to be written
 * @param [in] Data byte to be written to given EEPROM location
 * @example void main(void)
 *          {
 *              SYSTEM_Initialize();
 *              DATAEE_WriteByte(0x2, 0xAB);  //Writes a byte to 0x380002
 *          }
 */
void DATAEE_WriteByte(uint16_t bAdd, uint8_t bData);

/**
 * @brief This routine reads one data byte from given EEPROM address
 * @return Data byte read from given EEPROM address
 * @param [in] Address of EEPROM location to be read
 * @example void main(void)
 *          {
 *              uint8_t eepromByte;
 *              SYSTEM_Initialize();
 *              eepromByte = DATAEE_ReadByte(0x2);    //Reads a byte from 0x380002
 *          }
 */
uint8_t DATAEE_ReadByte(uint16_t bAdd);
#endif  // MEMORY_H
