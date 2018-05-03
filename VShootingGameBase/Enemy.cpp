#include "Enemy.h"

void Enemy::Exe(DrawManager *dm, int *area, BaseObject **bList)
{
  if (isExist) {
    pos += vel;
    animeFrame++;
    if (pos.x < -dm->GetDSize(graphicID).x) isExist = false;
    else if (pos.x > area[2] + dm->GetDSize(graphicID).x) isExist = false;
    if (pos.y < -dm->GetDSize(graphicID).y) isExist = false;
    else if (pos.y > area[3] + dm->GetDSize(graphicID).y) isExist = false;
    hitboxID = dm->GetHitBoxID(graphicID);
  }
}
void Enemy::Draw(DrawManager *dm)
{
  if (isExist) dm->Draw((int)pos.x, (int)pos.y, angle, graphicID, animeFrame, (hitCounter-- > 0 ? true : false));
}
void Enemy::Hit()
{
  hp--;
  hitCounter = 2;
  if (hp <= 0) {
    isExist = false;
  }
}
void Enemy::Spawn(Vector<double> &p, Vector<double> &v, int gID)
{
  isExist = true;
  pos = p;
  graphicID = gID;
  vel = v;
  hp = 6;
  animeFrame = 0;
  hitCounter = 0;
}