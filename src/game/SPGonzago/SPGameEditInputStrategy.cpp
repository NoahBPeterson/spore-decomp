// src/game/SPGonzago/SPGameEditInputStrategy.cpp -- migrated from slice(s) s00d1a2b0, s00d16f40, s00d160c0, s00d15440, s00d14460, s00cd16a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameEditInputStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include <stddef.h>
#include "SP/cGameEditInputStrategy.h"
#include "cSPUILayout.h"
#include <math.h>
#include "SP/cPropertyManager.h"
#include <stdlib.h>
#include "EA/UTFWinControls/IWinComboBox.h"
#include "EA/UTFWinControls/IWinScrollbar.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/ResourceMan/Key.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void operator_delete(void* p);                    // 0x00f47380

// ---- items of slice s00cd16a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
struct cNested1c {
    uint32_t mPad00[3];                                      // +0x00 .. +0x0b
    void*    mpValue0c;                                      // +0x0c

    void Release(void* value);                               // 0x00e4b990
};
}
namespace Simulator {
struct cSub04 {
    uint32_t  mPad00[3];                                     // +0x00 .. +0x0b
    void*     mpValue0c;                                     // +0x0c
    uint32_t  mPad10[3];                                     // +0x10 .. +0x1b
    cNested1c mNested1c;                                     // +0x1c

    void Release(void* value);                               // 0x00b1b830
};
}
namespace Simulator {
struct cScenarioEditModeInputStrategy {
    void*    mpVtable;                                       // +0x00
    cSub04   mSub;                                           // +0x04

    void* Destroy(uint8_t flags);
};
}
extern "C" void operator_delete(void* p);                    // 0x00f47380
// ---- items of slice s00cd16a0 end

// ---- items of slice s00d14460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) uint32_t __cdecl wide_to_ulong(const wchar_t* pText, wchar_t** ppEnd, int32_t nBase);   // msvcr90!wcstoul
extern "C" __declspec(dllimport) int __cdecl wide_compare(const wchar_t* pA, const wchar_t* pB);  // msvcr90!wcscmp
extern "C" __declspec(dllimport) double __cdecl wide_to_double(const wchar_t* pText, wchar_t** ppEnd);   // msvcr90!wcstod
struct cSpatial {
    virtual void  p000();                                   // +0x00
    virtual void  p004();                                   // +0x04
    virtual void  p008();                                   // +0x08
    virtual void  p00c();                                   // +0x0c
    virtual void  p010();                                   // +0x10
    virtual void  p014();                                   // +0x14
    virtual void  p018();                                   // +0x18
    virtual void  p01c();                                   // +0x1c
    virtual void  p020();                                   // +0x20
    virtual void  p024();                                   // +0x24
    virtual void  p028();                                   // +0x28
    virtual void* GetPosition();                            // +0x2c
    virtual void  p030();                                   // +0x30
    virtual void  p034();                                   // +0x34
    virtual void  SetPosition(const void* pPosition);       // +0x38
    virtual void  SetOrientation(const void* pMatrix);      // +0x3c
};
struct cNoun {
    virtual void  v000();                                   // +0x00
    virtual void  v004();                                   // +0x04 (release)
    virtual void* v008();                                   // +0x08
    virtual void* v00c(uint32_t nType);                     // +0x0c (cast)
    virtual void  v010();                                   // +0x10
    virtual void  v014();                                   // +0x14
    virtual void  v018();                                   // +0x18
    virtual void  v01c();                                   // +0x1c
    virtual void  v020();                                   // +0x20
    virtual void  v024();                                   // +0x24
    virtual void  v028();                                   // +0x28
    virtual void  v02c();                                   // +0x2c
    virtual void  v030();                                   // +0x30
    virtual void  v034();                                   // +0x34
    virtual void  v038();                                   // +0x38
    virtual void  v03c();                                   // +0x3c
    virtual void  v040();                                   // +0x40
    virtual void  v044();                                   // +0x44
    virtual void  v048();                                   // +0x48
    virtual void  v04c();                                   // +0x4c
    virtual void  v050();                                   // +0x50
    virtual void  v054();                                   // +0x54
    virtual void  v058();                                   // +0x58
    virtual void  v05c();                                   // +0x5c
    virtual void  v060();                                   // +0x60
    virtual void  v064();                                   // +0x64
    virtual void  v068();                                   // +0x68
    virtual void  v06c();                                   // +0x6c
    virtual void  v070();                                   // +0x70
    virtual void  v074();                                   // +0x74
    virtual void  v078();                                   // +0x78
    uint8_t       mPad004[0x30];                            // +0x04 .. +0x33
    cSpatial      mSpatial;                                 // +0x34
    uint8_t       mPad038[0xd0];                            // +0x38 .. +0x107
    int32_t       mDefA;                                    // +0x108
    int32_t       mDefB;                                    // +0x10c
    int32_t       mDefC;                                    // +0x110
    int32_t       mDefD;                                    // +0x114
    int32_t       mValueCount;                              // +0x118
    int32_t       mValues[64];                              // +0x11c
};
struct cTerraformingManager {
    void SetMode(int32_t nMode);                            // 0x00bc08d0
};
void* __cdecl SP_TerraformingManager();                     // 0x00b3d430
// ---- items of slice s00d14460 end

// ---- items of slice s00d15440 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
struct Vec3 { float x, y, z; };
struct Obj;
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pii)(void*, int, int);
typedef void  (__thiscall *Fn_v_ppb)(void*, bool, void*);
typedef Obj* (__thiscall *Fn_p_pi)(void*, int);
extern "C" int*  DAT_0169dc6c = 0;                 // 0x0169dc6c  marker entry vector end
struct Obj {
    void* m_slot30();                       // vftable slot 0x30
    Vec3* m_position();                     // vftable slot 0x2c
};
struct cSPUILayout_s00d1_5440 {
    u8    mPad00[0x24];
    Obj*  FindWindowByID(int id, int flag); // 0x008105b0
    void  SetVisibility(int v);             // 0x00810590
};
Obj*  __cdecl SP_GetGameTerrainCursor();              // 0x00b30d70
namespace SP {
struct cGameEditInputStrategy_s00d1_5440 {
    u8    mPad00[0x40];
    u8    mSub40[0x0c];              // +0x040  sub-object handed to window slot 0x108
    void* mpField4C;                 // +0x04c
    u8    mPad50[0x54 - 0x50];
    void* mpNoun;                    // +0x054  noun (vftable slot 0x58 query)
    u8    mPad58[0x88 - 0x58];
    void* mpField88;                 // +0x088  slot 0x1c0 target
    u8    mPad8c[0xa4 - 0x8c];
    void* mpFieldA4;                 // +0x0a4
    void* mpFieldA8;                 // +0x0a8  slot 0xd8 marker-list owner
    u8    mPadAc[0xc4 - 0xac];
    Vec3  mVecC4;                    // +0x0c4
    float mQuatD0[4];                // +0x0d0
    cSPUILayout_s00d1_5440 mLayout;             // +0x0e0
    void* mpHandler;                 // +0x104
    void* mHandlerArgs[6];           // +0x108

    void  FUN_00d15440(Vec3* pTarget);
    void  FUN_00d15550();
    void  FUN_00d15600();
    void  FUN_00d15630(void* a1, float* pX, float* pY);
    float FUN_00d15780(void* a1, float* pX, float* pY);
    void  FUN_00d15980(void* a1, void* pObj);
    void  FUN_00d15a10(void* p);
    u32   StartSelection(void* p, u8 flag, u32 a3);  // 0x00d15ab0 (SP::cGameEditInputStrategy::StartSelection)
    u32   FUN_00d15af0(void* p, u8 flag, u32 a3);
    u32   GetGameplayMarkerTypeFromUI();  // 0x00d15fb0 (SP::cGameEditInputStrategy::GetGameplayMarkerTypeFromUI)
};
}
// ---- items of slice s00d15440 end

// ---- items of slice s00d160c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cVec3i {
    int x;                              // 0x00
    int y;                              // 0x04
    int z;                              // 0x08
};
struct cWString {
    void* mpBegin;                      // 0x00
    void* mpEnd;                        // 0x04
    void* mpCap;                        // 0x08
    void* mpField0c;                    // 0x0c
};
struct cConvertArg {
    void* mpValue;                      // 0x00
    void* mpTag04;                      // 0x04
    void* mpScratch08;                  // 0x08
};
struct cStrCmp {
    void*    mpField00;                 // 0x00
    void*    mpConv04;                  // 0x04
    cWString mStr08;                    // 0x08
    cWString mStr18;                    // 0x18

    bool operator()(u32 a, u32 b);      // 0x00d16760
};
struct cGameEditInputStrategy;
void __fastcall cStrCmp_Destroy(cStrCmp* p);                                   // 0x00d167e0
int  __cdecl StringCompare(const void* b1, const void* e1,
                           const void* b2, const void* e2);                    // 0x00576970
void* __cdecl ObjectError();                                                   // 0x008de1a0
void __cdecl operator delete[](void* p);                                       // 0x00f47380
static inline void VT_7C_2(void* p, void* a, void* b)
{
    ((void (__thiscall*)(void*, void*, void*))(*(void***)p)[0x1f])(p, a, b);
}
static inline void VT_60_1(void* p, void* a, int b)
{
    ((void (__thiscall*)(void*, void*, int))(*(void***)p)[0x18])(p, a, b);
}
static inline void cStrCmp_FreeStrings(cStrCmp& comp)
{
    if ((int)(((char*)comp.mStr18.mpCap - (char*)comp.mStr18.mpBegin) & 0xfffffffe) > 2
        && comp.mStr18.mpBegin != 0)
        operator delete[](comp.mStr18.mpBegin);
    if ((int)(((char*)comp.mStr08.mpCap - (char*)comp.mStr08.mpBegin) & 0xfffffffe) > 2
        && comp.mStr08.mpBegin != 0)
        operator delete[](comp.mStr08.mpBegin);
}
struct cGameEditInputStrategy {
    u8      mPad0000[0x7c];
    void*   mpField7c;                  // 0x7c  planet-name text edit object
    u8      mPad0080[0xf8 - 0x80];
    cVec3i  mPlanetF8;                  // 0xf8  selected planet

    void SetPlanet(const cVec3i* planet);   // 0x00d16b90
};
// ---- items of slice s00d160c0 end

// ---- items of slice s00d16f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_01479b60[];                 // 0x01479b60  handler id table (0x23 entries)
extern void*    g_01440aec;                   // 0x01440aec  element container base
extern uint32_t FNV1_String16(const wchar_t* text, uint32_t seed, int mode);  // 0x00932f30
extern uint32_t FUN_00d15b30(uint32_t markerType);            // 0x00d15b30 GetGameplayMarkerClassId
extern char     FUN_00d16620(uint32_t markerType, int* out);  // 0x00d16620 GetGameplayMarkerTypes
#pragma pack(push, 4)
struct Vector3    { float x, y, z; };
struct Quaternion { float x, y, z, w; };
class cUiObject {
public:
    virtual void v00();                                       // 0x00
    virtual void v04();                                       // 0x04  Release
    virtual void v08();                                       // 0x08
    virtual cUiObject* v0c(uint32_t id);                      // 0x0c  GetWindowByID
    virtual cUiObject* v10();                                 // 0x10  sub-object getter
    virtual void v14();                                       // 0x14
    virtual void v18(uint32_t text);                          // 0x18
    virtual uint32_t v1c();                                   // 0x1c
    virtual void v20(uint32_t text);                          // 0x20
    virtual void v24(cUiObject* target, uint32_t id);         // 0x24  register message handler
    virtual void v28();                                       // 0x28
    virtual void* v2c();                                      // 0x2c
    virtual void* v30();                                      // 0x30
    virtual void v34();                                       // 0x34
    virtual void v38();                                       // 0x38
    virtual void v3c(void* transform);                        // 0x3c
    virtual void* v40();                                      // 0x40
    virtual void v44(int a, int b);                           // 0x44
    virtual void v48();                                       // 0x48
    virtual void v4c();                                       // 0x4c
    virtual void v50(uint32_t color);                         // 0x50
    virtual const wchar_t* v54();                             // 0x54
    virtual cUiObject* v58();                                 // 0x58
    virtual void v5c();                                       // 0x5c
    virtual void v60(const float* rect);                      // 0x60
    virtual void v64(float a, float b);                       // 0x64
    virtual void v68();                                       // 0x68
    virtual void v6c();                                       // 0x6c
    virtual void v70();                                       // 0x70
    virtual void v74();                                       // 0x74
    virtual void v78();                                       // 0x78
    virtual void v7c(int a, int b);                           // 0x7c
    virtual void v80(const wchar_t* text);                    // 0x80
    virtual void v84();                                       // 0x84
    virtual void v88();                                       // 0x88
    virtual void v8c();                                       // 0x8c
    virtual void v90();                                       // 0x90
    virtual void v94(int a, int b);                           // 0x94
    virtual void v98();                                       // 0x98
    virtual void v9c();                                       // 0x9c
    virtual void va0();                                       // 0xa0
    virtual void va4();                                       // 0xa4
    virtual void va8();                                       // 0xa8
    virtual void vac();                                       // 0xac
    virtual void vb0();                                       // 0xb0
    virtual void vb4();                                       // 0xb4
    virtual cUiObject* vb8(uint32_t id);                      // 0xb8
    virtual void vbc();                                       // 0xbc
    virtual void vc0(int count);                              // 0xc0
    virtual void vc4();                                       // 0xc4
    virtual void vc8();                                       // 0xc8
    virtual void vcc(void* out);                              // 0xcc
    virtual void vd0(void* out);                              // 0xd0
    virtual void vd4();                                       // 0xd4
    virtual void vd8(void* item);                             // 0xd8
    virtual void vdc();                                       // 0xdc
    virtual void ve0();                                       // 0xe0
    virtual void ve4();                                       // 0xe4
};
class cUiObjectB {
public:
    virtual void v00();                                       // 0x00
    virtual void v04();                                       // 0x04  Release
    virtual void v08();                                       // 0x08
    virtual cUiObjectB* v0c(uint32_t id);                     // 0x0c
    virtual cUiObjectB* v10();                                // 0x10
    virtual void v14();                                       // 0x14
    virtual void v18(uint32_t text);                          // 0x18
    virtual uint32_t v1c();                                   // 0x1c
    virtual void v20(uint32_t index, uint32_t color);         // 0x20
    virtual void v24(cUiObjectB* target, uint32_t id);        // 0x24
    virtual void v28();                                       // 0x28
    virtual void* v2c(void* arg);                             // 0x2c
    virtual void* v30(float value);                           // 0x30
    virtual void v34();                                       // 0x34
    virtual void v38();                                       // 0x38
    virtual void v3c(void* transform);                        // 0x3c
    virtual void* v40(int arg);                               // 0x40
    virtual void v44(int a, int b);                           // 0x44
    virtual void v48();                                       // 0x48
    virtual void v4c();                                       // 0x4c
    virtual void v50(uint32_t color);                         // 0x50
    virtual const wchar_t* v54(uint32_t color);               // 0x54
    virtual cUiObjectB* v58();                                // 0x58
    virtual void v5c();                                       // 0x5c
    virtual void v60(const float* rect);                      // 0x60
    virtual void v64(float a, float b);                       // 0x64
    virtual void v68();                                       // 0x68
    virtual void v6c();                                       // 0x6c
    virtual void v70();                                       // 0x70
    virtual void v74();                                       // 0x74
    virtual void v78();                                       // 0x78
    virtual void v7c(int a, int b);                           // 0x7c
    virtual void v80(const wchar_t* text);                    // 0x80
    virtual void v84();                                       // 0x84
    virtual void v88();                                       // 0x88
    virtual void v8c();                                       // 0x8c
    virtual void v90();                                       // 0x90
    virtual void v94(int a, int b);                           // 0x94
    virtual void v98();                                       // 0x98
    virtual void v9c();                                       // 0x9c
    virtual void va0();                                       // 0xa0
    virtual void va4();                                       // 0xa4
    virtual void va8();                                       // 0xa8
    virtual void vac();                                       // 0xac
    virtual void vb0();                                       // 0xb0
    virtual void vb4();                                       // 0xb4
    virtual cUiObjectB* vb8(uint32_t id);                     // 0xb8
    virtual void vbc();                                       // 0xbc
    virtual void vc0(int count);                              // 0xc0
    virtual void vc4();                                       // 0xc4
    virtual void vc8();                                       // 0xc8
    virtual void vcc(void* out);                              // 0xcc
    virtual void vd0(void* out);                              // 0xd0
    virtual void vd4();                                       // 0xd4
    virtual void vd8(void* item);                             // 0xd8
    virtual void vdc();                                       // 0xdc
    virtual void ve0();                                       // 0xe0
    virtual void ve4();                                       // 0xe4
};
class cPropertyManager_s00d1_6f40 {
public:
    virtual void p00();                                       // 0x00
    virtual void p04();                                       // 0x04
    virtual void p08();                                       // 0x08
    virtual void p0c();                                       // 0x0c
    virtual void p10();                                       // 0x10
    virtual void p14();                                       // 0x14
    virtual void p18();                                       // 0x18
    virtual void p1c();                                       // 0x1c
    virtual void p20();                                       // 0x20
    virtual void p24();                                       // 0x24
    virtual void p28();                                       // 0x28
    virtual void p2c();                                       // 0x2c
    virtual char p30(uint32_t hash, cUiObject** out);         // 0x30
};
struct AutoRefCount {
    cUiObject* mpObject;
    void Assign(cUiObject* value);                            // 0x00b5f950  operator=
};
class cMarkerInfo {
public:
    char      mPad00[0x34];
    cUiObject mSub34;                                         // +0x34
    char      mPad38[0x1a4 - 0x38];
    cUiObject* mpField1a4;                                    // +0x1a4
};
namespace SP {
    class cPlanetModel_s00d1_6f40 {
    public:
        uint32_t GetPlanetKey();                              // 0x00b7e380
        void*    FUN_00b7f1f0(const void* ctx, void* a2, void* a3);  // 0x00b7f1f0
    };
}
namespace SP {
    cPlanetModel_s00d1_6f40* PlanetModel();                              // 0x00b3d350
}
namespace SP {
    cUiObject*    MessageServer();                            // 0x0067dcc0
}
namespace SP {
    cPropertyManager_s00d1_6f40* PropertyManager();                      // 0x0067de30
}
namespace SP {
    void QuaternionFromDirections(Quaternion* out, const Vector3* a,
                                  const Vector3* b);          // 0x00698180
}
class cSPUILayout_s00d1_6f40 {
public:
    cUiObject* FindWindowByID(uint32_t id, int includeChildren);   // 0x008105b0
};
class cGameEditModeStrategy {
public:
    char     mPad00[0x108];
    uint32_t mMarkerType;                                     // +0x108
    uint32_t mMarkerClassId;                                  // +0x10c
    uint32_t mField110;                                       // +0x110
    uint32_t mMarkerValue;                                    // +0x114
    char     mPad118[4];
    int      mMarkerValues[32];                               // +0x11c
    static void LoadScenario(cGameEditModeStrategy* self, int a, int b);   // 0x00b931c0
};
class cGameEditInputStrategy_s00d1_6f40 {
public:
    char        mPad00[0x3c];
    cUiObject   mHandler;                     // +0x3c   message handler target
    char        mPad40[0x54 - 0x40];
    cUiObject*  mpSelectedObjectManipulator;  // +0x54
    char        mPad58[0xa4 - 0x58];
    cUiObject*  mpUIA4;                       // +0xa4
    cUiObject*  mpScrollBarA8;                // +0xa8
    char        mPadAc[0xc4 - 0xac];
    Vector3     mFacing;                      // +0xc4   the marker's current facing
    Vector3     mFrameD0;                     // +0xd0   transform input for FUN_007dcb00
    char        mPadDc[0xe0 - 0xdc];
    cSPUILayout_s00d1_6f40 mLayout;                      // +0xe0
    char        mPadE4[0x104 - 0xe4];
    cUiObject*  mpServer;                     // +0x104  handler registration installed on the server
    cUiObject*  mpHandlerTarget;              // +0x108
    void*       mpHandlerTable;               // +0x10c  the id table at 0x01479b60
    int         mHandlerCount;                // +0x110
    uint32_t    mField114;                    // +0x114

    void FUN_00d16f40(Vector3* target);                       // 0x00d16f40
    void Activate();                                          // 0x00d17250
    void CommitChangesToGameplayMarker(cGameEditModeStrategy* scenario, char apply);  // 0x00d172d0
    void AddGameplayMarkerValue(int type, uint32_t color, int* value,
                                float* posX, float* posY);     // 0x00d17550
    uint32_t GetGameplayMarkerTypeFromUI();                   // 0x00d15fb0
    uint32_t FUN_00d16820();                                  // 0x00d16820
    void SetPlanet(uint32_t key);                             // 0x00d16b90
    void FUN_00d15780(int type, void* a3, void* a4);          // 0x00d15780
};
extern void     FUN_00d15350(cGameEditModeStrategy* scenario, uint32_t index, int value,
                             const wchar_t* text);            // 0x00d15350
extern void*    FUN_007dcb00(void* out, const void* frame, const Quaternion* q);  // 0x007dcb00
const float kMarkerAxisX  = 1.0f;
const float kMarkerAxisY  = 0.0f;
const float kMarkerAxisZ  = 0.0f;
const float kDotThreshold = 0.99f;            // 0x013ef480
// ---- items of slice s00d16f40 end

// ---- items of slice s00d1a2b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern int g_1440aec;
#pragma intrinsic(memcpy)
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);
namespace eastl {
extern char gEmptyString[];   // 0x01667bac
}
namespace eastl {
class allocator_s00d1_a2b0 { public:
    void* allocate(unsigned int n) {
        return operator new[](n, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    void deallocate(void* p, unsigned int) { operator delete[](p); }
};
}
namespace eastl {
template <class T> struct basic_string_s00d1_a2b0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00d1_a2b0 mAllocator;

    basic_string_s00d1_a2b0() { AllocateSelf(); }
    __forceinline basic_string_s00d1_a2b0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + CharStrlen(p)); }
    ~basic_string_s00d1_a2b0() { DeallocateSelf(); }

    static unsigned int CharStrlen(const T* p) {
        const T* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        return (unsigned int)(pCurrent - p);
    }
    void AllocateSelf() {
        mpBegin = (T*)gEmptyString;
        mpEnd = (T*)gEmptyString;
        mpCapacity = (T*)gEmptyString + 1;
    }
    void AllocateSelf(unsigned int n) {
        if (n > 1) {
            mpBegin = DoAllocate(n);
            mpEnd = mpBegin;
            mpCapacity = mpBegin + n;
        } else
            AllocateSelf();
    }
    T* DoAllocate(unsigned int n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void RangeInitialize(const T* pBegin, const T* pEnd) {
        const unsigned int n = (unsigned int)(pEnd - pBegin);
        AllocateSelf(n + 1);
        memcpy(mpBegin, pBegin, n * sizeof(T));
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    const T* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    basic_string_s00d1_a2b0& assign(const T* pBegin, const T* pEnd);   // 0x00423650 (wchar_t)
    basic_string_s00d1_a2b0& operator=(const basic_string_s00d1_a2b0& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    basic_string_s00d1_a2b0& sprintf(const T* pFormat, ...);           // 0x0041e050 (wchar_t)
};
}
namespace eastl {
typedef basic_string_s00d1_a2b0<char> string8_s00d1_a2b0;
}
namespace eastl {
typedef basic_string_s00d1_a2b0<wchar_t> string16_s00d1_a2b0;
}
namespace eastl {
template <class It, class Compare> void sort(It first, It last, Compare compare);
}
struct IdVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    IdVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~IdVector() {
        if (mpBegin && mpBegin[-1] != 0)
            operator delete[](mpBegin);
    }
};
namespace EA {
eastl::string16_s00d1_a2b0 ConvertToString16(const eastl::string8_s00d1_a2b0& s);   // 0x0093c6d0
}
namespace EA {
eastl::string8_s00d1_a2b0 ConvertToString8(const eastl::string16_s00d1_a2b0& s);    // 0x0093c570
}
namespace EA {
namespace Hash {
 uint32_t FNV1_String16(const wchar_t* p, uint32_t seed, int caseMode);   // 0x00932f30
}
}
namespace EA {
namespace IO {
int SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
              wchar_t* pExtension, int flags);                                           // 0x00930180
}
}
namespace EA {
namespace ResourceMan {
class Key_s00d1_a2b0 { public:
    uint32_t instanceID, typeID, groupID;
    Key_s00d1_a2b0(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
}
}
namespace EA {
namespace ResourceMan {
struct IResourceManager {
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
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
    virtual bool GetFileName(const Key_s00d1_a2b0& key, eastl::string16_s00d1_a2b0& dst);   // +0x7c
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager* GetManager();   // 0x0067dcd0
}
}
inline uint32_t id(const wchar_t* p) { return EA::Hash::FNV1_String16(p, 0x811c9dc5, 1); }
struct Property {
    union {
        struct { void* mpData; uint32_t mnItemSize; uint32_t mnItemCount; };
        uint32_t mValue[4];
    };
    short mnFlags;     // +0x10
    unsigned short mnType;   // +0x12
    uint32_t GetItemCount() const { return (mnFlags & 0x30) ? mnItemCount : (mnType != 0); }
    void* GetValue() { return (mnFlags & 0x30) ? mpData : (mnType ? (void*)this : 0); }
};
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool HasProperty(uint32_t propID);          // +0x1c
virtual void v20();
virtual void v24();
    virtual Property* GetProperty(uint32_t propID);     // +0x28
};
struct IPropertyManager {
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
    virtual bool GetPropertyList(uint32_t instanceID, PropertyList** ppList);   // +0x30
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual void GetPropertyListIDs(uint32_t groupID, IdVector& dst);           // +0x48
};
namespace SP {
IPropertyManager* PropertyManager_s00d1_a2b0();   // 0x0067de30
}
namespace SP {
bool GetPropertyAsString8(PropertyList* pList, uint32_t propID, eastl::string8_s00d1_a2b0& dst);   // 0x006a13b0
}
namespace SP {
bool GetPropertyAsUint32Array(PropertyList* pList, uint32_t propID, uint32_t& count, uint32_t*& pArray);   // 0x006a0840
}
namespace SP {
namespace {
struct cPropertyListNameSort {
    cPropertyListNameSort(uint32_t groupID);   // 0x00d196f0
    uint32_t mData[10];
};
uint32_t GetGameplayMarkerClassId(uint32_t typeHash);   // 0x00d15b30
}
}
template <class T> struct AutoRefCount_s00d1_a2b0 {
    T* mpObject;
    AutoRefCount_s00d1_a2b0() : mpObject(0) {}
    AutoRefCount_s00d1_a2b0(T* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount_s00d1_a2b0() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount_s00d1_a2b0& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** AsPointer() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
struct Rectangle { float x1, y1, x2, y2; };
struct IWindow_s00d1_a2b0 {
    virtual int AddRef();                                         // +0x00
    virtual int Release();                                        // +0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                          // +0x0c
    virtual IWindow_s00d1_a2b0* GetParent();                                 // +0x10
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual const Rectangle& GetArea();                           // +0x34
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
    virtual void SetArea(const Rectangle& area);                  // +0x60
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                   // +0x7c
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
    virtual void** GetChildrenBegin(void*** pResult);             // +0xcc (sret)
    virtual void** GetChildrenEnd(void*** pResult);               // +0xd0 (sret)
virtual void vd4();
virtual void vd8();
virtual void vdc();
    virtual void DisposeWindowFamily(IWindow_s00d1_a2b0* pChild);            // +0xe0
};
struct IWinComboBox_s00d1_a2b0 {
    virtual int AddRef();
    virtual int Release();
virtual void v08();
virtual void v0c();
    virtual IWindow_s00d1_a2b0* ToWindow();                                  // +0x10
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void AddItem(const wchar_t* text);                    // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
    virtual void SetSelection(int index, bool notify);           // +0x44
};
struct IWinScrollbar_s00d1_a2b0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual void SetValue(int value, bool notify);               // +0x24
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual void SetMaxValue(int value, bool notify);            // +0x34
};
class cSPUILayout_s00d1_a2b0 { public:
    IWindow_s00d1_a2b0* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
    uint32_t mData[3];
};
struct NounEntry {
    uint32_t mUnk0, mUnk4;
    uint32_t mClassID;          // +0x08
    uint32_t mInstanceID;       // +0x0c
    uint32_t mUnk10;
    PropertyList* mpPropList;   // +0x14
    NounEntry* mpNext;          // +0x18
};
struct NounEntryIterator {
    NounEntry* mpNode;
    NounEntry** mpBucket;
    NounEntryIterator(NounEntry** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    NounEntryIterator(NounEntry* pNode, NounEntry** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    NounEntryIterator& operator++() { increment(); return *this; }
    NounEntry* operator->() const { return mpNode; }
    bool operator!=(const NounEntryIterator& x) const { return mpNode != x.mpNode; }
};
struct NounEntryTable {
    uint32_t mUnk0;
    NounEntry** mpBucketArray;   // +0x04
    uint32_t mnBucketCount;      // +0x08
    NounEntryIterator begin() {
        NounEntryIterator i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    NounEntryIterator end() { return NounEntryIterator(mpBucketArray + mnBucketCount); }
};
struct Noun {
    uint32_t mUnk[3];
    PropertyList* mpPropList;   // +0x0c
};
struct cNounManager {
    uint32_t pad[8];
    NounEntryTable mEntries;   // +0x20
    Noun* GetNoun(uint32_t classID, uint32_t instanceID);   // 0x00b21000
};
namespace SP {
 cNounManager* NounManager();   // 0x00b3d300
}
const char* GetNounClassName(uint32_t classID);  // 0x00b21490
struct cCommandGameplayMarker {
    uint32_t pad[0x108 / 4];
    uint32_t mType;             // +0x108 (hash of the type name)
    uint32_t mDefClassID;       // +0x10c
    uint32_t mDefInstanceID;    // +0x110
    uint32_t mGroup;            // +0x114
    uint32_t mValueCount;       // +0x118
    uint32_t mValues[32];       // +0x11c
    static int ParseTypeEnum(const char* p);   // 0x00d14600
};
void SetGameplayMarkerDefaultValue(cCommandGameplayMarker* pMarker, uint32_t index, int type, const wchar_t* pDefault);
namespace SP {
class cGameEditInputStrategy_s00d1_a2b0 {
public:
    void ShowGameplayMarkerProperties(cCommandGameplayMarker* pMarker, bool bReadOnly, bool bSetDefaults);  // 0x00d1a2b0 (SP::cGameEditInputStrategy::ShowGameplayMarkerProperties)
    void AddLabel(const wchar_t* text, float& x, float& y);                                      // 0x00d15630
    void AddComboBox(uint32_t controlID, float& x, float& y);                                    // 0x00d15780
    void AddTextEdit(uint32_t controlID, int type, uint32_t* pValue, float& x, float& y);       // 0x00d17550

    IWinComboBox_s00d1_a2b0* FindComboBox(uint32_t controlID) {
        IWindow_s00d1_a2b0* pWindow = mLayout.FindWindowByID(controlID, true);
        return pWindow ? (IWinComboBox_s00d1_a2b0*)pWindow->Cast(0x2f5528d9) : 0;
    }

    uint32_t pad[0xa4 / 4];
    IWindow_s00d1_a2b0* mGameplayMarkerRoot;              // +0xa4
    IWindow_s00d1_a2b0* mGameplayMarkerArea;              // +0xa8
    IWinScrollbar_s00d1_a2b0* mGameplayMarkerScrollbar;   // +0xac
    uint32_t pad2[(0xe0 - 0xb0) / 4];
    cSPUILayout_s00d1_a2b0 mLayout;                       // +0xe0
};  // namespace SP
}
// ---- items of slice s00d1a2b0 end

// @ 0x00cd1750
void* Simulator::cScenarioEditModeInputStrategy::Destroy(uint8_t flags)
{
    cSub04& sub = mSub;
    cNested1c& nested = sub.mNested1c;
    mpVtable = (void*)0x014771e0;
    nested.Release(nested.mpValue0c);
    sub.Release(sub.mpValue0c);
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00d15100
void __stdcall FUN_00d15100(int32_t nA, int32_t nB)
{
    (void)nA;
    (void)nB;
    if (*(uint8_t*)0x0169dc20) {
        *(uint8_t*)0x0169dc20 = 0;
        cTerraformingManager* pManager = (cTerraformingManager*)SP_TerraformingManager();
        if (pManager)
            pManager->SetMode(1);
    }
}

// @ 0x00d15350
void FUN_00d15350(cNoun* pNoun, int32_t nIndex, int32_t nType, const wchar_t* pValue)
{
    switch (nType) {
    case 1:
        pNoun->mValues[nIndex] = (wide_compare(pValue, L"true") == 0) ? 1 : 0;
        return;
    case 9:
        pNoun->mValues[nIndex] = (int32_t)wide_to_ulong(pValue, 0, 10);
        return;
    case 13: {
        wchar_t* pEnd;
        float fValue = (float)wide_to_double(pValue, &pEnd);
        *(float*)&pNoun->mValues[nIndex] = fValue;
        return;
    }
    default:
        pNoun->mValues[nIndex] = (int32_t)wide_to_ulong(pValue, 0, 10);
        return;
    }
}

// @ 0x00d15600
void SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15600()
{
    ((Fn_v_pii)VTSLOT(mpFieldA4, 0x7c))(mpFieldA4, 1, 0);
    ((Fn_v_p)VTSLOT(mpFieldA8, 0xe4))(mpFieldA8);
}

// @ 0x00d15ab0
int SP::cGameEditInputStrategy::StartSelection(SP::cGameData * p, int flag, cSPVector3 const & a3)
{
    (void)a3;
    Obj* cursor = SP_GetGameTerrainCursor();
    void* key;
    if (p != 0)
        key = (void*)((Fn_p_pi)VTSLOT(p, 0xc))(p, (int)0x01186577);
    else
        key = (void*)0;
    ((Fn_v_ppb)VTSLOT(cursor, 0x9c))(cursor, flag & 1, key);
    return 0;
}

// @ 0x00d15af0
u32 SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15af0(void* p, u8 flag, u32 a3)
{
    (void)a3;
    Obj* cursor = SP_GetGameTerrainCursor();
    void* key;
    if (p != 0)
        key = (void*)((Fn_p_pi)VTSLOT(p, 0xc))(p, (int)0x01186577);
    else
        key = (void*)0;
    ((Fn_v_ppb)VTSLOT(cursor, 0xa0))(cursor, flag & 1, key);
    return 0;
}

// @ 0x00d16760
bool cStrCmp::operator()(u32 a, u32 b)
{
    cWString& strA = mStr08;
    cWString& strB = mStr18;
    cConvertArg argA = { (void*)a, (void*)0x00b1b104, mpField00 };
    cConvertArg argB = { (void*)b, (void*)0x00b1b104, mpField00 };
    VT_7C_2(mpConv04, &argA, &strA);
    VT_7C_2(mpConv04, &argB, &strB);
    return StringCompare(strA.mpBegin, strA.mpEnd, strB.mpBegin, strB.mpEnd) < 0;
}

// @ 0x00d167e0
void __fastcall cStrCmp_Destroy(cStrCmp* p)
{
    if ((int)(((char*)p->mStr18.mpCap - (char*)p->mStr18.mpBegin) & 0xfffffffe) > 2
        && p->mStr18.mpBegin != 0)
        operator delete[](p->mStr18.mpBegin);
    if ((int)(((char*)p->mStr08.mpCap - (char*)p->mStr08.mpBegin) & 0xfffffffe) > 2
        && p->mStr08.mpBegin != 0)
        operator delete[](p->mStr08.mpBegin);
}

// @ 0x00d16b90
void cGameEditInputStrategy::SetPlanet(const cVec3i* planet)
{
    mPlanetF8 = *planet;
    if (mpField7c != 0) {
        cWString str;
        str.mpBegin = (void*)0x01667bac;
        str.mpEnd = (void*)0x01667bac;
        str.mpCap = (void*)0x01667bae;
        if (planet->y != 0)
            VT_7C_2(ObjectError(), (void*)planet, &str);
        VT_60_1(mpField7c, str.mpBegin, 0);
        if ((int)(((char*)str.mpCap - (char*)str.mpBegin) & 0xfffffffe) > 2
            && str.mpBegin != 0)
            operator delete[](str.mpBegin);
    }
}

// @ 0x00d16c30
void SortInsertBounded(u32* first, u32* last, cStrCmp comp)
{
    if (first != last) {
        for (u32* i = first + 1; i != last; ++i) {
            u32 value = *i;
            u32* j = i;
            while (j != first && comp(value, j[-1])) {
                *j = j[-1];
                --j;
            }
            *j = value;
        }
    }
    cStrCmp_FreeStrings(comp);
}

// @ 0x00d16cc0
void SortInsert(u32* first, u32* last, cStrCmp comp)
{
    for (u32* i = first; i != last; ++i) {
        u32 value = *i;
        u32* dst = i;
        u32* src = i - 1;
        while (comp(value, *src)) {
            *dst = *src;
            --dst;
            --src;
        }
        *dst = value;
    }
    cStrCmp_FreeStrings(comp);
}

// @ 0x00d16d60
u32* Median3(u32* a, u32* b, u32* c, cStrCmp comp)
{
    if (comp(*a, *b)) {
        if (comp(*b, *c)) {
            cStrCmp_Destroy(&comp);
            return b;
        }
        if (comp(*a, *c)) {
            cStrCmp_Destroy(&comp);
            return c;
        }
        cStrCmp_Destroy(&comp);
        return a;
    } else {
        if (comp(*a, *c)) {
            cStrCmp_Destroy(&comp);
            return a;
        }
        if (!comp(*b, *c)) {
            cStrCmp_Destroy(&comp);
            return b;
        }
        cStrCmp_Destroy(&comp);
        return c;
    }
}

// @ 0x00d16e00
u32* Partition(u32* first, u32* last, u32 pivot, cStrCmp comp)
{
    for (;;) {
        while (comp(*first, pivot))
            ++first;
        while (comp(pivot, *--last))
            ;
        if (first >= last)
            break;
        u32 tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
    cStrCmp_FreeStrings(comp);
    return first;
}

// @ 0x00d16eb0
void SiftUp(u32* arr, int start, int pos, u32 value, cStrCmp comp)
{
    int parent = (pos - 1) >> 1;
    while (pos > start) {
        if (!comp(arr[parent], value))
            break;
        arr[pos] = arr[parent];
        pos = parent;
        parent = (parent - 1) >> 1;
    }
    arr[pos] = value;
    cStrCmp_FreeStrings(comp);
}

// @ 0x00d16f40
void cGameEditInputStrategy_s00d1_6f40::FUN_00d16f40(Vector3* target)
{
    if (mpSelectedObjectManipulator->v58() == 0)
        return;

    Vector3* ringPos = (Vector3*)mpSelectedObjectManipulator->v58()->v2c();
    Vector3 delta;
    delta.x = target->x - ringPos->x;
    delta.y = target->y - ringPos->y;
    delta.z = target->z - ringPos->z;
    float lenInv = 1.0f / sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    Vector3 dir;
    dir.x = delta.x * lenInv;
    dir.y = delta.y * lenInv;
    dir.z = delta.z * lenInv;
    if (mFacing.x * dir.x + mFacing.y * dir.y + mFacing.z * dir.z < kDotThreshold) {
        Quaternion fromDir;
        SP::QuaternionFromDirections(&fromDir, &mFacing, &dir);
        float angle = (float)acos(fromDir.w);
        angle = angle + angle;
        Vector3* ringDir = (Vector3*)mpSelectedObjectManipulator->v58()->v2c();
        float turn = ringDir->x * fromDir.x + ringDir->y * fromDir.y + ringDir->z * fromDir.z;
        float half = angle * (turn > 0.0f ? 0.5f : -0.5f);
        float sn = sinf(half);
        float cs = cosf(half);
        Quaternion orient;
        orient.x = sn * kMarkerAxisX;
        orient.y = sn * kMarkerAxisY;
        orient.z = sn * kMarkerAxisZ;
        orient.w = cs;

        cUiObject* marker = mpSelectedObjectManipulator->v58();
        float frame[4];
        marker->v3c(FUN_007dcb00(frame, &mFrameD0, &orient));

        cUiObject* info = marker->vb8(0x36be278);
        if (info == 0)
            return;
        cMarkerInfo* markerInfo = (cMarkerInfo*)info;
        cUiObject* handler = markerInfo->mpField1a4;
        if (handler == 0)
            return;
        cUiObjectB* sub = (cUiObjectB*)handler->v0c(0x1186577);
        if (sub == 0)
            return;
        void* a2 = markerInfo->mSub34.v30();
        void* a3 = sub->v2c(a2);
        SP::cPlanetModel_s00d1_6f40* pm = SP::PlanetModel();
        float ctx[4];
        sub->v3c(pm->FUN_00b7f1f0(ctx, a3, a2));
    }
}

// @ 0x00d17250
void cGameEditInputStrategy_s00d1_6f40::Activate()
{
    mpSelectedObjectManipulator = 0;
    SP::cPlanetModel_s00d1_6f40* pm = SP::PlanetModel();
    SetPlanet(pm->GetPlanetKey());

    cUiObject* handlerTarget = &mHandler;
    cUiObject* server = SP::MessageServer();
    mpServer = server;
    mpHandlerTarget = handlerTarget;
    mpHandlerTable = g_01479b60;
    mHandlerCount = 0x23;
    mField114 = 0;
    if (server != 0 && handlerTarget != 0) {
        for (uint32_t i = 0; i < 0x23; i++)
            server->v24(handlerTarget, g_01479b60[i]);
    }
}

// @ 0x00d172d0
void cGameEditInputStrategy_s00d1_6f40::CommitChangesToGameplayMarker(cGameEditModeStrategy* scenario, char apply)
{
    AutoRefCount selectedText;
    AutoRefCount valueText;
    selectedText.mpObject = 0;
    valueText.mpObject = 0;

    if (scenario != 0) {
        cPropertyManager_s00d1_6f40* pm = SP::PropertyManager();
        if (selectedText.mpObject != 0) {
            selectedText.mpObject = 0;
            selectedText.mpObject->v04();
        }
        uint32_t editorHash = FNV1_String16(L"LevelEditor", 0x811c9dc5, 1);
        if (pm->p30(editorHash, &selectedText.mpObject)) {
            scenario->mMarkerType    = GetGameplayMarkerTypeFromUI();
            scenario->mMarkerClassId = FUN_00d15b30(scenario->mMarkerType);
            scenario->mField110      = FUN_00d16820();

            cUiObject* win = mLayout.FindWindowByID(0xabc0fffa, 1);
            if (win != 0) {
                cUiObject* text = win->v0c(0xcf428691);
                if (text != 0) {
                    text->v00();
                    valueText.mpObject = text;
                    scenario->mMarkerValue = (uint32_t)wcstoul(text->v54(), 0, 10);
                }
            }

            int types[32];
            if (FUN_00d16620(scenario->mMarkerType, types)) {
                void* it = 0;
                void* itEnd = 0;
                mpScrollBarA8->vcc(&it);
                mpScrollBarA8->vd0(&itEnd);
                while (it != itEnd) {
                    // the scrollbar hands back the element address itself; the container base
                    // 0x01440aec is added to it
                    cUiObject* elem = *(cUiObject**)((char*)g_01440aec + (int)it);
                    uint32_t v = elem->v1c();
                    if ((v & 0xfff0) != 0xfff0 && (v & 0xabc00000) == 0xabc00000) {
                        uint32_t index = v & 0x543fffff;
                        valueText.Assign(elem->v0c(0xcf428691));
                        selectedText.Assign(elem->v0c(0x2f5528d9));
                        if (valueText.mpObject != 0) {
                            FUN_00d15350(scenario, index, types[index], valueText.mpObject->v54());
                        } else if (selectedText.mpObject != 0) {
                            scenario->mMarkerValues[index] = (int)selectedText.mpObject->v40();
                        }
                    }
                    it = *(void**)it;
                }
            }
        }
    }

    if (apply != 0 && scenario != 0) {
        cGameEditModeStrategy::LoadScenario(scenario, -1, -1);
        mpUIA4->v7c(1, 0);
        mpScrollBarA8->ve4();
    }
    if (valueText.mpObject != 0)
        valueText.mpObject->v04();
    if (selectedText.mpObject != 0)
        selectedText.mpObject->v04();
}

// @ 0x00d1a2b0
namespace SP {
void cGameEditInputStrategy_s00d1_a2b0::ShowGameplayMarkerProperties(cCommandGameplayMarker* pMarker, bool bReadOnly, bool bSetDefaults)
{
    AutoRefCount_s00d1_a2b0<PropertyList> pPropList;
    if (!PropertyManager_s00d1_a2b0()->GetPropertyList(id(L"LevelEditor"), pPropList.AsPointer()))
        return;

    // Clear out the previous controls.
    void** it;
    void** itEnd;
    mGameplayMarkerArea->GetChildrenBegin(&it);
    mGameplayMarkerArea->GetChildrenEnd(&itEnd);
    while (it != itEnd) {
        void** pNode = it;
        it = (void**)*pNode;
        mGameplayMarkerArea->DisposeWindowFamily((IWindow_s00d1_a2b0*)((char*)pNode + g_1440aec));
    }
    mGameplayMarkerRoot->SetFlag(1, true);

    float x, y;
    y = x = 5.0f;
    {
        AddLabel(L"Type", x, y);
        AutoRefCount_s00d1_a2b0<IWinComboBox_s00d1_a2b0> pCombo(FindComboBox(0xabc0fff8));
        if (!pCombo) {
            AddComboBox(0xabc0fff8, x, y);
            pCombo = FindComboBox(0xabc0fff8);
            Property* pTypes = pPropList->GetProperty(0x185a7a14);
            uint32_t count = pTypes->GetItemCount();
            int selection = 0;
            eastl::string16_s00d1_a2b0* pType = (eastl::string16_s00d1_a2b0*)pTypes->GetValue();
            for (uint32_t i = 0; i < count; i++, pType++) {
                pCombo->AddItem(pType->c_str());
                uint32_t hash = id(pType->c_str());
                if (pMarker->mType == 0)
                    pMarker->mType = hash;
                if (hash == pMarker->mType)
                    selection = i;
            }
            pCombo->SetSelection(selection, false);
        }
        pCombo->ToWindow()->SetFlag(2, bReadOnly);
        pCombo->ToWindow()->SetFlag(0x10, !bReadOnly);
        pCombo->ToWindow()->SetFlag(0x1000, !bReadOnly);

        // Definition: every noun of the marker's class.
        x = 5.0f;
        y = 35.0f;
        AddLabel(L"Definition", x, y);
        AddComboBox(0xabc0fff9, x, y);
        uint32_t classID = GetGameplayMarkerClassId(pMarker->mType);
        pCombo = FindComboBox(0xabc0fff9);
        int selection = 0;
        int index = 0;
        NounEntryTable& entries = NounManager()->mEntries;
        for (NounEntryIterator itNoun = entries.begin(); itNoun != entries.end(); ++itNoun) {
            if (itNoun->mClassID == classID) {
                uint32_t instanceID = itNoun->mInstanceID;
                eastl::string16_s00d1_a2b0 name;
                if (itNoun->mpPropList && itNoun->mpPropList->HasProperty(0x2e9c159)) {
                    eastl::string8_s00d1_a2b0 name8;
                    GetPropertyAsString8(itNoun->mpPropList, 0x2e9c159, name8);
                    name = EA::ConvertToString16(name8);
                }
                if (name.empty()) {
                    eastl::string8_s00d1_a2b0 className(GetNounClassName(itNoun->mClassID));
                    name.sprintf(L"%ls 0x%08x", EA::ConvertToString16(className).c_str(), instanceID);
                }
                pCombo->AddItem(name.c_str());
                if (pMarker->mDefClassID == classID && pMarker->mDefInstanceID == instanceID)
                    selection = index;
                index++;
            }
        }
        pCombo->SetSelection(selection, false);

        // Triggers.
        x = 5.0f;
        y = 65.0f;
        Noun* pNoun = NounManager()->GetNoun(pMarker->mDefClassID, pMarker->mDefInstanceID);
        if (pNoun && pNoun->mpPropList) {
            uint32_t triggerCount = 0;
            uint32_t* pTriggers = 0;
            if (GetPropertyAsUint32Array(pNoun->mpPropList, 0x3d03b03, triggerCount, pTriggers)) {
                IdVector ids;
                PropertyManager_s00d1_a2b0()->GetPropertyListIDs(0x3cddc79, ids);
                eastl::sort(ids.mpBegin, ids.mpEnd, cPropertyListNameSort(0x3cddc79));
                eastl::string16_s00d1_a2b0 label;
                eastl::string16_s00d1_a2b0 fileName;
                for (int i = 0; i < (int)triggerCount; i++) {
                    label.sprintf(L"Trigger %d", i);
                    AddLabel(label.c_str(), x, y);
                    uint32_t controlID = i + 0xabc0fff0;
                    AddComboBox(controlID, x, y);
                    pCombo = FindComboBox(controlID);
                    uint32_t current = pTriggers[i];
                    int triggerSel = 0;
                    pCombo->AddItem(L"None");
                    int item = 1;
                    for (uint32_t* pID = ids.mpBegin; pID != ids.mpEnd; pID++) {
                        uint32_t listID = *pID;
                        if (listID != 0x2ea8fb98) {
                            fileName.clear();
                            EA::ResourceMan::GetManager()->GetFileName(
                                EA::ResourceMan::Key_s00d1_a2b0(listID, 0xb1b104, 0x3cddc79), fileName);
                            wchar_t buffer[256];
                            EA::IO::SplitPath(fileName.c_str(), 0, 0, buffer, 0, 4);
                            pCombo->AddItem(buffer);
                            if (listID == current)
                                triggerSel = item;
                            item++;
                        }
                    }
                    pCombo->SetSelection(triggerSel, false);
                    x = 5.0f;
                    y += 30.0f;
                    pCombo->ToWindow()->SetFlag(2, false);
                    pCombo->ToWindow()->SetFlag(0x10, true);
                    pCombo->ToWindow()->SetFlag(0x1000, true);
                }
            }
        }

        AddLabel(L"Group", x, y);
        AddTextEdit(0xabc0fffa, 10, &pMarker->mGroup, x, y);
        x = 5.0f;
        y += 30.0f;
    }

    // Per-type parameters: triples of (label, type, default) strings.
    if (pPropList->HasProperty(pMarker->mType)) {
        Property* pParams = pPropList->GetProperty(pMarker->mType);
        uint32_t count = pParams->GetItemCount();
        if (count <= 0x60) {
            pMarker->mValueCount = count / 3;
            eastl::string16_s00d1_a2b0* pParam = (eastl::string16_s00d1_a2b0*)pParams->GetValue();
            for (uint32_t i = 0; i < count; i += 3, pParam += 3) {
                uint32_t index = i / 3;
                int type = cCommandGameplayMarker::ParseTypeEnum(EA::ConvertToString8(pParam[1]).c_str());
                AddLabel(pParam[0].c_str(), x, y);
                if (bSetDefaults)
                    SetGameplayMarkerDefaultValue(pMarker, index, type, pParam[2].c_str());
                if (type == 1 || type == 9 || type == 10 || type == 13 || !pPropList->HasProperty(type)) {
                    AddTextEdit(index | 0xabc00000, type, &pMarker->mValues[index], x, y);
                } else {
                    AddComboBox(index | 0xabc00000, x, y);
                    AutoRefCount_s00d1_a2b0<IWinComboBox_s00d1_a2b0> pCombo(FindComboBox(index | 0xabc00000));
                    Property* pChoices = pPropList->GetProperty(type);
                    uint32_t n = pChoices->GetItemCount();
                    eastl::string16_s00d1_a2b0* pChoice = (eastl::string16_s00d1_a2b0*)pChoices->GetValue();
                    for (; n; n--, pChoice++)
                        pCombo->AddItem(pChoice->c_str());
                    pCombo->SetSelection(pMarker->mValues[index], false);
                }
                x = 5.0f;
                y += 30.0f;
            }
        }
    }

    Rectangle area = mGameplayMarkerArea->GetArea();
    area.y1 = 0.0f;
    area.y2 = y;
    mGameplayMarkerArea->SetArea(area);
    if (mGameplayMarkerScrollbar) {
        RoundToInt(area.y2);
        mGameplayMarkerScrollbar->SetMaxValue(RoundToInt(y), true);
        mGameplayMarkerScrollbar->SetValue(0, true);
    }
}
}  // namespace SP
