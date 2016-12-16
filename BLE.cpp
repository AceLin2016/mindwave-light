
 #include "BLE.h"
 #include "Arduino.h"
 #include <portable.h>
 #include <hardwareDrive.h>

/*---------------- BLE.c ---------------------------------------*/
void BLE_PIN_config( BLE_module_t *_pin){
  _pin->EN_PIN = 4;
  _pin->STA_PIN = 5;
  _pin->KEY_PIN = 6;
}

void BLE_PIN_INIT( BLE_module_t *_BLE_PIN){
    pinMode( _BLE_PIN->EN_PIN, OUTPUT );
    pinMode( _BLE_PIN->STA_PIN, INPUT );            // 看是否需要放一个下拉电阻
    pinMode( _BLE_PIN->KEY_PIN, OUTPUT );

    digitalWrite( _BLE_PIN->EN_PIN, HIGH );         // 低电平断电
    digitalWrite( _BLE_PIN->KEY_PIN, LOW );         // 拉高进入AT模式

}
/*---------------- end BLE.c ---------------------------------------*/

