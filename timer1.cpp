/// Author:        
// Net ID:         
// Date:           
// Assignment:     Lab 3
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/

void initTimer1(){
  //Set the mode to CTC 
  TCCR1A &= ~(1<<WGM10);
  TCCR1A &= ~(1<<WGM11);   
  TCCR1B |=  (1<<WGM12);
}

/* This delays the program an amount specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
  //calculate number of ticks for 1 microsecond
  int numTicks = 2 * delay;

  // Make sure the appropriate flag is down
  TIFR1 |= (1<<OCF1A);

  // clear the timer
  TCNT1H = 0;
  TCNT1L = 0;

  // calculate the TOP value and assign it to OCR1A (OCR1AH and OCR1AL)
  OCR1AH = (numTicks & 0x0F); 
  OCR1AL = ((numTicks >> 8) & 0x0F);
  

  // Turn on the timer by setting the prescaler to 8
  TCCR1B = (1<<CS11);

  // Do nothing while the OCF1A flag is not up
  while(!(TIFR1 & (1 << OCF1A)));
  
  // Turn off the timer
  TCCR1B &= ~(1<<CS12 | 1<<CS11 | 1<<CS10);
   
}

