/*
 * GameFunctions.h
 *
 * Created: 5/30/2018 4:37:00 AM
 *  Author: Deepak Chand
 */ 


#ifndef GAMEFUNCTIONS_H_
#define GAMEFUNCTIONS_H_

#include <avr/io.h>
#include <util/delay.h>
#include "General-function.h"
#include "Motor.h"
#include "GenevaMotor.h"
#include "GenevaEncoder.h"
#include "PID.h"
#include "headers.h"
#include "Encoder.h"

#define Throwing_12TCRT            D,1
#define Throwing_3TCRT             D,2
#define Home_TCRT                  D,3
#define Pneumatic                  L,0
#define ShuttleCockArm_P           G,2
#define Grip_P                     G,0
#define Plick_Plick                C,6
#define Plick_Plick_2              C,0


#define  Throwing_Zone_12_Interrupt_vect  INT2_vect
#define  Throwing_Zone_3_Interrupt_vect   INT1_vect

volatile bool HundredMS            = false;
volatile bool FiveHundredMS        = false;
volatile bool ACKSentFlag          = false;
volatile bool PIDFlag			   = true;
volatile bool Throwflag			   = false;
volatile bool Goflag			   = false;
volatile bool Ramp_up_flag		   = false;
volatile bool Home				   = false;
volatile bool TZ1				   = false;
volatile bool TZ2				   = false;
volatile bool TZ3				   = false;
volatile bool ReceiveShuttleCock   = false;
volatile bool inhome			   = false;
volatile bool G_PID                = false;
volatile bool Grab_ShuttleCock     = false;
volatile bool Grab_Rack            = false;
volatile bool first_Golden         = false;
volatile bool GOLDEN_1             = false;
volatile bool gotRack              = false;

volatile bool Golden_Rack          = false;
volatile bool ReachedHome          = false;
volatile bool Stopping             = false;
volatile bool Negative_Ramp        = false;

bool Going_To_RUNGBAY             = false;

bool ShuttleCockArm_home           = false;

#define MAX_SPEED		120
#define RAMP_STEP		3

GenevaMotor G;
Motor   M;
Encoder E;
GenevaEncoder E1;
PID    Speed_PID;
PID    Angle_PID;
PID    Geneva_PID;

int TCRTRevolutionCount;
unsigned long previous_time_gone_home = 0;

void Initialize_All(void);
void Initialize_Throwing12TCRT_Interrupt(void);
void Initialize_Throwing3TCRT_Interrupt(void);
void GoToHome(void);
void Run_Geneva(void);
void Initialize_Global_Timer(void);
void Initial_Position_Of_The_ARM(void);



void Run_Geneva()
{
	G_PID = true;
	Geneva_PID.SetSetPoint(720);
}

void Initialize_Throwing12TCRT_Interrupt()
{
	INPUT(Throwing_12TCRT);								//Interrupt Pin as Input
	SET(Throwing_12TCRT);									//Pull_UP
	
	EICRA |= (1<<ISC21);						//Falling Edge Interrupt
	EIMSK |= (1<<INT2);
	EIFR  |= (1<<INTF2);
}

void Initialize_Throwing3TCRT_Interrupt(void)
{
	INPUT(Throwing_3TCRT);               //Interrupt Pin as Input
	SET(Throwing_3TCRT);                 //Pull up
	
	EICRA |= (1<<ISC11);                 //Falling Edge Interrupt
	EIMSK |= (1<<INT1);
	EIFR  |= (1<<INTF1);

}

void Initialize_All()
 {
	Initialize_Throwing12TCRT_Interrupt();
	Initialize_Throwing3TCRT_Interrupt();
	M.Initialise();
	E.Encoder_Initialize();
	G.Initialize_Geneva_Motor();
	E1.Initialize_Geneva_Encoder();
}

void Initialize_Global_Timer()
{
	TCNT2 = 0;
	TCCR2B |= (1<<CS20)|(1<<CS21)|(1<<CS22);
	TIMSK2 |= (1<<TOIE2);
	TIFR2  |= (1<<TOV2);
}

void Initial_Position_Of_The_ARM(void)
{
	sei();
	while(!READ(Throwing_3TCRT))
	{
		M.SetOcrValue(-60);
	}
	E.Angle_count = 0;
	M.StopMotor();
	TCRTRevolutionCount = 0;
	E.ExtraCount = 0;
	
	
	Speed_PID.SetSetPoint(0);
	Angle_PID.SetSetPoint(E.Angle_count);
	PIDFlag = false;
	Speed_PID.lastinput = 0;
	Speed_PID.output    = 0;
	Speed_PID.Iterm     = 0;
}

void GoToHome()
{
	sei();
	while(!READ(Home_TCRT))
	{
		M.SetOcrValue(-60);	
	//	ReachedHome = false;
	}
	E.Angle_count = 0;
	M.StopMotor();
	
	TCRTRevolutionCount = 0;
	E.ExtraCount = 0;
	Speed_PID.SetSetPoint(0);
	Angle_PID.SetSetPoint(0);
	PIDFlag = false;
	Speed_PID.lastinput  = 0;
	Speed_PID.Iterm      = 0;
	Speed_PID.output     = 0;
		
	Stopping = true;
	
	if (!Golden_Rack && !ShuttleCockArm_home)
	{
		ShuttleCockArm_home = true;
		previous_time_gone_home = millis();
	}	
}


#endif /* GAMEFUNCTIONS_H_ */