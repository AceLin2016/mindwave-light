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

 #ifdef DEBUG
  const byte TEST_LED=13;
  void testLED_blink( void );
  const byte DEBUG_LED = 12;
 #endif /* DEBUG */

/******* main ************************/
/* 11-19-09:38  使用模拟串口更新版本
 * 引入头文件 SoftWareSerial.h 
 * 定义rxPin 和 txPin 引脚号 */
#if 0
 #define rxPin 8
 #define txPin 7
 SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
 void SoftwareSerial_init(void){
	  // setup UART and baud = 57600 as usual
 	  // Serial.begin( 57600 );
    pinMode( rxPin, INPUT );
    pinMode( txPin, OUTPUT );
    mySerial.begin(9600);
 }
#endif /* 0 or 1 */


 // bluetooth  相关
 const byte BLE_STA = 5;

/* 指示灯相关定义 */
 const byte getSYN = 12;
 const byte getBLE_data = 11;
 const byte connect_OK = 10;

 void indicatorLED_init( void ){
    pinMode( getSYN, OUTPUT );    digitalWrite ( getSYN, HIGH );               /* vcc|-----|\/\/\----|>|------|=> D12 */ 
    pinMode( getBLE_data, OUTPUT );    digitalWrite ( getBLE_data, LOW );
    pinMode( connect_OK, OUTPUT );    digitalWrite ( connect_OK, HIGH );      /* vcc|-----|\/\/\----|>|------|=> D10 */ 
 }

 // 脑波灯需要对象、标志位等相关...
 //const byte interruptPin = 2;

 mwData_t mindwaveLight;


/* 12/09 11:17 加入按键中断 */
const byte KEY_MODE = 2;
typedef enum{ MEDITATION=0, ATTENTION,  TURN_OFF }MODE_t;
//typedef enum{ TURN_ON = 0, TURN_OFF }MODE_t;
MODE_t chooseOneMode = MEDITATION;

typedef enum{ SLEEP = 0, WORK }sw_t;
sw_t Sleep_or_Work = WORK;

void setup(){
	//SoftwareSerial_init();
  pinMode( BLE_STA, INPUT );
  RGB_light_init();  
  indicatorLED_init();
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
/***************************   loop()   *************************/
void loop(){	

  if( digitalRead( BLE_STA ) == HIGH ){ // 高电平，配对连接上！
    digitalWrite ( connect_OK, LOW );
  }//else setLightColor ( FOOCOLOR );
  else  digitalWrite ( connect_OK, HIGH );

  if ( Sleep_or_Work == WORK ){
     //setLightColor( BLUE );
     getMindwaveData( &mindwaveLight );
     if ( mindwaveLight.GotData == PASS ){
            mindwaveLight.GotData = FAIL;
            if ( chooseOneMode == MEDITATION )    lightColor = getSuitLightColor( mindwaveLight.meditation );  
            if ( chooseOneMode == ATTENTION )     lightColor = getSuitLightColor( mindwaveLight.attention );          
            setLightColor( lightColor );
     }else testLED_blink();
  }
  if ( Sleep_or_Work == SLEEP ){
    if( chooseOneMode == TURN_OFF ){
      setLightColor( FOOCOLOR );
    }
  }
}

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
      }// end switch

  }// end if 

}// end func 




