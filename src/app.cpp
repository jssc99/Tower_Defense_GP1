#include "app.hpp"

#include "imgui_utils.hpp"
#include "calc.hpp"

#include <stdio.h>

App::App()
{
	
	this->grid.square[0][0].setType(GRASS);
	e.pos.x = 15.f;
	e.pos.y = 336.f;
	e.moveSpeed = 1.0f;
	e.direction = STOP;
}

App::~App()
{
}

void App::Update()
{
	
	{
		ImGui::Begin("Tower");
		ImGui::Text("square id %d:", this->grid.square[0][1].id);
		ImGui::Text("square type %s", this->grid.square[0][1].getType());
		ImGui::Text("spawn square %f, %f", this->grid.square[0][10].pos.x, this->grid.square[0][10].pos.y);
		ImGui::Text("square id %d:", this->grid.square[10][1].id);
		ImGui::Text("square type %s", this->grid.square[10][1].getType());
		ImGui::End();
	}
	this->grid.drawGrid();

	//enemy debug
	ImGui::Text("e.pos = %f, %f", e.pos.x, e.pos.y);
	ImGui::SliderFloat("move speed = ", &e.moveSpeed, 0.1f, 10.f);
	if (ImGui::Button("Right"))
	{
		e.direction = RIGHT;
	}
	if (ImGui::Button("Left"))
	{
		e.direction = LEFT;
	}
	if (ImGui::Button("Up"))
	{
		e.direction = UP;
	}
	if (ImGui::Button("Down"))
	{
		e.direction = DOWN;
	}
	if (ImGui::Button("Stop"))
	{
		e.direction = STOP;
	}

	e.drawEntity();
	e.pos += e.direction * e.moveSpeed;
}