// Slice s00820cc0 -- SP::cPropertyUI constructor + scalar property modifiers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <stdlib.h>

// Retail layout of SP::cPropertyUI (the 2008 dev PDB layout differs from +0x5c on): the member
// vectors / AutoRefCounts are runs of three zeroed words at a 0x14 stride, and the three hash_maps
// are 0x20 bytes each at +0x130, +0x150, +0x170.

struct __declspec(novtable) IWinProc {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual int QueryInterface(uint32_t, void**) = 0;
};

struct RefCountVTemplate {
    int32_t mRefCount;
    RefCountVTemplate() : mRefCount(0) {}
    virtual int AddRef();
    virtual int Release();
};

// cSPUILayout (12 bytes): constructed by SPUIHelpers at 0x00810000 (thiscall, returns this).
class cSPUILayout { public:
    uint32_t pad[3];
    cSPUILayout() throw();      // 0x00810000
};

extern char gEmptyBucketArray[];   // 0x0154DF28

struct HashMapRaw {
    void* mpBucketArray;          // +0x00
    uint32_t mnBucketCount;       // +0x04
    uint32_t mnElementCount;      // +0x08
    float mfMaxLoadFactor;        // +0x0c
    float mfGrowthFactor;         // +0x10
    uint32_t mnNextResize;        // +0x14
    uint32_t unk[2];              // +0x18 (not set by the constructor)
    HashMapRaw() {
        mfMaxLoadFactor = 1.0f;
        mfGrowthFactor = 2.0f;
        mnBucketCount = 1;
        mpBucketArray = gEmptyBucketArray;
        mnElementCount = 0;
        mnNextResize = 0;
    }
};

struct Zero3 {
    void* a; void* b; void* c;
    Zero3() : a(0), b(0), c(0) {}
};

struct VecSlot {
    Zero3 v;
    uint32_t unk[2];               // not set by the constructor
};

struct cPropertyUI : public IWinProc, public RefCountVTemplate {
    uint32_t mCurrentGroupID;          // +0x0c
    uint32_t mCurrentInstanceID;       // +0x10
    float mCurrentX;                   // +0x14
    float mCurrentY;                   // +0x18
    float mCurrentWindowX;             // +0x1c
    float mCurrentWindowY;             // +0x20
    float mPreviousScrollVal;          // +0x24
    float mRefreshScrollVal;           // +0x28 (not set by the constructor)
    float mScrollRatio;                // +0x2c
    float mScrollHeight;               // +0x30
    uint32_t mSpinnerButtonID;         // +0x34
    float mFloatIncrement;             // +0x38
    uint32_t mIntIncrement;            // +0x3c
    bool returnPressed;                // +0x40
    cSPUILayout mLayout;               // +0x44
    char padDialogs[0x5c - 0x50];      // +0x50 (editor/chooser dialogs, holder window)
    void* mScrollbar;                  // +0x5c
    void* mTitleText;                  // +0x60
    void* w64; void* w68; void* w6c;   // +0x64..+0x6c
    VecSlot v0;                        // +0x70
    VecSlot v1;                        // +0x84
    VecSlot v2;                        // +0x98
    VecSlot v3;                        // +0xac
    VecSlot v4;                        // +0xc0
    VecSlot v5;                        // +0xd4
    VecSlot v6;                        // +0xe8
    VecSlot v7;                        // +0xfc
    VecSlot v8;                        // +0x110
    Zero3 v9;                          // +0x124
    uint32_t pad130;                   // +0x130
    HashMapRaw mPropToTextEditMap;     // +0x134
    HashMapRaw mSpinnerToTextEditMap;  // +0x154
    HashMapRaw mPropToToggleButtonMap; // +0x174

    cPropertyUI();
    void ReloadPropResource();                  // 0x0081e230
    void ModifyInt32(struct IW* w, bool multi);   // 0x00820ec0
    void ModifyUInt32(struct IW* w, bool multi);  // 0x00821260
    void ModifyFloat(struct IW* w, bool multi);   // 0x00821600
};

// @ 0x00820cc0
cPropertyUI::cPropertyUI()
    : mCurrentGroupID(0), mCurrentInstanceID(0),
      mCurrentX(0.0f), mCurrentY(10.0f), mCurrentWindowX(8.0f), mCurrentWindowY(60.0f),
      mPreviousScrollVal(0.0f), mScrollRatio(1.0f), mScrollHeight(256.0f),
      mSpinnerButtonID(0), mFloatIncrement(0.25f), mIntIncrement(1), returnPressed(false),
      mScrollbar(0), mTitleText(0), w64(0), w68(0), w6c(0)
{
}


// ---------------------------------------------------------------------------------------------
// ModifyInt32 / ModifyUInt32 / ModifyFloat: push the text of one edit control (multi == false) or of
// every child edit control (multi == true) into the property's int / uint / float value.
// Compiled WITHOUT /EHsc (no unwind frames): flags /O2 /MD /Gy /TP /arch:SSE /fp:fast
// ---------------------------------------------------------------------------------------------
#define VT(p, off) ((*(void***)(p))[(off) / 4])
#define VC0(R, p, off) ((R(__thiscall*)(void*))VT(p, off))(p)
#define NODE_ELEM(it) ((void*)((char*)g_nodeOfs + (int)(it)))

extern int g_nodeOfs;                         // 0x01440aec  offset from an intrusive list node to its element
struct PropMgr;
PropMgr* __cdecl GetPropMgr();                // 0x0067de30  SP::PropertyManager
void __cdecl Dealloc(void* p);                // 0x00f47380  operator delete[] / eastl deallocate
double __cdecl StrToD(const wchar_t* s, wchar_t** end);   // 0x0092ddc0

extern wchar_t gEmptyW[];                     // 0x01667bac  eastl empty-string storage
struct WStrE {                                // eastl::basic_string<char16_t> (begin, end, capacity end)
  wchar_t* b;
  wchar_t* e;
  wchar_t* cap;
  WStrE() { b = gEmptyW; e = gEmptyW; cap = gEmptyW + 1; }
  ~WStrE() { if ((((char*)cap - (char*)b) & ~1) > 2 && b) Dealloc(b); }
  void __thiscall assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

struct IW {
  virtual void AddRef();   // +0x0
  virtual void Release();   // +0x4
  virtual void s8();
  virtual IW* QI(uint32_t iid);   // +0xc
  virtual void s10(); virtual void s14(); virtual void s18();
  virtual uint32_t GetID();   // +0x1c
  virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30();
  virtual void s34(); virtual void s38(); virtual void s3c();
  virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
  virtual void s50();
  virtual const wchar_t* GetCaption();   // +0x54
  virtual void s58(); virtual void s5c();
  virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
  virtual void s70(); virtual void s74(); virtual void s78(); virtual void s7c();
  virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8c();
  virtual void s90(); virtual void s94(); virtual void s98(); virtual void s9c();
  virtual void sa0(); virtual void sa4(); virtual void sa8(); virtual void sac();
  virtual void sb0(); virtual void sb4(); virtual void sb8(); virtual void sbc();
  virtual void sc0(); virtual void sc4(); virtual void sc8();
  virtual char** Begin(void* t);   // +0xcc
  virtual char** End(void* t);   // +0xd0
};

struct PL {
  virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc(); virtual void s10();
  virtual void SetValue(uint32_t id, void* v);   // +0x14
  virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
  virtual void* GetItem(uint32_t id);   // +0x28
};

struct PropMgr {
  virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc(); virtual void s10();
  virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20();
  virtual void s24(); virtual void s28();
  virtual void GetPropList(uint32_t inst, uint32_t grp, void** out);   // +0x2c
};

struct ARC {                                  // EA::AutoRefCount<IW>
  IW* p;
  ARC() { p = 0; }
  ~ARC() { if (p) p->Release(); }
  ARC& operator=(IW* n) {
    IW* old = p;
    if (n != old) {
      if (n) n->AddRef();
      p = n;
      if (old) old->Release();
    }
    return *this;
  }
  ARC& operator=(const ARC& o) { return *this = o.p; }
  IW** Out() { if (p) { IW* t = p; p = 0; t->Release(); } return &p; }   // release and hand out the slot
};

struct Variant {                              // EA::Variant (data at +0, flags +0x10, type id +0x12)
  uint32_t f0, f4, f8, fc;
  uint16_t flags, typeId;
  Variant() { flags = 0; typeId = 0; }
  Variant(uint16_t t) { flags = 2; typeId = t; }
  ~Variant() { if (flags & 4) Destruct(false); }
  bool __thiscall Construct(uint16_t type, uint16_t fl, const void* data, uint32_t size, uint32_t count);   // 0x0093dd80
  Variant& __thiscall operator=(const Variant& o);   // 0x00542b80
  void __thiscall Destruct(bool b);           // 0x0093db80
  Variant& __thiscall SetInt32Ptr(int32_t* p);     // 0x0081d800
  Variant& __thiscall SetUInt32Ptr(uint32_t* p);   // 0x0081d870
  Variant& __thiscall SetFloatPtr(float* p);       // 0x0081d8e0
};

static inline void AssignCaption(WStrE& str, ARC& btn) {
  const wchar_t* s = btn.p->GetCaption();
  const wchar_t* e = s;
  while (*e) ++e;
  str.assign(s, s + (e - s));
}

// @ 0x00820ec0
void cPropertyUI::ModifyInt32(IW* w, bool multi) {
  ARC cur;
  WStrE str;
  ARC btn;
  ARC prop;
  PropMgr* pm = GetPropMgr();
  pm->GetPropList(mCurrentInstanceID, mCurrentGroupID, (void**)prop.Out());
  if (!multi) {
    btn = w ? w->QI(0xcf428691) : 0;
    AssignCaption(str, btn);
    Variant v1;
    v1.Construct(0x13, 9, &str, 0x10, 1);
    Variant v2(9);
    v2 = v1;
    ((PL*)prop.p)->SetValue(w->GetID(), &v2);
  } else {
    Variant* iv = (Variant*)((PL*)prop.p)->GetItem(w->GetID());
    int32_t* base = (iv->flags & 0x30) ? *(int32_t**)iv : (iv->typeId ? (int32_t*)iv : 0);
    int32_t* out = base;
    void* t1;
    void* t2;
    char* n = *w->Begin(&t1);
    if (n != *w->End(&t2)) {
      do {
        IW* c = (IW*)NODE_ELEM(n);
        if (c->GetID()) {
          cur = (IW*)NODE_ELEM(n);
          btn = cur.p ? cur.p->QI(0xcf428691) : 0;
          AssignCaption(str, btn);
          *out++ = wcstol(str.b, 0, 0);
        }
        n = *(char**)n;
      } while (n != *w->End(&t2));
    }
    Variant v(9);
    v.SetInt32Ptr(base);
    ((PL*)prop.p)->SetValue(w->GetID(), &v);
  }
  ReloadPropResource();
}

// @ 0x00821260
void cPropertyUI::ModifyUInt32(IW* w, bool multi) {
  ARC cur;
  WStrE str;
  ARC btn;
  ARC prop;
  PropMgr* pm = GetPropMgr();
  pm->GetPropList(mCurrentInstanceID, mCurrentGroupID, (void**)prop.Out());
  if (!multi) {
    btn = w ? w->QI(0xcf428691) : 0;
    AssignCaption(str, btn);
    Variant v1;
    v1.Construct(0x13, 9, &str, 0x10, 1);
    Variant v2(0xa);
    v2 = v1;
    ((PL*)prop.p)->SetValue(w->GetID(), &v2);
  } else {
    Variant* iv = (Variant*)((PL*)prop.p)->GetItem(w->GetID());
    uint32_t* base = (iv->flags & 0x30) ? *(uint32_t**)iv : (iv->typeId ? (uint32_t*)iv : 0);
    uint32_t* out = base;
    void* t1;
    void* t2;
    char* n = *w->Begin(&t1);
    if (n != *w->End(&t2)) {
      do {
        IW* c = (IW*)NODE_ELEM(n);
        if (c->GetID()) {
          cur = (IW*)NODE_ELEM(n);
          btn = cur.p ? cur.p->QI(0xcf428691) : 0;
          AssignCaption(str, btn);
          *out++ = wcstoul(str.b, 0, 0);
        }
        n = *(char**)n;
      } while (n != *w->End(&t2));
    }
    Variant v(0xa);
    v.SetUInt32Ptr(base);
    ((PL*)prop.p)->SetValue(w->GetID(), &v);
  }
  ReloadPropResource();
}

// @ 0x00821600
void cPropertyUI::ModifyFloat(IW* w, bool multi) {
  ARC cur;
  WStrE str;
  ARC btn;
  ARC prop;
  PropMgr* pm = GetPropMgr();
  pm->GetPropList(mCurrentInstanceID, mCurrentGroupID, (void**)prop.Out());
  if (!multi) {
    btn = w ? w->QI(0xcf428691) : 0;
    AssignCaption(str, btn);
    Variant v1;
    v1.Construct(0x13, 9, &str, 0x10, 1);
    Variant v2(0xd);
    v2 = v1;
    ((PL*)prop.p)->SetValue(w->GetID(), &v2);
  } else {
    Variant* iv = (Variant*)((PL*)prop.p)->GetItem(w->GetID());
    float* base = (iv->flags & 0x30) ? *(float**)iv : (iv->typeId ? (float*)iv : 0);
    float* out = base;
    void* t1;
    void* t2;
    char* n = *w->Begin(&t1);
    if (n != *w->End(&t2)) {
      do {
        IW* c = (IW*)NODE_ELEM(n);
        if (c->GetID()) {
          cur = (IW*)NODE_ELEM(n);
          btn = cur.p ? cur.p->QI(0xcf428691) : 0;
          AssignCaption(str, btn);
          wchar_t* endp;
          *out++ = (float)StrToD(str.b, &endp);
        }
        n = *(char**)n;
      } while (n != *w->End(&t2));
    }
    Variant v(0xd);
    v.SetFloatPtr(base);
    ((PL*)prop.p)->SetValue(w->GetID(), &v);
  }
  ReloadPropResource();
}
