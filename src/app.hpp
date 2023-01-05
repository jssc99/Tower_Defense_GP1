#pragma once

#include "enemy.hpp"

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
