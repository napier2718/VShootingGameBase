#pragma once
#include "DrawManager.h"

class BaseObject
{
  friend class ObjectManager;
public:
  BaseObject() :isExist(false), posX(0.0), posY(0.0), hbPattern(0) {}
  virtual void Exe(DrawManager *dm, int *area, BaseObject **bList) = 0;
  virtual void Draw(DrawManager *dm, int *area) = 0;
  virtual void Hit() = 0;
  bool IsExist() const { return isExist; }
protected:
  bool isExist;
  double posX, posY;
  int hbPattern;
};