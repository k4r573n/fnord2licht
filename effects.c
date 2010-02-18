// vim: sw=8:ts=8:noexpandtab
/* effects.c */
#include <time.h>
#include "./fnordlicht.h"


/*
 * Here will all lighteffect funktions be
 */

/* send a notification
 *
 * color_channels basend on dual numbers
 * 1 for red - 2 for green - 3 for red and green -4 for ...
 *
 */
void notify(int addr, int color_channels) {
	int colors[] = {0,0,0};//r g b
	int cc=color_channels;//zum rechen
	int i=0;//laufvar
	int color_intensity=255;
	while ((cc+1) / 2) {
	  colors[i] = (cc % 2) ? color_intensity : 0;//set the color to the channel if there is a rest (1) else 0
	//	printf("temp:%i mod:%i\n",colors[i],(cc % 2));
	  cc/=2;
	  i++;
	}

	//printf("\n");
//	send_paket(fd,addr,colors[0],colors[1],colors[2]);

	//lustig blinken lassen - ggf noch anpassen
	for (i=0; i<20; i++) {
		fade_rgb(addr, 255, 0, colors[0],colors[1],colors[2]);
		usleep(50000);
		fade_rgb(addr, 255, 0, 0,0,0);
		usleep(50000);
	}
}

