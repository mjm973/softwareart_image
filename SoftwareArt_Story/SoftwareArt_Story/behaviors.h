#pragma once

#include "ofMain.h"
#include "Bullet.h"
#include "Spawner.h"

void drawSeed(Bullet* bul);
void drawSeedRing(Bullet* bul);
ofVec2f posSeed(Bullet* bul, float t);
ofVec2f posSeedRing(Bullet* bul, float t);
void spawnSeedRing(Spawner* spawn, float t);

void drawRootSpawn(Bullet* bul);
void drawRoot(Bullet* bul);
void spawnRootSpawn(Spawner* spawn, float t);

void drawRaindrop(Bullet* bul);
void spawnRain(Spawner* spawn, float t);

void drawStalk(Bullet* bul);
void drawLeaf(Bullet* bul);
ofVec2f posLeaf(Bullet* bul, float t);
void spawnStalk(Spawner* spawn, float t);

void drawSun(Bullet* bul);
void drawRay(Bullet* bul);
void spawnRay(Spawner* spawn, float t);

void drawFlower(Bullet* bul);
void drawPetal(Bullet* bul);
ofVec2f velPetal(Bullet* bul, float t);
void spawnPetal(Spawner* spawn, float t);

void drawWind(Bullet* bul);
void drawWindPetal(Bullet* bul);
ofVec2f accWindPetal(Bullet* bul, float t);
void spawnWindPetal(Spawner* spawn, float t);


float fib(int n);
