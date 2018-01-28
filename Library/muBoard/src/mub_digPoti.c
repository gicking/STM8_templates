/**
  \file mub_digPoti.c
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief implementation of function to control 20k digital poti
   
  implementation of function to control 20k digital poti via I2C. Type
  Analog Devices AD5280BRUZ20 (Farnell 1438441).
  Connect LCD I2C bus to STM8 SCL/SDA
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#define _MUB_DIGPOTI__MAIN_    // required for globals in mub_digPoti.h
  #include "mub_digPoti.h"
#undef _MUB_DIGPOTI__MAIN_
#include "i2c.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint8_t set_dig_poti(uint8_t res)
   
  \brief digital potentiometer control
   
  \param[in] res  new resistor value [0..255]
  
  \return  operation succeeded?
   
  set resistor btw terminal A and washer to 20kR/255*res. Resistance btw
  terminal B and washer to 20kR/255*(255-res)
*/
uint8_t set_dig_poti(uint8_t res) {

  // I2C Tx buffer
  uint8_t  buf[2], err;

  // set buffer
  buf[0] = 0x00;
  buf[1] = 0xFF-res; // invert value to have right R(A;washer) behaviour
  
  // generate start condition (w/ timeout)
  err  = i2c_start();
  
  // send command (w/ timeout)
  err |= i2c_send(MUB_ADDR_I2C_POTI,2,buf);    

  // generate stop condition (w/ timeout)
  err |= i2c_stop();

  // return error status
  return(err);

} // set_dig_poti


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
