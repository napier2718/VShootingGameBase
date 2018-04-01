#pragma once
#include "DrawManager.h"

class BulletManager;
class BaseObject
{
public:
  BaseObject() :isExist(false) {}
  virtual void Exe(BulletManager *bm, DrawManager *dm, int *area) = 0;
  virtual void Draw(DrawManager *dm, int *area) = 0;
  bool IsExist() const { return isExist; }
protected:
  bool isExist;
  double posX, posY;
};