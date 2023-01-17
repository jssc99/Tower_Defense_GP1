#include "tower.hpp"

#include "../calc.hpp"

Tower::Tower()
{
	this->turret.angle = 0;
	this->type = Type_Tower::NONE;
}

Tower::~Tower()
{
	if (this->hasTexture) {
		this->unloadTexture();
		ImGuiUtils::UnloadTexture(this->turret.sprite);
	}
}

void Tower::setPos(float2 pos)
{
	this->pos = pos;
}

void Tower::setPos(float x, float y)
{
	this->pos = { x,y };
}

const char* Tower::getTypeName() const
{
	return "None";
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
		if (this->current_target == nullptr || this->current_target->isDead() || !(this->isEnemyInsideRange(this->current_target)))
			this->getTarget(en, nbEnemies);
		if (this->current_target != nullptr)
			this->attackTarget();
	}
}

void Tower::draw(bool drawRadius)
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();
	if (drawRadius && this->isMouseOverTower())
		bgDrawList->AddCircle(this->pos, this->mAttackRadius, SHY_LIGHT_BLUE, 0, 2.f);
	ImGuiUtils::DrawTextureEx(*bgDrawList, this->sprite, this->pos, { 0.5f,0.5f });
	ImGuiUtils::DrawTextureEx(*bgDrawList, this->turret.sprite, this->pos, { 0.4f,0.4f }, this->turret.angle);
}

void Tower::upgrade()
{
	this->mUpgradeLvl++;
	// TODO
}

bool Tower::isEnemyInsideRange(Enemy const* en) const// SS collision
{																																// 10 == enemy.size TODO
	return (pow(en->pos.x - this->pos.x, 2.f) + pow(en->pos.y - this->pos.y, 2.f) < pow(10 + this->mAttackRadius, 2.f));
}

bool Tower::isMouseOverTower() const
{
	ImVec2 mouse = ImGui::GetMousePos();
	if ((this->pos.x - (float)H_TOWER_SIZE <= mouse.x && mouse.x <= this->pos.x + (float)H_TOWER_SIZE) &&
		(this->pos.y - (float)H_TOWER_SIZE <= mouse.y && mouse.y <= this->pos.y + (float)H_TOWER_SIZE))
		return true;
	else
		return false;
}

void Tower::getTarget(Enemy** en, int nbEnemies)
{
	for (int i = 0; i < nbEnemies; i++) {
		if (en[i] && this->isEnemyInsideRange(en[i])) {
			this->current_target = en[i];
			break;
		}
		else this->current_target = nullptr;
	}
}

void Tower::attackTarget()
{
	ImGui::GetForegroundDrawList()->AddCircle(this->current_target->pos, 10, WHITE, 0, 5.f);
	if ((this->mAttackCooldown += ImGui::GetIO().DeltaTime) >= this->mAttackSpeed)
	{
		this->attack();
		this->mAttackCooldown -= this->mAttackSpeed;
	}
}

void Tower::attack()
{
	this->current_target->getDamage(this->mAttackDmg);
}