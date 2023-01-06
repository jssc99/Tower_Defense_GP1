#pragma once

#include "grid.hpp"
#include "entities/enemy.hpp"
#include "calc.hpp"

class App
{
public:
    Grid grid;

    App();
    ~App();

    void Update();
    Enemy e;

    int nbrCheck;
    Checkpoint check[5];
};
