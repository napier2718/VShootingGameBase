#pragma once
#include "BaseObject.h"

struct BulletData
{
  int graphicID;
  Vector<double> pos, v;
  double angle;
};
class Player :public BaseObject
{
public:
  Player(const char *dataFileName);
  ~Player() { delete[] shotData; }
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm);
  void Hit();
private:
  void Shoot(BaseObject**, Vector<double>&, const double&, Vector<double>&, int);
  FILE *ReadPlayerData(FILE *);
  int gStartID;
  double speed;
  int shotWait, shotWaitTime;
  BulletData *shotData;
  int shotDataSize;
};