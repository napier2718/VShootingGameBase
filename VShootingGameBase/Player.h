#pragma once
#include "BaseObject.h"

class Player :public BaseObject
{
public:
  Player();
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm, int *area);
  void Hit();
private:
  void Shoot(BaseObject**, double, double, double, double, int, int);
  double speed;
  int gPattern;
  int shotWait;
};