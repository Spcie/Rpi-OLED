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

volatile static unsigned int* bcm_SysTimer;

#define BCM_ST_BASE			0x3000

static unsigned int bcm_st_register_read(unsigned int RegOfst)
{
	unsigned int ret;
	volatile unsigned int* pAddr = bcm_SysTimer + RegOfst/4;

	__sync_synchronize();
	ret = *pAddr;
	__sync_synchronize();
	return ret;
}

static unsigned long long bcm_st_read(void)
{
	unsigned int high,low;
	unsigned long long st;

	high = bcm_st_register_read(BCM_ST_CHI);
	low = bcm_st_register_read(BCM_ST_CLO);
	st = bcm_st_register_read(BCM_ST_CHI);

	//Test for overflow
	if (st == high)
    {
        st <<= 32;
        st += low;
    }
    else
    {
        st <<= 32;
        st += bcm_st_register_read(BCM_ST_CLO);
    }

    return st;
}

int bcm_st_init(volatile unsigned int* peripherals_base)
{
	bcm_SysTimer = peripherals_base + BCM_ST_BASE/4;
	return 0;
}

//delay us without sleep 
void bcm_st_delay_us(unsigned long long us)
{
	unsigned long long start;
	unsigned long long compare;

	start = bcm_st_read();
	compare = start + us;

	while(bcm_st_read() < compare);
}

//delay ms without sleep
void bcm_st_delay_ms(unsigned int ms)
{
	unsigned long long start;
	unsigned long long compare;

	start = bcm_st_read();
	compare = start + ms*1000;

	while(bcm_st_read() < compare);
}

void bcm_st_uninit(void)
{
	bcm_SysTimer = 0x00000000;
}
