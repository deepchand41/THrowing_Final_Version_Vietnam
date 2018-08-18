/* 
* GenevaEncoder.h
*
* Created: 5/31/2018 5:16:56 AM
* Author: Deepak Chand
*/


#ifndef __GENEVAENCODER_H__
#define __GENEVAENCODER_H__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "headers.h"

#define ENCODERA      E,4
#define ENCODERB      A,1

#define ENCODER_EICR    EICRB
#define ENCODER_INT     INT4
#define ENCODER_INTPIN  E,4
#define ENCODER_ISC0    ISC40
#define ENCODER_ISC1    ISC41
#define ENCODER_INTF    INTF4
#define GENEVA_ENCODER_INT_vect INT4_vect

#define PPR 180

class GenevaEncoder
{
	private:
		volatile int Encoder_Count;
	public:
		long count;
		int Geneva_Angle;
	public:
		GenevaEncoder();
		void Initialize_Geneva_Encoder(void);
		inline void Inc_Count(){Encoder_Count++;};
		inline void Dcr_Count(){Encoder_Count--;};
		inline void Reset_Count(){Encoder_Count = 0;};
			
		int Get_Count(){return Encoder_Count;};
		void Encoder_Increase_Pulse_counter();
		int Enoder_Get_Angle();

}; //GenevaEncoder

#endif //__GENEVAENCODER_H__
