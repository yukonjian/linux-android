#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>

#include "sunxi_display2.h"


int main(int argc, char **argv)
{
	int fd;
	int ret;
	int arg[5][5] = {0};
	arg[1][1] = atoi(argv[1]);
	arg[2][1] = atoi(argv[2]);
	arg[3][1] = atoi(argv[3]);
	arg[4][1] = atoi(argv[4]);
	
	if(arg[1][1] > 100)
		arg[1][1] = 100;
	
	if(arg[2][1] > 100)
		arg[2][1] = 100;
	
	if(arg[3][1] > 100)
		arg[3][1] = 100;
	
	if(arg[4][1] > 100)
		arg[4][1] = 100;

	printf("The input brinhtness: %d; contrast: %d; saturation: %d; hue: %d; \n", arg[1][1], arg[2][1], arg[3][1], arg[4][1]);	
	
	fd = open("/dev/disp", O_RDWR);
	if(fd < 0){
		printf("Open disp error;\n");
	}
	
	ret = ioctl(fd,DISP_ENHANCE_BRIGHTNESS, &arg[1][0]);
	if(ret)
		printf("Ioctal brinhtness failed;\n");
	
	ret = ioctl(fd,DISP_ENHANCE_CONTRAST, &arg[2][0]);
	if(ret)
		printf("Ioctal contrast failed;\n");
	
	ret = ioctl(fd,DISP_ENHANCE_SATUATION, &arg[3][0]);
	if(ret)
		printf("Ioctal saturation failed;\n");

	ret = ioctl(fd,DISP_ENHANCE_HUE, &arg[4][0]);
	if(ret)
		printf("Ioctal hue failed;\n");

	return 0;
}






