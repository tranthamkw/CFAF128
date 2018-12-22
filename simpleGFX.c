#include "simpleGFX.h"
#include "font.h"
#include "cfaf128.h"
#include <stdlib.h>

unsigned char pixelBuffer[24576];
/*
	128 lines (y-coordinate) * 128 columns (x-coordinate) * 1.5 bytes per pixel = 24576

4 bits per color so 12 bits of information per pixel
image is manipulated in pixelBuffer, then send pixel information in cfaf128.c one, complete line at at time.
pixelBuffer is char, so holds two of the three R, G, B values needed for a  pixel. Algorithm depends on if the pixel x value is even or odd.

Let Line# =0 (y=0)

pixelBuff[k]	k=	 0    1    2   3   4	 5   6    7    8						189  190  191
	k(x even)=								 3*x/2	 +1
	k (x odd)=			integer division trunc decimal-->		 3*x/2   +1
color image data =	(RG)(B  R)(GB)(RG)(B  R)(GB)(RG)(B  R)(GB)  . . .	(RG)	(B  R)	(GB)   . . .	(RG)(B  R)(GB)
Pixel x =		[  0  ][  1  ][  2  ][  3  ][  4  ][  5  ]		[   even  ][  odd  ]		[ 126 ][ 127 ]

for line number  y,  k = 3*x/2 + 192*y

*/

void initDisplay(void){
	unsigned int i,j;
	    initLCD(0);
	// paints splash screen from image[] in "font.h"
	for (i=0;i<128;i++){
			for (j=0;j<192;j++){
				pixelBuffer[j+192*i]=image[j+192*i];
			}
	}

	// update full image
    displayPixels(pixelBuffer, 0, 128, 0);
}

void updateDisplay(unsigned char chan){

    displayPixels(pixelBuffer, 0, 128, chan);

}

void drawBox(short x1, short y1, short x2, short y2, unsigned short color){
	unsigned char i,j;
	for (i=x1;i<x2; i++){
		setPixel(i,y1,color);
		setPixel(i,y2,color);
	}
	for (j=y1;j<y2;j++){
		setPixel(x1,j,color);
		setPixel(x2,j,color);
	}

}


void drawLine(short x0, short y0, short x1, short y1, unsigned short color){
	char steep = (abs(y1-y0) > abs(x1-x0));
	short t,dx,dy,err,ystep;
	if (steep){
		t=x0; // swap x0 and y0
		x0=y0;
		y0=t;
		t=x1; // swap x1 and y1
		x1=y1;
		y1=t;
	}
	if (x0>x1){
		t=x0; //swap x0 and x1
		x0=x1;
		x1=t;
		t=y0; //swap y0 and y1
		y1=y0;
		y0=t;
	}

	dx=x1-x0;
	dy=abs(y1-y0);
	err = dx/2;
	if (y0<y1){
		ystep = 1;
	} else {
		ystep = -1;
	}
	for (;x0<=x1;x0++){
		if (steep){
			setPixel(y0,x0,color);
		} else {
			setPixel(x0,y0,color);
		}
		err -= dy;
		if (err<0){
			y0+=ystep;
			err +=dx;
		}
	}
}


void drawCircle(short x0, short y0, short r, unsigned short color){
	short f = 1- r;
	short ddFx = 1;
	short ddFy = -2*r;
	short x=0;
	short y=r;

	setPixel(x0,y0+r,color);
	setPixel(x0,y0-r,color);
	setPixel(x0+r,y0,color);
	setPixel(x0-r,y0,color);

	while (x<y){
		if (f>=0){
		y--;
		ddFy+=2;
		f+=ddFy;
		}
	x++;
	ddFx+=2;
	f+=ddFx;

	setPixel(x0+x,y0+y,color);
	setPixel(x0-x,y0+y,color);
	setPixel(x0+x,y0-y,color);
	setPixel(x0-x,y0-y,color);
	setPixel(x0+y,y0+x,color);
	setPixel(x0-y,y0+x,color);
	setPixel(x0+y,y0-x,color);
	setPixel(x0-y,y0-x,color);
	}
}

void setPixel (short x0, short y0, unsigned short color){
	unsigned short k,x,y;
	char red, green, blue;
	blue = (char) ((color & 0xF00)>>8);
	green = (char)((color & 0x0F0)>>4);
	red = (char)(color & 0x00F);
	//error trap  0 < x,y < 128
	x = ((unsigned short) x0)& 0x7F;
	y = ((unsigned short) y0)& 0x7F;

	//is x even or odd
	if((x & 0x01) == 1) {
		//odd
		k=(x*3/2);
		pixelBuffer[y*192 + k]=(pixelBuffer[y*192 +k] & 0xF0) | (red);
		pixelBuffer[y*192 + k+1]=(green<<4) | blue;
	} else {
		//even
		k=(x*3/2);
	pixelBuffer[y*192 + k] = (red <<4) | green;
	pixelBuffer[y*192 + k + 1] = (pixelBuffer[y*192 + k+1] & 0x0F) | (blue<<4);
	}
}



/*
void writeText(char column, char* c, char start, char length, unsigned short fcolor, unsigned short bcolor){
     Use this to build a line of text. This only writes to a pixel
      buffer.  Call updateLine to actually write out the pixel data
    
	char i,j,k,s;
    char x;
    x=column * 6;
        for (i=0; i<length;i++){
            for (j=0;j<5;j++){ // x direction
                for (k=0;k<8;k++){  // y direction
                    s=(0x01 << k);
                    if ((myFont[c[i+start]*5+j] & s)==s){
                        setPixel(i*6+j+x, 7-k, fcolor);
                    }else{
                        setPixel(i*6+j+x, 7-k, bcolor);
				}
			}
		}
		for (k=0;k<8;k++) setPixel(i*6+j+x,7-k,bcolor);
	}

}
*/




/*
void printLine(char*c, char len, unsigned short fcolor, unsigned short bcolor){
   
    unsigned short j,i,k;
    unsigned short maxchar=21;
    k=(unsigned short)len / maxchar;
    j=(unsigned short)len % maxchar;
    
   for (i=0;i<k;i++){     
    verticalScroll(lineNum+2);
    clearLine(bcolor);
    writeText(0, c, i*maxchar, maxchar, fcolor,bcolor);
    if (lineNum==0){
           displayPixels(pixelBuffer,0);
    }else{
        displayPixels(pixelBuffer,128-lineNum);
    }
    lineNum+=8;
    lineNum = lineNum%126;
    //126=16*8
   }
    
    verticalScroll(lineNum+2);
    clearLine(bcolor);
    writeText(0, c, k*maxchar,j, fcolor,bcolor);
    if (lineNum==0){
           displayPixels(pixelBuffer,0);
    }else{
        displayPixels(pixelBuffer,128-lineNum);
    }
    lineNum+=8;
    lineNum = lineNum%128;   
}


/*
void itoa (int value, char *result, int base){

	char* ptr=result, *ptr1 = result, tmp_char;
	int tmp_value;
	if (base<2 || base > 16){
	*result = '\0';
		} else {
			do {
				tmp_value=value;
				value /=base;
				*ptr++="FEDCBA9876543210123456789ABCDEF" [15+(tmp_value-value*base)];
			} while (value);

			if (tmp_value<0) *ptr++='-';
			*ptr--='\0';
			while (ptr1<ptr){
				tmp_char=*ptr;
				*ptr-- = *ptr1;
				*ptr1++ = tmp_char;
			}


	}

*/
void charToHex (unsigned int value, char *result, char minPos ){
	char* ptr=result, *ptr1 = result, tmp_char;
	unsigned int tmp_value;
	char i=0;
	do {
	tmp_value=value;
	value /=16;
	*ptr++="0123456789ABCDEF" [(tmp_value-value*16)];
         i++;
	} while (value);

            while (i<minPos){
                *ptr++="0"[0];
                i++;
            }
			*ptr--='\0';
			while (ptr1<ptr){
				tmp_char=*ptr;
				*ptr-- = *ptr1;
				*ptr1++ = tmp_char;
			}
}
