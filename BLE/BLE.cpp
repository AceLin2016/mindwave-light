
 #include "BLE.h"
 #include "Arduino.h"
 #include <portable.h>
 #include <hardwareDrive.h>

  void constructePin( BLE_MCUpin_t *_mwLight_BLEpin ){
    // 面向过程的函数，实例化，在初始化时调用
    _mwLight_BLEpin->EN_pin = 4;
    _mwLight_BLEpin->STA_pin = 5;
    _mwLight_BLEpin->RXD_pin = 8;
    _mwLight_BLEpin->TXD_pin = 7;  
 }
 // constructePin( mwLight_BLEpin );       // 调用本句在初始化函数段中

 void BLE_MCUpin_init( BLE_MCUpin_t *_pin){
  setGPIO_mode( _pin->EN_pin, OUTPUT );
  setGPIO_level ( _pin->EN_pin, HIGH );        // ldo工作，模块使能
  
  setGPIO_mode( _pin->STA_pin, INPUT );  //setGPIO_level ( _pin_t->STA_pin, HIGH );
  
  setGPIO_mode( _pin->KEY_pin, OUTPUT );
  setGPIO_level ( _pin->KEY_pin, HIGH );       // KEY拉高，配对模式；拉低，AT模式
  //setGPIO_mode( _pin_t->RXD_pin; INPUT );              //  MCU   rxd|<= ------- <=| TXD   HC-05
  //setGPIO_mode( _pin_t->TXD_pin; OUTPUT );             //        txd|=> ------- =>| RXD
 }

