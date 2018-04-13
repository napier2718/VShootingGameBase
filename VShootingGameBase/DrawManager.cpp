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
void DrawManager::Draw(int posX, int posY, double &angle, int pattern, int animeFrame)
{
  DrawRotaGraph(posX + area[0] - 1, posY + area[1] - 1, dPattern[pattern].rate, angle * M_PI / 180.0, gHandle[dPattern[pattern].gHandleID + (dPattern[pattern].enableAnimation? (animeFrame / dPattern[pattern].aWaitFrame) % dPattern[pattern].aFrame : 0)], true, false);
}
void DrawManager::CalcRate(DrawPattern &dPattern)
{
  Vector<int> size;
  GetGraphSize(gHandle[dPattern.gHandleID], &size.x, &size.y);
  dPattern.rate = (double)dPattern.dSize.x / (double)size.x;
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
    fread_s(&dPattern[i].gHandleID, sizeof(int), sizeof(int), 1, dataFile);
    fread_s(&dPattern[i].dSize, sizeof(int) * 2, sizeof(int), 2, dataFile);
    fread_s(&dPattern[i].enableAnimation, sizeof(bool), sizeof(bool), 1, dataFile);
    fread_s(&dPattern[i].aFrame, sizeof(int) * 2, sizeof(int), 2, dataFile);
    if (!dPattern[i].enableAnimation) dPattern[i].aFrame = dPattern[i].aWaitFrame = 1;
    CalcRate(dPattern[i]);
  }
  return dataFile;
}