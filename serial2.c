/*
 * http://www.easysw.com/~mike/serial/serial.html
 */


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */

//#include <time.h>
#include <getopt.h>
#include <stdlib.h>

//#include "./help.c"

extern int open_port(void);
extern void init_port(int fd);
extern void show_help();


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
	while ((opt = getopt(argc, argv, "a:r:g:b:h")) != -1) {
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
      case 'h':
	      show_help();
        exit(0);
        break;
      default: // ?
        fprintf(stderr, "Usage: %s [-a <address>] [-r <red_color_code>] [-g <green_color_code>] [-b <blue_color_code>] [-h]\n", argv[0]);
        exit(1);
        break;
    }
  }



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
 
