#include "tower.hpp"

#include "../calc.hpp"

Tower::Tower()
{
	this->price = 0;
	this->mAttackRadius = 0.f;
	this->mAttackDmg = 0;
	this->mAttackSpeed = 0.f;
	this->mAttackCooldown = 0.f;
	this->mUpgradeLvl = 0;
	this->current_target = nullptr;
}

void Tower::setPos(float2 pos)
{
	this->pos = pos;
}

void Tower::setPos(float x, float y)
{
	this->pos = { x,y };
}

char* Tower::getType() const
{
	return (char*)"None";
}

void Tower::setAttackStats(float attackRadius, float attackSpeed, int attackDmg)
{
	this->mAttackRadius = attackRadius;
	this->mAttackSpeed = attackSpeed;
	this->mAttackDmg = attackDmg;
	this->mAttackCooldown = 0.f;
	this->mUpgradeLvl = 0;
}

void Tower::update(Enemy** en, int nbEnemies)
{
	if (nbEnemies) {
		if (this->current_target == nullptr || !(this->mIsEnemyInsideRange(this->current_target)))
			this->mGetTarget(en, nbEnemies);
		if (this->current_target != nullptr)
			this->mAttackTarget();
	}
}

void Tower::draw(bool drawRadius)
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();
	if (drawRadius)
		bgDrawList->AddCircleFilled({ this->pos.x, this->pos.y }, this->mAttackRadius, SHY_LIGHT_BLUE);
	bgDrawList->AddRectFilled({ this->pos.x - H_TOWER_SIZE , this->pos.y - H_TOWER_SIZE },
		{ this->pos.x + H_TOWER_SIZE, this->pos.y + H_TOWER_SIZE },
		this->color);
}

void Tower::upgrade()
{
	this->mUpgradeLvl++;
	// TODO
}

bool Tower::mIsEnemyInsideRange(Enemy* en) // SS collision
{																																// 10 == enemy radius TODO
	return (pow(en->pos.x - this->pos.x, 2.f) + pow(en->pos.y - this->pos.y, 2.f) < pow(10 + this->mAttackRadius, 2.f));
}

void Tower::mGetTarget(Enemy** en, int nbEnemies)
{
	for (int i = 0; i < nbEnemies; i++) {
		if (en[i] && this->mIsEnemyInsideRange(en[i])) {
			this->current_target = en[i];
			break;
		}
		else this->current_target = nullptr;
	}
}

void Tower::mAttackTarget()
{
	ImGui::GetForegroundDrawList()->AddCircle({ this->current_target->pos.x, this->current_target->pos.y }, 10, WHITE, 0, 5.f);
	if ((this->mAttackCooldown += ImGui::GetIO().DeltaTime) >= this->mAttackSpeed)
	{
		this->mAttack();
		this->mAttackCooldown -= this->mAttackSpeed;
	}
}

void Tower::mAttack()
{
	this->current_target; // TODO gets dmg
}