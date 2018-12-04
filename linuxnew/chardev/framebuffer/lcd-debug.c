1.执行dd if=/dev/zero of=/dev/graphics/fb0 bs=1280 count=720*2 实现清屏
向设备文件/dev/graphics/fb0 写入1280*720*2的数据（zero）
2.捕获屏幕图片
cat /dev/graphics/fb0 > /system/sreensnap
3.显示屏幕图片
cat /system/sreensnap > /dev/graphics/fb0
4.BMP 图像文件格式(Bitmap)
采用位映射存储格式，除了图像深度可选以外，不采用其他任何压缩，因此，BMP文件所占用的空间很大。
BMP文件的图像深度可选lbit、4bit、8bit及24bit。BMP文件存储数据时，图像的扫描方式是按从左到右、从下到上的顺序。
BMP文件由文件头、位图信息头、颜色信息和图形数据四部分组成。
