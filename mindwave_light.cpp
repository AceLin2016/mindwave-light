/* mindwave_light.cpp
 *
*/

 #include "mindwave_light.h"
 #include <string.h>                // memset() 头文件
 #include <portable.h>
 #include "Arduino.h"
 #include <SoftwareSerial.h>

//  volatile unsigned char protocolData[data_length] = {0};
//  volatile uint16_t N_index = 0;

void structureMindwaveData( mwData_t* _mwLight ){
	_mwLight->_signal = 0;
	_mwLight->attention = 0;
	_mwLight->meditation = 0;
	_mwLight->GotData = FAIL;
    _mwLight->N_index = 0;
     _mwLight->BLE_data = 0;
    memset( _mwLight->protocolData, 0, sizeof(char)*data_length );
}

void cleanProtocol(uint8_t array[], uint16_t length ){ /* 本函数不完整，只能够正常清除char类型指针 */
     memset(array, 0, sizeof(char)*length);
}


 


void getMindwaveData( mwData_t* _mwLight, uint8_t _BLE_data ){
     _mwLight->BLE_data = _BLE_data;      
//    digitalWrite( 11, HIGH );

    _mwLight->protocolData[ _mwLight->N_index ] = _mwLight->BLE_data;     // 将数值放到数字中
    if( (_mwLight->N_index==0)&&(_mwLight->protocolData[0]== SYN) ) _mwLight->N_index++;
     else if( (_mwLight->N_index==1) && (_mwLight->protocolData[1])==SYN ) _mwLight->N_index++;
     else if( (_mwLight->N_index==2) && (_mwLight->protocolData[2])==PAL ) _mwLight->N_index++;
     else if( (_mwLight->N_index==3) && (_mwLight->protocolData[3])==SIG ) _mwLight->N_index++;
     else if( (_mwLight->N_index==4) )   _mwLight->N_index++;
     else if( (_mwLight->N_index==5) && (_mwLight->protocolData[5])==EEG ) _mwLight->N_index++;
     else if( (_mwLight->N_index==6) && (_mwLight->protocolData[6])==LEN ) _mwLight->N_index++;
     else if( (_mwLight->N_index>6) && (_mwLight->N_index<35) ) _mwLight->N_index++;
     else if( _mwLight->N_index==35 ){
      _mwLight->_signal    =  _mwLight->protocolData[4];
      _mwLight->attention  =  _mwLight->protocolData[32];
      _mwLight->meditation =  _mwLight->protocolData[34];
      _mwLight->N_index =0;
      //cleanProtocol( _mwLight->protocolData, data_length );
            memset( _mwLight->protocolData, 0, sizeof(char)*data_length );
      _mwLight->GotData = PASS;
            //t=0;
     }else{
      _mwLight->N_index = 0;
      //cleanProtocol();
            memset( _mwLight->protocolData, 0, sizeof(char)*data_length );
    }
    //else  digitalWrite( 11, LOW );
} // end func



#if 0
void getMindwaveData( mwData_t* _mwLight, SoftwareSerial *_mySerial ){
  //static byte t=0;
	// if (Serial.available() > 0){
	// 	//Serial.readBytes( &(_mwLight->BLE_data), 1 );           // 读取数值
   	// _mwLight->BLE_data = Serial.read();  
	if ( _mySerial->available() > 0 ){
   		_mwLight->BLE_data = _mySerial->read();       
		digitalWrite( 11, HIGH );

		_mwLight->protocolData[ _mwLight->N_index ] = _mwLight->BLE_data;			// 将数值放到数字中
		if( (_mwLight->N_index==0)&&(_mwLight->protocolData[0]== SYN) ) _mwLight->N_index++;
		 else if( (_mwLight->N_index==1) && (_mwLight->protocolData[1])==SYN ) _mwLight->N_index++;
		 else if( (_mwLight->N_index==2) && (_mwLight->protocolData[2])==PAL ) _mwLight->N_index++;
		 else if( (_mwLight->N_index==3) && (_mwLight->protocolData[3])==SIG ) _mwLight->N_index++;
		 else if( (_mwLight->N_index==4) )	 _mwLight->N_index++;
		 else if( (_mwLight->N_index==5) && (_mwLight->protocolData[5])==EEG ) _mwLight->N_index++;
		 else if( (_mwLight->N_index==6) && (_mwLight->protocolData[6])==LEN ) _mwLight->N_index++;
		 else if( (_mwLight->N_index>6) && (_mwLight->N_index<35) ) _mwLight->N_index++;
		 else if( _mwLight->N_index==35 ){
			_mwLight->_signal    =  _mwLight->protocolData[4];
			_mwLight->attention  =  _mwLight->protocolData[32];
			_mwLight->meditation =  _mwLight->protocolData[34];
			_mwLight->N_index =0;
			//cleanProtocol( _mwLight->protocolData, data_length );
            memset( _mwLight->protocolData, 0, sizeof(char)*data_length );
			_mwLight->GotData = PASS;
            //t=0;
		 }else{
			_mwLight->N_index = 0;
			//cleanProtocol();
            memset( _mwLight->protocolData, 0, sizeof(char)*data_length );
		}
	} // end if mySerial.available()
  	else	digitalWrite( 11, LOW );
} // end func

#endif


