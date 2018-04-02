#include "TitleScene.h"
#include "GameScene.h"

#include "DxLib.h"

// �������p�֐�(����I����true��Ԃ�)
bool Initialize(bool IsWindow, char *WindowTitle)
{
  SetOutApplicationLogValidFlag(false);         // ���O�𐶐����Ȃ�
  ChangeWindowMode(IsWindow);                   // �E�C���h�E�ŋN�������邩�ǂ���
  SetWindowSizeChangeEnableFlag(false, false);  // �E�B���h�E�T�C�Y�Œ�
  SetGraphMode(WINDOW_X, WINDOW_Y, 32);         // �𑜓x�ݒ�
  if (IsWindow) {
    SetWindowSize(WINDOW_X, WINDOW_Y);          // �E�B���h�E�T�C�Y�ݒ�
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
  DxLib_End();  // DX���C�u�����g�p�̏I������
  return 0;
}