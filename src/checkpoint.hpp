
enum direction
{
	UP, LEFT, RIGHT, DOWN
};

class Checkpoint
{
public:
	int value;
	direction newDirection;

	Checkpoint(int val, direction dir) : value(val), newDirection(dir) {};
	~Checkpoint() {};
};
