#pragma once
#include "BaseObject.h"

class Bullet :public BaseObject
{
public:
  Bullet() :BaseObject() {}
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm, int *area);
  void Hit();
  void Shoot(double pX, double pY, double vX, double vY, int gP, int hbP);
private:
  double velX, velY;
  int gPattern;
};