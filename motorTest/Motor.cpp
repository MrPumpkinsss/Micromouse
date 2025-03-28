/***************
* Motor Class Implementation
*
* Sharang Phadke
* Sameer Chauhan
***************/

#ifndef MOTOR_CPP
#define MOTOR_CPP

#include "IIC.h"
#include "Motor.h"


int m_num = 2;
int8_t p1[3]={0,0,0};

Motor::Motor(int pin1, int pin2, int enablePin){
  this->enablePin = enablePin;
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->state = -1;
  this->power = 0;
  if((pin1 == 7) | (pin2 == 8)){
    m_num = 1;
  }
  else if((pin1 = 4) | (pin2 == 5)){
    m_num = 0;
  }
  else{
    m_num = 2;
  }
}

void Motor::setState(int state, int power){
  this->power = power;
  this->state = state;
  switch (state){
    case 0:  //lock
      p1[m_num] = 0;
      WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,p1,3);
      break;
    case 1:  //forward
      p1[m_num] = power;
      WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,p1,3);
      break;
    case 2:  //backward
      p1[m_num] = -power;
      WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,p1,3);
      break;
  }
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR,p1,3);
  m_num = 2;
}

#endif
