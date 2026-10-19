// Slice s008268b0 -- SP::cPropertyUI view reset (scroll/position state back to defaults).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct WinA {  // object at +0x64 (vtable slots 25 and 57)
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual void v20();
  virtual void v21();
  virtual void v22();
  virtual void v23();
  virtual void v24();
  virtual void SetFloats(float a, float b);  // slot 25 (+0x64)
  virtual void v26();
  virtual void v27();
  virtual void v28();
  virtual void v29();
  virtual void v30();
  virtual void v31();
  virtual void v32();
  virtual void v33();
  virtual void v34();
  virtual void v35();
  virtual void v36();
  virtual void v37();
  virtual void v38();
  virtual void v39();
  virtual void v40();
  virtual void v41();
  virtual void v42();
  virtual void v43();
  virtual void v44();
  virtual void v45();
  virtual void v46();
  virtual void v47();
  virtual void v48();
  virtual void v49();
  virtual void v50();
  virtual void v51();
  virtual void v52();
  virtual void v53();
  virtual void v54();
  virtual void v55();
  virtual void v56();
  virtual void v57();                         // slot 57 (+0xe4)
};
struct WinB {  // object at +0x68 (vtable slot 9)
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void Set(int a, int b);  // slot 9 (+0x24)
};

struct cPropertyUI {
  void* vfptr;
  unsigned pad4[2];
  unsigned pad0c[2];
  float mCurrentX;        // +0x14
  float mCurrentY;        // +0x18
  float mCurrentWindowX;  // +0x1c
  float mCurrentWindowY;  // +0x20
  float mPreviousScrollVal;  // +0x24
  float mRefreshScrollVal;   // +0x28
  unsigned pad2c[(0x64 - 0x2c) / 4];
  WinA* mWinA;  // +0x64
  WinB* mWinB;  // +0x68
  void ClearAllPropertyControls();  // 0x00824c20
  void ResetView();
};

// @ 0x008268b0
void cPropertyUI::ResetView() {
  mCurrentX = 0.0f;
  mCurrentY = 10.0f;
  mCurrentWindowX = 8.0f;
  mCurrentWindowY = 60.0f;
  mWinA->SetFloats(8.0f, 60.0f);
  mRefreshScrollVal = mPreviousScrollVal;
  mPreviousScrollVal = 0.0f;
  mWinB->Set(0, 1);
  mWinA->v57();
  ClearAllPropertyControls();
}
