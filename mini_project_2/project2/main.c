/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: Stop Watch using atmega32 with multiplixed Technic
 *
 * Author: Mahmoud Abdelrahman
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char sec1=0;
unsigned char sec2=0;
unsigned char min1=0;
unsigned char min2=0;
unsigned char hour1=0;
unsigned char hour2=0;
ISR(TIMER1_COMPA_vect)
{
	sec1++;
	if(sec1==10)
	{
		sec1=0;
		sec2++;
	}
	if(sec2==6)
	{
		sec1=0;
		sec2=0;
		min1++;
	}
	if(min1==10)
	{
		min2++;
		min1=0;

	}
	if(min2==6)
	{
		min2=0;
		hour1++;
	}
	if(hour1==10)
	{
		hour1=0;
		hour2++;
	}

}
void timer1_init()

{
	/* set bits for non pwm mode*/
	TCCR1A=(1<<FOC1A)|(1<< FOC1B);
	/*(1<<WGM12) foe compare mode
	 * (1<<CS10)|(1<<CS12) for pre scaler 1024
	 * */
	TCCR1B=(1<<WGM12)|(1<<CS10)|(1<<CS12);
	/*start count from 0*/
	TCNT1=0;
	/*count to 1000 to compare match happen every 1 second*/
	OCR1A=1000;
	/*enable module interrubt for compare mode*/
	TIMSK|=(1<< OCIE1A);
}
ISR(INT0_vect)
{
	/*reset timer by make values start from 0
	 * */
	sec1=0;
	sec2=0;
	min1=0;
	min2=0;
	hour1=0;
	hour2=0;
}
void INT0_init()
{
	MCUCR|=(1<<ISC01); /*enable external interrupt to catch falling edge in INT0*/
	GICR|=(1<< INT0);/*enable module interrupt for INT0*/
	DDRD&=~(1<<2);/*make PD2 I/P pin*/
}
ISR(INT1_vect)
{
	TCCR1B&=0xf8;/*clear bits of clock*/
}
void INT1_init()
{
	MCUCR|=(1<<ISC10)|(1<<ISC11);/*enable external interrupt to catch rising edge in INT1*/
	GICR|=(1<< INT1);/*enable module interrupt for INT1*/
	DDRD&=~(1<<3);/*make PD3 I/P pin*/
}
ISR(INT2_vect)
{
	TCCR1B|=(1<<CS10)|(1<<CS12)/*set bits of clock*/;
}
void INT2_init()
{
	MCUCSR&=~(1<< ISC2);/*enable external interrupt to catch falling edge in INT2*/
	GICR|=(1<< INT2);/*enable module interrupt for INT2*/
	DDRB&=~(1<<2);/*make PB2 I/P pin*/
}
void main() {
	/*
	 * calling init function for all peripherals
	 */
	timer1_init();
	INT0_init();
	INT1_init();
	INT2_init();
	SREG|=(1<<7);/*enable I bit*/
	DDRC|=0x0f;/*make first four bins in portc O/P*/
	DDRA|=0x3f;/*make first 6 pins in porta O/P*/
	while(1)
	{
		PORTA=(PORTA&0xc0)|(1<<0);/*enable first seven segment and disable others*/
		PORTC=(PORTC&0xf0)|sec1;/*first O/P of second*/
		_delay_ms(2);/* delay for multiplixing*/
		PORTA=(PORTA&0xc0)|(1<<1);/*enable second seven segment and disable others*/
		PORTC=(PORTC&0xf0)|sec2; /*second O/P of second*/
		_delay_ms(2);/* delay for multiplixing*/
		PORTA=(PORTA&0xc0)|(1<<2);/*enable third seven segment and disable others*/
		PORTC=(PORTC&0xf0)|min1; /*first O/P of minuts*/
		_delay_ms(2); /* delay for multiplixing*/
		PORTA=(PORTA&0xc0)|(1<<3);/*enable forth seven segment and disable others*/
		PORTC=(PORTC&0xf0)|min2;/*second O/P of minuts*/
		_delay_ms(2); /* delay for multiplixing*/
		PORTA=(PORTA&0xc0)|(1<<4);/*enable fifth seven segment and disable others*/
		PORTC=(PORTC&0xf0)|hour1;/*first O/P of  hours*/
		_delay_ms(2); /* delay for multiplixing*/
		PORTA=(PORTA&0xc0)|(1<<5);/*enable six seven segment and disable others*/
		PORTC=(PORTC&0xf0)|hour2; /*second O/P of  hours*/
		_delay_ms(2); /* delay for multiplixing*/
	}
}
