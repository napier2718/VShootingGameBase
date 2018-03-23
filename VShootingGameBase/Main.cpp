#include "DxLib.h"
#include <math.h>

class BaseScene
{
public:
  virtual int Exe() = 0;
  virtual void Draw() = 0;
};
class UI
{
public:
  UI()
  {
    area[0] = 20;
    area[1] = 20;
    area[2] = 400;
    area[3] = 560;
    areaColor = GetColor(100, 100, 100);
  }
  ~UI(){}
  int *GetArea() { return area; }
  void Draw()
  {
    DrawBox(area[0], area[1], area[0] + area[2] - 1, area[1] + area[3] - 1, areaColor, true);
  }
private:
  int area[4];
  int areaColor;
};
class Bullet
{
public:
  Bullet(int GHandle) :isExist(false), gHandle(GHandle)
  {
    dSize[0] = 16;
    dSize[1] = 16;
  }
  void Exe(int *area)
  {
    if (isExist) {
      posX += velX;
      posY += velY;
      if (posX < -dSize[0] / 2) isExist = false;
      else if (posX > area[2] + dSize[0] / 2) isExist = false;
      if (posY < -dSize[1] / 2) isExist = false;
      else if (posY > area[3] + dSize[1] / 2) isExist = false;
    }
  }
  void Draw(int *area)
  {
    if (isExist) DrawExtendGraph((int)posX + area[0] - dSize[0] / 2, (int)posY + area[1] - dSize[1] / 2, (int)posX + area[0] + dSize[0] / 2 - 1, (int)posY + area[1] + dSize[1] / 2 - 1, gHandle, true);
  }
  bool IsExist() const { return isExist; }
  void Shot(double pX, double pY, double vX, double vY)
  {
    isExist = true;
    posX = pX;
    posY = pY;
    velX = vX;
    velY = vY;
  }
private:
  bool isExist;
  double posX, posY;
  double velX, velY;
  int gHandle;
  int dSize[2];
};
class BulletManager
{
public:
  BulletManager()
  {
    LoadDivGraph("resource\\bullet.png", 16, 4, 4, 8, 8, gBHandle);
    for (int i = 0; i < 16; i++) bullet[i] = new Bullet(gBHandle[0]);
  }
  ~BulletManager()
  {
    for (int i = 0; i < 16; i++) delete bullet[i];
    for (int i = 0; i < 16; i++) DeleteGraph(gBHandle[i]);
  }
  void Exe(int *area)
  {
    for (int i = 0; i < 16; i++) bullet[i]->Exe(area);
  }
  void Draw(int *area)
  {
    for (int i = 0; i < 16; i++) bullet[i]->Draw(area);
  }
  void Shot(double pX, double pY, double vX, double vY)
  {
    for (int i = 0; i < 16; i++) {
      if (!bullet[i]->IsExist()) {
        bullet[i]->Shot(pX, pY, vX, vY);
        break;
      }
    }
  }
private:
  int gBHandle[16];
  Bullet *bullet[16];
};
class Player
{
public:
  Player() : posX(200.0), posY(500.0), speed(3.0), shotWait(0)
  {
    gSize[0] = 16;
    gSize[1] = 16;
    dSize[0] = 32;
    dSize[1] = 32;
    LoadDivGraph("resource\\player.png", 16, 4, 4, gSize[0], gSize[1], gHandle);
  }
  ~Player()
  {
    for (int i = 0; i < 16; i++) DeleteGraph(gHandle[i]);
  }
  void Exe(int *area, BulletManager *bm)
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
      bm->Shot(posX - 4.0, posY - 6.0, 0.0, -8.0);
      bm->Shot(posX + 4.0, posY - 6.0, 0.0, -8.0);
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
    if (posX < dSize[0] / 2) posX = (double)(dSize[0] / 2);
    else if (posX > area[2] - dSize[0] / 2) posX = (double)(area[2] - dSize[0] / 2);
    if (posY < dSize[1] / 2) posY = (double)(dSize[1] / 2);
    else if (posY > area[3] - dSize[1] / 2) posY = (double)(area[3] - dSize[1] / 2);
  }
  void Draw(int *area)
  {
    DrawExtendGraph((int)posX + area[0] - dSize[0] / 2, (int)posY + area[1] - dSize[1] / 2, (int)posX + area[0] + dSize[0] / 2 - 1, (int)posY + area[1] + dSize[1] / 2 - 1, gHandle[gPattern], true);
  }
private:
  double posX, posY;
  double speed;
  int gPattern;
  int gHandle[16];
  int gSize[2], dSize[2];
  int shotWait;
};
class Enemy
{
public:
  Enemy()
  {}
};

class TitleScene : public BaseScene
{
public:
  TitleScene() :select(0) 
  {
    fHandle = CreateFontToHandle("���C���I", 32, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
    fColor = GetColor(0, 255, 128);
    bColor = GetColor(128, 128, 255);
  }
  ~TitleScene()
  {
    DeleteFontToHandle(fHandle);
  }
  virtual int Exe()
  {
    memcpy_s(oKerBuffer, 256, keyBuffer, 256);
    GetHitKeyStateAll(keyBuffer);
    for (int i = 0; i < 256; i++) eKeyBuffer[i] = keyBuffer[i] & ~oKerBuffer[i];
    if (eKeyBuffer[KEY_INPUT_UP])   select = (select + 2 - 1) % 2;
    if (eKeyBuffer[KEY_INPUT_DOWN]) select = ++select % 2;
    if (eKeyBuffer[KEY_INPUT_Z]) {
      switch (select) {
      case 0:
        return 1;
      case 1:
        return -1;
      }
    }
    return 0;
  }
  virtual void Draw()
  {
    DrawBox(390, 290 + select * 40, 546, 342 + select * 40, bColor, true);
    DrawStringToHandle(400, 300, "�X�^�[�g", fColor, fHandle);
    DrawStringToHandle(430, 340, "�I��", fColor, fHandle);
  }
private:
  char keyBuffer[256], oKerBuffer[256], eKeyBuffer[256];
  int select;
  int fHandle;
  int fColor, bColor;
};
class GameScene : public BaseScene
{
public:
  GameScene()
  {
    ui = new UI();
    player = new Player();
    bm = new BulletManager();
  }
  ~GameScene()
  {
    delete ui;
    delete player;
    delete bm;
  }
  virtual int Exe()
  {
    player->Exe(ui->GetArea(), bm);
    bm->Exe(ui->GetArea());
    return 0;
  }
  virtual void Draw()
  {
    ui->Draw();
    bm->Draw(ui->GetArea());
    player->Draw(ui->GetArea());
  }
private:
  UI *ui;
  Player *player;
  BulletManager *bm;
};

// �������p�֐�(����I����true��Ԃ�)
bool Initialize(bool IsWindow, char *WindowTitle)
{
  SetOutApplicationLogValidFlag(false);         // ���O�𐶐����Ȃ�
  ChangeWindowMode(IsWindow);                   // �E�C���h�E�ŋN�������邩�ǂ���
  SetWindowSizeChangeEnableFlag(false, false);  // �E�B���h�E�T�C�Y�Œ�
  SetGraphMode(800, 600, 32);                   // �𑜓x�ݒ�
  if (IsWindow) {
    SetWindowSize(800, 600);                    // �E�B���h�E�T�C�Y�ݒ�
    SetMainWindowText(WindowTitle);             // �E�B���h�E�̃^�C�g����ύX
  }
  if (DxLib_Init() == -1) return false;         // DX���C�u�������������� �G���[���N������I��
  SetDrawScreen(DX_SCREEN_BACK);                // �`���𗠉�ʂɂ���
  return true;
}

// ���[�v�n�߂ɍs�킹��֐�(���펞��true��Ԃ�)
bool StartLoop()
{
  ScreenFlip();       // ����ʂ̓��e��\��ʂɔ��f
  ClearDrawScreen();  // ��ʂ��N���A
  // �E�C���h�E�Y�̃��b�Z�[�W���[�v�ɑ��鏈�����s��
  if (ProcessMessage() == -1) return false;
  // ESC�L�[�������ꂽ��I��
  if (CheckHitKey(KEY_INPUT_ESCAPE)) return false;
  return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // ������������
  if (!Initialize(true, "�c�X�N���[���V���[�e�B���O�x�[�X")) return -1;
  BaseScene *scene = new TitleScene();
  // ���[�v
  while (scene != NULL && StartLoop()) {
    switch (scene->Exe()) {
    case -1:
      delete scene;
      scene = NULL;
      break;
    case 0:
      scene->Draw();
      break;
    case 1:
      delete scene;
      scene = new GameScene();
    }
  }
  DxLib_End();  // DX���C�u�����g�p�̏I������
  return 0;
}