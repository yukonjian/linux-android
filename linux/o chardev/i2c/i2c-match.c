i2c匹配
1.设备树匹配
device:
/{
109           i2c@138B0000 {
110                      #address-cells = <1>;
111                      #size-cells = <0>;
112                      samsung,i2c-sda-delay = <100>;
113                      samsung,i2c-max-bus-freq = <20000>;
114                      pinctrl-0 =<&i2c5_bus>;
115                      pinctrl-names="default";
116                      status="okay";
117                      mpu6050@68{
118                                 compatible="invensense,mpu6050";
119                                 reg=<0x68>;
120                      };
121           };

--109-->即我们SoC上的i2c控制器的地址
--117-->设备子节点，/表示板子，它的子节点node1表示SoC上的某个控制器，控制器中的子节点node2表示挂接在这个控制器上的设备(们)。68即是设备地址。
--118-->这个属性就是我们和驱动匹配的钥匙，一个字符都不能错
driver:
struct of_device_id mpu6050_dt_match[] = {
    {.compatible = "invensense,mpu6050"},
    {},
};
struct i2c_device_id mpu6050_dev_match[] = {};

struct i2c_driver mpu6050_driver = {
    .probe = mpu6050_probe,
    .remove = mpu6050_remove,
    .driver = {
        .owner = THIS_MODULE,
        .name = "mpu6050drv",
        .of_match_table = of_match_ptr(mpu6050_dt_match),
    },
    .id_table = mpu6050_dev_match,
};

2. static struct i2c_board_info at24cxx_info = {
	I2C_BOARD_INFO("at24c08", 0x50),
};

static int at24cxx_dev_init(void)
{
	struct i2c_adapter *i2c_adap;

	i2c_adap = i2c_get_adapter(0);
	at24cxx_client = i2c_new_device(i2c_adap, &at24cxx_info);
	i2c_put_adapter(i2c_adap);

	return 0;
}

3. i2c_register_board_info
4. i2c_new_probed_device
5. 4.从用户空间实例化一个器件：这个方法相当智能快速，如下输入指令，即可增加一个i2c设备，同时增加了对应的设备文件。
# echo eeprom 0x50 > /sys/bus/i2c/devices/i2c-3/new_device

Linux的官方文档《linux-3.4.2\Documentation\i2c\instantiating-devices》

6. /drivers/i2c/i2c-core.c
static int i2c_device_match(struct device *dev, struct device_driver *drv)
{
	struct i2c_client	*client = i2c_verify_client(dev);
	struct i2c_driver	*driver;

	if (!client)
		return 0;

	/* Attempt an OF style match */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* Then ACPI style match */
	if (acpi_driver_match_device(dev, drv))
		return 1;

	driver = to_i2c_driver(drv);
	/* match on an id table if there is one */
	if (driver->id_table)
		return i2c_match_id(driver->id_table, client) != NULL;

	return 0;
}
7. 即使使用设备树来匹配，也要对id_table进行有效的赋值，否则probe不会被回调
https://www.cnblogs.com/xiaojiang1025/p/6501956.html
