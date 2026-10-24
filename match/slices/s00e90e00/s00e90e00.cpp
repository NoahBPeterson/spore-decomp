// Slice s00e90e00 -- SP view update helpers, MakeView factories and the
// cViewA / cRotationRingView ctors+dtors.
//
//  0x00e90e00  cSpatialObjectView::Update_90e00            (ret 8)
//  0x00e91060  cSpatialObjectView::MakeView_91060          (ret 4)
//  0x00e91190  cDamageView::HandleSimulationUpdate_91190   (ret 8)
//  0x00e911f0  cSpatialObjectView::MakeView_911f0          (ret 4)
//  0x00e91400  cViewA::GetFlag0                            (ret)
//  0x00e91410  GetPropertyV3a                              (cdecl)
//  0x00e914f0  GetPropertyV3b                              (cdecl)
//  0x00e915d0  cViewA::cViewA                              (ret)
//  0x00e915f0  cViewA::~cViewA                             (ret)
//  0x00e916a0  cViewA::Update_916a0                        (ret 8)
//  0x00e91990  cSpatialObjectView::MakeView_91990          (ret 4)
//  0x00e91ba0  cViewA::SetModelFlag                        (ret 4)
//  0x00e91bd0  cViewA::SetFlag0                            (ret 4)
//  0x00e91bf0  cViewA::GetFlagF                            (ret)
//  0x00e91c10  cRotationRingView::cRotationRingView         (ret)
//  0x00e91c30  cRotationRingView::~cRotationRingView        (ret)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (MSVC 2008 SP1).
#include "types.h"
#include <math.h>

// ---- basic types -----------------------------------------------------------
struct V3 { float x, y, z; };
struct Key { uint32_t mInstance, mType, mGroup; };
struct Matrix33 { float m[9]; };

// ---- property hashing ------------------------------------------------------
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x00932e80
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }

float __cdecl GetPropertyF(uint32_t group, int a, uint32_t prop, float def);  // 0x00bcea30

// ---- EA allocator new ------------------------------------------------------
void* __cdecl operator_new_sp(unsigned int size, const char* pName,
                              int a, int b, int c, int d);              // 0x00f473a0

// ---- raw callees -----------------------------------------------------------
void* __cdecl FUN_00b3d520();                                       // 0x00b3d520
void* __cdecl FUN_00b3d350(void* a, void* b);                       // 0x00b3d350
void* __cdecl FUN_00b3d380();                                       // 0x00b3d380
void* __cdecl FUN_00b815a0(void* p);                                // 0x00b815a0
void* __cdecl FUN_00b316c0(void* p);                                // 0x00b316c0
void* __cdecl FUN_00fd9c60();                                       // 0x00fd9c60
void* __cdecl FUN_0067dd10();                                       // 0x0067dd10
void* __cdecl FUN_0067dd80();                                       // 0x0067dd80
void* __cdecl FUN_0067ddd0();                                       // 0x0067ddd0
void* __cdecl FUN_0067de30();                                       // 0x0067de30
void* __cdecl FUN_00d1d5c0(void* p);                                // 0x00d1d5c0
void* __cdecl FUN_00a16f40(void* p);                                // 0x00a16f40
void* __cdecl FUN_00434040(void* p);                                // 0x00434040
void* __cdecl FUN_00571d40(void* p);                                // 0x00571d40
void* __cdecl FUN_0059c190(void* a, void* b);                       // 0x0059c190
void* __cdecl FUN_006a1250(void* a, void* b, void* c, void* d);     // 0x006a1250
void* __cdecl FUN_01021300(void* p);                                // 0x01021300
void* __cdecl FUN_00c32cd0(void* p);                                // 0x00c32cd0
void* __cdecl FUN_011e0970(void* a, void* b, void* c, void* d);     // 0x011e0970
void* __cdecl FUN_00b3d310(void* p, int a);                         // 0x00b3d310
void* __cdecl FUN_00478db0(void* p, void* a);                       // 0x00478db0
void* __cdecl FUN_007c3d30();                                       // 0x007c3d30
void  __cdecl FUN_006bb5e0();                                       // 0x006bb5e0
void  __cdecl FUN_006bb600();                                       // 0x006bb600
void* __cdecl FUN_00537dc0(void* self, const void* src);            // 0x00537dc0
void* __cdecl FUN_0069b440(void* out, void* a, void* b);            // 0x0069b440
void  __cdecl FUN_0041cb40(void* dst, const void* src);             // 0x0041cb40

// ---- retail constants used verbatim ----------------------------------------
extern float g_one;             // 0x01485720  (1.0f)
extern float g_thr;             // 0x01485378
extern float g_defR;            // 0x016c5a60
extern float g_defG;            // 0x016c5a64
extern float g_defB;            // 0x016c5a68
extern float g_k13ebc68;        // 0x013ebc68  (1.0f)
extern float g_bias13f4fd0;     // 0x013f4fd0
extern float g_k13f6a30;        // 0x013f6a30
extern float g_k13f9428;        // 0x013f9428
extern float g_k13f26dc;        // 0x013f26dc
extern float g_16c5a9c;         // 0x016c5a9c
extern float g_16c5aa0;         // 0x016c5aa0
extern float g_16c5aa4;         // 0x016c5aa4

// ---- vtable-call helpers ---------------------------------------------------
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))

// ---------------------------------------------------------------------------
// The "model" cell: view +0x14 / GetModel() result.  The first word points at
// the actual object (vtable at its +0x00); flags at +0x04, refcount at +0x40.
// ---------------------------------------------------------------------------
struct cModel {
    void*    mpObj;        // +0x00
    union {
        uint32_t mFlags;       // +0x04 (dword view)
        uint8_t  mFlagBytes[4];// +0x04 (byte view)
        struct { uint32_t mPadBit : 15; uint32_t mwFlagF : 1; };  // bit 15
        struct { uint32_t mPadBit2 : 14; uint32_t mwFieldE : 1; }; // bit 14
        struct { unsigned char mbFlag0 : 1; };                    // bit 0 (byte unit)
    };
    uint16_t mField08;     // +0x08
    uint16_t mField0a;     // +0x0a
    uint8_t  pad_0c[0x0c];
    float    mField18;     // +0x18
    uint8_t  pad_1c[0x24];
    uint32_t mRefCount;    // +0x40
    uint8_t  pad_44[0x08];
    V3       mColor;       // +0x4c
    float    mField58;     // +0x58
    uint8_t  pad_5c[0x30];
    float    mField8c;     // +0x8c
    uint8_t  pad_90[0x63c - 0x90];
    uint32_t mField63c;    // +0x63c
    uint32_t mField640;    // +0x640
    float    mField644;    // +0x644
    float    mField648;    // +0x648
    uint8_t  pad_64c[0x0c];
    uint32_t mField658;    // +0x658
    uint8_t  mbField65c;   // +0x65c
    uint8_t  mbField65d;   // +0x65d
    uint8_t  pad_65e[0x02];
    float    mField660;    // +0x660
};

struct cSpatialObject;

// ---------------------------------------------------------------------------
// cViewA -- base view with a model handle at +0x14 (vtable 0x1486a80).
// ---------------------------------------------------------------------------
class cViewA {
public:
    virtual void v00();

    cViewA();                                   // 0x00e915d0
    ~cViewA();                                  // 0x00e915f0

    bool  GetFlag0();                           // 0x00e91400
    void  Update_916a0(int a, int b);           // 0x00e916a0
    void  SetModelFlag(bool b);                 // 0x00e91ba0
    void  SetFlag0(bool b);                     // 0x00e91bd0
    bool  GetFlagF();                           // 0x00e91bf0

    uint32_t mField04;                          // +0x04
    uint32_t mField08;                          // +0x08
    cSpatialObject* mpObject;                   // +0x0c
    void*    mpField10;                         // +0x10
    cModel*  mModel;                            // +0x14
    uint32_t mField18;                          // +0x18
};

// ---------------------------------------------------------------------------
// cRotationRingView -- (vtable 0x1486b1c, size 0x20).
// ---------------------------------------------------------------------------
class cRotationRingView {
public:
    virtual void v00(void*);

    cRotationRingView();                        // 0x00e91c10
    ~cRotationRingView();                       // 0x00e91c30

    uint32_t mField04;                          // +0x04
    uint32_t mField08;                          // +0x08
    cSpatialObject* mpObject;                   // +0x0c
    void*    mpGameDataView;                    // +0x10
    cModel*  mModel;                            // +0x14
    uint32_t mAnimID;                           // +0x18
    int      mLifeTimer;                        // +0x1c
};

// ---------------------------------------------------------------------------
// cSpatialObjectView -- (vtable 0x1486c00).  Only the slots used here named.
// ---------------------------------------------------------------------------
class cSpatialObjectView {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void* v28(void*, void*);            // +0x28
    virtual cModel* GetModel();                 // +0x2c
    virtual void* GetTransform();               // +0x30

    __declspec(noinline) void BaseInit();       // mirrors ctor 0x00e92af0

    void  HandleSimulationUpdate(int a, int b); // 0x00e92ca0
    void  OnDamageStateChanged(int a, int b);   // 0x00e93160

    void  Update_90e00(int a, int b);           // 0x00e90e00
    cSpatialObjectView* MakeView_91060(void* gamedata);  // 0x00e91060
    cSpatialObjectView* MakeView_911f0(void* gamedata);  // 0x00e911f0
    cViewA* MakeView_91990(void* gamedata);              // 0x00e91990

    cSpatialObject* mpObject;                   // +0x0c
    void*    mpObjectCombatant;                 // +0x10
    uint8_t  mField14;                          // +0x14
    char     pad_15[3];
    V3       mColor;                            // +0x18
};

// ---------------------------------------------------------------------------
// factory targets (the objects the MakeView helpers allocate).
// ---------------------------------------------------------------------------
class cSubView1 : public cSpatialObjectView { };
class cSubView2 : public cSpatialObjectView { };

// A view whose HandleSimulationUpdate is overridden (0x00e91190).
class cDamageView : public cSpatialObjectView {
public:
    void HandleSimulationUpdate_91190(int a, int b);
};

// ===========================================================================
// cViewA
// ===========================================================================

// @ 0x00e91400
bool cViewA::GetFlag0()
{
    return mModel->mbFlag0;
}

// @ 0x00e915d0
cViewA::cViewA()
{
    mField08 = 0;
    mField04 = 0;
    *(void**)this = (void*)0x1486a80;
    mpObject = 0;
    mpField10 = 0;
    mModel = 0;
    mField18 = 0;
}

// @ 0x00e915f0
cViewA::~cViewA()
{
    cModel* m = mModel;
    *(void**)this = (void*)0x1486a80;
    ((void(__thiscall*)(void*, void*, int))VF(m->mpObj, 0x16c))(m->mpObj, m, 0);

    m = mModel;
    if (m != 0) {
        mModel = 0;
        uint32_t rc = m->mRefCount;
        if ((int)rc > 1) {
            m->mRefCount = rc - 1;
        } else {
            bool f = (m->mFlags >> 0x1f) & 1;
            ((void(__thiscall*)(void*, void*, bool))VF(m->mpObj, 0x170))(m->mpObj, m, f);
        }
    }
    m = mModel;
    if (m != 0) {
        uint32_t rc = m->mRefCount;
        if ((int)rc > 1) {
            m->mRefCount = rc - 1;
        } else {
            bool f = (m->mFlags >> 0x1f) & 1;
            ((void(__thiscall*)(void*, void*, bool))VF(m->mpObj, 0x170))(m->mpObj, m, f);
        }
    }
    void* p = mpField10;
    if (p != 0)
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    cSpatialObject* o = mpObject;
    if (o != 0)
        ((void(__thiscall*)(void*))VF(o, 4))(o);
    *(void**)this = (void*)0x1455648;
}

// @ 0x00e91ba0
void cViewA::SetModelFlag(bool b)
{
    cModel* m = mModel;
    if (m == 0)
        return;
    void* o = m->mpObj;
    typedef void (__thiscall* Fn)(void*, void*, int);
    if (b)
        ((Fn)VF(o, 0x16c))(o, m, 1);
    else
        ((Fn)VF(o, 0x16c))(o, m, 0);
}

// @ 0x00e91bd0
void cViewA::SetFlag0(bool b)
{
    uint32_t* f = &mModel->mFlags;
    if (b)
        *f |= 1u;
    else
        *f &= 0xfffffffeu;
}

// @ 0x00e91bf0
bool cViewA::GetFlagF()
{
    bool b;
    if (mModel != 0) {
        b = (mModel->mFlags >> 0xf) & 1;
    } else {
        b = true;
    }
    return b;
}

// ===========================================================================
// cRotationRingView
// ===========================================================================

// @ 0x00e91c10
cRotationRingView::cRotationRingView()
{
    mField08 = 0;
    mField04 = 0;
    *(void**)this = (void*)0x1486b1c;
    mpObject = 0;
    mpGameDataView = 0;
    mModel = 0;
    mAnimID = 0;
    mLifeTimer = 0;
}

// @ 0x00e91c30
cRotationRingView::~cRotationRingView()
{
    cModel* m = mModel;
    *(void**)this = (void*)0x1486b1c;
    ((void(__thiscall*)(void*, void*, int))VF(m->mpObj, 0x16c))(m->mpObj, m, 0);

    m = mModel;
    if (m != 0) {
        mModel = 0;
        uint32_t rc = m->mRefCount;
        if ((int)rc > 1) {
            m->mRefCount = rc - 1;
        } else {
            bool f = (m->mFlags >> 0x1f) & 1;
            ((void(__thiscall*)(void*, void*, bool))VF(m->mpObj, 0x170))(m->mpObj, m, f);
        }
    }
    m = mModel;
    if (m != 0) {
        uint32_t rc = m->mRefCount;
        if ((int)rc > 1) {
            m->mRefCount = rc - 1;
        } else {
            bool f = (m->mFlags >> 0x1f) & 1;
            ((void(__thiscall*)(void*, void*, bool))VF(m->mpObj, 0x170))(m->mpObj, m, f);
        }
    }
    void* p = mpGameDataView;
    if (p != 0)
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    cSpatialObject* o = mpObject;
    if (o != 0)
        ((void(__thiscall*)(void*))VF(o, 4))(o);
    *(void**)this = (void*)0x1455648;
}

// ===========================================================================
// GetPropertyV3a / GetPropertyV3b
// ===========================================================================

// @ 0x00e91410
V3* __cdecl GetPropertyV3a(V3* out, uint32_t group, int a, uint32_t prop, V3 def)
{
    void* guard = 0;
    void* obj = FUN_0067de30();
    if (guard != 0)
        ((void(__thiscall*)(void*))VF(guard, 4))(guard);

    bool ok = ((bool(__thiscall*)(void*, uint32_t, int, void**))VF(obj, 0x2c))
                  (obj, group, a, &guard);
    if (ok) {
        void* val = 0;
        if (((bool(__thiscall*)(void*, uint32_t, void**))VF(guard, 0x24))(guard, prop, &val)) {
            void* src;
            uint16_t ty = *(uint16_t*)((char*)val + 0x12);
            if (ty == 0x31 || ty == 0x10) {
                if (*(uint8_t*)((char*)val + 0x10) & 0x30)
                    src = *(void**)val;
                else
                    src = (ty != 0) ? val : 0;
            } else {
                FUN_006bb5e0();
                src = 0;
            }
            float* f = (float*)src;
            out->x = f[0];
            out->y = f[1];
            out->z = f[2];
        } else {
            *out = def;
        }
    } else {
        *out = def;
    }
    if (guard != 0)
        ((void(__thiscall*)(void*))VF(guard, 4))(guard);
    return out;
}

// @ 0x00e914f0
V3* __cdecl GetPropertyV3b(V3* out, uint32_t group, int a, uint32_t prop, V3 def)
{
    void* guard = 0;
    void* obj = FUN_0067de30();
    if (guard != 0)
        ((void(__thiscall*)(void*))VF(guard, 4))(guard);

    bool ok = ((bool(__thiscall*)(void*, uint32_t, int, void**))VF(obj, 0x2c))
                  (obj, group, a, &guard);
    if (ok) {
        void* val = 0;
        if (((bool(__thiscall*)(void*, uint32_t, void**))VF(guard, 0x24))(guard, prop, &val)) {
            void* src;
            uint16_t ty = *(uint16_t*)((char*)val + 0x12);
            if (ty == 0x32 || ty == 0x10) {
                if (*(uint8_t*)((char*)val + 0x10) & 0x30)
                    src = *(void**)val;
                else
                    src = (ty != 0) ? val : 0;
            } else {
                FUN_006bb600();
                src = 0;
            }
            float* f = (float*)src;
            out->x = f[0];
            out->y = f[1];
            out->z = f[2];
        } else {
            *out = def;
        }
    } else {
        *out = def;
    }
    if (guard != 0)
        ((void(__thiscall*)(void*))VF(guard, 4))(guard);
    return out;
}

// ===========================================================================
// cSpatialObjectView
// ===========================================================================

// mirrors 0x00e92af0
void cSpatialObjectView::BaseInit()
{
    uint32_t z = 0;
    *(uint32_t*)((char*)this + 8) = z;
    *(uint32_t*)((char*)this + 4) = z;
    *(void**)this = (void*)0x1486c00;
    mpObject = 0;
    mpObjectCombatant = 0;
    mField14 = 0;
    mColor.x = g_defR;
    mColor.y = g_defG;
    mColor.z = g_defB;
    *(uint32_t*)((char*)this + 0x24) = z;
    *(uint32_t*)((char*)this + 0x28) = z;
    *(uint32_t*)((char*)this + 0x2c) = z;
    *(uint8_t*)((char*)this + 0x30) = 0;
    *(uint8_t*)((char*)this + 0x31) = 0;
    *(uint8_t*)((char*)this + 0x32) = 0;
}

// @ 0x00e91060
cSpatialObjectView* cSpatialObjectView::MakeView_91060(void* gamedata)
{
    cSubView1* v = (cSubView1*)operator_new_sp(0x34, "Simulator/cView1", 0, 0, 0, 0);
    if (v != 0) {
        v->BaseInit();
        V3 c;
        c.x = g_one;
        c.y = g_one;
        c.z = g_one;
        v->mColor = c;
        *(void**)v = (void*)0x14869bc;
    } else {
        v = 0;
    }

    if (gamedata == 0)
        return 0;
    void* o = ((void*(__thiscall*)(void*, uint32_t))VF(gamedata, 0xc))(gamedata, 0x4e3faaf);
    if (o == 0)
        return 0;

    void* sub = (char*)o + 0x34;
    void* pos = ((void*(__thiscall*)(void*))VF(sub, 0x98))(sub);
    V3 p;
    p.x = ((float*)pos)[0];
    p.y = ((float*)pos)[1];
    p.z = ((float*)pos)[2];
    v->mColor = p;

    void* world = ((void*(__stdcall*)(void*, const void*))FUN_00b3d520)
                      ((char*)this + 0x18, &p);
    ((void(__thiscall*)(void*, void*, void*))VF(v, 0x28))(v, gamedata, world);

    cModel* m = (cModel*)((void*(__thiscall*)(void*))VF(v, 0x2c))(v);
    if (m != 0) {
        m->mField0a++;
        m->mField18 = g_one;
        m->mFlags |= 4;
        V3 tmp;
        void* q = FUN_01021300(&tmp);
        void* col = FUN_00c32cd0(q);
        m->mColor.x = ((float*)col)[0];
        m->mColor.y = ((float*)col)[1];
        m->mColor.z = ((float*)col)[2];
    }
    return v;
}

// @ 0x00e91190
void cDamageView::HandleSimulationUpdate_91190(int a, int b)
{
    HandleSimulationUpdate(a, b);

    cModel* m = GetModel();
    if (m == 0)
        return;
    uint32_t fl = m->mFlags;
    if (((fl >> 0xe) & 1) == 0)
        return;
    float dmgDist = m->mField8c;
    if (dmgDist <= g_thr)
        OnDamageStateChanged(1, 0);
    else
        OnDamageStateChanged(0, 0);
}

// @ 0x00e911f0
cSpatialObjectView* cSpatialObjectView::MakeView_911f0(void* gamedata)
{
    cSubView2* v = (cSubView2*)operator_new_sp(0x34, "Simulator/cView2", 0, 0, 0, 0);
    if (v != 0) {
        v->BaseInit();
        V3 c;
        c.x = g_one;
        c.y = g_one;
        c.z = g_one;
        v->mColor = c;
        *(void**)v = (void*)0x14869f0;
    } else {
        v = 0;
    }

    if (gamedata == 0)
        return 0;
    void* o = ((void*(__thiscall*)(void*, uint32_t))VF(gamedata, 0xc))(gamedata, 0x2dd8c33);
    if (o == 0)
        return 0;

    void* sub = (char*)o + 0x34;
    void* pos = ((void*(__thiscall*)(void*))VF(sub, 0x98))(sub);
    V3 p;
    p.x = ((float*)pos)[0];
    p.y = ((float*)pos)[1];
    p.z = ((float*)pos)[2];
    v->mColor = p;

    void* world = ((void*(__stdcall*)(void*, const void*))FUN_00b3d520)
                      ((char*)this + 0x18, &p);
    ((void(__thiscall*)(void*, void*, void*))VF(v, 0x28))(v, gamedata, world);

    cModel* m = (cModel*)((void*(__thiscall*)(void*))VF(v, 0x2c))(v);
    if (m != 0) {
        m->mField0a++;
        m->mField18 = g_one;
        m->mFlags |= 2;
    }
    if (m != 0) {
        V3 c;
        c.x = g_defR;
        c.y = g_defG;
        c.z = g_defB;
        GetPropertyV3a(&c, id((const char*)0x1486acc), 0,
                       id((const char*)0x146868c), c);
        m->mColor = c;
    }
    return v;
}

// @ 0x00e90e00
void cSpatialObjectView::Update_90e00(int a, int b)
{
    cModel* model = GetModel();
    float f1c = model ? model->mField18 : g_one;
    HandleSimulationUpdate(a, b);

    cSpatialObject* o = mpObject;
    cModel* m = 0;
    if (o != 0)
        m = (cModel*)((void*(__thiscall*)(void*, uint32_t))VF(o, 0xb8))(o, 0x2dd8c33);

    if (model == 0)
        return;

    float f3c = g_one;
    if (m->mField648 > g_thr)
        f3c = m->mField648;

    float xmm1 = f3c;
    if (m->mbField65d != 0) {
        float ax = ((float*)FUN_00fd9c60())[0x138 / 4];
        float ay = ((float*)FUN_00fd9c60())[0x13c / 4];
        if (m->mField644 > g_thr)
            ay = m->mField644;

        void* g = FUN_0067dd10();
        void* q = ((void*(__thiscall*)(void*))VF(g, 0x50))(g);
        void* r = ((void*(__thiscall*)(void*))VF(q, 0x1c))(q);
        V3 pv;
        if (r != 0)
            ((void(__thiscall*)(void*, void*, void*, void*, void*))FUN_007c3d30)
                (r, 0, 0, 0, &pv);
        V3 w;
        w.x = pv.x;
        w.y = pv.y;
        w.z = pv.z;
        float* c0 = (float*)FUN_00b815a0(FUN_00b3d350(&w, &pv));
        float dx = f1c - c0[0];
        float dy = ay - c0[1];
        float dz = pv.z - c0[2];
        float dist = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
        if (dist > ax)
            xmm1 = ay * f3c;
        else
            xmm1 = f3c;
    }

    float xmm0 = m->mField660;
    if (xmm0 >= 0.0f) {
        xmm0 = xmm0 * xmm1;
        xmm1 = xmm0;
    }
    float t = ((float)a) * g_k13f6a30;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    xmm0 = xmm1;
    model->mField0a++;
    model->mField18 = xmm0;

    if (m->mField640 != 0) {
        void* g2 = FUN_00b3d380();
        void* q2 = FUN_00b316c0(g2);
        void* r2 = FUN_011e0970(q2, g2, (void*)0x3e8, 0);
        unsigned old = m->mField640;
        unsigned cur = (unsigned)r2;
        if (old < cur) {
            unsigned d = cur - old;
            if (d >= 0x129) {
                float v2 = (float)b * g_k13f9428 * g_k13f26dc;
                model->mField58 = model->mField58 - v2;
            }
        }
    }
}

// @ 0x00e916a0
void cViewA::Update_916a0(int a, int b)
{
    cSpatialObject* o = mpObject;
    if (o == 0)
        return;
    if (((uint8_t(__thiscall*)(void*))VF(o, 0x58))(o) == 0) {
        mModel->mFlags &= 0xfffffffeu;
        mField18 = 0;
        (void)a;
        (void)b;
        return;
    }
    mModel->mFlags |= 1;

    uint32_t p1 = id((const char*)0x1486ae4);
    uint32_t p0 = id((const char*)0x146868c);
    float fv = GetPropertyF(p0, 0, p1, g_k13ebc68);
    (void)fv;

    float colr = g_defR;
    float colg = g_defG;
    float colb = g_defB;
    uint32_t p2 = id((const char*)0x1486acc);
    V3 c;
    c.x = colr;
    c.y = colg;
    c.z = colb;
    GetPropertyV3a(&c, p2, 0, p0, c);
    (void)c;

    void* o2 = mpObject;
    void* sub = (char*)o2 + 0x34;
    void* pos = ((void*(__thiscall*)(void*))VF(sub, 0x2c))(sub);
    float x = ((float*)pos)[0];
    float y = ((float*)pos)[1];
    float z = ((float*)pos)[2];
    (void)x; (void)y; (void)z;
    (void)a; (void)b;
}

// @ 0x00e91990
cViewA* cSpatialObjectView::MakeView_91990(void* gamedata)
{
    cViewA* v = (cViewA*)operator_new_sp(0x1c, "Simulator/cViewA", 0, 0, 0, 0);
    if (v != 0) {
        v->mField08 = 0;
        v->mField04 = 0;
        *(void**)v = (void*)0x1486a80;
        v->mpObject = 0;
        v->mpField10 = 0;
        v->mModel = 0;
        v->mField18 = 0;
    } else {
        v = 0;
    }

    void* old = v->mpField10;
    if (gamedata != old) {
        if (gamedata != 0)
            ((void(__thiscall*)(void*))VF(gamedata, 0))(gamedata);
        v->mpField10 = gamedata;
        if (old != 0)
            ((void(__thiscall*)(void*))VF(old, 4))(old);
    }
    if (gamedata == 0)
        return v;

    void* o = ((void*(__thiscall*)(void*, uint32_t))VF(gamedata, 0xc))(gamedata, 0x7292112);
    if (o == 0)
        return v;

    cSpatialObject* old2 = v->mpObject;
    if (o != old2) {
        ((void(__thiscall*)(void*))VF(o, 0))(o);
        v->mpObject = (cSpatialObject*)o;
        if (old2 != 0)
            ((void(__thiscall*)(void*))VF(old2, 4))(old2);
    }

    void* world = FUN_00b3d520();
    void* wf = ((void*(__thiscall*)(void*, const char*))VF(world, 0x58))(world, "$");
    (void)wf;

    // update transform + flags
    cSpatialObject* ob = v->mpObject;
    o = ((void*(__thiscall*)(void*))VF(o, 0x68))(o);
    uint32_t bb = *(uint32_t*)o;
    void* sub = (char*)ob + 0x34;
    ((void(__thiscall*)(void*, void*, uint32_t))VF(sub, 0x58))(sub, ob, bb);
    uint32_t* mfl = (uint32_t*)((char*)v->mpObject);
    (void)mfl;

    return v;
}