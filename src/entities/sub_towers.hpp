#pragma once
#include "tower.hpp"

class Basic : public Tower
{
public:
	Basic();
	~Basic() {};

	const char* getTypeName() const override;
};

class Slow : public Tower
{
public:
	Slow();
	~Slow() {};

	const char* getTypeName() const;
	void attack() override;
};

class Quick : public Tower
{
public:
	Quick();
	~Quick() {};

	const char* getTypeName() const;
};

class Explosive : public Tower
{
public:
	float bombRadius;

	Explosive();
	~Explosive() {};

	const char* getTypeName() const;
};
