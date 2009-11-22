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

extern int open_port(char *device);
extern void init_port(int fd);
extern void show_help();
void send_paket(int fd, int addr, int red, int green, int blue);
extern void notify(int fd, int addr, int color_channels);


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

void send_paket(int fd, int addr, int red, int green, int blue) {
/*send commands*/
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
  t = green;	
  a = (char*)&t;
  write(fd, a, 1);

	write(fd, "b", 1);
	t = blue;
	a = (char*)&t;
	write(fd, a, 1);
}


int main(int argc, char *argv[]) {
	//for (int i = 1; i <= argc;i++) {
  extern char *optarg;
  extern int optind, opterr, optopt;
  int opt;
  short verbose=0;
  short noti=0;
  char *device = "/dev/ttyUSB0";//testing

	int addr=255, red=-1, blue=-1, green=-1;//standard werte

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
      case 'd': // device
        device = optarg;
        break;
      case 'n': // notify
        noti=atoi(optarg);
        break;
      case 'v': // verbose
        verbose = 1;
        break;
      case 'h':
	      show_help();
        exit(0);
        break;
      default: // ?
        fprintf(stderr, "Usage: %s [-d <device>] [-a <address>] [-r <red_color_code>] [-g <green_color_code>] [-b <blue_color_code>] [-v] [-h]\n", argv[0]);
        exit(1);
        break;
    }
  }

  if (verbose) {//verbose mode
    printf("Device:%s\n",device);
	  printf("Light %i ist set to red:%i green:%i blue:%i \n",addr,red,green,blue);
	 }

  /*set/configure output*/
	int fd = open_port(device);
	if (!( fd > -1 )) {
	  fprintf(stderr, "Could not open Device: %s \n", device);
    exit(1);
  }
  init_port(fd);

  if (noti) {
    if (verbose) printf("start Notification %i\n",noti);
    notify(fd,addr,noti);
    exit(0);
  }

  /*if params are valid*/
  if (blue<0||red<0||green<0) {
	  fprintf(stderr, "Could not set colors: %i %i %i \n", red,green,blue);
    exit(1);
  }

  send_paket(fd,addr,red,green,blue);

	return 0;     
}
 
