#pragma once

class Health
{
public:
	int maxLife;
	int life;

	inline Health();
	~Health() {};
};

Health::Health()
{
	maxLife = 0;
	life = 0;
};