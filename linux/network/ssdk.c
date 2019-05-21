1. athrs_mac.c / athr_gmac_init();
1.1 athr_gmac_phy_attach(mac,mac->mac_unit);
1.1.1 qthrs17_phy.c / int athrs17_register_ops(void *arg)
1.1.2 athrs17_reg_init()
1.1.2.1 ssdk_init(0, &cfg);
1.1.2.2 初始化phy
    /*cpu port en*/
    athrs17_reg_write(0x620, (athrs17_reg_read(0x620)|0x400));
    /* enable L3 offload */
    athrs17_reg_write(0x30, (athrs17_reg_read(0x30) | 0x4));

    /* Power-on-strapping select */
    athrs17_reg_write(0x10  , 0x40000000);

    /* RMII interface, PHY RMII slave */
    athrs17_reg_write(0x4   , 0x20000000);

    /* 接收mac流控制 */
    athrs17_reg_write(0x7c  , 0x0000007e);
