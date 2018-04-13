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
    for (unsigned int i = 0; i < shotData.size(); i++)
    {
      Vector<double> bPos = pos + shotData[i].pos;
      Shoot(bList, bPos, shotData[i].angle, shotData[i].v, 4, 1);
    }
    shotWait = shotWaitTime;
  }
  gPattern = 0;
  if (move.y > 0.0) gPattern = 3;
  else {
    if (move.x > 0.0) gPattern = 1;
    else if (move.x < 0.0) gPattern = 2;
  }
  if (move.getLengthSQ() > 1.0) pos += move * (speed * M_SQRT1_2);
  else pos += move * speed;
  if (pos.x < dm->GetDSize(gPattern).x / 2) pos.x = (double)(dm->GetDSize(gPattern).x / 2);
  else if (pos.x > area[2] - dm->GetDSize(gPattern).x / 2) pos.x = (double)(area[2] - dm->GetDSize(gPattern).x / 2);
  if (pos.y < dm->GetDSize(gPattern).y / 2) pos.y = (double)(dm->GetDSize(gPattern).y / 2);
  else if (pos.y > area[3] - dm->GetDSize(gPattern).y / 2) pos.y = (double)(area[3] - dm->GetDSize(gPattern).y / 2);
}
void Player::Draw(DrawManager *dm)
{
  dm->Draw((int)pos.x, (int)pos.y, angle, gPattern, 0);
}
void Player::Hit() { }
void Player::Shoot(BaseObject **bList, Vector<double> &p, const double &Angle, Vector<double> &v, int gP, int hbP)
{
  for (int i = 0; i < PBULLET_MAX_SIZE; i++) {
    if (!bList[i]->IsExist()) {
      dynamic_cast<Bullet*>(bList[i])->Shoot(p, Angle, v, gP, hbP);
      break;
    }
  }
}
FILE *Player::ReadPlayerData(FILE *dataFile)
{
  PlayerData data;
  fread_s(&data, sizeof(double) * 3, sizeof(double), 3, dataFile);
  fread_s(&data.shotWait, sizeof(int), sizeof(int), 1, dataFile);
  pos.set(data.posX, data.posY);
  speed = data.speed;
  shotWaitTime = data.shotWait;
  int size;
  fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
  for (int i = 0; i < size; i++) {
    BulletData bulletData;
    fread_s(&bulletData.pos, sizeof(double) * 2, sizeof(double), 2, dataFile);
    fread_s(&bulletData.v, sizeof(double) * 2, sizeof(double), 2, dataFile);
    fread_s(&bulletData.angle, sizeof(double), sizeof(double), 1, dataFile);
    shotData.push_back(bulletData);
  }
  return dataFile;
}