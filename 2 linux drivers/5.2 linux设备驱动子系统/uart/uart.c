UART中的硬件流控RTS与CTS
https://blog.csdn.net/zeroboundary/article/details/8966586
1. uart的流控
RTS是模块的输入端，用于MCU通知模块，MCU是否准备好，模块是否可向MCU发送信息，RTS的有效电平为低。
CTS是模块的输出端，用于模块通知MCU，模块是否准备好，MCU是否可向模块发送信息，CTS的有效电平为低
