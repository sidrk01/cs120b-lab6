/* Author: Sidharth Ramkumar (sramk002@ucr.edu)
 *  Partner(s) Name: none
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #`
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	TimerSet(1000);
	TimerOn();
	unsigned char tmpB = 0x00;
    while (1) {
	//User code (i.e. synchSM calls) 
	tmpB = ~tmpB; //Toggle PORTB; Temporary, bad programming style;
	PORTB = tmpB;
	while (!TimerFlag); //Wait 1 sec
	TimerFlag = 0;

    }
    return 1;
}
