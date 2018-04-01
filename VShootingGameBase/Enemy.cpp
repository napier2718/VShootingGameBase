#include "Enemy.h"

void Enemy::Exe(DrawManager *dm, int *area, BaseObject **bList)
{
  if (isExist) {
    posX += velX;
    posY += velY;
    animeFrame++;
    if (posX < -dm->GetDSize(gPattern)[0] / 2) isExist = false;
    else if (posX > area[2] + dm->GetDSize(gPattern)[0] / 2)isExist = false;
    if (posY < -dm->GetDSize(gPattern)[1] / 2) isExist = false;
    else if (posY > area[3] + dm->GetDSize(gPattern)[1] / 2) isExist = false;
  }
}
void Enemy::Draw(DrawManager *dm, int *area)
{
  if (isExist) dm->Draw((int)posX, (int)posY, gPattern, (animeFrame / 6) % 6, area);
}
void Enemy::Hit() { isExist = false; }
void Enemy::Spawn(double pX, double pY, double vX, double vY, int gP, int hbP)
{
  isExist = true;
  posX = pX;
  posY = pY;
  velX = vX;
  velY = vY;
  gPattern = gP;
  hbPattern = hbP;
  animeFrame = 0;
}