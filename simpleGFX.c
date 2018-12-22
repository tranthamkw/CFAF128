#include "simpleGFX.h"
#include "font.h"
#include "cfaf128.h"



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

    Fill_LCD(0,0,0,0);
   // paints splash screen from image[] in "font.h"
	for (i=0;i<128;i++){
			for (j=0;j<192;j++){
				pixelBuffer[j+192*i]=image[j+192*i];
			}
	}

// update full image
    displayPixels(pixelBuffer, 0, 128, 0);

}

void setPixel (char x, char y, unsigned short color){
	unsigned short k;
	char red, green, blue;
	blue = (char) ((color & 0xF00)>>8);
	green = (char)((color & 0x0F0)>>4);
	red = (char)(color & 0x00F);
	//is j even or odd
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
void clearLine(unsigned short color){
    int j,i,k;
    char Tcolor[3];
    char red, green, blue;
	red = (char) ((color & 0xF00)>>8);
	green = (char)((color & 0x0F0)>>4);
	blue = (char)(color & 0x00F);
  Tcolor[0]=(blue <<4) | green;
  Tcolor[1]=(red <<4) | blue;
  Tcolor[2]=(green <<4) | red;
  
  for (k=0;k<8;k++){
       for (i=0; i<64;i++){
           for (j=0;j<3;j++){
           pixelBuffer[3*i+j + k*192]=Tcolor[j];
          }
            
        }
   }
}

*/

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
