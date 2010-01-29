/* help.c */

/*
 * Here will the help dialog be
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */


void show_help() {
	printf( "*********************\n" );
	printf( "**  Fnord 2 licht  **\n" ); 
	printf( "*********************\n\n" );
	printf( "a tool to control your Fnordlicht (a DIV Hardware see www.lochraster.de)\n\n" );
	printf( "fnord2licht -a <address> -r <red> -g <green> -b <blue> -d <device> -v -h\n\n" );
	printf( "all Parmeters are optional\n" );
	printf( "\t-a <address> default is 255 \n\t\t255 and 0 are broadcast adresses at the moment is it possible to \n\t\taddress 1-8 Ligths. The adressing based on dual numbers: \n\t\t- 1 is Light 1 \n\t\t- 2 is Light 2 \n\t\t- 3 is light 1 and 2 \n\t\t- 4 is light 3 and so on.\n\t\t After a address is send all following commands are send to these adress\n\n" );
	printf( "\t-d <device> default is set to /dev/ttyUSB0\n\t\t it's the device were the fnordlicht is connected\n" );
}

