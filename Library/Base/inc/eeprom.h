/**
  \file eeprom.h
   
  \author G. Icking-Konert
  \date 2014-04-22
  \version 0.1
   
  \brief declaration of flash read/write routines
   
  declaration of flash/EEPROM read and write routines.
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _EEPROM_H_
#define _EEPROM_H_

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"


/*-----------------------------------------------------------------------------
    DEFINITION OF GLOBAL MACROS/#DEFINES
-----------------------------------------------------------------------------*/

//////
// addresses of option bytes
//////
#define NUM_OPT 0x80                   //!< number of option bytes (for range check)

#define OPT0   (OPT_BaseAddress+0x00)  //!< Option byte 0: Read-out protection (not accessible in IAP mode)
#define OPT1   (OPT_BaseAddress+0x01)  //!< Option byte 1: User boot code */
#define NOPT1  (OPT_BaseAddress+0x02)  //!< Complementary Option byte 1 */
#define OPT2   (OPT_BaseAddress+0x03)  //!< Option byte 2: Alternate function remapping */
#define NOPT2  (OPT_BaseAddress+0x04)  //!< Complementary Option byte 2 */
#define OPT3   (OPT_BaseAddress+0x05)  //!< Option byte 3: Watchdog option */
#define NOPT3  (OPT_BaseAddress+0x06)  //!< Complementary Option byte 3 */
#define OPT4   (OPT_BaseAddress+0x07)  //!< Option byte 4: Clock option */
#define NOPT4  (OPT_BaseAddress+0x08)  //!< Complementary Option byte 4 */
#define OPT5   (OPT_BaseAddress+0x09)  //!< Option byte 5: HSE clock startup */
#define NOPT5  (OPT_BaseAddress+0x0A)  //!< Complementary Option byte 5 */
#define RES1   (OPT_BaseAddress+0x0B)  //!< Reserved Option byte*/
#define RES2   (OPT_BaseAddress+0x0C)  //!< Reserved Option byte*/
#define OPT7   (OPT_BaseAddress+0x0D)  //!< Option byte 7: flash wait states */
#define NOPT7  (OPT_BaseAddress+0x0E)  //!< Complementary Option byte 7 */

#define OPT8   (OPT_BaseAddress+0x10)  //!< Option byte 8:  TMU key 1 */
#define OPT9   (OPT_BaseAddress+0x11)  //!< Option byte 9:  TMU key 2 */
#define OPT10  (OPT_BaseAddress+0x12)  //!< Option byte 10: TMU key 3 */
#define OPT11  (OPT_BaseAddress+0x13)  //!< Option byte 11: TMU key 4 */
#define OPT12  (OPT_BaseAddress+0x14)  //!< Option byte 12: TMU key 5 */
#define OPT13  (OPT_BaseAddress+0x15)  //!< Option byte 13: TMU key 6 */
#define OPT14  (OPT_BaseAddress+0x16)  //!< Option byte 14: TMU key 7 */
#define OPT15  (OPT_BaseAddress+0x17)  //!< Option byte 15: TMU key 8 */
#define OPT16  (OPT_BaseAddress+0x18)  //!< Option byte 16: TMU access failure counter */

#define OPT17  (OPT_BaseAddress+0x7E)  //!< Option byte 17: BSL activation */
#define NOPT17 (OPT_BaseAddress+0x7F)  //!< Complementary Option byte 17 */


///////
// Cosmic compiler read/write macros. Required for missing far pointes in below SDCC 
///////
#if defined(__CSMC__)
  
  // read & write data from memory (16-bit address). For size use 16b pointers
  #if (ADDR_WIDTH==16)
    #define read_1B(addr)       (*((uint8_t*) addr))              /**< read 1B from 16-bit address */
    #define read_2B(addr)       (*((uint16_t*) addr))             /**< read 2B from 16-bit address */
    #define read_4B(addr)       (*((uint32_t*) addr))             /**< read 4B from 16-bit address */
    #define write_1B(addr,val)  *((uint8_t*) addr) = val          /**< write 1B to 16-bit address */
    #define write_2B(addr,val)  *((uint16_t*) addr) = val         /**< write 1B to 16-bit address */
    #define write_4B(addr,val)  *((uint32_t*) addr) = val         /**< write 1B to 16-bit address */
  
  // read & write data from memory (24-bit address). Use 24b far pointers
  #else
    #define read_1B(addr)       (*((@far uint8_t*) addr))         /**< read 1B from 24-bit address */
    #define read_2B(addr)       (*((@far uint16_t*) addr))        /**< read 2B from 24-bit address */
    #define read_4B(addr)       (*((@far uint32_t*) addr))        /**< read 4B from 24-bit address */
    #define write_1B(addr,val)  *((@far uint8_t*) addr) = val     /**< write 1B to 24-bit address */
    #define write_2B(addr,val)  *((@far uint16_t*) addr) = val    /**< write 1B to 24-bit address */
    #define write_4B(addr,val)  *((@far uint32_t*) addr) = val    /**< write 1B to 24-bit address */
  #endif


///////
// SDCC compiler read/write macros. Required for missing far pointes in SDCC 
///////
#elif defined(__SDCC)

  // read & write data from memory (16-bit address)
  #if (ADDR_WIDTH==16)
    #define read_1B(addr)       (*((uint8_t*) addr))              /**< read 1B from 16-bit address */
    #define read_2B(addr)       (*((uint16_t*) addr))             /**< read 2B from 16-bit address */
    #define read_4B(addr)       (*((uint32_t*) addr))             /**< read 4B from 16-bit address */
    #define write_1B(addr,val)  *((uint8_t*) addr) = val          /**< write 1B to 16-bit address */
    #define write_2B(addr,val)  *((uint16_t*) addr) = val         /**< write 1B to 16-bit address */
    #define write_4B(addr,val)  *((uint32_t*) addr) = val         /**< write 1B to 16-bit address */

  // read & write data from memory (24-bit address). SDCC doesn't support far pointers -> use inline assembly
  #else
    
    // global variables for interfacing with SDCC assembler
    #if defined(_EEPROM_MAIN_)
      volatile uint32_t          g_addr;         ///< address for interfacing to below assembler
      volatile uint8_t           g_valu8;        ///< 1B data for r/w via below assembler
      volatile uint32_t          g_valu32;       ///< 1B data for r/w via below assembler
      volatile uint32_t          g_mem_addr;     ///< address for interfacing to below assembler
      volatile uint32_t          g_mem_val;      ///< data for r/w via below assembler
    #else // _EEPROM_MAIN_
      extern volatile uint32_t   g_addr;
      extern volatile uint8_t    g_valu8;
      extern volatile uint32_t   g_valu32;
      extern volatile uint32_t   g_mem_addr;
      extern volatile uint32_t   g_mem_val;
    #endif // _EEPROM_MAIN_


    /**
      \fn uint8_t read_1B(uint32_t addr)
  
      \brief read 1 byte from memory (inline)
      
      \param[in] addr  address to read from

      \return 1B data read from memory

      Inline function to read 1B from memory. 
      Required for SDCC and >64kB due to lack of far pointers
    */
    inline uint8_t read_1B(uint32_t addr) {
      
      // pass data between C and assembler via global variables
      extern volatile uint32_t g_mem_addr = addr;
      extern volatile uint8_t  g_mem_val;            // use 8b of 32b variable

      // use inline assembler for actual read
      ASM_START
        ldf	a,[_g_mem_addr+1].e
        ld	_g_mem_val, a
      ASM_END

      // return data
      return(g_mem_val);

    } // read_1B


    /**
      \fn uint16_t read_2B(uint32_t addr)
  
      \brief read 2 bytes from memory (inline)
      
      \param[in] addr  address to read from

      \return 2B data read from memory

      Inline function to read 2B from memory. 
      Required for SDCC and >64kB due to lack of far pointers
    */
    inline uint16_t read_2B(uint32_t addr) {
      
      // pass data between C and assembler via global variables
      extern volatile uint32_t g_mem_addr = addr;
      extern volatile uint16_t g_mem_val;            // use 16b of 32b variable

      // use inline assembler for actual read
      ASM_START
        ldf	a,[_g_mem_addr+1].e
        ld	_g_mem_val,a
        ldw	x,#1
        ldf	a,([_g_mem_addr+1].e,x)
        ld	_g_mem_val+1,a
      ASM_END

      // return data
      return(g_mem_val);

    } // read_2B
  

    /**
      \fn uint16_t read_4B(uint32_t addr)
  
      \brief read 4 bytes from memory (inline)
      
      \param[in] addr  address to read from

      \return 4B data read from memory

      Inline function to read 4B from memory. 
      Required for SDCC and >64kB due to lack of far pointers
    */
    inline uint32_t read_4B(uint32_t addr) {
      
      // pass data between C and assembler via global variables
      extern volatile uint32_t g_mem_addr = addr;
      extern volatile uint32_t g_mem_val;

      // use inline assembler for actual read
      ASM_START
        ldf	a,[_g_mem_addr+1].e
        ld	_g_mem_val,a
        ldw	x,#1
        ldf	a,([_g_mem_addr+1].e,x)
        ld	_g_mem_val+1,a
        ldw	x,#2
        ldf	a,([_g_mem_addr+1].e,x)
        ld	_g_mem_val+2,a
        ldw	x,#3
        ldf	a,([_g_mem_addr+1].e,x)
        ld	_g_mem_val+3,a
      ASM_END

      // return data
      return(g_mem_val);

    } // read_4B
  

    /**
      \fn void write_1B(uint32_t addr, uint8_t val)
  
      \brief write 1 byte to memory (inline)
      
      \param[in] addr  address to read from
      \param[in] val   data to write

      Inline function to write 1B to memory. 
      Required for SDCC and >64kB due to lack of far pointers
    */
    inline void write_1B(uint32_t addr, uint8_t val) {
      
      // pass data between C and assembler via global variables
      extern volatile uint32_t g_mem_addr = addr;
      extern volatile uint8_t  g_mem_val  = val;     // use 8b of 32b variable

      // use inline assembler for actual write
      ASM_START
        ld	a,_g_mem_val
        ldf	[_g_mem_addr+1].e,a
      ASM_END

    } // write_1B

    
    /**
      \fn void write_2B(uint32_t addr, uint16_t val)
  
      \brief write 2 bytes to memory (inline)
      
      \param[in] addr  address to read from
      \param[in] val   data to write

      Inline function to write 2B to memory. 
      Required for SDCC and >64kB due to lack of far pointers
    */
    inline void write_2B(uint32_t addr, uint16_t val) {
      
      // pass data between C and assembler via global variables
      extern volatile uint32_t g_mem_addr = addr;
      extern volatile uint16_t g_mem_val  = val;     // use 16b of 32b variable

      // use inline assembler for actual write
      ASM_START
        ld	a,_g_mem_val
        ldf	[_g_mem_addr+1].e,a
        ld	a,_g_mem_val+1
        ldw	x,#1
        ldf	([_g_mem_addr+1].e,x),a
      ASM_END

    } // write_2B
  

    /**
      \fn void write_2B(uint32_t addr, uint32_t val)
  
      \brief write 4 bytes to memory (inline)
      
      \param[in] addr  address to read from
      \param[in] val   data to write

      Inline function to write 4B to memory. 
      Required for SDCC and >64kB due to lack of far pointers
    */
    inline void write_4B(uint32_t addr, uint32_t val) {
      
      // pass data between C and assembler via global variables
      extern volatile uint32_t g_mem_addr = addr;
      extern volatile uint32_t g_mem_val  = val;

      // use inline assembler for actual write
      ASM_START
        ld	a,_g_mem_val
        ldf	[_g_mem_addr+1].e,a
        ld	a,_g_mem_val+1
        ldw	x,#1
        ldf	([_g_mem_addr+1].e,x),a
        ld	a,_g_mem_val+2
        ldw	x,#2
        ldf	([_g_mem_addr+1].e,x),a
        ld	a,_g_mem_val+3
        ldw	x,#3
        ldf	([_g_mem_addr+1].e,x),a
      ASM_END

    } // write_4B

  #endif // (ADDR_WIDTH==32)

#endif // __SDCC



/*-----------------------------------------------------------------------------
    DEFINITION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

// option byte routines
uint8_t   OPT_writeByte(uint16_t addr, uint8_t data);            ///< write option byte (are in 16-bit range)
uint8_t   OPT_setDefault(void);                                  ///< revert to default option byte setting & reset on change
uint8_t   OPT_setBootloader(uint8_t state);                      ///< dis-/enable ROM bootloader & reset on change

// P-flash and EEPROM routines
uint8_t   flash_writeByte(MEM_POINTER_T physAddr, uint8_t data); ///< write 1B to P-flash (physical address)
uint8_t   EEPROM_writeByte(uint16_t logAddr, uint8_t data);      ///< write 1B to D-flash = EEPROM (logical address)
#define   EEPROM_readByte(logAddr) (*((uint8_t*) (EEPROM_START+logAddr))) ///< read 1B from D-flash = EEPROM (logical address)

// flash block must be executed from RAM. Not yet supported for SDCC
#if defined(__CSMC__)
  uint8_t   flash_eraseBlock(MEM_POINTER_T addr);                  ///< erase 128B block in flash
  uint8_t   flash_writeBlock(MEM_POINTER_T addr, uint8_t buf[]);   ///< write 128B block to flash
#endif

/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _EEPROM_H_
