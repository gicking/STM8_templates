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
  user functions to 1ms interrupt (-> #define USE_CLK_ISR) to 
  automatically call function every 1ms. 
  Functionality:
  - configure LED pin as output
  - attach LED toggle function to 1ms interrupt -> background operation
  - after 20 cycles detach user function


back to [Wiki](https://github.com/gicking/STM8_templates/wiki)

