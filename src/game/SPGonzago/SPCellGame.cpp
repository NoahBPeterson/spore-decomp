// src/game/SPGonzago/SPCellGame.cpp -- migrated from slice(s) s0137d820, s00e819b0, s00e80ba0, s00e7f630, s00e7dd90, s00e7ce10, s00e7b0a0, s00e7a190, s00e794f0, s00e777a0, s00e76880, s00e74a20, s00e73f60, s00e72430, s00e71520, s00e6e8c0, s00e6db70, s00e6cbd0, s00e6b370, s00e695f0, s00e67890, s00e66980, s00e65ad0, s00e63ac0, s00e61000, s00e5dba0, s00e5a430, s00e59640, s00e58730, s00e577a0, s00e558c0, s00e54b80, s00e52060, s00e51820, s00e4e8d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCellGame.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "cSPUILayout.h"
#include "SP/cIApp.h"
#include "SP/cCellGame.h"
#include "SP/cCellGfx.h"
#include "cSPTransform.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Swarm/cIVisualEffect.h"
#include <string.h>
#include "cSPVector3.h"
#include "SP/cCellUI.h"
// keep the canonical SP/cCellMode.h out of this TU: its SP::cCellMode would redefine the slice-local
// `namespace SP { class cCellMode { char pad0[9]; char f9, fa; int Activate(); }; }` stub that the
// landed 0x00e552f0 body (Activate) uses at +0x9/+0xa (C2011).  No landed body here names the
// canonical class; entry 29's 0x00e7d660 stays in its slice for the same reason.
#define GAME_SP_CCELLMODE_H
#include "SP/cSPFluidParticles.h"
#include "SP/cCellMode.h"

// unnamed retail callees and globals (address in the comment)
extern float g_16b39b4, g_16b39b8;  // 0x016b39b4 / 0x016b39b8
extern float g_16b3c88, g_16b3c8c;  // 0x016b3c88 / 0x016b3c8c
extern float g_16b3c94, g_16b3c98;  // 0x016b3c94 / 0x016b3c98
extern int   g_1483c34[];           // 0x01483c34 level threshold table (stride 7 dwords)
extern int   g_1483c14[];           // 0x01483c14 level value table
extern int   g_1483e60;             // 0x01483e60 special (level 1000)
extern void* g_16b3c0c;             // 0x016b3c0c ptr
extern float g_1550adc, g_1550af0, g_1550aec, g_1550ae0, g_1550ae4;
extern int   g_166c004, g_1550a84, g_1550ad8;
extern float g_16b3bf0, g_16b3bec, g_16b3be8, g_16b3be4, g_16b3be0;
extern int   g_16b3bfc, g_16b3bf8, g_16b3bf4;
extern "C" char FUN_00e5f810(void* box);      // 0x00e5f810 sBlockIsInRange (kept out of the slice blocks: a
                                              // landed call shaped `if (FUN_00e5f810(x) == 0) {` makes the tool's
                                              // _tu_defines_cpp read a definition and drop the slice's declaration)
int FUN_00e7ba30(void* self, float dt);       // 0x00e7ba30 (the TU defines it as int; s00e7dd90 spells it char)

// ---- items of slice s00e4e8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** Vt(void* p) { return *(void***)p; }
void* operator new(unsigned size, const char* name, int a, int b, int c, int d); // 0xf473a0
void* operator_new__(void* dst, int v, int n);          // 0x011e073e (operator new[])
void* FUN_00e56d40(void* out, void* v);                 // 0x00e56d40
void  FUN_00a7c3d0(int n);                              // 0x00a7c3d0
float FUN_00a7c350();                                   // 0x00a7c350
void  FUN_00a04ce0(int a);                              // 0x00a04ce0
void  FUN_00a04d00(int a);                              // 0x00a04d00
void* FUN_00b3d4d0();                                   // 0x00b3d4d0
void  FUN_00ad7e40(void* p);                            // 0x00ad7e40
extern float g_16b39b4, g_16b39b8;  // 0x016b39b4 / 0x016b39b8
extern float g_16b3c88, g_16b3c8c;  // 0x016b3c88 / 0x016b3c8c
extern float g_16b3c94, g_16b3c98;  // 0x016b3c94 / 0x016b3c98
extern int   g_1483c34[];           // 0x01483c34 level threshold table (stride 7 dwords)
extern int   g_1483c14[];           // 0x01483c14 level value table
extern int   g_1483e60;             // 0x01483e60 special (level 1000)
extern void* g_16b3c0c;             // 0x016b3c0c ptr
struct cTriggerMgr { void FUN_00ad7e40(void* v); };
extern float g_1550adc, g_1550af0, g_1550aec, g_1550ae0, g_1550ae4;
extern int   g_166c004, g_1550a84, g_1550ad8;
extern float g_16b3bf0, g_16b3bec, g_16b3be8, g_16b3be4, g_16b3be0;
extern int   g_16b3bfc, g_16b3bf8, g_16b3bf4;
// ---- items of slice s00e4e8d0 end

// ---- items of slice s00e51820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  gCellGame_16b3c04;   // cCellGame*
extern void*  gCellGfx_16b3c08;    // cCellGfx*
extern float  gOne_1485720, gHalf_1471064, gQuarter_13eb8a0,
              gEighth_1486d94, gSixteenth_13f115c, g32nd_140e964;
extern float  gVec_16b3c28[4];
extern float  gVec_15a7c4c[4];
extern "C" void  __cdecl SP_FluidParticlesSampleVelMagnitude(void* fluid, float* out); // 0xe4e590
extern "C" void* __cdecl SP_FluidParticlesSampleVelocity(float* out, void* fluid, float* in); // 0xe4e3c0
struct CellList {
  int   Head();       // 0xb72160
  char* Find(int id); // 0xb72210
};
// ---- items of slice s00e51820 end

// ---- items of slice s00e52060 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00e11e073e(void*, int, unsigned);   // memset thunk @0x11e073e
extern "C" float __cdecl FUN_00e837c0(unsigned key, float v);    // tuned-curve lookup
extern "C" void* __cdecl FUN_00e4ce40(void* guard);              // guard -> config block
extern unsigned g_16b3c84;
extern const float g_1485378;
#pragma auto_inline(off)
struct cGuard16 { void* p; cGuard16(); ~cGuard16(); };           // ctor @0x743b50, dtor @0xe82130
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct cPart {
    uint8_t active;       // 0x00
    uint8_t pad0[3];
    int     type;         // 0x04
    Vec3    pos;          // 0x08
    uint32_t pad1[9];     // 0x14
    float   radius;       // 0x38
    uint32_t pad2[3];     // 0x3c
};
struct cCellStats {
    uint32_t pad0[0x481];       // 0x0000 .. 0x1204
    int     counts[13];         // 0x1204: parts per type (active counts double)
    Vec3    center;             // 0x1238
    float   maxDist;            // 0x1244
    uint8_t flag1248;           // 0x1248
    uint8_t pad1249[3];
    float   val124c;            // 0x124c
    uint8_t flag1250;           // 0x1250
    uint8_t flag1251;           // 0x1251
    uint8_t pad1252[2];
    int     mask1254;           // 0x1254
    float   val1258;            // 0x1258
    float   val125c;            // 0x125c
    float   val1260;            // 0x1260
    float   val1264;            // 0x1264
    float   val1268;            // 0x1268
    int     val126c;            // 0x126c
    float   val1270;            // 0x1270
    int     numPicks;           // 0x1274
    int     picks[3];           // 0x1278
    int     val1284;            // 0x1284
    int     val1288;            // 0x1288
    int     nearestIdx;         // 0x128c
};
extern Vec3 g_16b3c28;
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
static inline const int& MinI(const int& a, const int& b) { return (b < a) ? b : a; }
static inline const float& MaxF(const float& a, const float& b) { return (a < b) ? b : a; }
// ---- items of slice s00e52060 end

// ---- items of slice s00e54b80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_16b3c08;             // 0x016b3c08 cell gfx globals
extern void* g_16b3c04;             // 0x016b3c04 cell game globals
extern char  g_16b3c00;             // 0x016b3c00
void* FUN_0067dd40();                                   // 0x0067dd40
void  FUN_007c4be0(void* self, void* p, int b);         // 0x007c4be0
void  FUN_007c3c50(int v);                              // 0x007c3c50
void* SP_EffectsManager();                              // 0x0067ddd0
void* FUN_00b3d400();                                   // 0x00b3d400
void* FUN_00b3d410(int a, void* b, int c);              // 0x00b3d410
void* SPUIHelpers_GetLayoutManager();                   // 0x00805070
char  FUN_00810760(int id);                             // 0x00810760
void  FUN_00810660(int id, int v);                      // 0x00810660
void  FUN_00e3e350(int a, void* b, int c);              // 0x00e3e350
void  cLocalInputState_Reset(void* self);               // 0x00697980
void  cUIMissionCardPanel_Refresh(void* self);          // 0x00e17df0
void  FUN_00e4f550_();                                  // 0x00e4f550 (cell tuning init)
// ---- items of slice s00e54b80 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void SP_sActivateGfx();  // 0x00e55120 (stays in the slice: not this object's)

// ---- items of slice s00e558c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*  __cdecl FUN_00b72210(int);
extern "C" bool   __cdecl FUN_00e83380(void*, unsigned int, float*);
extern "C" void   __cdecl FUN_00e82130();
extern "C" void   __cdecl FUN_00743b50();
extern "C" double __cdecl FUN_00e503a0(int);
extern "C" float g_15a853c;      // DAT_015a853c
extern "C" float g_14854c8;      // DAT_014854c8 (2.2f)
struct SomeObj { void* Lookup(); };     // 0xe51900
extern uint8_t* g_CellGame;      // cCellGame* at 0x16b3c04
extern int      g_16b3c10;       // 0x16b3c10
extern "C" double __cdecl FUN_00e55770(int);
extern "C" double __cdecl FUN_00e513d0(int, int, float, int, int);
extern "C" int    __cdecl SP_sGetSourceLevel();
extern "C" double __cdecl FUN_01041cd0(int, float, float);
extern "C" void   __cdecl FUN_00e53660(int, int);
extern "C" float  __cdecl sqrtf(float);
extern "C" float g_1485720;      // DAT_01485720
extern "C" float g_1483bd0[];    // kLevelSize
extern "C" float g_16b3c28_s00e5_58c0, g_16b3c2c, g_16b3c30;
extern uint8_t* g_16b3c0c_s00e5_58c0;       // 0x16b3c0c
struct IWindow;
struct cSPUILayout_s00e5_58c0 {
    IWindow* FindWindowByID(unsigned int id, bool a) const;   // 0x8105b0
};
struct IWindow {
virtual int v00();
virtual int v01();
virtual int v02();
virtual int v03();
virtual int v04();
virtual int v05();
virtual int v06();
virtual int v07();
virtual int v08();
virtual int v09();
virtual int v10();
virtual int v11();
virtual int v12();
virtual int v13();
virtual int v14();
virtual int v15();
virtual int v16();
virtual int v17();
virtual int v18();
virtual int v19();
virtual int v20();
virtual int v21();
virtual int v22();
virtual int v23();
virtual int v24();
virtual int v25();
virtual int v26();
virtual int v27();
virtual int v28();
virtual int v29();
virtual int v30();
virtual int v31(int, int);
};
// ---- items of slice s00e558c0 end

// ---- items of slice s00e577a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char* gspCellGfx;    // 0x016b3c08  SP::cCellGfx*
extern const float kf1485378;   // 0.0f
extern const float kf1485720;   // 1.0f
extern const float kf1488874;   // 0.1f
extern const float kf1470f1c;   // 2.0f
extern const float kf14853e0;   // 4.0f
extern const float kf1440f84;   // 0.16666667f
extern const float kf1486374;   // 0.8f
extern const float kf13f2100;   // 255.0f
extern const float kf14007f4;   // 15.0f
extern const float kf13ebc5c;   // 25.0f
extern const float kf15a7c28, kf15a7c2c, kf15a7c30;   // forward axes
extern const float kf15a7c34, kf15a7c38, kf15a7c3c;   // reference axes
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct CellPool { void* Get(unsigned int id); };       // 0x00b721d0
struct ResMap   { void* Find(unsigned int id); };      // 0x00b72210
struct CellGame { char pad0[0x1c]; CellPool mCells; };
extern CellGame* gspCellGame;        // 0x016b3c04  SP::cCellGame*
struct ObjHolder {
    void Init();       // 0x00743b50
    void Cleanup();    // 0x00e82130
};
void* FUN_00e823a0(int id, void* out);                 // thunk 0x00e4cc40
int   FUN_00e57340(int cell);
int   FUN_00e83470(void* a, int b);
void  FUN_00e50680(int a, void* b);
void  FUN_00e504b0(void* w, float v);
void  FUN_00e50750(float* a, float* b, float* c);
float FUN_005a6e00(float v);                           // Clamp01
void  FUN_00e54880(int cell);
char  FUN_00e52960(void* p);
int __fastcall FUN_00e4ee60(void* self, void* p);      // SP::sGetSourceLevel
struct RNG { double Next(double x); };                 // 0x009360d0
#define sMathRandom (*(RNG*)(void*)0x1601760)
struct IWindow_s00e5_77a0 {
  PV8 PV4 PV                              // 0x00 .. 0x30 (13)
  virtual float* GetArea();               // 0x34 (13)
  PV8 PV                                  // 0x38 .. 0x58 (9)
  virtual void SetColor(unsigned c);      // 0x5c (23)
  virtual void SetArea(const float* r);   // 0x60 (24)
  virtual void SetSize(float w, float h); // 0x64 (25)
  PV4 PV                                  // 0x68 .. 0x78 (5)
  virtual void SetFlag(int flag, int on); // 0x7c (31)
};
struct cSPUILayout_s00e5_77a0 {
  IWindow_s00e5_77a0* FindWindowByID(unsigned int id, int recurse);   // 0x008105b0
};
struct ConfigMgr {
  PV8 PV4
  virtual int Query(unsigned int id);     // 0x30
};
ConfigMgr* __cdecl ConfigManager();                        // 0x0067dd30
__declspec(noinline) char* FUN_00e52910(int param_1) {
  int iVar1 = *(int*)(*(int*)((char*)gspCellGame + 0x5190) + 0x7c);
  char* p;
  if (iVar1 == 0) {
    p = (char*)(param_1 + 0x248);
  } else {
    if (iVar1 != 2) return (char*)(param_1 + 0xe0);
    p = (char*)(param_1 + 0x194);
  }
  if (*(int*)p == -1) p = (char*)(param_1 + 0xe0);
  return p;
}
// ---- items of slice s00e577a0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00e57ec0(int param_1);  // 0x00e57ec0 (stays in the slice: not this object's)

// ---- items of slice s00e58730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char  gspCellGame_16b3c04[];   // holds SP::cCellGame*
extern "C" int   gLvlTableA[];            // 0x01483c14, stride 7 dwords
extern "C" int   gLvlTableB[];            // 0x01483c34
extern "C" int   gLvlTable1000[];         // 0x01483e60
extern "C" float k1488874;                // 0x01488874  0.1f
#define G (*(char**)gspCellGame_16b3c04)
struct Pool {
  void* Alloc();            // 0x00b72160
  void* Get(unsigned id);   // 0x00b72210, ret 4
  void* GetValid(int id);   // 0x00b721d0, ret 4
  void* Next(int* out);     // 0x00b72230, ret 4
  int   Begin();            // 0x00e31100, ret 0
  void  Remove(int id);     // 0x00b72260, ret 4
};
static inline Pool& CellsPool() { return *(Pool*)(G + 0x1c); }
static inline Pool& SecPool()   { return *(Pool*)(G + 0x8c); }
struct Ref {
  void* p;
  void Init();      // 0x00743b50
  void Release();   // 0x00e82130
};
static inline int* LevelEntry(int level) {
  if (level == 1000) return gLvlTable1000;
  int i = 0;
  if (level >= 0) {
    int* p = gLvlTableB;
    do { p += 7; ++i; } while (level >= *p);
  }
  return &gLvlTableA[i * 7];
}
// ---- items of slice s00e58730 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
float FUN_00e58b60(float a, float b);  // 0x00e58b60 (stays in the slice: not this object's)

// ---- items of slice s00e59640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kf13eb8c8;  // 0.3f
extern const float kf1477fc0;  // 300.0f
extern const float kf15a7c40;
extern float g16b4434, g16b4438, g16b443c;
extern int   g16b4440;
extern const float gExtentXMin;  // 0x016b3c88
extern const float gExtentYMin;  // 0x016b3c8c
extern const float gExtentXMax;  // 0x016b3c94
extern const float gExtentYMax;  // 0x016b3c98
struct CellPool_s00e5_9640 {  // 0x00b721d0 / 0x00e31100 / 0x00b72230
    void* Get(unsigned int id);
    int Begin();
    void* Next(int* out);
};
struct CellGame_s00e5_9640 { char pad0[0x1c]; CellPool_s00e5_9640 mCells; };
extern CellGame_s00e5_9640* gspCellGame_s00e5_9640;   // 0x016b3c04  SP::cCellGame*
void  FUN_00e57a10(void* cell, int x);             // 0x00e57a10
float FUN_00e51720(int a, int b);                   // 0x00e51720
void  FUN_00e4fac0(void* o);                        // 0x00e4fac0
void  FUN_00e84600(int, int, char, void*, float, char, int, int);  // 0x00e84600
void* __cdecl memset_thunk(void* p, int v, unsigned n);// 0x011e073e
int   FUN_00e50620(int a, int b);                   // 0x00e50620
int   FUN_00e4cce0(int a);                          // 0x00e4cce0
int   FUN_00e823a0_s00e5_9640(int id, void* out);              // 0x00e4cc40
void  FUN_00e51a40(int, int, void*, int);           // 0x00e51a40
float FUN_006994a0(float*, float*, const void*);    // 0x006994a0
void  FUN_00e56c30(float, float*, int*, int*);      // 0x00e56c30
struct CellSub { int Level(); };                    // 0x00e51430  thiscall
void  __cdecl FluidParticlesUpdate(void* p, float t);// 0x00e4ebe0
#define GAME_P (*(char**)((char*)gspCellGame_s00e5_9640 + 0x5190))
struct CbRec {
  char pad0[4];
  bool (*fn)(void* self, float x);  // +0x4
  char done;                        // +0x8
  char pad9[0x28 - 9];
  int  id;                          // +0x28
};
// ---- items of slice s00e59640 end

// ---- items of slice s00e5a430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kLevelSize[];                                      // 0x01483bd0, one float per level
struct cCellGameTC { char pad[0x514c]; float mLevelScale; };   // only the field this function reads
extern cCellGameTC* gspCellGame_s00e5_a430;                               // 0x016b3c04
namespace SP {
float sGetBoxSizeMultiplier2(int level, int unused);            // 0x00e51ff0, cdecl, float in st0
}
namespace SP {
__forceinline int RoundToInt_s00e5_a430(float f) { __asm cvtss2si eax, f }
}
namespace SP {
__forceinline uint32_t WrapTexCoord(int v) {
    uint32_t u = (uint32_t)v & 0x8000007fu;
    if ((int)u < 0) u = (u - 1 | 0xffffff80u) + 1;
    return u;
}
}
// ---- items of slice s00e5a430 end

// ---- items of slice s00e5dba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void*, int, unsigned int);
#define VPAD(n) virtual void vpad##n()
struct IRefObj {
    virtual int AddRef();    // +0x00
    virtual int Release();   // +0x04
};
template <class T> struct ARC {
    T* mp;
    ARC& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
    void Reset()
    {
        T* old = mp;
        if (old) {
            mp = 0;
            old->Release();
        }
    }
};
struct ILight : IRefObj {
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
    virtual void SetEnvironment(uint32_t id);                             // +0x30
};
struct ILightingManager {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
    virtual ILight* GetLightRig(uint32_t id, int a, int b);               // +0x18
};
struct IApp {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
    virtual int GetWindowWidth();                                         // +0x50
    VPAD(21);
    virtual int GetWindowHeight();                                        // +0x58
};
struct ICamera : IRefObj {
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
VPAD(22);
VPAD(23);
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
VPAD(28);
VPAD(29);
VPAD(30);
VPAD(31);
VPAD(32);
    virtual void SetViewport(int a, int b);                               // +0x84 (index 33)
};
struct IEffectsWorld : IRefObj {
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
    virtual void AttachCamera(ICamera* camera);                            // +0x1c
};
struct IEffectsManager {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
    virtual IEffectsWorld* CreateWorld(uint32_t id, const char* name);     // +0x4c
};
struct IModelWorld : IRefObj {
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
VPAD(22);
VPAD(23);
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
VPAD(28);
VPAD(29);
VPAD(30);
VPAD(31);
VPAD(32);
VPAD(33);
VPAD(34);
VPAD(35);
VPAD(36);
VPAD(37);
VPAD(38);
VPAD(39);
VPAD(40);
VPAD(41);
VPAD(42);
VPAD(43);
VPAD(44);
VPAD(45);
VPAD(46);
    virtual void SetFarClip(float f);                                      // +0xbc (index 47)
VPAD(48);
VPAD(49);
VPAD(50);
VPAD(51);
VPAD(52);
VPAD(53);
VPAD(54);
VPAD(55);
VPAD(56);
VPAD(57);
VPAD(58);
VPAD(59);
VPAD(60);
VPAD(61);
VPAD(62);
VPAD(63);
VPAD(64);
VPAD(65);
VPAD(66);
VPAD(67);
VPAD(68);
VPAD(69);
VPAD(70);
VPAD(71);
VPAD(72);
VPAD(73);
VPAD(74);
VPAD(75);
VPAD(76);
VPAD(77);
VPAD(78);
VPAD(79);
    virtual void SetLighting(ILight* light, int a, int b);                 // +0x140 (index 80)
};
struct IModelManager {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
    virtual IModelWorld* CreateWorld(uint32_t id, const char* name, int flags);   // +0x14
};
struct ILayer : IRefObj {
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
    virtual void AddEffectsWorld(IEffectsWorld* world);                    // +0x18
    virtual void AddModelWorld(IModelWorld* world, int a, int b, int c, int d);   // +0x1c
};
struct ILayerManager {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
    virtual ILayer* GetLayer(const wchar_t* name);                         // +0x20
};
struct cViewerPhysics { void Init(int flag); };                            // 0x007c4dd0 (global 0x016b42b8)
extern cViewerPhysics gEditorPhysicsWorld;                                 // 0x016b42b8
struct EffectSlots {
    uint32_t s[4];
};
struct cCellViewport {
    uint32_t pad[(0x161a0 - 0x168) / 4];
    void Init(int w, int h);
};                         // 0x00b72080 (ret 8)
struct cCellGfx_s00e5_dba0 {
    uint32_t pad000[0x4c / 4];
    float mScale;                                // +0x04c
    uint32_t pad050[(0x15c - 0x50) / 4];
    ARC<IRefObj> mpSkyboxEffect;                 // +0x15c
    uint32_t pad160[(0x168 - 0x160) / 4];
    cCellViewport mViewport;                     // +0x168 .. 0x161a0
    ARC<ILight> mpLighting;                      // +0x161a0
    ARC<ICamera> mpBeachCamera;                  // +0x161a4
    ARC<IModelWorld> mpBeachModels;              // +0x161a8
    ARC<IEffectsWorld> mpBeachEffects;           // +0x161ac
    ARC<ICamera> mpSkyCamera;                    // +0x161b0
    ARC<IEffectsWorld> mpSkyEffects;             // +0x161b4
    ARC<ICamera> mpBackCamera;                   // +0x161b8
    ARC<IEffectsWorld> mpBackEffects;            // +0x161bc
    ARC<IModelWorld> mpBackModels;               // +0x161c0
    ARC<ILayer> mpBackLayer;                     // +0x161c4
    ARC<IEffectsWorld> mpMainEffects;            // +0x161c8
    ARC<IModelWorld> mpMainModels;               // +0x161cc
    ARC<ILayer> mpMainLayer;                     // +0x161d0
    ARC<IEffectsWorld> mpFgEffects;              // +0x161d4
    ARC<ICamera> mpFgCamera;                     // +0x161d8
    uint32_t pad161dc[(0x161f0 - 0x161dc) / 4];
    uint32_t mEffectCount;                       // +0x161f0
    EffectSlots mEffectSlots;                    // +0x161f4
    uint8_t mFlag16204;                          // +0x16204
    uint8_t mFlag16205;                          // +0x16205
};
extern cCellGfx_s00e5_dba0* gspCellGfx_s00e5_dba0;                                               // 0x016b3c08
namespace SP {
ILightingManager* __cdecl LightingManager();                               // 0x0067dd90
}
namespace SP {
IApp*             __cdecl App();                                           // 0x0067dd10
}
namespace SP {
IEffectsManager*  __cdecl EffectsManager();                                // 0x0067ddd0
}
namespace SP {
IModelManager*    __cdecl ModelManager();                                  // 0x0067dd80
}
namespace SP {
ILayerManager*    __cdecl LayerManager();                                  // 0x0067cb20
}
namespace SP {
ICamera*          __cdecl GetLayerCamera(int layer);                       // 0x00e82730
}
namespace SP {
void __cdecl CreateEffectSafe(IEffectsWorld* world, uint32_t effectId, int a, ARC<IRefObj>* out);   // 0x00628450
}
// ---- items of slice s00e5dba0 end

// ---- items of slice s00e61000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_16b3dd0;
extern float  g_1485720;
extern float  g_1485548;
extern float  g_15a7c28;
extern float  g_15a7c2c;
extern float  g_15a7c30;
extern float  g_16b3c2c;
extern float  g_16b3c30;
extern char   g_15a7c40[];
extern char   g_16b3dac[];
extern float  g_16b3c28_s00e6_1000;
int   __cdecl f5c9d0(void);                                               // 0x00e5c9d0
void  __cdecl f83910(void*, int, int, int);                               // 0x00e83910
void  __cdecl f828c0(void);                                               // 0x00e828c0
int*  __cdecl f4ce40(void*);                                              // 0x00e4ce40
int   __cdecl f82970(void);                                               // 0x00e82970
void  __cdecl f82920(void*);                                              // 0x00e82920
void  __cdecl f82ce0(void*);                                              // 0x00e82ce0
void  __cdecl f91ff50(void*);                                             // 0x0091ff50
void  __cdecl f4fcd0(void*);                                              // 0x00e4fcd0
void* __cdecl memset_stub(void*, int, unsigned);                          // 0x011e073e
void* __cdecl f453b20(void*, const void*, float);                         // 0x00453b20
void  __fastcall f743b50(void*);                                          // 0x00743b50
void  __fastcall f82130(void*);                                           // 0x00e82130
struct Matrix33 {
    float x[3];
    float y[3];
    float z[3];
    Matrix33& operator=(const Matrix33&);   // 0x0041cb40 (out of line)
};
struct cSPTransform_s00e6_1000 {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    float          mTranslation[3];     // +0x04
    float          mScale;              // +0x10
    Matrix33       mRotation;           // +0x14
    cSPTransform_s00e6_1000()
    {
        mFlags = 0;
        mModificationCount = 0;
        mTranslation[0] = g_16b3c28_s00e6_1000;
        mTranslation[1] = g_16b3c2c;
        mTranslation[2] = g_16b3c30;
        mScale = g_1485720;
        mRotation = *(const Matrix33*)g_16b3dac;
    }
    cSPTransform_s00e6_1000(const cSPTransform_s00e6_1000& o)
    {
        mFlags = o.mFlags;
        mModificationCount = o.mModificationCount;
        mTranslation[0] = o.mTranslation[0];
        mTranslation[1] = o.mTranslation[1];
        mTranslation[2] = o.mTranslation[2];
        mScale = o.mScale;
        mRotation = o.mRotation;
    }
    cSPTransform_s00e6_1000& operator=(const cSPTransform_s00e6_1000&);   // 0x00537dc0 (out of line)
};
struct CellObj5190;
struct Invoker1c { int Call(); };
struct Sub10 { char pad[0xc]; };
struct CellObj5190 {
    char            pad0[0xc];
    int             field_0c;        // +0x0c
    Sub10           sub10;           // +0x10
    Invoker1c*      field_1c;        // +0x1c
    int             field_20;        // +0x20
    int             field_24;        // +0x24
    int             field_28;        // +0x28
    int             field_2c;        // +0x2c
    char            pad30[0xb4];
    int             field_e4;        // +0xe4
    bool            field_e8;        // +0xe8
};
struct cCellGame {
    char            pad0[0x40fc];
    unsigned int    midPlayerCell;   // +0x40fc
    char            pad4100[0x1c];
    int             field_411c;      // +0x411c
    char            pad4120[0x1044]; // 0x4120 .. 0x5164
    int             field_5164;      // +0x5164
    char            field_5168;      // +0x5168
    char            pad5169[0x27];
    CellObj5190*    field_5190;      // +0x5190
    char            pad5194[0x46];
    char            field_51da;      // +0x51da
};
extern cCellGame*   gspCellGame_s00e6_1000;     // 0x016b3c04
void FUN_00e611b0(void);
void* operator new(unsigned, const char*, int, int, const char*, int);
struct B1 { virtual void b1(); };
struct B2 { virtual void b2(); };
struct CellAbility : B1, B2 {
    int  f08;
    int  f0c;
    int  f10, f14, f18;
    int  f1c, f20, f24, f28;
    int  f2c;
    int  f30;
    char o34[0x68 - 0x34];
    char b68, b69;
    int  f6c, f70, f74;
    char o78[0x80 - 0x78];
    int  f7c;
    char buf80[0x60];
    char b_e0, b_e1, b_e2;
    char pad_e3;
    int  f_e4;
    char b_e8, b_e9;
    char pad_ea[0xec - 0xea];
    __forceinline CellAbility()
    {
        f10 = 0;
        f7c = 1;
        b_e2 = 1;
        f14 = 0; f18 = 0;
        b68 = 0;
        f1c = 0; f20 = 0; f24 = 0; f28 = 0;
        b69 = 0;
        f70 = 0; f6c = 0;
        f_e4 = 0;
        b_e8 = 0;
        f74 = 0;
        b_e0 = 0; b_e1 = 0;
        f30 = 10;
        f2c = 0;
        f91ff50(o78);
        f4fcd0(o34);
        memset_stub(buf80, 0, 0x60);
        gspCellGame_s00e6_1000->field_51da = 0;
        b_e9 = 0;
    }
};
struct SaveGameObj : B1, B2 {
    int f08;
    int pad0c;
    int f10, f14, f18;
    char pad1c[0xec - 0x1c];
    SaveGameObj()
    {
        f08 = 0;
        f10 = 0; f14 = 0; f18 = 0;
    }
};
// ---- items of slice s00e61000 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
__declspec(noinline) CellAbility* FUN_00e61550();  // 0x00e61550 (stays in the slice: not this object's)

// ---- items of slice s00e63ac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl sPartIntersectTarget(void*, void*, void*);                 // 0xe63480
extern "C" int   __cdecl WStr_Format(wchar_t*, const wchar_t*, ...);                // 0x41e050
extern "C" void  __cdecl FUN_00e627a0(int);
extern "C" void  __cdecl FUN_00e5bd30(void*);
extern "C" int   __cdecl EA_Hash_FNV1_String8(const char*, uint32_t, int);          // 0x932e80
extern "C" void* __cdecl SP_CreateEffectSafe(int, int, int, int);                   // 0x628450
extern "C" void* __cdecl FUN_0067de90(int, ...);
extern "C" void* __cdecl FUN_0099efa0(void*, void*, void*);
extern "C" void* __cdecl FUN_00e5c860(void*, void*, void*);
extern "C" void  __cdecl FUN_00e5c7d0(void*);
extern "C" void* __cdecl operator_new(uint32_t, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void  __cdecl operator_delete(void*);                                    // 0xf47380
extern void* g_CellGfx;               // cCellGfx*  stored at 0x16b3c08
struct cSPVector3_s00e6_3ac0 { float x, y, z; };
struct cSPMatrix3_s00e6_3ac0 { float m[9]; };
struct cSPTransform_s00e6_3ac0 {                 // size 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3_s00e6_3ac0 mTranslation;          // +0x4
    float mScale;                     // +0x10
    cSPMatrix3_s00e6_3ac0 mRotation;             // +0x14
};
struct RefObj {
    virtual int AddRef();
    virtual int Release();
virtual int v2();
virtual int v3();
virtual int v4();
virtual int v5();
virtual int v6();
virtual int v7();
virtual int v8();
virtual int v9();
virtual int v10();
virtual int v11();
virtual int v12();
virtual int v13();
virtual int v14();
virtual int v15();
virtual int v16();
virtual int v17();
virtual int v18();
virtual int v19();
virtual int v20();
virtual int v21();
virtual int v22();
virtual int v23();
};
struct VObj {
virtual int v00();
virtual int v01();
virtual int v02();
virtual int v03();
virtual int v04();
virtual int v05();
virtual int v06();
virtual int v07();
virtual int v08();
virtual int v09();
virtual int v10();
virtual int v11();
virtual int v12();
virtual int v13();
virtual int v14();
virtual int v15();
virtual int v16();
virtual int v17();
virtual int v18();
virtual int v19();
virtual int v20();
virtual int v21();
virtual int v22();
};
extern "C" void  __cdecl cSPTransform_assign(cSPTransform_s00e6_3ac0*, const cSPTransform_s00e6_3ac0*);   // 0x537dc0
struct IRef;
extern "C" IRef* __cdecl FUN_00e61550_s00e6_3ac0();
extern "C" void  __cdecl FUN_00743b50_s00e6_3ac0(void*);
extern "C" void* __cdecl FUN_00b72210_s00e6_3ac0(void* p, int id);
extern void* g_CellGame_s00e6_3ac0;              // cCellGame* stored at 0x16b3c04
#define CG(off) (*(void**)((char*)g_CellGame_s00e6_3ac0 + (off)))
struct Cell;                          // {cSPTransform m0; cSPTransform m1; void* mpPart;} size 0x74
struct CellArray { Cell* begin; Cell* end; Cell* cap; };
struct IRef { virtual int AddRef(); virtual int Release(); };
struct AutoRef {
    IRef* mpObject;
    AutoRef& operator=(IRef* p) {
        if (p != mpObject) {
            IRef* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
extern AutoRef g_16b3de0;
struct PairIU { int a; uint32_t b; };
struct FixedVec8 {
    PairIU* mpBegin;
    PairIU* mpEnd;
    PairIU* mpCapacity;
    uint32_t mOverflowAllocator;
    PairIU* mpPoolBegin;
    void DoInsertValue(PairIU* position, const PairIU& value);
};
struct SoundElem {
    SoundElem& operator=(const SoundElem& o);   // out-of-line at 0xe5c7d0
    char raw[0x2c];
};
struct FixedVec44 {
    SoundElem* mpBegin;
    SoundElem* mpEnd;
    SoundElem* mpCapacity;
    uint32_t mOverflowAllocator;
    SoundElem* mpPoolBegin;
    void DoInsertValue(SoundElem* position, const SoundElem& value);
};
struct FmtObj {
virtual int v00();
virtual int v01();
virtual int v02();
virtual int v03();
virtual int v04();
virtual int v05();
virtual int v06();
virtual int v07();
virtual int v08();
virtual int v09();
virtual int v10();
virtual int v11();
virtual int v12();
virtual int v13();
virtual int v14();
virtual int v15();
virtual int v16();
virtual int v17();
virtual int v18();
virtual int v19();
virtual int v20();
virtual int v21();
virtual int v22();
    uint8_t pad[0x8c];
    int mState;   // +0x90
    void Format(wchar_t* buf);
};
struct VecInsert44 {
    SoundElem* mpBegin;
    SoundElem* mpEnd;
    SoundElem* mpCapacity;
    uint32_t mOverflowAllocator;
    SoundElem* mpPoolBegin;
    SoundElem* insert(SoundElem* position, const SoundElem& value);
};
struct Gfx58 {
virtual int v00();
virtual int v01();
virtual int v02();
virtual int v03();
virtual int v04();
virtual int v05();
virtual int v06();
virtual int v07();
virtual int v08();
virtual int v09();
virtual int v10();
virtual int v11();
    virtual int v12(void*, int, void*, void*, int);
};
struct CellData;
struct SimpleVec { CellData** mpBegin; CellData** mpEnd; CellData** mpCapacity;
                   void DoInsertValue(CellData** position, CellData*& value); };
struct CellGfxObj {
    uint8_t pad0[0x28];
    SimpleVec mVector;        // +0x28
    uint8_t pad2[0x58 - 0x28 - 0xc];
    Gfx58* mpAt58;            // +0x58
};
// ---- items of slice s00e63ac0 end

// ---- items of slice s00e65ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_one_1485720;      // 0x01485720  1.0f
extern char   g_16b3dac[36];      // 0x016b3dac  identity rotation matrix
extern "C" void  FUN_00e65a00(int* ref);                    // 0x00e65a00
extern "C" void  FUN_00e826e0(int sound);                   // 0x00e826e0
extern "C" void  FUN_00e4f680(int val);                     // 0x00e4f680
extern "C" void  FUN_00e4ec30(int base, int idx);           // 0x00e4ec30
extern "C" void* FUN_00e4cc40(int id, void* out);           // 0x00e4cc40  (thunk_FUN_00e823a0)
extern "C" void  FUN_00e4fc20(int idx, int handle);         // 0x00e4fc20
extern "C" void  FUN_00e63480(void* effect, int a, void* desc);  // 0x00e63480  sPartIntersectTarget
extern "C" void  FUN_00e65410(int id, int flag);            // 0x00e65410
extern "C" void* FUN_0067ddd0();                            // 0x0067ddd0  SP::EffectsManager
extern "C" void* FUN_0067dd60();                            // 0x0067dd60
extern "C" void  __fastcall FUN_00e619a0(void* p);          // 0x00e619a0  Obj ctor (this = ecx)
extern "C" void* FUN_005f4e10(void* a, void* b, void* c);   // 0x005f4e10  eastl copy_impl::do_copy
extern "C" void  FUN_005f3680(void* a, void* b);            // 0x005f3680  DoDestroyValues (thiscall)
extern "C" void* FUN_006f43e0(void* a, void* b, void* c);   // 0x006f43e0  intrusive copy
extern "C" void  FUN_0070f520(void* a, void* b);            // 0x0070f520  DestroyRange (thiscall)
extern "C" void* FUN_011e0744(void* begin, void* end, int v);// 0x011e0744  eastl vector DoInsertValue
extern "C" void  FUN_009a9600(void* tree, void* node);      // 0x009a9600  DoNukeSubtree (thiscall)
extern "C" void  __cdecl FUN_00f47380(void* p);             // 0x00f47380  operator delete
extern "C" void* memcpy(void* dst, const void* src, unsigned n);
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
#define I(p,o) (*(int*)((char*)(p) + (o)))
#define B(p,o) (*(u8*)((char*)(p) + (o)))
#define VT(p)  (*(void***)(p))
struct Vec3_s00e6_5ad0 { float x, y, z; };
extern char*  gspCellGame_s00e6_5ad0;        // 0x016b3c04
extern Vec3_s00e6_5ad0   gCellWorldCenter;   // 0x016b3c28
struct Pool_s00e6_5ad0 {
    void* GetSafe(int h);      // 0x00b721d0, thiscall ret 4
    void* Get(int h);          // 0x00b72210, thiscall ret 4
    int   Alloc();             // 0x00b72160, thiscall ret
    void  Free(int h);         // 0x00b72260, thiscall ret 4
};
static Pool_s00e6_5ad0* cells() { return (Pool_s00e6_5ad0*)(gspCellGame_s00e6_5ad0 + 0x1c); }
typedef void (__thiscall *PFN_v)(void*);
typedef void (__thiscall *PFN_i)(void*, int);
typedef void (__thiscall *PFN_vp)(void*, void*);
typedef void (__stdcall  *PFN_sb)(void*, unsigned);
struct cCellGfxStub { void pushObj(void* p); };            // 0x00e653a0, thiscall (this = gspCellGfx)
struct RefVecOwner  { void push(void* p); };               // 0x00e65970, thiscall (this = gspCellGfx)
struct Obj74        { char d[0x74]; void ctor(const void* src); }; // 0x00e61750
struct ObjVec74 {
    void* b; void* e; void* c;
    void insertGrow(void* pos, void* val);                 // 0x00e65200
};
struct XForm { char d[0x38]; void assign(const void* src); }; // 0x00537dc0
struct RbTree {
    void find(void** out, const unsigned* key);            // 0x00e5c780
    void* operatorIndex(const int* key);                   // 0x00badea0 eastl::map<K,int>::operator[]
};
extern "C" void* FUN_00e4cce0_s00e6_5ad0(int idx);                     // 0x00e4cce0  (layer-catalog entry)
extern "C" void  __fastcall FUN_00743b50_s00e6_5ad0(void* ref);        // 0x00743b50
extern "C" void  __fastcall FUN_00e82130_s00e6_5ad0(void* ref);        // 0x00e82130
extern "C" void* CreateEffectSafe_s00e6_5ad0(void* world, u32 id, int flags, void* out); // 0x00628450
extern "C" u32   FNV1_String8(const char* s, u32 seed, int one); // 0x00932e80
void FUN_00e66280(int a, int b);
void FUN_00e663b0(int map, int key);
void FUN_00e665c0(int map, int id);
struct EffEntry { int a, b, type; int pad; };
struct EffDesc { u16 a, b; Vec3_s00e6_5ad0 pos; float scale; float m[9]; };
// ---- items of slice s00e65ad0 end

// ---- items of slice s00e66980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  g_15a7c4c[4];        // 0x015a7c4c  (0,0,0,1)
extern float  g_minus1;            // 0x013eb1bc  -1.0f
extern float  g_half;              // 0x01471064  0.5f
extern float  g_0p1_1488874;       // 0x01488874  0.1f
extern float  g_neg0p1_13eb964;    // 0x013eb964  -0.1f
struct cSPBoundingBox_s0137_d820;
extern struct cSPBoundingBox_s0137_d820 gCellGameExtents;    // 0x016b3c88  minX,minY,minZ,maxX,maxY,maxZ
extern char   g_16b42b8[];         // 0x016b42b8  (ctor target in sShutdownGfx)
extern "C" void  FUN_007c3ba0(void* self);                        // 0x007c3ba0 (ecx ctor)
extern "C" void* FUN_0067dd90();                                  // 0x0067dd90 LightingManager
extern "C" void* FUN_0067dd80();                                  // 0x0067dd80 ModelManager
extern "C" void  FUN_00e82750(void* p);                           // 0x00e82750
extern "C" void  FUN_007b1950(void* self);                        // 0x007b1950 (ecx)
extern "C" void  FUN_00e65180(void* first, void* last);           // 0x00e65180 vector erase
extern "C" void* __cdecl FUN_00e65840(void* self, void* key);     // KeyMap4::operator[]
extern "C" void  FUN_00e66f30(int a, int b, void* pos, float p4, float p5, float p6,
                              float p7, float p8);
extern "C" void  FUN_00e61b90(int flag, int zero, void* pos, int* key); // custom ABI (eax/edx)
extern "C" void  FUN_00e84150(int a, int b, void* out);           // 0x00e84150
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))
struct Vec3_s00e6_6980 { float x, y, z; };
extern char*  gspCellGame_s00e6_6980;         // 0x016b3c04
extern Vec3_s00e6_6980   gCellWorldCenter_s00e6_6980;    // 0x016b3c28
struct Pool_s00e6_6980 {
    int   Begin();            // 0x00e31100
    void* Next(int* it);      // 0x00b72230, ret 4
    void* GetSafe(int h);     // 0x00b721d0, ret 4
    void* Get(int h);         // 0x00b72210, ret 4
    int   Alloc();            // 0x00b72160, ret
    void  Free(int h);        // 0x00b72260, ret 4
    void  Reset();            // 0x00b720e0
};
struct KPair { int key; int val; };
struct KeyMap {                        // at gspCellGame + 0xe0
    KPair* mpBegin;
    KPair* mpEnd;
    char   pad08[0x4018 - 8];
    u8     mbFlag;                     // +0x4018
    int    erase(KPair* key);          // 0x00e64fc0
    KPair* insertAt(KPair* pos, KPair* val);
    int*   operatorIndex(KPair* key);  // 0x00e65730
};
struct SoundMap {                      // at gspCellGfx + 0x184
    KPair* mpBegin;
    KPair* mpEnd;
    char   pad08[0x16018 - 8];
    u8     mbFlag;                     // +0x16018
    int*   operatorIndex(KPair* key);  // 0x00e65790
    KPair* insertAt(KPair* pos, KPair* val);
};
extern "C" void* __cdecl FUN_00b41ea0(void* first, void* last, void* key, u8 flag); // lower_bound
extern "C" void* __cdecl FUN_00e61830(void* first, void* last, void* key, u8 flag); // lower_bound
extern "C" int   FUN_00e66280_s00e6_6980(u32 id, int flag);                  // 0x00e66280
extern "C" int   FNV1_String8_s00e6_6980(const char* s, u32 seed, int one);  // 0x00932e80
extern "C" void  __fastcall FUN_00743b50_s00e6_6980(void* self);             // 0x00743b50 (ecx init)
extern "C" void  __fastcall FUN_00e82130_s00e6_6980(void* self);             // 0x00e82130 (ecx release)
extern "C" void* CreateEffectSafe_s00e6_6980(void* world, u32 id, int flags, void* out); // 0x00628450
extern "C" void  FUN_00e65480(u32 a, u32 b);                      // 0x00e65480 map erase pair
void FUN_00e671c0(void* cell);                                    // SP::sBomb_Start
static inline void VCall_v(void* p, int slot) { ((void(__thiscall*)(void*))VT(p)[slot / 4])(p); }
static inline void VCall_i(void* p, int slot, int a) { ((PFN_i)VT(p)[slot / 4])(p, a); }
static inline void ReleaseSlot(char* base, int off) {
    void* p = *(void**)(base + off);
    if (p) { *(void**)(base + off) = 0; VCall_v(p, 4); }
}
struct Pair16 { u16 lo, hi; };
static inline int MakeKey(int a, int b) {
    Pair16 k;
    if (a < b) { k.hi = (u16)a; k.lo = (u16)b; }
    else       { k.hi = (u16)b; k.lo = (u16)a; }
    return *(int*)&k;
}
struct Mat3 { float m[9]; void Assign(const void* src); };  // 0x0041cb40
struct EffDesc_s00e6_6980 {
    u16   a;        // +0x00
    u16   b;        // +0x02
    Vec3_s00e6_6980  pos;      // +0x04
    float scale;    // +0x10
    Mat3  rot;      // +0x14
};
// ---- items of slice s00e66980 end

// ---- items of slice s00e67890 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double sqrt(double);
extern "C" double sin(double);
extern "C" double cos(double);
extern const float kf14851ec;   // 1.5258789e-05
extern const float kf13ec4b8;   // 1e-08
extern const float kf1471064;   // 0.5
extern const float kf15a7c24;   // pi
extern const float kf16b3dd0;   // 2*pi
extern const float kf15a7c40, kf15a7c44, kf15a7c48;   // up vector
struct MapTree   { void* Find(void* out, int* key); }; // 0x00e39fb0
struct RbTree_s00e6_7890    { int   Insert(int* key); };          // 0x00e67940
int   FUN_00e573e0(int a, int b);
int   FUN_00e50540(int a);
int   FUN_00e66840(int a, int b);
struct CellKey { int a, b, c; };
int   FUN_00e679e0(CellKey key);
void  FUN_00e83e30(int a, int b, void* c);
void  FUN_00e52060(int a, int b);
void  FUN_00e4fe90(int a, int b);
void  FUN_00e5eb20(void* out, int cell);
char* FUN_00e52910(int a);
void  FUN_00e62a20(void* p);
void  FUN_00e658a0(void* a, void* b, void* c, unsigned d);
float* SP_QuaternionFromFacingAndUp(float* out, float* dir, const void* up); // 0x0069b600
void   SP_normalized_safe(float* out, float* in);      // 0x00449c20
float* FUN_0046d660(float* out, float* a, float* b);   // 0x0046d660
float* FUN_007dcb00(float* out, float* in);            // 0x007dcb00
struct cSPTransform_s00e6_7890 {
  unsigned short flags;      // 0x00
  unsigned short modCount;   // 0x02
  float tx, ty, tz;          // 0x04 / 0x08 / 0x0c
  float scale;               // 0x10
  float rot[9];              // 0x14 .. 0x37
  void Assign(const cSPTransform_s00e6_7890& rhs);   // 0x00537dc0
};
// ---- items of slice s00e67890 end

// ---- items of slice s00e695f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float g_14007f4;                 // 15.0f
extern "C" float g_16b3c28_s00e6_95f0, g_16b3c2c, g_16b3c30;
extern "C" int   g_16b4494, g_16b4490, g_16b448c, g_16b4488;
extern "C" void  __cdecl FUN_00e82be0(int, int);
extern "C" void* __cdecl FUN_0067cac0();
extern "C" void  __cdecl FUN_00e41cb40(void*, const void*);                  // Matrix3 assign
extern "C" void  __cdecl FUN_00e5f4d0(int, float, float, void*);
extern "C" void  __cdecl FUN_00e62380(int, int, int, void*, float);
extern "C" void  __cdecl FUN_00409930(void*);
extern "C" void* __cdecl FUN_00b721d0(int);
extern "C" uint8_t g_16b3dac_s00e6_95f0;
struct ObjRef { int a, b, c; };
extern "C" void* __cdecl FUN_00e52910_s00e6_95f0(int);
extern "C" void* __cdecl FUN_00e679e0_s00e6_95f0(ObjRef);
struct cSPTransform_s00e6_95f0 {
    uint16_t mFlags; uint16_t mModCount;
    float mTranslation[3]; float mScale; float mRotation[9];
    cSPTransform_s00e6_95f0& operator=(const cSPTransform_s00e6_95f0&);
};
struct UIHints { void Update(); };
// ---- items of slice s00e695f0 end

// ---- items of slice s00e6b370 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gT_016b3c28[3];          // 0x016b3c28 (identity transform translation)
extern float gT_016b3c54[3];          // 0x016b3c54
extern float gR_016b3c60[9];          // 0x016b3c60 (identity 3x3 rotation)
extern float gMatrix_016b3dac;        // 0x016b3dac (matrix source)
extern float gOne;                    // 0x01485720 = 1.0f
extern float gMinPos;                 // 0x014851ec = 1.5258789e-05f
extern float gTwo;                    // 0x01470f1c = 2.0f
extern float gEpsilon;                // 0x013ec4b8 = 1e-08f
extern float gFrac05;                 // 0x013ec478 = 0.05f
extern float gFar;                    // 0x013f0620 = 10000.0f
#pragma intrinsic(sqrt)
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
struct Vector3 { float x, y, z; };
#define B_s00e6_b370(p,o) (*(uint8*)((char*)(p) + (o)))
extern char* gspCellGame_s00e6_b370;             // 0x016b3c04
struct Registry {                     // cSPObjectPool at gspCellGame + 0x1c (thiscall)
    void* GetSafe(int id);            // 0x00b721d0
    void* Get(int id);               // 0x00b72210
};
struct cCellGameFields {              // typed view used so the compiler forms &mCells as an lvalue
    char pad0[0x1c];
    Registry mCells;                  // +0x1c
    char pad1[0x411c - 0x1c - 1];
    int mAvatarCellIndex;             // +0x411c
    char pad2[0x5190 - 0x4120];
    char* mpSerializableData;         // +0x5190
    char pad3[0x51d4 - 0x5198];
    int field_51d4;                   // +0x51d4
};
struct RandomLCG {                    // EA::Random::RandomLinearCongruential at 0x01601760
    uint32 RandomUint32Uniform(uint32 range);   // 0x00a68fb0
};
extern RandomLCG gRandomLCG;          // 0x01601760
struct ResourceKey { uint32 instanceID, typeID, groupID; };
int* GetCellResource(ResourceKey key);                       // 0x00e679e0
int  GetScaleDifferenceWithPlayer(void* cell);               // 0x00e57340
int  FUN_00e573e0(void* cell, void* other);                  // 0x00e573e0
float* FUN_00e5fc90(void* out, void* cell, int a, int b);    // 0x00e5fc90
void* sChooseRandomLookatTarget(void* cell, int a2, int a3, int* out);
void FUN_00e68000(void* cell, int a, void* out);
void Matrix33_ctor(void* self, const void* src);               // 0x0041cb40
bool CreateEffectSafe(void* world, uint32 id, int flags, int** ppEffect);
struct Handle { int mValue; void ctor(); void dtor(); };
struct cIVisualEffect {
    virtual int  AddRef();                 // +0x00
    virtual int  Release();                // +0x04
    virtual bool Start(int flags);         // +0x08
    virtual bool Stop(int flags);          // +0x0c
    virtual bool v10();                    // +0x10
    virtual void v14();                    // +0x14
    virtual void SetTransform(const void*); // +0x18
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
    virtual void v44(int a, const void* data, int count);   // +0x44
};
struct cSPTransform_s00e6_b370 {
    uint16 mFlags;
    uint16 mModCount;
    float  mTranslation[3];
    float  mScale;
    float  mRotation[9];
};
struct IntVec {
    void* begin;
    void* end;
    void* cap;
    void DoInsertValue(void* where, void** value);   // 0x004558a0
};
// ---- items of slice s00e6b370 end

// ---- items of slice s00e6cbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gCellSpawnTableTag[];   // 0x016ae800
struct Vector3_s00e6_cbd0 {
    float x, y, z;
    Vector3_s00e6_cbd0() {}
    Vector3_s00e6_cbd0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct Matrix3 { float m[9]; };
inline Vector3_s00e6_cbd0 operator*(const Vector3_s00e6_cbd0& v, const Matrix3& mm)
{
    return Vector3_s00e6_cbd0(v.x * mm.m[0] + v.y * mm.m[3] + v.z * mm.m[6],
                   v.x * mm.m[1] + v.y * mm.m[4] + v.z * mm.m[7],
                   v.x * mm.m[2] + v.y * mm.m[5] + v.z * mm.m[8]);
}
struct CellSpawn {
    int f0;          // 0x00
    int f1;          // 0x04
    float weight;    // 0x08
    int flag;        // 0x0c
    int type;        // 0x10
    char outA;       // 0x14
    char pad15[3];
    int f6;          // 0x18
    int f7;          // 0x1c
    char outB;       // 0x20
    char pad21[3];
};
extern CellSpawn gCellSpawns[];   // 0x01483f70
struct CellInfo {
    char pad0[0x1214];
    int mField1214;   // 0x1214
    char pad1218[0x1238 - 0x1218];
    Vector3_s00e6_cbd0 mVec1238; // 0x1238
    float mScale1244; // 0x1244
    char pad1248[0x1284 - 0x1248];
    int mField1284;   // 0x1284
    int mField1288;   // 0x1288
};
CellInfo* FindCellInfo(CellKey key);   // 0x00e679e0
struct EffectObj {
    void FUN_00e4f100(int id, float v, int a, int b);   // 0x00e4f100
    float FUN_00e4f040(int r);                          // 0x00e4f040
    void FUN_00e4f330(int a, float b, float c, float d, int e);  // 0x00e4f330
};
struct ObjectPool {
    void* Get(int handle) const;         // 0x00b72210
    void* GetChecked(int handle) const;  // 0x00b721d0
    int   Alloc();                       // 0x00b72160
};
struct cCell {
    int mHandle;         // 0x00
    char pad04[0x48 - 0x4];
    short mFlags;        // 0x48
    char pad4a[0x4c - 0x4a];
    Vector3_s00e6_cbd0 mPosition;   // 0x4c
    float mRadius;       // 0x58
    Matrix3 mOrient;     // 0x5c
    char pad80[0x90 - 0x80];
    Vector3_s00e6_cbd0 mVelocity;   // 0x90
    char pad9c[0xfc - 0x9c];
    CellKey mKey;        // 0xfc
    int mType;           // 0x108
    char pad10c[0x18c - 0x10c];
    int mState0;         // 0x18c
    char pad190[0x1ac - 0x190];
    char mFlag1ac;       // 0x1ac
    char pad1ad[0x1b0 - 0x1ad];
    int mState1;         // 0x1b0
    int mState2;         // 0x1b4
    float mTimer;        // 0x1b8
    char pad1bc[0x248 - 0x1bc];
    int mPoolHandle;     // 0x248
    int mAnimIdx;        // 0x24c
    int mAnimCount;      // 0x250
    int mAnimData;       // 0x254
    char pad258[0x35c - 0x258];
    int mEffectGroup;    // 0x35c
    int mEffect;         // 0x360
    int mObstacle;       // 0x364
    char pad368[0x390 - 0x368];
    char mFlag390;       // 0x390
    char mFlag391;       // 0x391
};
struct cLevelInfo {
    char pad0[0x1c];
    int mField1c;   // 0x1c
    char pad20[0x74 - 0x20];
    int mField74;   // 0x74
};
struct cCellGame_s00e6_cbd0 {
    char pad0[0x1c];
    ObjectPool mCells;   // 0x1c
    char pad20[0x40fc - 0x20];
    int mSel40fc;        // 0x40fc
    int mSel4100;        // 0x4100
    int mObstacleGrid;   // 0x4104
    char pad4108[0x411c - 0x4108];
    int mHandle411c;     // 0x411c
    char pad4120;
    char mByte4121;      // 0x4121
    char pad4122[0x5190 - 0x4122];
    cLevelInfo* mpLevelInfo;  // 0x5190
};
struct cCellGfx_s00e6_cbd0 {
    char pad0[0x168];
    ObjectPool mEffects;   // 0x168
    char pad16c[0x16254 - 0x16c];
    int mField16254;       // 0x16254
};
extern cCellGame_s00e6_cbd0* gspCellGame_s00e6_cbd0;   // 0x016b3c04
extern cCellGfx_s00e6_cbd0* gspCellGfx_s00e6_cbd0;     // 0x016b3c08
int  FUN_00e516c0(cCell* c);            // 0x00e516c0
float FUN_00e563e0(cCell* c);           // 0x00e563e0
bool FUN_00e5c460(int handle, int v);   // 0x00e5c460
bool FUN_00e5c410(int handle, int v);   // 0x00e5c410
void FUN_00743b50(void* iter);          // 0x00743b50
void FUN_00e82130(void* iter);          // 0x00e82130
void* FUN_00e52910_s00e6_cbd0(int x);              // 0x00e52910
void FUN_00e51930();                    // 0x00e51930
struct IContext;
struct IDelegate {
    IContext* FUN_007ec160();           // 0x007ec160 (thiscall, no args)
};
struct IContext {
    void FUN_007eb820(int v);           // 0x007eb820 (thiscall, one arg)
    char pad[0xc];
    int* mOut;                          // 0x0c
};
IDelegate* __stdcall FUN_0067de90_s00e6_cbd0(int, int);   // 0x0067de90
void FUN_00e5cb60(void* a, void* out, void* b, void* c, int handle, int k, int z);  // 0x00e5cb60
void FUN_00e5ce90(void* a, int b, bool c, int d, int e, CellKey key);                 // 0x00e5ce90
void FUN_00e83e30(void* a, void* b, CellKey* key);  // 0x00e83e30
void FUN_00e52060(void* a, int b);                  // 0x00e52060 (a = the work block)
class RandomLCG_s00e6_cbd0 {
public:
    double RandomDoubleUniform();                   // 0x009360d0
};
extern RandomLCG_s00e6_cbd0 gMathRandom;                       // 0x01601760
void MoveObstacle(int grid, int obstacle, const void* vMin, const void* vMax);   // 0x00bbc2f0
struct CellInfoEntry {
    unsigned mType;                 // 0x00
    char pad04[0x44];
};
struct CellInfoList {
    int mCount;                     // 0x00
    char pad04[4];
    CellInfoEntry mEntries[1];      // 0x08 (stride 0x48)
};
struct EaterInfo {
    char pad00[0x10];
    unsigned mState;                // 0x10
};
static inline CellInfoList* CellListFor(int handle)
{
    cCell* cell = (cCell*)gspCellGame_s00e6_cbd0->mCells.Get(handle);
    if (cell->mKey.a == 0)
        return 0;
    return (CellInfoList*)FindCellInfo(cell->mKey);
}
static inline bool CellListHasValue(int handle, int value)
{
    CellInfoList* list = CellListFor(handle);
    if (list == 0)
        return false;
    for (int j = 0; j < list->mCount; j++) {
        if ((int)list->mEntries[j].mType == value)
            return true;
    }
    return false;
}
static inline unsigned EaterState(int a2)
{
    return ((EaterInfo*)FUN_00e52910_s00e6_cbd0(a2))->mState;
}
struct CellScratch {
    int mCount00;                              // 0x0000 (written by FUN_00e83e30)
    struct { char mBytes[0x1280]; } mDesc;     // 0x0004 (FUN_00e83e30's descriptor output)
    int mOut1284;                              // 0x1284
    int mOut1288;                              // 0x1288
    int mOut128c;                              // 0x128c
};
int FUN_00e6cbd0(int handle, int a2, unsigned a3, char* outA, char* outB);
// ---- items of slice s00e6cbd0 end

// ---- items of slice s00e6db70 begin (TODO(rewrite): local stubs, replace by canonical classes)
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float x_, float y_) : x(x_), y(y_) {}
};
struct Vector3_s00e6_db70 {
    float x, y, z;
    Vector3_s00e6_db70() {}
    Vector3_s00e6_db70(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s00e6_db70 operator+(const Vector3_s00e6_db70& v) const { return Vector3_s00e6_db70(x + v.x, y + v.y, z + v.z); }
    Vector3_s00e6_db70 operator-(const Vector3_s00e6_db70& v) const { return Vector3_s00e6_db70(x - v.x, y - v.y, z - v.z); }
    Vector3_s00e6_db70 operator*(float f) const { return Vector3_s00e6_db70(x * f, y * f, z * f); }
    Vector3_s00e6_db70& operator-=(const Vector3_s00e6_db70& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3_s00e6_db70& operator*=(float f) { x *= f; y *= f; z *= f; return *this; }
};
struct Matrix3_s00e6_db70 {
    Vector3_s00e6_db70 m[3];
};
inline Vector3_s00e6_db70 operator*(const Vector3_s00e6_db70& v, const Matrix3_s00e6_db70& m)
{
    return Vector3_s00e6_db70(v.x * m.m[0].x + v.y * m.m[1].x + v.z * m.m[2].x,
                   v.x * m.m[0].y + v.y * m.m[1].y + v.z * m.m[2].y,
                   v.x * m.m[0].z + v.y * m.m[1].z + v.z * m.m[2].z);
}
struct TransformMsg {
    short mType;        // +0x00
    short mFlags;       // +0x02
    Vector3_s00e6_db70 mPosition;  // +0x04
    float mScale;       // +0x10
    Matrix3_s00e6_db70 mOrient;    // +0x14
};
struct Modifier {
    void AccumulateScaled(const TransformMsg* pMsg);   // 0x0040cd80
};
struct IShape {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void Transform(const TransformMsg* pMsg);   // +0x18
};
struct IntPair {
    int first;
    int second;
    IntPair(int a, int b) : first(a), second(b) {}
};
template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}
template <class ForwardIterator>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, int value)
{
    int d = (int)(last - first);
    while (d > 0) {
        ForwardIterator i = first;
        int d2 = d >> 1;
        i += d2;
        if (i->first < value) {
            first = ++i;
            d -= d2 + 1;
        } else
            d = d2;
    }
    return first;
}
struct IntMap {
    IntPair* mpBegin;
    IntPair* mpEnd;
    IntPair* mpCapacity;

    IntPair* begin() { return mpBegin; }
    IntPair* end() { return mpEnd; }
    void DoInsertValue(IntPair* position, const IntPair& value);   // 0x00e63d60
    IntPair* vector_insert(IntPair* position, const IntPair& value) {
        const int n = (int)(position - mpBegin);
        if ((position == mpEnd) && (mpEnd != mpCapacity)) {
            IntPair* p = mpEnd++;
            if (p)
                *p = value;
        } else
            DoInsertValue(position, value);
        return mpBegin + n;
    }
    IntPair* erase(IntPair* first, IntPair* last) {
        copy(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(begin(), end()); }
    IntPair* insert(IntPair* position, const IntPair& value) {
        IntPair* it;
        if ((position != end()) && (value.first < position->first))
            it = lower_bound(begin(), position, value.first);
        else
            it = lower_bound(position, end(), value.first);
        if ((it == end()) || (value.first < it->first))
            it = vector_insert(it, value);
        return it;
    }
    int& operator[](int key) {
        IntPair* itLB = lower_bound(begin(), end(), key);
        if ((itLB == end()) || (key < itLB->first))
            itLB = insert(itLB, IntPair(key, 0));
        return itLB->second;
    }
};
struct ObjectPool_s00e6_db70 {
    int Begin();               // 0x00e31100 (returns 0)
    void* Next(int* pIndex);   // 0x00b72230
};
struct cCell_s00e6_db70 {
    int mHandle;            // +0x000
    uint32_t pad04;
    Vector3_s00e6_db70 mTarget;        // +0x008
    uint32_t pad14[(0x48 - 0x14) / 4];
    short mFlags;           // +0x048
    short mVersion;         // +0x04a
    Vector3_s00e6_db70 mPosition;      // +0x04c
    float mRadius;          // +0x058
    uint32_t pad5c[(0x90 - 0x5c) / 4];
    Vector3_s00e6_db70 mVelocity;      // +0x090
    uint32_t pad9c[(0xb4 - 0x9c) / 4];
    float mSize;            // +0x0b4
    float mMass;            // +0x0b8
    float mInvMass;         // +0x0bc
    Modifier mModifier;     // +0x0c0
    uint32_t padc4[(0x108 - 0xc4) / 4];
    int mType;              // +0x108
    uint32_t pad10c[(0x1c4 - 0x10c) / 4];
    Vector3_s00e6_db70 mGoal;          // +0x1c4
    uint32_t pad1d0[(0x35c - 0x1d0) / 4];
    int mEffectGroup;       // +0x35c
    int mEffect;            // +0x360
    int mObstacle;          // +0x364

    void SetPosition(const Vector3_s00e6_db70& v) {
        mFlags |= 4;
        mPosition = v;
        mVersion++;
    }
    void SetRadius(float r) {
        mVersion++;
        mRadius = r;
    }
};
struct cBackgroundTile {
    int mHandle;            // +0x000
    int mLayer;             // +0x004
    int mLevel;             // +0x008
    int mX;                 // +0x00c
    int mY;                 // +0x010
    uint32_t pad14[(0x300 - 0x14) / 4];
    IShape* mpShape;        // +0x300
};
struct cCellEffectPositions {
    uint32_t pad0;
    Vector3_s00e6_db70 mPositions[0x5dc];          // +0x00004
    uint32_t pad[(0x18e74 - 0x4654) / 4];
    int mActive[0x5dc];                 // +0x18e74
};
struct cCellLevelInfo { uint32_t pad[7]; int mStage; };   // +0x1c
struct cCellGame_s00e6_db70 {
    uint32_t pad0;
    float mWorldScale;                          // +0x0004
    uint32_t pad8[(0x1c - 0x8) / 4];
    ObjectPool_s00e6_db70 mCells;                          // +0x001c
    uint32_t pad20[(0x38 - 0x20) / 4];
    ObjectPool_s00e6_db70 mTiles;                          // +0x0038
    uint32_t pad3c[(0x4104 - 0x3c) / 4];
    int mObstacleGrid;                          // +0x4104
    cCellEffectPositions* mpEffectPositions;    // +0x4108
    uint32_t pad410c[(0x4128 - 0x410c) / 4];
    IntMap mTileMap;                            // +0x4128
    uint32_t pad4134[(0x514c - 0x4134) / 4];
    float mCellSize;                            // +0x514c
    uint32_t pad5150[(0x5190 - 0x5150) / 4];
    cCellLevelInfo* mpLevelInfo;                // +0x5190
};
struct cCellModifierEntry { uint32_t pad[0x74 / 4]; };
struct cCellGfx {
    uint32_t pad0[0x4c / 4];
    float mScale;                               // +0x4c
    uint32_t pad50[(0x161dc - 0x50) / 4];
    cCellModifierEntry* mModifiersBegin;        // +0x161dc
    cCellModifierEntry* mModifiersEnd;          // +0x161e0
};
struct cCellCameraState {
    uint32_t pad[0x48 / 4];
    Vector3_s00e6_db70 mPosition;     // +0x48
    Vector3_s00e6_db70 mTarget;       // +0x54
    Vector3_s00e6_db70 mOffset;       // +0x60
};
struct cCellStageInfo {
    int mLevel;            // +0x00
    int mStart;            // +0x04
    int pad[5];
};
extern cCellGame_s00e6_db70* gspCellGame_s00e6_db70;              // 0x016b3c04
extern cCellGfx* gspCellGfx_s00e6_db70;                // 0x016b3c08
extern cCellCameraState* gspCellCamera;     // 0x016b3c0c
extern Vector3_s00e6_db70 gCellWorldCenter_s00e6_db70;            // 0x016b3c28
extern Matrix3_s00e6_db70 gCellWorldOrient;            // 0x016b3c60
extern Matrix3_s00e6_db70 gCellTileOrient;             // 0x016b3dac
extern const float kLevelSize_s00e6_db70[];            // 0x01483bd0
extern const cCellStageInfo kCellStages[];  // 0x01483c14
extern const cCellStageInfo kCellEditorStage;   // 0x01483e60
void SnapToGrid(Vector3_s00e6_db70& v, float grid);   // 0x00e4f920 (in place: floor(v / grid) * grid)
void CellRescaleEffects();                                          // 0x00e86b60
float GetCellScaleFactor(int type);                                 // 0x00e4f9d0
void CellUpdateSpeed(cCell_s00e6_db70* pCell);                                 // 0x00e5a1a0
void GetCellBounds(cCell_s00e6_db70* pCell, Vector3_s00e6_db70* pCenter, float* pRadius); // 0x00e6d790
int CellMoveEffect(int group, const Vector3_s00e6_db70* pCenter, float radius, int handle);   // 0x00e868f0
void MoveObstacle(int grid, int obstacle, const Vector2* pMin, const Vector2* pMax); // 0x00bbc2f0 (thunk to 0x00bbbe60)
inline const cCellStageInfo* GetCellStage(int stage)
{
    if (stage == 1000)
        return &kCellEditorStage;
    int i = 0;
    while (stage >= kCellStages[i + 1].mStart)
        i++;
    return &kCellStages[i];
}
inline float GetLevelScale(int d)
{
    if (d < -1)
        return 1.0f;
    if (d >= 5)
        return 0.03125f;
    switch (d) {
    case -1: return 1.0f;
    case 1: return 0.25f;
    case 2: return 0.125f;
    case 3: return 0.0625f;
    case 4: return 0.03125f;
    default: return 0.5f;
    }
}
// ---- items of slice s00e6db70 end

// ---- items of slice s00e6e8c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kQuarterPi;                      // 0x015a7c1c
extern float kPi;                             // 0x015a7c24
struct Vec3_s00e6_e8c0 { float x, y, z; };
struct Cell_s00e6_e8c0 {
    int   mIndex;                 // +0x00 index in gspCellGame->mCells
    char  mDone;                  // +0x04 set once the cell has (almost) reached its target
    char  pad05[3];
    Vec3_s00e6_e8c0  mPos;                   // +0x08
    char  pad14[0x4c - 0x14];
    Vec3_s00e6_e8c0  mTarget;                // +0x4c (the position it is moving toward)
    char  pad58[0x90 - 0x58];
    Vec3_s00e6_e8c0  mHeading;               // +0x90 current v
    char  pad9c[0xb8 - 0x9c];
    float mVelocityScale;         // +0xb8
    char  padbc[0x17e - 0xbc];
    char  mSuppressed;            // +0x17e
    char  pad17f[0x18c - 0x17f];
    int   mState;                 // +0x18c motion state
    char  pad190[4];
    float mTurnDistance;          // +0x194 (flags & 1 / & 8)
    float mTurnRateB;             // +0x198 (flags & 4)
    float mTurnRateC;             // +0x19c (flags & 2)
    char  pad1a0[0x1c4 - 0x1a0];
    Vec3_s00e6_e8c0  mAccum;                 // +0x1c4 accumulated displacement
    char  pad1d0[0x248 - 0x1d0];
    int   mHasPath;               // +0x248
    char  pad24c[0x358 - 0x24c];
    int   mLevel;                 // +0x358
};
struct LevelInfo { char pad[0x1c]; int mLevel; };
struct cGameStub {                // gspCellGame
    char pad0[0x411c];
    int mAvatarCellIndex;         // +0x411c
    char pad4120[0x5190 - 0x4120];
    LevelInfo* mpLevelInfo;       // +0x5190
};
extern cGameStub* gspCellGame_s00e6_e8c0;                // 0x016b3c04
struct cHandleRef {
    int mp;
    cHandleRef();
    ~cHandleRef();
};
struct CellScales {               // 0x00e4ce40 result
    char pad0[0x48];
    float f48;
    float f4c;
    float f50;
    float f54;
};
extern const float kLevelSize_s00e6_e8c0[];              // 0x01483bd0
extern Vec3_s00e6_e8c0 kFallbackDir;                     // 0x016b3c28
void  CellDelta(Vec3_s00e6_e8c0* out, Cell_s00e6_e8c0* self);                                    // 0x00e56560
float CellSpeedFactor(Cell_s00e6_e8c0* self, unsigned flags, float dist);             // 0x00e56b50 (XMM0 in the original)
float CellLevelRatio(Cell_s00e6_e8c0* self);                                          // 0x00e56450
float CellTurnLimit(Cell_s00e6_e8c0* self);                                           // 0x00e56510
float CellTurnAngle(Cell_s00e6_e8c0* self);                                           // 0x00e5ef40
void  CellStartTurn(Cell_s00e6_e8c0* self);                                           // 0x00e6ee10
void  CellApplyTurn(Cell_s00e6_e8c0* self, float rate, float angle);                  // 0x00e61e20
bool  CellCanTurn(Cell_s00e6_e8c0* self, float angle);                                // 0x00e56ae0
void  CellSteerA(const Vec3_s00e6_e8c0* pos2, Vec3_s00e6_e8c0* v, const Vec3_s00e6_e8c0* pos, float a2, float a1, Vec3_s00e6_e8c0* out);   // 0x00e55f60
const Vec3_s00e6_e8c0* CellFacing(Vec3_s00e6_e8c0* out, Cell_s00e6_e8c0* self);                             // 0x00e5eb20
float CellSteerRateB(Cell_s00e6_e8c0* self);                                          // 0x00e56200
float CellSteerRateC(Cell_s00e6_e8c0* self);                                          // 0x00e56300
bool  CellSteerB(const Vec3_s00e6_e8c0* facing, const Vec3_s00e6_e8c0* pos2, Vec3_s00e6_e8c0* v, const Vec3_s00e6_e8c0* pos,
                 float a2, float s, float a3, int flag, float a1, Vec3_s00e6_e8c0* out);   // 0x00e558c0
bool  CellSteerC(const Vec3_s00e6_e8c0* facing, const Vec3_s00e6_e8c0* pos2, Vec3_s00e6_e8c0* v, const Vec3_s00e6_e8c0* pos,
                 float a2, float s, float a3, int flag, float a1, Vec3_s00e6_e8c0* out);   // 0x00e55c40
void  CellMove(Cell_s00e6_e8c0* self, const Vec3_s00e6_e8c0* v);                                 // 0x00e560d0
CellScales* GetCellScales(cHandleRef* tmp);                                // 0x00e4ce40
float CellScaleById(uint32 id, float ratio);                               // 0x00e837c0
int   __fastcall SP_sGetSourceLevel(void* unused, int level);              // 0x00e4ee60 (level in EDX)
const Vec3_s00e6_e8c0* NormalizedSafe(Vec3_s00e6_e8c0* out, const Vec3_s00e6_e8c0* in);                     // 0x00449c20
float Dot3(const Vec3_s00e6_e8c0* a, const Vec3_s00e6_e8c0* b);                                  // 0x00455cc0
static __forceinline Vec3_s00e6_e8c0 Scaled(const Vec3_s00e6_e8c0& v, float s) { Vec3_s00e6_e8c0 r = { v.x * s, v.y * s, v.z * s }; return r; }
// ---- items of slice s00e6e8c0 end

// ---- items of slice s00e71520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char*  gCellGame;          // 0x016b3c04
extern char*  gCellUI;            // 0x016b3c0c
extern float  gFwd_16b3c28;       // 0x016b3c28  camera forward
extern float  gFwd_16b3c2c;       // 0x016b3c2c
extern float  gFwd_16b3c30;       // 0x016b3c30
extern float  gBasis_15a7c4c;     // 0x015a7c4c  orthogonal basis
extern float  gBasis_15a7c50;
extern float  gBasis_15a7c54;
extern float  gBasis_15a7c58;
extern float  gk_1440f84;         // 0x01440f84  1/6
extern float  gk_1471064;         // 0x01471064  0.5f
extern float  gk_13f9428;         // 0x013f9428  0.001f
extern "C" float  __cdecl FUN_00e69480(void* cell, int handle, int flag);  // 0x00e69480
extern "C" int    __cdecl FUN_00e693f0(void* cell, void* a, void* b, float f, int* out); // 0x00e693f0
extern "C" void   __cdecl FUN_00e52a00(void);                             // 0x00e52a00 frame tick
extern "C" int    __cdecl FUN_00e679e0(int a, int b, int c);               // 0x00e679e0
extern "C" void*  __cdecl FUN_00e62200(int id, float f);                   // 0x00e62200
extern "C" void   __cdecl FUN_00e576f0(int handle);                        // 0x00e576f0 apply
extern "C" void   __cdecl FUN_00e56f80(void* a, float* v);                 // 0x00e56f80 face
extern "C" void   __cdecl FUN_00e6eec0(int a, int b, float c, float d, float e); // 0x00e6eec0 StepCell
extern "C" char   __cdecl FUN_00e57460(void* a, void* b);                  // 0x00e57460 same group
extern "C" void   __cdecl FUN_00e5c8e0(void);                              // 0x00e5c8e0 spawn
struct cObjectPool {
    void* GetSafe(int id);   // 0x00b721d0
    void* Get(int id);       // 0x00b72210
    int   Alloc();           // 0x00b72160
};
struct cLayerCtx {
    void Begin();            // 0x00743b50
    void End();              // 0x00e82130
};
struct cCellCmd {
    char  pad00[4];
    int   x04;               // +0x04
    char  x08;               // +0x08
    char  pad09[0x13];
    float t1c;               // +0x1c  duration A
    float t20;               // +0x20  duration B
    int   kind24;            // +0x24  command kind
    int   src28;             // +0x28  source handle
    int   arg2c;             // +0x2c
    int   arg30;             // +0x30
    int   arg34;             // +0x34
    int   arg38;             // +0x38
    int   arg3c;             // +0x3c
    float f40;               // +0x40
    float f44;               // +0x44
    float from48, from4c, from50;   // +0x48  start point
    float to54, to58, to5c;         // +0x54  end point
    float dir60, dir64, dir68, dir6c;// +0x60 direction / basis
    int   flag70;            // +0x70
    char  flag74;            // +0x74
    int   flag78;            // +0x78
};
extern "C" void*  __cdecl FUN_00e52910_s00e7_1520(int handle);                        // 0x00e52910
struct cTriggerMgr_s00e7_1520 { void SetModal(int); };   // 0x00ad7e40
struct cTriggerMgr_s00e7_94f0;
cTriggerMgr_s00e7_94f0* GetTriggerMgr();                 // 0x00b3d4d0
// ---- items of slice s00e71520 end

// ---- items of slice s00e72430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   __cdecl FUN_00e4ff50(int);
extern uint8_t* gspCellState;   // 0x16b3c0c
extern "C" int   g_15a7c4c_s00e7_2430, g_15a7c50, g_15a7c54, g_15a7c58;  // default orientation/scale
extern "C" float g_1486d94;     // 0.125f
extern "C" void  __cdecl FUN_00e59710(int, int, int, float, float, int);
extern "C" float __fastcall FUN_00e4eef0(void* self, int v);          // CellLevel_GetRatio
extern "C" void  __cdecl FUN_00e57170(float);
extern "C" void  __cdecl FUN_00e53580();
extern "C" void  __cdecl FUN_00e53130();
extern "C" void  __cdecl FUN_00e82c10(void*, int, int, int);
extern "C" void  __cdecl FUN_00e528f0(int, float);
extern "C" int   __cdecl SP_sAttach(int, int, int, void*, int);       // 0x00e5f450
struct cCellGame_s00e7_2430;                    // defined after ObjectPool below
extern cCellGame_s00e7_2430* gspCellGame_s00e7_2430;       // 0x16b3c04
extern uint8_t* gspCellGfx_s00e7_2430;     // 0x16b3c08
extern "C" int   g_16b3c28_s00e7_2430, g_16b3c2c_s00e7_2430, g_16b3c30_s00e7_2430;             // world centre
struct ObjectPool_s00e7_2430 {
    void* GetChecked(int handle);   // 0x00b721d0
    void* Get(int handle);          // 0x00b72210
    int   Alloc();                  // 0x00b72160
};
struct cCellGame_s00e7_2430 {
    char pad0[0x1c];
    ObjectPool_s00e7_2430 mCells;                          // 0x1c
    char pad1d[0x54 - 0x1d];
    ObjectPool_s00e7_2430 mEffects;                        // 0x54
    char pad55[0x411c - 0x55];
    int  mHandle411c;                           // 0x411c
    char pad4120[0x5158 - 0x4120];
    int  mState5158;                            // 0x5158
    char pad515c[0x5169 - 0x515c];
    uint8_t mByte5169;                          // 0x5169
    char pad516a[0x5190 - 0x516a];
    void* mpLevelInfo;                          // 0x5190
    int  mHandle5194;                           // 0x5194
};
#define gspCG ((uint8_t*)gspCellGame_s00e7_2430)   // raw byte view
struct ModalObj { void setModal(int); };      // method 0x00ad7e40
struct cSPTransform_s00e7_2430 {
    uint16_t mFlags; uint16_t mModCount;
    float mTranslation[3]; float mScale; float mRotation[9];
    cSPTransform_s00e7_2430& copyFrom(const cSPTransform_s00e7_2430&);   // 0x0040ce80
    cSPTransform_s00e7_2430& invert();                        // 0x0040efa0
    cSPTransform_s00e7_2430& compose(const cSPTransform_s00e7_2430&);    // 0x0040ccb0
};
extern "C" bool  __cdecl FUN_00e57460_s00e7_2430(int, int);
struct EvRec {
    char pad0[4];
    int  f04;              // +0x04
    uint8_t f08;           // +0x08
    char pad09[0x13];
    float f1c, f20;        // +0x1c +0x20
    int f24, f28, f2c;     // +0x24 +0x28 +0x2c
    int f30, f34, f38, f3c;
    float f40, f44;
    int v48, v4c, v50, v54, v58, v5c, v60, v64, v68, f6c;
    int f70;
    uint8_t f74;
    char pad75[3];
    int f78;
};
// ---- items of slice s00e72430 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00e72e70(int* param_1, int param_2);  // 0x00e72e70 (stays in the slice: not this object's)
void FUN_00e72fb0(int* param_1, int param_2);  // 0x00e72fb0 (stays in the slice: not this object's)

// ---- items of slice s00e73f60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
typedef uint64_t uint64;
struct Vector3_s00e7_3f60 {
    float x, y, z;
    Vector3_s00e7_3f60() {}
    Vector3_s00e7_3f60(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s00e7_3f60 operator+(const Vector3_s00e7_3f60& b) const { return Vector3_s00e7_3f60(x + b.x, y + b.y, z + b.z); }
    Vector3_s00e7_3f60 operator*(float f) const { return Vector3_s00e7_3f60(x * f, y * f, z * f); }
};
inline float Clamp(float value, float lo, float hi)
{
    __asm {
        movss xmm0, value
        maxss xmm0, lo
        minss xmm0, hi
        movss value, xmm0
    }
    return value;
}
inline float Saturate(float value, float hi)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, value
        minss xmm0, hi
        movss value, xmm0
    }
    return value;
}
struct ResourceKey_s00e7_3f60 {
    uint32 instanceID;   // +0x0
    uint32 typeID;       // +0x4
    uint32 groupID;      // +0x8
};
struct cIVisualEffect_s00e7_3f60 {                       // EA::Swarm::cIVisualEffect
    virtual int AddRef();                     // +0x00
    virtual int Release();                    // +0x04
    virtual bool Start(int flags);            // +0x08
    virtual bool Stop(int flags);             // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void SetTransform(const void* transform);   // +0x18
};
struct cIEffectsWorld {                       // EA::Swarm::cIEffectsWorld
    virtual int AddRef();                     // +0x00
    virtual int Release();                    // +0x04
    virtual bool CreateVisualEffect(uint64 instanceID, cIVisualEffect_s00e7_3f60** ppEffect);   // +0x08
};
struct VisualEffectPtr {
    cIVisualEffect_s00e7_3f60* mpObject;
    VisualEffectPtr() : mpObject(0) {}
    ~VisualEffectPtr() { if (mpObject) mpObject->Release(); }
    cIVisualEffect_s00e7_3f60** AsPointer() { return &mpObject; }
    cIVisualEffect_s00e7_3f60* operator->() const { return mpObject; }
    operator cIVisualEffect_s00e7_3f60*() const { return mpObject; }
};
struct MessageData {
    float mFloat;
    uint32 mPad;
};
struct IMessageRC_s00e7_3f60 {
    virtual int AddRef();
    virtual int Release();
};
struct MessageRC : IMessageRC_s00e7_3f60 {               // vtable 0x013eb90c
    volatile long mRefCount;                  // +0x4
    MessageRC() { _InterlockedExchange(&mRefCount, 0); }
};
struct MessageBasic5 {                        // non-polymorphic base, laid out after MessageRC
    MessageData mData[5];                     // +0x08
    uint32 mId;                               // +0x30
    uint32 mPad34;
    MessageBasic5() : mId(0) {}
};
struct MessageBasicRC5 : MessageBasic5, MessageRC {   // vtable 0x013eb844
    uint32 mRCFlags;                          // +0x38
    uint32 mPad3c;
    MessageBasicRC5() : mRCFlags(0) {}
    ~MessageBasicRC5();                       // 0x00421cf0 (SlotMessage::Destruct)
    virtual int AddRef();
    virtual int Release();
};
struct IMessageServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void MessageSend(uint32 messageID, void* pMessage, void* pListener);   // +0x14
};
namespace EA {
namespace Messaging {
 IMessageServer* GetServer();   // 0x00883860
}
}
struct cUIState { uint32 pad[0x2c / 4]; int mMode; };   // +0x2c
cUIState* GetUIState();                                  // 0x00b3d4d0
struct cCellScaleInfo {                       // Simulator::Cell::cCellScaleInfo (0x1c bytes)
    int scale;                                // +0x00
    int requiredFood;                         // +0x04
    int field_8;
    float field_C;
    float field_10;
    uint32 field_14;
    float field_18;
};
static const cCellScaleInfo kCellScaleInfos[21] = {
    { 1,    0,  0, 1.0f,     1.0f,     0x1d2ec0a4, 0.0f  },
    { 1,   50,  5, 1.73f,    1.0f,     0x1d2ec0a4, 0.0f  },
    { 2,  100, 10, 3.0f,     3.0f,     0x1d2ec0a4, 0.0f  },
    { 2,  150, 13, 5.2f,     3.0f,     0x1d2ec0a4, 0.0f  },
    { 3,  200, 16, 10.0f,    10.0f,    0x1d2ec0a5, 0.25f },
    { 3,  250, 19, 17.3f,    10.0f,    0x1d2ec0a5, 0.25f },
    { 4,  300, 22, 30.0f,    30.0f,    0x1d2ec0a5, 0.25f },
    { 4,  350, 25, 52.0f,    30.0f,    0x1d2ec0a5, 0.25f },
    { 5,  400, 28, 100.0f,   100.0f,   0x1d2ec0a6, 0.5f  },
    { 5,  450, 31, 173.0f,   100.0f,   0x1d2ec0a6, 0.5f  },
    { 6,  500, 34, 300.0f,   300.0f,   0x1d2ec0a6, 0.5f  },
    { 6,  550, 37, 520.0f,   300.0f,   0x1d2ec0a6, 0.5f  },
    { 7,  600, 40, 1000.0f,  1000.0f,  0x1d2ec0a7, 0.75f },
    { 7,  650, 43, 1730.0f,  1000.0f,  0x1d2ec0a7, 0.75f },
    { 8,  700, 46, 3000.0f,  3000.0f,  0x1d2ec0a7, 0.75f },
    { 8,  750, 49, 5200.0f,  3000.0f,  0x1d2ec0a7, 0.75f },
    { 9,  800, 52, 10000.0f, 10000.0f, 0x1d2ec0a0, 1.0f  },
    { 9,  850, 55, 17300.0f, 10000.0f, 0x1d2ec0a0, 1.0f  },
    { 10, 900, 58, 30000.0f, 30000.0f, 0x1d2ec0a0, 1.0f  },
    { 10, 950, 61, 52000.0f, 30000.0f, 0x1d2ec0a0, 1.0f  },
    { 10, 1000, 65, 52000.0f, 30000.0f, 0x1d2ec0a0, 1.0f },
};
inline const cCellScaleInfo* GetCellScaleInfo(int level)
{
    if (level == 1000)
        return &kCellScaleInfos[20];
    int i = 0;
    while (level >= kCellScaleInfos[i].requiredFood)
        i++;
    return &kCellScaleInfos[i - 1];
}
struct cSPTransform_s00e7_3f60 {                         // 0x38 bytes
    uint16 mFlags;                            // +0x00
    uint16 mModificationCount;                // +0x02
    Vector3_s00e7_3f60 mTranslation;                     // +0x04
    float mScale;                             // +0x10
    float mRotation[9];                       // +0x14
};
struct cCell_s00e7_3f60 {                                // SP::cSPCell / Simulator::Cell::cCellObjectData
    int mIndex;                               // +0x000 (pool handle)
    uint32 pad004[(0x48 - 0x04) / 4];
    cSPTransform_s00e7_3f60 mTransform;                  // +0x048
    float mRelativeElevation;                 // +0x080
    uint32 pad084[3];
    Vector3_s00e7_3f60 mVelocity;                        // +0x090
    uint32 pad09c;
    float mOpacity;                           // +0x0a0
    uint32 pad0a4[7];
    cSPTransform_s00e7_3f60 mVisualTransform;            // +0x0c0
    uint32 pad0f8;
    ResourceKey_s00e7_3f60 mModelKey;                    // +0x0fc
    uint32 pad108[(0x160 - 0x108) / 4];
    float field_160;                          // +0x160
    uint32 pad164[4];
    int field_174;                            // +0x174
};
#define CELL_FIELD(T, c, off) (*(T*)((char*)(c) + (off)))
struct cObjectPool_s00e7_3f60 {                          // cSPObjectPoolT<T, N>
    void* GetSafe(int index);                 // 0x00b721d0 (null when the handle is stale)
    void* Get(int index);                     // 0x00b72210
    int Begin();                              // 0x00e31100
    void* Next(int* pIterator);               // 0x00b72230
};
struct cCellSerializableData { uint32 pad[0x1c / 4]; int mLevel; };   // +0x1c
struct cCellGame_s00e7_3f60 {
    uint32 pad0000[0x1c / 4];
    cObjectPool_s00e7_3f60 mCells;                       // +0x001c
    uint32 pad0020[(0x40fc - 0x20) / 4];
    int midPlayerCell;                        // +0x40fc (cell group that renders in the main world)
    uint32 pad4100[2];
    void* mpFluidParticles;                   // +0x4108
    uint32 pad410c[4];
    int mAvatarCellIndex;                     // +0x411c
    bool field_4120;                          // +0x4120
    uint32 pad4124[(0x5158 - 0x4124) / 4];
    int field_5158;                           // +0x5158
    uint32 pad515c[(0x5190 - 0x515c) / 4];
    cCellSerializableData* mpSerializableData;   // +0x5190
    uint32 pad5194[(0x51b0 - 0x5194) / 4];
    int field_51b0;                           // +0x51b0
    int field_51b4;                           // +0x51b4
};
struct cCellGfxObject {                       // one entry of cCellGfx's pool at +0x168
    uint32 pad00[3];
    int mCellIndex;                           // +0x0c
    uint32 pad10[(0x60 - 0x10) / 4];
    cIVisualEffect_s00e7_3f60* mpElectricEffect;         // +0x60
    cIVisualEffect_s00e7_3f60* mpChargingEffect;         // +0x64
    uint32 pad68[4];
    cIVisualEffect_s00e7_3f60* mpPoisonEffect;           // +0x78
    uint32 pad7c[4];
    cIVisualEffect_s00e7_3f60* mpEffect8c;               // +0x8c
    cIVisualEffect_s00e7_3f60* mpEffect90;               // +0x90
    cIVisualEffect_s00e7_3f60* mpEffect94;               // +0x94
    cIVisualEffect_s00e7_3f60* mpPlayerEffect;           // +0x98
    cIVisualEffect_s00e7_3f60* mpEffect9c;               // +0x9c
    cIVisualEffect_s00e7_3f60* mpJetEffect;              // +0xa0
    cIVisualEffect_s00e7_3f60* mpCiliaEffect;            // +0xa4
    cIVisualEffect_s00e7_3f60* mpFlagellaEffect;         // +0xa8

    void Update(const cSPTransform_s00e7_3f60* transform, float opacity, float elevation, float lod,
                const cSPTransform_s00e7_3f60* visualTransform, int anim, int field24c, int scaleDelta,
                int group);                   // 0x00e62b80
};
struct cPartEffectTable {                     // pool entry at cCellGfx+0x168, data at +0x24
    uint32 pad[0x24 / 4];
    struct cEffectSet* mpEffects;             // +0x24
};
struct cEffectEntry { uint32 key; uint32 pad; int value; };
struct cEffectSet {
    uint32 pad[0x8c / 4];
    cEffectEntry mEntries[16];                // +0x8c
    uint32 mCount;                            // +0x14c
};
struct cCellGfx_s00e7_3f60 {
    uint32 pad00000[0x40 / 4];
    char field_40[0x128];                     // +0x40
    cObjectPool_s00e7_3f60 mGfxObjects;                  // +0x168
    uint32 pad0016c[(0x161bc - 0x16c) / 4];
    cIEffectsWorld* mpBackgroundEffectsWorld; // +0x161bc
    uint32 pad161c0[2];
    cIEffectsWorld* mpMainEffectsWorld;       // +0x161c8
    uint32 pad161cc[4];
    char field_161dc[0x14];                   // +0x161dc
    int mCurrentSample;                       // +0x161f0
    float mSpeedParamSampling[4];             // +0x161f4
    uint32 pad16204;
    int mAudioHandle;                         // +0x16208
};
struct cSPFluidParticles_s00e7_3f60 {
    char pad[0x1bd60];
    char field_1bd60[0x1c210 - 0x1bd60];      // +0x1bd60
    char field_1c210[4];                      // +0x1c210
};
struct cCellUI_s00e7_3f60 { uint32 pad[0x48 / 4]; Vector3_s00e7_3f60 mCursorPosition; };   // +0x48
struct cBoundingBox { Vector3_s00e7_3f60 lower; Vector3_s00e7_3f60 upper; };
extern cCellGame_s00e7_3f60* gspCellGame_s00e7_3f60;                // 0x016b3c04
extern cCellGfx_s00e7_3f60* gspCellGfx_s00e7_3f60;                  // 0x016b3c08
extern cCellUI_s00e7_3f60* gspCellUI;                    // 0x016b3c0c
extern cBoundingBox sVisibleBackgroundBBox;   // 0x016b3c88
void FUN_00e64e10();                                                   // 0x00e64e10
void LoadEffectMap();                                                  // 0x00e63560
void FUN_00e55080();                                                   // 0x00e55080
void SetAudioParameter(int handle, uint32 id, float value);           // 0x00e826b0
void SetGlobalAudioParameter(uint32 id, float value);                 // 0x00e82690
float FUN_00e5bfa0();                                                  // 0x00e5bfa0
float FUN_00e5be80();                                                  // 0x00e5be80
namespace SP {
float FluidParticlesSampleVelMagnitude(void* fluid, const Vector3_s00e7_3f60& pos);   // 0x00e4e590
}
namespace SP {
void UpdateCollectableVisibility(cCellGfxObject* gfx, int scale);     // 0x00e4f860
}
namespace SP {
int GetScaleDifferenceWithPlayer(cCell_s00e7_3f60* cell);                         // 0x00e57340
}
namespace SP {
bool CreateEffectSafe(cIEffectsWorld* world, uint32 id, int flags, cIVisualEffect_s00e7_3f60** ppEffect);   // 0x00628450
}
namespace SP {
void sUpdateElectricRibbonEffect(cIEffectsWorld* world, cIVisualEffect_s00e7_3f60** ppEffect, cCell_s00e7_3f60* cell, int a, int b);  // 0x00e6b9b0
}
namespace SP {
void sUpdateChargingEffect(cIEffectsWorld* world, cIVisualEffect_s00e7_3f60** ppEffect, const ResourceKey_s00e7_3f60* key,
                           cEffectSet* effects, const cSPTransform_s00e7_3f60* transform, bool b, float f);  // 0x00e6bc10
}
namespace SP {
void sUpdatePoisonReleaseEffect(cIEffectsWorld* world, cIVisualEffect_s00e7_3f60** ppEffect, cCell_s00e7_3f60* cell,
                                const ResourceKey_s00e7_3f60* key, const cSPTransform_s00e7_3f60* visualTransform, int level,
                                bool b, bool nearScale, bool isAvatar);  // 0x00e6bf30
}
float GetCellLod(cCell_s00e7_3f60* cell);                                         // 0x00e6d6d0
void StartPartEffect(cIVisualEffect_s00e7_3f60* effect, cEffectSet* effects, int a);   // 0x00e833f0
void UpdatePropulsionEffect(cIEffectsWorld* world, cIVisualEffect_s00e7_3f60** ppEffect, const cSPTransform_s00e7_3f60* visualTransform,
                            const cSPTransform_s00e7_3f60* transform, float scale, float strength, uint32 id,
                            const char* name);        // 0x00e639d0
bool CellWantsPlayerEffect(cCell_s00e7_3f60* cell);                               // 0x00e6b500
struct cCellResource { uint32 pad[0x1218 / 4]; int field_1218; uint32 pad121c[(0x128c - 0x121c) / 4]; int field_128c; };
cCellResource* GetCellResource_s00e7_3f60(ResourceKey_s00e7_3f60 key);                       // 0x00e679e0
void FUN_00e63bf0(cCell_s00e7_3f60* cell, cIEffectsWorld* world, cIVisualEffect_s00e7_3f60** ppEffect, const cSPTransform_s00e7_3f60* t, bool b);   // 0x00e63bf0
void CompactEffects(cCell_s00e7_3f60* cell, cCellGfxObject* gfx);                // 0x00e51990
void FUN_00e61050(cIEffectsWorld* world, cIVisualEffect_s00e7_3f60** ppEffect, const cSPTransform_s00e7_3f60* t, cEffectSet* effects,
                  int a, bool b);                                       // 0x00e61050
void FUN_00e67510(cIEffectsWorld* world, cIVisualEffect_s00e7_3f60** ppEffect, const cSPTransform_s00e7_3f60* visualTransform,
                  const cSPTransform_s00e7_3f60* t, cEffectSet* effects, int slot, bool b);   // 0x00e67510
void FUN_00e660e0(cCell_s00e7_3f60* cell, cCellGfxObject* gfx);                  // 0x00e660e0
void FUN_00e6c330();                                                   // 0x00e6c330
void FUN_00e63ac0(void* p);                                            // 0x00e63ac0
void FUN_00e831a0(void* p, void* a, void* b);                          // 0x00e831a0
static bool RemoveEffectEntry(cEffectSet* set, uint32 key, int* pValue)
{
    for (uint32 i = 0; i < set->mCount; i++) {
        if (set->mEntries[i].key == key) {
            if (pValue)
                *pValue = set->mEntries[i].value;
            set->mCount--;
            set->mEntries[i] = set->mEntries[set->mCount];
            return true;
        }
    }
    return false;
}
#define CELL_I(c, off)  CELL_FIELD(int, c, off)
#define CELL_F(c, off)  CELL_FIELD(float, c, off)
#define CELL_B(c, off)  CELL_FIELD(bool, c, off)
inline cObjectPool_s00e7_3f60& Cells() { return gspCellGame_s00e7_3f60->mCells; }
inline cObjectPool_s00e7_3f60& GfxObjects() { return gspCellGfx_s00e7_3f60->mGfxObjects; }
inline cCell_s00e7_3f60* GetCellSafe(int id) { return (cCell_s00e7_3f60*)Cells().GetSafe(id); }
inline cCell_s00e7_3f60* GetCell(int id) { return (cCell_s00e7_3f60*)Cells().Get(id); }
inline cCellGfxObject* NextGfx(int* it) { return (cCellGfxObject*)GfxObjects().Next(it); }
inline void* GetGfxEntry(int id) { return GfxObjects().Get(id); }
inline cEffectSet* GetPartEffects(cCell_s00e7_3f60* cell)
{
    if (!CELL_I(cell, 0x248))
        return 0;
    if (!cell->mModelKey.instanceID)
        return 0;
    return ((cPartEffectTable*)GetGfxEntry(CELL_I(cell, 0x248)))->mpEffects;
}
inline cIEffectsWorld* GetEffectsWorld(cCell_s00e7_3f60* cell)
{
    cIEffectsWorld*& world = CELL_I(cell, 0x35c) == gspCellGame_s00e7_3f60->midPlayerCell
                                 ? gspCellGfx_s00e7_3f60->mpMainEffectsWorld : gspCellGfx_s00e7_3f60->mpBackgroundEffectsWorld;
    return world;
}
inline bool IsCursorMode() { int mode = GetUIState()->mMode; return mode == 1 || mode == 2; }
// ---- items of slice s00e73f60 end

// ---- items of slice s00e74a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kTwoPi;                      // 016b3dd0 (runtime-initialised)
#pragma intrinsic(sin, cos)
struct Vector3f {                         // copies per float (movss)
    float x, y, z;
    Vector3f() {}
    Vector3f(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Quat {
    Vector3 v;
    float w;
};
extern const Vector3 kUnitZ;              // 015a7c40
extern const Quat kQuatIdentity;          // 015a7c4c
extern const Vector3 kVec3Zero;           // 016b3c28
extern const Matrix3 kMatrix3Identity;    // 016b3dac
extern const float kLevelSize_s00e7_4a20[];          // 01483bd0: 10, 30, 100, 300, ...
struct cSPTransform_s00e7_4a20 {                     // 0x38 bytes
    uint16 mFlags;                        // +0x00
    uint16 mModificationCount;            // +0x02
    Vector3 mTranslation;                 // +0x04
    float mScale;                         // +0x10
    Matrix3 mRotation;                    // +0x14
};
struct cCell_s00e7_4a20 {
    int mIndex;                           // +0x000 (pool handle)
    uint8 mActive; uint8 pad005[3];       // +0x004
    Vector3 mPosition;                    // +0x008
    Quat mOrientation;                    // +0x014
    uint32_t pad024[(0x48 - 0x24) / 4];
    cSPTransform_s00e7_4a20 mTransform;              // +0x048
    float mRelativeElevation;             // +0x080
    uint32_t pad084[3];
    Vector3 mVelocity;                    // +0x090
    uint32_t pad09c;
    float mOpacity;                       // +0x0a0
    float mField0a4;                      // +0x0a4
    float mField0a8;                      // +0x0a8
    float mField0ac;                      // +0x0ac
    uint32_t pad0b0;
    float mSize;                          // +0x0b4
    float mMass;                          // +0x0b8
    float mInvMass;                       // +0x0bc
    cSPTransform_s00e7_4a20 mVisualTransform;        // +0x0c0
    uint32_t pad0f8;
    Vector3 mModelKey;                    // +0x0fc (ResourceKey: instance, type, group)
    int mDefId;                           // +0x108
    int mField10c;
    uint8 mByte110, mByte111, mByte112, mByte113;
    uint32_t pad114;
    int mField118;
    int mField11c;
    int mField120;
    int mField124;
    int mField128;
    Vector3f mField12c;
    Vector3 mField138;
    int mField144;
    uint32_t pad148;
    int mField14c;
    float mField150;
    uint32_t pad154;
    float mField158;                      // +0x158 (written by FUN_00e6cad0)
    float mField15c;                      // +0x15c
    uint32_t pad160[(0x1c0 - 0x160) / 4];
    float mField1c0;
    uint32_t pad1c4[3];
    float mField1d0;
    uint32_t pad1d4[(0x1fc - 0x1d4) / 4];
    Vector3 mField1fc;
    uint32_t pad208[(0x234 - 0x208) / 4];
    float mField234;
    uint32_t pad238[(0x244 - 0x238) / 4];
    int mField244;
    int mField248, mField24c, mField250;
    uint32_t pad254[(0x354 - 0x254) / 4];
    uint8 mByte354; uint8 pad355[3];
    int mField358;                        // +0x358 level index
    int mField35c;                        // +0x35c group
    int mField360;                        // +0x360 handle from FUN_00e868f0
    int mField364;                        // +0x364 collision proxy
    float mField368;
    int mField36c;
    int mField370;
    float mField374;
};
struct cLevelInfo_s00e7_4a20 {
    int mType;                            // +0x00 (-1 = absent)
    uint32_t pad04[(0x48 - 0x04) / 4];
    float mLimit;                         // +0x48
    uint32_t pad4c[(0xb4 - 0x4c) / 4];
};
struct cCellDef {                         // resolved by FUN_00e823a0
    uint32_t pad00[0xac / 4];
    uint8 mSpecial; uint8 padad[3];       // +0xac
    uint32_t padb0;
    int mKind;                            // +0xb4
    uint32_t padb8[(0xe0 - 0xb8) / 4];
    cLevelInfo_s00e7_4a20 mLevels[3];                // +0xe0, +0x194, +0x248
    uint32_t pad2fc[(0x304 - 0x2fc) / 4];
    uint32_t mField304;
};
struct cDefRef {
    cDefRef();
    ~cDefRef();
    void* mp;
};
struct cObjectPool_s00e7_4a20 {                      // cSPObjectPoolT<cCell>
    int New();                            // 00b72160
    cCell_s00e7_4a20* Get(int index);                // 00b72210
};
struct cCellSerializableData_s00e7_4a20 { uint32_t pad[0x7c / 4]; int mStage; };   // +0x7c
struct cCellGame_s00e7_4a20 {
    uint32_t pad0000[0x1c / 4];
    cObjectPool_s00e7_4a20 mCells;                   // +0x001c
    uint32_t pad0020[(0x40fc - 0x20) / 4];
    int midPlayerCell;                    // +0x40fc
    int mGroup4100;                       // +0x4100
    void* mpPhysics;                      // +0x4104
    uint32_t pad4108[(0x514c - 0x4108) / 4];
    float mField514c;                     // +0x514c
    uint32_t pad5150[(0x5190 - 0x5150) / 4];
    cCellSerializableData_s00e7_4a20* mpSerializableData;   // +0x5190
};
extern cCellGame_s00e7_4a20* gspCellGame_s00e7_4a20;            // 016b3c04
cCellDef* GetCellDef(int defId, cDefRef* ref);                 // 00e4cc40 -> 00e823a0
float FUN_004df2d0(const void* p);                             // 004df2d0 (cdecl, x87 return)
float FUN_00e4f9d0(int defId);                                 // 00e4f9d0 (static in the cell TU: xmm0 return)
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quat* q);   // 0059c190
Vector3* FUN_00e5eb20(Vector3* out, cCell_s00e7_4a20* c);                 // 00e5eb20
Vector3* FUN_00e65640(Vector3* out, int defId);                // 00e65640
void FUN_00e6cad0(cCellDef* def, Vector3 key, float* a, float* b);   // 00e6cad0
void FUN_00e6d790(cCell_s00e7_4a20* c, Vector3* center, float* radius);   // 00e6d790 (esi = cell, edi = center, [esp+4] = radius)
int FUN_00e868f0(int group, Vector3* center, float radius, int index);   // 00e868f0
int FUN_00bbbdd0(void* physics, int index, const float* lo, const float* hi, int filter);   // 00bbbdd0 (thunk to 00bbb120)
union P8 { uint8 flag; float radius; };
// ---- items of slice s00e74a20 end

// this callee is defined in this TU as `char FUN_00e68630(int)` (0x00e68630, below): declared here so that the slice's
// conflicting `unsigned FUN_00e68630(int cell);` spelling is dropped by the prototype dedupe (C2556) instead of clashing
char FUN_00e68630(int cell);                             // 0x00e68630

// ---- items of slice s00e76880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gOrientUp[3];            // 0x015a7c34 orientation basis
extern float gUp_015a7c40[3];         // 0x015a7c40 reference "up"
#pragma intrinsic(sin)
#pragma intrinsic(cos)
#define U(p,o) (*(uint32*)((char*)(p) + (o)))
#define B_s00e7_6880(p,o) (*(uint8*)((char*)(p) + (o)))
#define GF(a)  (*(float*)(a))
struct cSPTransform_s00e7_6880 {                 // 0x38 bytes, embedded at cell + 0x48
    uint16 mFlags;
    uint16 mModCount;
    float  mTranslation[3];
    float  mScale;
    float  mRotation[9];
};
struct ObjectPool_s00e7_6880 {                   // cSPObjectPool, at gspCellGame+0x1c
    void* Get(int id);                // 0x00b72210
    void* GetSafe(int id);            // 0x00b721d0
};
extern char* gspCellGame_s00e7_6880;             // 0x016b3c04
struct RandomLCG_s00e7_6880 {                    // EA::Random::RandomLinearCongruential
    uint32 RandomUint32Uniform(uint32 range);   // 0x00a68fb0
    double RandomDoubleUniform();               // 0x009360d0
};
extern RandomLCG_s00e7_6880 gRandomLCG_s00e7_6880;          // 0x01601760
unsigned FUN_00e68630_s00e7_6880(int cell);                                   // 0x00e68630
char     FUN_00e69580(int* cell);                                  // 0x00e69580
void     FUN_00e68000(int cell, int arg, cSPTransform_s00e7_6880* xf);        // 0x00e68000
void     FUN_00e76660(int* cell, int arg, void* xf);               // 0x00e76660
void     FUN_00e71980(float dt);                                   // 0x00e71980
struct IterObj {                       // resource-iterator handle (first dword is the owned node)
    void* mpNode;                      // +0x0
    void Init();                       // 0x00743b50: mpNode = 0
    void Release();                    // 0x00e82130: if (mpNode) --mpNode->refcount (+0xc)
};
void     FUN_00e61b90(int a, int b);                               // 0x00e61b90
char     FUN_00e699b0(void* a, int b);                             // 0x00e699b0
char     FUN_00e5d340();                                           // 0x00e5d340
int      FUN_00e50990(int a);                                      // 0x00e50990
void     FUN_00e780a0(int handle, int a, int b, int c);            // 0x00e780a0
float*   FUN_00e5cae0();                                           // 0x00e5cae0
int      FUN_00e76480(int a, int b, const void* c, const void* d,
                      const void* e, int f, int g, int h, int i, int j, int k); // 0x00e76480
int      FUN_00e74a20(int a1, float* pos, int a3, int a4, int a5, float a6,
                      float a7, float a8, const void* def, int a10);   // 0x00e74a20
void     sAttach(int handle, int idx, int obj, cSPTransform_s00e7_6880* xf, int flag); // 0x00e5f450
float*   Matrix3FromFacingAndUp(float* out, const float* facing, const float* up); // 0x0069b440
float*   Matrix3FromQuaternion(float* out, const float* q);        // 0x0059c190
void     QuaternionFromFacingAndUp(float* out, const float* facing, const float* up); // 0x0069b600
void     FUN_0040efa0(void* self);                                 // 0x0040efa0
void     ComposeTransforms(cSPTransform_s00e7_6880* xf);                      // 0x0040ccb0
// ---- items of slice s00e76880 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00e76880(void* cell, float dt);  // 0x00e76880 (stays in the slice: not this object's)

// ---- items of slice s00e777a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00e7_77a0 { float x, y, z; Vector3_s00e7_77a0() {} Vector3_s00e7_77a0(float a,float b,float c):x(a),y(b),z(c){} };
struct CellInfo_s00e7_77a0 {
    char pad[0xcc];
    int mFieldCC;   // 0xcc
    char padD0[0xd4 - 0xd0];
    int mFieldD4;   // 0xd4
};
struct ObjectPool_s00e7_77a0 {
    void* Get(int handle) const;         // 0x00b72210
    void* GetChecked(int handle) const;  // 0x00b721d0
    int   Alloc();                       // 0x00b72160
    void  Free(int handle);              // 0x00b72260
};
struct cLevelInfo_s00e7_77a0 { char pad[0x1c]; int mStage; };   // +0x1c
struct cCellGame_s00e7_77a0 {
    char pad0[0x1c];
    ObjectPool_s00e7_77a0 mCells;   // 0x1c
    char pad20[0x40fc - 0x20];
    int mSel40fc;        // 0x40fc
    int mSel4100;        // 0x4100
    int mObstacleGrid;   // 0x4104
    char pad4108[0x411c - 0x4108];
    int mHandle411c;     // 0x411c
    char pad4120;
    char mByte4121;
    char pad4122[0x5190 - 0x4122];
    cLevelInfo_s00e7_77a0* mpLevelInfo;  // 0x5190
    int mField5194;           // 0x5194
};
struct CellState {
    char pad0[0xe0];
    int mFieldE0;         // 0xe0
    char padE4[0xf4 - 0xe4];
    float mFieldF4;       // 0xf4
    char padF8[0x936 - 0xf8];
    char mField936;       // 0x936
};
struct cSpawnCell {
    int mHandle;          // 0x000
    char pad004[0x1c - 4];
    float mField1c;       // 0x1c
    float mField20;       // 0x20
    int mField24;         // 0x24
    int mField28;         // 0x28
    int mField2c;         // 0x2c
    int mField30;         // 0x30
    int mField34;         // 0x34
    int mField38;         // 0x38
    int mField3c;         // 0x3c
    int mField40;         // 0x40
    int mField44;         // 0x44
    char mField48[4];     // 0x48
    Vector3_s00e7_77a0 mPos;         // 0x4c
    float mRadius;        // 0x58
    char pad05c[0xfc - 0x5c];
    CellKey mKey;         // 0x0fc
    int mType;            // 0x108
    char pad10c[0x17f - 0x10c];
    char mField17f;       // 0x17f
    char pad180[0x1b0 - 0x180];
    int mField1b0;
    char pad1b4[0x248 - 0x1b4];
    int mPoolHandle;      // 0x248
    char pad24c[0x358 - 0x24c];
    int mField358;        // 0x358
    int mField35c;        // 0x35c
    int mField360;        // 0x360
    int mField364;        // 0x364
    char pad368[0x370 - 0x368];
    int mField370;        // 0x370
};
extern cCellGame_s00e7_77a0* gspCellGame_s00e7_77a0;    // 0x016b3c04
extern CellState* gspCellState_s00e7_77a0;   // 0x016b3c0c
extern Vector3_s00e7_77a0 gCellWorldCenter_s00e7_77a0;  // 0x016b3c28
extern Vector3_s00e7_77a0 gDefaultTransform; // 0x015a7c4c
int  FUN_00e4cce0_5(int id, int a, float b, float c, float d);  // 0x00e4cce0
int  sGetSourceLevel();                          // 0x00e4ee60
void FUN_00e86980(int a, int b);                 // 0x00e86980
void FUN_00bbbde0(int grid, int obstacle);       // 0x00bbbde0 (thunk to 0x00bbb210)
void FUN_00e66010(int a);                        // 0x00e66010
void FUN_00e67890(cSpawnCell* c);                // 0x00e67890
void FUN_00e59200(int a);                        // 0x00e59200
void FUN_00e61370(void* out, void* in, float t);// 0x00e61370
int  sCreateCellAttachment(cSpawnCell* c, int a, void* vec, int b, int type, int key); // 0x00e76d70
int  FUN_00e74a20(int a1, int a2, float f1, int type, int count, float f2, float f3,
                  int one, const void* def, int neg1);   // 0x00e74a20
void sDropLoot(int a1, void* key, int a3, void* pos, float radius, int lvl, int a7, int a8,
               void* out, int* count);                  // 0x00e771d0
int  FUN_00e76540(void* a, int b, int c);        // 0x00e76540
class RandomLCG_s00e7_77a0 { public: double RandomDoubleUniform(); };  // 0x009360d0
extern RandomLCG_s00e7_77a0 gMathRandom_s00e7_77a0;   // 0x01601760
inline int GetStageLevel(int stage)
{
    int* p;
    if (stage == 1000) {
        p = (int*)&kCellEditorStage;
    } else {
        int i = 0;
        p = (int*)&kCellStages[0];
        if (stage >= 0) {
            p = (int*)&kCellStages[1].mStart;
            do { p += 7; i++; } while (stage >= *p);
        }
        p = (int*)&kCellStages[0] + i * 7;
    }
    return *p;
}
// ---- items of slice s00e777a0 end

// this slice's getter returns its own trigger-manager stub (the TU's `cTriggerMgr` from slice s00e4e8d0 differs).  The stub is
// defined here with the slice's exact text so the prototype dedupe takes this declaration and ret_clash cannot rename the calls.
struct cTriggerMgr_s00e7_94f0 {
    void goExit();                                                  // 0x00ad7df0 Sim::goExit
    void PostTrigger(const char* name, int a, int b, int c, int d, int e); // 0x00ae0930
};
cTriggerMgr_s00e7_94f0* GetTriggerMgr();                 // 0x00b3d4d0
// the TU's other spellings of 0x00e5eb20 take/return void* (line 1191) or Vector3* (line 2426), so an overload set hides the
// slice's `float* (float*, int)`; this alias carries that exact prototype (same symbol/address, and retail returns its out pointer).
extern "C" float* FUN_00e5eb20_f(float* out, int cell); // 0x00e5eb20

// ---- items of slice s00e794f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  gK_1414a84;         // 0x01414a84  3.5f
extern float  gK_1483f34;         // 0x01483f34  4.5f
extern float  gK_13eecd8;         // 0x013eecd8  20.0f
extern "C" void  FUN_00e5f010(int a, int b, float d, int c);               // 0x00e5f010
extern "C" void  __fastcall FUN_00e79460(float* center, int pool, float radius, int exclude); // 0x00e79460
extern "C" int   FUN_00e5cde0(void* cell);                                 // 0x00e5cde0 cell-visibility
extern float  gK_1471064;         // 0x01471064  0.5f
extern float  gK_13ec4b8;         // 0x013ec4b8  1e-08f
extern float  gK_13ec480;         // 0x013ec480  0.2f
extern float  gK_1473c70;         // 0x01473c70  10.0f
extern float  gK_14853e0;         // 0x014853e0  4.0f
extern "C" void  FUN_00e70e30(int a, int b, float c);                      // 0x00e70e30
extern "C" void  FUN_00e6f660(int cell, float* pos, float dt, float f, int x); // 0x00e6f660
extern "C" void  FUN_00e6f800(int cell, int handle, float dt, float f, int x); // 0x00e6f800
extern "C" void  FUN_00e6f940(int cell, int handle, float f, int x);       // 0x00e6f940
extern "C" void  FUN_00e6ff60(int cell, float f, int x);                   // 0x00e6ff60
extern "C" int   FUN_00e4ee60(void);                                       // 0x00e4ee60 SP::sGetSourceLevel
extern "C" void  FUN_00e791f0(int cell, int handle, float dt);             // 0x00e791f0 SP::sDigestionOutput
extern "C" void  FUN_00e771d0(int a, int b, int c, float* p, float d,
                              int e, int f, float g, int h, int i);        // 0x00e771d0 SP::sDropLoot
extern int    gFwd_16b3c28_s00e7_94f0;       // 0x016b3c28  camera forward (copied as raw dwords)
extern int    gFwd_16b3c2c_s00e7_94f0;       // 0x016b3c2c
extern int    gFwd_16b3c30_s00e7_94f0;       // 0x016b3c30
extern int    gBasis_15a7c4c_s00e7_94f0;     // 0x015a7c4c  orthogonal basis
extern int    gBasis_15a7c50_s00e7_94f0;
extern int    gBasis_15a7c54_s00e7_94f0;
extern int    gBasis_15a7c58_s00e7_94f0;
struct cCellCmd_s00e7_94f0 {
    char  pad00[4];
    int   x04;               // +0x04  callback / 0
    char  x08;               // +0x08
    char  pad09[0x13];
    float t1c;               // +0x1c  duration A
    float t20;               // +0x20  duration B
    int   kind24;            // +0x24  command kind
    int   src28;             // +0x28  source handle
    int   arg2c;             // +0x2c
    int   arg30;             // +0x30
    int   arg34;             // +0x34
    int   arg38;             // +0x38
    int   arg3c;             // +0x3c
    float f40;               // +0x40
    float f44;               // +0x44
    int   from48, from4c, from50;   // +0x48  start point (raw dwords)
    int   to54, to58, to5c;         // +0x54  end point
    int   dir60, dir64, dir68, dir6c;// +0x60 direction / basis
    int   flag70;            // +0x70
    char  flag74;            // +0x74
    int   flag78;            // +0x78
};
extern "C" void* FUN_00e52910_s00e7_94f0(int handle);                                 // 0x00e52910 resolve handle
extern float  gK_1486110;         // 0x01486110  5.0f
extern float  gK_14007f4;         // 0x014007f4  15.0f
extern float  gK_13ec5b4;         // 0x013ec5b4  1000.0f
extern "C" void  __fastcall FUN_00e78b20(float* center, int pool, float radius, int exclude); // 0x00e78b20
extern "C" void  FUN_00e577a0(int cell, float* dir);                       // 0x00e577a0
extern "C" void* FUN_00e74a20(int pool, void* pos, int z, int entry);      // 0x00e74a20 CreateCell
// ---- items of slice s00e794f0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00e79c30(int cell, int other, float dt);  // 0x00e79c30 (stays in the slice: not this object's)

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int FUN_00e79a00(int cmd, float dt);  // 0x00e79a00 (stays in the slice: not this object's)

// ---- items of slice s00e7a190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char   gMatrix_16b3dac;    // 0x016b3dac  default Matrix33
extern float  gk_1485720;         // 0x01485720  1.0f
extern "C" void   FUN_00e76a80(int self, int other, float dt);             // 0x00e76a80
extern "C" void   FUN_00e71c00(int cell, int other, float dt);             // 0x00e71c00
extern "C" void   FUN_00e6f5b0(int cell, float dt);                        // 0x00e6f5b0
extern "C" void   FUN_00e71300(float dt);                                  // 0x00e71300
extern "C" void   FUN_00e70650(int cell, float dt);                        // 0x00e70650 OrientToAvatar
extern "C" void   FUN_00e704b0(int cell, int other, float dt);             // 0x00e704b0
extern "C" void   FUN_00e702d0(int cell, int other, float dt);             // 0x00e702d0
extern "C" void   FUN_00e6f990(int cell, float dt);                        // 0x00e6f990
extern "C" void   FUN_00e707d0(int cell, float dt);                        // 0x00e707d0
extern "C" void   FUN_00e6fbb0(int cell, float dt);                        // 0x00e6fbb0
extern "C" void   FUN_00e6fd70(int cell, float dt);                        // 0x00e6fd70
extern "C" void   FUN_00e6fce0(int cell, float dt);                        // 0x00e6fce0
extern "C" int    SPIDFromName(const char* name);                          // 0x00571cf0
extern "C" void   FUN_00e71f00(void* cell, int a);                         // 0x00e71f00
extern "C" void   FUN_00e514c0(void);                                      // 0x00e514c0 emit
extern "C" int    FUN_00e52a40(int a, int b, int c, float f, int d, int e); // 0x00e52a40
extern "C" void   FUN_00e59170(int a, float f);                            // 0x00e59170 reset
extern "C" void   FUN_00e72060(void* cell, int a, int b, float dt);        // 0x00e72060
extern "C" void   FUN_0040ce80(void* t);                                   // 0x0040ce80
extern "C" void   FUN_00537dc0(void* dst, void* src);                      // 0x00537dc0 operator=
extern "C" void   FUN_0040ccb0(void* a, void* b);                          // 0x0040ccb0 ComposeTransforms
extern "C" void   FUN_004ff6d0(void* ctx, void* pt);                       // 0x004ff6d0 BackTransformPoint
extern "C" void   FUN_0041cb40(void* dst, void* src);                      // 0x0041cb40 Matrix3::Assign
extern "C" float  FUN_00e6d6d0(int a, int b, int c, int d, int e, int f);  // 0x00e6d6d0
extern "C" void   FUN_00e62b80(void* t, int a, int b, float f, int c, int d, int e, int g, int h); // 0x00e62b80
extern "C" void   FUN_00e72200(int handle);                                // 0x00e72200
struct cObjectPool_s00e7_a190 {
    void* GetSafe(int id);   // 0x00b721d0
    void* Get(int id);       // 0x00b72210
    int   Alloc();           // 0x00b72160
    void* Next(int* it);     // 0x00b72230
    int   Front();           // 0x00e31100
};
struct cCellCmd_s00e7_a190 {
    char  pad00[4];
    int   x04;               // +0x04
    char  x08;               // +0x08
    char  pad09[0x13];
    float t1c;               // +0x1c
    float t20;               // +0x20
    int   kind24;            // +0x24
    int   src28;             // +0x28
    int   arg2c;             // +0x2c
    int   arg30;             // +0x30
    int   arg34;             // +0x34
    int   arg38;             // +0x38
    int   arg3c;             // +0x3c
    float f40;               // +0x40
    float f44;               // +0x44
    int   from48, from4c, from50;   // +0x48
    int   to54, to58, to5c;         // +0x54
    int   dir60, dir64, dir68, dir6c;// +0x60
    int   flag70;            // +0x70
    char  flag74;            // +0x74
    int   flag78;            // +0x78
};
namespace SP {
    void sUpdateAICaterpillar(int cell, float dt);   // 0x00e78fc0
}
namespace SP {
    int  sGetSourceLevel(void);                      // 0x00e4ee60
}
namespace SP {
    void sDropLoot(int a, int b, int c, float* p, float f, int lvl, int flag, float dt, int x, int y); // 0x00e771d0
}
extern "C" void*  FUN_00e52910_s00e7_a190(int handle);                                // 0x00e52910 resolve handle
extern "C" void   FUN_00e6f800_s00e7_a190(int cell, int avatar, float dt, float f, int f40, int a, int b, int c); // 0x00e6f800
extern "C" int    FNV1_String8_s00e7_a190(const char* s, unsigned seed, int one);     // 0x00932e80
// ---- items of slice s00e7a190 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00e7aa20(int* p, float dt);  // 0x00e7aa20 (stays in the slice: not this object's)

// case callees of 0x00e7ba30: the slice's prototypes, respelled with the TU definition's return type where the
// parameter list is identical (C2556 forbids two declarations that differ only by return type)
void        FUN_00e532e0(void* a, float b);                                     // 0x00e532e0
void        FUN_00e53c70(void* a, float b, float t);                            // 0x00e53c70
void        FUN_00e53d50(float a, float b);                                     // 0x00e53d50
void        FUN_00e56820(float a, float b);                                     // 0x00e56820
void        FUN_00e569b0();                                                     // 0x00e569b0
void        FUN_00e571f0(int a, int b);                                         // 0x00e571f0
void        FUN_00e579c0(int a, int b);                                         // 0x00e579c0
void        FUN_00e57a60(int a, int b, int c, int d, void* e);                  // 0x00e57a60
void        FUN_00e57b50(int a, int b, int c, void* d);                         // 0x00e57b50
void        FUN_00e57c30(int a, int b, int c, float t);                         // 0x00e57c30
void        FUN_00e57c90(int a, int b);                                         // 0x00e57c90
void        FUN_00e57dc0(int a);                                                // 0x00e57dc0
bool        FUN_00e58890(int a, int b, int c);                                  // 0x00e58890
void        FUN_00e58ae0(int a);                                                // 0x00e58ae0
bool        FUN_00e58bf0(int a, float b, float c);                              // 0x00e58bf0
void        FUN_00e59010(int a, int b, int c, int d, float e, void* f);         // 0x00e59010
void        FUN_00e59170(int a, float b);                                       // 0x00e59170
void        FUN_00e591c0(int a, float t);                                       // 0x00e591c0
bool        FUN_00e59260(int a);                                                // 0x00e59260
void        FUN_00e592f0(int a, int b, int c, void* d, void* e);                // 0x00e592f0
void        FUN_00e593b0(int a, int b, int c, void* d);                         // 0x00e593b0
bool        FUN_00e59470(int a);                                                // 0x00e59470
bool        FUN_00e59500(int a);                                                // 0x00e59500
bool        FUN_00e59560(int a, int b);                                         // 0x00e59560
void        FUN_00e59640(int a, int b, int c, int d, void* e);                  // 0x00e59640
void        FUN_00e59710(int a, int b, int c, float d, float e, float t);       // 0x00e59710
static bool FUN_00e598e0(int a, float b);                                       // 0x00e598e0
static bool FUN_00e599b0(int a);                                                // 0x00e599b0
bool        FUN_00e59a30();                                                     // 0x00e59a30
static bool FUN_00e59a70(int id);                                               // 0x00e59a70
bool        FUN_00e59af0(int a, int b);                                         // 0x00e59af0
void        FUN_00e59b50(int a, int b, void* c);                                // 0x00e59b50
void        FUN_00e5ec10(int a);                                                // 0x00e5ec10
void        FUN_00e5ec70(int a, float b);                                       // 0x00e5ec70
void        FUN_00e5ed50(int a, void* b, void* c, float d, float e);            // 0x00e5ed50
void        FUN_00e5f160(int a, int b, void* c, float t);                       // 0x00e5f160
void        FUN_00e69a90(int a, int b, int c, int d, float e, float f);         // 0x00e69a90
int         FUN_00e69c10(int a, int b, int c, float d, float t);                // 0x00e69c10
int         FUN_00e69e00(int a, int b, int c, float d, float t);                // 0x00e69e00
int         FUN_00e6a090(int a, int b, int c, float d, float t);                // 0x00e6a090
void        FUN_00e75c30(float t);                                              // 0x00e75c30
void        FUN_00e76360(void* a, int b, int c, int d, void* e, void* f, void* g,
                         int h, float i, int j, int k, float l);                // 0x00e76360

// ---- items of slice s00e7b0a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define B_s00e7_b0a0(p,o) (*(uint8*)((char*)(p) + (o)))
struct Vec3_s00e7_b0a0 { float x, y, z; };
extern char*  gspCellGame_s00e7_b0a0;       // 0x016b3c04
extern char*  gspCellUI_s00e7_b0a0;         // 0x016b3c0c
extern Vec3_s00e7_b0a0   gCellWorldCenter_s00e7_b0a0;  // 0x016b3c28
struct cObjectPool_s00e7_b0a0 {                    // cSPObjectPoolT<T,N>
    void* GetSafe(int h);               // 0x00b721d0  (thiscall, ret 4)
    void* Get(int h);                   // 0x00b72210  (thiscall, ret 4)
    int   Alloc();                      // 0x00b72160  (thiscall, ret)
    void  Free(int h);                  // 0x00b72260  (thiscall, ret 4)
};
static cObjectPool_s00e7_b0a0* cells_s00e7_b0a0() { return (cObjectPool_s00e7_b0a0*)(gspCellGame_s00e7_b0a0 + 0x1c); }
static cObjectPool_s00e7_b0a0* msgs()  { return (cObjectPool_s00e7_b0a0*)(gspCellGame_s00e7_b0a0 + 0x54); }
struct cCellMessage {
    void*   vptr;      // +0x00
    void*   cb;        // +0x04  callback
    uint8   st8;       // +0x08
    uint8   pad09[3];
    float   f0c;       // +0x0c
    float   f10;       // +0x10
    uint8   pad14[8];
    float   f1c;       // +0x1c
    float   f20;       // +0x20
    int     type;      // +0x24  message id
    int     a28;       // +0x28
    int     a2c;       // +0x2c
    int     a30;       // +0x30
    int     a34;       // +0x34
    int     a38;       // +0x38
    int     a3c;       // +0x3c
    float   f40;       // +0x40
    float   f44;       // +0x44
    Vec3_s00e7_b0a0    v48;       // +0x48
    Vec3_s00e7_b0a0    v54;       // +0x54
    Vec3_s00e7_b0a0    v60;       // +0x60
    int     a6c;       // +0x6c
    int     a70;       // +0x70
    uint8   b74;       // +0x74
    uint8   pad75[3];
    int     a78;       // +0x78
};
struct cOccupancy { int* Claim(); };    // 0x00e65840 (thiscall)
struct cTriggerMgr_s00e7_b0a0 { void setModal(int); };   // 0x00ad7e40 (thiscall, ret 4)
cTriggerMgr_s00e7_b0a0* GetTriggerMgr_s00e7_b0a0();                 // 0x00b3d4d0
int   __fastcall sGetSourceLevel(void* unused, int level);          // 0x00e4ee60 (level in EDX)
void* FUN_00e4cce0_s00e7_b0a0(int id);                                        // 0x00e4cce0 LayerCatalog_GetEntry
int   FUN_00e57340(void* p);                                       // 0x00e57340 cell age
bool  FUN_00e52960();                                              // 0x00e52960
int   FUN_00e58980(void* a, void* b);                              // 0x00e58980
bool  FUN_00e57460_s00e7_b0a0(void* a, void* b);                              // 0x00e57460
float FUN_00e6d200(void* a, int b, int c, int d);                  // 0x00e6d200
void  FUN_00e7a7c0(void* a, void* b, void* dir, int c, int d, float t); // 0x00e7a7c0
void  FUN_00e7aee0(void* a, void* b, float t);                     // 0x00e7aee0
void  FUN_00e7a4a0(void* cell, int a, int b, int c, int d, float t); // 0x00e7a4a0
void  FUN_00e76af0(void* cell, void* pos, int level, void* entry, int a5); // 0x00e76af0
void  FUN_00e780a0(int id, int a, float b, int c);                 // 0x00e780a0
void  FUN_00e51ee0(int a, float b, int c, int d, int e, int f, int g, int h,
                   int i, int j, int k, int l, int m, int n, int o, int p); // 0x00e51ee0
void  FUN_00e528d0(void (*fp)(void));                              // 0x00e528d0
void  FUN_00e59200(void* p);                                       // 0x00e59200
int   FUN_00e87260(int group, void* pos, float radius, int* out, int max, int mask); // 0x00e87260
void  FUN_00e77ac0(void* cell, void* a, void* b, float t);         // 0x00e77ac0 sDropPieces
void  FUN_00e5d7b0(int p);                                         // 0x00e5d7b0
bool  FUN_00e7b280(void* m, float t);                              // forward (used by 0xe7b470)
int   FUN_00e7b8a0(void* p, float a, float b);
void  FUN_00e7b7c0(void* list, void* x, void* pos, float t);       // forward
// ---- items of slice s00e7b0a0 end

// ---- items of slice s00e7ce10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int    g_keyDefaultFood;        // 0x016b3c14  (default-food resource handle)
extern int    g_levelMaxTime;          // 0x01483c2c  (clamp target for level[0x1c])
extern float  g_147b9f0;               // 0x0147b9f0
extern float  g_1440f84;               // 0x01440f84  (1/6)
extern float  g_1470f1c;               // 0x01470f1c  (2.0f)
extern float  g_half_1471064;          // 0x01471064  (0.5f)
extern "C" int   FUN_00e4fca0(void);                                // 0x00e4fca0
extern "C" void  FUN_00e6e8c0(int a);                               // 0x00e6e8c0
extern "C" void  FUN_00e79720(void);                                // 0x00e79720 sCinematicGoldy_Start
extern "C" int   __fastcall FUN_00e51430(int level);                // 0x00e51430 level row
extern "C" float __fastcall FUN_00e4eea0(int unused, int n);        // 0x00e4eea0 CellLevel_GetFloat
extern "C" void  FUN_00e7cd10(void);                                // 0x00e7cd10
extern "C" float FUN_00e52b70(void);                                // 0x00e52b70
extern "C" void  FUN_00e648d0(void* self);                          // 0x00e648d0 empty stub
extern "C" void  FUN_00e51650(void);                                // 0x00e51650 emit
extern "C" void  FUN_00e53460(void);                                // 0x00e53460 mission
extern "C" void  FUN_00e62340(void* cell, int v);                   // 0x00e62340
extern "C" void  FUN_00e77d50(float dt);                            // 0x00e77d50
extern "C" int   FUN_00e5fa80(void* self, float* out);              // 0x00e5fa80 collect
extern "C" void  FUN_00e7c6c0(void* a, void* b);                    // 0x00e7c6c0
extern "C" void* FUN_00e63d60(void* self, void* pos, void* val);    // EASTL insert
extern "C" char  FUN_00e509d0(int a, void* b);                      // 0x00e509d0 mode
extern "C" void  FUN_00e72530(void* p, int a, void* v);             // 0x00e72530
extern "C" void  FUN_00e79320(void* self, int b, float f);          // 0x00e79320 sOnEatEater
struct Vec3_s00e7_ce10 { float x, y, z; };
extern char*  gspCellGame_s00e7_ce10;             // 0x016b3c04
extern char*  gspCellUI_s00e7_ce10;               // 0x016b3c0c
extern Vec3_s00e7_ce10   gCellWorldCenter_s00e7_ce10;        // 0x016b3c28
struct Pool_s00e7_ce10 {
    void* GetSafe(int h);        // 0x00b721d0, thiscall ret 4
    void* Get(int h);            // 0x00b72210, thiscall ret 4
    int   Alloc();               // 0x00b72160, thiscall ret
    void  Free(int h);           // 0x00b72260, thiscall ret 4
};
struct cTriggerMgr_s00e7_ce10 { void setModal(int a); };                 // 0x00ad7e40 thiscall
struct cSPUILayout_s00e7_ce10 { void* FindWindowByID(u32 id, int flag); };// 0x008105b0 thiscall
extern "C" void* FUN_00e52910_s00e7_ce10(int handle);                          // 0x00e52910 resolve handle
extern "C" void  FUN_00e57170_s00e7_ce10(int id, float v);                     // 0x00e57170 set
extern "C" void  FUN_00e394f0(u32 id, void* a, void* b, void* c, void* d); // 0x00e394f0
extern "C" void  FUN_00e5c8e0_s00e7_ce10(void* self);                          // 0x00e5c8e0 spawn
extern "C" cTriggerMgr_s00e7_ce10* FUN_00b3d4d0_s00e7_ce10(void);                         // 0x00b3d4d0 GetTriggerMgr
void FUN_00e7d070(int handle, int param_1, float param_2);          // 0x00e7d070 (EAX ABI)
void FUN_00e7d760(void* self, int a, int b, float f);               // 0x00e7d760 (ESI/EDI ABI)
// ---- items of slice s00e7ce10 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00e7ce10(int add, char flag);  // 0x00e7ce10 (stays in the slice: not this object's)

// ---- items of slice s00e7dd90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define B_s00e7_dd90(p,o) (*(uint8*)((char*)(p) + (o)))
extern char* gspCellGame_s00e7_dd90;             // 0x016b3c04
struct Registry_s00e7_dd90 {                       // thiscall members
    void* Get(int id);                  // 0x00b721d0
    void* Find(int id);                 // 0x00b72210
};
struct Manager {                        // thiscall members
    void Remove(int id);                // 0x00b72260
    void* Next(int* cursor);            // 0x00b72230
    int   GetPriority();                // 0x00e31100
};
static Registry_s00e7_dd90* registry() { return (Registry_s00e7_dd90*)(gspCellGame_s00e7_dd90 + 0x1c); }
static Manager*  manager()  { return (Manager*)(gspCellGame_s00e7_dd90 + 0x54); }
void  FUN_00e7d760(int a, float b);                             // 0x00e7d760
void  FUN_00e7a770(int a, int b, int c, int d, int e, float f); // 0x00e7a770
void  FUN_00e67d30(void* out, void* p, int a);                  // 0x00e67d30
char  FUN_00e56f20(int a);                                      // 0x00e56f20
void  FUN_00e69a90(int a, int b, float c, int d);               // 0x00e69a90
void  FUN_00e7db80(void);                                       // 0x00e7db80
char  FUN_00e59c10(void* self, float dt);                       // 0x00e59c10
char  FUN_00e7b540(void* self, int i, float dt);                 // 0x00e7b540
void  operator_delete__(void* p);                               // 0x00e59200-style delete
void  FUN_00e7d800(int a, int b, int c, int d, float e);        // 0x00e7d800
void  FUN_00e7add0(int a, int b, float c);                      // 0x00e7add0
void  FUN_00e59150(int a, float b);                             // 0x00e59150
void  FUN_00e7b410(int a, int b, int c);                        // 0x00e7b410
void  FUN_00e7df40(int a, int b, int c, float d);               // 0x00e7df40
void  FUN_00e7dd90(int a, int b, int c, int d, float e);        // 0x00e7dd90
void  FUN_00e7dbd0(int a, int b, int c, int d, float e);        // 0x00e7dbd0
void  FUN_00e7a160(int a);                                      // 0x00e7a160
void  FUN_00e7cbb0(int a, int b);                               // 0x00e7cbb0
void  FUN_00e50400(int a);                                      // 0x00e50400
void  FUN_00e50940(float a, int b);                             // 0x00e50940
void  FUN_00e72ac0(void);                                       // 0x00e72ac0
void  FUN_00e62440(void);                                       // 0x00e62440
void  sDigestion_End(int a, float b);                           // 0x00e7a4a0 (SP::sDigestion_End)
void  FUN_00e5ed20(int a, void* b);                             // 0x00e5ed20
void  FUN_00e794f0(int a, int b, float c, int d);               // 0x00e794f0
void  FUN_00e7cb90(void);                                       // 0x00e7cb90
void  FUN_00e59ab0(int a);                                      // 0x00e59ab0
void  FUN_00e7b9b0(int a, int b, float c);                      // 0x00e7b9b0
void  FUN_00e7b240(int a, float b);                             // 0x00e7b240
void  FUN_00e7d720(uint8 a);                                    // 0x00e7d720
void  FUN_00e567c0(void);                                       // 0x00e567c0
void  FUN_00e78de0(void);                                       // 0x00e78de0
void  FUN_00e53c20(void);                                       // 0x00e53c20
void  FUN_00e5daf0(void);                                       // 0x00e5daf0
void  FUN_00e56950(void);                                       // 0x00e56950
void  FUN_00e57d10(int a, int b, int c);                        // 0x00e57d10
void  sDoEnd(void* self, float dt, int a2, int a3);             // 0x00e7e130
void  sUpdateInteraction(void* self, float dt);                 // 0x00e7e6c0
// ---- items of slice s00e7dd90 end

// ---- items of slice s00e7f630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_16b3be0, g_16b3be4, g_16b3be8, g_16b3bec, g_16b3bf0;
extern int   g_16b3bf4, g_16b3bf8, g_16b3bfc;
extern float g_1550adc, g_1550ae0, g_1550ae4, g_1550aec, g_1550af0;
extern int   g_1550a84, g_1550ad8, g_166c004;
extern char* gspCellGame_s00e7_f630;      // 0x016b3c04
struct Manager_s00e7_f630 {                         // the +0x54 runtime object registry
    void* GetObj(int id);                // 0x00b721d0
    void* Next(int* cursor);             // 0x00b72230
    int   GetPriority();                 // 0x00e31100
    void  Destroy();                     // 0x00b720e0
    void  Reset();                       // 0x00b72110
};
static Manager_s00e7_f630* manager_s00e7_f630()      { return (Manager_s00e7_f630*)(gspCellGame_s00e7_f630 + 0x54); }
void  FUN_00e64a00(void);               // 0x00e64a00
void  FUN_00e82d40(void);               // 0x00e82d40
void* EffectsManager_s00e7_f630(void);             // 0x0067ddd0
typedef void (__thiscall *Vfn2i)(void*, int, int);
#define VTBL(o) (*(void***)(o))
// ---- items of slice s00e7f630 end

// ---- items of slice s00e80ba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char* gspCellGameMode;  // 0x016b3c0c  the active cell-mode object
typedef unsigned char  uint8_s00e8_0ba0;
typedef unsigned int   uint32_s00e8_0ba0;
#define B_s00e8_0ba0(p,o) (*(uint8_s00e8_0ba0*)((char*)(p) + (o)))
char  FUN_00e7f630(int msg, uint32_s00e8_0ba0 flags);   // 0x00e7f630
char  FUN_00e82cc0(void);              // 0x00e82cc0
char  FUN_00e82900(int msg, uint32_s00e8_0ba0 flags);   // 0x00e82900
struct LocaleMode {
    char RouteMessage(int msg, uint32_s00e8_0ba0 flags);   // 0x00697a50  (member of gspCellGameMode)
};
// ---- items of slice s00e80ba0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
char FUN_00e81120(int msg, uint8_s00e8_0ba0 flags);  // 0x00e81120 (stays in the slice: not this object's)

// ---- items of slice s0137d820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gFMax;            // 0x014851e8  ( 3.4028235e38)
extern float gFMin;            // 0x013f51ac  (-3.4028235e38)
struct Vec3_s0137_d820 { float x, y, z; };
struct cSPBoundingBox_s0137_d820 { Vec3_s0137_d820 min; Vec3_s0137_d820 max; };
extern cSPBoundingBox_s0137_d820 gCellGameExtents;            // 0x016b3c88
extern cSPBoundingBox_s0137_d820 gCellGameBackgroundExtents;  // 0x016b3ca0
// ---- items of slice s0137d820 end

// @ 0x00e4ecc0
int FUN_00e4ecc0()
{
    int base = (int)operator new(0x30580, "Simulator", 0, 0, 0, 0);
    float l10 = g_16b39b4;
    float lc = g_16b39b8;
    int l8 = 0, l4 = 0;
    FUN_00a7c3d0(2);
    char* p = (char*)(base + 4);
    int n = 0x5dc;
    do {
        FUN_00a7c350();
        *(float*)p = (g_16b3c94 - g_16b3c88) * l10 + g_16b3c88;
        *(float*)(p + 4) = (g_16b3c98 - g_16b3c8c) * lc + g_16b3c8c;
        *(float*)(p + 8) = 0.0f;
        char local[12];
        int* w = (int*)FUN_00e56d40(local, p);
        *(int*)(p + 0x4650) = w[0];
        *(int*)(p + 0x4654) = w[1];
        *(int*)(p + 0x4658) = w[2];
        p += 0xc;
        --n;
    } while (n != 0);
    operator_new__((void*)(base + 0x8ca4), 0, 18000);
    operator_new__((void*)(base + 0x4654), 0, 18000);
    operator_new__((void*)(base + 0x11944), 0, 18000);
    operator_new__((void*)(base + 0xd2f4), 0, 18000);
    operator_new__((void*)(base + 0x18e74), 0, 6000);
    *(int*)(base + 0x1bd54) = 0;
    *(int*)(base + 0x1bd58) = 0;
    *(int*)(base + 0x1bd5c) = -1;
    return base;
}

// @ 0x00e4ee30
int FUN_00e4ee30(int n)
{
    if (n == 1000) return 0x14;
    int i = 0;
    if (n >= 0) {
        int* p = g_1483c34;
        do { p += 7; ++i; } while (n >= *p);
    }
    return i - 1;
}

// @ 0x00e4ee60
int __fastcall SP_sGetSourceLevel(int, int n)
{
    if (n == 1000) return g_1483e60;
    int i = 0;
    if (n >= 0) {
        int* p = g_1483c34;
        do { p += 7; ++i; } while (n >= *p);
    }
    return g_1483c14[i * 7];
}

// @ 0x00e4ef60
int SP_sDestroyCell(int n)
{
    switch (n) {
    case 0: return 0;
    case 1: return 200;
    case 2: return 400;
    case 3: return 600;
    case 4: return 800;
    case 5: return 1000;
    }
    return 0;
}

// @ 0x00e4efb0
int FUN_00e4efb0(void* self, int arg)
{
    int r = (*(int(__thiscall**)(void*, int, int, int*, int*, int))((char*)Vt(self) + 0x30))
        (self, arg, 2, (int*)0x016b3c28, (int*)0x015a7c4c, 1);
    if (r) {
        (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(self) + 0x40))(self, r, 0, 1);
        FUN_00a04ce0(1);
        FUN_00a04d00(1);
    }
    return r;
}

// @ 0x00e4f550
void FUN_00e4f550()
{
    g_16b3bf0 = g_1550adc;
    g_16b3bec = g_1550af0;
    g_16b3be8 = g_1550aec;
    g_16b3be4 = g_1550ae0;
    g_16b3be0 = g_1550ae4;
    g_1550adc = 10.0f;
    g_1550af0 = 11.0f;
    g_1550aec = 90.0f;
    g_16b3bfc = g_166c004;
    g_1550ae0 = 1.0f;
    g_16b3bf8 = g_1550a84;
    g_16b3bf4 = g_1550ad8;
    g_166c004 = 1;
    g_1550a84 = 0;
    g_1550ad8 = 1;
    g_1550ae4 = 1.7f;
}

// @ 0x00e4f660
void FUN_00e4f660(int v)
{
    ((cTriggerMgr*)FUN_00b3d4d0())->FUN_00ad7e40((void*)v);
    *(char*)((char*)g_16b3c0c + 0x936) = (char)v;
}

// @ 0x00e4f6d0
int FUN_00e4f6d0(int* node, int a, int b, int** out, int* counter)
{
    if (a == b) {
        *(int*)*out = *counter;
        *out = *out + 1;
        ++*counter;
        return 1;
    }
    int total = 0;
    int n = 4;
    do {
        ++node;
        if (*node) total += FUN_00e4f6d0((int*)*node, a, b + 1, out, counter);
        --n;
    } while (n != 0);
    return total;
}

// @ 0x00e51820
void __stdcall FUN_00e51820(float* p)
{
  float local[3];
  local[0] = p[0];
  local[1] = p[1];
  local[2] = p[2];
  SP_FluidParticlesSampleVelMagnitude(*(void**)((char*)gCellGame_16b3c04 + 0x4108), local);
}

// @ 0x00e51870
float* __stdcall FUN_00e51870(float* out, float* in)
{
  float local[3];
  float tmp[3];
  local[0] = in[0];
  local[1] = in[1];
  local[2] = in[2];
  float* r = (float*)SP_FluidParticlesSampleVelocity(tmp, *(void**)((char*)gCellGame_16b3c04 + 0x4108), local);
  out[0] = r[0];
  out[1] = r[1];
  out[2] = r[2];
  return out;
}

// @ 0x00e518d0
void __stdcall FUN_00e518d0(float* out, int)
{
  float one = gOne_1485720;
  out[0] = one;
  out[1] = one;
  out[2] = one;
  out[3] = one;
}

// @ 0x00e51900
int __fastcall FUN_00e51900(char* self)
{
  int id = *(int*)(self + 0x248);
  if (id == 0) return 0;
  if (*(int*)(self + 0xfc) == 0) return 0;
  char* g = (char*)gCellGfx_16b3c08 + 0x168;
  char* rf = ((CellList*)g)->Find(id); int r = (int)rf;
  return *(int*)(r + 0x24);
}

// @ 0x00e51930
void FUN_00e51930(char* self)
{
  int id = *(int*)(self + 0x248);
  if (id != 0 && *(int*)(self + 0xfc) != 0) {
    char* g = (char*)gCellGfx_16b3c08 + 0x168;
    char* rf = ((CellList*)g)->Find(id); int r = (int)rf;
    int o = *(int*)(r + 0x24);
    if (o) {
      void* sub = *(void**)(o + 0x190);
      ((void(__thiscall*)(void*, int, int, int))Vt(sub)[0x40 / 4])(sub, o, 2, 1);
    }
  }
  int idx = *(int*)((char*)gCellGfx_16b3c08 + 0x16254);
  *(uint32_t*)((char*)gCellGfx_16b3c08 + 0x16214 + idx * 4) = *(uint32_t*)self;
  ++*(int*)((char*)gCellGfx_16b3c08 + 0x16254);
}

// @ 0x00e51990
void FUN_00e51990(char* ctx, char* vec)
{
  for (int i = 0; i < (*(int*)(vec + 0xb4) - *(int*)(vec + 0xb0)) >> 2; ++i) {
    void* o = *(void**)(*(int*)(vec + 0xb0) + i * 4);
    if (!((bool(__thiscall*)(void*))Vt(o)[0x10 / 4])(o)) {
      ((void(__thiscall*)(void*))Vt(o)[4 / 4])(o);
      *(uint32_t*)(*(int*)(vec + 0xb0) + i * 4) = 0;
      int b = *(int*)(vec + 0xb0);
      *(uint32_t*)(b + i * 4) = *(uint32_t*)(b + (((*(int*)(vec + 0xb4) - b) >> 2) - 1) * 4);
      *(int*)(vec + 0xb4) -= 4;
      --i;
    } else {
      ((void(__thiscall*)(void*, void*))Vt(o)[0x18 / 4])(o, ctx + 0x48);
    }
  }
}

// @ 0x00e51ee0
int FUN_00e51ee0(int p1, float p2, int p3, int p4, int p5, int p6, int p7, int p8, float p9, float p10, float* p11, float* p12, float* p13, int p14, uint8_t p15, int p16)
{
  void* g = (void*)((char*)gCellGame_16b3c04 + 0x54);
  CellList* list = (CellList*)((char*)gCellGame_16b3c04 + 0x54);
  int h = list->Head();
  char* o = list->Find(h);
  (void)g;
  *(int*)(o + 0x28) = p3;
  *(int*)(o + 0x24) = p1;
  *(int*)(o + 0x30) = p5;
  *(int*)(o + 0x2c) = p4;
  *(float*)(o + 0x1c) = p2;
  *(float*)(o + 0x20) = p2;
  *(int*)(o + 0x38) = p7;
  *(int*)(o + 0x34) = p6;
  *(int*)(o + 0x40) = p8;
  *(float*)(o + 0x3c) = p9;
  *(float*)(o + 0x44) = p10;
  float* v11 = p11 ? p11 : gVec_16b3c28;
  *(float*)(o + 0x48) = v11[0];
  *(float*)(o + 0x4c) = v11[1];
  *(float*)(o + 0x50) = v11[2];
  float* v12 = p12 ? p12 : gVec_16b3c28;
  *(float*)(o + 0x54) = v12[0];
  *(float*)(o + 0x58) = v12[1];
  *(float*)(o + 0x5c) = v12[2];
  float* v13 = p13 ? p13 : gVec_15a7c4c;
  *(float*)(o + 0x60) = v13[0];
  *(float*)(o + 0x64) = v13[1];
  *(float*)(o + 0x68) = v13[2];
  *(float*)(o + 0x6c) = v13[3];
  *(int*)(o + 0x70) = p14;
  *(uint8_t*)(o + 0x74) = p15;
  *(int*)(o + 0x78) = p16;
  *(int*)(o + 4) = 0;
  *(uint8_t*)(o + 8) = 0;
  return h;
}

// @ 0x00e52060
static void FUN_00e52060(cCellStats* self, int count, const cPart* parts, bool skipCurves)
{
    FUN_00e11e073e(self->counts, 0, 0x34);
    self->center = g_16b3c28;
    self->maxDist = 0.0f;

    float minY = self->center.y;
    float maxY = self->center.y;
    Vec3 minPt = self->center;
    Vec3 maxPt = self->center;
    float nearestY = 10000.0f;
    int idxA = -1, idxB = -1, idxC = -1, idxD = -1;
    self->nearestIdx = -1;
    int i = 0;
    for (i = 0; i < count; ++i) {
        const cPart& p = parts[i];
        if (p.active == 1) {
            float r = p.radius;
            if (p.pos.y + r > maxY) {
                maxPt = p.pos;
                maxY = r + maxPt.y;
            } else if (p.pos.y - r < minY) {
                minPt = p.pos;
                minY = minPt.y - r;
            }
        }
        if (p.type == 12 && p.pos.y < nearestY) {
            nearestY = p.pos.y;
            self->nearestIdx = i;
        }
    }
    self->center.x = (minPt.x + maxPt.x) * 0.5f;
    self->center.y = (minY + maxY) * 0.5f;
    self->center.z = (minPt.z + maxPt.z) * 0.5f;

    int negType = 0;
    for (i = 0; i < count; ++i) {
        const cPart& p = parts[i];
        int* counter = &self->counts[p.type];
        if (p.active == 1) {
            *counter += 2;
            if (p.pos.y < 0.0f) negType = p.type;
            if (p.type == 5) {
                if (p.pos.y > 0.0f) idxB = i;
                else idxD = i;
            }
        } else {
            *counter += 1;
            if (!(p.pos.y > 1000.0f) && p.type == 5) {
                if (p.pos.x > 0.0f) idxA = i;
                else idxC = i;
            }
        }
        float dx = self->center.x - p.pos.x;
        float dy = self->center.y - p.pos.y;
        float dz = self->center.z - p.pos.z;
        float d = sqrtf(dy * dy + (dz * dz + dx * dx)) + p.radius;
        self->maxDist = MaxF(self->maxDist, d);
    }

    self->numPicks = 0;
    if (idxB != -1) self->picks[self->numPicks++] = idxB;
    if (idxA != -1) self->picks[self->numPicks++] = idxA;
    if (idxC != -1) self->picks[self->numPicks++] = idxC;
    if (self->numPicks == 0 && idxD != -1) self->picks[self->numPicks++] = idxD;

    int s = self->counts[10] / 2 * 2 + self->counts[9] / 2 / 2 + self->counts[8] / 2;
    self->val1284 = MinI(s, 10);
    int t = 0;
    if ((negType == 2 || negType == 4 || negType == 7) && self->val1284 != 0) {
        int u = self->counts[6] / 2 * 2 + self->counts[7] / 2 + self->counts[5] / 2 + 1;
        t = MinI(u, 10);
    }
    self->val1288 = t;

    if (skipCurves) return;

    self->flag1250 = (self->counts[2] > 0 || self->counts[4] > 0);
    self->flag1251 = (self->counts[3] > 0 || self->counts[4] > 0);
    self->flag1248 = self->counts[7] > 0;
    self->val124c = FUN_00e837c0(0x77540c34, (float)self->counts[11]);

    cGuard16 g1;
    const char* cfg = (const char*)FUN_00e4ce40(&g1);
    if (self->counts[10] != 0) {
        self->val1258 = FUN_00e837c0(0x2c574746,
            (float)self->counts[9] * *(const float*)(cfg + 0x78) +
            (float)self->counts[8] * *(const float*)(cfg + 0x74) + (float)self->counts[10]);
    } else if (self->counts[9] != 0) {
        self->val1258 = FUN_00e837c0(0xbbab1bf5,
            (float)self->counts[8] * *(const float*)(cfg + 0x80) + (float)self->counts[9]);
    } else if (self->counts[8] != 0) {
        self->val1258 = FUN_00e837c0(0x2ef68471,
            *(const float*)(cfg + 0x7c) * g_1485378 + (float)self->counts[8]);
    } else {
        self->val1258 = 0.0f;
    }
    self->mask1254 = (self->counts[10] > 0 ? 4 : 0) | (self->counts[8] > 0 ? 2 : 0) |
                     (self->counts[9] > 0 ? 1 : 0);
    if (self->mask1254 == 0) {
        self->mask1254 = 1;
        cGuard16 g2;
        const char* cfg2 = (const char*)FUN_00e4ce40(&g2);
        self->val1258 = *(const float*)(cfg2 + 0x90);
    }
    self->val1260 = FUN_00e837c0(0xe5015d0c, (float)self->counts[6]);
    self->val125c = FUN_00e837c0(g_16b3c84, (float)self->counts[6]);
    self->val1264 = 0.0f;
    self->val1268 = FUN_00e837c0(0x03ab589e, (float)self->counts[6]);
    float v = FUN_00e837c0(0xaee2835e, (float)self->counts[6]);
    self->val126c = RoundToInt(v);
    self->val1270 = FUN_00e837c0(0x92baae19, (float)self->counts[5]);
}
#pragma auto_inline(on)

// @ 0x00e54b80
void FUN_00e54b80(void* arg)
{
    unsigned local18 = 0xffffffff, local14 = 0xffffffff;
    void* s = FUN_0067dd40();
    (*(void(__thiscall**)(void*, int, void*, int, void*))((char*)Vt(s) + 0xa8))(s, 0, &local14, 0, &local14);
    FUN_007c4be0((void*)0x016b42b8, &local18, 1);
    int a = *(int*)((char*)arg + 4);
    int b = *(int*)((char*)arg + 8);
    int c = *(int*)((char*)arg + 0xc);
    unsigned v3 = (unsigned)c;
    int v4 = (int)(unsigned)a;
    unsigned v5 = (unsigned)b;
    void* o = *(void**)((char*)g_16b3c08 + 0x161c0);
    void* r = (*(void*(__thiscall**)(void*))((char*)Vt(o) + 0x13c))(o);
    (*(void(__thiscall**)(void*, int, int, unsigned*, void*))((char*)Vt(r) + 0xc))(r, v4, 0xd, &v5, arg);
    o = *(void**)((char*)g_16b3c08 + 0x161c4);
    (*(void(__thiscall**)(void*, int, int, unsigned*, void*))((char*)Vt(o) + 0xc))(o, v4, 0xd, &v5, arg);
    o = *(void**)((char*)g_16b3c08 + 0x161b8);
    r = (*(void*(__thiscall**)(void*))((char*)Vt(o) + 0xa0))(o);
    (*(void(__thiscall**)(void*, int, int, unsigned*, void*))((char*)Vt(r) + 0xc))(r, v4, 0x12, &v3, arg);
    FUN_007c3c50(6);
}

// @ 0x00e54c70
void FUN_00e54c70(void* a, void* b, void* c, void* d)
{
    void* f;
    f = *(void**)((char*)g_16b3c08 + 0x161cc);
    void* o1 = (*(void*(__thiscall**)(void*))((char*)Vt(f) + 0x13c))(f);
    (*(void(__thiscall**)(void*, void*, void*, void*, void*))((char*)Vt(o1) + 0xc))(o1, a, b, c, d);
    f = *(void**)((char*)g_16b3c08 + 0x161d0);
    (*(void(__thiscall**)(void*, void*, void*, void*, void*))((char*)Vt(f) + 0xc))(f, a, b, c, d);
    f = *(void**)((char*)g_16b3c08 + 0x161a8);
    void* o2 = (*(void*(__thiscall**)(void*))((char*)Vt(f) + 0x13c))(f);
    (*(void(__thiscall**)(void*, void*, void*, void*, void*))((char*)Vt(o2) + 0xc))(o2, a, b, c, d);
    f = *(void**)((char*)g_16b3c08 + 0x161a4);
    void* o3 = (*(void*(__thiscall**)(void*))((char*)Vt(f) + 0xa0))(f);
    (*(void(__thiscall**)(void*, void*, int, void*, void*))((char*)Vt(o3) + 0xc))(o3, a, 0x12, c, d);
}

// @ 0x00e54d10
void FUN_00e54d10()
{
    void* o = *(void**)((char*)g_16b3c08 + 0x161d8);
    void* r = (*(void*(__thiscall**)(void*))((char*)Vt(o) + 0xa0))(o);
    (*(void(__thiscall**)(void*))((char*)Vt(r) + 0xc))(r);
}

// @ 0x00e552f0
namespace SP
{
class cCellMode { public:
    char pad0[9];
    char f9, fa;
    int Activate();
};
int cCellMode::Activate()
{
    f9 = 0;
    fa = 0;
    *(char*)((char*)g_16b3c04 + 0x5169) = 0;
    *(char*)((char*)g_16b3c0c + 0x937) = 0;
    cLocalInputState_Reset(g_16b3c0c);
    SP_sActivateGfx();
    FUN_00e4f550_();
    void* em = SP_EffectsManager();
    (*(void(__thiscall**)(void*, int, int))((char*)Vt(em) + 0x98))(em, 7, 1);
    if (g_16b3c00) {
        g_16b3c00 = 0;
        void* c = FUN_00b3d410(0, (void*)0x01654c00, 0);
        FUN_00e3e350(0, (void*)0x01654c00, 0);
        (void)c;
    }
    void* lm = SPUIHelpers_GetLayoutManager();
    if (FUN_00810760(0x614de4c)) FUN_00810660(0x614de4c, 0);
    void* mcp = FUN_00b3d400();
    if (mcp) cUIMissionCardPanel_Refresh(FUN_00b3d400());
    (void)lm;
    return 1;
}
}

// @ 0x00e558c0
bool FUN_00e558c0(float* p1, float* p2, float* p3, float* p4, float p5, float p6, float p7, int p8, float p9, float* out)
{
    if (p5 == 0.0f) {
        out[0] = g_16b3c28_s00e5_58c0; out[1] = g_16b3c2c; out[2] = g_16b3c30;
        return false;
    }
    float dx = p4[0] - p2[0], dy = p4[1] - p2[1], dz = p4[2] - p2[2];
    float d2 = dy * dy + dx * dx + dz * dz;
    float dist = sqrtf(d2);
    float vx, vy, vz;
    if (1.0f <= dist) { vx = p1[0]; vy = p1[1]; vz = p1[2]; }
    else {
        float inv = 1.0f / sqrtf(d2 + 1e-08f);
        vx = (p1[0] - inv * dx) * dist + inv * dx;
        vy = (p1[1] - inv * dy) * dist + inv * dy;
        vz = (p1[2] - inv * dz) * dist + inv * dz;
    }
    bool ok = true;
    if (1.5258789e-05f < p7) {
        float s = (float)FUN_00e55770(p8);
        vx *= s; vy *= s; vz *= s;
        if (s < 1.5258789e-05f) ok = false;
    }
    float* vp = (float*)SP_FluidParticlesSampleVelocity(&dx, (void*)(*(int*)(g_CellGame + 0x4108)), p2);
    float ex = p3[0] - vp[0], ey = p3[1] - vp[1], ez = p3[2] - vp[2];
    if (sqrtf(ey * ey + (ez * ez + ex * ex)) <= dist || (char)p8 == 0) {
        float t = FUN_00e513d0(0x3f000000, 0x40400000, dist, 0, 0x3f800000);
        dist = t;
        vp = (float*)SP_FluidParticlesSampleVelocity(&dx, (void*)(*(int*)(g_CellGame + 0x4108)), p2);
        ex = ((vx * p5) * dist) * p6 + vp[0];
        ez = vp[2] + ((vz * p5) * dist) * p6;
        ey = vp[1] + ((vy * p5) * dist) * p6;
    } else { ex = -ex; ey = -ey; ez = -ez; }
    float c1 = p3[1], c2 = p3[2], m = 1.0f;
    if (!ok && (char)p8 != 0) m = 10.0f;
    out[0] = ((ex - p3[0]) * p9) * m;
    out[1] = ((ey - c1) * p9) * m;
    out[2] = ((ez - c2) * p9) * m;
    return ok;
}

// @ 0x00e55c40
void FUN_00e55c40(float* p1, float* p2, float* p3, float* p4, float p5, float p6, float p7, int p8, float p9, float* out)
{
    if (p5 == 0.0f) {
        out[0] = g_16b3c28_s00e5_58c0; out[1] = g_16b3c2c; out[2] = g_16b3c30;
        return;
    }
    float dy = p4[1] - p2[1], dz = p4[2] - p2[2], dx = p4[0] - p2[0];
    float d2 = (dz * dz + dy * dy) + dx * dx;
    float dist = sqrtf(d2);
    float vx, vy, vz;
    if (1.0f <= dist) { vx = p1[0]; vy = p1[1]; vz = p1[2]; }
    else {
        float inv = 1.0f / sqrtf(d2 + 1e-08f);
        vx = (p1[0] - inv * dx) * dist + inv * dx;
        vy = (p1[1] - dy * inv) * dist + dy * inv;
        vz = (p1[2] - dz * inv) * dist + dz * inv;
    }
    if (1.5258789e-05f < p7) {
        float s = (float)FUN_00e55770(p8);
        vx *= s; vy *= s; vz *= s;
    }
    float* vp = (float*)SP_FluidParticlesSampleVelocity(&dx, (void*)(*(int*)(g_CellGame + 0x4108)), p2);
    float ex = p3[0] - vp[0], ey = p3[1] - vp[1], ez = p3[2] - vp[2];
    if (sqrtf(ey * ey + (ez * ez + ex * ex)) <= dist) {
        float t = FUN_00e513d0(0x3f000000, 0x40400000, dist, 0x3f000000, 0x3f800000);
        dist = t;
        vp = (float*)SP_FluidParticlesSampleVelocity(&dx, (void*)(*(int*)(g_CellGame + 0x4108)), p2);
        ex = vp[0] + ((vx * dist) * p5) * p6;
        ey = vp[1] + ((vy * dist) * p5) * p6;
        ez = vp[2] + ((vz * dist) * p5) * p6;
    } else { ex = -ex; ey = -ey; ez = -ez; }
    float c1 = p3[1], c2 = p3[2];
    out[0] = (ex - p3[0]) * p9;
    out[1] = (ey - c1) * p9;
    out[2] = (ez - c2) * p9;
}

// @ 0x00e55f60
void FUN_00e55f60(float* p1, float* p2, float* p3, float p4, int p5, float* out)
{
    if (p4 == 0.0f) {
        out[0] = g_16b3c28_s00e5_58c0; out[1] = g_16b3c2c; out[2] = g_16b3c30;
        return;
    }
    float dy = p3[1] - p1[1], dz = p3[2] - p1[2], dx = p3[0] - p1[0];
    float d2 = (dy * dy + dz * dz) + dx * dx;
    float inv = 1.0f / sqrtf(d2 + 1e-08f);
    float dlen = sqrtf(d2);
    float m = (p4 <= dlen) ? p4 : dlen;
    float ux = m * (inv * dx), uy = m * (dy * inv), uz = m * (inv * dz);
    float* vp = (float*)SP_FluidParticlesSampleVelocity(0, (void*)(*(int*)(g_CellGame + 0x4108)), p1);
    out[0] = (vp[0] + ux) - p2[0];
    out[1] = (vp[1] + uy) - p2[1];
    out[2] = (vp[2] + uz) - p2[2];
}

// @ 0x00e560d0
void FUN_00e560d0(int self, float* v)
{
    float sc, a, b, c;
    if (*(int*)(self + 0x248) == 0 || *(int*)(self + 0x250) < 2) {
        sc = *(float*)(self + 0xbc); a = v[1]; b = v[2]; c = sc * v[0];
    } else {
        int i = 0;
        if (0 < *(int*)(self + 0x250)) {
            int base = *(int*)(g_CellGame + 0x4108);
            int* idx = (int*)(self + 0x254);
            do {
                sc = *(float*)(self + 0xbc); a = v[1]; b = v[2];
                float* p = (float*)(base + 0x4654 + *idx * 0xc);
                p[0] = *(float*)(base + 0x4654 + *idx * 0xc) + sc * v[0];
                p[1] = p[1] + a * sc;
                p[2] = p[2] + b * sc;
                ++i; ++idx;
            } while (i < *(int*)(self + 0x250));
        }
        sc = *(float*)(self + 0xbc); a = v[1]; b = v[2]; c = sc * v[0];
    }
    *(float*)(self + 0x98) = b * sc + *(float*)(self + 0x98);
    *(float*)(self + 0x94) = a * sc + *(float*)(self + 0x94);
    *(float*)(self + 0x90) = *(float*)(self + 0x90) + c;
}

// @ 0x00e56200
double FUN_00e56200(int self)
{
    int k = *(int*)(self + 0x1b0);
    if (0x11 < k && (k < 0x15 || k == 0x30)) {
        if (*(int*)(self + 0x248) != 0 && *(int*)(self + 0xfc) != 0) {
            int cell = (int)FUN_00b72210(*(int*)(self + 0x248));
            if (*(int*)(cell + 0x24) != 0) {
                float out;
                if (FUN_00e83380(*(void**)(cell + 0x24), 0x98c942b4, &out) == false) {
                    FUN_00743b50();
                    int o = (int)FUN_00e4ce40(&self);
                    float f = *(float*)(o + 0x108);
                    FUN_00e82130();
                    return (double)f;
                }
                *(float*)(self + 0x1c0) = out * 100.0f;
                return (double)(out * 100.0f);
            }
        }
        FUN_00743b50();
        int o = (int)FUN_00e4ce40(&self);
        float f = *(float*)(o + 0x108);
        FUN_00e82130();
        return (double)f;
    }
    return (double)*(float*)(self + 0x1c0);
}

// @ 0x00e56300
double FUN_00e56300(int self)
{
    int k = *(int*)(self + 0x1b0);
    if (k < 0x12 || (0x14 < k && k != 0x30))
        return (double)*(float*)(self + 0x1c0);
    if (*(int*)(self + 0x248) != 0 && *(int*)(self + 0xfc) != 0) {
        int cell = (int)FUN_00b72210(*(int*)(self + 0x248));
        int q = *(int*)(cell + 0x24);
        if (q != 0 && *(int*)(q + 0x54) != 0) {
            float out;
            if (FUN_00e83380((void*)q, 0x98c942b4, &out) == false)
                return (double)FUN_00e503a0(2);
            *(float*)(self + 0x1c0) = out * 20.0f;
            return (double)(out * 20.0f);
        }
    }
    FUN_00743b50();
    int o = (int)FUN_00e4ce40(&self);
    float f = *(float*)(o + 0x104);
    FUN_00e82130();
    return (double)f;
}

// @ 0x00e563e0
float FUN_00e563e0(void* obj)
{
    float f = g_1485720;
    int idx = *(int*)((char*)obj + 0x358);
    if (idx != -1) {
        int lvl = SP_sGetSourceLevel();
        f = g_1483bd0[idx] / g_1483bd0[lvl];
    }
    return FUN_00e837c0(0x7ac2e49f, f);
}

// @ 0x00e56450
double FUN_00e56450(int self)
{
    int idx = *(int*)(self + 0x358);
    if (idx != -1) {
        int lvl = SP_sGetSourceLevel();
        float r = g_1483bd0[idx] / g_1483bd0[lvl];
        if (r <= 0.5f) return 4.0;
        if (r <= 1.0f) return 4.0 - ((double)r - 0.5) * 4.0;
        if (r <= 2.0f) return 2.0;
        if (r <= 4.0f) return 2.0 - ((double)r - 2.0) * 0.5;
    }
    return 1.0;
}

// @ 0x00e56510
float FUN_00e56510(SomeObj* obj)
{
    int k = *(int*)((char*)obj + 0x18c);
    if (k == 0x30 || k == 0x12 || k == 0x14 || k == 0x13)
        return 1.0f;
    void* h = obj->Lookup();
    if (h) {
        float out;
        if (FUN_00e83380(h, 0x98c942b5, &out))
            return out;
    }
    return 1.0f;
}

// @ 0x00e56560
void FUN_00e56560(float* out, int* self)
{
    if (self[0x92] != 0 && self[0x3f] != 0) {
        int cell = (int)FUN_00b72210(self[0x92]);
        if (*(int*)(cell + 0x24) != 0) {
            float q = 0.0f;
            FUN_00e83380(*(void**)(cell + 0x24), 0x98c942b6, &q);
            float s = sqrtf(*(float*)((char*)self + 0xbc));
            float a = (g_15a853c * (q * *(float*)((char*)self + 0x1a0))) * s;
            float b = (g_15a853c * (*(float*)((char*)self + 0x1a4) * q)) * s;
            float c = (g_15a853c * (*(float*)((char*)self + 0x1a8) * q)) * s;
            if (*self == *(int*)(g_CellGame + 0x411c)) {
                unsigned u = FUN_00e4ee30(*(int*)(*(int*)(g_CellGame + 0x5190) + 0x1c));
                if (u & 1) { a *= g_14854c8; b *= g_14854c8; c *= g_14854c8; }
            }
            out[0] = a; out[1] = b; out[2] = c;
            return;
        }
    }
    out[0] = g_16b3c28_s00e5_58c0; out[1] = g_16b3c2c; out[2] = g_16b3c30;
}

// @ 0x00e56690
void FUN_00e56690()
{
    *(uint8_t*)(g_16b3c0c_s00e5_58c0 + 0x938) = 0;
    FUN_00e53660(2, 0);
    uint8_t* p = *(uint8_t**)(g_CellGame + 0x5190) + 0x80;
    *(int*)(p + 0) = 1;
    *(int*)(p + 4) = 0;
    *(int*)(p + 8) = 0;
    *(float*)(p + 0xc) = 0.0f;
}

// @ 0x00e566e0
void FUN_00e566e0()
{
    *(uint8_t*)(g_16b3c0c_s00e5_58c0 + 0x938) = 0;
    FUN_00e53660(2, 0);
}

// @ 0x00e56700
double FUN_00e56700(int data, int count, float t)
{
    if (0 < count - 1) {
        int i = 0;
        do {
            float hi = *(float*)(data + 8 + i * 8);
            if (t < hi) {
                float lo = *(float*)(data + 4 + i * 8);
                float v2 = *(float*)(data + 0xc + i * 8);
                float u = FUN_01041cd0(*(int*)(data + i * 8), hi, t);
                float cl = 0.0f;
                if (0.0f <= u) cl = u;
                if (1.0f <= cl) cl = 1.0f;
                return ((double)v2 - (double)lo) * (double)cl + (double)lo;
            }
            ++i;
        } while (i < count - 1);
    }
    return (double)*(float*)(data + -4 + count * 8);
}

// @ 0x00e567c0
void FUN_00e567c0()
{
    cSPUILayout_s00e5_58c0* layout = *(cSPUILayout_s00e5_58c0**)(g_16b3c0c_s00e5_58c0 + 0x90);
    IWindow* w = layout->FindWindowByID(0x5af4ae5, 1);
    if (w) w->v31(1, 0);
    uint8_t* p = *(uint8_t**)(g_CellGame + 0x5190) + 0x80;
    g_16b3c10 = 0;
    *(int*)(p + 0) = 1;
    *(int*)(p + 4) = 0;
    *(int*)(p + 8) = 0;
    *(float*)(p + 0xc) = 0.0f;
}

// @ 0x00e577a0
void FUN_00e577a0(int param_1, float* param_2, float* param_3, float* param_4, float* param_5)
{
  float d[3];
  if (*param_2 > 0.0f) {
    d[0] = kf15a7c28; d[1] = kf15a7c2c; d[2] = kf15a7c30;
  } else {
    d[0] = -kf15a7c28; d[1] = -kf15a7c2c; d[2] = -kf15a7c30;
  }
  param_4[0] = param_3[0] + d[0] * kf14007f4;
  param_4[1] = param_3[1] + d[1] * kf14007f4;
  param_4[2] = param_3[2] + d[2] * kf14007f4;
  param_5[0] = param_3[0] + d[0] * kf13ebc5c;
  param_5[1] = param_3[1] + d[1] * kf13ebc5c;
  param_5[2] = param_3[2] + d[2] * kf13ebc5c;
}

// @ 0x00e57890
void FUN_00e57890(char* param_1, char* param_2)
{
  int mode = *(int*)(*(int*)((char*)gspCellGame + 0x5190) + 0x7c);
  char* sel;
  switch (mode) {
    case 0:
      sel = param_2 + 0x248;
      if (*(int*)sel == -1) sel = param_2 + 0xe0;
      break;
    case 2:
      sel = param_2 + 0x194;
      if (*(int*)sel == -1) sel = param_2 + 0xe0;
      break;
    case 1:
      sel = param_2 + 0xe0;
      break;
    default:
      sel = param_2 + 0xe0;
      break;
  }
  if (0.0f < *(float*)(sel + 0x88)) {
    *(float*)(param_1 + 0x230) = 0.0f;
    char* r = FUN_00e52910((int)param_2);
    *(float*)(param_1 + 0x224) = *(float*)(r + 0x88);
    *(float*)(param_1 + 0x238) = 0.0f;
  }
}

// @ 0x00e57910
static void FUN_00e57910(char* self)
{
  char local[4];
  ((ObjHolder*)local)->Init();
  char* obj = (char*)FUN_00e823a0(*(int*)(self + 0x108), local);
  int mode = *(int*)(*(int*)((char*)gspCellGame + 0x5190) + 0x7c);
  char* sel;
  if (mode == 0) {
    sel = obj + 0x248;
  } else if (mode == 2) {
    sel = obj + 0x194;
  } else {
    sel = obj + 0xe0;
  }
  if (mode == 0 || mode == 2) {
    if (*(int*)sel == -1) sel = obj + 0xe0;
  }
  switch (*(int*)sel) {
    case 0x1006:
      FUN_00e57890(self, obj);
      break;
  }
  ((ObjHolder*)local)->Cleanup();
}

// @ 0x00e579c0
char FUN_00e579c0(unsigned int id, int state)
{
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  *(int*)(p + 0x170) = state;
  int e = *(int*)(p + 0x18c);
  *(char*)(p + 0x17e) = 1;
  if (e == 0 || (unsigned)(e - 0x15) <= 1) *(int*)(p + 0x18c) = 0x15;
  return 1;
}

// @ 0x00e57a10
void FUN_00e57a10(char* param_1, int param_2)
{
  *(int*)(param_1 + 0x174) = param_2;
  if (*(int*)(param_1 + 0x248) == 0) return;
  if (*(int*)(param_1 + 0xfc) == 0) return;
  ResMap* map = (ResMap*)(gspCellGfx + 0x168);
  void* q = map->Find(*(unsigned int*)(param_1 + 0x248));
  char* s = *(char**)((char*)q + 0x24);
  if (s != 0) *(int*)(s + 0x174) = FUN_00e83470(s, param_2);
}

// @ 0x00e57a60
char FUN_00e57a60(unsigned int id, unsigned int id2, int a2, int state, float* vec)
{
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  CellPool* pool2 = &gspCellGame->mCells;
  if ((char*)pool2->Get(id2) == 0) return 0;
  *(char*)(p + 0x178) = 1;
  *(char*)(p + 0x17f) = 1;
  switch (*(int*)(p + 0x18c)) {
    case 0: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16:
    case 0x2f: case 0x30: case 0x32: case 0x33:
      *(int*)(p + 0x18c) = state;
      float v0 = vec[0];
      float v1 = vec[1];
      float v2 = vec[2];
      *(float*)(p + 0x1a0) = -v0;
      *(float*)(p + 0x1a4) = -v1;
      *(float*)(p + 0x1a8) = -v2;
      FUN_00e57a10(p, a2);
  }
  return 1;
}

// @ 0x00e57b50
char FUN_00e57b50(unsigned int id, unsigned int id2, int state, float* vec)
{
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  *(char*)(p + 0x178) = 1;
  *(char*)(p + 0x17f) = 1;
  switch (*(int*)(p + 0x18c)) {
    case 0: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16:
    case 0x32: case 0x33:
      *(int*)(p + 0x18c) = state;
      float v0 = vec[0];
      float v1 = vec[1];
      float v2 = vec[2];
      *(float*)(p + 0x1a0) = -v0;
      *(float*)(p + 0x1a4) = -v1;
      *(float*)(p + 0x1a8) = -v2;
      FUN_00e57a10(p, id2);
  }
  return 1;
}

// @ 0x00e57c30
char FUN_00e57c30(unsigned int id, unsigned int id2, int state)
{
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  CellPool* pool2 = &gspCellGame->mCells;
  if ((char*)pool2->Get(id2) == 0) return 0;
  int e = *(int*)(p + 0x18c);
  *(char*)(p + 0x17a) = 1;
  if (e == 0 || e == 0x12 || e == 0x30) *(int*)(p + 0x18c) = state;
  return 1;
}

// @ 0x00e57c90
char FUN_00e57c90(unsigned int id, int state)
{
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  *(int*)(p + 0x170) = state;
  int e = *(int*)(p + 0x18c);
  *(char*)(p + 0x17e) = 1;
  if (e == 0 || e == 0x16) *(int*)(p + 0x18c) = 0x16;
  return 1;
}

// @ 0x00e57ce0
char FUN_00e57ce0(int cell, void* p)
{
  if (FUN_00e57340(cell) == 1) return 0;
  if (*(int*)(cell + 0xfc) == 0) return 0;
  return FUN_00e52960(p) != 0;
}

// @ 0x00e57d10
void FUN_00e57d10(unsigned int id, float a, float b)
{
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return;
  float ra = a * kf1488874;
  float r = (float)sMathRandom.Next((double)ra) * ra;
  float v = (ra <= r) ? ra : ((0.0f <= r) ? ra : 0.0f);
  *(float*)(p + 0x234) = v + a;
  float rb = b * kf1488874;
  float r2 = (float)sMathRandom.Next((double)rb) * rb;
  float v2 = (r2 < rb) ? ((r2 < 0.0f) ? 0.0f : rb) : rb;
  *(float*)(p + 0x224) = v2 + b;
}

// @ 0x00e57dc0
char FUN_00e57dc0(unsigned int id)
{
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(id);
  if (p == 0) return 0;
  int e = *(int*)(p + 0x18c);
  *(char*)(p + 0x180) = 1;
  if (e == 0 || e == 0x12 || e == 0x30) *(int*)(p + 0x18c) = 0x2a;
  return 1;
}

// @ 0x00e57e10
namespace SP {
void sDropsWhichParts(unsigned int param_1, bool *const param_2)
{
  CellPool* pool = &gspCellGame->mCells;
  char* p = (char*)pool->Get(param_1);
  if (p == 0) return;
  void* mode = *(void**)((char*)gspCellGame + 0x5190);
  int lvl = FUN_00e4ee60(gspCellGame, *(void**)((char*)mode + 0x1c));
  int local[3];
  local[0] = 0;
  local[1] = lvl - 1;
  local[2] = 0x13;
  int* pi = local;
  if (lvl - 1 >= 0) pi = local + 1;
  if (*pi > 0x13) pi = local + 2;
  if (*(int*)(p + 0x358) != *pi) {
    char local2[4];
    ((ObjHolder*)local2)->Init();
    char* q = (char*)FUN_00e823a0(*(int*)(p + 0x108), local2);
    int s = *(int*)(q + 0xd4);
    if (s != 0) FUN_00e50680(s, param_2);
    ((ObjHolder*)local2)->Cleanup();
  }
}
}  // namespace SP

// @ 0x00e57ec0
void FUN_00e57ec0(int param_1)
{
  for (int i = 2; i < 0xb; ++i) {
    if (i == 3 || i == 9) continue;
    cSPUILayout_s00e5_77a0* layout = *(cSPUILayout_s00e5_77a0**)(param_1 + 0x34);
    IWindow_s00e5_77a0* w = layout->FindWindowByID((unsigned)(i + 0x93310500), 1);
    if (w != 0) w->SetFlag(1, 0);
  }
  int buf[4];
  buf[0] = 0; buf[1] = 0; buf[2] = 0; buf[3] = 0;
  SP::sDropsWhichParts(*(int*)(param_1 + 4), (bool*)buf);
  int n = 0;
  int off = 0x34;
  unsigned id = 0x93310500;
  do {
    if (*(char*)((char*)buf + (id - 0x93310500)) != 0 &&
        *(int*)(off + *(int*)((char*)gspCellGame + 0x5190)) == 0) {
      if (n >= 2) return;
      cSPUILayout_s00e5_77a0* layout = *(cSPUILayout_s00e5_77a0**)(param_1 + 0x34);
      IWindow_s00e5_77a0* w1 = layout->FindWindowByID(id, 1);
      cSPUILayout_s00e5_77a0* layout2 = *(cSPUILayout_s00e5_77a0**)(param_1 + 0x34);
      IWindow_s00e5_77a0* w2 = layout2->FindWindowByID((unsigned)(n + 0x93310400), 1);
      w1->SetArea(w2->GetArea());
      w1->SetFlag(1, 1);
      ++n;
    }
    off += 4;
    ++id;
  } while ((int)(id + 0x6ccefb00) < 0xd);
}

// @ 0x00e57fd0
void FUN_00e57fd0(int param_1)
{
  if (!(*(float*)(param_1 + 0x2c) > 0.0f) || *(char*)(param_1 + 0x30) == 0) {
    goto hide;
  }
  if (ConfigManager()->Query(0x679b833) != 0) goto hide;
  FUN_00e57ec0(param_1);
  {
    cSPUILayout_s00e5_77a0* layout = *(cSPUILayout_s00e5_77a0**)(param_1 + 0x34);
    IWindow_s00e5_77a0* w = layout->FindWindowByID(0x933103ea, 1);
    if (w != 0) {
      w->SetFlag(1, 1);
      unsigned c = ((unsigned)(int)(*(float*)(param_1 + 0x2c) * kf13f2100) << 0x18) | 0xffffff;
      w->SetColor(c);
    }
  }
  goto after;
hide:
  {
    cSPUILayout_s00e5_77a0* layout = *(cSPUILayout_s00e5_77a0**)(param_1 + 0x34);
    IWindow_s00e5_77a0* w = layout->FindWindowByID(0x933103ea, 1);
    if (w != 0) w->SetFlag(1, 0);
  }
after:
  {
    cSPUILayout_s00e5_77a0* layout = *(cSPUILayout_s00e5_77a0**)(param_1 + 0x34);
    IWindow_s00e5_77a0* w = layout->FindWindowByID(0x93310e4a, 1);
    if (w != 0) {
      unsigned c = ((unsigned)(int)(*(float*)(param_1 + 0x20) * kf13f2100) << 0x18) | 0xffffff;
      w->SetColor(c);
    }
  }
  IWindow_s00e5_77a0* bar = ((cSPUILayout_s00e5_77a0*)*(cSPUILayout_s00e5_77a0**)(param_1 + 0x34))->FindWindowByID(0x26e0df3, 1);
  IWindow_s00e5_77a0* f1;
  IWindow_s00e5_77a0* f2;
  {
    char* cell = (char*)((CellPool*)&gspCellGame->mCells)->Get(*(unsigned int*)(param_1 + 4));
    if (cell != 0 && FUN_00e57340((int)cell) == 4) {
      f1 = ((cSPUILayout_s00e5_77a0*)*(cSPUILayout_s00e5_77a0**)(param_1 + 0x34))->FindWindowByID(0x26e0df4, 1);
      f2 = ((cSPUILayout_s00e5_77a0*)*(cSPUILayout_s00e5_77a0**)(param_1 + 0x34))->FindWindowByID(0x26e0df0, 1);
    } else {
      f1 = ((cSPUILayout_s00e5_77a0*)*(cSPUILayout_s00e5_77a0**)(param_1 + 0x34))->FindWindowByID(0x26e0df0, 1);
      f2 = ((cSPUILayout_s00e5_77a0*)*(cSPUILayout_s00e5_77a0**)(param_1 + 0x34))->FindWindowByID(0x26e0df4, 1);
    }
  }
  float fv = *(float*)(param_1 + 8);
  if (f1 != 0) {
    float r[4];
    float* a = bar->GetArea();
    r[0] = 0.0f; r[1] = 0.0f;
    r[2] = (a[2] - a[0]) * fv;
    r[3] = a[3] - a[1];
    f1->SetArea(r);
    f1->SetFlag(1, 1);
  }
  if (f2 != 0) f2->SetFlag(1, 0);
  IWindow_s00e5_77a0* g1 = ((cSPUILayout_s00e5_77a0*)*(cSPUILayout_s00e5_77a0**)(param_1 + 0x34))->FindWindowByID(0x26e0df2, 1);
  IWindow_s00e5_77a0* g2 = ((cSPUILayout_s00e5_77a0*)*(cSPUILayout_s00e5_77a0**)(param_1 + 0x34))->FindWindowByID(0x26e0df1, 1);
  fv = *(float*)(param_1 + 0x14);
  if (g1 != 0) {
    float r[4];
    float* a = bar->GetArea();
    r[0] = 0.0f; r[1] = 0.0f;
    r[2] = (a[2] - a[0]) * fv;
    r[3] = a[3] - a[1];
    g1->SetArea(r);
  }
  fv = *(float*)(param_1 + 0x1c);
  if (g2 != 0) {
    float r[4];
    float* a = bar->GetArea();
    r[0] = 0.0f; r[1] = 0.0f;
    r[2] = (a[2] - a[0]) * fv;
    r[3] = a[3] - a[1];
    g2->SetArea(r);
  }
  FUN_00e504b0(g1, *(float*)(param_1 + 0x10));
  FUN_00e504b0(g2, *(float*)(param_1 + 0x18));
}

// @ 0x00e582c0
void FUN_00e582c0(int param_1, float param_2)
{
  float d, en, cap, cur, g, a0, a1, a2, o0, o1, v;
  float* ph;
  float* pe;
  char* cell;
  bool enUp, gPos;
  IWindow_s00e5_77a0* w;

  if (*(char*)((char*)gspCellGame + 0x5169) == 1) {
    FUN_00e54880(param_1);
    return;
  }

  d = param_2 * kf14853e0;                 // param_2 * 4.0
  ph = (float*)(param_1 + 0x2c);           // blinking-threshold slot
  *ph = *ph - d;
  if (*ph < kf1485378) *ph = kf1485378;    // clamp threshold to [0,1]
  if (*ph > kf1485720) *ph = kf1485720;

  cell = (char*)((CellPool*)&gspCellGame->mCells)->Get(*(unsigned int*)(param_1 + 4));
  if (cell == 0) {
    pe = (float*)(param_1 + 0x20);         // energy slot
    *pe = *pe - d;
    if (*(char*)(param_1 + 0x30) != 0) {
      if (!(*ph > *pe)) ph = pe;
      *pe = *ph;
    }
    FUN_00e57fd0(param_1);
    if (!(*pe > kf1485378)) FUN_00e54880(param_1);
    return;
  }

  cap = (float)*(int*)(cell + 0x244) * kf1440f84;   // capacity = max * 1/6
  cur = *(float*)(param_1 + 8);
  *(float*)(param_1 + 0xc) = cap;
  if (cur < cap) {
    *(float*)(param_1 + 0x14) = cap;
    *(float*)(param_1 + 0x1c) = cap;
  }
  if (*(float*)(param_1 + 0x28) > kf1485378) {      // death timer counts down
    *(float*)(param_1 + 0x28) = *(float*)(param_1 + 0x28) - param_2;
    goto done;
  }

  en = *(float*)(param_1 + 0x20);
  pe = (float*)(param_1 + 0x20);
  enUp = (kf1485720 > en && cur != cap);
  if (!enUp) {
    if (cur < cap) {
      if (*(float*)(param_1 + 0x10) > kf1485378)
        *(float*)(param_1 + 0x10) = FUN_005a6e00(*(float*)(param_1 + 0x10) - d);
      if (*(float*)(param_1 + 0x18) >= kf1485720) {
        v = param_2 * kf1470f1c + *(float*)(param_1 + 8);
        *(float*)(param_1 + 8) = v;
        if (*(float*)(param_1 + 0xc) <= v) *(float*)(param_1 + 8) = *(float*)(param_1 + 0xc);
      } else {
        *(float*)(param_1 + 0x18) = FUN_005a6e00(*(float*)(param_1 + 0x18) + d);
      }
      goto done;
    }
    if (cur == cap) {
      if (*(float*)(param_1 + 0x18) > kf1485378 && *(float*)(param_1 + 0x1c) > cur) {
        *(float*)(param_1 + 0x10) = FUN_005a6e00(*(float*)(param_1 + 0x10) - param_2);
        goto done;
      }
      if (*(float*)(param_1 + 0x24) > kf1485378) {
        if (kf1485720 > en) {
          enUp = true;
        } else {
          *(float*)(param_1 + 0x24) = *(float*)(param_1 + 0x24) - param_2;
          goto done;
        }
      } else {
        *pe = en - d;
        if (*(char*)(param_1 + 0x30) != 0) {
          if (!(*ph > *pe)) ph = pe;
          *pe = *ph;
        }
        if (!(*pe > kf1485378)) { FUN_00e54880(param_1); return; }
        goto done;
      }
    } else {                                   // cur > cap
      g = *(float*)(param_1 + 0x18);
      gPos = false;
      if (g > kf1485378) {
        *(float*)(param_1 + 0x18) = FUN_005a6e00(g - d);
        gPos = true;
      }
      if (*(float*)(param_1 + 0x10) >= kf1485720 || *(float*)(param_1 + 0x14) <= cur) {
        *(float*)(param_1 + 0x10) = kf1485720;
        if (!gPos) {
          v = *(float*)(param_1 + 8) - param_2 * kf1470f1c;
          *(float*)(param_1 + 8) = v;
          if (v <= *(float*)(param_1 + 0xc)) *(float*)(param_1 + 8) = *(float*)(param_1 + 0xc);
        }
        goto done;
      }
      *(float*)(param_1 + 0x10) = FUN_005a6e00(*(float*)(param_1 + 0x10) + d);
      goto done;
    }
  }
  // enUp: energy rises toward 1.0 (clamped)
  *pe = en + d;
  *pe = FUN_005a6e00(*pe);
  if (*(char*)(param_1 + 0x30) != 0) {
    if (!(*ph > *pe)) ph = pe;
    *pe = *ph;
  }

done:
  if (FUN_00e57340((int)cell) == 4) {
    a0 = *(float*)(cell + 0x4c);
    a1 = *(float*)(cell + 0x50);
    a2 = *(float*)(cell + 0x54);
  } else {
    v = *(float*)(cell + 0x58);
    a0 = *(float*)(cell + 0x4c) + (kf15a7c34 * v) * kf1486374;
    a1 = *(float*)(cell + 0x50) + (kf15a7c38 * v) * kf1486374;
    a2 = *(float*)(cell + 0x54) + (kf15a7c3c * v) * kf1486374;
  }
  FUN_00e50750(&a0, &o0, &o1);
  w = ((cSPUILayout_s00e5_77a0*)*(cSPUILayout_s00e5_77a0**)(param_1 + 0x34))->FindWindowByID(0x93310e4a, 1);
  w->SetSize(o0, o1);
  FUN_00e57fd0(param_1);
}

// @ 0x00e58890
bool FUN_00e58890(int id1, int id2, int a)
{
  char* c1 = (char*)CellsPool().GetValid(id1);
  if (!c1) return false;
  char* c2 = (char*)CellsPool().GetValid(id2);
  if (!c2) return false;
  c1[0x18a] = 1;
  c1[0x17f] = 1;
  c1[0x17c] = 1;
  c1[0x17b] = 1;
  c1[0x17e] = 1;
  *(int*)(c2 + 0x190) = id1;
  c2[0x17f] = 1;
  c2[0x178] = 1;
  c2[0x17c] = 1;
  FUN_00e57a10(c2, a);
  switch (*(int*)(c1 + 0x18c)) {
    case 0: case 1: case 0x12: case 0x13: case 0x14: case 0x15:
    case 0x16: case 0x1d: case 0x30:
      *(int*)(c1 + 0x18c) = 0x1e;
      FUN_00e57a10(c1, a);
  }
  return true;
}

// @ 0x00e58980
int FUN_00e58980(int* a, int* b)
{
  if (*a == *(int*)(G + 0x411c)) {
    switch (FUN_00e57340((int)b)) {
      case 0: case 1: return 6;
      case 2: return (*(int*)(*(int*)(G + 0x5190) + 0x7c) != 2) + 2;
      case 3: case 4: return 1;
      default: return 0;
    }
  }
  if (*b != *(int*)(G + 0x411c)) {
    int local_64[25] = {
      0, 0, 0, 0, 0,
      6, 2, 1, 0, 0,
      6, 6, 2, 0, 0,
      6, 6, 6, 2, 0,
      6, 6, 6, 6, 2
    };
    int i = FUN_00e57340((int)a);
    int j = FUN_00e57340((int)b);
    return local_64[i * 5 + j];
  }
  switch (FUN_00e57340((int)a)) {
    case 0: case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 6;
    default: return 0;
  }
}

// @ 0x00e58bf0
bool FUN_00e58bf0(int id, float a, float b)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  if (*(int*)(c + 0x248) != 0) {
    float r = FUN_00e58b60(a, b);
    *(float*)(c + 0xa0) = r;
    *(float*)(c + 0xa4) = r;
  }
  return true;
}

// @ 0x00e58c50
char* FUN_00e58c50(char* p)
{
  char* r = (char*)CellsPool().GetValid(*(int*)(p + 0x36c));
  while (r != 0) {
    p = r;
    int child = *(int*)(r + 0x36c);
    r = (char*)CellsPool().GetValid(child);
  }
  return p;
}

// @ 0x00e58c90
bool FUN_00e58c90(char* p)
{
  char* c1 = (char*)CellsPool().GetValid(*(int*)(p + 4));
  char* c2 = (char*)CellsPool().GetValid(*(int*)(p + 8));
  if (!c1 || !c2) return false;
  c1 = FUN_00e58c50(c1);
  c2 = FUN_00e58c50(c2);
  float old = *(float*)(p + 0x28);
  float dist = (*(float*)(p + 0x38) -
                ((*(float*)(c2 + 0x98) - *(float*)(c1 + 0x98)) * *(float*)(p + 0x20) +
                 (*(float*)(c2 + 0x94) - *(float*)(c1 + 0x94)) * *(float*)(p + 0x1c) +
                 (*(float*)(c2 + 0x90) - *(float*)(c1 + 0x90)) * *(float*)(p + 0x18))) *
               *(float*)(p + 0x30) + old;
  dist = (0.0f > dist) ? 0.0f : dist;
  *(float*)(p + 0x28) = dist;
  float d = dist - old;
  float vx = *(float*)(p + 0x18) * d;
  float vy = *(float*)(p + 0x1c) * d;
  float vz = *(float*)(p + 0x20) * d;
  if (*(float*)(p + 0x18) * vx + *(float*)(p + 0x1c) * vy + *(float*)(p + 0x20) * vz >= 0.0f) {
    float neg[3];
    neg[0] = -vx; neg[1] = -vy; neg[2] = -vz;
    FUN_00e560d0((int)c1, neg);
    float pos[3];
    pos[0] = vx; pos[1] = vy; pos[2] = vz;
    FUN_00e560d0((int)c2, pos);
  }
  return true;
}

// @ 0x00e58e30
int FUN_00e58e30()
{
  int result = 0;
  Ref t; t.Init();
  char* list = (char*)FUN_00e823a0(*(int*)(G + 0x4114), &t);
  int lvl = *(int*)(*(char**)(G + 0x5190) + 0x1c);
  int v = *LevelEntry(lvl);
  int n = *(int*)(list + 8);
  char* p = *(char**)(list + 0xc);
  for (int i = 0; i < n; ++i, p += 0x18) {
    if (*(int*)(p + 4) == v + 1) {
      t.Release();
      return *(int*)(p + 0x14);
    }
    if (*(int*)(p + 4) == -1) result = *(int*)(p + 0x14);
  }
  t.Release();
  return result;
}

// @ 0x00e58ef0
int FUN_00e58ef0(int* out0, float* out1, float* out2, float* out3)
{
  int result = 0;
  Ref t; t.Init();
  char* list = (char*)FUN_00e823a0(*(int*)(G + 0x4114), &t);
  int lvl = *(int*)(*(char**)(G + 0x5190) + 0x1c);
  int v = *LevelEntry(lvl);
  int n = *(int*)(list + 8);
  if (n > 0) {
    for (int i = 0; i < n; ++i) {
      char* e = *(char**)(list + 0xc) + i * 0x18;
      if (*(int*)(e + 4) == v) {
        *out0 = *(int*)(e);
        *out1 = *(float*)(e + 8);
        *out2 = *(float*)(e + 0xc);
        *out3 = *(float*)(e + 0x10);
        t.Release();
        return *(int*)(e + 0x14);
      }
      if (*(int*)(e + 4) == -1) {
        *out0 = *(int*)(e);
        *out1 = *(float*)(e + 8);
        *out2 = *(float*)(e + 0xc);
        *out3 = *(float*)(e + 0x10);
        result = *(int*)(e + 0x14);
      }
    }
  }
  t.Release();
  return result;
}

// @ 0x00e59010
bool FUN_00e59010(int id, int a, int b, char flag, float f, float* v)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x17c] = 1;
  c[0x178] = 1;
  c[0x188] = 1;
  if (flag) {
    switch (*(int*)(c + 0x18c)) {
      case 0: case 1: case 2: case 3: case 4: case 5: case 0xb: case 0xc:
      case 0xd: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x18:
      case 0x19: case 0x1c: case 0x1e: case 0x28: case 0x2f: case 0x30: case 0x31:
        switch (b) {
          case 1: case 2:
            if (k1488874 > f) *(int*)(c + 0x190) = a;
            *(int*)(c + 0x18c) = 0xe;
            break;
          case 3:
            *(int*)(c + 0x18c) = 0xf;
            return true;
          case 4:
            *(int*)(c + 0x18c) = 0x10;
            break;
          case 5:
            *(int*)(c + 0x18c) = 0x11;
            break;
          default:
            return true;
        }
        *(float*)(c + 0x1a8) = -v[2];
        *(float*)(c + 0x1a4) = -v[1];
        *(float*)(c + 0x1a0) = -v[0];
    }
  }
  return true;
}

// @ 0x00e59150
void FUN_00e59150(int id)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (c) c[0x112] = 1;
}

// @ 0x00e59170
bool FUN_00e59170(int id)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x16c] = 1;
  c[0x178] = 1;
  c[0x17c] = 1;
  c[0x188] = 1;
  *(int*)(c + 0x18c) = 7;
  return true;
}

// @ 0x00e591c0
bool FUN_00e591c0(int id)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x16c] = 1;
  c[0x178] = 1;
  c[0x17c] = 1;
  *(int*)(c + 0x18c) = 7;
  return true;
}

// @ 0x00e59200
void FUN_00e59200(int id)
{
  char* e = (char*)SecPool().GetValid(id);
  if (e) {
    int cid = *(int*)(e + 0xc);
    char* c = (char*)CellsPool().GetValid(cid);
    if (c) {
      *(int*)(c + 0x370) = 0;
      *(int*)(c + 0x36c) = 0;
    }
    SecPool().Remove(id);
  }
}

// @ 0x00e59260
bool FUN_00e59260(int id)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 1: case 4: case 5: case 0xb: case 0xc: case 0xe: case 0xf:
    case 0x10: case 0x11: case 0x12: case 0x15: case 0x16: case 0x28: case 0x2f:
    case 0x30:
      *(int*)(c + 0x18c) = 8;
  }
  c[0x178] = 1;
  c[0x17b] = 1;
  c[0x17c] = 1;
  return true;
}

// @ 0x00e592f0
bool FUN_00e592f0(int id, int a, int b, int c2, int* v)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x178] = 1;
  c[0x17f] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 2: case 4: case 5: case 0x12: case 0x13: case 0x14: case 0x15:
    case 0x16: case 0x21: case 0x28: case 0x30: case 0x32: case 0x33:
      *(int*)(c + 0x18c) = 4;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      FUN_00e57a10(c, b);
  }
  return true;
}

// @ 0x00e593b0
bool FUN_00e593b0(int id, int a, int b, int* v)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x178] = 1;
  c[0x17f] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x30:
      *(int*)(c + 0x18c) = 0x1c;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      FUN_00e57a10(c, b);
  }
  return true;
}

// @ 0x00e59470
bool FUN_00e59470(int id)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  if (c[0x112] != 0) return false;
  c[0x178] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 0x12: case 0x15: case 0x16: case 0x1d: case 0x30:
      *(int*)(c + 0x18c) = 0x3d;
  }
  return true;
}

// @ 0x00e59500
bool FUN_00e59500(int id)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  c[0x16c] = 1;
  c[0x17c] = 1;
  c[0x17b] = 1;
  c[0x17f] = 1;
  c[0x178] = 1;
  c[0x179] = 1;
  c[0x188] = 1;
  *(int*)(c + 0x18c) = 9;
  return true;
}

// @ 0x00e59560
bool FUN_00e59560(int id, int other, int b, int* v)
{
  char* c = (char*)CellsPool().GetValid(id);
  if (!c) return false;
  if (c[0x112] != 0) return false;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 4: case 5: case 0x12: case 0x13: case 0x14: case 0x15:
    case 0x16: case 0x1c: case 0x30: case 0x32: case 0x33:
      *(int*)(c + 0x18c) = 5;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      FUN_00e57a10(c, b);
  }
  c[0x17f] = 1;
  c[0x178] = 1;
  char* c2 = (char*)CellsPool().GetValid(other);
  if (c2) c2[0x188] = 1;
  return true;
}

// @ 0x00e59640
bool FUN_00e59640(int id, int a, int b, int state, int* v)
{
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  if (c[0x112]) return false;
  *(int*)(c + 0x184) = a;
  *(char*)(c + 0x178) = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 3: case 0xb: case 0xc: case 0xd: case 0x12:
    case 0x15: case 0x16: case 0x1a: case 0x1d: case 0x20: case 0x21:
    case 0x22: case 0x30:
      *(int*)(c + 0x18c) = state;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      c[4] = 1;
      FUN_00e57a10(c, b);
  }
  return true;
}

// @ 0x00e59710
bool FUN_00e59710(int id, int id2, int a, int b, float t)
{
  char* c1;
  { CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells; c1 = (char*)pool->Get(id); }
  if (!c1) return false;
  if (c1[0x112]) return false;
  char* c2;
  { CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells; c2 = (char*)pool->Get(id2); }
  if (!c2) return false;
  if (c2[0x112]) return false;
  *(char*)(c1 + 0x178) = 1;
  *(int*)(c1 + 0x184) = *(int*)c2;
  *(char*)(c1 + 0x188) = 1;
  *(int*)(c2 + 0x184) = *(int*)c1;
  switch (*(int*)(c1 + 0x18c)) {
    case 0: case 0xb: case 0xc: case 0xd: case 0x12: case 0x13: case 0x14:
    case 0x15: case 0x16: case 0x1d: case 0x30: case 0x32: case 0x33:
      if (t > kf1485378) {
        *(int*)(c1 + 0x18c) = 0xd;
        FUN_00e57a10(c1, a);
      }
  }
  return true;
}

// @ 0x00e59800
void FUN_00e59800(int param_1)
{
  int iVar3 = ((CellSub*)*(void**)(GAME_P + 0x1c))->Level();
  int delta = iVar3 - *(int*)(GAME_P + 0x2c);
  float f = FUN_00e51720(2, *(int*)(GAME_P + 0x1c));
  FUN_00e4fac0(GAME_P + 0x34);
  int iVar2 = *(int*)(GAME_P + 0x1c);
  int* entry;
  if (iVar2 == 1000) {
    entry = (int*)0x1483e60;
  } else {
    int i = 0;
    if (iVar2 >= 0) {
      int* t = (int*)0x1483c34;
      do { t += 7; ++i; } while (*t <= iVar2);
    }
    entry = (int*)0x1483c14 + i * 7;
  }
  FUN_00e84600(param_1, entry[5], GAME_P[0xe2], GAME_P + 0x10, f,
               GAME_P[0x410c], *(int*)(GAME_P + 0x5164), delta);
}

// @ 0x00e598e0
static bool FUN_00e598e0(int id, float t)
{
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  float d = t - kf1485720;
  c[0x16c] = 1;
  c[0x178] = 1;
  c[0x17f] = 1;
  c[0x180] = 1;
  c[0x17b] = 1;
  c[0x17c] = 1;
  c[0x188] = 1;
  if (d > kf1485378) {
    switch (*(int*)(c + 0x18c)) {
      case 0: case 7: case 8: case 9: case 0xb: case 0xc: case 0xd:
      case 0xf: case 0x10: case 0x12: case 0x1d: case 0x29: case 0x2b:
      case 0x2c: case 0x2d: case 0x2e: case 0x30: case 0x31: case 0x41:
      case 0x42:
        *(int*)(c + 0x18c) = 0x29;
    }
  }
  return true;
}

// @ 0x00e599b0
static bool FUN_00e599b0(int id)
{
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  c[0x178] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 7: case 8: case 9: case 0xb: case 0xc: case 0xd: case 0x21:
    case 0x22: case 0x29: case 0x2b: case 0x2c: case 0x2d: case 0x2e:
      break;
    default:
      *(int*)(c + 0x18c) = 0x1d;
  }
  return true;
}

// @ 0x00e59a30
bool FUN_00e59a30()
{
  unsigned int id = *(unsigned int*)((char*)gspCellGame_s00e5_9640 + 0x411c);
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  *(int*)(c + 0x18c) = 0x2e;
  c[0x17c] = 1;
  c[0x17b] = 1;
  c[0x188] = 1;
  return true;
}

// @ 0x00e59a70
static bool FUN_00e59a70(int id)
{
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  c[0x178] = 1;
  c[0x17f] = 1;
  *(int*)(c + 0x18c) = 0x31;
  return true;
}

// @ 0x00e59ab0
void FUN_00e59ab0(int id)
{
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (c) {
    int src = *(int*)((char*)gspCellGame_s00e5_9640 + 0x411c);
    float f = kf1477fc0;
    *(int*)(c + 0x220) = src;
    *(float*)(c + 0x21c) = f;
  }
}

// @ 0x00e59af0
bool FUN_00e59af0(int id, int a)
{
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  c[0x17c] = 1;
  c[0x178] = 1;
  c[0x16c] = 1;
  int s = *(int*)(c + 0x18c);
  if (s != 7 && s != 10) {
    *(int*)(c + 0x18c) = (a != 6) + 0x3f;
  }
  return true;
}

// @ 0x00e59b50
bool FUN_00e59b50(int id, int a, int* v)
{
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (!c) return false;
  c[0x16c] = 1;
  c[0x178] = 1;
  c[0x17f] = 1;
  switch (*(int*)(c + 0x18c)) {
    case 0: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x30:
      *(int*)(c + 0x18c) = 0x1c;
      *(int*)(c + 0x1a0) = v[0];
      *(int*)(c + 0x1a4) = v[1];
      *(int*)(c + 0x1a8) = v[2];
      FUN_00e57a10(c, a);
  }
  return true;
}

// @ 0x00e59c10
bool FUN_00e59c10(CbRec* p, float x)
{
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(p->id);
  if (c) {
    if (*(int*)(c + 0x248) != 0 && *(int*)(c + 0xfc) != 0) {
      void* q = ((ResMap*)(gspCellGfx + 0x168))->Find(*(unsigned int*)(c + 0x248));
      if (*(int*)((char*)q + 0x24) != 0) {
        char r = (char)FUN_00e50620(0xca880d53, 0);
        if (p->fn == 0) return true;
        if (p->done) return true;
        if (r == 0) return true;
        bool ret = p->fn(p, x);
        p->done = 1;
        return ret;
      }
    }
    if (p->fn != 0 && !p->done) {
      bool ret = p->fn(p, x);
      p->done = 1;
      return ret;
    }
  }
  return true;
}

// @ 0x00e59cc0
void FUN_00e59cc0(int* rec, int* a, int* b, float f, int c5, int c6, int c7, int c8, int c9)
{
  if (c9 > rec[2] || (c9 == rec[2] && f > *(float*)(rec + 5))) {
    rec[1] = c6;
    rec[0] = c5;
    rec[6] = a[0];
    rec[7] = a[1];
    rec[8] = a[2];
    rec[9] = b[0];
    rec[10] = b[1];
    rec[11] = b[2];
    *(float*)(rec + 5) = f;
    rec[3] = c7;
    rec[4] = c8;
    rec[2] = c9;
  }
  if (c9 == rec[2] && c9 == 8 && c5 == *(int*)((char*)gspCellGame_s00e5_9640 + 0x411c)) {
    rec[0] = c5;
    rec[1] = c6;
    rec[6] = a[0];
    rec[7] = a[1];
    rec[8] = a[2];
    rec[9] = b[0];
    rec[10] = b[1];
    rec[11] = b[2];
    *(float*)(rec + 5) = f;
    rec[3] = c7;
    rec[4] = c8;
    rec[2] = 8;
  }
}

// @ 0x00e59d90
int FUN_00e59d90(int id)
{
  int result = 2;
  CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells;
  char* c = (char*)pool->Get(id);
  if (c) {
    char obj[4];
    ((ObjHolder*)obj)->Init();
    char* r = (char*)FUN_00e823a0_s00e5_9640(*(int*)(c + 0x108), obj);
    int v = *(int*)(r + 0xc0);
    if (v != 0) {
      ((ObjHolder*)obj)->Cleanup();
      return v;
    }
    switch (*(int*)(r + 0xb4)) {
      case 1: result = 3; break;
      case 2: result = 1; break;
      case 3: result = 2; break;
      case 4: result = 4; break;
    }
    ((ObjHolder*)obj)->Cleanup();
  }
  return result;
}

// @ 0x00e59e50
bool FUN_00e59e50(int p, int arg)
{
  if (*(int*)(p + 0x108) != FUN_00e4cce0(arg)) return false;
  if (FUN_00e57340(p) == 4) return true;
  return false;
}

// @ 0x00e59e80
void FUN_00e59e80()
{
  *(char*)((char*)gspCellGame_s00e5_9640 + 0x4120) = 0;
  int local;
  { CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells; local = pool->Begin(); }
  char* p;
  { CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells; p = (char*)pool->Next(&local); }
  while (p) {
    memset_thunk(p + 0x16c, 0, 0x44);
    { CellPool_s00e5_9640* pool = &gspCellGame_s00e5_9640->mCells; p = (char*)pool->Next(&local); }
  }
}

// @ 0x00e59ee0
void SP_sUpdateFluidParticles(float dt)
{
  char* fp = *(char**)((char*)gspCellGame_s00e5_9640 + 0x4108);
  FluidParticlesUpdate(fp, dt);
  int off = 0;
  int idx = 0x18e74;
  do {
    char* c = fp + off;
    *(float*)(c + 0xc) = 0.0f;
    *(float*)(c + 0x465c) = 0.0f;
    *(float*)(c + 0xd2fc) = 0.0f;
    *(float*)(c + 0x1194c) = 0.0f;
    float* pos = (float*)(c + 4);
    float fy = *(float*)(c + 0xd2f8) * dt + *(float*)(c + 0x4658);
    float fx = *(float*)(c + 0x4654) + *(float*)(c + 0xd2f4) * dt;
    *(float*)(c + 0x4654) = fx;
    *(float*)(c + 0x4658) = fy;
    float fz = *(float*)(c + 0x465c) + dt * *(float*)(c + 0xd2fc);
    *(float*)(c + 0x465c) = fz;
    fy = (fy * dt + *(float*)(c + 0x11948)) + *(float*)(c + 8);
    fx = *pos + (fx * dt + *(float*)(c + 0x11944));
    *pos = fx;
    *(float*)(c + 8) = fy;
    *(float*)(c + 0xc) = (fz * dt + *(float*)(c + 0x1194c)) + *(float*)(c + 0xc);
    if ((fx < gExtentXMin || gExtentXMax < fx || fy < gExtentYMin || gExtentYMax < fy) &&
        *(int*)(fp + idx) == 0) {
      if (gExtentXMin <= fx) {
        if (gExtentXMax < fx) *pos = fx - (gExtentXMax - gExtentXMin);
      } else {
        *pos = (gExtentXMax - gExtentXMin) + fx;
      }
      if (gExtentYMin <= fy) {
        if (gExtentYMax < fy) *(float*)(c + 8) = fy - (gExtentYMax - gExtentYMin);
      } else {
        *(float*)(c + 8) = (gExtentYMax - gExtentYMin) + fy;
      }
      int col, row;
      FUN_00e56c30(*(float*)((char*)gspCellGame_s00e5_9640 + 4), pos, &col, &row);
      float s = *(float*)((char*)gspCellGame_s00e5_9640 + 8);
      int t = row * 0x80 + col;
      float vc = s * *(float*)(*(int*)(*(int*)(char*)gspCellGame_s00e5_9640 + 0x18) + t * 0xc);
      float v8 = s * *(float*)(*(int*)(*(int*)(char*)gspCellGame_s00e5_9640 + 0x18) + 4 + t * 0xc);
      float v4 = s * 0.0f;
      *(float*)(c + 0x4654) = vc;
      *(float*)(c + 0x4658) = v8;
      *(float*)(c + 0x465c) = v4;
    }
    idx += 4;
    off += 0xc;
  } while (idx < 0x1a5e4);
  memset_thunk(fp + 0xd2f4, 0, 18000);
  memset_thunk(fp + 0x11944, 0, 18000);
}

// @ 0x00e5a1a0
static void FUN_00e5a1a0(char* cell)
{
  if (*(int*)(cell + 0x248) != 0 &&
      *(int*)(cell + 0x35c) != *(int*)((char*)gspCellGame_s00e5_9640 + 0x4100)) {
    float f = *(float*)(cell + 0x58);
    int lvl;
    if (f < kf1470f1c) {
      if (f < kf1485720) {
        lvl = (f < kf13eb8c8) ? 0 : 1;
      } else {
        lvl = 2;
      }
    } else {
      lvl = 3;
    }
    if (*(int*)(cell + 0x24c) != lvl) {
      char o1[4];
      char o2[4];
      ((ObjHolder*)o1)->Init();
      char* r = (char*)FUN_00e823a0_s00e5_9640(*(int*)(cell + 0x108), o1);
      ((ObjHolder*)o2)->Init();
      FUN_00e823a0_s00e5_9640(*(int*)r, o2);
      int state = *(int*)(r + 0xb4);
      if (state != 0 && state != 5) {
        FUN_00e51a40(0x16ae800, *(int*)cell, cell + 0x250, *(int*)(cell + 0x24c));
        *(int*)(cell + 0x24c) = lvl;
      }
      ((ObjHolder*)o2)->Cleanup();
      ((ObjHolder*)o1)->Cleanup();
    }
  }
}

// @ 0x00e5a2a0
float FUN_00e5a2a0(float* a, float* b, float d)
{
  if ((g16b4440 & 1) == 0) {
    g16b4440 |= 1;
    g16b4434 = -kf15a7c34;
    g16b4438 = -kf15a7c38;
    g16b443c = -kf15a7c3c;
  }
  float va[3], vb[3];
  va[0] = (a[6] * g16b443c + a[3] * g16b4438) + a[0] * g16b4434;
  va[1] = (a[7] * g16b443c + a[4] * g16b4438) + a[1] * g16b4434;
  va[2] = (a[8] * g16b443c + a[5] * g16b4438) + a[2] * g16b4434;
  vb[0] = (b[6] * g16b443c + b[3] * g16b4438) + b[0] * g16b4434;
  vb[1] = (b[7] * g16b443c + b[4] * g16b4438) + b[1] * g16b4434;
  vb[2] = (b[8] * g16b443c + b[5] * g16b4438) + b[2] * g16b4434;
  return FUN_006994a0(va, vb, &kf15a7c40) / d;
}

// @ 0x00e5a850
namespace SP {
void sLevelGetTextureCoord(int level, float* pos, uint32_t* out0, uint32_t* out1)
{
    // volatile temps force each float to be rounded to 32 bits at the same points as the original's stores
    volatile float size = (kLevelSize[level] / gspCellGame_s00e5_a430->mLevelScale) * (sGetBoxSizeMultiplier2(level, 0) * 0.85f);
    volatile float inv = 1.0f / size;
    volatile float p0 = pos[0] * inv;
    *out0 = WrapTexCoord(RoundToInt_s00e5_a430(p0 * 128.0f));
    volatile float p1 = pos[1] * inv;
    *out1 = WrapTexCoord(RoundToInt_s00e5_a430(p1 * 128.0f));
    if ((int)*out0 < 1) *out0 = *out0 + 0x80;
    if ((int)*out1 < 1) *out1 = *out1 + 0x80;
}
}  // namespace SP

// @ 0x00e5dba0
namespace SP {
void sInitGfx()
{
    gEditorPhysicsWorld.Init(0);
    gspCellGfx_s00e5_dba0->mFlag16204 = 0;
    gspCellGfx_s00e5_dba0->mFlag16205 = 0;
    gspCellGfx_s00e5_dba0->mViewport.Init(200, 256);
    gspCellGfx_s00e5_dba0->mScale = 1.0f;

    gspCellGfx_s00e5_dba0->mpLighting = LightingManager()->GetLightRig(0x4a4d97f, 0, 0);
    gspCellGfx_s00e5_dba0->mpLighting->SetEnvironment(0xa426730b);

    int width = App()->GetWindowWidth();
    int height = App()->GetWindowHeight();

    gspCellGfx_s00e5_dba0->mpSkyEffects = EffectsManager()->CreateWorld(0x1010000, "CellSkyboxEffectsWorld");
    gspCellGfx_s00e5_dba0->mpSkyCamera = GetLayerCamera(2);
    gspCellGfx_s00e5_dba0->mpSkyCamera->SetViewport(height, width);
    gspCellGfx_s00e5_dba0->mpSkyEffects->AttachCamera(gspCellGfx_s00e5_dba0->mpSkyCamera);

    gspCellGfx_s00e5_dba0->mpBackEffects = EffectsManager()->CreateWorld(0x1010011, "CellBackgroundEffectsWorld");
    gspCellGfx_s00e5_dba0->mpBackCamera = GetLayerCamera(1);
    gspCellGfx_s00e5_dba0->mpBackCamera->SetViewport(height, width);
    gspCellGfx_s00e5_dba0->mpBackEffects->AttachCamera(gspCellGfx_s00e5_dba0->mpBackCamera);

    gspCellGfx_s00e5_dba0->mpBackModels = ModelManager()->CreateWorld(0x1010010, "CellBackgroundModelWorld", 0);
    gspCellGfx_s00e5_dba0->mpBackModels->SetLighting(gspCellGfx_s00e5_dba0->mpLighting, 0, 1);
    gspCellGfx_s00e5_dba0->mpBackModels->SetFarClip(8.0f);

    gspCellGfx_s00e5_dba0->mpBackLayer = LayerManager()->GetLayer(L"CellGame-Background");
    gspCellGfx_s00e5_dba0->mpBackLayer->AddModelWorld(gspCellGfx_s00e5_dba0->mpBackModels, 1, 1, 0, 1);
    gspCellGfx_s00e5_dba0->mpBackLayer->AddEffectsWorld(gspCellGfx_s00e5_dba0->mpBackEffects);

    gspCellGfx_s00e5_dba0->mpBeachEffects = EffectsManager()->CreateWorld(0x1010016, "CellBeachEffectsWorld");
    gspCellGfx_s00e5_dba0->mpBeachModels = ModelManager()->CreateWorld(0x1010015, "CellBeachModelWorld", 0);
    gspCellGfx_s00e5_dba0->mpBeachModels->SetLighting(gspCellGfx_s00e5_dba0->mpLighting, 0, 1);
    gspCellGfx_s00e5_dba0->mpBeachCamera = GetLayerCamera(0);
    gspCellGfx_s00e5_dba0->mpBeachCamera->SetViewport(height, width);
    gspCellGfx_s00e5_dba0->mpBeachEffects->AttachCamera(gspCellGfx_s00e5_dba0->mpBeachCamera);

    gspCellGfx_s00e5_dba0->mpMainEffects = EffectsManager()->CreateWorld(0x1010021, "CellEffectsWorld");
    gspCellGfx_s00e5_dba0->mpMainModels = ModelManager()->CreateWorld(0x1010020, "CellModelWorld", 0);
    gspCellGfx_s00e5_dba0->mpMainModels->SetLighting(gspCellGfx_s00e5_dba0->mpLighting, 0, 1);

    gspCellGfx_s00e5_dba0->mpMainLayer = LayerManager()->GetLayer(L"CellGame-Main");
    gspCellGfx_s00e5_dba0->mpMainLayer->AddModelWorld(gspCellGfx_s00e5_dba0->mpMainModels, 1, 1, 0, 1);
    gspCellGfx_s00e5_dba0->mpMainLayer->AddEffectsWorld(gspCellGfx_s00e5_dba0->mpMainEffects);

    gspCellGfx_s00e5_dba0->mpFgEffects = EffectsManager()->CreateWorld(0x1010031, "CellForegroundEffectsWorld");
    gspCellGfx_s00e5_dba0->mpFgCamera = GetLayerCamera(4);
    gspCellGfx_s00e5_dba0->mpFgCamera->SetViewport(height, width);
    gspCellGfx_s00e5_dba0->mpFgEffects->AttachCamera(gspCellGfx_s00e5_dba0->mpFgCamera);

    memset(&gspCellGfx_s00e5_dba0->mEffectSlots, 0, sizeof(EffectSlots));
    gspCellGfx_s00e5_dba0->mEffectCount = 0;

    ARC<IRefObj>* pEffect = &gspCellGfx_s00e5_dba0->mpSkyboxEffect;
    pEffect->Reset();
    CreateEffectSafe(gspCellGfx_s00e5_dba0->mpSkyEffects, 0x5c7a4d0, 0, pEffect);
}
}  // namespace SP

// @ 0x00e61140
void FUN_00e61140(void)
{
    int a = gspCellGame_s00e6_1000->field_5190->field_1c->Call();
    int d = a - gspCellGame_s00e6_1000->field_5190->field_2c + 0x32;
    int b = f5c9d0();
    f83910(&gspCellGame_s00e6_1000->field_5190->sub10, d, b, gspCellGame_s00e6_1000->field_5164);
    f828c0();
    gspCellGame_s00e6_1000->field_5168 = 1;
}

// @ 0x00e61320
bool FUN_00e61320(int param)
{
    cCellGame* g = gspCellGame_s00e6_1000;
    if (g->field_5190->field_0c == 0)
        return false;
    switch (param) {
    case 0:
        FUN_00e611b0();
        break;
    case 1:
        g->field_5190->field_e8 = (g->field_5190->field_e8 == 0);
        return true;
    }
    return true;
}

// @ 0x00e61370
void FUN_00e61370(float* out, cSPTransform_s00e6_1000* p, float s)
{
    Matrix33 tmp;
    Matrix33 m;
    m = *(Matrix33*)f453b20(&tmp, g_15a7c40, g_16b3dd0 * s);
    float f0 = (m.x[0] * g_15a7c28 + m.y[0] * g_15a7c2c + m.z[0] * g_15a7c30) * g_1485548;
    float f1 = (m.x[1] * g_15a7c28 + m.y[1] * g_15a7c2c + m.z[1] * g_15a7c30) * g_1485548;
    float f2 = (m.x[2] * g_15a7c28 + m.y[2] * g_15a7c2c + m.z[2] * g_15a7c30) * g_1485548;
    out[0] = f0; out[1] = f1; out[2] = f2;
    if (p->mFlags & 2) {
        out[0] = p->mRotation.x[0] * f0 + p->mRotation.y[0] * f1 + p->mRotation.z[0] * f2;
        out[1] = p->mRotation.x[1] * f0 + p->mRotation.y[1] * f1 + p->mRotation.z[1] * f2;
        out[2] = p->mRotation.x[2] * f0 + p->mRotation.y[2] * f1 + p->mRotation.z[2] * f2;
    }
    float sc = p->mScale;
    out[0] = sc * out[0] + p->mTranslation[0];
    out[1] = sc * out[1] + p->mTranslation[1];
    out[2] = out[2] * sc + p->mTranslation[2];
}

// @ 0x00e61630
CellAbility* FUN_00e61630()
{
    CellAbility* a = FUN_00e61550();
    char h[8];
    f743b50(h);
    int* r = f4ce40(h);
    a->f0c = *r;
    a->f7c = f82970();
    switch (a->f0c) {
    case 0:
    case 2: {
        float v[3];
        f82920(v);
        a->f10 = v[0]; a->f14 = v[1]; a->f18 = v[2];
        break;
    }
    case 1:
        f82ce0(&a->f10);
        break;
    }
    f82130(h + 4);
    return a;
}

// @ 0x00e61a50
void* __stdcall CreateInstance_SaveGame(void*, void*)
{
    return new ("SP_Simulator/CellSaveGame/COM", 0, 0, 0, 0) SaveGameObj();
}

// @ 0x00e63ac0
void __cdecl FUN_00e63ac0(CellArray* a)
{
    int n = (int)(((char*)a->end - (char*)a->begin) / 0x74);
    for (int i = 0; i < n; ++i) {
        Cell* c = (Cell*)((char*)a->begin + i * 0x74);
        void* part = *(void**)((char*)c + 0x70);
        if (((VObj*)part)->v10() != 0) {
            sPartIntersectTarget(part, c, (char*)c + 0x38);
        } else {
            if (part) {
                *(void**)((char*)c + 0x70) = 0;
                ((RefObj*)part)->v2();
            }
            Cell* last = (Cell*)((char*)a->begin + (n - 1) * 0x74);
            cSPTransform_assign((cSPTransform_s00e6_3ac0*)c, (cSPTransform_s00e6_3ac0*)last);
            cSPTransform_assign((cSPTransform_s00e6_3ac0*)((char*)c + 0x38), (cSPTransform_s00e6_3ac0*)((char*)last + 0x38));
            void* lp = *(void**)((char*)last + 0x70);
            void* cp = *(void**)((char*)c + 0x70);
            if (lp != cp) {
                if (lp) ((RefObj*)lp)->v2();
                *(void**)((char*)c + 0x70) = lp;
                if (cp) ((RefObj*)cp)->v3();
            }
            a->end = (Cell*)((char*)a->end - 0x74);
            void* ep = *(void**)((char*)a->end + 0x70);
            if (ep) ((RefObj*)ep)->v3();
            --i; --n;
        }
    }
}

// @ 0x00e63bf0
void __cdecl FUN_00e63bf0(int* pCell, int effKind, int* pEffect, uint16_t* xform, char create)
{
    if (create) {
        if (*pEffect == 0) {
            uint32_t nameHash;
            if (*(int*)((char*)g_CellGame_s00e6_3ac0 + 0x411c) == *pCell)
                nameHash = EA_Hash_FNV1_String8("cell_call_avatar", 0x811c9dc5, 1);
            else
                nameHash = EA_Hash_FNV1_String8("cell_call_mate", 0x811c9dc5, 1);
            SP_CreateEffectSafe(effKind, nameHash, 0, (int)pEffect);
            ((VObj*)*pEffect)->v02();
        }
        cSPTransform_s00e6_3ac0 local;
        cSPTransform_assign(&local, (cSPTransform_s00e6_3ac0*)xform);
        if (*(int*)((char*)g_CellGame_s00e6_3ac0 + 0x411c) != *pCell)
            FUN_00e5bd30(&local);
        sPartIntersectTarget((void*)*pEffect, (char*)pCell + 0xc0, &local);
    } else if (*pEffect) {
        ((VObj*)*pEffect)->v03();
        ((VObj*)*pEffect)->v01();
        *pEffect = 0;
    }
}

// @ 0x00e63d10
void __cdecl FUN_00e63d10(int arg)
{
    g_16b3de0 = FUN_00e61550_s00e6_3ac0();
    FUN_00e627a0(arg);
}

// @ 0x00e63d60
void FixedVec8::DoInsertValue(PairIU* position, const PairIU& value)
{
    PairIU* pValue = const_cast<PairIU*>(&value);
    if (mpEnd != mpCapacity) {
        if (pValue >= position && pValue < mpEnd) ++pValue;
        *mpEnd = *(mpEnd - 1);
        PairIU* p = mpEnd;
        while (p != position) { --p; p[0] = p[-1]; }
        *position = *pValue;
        ++mpEnd;
    } else {
        uint32_t n = (uint32_t)(mpEnd - mpBegin);
        uint32_t nNew = n ? n * 2 : 1;
        PairIU* pNew = nNew ? (PairIU*)operator_new(nNew * 8, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        PairIU* pNewEnd = (PairIU*)FUN_0099efa0(mpBegin, position, pNew);
        if (pNewEnd) *pNewEnd = *pValue;
        PairIU* pEnd2 = (PairIU*)FUN_0099efa0(position, mpEnd, pNewEnd + 1);
        if (mpBegin && mpBegin != mpPoolBegin) operator_delete(mpBegin);
        mpBegin = pNew; mpEnd = pEnd2; mpCapacity = pNew + nNew;
    }
}

// @ 0x00e63e70
void FixedVec44::DoInsertValue(SoundElem* position, const SoundElem& value)
{
    SoundElem* pValue = const_cast<SoundElem*>(&value);
    if (mpEnd != mpCapacity) {
        if (pValue >= position && pValue < mpEnd) ++pValue;
        if (mpEnd) FUN_00e5c7d0(mpEnd - 1);
        SoundElem* p = mpEnd;
        while (p != position) { --p; *p = p[-1]; }
        *position = *pValue;
        ++mpEnd;
    } else {
        uint32_t n = (uint32_t)(mpEnd - mpBegin);
        uint32_t nNew = n ? n * 2 : 1;
        SoundElem* pNew = nNew ? (SoundElem*)operator_new(nNew * 0x2c, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        SoundElem* pNewEnd = (SoundElem*)FUN_00e5c860(mpBegin, position, pNew);
        if (pNewEnd) FUN_00e5c7d0(pValue);
        SoundElem* pEnd2 = (SoundElem*)FUN_00e5c860(position, mpEnd, pNewEnd + 1);
        if (mpBegin && mpBegin != mpPoolBegin) operator_delete(mpBegin);
        mpCapacity = pNew + nNew; mpEnd = pEnd2; mpBegin = pNew;
    }
}

// @ 0x00e64390
void FmtObj::Format(wchar_t* buf)
{
    if (mState != 0 && mState != 4 && mState != 5) {
        int a = v21();
        int b = v22();
        WStr_Format(buf, L"%d/%d", a, b);
    }
}

// @ 0x00e643e0
void __cdecl FUN_00e643e0(int id)
{
    void* cell = FUN_00b72210_s00e6_3ac0((char*)g_CellGame_s00e6_3ac0 + 0x1c, id);
    void* a = *(void**)((char*)cell + 0xfc);
    void* b = *(void**)((char*)cell + 0x100);
    void* c = *(void**)((char*)cell + 0x104);
    if (a && a != *(void**)((char*)CG(0x5190) + 0x10)) {
        void* r = FUN_0067de90(7, a, b, c);
        (void)r;
    }
}

// @ 0x00e644e0
SoundElem* VecInsert44::insert(SoundElem* position, const SoundElem& value)
{
    int idx = (int)(position - mpBegin);
    SoundElem* pEnd = mpEnd;
    if (position == pEnd && pEnd != mpCapacity) {
        mpEnd = pEnd + 1;
        if (pEnd) pEnd->operator=(value);
    } else {
        ((FixedVec44*)this)->DoInsertValue(position, value);
    }
    return mpBegin + idx;
}

// @ 0x00e646d0
void* __fastcall FUN_00e646d0(void* self)
{
    *(int*)self = 0;
    FUN_00743b50_s00e6_3ac0((char*)self + 0x1c);
    FUN_00743b50_s00e6_3ac0((char*)self + 0x38);
    FUN_00743b50_s00e6_3ac0((char*)self + 0x54);
    *(int*)((char*)self + 0x74) = (int)((char*)self + 0x74);
    *(int*)((char*)self + 0x78) = (int)((char*)self + 0x74);
    *(int*)((char*)self + 0x7c) = 0;
    *(uint8_t*)((char*)self + 0x80) = 0;
    *(int*)((char*)self + 0x84) = 0;
    FUN_00743b50_s00e6_3ac0((char*)self + 0x8c);
    FUN_00743b50_s00e6_3ac0((char*)self + 0xa8);
    FUN_00743b50_s00e6_3ac0((char*)self + 0xc4);
    FUN_00743b50_s00e6_3ac0((char*)self + 0x168);
    return self;
}

// @ 0x00e647d0
void* __fastcall FUN_00e647d0(void* self)
{
    for (int i = 0; i < 0x5c; i += 4) *(int*)((char*)self + i) = 0;
    FUN_00743b50_s00e6_3ac0((char*)self + 0x168);
    return self;
}

// @ 0x00e64980
void __cdecl FUN_00e64980(int param1)
{
    int local[3];
    local[0] = param1;
    local[1] = 0x3d97a8e4;
    local[2] = *(int*)0x015a7d0c;
    CellGfxObj* gfx = (CellGfxObj*)g_CellGfx;
    CellData* r = (CellData*)gfx->mpAt58->v12(local, 2, (void*)0x016b3c28, (void*)0x015a7c4c, 1);
    if (r) {
        SimpleVec* v = &gfx->mVector;
        if (v->mpEnd < v->mpCapacity) {
            *v->mpEnd = r;
            v->mpEnd = v->mpEnd + 1;
        } else {
            v->DoInsertValue(v->mpEnd, r);
        }
    }
}

// @ 0x00e65ad0
void FUN_00e65ad0(void* self, u8 destroy)
{
    char* this_ = (char*)self;

    // release one effect handle: route through FUN_00e65a00 when destroying, else vtable-release
    #define RELS(off) do {                                                       \
        void* p_ = *(void**)(this_ + (off));                                     \
        if (destroy == 0) { int loc_ = (int)p_; FUN_00e65a00(&loc_); }           \
        else if (p_ != 0) {                                                      \
            ((PFN_i)VT(p_)[0xc / 4])(p_, 1);                                     \
            ((PFN_v)VT(p_)[4 / 4])(p_);                                          \
        }                                                                        \
    } while (0)

    // drain one pointer vector [b,e): release each element, then eastl erase-all
    #define DRAIN(b, e) do {                                                     \
        int i_ = 0;                                                              \
        int n_ = (I(this_, (e)) - I(this_, (b))) >> 2;                           \
        if (n_ > 0) {                                                            \
            do {                                                                 \
                void* p_ = *(void**)((char*)(long)I(this_, (b)) + i_ * 4);       \
                if (destroy == 0) { int loc_ = (int)p_; FUN_00e65a00(&loc_); }   \
                else if (p_ != 0) {                                              \
                    ((PFN_i)VT(p_)[0xc / 4])(p_, 1);                             \
                    ((PFN_v)VT(p_)[4 / 4])(p_);                                  \
                }                                                                \
                ++i_;                                                            \
                n_ = (I(this_, (e)) - I(this_, (b))) >> 2;                       \
            } while (i_ < n_);                                                   \
        }                                                                        \
        int d_ = I(this_, (e)) - I(this_, (b));                                  \
        FUN_011e0744(*(void**)(this_ + (b)), *(void**)(this_ + (e)), 0);         \
        I(this_, (e)) = I(this_, (e)) - d_;                                      \
    } while (0)

    // ---- pointer vectors 0x78, 0x64, 0xb0 ----
    DRAIN(0x78, 0x7c);
    DRAIN(0x64, 0x68);
    DRAIN(0xb0, 0xb4);

    // ---- ten single effect handles ----
    RELS(0x60);
    RELS(0x90);
    RELS(0x94);
    RELS(0x8c);
    RELS(0x98);
    RELS(0x9c);
    RELS(0xa0);
    RELS(0xa4);
    RELS(0xa8);
    RELS(0xac);

    #undef RELS
    #undef DRAIN

    // ---- sound ----
    if (I(this_, 0x10) != 0)
        FUN_00e826e0(I(this_, 0x10));

    // ---- creature (+0x24), released through its own interface ----
    if (I(this_, 0x24) != 0) {
        void* c = (void*)I(this_, 0x24);
        void* iface = *(void**)((char*)c + 0x190);
        ((void(__thiscall*)(void*))VT(iface)[0x3c / 4])(c);
    }

    // ---- attachment +0x28 ----
    if (I(this_, 0x28) != 0) {
        void* a = (void*)I(this_, 0x28);
        ((PFN_i)VT(a)[0x16c / 4])(a, 0);
        a = (void*)I(this_, 0x28);
        if (a != 0) {
            I(this_, 0x28) = 0;
            if (I(a, 0x40) > 1) {
                I(a, 0x40) = I(a, 0x40) - 1;
            } else {
                ((PFN_sb)VT(a)[0x170 / 4])(a, (u32)I(a, 4) >> 31);
            }
        }
    }

    // ---- per-attachment slots at +0x2c + i*4 ----
    {
        char ref[4];
        FUN_00743b50_s00e6_5ad0(ref);
        char* att = (char*)FUN_00e4cc40(I(this_, 0x14), ref);
        int n = I(att, 0x18);
        if (n > 0) {
            char* base = *(char**)(att + 0x14);
            char* slot = this_ + 0x2c;
            for (int i = 0; i < n; ++i, slot += 4, base += 0x28) {
                int kind = I(base, 4);
                if (kind == 0) {
                    void* p = *(void**)slot;
                    if (p != 0) {
                        ((PFN_i)VT(p)[0x16c / 4])(p, 0);
                        if (I(p, 0x40) < 2)
                            ((PFN_sb)VT(p)[0x170 / 4])(p, (u32)I(p, 4) >> 31);
                        else
                            I(p, 0x40) = I(p, 0x40) - 1;
                    }
                } else if (kind == 1) {
                    void* p = *(void**)slot;
                    if (destroy == 0) {
                        int loc = (int)p;
                        FUN_00e65a00(&loc);
                    } else if (p != 0) {
                        ((PFN_i)VT(p)[0xc / 4])(p, 1);
                        ((PFN_v)VT(p)[4 / 4])(p);
                    }
                } else if (kind == 3) {
                    void* p = *(void**)slot;
                    if (p != 0) {
                        void* iface = *(void**)((char*)p + 0x190);
                        ((void(__thiscall*)(void*))VT(iface)[0x3c / 4])(p);
                    }
                }
            }
        }
        I(this_, 0x54) = 0;
        FUN_00e82130_s00e6_5ad0(ref);
    }
}

// @ 0x00e66010
void FUN_00e66010(int hCell, u8 destroy)
{
    char* cell = (char*)cells()->Get(hCell);
    int hParts = I(cell, 0x248);
    char* parts = (char*)((Pool_s00e6_5ad0*)(gspCellGfx + 0x168))->Get(hParts);
    if (I(cell, 0x35c) == I(gspCellGame_s00e6_5ad0, 0x4100))
        FUN_00e4f680(I(cell, 0x35c));
    I(cell, 0x248) = 0;
    FUN_00e65ad0(parts, destroy);
    ((Pool_s00e6_5ad0*)(gspCellGfx + 0x168))->Free(hParts);
    int n = I(cell, 0x250);
    if (n > 1) {
        int* q = (int*)(cell + 0x254);
        int cnt = n;
        do {
            FUN_00e4ec30(I(gspCellGame_s00e6_5ad0, 0x4108), *q);
            *q = -1;
            ++q;
            --cnt;
        } while (cnt != 0);
        I(cell, 0x250) = 0;
    } else {
        I(cell, 0x250) = 0;
    }
}

// @ 0x00e660e0
void FUN_00e660e0(int part, int owner)
{
    if (B(part, 0x112) != 0 &&
        FUN_00e57340((int)part) > 1 &&
        FUN_00e57340((int)part) < 3) {
        int* slot = (int*)(owner + 0xac);
        if (*slot == 0) {
            char* wp = (I(part, 0x35c) == I(gspCellGame_s00e6_5ad0, 0x40fc))
                     ? (gspCellGfx + 0x161c8)
                     : (gspCellGfx + 0x161bc);
            void* world = *(void**)wp;
            int old = *(volatile int*)(owner + 0xac);  // reload (cl would otherwise fold to 0)
            if (old != 0) {
                *slot = 0;
                ((PFN_v)VT(old)[4 / 4])((void*)old);
            }
            u32 id = FNV1_String8("cell_death_continuous", 0x811c9dc5, 1);
            CreateEffectSafe_s00e6_5ad0(world, id, 0, slot);
            void* e = (void*)*slot;
            ((PFN_i)VT(e)[8 / 4])(e, 0);
        }
        FUN_00e63480((void*)*slot, part + 0xc0, (void*)(part + 0x48));
    } else {
        if (I(owner, 0xac) != 0)
            FUN_00e65a00((int*)(owner + 0xac));
    }
}

// @ 0x00e661c0
void FUN_00e661c0(int* p)
{
    int beg = p[0], end = p[1];
    void* r = FUN_005f4e10((void*)end, (void*)end, (void*)beg);
    FUN_005f3680(r, (void*)p[1]);
    p[1] = p[1] - ((end - beg) >> 2) * 4;

    int beg2 = p[5], end2 = p[6];
    void* r2 = FUN_006f43e0((void*)end2, (void*)end2, (void*)beg2);
    FUN_0070f520(r2, (void*)p[6]);
    p[6] = p[6] - ((end2 - beg2) >> 2) * 4;

    int n = (p[0xb] - p[10]) >> 2;
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            void* obj = (void*)*(int*)(p[10] + i * 4);
            void* iface = *(void**)(gspCellGfx + 0x58);
            ((PFN_i)VT(iface)[0x3c / 4])(iface, (int)obj);
        }
    }
    FUN_011e0744((void*)p[10], (void*)p[0xb], 0);
    p[0xb] = p[10];
}

// @ 0x00e66280
void FUN_00e66280(int a, int b)
{
    if ((a | b) == 0)
        return;

    void* mgr = FUN_0067ddd0();
    EffEntry buf[0x80];
    typedef int (__thiscall *PFN_mgr)(void*, int, int, void*, int);
    PFN_mgr fn = *(PFN_mgr*)((char*)VT(mgr) + 0x6c);
    int count = fn(mgr, a, b, buf, 0x80);
    if (count <= 0)
        return;

    EffEntry* e = buf;
    do {
        switch (e->type) {
        case 0x12:
            FUN_00e66280(e->a, e->b);
            break;
        case 0: {
            int x = e->a, y = e->b;
            void* obj = FUN_0067dd60();
            typedef void* (__thiscall *PFN_20)(void*, int, int, int);
            void* res = ((PFN_20)VT(obj)[0x20 / 4])(obj, x, y, 0);
            ((RefVecOwner*)gspCellGfx)->push(res);
            break;
        }
        case 2:
            FUN_00e65410(e->a, 0);
            break;
        case 0x102: {
            void* iface = *(void**)(gspCellGfx + 0x54);
            typedef void* (__thiscall *PFN_c)(void*, int, int, int);
            void* obj = ((PFN_c)VT(iface)[0xc / 4])(iface, e->a, 0, 0);
            if (obj != 0) {
                I(obj, 0x40) = I(obj, 0x40) + 1;
                ((cCellGfxStub*)gspCellGfx)->pushObj(obj);
                int rc = I(obj, 0x40);
                if (rc > 1) {
                    I(obj, 0x40) = rc - 1;
                } else {
                    ((PFN_sb)VT(obj)[0x170 / 4])(obj, ((u32)I(obj, 4) >> 31) & 1);
                }
            }
            break;
        }
        default:
            break;
        }
        ++e;
        --count;
    } while (count != 0);
}

// @ 0x00e663b0
void FUN_00e663b0(int map, int key)
{
    if (key == 0)
        return;

    void* out;
    char* m = (char*)map;
    ((RbTree*)m)->find(&out, (const unsigned*)&key);
    if (*(int*)out != (map + 4))
        return;

    int* val = (int*)((RbTree*)m)->operatorIndex(&key);
    *val = 1;

    char ref1[4];
    FUN_00743b50_s00e6_5ad0(ref1);
    char* a = (char*)FUN_00e4cc40(key, ref1);
    char ref2[4];
    FUN_00743b50_s00e6_5ad0(ref2);
    char* b = (char*)FUN_00e4cc40(*a, ref2);

    int n = I(b, 0x18);
    for (int i = 0; i < n; ++i) {
        char* desc = *(char**)(b + 0x14) + i * 0x28;
        int kind = I(desc, 4);
        if (kind == 0) {
            void* iface = *(void**)(gspCellGfx + 0x54);
            typedef void* (__thiscall *PFN_c)(void*, int, int, int);
            void* obj = ((PFN_c)VT(iface)[0xc / 4])(iface, I(desc, 0x10), 0, 0);
            if (obj != 0) {
                I(obj, 0x40) = I(obj, 0x40) + 1;
                ((cCellGfxStub*)gspCellGfx)->pushObj(obj);
                int rc = I(obj, 0x40);
                if (rc < 2)
                    ((PFN_sb)VT(obj)[0x170 / 4])(obj, (u32)I(obj, 4) >> 31);
                else
                    I(obj, 0x40) = rc - 1;
            }
        } else if (kind == 1) {
            FUN_00e66280(I(desc, 0x10), 0);
        } else if (kind == 3) {
            FUN_00e64980(I(desc, 0x10));
        }
    }

    for (int i = 0; i < 5; ++i)
        FUN_00e66280(I(b, i * 4), 0);

    FUN_00e663b0(map, val[0x37]);
    FUN_00e663b0(map, val[0x34]);
    FUN_00e663b0(map, val[0x33]);
    if (val[0x92] == 0x1008)
        FUN_00e663b0(map, val[0xaa]);
    if (val[0x38] == 0x1008)
        FUN_00e663b0(map, val[0x50]);
    if (val[0x65] == 0x1008)
        FUN_00e663b0(map, val[0x7d]);

    FUN_00e4fc20(map, val[0x35]);
    FUN_00e4fc20(map, val[0x32]);
    FUN_00e4fc20(map, val[0x36]);

    FUN_00e82130_s00e6_5ad0(ref1);
    FUN_00e82130_s00e6_5ad0(ref2);
}

// @ 0x00e665c0
void FUN_00e665c0(int map, int id)
{
    char ref[4];
    FUN_00743b50_s00e6_5ad0(ref);
    char* list = (char*)FUN_00e4cc40(id, ref);
    int n = I(list, 8);
    if (n > 0) {
        char* base = *(char**)(list + 0xc);
        for (int i = 0; i < n; ++i, base += 0x4c) {
            int sel = I(base, 0x28);
            switch (sel) {
            case 0:
                FUN_00e663b0(map, I(base, 0x18));
                break;
            case 1:
                FUN_00e663b0(map, I(base, 0x1c));
                break;
            case 3:
                FUN_00e665c0(map, I(base, 0x20));
                break;
            case 2: {
                int sub = I(base, 0x24);
                if (sub == 0) {
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(10));
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(0xb));
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(0xc));
                } else if (sub == 1) {
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(0xd));
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(0xe));
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(0xf));
                } else if (sub == 2) {
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(0x10));
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(0x11));
                    FUN_00e663b0(map, (int)FUN_00e4cce0_s00e6_5ad0(0x12));
                }
                break;
            }
            default:
                break;
            }
        }
    }
    FUN_00e82130_s00e6_5ad0(ref);
}

// @ 0x00e666f0
void FUN_00e666f0(void)
{
    // local eastl map/tree (anchor at +0, root at +4)
    struct LocalMap {
        void* anchor;   // +0
        void* root;     // +4
        void* node;     // +8
        int   pad0c;
        char  flag;     // +0x10
        char  pad11[0x1c - 0x11];
    } lm;
    lm.anchor = &lm.anchor;
    lm.node = 0;
    lm.pad0c = 0;
    lm.flag = 0;
    lm.root = 0;

    char ref[4];
    FUN_00743b50_s00e6_5ad0(ref);
    char* info = (char*)FUN_00e4ce40(ref);
    FUN_00e663b0((int)&lm.anchor, I(info, 0x34));

    char* cur = info + 4;
    for (int k = 5; k != 0; --k, cur += 4) {
        char ref2[4];
        FUN_00743b50_s00e6_5ad0(ref2);
        char* lst = (char*)FUN_00e4cc40(I(cur, 0), ref2);
        int n = I(lst, 0);
        if (n > 0) {
            char* base = *(char**)(lst + 4);
            for (int i = 0; i < n; ++i, base += 0xc)
                FUN_00e665c0((int)&lm.anchor, I(base, 0));
        }
        FUN_00e82130_s00e6_5ad0(ref2);
    }

    FUN_00e663b0((int)&lm.anchor, (int)FUN_00e4cce0_s00e6_5ad0(1));
    FUN_00e663b0((int)&lm.anchor, (int)FUN_00e4cce0_s00e6_5ad0(2));
    FUN_00e663b0((int)&lm.anchor, (int)FUN_00e4cce0_s00e6_5ad0(4));
    FUN_00e663b0((int)&lm.anchor, (int)FUN_00e4cce0_s00e6_5ad0(8));
    FUN_00e4fc20((int)&lm.anchor, (int)FUN_00e4cce0_s00e6_5ad0(7));

    FUN_00e82130_s00e6_5ad0(ref);

    // drain the sub-tree
    void* node = lm.root;
    while (node != 0) {
        FUN_009a9600(&lm.anchor, *(void**)node);
        void* next = *(void**)((char*)node + 4);
        FUN_00f47380(node);
        node = next;
    }
}

// @ 0x00e66840
int* FUN_00e66840(int cell, u32 id)
{
    char* wp = (I(cell, 0x35c) == I(gspCellGame_s00e6_5ad0, 0x40fc))
             ? (gspCellGfx + 0x161c8)
             : (gspCellGfx + 0x161bc);
    void* world = *(void**)wp;

    EffDesc d;
    FUN_00e619a0(&d);
    XForm xf;
    xf.assign((void*)(cell + 0x48));

    d.pos = gCellWorldCenter;
    d.scale = g_one_1485720;
    memcpy(&d.m, g_16b3dac, 36);
    d.a = 0;
    d.b = 0;

    int* effect;                 // original reads this uninitialised local before the create
    int* old = effect;
    if (old != 0) {
        effect = 0;
        ((PFN_v)VT(old)[4 / 4])(old);
    }
    CreateEffectSafe_s00e6_5ad0(world, id, 0, &effect);

    // append to the object vector at gspCellGfx + 0x161dc (0x74-byte elements)
    char* g = gspCellGfx;
    char* pos = *(char**)(g + 0x161e0);
    if (pos < *(char**)(g + 0x161e4)) {
        *(char**)(g + 0x161e0) = pos + 0x74;
        if (pos != 0)
            ((Obj74*)pos)->ctor(&d);
    } else {
        ((ObjVec74*)(g + 0x161dc))->insertGrow(pos, &d);
    }

    ((PFN_vp)VT(effect)[0x18 / 4])(effect, (void*)(cell + 0x48));
    ((PFN_i)VT(effect)[8 / 4])(effect, 0);
    int* ret = effect;
    if (effect != 0)
        ((PFN_v)VT(effect)[4 / 4])(effect);
    return ret;
}

// @ 0x00e66980
void FUN_00e66980(void)
{
    FUN_007c3ba0(g_16b42b8);
    char* g = gspCellGfx;
    int it = ((Pool_s00e6_6980*)(g + 0x168))->Begin();
    void* o = ((Pool_s00e6_6980*)(g + 0x168))->Next(&it);
    while (o != 0) {
        FUN_00e65ad0(o, 1);            // SP::cPartGfx::Clear(1)
        g = gspCellGfx;
        o = ((Pool_s00e6_6980*)(g + 0x168))->Next(&it);
    }
    ((Pool_s00e6_6980*)(g + 0x168))->Reset();
    g = gspCellGfx;
    int n = (I(g, 0x161e0) - I(g, 0x161dc)) / 0x74;
    for (int i = 0; i < n; ++i) {
        void** slot = (void**)(I(g, 0x161dc) + i * 0x74 + 0x70);
        void* p = *slot;
        VCall_i(p, 0xc, 1);
        p = *slot;
        if (p) { *slot = 0; VCall_v(p, 4); }
    }
    FUN_00e65180(P(g, 0x161dc), P(g, 0x161e0));
    for (int off = 0x5c; off < 0x15c; off += 4) {
        void** slot = (void**)(g + off);
        if (*slot != 0) {
            VCall_i(*slot, 0xc, 1);
            void* p = *slot;
            if (p) { *slot = 0; VCall_v(p, 4); }
        }
    }
    VCall_i(FUN_0067dd90(), 0x20, 0x4a4d97f);
    ReleaseSlot(g, 0x161a0);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010000);
    ReleaseSlot(g, 0x161b4);
    FUN_00e82750(P(g, 0x161b0));
    ReleaseSlot(g, 0x161b0);
    VCall_v(P(g, 0x161c4), 0x20);
    ReleaseSlot(g, 0x161c4);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010011);
    ReleaseSlot(g, 0x161bc);
    FUN_00e82750(P(g, 0x161b8));
    ReleaseSlot(g, 0x161b8);
    VCall_i(FUN_0067dd80(), 0x18, 0x1010010);
    ReleaseSlot(g, 0x161c0);
    VCall_i(FUN_0067dd80(), 0x18, 0x1010015);
    ReleaseSlot(g, 0x161a8);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010016);
    ReleaseSlot(g, 0x161ac);
    FUN_00e82750(P(g, 0x161a4));
    ReleaseSlot(g, 0x161a4);
    VCall_v(P(g, 0x161d0), 0x20);
    ReleaseSlot(g, 0x161d0);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010021);
    ReleaseSlot(g, 0x161c8);
    VCall_i(FUN_0067dd80(), 0x18, 0x1010020);
    ReleaseSlot(g, 0x161cc);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010031);
    ReleaseSlot(g, 0x161d4);
    FUN_00e82750(P(g, 0x161d8));
    ReleaseSlot(g, 0x161d8);
    if (I(g, 0x3c) != 0) {
        FUN_007b1950(P(g, 0x3c));
        ReleaseSlot(g, 0x3c);
    }
}

// @ 0x00e66dd0
int FUN_00e66dd0(int a, int b)
{
    int h = ((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0xc4))->Alloc();
    char* obj = (char*)((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0xc4))->Get(h);
    *(int*)(obj + 4) = a;
    *(int*)(obj + 8) = b;
    *(float*)(obj + 0x24) = 0.0f;
    int key = MakeKey(a, b);
    int* r = ((KeyMap*)(gspCellGame_s00e6_6980 + 0xe0))->operatorIndex((KPair*)&key);
    *r = h;
    return (int)obj;
}

// @ 0x00e66e50
int FUN_00e66e50(int a, int b)
{
    int key = MakeKey(a, b);
    KeyMap* map = (KeyMap*)(gspCellGame_s00e6_6980 + 0xe0);
    KPair* e = (KPair*)FUN_00b41ea0(map->mpBegin, map->mpEnd, &key, map->mbFlag);
    if (e == map->mpEnd || key < e->key) e = map->mpEnd;
    if (e != map->mpEnd) {
        int* slot = ((KeyMap*)(gspCellGame_s00e6_6980 + 0xe0))->operatorIndex((KPair*)&key);
        char* obj = (char*)((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0xc4))->GetSafe(*slot);
        if (obj != 0 && *(int*)(obj + 4) == a && *(int*)(obj + 8) == b)
            return (int)obj;
        ((KeyMap*)(gspCellGame_s00e6_6980 + 0xe0))->erase((KPair*)&key);
    }
    return 0;
}

// @ 0x00e66f30
void FUN_00e66f30(int a, int b, void* pos, float p4, float p5, float p6, float p7, float p8)
{
    if ((u32)a < (u32)b) {
        p4 = p4 * g_minus1;
        p5 = p5 * g_minus1;
        p6 = p6 * g_minus1;
    }
    int lo = a < b ? a : b;
    int hi = a < b ? b : a;
    char* esi = (char*)FUN_00e58c50((char*)&hi);
    char* edi = (char*)FUN_00e58c50((char*)&lo);
    int* rec = (int*)FUN_00e66e50(hi, lo);
    float dot = (F(esi, 0x50) - F(edi, 0x50)) * p8
              + (F(esi, 0x54) - F(edi, 0x54)) * p7
              + (F(esi, 0x4c) - F(edi, 0x4c)) * p6;
    if (dot > 0.0f) {
        if (rec != 0) {
            ((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0xc4))->Free(*rec);
            FUN_00e65480(hi, lo);
            return;
        }
    } else {
        if (rec == 0)
            rec = (int*)FUN_00e66dd0(hi, lo);
        float s0 = F(esi, 0xbc);
        float s1 = F(edi, 0xbc);
        rec[3] = I(pos, 0);
        rec[4] = I(pos, 4);
        rec[5] = I(pos, 8);
        rec[6] = *(int*)&p4;
        rec[7] = *(int*)&p5;
        rec[8] = *(int*)&p6;
        int v = I(gspCellGame_s00e6_6980, 0x5160);
        float inv = 1.0f / (s1 + s0);
        rec[0xc] = *(int*)&inv;
        rec[0xd] = *(int*)&inv;
        rec[0xf] = v;
        float n7 = -p7;
        rec[9] = *(int*)&n7;
        float adj = n7 + g_0p1_1488874;
        float pick = (0.0f <= adj) ? 0.0f : adj;
        float res = (pick / p8) * g_neg0p1_13eb964;
        rec[0xe] = *(int*)&res;
    }
}

// @ 0x00e67100
void FUN_00e67100(int hA, int hB, void* pos, float p2, float p3, float p4, float p5, float p6)
{
    char* A = (char*)((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0x1c))->GetSafe(hA);
    char* B = (char*)((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0x1c))->GetSafe(hB);
    if (A == 0) return;
    if (B == 0) return;
    if (B(A, 0x179) == 1) return;
    if (B(B, 0x179) == 1) return;
    if (I(A, 0x36c) == hB) return;
    if (I(B, 0x36c) == hA) return;
    if (I(A, 0x184) == hB) return;
    if (I(B, 0x184) == hA) return;
    if (B(A, 0x114) == 1) return;
    if (B(B, 0x114) == 1) return;
    FUN_00e66f30((int)B, (int)A, pos, p2, p3, p4, p5, p6);
}

// @ 0x00e671c0
void FUN_00e671c0(void* cellp)
{
    char* cell = (char*)cellp;
    char* obj = (char*)operator_new(0x202c, "Simulator/Cell/Bomb", 0, 0, 0, 0);
    if (obj != 0) {
        *(void**)(obj + 0x20) = obj + 0x28;
        *(void**)(obj + 0x14) = obj + 0x28;
        *(void**)(obj + 0x10) = obj + 0x28;
        *(void**)(obj + 0x18) = obj + 0x28 + 0x2000;
    } else {
        obj = 0;
    }
    *(int*)(obj + 0) = I(cell, 0x35c);
    *(int*)(obj + 4) = I(cell, 0x4c);
    *(int*)(obj + 8) = I(cell, 0x50);
    *(int*)(obj + 0xc) = I(cell, 0x54);
    int* slot = (int*)FUN_00e65840(obj + 0x10, cell);
    *slot = I(cell, 0);
    int h = ((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0x54))->Alloc();
    char* m = (char*)((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0x54))->Get(h);
    *(int*)(m + 0x28) = I(cell, 0);
    *(float*)(m + 0x1c) = g_half;
    *(float*)(m + 0x20) = g_half;
    *(int*)(m + 0x24) = 0x10;
    *(int*)(m + 0x2c) = 0;
    *(int*)(m + 0x30) = -1;
    *(int*)(m + 0x34) = -1;
    *(int*)(m + 0x38) = 0;
    *(int*)(m + 0x3c) = 0;
    *(float*)(m + 0x40) = 0.0f;
    *(float*)(m + 0x44) = 0.0f;
    char* src = cell + 0x4c;
    float* sp = (float*)src;
    if (sp == 0) sp = &gCellWorldCenter_s00e6_6980.x;
    *(int*)(m + 0x48) = I(sp, 0);
    *(int*)(m + 0x4c) = I(sp, 4);
    *(int*)(m + 0x50) = I(sp, 8);
    *(int*)(m + 0x54) = I(&gCellWorldCenter_s00e6_6980, 0);
    *(int*)(m + 0x58) = I(&gCellWorldCenter_s00e6_6980, 4);
    *(int*)(m + 0x5c) = I(&gCellWorldCenter_s00e6_6980, 8);
    *(int*)(m + 0x60) = I(g_15a7c4c, 0);
    *(int*)(m + 0x64) = I(g_15a7c4c, 4);
    *(int*)(m + 0x68) = I(g_15a7c4c, 8);
    *(int*)(m + 0x6c) = I(g_15a7c4c, 0xc);
    *(void**)(m + 0x70) = obj;
    *(u8*)(m + 0x74) = 0;
    *(int*)(m + 0x78) = 0;
    *(int*)(m + 4) = 0;
    *(u8*)(m + 8) = 0;
    int key = 0x62a981ec;
    int flag = (I(cell, 0x35c) != I(gspCellGame_s00e6_6980, 0x40fc));
    FUN_00e61b90(flag, 0, src, &key);
}

// @ 0x00e67330
void FUN_00e67330(int a, int b, float* pos, float radius, int soundId)
{
    if (!(pos[0] >= F(&gCellGameExtents, 0x00) && pos[0] <= F(&gCellGameExtents, 0x0c) &&
          pos[1] >= F(&gCellGameExtents, 0x04) && pos[1] <= F(&gCellGameExtents, 0x10) &&
          pos[2] >= F(&gCellGameExtents, 0x08) && pos[2] <= F(&gCellGameExtents, 0x14)))
        return;
    char ref[4];
    FUN_00743b50_s00e6_6980(ref);
    char* info = (char*)FUN_00e4ce40(ref);
    if (radius < F(info, 0x6c)) {
        FUN_00e82130_s00e6_6980(ref);
        return;
    }
    int key = MakeKey(a, b);
    SoundMap* map = (SoundMap*)(gspCellGfx + 0x184);
    KPair* e = (KPair*)FUN_00e61830(map->mpBegin, map->mpEnd, &key, map->mbFlag);
    if (e == map->mpEnd || key < e->key) e = map->mpEnd;
    if (e != *(KPair**)(gspCellGfx + 0x188)) {
        int* rec = (int*)((SoundMap*)(gspCellGfx + 0x184))->operatorIndex((KPair*)&key);
        rec[3] = soundId;
        rec[4] = I(pos, 0);
        rec[5] = I(pos, 4);
        rec[6] = I(pos, 8);
        FUN_00e82130_s00e6_6980(ref);
        return;
    }
    int* rec = (int*)((SoundMap*)(gspCellGfx + 0x184))->operatorIndex((KPair*)&key);
    rec[1] = b;
    rec[2] = soundId;
    rec[3] = soundId;
    rec[0] = a;
    *(u8*)((char*)rec + 0x1c) = radius < F(info, 0x70) ? 1 : 0;
    rec[4] = I(pos, 0);
    rec[5] = I(pos, 4);
    rec[6] = I(pos, 8);
    rec[9] = 0;
    rec[8] = 0;
    FUN_00e82130_s00e6_6980(ref);
}

// @ 0x00e67510
void FUN_00e67510(int world, int* ppEffect, int a3, int a4, int a5, int a6, char create)
{
    if (create != 0) {
        if (*ppEffect == 0) {
            u32 id = FNV1_String8_s00e6_6980("cell_eyegoo_flow", 0x811c9dc5, 1);
            CreateEffectSafe_s00e6_6980((void*)world, id, 0, ppEffect);
            void* e = (void*)*ppEffect;
            ((PFN_i)VT(e)[8 / 4])(e, 0);
        }
        EffDesc_s00e6_6980 d;
        d.a = 0;
        d.b = 0;
        d.pos.x = gCellWorldCenter_s00e6_6980.x;
        d.pos.y = gCellWorldCenter_s00e6_6980.y;
        d.pos.z = gCellWorldCenter_s00e6_6980.z;
        d.scale = g_one_1485720;
        d.rot.Assign((void*)0x16b3dac);
        FUN_00e84150(a5, a6, &d);
        FUN_00e63480((void*)*ppEffect, a3, &d);
        return;
    }
    if (*ppEffect != 0)
        FUN_00e65a00(ppEffect);
}

// @ 0x00e675f0
void FUN_00e675f0(void)
{
    char* c = (char*)((Pool_s00e6_6980*)(gspCellGame_s00e6_6980 + 0x1c))->GetSafe(I(gspCellGame_s00e6_6980, 0x411c));
    if (c != 0)
        FUN_00e671c0(c);
}

// @ 0x00e67610
void FUN_00e67610(int id)
{
    char ref[4];
    FUN_00743b50_s00e6_6980(ref);
    int* list = (int*)FUN_00e4cc40(id, ref);
    for (int i = 0; i < *list; ++i)
        FUN_00e66280_s00e6_6980(*(int*)(list[1] + i * 0x1c), 0);
    FUN_00e82130_s00e6_6980(ref);
}

// @ 0x00e67670
void FUN_00e67670(void)
{
    u32 h;
    h = FNV1_String8_s00e6_6980("cell_dof_distort_blind", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_dof_distort_blind", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_background_color", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_propulsionJet", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_propulsionCilia", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_propulsionFlagella", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_attack_electrical_charged", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_attack_electrical_charged_multiple", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_call_avatar", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_call_mate", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("EDT_currency_text_cell_sellItem", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("EDT_currency_text_cell_buyItem", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_egg_L0_autohatch", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_attack_electrical_secondaryBeam", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_attack_electrical_primaryBeam", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_death_continuous", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_death_oneshot_small", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_death_oneshot_large", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_death_oneshot", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_death_break", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
    h = FNV1_String8_s00e6_6980("cell_death_eaten", 0x811c9dc5, 1); FUN_00e66280_s00e6_6980(h, 0);
}

// @ 0x00e67890
void FUN_00e67890(int param_1)
{
  int iVar1 = param_1;
  int iVar5 = 0;
  switch (FUN_00e57340(param_1)) {
    case 0: case 1: iVar5 = 1; break;
    case 2: case 3: iVar5 = 0; break;
    case 4: iVar5 = 2; break;
  }
  char o1[4];
  ((ObjHolder*)o1)->Init();
  char* r = (char*)FUN_00e823a0(*(int*)(iVar1 + 0x108), o1);
  char o2[4];
  ((ObjHolder*)o2)->Init();
  char* e = (char*)FUN_00e823a0(*(int*)r, o2);
  if (*(int*)(e + iVar5 * 4) == 0) iVar5 = 0;
  int v = *(int*)(e + iVar5 * 4);
  if (v != 0) FUN_00e66840(iVar1, v);
  ((ObjHolder*)o2)->Cleanup();
  ((ObjHolder*)o1)->Cleanup();
}

// @ 0x00e67940
int RbTree_s00e6_7890::Insert(int* key)
{
  char* self = (char*)this;
  char* head = self + 4;
  char* cand = head;
  char* n = *(char**)(self + 0xc);
  if (n != 0) {
    do {
      if (*(int*)(n + 0x10) < *key) {
        n = *(char**)n;
      } else {
        cand = n;
        n = *(char**)(n + 4);
      }
    } while (n != 0);
  }
  if (cand != head && *(int*)(cand + 0x10) <= *key) {
    return (int)(cand + 0x14);
  }
  int buf[0x2528 / 4];
  char* b = (char*)buf;
  int* slot = (int*)(b + 0x12a0);
  *slot = *key;
  FUN_00e62a20(b + 0x12a8);
  FUN_00e658a0(b, cand, slot, *(unsigned*)b);
  return (int)(b + 0x14);
}

// @ 0x00e679e0
int FUN_00e679e0(CellKey key)
{
  char* base = (char*)gspCellGame;
  char out[4];
  int local = key.a;
  void* it = ((MapTree*)(base + 0x70))->Find(out, &local);
  local = key.a;
  if (*(int*)it != (int)(base + 0x74)) {
    return ((RbTree_s00e6_7890*)(base + 0x70))->Insert(&local);
  }
  int r = ((RbTree_s00e6_7890*)(base + 0x70))->Insert(&local);
  FUN_00e83e30(r, r + 4, &key);
  FUN_00e52060(r + 4, 0);
  return r;
}

// @ 0x00e67a60
char FUN_00e67a60()
{
  char* m = *(char**)((char*)gspCellGame + 0x5190);
  char* r = (char*)FUN_00e679e0(*(CellKey*)(m + 0x10));
  return 0 < *(int*)(r + 0x1210);
}

// @ 0x00e67aa0
char FUN_00e67aa0()
{
  char* m = *(char**)((char*)gspCellGame + 0x5190);
  char* r = (char*)FUN_00e679e0(*(CellKey*)(m + 0x10));
  return 0 < *(int*)(r + 0x120c);
}

// @ 0x00e67ae0
int FUN_00e67ae0(int param_1)
{
  if (param_1 == 0) {
    char* m = *(char**)((char*)gspCellGame + 0x5190);
    char* r = (char*)FUN_00e679e0(*(CellKey*)(m + 0x10));
    if (*(int*)(r + 0x120c) > 0) return 0;
  } else if (param_1 == 4) {
    char* m = *(char**)((char*)gspCellGame + 0x5190);
    char* r = (char*)FUN_00e679e0(*(CellKey*)(m + 0x10));
    if (*(int*)(r + 0x120c) <= 0) return 0;
    if (FUN_00e67a60()) return 0;
    param_1 = 0;
  } else if (param_1 == 5) {
    if (!FUN_00e67aa0()) return 0;
    if (!FUN_00e67a60()) return 0;
    param_1 = 0;
  }
  char* m = *(char**)((char*)gspCellGame + 0x5190);
  switch (*(int*)(m + param_1 * 0x10 + 0x80)) {
    case 0: return 0;
    case 1: return param_1 != 3;
    case 2: return 2;
    case 3: if (0.0f < *(float*)(m + param_1 * 0x10 + 0x8c)) return 2; break;
  }
  return 0;
}

// @ 0x00e67be0
void FUN_00e67be0(float param_1)
{
  int i = 0;
  int off = 0;
  do {
    char* base = *(char**)((char*)gspCellGame + 0x5190);
    float* p = (float*)(base + off + 0x8c);
    if (0.0f < *p) *p = *p - param_1;
    FUN_00e4fe90(i, FUN_00e67ae0(i));
    off += 0x10;
    ++i;
  } while (off < 0x60);
}

// @ 0x00e67c40
int FUN_00e67c40(int param_1, int param_2)
{
  if (*(int*)(param_1 + 0xfc) == 0) return 1;
  if (*(int*)(FUN_00e52910(param_2) + 0x10) != 0) {
    return *(int*)(FUN_00e52910(param_2) + 0x10);
  }
  char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  return *(int*)(r + 0x1254);
}

// @ 0x00e67cb0
void FUN_00e67cb0(int param_1, float* param_2)
{
  if (*(int*)(param_1 + 0xfc) == 0) {
    float one = kf1485720;
    param_2[0] = one;
    param_2[1] = one;
    param_2[2] = one;
    param_2[3] = one;
    return;
  }
  char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  param_2[0] = *(float*)(r + 0x1258);
  param_2[1] = *(float*)(r + 0x1258);
  param_2[2] = *(float*)(r + 0x1258);
  param_2[3] = *(float*)(r + 0x1258);
}

// @ 0x00e67d30
float* FUN_00e67d30(float* out, int cell, int idx)
{
  if (*(int*)(cell + 0x248) == 0) {
    FUN_00e5eb20(out, cell);
    return out;
  }
  if (*(int*)(cell + 0xfc) == 0) {
    FUN_00e5eb20(out, cell);
    return out;
  }
  if (idx == -1) {
    FUN_00e5eb20(out, cell);
    return out;
  }
  {
    char* r = (char*)FUN_00e679e0(*(CellKey*)(cell + 0xfc));
    float n34 = -kf15a7c34;
    float n38 = -kf15a7c38;
    float n3c = -kf15a7c3c;
    float* m = (float*)(r + idx * 0x48 + 0x18);
    float vx = (m[3] * n38 + m[6] * n3c) + m[0] * n34;
    float vy = (m[4] * n38 + m[1] * n34) + m[7] * n3c;
    float vz = (m[5] * n38 + m[2] * n34) + m[8] * n3c;
    float f3 = vx, f4 = vy, f5 = vz;
    if (*(unsigned char*)(cell + 0x48) & 2) {
      float c00 = *(float*)(cell + 0x5c), c01 = *(float*)(cell + 0x60), c02 = *(float*)(cell + 0x64);
      float c10 = *(float*)(cell + 0x68), c11 = *(float*)(cell + 0x6c), c12 = *(float*)(cell + 0x70);
      float c20 = *(float*)(cell + 0x74), c21 = *(float*)(cell + 0x78), c22 = *(float*)(cell + 0x7c);
      f3 = (c20 * vz + c10 * vy) + c00 * vx;
      f4 = (c21 * vz + c11 * vy) + c01 * vx;
      f5 = (c22 * vz + c12 * vy) + c02 * vx;
    }
    out[0] = f3;
    out[1] = f4;
    out[2] = f5;
    return out;
  }
}

// @ 0x00e67ec0
float* FUN_00e67ec0(float* out, int cell, int idx)
{
  if (*(int*)(cell + 0x248) == 0) {
    out[0] = *(float*)(cell + 0x4c);
    out[1] = *(float*)(cell + 0x50);
    out[2] = *(float*)(cell + 0x54);
    return out;
  }
  if (*(int*)(cell + 0xfc) == 0) {
    out[0] = *(float*)(cell + 0x4c);
    out[1] = *(float*)(cell + 0x50);
    out[2] = *(float*)(cell + 0x54);
    return out;
  }
  if (idx == -1) {
    out[0] = *(float*)(cell + 0x4c);
    out[1] = *(float*)(cell + 0x50);
    out[2] = *(float*)(cell + 0x54);
    return out;
  }
  {
    char* r = (char*)FUN_00e679e0(*(CellKey*)(cell + 0xfc));
    float vx = *(float*)(r + idx * 0x48 + 0x0c);
    float vy = *(float*)(r + idx * 0x48 + 0x10);
    float vz = *(float*)(r + idx * 0x48 + 0x14);
    if (*(unsigned char*)(cell + 0x48) & 2) {
      float c00 = *(float*)(cell + 0x5c), c01 = *(float*)(cell + 0x60), c02 = *(float*)(cell + 0x64);
      float c10 = *(float*)(cell + 0x68), c11 = *(float*)(cell + 0x6c), c12 = *(float*)(cell + 0x70);
      float c20 = *(float*)(cell + 0x74), c21 = *(float*)(cell + 0x78), c22 = *(float*)(cell + 0x7c);
      float nx = (c10 * vy + c20 * vz) + c00 * vx;
      float ny = (c11 * vy + c01 * vx) + c21 * vz;
      float nz = (c12 * vy + c02 * vx) + c22 * vz;
      vx = nx; vy = ny; vz = nz;
    }
    float s = *(float*)(cell + 0x58);
    out[0] = *(float*)(cell + 0x4c) + s * vx;
    out[1] = *(float*)(cell + 0x50) + s * vy;
    out[2] = *(float*)(cell + 0x54) + s * vz;
    return out;
  }
}

// @ 0x00e68000
void FUN_00e68000(int cell, int idx, cSPTransform_s00e6_7890* out)
{
  if (idx == -1) {
    out->Assign(*(cSPTransform_s00e6_7890*)((char*)cell + 0x48));
    return;
  }
  if (*(int*)(cell + 0x248) != 0 && *(int*)(cell + 0xfc) != 0) {
    void* q = ((ResMap*)(gspCellGfx + 0x168))->Find(*(unsigned int*)(cell + 0x248));
    int p = *(int*)((char*)q + 0x24);
    if (p != 0) {
      FUN_00e84150(p, idx, out);
      char* r = (char*)FUN_00e679e0(*(CellKey*)(cell + 0xfc));
      float a = *(float*)(r + idx * 0x48 + 0x40);
      float b = *(float*)(r + idx * 0x48 + 0x44);
      float c = *(float*)(r + idx * 0x48 + 0x48);
      if (out->flags & 2) {
        float nx = out->rot[3] * b + out->rot[6] * c + out->rot[0] * a;
        float ny = out->rot[1] * a + out->rot[4] * b + out->rot[7] * c;
        a = nx; b = ny;
      }
      out->tx = out->tx + out->scale * a;
      out->ty = out->ty + out->scale * b;
      out->tz = out->tz;
      out->modCount++;
      out->flags |= 4;
      return;
    }
  }
  out->Assign(*(cSPTransform_s00e6_7890*)((char*)cell + 0x48));
}

// @ 0x00e68170
void FUN_00e68170(int cell)
{
  float l4c, l48, l44, l40;
  float dir[3];
  float tmp[4];
  float q1[4];
  float q2[4];
  if (*(int*)(cell + 0x170) != 0) {
    void* t = ((CellPool*)((char*)gspCellGame + 0x1c))->Get(*(unsigned int*)(cell + 0x170));
    if (t != 0) {
      char* tp = (char*)t;
      l44 = *(float*)(tp + 0x54) - *(float*)(cell + 0x54);
      l48 = *(float*)(tp + 0x50) - *(float*)(cell + 0x50);
      l4c = *(float*)(tp + 0x4c) - *(float*)(cell + 0x4c);
      float inv = 1.0f / (float)sqrt((double)((l4c * l4c + l48 * l48) + l44 * l44) + kf13ec4b8);
      l4c = inv * l4c;
      l44 = l44 * inv;
      l48 = l48 * inv;
      if ((l44 * l44 + l48 * l48) + l4c * l4c <= kf14851ec) return;
      l4c = -l4c; l48 = -l48; l44 = -l44;
      dir[0] = l4c; dir[1] = l48; dir[2] = l44;
      SP_QuaternionFromFacingAndUp(q1, dir, &kf15a7c40);
      *(float*)(cell + 0x14) = q1[0];
      *(float*)(cell + 0x18) = q1[1];
      *(float*)(cell + 0x1c) = q1[2];
      *(float*)(cell + 0x20) = q1[3];
      if (*(int*)(cell + 0x174) == 0) return;
      float* pf = FUN_00e67ec0(dir, cell, *(int*)(cell + 0x174));
      l4c = *(float*)(tp + 0x4c) - pf[0];
      l48 = *(float*)(tp + 0x50) - pf[1];
      l44 = *(float*)(tp + 0x54) - pf[2];
      SP_normalized_safe(tmp, &l4c);
      FUN_00e67d30(q2, cell, *(int*)(cell + 0x174));
      float ang = FUN_006994a0(q2, tmp, &kf15a7c40);
      if (kf15a7c24 <= ang) ang = ang - kf16b3dd0;
      ang = (ang * kf1488874) * kf1471064;
      float sn = (float)sin((double)ang);
      float cs = (float)cos((double)ang);
      float axis[4];
      axis[0] = sn * kf15a7c40;
      axis[1] = sn * kf15a7c44;
      axis[2] = sn * kf15a7c48;
      axis[3] = cs;
      float* rr = FUN_0046d660(q1, (float*)(cell + 0x5c), axis);
      float* qq = FUN_007dcb00(q2, rr);
      *(float*)(cell + 0x14) = qq[0];
      *(float*)(cell + 0x18) = qq[1];
      *(float*)(cell + 0x1c) = qq[2];
      *(float*)(cell + 0x20) = qq[3];
      return;
    }
    *(int*)(cell + 0x170) = 0;
  }
  l4c = *(float*)(cell + 8) - *(float*)(cell + 0x4c);
  l44 = *(float*)(cell + 0x10) - *(float*)(cell + 0x54);
  l48 = *(float*)(cell + 0xc) - *(float*)(cell + 0x50);
  if (kf14851ec < (l4c * l4c + l44 * l44) + l48 * l48) {
    l4c = -l4c; l48 = -l48; l44 = -l44;
    dir[0] = l4c; dir[1] = l48; dir[2] = l44;
    SP_QuaternionFromFacingAndUp(q1, dir, &kf15a7c40);
    *(float*)(cell + 0x14) = q1[0];
    *(float*)(cell + 0x18) = q1[1];
    *(float*)(cell + 0x1c) = q1[2];
    *(float*)(cell + 0x20) = q1[3];
  }
}

// @ 0x00e68470
char FUN_00e68470(int param_1, int param_2)
{
  if (*(int*)(param_1 + 0xfc) == 0) return 0;
  char obj[4];
  ((ObjHolder*)obj)->Init();
  char* r = (char*)FUN_00e823a0(*(int*)(param_2 + 0x108), obj);
  int a = *(int*)(r + 0xb4);
  char* st = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  int b = FUN_00e573e0(param_1, param_2);
  if ((*(unsigned char*)(r + 0xb0) & 1) != 0 && b == 1) {
    ((ObjHolder*)obj)->Cleanup();
    return 1;
  }
  char f = *(char*)(st + 0x1251);
  if (f != 0 && a == 3 && b == 1) {
    ((ObjHolder*)obj)->Cleanup();
    return 1;
  }
  if (f != 0 && a == 3 && FUN_00e57340(param_1) == 1 && b == 2) {
    ((ObjHolder*)obj)->Cleanup();
    return 1;
  }
  if (*(char*)(st + 0x1250) != 0 && a == 2) {
    if (b == 0 || b == 1) {
      ((ObjHolder*)obj)->Cleanup();
      return 1;
    }
    if (b == a) {
      if (*(char*)(param_1 + 0x112) == 0) {
        ((ObjHolder*)obj)->Cleanup();
        return 1;
      }
      ((ObjHolder*)obj)->Cleanup();
      return 0;
    }
    if (b == 3) {
      if (FUN_00e57340(param_1) == 1) {
        if (*(char*)(param_2 + 0x112) != 0) {
          ((ObjHolder*)obj)->Cleanup();
          return 1;
        }
        if (FUN_00e50540(param_1) != 0) {
          ((ObjHolder*)obj)->Cleanup();
          return 1;
        }
      }
    }
  }
  ((ObjHolder*)obj)->Cleanup();
  return 0;
}

// @ 0x00e685b0
char FUN_00e685b0(int param_1)
{
  if (*(int*)(param_1 + 0xfc) == 0) return 0;
  char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  return *(char*)(r + 0x1250);
}

// @ 0x00e685f0
char FUN_00e685f0(int param_1)
{
  if (*(int*)(param_1 + 0xfc) == 0) return 0;
  char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
  return *(char*)(r + 0x1248);
}

// @ 0x00e68630
char FUN_00e68630(int param_1)
{
  if (*(int*)(param_1 + 0x248) != 0 && *(int*)(param_1 + 0xfc) != 0 &&
      *(char*)(param_1 + 0x112) == 0 &&
      *(int*)(param_1 + 0x18c) != 0x2b && *(int*)(param_1 + 0x18c) != 0x2c) {
    if (FUN_00e57340(param_1) > 1) {
      char* r = (char*)FUN_00e679e0(*(CellKey*)(param_1 + 0xfc));
      if (*(float*)(r + 0x1270) != 0.0f) return 1;
    }
  }
  return 0;
}

// @ 0x00e695f0
double FUN_00e695f0(int param_1, ObjRef ref)
{
    int iVar2 = *(int*)(*(int*)(g_CellGame + 0x5190) + 0x7c);
    int* piVar1;
    switch (iVar2) {
    case 0:
        piVar1 = (int*)(param_1 + 0x248);
        if (*piVar1 != -1) goto use;
        break;
    case 1:
        break;
    case 2:
        piVar1 = (int*)(param_1 + 0x194);
        if (*piVar1 != -1) goto use;
        break;
    default:
        break;
    }
    piVar1 = (int*)(param_1 + 0xe0);
use:
    float minus1 = -1.0f;
    float f = *(float*)((char*)piVar1 + 0xac);
    if (f == minus1) {
        int iVar3 = (int)FUN_00e52910_s00e6_95f0(param_1);
        f = *(float*)(iVar3 + 0xa8);
        if (f == minus1 && ref.a != 0) {
            int iVar4 = (int)FUN_00e679e0_s00e6_95f0(ref);
            f = *(float*)(iVar4 + 0x125c);
        }
    }
    return f;
}

// @ 0x00e696a0
double FUN_00e696a0(int param_1, ObjRef ref)
{
    int iVar2 = *(int*)(*(int*)(g_CellGame + 0x5190) + 0x7c);
    int* piVar1;
    switch (iVar2) {
    case 0:
        piVar1 = (int*)(param_1 + 0x248);
        if (*piVar1 != -1) goto use;
        break;
    case 1:
        break;
    case 2:
        piVar1 = (int*)(param_1 + 0x194);
        if (*piVar1 != -1) goto use;
        break;
    default:
        break;
    }
    piVar1 = (int*)(param_1 + 0xe0);
use:
    float f = *(float*)((char*)piVar1 + 0xa8);
    if (f == -1.0f && ref.a != 0) {
        int iVar3 = (int)FUN_00e679e0_s00e6_95f0(ref);
        f = *(float*)(iVar3 + 0x1260);
    }
    return f;
}

// @ 0x00e69740
double FUN_00e69740(int param_1, ObjRef ref)
{
    int iVar2 = *(int*)(*(int*)(g_CellGame + 0x5190) + 0x7c);
    int* piVar1;
    switch (iVar2) {
    case 0:
        piVar1 = (int*)(param_1 + 0x248);
        if (*piVar1 != -1) goto use;
        break;
    case 1:
        break;
    case 2:
        piVar1 = (int*)(param_1 + 0x194);
        if (*piVar1 != -1) goto use;
        break;
    default:
        break;
    }
    piVar1 = (int*)(param_1 + 0xe0);
use:
    float f = *(float*)((char*)piVar1 + 0xb0);
    if (f == 0.0f && ref.a != 0) {
        int iVar3 = (int)FUN_00e679e0_s00e6_95f0(ref);
        f = *(float*)(iVar3 + 0x1264);
    }
    return f;
}

// @ 0x00e697e0
void FUN_00e697e0(float param_1)
{
    if ((g_16b4494 & 1) == 0) {
        g_16b4494 |= 1;
        g_16b4490 = EA_Hash_FNV1_String8("clg-move", 0x811c9dc5, 1);
    }
    if ((g_16b4494 & 2) == 0) {
        g_16b4494 |= 2;
        g_16b448c = EA_Hash_FNV1_String8("clg-carnivore", 0x811c9dc5, 1);
    }
    if ((g_16b4494 & 4) == 0) {
        g_16b4494 |= 4;
        g_16b4488 = EA_Hash_FNV1_String8("clg-herbivore", 0x811c9dc5, 1);
    }
    int uVar5;
    if (*(char*)(*(int*)(g_CellGame + 0x5190) + 0xe0) == 0) {
        float f = param_1 + *(float*)(g_CellGame + 0x51c4);
        *(float*)(g_CellGame + 0x51c4) = f;
        uVar5 = (f > g_14007f4) ? 1 : 0;
    } else {
        uVar5 = 0;
    }
    FUN_00e82be0(g_16b4490, uVar5);
    if (*(char*)(*(int*)(g_CellGame + 0x5190) + 0xe1) == 0 &&
        *(char*)(*(int*)(g_CellGame + 0x5190) + 0xe0) == 1) {
        float f2 = *(float*)(g_CellGame + 0x51c8) + param_1;
        *(float*)(g_CellGame + 0x51c8) = f2;
        if (f2 > g_14007f4) {
            char c1 = FUN_00e67aa0();
            int a = c1 ? g_16b448c : g_16b4488;
            char c2 = FUN_00e67aa0();
            int b = c2 ? g_16b4488 : g_16b448c;
            FUN_00e82be0(a, 1);
            FUN_00e82be0(b, 0);
        } else {
            FUN_00e82be0(g_16b448c, 0);
            FUN_00e82be0(g_16b4488, 0);
        }
        ((UIHints*)FUN_0067cac0())->Update();
        return;
    }
    FUN_00e82be0(g_16b448c, 0);
    FUN_00e82be0(g_16b4488, 0);
    ((UIHints*)FUN_0067cac0())->Update();
}

// @ 0x00e699b0
bool FUN_00e699b0(int* param_1, int param_2)
{
    if (*param_1 == 0) return false;
    int iVar1 = (int)FUN_00e679e0_s00e6_95f0(*(ObjRef*)param_1);
    return 0 < *(int*)(iVar1 + 0x1204 + param_2 * 4);
}

// @ 0x00e699f0
void FUN_00e699f0(int param_1, int param_2, int param_3, cSPTransform_s00e6_95f0* param_4)
{
    cSPTransform_s00e6_95f0 local;
    local.mFlags = 0;
    local.mModCount = 0;
    local.mTranslation[0] = g_16b3c28_s00e6_95f0;
    local.mTranslation[1] = g_16b3c2c;
    local.mTranslation[2] = g_16b3c30;
    local.mScale = g_1485720;
    FUN_00e41cb40(local.mRotation, &g_16b3dac_s00e6_95f0);
    FUN_00e68000(param_1, param_2, (cSPTransform_s00e6_7890*)&local);
    *param_4 = local;
    param_4->mModCount++;
    param_4->mScale = g_1485720;
}

// @ 0x00e69a90
int FUN_00e69a90(int param_1, int param_2, int param_3, float param_4, float param_5)
{
    int iVar1 = (int)FUN_00b721d0(param_1);
    if (!iVar1 || *(char*)(iVar1 + 0x112) != 0) return 0;
    int uVar3 = (param_3 == 2) ? 0xc : 0xb;
    switch (*(int*)(iVar1 + 0x18c)) {
        case 0: case 1: case 2: case 3: case 0x12: case 0x13: case 0x14:
        case 0x15: case 0x16: case 0x18: case 0x19: case 0x1a: case 0x1b:
        case 0x1d: case 0x28: case 0x30: case 0x32: case 0x33:
            *(int*)(iVar1 + 0x18c) = uVar3;
            FUN_00e57a10((char*)iVar1, param_1);
    }
    int puVar2 = (int)FUN_00b721d0(param_2);
    if (puVar2) {
        cSPTransform_s00e6_95f0 local;
        FUN_00409930(&local);
        *(uint8_t*)(iVar1 + 0x178) = 1;
        *(uint8_t*)(puVar2 + 0x179) = 1;
        *(uint8_t*)(puVar2 + 0x17f) = 1;
        FUN_00e68000(iVar1, param_1, (cSPTransform_s00e6_7890*)&local);
        if (0.0f < param_4) {
            if (*(int*)(puVar2 + 0x370)) FUN_00e59200(*(int*)(puVar2 + 0x370));
            *(uint8_t*)(puVar2 + 4) = 1;
            FUN_00e5f4d0(*(int*)puVar2, param_5, param_4 + param_5, 0);
            *(int*)(iVar1 + 0x170) = param_2;
            return 1;
        }
        *(uint8_t*)(puVar2 + 4) = 1;
        FUN_00e62380(iVar1, param_1, puVar2, &local, param_5);
    }
    return 1;
}

// @ 0x00e69c10
int FUN_00e69c10(int param_1, int param_2, int param_3, float param_4, float param_5)
{
    int* puVar1 = (int*)FUN_00b721d0(param_1);
    if (!puVar1 || *(char*)((int)puVar1 + 0x112) != 0) return 0;
    int* puVar2 = (int*)FUN_00b721d0(param_2);
    if (!puVar2 || *(char*)((int)puVar2 + 0x112) != 0) return 0;
    *(uint8_t*)(puVar1 + 0x5e) = 1;
    puVar1[0x61] = *puVar2;
    *(uint8_t*)(puVar2 + 0x5e) = 1;
    *(uint8_t*)((int)puVar2 + 0x17b) = 1;
    *(uint8_t*)((int)puVar2 + 0x17f) = 1;
    *(uint8_t*)(puVar2 + 0x5f) = 1;
    puVar2[0x61] = *puVar1;
    *(uint8_t*)((int)puVar2 + 0x179) = 1;
    *(uint8_t*)(puVar2 + 0x62) = 1;
    switch (puVar1[99]) {
        case 0: case 0xb: case 0xc: case 0xd: case 0x12: case 0x13:
        case 0x14: case 0x15: case 0x16: case 0x1d: case 0x30: case 0x32: case 0x33:
            puVar1[99] = 0xd;
            FUN_00e57a10((char*)puVar1, param_3);
    }
    switch (puVar2[99]) {
        case 0: case 0xb: case 0xc: case 0xd: case 0x12: case 0x13: case 0x14:
        case 0x15: case 0x16: case 0x1a: case 0x1d: case 0x20: case 0x21: case 0x30:
            *(uint8_t*)(puVar2 + 1) = 1;
            puVar2[99] = 0x20;
    }
    cSPTransform_s00e6_95f0 local;
    FUN_00409930(&local);
    FUN_00e699f0((int)puVar1, param_3, (int)puVar2, &local);
    if (0.0f < param_4) {
        puVar1[0x5c] = param_2;
        FUN_00e5f4d0(*puVar2, param_5, param_4 + param_5, 0);
        return 1;
    }
    FUN_00e62380((int)puVar1, param_3, (int)puVar2, &local, param_5);
    return 1;
}

// @ 0x00e69e00
int FUN_00e69e00(int param_1, int param_2, int param_3, float param_4, float param_5)
{
    int iVar1 = (int)FUN_00b721d0(param_1);
    if (!iVar1 || *(char*)(iVar1 + 0x112) != 0) return 0;
    int puVar2 = (int)FUN_00b721d0(param_2);
    if (!puVar2) return 0;
    *(uint8_t*)(iVar1 + 0x178) = 1;
    *(uint8_t*)(puVar2 + 0x17b) = 1;
    *(uint8_t*)(puVar2 + 0x17f) = 1;
    *(uint8_t*)(puVar2 + 0x179) = 1;
    switch (*(int*)(iVar1 + 0x18c)) {
        case 0: case 0x12: case 0x15: case 0x16: case 0x1d: case 0x30: case 0x32: case 0x33:
            *(int*)(iVar1 + 0x18c) = 0xd;
            FUN_00e57a10((char*)iVar1, param_3);
    }
    cSPTransform_s00e6_95f0 local;
    FUN_00409930(&local);
    FUN_00e699f0(iVar1, param_3, puVar2, &local);
    if (0.0f < param_4) {
        if (*(int*)(puVar2 + 0x370)) FUN_00e59200(*(int*)(puVar2 + 0x370));
        *(int*)(iVar1 + 0x170) = param_2;
        FUN_00e5f4d0(*(int*)puVar2, param_5, param_4 + param_5, 0);
        return 1;
    }
    FUN_00e62380(iVar1, param_3, puVar2, &local, param_5);
    return 1;
}

// @ 0x00e69f90
int FUN_00e69f90(int param_1, int param_2)
{
    int iVar1 = FUN_00e4cce0(0x14);
    if (*(int*)(param_1 + 0x108) == iVar1) {
        FUN_00e679e0_s00e6_95f0(*(ObjRef*)(param_1 + 0xfc));
        if (param_2 == 6) return param_1 + 0x390;
        if (param_2 == 7) return param_1 + 0x391;
    } else {
        iVar1 = FUN_00e4cce0(0x18);
        if (*(int*)(param_1 + 0x108) == iVar1) {
            switch (param_2) {
                case 8:  return param_1 + 0x392;
                case 10: return param_1 + 0x393;
                case 12: return param_1 + 0x394;
                case 9:  return param_1 + 0x395;
                case 11: return param_1 + 0x396;
                case 13: return param_1 + 0x397;
            }
        }
    }
    return 0;
}

// @ 0x00e6a060
bool FUN_00e6a060(int param_1, int param_2)
{
    char* pcVar1 = (char*)FUN_00e69f90(param_1, param_2);
    if (!pcVar1) return false;
    return *pcVar1 == 0;
}

// @ 0x00e6a090
int FUN_00e6a090(int param_1, int param_2, int param_3, float param_4, float param_5)
{
    int iVar1 = (int)FUN_00b721d0(param_1);
    if (!iVar1 || *(char*)(iVar1 + 0x112) != 0) return 0;
    int puVar2 = (int)FUN_00b721d0(param_2);
    if (!puVar2) return 0;
    *(uint8_t*)(iVar1 + 0x178) = 1;
    *(uint8_t*)(puVar2 + 0x17b) = 1;
    *(uint8_t*)(puVar2 + 0x17f) = 1;
    *(uint8_t*)(puVar2 + 0x179) = 1;
    switch (*(int*)(iVar1 + 0x18c)) {
        case 0: case 0x12: case 0x15: case 0x16: case 0x1d: case 0x30:
            *(int*)(iVar1 + 0x18c) = 0x3b;
            FUN_00e57a10((char*)iVar1, param_3);
    }
    cSPTransform_s00e6_95f0 local;
    FUN_00409930(&local);
    FUN_00e699f0(iVar1, param_3, puVar2, &local);
    if (0.0f < param_4) {
        *(int*)(iVar1 + 0x170) = param_2;
        FUN_00e5f4d0(*(int*)puVar2, param_5, param_4 + param_5, 0);
        return 1;
    }
    FUN_00e62380(iVar1, param_3, puVar2, &local, param_5);
    return 1;
}

// @ 0x00e6a1f0
bool FUN_00e6a1f0(int param_1)
{
    if (*(int*)(param_1 + 0xfc) == 0) return false;
    int iVar1 = (int)FUN_00e679e0_s00e6_95f0(*(ObjRef*)(param_1 + 0xfc));
    return *(float*)(iVar1 + 0x1270) != 0.0f;
}

// @ 0x00e6a250
void FUN_00e6a250(int* param_1, int* param_2, int* param_3, float param_4, int* param_5, int* param_6, int param_7, int param_8)
{
    if (param_7 == 5) {
        char cVar1 = FUN_00e6a1f0((int)param_5);
        if (cVar1 == 0 && *param_5 != param_6[0x43] &&
            (FUN_00e4cce0(0x17) != param_5[0x42] || FUN_00e57340((int)param_5) != 4)) {
            if (param_8 != 0)
                FUN_00e59cc0(param_1, param_2, param_3, param_4, *param_5, *param_6, -1, -1, 0x11);
            else
                FUN_00e59cc0(param_1, param_2, param_3, param_4, *param_5, *param_6, -1, -1, 0x16);
            return;
        }
        if (param_1[2] < 0x16 || (param_1[2] == 0x16 && param_4 <= *(float*)&param_1[5])) {
            *param_1 = *param_5;
            param_1[1] = *param_6;
            param_1[6] = *param_2; param_1[7] = param_2[1]; param_1[8] = param_2[2];
            param_1[9] = *param_3; param_1[10] = param_3[1]; param_1[0xb] = param_3[2];
            *(float*)&param_1[5] = param_4;
            param_1[3] = -1; param_1[4] = -1; param_1[2] = 0x16;
        }
    } else {
        if (param_1[2] < 1 || (param_1[2] == 1 && param_4 <= *(float*)&param_1[5])) {
            *param_1 = *param_5;
            param_1[1] = *param_6;
            param_1[6] = *param_2; param_1[7] = param_2[1]; param_1[8] = param_2[2];
            param_1[9] = *param_3; param_1[10] = param_3[1]; param_1[0xb] = param_3[2];
            *(float*)&param_1[5] = param_4;
            param_1[3] = -1; param_1[4] = -1; param_1[2] = 1;
        }
    }
}

// @ 0x00e6b370
void FUN_00e6b370(void* cell)
{
    char* game = gspCellGame_s00e6_b370;
    if (I(game, 0x51d4) == I(cell, 0)) {
        cCellGameFields* g = (cCellGameFields*)game;
        int avatar = g->mAvatarCellIndex;
        void* target = ((Registry*)(gspCellGame_s00e6_b370 + 0x1c))->GetSafe(avatar);
        if (target != 0) {
            *(Vector3*)((char*)cell + 0x12c) = *(Vector3*)((char*)target + 0x4c);
            return;
        }
        game = gspCellGame_s00e6_b370;
    }
    if (I(cell, 0x248) != 0 && I(cell, 0xfc) != 0) {
        int iVar2;
        if (I(cell, 0) == I(game, 0x411c))
            iVar2 = 0;
        else
            iVar2 = (GetScaleDifferenceWithPlayer(cell) == 4) ? 2 : 1;

        int iVar4 = I(cell, 0x18c);
        switch (iVar4) {
        case 0:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x30:
            break;
        default:
            iVar4 = -1;
        }

        if (iVar4 != I(cell, 0x118) || iVar2 != I(cell, 0x11c) ||
            I(cell, 0x128) <= I(I(game, 0x5190), 0x74)) {
            I(cell, 0x118) = iVar4;
            I(cell, 0x11c) = iVar2;
            I(cell, 0x120) = (int)sChooseRandomLookatTarget(cell, iVar2, iVar4, (int*)((char*)cell + 0x124));
            int t = I(I(gspCellGame_s00e6_b370, 0x5190), 0x74);
            uint32 r = gRandomLCG.RandomUint32Uniform(1000);
            I(cell, 0x128) = (int)(r + 500 + t);
        }

        int local[3];
        float* p = FUN_00e5fc90(local, cell, I(cell, 0x120), I(cell, 0x124));
        I(cell, 0x12c) = I(p, 0);
        I(cell, 0x130) = I(p, 4);
        I(cell, 0x134) = I(p, 8);
    }
}

// @ 0x00e6b500
bool FUN_00e6b500(void* cell)
{
    int avatar = I(gspCellGame_s00e6_b370, 0x411c);
    if (avatar != 0 && I(cell, 0) != avatar) {
        Registry* reg = (Registry*)(gspCellGame_s00e6_b370 + 0x1c);
        void* c = reg->Get(avatar);
        int* res = GetCellResource(*(ResourceKey*)((char*)c + 0xfc));
        int r = FUN_00e573e0(c, cell);
        if (r == 1 || r == 0) {
            Handle h;
            h.ctor();
            void* a = FUN_00e4cc40((int)I(cell, 0x108), &h);
            int b4 = I(a, 0xb4);
            if (B_s00e6_b370(res, 0x1251) != 0 && b4 == 3) {
                h.dtor();
                return true;
            }
            if (B_s00e6_b370(res, 0x1250) != 0 && b4 == 2) {
                h.dtor();
                return true;
            }
            h.dtor();
        }
    }
    return false;
}

// @ 0x00e6b5d0
void FUN_00e6b5d0(float* out, const float* pos, void* cell)
{
    float l30 = pos[0] - F(cell, 0x4c);
    float l2c = pos[1] - F(cell, 0x50);
    float l28 = pos[2] - F(cell, 0x54);
    float inv = (float)(1.0 / sqrt((double)(l30 * l30 + (l2c * l2c + l28 * l28)) + (double)gEpsilon));
    float l18 = inv * l30;
    float l34 = F(cell, 0x58);
    float l14 = l2c * inv;
    float l10 = l28 * inv;

    if (I(cell, 0x248) == 0) {
        out[0] = F(cell, 0x4c) + l18 * l34;
        out[1] = F(cell, 0x50) + l14 * l34;
        out[2] = F(cell, 0x54) + l10 * l34;
        return;
    }
    if (I(cell, 0xfc) == 0) {
        out[0] = l18 * l34 + F(cell, 0x4c);
        out[1] = F(cell, 0x50) + l14 * l34;
        out[2] = F(cell, 0x54) + l10 * l34;
        return;
    }

    int* set = GetCellResource(*(ResourceKey*)((char*)cell + 0xfc));
    int* end = set + 5;
    float best = gFar;
    int bestIdx = -1;
    if (set[0] > 0) {
        int idx = 0;
        float* e = (float*)end;
        do {
            if (I(set, 8 + idx * 0x48) == 0xc) {
                float a = F(set, 0x0c + idx * 0x48);
                float b = F(set, 0x10 + idx * 0x48);
                float c = F(set, 0x14 + idx * 0x48);
                float ra = F(set, 0x3c + idx * 0x48);
                if ((B_s00e6_b370(cell, 0x48) & 2) != 0) {
                    float na = F(cell, 0x74) * c + F(cell, 0x68) * b + F(cell, 0x5c) * a;
                    float nb = F(cell, 0x60) * a + F(cell, 0x78) * c + F(cell, 0x6c) * b;
                    float nc = F(cell, 0x64) * a + F(cell, 0x7c) * c + F(cell, 0x70) * b;
                    a = na; b = nb; c = nc;
                }
                float scale = F(cell, 0x58);
                ra = F(set, 0x3c + idx * 0x48) * scale;
                a = F(cell, 0x4c) + a * scale;
                b = F(cell, 0x50) + b * scale;
                c = F(cell, 0x54) + c * scale;

                float dx = pos[0] - a;
                float dy = pos[1] - b;
                float dz = pos[2] - c;
                float dist = (float)sqrt((double)(dx * dx + (dy * dy + dz * dz)));
                float d = 0.0f;
                float* sel = (float*)&d;
                if (dist - ra > 0.0f)
                    sel = (float*)&pos;      // choose the position itself
                float score = *sel;
                if (score < best) {
                    float invd = (float)(1.0 / sqrt((double)(dx * dx + (dy * dy + dz * dz)) + (double)gEpsilon));
                    bestIdx = idx;
                    best = score;
                    out[0] = invd * dx * ra + a;
                    out[1] = invd * dy * ra + b;
                    out[2] = invd * dz * ra + c;
                }
            }
            idx++;
            e += 0x12;
        } while (idx < set[0]);
        if (bestIdx != -1)
            return;
    }

    out[0] = l18 * l34 + F(cell, 0x4c);
    out[1] = F(cell, 0x50) + l14 * l34;
    out[2] = F(cell, 0x54) + l10 * l34;
}

// @ 0x00e6b9b0
void sUpdateElectricRibbonEffect(void* world, cIVisualEffect** ppEffect, void* cell, int id, int a5)
{
    cIVisualEffect* fx = (cIVisualEffect*)((Registry*)(gspCellGame_s00e6_b370 + 0x1c))->GetSafe(id);
    if (fx == 0 || B_s00e6_b370(fx, 0x112) != 0) {
        if (*ppEffect != 0) {
            (*ppEffect)->Stop(1);
            (*ppEffect)->Release();
            *ppEffect = 0;
        }
        return;
    }

    if (*ppEffect == 0) {
        uint32 effID = 0xa1fb7133;
        void* subject = ((Registry*)(gspCellGame_s00e6_b370 + 0x1c))->Get(id);
        if (I(subject, 0xfc) != 0) {
            int* set = GetCellResource(*(ResourceKey*)((char*)subject + 0xfc));
            int n = set[0];
            int i = 0;
            if (n > 0) {
                int* e = set + 2;
                do {
                    if (*e == 6) { effID = 0x7d84966f; break; }
                    i++;
                    e += 0x12;
                } while (i < n);
            }
        }
        CreateEffectSafe(world, effID, 0, (int**)ppEffect);
        if (!(*ppEffect)->v10())
            (*ppEffect)->Start(0);
    }

    (*ppEffect)->SetTransform((char*)cell + 0x48);

    cSPTransform_s00e6_b370 xf;
    xf.mFlags = 0;
    xf.mModCount = 0;
    xf.mTranslation[0] = gT_016b3c28[0];
    xf.mTranslation[1] = gT_016b3c28[1];
    xf.mTranslation[2] = gT_016b3c28[2];
    xf.mScale = gOne;
    Matrix33_ctor(xf.mRotation, &gMatrix_016b3dac);
    FUN_00e68000(fx, a5, &xf);

    float x0 = xf.mTranslation[0], y0 = xf.mTranslation[1], z0 = xf.mTranslation[2];
    float out[3];
    float pos[3];
    pos[0] = x0; pos[1] = y0; pos[2] = z0;
    FUN_00e6b5d0(out, pos, cell);

    float x1 = out[0], y1 = out[1], z1 = out[2];
    float pts[0x15 * 3];
    for (int i = 0; i < 0x15; i++) {
        float t = (float)i * gFrac05;
        pts[i * 3 + 0] = (x1 - x0) * t + x0;
        pts[i * 3 + 1] = (y1 - y0) * t + y0;
        pts[i * 3 + 2] = (z1 - z0) * t + z0;
    }
    (*ppEffect)->v44(0xd, pts, 0x3f);
}

// @ 0x00e6bc10
void sUpdateChargingEffect(void* world, IntVec* vec, uint32* key, void* a4, void* a5, uint8 b, float f)
{
    int alive = 0;
    if (b != 0) {
        int* set = GetCellResource(*(ResourceKey*)key);
        if (set[0] > 0) {
            int i = 0;
            int* e = set + 2;
            do {
                if (*e == 6) {
                    cIVisualEffect* fx = 0;
                    int count = (int)(((char*)vec->end - (char*)vec->begin) >> 2);
                    if (alive < count) {
                        fx = (cIVisualEffect*)((void**)vec->begin)[alive];
                        if (fx != 0)
                            fx->AddRef();
                    } else {
                        uint32 effID = (I(set, 0x121c) > 2) ? 0x5ca636dc : 0x17aab61f;
                        CreateEffectSafe(world, effID, 0, (int**)&fx);
                        fx->Start(1);
                        bool added = false;
                        void** slot = (void**)vec->end;
                        if (slot < (void**)vec->cap) {
                            vec->end = (char*)slot + 4;
                            if (slot != 0) {
                                *slot = fx;
                                fx->AddRef();
                                added = true;
                            }
                        } else {
                            vec->DoInsertValue(vec->end, (void**)&fx);
                        }
                        if (!added)
                            fx->AddRef();
                    }

                    cSPTransform_s00e6_b370 xf;
                    xf.mFlags = 0;
                    xf.mModCount = 0;
                    xf.mTranslation[0] = gT_016b3c54[0];
                    xf.mTranslation[1] = gT_016b3c54[1];
                    xf.mTranslation[2] = gT_016b3c54[2];
                    xf.mScale = gOne;
                    for (int k = 0; k < 9; k++)
                        xf.mRotation[k] = gR_016b3c60[k];
                    FUN_00e84150((int)a4, i, &xf);
                    float s = f * gTwo;
                    xf.mScale = (s < gMinPos) ? gMinPos : s;
                    xf.mModCount = (uint16)(xf.mModCount + 1);
                    fx->SetTransform(&xf);
                    if (fx != 0)
                        fx->Release();
                    alive++;
                }
                e += 0x12;
                i++;
            } while (i < set[0]);
        }
    }

    int n = (int)(((char*)vec->end - (char*)vec->begin) >> 2);
    while (n - 1 >= alive) {
        n--;
        cIVisualEffect* p = (cIVisualEffect*)((void**)vec->begin)[n];
        p->Stop(1);
        p->Release();
        ((void**)vec->begin)[n] = 0;
        vec->end = (char*)vec->end - 4;
    }
}

// @ 0x00e6cbd0
int FUN_00e6cbd0(int handle, int a2, unsigned a3, char* outA, char* outB)
{
    float total = 0.0f;
    const unsigned mismatch = (unsigned)(gspCellGame_s00e6_cbd0->mHandle411c != handle);
    int picked[131];
    int n = 0;

    // Sweep 1: records whose id matches and whose flag is the mismatch flag (or the literal 2).
    // A type-1 record is always eligible; every other type must appear in the target cell's own
    // placed-object list. Types 8/9 additionally consult the target creature's state and the list.
    for (int i = 0; i < 131; i++) {
        CellSpawn& e = gCellSpawns[i];
        if (e.f0 != (int)a3 || (e.flag != (int)mismatch && e.flag != 2))
            continue;
        if (e.type != 1 && !CellListHasValue(handle, e.type))
            continue;

        if (e.type == 9) {
            bool hold = false;
            if (a2 != 0) {
                const unsigned state = EaterState(a2);
                if (state != 0 && state != 8) {
                    if ((state & 4) != 0)
                        continue;
                } else {
                    hold = true;
                }
            } else {
                hold = true;
            }
            if (hold && CellListHasValue(handle, 10))
                continue;
        } else if (e.type == 8) {
            if (a2 != 0) {
                const unsigned state = EaterState(a2);
                if (state != 0 && state != 8) {
                    if ((state & 4) != 0)
                        continue;
                    if ((state & 1) != 0)
                        continue;
                    goto eligible;
                }
            }
            if (CellListHasValue(handle, 10))
                continue;
            if (a2 != 0) {
                // the state is 0 or 8 here; the original re-reads it before the second gate
                const unsigned state = EaterState(a2);
                if (state != 0 && state != 8) {
                    if ((state & 1) != 0)
                        continue;
                    goto eligible;
                }
            }
            if (CellListHasValue(handle, 9))
                continue;
        }

    eligible:
        if (FUN_00e5c460(handle, e.f6) && FUN_00e5c410(handle, e.f7)) {
            total = total + e.weight;
            picked[n++] = i;
        }
    }

    // Nothing weighed: fall back to the untyped (type 0) records over the whole table.
    if (total == 0.0f) {
        for (int i = 0; i < 131; i++) {
            CellSpawn& e = gCellSpawns[i];
            if (e.f0 != (int)a3 || (e.flag != (int)mismatch && e.flag != 2) || e.type != 0)
                continue;
            total = total + e.weight;
            picked[n++] = i;
        }
    }

    double draw = gMathRandom.RandomDoubleUniform() * (double)total;
    if (draw > (double)total)
        draw = (double)total;
    if (draw < 0.0)
        draw = 0.0;
    float remaining = (float)draw;
    for (int i = 0; i < n; i++) {
        const int idx = picked[i];
        remaining = remaining - gCellSpawns[idx].weight;
        if (remaining <= 0.0f) {
            *outB = gCellSpawns[idx].outB;
            *outA = gCellSpawns[idx].outA;
            return gCellSpawns[idx].f1;
        }
    }
    *outA = 0;
    return 0;
}

// @ 0x00e6d180
void FUN_00e6d180(cCell* c, int a2, int a3, int* out4, float* out5, int* out6, int* out7)
{
    float f;
    int r = FUN_00e6cbd0(c->mHandle, a2, (unsigned)a3, (char*)out6, (char*)out7);
    *out4 = r;
    if (c->mPoolHandle == 0) {
        *out5 = 1.0f;
        return;
    }
    EffectObj* obj;
    {
        ObjectPool& pool = gspCellGfx_s00e6_cbd0->mEffects;
        obj = (EffectObj*)pool.Get(c->mPoolHandle);
    }
    f = obj->FUN_00e4f040(r);
    *out5 = f;
}

// @ 0x00e6d200
float FUN_00e6d200(cCell* c, int a2, int a3, int a4)
{
    if (c->mKey.a == 0 || c->mPoolHandle == 0)
        return 1.0f;

    int local_4;
    float local_10;
    int local_8;
    bool bFlag;
    FUN_00e6d180(c, a2, a3, &local_4, &local_10, &local_8, (int*)&bFlag);

    float local_c = 0.2f;
    float local_14 = 0.2f;
    if (a4 == 0x32 || a4 == 0x33)
        local_14 = 0.7f;
    if (a4 == 0x2f || a4 == 0x2b || a4 == 0x2c)
        local_14 = 0.0f;
    if (a3 == 0x2f)
        local_c = 0.0f;

    if (bFlag) {
        float s = FUN_00e563e0(c);
        local_10 = local_10 * s;
        local_c = local_c * s;
        local_14 = local_14 * s;
    }

    EffectObj* obj;
    {
        ObjectPool& pool = gspCellGfx_s00e6_cbd0->mEffects;
        obj = (EffectObj*)pool.Get(c->mPoolHandle);
    }
    obj->FUN_00e4f330(local_4, local_10, local_c, local_14, local_8);

    if (local_8)
        c->mState2 = a3;
    c->mState1 = a3;
    c->mTimer = local_10;
    return local_10;
}

// @ 0x00e6d340
namespace SP {
void CellUpdateAnimation(cCell* c, int a2, float dt)
{
    if (c->mFlag1ac != 0 && c->mPoolHandle != 0) {
        ObjectPool& pool = gspCellGfx_s00e6_cbd0->mEffects;
        EffectObj* o = (EffectObj*)pool.Get(c->mPoolHandle);
        o->FUN_00e4f100(0xaaaa0066, 1.6f, 0, -1);
    }
    if (c->mPoolHandle != 0) {
        ObjectPool& pool = gspCellGfx_s00e6_cbd0->mEffects;
        EffectObj* o = (EffectObj*)pool.Get(c->mPoolHandle);
        if (c->mFlag390 != 0) {
            o->FUN_00e4f100(0xaaaa0101, 0.0f, 1, -1);
            o->FUN_00e4f100(0xaaaa0103, 0.0f, 1, -1);
            o->FUN_00e4f100(0xaaaa0105, 0.0f, 1, -1);
        }
        if (c->mFlag391 != 0) {
            o->FUN_00e4f100(0xaaaa0100, 0.0f, 1, -1);
            o->FUN_00e4f100(0xaaaa0102, 0.0f, 1, -1);
            o->FUN_00e4f100(0xaaaa0104, 0.0f, 1, -1);
        }
    }
    if (c->mState0 != c->mState1) {
        FUN_00e6d200(c, a2, c->mState0, c->mState1);
        return;
    }
    float t = c->mTimer - dt;
    c->mTimer = t;
    if (t > 0.0f)
        return;
    FUN_00e6d200(c, a2, c->mState2, c->mState1);
}
}  // namespace SP

// @ 0x00e6d4a0
void FUN_00e6d4a0(CellKey* key, int* outA, int* outB)
{
    if (gspCellGame_s00e6_cbd0->mByte4121 == 1) {
        CellInfo* info = FindCellInfo(*key);
        *outA = info->mField1288;
        *outB = info->mField1284;
        return;
    }
    CellScratch buf;
    FUN_00e83e30(&buf.mCount00, &buf.mDesc, key);
    FUN_00e52060(&buf, 1);              // ESI = &buf, EAX = buf.mCount00 in the original
    *outA = buf.mOut1288;
    *outB = buf.mOut1284;
}

// @ 0x00e6d560
void FUN_00e6d560()
{
    IContext* p = FUN_0067de90_s00e6_cbd0(0, 1)->FUN_007ec160();
    p->FUN_007eb820(3);
    p->mOut[0] = gspCellGame_s00e6_cbd0->mpLevelInfo->mField74;
    p->mOut[1] = gspCellGame_s00e6_cbd0->mpLevelInfo->mField1c;
    cCell* c = (cCell*)gspCellGame_s00e6_cbd0->mCells.GetChecked(gspCellGame_s00e6_cbd0->mHandle411c);
    if (c == 0) {
        p->mOut[2] = (int)c;
        return;
    }
    CellInfo* info = FindCellInfo(c->mKey);
    p->mOut[2] = *(int*)info;
}

// @ 0x00e6d600
void FUN_00e6d600()
{
    IContext* p = FUN_0067de90_s00e6_cbd0(0, 5)->FUN_007ec160();
    p->FUN_007eb820(2);
    p->mOut[0] = gspCellGame_s00e6_cbd0->mpLevelInfo->mField74;
    cCell* c = (cCell*)gspCellGame_s00e6_cbd0->mCells.GetChecked(gspCellGame_s00e6_cbd0->mHandle411c);
    if (c == 0) {
        p->mOut[1] = (int)c;
        return;
    }
    CellInfo* info = FindCellInfo(c->mKey);
    p->mOut[1] = *(int*)info;
}

// @ 0x00e6d680
bool FUN_00e6d680(cCell* c)
{
    if (c->mKey.a == 0)
        return false;
    CellInfo* info = FindCellInfo(c->mKey);
    return info->mField1214 > 0;
}

// @ 0x00e6d6d0
float FUN_00e6d6d0(cCell* c)
{
    float r = 0.7f;
    if (c->mKey.a != 0 && !FUN_00e6d680(c)) {
        switch (FUN_00e516c0(c)) {
        case 0: r = -0.7f; break;
        case 1: r = 0.0f; break;
        case 3: r = 1.4f; break;
        case 4: r = 2.1f; break;
        case 5: r = 2.8f; break;
        }
    }
    return r;
}

// @ 0x00e6d790
void FUN_00e6d790(cCell* c, Vector3_s00e6_cbd0* center, float* radius)
{
    if (c->mPoolHandle == 0) {
        center->x = c->mPosition.x;
        center->y = c->mPosition.y;
        center->z = c->mPosition.z;
        *radius = c->mRadius;
        return;
    }
    CellInfo* info = FindCellInfo(c->mKey);
    *radius = info->mScale1244 * c->mRadius;
    center->x = info->mVec1238.x;
    center->y = info->mVec1238.y;
    center->z = info->mVec1238.z;
    if (c->mFlags & 2) {
        Vector3_s00e6_cbd0 v = *center;
        *center = v * c->mOrient;
    }
    center->x = center->x * c->mRadius;
    center->y = center->y * c->mRadius;
    center->z = center->z * c->mRadius;
    center->x = center->x + c->mPosition.x;
    center->y = center->y + c->mPosition.y;
    center->z = center->z + c->mPosition.z;
}

// @ 0x00e6d8f0
void FUN_00e6d8f0(int handle, int)
{
    cCell* cell = (cCell*)gspCellGame_s00e6_cbd0->mCells.Get(handle);

    // the animation channels of the cell's model: one 4-byte cursor per range, reset by
    // 0x00743b50 and then seeded from the cell's type (and from the channels it lists)
    int it1;
    FUN_00743b50(&it1);
    int* p1 = (int*)FUN_00e823a0(cell->mType, &it1);
    int it2;
    FUN_00743b50(&it2);
    FUN_00e823a0(*p1, &it2);

    int k;
    if (cell->mRadius >= 2.0f) k = 3;
    else if (cell->mRadius >= 1.0f) k = 2;
    else if (cell->mRadius >= 0.3f) k = 1;
    else k = 0;
    cell->mAnimIdx = k;

    if (k == 0 || cell->mEffectGroup != gspCellGame_s00e6_cbd0->mSel40fc ||
        p1[0x2d] == 0 || p1[0x2d] == 5) {
        cell->mAnimCount = 1;
        cell->mAnimData = -1;
    } else {
        int* p = (int*)&cell->mAnimData;
        FUN_00e5cb60(&gCellSpawnTableTag, &p, &cell->mFlags, &cell->mVelocity, handle, k, 0);
        cell->mAnimCount = (int)(p - (int*)&cell->mAnimData) >> 2;
    }

    int grp = cell->mEffectGroup;
    int cmp = gspCellGame_s00e6_cbd0->mSel40fc;
    int h = gspCellGfx_s00e6_cbd0->mEffects.Alloc();
    cell->mPoolHandle = h;
    EffectObj* obj = (EffectObj*)gspCellGfx_s00e6_cbd0->mEffects.Get(h);
    FUN_00e5ce90(obj, cell->mHandle, (grp != cmp), *p1, handle, cell->mKey);

    cCell* c2 = (cCell*)gspCellGame_s00e6_cbd0->mCells.Get(handle);
    FUN_00e6d200(c2, 0, 0, c2->mState1);

    if (cell->mEffectGroup == gspCellGame_s00e6_cbd0->mSel4100 && gspCellGfx_s00e6_cbd0->mField16254 < 0x10)
        FUN_00e51930();

    FUN_00e82130(&it2);
    FUN_00e82130(&it1);
}

// @ 0x00e6dae0
void FUN_00e6dae0(cCell* c)
{
    if (c->mObstacle == -1)
        return;
    Vector3_s00e6_cbd0 center;
    float radius;
    FUN_00e6d790(c, &center, &radius);
    float vmaxx = center.x + radius;
    float vmaxy = center.y + radius;
    float vminx = center.x - radius;
    float vminy = center.y - radius;
    MoveObstacle(gspCellGame_s00e6_cbd0->mObstacleGrid, c->mObstacle, &vminx, &vmaxx);
    (void)vmaxy; (void)vminy;
}

// @ 0x00e6db70
void CellRecenterWorld(const Vector3_s00e6_db70& newCenter, float scale)
{
    Vector3_s00e6_db70 center = newCenter;
    if (center.z * center.z + center.y * center.y + center.x * center.x > 1000000.0f)
        SnapToGrid(center, 1000.0f);
    else
        center = gCellWorldCenter_s00e6_db70;

    float invScale = 1.0f / scale;
    float worldScale = invScale;

    cCellEffectPositions* pEffects = gspCellGame_s00e6_db70->mpEffectPositions;
    for (int i = 0; i < 0x5dc; i++) {
        if (pEffects->mActive[i]) {
            Vector3_s00e6_db70& p = pEffects->mPositions[i];
            p.x = (p.x - center.x) * invScale;
            p.y = (p.y - center.y) * invScale;
            p.z = (p.z - center.z) * invScale;
        }
    }
    CellRescaleEffects();

    TransformMsg msg;
    msg.mType = 4;
    msg.mFlags = 3;
    Matrix3_s00e6_db70 orient = gCellWorldOrient;
    msg.mOrient = orient;
    msg.mPosition = center + (gCellWorldCenter_s00e6_db70 - (gCellWorldCenter_s00e6_db70 * invScale) * orient);
    msg.mScale = invScale;

    int index = gspCellGame_s00e6_db70->mCells.Begin();
    for (cCell_s00e6_db70* pCell = (cCell_s00e6_db70*)gspCellGame_s00e6_db70->mCells.Next(&index); pCell; pCell = (cCell_s00e6_db70*)gspCellGame_s00e6_db70->mCells.Next(&index)) {
        Vector3_s00e6_db70 pos = (pCell->mPosition - center) * invScale;
        float radius = pCell->mRadius;
        pCell->mModifier.AccumulateScaled(&msg);
        pCell->SetPosition(pos);
        pCell->SetRadius(radius * invScale);
        pCell->mVelocity *= invScale;
        float size = pCell->mSize * invScale;
        pCell->mSize = size;
        if (size != 0.0f) {
            float mass = GetCellScaleFactor(pCell->mType) * size * size;
            pCell->mMass = mass;
            pCell->mInvMass = 1.0f / mass;
        }
        CellUpdateSpeed(pCell);

        Vector3_s00e6_db70 boundsCenter;
        float boundsRadius;
        GetCellBounds(pCell, &boundsCenter, &boundsRadius);
        pCell->mEffect = CellMoveEffect(pCell->mEffectGroup, &boundsCenter, boundsRadius, pCell->mHandle);
        if (pCell->mObstacle != -1) {
            Vector3_s00e6_db70 c;
            float r;
            GetCellBounds(pCell, &c, &r);
            Vector2 vMax(c.x + r, c.y + r);
            Vector2 vMin(c.x - r, c.y - r);
            MoveObstacle(gspCellGame_s00e6_db70->mObstacleGrid, pCell->mObstacle, &vMin, &vMax);
        }
        pCell->mTarget -= center;
        pCell->mTarget *= invScale;
        pCell->mGoal *= invScale;
    }

    for (int i = 0; i < (int)(gspCellGfx_s00e6_db70->mModifiersEnd - gspCellGfx_s00e6_db70->mModifiersBegin); i++)
        ((Modifier*)&gspCellGfx_s00e6_db70->mModifiersBegin[i])->AccumulateScaled(&msg);
    gspCellGfx_s00e6_db70->mScale *= invScale;

    gspCellCamera->mPosition -= center;
    gspCellCamera->mPosition *= invScale;
    gspCellCamera->mTarget -= center;
    gspCellCamera->mTarget *= invScale;
    gspCellCamera->mOffset -= center;
    gspCellCamera->mOffset *= invScale;

    gspCellGame_s00e6_db70->mTileMap.clear();

    index = gspCellGame_s00e6_db70->mTiles.Begin();
    for (cBackgroundTile* pTile = (cBackgroundTile*)gspCellGame_s00e6_db70->mTiles.Next(&index); pTile;
         pTile = (cBackgroundTile*)gspCellGame_s00e6_db70->mTiles.Next(&index)) {
        float tileScale = 1.0f / ((kLevelSize_s00e6_db70[pTile->mLevel] / gspCellGame_s00e6_db70->mCellSize) *
            (GetLevelScale(pTile->mLevel - GetCellStage(gspCellGame_s00e6_db70->mpLevelInfo->mStage)->mLevel) * 0.85f));
        pTile->mX -= FloorToInt(tileScale * center.x);
        pTile->mY -= FloorToInt(center.y * tileScale);

        if (pTile->mpShape) {
            int level = pTile->mLevel;
            float levelSize = kLevelSize_s00e6_db70[level];
            float border = level * 0.0f;
            float x0 = pTile->mX * levelSize + border;
            float y0 = pTile->mY * levelSize + border;
            float x1 = (pTile->mX + 1) * levelSize - border;
            float y1 = (pTile->mY + 1) * levelSize - border;
            float s = 1.0f / (gspCellGame_s00e6_db70->mCellSize /
                (GetLevelScale(level - GetCellStage(gspCellGame_s00e6_db70->mpLevelInfo->mStage)->mLevel) * 0.85f));
            Vector3_s00e6_db70 vMin = Vector3_s00e6_db70(x0, y0, 0.0f) * s;
            Vector3_s00e6_db70 vMax = Vector3_s00e6_db70(x1, y1, 0.0f) * s;

            TransformMsg tileMsg;
            tileMsg.mOrient = gCellTileOrient;
            tileMsg.mPosition = (vMax + vMin) * 0.5f;
            tileMsg.mType = 4;
            tileMsg.mFlags = 2;
            tileMsg.mScale = vMax.x - vMin.x;
            pTile->mpShape->Transform(&tileMsg);
        }

        int key = ((((pTile->mLayer << 8) | (pTile->mLevel & 0xff)) << 8 | (pTile->mX & 0xff)) << 8) | (pTile->mY & 0xff);
        gspCellGame_s00e6_db70->mTileMap[key] = pTile->mHandle;
    }

    gspCellGame_s00e6_db70->mWorldScale *= worldScale;
}

// @ 0x00e6eec0
static void StepCell(Cell_s00e6_e8c0* self, float a1, float a2, float a3, unsigned flags, int mode)
{
    Vec3_s00e6_e8c0 v;                       // per-step delta; later reused as the steering vector
    CellDelta(&v, self);
    self->mAccum.x = self->mAccum.x + v.x;
    self->mAccum.y = v.y + self->mAccum.y;
    self->mAccum.z = v.z + self->mAccum.z;
    if (self->mDone)
        return;

    const Vec3_s00e6_e8c0* pos = &self->mPos;
    const Vec3_s00e6_e8c0* target = &self->mTarget;
    double ddx = (double)pos->x - target->x;
    double ddy = (double)pos->y - target->y;
    double ddz = (double)pos->z - target->z;
    double dist = sqrt(ddx * ddx + ddy * ddy + ddz * ddz);
    if (dist < 0.5f) {
        self->mDone = 1;
        return;
    }

    float speed = CellSpeedFactor(self, flags, (float)dist);
    a2 = (self->mHasPath ? 1.0f : 0.5f) * (float)((double)a2 / CellLevelRatio(self));
    if (self->mIndex != gspCellGame_s00e6_e8c0->mAvatarCellIndex) {
        cHandleRef h;
        CellScales* sc = GetCellScales(&h);
        a2 = sc->f48 * a2;
        if (flags & 8)
            speed = sc->f50 * speed;
        else if (flags & 1)
            speed = sc->f50 * speed;
        else if (flags & 2)
            speed = sc->f54 * speed;
        else if (flags & 4)
            speed = sc->f4c * speed;
        int src = SP_sGetSourceLevel(0, gspCellGame_s00e6_e8c0->mpLevelInfo->mLevel);
        speed = CellScaleById(0x1106a9e2, kLevelSize_s00e6_e8c0[self->mLevel] / kLevelSize_s00e6_e8c0[src]) * speed;
    }
    speed = speed * a3;

    if (self->mState == 0 || self->mState == 0x28 || !(1.5258789e-05f > CellTurnLimit(self))) {
        float angle = CellTurnAngle(self);
        static float sQuarter = kQuarterPi;
        float absAngle = (float)fabs(angle);
        if (absAngle > kPi - sQuarter && (flags & 2)) {
            CellStartTurn(self);
        } else {
            static float sEighth = kQuarterPi * 0.5f;
            if (absAngle > sEighth) {
                mode = 3;
                if (!(angle > 0.0f))
                    mode = 4;
            }
            CellApplyTurn(self, speed, a1);
        }
    }

    if (self->mSuppressed == 1)
        return;

    bool pickMode = false;
    switch (self->mState) {
    case 0:
    case 0x12:
    case 0x30:
        pickMode = true;
        break;
    case 0x28:
        if (self->mIndex == gspCellGame_s00e6_e8c0->mAvatarCellIndex)
            pickMode = true;
        break;
    }
    if (pickMode) {
        switch (mode) {
        case 0: self->mState = CellCanTurn(self, a1) ? 0x30 : 0x12; break;
        case 1: self->mState = 0x14; break;
        case 2: self->mState = 0x13; break;
        case 3: self->mState = 0x32; break;
        case 4: self->mState = 0x33; break;
        }
    }

    float scale = CellTurnLimit(self);
    Vec3_s00e6_e8c0 n1, n2;
    if (flags & 8) {
        CellSteerA(target, &self->mHeading, pos, a2, a1, &v);
        const Vec3_s00e6_e8c0* p = NormalizedSafe(&n1, &v);
        const Vec3_s00e6_e8c0* q = CellFacing(&n2, self);
        float dot = q->z * p->z + (q->y * p->y + q->x * p->x);
        if ((float)fabs(dot) < 0.9f)
            v = kFallbackDir;
        v = Scaled(v, scale);
        self->mTurnDistance = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    } else if (flags & 4) {
        float s = CellSteerRateB(self);
        bool ok = CellSteerB(CellFacing(&n2, self), target, &self->mHeading, pos, a2, s, a3,
                             (flags & 2) == 2, a1, &v);
        if (!ok) {
            int st = self->mState;
            if (st == 0x13 || st == 0x14 || st == 0x12 || st == 0x30)
                self->mState = 0;
        }
        v = Scaled(v, scale);
        const Vec3_s00e6_e8c0* p = NormalizedSafe(&n1, &v);
        const Vec3_s00e6_e8c0* h = NormalizedSafe(&n2, &self->mHeading);
        float dot = Dot3(h, p);
        self->mTurnRateB = (float)(sqrt((double)(v.x * v.x + v.y * v.y + v.z * v.z)) * dot
                                   + 1.5258789e-05f);
    } else if (flags & 1) {
        CellSteerC(CellFacing(&n2, self), target, &self->mHeading, pos, a2, 1.0f, a3, 0, a1, &v);
        v = Scaled(v, scale);
        self->mTurnDistance = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z)
                              + 1.5258789e-05f;
    } else if (flags & 2) {
        float s = CellSteerRateC(self);
        CellSteerC(CellFacing(&n2, self), target, &self->mHeading, pos, a2, s, a3, 1, a1, &v);
        v = Scaled(v, scale);
        self->mTurnRateC = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z)
                           + 1.5258789e-05f;
    }

    v = Scaled(v, self->mVelocityScale);
    CellMove(self, &v);
}

// @ 0x00e71520
void FUN_00e71520(char* cell, int param2, int* param3)
{
    if (*(char*)(cell + 0x17f) == 1) return;

    char ctx[0x18];
    ((cLayerCtx*)ctx)->Begin();
    void* ent = FUN_00e4cc40(*(int*)(cell + 0x108), ctx);
    float f0 = FUN_00e69480(cell, (int)ent, 1);
    int list[512];
    int n = FUN_00e693f0(cell, param3, &param2, f0, list);
    FUN_00e52a00();

    void* cp = ((cObjectPool*)(gCellGame + 0x1c))->Get(*(int*)cell);
    float t = FUN_00e6d200((cCell*)cp, 0, 0x1e, *(int*)((char*)cp + 0x1b0));

    cObjectPool* cmdp = (cObjectPool*)(gCellGame + 0x54);
    cCellCmd* cmd = (cCellCmd*)cmdp->Get(cmdp->Alloc());
    cmd->t1c = t; cmd->t20 = t;
    cmd->kind24 = 0x11;
    cmd->src28 = *(int*)cell;
    cmd->arg2c = *(int*)param3;
    cmd->arg30 = param2;
    cmd->arg34 = -1;
    cmd->arg38 = 0; cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = gFwd_16b3c28; cmd->from4c = gFwd_16b3c2c; cmd->from50 = gFwd_16b3c30;
    cmd->to54   = gFwd_16b3c28; cmd->to58   = gFwd_16b3c2c; cmd->to5c   = gFwd_16b3c30;
    cmd->dir60 = gBasis_15a7c4c; cmd->dir64 = gBasis_15a7c50;
    cmd->dir68 = gBasis_15a7c54; cmd->dir6c = gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    void* s = FUN_00e52910_s00e7_1520((int)ent);
    int num;
    if (*(int*)s == 0x1001 || *(int*)(gCellGame + 0x411c) == *(int*)cell) {
        int x = FUN_00e679e0(*(int*)(cell + 0xfc), *(int*)(cell + 0x100), *(int*)(cell + 0x104));
        num = *(int*)(x + 0x126c);
        if (n <= num) num = n;
    } else {
        void* s2 = FUN_00e52910_s00e7_1520((int)ent);
        num = *(int*)((char*)s2 + 0x5c);
        if (n <= num) num = n;
    }

    for (int i = 0; i < num; i++) {
        int id = list[i];
        int k = 0xe;
        int kind = 1;
        void* a = ((cObjectPool*)(gCellGame + 0x1c))->Get(id);
        if (*(int*)((char*)a + 0x108) == FUN_00e4cce0(0x16)) { k = 0x3c; kind = 2; }

        void* b = ((cObjectPool*)(gCellGame + 0x1c))->Get(id);
        float t2 = FUN_00e6d200((cCell*)b, 0, k, *(int*)((char*)b + 0x1b0));

        cCellCmd* cmd2 = (cCellCmd*)cmdp->Get(cmdp->Alloc());
        cmd2->t1c = t2; cmd2->t20 = t2;
        cmd2->kind24 = 2;
        cmd2->src28 = id;
        cmd2->arg2c = param2 - 0;
        cmd2->arg30 = param2;
        cmd2->arg34 = -1;
        cmd2->arg38 = kind;
        cmd2->arg3c = *(int*)(cell + 0x108);
        cmd2->f40 = 0.0f; cmd2->f44 = 0.0f;
        cmd2->from48 = gFwd_16b3c28; cmd2->from4c = gFwd_16b3c2c; cmd2->from50 = gFwd_16b3c30;
        cmd2->to54   = gFwd_16b3c28; cmd2->to58   = gFwd_16b3c2c; cmd2->to5c   = gFwd_16b3c30;
        cmd2->dir60 = gBasis_15a7c4c; cmd2->dir64 = gBasis_15a7c50;
        cmd2->dir68 = gBasis_15a7c54; cmd2->dir6c = gBasis_15a7c58;
        cmd2->flag70 = 0;
        cmd2->flag74 = (char)(*(int*)cell == *(int*)(gCellGame + 0x411c));
        cmd2->flag78 = 0;
        cmd2->x04 = 0; cmd2->x08 = 0;

        void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(id);
        *(float*)((char*)c + 0x90) = gFwd_16b3c28;
        *(float*)((char*)c + 0x94) = gFwd_16b3c2c;
        *(float*)((char*)c + 0x98) = gFwd_16b3c30;

        if ((*(int*)(gCellGame + 0x411c) == *(int*)cell || *(int*)(gCellGame + 0x411c) == *(int*)c)
            && *(int*)((char*)c + 0x248) != 0) {
            void* r = FUN_00e62200(*(int*)c, (float)*(int*)((char*)c + 0x244) * gk_1440f84);
            if (r != 0) *(float*)((char*)r + 0x24) = gk_1471064;
        }

        int* timer = (int*)((char*)c + 0x244);
        *timer -= FUN_00e58980((int*)cell, (int*)c);
        if (*timer < 0) *timer = 0;
        FUN_00e576f0(*(int*)cell);
    }

    FUN_00e58890(*(int*)cell, *param3, param2);
    ((cLayerCtx*)ctx)->End();
}

// @ 0x00e71c00
void FUN_00e71c00(int param1, int param2, int param3, int param4)
{
    char local[0x18];
    FUN_00e67cb0((int)param1, (float*)local);

    int* pi;
    int mode = *(int*)(*(int*)(gCellGame + 0x5190) + 0x7c);
    if (mode == 0) {
        pi = (int*)(param2 + 0x248);
        if (*pi == -1) goto use_default;
    } else if (mode == 1) {
        goto use_default;
    } else if (mode == 2) {
        pi = (int*)(param2 + 0x194);
        if (*pi == -1) goto use_default;
    } else {
        goto use_default;
    }
    goto have;
use_default:
    pi = (int*)(param2 + 0xe0);
have:
    {
        int iVar1 = pi[0x10];
        int avatar = *(int*)(gCellGame + 0x411c);
        int uVar4 = FUN_00e67c40((int)param1, (int)param2);
        void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(avatar);
        float v[3];
        v[0] = *(float*)((char*)c + 0x4c);
        v[1] = *(float*)((char*)c + 0x50);
        v[2] = *(float*)((char*)c + 0x54);
        FUN_00e56f80((void*)param1, v);
        FUN_00e6eec0(param3, uVar4, *(float*)&iVar1, *(float*)&param4, 0.0f);
    }
}

// @ 0x00e72060
int FUN_00e72060(void* cell)
{
    *(char*)((char*)cell + 0x113) = 1;
    ((cTriggerMgr_s00e7_1520*)GetTriggerMgr())->SetModal(1);
    *(char*)(gCellUI + 0x936) = 1;
    FUN_00e5c8e0();

    void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(*(int*)cell);
    FUN_00e6d200((cCell*)c, 0, 10, *(int*)((char*)c + 0x1b0));
    float f = FUN_00e6d200((cCell*)c, 0, 7, *(int*)((char*)c + 0x1b0));

    cObjectPool* cmdp = (cObjectPool*)(gCellGame + 0x54);
    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cCellCmd* cmd = (cCellCmd*)cmdp->Get(slot);
    cmd->t1c = f; cmd->t20 = f;
    cmd->kind24 = 0x1d;
    cmd->src28 = *(int*)cell;
    cmd->arg2c = 0;
    cmd->arg30 = -1;
    cmd->arg34 = -1;
    cmd->arg38 = 0; cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = gFwd_16b3c28; cmd->from4c = gFwd_16b3c2c; cmd->from50 = gFwd_16b3c30;
    cmd->to54   = gFwd_16b3c28; cmd->to58   = gFwd_16b3c2c; cmd->to5c   = gFwd_16b3c30;
    cmd->dir60 = gBasis_15a7c4c; cmd->dir64 = gBasis_15a7c50;
    cmd->dir68 = gBasis_15a7c54; cmd->dir6c = gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;
    *(int*)(gCellGame + 0x5194) = slot;

    void* s = ((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)cell);
    if (s != 0) {
        *(char*)((char*)s + 0x16c) = 1;
        *(char*)((char*)s + 0x178) = 1;
        *(char*)((char*)s + 0x17c) = 1;
        *(int*)((char*)s + 0x18c) = 7;
    }
    *(int*)(gCellUI + 0xe0) = *(int*)cell;
    return 1;
}

// @ 0x00e72360
void FUN_00e72360(int* cell, int* other, int param3, int param4, int param5, int param6)
{
    if (*(char*)((char*)cell + 0x17f) == 1) return;
    if (FUN_00e57460(cell, other)) return;

    void* c = ((cObjectPool*)(gCellGame + 0x1c))->Get(*cell);
    float f = FUN_00e6d200((cCell*)c, 0, 4, *(int*)((char*)c + 0x1b0));
    int slot = (int)FUN_00e51ee0(10, f, *cell, *other, param3, -1, param6, 0, 0.0f, 0.0f,
                                 (float*)param4, (float*)param5, (float*)0, 0, 0, 0);
    void* p = ((cObjectPool*)(gCellGame + 0x54))->Get(slot);
    *(float*)((char*)p + 0x0c) = gk_13f9428;
    FUN_00e592f0(*cell, *other, param3, param4, (int*)param5);
}

// @ 0x00e72430
void FUN_00e72430(int* param_1)
{
    void* e = gspCellGame_s00e7_2430->mCells.Get(*param_1);
    float f = FUN_00e6d200((cCell*)e, 0, 0x3d, *(int*)((char*)e + 0x1b0));
    int h = gspCellGame_s00e7_2430->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame_s00e7_2430->mEffects.Get(h);
    r->f1c = f;
    r->f28 = *param_1;
    r->f20 = f;
    r->f2c = 0;
    r->f38 = 0;
    r->f3c = 0;
    r->f24 = 0x2a;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->f30 = -1;
    r->f34 = -1;
    r->v48 = g_16b3c28_s00e7_2430; r->v4c = g_16b3c2c_s00e7_2430; r->v50 = g_16b3c30_s00e7_2430;
    r->v54 = g_16b3c28_s00e7_2430; r->v58 = g_16b3c2c_s00e7_2430; r->v5c = g_16b3c30_s00e7_2430;
    r->v60 = g_15a7c4c_s00e7_2430; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    FUN_00e59470(*param_1);
}

// @ 0x00e72530
void FUN_00e72530(int* self, int ediVal, int arg1, int arg2, int arg3)
{
    if (*(char*)((char*)self + 0x113) != 0) return;
    if (*(char*)((char*)self + 0x112) != 0) return;
    void* e = gspCellGame_s00e7_2430->mCells.Get(*self);
    float f = FUN_00e6d200((cCell*)e, 0, ediVal, *(int*)((char*)e + 0x1b0));
    FUN_00e51ee0(0x15, f, *self, arg1, arg2, -1, ediVal, 0, 0, 0,
                 (float*)arg3, 0, 0, 0, 0, 0);
    FUN_00e59640(*self, arg1, arg2, ediVal, (int*)arg3);
}

// @ 0x00e725c0
int FUN_00e725c0(int* self, int* edi_obj, int param_1)
{
    if (*(char*)((char*)self + 0x179) != 0) return 1;
    if (*(char*)((char*)self + 0x17b) != 0) return 0;
    if (*(char*)((char*)edi_obj + 0x178) != 0) return 0;
    if (FUN_00e57460_s00e7_2430((int)edi_obj, (int)self)) return 0;

    void* e = gspCellGame_s00e7_2430->mCells.Get(*edi_obj);
    float f = FUN_00e6d200((cCell*)e, 0, 0xd, *(int*)((char*)e + 0x1b0));
    int h = gspCellGame_s00e7_2430->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame_s00e7_2430->mEffects.Get(h);
    r->f2c = *self;
    r->f28 = *edi_obj;
    r->f1c = f;
    r->f20 = f;
    r->f3c = self[0x42];
    r->f24 = 0x14;
    r->f30 = param_1;
    r->f34 = 0;
    r->f38 = 4;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28_s00e7_2430; r->v4c = g_16b3c2c_s00e7_2430; r->v50 = g_16b3c30_s00e7_2430;
    r->v54 = g_16b3c28_s00e7_2430; r->v58 = g_16b3c2c_s00e7_2430; r->v5c = g_16b3c30_s00e7_2430;
    r->v60 = g_15a7c4c_s00e7_2430; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;

    void* r2 = gspCellGame_s00e7_2430->mEffects.Get(h);
    *(float*)((char*)r2 + 0x10) = f;
    void* r3 = gspCellGame_s00e7_2430->mEffects.Get(h);
    *(float*)((char*)r3 + 0xc) = f * g_1486d94;

    cSPTransform_s00e7_2430 local;
    local.copyFrom(*(cSPTransform_s00e7_2430*)((char*)self + 0x48));
    local.invert();
    local.compose(*(cSPTransform_s00e7_2430*)((char*)edi_obj + 0x48));
    int att = SP_sAttach(*self, -1, *edi_obj, &local, 0);
    *(int*)((char*)self + 0x168) = att;
    FUN_00e59710(*edi_obj, *self, param_1, f * g_1486d94, f, 0);
    return 1;
}

// @ 0x00e727e0
int FUN_00e727e0(int* self, int* edi_obj, int param_1)
{
    if (*(char*)((char*)self + 0x179) != 0) return 1;
    if (*(char*)((char*)self + 0x17b) != 0) return 0;
    if (*(char*)((char*)edi_obj + 0x178) != 0) return 0;
    if (*(char*)((char*)edi_obj + 0x113) != 0) return 0;
    if (*(char*)((char*)edi_obj + 0x112) != 0) return 0;
    if (FUN_00e57460_s00e7_2430((int)edi_obj, (int)self)) return 0;

    void* e = gspCellGame_s00e7_2430->mCells.Get(*edi_obj);
    float f = FUN_00e6d200((cCell*)e, 0, 0xd, *(int*)((char*)e + 0x1b0));
    void* e2 = gspCellGame_s00e7_2430->mCells.Get(*self);
    FUN_00e6d200((cCell*)e2, 0, 0x20, *(int*)((char*)e2 + 0x1b0));
    FUN_00e51ee0(0x13, f, *edi_obj, *self, param_1, 0, 4, self[0x42],
                 0, 0, 0, 0, 0, 0, 0, 0);
    float q = f * g_1486d94;
    FUN_00e528f0(0, q);
    FUN_00e69c10(*edi_obj, *self, param_1, q, 0.0f);
    return 1;
}

// @ 0x00e72910
int FUN_00e72910(int* self, int* param_1, int param_2)
{
    if (*(char*)((char*)self + 0x179) != 0) return 1;
    if (*(char*)((char*)self + 0x17b) != 0) return 0;
    if (*(char*)((char*)param_1 + 0x178) != 0) return 0;

    void* e = gspCellGame_s00e7_2430->mCells.Get(*param_1);
    float f = FUN_00e6d200((cCell*)e, 0, 0xd, *(int*)((char*)e + 0x1b0));
    if (self[0xdc]) FUN_00e59200(self[0xdc]);

    int h = gspCellGame_s00e7_2430->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame_s00e7_2430->mEffects.Get(h);
    r->f2c = *self;
    r->f28 = *param_1;
    r->f1c = f;
    r->f20 = f;
    r->f3c = self[0x42];
    r->f24 = 0x12;
    r->f30 = param_2;
    r->f34 = 0;
    r->f38 = 4;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28_s00e7_2430; r->v4c = g_16b3c2c_s00e7_2430; r->v50 = g_16b3c30_s00e7_2430;
    r->v54 = g_16b3c28_s00e7_2430; r->v58 = g_16b3c2c_s00e7_2430; r->v5c = g_16b3c30_s00e7_2430;
    r->v60 = g_15a7c4c_s00e7_2430; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;

    void* r2 = gspCellGame_s00e7_2430->mEffects.Get(h);
    *(float*)((char*)r2 + 0xc) = f * g_1486d94;
    FUN_00e69e00(*param_1, *self, param_2, f * g_1486d94, 0.0f);
    return 1;
}

// @ 0x00e72ac0
void FUN_00e72ac0()
{
    ((ModalObj*)FUN_00b3d4d0())->setModal(0);
    *(uint8_t*)(gspCellState + 0x936) = 0;
    FUN_00e6d560();
    FUN_00e59800(0);
    void* local_4 = 0;
    SP_CreateEffectSafe(*(int*)(gspCellGfx_s00e7_2430 + 0x161c8), 0xa1b0293d, 0, (int)&local_4);
    if (local_4) ((void(__thiscall*)(void*, int))(*(void***)local_4)[2])(local_4, 0);
    *(uint8_t*)(gspCellState + 0x936) = 1;
    if (local_4) ((void(__thiscall*)(void*))(*(void***)local_4)[1])(local_4);
}

// @ 0x00e72b40
void FUN_00e72b40(int* self)
{
    void* e = gspCellGame_s00e7_2430->mCells.Get(*self);
    float v = FUN_00e6d200((cCell*)e, 0, 0x1d, *(int*)((char*)e + 0x1b0));
    if (v == 0.0f) {
        gspCellGame_s00e7_2430->mCells.GetChecked(*self);
        return;
    }
    void* lvl = *(void**)(gspCG + 0x5190);
    FUN_00e57170(FUN_00e4eef0(lvl, *(int*)((char*)lvl + 0x1c)));

    int h = gspCellGame_s00e7_2430->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame_s00e7_2430->mEffects.Get(h);
    r->f1c = v;
    r->f20 = v;
    r->f28 = *self;
    r->f2c = 0;
    r->f38 = 0;
    r->f3c = 0;
    r->f24 = 0x1f;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->f30 = -1;
    r->f34 = -1;
    r->v48 = g_16b3c28_s00e7_2430; r->v4c = g_16b3c2c_s00e7_2430; r->v50 = g_16b3c30_s00e7_2430;
    r->v54 = g_16b3c28_s00e7_2430; r->v58 = g_16b3c2c_s00e7_2430; r->v5c = g_16b3c30_s00e7_2430;
    r->v60 = g_15a7c4c_s00e7_2430; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    FUN_00e599b0(*self);
}

// @ 0x00e72c80
void FUN_00e72c80()
{
    int* e = (int*)gspCellGame_s00e7_2430->mCells.GetChecked(*(int*)(gspCG + 0x411c));
    if (!e) return;
    if (*(char*)((char*)e + 0x113) == 1) return;
    if (*(char*)((char*)e + 0x112) == 1) return;

    *(uint8_t*)(gspCG + 0x5169) = 1;
    if (*(int*)(gspCG + 0x5158) == 3) return;

    FUN_00e53580();
    *(int*)(gspCG + 0x5158) = 3;
    FUN_00e53130();
    FUN_00e6d600();

    int* e2 = (int*)gspCellGame_s00e7_2430->mCells.GetChecked(*(int*)(gspCG + 0x411c));
    int local_c = 0, local_8 = 0, local_4 = 0;
    if (e2) {
        local_c = *(int*)((char*)e2 + 0xfc);
        local_8 = *(int*)((char*)e2 + 0x100);
        local_4 = *(int*)((char*)e2 + 0x104);
    }
    int* lvl = *(int**)(gspCG + 0x5190);
    FUN_00e82c10(&local_c, *(int*)((char*)lvl + 0x74), *(int*)((char*)lvl + 0x70),
                 *(int*)((char*)lvl + 0x6c));
    FUN_00e4f660(1);

    void* e3 = gspCellGame_s00e7_2430->mCells.Get(*(int*)(gspCG + 0x411c));
    float f = FUN_00e6d200((cCell*)e3, 0, 0x2e, *(int*)((char*)e3 + 0x1b0));
    int h = gspCellGame_s00e7_2430->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame_s00e7_2430->mEffects.Get(h);
    r->f1c = f;
    r->f20 = f;
    r->f24 = 0x1f;
    r->f28 = 0;
    r->f2c = 0;
    r->f38 = 0;
    r->f3c = 0;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->f30 = -1;
    r->f34 = -1;
    r->v48 = g_16b3c28_s00e7_2430; r->v4c = g_16b3c2c_s00e7_2430; r->v50 = g_16b3c30_s00e7_2430;
    r->v54 = g_16b3c28_s00e7_2430; r->v58 = g_16b3c2c_s00e7_2430; r->v5c = g_16b3c30_s00e7_2430;
    r->v60 = g_15a7c4c_s00e7_2430; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    *(int*)(gspCG + 0x5194) = h;
    FUN_00e59a30();
}

// @ 0x00e72e70
void FUN_00e72e70(int* param_1, int param_2)
{
    char* pFlag = (char*)FUN_00e69f90((int)param_1, param_2);
    if (*pFlag == 1) return;
    int b = (param_2 != 6);
    *pFlag = 1;

    void* e = gspCellGame_s00e7_2430->mCells.Get(*param_1);
    float f = FUN_00e6d200((cCell*)e, 0, b + 0x3f, *(int*)((char*)e + 0x1b0));
    int v = *param_1;
    int h = gspCellGame_s00e7_2430->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame_s00e7_2430->mEffects.Get(h);
    r->f1c = f;
    r->f20 = f;
    r->f24 = 0x27;
    r->f28 = v;
    r->f2c = 0;
    r->f30 = param_2;
    r->f34 = -1;
    r->f38 = 0;
    r->f3c = 0;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28_s00e7_2430; r->v4c = g_16b3c2c_s00e7_2430; r->v50 = g_16b3c30_s00e7_2430;
    r->v54 = g_16b3c28_s00e7_2430; r->v58 = g_16b3c2c_s00e7_2430; r->v5c = g_16b3c30_s00e7_2430;
    r->v60 = g_15a7c4c_s00e7_2430; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    FUN_00e59af0(*param_1, param_2);
}

// @ 0x00e72fb0
void FUN_00e72fb0(int* param_1, int param_2)
{
    char* pFlag = (char*)FUN_00e69f90((int)param_1, param_2);
    if (*pFlag == 1) return;
    *pFlag = 1;

    void* e = gspCellGame_s00e7_2430->mCells.Get(*param_1);
    float f = FUN_00e6d200((cCell*)e, 0, 0x34, *(int*)((char*)e + 0x1b0));
    int v = *param_1;
    int h = gspCellGame_s00e7_2430->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame_s00e7_2430->mEffects.Get(h);
    r->f1c = f;
    r->f20 = f;
    r->f24 = 0x28;
    r->f28 = v;
    r->f2c = 0;
    r->f30 = param_2;
    r->f34 = -1;
    r->f38 = 0;
    r->f3c = 0;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28_s00e7_2430; r->v4c = g_16b3c2c_s00e7_2430; r->v50 = g_16b3c30_s00e7_2430;
    r->v54 = g_16b3c28_s00e7_2430; r->v58 = g_16b3c2c_s00e7_2430; r->v5c = g_16b3c30_s00e7_2430;
    r->v60 = g_15a7c4c_s00e7_2430; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;
    FUN_00e59af0(*param_1, param_2);
}

// @ 0x00e730d0
bool FUN_00e730d0(int param_1, int param_2, int param_3)
{
    if (!gspCellGame_s00e7_2430->mCells.GetChecked(param_1)) return false;
    int other = (int)gspCellGame_s00e7_2430->mCells.GetChecked(param_2);
    if (!other) return false;
    if (FUN_00e4ff50(other) == 1) {
        FUN_00e72fb0((int*)other, param_3);
        return true;
    }
    FUN_00e72e70((int*)other, param_3);
    return true;
}

// @ 0x00e73140
bool FUN_00e73140(int* param_1, int* param_2, int param_3)
{
    if (*(char*)((char*)param_1 + 0x178) != 0) return false;

    void* e = gspCellGame_s00e7_2430->mCells.Get(*param_1);
    float f = FUN_00e6d200((cCell*)e, 0, 0x3b, *(int*)((char*)e + 0x1b0));
    if (param_2[0xdc]) FUN_00e59200(param_2[0xdc]);

    int h = gspCellGame_s00e7_2430->mEffects.Alloc();
    EvRec* r = (EvRec*)gspCellGame_s00e7_2430->mEffects.Get(h);
    r->f28 = *param_1;
    r->f1c = f;
    r->f20 = f;
    r->f30 = param_3;
    r->f24 = 0x29;
    r->f2c = *param_2;
    r->f34 = -1;
    r->f38 = 0;
    r->f3c = 0;
    r->f40 = 0.0f;
    r->f44 = 0.0f;
    r->v48 = g_16b3c28_s00e7_2430; r->v4c = g_16b3c2c_s00e7_2430; r->v50 = g_16b3c30_s00e7_2430;
    r->v54 = g_16b3c28_s00e7_2430; r->v58 = g_16b3c2c_s00e7_2430; r->v5c = g_16b3c30_s00e7_2430;
    r->v60 = g_15a7c4c_s00e7_2430; r->v64 = g_15a7c50; r->v68 = g_15a7c54;
    r->f6c = g_15a7c58;
    r->f70 = 0;
    r->f74 = 0;
    r->f78 = 0;
    r->f04 = 0;
    r->f08 = 0;

    float q = f * g_1486d94;
    void* r2 = gspCellGame_s00e7_2430->mEffects.Get(h);
    *(float*)((char*)r2 + 0xc) = q;
    FUN_00e6a090(*param_1, *param_2, param_3, q, 0.0f);
    return true;
}

// @ 0x00e732d0
void FUN_00e732d0(int* param_1, int* param_2, int param_3, int param_4, int param_5)
{
    if (*(char*)((char*)param_1 + 0x112) == 1) return;
    if (*(char*)((char*)param_1 + 0x113) == 1) return;
    if (*(char*)((char*)param_1 + 0x17f) != 0) return;

    void* e = gspCellGame_s00e7_2430->mCells.Get(*param_1);
    float f = FUN_00e6d200((cCell*)e, 0, 0x1c, *(int*)((char*)e + 0x1b0));
    FUN_00e51ee0(0x26, f, *param_1, *param_2, param_3, param_4, 0, 0, 0, 0,
                 (float*)param_5, 0, 0, 0, 0, 0);
    FUN_00e59b50(*param_1, param_3, (int*)param_5);
    FUN_00e730d0(*param_1, *param_2, param_4);
}

// @ 0x00e73f60
namespace SP {
void sUpdateGfx()
{
    FUN_00e64e10();
    LoadEffectMap();
    FUN_00e55080();

    cCell_s00e7_3f60* avatar = GetCellSafe(gspCellGame_s00e7_3f60->mAvatarCellIndex);
    float avgSpeed = 0.0f;
    float fluidSpeed;
    float health;
    float zoomed;
    if (avatar) {
        float speed = Saturate((float)sqrt(avatar->mVelocity.x * avatar->mVelocity.x +
                                           avatar->mVelocity.y * avatar->mVelocity.y +
                                           avatar->mVelocity.z * avatar->mVelocity.z) * 0.125f, 1.0f);
        gspCellGfx_s00e7_3f60->mSpeedParamSampling[gspCellGfx_s00e7_3f60->mCurrentSample++] = speed;
        gspCellGfx_s00e7_3f60->mCurrentSample %= 4;
        float sum = 0.0f;
        for (int i = 0; i < 4; i++)
            sum += gspCellGfx_s00e7_3f60->mSpeedParamSampling[i];
        avgSpeed = sum * 0.25f;
        SetAudioParameter(gspCellGfx_s00e7_3f60->mAudioHandle, 0xf03e3ddf, Clamp((avatar->mTransform.mScale - 0.5f) * 0.6666667f, 0.0f, 1.0f));

        IMessageServer* server = EA::Messaging::GetServer();
        if (server) {
            Vector3_s00e7_3f60 pos;
            if (IsCursorMode())
                pos = gspCellUI->mCursorPosition;
            else
                pos = avatar->mTransform.mTranslation;
            MessageBasicRC5 msg;
            msg.mData[0].mFloat = pos.x;
            msg.mData[1].mFloat = pos.y;
            msg.mData[2].mFloat = pos.z;
            server->MessageSend(0x052d9bab, &msg, 0);
        }

        int anim = CELL_I(avatar, 0x18c);
        if (anim == 7 || anim == 8 || anim == 9 || anim == 10)
            SetGlobalAudioParameter(0xf83dae6e, 0.0f);
        else
            SetGlobalAudioParameter(0xf83dae6e, FUN_00e5bfa0() + 1.0f);
        fluidSpeed = SP::FluidParticlesSampleVelMagnitude(gspCellGame_s00e7_3f60->mpFluidParticles,
                                                          avatar->mTransform.mTranslation);
        health = (float)CELL_I(avatar, 0x244) * 0.16666667f;
        zoomed = gspCellGame_s00e7_3f60->field_4120 ? 1.0f : 0.0f;
    } else {
        fluidSpeed = SP::FluidParticlesSampleVelMagnitude(gspCellGame_s00e7_3f60->mpFluidParticles,
            (sVisibleBackgroundBBox.upper + sVisibleBackgroundBBox.lower) * 0.5f);
        health = 0.0f;
        zoomed = 0.0f;
        if (gspCellGame_s00e7_3f60->field_5158 == 4)
            SetGlobalAudioParameter(0xf83dae6e, 0.0f);
        else
            SetGlobalAudioParameter(0xf83dae6e,
                Saturate((float)gspCellGame_s00e7_3f60->mpSerializableData->mLevel * 0.001f, 1.0f) + 1.0f);
    }

    SetGlobalAudioParameter(0x07632190, Saturate(fluidSpeed * 0.1f, 1.0f));
    SetGlobalAudioParameter(0xb0b3caf6, health);
    SetGlobalAudioParameter(0xa807ac16, zoomed);
    SetGlobalAudioParameter(0xe6a63e05, avgSpeed);
    if (gspCellGame_s00e7_3f60->field_51b4 == 3)
        SetGlobalAudioParameter(0x4cd9e37f, FUN_00e5be80());
    else
        SetGlobalAudioParameter(0x4cd9e37f, 0.0f);

    int it = gspCellGfx_s00e7_3f60->mGfxObjects.Begin();
    for (cCellGfxObject* gfx = NextGfx(&it); gfx;
         gfx = NextGfx(&it)) {
        cCell_s00e7_3f60* cell = GetCell(gfx->mCellIndex);

        int level = gspCellGame_s00e7_3f60->mpSerializableData->mLevel;
        int playerScale = GetCellScaleInfo(level)->scale;
        int cellScale = CELL_I(cell, 0x358);
        if (cellScale == -1)
            cellScale = GetCellScaleInfo(level)->scale;
        gfx->Update(&cell->mTransform, cell->mOpacity, cell->mRelativeElevation, GetCellLod(cell),
                    &cell->mVisualTransform, CELL_I(cell, 0x18c), CELL_I(cell, 0x24c),
                    cellScale - playerScale + 2, CELL_I(cell, 0x35c));

        int scale = CELL_I(cell, 0x358);
        if (scale == -1)
            scale = GetCellScaleInfo(gspCellGame_s00e7_3f60->mpSerializableData->mLevel)->scale;
        SP::UpdateCollectableVisibility(gfx, scale);

        cEffectSet* effects = GetPartEffects(cell);
        if (effects) {
            int effectID;
            if (RemoveEffectEntry(GetPartEffects(cell), 0x4ff54f49, &effectID)) {
                cIEffectsWorld* world = GetEffectsWorld(cell);
                VisualEffectPtr effect;
                world->CreateVisualEffect(effectID, effect.AsPointer());
                if (effect) {
                    effect->Start(0);
                    StartPartEffect(effect, GetPartEffects(cell), CELL_I(cell, 0x174));
                }
            }
        }

        cIEffectsWorld* world = GetEffectsWorld(cell);
        const ResourceKey_s00e7_3f60* key = &cell->mModelKey;
        if (cell->mModelKey.instanceID) {
            float strength = 1.0f;
            if (SP::GetScaleDifferenceWithPlayer(cell) <= 1)
                strength = 0.25f;
            UpdatePropulsionEffect(world, &gfx->mpJetEffect, &cell->mVisualTransform, &cell->mTransform,
                                   strength, CELL_F(cell, 0x198), 0x2c34420c, "cell_propulsionJet");
            UpdatePropulsionEffect(world, &gfx->mpCiliaEffect, &cell->mVisualTransform, &cell->mTransform,
                                   strength, CELL_F(cell, 0x19c), 0xa6d4590b, "cell_propulsionCilia");
            UpdatePropulsionEffect(world, &gfx->mpFlagellaEffect, &cell->mVisualTransform, &cell->mTransform,
                                   strength, CELL_F(cell, 0x194), 0x44894cd7, "cell_propulsionFlagella");
        }

        if (CELL_I(cell, 0x35c) == gspCellGame_s00e7_3f60->midPlayerCell) {
            if (CellWantsPlayerEffect(cell)) {
                if (!gfx->mpPlayerEffect) {
                    SP::CreateEffectSafe(world, 0xb71008db, 0, &gfx->mpPlayerEffect);
                    gfx->mpPlayerEffect->Start(0);
                }
                gfx->mpPlayerEffect->SetTransform(&cell->mTransform);
            } else if (gfx->mpPlayerEffect) {
                gfx->mpPlayerEffect->Stop(0);
                gfx->mpPlayerEffect->Release();
                gfx->mpPlayerEffect = 0;
            }
        }

        SP::sUpdateElectricRibbonEffect(world, &gfx->mpElectricEffect, cell, CELL_I(cell, 0x190),
                                        CELL_I(cell, 0x174));
        SP::sUpdateChargingEffect(world, &gfx->mpChargingEffect, key, effects, &cell->mTransform,
                                  CELL_B(cell, 0x18a), cell->field_160);

        int poisonLevel;
        if (key->instanceID == 0)
            poisonLevel = 0;
        else {
            cCellResource* res = GetCellResource_s00e7_3f60(*key);
            if (gspCellGame_s00e7_3f60->mAvatarCellIndex != cell->mIndex)
                poisonLevel = 1;
            else if (res->field_1218 <= 2)
                poisonLevel = 1;
            else
                poisonLevel = res->field_1218 > 4 ? 3 : 2;
        }
        SP::sUpdatePoisonReleaseEffect(world, &gfx->mpPoisonEffect, cell, key, &cell->mVisualTransform,
                                       poisonLevel, CELL_B(cell, 0x1ac),
                                       SP::GetScaleDifferenceWithPlayer(cell) <= 1,
                                       cell->mIndex == gspCellGame_s00e7_3f60->mAvatarCellIndex);
        FUN_00e63bf0(cell, world, &gfx->mpEffect9c, &cell->mTransform, CELL_B(cell, 0x18b));
        CompactEffects(cell, gfx);

        bool isTarget = cell->mIndex == gspCellGame_s00e7_3f60->field_51b0;
        FUN_00e61050(world, &gfx->mpEffect8c, &cell->mTransform, effects,
                     key->instanceID == 0 ? -1 : GetCellResource_s00e7_3f60(*key)->field_128c, isTarget);
        FUN_00e67510(world, &gfx->mpEffect90, &cell->mVisualTransform, &cell->mTransform, effects, 6,
                     CELL_B(cell, 0x390));
        FUN_00e67510(world, &gfx->mpEffect94, &cell->mVisualTransform, &cell->mTransform, effects, 7,
                     CELL_B(cell, 0x391));
        FUN_00e660e0(cell, gfx);
    }

    FUN_00e6c330();
    FUN_00e63ac0(gspCellGfx_s00e7_3f60->field_161dc);
    FUN_00e831a0(gspCellGfx_s00e7_3f60->field_40, ((cSPFluidParticles_s00e7_3f60*)gspCellGame_s00e7_3f60->mpFluidParticles)->field_1c210,
                 ((cSPFluidParticles_s00e7_3f60*)gspCellGame_s00e7_3f60->mpFluidParticles)->field_1bd60);
}
}  // namespace SP

// @ 0x00e74a20
int __cdecl CreateCell(int group, const Vector3* pos, float elevation, int defId, int level, float sizeScale, float size, P8 radiusOrFlag, const Quat* orient, int filter)
{
    cCellDef* def;
    cDefRef ref;
    def = GetCellDef(defId, &ref);

    if (size == 0.0f) {
        float scale;
        if (level != -1)
            scale = kLevelSize_s00e7_4a20[level] * 0.033333335f;
        else
            scale = 1.0f;
        size = scale / gspCellGame_s00e7_4a20->mField514c * FUN_004df2d0(&def->mField304) * sizeScale;
    } else {
        size = sizeScale * size;
    }

    int id = gspCellGame_s00e7_4a20->mCells.New();
    cCell_s00e7_4a20* cell = gspCellGame_s00e7_4a20->mCells.Get(id);
    cell->mActive = 1;
    cell->mPosition = *pos;
    cell->mField1d0 = 0.0f;

    int zero = 0;
    if (def->mSpecial == 1) {
        cell->mOrientation = kQuatIdentity;
    } else {
        Quat* q = &cell->mOrientation;
        float w;
        if (orient == 0) {
            float half = (float)(gMathRandom.RandomDoubleUniform() * kTwoPi * 0.5f);
            float s = (float)sin(half);
            float c = (float)cos(half);
            Vector3f axis(s * kUnitZ.x, s * kUnitZ.y, s * kUnitZ.z);
            q->v.x = axis.x; q->v.y = axis.y; q->v.z = axis.z;
            w = c;
        } else {
            q->v = orient->v;
            w = orient->w;
        }
        q->w = w;
    }
    cell->mTransform.mTranslation = cell->mPosition;
    cell->mTransform.mFlags |= 4;
    cell->mTransform.mModificationCount++;
    Matrix3 rot;
    cell->mTransform.mRotation = *Matrix3FromQuaternion(&rot, &cell->mOrientation);
    cell->mTransform.mFlags |= 2;
    cell->mTransform.mModificationCount++;

    if (group == gspCellGame_s00e7_4a20->mGroup4100) {
        Vector3 tmp;
        Vector3* v = FUN_00e5eb20(&tmp, cell);
        cell->mVelocity.x = v->x;
        cell->mVelocity.y = v->y;
        cell->mVelocity.z = v->z;
    } else {
        cell->mVelocity = kVec3Zero;
    }
    cell->mRelativeElevation = elevation;
    cell->mOpacity = 1.0f;
    cell->mField0a4 = 1.0f;
    cell->mSize = size;
    cell->mField0a8 = 0.0f;
    cell->mField0ac = 10.0f;
    float mass = FUN_00e4f9d0(defId) * size * size;
    cell->mMass = mass;
    cell->mInvMass = 1.0f / mass;
    if (radiusOrFlag.flag) {
        cell->mTransform.mModificationCount++;
        cell->mTransform.mScale = cell->mSize;
    }
    cell->mField11c = 1;
    cell->mField128 = 0;
    cell->mField118 = 0;
    cell->mField120 = 0;
    cell->mField124 = 0;
    cell->mField12c = Vector3f(kUnitZ.x * 10.0f + pos->x, kUnitZ.y * 10.0f + pos->y, kUnitZ.z * 10.0f + pos->z);
    cell->mField138 = *(Vector3*)&cell->mField12c;
    cell->mField144 = 0;
    cell->mField1c0 = 1.0f;
    cell->mVisualTransform.mRotation = kMatrix3Identity;
    cell->mVisualTransform.mScale = 1.0f;
    cell->mVisualTransform.mTranslation = kVec3Zero;
    cell->mVisualTransform.mFlags = 0;
    cell->mVisualTransform.mModificationCount = 0;
    {
        Vector3 keyTmp;
        cell->mModelKey = *FUN_00e65640(&keyTmp, defId);
    }
    cell->mDefId = defId;
    cell->mByte111 = 0;
    cell->mByte112 = 0;
    cell->mByte113 = 0;
    cell->mByte110 = 0;
    cell->mField10c = 0;
    cell->mField368 = 0.0f;
    cell->mField36c = 0;
    cell->mField370 = 0;
    cell->mField374 = 0.0f;
    cell->mField14c = 0;
    FUN_00e6cad0(def, cell->mModelKey, &cell->mField158, &cell->mField15c);
    cell->mField150 = 0.0f;
    cell->mField244 = 6;
    cell->mField248 = 0;
    cell->mField24c = 0;
    cell->mField250 = 0;
    cell->mByte354 = 0;
    cell->mField358 = level;
    cell->mField35c = group;

    Vector3 center;
    FUN_00e6d790(cell, &center, &radiusOrFlag.radius);
    cell->mField360 = FUN_00e868f0(group, &center, radiusOrFlag.radius, id);
    if (group == gspCellGame_s00e7_4a20->midPlayerCell) {
        int f = filter;
        if (f == -1) {
            if (def->mKind == 7)
                f = -5;
            else if (def->mKind == 5)
                f = -5;
            else
                f = id;
        }
        float lo[2], hi[2];
        hi[0] = center.x + radiusOrFlag.radius;
        hi[1] = center.y + radiusOrFlag.radius;
        lo[0] = center.x - radiusOrFlag.radius;
        lo[1] = center.y - radiusOrFlag.radius;
        cell->mField364 = FUN_00bbbdd0(gspCellGame_s00e7_4a20->mpPhysics, cell->mIndex, lo, hi, f);
    } else {
        cell->mField364 = -1;
    }

    cLevelInfo_s00e7_4a20* info;
    switch (gspCellGame_s00e7_4a20->mpSerializableData->mStage) {
    case 0:
        info = &def->mLevels[2];
        if (info->mType == -1)
            info = &def->mLevels[0];
        break;
    case 1:
        info = &def->mLevels[0];
        break;
    case 2:
        info = &def->mLevels[1];
        if (info->mType == -1)
            info = &def->mLevels[0];
        break;
    default:
        info = &def->mLevels[0];
        break;
    }
    double limit = info->mLimit;
    double v = gMathRandom.RandomDoubleUniform() * limit;
    if (v < limit) {
        if (v < 0.0)
            v = 0.0;
    } else {
        v = limit;
    }
    cell->mField234 = (float)v;
    if (info->mType == 0x100c)
        cell->mField1fc = cell->mTransform.mTranslation;
    return id;
}

// @ 0x00e76880
void FUN_00e76880(void* cell, float dt)
{
    B_s00e7_6880(cell, 0x1ac) = 0;
    if (FUN_00e68630_s00e7_6880((int)cell)) {
        B_s00e7_6880(cell, 0x1ac) = 1;
        FUN_00e69580((int*)cell);
        int* res = GetCellResource(*(ResourceKey*)((char*)cell + 0xfc));
        float s = F(cell, 0x90) * F(cell, 0x90) +
                  F(cell, 0x94) * F(cell, 0x94) +
                  F(cell, 0x98) * F(cell, 0x98);
        float f = (float)sqrt((double)s);
        f = ((f + f) + 1.0f) * dt + F(cell, 0x374);
        F(cell, 0x374) = f;

        int n = I(res, 0x1274);
        if (1.0f < f && 0 < n) {
            cSPTransform_s00e7_6880 xf;
            xf.mFlags = 0;
            xf.mModCount = 0;
            xf.mTranslation[0] = gOrientUp[0];
            xf.mTranslation[1] = gOrientUp[1];
            xf.mTranslation[2] = gOrientUp[2];
            xf.mScale = gOne;
            Matrix33_ctor(xf.mRotation, &gMatrix_016b3dac);
            for (int i = 0; i < n; i++) {
                FUN_00e68000((int)cell, I(res, 0x1278 + i * 4), &xf);
                FUN_00e76660((int*)cell, I(res, 0x1278 + i * 4), &xf);
                F(cell, 0x374) = 0.0f;
            }
        }
    }
}

// @ 0x00e76a80
void FUN_00e76a80(void* cell, float dt)
{
    float f = dt + F(cell, 0x154);
    F(cell, 0x154) = f;
    while (0.3f < f) {
        f = F(cell, 0x154) - 0.3f;
        F(cell, 0x154) = f;
    }
    FUN_00e71980(dt);
    FUN_00e76880(cell, dt);
}

// @ 0x00e76af0
int sCreateLeakAttachment(void* obj, float* pos, int a3, int a4, int a5)
{
    float facing[3];
    facing[0] = gOrientUp[0];
    facing[1] = gOrientUp[1];
    facing[2] = gOrientUp[2];

    float dx = F(obj, 0x4c) - pos[0];
    float dy = F(obj, 0x50) - pos[1];
    float dz = F(obj, 0x54) - pos[2];
    if (gMinPos < dx * dx + dy * dy + dz * dz) {
        float inv = (float)(1.0 / sqrt((double)(dx * dx + dy * dy + dz * dz)));
        facing[0] = inv * dx;
        facing[1] = dy * inv;
        facing[2] = dz * inv;
    }

    cSPTransform_s00e7_6880 xf;
    xf.mFlags = 0;
    xf.mModCount = 0;
    Matrix33_ctor(xf.mRotation, &gMatrix_016b3dac);
    xf.mTranslation[0] = pos[0];
    xf.mTranslation[1] = pos[1];
    xf.mTranslation[2] = pos[2];
    xf.mFlags |= 4;
    xf.mModCount += 1;

    float mat[9];
    Matrix3FromFacingAndUp(mat, facing, gUp_015a7c40);
    xf.mScale = F(obj, 0x58);
    for (int i = 0; i < 9; i++)
        xf.mRotation[i] = mat[i];

    cSPTransform_s00e7_6880 parent;
    parent.mFlags = *(uint16*)((char*)obj + 0x48);
    parent.mModCount = *(uint16*)((char*)obj + 0x4a);
    xf.mFlags |= 2;
    parent.mTranslation[0] = F(obj, 0x4c);
    parent.mTranslation[1] = F(obj, 0x50);
    parent.mTranslation[2] = F(obj, 0x54);
    parent.mScale = F(obj, 0x58);
    Matrix33_ctor(parent.mRotation, (char*)obj + 0x5c);

    FUN_0040efa0(parent.mRotation);
    ComposeTransforms(&xf);

    float quat[4];
    QuaternionFromFacingAndUp(quat, facing, gUp_015a7c40);

    int created = FUN_00e74a20(I(obj, 0x35c), pos, I(obj, 0x80), a4, a3, F(obj, 0x58),
                               0.0f, 1.0f, quat, 0);
    sAttach(I(obj, 0), a5, created, &parent, 1);
    void* pool = (char*)gspCellGame_s00e7_6880 + 0x1c;
    int inst = (int)((ObjectPool_s00e7_6880*)pool)->Get(created);
    I(inst, 0x14c) = I(obj, 0);
    return created;
}

// @ 0x00e76d70
int sCreateCellAttachment(void* obj, char flag, float* pos, int a4, int a5, int a6)
{
    float facing[3];
    facing[0] = gOrientUp[0];
    facing[1] = gOrientUp[1];
    facing[2] = gOrientUp[2];

    float dx = F(obj, 0x4c) - pos[0];
    float dy = F(obj, 0x50) - pos[1];
    float dz = F(obj, 0x54) - pos[2];
    if (gMinPos < dx * dx + dy * dy + dz * dz) {
        float inv = (float)(1.0 / sqrt((double)(dx * dx + dy * dy + dz * dz)));
        facing[0] = inv * dx;
        facing[1] = dy * inv;
        facing[2] = dz * inv;
    }

    float q[4];
    QuaternionFromFacingAndUp(q, facing, gUp_015a7c40);

    if (flag != 0) {
        double ang = (double)(gUp_015a7c40[0] * 0.0f) + (double)GF(0x015a7c1c);
        float sn = (float)sin(ang);
        float cs = (float)cos(ang);
        float v0 = sn * gUp_015a7c40[0];
        float v1 = sn * gUp_015a7c40[1];
        float v2 = sn * gUp_015a7c40[2];
        float q0 = q[0], q1 = q[1], q2 = q[2], q3 = q[3];
        float r0 = q1 * v2 - q2 * v1;
        float r1 = q2 * v0 - v2 * q0;
        float r2 = v1 * q0 - q1 * v0;
        float c1 = q2 * v2;
        float r3 = q3 * v0 + cs * q0;
        float r4 = q3 * v1 + q1 * cs;
        float r5 = q3 * v2 + q2 * cs;
        q2 = r5 + r2;
        q1 = q3 * cs - ((q0 * v0 + c1) + q1 * v1);
        q0 = r3 + r0;
        q3 = r4 + r1;
    }

    int created = FUN_00e74a20(I(obj, 0x35c), pos, I(obj, 0x80), a5, a4, 1.0f, 0.0f, 1.0f,
                               q, a6);
    int inst = (int)((ObjectPool_s00e7_6880*)((char*)gspCellGame_s00e7_6880 + 0x1c))->Get(created);

    cSPTransform_s00e7_6880 xf;
    xf.mFlags = 0;
    xf.mModCount = 0;
    Matrix33_ctor(xf.mRotation, &gMatrix_016b3dac);
    xf.mTranslation[0] = pos[0];
    xf.mTranslation[1] = pos[1];
    xf.mTranslation[2] = pos[2];
    xf.mFlags |= 4;
    xf.mModCount += 1;

    float mat[9];
    Matrix3FromQuaternion(mat, q);
    xf.mScale = F(inst, 0x58);
    for (int i = 0; i < 9; i++)
        xf.mRotation[i] = mat[i];

    cSPTransform_s00e7_6880 parent;
    parent.mFlags = *(uint16*)((char*)obj + 0x48);
    parent.mModCount = *(uint16*)((char*)obj + 0x4a);
    xf.mFlags |= 2;
    parent.mTranslation[0] = F(obj, 0x4c);
    parent.mTranslation[1] = F(obj, 0x50);
    parent.mTranslation[2] = F(obj, 0x54);
    parent.mScale = F(obj, 0x58);
    Matrix33_ctor(parent.mRotation, (char*)obj + 0x5c);

    FUN_0040efa0(parent.mRotation);
    ComposeTransforms(&xf);

    sAttach(I(obj, 0), -1, created, &parent, 1);
    return created;
}

// @ 0x00e771d0
void sDropLoot(int a1, void* key, int a3, float* pos, float radius, int lvl, int a7, int a8, void* out, int* outCount)
{
    if (a7 == 0)
        return;
    if (B_s00e7_6880(gspCellGame_s00e7_6880, 0x518c) != 0 && a1 != FUN_00e4cce0(1))
        return;

    IterObj itbuf[2];
    IterObj* const it = itbuf;
    it->Init();
    int* tbl = (int*)FUN_00e4cc40(a7, it);
    if (tbl[6] != 0)
        FUN_00e61b90(a3 != I(gspCellGame_s00e7_6880, 0x40fc) ? 1 : 0, 0);

    int count = tbl[1];
    int chosen = -1;
    float acc = 0.0f;
    if (0 < count) {
        int off = 0;
        int i = 0;
        do {
            int* e = (int*)(tbl[0] + off);
            bool skip = false;
            if (*e != 1) {
                skip = true;
            } else {
                IterObj it2buf[2];
                IterObj* const it2 = it2buf;
                it2->Init();
                int* slot = (int*)FUN_00e4cc40(e[1], it2);
                if (I(slot, 0xb4) != 6) {
                    it2->Release();
                    skip = true;
                } else {
                    int sub = I(slot, 0xb8);
                    it2->Release();
                    if (sub == 0) {
                        skip = true;
                    } else if (I(I(gspCellGame_s00e7_6880, 0x5190), 0x34 + sub * 4) == 0) {
                        if ((B_s00e7_6880(tbl, 0x1c) == 0 || FUN_00e699b0(key, sub)) &&
                            !FUN_00e5d340()) {
                            float minY = GF(0x016b3c8c);
                            float minZ = GF(0x016b3c90);
                            float maxX = GF(0x016b3c94);
                            float maxY = GF(0x016b3c98);
                            float maxZ = GF(0x016b3c9c);
                            float cy = (maxY + minY) * 0.5f;
                            float cz = (maxZ + minZ) * 0.5f;
                            float cx = (maxX + minY) * 0.5f;
                            float loY = (minY - cy) * 0.75f + cy;
                            float loZ = (minZ - cz) * 0.75f + cz;
                            bool inside =
                                ((maxX - cx) * 0.75f + cx <= pos[0] && pos[0] <= cx) &&
                                loY <= pos[1] &&
                                pos[1] <= (maxY - cy) * 0.75f + cy &&
                                loZ <= pos[2] &&
                                pos[2] <= (maxZ - cz) * 0.75f + cz;
                            if (inside || B_s00e7_6880(gspCellGame_s00e7_6880, 0x518c) != 0)
                                skip = true;
                        }
                    }
                }
            }
            if (skip) {
                acc += (float)e[3];
                double r = gRandomLCG_s00e7_6880.RandomDoubleUniform() * (double)acc;
                if (r < 0.0)
                    r = 0.0;
                if (r < (double)(float)e[3])
                    chosen = i;
            }
            off += 0x1c;
            i++;
        } while (i < count);
    }

    if (chosen != -1) {
        int base = tbl[0] + chosen * 0x1c;
        int kind = I(base, 0);
        if (kind == 2) {
            int n = (int)gRandomLCG_s00e7_6880.RandomUint32Uniform(U(base, 0x14));
            int num = I(base, 0x10) + n;
            if (0 < num) {
                do {
                    sDropLoot(a1, key, a3, pos, radius, lvl, I(base, 8), a8, out, outCount);
                    num--;
                } while (num != 0);
                it->Release();
                return;
            }
        } else if (kind == 1) {
            float lo = (float)I(base, 8);
            float hi = (float)I(base, 0xc);
            if (hi == 0.0f)
                hi = radius;
            int n = (int)gRandomLCG_s00e7_6880.RandomUint32Uniform(U(base, 0x14));
            int num = I(base, 0x10) + n;
            int hasPool = 0;
            int r = FUN_00e50990(I(base, 4));
            if (r != 0) {
                int ex = I(gspCellGame_s00e7_6880, 0x516c);
                int c = (int)((ObjectPool_s00e7_6880*)((char*)gspCellGame_s00e7_6880 + 0x1c))->GetSafe(ex);
                if (c != 0) {
                    B_s00e7_6880(c, 0x354) = 0;
                    FUN_00e780a0(ex, 0, 0, 0);
                    I(gspCellGame_s00e7_6880, 0x516c) = 0;
                }
                hasPool = 1;
            }
            if (0 < num) {
                int cnt = num;
                do {
                    double rnd = gRandomLCG_s00e7_6880.RandomDoubleUniform();
                    float t = (float)((double)(hi - lo) * rnd + (double)lo);
                    float* o1 = FUN_00e5cae0();
                    float p0 = pos[0] + t * o1[0];
                    float p1 = pos[1] + o1[1] * t;
                    float p2 = pos[2] + o1[2] * t;
                    float* o2 = FUN_00e5cae0();
                    float rr = (float)tbl[5];
                    float r0 = o2[0] * rr;
                    float r1 = o2[1] * rr;
                    float r2 = o2[2] * rr;
                    int sub = I(base, 0x18) + a7;
                    if (sub < 0 || 0x13 < sub)
                        sub = 0x13;
                    int made = FUN_00e76480(I(base, 4), a3, &sub, &p0, &r0, 0, tbl[4],
                                            a8, tbl[8], 0x3f400000, -1);
                    if (hasPool) {
                        int c2 = (int)((ObjectPool_s00e7_6880*)((char*)gspCellGame_s00e7_6880 + 0x1c))->GetSafe(
                                     I(gspCellGame_s00e7_6880, 0x516c));
                        if (c2 != 0)
                            *(int*)((char*)c2 + *outCount * 4) = made;
                        (void)c2;
                    }
                    cnt--;
                } while (cnt != 0);
            }
            int ex2 = I(gspCellGame_s00e7_6880, 0x516c);
            int c3 = (int)((ObjectPool_s00e7_6880*)((char*)gspCellGame_s00e7_6880 + 0x1c))->GetSafe(ex2);
            if (c3 != 0)
                B_s00e7_6880(c3, 0x354) = 1;
        }
    }
    it->Release();
}

// @ 0x00e778b0
bool FUN_00e778b0(int* p)
{
    int h = p[0x28 / 4];
    ObjectPool_s00e7_77a0& cells = gspCellGame_s00e7_77a0->mCells;
    cSpawnCell* c = (cSpawnCell*)cells.GetChecked(h);
    if (c == 0)
        return false;
    int r = FUN_00e4cce0_5(8, (int)&gCellWorldCenter_s00e7_77a0, 0.0f, 1.5f, 0.0f);
    r = FUN_00e76540(c, -1, r);
    gspCellState_s00e7_77a0->mFieldE0 = r;
    gspCellState_s00e7_77a0->mFieldF4 = 0.0f;
    return true;
}

// @ 0x00e780a0
void FUN_00e780a0(int handle, char flag, int a3, int a4)
{
    cSpawnCell* c = (cSpawnCell*)gspCellGame_s00e7_77a0->mCells.GetChecked(handle);
    if (c == 0)
        return;
    if (handle == gspCellGame_s00e7_77a0->mHandle411c)
        gspCellGame_s00e7_77a0->mHandle411c = 0;
    cSpawnCell* cc = (cSpawnCell*)gspCellGame_s00e7_77a0->mCells.Get(handle);
    FUN_00e86980(cc->mField35c, cc->mField360);
    if (cc->mField364 != -1)
        FUN_00bbbde0(gspCellGame_s00e7_77a0->mObstacleGrid, cc->mField364);
    if (cc->mPoolHandle != 0) {
        FUN_00e66010(a4);
        if (flag != 0)
            FUN_00e67890(cc);
    }
    if (cc->mField370 != 0)
        FUN_00e59200(cc->mField370);
    if (flag != 0) {
        int it[4];
        FUN_00743b50(it);
        CellInfo_s00e7_77a0* info = (CellInfo_s00e7_77a0*)FUN_00e4cc40(cc->mType, it);
        int lvl = sGetSourceLevel() - 1;
        int idx = lvl;
        if (lvl >= 0) idx = lvl;
        if (idx > 0x13) idx = 0x13;
        if (cc->mField358 != idx)
            sDropLoot(cc->mType, &cc->mKey, cc->mField35c, &cc->mPos, cc->mRadius, idx,
                      info->mFieldD4, a3, 0, 0);
        FUN_00e82130(it);
    }
    gspCellGame_s00e7_77a0->mCells.Free(handle);
}

// @ 0x00e78230
int FUN_00e78230(int a1, int a2, int a3, int count)
{
    int uv2 = FUN_00e4cce0(10);
    int uv3 = FUN_00e4cce0(0xb);
    int uv4 = FUN_00e4cce0(0xc);
    int lvl0 = GetStageLevel(gspCellGame_s00e7_77a0->mpLevelInfo->mStage);
    int cell = FUN_00e74a20(a1, a2, 0.0f, uv2, count, 1.0f, 0.0f, 1, &gDefaultTransform, -1);
    cSpawnCell* cp;
    { ObjectPool_s00e7_77a0& cells = gspCellGame_s00e7_77a0->mCells; cp = (cSpawnCell*)cells.Get(cell); }
    if (count < lvl0)
        goto done78230;
    {
        for (int i = 0; i < 10; i++) {
            Vector3_s00e7_77a0 local_18;
            FUN_00e61370(&local_18, (void*)((char*)cp + 0x48), (float)i * 0.1f);
            int att = sCreateCellAttachment(cp, 1, &local_18, count - 1, uv3, cell);
            cSpawnCell* ap;
            { ObjectPool_s00e7_77a0& cells = gspCellGame_s00e7_77a0->mCells; ap = (cSpawnCell*)cells.Get(att); }
            if (count > lvl0) {
                for (int j = 3; j < 8; j++) {
                    Vector3_s00e7_77a0 local_c;
                    FUN_00e61370(&local_c, (void*)((char*)ap + 0x48), (float)j * 0.1f);
                    sCreateCellAttachment(ap, 1, &local_c, count - 2, uv4, cell);
                }
            }
        }
    }
done78230:
    return cell;
}

// @ 0x00e783d0
namespace SP {
int sCreatePlant_Type1(int a1, int a2, int a3, int count)
{
    int uv2 = FUN_00e4cce0(0xd);
    int uv3 = FUN_00e4cce0(0xe);
    int uv4 = FUN_00e4cce0(0xf);
    int lvl0 = GetStageLevel(gspCellGame_s00e7_77a0->mpLevelInfo->mStage);
    int cell = FUN_00e74a20(a1, a2, 0.0f, uv2, count, 1.0f, 0.0f, 1, &gDefaultTransform, -1);
    cSpawnCell* cp;
    { ObjectPool_s00e7_77a0& cells = gspCellGame_s00e7_77a0->mCells; cp = (cSpawnCell*)cells.Get(cell); }
    if (count < lvl0)
        goto done783d0;
    {
        for (int i = 0; i < 7; i++) {
            Vector3_s00e7_77a0 local_18;
            FUN_00e61370(&local_18, (void*)((char*)cp + 0x48), (float)i * 0.14285715f);
            int att = sCreateCellAttachment(cp, 1, &local_18, count - 1, uv3, cell);
            cSpawnCell* ap;
            { ObjectPool_s00e7_77a0& cells = gspCellGame_s00e7_77a0->mCells; ap = (cSpawnCell*)cells.Get(att); }
            if (count > lvl0) {
                for (int j = 4; j < 7; j++) {
                    Vector3_s00e7_77a0 local_c;
                    FUN_00e61370(&local_c, (void*)((char*)ap + 0x48), (float)j * 0.1f);
                    sCreateCellAttachment(ap, 1, &local_c, count - 2, uv4, cell);
                }
            }
        }
    }
done783d0:
    return cell;
}
}  // namespace SP

// @ 0x00e78570
namespace SP {
int sCreatePlant_Type2(int a1, int a2, int a3, int count)
{
    int n = count;
    int uv3 = FUN_00e4cce0(0xe);
    int lvl0 = GetStageLevel(gspCellGame_s00e7_77a0->mpLevelInfo->mStage);
    int cell = FUN_00e74a20(a1, a2, 0.0f, uv3, count, 1.0f, 0.0f, 1, &gDefaultTransform, -1);
    if (lvl0 <= count) {
        int remaining = 8;
        int cur = cell;
        do {
            cSpawnCell* cp = (cSpawnCell*)gspCellGame_s00e7_77a0->mCells.Get(cur);
            double rnd = gMathRandom_s00e7_77a0.RandomDoubleUniform();
            float f = (float)((rnd + rnd) - 1.0);
            if (f > 1.0f) f = 1.0f;
            if (f < -1.0f) f = -1.0f;
            Vector3_s00e7_77a0 local_c;
            FUN_00e61370(&local_c, (void*)((char*)cp + 0x48), (float)(f * 0.1 + 0.75));
            int att = sCreateCellAttachment(cp, 1, &local_c, n, uv3, cur);
            gspCellGame_s00e7_77a0->mCells.Get(att);
            if (lvl0 < n)
                cur = att;
            remaining--;
        } while (remaining != 0);
    }
    return cell;
}
}  // namespace SP

// @ 0x00e794f0
void FUN_00e794f0(int a, int b, float c, char back)
{
    char* lc = *(char**)(gCellGame + 0x5190);
    *(int*)(lc + 0x90)   = 1;
    *(int*)(lc + 0x94)   = 0;
    *(int*)(lc + 0x98)   = 0;
    *(float*)(lc + 0x9c) = 0.0f;

    GetTriggerMgr()->goExit();

    char* self = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
    if (self == 0) return;

    *(int*)(gCellUI + 0xe0)   = 0;
    *(float*)(gCellUI + 0xf4) = gK_1414a84;

    char* t = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(b);
    if (t != 0) *(char*)(t + 0x354) = 0;

    char* o = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(a);
    if (o != 0) {
        if (FUN_00e5cde0(o)) {
            FUN_00e5f010(*(int*)o, *(int*)(gCellGame + 0x411c), gK_1483f34, 0);
        }
        FUN_00e780a0(a, 1, c, 0);
    }

    FUN_00e79460((float*)(self + 0x4c), *(int*)(gCellGame + 0x40fc), gK_1473c70,
                 *(int*)(gCellGame + 0x411c));

    if (back == 0) {
        *(int*)(self + 0x170)     = *(int*)(gCellGame + 0x516c);
        *(int*)(gCellUI + 0xe0)   = *(int*)(gCellGame + 0x411c);
        *(float*)(gCellUI + 0xf4) = gK_1486110;
        *(float*)(gCellUI + 0x80) = gK_13eecd8;
        FUN_00e5f010(*(int*)(gCellGame + 0x411c), *(int*)(gCellGame + 0x516c), gK_1483f34, 0);
    } else {
        *(float*)(gCellUI + 0x80) = gK_13eecd8;
        *(float*)(gCellUI + 0x48) = *(float*)(self + 0x4c);
        *(float*)(gCellUI + 0x4c) = *(float*)(self + 0x50);
        *(float*)(gCellUI + 0x50) = *(float*)(self + 0x54);
        *(float*)(gCellUI + 0x54) = *(float*)(gCellUI + 0x48);
        *(float*)(gCellUI + 0x58) = *(float*)(gCellUI + 0x4c);
        *(float*)(gCellUI + 0x5c) = *(float*)(gCellUI + 0x50);
        *(float*)(gCellUI + 0x60) = *(float*)(gCellUI + 0x48);
        *(float*)(gCellUI + 0x64) = *(float*)(gCellUI + 0x4c);
        *(float*)(gCellUI + 0x68) = *(float*)(gCellUI + 0x50);
        FUN_00e5f010(*(int*)(gCellGame + 0x516c), *(int*)(gCellGame + 0x411c), gK_1483f34, 0);
    }
    *(char*)(gCellGame + 0x518c) = 0;
}

// @ 0x00e79720
namespace SP {
void sCinematicGoldy_Start()
{
    if (*(char*)(gCellGame + 0x410c) != 0) return;

    char* self = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
    if (self == 0) return;

    *(char*)(*(int*)(gCellGame + 0x5190) + 0x68) = 1;

    char* c = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x516c));
    if (c != 0) FUN_00e780a0(*(int*)c, 0, 0.0f, 0);

    char scratch[0x18];
    float* d = FUN_00e5eb20_f((float*)scratch, (int)self);
    FUN_00e577a0((int)(self + 0x4c), d);

    FUN_00e78b20((float*)(gCellUI + 0x48), *(int*)(gCellGame + 0x40fc), gK_1486110,
                 *(int*)(gCellGame + 0x411c));
    FUN_00e78b20((float*)(gCellUI + 0x48), *(int*)(gCellGame + 0x40fc), gK_14007f4,
                 *(int*)(gCellGame + 0x411c));

    char posA[0xc], posB[0xc];
    int e1 = FUN_00e4cce0(1);
    char* cellA = (char*)FUN_00e74a20(*(int*)(gCellGame + 0x40fc), posA, 0, e1);
    int e2 = FUN_00e4cce0(2);
    char* cellB = (char*)FUN_00e74a20(*(int*)(gCellGame + 0x40fc), posB, 0, e2);

    *(char*)(gCellGame + 0x518c) = 1;

    char* p1 = (char*)((cObjectPool*)(gCellGame + 0x1c))->Get((int)cellA);
    *(char*)(p1 + 0x354) = 1;

    char* p2 = (char*)((cObjectPool*)(gCellGame + 0x1c))->Get((int)cellB);
    *(float*)(p2 + 0x230) = gK_13ec5b4;
    *(char*)(p2 + 0x354)  = 1;
    *(int*)(p2 + 0x22c)   = (int)cellA;
    *(int*)(gCellUI + 0xe0)   = (int)cellA;
    *(float*)(gCellUI + 0xf4) = gK_1473c70;

    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cCellCmd_s00e7_94f0* cmd = (cCellCmd_s00e7_94f0*)((cObjectPool*)(gCellGame + 0x54))->Get(slot);
    cmd->t1c = gK_14007f4;
    cmd->t20 = gK_14007f4;
    cmd->kind24 = 0x24;
    cmd->src28 = (int)cellA;
    cmd->arg2c = (int)cellB;
    cmd->arg30 = -1;
    cmd->arg34 = -1;
    cmd->arg38 = 0; cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = gFwd_16b3c28_s00e7_94f0; cmd->from4c = gFwd_16b3c2c_s00e7_94f0; cmd->from50 = gFwd_16b3c30_s00e7_94f0;
    cmd->to54   = gFwd_16b3c28_s00e7_94f0; cmd->to58   = gFwd_16b3c2c_s00e7_94f0; cmd->to5c   = gFwd_16b3c30_s00e7_94f0;
    cmd->dir60 = gBasis_15a7c4c_s00e7_94f0; cmd->dir64 = gBasis_15a7c50_s00e7_94f0;
    cmd->dir68 = gBasis_15a7c54_s00e7_94f0; cmd->dir6c = gBasis_15a7c58_s00e7_94f0;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    *(int*)(gCellGame + 0x5194) = slot;
    *(int*)(gCellGame + 0x5198) = slot;
    GetTriggerMgr()->PostTrigger("goldies_demise", 0, 0, 0, 0, 0);
}
}  // namespace SP

// @ 0x00e79a00
int FUN_00e79a00(int cmd, float dt)
{
    char* c = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(cmd + 0x28));
    if (c == 0) return 0;

    int flag = *(int*)(cmd + 0x70);
    float r  = *(float*)(c + 0x58) * gK_1471064;

    float scratch[0x6];
    float* d = FUN_00e5eb20_f(scratch, (int)c);

    int lvl = *(int*)(c + 0x358);
    float p[3];
    p[0] = *(float*)(c + 0x4c) + d[0] * r;
    p[1] = *(float*)(c + 0x50) + d[1] * r;
    p[2] = *(float*)(c + 0x54) + d[2] * r;

    if (lvl == -1) lvl = FUN_00e4ee60();

    FUN_00e771d0(*(int*)(c + 0x108), (int)(c + 0xfc), *(int*)(c + 0x35c), p,
                 gK_13ec480, lvl, flag, dt, 0, 0);
    return 1;
}

// @ 0x00e79af0
void FUN_00e79af0(int* cell, int flag, float f40, float f44)
{
    if (*(char*)((char*)cell + 0x112) != 0) return;
    if (*(char*)((char*)cell + 0x113) != 0) return;
    if (*(char*)((char*)cell + 0x180) != 0) return;

    int h0 = *cell;
    cObjectPool* cells = (cObjectPool*)(gCellGame + 0x1c);
    char* p = (char*)cells->Get(h0);
    float t = FUN_00e6d200((cCell*)p, 0, 0x2a, *(int*)(p + 0x1b0));
    int h = *cell;

    int slot = ((cObjectPool*)(gCellGame + 0x54))->Alloc();
    cObjectPool* cp = (cObjectPool*)(gCellGame + 0x54);
    cCellCmd_s00e7_94f0* cmd = (cCellCmd_s00e7_94f0*)cp->Get(slot);
    cmd->t1c = t; cmd->t20 = t;
    cmd->kind24 = 0x32;
    cmd->src28 = h;
    cmd->arg2c = 0;
    cmd->arg30 = -1;
    cmd->arg34 = -1;
    cmd->arg38 = 0; cmd->arg3c = 0;
    cmd->f40 = f40; cmd->f44 = f44;
    cmd->from48 = gFwd_16b3c28_s00e7_94f0; cmd->from4c = gFwd_16b3c2c_s00e7_94f0; cmd->from50 = gFwd_16b3c30_s00e7_94f0;
    cmd->to54   = gFwd_16b3c28_s00e7_94f0; cmd->to58   = gFwd_16b3c2c_s00e7_94f0; cmd->to5c   = gFwd_16b3c30_s00e7_94f0;
    cmd->dir60 = gBasis_15a7c4c_s00e7_94f0; cmd->dir64 = gBasis_15a7c50_s00e7_94f0;
    cmd->dir68 = gBasis_15a7c54_s00e7_94f0; cmd->dir6c = gBasis_15a7c58_s00e7_94f0;
    cmd->flag70 = flag; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    cObjectPool* cp2 = (cObjectPool*)(gCellGame + 0x54);
    cCellCmd_s00e7_94f0* cmd2 = (cCellCmd_s00e7_94f0*)cp2->Get(slot);
    cmd2->x04 = (int)FUN_00e79a00;
}

// @ 0x00e79c30
void FUN_00e79c30(int cell, int other, float dt)
{
    int* pi;
    int mode = *(int*)(*(int*)(gCellGame + 0x5190) + 0x7c);
    if (mode == 0) {
        pi = (int*)(other + 0x248);
    } else if (mode == 2) {
        pi = (int*)(other + 0x194);
    } else {
        pi = (int*)(other + 0xe0);
    }
    if (pi != (int*)(other + 0xe0) && *pi == -1) pi = (int*)(other + 0xe0);

    float l10 = *(float*)(pi + 7); if (l10 == 0.0f) l10 = *(float*)(pi + 6);
    float lc  = *(float*)(pi + 8); if (lc  == 0.0f) lc  = *(float*)(pi + 6);
    float l8  = *(float*)(pi + 9); if (l8  == 0.0f) l8  = *(float*)(pi + 6);

    if (*(char*)(gCellGame + 0x51dc) != 0) {
        char* av = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
        if (av != 0) {
            float dz = *(float*)(av + 0x54) - *(float*)(cell + 0x54);
            float dy = *(float*)(av + 0x50) - *(float*)(cell + 0x50);
            float dx = *(float*)(av + 0x4c) - *(float*)(cell + 0x4c);
            float inv = 1.0f / (float)sqrt((double)(dx * dx + dy * dy + dz * dz)
                                           + (double)gK_13ec4b8);
            float p[3];
            p[0] = *(float*)(cell + 0x4c) - (dx * inv) * gK_1473c70;
            p[1] = *(float*)(cell + 0x50) - (dy * inv) * gK_1473c70;
            p[2] = *(float*)(cell + 0x54) - (dz * inv) * gK_1473c70;

            void* s  = FUN_00e52910_s00e7_94f0(other);
            int   r  = FUN_00e67c40(cell, other);
            void* s2 = FUN_00e52910_s00e7_94f0(r);
            FUN_00e6f660(cell, p, dt, lc, *(int*)((char*)s2 + 0x40));
            (void)s;
            return;
        }
    }

    if (*(float*)(cell + 0x224) > 0.0f) {
        *(float*)(cell + 0x224) -= dt;
        return;
    }

    if (*(float*)(cell + 0x228) > 0.0f) {
        float x = *(float*)(cell + 0x228) - dt;
        *(char*)(cell + 0x178)  = 1;
        *(float*)(cell + 0x228) = x;
        if (x > 0.0f) return;
        void* s = FUN_00e52910_s00e7_94f0(other);
        FUN_00e791f0(cell, *(int*)((char*)s + 0x78), dt);
        return;
    }

    if (*(float*)(cell + 0x21c) > 0.0f) {
        float x = *(float*)(cell + 0x21c) - dt;
        *(float*)(cell + 0x21c) = x;
        void* s = FUN_00e52910_s00e7_94f0(other);
        int r   = FUN_00e67c40(cell, other);
        void* s2 = FUN_00e52910_s00e7_94f0(r);
        (void)s;
        FUN_00e6f940(cell, *(int*)(cell + 0x220), l8, *(int*)((char*)s2 + 0x40));
        if (*(float*)(cell + 0x21c) > 0.0f) return;
        void* s3 = FUN_00e52910_s00e7_94f0(other);
        *(float*)(cell + 0x224) = *(float*)((char*)s3 + 0x80);
        *(float*)(cell + 0x238) = 0.0f;
        return;
    }

    if (*(float*)(cell + 0x230) > 0.0f) {
        char* hold = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(cell + 0x22c));
        int ok = hold && FUN_00e57ce0(cell, hold);
        void* s = FUN_00e52910_s00e7_94f0(other);
        int r   = FUN_00e67c40(cell, other);
        void* s2 = FUN_00e52910_s00e7_94f0(r);
        (void)s;
        FUN_00e6f800(cell, *(int*)(cell + 0x22c), dt, l10, *(int*)((char*)s2 + 0x40));
        if (*(int*)(cell + 0x22c) == *(int*)(gCellGame + 0x411c))
            *(char*)(gCellGame + 0x4120) = 1;
        float x = *(float*)(cell + 0x230) - dt;
        *(float*)(cell + 0x230) = x;
        if (x > 0.0f) return;
        void* s3 = FUN_00e52910_s00e7_94f0(other);
        *(float*)(cell + 0x224) = *(float*)((char*)s3 + 0x88);
        *(float*)(cell + 0x238) = 0.0f;
        (void)ok;
        return;
    }

    void* s = FUN_00e52910_s00e7_94f0(other);
    if (*(float*)((char*)s + 0x48) > 0.0f) {
        float x = *(float*)(cell + 0x234) - dt;
        *(float*)(cell + 0x234) = x;
        if (x > 0.0f) {
            void* a = FUN_00e52910_s00e7_94f0(other);
            float f48 = *(float*)((char*)a + 0x4c);
            void* b = FUN_00e52910_s00e7_94f0(other);
            int   h50 = *(int*)((char*)b + 0x50);
            FUN_00e79af0((int*)cell, h50, f48, 0.0f);
        }
    }

    void* s4 = FUN_00e52910_s00e7_94f0(other);
    *(int*)(cell + 0x220) = 0;
    *(int*)(cell + 0x22c) = 0;
    int r  = FUN_00e67c40(cell, other);
    void* s5 = FUN_00e52910_s00e7_94f0(r);
    FUN_00e6ff60(cell, lc, *(int*)((char*)s5 + 0x40));
    (void)s4;
}

// @ 0x00e7a0a0
void FUN_00e7a0a0(int a, int b, float c)
{
    FUN_00e70e30(a, b, c);
    FUN_00e79c30(a, b, c);
}

// @ 0x00e7a0d0
void FUN_00e7a0d0(int* self, float dt)
{
    *(float*)((char*)self + 0x148) += dt;
    char* c = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)((char*)self + 0x14c));
    if (c == 0 || *(char*)(c + 0x113) != 0 || *(char*)(c + 0x112) != 0) {
        FUN_00e780a0(self[0], 0, dt, 0);
    } else if (*(float*)((char*)self + 0x148) > gK_14853e0) {
        FUN_00e780a0(self[0], 0, dt, 0);
    }
}

// @ 0x00e7a190
void FUN_00e7a190(int* self, int* other, float dt)
{
    int  mode = *(int*)(*(int*)(gCellGame + 0x5190) + 0x7c);
    int* rec;
    if (mode == 0) {
        rec = (int*)((char*)other + 0x248);
    } else if (mode == 2) {
        rec = (int*)((char*)other + 0x194);
    } else {
        rec = (int*)((char*)other + 0xe0);
    }
    if ((mode == 0 || mode == 2) && *rec == -1) rec = (int*)((char*)other + 0xe0);

    if (*rec != 0 || *self == *(int*)(gCellGame + 0x411c)) {
        FUN_00e76a80((int)self, (int)other, dt);

        if (*(char*)((char*)self + 0x112) != 0 && self[99] != 8) {
            self[99] = 10;
            return;
        }
        if (*(char*)((char*)self + 0x16c) != 0) return;
        if (*(char*)(gCellGame + 0x51db) == 1 &&
            *(int*)(gCellGame + 0x411c) == *self) return;

        int id = *self;
        if (id == *(int*)(gCellGame + 0x51b0)) {
            char* s1 = (char*)FUN_00e52910_s00e7_a190((int)other);
            float f = *(float*)(s1 + 0x1c);
            if (f == 0.0f) f = *(float*)(s1 + 0x18);
            if (*(int*)(gCellGame + 0x51b4) == 3) {
                char* s2 = (char*)FUN_00e52910_s00e7_a190((int)other);
                unsigned char b = *(unsigned char*)(s2 + 0x44);
                int r  = FUN_00e67c40((int)self, (int)other);
                char* s3 = (char*)FUN_00e52910_s00e7_a190((int)other);
                FUN_00e6f800_s00e7_a190((int)self, *(int*)(gCellGame + 0x411c), dt, f,
                             *(int*)(s3 + 0x40), r, 1, (int)b);
                return;
            }
        }
        if (id == *(int*)(gCellGame + 0x51d4)) {
            FUN_00e71c00((int)self, (int)other, dt);
            return;
        }
        if (id == *(int*)(gCellGame + 0x411c)) {
            FUN_00e6f5b0((int)self, dt);
            return;
        }

        void* ent = FUN_00e52910_s00e7_a190((int)other);
        switch (*(int*)ent) {
        case 0x1001: FUN_00e71300(dt); break;
        case 0x1003: FUN_00e70650((int)self, dt); return;
        case 0x1004: FUN_00e704b0((int)self, (int)other, dt); return;
        case 0x1005: FUN_00e702d0((int)self, (int)other, dt); return;
        case 0x1006: FUN_00e7a0a0((int)self, (int)other, dt); return;
        case 0x1007: FUN_00e6f990((int)self, dt); return;
        case 0x1008: SP::sUpdateAICaterpillar((int)self, dt); return;
        case 0x1009: FUN_00e707d0((int)self, dt); return;
        case 0x100b: FUN_00e6fbb0((int)self, dt); return;
        case 0x100c: FUN_00e6fd70((int)self, dt); return;
        case 0x100d: FUN_00e6fce0((int)self, dt); return;
        case 0x100e: FUN_00e7a0d0(self, dt); return;
        }
    }
}

// @ 0x00e7a4a0
int FUN_00e7a4a0(int* cell, int p2, int p3, int p4, int p5, float p6)
{
    if (*(char*)((char*)cell + 0x112) != 0) return 0;
    if (*(char*)((char*)cell + 0x113) != 0) return 0;

    if (*(int*)(gCellGame + 0x411c) == *cell) {
        if (*(char*)(gCellGame + 0x5169) != 0) return 0;
        int v = *(int*)(gCellGame + 0x5158);
        if (v == 5 || v == 3) return 0;
        FUN_00e72060(cell, p2, p3, p6);
        return 1;
    }

    *(char*)((char*)cell + 0x113) = 1;
    int n = FUN_00e57340((int)cell);
    if (n < 2) {
        int h = FNV1_String8_s00e7_a190("cell_death_oneshot_small", 0x811c9dc5u, 1);
        FUN_00e66840((int)cell, h);
    } else {
        n = FUN_00e57340((int)cell);
        const char* s = (n < 3) ? "cell_death_oneshot" : "cell_death_oneshot_large";
        FUN_00e66840((int)cell, SPIDFromName(s));
    }
    FUN_00e71f00(cell, p2);

    if (p4 != 0) {
        FUN_00e514c0();
        (*(int*)(*(int*)(gCellGame + 0x5190) + 0x6c))++;
    }

    if (*(int*)((char*)cell + 0x358) != 0) {
        char raw[0x10];
        cLayerCtx* ctx = (cLayerCtx*)raw;
        ctx->Begin();
        void* e = FUN_00e4cc40(*(int*)((char*)cell + 0x108), raw);
        int lvl = SP::sGetSourceLevel();
        int v   = *(int*)((char*)cell + 0x358);
        if (v > lvl - 1 && v < lvl + 2) {
            int u = FUN_00e52a40(v, -1, *(int*)((char*)e + 0xd4), p6, 0, 0);
            SP::sDropLoot(*(int*)((char*)cell + 0x108), (int)((char*)cell + 0xfc),
                          *(int*)((char*)cell + 0x35c), (float*)((char*)cell + 0x4c),
                          *(float*)((char*)cell + 0x58), u, p5, p6, 0, 0);
        }
        ctx->End();
    }

    void* c1 = ((cObjectPool_s00e7_a190*)(gCellGame + 0x1c))->Get(*cell);
    FUN_00e6d200((cCell*)c1, 0, 10, *(int*)((char*)c1 + 0x1b0));
    void* c2 = ((cObjectPool_s00e7_a190*)(gCellGame + 0x1c))->Get(*cell);
    float t  = FUN_00e6d200((cCell*)c2, 0, 7, *(int*)((char*)c2 + 0x1b0));

    int slot = ((cObjectPool_s00e7_a190*)(gCellGame + 0x54))->Alloc();
    cCellCmd_s00e7_a190* cmd = (cCellCmd_s00e7_a190*)((cObjectPool_s00e7_a190*)(gCellGame + 0x54))->Get(slot);
    cmd->t1c = t; cmd->t20 = t;
    cmd->kind24 = 6;
    cmd->src28 = *cell;
    cmd->arg2c = 0;
    cmd->arg30 = -1; cmd->arg34 = -1;
    cmd->arg38 = 0;  cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = *(int*)&gFwd_16b3c28; cmd->from4c = *(int*)&gFwd_16b3c2c;
    cmd->from50 = *(int*)&gFwd_16b3c30;
    cmd->to54   = *(int*)&gFwd_16b3c28; cmd->to58   = *(int*)&gFwd_16b3c2c;
    cmd->to5c   = *(int*)&gFwd_16b3c30;
    cmd->dir60  = *(int*)&gBasis_15a7c4c; cmd->dir64 = *(int*)&gBasis_15a7c50;
    cmd->dir68  = *(int*)&gBasis_15a7c54; cmd->dir6c = *(int*)&gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    FUN_00e59170(*cell, p6);
    return 1;
}

// @ 0x00e7a770
void FUN_00e7a770(int handle, int a, int b, int c, int d, float f)
{
    cObjectPool_s00e7_a190* pool = (cObjectPool_s00e7_a190*)(gCellGame + 0x1c);
    char* cell = (char*)pool->GetSafe(handle);
    if (cell == 0) return;
    if (*(int*)(cell + 0x244) != 0) return;
    FUN_00e7a4a0((int*)cell, a, b, c, d, f);
}

// @ 0x00e7aa20
void FUN_00e7aa20(int* p, float dt)
{
    char* iVar12 = (char*)((cObjectPool_s00e7_a190*)(gCellGame + 0x1c))->GetSafe(p[1]);
    if (iVar12 == 0) {
        if (*(char*)((char*)p + 0x48) != 0) {
            FUN_00e780a0(p[3], 0, 0.0f, 0);
            return;
        }
        FUN_00e59200(*p);
        return;
    }
    char* iVar13 = (char*)((cObjectPool_s00e7_a190*)(gCellGame + 0x1c))->GetSafe(p[3]);
    if (iVar13 == 0) {
        FUN_00e59200(*p);
        return;
    }

    float mat[6];
    memset(mat, 0, sizeof(mat));
    mat[0] = gFwd_16b3c28;
    mat[1] = gFwd_16b3c2c;
    mat[3] = gFwd_16b3c30;
    mat[5] = gk_1485720;
    (void)dt;

    char m33[0x1c];
    FUN_0041cb40(m33, &gMatrix_16b3dac);
    FUN_00e68000((int)iVar12, p[2], (cSPTransform_s00e7_6880*)mat);

    char* xf = iVar13 + 0x48;
    FUN_0040ce80(xf);
    float saved58 = *(float*)(iVar13 + 0x58);
    FUN_00537dc0(xf, mat);
    FUN_0040ccb0(xf, (char*)p + 0x10);
    *(float*)(iVar13 + 0x58) = saved58;
    *(short*)(iVar13 + 0x4a) += 1;
    float saved4c = *(float*)(iVar13 + 0x4c);
    float saved50 = *(float*)(iVar13 + 0x50);
    *(short*)(xf) |= 4;
    *(short*)(iVar13 + 0x4a) += 1;
    *(float*)(iVar13 + 0x4c) = saved4c;
    *(float*)(iVar13 + 0x50) = saved50;
    *(float*)(iVar13 + 0x54) = 0.0f;

    if (*(int*)(iVar13 + 0x248) != 0 && *(int*)(iVar13 + 0x250) > 1) {
        char xf2[0x40];
        FUN_0040ce80(xf2);   // scratch transform copy source (kept logical)
        int* idx = (int*)(iVar13 + 0x254);
        for (int i = 0; i < *(int*)(iVar13 + 0x250); ++i, ++idx) {
            float* pt = (float*)(*(int*)(gCellGame + 0x4108) + 4 + *idx * 0xc);
            FUN_004ff6d0(xf, pt);
            float z = pt[2], y = pt[1], x = pt[0];
            if ((*(short*)(xf) & 2) != 0) {
                pt[0] = *(float*)(iVar13 + 0x5c) * x + *(float*)(iVar13 + 0x68) * y +
                        *(float*)(iVar13 + 0x74) * z;
                pt[1] = *(float*)(iVar13 + 0x60) * x + *(float*)(iVar13 + 0x6c) * y +
                        *(float*)(iVar13 + 0x78) * z;
                pt[2] = *(float*)(iVar13 + 0x64) * x + *(float*)(iVar13 + 0x70) * y +
                        *(float*)(iVar13 + 0x7c) * z;
            }
            float s = *(float*)(iVar13 + 0x58);
            pt[0] = pt[0] * s + *(float*)(iVar13 + 0x4c);
            pt[1] = pt[1] * s + *(float*)(iVar13 + 0x50);
            pt[2] = pt[2] * s + *(float*)(iVar13 + 0x54);
        }
    }

    int anim = *(int*)(iVar13 + 0x248);
    if (anim != 0) {
        int src = FUN_00e516c0((cCell*)iVar13);
        void* ag = (void*)((cObjectPool_s00e7_a190*)(gCellGame + 0x1c))->Next((int*)&anim);

        float f = FUN_00e6d6d0((int)iVar13, (int)(iVar13 + 0xc0), *(int*)(iVar13 + 0x18c),
                               *(int*)(iVar13 + 0x24c), src, *(int*)(iVar13 + 0x35c));
        FUN_00e62b80(xf, *(int*)(iVar13 + 0xa0), *(int*)(iVar13 + 0x80), f,
                     (int)(iVar13 + 0xc0), *(int*)(iVar13 + 0x18c), *(int*)(iVar13 + 0x24c),
                     src, *(int*)(iVar13 + 0x35c));
        (void)ag;
    }
}

// @ 0x00e7ad70
void FUN_00e7ad70(float dt)
{
    int it = ((cObjectPool_s00e7_a190*)(gCellGame + 0x8c))->Front();
    for (;;) {
        cObjectPool_s00e7_a190* pool = (cObjectPool_s00e7_a190*)(gCellGame + 0x8c);
        void* e = (void*)pool->Next(&it);
        if (e == 0) break;
        FUN_00e7aa20((int*)e, dt);
    }
}

// @ 0x00e7add0
void FUN_00e7add0(int handle, int p2, float dt)
{
    char* c = (char*)((cObjectPool_s00e7_a190*)(gCellGame + 0x1c))->GetSafe(handle);
    if (c == 0) return;

    char raw[0x10];
    cLayerCtx* ctx = (cLayerCtx*)raw;
    ctx->Begin();
    FUN_00e4cc40(*(int*)(c + 0x108), raw);

    if (*(int*)(c + 0x358) != 0) {
        int lc[3];
        lc[1] = *(int*)(c + 0x358) - 1;
        lc[2] = 0x13;
        lc[0] = 0;
        int* pv = lc;
        if (lc[1] >= 0) pv = lc + 1;
        if (*pv > 0x13) pv = lc + 2;
        int entry = FUN_00e4cce0(7);
        SP::sDropLoot(*(int*)(c + 0x108), (int)(c + 0xfc), *(int*)(c + 0x35c),
                      (float*)(c + 0x4c), *(float*)(c + 0x58), *pv, entry, dt, 0, 0);
    }

    if (handle == *(int*)(gCellGame + 0x411c)) {
        FUN_00e72200(p2);
        ctx->End();
        return;
    }
    FUN_00e780a0(handle, 1, dt, 0);
    ctx->End();
}

// @ 0x00e7aee0
void FUN_00e7aee0(int* cell, int* other, float dt)
{
    int st = cell[99];
    if (st == 7 || st == 8 || st == 9) return;
    if (*(char*)((char*)cell + 0x17c) != 0) return;

    int h = FNV1_String8_s00e7_a190("cell_death_break", 0x811c9dc5u, 1);
    FUN_00e66840((int)cell, h);

    if (*(int*)((char*)cell + 0xfc) == 0) {
        FUN_00e7add0(*cell, 0, dt);
        return;
    }

    if (*other == *(int*)(gCellGame + 0x411c) && *(char*)((char*)cell + 0x112) == 0) {
        FUN_00e514c0();
        (*(int*)(*(int*)(gCellGame + 0x5190) + 0x6c))++;
    }
    if (*cell == *(int*)(gCellGame + 0x411c)) {
        FUN_00e5c8e0();
        (*(int*)(*(int*)(gCellGame + 0x5190) + 0x70))++;
    }

    void* c1 = ((cObjectPool_s00e7_a190*)(gCellGame + 0x1c))->Get(*cell);
    float t  = FUN_00e6d200((cCell*)c1, 0, 8, *(int*)((char*)c1 + 0x1b0));

    int slot = ((cObjectPool_s00e7_a190*)(gCellGame + 0x54))->Alloc();
    cCellCmd_s00e7_a190* cmd = (cCellCmd_s00e7_a190*)((cObjectPool_s00e7_a190*)(gCellGame + 0x54))->Get(slot);
    cmd->t1c = t; cmd->t20 = t;
    cmd->kind24 = 5;
    cmd->src28 = *cell;
    cmd->arg2c = 0;
    cmd->arg30 = -1; cmd->arg34 = -1;
    cmd->arg38 = 0;  cmd->arg3c = 0;
    cmd->f40 = 0.0f; cmd->f44 = 0.0f;
    cmd->from48 = *(int*)&gFwd_16b3c28; cmd->from4c = *(int*)&gFwd_16b3c2c;
    cmd->from50 = *(int*)&gFwd_16b3c30;
    cmd->to54   = *(int*)&gFwd_16b3c28; cmd->to58   = *(int*)&gFwd_16b3c2c;
    cmd->to5c   = *(int*)&gFwd_16b3c30;
    cmd->dir60  = *(int*)&gBasis_15a7c4c; cmd->dir64 = *(int*)&gBasis_15a7c50;
    cmd->dir68  = *(int*)&gBasis_15a7c54; cmd->dir6c = *(int*)&gBasis_15a7c58;
    cmd->flag70 = 0; cmd->flag74 = 0; cmd->flag78 = 0;
    cmd->x04 = 0; cmd->x08 = 0;

    FUN_00e59260(*cell);
}

// @ 0x00e7b0a0
bool FUN_00e7b0a0(int hA, int hB, void* p3, float* dir, int e, float t)
{
    void* pa = cells_s00e7_b0a0()->GetSafe(hA);
    if (pa == 0)
        return false;
    void* pb = cells_s00e7_b0a0()->GetSafe(hB);
    if (pb == 0)
        return false;
    B_s00e7_b0a0(pa, 0x178) = 1;
    B_s00e7_b0a0(pb, 0x178) = 1;
    Vec3_s00e7_b0a0 d;
    if (FUN_00e57340(pb) >= 3) {
        if (FUN_00e52960()) {
            Vec3_s00e7_b0a0 tv = { dir[0], dir[1], dir[2] };
            d.x = -tv.x;
            d.y = -tv.y;
            d.z = -tv.z;
            FUN_00e7a7c0(pb, pa, &d, 4, e, t);
            void* unused;
            int level = sGetSourceLevel(unused, I(I(gspCellGame_s00e7_b0a0, 0x5190), 0x1c));
            FUN_00e76af0(pb, p3, level, FUN_00e4cce0_s00e7_b0a0(0x1b), -1);
            return true;
        }
        return false;
    }
    if (FUN_00e52960()) {
        if (I(pb, 0x244) > FUN_00e58980(pa, pb)) {
            Vec3_s00e7_b0a0 tv = { dir[0], dir[1], dir[2] };
            d.x = -tv.x;
            d.y = -tv.y;
            d.z = -tv.z;
            FUN_00e7a7c0(pb, pa, &d, 4, e, t);
            return true;
        }
    }
    FUN_00e7aee0(pb, pa, t);
    return true;
}

// @ 0x00e7b240
void FUN_00e7b240(int h, float t)
{
    cObjectPool_s00e7_b0a0* pool = (cObjectPool_s00e7_b0a0*)(gspCellGame_s00e7_b0a0 + 0x1c); void* c = pool->GetSafe(h);
    if (c != 0)
        FUN_00e7a4a0(c, 0, 0, 1, 3, t);
}

// @ 0x00e7b280
bool FUN_00e7b280(void* m, float t)
{
    void* pa = cells_s00e7_b0a0()->GetSafe(I(m, 0x28));
    void* pb = cells_s00e7_b0a0()->GetSafe(I(m, 0x2c));
    if (pa == 0)
        return false;
    if (pb == 0)
        return false;
    if (B_s00e7_b0a0(pa, 0x17f) != 0)
        return false;
    if (B_s00e7_b0a0(pb, 0x17c) != 0)
        return false;
    Vec3_s00e7_b0a0 d;
    if (FUN_00e57340(pb) >= 3) {
        if (FUN_00e52960()) {
            Vec3_s00e7_b0a0 tv = { F(m, 0x48), F(m, 0x4c), F(m, 0x50) };
            d.x = -tv.x;
            d.y = -tv.y;
            d.z = -tv.z;
            FUN_00e7a7c0(pb, pa, &d, 5, 1, t);
            int level = sGetSourceLevel(gspCellGame_s00e7_b0a0, I(I(gspCellGame_s00e7_b0a0, 0x5190), 0x1c));
            FUN_00e76af0(pb, (char*)m + 0x54, level, FUN_00e4cce0_s00e7_b0a0(0x1b), -1);
            return true;
        }
        return false;
    }
    if (FUN_00e52960()) {
        if (I(pb, 0x244) > FUN_00e58980(pa, pb)) {
            Vec3_s00e7_b0a0 tv = { F(m, 0x48), F(m, 0x4c), F(m, 0x50) };
            d.x = -tv.x;
            d.y = -tv.y;
            d.z = -tv.z;
            FUN_00e7a7c0(pb, pa, &d, 5, 1, t);
            return true;
        }
    }
    FUN_00e7aee0(pb, pa, t);
    return true;
}

// @ 0x00e7b410
void FUN_00e7b410(int h, char b)
{
    if (h == I(gspCellGame_s00e7_b0a0, 0x411c)) {
        GetTriggerMgr_s00e7_b0a0()->setModal(0);
        B_s00e7_b0a0(gspCellUI_s00e7_b0a0, 0x936) = 0;
        B_s00e7_b0a0(gspCellGame_s00e7_b0a0, 0x51d8) = 1;
        B_s00e7_b0a0(gspCellGame_s00e7_b0a0, 0x51d9) = b;
        return;
    }
    FUN_00e780a0(h, 1, 0.0f, 0);
}

// @ 0x00e7b470
void FUN_00e7b470(void* self, void* other, int a2, void* a3)
{
    if (B_s00e7_b0a0(other, 0x17c) != 0)
        return;
    if (B_s00e7_b0a0(other, 0x17b) != 0)
        return;
    if (B_s00e7_b0a0(self, 0x178) != 0)
        return;
    if (B_s00e7_b0a0(self, 0x17f) != 0)
        return;
    if (FUN_00e57460_s00e7_b0a0(self, other))
        return;
    void* r = cells_s00e7_b0a0()->Get(I(self, 0));
    float f = FUN_00e6d200(r, 0, 5, I(r, 0x1b0));
    FUN_00e51ee0(4, f, I(self, 0), I(other, 0), a2, -1, 0, 0, 0.0f, 0.0f,
                 (int)self, (int)a3, 0, 0, 0, 0);
    FUN_00e528d0((void (*)(void))FUN_00e7b280);
    FUN_00e59560(I(other, 0), a2);
}

// @ 0x00e7b540
bool __fastcall FUN_00e7b540(cCellMessage* m, int a, float t)
{
    switch (m->type) {
    case 10:
        if (a == 0)
            return FUN_00e7b0a0(m->a28, m->a2c, (char*)m + 0x48, (float*)((char*)m + 0x54),
                                m->a38, t);
        break;
    case 0x12:
    case 0x13:
    case 0x14:
        break;
    default:
        break;
    }
    return true;
}

// @ 0x00e7b5d0
void FUN_00e7b5d0(void* a, void* b)
{
    if (B_s00e7_b0a0(a, 0x112) == 1 || B_s00e7_b0a0(a, 0x113) == 1)
        return;
    {
        char buf[0x18];
        FUN_00743b50(buf);
        FUN_00e4cc40(I(b, 0x108), buf);
        FUN_00e780a0(I(b, 0), 1, 0.0f, 0);
        FUN_00e82130(buf);
    }
}

// @ 0x00e7b630
void FUN_00e7b630(void* self, void* other)
{
    if (B_s00e7_b0a0(self, 0x112) == 1 || B_s00e7_b0a0(self, 0x113) == 1)
        return;
    if (B_s00e7_b0a0(self, 0x178) != 0 || B_s00e7_b0a0(self, 0x17f) != 0 || B_s00e7_b0a0(other, 0x17b) != 0)
        return;
    void* r = cells_s00e7_b0a0()->Get(I(self, 0));
    float f = FUN_00e6d200(r, 0, 0x31, I(r, 0x1b0));
    int mh = msgs()->Alloc();
    cCellMessage* m = (cCellMessage*)msgs()->Get(mh);
    m->f1c = f;
    m->f20 = f;
    m->type = 0x20;
    m->a28 = I(self, 0);
    m->a2c = 0;
    m->a30 = -1;
    m->a34 = -1;
    m->a38 = 0;
    m->a3c = 0;
    m->f40 = 0.0f;
    m->f44 = 0.0f;
    m->v48.x = gCellWorldCenter_s00e7_b0a0.x;
    m->v48.y = gCellWorldCenter_s00e7_b0a0.y;
    m->v48.z = gCellWorldCenter_s00e7_b0a0.z;
    m->v54.x = gCellWorldCenter_s00e7_b0a0.x;
    m->v54.y = gCellWorldCenter_s00e7_b0a0.y;
    m->v54.z = gCellWorldCenter_s00e7_b0a0.z;
    m->v60.x = g_15a7c4c[0];
    m->v60.y = g_15a7c4c[1];
    m->v60.z = g_15a7c4c[2];
    m->a6c = (int)g_15a7c4c[3];
    m->a70 = 0;
    m->b74 = 0;
    m->a78 = 0;
    m->cb = 0;
    m->st8 = 0;
    {
        char buf[0x18];
        FUN_00743b50(buf);
        void* def = FUN_00e4cc40(I(other, 0x108), buf);
        FUN_00e5d7b0(I(def, 0xb8));
        FUN_00e780a0(I(other, 0), 1, 0.0f, 0);
        FUN_00e59a70(I(self, 0));
        FUN_00e82130(buf);
    }
}

// @ 0x00e7b7c0
void FUN_00e7b7c0(void* list, void* x, void* pos, float t)
{
    int* r = ((cOccupancy*)list)->Claim();
    *r = I(x, 0);
    if (I(x, 0) == I(gspCellGame_s00e7_b0a0, 0x516c))
        return;
    if (I(x, 0xfc) != 0) {
        FUN_00e77ac0(x, pos, FUN_00e4cce0_s00e7_b0a0(7), t);
    } else {
        char buf[0x18];
        FUN_00743b50(buf);
        void* def = FUN_00e4cc40(I(x, 0x108), buf);
        FUN_00e77ac0(x, pos, P(def, 0xd8), t);
        FUN_00e82130(buf);
    }
    int key = 0xf620401c;
    FUN_00e61b90(I(x, 0x35c) != I(gspCellGame_s00e7_b0a0, 0x40fc), 0, (char*)x + 0x4c, &key);
    FUN_00e780a0(I(x, 0), 1, t, 0);
}

// @ 0x00e7b8a0
int FUN_00e7b8a0(void* p, float a, float b)
{
    int buf[0x200];
    int n = FUN_00e87260(I(p, 0), (char*)p + 4, (0.5f - (a + b)) * 15.0f, buf, 0x200, 0);
    for (int i = 0; i < n; i++) {
        int key = buf[i];
        int* base = (int*)I(p, 0x10);
        int* end = (int*)I(p, 0x14);
        int* it = base;
        int cnt = (int)((char*)end - (char*)base) >> 3;
        while (cnt > 0) {
            int half = cnt >> 1;
            int* mid = it + half * 2;
            if (*mid < key) {
                it = mid + 2;
                cnt -= half + 1;
            } else {
                cnt = half;
            }
        }
        if (it != end && key >= *it)
            continue;
        FUN_00e7b7c0((char*)p + 0x10, cells_s00e7_b0a0()->Get(key), (char*)p + 4, b);
    }
    return 1;
}

// @ 0x00e7b9b0
void FUN_00e7b9b0(int hA, int hB, float t)
{
    FUN_00e780a0(hB, 1, t, 0);
    cObjectPool_s00e7_b0a0* pool = (cObjectPool_s00e7_b0a0*)(gspCellGame_s00e7_b0a0 + 0x1c); void* c = pool->GetSafe(hA);
    if (c != 0) {
        if (I(c, 0x168) != 0) {
            FUN_00e59200(P(c, 0x168));
            I(c, 0x168) = 0;
        }
        I(c, 0x220) = I(gspCellGame_s00e7_b0a0, 0x411c);
        F(c, 0x21c) = 300.0f;
    }
}

// @ 0x00e7ba30
int FUN_00e7ba30(void* m, float t)
{
    switch (I(m, 0x24)) {
    case 1:
        FUN_00e69a90(I(m, 0x28), I(m, 0x2c), I(m, 0x30), I(m, 0x38), F(m, 0xc), t);
        break;
    case 2:
        FUN_00e59010(I(m, 0x28), I(m, 0x2c), I(m, 0x38), F(m, 0xc) <= 0.0f,
                     F(m, 0x20) - F(m, 0x1c), (char*)m + 0x48);
        break;
    case 3:
        FUN_00e76360((char*)m + 0x28, I(m, 0x38), I(m, 0x70), I(m, 0x3c),
                     (char*)m + 0x48, (char*)m + 0x54, (char*)m + 0x60, I(m, 0x40),
                     F(m, 0x20) - F(m, 0x1c), I(m, 0x44), I(m, 0x78), t);
        break;
    case 4:
        FUN_00e59560(I(m, 0x2c), I(m, 0x30));
        break;
    case 5:
        FUN_00e59260(I(m, 0x28));
        break;
    case 6:
        FUN_00e59170(I(m, 0x28), t);
        break;
    case 7:
        FUN_00e59500(I(m, 0x28));
        break;
    case 8:
        FUN_00e57c30(I(m, 0x28), I(m, 0x2c), I(m, 0x38), t);
        break;
    case 9:
        FUN_00e57a60(I(m, 0x28), I(m, 0x2c), I(m, 0x30), I(m, 0x38), (char*)m + 0x48);
        break;
    case 10:
        FUN_00e592f0(I(m, 0x28), I(m, 0x2c), I(m, 0x30), (char*)m + 0x48, (char*)m + 0x54);
        break;
    case 11:
        FUN_00e57b50(I(m, 0x28), I(m, 0x30), I(m, 0x38), (char*)m + 0x48);
        break;
    case 12:
        FUN_00e579c0(I(m, 0x28), I(m, 0x2c));
        break;
    case 13:
        FUN_00e57c90(I(m, 0x28), I(m, 0x2c));
        break;
    case 14:
        FUN_00e593b0(I(m, 0x28), I(m, 0x2c), I(m, 0x30), (char*)m + 0x48);
        break;
    case 15:
        FUN_00e599b0(I(m, 0x28));
        break;
    case 16:
        FUN_00e7b8a0((char*)m + 0x70, F(m, 0x1c), t);
        break;
    case 17:
        FUN_00e58890(I(m, 0x28), I(m, 0x2c), I(m, 0x30));
        break;
    case 18:
        FUN_00e69e00(I(m, 0x28), I(m, 0x2c), I(m, 0x30), F(m, 0xc), t);
        break;
    case 19:
        FUN_00e69c10(I(m, 0x28), I(m, 0x2c), I(m, 0x30), F(m, 0xc), t);
        break;
    case 20:
        FUN_00e59710(I(m, 0x28), I(m, 0x2c), I(m, 0x30), F(m, 0xc), F(m, 0x10), t);
        break;
    case 21:
        FUN_00e59640(I(m, 0x28), I(m, 0x2c), I(m, 0x30), I(m, 0x38), (char*)m + 0x48);
        break;
    case 25:
        FUN_00e58ae0(I(m, 0x28));
        break;
    case 26:
        FUN_00e58bf0(I(m, 0x28), F(m, 0x20) - F(m, 0x1c), F(m, 0x20));
        break;
    case 27:
        FUN_00e5ec70(I(m, 0x28), F(m, 0x1c));
        break;
    case 28:
        FUN_00e5ec10(I(m, 0x28));
        break;
    case 29:
        FUN_00e591c0(I(m, 0x28), t);
        break;
    case 30:
        FUN_00e598e0(I(m, 0x28), F(m, 0x1c));
        break;
    case 31:
        FUN_00e59a30();
        break;
    case 32:
        FUN_00e59a70(I(m, 0x28));
        break;
    case 33:
        FUN_00e571f0(I(m, 0x28), I(m, 0x38));
        break;
    case 34:
        FUN_00e5ed50(I(m, 0x28), (char*)m + 0x48, (char*)m + 0x60, F(m, 0x1c), F(m, 0x20));
        break;
    case 36:
        FUN_00e5f160(I(m, 0x28), I(m, 0x2c), m, t);
        break;
    case 38:
        FUN_00e59b50(I(m, 0x28), I(m, 0x30), (char*)m + 0x48);
        break;
    case 39:
        FUN_00e59af0(I(m, 0x28), I(m, 0x30));
        break;
    case 40:
        FUN_00e59af0(I(m, 0x28), I(m, 0x30));
        break;
    case 41:
        FUN_00e6a090(I(m, 0x28), I(m, 0x2c), I(m, 0x30), F(m, 0xc), t);
        break;
    case 42:
        FUN_00e59470(I(m, 0x28));
        break;
    case 43:
        FUN_00e532e0((char*)m + 0x74, F(m, 0x20) - F(m, 0x1c));
        break;
    case 44:
        FUN_00e56820(F(m, 0x20) - F(m, 0x1c), F(m, 0x20));
        break;
    case 45:
        FUN_00e75c30(t);
        break;
    case 46:
        FUN_00e53d50(F(m, 0x20) - F(m, 0x1c), F(m, 0xc));
        break;
    case 47:
        FUN_00e53c70(m, F(m, 0x1c), t);
        break;
    case 48:
        FUN_00e569b0();
        break;
    case 49:
        FUN_00e569b0();
        break;
    case 50:
        FUN_00e57dc0(I(m, 0x28));
        break;
    default:
        break;
    }
    return 1;
}

// @ 0x00e7ce10
void FUN_00e7ce10(int add, char flag)
{
    char* lvl = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
    if (B(lvl, 0x68) == 0 && I(lvl, 0x1c) > 0x77 && I(lvl, 0x1c) < 0x97) {
        int cnt = 0;
        int n = 13;
        int* p = (int*)(lvl + 0x34);
        do { if (*p != 0) ++cnt; ++p; --n; } while (n != 0);
        cnt -= 4;
        if (cnt < 1 && I(lvl, 0x7c) != 2)
            FUN_00e79720();
    }
    lvl = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
    int old = I(lvl, 0x1c);
    I(lvl, 0x1c) = I(lvl, 0x1c) + add;
    if (I(lvl, 0x1c) > 0x3e8)
        I(lvl, 0x1c) = g_levelMaxTime;
    int delta = (old - I(lvl, 0x1c)) + add;
    if (delta > 0) {
        if (flag != 0) I(lvl, 0x24) += delta;
        else           I(lvl, 0x28) += delta;
    }
    if (old != I(lvl, 0x1c)) {
        if (flag != 0)
            I(lvl, 0x20) += I(lvl, 0x1c) - old;
        char* player = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c))->GetSafe(I(gspCellGame_s00e7_ce10, 0x411c));
        FUN_00e51430(I(lvl, 0x1c));
        FUN_00e51430(old);
        FUN_00e648d0(player);
        float f_old = FUN_00e4eea0(0, old);
        float f_new = FUN_00e4eea0(0, I(lvl, 0x1c));
        if (f_old != f_new) {
            F(gspCellGame_s00e7_ce10, 0x5150) = f_new;
            FUN_00e7cd10();
        }
        float r_old = FUN_00e4eef0(0, old);
        float r_new = FUN_00e4eef0(0, I(lvl, 0x1c));
        if (f_old != f_new || r_old != r_new) {
            char* q = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c))->Get(I(gspCellGame_s00e7_ce10, 0x411c));
            if (r_new > r_old || f_new > f_old)
                FUN_00e72b40((int*)q);
            else
                FUN_00e57170_s00e7_ce10(I(q, 0), r_new);
            F(gspCellGame_s00e7_ce10, 0x51bc) = FUN_00e52b70();
            B(gspCellGame_s00e7_ce10, 0x51c0) = 0;
        }
        if (I(lvl, 0x1c) == 1000) {
            char ref[4];
            FUN_00743b50(ref);
            char* info = (char*)FUN_00e4ce40(ref);
            int x = I(info, 0xdc);
            FUN_00e82130(ref);
            if (x == 1 || FUN_00e4fca0() == 2)
                FUN_00e6e8c0(0);
        }
    }
}

// @ 0x00e7d070
void FUN_00e7d070(int handle, int param_1, float param_2)
{
    if (I(gspCellGame_s00e7_ce10, 0x411c) == 0)
        return;
    char* cell = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c))->Get(I(gspCellGame_s00e7_ce10, 0x411c));
    char ref[4];
    FUN_00743b50(ref);
    char* ent = 0;
    if (handle != g_keyDefaultFood)
        ent = (char*)FUN_00e4cc40(handle, ref);
    if (ent != 0) {
        if (B(ent, 0x314) != 0)
            FUN_00e671c0(cell);
        if (B(ent, 0x315) != 0)
            FUN_00e77d50(param_2);
    }
    int* pi = (int*)(cell + 0x244);
    int v = *pi;
    if (v < 6) {
        if (ent == 0) {
            if (I(gspCellGame_s00e7_ce10, 0x411c) == I(cell, 0))
                FUN_00e62340(cell, v);
            *pi += 2;
        } else if (I(ent, 0x310) > 0) {
            if (I(gspCellGame_s00e7_ce10, 0x411c) == I(cell, 0))
                FUN_00e62340(cell, v);
            char* lvl = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
            if (I(lvl, 0x7c) == 0)
                *pi += I(ent, 0x310) * 2;
            else
                *pi += I(ent, 0x310);
        }
    }
    int six = 6;
    if (*pi < 6) six = *pi;
    *pi = six;
    int a;
    if (ent == 0) {
        a = 10;
    } else {
        a = I(ent, 0x30c);
        if (a == 0) {
            FUN_00e82130(ref);
            return;
        }
    }
    B(*(char**)(gspCellGame_s00e7_ce10 + 0x5190), 0xe1) = 1;
    FUN_00e51650();
    char* lvl = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
    if (B(lvl, 0x69) == 0 && I(lvl, 0x1c) > 0x95) {
        F(gspCellGame_s00e7_ce10, 0x51d0) = g_147b9f0;
        B(lvl, 0x69) = 1;
    }
    lvl = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
    if (I(lvl, 0x80) == 1) {
        int* pi2 = (int*)(lvl + 0x84);
        if (*pi2 != 5) {
            *pi2 += 1;
            int cap = 5;
            if (*pi2 < 6) cap = *pi2;
            *pi2 = cap;
            if (cap == 5)
                FUN_00e53460();
        }
    }
    int first;
    if (ent == 0) first = 1;
    else if ((B(ent, 0xb0) & 1) == 0) first = (I(ent, 0xb4) == 3) ? 1 : 0;
    else if (param_1 == 2) first = 0;
    else if (param_1 == 3) first = 1;
    else if (param_1 == 4) first = 0;
    else first = (I(ent, 0xb4) == 3) ? 1 : 0;
    FUN_00e7ce10(a, (char)first);
    char* lvl2 = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
    int buf[10];
    for (int i = 0; i < 10; ++i) buf[i] = 0;
    if (first)
        FUN_00e394f0(0x9ef61113, lvl2 + 0x10, buf + 7, buf + 4, buf + 1);
    else
        FUN_00e394f0(0xac7161b5, lvl2 + 0x10, buf + 1, buf + 4, buf + 7);
    FUN_00e82130(ref);
}

// @ 0x00e7d370
void FUN_00e7d370(int param_1, int* vec, char param_3)
{
    int* cur = (int*)vec[0];
    if (cur != (int*)vec[1]) {
        int* el = cur + 2;
        do {
            int handle = el[-1];
            char* blk = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x38))->Get(handle);
            if (I(blk, 8) != -1) {
                if (FUN_00e5f810(blk + 4) == 0) {
                    blk = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x38))->Get(handle);
                    void* sub = P(blk, 0x300);
                    if (sub != 0) {
                        ((void(__thiscall*)(void*, int))(*(void***)sub)[3])(sub, 1);
                        sub = P(blk, 0x300);
                        if (sub != 0) {
                            P(blk, 0x300) = 0;
                            ((void(__thiscall*)(void*))(*(void***)sub)[1])(sub);
                        }
                    }
                    ((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x38))->Free(handle);
                    int* gend = *(int**)(gspCellGame_s00e7_ce10 + 0x412c);
                    int* src = el;
                    int* dst = el - 2;
                    while (src != gend) {
                        dst[0] = src[0];
                        dst[1] = src[1];
                        src += 2;
                        dst += 2;
                    }
                    I(gspCellGame_s00e7_ce10, 0x412c) = I(gspCellGame_s00e7_ce10, 0x412c) - 8;
                } else {
                    cur += 2;
                    el += 2;
                }
            }
        } while (cur != (int*)vec[1]);
    }

    float recbuf[2560];
    int n = FUN_00e5fa80((void*)(long)param_1, recbuf);
    int hit = 0;
    int idx = 0;
    if (n > 0) {
        char* rd = (char*)recbuf;
        do {
            u32 k = (((u32)*(u32*)(rd) << 8) | (u8)rd[4]);
            k = (k << 8) | (u8)rd[8];
            k = (k << 8) | (u8)rd[0xc];
            int* pb = (int*)vec[0];
            int* pe = (int*)vec[1];
            int cnt = ((char*)pe - (char*)pb) >> 3;
            while (cnt > 0) {
                int half = cnt >> 1;
                if (pb[half * 2] < (int)k) {
                    pb += half * 2 + 2;
                    cnt += -1 - half;
                } else {
                    cnt = half;
                }
            }
            if (pb == pe || (int)k < pb[0]) {
                // not present: register the block and insert its key
                u8 flag = (param_3 == 0 || *(u32*)rd == 0) ? 0 : 1;
                rd[0x10] = (char)flag;
                int h = ((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x38))->Alloc();
                char* nb = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x38))->Get(h);
                I(nb, 4)    = *(int*)(rd + 0x00);
                I(nb, 8)    = *(int*)(rd + 0x04);
                I(nb, 0xc)  = *(int*)(rd + 0x08);
                I(nb, 0x10) = *(int*)(rd + 0x0c);
                I(nb, 0x14) = *(int*)(rd + 0x10);
                FUN_00e7c6c0(nb, (void*)(char)param_3);
                int stored = I(nb, 0);
                int keyv = (int)k;
                int* pos = (int*)FUN_00b41ea0((void*)vec[0], (void*)pe, &keyv, (char)vec[0x406]);
                if (pos == pe || (int)k < pos[0]) {
                    int* r;
                    if (pos == pe)
                        r = (int*)FUN_00b41ea0((void*)vec[0], (void*)pe, &keyv, (char)vec[0x406]);
                    else
                        r = (int*)FUN_00b41ea0((void*)vec[0], (void*)pos, &keyv, (char)vec[0x406]);
                    if (r == pe || (int)k < r[0]) {
                        int* base = (int*)vec[0];
                        if (r == pe && pe != (int*)vec[2]) {
                            vec[1] = (int)(pe + 2);
                            pe[0] = keyv;
                            pe[1] = 0;
                        } else {
                            FUN_00e63d60(vec, r, &keyv);
                        }
                        pos = (int*)((char*)vec[0] + (((char*)r - (char*)base) >> 3) * 8);
                    }
                }
                pos[1] = stored;
                ++hit;
                if (hit > 0x32 && param_3 == 0)
                    return;
            }
            ++idx;
            rd += 0x14;
        } while (idx < n);
    }
}

// @ 0x00e7d720
void FUN_00e7d720(u8 param_1)
{
    if (param_1 == 0)
        FUN_00e7ce10(0x32, 1);
    char* ui = gspCellUI_s00e7_ce10;
    void* w = ((cSPUILayout_s00e7_ce10*)P(ui, 0x90))->FindWindowByID(0x5af4ae3, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, 0);
}

// @ 0x00e7d760
void FUN_00e7d760(void* self, int a, int b, float f)
{
    if (I(self, 0) == I(gspCellGame_s00e7_ce10, 0x411c)) {
        FUN_00e7d070(a, b, f);
        return;
    }
    char ref[4];
    FUN_00743b50(ref);
    void* ent = (void*)FUN_00e4cc40(I(self, 0x108), ref);
    int* e = (int*)FUN_00e52910_s00e7_ce10((int)ent);
    switch (*e) {
    case 0x1006:
        FUN_00e79320(self, b, f);
        break;
    }
    FUN_00e82130(ref);
}

// @ 0x00e7d800
void FUN_00e7d800(int hCell, int a2, int a3, char a4, float dt)
{
    char* c = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c))->GetSafe(hCell);
    if (c == 0 || a4 == 0)
        return;
    FUN_00e7d760(c, a3, a2, dt);
    char* p = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c))->Get(hCell);
    int e = FUN_00e4cce0(0x17);
    if (I(p, 0x108) == e) {
        e = FUN_00e4cce0(0x16);
        if (a3 == e)
            FUN_00e72430((int*)c);
    }
}

// @ 0x00e7d880
void FUN_00e7d880(int* a1, int* a2, int a3)
{
    char* ui = gspCellUI_s00e7_ce10;
    if (*a2 == I(gspCellGame_s00e7_ce10, 0x411c)) {
        char* lvl = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
        if (B(lvl, 0xe8) != 0) {
            I(gspCellGame_s00e7_ce10, 0x411c) = *a1;
            lvl = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
            int old = I(lvl, 0x1c);
            I(lvl, 0x1c) = I(lvl, 0x1c) + 0x96;
            float f_new = FUN_00e4eea0(0, I(lvl, 0x1c));
            float f_old = FUN_00e4eea0(0, old);
            if (f_old != f_new) {
                F(gspCellGame_s00e7_ce10, 0x5150) = f_new;
                FUN_00e7cd10();
            }
            FUN_00e780a0(*a2, 1, 0.0f, 0);
            lvl = *(char**)(gspCellGame_s00e7_ce10 + 0x5190);
            I(lvl, 0x10) = a1[0x3f];
            I(lvl, 0x14) = a1[0x40];
            I(lvl, 0x18) = a1[0x41];
            return;
        }
        I(ui, 0xe0) = *a1;
        I(ui, 0x54) = I(ui, 0x48);
        I(ui, 0x58) = I(ui, 0x4c);
        I(ui, 0x5c) = I(ui, 0x50);
        I(ui, 0x60) = I(ui, 0x48);
        I(ui, 0x64) = I(ui, 0x4c);
        I(ui, 0x68) = I(ui, 0x50);
    }
    B(a2, 0x114) = 1;
    if (*a1 == I(gspCellGame_s00e7_ce10, 0x411c) && B(a2, 0x112) == 0) {
        FUN_00e514c0();
        char ref[4];
        FUN_00743b50(ref);
        void* ent = (void*)FUN_00e4cc40(I(a2, 0x108), ref);
        if (FUN_00e509d0(a3, ent) == 0)
            I(*(char**)(gspCellGame_s00e7_ce10 + 0x5190), 0x6c) += 1;
        FUN_00e82130(ref);
    }
    if (*a2 == I(gspCellGame_s00e7_ce10, 0x411c))
        FUN_00e5c8e0_s00e7_ce10((void*)*a1);
    if (a2[0x3f] == 0) {
        FUN_00e780a0(*a2, 1, 0.0f, 0);
        return;
    }
    u32 id = FNV1_String8("cell_death_eaten", 0x811c9dc5, 1);
    FUN_00e66840((int)a2, id);
    char* rec = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c))->Get(*a2);
    float f = FUN_00e6d200(rec, 0, 9, I(rec, 0x1b0));
    int self = *a2;
    int h = ((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x54))->Alloc();
    char* m = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x54))->Get(h);
    F(m, 0x1c) = f;
    F(m, 0x20) = f;
    I(m, 0x24) = 7;
    I(m, 0x28) = self;
    I(m, 0x2c) = 0;
    I(m, 0x30) = -1;
    I(m, 0x34) = -1;
    I(m, 0x38) = 0;
    I(m, 0x3c) = 0;
    F(m, 0x40) = 0.0f;
    F(m, 0x44) = 0.0f;
    I(m, 0x48) = I(&gCellWorldCenter_s00e7_ce10, 0);
    I(m, 0x4c) = I(&gCellWorldCenter_s00e7_ce10, 4);
    I(m, 0x50) = I(&gCellWorldCenter_s00e7_ce10, 8);
    I(m, 0x54) = I(&gCellWorldCenter_s00e7_ce10, 0);
    I(m, 0x58) = I(&gCellWorldCenter_s00e7_ce10, 4);
    I(m, 0x5c) = I(&gCellWorldCenter_s00e7_ce10, 8);
    I(m, 0x60) = I(g_15a7c4c, 0);
    I(m, 0x64) = I(g_15a7c4c, 4);
    I(m, 0x68) = I(g_15a7c4c, 8);
    I(m, 0x6c) = I(g_15a7c4c, 0xc);
    I(m, 0x70) = 0;
    B(m, 0x74) = 0;
    I(m, 0x78) = 0;
    I(m, 4) = 0;
    B(m, 8) = 0;
    if (I(gspCellGame_s00e7_ce10, 0x411c) == *a2) {
        FUN_00b3d4d0_s00e7_ce10()->setModal(1);
        B(gspCellUI_s00e7_ce10, 0x936) = 1;
        I(gspCellGame_s00e7_ce10, 0x5194) = h;
    }
    FUN_00e59500(*a2);
}

// @ 0x00e7db80
char FUN_00e7db80(int rec)
{
    Pool_s00e7_ce10* p1 = (Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c);
    char* a = (char*)p1->GetSafe(I(rec, 0x28));
    int h2 = I(rec, 0x2c);
    Pool_s00e7_ce10* p2 = (Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c);
    char* b = (char*)p2->GetSafe(h2);
    if (a == 0)
        return 0;
    if (b == 0)
        return 0;
    FUN_00e7d880((int*)a, (int*)b, I(rec, 0x38));
    return 1;
}

// @ 0x00e7dbd0
void FUN_00e7dbd0(int a1, int a2, int a3, int a4, float dt)
{
    char* p = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c))->GetSafe(a1);
    if (p == 0)
        return;
    FUN_00e7d760(p, a4, 4, dt);
    if (P(p, 0x168) != 0) {
        FUN_00e59200(P(p, 0x168));
        P(p, 0x168) = 0;
    }
    char* q = (char*)((Pool_s00e7_ce10*)(gspCellGame_s00e7_ce10 + 0x1c))->GetSafe(a2);
    if (q == 0)
        return;
    if (P(q, 0x168) != 0) {
        FUN_00e59200(P(q, 0x168));
        P(p, 0x168) = 0;
    }
    if ((I(gspCellGame_s00e7_ce10, 0x411c) == a1 || I(gspCellGame_s00e7_ce10, 0x411c) == a2) && I(q, 0x248) != 0) {
        float f = (float)I(q, 0x244) * g_1440f84;
        void* r = FUN_00e62200(I(q, 0), f);
        if (r != 0)
            F(r, 0x24) = g_half_1471064;
    }
    int* pi = (int*)(q + 0x244);
    int d = FUN_00e58980(p, q);
    *pi -= d;
    int zero = 0;
    if (*pi > 0) zero = *pi;
    *pi = zero;
    FUN_00e576f0(a1);
    FUN_00e7a770(a2, I(p, 0), I(p, 0x108), I(gspCellGame_s00e7_ce10, 0x411c) == a1, 6, dt);
    float v[3];
    FUN_00e67d30(v, (int)p, a3);
    v[0] = v[0] * g_1470f1c;
    v[1] = v[1] * g_1470f1c;
    v[2] = v[2] * g_1470f1c;
    FUN_00e72530(q, a3, v);
}

// @ 0x00e7dd90
void FUN_00e7dd90(int a1, int a2, int a3, int a4, float a5)
{
    void* p = registry()->Get(a1);
    if (p != 0) {
        FUN_00e7d760(a4, a5);
        if (I(p, 0x168) != 0) {
            FUN_00e59200(P(p, 0x168));
            I(p, 0x168) = 0;
        }
        void* q = registry()->Get(a2);
        if (q != 0) {
            if ((I(gspCellGame_s00e7_dd90, 0x411c) == a1) || (I(gspCellGame_s00e7_dd90, 0x411c) == a2)) {
                float f = (float)I(q, 0x244) * 0.16666667f;
                if (I(q, 0x248) != 0) {
                    void* r = FUN_00e62200(I(q, 0), f);
                    if (r != 0)
                        I(r, 0x24) = 0x3f000000;
                }
            }
            int* pi = (int*)((char*)q + 0x244);
            int r = FUN_00e58980(p, q);
            *pi -= r;
            int zero = 0;
            int* sel = pi;
            if (*pi < 1)
                sel = &zero;
            *pi = *sel;

            FUN_00e576f0(a1);
            FUN_00e7a770(a2, I(p, 0), I(p, 0x108), I(gspCellGame_s00e7_dd90, 0x411c) == a1, 6, a5);

            uint32 v[3];
            FUN_00e67d30(v, p, a3);
            FUN_00e72530(q, a3, v);
            v[0] ^= 0x80000000u;
            v[1] ^= 0x80000000u;
            v[2] ^= 0x80000000u;
            FUN_00e72530(p, -1, v);
        }
    }
}

// @ 0x00e7df40
void FUN_00e7df40(int a1, int a2, int a3, float a4)
{
    void* p = registry()->Get(a1);
    if (p != 0) {
        FUN_00e7d760(a3, a4);
        if (I(p, 0x168) != 0) {
            FUN_00e59200(P(p, 0x168));
            I(p, 0x168) = 0;
        }
    }
    void* q = registry()->Get(a2);
    if (q != 0) {
        int e = I(q, 0x358);
        int d = e - 1;
        if (FUN_00e56f20(d) == 0) {
            FUN_00e780a0(I(q, 0), 1, 0.0f, 0);
            return;
        }
        F(q, 0xb4) = (kLevelSize[d] / kLevelSize[e]) * F(q, 0xb4);
        I(q, 0x358) = d;
        if (0.0f < F(q, 0x1f0))
            F(q, 0x1f0) = 0.0f;
    }
}

// @ 0x00e7e020
int FUN_00e7e020(void* self, void* p, int a2, int a3)
{
    if (B_s00e7_dd90(self, 0x179) == 0) {
        if (B_s00e7_dd90(self, 0x111) == 1 || B_s00e7_dd90(self, 0x17b) != 0 || B_s00e7_dd90(p, 0x178) != 0 ||
            FUN_00e57460(p, self))
            return 0;
        int u = (a3 == 2) ? 0xc : 0xb;
        void* r = registry()->Find(I(p, 0));
        float f = FUN_00e6d200(r, 0, u, I(r, 0x1b0));
        FUN_00e51ee0(1, f, I(p, 0), I(self, 0), a2, -1, a3, I(self, 0x108),
                     0, 0, 0, 0, 0, 0, 0, 0);
        FUN_00e528d0(FUN_00e7db80);
        FUN_00e528f0(0, 0.33333334f * f);
        FUN_00e69a90(I(self, 0), a3, 0.33333334f * f, 0);
    }
    return 1;
}

// @ 0x00e7e130
void sDoEnd(void* self, float dt, int a2, int a3)
{
    if (B_s00e7_dd90(self, 8) == 0 && P(self, 4) != 0 && (int8_t)a3 == 0) {
        ((void (*)(void*, float))P(self, 4))(self, dt);
        B_s00e7_dd90(self, 8) = 1;
    }

    switch (I(self, 0x24)) {
    case 1:
        FUN_00e7d800(I(self, 0x28), I(self, 0x38), I(self, 0x3c), B_s00e7_dd90(self, 8), dt);
        manager()->Remove(I(self, 0));
        return;
    case 2:
        FUN_00e7a770(I(self, 0x28), I(self, 0x2c), I(self, 0x3c), B_s00e7_dd90(self, 0x74),
                     I(self, 0x38), dt);
        manager()->Remove(I(self, 0));
        return;
    case 5: {
        int u = I(self, 0x28);
        manager()->Remove(I(self, 0));
        FUN_00e7add0(u, a2, dt);
        return;
    }
    case 6:
        FUN_00e59150(I(self, 0x28), dt);
        manager()->Remove(I(self, 0));
        return;
    case 7: {
        int u1 = I(self, 0x28);
        int u2 = I(self, 0x3c);
        manager()->Remove(I(self, 0));
        FUN_00e7b410(u1, a2, u2);
        return;
    }
    case 0xf:
        registry()->Get(I(self, 0x28));
        manager()->Remove(I(self, 0));
        return;
    case 0x10: {
        void* h = P(self, 0x70);
        if (h != 0) {
            int inner = I(h, 0x10);
            if (inner != 0 && inner != I(h, 0x20))
                operator_delete__((void*)inner);
            operator_delete__(h);
            manager()->Remove(I(self, 0));
            return;
        }
        break;
    }
    case 0x12:
        FUN_00e7df40(I(self, 0x28), I(self, 0x2c), I(self, 0x3c), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x13:
        FUN_00e7dd90(I(self, 0x28), I(self, 0x2c), I(self, 0x30), I(self, 0x3c), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x14:
        FUN_00e7dbd0(I(self, 0x28), I(self, 0x2c), I(self, 0x30), I(self, 0x3c), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x1a:
        FUN_00e7a160(I(self, 0x28));
        manager()->Remove(I(self, 0));
        return;
    case 0x1b:
        FUN_00e7cbb0(a2, a3);
        manager()->Remove(I(self, 0));
        return;
    case 0x1c:
        FUN_00e50400(a2);
        manager()->Remove(I(self, 0));
        return;
    case 0x1d:
        manager()->Remove(I(self, 0));
        FUN_00e50940(dt, a2);
        return;
    case 0x1e:
        FUN_00e72ac0();
        manager()->Remove(I(self, 0));
        return;
    case 0x1f:
        FUN_00e62440();
        manager()->Remove(I(self, 0));
        return;
    case 0x21:
        sDigestion_End(I(self, 0x28), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x22:
        FUN_00e5ed20(I(self, 0x28), (char*)self + 0x60);
        manager()->Remove(I(self, 0));
        return;
    case 0x24:
        FUN_00e794f0(I(self, 0x28), I(self, 0x2c), dt, a2);
        manager()->Remove(I(self, 0));
        return;
    case 0x25:
        FUN_00e7cb90();
        manager()->Remove(I(self, 0));
        return;
    case 0x28:
        FUN_00e59ab0(I(self, 0x28));
        manager()->Remove(I(self, 0));
        return;
    case 0x29:
        FUN_00e7b9b0(I(self, 0x28), I(self, 0x2c), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x2a:
        FUN_00e7b240(I(self, 0x28), dt);
        manager()->Remove(I(self, 0));
        return;
    case 0x2b:
        FUN_00e7d720(B_s00e7_dd90(self, 0x74));
        manager()->Remove(I(self, 0));
        return;
    case 0x2c:
        FUN_00e567c0();
        manager()->Remove(I(self, 0));
        return;
    case 0x2d:
        FUN_00e78de0();
        manager()->Remove(I(self, 0));
        return;
    case 0x2f:
        FUN_00e53c20();
        manager()->Remove(I(self, 0));
        return;
    case 0x30:
        FUN_00e5daf0();
        manager()->Remove(I(self, 0));
        return;
    case 0x31:
        FUN_00e56950();
        manager()->Remove(I(self, 0));
        return;
    case 0x32:
        FUN_00e57d10(I(self, 0x28), I(self, 0x40), I(self, 0x44));
        manager()->Remove(I(self, 0));
        return;
    default:
        break;
    }
    manager()->Remove(I(self, 0));
}

// @ 0x00e7e6c0
void sUpdateInteraction(void* self, float dt)
{
    F(self, 0x1c) = F(self, 0x1c) - dt;
    if (FUN_00e59c10(self, dt) == 0) {
        sDoEnd(self, dt, 0, 0);
        return;
    }
    for (int i = 0; i < 4; i++) {
        float* pf = (float*)((char*)self + 0xc) + i;
        if (0.0f < *pf) {
            float f = *pf - dt;
            *pf = f;
            if (f < 0.0f) {
                *pf = 0.0f;
                if (FUN_00e7b540(self, i, dt) == 0)
                    goto end;
            }
        }
    }
    if (0.0f < F(self, 0x1c) || I(gspCellGame_s00e7_dd90, 0x5198) == I(self, 0)) {
        if (FUN_00e7ba30(self, dt) != 0)
            return;
    } else {
        F(self, 0x1c) = 0.0f;
    }
end:
    sDoEnd(self, dt, 0, 0);
}

// @ 0x00e7e7a0
void FUN_00e7e7a0(float dt)
{
    int local = manager()->GetPriority();
    void* it = manager()->Next(&local);
    while (it != 0) {
        sUpdateInteraction(it, dt);
        it = manager()->Next(&local);
    }
}

// @ 0x00e7fc00
void FUN_00e7fc00(void)
{
    FUN_00e53580();

    g_1550adc = g_16b3bf0;
    g_1550af0 = g_16b3bec;
    g_1550a84 = g_16b3bf8;
    g_1550aec = g_16b3be8;
    g_1550ae0 = g_16b3be4;
    g_166c004 = g_16b3bfc;
    g_1550ad8 = g_16b3bf4;
    g_1550ae4 = g_16b3be0;

    int h = manager_s00e7_f630()->GetPriority();
    for (void* o = manager_s00e7_f630()->Next(&h); o != 0; o = manager_s00e7_f630()->Next(&h))
        sDoEnd(o, 0.0f, 0, 1);

    manager_s00e7_f630()->Reset();

    void** em = (void**)EffectsManager_s00e7_f630();
    ((Vfn2i)VTBL(em)[0x98 / 4])(em, 7, 0);

    FUN_00e64a00();
    FUN_00e82d40();
}

// @ 0x00e818f0
char __stdcall FUN_00e818f0(int msg, uint32_s00e8_0ba0 flags)
{
    if (FUN_00e82900(msg, flags) == 0) {
        if (flags == 2 && msg == 0x48)
            B_s00e8_0ba0(gspCellGameMode, 0x937) = (B_s00e8_0ba0(gspCellGameMode, 0x937) == 0);

        // thiscall member: the mode object travels in ECX
        ((struct LocaleMode*)gspCellGameMode)->RouteMessage(msg, flags);

        char both;
        if ((flags & 2) == 0 || (both = 1, (flags & 4) == 0))
            both = 0;

        char c = FUN_00e82cc0();
        if (c != 0 && msg != 0x42)
            return 0;

        if (both) {
            c = FUN_00e81120(msg, (uint8_s00e8_0ba0)flags);
            if (c != 1 && (c = FUN_00e7f630(msg, flags)) != 1)
                return 0;
        } else {
            c = FUN_00e7f630(msg, flags);
            if (c != 1) {
                c = FUN_00e81120(msg, (uint8_s00e8_0ba0)flags);
                if (c != 1)
                    return 0;
                return 1;
            }
        }
    }
    return 1;
}

// @ 0x00e82130
void __fastcall FUN_00e82130(int* it)
{
    if (*it != 0)
        (*(int*)(*it + 0xc))--;
}

// @ 0x0137ed40
void FUN_0137ed40(void)
{
    Vec3_s0137_d820 mn; mn.x = gFMax; mn.y = gFMax; mn.z = gFMax;
    gCellGameExtents.min = mn;
    Vec3_s0137_d820 mx; mx.x = gFMin; mx.y = gFMin; mx.z = gFMin;
    gCellGameExtents.max = mx;
}

// @ 0x0137edc0
void FUN_0137edc0(void)
{
    Vec3_s0137_d820 mn; mn.x = gFMax; mn.y = gFMax; mn.z = gFMax;
    gCellGameBackgroundExtents.min = mn;
    Vec3_s0137_d820 mx; mx.x = gFMin; mx.y = gFMin; mx.z = gFMin;
    gCellGameBackgroundExtents.max = mx;
}
