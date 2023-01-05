#pragma once

#include "grid.hpp"
#include "entities/enemy.hpp"

class App
{
public:
    Grid grid;

    App();
    ~App();

    void Update();
    Enemy e;
};
