#pragma once

#include "tower.hpp"

class Basic : public Tower
{
public:
	Basic();
	~Basic() {};

	const char* getTypeName() const override;
	void upgrade(int* money) override;
};

class Slow : public Tower
{
public:
	Slow();
	~Slow() {};

	const char* getTypeName() const override;
	void attack() override;
	void upgrade(int* money) override;
};

class Quick : public Tower
{
public:
	Quick();
	~Quick() {};

	const char* getTypeName() const override;
	void upgrade(int* money) override;
};

class Explosive : public Tower
{
public:
	float bombRadius = 10.f;

	Explosive();
	~Explosive() {};

	const char* getTypeName() const override;
	void upgrade(int* money) override;
};
