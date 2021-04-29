/*      Author Sidharth Ramkumar (sramk002@ucr.edu) 
 *       *       *  Partner(s) Name: 
 *        *        *      Lab Section: 022
 *         *         *      Assignment: Lab #6  Exercise #3
 *          *          *      Exercise Description: [optional - include for your own benefit]
 *           *           *
 *            *            *      I acknowledge all content contained herein, excluding template or example
 *             *             *      code, is my own original work.
 *              *              */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define b1 (~PINA & 0x01)
#define b2 (~PINA & 0x02)

unsigned char userVal;
unsigned long timeElapsed; //increments of 100 miliseconds

enum Num_States { SMStart, Wait, Inc, Dec, Reset } Num_State;

void TickFct(){
   switch(Num_State) {
        case SMStart:
        Num_State = Wait;
        break;

        case Wait:
        if (b1 && !b2){
        timeElapsed = 10;
        Num_State = Inc;
        } else if (!b1 && b2){
        timeElapsed = 10;
        Num_State = Dec;
        } else if (!b1 && !b2){
        Num_State = Wait;
        } else {
        Num_State = Reset;
        }
        break;

        case Inc:
        if (b1 && !b2){
        Num_State = Inc;
        } else if (!b1 && b2){
        Num_State = Dec;
        } else if (!b1 && !b1){
        Num_State = Wait;
        } else {
        Num_State = Reset;
        }
        break;

        case Dec:
        if (!b1 && b2){
        Num_State = Dec;
        } else if (b1 && !b2){
        Num_State = Inc;
        } else if (!b1 && !b2){
        Num_State = Wait;
        } else {
        Num_State = Reset;
        }
        break;

        case Reset:
        if (b1 || b2){
        Num_State = Reset;
        } else {
        Num_State = Wait;
        }
        break;
   }

   switch (Num_State){
        case Wait:
        timeElapsed = 0;
        break;

        case Inc:
        if (timeElapsed < 10 && userVal < 9){
        timeElapsed += 1;
        } else if (timeElapsed >= 10 && userVal < 9){
        timeElapsed = 0;
        userVal += 1;
        }
        break;

        case Dec:
        if (timeElapsed < 10 && userVal > 0){
        timeElapsed += 1;
        } else if (timeElapsed >= 10 && userVal > 0){
        timeElapsed = 0;
        userVal -= 1;
        }
        break;

        case Reset:
        userVal = 0;
        break;
   }
}
int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
        TimerSet(100);
        TimerOn();

        timeElapsed = 0;
        userVal= 7;
        Num_State = SMStart;
while (1) {
       TickFct();
       PORTB = userVal;

        while (!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
