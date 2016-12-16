/* mindwave_light.cpp
 *
*/

 #include "mindwave_light.h"
 #include <string.h>                // memset() 头文件
 #include <portable.h>
 #include "Arduino.h"
 //#include <SoftwareSerial.h>

 #include "debug.h"
// #include "BLE.h"


mwData_t g_mindwaveLight;                 // 定义一个脑波数据对象，包含了接收成功标志位、专注度、放松度的值 等




static void forceFlush(){
    while( Serial.available()>0 ){
      Serial.read();
    } // end while available
}

void structureMindwaveData(){
	g_mindwaveLight._signal = 0;
	g_mindwaveLight.attention = 0;
	g_mindwaveLight.meditation = 0;
	g_mindwaveLight.GotData = FAIL;			// enum{ PASS = 0, FAIL = 1 }pf_t; in portable.h
    g_mindwaveLight.N_index = 0;
     g_mindwaveLight.BLE_data = 0;
    cleanProtocol();
}

void set_Got_data(pf_t PASS_or_FAIL){
	g_mindwaveLight.GotData = PASS_or_FAIL;
}
pf_t ifSuccess_got_data(){
	return g_mindwaveLight.GotData;
}


uint8_t getMeditation(){
	return g_mindwaveLight.meditation;
}
uint8_t getAttention(){
	return g_mindwaveLight.attention;
}


void getMindwaveData( uint8_t _BLE_data ){
     g_mindwaveLight.BLE_data = _BLE_data;      

    g_mindwaveLight.protocolData[ g_mindwaveLight.N_index ] = g_mindwaveLight.BLE_data;     // 将数值放到数字中
    if( (g_mindwaveLight.N_index==0)&&(g_mindwaveLight.protocolData[0]== SYN) ) { g_mindwaveLight.N_index++; SYN_ON(); }
     else if( (g_mindwaveLight.N_index==1) && (g_mindwaveLight.protocolData[1])==SYN ) g_mindwaveLight.N_index++;
     else if( (g_mindwaveLight.N_index==2) && (g_mindwaveLight.protocolData[2])==PAL ) g_mindwaveLight.N_index++;
     else if( (g_mindwaveLight.N_index==3) && (g_mindwaveLight.protocolData[3])==SIG ) g_mindwaveLight.N_index++;
     else if( (g_mindwaveLight.N_index==4) )   g_mindwaveLight.N_index++;
     else if( (g_mindwaveLight.N_index==5) && (g_mindwaveLight.protocolData[5])==EEG ) g_mindwaveLight.N_index++;
     else if( (g_mindwaveLight.N_index==6) && (g_mindwaveLight.protocolData[6])==LEN ) g_mindwaveLight.N_index++;
     else if( (g_mindwaveLight.N_index>6) && (g_mindwaveLight.N_index<35) ) { g_mindwaveLight.N_index++; SYN_OFF(); }
     else if( g_mindwaveLight.N_index==35 ){
		 forceFlush();
        g_mindwaveLight._signal    =  g_mindwaveLight.protocolData[4];
        g_mindwaveLight.attention  =  g_mindwaveLight.protocolData[32];
        g_mindwaveLight.meditation =  g_mindwaveLight.protocolData[34];
        g_mindwaveLight.N_index =0;
		forceFlush();
        //memset( g_mindwaveLight.protocolData, 0, sizeof(char)*data_length );
		    cleanProtocol();
        //g_mindwaveLight.GotData = PASS;
		    set_Got_data(PASS);

        SYN_OFF();
		forceFlush();
     }else{
		 forceFlush();
        g_mindwaveLight.N_index = 0;
        //memset( g_mindwaveLight.protocolData, 0, sizeof(char)*data_length );
		    cleanProtocol();
        SYN_OFF();
		forceFlush();
    }
} // end func


void cleanProtocol( ){ 
	 uint16_t i = 0;
	 for( i=0; i<data_length; i++)
	 	g_mindwaveLight.protocolData[i]=0;
}




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


