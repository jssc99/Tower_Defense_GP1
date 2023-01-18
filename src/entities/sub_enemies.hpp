#pragma once

#include "enemy.hpp"

// Healer enemy //

class Healer : public Enemy
{
public:
	Healer();
	~Healer() {};
};

// Knight enemy //

class Knight : public Enemy
{
public:
	Knight();
	~Knight() {};
};

// Soldier enemy //

class Soldier : public Enemy
{
public:
	Soldier();
	~Soldier() {};
};