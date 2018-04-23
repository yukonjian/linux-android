1. i2c_msg

68 struct i2c_msg {
69         __u16 addr;     /* slave address                        */
70         __u16 flags;
71 #define I2C_M_TEN               0x0010  /* this is a ten bit chip address */
72 #define I2C_M_RD                0x0001  /* read data, from slave to master */
73 #define I2C_M_STOP              0x8000  /* if I2C_FUNC_PROTOCOL_MANGLING */
74 #define I2C_M_NOSTART           0x4000  /* if I2C_FUNC_NOSTART */
75 #define I2C_M_REV_DIR_ADDR      0x2000  /* if I2C_FUNC_PROTOCOL_MANGLING */
76 #define I2C_M_IGNORE_NAK        0x1000  /* if I2C_FUNC_PROTOCOL_MANGLING */
77 #define I2C_M_NO_RD_ACK         0x0800  /* if I2C_FUNC_PROTOCOL_MANGLING */
78 #define I2C_M_RECV_LEN          0x0400  /* length will be first received byte */
79         __u16 len;              /* msg length                           */
80         __u8 *buf;              /* pointer to msg data                  */
81 };

--69-->从机地址
--70-->操作标志，I2C_M_RD为读(0)，写为1
--79-->有效数据长度
--80-->装载有效数据的头指针

example:
static void mpu6050_write_byte(struct i2c_client *client,const unsigned char reg,const unsigned char val)
{
    char txbuf[2] = {reg,val};
    struct i2c_msg msg[2] = {
        [0] = {
            .addr = client->addr,
            .flags= W_FLG,
            .len = sizeof(txbuf),
            .buf = txbuf,
        },
    };
    i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
}

static char mpu6050_read_byte(struct i2c_client *client,const unsigned char reg)
{
    char txbuf[1] = {reg};
    char rxbuf[1] = {0};
    struct i2c_msg msg[2] = {
        [0] = {
            .addr = client->addr,
            .flags = W_FLG,
            .len = sizeof(txbuf),
            .buf = txbuf,
        },
        [1] = {
            .addr = client->addr,
            .flags = I2C_M_RD,
            .len = sizeof(rxbuf),
            .buf = rxbuf,
        },
    };

    i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
    return rxbuf[0];
}
