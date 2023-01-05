#pragma once

#include "grid.hpp"
#include "imgui_utils.hpp"
#include "entities/enemy.hpp"
#include "entity.hpp"
#include "calc.hpp"

class App
{
public:
    Grid grid;

    App();
    ~App();

    void Update();

    Enemy e;
};
