#include "enemy.hpp"
#include "../calc.hpp"

Enemy::Enemy()
{
	this->health.maxLife = 0;
	this->health.life = 0;
}

Enemy::~Enemy()
{
	this->unloadTexture();
}

void Enemy::update(const Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle, float gameAcc, Enemy** en)
{
	if (this->checkId -1 != nbCheckpoint)
		this->move(listCheckpoint, nbCheckpoint ,gameAcc);
	else
		if (castle->health.life - this->attackDmg >= 0)
			castle->health.life -= this->attackDmg;
	this->health.posCenter = this->pos;
	this->moveSpeed = initMS;
	if (this->type == Type_Enemy::HEALER)
		this->heal(en, gameAcc);
}

void Enemy::draw(bool drawRadius)
{
	ImDrawList* bgDrawList = ImGui::GetBackgroundDrawList();
	if (drawRadius && this->isMouseOverEnemy())
		bgDrawList->AddCircle(this->pos, this->radius, SHY_GREEN, 0, 2.f);
	ImGuiUtils::DrawTextureEx(*bgDrawList, this->sprite, { this->pos.x, this->pos.y }, { 0.5f,0.5f }, this->angle);
	this->health.draw(L_HEALTH_SIZE, H_HEALTH_SIZE);
}

void Enemy::spawn(float2 spawnPoint)
{
	this->pos = spawnPoint;
}

void Enemy::move(const Checkpoint* listCheckpoint, int nbCheckpoint, float gameAcc)
{
	//checkpoints change direction
	for (int i = 0; i < nbCheckpoint; ++i)
	{
		if (listCheckpoint[i].id == this->checkId)
		{
			if (this->pos.x >= listCheckpoint[i].pos.x - this->moveSpeed * ImGui::GetIO().DeltaTime * gameAcc &&
				this->pos.x <= listCheckpoint[i].pos.x + this->moveSpeed * ImGui::GetIO().DeltaTime * gameAcc &&
				this->pos.y >= listCheckpoint[i].pos.y - this->moveSpeed * ImGui::GetIO().DeltaTime * gameAcc &&
				this->pos.y <= listCheckpoint[i].pos.y + this->moveSpeed * ImGui::GetIO().DeltaTime * gameAcc)
			{
				this->direction = listCheckpoint[i].newDirection;
				this->checkId++;
				this->pos = listCheckpoint[i].pos;
			}
			else
				this->pos += this->direction * this->moveSpeed * ImGui::GetIO().DeltaTime * gameAcc;
			//changes enemy see direction 
			// TODO change to switch
			if (this->direction == LEFT)
				this->angle = calc::PI;
			else if (this->direction == RIGHT)
				this->angle = 0.f;
			else if (this->direction == UP)
				this->angle = -calc::PI/2;
			else if (this->direction == DOWN)
				this->angle = calc::PI/2;
		}
	}
}

bool Enemy::isDead() const
{
	return this->health.life <= 0;
}

void Enemy::getDamage(int damage)
{
	this->health.life -= damage;
}

void Enemy::heal(Enemy** en, float gameAcc)
{
	for (int i = 0; i < MAX_NB_ENEMIES; ++i)
	{
		if (en[i] && pow(en[i]->pos.x - this->pos.x, 2.f) + pow(en[i]->pos.y - this->pos.y, 2.f) < pow(en[i]->size + this->radius, 2.f))
		{
			this->actionCD += ImGui::GetIO().DeltaTime;
			if (this->actionCD * gameAcc >= 3.f)
			{
				if (en[i]->health.life + 5 <= en[i]->health.maxLife)
				{
					this->actionCD = 0;
					en[i]->health.life += 5;
				}
			}
		}
	}
}

bool Enemy::isMouseOverEnemy() const
{
	ImVec2 mouse = ImGui::GetMousePos();
	if ((this->pos.x - this->size <= mouse.x && mouse.x <= this->pos.x + this->size) &&
		(this->pos.y - this->size <= mouse.y && mouse.y <= this->pos.y + this->size))
		return true;
	else
		return false;
}