#include "DrawManager.h"

#include "DxLib.h"

#define TEXTSIZE 128

DrawManager::DrawManager(const char *dataFileName, int *Area) :area(Area)
{
  FILE *dataFile;
  fopen_s(&dataFile, dataFileName, "rb");
  dataFile = LoadImages(dataFile);
  dataFile = ReadGraphicData(dataFile);
  fclose(dataFile);
}
DrawManager::~DrawManager()
{
  for (int i = 0; i < 48; i++) DeleteGraph(gHandle[i]);
}
void DrawManager::Draw(int posX, int posY, double &angle, int graphicID, int animeFrame, bool isHit)
{
  if (isHit) {
    SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
    DrawRotaGraph(posX + area[0] - 1, posY + area[1] - 1, graphicList[graphicID].rate, angle * M_PI / 180.0, gHandle[graphicList[graphicID].gHandleID + (graphicList[graphicID].enableAnimation ? (animeFrame / graphicList[graphicID].aWaitFrame) % graphicList[graphicID].aFrame : 0)], true, false);
    SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
  }
  DrawRotaGraph(posX + area[0] - 1, posY + area[1] - 1, graphicList[graphicID].rate, angle * M_PI / 180.0, gHandle[graphicList[graphicID].gHandleID + (graphicList[graphicID].enableAnimation? (animeFrame / graphicList[graphicID].aWaitFrame) % graphicList[graphicID].aFrame : 0)], true, false);
  if (isHit) SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
void DrawManager::CalcRate(Graphic &graphic)
{
  Vector<int> size;
  GetGraphSize(gHandle[graphic.gHandleID], &size.x, &size.y);
  graphic.rate = (double)graphic.dSize.x / (double)size.x;
}
FILE *DrawManager::ReadText(char *text, FILE *dataFile)
{
  int length;
  fread_s(&length, sizeof(int), sizeof(int), 1, dataFile);
  fread_s(text, sizeof(char) * length, sizeof(char), length, dataFile);
  text[length] = '\0';
  return dataFile;
}
FILE *DrawManager::LoadImages(FILE *dataFile)
{
  Vector<int> gSize, div;
  int size, offset = 0;
  char filePath[TEXTSIZE];
  fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
  for (int i = 0; i < size; i++) {
    dataFile = ReadText(filePath, dataFile);
    fread_s(&gSize, sizeof(int) * 2, sizeof(int), 2, dataFile);
    fread_s(&div, sizeof(int) * 2, sizeof(int), 2, dataFile);
    LoadDivGraph(filePath, div.x*div.y, div.x, div.y, gSize.x, gSize.y, gHandle + offset);
    offset += div.x*div.y;
  }
  return dataFile;
}
FILE *DrawManager::ReadGraphicData(FILE *dataFile)
{
  int size;
  fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
  for (int i = 0; i < size; i++) {
    fread_s(&graphicList[i].gHandleID, sizeof(int), sizeof(int), 1, dataFile);
    fread_s(&graphicList[i].dSize, sizeof(int) * 2, sizeof(int), 2, dataFile);
    fread_s(&graphicList[i].hitboxID, sizeof(int), sizeof(int), 1, dataFile);
    fread_s(&graphicList[i].enableAnimation, sizeof(bool), sizeof(bool), 1, dataFile);
    fread_s(&graphicList[i].aFrame, sizeof(int) * 2, sizeof(int), 2, dataFile);
    if (!graphicList[i].enableAnimation) graphicList[i].aFrame = graphicList[i].aWaitFrame = 1;
    CalcRate(graphicList[i]);
  }
  return dataFile;
}