
#ifndef BLE_H
#define BLE_H

 #include "Arduino.h"
 #include <portable.h>
 #include <hardwareDrive.h>



/*================= 蓝牙模块相关 ==================================*/
 /*** 定义蓝牙引脚控制对象 ***/
 typedef struct BLE_MCUpin_t {
  uint8_t EN_pin;
  uint8_t STA_pin;
  uint8_t KEY_pin;
  uint8_t RXD_pin;
  uint8_t TXD_pin;
 }BLE_MCUpin_t;

  void constructePin( BLE_MCUpin_t *_mwLight_BLEpin );
 // constructePin( mwLight_BLEpin );       // 调用本句在初始化函数段中

 void BLE_MCUpin_init( BLE_MCUpin_t *_pin_t);

#if 0
 typedef struct {
  uint8_t name[20];
  uint8_t pswd[10];
  uint8_t role;
  uint8_t baud[10];
 } BLE_data_t
#endif /* 0 or 1 */
/*===============end 蓝牙模块相关 ===================================*/


#endif /* BLE_H */
