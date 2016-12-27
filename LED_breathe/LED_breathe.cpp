

#include "LED_breathe.h"



#ifdef __cpluscplus
extern "C" {
#endif /* def __cpluscplus */
// #include <portable.h>
// #include <ctrlColor.h>
 #include "portable.h"
 #include "ctrlColor.h"

/*** Class init and cleanup ***/
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
                    )
 {  // begin class init
    me->Red_pin = 9;         // 初始化为一个不存在的引脚
    me->Green_pin = 6;
    me->Blue_pin = 5;

    me->increment = -1;
    me->brightness = 255;
    me->OKbreathe = B_TRUE;

    me->pin_init = func_pin_init;
    me->breathe = func_breathe;
    me->pin_turnTo_digital = func_pin_turnTo_digital;
 } // end class init

  void breathe_t_Cleanup( breathe_t* const me){
  } // end class cleanup



/*********** Object function **********************/
 void breathe_pin_init(
                    breathe_t* const me, 
                    uint16_t _Red_pin,
                    uint16_t _Green_pin,
                    uint16_t _Blue_pin
                    )
 {
    me->Red_pin = _Red_pin;
    me->Green_pin = _Green_pin;
    me->Blue_pin = _Blue_pin;
 }

  void breathe_pin_turnTo_digital(breathe_t* const me){
     pinMode( me->Red_pin, OUTPUT);
     pinMode( me->Green_pin, OUTPUT);
     pinMode( me->Blue_pin, OUTPUT);
     digitalWrite( me->Red_pin, LOW); 
     digitalWrite(me->Green_pin, LOW);
     digitalWrite(me->Blue_pin, LOW);               // 全亮，白灯
  }

 /*
 * Example:     myBreathe.breathe(&myBreathe, YELLOW); */
 void breathe_breathe(breathe_t* const me, color_t _color)
 { // 主程序调用本函数实现呼吸灯闪烁三下
    volatile int CNT=-1;  
    me->OKbreathe = B_FALSE;                        // 用于判断是否呼吸三次完成
    me->increment = -1;                             // 引脚连接的是led负极，变亮的过程是减
    me->brightness = 255;                           // 255->灭灯

    while( me->OKbreathe == B_FALSE){  // 呼吸灯状态变换未完成
        if( me->brightness > 254 ){ // 灯灭状态
            delay(1000);                            // 呼吸到灯灭，停1s
            me->increment = -1;                     // 逐减，变亮
            CNT++;
        } // end if brightne > 255
        else if( me->brightness < 3 ){ // 灯亮状态
            me->increment = 1;                      // 逐增，变暗
        } // end if brightness <　3
        me->brightness += me->increment;
        switch( _color ){ // 要呼吸那种颜色的
            case YELLOW:                            // 注意力 110
                        analogWrite(me->Red_pin, me->brightness);
                        analogWrite(me->Green_pin, me->brightness);
                        analogWrite(me->Blue_pin, VAL_LIGHT_OFF);
                        break;
            case BLUE:                              // 放松度
                        analogWrite(me->Blue_pin, me->brightness);
                        analogWrite(me->Red_pin, VAL_LIGHT_OFF);
                        analogWrite(me->Green_pin, VAL_LIGHT_OFF);
                        break;
            case ORANGE:                             // turn_off
                        analogWrite(me->Red_pin, me->brightness);
                        analogWrite(me->Green_pin, me->brightness);
                        analogWrite(me->Blue_pin, me->brightness);
                        break;
            default:    break;
        }
        delay(me->brightness/10);                       // 我也不知道怎么解释这句
        if(CNT > 3) // 0、1、【2，OKbreathe++】，三次
           me->OKbreathe = B_TRUE;
    } // end while
 }



/*--- Create Object and Destroy it ---*/
 void breathe_Create( breathe_t* newObject ){
     breathe_t* me = ( breathe_t*)malloc(sizeof(breathe_t));
     if (me=NULL){
         breathe_t_Init(
                    me,
                    breathe_pin_init,
                    breathe_breathe,
                    breathe_pin_turnTo_digital
                    );
     }
     *newObject = *me;
     breathe_Destroy( me );
 } // end Object Create

 void breathe_Destroy( breathe_t* theObject ){
     if( theObject != NULL ){
         breathe_t_Cleanup( theObject );
     }
     free( theObject );
 } // end Object Destroy

#ifdef __cpluscplus
}
#endif /* def __cpluscplus */
