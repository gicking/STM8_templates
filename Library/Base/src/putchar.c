/**
  \file putchar.c
   
  \author G. Icking-Konert
  \date 2015-04-09
  \version 0.1
   
  \brief implementation of putchar() function for printf()
   
  implementation of putchar() function required for stdio.h
  functions, e.g. printf().
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "putchar.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/
 
volatile void (*m_putchar_Tx_pFct)(uint8_t) = putchar_Default;   ///< pointer to printf()/putchar() send routine


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn void putchar_Default(uint8_t c)
   
  \brief dummy putchar() send function
  
  \param[in]  c  char to (not) send
   
  Dummy send routine for putchar() / printf().
  Doesn't do anything. Is used because this is faster than
  an if check for a NULL pointer
*/
void putchar_Default(uint8_t c) {
  
  // do nothing but avoid compiler warning
  (void) c;
  
  // dummy
  
} // putchar_Default



/**
  \fn void putcharAttach(void (*pFct)(uint8_t))
   
  \brief set putchar() send function
  
  \param[in]  pFct  send to use in putchar()
   
  set send function to use in putchar(). Is required for printf()
*/
void putcharAttach(void (*pFct)(uint8_t)) {

  // set send function for putchar()
  m_putchar_Tx_pFct = pFct;
    
} // putcharAttach
  
  
  
/**
  \fn void putchar(char byte)
   
  \brief output routine for printf()
  
  \param[in]  byte   data to send
  
  \return  always zero (Cosmic & SDCC >=3.6.0)

  implementation of putchar() for printf(), using selected output channel.
  Use send routine set via putchar_attach()
  Return type depends on used compiler (see respective stdio.h)
*/
#if defined(__CSMC__)
  char putchar(char byte) {
#elif defined(__SDCC)
  #if SDCC_VERSION >= 30600  // declaration changed after sdcc 3.6.0
    int putchar(int byte) {
  #else
    void putchar(char byte) {
    #define VOID_PUTCHAR
  #endif
#else
  int putchar(char byte) {
#endif
 
  // NL -> add CR
  if (byte=='\n') {
     (*m_putchar_Tx_pFct)(13);
     (*m_putchar_Tx_pFct)(10);
  }
  else
    (*m_putchar_Tx_pFct)(byte);
  
  // avoid warning message (except for void function)
  #if !defined(VOID_PUTCHAR)
    return(0);
  #else
    #undef VOID_PUTCHAR
  #endif
  
} // putchar

/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
