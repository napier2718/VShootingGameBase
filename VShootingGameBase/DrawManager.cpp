#include "DrawManager.h"

#include "DxLib.h"

DrawManager::DrawManager()
{
  LoadDivGraph("resource\\player.png", 16, 4, 4, 16, 16, gHandle);
  LoadDivGraph("resource\\bullet.png", 16, 4, 4, 8, 8, gHandle + 16);
  LoadDivGraph("resource\\enemy.png", 16, 4, 4, 16, 16, gHandle + 32);
  dPattern[0].dSize[0] = 32;
  dPattern[0].dSize[1] = 32;
  dPattern[0].gHandleID = 0;
  dPattern[1].dSize[0] = 32;
  dPattern[1].dSize[1] = 32;
  dPattern[1].gHandleID = 1;
  dPattern[2].dSize[0] = 32;
  dPattern[2].dSize[1] = 32;
  dPattern[2].gHandleID = 2;
  dPattern[3].dSize[0] = 32;
  dPattern[3].dSize[1] = 32;
  dPattern[3].gHandleID = 3;
  dPattern[4].dSize[0] = 16;
  dPattern[4].dSize[1] = 16;
  dPattern[4].gHandleID = 16;
  dPattern[5].dSize[0] = 32;
  dPattern[5].dSize[1] = 32;
  dPattern[5].gHandleID = 32;
}
DrawManager::~DrawManager()
{
  for (int i = 0; i < 48; i++) DeleteGraph(gHandle[i]);
}
void DrawManager::Draw(int posX, int posY, int pattern, int animeFrame, int *area)
{
  DrawExtendGraph(posX + area[0] - dPattern[pattern].dSize[0] / 2,
                  posY + area[1] - dPattern[pattern].dSize[1] / 2,
                  posX + area[0] + dPattern[pattern].dSize[0] / 2 - 1,
                  posY + area[1] + dPattern[pattern].dSize[1] / 2 - 1,
                  gHandle[dPattern[pattern].gHandleID + animeFrame], true);
}