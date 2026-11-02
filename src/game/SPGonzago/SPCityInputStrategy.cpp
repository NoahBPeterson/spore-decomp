// src/game/SPGonzago/SPCityInputStrategy.cpp -- migrated from slice(s) s00cf3bf0, s00cf2fd0, s00e34290, s00cf4660, s00cf1ca0, s00cf0cf0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityInputStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>
#include "SP/cSPCreatureCitizen.h"
#include "SP/cPlanet.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayout.h"
#include "SP/cCity.h"
#include "SP/cCivilization.h"
#include "SP/cVehicle.h"
#include "SP/cPollinator.h"
#include "SP/cSpeciesProfile.h"
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
extern u32 gEditorCursor[3];                        // 0x0169cc8c
extern u32 gTmpVecA[3];                             // 0x0169d258
extern u32 gTmpVecB[3];                             // 0x0169d264
extern u32 gCursorPosA;                             // 0x0169cc78
extern u32 gCursorPosB;                             // 0x0169cc7c
extern u8  gEditorModeFlag;                         // 0x0167ade8
extern u32 gFlag0169cc88;                           // 0x0169cc88
extern u32 gCityTuning;                             // 0x0169ca60
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
// ---- items of slice s00cf0cf0 end

// unnamed retail callees and globals that name local stubs (address in the comment)

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
extern "C" void* __cdecl FUN_01021260();              // active planet
extern "C" void  __cdecl op_del_array(void* p);                // 0x00f47380
extern "C" void  __cdecl RemoveHandler(void* h, void* a, void* b,
                                       void* c, void* d);       // 0x00571db0
extern "C" void* __cdecl FUN_00ba5e10(void* o, int v);
extern "C" void* __cdecl FUN_00ba57a0(void* o, int v);
extern "C" void* __cdecl FUN_00ba58e0(void* o, int v);
extern "C" void* __cdecl FUN_00b3d4f0(void* o);
extern "C" void* __cdecl NounManager_s00cf_4660();               // 0x00b3d300
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
struct SmallObj {
    SmallObj* Ctor();                // 0x00e34f40
};
struct PieMenuVec {
    void** mpBegin;                  // +0x00
    void** mpEnd;                    // +0x04
    void DestroyRange(void** a, void** b);  // 0x00b7cf10
};
struct AutoRefVector {
    u32  mpBegin;                    // +0x00
    u32  mpEnd;                      // +0x04
    u32  mpCap;                      // +0x08
    u8   mPad[8];                    // +0x0c
    void Dtor();                     // 0x00ae6970
};
struct TreePairLayout {
    u32 mn00;                        // +0x00 tree A header
    u32 mn04;                        // +0x04 self pointer
    u32 mn08;                        // +0x08
    u32 mn0C;                        // +0x0c element count
    union { u32 mn10; u8 mb10; };    // +0x10
    u32 mn14;                        // +0x14
    u32 mn18;                        // +0x18
    u32 mn1C;                        // +0x1c tree B header
    u32 mn20;                        // +0x20 self pointer
    u32 mn24;                        // +0x24
    u32 mn28;                        // +0x28 element count
    union { u32 mn2C; u8 mb2C; };    // +0x2c
    u32 mn30;                        // +0x30
};
struct ScanObj {
    u32* FUN_c0bc00();               // 0x00c0bc00
};
struct Planet_s00cf_4660 {
    bool SetSpeciesAsScanned(u32* sp);   // 0x00c73ea0
    bool IsScanned(u32* sp);             // 0x00c73f10
    bool Known(u32* key);                // 0x00c744e0
};
struct StarRec {
    void* GetCommContext();          // 0x00ce6950
};
struct TribeHolder {
    u8    mPad00[0x10c];
    void* mpTribe;                   // +0x10c
};
struct NounMgr_s00cf_4660 {
    void* GetTerrain();              // 0x00f67d90
};
struct Sphere {
    void* GetEntry(u32* commCtx);    // 0x00ba4e60
};
struct Entry8  { u8* Find(u32* sp); };   // 0x00ba4520
struct Entry20 { u8* Find(u32* sp); };   // 0x00ba4520
struct Entry38 { u8* Find(u32* sp); };   // 0x00ba4520
struct Entry68 { u8* Find(u32* key); };  // 0x00c735e0
struct Edition {
    int GetFileCount();              // 0x008e7f80
};
struct ObjA {
    void* FUN_c9d9e0();              // 0x00c9d9e0
};
struct ObjB_s00cf_4660 {
    void* GetTribe();                // 0x00c22f50
};
struct Obj9 {
    void Do();                       // 0x00e30d20
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

// ---- items of slice s00cf2fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00cf_2fd0 {
    float x, y, z;
    Vec3_s00cf_2fd0() {}
    Vec3_s00cf_2fd0(const Vec3_s00cf_2fd0& o) : x(o.x), y(o.y), z(o.z) {}
};
template <class R> static inline R VC0(void* o, int off)
{ return ((R(__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define P1 virtual void CAT(pad_, __COUNTER__)();
#define P2 P1 P1
#define P4 P2 P2
#define P8 P4 P4
#define P16 P8 P8
#define P32 P16 P16
struct ResourceKey { uint32_t a, b, c; };
struct Vehicle;
struct Obj {                       // cast-capable game object; Cast() is vtable slot 3
virtual void s0();
virtual void s1();
virtual void s2();
    virtual void* Cast(uint32_t id);
    P32 P8 P2                      // slots 4..45
    virtual Vehicle* GetVehicle(uint32_t id);   // +0xb8
};
struct Civilization {
    char pad[0x98];
    float mMoney;                                    // +0x98
    ResourceKey* GetModelTypeKey(int x);             // 0x00bf9770 (this+0x6c, jmp 0x00bf9700)
    void SpendMoney(float amount);                   // 0x00bef710 (ret 4)
    void Func_BEFD80(float amount, bool b);          // 0x00befd80 (ret 8)
    void Func_BF03E0(void* pObj, float f);           // 0x00bf03e0 (ret 8)
};
struct PosIface {                                    // spatial interface: GetPosition() at +0x2c
    P8 P2 P1
    virtual const Vec3_s00cf_2fd0* GetPosition();
};
struct City {
    virtual void v0();
    char pad[0x120 - 4];
    PosIface mOwned;                                 // +0x120 (interface)
    Civilization* GetCivilization();                 // 0x00bd9bf0 (mov eax,[ecx+0x590])
    void Func_BDDDA0(int quot, int rem, ResourceKey key, int flag);   // 0x00bddda0 (ret 0x18)
    void Func_BE1820(int a);                         // 0x00be1820 (ret 4)
    void Func_BE33E0(void* pSelected);               // 0x00be33e0 (ret 4)
    bool Func_BD7FC0(int empireID);                  // 0x00bd7fc0 (ret 4)
    float Func_BE9250(int empireID);                 // 0x00be9250 (ret 4), float in st0
};
City* __cdecl EndObjectPlacement(void* pOwner);      // 0x00ac86d0
struct Vehicle {                   // SP::cVehicle (fields used here)
    char pad[0xb20];
    int  mState;                   // +0xb20
    bool Func_C9FE40(void* o);                    // 0x00c9fe40 (ret 4)
    void Func_CAC000(void* o, int a, int b);      // 0x00cac000 (ret 0xc)
    void Func_CAC0E0(Vec3_s00cf_2fd0 pos, int n);            // 0x00cac0e0 (ret 0x10)
    void SetTimer(int t);                         // 0x00c9ee30 (ret 4)
    bool Func_CA8340(void* x);                    // 0x00ca8340 (ret 4)
};
struct TerrainSphere {
    void Func_C77BF0(uint32_t id);  // 0x00c77bf0 (ret 4)
};
struct NounMgr {
    TerrainSphere* GetCurrentTerrainSphere();  // 0x00f67d90
    int GetPlayerEmpireOrMinus1();             // 0x00b1f9d0
    Civilization* GetPlayerCivilization();     // 0x00b25fb0
};
struct BanOwner {                              // object at civStrategy+0xec
    void Func_CE96B0(int flag);                // 0x00ce96b0
};
struct CivModeStrategy {
    char pad[0xec];
    BanOwner* GetBanOwner();                   // 0x00cf7500 (mov eax,[ecx+0xec])
    float Func_CF7A50();                       // 0x00cf7a50
};
struct CommManager {
    void ShowCommEvent(void* a, void* b, void* c, uint32_t d, uint32_t e, int f);   // 0x00aeb760 (ret 0x18)
};
struct StarRef {
    void* GetCommContext();                    // 0x00ce6950 (mov eax,[ecx+0x184])
};
struct Planet {
    char pad[0x13c];
    StarRef* mpStar;                           // +0x13c
    StarRef* GetStar() { return mpStar; }
};
struct SpatialIface34 {                              // interface at sel+0x34
    P8 P2 P1                                         // slots 0..10
    virtual const Vec3_s00cf_2fd0* GetPosition();               // +0x2c
    P16 P8 P2                                        // slots 12..37
    virtual void* Func98();                          // +0x98
};
struct CostIface120 {                                // interface at sel+0x120
    P8 P2 P1
    virtual void Func2C(int v);                      // +0x2c
};
struct Sel {                                         // object behind this+0x10c / this+0x110 (cSpatialGameData)
    P8 P4                                            // slots 0..11
    virtual Obj* GetOwner();                         // +0x30
    P8 P2                                            // slots 13..22
    virtual float GetCostA();                        // +0x5c
    virtual float GetCostB();                        // +0x60
    P8                                               // slots 25..32
    virtual City* GetPlaced();                       // +0x84
    char pad04[0x34 - 4];
    SpatialIface34 mIface34;                         // +0x34
    char pad38[0x120 - 0x38];
    CostIface120 mIface120;                          // +0x120
    void* Func_BCD630();                             // 0x00bcd630
};
struct Obj118 {                                // object behind this+0x118
    char pad[0x588];
    CostIface120 mIface588;
    City* Func_BCE5C0();                       // 0x00bce5c0 (mov eax,[ecx+0x688])
    float Func_BD0110();                       // 0x00bd0110 (float in st0)
};
struct Cursor {                                      // terrain cursor
    P16 P8
    virtual void GetObjects(struct ObjVec* pOut, uint32_t type);   // +0x60
};
NounMgr*       __cdecl NounManager();             // 0x00b3d300
CivModeStrategy* __cdecl GetCivModeStrategy();    // 0x00cf74c0
CommManager*   __cdecl GetCommManager();          // 0x00b3d4a0
Planet*        __cdecl GetActivePlanet();         // 0x01021260
uint32_t       __cdecl GetRecorderState();        // 0x00435e90
void           __cdecl KillSetiEffects(uint32_t hash, uint32_t state);   // 0x00435ed0
Cursor*        __cdecl GetGameTerrainCursor_s00cf_2fd0();    // 0x00b30d70
void*          __cdecl InterfaceCastBuilding(void* p);   // 0x00cf1090
struct Item34 { int Func_8E7F80(); };                  // 0x008e7f80 (mov eax,[ecx+0x34])
Item34*        __cdecl Func_AE6740(void* p);      // 0x00ae6740
int            __cdecl Func_C9E6D0(int a, int b); // 0x00c9e6d0
Vehicle*       __cdecl CastVehicle(void** it);    // 0x00bd8440
void           __cdecl HideUTFMenu(int flag);     // 0x00b7c810
struct Zero16 { int a, b, c, d; };
void __cdecl EditorLaunch(uint32_t id, void* pObj, uint32_t key, void* pSel, Zero16 z, int flag);   // 0x005a94d0
struct ObjVec {                    // eastl::vector<AutoRefCount<cSpatialObject>, sp_vector_allocator>
    Obj** mpBegin; Obj** mpEnd; Obj** mpCap;
    int mAllocFields[2];           // allocator state, not initialised by the inlined constructor
    ObjVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    void Destroy();                // 0x00ad92d0 (out-of-line ~vector)
};
struct VRef {                      // EA::AutoRefCount<cVehicle>
    Vehicle* p;
    VRef(Vehicle* v);              // 0x00572660
    ~VRef() { if (p) VC0<void>(p, 4); }
};
struct VehVec {                    // eastl::vector<AutoRefCount<cVehicle>, sp_vector_allocator>
    Vehicle** mpBegin; Vehicle** mpEnd; Vehicle** mpCap;
    void erase(Vehicle** first, Vehicle** last);          // 0x00e25bd0 (ret 8)
    bool empty() const { return mpBegin == mpEnd; }
    void push_back(VRef* v);                              // 0x00e1c7f0 (ret 4)
};
struct CityInputStrategy_s00cf_2fd0 {
    char   pad[0xe8];
    VehVec mSelected;                                     // +0xe8
    char   pade[0x10c - 0xf4];
    Sel*   mp10c;                                         // +0x10c
    Sel*   mp110;                                         // +0x110
    char   pad114[0x118 - 0x114];
    Obj118* mp118;                                        // +0x118
    Sel*   mp11c;                                         // +0x11c
    char   pad120[0x13c - 0x120];                         // +0x120
    int    mBanMode;                                      // +0x13c (0 = off)
    int    mBanId;                                        // +0x140
    void Func_CF30B0(void* target, Vec3_s00cf_2fd0 pos, int flag);   // 0x00cf30b0 (ret 0x14)
    void SetDefaultPickPriorities();                      // 0x00cf28f0 (ret 0)
    void Func_CF2B70();                                   // 0x00cf2b70 (ret 0)
    void Func_CF2D60();                                   // 0x00cf2d60 (ret 0)
    void ToggleTribeBanning();                            // 0x00cf2fd0 (ret 0)
    void ToggleCityBanning();                             // 0x00cf3040 (ret 0)
    bool HandleMenuItem(int id);
};
struct PathMgr {                       // singleton behind 0x00b3d290
    char pad[0x48];
    void NextStamp();                  // 0x00ac15e0 (++[(this)+0x48])
};
PathMgr* GetPathManager();             // 0x00b3d290
void __cdecl SortVehicles(Vehicle** first, Vehicle** last, Vec3_s00cf_2fd0 pos);   // 0x00cf2440
void __cdecl EndBanMode(int flag);     // 0x00dd1840 (cUIBanningContent::EndBanMode)
void __cdecl ToggleTribeBanMode(int flag);   // 0x00dd17f0 (cTribeInputStrategy::ToggleBanningContent)
void __cdecl Func_00E09A50(int flag);  // 0x00e09a50 (leaves the mode-2 ban UI)
void __cdecl Func_00E099D0(int flag);  // 0x00e099d0 (enters the mode-2 ban UI)
extern Vec3_s00cf_2fd0 g_banDefaultPos;           // 0x0169cc8c (position meaning "keep the current order")
// ---- items of slice s00cf2fd0 end

// ---- items of slice s00cf3bf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gAppNameTag;                               // 0x01654c05
struct Vec3_s00cf_3bf0 { float x, y, z; };
void __cdecl operator delete[](void*);             // 0x00f47380
template <class R, class A> static inline R VC1(void* o, int off, A a)
{ return ((R(__thiscall*)(void*, A))(*(void***)o)[off / 4])(o, a); }
struct Obj_s00cf_3bf0 {                       // cast-capable game object; Cast() is vtable slot 3
virtual void s0();
virtual void s1();
virtual void s2();
    virtual void* Cast(uint32_t id);
};
struct Vehicle_s00cf_3bf0 {                   // SP::cVehicle (fields used here)
    char pad[0xb1c];
    int  mbFlagB1C;                // +0xb1c
    int  mState;                   // +0xb20
    bool Func_C9FE40(void* o);                    // 0x00c9fe40
    void Func_CAC000(void* o, int a, int b);      // 0x00cac000
    void Func_C9EE30(int id);                     // 0x00c9ee30
    bool CanOccupyTerrain(const Vec3_s00cf_3bf0* pos);       // 0x00c9e960
    bool Func_CA8340(void* x);                    // 0x00ca8340
    void Func_CA80E0(int a);                      // 0x00ca80e0
};
struct ObjB {
    void Func_BD1AB0(int a);  // 0x00bd1ab0
};
struct GameDataList;
struct cCivilization;
struct NounMgr_s00cf_3bf0 {
    TerrainSphere* GetCurrentTerrainSphere();  // 0x00f67d90
    GameDataList*  GetGameDataVector(void* f1, void* f2, void* f3, void* f4, uint32_t id);  // 0x00b21340
    cCivilization* GetPlayerCivilization();    // 0x00b25fb0
};
struct IdSource {
    int NextId();  // 0x00ac15e0
};
struct PlanetModel {
    int GetContinent(const Vec3_s00cf_3bf0* pos);  // 0x00b88590
};
struct EventLog {
    void RemoveAllEventsOfSameType(uint32_t type, int a, int b);  // 0x00dd7620
};
struct CivModeStrategy_s00cf_3bf0 {
    bool HasCivTutorialOccurred(uint32_t id);                  // 0x00cf7830
    void DoNextCivTutorial(uint32_t id, int a);                // 0x00cfa990
};
struct AudioSystem {                                           // vtable slot 0x20 = GetToken
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual void* GetToken();
};
NounMgr_s00cf_3bf0*       __cdecl NounManager_s00cf_3bf0();             // 0x00b3d300
EventLog*      __cdecl GetEventLog();             // 0x00b3d3e0
IdSource*      __cdecl GetIdSource();             // 0x00b3d290
PlanetModel*   __cdecl GetPlanetModel();          // 0x00b3d350
CivModeStrategy_s00cf_3bf0* __cdecl GetCivModeStrategy_s00cf_3bf0();    // 0x00cf74c0
AudioSystem*   __cdecl GetSystemAT();             // 0x00a206f0
void*          __cdecl GetRecorderState_s00cf_3bf0();        // 0x00435e90
void           __cdecl KillSetiEffects(uint32_t hash, void* state);          // 0x00435ed0
void           __cdecl Start3dSoundByName(uint32_t hash, void* state, Vec3_s00cf_3bf0 pos);  // 0x00571f80
Vehicle_s00cf_3bf0*       __cdecl CastVehicle_s00cf_3bf0(void** it);    // 0x00bd8440
void*          __cdecl Func_BCE5C0(void* x);      // 0x00bce5c0 (thiscall on x, no args)
struct ObjVec_s00cf_3bf0 {                    // eastl::vector<AutoRefCount<cSpatialObject>, sp_vector_allocator>
    Obj_s00cf_3bf0** mpBegin; Obj_s00cf_3bf0** mpEnd; Obj_s00cf_3bf0** mpCap;
    void Destroy();                // 0x00ad92d0 (out-of-line ~vector)
};
struct VRef_s00cf_3bf0 {                      // EA::AutoRefCount<cVehicle>
    Vehicle_s00cf_3bf0* p;
    VRef_s00cf_3bf0(Vehicle_s00cf_3bf0* v);              // 0x00572660
    ~VRef_s00cf_3bf0() { if (p) VC0<void>(p, 4); }
};
struct VRefInline {                // same object, constructed inline (AddRef of a known non-null pointer)
    Vehicle_s00cf_3bf0* p;
    VRefInline(Vehicle_s00cf_3bf0* v) { p = v; VC0<void>(v, 0); }
    ~VRefInline() { if (p) VC0<void>(p, 4); }
};
struct VehVec_s00cf_3bf0 {                    // eastl::vector<AutoRefCount<cVehicle>, sp_vector_allocator>
    Vehicle_s00cf_3bf0** mpBegin; Vehicle_s00cf_3bf0** mpEnd; Vehicle_s00cf_3bf0** mpCap;
    void erase(Vehicle_s00cf_3bf0** first, Vehicle_s00cf_3bf0** last);          // 0x00e25bd0
    void push_back(VRef_s00cf_3bf0* v);                              // 0x00e1c7f0
    void DoInsertValue(Vehicle_s00cf_3bf0** pos, Vehicle_s00cf_3bf0** v);       // 0x00aea5d0
};
struct cRelationshipRollover {
    void Func_E35350();                                   // 0x00e35350
};
struct CityInputStrategy_s00cf_3bf0 {
    char   pad[0xe4];
    cRelationshipRollover* mpRollover;                    // +0xe4
    VehVec_s00cf_3bf0 mSelected;                                     // +0xe8
    void Func_CF30B0(Obj_s00cf_3bf0* target, Vec3_s00cf_3bf0 pos, int flag);    // 0x00cf30b0
    int  DoObjectInteraction(Obj_s00cf_3bf0* pObj, int arg2);
    bool HandleMenuItem(uint32_t messageId);              // 0x00cf31f0
    int  FUN_00cf4440(uint32_t arg1, uint32_t messageId);  // 0x00cf4440
    bool FUN_00cf44c0(const Vec3_s00cf_3bf0* pPos);                  // 0x00cf44c0
};
struct CVecHost {                                          // what FUN_00fd9c60 hands back (0x016d9938)
    uint8_t mPad00[0x7c];                                  // +0x00
    Vec3_s00cf_3bf0    mVec;                                          // +0x7c
};
CVecHost* __cdecl FUN_00fd9c60();                          // 0x00fd9c60
struct cGameTimeManager {
    void DecPauseGate(uint32_t gate);                      // 0x00b32250
    int  GetPauseGateCount(uint32_t gate);                 // 0x00b320d0
    void TogglePauseGate(uint32_t gate);                   // 0x00b32280
};
cGameTimeManager* __cdecl GameTimeManager();               // 0x00b3d380
struct cGameInputManager {
    uint32_t mPad000[0x110 / 4];                           // +0x000
    int32_t  mField110;                                    // +0x110
};
cGameInputManager* __cdecl GameInputManager_s00cf_3bf0();             // 0x00b3d250
struct cCameraControl {
    uint32_t mPad000[0x364 / 4];                           // +0x000
    bool     mbFlag364;                                    // +0x364
};
cCameraControl* __cdecl GetCameraCtl();                    // 0x00b3d280
struct DataEntrySub {                                      // the sub-object at +0x120 of a game-data entry
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void sA();
virtual void sB();
virtual void sC();
virtual void sD();
virtual void sE();
virtual void sF();
virtual void sG();
virtual void sH();
virtual void sI();
virtual void sJ();
virtual void sK();
virtual void sL();
    virtual bool IsLive();                                 // +0x58
};
struct GameDataEntry {
    uint8_t      mPad000[0x120];                           // +0x000
    DataEntrySub mSub;                                     // +0x120
    void Func_BD9BB0();                                    // 0x00bd9bb0
};
struct GameDataVec {
    GameDataEntry** mpBegin;                               // +0x00
    GameDataEntry** mpEnd;                                 // +0x04
};
struct GameDataList {
    uint32_t    mPad00;                                    // +0x00
    GameDataVec mEntries;                                  // +0x04
};
struct cCivilization {
    void* GetSpeciesProfile();                             // 0x00bef950
};
struct SpeciesProfileKey {
    uint32_t mWords[4];
};
struct cSpeciesProfile {
    uint8_t           mPad000[0x504];                      // +0x000
    SpeciesProfileKey mKey;                                // +0x504
};
struct cPollinator {
    void UpdateProperty(uint32_t propertyId, const SpeciesProfileKey* key);   // 0x0060d860
};
cPollinator* __cdecl FUN_0067cb30();                       // 0x0067cb30
struct cAppGlobal {
    void Func_B1E410(uint32_t tag);                        // 0x00b1e410
};
cAppGlobal* __cdecl FUN_00b3d320_s00cf_3bf0();                        // 0x00b3d320
void* __cdecl operator new(uint32_t size, const char* name, int, int, int, int);  // 0x00f473a0
struct cSimSingleton {
    void Func_AE37C0(int mode, Vec3_s00cf_3bf0 v);                    // 0x00ae37c0 (Vec3 by value, ret 0x10)
    void Construct();                                      // 0x00ae5c30
    static cSimSingleton* Instance();                      // inlined accessor over 0x0167a60c
};
extern cSimSingleton* gpSimSingleton;                      // 0x0167a60c
extern Vec3_s00cf_3bf0 gSelectionPoint;                               // 0x0169cc8c
inline cSimSingleton* cSimSingleton::Instance()
{
    if (!gpSimSingleton) {
        cSimSingleton* p = (cSimSingleton*)::operator new(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p)
            p->Construct();
        else
            p = 0;
        gpSimSingleton = p;
    }
    return gpSimSingleton;
}
// ---- items of slice s00cf3bf0 end

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

// @ 0x00cf0fe0
u32 cCityInputStrategy::FUN_00cf0fe0()
{
    if ((mFieldc0 | mFieldc4) != 0)
        return 1;
    return 0;
}

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

// @ 0x00cf2fd0
void CityInputStrategy_s00cf_2fd0::ToggleTribeBanning()
{
    if (mBanMode == 1) {
        mBanMode = 0;
        SetDefaultPickPriorities();
        EndBanMode(1);
        return;
    }
    mBanId = -1;
    GetCivModeStrategy()->GetBanOwner()->Func_CE96B0(1);
    mBanMode = 1;
    Func_CF2B70();
    ToggleTribeBanMode(1);
}

// @ 0x00cf3040
void CityInputStrategy_s00cf_2fd0::ToggleCityBanning()
{
    if (mBanMode == 2) {
        mBanMode = 0;
        SetDefaultPickPriorities();
        Func_00E09A50(1);
        return;
    }
    mBanId = -1;
    GetCivModeStrategy()->GetBanOwner()->Func_CE96B0(1);
    mBanMode = 2;
    Func_CF2D60();
    Func_00E099D0(1);
}

// @ 0x00cf30b0
void CityInputStrategy_s00cf_2fd0::Func_CF30B0(void* target, Vec3_s00cf_2fd0 pos, int flag)
{
    VehVec& sel = mSelected;
    if (sel.mpBegin != sel.mpEnd) {
        int count = (int)(sel.mpEnd - sel.mpBegin);
        if (count > 1) {
            GetPathManager()->NextStamp();
            if (!(pos.x == g_banDefaultPos.x && pos.y == g_banDefaultPos.y
                  && pos.z == g_banDefaultPos.z))
                SortVehicles(sel.mpBegin, sel.mpEnd, pos);
        }
        // the index qualifier is 1 for the first ten vehicles of the group, 2 for the rest
        if (flag == 6) {
            for (int i = 0; i < count; ++i) {
                sel.mpBegin[i]->Func_CAC0E0(pos, (i >= 10) + 1);
                sel.mpBegin[i]->SetTimer(0);
            }
        } else {
            for (int i = 0; i < count; ++i) {
                sel.mpBegin[i]->Func_CAC000(target, flag, (i >= 10) + 1);
                sel.mpBegin[i]->SetTimer(0);
            }
        }
        sel.erase(sel.mpBegin, sel.mpEnd);
    }
}

// @ 0x00cf31f0
bool CityInputStrategy_s00cf_2fd0::HandleMenuItem(int id)
{
    if (id >= 0x321 && id <= 0x32f) {
        int quot = (id - 0x321) / 5;
        int rem = (id - 0x321) % 5;
        Obj* hall = mp110->GetOwner();
        City* city = hall ? (City*)hall->Cast(0xee9b2232) : 0;
        Civilization* civ = city->GetCivilization();
        ResourceKey* key = civ->GetModelTypeKey(Func_C9E6D0(quot, rem));
        city->Func_BDDDA0(quot, rem, *key, 0);
    }

    switch (id) {
    case 0x38b:
        if (mp10c)
            EndObjectPlacement(mp10c->GetOwner())->Func_BE1820(0);
        break;

    case 0x37e95b9: {
        ObjVec objects;
        GetGameTerrainCursor_s00cf_2fd0()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp10c
            && InterfaceCastBuilding(mp10c)) {
            Item34* pX = Func_AE6740(mp10c);
            if (pX && pX->Func_8E7F80() != 2) {
                Obj** it = objects.mpBegin;
                Obj** itEnd = objects.mpEnd;
                for (; it != itEnd; ++it) {
                    Vehicle* veh = CastVehicle((void**)it);
                    if (veh && veh->mState == 0 && veh->Func_CA8340(mp10c->GetPlaced())) {
                        VRef r(veh);
                        mSelected.push_back(&r);
                    }
                }
                if (mSelected.mpBegin != mSelected.mpEnd) {
                    Func_CF30B0(mp10c->GetPlaced(), *mp10c->GetPlaced()->mOwned.GetPosition(), 2);
                    NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f6);
                    KillSetiEffects(0x940e34ee, 0x37fd5b2);
                }
            }
        }
        objects.Destroy();
        break;
    }

    case 0x37e95bb:
        if (mp10c->GetPlaced()->Func_BD7FC0(NounManager()->GetPlayerEmpireOrMinus1())) {
            NounManager()->GetPlayerCivilization()->Func_BF03E0(
                mp10c->GetPlaced(),
                mp10c->GetPlaced()->Func_BE9250(NounManager()->GetPlayerEmpireOrMinus1()));
            NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f7);
        }
        break;

    case 0x37e95ba: {
        ObjVec objects;
        GetGameTerrainCursor_s00cf_2fd0()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp10c) {
            mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
            Obj** it = objects.mpBegin;
            Obj** itEnd = objects.mpEnd;
            for (; it != itEnd; ++it) {
                Vehicle* veh = CastVehicle((void**)it);
                if (veh->mState == 1 && veh->Func_CA8340(mp10c->GetPlaced())) {
                    VRef r(veh);
                    mSelected.push_back(&r);
                }
            }
            if (!mSelected.empty()) {
                Func_CF30B0(mp10c->GetPlaced(), *mp10c->GetPlaced()->mOwned.GetPosition(), 3);
                KillSetiEffects(0x9ab713eb, 0x37fd5b2);
            }
        }
        objects.Destroy();
        break;
    }

    case 0x37e95bc: {
        ObjVec objects;
        GetGameTerrainCursor_s00cf_2fd0()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp10c) {
            mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
            Obj** it = objects.mpBegin;
            Obj** itEnd = objects.mpEnd;
            for (; it != itEnd; ++it) {
                Vehicle* veh = CastVehicle((void**)it);
                if (veh->mState == 2 && veh->Func_CA8340(mp10c->GetPlaced())) {
                    VRef r(veh);
                    mSelected.push_back(&r);
                }
            }
            if (!mSelected.empty()) {
                Func_CF30B0(mp10c->GetPlaced(), *mp10c->GetPlaced()->mOwned.GetPosition(), 9);
                NounManager()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f4);
                KillSetiEffects(0xca345816, 0x37fd5b2);
            }
        }
        objects.Destroy();
        break;
    }

    case 0x37e95bd: {
        ObjVec objects;
        GetGameTerrainCursor_s00cf_2fd0()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp10c) {
            Obj** it = objects.mpBegin;
            Obj** itEnd = objects.mpEnd;
            for (; it != itEnd; ++it) {
                Vehicle* veh = CastVehicle((void**)it);
                if (veh->mState == 2 && veh->Func_CA8340(mp10c->GetPlaced()))
                    veh->Func_CAC000(mp10c->GetPlaced(), 5, 1);
            }
        }
        objects.Destroy();
        break;
    }

    case 0x37eaf27: {
        Obj* hall = VC0<Obj*>(mp10c, 0x30);
        City* city = hall ? (City*)hall->Cast(0xee9b2232) : 0;
        Sel* sel = mp10c;
        city->GetCivilization()->Func_BEFD80(GetCivModeStrategy()->Func_CF7A50() * sel->GetCostA(), false);
        Obj* hall2 = VC0<Obj*>(mp10c, 0x30);
        City* city2 = hall2 ? (City*)hall2->Cast(0xee9b2232) : 0;
        city2->Func_BE33E0(mp10c);
        mp10c = 0;
        break;
    }

    case 0x37eaf2b:
        EndObjectPlacement(mp10c->GetOwner())->Func_BE33E0(mp10c);
        mp10c = 0;
        break;

    case 0x37eaf2a: {
        City* city = EndObjectPlacement(mp10c->GetOwner());
        Civilization* civ = city->GetCivilization();
        float cost = mp10c->GetCostB();
        if (civ->mMoney >= cost) {
            Sel* sel = mp10c;
            sel->mIface120.Func2C(0);
            civ->SpendMoney(cost);
        } else {
            KillSetiEffects(0x594303b7, GetRecorderState());
        }
        break;
    }

    case 0x37eaf29: {
        Sel* sel = mp10c;
        Zero16 z = { 0, 0, 0, 0 };
        EditorLaunch(0xd817cd63, sel->mIface34.Func98(), 0x2def34f, sel, z, 0);
        break;
    }

    case 0x39a6152:
        if (mp118) {
            Civilization* civ = mp118->Func_BCE5C0()->GetCivilization();
            if (civ) {
                float cost = mp118->Func_BD0110();
                if (civ->mMoney >= cost) {
                    mp118->mIface588.Func2C(0);
                    civ->SpendMoney(cost);
                }
            }
        }
        break;

    case 0x51b4174: {
        CommManager* pComm = GetCommManager();
        Planet* pPlanet = GetActivePlanet();
        pComm->ShowCommEvent(mp10c->Func_BCD630(), mp10c->GetPlaced(),
                             pPlanet->GetStar()->GetCommContext(), 0xdbf385bf, 0xee4f8f7f, 0);
        break;
    }

    case 0x51b40a4: {
        ObjVec objects;
        GetGameTerrainCursor_s00cf_2fd0()->GetObjects(&objects, 0x137e8e0);
        if (objects.mpBegin != objects.mpEnd && mp11c) {
            mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
            Obj** it = objects.mpBegin;
            Obj** itEnd = objects.mpEnd;
            for (; it != itEnd; ++it) {
                Obj* p = *it;
                Vehicle* veh = p ? p->GetVehicle(0x137e8e0) : 0;
                if (veh->mState == 2 && veh->Func_C9FE40(mp11c)) {
                    VRef r(veh);
                    mSelected.push_back(&r);
                }
            }
            if (!mSelected.empty()) {
                Func_CF30B0(mp11c, *mp11c->mIface34.GetPosition(), 0xb);
                KillSetiEffects(0xd15f2608, 0x37fd5b2);
            }
        }
        objects.Destroy();
        break;
    }

    case 0x46ee610: {
        CommManager* pComm = GetCommManager();
        Planet* pPlanet = GetActivePlanet();
        pComm->ShowCommEvent(mp10c->Func_BCD630(), mp10c->GetPlaced(),
                             pPlanet->GetStar()->GetCommContext(), 0xdbf385bf, 0x942bfb93, 0);
        break;
    }
    }

    HideUTFMenu(1);
    return true;
}

// @ 0x00cf3bf0
int CityInputStrategy_s00cf_3bf0::DoObjectInteraction(Obj_s00cf_3bf0* pObj, int arg2)
{
    if (!pObj)
        return 0;

    Obj_s00cf_3bf0*  pAnimal = (Obj_s00cf_3bf0*)pObj->Cast(0xd0036e08);
    Obj_s00cf_3bf0*  pB      = (Obj_s00cf_3bf0*)pObj->Cast(0x0e9cb8ba);
    if (pB) {
        if (pB->Cast(0x1007ae63))
            pB = 0;
    }
    Obj_s00cf_3bf0*  pE      = (Obj_s00cf_3bf0*)pObj->Cast(0x00ee02c7);
    pObj->Cast(0x137e8e0);
    pObj->Cast(0x4f176642);
    pObj->Cast(0x116d858);
    pObj->Cast(0x629baec);

    ObjVec_s00cf_3bf0 objects;
    objects.mpBegin = 0; objects.mpEnd = 0; objects.mpCap = 0;
    VC1<void, ObjVec_s00cf_3bf0*>(GetGameTerrainCursor(), 0x5c, &objects);   // GetObjectsUnderCursor
    if (objects.mpBegin == objects.mpEnd) {
        objects.Destroy();
        return 0;
    }
    if (!VC1<void*, uint32_t>(*objects.mpBegin, 0xb8, 0x137e8e0)) {
        objects.Destroy();
        return 0;
    }

    bool bAny = false;
    Obj_s00cf_3bf0* pC = (Obj_s00cf_3bf0*)pObj->Cast(0x436f315);
    Obj_s00cf_3bf0* pD = (Obj_s00cf_3bf0*)pObj->Cast(0x403df5f);
    int  nextId = GetIdSource()->NextId();

    if (!pB && !pC && !pAnimal) {
        if (pD) {
            bool bFlag = false;
            int id = VC0<int>(pD, 0x4c);
            Obj_s00cf_3bf0** it = objects.mpBegin;
            if (it != objects.mpEnd) {
                do {
                    Vehicle_s00cf_3bf0* v = CastVehicle_s00cf_3bf0((void**)it);
                    if (bFlag || v->mState == 2)
                        bFlag = true;
                    if (id == -1) {
                        if (v->Func_C9FE40(pD)) {
                            NounManager_s00cf_3bf0()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f2);
                            v->Func_CAC000(pD, 8, 1);
                            bAny = true;
                            GetEventLog()->RemoveAllEventsOfSameType(0x6889d3f5, 0, 0);
                        }
                    } else {
                        int st = v->mState;
                        if (st == 0 || st == 1) {
                            if (VC0<int>(v, 0x4c) != id) {
                                if (v->Func_C9FE40(pD)) {
                                    NounManager_s00cf_3bf0()->GetCurrentTerrainSphere()->Func_C77BF0(0x57fbc70);
                                    v->Func_CAC000(pObj, 1, 1);
                                    v->Func_C9EE30(nextId);
                                    bAny = true;
                                }
                            }
                        }
                    }
                    ++it;
                } while (it != objects.mpEnd);
                if (!bAny) {
                    if (!bFlag)
                        KillSetiEffects(0x594303b7, GetRecorderState_s00cf_3bf0());
                } else {
                    Vec3_s00cf_3bf0* p = VC0<Vec3_s00cf_3bf0*>((char*)pD + 0x34, 0x2c);
                    Start3dSoundByName(0xc6f2fe9b, GetRecorderState_s00cf_3bf0(), *p);
                }
            } else {
                KillSetiEffects(0x594303b7, GetRecorderState_s00cf_3bf0());
            }
        } else if (pE) {
            char* pEpos = (char*)pE + 0x34;
            if (!*((char*)VC0<char*>(pE, 0x58) + 0x557)) {
                Obj_s00cf_3bf0** it = objects.mpBegin;
                if (it != objects.mpEnd) {
                    do {
                        Vehicle_s00cf_3bf0* v = CastVehicle_s00cf_3bf0((void**)it);
                        if (v->CanOccupyTerrain(VC0<Vec3_s00cf_3bf0*>(pEpos, 0x2c))) {
                            NounManager_s00cf_3bf0()->GetCurrentTerrainSphere()->Func_C77BF0(0x57fbc6b);
                            v->Func_CAC000(pObj, 8, 1);
                            v->Func_C9EE30(nextId);
                            bAny = true;
                        }
                        ++it;
                    } while (it != objects.mpEnd);
                    if (!bAny) {
                        KillSetiEffects(0x594303b7, GetRecorderState_s00cf_3bf0());
                    } else {
                        Vec3_s00cf_3bf0* p = VC0<Vec3_s00cf_3bf0*>(pEpos, 0x2c);
                        Start3dSoundByName(0x5580e0f9, GetRecorderState_s00cf_3bf0(), *p);
                    }
                } else {
                    KillSetiEffects(0x594303b7, GetRecorderState_s00cf_3bf0());
                }
            }
        }
    } else {
        mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
        for (Obj_s00cf_3bf0** it = objects.mpBegin; it != objects.mpEnd; ++it) {
            Obj_s00cf_3bf0* o = *it;
            if (!o) continue;
            Vehicle_s00cf_3bf0* v = (Vehicle_s00cf_3bf0*)VC1<void*, uint32_t>(o, 0xb8, 0x137e8e0);
            if (!v) continue;
            if ((pB || pC) && (v->mState == 0 || v->mState == 1)) {
                void* x;
                if (pB)
                    x = VC0<void*>(pB, 0x84);
                else
                    x = Func_BCE5C0(pC);
                if (v->mbFlagB1C != 0 || v->Func_CA8340(x)) {
                    VRefInline ref(v);
                    mSelected.push_back((VRef_s00cf_3bf0*)&ref);
                }
            } else if (pAnimal) {
                int st = v->mState;
                if (st == 0 || st == 1) {
                    if (v->mbFlagB1C != 0 || v->CanOccupyTerrain(VC0<Vec3_s00cf_3bf0*>((char*)pAnimal + 0xc0, 0x2c))) {
                        VRef_s00cf_3bf0 ref(v);
                        mSelected.push_back(&ref);
                    }
                }
            }
        }
        if (mSelected.mpBegin != mSelected.mpEnd) {
            Obj_s00cf_3bf0* q = (Obj_s00cf_3bf0*)pObj->Cast(0x1186577);
            if (q) {
                if (pB || pC || pAnimal) {
                    Vec3_s00cf_3bf0* pp = VC0<Vec3_s00cf_3bf0*>(q, 0x2c);
                    Func_CF30B0(pObj, *pp, 1);
                    if (pAnimal)
                        NounManager_s00cf_3bf0()->GetCurrentTerrainSphere()->Func_C77BF0(0x57fbc60);
                    else
                        NounManager_s00cf_3bf0()->GetCurrentTerrainSphere()->Func_C77BF0(0x52da1f6);
                    bAny = true;
                    char* src;
                    if (pB) src = (char*)pB + 0x34;
                    else if (pC) src = (char*)pC + 0x34;
                    else src = 0;
                    if (src) {
                        Vec3_s00cf_3bf0 p2 = *VC0<Vec3_s00cf_3bf0*>(src, 0x2c);
                        AudioSystem* at = GetSystemAT();
                        void* tok = at ? at->GetToken() : 0;
                        Start3dSoundByName(0x8216c026, tok, p2);
                        if (pB)
                            ((ObjB*)pB)->Func_BD1AB0(2);
                    }
                }
            }
        }
    }

    // Step 2: pick up vehicles when the clicked object itself is a vehicle.
    Vehicle_s00cf_3bf0* pV = (Vehicle_s00cf_3bf0*)pObj->Cast(0x137e8e0);
    bool bTutorial = bAny;
    if (pV) {
        mSelected.erase(mSelected.mpBegin, mSelected.mpEnd);
        for (Obj_s00cf_3bf0** it = objects.mpBegin; it != objects.mpEnd; ++it) {
            Obj_s00cf_3bf0* o = *it;
            if (!o) continue;
            Vehicle_s00cf_3bf0* v = (Vehicle_s00cf_3bf0*)VC1<void*, uint32_t>(o, 0xb8, 0x137e8e0);
            if (!v) continue;
            if (v->mState == 2) continue;
            if (v->mbFlagB1C == 0 && pV->mbFlagB1C == 0) {
                PlanetModel* pm = GetPlanetModel();
                if (pm) {
                    int c1 = pm->GetContinent(VC0<Vec3_s00cf_3bf0*>((char*)pV + 0x34, 0x2c));
                    int c2 = pm->GetContinent(VC0<Vec3_s00cf_3bf0*>((char*)v + 0x34, 0x2c));
                    if (c2 != c1) continue;
                }
            }
            Vehicle_s00cf_3bf0* ref = v;
            VC0<void>(ref, 0);                         // AddRef
            if (mSelected.mpEnd < mSelected.mpCap) {
                Vehicle_s00cf_3bf0** slot = mSelected.mpEnd++;
                if (slot) {
                    *slot = v;
                    VC0<void>(v, 0);
                }
            } else {
                mSelected.DoInsertValue(mSelected.mpEnd, &ref);
            }
            if (ref) VC0<void>(ref, 4);                // Release
        }
        if (mSelected.mpBegin != mSelected.mpEnd) {
            Vec3_s00cf_3bf0 p = *VC0<Vec3_s00cf_3bf0*>((char*)pV + 0x34, 0x2c);
            Func_CF30B0(pObj, p, 1);
            pV->Func_CA80E0(0xb);
            AudioSystem* at = GetSystemAT();
            void* tok = at ? at->GetToken() : 0;
            Start3dSoundByName(0x8541328e, tok, p);
            bTutorial = true;
        }
    }

    if (bTutorial) {
        CivModeStrategy_s00cf_3bf0* cs = GetCivModeStrategy_s00cf_3bf0();
        if (cs->HasCivTutorialOccurred(0x64e667b))
            cs->DoNextCivTutorial(0x64e667d, 1);
    }

    // inlined ~vector: release every element, then free the block
    for (Obj_s00cf_3bf0** p = objects.mpBegin; p < objects.mpEnd; ++p) {
        if (*p) VC0<void>(*p, 0xc0);
    }
    if (objects.mpBegin && ((int*)objects.mpBegin)[-1])
        operator delete[](objects.mpBegin);
    return 0;
}

// @ 0x00cf4440
int CityInputStrategy_s00cf_3bf0::FUN_00cf4440(uint32_t arg1, uint32_t messageId)
{
    (void)arg1;
    int handled = 0;
    if (!HandleMenuItem(messageId))
        handled = 1;
    if (messageId != 0x000001f6 && messageId != 0x037e95bb && messageId != 0x037e95b9 &&
        messageId != 0x037e95ba && messageId != 0x037e95bc && messageId != 0x037e95bd &&
        messageId != 0x051b40a4 && messageId != 0x046ee610 && messageId != 0x051b4174) {
        VC0<void>(GetGameTerrainCursor(), 0x64);
    }
    return handled;
}

// @ 0x00cf44c0
bool CityInputStrategy_s00cf_3bf0::FUN_00cf44c0(const Vec3_s00cf_3bf0* pPos)
{
    Vec3_s00cf_3bf0 pos = *pPos;
    FUN_00fd9c60()->mVec = pos;
    mpRollover->Func_E35350();

    GameTimeManager()->DecPauseGate(0x4bf38a6);
    if (GameTimeManager()->GetPauseGateCount(0x4bf38a8) > 0)
        GameTimeManager()->TogglePauseGate(0x4bf38a8);

    GameInputManager_s00cf_3bf0()->mField110--;
    cCameraControl* cam = GetCameraCtl();
    if (cam)
        cam->mbFlag364 = true;

    GameDataList* list = NounManager_s00cf_3bf0()->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                                          (void*)0x00acdff0, (void*)0x00b1e500,
                                                          0x18c43e8);
    for (uint32_t i = 0; i < (uint32_t)(list->mEntries.mpEnd - list->mEntries.mpBegin); ++i) {
        GameDataEntry* entry = list->mEntries.mpBegin[i];
        if (entry->mSub.IsLive())
            entry->Func_BD9BB0();
    }

    cSimSingleton::Instance()->Func_AE37C0(10, gSelectionPoint);

    void* profile = NounManager_s00cf_3bf0()->GetPlayerCivilization()->GetSpeciesProfile();
    FUN_0067cb30()->UpdateProperty(0x3d1afc95, &((cSpeciesProfile*)profile)->mKey);
    FUN_00b3d320_s00cf_3bf0()->Func_B1E410(gAppNameTag);
    return true;
}

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

// @ 0x00cf4c00
void CityInputStrategy::Reset(u32 mode)
{
    TreePairLayout* t1 = (TreePairLayout*)&mTreeBase04;
    ((TreeOps*)t1)->ResetA(t1->mn0C);
    t1->mn04 = (u32)&t1->mn04;
    t1->mn08 = (u32)&t1->mn04;
    t1->mn0C = 0;
    t1->mb10 = 0;
    t1->mn14 = 0;

    TreePairLayout* t2 = (TreePairLayout*)&mTreeBase20;
    ((TreeOps*)t2)->ResetB(t2->mn0C);
    t2->mn04 = (u32)&t2->mn04;
    t2->mn08 = (u32)&t2->mn04;
    t2->mn0C = 0;
    t2->mb10 = 0;
    t2->mn14 = 0;

    ArgCmd local;
    local.Ctor(&mTreeBase04);
    local.SetName((const char*)0x1478788);
    switch (mode) {
    case 0:
        local.SetName((const char*)0x147875c);
        break;
    case 1:
        local.SetName((const char*)0x1478774);
        break;
    default:
        local.SetName((const char*)0x147875c);
        break;
    }
    local.Finish();
    local.Destroy();
}

// @ 0x00cf4ca0
CityInputStrategy* CityInputStrategy::Ctor(u32 param)
{
    mn0C = 0;
    mn10 = 0;
    mn14 = 0;
    mn10 = 0;
    mb14 = 0;
    mn18 = 0;
    mn08 = (u32)((char*)this + 8);
    mn0C = (u32)((char*)this + 8);
    mn28 = 0;
    mn2C = 0;
    mn30 = 0;
    mn2C = 0;
    mb30 = 0;
    mn34 = 0;
    mn24 = (u32)((char*)this + 0x24);
    mn28 = (u32)((char*)this + 0x24);
    mpVtbl3C = (void*)0x13eb384;
    mpVtbl40 = (void*)0x13ec458;
    mn44 = 0;
    mn4C = param;
    mpVtbl = (void*)0x14787bc;
    mpVtbl3C = (void*)0x14787ac;
    mpVtbl40 = (void*)0x147879c;
    mb48 = 0;
    mp50 = 0;
    mp54 = 0;
    mp58 = 0;
    mp5C = 0;
    mp60 = 0;
    mp64 = 0;
    mp68 = 0;
    mp6C = 0;
    mp70 = 0;
    mp74 = 0;
    mn78 = 0;
    mn7C = 0;
    mp80 = 0;
    mn8C = 0;
    mn90 = 0;
    mn94 = 0;
    mn88 = (u32)((char*)this + 0x88);
    mn8C = (u32)((char*)this + 0x88);
    mn90 = 0;
    mb94 = 0;
    mn98 = 0;
    mnA8 = 0;
    mnAC = 0;
    mnB0 = 0;
    mnA4 = (u32)((char*)this + 0xA4);
    mnA8 = (u32)((char*)this + 0xA4);
    mnAC = 0;
    mbB0 = 0;
    mnB4 = 0;
    mStopwatch.Ctor(4, 0);
    mpD8 = 0;
    mbDC = 0;
    mnE0 = 0;

    SmallObj* obj = (SmallObj*)op_new(0x28, (const char*)0x13f09b4, 0, 0, 0, 0);
    if (obj != 0)
        obj = obj->Ctor();
    mpE4 = obj;
    if (obj != 0)
        ((void(__fastcall*)(void*))(*(void***)obj)[4 / 4])(obj);

    mE8Vector.mpBegin = 0;
    mE8Vector.mpEnd = 0;
    mE8Vector.mpCap = 0;
    mn100 = (u32)-1;
    mn140 = (u32)-1;
    mnFC = 0;
    mn104 = 0;
    mn108 = 0;
    mn10C = 0;
    mn110 = 0;
    mn114 = 0;
    mn118 = 0;
    mn11C = 0;
    mn120 = 0;
    mn124 = 0;
    mn128 = 0;
    mn12C = 0;
    mn130 = 0;
    mb134 = 0;
    mb135 = 0;
    mb136 = 0;
    mn13C = 0;
    mn138 = 0x1510d07;
    return this;
}

// @ 0x00cf4ea0
void CityInputStrategy::Destroy()
{
    mpVtbl = (void*)0x14787bc;
    mpVtbl3C = (void*)0x14787ac;
    mpVtbl40 = (void*)0x147879c;

    PieMenuVec* v = (PieMenuVec*)mp50;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp54;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp5C;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp60;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp64;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }
    v = (PieMenuVec*)mp68;
    if (v != 0) {
        v->DestroyRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && ((u32*)v->mpBegin)[-1] != 0)
            op_del_array(v->mpBegin);
        op_del_array(v);
    }

    void* o = mpE4;
    if (o != 0) {
        mpE4 = 0;
        ((void(__fastcall*)(void*))(*(void***)o)[8 / 4])(o);
    }
    mE8Vector.Dtor();
    o = mpE4;
    if (o != 0)
        ((void(__fastcall*)(void*))(*(void***)o)[8 / 4])(o);
    o = mpD8;
    if (o != 0)
        ((void(__fastcall*)(void*))(*(void***)o)[4 / 4])(o);

    TreePairLayout* t84 = (TreePairLayout*)&mTreeBase84;
    ((TreeOps*)&t84->mn1C)->ResetB(t84->mn28);
    ((TreeOps*)t84)->ResetA(t84->mn0C);
    o = mp80;
    if (o != 0)
        ((void(__fastcall*)(void*))(*(void***)o)[0xc / 4])(o);

    void* handler = mp6C;
    if (handler != 0) {
        mp6C = 0;
        RemoveHandler(handler, mp70, mp74, (void*)mn78, (void*)mn7C);
    }

    mpVtbl40 = (void*)0x13ec458;
    mpVtbl3C = (void*)0x13eb394;
    mpVtbl = (void*)0x14771e0;
    TreePairLayout* t = (TreePairLayout*)&mTreeBase04;
    ((TreeOps*)&t->mn1C)->ResetB(t->mn28);
    ((TreeOps*)t)->ResetA(t->mn0C);
}

// @ 0x00cf50e0
u32 __stdcall FUN_00cf50e0(void* a1, void* a2)
{
    if (a1 == 0)
        return 0;

    u32 v1 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0xd0036e08);
    u32 v2 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0xe9cb8ba);
    u32 v3 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0xee02c7);
    u32 v4 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0x137e8e0);
    u32 v5 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0x4f176642);
    u32 v6 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0x116d858);
    u32 v7 = ((u32(__thiscall*)(void*, u32))(*(void***)a1)[0xc / 4])(a1, 0x629baec);

    void* planet = FUN_01021260();

    if (v1 != 0) {
        u32* sp = ((ScanObj*)v1)->FUN_c0bc00();
        if (!((Planet_s00cf_4660*)planet)->SetSpeciesAsScanned(sp)) {
            u32 commCtx;
            commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
            void* terrain = ((NounMgr_s00cf_4660*)NounManager_s00cf_4660())->GetTerrain();
            void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
            sp = ((ScanObj*)v1)->FUN_c0bc00();
            u8* slot = ((Entry8*)((char*)node + 8))->Find(sp);
            *slot = 1;
            void* r = FUN_00ba5e10((void*)v1, 1);
            ((Obj9*)FUN_00b3d4f0(r))->Do();
        }
    }

    if (v4 != 0) {
        void* sub = (char*)v4 + 0x34;
        u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)sub)[0x98 / 4])(sub);
        if (!((Planet_s00cf_4660*)planet)->Known(sp)) {
            u32 commCtx;
            commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
            void* terrain = ((NounMgr_s00cf_4660*)NounManager_s00cf_4660())->GetTerrain();
            void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
            sp = (u32*)((void*(__fastcall*)(void*))(*(void***)sub)[0x98 / 4])(sub);
            u8* slot = ((Entry38*)((char*)node + 0x38))->Find(sp);
            *slot = 1;
            void* r = FUN_00ba57a0((void*)v4, 1);
            ((Obj9*)FUN_00b3d4f0(r))->Do();
        }
    }

    if (v2 != 0) {
        if (((Edition*)((char*)v2 + 0x120))->GetFileCount() != 2) {
            void* sub = (char*)v2 + 0x34;
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)sub)[0x98 / 4])(sub);
            u32 key = (u32)sp;
            if (!((Planet_s00cf_4660*)planet)->IsScanned(sp)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr_s00cf_4660*)NounManager_s00cf_4660())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                sp = (u32*)((void*(__fastcall*)(void*))(*(void***)sub)[0x98 / 4])(sub);
                u8* slot = ((Entry20*)((char*)node + 0x20))->Find(sp);
                *slot = 1;
                void* r = FUN_00ba57a0((void*)v2, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
            (void)key;
        }
    }

    if (v3 != 0) {
        void* obj = ((void*(__fastcall*)(void*))(*(void***)v3)[0x58 / 4])((void*)v3);
        if (obj != 0) {
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)obj)[0x4c / 4])(obj);
            u32 key = (u32)sp;
            if (!((Planet_s00cf_4660*)planet)->Known(&key)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr_s00cf_4660*)NounManager_s00cf_4660())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                u8* slot = ((Entry68*)((char*)node + 0x68))->Find(&key);
                *slot = 1;
                void* r = FUN_00ba58e0(obj, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
        }
    }

    if (v6 != 0) {
        void* obj = ((ObjA*)v6)->FUN_c9d9e0();
        if (obj != 0) {
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)obj)[0x4c / 4])(obj);
            u32 key = (u32)sp;
            if (!((Planet_s00cf_4660*)planet)->Known(&key)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr_s00cf_4660*)NounManager_s00cf_4660())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                u8* slot = ((Entry68*)((char*)node + 0x68))->Find(&key);
                *slot = 1;
                void* r = FUN_00ba58e0(obj, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
        }
    }

    if (v5 != 0) {
        void* obj = ((ObjB_s00cf_4660*)v5)->GetTribe();
        if (obj != 0) {
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)obj)[0x4c / 4])(obj);
            u32 key = (u32)sp;
            if (!((Planet_s00cf_4660*)planet)->Known(&key)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr_s00cf_4660*)NounManager_s00cf_4660())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                u8* slot = ((Entry68*)((char*)node + 0x68))->Find(&key);
                *slot = 1;
                void* r = FUN_00ba58e0(obj, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
        }
    }

    if (v7 != 0) {
        void* obj = ((TribeHolder*)v7)->mpTribe;
        if (obj != 0) {
            u32* sp = (u32*)((void*(__fastcall*)(void*))(*(void***)obj)[0x4c / 4])(obj);
            u32 key = (u32)sp;
            if (!((Planet_s00cf_4660*)planet)->Known(&key)) {
                u32 commCtx;
                commCtx = (u32)((StarRec*)((char*)planet + 0x13c))->GetCommContext();
                void* terrain = ((NounMgr_s00cf_4660*)NounManager_s00cf_4660())->GetTerrain();
                void* node = ((Sphere*)((char*)terrain + 0x11c0))->GetEntry(&commCtx);
                u8* slot = ((Entry68*)((char*)node + 0x68))->Find(&key);
                *slot = 1;
                void* r = FUN_00ba58e0(obj, 1);
                ((Obj9*)FUN_00b3d4f0(r))->Do();
            }
        }
    }

    return 0;
}

// @ 0x00e34ea0
void cToolButton::SetEnabled(bool enabled)
{
    mbEnabled = !enabled;
}
