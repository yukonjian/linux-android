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

2.
