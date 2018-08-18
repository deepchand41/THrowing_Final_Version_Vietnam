/* 
* GenevaEncoder.cpp
*
* Created: 5/31/2018 5:16:56 AM
* Author: Deepak Chand
*/


#include "GenevaEncoder.h"
#include <avr/io.h>
#include <avr/interrupt.h>




GenevaEncoder::GenevaEncoder()
{
	Encoder_Count = 0;
	Initialize_Geneva_Encoder();
} //GenevaEncoder

void GenevaEncoder::Initialize_Geneva_Encoder()
{
	//PIn configuration
	INPUT(ENCODERA);
	INPUT(ENCODERB);
	PULLUP_ON(ENCODERA);
	PULLUP_ON(ENCODERB);	
	
	REGISTER_SET1(ENCODER_EICR,ENCODER_ISC1);    //Falling Edge
	REGISTER_SET1(EIMSK,ENCODER_INT);
	REGISTER_SET1(EIFR,ENCODER_INTF);
}

void GenevaEncoder::Encoder_Increase_Pulse_counter()
{
	if (READ(ENCODERB))
	{
		Inc_Count();
	}
	else if (!(READ(ENCODERB)))
	{
		Dcr_Count();
	}
}

int GenevaEncoder::Enoder_Get_Angle()
{
	Geneva_Angle = (float(Encoder_Count)/PPR)*360;
	return Geneva_Angle;
}

