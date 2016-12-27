
/*
 * 
 */

 
//  #include "setColorFromData.h"

  #include "Arduino.h"
 #include "portable.h"
 #include "hardwareDrive.h"
 #include "ctrlColor.h"
 #include "setColorFromData.h"
 
//  #include "portable\portable.h"
//  #include "ctrlColor\ctrlColor.h"
//  #include "setColorFromData\setColorFromData.h"
//  #include "hardwareDrive\hardwareDrive.h"

//  #include <portable.h>
//  #include <ctrlColor.h>
//  #include <setColorFromData.h>
//  #include <hardwareDrive.h>

 color_t getSuitLightColor( const uint8_t _mindwave ){
 		if( (_mindwave>0x00)&&(_mindwave<=0x14) ) return RED;
 		if( (_mindwave>0x14)&&(_mindwave<=0x1E) ) return ORANGE;
 		if( (_mindwave>0x1E)&&(_mindwave<=0x28) ) return YELLOW;
 		if( (_mindwave>0x28)&&(_mindwave<=0x3C) ) return GREEN;
 		if( (_mindwave>0x3C)&&(_mindwave<=0x46) ) return BLUE;
 		if( (_mindwave>0x46)&&(_mindwave<=0x50) ) return CYAN;
 		if( (_mindwave>0x50)&&(_mindwave<=0x64) ) return PURPLE;
 }







