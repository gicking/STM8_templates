// include modules
#include "main_general.h"
#include "uart1.h"           // UART1 communication
#include "putchar.h"         // for printf()

void toggle_LED(void);

// LED pin write
#define LED   pinOutputReg(&PORT_H, pin3)   // muBoard LED


// called once after reset
void setup() {

  pinMode(&PORT_H, 3, OUTPUT);	// configure LED pin
  attachInterruptMillis(toggle_LED);	// attach toggle function to 1ms interrupt
  
  UART1_begin(115200);			// init UART1 to 115.2kBaud
  putcharAttach(UART1_write);		// printf() uses UART1_write() 

} // setup()


// called continuously
void loop() {

  // print time every 1s
  static uint32_t nextTime = 0;
  if (nextTime - millis() >= 1000) { 
    nextTime += 1000;
    printf("time is %ds\n", (int) (millis()/1000L));
  }

} // loop()


// toggle LED every 500th call
void toggle_LED() {
  
  // every 500th time toggle LED
  static uint16_t   count1ms = 0;
  if (++count1ms == 500) {
    count1ms = 0;
    LED ^= 1;
  }

} // toggle_LED()

