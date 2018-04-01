#pragma once
struct DrawPattern
{
  int dSize[2];
  int gHandleID;
};
class DrawManager
{
public:
  DrawManager();
  ~DrawManager();
  void Draw(int posX, int posY, int pattern, int animeFrame, int *area);
  int *GetDSize(int pattern) { return dPattern[pattern].dSize; }
private:
  DrawPattern dPattern[10];
  int gHandle[100];
};