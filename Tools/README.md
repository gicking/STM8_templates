Helper Tools for STM8 templates
=================================

In a nutshell: 
  - to upload code to STM8 download stm8flash (debug interface) and/or 
    STM8_serial_flasher (bootloader) from below links
  - make respective binary and place in this folder
  - adapt the respective "build_upload.py" of project
  - double-click "build_upload.py"


terminal.py (provided):
-----------------------
  simple serial terminal in Python. Requires Python installation with
  additional package pySerial 



stm8flash (external):
---------------------
  tool for uploading hexfile to STM8 via SWIM debug interface. 
  Open source, platform independent.
  Available from https://github.com/vdudouyt/stm8flash 


STVisualProgrammer (external):
------------------------------
  tool for uploading hexfile to STM8 via SWIM debug interface. 
  Closed source, Windows only, not yet supported by automatic build.
  Available from http://www.st.com



STM8_serial_flasher (external):
----------------------------------
  tool for uploading hexfile to STM8 via UART bootloader -> 
  requires serial connection between PC and STM8 e.g. USB<->UART adapter
  Open source, platform independent.
  Available from https://github.com/gicking/STM8_serial_flasher


Flash Loader Demonstrator (external):
-------------------------------------
  tool for uploading hexfile to STM8 via UART bootloader -> 
  requires serial connection between PC and STM8 e.g. USB<->UART adapter
  Closed source, Windows only, not yet supported by automatic build.
  Available from http://www.st.com


====================================

Revision History
----------------

1.0.0 (2017-03-11): initial release by Georg Icking-Konert under Apache license

