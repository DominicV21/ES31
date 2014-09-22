#ifndef ITEMPERATURE_H
#define ITEMPERATURE_H

class ITemperature
{
public:
  // Inputs
  virtual int GetTemperature() = 0;

  // Outputs
  virtual void SetHeater(boolean state) = 0;
  virtual void SetTemperature(int level) = 0;
};

#endif
