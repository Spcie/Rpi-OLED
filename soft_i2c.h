#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H

typedef struct I2cGpioOps
{
    void (*I2C_SDA_Set)(unsigned int lev);
    unsigned int (*I2C_SDA_read)(void);
    void (*I2C_SCL_set)(unsigned int lev);
    void (*delay_us)(unsigned int);
}I2cGpioOps;


void soft_i2c_init(I2cGpioOps FucTab)；
void soft_i2c_sendByte(char byt);
char soft_i2c_readByte(unsigned char ack)；
#endif
