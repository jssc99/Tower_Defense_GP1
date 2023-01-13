#include "tower.hpp"

#include "../calc.hpp"
#include "enemy.hpp"

Tower::Tower()
{
	this->price = 0;
	this->actionRadius = 0;
	this->attackDmg = 0;
	this->attackSpeed = 0.f;
	this->current_target = nullptr;
	this->upgradeLvl = 0;
}

void Tower::setPos(float2 pos)
{
	this->pos = pos;
}

void Tower::setPos(float x, float y)
{
	this->pos = { x,y };
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

void Tower::draw()
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();
	bgDrawList->AddCircleFilled({ this->pos.x, this->pos.y }, this->actionRadius, SHY_LIGHT_BLUE);
	bgDrawList->AddRectFilled({ this->pos.x - H_TOWER_SIZE , this->pos.y - H_TOWER_SIZE },
		{ this->pos.x + H_TOWER_SIZE, this->pos.y + H_TOWER_SIZE },
		this->color);
}

bool Tower::mIsEnemyInsideRange(Enemy* en) // SS collision
{																																// 10 == enemy radius TODO 
	return (pow(en->pos.x - this->pos.x, 2.f) + pow(en->pos.y - this->pos.y, 2.f) < pow(10 + this->actionRadius, 2.f));
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
	// TODO
}
