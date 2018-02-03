/**********************
  Arduino-like project with setup() & loop(). Mirror switch 
  input state of io_1 to LED (i.e. pin read and write).
  Use muBoard pin naming convention
  Functionality:
  - configure pin as input with pull-up
  - configure other pin as output
  - mirror input to output 
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_muBoard.h"   // muBoard-dependent main


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

//////////
// user setup, called once after reset
//////////
void setup() {
    
  // configure io_1 as input with pull-up
  pinMode(ioPort[1], ioPin[1], INPUT_PULLUP);

  // set initial timeouts
  setTimeout(0, 1000);
  setTimeout(1, 200);
  
} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  char     str[20];    // string buffer for output

  // mirror io_1(=button) to LED
  //LED_RED = BUTTON;                         // via special names  
  //LED_RED = pinRead(ioPort[1], ioPin[1]);   // via "normal" functions
  LED_RED = IO_1(IDR);                      // via io* macros 


  // timeout 0 has passed
  if (checkTimeout(0)) {
    setTimeout(0, 1000);
    
    // print time to LCD
    sprintf(str, "time = %d s", (int) (millis()/1000L));
    lcd_print(2, 1, str);
    
    // toggle LS1
    LS_1 ^= 1;
  
  } // timeout 0 passed


  // timeout 1 has passed
  if (checkTimeout(1)) {
    setTimeout(1, 200);

    // print ADC value to terminal
    //printf("poti = %d\n", (int) ADC2_measure_single(ADC_POTI));
    printf("%d\n", voltVdd);
  
    LED_GREEN ^= 1;

  } // timeout 1 passed

} // loop

