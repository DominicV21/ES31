#define Potmeter  A0

uint8_t sinusArray[360];
int prevPot = 0;

ISR(TIMER1_COMPA_vect)
{
  static int i = 0;

  cli();

  PORTD &= 0x03;
  int mask = sinusArray[i];
  mask &= 0xFC;

  PORTD |= mask;

  i++;

  sei();

  if(i == sizeof(sinusArray))
  {
    i = 0;
  }
}

void calculateArrayValues()
{
  for (int i = 0; i < 360; i++)
  {
    double i2 = i;
    double rad = (i2 * 2.0 * M_PI) / 360.0; // calculating degrees to rads
    double sine = sin(rad);                 // calculating the sine
    double result = (sine * 127.5) + 127.5; // mapping the value
    sinusArray[i] = result;                  // storing them in an array
  }
}

void setup()
{
  calculateArrayValues();

  cli();

  DDRD = 0;
  DDRD |= _BV(DDD2) | _BV(DDD3) | _BV(DDD4) | _BV(DDD5) | _BV(DDD6) | _BV(DDD7);

  //clear registers
  TCCR1A = 0;
  TCCR1B = 0;

  //compare interval
  OCR1A = 40000;

  //set CTC-mode
  TCCR1B |= _BV(WGM12);

  // prescaler 1
  TCCR1B |= _BV(CS10);

  // timer interrupts
  TIMSK1 = 0;            // clear the interrupt mask
  TIMSK1 |= _BV(OCIE1A);  // enable compare interupt

  sei();
}

void loop()
{
  //read the analog pin, update the OCR1A register if the value has changed
  int currentPotValue = analogRead(Potmeter);
  if (currentPotValue != prevPot)
  {
    prevPot = currentPotValue;
    cli();
    OCR1A = map(currentPotValue, 0, 1023, 3000, 65535);
    sei();
  }
}

