#ifndef __E2PROM_24C08_H__
#define __E2PROM_24C08_H__

#include "i2c_master_sim.h"

typedef struct address_to_ctrl_byte
{
	uint8_t ctrl_byte;
	uint8_t word_addr;
}addr_ctrl_byte_struct;

void i2c_byte_write(uint8_t ctrl_byte,uint8_t word_addr,uint8_t data_byte);
void i2c_page_write(uint8_t ctrl_byte,uint8_t word_addr,uint8_t *source_data_addr,uint8_t data_len);
void i2c_write_within_block(uint8_t ctrl_byte,uint8_t word_addr,uint8_t *source_data_addr,uint16_t data_len);
uint8_t i2c_current_addr_read(uint8_t ctrl_byte);
uint8_t i2c_rand_read(uint8_t ctrl_byte,uint8_t word_addr);
void i2c_sequential_read(uint8_t ctrl_byte,uint8_t word_addr,uint16_t data_len,uint8_t *data_addr_in_master_mem);

addr_ctrl_byte_struct get_eigenbytes(uint16_t address_in_chip);

void i2c_write_within_chip(uint16_t address_in_chip,uint8_t *source_data_addr,uint16_t data_len);
void i2c_read_within_chip(uint16_t address_in_chip,uint8_t *data_addr_in_master_mem,uint16_t data_len);

#endif