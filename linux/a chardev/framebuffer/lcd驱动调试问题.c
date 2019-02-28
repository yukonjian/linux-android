一. 调试东鑫达的3.5寸液晶屏
1. 在输入某些命令前需要输入命令开关
	lcd_spi_cmd_write(0xf0);	//使能command tab 1
	lcd_spi_data_write(0xc3);
2. RGB模式设置
lcd_spi_cmd_write(0x3A);	//RGB=16bit/pixel
3. 信号选择，是否选择GRB模式，DE是否使能，是否使用frame memory
	lcd_spi_cmd_write(0xB6);
	lcd_spi_data_write(0x20);
	lcd_spi_data_write(0x02);
	lcd_spi_data_write(0x3b);

4. 在将320*480的竖屏显示转换为横屏显示的过程中遇到的问题
1)主机端的数据传输：理论上横屏显示传输的格式应该是480*320,但是该液晶屏需要使用320*480的格式进行数据传输
2)MV的调换，只用使用了frame memory 模式才有水平和垂直方向的调换，而Direct to shift register是没有MV反转功能的。
3)若发现屏幕不停的闪动，一般和主发送的信号有关，
a)对于大的屏幕可能是屏幕的刷新比较慢导致的。
b)可能和HSYNC和VSYNC的信号有关。
