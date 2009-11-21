/* port.c */

/*
 * Here will all port funktions be
 */

#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */


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

