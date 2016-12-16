#ifndef DEBUG_H
#define DEBUG_H


#include "Arduino.h"
#include <portable.h>
#include <hardwareDrive.h>


//  #define DEBUG
//  #define mwLight_DEBUG

 //#ifdef DEBUG
  const uint8_t TEST_LED = 13;
  void testLED_blink( void );
  
  const uint8_t DEBUG_R = 10;
  const uint8_t DEBUG_G = 11;
  const uint8_t DEBUG_Y = 12;
  void DEBUG_LED_init();
 //#endif /* DEBUG */

//#ifdef mwLight_DEBUG
    void paired_ON(void);
    void paired_OFF(void);

  void RXD_ON(void);
  void RXD_OFF(void);

  void SYN_ON(void);
  void SYN_OFF(void);
//#endif /* mwLight_DEBUG */




#endif /* DEBUG_H */
