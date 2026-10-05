// Slice s005fd260 - cImportExport import helpers + UI::AchievementNotifier + cSPUILayout helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "../s005fa8d0/s005fa8d0.h"

// local vec handle used by the message handler
struct VecHandle { void* mpBegin; uint32_t a; uint32_t b; uint32_t c; uint32_t d; };
void __stdcall FUN_005fd260(void* p, VecHandle* out);      // 0x005fd260
void FUN_005fdca0();                             // 0x005fdca0
uint32_t FUN_005fde30();                         // 0x005fde30
void FUN_005fdaa0(int on);                       // 0x005fdaa0

struct HandlerStub {
  bool Handler(uint32_t id, void* p);
};

// @ 0x005fda40
bool HandlerStub::Handler(uint32_t id, void* p)
{
  if (id == 0x24ce123 && p) {
    VecHandle v;
    VecHandle* pv = &v;
    v.mpBegin = 0; v.a = 0; v.b = 0;
    FUN_005fd260(p, pv);
    if (v.mpBegin && ((int*)v.mpBegin)[-1]) operator delete(v.mpBegin);
  }
  return true;
}

// @ 0x005fdca0
void FUN_005fdca0()
{
}

// @ 0x005fd880
void FUN_005fd880()
{
}

// @ 0x005fe050
void FUN_005fe050()
{
}

// @ 0x005fd260
void FUN_005fd260()
{
}

// @ 0x005fde30
uint32_t FUN_005fde30()
{
  return 0;
}

// @ 0x005fdeb0
void FUN_005fdeb0()
{
}

// @ 0x005fdbb0
void FUN_005fdbb0()
{
}

// @ 0x005fdf40
struct AchievementNotifierData {
  char pad0[0x24];
  int mState;         // +0x24
  float mTimer;       // +0x28
  float mLast;        // +0x2c
  void* m30;          // +0x30
  void* m34;          // +0x34
  char pad38[0x44 - 0x38];
  void* m44;          // +0x44 (cSPUILayout*)
  void Update();
};

void* GetElapsedSecondsF();     // 0x00805080
float GetElapsedSeconds();
void FunDca0(void* arg);
void cSPUISetVisibility(void* layout, int on);   // 0x00810590
void* cSPUIFindWindowByID(void* layout, uint32_t id, int recurse);  // 0x008105b0
void FUN_005fdaa0(int on);

void AchievementNotifierData::Update()
{
  float elapsed = GetElapsedSeconds();
  float dt = elapsed - mLast;
  mLast = elapsed;
  switch (mState) {
    case 0:
      if (m30 != m34) {
        FunDca0(*(void**)((char*)m34 - 4));
        m34 = (char*)m34 - 4;
        mState = 1;
        return;
      }
      break;
    case 1:
      if (FUN_005fde30()) {
        cSPUISetVisibility(m44, 1);
        FUN_005fdaa0(1);
        mTimer = 0.0f;
        mState = 2;
        return;
      }
      break;
    case 2:
      mTimer = mTimer + dt;
      if (5.0f < mTimer) {
        void* w = cSPUIFindWindowByID(m44, 0x6244c50, 1);
        if (w) {
          // (*(vtbl+0x7c))(1,0)
          typedef void (__thiscall *SetFlagFn)(void*, int, int);
          (*(SetFlagFn*)(*(void***)w + 0x7c / 4))(w, 1, 0);
        }
        mTimer = 0.0f;
        mState = 3;
        return;
      }
      break;
    case 3:
      mTimer = mTimer + dt;
      if (3.0f < mTimer) {
        cSPUISetVisibility(m44, 0);
        mState = 0;
      }
      break;
  }
}

// @ 0x005fdaa0
void FUN_005fdaa0(int on)
{
  (void)on;
}
