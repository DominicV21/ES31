#define buttonPressD10 ((PINB & _BV(PINB2)) >> PINB2)
#define buttonPressD11 ((PINB & _BV(PINB3)) >> PINB3)
#define buttonPressD12 ((PINB & _BV(PINB4)) >> PINB4)

#define buzzerPin _BV(PIND3)
#define ledD5 _BV(PIND5)
#define ledD6 _BV(PIND6)

#define pullUp 0xFF

void setup()
{
  DDRD |= buzzerPin | ledD5 | ledD6;
  DDRB = 0;
  PORTB = pullUp;


  Serial.begin(9600);
}

void loop()
{
  //PORTD &= reset;
  if(!buttonPressD10 && buttonPressD11 && buttonPressD12)
  {
    PORTD |= ledD5;
  }
  else 
  { 
    PORTD &= ~ledD5; 
  }
  
  
  if(!buttonPressD12 && buttonPressD10 && buttonPressD11)
  {
    PORTD |= ledD6;
    Serial.println("Hello World!");
  }
  else
  {
    PORTD &= ~ledD6;
  }
  
  if(!buttonPressD10 && !buttonPressD12 && buttonPressD11)
  {
    Buzz();
  }
}


void Buzz()
{
  PORTD |= buzzerPin;
  delay(2);
  PORTD &= ~buzzerPin;
  delay(2);
}

