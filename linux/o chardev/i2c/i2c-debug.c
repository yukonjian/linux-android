1. /sys/bus/i2c/devices # ls
0-0034
1-005d
3-003c
i2c-0
i2c-1
i2c-2
i2c-3

2. root@t3-p1:/sys/bus/i2c/drivers # ls -l
drwxr-xr-x root     root              1970-01-01 08:04 axp20
drwxr-xr-x root     root              1970-01-01 08:04 axp22
drwxr-xr-x root     root              1970-01-01 08:04 dummy
drwxr-xr-x root     root              1970-01-01 08:00 gc2155
drwxr-xr-x root     root              1970-01-01 08:00 gt9xxnew_ts
drwxr-xr-x root     root              1970-01-01 08:04 ir-kbd-i2c

ASE
./drivers/i2c/busses/i2c-ralink.c:      release_mem_region(RALINK_I2C_BASE, 256);
./drivers/i2c/busses/i2c-ralink.c:      if (!request_mem_region(RALINK_I2C_BASE, resource_size(res), pdev->name)) {
./drivers/i2c/busses/i2c-ralink.h:#define RT2880_I2C_REG_BASE             (RALINK_I2C_BASE)
./drivers/char/i2c_drv.h:#define RT2880_I2C_REG_BASE            (RALINK_I2C_BASE)
./arch/mips/ralink/dev-i2c.c:   i2c_resources[0].start = RALINK_I2C_BASE;
./arch/mips/ralink/dev-i2c.c:   i2c_resources[0].end += RALINK_I2C_BASE + 256 - 1;
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xA0300900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xA0300900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xBE000900
./arch/mips/include/asm/mach-ralink/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xA0300900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xA0300900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xB0000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xB0000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xB0000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xB0000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xB0000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xB0000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xB0000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xBE000900
./arch/mips/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                        0xB0000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xA0300900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xA0300900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xBE000900
./arch/mips/include/uapi/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                   0xB0000900
./user_headers/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                     0xA0300900
./user_headers/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                     0xA0300900
./user_headers/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                     0xB0000900
./user_headers/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                     0xB0000900
./user_headers/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                     0xB0000900
./user_headers/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                     0xB0000900
./user_headers/include/asm/rt2880/rt_mmap.h:#define RALINK_I2C_BASE                     0xB0000900
