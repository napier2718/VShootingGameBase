#include "TitleScene.h"

#include <cstdio>
#include "DxLib.h"

using namespace std;

#define TEXTSIZE 128

TitleScene::TitleScene() :select(0)
{
  FILE *dataFile;
  fopen_s(&dataFile, "data\\title.data", "rb");
  dataFile = LoadImages(gHandleList, dataFile);
  dataFile = LoadColors(colorList, dataFile);
  dataFile = CreateFonts(fHandleList, dataFile);
  dataFile = ReadObjects(objectList, bgListSize, dataFile);
  dataFile = ReadLinks(linkList, dataFile);
  fclose(dataFile);
  bColor = GetColor(128, 128, 255);
}
TitleScene::~TitleScene()
{
  for (size_t i = 0; i < gHandleList.size(); i++) DeleteGraph(gHandleList[i]);
  for (size_t i = 0; i < fHandleList.size(); i++) DeleteFontToHandle(fHandleList[i]);
}
Scene TitleScene::Exe()
{
  memcpy_s(oKerBuffer, 256, keyBuffer, 256);
  GetHitKeyStateAll(keyBuffer);
  for (int i = 0; i < 256; i++) eKeyBuffer[i] = keyBuffer[i] & ~oKerBuffer[i];
  if (eKeyBuffer[KEY_INPUT_UP])   select = (select + (int)(linkList.size()) - 1) % (int)(linkList.size());
  if (eKeyBuffer[KEY_INPUT_DOWN]) select = ++select % (int)(linkList.size());
  if (eKeyBuffer[KEY_INPUT_Z]) {
    switch (linkList[select].link) {
    case startLink:
      return gameScene;
    case endLink:
      return endScene;
    }
  }
  return preserve;
}
void TitleScene::Draw()
{
  for (size_t i = 0; i < bgListSize; i++) DrawObject(objectList[i]);
  DrawBox(linkList[select].posX, linkList[select].posY, linkList[select].posX + linkList[select].sizeX - 1, linkList[select].posY + linkList[select].sizeY - 1, bColor, true);
  for (size_t i = bgListSize; i < objectList.size(); i++) DrawObject(objectList[i]);
}
FILE *TitleScene::ReadText(char *text, FILE *dataFile)
{
  int length;
  fread_s(&length, sizeof(int), sizeof(int), 1, dataFile);
  fread_s(text, sizeof(char) * length, sizeof(char), length, dataFile);
  text[length] = '\0';
  return dataFile;
}
FILE *TitleScene::LoadImages(vector<int> &gHandleList, FILE *dataFile)
{
  int size;
  char filePath[TEXTSIZE];
  fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
  for (int i = 0; i < size; i++) {
    dataFile = ReadText(filePath, dataFile);
    gHandleList.push_back(LoadGraph(filePath));
  }
  return dataFile;
}
FILE *TitleScene::LoadColors(vector<unsigned int> &colorList, FILE *dataFile)
{
  int size;
  fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
  for (int i = 0; i < size; i++) {
    unsigned int color;
    fread_s(&color, sizeof(unsigned int), sizeof(unsigned int), 1, dataFile);
    colorList.push_back(color);
  }
  return dataFile;
}
FILE *TitleScene::CreateFonts(vector<int> &fHandleList, FILE *dataFile)
{
  int size, fontSize;
  char fontName[TEXTSIZE];
  fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
  for (int i = 0; i < size; i++) {
    dataFile = ReadText(fontName, dataFile);
    fread_s(&fontSize, sizeof(int), sizeof(int), 1, dataFile);
    fHandleList.push_back(CreateFontToHandle(fontName, fontSize, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8));
  }
  return dataFile;
}
FILE *TitleScene::ReadObjects(vector<Object> &objectList, int &bgSize, FILE *dataFile)
{
  int size;
  char text[TEXTSIZE];
  fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
  fread_s(&bgSize, sizeof(int), sizeof(int), 1, dataFile);
  for (int i = 0; i < size; i++) {
    Object object;
    fread_s(&object.type, sizeof(ObjectType), sizeof(ObjectType), 1, dataFile);
    fread_s(&object.posX, sizeof(int) * 5, sizeof(int), 5, dataFile);
    if (object.type == ObjectType::text) {
      fread_s(&object.colorID, sizeof(int), sizeof(int), 1, dataFile);
      dataFile = ReadText(text, dataFile);
      object.text += text;
    }
    objectList.push_back(object);
  }
  return dataFile;
}
FILE *TitleScene::ReadLinks(vector<Link> &linkList, FILE *dataFile)
{
  int size;
  fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
  for (int i = 0; i < size; i++) {
    Link link;
    fread_s(&link.posX, sizeof(int) * 4, sizeof(int), 4, dataFile);
    fread_s(&link.link, sizeof(LinkType), sizeof(LinkType), 1, dataFile);
    linkList.push_back(link);
  }
  return dataFile;
}
void TitleScene::DrawObject(const Object &object) const
{
  switch (object.type) {
  case image:
    DrawExtendGraph(object.posX, object.posY,
      object.posX + object.sizeX - 1,
      object.posY + object.sizeY - 1,
      gHandleList[object.id], true);
    break;
  case text:
    DrawStringToHandle(object.posX, object.posY, object.text.c_str(), colorList[object.colorID], fHandleList[object.id]);
    break;
  }
}