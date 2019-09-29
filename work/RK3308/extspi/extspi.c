crw-rw----    1   13, 224 misc0
crw-rw----    1   10,  62 host_spi

1. ioctl MISC_IOCS_SPI_SEND_UP:   //iss/iss.c
    slave_add_sendup_msg();       //ext/ext.c
      wake_up(&task->waitqueue);

2. task_thread()                //ext/ext.c
    add_wait_queue(&task->waitqueue, &wait);
    slave_sendup_request();
