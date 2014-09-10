#define buttonPressD10 0x3B
#define buttonPressD11 0x2F
#define buttonPressD11AndD12 0x2B

#define buzzerPin _BV(3)
#define ledD5 _BV(5)
#define ledD6 _BV(6)

#define pullUp 0x003F

#define reset 0

void setup()
{
  DDRD |= buzzerPin | ledD5 | ledD6;
  DDRB = 0;
  PORTB = pullUp;


  Serial.begin(9600);
}

void loop()
{
  PORTD &= reset;
  if(PINB == buttonPressD10)
  {
    PORTD |= ledD5;
  }
  else if(PINB == buttonPressD11)
  {
    PORTD |= ledD6;
    Serial.println("Hello World!");
  }
  else if(PINB == buttonPressD11AndD12)
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

