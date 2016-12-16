
/*
 *
 */


#include "debug.h"
 #include "Arduino.h"
 #include <portable.h>
 #include <hardwareDrive.h>

 #define DEBUG
 #define mwLight_DEBUG

  void DEBUG_LED_init(){
    pinMode( DEBUG_R, OUTPUT );    digitalWrite ( DEBUG_R, HIGH );               /* vcc|-----|\/\/\----|>|------|=> D12 */ 
    pinMode( DEBUG_G, OUTPUT );    digitalWrite ( DEBUG_G, HIGH );
    pinMode( DEBUG_Y, OUTPUT );    digitalWrite ( DEBUG_Y, HIGH );      /* vcc|-----|\/\/\----|>|------|=> D10 */  

//    setGPIO_mode( DEBUG_R, OUTPUT );    setGPIO_level ( DEBUG_R, LOW );               /* vcc|-----|\/\/\----|>|------|=> D12 */ 
//    setGPIO_mode( DEBUG_G, OUTPUT );    setGPIO_level ( DEBUG_G, LOW );
//    setGPIO_mode( DEBUG_Y, OUTPUT );    setGPIO_level ( DEBUG_Y, LOW );      /* vcc|-----|\/\/\----|>|------|=> D10 */  
  }

//#ifdef mwLight_DEBUG
//    void paired_ON(void){  setGPIO_level( DEBUG_Y, LOW ); }
//    void paired_OFF(void){  setGPIO_level( DEBUG_Y, HIGH ); }
//
//  void RXD_ON(void){  setGPIO_level( DEBUG_G, LOW ); }
//  void RXD_OFF(void){ setGPIO_level( DEBUG_G, HIGH); }
//
//  void SYN_ON(void){  setGPIO_level( DEBUG_R, LOW); }
//  void SYN_OFF(void){ setGPIO_level(DEBUG_R, HIGH); }

    void paired_ON(void){  digitalWrite( DEBUG_Y, LOW ); }
    void paired_OFF(void){  digitalWrite( DEBUG_Y, HIGH ); }

  void RXD_ON(void){  digitalWrite( DEBUG_G, LOW ); }
  void RXD_OFF(void){ digitalWrite( DEBUG_G, HIGH); }

  void SYN_ON(void){  digitalWrite( DEBUG_R, LOW); }
  void SYN_OFF(void){ digitalWrite(DEBUG_R, HIGH); }
//#endif /* mwLight_DEBUG */









