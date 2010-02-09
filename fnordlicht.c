/* fnordlicht.c */

/*	hier sind die Funktionen zum ansteuern eines
 *	Fnordlichts mit der Firmware 0.3 drin
 * 
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */

extern int fd;
int byte_index=0;

//sends a byte of bits to the device fd
void send_byte(unsigned int value, char* comment) {
	fprintf(stdout, "byte %d (%s) \n",byte_index,comment);
	char* a = (char*)&value;
	if (0 > write(fd, a, 1)) { //returns -1 on fail otherwise bytes send
	  fprintf(stderr, "write() of byte %d failed!\n", byte_index);
	}
	byte_index++;
}


/** sendet ein Paket zum farben wechseln des Fnordlichts mit der Firmware 0.3
  */
void fade_rgb(int addr, int step, int delay, int red, int green, int blue) {
	fprintf(stdout, "send Package FADE_RGB to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x01,"cmd fade_rgb");
	//send step
	send_byte( step,"step" );
	//send delay
	send_byte(delay,"delay");
	//send red
	send_byte(red,"red");
	//send green
	send_byte(green,"green");
	//send blue
	send_byte(blue,"blue");
	for (int i=7; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** sendet ein Paket zum farben wechseln des Fnordlichts mit der Firmware 0.3
  */
void fade_hsv(int addr, int step, int delay, int hue, int saturation, int value) {
	fprintf(stdout, "send Package FADE_HSV to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x02,"cmd fade_hsv");
	//send step
	send_byte( step,"step" );
	//send delay
	send_byte(delay,"delay");
	//send hue (2 bytes) TODO: convert the int hue = 0 - 360; to two bytes
	send_byte(hue,"hue byte 1");
	send_byte(hue,"hue byte 2");
	//sends saturation
	send_byte(saturation,"saturation");
	//send value of brigthness
	send_byte(value,"brightness");
	for (int i=8; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** ends a package to save a rgb color  */
void save_rgb(int addr, int slot, int step, int delay, int pause, int red, int green, int blue) {
	fprintf(stdout, "send Package SAVE_RGB to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x03,"cmd save_rgb");
	//send slot
	send_byte( slot,"slot" );
	//send step
	send_byte(step,"step");
	//send delay
	send_byte(delay,"delay");
	//send pause (2 bytes) TODO: convert the int pause = 0 - 360; to two bytes
	send_byte(pause,"pause byte 1");
	send_byte(pause,"pause byte 2");
	//sends red
	send_byte(red,"red");
	//send green
	send_byte(green,"green");
	//send blue
	send_byte(blue,"blue");
	for (int i=10; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** ends a package to save a hsv color  */
void save_hsv(int addr, int slot, int step, int delay, int pause, int hue, int saturation, int value) {
	fprintf(stdout, "send Package SAVE_HSV to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x04,"cmd save_hsv");
	//send slot
	send_byte( slot,"slot" );
	//send step
	send_byte(step,"step");
	//send delay
	send_byte(delay,"delay");
	//send pause (2 bytes) TODO: convert the int pause = 0 - 360; to two bytes
	send_byte(pause,"pause byte 1");
	send_byte(pause,"pause byte 2");
	//send hue (2 bytes) TODO: convert the int hue = 0 - 360; to two bytes
	send_byte(hue,"hue byte 1");
	send_byte(hue,"hue byte 2");
	//send saturation
	send_byte(saturation,"saturation");
	//send value
	send_byte(value,"value of brightness");
	for (int i=10; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** ends a package to save the current color  */
void save_current(int addr, int slot, int step, int delay, int pause) {
	fprintf(stdout, "send Package SAVE_CURRENT to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x05,"cmd save_current");
	//send slot
	send_byte( slot,"slot" );
	//send step
	send_byte(step,"step");
	//send delay
	send_byte(delay,"delay");
	//send pause (2 bytes) TODO: convert the int pause = 0 - 360; to two bytes
	send_byte(pause,"pause byte 1");
	send_byte(pause,"pause byte 2");
	for (int i=7; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** sends a package to change the fade offset  */
void config_offsets(int addr, int step, int delay, int hue, int saturation, int value) {
	fprintf(stdout, "send Package CONFIG_OFFSETS to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x06,"cmd config_offsets");
	//send step
	send_byte(step,"step");
	//send delay
	send_byte(delay,"delay");
	//send hue (2 bytes) TODO: convert the int hue = 0 - 360; to two bytes
	send_byte(hue,"hue byte 1");
	send_byte(hue,"hue byte 2");
	//send saturation
	send_byte(saturation,"saturation");
	//send value of brightness
	send_byte(value,"value of briightness");
	for (int i=8; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** sends a package to start a program  */
void start_program(int addr, int program, int params[10]) {
	fprintf(stdout, "send Package START_PROGRAM to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x07,"cmd start_program");
	//send program
	send_byte(program,"program");
	for (int i=3; i<=11; i++){
  	//send params
	  send_byte(params[i-3],"params");
	}
	for (int i=12; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** sends a package to stop all fadings */
void stop(int addr,int fade) {
	fprintf(stdout, "send Package STOP to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x08,"cmd - stop");
	//sends fade (0 / 1)
	send_byte(fade,"fade");
	for (int i=3; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** sendet ein Paket zum ausschalten des Fnordlichts mit der Firmware 0.3
  */
void powerdown(int addr) {
	fprintf(stdout, "send Package Powerdown to %d \n", fd);

  byte_index=0;//init new package

	//sendet die addresse (255 = broadcast)
	send_byte(addr,"addr");
	//send the command
	send_byte(0x01,"cmd - powerdown");
	for (int i=2; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(0x00,"dosen't matter");
	}
}

/** sendet ein Paket zum konfigurieren des Standard programms des Fnordlichts mit der Firmware 0.3
  */
void config_startup(int addr,int mode, int program, int parameters[10]) {
	fprintf(stdout, "send Package config_startup to %d \n", fd);

  byte_index=0;//init new package

	//sends the address (255 = broadcast)
	send_byte(addr,"addr");
	//sends the command
	send_byte(0x0b,"cmd - config_startup");
	//sends mode (0 or 1)
	send_byte( mode,"mode" );
	//sends program
	send_byte(program,"program");

	//TODO: send paramets and check the length
	for (int i=4; i<=14; i++) {
	 	//send some bytes to complete the pakege
		send_byte(parameters[i-4],"parametes"); //TODO: line is maybe incorrect
	}
}


