/**********************
  Arduino-like project with setup() & loop(). 
  Write data to P-flash and read back.
  Functionality:
  - configure UART1
  - configure putchar() for PC output via UART1
  - save data to P-flash (take care not to overwrite application)
  - read from P-flash and print to terminal 
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include <stdio.h>
#include "main_general.h"    // board-independent main
#include "uart1.h"           // UART1 communication
#include "putchar.h"         // for printf()
#include "eeprom.h"          // for EEPROM read/write


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

// start address
#define ADDR_START  0xF000     // 16-bit range
//#define ADDR_START  0x10000    // 32-bit range


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  uint32_t i;

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

  // wait for terminal ready
  sw_delay(1000);

  // write some data to P-flash
  #if (ADDR_START < 0x10000)
    printf("start P-flash write at 0x%04x ... ", ADDR_START);
  #else
    printf("start P-flash write at 0x%06lx ... ", ADDR_START);
  #endif
  for (i=0; i<100; i++)
    flash_writeByte(ADDR_START+i, i+1);
  printf("done\n\n");
  
  // read data from P-flash and send to UART
  for (i=0; i<10; i++) {
    printf("  %d -> %d\n", (int) i, (int) (read_1B(ADDR_START+i)));   // read physical address
  }

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  // dummy. Action happens in setup()

} // loop

