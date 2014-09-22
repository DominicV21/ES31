#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include "Centipede.h"

#include "IBuzzer.h"
#include "ICoin.h"
#include "ILock.h"
#include "IMotor.h"
#include "IProgram.h"
#include "ISoap.h"
#include "ITemperature.h"
#include "IWater.h"

class HardwareControl: public IBuzzer, public ICoin, public ILock, public IMotor, public IProgram, public ISoap, public ITemperature, public IWater
{
  public:
    HardwareControl();
    // Inputs
    boolean GetCoin10Button();
    boolean GetStartButton();
    int GetTemperature();
    boolean GetSoap1();
    boolean GetSoap2();

    // Outputs
    void SetBuzzer(int level);
    void SetSoap1(int level);
    void SetSoap2(int level);
    void SetDrain(int level);
    void SetDirection(int dir);
    void SetProgramIndicator(int program);
    void SetHeater(boolean state);
    void SetTemperature(int level);
  private:
    Centipede centipede;
    void SetKeySelect(int value);
    void SetGroup(int group);
    void SetData(int data);
    void Strobe();
};

#endif



