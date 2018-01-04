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
  memory limitations.
  Functionality:
  - init FCPU to 16MHz
  - configure pin as output
  - toggle pin every 500ms with delay (->blocking)
  - optionally use delay via SW (less overhead & latency) or timer 3 (robust against high ISR load)


Basic_Project: 
----------
  Arduino-like project with setup() & loop(). Only 1ms interrupts
  are used, but no other optional features. Can be used as a 
  starting point for simple Arduino-like STM8 projects.
  Functionality:
  - configure pin as output
  - poll SW clock and toggle pin every 500ms -> non-blocking


Timeout_Scheduler:
----------
  Arduino-like project with setup() & loop(). Use several timeouts
  to execute periodic tasks in loop(). 
  Functionality:
  - configure 2 (LED-)pins as output
  - toggle 2 pins at different intervals


Attach_1ms_Interrupt: 
----------
  Arduino-like project with setup() & loop(). Dynamically attach 
  user functions to 1ms interrupt (-> #define USE_MILLI_ISR) to 
  automatically call function every 1ms. 
  Functionality:
  - configure 2 pins as output high
  - attach pin toggle function to 1ms interrupt -> background operation
  - use timeouts to periodically perform tasks in ISR
  - after 10 cycles swap user function
  - after 20 cycles detach user function


Pin_Interrupt: 
----------
  Arduino-like project with setup() & loop(). 
  Use TLI interrupt @ pin PD7 (=automode on muBoard)
  (-> #define USE_TLI_ISR) to call function on falling edge. 
  Functionality:
  - configure 1 pins as input pull-up & 2 pins as output high
  - attach ISR to TLI interrupt -> background operation
  - after 10 ISR calls disable ISR
  - poll TLI pin and mirror to LED


Port_Interrupt: 
----------
  Arduino-like project with setup() & loop(). 
  Use EXINT port interrupt @ pin PE5 (=io_1 on muBoard)
  (-> #define USE_PORT_ISR) to call function on falling edge. 
  Functionality:
  - configure 1 pins as input pull-up & 2 pins as output high
  - attach ISR to port interrupt -> background operation
  - after 10 ISR calls disable ISR
  - poll button and mirror to LED


Printf_UART:
----------
  Arduino-like project with setup() & loop(). Print output
  via UART to PC terminal. Optionally in integer (small)
  or floating (large) number format. 
  For float output #define USE_FTOA in config.h)
  Functionality:
  - configure UART1
  - configure putchar() for PC output via UART1
  - every 500ms send current time via printf()


Gets_Printf_UART:
----------
  Arduino-like project with setup() & loop(). Read number
  as string via UART from PC terminal and echo value back.
  Functionality:
  - configure UART1 for PC in-/output
  - use UART1 send for putchar() output
  - use UART1 receive for gets() input
  - read string from PC, convert to number and send value to PC


Beeper:
----------
  Arduino-like project with setup() & loop(). 
  Demonstrate tone output via beeper module.
  Beeper requires option byte AFR7=1 for alternate usage of BEEP pin 
  Functionality:
  - assert option byte setting for beeper output 
  - play tones with different pitch

  
Bootloader_Activation
----------
  Arduino-like project with setup() & loop(). 
  Activate/Deactivate STM8 ROM bootloader depending on
  state of pin PD7 (=switch "automode" on muBoard)
  Functionality:
  - configure pin as input pull-up
  - wait a bit and read pin state
  - activate(state=1) or deactivate(state=0) BL via option byte


EEPROM_Datalogger:
----------
  Arduino-like project with setup() & loop(). Write data 
  to EEPROM and read back.
  Functionality:
  - configure UART1
  - configure putchar() for PC output via UART1
  - save data to EEPROM
  - read from EEPROM and print to terminal 


P-Flash_Datalogger:
----------
  Arduino-like project with setup() & loop(). 
  Write data to P-flash and read back.
  Functionality:
  - configure UART1
  - configure putchar() for PC output via UART1
  - save data to P-flash (take care not to overwrite application)
  - read from P-flash and print to terminal 


ADC2_Measure:
----------
  Arduino-like project with setup() & loop().
  Periodically measure via ADC2 and send result via 
  UART1 in ADC interrupt routine (muBoard)
  Functionality:
  - configure UART1 for PC in-/output
  - use UART1 send for putchar() output
  - initialize ADC2 for single measurement
  - periodically send ADC result via UART1 and blink LED


ADC2_Continuous_Interrupt:
----------
  Arduino-like project with setup() & loop().
  Continuously measure via ADC2 and send result via 
  UART1 in ADC interrupt routine (muBoard)
  Functionality:
  - configure UART1 for PC in-/output
  - use UART1 send for putchar() output
  - initialize ADC2 for continuous mode
  - attach ISR to ADC2_EOC interrupt
  - in ADC ISR send every Nth result via UART1 and blink LED


Auto-Wakeup:
----------
  Arduino-like project with setup() & loop().
  Periodically enter STOP mode with auto-wake.
  Functionality:
  - attach ISR to AWU interrupt
  - periodically enter STOP mode with auto-wake

