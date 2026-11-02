// src/game/SPGonzago/_at_00cf0000.cpp -- migrated from slice(s) s00cf6df0, s00cf0cf0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00cf0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>
#pragma warning(disable: 4100)

// ---- items of slice s00cf0cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef signed int     i32;
#define MOPS(p) ((COps*)(p))
#define VT(p)   (*(void***)(p))
u8    __cdecl FUN_00b7c780();                                     // 0x00b7c780
u32   __cdecl FUN_00b7c770();                                     // 0x00b7c770
void  __cdecl FUN_00b7c810(u32 a);                                // 0x00b7c810
void* __cdecl FUN_00b3d250();                                     // 0x00b3d250
void* __cdecl FUN_00cf74c0();                                     // 0x00cf74c0
struct COps
{
    void  FUN_00e352c0();                              // 0x00e352c0
    void* FUN_00cf74f0();                              // 0x00cf74f0
    void* FUN_00cf7500();                              // 0x00cf7500
    void  FUN_00ce8ee0(u32 a);                         // 0x00ce8ee0
    void  FUN_00e34ea0(void* a);                       // 0x00e34ea0
    void  FUN_00571e80();                              // 0x00571e80
    u32   FUN_00b2fa60();                              // 0x00b2fa60
    void  FUN_00cf8d70(u32 a);                         // 0x00cf8d70
    void  FUN_00cf7470(u32 a);                         // 0x00cf7470
    void  FUN_00cec7a0(u32 a);                         // 0x00cec7a0
    void* FUN_00b25fb0();                              // 0x00b25fb0
    void  FUN_00b10c40(u32 a);                         // 0x00b10c40
    u32   FUN_00c44f10();                              // 0x00c44f10
    void  FUN_00b5f950(void* a);                       // 0x00b5f950
    void  FUN_00b2fba0(u32 a);                         // 0x00b2fba0
    u8    FUN_00d09660();                              // 0x00d09660
    void  FUN_00b146a0(u32 a);                         // 0x00b146a0
    void  FUN_00ce96b0(u32 a);                         // 0x00ce96b0
    void  FUN_00b32250(u32 a);                         // 0x00b32250
    u8    FUN_00bf8a00(u32 a);                         // 0x00bf8a00
    void  FUN_00bf8a70(u32 a, void* b);                // 0x00bf8a70
    void* FUN_00b25c30();                              // 0x00b25c30
    u32   FUN_00cfb610(u32 a);                         // 0x00cfb610
    void  FUN_00b0f950(u32 a);                         // 0x00b0f950
    void  FUN_00b815a0(void* a, void* b, void* c);      // 0x00b815a0
    void  FUN_00b7f1f0(void* a, void* b, u32 c);        // 0x00b7f1f0
};
struct cCityInputStrategy
{
    u8    pad0[0x48];            // +0x0000
    u8    mField48;              // +0x0048
    u8    pad49[0x4c - 0x49];
    void* mField4c;              // +0x004c
    u8    pad50[0x6c - 0x50];
    u32   mpHandler;             // +0x006c
    union
    {
        u32 mField70;            // +0x0070
        struct
        {
            u8  pad70[2];
            u8  mFlag72;         // +0x0072
            u8  pad73[1];
        };
    };
    u32   mField74;              // +0x0074
    u32   mField78;              // +0x0078
    u32   mField7c;              // +0x007c
    void* mpField80;             // +0x0080
    u8    pad84[0xc0 - 0x84];
    u32   mFieldc0;              // +0x00c0
    u32   mFieldc4;              // +0x00c4
    u32   mFieldc8;              // +0x00c8
    u32   mFieldcc;              // +0x00cc
    u8    padd0[0xd8 - 0xd0];
    void* mpFieldd8;             // +0x00d8
    u8    paddc[0xe4 - 0xdc];
    void* mFielde4;              // +0x00e4
    u8    pade8[0x104 - 0xe8];
    void* mpField104;            // +0x0104
    u8    pad108[0x12c - 0x108];
    u32   mField12c;             // +0x012c
    u8    pad130[0x136 - 0x130];
    u8    mField136;             // +0x0136
    u8    pad137[0x138 - 0x137];
    u32   mField138;             // +0x0138
    u8    pad13c[0x140 - 0x13c];
    i32   mField140;             // +0x0140

    void  FUN_00cf0e20(u32 a, u32 b);
    void  FUN_00cf0ed0();
    u32   FUN_00cf0fe0();
    u32   FUN_00cf1000(void* a, u32 b);
    void  FUN_00cf1440();
    void  FUN_00cf14d0();
    void  FUN_00cf1500(u32 a);
    u32   FUN_00cf1540();
    u32   FUN_00cf1630(void* a);
    u32   FUN_00cf16f0(void* a, void* b);
    u32   FUN_00cf17b0(void* a, void* b);
    void  FUN_00cf1810(void* a, u8 b);
    u32   FUN_00cf18b0(void* a, void* b);
    u32   FUN_00cf1ad0(void* a, void* b);
    void  FUN_00cf1be0(i32 a);
};
// ---- items of slice s00cf0cf0 end

// ---- items of slice s00cf6df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  *SP_NounManager();                         // 0x00b3d300
extern "C" void  *GetPlayerCivilization(void *mgr);         // 0x00b25fb0
extern const float kOne;        // 0x1485720 == 1.0f
extern "C" void  *GameTimeManager();                            // 0x00b3d380
extern "C" void  *FUN_00b3d4f0();                               // 0x00b3d4f0
extern "C" void FUN_00b32250();          // 0x00b32250 DecPauseGate (thiscall)
extern "C" void   FUN_00e2f270();                               // 0x00e2f270
extern "C" void *GameInputManager();    // 0x00b3d250
extern const float kCivRatioConst;      // 0x1471064
extern const float kZero;               // 0x1485378
extern "C" float FUN_00bf1880();        // 0x00bf1880 cCivilization method (thiscall)
extern "C" void *SP_ConfigManager();        // 0x0067dd30
extern "C" void  *g_opNew();                 // 0x00f473a0 operator new
extern "C" void  *FUN_00cf4ca0();            // 0x00cf4ca0 cCityInputStrategy ctor (thiscall)
extern "C" void  *FUN_00ceb090();            // 0x00ceb090 cCityDisplayStrategy ctor (thiscall)
extern "C" void   FUN_00cea090();            // 0x00cea090 cCityDisplayStrategy::Init (thiscall)
extern "C" void   FUN_00cf14d0();            // 0x00cf14d0 (thiscall)
extern "C" void   FUN_00cf4c00();            // 0x00cf4c00 (thiscall)
extern "C" void   FUN_00cf1500();            // 0x00cf1500 (thiscall)
extern "C" void   FUN_00b22960();            // 0x00b22960 cGNM2::ProcessPending (thiscall)
extern "C" void  *FUN_0067cab0();            // 0x0067cab0
extern "C" void   FUN_00801bb0();            // 0x00801bb0 CurMgr::FindLocal (thiscall)
extern "C" void  *FUN_00b3d230();            // 0x00b3d230
extern "C" void   FUN_00b5cde0();            // 0x00b5cde0 (thiscall)
extern "C" void  *SP_GetCameraCtl();         // 0x00b3d280
extern "C" void   FUN_00cf28f0();            // 0x00cf28f0 cCityInputStrategy::SetDefaultPickPriorities
extern "C" void   FUN_00b316d0();            // 0x00b316d0 (thiscall)
extern const float k42c80000;                // 0x13ec4d0 == 100.0f
extern const float kCamPitch789;             // 0x169cb78
extern const float kCamPitch77c;             // 0x169cb7c
extern const float kCamPitch780;             // 0x169cb80
extern const float kCamPitch784;             // 0x169cb84
extern const float kTwoj;       // 0x1470f1c == 2.0f
extern const float kThird;      // 0x13f26dc == 0.33333334f
extern const float kTwoThird;   // 0x140e87c == 0.6666667f
extern const float kNegThird;   // 0x140d0cc == -0.33333334f
// ---- items of slice s00cf6df0 end

// @ 0x00cf0e10
bool FUN_00cf0e10()
{
    return FUN_00b7c780() != 0;
}

// @ 0x00cf0eb0
void __stdcall FUN_00cf0eb0(u32 param_1)
{
    if (FUN_00b7c770() == param_1)
        FUN_00b7c810(1);
}

// @ 0x00cf0ed0
void cCityInputStrategy::FUN_00cf0ed0()
{
    void* gim = FUN_00b3d250();
    mField12c = ((u32 (__thiscall*)(void*))VT(gim)[0x34 / 4])(gim);
}

// @ 0x00cf0f10
void __stdcall FUN_00cf0f10(u32 param_1)
{
    (void)param_1;
    void* s = FUN_00cf74c0();
    if (s)
    {
        void* st = MOPS(s)->FUN_00cf74f0();
        if (st)
        {
            ((cCityInputStrategy*)st)->mField136 = 1;
            ((cCityInputStrategy*)st)->mField138 = 0x1510d07;
        }
    }
}

// @ 0x00cf0f40
void __stdcall FUN_00cf0f40(void* param_1, u32 param_2)
{
    void* s = FUN_00cf74c0();
    if (s)
    {
        void* st = MOPS(s)->FUN_00cf74f0();
        if (st)
            ((cCityInputStrategy*)st)->FUN_00cf0e20((u32)param_1, param_2);
    }
}

// @ 0x00cf6df0
void FUN_00cf6df0()
{
    void *gtm = GameTimeManager();
    typedef void (__thiscall *DecPauseFn)(void *self, u32 hash);
    ((DecPauseFn)FUN_00b32250)(gtm, 0x4bf38a7);
    while (*(u32 *)((u8 *)FUN_00b3d4f0() + 0x54) != 0) {
        typedef void (__thiscall *StepFn)(void *self, int v);
        ((StepFn)FUN_00e2f270)(FUN_00b3d4f0(), 0);
    }
}

// @ 0x00cf6e70
float FUN_00cf6e70()
{
    float local = 0.0f;
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    if (civ != 0) {
        float fVar6 = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0xa35d0f5);
        float fVar1 = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0x6aeb96a1);
        float fVar2 = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0x3360727f);
        if (fVar6 > fVar2 && fVar2 < fVar1) {
            float fVar7 = ((fVar1 / (fVar1 + fVar6)) * kTwoj) * kThird + kTwoThird;
            if (kOne < fVar7) {
                return (fVar2 / ((fVar2 + fVar1) + fVar6)) * kThird + (fVar7 - kTwoj);
            }
            return fVar7 - (fVar2 / ((fVar2 + fVar1) + fVar6)) * kThird;
        }
        if (fVar1 < fVar6 && fVar1 < fVar2) {
            float fVar7 = ((fVar6 / (fVar2 + fVar6)) * kTwoj) * kThird;
            float fVar6b = (fVar1 / ((fVar2 + fVar1) + fVar6)) * kThird;
            if (kThird < fVar7) {
                return fVar6b + fVar7;
            }
            return fVar7 - fVar6b;
        }
        if (fVar6 < fVar1 && fVar6 < fVar2) {
            float fVar7 = -(((fVar1 / (fVar2 + fVar1)) * kTwoj) * kThird);
            float fVar6b = (fVar6 / ((fVar2 + fVar1) + fVar6)) * kThird;
            if (fVar7 < kNegThird) {
                return fVar7 - fVar6b;
            }
            return fVar6b + fVar7;
        }
        if (0.0f < fVar6) {
            return kTwoThird;
        }
        if (0.0f < fVar1) {
            local = -kTwoThird;
        }
    }
    return local;
}

// @ 0x00cf7090
float FUN_00cf7090()
{
    float result = kCivRatioConst;
    void *civ = ((void *(__thiscall *)(void *))GetPlayerCivilization)(SP_NounManager());
    if (civ == 0) {
        return result;
    }
    float a = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0xa35d0f5);
    float b = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0x6aeb96a1);
    float c = ((float (__thiscall *)(void *, u32))FUN_00bf1880)(civ, 0x3360727f);
    float lo1 = (b > a) ? a : b;
    float m = (c > lo1) ? lo1 : c;
    result = m;
    if (m > kZero) {
        result = m / (c + b + a);
    }
    return result;
}

// @ 0x00cf71d0
void __fastcall FUN_00cf71d0(void *self, void * /*edx*/, u32 arg)
{
    u8 *s = (u8 *)self;
    if (*(void **)(s + 0xe8) == 0) {
        void *p = ((void *(__cdecl *)(u32, const char *, int, int, int, int))g_opNew)(
            0x148, "Simulator/cCityInputStrategy", 0, 0, 0, 0);
        if (p != 0) {
            typedef void *(__thiscall *CtorFn)(void *, void *);
            p = ((CtorFn)FUN_00cf4ca0)(p, self);
        }
        *(void **)(s + 0xe8) = p;
    }
    void *in = *(void **)(s + 0xe8);
    if (in != 0) {
        ((void (__thiscall *)(void *))(*(void ***)in)[1])(in);
        if (arg == 0xdbdba1) {
            ((void (__thiscall *)(void *))FUN_00cf14d0)(*(void **)(s + 0xe8));
        }
        void *cfg = SP_ConfigManager();
        u32 q = ((u32 (__thiscall *)(void *, u32))(*(void ***)cfg)[0x30 / 4])(cfg, 0x679b873);
        ((void (__thiscall *)(void *, u32))FUN_00cf4c00)(*(void **)(s + 0xe8), q);
    }
    void *gim = GameInputManager();
    ((void (__thiscall *)(void *, void *, int, int))(*(void ***)gim)[0x20 / 4])(
        gim, (u8 *)*(void **)(s + 0xe8) + 4, 0, 0);
    ((void (__thiscall *)(void *))FUN_00b22960)(SP_NounManager());
    if (*(void **)(s + 0xec) == 0) {
        void *p = ((void *(__cdecl *)(u32, const char *, int, int, int, int))g_opNew)(
            0x120, "Simulator/cCityDisplayStrategy", 0, 0, 0, 0);
        if (p != 0) {
            typedef void *(__thiscall *CtorFn)(void *, void *);
            p = ((CtorFn)FUN_00ceb090)(p, self);
        }
        *(void **)(s + 0xec) = p;
        ((void (__thiscall *)(void *))FUN_00cea090)(p);
    }
    if (arg != 0xdbdba1) {
        ((void (__thiscall *)(void *, int))FUN_00cf1500)(*(void **)(s + 0xe8), 1);
    }
    void *cm = FUN_0067cab0();
    ((void (__thiscall *)(void *, u32))FUN_00801bb0)(cm, 0x1002);
    void *v = FUN_00b3d230();
    ((void (__thiscall *)(void *, u32))FUN_00b5cde0)(v, 0xe3057616);
    void *cam = SP_GetCameraCtl();
    *(float *)((u8 *)cam + 0x380) = k42c80000;
    cam = SP_GetCameraCtl();
    *(u32 *)((u8 *)cam + 0x384) = 0x3e9;
    ((void (__thiscall *)(void *))FUN_00cf28f0)(*(void **)(s + 0xe8));
    ((void (__thiscall *)(void *, float, float, float, float))FUN_00b316d0)(
        GameTimeManager(), kCamPitch789, kCamPitch77c, kCamPitch780, kCamPitch784);
}
