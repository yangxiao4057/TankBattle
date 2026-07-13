#pragma once

#include "Common.h"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include <vector>
#include "Bullet.h"
#include"Explosion.h"



//=================================
// Game
//
// 游戏主类
//
// 负责：
//
// 初始化
// 更新
// 绘制
//=================================

class Game
{
public:

    Game();

    void Init();

    void Run();

    void NextLevel();

private:

    void Update();

    void Render();

    Player player;

    vector<Enemy> enemies;

    bool running;

    Map map;

    bool gameOver;

    int level;

    vector<Explosion> explosions;

    bool playerDead;

    int gameOverTimer;


};
