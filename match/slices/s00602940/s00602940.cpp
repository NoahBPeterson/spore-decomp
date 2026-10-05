// Slice s00602940 - cOnlineTab / cSPUISettings tab management.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "../s005fa8d0/s005fa8d0.h"

// ---- 00603170: cOnlineTab::HandleMessage -----------------------------------------------
struct Tab13 { void InitUIState(uint8_t b); };   // 0x00602940
struct Handler13 {
  bool HandleMessage(uint32_t msg, int p3);
};

// @ 0x00603170
bool Handler13::HandleMessage(uint32_t msg, int p3)
{
  if (msg != 0x44db12e && msg != 0x5b96086 && msg != 0x5c5594a) return false;
  uint8_t b = 0;
  if (msg == 0x44db12e && p3 == 0) b = 1;
  ((Tab13*)((char*)this - 0x24))->InitUIState(b);
  return true;
}

// ---- 006035d0: ShowSettingsWindow ------------------------------------------------------
void* operator new(size_t, const char*, int, int, int, int);
struct cSPUISettings13 {
  virtual int AddRef();
  virtual int Release();
  cSPUISettings13();              // 0x00601790
  bool Init(int a);               // 0x00603260
  bool Shutdown();                // 0x00601e60
  bool Apply();                   // 0x00600ab0
  char pad[0x248 - 4];
};

// @ 0x006035d0
bool ShowSettingsWindow(int param)
{
  cSPUISettings13* p = new ((const char*)0x13f6b3c, 0, 0, 0, 0) cSPUISettings13();
  if (p) p->AddRef();
  if (p->Init(param)) {
    if (p->Apply()) {
      if (p) p->Release();
      return true;
    }
    p->Shutdown();
  }
  if (p) p->Release();
  return false;
}

// ---- stubs -----------------------------------------------------------------------------
void FUN_00602940() {}
void FUN_006031c0() {}
void FUN_00603260() {}
void FUN_00603650() {}
void FUN_00603780() {}
