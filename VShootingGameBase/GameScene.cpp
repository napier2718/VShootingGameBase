#include "GameScene.h"

#include "DxLib.h"

GameScene::GameScene()
{
  gameui = new GameUI();
  om = new ObjectManager();
  dm = new DrawManager(gameui->GetArea());
}
GameScene::~GameScene()
{
  delete dm;
  delete gameui;
  delete om;
}
Scene GameScene::Exe()
{
  om->Exe(dm, gameui->GetArea());
  return preserve;
}
void GameScene::Draw()
{
  gameui->Draw();
  SetDrawArea(gameui->GetArea()[0], gameui->GetArea()[1], gameui->GetArea()[0] + gameui->GetArea()[2], gameui->GetArea()[1] + gameui->GetArea()[3]);
  om->Draw(dm);
  SetDrawArea(0, 0, WINDOW_X, WINDOW_Y);
}