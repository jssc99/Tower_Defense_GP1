
#include "enemy.hpp"
#include "../calc.hpp"


Enemy::Enemy()
{
	this->attackDmg = 0;
	this->moveSpeed = 1;
	this->loot = 0;
	this->direction = RIGHT;
	this->checkId = 1;
	this->health.maxLife = 0;
	this->health.life = 0;
	this->enemy_t.angle = 0;
	this->type = Type_Enemy::NONE;
}


void Enemy::update(Checkpoint* listCheckpoint, int nbCheckpoint, Castle* castle)
{
	if (this->checkId -1 != nbCheckpoint)
		this->move(listCheckpoint, nbCheckpoint);
	else
		if(castle->health.life - this->attackDmg >= 0)
			castle->health.life -= this->attackDmg;
	if (this->health.life <= 0)
		this->die();
}

void Enemy::draw()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddCircleFilled({ pos.x, pos.y }, 10, this->color);
	ImGuiUtils::DrawTextureEx(*fgDrawlist, this->enemy_t.sprite, { this->pos.x, this->pos.y }, { 0.5f,0.5f }, this->enemy_t.angle);
}

void Enemy::drawHealth()
{
	ImDrawList* fgDrawlist = ImGui::GetForegroundDrawList();
	fgDrawlist->AddRectFilled({ pos.x - (health.life * L_HEALTH_SIZE/2) / health.maxLife, pos.y - 30 }, { pos.x + (health.life * L_HEALTH_SIZE/2) / health.maxLife, pos.y - H_HEALTH_SIZE - 30 }, BLACK);
};

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
				this->health.life -= 10;
			}
			else
				this->pos += this->direction * this->moveSpeed;
			//changes enemy see direction
			if (this->direction == LEFT)
				this->enemy_t.angle = calc::PI;
			if (this->direction == RIGHT)
				this->enemy_t.angle = 0.f;
			if (this->direction == UP)
				this->enemy_t.angle = -calc::PI/2;
			if (this->direction == DOWN)
				this->enemy_t.angle = calc::PI/2;
		}
	}
}

void Enemy::die()
{
}

bool Enemy::isDead()
{
	return this->health.life <= 0;
}