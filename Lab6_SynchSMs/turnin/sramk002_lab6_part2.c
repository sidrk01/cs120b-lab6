/* Author: Sidharth Ramkumar (sramk002@ucr.edu)
 *  Partner(s) Name: none
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * 	Demo Link: https://youtu.be/MxoNZygQW5A
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define button (~PINA & 0x01)

enum LED_Blink {SMStart, L1, L2, L3, Press, Press_Wait, Restart} LED_State;

void Tick_Fct(){
   switch(LED_State){
	case SMStart: 
	LED_State = L1; 
	break;
	
	case L1: 
	if (button){
	LED_State = Press;
	} else {
	LED_State = L2;
	}
	break;

	case L2:
	if (button){
	LED_State = Press;
	} else {
	LED_State = L3;
	}
	break;

	case L3: 
	if (button) {
	LED_State = Press;
	} else {
	LED_State = L1;
	}
	break;
	
	case Press:
	if (button){
	LED_State = Press;
	} else {
	LED_State = Press_Wait;
	}
	break;
		
	case Press_Wait:
	if (button){
	LED_State = Restart;
	} else {
	LED_State = Press_Wait;
	}
	break;

	case Restart:
	if (button){
	LED_State = Restart;
	} else {
	LED_State = L1;
	}
	break;	
   }

   switch(LED_State){
	case SMStart: 
	case L1:
	PORTB = 0x01;
	break;

	case L2:
	PORTB = 0x02;
	break;

	case L3: 
	PORTB = 0x04; 
	break;
        
	default:
	break;	
   }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	TimerSet(300);
	TimerOn();
	
	LED_State = SMStart;
    while (1) {
	//User code (i.e. synchSM calls) 
	Tick_Fct(); //Toggle PORTB

	while (!TimerFlag); //Wait 1 sec
	TimerFlag = 0;

    }
    return 1;
}
