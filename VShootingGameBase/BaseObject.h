#pragma once
#include "DrawManager.h"
#include "Vector.h"

class BaseObject
{
  friend class ObjectManager;
public:
  BaseObject() :isExist(false), pos(0.0, 0.0), angle(0.0), graphicID(0), hitboxID(0) {}
  virtual void Exe(DrawManager *dm, int *area, BaseObject **bList, BaseObject *enemy) = 0;
  virtual void Draw(DrawManager *dm) = 0;
  virtual void Hit() = 0;
  bool IsExist() const { return isExist; }
  const Vector<double> &GetPosition() { return pos; }
protected:
  bool isExist;
  Vector<double> pos;
  double angle;
  int graphicID, hitboxID;
};