#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#define ENEMY_MAX_SIZE 128

struct HitBox
{
  Vector<double> size;
  double radius;
};
class ObjectManager
{
public:
  ObjectManager() :spawnWait(1)
  {
    hb[0].size.set(32.0, 32.0);
    hb[1].size.set(4.0,  16.0);
    CalcRadius();
    player = new Player();
    for (int i = 0; i < ENEMY_MAX_SIZE; i++) enemy[i] = new Enemy();
    for (int i = 0; i < PBULLET_MAX_SIZE; i++) pBullet[i] = new Bullet();
    for (int i = 0; i < EBULLET_MAX_SIZE; i++) eBullet[i] = new Bullet();
  }
  ~ObjectManager()
  {
    delete player;
    for (int i = 0; i < ENEMY_MAX_SIZE; i++) delete enemy[i];
    for (int i = 0; i < PBULLET_MAX_SIZE; i++) delete pBullet[i];
    for (int i = 0; i < EBULLET_MAX_SIZE; i++) delete eBullet[i];
  }
  void Exe(DrawManager *dm, int *area)
  {
    if (--spawnWait == 0) {
      for (int i = 0; i < ENEMY_MAX_SIZE; i++) {
        if (!enemy[i]->IsExist()) {
          dynamic_cast<Enemy*>(enemy[i])->Spawn(Vector<double>(150.0, 0.0), Vector<double>(0.0, 2.0), 5, 0);
          break;
        }
      }
      for (int i = 0; i < ENEMY_MAX_SIZE; i++) {
        if (!enemy[i]->IsExist()) {
          dynamic_cast<Enemy*>(enemy[i])->Spawn(Vector<double>(250.0, 0.0), Vector<double>(0.0, 2.0), 5, 0);
          break;
        }
      }
      spawnWait = 40;
    }
    player->Exe(dm, area, pBullet);
    for (int i = 0; i < ENEMY_MAX_SIZE; i++) enemy[i]->Exe(dm, area, eBullet);
    for (int i = 0; i < PBULLET_MAX_SIZE; i++) pBullet[i]->Exe(dm, area, pBullet);
    for (int i = 0; i < EBULLET_MAX_SIZE; i++) eBullet[i]->Exe(dm, area, eBullet);
    for (int i = 0; i < ENEMY_MAX_SIZE; i++) {
      if (!enemy[i]->isExist) continue;
      if (HitCheck(player, enemy[i])) {
        player->Hit();
        enemy[i]->Hit();
      }
      for (int j = 0; j < PBULLET_MAX_SIZE; j++) {
        if (!pBullet[j]->isExist) continue;
        if (HitCheck(enemy[i], pBullet[j])) {
          enemy[i]->Hit();
          pBullet[j]->Hit();
        }
      }
    }
    for (int i = 0; i < EBULLET_MAX_SIZE; i++) {
      if (!eBullet[i]->isExist) continue;
      if (HitCheck(player, eBullet[i])) {
        player->Hit();
        eBullet[i]->Hit();
      }
    }
  }
  void Draw(DrawManager *dm)
  {
    for (int i = 0; i < PBULLET_MAX_SIZE; i++) pBullet[i]->Draw(dm);
    for (int i = 0; i < EBULLET_MAX_SIZE; i++) eBullet[i]->Draw(dm);
    for (int i = 0; i < ENEMY_MAX_SIZE; i++) enemy[i]->Draw(dm);
    player->Draw(dm);
  }
private:
  void CalcRadius()
  {
    for (int i = 0; i < 10; i++) {
      hb[i].radius = (hb[i].size * 0.5).getLength();
    }
  }
  bool HitCheck(BaseObject *a, BaseObject *b)
  {
    Vector<double> interval = a->pos - b->pos;
    if (interval.getLength() > hb[a->hbPattern].radius + hb[b->hbPattern].radius) return false;
    Vector<double> ae[2], be[2];
    Vector<double> nae[2], nbe[2];
    double ra, rb;
    nae[0].set(1.0, 0.0);
    nae[1].set(0.0, 1.0);
    nbe[0].set(1.0, 0.0);
    nbe[1].set(0.0, 1.0);
    for (int i = 0; i < 2; i++) {
      nae[i].rotate(a->angle);
      nbe[i].rotate(b->angle);
      if (i == 0) {
        ae[i] = nae[i] * hb[a->hbPattern].size.x * 0.5;
        be[i] = nbe[i] * hb[b->hbPattern].size.x * 0.5;
      }
      else {
        ae[i] = nae[i] * hb[a->hbPattern].size.y * 0.5;
        be[i] = nbe[i] * hb[b->hbPattern].size.y * 0.5;
      }
    }
    ra = hb[a->hbPattern].size.x * 0.5;
    rb = std::abs(nae[0] * be[0]) + abs(nae[0] * be[1]);
    if (abs(nae[0] * interval) > ra + rb) return false;
    ra = hb[a->hbPattern].size.y * 0.5;
    rb = std::abs(nae[1] * be[0]) + abs(nae[1] * be[1]);
    if (abs(nae[1] * interval) > ra + rb) return false;
    ra = std::abs(ae[0] * nbe[0]) + abs(ae[1] * nbe[0]);
    rb = hb[b->hbPattern].size.x * 0.5;
    if (abs(nbe[0] * interval) > ra + rb) return false;
    ra = std::abs(ae[0] * nbe[1]) + abs(ae[1] * nbe[1]);
    rb = hb[b->hbPattern].size.y * 0.5;
    if (abs(nbe[1] * interval) > ra + rb) return false;
    return true;
  }
  HitBox hb[10];
  BaseObject *player;
  BaseObject *enemy[ENEMY_MAX_SIZE];
  BaseObject *pBullet[PBULLET_MAX_SIZE];
  BaseObject *eBullet[EBULLET_MAX_SIZE];
  int spawnWait;
};