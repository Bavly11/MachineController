/*
 * keypad.c
 *
 * Created: 10/2/2018 5:13:31 AM
 *  Author: stone
 */ 
#include <avr/io.h>
#include "keypad.h"

#define col(x) ( x==1 ? COL1 : x==2 ? COL2 : x==3 ?COL3 : COL4 )
#define row(x) ( x==1 ? ROW1 : x==2 ? ROW2 : x==3 ?ROW3 : ROW4 )

void keypad_initialize()
{
	//initialize rows as inputs
	DDRA &= ~(1<<ROW1) | ~(1<<ROW2) | ~(1<<ROW3) | ~(1<<ROW4);
	//initialize cols as outputs
	DDRA |= (1<<COL1) | (1<<COL2) | (1<<COL3) | (1<<COL4);
	//initialize all buttons as not pressed
	PORTA |= (1<<COL1) | (1<<COL2) | (1<<COL3) | (1<<COL4);
	//deactivate pull up resistors on inputs
	PORTA &= ~(1<<ROW1) | ~(1<<ROW2) | ~(1<<ROW3) | ~(1<<ROW4);
	
	Keypad_key_pressesd_interrupt_init();
	
}
static void Keypad_key_pressesd_interrupt_init( void )
{	
	DDRD |=(1 << DDD2);		 /* Clear the PD2 pin
								 PD2  is now an output*/
	
	MCUCR |=(1<<ISC00); //logical change
	
	GICR |=(1<<INT0);
	
   // sei();// turn on interrupt
}
uint16_t keypad_state = 0xffff; // default state
const uint8_t buffer_size = 10;

void keypad_scan(){
	
	static uint16_t keypad_buffer[10]={0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};
	static uint8_t buffer_cursor = 0;
	static uint16_t cols_state=0x0000;
	uint16_t buffer_and,buffer_or;
	
	cols_state=0x0000;
	for(int col=0;col<=3 ;col++){
		PORTA &= ~(1<<(4+col)); //trade off between code size and simplicity and on the other hand speed degradation
		//read the rows of each column
		cols_state|=(((uint16_t)(PORTA&(00001111)))<<col*4);
		PORTA |=(1<<(4+col));	
	}
	keypad_buffer[buffer_cursor]=cols_state;
	if (++buffer_cursor >= buffer_size) buffer_cursor -= buffer_size;
	buffer_or = 0x0000; buffer_and = 0xffff;
	for (int i = 0; i < buffer_size; ++i) {
		buffer_or |= keypad_buffer[i]; buffer_and &= keypad_buffer[i];
	}
	keypad_state&=buffer_or;
	keypad_state|=buffer_and;
	
}

uint16_t keypad_read(){
	return keypad_state;
}