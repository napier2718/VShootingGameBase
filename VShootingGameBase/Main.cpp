#include "DxLib.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>

#define TEXTSIZE 128

using namespace std;

enum ObjectType
{
  image,
  text,
};
struct Object
{
  ObjectType type;
  int posX, posY;
  int sizeX, sizeY;
  int id;
  string text;
};
enum LinkType
{
  none,
  start,
  end,
};
struct Link
{
  LinkType link;
  int posX, posY;
  int sizeX, sizeY;
};

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
struct DrawPattern
{
  int dSize[2];
  int gHandleID;
};
class DrawManager
{
public:
  DrawManager()
  {
    LoadDivGraph("resource\\player.png", 16, 4, 4, 16, 16, gHandle);
    LoadDivGraph("resource\\bullet.png", 16, 4, 4, 8, 8,   gHandle + 16);
    LoadDivGraph("resource\\enemy.png", 16, 4, 4, 16, 16, gHandle + 32);
    dPattern[0].dSize[0] = 32;
    dPattern[0].dSize[1] = 32;
    dPattern[0].gHandleID = 0;
    dPattern[1].dSize[0] = 32;
    dPattern[1].dSize[1] = 32;
    dPattern[1].gHandleID = 1;
    dPattern[2].dSize[0] = 32;
    dPattern[2].dSize[1] = 32;
    dPattern[2].gHandleID = 2;
    dPattern[3].dSize[0] = 32;
    dPattern[3].dSize[1] = 32;
    dPattern[3].gHandleID = 3;
    dPattern[4].dSize[0] = 16;
    dPattern[4].dSize[1] = 16;
    dPattern[4].gHandleID = 16;
    dPattern[5].dSize[0] = 32;
    dPattern[5].dSize[1] = 32;
    dPattern[5].gHandleID = 32;
  }
  ~DrawManager()
  {
    for (int i = 0; i < 48; i++) DeleteGraph(gHandle[i]);
  }
  void Draw(int posX, int posY, int pattern, int animeFrame, int *area)
  {
    DrawExtendGraph(posX + area[0] - dPattern[pattern].dSize[0] / 2,
                    posY + area[1] - dPattern[pattern].dSize[1] / 2,
                    posX + area[0] + dPattern[pattern].dSize[0] / 2 - 1,
                    posY + area[1] + dPattern[pattern].dSize[1] / 2 - 1,
                    gHandle[dPattern[pattern].gHandleID + animeFrame], true);
  }
  int *GetDSize(int pattern) { return dPattern[pattern].dSize; }
private:
  DrawPattern dPattern[10];
  int gHandle[100];
};
class Bullet
{
public:
  Bullet() :isExist(false) {}
  void Exe(DrawManager *dm, int *area)
  {
    if (isExist) {
      posX += velX;
      posY += velY;
      if (posX < -dm->GetDSize(gPattern)[0] / 2) isExist = false;
      else if (posX > area[2] + dm->GetDSize(gPattern)[0] / 2 )isExist = false;
      if (posY < -dm->GetDSize(gPattern)[1] / 2) isExist = false;
      else if (posY > area[3] + dm->GetDSize(gPattern)[1] / 2) isExist = false;
    }
  }
  void Draw(DrawManager *dm, int *area)
  {
    if (isExist) dm->Draw((int)posX, (int)posY, gPattern, 0, area); 
  }
  bool IsExist() const { return isExist; }
  void Shot(double pX, double pY, double vX, double vY, int gP)
  {
    isExist = true;
    posX = pX;
    posY = pY;
    velX = vX;
    velY = vY;
    gPattern = gP;
  }
private:
  bool isExist;
  double posX, posY;
  double velX, velY;
  int gPattern;
};
class BulletManager
{
public:
  BulletManager()
  {
    for (int i = 0; i < 16; i++) bullet[i] = new Bullet();
  }
  ~BulletManager()
  {
    for (int i = 0; i < 16; i++) delete bullet[i];
  }
  void Exe(DrawManager *dm, int *area)
  {
    for (int i = 0; i < 16; i++) bullet[i]->Exe(dm, area);
  }
  void Draw(DrawManager *dm, int *area)
  {
    for (int i = 0; i < 16; i++) bullet[i]->Draw(dm, area);
  }
  void Shot(double pX, double pY, double vX, double vY, int gPattern)
  {
    for (int i = 0; i < 16; i++) {
      if (!bullet[i]->IsExist()) {
        bullet[i]->Shot(pX, pY, vX, vY, gPattern);
        break;
      }
    }
  }
private:
  Bullet *bullet[16];
};
class Player
{
public:
  Player() : posX(200.0), posY(500.0), speed(3.0), shotWait(0) {}
  void Exe(DrawManager *dm, int *area, BulletManager *bm)
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
      bm->Shot(posX - 4.0, posY - 6.0, 0.0, -8.0, 4);
      bm->Shot(posX + 4.0, posY - 6.0, 0.0, -8.0, 4);
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
  void Draw(DrawManager *dm, int *area)
  {
    dm->Draw((int)posX, (int)posY, gPattern, 0, area);
  }
private:
  double posX, posY;
  double speed;
  int gPattern;
  int shotWait;
};
class Enemy
{
public:
  Enemy() :isExist(false) {}
  void Exe(DrawManager *dm, int *area)
  {
    if (isExist) {
      posX += velX;
      posY += velY;
      animeFrame++;
      if (posX < -dm->GetDSize(gPattern)[0] / 2) isExist = false;
      else if (posX > area[2] + dm->GetDSize(gPattern)[0] / 2)isExist = false;
      if (posY < -dm->GetDSize(gPattern)[1] / 2) isExist = false;
      else if (posY > area[3] + dm->GetDSize(gPattern)[1] / 2) isExist = false;
    }
  }
  void Draw(DrawManager *dm, int *area)
  {
    if (isExist) dm->Draw((int)posX, (int)posY, gPattern, (animeFrame / 6) % 6, area);
  }
  bool IsExist() const { return isExist; }
  void Spawn(double pX, double pY, double vX, double vY, int gP)
  {
    isExist = true;
    posX = pX;
    posY = pY;
    velX = vX;
    velY = vY;
    gPattern = gP;
    animeFrame = 0;
  }
private:
  bool isExist;
  double posX, posY;
  double velX, velY;
  int gPattern;
  int animeFrame;
};
class EnemyManager
{
public:
  EnemyManager() : spawnWait(20)
  {
    for (int i = 0; i < 16; i++) enemy[i] = new Enemy();
  }
  ~EnemyManager()
  {
    for (int i = 0; i < 16; i++) delete enemy[i];
  }
  void Exe(DrawManager *dm, int *area)
  {
    if (--spawnWait == 0) {
      Spawn(100, 0, 0, 2, 5);
      spawnWait = 40;
    }
    for (int i = 0; i < 16; i++) enemy[i]->Exe(dm, area);
  }
  void Draw(DrawManager *dm, int *area)
  {
    for (int i = 0; i < 16; i++) enemy[i]->Draw(dm, area);
  }
  void Spawn(double pX, double pY, double vX, double vY, int gPattern)
  {
    for (int i = 0; i < 16; i++) {
      if (!enemy[i]->IsExist()) {
        enemy[i]->Spawn(pX, pY, vX, vY, gPattern);
        break;
      }
    }
  }
private:
  Enemy *enemy[16];
  int spawnWait;
};

class TitleScene : public BaseScene
{
public:
  TitleScene() :select(0) 
  {
    FILE *dataFile;
    fopen_s(&dataFile, "data\\title.data", "rb");
    dataFile = LoadImages(gHandleList, dataFile);
    dataFile = CreateFonts(fHandleList, dataFile);
    dataFile = ReadObjects(bgList, dataFile);
    dataFile = ReadObjects(objectList, dataFile);
    dataFile = ReadLinks(linkList, dataFile);
    fclose(dataFile);
    fColor = GetColor(0, 255, 128);
    bColor = GetColor(128, 128, 255);
  }
  ~TitleScene()
  {
    for (size_t i = 0; i < gHandleList.size(); i++) DeleteGraph(gHandleList[i]);
    for (size_t i = 0; i < fHandleList.size(); i++) DeleteFontToHandle(fHandleList[i]);
  }
  virtual int Exe()
  {
    memcpy_s(oKerBuffer, 256, keyBuffer, 256);
    GetHitKeyStateAll(keyBuffer);
    for (int i = 0; i < 256; i++) eKeyBuffer[i] = keyBuffer[i] & ~oKerBuffer[i];
    if (eKeyBuffer[KEY_INPUT_UP])   select = (select + (int)(linkList.size()) - 1) % (int)(linkList.size());
    if (eKeyBuffer[KEY_INPUT_DOWN]) select = ++select % (int)(linkList.size());
    if (eKeyBuffer[KEY_INPUT_Z]) {
      switch (linkList[select].link) {
      case start:
        return 1;
      case LinkType::end:
        return -1;
      }
    }
    return 0;
  }
  virtual void Draw()
  {
    for (size_t i = 0; i < bgList.size(); i++) DrawObject(bgList[i]);
    DrawBox(linkList[select].posX, linkList[select].posY, linkList[select].posX + linkList[select].sizeX - 1, linkList[select].posY + linkList[select].sizeY - 1, bColor, true);
    for (size_t i = 0; i < objectList.size(); i++) DrawObject(objectList[i]);
  }
private:
  FILE *ReadText(char *text, FILE *dataFile)
  {
    int length;
    fread_s(&length, sizeof(int), sizeof(int), 1, dataFile);
    fread_s(text,    sizeof(char) * length, sizeof(char), length, dataFile);
    text[length] = '\0';
    return dataFile;
  }
  FILE *LoadImages(vector<int> &gHandleList, FILE *dataFile)
  {
    int size;
    char filePath[TEXTSIZE];
    fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
    for (int i = 0; i < size; i++) {
      dataFile = ReadText(filePath, dataFile);
      gHandleList.push_back(LoadGraph(filePath));
    }
    return dataFile;
  }
  FILE *CreateFonts(vector<int> &fHandleList, FILE *dataFile)
  {
    int size, fontSize;
    char fontName[TEXTSIZE];
    fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
    for (int i = 0; i < size; i++) {
      dataFile = ReadText(fontName, dataFile);
      fread_s(&fontSize, sizeof(int), sizeof(int), 1, dataFile);
      fHandleList.push_back(CreateFontToHandle(fontName, fontSize, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8));
    }
    return dataFile;
  }
  FILE *ReadObjects(vector<Object> &objectList, FILE *dataFile)
  {
    int size;
    char text[TEXTSIZE];
    fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
    for (int i = 0; i < size; i++) {
      Object object;
      fread_s(&object.type, sizeof(ObjectType), sizeof(ObjectType), 1, dataFile);
      fread_s(&object.posX, sizeof(int) * 5, sizeof(int), 5, dataFile);
      if (object.type == ObjectType::text) {
        dataFile = ReadText(text, dataFile);
        object.text += text;
      }
      objectList.push_back(object);
    }
    return dataFile;
  }
  FILE *ReadLinks(vector<Link> &linkList, FILE *dataFile)
  {
    int size;
    fread_s(&size, sizeof(int), sizeof(int), 1, dataFile);
    for (int i = 0; i < size; i++) {
      Link link;
      fread_s(&link.posX, sizeof(int) * 4, sizeof(int), 4, dataFile);
      fread_s(&link.link, sizeof(LinkType), sizeof(LinkType), 1, dataFile);
      linkList.push_back(link);
    }
    return dataFile;
  }
  void DrawObject(const Object &object) const
  {
    switch (object.type) {
    case image:
      DrawExtendGraph(object.posX, object.posY,
                      object.posX + object.sizeX - 1,
                      object.posY + object.sizeY - 1,
                      gHandleList[object.id], true);
      break;
    case text:
      DrawStringToHandle(object.posX, object.posY, object.text.c_str(), fColor, fHandleList[object.id]);
      break;
    }
  }
  vector<int> gHandleList;
  vector<int> fHandleList;
  vector<Object> bgList, objectList;
  vector<Link> linkList;
  char keyBuffer[256], oKerBuffer[256], eKeyBuffer[256];
  int select;
  int fColor, bColor;
};
class GameScene : public BaseScene
{
public:
  GameScene()
  {
    ui = new UI();
    dm = new DrawManager();
    player = new Player();
    bm = new BulletManager();
    em = new EnemyManager();
  }
  ~GameScene()
  {
    delete ui;
    delete dm;
    delete player;
    delete bm;
    delete em;
  }
  virtual int Exe()
  {
    player->Exe(dm, ui->GetArea(), bm);
    bm->Exe(dm, ui->GetArea());
    em->Exe(dm, ui->GetArea());
    return 0;
  }
  virtual void Draw()
  {
    ui->Draw();
    bm->Draw(dm, ui->GetArea());
    em->Draw(dm, ui->GetArea());
    player->Draw(dm, ui->GetArea());
  }
private:
  UI *ui;
  DrawManager *dm;
  Player *player;
  BulletManager *bm;
  EnemyManager *em;
};

// 初期化用関数(正常終了でtrueを返す)
bool Initialize(bool IsWindow, char *WindowTitle)
{
  SetOutApplicationLogValidFlag(false);         // ログを生成しない
  ChangeWindowMode(IsWindow);                   // ウインドウで起動させるかどうか
  SetWindowSizeChangeEnableFlag(false, false);  // ウィンドウサイズ固定
  SetGraphMode(800, 600, 32);                   // 解像度設定
  if (IsWindow) {
    SetWindowSize(800, 600);                    // ウィンドウサイズ設定
    SetMainWindowText(WindowTitle);             // ウィンドウのタイトルを変更
  }
  if (DxLib_Init() == -1) return false;         // DXライブラリ初期化処理 エラーが起きたら終了
  SetDrawScreen(DX_SCREEN_BACK);                // 描画先を裏画面にする
  return true;
}

// ループ始めに行わせる関数(正常時にtrueを返す)
bool StartLoop()
{
  ScreenFlip();       // 裏画面の内容を表画面に反映
  ClearDrawScreen();  // 画面をクリア
  // ウインドウズのメッセージループに代わる処理を行う
  if (ProcessMessage() == -1) return false;
  // ESCキーが押されたら終了
  if (CheckHitKey(KEY_INPUT_ESCAPE)) return false;
  return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // 初期化をする
  if (!Initialize(true, "縦スクロールシューティングベース")) return -1;
  BaseScene *scene = new TitleScene();
  // ループ
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
  DxLib_End();  // DXライブラリ使用の終了処理
  return 0;
}