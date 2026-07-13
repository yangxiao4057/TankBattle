#pragma once
#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
// 游戏窗口大小

const int WINDOW_WIDTH = 832;
const int WINDOW_HEIGHT = 832;

// FPS

const int FPS = 60;

// 每帧时间

const int FRAME_DELAY = 1000 / FPS;

// 坦克方向

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
