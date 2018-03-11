/*
 * Watchdog Driver Test Program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>
//#include <asm/delay.h>
int fd;
#define	WDIOS_DISABLECARD	0x0001	/* Turn off the watchdog timer */
#define	WDIOS_ENABLECARD	0x0002	/* Turn on the watchdog timer */
#define	WDIOS_TEMPPANIC		0x0004	/* Kernel panic on temperature trip */
/*
 * This function simply sends an IOCTL to the driver, which in turn ticks
 * the PC Watchdog card to reset its internal timer so it doesn't trigger
 * a computer reset.
 */
static void keep_alive(void)
{
    int dummy;

    ioctl(fd, WDIOC_KEEPALIVE, &dummy);
}

/*
 * The main program.  Run the program with "-d" to disable the card,
 * or "-e" to enable the card.
 */

static void term(int sig)
{
    close(fd);
    fprintf(stderr, "Stopping watchdog ticks...\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    int flags;

    fd = open("/dev/watchdog", O_WRONLY);
	printf("48\n");
    if (fd == -1) {
	fprintf(stderr, "Watchdog device not enabled.\n");
	fflush(stderr);
	exit(-1);
    }
	printf("54\n");
    if (argc > 1) {
		if (!strncasecmp(argv[1], "-d", 2)) {
		    flags = WDIOS_DISABLECARD;

		    ioctl(fd, WDIOC_SETOPTIONS, &flags);
		    fprintf(stderr, "Watchdog card disabled.\n");
		    fflush(stderr);
			
			while(1);
		    goto end;
		    
		} else if (!strncasecmp(argv[1], "-e", 2)) {
		//Æô¶¯

			flags = WDIOS_DISABLECARD;

		    ioctl(fd, WDIOC_SETOPTIONS, &flags);
		    fprintf(stderr, "Watchdog card disabled.\n");
		    fflush(stderr);
			 flags = 5;
		    printf("set flags=%d\n",flags);
		    ioctl(fd, WDIOC_SETTIMEOUT, &flags);
		    fprintf(stderr, "Watchdog card enabled.\n");
			while(1){
			keep_alive();
			}
		    flags = WDIOS_ENABLECARD;
		    printf("flags=%d\n",flags);
		    ioctl(fd, WDIOC_SETOPTIONS, &flags);
		    fprintf(stderr, "Watchdog card enabled.\n");
		   
			while(1);
	 
	          #if 0
		    //get
	           ioctl(fd, WDIOC_GETTIMELEFT, &flags);
	           printf("%d\n",__LINE__);
	        	printf("%d read flags=%d\n",__LINE__, flags);
	        	//keep_alive();
	        	sleep(1);
	        	flags = WDIOS_DISABLECARD;
			printf("%d\n",__LINE__);
		    ioctl(fd, WDIOC_SETOPTIONS, &flags);
		    printf("%d\n",__LINE__);
		    #endif
		    fflush(stderr);
		    goto end;
		}else if (!strncasecmp(argv[1], "-b", 2)) {
	 
	        //ÉèÖÃ
		    flags = 20;
		    printf("set flags=%d\n",flags);
		    ioctl(fd, WDIOC_SETTIMEOUT, &flags);
		    fprintf(stderr, "Watchdog card enabled.\n");
	 
	           //while(1)
	           //{
	                //keep_alive();
	                //mdelay(100);
	           //}
	           //¶ÁÈ¡
	          #if 0
	           //Æô¶¯
		    flags = WDIOS_ENABLECARD;
		    printf("flags=%d\n",flags);
		    ioctl(fd, WDIOC_SETOPTIONS, &flags);
		    fprintf(stderr, "Watchdog card enabled.\n");

		    #endif
		    fflush(stderr);
		    goto end;
		}else {	    
		    
		    ioctl(fd, WDIOC_GETTIMELEFT, &flags);
		    printf("%d read flags=%d\n",__LINE__, flags);
		    fprintf(stderr, "Watchdog card enabled.\n");
		    fflush(stderr);
		    goto end;
		}
	}else {

	fprintf(stderr, "Watchdog Ticking Away!\n");
	fflush(stderr);
    }
	
    //signal(SIGINT, term);


 //   while(1) {
// #if 1
     printf("%d\n",__LINE__);
//       ioctl(fd, WDIOC_GETTIMELEFT, flags);
 //      printf("%d\n",__LINE__);
//	printf("%d read flags=%d\n",__LINE__, flags);
//	keep_alive();
//	sleep(10);
/*	flags = WDIOS_DISABLECARD;
		printf("%d\n",__LINE__);
	    ioctl(fd, WDIOC_SETOPTIONS, &flags);
	    printf("%d\n",__LINE__);*/
//#endif
//       }
end:
    close(fd);
    return 0;
}
