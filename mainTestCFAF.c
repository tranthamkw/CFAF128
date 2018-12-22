

#include "simpleGFX.h"
#include <string.h>
#include "piBoard.h"
#include "cfaf128.h"



char outText[128];
/*
void drawStartupScreen(void){
    char k;
    
    clearLine(BLACK);
    strcpy(outText,"RS485Address:");
    k=strlen(outText);
    writeText(2,outText,0,k,CYAN,BLACK);
    charToHex(50,outText,2);
    k=strlen(outText);
    writeText(17,outText,0,k,CYAN,BLACK);
    updateLine(1);
    
    clearLine(BLACK);
    strcpy(outText," = RS485 to GPIB =");
    k=strlen(outText);
    writeText(0,outText,0,k,YELLOW,BLACK);
    updateLine(3);
    clearLine(BLACK);
    strcpy(outText,"     = BRIDGE =");
    k=strlen(outText);
    writeText(0,outText,0,k,YELLOW,BLACK);
    updateLine(2);
    
}


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


	if (argc==4){
		strcpy(data,argv[3]);
		x0=atoi(argv[1]);
		y0=atoi(argv[2]);
		length = strlen(data);
		writeText(x0,y0,data,length,BLACK);
	} else {
	printf("usage ./mainTestCFAF <x0> <y0> \"text to display\"\n");
	}

	updateDisplay(0);

return 0;

}
/**
 End of File
*/
