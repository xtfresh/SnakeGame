//Montek Singh
#include "myLib.h"
#include "gameOver.h"
#include "startScreen.h"

u16 *videoBuffer = (u16*) 0x6000000;

void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}
/*
void drawRect(int row, int col, int height, int width, u16 color)
{
    int r,c;
    for(r=0; r<height; r++)
    {
        for(c=0; c<width; c++)
        {
            setPixel(row+r, col+c, color);
        }
    }
} */

void drawRect(int row, int col, int height, int width, u16 color)
{
    int r;
    for(r=0; r<height; r++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
        DMA[3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
        
    }
}

void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}

void delay(int n)
{
    int i = 0;
    volatile int x=0;
    for(i=0; i<n*10000; i++)
    {
        x++;
    }
}


void clearScreen(){
	u16 black = RGB(0,0,0);
	DMA[3].src = &black;
       	DMA[3].dst = videoBuffer;
        DMA[3].cnt = 38400 | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED | DMA_ON;
	
}

void start(int *seed){
	DMA[3].src = startScreen;
        DMA[3].dst = videoBuffer;
       	DMA[3].cnt = 38400 | DMA_ON;
	while(!KEY_DOWN_NOW(BUTTON_START))
		*seed = *seed + 1;
	clearScreen();
}
