Example Projects
=================

This folder contains some general, board independent examples for
the STM8 template library. The functionality (loosely sorted by 
rising complexity) is as follows:

Minimal-C: 
----------
  simple C-project without Arduino-like initialization and 
  setup()/loop(). No assumption is made, no interrupts used.
  Can be used as starting point for projects with extreme
  memory limitations or real-time requirements.
  Functionality:
    - init FCPU to 16MHz
    - configure pin as output
    - toggle pin every 500ms w/o timer -> blocking


Basic_Project: 
----------
  Arduino-like project with setup() & loop(). Only 1ms interrupts
  are used, but no other optional features. Can be used as a 
  starting point for simple Arduino-like STM8 projects.
  Functionality:
    - configure pin as output
    - poll SW clock and toggle pin every 500ms -> non-blocking


Play_Tone: 
----------
  Arduino-like project with setup() & loop(). Demonstrate tone
  output via beeper module.
  Note: requires option byte AFR7=1 for alternate usage of BEEP pin 
  Functionality:
    - play tone ladder with increasing frequency


Attach_1ms_Interrupt: 
----------
  Arduino-like project with setup() & loop(). Dynamically attach 
  user functions to 1ms interrupt (-> #define USE_CLK_ISR) to 
  automatically call function every 1ms. 
  Functionality:
    - configure 2 pins as output high
    - attach pin toggle function to 1ms interrupt -> background operation
    - after 10 cycles swap user function
    - after 20 cycles detach user function


Attach_Port_Interrupt: 
----------
  Arduino-like project with setup() & loop(). Dynamically attach 
  user function to external port interrupt @ PE5 (=io_1 on muBoard)
  (-> #define USE_PORT_ISR) to call function on falling edge. 
  Functionality:
    - configure 1 pins as input pull-up & 2 pins as output high
    - attach user function to port interrupt -> background operation
    - after 10 ISR calls detach user function
    - poll button and mirror to LED


Attach_Pin_Interrupt: 
----------
  Arduino-like project with setup() & loop(). Dynamically attach 
  user function to TLI pin interrupt @ PD7 (=automode on muBoard)
  (-> #define USE_TLI_ISR) to call function on falling edge. 
  Functionality:
    - configure 1 pins as input pull-up & 2 pins as output high
    - attach user function to port interrupt -> background operation
    - after 10 ISR calls detach user function
    - poll TLI pin and mirror to LED


Printf_UART:
----------
  Arduino-like project with setup() & loop(). Print output
  via UART to PC terminal. Optionally in integer (small)
  or floating (large; #define USE_FTOA) format.
  Functionality:
    - configure UART1 and putchar() for PC output
    - every 500ms send current time via printf()

