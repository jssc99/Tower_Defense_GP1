#pragma once

#include "enemy.hpp"

class Healer : public Enemy
{
public:
	Healer();
	~Healer();
};

class Knight : public Enemy
{
public:
	Knight();
	~Knight();
};

class Soldier : public Enemy
{
public:
	Soldier();
	~Soldier();
};