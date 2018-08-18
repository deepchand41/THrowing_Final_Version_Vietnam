/* 
* GenevaMotor.h
*
* Created: 5/31/2018 4:19:01 AM
* Author: Deepak Chand
*/


#ifndef __GENEVAMOTOR_H__
#define __GENEVAMOTOR_H__

#include "headers.h"

#define ICR_TOP    249
#define MAX_VALUE  249
#define MIN_VALUE  -249

//For Geneva Motor


#define DD_F_G          B,4
#define DD_B_G          B,7

#define DD_PWM_G        B,5
#define PWM_TCCRA_G     TCCR1A
#define PWM_TCCRB_G     TCCR1B
#define PWM_ICR_G       ICR1
#define PWM_OCR_G       OCR1A

#define PWM_G_COM0      COM1A0
#define PWM_G_COM1      COM1A1

#define PWM_G_WGM0      WGM10
#define PWM_G_WGM1      WGM11
#define PWM_G_WGM2      WGM12
#define PWM_G_WGM3      WGM13
#define PWM_G_CS0       CS10
#define PWM_G_CS1       CS11
#define PWM_G_CS2       CS12

class GenevaMotor
{
	public:
		void Initialize_Geneva_Motor();
		void InitPWM();
		void SetForwardDirection();
		void SetReverseDirection();
		void StopMotor();
		void SetOcrValue(int x);

}; //GenevaMotor

#endif //__GENEVAMOTOR_H__
