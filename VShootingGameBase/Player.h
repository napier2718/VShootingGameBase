#pragma once
#include "BaseObject.h"

#include <vector>

struct BulletData
{
  Vector<double> pos;
  Vector<double> v;
  int graphicID;
  double angle;
};
class Player :public BaseObject
{
public:
  Player(const char *dataFileName);
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm);
  void Hit();
private:
  void Shoot(BaseObject**, Vector<double>&, const double&, Vector<double>&, int);
  FILE *ReadPlayerData(FILE *);
  double speed;
  int gStartID;
  int shotWait, shotWaitTime;
  std::vector<BulletData> shotData;
};