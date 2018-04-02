#include "TitleScene.h"
#include "GameScene.h"

#include "DxLib.h"

// 初期化用関数(正常終了でtrueを返す)
bool Initialize(bool IsWindow, char *WindowTitle)
{
  SetOutApplicationLogValidFlag(false);         // ログを生成しない
  ChangeWindowMode(IsWindow);                   // ウインドウで起動させるかどうか
  SetWindowSizeChangeEnableFlag(false, false);  // ウィンドウサイズ固定
  SetGraphMode(WINDOW_X, WINDOW_Y, 32);         // 解像度設定
  if (IsWindow) {
    SetWindowSize(WINDOW_X, WINDOW_Y);          // ウィンドウサイズ設定
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
    case preserve:
      scene->Draw();
      break;
    case gameScene:
      delete scene;
      scene = new GameScene();
      break;
    case endScene:
      delete scene;
      scene = NULL;
      break;
    }
  }
  DxLib_End();  // DXライブラリ使用の終了処理
  return 0;
}