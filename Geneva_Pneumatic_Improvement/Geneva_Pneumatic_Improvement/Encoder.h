/*
 * Encoder.h
 *
 * Created: 10/24/2017 10:10:26 PM
 *  Author: HB
 */ 

#ifndef ENCODER
#define ENCODER

#include "Headers.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//#define DDR_SELECT DDRC

#define TIMER_OVERFLOW_VECT TIMER0_OVF_vect		 //Set the timer/counter overflow vector name

#define ENCODER_PIN1 D,0		                 //Set the interrupt pin for the encoder
#define ENCODER_PIN2 A,0		                 //Set the digital pin for encoder
#define ENCODER_INTERRUPT INT0		             //Set the interrupt for interrupt init
#define ENCODER_INTERRUPT_VECT INT0_vect	     //Set the respective interrupt vector name
#define ENCODER_INTERRUPT_FLAG INTF0		     //Enable the respective interrupt flag


#define ENCODER_PPR 1020		                 //Set the PPR value of the encoder motor
#define ENCODER_RADIUS 5	                     //Set the radius of the wheel so as to calculate the distance covered
#define ENCODER_MOTOR_FACTOR 1

class Encoder
{
	private:
	int Angle;
	long int EncoderBuffer[4];
	long int speed;
	

	public:
	long int Count;
	long int ExtraCount;
	int Angle_count;
	int Encoder_rpm;
	
	Encoder();
	volatile int Count_Angle ;
	void Encoder_Initialize(void);
	void Encoder_Initialize_Timer(void);	                           //Initializes the timer
	void Encoder_Initialize_External_Interrupt(void);	               //Enables the interrupt pin
	void Encoder_Increase_Angle_Counter(void);

	int Encoder_Get_angle();
	inline void Encoder_Set_angle(int val){Angle = val;}
	int Get_RPM(void);
	int Get_Count(void);
	void Encoder_Increase_Pulse_Counter(void);
	void Encoder_Calculate_RPM_Distance(void);
	void Encoder_update_Speed();
	inline int Encoder_get_speed(){return speed;}
	
};
	
	
#endif



