#pragma once
#include "Tank.h"

// 敌方坦克
class Enemy : public Tank
{
public:
    Enemy();

    void AI(Map& map);

private:
    int moveTimer;   // 控制移动频率
    int fireTimer;   // 控制开火频率
};

