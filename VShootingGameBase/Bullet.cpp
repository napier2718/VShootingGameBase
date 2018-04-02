#include "Bullet.h"

void Bullet::Exe(DrawManager *dm, int *area, BaseObject **bList)
{
  if (isExist) {
    pos += vel;
    if (pos.x < -dm->GetDSize(gPattern).x / 2) isExist = false;
    else if (pos.x > area[2] + dm->GetDSize(gPattern).x / 2)isExist = false;
    if (pos.y < -dm->GetDSize(gPattern).y / 2) isExist = false;
    else if (pos.y > area[3] + dm->GetDSize(gPattern).y / 2) isExist = false;
  }
}
void Bullet::Draw(DrawManager *dm)
{
  if (isExist) dm->Draw((int)pos.x, (int)pos.y, angle, gPattern, 0);
}
void Bullet::Hit() { isExist = false; }
void Bullet::Shoot(Vector<double> &p, const double &Angle, Vector<double> &v, int gP, int hbP)
{
  isExist = true;
  pos = p;
  angle = Angle;
  vel = v;
  gPattern = gP;
  hbPattern = hbP;
}