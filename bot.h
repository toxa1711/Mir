class bot {
public:
	char* allow;

	char symbolDead;

	int Hunger;
	int MaxHunger;

	int x;
	int y;
	int dead;
	int hp;
	char symbol;
	int color;
	int direction;

	int die();

	int initialize(char c, char* f);

	int setup(int xx, int yy);

	int getSolution(const char* array);
};
