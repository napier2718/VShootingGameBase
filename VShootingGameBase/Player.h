#pragma once
#include "BaseObject.h"

class Player :public BaseObject
{
public:
  Player();
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm);
  void Hit();
private:
  void Shoot(BaseObject**, Vector<double>&, const double&, Vector<double>&, int, int);
  double speed;
  int gPattern;
  int shotWait;
};