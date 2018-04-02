#include "DrawManager.h"

#include "DxLib.h"

DrawManager::DrawManager(int *Area) :area(Area)
{
  LoadDivGraph("resource\\player.png", 16, 4, 4, 16, 16, gHandle);
  LoadDivGraph("resource\\bullet.png", 16, 4, 4,  8,  8, gHandle + 16);
  LoadDivGraph("resource\\enemy.png",  16, 4, 4, 16, 16, gHandle + 32);
  dPattern[0].gHandleID = 0;
  dPattern[0].dSize.set(32, 32);
  CalcRate(dPattern[0]);
  dPattern[1].gHandleID = 1;
  dPattern[1].dSize.set(32, 32);
  CalcRate(dPattern[1]);
  dPattern[2].gHandleID = 2;
  dPattern[2].dSize.set(32, 32);
  CalcRate(dPattern[2]);
  dPattern[3].gHandleID = 3;
  dPattern[3].dSize.set(32, 32);
  CalcRate(dPattern[3]);
  dPattern[4].gHandleID = 16;
  dPattern[4].dSize.set(16, 16);
  CalcRate(dPattern[4]);
  dPattern[5].gHandleID = 32;
  dPattern[5].dSize.set(32, 32);
  CalcRate(dPattern[5]);
}
DrawManager::~DrawManager()
{
  for (int i = 0; i < 48; i++) DeleteGraph(gHandle[i]);
}
void DrawManager::Draw(int posX, int posY, double &angle, int pattern, int animeFrame)
{
  DrawRotaGraph(posX + area[0] - 1, posY + area[1] - 1, dPattern[pattern].rate, angle * M_PI / 180.0, gHandle[dPattern[pattern].gHandleID + animeFrame], true, false);
}
void DrawManager::CalcRate(DrawPattern &dPattern)
{
  Vector<int> size;
  GetGraphSize(gHandle[dPattern.gHandleID], &size.x, &size.y);
  dPattern.rate = (double)dPattern.dSize.x / (double)size.x;
}