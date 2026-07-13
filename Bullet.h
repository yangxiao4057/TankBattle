#pragma once

#include "Common.h"

//==========================
// ×Óµ¯Àà
//==========================

class Bullet
{
public:

    Bullet();

    void Init(int x, int y, Direction dir);

    void Update();

    void Draw();

    bool IsAlive();

    int GetX() const;

    int GetY() const;

    void Destroy();
private:

    int x;

    int y;

    int speed;

    Direction direction;

    bool alive;
};
