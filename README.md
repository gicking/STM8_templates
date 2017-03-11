STM8_templates
=================

This project provides Arduino-like C-libraries & -templates for the STM8A and STM8S 
8-bit microcontrollers by STMicro (see https://en.wikipedia.org/wiki/STM8).

Most projects are written for the STM8S Discovery board (see UM0817 on http://www.st.com), 
or a proprietary PCB "muBoard" (see https://frosch.piandmore.de//de/pam9/call/public-media/event_media/160611_Vortrag_Interpreter.pdf)

For bugs reports or feature requests, please send me a note.


Installation:
-------------

  - cross-compiler: the C modules & examples are compatible with
    - SDCC open-source compiler (http://sdcc.sourceforge.net/) and python for build process (see below) -> any OS
    - Cosmic commercial compiler (http://www.cosmic-software.com/) and STVisualDevelop (http://www.st.com) -> Windows only
  
  - build process (only SDCC):
    - GNU make -> any OS. Windows requires separate install
    - python installation with additional pySerial module (for code upload and terminal). See ./Tools

  - STM8 programming 
    - SWIM debug interface (not yet supported by python build!): requires debug hardware and 
      - stm8flash (https://github.com/vdudouyt/stm8flash) -> any OS
      - STVisualProgrammer (not yet supported by python build!) (http://www.st.com) -> Windows only
    - STM8 serial bootloader: requires serial connection e.g. USB<->UART adapter and
      - STM8_serial_flasher (https://github.com/gicking/STM8_serial_flasher) -> any OS
      - Flash Loader Demonstrator (not yet supported by python build!) (http://www.st.com) -> Windows only
      
  - helper tools like stm8flash and python terminal are stored in $(LIBROOT)/Tools


Usage:
------
- install compiler & make and assert that binaries are in $(PATH)
- install helper tools for code upload in $(LIBROOT)/Tools
- configure your OS to launch *.py files on double-click
- in respective project folder adapt "build_upload.py" to your respective setting, e.g. COM port
- double-click on "build_upload.py" and follow instructions


Legal stuff
-----------
see file "LICENSE"


Have fun!
Georg. Icking-Konert

====================================

Revision History
----------------

1.0.0 (2017-03-11): initial release by Georg Icking-Konert

