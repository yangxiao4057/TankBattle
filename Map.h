#pragma once

#include "Common.h"

//=====================================
// 地图类
//
// 负责：
// 1. 保存墙壁
// 2. 绘制墙壁
//=====================================

class Map
{
public:

    Map();

    void Draw();

    bool IsWall(int row, int col);

    void Generate();

private:

    int map[26][26];

    IMAGE brickImg;
};
