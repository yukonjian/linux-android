1. Input驱动编写步骤：
1）分配一个输入设备(input_dev): >> buttons_dev=input_allocate_devices;
2）设置驱动支持什么事件：>> set_bit(EV_KEY,button_dev.evbit)
set_bit告诉input子系统它支持哪些事件(按键，滑动，重复......)
3）注册一个输入设备；>> input_register_device(buttons_dev);
4）驱动事件报告,硬件相关；(申请中断，添加定时器...)
5）释放和注销设备；

/* 1. 分配一个input_dev结构体 */
buttons_dev = input_allocate_device();;

/* 2. 设置 */
/* 2.1 能产生哪类事件 */
set_bit(EV_KEY, buttons_dev->evbit);
set_bit(EV_REP, buttons_dev->evbit);

/* 2.2 能产生这类操作里的哪些事件: L,S,ENTER,LEFTSHIT */
set_bit(KEY_L, buttons_dev->keybit);
set_bit(KEY_S, buttons_dev->keybit);
set_bit(KEY_ENTER, buttons_dev->keybit);
set_bit(KEY_LEFTSHIFT, buttons_dev->keybit);

/* 3. 注册 */
input_register_device(buttons_dev);

/* 4. 硬件相关的操作 */
init_timer(&buttons_timer);
buttons_timer.function = buttons_timer_function;
add_timer(&buttons_timer);

/* 5. 硬件相关的操作 */
input_unregister_device(buttons_dev);
input_free_device(buttons_dev);
