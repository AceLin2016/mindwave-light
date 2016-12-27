/* 2016/12/01 23:40
 * 外设驱动层，
 * 针对蓝牙，提供API接口
 */
 #ifndef HARDWAREDRIVE_H
 #define HARDWAREDRIVE_H

 
  #include "Arduino.h"
  #include "portable.h"

// #include <portable.h>
 //#include <hardwareDrive.h>

void delay_ms(uint16_t _ms);
void setGPIO_mode( uint16_t _pin, gpioMode_t _mode );
void setGPIO_level( uint16_t _pin, B_level_t _level );


 
 
 /************* UART Drive ************************************/
/* TX,RX 已经被构造类，在未彻底搞清楚前，还是先不动它，
 * 应该是在调用这两个函数之前，有一个初始化过程，
 * 就像Serial.begin(uint16_t baud); 一样 */
 //void tx_data( uint8_t _data );
//  void tx_data( uint8_t _data ){

//  }


 //uint8_t rx_data( void );

 #endif /* HARDWAREDRIVE_H */

