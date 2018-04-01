#include "GameScene.h"

GameScene::GameScene()
{
  dm = new DrawManager();
  gameui = new GameUI();
  om = new ObjectManager();
}
GameScene::~GameScene()
{
  delete dm;
  delete gameui;
  delete om;
}
int GameScene::Exe()
{
  om->Exe(dm, gameui->GetArea());
  return 0;
}
void GameScene::Draw()
{
  gameui->Draw();
  om->Draw(dm, gameui->GetArea());
}