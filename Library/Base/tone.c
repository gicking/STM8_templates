/**
  \file tone.c
   
  \author G. Icking-Konert
  \date 2013-11-22
  \version 0.1
   
  \brief implementation of beeper control
   
  implementation of functions for beeper control to play tone.
  Note that the beeper has very coarse resolution!
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stm8as.h"
#include "tone.h"
#include "sw_delay.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void tone(uint16_t freq, uint16_t duration)
   
  \brief play tone via beeper module
   
  \param[in] freq       tone frequency [Hz] in [500Hz; 32kHz] (freq<500Hz stops tone)
  \param[in] duration   blocking tone duration [ms] (0=start beep and continue)
  
  play tone via the beeper module with frequency and duration. Note that the
  beeper module has very coarse resolution -> for music use real timer, not beeper
*/
void tone(uint16_t freq, uint16_t duration) {

  uint8_t   SEL, DIV;
  uint32_t  beepFreq;
  
  // switch off and reset
  BEEP.CSR.byte = 0x00;
  
  // switch off, respectively select optimum prescaler (=SEL)
  if (freq < 500) {
    BEEP.CSR.reg.BEEPEN  = 0;
    return;
  } 
  else if (freq < 1000) {
    BEEP.CSR.reg.BEEPSEL = 0;  // -> 16kHz
    beepFreq = 16000L;
  } 
  else if (freq < 2000) {
    BEEP.CSR.reg.BEEPSEL = 1;  // -> 32kHz
    beepFreq = 32000L;
  } 
  else {
    BEEP.CSR.reg.BEEPSEL = 2;  // -> 64kHz
    beepFreq = 64000L;
  }
  
  // calculate optimum counter (=DIV)
  DIV = (uint8_t) ((beepFreq / (uint32_t) freq) - 2L);
  if (DIV > 0x1E)
    DIV = 0x1E;
  BEEP.CSR.reg.BEEPDIV = DIV;
 
  // switch on beeper
  BEEP.CSR.reg.BEEPEN  = 1;

  // if duration >0 -> wait time [ms], then disable beeper
  if (duration > 0) {
    sw_delay(duration);
    BEEP.CSR.reg.BEEPEN  = 0;    // disable beeper
  }

} // tone


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
