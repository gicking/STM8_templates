/**
  \file lcd-BTHQ21605V.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of 2x16 I2C LCD functions for BTHQ21605V-COG-FSRE-I2C
   
  implementation of functions for printing strings via I2C to 2x16 LCD
  Batron BTHQ21605V-COG-FSRE-I2C (Farnell 1220409).
  Connect LCD I2C bus to STM8 SCL/SDA, and LCD reset pin to any STM8 GPIO
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stm8as.h"
#include "i2c.h"
#include "gpio.h"
#include "sw_delay.h"
#define _BTHQ21605V_MAIN_
  #include "lcd-BTHQ21605V.h"
#undef _BTHQ21605V_MAIN_


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint8_t BTHQ21605V_lcd_init(PORT_t *pPortRST, uint8_t pinRST)
   
  \brief reset and initialize LCD for output
  
  \param[in]  pPortRST  pointer to port for LCD reset, e.g. &PORT_A
  \param[in]  pinRST    pin for LCD reset (0..7)
  
  \return is an LCD attached?

  Reset and rnitialize LCD for output.
  Check if LCD display is attached via bus timeout 
*/
uint8_t BTHQ21605V_lcd_init(PORT_t *pPortRST, uint8_t pinRST) {

  uint8_t   status;
  
  // reset LCD via **high** pulse
  pinMode(pPortRST, pinRST, OUTPUT);
  pinHigh(pPortRST, pinRST);
  sw_delay(50);
  pinLow(pPortRST, pinRST);


  ////
  // check if LCD present by sending a dummy frame
  ////
  
  // generate start condition
  i2c_start();

  // send dummy frame (with timeout)
  status = (uint8_t) (i2c_send(ADDR_I2C_BTHQ21605V, 0, NULL));

  // generate stop condition
  i2c_stop();
  
  
  // if LCD is present clear it
  if (status) 
    BTHQ21605V_lcd_clear();
  
  // return LCD status
  return(status);

} // BTHQ21605V_lcd_init



/**
  \fn void BTHQ21605V_clear_lcd(void)
   
  \brief clear LCD display
  
  clear both lines of LCD display  
*/
void BTHQ21605V_lcd_clear() {

  uint8_t   str[1];
  
  // print empty lines to both lines clears LCD
  sprintf(str, "");
  BTHQ21605V_lcd_print(1, 1, str);
  BTHQ21605V_lcd_print(2, 1, str);

} // BTHQ21605V_lcd_clear



/**
  \fn void BTHQ21605V_lcd_print(uint8_t line, uint8_t col, char *s)
   
  \brief print to LCD display
  
  \param[in]  line    line to print to (1 or 2)
  \param[in]  col     column to start at
  \param[in]  s       string to print

  print up to 16 chars to line in LCD display
  
*/
void BTHQ21605V_lcd_print(uint8_t line, uint8_t col, char *s) {

  uint8_t   s2[21];
  uint8_t   len;
  uint8_t   i, j;


  //////
  // config display
  //////
  i = 0;
  s2[i++] = 0x00;                   // control byte 'config mode'
  s2[i++] = 0x34;                   // command 'function set'
  s2[i++] = 0x0C;                   // command 'display on'
  s2[i++] = 0x06;                   // command 'entry mode'
  if (line == 1)
    s2[i++] = (uint8_t)(0x80 + col - 1); // DRAM adress offset for line 1 + column
  else
    s2[i++] = (uint8_t)(0xC0 + col - 1); // DRAM adress offset for line 2

  
  // wait until bus is free (with timeout)
  i2c_waitFree();
  
  // generate start condition (with timeout)
  i2c_start();

  // send data (with timeout)
  i2c_send(ADDR_I2C_BTHQ21605V, i, s2);
  

  //////
  // send string
  //////

  // init array to SPC
  for (i=0; i<20; i++)
    s2[i] = 0xA0;
  
  i = 0;
  s2[i++] = 0x40;     // control byte 'write data'
  
  // copy string
  len = (uint8_t) strlen(s); 
  for (j=0; (j<len) && (j<21); j++) {
  
    // replace TAB, CR, LF, BEL with SPC
    if ((s[j] == '\t') || (s[j] == '\r') || (s[j] == '\n') || (s[j] == 7))
      s2[i++] = 0xA0;
    
    // convert ASCII to lcd char set (+128)
    else
      s2[i++] = (uint8_t)(s[j] | 0x80);
  
  }

  // generate start condition again to witch to "write data" mode
  i2c_start();

  // send to LCD (with timeout)
  i2c_send(ADDR_I2C_BTHQ21605V, 17, s2);

  // generate stop condition
  i2c_stop();
  
  // wait until bus is free (with timeout)
  i2c_waitFree();

} // BTHQ21605V_lcd_print


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
