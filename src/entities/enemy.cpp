
#include "enemy.hpp"
#include "../calc.hpp"


Enemy::Enemy()
{
	this->attackDmg = 0;
	this->initMS = 1;
	this->moveSpeed = initMS;
	this->loot = 0;
	this->direction = RIGHT;
	this->checkId = 1;
	this->health.maxLife = 0;
	this->health.life = 0;
	this->type = Type_Enemy::NONE;
}

Enemy::~Enemy()
{

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
	fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 10, this->color);
	ImGuiUtils::DrawTextureEx(*fgDrawlist, this->sprite, { this->pos.x, this->pos.y }, { 0.5f,0.5f }, this->angle); 
	this->health.draw();
}

void Enemy::spawn(Grid* grid)
{
	this->pos = grid->getSpawnPoint();
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
			if (this->direction == LEFT)
				this->angle = calc::PI;
			if (this->direction == RIGHT)
				this->angle = 0.f;
			if (this->direction == UP)
				this->angle = -calc::PI/2;
			if (this->direction == DOWN)
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