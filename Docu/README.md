Installation:
-------------

  - cross-compiler: the C modules & examples are compatible with
    - [SDCC open-source compiler](http://sdcc.sourceforge.net/) and [Python](https://www.python.org/) for automatic build process (see below) -> any OS
    - [Cosmic compiler](http://www.cosmic-software.com/) and [STVisualDevelop](http://www.st.com) -> Windows only, not supported by automatic build
  
  - build process for SDCC:
    - GNU make -> any OS. Windows requires separate install, e.g. from [MinGW](http://www.mingw.org) or [GnuWin](http://gnuwin32.sourceforge.net/packages/make.htm)
    - [Python](https://www.python.org/) with additional pySerial module for build process and terminal

  - STM8 programming 
    - SWIM debug interface: requires debug hardware, e.g. ST-Link, and 
      - [stm8flash](https://github.com/vdudouyt/stm8flash) -> any OS
      - [STVisualProgrammer](http://www.st.com) -> Windows only, not supported by automatic build
    - STM8 serial bootloader: requires serial connection e.g. USB<->UART adapter, and
      - [STM8 serial flasher](https://github.com/gicking/STM8_serial_flasher) -> any OS
      - [Flash Loader Demonstrator](http://www.st.com) -> Windows only, not supported by automatic build
      
  - helper tools like stm8flash and python terminal need to be located in ./Tools
  - install SDCC compiler, Python and make and assert that binaries are in $(PATH)
  - configure your OS to launch *.py files on double-click


Usage:
------

  - in project folder adapt "build_upload.py" to your setting, e.g. COM port and upload method
  - if required set file execute permission for "build_upload.py"
  - double-click on "build_upload.py" and follow instructions

====================================

Revision History
----------------

1.0.0 (2017-03-11): initial release by Georg Icking-Konert

