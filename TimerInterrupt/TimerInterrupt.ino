// Pin definitions
#define SLIDER1  0
#define SLIDER2  1
#define SLIDER3  2
#define LIGHT    3
#define TEMP     4
#define KNOCK    5

#define BUZZER   3
#define DATA     4
#define LED1     5
#define LED2     6
#define LATCH    7
#define CLOCK    8
#define BUTTON1  10
#define BUTTON2  11
#define BUTTON3  12

uint8_t val;
boolean dotState = false;
int prevSlider = 0;

const uint8_t displayCharSet[] = 
{
  // each byte represent one appearance of the 8-segment display
  // each bit in a byte represent one segment of the 8-segment display
  0xC0, //  0 
  0xF9, //  1
  0xA4, //  2
  0xB0, //  3
  0x99, //  4
  0x92, //  5
  0x82, //  6
  0xF8, //  7
  0x80, //  8
  0x90, //  9
  0x88, //  a
  0x83, //  b
  0xC6, //  c
  0xA1, //  d
  0x86, //  e
  0x8E  //  f
};

void inc_8segment(void)
{
  static int i = 0;

  val = displayCharSet[i];

  digitalWrite(LATCH,LOW);
  shiftOut(DATA,CLOCK,MSBFIRST,val);  
  digitalWrite(LATCH,HIGH);

  i++;
  i %= sizeof (displayCharSet);
}

ISR(PCINT0_vect)
{
  static boolean state = false;

  state = !state;  // toggle
  digitalWrite (LED1, state ? HIGH : LOW);
}

//interupt on compare instead of OVF(overflow))
ISR(TIMER1_COMPA_vect)
{
  static int k = 0;
  static long timer = 0;

  timer += OCR1A;

  k++;
  // update segmentdisplay (OCR1A */ 5) times
  if (k == 5)
  {
    k = 0;
    inc_8segment();
  }

  
    // 250000 = 1 sec 
    if (timer >= 250000)
    {
      timer = 0;
      dotState = !dotState;
    }
    
    // turn dot on or off
    bleepingDot();
}


void bleepingDot()
{
  if(dotState)
  {
    // turn dot on
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLOCK,MSBFIRST, val & 0x7F);
    digitalWrite(LATCH,HIGH);
  }
  else
  {
    // turn dot off
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLOCK,MSBFIRST, val);
    digitalWrite(LATCH,HIGH);
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  digitalWrite(BUTTON1, HIGH);
  digitalWrite(BUTTON2, HIGH);
  digitalWrite(BUTTON3, HIGH);

  pinMode(BUZZER, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

  //disable interupts
  cli();

  // digital interrupts
  PCMSK0 |= _BV (PCINT3);  // we want button 2 (connected to pin D11)
  PCIFR  |= _BV (PCIF0);   // clear any outstanding interrupts
  PCICR  |= _BV (PCIE0);   // enable pin change interrupts for 0

    //clear registers
  TCCR1A = 0;
  TCCR1B = 0;

  //compare interval
  OCR1A = 25000;

  //set CTC-mode
  TCCR1B |= _BV (WGM12);

  // prescaler 64
  TCCR1B |= _BV(CS11) | _BV(CS10);

  // timer interrupts
  TIMSK1 = 0;            // clear the interrupt mask
  TIMSK1 |= _BV(OCIE1A);  // enable compare interupt

  //enable interupts
  sei();
}


void loop()
{
  int slider = analogRead(SLIDER1);
  
  //check if slider changed
  if(prevSlider != slider)
  {
    prevSlider = slider;
    //disable interupts
    cli();
    //change timerlimit
    OCR1A = map(slider, 0, 1023, 1000, 25000);
    //enable interupts
    sei();
  }
}







