/**********************
  Arduino-like project with setup() & loop().
  Periodically ramp potentiometer resistance attached to I2C (muBoard).
  Used 20kR potentiometer: Analog Devices AD5280BRUZ20 (Farnell 1438441).
  Connected via I2C pins PE1/SCL and PE2/SDA
  Functionality:
  - initialize I2C bus
  - periodically ramp resistance
  - print current value via UART1  
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "i2c.h"             // I2C communication
#include "uart1_blocking.h"  // minimal UART1 communication
#include "putchar.h"         // for printf()

// I2C address of potentiometer (see datasheet how to set)
#define ADDR_POTI  46


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// set resistance of potentiometer AD5280 via I2C
//////////
uint8_t setAD5280(uint8_t addr, uint8_t res) {
  
  uint8_t  err, buf[2] = {0x00, res};
  
  // set new resistance via I2C
  err  = i2c_start();             // generate start condition
  err |= i2c_send(addr,2,buf);    // send data
  err |= i2c_stop();              // generate stop condition

  // return error status
  return(err);

} // setAD5280



//////////
// user setup, called once after reset
//////////
void setup() {

  // init LCD. Use default I2C address
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
  
  static uint8_t  res = 0;                     // resistance in [Rmax/255]
  uint8_t         err, buf[2] = {0x00, 0x00};  // err state and I2C buffer
  
  // set new resistance
  buf[1] = res;
  err = setAD5280(ADDR_POTI, res);
  res += 8;

  // print to terminal
  printf("%d Ohm, err=%d\n", (int) (((long) res * 20000L) >> 8), (int) err);
      
  // wait a bit
  sw_delay(500);

} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
