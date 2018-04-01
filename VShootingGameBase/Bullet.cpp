#include "Bullet.h"

void Bullet::Exe(BulletManager *bm, DrawManager *dm, int *area)
{
  if (isExist) {
    posX += velX;
    posY += velY;
    if (posX < -dm->GetDSize(gPattern)[0] / 2) isExist = false;
    else if (posX > area[2] + dm->GetDSize(gPattern)[0] / 2)isExist = false;
    if (posY < -dm->GetDSize(gPattern)[1] / 2) isExist = false;
    else if (posY > area[3] + dm->GetDSize(gPattern)[1] / 2) isExist = false;
  }
}
void Bullet::Draw(DrawManager *dm, int *area)
{
  if (isExist) dm->Draw((int)posX, (int)posY, gPattern, 0, area);
}
void Bullet::Shot(double pX, double pY, double vX, double vY, int gP)
{
  isExist = true;
  posX = pX;
  posY = pY;
  velX = vX;
  velY = vY;
  gPattern = gP;
}

BulletManager::BulletManager()
{
  for (int i = 0; i < 16; i++) bullet[i] = new Bullet();
}
BulletManager::~BulletManager()
{
  for (int i = 0; i < 16; i++) delete bullet[i];
}
void BulletManager::Exe(DrawManager *dm, int *area)
{
  for (int i = 0; i < 16; i++) bullet[i]->Exe(this, dm, area);
}
void BulletManager::Draw(DrawManager *dm, int *area)
{
  for (int i = 0; i < 16; i++) bullet[i]->Draw(dm, area);
}
void BulletManager::Shot(double pX, double pY, double vX, double vY, int gPattern)
{
  for (int i = 0; i < 16; i++) {
    if (!bullet[i]->IsExist()) {
      dynamic_cast<Bullet*>(bullet[i])->Shot(pX, pY, vX, vY, gPattern);
      break;
    }
  }
}