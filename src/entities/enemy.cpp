
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

void Enemy::update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle)
{
	if (this->checkId -1 != nbCheckpoint)
		this->move(listCheckpoint, nbCheckpoint);
	else
		if(castle->health.life - this->attackDmg >= 0)
			castle->health.life -= this->attackDmg;
	this->health.posCenter = this->pos;
	this->moveSpeed = initMS;
}

void Enemy::draw()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	ImGuiUtils::DrawTextureEx(*fgDrawlist, this->sprite, this->pos, { 0.5f,0.5f }, this->angle); 
	this->health.draw();
}

void Enemy::spawn(float2 spawnPoint)
{
	this->pos = spawnPoint;
}

void Enemy::move(Checkpoint* listCheckpoint, int nbCheckpoint)
{
	//checkpoints change direction
	for (int i = 0; i < nbCheckpoint; ++i)
	{
		if (listCheckpoint[i].id == this->checkId)
		{
			if (this->pos.x >= listCheckpoint[i].pos.x - this->moveSpeed &&
				this->pos.x <= listCheckpoint[i].pos.x + this->moveSpeed &&
				this->pos.y >= listCheckpoint[i].pos.y - this->moveSpeed &&
				this->pos.y <= listCheckpoint[i].pos.y + this->moveSpeed)
			{
				this->direction = listCheckpoint[i].newDirection;
				this->checkId++;
				this->pos = listCheckpoint[i].pos;
			}
			else
				this->pos += this->direction * this->moveSpeed;
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

bool Enemy::isDead()
{
	return this->health.life <= 0;
}

void Enemy::getDamage(int damage)
{
	this->health.life -= damage;
}