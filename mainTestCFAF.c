

#include "simpleGFX.h"
#include <string.h>
#include "piBoard.h"
#include "RS485Devices.h"
//#include "cfaf128.h"


/*
                         Main application to test CFAF 128x128 display on RasPi
 */
int main(int argc, char **argv) {
short i;
char data[32];
unsigned short length,x0,y0;
float volts=0.0;

	initializeBoard();
	initDisplay();

/*	drawBox(30,30,100,100,GREEN);
	drawCircle(25,25,20, BLACK);
	for (i=10;i<100;i+=5){
		drawLine(10,10,i,100,RED);
	}

	updateDisplay(0);
*/

	for (i=0;i<50;i++){
		readRS485AnalogRecorderSimple(0x20,0,&volts);
		sprintf(data,"%d: %.2f",i,volts);
		length = strlen(data);
		printLine(data,length,WHITE,BLACK);
	}


return 0;

}
/**
 End of File
*/
