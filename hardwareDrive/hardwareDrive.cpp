
/*
 *
 */

//  #include "hardwareDrive.h"

  #include "Arduino.h"
  #include "portable.h"
  #include "hardwareDrive.h"
 //#include <portable.h>
 //#include <hardwareDrive.h>


void delay_ms(uint16_t _ms){
     delay(_ms);
 }

 /*************** GPIO Drive ************************************/
 //void setGPIO_mode( uint16_t _pin, uint16_t _mode );
 void setGPIO_mode( uint16_t _pin, gpioMode_t _mode ){
     switch(_mode){
         case INPUT_mulpx: pinMode( _pin, INPUT ); break;
         case INPUT_PULLUP_mulpx: pinMode( _pin, INPUT_PULLUP ); break;
         case OUTPUT_mulpx: pinMode( _pin, OUTPUT ); break;
     }
     //pinMode( _pin, _mode );
 }


 //void setGPIO_level( uint16_t _pin, B_level_t _level ); // typedef enum{ B_HIGH = 0, B_LOW = 1 }boolean_t;
 void setGPIO_level( uint16_t _pin, B_level_t _level ){
      digitalWrite( _pin, _level );
 }




