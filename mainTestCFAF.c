

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
	initDisplay(0);
	initDisplay(1);

if (argc==2){
	strcpy(data, argv[1]);
	if(loadBMP(data)) updateDisplay(0);
}

	clearCanvas(BLACK);
	drawBox(30,30,100,100,GREEN);
	drawCircle(25,25,20, WHITE);
	for (i=10;i<100;i+=5){
		drawLine(10,10,i,100,RED);
	}

	updateDisplay(1);


	for (i=0;i<50;i++){
		readRS485AnalogRecorderSimple(0x20,0,&volts);
		sprintf(data,"%d: %.2f",i,volts);
		length = strlen(data);
		printLine(data,length,WHITE,BLACK,1);
	}


return 0;

}
/**
 End of File
*/
