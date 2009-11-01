/*
 * http://www.easysw.com/~mike/serial/serial.html
 */


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include <time.h>

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int open_port(void)
{
     int fd; /* File descriptor for the port */
     
     
     fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
     if (fd == -1)
     {
	  /*
	   * Could not open the port.
	   */
	  
	  perror("open_port: Unable to open /dev/ttyS0 - ");
     }
     else
	  fcntl(fd, F_SETFL, 0);
     
     return (fd);
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


int main(int argc, char** argv) {
int addr = atoi(argv[1]);
int red = atoi(argv[2]);
int blue = atoi(argv[3]);
int green = atoi(argv[4]);

 printf("%i %i %i %i\n",addr,red,blue,green);

int fd = open_port();

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

 int n;
 unsigned int t=0;
 char* a=(char*)&t;

// write(fd, "X", 1);

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

// write(fd, "X", 1);
//
// write(fd, "r", 1);
// write(fd, a, 1);
//
// write(fd, "g", 1);
// write(fd, a, 1);
//
// write(fd, "b", 1);
// write(fd, a, 1);
//
//
// unsigned int max = 100;
// unsigned int sleeptime = 10;
// char test = '0';;
//
// for(t=0;t<max;++t){
//      write(fd, "r", 1);     
//      a = (char*)&t;
//      test = a[0];
//      printf("%c\n",test);
//      write(fd, a, 1);
//      msleep(sleeptime);
//      
// }
//
// 
// for(t=0;t<max;++t){
//      write(fd, "g", 1);     
//      a = (char*)&t;
//      write(fd, a, 1);
//      msleep(sleeptime);
//      
// }
// 
// 
// for(t=0;t<max;++t){
//      write(fd, "b", 1);     
//      a = (char*)&t;
//      write(fd, a, 1);
//      msleep(sleeptime);
// }      
      
}
 
