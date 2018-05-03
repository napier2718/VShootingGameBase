#pragma once
#include "BaseObject.h"

#define PBULLET_MAX_SIZE 64
#define EBULLET_MAX_SIZE 256

class Bullet :public BaseObject
{
public:
  Bullet() :BaseObject() {}
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm);
  void Hit();
  void Shoot(Vector<double> &p, const double &Angle, Vector<double> &v, int gID);
private:
  Vector<double> vel;
};