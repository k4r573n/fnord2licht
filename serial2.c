/* vim ts=4 noexpandtab sw=4
 * http://www.easysw.com/~mike/serial/serial.html
 */


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */

#include <time.h>
#include <getopt.h>
#include <stdlib.h>

//#include "./help.c"
#include "./fnordlicht.h"

#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */



extern int open_port(char *device);
extern int init_port(int fd);
extern void show_help();


extern void notify(int addr, int color_channels);

extern int fd;//  fd is for the port connection

int getinfo(int fd) {
	struct termios termAttr;
	int inputSpeed = -1;
	speed_t baudRate;
	tcgetattr(fd, &termAttr);
	printf("c_cflag=%d\n",termAttr.c_cflag);
	printf("c_iflag=%d\n",termAttr.c_iflag);
	printf("c_oflag=%d\n",termAttr.c_oflag);
	printf("c_lflag=%d\n",termAttr.c_lflag);
	printf("c_cc=%d\n",termAttr.c_cc);
	printf("c_ispeed=%d\n",termAttr.c_ispeed);
	printf("c_ospeed=%d\n",termAttr.c_ospeed);

	/* Get the input speed.                              */
	baudRate = cfgetispeed(&termAttr);
	switch (baudRate) {
		case B0:      inputSpeed = 0; break;
		case B50:     inputSpeed = 50; break;
		case B110:    inputSpeed = 110; break;
		case B134:    inputSpeed = 134; break;
		case B150:    inputSpeed = 150; break;
		case B200:    inputSpeed = 200; break;
		case B300:    inputSpeed = 300; break;
		case B600:    inputSpeed = 600; break;
		case B1200:   inputSpeed = 1200; break;
		case B1800:   inputSpeed = 1800; break;
		case B2400:   inputSpeed = 2400; break;
		case B4800:   inputSpeed = 4800; break;
		case B9600:   inputSpeed = 9600; break;
		case B19200:  inputSpeed = 19200; break;
		case B38400:  inputSpeed = 38400; break;
	}
	printf("baud=%d\n",inputSpeed);
	return 0;
}


int main(int argc, char *argv[]) {
	//for (int i = 1; i <= argc;i++) {
	extern char *optarg;
	extern int optind, opterr, optopt;
	int opt; 
	short verbose=0;
	char *device = "/dev/ttyUSB0";//testing

	int addr=255,notif=0,
		 red=( rand() % ( 255 + 1 ) ),
		 blue=( rand() % ( 255 + 1 ) ),
		 green=( rand() % ( 255 + 1 ) );//standard werte (random)
//	int red=255, blue=0, green=0;

	/* set/configure output */
	/*open_port(device);
	init_port(fd);

	addr=0;
	//notify(fd,addr,2);
	powerdown(addr);
//	 sync();
//	stop(addr, 255);
	powerdown(addr); //send powerdown to broadcast
	sleep(10);

	fade_rgb(addr, 255, 0, red, green, blue);//0,0,255);//red, green, blue);
	close(fd);
	return 0;
*/
	//parameterauswerten
	while ((opt = getopt(argc, argv, "a:r:g:b:d:n:hv")) != -1) {
		switch (opt) {
			case 'a': // adress
				addr = atoi(optarg);
				break;
			case 'r': // red
				red = atoi(optarg);
				break;
			case 'g': // green
				blue = atoi(optarg);
				break;
			case 'b': // blue
				green = atoi(optarg);
				break;
			case 'n': // notify
				notif = atoi(optarg);
				break;
			case 'd': // device
				device = optarg;
				break;
			case 'v': // verbose
				verbose = 1;
				break;
			case 'h':
				show_help();
				exit(0);
				break;
			default:
				//error
				fprintf(stderr, "Short Usage: %s [-a <address>] [-r <red_color_code>] [-g <green_color_code>] [-b <blue_color_code>]\n\t\t try -h for more information\n", argv[0]);
				exit(1);
		}
	}

	getinfo(fd);

	/* set/configure output */
	open_port(device);
	init_port(fd);

	getinfo(fd);

	//syncronisation of the connection
	sync();
	//stop all fadings
	stop(addr,255);
	//notification
	if (notif>0) {
		printf("noti1\n");
		if (verbose) printf("start Notification %i\n",notif);
		notify(addr,notif);
	}else{
             printf("not noti\n");
		//set color
		fade_rgb(addr,255,0,red,green,blue);

		if (verbose) {//verbose mode
			printf("Device:%s\n",device);
      		 printf("Light %i ist set to red:%i green:%i blue:%i \n",addr,red,green,blue);
		}
	}

	close(fd);
	return 0;
}
