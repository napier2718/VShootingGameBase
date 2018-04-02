#pragma once
#define WINDOW_X 800
#define WINDOW_Y 600

enum Scene
{
  preserve,
  titleScene,
  gameScene,
  endScene,
};
class BaseScene
{
public:
  virtual Scene Exe() = 0;
  virtual void Draw() = 0;
};