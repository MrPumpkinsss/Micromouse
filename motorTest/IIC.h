#ifndef IIC_H
#define IIC_H

#include "Arduino.h"
#include <Wire.h>

#define I2C_ADDR 0x34//I2C 地址
#define ADC_BAT_ADDR 0 //电压地址
#define MOTOR_TYPE_ADDR 20 //编码电机类型设置
#define MOTOR_ENCODER_POLARITY_ADDR 21 //设置编码方向极性，//如果发现电机转速根本不受控制，要么最快速度转动，要么停止。可以将此地址的值重新设置一下
//范围 0 或 1，默认 0
#define MOTOR_FIXED_PWM_ADDR 31 //固定 PWM 控制，属于开环控制
//#define SERVOS_ADDR_CMD 40
#define MOTOR_FIXED_SPEED_ADDR 51 //固定转速控制，属于闭环控制
#define MOTOR_ENCODER_TOTAL_ADDR 60 //4 个编码电机各自的总脉冲值
//如果已知电机每转一圈的脉冲数为 U，又已知轮子的直径 D，那么就可以通过脉冲计数的方式得知每个轮子行进的距离
//比如读到电机 1 的脉冲总数为 P，那么行进的距离为(P/U) * (3.14159*D)
//对于不同的电机可以自行测试每圈的脉冲数 U，可以手动旋转 10 圈读出脉冲数，然后取平均值得出
//电机类型具体值
#define MOTOR_TYPE_WITHOUT_ENCODER 0 //无编码器的电机,磁环每转是44个脉冲减速比:90 默认
#define MOTOR_TYPE_TT 1 //TT 编码电机
#define MOTOR_TYPE_N20 2 //N20 编码电机
#define MOTOR_TYPE_JGB37_520_12V_110RPM 3 //磁环每转是44 个脉冲减速比:90默认



bool WireWriteByte(uint8_t val);
bool WireWriteDataArray( uint8_t reg,uint8_t *val,unsigned int len);
//读取地址中的数据（reg：地址 val：数据内容）
bool WireReadDataByte(uint8_t reg, uint8_t &val);
//读取地址中指定长度的数据（reg：地址 val：数据内容 len：数据长度）
int WireReadDataArray( uint8_t reg, uint8_t *val, unsigned int len);
int serial_putc( char c, struct __file * );
void printf_begin(void);

#endif