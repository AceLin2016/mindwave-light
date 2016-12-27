
/* mindwave_light.h
 * 
 */
#ifndef MINDWAVE_LIGHT_H
#define MINDWAVE_LIGHT_H

#include "Arduino.h"
// #include <portable.h>
#include "portable.h"
#include <SoftwareSerial.h>

#define SYN  0xAA
#define PAL  0x20    /* 代表32个字节的payload, */
#define SIG  0x02
#define EEG  0x83
#define LEN  0x18    /* 十进制的24， EEG Power由24字节组成 */
#define ATT  0x04
#define MED  0x05

#define data_length 37

 typedef struct mindwaveData {
 		uint8_t _signal;
 		uint8_t attention;
 		uint8_t meditation;
 		pf_t GotData;
    volatile uint8_t BLE_data;
    volatile uint8_t protocolData[data_length];
    volatile uint16_t N_index;
 }mwData_t;

/* 11-19-09:38  使用模拟串口更新版本
 * 引入头文件 SoftWareSerial.h 
 * 定义rxPin 和 txPin 引脚号 */
#if 1
 #define rxPin 8
 #define txPin 7
 
  //void SoftwareSerial_init( void );
#endif /* 0 or 1 */


// void structureMindwaveData( mwData_t* _mwLight );
void structureMindwaveData();
// void cleanProtocol(uint8_t array[], uint16_t _length );
void cleanProtocol( );
// void getMindwaveData( mwData_t* _mwLight, SoftwareSerial *_mySerial );
//void getMindwaveData( mwData_t* _mwLight, uint8_t _BLE_data );
void getMindwaveData(uint8_t _BLE_data );


void set_Got_data(pf_t PASS_or_FAIL);
pf_t ifSuccess_got_data();
uint8_t getAttention();
uint8_t getMeditation();

#endif /* MINDWAVE_LIGHT_H */
