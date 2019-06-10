#include "bot.h"

int bot::initialize(char c, char* f){
	symbol = c;
	dead = 0;
	x = -1;
	y = -1;
	symbolDead = 'Z';
	allow = f;
	return 0;
}

int bot::setup(int xx, int yy){
	x = xx;
	y = yy;
	Hunger = 100;
	dead = 0;
	return 0;
}

int bot::getSolution(const char* array){

	return 1;
}

int bot::die(){

	Hunger = -1;
	dead = 1;

	return 0;
}
