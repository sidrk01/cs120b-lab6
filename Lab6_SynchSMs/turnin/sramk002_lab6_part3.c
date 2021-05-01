/*      Author Sidharth Ramkumar (sramk002@ucr.edu) 
 *       *  Partner(s) Name: 
 *        *      Lab Section: 022
 *         *      Assignment: Lab #6  Exercise #3
 *          *      Exercise Description: [optional - include for your own benefit]
 *           *
 *            *      I acknowledge all content contained herein, excluding template or example
 *             *      code, is my own original work.
 *              */

#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define b1 (~PINA & 0x01)
#define b2 (~PINA & 0x02)

enum Num_States { SMStart, Wait, Inc, Dec, Reset } Num_State;

void TickFct(unsigned char *tmpB){
  static unsigned char cnt; //Local synchSM variable for time count in 100ms increments
  switch(Num_State) {
     case SMStart:
        Num_State = Wait;
     break;
      
     case Wait:
        cnt = 0;
        if (b1 && !b2){
        Num_State = Inc;
        } else if (!b1 && b2){
        Num_State = Dec;
        } else if (b1 && b2){
        Num_State = Reset;
        } else {
        Num_State = Wait;
        }
     break;
      
    case Inc:
       if (b1 && !b2){
       Num_State = Inc;
       if (cnt % 10 == 0){
          tmpB += 1;
       }
       } else if (b1 && b2){
       Num_State = Reset;
       } else if (!b1 && !b2){
       Num_State = Wait;
       } else {
        Num_State = Dec;
        cnt = 0;
       }
   break;
      
    case Dec:
      if (!b1 && b2){
      Num_State = Dec;
        if (cnt % 10 == 0){
          tmpB -= 1;
        }
      } else if (b1 && b2){
       Num_State = Reset;
      } else if (b1 && b2){
       Num_State = Wait;
      } else {
        Num_State = Inc;
        cnt = 0;
      }      
    break;
      
      case Reset:
      if (b1 || b1){
      Num_State = Reset;
      } else {
        Num_State = Wait;
      }
      break;   
  }
  
  switch (Num_State){
    case Inc:
    case Dec:
        cnt += 1;
    break;
    
    case Reset:
        tmpB = 0x00;
    break;
      
    default:
      break;
  }
}

int main(void){
/* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
        unsigned char tmpB = 0x07;
  
        TimerSet(100);
        TimerOn();
  
        Num_State = SMStart;
  while (1){
      TickFct(&tmpB);
      if (tmpB >= 0x09){
        tmpB = 0x09;
      } else if (tmpB <= 0x00){
        tmpB = 0x00;
      }
        PORTB = tmpB
      
      while(!TimerFlag); //Wait 100 ms
      TimerFlag = 0;
  }
  return 1;
  
}
