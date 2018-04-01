#pragma once
class GameUI
{
public:
  GameUI();
  void Draw();
  int *GetArea() { return area; }
private:
  int area[4];
  int areaColor;
};