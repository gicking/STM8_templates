/**********************
  Arduino-like project with setup() & loop(). Write data 
  to EEPROM and read back.
  Functionality:
    - configure UART1 and putchar() for PC output
    - save data to EEPROM
    - read from EEPROM and print to terminal 
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include <stdio.h>
#include "main_general.h"    // board-independent main
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()
#include "eeprom.h"          // for EEPROM read/write


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  uint16_t i;

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

  // wait for terminal ready
  sw_delay(1000);

  // write some data to EEPROM
  printf("start EEPROM write ... ");
  for (i=0; i<100; i++)
    EEPROM_writeByte(i, i+1);
  printf("done\n\n");
  
  // read data from EEPROM and send to UART
  printf("EEPROM size is %dB\n", EEPROM_SIZE);
  for (i=0; i<10; i++) {
    printf("  %d -> %d\n", (int) i, (int) (EEPROM_readByte(i)));        // read EEPROM logical address
    //printf("  %d -> %d\n", (int) i, (int) (read_1B(EEPROM_START+i)));   // read physical address
  }

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  // dummy. Action happens in setup()

} // loop

