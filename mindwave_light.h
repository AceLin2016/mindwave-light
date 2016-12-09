
/* mindwave_light.h
 * 
 */
#ifndef MINDWAVE_LIGHT_H
#define MINDWAVE_LIGHT_H

#include "Arduino.h"
#include <portable.h>

#define SYN  0xAA
#define PAL  0x20    /* 代表32个字节的payload, */
#define SIG  0x02
#define EEG  0x83
#define LEN  0x18    /* 十进制的24， EEG Power由24字节组成 */
#define ATT  0x04
#define MED  0x05

//typedef unsigned char uint8_t;

 typedef struct mindwaveData {
 		uint8_t _signal;
 		uint8_t attention;
 		uint8_t meditation;
 		pf_t GotData;
    volatile uint8_t BLE_data;
    volatile uint8_t protocolData[36];
    volatile uint16_t N_index;
 }mwData_t;


 void structureMindwaveData( mwData_t* _mwLight );
 void cleanProtocol(uint8_t array[], uint16_t length );
 void getMindwaveData( mwData_t* _mwLight );




#endif /* MINDWAVE_LIGHT_H */
