/*
 * 
 */
#ifndef PORTABLE_H
#define PORTABLE_H

// #define Arduino

 /* 之后把这一部分放到同一个文件protable.h 下 */
// typedef char    int8_t;
// //typedef short   int16_t;
// typedef int     int16_t;
// typedef long    int32_t;
// typedef unsigned char   uint8_t;
// //typedef unsigned short  uint16_t;
// typedef unsigned int    uint16_t;
// typedef unsigned long   uint32_t; 

 typedef enum{ B_FALSE = 0, B_TRUE = 1 }boolean_t;
 typedef enum{ PASS = 0, FAIL = 1 }pf_t;
 //typedef enum{ PASSED = 0, FAILED = 1 }pf_t; 

 typedef enum{ B_LOW = 0, B_HIGH = 1 }B_level_t;

// #ifdef Arduino
 typedef enum{ INPUT_mulpx, INPUT_PULLUP_mulpx, OUTPUT_mulpx }gpioMode_t;
// #endif /* Arduino */

#endif /* PORTABLE_H */

