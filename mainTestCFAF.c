

#include "simpleGFX.h"
#include <string.h>
#include "piBoard.h"
//#include "cfaf128.h"


/*
                         Main application to test CFAF 128x128 display on RasPi
 */
int main(int argc, char **argv) {
short i;
char data[32];
unsigned short length,x0,y0;

	initializeBoard();
	initDisplay();
	drawBox(30,30,100,100,GREEN);
	drawCircle(25,25,20, BLACK);
	for (i=10;i<100;i+=5){
		drawLine(10,10,i,100,RED);
	}

	updateDisplay(0);

	if (argc==4){
		strcpy(data,argv[3]);
		x0=atoi(argv[1]);
		y0=atoi(argv[2]);
		length = strlen(data);
		printLine(data,length,WHITE,BLACK);
//		writeText(x0,y0,data,length,BLACK);

	} else {
	printf("usage ./mainTestCFAF <x0> <y0> \"text to display\"\n");
	}


return 0;

}
/**
 End of File
*/
