
/*
 *
 */
#ifndef LED_BREATHE_H_
#define LED_BREATHE_H_


#include "Arduino.h"

#ifdef __cpluscplus
extern "C" {
#endif /* def __cpluscplus */
 #include <stdlib.h>
// #include <portable.h>
// #include <ctrlColor.h>
 #include "portable.h"
 #include "ctrlColor.h"

 #define VAL_LIGHT_OFF  255

 typedef struct breathe breathe_t;
 struct breathe{
     uint16_t Red_pin;
     uint16_t Green_pin;
     uint16_t Blue_pin;

     int increment;
     uint16_t brightness;
     boolean_t OKbreathe;
     
     void (* pin_init)( breathe_t* const me);
     void (* breathe)( breathe_t* const me, color_t _color);
     void (* pin_turnTo_digital)( breathe_t* const me );
 };

 void breathe_t_Init( 
                    breathe_t* const me,
                    void (* func_pin_init)(
                                        breathe_t* const me,
                                        uint16_t _Red_pin,
                                        uint16_t _Green_pin,
                                        uint16_t _Blue_pin
                        ),
                    void (* func_breathe)( 
                                        breathe_t* const me,
                                        color_t _color
                        ),
                    void (* func_pin_turnTo_digital)( breathe_t* const me)
        );

 void breathe_t_Cleanup( breathe_t* const me);




 void breathe_pin_init(
                    breathe_t* const me, 
                    uint16_t _Red_pin,
                    uint16_t _Green_pin,
                    uint16_t _Blue_pin
                    );
 void breathe_breathe(
                    breathe_t* const me,
                    color_t _color
                    );
 void breathe_pin_turnTo_digital(
                    breathe_t* const me
                    );


 //breathe_t* breathe_Create(void);
 void breathe_Create( breathe_t* newObject );
 void breathe_Destroy( breathe_t* me );


#ifdef __cpluscplus
}
#endif /* def __cpluscplus */

#endif /* LED_BREATHE_H_ */
