/*
 * http://www.easysw.com/~mike/serial/serial.html
 */


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

//#include <time.h>
#include <getopt.h>
#include <stdlib.h>

#include "./help.c"

int open_port(void);
void init_port(int fd);
extern void show_help();


/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int open_port(void) {
     int fd; /* File descriptor for the port */


     fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
     if (fd == -1) {
	    /*
	     * Could not open the port.
	     */

	     //try an alternativ divice
       fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
	     if (fd == -1) {
	     	 //Could not open the other port
	       perror("open_port: Unable to open /dev/ttyUSB0 - ");
	     }
       else { //alternativ device works
	      fcntl(fd, F_SETFL, 0);
        return (fd);
	     }

	     perror("open_port: Unable to open /dev/ttyS0 - ");
     }
     else
	  fcntl(fd, F_SETFL, 0);

     return (fd);
}

/*
 * 'init_port()' - initialised serial port 1.
 *
 * Needs the file descriptor 
 * Returns nothing.
 */


void init_port(int fd) {
	struct termios options;

/*
 * Get the current options for the port...
 */

	tcgetattr(fd, &options);

/*
 * Set the baud rates to 19200...
 */

	cfsetispeed(&options, B19200);
	cfsetospeed(&options, B19200);

/*
 * Enable the receiver and set local mode...
 */

	options.c_cflag |= (CLOCAL | CREAD);

/*
 * Set the new options for the port...
 */

	tcsetattr(fd, TCSANOW, &options);

	options.c_cflag &= ~CSIZE; /* Mask the character size bits */
	options.c_cflag |= CS8;    /* Select 8 data bits */

	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

/*
 * Choosing Raw Input
 */

	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
}

/*int msleep(unsigned long milisec)
{
    struct timespec req={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    while(nanosleep(&req,&req)==-1)
         continue;
    return 1;
}*/


int main(int argc, char *argv[]) {
	//for (int i = 1; i <= argc;i++) {
  extern char *optarg;
  extern int optind, opterr, optopt;
  int opt;

	int addr=255, red=-1, blue=-1, green=-1;//standard werte

	//parameterauswerten
	while ((opt = getopt(argc, argv, "a:r:g:b:v")) != -1) {
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
      case 'v':
        fprintf(stdout,"version 0.2 by Karsten Hinz");
        exit(0);
        break;
      default: // ?
        fprintf(stderr, "Usage: %s [-a <address>] [-r <red_color_code>] [-g <green_color_code>] [-b <blue_color_code>] [-v]\n", argv[0]);
        exit(1);
        break;
    }
  }


	show_help();

	printf("%i %i %i %i\n",addr,red,blue,green);

	int fd = open_port();
	if ( fd > -1 ) exit(1);
  init_port(fd);
	unsigned int t=0;

	char* a=(char*)&t;


	write(fd, "a", 1);
	t = addr;
	a = (char*)&t;
	write(fd, a, 1);

 write(fd, "r", 1);
 t = red;
 a = (char*)&t;
 write(fd, a, 1);

 write(fd, "g", 1);
 t = blue;	
 a = (char*)&t;
 write(fd, a, 1);

	write(fd, "b", 1);
	t = green;
	a = (char*)&t;
	write(fd, a, 1);

	return 0;     
}
 
