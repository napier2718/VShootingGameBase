#include "Player.h"
#include "Bullet.h"

#include "DxLib.h"

Player::Player() :BaseObject(), speed(3.0), shotWait(0)
{
  isExist = true;
  pos.set(200.0, 500.0);
}
void Player::Exe(DrawManager *dm, int *area, BaseObject **bList)
{
  Vector<double> move;
  char keyBuffer[256];
  GetHitKeyStateAll(keyBuffer);
  if (keyBuffer[KEY_INPUT_UP])    move.y--;
  if (keyBuffer[KEY_INPUT_DOWN])  move.y++;
  if (keyBuffer[KEY_INPUT_RIGHT]) move.x++;
  if (keyBuffer[KEY_INPUT_LEFT])  move.x--;
  if (keyBuffer[KEY_INPUT_Z] && shotWait == 0) {
    Shoot(bList, Vector<double>(pos.x - 4.0, pos.y - 6.0), -30.0, Vector<double>(-4.62, -8.0), 4, 1);
    Shoot(bList, Vector<double>(pos.x + 4.0, pos.y - 6.0),  30.0, Vector<double>( 4.62, -8.0), 4, 1);
    shotWait = 8;
  }
  else {
    if (--shotWait < 0) shotWait = 0;
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
void Player::Hit() { isExist = false; }
void Player::Shoot(BaseObject **bList, Vector<double> &p, const double &Angle, Vector<double> &v, int gP, int hbP)
{
  for (int i = 0; i < 16; i++) {
    if (!bList[i]->IsExist()) {
      dynamic_cast<Bullet*>(bList[i])->Shoot(p, Angle, v, gP, hbP);
      break;
    }
  }
}