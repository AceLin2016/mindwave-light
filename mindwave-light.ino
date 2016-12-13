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
  const uint8_t TEST_LED=13;
  void testLED_blink( void );
  const uint8_t DEBUG_LED = 12;
 #endif /* DEBUG */

/******* main ************************/

//extern SoftwareSerial mySerial;

 // bluetooth  相关
 const uint8_t BLE_STA = 5;
 const uint8_t BLE_EN = 4;

/* 指示灯相关定义 */
 const uint8_t getSYN = 12;
 const uint8_t getBLE_data = 11;
 const uint8_t connect_OK = 10;

 void indicatorLED_init( void ){
    pinMode( getSYN, OUTPUT );    digitalWrite ( getSYN, HIGH );               /* vcc|-----|\/\/\----|>|------|=> D12 */ 
    pinMode( getBLE_data, OUTPUT );    digitalWrite ( getBLE_data, LOW );
    pinMode( connect_OK, OUTPUT );    digitalWrite ( connect_OK, HIGH );      /* vcc|-----|\/\/\----|>|------|=> D10 */ 
 }

 // 脑波灯需要对象、标志位等相关...
 //const uint8_t interruptPin = 2;

 mwData_t mindwaveLight;


/* 12/09 11:17 加入按键中断 */
const uint8_t KEY_MODE = 2;
typedef enum{ MEDITATION=0, ATTENTION,  TURN_OFF }MODE_t;
//typedef enum{ TURN_ON = 0, TURN_OFF }MODE_t;
MODE_t chooseOneMode = MEDITATION;

typedef enum{ SLEEP = 0, WORK }sw_t;
sw_t Sleep_or_Work = WORK;

#if 1
  SoftwareSerial mySerial =  SoftwareSerial(8, 7);
  void SoftwareSerial_init( void ){
    pinMode( 8, INPUT );
    pinMode( 7, OUTPUT );
    mySerial.begin(57600);                            // 与蓝牙模块连接的波特率
 }
#endif

void BLE_INIT(){
     pinMode( BLE_STA, INPUT );
     pinMode( BLE_EN, OUTPUT );
     digitalWrite ( BLE_EN, HIGH );
}


void setup(){
	SoftwareSerial_init();
  BLE_INIT();
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




