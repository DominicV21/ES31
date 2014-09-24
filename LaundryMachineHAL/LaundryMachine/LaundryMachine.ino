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

////Dit is manual test uncomment om te testen
//void loop()
//{
//  if(mControl->GetSoap1())
//  {
//    mControl->SetSoap1(1);
//  }
//  else
//  {
//    mControl->SetSoap1(0);
//  }
//  
//  if(mControl->GetSoap2())
//  {
//    mControl->SetSoap2(1);
//  }
//  else
//  {
//    mControl->SetSoap2(0);
//  }
//  
//  mControl->SetHeater(true);
//}


////Dit is de automatische test loop (uncomment en upload om de automatische test uit te voeren)
//void loop()
//{
//  int randomNr = random(0, 3);
//  int randomTemp = random(0, 2);
//  int randomOnOff = random (0, 2);
//  
//  if(randomNr == 0)
//  {
//    mControl->SetSoap1(randomOnOff);
//  }
//  else if (randomNr == 1)
//  {
//    mControl->SetSoap2(randomOnOff);
//  }
//  else if (randomNr == 2 && randomTemp == 1)
//  {
//    mControl->SetHeater(true);
//  }
//  else if (randomNr == 2 && randomTemp == 0)
//  {
//    mControl->SetHeater(false);
//  }
//  Serial.println(randomNr);
//  Serial.println(randomTemp);
//  Serial.println(randomOnOff);
//  delay(100);
//}
