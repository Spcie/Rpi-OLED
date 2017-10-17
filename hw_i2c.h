#ifndef __HW_I2C_H
#define __HW_I2C_H



#define BCM_BSC0_BASE		0x00205000
#define BCM_BSC1_BASE		0x00804000

#define BCM_BSC_C 			0x0000 // BSC Master Control 
#define BCM_BSC_S 			0x0004 // BSC Master Status 
#define BCM_BSC_DLEN		0x0008 // BSC Master Data Length 
#define BCM_BSC_A 			0x000c // BSC Master Slave Address 
#define BCM_BSC_FIFO		0x0010 // BSC Master Data FIFO 
#define BCM_BSC_DIV			0x0014 // BSC Master Clock Divider 
#define BCM_BSC_DEL			0x0018 // BSC Master Data Delay 
#define BCM_BSC_CLKT		0x001c // BSC Master Clock Stretch Timeout 

#define BCM_CORE_CLK_HZ		250000000  //Speed of the core clock core_clk  250 MHz 

//C Register
#define BCM_BSC_C_I2CEN		0x00008000 // I2C Enable
#define BCM_BSC_C_INTR 		0x00000400 // Interrupt on RX
#define BCM_BSC_C_INTT 		0x00000200 // Interrupt on TX
#define BCM_BSC_C_INTD 		0x00000100 // Interrupt on DONE
#define BCM_BSC_C_ST 		0x00000080 // Start transfer
#define BCM_BSC_C_CLEAR_1 	0x00000020 // Clear FIFO Clear
#define BCM_BSC_C_CLEAR_2 	0x00000010 // Clear FIFO Clear
#define BCM_BSC_C_READ 		0x00000001 // Read transfer

//S Register
#define BCM_BSC_S_CLKT 		0x00000200 /*!< Clock stretch timeout */
#define BCM_BSC_S_ERR 		0x00000100 /*!< ACK error */
#define BCM_BSC_S_RXF 		0x00000080 /*!< RXF FIFO full, 0 = FIFO is not full, 1 = FIFO is full */
#define BCM_BSC_S_TXE 		0x00000040 /*!< TXE FIFO full, 0 = FIFO is not full, 1 = FIFO is full */
#define BCM_BSC_S_RXD 		0x00000020 /*!< RXD FIFO contains data */
#define BCM_BSC_S_TXD 		0x00000010 /*!< TXD FIFO can accept data */
#define BCM_BSC_S_RXR 		0x00000008 /*!< RXR FIFO needs reading (full) */
#define BCM_BSC_S_TXW 		0x00000004 /*!< TXW FIFO needs writing (full) */
#define BCM_BSC_S_DONE 		0x00000002 /*!< Transfer DONE */
#define BCM_BSC_S_TA 		0x00000001 /*!< Transfer Active */

#define BCM_BSC_FIFO_DEPTH	16

typedef enum
{
    BCM_I2C_CLOCK_DIVIDER_2500   = 2500,      // 2500 = 10us = 100 kHz
    BCM_I2C_CLOCK_DIVIDER_626    = 626,       // 622 = 2.504us = 399.3610 kHz
    BCM_I2C_CLOCK_DIVIDER_150    = 150,       // 150 = 60ns = 1.666 MHz (default at reset)
    BCM_I2C_CLOCK_DIVIDER_148    = 148        // 148 = 59ns = 1.689 MHz
} bcmI2CClockDivider;

typedef enum
{
    BCM_I2C_REASON_OK   	     = 0x00,      // Success
    BCM_I2C_REASON_ERROR_NACK    = 0x01,      // Received a NACK
    BCM_I2C_REASON_ERROR_CLKT    = 0x02,      // Received Clock Stretch Timeout
    BCM_I2C_REASON_ERROR_DATA    = 0x04       // Not all data is sent / received
} bcmI2CReasonCodes;


typedef enum 
{
	BCM_BSC0 = 0X00,	
	BCM_BSC1 = 0X01,
	BCM_BSC_ALL = 0X02,   //without BSC2 
}bcmBSC;

int bcm_i2c_init(volatile unsigned int* peripherals_base, bcmBSC bsc_choice);
void bcm_i2c_uninit(bcmBSC bsc_choice);
int bcm_i2c_ReplaceBSC(bcmBSC bsc_choice);
void bcm_i2c_setSlaveAddress(unsigned char addr);
bcmI2CReasonCodes bcm_i2c_write(const char * buf, unsigned int len);
bcmI2CReasonCodes bcm_i2c_read(char * buf, unsigned int len);
#endif
