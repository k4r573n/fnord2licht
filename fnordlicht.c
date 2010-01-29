/* fnordlicht.c */

/*	hier sind die Funktionen zum ansteuern eines
 *	Fnordlichts mit der Firmware 0.3 drin
 * 
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */

extern int fd;

/** sendet ein Paket zum farben wechseln des Fnordlichts mit der Firmware 0.3
  */
void fade_rgb(int addr, int step, int delay, int red, int green, int blue) {
	fprintf(stdout, "send Package FADE_RGB to %d \n", fd);


	/*send commands*/
	unsigned int t=0;
	char* a=(char*)&t;
	int n;//write retrun value

	//sendet die addresse (255 = broadcast)
	fprintf(stdout, "byte 0 (addr) : %d \n", addr);
	t = addr;
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);
 
	//send the command
	t = 0x01;
	fprintf(stdout, "byte 1 (cmd - now fade_rgb) : 0x%02x \n", t);
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);

	//send step
	t = step;
	fprintf(stdout, "byte 2 (step) : 0x%02x \n", t);
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);

	//send delay
	t = delay;
	fprintf(stdout, "byte 3 (delay) : 0x%02x \n", t);
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);

	//send red
	t = red;
	fprintf(stdout, "byte 4 (red) : %03d \n", t);
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);

	//send green
	t = green;
	fprintf(stdout, "byte 5 (green) : %03d \n", t);
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);

	//send blue
	t = blue;
	fprintf(stdout, "byte 6 (blue) : %03d \n", t);
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);

	t = 0x00;
	a = (char*)&t;
	for (int i=7; i<=14; i++) {
	 	//send some bytes to complete the pakege
		fprintf(stdout, "byte %2d (dosen't matter): 0x%02x \n", i,t);
		n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
		if (n < 0)
			fputs("write() of 1 bytes failed!\n", stderr);
	}
}

/** sendet ein Paket zum ausschalten des Fnordlichts mit der Firmware 0.3
  */
void powerdown(int addr) {
	fprintf(stdout, "send Package Powerdown to %d \n", fd);


	/*send commands*/
	unsigned int t=0;
	char* a=(char*)&t;
	int n;

	//sendet die addresse (255 = broadcast)
	fprintf(stdout, "byte 0 (addr) : %d \n", addr);
	t = addr;
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);
 
	//sendet den ausschalt code
	t = 0x0c;
	fprintf(stdout, "byte 1 (cmd - now powerdown) : 0x%02x \n", t);
	a = (char*)&t;
	n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
	if (n < 0)
		fputs("write() of 1 bytes failed!\n", stderr);

	t = 0x00;
	a = (char*)&t;
	for (int i=2; i<=14; i++) {
	 //send some bytes to complete the pakege
		fprintf(stdout, "byte %2d (dosen't matter): 0x%02x \n", i,t);
		n = write(fd, a, 1); //returns -1 on fail otherwise bytes send
		if (n < 0)
			fputs("write() of 1 bytes failed!\n", stderr);
	}
}
