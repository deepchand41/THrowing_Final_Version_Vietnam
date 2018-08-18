#ifndef MOTOR_H
#define MOTOR_H


	#include "headers.h"

     #define ICR_TOP   249
     #define MAX_VALUE 249
     #define MIN_VALUE -249 


	//For Throwing Motor


    #define DD_F1  H,5                          //B,6
    #define DD_B1  H,6                           //H,6

    #define DD_PWM1			B,6                  //B,5           OC3A
    #define PWM_TCCRA1		TCCR1A                                     //Timer 3
    #define PWM_TCCRB1		TCCR1B
    #define PWM_ICR1		ICR1
    #define PWM_OCR1		OCR1B

    #define PWM_1COM0		COM1B0
    #define PWM_1COM1		COM1B1

    #define PWM_1WGM0		WGM10
    #define PWM_1WGM1		WGM11
    #define PWM_1WGM2		WGM12
    #define PWM_1WGM3		WGM13
    #define PWM_1CS0		CS10
    #define PWM_1CS1		CS11
    #define PWM_1CS2		CS12

    


class Motor
{

     private:
		
     public:
        void Initialise();

        void InitPWM();

        void SetForwardDirection();
        void SetReverseDirection();
        void StopMotor();
        void SetOcrValue(int x);
};

#endif // MOTOR_H
