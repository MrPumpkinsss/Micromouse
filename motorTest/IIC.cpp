#ifndef IIC_CPP
#define IIC_CPP

#include "IIC.h"


uint8_t data[20]; //用于暂存 I2C 读取的数据
bool WireWriteByte(uint8_t val)
{
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(val);
  if( Wire.endTransmission() != 0 ) {
    return false;
  }
    return true;
}
//向地址中写入数据（reg：地址 val：数据内容 len：数据长度）
bool WireWriteDataArray( uint8_t reg,uint8_t *val,unsigned int len)
{
  unsigned int i;
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(reg);
  for(i = 0; i < len; i++) {
    Wire.write(val[i]);
  }
  if( Wire.endTransmission() != 0 ) {
    return false;
  }
  return true;
}
//读取地址中的数据（reg：地址 val：数据内容）
bool WireReadDataByte(uint8_t reg, uint8_t &val)
{
  if (!WireWriteByte(reg)) {
    return false;
  }
  Wire.requestFrom(I2C_ADDR, 1);
  while (Wire.available()) {
    val = Wire.read();
  }
  return true;
}
//读取地址中指定长度的数据（reg：地址 val：数据内容 len：数据长度）
int WireReadDataArray( uint8_t reg, uint8_t *val, unsigned int len)
{
  unsigned char i = 0;
  /* Indicate which register we want to read from */
  if (!WireWriteByte(reg)) {
    return -1;
  }
  /* Read block data */
  Wire.requestFrom(I2C_ADDR, len);
  while (Wire.available()) {
    if (i >= len) {
      return -1;
    }
    val[i] = Wire.read();
    i++;
  }
  return i;
}
int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}
void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}

#endif