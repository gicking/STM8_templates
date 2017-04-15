/**
  \file getchar.c
   
  \author G. Icking-Konert
  \date 2017-04-15
  \version 0.1
   
  \brief implementation of getchar() function for gets()
   
  implementation of getchar() function required for stdio.h
  functions, e.g. gets(). 
*/

/*-----------------------------------------------------------------------------
    INCLUDE FILES
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "getchar.h"


/*-----------------------------------------------------------------------------
    DECLARATION OF MODULE VARIABLES
-----------------------------------------------------------------------------*/
 
volatile uint8_t (*m_getchar_Rx_pFct)(void) = getchar_Default;   ///< pointer to gets()/getchar() receive routine


/*----------------------------------------------------------
    FUNCTIONS
----------------------------------------------------------*/

/**
  \fn uint8_t getchar_Default(void)
   
  \brief dummy getchar() receive function
  
  \return received byte

  Dummy receive routine for getchar() / gets().
  Doesn't do anything. Is used because this is faster than
  an if check for a NULL pointer
*/
uint8_t getchar_Default(void) {
  
  // dummy
  return(0);
  
} // getchar_Default



/**
  \fn void getcharAttach(uint8_t (*pFct)(void));
   
  \brief set getchar() receive function
  
  \param[in]  pFct  receive to use in getchar()
   
  set receive function to use in getchar(). Is required for gets()
*/
void getcharAttach(uint8_t (*pFct)(void)) {

  // set receive function for getchar()
  m_getchar_Rx_pFct = pFct;
    
} // getcharAttach
  
  
  
/**
  \fn char getchar(void) 
   
  \brief receive byte
  
  \return  character received or zero on error.

  implementation of getchar() for gets(), using selected input channel.
  Use receive routine set via getchar_attach()
  Return type depends on used compiler (see respective stdio.h)
*/
char getchar(void) {

  char c;

  // call receive function
  c = m_getchar_Rx_pFct();

  // return received byte
  return c;
  
} // getchar


/*-----------------------------------------------------------------------------
    END OF MODULE
-----------------------------------------------------------------------------*/
