/*
 * PID.h
 *
 * Created: 1/29/2016 1:09:27 PM
 *  Author: YinYang
 */ 


#ifndef PID_H_
#define PID_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <math.h>


#define  PID_TCCRA      TCCR3A
#define  PID_TCCRB      TCCR3B
#define  PID_TCNT       TCNT3
#define  PID_CS0        CS30
#define  PID_CS2        CS32
#define  PID_TIMSK      TIMSK3
#define  PID_OCIE       OCIE3B
#define  PID_TIFR       TIFR3
#define  PID_TOV        TOV3
#define  PID_OCR        OCR3B


class PID
{
	public:
			bool PID_Flag;
			float kp,ki,kd;
			float errSum,maxOut,minOut,error,output;
			float Iterm;
			
	
	public:
			float lastinput;
			float offset;
			int setPoint;
			void Initialize();
			void Set_Range(float min,float max){minOut=min;maxOut=max;}
			void SetKp(float KP)
			{
				kp=KP;
				Set_PID(kp,ki,kd);
			}
			void SetKi(float KI)
			{
				ki=KI;
				Set_PID(kp,ki,kd);
			}
			void SetKd(float KD)
			{
				kd=KD;
				Set_PID(kp,ki,kd);
			}
			void SetSetPoint(float x)
			{
				setPoint = x;
			}
			float GetKp(){return kp;}
			float GetKi(){return ki;}
			float GetKd(){return kd;}
			void Set_PID(float KP,float KI,float KD);
			float Compute_PID(float input);
			inline int getoutput(){return output;}
			//void InitializePIDTimer();
};
#endif /* PID_H_ */