class bot {
public:
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

	int initialize(char c);

	int setup(int xx, int yy);

	int getSolution(const char* array);
};
