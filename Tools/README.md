Helper Tools for STM8 Templates
=================================

In a nutshell: 
  - to upload code to STM8 download [stm8flash](https://github.com/vdudouyt/stm8flash) (debug interface) and/or [STM8 serial flasher](https://github.com/gicking/STM8_serial_flasher) (bootloader) source code
  - make respective binary and place in this folder
  - adapt the project "build_upload.py" to use the respective upload method 
  - make "build_upload.py" executable
  - double-click "build_upload.py"  

For installation of other tools, e.g. compiler, see [Docu](../Docu) 


terminal.py (provided):
----------------------------------
  Simple serial terminal in Python. Requires [Python](https://www.python.org/) installation with additional package pySerial 


[stm8flash](https://github.com/vdudouyt/stm8flash) (external):
----------------------------------
  Tool for uploading hexfile to STM8 via SWIM debug interface. Open source, platform independent.
  - requires libusb-dev (e.g. sudo apt-get install libusb-1.0-0-dev)
  - on Linux grant write access to ST-Link debugger by creating a file /etc/udev/rules.d/99-stlinkv2.rules with content  
    SUBSYSTEM=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="3744", MODE="0666"  
    Note: check the idProduct of your ST-Link device via terminal command usb-devices


[STVisualProgrammer](http://www.st.com) (external):
----------------------------------
  Tool for uploading hexfile to STM8 via SWIM debug interface. Closed source, Windows only, not supported by automatic build.


[STM8 serial flasher](https://github.com/gicking/STM8_serial_flasher) (external):
----------------------------------
  Tool for uploading hexfile to STM8 via UART bootloader. Open source, platform independent.


[Flash Loader Demonstrator](http://www.st.com) (external):
-------------------------------------
  Tool for uploading hexfile to STM8 via UART bootloader. Closed source, Windows only, not supported by automatic build.
