#pragma once
#include "BaseObject.h"

enum PatternType
{
  wait,
  normal_move,
  shot,
};
struct PatternData
{
  int size;
  PatternType* list;
};
class Enemy :public BaseObject
{
public:
  Enemy() :BaseObject() {}
  void Exe(DrawManager *dm, int *area, BaseObject **bList);
  void Draw(DrawManager *dm);
  void Hit();
  void Spawn(Vector<double> &p, int gID, int pID);
  static void ReadPatternData(const char *dataFileName);
  static void DeletePatternData();
private:
  void Shoot(BaseObject**, Vector<double>&, const double&, Vector<double>&, int);
  int hp;
  int patternID;
  int counter;
  int hitCounter;
  static PatternData *pDataList;
  static int pDataListSize;
};