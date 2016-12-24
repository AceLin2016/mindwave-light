

//#include "Interrupt.h"
#include "colorLED.h"

/*
* LedBrightness sketch 
* controls the brightness of LEDs on analog output ports */ 
const int RedLed = 3;
const int GreenLed = 5; 
const int BlueLed = 6;

//const uint16_t modeKEY_pin = 2;
uint16_t modeKEY_pin = 2;

int brightness = 0; 
int increment = 1;



 
void setup() {
    // pins driven by analogWrite do not need to be declared as outputs 

    pinMode(modeKEY_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(modeKEY_pin), modeISR, FALLING);

}


colorLED_list_t witchLED_work = RED;
//extern colorLED_list_t witchLED_work;
void loop() {
    if(brightness > 254) {
        delay( 1000 );
        increment = -1;                 // count down after reaching 254 // not be 255 
    }
    else if(brightness < 2) {
        
        increment = 1;                  // count up after dropping back down to 0
    } 
    brightness = brightness + increment; // increment (or decrement sign is minus)
    // write the brightness value to the LEDs 
    switch( witchLED_work ){
        case RED:   
                analogWrite(RedLed, brightness);
                analogWrite(GreenLed, 255);
                analogWrite(BlueLed, 255);
                break;
        case WHITE: 
                analogWrite(GreenLed, brightness);
                analogWrite(RedLed, 255);
                analogWrite(BlueLed, 255);
                break;
        case BLUE:  
                analogWrite(BlueLed, brightness);
                analogWrite(GreenLed, 255);
                analogWrite(RedLed, 255);
                break;
        default:    break;
    } // end switch witchLED_work
    delay(brightness/10);
    //delay(10);
} // end loop function



/*__ special func --> KEY ISR  //  out of class ___*/
void modeISR(void){
    delay(10);                  // 消抖  // 换成delay_ms();
    if( digitalRead(2) == LOW ){
        switch( witchLED_work ){
            case RED:   witchLED_work = WHITE;  break;
            case WHITE: witchLED_work = BLUE;   break;
            case BLUE:  witchLED_work = RED;    break;
            default:    break;
        } // end switch witchLED_work
    } // end if pin_2 = LOW
} // end func modeISR
