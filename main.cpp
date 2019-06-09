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
#include "Sheep.h"
#include "Wolf.h"
#include <math.h>

#define Mountains_CELL 'X'
#define Water_CELL '~'
#define Flowers_CELL '*'
#define Grass_CELL '.'
#define Sheep_CELL 'S'
#define SmallSheep_CELL 's'
#define empty_CELL ' '

#define screenH 60
#define screenW 212

char map[screenH*screenW];
char String[screenW] = " move:";

int moveCount = 0;

Sheep sheeps[500];
int sheepsN = 500;
int sheepsStart = 2;

Wolf wolfs[500];
int wolfsStart = 2;
int wolfsN = 200;

int screenUpdate(){
	for(int j = 0; j < screenH; j++){
		for(int i = 0; i < screenW; i++){
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
				putchar(map[i+j*(screenW)]);
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
		putchar('\n');
	}
	for(int i = 0; i < screenW; i++){
		putchar(String[i]);
	}
	for(int j = 0; j < screenH+1; j++){
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
	for(int j = 0; j < screenH; j++){
			for(int i = 0; i < screenW; i++){
				map[j*screenW+i] = '.';
				//putchar('X');
			}
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

int setupSheeps(){
	for(int i = 0; i < sheepsStart; i++){
		sheeps[i].setup(rand() % screenW, rand() % screenH);
		//sheeps[i].setup(100, 5);
		map[sheeps[i].x+sheeps[i].y*screenW] = 'S';
	}
	return 0;
}

int setupWolfs(){
	for(int i = 0; i < wolfsStart; i++){
			wolfs[i].setup(rand() % screenW, rand() % screenH);
			//sheeps[i].setup(100, 5);
			map[wolfs[i].x+wolfs[i].y*screenW] = 'W';
		}
	return 0;
}

int groundSheepMovable(char f){
	if((f == ' ') || (f == '.') || (f == '*')){
		return 1;
	}
	return 0; //yes
}

int grassGrow(){
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
			/*if(map[x+y*screenW] == '*'){
				if(map[x+1+y*screenW] == '.'){
					map[x+1+y*screenW] = '*';
					break;
				}
				if(map[x+(y-1)*screenW] == '.'){
					map[x+(y-1)*screenW] = '*';
					break;
				}
				if(map[x-1+y*screenW] == '.'){
					map[x-1+y*screenW] = '*';
					break;
				}
				if(map[x+(y+1)*screenW] == '.'){
					map[x+(y+1)*screenW] = '*';
					break;
				}
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
				}*/
				/*if(map[x+y*screenW] == '.'){
					map[x+y*screenW] = '*';
					break;
				}
			}*/
				z--;
		}
	}
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
	if(rand() % 4 == 0){
		for(int i = 0; i < 1; i++){
				int z = 1; // grass count
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
	return 0;
}

int moveSheeps(){
	for(int i = 0; i < sheepsN; i++){
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
	}
	return 0;
}

int moveWolfs(){


	for(int i = 0;i < wolfsN; i++){
		int x = wolfs[i].x;
		int y = wolfs[i].y;
		int flag = 0;
		if(wolfs[i].Hunger > -10){
			wolfs[i].Hunger--;
		}
		else{

		}

		if(wolfs[i].Hunger > 0){
			if(wolfs[i].Hunger > 1500){
				for(int z = 0; z < wolfsN; z++){
					if(wolfs[z].dead == 1){
						wolfs[z].setup(wolfs[i].x-1, wolfs[i].y);
						wolfs[z].dead = 0;
						wolfs[z].Hunger = 500;
						wolfs[i].Hunger -= 1000;
						break;
					}
				}
			}

			for(int j = 1; j < 16;j++){
				if((x+j < screenW) && ((map[x+j+(y)*screenW] == 'S'))){
					x = wolfs[i].x + 1;
					y = wolfs[i].y;
					flag = 1;
					break;
				}
				else if((y-j > 0) && ((map[x+(y-j)*screenW] == 'S'))){
					x = wolfs[i].x;
					y = wolfs[i].y - 1;
					flag = 1;
					break;

				}
				else if((x-j > 0) && ((map[x-j+(y)*screenW] == 'S'))){
					x = wolfs[i].x - 1;
					y = wolfs[i].y;
					flag = 1;
					break;
				}
				else if((y+j < screenH) && ((map[x+(y+j)*screenW] == 'S') )){
					x = wolfs[i].x;
					y = wolfs[i].y + 1;
					flag = 1;
					break;
				}
			}
			if((map[x+y*screenW] == 'X') || (map[x+y*screenW] == '~')){

			}
			else{

				if((map[x+y*screenW] == '*')){
					wolfs[i].Hunger += 2;
				}

				if((map[x+y*screenW] == '.')){
					wolfs[i].Hunger += 1;
				}
				if((map[x+y*screenW] == 'S')){
					wolfs[i].Hunger += 300;
					for(int uu = 0; uu < sheepsN; uu++){
						if((sheeps[uu].x == x) && (sheeps[uu].y == y)){
							sheeps[uu].Hunger = -1000;
							sheeps[uu].dead = 0;
							break;
						}
					}
				}
			}
			map[wolfs[i].x+wolfs[i].y*screenW] = ' ';
			wolfs[i].x = x;
			wolfs[i].y = y;
			map[x+y*screenW] = 'W';
			}
		else{
			if(wolfs[i].dead == 0){
				wolfs[i].dead = 1;
				map[wolfs[i].x+wolfs[i].y*screenW] = ' ';
			}
		}
	}
	return 0;
}

int move(){
	moveSheeps();
	moveWolfs();
	moveCount++;
	return 0;
}

int main(){
	srand(time(0));
	printf("\033[2J\033[1;1H");
	//generateMap();
	MapLoad();
	setupSheeps();
	setupWolfs();
	screenUpdate();
	screenUpdate();
	while(1){
		move();
		grassGrow();
		updateString();
		usleep(10000);
		screenUpdate();
		//getchar();
	}

	return 0;
}
