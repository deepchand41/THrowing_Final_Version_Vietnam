#include "Motor.h"



void Motor::Initialise()
{
	InitPWM();

	StopMotor();
	SetOcrValue(0);

}

void Motor::InitPWM()
{
		OUTPUT(DD_F1);
		OUTPUT(DD_B1);

		OUTPUT(DD_PWM1);

		PWM_TCCRA1	|=  ( 1 << PWM_1COM1 ) | ( 1 << PWM_1WGM1 );												    // Clear on Compare Match
		PWM_TCCRB1	|=  ( 1 << PWM_1WGM2 ) | ( 1 << PWM_1WGM3 ) | ( 1 << PWM_1CS1);									//PRESCALAR 8
		PWM_ICR1		 =         ICR_TOP;
}

void Motor::SetForwardDirection()
{
	SET (DD_F1);
	CLEAR	(DD_B1);
}
void Motor::SetReverseDirection()
{
	CLEAR	(DD_F1);
	SET (DD_B1);
}

void Motor::StopMotor()
{
	SET	(DD_F1);
	SET	(DD_B1);

	PWM_OCR1 = 0;	
}


void Motor::SetOcrValue(int Ocr)
{
    if (Ocr > 0)
		//SetReverseDirection();
		SetForwardDirection();
	if( Ocr >= MAX_VALUE)
		Ocr = MAX_VALUE;
		
	if(Ocr < 0)
	 {
		Ocr = -Ocr;
		//SetForwardDirection();
		SetReverseDirection();   
	 }
	PWM_OCR1	= Ocr;
		
}
