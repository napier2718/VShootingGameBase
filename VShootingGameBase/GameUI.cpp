#include "GameUI.h"

#include "DxLib.h"

GameUI::GameUI()
{
  area[0] = 20;
  area[1] = 20;
  area[2] = 400;
  area[3] = 560;
  areaColor = GetColor(100, 100, 100);
}
void GameUI::Draw()
{
  DrawBox(area[0], area[1], area[0] + area[2] - 1, area[1] + area[3] - 1, areaColor, true);
}