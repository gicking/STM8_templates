/**
  \file main_general.c
   
  \author G. Icking-Konert
  \date 2017-02-19
  \version 0.1
   
  \brief implementation of a general main() with minimal initialization
   
  implementation of a general, Arduino-like main() routine with minimal
  initialization. Only FCPU is set to 16MHz and SW-clock ist started.
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "main_general.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void main(void)
     
  \brief actual main routine of program
    
  actual main routine of program with general initialization
  and start of SW clock via TIM4.
  From here user setup and loop is called.  
*/
void main(void)
{

  /////////////////
  // init modules
  /////////////////

  // globally disable interrupts
  DISABLE_INTERRUPTS;

  // switch to 16MHz (default is 2MHz)
  CLK.CKDIVR.byte = 0x00;  
  
  // init 1ms SW clock
  TIM4_init();

  // set default seed for random()
  randomSeed(1);

  // globally enable interrupts
  ENABLE_INTERRUPTS;   
  
  // call user setup function
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
