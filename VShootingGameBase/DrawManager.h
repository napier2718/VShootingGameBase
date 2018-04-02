#pragma once
#include "Vector.h"

struct DrawPattern
{
  int gHandleID;
  Vector<int> dSize;
  double rate;
};
class DrawManager
{
public:
  DrawManager(int*);
  ~DrawManager();
  void Draw(int posX, int posY, double &angle, int pattern, int animeFrame);
  Vector<int> &GetDSize(int pattern) { return dPattern[pattern].dSize; }
private:
  void CalcRate(DrawPattern&);
  int *area;
  DrawPattern dPattern[10];
  int gHandle[100];
};