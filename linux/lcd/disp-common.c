1.bsp_disp_set_print_level(DEFAULT_PRINT_LEVLE); //disp2/disp/de/disp_display.c
2.disp2/disp/de/include.h/ DEFAULT_PRINT_LEVLE 0
3.disp_init_al(para);  //所有base寄存器赋值给全局变量。
4../aw/hwc/t3/hwc_sunxi.cpp:    Globctx->FBFd = open("/dev/graphics/fb0", O_RDWR);
