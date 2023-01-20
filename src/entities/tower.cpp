#include "tower.hpp"

#include "../calc.hpp"

Tower::Tower()
{
	this->mType = Type_Tower::NONE;
}

Tower::~Tower()
{
	this->unloadTexture();
	ImGuiUtils::UnloadTexture(this->mTurret.sprite);
	this->mTurret.projectile.unloadTexture();
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

Type_Tower Tower::getType() const
{
	return this->mType;
}

int Tower::getPrice() const
{
	return this->mPrice;
}

void Tower::setAttackStats(float attackRadius, float attackSpeed, int attackDmg)
{
	this->mAttackRadius = attackRadius;
	this->mAttackSpeed = attackSpeed;
	this->mAttackDmg = attackDmg;
	this->mAttackCooldown = 0.f;
	this->mUpgradeLvl = 0;
}

void Tower::upgradeAttackStats(float attackRadius, float attackSpeed, int attackDmg)
{
	this->mAttackRadius += attackRadius;
	this->mAttackSpeed += attackSpeed;
	this->mAttackDmg += attackDmg;
}

void Tower::update(Enemy** en, int nbEnemies, int* money, float gameSpeed)
{
	if (nbEnemies) {
		if (this->mCurrentTarget == nullptr || this->mCurrentTarget->isDead() || !(this->isEnemyInsideRange(this->mCurrentTarget)))
			this->getTarget(en, nbEnemies);
		if (this->mCurrentTarget != nullptr) {
			this->attackTarget(gameSpeed);
			this->mTurret.angle = atan2f(this->mCurrentTarget->pos.y - this->pos.y, this->mCurrentTarget->pos.x - this->pos.x) + calc::PI / 2.f;
		}
		else this->mTurret.angle = 0.f;
		if (this->isMouseOverTower() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			this->upgrade(money);
	}
}

void Tower::draw(bool drawRadius)
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();
	if (drawRadius && this->isMouseOverTower())
		bgDrawList->AddCircle(this->pos, this->mAttackRadius, SHY_LIGHT_BLUE, 0, 2.f);
	ImGuiUtils::DrawTextureEx(*bgDrawList, this->sprite, this->pos, { 0.5f,0.5f });
	ImGuiUtils::DrawTextureEx(*bgDrawList, this->mTurret.sprite, this->pos, { 0.4f,0.4f }, this->mTurret.angle);
}

bool Tower::isEnemyInsideRange(Enemy* en) const// SS collision
{
	return (pow(en->pos.x - this->pos.x, 2.f) + pow(en->pos.y - this->pos.y, 2.f) < pow(en->getSize() + this->mAttackRadius, 2.f));
}

bool Tower::isMouseOverTower() const
{
	ImVec2 mouse = ImGui::GetMousePos();
	return ((this->pos.x - H_TOWER_SIZE <= mouse.x && mouse.x <= this->pos.x + H_TOWER_SIZE) &&
		(this->pos.y - H_TOWER_SIZE <= mouse.y && mouse.y <= this->pos.y + H_TOWER_SIZE));
}

bool Tower::hasTarget() const
{
	if (this->mCurrentTarget)
		return true;
	else
		return false;
}

void Tower::drawTarget()
{
	ImGui::GetForegroundDrawList()->AddCircle(this->mCurrentTarget->pos, 10, VIOLET, 0, 5.f);
}

void Tower::getTarget(Enemy** en, int nbEnemies)
{
	for (int i = 0; i < nbEnemies; i++) {
		if (en[i] && this->isEnemyInsideRange(en[i])) {
			if (mType == Type_Tower::SLOW)
				ma_engine_play_sound(&Entity::sAudioEngine, "assets/slow.mp3.", nullptr);
			this->mCurrentTarget = en[i];
			break;
		}
		else this->mCurrentTarget = nullptr;
	}
}

void Tower::attackTarget(float gameSpeed)
{
	if ((this->mAttackCooldown += ImGui::GetIO().DeltaTime * gameSpeed) >= this->mAttackSpeed)
	{
		this->attack();
		this->mAttackCooldown -= this->mAttackSpeed;
		if (mType == Type_Tower::EXPLOSIVE)
			ma_engine_play_sound(&Entity::sAudioEngine, "assets/explosive.mp3.", nullptr);
		else if (mType != Type_Tower::SLOW)
			ma_engine_play_sound(&Entity::sAudioEngine, "assets/shot.mp3.", nullptr);
	}
}

void Tower::attack()
{
	this->mCurrentTarget->getDamage(this->mAttackDmg);
}