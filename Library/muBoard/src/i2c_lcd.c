/**
  \file i2c_lcd.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of 2x16 LCD output functions/macros
   
  implementation of functions for printing strings via I2C to 2x16 LCD
  Batron BTHQ21605V-COG-FSRE-I2C (Farnell 1220409).
  Connect LCD I2C bus to STM8 SCL/SDA, and LCD reset pin to STM8 pin PE3
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stm8as.h"
#define _I2CLCD_MAIN_          // required for globals in i2c_lcd.h
  #include "i2c_lcd.h"
#undef _I2CLCD_MAIN_
#include "i2c.h"
#include "gpio.h"
#include "sw_delay.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/
 
#define LCD_ADDR_I2C  59                            ///< default I2C addresses of LCD display
volatile uint8_t   lcd_addr_i2c = LCD_ADDR_I2C;     ///< I2C address of LCD display


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint8_t lcd_init(uint8_t addr)
   
  \brief initialize LCD for output
  
  \param[in]  addr   I2C address to use (or '0' for default)

  \return is an LCD attached?

  Initialize LCD for output.
  Also check if LCD display is attached via bus timeout 
*/
uint8_t lcd_init(uint8_t addr) {

  uint8_t   status;
  

  ////
  // check if LCD present by sending a dummy frame
  ////
  
  // if specified, change I2C address for display
  if (addr != 0)
    lcd_addr_i2c = addr;
  
  // generate start condition
  i2c_start();
  
  // send dummy frame (with timeout)
  status = (uint8_t) (i2c_send(lcd_addr_i2c, 0, NULL));

  // generate stop condition
  i2c_stop();
  
  
  // if LCD is present clear it
  if (status) 
    lcd_clear();
  
  // return LCD status
  return(status);

} // lcd_init



/**
  \fn void clear_lcd(void)
   
  \brief clear LCD display
  
  clear both lines of LCD display  
*/
void lcd_clear() {

  uint8_t   str[1];
  
  // print empty lines to both lines clears LCD
  sprintf(str, "");
  lcd_print(1, 1, str);
  lcd_print(2, 1, str);

} // lcd_clear



/**
  \fn void lcd_print(uint8_t line, uint8_t col, char *s)
   
  \brief print to LCD display
  
  \param[in]  line    line to print to (1 or 2)
  \param[in]  col     column to start at
  \param[in]  s       string to print

  print up to 16 chars to line in LCD display
  
*/
void lcd_print(uint8_t line, uint8_t col, char *s) {

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
  i2c_send(lcd_addr_i2c, i, s2);
  

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
  i2c_send(lcd_addr_i2c, 17, s2);

  // generate stop condition
  i2c_stop();
  
  // wait until bus is free (with timeout)
  i2c_waitFree();

} // lcd_print


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
