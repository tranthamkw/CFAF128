

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
void main(void)
{
short i;

	initializeBoard();

	initDisplay();

	drawBox(30,30,100,100,GREEN);
	drawCircle(25,25,20, BLACK);

	for (i=10;i<100;i+=5){
	drawLine(10,10,i,100,RED);
	}
	updateDisplay(0);



}
/**
 End of File
*/
