// Slice s00827bf0 -- SP::cPropertyUI::DoMessage, SP::cSPUIPropertyLayout methods + vector_map element helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// Note: the dtor/ctor rows (828670, 8286d0) and the three eastl range helpers are compiled with the same flags
// minus /EHsc; the original has no EH frame for them (see manifest.txt / nonmatching.txt).
#include "types.h"
#include <new>

struct Key { unsigned int a, b, c; };
void SPKeyFromName(Key* out, const wchar_t* name, unsigned int ns, int id);

// ---- virtual-slot stand-ins (filler virtuals keep the vtable indices right) --------------
struct RectF { float x0, y0, x1, y1; };
struct Pt { float x, y; Pt() {} Pt(const Pt& o) : x(o.x), y(o.y) {} };
struct Rect2 { Pt a, b; };
struct UIObj {
  virtual void s0(); virtual void s1(); virtual void s2(); 
  virtual void* Cast(unsigned id);  // +0xc
  virtual UIObj* Get10();  // +0x10
  virtual void s5(); virtual void s6(); 
  virtual unsigned GetId();  // +0x1c
  virtual void s8(); virtual void s9(); 
  virtual int Get28();  // +0x28
  virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
  virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); 
  virtual void SetPos64(float x, float y);  // +0x64
  virtual void s26(); virtual void s27(); 
  virtual void SetPos(float x, float y);  // +0x70
  virtual void s29(); virtual void s30(); 
  virtual void Set7c(int a, int b);  // +0x7c
  virtual void Set80(unsigned a);  // +0x80
  virtual void s33(); virtual void s34(); virtual void s35(); 
  virtual void Fn90();  // +0x90
  virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); 
  virtual bool Fa4(unsigned* a, unsigned* b);  // +0xa4
  virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46();
  virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
  virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56();
  virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
  virtual void s62(); virtual void s63(); virtual void s64(); 
  virtual void Attach(void* p);  // +0x104
  virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69(); virtual void s70();
  virtual void s71(); virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
  virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79(); virtual void s80();
  virtual void s81(); virtual void s82(); virtual void s83(); virtual void s84(); virtual void s85();
  virtual void s86(); virtual void s87(); virtual void s88(); virtual void s89(); virtual void s90();
  virtual void s91(); virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95();
  virtual void s96(); virtual void s97(); virtual void s98(); virtual void s99(); virtual void s100();
  virtual void s101(); virtual void s102(); virtual void s103(); 
  virtual void F1a0(unsigned a, unsigned b, unsigned* c);  // +0x1a0
  virtual void s105(); virtual void s106(); virtual void s107(); virtual void s108(); virtual void s109();
  virtual void s110(); virtual void s111(); virtual void s112(); 
  virtual unsigned F1c4(unsigned a, unsigned b);  // +0x1c4
};

struct IdObj {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); 
  virtual unsigned GetId();  // +0x10
};

struct QObj {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
  virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
  virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); 
  virtual RectF* GetRect();  // +0x38
  virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
  virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
  virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
  virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
  virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
  virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
  virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); 
  virtual Pt* FindPos(Pt* out, Pt p);  // +0xc4
};

struct WinMgr {
  virtual void s0(); 
  virtual QObj* GetMain();  // +0x4
};

struct MsgSrv {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
  virtual void Post(unsigned id, int a, int b);  // +0x14
};

struct WinProcBase {
  WinProcBase() {}
  ~WinProcBase() {}
  virtual int AddRef();  // +0x0
  virtual int Release();  // +0x4
  virtual void s2(); 
  virtual void* Cast(unsigned id);  // +0xc
  virtual void s4(); 
  virtual unsigned GetEventMask();  // +0x14
  virtual bool DoMessage(int, void*);  // +0x18
  virtual bool Init();  // +0x1c
  virtual void func20h();  // +0x20
  virtual void func24h();  // +0x24
};

WinMgr* WindowManager();                         // 0x0067caa0
MsgSrv* SP_MessageServer();                      // 0x0067dcc0
Rect2* FUN_00808370(Rect2* out, UIObj* w, int flag);   // 0x00808370 (cdecl)
typedef UIObj IWindow;

// ---- layout / window helpers --------------------------------------------
struct cSPUILayout {
  cSPUILayout();                              // 0x00810000
  ~cSPUILayout();                             // 0x00811fe0
  void Shutdown(int);                         // 0x00811ad0 (callee pops)
  bool IsVisible() const;                     // 0x00810070
  bool Init(const Key* k, bool b, unsigned u);   // 0x008120d0
  void* FindWindowByID(int id, int flag);     // 0x008105b0 __thiscall (callee pops)
  struct ObjVec { UIObj** mpBegin; UIObj** mpEnd; };
  ObjVec* GetObjects();                       // 0x008100c0
  void* mpVtbl;               // +0x0
  int mRefCount;              // +0x4
  void* mpObject;             // +0x8
};

// ===========================================================================
// SP::cPropertyUI::DoMessage (retail layout: hash maps at +0x130/+0x150/+0x170)
// ===========================================================================
struct Msg { char pad[8]; unsigned type; unsigned param; int p10; int p14; };

struct IdObj;
struct HashNode { unsigned first; IdObj* second; HashNode* next; };
struct HashIter { HashNode* mpNode; HashNode** mpBucket; };
struct HashMapU32 {
  unsigned pad0;
  HashNode** mpBucketArray;   // +4
  unsigned mnBucketCount;     // +8
  char pad1[0x20 - 0xc];
  HashIter find(const unsigned& key);   // 0x00645ed0
};

struct DirPropList2 { char pad[0x3c]; struct AppX* mp3c; void SetBoolProperty(unsigned id, bool v); };  // 0x006a17e0
struct AppX { char pad[0x54]; int v54; };
extern DirPropList2* g_AppProperties;     // 0x015fd918

namespace SP {
struct cPropertyUI {
  virtual int vslot0();
  char pad4[8];               // +0x4 .. +0xb
  unsigned mCurrentGroupID;   // +0xc
  char pad10[0x1c - 0x10];
  float mCurrentWindowX;      // +0x1c
  float mCurrentWindowY;      // +0x20
  float mPreviousScrollVal;   // +0x24
  char pad28[4];
  float mScrollRatio;         // +0x2c
  char pad30[0x40 - 0x30];
  bool returnPressed;         // +0x40
  char pad41[3];
  cSPUILayout mLayout;        // +0x44
  char pad50[0x60 - 0x50];
  UIObj* mTitleText;          // +0x60
  UIObj* mWin64;              // +0x64
  UIObj* mWin68;              // +0x68
  UIObj* mWin6c;              // +0x6c
  char pad70[0x128 - 0x70];
  UIObj* mGroupsGrid;         // +0x128
  UIObj* mPropsGrid;          // +0x12c
  HashMapU32 mPropToTextEditMap;   // +0x130
  HashMapU32 mSpinnerMap;          // +0x150
  HashMapU32 mPropToToggleMap;     // +0x170

  bool DoMessage(int, Msg* m);
  void ProcessTextChange(unsigned);       // 0x00823b50
  void ProcessToggleButton(unsigned);     // 0x0081f020
  void ProcessSpinnerButtons(unsigned);   // 0x00823e30
  void SavePropFile();                    // 0x008220e0
  void LoadPropFile(unsigned, unsigned, bool);  // 0x00826960
  void PopulatePropsGrid(unsigned);       // 0x0081ebe0
  void FUN_0081e070();                    // 0x0081e070
};
}

// @ 0x00827bf0
bool SP::cPropertyUI::DoMessage(int, Msg* m) {
  if (!mLayout.IsVisible()) return false;
  if (m->type == 1 && m->p14 == 0 && m->p10 == 0xd) returnPressed = true;
  
  if (m->type == 0x8f4d1282) {
    if (m->param == 0x154feb2) {
      mTitleText->Get10()->Set7c(1, 0);
      return true;
    }
    if (m->param == 0x153a7c9) {
      g_AppProperties->SetBoolProperty(0x15, g_AppProperties->mp3c->v54 == 0);
      SP_MessageServer()->Post(0x15bbbf3, 0, 0);
      return true;
    }
  }
  if (m->type == 0x9b1552d8) {
    unsigned key = m->param;
    HashIter it = mPropToTextEditMap.find(key);
    if (it.mpNode != mPropToTextEditMap.mpBucketArray[mPropToTextEditMap.mnBucketCount]) {
      ProcessTextChange(it.mpNode->second->GetId());
      returnPressed = false;
      return true;
    }
  }
  if (m->type == 0x287259f6) {
    unsigned id = m->param;
    switch (id) {
    case 0x153a7f7:
      SavePropFile();
      return true;
    case 0x153a853:
      mTitleText->Get10()->Set7c(1, 1);
      return true;
    case 0x154febb:
      mTitleText->Get10()->Set7c(1, 0);
      return true;
    default: {
      unsigned key = id;
      HashIter it = mPropToToggleMap.find(key);
      if (it.mpNode != mPropToToggleMap.mpBucketArray[mPropToToggleMap.mnBucketCount]) {
        ProcessToggleButton(it.mpNode->second->GetId());
        return true;
      }
      ProcessSpinnerButtons(id);
      return true;
    }
    }
  }
  if (m->type == 0x8ef0c8dd && m->param == 0x15a490f) {
    int v = mWin68->Get28();
    float prev = mPreviousScrollVal;
    mPreviousScrollVal = (float)v;
    mCurrentWindowY = mCurrentWindowY - mScrollRatio * ((float)v - prev);
    mWin64->SetPos64(mCurrentWindowX, mCurrentWindowY);
    FUN_0081e070();
    return true;
  }
  if (m->type == 0x9a1552d3) {
    unsigned id = m->param;
    if (id == 0x154fec5) {
      unsigned a, b;
      if (mGroupsGrid->Fa4(&a, &b)) {
        mCurrentGroupID = mGroupsGrid->F1c4(a, b);
        PopulatePropsGrid(mCurrentGroupID);
      }
      return true;
    }
    if (id == 0x154fed1) {
      unsigned a, b, z;
      if (mPropsGrid->Fa4(&a, &b)) {
        unsigned r = mPropsGrid->F1c4(a, b);
        if (r) {
          mPropsGrid->F1a0(a, b, &z);
          mWin6c->Get10()->Set7c(1, 1);
          mWin6c->Get10()->Set80(z);
          mWin6c->Get10()->Fn90();
          LoadPropFile(mCurrentGroupID, r, false);
        }
      }
      return true;
    }
  }
  return false;
}

// ===========================================================================
// retail cSPUIPropertyLayout (offsets confirmed from disassembly)
// ===========================================================================
struct Stopwatch {
  char pad0[0x14];            // +0x0
  float mUnitsPerSecond;      // +0x14
  Stopwatch(int units, bool b);    // 0x0093a560 (callee pops)
  __int64 GetElapsedTime();
};

struct Variant {
  char pad[0x10];
  unsigned short mFlags;
  unsigned short mTypeId;
  Variant() { mFlags = 0; mTypeId = 0; }
  Variant& operator=(const Variant&);   // 0x00542b80
  void Destruct(int);
};

struct IRefThing { virtual int AddRef(); virtual int Release(); };

// eastl::pair<unsigned int, cSPUIPropertyLayout::cProperty> (0x20 bytes)
struct Elem {
  unsigned int first;      // +0x00
  void* mpObject;          // +0x04
  Variant mVariant;        // +0x08
  int mLast;               // +0x1c
  Elem(const Elem& o);
  Elem& operator=(const Elem& o);
};

// eastl::vector<Elem> (vector_map storage)
struct ElemVec {
  Elem* mpBegin;
  Elem* mpEnd;
  Elem* mpCapacity;
  ElemVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~ElemVec() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin) operator delete(mpBegin);
  }
  void DoDestroyValues(Elem* first, Elem* last);
};

struct RefCountBase {
  RefCountBase() : mRefCount(0) {}
  ~RefCountBase() {}
  virtual int rc0(); virtual int rc1(); virtual int rc2(); virtual int rc3();
  int mRefCount;              // +0x8
};

struct CPL : WinProcBase, RefCountBase {
  cSPUILayout mLayout;        // +0xc
  char pad18[0xc];            // +0x18 .. +0x23
  int mKey24;                 // +0x24
  int mKey28;                 // +0x28
  ElemVec mProperties;        // +0x2c
  char pad38[0xc];            // +0x38 .. +0x43
  bool mbInitialized;         // +0x44
  int mRootWinId;             // +0x48
  float mInterval;            // +0x4c
  Stopwatch mStopwatch;       // +0x50
  float mTime;                // +0x68
  float mOffsetX;             // +0x6c
  float mOffsetY;             // +0x70
  bool mbFlag;                // +0x74

  CPL();
  ~CPL();
  virtual unsigned GetEventMask();
  virtual bool DoMessage(int, void*);
  virtual bool Init();
  void SetKey(const wchar_t* name, int uid);
  void SetFlag(bool b);
  void* GetRootWindow();
  void SetPositionAndOffset(float x, float y, float offX, float offY);
  void ForceVisibleLocation();
};

// ===========================================================================
// 00827fc0
// ===========================================================================
void CPL::SetKey(const wchar_t* name, int uid) {
  if (name) {
    Key k = {0, 0, 0};
    SPKeyFromName(&k, name, 0x510a95b, uid);
    mKey28 = uid;
    mKey24 = (int)k.a;
  }
}

// ===========================================================================
// 00828020
// ===========================================================================
void CPL::SetFlag(bool b) {
  if (b != mbFlag) {
    mbFlag = b;
    IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
    if (w) {
      ((void(__thiscall*)(void*, void*))(*(void***)w)[0x104 / 4])(w, this);
      ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, mbFlag);
    }
  }
}

// ===========================================================================
// 00828070  cSPUIPropertyLayout::GetEventMask
// ===========================================================================
unsigned int CPL::GetEventMask() {
  return mbFlag ? 2 : 0;
}

// ===========================================================================
// 00828080  cSPUIPropertyLayout::DoMessage
// ===========================================================================
bool CPL::DoMessage(int a, void* b) {
  if (*(int*)((char*)b + 8) == 0xc) {
    if (mTime > mInterval) {
      ((void(__thiscall*)(void*))(*(void***)this)[0x20 / 4])(this);
    }
    Stopwatch& sw = mStopwatch;
    mTime = (float)sw.GetElapsedTime() * sw.mUnitsPerSecond;
  }
  return false;
}

// ===========================================================================
// 00828100  cSPUIPropertyLayout::GetRootWindow
// ===========================================================================
void* CPL::GetRootWindow() {
  return mLayout.FindWindowByID(mRootWinId, 1);
}

// ===========================================================================
// 008283a0  cSPUIPropertyLayout::SetPositionAndOffset
// ===========================================================================
void CPL::SetPositionAndOffset(float x, float y, float offX, float offY) {
  mOffsetX = offX;
  mOffsetY = offY;
  IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
  if (w) {
    ((void(__thiscall*)(void*, float, float))(*(void***)w)[0x70 / 4])(w, x + offX, y + offY);
    ForceVisibleLocation();
  }
}

// ===========================================================================
// vector_map element helpers (eastl::pair<unsigned int, cProperty>, 0x20 bytes)
// These are complete but not byte-exact (instruction scheduling of the inlined
// Variant reset differs); see nonmatching.txt.
// ===========================================================================
// 00828450 pair element copy-ctor
// @ 0x00828450
Elem::Elem(const Elem& o) : first(o.first), mpObject(o.mpObject) {
  if (mpObject) ((IRefThing*)mpObject)->AddRef();
  mVariant = o.mVariant;
  mLast = o.mLast;
}

// 008284a0 pair element operator=
Elem& Elem::operator=(const Elem& o) {
  first = o.first;
  void* old = mpObject;
  void* nw = o.mpObject;
  if (nw != old) {
    if (nw) ((IRefThing*)nw)->AddRef();
    mpObject = nw;
    if (old) ((IRefThing*)old)->Release();
  }
  mVariant = o.mVariant;
  mLast = o.mLast;
  return *this;
}

// 00828410 vector::DoDestroyValues
// @ 0x00828410
void ElemVec::DoDestroyValues(Elem* first, Elem* last) {
  for (; first < last; ++first) {
    Variant* v = &first->mVariant;
    if (first->mVariant.mFlags & 4) v->Destruct(0);
    IRefThing* p = (IRefThing*)first->mpObject;
    if (p) p->Release();
  }
}

// 00828350 destroy-source / advance-dest range helper
// @ 0x00828350
Elem* ElemDestroyRange(Elem* first, Elem* last, Elem* dst) {
  while (first != last) {
    Variant* v = &first->mVariant;
    if (first->mVariant.mFlags & 4) v->Destruct(0);
    IRefThing* p = (IRefThing*)first->mpObject;
    if (p) p->Release();
    ++first;
    ++dst;
  }
  return dst;
}

// ===========================================================================
// 00828110  cSPUIPropertyLayout::ForceVisibleLocation
// If the window's top-left (translated to screen space) lies past the right/bottom edge of the
// main window, mirror it back across the edge by the stored offset.
// ===========================================================================
// @ 0x00828110
void CPL::ForceVisibleLocation() {
  IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
  if (w) {
    if (w->Get10()) {
      if (WindowManager()->GetMain()) {
        QObj* q = WindowManager()->GetMain();
        RectF* r = q->GetRect();
        Rect2 R;
        Pt P;
        FUN_00808370(&R, w, 1);
        Pt pf = *q->FindPos(&P, R.b);
        float x = P.x;
        float y = P.y;
        if (pf.x > r->x1) x = (P.x - mOffsetX * 2.0f) - (R.a.x - P.x);
        if (pf.y > r->y1) y = (P.y - mOffsetY * 2.0f) - (R.a.y - P.y);
        w->SetPos(x, y);
      }
    }
  }
}

// ===========================================================================
// 00828250  cSPUIPropertyLayout::Init
// ===========================================================================
// @ 0x00828250
bool CPL::Init() {
  if (!mbInitialized) {
    mTime = 1.0e30f;
    Key k = {(unsigned)mKey24, 0x510a95b, (unsigned)mKey28};
    mbInitialized = mLayout.Init(&k, false, 0x5b598fa);
    if (mbInitialized) {
      IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
      if (!w) {
        cSPUILayout::ObjVec* objs = mLayout.GetObjects();
        int n = (int)(objs->mpEnd - objs->mpBegin);
        for (int i = 0; i < n; ++i) {
          IWindow* c = (IWindow*)objs->mpBegin[i]->Cast(0xeeee8218);
          if (c) {
            mRootWinId = c->GetId();
            w = c;
            break;
          }
        }
      }
      mbInitialized = (w != 0);
      if (w) w->Attach(this);
    }
  }
  return mbInitialized;
}

// ===========================================================================
// 00828560 / 008284f0 / 008285e0  eastl range helpers for pair<unsigned, cProperty>
// ===========================================================================
// @ 0x008284f0
Elem* ElemMoveStart(Elem* first, Elem* last, Elem* dst) {
  for (; first != last; ++first, ++dst) {
    if (dst) ::new ((void*)dst) Elem(*first);
  }
  return dst;
}

// @ 0x00828560
Elem* ElemCopy(Elem* first, Elem* last, Elem* dst) {
  for (; first != last; ++first, ++dst) *dst = *first;
  return dst;
}

// @ 0x008285e0
Elem* ElemCopyBackward(Elem* first, Elem* last, Elem* dst) {
  while (last != first) {
    --last;
    --dst;
    *dst = *last;
  }
  return dst;
}

// ===========================================================================
// 00828670 / 008286d0  cSPUIPropertyLayout dtor / ctor
// ===========================================================================
// @ 0x00828670
CPL::~CPL() {
  mLayout.Shutdown(1);
}

// @ 0x008286d0
CPL::CPL() : mKey24(-1), mKey28(-1), mbInitialized(false), mRootWinId(0), mInterval(1.0f), mStopwatch(5, false) {
  mTime = 1.0e30f;
  mbFlag = true;
}
