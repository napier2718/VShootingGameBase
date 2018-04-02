#include "Enemy.h"

void Enemy::Exe(DrawManager *dm, int *area, BaseObject **bList)
{
  if (isExist) {
    pos += vel;
    animeFrame++;
    if (pos.x < -dm->GetDSize(gPattern).x / 2) isExist = false;
    else if (pos.x > area[2] + dm->GetDSize(gPattern).x / 2)isExist = false;
    if (pos.y < -dm->GetDSize(gPattern).y / 2) isExist = false;
    else if (pos.y > area[3] + dm->GetDSize(gPattern).y / 2) isExist = false;
  }
}
void Enemy::Draw(DrawManager *dm)
{
  if (isExist) dm->Draw((int)pos.x, (int)pos.y, angle, gPattern, (animeFrame / 6) % 6);
}
void Enemy::Hit() { isExist = false; }
void Enemy::Spawn(Vector<double> &p, Vector<double> &v, int gP, int hbP)
{
  isExist = true;
  pos = p;
  vel = v;
  gPattern = gP;
  hbPattern = hbP;
  animeFrame = 0;
}