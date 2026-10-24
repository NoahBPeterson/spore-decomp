// Decompiled slice s00e24700 -- UI Posse / posse-item windows.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include <intrin.h>
#include "types.h"

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);

// ---------------------------------------------------------------------------
// shared shapes
// ---------------------------------------------------------------------------
struct cSPUIWindow;

// A behaviour message (0x40 bytes; vtable pair 0x013eb90c base / 0x013eb844 final).
extern void* vtbl_BehaviorMessageBase[];                   // 0x013eb90c
extern void* vtbl_BehaviorMessage[];                       // 0x013eb844

struct Msg40 {
  void*    vptr;                                            // +0x00
  long     refcount;                                        // +0x04
  uint32_t mData[10];                                       // +0x08 .. +0x2f
  uint32_t mId;                                             // +0x30
  uint32_t mPad34;                                          // +0x34
  uint32_t mRCFlags;                                        // +0x38
  uint32_t mPad3c;                                          // +0x3c
  Msg40(uint32_t id) : mId(id) {
    vptr = vtbl_BehaviorMessageBase;
    _InterlockedExchange(&refcount, 0);
    vptr = vtbl_BehaviorMessage;
    mRCFlags = 0;
  }
  void AddRef()  { ((void(__thiscall*)(Msg40*))((void**)vptr)[1])(this); }
  void Release() { ((void(__thiscall*)(Msg40*))((void**)vptr)[2])(this); }
  void SetIRefCount(int idx, uint32_t p);                   // 0x005726e0 (ret 8)
};

// The message server, virtual MessageSend at vtable +0x18.
struct MsgServer {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual void v3(); virtual void v4(); virtual void v5();
  virtual void MessageSend(uint32_t id, void* msg, int a, int b);   // +0x18
};
MsgServer* MessageServer();                                 // 0x0067dcc0

// A generic object with a vtable at +0x00 (used for posse items).
struct Vtbl { void (*slot[128])(); };
typedef void (__thiscall* FnVoidI)(void*, int);
typedef int  (__thiscall* FnInt0)(void*);

struct MsgIn { uint8_t mPad00[8]; int mField08; int mField0c; };

struct cSPUIPosseItem {
  Vtbl*   mpVtable;                                         // +0x00
  uint8_t mPad004[0x4c];
  void*   mField50;                                         // +0x50
  uint8_t mPad054[0x40];
  int     mField94;                                         // +0x94
  void FUN_00950ef0(int, MsgIn*);                           // 0x00950ef0

  void FUN_00e24700(int state);
  void FUN_00e247f0(int param_2, MsgIn* param_3);
};

// Embedded SP UI layout (only its address is used here).
struct cSPUILayout {
  uint8_t mData[0x200];
  void* FindWindowByID(uint32_t id, uint32_t flags);       // 0x008105b0
  void  Shutdown(uint32_t mode);                            // 0x00811ad0
};

// An entry of the posse item vector (8 bytes each).
struct ItemNode {
  void* mField00;       // +0x00
  void* mField04;       // +0x04
};

void FUN_00e24d10(uint32_t id, void* ctx);                 // 0x00e24d10 (cdecl)
float GetElapsedSeconds();                                 // 0x00805080 (SPUIHelpers, cdecl)
extern float g_clickThreshold;                             // 0x01480568 (0.25f)
extern void* g_pMsgRef;                                    // 0x016ac278 (pending message)

// Objects whose behaviour is dispatched through a raw vtable.
typedef void     (__thiscall* FnVoid0)(void*);
typedef void     (__thiscall* FnVoidI)(void*, int);
typedef void     (__thiscall* FnVoidII)(void*, int, int);
typedef int      (__thiscall* FnInt0)(void*);
typedef uint32_t (__thiscall* FnU32_0)(void*);

struct WindowMgr { Vtbl* mpVtable;  /* +0x00 */ };
WindowMgr* WindowManager();                                // 0x0067caa0

struct cSPUIPosse {
  Vtbl*    mpVtable;                                        // +0x00
  uint8_t  mPad004[0x4c];                                   // +0x04 .. +0x4f
  void*    mField50;                                        // +0x50
  uint8_t  mPad054[0x40];                                   // +0x54 .. +0x93
  int      mField94;                                        // +0x94
  uint8_t  mPad098[0x09];                                   // +0x98 .. +0xa0
  uint8_t  mFieldA1;                                        // +0xa1
  uint8_t  mFieldA2;                                        // +0xa2
  uint8_t  mFieldA3;                                        // +0xa3
  ItemNode* mFieldA4;                                       // +0xa4
  ItemNode* mFieldA8;                                       // +0xa8
  uint8_t  mPad0ac[0x90];                                   // +0xac .. +0x13b
  int      mField13c;                                       // +0x13c
  uint8_t  mField140;                                       // +0x140
  uint8_t  mPad141[0x03];                                   // +0x141 .. +0x143
  int      mField144;                                       // +0x144
  float    mField148;                                       // +0x148
  uint8_t  mPad14c[0x70];                                   // +0x14c .. +0x1bb
  cSPUILayout mLayout;                                      // +0x1bc

  char      FUN_00e248b0(int p2, float p3, float p4, int p5, int p6); // 0x00e248b0
  char      FUN_00e24b10();                                 // 0x00e24b10
  void      toggle_select_all();                            // 0x00e23d50
  ItemNode* find_item(int id);                              // 0x00e24ba0

  void* FUN_00e24c90(int id);
  char  FUN_00e24cc0(void* p2, void* p3, void* p4, void* p5, void* p6);
  char  FUN_00e24eb0(int p2, float p3, float p4, int p5, int p6);
  char  FUN_00e250a0(int p2, float p3, float p4, int p5, int p6);
  char  FUN_00e25120(int p2, float p3, float p4, int p5, int p6);
};

// ---------------------------------------------------------------------------
// @ 0x00e248b0
// Mouse-down handler shared by the posse windows. Records the click/debounce
// stamp, dispatches to the owning context, and updates the per-item state.
char cSPUIPosse::FUN_00e248b0(int param_2, float param_3, float param_4, int param_5,
                              int param_6)
{
  uint32_t recent = (param_5 == mField144) && ((GetElapsedSeconds() - mField148) < g_clickThreshold);
  mField140 = (uint8_t)recent;
  mField148 = GetElapsedSeconds();
  mField144 = param_5;
  if (param_5 == 1000) {
    if (mField13c == param_2) {
      WindowMgr* wm = WindowManager();
      ((FnVoidII)wm->mpVtable->slot[0x58 / 4])(wm, 1, param_2);
    }
    int held = (param_6 & 3) != 0;
    mFieldA2 = 1;
    mFieldA3 = (uint8_t)held;
    if (!held)
      ((FnVoid0)mpVtable->slot[0xe0 / 4])(this);
    switch (mField94) {
    case 1:
    case 3:
      mFieldA1 = 1;
      ((FnVoidI)mpVtable->slot[0xb8 / 4])(this, 2);
      break;
    case 2:
      mFieldA1 = 1;
      if (mFieldA3)
        ((FnVoidI)mpVtable->slot[0xb8 / 4])(this, 1);
      break;
    case 4:
      mFieldA1 = 1;
      if (mFieldA3)
        ((FnVoidI)mpVtable->slot[0xb8 / 4])(this, 1);
      else
        ((FnVoidI)mpVtable->slot[0xb8 / 4])(this, 2);
      break;
    }
    uint32_t r = ((FnU32_0)mpVtable->slot[0xbc / 4])(this);
    mFieldA4 = (ItemNode*)r;
    return 0;
  }
  if (param_5 == 0x3ea) {
    Msg40* msg = new ("UI", 0, 0, 0, 0) Msg40(0x3deb12a);
    if (msg)
      msg->AddRef();
    uint32_t v = ((FnU32_0)mpVtable->slot[0xc4 / 4])(this);
    msg->SetIRefCount(0, v);
    MessageServer()->MessageSend(msg->mId, msg, 0, 0);
    msg->Release();
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00e24b10
// Tears the posse down: drops the pending message reference, releases every
// queued item (calling each item's own cleanup slot), then shuts the embedded
// layout down.
char cSPUIPosse::FUN_00e24b10()
{
  void* pending = g_pMsgRef;
  if (pending) {
    g_pMsgRef = 0;
    ((FnVoid0)(((void**)*(void**)pending)[1]))(pending);
  }
  if (mFieldA8 != mFieldA4) {
    do {
      void* item = mFieldA8[-1].mField04;
      ((FnVoid0)(((void**)*(void**)item)[0xcc / 4]))(item);
      mFieldA8 -= 1;
      ItemNode* e = mFieldA8;
      void* f4 = e->mField04;
      if (f4)
        ((FnVoid0)(((void**)*(void**)f4)[1]))(f4);
      void* f0 = e->mField00;
      if (f0)
        ((FnVoid0)(((void**)*(void**)f0)[1]))(f0);
    } while (mFieldA8 != mFieldA4);
  }
  mLayout.Shutdown(1);
  return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00e24c90
// Looks up the item with the given id; returns the looked-up node's payload,
// or null when the lookup landed on the end sentinel.
void* cSPUIPosse::FUN_00e24c90(int id)
{
  ItemNode* n = find_item(id);
  if (n != mFieldA8)
    return n->mField04;
  return 0;
}

// @ 0x00e24cc0
// Mouse-up handler: when the release happened on one of the two select-all
// buttons, toggles select-all. Always reports "not handled" (low byte cleared).
char cSPUIPosse::FUN_00e24cc0(void* p2, void* p3, void* p4, void* p5, void* p6)
{
  if (p2 == mLayout.FindWindowByID(0x3dae410, 1) ||
      p2 == mLayout.FindWindowByID(0x3dae411, 1))
    toggle_select_all();
  return 0;
}

// @ 0x00e24eb0
// Posse window event forwarder (variant A); notifies the owning context on a
// click at the (1000) column.
char cSPUIPosse::FUN_00e24eb0(int p2, float p3, float p4, int p5, int p6)
{
  char r = FUN_00e248b0(p2, p3, p4, p5, p6);
  if (mField140 != 0 && p5 == 1000)
    FUN_00e24d10(0x6204441, mField50);
  return r;
}

// @ 0x00e250a0
// Posse window event forwarder (variant B); same shape as FUN_00e24eb0 with a
// different notification id.
char cSPUIPosse::FUN_00e250a0(int p2, float p3, float p4, int p5, int p6)
{
  char r = FUN_00e248b0(p2, p3, p4, p5, p6);
  if (mField140 != 0 && p5 == 1000)
    FUN_00e24d10(0x346048a, mField50);
  return r;
}

// @ 0x00e25120
// Posse window event forwarder (variant C); no-ops as "handled" when the
// context pointer is absent.
char cSPUIPosse::FUN_00e25120(int p2, float p3, float p4, int p5, int p6)
{
  if (mField50 != 0)
    return FUN_00e248b0(p2, p3, p4, p5, p6);
  return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00e24700
// Sets the item state; when it changed and the item is live, posts a
// "state changed" message carrying the state-derived flag bits.
void cSPUIPosseItem::FUN_00e24700(int state)
{
  int old = mField94;
  ((FnVoidI)mpVtable->slot[0xd0 / 4])(this, state);
  if (old != state) {
    if (((FnInt0)mpVtable->slot[0xc4 / 4])(this) != 0) {
      Msg40* msg = new ("UI", 0, 0, 0, 0) Msg40(0x3deb129);
      if (msg)
        msg->AddRef();
      uint32_t v = (uint32_t)((FnInt0)mpVtable->slot[0xc4 / 4])(this);
      msg->SetIRefCount(0, v);
      uint32_t flags = 0;
      if (state == 2 || state == 4)
        flags = 1;
      if (state == 3 || state == 4)
        flags |= 2;
      msg->mData[2] = flags;
      MessageServer()->MessageSend(msg->mId, msg, 0, 0);
      msg->Release();
    }
  }
}

// @ 0x00e247f0
// Handles an incoming "do message"; when it matches the expected tag pair, it
// posts a notification and a follow-up message, then defers to the base.
void cSPUIPosseItem::FUN_00e247f0(int param_2, MsgIn* param_3)
{
  if (param_3->mField08 == 0x287259f6 && param_3->mField0c == 0x4acfcaf) {
    MessageServer()->MessageSend(0x4e54d0c, 0, 0, 0);
    Msg40* msg = new ("UI", 0, 0, 0, 0) Msg40(0x14051500);
    msg->mData[0] = (uint32_t)mField50;
    msg->SetIRefCount(4, (uint32_t)mField50);
    MessageServer()->MessageSend(0x14051500, msg, 0, 0);
  }
  FUN_00950ef0(param_2, param_3);
}

// @ 0x00e251c0
// Window handler that posts a fixed "dirty" message built on the heap.
char __stdcall FUN_00e251c0(void* p2, void* p3, void* p4, void* p5, void* p6)
{
  Msg40* msg = new ("UI", 0, 0, 0, 0) Msg40(0x337f07d8);
  if (msg)
    msg->AddRef();
  MessageServer()->MessageSend(msg->mId, msg, 0, 0);
  msg->Release();
  return 1;
}