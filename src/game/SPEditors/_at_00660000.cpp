// src/game/SPEditors/_at_00660000.cpp -- migrated from slice(s) s0066afd0, s00669f50, s00662d70 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00660000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIFeedListCategory.h"
#include "cSPUILayout.h"
#include "SP/cSPUIFeedList.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" bool  FeedListReserve(void* vec, unsigned key, int* countOut, void** arrayOut); // 0x006a0ae0
#include <intrin.h>
#include "SP/cString.h"
#include "SP/cSPUIFeedListItem.h"
#include <string.h>

// ---- items of slice s00662d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void(__thiscall* FnThV)(void*);
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
struct ThCategory {                                  // SP::cSPUIFeedListCategory
    void* Ctor();                                    // 0x00664c90
    char  Init(void* a, void* b, void* c, void* d);  // 0x006661d0
    void  SetFlag(char v);                           // 0x006644e0
    void  Shutdown();                                // 0x00663e50
};
struct ThProp {                                      // cSPProperty
    void* GetBoolPtr();                              // 0x0041e920
};
struct ThVec {                                       // eastl::vector<AutoRefCount<...>>
    void PushBackSlow(void* pos, void* src);         // 0x005c9f20
};
extern "C" bool  FeedListReserve(void* vec, unsigned key, int* countOut, void** arrayOut); // 0x006a0ae0
struct cSPUIFeedList {
    void FUN_00663350(int param);
    char  vt[0xc];                     // 0x00
    bool  mIsVisible;                  // 0x10
    bool  mWheel;                      // 0x11
    bool  m12;                         // 0x12
    bool  m13;                         // 0x13
    float mTarget;                     // 0x14
    float mActual;                     // 0x18
    float mMax;                        // 0x1c
    void* mpLayout;                    // 0x20
    void* mpWinParent;                 // 0x24
    void* mpWinRoot;                   // 0x28
    void* mpWinList;                   // 0x2c
    void* mpWinScrollRoot;             // 0x30
    void* mpWinScrollClientArea;       // 0x34
    void* mCatBegin;                   // 0x38
    void* mCatEnd;                     // 0x3c
    void* mCatCap;                     // 0x40
    void* m44;                         // 0x44
    char  pad48[4];                    // 0x48
    void* mpSelectedFeed;              // 0x4c
    void* mpServer;                    // 0x50
    void* mpHandler;                   // 0x54
    void* mpIdArray;                   // 0x58
    int   mnIdArrayCount;              // 0x5c
    int   mnPriority;                  // 0x60
    void* mpConfig;                    // 0x64

    void* Ctor();
    void  Dtor();
    void  ShutdownCategories();
    void  FUN_006634d0();                                          // 0x006634d0
    void  ReloadCallback(void* parent, int a, int b, void* cfg);   // 0x00663860
};
struct VecAutoRef {
    void* begin; void* end; void* cap;
    void erase(void* first, void* last);
};
// ---- items of slice s00662d70 end

// ---- items of slice s00669f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_ids24[24];
extern int* g_vecBegin15fb19c;
extern int* g_vecEnd15fb1a0;
struct VObj { void** vt; };
struct CItem { char pad[0xc]; int* p; };
typedef int  (__thiscall *FnRetInt)(void*);
typedef long long (__thiscall *FnRetLL)(void*);
typedef bool (__thiscall *FnRetBool)(void*);
typedef void* (__thiscall *FnV0)(void*);
typedef void* (__thiscall *FnV0i)(void*, int);
typedef int  (__thiscall *FnV2iR)(void*, int, int);
unsigned __cdecl FUN_006b8ea0(int, int, int);
struct Neger {
  int Neg(int a, int b);
};
struct Switcher {
  int pad0; int pad1; int m8;
  unsigned Get();
};
struct Switcher2 {
  int pad0; int pad1; int m8;
  unsigned Get();
};
__forceinline int* Lookup0066(void* a) {
  int* p = *(int**)((char*)a + 0xc);
  return p ? (int*)((FnV0i)((VObj*)((char*)p + 0x10))->vt[3])(
                 (VObj*)((char*)p + 0x10), 0x13d55dc8)
           : 0;
}
struct Cmp0c {
  unsigned operator()(int a, int b);
};
struct Cmp10 {
  unsigned operator()(int a, int b);
};
struct Cmp70 {
  unsigned operator()(int a, int b);
};
struct Cmp38 {
  unsigned operator()(CItem& a, CItem& b);
};
struct Cmp28 {
  unsigned operator()(int a, int b);
};
struct Cmp94 {
  unsigned operator()(int a, int b);
};
struct Cmp950 {
  unsigned operator()(int a, int b);
};
struct CmpAd {
  int pad0; int pad1; int m8;
  unsigned operator()(int a, int b);
};
typedef int (__thiscall *FnCmp2)(void*, void*, void*);
struct Sorter830 {
  int pad0, pad1, pad2;   // +0x0..+0xc
  int* mC;                // +0xc
  int* m10;               // +0x10
  char pad14[0xc];
  bool m20;               // +0x20
  bool operator()(void* pa, void* pb);
};
struct SortElem {
  unsigned m0;            // +0x0
  unsigned m4;            // +0x4
  unsigned m8;            // +0x8
  char pad0c[4];
  void* m10;              // +0x10
  char pad14[8];
  unsigned char m1c;      // +0x1c
  unsigned char m1d;      // +0x1d
};
struct CmpA680 {
  int pad0; int pad1; int m8;
  unsigned operator()(int a, int b);
};
// ---- items of slice s00669f50 end

// ---- items of slice s0066afd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gVecEnd;     // 0x015fb124
extern void* gVecCap;     // 0x015fb128
extern void* gVecObj;     // 0x015fb120
extern void* gTreeHead;    // 0x01527b90
extern void* gTreeHead2;   // 0x01527b94
extern void* gTreeRoot;    // 0x01527b98
extern uint8_t gB9c;       // 0x01527b9c
extern uint32_t gBA0;      // 0x01527ba0
typedef int   (__thiscall *FnIntV)(void*);
#define VT(p) (*(void***)(p))
struct RefObj {
    virtual void v0();       // +0x00 AddRef
    virtual int  Release();  // +0x04
    virtual void Release2(); // +0x08
    virtual void v3();       // +0x0c
};
class Vec {
 public:
  void push_back(void* end, void* const& value);   // 0x005c8480
};
struct MapU {
    unsigned* operator[](const unsigned& k);
};
extern MapU gMapU;        // 0x01527b8c
struct ObjA { char pad0[0xc]; void* c; };
struct ObjB { char pad0[0xc]; void* c; };
void __cdecl DoNukeSubtreeStub(void* p);
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   int file, int line);   // 0x00f473a0 (EA allocator, 6 args)
struct SpHandler {                          // refcounted handler: [vt][refcount](+field)
    virtual void v0();
    virtual void AddRef();                  // +0x04
    virtual void Release();                 // +0x08
    int mRefCount;                          // +0x04 in memory: vptr is at +0
    SpHandler() : mRefCount(0) {}
};
template <int N> struct SpHandlerN : SpHandler {      // eight distinct 8-byte handler classes
    virtual void Apply();
};
struct SpHandlerA : SpHandler {                        // vtable 0x01400600, 12 bytes
    int mKind;
    SpHandlerA(int k) : mKind(k) {}
    virtual void Apply();
};
struct SpHandlerB : SpHandler {                        // vtable 0x014004e0, 12 bytes
    int mKind;
    SpHandlerB(int k) : mKind(k) {}
    virtual void Apply();
};
struct SpHandlerVec {                       // global vector of refcounted handlers (0x015fb120)
    SpHandler** mBegin;                     // +0x00
    SpHandler** mEnd;                       // +0x04
    SpHandler** mCap;                       // +0x08
    void DoInsertValueEnd(SpHandler** pos, const struct SpRef& v);   // 0x005c8480 (thiscall, ret 8)
};
extern SpHandlerVec gSpHandlers;            // 0x015fb120
struct SpRef {                              // AutoRefCount<SpHandler>
    SpHandler* mp;
    SpRef(SpHandler* q) { mp = q; if (q) q->AddRef(); }
    ~SpRef() { if (mp) mp->Release(); }
};
#define REGISTER_HANDLER(EXPR) { \
    SpHandler* raw = EXPR; \
    SpRef r(raw); \
    if (gSpHandlers.mEnd < gSpHandlers.mCap) { \
        SpHandler** slot = gSpHandlers.mEnd; \
        gSpHandlers.mEnd = slot + 1; \
        if (slot) { \
            *slot = r.mp; \
            if (r.mp) r.mp->AddRef(); \
        } \
    } else { \
        gSpHandlers.DoInsertValueEnd(gSpHandlers.mEnd, r); \
    } \
}
#define NEW_SP(T, args) new ("Sporepedia", 0, 0, 0, 0) T args
// ---- items of slice s0066afd0 end

// @ 0x006634d0
void cSPUIFeedList::FUN_006634d0()
{
    char* p = (char*)this;
    int n = (int)((*(char**)(p + 0x3c) - *(char**)(p + 0x38)) >> 2);
    for (int i = 0; i < n; ++i)
        ((ThCategory*)*(void**)(*(int*)(p + 0x38) + i * 4))->Shutdown();
    ((VecAutoRef*)(p + 0x38))->erase(*(void**)(p + 0x38), *(void**)(p + 0x3c));

    if (*(void**)(p + 0x30) == 0)
        return;

    void* cat = 0;
    void* pending = 0;
    int count = 0;
    void* array = 0;
    if (!FeedListReserve(*(void**)(p + 0x68), 0x744717c0, &count, &array))
        return;

    for (int i = 0; i < count; ++i) {
        void* mem = EASTL_allocator_allocate(0xd8, (const char*)0x013f6b3c, 0, 0, 0, 0);
        void* fresh = mem ? ((ThCategory*)mem)->Ctor() : 0;
        if (fresh != cat) {
            if (fresh) (*(FnThV)Vslot(fresh, 8))(fresh);
            if (cat) (*(FnThV)Vslot(cat, 0xc))(cat);
            cat = fresh;
            pending = fresh;
        }
        if (((ThCategory*)cat)->Init(*(void**)(p + 0x30), *(void**)(p + 0x28),
                                     array ? *(void**)((char*)array + i * 0xc) : 0, p)) {
            void** end = (void**)(p + 0x3c);
            if (*end < *(void**)(p + 0x40)) {
                void* slot = *end;
                *end = (char*)slot + 4;
                if (slot) {
                    *(void**)slot = cat;
                    if (cat) (*(FnThV)Vslot(cat, 8))(cat);
                }
            } else {
                ((ThVec*)(p + 0x38))->PushBackSlow(*end, &pending);
                cat = pending;
            }
        }
    }

    if (count == 1) {
        void* cfg = *(void**)(p + 0x68);
        int v = 0;
        bool skip = true;
        if (cfg) {
            if ((*(char(__thiscall*)(void*, unsigned, int*))Vslot(cfg, 0x24))(cfg, 0xea7e4c1c, &v)
                && *(short*)((char*)&v + 0x12) == 1) {
                skip = (*(char*)((ThProp*)v)->GetBoolPtr() != 0);
            }
        }
        if (skip) ((ThCategory*)*(void**)(p + 0x38))->SetFlag(0);
    }
    if (cat) (*(FnThV)Vslot(cat, 0xc))(cat);
}

// @ 0x0066a5c0
int FindIndex0066a5c0(int x)
{
  int i = 0;
  do {
    if (x == g_ids24[i]) return i;
    ++i;
  } while (i < 0x18);
  return 0x18;
}

// @ 0x0066a610
int Neger::Neg(int a, int b)
{
  return -((FnV2iR)((VObj*)this)->vt[5])(this, a, b);
}

// @ 0x0066a630
unsigned Switcher::Get()
{
  switch (m8) {
  case 0: return 0x2dfb4f9f;
  case 1: return 0xa28a67e8;
  case 2: return 0x5cd23f68;
  case 3: return 0x93b9d42e;
  case 4: return 0x38f64117;
  default: return 0;
  }
}

// @ 0x0066a680
unsigned CmpA680::operator()(int a, int b)
{
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  float* fa = 0;
  float* fb = 0;
  if (p) {
    int* r = (int*)((FnV0)((VObj*)p)->vt[38])(p);
    if (*r == 0) fa = (float*)((FnV0)((VObj*)p)->vt[38])(p) + 1;
  }
  if (q) {
    int* r = (int*)((FnV0)((VObj*)q)->vt[38])(q);
    if (*r == 0) fb = (float*)((FnV0)((VObj*)q)->vt[38])(q) + 1;
  }
  if (!fa) return fb != 0;
  if (fb) {
    float x, y;
    switch (m8) {
    case 0: x = (*(int*)fa == 1) ? 1.0f : 0.0f; y = (*(int*)fb == 1) ? 1.0f : 0.0f; break;
    case 1: x = (*(int*)fa == 2) ? 1.0f : 0.0f; y = (*(int*)fb == 2) ? 1.0f : 0.0f; break;
    case 2: x = (*(int*)fa == 3) ? 1.0f : 0.0f; y = (*(int*)fb == 3) ? 1.0f : 0.0f; break;
    case 3: x = fa[1]; y = fb[1]; break;
    case 4: x = fa[2]; y = fb[2]; break;
    default: return 0;
    }
    if (x == y) return 0;
    if (x <= y) return 1;
  }
  return 0xffffffff;
}

// @ 0x0066a800
int GetElem0066a800(int i)
{
  if (i >= 0 && i < (int)(g_vecEnd15fb1a0 - g_vecBegin15fb19c))
    return g_vecBegin15fb19c[i];
  return 0;
}

// @ 0x0066a830
bool Sorter830::operator()(void* pa, void* pb)
{
  SortElem* a = (SortElem*)pa;
  SortElem* b = (SortElem*)pb;
  if (b->m1c != a->m1c) return b->m1c < a->m1c;
  unsigned char a1 = a->m1d;
  bool av = false, bv = false;
  if (a1 == 0 && a->m10 != 0 && *(char*)((char*)a->m10 + 0xf4) != 0) av = true;
  if (b->m1d == 0 && b->m10 != 0 && *(char*)((char*)b->m10 + 0xf4) != 0) bv = true;
  if (bv != av) return bv < av;
  if (b->m1d != a1) return b->m1d < a1;
  int n = (int)(m10 - mC);
  for (int i = 0; i < n; ++i) {
    void* obj;
    int slot;
    if (i == 0 && m20) { obj = *(void**)mC; slot = 6; }
    else { obj = (void*)mC[i]; slot = 5; }
    int res = ((FnCmp2)((VObj*)obj)->vt[slot])(obj, pa, pb);
    if (res != 0) return res < 0;
  }
  if (a->m0 == b->m0) {
    if (a->m4 == b->m4 && a->m8 == b->m8) return false;
    if (a->m8 != b->m8) return a->m8 < b->m8;
    return a->m4 < b->m4;
  }
  return a->m0 < b->m0;
}

// @ 0x0066a950
unsigned Cmp950::operator()(int a, int b)
{
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  if (p) {
    if (q) {
      if (((FnRetBool)((VObj*)p)->vt[30])(p)) {
        if (((FnRetBool)((VObj*)q)->vt[30])(q)) {
          int x = ((FnRetInt)((VObj*)p)->vt[34])(p);
          int y = ((FnRetInt)((VObj*)q)->vt[34])(q);
          if (x == y) return 0;
          return (x <= y) ? 1u : 0xffffffffu;
        }
      }
      if (((FnRetBool)((VObj*)p)->vt[30])(p)) return 0xffffffff;
      return ((FnRetBool)((VObj*)q)->vt[30])(q) != 0;
    }
    return 0xffffffff;
  }
  return q != 0;
}

// @ 0x0066aa40
unsigned Cmp28::operator()(int a, int b)
{
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      long long x = ((FnRetLL)((VObj*)p)->vt[10])(p);
      long long y = ((FnRetLL)((VObj*)*(int**)(b + 0xc))->vt[10])(*(int**)(b + 0xc));
      if (x == y) return 0;
      if (x > y) return 0xffffffff;
      return 1;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// @ 0x0066aad0
unsigned Cmp94::operator()(int a, int b)
{
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  if (p) {
    if (q) {
      long long x = ((FnRetLL)((VObj*)p)->vt[37])(p);
      long long y = ((FnRetLL)((VObj*)q)->vt[37])(q);
      if (x == y) return 0;
      if (x > y) return 0xffffffff;
      return 1;
    }
    return 0xffffffff;
  }
  return q != 0;
}

// @ 0x0066ab90
unsigned Cmp0c::operator()(int a, int b)
{
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      int x = ((FnRetInt)((VObj*)p)->vt[3])(p);
      int y = ((FnRetInt)((VObj*)*(int**)(b + 0xc))->vt[3])(*(int**)(b + 0xc));
      if (x != 0) {
        if (y != 0) return FUN_006b8ea0(x, y, 0);
        return 1;
      }
      return (y != 0) ? -1 : 0;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// @ 0x0066ac10
unsigned Cmp10::operator()(int a, int b)
{
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      int x = ((FnRetInt)((VObj*)p)->vt[4])(p);
      int y = ((FnRetInt)((VObj*)*(int**)(b + 0xc))->vt[4])(*(int**)(b + 0xc));
      if (x != 0) {
        if (y != 0) return FUN_006b8ea0(x, y, 0);
        return 1;
      }
      return (y != 0) ? -1 : 0;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// @ 0x0066aca0
unsigned Cmp70::operator()(int a, int b)
{
  int* p = *(int**)(a + 0xc);
  if (p) {
    if (*(int**)(b + 0xc)) {
      unsigned char x = ((FnRetBool)((VObj*)p)->vt[28])(p);
      unsigned char y = ((FnRetBool)((VObj*)*(int**)(b + 0xc))->vt[28])(*(int**)(b + 0xc));
      if (y == x) return 0;
      return (y < x) ? 0xffffffffu : 1u;
    }
    if (*(int**)(a + 0xc)) return 0xffffffff;
  }
  return *(int**)(b + 0xc) != 0;
}

// @ 0x0066ad10
unsigned Cmp38::operator()(CItem& a, CItem& b)
{
  int* p = a.p;
  if (p) {
    if (b.p) {
      int x = ((FnRetInt)((VObj*)p)->vt[14])(p);
      int y = ((FnRetInt)((VObj*)b.p)->vt[14])(b.p);
      if (x == y) return 0;
      return (x <= y) ? 1u : 0xffffffffu;
    }
    if (a.p) return 0xffffffff;
  }
  return b.p != 0;
}

// @ 0x0066ad70
unsigned Switcher2::Get()
{
  switch (m8) {
  case 0: return 0x7ca87ec2;
  case 1: return 0x3019275;
  case 2: return 0x1d7707e0;
  default: return 0;
  }
}

// @ 0x0066ada0
unsigned CmpAd::operator()(int a, int b)
{
  int* p = Lookup0066((void*)a);
  int* q = Lookup0066((void*)b);
  float* fa = 0;
  float* fb = 0;
  if (p) {
    int* r = (int*)((FnV0)((VObj*)p)->vt[38])(p);
    if (*r == 1) fa = (float*)((FnV0)((VObj*)p)->vt[38])(p) + 1;
  }
  if (q) {
    int* r = (int*)((FnV0)((VObj*)q)->vt[38])(q);
    if (*r == 1) fb = (float*)((FnV0)((VObj*)q)->vt[38])(q) + 1;
  }
  if (!fa) return fb != 0;
  if (fb) {
    float x, y;
    switch (m8) {
    case 0: x = fa[0]; y = fb[0]; break;
    case 1: x = fa[1]; y = fb[1]; break;
    case 2: x = fa[2]; y = fb[2]; break;
    default: return 0;
    }
    if (x == y) return 0;
    if (x <= y) return 1;
  }
  return 0xffffffff;
}

// @ 0x0066afd0
int __cdecl FUN_0066afd0(ObjA* a, ObjB* b)
{
    void* ca = a->c;
    if (ca) {
        if (b->c) {
            unsigned ka = ((FnIntV)VT(ca)[9])(ca);
            unsigned va = *gMapU[ka];
            unsigned kb = ((FnIntV)VT(b->c)[9])(b->c);
            unsigned vb = *gMapU[kb];
            if (va == vb) return 0;
            return (va < vb) ? -1 : 1;
        }
        return -1;
    }
    return b->c != 0;
}

// @ 0x0066b050
void __cdecl FUN_0066b050(void* p)
{
    // Retail refcounts through vtable slot 1 (+0x04, twice: once for the caller's reference and
    // once for the vector's) and finishes with slot 2 (+0x08), which cl turns into a tail call.
    if (p) ((RefObj*)p)->Release();
    if (gVecEnd < gVecCap) {
        void** slot = (void**)gVecEnd;
        gVecEnd = (char*)gVecEnd + 4;
        if (slot) {
            *slot = p;
            if (p) ((RefObj*)p)->Release();
        }
    } else {
        ((Vec*)&gVecObj)->push_back(gVecEnd, p);
    }
    if (p) ((RefObj*)p)->Release2();
}

// @ 0x0066b0c0
void __cdecl FUN_0066b0c0(int* vec)
{
    DoNukeSubtreeStub(gTreeRoot);
    gTreeHead = &gTreeHead;
    gTreeHead2 = &gTreeHead;
    gTreeRoot = 0;
    gB9c = 0;
    gBA0 = 0;
    unsigned n = (unsigned)((vec[1] - vec[0]) >> 2);
    for (unsigned i = 0; i < n; ++i) {
        unsigned key = *(unsigned*)(vec[0] + i * 4);
        *gMapU[key] = i;
    }
}

// @ 0x0066b480
void __cdecl FUN_0066b480()
{
    REGISTER_HANDLER(NEW_SP(SpHandlerN<0>, ()))
    REGISTER_HANDLER(NEW_SP(SpHandlerN<1>, ()))
    REGISTER_HANDLER(NEW_SP(SpHandlerN<2>, ()))
    REGISTER_HANDLER(NEW_SP(SpHandlerN<3>, ()))
    REGISTER_HANDLER(NEW_SP(SpHandlerN<4>, ()))
    REGISTER_HANDLER(NEW_SP(SpHandlerN<5>, ()))
    REGISTER_HANDLER(NEW_SP(SpHandlerN<6>, ()))
    REGISTER_HANDLER(NEW_SP(SpHandlerN<7>, ()))
    REGISTER_HANDLER(NEW_SP(SpHandlerA, (0)))
    REGISTER_HANDLER(NEW_SP(SpHandlerA, (1)))
    REGISTER_HANDLER(NEW_SP(SpHandlerA, (2)))
    REGISTER_HANDLER(NEW_SP(SpHandlerB, (0)))
    REGISTER_HANDLER(NEW_SP(SpHandlerB, (1)))
    REGISTER_HANDLER(NEW_SP(SpHandlerB, (2)))
    REGISTER_HANDLER(NEW_SP(SpHandlerB, (3)))
    REGISTER_HANDLER(NEW_SP(SpHandlerB, (4)))
}
