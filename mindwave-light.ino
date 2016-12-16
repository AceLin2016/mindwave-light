/* 2016/12/02 13:33 
 * 脑波灯程序
 * 
 */

#include <SoftwareSerial.h>

 #include <portable.h>
 #include <ctrlColor.h>
 #include <setColorFromData.h>
 #include <hardwareDrive.h>
 #include "mindwave_light.h"

 #include "BLE.h"
 #include "debug.h"

 #define DEBUG
 #define mwLight_DEBUG

/*================= 蓝牙模块相关  BLE.h ==================================*/
/*================= end 蓝牙模块相关 ==================================*/



/******* main ************************/
void forceFlush(){
    while( Serial.available()>0 ){
      Serial.read();
      RXD_ON();
    } // end while available
}

 // 脑波灯需要对象、标志位等相关...
 //const uint8_t interruptPin = 2;

/* 12/09 11:17 加入按键中断 */
const uint8_t KEY_MODE = 2;
typedef enum{ MEDITATION=0, ATTENTION,  TURN_OFF }MODE_t;
//typedef enum{ TURN_ON = 0, TURN_OFF }MODE_t;
MODE_t chooseOneMode = MEDITATION;

/*** 大灯专有属性，按键切换模式，进入关闭状态（睡眠） ***/
typedef enum{ SLEEP = 0, WORK }sw_t;
sw_t Sleep_or_Work = WORK;                 // 定义初始状态在工作状态

#if 0
  SoftwareSerial mySerial =  SoftwareSerial(8, 7);
  void SoftwareSerial_init( void ){
    pinMode( 8, INPUT );
    pinMode( 7, OUTPUT );
    mySerial.begin(57600);                            // 与蓝牙模块连接的波特率
 }
#endif


/*** 定义蓝牙模块在本实例电路中连接的引脚 ***/
BLE_module_t BLElight;            // 在定义一个struct 对象时，如何初始化？


void setup(){
	//SoftwareSerial_init();              // 与蓝牙连接的IO口-> 模拟串口初始化 
  forceFlush();                                    
  BLE_PIN_config( &BLElight );                     // 在函数中构造蓝牙模块各个控制引脚
  BLE_PIN_INIT( &BLElight );                       // 蓝牙模块的各个控制引脚（状态）初始化--> 对象以MCU为标准命名
  
  forceFlush();
  RGB_light_init();                              // 脑波灯（RGB三色灯） 控制引脚初始化
  DEBUG_LED_init();                              // 调试指示灯控制引脚初始化
  pinMode( TEST_LED, OUTPUT );    digitalWrite ( TEST_LED, LOW );
  
  forceFlush();
	structureMindwaveData();			                // 初始化对象数据
  
  #ifdef DEBUG
    forceFlush();
    Serial.begin( 57600 );
    setLightColor( RED );
    delay_ms(1500);
    setLightColor( FOOCOLOR );
  #endif /* DEBUG */

  // add KEY_MODE
  forceFlush();
  pinMode( KEY_MODE, INPUT_PULLUP );
  attachInterrupt( digitalPinToInterrupt( KEY_MODE ), chooseMode, FALLING);
  forceFlush();
}



color_t lightColor = FOOCOLOR;              // RBG灯对象，设定颜色即可
uint8_t Rx_data;                            // 从连接蓝牙模块的虚拟串口接收到的数据
/***************************   loop()   *************************/
void loop(){
    if ( Sleep_or_Work == SLEEP ){                            // 进入低功耗模式
        digitalWrite ( BLElight.EN_PIN, LOW );                // 这一句后期调整成面向对象模式
        if( chooseOneMode == TURN_OFF ){
            // digitalWrite( 11, HIGH );
            lightColor = FOOCOLOR;
            setLightColor( FOOCOLOR );
        } // end if TURN_OFF 
    }
    else if ( Sleep_or_Work == WORK ){
          digitalWrite ( BLElight.EN_PIN, HIGH );                // 打开蓝牙
          if( ifSuccess_got_data()== FAIL ){
            if( Serial.available() > 0 ){
              Rx_data = Serial.read();
              getMindwaveData( Rx_data );  
              RXD_ON();
            }
            else{
               RXD_OFF();
            //setLightColor( FOOCOLOR );
            }
          } // end if not ifSuccess_got_data
          else if ( ifSuccess_got_data() == PASS ){
            forceFlush();
        
            RXD_OFF();
            switch( chooseOneMode ){
            case MEDITATION:
                            forceFlush();
                            lightColor = getSuitLightColor( getMeditation() );  
                            break;
            case ATTENTION:
                            forceFlush();
                            lightColor = getSuitLightColor( getAttention() );          
                            break;
            } // end switch
            setLightColor( lightColor );
            set_Got_data(FAIL);    
        
            forceFlush();
            RXD_OFF();
          } // end else if
    } // end if work
} // end loop



/**** main *******/
#ifdef DEBUG
 void testLED_blink( void ){
  static byte LED_STA = 0;
  if (LED_STA) LED_STA = 0;
  else LED_STA = 1;
  digitalWrite( TEST_LED, LED_STA);
 }
#endif /* debug */

void chooseMode(void){
  static MODE_t lastMode = MEDITATION;
  forceFlush();
  delay_ms( 10 );
  forceFlush();
  if ( digitalRead(KEY_MODE) == LOW ){

      switch ( lastMode ){
      case MEDITATION:
                    forceFlush();
                    Sleep_or_Work = WORK;  
                    chooseOneMode = ATTENTION; 
                    lastMode = ATTENTION;
                    Serial.println( "get into Attention mode " );
                    break;
      case ATTENTION: 
                    forceFlush();
                    Sleep_or_Work = SLEEP; 
                    chooseOneMode = TURN_OFF; 
                    lastMode = TURN_OFF;
                    Serial.println( "get into low power mode" );
                    break;

      case TURN_OFF: 
                    forceFlush();
                    Sleep_or_Work = WORK; 
                    chooseOneMode = MEDITATION; 
                    lastMode = MEDITATION;
                    Serial.println( "get into Medition mode " );
                    break;        
      }// end switch lastMode
      forceFlush();
  }// end if KEY_MODE = LOW

}// end func chooseMode






