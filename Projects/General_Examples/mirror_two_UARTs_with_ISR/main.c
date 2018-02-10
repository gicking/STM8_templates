/**********************
  Arduino-like project with setup() & loop(). 
  Mirror bytes received via UART1 to UART3 and vice
  versa with interrupts.
  Functionality:
  - configure UART1 to 115.2kBaud
  - configure UART3 to 19.2kBaud
  - attach send and receive ISRs to UART1 and UART3 interrupts
  - in receive ISR mirror received byte to respective other UART
  - in send ISRs toggle LEDs for each sent byte
**********************/

/*----------------------------------------------------------
    INCLUDE FILES
----------------------------------------------------------*/
#include "main_general.h"    // board-independent main
#include "uart1.h"           // UART1 communication
#include "uart3.h"           // UART3 communication


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void UART1_RXF_ISR(void)
 
  \brief UART1 receive interrupt
  
  UART1 receive interrupt. Mirror received byte to UART3 and
  enable send interrupt
*/
ISR_HANDLER(UART1_RXF_ISR, __UART1_RXF_VECTOR__) {

  // send received byte via UART3 
  UART3_write(UART1_read());
  
  // enable UART3 TXE interrupt
  UART3_enable_send_interrupt();
   
} // UART1_RXF_ISR



/**
  \fn void UART1_TXE_ISR(void)
 
  \brief UART1 send interrupt
  
  UART1 send interrupt. Toggle pin after byte sent, and disable
  TXE interrupt again (else stall the device)
*/
ISR_HANDLER(UART1_TXE_ISR, __UART1_TXE_VECTOR__) {

  // toggle red LED state
  pinToggle(&PORT_H, 3);
  
  // disable send interrupt again (important!)
  UART1_disable_send_interrupt();
   
} // UART1_TXE_ISR



/**
  \fn void UART234_RXF_ISR(void)
 
  \brief UART3 receive interrupt
  
  UART3 receive interrupt. Mirror received byte to UART1 and
  enable send interrupt
*/
ISR_HANDLER(UART234_RXF_ISR, __UART234_RXF_VECTOR__) {

  // send received byte via UART1 
  UART1_write(UART3_read());
  
  // enable UART1 TXE interrupt
  UART1_enable_send_interrupt();
   
} // UART234_RXF_ISR



/**
  \fn void UART234_TXE_ISR(void)
 
  \brief UART3 send interrupt
  
  UART3 send interrupt. Toggle pin after byte sent, and disable
  TXE interrupt again (else stall the device)
*/
ISR_HANDLER(UART234_TXE_ISR, __UART234_TXE_VECTOR__) {

  // toggle green LED state
  pinToggle(&PORT_H, 2);
  
  // disable send interrupt again (important!)
  UART3_disable_send_interrupt();
   
} // UART234_TXE_ISR



//////////
// user setup, called once after reset
//////////
void setup() {

  // init UART1 to 115.2kBaud and UART3 to 19.2kBaud
  UART1_begin(115200);
  UART3_begin(19200);

  // enable receive interrupts
  UART1_enable_receive_interrupt();
  UART3_enable_receive_interrupt();
  
  // configure LED pins as output
  pinMode(&PORT_H, 2, OUTPUT);    // muBoard green LED
  pinMode(&PORT_H, 3, OUTPUT);    // muBoard red LED

} // setup



//////////
// user loop, called continuously
//////////
void loop() {
  
  // dummy, all action happens in UARTx interrupts
  
} // loop

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
