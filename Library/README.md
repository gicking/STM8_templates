STM8 Libraries
=================================

Collection of STM8 register header file, C-functions and macros. These are the basis for the example projects in the [Projects](../Projects) folder. The function documentation is in the [Wiki](https://github.com/gicking/STM8_templates/wiki)

To be compatible with the SPL folder structure, library sources are located in subfolders src/ and headers in inc/ 


[Base](Base) Libraries
----------------------------------
Generic, board and device independent STM8 macros and routines 


[STM8L_Discovery](STM8L_Discovery) Libraries
----------------------------------
[STM8L Discovery](http://www.st.com/en/evaluation-tools/stm8l-discovery.html) specific configuration, routines and macros. This STM8L board is very cheap and has a built-in LCD, ST-Link debugger. However, it lacks a serial interface 


[STM8S_Discovery](STM8S_Discovery) Libraries
----------------------------------
[STM8S Discovery](http://www.st.com/en/evaluation-tools/stm8s-discovery.html) specific configuration, routines and macros. This STM8S board is very cheap and has a built-in ST-Link debugger. However, it lacks a serial interface 


[muBoard](muBoard) Libraries
----------------------------------
muBoard v2.3 specific configuration, routines and macros. This STM8 board was developed for IC validation and testing at [Robert Bosch GmbH](http://www.bosch.com). For an overview of board functions see [here](https://frosch.piandmore.de//de/pam9/call/public-media/event_media/160611_Vortrag_Interpreter.pdf) (in German).


[User](User) Libraries
----------------------------------
Place to store user libraries. If you implemented a useful library, please consider contributing it to this repository! Just drop me a short note. Thanks in advance! :smile:
