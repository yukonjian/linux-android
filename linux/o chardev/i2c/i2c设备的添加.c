1. 让系统自动添加
1）注册板级信息，主要是名字（会拷贝到client->name中，在match时会用到）和I2c的从设备地址；
static struct i2c_board_info ksz8873_i2c_board_info [] = {
	{
		I2C_BOARD_INFO("ksz8873", 0x5f),
		.platform_data = &ksz8873_data,
	}
};
2）将板级信息添加到__i2c_board_list中，注册adapter的时候会注册所有__i2c_board_list中的设备
i2c_register_board_info(0, ksz8873_i2c_board_info,
					ARRAY_SIZE(ksz8873_i2c_board_info));
3）在int i2c_register_adapter(struct i2c_adapter *adap)调用中会调用：
i2c_scan_static_board_info(adap);
    i2c_new_device(adapter, &devinfo->board_info)
最终会调用i2c_new_device添加设备

2. 手动调用i2c_new_device进行添加
1）注册板级信息
static struct i2c_board_info ksz8873_i2c_board_info [] = {
	{
		I2C_BOARD_INFO("ksz8873", 0x5f),
		.platform_data = &ksz8873_data,
	}
};
2）获取根据ID获取adapter
i2c_adapter* i2c_get_adapter(int id)
3）调用i2c_new_device进行设备的添加
i2c_new_device(adapter, &ksz8873_i2c_board_info)
    拷贝name到client->name中；拷贝从设备地址；
    注册设备，device_register(&client->dev);
