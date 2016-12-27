
#ifndef BLE_H
#define BLE_H

 #include "Arduino.h"
// #include <portable.h>
// #include <hardwareDrive.h>
 #include "portable.h"
 #include "hardwareDrive.h"



/*================= 蓝牙模块相关 ==================================*/
 /*** 定义蓝牙引脚控制对象 ***/
typedef struct BLE_module{
    unsigned int EN_PIN;
    unsigned int STA_PIN;
    unsigned int KEY_PIN;

    //unsigned int RX_PIN;
    //unsigned int TX_PIN;
} BLE_module_t;
void BLE_PIN_config( BLE_module_t *_pin);
void BLE_PIN_INIT( BLE_module_t *_BLE_PIN);

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
