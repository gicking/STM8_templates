/**********************
  STM8 port of Dhrystone benchmark test without Arduino-like 
  initialization and setup()/loop(), but with interrupts and
  UART output.
  Functionality (see "portme.c"):
  - init FCPU to 16MHz
  - init 1ms TIM4 interrupt (for measuring times)
  - configure UART1 for output via UART1
  - run benchmark test and print result
  Note:
  - SDCC requires ISRs declared in source containing main(), here "dhry_1.c"
  - template based on: http://www.colecovision.eu/stm8/dhrystone-stm8af5288-usart3-sdcc-3.6.0.tar.gz
**********************/

#include "stm8as.h"                   // STM8 peripheral registers
#include "timer4.h"                   // 1ms clock
#include "uart1_blocking.h"           // minimal UART1 communication
#include "putchar.h"                  // required for printf()
#include "sw_delay.h"                 // for sw_delay()


//////////
// STM8 initialization. called by main() in dhry_1.c
//////////
void init(void) {

  // globally disable interrupts
  DISABLE_INTERRUPTS;

  // switch to 16MHz (default is 2MHz)
  CLK.CKDIVR.byte = 0x00;  
  
  // init 1ms SW clock
  TIM4_init();

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // use UART1 for printf() output
  putcharAttach(UART1_write);

  // globally enable interrupts
  ENABLE_INTERRUPTS;
  
  // allow some time for serial monitor to start 
  sw_delay(1000);
  
} // init()


//////////
// return ms clock to measuring time. Called by main() in dhry_1.c
//////////
unsigned int clock(void) {

	// 1ms clock updated in TIM4_UPD_ISR 
	return(millis());

} // clock()

