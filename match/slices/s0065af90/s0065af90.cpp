// Slice s0065af90: string helpers (byte-exact) plus the SP::cSPUIAssetWebBrowser UI
// methods and one sibling window.  Layouts follow the binary, not the 2008 PDB.
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, int c,
                                          int d);
extern "C" unsigned int __cdecl strlen(const char* p);

namespace eastl {

template <typename T>
inline const T& min_alt(const T& a, const T& b) {
  return b < a ? b : a;
}

extern "C" void* memcpy(void*, const void*, unsigned int);

// ===================== char string helpers (byte-exact) ====================

// @ 0x0065b180
__declspec(noinline) const char* CharTypeStringFindEnd(const char* pBegin, const char* pEnd, char c) {
  const char* pTemp = pEnd;
  while (--pTemp >= pBegin) {
    if (*pTemp == c)
      return pTemp;
  }
  return pEnd;
}

// @ 0x0065b530
__declspec(noinline) const char* CharTypeStringRSearch(const char* p1Begin, const char* p1End,
                                                       const char* p2Begin, const char* p2End) {
  if (p1Begin == p1End)
    return p1Begin;
  if (p2Begin == p2End)
    return p1Begin;
  if ((p2Begin + 1) == p2End)
    return CharTypeStringFindEnd(p1Begin, p1End, *p2Begin);
  if ((p2End - p2Begin) > (p1End - p1Begin))
    return p1End;

  const char* pSearchEnd = (p1End - (p2End - p2Begin) + 1);
  const char* pCurrent1;
  const char* pCurrent2;
  while (pSearchEnd != p1Begin) {
    pCurrent1 = CharTypeStringFindEnd(p1Begin, pSearchEnd, *p2Begin);
    if (pCurrent1 == pSearchEnd)
      return p1End;
    pCurrent2 = p2Begin;
    while (*pCurrent1++ == *pCurrent2++) {
      if (pCurrent2 == p2End)
        return (pCurrent1 - (p2End - p2Begin));
    }
    --pSearchEnd;
  }
  return p1End;
}

inline unsigned int CharStrlen(const char* p) { return strlen(p); }

struct allocator {};

class cstring {
 public:
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  allocator mAllocator;
  // @ 0x0065b8c0
  unsigned int rfind(const char* p, unsigned int position, unsigned int n) const;
  // @ 0x0065bcb0
  unsigned int rfind(const char* p, unsigned int position) const;
};

// @ 0x0065b8c0
unsigned int cstring::rfind(const char* p, unsigned int position, unsigned int n) const {
  const unsigned int nLength = (unsigned int)(mpEnd - mpBegin);
  if (n <= nLength) {
    if (n) {
      const char* pEnd = mpBegin + min_alt(nLength - n, position) + n;
      const char* pResult = CharTypeStringRSearch(mpBegin, pEnd, p, p + n);
      if (pResult != pEnd)
        return (unsigned int)(pResult - mpBegin);
    } else
      return min_alt(nLength, position);
  }
  return 0xffffffffu;
}

// @ 0x0065bcb0
unsigned int cstring::rfind(const char* p, unsigned int position) const {
  return rfind(p, position, CharStrlen(p));
}

// ===================== wide string (range ctor is a slice function) ========

class wstring {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator mAllocator;

  void AllocateSelf();
  void AllocateSelf(unsigned int n);
  __declspec(noinline) void RangeInitialize(const wchar_t* p);

  void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
    const unsigned int n = (unsigned int)(pEnd - pBegin);
    AllocateSelf(n + 1);
    memcpy(mpBegin, pBegin, n * sizeof(wchar_t));
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }

  wstring() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
  wstring(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  // @ 0x0065bce0
  __declspec(noinline) wstring(const wstring& x, unsigned int position, unsigned int n);
  ~wstring() { DeallocateSelf(); }

  wstring& operator=(const wstring& x) {
    if (this != &x)
      assign(x.mpBegin, x.mpEnd);
    return *this;
  }

  void assign(const wchar_t* pBegin, const wchar_t* pEnd);
  unsigned int find(const wchar_t* p, unsigned int position) const;
  unsigned int rfind(wchar_t c, unsigned int position) const;
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }

  void DeallocateSelf() {
    if ((mpCapacity - mpBegin) > 1)
      DoFree(mpBegin);
  }
  void DoFree(wchar_t* p) {
    if (p)
      EASTL_allocator_deallocate(p);
  }
};

inline unsigned int CharStrlen(const wchar_t* p) {
  const wchar_t* pCurrent = p;
  while (*pCurrent)
    ++pCurrent;
  return (unsigned int)(pCurrent - p);
}

// @ 0x0065bce0
wstring::wstring(const wstring& x, unsigned int position, unsigned int n)
    : mpBegin(0), mpEnd(0), mpCapacity(0) {
  RangeInitialize(x.mpBegin + position,
                  x.mpBegin + position + min_alt(n, (unsigned int)(x.mpEnd - x.mpBegin) - position));
}

__declspec(noinline) void wstring::RangeInitialize(const wchar_t* p) {
  RangeInitialize(p, p + CharStrlen(p));
}

}  // namespace eastl

// ===========================================================================
// callee stubs
// ===========================================================================
struct ResourceKey {
  uint32_t a, b, c;
};
extern ResourceKey g_key_1526560;
extern const wchar_t* g_user;      // 0x152658c
extern uint32_t g_152685c;
extern void* g_152657c;

struct cSPUILayout {
  void** vt;
  void Init(ResourceKey* key, int a, uint32_t b);
  void SetParentWin(void* parent, int a, uint32_t b);
  void SetReloadCallback(void* fn, void* self);
  void* FindWindowByID(uint32_t id, bool recursive);
  void Shutdown(int a);
};

struct cXHTMLFrameSet {
  virtual void f0();
  char pad[0x60];
  cXHTMLFrameSet(void* fn);
  ~cXHTMLFrameSet();
  void* GetFrame(uint32_t id);
  bool HandleLocationChange(void* win, const wchar_t* url, int a, int b);
  void FUN_00997140();
};

struct ILayoutObj {
  virtual void a0(); virtual void a1(); virtual void a2(); virtual void* a3();
  virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
  virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
  virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
  virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
  virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
  virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
  virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31();
  virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35();
  virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
  virtual void a40(); virtual void a41(); virtual void a42(); virtual int a43();  // 0xac?
  virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47();
  virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51();
  virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55();
  virtual void a56();  // 0xe0
  virtual void a57(); virtual void a58(); virtual void a59(); virtual void a60();
  virtual void a61(); virtual void a62(); virtual void a63();
  virtual void a64();  // 0x100
  virtual void a65(void*);  // 0x104
  virtual void a66(void*);  // 0x108
};

struct IMessageServer {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4();
  virtual void Post(uint32_t id, void* p, int n);  // 0x14
  virtual void v6(); virtual void v7(); virtual void v8();
  virtual void Sub(void* h, uint32_t id);          // 0x24
  virtual void v10();
  virtual void Unsub(void* h, uint32_t id, int y); // 0x2c
};

extern "C" IMessageServer* MessageServer();

// non-virtual callees (this in ecx)
struct FeedList {
  void FUN_005febf0();
  void FUN_005fec90();
  void FUN_005fed90(void* p);
  int  FUN_005fedb0(void* p);
  void FUN_005febb0(int a, int b);
  void FUN_005ff0d0();
};
struct Content36 {
  int FUN_005fed70();
};
void FUN_00996280(int a, int b, int c, int d);
void FUN_00997140();
int FUN_009979f0c(void* self, uint32_t id);
void AutoRef_assign_0xb5f950(void* self, void* obj);
void* FUN_0067cb30();
void* FUN_00ef4470(void* tbl);
void FUN_005467e0();
void FUN_00666af0(ResourceKey* k, uint32_t h);
uint32_t FNVHash(const char* s, uint32_t seed, int n);
int Resource_GetFileCount(void* self, int a);
void SPUIHelpers_SetWindowAreaToParent(void* w);
void SP_Pollen_GetURL(void* url, void* a, void* b);
void* WinXHTML_GetDocument(void* w);
void cPollinator_SubscribeToFeed(void* self, void* f);
void cPollinator_UnsubscribeToFeed(void* self, void* f);
extern "C" void* operator_new_ea(unsigned int size, const char* tag, int, int, int, int);
void FUN_00657420();
void* LayoutCtor18();  // 0x810000
void* FUN_005feff0();
void FUN_005feea0(void* a, void* b);

// ===========================================================================
// sibling UI window (FUN_0065af90)
// ===========================================================================
struct SiblingWin {
  void** vt;
  char pad[0x13];
  bool m17;
  char pad18[4];
  int m1c;             // +0x1c
  ILayoutObj* mpLayout;  // +0x20
  void* mpParent;      // +0x24
  char pad28[0x2c];
  void* m54;           // +0x54
  char pad58[0x9c];
  bool mf4;            // +0xf4
  void v38(bool);
  void v3c(ResourceKey*);
  void v40();
  // @ 0x0065af90
  void FUN_0065af90(bool active, int unused);
};

extern uint32_t g_15f9f40;
extern void** g_15fa018;
extern void** g_15fa01c;
void FUN_0065aed0(int n);

// @ 0x0065af90
void SiblingWin::FUN_0065af90(bool active, int) {
  m17 = active;
  ResourceKey k;
  v3c(&k);
  if (k.a == g_key_1526560.a && k.b == g_key_1526560.b && k.c == g_key_1526560.c && active) {
    if ((int)(((int*)g_15fa01c - (int*)g_15fa018)) <= (int)g_15f9f40)
      FUN_0065aed0((int)g_15f9f40 + 1);
    ILayoutObj* pNew = (ILayoutObj*)g_15fa018[g_15f9f40];
    ILayoutObj* pOld = mpLayout;
    g_15f9f40 = g_15f9f40 + 1;
    if (pNew != pOld) {
      if (pNew)
        pNew->a1();
      mpLayout = pNew;
      if (pOld)
        pOld->a2();
    }
    m1c = 1;
  } else {
    void* obj = operator_new_ea(0x18, "Sporepedia", 0, 0, 0, 0);
    ILayoutObj* pNew = obj ? (ILayoutObj*)LayoutCtor18() : 0;
    ILayoutObj* pOld = mpLayout;
    if (pNew != pOld) {
      if (pNew)
        pNew->a1();
      mpLayout = pNew;
      if (pOld)
        pOld->a2();
    }
    mpLayout->a43();  // placeholder for Init
    m1c = 0;
  }
  mpLayout->a65(mpParent);
  mpLayout->a66((void*)&FUN_00657420);
  v40();
  if (m54) {
    ILayoutObj* p = (ILayoutObj*)m54;
    int v = p->a43();  // 0x10 slot accessor stand-in
    (void)v;
    if (p->a43()) {
      ILayoutObj* q = (ILayoutObj*)p->a43();
      q->a56();
      ILayoutObj* r = (ILayoutObj*)m54;
      m54 = 0;
      r->a1();
    }
  }
  v38(mf4);
}

// ===========================================================================
// SP::cSPUIAssetWebBrowser
// ===========================================================================
class cSPUIAssetWebBrowser {
 public:
  void** vt;         // +0x00
  void** vt4;        // +0x04
  void** vt8;        // +0x08
  void** vtc;        // +0x0c
  int mRefCount;     // +0x10
  cSPUILayout* mpLayout;  // +0x14
  bool m18;          // +0x18
  char pad19[3];
  int mMode;         // +0x1c
  cXHTMLFrameSet mFrameSet;  // +0x20 (size 0x64)
  eastl::wstring mURL;       // +0x84
  bool mActive;      // +0x94
  char pad95[3];
  void* mpParentWin; // +0x98
  void* mpContentWin;  // +0x9c
  FeedList* mpFeedList;  // +0xa0
  int mState;        // +0xa4
  int mA8;           // +0xa8

  cSPUIAssetWebBrowser();
  ~cSPUIAssetWebBrowser();

  bool Shutdown();
  void SetActive(bool b);
  void FUN_0065b380();
  void FUN_0065b5f0();
  bool Init(void* parent, void* content);
  bool LoadPage(void* url);
  bool HandleMessage(int id, void* data);
  void FUN_0065b440(int a, int b);
  void FUN_0065b510();
  void FUN_0065b6b0(int msg, int param);
};

// @ 0x0065b1b0
bool cSPUIAssetWebBrowser::Shutdown() {
  if (mMode == 0) {
    IMessageServer* ms = MessageServer();
    ms->Unsub((char*)this + 8, 0xd4231540, (int)0xffffd8f1);
  }
  mFrameSet.FUN_00997140();
  if (mpLayout) {
    mpLayout->Shutdown(1);
    cSPUILayout* old = mpLayout;
    if (old) {
      mpLayout = 0;
      ((ILayoutObj*)old)->a2();
    }
  }
  if (mpParentWin) {
    ((ILayoutObj*)mpParentWin)->a66(mpParentWin);
    void* old = mpParentWin;
    if (old) {
      mpParentWin = 0;
      ((ILayoutObj*)old)->a1();
    }
  }
  if (mpFeedList) {
    mpFeedList->FUN_005febf0();
    FeedList* old = mpFeedList;
    if (old) {
      mpFeedList = 0;
      ((ILayoutObj*)old)->a1();
    }
  }
  if (mActive) {
    IMessageServer* ms = MessageServer();
    ms->Unsub((char*)this + 8, 0x3d1cd0b, (int)0xffffd8f1);
    ms = MessageServer();
    ms->Unsub((char*)this + 8, 0x3ffd8c9, (int)0xffffd8f1);
  }
  return true;
}

// @ 0x0065b2a0
void cSPUIAssetWebBrowser::SetActive(bool active) {
  if (!mpContentWin)
    return;
  if (active) {
    if (mActive)
      return;
    void* h = (char*)this + 8;
    IMessageServer* ms = MessageServer();
    ms->Sub(h, 0x3d1cd0b);
    ms = MessageServer();
    ms->Sub(h, 0x3ffd8c9);
    ms = MessageServer();
    ms->Sub(h, 0x3b60b3ad);
    mActive = true;
  } else {
    if (!mActive)
      return;
    void* h = (char*)this + 8;
    IMessageServer* ms = MessageServer();
    ms->Unsub(h, 0x3d1cd0b, (int)0xffffd8f1);
    ms = MessageServer();
    ms->Unsub(h, 0x3ffd8c9, (int)0xffffd8f1);
    ms = MessageServer();
    ms->Unsub(h, 0x3b60b3ad, (int)0xffffd8f1);
    mActive = false;
  }
}

// @ 0x0065b380
void cSPUIAssetWebBrowser::FUN_0065b380() {
  if (m18)
    return;
  void* w = mpLayout->FindWindowByID(0x61c8cb8, true);
  if (!w)
    return;
  ((ILayoutObj*)w)->a65(this);
  SPUIHelpers_SetWindowAreaToParent(w);
  if (!FUN_009979f0c(&mFrameSet, 0x61c8dc0)) {
    m18 = true;
    return;
  }
  void* frame = mFrameSet.GetFrame((uint32_t)g_152657c);
  if (frame)
    AutoRef_assign_0xb5f950(&mpContentWin, (char*)frame + 4);
  else
    AutoRef_assign_0xb5f950(&mpContentWin, 0);
  m18 = true;
}

void FUN_0065b410(cSPUIAssetWebBrowser* p, int unused, bool b);

// @ 0x0065b410
void FUN_0065b410(cSPUIAssetWebBrowser* p, int, bool b) {
  if (!b) {
    if (p->m18) {
      p->mFrameSet.FUN_00997140();
      p->m18 = false;
    }
    return;
  }
  p->FUN_0065b380();
}

// @ 0x0065b440
void cSPUIAssetWebBrowser::FUN_0065b440(int a, int b) {
  if (!mpFeedList)
    return;
  mpFeedList->FUN_005ff0d0();
  mpFeedList->FUN_005febb0(a, b);
  void* tbl = FUN_0067cb30();
  int idx = mpFeedList->FUN_005fedb0((void*)FUN_00ef4470(tbl));
  int count = (*(int*)((char*)tbl + 0xb8) - *(int*)((char*)tbl + 0xb4)) / 0x70;
  if (count) {
    int off = 0;
    do {
      char* e = (char*)(*(int*)((char*)tbl + 0xb4) + off);
      if (*(int*)(e + 0x68) != 7)
        mpFeedList->FUN_005fedb0(*(void**)(e + 0x18));
      off += 0x70;
      --count;
    } while (count);
  }
  mpFeedList->FUN_005fed90((void*)idx);
  mState = 3;
  mpFeedList->FUN_005fec90();
}

// @ 0x0065b510
void cSPUIAssetWebBrowser::FUN_0065b510() {
  extern const wchar_t* g_empty_1526598;
  mFrameSet.HandleLocationChange(mpContentWin, g_empty_1526598, 0, 0);
}

// @ 0x0065b5f0
void cSPUIAssetWebBrowser::FUN_0065b5f0() {
  void* obj = operator_new_ea(0x18, "Sporepedia", 0, 0, 0, 0);
  cSPUILayout* pNew = obj ? (cSPUILayout*)LayoutCtor18() : 0;
  cSPUILayout* pOld = mpLayout;
  if (pNew != pOld) {
    if (pNew)
      ((ILayoutObj*)pNew)->a1();
    mpLayout = pNew;
    if (pOld)
      ((ILayoutObj*)pOld)->a2();
  }
  ResourceKey key;
  key.a = 0xfcd77c3b;
  key.b = 0x510a95b;
  key.c = g_152685c;
  mpLayout->Init(&key, 1, 0x5b598fa);
  mpLayout->SetParentWin(mpParentWin, 1, 0x5b598fa);
  mpLayout->SetReloadCallback((void*)&FUN_0065b410, this);
  FUN_0065b380();
}

// @ 0x0065b6b0
void cSPUIAssetWebBrowser::FUN_0065b6b0(int msg, int param) {
  if (mState == 3) {
    if (msg != 0x6163290)
      goto reset;
    {
      void* tbl = FUN_0067cb30();
      param = 0;
      Content36* cv = (Content36*)mpContentWin;
      if (!cv->FUN_005fed70()) {
        IMessageServer* ms = MessageServer();
        uint32_t h = FNVHash("Link_CreateSporecast", 0x811c9dc5, 1);
        ResourceKey k;
        FUN_00666af0(&k, h);
        ms->Post(0xb3d53f95, &k, 0);
        ms = MessageServer();
        int n = Resource_GetFileCount(mpContentWin, 0);
        ms->Post(0x639cceb, (void*)n, 0);
        goto reset;
      }
      int sel = cv->FUN_005fed70();
      int count = (*(int*)((char*)tbl + 0xb8) - *(int*)((char*)tbl + 0xb4)) / 0x70;
      if (!count)
        goto reset;
      int i = 0;
      char* e = (char*)(*(int*)((char*)tbl + 0xb4));
      for (;;) {
        if (*(int*)(e + 0x68) != 7) {
          if (param == sel - 1) {
            FUN_005467e0();
            int v = 0;
            IMessageServer* ms = MessageServer();
            ms->Post(0x6255f5e, &v, 0);
            ms = MessageServer();
            int n = Resource_GetFileCount(mpContentWin, 0);
            ms->Post(0x639cceb, (void*)n, 0);
            goto reset;
          }
          ++param;
        }
        e += 0x70;
        if (++i >= count)
          break;
      }
      goto reset;
    }
  } else if (msg == 0x5107b1a && FUN_0067cb30()) {
    if (mState == 1) {
      void* f = *(void**)((char*)this + 0x80);
      cPollinator_SubscribeToFeed(FUN_0067cb30(), f);
      goto reset;
    }
    if (mState == 2) {
      void* f = *(void**)((char*)this + 0x80);
      cPollinator_UnsubscribeToFeed(FUN_0067cb30(), f);
    }
  }
reset:
  mState = 0;
}

// @ 0x0065b930
cSPUIAssetWebBrowser::cSPUIAssetWebBrowser()
    : mFrameSet((void*)&FUN_00657420) {
  mMode = 0;
  m18 = false;
  mActive = false;
  mpParentWin = 0;
  mpContentWin = 0;
  mpFeedList = 0;
  mA8 = 0;
}

// @ 0x0065ba20
cSPUIAssetWebBrowser::~cSPUIAssetWebBrowser() {
  if (mpFeedList) {
    ((ILayoutObj*)mpFeedList)->a2();
    mpFeedList = 0;
  }
  if (mpContentWin) {
    ((ILayoutObj*)mpContentWin)->a2();
    mpContentWin = 0;
  }
  if (mpParentWin) {
    ((ILayoutObj*)mpParentWin)->a2();
    mpParentWin = 0;
  }
  mURL.~wstring();
}

// @ 0x0065bac0
bool cSPUIAssetWebBrowser::Init(void* parent, void* content) {
  FUN_00996280(0x1002, 0x1006, 0x1003, 0x1024);
  mMode = (int)content;
  if (!mMode) {
    IMessageServer* ms = MessageServer();
    ms->Sub((char*)this + 8, 0xd4231540);
  }
  if (parent != mpParentWin) {
    if (parent)
      ((ILayoutObj*)parent)->a0();
    void* old = mpParentWin;
    mpParentWin = parent;
    if (old)
      ((ILayoutObj*)old)->a1();
  }
  if (!mpParentWin)
    return false;
  void* obj = operator_new_ea(0x50, (const char*)0x13f6b3c, 0, 0, 0, 0);
  FeedList* fl = obj ? (FeedList*)FUN_005feff0() : 0;
  FeedList* oldfl = mpFeedList;
  if (fl != oldfl) {
    if (fl)
      ((ILayoutObj*)fl)->a0();
    mpFeedList = fl;
    if (oldfl)
      ((ILayoutObj*)oldfl)->a1();
  }
  FUN_005feea0(mpFeedList, (char*)this + 4);
  if (mMode == 1) {
    FUN_0065b5f0();
    return mpContentWin != 0;
  }
  ((ILayoutObj*)parent)->a65(this);
  if (!FUN_009979f0c(&mFrameSet, 0x5406873))
    return false;
  void* frame = mFrameSet.GetFrame((uint32_t)g_152657c);
  void* p = frame ? (char*)frame + 4 : 0;
  AutoRef_assign_0xb5f950(&mpContentWin, p);
  return mpContentWin != 0;
}

// @ 0x0065bc20
bool cSPUIAssetWebBrowser::LoadPage(void* url) {
  if (!mpContentWin)
    return false;
  void* tmp[3];
  tmp[0] = (void*)0x1667bac;
  tmp[1] = (void*)0x1667bac;
  tmp[2] = (void*)0x1667bae;
  SP_Pollen_GetURL(url, tmp, tmp);
  return mFrameSet.HandleLocationChange(mpContentWin, (const wchar_t*)tmp[0], 0, 0);
}

// @ 0x0065bd80
bool cSPUIAssetWebBrowser::HandleMessage(int id, void* data) {
  if (id == 0x3d1cd0b || id == 0x3ffd8c9) {
    IMessageServer* ms = MessageServer();
    ms->Post(0x53dd093, 0, 0);
    if (mpContentWin) {
      void* w = ((ILayoutObj*)mpContentWin)->a3();
      if (w) {
        (void)w;
        void* doc = WinXHTML_GetDocument((void*)w);
        mFrameSet.HandleLocationChange(mpContentWin, *(const wchar_t**)((char*)doc + 0x48), 0, 0);
      }
    }
    return true;
  }
  if (id == (int)0xd4231540 && data) {
    LoadPage(*(void**)data);
    return true;
  }
  return false;
}

// @ 0x0065be20
bool ExtractFeedPath(const wchar_t* p, eastl::wstring* out) {
  eastl::wstring local(p);
  if (local.find(g_user, 0) != 0xffffffffu) {
    unsigned int pos = local.rfind(L'/', 0xffffffffu);
    if (pos != 0xffffffffu && (pos + 1) < local.size()) {
      eastl::wstring temp(local, pos + 1, 0xffffffffu);
      *out = temp;
      return true;
    }
  }
  return false;
}
