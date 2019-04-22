1. 按键事件上报
input_report_key(data->input_dev, key_val, 1);
input_sync(data->input_dev);
2. 触摸屏的单点事件上报
input_report_abs(data->input_dev, ABS_X, event->x1);
input_report_abs(data->input_dev, ABS_Y, event->y1);
input_report_abs(data->input_dev, ABS_PRESSURE, event->pressure);

input_report_key(data->input_dev, BTN_TOUCH, 1);
input_sync(data->input_dev);

input_report_abs(data->input_dev, ABS_PRESSURE, 0);
input_report_key(data->input_dev, BTN_TOUCH, 0);
input_sync(data->input_dev);
3. 触摸屏的多点事件上报
input_report_abs(data->input_dev, ABS_MT_TRACKING_ID, event->touch_ID5);
input_report_abs(data->input_dev, ABS_MT_TOUCH_MAJOR, event->pressure);
input_report_abs(data->input_dev, ABS_MT_POSITION_X, event->x5);
input_report_abs(data->input_dev, ABS_MT_POSITION_Y, event->y5);
input_report_abs(data->input_dev, ABS_MT_WIDTH_MAJOR, 30);
input_mt_sync(data->input_dev);

input_sync(data->input_dev);

input_report_abs(data->input_dev, ABS_MT_TOUCH_MAJOR, 0);
input_report_abs(data->input_dev, ABS_MT_WIDTH_MAJOR, 0);
input_sync(data->input_dev);
