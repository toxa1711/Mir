/*
 * main.cpp
 *
 *  Created on: Jun 7, 2019
 *      Author: root
 */
#include <stdlib.h> // srand, rand
#include <time.h>   // time
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "bot.h"
#include <math.h>

#define Mountains_CELL 'X'
#define Water_CELL '~'
#define Flowers_CELL '*'
#define Grass_CELL '.'
#define Sheep_CELL 'S'
#define SmallSheep_CELL 's'
#define empty_CELL ' '

#define screenH 58
#define screenW 212

char map[screenH*screenW];

char mapMobs[screenH*screenW];

char String[screenW] = " move:";

int moveCount = 0;

bot sheeps[500];
int sheepsN = 2;
int sheepsStart = 2;



/* No Wolfs as a part of a programm
Wolf wolfs[500];
int wolfsStart = 2;
int wolfsN = 200;
*/


int grassGrow(){

	//increasing grass
	for(int i = 0; i < 10; i++){
		int z = 100; // grass count
		while(z > 0){
			int x = rand() % (screenW-2) + 1;
			int y = rand() % (screenH-2) + 1;
			if(map[x+y*screenW] == '.'){
				if(map[x+1+y*screenW] == ' '){
					map[x+1+y*screenW] = '.';
					break;
				}
				if(map[x+(y-1)*screenW] == ' '){
					map[x+(y-1)*screenW] = '.';
					break;
				}
				if(map[x-1+y*screenW] == ' '){
					map[x-1+y*screenW] = '.';
					break;
				}
				if(map[x+(y+1)*screenW] == ' '){
					map[x+(y+1)*screenW] = '.';
					break;
				}
			}
				z--;
		}
	}
	//increasing grass


	//promoting grass to flowers
	for(int i = 0; i < 1; i++){
		int z = 2; // grass count
			while(z > 0){
					int x = rand() % (screenW-2) + 1;
					int y = rand() % (screenH-2) + 1;
					if(map[x+y*screenW] == '.'){
						map[x+y*screenW] = '*';
					}
					z--;
			}
	}
	//promoting grass to flowers


	//creating random grass spots
	if(rand() % 4 == 0){
		for(int i = 0; i < 1; i++){
				int z = 1;
					while(z > 0){
							int x = rand() % (screenW-2) + 1;
							int y = rand() % (screenH-2) + 1;
							if(map[x+y*screenW] == ' '){
								map[x+y*screenW] = '.';
							}
							z--;
					}
			}
	}
	//creating random grass spots

	return 0;
}

int screenUpdate(){
	for(int j = 0; j < screenH; j++){
		for(int i = 0; i < screenW; i++){
			if(mapMobs[i+j*(screenW)] == ' '){
				if(map[i+j*(screenW)] == 'X'){
					printf("\033[1;30m");
					printf("\033[1;100m");
					putchar(map[i+j*(screenW)]);
					printf("\033[1;0m");
				}
				else if(map[i+j*(screenW)] == '.'){
					printf("\033[1;32m");
					printf("\033[1;40m");
					putchar(map[i+j*(screenW)]);
					printf("\033[1;0m");
				}
				else if(map[i+j*(screenW)] == '*'){
					printf("\033[1;33m");
					printf("\033[1;40m");
					putchar(map[i+j*(screenW)]);
					printf("\033[1;0m");
				}
				else if(map[i+j*(screenW)] == '~'){
					printf("\033[1;34m");
					printf("\033[1;44m");
					//putchar(map[i+j*(screenW)]);
					putchar(' ');
					printf("\033[1;0m");
				}
				else if(map[i+j*(screenW)] == 'W'){
					printf("\033[1;31m");
					putchar(map[i+j*(screenW)]);
					printf("\033[1;0m");
				}
				else{
					printf("\033[1;40m");
					//printf("\033[1;27m");
					putchar(map[i+j*(screenW)]);
					printf("\033[1;0m");
				}
			}
			else{
				if(mapMobs[i+j*(screenW)] == 'W'){
					printf("\033[1;31m");
					putchar(mapMobs[i+j*(screenW)]);
					printf("\033[1;0m");
				}
				else if(mapMobs[i+j*(screenW)] == 'X'){
					printf("\033[1;30m");
					printf("\033[1;100m");
					putchar(mapMobs[i+j*(screenW)]);
					printf("\033[1;0m");
				}
				else{
					putchar(mapMobs[i+j*(screenW)]);
				}

			}
		}
		putchar('\n');
	}
	for(int i = 0; i < screenW; i++){
		putchar(String[i]);
	}
	putchar('\n');
	for(int j = 0; j < screenH+2; j++){
		printf("\033[1A");
	}
	return 0;
}

int updateString(){
	for(int i = 0; i < 5; i++){
		String[i+7] = (moveCount / (int)(pow(10, (4-i)))) % 10 + '0';
	}
	return 0;
}

int generateMap(){

	//filling object layer
	for(int j = 0; j < screenH; j++){
			for(int i = 0; i < screenW; i++){
				mapMobs[j*screenW+i] = ' ';
				//putchar('X');
			}
		}
	//filling object layer

	//filling world with water
	for(int j = 0; j < screenH; j++){
		for(int i = 0; i < screenW; i++){
			map[j*screenW+i] = '~';
			//putchar('X');
		}
	}
	//filling world with water

	//LAND

	for(int ff = 0;ff < 100; ff++){

	//creating random land spots
		if(rand() % 4 == 0){
			for(int i = 0; i < 1; i++){
					int z = 1;
						while(z > 0){
								int x = rand() % (screenW-2) + 1;
								int y = rand() % (screenH-2) + 1;
								if(map[x+y*screenW] == '~'){
									map[x+y*screenW] = ' ';
								}
								z--;
						}
				}
		}
		//creating random land spots

		//increasing lands
			for(int i = 0; i < 100; i++){ //max grass per move
				int z = 100; // randow trys
				while(z > 0){
					int x = rand() % (screenW-2) + 1;
					int y = rand() % (screenH-2) + 1;
					if(map[x+y*screenW] == ' '){
						if(map[x+1+y*screenW] == '~'){
							map[x+1+y*screenW] = ' ';
							break;
						}
						if(map[x+(y-1)*screenW] == '~'){
							map[x+(y-1)*screenW] = ' ';
							break;
						}
						if(map[x-1+y*screenW] == '~'){
							map[x-1+y*screenW] = ' ';
							break;
						}
						if(map[x+(y+1)*screenW] == '~'){
							map[x+(y+1)*screenW] = ' ';
							break;
						}
					}
						z--;
				}
			}
			//increasing lands
	}

	//LAND


	//Mountains

	for(int ff = 0;ff < 50; ff++){

		//creating random land spots
			if(rand() % 2 == 0){
				for(int i = 0; i < 1; i++){
						int z = 1;
							while(z > 0){
									int x = rand() % (screenW-2) + 1;
									int y = rand() % (screenH-2) + 1;
									if(map[x+y*screenW] == ' '){
										map[x+y*screenW] = 'X';
									}
									z--;
							}
					}
			}
			//creating random land spots

			//increasing lands
				for(int i = 0; i < 100; i++){ //max grass per move
					int z = 10; // randow trys
					while(z > 0){
						int x = rand() % (screenW-2) + 1;
						int y = rand() % (screenH-2) + 1;
						if(map[x+y*screenW] == 'X'){
							if(map[x+1+y*screenW] == ' '){
								map[x+1+y*screenW] = 'X';
								break;
							}
							if(map[x+(y-1)*screenW] == ' '){
								map[x+(y-1)*screenW] = 'X';
								break;
							}
							if(map[x-1+y*screenW] == ' '){
								map[x-1+y*screenW] = 'X';
								break;
							}
							if(map[x+(y+1)*screenW] == ' '){
								map[x+(y+1)*screenW] = 'X';
								break;
							}
						}
							z--;
					}
				}
				//increasing lands
		}

	//Mountains

	for(int g = 0; g < 30; g++){
		grassGrow();
	}

	return 0;
}

int MapLoad(){

	for(int j = 0; j < screenH; j++){
				for(int i = 0; i < screenW; i++){
					map[j*screenW+i] = ' ';
					//putchar('X');
				}
			}

	FILE *buff = fopen("../map1.txt", "r");
	int i = 0;
	char c;
	while((c = getc(buff)) != EOF){
		if(c != '\n'){
			if(c != '0'){
				map[i] = c;
			}
			else{
				map[i] = ' ';
			}
			i++;
		}
		else{
			i += screenW - 190;
		}
	}
	fclose(buff);
	return 0;
}

int setupMobs(){
	for(int i = 0; i < sheepsN; i++){
		sheeps[i].initialize('W', " .*");
		sheeps[i].setup(rand() % screenW, rand() % screenH);
		//sheeps[i].setup(100, 5);
		mapMobs[sheeps[i].x+sheeps[i].y*screenW] = sheeps[i].symbol;
	}
	sheeps[sheepsN].initialize('u', "~");
	sheeps[sheepsN].setup(rand() % screenW, rand() % screenH);
	mapMobs[sheeps[sheepsN].x+sheeps[sheepsN].y*screenW] = sheeps[sheepsN].symbol;
	sheepsN++;
	sheeps[sheepsN].Hunger = 1000;
	sheeps[sheepsN].symbolDead = 'n';

	return 0;
}

int moveMobs(){

	for(int i = 0; i < sheepsN; i++){

		if(sheeps[i].dead == 1){
			return 0;
		}

		if(sheeps[i].Hunger < 1){
			sheeps[i].die();
			mapMobs[screenW*sheeps[i].y+sheeps[i].x] = sheeps[i].symbolDead;
		}
		else{
			sheeps[i].Hunger--;
		}

		int direction = sheeps[i].getSolution("hui");

		int x,y;

		x = sheeps[i].x;
		y = sheeps[i].y;

		if((x+1 < screenW) && direction == 0){
			x = sheeps[i].x + 1;
			y = sheeps[i].y;
		}
		if((y > 0) && direction == 1){
			x = sheeps[i].x;
			y = sheeps[i].y - 1;
			}
		if((x-1 > 0) && direction == 2){
			x = sheeps[i].x - 1;
			y = sheeps[i].y;
			}
		if((y+1 < screenH) && direction == 3){
			x = sheeps[i].x;
			y = sheeps[i].y + 1;
			}

		int z = 0;
		while(*(sheeps[i].allow + z) != '\0'){
			if(map[x+y*screenW] == *(sheeps[i].allow + z)){
				mapMobs[screenW*sheeps[i].y+sheeps[i].x] = ' ';
				sheeps[i].x = x;
				sheeps[i].y = y;
				mapMobs[x+y*screenW] = sheeps[i].symbol;
				break;
			}
			z++;
		}
		/*else{

		}*/

	}

	/*for(int i = 0; i < sheepsN; i++){
		if(sheeps[i].Hunger > 1000){
			for(int z = 0; z < sheepsN; z++){
				if(sheeps[z].dead == 1){
					sheeps[z].setup(sheeps[i].x-1, sheeps[i].y);
					sheeps[z].dead = 0;
					sheeps[z].Hunger = 25;
					sheeps[i].Hunger -= 500;
					break;
				}
			}
		}
			if(sheeps[i].Hunger > 0){
				sheeps[i].Hunger--;
				int x = 0;
				int y = 0;

				int flag = 0;

				x = sheeps[i].x;
				y = sheeps[i].y;

				for(int j = 1; j < 5;j++){
					if((x+j < screenW) && ((map[x+j+(y)*screenW] == '.') || (map[x+j+(y)*screenW] == '*'))){
						x = sheeps[i].x + 1;
						y = sheeps[i].y;
						flag = 1;
						break;
					}
					else if((y-j > 0) && ((map[x+(y-j)*screenW] == '.') || (map[x+(y-j)*screenW] == '*'))){
						x = sheeps[i].x;
						y = sheeps[i].y - 1;
						flag = 1;
						break;

					}
					else if((x-j > 0) && ((map[x-j+(y)*screenW] == '.') || (map[x-j+(y)*screenW] == '*'))){
						x = sheeps[i].x - 1;
						y = sheeps[i].y;
						flag = 1;
						break;
					}
					else if((y+j < screenH) && ((map[x+(y+j)*screenW] == '.') || (map[x+(y+j)*screenW] == '*'))){
						x = sheeps[i].x;
						y = sheeps[i].y + 1;
						flag = 1;
						break;
					}
				}

				if(flag == 0){
					int direction = rand() % 4;
					if((x+1 < screenW) && direction == 0){
						x = sheeps[i].x + 1;
						y = sheeps[i].y;
					}
					if((y-1 > 0) && direction == 1){
						x = sheeps[i].x;
						y = sheeps[i].y - 1;
						}
					if((x-1 > 0) && direction == 2){
						x = sheeps[i].x - 1;
						y = sheeps[i].y;
						}
					if((y+1 < screenH) && direction == 3){
						x = sheeps[i].x;
						y = sheeps[i].y + 1;
						}
				}

				if((map[x+y*screenW] == 'X') || (map[x+y*screenW] == '~') || (map[x+y*screenW] == 'S')){

				}
				else{

					if((map[x+y*screenW] == '*')){
						sheeps[i].Hunger += 20;
					}

					if((map[x+y*screenW] == '.')){
						sheeps[i].Hunger += 10;
					}

					map[sheeps[i].x+sheeps[i].y*screenW] = ' ';
					sheeps[i].x = x;
					sheeps[i].y = y;
					map[x+y*screenW] = 'S';
				}
			}
			else {
				if(sheeps[i].dead == 0){
					sheeps[i].dead = 1;
					map[sheeps[i].x+sheeps[i].y*screenW] = ' ';
				}
			}
	}*/
	return 0;
}

int move(){
	moveMobs();
	moveCount++;
	return 0;
}

int main(){
	srand(time(0));
	printf("\033[2J\033[1;1H");
	generateMap();
	//MapLoad();
	setupMobs();
	screenUpdate();
	while(1){
		move();
		grassGrow();
		updateString();
		usleep(100000);
		screenUpdate();
		//getchar();
	}

	return 0;
}
