#define OUT_GROUP2      0
#define OUT_GROUP1      1
#define OUT_STROBE      2
#define OUT_KEYSELECT   3
#define OUT_BUZZER      4
#define OUT_HEATER      5
#define OUT_SPEED2      6
#define OUT_SPEED1      7
#define OUT_DATAC       8
#define OUT_DATAB       9
#define OUT_DATAA       10
#define OUT_MOTOR_RL    11
#define OUT_SOAP1       12
#define OUT_SINK        13
#define OUT_DRAIN       14
#define OUT_LOCK        15
#define IN_W2           16
#define IN_W1           17
#define IN_T2           18
#define IN_T1           19
#define IN_IN3          20
#define IN_IN2          21
#define IN_IN1          22
#define IN_IN0          23

HardwareControl::HardwareControl()
{
  Wire.begin(); // start I2C
  centipede.initialize(); // set all registers to default
  for (int i = 0; i <= 15; i++) 
  {
    centipede.pinMode(i, OUTPUT);
  }
  centipede.digitalWrite(OUT_GROUP2, LOW);
  centipede.digitalWrite(OUT_GROUP1, LOW);
  centipede.digitalWrite(OUT_STROBE, LOW);
  centipede.digitalWrite(OUT_KEYSELECT, HIGH);
  centipede.digitalWrite(OUT_BUZZER, HIGH);
  centipede.digitalWrite(OUT_HEATER, HIGH);
  centipede.digitalWrite(OUT_SPEED2, HIGH);
  centipede.digitalWrite(OUT_SPEED1, HIGH);
  centipede.digitalWrite(OUT_DATAC, LOW);
  centipede.digitalWrite(OUT_DATAB, LOW);
  centipede.digitalWrite(OUT_DATAA, LOW);
  centipede.digitalWrite(OUT_MOTOR_RL, LOW);
  centipede.digitalWrite(OUT_SOAP1, LOW);
  centipede.digitalWrite(OUT_SINK, LOW);
  centipede.digitalWrite(OUT_DRAIN, LOW);
  centipede.digitalWrite(OUT_LOCK, LOW);
}

boolean HardwareControl::GetCoin10Button()
{
  return (false);
}

boolean HardwareControl::GetStartButton()
{
  return (false);
}

int HardwareControl::GetTemperature()
{
  int temp = 0;
  if(centipede.digitalRead(IN_T1) == LOW && centipede.digitalRead(IN_T2) == LOW)
  {
    temp = 0;
  }
  else if(centipede.digitalRead(IN_T1) == HIGH && centipede.digitalRead(IN_T2) == LOW)
  {
    temp = 1;
  }
  else if(centipede.digitalRead(IN_T1) == LOW && centipede.digitalRead(IN_T2) == HIGH)
  {
    temp = 2;
  }
  else if(centipede.digitalRead(IN_T1) == HIGH && centipede.digitalRead(IN_T2) == HIGH)
  {
    temp = 3;
  }
  return temp;
}

boolean HardwareControl::GetSoap1()
{
  SetKeySelect(0);
  if(centipede.digitalRead(IN_IN1) == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean HardwareControl::GetSoap2()
{
  SetKeySelect(0);
  if(centipede.digitalRead(IN_IN2) == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}


void HardwareControl::SetSoap1(int level)
{
  if(level == 0)
  {
    centipede.digitalWrite(OUT_SOAP1, LOW);
  }
  else
  {
    centipede.digitalWrite(OUT_SOAP1, HIGH);
  }
}

void HardwareControl::SetSoap2(int level)
{
  if (level == 0)
  {
    SetGroup(2, 1);
    SetGroup(1, 0);
    SetData(0);
  }
  else
  {
    SetGroup(2, 1);
    SetGroup(1, 0);
    SetData(3);
  }
  Strobe();
}

void HardwareControl::SetHeater(boolean state)
{
  if(!state)
  {
    centipede.digitalWrite(OUT_HEATER, HIGH);
  }
  else
  {
    centipede.digitalWrite(OUT_HEATER, LOW);
  }
}

void HardwareControl::SetDrain(int level)
{
}

void HardwareControl::SetDirection(int dir)
{
}

void HardwareControl::SetProgramIndicator(int program)
{
}

void HardwareControl::SetBuzzer(int level)
{
}

void HardwareControl::SetKeySelect(int value)
{
  centipede.digitalWrite(OUT_KEYSELECT, value);
}

void HardwareControl::SetGroup(int group, int level)
{
  if(group == 1)
  {
    centipede.digitalWrite(OUT_GROUP1, level);
  } 
  else if (group == 2)
  {
    centipede.digitalWrite(OUT_GROUP2, level);
  }
}

void HardwareControl::SetData(int data)
{
  if(data <= 3 && data >= 0)
  {
    centipede.digitalWrite(OUT_DATAC, LOW);
    centipede.digitalWrite(OUT_DATAB, LOW);
    centipede.digitalWrite(OUT_DATAA, LOW);
    
    switch(data)
    {
      case 1 :
      {
        centipede.digitalWrite(OUT_DATAA, HIGH);
      }
      case 2 :
      {
        centipede.digitalWrite(OUT_DATAB, HIGH);
      }
      case 3 :
      {
        centipede.digitalWrite(OUT_DATAC, HIGH);
      }
    }
  }
}

void HardwareControl::Strobe()
{
  centipede.digitalWrite(OUT_STROBE, LOW);
  delay(80);
  centipede.digitalWrite(OUT_STROBE, HIGH);
  delay(10);
  centipede.digitalWrite(OUT_STROBE, LOW);
}





