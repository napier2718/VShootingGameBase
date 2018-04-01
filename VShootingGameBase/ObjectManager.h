#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

struct HitBox
{
  double sizeX, sizeY;
};
class ObjectManager
{
public:
  ObjectManager() :spawnWait(1)
  {
    hbList[0].sizeX = 32.0;
    hbList[0].sizeY = 32.0;
    hbList[1].sizeX = 4.0;
    hbList[1].sizeY = 16.0;
    player = new Player();
    for (int i = 0; i < 16; i++) enemy[i] = new Enemy();
    for (int i = 0; i < 32; i++) pBullet[i] = new Bullet();
    for (int i = 0; i < 32; i++) eBullet[i] = new Bullet();
  }
  ~ObjectManager()
  {
    delete player;
    for (int i = 0; i < 16; i++) delete enemy[i];
    for (int i = 0; i < 32; i++) delete pBullet[i];
    for (int i = 0; i < 32; i++) delete eBullet[i];
  }
  void Exe(DrawManager *dm, int *area)
  {
    if (--spawnWait == 0) {
      for (int i = 0; i < 16; i++) {
        if (!enemy[i]->IsExist()) {
          dynamic_cast<Enemy*>(enemy[i])->Spawn(100, 0, 0, 2, 5, 0);
          break;
        }
      }
      spawnWait = 40;
    }
    player->Exe(dm, area, pBullet);
    for (int i = 0; i < 16; i++) enemy[i]->Exe(dm, area, eBullet);
    for (int i = 0; i < 32; i++) pBullet[i]->Exe(dm, area, pBullet);
    for (int i = 0; i < 32; i++) eBullet[i]->Exe(dm, area, eBullet);
    for (int i = 0; i < 16; i++) {
      if (!enemy[i]->isExist) continue;
      for (int j = 0; j < 32; j++) {
        if (!pBullet[j]->isExist) continue;
        if (HitCheck(enemy[i], pBullet[j])) {
          enemy[i]->Hit();
          pBullet[j]->Hit();
        }
      }
    }
  }
  void Draw(DrawManager *dm, int *area)
  {
    for (int i = 0; i < 32; i++) pBullet[i]->Draw(dm, area);
    for (int i = 0; i < 32; i++) eBullet[i]->Draw(dm, area);
    for (int i = 0; i < 16; i++) enemy[i]->Draw(dm, area);
    player->Draw(dm, area);
  }
private:
  bool HitCheck(BaseObject *a, BaseObject *b)
  {
    if (a->posX - hbList[a->hbPattern].sizeX / 2 >= b->posX + hbList[b->hbPattern].sizeX / 2) return false;
    if (a->posX + hbList[a->hbPattern].sizeX / 2 <= b->posX - hbList[b->hbPattern].sizeX / 2) return false;
    if (a->posY - hbList[a->hbPattern].sizeY / 2 >= b->posY + hbList[b->hbPattern].sizeY / 2) return false;
    if (a->posY + hbList[a->hbPattern].sizeY / 2 <= b->posY - hbList[b->hbPattern].sizeY / 2) return false;
    return true;
  }
  HitBox hbList[10];
  BaseObject *player;
  BaseObject *enemy[16];
  BaseObject *pBullet[32];
  BaseObject *eBullet[32];
  int spawnWait;
};