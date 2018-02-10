/**********************
  Arduino-like project with setup() & loop(). 
  Echo bytes received via UART1 with interrupts.
  Functionality:
  - configure UART1 for PC in-/output
  - attach send and receive ISRs to UART1 interrupts
  - in receive ISR echo received byte to PC
  - in send ISR toggle LED for each sent byte
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1.h"           // UART1 communication


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void UART1_RXF_ISR(void)
 
  \brief UART1 receive interrupt
  
  UART1 receive interrupt. Send received byte and enable send interrupt
*/
ISR_HANDLER(UART1_RXF_ISR, __UART1_RXF_VECTOR__) {

  // send received byte 
  UART1_write(UART1_read());
  
  // enable TXE interrupt
  UART1_enable_send_interrupt();
   
} // UART1_RXF_ISR



/**
  \fn void UART1_RXF_ISR(void)
 
  \brief UART1 send interrupt
  
  UART1 send interrupt. Toggle pin after byte sent, and disable
  TXE interrupt again (else stall the device)
*/
ISR_HANDLER(UART1_TXE_ISR, __UART1_TXE_VECTOR__) {

  // toggle LED state
  pinToggle(&PORT_H, 3);
  
  // disable send interrupt again (important!)
  UART1_disable_send_interrupt();
   
} // UART1_TXE_ISR



//////////
// user setup, called once after reset
//////////
void setup() {

  // init UART1 to 115.2kBaud, 8N1, full duplex
  UART1_begin(115200);

  // enable receive interrupt
  UART1_enable_receive_interrupt();
  
  // configure LED pin as output
  pinMode(&PORT_H, 3, OUTPUT);    // muBoard LED

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  // dummy, all action happens in UART1 interrupts
  
} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
