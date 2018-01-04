Helper Tools for STM8 Templates
=================================

For installation of required tools, e.g. compiler, see [Docu](../Docu) 


[stm8flash](https://github.com/vdudouyt/stm8flash) (external):
----------------------------------
  Tool for uploading hexfile to STM8 via SWIM debug interface. Open source, platform independent.
  - requires libusb-dev (e.g. `sudo apt-get install libusb-1.0-0-dev`)
  - on Linux grant write access to ST-Link debugger by creating a file `/etc/udev/rules.d/99-stlinkv2.rules` with content  
    `SUBSYSTEM=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="3744", MODE="0666"`  
    Note: check the idProduct of your ST-Link device via terminal command `usb-devices`


[STM8 serial flasher](https://github.com/gicking/STM8_serial_flasher) (external):
----------------------------------
  Tool for uploading hexfile to STM8 via UART bootloader. Open source, platform independent


terminal.py (provided):
----------------------------------
  Simple serial terminal in Python. Requires [Python](https://www.python.org/) installation with additional package `pySerial`


buildProject.py (provided):
----------------------------------
  Routines for generate Makefile and build project. Is called by project build script


misc.py (provided):
----------------------------------
  Gereric helper routines

