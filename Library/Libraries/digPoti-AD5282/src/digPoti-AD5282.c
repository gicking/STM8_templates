/**
  \file digPoti-AD5282.c
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief implementation of control for digital poti AD5282
   
  implementation of function to control digital poti AD5282 (Farnell 1438442, 200k)
  via I2C. Connect SCL/SDA of digital poti and of STM8 
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#include "i2c.h"
#define _AD5282_MAIN_
  #include "digPoti-AD5282.h"
#undef _AD5282_MAIN_


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint8_t AD5282_set_poti(uint8_t res)
   
  \brief 2-channel digital potentiometer control
   
  \param[in] ch   channel to set (0,1)
  \param[in] res  new resistor value [0..255]
  
  \return  operation succeeded?
   
  set resistance btw terminal A and washer ch to Rmax/255*res. Resistance btw
  terminal B and washer to Rmax/255*(255-res)
*/
uint8_t AD5282_set_poti(uint8_t ch, uint8_t res) {

  // I2C Tx buffer
  uint8_t  buf[2], err;

  // set buffer
  if (ch == 0)
    buf[0] = 0x00;    // channel A
  else
    buf[0] = 0x80;    // channel B
  buf[1] = res;       // resistance
  
  // generate start condition (w/ timeout)
  err  = i2c_start();
  
  // send command (w/ timeout)
  err |= i2c_send(ADDR_I2C_AD5282,2,buf);    

  // generate stop condition (w/ timeout)
  err |= i2c_stop();

  // return error status
  return(err);

} // AD5282_set_poti


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
