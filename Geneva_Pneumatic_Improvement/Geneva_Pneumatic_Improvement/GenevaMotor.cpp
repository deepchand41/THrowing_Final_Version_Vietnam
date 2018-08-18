/* 
* GenevaMotor.cpp
*
* Created: 5/31/2018 4:19:01 AM
* Author: Deepak Chand
*/


#include "GenevaMotor.h"

void GenevaMotor::Initialize_Geneva_Motor()
{
	InitPWM();
	StopMotor();
	SetOcrValue(0);
}

void GenevaMotor::InitPWM()
{
	OUTPUT(DD_F_G);
	OUTPUT(DD_B_G);
	
	OUTPUT(DD_PWM_G);
	 
	PWM_TCCRA_G |= (1 << PWM_G_COM1)| (1 << PWM_G_WGM1);                                   //Fast PWM
	
	
	PWM_TCCRB_G |= (1 << PWM_G_WGM2) | (1 << PWM_G_WGM3) | (1 << PWM_G_CS1);
	PWM_ICR_G    = ICR_TOP;
}

void GenevaMotor::SetForwardDirection()
{
	SET(DD_F_G);
	CLEAR(DD_B_G);
}

void GenevaMotor::SetReverseDirection()
{
	CLEAR(DD_F_G);
	SET(DD_B_G);
}

void GenevaMotor::StopMotor()
{
	SET(DD_F_G);
	SET(DD_B_G);
	
	PWM_OCR_G = 0;
}

void GenevaMotor::SetOcrValue(int ocr)
{
	if (ocr > 0)
		SetForwardDirection();
	if(ocr >= MAX_VALUE)
		ocr = MAX_VALUE;
		
	if (ocr < 0)
	{
		ocr = -ocr;
		SetReverseDirection();
	}
	
	PWM_OCR_G = ocr;
}