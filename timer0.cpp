void initTimer0(){
// Set the mode to be CTC
  TCCR0A &= ~(1 << WGM00);//CTC mode: WGM00 sets as 0
  TCCR0A |= (1 << WGM01);//CTC mode: WGM01 sets as 1
  TCCR0B &= ~(1 << WGM02);//CTC mode: WGM02 sets as 0
  
}

void delayMs(unsigned int delay){
for(unsigned int i=0; i<delay; i++){//go through the timer delay times
 OCR0A = 250; //OCROA = 250 to get 1ms 

 // Make sure the appropriate flag is down
  TIFR0 |= (1 << OCF0A);

  // Clear the timer
  TCNT0 = 0;

 // turn on the timer by setting the pre-scaler to 64
  TCCR0B |= (1 << CS01) | (1 << CS00);

  // while the flag is down, do not do anything.
  while(!(TIFR0 & (1 << OCF0A)));

  // Turn the clock back off
  TCCR0B &= ~(1 << CS02 | 1 << CS01 | 1 << CS00);
 
  }
}
