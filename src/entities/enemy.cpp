#include "enemy.hpp"
#include "../calc.hpp"

Enemy::Enemy()
{
	this->mHealth.maxLife = 0;
	this->mHealth.life = 0;
}

Enemy::~Enemy()
{
	this->unloadTexture();
}

void Enemy::update(const Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle, float gameSpeed, Enemy** en)
{
	if (this->mCheckId - 1 != nbCheckpoint)
		this->move(listCheckpoint, nbCheckpoint, gameSpeed);
	else
		if (castle->health.life - this->mAttackDmg >= 0)
			castle->health.life -= this->mAttackDmg;
	this->mHealth.posCenter = this->pos;
	this->mMoveSpeed = mInitMS;
	if (this->mType == Type_Enemy::HEALER)
		this->heal(en, gameSpeed);
}

void Enemy::draw(bool drawRadius)
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();
	if (drawRadius && this->isMouseOverEnemy())
		bgDrawList->AddCircle(this->pos, this->mRadius, SHY_GREEN, 0, 2.f);
	ImGuiUtils::DrawTextureEx(*bgDrawList, this->sprite, this->pos, { 0.5f,0.5f }, this->mAngle);
	this->mHealth.draw(L_HEALTH_SIZE, H_HEALTH_SIZE);
}

void Enemy::spawn(float2 spawnPoint)
{
	this->pos = spawnPoint;
}

void Enemy::move(const Checkpoint* listCheckpoint, int nbCheckpoint, float gameSpeed)
{
	//checkpoints change direction
	for (int i = 0; i < nbCheckpoint; ++i)
	{
		if (listCheckpoint[i].id == this->mCheckId)
		{
			if (this->pos.x >= listCheckpoint[i].pos.x - this->mMoveSpeed * ImGui::GetIO().DeltaTime * gameSpeed &&
				this->pos.x <= listCheckpoint[i].pos.x + this->mMoveSpeed * ImGui::GetIO().DeltaTime * gameSpeed &&
				this->pos.y >= listCheckpoint[i].pos.y - this->mMoveSpeed * ImGui::GetIO().DeltaTime * gameSpeed &&
				this->pos.y <= listCheckpoint[i].pos.y + this->mMoveSpeed * ImGui::GetIO().DeltaTime * gameSpeed)
			{
				this->mDirection = listCheckpoint[i].newDirection;
				this->mCheckId++;
				this->pos = listCheckpoint[i].pos;
			}
			else
				this->pos += this->mDirection * this->mMoveSpeed * ImGui::GetIO().DeltaTime * gameSpeed;
			//changes enemy see direction
			// TODO change to switch
			if (this->mDirection == LEFT)
				this->mAngle = calc::PI;
			else if (this->mDirection == RIGHT)
				this->mAngle = 0.f;
			else if (this->mDirection == UP)
				this->mAngle = -calc::PI / 2;
			else if (this->mDirection == DOWN)
				this->mAngle = calc::PI / 2;
		}
	}
}

bool Enemy::isDead() const
{
	return this->mHealth.life <= 0;
}

void Enemy::getDamage(int damage)
{
	this->mHealth.life -= damage;
}

void Enemy::heal(Enemy** en, float gameSpeed)
{
	for (int i = 0; i < MAX_NB_ENEMIES; ++i)
		if (en[i] && pow(en[i]->pos.x - this->pos.x, 2.f) + pow(en[i]->pos.y - this->pos.y, 2.f) < pow(en[i]->mSize + this->mRadius, 2.f))
		{
			this->mActionCD += ImGui::GetIO().DeltaTime;
			if (this->mActionCD * gameSpeed >= 3.f)
				if (en[i]->mHealth.life + 5 <= en[i]->mHealth.maxLife)
				{
					this->mActionCD = 0;
					en[i]->mHealth.life += 5;
				}
		}
}

bool Enemy::isMouseOverEnemy() const
{
	ImVec2 mouse = ImGui::GetMousePos();
	if ((this->pos.x - this->mSize <= mouse.x && mouse.x <= this->pos.x + this->mSize) &&
		(this->pos.y - this->mSize <= mouse.y && mouse.y <= this->pos.y + this->mSize))
		return true;
	else
		return false;
}

void Enemy::setMoveSpeed(float s)
{
	this->mMoveSpeed = this->mInitMS * s;
}

float Enemy::getSize()
{
	return this->mSize;
}

int Enemy::getLoot()
{
	return this->mLoot;
}

bool Enemy::isAtEndOfPath(int nbCheckpoints)
{
	if (this->mCheckId - 1 == nbCheckpoints)
		return true;
	else
		return false;
}
