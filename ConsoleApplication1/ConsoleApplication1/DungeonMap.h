#pragma once
constexpr int dungeonWidth = 50;
constexpr int dungeonHeight = 50;
constexpr int startLocationX = 4;
constexpr int startLocationY = 45;
constexpr int dungeonDisplay = 15;
constexpr int displayCenter = dungeonDisplay / 2;

constexpr int tileBlank = 0xff;
constexpr int tileFloor = 0xe0;
constexpr int tileWall = 0x00;
constexpr int tileWallShadow = 0x92;

void getMapLayout(int curX, int curY, int displayedSection[dungeonDisplay][dungeonDisplay]);
