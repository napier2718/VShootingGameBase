#include "GameScene.h"

GameScene::GameScene()
{
  dm = new DrawManager();
  gameui = new GameUI();
  player = new Player();
  bm = new BulletManager();
  em = new EnemyManager();
}
GameScene::~GameScene()
{
  delete dm;
  delete gameui;
  delete player;
  delete bm;
  delete em;
}
int GameScene::Exe()
{
  player->Exe(bm, dm, gameui->GetArea());
  bm->Exe(dm, gameui->GetArea());
  em->Exe(bm, dm, gameui->GetArea());
  return 0;
}
void GameScene::Draw()
{
  gameui->Draw();
  bm->Draw(dm, gameui->GetArea());
  em->Draw(dm, gameui->GetArea());
  player->Draw(dm, gameui->GetArea());
}