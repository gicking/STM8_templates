back to [Wiki](https://github.com/gicking/STM8_templates/wiki)


Standard Peripheral Library Examples
=================

This folder contains some examples for mixing "STM8_templates"
projects with STM8 Standard Peripheral Library (SPL) function calls.

The STM8 SPL is a powerful library containing many functions for controlling
STM8 peripherals. In addition the [STM homepage](http://www.st.com) contains
many software examples, which use SPL function calls.

For compilation, the SPL libraries are required under STM8_templates/Library.
Links work under Linux, but fail under Windows. Subfolder are supported.

SPL libraries with corresponding examples are available for several STM8 
(and STM32) families on the [STM homepage](http://www.st.com). For a specific 
device type, just search for:
  - STM8S/A: "STSW-STM8069" 
  - STM8L10x: "STSW-STM8012"
  - STM8L15x-16x-05x-AL31-L: "STSW-STM8016" 
  - STM8TL5x: "STSW-STM8030" 

Notes:
  - the SPL license is not free (as in OSS), 
  as [pointed out by spth](https://github.com/gicking/STM8-SPL_SDCC_patch/issues/1). 
  **Make sure to respect the SPL license conditions** 
  - the original SPL is not (quite) compatible with the SDCC compiler. However, a 
  patch is available on [Github](https://github.com/gicking/STM8-SPL_SDCC_patch).
  - the device headers from "STM8_templates" and "SPL" are incompatible. To mix them, 
  create separate SPL.c file in project folder and use interface
  functions (see example projects).


Example Projects
=================

Minimal-C: 
----------
  simple C-project without Arduino-like initialization and 
  with calls to the STM8 Standard Peripheral Library
  (SDCC patch available from https://github.com/gicking/STM8-SPL_SDCC_patch)
  No further assumption is made, no interrupts are used.
  Can be used as starting point for SPL projects with extreme
  memory limitations.
  Functionality:
  - init FCPU to 16MHz
  - configure pin as output
  - toggle pin every 500ms w/o timer -> blocking


Basic_Project: 
----------
  Arduino-like project with calls to the STM8 Standard Peripheral Library
  (SDCC patch available from https://github.com/gicking/STM8-SPL_SDCC_patch). 
  Functionality:
  - use SPL to configure LED pin as output
  - toggle LED via SPL every 500ms


back to [Wiki](https://github.com/gicking/STM8_templates/wiki)

