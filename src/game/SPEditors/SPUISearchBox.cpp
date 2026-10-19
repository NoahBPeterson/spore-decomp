// src/game/SPEditors/SPUISearchBox.cpp -- migrated from slice(s) s00671840 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUISearchBox.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUISearchBox.h"
#include "SP/cTribeTool.h"
#include "cSPUILayout.h"
#include <intrin.h>

// ---- items of slice s00671840 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj { void** vt; };
typedef void (__thiscall *FnV1)(void*);
typedef void (__thiscall *FnV2ii)(void*, int, int);
typedef void (__thiscall *FnV2ip)(void*, int, void*);
typedef void* (__thiscall *FnV0)(void*);
typedef void* (__thiscall *FnV1p)(void*, void*);
void AddRefObj(void* p) { if (p) ((FnV1)((VObj*)p)->vt[0])(p); }
void ReleaseObj(void* p) { if (p) ((FnV1)((VObj*)p)->vt[1])(p); }
struct BigInt { int lo; int hi; };
void QueryPerformanceCounter(BigInt* out);
struct cSPUILayout_s0067_1840 {
  void Shutdown(int a);  // 0x00811ad0 (cSPUILayout::Shutdown)
  bool Init(void* arr, int a, unsigned key);  // 0x008120d0 (cSPUILayout::Init)
  void SetParentWin(void* w, int a, unsigned key);  // 0x008121b0 (cSPUILayout::SetParentWin)
  void SetReloadCallback(void* cb, void* self);  // 0x00810090 (cSPUILayout::SetReloadCallback)
  void* FindWindowByID(unsigned id, int rec);  // 0x008105b0 (cSPUILayout::FindWindowByID)
  void Dtor();   // 0x00811fe0 (equiv t3)
};
void* WindowManager();
void* AssetBrowser(); // 0x00401030
struct Stopwatch { void Init(int a, int b); long long GetElapsedTime(); void Restart(); };
int GetTutorialToolPrice(void* a, unsigned key, int def); // 0x004e1c30
void* MessageServer(); // 0x0067dcc0
void RemoveHandler(void* server, void* handler, void* ids, int count, int prio);
struct EString {
  void Assign(unsigned short* s);   // 0x005c3d90 (equiv t3)
  void Assign(unsigned short* a, unsigned short* b);
  void Detok8f40();
  long long Find(unsigned short* sub, int pos);
  EString* AssignFrom(EString* other);
};
void FUN_006b8f40(void* s);
void CenterWindowInRect(void* obj);   // 0x00810000 (equiv t2)
void* operator_new(size_t n, const char* name, int a, int b, int c, int d); // 0x00f473a0
void operator_delete_(void* p);
unsigned g_1528cf0;
struct cSPUISearchBox {
  void* vt0;            // +0x00
  void* vt1;            // +0x04
  void* vt2;            // +0x08
  int   mRefCount;      // +0x0c
  bool  mIsVisible;     // +0x10
  char  pad11[7];       // 0x11..0x18
  char  sw[0x18];       // +0x18 stopwatch subobject
  bool  mSearchMessageSent; // +0x30
  char  pad31[3];
  void* mLayout;        // +0x34
  void* mWinParent;     // +0x38
  void* mWinRoot;       // +0x3c
  void* mWinSearchBox;  // +0x40
  void* mpServer;       // +0x44
  void* mpHandler;      // +0x48
  void* mpIdArray;      // +0x4c
  int   mnIdCount;      // +0x50
  int   mnPriority;     // +0x54
  unsigned short* strBegin; // +0x58
  unsigned short* strEnd;   // +0x5c
  unsigned short* strCap;   // +0x60

  void Shutdown();
  void OnSearchChanged();
  void EmptySearch();
  void SetParentWindow(void* w);
  void ReloadCallback(void* layout, char reload);
  void Update_(int unused);
  bool DoMessage(int unused, int* msg);
  bool Execute(int* p);
  cSPUISearchBox();
  ~cSPUISearchBox();
};
namespace __equiv_ann1 {
struct Stopwatch {
    void GetElapsedTime();   // 0x0093a5e0 (equiv t2)
};
}
// ---- items of slice s00671840 end

// @ 0x00671c00
void SP::cSPUISearchBox::Shutdown()
{
  void* p = mLayout.mpObject;
  if (p) {
    ((cSPUILayout*)p)->Shutdown(1);
    p = mLayout.mpObject;
    if (p) { mLayout.mpObject = 0; ((FnV1)((VObj*)p)->vt[2])(p); }
  }
  if (mAutoMsgHandler.mpServer) {
    void* s = mAutoMsgHandler.mpServer;
    mAutoMsgHandler.mpServer = 0;
    RemoveHandler(s, mAutoMsgHandler.mpHandler, mAutoMsgHandler.mpIdArray, mAutoMsgHandler.mnIdArrayCount, mAutoMsgHandler.mnPriority);
  }
}

// @ 0x00671c50
void cSPUISearchBox::OnSearchChanged()
{
  if (WindowManager()) {
    void* wm = WindowManager();
    ((FnV2ip)((VObj*)wm)->vt[0x4c / 4])(wm, 0, mWinSearchBox);
  }
}

// @ 0x00671ca0
void cSPUISearchBox::ReloadCallback(void* layout, char reload)
{
  if (!reload) {
    if (mWinRoot) {
      ((FnV1)((VObj*)mWinRoot)->vt[0x108 / 4])(mWinRoot);
    }
    if (mWinRoot) {
      void* p = mWinRoot; mWinRoot = 0; ReleaseObj(p);
    }
    if (mWinSearchBox) {
      void* p = mWinSearchBox; mWinSearchBox = 0; ReleaseObj(p);
    }
    return;
  }
  void* w = ((cSPUILayout_s0067_1840*)mLayout)->FindWindowByID( 0x149371c4, 1);
  if (w != mWinRoot) {
    if (w) AddRefObj(w);
    void* old = mWinRoot;
    mWinRoot = w;
    ReleaseObj(old);
  }
  w = ((cSPUILayout_s0067_1840*)mLayout)->FindWindowByID( 0xd4935a8f, 1);
  if (w != mWinSearchBox) {
    if (w) AddRefObj(w);
    void* old = mWinSearchBox;
    mWinSearchBox = w;
    ReleaseObj(old);
  }
  w = ((cSPUILayout_s0067_1840*)mLayout)->FindWindowByID( 0xb4935a77, 1);
  if (w) ((FnV2ii)((VObj*)w)->vt[0x7c / 4])(w, 1, 0);
  if (mWinRoot) {
    ((FnV1)((VObj*)mWinRoot)->vt[0x104 / 4])(mWinRoot);
    void* p = mWinRoot;
    ((FnV1)((VObj*)p)->vt[0x104 / 4])(p);
  }
}

// @ 0x00671da0
void cSPUISearchBox::SetParentWindow(void* w)
{
  void* old = this->mWinParent;
  if (w != old) {
    if (w) AddRefObj(w);
    this->mWinParent = w;
    ReleaseObj(old);
  }
  void* obj = operator_new(0x18, "Sporepedia", 0, 0, 0, 0);
  if (obj) CenterWindowInRect(obj);
  void* oldL = this->mLayout;
  if (obj != oldL) {
    if (obj) ((FnV1)((VObj*)obj)->vt[1])(obj);
    this->mLayout = obj;
    if (oldL) ((FnV1)((VObj*)oldL)->vt[2])(oldL);
  }
  int arr[3];
  arr[0] = (int)0xdecdb609; arr[1] = (int)0x510a95b; arr[2] = (int)g_1528cf0;
  ((cSPUILayout_s0067_1840*)this->mLayout)->Init(arr, 1, 0x5b598fa);
  ((cSPUILayout_s0067_1840*)this->mLayout)->SetParentWin(this->mWinParent, 1, 0x5b598fa);
  ((cSPUILayout_s0067_1840*)this->mLayout)->SetReloadCallback((void*)0x671ca0, this);
  this->ReloadCallback(this->mLayout, 1);
  if (*(int*)((char*)this + 0x28) == 1) {
    unsigned long long t = __rdtsc();
    *(int*)((char*)this + 0x24) = 0;
    *(int*)((char*)this + 0x20) = 0;
    *(unsigned long long*)((char*)this + 0x18) = t;
  } else {
    BigInt local;
    QueryPerformanceCounter(&local);
    *(int*)((char*)this + 0x24) = 0;
    *(int*)((char*)this + 0x20) = 0;
    *(long long*)((char*)this + 0x18) = *(long long*)&local;
  }
}

// @ 0x00671ec0
cSPUISearchBox::cSPUISearchBox()
{
  *(void**)((char*)this + 4) = (void*)0x13eb384;
  *(void**)((char*)this + 8) = (void*)0x13ec458;
  mRefCount = 0;
  _ReadWriteBarrier();
  *(void**)this = (void*)0x1400ea4;
  *(void**)((char*)this + 4) = (void*)0x1400e94;
  *(void**)((char*)this + 8) = (void*)0x1400e84;
  mIsVisible = false;
  ((Stopwatch*)((char*)this + 0x18))->Init(4, 0);
  mSearchMessageSent = true;
  mLayout = 0;
  mWinParent = 0;
  mWinRoot = 0;
  mWinSearchBox = 0;
  mpServer = 0;
  mpHandler = 0;
  mpIdArray = 0;
  mnIdCount = 0;
  mnPriority = 0;
  strBegin = (unsigned short*)0x1667bac;
  strEnd = (unsigned short*)0x1667bac;
  strCap = (unsigned short*)0x1667bae;
}

// @ 0x00671f70
cSPUISearchBox::~cSPUISearchBox()
{
  *(void**)this = (void*)0x1400ea4;
  *(void**)((char*)this + 4) = (void*)0x1400e94;
  *(void**)((char*)this + 8) = (void*)0x1400e84;
  _ReadWriteBarrier();
  unsigned short* p = strBegin;
  if ((int)(((char*)strCap - (char*)p) & 0xfffffffe) > 2 && p) {
    operator_delete_(p);
  }
  if (mpServer) {
    void* s = mpServer; mpServer = 0;
    RemoveHandler(s, mpHandler, mpIdArray, mnIdCount, mnPriority);
  }
  ReleaseObj(mWinSearchBox);
  ReleaseObj(mWinRoot);
  ReleaseObj(mWinParent);
  if (mLayout) ((FnV1)((VObj*)mLayout)->vt[8 / 4])(mLayout);
  *(void**)((char*)this + 8) = (void*)0x13ec458;
  *(void**)((char*)this + 4) = (void*)0x13eb394;
  *(void**)this = (void*)0x13eb938;
}

// @ 0x00672040
void cSPUISearchBox::Update_(int unused)
{
  (void)unused;
  int threshold = 0x12c;
  if (AssetBrowser() && ((VObj*)AssetBrowser())->vt) {
    int* ab = (int*)AssetBrowser();
    if (ab[6]) threshold = GetTutorialToolPrice((void*)ab[6], 0x6062a61a, 0x12c);
  }
  long long elapsed = ((Stopwatch*)((char*)this + 0x18))->GetElapsedTime();
  if ((long long)threshold < elapsed && !mSearchMessageSent) {
    if (mWinSearchBox) {
      unsigned short* s = (unsigned short*)((FnV0)((VObj*)mWinSearchBox)->vt[0x3c / 4])(mWinSearchBox);
      ((EString*)((char*)this + 0x58))->Assign(s);
      FUN_006b8f40((char*)this + 0x58);
    }
    void* ms = MessageServer();
    ((FnV2ii)((VObj*)ms)->vt[0x14 / 4])(ms, (int)0xd4937185, 0);
    mSearchMessageSent = true;
  }
}

// @ 0x006720e0
void cSPUISearchBox::EmptySearch()
{
  if (mWinSearchBox) {
    ((EString*)((char*)this + 0x58))->Assign((unsigned short*)0x13ec468, (unsigned short*)0x13ec468);
    ((FnV1p)((VObj*)mWinSearchBox)->vt[0x80 / 4])(mWinSearchBox, strBegin);
  }
}

// @ 0x00672120
bool cSPUISearchBox::DoMessage(int unused, int* msg)
{
  (void)unused;
  if (!mLayout || !mWinSearchBox) return false;
  if (msg[2] == 0x287259f6) {
    if (msg[3] == (int)0xb4935a77) {
      this->EmptySearch();
      void* ms = MessageServer();
      ((FnV2ii)((VObj*)ms)->vt[0x14 / 4])(ms, (int)0xd4937186, 0);
    }
    return true;
  }
  if (msg[2] == 0x18) {
    if (msg[3] == (int)0xd4935a8f) {
      ((Stopwatch*)((char*)this + 0x18))->Restart();
      mSearchMessageSent = false;
      unsigned short* s = (unsigned short*)((FnV0)((VObj*)mWinSearchBox)->vt[0x3c / 4])(mWinSearchBox);
      char got = 0;
      if (s) {
        while (*s) ++s;
        if (s != (unsigned short*)((FnV0)((VObj*)mWinSearchBox)->vt[0x3c / 4])(mWinSearchBox)) got = 1;
      }
      void* w = ((cSPUILayout_s0067_1840*)mLayout)->FindWindowByID( 0xb4935a77, 1);
      if (w) ((FnV2ii)((VObj*)w)->vt[0x7c / 4])(w, 1, got);
    }
    return true;
  }
  return false;
}
