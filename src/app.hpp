#pragma once

#include "entities/enemy.hpp"
#include "imgui_utils.hpp"
#include "calc.hpp"
#include "grid.hpp"

class App
{
public:
    Grid grid;

    App();
    ~App();

    void Update();

    Enemy e;
};
