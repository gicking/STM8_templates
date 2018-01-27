back to [Wiki](https://github.com/gicking/STM8_templates/wiki)


Other Examples
=================

This folder contains some miscellaneous examples not really fitting anywhere else. 
The functionality is (loosely) sorted by rising complexity.


Beeper:
----------
  Arduino-like project with setup() & loop(). 
  Demonstrate tone output via beeper module.
  Beeper requires option byte AFR7=1 for alternate usage of BEEP pin 
  Functionality:
  - assert option byte setting for beeper output 
  - play tones with different pitch
  Note: the beeper module is VERY basic. For flexible tones use timer instead 


Trap_Interrupt:
----------
  Arduino-like project with setup() & loop(). 
  Trigger TRAP interrupt by software. 
  Functionality:
  - configure pin as input pull-up
  - on pin=low, trigger TRAP_ISR


Power_Saving_Modes:
----------
  Arduino-like project with setup() & loop(). 
  Enter power-saving modes with auto-wake via 
    - any interrupt (lowPower_Wait)
    - external interrupt or auto-wake (lowPower_HaltAWU)  
    - external interrupt (lowPower_Halt)
  Use EXINT port interrupt @ pin PE5 (=io_1 on muBoard)
  (-> #define USE_PORTE_ISR) and AWU (-> #define USE_AWU_ISR)
  Functionality:
  - configure wake pin as input pull-up with interrupt on falling edge
  - configure LED output pin
  - enter power-down mode


back to [Wiki](https://github.com/gicking/STM8_templates/wiki)

