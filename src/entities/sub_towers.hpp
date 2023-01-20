#pragma once

#include "tower.hpp"

// Basic Tower //

class Basic : public Tower
{
public:
	Basic();
	~Basic() {};

	const char* getTypeName() const override;
	void upgrade(int* money) override;
};

// Slow Tower //

class Slow : public Tower
{
public:
	Slow();
	~Slow() {};

	const char* getTypeName() const override;
	void upgrade(int* money) override;
	void attack() override;
};

// Quick Tower //

class Quick : public Tower
{
public:
	Quick();
	~Quick() {};

	const char* getTypeName() const override;
	void upgrade(int* money) override;
};

// Explosive Tower //

class Explosive : public Tower
{
public:
	float bombRadius = 10.f;

	Explosive();
	~Explosive() {};

	const char* getTypeName() const override;
	void upgrade(int* money) override;
};