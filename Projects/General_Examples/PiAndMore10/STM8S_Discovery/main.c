// include modules
#include "main_general.h"

void toggle_LED(void);

// LED pin write
#define LED   pinSet(PORT_D, pin0)


// called once after reset
void setup() {

  pinMode(PORT_D, pin0, OUTPUT);	// configure LED pin
  attachInterruptMillis(toggle_LED);	// attach toggle function to 1ms interrupt

} // setup()


// called continuously
void loop() {

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

