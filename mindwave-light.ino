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

/*** 配置低功耗 ***/
#include<Enerlib.h>

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
uint16_t change_moment = 0;                // 标志此时是否处于切换状态的瞬间，如果是，指示灯需要针对闪烁
void OFF_Light();

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


/*** 加入低功耗 *****/
Energy lowPower;                        // 定义低功耗类对象
const uint16_t whether_Sleep_pin = 3;   // pin3读取电平状态判断是否需要进入睡眠模式
const uint16_t ctrlSleep_pin = 17;      // pin17(A3) 根据chooseOneMode输出高低
void lowPower_pin_init(){
    pinMode( whether_Sleep_pin, INPUT_PULLUP );
    pinMode( ctrlSleep_pin, OUTPUT );
    digitalWrite( ctrlSleep_pin, HIGH );
}


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
  
  lowPower_pin_init();                        /* 低功耗模式引脚控制 */
  pinMode( KEY_MODE, INPUT_PULLUP );
  attachInterrupt( digitalPinToInterrupt( KEY_MODE ), chooseMode, FALLING);   // LOW-低电平触发中断会出现问题，多次进入中断
  forceFlush();
}



color_t lightColor = FOOCOLOR;              // RBG灯对象，设定颜色即可
uint8_t Rx_data;                            // 从连接蓝牙模块的虚拟串口接收到的数据
/***************************   loop()   *************************/
void loop(){
    if ( Sleep_or_Work == SLEEP ){ // 进入低功耗模式
        if ( change_moment == 1 ){  // 如果这个按键更改模式的时刻...
          OFF_Light();   delay_ms( 1500); 
          OFF_Light();
          change_moment = 0;
        }
        digitalWrite ( BLElight.EN_PIN, LOW );                // 这一句后期调整成面向对象模式
        digitalWrite( ctrlSleep_pin, LOW );
        if( chooseOneMode == TURN_OFF ){
            // digitalWrite( 11, HIGH );
            lightColor = FOOCOLOR;
            setLightColor( FOOCOLOR );
            if( digitalRead( whether_Sleep_pin ) == LOW )
                Serial.println( "Enter into SLEEP in... ");
                Serial.println( " 3 ");
                Serial.println( " 2 ");
                Serial.println( " 1 ");
                lowPower.PowerDown();                            // 进入低功耗
        } // end if TURN_OFF 
    }
    else if ( Sleep_or_Work == WORK ){
          if( change_moment == 1 ){
            switch( chooseOneMode ){
              case MEDITATION:
                    change_moment = 1;
                    lightColor = BLUE;
                    setLightColor( FOOCOLOR );  delay_ms( 1000 );
                    setLightColor( lightColor );    delay_ms( 1000 );
                    setLightColor( FOOCOLOR );  delay_ms( 1000 );
                    setLightColor( lightColor );    delay_ms( 1000 );
                    setLightColor( FOOCOLOR );  delay_ms( 1000 );
                    setLightColor( lightColor );
                    break;
              case ATTENTION:
                    lightColor = YELLOW;
                    setLightColor( FOOCOLOR );  delay_ms( 1000 );
                    setLightColor( lightColor );    delay_ms( 1000 );
                    setLightColor( FOOCOLOR );  delay_ms( 1000 );
                    setLightColor( lightColor );    delay_ms( 1000 );
                    setLightColor( FOOCOLOR );  delay_ms( 1000 );
                    setLightColor( lightColor );  
                    break;
            } // end switch()
            change_moment = 0;
          }
          digitalWrite( ctrlSleep_pin, HIGH );
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

void blinkLight( color_t _color, uint16_t _period_ms ){
  uint16_t i=0, j= 1000/_period_ms;
  for ( i=0; i<j; i++){
    setLightColor( FOOCOLOR );  delay_ms( _period_ms );
    setLightColor( _color );    delay_ms( _period_ms );
  }
}

void breatheLight( color_t _color ){
  uint16_t i=0, times = 10;
  for( i=0; i<5; i++){   //  越亮
      blinkLight( _color, times );
      //delay_ms( times );
      times += 10;
  }
  setLightColor( _color );
  for( i=0; i<50; i++){ //  越暗
      setLightColor( _color );
      delay_ms( 10 );
      setLightColor( FOOCOLOR );
      delay_ms( times );
      times += 10;
  }
  setLightColor( FOOCOLOR );
}
void OFF_Light(){
    setLightColor( FOOCOLOR ); delay_ms( 800 ); 
    setLightColor( ORANGE );  delay_ms(1000);
    setLightColor( FOOCOLOR ); delay_ms( 1000 ); 
    setLightColor( ORANGE );  delay_ms(1000);
    setLightColor( FOOCOLOR );
}


void chooseMode(void){
  static MODE_t lastMode = MEDITATION;
  delay_ms( 10 );
  forceFlush();

  if ( digitalRead(KEY_MODE) == LOW ){
      if( lowPower.WasSleeping() )  delay(10);        // 推出低功耗模式

      switch ( lastMode ){
      case MEDITATION:
                    forceFlush();
                    Sleep_or_Work = WORK;  
                    chooseOneMode = ATTENTION; 
                    lastMode = ATTENTION;
                    Serial.println( "get into Attention mode " );
                    change_moment = 1;
                    break;
      case ATTENTION: 
                    forceFlush();
                    Sleep_or_Work = SLEEP; 
                    chooseOneMode = TURN_OFF; 
                    lastMode = TURN_OFF;
                    Serial.println( "get into low power mode" );
                    change_moment = 1;
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






