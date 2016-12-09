/* mindwave_light.cpp
 *
*/

 #include "mindwave_light.h"
 #include <string.h>                // memset() 头文件
 #include <portable.h>
 #include "Arduino.h"

//  volatile unsigned char protocolData[36] = {0};
//  volatile uint16_t N_index = 0;

void structureMindwaveData( mwData_t* _mwLight ){
	_mwLight->_signal = 0;
	_mwLight->attention = 0;
	_mwLight->meditation = 0;
	_mwLight->GotData = FAIL;
    _mwLight->N_index = 0;
     _mwLight->BLE_data = 0;
    memset( _mwLight->protocolData, 0, sizeof(char)*36 );
}

void cleanProtocol(uint8_t array[], uint16_t length ){ /* 本函数不完整，只能够正常清除char类型指针 */
     memset(array, 0, sizeof(char)*length);
}


void getMindwaveData( mwData_t* _mwLight ){
  //static byte t=0;
	if (Serial.available() > 0){
		//Serial.readBytes( &(_mwLight->BLE_data), 1 );           // 读取数值
   _mwLight->BLE_data = Serial.read();        
      #if 1
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
   #if 0
    if( (N_index==1)&&(protocolData[1])==0xAA ){    N_index++; t=1; }
    if( (N_index==2)&&(protocolData[2])==0x20 ){    N_index++; t=1; }
    if( (N_index==3)&&(protocolData[3])==0x02 ){    N_index++; t=1; }
    if( (N_index==4) ){    N_index++; t=1; }
    if( (N_index==5)&&(protocolData[5])==0x83 ){    N_index++; t=1; }
    if( (N_index==6)&&(protocolData[6])==0x18 ){    N_index++; t=1; }
    if( (N_index>6)&&(N_index<35) ){    N_index++; t=1; }
    if(t==0){     N_index = 0;   cleanProtocol();   }
    if( N_index==35 ){
   #endif
			_mwLight->_signal    =  _mwLight->protocolData[4];
			_mwLight->attention  =  _mwLight->protocolData[32];
			_mwLight->meditation =  _mwLight->protocolData[34];
			_mwLight->N_index =0;
			//cleanProtocol( _mwLight->protocolData, 36 );
            memset( _mwLight->protocolData, 0, sizeof(char)*36 );
			_mwLight->GotData = PASS;
            //t=0;
		 }else{
			_mwLight->N_index = 0;
			//cleanProtocol();
            memset( _mwLight->protocolData, 0, sizeof(char)*36 );
		}
        //if(t==0){     N_index = 0;   cleanProtocol();   }
     #endif /* 0 or 1 */
	} // end if mySerial.available()
  //else{ digitalWrite ( TEST_LED, LOW ); }
} // end func
