back to [Wiki](https://github.com/gicking/STM8_templates/wiki)


Libraries Examples
=================

This folder contains examples for the external libraries and routines to control external circuits. 
The functionality is (loosely) unsorted.

LCD-BTHQ21605V:
----------
  Arduino-like project with setup() & loop(). 
  Print current millis() to the LCD screen. 


DigPoti-AD5280
----------
  Arduino-like project with setup() & loop(). 
  Ramp up resistance of 1-channel poti AD5280 via I2C. 


DigPoti-AD5282
----------
  Arduino-like project with setup() & loop(). 
  Ramp up/down resistances of 2-channel poti AD5282 via I2C. 


SD-card_petitFS
----------
  Arduino-like project with setup() & loop(). 
  Read & write to SD card via [PetitFS](http://elm-chan.org/fsw/ff/00index_p.html) 
  and bitbanging -> slow (meas. 27kB/s), but requires no dedicated SPI.
  Notes:
    - SD cards generally use 3.3V -> check schematics
    - PetitFS can only change file content, not create or extend. For this use FatFS
    - pin macros are required in `config.h`


SD-card_fatFS
----------
  Arduino-like project with setup() & loop(). 
  Read & write to SD card via [FatFS](http://www.elm-chan.org/fsw/ff/00index_e.html)
  and bitbanging -> slow (meas. 27kB/s), but requires no dedicated SPI.
  Notes:
    - SD cards generally use 3.3V -> check schematics
    - pin macros are required in `config.h`


back to [Wiki](https://github.com/gicking/STM8_templates/wiki)

