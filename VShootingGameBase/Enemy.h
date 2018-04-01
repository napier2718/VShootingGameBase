#pragma once
#include "BaseObject.h"

class Enemy :public BaseObject
{
public:
  Enemy() :BaseObject() {}
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm, int *area);
  void Hit();
  void Spawn(double pX, double pY, double vX, double vY, int gP, int hbP);
private:
  double velX, velY;
  int gPattern;
  int animeFrame;
};