#prama once

#include "types.hpp"
#include "imgui_utils.hpp"

class Entity
{
public:
	float2 pos;
	ImGuiUtils sprite;

	Entity() virtual {};
	~Entity() virtual {};

	void drawEntity() virtual;
};

void Entity::drawEntity()
{
	// TODO
};