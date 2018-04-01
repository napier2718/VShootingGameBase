#pragma once
#include "BaseScene.h"
#include "DrawManager.h"
#include "GameUI.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class GameScene :public BaseScene
{
public:
  GameScene();
  ~GameScene();
  int Exe();
  void Draw();
private:
  DrawManager *dm;
  GameUI *gameui;
  BaseObject *player;
  BulletManager *bm;
  EnemyManager *em;
};