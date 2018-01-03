/**
  \file eeprom.c
   
  \author G. Icking-Konert
  \date 2014-04-22
  \version 0.1
   
  \brief implementation of flash read/write routines
   
  implementation of flash/EEPROM read and write routines.
*/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#define _EEPROM_MAIN_
  #include "eeprom.h"
#undef _EEPROM_MAIN_


/**
  \fn uint8_t OPT_writeByte(uint16_t addr, uint8_t byte)
  
  \brief write option byte (are in 16-bit range)
  
  \param[in] addr   16b address of option byte to write
  \param[in] byte   byte to program
  
  \return byte changed (=1) or unchanged (=0)

  write single option byte to given address (16b sufficient for all devices).
  Only write if value needs to be changed.
*/
uint8_t OPT_writeByte(uint16_t addr, uint8_t byte) {

  uint8_t    countTimeout;   // use counter for timeout to minimize dependencies

  // check address range
  if ((addr < OPT_BaseAddress) || (addr >= OPT_BaseAddress+NUM_OPT))
    return(0);
  
  // skip write if value is already correct
  if ((*((uint8_t*) addr)) == byte)
    return(0);
  
  // begin critical cection (disable interrupts)
  CRITICAL_START;
  
  {
    // unlock w/e access to EEPROM & option bytes
    FLASH.DUKR.byte = 0xAE;
    FLASH.DUKR.byte = 0x56;
  
    // additionally required for option bytes
    FLASH.CR2.byte  |= 0x80;
    FLASH.NCR2.byte &= 0x7F;
  
    // wait until access granted
    while(!FLASH.IAPSR.reg.DUL);

    // write option byte to p-flash
    *((uint8_t*) addr) = byte;
  
    // wait until done or timeout (normal flash write measured with 0 --> 100 is more than sufficient)
    countTimeout = 100;                                // ~0.95us/inc -> ~0.1ms
    while ((!FLASH.IAPSR.reg.EOP) && (countTimeout--));
    
    // lock EEPROM again against accidental erase/write
    FLASH.IAPSR.reg.DUL = 0;
  
    // additional lock
    FLASH.CR2.byte  &= 0x7F;
    FLASH.NCR2.byte |= 0x80;
  }
  
  // critical section (restore interrupt setting)
  CRITICAL_END;

  // option byte changed -> return 1
  return(countTimeout != 0);

} // OPT_writeByte



/**
  \fn void OPT_setDefault(void)
  
  \brief revert to default option byte setting & reset on change
  
  assert that all option bytes have their default setting (see below).
  On change trigger a reset.
*/
void OPT_setDefault() {
  
  uint8_t  flagWD = 0;

  // reset alternate GPIO mapping (=OPT2/NOPT2)
  flagWD += OPT_writeByte(OPT2,  0x00);
  flagWD += OPT_writeByte(NOPT2, 0xFF);
  
  // deactivate watchdog (=OPT3/NOPT3)
  flagWD += OPT_writeByte(OPT3,  0x00);
  flagWD += OPT_writeByte(NOPT3, 0xFF);
  
  // reset clock options to default (=OPT4/NOPT4)
  flagWD += OPT_writeByte(OPT4,  0x00);
  flagWD += OPT_writeByte(NOPT4, 0xFF);
   
  // max. HCE clock startup time (=OPT5/NOPT5)
  flagWD += OPT_writeByte(OPT5,  0x00);
  flagWD += OPT_writeByte(NOPT5, 0xFF);
   
  // OPT6 is reserved/undocumented
   
  // no flash wait state (required for >16MHz) (=OPT7/NOPT7)
  flagWD += OPT_writeByte(OPT7,  0x00);
  flagWD += OPT_writeByte(NOPT7, 0xFF);
   
  // OPT8-16 contain temporary memory unprotection key (TMU) -> rather don't touch 

  // activate ROM-bootloader (=OPT17/NOPT17)  
  flagWD += OPT_writeByte(OPT17,  0x55);
  flagWD += OPT_writeByte(NOPT17, 0xAA);
 
  // if any option byte was changed trigger SW reset
  if (flagWD != 0)
    SW_RESET;

} // OPT_setDefault



/**
  \fn uint8_t OPT_setBootloader(uint8_t state)
  
  \brief dis-/enable ROM bootloader & reset on change
  
  \param[in] state  enable(=1) or disable(=0) bootloader
  
  write single byte to address in P-flash or EEPROM.
  On change trigger a reset.
  For address width see file stm8as.h
*/
void OPT_setBootloader(uint8_t state) {
  
  uint8_t   flag = 0;
  
  // activate ROM-bootloader (=OPT17/NOPT17)  
  if (state) {
    flag += OPT_writeByte(OPT17,  0x55);
    flag += OPT_writeByte(NOPT17, 0xAA);
  }
  
  // deactivate bootloader
  else {
    flag += OPT_writeByte(OPT17,  0x00);
    flag += OPT_writeByte(NOPT17, 0x00);
  }
 
  // if option byte was changed trigger SW reset
  if (flag != 0)
    SW_RESET;

} // OPT_setBootloader



/**
  \fn uint8_t flash_writeByte(MEM_POINTER_T physAddr, uint8_t data)
  
  \brief write 1B to P-flash (physical address)
  
  \param[in] physAddr   physical address to write to
  \param[in] data       byte to program
  
  \return write successful(=1) or error(=0)

  write single byte to physical address in P-flash. 
  For memory size and address width see file stm8as.h
  
  Warning: for simplicity no safeguard is used to protect against
  accidental data loss or even overwriting the application -> use with care!
*/
uint8_t flash_writeByte(MEM_POINTER_T physAddr, uint8_t data) {

  uint8_t    countTimeout;   // use counter for timeout to minimize dependencies
  
  // address range check
  if ((physAddr < (uint32_t) (PFLASH_START)) || (physAddr > (uint32_t) (PFLASH_END)))
    return;
  
  // begin critical cection (disable interrupts)
  CRITICAL_START;
  
  {
    // unlock w/e access to P-flash
    FLASH.PUKR.byte = 0x56;
    FLASH.PUKR.byte = 0xAE;
    
    // wait until access granted
    while(!FLASH.IAPSR.reg.PUL);
  
    // write byte using 16-bit or 32-bit macro/function (see flash.h)
    write_1B(physAddr, data);

    // wait until done or timeout (normal flash write measured with 0 --> 100 is more than sufficient)
    countTimeout = 100;                                // ~0.95us/inc -> ~0.1ms
    while ((!FLASH.IAPSR.reg.EOP) && (countTimeout--));
    
    // lock P-flash again against accidental erase/write
    FLASH.IAPSR.reg.PUL = 0;  
  }
  
  // critical section (restore interrupt setting)
  CRITICAL_END;

  // write successful -> return 1
  return(countTimeout != 0);

} // flash_writeByte



/**
  \fn uint8_t EEPROM_writeByte(uint16_t logAddr, uint8_t data)
  
  \brief write 1B to D-flash = EEPROM (logical address)
  
  \param[in] logAddr    logical address to write to
  \param[in] data       byte to program
  
  \return write successful(=1) or error(=0)

  write single byte to physical address in D-flash = EEPROM. 
  For memory size and address width see file stm8as.h
*/
uint8_t EEPROM_writeByte(uint16_t logAddr, uint8_t data) {

  uint8_t    countTimeout;   // use counter for timeout to minimize dependencies
  uint16_t   addr = EEPROM_START+logAddr; 
  
  // address range check
  if (logAddr > EEPROM_SIZE)
    return;
  
  // begin critical cection (disable interrupts)
  CRITICAL_START;
  
  {
    // unlock w/e access to EEPROM
    FLASH.DUKR.byte = 0xAE;
    FLASH.DUKR.byte = 0x56;
    
    // wait until access granted
    while(!FLASH.IAPSR.reg.DUL);
  
    // write byte using 16-bit or 32-bit macro/function (see flash.h)
    write_1B(addr, data);

    // wait until done or timeout (normal flash write measured with 0 --> 100 is more than sufficient)
    countTimeout = 100;                                // ~0.95us/inc -> ~0.1ms
    while ((!FLASH.IAPSR.reg.EOP) && (countTimeout--));
    
    // lock EEPROM again against accidental erase/write
    FLASH.IAPSR.reg.DUL = 0;
  }
  
  // critical section (restore interrupt setting)
  CRITICAL_END;

  // write successful -> return 1
  return(countTimeout != 0);

} // EEPROM_writeByte


// only required for flash block write/erase operations (need to be executed from RAM!)
#if defined(__CSMC__) && defined(FLASH_BLOCK_OPS)

  xxx  check if this also works for SDCC

  // start RAM code section (Cosmic compiler)
  #pragma section (RAM_CODE)
  
  /**
    \fn uint8_t flash_eraseBlock(MEM_POINTER_T addr)
    
    \brief erase 128B block in P-flash (must be executed from RAM)
    
    \param[in] addr   address of block to erase
  
    \return write successful(=1) or error(=0)
  
    erase 128B flash block which contains addr. 
    Actual code for block erase needs to be executed from RAM
    For address width see file stm8as.h
    
    Warning: for simplicity no safeguard is used to protect against
    accidental data loss or even overwriting the application -> use with care!
  */
  uint8_t flash_eraseBlock(MEM_POINTER_T addr) {
  
    uint8_t    countTimeout;   // use counter for timeout to minimize dependencies
  
    // begin critical cection (disable interrupts)
    CRITICAL_START;
  
    {
      // unlock w/e access to P-flash
      FLASH.PUKR.byte = 0x56;
      FLASH.PUKR.byte = 0xAE;
  
  
      /////////////// start min. code section in RAM... /////////////////
  
      // enable p-flash erase
      FLASH.CR2.reg.ERASE   = 1;
      FLASH.NCR2.reg.ERASE  = 0;      // complementary register
  
      // wait until access granted
      countTimeout = 100;                                // ~0.95us/inc -> ~0.1ms
      while ((!FLASH.IAPSR.reg.PUL) && (countTimeout--));
  
      // init erwase by writing 0x00 to 4B word inside page
      write_4B(addr, 0x00000000);
  
      /////////////// ...until here /////////////////

      
      // lock P-flash again against accidental erase/write
      FLASH.IAPSR.reg.PUL = 0;
    }
  
    // critical section (restore interrupt setting)
    CRITICAL_END;

    // write successful -> return 1
    return(countTimeout != 0);

  } // flash_eraseBlock
  
  
  
  /**
    \fn void flash_writeBlock(MEM_POINTER_T addr, uint8_t ch[])
    
    \brief write 128B block to flash (must be executed from RAM)
    
    \param[in] addr   address to write to (for width see stm8as.h)
    \param[in] buf    128B buffer to write
  
    Fast write 128B block to flash (adress must be divisable by 128)
    Actual code for block write needs to be executed from RAM
    For address width see file stm8as.h
    
    Warning: for simplicity no safeguard is used to protect against
    accidental data loss or even overwriting the application -> use with care!
  */
  void flash_writeBlock(MEM_POINTER_T addr, uint8_t buf[]) {
    
    uint8_t    i;
    uint8_t    countTimeout;   // use counter for timeout to minimize dependencies
  
    // begin critical cection (disable interrupts)
    CRITICAL_START;
  
    {
      // unlock w/e access to P-flash
      FLASH.PUKR.byte = 0x56;
      FLASH.PUKR.byte = 0xAE;
    
      // wait until access granted
      countTimeout = 100;                                // ~0.95us/inc -> ~0.1ms
      while ((!FLASH.IAPSR.reg.PUL) && (countTimeout--));
    
  
      /////////////// start min. code section in RAM... /////////////////
  
      // set fast block programming mode
      FLASH.CR2.reg.FPRG  = 1;
      FLASH.NCR2.reg.FPRG = 0;
  
      // copy 128B to latch
      for (i=0; i<128; i++)
        write_1B(addr+i, buf[i]);
  
      /////////////// ...until here /////////////////
  

      // lock P-flash and EEPROM again against accidental erase/write
      FLASH.IAPSR.reg.PUL = 0;
      FLASH.IAPSR.reg.DUL = 0;
    }
  
    // critical section (restore interrupt setting)
    CRITICAL_END;

    // write successful -> return 1
    return(countTimeout != 0);

  } // flash_writeBlock
  
  
  // end RAM code section (Cosmic compiler)
  #pragma section ()

#endif // __CSMC__ && FLASH_BLOCK_OPS

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
