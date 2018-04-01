#include "Enemy.h"

void Enemy::Exe(BulletManager *bm, DrawManager *dm, int *area)
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
void Enemy::Spawn(double pX, double pY, double vX, double vY, int gP)
{
  isExist = true;
  posX = pX;
  posY = pY;
  velX = vX;
  velY = vY;
  gPattern = gP;
  animeFrame = 0;
}

EnemyManager::EnemyManager() : spawnWait(20)
{
  for (int i = 0; i < 16; i++) enemy[i] = new Enemy();
}
EnemyManager::~EnemyManager()
{
  for (int i = 0; i < 16; i++) delete enemy[i];
}
void EnemyManager::Exe(BulletManager *bm, DrawManager *dm, int *area)
{
  if (--spawnWait == 0) {
    Spawn(100, 0, 0, 2, 5);
    spawnWait = 40;
  }
  for (int i = 0; i < 16; i++) enemy[i]->Exe(bm, dm, area);
}
void EnemyManager::Draw(DrawManager *dm, int *area)
{
  for (int i = 0; i < 16; i++) enemy[i]->Draw(dm, area);
}
void EnemyManager::Spawn(double pX, double pY, double vX, double vY, int gPattern)
{
  for (int i = 0; i < 16; i++) {
    if (!enemy[i]->IsExist()) {
      dynamic_cast<Enemy*>(enemy[i])->Spawn(pX, pY, vX, vY, gPattern);
      break;
    }
  }
}