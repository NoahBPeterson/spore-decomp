// src/game/SPGonzago/SPPlanetaryArtifactView.cpp -- migrated from slice(s) s00e90e00 by tools/migrate/rewrite.py
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

// ---- items of slice s00e90e00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; };
void* __cdecl operator_new_sp(unsigned int size, const char* pName,
                              int a, int b, int c, int d);              // 0x00f473a0
void* __cdecl FUN_00b3d520();                                       // 0x00b3d520
void* __cdecl FUN_01021300(void* p);                                // 0x01021300
void* __cdecl FUN_00c32cd0(void* p);                                // 0x00c32cd0
extern float g_one;             // 0x01485720  (1.0f)
extern float g_thr;             // 0x01485378
extern float g_defR;            // 0x016c5a60
extern float g_defG;            // 0x016c5a64
extern float g_defB;            // 0x016c5a68
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
