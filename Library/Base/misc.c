/**
  \file misc.h
   
  \author G. Icking-Konert
  \date 2008-11-02
  \version 0.1
   
  \brief implementation of misc macros & inline routines
   
  implementation of macros & inline routines not really 
  fitting anywhere else. Mostly for Arduino compatibility
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "config.h"     // for optional features
#include "stm8as.h"     // STM8 registers etc.
#include "misc.h"
#if defined(USE_FTOA)
  #include <stdio.h>
#endif


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint8_t log2(uint32_t arg)
  
  \brief simple calculation of log2(x)
  
  \param[in]  arg   log2 argument. Has to be positive.

  \return result of log2(arg)
  
  simple calculation of log2(x) in O(log(N)). Basically
  compare argument vs. 1<<n with increasing n
*/
uint8_t log2(uint32_t arg) {

  uint8_t result = 0;
  
  while ((1L<<result) < arg)
    result++;
    
  return(result);

} // log2



/**
  \fn void floatToString(float f, uint8_t digits)
   
  \brief convert float to ascii string
  
  \param[out] buf     string to convert into
  \param[in]  value   floating number to convert
  \param[in]  digits  number of digits
  
  \return buf

  Convert a floating point number to C-terminated string.
  Can be used e.g. for printing floats via printf(), which
  is not supported natively by SDCC.
  Does not support scientific notation, e.g. 1.2e5.
*/
#if defined(USE_FTOA)
  char *floatToString(char *buf, float f, uint8_t digits) {

    uint8_t   i;
    uint32_t  scale;
    char      fmt[10];

    // clip digits to 6
    if (digits > 6)
      digits = 6;

    // convert digits to scale for base 10
    scale = 1;
    for (i=0; i<digits; i++)
      scale *= 10;
 
    // required for -0.x and trailing 0
    if (f < 0.0)
      sprintf(fmt, "-%%ld.%%0%dld", digits);
    else
      sprintf(fmt,  "%%ld.%%0%dld", digits);

    // convert int to string
    sprintf(buf, fmt, abs((int32_t) f), abs((int32_t)((f-(float)((int32_t)f))*scale)));
  
    // return buf
    return(buf);

  } // floatToString
#endif // USE_FTOA

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
