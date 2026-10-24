// Slice s01064990: SP::cSPUIRares (empire UI), the eastl wide-string
// helpers it uses, and a few small UI / space helpers.
// /O2 /Ob1 /arch:SSE module.
#include "types.h"
#include <math.h>
#include <intrin.h>

// ---------------------------------------------------------------- utilities
typedef void  (__thiscall *Tc0)(void*);
typedef void  (__thiscall *Tc1i)(void*, int);
typedef void  (__thiscall *Tc1p)(void*, void*);
typedef void  (__thiscall *Tc2ii)(void*, int, int);
typedef void  (__thiscall *Tc2ip)(void*, int, void*);
typedef void  (__thiscall *Tc2pi)(void*, void*, int);
typedef void  (__thiscall *Tc3iii)(void*, int, int, int);
typedef void  (__thiscall *Tc3p)(void*, void*, int, void*);
typedef void  (__thiscall *Tc5)(void*, void*, void*, void*, void*);
typedef int   (__thiscall *TcRi)(void*);
typedef void* (__thiscall *TcRp)(void*);
typedef void* (__thiscall *TcRpi)(void*, int);

#define VTS(o, off) (*(void**)((char*)*(void**)(o) + (off)))

void memcpy_11e0744(void*, const void*, unsigned int);

// ref-counted object: slot +0 = AddRef, slot +4 = Release.
class RefObj
{
public:
    virtual void AddRef();       // +0x00
    virtual void Release();      // +0x04
    virtual void v08();          // +0x08
    virtual void v0c();          // +0x0c
};

// ------------------------------------------------------------------- globals
extern uint16_t gEmptyString16[];      // 0x01667bac (?gEmptyString16@eastl@@3PA_WA)
extern float    gBakePhase;            // 0x016e2830
extern uint32_t gBakePhaseInit;        // 0x016e2834
extern float    gBakePhaseSpeed;       // 0x015b90e0

// --------------------------------------------------------------- extern APIs
void*  FUN_00b3d3d0();
void*  FUN_00b3d3f0();
void*  PropertyManager_67de30();
void*  MessageServer_67dcc0();
void*  __stdcall TM_a_b3d430(int a);
void*  __stdcall TM_b_b3d430(int a, int b);

class CTM
{
public:
    int  Max_bbc670();
    bool A_bbcda0();
    bool B_bbce00();
};
void   RemoveHandler_571db0(void*, void*, void*, void*, void*);
void   KillSetiEffects_435ed0(void* a, int id);
void*  GetSystemAT_a206f0();
class cString12;
bool   GetPropertyAsText_6a1360(void* prop, int id, cString12* out);
int    Format_010654f0(cString12* out, const wchar_t* fmt, int a, int b);

// Objects returned by the property manager / simulator.
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

// ---------------------------------------------------------------- layout/UI
class CLayout
{
public:
    void* FindWindowByID(int id, int flag);
};
class CGlobalUI
{
public:
    void* FindWindowByID(int id);
};

class CSfv
{
public:
    void Shutdown_0082a450();
    void Update_0082a500(int a);
};

// -------------------------------------------------------------- feed objects
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

// ------------------------------------------------------------- string (wide)
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

// ------------------------------------------------------------------- cEmpire
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

extern void* gVtbl0_0149c0e8[];
extern void* gVtbl1_0149c0cc[];
extern void* gVtbl2_0149c0c4[];

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

// Object views seen from the second (+0x08) and third (+0x0c) interface vptrs.
class cEmpireB
{
public:
    void* mpVtblB;        // this+0x00 = outer+0x08
    char  mPad04[0x38];   // this+0x04 .. this+0x3b
    void* m44;            // this+0x3c = outer+0x44
    bool DefineLeftScroll_01064f00(int id, void* ev);
};

class cEmpireC
{
public:
    void* mpVtblC;        // this+0x00 = outer+0x0c
    char  mPad04[0x34];   // this+0x04 .. this+0x37
    void* m44;            // this+0x38 = outer+0x44
    char  mPad3c[0x8c];   // this+0x3c .. this+0xc7
    CFeedItem* mpSelected;// this+0xc8 = outer+0xd4
    bool Ret_01065360(int id, void* ev);
    bool BaseHandler_00e18600(int a, void* b);
};

// Base-class pointer adjustments for the two non-primary interface vptrs.
static inline cEmpire* empireFromB(void* p) { return (cEmpire*)((char*)p - 0x08); }
static inline cEmpire* empireFromC(void* p) { return (cEmpire*)((char*)p - 0x0c); }


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
struct CEvent
{
    void*    mpObj;     // +0
    void*    mpUnk4;    // +4
    uint32_t mId;       // +8
    char     pad0c[4];
    void*    mpData;    // +0x10
};

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

// @ 0x01064fd0
void cEmpire::Init_01064fd0()
{
    if (mpSelected == 0)
        return;

    bool differ = (*(int*)((char*)mpSelected + 0x17c) != 0x56624a99);

    void* w1 = mpLayout->FindWindowByID(0x6032b88, 1);
    ((Tc2ii)VTS(w1, 0x7c))(w1, 1, (int)mpLayout);

    void* w2 = mpLayout->FindWindowByID(0x6032bd8, 1);
    ((Tc2ii)VTS(w2, 0x7c))(w2, 1, differ ? 0 : 1);

    if (!differ)
        return;

    FUN_00b3d3d0();
    mpFeedList->FUN_00662920(0);
    (void)0;

    if (!m48.FUN_00e0a780(0x16e2224, 0))
        return;

    PopulateLeft_01064b60();
}

// @ 0x01065360
bool cEmpireC::Ret_01065360(int id, void* ev)
{
    if (id == (int)0xb3d53f95)
    {
        int v = *(int*)((char*)mpSelected + 0x17c);
        void* sim = FUN_00b3d3f0();
        ((E30Obj*)((SimSlot*)sim)->mpE30)->Method_e30a60(v);

        void* nw = *(void**)((char*)ev + 0x10);
        void* old = mpSelected;
        if (nw != old)
        {
            if (nw != 0)
                ((RefObj*)nw)->AddRef();
            mpSelected = (CFeedItem*)nw;
            if (old != 0)
                ((RefObj*)old)->Release();
        }
        m44 = 0;
        empireFromC(this)->Init_01064fd0();
        return true;
    }
    return BaseHandler_00e18600(id, ev);
}

// @ 0x01065510
void cString12::Swap_01065510(cString12* other)
{
    if (&mFlag0c == &other->mFlag0c)
    {
        void* a = mpBegin; mpBegin = other->mpBegin; other->mpBegin = a;
        _ReadWriteBarrier();
        void* b = mpEnd;
        _ReadWriteBarrier();
        mpEnd   = other->mpEnd;   other->mpEnd   = b;
        _ReadWriteBarrier();
        void* c = mpCap;   mpCap   = other->mpCap;   other->mpCap   = c;
        return;
    }

    cString12 tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCap = 0;
    tmp.Assign_01064d80(mpBegin, mpEnd);
    if (other != this)
        Assign2_010652d0(other->mpBegin, other->mpEnd);
    if (&tmp != other)
        other->Assign2_010652d0(tmp.mpBegin, tmp.mpEnd);
}

// @ 0x010655a0
void cEmpire::PopulateFeed_010655a0()
{
    mpFeedList->FUN_00662920(1);
    void* list = mpFeedList->FUN_00662a20(0);
    if (list == 0)
        return;

    FUN_00b3d3d0();
    unsigned count = mpFeedList->FUN_00664600();
    for (unsigned i = 0; i < count; ++i)
    {
        CFeedItem* item = (CFeedItem*)mpFeedList->FUN_00664610(i);
        item->Reserve_666630(0, 0);
    }
    if (mpSelected != 0)
        mpFeedList->FUN_00662c10(mpSelected);
}

// @ 0x01065860
void cString12::Resize_01065860(uint32_t n)
{
    if (n != 0xffffffffu)
    {
        char* src = (char*)mpBegin;
        unsigned have = (unsigned)(((int)mpEnd - (int)src) >> 1);
        if (n > have)
        {
            char* dst = (char*)(have * 2);
            memcpy_11e0744(0, src, (unsigned)(int)dst);
            *(uint16_t*)dst = 0;
            mpEnd = dst;
            mpBegin = 0;
            mpCap = (void*)(n * 2);
            return;
        }
    }
    unsigned have = (unsigned)(((int)mpEnd - (int)mpBegin) >> 1);
    if (n < have)
        Reserve_01065270(n);

    cString12 tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCap = 0;
    tmp.Assign_01064d80(mpBegin, mpEnd);
    Swap_01065510(&tmp);
}

// @ 0x01065900
void cEmpire::Show_01065900(int arg)
{
    if (mb40 != 0)
        return;

    Show_00e18860(arg);

    cString12 s;
    s.Init_6b5770(0xf5e156f8, 0x6038566, 0);
    SetText_00e18890((void*)s.GetText_6b55c0());

    mb40 = 1;
    PopulateFeed_010655a0();
    Init_01064fd0();
    mpFeedList->FUN_00662920(1);

    void* srv = MessageServer_67dcc0();
    mpMsgServer = srv;
    mpIdentity = (void*)((char*)this + 0x0c);
    mMsgId = 0x1400244;
    mC8 = 1;
    mCC = 0;
    if (srv != 0 && mpIdentity != 0)
        ((Tc2pi)VTS(srv, 0x24))(srv, mpIdentity, 0xb3d53f95);
}

// @ 0x010659c0
uint32_t convertStarMapButtonToFilter(uint32_t id)
{
    uint32_t v = id;
    switch (v)
    {
    case 0x2e1b6f8: return 0;
    case 0x2e1b708: return 1;
    case 0x2e1b720: return 5;
    case 0x2e1b72c: return 4;
    case 0x2e1b73c: return 3;
    case 0x2e1cbd7: return 2;
    }
    return id;
}

// @ 0x01065a50
#pragma intrinsic(cos, sin)
void BuildBakeOffset(float radius, float angle, float* out)
{
    if ((gBakePhaseInit & 1) == 0)
    {
        gBakePhase = gBakePhaseSpeed * 0.0055555557f;
        gBakePhaseInit |= 1;
    }
    float s = radius * 0.05f;
    float a = gBakePhase * angle;
    out[2] = 0.0f;
    out[0] = -(float)(cos(a) * s);
    out[1] = -(float)(sin(a) * s);
}

// --------------------------------------------------------------- cSPUISpace
class cSPUISpace
{
public:
    char       mPad00[0x224];
    CGlobalUI* mpGlobalUI;        // +0x224

    void ShowBakeTimeSplash_01065ab0();
    void HideBakeTimeSplash_01065af0();
    bool IsBakeSplashShown_01065b30();
};

// @ 0x01065ab0
void cSPUISpace::ShowBakeTimeSplash_01065ab0()
{
    void* w = mpGlobalUI->FindWindowByID(0x54fc370);
    if (w != 0)
        ((Tc2ii)VTS(w, 0x7c))(w, 1, 1);
    void* srv = MessageServer_67dcc0();
    ((Tc3iii)VTS(srv, 0x14))(srv, 0x604d856, 0, 0);
}

// @ 0x01065af0
void cSPUISpace::HideBakeTimeSplash_01065af0()
{
    void* w = mpGlobalUI->FindWindowByID(0x54fc370);
    if (w != 0)
        ((Tc2ii)VTS(w, 0x7c))(w, 1, 0);
    void* srv = MessageServer_67dcc0();
    ((Tc3iii)VTS(srv, 0x14))(srv, 0x604d85d, 0, 0);
}

// @ 0x01065b30
bool cSPUISpace::IsBakeSplashShown_01065b30()
{
    bool shown = false;
    void* w = mpGlobalUI->FindWindowByID(0x54fc370);
    if (w != 0)
        shown = (((TcRi)VTS(w, 0x28))(w) & 1);
    return shown;
}

// @ 0x01065b60
void __stdcall HideStarPlanet_01065b60(void* layout, uint32_t n)
{
    if (n < 5)
    {
        void* w = ((CLayout*)layout)->FindWindowByID((int)((n + 0x684bc0) * 16), 1);
        if (w != 0)
            return ((Tc2ii)VTS(w, 0x7c))(w, 1, 0);
    }
}

// @ 0x01065ba0
class CTerrainIconOwner
{
public:
    char mPad00[0x544];
    int  m544;      // +0x544
    int  m548;      // +0x548
    int  m54c;      // +0x54c
    int  m550;      // +0x550
    int  m554;      // +0x554

    int GetTerrainIcon_01065ba0(int n);
};

int CTerrainIconOwner::GetTerrainIcon_01065ba0(int n)
{
    void* tm = TM_a_b3d430(0);
    int max = ((CTM*)tm)->Max_bbc670();
    if (n > max)
        return m544;

    void* tm2 = TM_b_b3d430(n, 0);
    if (((CTM*)tm2)->A_bbcda0())
        return m554;

    void* tm3 = TM_b_b3d430(n, 0);
    if (((CTM*)tm3)->B_bbce00())
        return m550;

    if (n != 1)
    {
        void* tm4 = TM_b_b3d430(n - 1, 0);
        if (!((CTM*)tm4)->A_bbcda0())
            return m548;
    }
    return m54c;
}
