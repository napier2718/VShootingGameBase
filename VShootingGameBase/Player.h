#pragma once
#include "BaseObject.h"

class Player :public BaseObject
{
public:
  Player();
  void Exe(BulletManager *bm, DrawManager *dm, int *area);
  void Draw(DrawManager *dm, int *area);
private:
  double speed;
  int gPattern;
  int shotWait;
};