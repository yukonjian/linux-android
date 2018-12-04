#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define C72_LED_IOCTL			(0xa000)
#define C72_LED_SOUND_ON		(C72_LED_IOCTL + 1)
#define C72_LED_SOUND_OFF		(C72_LED_IOCTL + 2)
#define C72_LED_PHONE_ON		(C72_LED_IOCTL + 3)
#define C72_LED_PHONE_OFF		(C72_LED_IOCTL + 4)
#define C72_LED_MEETING_ON		(C72_LED_IOCTL + 5)
#define C72_LED_MEETING_OFF		(C72_LED_IOCTL + 6)
#define C72_LED_LOCK_ON			(C72_LED_IOCTL + 7)
#define C72_LED_LOCK_OFF		(C72_LED_IOCTL + 8)
#define C72_LED_POWER_ON		(C72_LED_IOCTL + 9)
#define C72_LED_POWER_OFF		(C72_LED_IOCTL + 10)
#define C72_LED_MESSAGE_ON		(C72_LED_IOCTL + 11)
#define C72_LED_MESSAGE_OFF		(C72_LED_IOCTL + 12)
#define C72_LED_ALARM_RED_ON	(C72_LED_IOCTL + 13)
#define C72_LED_ALARM_BLUE_ON	(C72_LED_IOCTL + 14)
#define C72_LED_ALARM_OFF		(C72_LED_IOCTL + 15)


int main(void)
{
	int fd;
	int ret;

	fd = open("/dev/disp", O_RDWR);
	if(fd < 0){
		printf("open error.\n");
		return -1;
	}

/*	ret = ioctl(fd,C72_LED_SOUND_OFF,0);	
	if(ret)
		printf("Ioctl running faiulre.\n");

	ret = ioctl(fd,C72_LED_PHONE_OFF,0);	
	if(ret)
		printf("Ioctl running faiulre.\n");
	
	ret = ioctl(fd,C72_LED_MEETING_OFF,0);	
	if(ret)
		printf("Ioctl running faiulre.\n");

	ret = ioctl(fd,C72_LED_LOCK_OFF,0);	
	if(ret)
		printf("Ioctl running faiulre.\n");

	ret = ioctl(fd,C72_LED_POWER_OFF,0);	
	if(ret)
		printf("Ioctl running faiulre.\n");

	ret = ioctl(fd,C72_LED_MESSAGE_OFF,0);	


	ret = ioctl(fd,C72_LED_ALARM_OFF,0);	

*/
//	ret = ioctl(fd,C72_LED_ALARM_RED_ON,0);		
	
	printf("main running finished.\n");

	return 0;
}




