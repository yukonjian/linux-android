#include "stdlib.h"
#include "math.h"
#include "e2prom_24C08.h"
#include "i2c_master_sim.h"

#define SDA IO_CONFIG_PB0
#define SCL IO_CONFIG_PB1

addr_ctrl_byte_struct get_eigenbytes(uint16_t address_in_chip)
{
	addr_ctrl_byte_struct cbs;
	if((address_in_chip<0x00) || (address_in_chip>0x3FF))
	{
		printf("Cross-border error! The range of address_in_chip is 0x000-0x3FF.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		if((address_in_chip>=0x00) && (address_in_chip<0x100))
		{
			cbs.ctrl_byte  = 0xA0;
			cbs.word_addr  = address_in_chip;
		}
		else if((address_in_chip>=0x100) && (address_in_chip<0x200))
		{
			cbs.ctrl_byte  = 0xA2;
			cbs.word_addr  = address_in_chip%0x100;
		}
		else if((address_in_chip>=0x200) && (address_in_chip<0x300))
		{
			cbs.ctrl_byte  = 0xA4;
			cbs.word_addr  = address_in_chip%0x200;
		}
		else
		{
			cbs.ctrl_byte  = 0xA6;
			cbs.word_addr  = address_in_chip%0x300;
		}
	}
	return cbs;
}

// write one byte to e2prom
void i2c_byte_write(uint8_t ctrl_byte,uint8_t word_addr,uint8_t data_byte)
{
	i2c_start();
	i2c_write_single_byte(ctrl_byte);
	if(i2c_read_ack() == 0)
		i2c_write_single_byte(word_addr);
	else 
		return;
	if(i2c_read_ack() == 0)
		i2c_write_single_byte(data_byte);
	else
		return;
	if(i2c_read_ack() == 0)
		i2c_stop();
	else
		return;
}

// write bytes to e2prom (page write)
void i2c_page_write(uint8_t ctrl_byte,uint8_t word_addr,uint8_t *source_data_addr,uint8_t data_len)
{
	uint8_t i;
	if (data_len<=0)
	{
		printf("i2c_page_write: data_len should be a positive number.\n");
		return;
	}
	else
	{
		i2c_start();
		i2c_write_single_byte(ctrl_byte);
		if(i2c_read_ack() == 0)
			i2c_write_single_byte(word_addr);
		else 
			return;
		for(i=0;i<data_len;i++)
		{
			if(i2c_read_ack() == 0)
				i2c_write_single_byte(*(source_data_addr+i));
			else
				return;
		}
		if(i2c_read_ack() == 0)
			i2c_stop();
		else
			return;
	}
	printf("i2c_page_write finished.\n");
}

// read current address
uint8_t i2c_current_addr_read(uint8_t ctrl_byte)
{
	uint8_t data;
	i2c_start();
	i2c_write_single_byte(ctrl_byte);
	if(i2c_read_ack() == 0)
	{
		data = i2c_read_single_byte();
		i2c_send_nack();
		i2c_stop();
		return data;
	}
	else 
		return 0;
}

// read one byte from eeprom
uint8_t i2c_rand_read(uint8_t ctrl_byte,uint8_t word_addr)
{
	uint8_t data;
	i2c_start();
	i2c_write_single_byte(ctrl_byte);
	
	if(i2c_read_ack() == 0)
		i2c_write_single_byte(word_addr);
	else 
		return 0;
	
	if(i2c_read_ack() == 0)
		i2c_start();
	else 
		return 0;
	
	i2c_write_single_byte((ctrl_byte+1));
	
	if(i2c_read_ack() == 0)
	{
		data = i2c_read_single_byte();
		i2c_send_nack();
		i2c_stop();
		return data;
	}
	else 
		return 0;
}

// read sequential bytes from eeprom 
// it is the ADDRESS that is transferred, but not DATA!
//uint32_t i2c_sequential_read(uint8_t ctrl_byte,uint8_t word_addr,uint16_t data_num)
void i2c_sequential_read(uint8_t ctrl_byte,uint8_t word_addr,uint16_t data_len,uint8_t *data_addr_in_master_mem)
{
	uint16_t i=0;
	
	if(data_len<=0)
	{
		printf("i2c_sequential_read: data_len should be a positive number.\n");
		return;
	}
	else
	{
		i2c_start();
		i2c_write_single_byte(ctrl_byte);
		
		if(i2c_read_ack() == 0)
			i2c_write_single_byte(word_addr);
		else 
			return;
		
		if(i2c_read_ack() == 0)
			i2c_start();
		else 
			return;
		
		i2c_write_single_byte((ctrl_byte+0x01));
		
		if(i2c_read_ack() == 0)
			*data_addr_in_master_mem = i2c_read_single_byte();
		else 
			return;
		
		for(i=1;i<data_len;i++)
		{
			i2c_send_ack();		// master send ACK
			*(data_addr_in_master_mem + i) = i2c_read_single_byte();
		}
		
		i2c_send_nack();		// master send NACK
		i2c_stop();
	}
	printf("i2c_sequential_read finished.\n");
}

// memory_write within one single block
void i2c_write_within_block(uint8_t ctrl_byte,uint8_t word_addr,uint8_t *source_data_addr,uint16_t data_len)
{
	uint8_t page_size = 0x10;
	uint16_t bolck_size = 0x100;
	uint8_t extra_page = 0;
	uint8_t i = 0;
	uint8_t page_offset = word_addr % page_size;
	uint8_t len_left = page_size - page_offset;
	
	// beyond the scope of the current block
	if( (word_addr + data_len) > bolck_size )
	{
		printf("(B1)i2c_write_within_block:beyond the scope of the current block, JUST RETURN.");
		return;
	}
	// within the current block
	else
	{
		if(data_len <= len_left)
		{
			printf("(B2)i2c_write_within_block:within the current page.\n");
			i2c_page_write(ctrl_byte,word_addr,source_data_addr,data_len); // pointer as function parameter?
			while(i2c_ack_check(ctrl_byte));
		}
		else
		{
			printf("(B3)i2c_write_within_block:within the current block but beyond the current page.\n");
			if( (data_len - len_left)%page_size != 0 )
				extra_page = floor( (data_len - len_left)/(float)page_size+1 );
			else
				extra_page = (data_len - len_left)/(float)page_size;
			
			printf("extra_page = %d.\n data_len = %d.\n len_left = %d.\n",extra_page,data_len,len_left);
			// first, write the current page
			i2c_page_write(ctrl_byte,word_addr,source_data_addr,len_left);
			while(i2c_ack_check(ctrl_byte));
			// then, write the following complete page except the last maybe-incomplete page
			for (i=1;i<extra_page;i++)
			{
				i2c_page_write(ctrl_byte,(word_addr+len_left+(i-1)*page_size),(source_data_addr+len_left+(i-1)*page_size),page_size);
				while(i2c_ack_check(ctrl_byte));
			}
			// finally, write the last maybe-incomplete page
			i2c_page_write(ctrl_byte,(word_addr+len_left+(extra_page-1)*page_size),(source_data_addr+len_left+(extra_page-1)*page_size),
			(data_len-len_left-(extra_page-1)*page_size));
			while(i2c_ack_check(ctrl_byte));
		}
	}
	printf("i2c_write_within_block finished.\n");
}

/******************** the following are 2 highest API:Write/Read in chip********************/

// memory_write within one 24c08 Chip
void i2c_write_within_chip(uint16_t address_in_chip,uint8_t *source_data_addr,uint16_t data_len)
{
	uint16_t block_size = 0x100;
	uint8_t extra_block = 0;
	uint8_t i = 0;
	
	addr_ctrl_byte_struct Scb;
	Scb = get_eigenbytes(address_in_chip);
	uint8_t ctrl_byte = Scb.ctrl_byte;
	uint8_t word_addr = Scb.word_addr;
	uint8_t left_block_num = 4 - ((ctrl_byte & 0x06) >> 1);
	uint16_t total_mem_left = 1024-256*(4-left_block_num)-word_addr;
	uint16_t current_block_mem_left = block_size-word_addr;
	
	// do not beyond current block
	if ( (word_addr+data_len) <= block_size )
	{
		printf("(C1)i2c_write_within_chip:do not beyond current block.\n");
		i2c_write_within_block(ctrl_byte,word_addr,source_data_addr,data_len);
	}
	// the chip itself is not large enough
	// just write the chip full and abandon the left part
	else if ( data_len > total_mem_left )
	{	
		printf("(C2)i2c_write_within_chip:the chip itself is not large enough.\n");
		data_len = total_mem_left;
		
		if( (data_len-current_block_mem_left)%block_size != 0 )
			extra_block = floor((data_len-current_block_mem_left)/(float)block_size + 1);
		else
			extra_block = (data_len-current_block_mem_left)/(float)block_size;
		
		// first, write the current block
		i2c_write_within_block(ctrl_byte,word_addr,source_data_addr,current_block_mem_left);
		// just write the chip full and abandon the left part
		for (i=1;i <= extra_block;i++)
		{
			i2c_write_within_block(ctrl_byte+0x02*i,0x00,source_data_addr+current_block_mem_left+(i-1)*block_size,block_size);
		}
	}
	// occupy more than one block of memory but not beyond chip's memory range
	else
	{
		printf("(C3)i2c_write_within_chip:occupy more than one block of memory but not beyond chip's memory range.\n");
		
		// judge whether extra_block is intergals or float
		if( (data_len-current_block_mem_left)%block_size != 0 )
			extra_block = floor((data_len-current_block_mem_left)/(float)block_size + 1);
		else
			extra_block = (data_len-current_block_mem_left)/(float)block_size;
		
		printf("extra_block = %d.\n",extra_block);
		// first, write the current block
		i2c_write_within_block(ctrl_byte,word_addr,source_data_addr,current_block_mem_left);
		// then, write the following complete block except the last maybe-incomplete block
		for (i=1;i<extra_block;i++)
		{
			i2c_write_within_block(ctrl_byte+0x02*i,0x00,source_data_addr+current_block_mem_left+(i-1)*block_size,block_size);
		}
		// finally, write the last maybe-incomplete block
		i2c_write_within_block(ctrl_byte+0x02*extra_block,0x00,
			source_data_addr+current_block_mem_left+(extra_block-1)*block_size,
			data_len-current_block_mem_left-(extra_block-1)*block_size);
	}
	printf("i2c_write_within_chip finished.\n");
}

void i2c_read_within_chip(uint16_t address_in_chip,uint8_t *data_addr_in_master_mem,uint16_t data_len)
{
	uint16_t block_size = 0x100;
	uint8_t extra_block = 0;
	uint8_t i = 0;
	
	addr_ctrl_byte_struct Scb;
	Scb = get_eigenbytes(address_in_chip);
	uint8_t ctrl_byte = Scb.ctrl_byte;
	uint8_t word_addr = Scb.word_addr;
	uint8_t left_block_num = 4 - ((ctrl_byte & 0x06) >> 1);
	uint16_t total_mem_left = 1024-256*(4-left_block_num)-word_addr;
	uint16_t current_block_mem_left = block_size-word_addr;
	
	// donot beyond current block
	if ( (word_addr+data_len) <= block_size )
	{
		printf("(C1)i2c_read_within_chip:do not beyond current block.\n");
		i2c_sequential_read(ctrl_byte,word_addr,data_len,data_addr_in_master_mem);
	}
	// the chip itself is not large enough
	// just read the chip full and abandon the left part
	else if (data_len > total_mem_left)
	{
		printf("(C2)i2c_read_within_chip:the chip itself is not large enough.\n");
		data_len = total_mem_left;
		
		if( (data_len-current_block_mem_left)%block_size != 0 )
			extra_block = floor((data_len-current_block_mem_left)/(float)block_size + 1);
		else
			extra_block = (data_len-current_block_mem_left)/(float)block_size;
		
		printf("data_len=%d\n current_block_mem_left=%d\n extra_block=%d\n",data_len,current_block_mem_left,extra_block);
		
		// first, read the current block
		i2c_sequential_read(ctrl_byte,word_addr,current_block_mem_left,data_addr_in_master_mem);
		// then, read the following complete block till the end
		for (i = 1;i <= extra_block;i++)
		{
			i2c_sequential_read(ctrl_byte+0x02*i,0x00,block_size,(data_addr_in_master_mem+current_block_mem_left+(i-1)*block_size));
		}
	}
	// occupy more than one block of memory but not beyond chip's memory range
	else
	{
		printf("(C3)i2c_read_within_chip:occupy more than one block of memory but not beyond chip's memory range.\n");
		
		if( (data_len-current_block_mem_left)%block_size != 0 )
			extra_block = floor((data_len-current_block_mem_left)/(float)block_size + 1);
		else
			extra_block = (data_len-current_block_mem_left)/(float)block_size;
		
		printf("data_len=%d\n current_block_mem_left=%d\n extra_block=%d\n",data_len,current_block_mem_left,extra_block);
		// first, read the current block
		i2c_sequential_read(ctrl_byte,word_addr,current_block_mem_left,data_addr_in_master_mem);
		// then, read the following complete block till the end
		for (i = 1;i < extra_block;i++)
		{
			i2c_sequential_read(ctrl_byte+0x02*i,0x00,block_size,(data_addr_in_master_mem+current_block_mem_left+(i-1)*block_size));
		}
		// finally, write the last maybe-incomplete block
		i2c_sequential_read(ctrl_byte+0x02*extra_block,0x00,data_len-current_block_mem_left-(extra_block-1)*block_size,
		(data_addr_in_master_mem+current_block_mem_left+(extra_block-1)*block_size));
	}
	printf("i2c_read_within_chip finished.\n");
}
	