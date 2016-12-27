/*
 * 
 */

//  #include "ctrlColor.h"

  #include "Arduino.h"
  #include "portable.h"
  #include "hardwareDrive.h"
  #include "ctrlColor.h"
//  #include <portable.h>
//  #include <ctrlColor.h>
//  //#include <setColorFromData.h>
//  #include <hardwareDrive.h>

 RGB_pin_t _COLOR_ON_OFF_API;

static void forceFlush(){
    while( Serial.available()>0 ){
      Serial.read();
    } // end while available
}

 void RGB_light_init(void){
     setGPIO_mode(_COLOR_ON_OFF_API.led_red_pin, OUTPUT_mulpx);
     setGPIO_mode(_COLOR_ON_OFF_API.led_green_pin, OUTPUT_mulpx);
     setGPIO_mode(_COLOR_ON_OFF_API.led_blue_pin, OUTPUT_mulpx);
     RED_OFF(); GREEN_OFF(); BLUE_OFF();
 }

#if 1
 void RED_ON(){	setGPIO_level(_COLOR_ON_OFF_API.led_red_pin,B_LOW); }
 void RED_OFF(){ setGPIO_level(_COLOR_ON_OFF_API.led_red_pin,B_HIGH); }

 void GREEN_ON(){ setGPIO_level(_COLOR_ON_OFF_API.led_green_pin,B_LOW); }
 void GREEN_OFF(){ setGPIO_level(_COLOR_ON_OFF_API.led_green_pin,B_HIGH); }

 void	BLUE_ON(){ setGPIO_level(_COLOR_ON_OFF_API.led_blue_pin,B_LOW); }
 void	BLUE_OFF(){ setGPIO_level(_COLOR_ON_OFF_API.led_blue_pin,B_HIGH); }
#endif

void setLightColor( color_t _lightColor ){
 	switch( _lightColor ){
 		case RED: //1
 							//forceFlush();
 							RED_ON();	GREEN_OFF();	BLUE_OFF(); // 100
 							delay_ms( 1000 );
 							break;
  		case ORANGE: //2
 									//forceFlush();
  						    RED_ON();	GREEN_ON();	BLUE_ON(); // 111
  						    delay_ms( 1000 );
 						    break;				
 		case YELLOW: //3
 							//forceFlush();
 							RED_ON();	GREEN_ON();	BLUE_OFF(); // 110
 							delay_ms( 1000 );
 							break;
 		case GREEN: //4
 							//forceFlush();
 							RED_OFF();	GREEN_ON();	BLUE_OFF(); //010
 							delay_ms( 1000 );
 							break;
 		case BLUE: //5
 							//forceFlush();
 							RED_OFF();	GREEN_OFF();	BLUE_ON(); //001
 							delay_ms( 1000 );
 							break;
 		case CYAN: //6
 							//forceFlush();
 							RED_OFF();	GREEN_ON();	BLUE_ON(); //011
 							delay_ms( 1000 );
 							break;
 		case PURPLE: //7
 							//forceFlush();
 							RED_ON();	GREEN_OFF();	BLUE_ON(); // 101
 							delay_ms( 1000 );
 							break;
 		case FOOCOLOR:
 							//forceFlush();
 							RED_OFF(); GREEN_OFF(); BLUE_OFF();
 							delay_ms( 10 );
 							break;
 	} // end switch
 } // end func set color








