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
  int colorID;
  std::string text;
};
enum LinkType
{
  lNone,
  startLink,
  endLink,
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
  Scene Exe();
  void Draw();
private:
  FILE *ReadText(char*, FILE*);
  FILE *LoadImages(std::vector<int>&, FILE*);
  FILE *LoadColors(std::vector<unsigned int>&, FILE*);
  FILE *CreateFonts(std::vector<int>&, FILE*);
  FILE *ReadObjects(std::vector<Object>&, int&, FILE*);
  FILE *ReadLinks(std::vector<Link>&, FILE*);
  void DrawObject(const Object&) const;
  std::vector<int> gHandleList;
  std::vector<unsigned int> colorList;
  std::vector<int> fHandleList;
  std::vector<Object> objectList;
  std::vector<Link> linkList;
  int bgListSize;
  char keyBuffer[256], oKerBuffer[256], eKeyBuffer[256];
  int select;
  int bColor;
};