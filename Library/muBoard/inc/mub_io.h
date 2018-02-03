/**
  \file mub_io.h
   
  \author G. Icking-Konert
  \date 2018-01-28
  \version 0.1
   
  \brief declaration of muBoard io_* functions & macros
   
  declaration of functions & macros for controlling io_* pins on a muBoard.
*/

/*-----------------------------------------------------------------------------
    MODULE DEFINITION FOR MULTIPLE INCLUSION
-----------------------------------------------------------------------------*/
#ifndef _MUB_IO_H_
#define _MUB_IO_H_


/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include "stm8as.h"
#include "config.h"
#include "misc.h"
#include "gpio.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL MACROS
-----------------------------------------------------------------------------*/

// I2C addresses
#define ADDR_I2C_LCD    59        ///< I2C address of LCD display
#define ADDR_I2C_POTI   46        ///< I2C address of digital potentiometer
#define ADDR_I2C_AMP    44        ///< I2C address of differential amplifier

// ADC channels (correspond to AINi)
#define ADC_GPIO_15     0         ///< ADC channel to measure io15
#define ADC_GPIO_14     1         ///< ADC channel to measure io14
#define ADC_VD_LV       2         ///< ADC channel to measure VD_LV
#define ADC_VD_HV       3         ///< ADC channel to measure VD_HV
#define ADC_NTC         4         ///< ADC channel to measure NTC
#define ADC_POTI        5         ///< ADC channel to measure poti
#define ADC_GPIO_13     6         ///< ADC channel to measure io13
#define ADC_GPIO_12     7         ///< ADC channel to measure io12
#define ADC_GPIO_11     10        ///< ADC channel to measure io11
#define ADC_GPIO_10     11        ///< ADC channel to measure io10
#define ADC_GPIO_9      12        ///< ADC channel to measure io9
#define ADC_GPIO_8      13        ///< ADC channel to measure io8
#define ADC_GPIO_7      14        ///< ADC channel to measure io7
#define ADC_VCORE       15        ///< ADC channel to measure 1.8V Vcore


// LED control
#define LED_GREEN       (PORT_H.ODR.bit.pin2)    ///< green LED
#define LED_RED         (PORT_H.ODR.bit.pin3)    ///< red LED

// buttons & switches
#define BUTTON          (PORT_E.IDR.bit.pin5)    ///< button connected to io1
#define AUTO_MODE       (PORT_D.IDR.bit.pin7)    ///< mode selection switch

// low-side control
#define LS_1            (PORT_E.ODR.bit.pin6)    ///< control of low-side switch 1
#define LS_2            (PORT_A.ODR.bit.pin3)    ///< control of low-side switch 2
#define LS_3            (PORT_C.ODR.bit.pin0)    ///< control of low-side switch 3

// HV bridge control
#define HV_BRIDGE_1     (PORT_H.ODR.bit.pin5)    ///< control of HV-bridge 1
#define HV_BRIDGE_2     (PORT_H.ODR.bit.pin6)    ///< control of HV-bridge 2
#define HV_BRIDGE_3     (PORT_H.ODR.bit.pin7)    ///< control of HV-bridge 3
#define HV_BRIDGE_4     (PORT_E.ODR.bit.pin7)    ///< control of HV-bridge 4

// voltage DAC control
#define VDAC_SELECT_1   (PORT_C.ODR.bit.pin2)    ///< start data transfer to VDAC 1
#define VDAC_SELECT_2   (PORT_C.ODR.bit.pin3)    ///< start data transfer to VDAC 2
#define VDAC_CHANNEL_1  (PORT_I.ODR.bit.pin6)    ///< VDAC channel lb (= parallel bus #14)
#define VDAC_CHANNEL_2  (PORT_I.ODR.bit.pin7)    ///< VDAC channel hb (= parallel bus #15)

// IDAC control
#define IDAC_SELECT     (PORT_E.ODR.bit.pin4)    ///< start data transfer to IDAC
#define IDAC_CHANNEL    (PORT_I.ODR.bit.pin2)    ///< IDAC channel 0/1 (= parallel bus #10)

// LCD reset
#define LCD_RESET       (PORT_E.ODR.bit.pin3)    ///< reset LCD (active righ)

// LIN UART pins
#define OUT_LIN_RX      (PORT_D.ODR.bit.pin6)    ///< UART2 receive
#define OUT_LIN_TX      (PORT_D.ODR.bit.pin5)    ///< UART2 send

// IOs
#define IO_1(reg)       (PORT_E.reg.bit.pin5)    ///< direct access to io1  = PE5
#define IO_2(reg)       (PORT_D.reg.bit.pin2)    ///< direct access to io2  = PD2
#define IO_3(reg)       (PORT_D.reg.bit.pin0)    ///< direct access to io3  = PD0
#define IO_4(reg)       (PORT_A.reg.bit.pin6)    ///< direct access to io4  = PA6
#define IO_5(reg)       (PORT_H.reg.bit.pin0)    ///< direct access to io5  = PH0
#define IO_6(reg)       (PORT_H.reg.bit.pin1)    ///< direct access to io6  = PH1
#define IO_7(reg)       (PORT_F.reg.bit.pin6)    ///< direct access to io7  = PF6
#define IO_8(reg)       (PORT_F.reg.bit.pin5)    ///< direct access to io8  = PF5
#define IO_9(reg)       (PORT_F.reg.bit.pin4)    ///< direct access to io9  = PF4
#define IO_10(reg)      (PORT_F.reg.bit.pin3)    ///< direct access to io10 = PF3
#define IO_11(reg)      (PORT_F.reg.bit.pin0)    ///< direct access to io11 = PF0
#define IO_12(reg)      (PORT_B.reg.bit.pin7)    ///< direct access to io12 = PB7
#define IO_13(reg)      (PORT_B.reg.bit.pin6)    ///< direct access to io13 = PB6
#define IO_14(reg)      (PORT_B.reg.bit.pin1)    ///< direct access to io14 = PB1
#define IO_15(reg)      (PORT_B.reg.bit.pin0)    ///< direct access to io15 = PB0
#define IO_16(reg)      (PORT_H.reg.bit.pin4)    ///< direct access to io16 = PH4
#define IO_17(reg)      (PORT_C.reg.bit.pin1)    ///< direct access to io17 = TIM1 = PC1
#define IO_18(reg)      (PORT_D.reg.bit.pin3)    ///< direct access to io18 = TIM2 = PD3
#define IO_TIM1(reg)    (IO_17(reg))             ///< alternative access to io17 = TIM1 = PC1
#define IO_TIM2(reg)    (IO_18(reg))             ///< alternative access to io18 = TIM2 = PD3


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL VARIABLES
-----------------------------------------------------------------------------*/

// declare or reference to global variables, depending on '_MUB_IO_MAIN_'
#if defined(_MUB_IO_MAIN_)
  
  const PORT_t *ioPort[] = {
	  (PORT_t*) NULL,   // skip idx 0, io_* start with 1
    &PORT_E,          // io1  = PE5
    &PORT_D,          // io2  = PD2
    &PORT_D,          // io3  = PD0
    &PORT_A,          // io4  = PA6
    &PORT_H,          // io5  = PH0
    &PORT_H,          // io6  = PH1
    &PORT_F,          // io7  = PF6
    &PORT_F,          // io8  = PF5
    &PORT_F,          // io9  = PF4
    &PORT_F,          // io10 = PF3
    &PORT_F,          // io11 = PF0
    &PORT_B,          // io12 = PB7
    &PORT_B,          // io13 = PB6
    &PORT_B,          // io14 = PB1
    &PORT_B,          // io15 = PB0
    &PORT_H,          // io16 = PH4
    &PORT_C,          // io17 = TIM1 = PC1
    &PORT_D           // io18 = TIM2 = PD3
  };

  const uint8_t ioPin[] = {
	  0xFF,       // skip idx 0, io_* start with 1
    5,          // io1  = PE5
    2,          // io2  = PD2
    0,          // io3  = PD0
    6,          // io4  = PA6
    0,          // io5  = PH0
    1,          // io6  = PH1
    6,          // io7  = PF6
    5,          // io8  = PF5
    4,          // io9  = PF4
    3,          // io10 = PF3
    0,          // io11 = PF0
    7,          // io12 = PB7
    6,          // io13 = PB6
    1,          // io14 = PB1
    0,          // io15 = PB0
    4,          // io16 = PH4
    1,          // io17 = TIM1 = PC1
    3           // io18 = TIM2 = PD3
  };


#else // _MUB_IO_MAIN_
  extern const PORT_t  *ioPort[];
  extern const uint8_t ioPin[];
#endif // _MUB_IO_MAIN_


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// initialize STM8 GPIOs for muBoard
void muBoard_io_init(void);


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _MUB_IO_H_
