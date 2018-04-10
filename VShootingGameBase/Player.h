#pragma once
#include "BaseObject.h"

#include <vector>

struct PlayerData
{
  double posX, posY;
  double speed;
  int shotWait;
};
struct BulletData
{
  Vector<double> pos;
  Vector<double> v;
  double angle;
};
class Player :public BaseObject
{
public:
  Player();
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm);
  void Hit();
private:
  void Shoot(BaseObject**, Vector<double>&, const double&, Vector<double>&, int, int);
  FILE *ReadPlayerData(FILE *);
  double speed;
  int gPattern;
  int shotWait, shotWaitTime;
  std::vector<BulletData> shotData;
};