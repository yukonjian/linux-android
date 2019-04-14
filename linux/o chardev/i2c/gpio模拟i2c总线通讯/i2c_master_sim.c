#include "i2c_master_sim.h"

#define SDA IO_CONFIG_PB0
#define SCL IO_CONFIG_PB1

//TX1 IO_CONFIG_PB0 SDA DATA7
//RX1 IO_CONFIG_PB1 SCL DATA6
void i2c_init(void)
{
	io_func_config(SDA, IO_FUNC_GPIO);	// choose IO_CONFIG_PB0 as GPIO
	io_func_config(SCL, IO_FUNC_GPIO);	// choose IO_CONFIG_PB1 as GPIO
	io_input(SDA);		// SDA input
	io_input(SCL);		// SCL input
	delay_us(20);
}

void i2c_start(void)
{
	io_output(SDA);		// SDA output
	io_output(SCL);		// SCL output
	io_set_high(SDA);	// SDA=1
	io_set_high(SCL);	// SCL=1
	delay_us(5);
	io_set_low(SDA);	// SDA=0
	delay_us(5);
}

void i2c_stop(void)
{
	io_output(SDA);		// set SDA as input
	//io_output(SCL);		// set SCL as input
	
	if (io_get(SCL) == 1)
		io_set_low(SCL);	// SDA=0
	if (io_get(SDA) == 1)
		io_set_low(SDA);	// SDA=0
	delay_us(5);
	io_set_high(SCL);	// SCL=1
	delay_us(5);
	io_set_high(SDA);	// SDA=1
	delay_us(5);
	// release SDA and SCL
	io_input(SDA);		// set SDA as input
	io_input(SCL);		// set SCL as input
}

uint8_t i2c_read_ack(void)
{
	uint8_t ack;
	io_input(SDA);		// SDA input
	io_set_high(SCL);	// SCL=1
	ack = io_get(SDA);
	delay_us(5);
	io_set_low(SCL);	// SCL=0
	delay_us(5);
	return ack;
}

void i2c_send_ack(void)
{
	io_output(SDA);
	io_set_low(SCL);	// SCL=0
	io_set_low(SDA);	// SDA=0
	delay_us(5);
	io_set_high(SCL);	// SCL=1
	delay_us(5);
	// TAKE CAREFULLY！！！These two orders below must be included
	// to pull down the SCL for the following opreations.
	io_set_low(SCL);	// SCL=0
	delay_us(5);
}

void i2c_send_nack(void)
{
	io_output(SDA);
	io_set_low(SCL);	// SCL=0
	io_set_high(SDA);	// SDA=1
	delay_us(5);
	io_set_high(SCL);	// SCL=1
	delay_us(5);
	io_set_low(SCL);	// SCL=0
	delay_us(5);
}


uint8_t i2c_ack_check(uint8_t ctrl_byte)
{
	i2c_start();
	i2c_write_single_byte(ctrl_byte);
	if(i2c_read_ack() == 0)
	{
		//sl_printf("i2c_read_ack() == 0.\n");
		// time delay here is not necessary, just to make waveforms more readable
		delay_us(30);
		//i2c_stop();
		io_input(SDA);		// set SDA as input
		io_input(SCL);		// set SCL as input
		return 0;
	}
	else
	{
		//sl_printf("i2c_read_ack() == 1.\n");
		// time delay here is to save computing resource
		delay_us(100);
		//io_input(SDA);		// set SDA as input
		//io_input(SCL);		// set SCL as input
		return 1;
	}
}

void i2c_write_single_byte(uint8_t i2c_buff)
{
	uint8_t i=8;
	io_output(SDA);		// SDA output
	io_output(SCL);		// SCL output
	while (i--)
	{
		io_set_low(SCL);			// SCL=0
		delay_us(5);
		if(i2c_buff & 0x80)					// MSB(i2c_buff)==1
			io_set_high(SDA);		// SDA=1
		else
			io_set_low(SDA);		// SDA=0
		io_set_high(SCL);			// SCL=1
		delay_us(5);
		i2c_buff = i2c_buff<<1;							// move to the next MSB(from MSB to LEB)
	}
	// After transfer, release the SCL line
	io_set_low(SCL);				// SCL=0
	delay_us(5);
}

uint8_t i2c_read_single_byte(void)
{
	uint8_t i=8;
	uint8_t i2c_buff = 0x0;
	// 每次read，最开始总是高电平，即使MSB is low 也要先高再低(在SCL=0期间有一个小凸起)
	// Is that because of setting SDA as input, making it HIGH at the very beginning? Maybe so.
	delay_us(5);
	io_input(SDA);				// SDA input
	delay_us(5);
	while (i--)
	{
		i2c_buff = i2c_buff<<1;
		io_set_high(SCL);		// SCL=1
		//
		if(io_get(SDA)==1)
			i2c_buff |= 0x01;							// Write 1 to LSB of i2c_buff
		else
			i2c_buff &= 0xFE;							// Write 0 to LSB of i2c_buff
		delay_us(5);
		io_set_low(SCL);		// SCL=0
		delay_us(5);
		//i2c_buff = i2c_buff<<1;						// move to the next MSB(from MSB to LEB)
	}
	//sl_printf("i2cbuf=%d\n", i2c_buff);
	return i2c_buff;
}