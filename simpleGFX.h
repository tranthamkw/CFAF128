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
void updateDisplay(unsigned char chan);
void charToHex (unsigned int value, char *result, char numPos );
void drawBox(short x1, short y1, short x2, short y2, unsigned short color);
void drawCircle(short x0, short y0, short r, unsigned short color);
void drawLine(short x0, short y0, short x1, short y1, unsigned short color);

void setPixel (short x0, short y0, unsigned short color);

//void writeText(char column, char* c, char start, char length, unsigned short fcolor, unsigned short bcolor);

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



