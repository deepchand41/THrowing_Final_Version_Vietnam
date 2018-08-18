/*
 * Encoder.cpp
 *
 * Created: 10/24/2017 10:10:26 PM
 *  Author: HB
 */ 
#include "Encoder.h"
#include "uart.h"

Encoder::Encoder()
{
	Count        = 0;
	Angle_count  = 0;
	Angle        = 0;
	Encoder_rpm  = 0;
	Count_Angle  = 0;
}

void  Encoder::Encoder_Initialize(void)
{
	INPUT(ENCODER_PIN1);
	INPUT(ENCODER_PIN2);

	Encoder_Initialize_External_Interrupt();            //Initialize External Interrupt zero(INT0)
	Encoder_Initialize_Timer();			                //for the calculation of rpm
}

void Encoder::Encoder_Initialize_Timer(void)
{
	TCCR0B |= (1<<CS02) | (1<<CS00);			        //prescaler of 1024
	OCR0A   = 155;
	TIMSK0 |= (1<<OCIE0A);
	TIFR0  |= (1<<OCF0A);
	TCNT0   = 0;
}

void Encoder::Encoder_Initialize_External_Interrupt(void)
{
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<ENCODER_INTERRUPT);
	EIFR  |= (1<<ENCODER_INTERRUPT_FLAG);
}

void Encoder::Encoder_Increase_Pulse_Counter(void)
{
	if (READ(ENCODER_PIN2))
	{
		Count--;
		ExtraCount--;
		Angle_count--;
	}
	else if (!READ(ENCODER_PIN2))
	{
		Count++;
		ExtraCount++;
		Angle_count++;
	}
	
}

int Encoder::Get_Count(void)
{
	return Count;
}

void Encoder::Encoder_Calculate_RPM_Distance(void)
{
	Encoder_rpm = float((float(Count)/ENCODER_PPR)*6000);
	Count = 0;
}

int Encoder::Get_RPM(void)
{
	return Encoder_rpm;
}

void Encoder::Encoder_Increase_Angle_Counter(void)
{

}

int Encoder::Encoder_Get_angle()
{
	Angle = (float(Angle_count)*(float(ENCODER_MOTOR_FACTOR)/ENCODER_PPR))*360;
	return Angle;
}

void Encoder::Encoder_update_Speed()
{
	EncoderBuffer[3] = EncoderBuffer[2];
	EncoderBuffer[2] = EncoderBuffer[1];
	EncoderBuffer[1] = EncoderBuffer[0];
	EncoderBuffer[0] = Count;
	speed   =  ((EncoderBuffer[0]+EncoderBuffer[1]+EncoderBuffer[2]+EncoderBuffer[3])>>2);
	Count = 0;
}