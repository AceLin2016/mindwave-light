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

 #define DEBUG
 #define mwLight_DEBUG

 #ifdef DEBUG
  const uint8_t TEST_LED = 13;
  void testLED_blink( void );
  
  const uint8_t DEBUG_R = 10;
  const uint8_t DEBUG_G = 11;
  const uint8_t DEBUG_Y = 12;
  void DEBUG_LED_init(){
    pinMode( DEBUG_R, OUTPUT );    digitalWrite ( DEBUG_R, HIGH );               /* vcc|-----|\/\/\----|>|------|=> D12 */ 
    pinMode( DEBUG_G, OUTPUT );    digitalWrite ( DEBUG_G, HIGH );
    pinMode( DEBUG_Y, OUTPUT );    digitalWrite ( DEBUG_Y, HIGH );      /* vcc|-----|\/\/\----|>|------|=> D10 */     
  }
 #endif /* DEBUG */

#ifdef mwLight_DEBUG
  void RXD_ON(void){  digitalWrite( DEBUG_G, LOW );
  void RXD_OFF(void){ digitalWrite( DEBUG_G, HIGH);

  void SYN_ON(void){  digitalWrite( DEBUG_R, LOW);
  void SYN_OFF(void){ digitalWrite(DEBUG_R, HIGH);
#endif /* mwLight_DEBUG */

/******* main ************************/

//extern SoftwareSerial mySerial;

 // bluetooth  相关
 const uint8_t BLE_STA = 5;
 const uint8_t BLE_EN = 4;


 // 脑波灯需要对象、标志位等相关...
 //const uint8_t interruptPin = 2;

 mwData_t mindwaveLight;                // 定义一个脑波数据对象，包含了接收成功标志位、专注度、放松度的值 等


/* 12/09 11:17 加入按键中断 */
const uint8_t KEY_MODE = 2;
typedef enum{ MEDITATION=0, ATTENTION,  TURN_OFF }MODE_t;
//typedef enum{ TURN_ON = 0, TURN_OFF }MODE_t;
MODE_t chooseOneMode = MEDITATION;

/*** 大灯专有属性，按键切换模式，进入关闭状态（睡眠） ***/
typedef enum{ SLEEP = 0, WORK }sw_t;
sw_t Sleep_or_Work = WORK;                 // 定义初始状态在工作状态

#if 1
  SoftwareSerial mySerial =  SoftwareSerial(8, 7);
  void SoftwareSerial_init( void ){
    pinMode( 8, INPUT );
    pinMode( 7, OUTPUT );
    mySerial.begin(57600);                            // 与蓝牙模块连接的波特率
 }
#endif


/*================= 蓝牙模块相关 ==================================*/
 /*** 定义蓝牙引脚控制对象 ***/
 typedef struct {
  uint8_t EN_pin;
  uint8_t STA_pin;
  uint8_t KEY_pin;
  uint8_t RXD_pin;
  uint8_t TXD_pin;
 }BLE_MCUpin_t;
 void BLE_MCUpin_init( BLE_MCUpin_t *_pin_t){
  pinMode( _pin_t->EN_pin; OUTPUT );  digitalWrite ( _pin_t->EN_pin, HIGH );        // ldo工作，模块使能
  pinMode( _pin_t->STA_pin; INPUT );  //digitalWrite ( _pin_t->STA_pin, HIGH );
  pinMode( _pin_t->KEY_pin; OUTPUT ); digitalWrite ( _pin_t->KEY_pin, HIGH );       // KEY拉高，配对模式；拉低，AT模式
  //pinMode( _pin_t->RXD_pin; INPUT );              //  MCU   rxd|<= ------- <=| TXD   HC-05
  //pinMode( _pin_t->TXD_pin; OUTPUT );             //        txd|=> ------- =>| RXD
 }

#if 0
 typedef struct {
  uint8_t name[20];
  uint8_t pswd[10];
  uint8_t role;
  uint8_t baud[10];
 } BLE_data_t
#endif /* 0 or 1 */
/*===============end 蓝牙模块相关 ===================================*/

/*** 定义蓝牙模块在本实例电路中连接的引脚 ***/
BLE_MCUpin_t mwLight_BLEpin;      // 在定义一个struct 对象时，如何初始化？
void constructePin( BLE_MCUpin_t *_mwLight_BLEpin ){
  // 面向过程的函数，实例化，在初始化时调用
  _mwLight_BLEpin->EN_pin = 4;
  _mwLight_BLEpin->STA_pin = 5;
  _mwLight_BLEpin->RXD_pin = 8;
  _mwLight_BLEpin->TXD_pin = 7;  
}
// constructePin( mwLight_BLEpin );       // 调用本句在初始化函数段中



void setup(){
	SoftwareSerial_init();                          // 与蓝牙连接的IO口-> 模拟串口初始化
  constructePin( &mwLight_BLEpin )                // 在函数中构造蓝牙模块各个控制引脚
  BLE_MCUpin_init( &mwLight_BLEpin );            // 蓝牙模块的各个控制引脚（状态）初始化--> 对象以MCU为标准命名
  RGB_light_init();                              // 脑波灯（RGB三色灯） 控制引脚初始化
  DEBUG_LED_init();                              // 调试指示灯控制引脚初始化
  pinMode( TEST_LED, OUTPUT );    digitalWrite ( TEST_LED, LOW );
	structureMindwaveData( &mindwaveLight );			// 初始化对象数据
  
  #ifdef DEBUG
    Serial.begin( 9600 );
    setLightColor( RED );
    delay_ms(1500);
    setLightColor( FOOCOLOR );
  #endif /* DEBUG */

  // add KEY_MODE
  pinMode( KEY_MODE, INPUT_PULLUP );
  attachInterrupt( digitalPinToInterrupt( KEY_MODE ), chooseMode, FALLING);
}



color_t lightColor = FOOCOLOR;
uint8_t Rx_data;
/***************************   loop()   *************************/
void loop(){	
  
  if( digitalRead( BLE_STA ) == HIGH ){ // 高电平，配对连接上！
    digitalWrite ( connect_OK, LOW );
  }//else setLightColor ( FOOCOLOR );
  else  digitalWrite ( connect_OK, HIGH );

    if ( mySerial.available()>0 ){
        digitalWrite( 11, HIGH );
        Rx_data = mySerial.read();
        getMindwaveData( &mindwaveLight, Rx_data );  
    }
    //else digitalWrite( 11, LOW );


  if ( Sleep_or_Work == WORK ){
      digitalWrite ( BLE_EN, HIGH );
     //getMindwaveData( &mindwaveLight, &mySerial );
     if ( mindwaveLight.GotData == PASS ){
            mindwaveLight.GotData = FAIL;
            if ( chooseOneMode == MEDITATION )    lightColor = getSuitLightColor( mindwaveLight.meditation );  
            if ( chooseOneMode == ATTENTION )     lightColor = getSuitLightColor( mindwaveLight.attention );          
            setLightColor( lightColor );
     }else testLED_blink();
  } // end if WORK


  if ( Sleep_or_Work == SLEEP ){
    digitalWrite ( BLE_EN, LOW );
    if( chooseOneMode == TURN_OFF ){
      // digitalWrite( 11, HIGH );
      lightColor = FOOCOLOR;
      setLightColor( FOOCOLOR );
    }
  } // end if SLEEP
} // end LOOP

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
  delay_ms( 10 );
  if ( digitalRead(KEY_MODE) == LOW ){

      switch ( lastMode ){
      case MEDITATION:
                    Sleep_or_Work = WORK;  
                    chooseOneMode = ATTENTION; 
                    lastMode = ATTENTION;
                    break;
      case ATTENTION: 
                    Sleep_or_Work = SLEEP; 
                    chooseOneMode = TURN_OFF; 
                    lastMode = TURN_OFF;
                    break;

      case TURN_OFF: 
                    Sleep_or_Work = WORK; 
                    chooseOneMode = MEDITATION; 
                    lastMode = MEDITATION;
                    break;        
      }// end switch lastMode

  }// end if KEY_MODE = LOW

}// end func chooseMode




