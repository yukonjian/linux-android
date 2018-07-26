1. gpio子系统的核心文件
/driver/gpio/gpiolib.c
参考文件：/Documentation/gpio.txt

2. gpio的使用
1) 判断gpio num是否可以使用
static inline bool gpio_is_valid(int number)
{
	return number >= 0 && number < ARCH_NR_GPIOS;
}

2) gpio请求
int gpio_request(unsigned gpio, const char *label)
return: 成功：0

3) 设置gpio的输入还是输出
int gpio_direction_input(unsigned gpio)
gpiod_direction_output(struct gpio_desc *desc)
return：成功：0

4) 得到gpio的值和设置gpio的值
int gpio_get_value(unsigned int gpio)
void gpio_set_value(unsigned int gpio, int value)

5) 释放申请的gpio引脚
void gpio_free(unsigned gpio)
