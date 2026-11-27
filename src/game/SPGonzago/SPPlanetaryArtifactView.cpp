// src/game/SPGonzago/SPPlanetaryArtifactView.cpp -- migrated from slice(s) s00e8ffa0, s00e90e00 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlanetaryArtifactView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float g_one;             // 0x01485720  (1.0f)
extern float g_thr;             // 0x01485378
extern float g_defR;            // 0x016c5a60
extern float g_defG;            // 0x016c5a64
extern float g_defB;            // 0x016c5a68
#include <math.h>
#include "SP/cCommodityNode.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpatialObject.h"
#include <float.h>
#include <new>

// ---- items of slice s00e90e00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_k13f6a30;        // 0x013f6a30
extern float g_k13f9428;        // 0x013f9428
extern float g_k13f26dc;        // 0x013f26dc
struct V3 { float x, y, z; };
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x00932e80
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }
void* __cdecl operator_new_sp(unsigned int size, const char* pName,
                              int a, int b, int c, int d);              // 0x00f473a0
void* __cdecl FUN_00b3d520();                                       // 0x00b3d520
void* __cdecl FUN_00b3d350(void* a, void* b);                       // 0x00b3d350
void* __cdecl FUN_00b3d380();                                       // 0x00b3d380
void* __cdecl FUN_00b815a0(void* p);                                // 0x00b815a0
void* __cdecl FUN_00b316c0(void* p);                                // 0x00b316c0
void* __cdecl FUN_00fd9c60();                                       // 0x00fd9c60
void* __cdecl FUN_0067dd10();                                       // 0x0067dd10
void* __cdecl FUN_01021300(void* p);                                // 0x01021300
void* __cdecl FUN_00c32cd0(void* p);                                // 0x00c32cd0
void* __cdecl FUN_011e0970(void* a, void* b, void* c, void* d);     // 0x011e0970
void* __cdecl FUN_007c3d30();                                       // 0x007c3d30
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
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
class cSubView1 : public cSpatialObjectView { };
class cSubView2 : public cSpatialObjectView { };
class cDamageView : public cSpatialObjectView {
public:
    void HandleSimulationUpdate_91190(int a, int b);
};
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
// ---- items of slice s00e90e00 end

// ---- items of slice s00e8ffa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_14869f0[];
typedef unsigned char      u8;
typedef unsigned int       u32;
struct Vec3 { float x, y, z; };
namespace SP {
class cSpatialObjectView_s00e8_ffa0 {
public:
    void** mVTable;                    // +0x00
    void*  mpPrev;                     // +0x04
    void*  mpNext;                     // +0x08
    void*  mpObject;                   // +0x0c
    void*  mpObjectCombatant;          // +0x10
    u8     mField14;                   // +0x14
    u8     mPad15[3];
    Vec3   mColor;                     // +0x18
    u32    mKeyType;                   // +0x24
    u32    mKeyGroup;                  // +0x28
    u32    mKeyInstance;               // +0x2c
    u8     mField30;                   // +0x30
    u8     mField31;                   // +0x31
    u8     mField32;                   // +0x32
    u8     mPad33;                     // +0x33

    cSpatialObjectView_s00e8_ffa0();              // 0x00e92af0
    void BaseCtor();                   // 0x00e92af0
    void HandleSimulationUpdate(int a, int b);   // 0x00e92ca0
};
}
namespace SP {
class cPlanetaryArtifact : public cSpatialObjectView_s00e8_ffa0 {
public:
    cPlanetaryArtifact();
};
}
using SP::cSpatialObjectView_s00e8_ffa0;
using SP::cPlanetaryArtifact;
// ---- items of slice s00e8ffa0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
V3* __cdecl GetPropertyV3a(V3* out, uint32_t group, int a, uint32_t prop, V3 def);  // 0x00e91410 (stays in the slice: not this object's)

// @ 0x00e90d80
SP::cPlanetaryArtifact::cPlanetaryArtifact()
: cSpatialObjectView_s00e8_ffa0()
{
    Vec3 c = { 1.0f, 1.0f, 1.0f };
    mVTable = (void**)g_14869f0;
    mColor = c;
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
    bool on = ((fl >> 0xe) & 1) != 0;
    if (!on)
        return;
    float dmgDist = m->mField8c;
    if (dmgDist > g_thr)
        OnDamageStateChanged(0, 0);
    else
        OnDamageStateChanged(1, 0);
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
