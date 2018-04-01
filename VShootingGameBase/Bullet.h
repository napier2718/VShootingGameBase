#pragma once
#include "BaseObject.h"

class Bullet :public BaseObject
{
public:
  Bullet() :BaseObject() {}
  void Exe(BulletManager *bm, DrawManager *dm, int *area);
  void Draw(DrawManager *dm, int *area);
  void Shot(double pX, double pY, double vX, double vY, int gP);
private:
  double velX, velY;
  int gPattern;
};

class BulletManager
{
public:
  BulletManager();
  ~BulletManager();
  void Exe(DrawManager *dm, int *area);
  void Draw(DrawManager *dm, int *area);
  void Shot(double pX, double pY, double vX, double vY, int gPattern);
private:
  BaseObject *bullet[16];
};