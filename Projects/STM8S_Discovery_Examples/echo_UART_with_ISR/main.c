/**********************
  Arduino-like project with setup() & loop(). 
  Echo bytes received via UART2 with interrupts.
  STM8S Discovery pinning:
    CN1 pin5  = GND
    CN4 pin10 = UART2 TxD
    CN4 pin11 = UART2 RxD
  Functionality:
  - configure UART2 with 19.2kBaud
  - attach send and receive ISRs to UART2 interrupts
  - in receive ISR echo received byte+1 to PC
  - in send ISR toggle LED for each sent byte
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart2.h"           // UART2 communication


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void UART234_RXF_ISR(void)
 
  \brief UART2 receive interrupt
  
  UART2 receive interrupt. Send received byte and enable send interrupt
*/
ISR_HANDLER(UART234_RXF_ISR, __UART234_RXF_VECTOR__) {

  // send received byte 
  UART2_write(UART2_read()+1);
  
  // enable TXE interrupt
  UART2_enable_send_interrupt();
   
  // toggle LED state
  pinToggle(&PORT_D, 0);

} // UART234_RXF_ISR



/**
  \fn void UART234_TXE_ISR(void)
 
  \brief UART2 send interrupt
  
  UART2 send interrupt. Toggle pin after byte sent, and disable
  TXE interrupt again (else stall the device)
*/
ISR_HANDLER(UART234_TXE_ISR, __UART234_TXE_VECTOR__) {

  // toggle LED state
  pinToggle(&PORT_D, 0);
  
  // disable send interrupt again (important!)
  UART2_disable_send_interrupt();
   
} // UART234_TXE_ISR



//////////
// user setup, called once after reset
//////////
void setup() {

  // init UART2 to 19.2kBaud, 8N1, full duplex
  UART2_begin(115200);

  // enable receive interrupt
  UART2_enable_receive_interrupt();
  
  // configure LED pin as output
  pinMode(&PORT_D, 0, OUTPUT);    // STM8S Discovery LED

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  // dummy, all action happens in UART2 interrupts
  
} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
