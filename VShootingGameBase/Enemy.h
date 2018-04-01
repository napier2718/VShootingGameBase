#pragma once
#include "BaseObject.h"

class Enemy :public BaseObject
{
public:
  Enemy() :BaseObject() {}
  void Exe(BulletManager *bm, DrawManager *dm, int *area);
  void Draw(DrawManager *dm, int *area);
  void Spawn(double pX, double pY, double vX, double vY, int gP);
private:
  double velX, velY;
  int gPattern;
  int animeFrame;
};
class EnemyManager
{
public:
  EnemyManager();
  ~EnemyManager();
  void Exe(BulletManager *bm, DrawManager *dm, int *area);
  void Draw(DrawManager *dm, int *area);
  void Spawn(double pX, double pY, double vX, double vY, int gPattern);
private:
  BaseObject *enemy[16];
  int spawnWait;
};