/**
  \file misc.h
   
  \author G. Icking-Konert
  \date 2008-11-02
  \version 0.1
   
  \brief declaration of misc macros & inline routines
   
  declaration of macros & inline routines not really 
  fitting anywhere else
*/

// for including file only once
#ifndef _MISC_H_
#define _MISC_H_

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdint.h>
#include <ctype.h>
#include "stm8as.h"


/*-----------------------------------------------------------------------------
    GLOBAL MACROS
-----------------------------------------------------------------------------*/

/// skip warnings for unused parameters, see http://stackoverflow.com/questions/3599160/unused-parameter-warnings-in-c-code
#define UNUSED(x) (void)(x)


/*----------------
 for compatibility with Arduino
----------------*/

/*---
 constants
---*/
#ifndef LOW
  #define  LOW                    0
#endif
#ifndef HIGH
  #define  HIGH                   1
#endif
#ifndef false
  #define  false                  0
#endif
#ifndef true
  #define  true                   1
#endif

/*---
 data types
---*/
#ifndef bool
  #define  bool                   (uint8_t)
#endif
#ifndef boolean
  #define  boolean                (uint8_t)
#endif
/* collides with definitions in stm8as.h -> skip
#ifndef byte
  #define  byte                   (uint8_t)
#endif
#ifndef word
  #define  word                   (uint16_t)
#endif
*/
#ifndef string
  #define  string                 (char*)
#endif

/*---
 conversion
---*/
#define char(a)                   ((char)(a))
#define byte(a)                   ((uint8_t)(a))
#define int(a)                    ((int)(a))
#define word(a)                   ((uint16_t)(a))
#define long(a)                   ((int32_t)(a))
#define float(a)                  ((float)(a))

/*---
 math
---*/
#define min(a,b)                   ((a < b) ?  (a) : (b))                      ///< minimum of 2 numbers
#define max(a,b)                   ((a > b) ?  (a) : (b))                      ///< maximum of 2 numbers
//#define abs(x)                     (((x) < 0) ? -(x) : (x))                  // absolute value of number (obsolete: already part of SDCC)
#define constrain(x,low,high)      ((x)<(low)?(low):((x)>(high)?(high):(x)))   ///< clip value to range [low;high]
#define map(x,inMin,inMax,outMin,outMax)                                       /**< re-map a number from one range to another **/ \
                                   ((int32_t)(x-inMin)*(int32_t)(outMax-outMin)/(inMax-inMin)+outMin)
#define scale(x,inMax,outMax)      (((int32_t)x*(int32_t)outMax)/inMax)        ///< scale a number from one range to another (like map() but with 0 offsets)
#define pow(x,y)                   powf(x,y)                                   ///< 
#define sq(x)                      ((float)x*(float)x)                         ///< 
#define sqrt(x)                    sqrtf(x)                                    ///< 

/*---
 trigonometry
---*/
#define sin(x)                     sinf(x)
#define cos(x)                     cosf(x)
#define tan(x)                     tanf(x)
#define deg2rad(x)                 (x * 0.017453293)                           ///< convert degrees to radians (=x*pi/180)
#define rad2deg(x)                 (x * 57.29577952)                           ///< convert radians to degrees (=x*180/pi)

/*---
 characters
---*/
#define isAlphaNumeric(a)          isalnum(a)
#define isAlpha(a)                 isalpha(a)
#define isAscii(a)                 isascii(a)
#define isWhitespace(a)            isspace(a)
#define isControl(a)               iscntrl(a)
#define isDigit(a)                 isdigit(a)
#define isGraph(a)                 isgraph(a)
#define isLowerCase(a)             islower(a)
#define isPrintable(a)             isprint(a)
#define isPunct(a)                 ispunct(a)
#define isSpace(a)                 (((uint8_t) a) == 32 ? (1) : (0))
#define isUpperCase(a)             isupper(a)
#define isHexadecimalDigit(a)      isxdigit(a)

/*---
 random numbers
---*/
#define randomSeed(seed)           srand(seed)
#define random()                   rand()
#define randomIn(Min,Max)          (Min + random() % (Max-Min+1))

/*---
 bits and bytes
---*/
#define bit(n)                     (1 << n)                                    ///< get bit value 2^n
#define bitClear(b,n)              (b &= ~(1 << n))                            ///< clear single bit in data to '0'
#define bitRead(b,n)               ((b & (1 << n)) >> n)                       ///< read single bit position in byte
#define bitSet(b,n)                (b |= (1 << n))                             ///< set single bit in data to '1'
#define bitToggle(b,n)             (b ^= (1 << n))                             ///< toggle single bit state in byte
#define bitWrite(b,n,value)        (value?(b|=(1<<n)):(b&=~(1<<n)))            ///< set single bit value in byte to value
#define lowByte(x)                 ((uint8_t) x)                               ///< get low (=rightmost) byte from x
#define highByte(x)                ((uint8_t) (((uint16_t) x) >> 8))           ///< get high (=2nd) byte from a word
#define concatBytes(hb,lb)         ((((uint16_t)hb) << 8) | ((uint16_t)lb))    ///< concat 2 bytes to a 16bit word 


/*---
 interrupts
---*/
#define interrupts()              ENABLE_INTERRUPTS
#define noInterrupts()            DISABLE_INTERRUPTS


/*----------------
 additional commands 
----------------*/

/*---
 rounding functions
---*/
#define round(a)                   ((uint32_t)((float) a + 0.50001))           ///< round a floating point value
#define ceil(a)                    ceilf(a)                                    ///< round to next lower integer, use compiler function
#define floor(a)                   floorf(a)                                   ///< round to next higher integer, use compiler function

/*---
 conversion
---*/
#define toASCII(a)                 toascii(a)
#define toUpperCase(a)             toupper(a)
#define toLowerCase(a)             tolower(a)


/*----------------
 pre-defined values
----------------*/

#define PI                          3.141592653                       ///< Archimedes' constant 
#define EUL                         2.718281828                       ///< Euler number
#define SQRT2                       1.414213562                       ///< square root of two
#define SQRT3                       1.732050807                       ///< square root of three


/*-----------------------------------------------------------------------------
    DECLARATION OF GLOBAL FUNCTIONS
-----------------------------------------------------------------------------*/

/// simple calculation of log2(x)
uint8_t log2(uint32_t arg);

#if defined(USE_FTOA)
  /// convert float to ascii string for printf() output. Adds ~3.3kB -> require USE_FTOA
  char *floatToString(char *buf, float f, uint8_t digits);
#endif


/*-----------------------------------------------------------------------------
    END OF MODULE DEFINITION FOR MULTIPLE INLUSION
-----------------------------------------------------------------------------*/
#endif // _MISC_H_
