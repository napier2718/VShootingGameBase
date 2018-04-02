#pragma once
#include "BaseScene.h"
#include "DrawManager.h"
#include "GameUI.h"
#include "ObjectManager.h"

class GameScene :public BaseScene
{
public:
  GameScene();
  ~GameScene();
  Scene Exe();
  void Draw();
private:
  DrawManager *dm;
  GameUI *gameui;
  ObjectManager *om;
};