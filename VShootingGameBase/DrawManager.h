#pragma once
#include "Vector.h"

#include <cstdio>

struct Graphic
{
  int gHandleID;
  Vector<int> dSize;
  int hitboxID;
  double rate;
  int aFrame, aWaitFrame;
  bool enableAnimation;
};
class DrawManager
{
public:
  DrawManager(const char *dataFileName, int *Area);
  ~DrawManager();
  void Draw(int posX, int posY, double &angle, int graphicID, int animeFrame, bool isHit = false);
  Vector<int> &GetDSize(int graphicID) { return graphicList[graphicID].dSize; }
  int GetHitBoxID(int graphicID) { return graphicList[graphicID].hitboxID; }
private:
  void CalcRate(Graphic&);
  FILE *ReadText(char*, FILE*);
  FILE *LoadImages(FILE*);
  FILE *ReadGraphicData(FILE*);
  int *area;
  Graphic graphicList[10];
  int gHandle[100];
};