#ifndef __HW_DELAY_H
#define __HW_DELAY_H

#define BCM_ST_CS 			0x0000 //System Timer Control/Status
#define BCM_ST_CLO 			0x0004 // System Timer Counter Lower 32 bits
#define BCM_ST_CHI 			0x0008 // System Timer Counter Upper 32 bits

int bcm_st_init(volatile unsigned int* peripherals_base);
void bcm_st_delay_us(unsigned long long us);
void bcm_st_delay_ms(unsigned int ms);
void bcm_st_uninit(void);
#endif
