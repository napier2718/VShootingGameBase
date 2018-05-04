#include "Player.h"
#include "Bullet.h"

#include "DxLib.h"

Player::Player(const char *dataFileName) :BaseObject(), shotWait(0)
{
  FILE *dataFile;
  fopen_s(&dataFile, dataFileName, "rb");
  dataFile = ReadPlayerData(dataFile);
  fclose(dataFile);
  isExist = true;
}
void Player::Exe(DrawManager *dm, int *area, BaseObject **bList)
{
  char keyBuffer[256];
  GetHitKeyStateAll(keyBuffer);
  Vector<double> move;
  if (keyBuffer[KEY_INPUT_UP])    move.y--;
  if (keyBuffer[KEY_INPUT_DOWN])  move.y++;
  if (keyBuffer[KEY_INPUT_RIGHT]) move.x++;
  if (keyBuffer[KEY_INPUT_LEFT])  move.x--;
  if (--shotWait < 0 && keyBuffer[KEY_INPUT_Z]) {
    for (int i = 0; i < shotDataSize; i++)
    {
      Vector<double> bPos = pos + shotData[i].pos;
      Shoot(bList, bPos, shotData[i].angle, shotData[i].v, shotData[i].graphicID);
    }
    shotWait = shotWaitTime;
  }
  graphicID = gStartID;
  if (move.y > 0.0) graphicID = gStartID + 3;
  else {
    if (move.x > 0.0) graphicID = gStartID + 1;
    else if (move.x < 0.0) graphicID = gStartID + 2;
  }
  if (move.getLengthSQ() > 1.0) pos += move * (speed * M_SQRT1_2);
  else pos += move * speed;
  if (pos.x < dm->GetDSize(graphicID).x / 2) pos.x = (double)(dm->GetDSize(graphicID).x / 2);
  else if (pos.x > area[2] - dm->GetDSize(graphicID).x / 2) pos.x = (double)(area[2] - dm->GetDSize(graphicID).x / 2);
  if (pos.y < dm->GetDSize(graphicID).y / 2) pos.y = (double)(dm->GetDSize(graphicID).y / 2);
  else if (pos.y > area[3] - dm->GetDSize(graphicID).y / 2) pos.y = (double)(area[3] - dm->GetDSize(graphicID).y / 2);
  hitboxID = dm->GetHitBoxID(graphicID);
}
void Player::Draw(DrawManager *dm)
{
  dm->Draw((int)pos.x, (int)pos.y, angle, graphicID, 0);
}
void Player::Hit() { }
void Player::Shoot(BaseObject **bList, Vector<double> &p, const double &Angle, Vector<double> &v, int gID)
{
  for (int i = 0; i < PBULLET_MAX_SIZE; i++) {
    if (!bList[i]->IsExist()) {
      dynamic_cast<Bullet*>(bList[i])->Shoot(p, Angle, v, gID);
      break;
    }
  }
}
FILE *Player::ReadPlayerData(FILE *dataFile)
{
  fread_s(&pos, sizeof(double) * 2, sizeof(double), 2, dataFile);
  fread_s(&speed, sizeof(double), sizeof(double), 1, dataFile);
  fread_s(&gStartID, sizeof(int), sizeof(int), 1, dataFile);
  fread_s(&shotWaitTime, sizeof(int), sizeof(int), 1, dataFile);
  graphicID = gStartID;
  fread_s(&shotDataSize, sizeof(int), sizeof(int), 1, dataFile);
  shotData = new BulletData[shotDataSize];
  for (int i = 0; i < shotDataSize; i++) {
    fread_s(&shotData[i].pos, sizeof(double) * 2, sizeof(double), 2, dataFile);
    fread_s(&shotData[i].v, sizeof(double) * 2, sizeof(double), 2, dataFile);
    fread_s(&shotData[i].graphicID, sizeof(int), sizeof(int), 1, dataFile);
    fread_s(&shotData[i].angle, sizeof(double), sizeof(double), 1, dataFile);
  }
  return dataFile;
}