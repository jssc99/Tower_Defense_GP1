#pragma once

#include "../tower.hpp"

class Slow : public Tower
{
public:
	inline Slow();
	inline ~Slow() {};

	inline char* getType() const;

private:
	void mAttack() override;
};

Slow::Slow()
{
	this->color = CYAN;
	this->price = 30;
	this->setAttackStats(50.f, 0.f, 0);
}

char* Slow::getType() const
{
	return (char*)"Slow";
}

inline void Slow::mAttack()
{
	this->current_target; // TODO slow it down
}