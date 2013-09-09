//Montek Singh




#include "myLib.h"
#include <stdlib.h>
#include <debugging.h>
#include "gameOver.h"
#include "text.h"
#include <stdio.h>


typedef struct 
{
	int row;
	int col;
    	u16 color;
} SNAKE;

typedef struct
{
	int row;
	int col;
}POINT;



int main(){

	REG_DISPCNT = BG2_EN | MODE_3;
	int seed = 0;
	start(&seed);
	srand(seed);
	SNAKE head;
	POINT points[50];
	head.row = 60;
	head.col = 60;
	head.color = GREEN;
	int* mPtr = &head.col;
	int moveAmount = 5;
	int noFruit = 1;
	int pixelRow = 0;
	int pixelCol = 0;
	int apples = 0;
	char buffer[41];
	
	while(1){
		
		if(KEY_DOWN_NOW(BUTTON_UP)){
			mPtr = &head.row;
			moveAmount = -5;
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN)){
			mPtr = &head.row;
			moveAmount = 5;
			moveAmount = 5;
				
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT)){
			mPtr = &head.col;
			moveAmount = -5;
			moveAmount = -5;
				
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT)){
			mPtr = &head.col;
			moveAmount = 5;
			if(head.col >= 230)
			moveAmount = 5;
		}
		if(KEY_DOWN_NOW(BUTTON_SELECT)){
			clearScreen();
			main();
		}
		//if there is no fruit on screen, draw a fruit at a random location
		//set noFruit to false
		//add location of fruit to an array so the next time player steps on that location, game ends
		if(noFruit){
			pixelRow = (rand()%30)*5;
			pixelCol = (rand()%47)*5;
			drawRect(pixelRow, pixelCol, 5, 5, YELLOW);
			noFruit = 0;	
			points[apples].row = pixelRow;
			points[apples].col = pixelCol;	
		}
		//if the player is on top of the fruit, increase score
		//else erase the location(prev player position)
		if(head.row == pixelRow && head.col == pixelCol){
			noFruit = 1;	
			apples++;	
			drawRect(head.row, head.col, 5, 5, RED);
		}else{
			drawRect(head.row, head.col, 5, 5, BLACK);//erase end
			for(int i = 0; i < apples; i++){
				//if player resteps on a prev fruit location
				if(head.row == points[i].row && head.col == points[i].col){
					endScreen();			
				}		
			}
		}
		sprintf(buffer, "Score: %d", apples);
		//is player is out of bounds i.e collides with wall end game
		if(head.row < 0 || head.row > 150 || head.col < 0 || head.col > 235)
			endScreen();
		//increment what ever direction the player is moving in
		(*mPtr) += moveAmount;
		drawRect(head.row, head.col, 5, 5, head.color);
		
		drawRect(150, 48, 8, 24, BLACK);
        	drawString(150, 5, buffer, RED);		
		delay(1);

	}
}

void endScreen(){
	DMA[3].src = gameOver;
        DMA[3].dst = videoBuffer;
        DMA[3].cnt = 38400 | DMA_ON;
	while(!KEY_DOWN_NOW(BUTTON_SELECT));
	main();
}



