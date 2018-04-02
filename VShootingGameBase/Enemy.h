#pragma once
#include "BaseObject.h"

class Enemy :public BaseObject
{
public:
  Enemy() :BaseObject() {}
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm);
  void Hit();
  void Spawn(Vector<double> &p, Vector<double> &v, int gP, int hbP);
private:
  Vector<double> vel;
  int gPattern;
  int animeFrame;
};