// s00ae73e0 targets: combat/tool manager helpers (names are working names).
#include "types.h"

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

// ---------------------------------------------------------------------------
// 00ae7ce0: game-data extraction callback (naked-style 3 dword args by value).
struct GDVCallbackArg {                     // the object whose +0x58 field is a type id
    uint32_t pad00;
    uint32_t pad54[0x58 / 4 - 1];
    uint32_t mType58;                       // +0x58
};

struct GDVArgObj {                          // arg consumed by FUN_00bf0f40
    uint32_t mWord0;                        // +0x00
    int Get();                              // 0xbf0f40 (__thiscall)
};

static uint32_t* const g_nullArgKinds = (uint32_t*)0x0145bdcc;   // 3 game-mode tags cycled by index

int FUN_00bef920(int v);                    // 0xbef920 (cdecl)

// @ 0x00ae7ce0
int __stdcall FUN_00ae7ce0(GDVCallbackArg* o, uint32_t p2, uint32_t idx)
{
    if (o) {
        switch (o->mType58) {
        case 0:  return 0x52524157;   // "WARR"
        case 1:  return 0x44415254;   // "TRAD"
        case 2:  return 0x45494353;   // "SICE"
        case 3:  return 0x4d414853;   // "SHAM"
        case 4:  return 0x44524142;   // "BARD"
        case 5:  return 0x4c41455a;   // "ZEAL"
        case 6:  return 0x4c504944;   // "DIPL"
        case 7:  return 0x4c4f4345;   // "ECOL"
        case 8:  return 0x424f5247;   // "GROB"
        case 9: case 10: case 11: case 12: case 13:
        case 14: case 15: case 16: case 17: case 18:
            return (int)g_nullArgKinds[idx % 3];
        default:
            return 0;
        }
    }
    switch (FUN_00bef920(((GDVArgObj*)p2)->Get())) {
    case 0:  return 0x4d594c50;   // "PLYM"
    case 1:  return 0x52594c50;   // "PLYR"
    default: return 0x45594c50;   // "PLYE"
    }
}

// ---------------------------------------------------------------------------
// 00ae7de0 / 00ae7df0: the +0x94 "selected index" accessors.

// @ 0x00ae7de0
struct SelIdxObjA {
    int pad00[0x94 / 4];
    int mSel94;                            // +0x94
    void Reset();
    void Set(int v);
};
void SelIdxObjA::Reset() { mSel94 = -1; }

// @ 0x00ae7df0
void SelIdxObjA::Set(int v)
{
    if (mSel94 != v)
        mSel94 = v;
}

// ---------------------------------------------------------------------------
// 00ae7e10: swap the object pair for slot `slot`.
struct Comp {                               // cAnimatingCreature-like
    void Attach(int flag);                  // 0xa02ab0 (__thiscall, 1 arg)
    bool FUN_00a02b20();                    // 0xa02b20 (__thiscall)
};

struct SlotHolder {
    uint32_t pad00[0x2c / 4];
    Comp*   mpCreature[2];                  // +0x2c (index 0) / +0x30 (index 1)
    uint32_t pad34[2];
    void*   mpPrimary[2];                   // +0x3c (index 0) / +0x40 (index 1)
    void*   mpSecondary[2];                 // +0x44 (index 0) / +0x48 (index 1)
    void FUN_00ae7e10(void* a, void* b, int slot, char flag);  // 0x00ae7e10
};

struct RenderObj {                          // object stored in the mpPrimary/mpSecondary slots
    virtual void          v00();            // +0x00
    virtual void          Destroy(int keep); // +0x04
    virtual void*         SetModel(void* model, int flags);  // +0x08
    virtual void          SetRef(void* ref, int on);         // +0x0c
    virtual void          Slot10(void* ref, int on);         // +0x10
    virtual void          Slot14(void* p);  // +0x14
    virtual void          Slot18(void* p);  // +0x18
    virtual void          Slot1c(void* p);  // +0x1c
    virtual void          Slot20(void* p, int on);           // +0x20
    virtual void          Slot24(void* p, float v);          // +0x24
};

// @ 0x00ae7e10
void SlotHolder::FUN_00ae7e10(void* a, void* b, int slot, char flag)
{
    RenderObj* ro = (RenderObj*)mpCreature[slot];
    if (!ro)
        return;
    if (!flag) {
        void* p = mpSecondary[slot];
        if (p && !((Comp*)p)->FUN_00a02b20())
            return;
    }
    ((Comp*)mpCreature[slot])->Attach(0);
    if (a) {
        void* v = ro->SetModel(a, 0);
        mpPrimary[slot] = v;
        ro->SetRef(v, 1);
        ro->Slot18(mpPrimary[slot]);
    }
    if (b) {
        void* v = ro->SetModel(b, 0);
        mpSecondary[slot] = v;
        ro->SetRef(v, 0);
        ro->Slot10(v, 1);
        ro->Slot18(mpSecondary[slot]);
        ro->Slot20(mpSecondary[slot], 1);
        ro->Slot24(mpSecondary[slot], 0.0f);
    }
}

// ---------------------------------------------------------------------------
// 00ae7f00 / 00ae7f90: cGonzagoSubsystem-derived construction / destruction.
struct cGonzagoSubsystem {
    void ctor();                            // 0xb5b960
    void dtor();                            // 0xb5b9a0
};

struct RefCountTemplate {                   // second vtable base
    virtual void v00();                     // +0x00
    virtual int  Release();                 // +0x04
};
struct RefCounted {
    RefCountTemplate mRefBase;              // +0x04 vptr
};

struct cAnimatingCreature {
    int  Release();                         // 0xa05270
};
struct cSPUIModelsAndEffectsRenderer {
    int  Release();                         // 0x80df80
};

struct eGameMode {
    void** mpVtbl;                          // +0x00
    uint32_t mWord4;                        // +0x04
    uint32_t pad08[0x40 / 4 - 2];
    int    mRefCount40;                     // +0x40
};

struct eGameModeHolder {
    eGameMode* mpMode;                      // +0x00
};

struct Gonzago {
    virtual void v00();                     // +0x00 (base cIGonzagoSubsystem vptr)
    Gonzago* Init();                        // 0x00ae7f00
    Gonzago* Destroy();                     // 0x00ae7f90
    void InitCommScreen();                  // 0x00ae8070
    RefCountTemplate mRefBase;              // +0x04 vptr (RefCountTemplate<int> vtable)
    uint32_t pad08;                         // +0x08
    eGameModeHolder mObj[2];                // +0x0c, +0x10  (mpMode pointers)
    uint32_t pad14;                         // +0x14
    void*   mpA18;                          // +0x18 (uninitialised in Init)
    cSPUIModelsAndEffectsRenderer* mpA1c;   // +0x1c
    cSPUIModelsAndEffectsRenderer* mpA20;   // +0x20
    void*   mpA24;                          // +0x24
    void*   mpA28;                          // +0x28
    cAnimatingCreature* mpA2c;              // +0x2c
    cAnimatingCreature* mpA30;              // +0x30
    eGameModeHolder mObjs[2];               // +0x34, +0x38  (mpMode pointers)
    eGameModeHolder mObj3c;                 // +0x3c
    eGameModeHolder mObj40;                 // +0x40
    eGameModeHolder mObj44;                 // +0x44
    eGameModeHolder mObj48;                 // +0x48
    uint32_t pad4c[12];                     // +0x4c..+0x7b
    uint8_t mA7c;                           // +0x7c
    uint8_t mA7d;                           // +0x7d
    uint16_t pad7e;                         // +0x7e
    RefCounted* mpA80;                      // +0x80
    RefCounted* mpA84;                      // +0x84
    float   mA88;                           // +0x88
    float   mA8c;                           // +0x8c
    uint8_t mA90;                           // +0x90
    uint8_t mA91;                           // +0x91
    uint8_t mA92;                           // +0x92
    uint8_t pad93[1];
    int     mSel94;                         // +0x94
};

void cGonzagoSubsystem_ctor2(cGonzagoSubsystem* self);   // 0xb5b960
extern "C" void __stdcall cGonzagoSubsystem_ctor2_sc(void* self);  // 0xb5b960

// @ 0x00ae7f00
Gonzago* Gonzago::Init()
{
    ((cGonzagoSubsystem*)this)->ctor();
    *(void**)this = (void*)0x0145bde0;
    *(void**)((char*)this + 4) = (void*)0x0145bdd8;
    mpA1c = 0;
    mpA20 = 0;
    mpA24 = 0;
    mpA28 = 0;
    mpA2c = 0;
    mpA30 = 0;
    mObjs[0].mpMode = 0;
    mObjs[1].mpMode = 0;
    mpA80 = 0;
    mpA84 = 0;
    mA92 = 0;
    mSel94 = -1;
    return this;
}

// @ 0x00ae7f90
Gonzago* Gonzago::Destroy()
{
    *(void**)this = (void*)0x0145bde0;
    *(void**)((char*)this + 4) = (void*)0x0145bdd8;

    for (int i = 1; i >= 0; --i) {          // +0x0c, +0x10
        eGameMode* m = mObj[i].mpMode;
        if (m)
            ((RefCountTemplate*)m)->Release();
    }
    for (int i = 1; i >= 0; --i) {          // +0x34, +0x38
        eGameMode* m = mObjs[i].mpMode;
        if (m) {
            if (m->mRefCount40 > 1) {
                --m->mRefCount40;
            } else {
                ((void(*)(eGameMode*, uint32_t))m->mpVtbl[0x170 / 4])(m, m->mWord4 >> 31);
            }
        }
    }
    for (int i = 1; i >= 0; --i) {          // +0x2c, +0x30
        cAnimatingCreature* c = (i == 1) ? mpA30 : mpA2c;
        if (c)
            c->Release();
    }
    for (int i = 1; i >= 0; --i) {          // +0x24, +0x28
        void* p = (i == 1) ? mpA28 : mpA24;
        if (p)
            ((RefCountTemplate*)p)->Release();
    }
    ((cGonzagoSubsystem*)this)->dtor();
    return this;
}

// ---------------------------------------------------------------------------
// 00ae8070: one-shot setup of the comm-screen renderers.
void* SP_LightingManager();                 // 0x67dd90
void* SP_LayerManager();                    // 0x67cb20
void* FUN_0080ed50();                       // 0x80ed50
void  FUN_0080df50(void* p);                // 0x80df50
void  FUN_0080fa00(int id, uint32_t tag, void* obj);   // 0x80fa00
void  FUN_0080d5c0(int on);                 // 0x80d5c0
void* FUN_0080db90();                       // 0x80db90
void* FUN_0080db70(int a, int b, int c, int d);  // 0x80db70
void* FUN_0080d5a0(void* obj, int a, int b);     // 0x80d5a0
void  FUN_0080f360(void* obj, void* a, void* b);// 0x80f360

struct CommCtl {                            // the renderer objects (vtbl at +0)
    virtual void v00();                     // +0x00
    virtual void v04();                     // +0x04
    virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void Slot18(void* p);           // +0x18
    virtual void Slot1c(void* p);           // +0x1c
    virtual void v20();
};

struct CommUiObj {                          // CommScreen-N widget returned by LayerManager
    virtual void v00();                     // +0x00
    virtual void v04();                     // +0x04
    uint32_t pad08[0x18 / 4 - 2];
    virtual void Slot18(void* p);           // +0x18
    virtual void Slot1c(void* p);           // +0x1c
};

struct LayerMgrApi {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual CommUiObj* Find(const wchar_t* name);            // +0x20
};

struct LightingMgrApi {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void* Find(int id, int a, int b);                // +0x18
};

struct CommApi {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void Slot30(uint32_t id);                        // +0x30
};

static LayerMgrApi* GetLayerMgr() { return (LayerMgrApi*)SP_LayerManager(); }
static LightingMgrApi* GetLightingMgr() { return (LightingMgrApi*)SP_LightingManager(); }

// Assign a ref-counted renderer slot: AddRef the new value, store, Release the old.
struct AddRefApi { virtual void AddRef(); };       // +0x00

static void AssignRenderer(void** slot, void* v)
{
    if (v == *slot)
        return;
    if (v)
        ((AddRefApi*)v)->AddRef();
    void* old = *slot;
    *slot = v;
    if (old)
        ((cSPUIModelsAndEffectsRenderer*)old)->Release();
}

// Overloads for the raw vtable-slot call on the new renderer value.

// Assign a CommScreen widget slot (AddRef = vtbl slot 0, release = vtbl slot +4).
static void AssignUiSlot(void** slot, void* v)
{
    if (v == *slot)
        return;
    if (v)
        ((RefCountTemplate*)v)->v00();             // AddRef (slot +0x00)
    void* old = *slot;
    *slot = v;
    if (old)
        ((RefCountTemplate*)old)->Release();       // slot +0x04
}

// @ 0x00ae8070
void Gonzago::InitCommScreen()
{
    if (mA92)
        return;
    mA92 = 1;

    CommApi* r0 = (CommApi*)GetLightingMgr()->Find(0x4a4de35, 0, 0);
    CommApi* r1 = (CommApi*)GetLightingMgr()->Find(0x4a4de36, 0, 0);
    r0->Slot30(0x212564ed);
    r1->Slot30(0x212564ed);

    {
        void* v = FUN_0080ed50();
        void* old = mpA1c;
        if (v != old) {
            if (v)
                ((AddRefApi*)v)->AddRef();
            mpA1c = (cSPUIModelsAndEffectsRenderer*)v;
            if (old)
                ((cSPUIModelsAndEffectsRenderer*)old)->Release();
        }
    }
    {
        void* v = FUN_0080ed50();
        void* old = mpA20;
        if (v != old) {
            if (v)
                ((AddRefApi*)v)->AddRef();
            mpA20 = (cSPUIModelsAndEffectsRenderer*)v;
            if (old)
                ((cSPUIModelsAndEffectsRenderer*)old)->Release();
        }
    }
    FUN_0080fa00(0x17f40c6, 0x5df87d7, r0);
    FUN_0080fa00(0x17f40c9, 0x5df87d8, r1);
    FUN_0080d5c0(1);
    FUN_0080d5c0(1);

    {
        CommUiObj* w0 = GetLayerMgr()->Find(L"CommScreen-0");
        AssignUiSlot(&mpA24, w0);
        CommUiObj* w = (CommUiObj*)mpA24;
        w->Slot18(FUN_0080db90());
        w->Slot1c(FUN_0080db70(1, 1, 1, 0));
        FUN_0080f360(mpA24, FUN_0080d5a0(mpA24, 0xe, 0), 0);
    }
    {
        CommUiObj* w1 = GetLayerMgr()->Find(L"CommScreen-1");
        AssignUiSlot(&mpA28, w1);
        CommUiObj* w = (CommUiObj*)mpA28;
        w->Slot18(FUN_0080db90());
        w->Slot1c(FUN_0080db70(1, 1, 1, 0));
        FUN_0080f360(mpA28, FUN_0080d5a0(mpA28, 0xe, 0), 0);
    }

    if (mpA2c) {
        cAnimatingCreature* p = mpA2c;
        mpA2c = 0;
        p->Release();
    }
    if (mpA30) {
        cAnimatingCreature* p = mpA30;
        mpA30 = 0;
        p->Release();
    }
    mA7c = 0;
    mA7d = 0;
    mA90 = 0;
    mA91 = 0;
    mA88 = 0.0f;
    mA8c = 0.0f;

    if (mpA80) {
        RefCounted* p = mpA80;
        mpA80 = 0;
        ((RefCountTemplate*)p)->Release();
    }
    if (mpA84) {
        RefCounted* p = mpA84;
        mpA84 = 0;
        ((RefCountTemplate*)p)->Release();
    }

    {
        eGameMode* m = mObjs[0].mpMode;            // +0x34
        if (m) {
            mObjs[0].mpMode = 0;
            if (m->mRefCount40 > 1) {
                --m->mRefCount40;
            } else {
                ((void(*)(eGameMode*, uint32_t))m->mpVtbl[0x170 / 4])(m, m->mWord4 >> 31);
            }
        }
    }
    {
        eGameMode* m = mObjs[1].mpMode;            // +0x38
        if (m != 0) {
            mObjs[1].mpMode = 0;
            if (m->mRefCount40 > 1) {
                --m->mRefCount40;
            } else {
                ((void(*)(eGameMode*, uint32_t))m->mpVtbl[0x170 / 4])(m, m->mWord4 >> 31);
            }
        }
    }
    mObj3c.mpMode = 0;                             // +0x3c
    mObj40.mpMode = 0;                             // +0x40
    mObj44.mpMode = 0;                             // +0x44
    mObj48.mpMode = 0;                             // +0x48
}
