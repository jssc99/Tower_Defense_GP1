
#include "app.hpp"

#include "imgui_utils.hpp"
#include "entity.hpp"
#include "enemy.hpp"
#include "checkpoint.hpp"
#include "calc.hpp"

#include <stdio.h>

App::App()
{
	//enemy test
	/*
	e.pos.x = 100.f;
	e.pos.y = 100.f;
	e.moveSpeed = 1.f;
	e.direction = Direction::RIGHT;*/
}

App::~App()
{
}

void App::Update()
{
	//enemy test
	/*
	ImGui::Text("e.pos = %f, %f", e.pos.x, e.pos.y);
	ImGui::SliderFloat("move speed = ", &e.moveSpeed, 0.1f, 10.f);
	if (ImGui::Button("Right"))
	{
		e.direction = Direction::RIGHT;
	}
	if (ImGui::Button("Left"))
	{
		e.direction = Direction::LEFT;
	}
	if (ImGui::Button("Up"))
	{
		e.direction = Direction::UP;
	}
	if (ImGui::Button("Down"))
	{
		e.direction = Direction::DOWN;
	}

	e.drawEntity();
	e.pos += e.direction * e.moveSpeed;
	*/
}

