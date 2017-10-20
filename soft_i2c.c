
#include "soft_i2c.h"

static I2cGpioOps I2c_ops;

static void i2c_Start(void);
static void i2c_Stop(void);
static void i2c_waitAck(void);
static void i2c_Ack(void);
static void i2c_NAck(void);

static void i2c_Start(void)
{
    *(I2c_ops.I2C_SCL_set)(1);
    *(I2c_ops.I2C_SDA_Set)(1);
    *(I2c_ops.delay_us)(4);
    *(I2c_ops.I2C_SCL_set)(0);
    *(I2c_ops.delay_us)(4);
    *(I2c_ops.I2C_SCL_set)(0);
}
static void i2c_Stop(void)
{
    *(I2c_ops.I2C_SCL_set)(0);
    *(I2c_ops.I2C_SDA_Set)(0);
    *(I2c_ops.delay_us)(4);
    *(I2c_ops.I2C_SCL_set)(1);
    *(I2c_ops.delay_us)(4);
    *(I2c_ops.I2C_SCL_set)(1);
}
static void i2c_waitAck(void)
{
    unsigned char ucErrTime = 0;

    *(I2c_ops.I2C_SDA_Set)(1);
    *(I2c_ops.delay_us)(1);
    *(I2c_ops.I2C_SCL_set)(1);
    *(I2c_ops.delay_us)(1);

    while(*(I2c_ops.I2C_SDA_read)())
    {
        ucErrTime++;
        if (ucErrTime>250)
		{
			IIC_Stop();
			return 1;
        }
        *(I2c_ops.delay_us)(1);
    }
    *(I2c_ops.I2C_SCL_set)(0);
}

static void i2c_Ack(void)
{
    *(I2c_ops.I2C_SCL_set)(0);
    *(I2c_ops.I2C_SDA_Set)(0);
    *(I2c_ops.delay_us)(2);
    *(I2c_ops.I2C_SCL_set)(1);
    *(I2c_ops.delay_us)(2);
    *(I2c_ops.I2C_SCL_set)(0);
}

static void i2c_NAck(void)
{
    *(I2c_ops.I2C_SCL_set)(0);
    *(I2c_ops.I2C_SDA_Set)(1);
    *(I2c_ops.delay_us)(2);
    *(I2c_ops.I2C_SCL_set)(1);
    *(I2c_ops.delay_us)(2);
    *(I2c_ops.I2C_SCL_set)(0);
}


void soft_i2c_init(I2cGpioOps FucTab)
{
    I2c_ops.delay_us = FucTab.delay_us;
    I2c_ops.I2C_SCL_set = FucTab.I2C_SCL_set;
    I2c_ops.I2C_SDA_Set = FucTab.I2C_SDA_Set;
    I2c_ops.I2C_SDA_read = FucTab.I2C_SDA_read;
}

void soft_i2c_sendByte(char byt)
{
    unsigned char t;
    *(I2c_ops.I2C_SCL_set)(0);
    for(t = 0; t < 8; t++)
    {
        *(I2c_ops.I2C_SDA_Set)((byt & 0x80) >> 7);
        byt <<= 1;
        *(I2c_ops.delay_us)(2);
        *(I2c_ops.I2C_SCL_set)(1);
        *(I2c_ops.delay_us)(2);
        *(I2c_ops.I2C_SCL_set)(0);
        *(I2c_ops.delay_us)(2);
    }
    *(I2c_ops.I2C_SDA_Set)(1);
    *(I2c_ops.I2C_SCL_set)(1);
    *(I2c_ops.I2C_SCL_set)(0);

}

char soft_i2c_readByte(unsigned char ack)
{
    unsigned char i;
    char receive = 0;

    for(i = 0; i < 8; i++)
    {
        *(I2c_ops.I2C_SCL_set)(0);
        *(I2c_ops.delay_us)(2);
        *(I2c_ops.I2C_SCL_set)(1);
        receive <<= 1;
        if (*(I2c_ops.I2C_SDA_read)()) receive++;
        *(I2c_ops.delay_us)(1);
    }
    if(!ack)
    {
        i2c_NAck();
    }
    else
    {
        i2c_Ack();
    }
}
