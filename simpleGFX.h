/* 
 * File:   simpleGFX.h
 * Author: tranthamkw
 *
 * Created on June 30, 2018, 7:10 PM
 */


// index of color codes
// it.labelpartners.com/pantone_coated_table.html
// htmlcolorcodes.com


void initDisplay(void);
void charToHex (unsigned int value, char *result, char numPos );

void setPixel (char x, char y, unsigned short color);

//void writeText(char column, char* c, char start, char length, unsigned short fcolor, unsigned short bcolor);
void updateLine(char line, unsigned char chan);

//void clearLine(unsigned short color);
//void printLine(char*c, char len, unsigned short fcolor, unsigned short bcolor);

// 12 bits per pixel
// each pixel RGB,4 bits each
#define RED 0xF00
#define BLUE 0x00F
#define CYAN 0x0FF
#define GREEN 0x0F0
#define WHITE 0xFFF
#define BLACK 0x000
#define YELLOW 0xFF0



