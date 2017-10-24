
#include "soft_i2c.h"
#include "hw_gpio.h"
#include "hw_delay.h"

static void i2c_sda_set(unsigned char lev);
static void i2c_scl_set(unsigned char lev);
static unsigned char i2c_sda_read(void);
static unsigned char i2c_waitAck(void);
static void i2c_Ack(void);
static void i2c_NAck(void);


static void i2c_sda_set(unsigned char lev)
{
    if(lev)
    {
        bcm_gpio_set(RPI_GPIO_02);
    }
    else
    {
        bcm_gpio_clr(RPI_GPIO_02);
    }
}
static void i2c_scl_set(unsigned char lev)
{
    if(lev)
    {
        bcm_gpio_set(RPI_GPIO_03);
    }
    else
    {
        bcm_gpio_clr(RPI_GPIO_03);
    }
}

static unsigned char i2c_sda_read(void)
{
    //wait
    return 0;
}

static unsigned char i2c_waitAck(void)
{
    unsigned char ucErrTime = 0;

    i2c_sda_set(1);
    soft_i2c_delay_us(1);
    i2c_scl_set(1);
    soft_i2c_delay_us(1);

    while(i2c_sda_read())
    {
        ucErrTime++;
        if (ucErrTime>250)
		{
			soft_i2c_Stop();
			return 1;
        }
        soft_i2c_delay_us(1);
    }
    i2c_scl_set(0);
    return 0;
}

static void i2c_Ack(void)
{
    i2c_scl_set(0);
    i2c_sda_set(0);
    soft_i2c_delay_us(2);
    i2c_scl_set(1);
    soft_i2c_delay_us(2);
    i2c_scl_set(0);
}

static void i2c_NAck(void)
{
    i2c_scl_set(0);
    i2c_sda_set(1);
    soft_i2c_delay_us(2);
    i2c_scl_set(1);
    soft_i2c_delay_us(2);
    i2c_scl_set(0);
}

void soft_i2c_delay_us(unsigned int us)
{
    bcm_st_delay_us(us);
}

void soft_i2c_delay_ms(unsigned int ms)
{
    bcm_st_delay_ms(ms);
}

void soft_i2c_Start(void)
{
    i2c_scl_set(1);
    i2c_sda_set(1);
    soft_i2c_delay_us(4);
    i2c_sda_set(0);
    soft_i2c_delay_us(4);
    i2c_scl_set(0);
}
void soft_i2c_Stop(void)
{
    i2c_scl_set(0);
    i2c_sda_set(0);
    soft_i2c_delay_us(4);
    i2c_scl_set(1);
    i2c_sda_set(1);
    soft_i2c_delay_us(4);
}

void soft_i2c_init(volatile unsigned int* peripherals_base)
{
    bcm_st_init(peripherals_base);
    bcm_gpio_init(peripherals_base);

    bcm_gpio_fsel(RPI_GPIO_02, BCM_GPIO_FSEL_OUTP);
    bcm_gpio_fsel(RPI_GPIO_03, BCM_GPIO_FSEL_OUTP);
}

void soft_i2c_sendByte(unsigned char byt)
{
    unsigned char t;
    i2c_scl_set(0);
    for(t = 0; t < 8; t++)
    {
        i2c_sda_set((byt & 0x80) >> 7);
        byt <<= 1;
        soft_i2c_delay_us(2);
        i2c_scl_set(1);
        soft_i2c_delay_us(2);
        i2c_scl_set(0);
        soft_i2c_delay_us(2);
    }
    i2c_sda_set(1);
    i2c_scl_set(1);
    i2c_scl_set(0);

}

char soft_i2c_readByte(unsigned char ack)
{
    unsigned char i;
    char receive = 0;

    for(i = 0; i < 8; i++)
    {
        i2c_scl_set(0);
        soft_i2c_delay_us(2);
        i2c_scl_set(1);
        receive <<= 1;
        if (i2c_sda_read()) receive++;
        soft_i2c_delay_us(1);
    }
    if(!ack)
    {
        i2c_NAck();
    }
    else
    {
        i2c_Ack();
    }
    return receive;
}
