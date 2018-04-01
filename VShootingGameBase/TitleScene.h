#pragma once
#include "BaseScene.h"

#include <cstring>
#include <vector>

enum ObjectType
{
  image,
  text,
};
struct Object
{
  ObjectType type;
  int posX, posY;
  int sizeX, sizeY;
  int id;
  std::string text;
};
enum LinkType
{
  none,
  start,
  end,
};
struct Link
{
  LinkType link;
  int posX, posY;
  int sizeX, sizeY;
};

class TitleScene :public BaseScene
{
public:
  TitleScene();
  ~TitleScene();
  int Exe();
  void Draw();
private:
  FILE *ReadText(char*, FILE*);
  FILE *LoadImages(std::vector<int>&, FILE*);
  FILE *CreateFonts(std::vector<int>&, FILE*);
  FILE *ReadObjects(std::vector<Object>&, int&, FILE*);
  FILE *ReadLinks(std::vector<Link>&, FILE*);
  void DrawObject(const Object&) const;
  std::vector<int> gHandleList;
  std::vector<int> fHandleList;
  std::vector<Object> objectList;
  std::vector<Link> linkList;
  int bgListSize;
  char keyBuffer[256], oKerBuffer[256], eKeyBuffer[256];
  int select;
  int fColor, bColor;
};