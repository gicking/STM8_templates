# Toolchain Installation

***

  - if required, download and install [SDCC](http://sdcc.sourceforge.net/), Python and Gnu-Make. Add binaries to $(PATH)
  - for STM8 programming via SWIM debug interface
    - download [stm8flash](https://github.com/vdudouyt/stm8flash) source code
    - install libusb-dev (e.g. `sudo apt-get install libusb-1.0-0-dev`)
    - make stm8flash and copy executable to `Tools`
    - on Linux grant write access to ST-Link debugger by creating a file `/etc/udev/rules.d/99-stlinkv2.rules` with content  
    `SUBSYSTEM=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="3744", MODE="0666"`  
    Note: since several versions of ST-Link exist, check the idProduct of your device via command `usb-devices`
  - for STM8 programming via serial bootloader
    - download [STM8 serial flasher](https://github.com/gicking/STM8_serial_flasher) source code
    - install Python module `pySerial`
    - make STM8_serial_flasher and copy executable to `Tools`
  - if necessary, set execute permission for *.py files in project folders
  - configure your OS to launch *.py files on double-click

## Notes
  - the STM8 template libraries & example projects are also compatible with [Cosmic compiler](http://www.cosmic-software.com/) and [STVisualDevelop](http://www.st.com) IDE. These are not supported by the automatic build, but allow graphical debugging which is not yet supported by SDCC 
  - on Windows
    - SWIM upload can also be performed via [STVisualProgrammer](http://www.st.com). However, this is not supported by the automatic build
    - bootloader upload can also be performed via [Flash Loader Demonstrator](http://www.st.com). However, this is not supported by the automatic build
