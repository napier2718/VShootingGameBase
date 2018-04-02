#pragma once
#include "BaseObject.h"

class Bullet :public BaseObject
{
public:
  Bullet() :BaseObject() {}
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm);
  void Hit();
  void Shoot(Vector<double> &p, const double &Angle, Vector<double> &v, int gP, int hbP);
private:
  Vector<double> vel;
  int gPattern;
};