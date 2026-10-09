#include "types.h"
#include <intrin.h>

// Slice s00671840 - SP::cSPUISearchBox / cSPUISporeGuidePage / XHTML detokenizer helpers.

struct VObj { void** vt; };
typedef void (__thiscall *FnV1)(void*);
typedef void (__thiscall *FnV1i)(void*, int);
typedef void (__thiscall *FnV2ii)(void*, int, int);
typedef void (__thiscall *FnV2ip)(void*, int, void*);
typedef void (__thiscall *FnV2pi)(void*, void*, int);
typedef void* (__thiscall *FnV0)(void*);
typedef void* (__thiscall *FnV0i)(void*, int);
typedef void* (__thiscall *FnV1p)(void*, void*);
typedef unsigned (__thiscall *FnVu0)(void*);
typedef int (__thiscall *FnVi0)(void*);
typedef bool (__thiscall *FnVb0)(void*);
typedef bool (__thiscall *FnVb2i)(void*, int, int);

struct RefCounted { void** vt; int mRefCount; };
void AddRefObj(void* p) { if (p) ((FnV1)((VObj*)p)->vt[0])(p); }
void ReleaseObj(void* p) { if (p) ((FnV1)((VObj*)p)->vt[1])(p); }
void ReleaseObj2(void* p) { if (p) ((FnV1)((VObj*)p)->vt[2])(p); }
struct BigInt { int lo; int hi; };
void QueryPerformanceCounter(BigInt* out);

// ---- external callees -------------------------------------------------
void FUN_0092ddc0(void* a, void* out);
struct cSPUILayout {
  void Shutdown(int a);
  bool Init(void* arr, int a, unsigned key);
  void SetParentWin(void* w, int a, unsigned key);
  void SetReloadCallback(void* cb, void* self);
  void* FindWindowByID(unsigned id, int rec);
  void Dtor();
};
void* WindowManager();
void* AssetBrowser(); // 0x00401030
struct Stopwatch { void Init(int a, int b); long long GetElapsedTime(); void Restart(); };
int GetTutorialToolPrice(void* a, unsigned key, int def); // 0x004e1c30
void* MessageServer(); // 0x0067dcc0
void RemoveHandler(void* server, void* handler, void* ids, int count, int prio);
unsigned short* Window_GetText(void* w);
struct EString {
  void Assign(unsigned short* s);
  void Assign(unsigned short* a, unsigned short* b);
  void Detok8f40();
  long long Find(unsigned short* sub, int pos);
  EString* AssignFrom(EString* other);
};
struct EStrLayout { void* begin; void* end; void* cap; };
void FUN_006b8f40(void* s);
void QualifyNameWithGroup(void* s);
void FUN_00996280(int a, int b, int c, int d);
bool FUN_009979f0(void* a, unsigned key);
struct FrameSet { void Ctor(int a); void Dtor(); void* GetFrame(void* key); void Clear(); void Release(); };
void CenterWindowInRect(void* obj);
void* operator_new(size_t n, const char* name, int a, int b, int c, int d); // 0x00f473a0
void operator_delete_(void* p);
void SetScrollbarDrawable(void* frame, int a, void* drawable);
void FUN_00992dc0(int a, int b);
void* interface_cast(void* p); // 0x0081d780
void FUN_00997140(void* a);
struct DetokBase { void BaseDtor(); };
struct VecHolder { void Dtor(); };
void* Alloc_Dealloc(void* p);
void CStringDetokenizer_ProcessString(void* self, unsigned short* a, unsigned short* b);
void* FUN_00672400();
void FUN_006720e0(void* self);
void Layout_FindWindowByID2();
unsigned g_scrollbarKey;
unsigned short* DAT_01667bac;
unsigned g_1528cf0;
void* g_1528cfc;
void* g_1529058;

// ---- 0x00671840 : ShowMissingExpansionPacks (partial skeleton) --------
struct MissingPage {
  char pad[0x400];
  bool ShowMissingExpansionPacks(void* a, int b);
};
// @ 0x00671840
bool MissingPage::ShowMissingExpansionPacks(void* a, int b) {
  (void)a; (void)b;
  return false;
}

// ---- 0x00671b80 -------------------------------------------------------
// @ 0x00671b80
void FUN_00671b80(void* a) {
  char tmp[4];
  FUN_0092ddc0(a, tmp);
}

// ---- cSPUISearchBox ---------------------------------------------------
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

// @ 0x00671c00
void cSPUISearchBox::Shutdown() {
  void* p = mLayout;
  if (p) {
    ((cSPUILayout*)p)->Shutdown(1);
    p = mLayout;
    if (p) { mLayout = 0; ((FnV1)((VObj*)p)->vt[2])(p); }
  }
  if (mpServer) {
    void* s = mpServer;
    mpServer = 0;
    RemoveHandler(s, mpHandler, mpIdArray, mnIdCount, mnPriority);
  }
}

// @ 0x00671c50
void cSPUISearchBox::OnSearchChanged() {
  if (WindowManager()) {
    void* wm = WindowManager();
    ((FnV2ip)((VObj*)wm)->vt[0x4c / 4])(wm, 0, mWinSearchBox);
  }
}

// @ 0x00671ca0
void cSPUISearchBox::ReloadCallback(void* layout, char reload) {
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
  void* w = ((cSPUILayout*)mLayout)->FindWindowByID( 0x149371c4, 1);
  if (w != mWinRoot) {
    if (w) AddRefObj(w);
    void* old = mWinRoot;
    mWinRoot = w;
    ReleaseObj(old);
  }
  w = ((cSPUILayout*)mLayout)->FindWindowByID( 0xd4935a8f, 1);
  if (w != mWinSearchBox) {
    if (w) AddRefObj(w);
    void* old = mWinSearchBox;
    mWinSearchBox = w;
    ReleaseObj(old);
  }
  w = ((cSPUILayout*)mLayout)->FindWindowByID( 0xb4935a77, 1);
  if (w) ((FnV2ii)((VObj*)w)->vt[0x7c / 4])(w, 1, 0);
  if (mWinRoot) {
    ((FnV1)((VObj*)mWinRoot)->vt[0x104 / 4])(mWinRoot);
    void* p = mWinRoot;
    ((FnV1)((VObj*)p)->vt[0x104 / 4])(p);
  }
}

// @ 0x00671da0
void cSPUISearchBox::SetParentWindow(void* w) {
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
  ((cSPUILayout*)this->mLayout)->Init(arr, 1, 0x5b598fa);
  ((cSPUILayout*)this->mLayout)->SetParentWin(this->mWinParent, 1, 0x5b598fa);
  ((cSPUILayout*)this->mLayout)->SetReloadCallback((void*)0x671ca0, this);
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
cSPUISearchBox::cSPUISearchBox() {
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
cSPUISearchBox::~cSPUISearchBox() {
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
void cSPUISearchBox::Update_(int unused) {
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
void cSPUISearchBox::EmptySearch() {
  if (mWinSearchBox) {
    ((EString*)((char*)this + 0x58))->Assign((unsigned short*)0x13ec468, (unsigned short*)0x13ec468);
    ((FnV1p)((VObj*)mWinSearchBox)->vt[0x80 / 4])(mWinSearchBox, strBegin);
  }
}

// @ 0x00672120
bool cSPUISearchBox::DoMessage(int unused, int* msg) {
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
      void* w = ((cSPUILayout*)mLayout)->FindWindowByID( 0xb4935a77, 1);
      if (w) ((FnV2ii)((VObj*)w)->vt[0x7c / 4])(w, 1, got);
    }
    return true;
  }
  return false;
}

// @ 0x00672200
bool cSPUISearchBox::Execute(int* p) {
  unsigned short* local[3];
  if (strBegin == strEnd) return true;
  if (p) {
    local[0] = (unsigned short*)0x1667bac;
    local[1] = (unsigned short*)0x1667bac;
    local[2] = (unsigned short*)0x1667bae;
    unsigned short* s = (unsigned short*)((FnV0)((VObj*)p)->vt[3])(p);
    if (s) {
      ((EString*)local)->Assign(s);
      FUN_006b8f40(local);
      if (((EString*)((char*)this + 0x58))->Find((unsigned short*)local, 0) != -1) {
        if ((((unsigned)((char*)local[2] - (char*)local[0]) & 0xfffffffe) > 2) && local[0])
          operator_delete_(local[0]);
        return true;
      }
    }
    s = (unsigned short*)((FnV0)((VObj*)p)->vt[4])(p);
    if (s) {
      ((EString*)local)->Assign(s);
      FUN_006b8f40(local);
      if (((EString*)((char*)this + 0x58))->Find((unsigned short*)local, 0) != -1) goto done_true;
    }
    s = (unsigned short*)((FnV0)((VObj*)p)->vt[5])(p);
    if (s) {
      ((EString*)local)->Assign(s);
      FUN_006b8f40(local);
      if (((EString*)((char*)this + 0x58))->Find((unsigned short*)local, 0) != -1) goto done_true;
    }
    if (local[0] != local[1]) { *local[0] = 0; local[1] = local[0]; }
    ((FnV1p)((VObj*)p)->vt[8])(p, local);
    if (local[0] != local[1]) {
      FUN_006b8f40(local);
      if (((EString*)((char*)this + 0x58))->Find((unsigned short*)local, 0) != -1) goto done_true;
    }
    s = (unsigned short*)((FnV0)((VObj*)p)->vt[0xc])(p);
    if (s) {
      ((EString*)local)->Assign(s);
      FUN_006b8f40(local);
      if (((EString*)((char*)this + 0x58))->Find((unsigned short*)local, 0) != -1) goto done_true;
    }
    if ((((unsigned)((char*)local[2] - (char*)local[0]) & 0xfffffffe) > 2) && local[0])
      operator_delete_(local[0]);
  }
  return false;
done_true:
  QualifyNameWithGroup(local);
  return true;
}

// ---- 0x00672400 / 0x00672440 : cXHTMLFrameSet holder -----------------
struct HFrameSet {
  void* vt;             // +0
  int m4;               // +4
  char fs[0x64];        // +8 .. +0x6c
  void* m6c;            // +0x6c
  HFrameSet();
  HFrameSet* Destroy(unsigned char flags);
};
// @ 0x00672400
HFrameSet::HFrameSet() {
  m4 = 0;
  vt = (void*)0x1400f30;
  ((FrameSet*)&fs)->Ctor(0);
  m6c = 0;
  _ReadWriteBarrier();
  ((FnV1)((VObj*)&fs)->vt[0])(&fs);
}
// @ 0x00672440
HFrameSet* HFrameSet::Destroy(unsigned char flags) {
  vt = (void*)0x1400f30;
  _ReadWriteBarrier();
  if (m6c) ((FnV1)((VObj*)m6c)->vt[1])(m6c);
  ((FrameSet*)&fs)->Dtor();
  vt = (void*)0x13ec458;
  if (flags & 1) operator_delete_(this);
  return this;
}

// ---- 0x00672480 : cSPUISporeGuidePage::Init --------------------------
struct GuidePage {
  char pad[8];
  void* mFrameSet;      // +8
  char padC[0x60];
  void* mFrame;         // +0x6c
  bool Init(void* a);
  bool OnRelease();
};
// @ 0x00672480
bool GuidePage::Init(void* a) {
  if (!a) return false;
  FUN_00996280(0x1002, 0x1006, 0x1003, 0x1024);
  if (!FUN_009979f0(a, 0x58c80f8)) return false;
  void* fr = ((FrameSet*)((char*)this + 8))->GetFrame(g_1528cfc);
  void* old = mFrame;
  if (fr != old) {
    if (fr) AddRefObj(fr);
    mFrame = fr;
    ReleaseObj(old);
  }
  char layout[0x18];
  CenterWindowInRect(layout);
  if (!mFrame) { ((cSPUILayout*)layout)->Dtor(); return false; }
  if (!((cSPUILayout*)layout)->Init((void*)0x1529058, 0, 0x5b598fa)) {
    ((cSPUILayout*)layout)->Dtor();
    return false;
  }
  void* w = ((cSPUILayout*)layout)->FindWindowByID( 0x4ab5e70, 1);
  if (w) {
    void* p2 = (void*)((FnV0i)((VObj*)w)->vt[3])(w, 0x2ef0c885);
    if (p2) {
      void* d = (void*)((FnV0)((VObj*)p2)->vt[0x60 / 4])(p2);
      void* dr = interface_cast(d);
      if (dr) {
        SetScrollbarDrawable(mFrame, 1, dr);
        FUN_00992dc0(1, 0);
      }
    }
  }
  ((cSPUILayout*)layout)->Dtor();
  return true;
}

// @ 0x006725a0
bool GuidePage::OnRelease() {
  ((FrameSet*)((char*)this + 8))->Clear();
  if (mFrame) {
    void* p = mFrame; mFrame = 0; ReleaseObj(p);
  }
  return true;
}

// @ 0x00672880
EString* EString::AssignFrom(EString* other) {
  if (this != other) {
    unsigned short** a = (unsigned short**)this;
    if (a[0] != (unsigned short*)a[1]) { *a[0] = 0; a[1] = a[0]; }
    unsigned short** b = (unsigned short**)other;
    Assign(b[0], b[1]);
  }
  return this;
}

// @ 0x00672910
void* FUN_00672910(void* first, void* last, void* dst) {
  if (first == last) return dst;
  do {
    if (dst != first) {
      unsigned short** d = (unsigned short**)dst;
      if (d[0] != (unsigned short*)d[1]) { *d[0] = 0; d[1] = d[0]; }
      unsigned short** f = (unsigned short**)first;
      ((EString*)dst)->Assign(f[0], f[1]);
    }
    first = (char*)first + 0x54;
    dst = (char*)dst + 0x54;
  } while (first != last);
  return dst;
}

// @ 0x00672960
struct CDetok {
  void* vt;
  char pad4[0x18];
  char strs[0x40];
  void* m5c;
  void Destroy();
};
void CDetok::Destroy() {
  *(void**)this = (void*)0x1400f40;
  char* p = (char*)this + 0x5c;
  for (int i = 3; i >= 0; --i) {
    char* beg = *(char**)(p - 0x10);
    char* cap = *(char**)(p - 8);
    p -= 0x10;
    if ((int)((cap - beg) & 0xfffffffe) > 2 && beg)
      operator_delete_(beg);
  }
  ((VecHolder*)((char*)this + 8))->Dtor();
  ((DetokBase*)this)->BaseDtor();
}

// ---- detokenizer helpers (partial) -----------------------------------
struct Detokenizer {
  bool detokenize();
  void token_action_copy(void* a, unsigned short* b);
};
// @ 0x006729d0
bool Detokenizer::detokenize() {
  return false;
}
// @ 0x00672b50
void Detokenizer::token_action_copy(void* a, unsigned short* b) {
  (void)a;
  unsigned short* local[3];
  local[0] = (unsigned short*)0x1667bac;
  local[1] = (unsigned short*)0x1667bac;
  local[2] = (unsigned short*)0x1667bae;
  CStringDetokenizer_ProcessString(this, b, local[0]);
  unsigned short* e = local[0];
  while (*e) ++e;
  ((EString*)*(void**)((char*)this + 0x94))->Assign((unsigned short*)local[0], e);
  if ((((unsigned)((char*)local[2] - (char*)local[0]) & 0xfffffffe) > 2) && local[0])
    operator_delete_(local[0]);
}
// --- equivalence checker address annotations
    void AssetBrowser(...); // 0x00401030
    void GetTutorialToolPrice(...); // 0x004e1c30
    void MessageServer(...); // 0x0067dcc0
    void interface_cast(...); // 0x0081d780
    void operator_delete_(...); // 0x00f47380
    void operator_new(...); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct FrameSet {
    void GetFrame(void*); // 0x00996d40
};
struct cSPUILayout {
    void Init(void*, int, unsigned int); // 0x008120d0
};
struct Stopwatch {
    void Restart(); // 0x00571e80
};
}
