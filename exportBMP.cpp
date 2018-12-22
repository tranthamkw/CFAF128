/*
*  test area for using bitmap.cpp
*
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "Bitmap.cpp"


using namespace std;



int main (int nNumberofArgs, char* argv[]){
   
FILE *fp;
char fileName[32];
unsigned int width,height,i,j;
unsigned int color;
unsigned char red, green, blue;
unsigned char pixel[3];


 
if (nNumberofArgs==3){
      cout<<"Number of Args "<<nNumberofArgs<<"\n";
      //load bitmap
      Bitmap* sourcebmap = new Bitmap(argv[1]);

	strcpy(fileName,argv[2]);
	fp=fopen(fileName,"w");

	height=sourcebmap->height;
	width=sourcebmap->width;
	printf("height %d \twidth %d\n",height,width);
	
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
		color=sourcebmap->getPixel(i,j);
		blue = ((color&0xF00000)>>20);
		green = (color&0x00F000)>>12;
		red = (color&0x0000F0)>>4;
		//printf("%02X,%02X,%02X  ",red,green,blue);

		if ((j & 0x01) ==1){
		//odd
			pixel[1] = (pixel[1] & 0xF0) | red;
			pixel[2]= (green<<4) | blue;
		printf("%02X%02X%02X,",pixel[0],pixel[1],pixel[2]);
		fprintf(fp,"%d,%d,%d,",pixel[0],pixel[1],pixel[2]);
		} else {
		//even
			pixel[0]=(red<<4) | green;
			pixel[1]= (pixel[1] & 0x0F) | (blue<<4);
		}		

		if ((j % 64) ==0) {
		printf("\n");
		fprintf(fp,"\n");
	}

      }
	}

	fclose(fp); 
}
return 0;
}
