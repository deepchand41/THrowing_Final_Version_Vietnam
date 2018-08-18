/*
 * headers.h
 *
 * Created: 2/18/2017 4:33:57 PM
 *  Author: Bibek Shrestha
 */ 


#ifndef HEADERS_H_
#define HEADERS_H_

#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#define INPUT2(port,pin) DDR ## port &= ~_BV(pin)
#define OUTPUT2(port,pin) DDR ## port |= _BV(pin)
#define CLEAR2(port,pin) PORT ## port &= ~_BV(pin)
#define SET2(port,pin) PORT ## port |= _BV(pin)
#define TOGGLE2(port,pin) PORT ## port ^= _BV(pin)

#define READ2(port,pin) ((PIN ## port & _BV(pin))?1:0)

#define REGISTER_SET1( REGISTER, BIT1 ) REGISTER|=_BV( BIT1 )
#define REGISTER_SET2( REGISTER, BIT1, BIT2 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )
#define REGISTER_SET3( REGISTER, BIT1, BIT2, BIT3 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )|_BV( BIT3 )
#define REGISTER_SET4( REGISTER, BIT1, BIT2, BIT3, BIT4 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )|_BV( BIT3 )|_BV( BIT4 )
#define REGISTER_SET5( REGISTER, BIT1, BIT2, BIT3, BIT4, BIT5 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )|_BV( BIT3 )|_BV( BIT4 )|_BV( BIT5 )
#define REGISTER_SET6( REGISTER, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6 ) REGISTER|=_BV( BIT1 )|_BV( BIT2 )|_BV( BIT3 )|_BV( BIT4 )|_BV( BIT5 )|_BV( BIT6 )
#define REGISTER_RESET( REGISTER,BIT ) REGISTER&=~_BV( BIT )
#define READVALUE(REGISTER) REGISTER
#define REGISTER_CLEAR(REGISTER) REGISTER = 0


#define INPUT(x) INPUT2(x)
#define OUTPUT(x) OUTPUT2(x)
#define CLEAR(x) CLEAR2(x)
#define SET(x) SET2(x)
#define TOGGLE(x) TOGGLE2(x)
#define READ(x) READ2(x)
#define PULLUP_ON(x) INPUT2(x); SET2(x)
#define PULLUP_OFF(x) INPUT2(x); CLEAR2(x)

#define InitializeGeneralInterrupt sei()

#include <avr/io.h>
#include <avr/interrupt.h>

#include <avr/wdt.h>

#include "uart.h"



#endif /* HEADERS_H_ */