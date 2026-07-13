#pragma once
#include "Common.h"

class Explosion
{
public:
    Explosion();

    void Play(int x, int y);

    void Update();

    void Draw();

    bool IsAlive();

private:
    int x;
    int y;

    int radius;

    int timer;

    bool alive;
};

