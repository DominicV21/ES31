#include <Wire.h>
#include <Centipede.h>

#include "IBuzzer.h"
#include "ICoin.h"
#include "ILock.h"
#include "IMotor.h"
#include "IProgram.h"
#include "ISoap.h"
#include "ITemperature.h"
#include "IWater.h"

#include "HardwareControl.h"
#include "CoinWallet.h"
#include "ProgramSelect.h"
#include "ProgramSettings.h"
#include "ProgramExecutor.h"

static HardwareControl * mControl;
static IBuzzer * mBuzzer;
static ICoin * mCoin;
static IMotor * mMotor;
static ILock * mLock;
static IProgram * mProgram;
static ISoap * mSoap;
static ITemperature * mTemperature;
static IWater * mWater;
static CoinWallet * mCoinWallet;
static ProgramSelect * mProgramSelect;
static ProgramSettings * mProgramSettings;
static ProgramExecutor * mProgramExecutor;

void setup()
{
  mControl = new HardwareControl();
  Serial.begin(9600);
}

void loop()
{
  if(mControl->GetSoap1())
  {
    mControl->SetSoap1(1);
  }
  else
  {
    mControl->SetSoap1(0);
  }
  
  if(mControl->GetSoap2())
  {
    mControl->SetSoap2(1);
  }
  else
  {
    mControl->SetSoap2(0);
  }
  
  mControl->SetTemperature(3);
}
