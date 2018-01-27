/**
  \file pulse.c
   
  \author G. Icking-Konert
  \date 2018-01-25
  \version 0.1
   
  \brief implementation of pulseIn()
   
  implementation of routine to measure pulse durations (blocking).
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "pulse.h"
#include "timer4.h"
#include <stdio.h>


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint32_t pulseIn(PORT_t *pPort, uint8_t pin, uint8_t state, uint32_t timeout)
   
  \brief measure pulse duration without timepout (caution!)
  
  \param[in]  pPort    pointer to port to measure, e.g. &PORT_A
  \param[in]  pin      pin number to measure
  \param[in]  state    polarity to measure (HIGH/1 or LOW/0)
  \param[in]  timeout  timeout in milliseconds
  
  \return duration of the pulse in microseconds, or 0 on timeout
  
  Measures the duration of a pulse on a pin. For example, if state==HIGH, 
  starts timing when the pin goes HIGH and stops it when it goes LOW again.
  Function returns 0 if a timeout occurred.
*/
uint32_t pulseIn(PORT_t *pPort, uint8_t pin, uint8_t state, uint16_t timeout) {
  
  volatile uint32_t   timeoutStart;
  volatile uint32_t   start, stop;
  
  // for speed use bit masks
  volatile uint8_t pinMask = (0x01 << pin);
  volatile uint8_t stateMask = 0x00;
	if (state) 
	  stateMask = (0x01 << pin);
		
  // for timeout
	timeoutStart = millis();

	// wait for any previous pulse to end
	while ((((pPort)->IDR.byte) & pinMask) == stateMask) {
		if (millis() - timeoutStart > timeout)
			return 0;
	}

	// wait for the pulse to start
	while ((((pPort)->IDR.byte) & pinMask) != stateMask) {
		if (millis() - timeoutStart > timeout)
			return 0;
	}
	
  // start measurement
	start = micros();

	// wait for the pulse to stop
	while ((((pPort)->IDR.byte) & pinMask) == stateMask) {
		if (millis() - timeoutStart > timeout)
			return 0;
	}
	
  // stop measurement
	stop = micros();

  // return pulse duration
  return(stop-start);

} // pulseIn


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
