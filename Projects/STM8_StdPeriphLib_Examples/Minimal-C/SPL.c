/**********************
  Interface functions between STM8_templates and STM8 Standard Peripheral Library
  (SDCC patch available from https://github.com/gicking/STM8-SPL_SDCC_patch). 
  Is required because the different device headers from STM8_templates 
  and SPL are incompatible.
  Advantage is transparent mixing of STM8_templates (simple) with STM8
  SPL library (powerful) and examples by STM.
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "stm8s_conf.h"   // set required SPL modules only in this header


//////////
// init peripherals using SPL
//////////
void SPL_init() {
  
  // SPL: switch to 16MHz (default is 2MHz) 
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  // SPL: configure STM8S Discovery Board LED pin as output
  GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_WriteHigh(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_0);

} // SPL_init()



//////////
// set GPIO state using SPL
//////////
void SPL_setPin(uint8_t state) {
  
  // SPL: set new pin state
  if (state)
    GPIO_WriteHigh(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_0);
  else
    GPIO_WriteLow(GPIOD, (GPIO_Pin_TypeDef)GPIO_PIN_0);
  
} // SPL_setPin()



//////////
// required by SPL. Just copy
//////////
#ifdef USE_FULL_ASSERT
  void assert_failed(uint8_t* file, uint32_t line) { 
    while (1);
  }
#endif

