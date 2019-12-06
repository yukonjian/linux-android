#ifndef __I2C_MASTER_SIM_H__
#define __I2C_MASTER_SIM_H__

#include "silan_types.h"
#include "silan_printf.h"
#include "silan_config.h"
#include "silan_uart.h"
#include "silan_m0_cache.h"
#include "silan_iomux.h"
#include "silan_syscfg.h"
#include "silan_pmu.h"
#include "silan_gpio.h"
#include "silan_pic.h"
#include "silan_timer.h"
#include "silan_adc.h"
#include "silan_bootspi.h"
#include "silan_rtc.h"
#include "silan_sdram.h"
#include "silan_pwm.h"
#include "silan_version.h"

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_send_ack(void);
void i2c_send_nack(void);
uint8_t i2c_read_ack(void);
uint8_t i2c_ack_check(uint8_t ctrl_byte);
void i2c_write_single_byte(uint8_t i2cBuff);
uint8_t i2c_read_single_byte(void);

#endif