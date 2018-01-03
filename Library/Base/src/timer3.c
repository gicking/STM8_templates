/**
  \file timer3.c
   
  \author G. Icking-Konert
  \date 2017-12-30
  \version 0.1
   
  \brief implementation of TIM3 functions/macros 
   
  implementation of timer TIM3 functions, currently for (mutually exclusive)
    - generating PWM signals
    - high accuracy delay* functions
  Optional functionality via #define:
    - USE_TIM3_UPD_ISR:    call TIM4 update/overflow ISR
    - USE_TIM3_CAPCOM_ISR: call TIM3 capture/compare ISR
*/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "stm8as.h"
#include "config.h"
#define _TIM3_MAIN_          // required for globals in timer4.h
  #include "timer3.h"
#undef _TIM3_MAIN_
#include "misc.h"


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void TIM3_init(void)
   
  \brief init timer 3
   
  init timer TIM3, i.e. reset to default values
*/
void TIM3_init(void) {

  // (mainly) stop timer
  TIM3.CR1.byte = TIM3_CR1_RESET_VALUE;

  // disable TIM3 interrupts
  TIM3.IER.byte = TIM3_IER_RESET_VALUE;
  
  // reset status registers
  TIM3.SR1.byte = TIM3_SR1_RESET_VALUE;
  TIM3.SR2.byte = TIM3_SR2_RESET_VALUE;

  // 
  TIM3.EGR.byte = TIM3_EGR_RESET_VALUE;

  // reset PWM mode
  TIM3.CCMR1.byte = TIM3_CCMR1_RESET_VALUE;
  TIM3.CCMR2.byte = TIM3_CCMR2_RESET_VALUE;
  
  // 
  TIM3.CCER1.byte = TIM3_CCER1_RESET_VALUE;

  // reset counter register (write high byte first)
  TIM3.CNTR.byteH = TIM3_CNTRH_RESET_VALUE;
  TIM3.CNTR.byteL = TIM3_CNTRL_RESET_VALUE;
  
  // set prescaler to fclk/2^4 -> 1us resolution (not default) for delayMicroseconds()
  TIM3.PSCR.reg.PSC = 4;
  
  // set max period
  TIM3.ARR.byteH = TIM3_ARRH_RESET_VALUE;
  TIM3.ARR.byteL = TIM3_ARRL_RESET_VALUE;

  // reset duty cycles
  TIM3.CCR1.byteH = TIM3_CCR1H_RESET_VALUE;
  TIM3.CCR1.byteL = TIM3_CCR1L_RESET_VALUE;
  TIM3.CCR2.byteH = TIM3_CCR2H_RESET_VALUE;
  TIM3.CCR2.byteL = TIM3_CCR2L_RESET_VALUE;
  
  // request register update
  TIM3.EGR.reg.UG = 1;

} // TIM3_init



/**
  \fn void TIM3_delay(uint32_t dt)

  \brief delay code execution for 'ms' using timer 3
   
  \param[in] ms   pause duration in ms
   
  code execution is halted for specified number of milliseconds
  using timer 3 -> more accurate than sw_delay() or delay(). 
*/
void TIM3_delay(uint32_t ms) {

  // for simplicity use below TIM3_delayMicroseconds()
  while (ms) {
    TIM3_delayMicroseconds(1000);
    ms--;
  }
    
} // TIM3_delay



/**
  \fn void TIM3_delayMicroseconds(uint16_t dt)

  \brief halt code execution for specified microseconds
   
  \param dt halt duration in us
   
  code execution is halted for specified number of microseconds
  using timer 3 -> more accurate than sw_delay() or delay(). 
  Note: measured overhead is ~5.5us 
*/
void TIM3_delayMicroseconds(uint16_t dt) {
  
  // stop timer
  TIM3.CR1.reg.CEN = 0;

  // set prescaler to fclk/2^4 -> 1MHz clock -> 1us resolution
  TIM3.PSCR.reg.PSC = 4;
  
  // set timout to dt us (freq_Hz=fclk/(prescaler*ARR)) (write high byte first)
  TIM3.ARR.byteH = (uint8_t) (dt >> 8);
  TIM3.ARR.byteL = (uint8_t) dt;
  
  // reset counter register (write high byte first)
  TIM3.CNTR.byteH = (uint8_t) 0;
  TIM3.CNTR.byteL = (uint8_t) 0;
      
  // disable update interrupt 
  TIM3.IER.reg.UIE = 0;

  // request register update
  TIM3.EGR.reg.UG = 1;
  
  // start the timer
  TIM3.CR1.reg.CEN = 1;
  
  // clear status registers (do this last)
  TIM3.SR1.byte = 0x00;
  
  // on zero delay return. Do here to have similar overhead for dt=0
  if (!dt)
    return;
  
  // wait for overflow (no interrupts!)
  while (!(TIM3.SR1.reg.UIF));
    
} // TIM3_delayMicroseconds



/**
  \fn void TIM3_delayNanoseconds(uint16_t dt)

  \brief delay code execution for dt*62.5ns using timer 3
   
  \param dt halt duration in 62.5ns units
   
  code execution is halted for specified number of 62.5ns 
  using timer 3. 
  Note: measured overhead is ~4.7us 
*/
void TIM3_delayNanoseconds(uint16_t dt) {
  
  // stop timer
  TIM3.CR1.reg.CEN = 0;

  // set prescaler to fclk -> 16MHz clock -> 62.5ns resolution
  TIM3.PSCR.reg.PSC = 0;
  
  // set timout to dt*62.5ns (freq_Hz=fclk/(prescaler*ARR)) (write high byte first)
  TIM3.ARR.byteH = (uint8_t) (dt >> 8);
  TIM3.ARR.byteL = (uint8_t) dt;
  
  // reset counter register (write high byte first)
  TIM3.CNTR.byteH = (uint8_t) 0;
  TIM3.CNTR.byteL = (uint8_t) 0;
      
  // disable update interrupt 
  TIM3.IER.reg.UIE = 0;

  // request register update
  TIM3.EGR.reg.UG = 1;
  
  // start the timer
  TIM3.CR1.reg.CEN = 1;
  
  // clear status registers (do this last)
  TIM3.SR1.byte = 0x00;
  
  // on zero delay return. Do here to have similar overhead for dt=0
  if (!dt)
    return;
  
  // wait for overflow (no interrupts!)
  while (!(TIM3.SR1.reg.UIF));
    
} // TIM3_delayNanoseconds



/**
  \fn void TIM3_setFrequency(uint32_t centHz)

  \brief set PWM frequency for all channels
   
  \param[in] centHz   PWM frequency [0.01Hz]
   
  Set PWM frequency in 0.01Hz for all TIM3 compare channels. 
*/
void TIM3_setFrequency(uint32_t centHz) {

  uint8_t     pre;          // 16b timer prescaler
  uint16_t    ARR;          // 16b reload value
  uint16_t    tmp;


  //////////////
  // calculate timer parameter
  //////////////

	// find smallest usable prescaler
	tmp = (uint16_t)(1600000000L / (centHz * UINT16_MAX));
	pre = 0;
	while (tmp > (0x0001 << pre))
	  pre++;
	
  // set freq to spec. value (fPWM = fCPU/((2^pre)*(ARR+1))
  ARR = (uint16_t) (1600000000L >> pre) / centHz - 1;
  

  //////////////
  // set PWM period
  //////////////

  // reset timer registers (just to make sure)
  TIM3_init();
	
  // exit on zero or too low frequency. Above Init deactivates timer 3
  if ((centHz == 0) || (pre > 15))
    return;

  // set TIM3 prescaler f = fcpu/2^pre with pre in [0..15]
  TIM3.PSCR.reg.PSC = pre;

  // set reload value
  TIM3.ARR.byteH = (uint8_t) (ARR >> 8);
  TIM3.ARR.byteL = (uint8_t) ARR;

  // set PWM behavior
  TIM3.CCMR2.regOut.OC2M  = 6;   // PWM mode 1
  TIM3.CCMR2.regOut.OC2PE = 1;   // pre-load enable
  TIM3.CCMR2.regOut.CC2S  = 0;   // enable output

  // set active polarity and enable output
  TIM3.CCER1.reg.CC2P = 0;    // high polarity
  TIM3.CCER1.reg.CC1E = 1;    // output enable
  
  // request register update
  TIM3.EGR.reg.UG = 1;
  
  // activate timer
  TIM1.CR1.reg.CEN = 1;       // start the timer
  
} // TIM3_setFrequency



/**
  \fn void TIM3_setDutyCycleSingle(uint8_t channel, uint16_t deciPrc)

  \brief set PWM duty cycle for single compare channel
   
  \param[in] channel   compare channel
  \param[in] deciPrc   PWM duty cycle in [0.1%]
   
  Set PWM duty cycle in 0.1% for single compare channel. 
*/
void TIM3_setDutyCycleSingle(uint8_t channel, uint16_t deciPrc) {

  uint16_t   CCR, ARR;
  
  // get reload value
  ARR = ((uint16_t) (TIM3.ARR.byteH)) << 8 + (uint16_t) (TIM3.ARR.byteL);
  
  // map duty cycle [0.1%] to reload period
  CCR = map(deciPrc, 0, 1000, 0, ARR);
  
  // set capture/compare value (DC=CCR/ARR)
  TIM3.CCR1.byteH = (uint8_t) (CCR >> 8);
  TIM3.CCR1.byteL = (uint8_t) CCR;

} // TIM3_setDutyCycleSingle



/**
  \fn void TIM3_setDutyCycleAll(uint16_t *deciPrc)

  \brief set PWM duty cycle for all compare channels
   
  \param[in] deciPrc   PWM duty cycle in [0.1%]
  \param[in] channel   compare channel
   
  Set PWM duty cycle in 0.1% for all timer 3 compare channels. 
*/
void TIM3_setDutyCycleAll(uint16_t *deciPrc) {

  

} // TIM3_setDutyCycleAll


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
