/**
  \file digPoti-AD5280.c
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief implementation of control for digital poti AD5280
   
  implementation of function to control digital poti AD5280 (Farnell 1438441, 20k)
  via I2C. Connect SCL/SDA of digital poti and of STM8 
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#include "i2c.h"
#define _AD5280_MAIN_
  #include "digPoti-AD5280.h"
#undef _AD5280_MAIN_


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint8_t AD5280_set_poti(uint8_t res)
   
  \brief digital potentiometer control
   
  \param[in] res  new resistor value [0..255]
  
  \return  operation succeeded?
   
  set resistance btw terminal A and washer to Rmax/255*res. Resistance btw
  terminal B and washer to Rmax/255*(255-res)
*/
uint8_t AD5280_set_poti(uint8_t res) {

  // I2C Tx buffer
  uint8_t  buf[2], err;

  // set buffer
  buf[0] = 0x00;
  buf[1] = res;
  
  // generate start condition (w/ timeout)
  err  = i2c_start();
  
  // send command (w/ timeout)
  err |= i2c_send(ADDR_I2C_AD5280,2,buf);    

  // generate stop condition (w/ timeout)
  err |= i2c_stop();

  // return error status
  return(err);

} // AD5280_set_poti


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
