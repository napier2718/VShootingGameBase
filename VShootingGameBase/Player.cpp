#include "Player.h"
#include "Bullet.h"

#include "DxLib.h"

Player::Player() :BaseObject(), shotWait(0)
{
  FILE *dataFile;
  fopen_s(&dataFile, "data\\player.data", "rb");
  PlayerData data;
  fread_s(&data, sizeof(PlayerData), sizeof(PlayerData), 1, dataFile);
  fclose(dataFile);
  isExist = true;
  pos.set(data.posX, data.posY);
  speed = data.speed;
  shotWaitTime = data.shotWait;
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
    Shoot(bList, Vector<double>(pos.x, pos.y - 6.0), 0.0, Vector<double>(0.0, -8.0), 4, 1);
    Shoot(bList, Vector<double>(pos.x - 2.0, pos.y - 6.0), -5.0, Vector<double>(-0.7, -8.0), 4, 1);
    Shoot(bList, Vector<double>(pos.x + 2.0, pos.y - 6.0),  5.0, Vector<double>( 0.7, -8.0), 4, 1);
    Shoot(bList, Vector<double>(pos.x - 4.0, pos.y - 6.0), -10.0, Vector<double>(-1.41, -8.0), 4, 1);
    Shoot(bList, Vector<double>(pos.x + 4.0, pos.y - 6.0),  10.0, Vector<double>( 1.41, -8.0), 4, 1);
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