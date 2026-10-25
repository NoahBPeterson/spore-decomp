// src/game/SPGonzago/SPCityInputStrategy.cpp -- migrated from slice(s) s00e34290, s00cf4660, s00cf1ca0, s00cf0cf0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityInputStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>
#include "SP/cSPCreatureCitizen.h"
#include "SP/cPlanet.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#pragma warning(disable: 4100)

// ---- items of slice s00cf0cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef signed int     i32;
typedef float          f32;
#define MOPS(p) ((COps*)(p))
#define VT(p)   (*(void***)(p))
static inline void Release(void* p)
{
    if (p) { void** vt = *(void***)p; ((void (__thiscall*)(void*))vt[1])(p); }
}
void* __cdecl FUN_0067dcc0();                                     // 0x0067dcc0
void  __cdecl FUN_00b7c810(u32 a);                                // 0x00b7c810
void* __cdecl FUN_00a206f0();                                     // 0x00a206f0
void  __cdecl FUN_00435ed0(void* a, u32 b);                       // 0x00435ed0
void* __cdecl FUN_00b3d250();                                     // 0x00b3d250
void* __cdecl FUN_00b3d380();                                     // 0x00b3d380
void* __cdecl FUN_00cf74c0();                                     // 0x00cf74c0
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
extern u32 gEditorCursor[3];                        // 0x0169cc8c
extern u32 gTmpVecA[3];                             // 0x0169d258
extern u32 gTmpVecB[3];                             // 0x0169d264
extern u32 gCursorPosA;                             // 0x0169cc78
extern u32 gCursorPosB;                             // 0x0169cc7c
extern u8  gEditorModeFlag;                         // 0x0167ade8
extern u32 gFlag0169cc88;                           // 0x0169cc88
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
struct Vec3
{
    f32 x;
    f32 y;
    f32 z;
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

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32 gEditorCursor[3];                        // 0x0169cc8c
extern u32 gTmpVecA[3];                             // 0x0169d258
extern u32 gTmpVecB[3];                             // 0x0169d264
extern u32 gCursorPosA;                             // 0x0169cc78
extern u32 gCursorPosB;                             // 0x0169cc7c
extern u8  gEditorModeFlag;                         // 0x0167ade8
extern u32 gFlag0169cc88;                           // 0x0169cc88

// ---- items of slice s00cf1ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl GetGameTerrainCursor();                  // 0x00b30d70 SP::GetGameTerrainCursor
extern "C" void* __cdecl FUN_00b3d290();                          // 0x00b3d290
extern "C" void* __cdecl FUN_00b3d320();                          // 0x00b3d320
extern "C" void* __cdecl FUN_00ac15e0(void* o);                   // 0x00ac15e0
extern "C" void  __cdecl FUN_00afba10(void* o);                   // 0x00afba10
extern "C" int   __cdecl FUN_00af9dd0(float f, int n);            // 0x00af9dd0
extern "C" void  __cdecl FUN_00af9cf0(float* center, float r, float* facing, float altitude);  // cActionCircle::SetAtCenter
extern "C" void  __cdecl FUN_00afef10(int a, float f);            // 0x00afef10
extern "C" void* __cdecl FUN_00af1450(void* o);                   // TimerOwner::Add
extern "C" void  __cdecl FUN_00b535d0(void* pos, const void* val);  // 0x00b535d0 vector insert
extern "C" void  __cdecl FUN_00b2af00(void* a, void* b);          // 0x00b2af00 swap
extern "C" void  __cdecl FUN_00b1dfc0(void* o);                   // 0x00b1dfc0
extern "C" void  __cdecl FUN_00cf1380(void* base, int dummy, int pos);     // 0x00cf1380 heap-replace
extern "C" void  __cdecl FUN_00cf1e70(int* a, int* b, float f, float g, float h);  // 0x00cf1e70
extern "C" void  __cdecl FUN_00cf1ee0(int* a, int* b, float f, float g, float h);  // 0x00cf1ee0
extern "C" void* __cdecl FUN_00cf7500(void* o);                   // 0x00cf7500
extern "C" void* __cdecl FUN_00579a90(const wchar_t* s);          // 0x00579a90 RangeInitialize
extern "C" void* __cdecl FUN_0067cab0(int id);                    // 0x0067cab0
extern "C" void  __cdecl FUN_00f47380(void* p);                   // ??3 operator delete
extern "C" void  __cdecl FUN_00e25bd0(void* vec, void* first, void* last);  // vector::erase
extern "C" void* __cdecl FUN_00b7f190(void* planet, void* out, const void* pos);  // BuildSurfaceOrientation
extern float gZeroF;              // 0x01485378  0.0f
#pragma warning(disable : 4100)
extern "C" void  __cdecl FUN_00b11870(void* cam, u32 id);         // 0x00b11870
extern "C" char  __cdecl FUN_00801bb0(void* mgr, u32 id);         // 0x00801bb0 CurMgr::FindLocal
extern "C" void* __cdecl FUN_00f473a0(u32 size, const char* file, int a, int b, int c, int d);  // EAAllocate
struct Vec3_s00cf_1ca0 { float x, y, z; };
extern Vec3_s00cf_1ca0  gSurfaceDir;         // 0x0169d2ac
namespace SP {
class AutoRefCount
{
  public:
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
};
}
namespace SP {
class WStr
{
  public:
    u32* mBegin;                        // +0x00
    u32* mEnd;                          // +0x04
    u32* mCap;                          // +0x08

    void Init(const wchar_t* s) {
        mBegin = 0; mEnd = 0; mCap = 0;
        RangeInit(s);
    }
    void RangeInit(const wchar_t* s);   // 0x00579a90 (thiscall on this)
    void Release() {
        int cnt = (int)((char*)mEnd - (char*)mBegin);
        cnt &= 0xfffffffe;
        if (cnt > 2 && mBegin != 0) {
            FUN_00f47380(mBegin);
        }
    }
};
}
namespace SP {
void WStr::RangeInit(const wchar_t* s) { FUN_00579a90(s); }
}
namespace SP {
void __fastcall FUN_00cf1ca0(void* ecx_this, void* edx, int first, int last, int pos,
                             AutoRefCount* pivot, int a, int b);
}
namespace SP {
class cCityInputStrategy_s00cf_1ca0
{
  public:
    bool RestoreCommunityEditorOrShopping(int id);          // 0x00cf1f50 (ret 4)
    bool EndSelection(const Vec3_s00cf_1ca0* dir, const void* picked);  // 0x00cf2520 (ret 0xc)
    void SetDefaultPickPriorities();                        // 0x00cf28f0

    unsigned char pad000[0x80];
    int  mAutoHandlerPriority;          // 0x080
    unsigned char pad084[0xfc - 0x84];
    void* mpCreatureSelected;           // 0x0fc
};
}
namespace SP {
class BehaviorMessage
{
  public:
    virtual void v00();                 // +0x00 AddRef-like
    virtual void v04();                 // +0x04 Release-like
    virtual void v08();                 // +0x08
    virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
};
}
namespace SP {
class MessageServer
{
  public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void Send(u32 id, void* msg, int a, int b);     // +0x18
};
}
namespace SP {
class RefList
{
  public:
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
};
}
namespace SP {
class PickWorld
{
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
virtual void v28();
    virtual void SetPickPriorities(void* vec, int flag);    // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual void v60(void* a, void* b, void* c);            // +0x60
};
}
namespace SP {
class TerrainCursor
{
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
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void GetPickedList(void* vec);                  // +0x5c
    virtual void v60(void* a, void* b, void* c);            // +0x60
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void HideCursor();                              // +0x70 is level 0x70 -> +0x74
    virtual void v74();
};
}
namespace SP {
struct PickPriority
{
    u32 mId;        // +0x00
    int mPriority;  // +0x04
    int mWeight;    // +0x08
};
}
// ---- items of slice s00cf1ca0 end

// ---- items of slice s00cf4660 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl GameInputManager();          // 0x00b3d250
extern "C" void* __cdecl MessageServer();             // 0x0067dcc0
extern "C" void* __cdecl op_new(u32 size, const char* name,
                                int a, int b, int c, int d);   // 0x00f473a0
struct TreeOps {
    void ResetA(u32 alloc);      // 0x00b1b830
    void ResetB(u32 alloc);      // 0x00e4b990
};
struct ArgCmd {
    void Ctor(void* arg);            // 0x00b198d0
    void SetName(const char* name);  // 0x00b1b410
    void Finish();                   // 0x00b19b60
    void Destroy();                  // 0x0083c750
    u8   mPad[0x14];
};
struct Stopwatch {
    void Ctor(int a, int b);         // 0x0093a560
    u8   mPad[0x18];
};
struct PieMenu {
    PieMenu* Ctor();                 // 0x00b7d170
};
struct CommEditor {
    CommEditor* Ctor();                          // 0x00d0d200
    void Init(u32 a, u32 b, u32 c, u32 d);       // 0x00d0a760
};
struct AutoRefVector {
    u32  mpBegin;                    // +0x00
    u32  mpEnd;                      // +0x04
    u32  mpCap;                      // +0x08
    u8   mPad[8];                    // +0x0c
    void Dtor();                     // 0x00ae6970
};
struct CityInputStrategy {
    void* mpVtbl;            // +0x000
    u32   mTreeBase04;       // +0x004
    u32   mn08;              // +0x008
    u32   mn0C;              // +0x00c
    u32   mn10;              // +0x010
    union { u32 mn14; u8 mb14; };   // +0x014
    u32   mn18;              // +0x018
    u32   mn1C;              // +0x01c
    u32   mTreeBase20;       // +0x020
    u32   mn24;              // +0x024
    u32   mn28;              // +0x028
    u32   mn2C;              // +0x02c
    union { u32 mn30; u8 mb30; };   // +0x030
    u32   mn34;              // +0x034
    u32   mn38;              // +0x038
    void* mpVtbl3C;          // +0x03c
    void* mpVtbl40;          // +0x040
    u32   mn44;              // +0x044
    u8    mb48;              // +0x048
    u8    mPad49[3];         // +0x049
    u32   mn4C;              // +0x04c
    void* mp50;              // +0x050
    void* mp54;              // +0x054
    void* mp58;              // +0x058
    void* mp5C;              // +0x05c
    void* mp60;              // +0x060
    void* mp64;              // +0x064
    void* mp68;              // +0x068
    void* mp6C;              // +0x06c
    void* mp70;              // +0x070
    u32*  mp74;              // +0x074
    u32   mn78;              // +0x078
    u32   mn7C;              // +0x07c
    void* mp80;              // +0x080
    u32   mTreeBase84;       // +0x084
    u32   mn88;              // +0x088
    u32   mn8C;              // +0x08c
    u32   mn90;              // +0x090
    union { u32 mn94; u8 mb94; };   // +0x094
    u32   mn98;              // +0x098
    u32   mn9C;              // +0x09c
    u32   mTreeBaseA0;       // +0x0a0
    u32   mnA4;              // +0x0a4
    u32   mnA8;              // +0x0a8
    u32   mnAC;              // +0x0ac
    union { u32 mnB0; u8 mbB0; };   // +0x0b0
    u32   mnB4;              // +0x0b4
    u8    mPadB8[8];         // +0x0b8
    Stopwatch mStopwatch;    // +0x0c0
    void* mpD8;              // +0x0d8
    u8    mbDC;              // +0x0dc
    u8    mPadDD[3];         // +0x0dd
    u32   mnE0;              // +0x0e0
    void* mpE4;              // +0x0e4
    AutoRefVector mE8Vector; // +0x0e8
    u32   mnFC;              // +0x0fc
    u32   mn100;             // +0x100
    u32   mn104;             // +0x104
    u32   mn108;             // +0x108
    u32   mn10C;             // +0x10c
    u32   mn110;             // +0x110
    u32   mn114;             // +0x114
    u32   mn118;             // +0x118
    u32   mn11C;             // +0x11c
    u32   mn120;             // +0x120
    u32   mn124;             // +0x124
    u32   mn128;             // +0x128
    u32   mn12C;             // +0x12c
    u32   mn130;             // +0x130
    u8    mb134;             // +0x134
    u8    mb135;             // +0x135
    u8    mb136;             // +0x136
    u8    mPad137;           // +0x137
    u32   mn138;             // +0x138
    u32   mn13C;             // +0x13c
    u32   mn140;             // +0x140

    CityInputStrategy* Ctor(u32 param);   // 0x00cf4ca0
    void Reset(u32 mode);                 // 0x00cf4c00
    void Init();                          // 0x00cf4660
    void Destroy();                       // 0x00cf4ea0
};
// ---- items of slice s00cf4660 end

// ---- items of slice s00e34290 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cToolButton {
    char     mPad00[0x1a];
    bool     mbActive;                                      // +0x1a
    uint32_t mToolId;                                       // +0x1c
    char     mPad20[1];
    bool     mbEnabled;                                     // +0x21

    bool SetTool(uint32_t toolId, uint32_t data);           // 0x00e34eb0
    void SetEnabled(bool enabled);                          // 0x00e34ea0
};
// ---- items of slice s00e34290 end

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

// @ 0x00cf14d0
void cCityInputStrategy::FUN_00cf14d0()
{
    if (mFielde4)
    {
        void* mgr = FUN_00b3d230();
        ((void (__thiscall*)(void*, void*, u32))VT(mgr)[0x38 / 4])(mgr, mFielde4, 1);
    }
}

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

// @ 0x00cf1ca0
namespace SP {
void __fastcall FUN_00cf1ca0(void* ecx_this, void* edx, int first, int last, int pos, AutoRefCount* pivot, int a, int b)
{
    int* base = (int*)first;
    int* base2 = (int*)ecx_this;
    (void)base2;
    int i = pos;
    int child = i * 2 + 2;
    while (child < last) {
        int l = *(int*)((char*)base + (child - 1) * 4);
        void* lp = (l == 0) ? 0 : (void*)(l + 0x34);
        int r = *(int*)((char*)base + child * 4);
        void* rp = (r == 0) ? 0 : (void*)(r + 0x34);
        if (FUN_00ac0730(rp, lp)) {
            child = i * 2 + 1;
        }
        AutoRefCount* cl = (AutoRefCount*)*(int*)((char*)base + child * 4);
        AutoRefCount* ci = (AutoRefCount*)*(int*)((char*)base + i * 4);
        if (cl != ci) {
            if (cl) cl->AddRef();
            *(int*)((char*)base + i * 4) = (int)cl;
            if (ci) ci->Release();
        }
        i = child;
        child = i * 2 + 2;
    }
    if (child == last) {
        AutoRefCount* cl = (AutoRefCount*)*(int*)((char*)base + (child - 1) * 4);
        AutoRefCount* ci = (AutoRefCount*)*(int*)((char*)base + i * 4);
        if (cl != ci) {
            if (cl) cl->AddRef();
            *(int*)((char*)base + i * 4) = (int)cl;
            if (ci) ci->Release();
        }
        i = child - 1;
    }
    if (pivot) {
        ((void(__thiscall**)(AutoRefCount*, int, int))(*(char**)pivot))[0](pivot, a, b);
    }
    FUN_00cf1380(base, 0, i);
    if (pivot) {
        ((void(__thiscall**)(AutoRefCount*))(*(char**)pivot + 4))[0](pivot);
    }
}
}  // namespace SP

// @ 0x00cf1f50
namespace SP {
bool cCityInputStrategy_s00cf_1ca0::RestoreCommunityEditorOrShopping(int id)
{
    if (mAutoHandlerPriority == 0 || id == -1) {
        return mpCreatureSelected != 0;
    }
    BehaviorMessage* msg = (BehaviorMessage*)FUN_00f473a0(0x40, "App", 0, 0, 0, 0);
    if (msg != 0) {
        *(u32*)((char*)msg + 0x30) = 0;
        *(u32*)((char*)msg + 0x00) = 0x013eb90c;
        _InterlockedExchange((volatile long*)((char*)msg + 0x04), (long)0);
        *(u32*)((char*)msg + 0x00) = 0x013eb844;
        *(u32*)((char*)msg + 0x38) = 0;
        ((void(__thiscall**)(BehaviorMessage*))(*(char**)msg + 4))[0](msg);
    }
    *(u32*)((char*)msg + 0x30) = 0xb2699148;
    *(int*)((char*)msg + 0x08) = id;
    MessageServer* srv = (MessageServer*)FUN_0067dcc0();
    ((void(__thiscall**)(MessageServer*, u32, void*, int, int))(*(char**)srv + 0x18))[0](
        srv, *(u32*)((char*)msg + 0x30), msg, 0, 0);
    void* a = FUN_00b3d320();
    FUN_00b1dfc0(a);
    ((void(__thiscall**)(BehaviorMessage*))(*(char**)msg + 8))[0](msg);
    return true;
}
}  // namespace SP

// @ 0x00cf2010
namespace SP {
int* __fastcall FUN_00cf2010(int* ecx_this, void* edx, int* last, int* value)
{
    int* first = ecx_this;
    int* vp;
    while (true) {
        int a;
        vp = (value == 0) ? 0 : value + 0x0d;
        a  = (*first == 0) ? 0 : *first + 0x34;
        if (!FUN_00ac0730((void*)a, (void*)vp)) break;
        first++;
    }
    do {
        int a;
        int* vp2;
        last--;
        a   = (*last == 0) ? 0 : *last + 0x34;
        vp2 = (value == 0) ? 0 : value + 0x0d;
        if (FUN_00ac0730((void*)vp2, (void*)a)) break;
    } while (true);
    if (first < last) {
        FUN_00b2af00(first, last);
        first++;
    }
    if (value != 0) {
        ((void(__thiscall**)(int*))(*(int**)value + 4))[0](value);
    }
    return last;
}
}  // namespace SP

// @ 0x00cf20b0
namespace SP {
void __fastcall FUN_00cf20b0(void* ecx_this, void* edx, int* last, int* value, float f1, float f2, float f3)
{
    int* first = (int*)ecx_this;
    FUN_00cf1e70(first, last, f1, f2, f3);
    int* p = last;
    while (p < value) {
        int lp = (*first == 0) ? 0 : *first + 0x34;
        int vp = (*p == 0) ? 0 : *p + 0x34;
        if (!FUN_00ac0730((void*)vp, (void*)lp)) {
            p++;
            continue;
        }
        AutoRefCount* save = (AutoRefCount*)*p;
        if (save) save->AddRef();
        AutoRefCount* cur = (AutoRefCount*)*first;
        AutoRefCount* oth = (AutoRefCount*)*p;
        if (cur != oth) {
            if (cur) cur->AddRef();
            *p = (int)cur;
            if (oth) oth->Release();
        }
        if (save) {
            ((void(__thiscall**)(AutoRefCount*, float, float, float))(*(char**)save))[0](save, f1, f2, f3);
        }
        FUN_00cf1ca0(first, (void*)0, (int)first, (int)last - (int)first, 0, *(AutoRefCount**)&save, 0, 0);
        if (save) save->Release();
        p++;
    }
    FUN_00cf1ee0(first, last, f1, f2, f3);
}
}  // namespace SP

// @ 0x00cf2330
namespace SP {
void __fastcall FUN_00cf2330(void* ecx_this, void* edx)
{
    char* self = (char*)ecx_this;
    WStr msg;                                   // local eastl::wstring (12 bytes: begin/end/cap)
    if (*(int*)(self + 0xe0) == 1) {
        *(int*)(self + 0xe0) = 0;
        if (FUN_00b3d280() != 0) {
            void* cam = FUN_00b3d280();
            FUN_00b11870(cam, 0xf31f49a1);
        }
        msg.Init(L"Free Camera OFF");
        FUN_00af1450(FUN_00cf7500(FUN_00cf74c0()));
        msg.Release();
    } else {
        *(int*)(self + 0xe0) = 1;
        msg.Init(L"Free Camera ON");
        FUN_00af1450(FUN_00cf7500(FUN_00cf74c0()));
        msg.Release();
        if (FUN_00b3d280() != 0) {
            void* cam = FUN_00b3d280();
            FUN_00b11870(cam, 0xcf14603b);
        }
    }
}
}  // namespace SP

// @ 0x00cf2520
namespace SP {
bool cCityInputStrategy_s00cf_1ca0::EndSelection(const Vec3_s00cf_1ca0* dir, const void* picked)
{
    (void)picked;
    int success = 0;

    TerrainCursor* c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*, int))(*(char**)c + 0xb8))[0](c, 0);
    c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*))(*(char**)c + 0xa4))[0](c);
    c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*, float))(*(char**)c + 0xac))[0](c, 1.0f);
    c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*, float))(*(char**)c + 0xb0))[0](c, 1.0f);

    void* mgr = FUN_0067cab0(0x1002);
    FUN_00801bb0(mgr, 0x1002);

    if ((success & 2) == 0) {
        return success;
    }

    // gather the picked spatial list
    RefList list;
    list.mBegin = 0; list.mEnd = 0; list.mCap = 0;
    c = (TerrainCursor*)GetGameTerrainCursor();
    ((void(__thiscall**)(TerrainCursor*, void*))(*(char**)c + 0x5c))[0](c, &list);

    if (list.mBegin == list.mEnd) {
        success = 1;
    } else {
        float len2 = dir->x * dir->x + dir->y * dir->y + dir->z * dir->z;
        if (len2 > gZeroF) {
            // build a circle at the picked position and try to place vehicles
            FUN_00b3d290();
            void* gd = FUN_00ac15e0(0);
            FUN_00afba10(0);
            int n = FUN_00af9dd0(16.0f, (int)((char*)list.mEnd - (char*)list.mBegin) >> 2);
            Vec3_s00cf_1ca0 facing = gSurfaceDir;
            void* planet = FUN_00b3d350();
            FUN_00b7f190(planet, &facing, dir);
            FUN_00af9cf0((float*)dir, (float)n + 16.0f, (float*)&facing, 0.0f);
            FUN_00afef10(0, 16.0f);
            char* vec = (char*)this + 0xe8;
            void* first = *(void**)(vec);
            void* last  = *(void**)(vec + 4);
            FUN_00e25bd0(vec, first, last);
        }
    }
    (void)success;
    return false;
}
}  // namespace SP

// @ 0x00cf28f0
namespace SP {
void cCityInputStrategy_s00cf_1ca0::SetDefaultPickPriorities()
{
    PickPriority* begin = 0;
    PickPriority* end   = 0;
    PickPriority* cap   = 0;

    PickPriority rec;
    u32 ids[] = {
        0x137e8e0, 0x436f315, 0xecade42, 0xff10521, 0x1a55e4d,
        0x137e8e0, 0x175cdc9, 0x1007ae63, 0xd0036e08
    };
    int prios[] = { 1, 0, 0, 0, 0, 2, 0, 0, 0 };

    for (int i = 0; i < 9; i++) {
        rec.mId = ids[i];
        rec.mPriority = prios[i];
        rec.mWeight = 100;
        if (end < cap) {
            if (end) *end = rec;
            end++;
        } else {
            FUN_00b535d0(end, &rec);
            end = cap; // slow path reallocates; approximate
        }
    }

    PickWorld* w = (PickWorld*)FUN_00b3d240();
    ((void(__thiscall**)(PickWorld*, PickPriority**, int))(*(char**)w + 0x2c))[0](w, &begin, 1);
    (void)end;
}
}  // namespace SP

// @ 0x00cf2b70
namespace SP {
void __fastcall FUN_00cf2b70(void* ecx_this, void* edx)
{
    PickPriority* begin = 0;
    PickPriority* end   = 0;
    PickPriority* cap   = 0;

    PickPriority rec;
    u32 ids[] = {
        0x137e8e0, 0x436f315, 0xecade42, 0xff10521,
        0x1a55e4d, 0x4f176642, 0x1007ae63, 0xd0036e08
    };
    for (int i = 0; i < 8; i++) {
        rec.mId = ids[i];
        rec.mPriority = 0;
        rec.mWeight = 100;
        if (end < cap) {
            if (end) *end = rec;
            end++;
        } else {
            FUN_00b535d0(end, &rec);
            end = cap;
        }
    }
    PickWorld* w = (PickWorld*)FUN_00b3d240();
    ((void(__thiscall**)(PickWorld*, PickPriority**, int))(*(char**)w + 0x2c))[0](w, &begin, 1);
    (void)end;
}
}  // namespace SP

// @ 0x00cf2d60
namespace SP {
void __fastcall FUN_00cf2d60(void* ecx_this, void* edx)
{
    PickPriority* begin = 0;
    PickPriority* end   = 0;
    PickPriority* cap   = 0;

    PickPriority rec;
    u32 ids[] = {
        0x137e8e0, 0xecade42, 0xff10521, 0x1a55e4d, 0x4f176642,
        0xaeb336b4, 0xd0036e08, 0xce9f6639, 0x1007ae63
    };
    for (int i = 0; i < 9; i++) {
        rec.mId = ids[i];
        rec.mPriority = 0;
        rec.mWeight = 100;
        if (end < cap) {
            if (end) *end = rec;
            end++;
        } else {
            FUN_00b535d0(end, &rec);
            end = cap;
        }
    }
    PickWorld* w = (PickWorld*)FUN_00b3d240();
    ((void(__thiscall**)(PickWorld*, PickPriority**, int))(*(char**)w + 0x2c))[0](w, &begin, 1);
    (void)end;
}
}  // namespace SP

// @ 0x00cf4660
void CityInputStrategy::Init()
{
    if (mb48 != 0)
        return;
    mb48 = 1;

    if (mpE4 != 0) {
        void* mgr = FUN_00b3d230();
        ((void(__thiscall*)(void*, void*, int))(*(void***)mgr)[0x38 / 4])
            (mgr, mpE4, 1);
    }

    void* input = GameInputManager();
    if (input == 0)
        return;

    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0xfa0, (const char*)0x147874c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x132, (const char*)0x147873c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e8514, (const char*)0x147872c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37ea1bd, (const char*)0x1478714);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4d2b5fd, (const char*)0x14786fc);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e851a, (const char*)0x14786ec);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e851b, (const char*)0x14786d4);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95bd, (const char*)0x14786c0);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95bc, (const char*)0x14786a8);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95ba, (const char*)0x1478694);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95b9, (const char*)0x1478684);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x3e9, (const char*)0x1478670);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x3ea, (const char*)0x147865c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x3eb, (const char*)0x1478648);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x1f7, (const char*)0x147863c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x12d, (const char*)0x1478628);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x12e, (const char*)0x147861c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x12f, (const char*)0x147860c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x130, (const char*)0x1478600);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x131, (const char*)0x14785f0);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x1f5, (const char*)0x14785e8);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x1f7, (const char*)0x147863c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x1f6, (const char*)0x14785d8);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x7d1, (const char*)0x14785c4);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x7d2, (const char*)0x14785b0);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37eaf27, (const char*)0x147859c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37eaf28, (const char*)0x1478588);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37eaf28, (const char*)0x1478574);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37eaf29, (const char*)0x1478560);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x38b, (const char*)0x147854c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x406d0d8, (const char*)0x147853c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x37e95bb, (const char*)0x1478534);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x51b4174, (const char*)0x1478528);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x46ee610, (const char*)0x1478520);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x51b40a4, (const char*)0x1478514);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x49363f1, (const char*)0x1478504);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x6264b4d, (const char*)0x14784f0);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4e54bb3, (const char*)0x14784cc);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4e540ec, (const char*)0x14784ac);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4e540ed, (const char*)0x147848c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x4518450, (const char*)0x147847c);
    ((void(__thiscall*)(void*, u32, const char*))(*(void***)input)[0x40 / 4])
        (input, 0x58b3913, (const char*)0x1478468);

    void* cursor = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, u32))(*(void***)cursor)[0xb8 / 4])(cursor, 0);

    void* server = MessageServer();
    void* handler = (void*)&mpVtbl3C;
    mp6C = server;
    mp70 = handler;
    mp74 = (u32*)0x14782f0;
    mn78 = 0x4a;
    mn7C = 0;
    if (server != 0 && handler != 0) {
        for (u32 i = 0; i < 0x4a; ++i)
            ((void(__thiscall*)(void*, void*, u32))(*(void***)server)[0x24 / 4])
                (server, handler, ((u32*)0x14782f0)[i]);
    }

    CommEditor* ce = (CommEditor*)op_new(0x2fc, (const char*)0x1477120, 0, 0, 0, 0);
    if (ce != 0)
        ce = ce->Ctor();

    CommEditor* old = (CommEditor*)mp80;
    if (ce != old) {
        if (ce != 0)
            ((void(__fastcall*)(void*))(*(void***)ce)[8 / 4])(ce);
        mp80 = ce;
        if (old != 0)
            ((void(__fastcall*)(void*))(*(void***)old)[0xc / 4])(old);
    }
    ce = (CommEditor*)mp80;
    if (ce != 0)
        ce->Init(0x169d248, 0x5b9c8704, 0, 0);

    mn130 = 0;
    ((TreeOps*)&mTreeBase84)->ResetA(mn90);
    mn90 = 0;
    mn98 = 0;
    mn88 = (u32)((char*)this + 0x88);
    mn8C = (u32)((char*)this + 0x88);
    mb94 = 0;
    ((TreeOps*)&mTreeBaseA0)->ResetB(mnAC);
    mnA4 = (u32)((char*)this + 0xA4);
    mnA8 = (u32)((char*)this + 0xA4);
    mnAC = 0;
    mbB0 = 0;
    mnB4 = 0;

    ArgCmd local;
    local.Ctor(&mTreeBase84);
    local.SetName((const char*)0x1478450);
    local.Finish();

    PieMenu* menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp50 = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp54 = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp5C = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp60 = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp64 = menu;
    menu = (PieMenu*)op_new(0x1c, (const char*)0x147843c, 0, 0, 0, 0);
    if (menu != 0)
        menu = menu->Ctor();
    mp68 = menu;
    local.Destroy();
}

// @ 0x00e34ea0
void cToolButton::SetEnabled(bool enabled)
{
    mbEnabled = !enabled;
}
