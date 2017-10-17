#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

#include "hw_delay.h"
#include "hw_gpio.h"
#include "hw_i2c.h"

static void OLED_DelayMs(unsigned int ms);
static void OLED_WriteCmd(unsigned char cmd);
static void OLED_WriteData(unsigned char dat);
static void OLED_Fill(unsigned char FillData);
static void OLED_SetPos(unsigned char x, unsigned char y);
static int IIC_Init(void);

void OLED_Init(void)
{
	IIC_Init();

	OLED_DelayMs(500);

	OLED_WriteCmd(0xAE);
	OLED_WriteCmd(0x00);
	OLED_WriteCmd(0x10);
	OLED_WriteCmd(0x40);
	OLED_WriteCmd(0x81);
	OLED_WriteCmd(0xCF);
	OLED_WriteCmd(0xA1);
	OLED_WriteCmd(0xC8);
	OLED_WriteCmd(0xA6);
	OLED_WriteCmd(0xA8);
	OLED_WriteCmd(0x3F);
	OLED_WriteCmd(0xD3);
	OLED_WriteCmd(0x00);
	OLED_WriteCmd(0xD5);
	OLED_WriteCmd(0x80);
	OLED_WriteCmd(0xD9);
	OLED_WriteCmd(0xF1);
	OLED_WriteCmd(0xDA);
	OLED_WriteCmd(0x12);
	OLED_WriteCmd(0xDB);
	OLED_WriteCmd(0x40);
	OLED_WriteCmd(0x20);
	OLED_WriteCmd(0x02);
	OLED_WriteCmd(0x8D);
	OLED_WriteCmd(0x14);
	OLED_WriteCmd(0xA4);
	OLED_WriteCmd(0xA6);
	OLED_WriteCmd(0xAF);
	OLED_Fill(0x00);
	OLED_SetPos(0,0);
}

static int IIC_Init(void)
{
	volatile unsigned int* bcm_peripherals_base = (volatile unsigned int *)ioremap(0x3f000000, 0x01000000);

	//delay init
	bcm_st_init(bcm_peripherals_base);

	//gpio init 
	bcm_gpio_init(bcm_peripherals_base);
	bcm_gpio_fsel(RPI_GPIO_02, BCM_GPIO_FSEL_ALT1);
	bcm_gpio_fsel(RPI_GPIO_03, BCM_GPIO_FSEL_ALT1);

	//i2c init
	bcm_i2c_init(bcm_peripherals_base,BCM_BSC1);
	bcm_i2c_ReplaceBSC(BCM_BSC1);
	bcm_i2c_setSlaveAddress(0x078);
}

static void OLED_DelayMs(unsigned int ms)
{
	bcm_st_delay_ms(ms);
}

static void OLED_WriteCmd(unsigned char cmd)
{
	/*
	IIC_Start();
	IIC_Send_Byte(0x78);
	IIC_Send_Byte(0x00);
	IIC_Send_Byte(cmd);
	IIC_Stop();
	*/
	unsigned char buf[2];

	buf[0] = 0x00;
	buf[1] = cmd;

	bcm_i2c_write(buf,2);
}

static void OLED_WriteData(unsigned char dat)
{
	/*
	IIC_Start();
	IIC_Send_Byte(0x78);
	IIC_Send_Byte(0x40);
	IIC_Send_Byte(dat);
	IIC_Stop();
	*/
	unsigned char buf[2];

	buf[0] = 0x40;
	buf[1] = dat;

	bcm_i2c_write(buf,2);
}

static void OLED_Fill(unsigned char FillData)
{
	unsigned char m,n;
	for(m=0; m<8; m++)
	{
		OLED_WriteCmd(0xb0+m);		//page0-page1
		OLED_WriteCmd(0x01);		//low column start address
		OLED_WriteCmd(0x10);		//high column start address
		for(n=0; n<128; n++)
		{
			OLED_WriteData(FillData);
		}
	}
}

static void OLED_SetPos(unsigned char x, unsigned char y)
{ 
	OLED_WriteCmd(0xb0+y);
	OLED_WriteCmd(((x&0xf0)>>4)|0x10);
	OLED_WriteCmd((x&0x0f)|0x01);
}


void OLED_StringShow(unsigned char x, unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_SetPos(x,y);
		for(i=0;i<8;i++)
		OLED_WriteData(F8X16[c*16+i]);
		OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WriteData(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}
