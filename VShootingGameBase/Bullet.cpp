#include "Bullet.h"

void Bullet::Exe(DrawManager *dm, int *area, BaseObject **bList)
{
  if (isExist) {
    pos += vel;
    if (pos.x < -dm->GetDSize(graphicID).x) isExist = false;
    else if (pos.x > area[2] + dm->GetDSize(graphicID).x) isExist = false;
    if (pos.y < -dm->GetDSize(graphicID).y) isExist = false;
    else if (pos.y > area[3] + dm->GetDSize(graphicID).y) isExist = false;
    hitboxID = dm->GetHitBoxID(graphicID);
  }
}
void Bullet::Draw(DrawManager *dm)
{
  if (isExist) dm->Draw((int)pos.x, (int)pos.y, angle, graphicID, 0);
}
void Bullet::Hit() { isExist = false; }
void Bullet::Shoot(Vector<double> &p, const double &Angle, Vector<double> &v, int gID)
{
  isExist = true;
  pos = p;
  angle = Angle;
  graphicID = gID;
  vel = v;
}