#pragma once
#include "Tank.h"
#include"Enemy.h"


//==========================
// 玩家类
//
// public Tank
//
// 表示：
// Player 是 Tank 的子类
//==========================

class Player : public Tank
{
public:
    Player();
    void Control(Map& map);
};

