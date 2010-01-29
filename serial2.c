/*
 * http://www.easysw.com/~mike/serial/serial.html
 */


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */

#include <time.h>
#include <getopt.h>
#include <stdlib.h>

//#include "./help.c"

extern int open_port(char *device);
extern int init_port(int fd);
extern void show_help();

extern void powerdown(int addr);
extern void fade_rgb(int addr, int step, int delay, int red, int green, int blue);

extern void notify(int addr, int color_channels);

int fd=-1;//  fd is for the port connection

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
  short verbose=0;
  char *device = "/dev/ttyUSB0";//testing

	int addr=255, red=255, blue=255, green=255;//standard werte


  /* set/configure output */ 
  open_port(device);
  init_port(fd);
            
  //notify(fd,addr,2);

  fade_rgb(addr, 255, 0, red, green, blue);
//  powerdown(addr); //send powerdown to broadcast

  close(fd);
  return 0;

	//parameterauswerten
	while ((opt = getopt(argc, argv, "a:r:g:b:d:n:Rhv")) != -1) {
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
      case 'v': // verbose
        verbose = 1;
        break;
      case 'h':
	      show_help();
        exit(0);
        break;
      default: // ?
        /* and now connect and show the effects */

        if (verbose) {//verbose mode
          printf("Device:%s\n",device);
	        printf("Light %i ist set to red:%i green:%i blue:%i \n",addr,red,green,blue);
         }

        /* set/configure output */
        fd = open_port(device);
        if (!( fd > -1 )) {
	        fprintf(stderr, "Could not open Device: %s \n", device);
          exit(1);
        }
        init_port(fd);
        
        switch (opt) {
          case 'R': //set random color
            if (verbose) printf("set color at random \n");
            //init random
            srand( (unsigned) time(NULL) ) ; 
            //Eine Zufallszahl zwischen a und b (incl. a und b) erzeugt man z.B. mit:
            //a + ( rand() % ( b - a + 1 ) ) 
            fade_rgb(addr,255,0,( rand() % ( 255 + 1 ) ),( rand() % ( 255 + 1 ) ),( rand() % ( 255 + 1 ) ));
            exit(0);
            break;
          case 'n': // notify
            if (verbose) printf("start Notification %i\n",atoi(optarg));
            notify(addr,atoi(optarg));
            exit(0);
            break;
          default: // ?
            //set color
            if ((red!=-1)&&(green!=-1)&&(blue!=-1)) fade_rgb(addr,255,0,red,green,blue);

            fprintf(stderr, "Short Usage: %s [-a <address>] [-r <red_color_code>] [-g <green_color_code>] [-b <blue_color_code>]\n\t\t try -h for more information\n", argv[0]);
            exit(1);
            break;
        }
    }

  }
//bull shit - der code kann nie richtig ausgeführt werden - notify und random mag zwar schein bar gehen
  // aber nicht wennn irgend ein anderer parameter angegeben wird - da dann aus der abfrage gesprungen wird...

  /*if params are valid*/
  if (blue<0||red<0||green<0) {
	  fprintf(stderr, "Could not set colors: %i %i %i \n", red,green,blue);
    exit(1);
  }

  fade_rgb(addr,255,0,red,green,blue);

	return 0;     
}
 
