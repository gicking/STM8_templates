/**
  \file mub_io.c
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief implementation of muBoard io_* functions
   
  implementation of functions for controlling io_* pins on a muBoard.
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#define _MUB_IO_MAIN_    // required for globals in mub_io.h
  #include "mub_io.h"
#undef _MUB_IO_MAIN_



/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void muBoard_io_init(void)
   
  \brief initialize STM8 GPIOs for muBoard
  
  initialize all STM8 GPIOs to their respective muBoard functions.
*/
void muBoard_io_init(void) {

  //////////////////
  // init ports
  //////////////////
  
  //////////////////////////////////////////////////////////////////////////
  // parallel bus first to avoid glitches on DACs
  
  /////////
  // PORT G:
  //    0: CAN Tx
  //    1: CAN Rx
  //    2: parallel bus 2
  //    3: parallel bus 3
  //    4: parallel bus 4
  //    5: parallel bus 5
  //    6: parallel bus 6
  //    7: parallel bus 7
  /////////
  PORT_G.ODR.byte = 0b00000001;   // init outputs to low, except for CAN Tx
  PORT_G.DDR.byte = 0b11111101;   // input(=0) or output(=1)
  PORT_G.CR1.byte = 0b11111101;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_G.CR2.byte = 0b11111101;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
  
              
  /////////
  // PORT I:
  //    0: parallel bus 8
  //    1: parallel bus 9
  //    2: parallel bus 10 / IDAC channel
  //    3: parallel bus 11
  //    4: parallel bus 12
  //    5: parallel bus 13
  //    6: parallel bus 14
  //    7: parallel bus 15
  /////////
  PORT_I.ODR.byte = 0b00000000;   // init outputs to low
  PORT_I.DDR.byte = 0b11111111;   // input(=0) or output(=1)
  PORT_I.CR1.byte = 0b11111111;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_I.CR2.byte = 0b11111111;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope


  /////////
  // single pins of parallel bus 
  /////////

  // PC4: parallel bus 0
  PORT_C.ODR.bit.b4 = 0;   // init outputs to low, except for DAC update 
  PORT_C.DDR.bit.b4 = 1;   // input(=0) or output(=1)
  PORT_C.CR1.bit.b4 = 1;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_C.CR2.bit.b4 = 1;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope

  // PE0: parallel bus 1
  PORT_E.ODR.bit.b0 = 0;   // init outputs to low, except for DAC update 
  PORT_E.DDR.bit.b0 = 1;   // input(=0) or output(=1)
  PORT_E.CR1.bit.b0 = 1;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_E.CR2.bit.b0 = 1;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope

  // done with parallel bus
  //////////////////////////////////////////////////////////////////////////



  /////////
  // PORT A:
  //    0: non-existent
  //    1: XTAL1
  //    2: XTAL2
  //    3: LS_2 control
  //    4: USART Rx (-> PC)
  //    5: USART Tx (-> PC)
  //    6: GPIO 4 / EXINT
  //    7: non-existent
  /////////
  PORT_A.ODR.byte = 0b00100000;  // init outputs to low, expect Tx
  PORT_A.DDR.byte = 0b00101000;  // input(=0) or output(=1)
  PORT_A.CR1.byte = 0b10111001;  // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_A.CR2.byte = 0b00101000;  // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
  
  
  /////////
  // PORT B:
  //    0: GPIO_ADC 15 / EXINT
  //    1: GPIO_ADC 14  
  //    2: volt. divider ADC (9/1)
  //    3: volt. divider ADC (1/1)
  //    4: NTC ADC
  //    5: Poti ADC
  //    6: GPIO_ADC 13
  //    7: GPIO_ADC 12
  /////////
  PORT_B.ODR.byte = 0b00000000;   // init outputs to low
  PORT_B.DDR.byte = 0b00000000;   // input(=0) or output(=1)
  PORT_B.CR1.byte = 0b00000000;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_B.CR2.byte = 0b00000000;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
  
  
  /////////
  // PORT C:
  //    0: LS_3 control  
  //    1: Timer/PWM 1 (TIM1_CC1)
  //    2: VDAC 1 update
  //    3: VDAC 2 update
  //    4: parallel bus 0 (v2.3) / n.c. (v2.2)
  //    5: SPI CLK
  //    6: SPI MOSI
  //    7: SPI MISO
  /////////
  PORT_C.ODR.byte = 0b00001100;   // init outputs to low, except for DAC update 
  PORT_C.DDR.byte = 0b01111101;   // input(=0) or output(=1)
  PORT_C.CR1.byte = 0b11111101;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_C.CR2.byte = 0b01111101;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
  
                   
  /////////
  // PORT D:
  //    0: GPIO 3
  //    1: SWIM
  //    2: GPIO 2 / EXINT
  //    3: Timer/PWM 2 (TIM2_CC2)
  //    4: Beeper
  //    5: LIN UART Tx
  //    6: LIN UART Rx
  //    7: mode select (autorun)
  /////////
  PORT_D.ODR.byte = 0b00100000;   // init outputs to low, except LIN UART Tx
  PORT_D.DDR.byte = 0b00110000;   // input(=0) or output(=1)
  PORT_D.CR1.byte = 0b10110010;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_D.CR2.byte = 0b00110000;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
  

  /////////
  // PORT E:
  //    0: parallel bus 1 (v2.3) / n.c. (v2.2)
  //    1: I2C SCL
  //    2: I2C SDA
  //    3: LCD reset
  //    4: IDAC update
  //    5: GPIO 1 / EXINT (make pull-up for button)
  //    6: LS_1 control
  //    7: HV-bridge out 4
  /////////
  PORT_E.ODR.byte = 0b00000110;   // init outputs to low, except for diff ampl update
  PORT_E.DDR.byte = 0b11011111;   // input(=0) or output(=1)
  PORT_E.CR1.byte = 0b11111001;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_E.CR2.byte = 0b11011111;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
  
  
  /////////
  // PORT F:
  //    0: GPIO_ADC 11 / CSN for SD card (initialized on first write to SD card)
  //    1: non-existent
  //    2: non-existent
  //    3: GPIO_ADC 10
  //    4: GPIO_ADC 9
  //    5: GPIO_ADC 8
  //    6: GPIO_ADC 7
  //    7: Vcap ADC (1.8V core voltage -> detect 3.3V / 5V supply)
  /////////
  PORT_F.ODR.byte = 0b00000000;   // init outputs to low
  PORT_F.DDR.byte = 0b00000000;   // input(=0) or output(=1)
  PORT_F.CR1.byte = 0b00000110;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_F.CR2.byte = 0b00000000;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
  
  
  /////////
  // PORT H:
  //    0: GPIO 5
  //    1: GPIO 6
  //    2: status LED green
  //    3: status LED red
  //    4: GPIO 16 (Timer 1 trigger)
  //    5: HV-bridge out 1
  //    6: HV-bridge out 2
  //    7: HV-bridge out 3
  /////////
  PORT_H.ODR.byte = 0b00001100;   // init outputs to low (exception status LEDs 1=off)
  PORT_H.DDR.byte = 0b11101100;   // input(=0) or output(=1)
  PORT_H.CR1.byte = 0b11101100;   // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  PORT_H.CR2.byte = 0b11101100;   // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope

} // muBoard_io_init


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
