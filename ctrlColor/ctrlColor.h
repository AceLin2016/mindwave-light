
/*
 * 
 */
 #ifndef CTRLCOLOR_H
 #define CTRLCOLOR_H

 #include "Arduino.h" 

//  #include <portable.h>
//  //#include <ctrlColor.h>
//  //#include <setColorFromData.h>
//  #include <hardwareDrive.h>
 #include "portable.h"
 //#include <ctrlColor.h>
 //#include <setColorFromData.h>
 #include "hardwareDrive.h"

 /****** ctrlColor.h ****************/
 /* 要设置的灯的颜色 */
 typedef enum { 
 			   RED=1, ORANGE, YELLOW, GREEN, BLUE, CYAN, PURPLE, FOOCOLOR
 	/*         红色   橙色    黄色    绿色   蓝色  青色  紫色            
  	 *         0-20   20-30   30-40   40-60  60-70  70-80 80-100         */
 			 }color_t;

 /* 构造三种颜色灯对象 */
 typedef struct primaryColorPin{
 	 /* primaryColorPin_number */
 		const uint16_t led_red_pin = 9;
 		const uint16_t led_green_pin = 6;
 		const uint16_t led_blue_pin = 5;

 	 /* primaryColorPin_state */
 		B_level_t led_red_level;
 	 	B_level_t led_green_level;
   		B_level_t led_blue_level;
 }RGB_pin_t;
 
 void RGB_light_init(void);

#if 1
 void RED_ON();
 void RED_OFF();

 void GREEN_ON();
 void GREEN_OFF();

 void	BLUE_ON();
 void	BLUE_OFF();
#endif

 void setLightColor( color_t _lightColor );


#endif /* CTRLCOLOR_H */
