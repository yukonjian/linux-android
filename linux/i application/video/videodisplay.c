#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

#include <linux/videodev2.h>
#include "sunxi_display2.h"



#define VIDEO_DEVICE_NAME	"/dev/video2"

#define NB_BUFFER		(5)
#define C72_SCREEN_WIDTH	(1024)
#define C72_SCREEN_HIGH	(600)
#define VIDEO_WIDTH 	(800)
#define VIDEO_HIGH 		(600)


struct v4l2_capability cap;
struct v4l2_format format;
struct v4l2_requestbuffers rqbuf;
struct v4l2_buffer buf;
struct v4l2_fmtdesc fmtdesc;
struct v4l2_input input;
struct v4l2_streamparm parms;
struct disp_layer_info info;





struct buffer
{
	void* start;
	unsigned int length;
};

struct buffer mapbuff[NB_BUFFER] = {NULL};







//存放的码流为: Y0 U0 Y1 V1 Y2 U2 Y3 V3
//映射出像素点为：[Y0 U0 V1] [Y1 U0 V1] [Y2 U2 V3] [Y3 U2 V3]

void yuv_to_rgb(int Y,int Cb,int Cr, char *r, char *g, char *b)
{
	int tmpr, tmpg, tmpb;
	/* 使用浮点运算效率较差 */
	tmpr = 1.16*(Y-16) + 1.596*(Cr-128);
	tmpg = 1.164*(Y-16)-0.392*(Cb-128)-0.813*(Cr-128);
	tmpb = 1.164*(Y-16)+2.017*(Cb-128);

	if(tmpr > 255)
		tmpr = 255;
	if(tmpg > 255)
		tmpg = 255;
	if(tmpb > 255)
		tmpb = 255;

	if(tmpr < 0)
		tmpr = 0;
	if(tmpg < 0)
		tmpg = 0;
	if(tmpb < 0)
		tmpb = 0;

	*r = tmpr;
	*g = tmpg;
	*b = tmpb;

}

void yuv422_to_rgb(char *yuv, char *rgb, unsigned int length)
{
	int y0, cb0, cr0, y1, cb1, cr1;
	char r, g, b;
	unsigned int i=0, j=0;
	unsigned y_num = VIDEO_WIDTH*VIDEO_HIGH;

	for (i = 0; i < y_num; ) {
		y0 = *(yuv + i);
		cr0 = *(yuv + i + y_num);
		cb0 = *(yuv + i + y_num + 1);

		y1 = *(yuv + i + 1);
		cb1 = cb0;
		cr1 = cr0;

		yuv_to_rgb(y0, cb0, cr0, &r, &g, &b);
		*(rgb + j) = r;
		*(rgb + j + 1) = g;
		*(rgb + j + 2) = b;
		yuv_to_rgb(y1, cb1, cr1, &r, &g, &b);
		*(rgb + j + 3) = r;
		*(rgb + j + 4) = g;
		*(rgb + j + 5) = b;

		i = i + 2;
		j = j +6;

	}
}

static int crop_rgb_map(char *src, char *des, int src_width, int src_heigh, int des_width, int des_heigh, int channel)
{
	int i,j,k;

	if(des_width > src_width || des_heigh > src_heigh)
		return -1;

	for (i = 0; i < des_heigh; i++) {
		for (j = 0; j < des_width; j++) {
			for (k = 0; k < channel; k++)
				*(des + ((i * des_width) + j) * channel + k) = *(src + ((i * src_width) + j) * channel + k);
		}
	}
}

static int rotation_180_map(unsigned char *src, unsigned char *des, int srcW, int srcH, int channel)
{
	int i = 0;
	int j = 0;
	int k = 0;
	unsigned char temp =  (unsigned char)0;
	for(i = 0; i <=srcH-1 ; i ++)
	{
		for(j = 0; j <= srcW -1; j ++)
		{
			for(k = 0; k < channel; k ++)
			{
				temp = src[(i * srcW + j) * channel + k];
				des[((srcH-1-i)*srcW +(srcW-1-j))* channel + k]=temp;
			}
		}
	}
 return 0;
}

void lcd_map_view(int x, int y, int width, int heigh, int screen_width, int screen_heigh, unsigned char *addr, unsigned char *data, int channel)
{
	int i,j;
	unsigned int base;
	unsigned int width_data;
	if (width * heigh > screen_width * screen_heigh)
		return;

	width_data = width * channel;
	base = (x + (y * screen_width)) * channel;

	for(i = 0; i < heigh; i++) {
		for (j = 0; j < width_data; j++) {
			*(addr + base + j) = *(data);
			data++;
		}

		base += C72_SCREEN_WIDTH * channel;		//一行的数据量,c72使用的屏幕宽度为1024

	}
}

/***********************************************************************************************************
 *初始化lcd屏幕，
 *
 *return : 设备号
 *
 ***********************************************************************************************************/
int c72_lcd_view_init(void **memmap)
{
	unsigned int arg[3];
	unsigned int fb_width,fb_height;
	int dispfb0;

	if((dispfb0 = open("/dev/fb0",O_RDWR)) == -1) {
		printf("open /dev/fb0 device fail!\n");
		return -1;
	}

	*memmap = (int)mmap(NULL, C72_SCREEN_WIDTH*C72_SCREEN_HIGH*3, PROT_READ | PROT_WRITE, MAP_SHARED, dispfb0, 0L);
	if(*memmap == 0) {
		printf("DISP_MEM_MAP 0\n");
		return -1;
	}

	return dispfb0;
}

void c72_lcd_view_exit(int fd, void *memmap)
{
	munmap(memmap, C72_SCREEN_WIDTH*C72_SCREEN_HIGH*3);
	close(fd);
}



int main(int argc, char **argv)
{
	int retval = 0;
	int dispfd;
	int viodefd;
	void *disp_buf;
	int type;
	int i;
	fd_set fds;
	struct timeval tv;

	char *data_buf1 = NULL;
	char *data_buf2 = NULL;



	/* 分配缓冲区 */
	data_buf1 = malloc(C72_SCREEN_WIDTH*C72_SCREEN_HIGH*3);
	data_buf2 = malloc(C72_SCREEN_WIDTH*C72_SCREEN_HIGH*3);

	/* 初始化lcd */
	c72_lcd_view_init(&disp_buf);

	/* 摄像头获取数据 */
	/* 打开设备 */
	viodefd = open("/dev/video2", O_RDWR | O_NONBLOCK);
	if (viodefd <= 0)
		printf("Error open video device.\n");

	fcntl(viodefd, F_SETFD, FD_CLOEXEC);

	/* 查询设备支持的操作 */
	if(ioctl(viodefd,VIDIOC_QUERYCAP,&cap) < 0)
		printf("Error VIDIOC_QUERYCAP failed.\n");
	printf("The driver name is %s; card name is %s;\n", cap.driver, cap.card);
	printf("The capability is 0x%x\n", cap.capabilities);
	/* V4L2_CAP_VIDEO_CAPTURE  V4L2_CAP_READWRITE   V4L2_CAP_STREAMING */
	input.index = 0;
	input.type = V4L2_INPUT_TYPE_CAMERA;

	/* set input input index */
	if (ioctl(viodefd, VIDIOC_S_INPUT, &input))
		printf("The VIDIOC_S_INPUT is failed\n");
#if 0
	/*  */
	parms.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	parms.parm.capture.timeperframe.numerator = 1;
	parms.parm.capture.timeperframe.denominator = fps;
	if (ioctl(viodefd, VIDIOC_S_PARM, &parms) < 0)
		printf("The VIDIOC_S_INPUT is failed\n");
#endif

	/* 设置视频格式 */
	memset(&format, 0, sizeof(struct v4l2_format));
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	format.fmt.pix.width = VIDEO_WIDTH;
	format.fmt.pix.height = VIDEO_HIGH;
	format.fmt.pix.field = V4L2_FIELD_NONE;
	format.fmt.pix.pixelformat = V4L2_PIX_FMT_NV16;
	if(ioctl(viodefd,VIDIOC_S_FMT,&format) < 0)
		printf("The VIDIOC_S_FMT is failed\n");



	/* 请求缓存 */
	rqbuf.count = NB_BUFFER;
	rqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	rqbuf.memory = V4L2_MEMORY_MMAP;
	if(ioctl(viodefd,VIDIOC_REQBUFS,&rqbuf) < 0)
		printf("The VIDIOC_REQBUFS is failed\n");

	/* 查询(请求的)缓冲区的地址和长度,并映射到用户空间 */
	for (i = 0; i < NB_BUFFER; i++) {
		memset(&buf, 0, sizeof(struct v4l2_buffer));
		buf.index = i;
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;		/* 和请求的类型一致 */
		buf.memory = V4L2_MEMORY_MMAP;
		if(ioctl(viodefd,VIDIOC_QUERYBUF,&buf) < 0)
			printf("The VIDIOC_QUERYBUF failed.\n");

		/* 映射到用户空间 */
		mapbuff[i].start = mmap(0, buf.length, PROT_READ, MAP_SHARED, viodefd, buf.m.offset);
		if (mapbuff[i].start == ((void*)-1))
			printf("mmap[%d] failed;\n", i);
		mapbuff[i].length = buf.length;
	}

	/* 将缓冲区的数据放入队列中(以的到camera的数据),queue the                   buffer */
	for (i = 0; i < NB_BUFFER; i++) {
		memset(&buf, 0, sizeof(struct v4l2_buffer));
		buf.index = i;
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;		/* 和请求的类型一致 */
		buf.memory = V4L2_MEMORY_MMAP;
		if(ioctl(viodefd,VIDIOC_QBUF,&buf) < 0)
			printf("The VIDIOC_QBUF failed.\n");
	}

	/* 开始捕获摄像头信号 */
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(ioctl(viodefd,VIDIOC_STREAMON,&type) < 0)
		printf("The VIDIOC_STREAMON is failed\n");


	while(1) {
//	sleep(1);
		FD_ZERO(&fds);
		FD_SET(viodefd, &fds);

		/* timeout */
		tv.tv_sec  = 2;
		tv.tv_usec = 0;
		select(viodefd + 1, &fds, NULL, NULL, &tv);
		printf("Read frame buffer\n");

		/* 获取帧并进行处理 */
		memset(&buf, 0, sizeof(struct v4l2_buffer));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		/* get data from buffers */
		if(ioctl(viodefd, VIDIOC_DQBUF,&buf) < 0)
			printf("The VIDIOC_DQBUF is failed\n");
#if 1

		/* 拷贝数据 */
		memcpy(data_buf1, mapbuff[buf.index].start, buf.bytesused);
		//printf("The get data length is %d\n", buf.bytesused);

		/* 将采集到的ycrcb数据转换为rgb */
		yuv422_to_rgb(data_buf1, data_buf2, buf.bytesused);

		/* 裁剪512*300的图像 */
		crop_rgb_map(data_buf2, data_buf1,VIDEO_WIDTH, VIDEO_HIGH, 512, 300, 3);

		/* 将图片旋转180度 */
		rotation_180_map(data_buf1, data_buf2, 512, 300, 3);

		/* 显示图片 */
		lcd_map_view(512, 50, 512, 300, C72_SCREEN_WIDTH, C72_SCREEN_HIGH, disp_buf, data_buf2, 3);
#endif
		if(ioctl(viodefd,VIDIOC_QBUF,&buf) < 0)
			printf("The VIDIOC_QBUF failed.\n");
	}

	/* 停止捕获摄像头信号 */
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(ioctl(viodefd,VIDIOC_STREAMOFF,&type) < 0)
		printf("The VIDIOC_STREAMOFF is failed\n");


	/* 关闭设备文件 */
	close(viodefd);


	/* 释放lcd资源 */
	c72_lcd_view_exit(dispfd, disp_buf);
	return 0;
}
