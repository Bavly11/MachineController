/*
 * IncFile1.h
 *
 * Created: 10/2/2018 3:59:42 AM
 *  Author: stone
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

//The interfacing port for Keypad
#define KEYPAD_PORT PORTA

//The pins definitions for rows & columns definitions
//bit definitions


//bit fields definitions

//rows to scan
#define ROW1 PA0
#define ROW2 PA1
#define ROW3 PA2
#define ROW4 PA3

//connecting each col to ground
#define COL1 PA4
#define COL2 PA5
#define COL3 PA6
#define COL4 PA7


void keypad_initialize();

#endif /* INCFILE1_H_ */
