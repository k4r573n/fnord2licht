/* port.c */

/*
 * Here will all port funktions be
 */

#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include <string.h>  /* String function definitions */

extern int fd;

/*
 * 'open_port(device)' - Open the device.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int open_port(char *device) {
    // int fd; fd is a global var /* File descriptor for the port */

    // printf("Device in op:%s\n",device);

	fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		perror("open_port: Unable to open - ",  device);
//		fprintf(stderr, "open_port: Unable to open Device (%s) \n", device);
		exit(1);
		return -1;
	} else {
		fcntl(fd, F_SETFL, 0);
	}

	return 0;
}

/*
 * 'init_port()' - initialised serial port 1.
 *
 * Needs the file descriptor 
 * Returns nothing.
 */


int init_port(int fd) {
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


	options.c_cflag &= ~CSIZE; /* Mask the character size bits */
	options.c_cflag |= CS8;    /* Select 8 data bits */

	options.c_cflag &= ~PARENB;
	options.c_cflag &= 0;//~CSTOPB; //STOPBITS 1==0; 2==CSTOPB
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

/*
 * Choosing Raw Input
 */

	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

/*
 * Set the new options for the port...
 */

	tcsetattr(fd, TCSANOW, &options);
  
  return 1;
}

