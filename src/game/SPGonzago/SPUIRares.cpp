// src/game/SPGonzago/SPUIRares.cpp -- migrated from slice(s) s01063a10, s01064990 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIRares.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s01064990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint16_t gEmptyString16[];      // 0x01667bac (?gEmptyString16@eastl@@3PA_WA)
extern void* gVtbl0_0149c0e8[];
extern void* gVtbl1_0149c0cc[];
extern void* gVtbl2_0149c0c4[];
typedef void  (__thiscall *Tc1i)(void*, int);
typedef void  (__thiscall *Tc1p)(void*, void*);
typedef void  (__thiscall *Tc2ii)(void*, int, int);
typedef void  (__thiscall *Tc3p)(void*, void*, int, void*);
typedef int   (__thiscall *TcRi)(void*);
typedef void* (__thiscall *TcRp)(void*);
typedef void* (__thiscall *TcRpi)(void*, int);
#define VTS(o, off) (*(void**)((char*)*(void**)(o) + (off)))
void memcpy_11e0744(void*, const void*, unsigned int);
class RefObj
{
public:
    virtual void AddRef();       // +0x00
    virtual void Release();      // +0x04
    virtual void v08();          // +0x08
    virtual void v0c();          // +0x0c
};
void*  FUN_00b3d3d0();
void*  FUN_00b3d3f0();
void*  PropertyManager_67de30();
void   RemoveHandler_571db0(void*, void*, void*, void*, void*);
void   KillSetiEffects_435ed0(void* a, int id);
void*  GetSystemAT_a206f0();
class cString12;
bool   GetPropertyAsText_6a1360(void* prop, int id, cString12* out);
class SimSlot
{
public:
    char  mPad00[0x5c];
    void* mpE30;        // +0x5c
};
class E30Obj
{
public:
    void Method_e30a60(int v);
};
class CLayout
{
public:
    void* FindWindowByID(int id, int flag);
};
class CSfv
{
public:
    void Shutdown_0082a450();
    void Update_0082a500(int a);
};
class CFeedItem
{
public:
    void  Reserve_666630(int a, int b);
    void  Refresh_6666c0(const wchar_t* text);
    void  FUN_00666660(int a);
    bool  CheckFlag_666680(int a);
    void  Release();
};
class CFeedList
{
public:
    void  FUN_006628d0();
    void  FUN_00662920(int on);
    void* FUN_00662a20(int a);
    void  FUN_00662c10(void* item);
    void  FUN_00663350(int a);
    unsigned FUN_00664600();
    void* FUN_00664610(unsigned idx);
};
class cString12
{
public:
    void* mpBegin;        // +0x00
    void* mpEnd;          // +0x04
    void* mpCap;          // +0x08
    int   mFlag0c;        // +0x0c

    void  Assign_01064d80(const void* begin, const void* end);
    cString12* InsertRange_01064df0(const void* begin, const void* end);
    void  Swap_01065510(cString12* other);
    void  Resize_01065860(uint32_t n);
    void  Assign2_010652d0(const void* begin, const void* end);
    void  Reserve_01065270(uint32_t n);
    void  Init_6b5770(uint32_t a, int b, int c);
    const wchar_t* GetText_6b55c0();
};
class cEmpire;
struct Sub48
{
    void  Init_00e0a390();
    void  FUN_00e0a5c0();
    void  FUN_00e0a400();
    bool  FUN_00e0a780(int a, void* b);
    void* FUN_00e09c90(int a, int b, int c);
    char  mBody[0x70];
};
struct FilterNode
{
    FilterNode* mpNext;    // +0
    void*       mpPrev;    // +4
    void*       mpKey;     // +8
};
class cEmpire
{
public:
    void*       mpVtbl0;        // +0x00
    char        mPad04[4];      // +0x04
    void*       mpVtbl1;        // +0x08
    void*       mpVtbl2;        // +0x0c
    char        mPad10[4];      // +0x10
    int         m14;            // +0x14
    CLayout*    mpLayout;       // +0x18
    char        mPad1c[0x34 - 0x1c];
    FilterNode  mFilterHead;    // +0x34
    char        mb40;           // +0x40
    char        mPad41[3];
    void*       m44;            // +0x44
    Sub48       m48;            // +0x48
    void*       mpSFV;          // +0xb8
    void*       mpMsgServer;    // +0xbc
    void*       mpIdentity;     // +0xc0
    int         mMsgId;         // +0xc4
    int         mC8;            // +0xc8
    int         mCC;            // +0xcc
    CFeedList*  mpFeedList;     // +0xd0
    CFeedItem*  mpSelected;     // +0xd4

    void InitBase_00e18bb0();
    void OnWinProcAdd_010829f0(int arg);
    void BaseDestroy_00e18810();
    void BaseDestroy2_00e18980();
    void Show_00e18860(int arg);
    void SetText_00e18890(void* text);

    cEmpire();
    ~cEmpire();

    void Destroy_01064990();
    void OnWinProcAdd_01064a00(int arg);
    void PopulateLeft_01064b60();
    void Init_01064fd0();
    void PopulateFeed_010655a0();
    void Show_01065900(int arg);
};
class cEmpireB
{
public:
    void* mpVtblB;        // this+0x00 = outer+0x08
    char  mPad04[0x38];   // this+0x04 .. this+0x3b
    void* m44;            // this+0x3c = outer+0x44
    bool DefineLeftScroll_01064f00(int id, void* ev);
};
static inline cEmpire* empireFromB(void* p) { return (cEmpire*)((char*)p - 0x08); }
struct CEvent
{
    void*    mpObj;     // +0
    void*    mpUnk4;    // +4
    uint32_t mId;       // +8
    char     pad0c[4];
    void*    mpData;    // +0x10
};
// ---- items of slice s01064990 end

// ---- items of slice s01063a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
void  __cdecl FUN_00e0a640(void* self);                // 0x00e0a640
void  __cdecl FUN_00e0a4c0(void* self, void* a);       // 0x00e0a4c0
void  __cdecl FUN_00e18a30(void* self);                // 0x00e18a30
void  __cdecl FUN_00e186d0(void* self, void* a, void* b, void* c, void* d);  // 0x00e186d0
void* __cdecl FUN_008105b0(void);                     // 0x008105b0 cSPUILayout::FindWindowByID (2-arg thiscall)
void  __cdecl FUN_00662920(void* self, int b);         // 0x00662920
void  __cdecl FUN_00663350(void* self, void* a);       // 0x00663350
void  __cdecl FUN_00663860(void* a, void* b, void* c, int d, void* e);  // 0x00663860
void* __cdecl FUN_00f473a0(u32 size, const char* name, int, int, int, int);  // operator new
void* __cdecl FUN_0082a040(void* self);                // 0x0082a040 ScrollFrameVertical ctor
u8    __cdecl FUN_0082a140(void* self, int a, u32 b, u32 c);  // 0x0082a140 SFV::Create
float __cdecl FUN_0082a4e0(void* self);                // 0x0082a4e0 SFV::GetScrollOffset
void* __cdecl FUN_00663040(void* self);                // 0x00663040 cSPUIFeedList ctor
void  __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e);  // 0x00571db0 RemoveHandler
// ---- items of slice s01063a10 end

// @ 0x010646f0
void __fastcall FUN_010646f0(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  if (*(u8*)(p + 0x40) == 0) return;

  void* handler = *(void**)(p + 0xbc);
  if (handler != 0) {
    *(void**)(p + 0xbc) = 0;
    FUN_00571db0(handler, *(void**)(p + 0xc0), *(void**)(p + 0xc4),
                 *(void**)(p + 0xc8), *(void**)(p + 0xcc));
  }
  ((void(__thiscall*)(void*, int))FUN_00662920)(*(void**)(p + 0xd0), 0);
  ((void(__thiscall*)(void*))FUN_00e0a640)(p + 0x48);
  *(u8*)(p + 0x40) = 0;
  ((void(__thiscall*)(void*))FUN_00e18a30)(p);
}

// @ 0x01064760
void __fastcall FUN_01064760(void* self, void* /*edx*/, void* a2, void* a3, void* a4, void* a5)
{
  char* p = (char*)self;
  ((void(__thiscall*)(void*, void*, void*, void*, void*))FUN_00e186d0)(
      p, a2, a3, a4, a5);
  *(u8*)(p + 0x40) = 0;
  *(u32*)(p + 0x44) = 0;

  u32 local_10 = 0;
  float local_c = 0.0f;
  u32 local_8 = 0;
  (void)local_c; (void)local_8;

  void* w = ((void* (__thiscall*)(void*, u32, int, void*))FUN_008105b0)(
      *(void**)(p + 0x18), 0x5f00928, 1, &local_10);
  ((void(__thiscall*)(void*, void*))FUN_00e0a4c0)(p + 0x48, w);

  char* sfv = (char*)FUN_00f473a0(0x48, "UI/cSPUIScrollFrameVertical", 0, 0, 0, 0);
  sfv = sfv ? (char*)FUN_0082a040(sfv) : 0;
  char* oldS = *(char**)(p + 0xb8);
  if (sfv != oldS) {
    if (sfv != 0) (*(void(__thiscall**)(char*))(*(void***)sfv + 0))(sfv);
    *(char**)(p + 0xb8) = sfv;
    if (oldS != 0) (*(void(__thiscall**)(char*))(*(void***)oldS + 1))(oldS);
  }

  ((u8 (__thiscall*)(void*, u32, int, int))FUN_0082a140)(
      *(void**)(p + 0xb8), 0xaef7d6ba, 1, 0);
  void* win = ((void* (__thiscall*)(void*, u32, int, void*))FUN_008105b0)(
      *(void**)(p + 0x18), 0x51a37b9, 1, &local_10);
  char* wc = (char*)win;
  if (wc != 0) {
    (*(void(__thiscall**)(char*))(*(void***)wc + 0))(wc);
    char* sfv2 = *(char**)(p + 0xb8);
    char* own = *(char**)(sfv2 + 0x10);
    char* other = *(char**)(sfv2 + 0x18);
    char* sub = (char*)(*(void* (__thiscall**)(char*))(*(void***)wc + 0x10 / 4))(wc);
    (*(void(__thiscall**)(char*, char*))(*(void***)sub + 0xd8 / 4))(sub, own);
    float* r = (float*)(*(void* (__thiscall**)(char*))(*(void***)wc + 0x38 / 4))(wc);
    local_10 = *(u32*)&r[0];
    local_c = r[2];
    local_8 = *(u32*)&r[3];
    float off = FUN_0082a4e0(*(void**)(p + 0xb8));
    local_c += off;
    (*(void(__thiscall**)(char*, void*))(*(void***)own + 0x6c / 4))(own, &local_10);
    (*(void(__thiscall**)(char*, char*))(*(void***)sub + 0xdc / 4))(sub, wc);
    (*(void(__thiscall**)(char*, char*))(*(void***)(char*)a2 + 0xd8 / 4))((char*)a2, wc);
    (*(void(__thiscall**)(char*, int, int))(*(void***)wc + 0x70 / 4))(wc, 0, 0);
    (void)other;
  }

  char* fl = (char*)FUN_00f473a0(0x6c, "UI/cSPUIFeedList", 0, 0, 0, 0);
  fl = fl ? (char*)FUN_00663040(fl) : 0;
  char* oldF = *(char**)(p + 0xd0);
  if (fl != oldF) {
    if (fl != 0) (*(void(__thiscall**)(char*))(*(void***)fl + 0))(fl);
    *(char**)(p + 0xd0) = fl;
    if (oldF != 0) (*(void(__thiscall**)(char*))(*(void***)oldF + 1))(oldF);
  }

  char* fl2 = *(char**)(p + 0xd0);
  void* ww = ((void* (__thiscall*)(void*, u32, int, void*))FUN_008105b0)(
      *(void**)(p + 0x18), 0x5f00660, 1, &local_10);
  ((void(__thiscall*)(void*, u32, int, int))FUN_00663860)(fl2, 0xee896903, 1, 0);
  (void)ww;
  ((void(__thiscall*)(void*, int))FUN_00663350)(fl2, 0);
  ((void(__thiscall*)(void*, int))FUN_00662920)(fl2, 0);
  if (wc != 0) {
    (*(void(__thiscall**)(char*))(*(void***)wc + 1))(wc);
  }
}

// @ 0x01064990
void cEmpire::Destroy_01064990()
{
    if (mpFeedList != 0)
    {
        mpFeedList->FUN_006628d0();
        if (mpFeedList != 0)
        {
            CFeedList* p = mpFeedList;
            mpFeedList = 0;
            ((RefObj*)p)->Release();
        }
    }
    m48.FUN_00e0a5c0();
    if (mpSFV != 0)
    {
        ((CSfv*)mpSFV)->Shutdown_0082a450();
        if (mpSFV != 0)
        {
            void* p = mpSFV;
            mpSFV = 0;
            ((RefObj*)p)->Release();
        }
    }
    BaseDestroy_00e18810();
}

// @ 0x01064a00
void cEmpire::OnWinProcAdd_01064a00(int arg)
{
    OnWinProcAdd_010829f0(arg);
    if (mb40 != 0)
        mpFeedList->FUN_00663350(arg);
}

// @ 0x01064a30
cEmpire::cEmpire()
{
    InitBase_00e18bb0();
    mpVtbl0 = gVtbl0_0149c0e8;
    mpVtbl1 = gVtbl1_0149c0cc;
    mpVtbl2 = gVtbl2_0149c0c4;
    mb40 = 0;
    m44 = 0;
    m48.Init_00e0a390();
    mpSFV = 0;
    mpMsgServer = 0;
    mpIdentity = 0;
    mMsgId = 0;
    mC8 = 0;
    mCC = 0;
    mpFeedList = 0;
    mpSelected = 0;
}

// @ 0x01064ac0
cEmpire::~cEmpire()
{
    mpVtbl0 = gVtbl0_0149c0e8;
    mpVtbl1 = gVtbl1_0149c0cc;
    mpVtbl2 = gVtbl2_0149c0c4;
    _ReadWriteBarrier();
    if (mpSelected != 0)
        ((RefObj*)mpSelected)->Release();
    if (mpFeedList != 0)
        ((RefObj*)mpFeedList)->Release();
    if (mpMsgServer != 0)
    {
        void* srv = mpMsgServer;
        void* a = mpIdentity;
        void* b = (void*)mMsgId;
        void* c = (void*)mC8;
        void* d = (void*)mCC;
        mpMsgServer = 0;
        RemoveHandler_571db0(srv, a, b, c, d);
    }
    if (mpSFV != 0)
        ((RefObj*)mpSFV)->Release();
    m48.FUN_00e0a400();
    BaseDestroy2_00e18980();
}

// @ 0x01064b60
void cEmpire::PopulateLeft_01064b60()
{
    void* res = 0;

    if (m44 != 0)
    {
        FUN_00b3d3d0();
        void* pm = PropertyManager_67de30();
        if (res != 0)
        {
            void* old = res;
            res = 0;
            ((RefObj*)old)->Release();
        }
        ((Tc3p)VTS(pm, 0x2c))(pm, m44, 0x34d97fa, &res);
    }

    void* w1 = mpLayout->FindWindowByID(0x51a37b8, 1);
    cString12 s1;
    bool ok1 = GetPropertyAsText_6a1360(res, 0x3068d95d, &s1);
    if (ok1)
        ((Tc1p)VTS(w1, 0x80))(w1, (void*)s1.GetText_6b55c0());
    ((Tc2ii)VTS(w1, 0x7c))(w1, 1, ok1 ? 1 : 0);

    void* w2 = mpLayout->FindWindowByID(0x51a37b9, 1);
    cString12 s2;
    bool ok2 = GetPropertyAsText_6a1360(res, 0x4cad19b, &s2);
    if (ok2)
    {
        ((Tc2ii)VTS(w2, 0x7c))(w2, 1, 1);
        ((Tc1p)VTS(w2, 0x80))(w2, (void*)s2.GetText_6b55c0());
        void* x = ((TcRpi)VTS(w2, 0x0c))(w2, 0xf15f4bd);
        ((Tc1i)VTS(x, 0x14))(x, 1);
    }
    else
    {
        ((Tc2ii)VTS(w2, 0x7c))(w2, 1, 0);
    }

    ((Tc1i)VTS(mpSFV, 0))(mpSFV, 1);
}

// @ 0x01064d80
void cString12::Assign_01064d80(const void* begin, const void* end)
{
    int n = ((int)end - (int)begin) >> 1;
    uint32_t cap = (uint32_t)(n + 1);
    if (cap > 1)
    {
        mpBegin = 0;
        mpEnd   = 0;
        mpCap   = (void*)(cap * 2);
    }
    else
    {
        mpBegin = gEmptyString16;
        mpEnd   = gEmptyString16;
        mpCap   = gEmptyString16 + 1;
    }
    void* dst = mpBegin;
    memcpy_11e0744(dst, begin, (unsigned int)(n * 2));
    uint16_t* p = (uint16_t*)((char*)dst + n * 2);
    mpEnd = p;
    *p = 0;
}

// @ 0x01064df0
cString12* cString12::InsertRange_01064df0(const void* begin, const void* end)
{
    if (begin != end)
    {
        char* b = (char*)begin;
        char* e = (char*)end;
        char* src = (char*)mpBegin;
        int added = ((int)e - (int)b) >> 1;
        unsigned capLeft = (unsigned)(((int)mpCap - (int)src) >> 1) - 1;
        unsigned need = (unsigned)(((int)mpEnd - (int)src) >> 1) + (unsigned)added;

        if (capLeft < need)
        {
            unsigned newCap = (capLeft < 9) ? 8u : capLeft * 2;
            unsigned finalCap = (newCap < need) ? need : newCap;
            char* tail = (char*)(((int)mpEnd - (int)src) >> 1);
            memcpy_11e0744(0, src, (unsigned)(int)tail);
            memcpy_11e0744(tail, b, (unsigned)(added * 2));
            char* endPos = tail + added * 2;
            *(uint16_t*)endPos = 0;
            mpBegin = 0;
            mpEnd = endPos;
            mpCap = (void*)(finalCap * 2 + 2);
            return this;
        }

        memcpy_11e0744((char*)mpEnd + 2, b + 2,
                       (unsigned)(((int)e - ((int)b + 2)) >> 1) * 2);
        *(uint16_t*)((char*)mpEnd + added * 2) = 0;
        *(uint16_t*)mpEnd = *(uint16_t*)b;
        mpEnd = (char*)mpEnd + added * 2;
    }
    return this;
}

// @ 0x01064f00
bool cEmpireB::DefineLeftScroll_01064f00(int id, void* ev)
{
    CEvent* e = (CEvent*)ev;

    if (e->mId == 0x1b)
    {
        void* obj = e->mpObj;
        int t = ((TcRi)VTS(obj, 0x20))(obj);
        if (t == 0x51aff90)
        {
            void* sys = GetSystemAT_a206f0();
            if (sys != 0)
                sys = ((TcRp)VTS(sys, 0x20))(sys);
            KillSetiEffects_435ed0(sys, 0x8821b509);
            return false;
        }
    }
    else if (e->mId == 0x287259f6)
    {
        void* obj = e->mpObj;
        int t = ((TcRi)VTS(obj, 0x20))(obj);
        if (t == 0x51aff90)
        {
            int v = ((TcRi)VTS(obj, 0x1c))(obj);
            m44 = (void*)v;
            void* sys = GetSystemAT_a206f0();
            if (sys != 0)
                sys = ((TcRp)VTS(sys, 0x20))(sys);
            KillSetiEffects_435ed0(sys, 0x806318da);
            empireFromB(this)->PopulateLeft_01064b60();
            void* sim = FUN_00b3d3f0();
            ((E30Obj*)((SimSlot*)sim)->mpE30)->Method_e30a60(v);
        }
    }
    return false;
}
