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
#define wordConcat(hb,lb)         ((((uint16_t)hb) << 8) | ((uint16_t)lb))
#define long(a)                   ((int32_t)(a))
#define float(a)                  ((float)(a))

/*---
 math
---*/
#define min(a,b)                   ((a < b) ?  (a) : (b))                      ///< minimum of 2 numbers
#define max(a,b)                   ((a > b) ?  (a) : (b))                      ///< maximum of 2 numbers
//#define abs(x)                     (((x) < 0) ? -(x) : (x))                    // absolute value of number (obsolete: already part of SDCC)
#define constrain(x,low,high)      ((x)<(low)?(low):((x)>(high)?(high):(x)))   ///< clip value to range [low;high]
#define map(x,inMin,inMax,outMin,outMax)  ((x-inMin)*(outMax-outMin)/(inMax-inMin)+outMin)  ///< re-map a number from one range to another
#define pow(x,y)                   powf(x,y)
#define sqrt(x)                    sqrtf(x)

/*---
 trigonometry
---*/
#define sin(x)                     sinf(x)
#define cos(x)                     cosf(x)
#define tan(x)                     tanf(x)

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
#define random()                   rand()
#define randomSeed(seed)           srand(seed)

/*---
 bits and bytes
---*/
#define lowByte(x)                 ((uint8_t) x)                               ///< get low (=rightmost) byte from x
#define highByte(x)                ((uint8_t) (((uint16_t) x) >> 8))           ///< get high (=2nd) byte from a word
#define bitRead(b,n)               ((b & (1 << n)) >> n)                       ///< read single bit position in byte
#define bitWrite(b,n,value)        (value?(b|=(1<<n)):(b&=~(1<<n)))            ///< set single bit value in byte to value
#define bitSet(b,n)                (b |= (1 << n))                             ///< set single bit in data to '1'
#define bitClear(b,n)              (b &= ~(1 << n))                            ///< clear single bit in data to '0'
#define bitToggle(b,n)             (b ^= (1 << n))                             ///< toggle single bit state in byte
#define bit(n)                     (1 << n)                                    ///< get bit value 2^n

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
