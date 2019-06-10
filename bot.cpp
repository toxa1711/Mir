#include "bot.h"

int bot::initialize(char c){
	symbol = c;
	dead = 0;
	return 0;
}

int bot::setup(int xx, int yy){
	x = xx;
	y = yy;
	Hunger = 100;
	dead = 0;
	return 0;
}
