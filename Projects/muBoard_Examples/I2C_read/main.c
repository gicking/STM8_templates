/**********************
  Arduino-like project with setup() & loop().
  Periodically request data from an Arduino configured as I2C slave.
  Arduino slave from example "Wire/slave sender".
  Connected via I2C pins PE1/SCL and PE2/SDA
  Functionality:
 - initialize I2C bus
 - periodically read data from Arduino ("hello ")
 - print data via UART1  
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "i2c.h"             // I2C communication
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()

// address of I2C slave (see Arduino example "Wire/slave sender")
#define ADDR_I2C  8


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // init I2C
  i2c_init();
  
  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  uint8_t   buf[10];    // I2C buffer
  uint8_t   err;        // I2C err state
  
  // read data from I2C slave
  err  = i2c_start();                   // generate start condition
  err |= i2c_request(ADDR_I2C,6,buf);   // send data
  err |= i2c_stop();                    // generate stop condition

  // terminate C-string for output
  buf[6] = '\0';

  // print I2C data to terminal ("hello ")
  printf("%ld  '%s', err=%d\n", millis(), buf, (int) err);
      
  // wait a bit
  sw_delay(1000);

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
