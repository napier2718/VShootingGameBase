#include "Player.h"
#include "Bullet.h"

#include "DxLib.h"
#include <math.h>

Player::Player() :BaseObject(), speed(3.0), shotWait(0)
{
  isExist = true;
  posX = 200.0;
  posY = 500.0;
}
void Player::Exe(DrawManager *dm, int *area, BaseObject **bList)
{
  const double sr2 = sqrt(2);
  int move[2] = { 0,0 };
  char keyBuffer[256];
  GetHitKeyStateAll(keyBuffer);
  if (keyBuffer[KEY_INPUT_UP])    move[1]--;
  if (keyBuffer[KEY_INPUT_DOWN])  move[1]++;
  if (keyBuffer[KEY_INPUT_RIGHT]) move[0]++;
  if (keyBuffer[KEY_INPUT_LEFT])  move[0]--;
  if (keyBuffer[KEY_INPUT_Z] && shotWait == 0) {
    Shoot(bList, posX - 4.0, posY - 6.0, 0.0, -8.0, 4, 1);
    Shoot(bList, posX + 4.0, posY - 6.0, 0.0, -8.0, 4, 1);
    shotWait = 8;
  }
  else {
    if (--shotWait < 0) shotWait = 0;
  }
  gPattern = 0;
  if (move[1] > 0) gPattern = 3;
  else {
    if (move[0] > 0) gPattern = 1;
    else if (move[0] < 0) gPattern = 2;
  }
  if (move[0] * move[0] + move[1] * move[1] == 2) {
    posX += speed / sr2 * move[0];
    posY += speed / sr2 * move[1];
  }
  else {
    posX += speed * move[0];
    posY += speed * move[1];
  }
  if (posX < dm->GetDSize(gPattern)[0] / 2) posX = (double)(dm->GetDSize(gPattern)[0] / 2);
  else if (posX > area[2] - dm->GetDSize(gPattern)[0] / 2) posX = (double)(area[2] - dm->GetDSize(gPattern)[0] / 2);
  if (posY < dm->GetDSize(gPattern)[1] / 2) posY = (double)(dm->GetDSize(gPattern)[1] / 2);
  else if (posY > area[3] - dm->GetDSize(gPattern)[1] / 2) posY = (double)(area[3] - dm->GetDSize(gPattern)[1] / 2);
}
void Player::Draw(DrawManager *dm, int *area)
{
  dm->Draw((int)posX, (int)posY, gPattern, 0, area);
}
void Player::Hit() { isExist = false; }
void Player::Shoot(BaseObject **bList, double pX, double pY, double vX, double vY, int gP, int hbP)
{
  for (int i = 0; i < 16; i++) {
    if (!bList[i]->IsExist()) {
      dynamic_cast<Bullet*>(bList[i])->Shoot(pX, pY, vX, vY, gP, hbP);
      break;
    }
  }
}