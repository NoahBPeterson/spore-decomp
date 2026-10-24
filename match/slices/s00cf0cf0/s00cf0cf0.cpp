// s00cf0cf0 -- SP city-strategy helpers: game tuning property fetch, modal-window
//               end handling, camera/menu plumbing, the ref-counted pointer list
//               sort/insert helpers and the object-placement / weapon-mode paths.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

#include <math.h>
#include <intrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     i32;
typedef float          f32;

#pragma warning(disable: 4100)

#define MOPS(p) ((COps*)(p))
#define VT(p)   (*(void***)(p))

static inline void Release(void* p)
{
    if (p) { void** vt = *(void***)p; ((void (__thiscall*)(void*))vt[1])(p); }
}

// ---------------------------------------------------------------------------
// callees that are plain (non-ecx) functions in the original binary
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067de30();                                     // 0x0067de30
void* __cdecl FUN_0067dcc0();                                     // 0x0067dcc0
void* __cdecl FUN_0067dcd0();                                     // 0x0067dcd0
u8    __cdecl FUN_00b7c780();                                     // 0x00b7c780
u32   __cdecl FUN_00b7c770();                                     // 0x00b7c770
void  __cdecl FUN_00b7c810(u32 a);                                // 0x00b7c810
void* __cdecl FUN_00a206f0();                                     // 0x00a206f0
void  __cdecl FUN_00435ed0(void* a, u32 b);                       // 0x00435ed0
void* __cdecl FUN_00b3d250();                                     // 0x00b3d250
void* __cdecl FUN_00b3d380();                                     // 0x00b3d380
void* __cdecl FUN_00cf74c0();                                     // 0x00cf74c0
void* __cdecl FUN_00ce8cf0();                                     // 0x00ce8cf0
void* __cdecl FUN_00b30d70();                                     // 0x00b30d70
void* __cdecl FUN_00b3d300();                                     // 0x00b3d300
void* __cdecl FUN_00b3d280();                                     // 0x00b3d280
u8    __cdecl FUN_00ac0730(void* a, void* b);                     // 0x00ac0730
void* __cdecl FUN_00b3d230();                                     // 0x00b3d230
void  __cdecl FUN_00d12fc0();                                     // 0x00d12fc0
void  __cdecl FUN_00571db0(u32 a, u32 b, u32 c, u32 d, u32 e);    // 0x00571db0
void* __cdecl FUN_00883860();                                     // 0x00883860
u32   __cdecl FUN_00b5b800();                                     // 0x00b5b800
void  __cdecl FUN_008d2f30(void* a, void* b);                     // 0x008d2f30
void* __cdecl FUN_00b3d240();                                     // 0x00b3d240
void* __cdecl FUN_00b3d350();                                     // 0x00b3d350
void  __cdecl FUN_00be1ef0(void* a, u32 b);                       // 0x00be1ef0
f32*  __cdecl FUN_0041ea70();                                     // 0x0041ea70

extern u32 gEditorCursor[3];                        // 0x0169cc8c
extern u32 gTmpVecA[3];                             // 0x0169d258
extern u32 gTmpVecB[3];                             // 0x0169d264
extern u32 gCursorPosA;                             // 0x0169cc78
extern u32 gCursorPosB;                             // 0x0169cc7c
extern u8  gEditorModeFlag;                         // 0x0167ade8
extern u32 gFlag0169cc88;                           // 0x0169cc88
extern u32 gCityTuning;                             // 0x0169ca60

// ---------------------------------------------------------------------------
// callees invoked with ecx == an object pointer (free-function form)
// ---------------------------------------------------------------------------
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
// ---------------------------------------------------------------------------
// structs
// ---------------------------------------------------------------------------
struct Vec3
{
    f32 x;
    f32 y;
    f32 z;
};

struct cCityGameTuning
{
    u8  pad0[0x84];              // +0x0000
    f32 mEntertainmentThreshold; // +0x0084
    f32 mProtestDuration;        // +0x0088
    f32 mLurkDuration;           // +0x008c

    void FUN_00cf0cf0();
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

// ---------------------------------------------------------------------------
// 0x00cf0cf0  cCityGameTuning::SwitchToCivMode
// ---------------------------------------------------------------------------
// @ 0x00cf0cf0
void cCityGameTuning::FUN_00cf0cf0()
{
    void* prop = 0;
    void* mgr = FUN_0067de30();
    if (prop)
    {
        void* old = prop;
        prop = 0;
        ((void (__thiscall*)(void*))VT(old)[1])(old);
    }
    if (!((u8 (__thiscall*)(void*, u32, void**))VT(mgr)[0x30 / 4])(mgr, 0xb6a5c63d, &prop))
    {
        if (prop)
            Release(prop);
        return;
    }
    if (!prop)
        return;
    void* sub;
    if (((u8 (__thiscall*)(void*, u32, void**))VT(prop)[0x24 / 4])(prop, 0x1ac13b9, &sub)
        && *(u16*)((u8*)sub + 0x12) == 0xd)
    {
        mEntertainmentThreshold = *FUN_0041ea70();
    }
    if (prop)
    {
        if (((u8 (__thiscall*)(void*, u32, void**))VT(prop)[0x24 / 4])(prop, 0x1ac13ba, &sub)
            && *(u16*)((u8*)sub + 0x12) == 0xd)
        {
            mProtestDuration = *FUN_0041ea70();
        }
        if (prop)
        {
            if (((u8 (__thiscall*)(void*, u32, void**))VT(prop)[0x24 / 4])(prop, 0x1ac13bb, &sub)
                && *(u16*)((u8*)sub + 0x12) == 0xd)
            {
                mLurkDuration = *FUN_0041ea70();
            }
        }
    }
    if (prop)
        Release(prop);
}

// ---------------------------------------------------------------------------
// 0x00cf0e10
// ---------------------------------------------------------------------------
// @ 0x00cf0e10
bool FUN_00cf0e10()
{
    return FUN_00b7c780() != 0;
}

// ---------------------------------------------------------------------------
// 0x00cf0e20
// ---------------------------------------------------------------------------
// @ 0x00cf0e20
void cCityInputStrategy::FUN_00cf0e20(u32 param_1, u32 param_2)
{
    (void)param_1;
    mField138 = param_2;
    if (param_2 == 0x5107b1a)
    {
        void* ms = FUN_0067dcc0();
        ((void (__thiscall*)(void*, u32, u32, u32))VT(ms)[0x14 / 4])(ms, 0x37033e2, 0, 0);
        void* gim = FUN_00b3d250();
        ((void (__thiscall*)(void*, u32, u32))VT(gim)[0x64 / 4])(gim, 0x4e540ec, 1);
    }
    else
    {
        void* au = FUN_00a206f0();
        u32 v = au ? ((u32 (__thiscall*)(void*))VT(au)[0x20 / 4])(au) : 0;
        FUN_00435ed0((void*)0xade45080, v);
        void* gim = FUN_00b3d250();
        ((void (__thiscall*)(void*, u32, u32))VT(gim)[0x64 / 4])(gim, 0x4e540ed, 1);
    }
    MOPS(FUN_00b3d380())->FUN_00b32250(0x4bf38a7);
    mField136 = 0;
}
// ---------------------------------------------------------------------------
// 0x00cf0eb0
// ---------------------------------------------------------------------------
// @ 0x00cf0eb0
void __stdcall FUN_00cf0eb0(u32 param_1)
{
    if (FUN_00b7c770() == param_1)
        FUN_00b7c810(1);
}

// ---------------------------------------------------------------------------
// 0x00cf0ed0
// ---------------------------------------------------------------------------
// @ 0x00cf0ed0
void cCityInputStrategy::FUN_00cf0ed0()
{
    void* gim = FUN_00b3d250();
    mField12c = ((u32 (__thiscall*)(void*))VT(gim)[0x34 / 4])(gim);
}

// ---------------------------------------------------------------------------
// 0x00cf0f10
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00cf0f40
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00cf0f80
// ---------------------------------------------------------------------------
// @ 0x00cf0f80
u32 __stdcall FUN_00cf0f80(void* param_1, void* param_2)
{
    (void)param_1;
    (void)param_2;
    MOPS(FUN_00cf74c0())->FUN_00cf7470(1);
    if (FUN_00ce8cf0())
    {
        MOPS(FUN_00ce8cf0())->FUN_00cec7a0(1);
    }
    void* cur = FUN_00b30d70();
    u8* base = (u8*)*(void**)cur;
    u32 v = MOPS(MOPS(FUN_00b3d300())->FUN_00b25fb0())->FUN_00b2fa60();
    ((void (__thiscall*)(void*, u32))*(void**)(base + 0x58))(cur, v);
    ((cCityGameTuning*)&gCityTuning)->FUN_00cf0cf0();
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf0fe0
// ---------------------------------------------------------------------------
// @ 0x00cf0fe0
u32 cCityInputStrategy::FUN_00cf0fe0()
{
    if ((mFieldc0 | mFieldc4) != 0)
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf1000
// ---------------------------------------------------------------------------
// @ 0x00cf1000
u32 cCityInputStrategy::FUN_00cf1000(void* param_1, u32 param_2)
{
    (void)param_1;
    void* cam = FUN_00b3d280();
    void* city;
    if (param_2 == 1)
    {
        city = MOPS(FUN_00b3d300())->FUN_00b25c30();
    }
    else
    {
        city = (void*)MOPS(mField4c)->FUN_00cfb610(param_2 - 1);
    }
    if (city && cam)
    {
        void* sub = (u8*)city + 0x120;
        u32 a = ((u32 (__thiscall*)(void*, u32, u32))VT(sub)[0x2c / 4])(sub, 1, 0);
        MOPS(cam)->FUN_00b146a0(a);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf1060
// ---------------------------------------------------------------------------
// @ 0x00cf1060
u32 __stdcall FUN_00cf1060(void* param_1, u32 param_2)
{
    (void)param_1;
    FUN_00b7c810(1);
    if (param_2 == 8)
    {
        void* cur = FUN_00b30d70();
        ((void (__thiscall*)(void*))VT(cur)[0x64 / 4])(cur);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf10d0
// ---------------------------------------------------------------------------
// @ 0x00cf10d0
void __cdecl FUN_00cf10d0(void** param_1, void** param_2)
{
    if (param_1 == param_2)
        return;
    void** p = param_1 + 1;
    if (p == param_2)
        return;
    do
    {
        void* val = *p;
        if (val)
            (**(void (__thiscall***)(void*))val)(val);
        void** q = p;
        while (q != param_1)
        {
            void* prev = *(q - 1);
            u8 less = FUN_00ac0730(val ? (void*)((u8*)val + 0x34) : 0,
                                   prev ? (void*)((u8*)prev + 0x34) : 0);
            if (!less)
                break;
            void* a = *(q - 1);
            void* b = *q;
            if (a != b)
            {
                if (a)
                    (**(void (__thiscall***)(void*))a)(a);
                *q = a;
                if (b)
                    Release(b);
            }
            q--;
        }
        void* b = *q;
        if (val != b)
        {
            if (val)
                (**(void (__thiscall***)(void*))val)(val);
            *q = val;
            if (b)
                Release(b);
        }
        if (val)
            Release(val);
        p++;
    } while (p != param_2);
}

// ---------------------------------------------------------------------------
// 0x00cf11b0
// ---------------------------------------------------------------------------
// @ 0x00cf11b0
void __cdecl FUN_00cf11b0(void** param_1, void** param_2)
{
    for (; param_1 != param_2; param_1++)
    {
        void* val = *param_1;
        void** q = param_1;
        if (val)
            (**(void (__thiscall***)(void*))val)(val);
        for (;;)
        {
            void* prev = *(q - 1);
            u8 less = FUN_00ac0730(val ? (void*)((u8*)val + 0x34) : 0,
                                   prev ? (void*)((u8*)prev + 0x34) : 0);
            if (!less)
                break;
            void* a = *(q - 1);
            void* b = *q;
            if (a != b)
            {
                if (a)
                    (**(void (__thiscall***)(void*))a)(a);
                *q = a;
                if (b)
                    Release(b);
            }
            q--;
        }
        void* b = *q;
        if (val != b)
        {
            if (val)
                (**(void (__thiscall***)(void*))val)(val);
            *q = val;
            if (b)
                Release(b);
        }
        if (val)
            Release(val);
    }
}

// ---------------------------------------------------------------------------
// 0x00cf1280
// ---------------------------------------------------------------------------
// @ 0x00cf1280
void** __cdecl FUN_00cf1280(void** param_1, void** param_2, void** param_3)
{
    u8 r = FUN_00ac0730(*param_1 ? (void*)((u8*)*param_1 + 0x34) : 0,
                        *param_2 ? (void*)((u8*)*param_2 + 0x34) : 0);
    if (r)
    {
        if (FUN_00ac0730(*param_3 ? (void*)((u8*)*param_3 + 0x34) : 0,
                         *param_2 ? (void*)((u8*)*param_2 + 0x34) : 0))
        {
            return param_2;
        }
        if (FUN_00ac0730(*param_3 ? (void*)((u8*)*param_3 + 0x34) : 0,
                         *param_1 ? (void*)((u8*)*param_1 + 0x34) : 0))
        {
            return param_3;
        }
        return param_1;
    }
    if (FUN_00ac0730(*param_3 ? (void*)((u8*)*param_3 + 0x34) : 0,
                     *param_1 ? (void*)((u8*)*param_1 + 0x34) : 0))
    {
        return param_1;
    }
    if (FUN_00ac0730(*param_2 ? (void*)((u8*)*param_2 + 0x34) : 0,
                     *param_3 ? (void*)((u8*)*param_3 + 0x34) : 0))
    {
        return param_3;
    }
    return param_2;
}

// ---------------------------------------------------------------------------
// 0x00cf1380
// ---------------------------------------------------------------------------
// @ 0x00cf1380
void __cdecl FUN_00cf1380(void** param_1, i32 param_2, i32 param_3, void* param_4)
{
    i32 iVar4 = param_3;
    while (param_2 < iVar4)
    {
        i32 iParent = (iVar4 - 1) >> 1;
        void* at = param_1[iParent];
        u8 less = FUN_00ac0730(at ? (void*)((u8*)at + 0x34) : 0,
                               param_4 ? (void*)((u8*)param_4 + 0x34) : 0);
        if (!less)
            break;
        void* a = param_1[iParent];
        void* b = param_1[iVar4];
        if (a != b)
        {
            if (a)
                (**(void (__thiscall***)(void*))a)(a);
            param_1[iVar4] = a;
            if (b)
                Release(b);
        }
        iVar4 = iParent;
    }
    void* b = param_1[iVar4];
    if (param_4 != b)
    {
        if (param_4)
            (**(void (__thiscall***)(void*))param_4)(param_4);
        param_1[iVar4] = param_4;
        if (b)
            Release(b);
    }
    if (param_4)
        Release(param_4);
}

// ---------------------------------------------------------------------------
// 0x00cf1440
// ---------------------------------------------------------------------------
// @ 0x00cf1440
void cCityInputStrategy::FUN_00cf1440()
{
    void* mgr = FUN_00b3d230();
    ((void (__thiscall*)(void*, void*))VT(mgr)[0x40 / 4])(mgr, mFielde4);
    if (mpField80)
    {
        FUN_00d12fc0();
        void* p = mpField80;
        if (p)
        {
            mpField80 = 0;
            ((void (__thiscall*)(void*))VT(p)[0x0c / 4])(p);
        }
    }
    if (mpHandler)
    {
        u32 h = mpHandler;
        mpHandler = 0;
        FUN_00571db0(h, mField70, mField74, mField78, mField7c);
    }
    gFlag0169cc88 = 0;
    void* ms = FUN_00883860();
    ((void (__thiscall*)(void*, void*, u32, u32))VT(ms)[0x14 / 4])(ms, (void*)0x0158cd75, 0, 0);
    mField48 = 0;
}

// ---------------------------------------------------------------------------
// 0x00cf14d0
// ---------------------------------------------------------------------------
// @ 0x00cf14d0
void cCityInputStrategy::FUN_00cf14d0()
{
    if (mFielde4)
    {
        void* mgr = FUN_00b3d230();
        ((void (__thiscall*)(void*, void*, u32))VT(mgr)[0x38 / 4])(mgr, mFielde4, 1);
    }
}

// ---------------------------------------------------------------------------
// 0x00cf1500
// ---------------------------------------------------------------------------
// @ 0x00cf1500
void cCityInputStrategy::FUN_00cf1500(u32 param_1)
{
    if (FUN_00b5b800() == (u32)&gEditorCursor[0])
    {
        MOPS(mFielde4)->FUN_00e34ea0((void*)param_1);
        void* a = FUN_00cf74c0();
        void* b = MOPS(a)->FUN_00cf7500();
        MOPS(b)->FUN_00ce8ee0(param_1);
    }
}

// ---------------------------------------------------------------------------
// 0x00cf1540
// ---------------------------------------------------------------------------
// @ 0x00cf1540
u32 cCityInputStrategy::FUN_00cf1540()
{
    void* p = mpField80;
    if (p)
    {
        if (MOPS(p)->FUN_00d09660())
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf1560
// ---------------------------------------------------------------------------
// @ 0x00cf1560
u32 __stdcall FUN_00cf1560(void* param_1, u32 param_2)
{
    volatile bool uVar3 = 0;
    switch (param_2)
    {
    case 0:
        uVar3 = 1;
        break;
    case 1:
        MOPS(FUN_00b30d70())->FUN_00b2fba0(2);
        break;
    case 2:
        MOPS(FUN_00b30d70())->FUN_00b2fba0(0);
        break;
    case 3:
        MOPS(FUN_00b30d70())->FUN_00b2fba0(1);
        break;
    default:
        break;
    }
    u32 uVar1 = param_1 ? ((u32 (__thiscall*)(void*, void*))VT(param_1)[0x0c / 4])(param_1, (void*)0x01186577) : 0;
    void* cur = FUN_00b30d70();
    ((void (__thiscall*)(void*, u32, u32))VT(cur)[0xa0 / 4])(cur, uVar3, uVar1);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf15e0
// ---------------------------------------------------------------------------
// @ 0x00cf15e0
u32 __stdcall FUN_00cf15e0(void* param_1, u32 param_2)
{
    if (param_2 == 0)
    {
        MOPS(FUN_00b30d70())->FUN_00b2fba0(0);
    }
    void* cur = FUN_00b30d70();
    u32 uVar2 = param_1 ? ((u32 (__thiscall*)(void*, void*))VT(param_1)[0x0c / 4])(param_1, (void*)0x01186577) : 0;
    ((void (__thiscall*)(void*, u32, u32))VT(cur)[0x9c / 4])(cur, 0, uVar2);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf1630
// ---------------------------------------------------------------------------
// @ 0x00cf1630
u32 cCityInputStrategy::FUN_00cf1630(void* param_1)
{
    u32 uVar1 = param_1 ? ((u32 (__thiscall*)(void*, void*))VT(param_1)[0x0c / 4])(param_1, (void*)0x01186577) : 0;
    mpField104 = (void*)uVar1;
    FUN_008d2f30((void*)&gCursorPosB, (void*)&gCursorPosA);
    void* pm = FUN_00b3d240();
    Vec3 tmp;
    f32* out = (f32*)((u32* (__thiscall*)(void*, Vec3*, u32, Vec3))VT(pm)[0x38 / 4])(
        pm, &tmp, 0, *(Vec3*)&gEditorCursor[0]);
    gTmpVecA[0] = ((u32*)out)[0];
    gTmpVecA[1] = ((u32*)out)[1];
    gTmpVecA[2] = ((u32*)out)[2];
    void* p = mpField104;
    f32* out2 = (f32*)((u32* (__thiscall*)(void*))VT(p)[0x2c / 4])(p);
    gTmpVecB[0] = ((u32*)out2)[0];
    gTmpVecB[1] = ((u32*)out2)[1];
    gTmpVecB[2] = ((u32*)out2)[2];
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf16f0
// ---------------------------------------------------------------------------
// @ 0x00cf16f0
u32 cCityInputStrategy::FUN_00cf16f0(void* param_1, void* param_2)
{
    (void)param_1;
    (void)param_2;
    void* a = 0;
    if (mpField104)
        a = (void*)((u32 (__thiscall*)(void*, u32))VT(mpField104)[0xb8 / 4])(mpField104, 0x1007ae63);
    void* b = 0;
    if (mpField104)
        b = (void*)((u32 (__thiscall*)(void*, u32))VT(mpField104)[0xb8 / 4])(mpField104, 0xe9cb8ba);
    void* c = 0;
    if (mpField104)
        c = (void*)((u32 (__thiscall*)(void*, u32))VT(mpField104)[0xb8 / 4])(mpField104, 0x175cdc9);
    if (a)
        return 2;
    if (b)
    {
        if (!((u8 (__thiscall*)(void*))VT((u8*)b + 0x34)[0x58 / 4])((u8*)b + 0x34))
            return 2;
        if (!c)
            goto LAB;
    }
    else if (!c)
    {
        return 2;
    }
    if (!((u8 (__thiscall*)(void*))VT((u8*)c + 0x70)[0x58 / 4])((u8*)c + 0x70))
        return 2;
LAB:
    if (!mpField104)
        return 1;
    ((cCityInputStrategy*)mpField104)->mFlag72 = 1;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf17b0
// ---------------------------------------------------------------------------
// @ 0x00cf17b0
u32 cCityInputStrategy::FUN_00cf17b0(void* param_1, void* param_2)
{
    (void)param_1;
    (void)param_2;
    void* cam = FUN_00b3d280();
    if (cam)
    {
        if (mFieldc0 | mFieldc4)
            MOPS(mFielde4)->FUN_00e352c0();
        if (mFieldc0 | mFieldc4)
        {
            MOPS(cam)->FUN_00b0f950(1);
            return 0;
        }
        MOPS(cam)->FUN_00b0f950(0);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf1810
// ---------------------------------------------------------------------------
// @ 0x00cf1810
void cCityInputStrategy::FUN_00cf1810(void* param_1, u8 param_2)
{
    if (param_2)
    {
        mFieldc0 = 0;
        mFieldc4 = 0;
        mFieldc8 = 0;
        mFieldcc = 0;
        if (mpFieldd8)
        {
            void* p = mpFieldd8;
            mpFieldd8 = 0;
            Release(p);
        }
    }
    else
    {
        MOPS(&mFieldc0)->FUN_00571e80();
        if (param_1)
        {
            u32 r = ((u32 (__thiscall*)(void*, u32))VT(param_1)[0x0c / 4])(param_1, 0xed7fc07);
            if (r == 0)
                MOPS(&mpFieldd8)->FUN_00b5f950(param_1);
        }
    }
    MOPS(FUN_00cf74c0())->FUN_00cf8d70(0);
}

// ---------------------------------------------------------------------------
// 0x00cf18b0
// ---------------------------------------------------------------------------
// @ 0x00cf18b0
u32 cCityInputStrategy::FUN_00cf18b0(void* param_1, void* param_2)
{
    (void)param_1;
    (void)param_2;
    if (mpField104)
    {
        void* pm = FUN_00b3d240();
        Vec3 origin = { *(f32*)&gEditorCursor[0], *(f32*)&gEditorCursor[1], *(f32*)&gEditorCursor[2] };
        Vec3 out;
        ((void (__thiscall*)(void*, Vec3*, u32, Vec3))VT(pm)[0x38 / 4])(pm, &out, 0, origin);
        if (out.x * out.x + out.y * out.y + out.z * out.z > 0.0f)
        {
            Vec3 t;
            t.x = out.x - *(f32*)&gTmpVecA[0] + *(f32*)&gTmpVecB[0];
            t.y = out.y - *(f32*)&gTmpVecA[1] + *(f32*)&gTmpVecB[1];
            t.z = out.z - *(f32*)&gTmpVecA[2] + *(f32*)&gTmpVecB[2];
            Vec3 pos;
            Vec3 dir;
            MOPS(FUN_00b3d350())->FUN_00b815a0(&pos, &dir, &t);
            void* sel = mpField104;
            ((void (__thiscall*)(void*, Vec3*))VT(sel)[0x38 / 4])(sel, &dir);
            u32 r = ((u32 (__thiscall*)(void*))VT(sel)[0x30 / 4])(sel);
            MOPS(FUN_00b3d350())->FUN_00b7f1f0(&t, &dir, r);
            ((void (__thiscall*)(void*, u32))VT(sel)[0x3c / 4])(sel, r);
            ((cCityInputStrategy*)mpField104)->mFlag72 = 0;
        }
    }
    mpField104 = 0;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf1aa0
// ---------------------------------------------------------------------------
// @ 0x00cf1aa0
u32 __stdcall FUN_00cf1aa0(void* param_1, void* param_2)
{
    (void)param_2;
    if (param_1)
    {
        void* p = (void*)((u32 (__thiscall*)(void*, u32))VT(param_1)[0x0c / 4])(param_1, 0x4f396a66);
        if (p)
            ((void (__thiscall*)(void*, u32))VT(p)[0x98 / 4])(p, 1);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf1ad0
// ---------------------------------------------------------------------------
// @ 0x00cf1ad0
u32 cCityInputStrategy::FUN_00cf1ad0(void* param_1, void* param_2)
{
    (void)param_1;
    (void)param_2;
    FUN_00b7c810(1);
    mFieldc0 = 0;
    mFieldc4 = 0;
    mFieldc8 = 0;
    mFieldcc = 0;
    void* p = mpFieldd8;
    if (p)
    {
        mpFieldd8 = 0;
        Release(p);
    }
    MOPS(FUN_00cf74c0())->FUN_00cf8d70(0);
    void* cam = FUN_00b3d280();
    if (cam)
        MOPS(cam)->FUN_00b10c40(0);
    void* cur = FUN_00b30d70();
    void* strat = FUN_00cf74c0();
    i32 n = ((i32 (__thiscall*)(void*))VT(cur)[0x70 / 4])(cur);
    if (n <= 0
        && !((u8 (__thiscall*)(void*))VT(cur)[0xa8 / 4])(cur)
        && !MOPS(strat)->FUN_00c44f10()
        && !gEditorModeFlag
        && mField140 == -1)
    {
        void* ms = FUN_0067dcc0();
        ((void (__thiscall*)(void*, u32, u32, u32))VT(ms)[0x14 / 4])(ms, 0x64eb18e, 0, 0);
        return 0;
    }
    ((void (__thiscall*)(void*))VT(cur)[0x64 / 4])(cur);
    ((void (__thiscall*)(void*, u32))VT(cur)[0xb8 / 4])(cur, 0);
    ((void (__thiscall*)(void*))VT(cur)[0xa4 / 4])(cur);
    MOPS(strat)->FUN_00cf8d70(0);
    gEditorModeFlag = 0;
    mField140 = -1;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00cf1be0
// ---------------------------------------------------------------------------
// @ 0x00cf1be0
void cCityInputStrategy::FUN_00cf1be0(i32 param_1)
{
    if (mField140 == param_1)
        return;
    void* noun = FUN_00b3d300();
    void* civ = MOPS(noun)->FUN_00b25fb0();
    if (!civ)
        return;
    if (!MOPS(civ)->FUN_00bf8a00((u32)param_1))
        return;
    switch (param_1)
    {
    case 2:
    case 5:
    case 8:
        mField140 = param_1;
        FUN_00cf1ad0(0, 0);
        MOPS(civ)->FUN_00bf8a70((u32)param_1, (void*)&gEditorCursor[0]);
        mField140 = -1;
        break;
    default:
        mField140 = param_1;
        FUN_00cf1ad0(0, 0);
        mField140 = param_1;
        {
            void* gim = FUN_00b3d250();
            ((void (__thiscall*)(void*, u32, u32))VT(gim)[0x64 / 4])(gim, 0x58b3913, 1);
        }
        break;
    }
    MOPS(MOPS(FUN_00cf74c0())->FUN_00cf7500())->FUN_00ce96b0(0);
}
