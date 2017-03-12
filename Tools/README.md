Helper Tools for STM8 Templates
=================================

In a nutshell: 
  - to upload code to STM8 download [stm8flash](https://github.com/vdudouyt/stm8flash) (debug interface) and/or [STM8 serial flasher](https://github.com/gicking/STM8_serial_flasher) (bootloader) source code
  - make respective binary and place in this folder
  - adapt the project "build_upload.py" to use the respective upload method 
  - make "build_upload.py" executable
  - double-click "build_upload.py"


terminal.py (provided):
----------------------------------
  Simple serial terminal in Python. Requires [Python](https://www.python.org/) installation with additional package pySerial 


[stm8flash](https://github.com/vdudouyt/stm8flash) (external):
----------------------------------
  Tool for uploading hexfile to STM8 via SWIM debug interface. Open source, platform independent.


[STVisualProgrammer](http://www.st.com) (external):
----------------------------------
  Tool for uploading hexfile to STM8 via SWIM debug interface. Closed source, Windows only, not supported by automatic build.


[STM8 serial flasher](https://github.com/gicking/STM8_serial_flasher) (external):
----------------------------------
  Tool for uploading hexfile to STM8 via UART bootloader. Open source, platform independent.


[Flash Loader Demonstrator](http://www.st.com) (external):
-------------------------------------
  Tool for uploading hexfile to STM8 via UART bootloader. Closed source, Windows only, not supported by automatic build.
