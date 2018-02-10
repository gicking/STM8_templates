back to [Wiki](https://github.com/gicking/STM8_templates/wiki)


STM8S Discovery Examples
=================

This folder contains some examples for the [STM8S Discovery](http://www.st.com/en/evaluation-tools/stm8s-discovery.html) board using the STM8 template library.  
The functionality (loosely sorted by rising complexity) is as follows:

Minimal-C: 
----------
  simple C-project without Arduino-like initialization and 
  setup()/loop(). No assumption is made, no interrupts used.
  Can be used as starting point for projects with extreme
  memory limitations or real-time requirements.
  Functionality:
  - init FCPU to 16MHz
  - configure LED pin as output
  - toggle LED every 500ms w/o timer -> blocking


Basic_Project: 
----------
  Arduino-like project with setup() & loop(). Only 1ms interrupts
  are used, but no other optional features. Can be used as a 
  starting point for simple Arduino-like STM8 projects.
  Functionality:
  - configure LED pin as output
  - poll SW clock and toggle LED every 500ms -> non-blocking


Attach_1ms_Interrupt: 
----------
  Arduino-like project with setup() & loop(). Dynamically attach 
  user functions to 1ms interrupt (-> #define USE_MILLI_ISR) to 
  automatically call function every 1ms. 
  Functionality:
  - configure LED pin as output
  - attach pin toggle function to 1ms interrupt -> background operation
  - after N cycles detach user function


echo_UART_with_ISR: (requires USB<->TTL adapter for PC communication)
----------
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


back to [Wiki](https://github.com/gicking/STM8_templates/wiki)

