#include <avr/sleep.h>
int led = 13;

void setup() 
{                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  WDTCSR |= _BV(WDCE); // enable watchdog interupt timer change
  WDTCSR |= _BV(WDP3); // change watchdog interupt timer prescaler to 4sec
  
  CLKPR = 0x80; // enable prescaler editing
  CLKPR = 0x00; // edit prescaler
  
  
  
  PRR |= 0xFF; //Disable all timers and other peripherals
  ADCSRA &= ~(1<<ADEN); //Disable ADC
  ACSR = (1<<ACD); //Disable the analog comparator
  DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins
  DIDR1 = (1<<AIN1D)|(1<<AIN0D); //Disable digital input buffer on AIN1/0
  

}

ISR(SIG_WATCHDOG_TIMEOUT)
{
  
}

void loop() 
{
  Blink();

  SMCR |= _BV(SE) | _BV(SM1); //enable sleep and set power down
  sleep_cpu(); //call cpu sleep
  
}


void myDelay(volatile double time)
{
  for(volatile double i = 0; i < time; i++)
  {
    //Keep the cpu buisy for 1,0002 seconds
  }
}

void Blink()
{
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  myDelay(390534);               // wait for 5 seconds (72402 = 1 sec)
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  myDelay(390534);               // wait for 5 seconds (72402 = 1 sec)
}
