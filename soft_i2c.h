#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H

void soft_i2c_Start(void);
void soft_i2c_Stop(void);
void soft_i2c_init(volatile unsigned int* peripherals_base);
void soft_i2c_sendByte(char byt);
char soft_i2c_readByte(unsigned char ack);

#endif
