/***************
*  Motor Test
*
*  Sharang Phadke
*  Sameer Chauhan
***************/

#include "Motor.h"
#include "IIC.h"

int32_t EncodeTotal[2];//用于暂存电机累积转动量的值，正转递增，反转递减
int loopCount = 0;
int Forward = 0;

extern int8_t p1[2];

void slowToStop(Motor right, Motor left, int time){
  int i;
  float rightDecrement = ((float)right.power)/time;
  float leftDecrement = ((float)left.power)/time;
  float rightPowerFloat = right.power;
  float leftPowerFloat = left.power;

  for(i = 0; i < time; i++){
    rightPowerFloat -= rightDecrement;
    leftPowerFloat -= leftDecrement;
    right.power = (int)rightPowerFloat;
    left.power = (int)leftPowerFloat;

    analogWrite(right.enablePin, right.power);
    analogWrite(left.enablePin, left.power);
    delay(1);
  }
}

void timedMove(Motor right, Motor left, int time){
  analogWrite(right.enablePin, right.power);
  analogWrite(left.enablePin, left.power);
  delay(time-1000);
  slowToStop(right, left, 1000);
  digitalWrite(right.enablePin, LOW);
  digitalWrite(left.enablePin, LOW);
}


Motor rightMotor(7, 8, 9);
Motor leftMotor(4, 5, 6);


void setup(){
  uint8_t MotorType = MOTOR_TYPE_TT; //设定电机类型
  uint8_t MotorEncoderPolarity = 1;
  //rightMotor.setState(0, 0);
  //leftMotor.setState(0, 0);
  Serial.begin(9600); //初始化串口，波特率设置为 9600
  printf_begin(); //printf 输出初始化
  Wire.begin(); //初始化 I2C，以 Ardunio UNO 为例 I2C 口为：A4(SCL)、A5(CLK)
  delay(200);
  WireWriteDataArray(MOTOR_TYPE_ADDR,&MotorType,1);//在电机类型地址中写入电机类型编号
  delay(5);
  WireWriteDataArray(MOTOR_ENCODER_POLARITY_ADDR,&MotorEncoderPolarity,1);
}


void loop(){
//  rightMotor.setState(1, 150);
//  leftMotor.setState(1, 200);
//  timedMove(rightMotor, leftMotor, 2000);
  //int i = 0;
  //for(i=0;i<=50;i++){
  //WireReadDataArray(MOTOR_ENCODER_TOTAL_ADDR,(uint8_t*)EncodeTotal,16);// 读取机累积转动量
  /*打印 4 个电机的累计转动量*/
  //printf("Encode1 = %ld Encode2 = %ld %d %d \n\r ", EncodeTotal[0], EncodeTotal[1], p1[0], p1[1]);
  rightMotor.setState(1, 30);
  leftMotor.setState(1, 40);

  //delay(50);
  //}
  WireReadDataArray(MOTOR_ENCODER_TOTAL_ADDR,(uint8_t*)EncodeTotal,16);// 读取机累积转动量
  /*打印 4 个电机的累计转动量*/
  printf("Encode1 = %ld Encode2 = %ld %d %d \n\r ", EncodeTotal[0], EncodeTotal[1], p1[0], p1[1]);
//  timedMove(rightMotor, leftMotor, 3000);
  //rightMotor.setState(0,0);
  //leftMotor.setState(0,0);
  //delay(5000);
}
