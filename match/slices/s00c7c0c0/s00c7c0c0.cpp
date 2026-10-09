// Slice s00c7c0c0: Simulator::cGameData / cRock / cInteractableObject helpers (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
// NOTE: the large serialization/owner routines are partial reconstructions (see partial.txt).
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };

extern float g_01694b24, g_01694b28, g_01694b2c;
extern float g_014650a8;
extern void* vtbl_cRock_014732a8;
extern void* vtbl_cRock_4_01473294;
extern void* vtbl_cRock_34_014731d0;
extern void* g_0150d6dc;
extern uint32_t g_01687968;

struct GD {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int  v2c(); virtual void v30(); virtual bool v34(); virtual bool v38();
    virtual bool v3c(int a); virtual void v40();
    virtual void* v44(); virtual void v48();
    char pad_4c[0x2c - 4];
    void* mp2C;                    // +0x2c
    char pad_30[0x84 - 0x30];
    uint32_t mFlags84;             // +0x84
    char pad_88[0xa5 - 0x88];
    uint8_t mFieldA5;              // +0xa5
    char pad_a6[0x10e8 - 0xa6];
    void* mp10E8;                  // +0x10e8
    char pad_10ec[0x113c - 0x10ec];
    uint32_t mField113C;           // +0x113c
    uint32_t mField1140;           // +0x1140
    char pad_1144[0x1184 - 0x1144];
    uint32_t mField1184, mField1188;
    char pad_118c[0x1198 - 0x118c];
    uint32_t mField1198, mField119C;
    char pad_11a0[0x11ac - 0x11a0];
    uint32_t mField11AC, mField11B0;
    char pad_11b4[0x11f4 - 0x11b4];
    void* mp11F4;                  // +0x11f4
    char pad_11f8[0x1244 - 0x11f8];
    void* mp1244;                  // +0x1244
    void* GetAvatar_00b1fdb0();
};
struct RO {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20(); virtual void r24(); virtual void r28();
    virtual void* r2c(); virtual void r30(); virtual void r34(); virtual void r38();
    virtual void r3c(int);
    char pad_40[0x84 - 0x40];
    uint32_t mFlags84;             // +0x84
    uint32_t mField88;             // +0x88
    char pad_8c[0xa5 - 0x8c];
    uint8_t mFieldA5;              // +0xa5
    char pad_a6[0x130 - 0xa6];
    float m130, m134, m138;        // +0x130
    void* mp13C;                   // +0x13c
    uint32_t m140;                 // +0x140
    bool InitFromDefinition_00c7cce0(int def);
    void* ctor_00c7cde0();
};
struct Sub34 {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual Vec3* s2C();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c(int);
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
    virtual void s70(); virtual float s74(int a, int b);
};

void*  MessageServer_0067dcc0();
void*  NounManager_00b3d300();
void*  PropertyManager_0067de30();
void*  ObjectTemplateDB_0067cb40();
void*  FUN_00b3d3b0();
void*  FUN_00b21000_00(void* mgr, uint32_t id);
bool   cGameData_vtableSlot40_00b183f0(void* p, int a);
void   SetGameDataOwner2_00b18550(void* p, int a);
bool   cGameData_Read_00b18600(void* p, void* s);
void   FUN_0091ff50_00(void* p);
void   cCollectableItems_ctor_00597e00(void* p);
void   FUN_00599440_00(int a, int b, int c);
void   FUN_00c751e0_00(void* p);
void   FUN_00c76fd0_00(void* p);
bool   FUN_00c3fc80_00(void* p, int a, int b, int c);
void   FUN_00c3f9b0_00();
void   FUN_00c3f9a0_00(void* p, int a);
void   FUN_00c89160_00(void* p, void* v, float f);
void   FUN_00b83c40_00();
unsigned char FUN_0064f350_00(int a, uint32_t id, int b);

// @ 0x00c7c0c0  eastl vector insert (partial)
void __cdecl FUN_00c7c0c0(void* v, void* pos, void* val)
{
    (void)v; (void)pos; (void)val;
}

// @ 0x00c7c220  cGameData::RemoveOwner (partial: releases + message broadcast)
void __cdecl FUN_00c7c220(GD* self)
{
    if (self->mp2C != 0) {
        ((void(__thiscall*)(void*))(*(void***)self->mp2C)[1])(self->mp2C);
        self->mp2C = 0;
    }
    if (self->mp10E8 != 0) {
        ((void(__thiscall*)(void*))(*(void***)self->mp10E8)[1])(self->mp10E8);
        self->mp10E8 = 0;
    }
    static const uint32_t ids[] = {
        0x4bef1e3, 0x44f1189, 0x5e902d3, 0x6524498, 0x6526395,
        0x6667038, 0x6666683, 0x6527231, 0x6527eaf, 0x1a0219e };
    for (int i = 0; i < 10; ++i) {
        void* ms = MessageServer_0067dcc0();
        ((void(__thiscall*)(void*, int, uint32_t, int))(*(void***)ms)[0x2c / 4])(
            ms, (int)((char*)self + 0x34), ids[i], 0xffffd8f1);
    }
    (void)g_0150d6dc;
}

// @ 0x00c7c4a0  vector resize (partial)
void __cdecl FUN_00c7c4a0(void* v, unsigned n) { (void)v; (void)n; }

// @ 0x00c7c530  load list (partial)
void __cdecl FUN_00c7c530(void* v, void* s) { (void)v; (void)s; }

// @ 0x00c7c6d0  cGameData::SetGameDataOwner (partial)
void __cdecl FUN_00c7c6d0(GD* self, int owner)
{
    SetGameDataOwner2_00b18550(self, owner);
    FUN_0091ff50_00((char*)self + 0x10f8);
    FUN_00c7c4a0((char*)self + 0x113c, 10);
    void* mem = (void*)0;
    (void)mem;
    if (self->mp10E8 == 0) {
        void* p = (void*)0;
        if (p != 0) cCollectableItems_ctor_00597e00(p);
    }
    self->mField1140 = 0;
    FUN_00c751e0_00(self);
    void* pm = PropertyManager_0067de30();
    if (self->mp11F4 != 0) {
        ((void(__thiscall*)(void*))(*(void***)self->mp11F4)[1])(self->mp11F4);
        self->mp11F4 = 0;
    }
    ((void(__thiscall*)(void*, uint32_t, uint32_t, void*))(*(void***)pm)[0x2c / 4])(
        pm, 0x2ca2581, 0x2ae0c7e, (char*)self + 0x11f4);
}

// @ 0x00c7c7c0  ISimulatorSerializable::Read (partial)
bool __cdecl FUN_00c7c7c0(GD* self, void* param_2)
{
    (void)self; (void)param_2; return false;
}

// @ 0x00c7c9b0  load player planet data (partial)
void __cdecl FUN_00c7c9b0(void* v, void* s) { (void)v; (void)s; }

// @ 0x00c7cce0  cInteractableObject::InitFromDefinition wrapper
bool RO::InitFromDefinition_00c7cce0(int def)
{
    if (FUN_00c3fc80_00(this, def, 0, 0)) {
        Vec3* v = ((Sub34*)((char*)this + 0x34))->s2C();
        m130 = v->x;
        m134 = v->y;
        m138 = v->z;
        return true;
    }
    return false;
}

// @ 0x00c7cde0  Simulator::cRock::cRock
void* RO::ctor_00c7cde0()
{
    FUN_00c3f9b0_00();
    *(void**)this = vtbl_cRock_014732a8;
    *(void**)((char*)this + 4) = vtbl_cRock_4_01473294;
    *(void**)((char*)this + 0x34) = vtbl_cRock_34_014731d0;
    m130 = g_01694b24;
    m134 = g_01694b28;
    m138 = g_01694b2c;
    mp13C = 0;
    m140 = 0xffffffff;
    FUN_00c3f9a0_00(this, 5);
    mField88 = 4;
    mFieldA5 = 0;
    mFlags84 |= 0x200;
    return this;
}

// @ 0x00c7ce70
void __cdecl FUN_00c7ce70(RO* self)
{
    if (self->mFieldA5 != 0) {
        void* mgr = NounManager_00b3d300();
        void* o = FUN_00b21000_00(mgr, 0x2a8fb3f);
        if (o != 0 && FUN_0064f350_00(*(int*)((char*)o + 0xc), 0x67364ba, 0) &&
            FUN_0064f350_00(*(int*)((char*)o + 0xc), 0x3d08e15, 0)) {
            Vec3* v = ((Sub34*)((char*)self + 0x34))->s2C();
            float r = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z) * 0.00390625f
                    + ((Sub34*)((char*)self + 0x34))->s74(0x10000000, 0);
            FUN_00b83c40_00();
            (void)r;
        }
    }
}

// @ 0x00c7cf50
void __cdecl FUN_00c7cf50(RO* self, int a) { (void)self; (void)a; }

// @ 0x00c7cfc0
bool __cdecl FUN_00c7cfc0(RO* self, int a)
{
    bool b = cGameData_vtableSlot40_00b183f0(self, a);
    if (b) FUN_00c7ce70(self);
    return b;
}

// @ 0x00c7d020
void __cdecl FUN_00c7d020(RO* self, void* v, float f)
{
    FUN_00c89160_00(self, v, f);
    FUN_00c7ce70((RO*)((char*)self - 0x34));
}

// @ 0x00c7d090
bool __cdecl FUN_00c7d090(RO* self, int* p)
{
    switch (p[0]) {
    case 0: return true;
    case 1: return (int)((Sub34*)((char*)self + 0x34))->s2C() == p[1];
    case 2: return *(int*)((char*)self + 0x1c) == p[1];
    case 8: return (int)self == (int)((GD*)NounManager_00b3d300())->GetAvatar_00b1fdb0();
    default: return false;
    }
}
