// src/game/SPEditors/_at_00f00000.cpp -- migrated from slice(s) s00f031a0, s00f02160, s00f015b0, s00f00610 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00f00000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void*   g_mgr;             // 0x016c7b88 (singleton pointer variable)
extern void*   gSimulator;        // 0x016c7aa4 (simulator pointer variable)
extern uint8_t g_015acb40;        // 0x015acb40  tutorial scenario enabled flag
extern float   g_015ad360;        // 0x015ad360  approach-rate constant
extern float   g_16c7d74;         // 0x016c7d74  audio cue toggle float
extern float   g_0148cfe8;        // 0x0148cfe8  +3.0f constant
extern uint8_t g_016c7b98[];      // 0x016c7b98  sphere description for ray_sphere
extern "C" void* __cdecl FUN_00b18e00(void*);          // 0x00b18e00
extern "C" void* __cdecl FUN_00eebf80(void*);          // 0x00eebf80 GetRefCounted18
extern "C" void  __cdecl f_eff4c0_impl(void*, float);  // 0x00eff4c0 (thiscall in real code)
extern "C" void  __cdecl FUN_00eec3d0(void*, void*);   // 0x00eec3d0
extern "C" void* __cdecl FUN_00eec0d0(void*);          // 0x00eec0d0
extern "C" float __cdecl FUN_00f409a0(void*, void*, float, int, void*); // 0x00f409a0 ScenarioNode_ClampValue
extern "C" int   __cdecl FUN_00eece20(void*);          // 0x00eece20 ResourceKeyToIcon
extern "C" void* __cdecl FUN_0067dcc0();               // 0x0067dcc0 MessageServer
extern "C" void  __cdecl FUN_00efd970(void*);          // 0x00efd970
extern "C" void* __cdecl FUN_00b3d250();               // 0x00b3d250 SP::GameInputManager
extern "C" void  __cdecl FUN_00efe260();               // 0x00efe260 ScenarioTutorials_SetSelectedObject
extern "C" void  __cdecl FUN_00eef7d0(void*);          // 0x00eef7d0
extern "C" void* __cdecl FUN_00b3d240();               // 0x00b3d240
extern "C" void* __cdecl FUN_00ae66d0(void*);          // 0x00ae66d0
extern "C" void  __cdecl FUN_00eef4b0(void*);          // 0x00eef4b0
extern "C" void* __cdecl FUN_00a206f0();              // 0x00a206f0 EA::Audio::GetSystemAT
extern "C" void* __cdecl FUN_0067dd10();               // 0x0067dd10 SP::App
extern "C" void  __cdecl FUN_007c4900(void*, void*);   // 0x007c4900
extern "C" void  __cdecl FUN_00efd8e0();               // 0x00efd8e0 ObjPlaneVec (pointer arrives in esi)
extern "C" char  __cdecl FUN_00ebaa20(void*, void*, void*, float, void*); // 0x00ebaa20 ray_sphere
extern "C" void  __cdecl FUN_00698180(void*, void*, void*); // 0x00698180 QuaternionFromDirections
extern "C" void  __cdecl FUN_00eed720(void*, void*, void*); // 0x00eed720
extern "C" float __cdecl FUN_00eec370(void*, uint32_t, void*); // 0x00eec370
extern "C" void  __cdecl FUN_00eec8e0(void*, void*, void*); // 0x00eec8e0 ResourceFlagPair
extern "C" void* __cdecl FUN_00b3d350(void*, void*);   // 0x00b3d350 SP::PlanetModel
extern "C" void* __cdecl FUN_00b82df0(void*, void*, uint32_t, int, int, int); // 0x00b82df0 ProjectToSurface
extern "C" void  __cdecl FUN_00eee760(void*, void*);   // 0x00eee760
#include <math.h>
#include "EA/IO/FileStream.h"
#include "EA/LimitStopwatch.h"
#include "SP/cGameNounManager.h"

// ---- items of slice s00f00610 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*   g_mgr;             // 0x016c7b88 (singleton pointer variable)
extern void*   gSimulator;        // 0x016c7aa4 (simulator pointer variable)
extern uint8_t g_015acb40;        // 0x015acb40  tutorial scenario enabled flag
extern float   g_015ad360;        // 0x015ad360  approach-rate constant
extern float   g_16c7d74;         // 0x016c7d74  audio cue toggle float
extern float   g_0148cfe8;        // 0x0148cfe8  +3.0f constant
extern uint8_t g_016c7b98[];      // 0x016c7b98  sphere description for ray_sphere
extern "C" void* __cdecl FUN_00b18e00(void*);          // 0x00b18e00
extern "C" void* __cdecl FUN_00eebf80(void*);          // 0x00eebf80 GetRefCounted18
extern "C" void  __cdecl f_eff4c0_impl(void*, float);  // 0x00eff4c0 (thiscall in real code)
extern "C" void  __cdecl FUN_00eec3d0(void*, void*);   // 0x00eec3d0
extern "C" void* __cdecl FUN_00eec0d0(void*);          // 0x00eec0d0
extern "C" float __cdecl FUN_00f409a0(void*, void*, float, int, void*); // 0x00f409a0 ScenarioNode_ClampValue
extern "C" int   __cdecl FUN_00eece20(void*);          // 0x00eece20 ResourceKeyToIcon
extern "C" void* __cdecl FUN_0067dcc0();               // 0x0067dcc0 MessageServer
extern "C" void  __cdecl FUN_00efd970(void*);          // 0x00efd970
extern "C" void* __cdecl FUN_00b3d250();               // 0x00b3d250 SP::GameInputManager
extern "C" void  __cdecl FUN_00efe260();               // 0x00efe260 ScenarioTutorials_SetSelectedObject
extern "C" void  __cdecl FUN_00eef7d0(void*);          // 0x00eef7d0
extern "C" void* __cdecl FUN_00b3d240();               // 0x00b3d240
extern "C" void* __cdecl FUN_00ae66d0(void*);          // 0x00ae66d0
extern "C" void  __cdecl FUN_00eef4b0(void*);          // 0x00eef4b0
struct Container {                                     // object at g_mgr+0x30
    void F_00c688a0(void*, char*);   // 0x00c688a0 (element, &flag)
    void F_00c68d20(void*);          // 0x00c68d20
};
struct B34Obj { void F_eeff40(); };                    // 0x00eeff40
extern B34Obj   g_016c7b34obj;    // 0x016c7b34
struct STut { char CheckObject(void*); };              // 0x00efeae0 on 0x015ad328
extern STut     g_015ad328obj;    // 0x015ad328
struct Obj74 { void F3BBD0(int, int); void F3DA90(void*, int); }; // 0x00f3bbd0 / 0x00f3da90 on gSimulator+0x74
struct AutoRef { void F_00b5f950(void*); };             // 0x00b5f950 refcounted slot assign
struct Simulator {
    char  pad0[0x74];
    Obj74* p74;                    // +0x74  window/hint owner
    char  pad78[0x5c];             // +0x78 .. +0xd3
    void* pD4;                     // +0xd4  checklist UI
};
struct Mgr {
    int      mIndex;               // +0x00  index of the current placement record
    void*    mp4;                  // +0x04  refcounted current object
    void*    mp8;                  // +0x08  refcounted secondary slot
    void*    mpSelected;           // +0x0c  refcounted selected object
    void*    mp10;                 // +0x10  refcounted active object
    char     pad14[0xc];           // +0x14
    void*    mp20;                 // +0x20  raw compare object
    char     pad24[4];             // +0x24
    void*    mp28;                 // +0x28  compare object
    char     pad2c[4];             // +0x2c
    char     mVec30[0x2c];         // +0x30  association container
    void*    mp5c;                 // +0x5c
    void*    mp60;                 // +0x60
    uint8_t  b64;                  // +0x64
    char     pad65[3];             // +0x65
    int      f68;                  // +0x68
    char     pad6c[0xc];           // +0x6c
    float    f78;                  // +0x78
    char     pad7c[0x10];          // +0x7c
    void*    begin8c;              // +0x8c  list begin (used as a pair +0x8c/+0x90)
    void*    end90;                // +0x90  list end
};
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Node {
    void*    vtable;               // +0x00
    Vec3     pos;                  // +0x04
    Quat     rot;                  // +0x10
    float    f20;                  // +0x20
    uint32_t f24;                  // +0x24
    char*    p28;                  // +0x28  record array begin
    char*    p2c;                  // +0x2c  record array end
    char     pad30[0x1f0];         // +0x30 .. +0x21f
    float    f220;                 // +0x220
};
struct SNode {                     // object returned by GObj::F3E8A0
    char     pad0[0x20];
    uint8_t  b20;                  // +0x20
};
struct NodeB {                     // object returned by FUN_00b18e00(0)
    char     pad0[0x6e];
    uint8_t  b6e;                  // +0x6e
};
struct PObj {                      // object returned by GObj::F32790
    char     pad0[4];
    uint32_t f4;                   // +0x04
};
struct Key { uint32_t a; uint32_t b; };
struct GObj {
    char pad0[0x1b0];
    void* f1b0;                // +0x1b0  associated object pointer
    char pad1b4[0x24c];
    void* F32790(void*);       // 0x00f32790 ret 4
    void  F33BF0();            // 0x00f33bf0
    void  F38150(void*);       // 0x00f38150 ret 4
    void  F34560();            // 0x00f34560
    void  F36450(int, int, void*); // 0x00f36450 ret 0xc
    void* F336A0(void*);       // 0x00f336a0 ret 4
    void  F38330(int);         // 0x00f38330 ret 4
    void  F45970();            // 0x00f45970
    void  F45A80();            // 0x00f45a80
    void  F3DA90(void*, int);  // 0x00f3da90 ret 8
    char  F3EC90(void*);       // 0x00f3ec90 ret 4
    char  F326D0(void*);       // 0x00f326d0 ret 4
    void* F3E8A0(void*);       // 0x00f3e8a0 ret 4
    void* F445C0(void*);       // 0x00f445c0 ret 4
    void  F3BBD0(int, int);    // 0x00f3bbd0 ret 8
};
struct VObj {
    void  v0();                // vtable slot 0 (addref)
    void  v4();                // vtable slot 1 (release)
    float v34();               // vtable slot 0x34, returns float
    void  v38(void*);
    void  v3c(void*);
    void  v40(float);
};
struct Ref {
    virtual void v0();     // slot 0 addref
    virtual void v4();     // slot 1 release
};
struct V4 {
    void* p0;    // refcounted object
    int   f4;
    int   f8;
    float fC;
    V4* assign(V4* src);   // 0x00f00b00
};
struct Mp10Obj {
    float F_efc4c0();          // 0x00efc4c0
    char  CheckObj(void*);     // 0x00efeae0 (same target as STut::CheckObject)
};
struct UI {
    void* vtable;      // +0x00
    uint8_t f4;        // +0x04
    uint8_t b5;        // +0x05
    uint8_t b6;        // +0x06
    uint8_t b7;        // +0x07
    GObj* pGame;       // +0x08
    void* pC;          // +0x0c
    void* p10;         // +0x10
    char  F_efc660(void*);         // 0x00efc660 ret 4
    char  F_efc7d0(void*, void*);  // 0x00efc7d0 ret 8
    void  F_efec90(void*);         // 0x00efec90 ret 4
    void  F_efcde0();              // 0x00efcde0
    void  FwdC6E0(void*);          // 0x00efc6e0 ret 4
    void  SetObject(void*);        // 0x00eff230 ret 4
    void  UpdateVisibility();      // 0x00eff0c0
    void  Adjust(void*, float);    // 0x00eff4c0 ret 8
    void* Place(void*);            // 0x00efeee0 ret 4
    void* GetPlacement();          // 0x00eff590
    void  ToggleHint(int, int);    // 0x00efbbe0 ret 8
    char  CheckObject(void*);      // 0x00efeae0 ret 4
    void  f00b50();                // 0x00f00b50
    void  f00ba0();                // 0x00f00ba0
    void  f01030(void*, float);    // 0x00f01030 ret 8
    void  SyncPlacement(int, float);   // 0x00f00610 ret 8
    char  ApplyPlacement(void*);       // 0x00f00790 ret 4
    char  ApplyPlacementEx(void*);     // 0x00f00850 ret 4
    void  CommitPlacement(void*);      // 0x00f00bd0 ret 4
    void  Teardown();                  // 0x00f00d10
    char  UpdatePlacement(void*);      // 0x00f00e50 ret 4
    void  Dispatch();                  // 0x00f00f80
    char  AddObject(void*);            // 0x00f01090 ret 4
};
struct GD { void* F_B18530(); char dummy; };   // 0x00b18530 object accessor
struct CGameData { char F_F253E0(); };         // 0x00f253e0
struct Rec { int f0; float f1, f2, f3, f4, f5, f6, f7; };
typedef void  (__thiscall *ThV0)(void*);
typedef void  (__thiscall *ThV1)(void*, int);
typedef void  (__thiscall *ThV2)(void*, int, int);
typedef void  (__thiscall *ThV3)(void*, int, int, int);
typedef void  (__thiscall *ThV2F)(void*, int, float);
typedef void* (__thiscall *ThP0)(void*);
typedef void* (__thiscall *ThP1)(void*, void*);
typedef void  (__thiscall *ThV2P)(void*, void*, void*);
typedef int   (__thiscall *ThI0)(void*);
typedef int   (__thiscall *ThI1)(void*, int);
typedef int*  (__thiscall *ThIP0)(void*);
static inline void* vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
static inline void  do_release(void* o) { ((ThV0)vslot(o, 4))(o); }
static __forceinline float s_exp(float x)
{
    double y = (double)x * 1.4426950408889634;
    double dn = (double)(long long)(y >= 0.0 ? y + 0.5 : y - 0.5);
    double r = y - dn;
    double p = 1.0 + r * (0.6931471805599453094
               + r * (0.2402265069591007123
               + r * (0.05550410866482157995
               + r * (0.009618129107628477161
               + r * (0.001333355814642844342
               + r * 0.0001540353039338161012)))));
    union { unsigned long long u; double d; } sc;
    sc.u = ((unsigned long long)((long long)dn + 1023)) << 52;
    return (float)(p * sc.d);
}
extern "C" void* __cdecl FUN_00a206f0();              // 0x00a206f0 EA::Audio::GetSystemAT
extern "C" void* __cdecl FUN_0067dd10();               // 0x0067dd10 SP::App
extern "C" void  __cdecl FUN_007c4900(void*, void*);   // 0x007c4900
extern "C" void  __cdecl FUN_00efd8e0();               // 0x00efd8e0 ObjPlaneVec (pointer arrives in esi)
extern "C" char  __cdecl FUN_00ebaa20(void*, void*, void*, float, void*); // 0x00ebaa20 ray_sphere
extern "C" void  __cdecl FUN_00698180(void*, void*, void*); // 0x00698180 QuaternionFromDirections
extern "C" void  __cdecl FUN_00eed720(void*, void*, void*); // 0x00eed720
extern "C" float __cdecl FUN_00eec370(void*, uint32_t, void*); // 0x00eec370
extern "C" void  __cdecl FUN_00eec8e0(void*, void*, void*); // 0x00eec8e0 ResourceFlagPair
extern "C" void* __cdecl FUN_00b3d350(void*, void*);   // 0x00b3d350 SP::PlanetModel
extern "C" void* __cdecl FUN_00b82df0(void*, void*, uint32_t, int, int, int); // 0x00b82df0 ProjectToSurface
extern "C" void  __cdecl FUN_00eee760(void*, void*);   // 0x00eee760
// ---- items of slice s00f00610 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern B34Obj   g_016c7b34obj;    // 0x016c7b34
extern STut     g_015ad328obj;    // 0x015ad328

// ---- items of slice s00f015b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double sqrt(double);
extern "C" double fabs(double);
extern "C" void __cdecl FUN_00f47380(void* pMemory);      // 0x00f47380 operator delete
extern char g_ChecklistTutorialUI;                         // 0x016c7c08
static inline float fabsf_(float v) { return (float)fabs((double)v); }
struct V3 { float x, y, z; };
#define P4(n) virtual void p##n##a(); virtual void p##n##b(); virtual void p##n##c(); virtual void p##n##d();
struct Viewer {
  void GetCameraRay(V3* origin, V3* dir);               // 0x007c4900 (ret 8)
};
struct cTutorialHost;
struct AppObj {
  P4(0) P4(1) P4(2) P4(3) P4(4)
  virtual cTutorialHost* GetTutorialHost();             // +0x50
  virtual void p5b();
  virtual Viewer* GetViewer();                          // +0x58
};
AppObj* AppGet();                                       // 0x0067dd10 (SP::App)
struct Ent {
  char pad0[4];
  float px, py, pz;       // +0x04
  float qx, qy, qz, qw;   // +0x10
  char pad20[0x220 - 0x20];
  float f220;             // +0x220
};
struct Thing {
  P4(0) P4(1) P4(2) P4(3) P4(4) P4(5) P4(6) P4(7) P4(8) P4(9) P4(10)
virtual void p11a();
virtual void p11b();
  virtual void* QueryInterface(unsigned id);            // +0xb8
};
Thing* __cdecl GetThing(unsigned h);                    // 0x00b18e00
Ent* __cdecl GetEnt(unsigned h);                        // 0x00eebf80
V3* __cdecl ObjPlaneVec(unsigned h, V3* result);        // 0x00efd8e0 (esi = result, edi = h in the original)
struct Query {
  int mode;
  int a;
  int b;
  float c;
  unsigned flags;
};
void __cdecl EntQuery(Ent* e, Thing* t, Query* q);      // 0x00eed720
struct SnapOpt {
  virtual void f();                                     // vtable at 0x0148b6e4
  bool on;
  SnapOpt() : on(true) {}
};
struct Planet {
  V3* Project(V3* sret, V3* from, V3* dir);             // 0x00b82110 (ret 12)
  V3* ProjectOpt(V3* sret, V3* from, V3* dir, SnapOpt* o);  // 0x00b82620 (ret 16)
};
Planet* PlanetModel();                                  // 0x00b3d350
bool __cdecl RayPlanet(V3* from, V3* dir, V3* zero, float maxT, float* t);  // 0x00ebaa20
void __cdecl QuaternionFromDirections(Quat* out, const V3* a, const V3* b); // 0x00698180
Quat* __cdecl QuatMul(Quat* out, const Quat* a, const Quat* b);             // 0x007dcb00
float* __cdecl SurfaceDir(float* out, float* dir, int lead, int* flag, int a5);  // 0x00eec2b0
void __cdecl EntRefresh(Ent* e);                        // 0x00eec440
struct EntMgr {
  void Commit(Ent* e, int arg);                         // 0x00f3da90 (ret 8)
};
void __cdecl EntSnap(Ent* e, void* v);                  // 0x00eee760
struct UICtx {
  int idx;                // +0x00
  char pad4[8];
  unsigned handle;        // +0x0c
  char pad10[0x64 - 0x10];
  bool m64;               // +0x64  drag/placement pending flag
  char pad65[3];
  int m68;                // +0x68  active editor mode (1..3)
  char pad6c[0x78 - 0x6c];
  float maxT;             // +0x78
  V3 m7c;                 // +0x7c
  float m88;              // +0x88
  char snapVec[0x14];     // +0x8c
  char m_a0[0x10];        // +0xa0
};
struct Services {
  char pad[0x74];
  EntMgr* mgr;            // +0x74
};
#define g_UI (*(UICtx**)0x016c7b88)        // 0x016c7b88
#define g_Svc (*(Services**)0x016c7aa4)    // 0x016c7aa4
#define g_Flag (*(char*)0x015acb40)        // 0x015acb40
#define g_Zero (*(V3*)0x016c7b98)          // 0x016c7b98
static __forceinline void Reorient(Ent* e, const V3* oldPos, const V3* newPos) {
  Quat q1;
  q1.x = e->qx; q1.y = e->qy; q1.z = e->qz; q1.w = e->qw;
  Quat dq, prod;
  QuaternionFromDirections(&dq, oldPos, newPos);
  Quat r = *QuatMul(&prod, &dq, &q1);
  float inv = 1.0f / (float)sqrt((double)(r.w * r.w + r.z * r.z + r.y * r.y + r.x * r.x));
  e->qx = r.x * inv;
  e->qy = r.y * inv;
  e->qz = r.z * inv;
  e->qw = r.w * inv;
}
class cRefCounted {
public:
  virtual void v00();
  virtual void Release();                                 // vtable +0x04
};
template <class T>
class AutoRefCount {
public:
  T* mpPtr;                                               // +0x00
  ~AutoRefCount() { if (mpPtr) mpPtr->Release(); }
};
struct StarVector {                                       // eastl::vector<AutoRefCount<cStarRecord>>
  void* mpBegin;                                          // +0x00
  void* mpEnd;                                            // +0x04
  void* mpEndCapacity;                                    // +0x08
  ~StarVector();                                          // 0x00ae6970
};
struct SpVectorPtr {
  void* mpBegin;                                          // +0x00
  ~SpVectorPtr() {
    if (mpBegin != 0 && ((int32_t*)mpBegin)[-1] != 0)
      FUN_00f47380(mpBegin);
  }
};
class cScenarioTutorialsList {
public:
  ~cScenarioTutorialsList();                              // 0x00f01d60
  uint32_t pad00;                                         // +0x00
  AutoRefCount<cRefCounted> m04;                          // +0x04
  AutoRefCount<cRefCounted> m08;                          // +0x08
  AutoRefCount<cRefCounted> m0c;                          // +0x0c
  AutoRefCount<cRefCounted> m10;                          // +0x10
  AutoRefCount<cRefCounted> m14;                          // +0x14
  AutoRefCount<cRefCounted> m18;                          // +0x18
  AutoRefCount<cRefCounted> m1c;                          // +0x1c
  AutoRefCount<cRefCounted> m20;                          // +0x20
  AutoRefCount<cRefCounted> m24;                          // +0x24
  AutoRefCount<cRefCounted> m28;                          // +0x28
  AutoRefCount<cRefCounted> m2c;                          // +0x2c
  uint32_t pad30;                                         // +0x30
  StarVector m34;                                         // +0x34
  uint8_t pad40[0x14];                                    // +0x40
  AutoRefCount<cRefCounted> m54;                          // +0x54
  AutoRefCount<cRefCounted> m58;                          // +0x58
  AutoRefCount<cRefCounted> m5c;                          // +0x5c
  AutoRefCount<cRefCounted> m60;                          // +0x60
  uint8_t pad64[0x28];                                    // +0x64
  SpVectorPtr m8c;                                        // +0x8c
};
#define g_TutorialsEnabled (*(char*)0x016065f8)            // 0x016065f8
#define g_pActiveTutorial (*(void**)0x015ad298)            // 0x015ad298
struct cScenarioTutorials {
  bool CheckObject(uint32_t handle);                       // 0x00efeae0
};
extern cScenarioTutorials g_ScenarioTutorials;             // 0x015ad328
struct cTutorialQuery {                                   // result of the 0x11966ed query
  void Finish();                                          // 0x00b16270
};
struct cTutorialManager {
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
virtual void t20();
virtual void t24();
virtual void t28();
virtual void t2c();
virtual void t30();
virtual void t34();
  virtual bool IsSuppressed();                            // +0x38
};
struct cTutorialEntry {
virtual void e00();
virtual void e04();
virtual void e08();
  virtual cTutorialQuery* Query(unsigned id);             // +0x0c
};
struct cTutorialHost {
virtual void h00();
virtual void h04();
virtual void h08();
virtual void h0c();
virtual void h10();
virtual void h14();
virtual void h18();
virtual void h1c();
virtual void h20();
virtual void h24();
virtual void h28();
virtual void h2c();
virtual void h30();
virtual void h34();
  virtual cTutorialEntry* GetEntry();                     // +0x38
};
void __stdcall FUN_00efe930(uint32_t handle);             // 0x00efe930 ScenarioTutorials_SetSelectedWindow
void __stdcall FUN_00f00bd0(uint32_t handle);             // 0x00f00bd0 CommitPlacement
struct cPlacementThing {
  void SetPlacement();                                    // 0x00efccd0 (thing passed in eax)
};
struct cTutorialService {
  int32_t Place(uint32_t handle);                         // 0x00f32790
};
bool __cdecl FUN_00efc9c0();                              // 0x00efc9c0
struct cGridProvider {
  uint32_t GetCount();                                    // 0x008d3ac0
  void* GetPath(int32_t mode);                            // 0x00688ed0
};
struct FileStream {
  void* mpVt00;                                           // +0x00
  uint8_t pad04[0x8c];
  void Ctor(const wchar_t* pName);                        // 0x00931e10
  void AddRef();                                          // 0x009317b0
  bool Open(unsigned f0, unsigned f1, unsigned f2, unsigned f3);  // 0x009318f0
  bool Close();                                           // 0x00931a70
  void Dtor();                                            // 0x00931e70
};
struct cImportInfo {
  void* mpVt00;                                           // +0x00
  uint32_t mAsset;                                        // +0x04
  uint8_t pad08[0xc];
  void Ctor();                                            // 0x005f8e00
  void Dtor();                                            // 0x005f8e40
};
struct cImportReader {
  bool Read();                                            // 0x005fbb00
};
void* __stdcall FUN_005f7930(FileStream* pStream, cImportInfo* pInfo, int32_t zero); // 0x005f7930
bool __stdcall FUN_004bbe20(uint32_t asset, int32_t zero);                 // 0x004bbe20 SetAssetData
struct V3Vector {                                          // eastl::sp_vector<V3>
  V3* mpBegin;                                             // +0x00
  V3* mpEnd;                                               // +0x04
  V3* mpEndCapacity;                                       // +0x08
  void Destroy();                                          // 0x00540520
};
void* __stdcall FUN_005f7930(V3Vector* pGrid, void* pObj);                 // 0x005f7930 fill helper
struct cFillResult {
  void Commit();                                           // 0x005fd260
};
int32_t __cdecl FUN_00efe870(const V3* pPoint);           // 0x00efe870 FindSurfacePoint
struct cIconService {
  int32_t GetIconCount(int32_t key);                      // 0x00ed20c0
  void RemoveIcon(int32_t id);                            // 0x00ed38a0
};
struct cPointTable {
  int32_t FindPoint(const V3* pPoint);                    // 0x00f46450
};
struct cSPEditorDevUI {
virtual void g00();
virtual void g04();
virtual void g08();
virtual void g0c();
virtual void g10();
virtual void g14();
virtual void g18();
virtual void g1c();
virtual void g20();
virtual void g24();
virtual void g28();
virtual void g2c();
  virtual void g30();
  virtual bool RefreshGrid(int32_t id);                    // +0x34
  uint32_t pad04;                                          // +0x04
  void* mpTable08;                                         // +0x08
  bool RefreshGrids(int32_t argUnused, void* pObj);        // 0x00f01f40
};
// ---- items of slice s00f015b0 end

// ---- items of slice s00f02160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*   g_Simulator;       // 0x016c7aa4
extern uint8_t g_15ad328[];       // 0x015ad328 (ScenarioTutorialsPlacement instance)
extern float   g_f16c7b98;        // 0x016c7b98
extern float   g_f16c7b9c;        // 0x016c7b9c
extern float   g_f16c7ba0;        // 0x016c7ba0
extern "C" void* __cdecl operator_new6(unsigned, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void  __cdecl operator_delete_(void*);          // 0x00f47380
extern "C" void* __fastcall FUN_00f31fd0(void* self, int dummy); // 0x00f31fd0
extern "C" void* __cdecl FUN_00efc830(void*);               // 0x00efc830
extern "C" void* __cdecl FUN_007dcb00(void*, const void*, const void*); // 0x007dcb00
extern "C" void  __cdecl FUN_00f01140(void*, void*, void*, int, int);   // 0x00f01140
extern "C" void  __cdecl FUN_00eec940(void*, int);          // 0x00eec940
extern "C" void  __cdecl SP_QuaternionFromDirections(void*, const void*, const void*); // 0x698180
extern "C" void f_eff0c0_ext();   // 0x00eff0c0
extern "C" void f_efd020_ext();   // 0x00efd020
extern "C" void f01c20_ext();     // 0x00f01c20
extern "C" void f00f80_ext();     // 0x00f00f80
extern void* g_vtbl_148b708[];   // 0x0148b708  (the PL vtable itself)
extern void* g_vtbl_148b788[];   // 0x0148b788  (the ScenarioTutorialsPlacement vtable)
struct Quat4 { float x, y, z, w; };                 // EA::Quaternion (16 bytes)
struct Plane4 { float x, y, z, w; void build(); };  // 0x00efd8e0 (plane ctor)
struct RectT  { void assign(const void*); };        // 0x00572600 ret 4
struct PM     { V3* f_b82110(Plane4*, V3*, V3*); };  // 0x00b82110 ret 0xc
extern "C" void* __cdecl FUN_00b3d350_s00f0_2160();                    // 0x00b3d350  SP::PlanetModel
struct SW {                       // EA::Stopwatch at +0xb0
    void ctor(int, int);          // 0x93a560
    void SetTimeLimit(int, int);  // 0x93a480
};
struct X { void run(); };
struct V4_s00f0_2160 {
    void* p0;
    int   f4;
    int   f8;
    float fC;
};
struct Vec;                       // 0x00dfb850
struct Big;
struct GObj_s00f0_2160;
struct WndC;
struct Vec30;
struct VecBox;
struct Vec {
    void destroy(void* b, void* e);              // 0x00dfb850 ret 8
};
struct Big {
    void* h0;                     // +0x00
    char  pad04[0x0c];            // +0x04 .. +0x0f
    float rc10[4];                // +0x10  a RectT<float>
    float f20;                    // +0x20
    char  pad24[4];
    char* begin;                  // +0x28
    char* end;                    // +0x2c
    char  pad30[0x1b4];           // +0x30 .. +0x1e3
    float f1e4;                   // +0x1e4
    float v1e8[3];                // +0x1e8  a Vector3
    float rc1f4[4];               // +0x1f4  a RectT<float>
    float f204;                   // +0x204
    char  pad208[4];
    int*  p20c;                   // +0x20c
    void* assign(void* src);      // 0x00dfd3a0 ret 4  (copy into this)
};
struct GObj_s00f0_2160 {
    void* vtable;                 // +0x00
    char  pad04[0x1c];            // +0x04 .. +0x1f
    uint8_t b20;                  // +0x20
    void  f45970();               // 0x00f45970
    void  f45a80();               // 0x00f45a80
    void  f414b0();               // 0x00f414b0
    void  f42a00(void*);          // 0x00f42a00 ret 4
    GObj_s00f0_2160* f3e8a0(void*);          // 0x00f3e8a0 ret 4
    void  f3da90(void*, int);     // 0x00f3da90 ret 8
    void  f3bbd0(void*, int);     // 0x00f3bbd0 ret 8
    char  f253e0();               // 0x00f253e0
};
struct Sim {
    char  pad00[0x74];            // +0x00 .. +0x73
    GObj_s00f0_2160* p74;                    // +0x74
};
#define SIM ((Sim*)g_Simulator)
struct Ter {
    char  pad000[0x128];          // +0x000 .. +0x127
    float f128;                   // +0x128
    float f12c;                   // +0x12c
    float f130;                   // +0x130
    float f134;                   // +0x134
    char  pad138[0x30];           // +0x138 .. +0x167
    float f168;                   // +0x168
    float f16c;                   // +0x16c
    float f170;                   // +0x170
    float f174;                   // +0x174
};
struct SubWnd {                   // the inner window stored inline at WndC+0x34
    void* vtable;                 // +0x34
};
struct WndC {
    void* vtable;                 // +0x00
    char  pad04[0x30];            // +0x04 .. +0x33
    SubWnd sub34;                 // +0x34  (an inner window, has its own vtable)
    char  pad38[0x144];           // +0x38 .. +0x17b
    float f17c;                   // +0x17c
    char  pad180[0x18];           // +0x180 .. +0x197
    float f198;                   // +0x198
    float f19c;                   // +0x19c
    float f1a0;                   // +0x1a0
    float f1a4;                   // +0x1a4   (also rc198[3])
    float f1a8;                   // +0x1a8   (also rc1a4[1])
    float f1ac;                   // +0x1ac
    float f1b0;                   // +0x1b0
    float f_efc4c0();                     // 0x00efc4c0
    void  f_efce30(void*, void*, float);   // 0x00efce30 ret 0xc
};
struct VecBox {
    void* begin;                  // +0x00
    void* end;                    // +0x04
    void* cap;                    // +0x08
    void* f0c;                    // +0x0c
    char  pad10[8];               // +0x10
    void  fromVec(void* src);     // 0x00f02d80 ret 4
    void  build(int n, void* src); // 0x00dfa400 ret 8
};
struct Vec30 {
    char  pad[4];
    bool  f_c68250(void*);        // 0x00c68250 ret 4
    void  check(void*, bool*);    // 0x00c688a0 ret 8
    void  f_c64940(void*);        // 0x00c64940 ret 4
};
struct Mgr_s00f0_2160 {
    int   curIdx;                 // +0x00
    void* f4;                     // +0x04
    void* f8;                     // +0x08
    void* fC;                     // +0x0c
    void* f10;                    // +0x10
    void* f14;                    // +0x14
    char  pad18[0x10];            // +0x18 .. +0x27
    void* f28;                    // +0x28
    void* f2c;                    // +0x2c
    char  vec30[0x24];            // +0x30
    void* f54;                    // +0x54
    void* f58;                    // +0x58
    char  pad5c[0x0c];            // +0x5c .. +0x67
    int   f68;                    // +0x68
    char  pad6c[0x20];            // +0x6c .. +0x8b
    VecBox vec8c;                 // +0x8c
    uint8_t fA4;                  // +0xa4
};
#define MGR ((Mgr_s00f0_2160*)g_mgr)
#define VEC30 ((Vec30*)((char*)MGR + 0x30))
struct PL {
    void*  vtable;    // +0x00
    uint8_t b4;       // +0x04
    uint8_t b5;       // +0x05
    uint8_t b6;       // +0x06
    uint8_t b7;       // +0x07
    void*  pGame;     // +0x08  (the scene GObj)
    V4_s00f0_2160*    pC;        // +0x0c
    void*  p10;       // +0x10
    char   pad14[0x168];   // +0x14 .. +0x17b
    float  f17c;      // +0x17c
    void  f02160();              // 0x00f02160
    void  f02670();              // 0x00f02670
    void  f02700();              // 0x00f02700
    int   f02a10(int, int, float); // 0x00f02a10 ret 0xc
    void  f02b00();              // 0x00f02b00
    PL*   f02b80();              // 0x00f02b80
    PL*   ctor_2cd0();           // 0x00f02cd0
    void  f02c50();              // 0x00f02c50
    PL*   f02d30(int);           // 0x00f02d30 ret 4
    void  f02e00();              // 0x00f02e00
    void  f03010();              // 0x00f03010
    void  f030a0();              // 0x00f030a0
    void  SetObjectEx(void*);        // 0x00eff280 ret 4
    void  CommitObject(void*);       // 0x00eff360 ret 4
    void  AdjustPlacement(void*, float); // 0x00f01030 ret 8
    char  UpdatePlacement(void*);    // 0x00f00e50 ret 4
    void  MsgTeardown();             // 0x00f00d10
    void  ClearObject();             // 0x00eff3b0
    char  CheckObject(void*);        // 0x00efeae0 ret 8
};
// ---- items of slice s00f02160 end

// ---- items of slice s00f031a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*    g_15f7cf4;      // 0x015f7cf4
extern uint8_t  g_016c7b34[];   // 0x016c7b34
extern uint8_t  g_16c7c08[];    // 0x016c7c08
extern uint8_t  g_015ad45c[];   // 0x015ad45c
extern uint8_t  g_015ad468[];   // 0x015ad468
extern uint8_t  g_015ad450[];   // 0x015ad450
extern "C" void* __cdecl FUN_00eeca30(void*);                  // 0x00eeca30
extern "C" void  __cdecl FUN_00efcec0(void*, void*);           // 0x00efcec0
extern "C" void* __cdecl FUN_0067dd60();                       // 0x0067dd60
extern "C" void* __cdecl FUN_00b3d300();                       // 0x00b3d300
extern "C" void  __cdecl FUN_00809db0(void*, void*);           // 0x00809db0
extern "C" void  __cdecl SPUI_UpdateMouseFocus(int);           // 0x00804f50
extern "C" void* __cdecl EA_ConvertToString16(void*, int);     // 0x0093c6d0
extern "C" void  __cdecl SPUI_AutoSizeWindowForText(void*, int, int); // 0x00806e40
extern "C" void  __cdecl EA_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
extern "C" bool  __cdecl GetYTPrompt();                        // 0x0063b890
struct Big_s00f0_31a0 {
    char  pad0[0x28];
    char* begin;        // +0x28
    char* end;          // +0x2c
    char  pad2[0x1dc];  // +0x30 .. +0x20b
    int*  p20c;         // +0x20c
    char  pad3[0x24];   // size 0x234
    Big_s00f0_31a0*  init();                 // 0x00f2aac0
    Big_s00f0_31a0*  copyFrom(Big_s00f0_31a0*);         // 0x00dfdfe0
    Big_s00f0_31a0*  assign(Big_s00f0_31a0*);           // 0x00dfd3a0
};
struct GObj_s00f0_31a0;
struct GObj_s00f0_31a0 {
    void*   vtable;     // +0x00
    char pad4[0x0c];
    void* f10;          // +0x10
    char pad14[0x5a];   // -> +0x6e
    uint8_t b6e;        // +0x6e
    void InitThing();                 // 0x00f3c060
    void KillThing();                 // 0x00f3c0b0
    void* GetAt(void*);               // 0x00f3cb30 ret 4
    void f401a0();                    // 0x00f401a0
    void f40370();                    // 0x00f40370
    void f414b0();                    // 0x00f414b0
    void f427c0();                    // 0x00f427c0
    void f42a00(void*);               // 0x00f42a00 ret 4
    void f45a80();                    // 0x00f45a80
    char ScenarioNode_Load(void*);    // 0x00f3ff70 ret 4
    void f32880(void*);               // 0x00f32880 ret 4
    void f347e0();                    // 0x00f347e0
    void f3da90(void*, int);          // 0x00f3da90 ret 8
    void f3bbd0(void*, int);          // 0x00f3bbd0 ret 8
    void* f3e8a0(void*);              // 0x00f3e8a0 ret 4
    void f_ed4e90();                  // 0x00ed4e90
    void f_ed4f00(int);               // 0x00ed4f00 ret 4
};
struct Tut {
    void f_eeff80();                  // 0x00eeff80
};
struct HintObj {
    void ToggleHint(int, int);        // 0x00efbbe0 ret 8
};
struct RefObj {
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void v0c(int);
};
struct NounMgr {
    void RemoveNoun(void*);           // 0x00b225d0 ret 4
};
struct MgrB {
    void f33ce0(int);                 // 0x00b33ce0 ret 4
    void f33cf0(int);                 // 0x00b33cf0 ret 4
};
struct Mgr_s00f0_31a0 {
    int   f0;           // +0x00
    void* f4;           // +0x04
    void* f8;           // +0x08
    void* fC;           // +0x0c
    void* f10;          // +0x10
    void* f14;          // +0x14
    void* f18;          // +0x18
    void* f1c;          // +0x1c
    void* f20;          // +0x20
    void* f24;          // +0x24
    void* f28;          // +0x28
    void* f2c;          // +0x2c
    char  vec30[0x24];  // +0x30
    void* f54;          // +0x54
    void* f58;          // +0x58
    void* f5c;          // +0x5c
    void* f60;          // +0x60
    char  pad64[4];
    int   f68;          // +0x68
    char  pad6c[0x20];  // +0x6c .. +0x8b
    char  vec8c[0x18];  // +0x8c
    uint8_t fA4;        // +0xa4
};
#define MGR_s00f0_31a0 ((Mgr_s00f0_31a0*)g_mgr)
struct PL_s00f0_31a0 {
    void** vtable;      // +0x00
    uint8_t b4;         // +0x04
    uint8_t b5;         // +0x05
    uint8_t b6;         // +0x06
    uint8_t b7;         // +0x07
    GObj_s00f0_31a0*  pGame;       // +0x08
    Big_s00f0_31a0*   pC;          // +0x0c
    void*  p10;         // +0x10

    void f031a0();
    void f031d0();
    void f03290();
    bool f03320();
    void f03440();
    bool f036f0();
    int  f03890(int, int, float);   // ret 0xc
    void f00610(void*, float);      // 0x00f00610 ret 8
    char f00850(void*);             // 0x00f00850 ret 4
    void f02670();                  // 0x00f02670
    void f_efec90(void*);           // 0x00efec90 ret 4
    void f_efee60(void*);           // 0x00efee60 ret 4
    char Scenario_CheckObj(void*);  // 0x00efeae0 ret 8
    void f_efebb0(void*);           // 0x00efebb0 ret 4
};
struct Vec30_s00f0_31a0 {
    void add(void*);                  // 0x00c68190 ret 4
    void check(void*, bool*);         // 0x00c688a0 ret 8
    void clear();                     // 0x00c68840
};
struct CamObj {
    float* f_b10260();                // 0x00b10260
    float* f_644a70();                // 0x00644a70
    float  f_c37540();                // 0x00c37540
};
struct IW {
    virtual void* v00();
    virtual void* v04();
    virtual void* v08();
    virtual void* v0c(unsigned);
    virtual void* v10();
    virtual void* v14();
    virtual void* v18();
    virtual void* v1c();
    virtual void* v20();
    virtual void* v24();
    virtual void* v28(int);
    virtual void* v2c();
    virtual void* v30();
    virtual void* v34(int, bool);
    virtual float* v38();
    virtual void* v3c();
    virtual void* v40();
    virtual void* v44();
    virtual void* v48();
    virtual void* v4c();
    virtual void* v50();
    virtual void* v54();
    virtual void* v58();
    virtual void* v5c();
    virtual void* v60();
    virtual void* v64();
    virtual void* v68();
    virtual void* v6c();
    virtual void  v70(float, float);
    virtual void* v74();
    virtual void* v78();
    virtual void  v7c(int, int);
    virtual void  v80(void*);
    virtual void* v84();
    virtual void* v88();
    virtual void* v8c();
    virtual void* v90();
    virtual void* v94();
    virtual void* v98();
    virtual void* v9c();
    virtual void* va0();
    virtual void* va4();
    virtual void* va8();
    virtual void* vac();
    virtual void* vb0();
    virtual void* vb4();
    virtual void* vb8(unsigned);
    virtual void* vbc();
    virtual void* vc0();
    virtual void* vc4();
    virtual void* vc8();
    virtual void* vcc();
    virtual void* vd0();
    virtual void* vd4();
    virtual void* vd8();
    virtual void* vdc();
    virtual void* ve0();
    virtual void* ve4();
    virtual void* ve8();
    virtual void* vec();
    virtual void* vf0(unsigned, bool);
    virtual void* vf4();
    virtual void* vf8();
    virtual void* vfc();
};
struct Layout {
    IW* FindWindowByID(unsigned, bool);   // 0x008105b0 ret 8
};
struct Q2c {
    virtual void* d00();
    virtual void* d04();
    virtual void* d08();
    virtual void* d0c();
    virtual void* d10();
    virtual void* d14();
    virtual void* d18();
    virtual void* d1c();
    virtual void* d20();
    virtual void* d24();
    virtual void* d28();
    virtual V3*   v2c(V3* out, void* id);
};
struct Str16 { void* begin; void* pad4; void* end; void* padC; };
struct UI_s00f0_31a0 {
    void*   vtable;     // +0x00
    uint8_t f4;         // +0x04
    uint8_t b5;         // +0x05
    uint8_t b6;         // +0x06
    uint8_t b7;         // +0x07
    void*   p8;         // +0x08
    void*   pC;         // +0x0c
    void*   p10;        // +0x10
    void*   h14;        // +0x14
    void*   h18;        // +0x18
    void*   h1c;        // +0x1c
    void*   h20;        // +0x20
    void*   h24;        // +0x24
    int     step;       // +0x28
    Layout* layout;     // +0x2c
    IW*     w30;        // +0x30
    IW*     w34;        // +0x34
    IW*     w38;        // +0x38
    char    pad3c[0x18];
    int     f54;        // +0x54
    char    pad58[0x0c];
    int     f64;        // +0x64
    char    pad68[0x11];
    uint8_t b79;        // +0x79
    char    pad7a[0x52];
    RefObj* rcc;        // +0xcc
    void**  vD0;        // +0xd0
    void**  vD4;        // +0xd4
    char    padD8[0x0c];
    void**  vE4;        // +0xe4

    void f03d20();
    void f03d50();
    void f03d80();
    void f03de0();
    void f03e20();
    void f03e40();
    void f03e90();
    void f03fa0();
    void f03fc0(int);
    bool f03ff0(unsigned, V3*, char);
    void f04070(char);
    void f040e0(int);
};
// ---- items of slice s00f031a0 end

// @ 0x00f00610
void UI::SyncPlacement(int handle, float dt)
{
    if (handle == 0) return;
    Mgr* m = (Mgr*)g_mgr;
    if (g_015acb40 != 0 && m->begin8c != m->end90) {
        ((Simulator*)gSimulator)->p74->F3BBD0((int)m->mp4, 0);
        return;
    }
    if (b5 == 0) {
        g_016c7b34obj.F_eeff40();
        b5 = 1;
        pGame->F45970();
    }
    Node* n = (Node*)FUN_00eebf80((void*)handle);
    Key key;
    FUN_00eec3d0(&key, n);
    float cur = n->f20;
    float scaled = s_exp(g_015ad360 * dt) * cur;
    int gt = scaled > cur;
    float res = FUN_00f409a0(n, &key, scaled, gt, &n->f24);
    n->f20 = res;
    if (res != cur) {
        if (key.b == 0x2b978c46) {
            ((UI*)((Simulator*)gSimulator)->pD4)->ToggleHint(0x23, 0x24);
        } else if (FUN_00eece20(&key) == 0xe137ff08) {
            ((UI*)((Simulator*)gSimulator)->pD4)->ToggleHint(0x37, 0x38);
        }
    }
    pGame->F3DA90(n, 0);
    char chk = g_015ad328obj.CheckObject((void*)handle);
    ((Simulator*)gSimulator)->p74->F3BBD0(handle, chk == 0);
}

// @ 0x00f00790
char UI::ApplyPlacement(void* p)
{
    if (!pGame->F3EC90(p)) {
        void* ms = FUN_0067dcc0();
        ((ThV3)vslot(ms, 0x14))(ms, 0x78c406b, 0, 0);
        return 0;
    }
    pGame->F45970();
    b6 = 1;
    void* r = FUN_00eec0d0(Place(p));
    FUN_00efe260();
    FwdC6E0(r);
    ((ThV1)vslot(this, 0x18))(this, 1);
    FUN_00efd970(r);
    void* gd = ((GD*)r)->F_B18530();
    if (gd != 0 && ((CGameData*)gd)->F_F253E0())
        ((UI*)r)->F_efcde0();
    g_016c7b34obj.F_eeff40();
    void* gim = FUN_00b3d250();
    ((ThV2)vslot(gim, 0x64))(gim, 0xc9d8638f, 1);
    return 1;
}

// @ 0x00f00850
char UI::ApplyPlacementEx(void* p)
{
    Mgr* m = (Mgr*)g_mgr;
    if (m->mp10 != 0) {
        void* obj = m->mp10;
        int t = ((ThI1)vslot(obj, 0xc))(obj, 0x76c67df);
        if (t == 0) return 0;
        if (t == (int)m->mp28) return 0;
        if (m->mpSelected != p) F_efec90(p);
        ((Container*)m->mVec30)->F_00c68d20((void*)t);
        Node* n = (Node*)FUN_00eebf80(m->mp4);
        SNode* s = (SNode*)pGame->F3E8A0(n->vtable);
        char* base = n->p28;
        if (s->b20 == 0) {
            char flag = 0;
            ((Container*)m->mVec30)->F_00c688a0(base + m->mIndex * 0x34 + 0x1c, &flag);
            if (flag) *(uint32_t*)(base + m->mIndex * 0x34 + 0x30) = 2;
        } else {
            int count = (int)((n->p2c - n->p28) / 0x34);
            for (int i = 0; i < count; i++) {
                char flag = 0;
                ((Container*)m->mVec30)->F_00c688a0(base + i * 0x34 + 0x1c, &flag);
                if (flag) *(uint32_t*)(base + i * 0x34 + 0x30) = 2;
            }
        }
        ((UI*)((Simulator*)gSimulator)->pD4)->ToggleHint(0x63, 0x64);
        return 1;
    }
    if (!F_efc660(p)) return 0;
    bool e0 = (m->mpSelected == 0);
    bool skip = false;
    if (b5 != 0) { b5 = 0; FUN_00efe260(); }
    else if (e0) skip = true;
    if (!skip) {
        if (b6 != 0) {
            void* h = FUN_00eebf80(p);
            FUN_00eef7d0(h);
        }
        pGame->F45A80();
        b6 = 0;
    }
    pGame->F45970();
    void* n3 = FUN_00b3d240();
    void* r = ((ThP0)vslot(n3, 0x34))(n3);
    int t = 0;
    if (r != 0) t = ((ThI1)vslot(r, 0xc))(r, 0x17f243b);
    if (t != (int)p) {
        Node* o = (Node*)FUN_00b18e00(p);
        if (o != 0) {
            void* h = FUN_00ae66d0(o);
            ((ThV1)vslot(o, 0x28))(o, 0);
            if (h == m->mp8 && m->mp8 != 0) {
                void* old = m->mp8;
                m->mp8 = 0;
                do_release(old);
            }
            int* f = ((ThIP0)vslot(o, 0xac))(o);
            if (f) f[1] &= ~8u;
        }
    }
    void* h2 = FUN_00eebf80(p);
    void* r2 = FUN_00eec0d0(pGame->F445C0(h2));
    char c = CheckObject(r2);
    pGame->F3BBD0((int)r2, c == 0);
    FUN_00efe260();
    FwdC6E0(r2);
    ((UI*)((Simulator*)gSimulator)->pD4)->ToggleHint(0x21, 0x22);
    b7 = 1;
    FUN_00eef4b0(&m->begin8c);
    return 1;
}

// @ 0x00f00b00
V4* V4::assign(V4* src)
{
    void* old = p0;
    void* nw = src->p0;
    if (nw != old) {
        if (nw) ((Ref*)nw)->v0();
        p0 = nw;
        if (old) ((Ref*)old)->v4();
    }
    f4 = src->f4;
    f8 = src->f8;
    fC = src->fC;
    return this;
}

// @ 0x00f00b50
void UI::f00b50()
{
    void* u = *(void**)((char*)g_mgr + 4);
    void* r = pGame->F32790(u);
    if (r) {
        pGame->F33BF0();
        ((V4*)pC)->assign((V4*)r);
        ((void(__thiscall*)(void*, int)) * ((void**)vtable + 0x20 / 4))(this, 0);
        pGame->F38150(u);
        pGame->F34560();
    }
}

// @ 0x00f00ba0
void UI::f00ba0()
{
    void* r = pGame->F32790(*(void**)((char*)g_mgr + 4));
    if (r) ((V4*)pC)->assign((V4*)r);
}

// @ 0x00f00bd0
void UI::CommitPlacement(void* p)
{
    Mgr* m = (Mgr*)g_mgr;
    if (m->mp20 == 0) return;
    if (p == 0) {
        void* x = m->mp10;
        if (x != 0) { m->mp10 = 0; do_release(x); }
        ((ThV1)vslot(this, 0x18))(this, 0);
    }
    void* r = pGame->F32790(p);
    if (p != 0) {
        int t = ((ThI0)vslot(p, 0x38))(p);
        bool matched = (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a ||
                        t == 0x7a81824 || t == 0x7abdd8d);
        if (matched && r == 0) {
            ((AutoRef*)&m->mp10)->F_00b5f950(p);
            return;
        }
    }
    pGame->f1b0 = r;
    void* old4 = m->mp4;
    if (p != old4) {
        if (p != 0) ((ThV0)vslot(p, 0))(p);
        m->mp4 = p;
        if (old4 != 0) do_release(old4);
    }
    if (p == 0 && m->mp8 != 0) { void* o = m->mp8; m->mp8 = 0; do_release(o); }
    UpdateVisibility();
    if (old4 != p) {
        void* gim = FUN_00b3d250();
        uint32_t arg = (p != 0 ? 0x463ccfb9u : 0u) + 0x91247de4u;
        ((ThV2)vslot(gim, 0x64))(gim, (int)arg, 1);
    }
}

// @ 0x00f00d10
void UI::Teardown()
{
    Mgr* m = (Mgr*)g_mgr;
    Node* x = (Node*)FUN_00b18e00(m->mp10);
    if (x != 0) {
        void* h = FUN_00ae66d0(x);
        ((ThV1)vslot(x, 0x28))(x, 0);
        if (h == m->mp8 && m->mp8 != 0) { void* o = m->mp8; m->mp8 = 0; do_release(o); }
        int* f = ((ThIP0)vslot(x, 0xac))(x);
        if (f) f[1] &= ~8u;
    }
    pGame->F38330(1);
    pGame->F34560();
    if (m->mpSelected != 0) { void* o = m->mpSelected; m->mpSelected = 0; do_release(o); }
    if (m->mp10 != 0) { void* o = m->mp10; m->mp10 = 0; do_release(o); }
    g_16c7d74 = (g_16c7d74 == 0.0f) ? 1.0f : 0.0f;
    void* at = FUN_00a206f0();
    if (at != 0) {
        ((ThV1)vslot(at, 0x38))(at, 0x3cdd1a9);
        ((ThV2)vslot(at, 0x40))(at, 0x34753a7, (int)0xa984aa45u);
        ((ThV2F)vslot(at, 0x3c))(at, 0x34753aa, g_16c7d74);
        ((ThV0)vslot(at, 0x58))(at);
    }
}

// @ 0x00f00e50
char UI::UpdatePlacement(void* p)
{
    Mgr* m = (Mgr*)g_mgr;
    void* n = pGame->F32790(p);
    if (p != 0) {
        int t = ((ThI0)vslot(p, 0x38))(p);
        bool inSet = (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a ||
                      t == 0x7a81824 || t == 0x7abdd8d);
        if (inSet && n == 0) return 0;
    }
    bool e0 = (m->mpSelected == 0);
    if (!F_efc7d0(p, (void*)(size_t)((PObj*)n)->f4)) return 0;
    bool skip = false;
    if (b5 != 0) b5 = 0;
    else if (e0) skip = true;
    if (!skip) {
        void* o = (void*)FUN_00b18e00(p);
        if (o != 0) {
            void* h = FUN_00ae66d0(o);
            ((ThV1)vslot(o, 0x28))(o, 0);
            if (h == m->mp8 && m->mp8 != 0) { void* old = m->mp8; m->mp8 = 0; do_release(old); }
            int* f = ((ThIP0)vslot(o, 0xac))(o);
            if (f) f[1] &= ~8u;
        }
        pGame->F38330(1);
        pGame->F34560();
        b6 = 0;
    }
    pGame->F33BF0();
    void* r = pGame->F336A0(n);
    SetObject(r);
    pGame->F36450((int)r, 0, n);
    b7 = 1;
    return 1;
}

// @ 0x00f00f80
void UI::Dispatch()
{
    Mgr* m = (Mgr*)g_mgr;
    void* obj = m->mp10;
    if (obj == 0 || m->mpSelected == 0) return;
    ((ThV0)vslot(obj, 0x5c))(obj);
    if (obj == m->mp20) {
        void* a = FUN_00b18e00(m->mpSelected);
        ((ThP1)vslot(a, 0x3c))(a, (char*)obj + 0x1a4);
        return;
    }
    if (obj == m->mp5c) {
        float v = ((Mp10Obj*)obj)->F_efc4c0() + g_0148cfe8;
        uint8_t old = b5;
        b5 = 1;
        Adjust(m->mpSelected, v);
        b5 = old;
        return;
    }
    if (obj == m->mp60) {
        float v = ((Mp10Obj*)obj)->F_efc4c0();
        *(float*)((char*)pGame->f1b0 + 0xc) = v;
    }
}

// @ 0x00f01030
void UI::f01030(void* p, float f)
{
    if (p == 0) return;
    if (b5 == 0) {
        b5 = 1;
        pGame->F33BF0();
        pGame->F36450(0, 0, p);
    }
    VObj* r = (VObj*)FUN_00b18e00(p);
    float cur = r->v34();
    ((void(__thiscall*)(void*, void*, float))f_eff4c0_impl)(this, p, f * 0.01f + cur);
}

// @ 0x00f01090
char UI::AddObject(void* unused)
{
    (void)unused;
    void* p10 = this->p10;
    NodeB* v = (NodeB*)FUN_00b18e00(0);
    if (v != 0 && v->b6e != 0) return 0;
    if (!pGame->F326D0(p10)) {
        void* ms = FUN_0067dcc0();
        ((ThV3)vslot(ms, 0x14))(ms, 0x78c406b, 0, 0);
        return 0;
    }
    b6 = 1;
    pGame->F33BF0();
    void* r = GetPlacement();
    SetObject(r);
    pGame->F36450((int)r, (int)p10, 0);
    ((ThV1)vslot(this, 0x18))(this, 1);
    FUN_00efd970(r);
    g_016c7b34obj.F_eeff40();
    void* gim = FUN_00b3d250();
    ((ThV2)vslot(gim, 0x64))(gim, 0xc9d8638f, 1);
    return 1;
}

// @ 0x00f01140
void** __cdecl f01140(void** out, const Rec* begin, const Rec* end, Rec* dst)
{
    *out = dst;
    if (begin == end) return out;
    do {
        if (dst) {
            dst->f0 = begin->f0;
            dst->f1 = begin->f1;
            dst->f2 = begin->f2;
            dst->f3 = begin->f3;
            dst->f4 = begin->f4;
            dst->f5 = begin->f5;
            dst->f6 = begin->f6;
            dst->f7 = begin->f7;
        }
        begin = (const Rec*)((const char*)begin + 0x20);
        dst = (Rec*)((char*)dst + 0x20);
    } while (begin != end);
    *out = dst;
    return out;
}

// @ 0x00f011b0
void BuildScene()
{
    Mgr* m = (Mgr*)g_mgr;
    void* sel = m->mpSelected;
    Node* n = (Node*)FUN_00eebf80(sel);
    uint32_t handle = (uint32_t)(size_t)FUN_00b18e00(sel);
    Vec3 base = n->pos;
    float radius = m->f78;

    void* app = FUN_0067dd10();
    Vec3 dirA, dirB;
    ((ThV2P)vslot(app, 0x58))(app, &dirB, &dirA);
    FUN_007c4900(&dirB, &dirA);
    FUN_00efd8e0();

    // probe point: base + dirA
    float p1 = base.x + dirA.x;
    float p2 = base.y + dirA.y;
    float p3 = base.z + dirA.z;
    float g1 = p1, g2 = p2, g3 = p3;

    float probeR = radius;
    if (FUN_00ebaa20(&p1, &dirB, g_016c7b98, radius, &probeR)) {
        Vec3 hit;
        hit.x = dirB.x * radius + g1;
        hit.y = dirB.y * radius + g2;
        hit.z = dirB.z * radius + g3;

        Quat q;
        FUN_00698180(&q, &n->pos, &hit);

        float rx = n->rot.x, ry = n->rot.y, rz = n->rot.z, rw = n->rot.w;
        float t68 = rz * q.w - ry * q.z;
        float t64 = q.z * rx - rz * q.x;
        float t60 = ry * q.x - q.y * rx;
        float nx = q.w * rx + rw * q.x + t68;
        float ny = q.w * ry + rw * q.y + t64;
        float nz = q.w * rz + rw * q.z + t60;
        float nw = q.w * rw - (rx * q.x + rz * q.z + ry * q.y);
        float inv = 1.0f / sqrtf(nw * nw + (nz * nz + (ny * ny + nx * nx)));
        nx *= inv; ny *= inv; nz *= inv; nw *= inv;

        n->rot.x = nx; n->rot.y = ny; n->rot.z = nz; n->rot.w = nw;
        n->pos = hit;

        uint32_t flags = 1;
        FUN_00eed720(n, (void*)(size_t)handle, &flags);
        uint32_t f = (uint32_t)((handle >> 4) & 1);
        uint32_t sel2 = 1;
        float dist = FUN_00eec370(&n->pos, f, &sel2);
        n->f220 = dist;
        char c81 = 0, c82 = 0;
        FUN_00eec8e0(n, &c82, &c81);
        if ((n->f220 > 0.0f && c81 == 0) || (n->f220 < 0.0f && c82 == 0)) {
            Vec3 out;
            out.x = out.y = out.z = 0.0f;
            void* surf = FUN_00b3d350(&out, &n->pos);
            void* res = FUN_00b82df0(surf, &n->pos, f, 1, 1, 0);
            float* rp = (float*)res;
            n->pos.x = rp[0]; n->pos.y = rp[1]; n->pos.z = rp[2];
            n->f220 = 0.0f;
        }
    }
    ((Obj74*)((Simulator*)gSimulator)->p74)->F3DA90(n, 0);
    if (g_015acb40 != 0) FUN_00eee760(n, &m->begin8c);
}

// @ 0x00f015b0
void DragObjectToSurface()
{
  unsigned h = g_UI->handle;
  Thing* thing = GetThing(h);
  Ent* e = GetEnt(h);
  V3 plane;
  ObjPlaneVec(h, &plane);
  Query q;
  q.mode = 2;
  q.a = 0;
  q.b = 1;
  q.c = 0.0f;
  q.flags = 0;
  EntQuery(e, thing, &q);
  bool lead = ((q.flags >> 4) & 1) != 0;
  V3 origin, dir;
  AppGet()->GetViewer()->GetCameraRay(&origin, &dir);
  V3 from;
  from.x = plane.x + origin.x;
  from.y = origin.y + plane.y;
  from.z = origin.z + plane.z;
  SnapOpt opt;
  bool has = false;
  if (thing != 0 && thing->QueryInterface(0x137e8e0) != 0)
    has = true;
  Planet* pm = PlanetModel();
  V3 sret;
  V3 hit;
  if (lead) {
    V3* r = pm->ProjectOpt(&sret, &from, &dir, has ? &opt : 0);
    hit.x = r->x; hit.y = r->y; hit.z = r->z;
  } else {
    V3* r = pm->Project(&sret, &from, &dir);
    hit.x = r->x; hit.y = r->y; hit.z = r->z;
  }
  bool moved;
  if (hit.x == g_Zero.x && hit.y == g_Zero.y && hit.z == g_Zero.z)
    moved = false;
  else
    moved = true;

  if (0.1f < fabsf_(e->f220)) {
    float t;
    if (!RayPlanet(&from, &dir, &g_Zero, g_UI->maxT, &t))
      return;
    V3 p2;
    p2.x = dir.x * t + from.x;
    p2.y = dir.y * t + from.y;
    p2.z = dir.z * t + from.z;
    if (moved) {
      float dx = hit.x - from.x, dy = hit.y - from.y, dz = hit.z - from.z;
      float d = (float)sqrt((double)(dz * dz + dy * dy + dx * dx)) /
                (float)sqrt((double)(dir.x * dir.x + dir.z * dir.z + dir.y * dir.y));
      if (!(t > d))
        hit = p2;
    } else {
      hit = p2;
    }
    V3 oldPos;
    oldPos.x = e->px; oldPos.y = e->py; oldPos.z = e->pz;
    Reorient(e, &oldPos, &hit);
    V3 sdir = hit;
    float scratch[3];
    int dummy;
    float* np = SurfaceDir(scratch, &sdir.x, lead, &dummy, g_Flag == 0);
    e->px = np[0]; e->py = np[1]; e->pz = np[2];
    if (0.1f < fabsf_(e->f220)) {
      float s = e->f220 / (float)sqrt((double)(e->px * e->px + e->py * e->py + e->pz * e->pz));
      e->px = e->px + e->px * s;
      e->py = e->py * s + e->py;
      e->pz = e->pz * s + e->pz;
    }
    EntRefresh(e);
    g_Svc->mgr->Commit(e, 0);
    if (g_Flag != 0)
      EntSnap(e, g_UI->snapVec);
  } else if (moved) {
    V3 oldPos;
    oldPos.x = e->px; oldPos.y = e->py; oldPos.z = e->pz;
    Reorient(e, &oldPos, &hit);
    e->px = hit.x; e->py = hit.y; e->pz = hit.z;
    EntRefresh(e);
    g_Svc->mgr->Commit(e, 0);
    if (g_Flag != 0)
      EntSnap(e, g_UI->snapVec);
  }
}

// @ 0x00f01d60
cScenarioTutorialsList::~cScenarioTutorialsList()
{
}

// @ 0x00f01e60
void FUN_00f01e60(uint32_t handle)
{
  if (g_TutorialsEnabled == 0)
    return;
  if (((cTutorialManager*)g_pActiveTutorial)->IsSuppressed())
    return;
  cTutorialHost* pHost = AppGet()->GetTutorialHost();
  cTutorialEntry* pEntry = pHost->GetEntry();
  if (pEntry == 0)
    return;
  cTutorialQuery* pQuery = pEntry->Query(0x11966ed);
  if (pQuery == 0)
    return;
  Ent* pEnt = GetEnt(handle);
  Thing* pThing = GetThing(handle);
  if (pEnt != 0) {
    if (g_pActiveTutorial == (void*)&g_ScenarioTutorials)
      FUN_00efe930(handle);
    ((cPlacementThing*)pThing)->SetPlacement();
    pQuery->Finish();
    return;
  }
  if (pThing != 0) {
    cTutorialService* pService = (cTutorialService*)*((void**)((uint8_t*)g_Svc + 0x18));
    int32_t placed = pService->Place(handle);
    if (g_pActiveTutorial == (void*)&g_ChecklistTutorialUI && placed != 0)
      FUN_00f00bd0(handle);
    ((cPlacementThing*)pThing)->SetPlacement();
    pQuery->Finish();
  }
}

// @ 0x00f01f40
bool cSPEditorDevUI::RefreshGrids(int32_t argUnused, void* pObj)
{
  (void)argUnused;
  if (g_UI->handle != 0)
    return false;
  if (!FUN_00efc9c0())
    return false;
  cGridProvider* pProvider = (cGridProvider*)pObj;
  if (pProvider->GetCount() >= 1) {
    FileStream stream;
    stream.Ctor((const wchar_t*)pProvider->GetPath(0));
    stream.AddRef();
    if (!stream.Open(1, 3, 1, 0)) {
      stream.Dtor();
      return false;
    }
    cImportInfo info;
    info.Ctor();
    cImportReader* pReader = (cImportReader*)FUN_005f7930(&stream, &info, 0);
    bool bRead = pReader->Read();
    uint32_t asset = bRead ? info.mAsset : 0;
    stream.Close();
    info.Dtor();
    if (asset == 0) {
      stream.Dtor();
      return false;
    }
    if (!FUN_004bbe20(asset, 0)) {
      stream.Dtor();
      return false;
    }
    stream.Dtor();
  }
  V3Vector grid;
  grid.mpBegin = 0;
  grid.mpEnd = 0;
  grid.mpEndCapacity = 0;
  cFillResult* pFill = (cFillResult*)FUN_005f7930(&grid, pObj);
  pFill->Commit();
  int32_t count = (int32_t)((uint8_t*)grid.mpEnd - (uint8_t*)grid.mpBegin) / 12;
  if (count == 0) {
    if (grid.mpBegin != 0 && ((int32_t*)grid.mpBegin)[-1] != 0)
      FUN_00f47380(grid.mpBegin);
    return false;
  }
  V3 first;
  first.x = grid.mpBegin[0].x;
  first.y = grid.mpBegin[0].y;
  first.z = grid.mpBegin[0].z;
  int32_t id = FUN_00efe870(&first);
  if (id == -1) {
    int32_t key = FUN_00eece20(&first);
    if (key == 0x867a9ee9) {
      grid.Destroy();
      return false;
    }
    void* pService = *((void**)((uint8_t*)g_Svc + 0x14));
    cIconService* pIcons = (cIconService*)*((void**)((uint8_t*)pService + 0x14));
    if (pIcons->GetIconCount(key) < 1) {
      grid.Destroy();
      return false;
    }
    id = ((cPointTable*)mpTable08)->FindPoint(&first);
    if (id == -1) {
      grid.Destroy();
      return false;
    }
    pIcons->RemoveIcon(id);
  }
  bool bDone = RefreshGrid(id);
  grid.Destroy();
  return bDone;
}

// @ 0x00f02160
void PL::f02160()
{
    Mgr_s00f0_2160* m = MGR;
    if (!m->fC || !m->f10) {
        if (g_015acb40 && m->f4) SIM->p74->f3bbd0(m->f4, 0);
        return;
    }

    Big* eso = (Big*)FUN_00eebf80(m->fC);
    void* w10 = m->f10;
    int state = (int)((void*(__thiscall*)(void*))((void**)*(void**)w10)[0x38 / 4])(w10);

    if (state == 0x771ad6a) {
        WndC* wp = (WndC*)m->f10;
        ((void(__thiscall*)(void*))((void**)wp->vtable)[0x5c / 4])(wp);
        if ((void*)wp == m->f2c) {
            GObj_s00f0_2160* sc = SIM->p74->f3e8a0(eso->h0);
            if (sc->b20 == 0) {
                *(float*)(eso->begin + m->curIdx * 0x34) = wp->f17c;
            } else {
                int n = (int)((eso->end - eso->begin) / 0x34);
                for (int i = 0; i < n; ++i)
                    *(float*)(eso->begin + i * 0x34) = wp->f17c;
            }
        } else if ((void*)wp == m->f54) {
            void** vc = *(void***)m->fC;
            Ter* t = (Ter*)((void*(__thiscall*)(void*, unsigned))vc[0x0c / 4])(m->fC, 0x74e0069);
            if (t) eso->f1e4 = wp->f_efc4c0() * (t->f16c - t->f168) + t->f168;
            Ter* r = (Ter*)FUN_00efc830(m->fC);
            if (!r) return;
            eso->f1e4 = wp->f_efc4c0() * (r->f12c - r->f128) + r->f128;
        } else if ((void*)wp == m->f58) {
            void** vc = *(void***)m->fC;
            Ter* t = (Ter*)((void*(__thiscall*)(void*, unsigned))vc[0x0c / 4])(m->fC, 0x74e0069);
            if (t) eso->f20 = wp->f_efc4c0() * (t->f174 - t->f170) + t->f170;
            Ter* r = (Ter*)FUN_00efc830(m->fC);
            if (!r) return;
            eso->f20 = wp->f_efc4c0() * (r->f134 - r->f130) + r->f130;
        }
        return;
    }

    if (state == 0x76c67df) {
        WndC* wp = (WndC*)m->f10;
        ((void(__thiscall*)(void*))((void**)wp->vtable)[0x5c / 4])(wp);
        GObj_s00f0_2160* sc = ((GObj_s00f0_2160*)pGame)->f3e8a0(eso->h0);
        if (sc->f253e0() != 0) {
            void* sub = ((void*(__thiscall*)(void*))((void**)wp->sub34.vtable)[0x2c / 4])(&wp->sub34);
            Quat4 q;
            SP_QuaternionFromDirections(&q, eso->v1e8, sub);
            eso->v1e8[0] = ((float*)sub)[0];
            eso->v1e8[1] = ((float*)sub)[1];
            eso->v1e8[2] = ((float*)sub)[2];
            float loA, loB;
            void* r = FUN_007dcb00(&loA, &loB, eso->rc1f4);
            ((RectT*)eso->rc1f4)->assign(r);
            ((WndC*)m->fC)->f_efce30(eso->v1e8, eso->rc1f4, eso->f204);
            return;
        }
        VEC30->f_c64940(wp);
        if (sc->b20 == 0) {
            char* e = eso->begin + m->curIdx * 0x34;
            bool ok;
            VEC30->check(e + 0x1c, &ok);
            if (ok) *(int*)(e + 0x30) = 2;
        } else {
            int n = (int)((eso->end - eso->begin) / 0x34);
            for (int i = 0; i < n; ++i) {
                char* e = eso->begin + i * 0x34;
                bool ok;
                VEC30->check(e + 0x1c, &ok);
                if (ok) *(int*)(e + 0x30) = 2;
            }
        }
        return;
    }

    if (state == 0x7a81824) {
        WndC* wp = (WndC*)m->f10;
        ((void(__thiscall*)(void*))((void**)wp->vtable)[0x5c / 4])(wp);
        if ((void*)wp == m->f14) {
            eso->rc1f4[0] = wp->f1a4; eso->rc1f4[1] = wp->f1a8;
            eso->rc1f4[2] = wp->f1ac; eso->rc1f4[3] = wp->f1b0;
            ((WndC*)m->fC)->f_efce30(eso->v1e8, eso->rc1f4, eso->f204);
        } else {
            eso->rc10[0] = wp->f1a4; eso->rc10[1] = wp->f1a8;
            eso->rc10[2] = wp->f1ac; eso->rc10[3] = wp->f1b0;
        }
        ((GObj_s00f0_2160*)pGame)->f3da90(eso, 0);
        if (g_015acb40) FUN_00eee760(eso, &MGR->vec8c);
        char chk = ((PL*)g_15ad328)->CheckObject(m->fC);
        SIM->p74->f3bbd0(m->fC, chk == 0);
        return;
    }

    if (state == 0x7abdd8d) {
        WndC* wp = (WndC*)m->f10;
        ((void(__thiscall*)(void*))((void**)wp->vtable)[0x5c / 4])(wp);
        eso->rc10[0] = wp->f198; eso->rc10[1] = wp->f19c;
        eso->rc10[2] = wp->f1a0; eso->rc10[3] = wp->f1a4;
        ((GObj_s00f0_2160*)pGame)->f3da90(eso, 0);
        char chk = ((PL*)g_15ad328)->CheckObject(m->fC);
        SIM->p74->f3bbd0(m->fC, chk == 0);
        return;
    }
}

// @ 0x00f02670
void PL::f02670()
{
    void* sim = g_Simulator;
    *(void**)((char*)this + 8) = sim ? *(void**)((char*)sim + 0x18) : 0;
    void** vt = *(void***)this;
    ((void(__thiscall*)(void*, int))vt[0x18 / 4])(this, 0);
    b5 = 0;
    b6 = 0;
    b7 = 0;
    V4_s00f0_2160 tmp;
    V4_s00f0_2160* t = (V4_s00f0_2160*)FUN_00f31fd0(&tmp, 0);
    V4_s00f0_2160* dst = pC;
    void* old = dst->p0;
    void* nw = t->p0;
    if (nw != old) {
        if (nw) ((Ref*)nw)->v0();
        dst->p0 = nw;
        if (old) ((Ref*)old)->v4();
    }
    dst->f4 = t->f4;
    dst->f8 = t->f8;
    dst->fC = t->fC;
    if (t->p0) ((Ref*)t->p0)->v4();
}

// @ 0x00f02700
void PL::f02700()
{
    void* fC = MGR->fC;
    void* it = FUN_00b18e00(fC);
    FUN_00eebf80(fC);

    Plane4 plane;
    plane.build();                       // 0x00efd8e0

    void* app = FUN_0067dd10();
    V3 a, b;
    ((void(__thiscall*)(void*, V3*, V3*))((void**)app)[0x58 / 4])(app, &a, &b);
    FUN_007c4900(&a, &b);
    a.x += plane.x; a.y += plane.y; a.z += plane.z;

    void* pm = FUN_00b3d350_s00f0_2160();
    V3* res = ((PM*)pm)->f_b82110(&plane, &a, &b);
    if (res->x == g_f16c7b98 && res->y == g_f16c7b9c && res->z == g_f16c7ba0)
        return;

    V3 target = *res;
    V3* pFrom = (V3*)((void*(__thiscall*)(void*))((void**)it)[0x2c / 4])(it);   // slot 0x2c
    V3 from = *pFrom;
    Quat4* pw = (Quat4*)((void*(__thiscall*)(void*))((void**)it)[0x30 / 4])(it); // slot 0x30
    Quat4 q;
    SP_QuaternionFromDirections(&q, &from, &target);

    float t0 = pw->z * q.y - pw->y * q.z;
    float t1 = q.z * pw->x - pw->z * q.x;
    float t2 = pw->y * q.x - q.y * pw->x;
    float nx = (q.w * pw->x + pw->w * q.x) + t0;
    float ny = (q.w * pw->y + pw->w * q.y) + t1;
    float nz = (q.w * pw->z + pw->w * q.z) + t2;
    float nw = pw->w * q.w - ((pw->z * q.z + pw->y * q.y) + pw->x * q.x);
    float inv = 1.0f / sqrtf(ny * ny + (nz * nz + (nx * nx + nw * nw)));
    Quat4 norm;
    norm.x = inv * nx; norm.y = inv * ny; norm.z = inv * nz; norm.w = inv * nw;

    ((void(__thiscall*)(void*, V3*))((void**)it)[0x38 / 4])(it, &target);     // slot 0x38
    ((void(__thiscall*)(void*, Quat4*))((void**)it)[0x3c / 4])(it, &norm);    // slot 0x3c
}

// @ 0x00f02a10
int PL::f02a10(int msg, int, float c)
{
    void* f4 = MGR->f4;
    switch (msg) {
    case 0:
        if (MGR->f10 == 0) {
            if (MGR->fC != 0) ClearObject();
        } else {
            MsgTeardown();
        }
        MGR->f68 = 0;
        ((void(__thiscall*)(PL*, int))((void**)vtable)[0x18 / 4])(this, 0);
        b6 = 0;
        return 1;
    case 1:
        if (b4 != 0 && MGR->fC == 0) {
            if (MGR->f10 != 0) { SetObjectEx(f4); return 1; }
            CommitObject(f4);
            return 1;
        }
        return 0;
    case 6:
        AdjustPlacement(f4, c);
        return 1;
    case 0xb:
        if (b4 != 0) return (int)(unsigned char)UpdatePlacement(f4);
        return 0;
    default:
        return 1;
    }
}

// @ 0x00f02b00
void PL::f02b00()
{
    void** vt = *(void***)this;
    if (!((bool(__thiscall*)(void*))vt[0x38 / 4])(this)) return;
    void* a = FUN_0067dd10();
    void** va = *(void***)a;
    void* b = ((void*(__thiscall*)(void*))va[0x50 / 4])(a);
    void** vb = *(void***)b;
    void* c = ((void*(__thiscall*)(void*))vb[0x38 / 4])(b);
    if (c) {
        void** vc = *(void***)c;
        void* d = ((void*(__thiscall*)(void*, int))vc[0x0c / 4])(c, 0x11966ed);
        if (d) {
            if (*(uint8_t*)((char*)d + 0x319) == 0) return;
        }
    }
    if (*(int*)((char*)g_mgr + 0x10) != 0) { f00f80_ext(); f_eff0c0_ext(); return; }
    if (*(int*)((char*)g_mgr + 0xc) != 0) { f02700(); f_eff0c0_ext(); return; }
    if (b5) f00f80_ext();
    f_eff0c0_ext();
}

// @ 0x00f02b80
PL* PL::f02b80()
{
    char* s = (char*)this;
    *(int*)(s + 0x00) = 0;
    *(int*)(s + 0x04) = 0;
    *(int*)(s + 0x08) = 0;
    *(int*)(s + 0x0c) = 0;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x2c) = 0;
    *(int*)(s + 0x34) = 0;
    *(int*)(s + 0x38) = 0;
    *(int*)(s + 0x3c) = 0;
    *(int*)(s + 0x54) = 0;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x5c) = 0;
    *(int*)(s + 0x60) = 0;
    *(int*)(s + 0x8c) = 0;
    *(int*)(s + 0x90) = 0;
    *(int*)(s + 0x94) = 0;
    SW* sw = (SW*)(s + 0xb0);
    *(uint8_t*)(s + 0xa5) = 1;
    *(int*)(s + 0xa8) = 0;
    *(int*)(s + 0xac) = 0;
    sw->ctor(4, 0);
    sw->SetTimeLimit(0, 0);
    return this;
}

// @ 0x00f02c50
void PL::f02c50()
{
    void** vt = *(void***)this;
    if (!((bool(__thiscall*)(void*))vt[0x38 / 4])(this)) return;
    void* a = FUN_0067dd10();
    void** va = *(void***)a;
    void* b = ((void*(__thiscall*)(void*))va[0x50 / 4])(a);
    void** vb = *(void***)b;
    void* c = ((void*(__thiscall*)(void*))vb[0x38 / 4])(b);
    if (c) {
        void** vc = *(void***)c;
        void* d = ((void*(__thiscall*)(void*, int))vc[0x0c / 4])(c, 0x11966ed);
        if (d && *(uint8_t*)((char*)d + 0x319) == 0) return;
    }
    if (*(int*)((char*)g_mgr + 0x10) != 0) { f02160(); f_efd020_ext(); return; }
    if (*(int*)((char*)g_mgr + 0xc) != 0) { f01c20_ext(); }
    f_efd020_ext();
}

// @ 0x00f02cd0
PL* PL::ctor_2cd0()
{
    PL* self = this;
    *(void**)self = g_vtbl_148b708;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    void* m = operator_new6(0x10, (const char*)0x148b76c, 0, 0, 0, 0);
    if (m) {
        void* v = FUN_00f31fd0(m, 0);
        *(void**)((char*)self + 0xc) = v;
    } else {
        *(void**)((char*)self + 0xc) = 0;
    }
    self->f02670();
    return self;
}

// @ 0x00f02d30
PL* PL::f02d30(int flag)
{
    V4_s00f0_2160* p = pC;
    vtable = g_vtbl_148b708;
    if (p) {
        void* o = p->p0;
        if (o) ((Ref*)o)->v4();
        operator_delete_(p);
    }
    *(void**)((char*)this + 0xc) = 0;
    if (flag & 1) operator_delete_(this);
    return this;
}

// @ 0x00f02dd0
void __cdecl destroy_global_2dd0()
{
    X* p = (X*)g_mgr;
    if (p) {
        p->run();
        operator_delete_(p);
    }
    g_mgr = 0;
}

// @ 0x00f02e00
void PL::f02e00()
{
    if (!g_mgr) return;
    Big* obj = (Big*)FUN_00eebf80(MGR->f4);
    if (!obj) return;
    GObj_s00f0_2160* scene = (GObj_s00f0_2160*)((GObj_s00f0_2160*)pGame)->f3e8a0(obj->h0);

    WndC* wf8 = (WndC*)MGR->f8;
    if (wf8) {
        void* w = ((void*(__thiscall*)(void*, unsigned))((void**)wf8->vtable)[0x0c / 4])(wf8, 0x76c67df);
        if (w && w != MGR->f28) {
            if (!VEC30->f_c68250(w)) return;
            (*(GObj_s00f0_2160*)pGame).f45970();
            if (scene->b20 == 0) {
                char* e = obj->begin + MGR->curIdx * 0x34;
                bool ok;
                VEC30->check(e + 0x1c, &ok);
                if (ok) *(int*)(e + 0x30) = 2;
            } else {
                int n = (int)((obj->end - obj->begin) / 0x34);
                for (int i = 0; i < n; ++i) {
                    char* e = obj->begin + i * 0x34;
                    bool ok;
                    VEC30->check(e + 0x1c, &ok);
                    if (ok) *(int*)(e + 0x30) = 2;
                }
            }
            (*(GObj_s00f0_2160*)pGame).f45a80();
            if (MGR->f10 == MGR->f8 && MGR->f10) {
                void* p = MGR->f10;
                MGR->f10 = 0;
                (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
            }
            if (MGR->f8) {
                void* p = MGR->f8;
                MGR->f8 = 0;
                (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
            }
            return;
        }
    }

    (*(GObj_s00f0_2160*)pGame).f45970();
    VecBox local;
    local.fromVec(&MGR->vec8c);
    ((void(__thiscall*)(PL*, int))((void**)vtable)[0x20 / 4])(this, 0);
    (*(GObj_s00f0_2160*)pGame).f42a00(obj);
    if (g_015acb40) FUN_00eec940(&local, 0);
    FUN_00eef4b0(&local);
    (*(GObj_s00f0_2160*)pGame).f414b0();
    (*(GObj_s00f0_2160*)pGame).f45a80();
    if (local.begin && ((int*)local.begin)[-1]) operator_delete_(local.begin);
}

// @ 0x00f03010
void PL::f03010()
{
    Big* b = (Big*)pC;
    vtable = g_vtbl_148b788;
    if (b) {
        if (b->p20c && b->p20c[-1]) operator_delete_(b->p20c);
        ((Vec*)&b->begin)->destroy(b->begin, b->end);
        if (b->begin && ((int*)b->begin)[-1]) operator_delete_(b->begin);
        operator_delete_(b);
    }
    pC = 0;
}

// @ 0x00f030a0
void PL::f030a0()
{
    if (!g_mgr) return;
    Big* obj = (Big*)FUN_00eebf80(MGR->f4);
    if (!obj) return;
    (*(GObj_s00f0_2160*)pGame).f45970();

    VecBox local;
    int n = (int)(((char*)MGR->vec8c.end - (char*)MGR->vec8c.begin) >> 5);
    local.build(n, &MGR->vec8c.f0c);
    FUN_00f01140(&local, MGR->vec8c.begin, MGR->vec8c.end,
                 (int)local.end, (int)local.begin);
    local.cap = local.begin;
    ((Big*)pC)->assign(obj);

    ((void(__thiscall*)(PL*, int))((void**)vtable)[0x20 / 4])(this, 0);
    (*(GObj_s00f0_2160*)pGame).f42a00(obj);
    if (g_015acb40) FUN_00eec940(&local, 0);
    FUN_00eef4b0(&local);
    (*(GObj_s00f0_2160*)pGame).f414b0();
    (*(GObj_s00f0_2160*)pGame).f45a80();
    if (local.begin && ((int*)local.begin)[-1]) operator_delete_(local.begin);
}

// @ 0x00f031a0
void PL_s00f0_31a0::f031a0()
{
    if (g_mgr) {
        Big_s00f0_31a0* o = (Big_s00f0_31a0*)FUN_00eebf80(*(void**)((char*)g_mgr + 4));
        if (o)
            pC->assign(o);
    }
}

// @ 0x00f031d0
void PL_s00f0_31a0::f031d0()
{
    Big_s00f0_31a0* o = (Big_s00f0_31a0*)FUN_00eebf80(*(void**)((char*)g_mgr + 4));
    if (o) {
        Big_s00f0_31a0 tmp;
        tmp.copyFrom(o);
        pGame->InitThing();
        void* v = pGame->GetAt(&tmp);
        void* w = FUN_00eec0d0(v);
        void** slot = (void**)((char*)vtable + 0x20);
        (*(void (__thiscall**)(PL_s00f0_31a0*, void*))slot)(this, w);

        if (tmp.p20c && tmp.p20c[-1])
            operator_delete_(tmp.p20c);
        ((Vec*)&tmp.begin)->destroy(tmp.begin, tmp.end);
        if (tmp.begin && ((int*)tmp.begin)[-1])
            operator_delete_(tmp.begin);
    } else {
        pGame->InitThing();
    }
}

// @ 0x00f03290
void PL_s00f0_31a0::f03290()
{
    pGame = g_Simulator ? (GObj_s00f0_31a0*)*(void**)((char*)g_Simulator + 0x74) : 0;
    (*(void (__thiscall**)(PL_s00f0_31a0*, int))((char*)vtable + 0x18))(this, 0);
    b5 = 0;
    b6 = 0;
    b7 = 0;

    Big_s00f0_31a0 tmp;
    pC->assign(tmp.init());

    if (tmp.p20c && tmp.p20c[-1])
        operator_delete_(tmp.p20c);
    ((Vec*)&tmp.begin)->destroy(tmp.begin, tmp.end);
    if (tmp.begin && ((int*)tmp.begin)[-1])
        operator_delete_(tmp.begin);
}

// @ 0x00f03320
bool PL_s00f0_31a0::f03320()
{
    if (!b5) {
        if (g_015acb40 && MGR_s00f0_31a0->f4)
            pGame->f3bbd0(MGR_s00f0_31a0->f4, 1);
        return true;
    }
    ((Tut*)g_016c7b34)->f_eeff80();
    Big_s00f0_31a0* o = (Big_s00f0_31a0*)FUN_00eebf80(MGR_s00f0_31a0->f4);
    GObj_s00f0_31a0* g = (GObj_s00f0_31a0*)FUN_00eeca30(o);
    void* w = FUN_00ae66d0(g);
    if (!o) {
        b5 = 0;
        return false;
    }
    pGame->f3da90(o, 1);
    GObj_s00f0_31a0* p = (GObj_s00f0_31a0*)*(void**)((char*)g_Simulator + 0x74);
    bool notok = ((PL_s00f0_31a0*)g_15ad328)->Scenario_CheckObj(w) == 0;
    p->f3bbd0(w, notok);

    if (g->b6e) {
        FUN_00efcec0(MGR_s00f0_31a0->f4, g);
        f031d0();
        pGame->f401a0();
    } else {
        pGame->f45a80();
        pGame->f427c0();
        GObj_s00f0_31a0* q = (GObj_s00f0_31a0*)*(void**)((char*)g_Simulator + 0x18);
        q->f32880((void*)o);
        q->f347e0();
        pGame->f401a0();
    }
    b5 = 0;
    return true;
}

// @ 0x00f03440
void PL_s00f0_31a0::f03440()
{
    void* h = MGR_s00f0_31a0->fC;
    void* o = FUN_00eebf80(h);
    GObj_s00f0_31a0* g = (GObj_s00f0_31a0*)FUN_00b18e00(h);

    if (h) {
        IW* q = (IW*)((IW*)h)->v0c(0x074e0069);
        if (q) {
            *(uint8_t*)((char*)q + 0x12b) = 1;
            *(uint8_t*)((char*)q + 0x128) = 0;
            (*(void (__thiscall**)(char*, void*))((char*)*(void**)((char*)q + 0x34) + 0x3c))((char*)q + 0x34, (char*)q + 0x44);
        }
    }

    if (MGR_s00f0_31a0->f10) {
        IW* r = (IW*)((IW*)MGR_s00f0_31a0->f10)->v0c(0x076c67df);
        if (r) {
            if ((void*)r == MGR_s00f0_31a0->f28) {
                r->v64();
            } else {
                ((Vec30_s00f0_31a0*)((char*)MGR_s00f0_31a0 + 0x30))->add(r);
                Big_s00f0_31a0* b = (Big_s00f0_31a0*)FUN_00eebf80(MGR_s00f0_31a0->f4);
                GObj_s00f0_31a0* q = (GObj_s00f0_31a0*)pGame->f3e8a0(*(void**)b);
                if (*(uint8_t*)((char*)q + 0x20) == 0) {
                    bool ok;
                    ((Vec30_s00f0_31a0*)((char*)MGR_s00f0_31a0 + 0x30))->check(b->begin + MGR_s00f0_31a0->f0 * 0x34 + 0x1c, &ok);
                    if (ok)
                        *(int*)(b->begin + MGR_s00f0_31a0->f0 * 0x34 + 0x30) = 2;
                } else {
                    int n = (int)((b->end - b->begin) / 0x34);
                    for (int i = 0; i < n; ++i) {
                        char* e = b->begin + i * 0x34;
                        bool ok;
                        ((Vec30_s00f0_31a0*)((char*)MGR_s00f0_31a0 + 0x30))->check(e + 0x1c, &ok);
                        if (ok)
                            *(int*)(e + 0x30) = 2;
                    }
                }
                ((HintObj*)*(void**)((char*)g_Simulator + 0xd4))->ToggleHint(0x61, 0x62);
            }
        }
    }

    if (g) {
        if (g->b6e) {
            FUN_00efcec0(MGR_s00f0_31a0->fC, g);
            f031d0();
            pGame->f414b0();
        } else {
            pGame->f45a80();
            pGame->f414b0();
        }
    } else if (g_015acb40 && MGR_s00f0_31a0->f4) {
        pGame->f3bbd0(MGR_s00f0_31a0->f4, 1);
    }

    IW* p = (IW*)FUN_00b3d240();
    void* pvt = *(void**)p;
    void* cur = ((void* (__thiscall*)(void*))*(void**)((char*)pvt + 0x34))(p);
    if (cur != MGR_s00f0_31a0->f10) {
        GObj_s00f0_31a0* q = (GObj_s00f0_31a0*)FUN_00b18e00(MGR_s00f0_31a0->f10);
        if (q) {
            void* x = FUN_00ae66d0(q);
            ((IW*)q)->v28(0);
            if (x == MGR_s00f0_31a0->f8 && MGR_s00f0_31a0->f8) {
                void* y = MGR_s00f0_31a0->f8;
                MGR_s00f0_31a0->f8 = 0;
                (*(void (__thiscall**)(void*))((char*)*(void**)y + 4))(y);
            }
            IW* z = (IW*)((IW*)q)->vac();
            if (z)
                *(uint32_t*)((char*)z + 4) &= 0xfffffff7;
        }
    }

    if (MGR_s00f0_31a0->fC) {
        void* y = MGR_s00f0_31a0->fC;
        MGR_s00f0_31a0->fC = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)y + 4))(y);
    }
    if (MGR_s00f0_31a0->f10) {
        void* y = MGR_s00f0_31a0->f10;
        MGR_s00f0_31a0->f10 = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)y + 4))(y);
    }
}

// @ 0x00f036f0
bool PL_s00f0_31a0::f036f0()
{
    Big_s00f0_31a0* o = (Big_s00f0_31a0*)FUN_00eebf80(MGR_s00f0_31a0->fC);
    GObj_s00f0_31a0* g = (GObj_s00f0_31a0*)FUN_00b18e00(MGR_s00f0_31a0->fC);
    uint8_t b6e = g->b6e;
    if (b6e)
        FUN_00efcec0(MGR_s00f0_31a0->fC, g);

    bool bb = (b6 != 0) || (b7 != 0);
    bool result = false;
    if (b6e) {
        if (bb) {
            pGame->f42a00(o);
            pGame->f414b0();
            pGame->KillThing();
            (*(void (__thiscall**)(PL_s00f0_31a0*, int))((char*)vtable + 0x20))(this, 0);
            ((GObj_s00f0_31a0*)*(void**)((char*)g_Simulator + 0x14))->f_ed4e90();
            result = true;
            goto done_reg;
        }
        if (!MGR_s00f0_31a0->fA4) {
            f031d0();
            goto done;
        }
    }

    if (b6)
        FUN_00eef7d0(o);
    if (!pGame->ScenarioNode_Load(o))
        *(uint32_t*)((char*)o + 0x224) |= 2;
    else
        *(uint32_t*)((char*)o + 0x224) &= ~2;

    if (b6e && MGR_s00f0_31a0->fA4)
        pGame->f40370();
    else
        pGame->f414b0();

    pGame->f401a0();
    pGame->f45a80();
    pGame->f427c0();
    f_efebb0(o);
    {
        IW* q = (IW*)((IW*)g)->vb8(0x074e0069);
        if (q) {
            *(uint8_t*)((char*)q + 0x12b) = 1;
            *(uint8_t*)((char*)q + 0x128) = 0;
            (*(void (__thiscall**)(char*, void*))((char*)*(void**)((char*)q + 0x34) + 0x3c))((char*)q + 0x34, (char*)q + 0x44);
        }
    }
    {
        GObj_s00f0_31a0* q = (GObj_s00f0_31a0*)*(void**)((char*)g_Simulator + 0x18);
        q->f32880(o);
        q->f347e0();
    }

done:
    result = false;
done_reg:
    if (MGR_s00f0_31a0->fC) {
        void* y = MGR_s00f0_31a0->fC;
        MGR_s00f0_31a0->fC = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)y + 4))(y);
    }
    return result;
}

// @ 0x00f03890
int PL_s00f0_31a0::f03890(int msg, int, float c)
{
    void* f4 = MGR_s00f0_31a0->f4;
    switch (msg) {
    case 0:
        {
            bool b = false;
            if (MGR_s00f0_31a0->f10 == 0) {
                if (MGR_s00f0_31a0->fC != 0 && f036f0())
                    b = true;
            } else {
                f03440();
            }
            MGR_s00f0_31a0->f68 = 0;
            b6 = 0;
            b7 = 0;
            (*(void (__thiscall**)(PL_s00f0_31a0*, int))((char*)vtable + 0x18))(this, 0);
            if (b)
                return 2;
            return 1;
        }
    case 1:
        if (!b4)
            return 0;
        if (MGR_s00f0_31a0->f10 != 0) {
            if (MGR_s00f0_31a0->fC != 0)
                return 0;
            if (MGR_s00f0_31a0->f10 != 0) {
                f_efec90(f4);
                return 1;
            }
        }
        f_efee60(f4);
        return 1;
    case 6:
        f00610(f4, c);
        return 1;
    case 0xb:
        if (!b4)
            return 0;
        return (int)(unsigned char)f00850(f4);
    default:
        return 1;
    }
}

// @ 0x00f039a0
void __cdecl ScenarioTutorials_Teardown(char teardown)
{
    ((MgrB*)FUN_00b3d240())->f33ce0(0);
    ((MgrB*)FUN_00b3d240())->f33cf0(0);

    { void* p = MGR_s00f0_31a0->f8;  if (p) { MGR_s00f0_31a0->f8  = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } }
    { void* p = MGR_s00f0_31a0->f4;  if (p) { MGR_s00f0_31a0->f4  = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } }
    { void* p = MGR_s00f0_31a0->f10; if (p) { MGR_s00f0_31a0->f10 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } }
    { void* p = MGR_s00f0_31a0->fC;  if (p) { MGR_s00f0_31a0->fC  = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } }

    ((PL_s00f0_31a0*)g_16c7c08)->f02670();
    ((PL_s00f0_31a0*)g_15ad328)->f03290();
    FUN_00eef4b0((char*)g_mgr + 0x8c);

    { void* n = MGR_s00f0_31a0->f24; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f24) { void* p = MGR_s00f0_31a0->f24; MGR_s00f0_31a0->f24 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f18; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f18) { void* p = MGR_s00f0_31a0->f18; MGR_s00f0_31a0->f18 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f1c; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f1c) { void* p = MGR_s00f0_31a0->f1c; MGR_s00f0_31a0->f1c = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f20; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f20) { void* p = MGR_s00f0_31a0->f20; MGR_s00f0_31a0->f20 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f14; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f14) { void* p = MGR_s00f0_31a0->f14; MGR_s00f0_31a0->f14 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f28; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f28) { void* p = MGR_s00f0_31a0->f28; MGR_s00f0_31a0->f28 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f2c; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f2c) { void* p = MGR_s00f0_31a0->f2c; MGR_s00f0_31a0->f2c = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }

    ((Vec30_s00f0_31a0*)((char*)MGR_s00f0_31a0 + 0x30))->clear();

    { void* n = MGR_s00f0_31a0->f5c; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f5c) { void* p = MGR_s00f0_31a0->f5c; MGR_s00f0_31a0->f5c = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f60; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f60) { void* p = MGR_s00f0_31a0->f60; MGR_s00f0_31a0->f60 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f54; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f54) { void* p = MGR_s00f0_31a0->f54; MGR_s00f0_31a0->f54 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }
    { void* n = MGR_s00f0_31a0->f58; if (n) { ((NounMgr*)FUN_00b3d300())->RemoveNoun(n); if (MGR_s00f0_31a0->f58) { void* p = MGR_s00f0_31a0->f58; MGR_s00f0_31a0->f58 = 0; (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p); } } }

    if (teardown == 0) {
        IW* app = (IW*)FUN_0067dd10();
        IW* a = (IW*)app->v50();
        IW* b = (IW*)a->v38();
        if (b) {
            IW* c = (IW*)b->v0c(0x011966ed);
            if (c) {
                void* g = (void*)*(void**)((char*)g_Simulator + 0x74);
                void* cam = *(void**)((char*)g + 0x10);
                float* p1 = ((CamObj*)c)->f_b10260();
                *(float*)((char*)cam + 0x2c30) = p1[0];
                *(float*)((char*)cam + 0x2c34) = p1[1];
                *(float*)((char*)cam + 0x2c38) = p1[2];
                float* p2 = ((CamObj*)c)->f_644a70();
                *(float*)((char*)cam + 0x2c3c) = p2[0];
                *(float*)((char*)cam + 0x2c40) = p2[1];
                *(float*)((char*)cam + 0x2c44) = p2[2];
                *(float*)((char*)cam + 0x2c48) = p2[3];
                *(float*)((char*)cam + 0x2c4c) = ((CamObj*)c)->f_c37540();
            }
        }
    }
}

// @ 0x00f03d20
void UI_s00f0_31a0::f03d20()
{
    FUN_00809db0(this ? (void*)((char*)this + 4) : 0, g_015ad45c);
    step = 2;
}

// @ 0x00f03d50
void UI_s00f0_31a0::f03d50()
{
    FUN_00809db0(this ? (void*)((char*)this + 4) : 0, g_015ad468);
    step = 4;
}

// @ 0x00f03d80
void UI_s00f0_31a0::f03d80()
{
    RefObj* r = rcc;
    if (r) {
        r->v0c(0);
        r = rcc;
        if (r) {
            rcc = 0;
            r->v4();
        }
    }
    void* h = h14;
    if (h) {
        h14 = 0;
        EA_RemoveHandler(h, h18, h1c, h20, h24);
    }
}

// @ 0x00f03de0
void UI_s00f0_31a0::f03de0()
{
    ((int*)g_15f7cf4)[6] = f54;
    ((int*)g_15f7cf4)[7] = f64;
    FUN_00809db0(&f4, g_015ad450);
    step = 1;
}

// @ 0x00f03e20
void UI_s00f0_31a0::f03e20()
{
    IW* w = layout->FindWindowByID(0x5b5ef50, true);
    w->v7c(1, false);
}

// @ 0x00f03e40
void UI_s00f0_31a0::f03e40()
{
    char b = b79 == 0;
    b79 = b;
    w30->v7c(1, *(int*)&b);
    w34->v7c(1, b == 0);
    SPUI_UpdateMouseFocus(1);
}

// @ 0x00f03e90
void UI_s00f0_31a0::f03e90()
{
    IW* w1 = layout->FindWindowByID(0x5baefc8, true);
    SPUI_AutoSizeWindowForText(w1, 0, 0);
    IW* w2 = layout->FindWindowByID(0x5652348, true);
    SPUI_AutoSizeWindowForText(w2, 1, 0);
    IW* w3 = layout->FindWindowByID(0x5b5bd80, true);
    SPUI_AutoSizeWindowForText(w3, 1, 0);
    if (w2 && w3) {
        float* a = w2->v38();
        float* b = w3->v38();
        w3->v70(a[0] - (b[2] - b[0]), b[1]);
    }
    IW* w4 = layout->FindWindowByID(0x5650568, true);
    w4->v7c(1, true);
    IW* w5 = layout->FindWindowByID(0x5665f58, true);
    IW* o = w5 ? (IW*)w5->v0c(0x8ed27e7a) : 0;
    o->v34(4, !GetYTPrompt());
    step = 3;
}

// @ 0x00f03fa0
void UI_s00f0_31a0::f03fa0()
{
    IW* w = layout->FindWindowByID(0x5650568, true);
    w->v7c(1, false);
}

// @ 0x00f03fc0
void UI_s00f0_31a0::f03fc0(int b)
{
    IW* w = layout->FindWindowByID(0x3f67620, true);
    w->v7c(1, b);
}

// @ 0x00f03ff0
bool UI_s00f0_31a0::f03ff0(unsigned idx, V3* out, char alt)
{
    bool ok = idx < (unsigned)(vD4 - vD0);    if (ok) {
        void** base = alt ? vE4 : vD0;
        void* h = base[idx];
        V3 tmp;
        V3* r = ((Q2c*)FUN_0067dd60())->v2c(&tmp, h);
        *out = *r;
    }
    return ok;
}

// @ 0x00f04070
void UI_s00f0_31a0::f04070(char b)
{
    int raw = *(int*)&b;
    int v = 0;
    if (b)
        v = ((unsigned)(vD4 - vD0) < 0x32) ? 1 : 0;
    int arg = (raw & ~0xff) | v;
    if (w38) {
        IW* q = (IW*)w38->vf0(0x78d57d8, true);
        if (q)
            q->v7c(2, arg);
    }
    GObj_s00f0_31a0* s = (GObj_s00f0_31a0*)*(void**)((char*)g_Simulator + 0x14);
    if (s)
        s->f_ed4f00(arg);
}

// @ 0x00f040e0
void UI_s00f0_31a0::f040e0(int param)
{
    IW* w = layout->FindWindowByID(0x5650498, true);
    Str16 local;
    void* r = EA_ConvertToString16(&local, param);
    w->v80(*(void**)r);
    char* begin = (char*)local.begin;
    char* end = (char*)local.end;
    int n = (int)(end - begin) & ~1;
    if (n > 2 && begin)
        operator_delete_(begin);
}
