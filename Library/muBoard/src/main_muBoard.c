/**
  \file main_muBoard.c
   
  \author G. Icking-Konert
  \date 2017-02-19
  \version 0.1
   
  \brief implementation of a general main() with board specific initialization
   
  implementation of a muBoard-specific, Arduino-like main() routine with
  initialization. 
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#define _MUBOARD_MAIN_
  #include "main_muBoard.h"
#undef _MUBOARD_MAIN_


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void muBoard_resetHardware(void)
   
  \brief initialize muBoard modules
  
  initialize all STM8 and muBoard modules
*/
void muBoard_resetHardware(void) {

  // switch to 16MHz (default is 2MHz)
  CLK.CKDIVR.byte = 0x00;
  
  // init STM8 and muBoard modules
  muBoard_io_init();

  // initialize STM8 GPIOs
  muBoard_io_init();

  // init 1ms SW clock
  TIM4_init();

  // init ADC2 for measuring poti 
  ADC2_init(ADC_SINGLE_SHOT);

  // init I2C bus
  i2c_init();

  // reset and init LCD display
  lcd_init(&PORT_E, 3);

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

} // muBoard_resetHardware



/**
  \fn void main(void)
     
  \brief actual main routine of program
    
  actual main routine of program with general initialization
  and start of SW clock via TIM4.
  From here user setup and loop is called.  
*/
void main(void)
{
  uint8_t   flagReset;
  uint16_t  countTimeout;     // for resonator timeout
  

  /////////////////
  // init STM8 & muBoard
  /////////////////

  // globally disable interrupts
  DISABLE_INTERRUPTS;

  // switch to external 16MHz clock
  CLK.SWCR.reg.SWIF = 0;          // reset clk ISR flag
  CLK.SWR.reg.SWI = 0xB4;         // select target clock source to external
  countTimeout = 10000;           // ~1.1us/inc -> ~10ms
  while ((!CLK.SWCR.reg.SWIF) && (countTimeout--)); // wait for HSE stable or timeout
  if (CLK.SWCR.reg.SWIF)          // external resonator stable -> execute switch
    CLK.SWCR.reg.SWEN = 1;
 
  
  // init STM8 and muBoard modules
  muBoard_resetHardware();
  
  // set default seed for random()
  randomSeed(1);
  
  
  // assert option byte for using PD4 for beeper
  flagReset  = OPT_writeByte(OPT2,  0x80);
  flagReset |= OPT_writeByte(NOPT2, 0x7F);

  // if automode switch is on (=low), activate bootloader
  if (AUTO_MODE == 0)
    flagReset |= OPT_setBootloader(true);
  else
    flagReset |= OPT_setBootloader(false);

  // if any option byte has changer, trigger reset
  if (flagReset)
    SW_RESET;
  
  
  // measure Vcore to determine if Vdd=5V or 3.3V
  if (ADC2_measure_single(ADC_VCORE) < 464)
    g_Vdd = 5;
  else
    g_Vdd = 3;


  // print start message on LCD
  lcd_clear();
  lcd_print(1, 1, " Bosch muBoard ");
  if (g_Vdd == 5)
    lcd_print(2, 1, "   5V C-control");
  else
    lcd_print(2, 1, " 3.3V C-control");
  if (!(CLK.SWCR.reg.SWIF))
    lcd_print(2, 6, "*");
  sw_delay(2000);
  lcd_clear();
  
  
  // globally enable interrupts
  ENABLE_INTERRUPTS;   


  /////////////////
  // call user setup()
  /////////////////
  setup();


  /////////////////
  // main loop
  /////////////////
  while (1) {
    
    // call user loop function
    loop();

  } // main loop

} // main


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
