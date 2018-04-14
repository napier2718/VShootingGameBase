#pragma once
#include "Vector.h"

#include <cstdio>

struct DrawPattern
{
  int gHandleID;
  Vector<int> dSize;
  double rate;
  int aFrame, aWaitFrame;
  bool enableAnimation;
};
class DrawManager
{
public:
  DrawManager(const char *dataFileName, int *Area);
  ~DrawManager();
  void Draw(int posX, int posY, double &angle, int pattern, int animeFrame, bool isHit = false);
  Vector<int> &GetDSize(int pattern) { return dPattern[pattern].dSize; }
private:
  void CalcRate(DrawPattern&);
  FILE *ReadText(char*, FILE*);
  FILE *LoadImages(FILE*);
  FILE *ReadGraphicData(FILE*);
  int *area;
  DrawPattern dPattern[10];
  int gHandle[100];
};