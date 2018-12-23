/*
*  test area for using bitmap.cpp
*
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "Bitmap.cpp"
#include <stdio.h>
#include <string.h>

using namespace std;



int main (int nNumberofArgs, char* argv[]){


FILE *fp;
char fileName[32];
unsigned int width,height,i,j;
unsigned int color;
unsigned char red, green, blue;
unsigned char pixel[3];

 
if (nNumberofArgs==2){
      cout<<"Number of Args "<<nNumberofArgs<<"\n";
      //load bitmap
      Bitmap* sourcebmap = new Bitmap(argv[1]);

	if(sourcebmap->loaded){


	height=sourcebmap->height;
	width=sourcebmap->width;
	printf("height %d \twidth %d\n",height,width);

	} else {
	printf("error loading bmp\n");
	}
	} else {

	printf("Usage::  ./openBMP <source.bmp>\n");

}

return 0;
}
