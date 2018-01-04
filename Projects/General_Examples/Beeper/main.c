/**********************
  Arduino-like project with setup() & loop(). 
  Demonstrate tone output via beeper module.
  Beeper requires option byte AFR7=1 for alternate usage of BEEP pin 
  Functionality:
  - assert option byte setting for beeper output 
  - play tones with different pitch
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"   // board-independent main
#include "eeprom.h"
#include "tone.h"


/*----------------------------------------------------------
    MACROS
----------------------------------------------------------*/

/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {

  // assert option byte for using PD4 for beeper. See STM8 UM for details
  uint8_t flagChanged = 0;  
  flagChanged += OPT_writeByte(OPT2,  0x80);
  flagChanged += OPT_writeByte(NOPT2, 0x7F);

  // if changed, trigger reset
  if (flagChanged)
    SW_RESET;

} // setup



//////////
// user loop, called continuously
//////////
void loop() {

  uint16_t freq;
  
  for (freq=500; freq<=4000; freq+=100) {
    tone(freq,0);
    sw_delay(75);
  }
  tone(0,0);
  sw_delay(1500);

} // loop

