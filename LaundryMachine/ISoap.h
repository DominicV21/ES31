#ifndef ISOAP_H
#define ISOAP_H

class ISoap
{
public:
  // Inputs
  virtual boolean GetSoap1() = 0;
  virtual boolean GetSoap2() = 0;
  // Outputs
  virtual void SetSoap1(int level) = 0;
  virtual void SetSoap2(int level) = 0;
};

#endif


