/***************
* Motor Class Declaration
*
* Sharang Phadke
* Sameer Chauhan
***************/

#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"


class Motor {

public:

  Motor(int pin1, int pin2, int enablePin);
  void setState(int state, int power);

  int enablePin;
  int pin1;
  int pin2;
  int power;
};

#endif
