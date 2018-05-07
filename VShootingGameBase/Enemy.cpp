#include "Enemy.h"
#include "Bullet.h"

void Enemy::Exe(DrawManager *dm, int *area, BaseObject **bList, BaseObject *enemy)
{
  if (isExist) {
    DirectionType direction = pDataList[patternID].list[counter % pDataList[patternID].size].direction;
    switch (pDataList[patternID].list[counter++ % pDataList[patternID].size].pattern) {
    case move_normal:
      switch (direction)
      {
      case up:
        pos.y -= 1.0;
        break;
      case down:
        pos.y += 1.0;
        break;
      case right:
        pos.x += 1.0;
        break;
      case left:
        pos.x -= 1.0;
        break;
      case player:
        Vector<double> v = enemy->GetPosition() - pos;
        v.normalize();
        pos += v;
        break;
      }
      break;
    case shot:
      Vector<double> v;
      switch (direction)
      {
      case up:
        v.set(0.0, -3.0);
        break;
      case down:
        v.set(0.0, 3.0);
        break;
      case right:
        v.set(3.0, 0.0);
        break;
      case left:
        v.set(-3.0, 0.0);
        break;
      case player:
        v = enemy->GetPosition() - pos;
        v.normalize();
        v *= 3.0;
        break;
      }
      Shoot(bList, pos, 0.0, v, 7);
      break;
      counter++;
      break;
    }
    if (pos.x < -dm->GetDSize(graphicID).x) isExist = false;
    else if (pos.x > area[2] + dm->GetDSize(graphicID).x) isExist = false;
    if (pos.y < -dm->GetDSize(graphicID).y) isExist = false;
    else if (pos.y > area[3] + dm->GetDSize(graphicID).y) isExist = false;
    hitboxID = dm->GetHitBoxID(graphicID);
  }
}
void Enemy::Draw(DrawManager *dm)
{
  if (isExist) dm->Draw((int)pos.x, (int)pos.y, angle, graphicID, counter, (hitCounter-- > 0 ? true : false));
}
void Enemy::Hit()
{
  hp--;
  hitCounter = 2;
  if (hp <= 0) {
    isExist = false;
  }
}
void Enemy::Spawn(Vector<double> &p, int gID, int pID)
{
  isExist = true;
  pos = p;
  graphicID = gID;
  hp = 6;
  patternID = pID;
  counter = 0;
  hitCounter = 0;
}
void Enemy::ReadPatternData(const char *dataFileName)
{
  FILE *dataFile;
  fopen_s(&dataFile, dataFileName, "rb");
  fread_s(&pDataListSize, sizeof(int), sizeof(int), 1, dataFile);
  pDataList = new PatternData[pDataListSize];
  for (int i = 0; i < pDataListSize; i++) {
    fread_s(&pDataList[i].size, sizeof(int), sizeof(int), 1, dataFile);
    pDataList[i].list = new BasePattern[pDataList[i].size];
    fread_s(pDataList[i].list, sizeof(BasePattern) * pDataList[i].size, sizeof(BasePattern), pDataList[i].size, dataFile);
  }
  fclose(dataFile);
}
void Enemy::DeletePatternData()
{
  for (int i = 0; i < pDataListSize; i++) delete[] pDataList[i].list;
  delete[] pDataList;
}
void Enemy::Shoot(BaseObject **bList, Vector<double> &p, const double &Angle, Vector<double> &v, int gID)
{
  for (int i = 0; i < EBULLET_MAX_SIZE; i++) {
    if (!bList[i]->IsExist()) {
      dynamic_cast<Bullet*>(bList[i])->Shoot(p, Angle, v, gID);
      break;
    }
  }
}
PatternData *Enemy::pDataList;
int Enemy::pDataListSize;