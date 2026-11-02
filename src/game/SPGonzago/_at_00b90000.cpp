// src/game/SPGonzago/_at_00b90000.cpp -- migrated from slice(s) s00b9f9b0, s00b9caa0, s00b9bed0, s00b981a0, s00b96180, s00b95160, s00b94150, s00b930c0, s00b91320, s00b8f230 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00b90000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl EastlNew(unsigned int size, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
extern "C" void* __cdecl PropertyManager(void);                                            // 0x0067de30
extern "C" void  __cdecl FUN_006a1250(void* src, unsigned int id, void* out);              // 0x006a1250
extern "C" void* __cdecl FUN_00401090(void* key);                                          // 0x00401090
extern "C" void* __cdecl FUN_004df440(void* mgr, void* key);                               // 0x004df440
extern "C" void* __cdecl FUN_00b1f9c0(void* item);                                         // 0x00b1f9c0
extern "C" float* __cdecl FUN_0041ea70(void* prop);                                        // 0x0041ea70
#include <intrin.h>
#include <stddef.h>
#include <math.h>
#include <xmmintrin.h>
#include "SP/cPlanetModel.h"
#include <stdlib.h>
#include "cSPTransform.h"
#include "SP/cTribe.h"
#include <string.h>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPEditorSpeciesManager.h"
#include "SP/cGameData.h"
#include <new>
#include "SP/cSpatialObject.h"

// ---- items of slice s00b8f230 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EastlNew(unsigned int size, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
extern "C" void* __cdecl PropertyManager(void);                                            // 0x0067de30
extern "C" void  __cdecl FUN_006a1250(void* src, unsigned int id, void* out);              // 0x006a1250
extern "C" void* __cdecl FUN_00401090(void* key);                                          // 0x00401090
extern "C" void* __cdecl FUN_004df440(void* mgr, void* key);                               // 0x004df440
extern "C" void* __cdecl FUN_00b1f9c0(void* item);                                         // 0x00b1f9c0
extern "C" float* __cdecl FUN_0041ea70(void* prop);                                        // 0x0041ea70
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
struct TreeNode {
  TreeNode* right;
  TreeNode* left;
  TreeNode* parent;
  int color;
  int k0;              // +0x10
  int k1;              // +0x14
  int k2;              // +0x18
  void* value;         // +0x1c
};
struct cPlantCargoInfo {
  void* vf0;                    // +0x00
  char pad0[4];
  void* vf1;                    // +0x08
  void* vf2;                    // +0x0c
  char pad1[0x70];              // +0x10 .. +0x7f
  int   f7c;                    // +0x7c
  int   f80;                    // +0x80
  int   f84;                    // +0x84
  int   f88;                    // +0x88
  int   f8c;                    // +0x8c
  float f90;                    // +0x90
  float f94;                    // +0x94
  float f98;                    // +0x98
  float f9c;                    // +0x9c
  int   fa0;                    // +0xa0
};
struct S {
  // Simulator::cPlantCargoInfo
  cPlantCargoInfo* FUN_00b8f690();                                          // 0x00b8f690
  cPlantCargoInfo* FUN_00b8f730(cPlantCargoInfo* other);                    // 0x00b8f730
  void  FUN_00b8f7f0(void** out);                                           // 0x00b8f7f0
  int   FUN_00b8f860();                                                     // 0x00b8f860
  void  FUN_00b8f9b0(int* out);                                             // 0x00b8f9b0
  char  FUN_00b8fa40(void* stream);                                         // 0x00b8fa40
  char  FUN_00b8fad0(void* stream);                                         // 0x00b8fad0
  char  FUN_00b8fb70();                                                     // 0x00b8fb70
  int   FUN_00b8fbb0(void* src);                                            // 0x00b8fbb0
  void* FUN_00b8fdd0(void** out, TreeNode* pos, int* key);                  // 0x00b8fdd0
  void  FUN_00b8ff60();                                                     // 0x00b8ff60
  void* FUN_00b8ff90();                                                     // 0x00b8ff90
  void* FUN_00b8ffd0(char del);                                             // 0x00b8ffd0
  void* FUN_00b90010(void* key);                                            // 0x00b90010
  void  FUN_00b900a0(void* speciesProfile);                                 // 0x00b900a0
  void* FUN_00b90410(void* key);                                            // 0x00b90410
};
// ---- items of slice s00b8f230 end

// ---- items of slice s00b91320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned char g_cubeAxes[];                           // @ 0x1465948: 4 bytes per face pair
struct Vec3 { float x, y, z; };
namespace SP {
int __cdecl WrapCubeFace(int n, int* face, int* x, int* y, int a, int b);  // @ 0x684ca0
}
int __cdecl CubeSpan(int n, int* abf, int radius, void* rects);    // @ 0x685450 -> rect count (stride 5 ints)
void __cdecl CubeWrap3(int n, int* face, int* x, int* y);          // @ 0x6906f0 (FUN_00b906f0)
struct Region {
  char valid;       // +0
  char face;        // +1
  short y0;         // +2
  short y1;         // +4
  short x0;         // +6
  short x1;         // +8
  short pad;        // +0xa
  int area;         // +0xc
};
struct Cell {
  Region* owner;    // +0
  unsigned int flags;  // +4
  int pad;
};
struct cCubeGrid {
  char pad0[0x24];
  int mN;                      // +0x24 cells per face edge
  char pad1[4];
  unsigned short* mHeights;    // +0x2c
  char pad2[4];
  Cell* mCells;                // +0x34
  int mStrideA;                // +0x38
  int mStrideB;                // +0x3c
  char pad3[4];
  float mScale;                // +0x44
  int mBase;                   // +0x48
  float mBias;                 // +0x4c

  bool IsCellFree(int idx, int face, int x, int y);   // @ 0xb907f0
  Cell* GetCell(int face, int x, int y);              // @ 0xb90750
  bool CheckCell(int face, int x, int y);
  void MarkSphere(const Vec3* dir, float radius, unsigned int flag);
  void GrowRegion(const int* seed, Region* r);
  float GetHeight(const int* p);
  bool GetCellDir(unsigned int mask, int face, int x, int y, Vec3* out);

  // wrap (face,x,y) onto the cube and return the cell
  Cell& CellAt(int f, int x, int y) {
    int a = f, b = x, c = y;
    do {
    } while (SP::WrapCubeFace(mN, &a, &b, &c, 0, 0));
    return mCells[(a * mN + c) * mN + b];
  }
  bool Owned(int f, int x, int y) { return CellAt(f, x, y).owner != 0; }
  bool Open(int f, int x, int y) {
    int a = f, b = x, c = y;
    do {
    } while (SP::WrapCubeFace(mN, &a, &b, &c, 0, 0));
    return IsCellFree((a * mN + c) * mN + b, a, b, c);
  }
};
struct PlanetModel {
  char pad[0x64];
  unsigned char* mFlags;  // +0x64
  int Lookup(unsigned int a);        // @ 0xb88590
  unsigned int Count(int idx);       // @ 0xb7ea00
};
PlanetModel* GetPlanetModel();  // @ 0xb3d350
// ---- items of slice s00b91320 end

// ---- items of slice s00b930c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double sqrt(double);
extern "C" void* SP_PlanetModel();                              // 0x00b3d350
extern "C" void* SP_NounManager();                              // 0x00b3d300
extern "C" void* SP_StarManager();                              // 0x00b3d2a0
extern "C" void* SP_TerraformingManager();                       // 0x00b3d430
extern "C" void* SP_PropertyManager();                          // 0x0067de30
extern "C" void* FUN_0059aed0(void* out, void* vec, void* quat); // 0x0059aed0
extern "C" void* FUN_00bd8750(void* out, void* pos);             // 0x00bd8750
extern "C" int   FUN_00ae2e40(int* self, int* stream);           // 0x00ae2e40
extern "C" int   EA_IO_WriteUint32(void* s, void* p, int n, int z); // 0x0093aa70
extern "C" int   EA_IO_StreamWrite(void* s, void* p, int n);     // 0x0093a9a0
extern "C" void  FUN_00f47380(void* p);                          // 0x00f47380
extern "C" void  SP_GetPropertyAsKey(void* obj, int key, void* out3); // 0x006a1250
extern "C" void* FUN_006bb5e0();                                 // 0x006bb5e0
extern "C" int   FUN_00b90b10(int* arr, int top, int index, int* elem,
                              float kx, float ky, float kz);      // 0x00b90b10
extern "C" char  FUN_00b931c0(void* self, int type, int id);     // 0x00b931c0
extern "C" void  FUN_00b93a90(int* arr, int top, int end, int start,
                              int* elem, float kx, float ky, float kz); // 0x00b93a90
extern "C" void  FUN_00b93cc0(int* arr, int* slot, float fx, float fy, float fz); // 0x00b93cc0
extern "C" float FUN_00b93dc0(void* self, int mode);             // 0x00b93dc0
extern "C" void  FUN_00b93f40(int pos, int self, int p3, int p4);// 0x00b93f40
extern "C" int   FUN_00b94090(void* a0, void* a1, int type, int id,
                              int unused, int* out, char load);  // 0x00b94090
extern "C" __declspec(dllimport) int __cdecl msvcr90_rand();     // 0x013cc560 imported rand
extern float DAT_01465960;      // 70.0f
extern float DAT_01465984;      // FLT_MAX
extern float DAT_014659c8;      // 55.0f
extern float DAT_01465a04;      // 0x42420000
extern float DAT_01465a08;      // 0x42832560
extern float DAT_013ec4b8;      // 1e-08f
extern float DAT_01470f1c;      // 2.0f
extern float DAT_01471064;      // 0.5f
extern float DAT_01488874;      // 0.1f
extern float DAT_013eecd8;      // 20.0f
extern float DAT_0168894c;      // direction vector base
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
struct NounManagerStub {
    void FUN_00b225d0_RemoveNoun(int noun);                             // 0x00b225d0
    int  FUN_00b21000(int type, int id);                               // 0x00b21000
    int  FUN_00b23650(int type, int id, void* o1, void* o2, void* o3);  // 0x00b23650
    int  FUN_00b20c60(int type);                                       // 0x00b20c60
};
struct StarManagerStub { int FUN_00ba6d80(u32 id); };                    // 0x00ba6d80
struct BannerStub      { char FUN_00bb9af0(int flag); };                 // 0x00bb9af0
struct TerraformStub   { int FUN_00bbe5f0(int); };                       // 0x00bbe5f0
struct Sub13C          { int FUN_00b8d8f0(); };                          // 0x00b8d8f0
struct PlayerObj       { int FUN_00ff35d0(); };                          // 0x00ff35d0
struct ArrayStub       { void FUN_00ff2d50(int index, int array); };      // 0x00ff2d50
struct PlanetModelStub {
    void* FUN_00b815a0(void* out, void* pos);                            // 0x00b815a0 ret 8
    char  FUN_00b7e3e0(void* pos);                                       // 0x00b7e3e0 ret 4
    void* FUN_00b7f250(void* out, void* pos, void* up);                  // 0x00b7f250 ret 0xc
    void* FUN_00b7f190(void* out, void* pos);                            // 0x00b7f190 ret 8
    char  FUN_00b8bb70(int handle);                                      // 0x00b8bb70 ret 4
};
struct Sub34 {
virtual int v00();
virtual int v04();
virtual int v08();
virtual int v0c();
virtual int v10();
virtual int v14();
virtual int v18();
virtual int v1c();
virtual int v20();
virtual int v24();
virtual int v28();
    virtual int v2c(float range, float* out);   // 0x2c
virtual int v30();
virtual int v34();
    virtual int v38(void* pos);                 // 0x38
    virtual int v3c(void* quat);                // 0x3c
    virtual int v40();
};
struct ElemArray {
    int* FUN_00c71000();                                                 // 0x00c71000
    int  FUN_00c710c0();                                                 // 0x00c710c0
    int  FUN_00c71030(int index);                                        // 0x00c71030 ret 4
};
struct IPos          { float* FUN_00572590(); };                         // 0x00572590
struct RandStub      { int FUN_00a68fb0(int n); };                       // 0x00a68fb0 ret 4
struct PropFloatStub { float* FUN_0041ea70(); };                         // 0x0041ea70
struct CmpStub       { char FUN_00ac0730(void* a, void* b); };           // 0x00ac0730 ret 8
typedef void (__thiscall *TCV)(void*);                                   // ret 0
typedef char (__thiscall *TCC_k2)(void*, int, void**);                   // (key, out) ret 8
typedef char (__thiscall *TCC_3v)(void*, void*, void*, void*);           // (a, b, out) ret 0xc
typedef int  (__thiscall *TCI_p)(void*, int);                            // (arg) ret 4
typedef int  (__thiscall *TCI_fp)(void*, float, void*);                  // (float, out) ret 8
typedef void (__thiscall *TCV_III)(void*, int, int, int);                // ret 0xc
extern u8    DAT_015d9c70;
struct ScenarioRecord {
    int mField0;        // +0x00
    int mField4;        // +0x04
    int mNoun;          // +0x08  noun + 0x504 is the stream target
    u8  mFlag;          // +0x0c
    u8  pad0d; u8 pad0e; u8 pad0f;
};
struct StreamAPI {
virtual int v00();
virtual int v04();
virtual int v08();
virtual int v0c();
virtual int v10();
virtual int v14();
    virtual int GetStream();                                // +0x18
    virtual int v1c();
    virtual int GetSubStream();                             // +0x20
};
extern ScenarioRecord* DAT_0168890c;    // 0x0168890c begin
extern ScenarioRecord* DAT_01688910;    // 0x01688910 end
static int RoundEven(float x)
{
    if (x >= 4194304.0f || x <= -4194304.0f)
        return (int)x;                  // |x| >= 2^22: no roundable fraction at this scale
    float m = 12582912.0f;              // 1.5 * 2^23: forces round-to-nearest-even
    x = (x + m) - m;
    return (int)x;
}
struct FloatPairCtorA {
    FloatPairCtorA* FUN_00b93810(float a, float b);
};
struct FloatPairCtorB {
    FloatPairCtorB* FUN_00b93840(float a, float b);
};
struct Weighted {
    void FUN_00b93870(int, int, int);
};
struct Float3 { float x, y, z; };
typedef char (__thiscall *TC_Char_IPtr)(void*, int, int*);
struct BucketArray {
    int* FUN_00b93980(int buckets);      // 0x00b93980 allocate
    void FUN_00b939f0(int buckets);
};
// ---- items of slice s00b930c0 end

// ---- items of slice s00b94150 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   g_169ca74;                                  // 0x169ca74
extern float g_1688890;                                  // 0x1688890  Vec3 sentinel .x
extern float g_1688894;                                  // 0x1688894  Vec3 sentinel .y
extern float g_1688898;                                  // 0x1688898  Vec3 sentinel .z
extern float g_1485720;                                  // 0x1485720  1.0f
extern char  g_1688924[];                                // 0x1688924  Matrix33 const
extern float g_1688948;                                  // 0x1688948  RandomRange hi
extern int   g_1465a0c[10];                              // 0x1465a0c  tool type ids
extern float g_1465968;                                  // 0x1465968  20.0f
namespace EA {
namespace Random {
struct RandomLinearCongruential_s00b9_4150 { double RandomDoubleUniform(); };   // 0x9360d0
}
}
extern EA::Random::RandomLinearCongruential_s00b9_4150 g_1601760;
void* __cdecl SP_CreateTribe(void*, int, int, int, int, int);   // 0xc93160
void  __cdecl operator_delete_(void*);                   // 0xf47380
float* __cdecl Matrix3FromQuaternion(void* dest, const void* quat);      // 0x59c190
char   __cdecl FUN_00b90cb0(float* pos, float r);                        // 0xb90cb0
struct Matrix33 { float m[9]; };
struct cSPTransformOps {
  char raw[0x40];
  void* Assign(const void* src);                         // 0x537dc0
};
struct cPlanetModel {
  char raw[0x400];
  float* FUN_00b7ee70(void* dest, void* src);            // 0xb7ee70
  char   FUN_00b832d0(float* pos, float v);              // 0xb832d0
  void*  FUN_00b81a40(void* dest, void* src);            // 0xb81a40
  void*  BuildSurfaceOrientation(void* dest, void* src); // 0xb7f190
  void*  BuildSurfaceOrientation2(void* out, void* pos, void* dir); // 0xb7f250
};
struct cTribeBase {
  char raw[0x200];
  void* GetToolOfType(int t);                            // 0xc8f6e0
  void  ReserveToolsSlots(int n);                        // 0xc998c0
};
struct ListProvider {
  void  GetList(void* out);                              // 0xc73520
  void* GetPtrList();                                    // 0xc71010
};
struct Range { int* begin; int* end; };                  // {begin,end} pair
struct UintArray { void* Self(); };                      // 0x572590
struct Elem {
  float* Pos();                                          // 0x6e64f0 (returns elem+4)
};
struct M3Op { void Assign(const void* src); };           // 0x41cb40
typedef void  (__thiscall *FnVoid)(void*);
typedef void* (__thiscall *FnPtr)(void*);
typedef void* (__thiscall *FnPtrI)(void*, int);
typedef void* (__thiscall *FnPtrFF)(void*, float, float);
typedef void  (__thiscall *FnVoidP)(void*, void*);
typedef void  (__thiscall *FnVoidPP)(void*, void*, void*);
typedef void  (__thiscall *FnVoidIII)(void*, int, int, void*);
static inline FnVoid   VtV(void* o, int off) { return *(FnVoid*)  (*(char**)o + off); }
static inline FnPtr    VtP(void* o, int off) { return *(FnPtr*)   (*(char**)o + off); }
static inline FnPtrI   VtPI(void* o, int off){ return *(FnPtrI*)  (*(char**)o + off); }
static inline FnVoidP  VtVP(void* o, int off){ return *(FnVoidP*) (*(char**)o + off); }
static inline FnVoidPP VtVPP(void* o, int off){return *(FnVoidPP*)(*(char**)o + off); }
static inline FnVoidIII VtVIII(void* o, int off){ return *(FnVoidIII*)(*(char**)o + off); }
static double RandomRange(double lo, double hi) {
  double range = hi - lo;
  double r = g_1601760.RandomDoubleUniform();
  double v = r * range + lo;
  if (v > hi) v = hi;
  else if (v < lo) v = lo;
  return v;
}
struct XformMsg {
  unsigned short flags;   // +0x00
  unsigned short seq;     // +0x02
  float x, y, z, w;       // +0x04
  Matrix33 mat;           // +0x14
};
struct VBaseA {
  virtual ~VBaseA() {}
  int m4;
  VBaseA() : m4(0) {}
};
struct CA : VBaseA {
  float mLo;              // +0x08
  float mHi;              // +0x0c
  CA(float lo, float hi);
  void funcAC0(int param2, unsigned short* param3, void* param4);                 // 0xb94ac0
  void funcBE0(int param2, unsigned short* param3, unsigned short* param4);       // 0xb94be0
  void funcDE0(int param2, unsigned short* param3, cSPTransformOps* param4);      // 0xb94de0
};
template <class T> struct Ref {
  T* mp;
  Ref() : mp(0) {}
  ~Ref() { if (mp && *(int*)((char*)mp - 4) != 0) operator_delete_(mp); }
};
struct VBaseB {
  virtual ~VBaseB() {}
  int m4;
  VBaseB() : m4(0) {}
};
struct CB : VBaseB {
  Ref<void>  m8;          // +0x08
  void*      mC;          // +0x0c
  void*      m10;         // +0x10
  char       pad14[8];    // +0x14
  Ref<void>  m1c;         // +0x1c
  void*      m20;         // +0x20
  void*      m24;         // +0x24
  CB();
  ~CB();
};
// ---- items of slice s00b94150 end

// ---- items of slice s00b95160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d); // 0xf473a0
extern "C" void  operator_delete(void* p);                                                    // 0xf47380
extern const char g_str_Simulator[];   // 0x13f09b4 ("Simulator")
extern void* g_allocator_13ebb38;      // 0x13ebb38 (EASTL allocator)
extern void __stdcall HeapFixdown(void* base, int i, int n, int extra);   // 0xb93a90
extern void __stdcall SwapElems(void* a, void* b);   // 0xb2af00
extern unsigned char __stdcall SP_GetPropertyAsKey(void* p); // 0x6a1250
extern void* __stdcall EA_ResourceMan_GetManager();      // 0x67dcd0
extern void* gEmptyString16;   // 0x1667bac
extern void* g_vtbl_1465a58;    // 0x1465a58
extern void* g_vtbl_13ec458;    // 0x13ec458
extern void __cdecl CopyElems16(void* srcFirst, void* srcLast, void* dst);  // 0xc7ea30
extern unsigned char __stdcall Func_ac0730(void* a, void* b);   // 0xac0730
extern void __stdcall HeapFixdown2(void* base, int a, int b, int c);  // 0xb93a90
extern void __stdcall HeapMake2(void* base, void* end, unsigned int a, unsigned int b, unsigned int c); // 0xb951d0
extern void __cdecl SwapElems2(void* a, void* b);   // 0xb2af00
extern "C" int __stdcall SP_WrapCubeFace(int face, unsigned int* a, int* b, int* c, int d, int e); // 0x684ca0
extern "C" void __stdcall SP_GridFaceTransform(int* a, int* b, int* c);                            // 0xb906f0
extern "C" unsigned int __stdcall SP_GridFaceMask(int a, int b, int c);                            // 0xb907a0
extern int g_156c084int;   // 0x156c084
extern int g_156c060;   // 0x156c060
extern void* __stdcall SP_CellRecord(int face, int x, int y);  // 0xb90750
typedef void* (__thiscall* Thiscall0)(void*);
typedef void* (__thiscall* Thiscall2)(void*, int, int);
inline void HandleAddRef(void* p)
{
    if (p) {
        void** vt = *(void***)p;
        ((Thiscall0)vt[0xbc / 4])(p);
    }
}
inline void HandleRelease(void* p)
{
    if (p) {
        void** vt = *(void***)p;
        ((Thiscall0)vt[0xc0 / 4])(p);
    }
}
struct Elem16 {
    unsigned int key;    // +0x00
    unsigned int sub;    // +0x04
    char pad[8];         // +0x08
};
struct RbNode {
    RbNode* left;      // +0x00
    RbNode* right;     // +0x04
    RbNode* parent;    // +0x08
    unsigned char color; // +0x0c
    char pad[3];
    unsigned int key;  // +0x10
};
struct ContentValidationSummarizer {
    void* vtable;          // +0x00
    char pad0[4];
    void* m8;              // +0x08
    char pad1[0x10];
    void* m1c;             // +0x1c

    void* Destroy(unsigned char freeFlag);
};
struct Vec16 {
    char* begin;   // +0x00
    char* end;     // +0x04
    char* cap;     // +0x08

    void Realloc(unsigned int n);
};
struct HashTable {
    char pad0[4];
    void** buckets;   // +0x04
    unsigned int count; // +0x08

    void Find(unsigned int* key, void** out);
};
struct RandomLCG {
    unsigned int Uniform(unsigned int n);   // 0xa68fb0 (thiscall)
};
struct TerrainGrid {
    char  pad0[0x24];
    int   m_res;          // +0x24
    char  pad1[0x0c];
    void* m_faces;        // +0x34
    char  pad2[0x14];
    float m_cellScale;    // +0x4c

    float SampleFaceUV(int* cell);                                        // 0xb917b0
    int   RingSearch(unsigned int mask, int* cell, float rmin, float rmax,
                     int f2, int f3, int f4, int f5, int lim, float* dir); // 0xb95630
    int   MarkSphere(unsigned int mask, int face, int x, int y, float* dir); // 0xb920b0
    int   CheckAngle(float* dir, int limit);                              // 0xb92280
    int   FaceDistance(int* cell, float rmin, float rmax, float f2, float f3,
                       float f4, int lim, unsigned int mask, int a, int b);// 0xb95900
};
// ---- items of slice s00b95160 end

// ---- items of slice s00b96180 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int   DAT_01688888;
extern int   DAT_01688884;
extern float DAT_01688880;
extern float DAT_0168887c;
extern char  DAT_01688890;
extern char  _sMathRandom_SP__3VRandomLinearCongruential_Random_EA__A;
extern const char kAllocFile[];
#pragma warning(disable: 4100)
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned int undefined4;
#define ROUND(x) ((int)((x) + 0.5f))
int  operator_new(int size, const char* n, int a, int b, const char* path, int line);
void operator_delete__(void*);
void RBTreeInsert(void* node, void* parent, void* header, unsigned isLeft);
int FUN_00b95340(int a, int b, void* c, undefined4 d);
int FUN_00b952e0(int a, int b, void* c, undefined4 d);
void FUN_00b3f260(int* out, int a, int b, int c, int d);
void FUN_00ac4470(int a, int b, int c);
void FUN_00ac4360(int a, int b, int c);
int  FUN_00ac2130(int a, int b, int c);
void* VectorInsert(void* dst, void* src, unsigned n);
void FUN_00edba80(void* a, int b, int c);
void* FUN_00c7ea30(int a, void* b, int c);
void DoNukeSubtree(void* node);
void cArithmeticaProgram_ctor(void* p);
void LoadArithmeticaFile(unsigned a, unsigned b, void* p);
float FUN_00b7ec50();
void FUN_007f25c0(const char* name, float v);
void FUN_007f2500();
float FUN_007f2590(const char* name);
void FUN_007f1d90();
void* FUN_00401090();
int  cTribeData_ctor(void* p, int a, int b);
void FUN_00b8ef00(int a);
unsigned RandomUint32Uniform(void* rng, unsigned n);
int  FUN_00ff34c0(float f);
int  FUN_00ff1cb0();
int  FUN_00bef920(unsigned a);
void FUN_00bfc460(int a);
int  FUN_00bebc90(int a, unsigned b);
void FUN_00ff0380(int a);
void FUN_00ff2c70(void* p);
void FUN_00b8eec0(void* p);
char FUN_00c6fe50(int a);
int  FUN_00b8d8f0(int a);
void FUN_00b3d2a0(int a);
void FUN_00ba6d80(int a);
char FUN_00bb9af0(int a);
int  FUN_00ff3440();
void* BioProtectorSort_op();
int  cGameNounManager_GetAvatar(void* mgr);
void rw_SList_SetElementSize(void* list, int a);
int  FUN_00ba9370(int a);
void FUN_00c352f0(void* p);
void FUN_00ff3190(void* p);
void VideoEncoder_Jpeg_SetWidth(void* p, int w);
int  FUN_00885c90();
int* FUN_00c71000();
int  FUN_00c71030(int i);
int  FUN_00ff0df0(void* g, int a, int b);
void FUN_00ff2d20(int a);
struct VideoEncoder_Jpeg { char pad0[0x18]; float mFramesPerSecond; };
struct S96180 { void fn(int* param_2, int* param_3); };
struct S96360 { void fn(int param_2, int param_3, int param_4, int allocator); };
struct S965d0 { unsigned fn(unsigned param_2, unsigned param_3); };
struct S96600 { void fn(undefined4* param_2, undefined4* param_3); };
struct S96710 { void fn(undefined4* param_2, undefined4* param_3); };
struct S96820 { void fn(undefined4* param_2, int param_3, uint* param_4, char param_5); };
struct S96560 { void ctorFrom(const void* src); };
struct SRBTree { void DoNuke(void* child); };
struct S96f40 { void Notify(int n); };
struct S970c0 { int fn(undefined4 param_2); };
struct S97140 { int fn(undefined4* param_2, undefined4* param_3); };
struct Vec4f { float a, b, c, d; };
struct Elem97240 { Vec4f v; char b; int i; };
struct S97240 { undefined4* fn(undefined4* param_2); };
// ---- items of slice s00b96180 end

// ---- items of slice s00b981a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
struct cRegion {               // size 0x18
    u8    mbDone;              // +0x00 (0 = dead / not a region any more)
    char  mFace;               // +0x01
    short mRowMin;             // +0x02
    short mRowMax;             // +0x04
    short mColMin;             // +0x06
    short mColMax;             // +0x08
    short pad0a;
    int   mArea;               // +0x0c
    u8    mSide[4];            // +0x10 flags OR'ed from the cells left / above / right / below
    u8    mbAnySide;           // +0x14
    u8    pad15[3];
};
struct cCell { cRegion* mpRegion; u8 mFlag; u8 pad05[3]; u32 pad08; };   // size 0xc
int __cdecl WrapCubeFace(int size, int* face, int* col, int* row, int a, int b);   // 0x684ca0
typedef char (__cdecl* RegionPred)(const cRegion*, const cRegion*);
void __cdecl SortRegions(cRegion** first, cRegion** last, RegionPred pred);        // 0xbbf6c0
void __cdecl introsort(cRegion** first, cRegion** last, int depth, RegionPred pred);   // 0xd53940
void __cdecl insertion_sort(cRegion** first, cRegion** last, RegionPred pred);     // 0xb909f0
char __cdecl RegionLess(const cRegion* a, const cRegion* b);   // 0xb90730
struct cSpotGrid {
    u32 pad00[2];
    cRegion** mpRegionBegin;    // +0x08
    cRegion** mpRegionEnd;      // +0x0c
    u32 pad10[5];
    int mnSize;                 // +0x24
    u32 pad28[3];
    cCell* mpCells;             // +0x34

    void FinishRegions();                                                  // 0xb983b0

    __forceinline cCell& CellAt(int face, int row, int col)
    {
        int f = face, r = row, c = col;
        while (WrapCubeFace(mnSize, &f, &c, &r, 0, 0))
            ;
        return mpCells[(f * mnSize + r) * mnSize + c];
    }
};
struct Entry { u32 k0, k1, v2, v3; };   // 16 bytes
struct Key   { u32 m0, m1, m2; };       // 12 bytes (EA::ResourceMan::Key)
class Node;
class ChildVector {
public:
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCap;        // +0x08
    u32    mPad0c;       // +0x0c
    u32    mPad10;       // +0x10
    u32    mSize;        // +0x14
    void*  mInline[8];   // +0x18

    void CopyFrom(const void* src);                  // 0x01011cc0
    u32  AllocFlagBefore() const { return ((const u32*)mpBegin)[-1]; }
};
struct NodeKey { u32 m0, m1; };
class Node {
public:
    union { NodeKey mKey; Node* mpFreeNext; };   // +0x00
    ChildVector mChildren;                      // +0x08
    Node* mpNext;                               // +0x40
};
struct NodeSource {
    NodeKey mKey;
    ChildVector mChildren;
};
struct InsertResult {
    Entry* mpPos;
    bool   mbInserted;
    char   mPad05[3];
};
void* operator_new(void* allocator, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
void* __cdecl FUN_00b952e0(Entry* first, Entry* last, const Entry* value, u32 flag);              // 0xb952e0
static const char kAllocFile_s00b9_81a0[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
class cSpawnTable {
public:
    Entry* mpBegin;      // +0x00
    Entry* mpEnd;        // +0x04
    Entry* mpCap;        // +0x08
    u32    mPad0c;       // +0x0c
    u32    mPad10;       // +0x10
    bool   mbFlag;       // +0x14
    u8     mPad15[7];    // +0x15
    Node*  mpFreeList;   // +0x1c
    u32    mPad20;       // +0x20
    Node*  mpPoolBegin;  // +0x24
    Node*  mpPoolEnd;    // +0x28
    void*  mpAllocator;  // +0x2c
    Node*  mpSentinel;   // +0x30

    void Realloc(u32 n);                                      // 0x00b95ef0
    Entry* InsertAt(Entry* pos, const Entry* e);              // 0x00b97140
    Entry* InsertShift(Entry* pos, const Entry* e);           // 0x00b96710
    InsertResult* Insert(InsertResult* out, const Entry* e);  // 0x00b98230
    Node* AllocNode(const NodeSource* src);                   // 0x00b98270
    void DestroyBuckets(Node** buckets, u32 count);           // 0x00b982e0
};
extern cSpawnTable g_SpawnTable;   // 0x0168890c
class HeapU32Vector {
public:
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;
    void DoInsertValue(u32* pos, const u32& value);   // 0x004558a0

    __forceinline u32  size() const  { return (u32)(mpEnd - mpBegin); }
    __forceinline u32* begin() const { return mpBegin; }

    __forceinline void push_back(const u32& value)
    {
        if (mpEnd < mpCap)
        {
            u32* p = mpEnd++;
            if (p)
                *p = value;
        }
        else
        {
            DoInsertValue(mpEnd, value);
        }
    }
};
class U32Vector {
public:
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;
    void DoInsertKey4(u32* pos, const u32& value);    // 0x00b96600

    __forceinline void push_back(const u32& value)
    {
        if (mpEnd < mpCap)
        {
            u32* p = mpEnd++;
            if (p)
                *p = value;
        }
        else
        {
            DoInsertKey4(mpEnd, value);
        }
    }
};
class cChildList {
public:
    u32 mPad00[2];          // +0x00
    HeapU32Vector mValues;  // +0x08
    u32 mPad14[2];          // +0x14
    U32Vector mObjects;     // +0x1c
    u32 mPad28[2];          // +0x28
    u32 mTotal;             // +0x30

    void Add(u32 value, u32 object);
};
struct Destroyable {
    virtual void v00();
    virtual void v01();
};
class IOStream {
public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void* GetStream();                 // +0x18
};
class IOSource {
public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual IOStream* GetStreamSource();       // +0x20
};
class cSPEditorSpeciesManager {
public:
    const void* GetProfile(const Key& key);    // 0x004df550
};
cSPEditorSpeciesManager* GetSetting9();        // 0x00401090
void __cdecl ReadInt32(void* stream, void* out, int count, int flags);   // 0x0093a780
void __cdecl ReadBool(void* stream, bool* out);                          // 0x0093ac80
void __cdecl FUN_00ae2ed0(void* obj, Key* key);                          // 0x00ae2ed0
void* __cdecl copy_705250(const void* first, const void* last, void* dst);// 0x00705250
// ---- items of slice s00b981a0 end

// ---- items of slice s00b9bed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  __cdecl FUN_00b969a0(int, int, int);   // 0xb969a0
extern "C" void __cdecl FUN_00b9bb40(int);             // 0xb9bb40
extern "C" void __cdecl FUN_00cd7d10();     // 0x00cd7d10
extern "C" void __cdecl FUN_00d3d420();     // 0x00d3d420
extern "C" void __cdecl FUN_00accbb0();     // 0x00accbb0
extern "C" void __cdecl FUN_00b1e500();     // 0x00b1e500
extern const char kNumTribesNearWater[];      // 0x01465bc8
extern const char kMinDistToNeighborTribe[];  // 0x01465bac
extern const char kMaxDistToNeighborTribe[];  // 0x01465b90
extern const char kMaxTribeLocationSlope[];   // 0x01465b74
extern const float kFloatMax;                 // 0x01465984  FLT_MAX
extern "C" int  __cdecl FUN_00b3d440();                               // 0x00b3d440
extern "C" bool __cdecl GetPropertyAsUint32Array(int list, int prop,
                                                 int* count,
                                                 unsigned** out);     // 0x006a0840
extern "C" void __cdecl PlaceSpawnDefinitionsOnPlanet(float* pos,
                                                      unsigned* ids,
                                                      int count, int a,
                                                      int b);         // 0x00b9b090
extern "C" void __cdecl PlaceArchetypeSubSpawns(float* pos,
                                                unsigned* ids,
                                                int count, int a);    // 0x00b9aa10
#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
class TObj {
public:
    int*  mBegin;    // +0x00
    int*  mEnd;      // +0x04
    void* mArr;      // +0x08
    int   m0c;       // +0x0c
    int   m10;       // +0x10
    int   m14;       // +0x14
    int   m18;       // +0x18
    void* mRef1c;    // +0x1c
    void* mRef20;    // +0x20
    int   m24;       // +0x24
    int   m28;       // +0x28
    int   m2c;       // +0x2c
    void* mSub30;    // +0x30

    void FUN_00b9c250(void);        // 0xb9c250
    void FUN_00b9c5c0(void);        // 0xb9c5c0
    void F_1023030(int, int);       // 0x1023030  eastl vector dtor-ish (thiscall, 2 args)
    void F_b9a630(void);            // 0xb9a630
};
struct Range_s00b9_bed0 { void** mpBegin; void** mpEnd; };
struct CharRange { char* mpBegin; char* mpEnd; };
typedef void (*GameDataFn)();
template<class T> struct PtrVec { T** mpBegin; T** mpEnd; };
template<class T> struct VecOut { char mPad0[4]; PtrVec<T> mVec; };
#define kTribeTypeTag ((const void*)0x018c6d19)
struct cPlanetModel_s00b9_bed0;
struct cSpawner;
struct cGameNounManager_s00b9_bed0 {
    VecOut<void>* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c,
                                    GameDataFn d, const void* tag);       // 0x00b21340
};
namespace SP {
 cGameNounManager_s00b9_bed0* __cdecl NounManager();   // 0x00b3d300
}
namespace SP {
 cPlanetModel_s00b9_bed0* __cdecl PlanetModel();   // 0x00b3d350
}
struct cPlanetModel_s00b9_bed0 {
    float* PickPoint(float* out);              // 0x00b81720
    bool   IsPointValid(const float* pos);     // 0x00b7e3e0
    int    GetContinent(const float* pos);     // 0x00b88590
};
struct cArithmeticaProgram {
    int mStorage[0x25];                        // 0x94 bytes
    void  Construct();                         // 0x007f1e60
    void  Reset();                             // 0x007f2500
    float GetVar(const char* name);            // 0x007f2590
    void  Destroy();                           // 0x007f1d90
};
extern "C" bool __cdecl LoadArithmeticaFile_s00b9_bed0(void* a, void* b,
                                            cArithmeticaProgram* prog);   // 0x007f2240
struct cSpawnHandle {
    void SetPosition(const float* pos);        // 0x00980c20
};
struct cGameData_s00b9_bed0 {
    float* GetPos();                           // 0x006e64f0
};
struct cSpawner {
    int mPad0;
    Range_s00b9_bed0* GetSpawnList();                     // 0x00c71010
    cSpawnHandle* CreateSpawn(int index);      // 0x00c71110
    int  CountSpawns();                        // 0x00c71120
    void RemoveSpawn(int index);               // 0x00c71140
};
struct Key8  { int m0; int m4; };
struct Pair8 { int m0; int m4; };
struct VecTemp {                              // eastl vector temp, 0x14 bytes
    void* mpBegin;                            // +0x00
    void* mpEnd;                              // +0x04
    void* mpCapacity;                         // +0x08
    void* mAllocName;                         // +0x0c
    void* mAllocPad;                          // +0x10
    void Assign(const VecTemp& src);          // 0x01011cc0
    void Destroy();                           // 0x00ae6970
};
struct StarTable {
    int  m00;                                 // +0x00
    int* mSlots04;                            // +0x04
    int  mIndex08;                            // +0x08
    void MakeKey(Key8* out, const int* src);                        // 0x00b95f70
    void FindRecord(const Key8* key, const Pair8* pair, int flag);  // 0x00b98dd0
    int  Find(const int* src);
};
// ---- items of slice s00b9bed0 end

// ---- items of slice s00b9caa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_1565b18[];   // path-finder grid object
extern const uint32_t g_TribeSetupLists[];   // 0x0146598c, indexed by terrain kind + 3
#pragma intrinsic(sqrt)
void operator delete[](void* p);                                     // 0x00f47380
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3 Normalized() const {
        float inv = (float)(1.0f / sqrt(x * x + y * y + z * z + 1e-08f));
        return Vector3(x * inv, y * inv, z * inv);
    }
};
template<class T> struct RefPtr {
    T* mp;
    __forceinline RefPtr() : mp(0) {}
    __forceinline ~RefPtr() { if (mp) mp->Release(); }
    __forceinline void reset() { if (mp) { T* t = mp; mp = 0; t->Release(); } }
    __forceinline T* get() const { return mp; }
    __forceinline T* operator->() const { return mp; }
};
struct Property {
    void*    mpData;   // +0x0  (array/pointer storage when mnFlags & 0x30)
    uint32_t pad04;
    int      mnCount;  // +0x8
    uint32_t pad0c;
    uint16_t mnFlags;  // +0x10
    uint16_t mnType;   // +0x12  (0xa = uint32, 0xd = float)

    uint32_t* GetUInt();   // 0x0041ea00
    float*    GetFloat();  // 0x0041ea70
};
__forceinline int PropertyItemCount(const Property* p)
{
    return (p->mnFlags & 0x30) ? p->mnCount : (p->mnType != 0);
}
__forceinline const uint32_t* PropertyItems(const Property* p)
{
    return (const uint32_t*)((p->mnFlags & 0x30) ? p->mpData : (p->mnType ? p : 0));
}
class PropertyList {
public:
    virtual int  AddRef();
    virtual int  Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // 0x1c
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);       // 0x24
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
};
typedef RefPtr<PropertyList> PropertyListPtr;
class IPropManager {
public:
    virtual int  AddRef();
    virtual int  Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);  // 0x2c
};
__forceinline bool GetPropList(IPropManager* pm, uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst)
{
    dst.reset();
    return pm->GetPropertyList(instanceID, groupID, dst);
}
__forceinline bool GetPropertyUInt(PropertyList* list, uint32_t id, uint32_t& value)
{
    Property* p;
    if (list && list->GetProperty(id, p) && p->mnType == 0xa) {
        value = *p->GetUInt();
        return true;
    }
    return false;
}
__forceinline bool GetPropertyFloat(PropertyList* list, uint32_t id, float& value)
{
    Property* p;
    if (list && list->GetProperty(id, p) && p->mnType == 0xd) {
        value = *(const float*)((p->mnFlags & 0x30) ? p->mpData : p);
        return true;
    }
    return false;
}
bool     GetFloatProperty(PropertyList* list, uint32_t id, float* out);                 // 0x0040cf10
float    GetPropertyFloatDefault(PropertyList* list, uint32_t id, float def);           // 0x004e1c70 SP::GetPropertyT<float>
uint32_t GetPropertyIntDefault(PropertyList* list, uint32_t id, uint32_t def);          // 0x00ac8fa0
class cDirectPropertyList {
public:
    bool GetBool(uint32_t id);   // 0x006a25a0
};
extern cDirectPropertyList* g_DebugProperties;   // 0x015fd918
#define VPAD4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();
class cSpatialObject {   // cGameData + 0x34
public:
    VPAD4(a) VPAD4(b)
virtual void c0();
virtual void c1();
virtual void c2();
    virtual const Vector3* GetPosition();                          // 0x2c
    VPAD4(d) VPAD4(e) VPAD4(f) VPAD4(g) VPAD4(h) VPAD4(i) VPAD4(j) VPAD4(k)
virtual void l0();
virtual void l1();
virtual void l2();
    virtual int AddRef();                                          // 0xbc
    virtual int Release();                                         // 0xc0
};
class cGameData {
public:
    virtual int   AddRef();
    virtual int   Release();
    uint32_t pad04[0xc];
    cSpatialObject mSpatial;   // +0x34
    uint32_t pad38[0x34];
    uint32_t mDefinitionID;    // +0x108
    uint32_t mNounID;          // +0x10c
    uint32_t mSubType;         // +0x110
};
struct GameDataPtrVector {
    cGameData** mpBegin;
    cGameData** mpEnd;
    cGameData** mpCapacity;
    const char* mpAllocName;
};
struct tGameDataVector {
    bool              mbDirty;   // +0x0
    GameDataPtrVector mData;     // +0x4
};
struct SpatialPtr {
    cSpatialObject* mp;
    __forceinline SpatialPtr(cSpatialObject* p) : mp(p) { if (mp) mp->AddRef(); }
    __forceinline SpatialPtr(const SpatialPtr& x) : mp(x.mp) { if (mp) mp->AddRef(); }
    __forceinline ~SpatialPtr() { if (mp) mp->Release(); }
    __forceinline cSpatialObject* operator->() const { return mp; }
};
struct SpatialPtrVector {
    SpatialPtr* mpBegin;
    SpatialPtr* mpEnd;
    SpatialPtr* mpCapacity;
    uint32_t    mAllocator;

    __forceinline SpatialPtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~SpatialPtrVector()
    {
        for (SpatialPtr* p = mpBegin; p < mpEnd; ++p)
            p->~SpatialPtr();
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
    }
    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);                                    // 0x00d01790
    void DoInsertValue(SpatialPtr* pos, const SpatialPtr& value);  // 0x00bab900
    __forceinline void push_back(const SpatialPtr& value)
    {
        if (mpEnd < mpCapacity) {
            SpatialPtr* p = mpEnd++;
            if (p) new(p) SpatialPtr(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
struct DistanceLess {
    Vector3 mPos;
    __forceinline DistanceLess(const Vector3& p) : mPos(p) {}
};
void FUN_00b95fe0(SpatialPtr* first, SpatialPtr* middle, SpatialPtr* last, DistanceLess compare);  // partial_sort
struct GridNode {
    Vector3  mPos;
    uint32_t pad[12];
};
struct GridNodeVector {
    GridNode* mpBegin;
    GridNode* mpEnd;
    GridNode* mpCapacity;
    uint32_t  mAllocator;

    __forceinline GridNodeVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~GridNodeVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
    __forceinline int size() const { return (int)(mpEnd - mpBegin); }
    GridNode* erase(GridNode* first, GridNode* last);   // 0x00ac4570
    __forceinline void clear() { erase(mpBegin, mpEnd); }
};
struct Vector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;

    void reserve(int n);                                     // 0x00473890
    void DoInsertValue(Vector3* pos, const Vector3& value);  // 0x004b5ad0
    __forceinline void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity) {
            Vector3* p = mpEnd++;
            if (p) new(p) Vector3(value);
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
struct TribePath {   // 20 bytes
    Vector3Vector mPoints;
    uint32_t      mField10;
};
TribePath* FUN_00b969a0_s00b9_caa0(TribePath* first, TribePath* last, TribePath* dest);   // eastl::copy
struct TribePathVector {
    TribePath* mpBegin;
    TribePath* mpEnd;
    TribePath* mpCapacity;

    void DestroyRange(TribePath* first, TribePath* last);   // 0x01023030
    void reserve(uint32_t n);                               // 0x00c77a00
    void push_back();                                       // 0x00b89770
    __forceinline TribePath* erase(TribePath* first, TribePath* last)
    {
        TribePath* const pNewEnd = FUN_00b969a0_s00b9_caa0(last, mpEnd, first);
        DestroyRange(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void clear() { erase(mpBegin, mpEnd); }
    __forceinline TribePath& back() { return mpEnd[-1]; }
};
class cTribeModeStrategy {
public:
    uint32_t        pad00[0xb];
    TribePathVector mPaths;    // +0x2c
    static cTribeModeStrategy* Instance();   // 0x00cd40b0
};
void FUN_00b922c0(TribePath* path, float halfWidth);   // stamp path into the planet grid
namespace eastl {
struct Link { Link* mpNext; };
}
namespace eastl {
struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    __forceinline fixed_pool_base() : mpHead(0) {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment,
              uint32_t alignmentOffset);   // 0x00921260
};
}
namespace eastl {
class fixed_pool_with_overflow : public fixed_pool_base { public:
    void*    mpPoolBegin;   // +8
    void*    mpPoolEnd;     // +0xc
    uint32_t mnNodeSize;    // +0x10
    __forceinline fixed_pool_with_overflow(void* pMemory, uint32_t memorySize, uint32_t nodeSize,
                                           uint32_t alignment, uint32_t alignmentOffset)
    {
        init(pMemory, memorySize, nodeSize, alignment, alignmentOffset);
        mpPoolBegin = pMemory;
        mpPoolEnd = (char*)pMemory + memorySize;
        mnNodeSize = nodeSize;
    }
};
}
namespace eastl {
struct fixed_node_allocator {
    fixed_pool_with_overflow mPool;
    __forceinline fixed_node_allocator(void* pNodeBuffer) : mPool(pNodeBuffer, 0xa0, 0x14, 4, 0) {}
    __forceinline fixed_node_allocator(const fixed_node_allocator& x) : mPool(x.mPool.mpHead, 0xa0, 0x14, 4, 0) {}
};
}
namespace eastl {
struct rbtree_node_base_s00b9_caa0 {
    rbtree_node_base_s00b9_caa0* mpNodeRight;
    rbtree_node_base_s00b9_caa0* mpNodeLeft;
    rbtree_node_base_s00b9_caa0* mpNodeParent;
    char              mColor;
};
}
namespace eastl {
struct rbtree_node_s00b9_caa0 : rbtree_node_base_s00b9_caa0 {
    uint32_t mValue;
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
struct insert_result {
    rbtree_node_s00b9_caa0* first;
    bool         second;
    insert_result() {}
};
}
namespace eastl {
struct less_s00b9_caa0 { };
}
namespace eastl {
struct rbtree_uint {
    less_s00b9_caa0                 mCompare;     // +0x0
    rbtree_node_base_s00b9_caa0     mAnchor;      // +0x4
    uint32_t             mnSize;       // +0x14
    fixed_node_allocator mAllocator;   // +0x18

    __forceinline rbtree_uint(const fixed_node_allocator& allocator)
        : mAnchor(), mnSize(0), mAllocator(allocator) { reset(); }
    __forceinline ~rbtree_uint() { DoNukeSubtree((rbtree_node_s00b9_caa0*)mAnchor.mpNodeParent); }
    __forceinline void reset()
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(rbtree_node_s00b9_caa0* pNode);                                           // 0x00d3b370
    insert_result DoInsertValue(const uint32_t& value, true_type);                    // 0x00b971b0
    __forceinline insert_result insert(const uint32_t& value) { return DoInsertValue(value, true_type()); }
    __forceinline rbtree_node_base_s00b9_caa0* end() { return &mAnchor; }
    __forceinline rbtree_node_base_s00b9_caa0* find(const uint32_t& key)
    {
        rbtree_node_base_s00b9_caa0* pRangeEnd = &mAnchor;
        rbtree_node_s00b9_caa0* pCurrent = (rbtree_node_s00b9_caa0*)mAnchor.mpNodeParent;
        while (pCurrent) {
            if (!(pCurrent->mValue < key)) {
                pRangeEnd = pCurrent;
                pCurrent = (rbtree_node_s00b9_caa0*)pCurrent->mpNodeLeft;
            } else {
                pCurrent = (rbtree_node_s00b9_caa0*)pCurrent->mpNodeRight;
            }
        }
        if (pRangeEnd != &mAnchor && !(key < ((rbtree_node_s00b9_caa0*)pRangeEnd)->mValue))
            return pRangeEnd;
        return &mAnchor;
    }
};
}
namespace eastl {
struct fixed_set_uint8 : rbtree_uint {
    uint32_t mBuffer[0x28];            // +0x2c (8 nodes of 0x14 bytes)
    __forceinline fixed_set_uint8() : rbtree_uint(fixed_node_allocator(mBuffer)) {}
};
}
namespace eastl {
template <class T> __forceinline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
}
struct cTerrainInfo {
    int FUN_00c75420();      // terrain kind
};
class cGameNounManager {
public:
    tGameDataVector* GetGameDataVector(void* create, void* f2, void* filter, void* f4, uint32_t typeID);  // 0x00b21340
    cTerrainInfo*    GetCurrentTerrainSphere();                                                          // 0x00f67d90
};
class cPlanetModel_s00b9_caa0 {
public:
    Vector3 FUN_00b81720();                                // default start position
    Vector3 DirectionToSurfacePosition(const Vector3& dir);   // 0x00b815a0
    uint32_t GetContinent(const Vector3& pos);             // 0x00b88590
};
struct cCubeGrid_s00b9_caa0 {
    void FUN_00b90ea0(const Vector3* pos, float a, float b, float c);   // clear marker area
    void FUN_00b90ea0(void* target, Vector3 pos);                       // same address, (target, pos) form
};
extern cCubeGrid_s00b9_caa0 g_PlanetGrid;   // 0x0156c060
struct cGameModeState {   // 0x01581208
    uint32_t Get178();    // 0x0104c100
    uint32_t Get17c();    // 0x0104bd80
};
extern cGameModeState g_GameModeState;
class cPathFinder {
public:
    bool FUN_00ac6960(void* grid, const Vector3& start, const Vector3& end, GridNodeVector* out,
                      float a, float b);
};
cGameNounManager* NounManager_s00b9_caa0();       // 0x00b3d300
IPropManager*     PropertyManager_s00b9_caa0();   // 0x0067de30
cPlanetModel_s00b9_caa0*     PlanetModel_s00b9_caa0();       // 0x00b3d350
cPathFinder*      FUN_00b3d290();
bool FUN_00b99070(Vector3* pos, bool* flag);
void FUN_00b992c0();
void FUN_00c99dc0(const Vector3* pos, uint32_t a, uint32_t b, int c);   // CreatePlayerTribe
int  FUN_00b9b090(const Vector3* pos, const uint32_t* ids, int count, uint32_t a, int b);
void FUN_00b9aa10(const Vector3* pos, const uint32_t* ids, int count, uint32_t groupID);
void FUN_00b9c830(PropertyList* list, const Vector3* pos, float radiusSq, uint32_t a, uint32_t b);
void FUN_00ace070();
struct SpawnRecord {                 // the small value kept per placed definition
    uint8_t mbFlag;                  // +0x0
    uint8_t mPad01[3];
};
struct SpawnRbtreeIterator {
    eastl::rbtree_node_base_s00b9_caa0* mpNode;
};
struct SpawnRbtreePair {
    eastl::rbtree_node_base_s00b9_caa0* first;
    bool                     second;
};
struct cSpawnTree {                                  // eastl::rbtree held by a spawn definition
    eastl::less_s00b9_caa0             mCompare;                // +0x00
    eastl::rbtree_node_base_s00b9_caa0 mAnchor;                 // +0x04
    uint32_t                mnSize;                  // +0x14
    uint32_t                mAllocator;              // +0x18 (rest of the fixed node allocator)
    SpawnRbtreeIterator find(const uint32_t& key);                          // 0x00e5c780
    SpawnRbtreePair     insert(const uint32_t& key, SpawnRecord value);     // 0x00a17a70
    __forceinline eastl::rbtree_node_base_s00b9_caa0* end() { return &mAnchor; }
};
struct cSpawnDefinition {                            // the definition record searched here
    uint32_t   mPad00[4];                            // +0x00
    bool       mbEnabled;                            // +0x10
    uint8_t    mPad11[7];                            // +0x11
    cSpawnTree mPlaced;                              // +0x18
};
class cSpawnPropertyList : public PropertyList {
public:
    uint32_t mPad04;                                 // +0x04
    uint32_t mGroupId;                               // +0x08
};
__forceinline bool GetSpawnFloat(PropertyList* list, uint32_t id, float& value)
{
    Property* p;
    if (list->GetProperty(id, p) && p->mnType == 0xd) {
        value = *p->GetFloat();
        return true;
    }
    return false;
}
// ---- items of slice s00b9caa0 end

// ---- items of slice s00b9f9b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00b9_f9b0
{
    float x, y, z;
    Vector3_s00b9_f9b0* Self();
};
struct ChildVec
{
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    unsigned size() { return (unsigned)((char*)mpEnd - (char*)mpBegin) >> 2; }
};
struct iSurfaceShape
{
    virtual void*  v00();
    virtual void*  v04();
    virtual void*  v08();
    virtual void*  v0c();
    virtual void*  v10();
    virtual void*  v14();
    virtual void*  v18();
    virtual void*  v1c();
    virtual void*  v20();
    virtual void*  v24();
    virtual void*  v28();
    virtual float* GetPosition();             // slot 0x2c
    virtual unsigned GetSurfaceID();          // slot 0x30
};
struct StarRec
{
    int            mPad0[13];   // +0x00
    iSurfaceShape* mpShape;     // +0x34
    int            mPad38[1];   // +0x38
    ChildVec       mChildren;   // +0x3c
    int            mPad44[49];  // +0x44
    int            mType;       // +0x108
    int            mPad10C;     // +0x10c
    int            mSubType;    // +0x110
};
struct StarVec
{
    StarRec** mpBegin;
    StarRec** mpEnd;
};
struct RandomLCG_s00b9_f9b0
{
    unsigned RandomUint32Uniform(unsigned a, unsigned b = 0);
};
struct StarWorld
{
    StarVec* getVec();      // 0x00c71000
    int      count();       // 0x00c710c0
    void     remove(int i); // 0x00c71150
};
extern Vector3_s00b9_f9b0 g_starPos;                       // 0x01688890
extern RandomLCG_s00b9_f9b0 g_random;                      // 0x01601760
void __cdecl FUN_00bf55d0();                    // 0x00bf55d0
void __cdecl FUN_00b9fa40();                    // 0x00b9fa40
void __cdecl FUN_00b9a4d0(void* p);             // 0x00b9a4d0
void __cdecl FUN_00b96fa0(void* p);             // 0x00b96fa0
void __cdecl FUN_00b93750(unsigned a, void* p); // 0x00b93750
// ---- items of slice s00b9f9b0 end

// @ 0x00b90010
void* S::FUN_00b90010(void* key)
{
  char* self = (char*)this;
  unsigned tmp = 0;
  char* anchor = self + 4;
  unsigned local_10 = 0;
  unsigned local_c = 0;
  unsigned local_8 = 0;
  unsigned local_4 = 0;
  void* node = 0;
  ((void (*)(void**, void*))0x00c7f560)(&node, key);   // FUN_00c7f560(&param_2, key)
  unsigned* k = (unsigned*)key;
  char* found = (char*)node;
  bool go = true;
  if (found != anchor) {
    bool lt = k[0] < *(unsigned*)(found + 0x10);
    if (k[0] == *(unsigned*)(found + 0x10) && (lt = k[2] < *(unsigned*)(found + 0x18),
                                                 k[2] == *(unsigned*)(found + 0x18)))
      lt = k[1] < *(unsigned*)(found + 0x14);
    go = lt;
  }
  if (go) {
    local_10 = k[0];
    local_c = k[1];
    local_8 = k[2];
    local_4 = 0;
    ((void* (*)(void**, void*, unsigned*, unsigned))0x00b8fdd0)(&node, found, &local_10, 0);
  }
  (void)tmp;
  return found + 0x1c;
}

// @ 0x00b900a0
void S::FUN_00b900a0(void* speciesProfile)
{
  char* self = (char*)this;
  char keybuf[0xa4];
  ((void (__thiscall*)(void*))0x00b8f690)(keybuf);   // cPlantCargoInfo ctor on local
  char* p2 = (char*)speciesProfile;
  int* src = (int*)(p2 + 0x504);
  *(void**)(keybuf + 0xa0) = p2;

  int* slotOut = 0;
  char* found = (char*)((void* (__thiscall*)(void*, void*, int**))0x00a21dc0)(self + 0x1c, src, &slotOut);
  if (*(int*)found == (int)(self + 0x20)) {
    int k0 = src[0], k1 = src[1], k2 = src[2];
    ((void (__thiscall*)(void*, int*))0x004da3a0)(&k0, &k0);   // ResourceManager(key)
    void* prop = PropertyManager();
    void* local_obj = 0;
    ((void (*)(void*, unsigned, void**))VFn(prop, 0x2c))(prop, (*(unsigned*)(p2 + 0x50c) & 0xffff62ffu) | 0x6200u, &local_obj);
    if (local_obj != 0) {
      unsigned v = 0;
      FUN_006a1250(local_obj, 0xf9efbb, &v);
      *(int*)(keybuf + 0x7c) = (v != 0x2ebcd6a6u) ? (int)v : 0;
      FUN_006a1250(local_obj, 0xf9efbc, &v);
      *(int*)(keybuf + 0x80) = (v != 0x2ebcd6a6u) ? (int)v : 0;
      FUN_006a1250(local_obj, 0xf9efbd, &v);
      *(int*)(keybuf + 0x84) = (v != 0x2ebcd6a6u) ? (int)v : 0;
      FUN_006a1250(local_obj, 0xf9efbe, &v);
      *(int*)(keybuf + 0x88) = (v != 0x2ebcd6a6u) ? (int)v : 0;
      FUN_006a1250(local_obj, 0x279a9c8, &v);
      *(int*)(keybuf + 0x8c) = (v != 0x2ebcd6a6u) ? (int)v : 0;
      if (local_obj != 0) {
        unsigned propOut = 0;
        char c1 = ((char (*)(void*, unsigned, unsigned*))VFn(local_obj, 0x24))(local_obj, 0x4057881, &propOut);
        if (c1 && *(short*)(propOut + 0x12) == 0xd) {
          float* f = FUN_0041ea70((void*)propOut);
          *(float*)(keybuf + 0x90) = *f;
        }
        if (local_obj != 0) {
          char c2 = ((char (*)(void*, unsigned, unsigned*))VFn(local_obj, 0x24))(local_obj, 0x254cf89, &propOut);
          if (c2 && *(short*)(propOut + 0x12) == 0xd) {
            float* f = FUN_0041ea70((void*)propOut);
            *(float*)(keybuf + 0x94) = *f;
          }
          if (local_obj != 0) {
            char c3 = ((char (*)(void*, unsigned, unsigned*))VFn(local_obj, 0x24))(local_obj, 0x254cf8f, &propOut);
            if (c3 && *(short*)(propOut + 0x12) == 0xd) {
              float* f = FUN_0041ea70((void*)propOut);
              *(float*)(keybuf + 0x98) = *f;
            }
            if (local_obj != 0) {
              char c4 = ((char (*)(void*, unsigned, unsigned*))VFn(local_obj, 0x24))(local_obj, 0x254cf97, &propOut);
              if (c4 && *(short*)(propOut + 0x12) == 0xd) {
                float* f = FUN_0041ea70((void*)propOut);
                *(float*)(keybuf + 0x9c) = *f;
              }
            }
          }
        }
      }
    }
    *(int*)(keybuf + 0x00) = src[0];
    *(int*)(keybuf + 0x04) = src[1];
    *(int*)(keybuf + 0x08) = src[2];

    char* pc = (char*)EastlNew(0xa4, "Simulator/cPlantCargoInfo", 0, 0, 0, 0);
    if (pc != 0) {
      ((void (__thiscall*)(void*))0x00c87660)(pc);
      *(void**)(pc + 0x00) = (void*)0x01465798;
      *(void**)(pc + 0x08) = (void*)0x01465790;
      *(void**)(pc + 0x0c) = (void*)0x0146576c;
      ((cPlantCargoInfo* (__thiscall*)(void*, void*))0x00b8f730)(pc, keybuf);
    } else {
      pc = 0;
    }
    void* id = FUN_00b1f9c0(keybuf);
    int* slot = (int*)FUN_00b90010(id);
    void* oldv = (void*)*slot;
    if (pc != oldv) {
      if (pc != 0) ((void (*)(void*))VFn(pc, 0x04))(pc);
      *slot = (int)pc;
      if (oldv != 0) ((void (*)(void*))VFn(oldv, 0x08))(oldv);
    }
    if (local_obj != 0) ((void (*)(void*))VFn(local_obj, 0x04))(local_obj);
  }
  *(void**)(keybuf + 0x00) = (void*)0x01465798;
  *(void**)(keybuf + 0x08) = (void*)0x01465790;
  *(void**)(keybuf + 0x0c) = (void*)0x0146576c;
  ((void (__thiscall*)(void*))0x00c87770)(keybuf);
}

// @ 0x00b90410
void* S::FUN_00b90410(void* key)
{
  char* self = (char*)this;
  int* slotOut = 0;
  char* found = (char*)((void* (__thiscall*)(void*, void*, int**))0x00a21dc0)(self + 0x1c, key, &slotOut);
  int v = *(int*)found;
  char* end = self + 0x20;
  for (;;) {
    if ((char*)v != end) return *(void**)(v + 0x1c);
    if (*(char*)(self + 0x38) == 0) return 0;
    void* mgr = FUN_00401090(key);
    void* prof = FUN_004df440(mgr, key);
    if (prof == 0) return 0;
    ((void (__thiscall*)(void*, void*))0x00b900a0)(this, prof);
    found = (char*)((void* (__thiscall*)(void*, void*, int**))0x00a21dc0)(self + 0x1c, key, &slotOut);
    v = *(int*)found;
  }
}

// @ 0x00b91320
void cCubeGrid::MarkSphere(const Vec3* dir, float radius, unsigned int flag)
{
  Vec3 v = *dir;
  float len = (float)sqrt((v.z * v.z + v.y * v.y) + v.x * v.x);
  if (len > 1.5258789e-05f && radius >= 1.5258789e-05f) {
    int n = mN;
    float inv = 1.0f / len;
    v.x = v.x * inv;
    float ax = (float)fabs(v.x);
    v.y = v.y * inv;
    v.z = v.z * inv;
    float ay = (float)fabs(v.y);
    float r2 = (inv * radius) * (inv * radius);
    float az = (float)fabs(v.z);
    float half = (float)n * 0.5f;
    float x = v.x, y = v.y, z = v.z;
    int seed[3];  // x, y, face
    if (az < ax || az < ay) {
      if (ay < ax) {
        seed[0] = (int)((y / x + 1.0f) * half);
        seed[1] = (int)((z / ax + 1.0f) * half);
        seed[2] = (x < 0.0f) ? 3 : 2;
      } else {
        seed[0] = (int)((z / y + 1.0f) * half);
        seed[1] = (int)((x / ay + 1.0f) * half);
        seed[2] = (y < 0.0f) ? 5 : 4;
      }
    } else {
      seed[0] = (int)((x / z + 1.0f) * half);
      seed[1] = (int)((y / az + 1.0f) * half);
      seed[2] = (z < 0.0f) ? 1 : 0;
    }
    if (seed[0] == n) seed[0]--;
    if (seed[1] == n) seed[1]--;
    float span = ((float)n * inv) * radius;
    int ispan = _mm_cvtss_si32(_mm_set_ss(span));
    if ((float)ispan < span) ispan++;
    struct Rect { int face, a0, b0, a1, b1; } rects[6];
    int count = CubeSpan(mN, seed, ispan, rects);
    unsigned int mask = flag | 7;
    for (int i = 0; i < count; i++) {
      unsigned int face = rects[i].face;
      for (int b = rects[i].b0; b < rects[i].b1; b++) {
        for (int a = rects[i].a0; a < rects[i].a1; a++) {
          unsigned int* pf = &mCells[(mN * face + b) * mN + a].flags;
          unsigned int f = *pf;
          if ((mask & f) == 0) {
            float fb = (((float)b + 0.5f) * (1.0f / (float)mN)) * 2.0f - 1.0f;
            float fa = (((float)a + 0.5f) * (1.0f / (float)mN)) * 2.0f - 1.0f;
            const unsigned char* t = &g_cubeAxes[((int)face >> 1) * 4];
            float nrm = 1.0f / (float)sqrt((fa * fa + fb * fb) + 1.0f);
            float s = nrm;
            if (face & 1) s = -nrm;
            float v[3];
            v[t[0]] = s * fa;
            v[t[1]] = nrm * fb;
            v[t[2]] = s;
            if (((v[2] - z) * (v[2] - z) + (v[1] - y) * (v[1] - y)) + (v[0] - x) * (v[0] - x) <= r2)
              *pf = f | flag;
          }
        }
      }
    }
  }
}

// @ 0x00b91750
bool cCubeGrid::CheckCell(int face, int x, int y)
{
  int n = mN;
  do {
  } while (SP::WrapCubeFace(n, &face, &x, &y, 0, 0));
  int m = mN;
  int idx = (m * face + y) * m + x;
  return IsCellFree(idx, face, x, y);
}

// @ 0x00b917b0
float cCubeGrid::GetHeight(const int* p)
{
  unsigned int a = (unsigned int)(mStrideA * p[0]) / (unsigned int)mN;
  unsigned int b = (unsigned int)(p[1] * mStrideB) / (unsigned int)mN;
  int idx = a + b + p[2] * mStrideB + mBase;
  int h = (int)mHeights[idx] - 0x8000;
  return ((float)h * mScale) * 3.051851e-05f + mBias;
}

// @ 0x00b91810
void cCubeGrid::GrowRegion(const int* seed, Region* r)
{
  int x0 = seed[0], y0 = seed[1], face = seed[2];
  int n = mN;
  int cur, cand;

  cur = x0;
  for (;;) {
    cand = cur - 1;
    if (Owned(face, cand, y0)) break;
    if (!Open(face, cand, y0) || cand <= x0 - 4 * n) break;
    cur = cand;
  }
  int xl = cur;

  cur = x0;
  for (;;) {
    cand = cur + 1;
    if (Owned(face, cand, y0)) break;
    if (!Open(face, cand, y0) || x0 + 4 * n <= cand) break;
    cur = cand;
  }
  int xm = (cur - xl) / 2 + xl;

  cur = y0;
  for (;;) {
    cand = cur - 1;
    if (Owned(face, xm, cand)) break;
    if (!Open(face, xm, cand) || cand <= y0 - 4 * n) break;
    cur = cand;
  }
  int yl = cur;

  cand = y0;
  for (;;) {
    cand = cand + 1;
    if (Owned(face, xm, cand)) break;
    if (!Open(face, xm, cand) || y0 + 4 * n <= cand) break;
  }
  int ym = ((cand - yl) - 1) / 2 + yl;

  bool L = true, R = true, T = true, B = true;
  int xlo = xm, xhi = xm, ylo = ym, yhi = ym;
  int iy = ym;
  int top, bot, ix;

X_TOP:
  if (L || R) {
    if (iy <= yhi) {
      bool ok;
      if (L) {
        ok = !Owned(face, xlo - 1, iy) && CheckCell(face, xlo - 1, iy);
      } else {
        ok = false;
      }
      L = L & ok;
      if (R) {
        if (!Owned(face, xhi + 1, iy) && CheckCell(face, xhi + 1, iy)) {
          iy++;
          goto X_TOP;
        }
      }
      R = false;
      iy++;
      goto X_TOP;
    }
    if (L) xlo--;
    if (R) xhi++;
  }

  top = ylo - 1;
  bot = yhi + 1;
  ix = xlo;
  for (;;) {
    if (!T && !B) goto FINAL;
    if (xhi < ix) break;
    bool ok;
    if (T) {
      ok = !Owned(face, ix, top) && Open(face, ix, top);
    } else {
      ok = false;
    }
    T = T & ok;
    if (B) {
      ok = !Owned(face, ix, bot) && Open(face, ix, bot);
    } else {
      ok = false;
    }
    B = B & ok;
    ix++;
  }
  if (T) ylo = top;
  if (B) yhi = bot;
  iy = ylo;
  if ((!T || (!L && !R)) && (!B || (!L && !R))) goto FINAL;
  goto X_TOP;

FINAL:
  r->face = (char)face;
  r->x0 = (short)xlo;
  r->valid = 1;
  r->y0 = (short)ylo;
  r->x1 = (short)xhi;
  r->y1 = (short)yhi;
  for (int y = ylo; y <= yhi; y++) {
    for (int x = xlo; x <= xhi; x++) {
      CellAt(face, x, y);           // the original wraps the coordinates twice per cell
      CellAt(face, x, y).owner = r;
    }
  }
  r->area = ((int)r->x1 - (int)r->x0 + 1) * ((int)r->y1 - (int)r->y0 + 1);
}

// @ 0x00b920b0
bool cCubeGrid::GetCellDir(unsigned int mask, int face, int x, int y, Vec3* out)
{
  int cx = x, cy = y, f = face;
  CubeWrap3(mN, &f, &cx, &cy);
  float inv = 1.0f / (float)mN;
  float fa = (((float)cx + 0.5f) * inv) * 2.0f - 1.0f;
  float fb = (((float)cy + 0.5f) * inv) * 2.0f - 1.0f;
  const unsigned char* t = &g_cubeAxes[(f >> 1) * 4];
  float nrm = 1.0f / (float)sqrt((fa * fa + fb * fb) + 1.0f);
  float s = nrm;
  if (f & 1) s = -nrm;
  Vec3 v;
  (&v.x)[t[0]] = s * fa;
  (&v.x)[t[1]] = nrm * fb;
  (&v.x)[t[2]] = s;
  unsigned int a0 = (unsigned int)(mStrideA * cx) / (unsigned int)mN;
  unsigned int b0 = (unsigned int)(mStrideB * cy) / (unsigned int)mN;
  int idx = a0 + b0 + mStrideB * f + mBase;
  int h = (int)mHeights[idx] - 0x8000;
  float height = ((float)h * mScale) * 3.051851e-05f + mBias;
  v.x = v.x * height;
  v.y = v.y * height;
  v.z = v.z * height;
  Cell* c = GetCell(face, x, y);
  *out = v;
  return (c->flags & mask) != 0;
}

// @ 0x00b92280
bool __stdcall PlanetModelIndexInRange(unsigned int a, unsigned int limit)
{
  bool r = false;
  PlanetModel* pm = GetPlanetModel();
  int idx = pm->Lookup(a);
  if (pm->mFlags[idx] == r) {
    unsigned int v = pm->Count(idx);
    if (v > limit) r = true;
  }
  return r;
}

// @ 0x00b930c0
int FUN_00b930c0(StreamAPI* self)
{
    int count = DAT_01688910 - DAT_0168890c;

    StreamAPI* a = (StreamAPI*)self->GetSubStream();
    int stream = a->GetStream();
    EA_IO_WriteUint32((void*)stream, &count, 1, 0);

    ScenarioRecord* r = DAT_0168890c;
    ScenarioRecord* end = DAT_01688910;
    while (r != end) {
        StreamAPI* w1 = (StreamAPI*)self->GetSubStream();
        int s1 = w1->GetStream();
        EA_IO_WriteUint32((void*)s1, &r->mField0, 1, 0);

        StreamAPI* w2 = (StreamAPI*)self->GetSubStream();
        int s2 = w2->GetStream();
        EA_IO_WriteUint32((void*)s2, &r->mField4, 1, 0);

        FUN_00ae2e40((int*)self, (int*)(r->mNoun + 0x504));

        StreamAPI* w3 = (StreamAPI*)self->GetSubStream();
        int s3 = w3->GetStream();
        u8 flag = (r->mFlag != 0) ? 1 : 0;
        EA_IO_StreamWrite((void*)s3, &flag, 1);

        ++r;
    }
    return 1;
}

// @ 0x00b932a0
void FUN_00b932a0(float* pos, float* outQuat, float range)
{
    float buf[3];
    float* v = (float*)FUN_0059aed0(buf, &DAT_0168894c, outQuat);
    buf[0] = v[0];
    buf[1] = v[1];
    buf[2] = v[2];

    float inv = (float)(1.0 / sqrt((double)buf[2] * buf[2] + (double)buf[0] * buf[0] +
                                   (double)buf[1] * buf[1] + DAT_013ec4b8));
    float ux = -(inv * buf[0]);
    float uy = -(inv * buf[1]);
    float hi = range * DAT_01470f1c;
    float lo = range;
    float uz = -(inv * buf[2]);

    float t;
    int iter = 0;
    do {
        t = (hi - lo) * DAT_01471064 + lo;

        buf[0] = pos[0] + ux * t;
        buf[1] = pos[1] + uy * t;
        buf[2] = pos[2] + uz * t;

        float scratch[3];
        float* r = (float*)((PlanetModelStub*)SP_PlanetModel())->FUN_00b815a0(scratch, buf);
        buf[0] = r[0];
        buf[1] = r[1];
        buf[2] = r[2];

        char ok = ((PlanetModelStub*)SP_PlanetModel())->FUN_00b7e3e0(buf);
        if (ok != 0)
            hi = t;
        else
            lo = t;
        ++iter;
    } while (DAT_01488874 <= hi - lo && iter < 12);

    float dt = t - range;
    pos[0] += ux * dt;
    pos[1] += uy * dt;
    pos[2] += uz * dt;

    float scratch[3];
    float* r = (float*)((PlanetModelStub*)SP_PlanetModel())->FUN_00b815a0(scratch, pos);
    pos[0] = r[0];
    pos[1] = r[1];
    pos[2] = r[2];

    void* up = FUN_00bd8750(scratch, pos);
    float quat[4];
    float* q = (float*)((PlanetModelStub*)SP_PlanetModel())->FUN_00b7f250(
                     quat, pos, up);
    outQuat[0] = q[0];
    outQuat[1] = q[1];
    outQuat[2] = q[2];
    outQuat[3] = q[3];

    if (range < DAT_014659c8) {
        pos[0] += ux * DAT_013eecd8;
        pos[1] += uy * DAT_013eecd8;
        pos[2] += uz * DAT_013eecd8;
    }
}

// @ 0x00b93550
int FUN_00b93550(void* arg0, char* self)
{
    int id = ((Sub13C*)(void*)*(int*)(self + 0x13c))->FUN_00b8d8f0();
    int banner = ((StarManagerStub*)SP_StarManager())->FUN_00ba6d80((u32)id);
    char have = ((BannerStub*)(void*)banner)->FUN_00bb9af0(0x100) != 0;
    int pop = ((PlayerObj*)arg0)->FUN_00ff35d0();
    int denom = 4;
    if (have != 0)
        denom = 2;
    float ratio = (float)pop / (float)denom;

    int base = 2;
    if (have == 0)
        base = ((TerraformStub*)SP_TerraformingManager())->FUN_00bbe5f0(0);

    float prod = (float)base * ratio;
    return RoundEven(prod);
}

// @ 0x00b935e0
void* FUN_00b935e0(void* out, int param_2, int param_3)
{
    int* o = (int*)out;
    o[0] = 0;
    o[1] = 0;
    *(float*)((char*)o + 8) = DAT_01465984;

    if (param_2 == 0 || param_3 == 0)
        return out;

    int* arr = ((ElemArray*)(void*)param_2)->FUN_00c71000();
    if ((u32)((arr[1] - arr[0]) >> 2) <= 1)
        return out;

    int nOuter = (*(int*)(param_3 + 0x40) - *(int*)(param_3 + 0x3c)) >> 2;
    if (nOuter <= 0)
        return out;

    for (int i = 0; i < nOuter; ++i) {
        int el = *(int*)(*(int*)(param_3 + 0x3c) + i * 4);
        int n = ((ElemArray*)(void*)param_2)->FUN_00c710c0();
        if (n <= 0)
            continue;
        for (int j = 0; j < n; ++j) {
            int obj = ((ElemArray*)(void*)param_2)->FUN_00c71030(j);
            if (obj == param_3)
                continue;
            int nElem = (*(int*)(obj + 0x40) - *(int*)(obj + 0x3c)) >> 2;
            if (nElem <= 0)
                continue;
            for (int k = 0; k < nElem; ++k) {
                int u = *(int*)(*(int*)(obj + 0x3c) + k * 4);
                float* pa = ((IPos*)(void*)u)->FUN_00572590();
                float* pb = ((IPos*)(void*)el)->FUN_00572590();
                float dy = pb[1] - pa[1];
                float dx = pb[0] - pa[0];
                float dz = pb[2] - pa[2];
                float dist = (dx * dx + dy * dy) + dz * dz;
                if (dist < *(float*)((char*)o + 8)) {
                    *(float*)((char*)o + 8) = dist;
                    o[0] = u;
                    o[1] = obj;
                }
            }
        }
    }
    return out;
}

// @ 0x00b93750
void FUN_00b93750(int count, int param_2)
{
    if (count <= 0)
        return;
    do {
        int n = ((ElemArray*)(void*)param_2)->FUN_00c710c0();
        int r = ((RandStub*)0x1601760)->FUN_00a68fb0(n);
        int arr = ((ElemArray*)(void*)param_2)->FUN_00c71030(r);
        if ((*(int*)(arr + 0x40) - *(int*)(arr + 0x3c)) & 0xfffffffc) {
            int local[3];
            FUN_00b935e0(local, param_2, arr);
            int local0 = local[0];
            int local1 = local[1];
            if (local0 != 0 && local1 != 0) {
                int n2 = (*(int*)(local1 + 0x40) - *(int*)(local1 + 0x3c)) >> 2;
                char found = 0;
                for (int i = 0; i < n2; ++i) {
                    if (found != 0)
                        break;
                    if (*(int*)(*(int*)(local1 + 0x3c) + i * 4) == local0) {
                        found = 1;
                        ((ArrayStub*)(void*)local1)->FUN_00ff2d50(i, arr);
                    }
                }
            }
        }
        --count;
    } while (count != 0);
}

// @ 0x00b93810
FloatPairCtorA* FloatPairCtorA::FUN_00b93810(float a, float b)
{
    *(float*)((char*)this + 8) = a;
    *(int*)((char*)this + 4) = 0;
    *(int*)this = 0x14659cc;
    *(float*)((char*)this + 0xc) = b;
    return this;
}

// @ 0x00b93840
FloatPairCtorB* FloatPairCtorB::FUN_00b93840(float a, float b)
{
    *(float*)((char*)this + 8) = a;
    *(int*)((char*)this + 4) = 0;
    *(int*)this = 0x14659e8;
    *(float*)((char*)this + 0xc) = b;
    return this;
}

// @ 0x00b93870
void Weighted::FUN_00b93870(int a, int b, int c)
{
    int* self = (int*)this;
    int idx = msvcr90_rand() % self[0xc];
    unsigned count = (unsigned)((self[3] - self[2]) >> 2);
    unsigned i = 0;
    _ReadWriteBarrier();
    if (count > 0) {
        int* w = (int*)self[2];
        do {
            idx -= *w;
            if (idx < 0) {
                int el = *(int*)(self[7] + i * 4);
                ((TCV_III)(*(void***)el)[0x10 / 4])((void*)el, a, b, c);
                return;
            }
            ++i;
            ++w;
        } while (i < count);
    }
}

// @ 0x00b938d0
float* FUN_00b938d0(float* out, int* prop, int mode, float fx, float fy, float fz)
{
    if (prop != 0) {
        char ok = ((TC_Char_IPtr)(*(void***)prop)[0x24 / 4])((void*)prop, mode, (int*)&prop);
        if (ok != 0) {
            int p = (int)prop;
            u16 type = *(u16*)((char*)p + 0x12);
            float* src;
            if (type == 0x31 || type == 0x10) {
                if ((*(u8*)((char*)p + 0x10) & 0x30) != 0)
                    src = *(float**)p;
                else
                    src = (float*)(type != 0 ? p : 0);
            } else {
                src = (float*)FUN_006bb5e0();
            }
            Float3* o = (Float3*)out;
            o->x = src[0];
            o->y = src[1];
            o->z = src[2];
            return out;
        }
    }
    out[0] = fx;
    out[1] = fy;
    out[2] = fz;
    return out;
}

// @ 0x00b939f0
void BucketArray::FUN_00b939f0(int param_2)
{
    int* self = (int*)this;
    int* buckets = (int*)FUN_00b93980(param_2);
    for (u32 i = 0; i < (u32)self[2]; ++i) {
        int* p = *(int**)(self[1] + i * 4);
        while (p != 0) {
            unsigned rem = (unsigned)p[0] % (unsigned)param_2;
            int* next = (int*)p[0x10];
            *(int*)(self[1] + i * 4) = (int)next;
            p[0x10] = buckets[rem];
            buckets[rem] = (int)p;
            p = *(int**)(self[1] + i * 4);
        }
    }
    int* old = (int*)self[1];
    if ((u32)self[2] > 1 && old != (int*)self[0x30 / 4]) {
        if (old < (int*)self[0x24 / 4] || old >= (int*)self[0x28 / 4]) {
            FUN_00f47380(old);
        } else {
            *old = self[0x1c / 4];
            self[0x1c / 4] = (int)old;
        }
    }
    self[1] = (int)buckets;
    self[2] = param_2;
}

// @ 0x00b93a90
void FUN_00b93a90(int* arr, int top, int end, int start, int* elem, float kx, float ky, float kz)
{
    int i = start;
    int j = i * 2 + 2;
    if (j < end) {
        do {
            if (((CmpStub*)(void*)&kx)->FUN_00ac0730((void*)arr[j], (void*)arr[j - 1]))
                --j;
            int* cur = (int*)arr[i];
            int* child = (int*)arr[j];
            if (child != cur) {
                if (child != 0)
                    ((TCV)(*(void***)child)[0xbc / 4])((void*)child);
                arr[i] = (int)child;
                if (cur != 0)
                    ((TCV)(*(void***)cur)[0xc0 / 4])((void*)cur);
            }
            i = j;
            j = i * 2 + 2;
        } while (j < end);
    }
    if (j == end) {
        int* cur = (int*)arr[i];
        int* child = (int*)arr[j - 1];
        if (child != cur) {
            if (child != 0)
                ((TCV)(*(void***)child)[0xbc / 4])((void*)child);
            arr[i] = (int)child;
            if (cur != 0)
                ((TCV)(*(void***)cur)[0xc0 / 4])((void*)cur);
        }
        i = j - 1;
    }
    if (elem != 0)
        ((TCV)(*(void***)elem)[0xbc / 4])((void*)elem);
    FUN_00b90b10(arr, top, i, elem, kx, ky, kz);
    if (elem != 0)
        ((TCV)(*(void***)elem)[0xc0 / 4])((void*)elem);
}

// @ 0x00b93ba0
int* FUN_00b93ba0(int* begin, int* end)
{
    int* p = begin;
    while (p != end) {
        int obj = *p;
        float out[3];
        void** vt = *(void***)(obj + 0x34);
        int handle = ((TCI_fp)vt[0x2c / 4])((void*)(obj + 0x34), DAT_01465960, out);
        char c = ((PlanetModelStub*)SP_PlanetModel())->FUN_00b8bb70(handle);
        if (c == 0)
            break;
        ++p;
    }
    return p;
}

// @ 0x00b93bf0
int* FUN_00b93bf0(int* begin, int* end, int* out)
{
    if (begin != end) {
        do {
            int obj = *begin;
            float tmp[3];
            int handle = ((Sub34*)(obj + 0x34))->v2c(DAT_01465960, tmp);
            char c = ((PlanetModelStub*)SP_PlanetModel())->FUN_00b8bb70(handle);
            if (c != 0) {
                *out = *begin;
                ++out;
            }
            ++begin;
        } while (begin != end);
    }
    return out;
}

// @ 0x00b93cc0
void FUN_00b93cc0(int* arr, int* slot, float fx, float fy, float fz)
{
    int* old = (int*)slot[-1];
    if (old != 0)
        ((TCV)(*(void***)old)[0xbc / 4])((void*)old);
    int* nw = (int*)*arr;
    int* prev = (int*)slot[-1];
    if (nw != prev) {
        if (nw != 0)
            ((TCV)(*(void***)nw)[0xbc / 4])((void*)nw);
        slot[-1] = (int)nw;
        if (prev != 0)
            ((TCV)(*(void***)prev)[0xc0 / 4])((void*)prev);
    }
    if (old != 0)
        ((TCV)(*(void***)old)[0xbc / 4])((void*)old);
    FUN_00b93a90(arr, 0, (int)(slot - arr) - 1, 0, old, fx, fy, fz);
    if (old != 0)
        ((TCV)(*(void***)old)[0xc0 / 4])((void*)old);
}

// @ 0x00b93dc0
extern "C" float FUN_00b93dc0(void* self, int mode)
{
    float value;
    if (mode == 0 || mode == 2)
        value = DAT_01465a04;
    else
        value = DAT_01465a08;

    int* temp = 0;
    void* pm = SP_PropertyManager();
    char ok = ((TCC_3v)(*(void***)pm)[0x2c / 4])(pm, self, (void*)0x2e4b4cc,
                                                  (void*)&temp);
    if (ok == 0) {
        if (temp != 0) {
            int* t = temp;
            temp = 0;
            ((TCV)(*(void***)t)[1])((void*)t);
        }
        return value;
    }

    int vec[3];
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
    switch (mode) {
    case 0:
        SP_GetPropertyAsKey(self, 0x44449ba, vec);
        break;
    case 1:
        SP_GetPropertyAsKey((void*)temp, 0x44449bb, vec);
        break;
    case 2:
        SP_GetPropertyAsKey((void*)temp, 0x44449bc, vec);
        break;
    case 3:
        SP_GetPropertyAsKey(self, 0x44449bd, vec);
        break;
    }
    vec[2] = 0x40828100;

    int* temp2 = 0;
    void* pm2 = SP_PropertyManager();
    char ok2 = ((TCC_3v)(*(void***)pm2)[0x2c / 4])(pm2, (void*)vec[0],
                                                    (void*)vec[2], (void*)&temp2);
    if (ok2 != 0 && temp2 != 0) {
        int* t3 = 0;
        char ok3 = ((TCC_k2)(*(void***)temp2)[0x24 / 4])(
                       (void*)temp2, 0x4408ed7, (void**)&t3);
        if (ok3 != 0 && *(u16*)((char*)t3 + 0x12) == 0xd)
            value = *((PropFloatStub*)(void*)t3)->FUN_0041ea70();
    }

    if (temp2 != 0) {
        int* t = temp2;
        temp2 = 0;
        ((TCV)(*(void***)t)[1])((void*)t);
    }
    if (temp != 0) {
        int* t = temp;
        temp = 0;
        ((TCV)(*(void***)t)[1])((void*)t);
    }
    return value;
}

// @ 0x00b93f40
extern "C" void FUN_00b93f40(int pos, int selfp, int p3, int p4)
{
    int obj = *(int*)(selfp + 0x43c);
    u8 useDefault = 0;
    if (obj != 0) {
        int got = 0;
        char ok = ((TCC_k2)(*(void***)obj)[0x24 / 4])((void*)obj, 0xa8f33541, (void**)&got);
        if (ok != 0) {
            u16 type = *(u16*)(got + 0x12);
            if (type == 1 || type == 0x10) {
                if ((*(u8*)(got + 0x10) & 0x30) != 0)
                    useDefault = *(u8*)(*(int*)got);
                else
                    useDefault = *(u8*)(type != 0 ? got : 0);
            } else {
                useDefault = DAT_015d9c70;
            }
        }
    }

    int noun = ((NounManagerStub*)SP_NounManager())->FUN_00b20c60(0x36be27e);
    int s = 0;
    if (noun != 0)
        s = ((TCI_p)(*(void***)noun)[0xc / 4])((void*)noun, 0x36be278);

    *(int*)(s + 0x11c) = 0;
    *(int*)(s + 0x120) = 0;
    *(int*)(s + 0x124) = 0;
    *(int*)(s + 0x13c) = 0;
    *(int*)(s + 0x114) = p4;
    *(int*)(s + 0x110) = p3;
    *(int*)(s + 0x128) = (useDefault == 0);
    *(int*)(s + 0x108) = 0x91fe517b;
    *(int*)(s + 0x10c) = 0x1be418e;
    *(int*)(s + 0x12c) = 0;
    *(int*)(s + 0x130) = 0;
    *(int*)(s + 0x134) = 0;
    *(int*)(s + 0x138) = 0;
    *(int*)(s + 0x140) = 5;

    ((Sub34*)(s + 0x34))->v38((void*)pos);

    float quat[4];
    ((PlanetModelStub*)SP_PlanetModel())->FUN_00b7f190(quat, (void*)pos);
    ((Sub34*)(s + 0x34))->v3c(quat);

    FUN_00b931c0((void*)s, -1, -1);
}

// @ 0x00b94090
extern "C" int FUN_00b94090(void* a0, void* a1, int type, int id, int unused, int* out, char load)
{
    int noun = ((NounManagerStub*)SP_NounManager())->FUN_00b20c60(0x36be27e);
    int s = 0;
    if (noun != 0)
        s = ((TCI_p)(*(void***)noun)[0xc / 4])((void*)noun, 0x36be278);

    *(int*)(s + 0x108) = 0;
    *(int*)(s + 0x114) = 0;
    *(int*)(s + 0x10c) = type;
    *(int*)(s + 0x110) = id;

    ((Sub34*)(s + 0x34))->v38(a0);
    ((Sub34*)(s + 0x34))->v3c(a1);

    if (type == 0x1be418e)
        *(int*)(s + 0x108) = 0x91fe517b;
    else if (type == 0x36be27e)
        *(int*)(s + 0x108) = id;

    char r = 0;
    if (load != 0) {
        if (FUN_00b931c0((void*)s, -1, -1) != 0)
            r = 1;
    }
    if (out != 0)
        *out = s;
    return r;
}

// @ 0x00b94150
void* __cdecl FUN_00b94150(void* p1, void* p2, void* p3, char p4)
{
  (void)p2; (void)p3;
  unsigned short msg[4 + 12 + 18];   // scratch for the transform message (0x38 bytes)
  (void)msg;

  SP_NounManager();
  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  void* q = *(void**)((char*)pm + 0x24);   // local_a4._4_4_

  int n = g_169ca74;
  char toolEnable[16] = {0};
  toolEnable[10] = 1;

  cTribeBase* tribe = (cTribeBase*)SP_CreateTribe(p1, 0, n, n * 10, 0, 0);

  void* prop = 0;                          // local_a4._0_4_ (smart pointer)
  if (p4 == 0) {
    void* pmgr = SP_PropertyManager();
    if (prop) {
      void* t = prop;
      prop = 0;
      (*VtV(t, 4))(t);
    }
    (*VtVIII(pmgr, 0x2c))(pmgr, 0x3bce99e9, 0x302a1c9, &prop);
    if (prop) {
      XformMsg m;
      m.flags = 0;
      m.seq = 0;
      m.x = g_1688890;
      m.y = g_1688894;
      m.z = g_1688898;
      m.w = g_1485720;
      ((M3Op*)&m.mat)->Assign(g_1688924);

      char* sub = (char*)tribe + 0x120;
      float* p = (float*)(*VtP(sub, 0x2c))(sub);
      m.x = p[0];
      m.y = p[1];
      m.z = p[2];
      m.flags |= 4;
      m.seq++;
      void* quat = (*VtP(sub, 0x30))(sub);
      float mtmp[9];
      float* mm = Matrix3FromQuaternion(mtmp, quat);
      for (int i = 0; i < 9; i++)
        ((float*)&m.mat)[i] = mm[i];
      m.flags |= 2;
      m.seq++;
      (*VtVPP(q, 0x54))(q, &m, prop);

      void* t2 = prop;
      prop = 0;
      (*VtV(t2, 4))(t2);
    }
  }

  for (unsigned off = 0; off < 0x28; off += 4) {
    int tt = g_1465a0c[off >> 2];
    if (toolEnable[tt] == 0)
      continue;
    if (tribe->GetToolOfType(tt) != 0)
      continue;
    void* tool = (*VtPI(tribe, 0xb4))(tribe, tt);
    if (tool == 0)
      continue;
    (*VtVP(tool, 0x64))(tool, tribe);

    double r0 = RandomRange(0.0, (double)g_1688948);
    double r1 = RandomRange(4.0, 10.0);
    float f1 = (float)r1;
    float f0 = (float)r0;
    char* sub = (char*)tribe + 0x120;
    void* pos = (*(FnPtrFF*)(*(char**)sub + 0x2c))(sub, f1, f0);
    char buf[0x40];
    pm->FUN_00b81a40(buf, pos);

    char* toolSub = (char*)tool + 0x34;
    (*VtVP(toolSub, 0x38))(toolSub, buf);
    void* p2 = (*VtP(toolSub, 0x2c))(toolSub);
    void* orient = pm->BuildSurfaceOrientation(buf, p2);
    (*VtVP(toolSub, 0x3c))(toolSub, orient);
  }

  tribe->ReserveToolsSlots(0);
  return tribe;
}

// @ 0x00b94420
char __cdecl FUN_00b94420(void* self, float* pos, float r1, float r2, float r3)
{
  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  float local[3];
  float* p = pm->FUN_00b7ee70(local, pos);
  float len = (float)sqrt((double)p[0] * (double)p[0] +
                          (double)p[1] * (double)p[1] +
                          (double)p[2] * (double)p[2]);

  char bl;
  if (r3 <= len)
    bl = 0;
  else if (pm->FUN_00b832d0(pos, 15.0f))
    bl = 0;
  else
    bl = pm->FUN_00b832d0(pos, 20.0f) ? 1 : 0;

  Range arr;
  ((ListProvider*)self)->GetList(&arr);
  int n = (int)(((char*)arr.end - (char*)arr.begin) >> 2);
  if (n > 0 && bl) {
    for (int i = 0; i < n; i++) {
      float* pf = (float*)((UintArray*)arr.begin[i])->Self();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        if (dx * dx + dy * dy + dz * dz > r1 * r1)
          bl = 1;
        else
          bl = 0;
      }
    }
  }

  Range* arr2 = (Range*)((ListProvider*)self)->GetPtrList();
  int n2 = (int)(((char*)arr2->end - (char*)arr2->begin) >> 2);
  if (n2 > 0 && bl) {
    for (int i = 0; i < n2; i++) {
      float* pf = ((Elem*)arr2->begin[i])->Pos();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        if (dx * dx + dy * dy + dz * dz > r2 * r2)
          bl = 1;
        else
          bl = 0;
      }
    }
  }

  if (FUN_00b90cb0(pos, g_1465968))
    bl = 0;

  if (arr.begin && *(int*)((char*)arr.begin - 4) != 0)
    operator_delete_(arr.begin);

  return bl;
}

// @ 0x00b94670
bool __cdecl FUN_00b94670(void* self, float* pos, float r1, float r2, float r3, float r4, float r5)
{
  cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
  float local[3];
  float* p = pm->FUN_00b7ee70(local, pos);
  float len = (float)sqrt((double)p[0] * (double)p[0] +
                          (double)p[1] * (double)p[1] +
                          (double)p[2] * (double)p[2]);

  char result = (len < r5) ? 1 : 0;

  Range arr;
  ((ListProvider*)self)->GetList(&arr);
  int n = (int)(((char*)arr.end - (char*)arr.begin) >> 2);
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      if (!result)
        break;
      float* pf = (float*)((UintArray*)arr.begin[i])->Self();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        if (dx * dx + dy * dy + dz * dz <= r1 * r1)
          result = 0;
        else
          result = 1;
      }
    }
  }

  char hasAny = 0;
  char outside = 0;
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      if (!result)
        break;
      float* pf = (float*)((UintArray*)arr.begin[i])->Self();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        hasAny = 1;
        if (dx * dx + dy * dy + dz * dz >= r2 * r2)
          outside = 0;
        else
          outside = 1;
      }
    }
    if (hasAny && result && !outside)
      result = 0;
  }

  Range* arr2 = (Range*)((ListProvider*)self)->GetPtrList();
  int n2 = (int)(((char*)arr2->end - (char*)arr2->begin) >> 2);
  if (n2 > 0) {
    for (int i = 0; i < n2; i++) {
      if (!result)
        break;
      float* pf = ((Elem*)arr2->begin[i])->Pos();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        if (dx * dx + dy * dy + dz * dz <= r3 * r3)
          result = 0;
      }
    }
  }

  char hasAny2 = 0;
  char outside2 = 0;
  if (n2 > 0) {
    for (int i = 0; i < n2; i++) {
      if (!result || hasAny2)
        break;
      float* pf = ((Elem*)arr2->begin[i])->Pos();
      if (pf[0] != g_1688890 || pf[1] != g_1688894 || pf[2] != g_1688898) {
        float dx = pos[0] - pf[0];
        float dy = pos[1] - pf[1];
        float dz = pos[2] - pf[2];
        hasAny2 = 1;
        if (dx * dx + dy * dy + dz * dz >= r4 * r4)
          outside2 = 0;
        else
          outside2 = 1;
      }
    }
  }

  if (FUN_00b90cb0(pos, 20.0f))
    result = 0;

  if (hasAny2 && result && !outside2)
    result = 0;

  if (arr.begin && *(int*)((char*)arr.begin - 4) != 0)
    operator_delete_(arr.begin);

  return result != 0;
}

// @ 0x00b94a90
CA::CA(float lo, float hi)
: mLo(lo), mHi(hi) {}

// @ 0x00b95050
CB::CB()
: mC(0), m10(0), m20(0), m24(0) {}

// @ 0x00b95070
CB::~CB()
{}

// @ 0x00b95160
void HeapMake(void** base, void** end, unsigned int a3, unsigned int a4, unsigned int a5)
{
    int n = (int)((char*)end - (char*)base) >> 2;
    if (n > 1) {
        int i = ((n - 2) >> 1) + 1;
        do {
            --i;
            void* p = base[i];
            if (p) {
                void** vt = *(void***)p;
                ((Thiscall2)vt[0xbc / 4])(p, (int)a4, (int)a5);
                (void)a3;
            }
            HeapFixdown(base, i, n, i);
        } while (i != 0);
    }
}

// @ 0x00b952e0
Elem16* LowerBound16(Elem16* first, Elem16* last, const unsigned int* key)
{
    int n = (int)((char*)last - (char*)first) >> 4;
    while (n > 0) {
        int half = n >> 1;
        Elem16* mid = first + half;
        if (key[0] > mid->key || (key[0] == mid->key && mid->sub < key[1])) {
            first = mid + 1;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// @ 0x00b95340
Elem16* UpperBound16(Elem16* first, Elem16* last, const unsigned int* key)
{
    int n = (int)((char*)last - (char*)first) >> 4;
    while (n > 0) {
        int half = n >> 1;
        Elem16* mid = first + half;
        if (mid->key <= key[0] && (mid->key < key[0] || !(key[1] < mid->sub))) {
            first = mid + 1;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// @ 0x00b953a0
RbNode* RbClone(RbNode* src, RbNode* parent)
{
    RbNode* node = (RbNode*)EAAllocate(0x14, g_str_Simulator, 0, 0, 0, 0);
    if (node) node->key = src->key;
    node->left = 0;
    node->right = 0;
    node->parent = parent;
    node->color = src->color;

    if (src->left) {
        node->left = RbClone(src->left, node);
    }
    RbNode* prev = node;
    for (RbNode* cur = src->right; cur != 0; cur = cur->right) {
        RbNode* nn = (RbNode*)EAAllocate(0x14, g_str_Simulator, 0, 0, 0, 0);
        if (nn) nn->key = cur->key;
        nn->left = 0;
        nn->right = 0;
        nn->parent = prev;
        nn->color = cur->color;
        prev->right = nn;
        if (cur->left) {
            nn->left = RbClone(cur->left, nn);
        }
        prev = nn;
    }
    return node;
}

// @ 0x00b95480
void* Partition4(void** first, void** last, void* pred, int (*cmp)(void*, void*))
{
    for (;;) {
        while (cmp(*first, pred)) ++first;
        while (cmp(pred, *(last - 1))) --last;
        if (first >= last) break;
        SwapElems(first, last);
        ++first;
    }
    // functor destructor
    if (pred) {
        HandleRelease(pred);
    }
    return first;
}

// @ 0x00b95500
void cTerrainResourceManager_GetPlanetInfo(void* self)
{
    void* pm = SP_PlanetModel();
    void* p = *(void**)((char*)pm + 0x24);
    if (!p) return;
    if (!((Thiscall0)((void**)*(void**)p)[8 / 4])(p)) return;

    unsigned int a = 0, b = 0, c = 0;
    void* r = ((Thiscall2)((void**)*(void**)p)[8 / 4])(p, 0x3d03f84, (int)&a);
    if (!SP_GetPropertyAsKey(r)) return;

    void* mgr = EA_ResourceMan_GetManager();
    unsigned int k3 = (unsigned int)&gEmptyString16;
    unsigned int k2 = (unsigned int)&gEmptyString16;
    unsigned int k1 = (unsigned int)&gEmptyString16;
    ((Thiscall2)((void**)*(void**)mgr)[0x7c / 4])(mgr, (int)&a, (int)&k1);

    (void)b; (void)c;
}

// @ 0x00b95630
int TerrainGrid::RingSearch(unsigned int mask, int* cell, float rmin, float rmax, int f2, int f3, int f4, int f5, int lim, float* dir)
{
    int  res = m_res;
    bool ok  = true;
    int  radius = 0;
    int  lo = f3;
    int  hi = f5;
    int  row = f2;
    int  col = f4;
    int  r2  = lim;

    for (;;) {
        ++lo;
        --r2;
        int inner = r2;
        while (r2 <= hi) {
            int face = res;
            int a = row, b = r2, c = inner;
            while (SP_WrapCubeFace(face, (unsigned int*)&a, &b, &c, 0, 0)) { /* remap */ }
            int idx = (res * a + c) * res + b;
            unsigned int* rec = (unsigned int*)((char*)m_faces + 4 + idx * 0xc);
            if (*rec & mask)
                return MarkSphere(mask, row, r2, inner, dir);
            ++inner;
        }

        --r2;
        ++hi;
        int outer = r2;
        if (r2 <= lo) {
            do {
                int face = res;
                int a = row, b = inner, c = lo;
                while (SP_WrapCubeFace(face, (unsigned int*)&a, &c, &b, 0, 0)) { /* remap */ }
                int idx = (res * a + b) * res + c;
                unsigned int* rec = (unsigned int*)((char*)m_faces + 4 + idx * 0xc);
                if (*rec & mask)
                    return MarkSphere(mask, row, inner, lo, dir);
                ++inner;
            } while (inner <= lo);
        }

        ++radius;
        if (col < 1) {
            if (r2 <= radius) return 1;
        } else {
            ok = (radius <= col);
        }
        if (!ok) return 0;
        (void)rmin; (void)rmax; (void)r2; (void)outer; (void)cell;
    }
}

// @ 0x00b95900
int TerrainGrid::FaceDistance(int* cell, float rmin, float rmax, float f2, float f3, float f4, int lim, unsigned int mask, int a, int b)
{
    void* rec = SP_CellRecord(cell[2], cell[0], cell[1]);
    float d = *(float*)((char*)rec + 8);
    if (d < 0.0f) {
        float dir[4];
        dir[0] = 0.0f; dir[1] = 0.0f; dir[2] = 0.0f; dir[3] = 0.0f;
        if ((mask & *(unsigned int*)((char*)rec + 4)) == 0) {
            float scale = (float)m_res / m_cellScale;
            int cx = (int)((float)cell[0] * 1.0f);
            int cy = (int)((float)cell[1] * 1.0f);
            int hit = RingSearch(mask, cell, (float)cell[2], (float)cell[0],
                                 (float)cell[1], cell[1], cx, cy, lim, dir);
            if (rmax > 0.0f && hit) {
                float uv0 = ((float)cell[0] + 0.5f) * scale * 2.0f - 1.0f;
                float uv1 = ((float)cell[1] + 0.5f) * scale * 2.0f - 1.0f;
                float uv2 = ((float)cell[2] + 0.5f) * scale * 2.0f - 1.0f;
                float t = SampleFaceUV(cell);
                dir[0] = uv0 * t - dir[0];
                dir[1] = uv1 * t - dir[1];
                dir[2] = uv2 * t - dir[2];
                float dist = dir[0] * dir[0] + (dir[1] * dir[1] + dir[2] * dir[2]);
                *(float*)((char*)rec + 8) = dist;
                if (dist < rmin) return 0;
                return 1;
            }
        } else {
            if (MarkSphere(mask, cell[2], cell[0], cell[1], dir) == 0) return 0;
            float scale = (float)m_res / m_cellScale;
            float uv0 = ((float)cell[0] + 0.5f) * scale * 2.0f - 1.0f;
            float uv1 = ((float)cell[1] + 0.5f) * scale * 2.0f - 1.0f;
            float uv2 = ((float)cell[2] + 0.5f) * scale * 2.0f - 1.0f;
            float t = SampleFaceUV(cell);
            dir[0] = uv0 * t - dir[0];
            dir[1] = uv1 * t - dir[1];
            dir[2] = uv2 * t - dir[2];
            float dist = dir[0] * dir[0] + (dir[1] * dir[1] + dir[2] * dir[2]);
            *(float*)((char*)rec + 8) = dist;
            if (lim != 0 && CheckAngle(dir, lim) == 0) return 0;
        }
    } else if (d == 3.4028235e+38) {
        return 0;
    }
    if (rmin <= d) {
        if (rmax <= 0.0f || d <= rmax) return 1;
    }
    (void)f2; (void)f3; (void)f4; (void)a; (void)b;
    return 0;
}

// @ 0x00b95d50
int TerrainGrid_FaceSample(int* cell, float zmin, float zmax, float dmin, float dmax, float ang, int f7, unsigned int mask, int f9, int f10)
{
    int local2 = cell[2];
    int local0 = cell[0];
    int local1 = cell[1];
    SP_GridFaceTransform(&local2, &local0, &local1);
    int l4 = local2, l0 = local0, l8 = local1;
    unsigned int m = SP_GridFaceMask(l4, l0, l8);
    if (mask != 0 && (mask & m) != 0) return 0;

    float v = (float)((g_156c084int * l0) + (unsigned int)(g_156c084int * l8) +
                      (unsigned int)(g_156c084int * l4));
    if (v < zmin || v > zmax) return 0;

    (void)dmin; (void)dmax; (void)ang; (void)f7; (void)f9; (void)f10; (void)g_156c060;
    return 1;
}

// @ 0x00b95e90
void* ContentValidationSummarizer::Destroy(unsigned char freeFlag)
{
    void** pv = (void**)this;
    *pv = &g_vtbl_1465a58;
    _ReadWriteBarrier();
    void* p1 = *(void**)((char*)this + 0x1c);
    if (p1 && *(int*)((char*)p1 - 4) != 0) operator_delete(p1);
    void* p2 = *(void**)((char*)this + 8);
    if (p2 && *(int*)((char*)p2 - 4) != 0) operator_delete(p2);
    *(void**)this = &g_vtbl_13ec458;
    if (freeFlag & 1) operator_delete(this);
    return this;
}

// @ 0x00b95ef0
void Vec16::Realloc(unsigned int n)
{
    if (n > (unsigned int)(((char*)cap - (char*)begin) >> 4)) {
        char* nb;
        if (n != 0) {
            nb = (char*)EAAllocate(n << 4, g_str_Simulator, 0, 0, (int)&g_allocator_13ebb38, 0xd1);
        } else {
            nb = 0;
        }
        CopyElems16(begin, end, nb);
        if (begin) operator_delete(begin);
        int cnt = (int)((Elem16*)end - (Elem16*)begin);
        begin = nb;
        end = nb + cnt * (int)sizeof(Elem16);
        cap = nb + (n << 4);
    }
}

// @ 0x00b95f70
void HashTable::Find(unsigned int* key, void** out)
{
    unsigned int k0 = key[0];
    unsigned int k1 = key[1];
    unsigned int idx = k0 % count;
    void* node = buckets[idx];
    unsigned int* bucket = &((unsigned int*)buckets)[idx];
    while (node) {
        if (k0 == *(unsigned int*)node && k1 == *(unsigned int*)((char*)node + 4)) {
            out[0] = node;
            out[1] = bucket;
            return;
        }
        node = *(void**)((char*)node + 0x40);
    }
    bucket = (unsigned int*)&buckets[count];
    out[0] = *(void**)bucket;
    out[1] = bucket;
}

// @ 0x00b95fe0
void HeapOps(void** first, void** last, unsigned int a4, unsigned int a5, unsigned int a6)
{
    // make-heap (variant that also inlines the same helper)
    {
        int n = (int)((char*)last - (char*)first) >> 2;
        if (n > 1) {
            int i = ((n - 2) >> 1) + 1;
            do {
                --i;
                void* p = first[i];
                if (p) {
                    void** vt = *(void***)p;
                    ((Thiscall2)vt[0xbc / 4])(p, (int)a5, (int)a6);
                }
                HeapFixdown2(first, i, n, i);
            } while (i != 0);
        }
    }

    for (void** it = last; it < first; ++it) {
        if (Func_ac0730(*it, *first)) {
            void* saved = *it;
            HandleAddRef(saved);
            void* old = *it;
            void* nv = *first;
            if (nv != old) {
                HandleAddRef(nv);
                *it = nv;
                HandleRelease(old);
            }
            HandleRelease(saved);
            HeapFixdown2(first, 0, (int)((char*)last - (char*)first) >> 2, 0);
        }
    }
    HeapMake2(first, last, a4, a5, a6);
}

// @ 0x00b96130
void Shuffle4(void** first, void** last, RandomLCG* rng)
{
    void** it = first + 1;
    if (it >= last) return;
    for (; it < last; ++it) {
        unsigned int r = rng->Uniform((unsigned int)(((char*)it - (char*)first) >> 2) + 1);
        void** target = first + r;
        SwapElems2(it, target);
    }
}

// @ 0x00b96180
void S96180::fn(int* param_2, int* param_3)
{
    int param_1 = (int)this;
    undefined4* puVar3 = (undefined4*)(param_1 + 4);
    if (*(undefined4**)(param_1 + 0xc) != 0) {
        undefined4* puVar1 = *(undefined4**)(param_1 + 0xc);
        do {
            puVar3 = puVar1;
            if (*param_3 < (int)puVar3[4])
                puVar1 = (undefined4*)puVar3[1];
            else
                puVar1 = (undefined4*)*puVar3;
        } while (puVar1 != 0);
    }
    undefined4 uVar4;
    if ((puVar3 == (undefined4*)(param_1 + 4)) || (*param_3 < (int)puVar3[4]))
        uVar4 = 0;
    else
        uVar4 = 1;
    int iVar2 = operator_new(0x18, "Simulator", 0, 0, kAllocFile, 0xd1);
    if ((int*)(iVar2 + 0x10) != 0) {
        *(int*)(iVar2 + 0x10) = *param_3;
        *(int*)(iVar2 + 0x14) = param_3[1];
    }
    RBTreeInsert((void*)iVar2, puVar3, (void*)(param_1 + 4), uVar4);
    *(int*)(param_1 + 0x14) = *(int*)(param_1 + 0x14) + 1;
    *param_2 = iVar2;
}

// @ 0x00b96220
int* FUN_00b96220(int* param_1, int param_2, int param_3, uint* param_4, undefined4 param_5)
{
    int iVar3 = param_3 - param_2 >> 4;
    int iVar5;
    int iVar2;
    if (0 < iVar3) {
        uint uVar4 = *param_4;
        do {
            iVar2 = iVar3 >> 1;
            uint uVar1 = *(uint*)(iVar2 * 0x10 + param_2);
            iVar5 = iVar2 * 0x10 + param_2;
            if ((uVar1 < uVar4) ||
                ((uVar1 <= uVar4 && (uVar4 = *param_4, *(uint*)(iVar5 + 4) < param_4[1])))) {
                param_2 = iVar5 + 0x10;
                iVar2 = iVar3 + (-1 - iVar2);
                iVar5 = param_3;
            } else if ((uVar1 <= uVar4) && (*(uint*)(iVar5 + 4) <= param_4[1])) {
                int p = FUN_00b95340(iVar5 + 0x10, param_3, param_4, param_5);
                iVar5 = FUN_00b952e0(param_2, iVar5, param_4, param_5);
                *param_1 = iVar5;
                param_1[1] = p;
                return param_1;
            }
            param_3 = iVar5;
            iVar3 = iVar2;
        } while (0 < iVar2);
    }
    *param_1 = param_2;
    param_1[1] = param_2;
    return param_1;
}

// @ 0x00b96360
void S96360::fn(int param_2, int param_3, int param_4, int allocator)
{
    int* param_1 = (int*)this;
    int local_4;
    if (param_3 != param_4) {
        int iVar3 = param_1[1];
        uint uVar2 = (param_4 - param_3) / 0x3c;
        if (uVar2 <= (uint)((param_1[2] - iVar3) / 0x3c)) {
            int iVar1 = param_1[1];
            uint uVar5 = (iVar3 - param_2) / 0x3c;
            if (uVar2 < uVar5) {
                int iVar6 = iVar1 + uVar2 * -0x3c;
                FUN_00b3f260(&local_4, iVar6, iVar1, iVar1, param_3);
                iVar3 = param_2;
                param_1[1] = param_1[1] + uVar2 * 0x3c;
                FUN_00ac4470(param_2, iVar6, iVar1);
                FUN_00ac4360(param_3, param_4, iVar3);
                return;
            }
            iVar3 = uVar5 * 0x3c;
            local_4 = iVar3 + param_3;
            FUN_00b3f260(&param_4, local_4, param_4, iVar1, param_3);
            int iVar6 = param_2;
            param_1[1] = param_1[1] + (uVar2 - uVar5) * 0x3c;
            FUN_00b3f260(&param_2, param_2, iVar1, param_1[1], param_3);
            param_1[1] = param_1[1] + iVar3;
            FUN_00ac4470(param_3, local_4, iVar3 + iVar6);
            return;
        }
        iVar3 = (iVar3 - *param_1) / 0x3c;
        uint uVar5 = iVar3 * 2;
        if (iVar3 == 0)
            uVar5 = 1;
        if (uVar5 <= uVar2 + iVar3)
            uVar5 = uVar2 + iVar3;
        if (uVar5 == 0)
            iVar3 = 0;
        else
            iVar3 = operator_new(uVar5 * 0x3c, "Simulator", 0, 0, kAllocFile, 0xd1);
        int iVar1 = param_2;
        undefined4 uVar4 = FUN_00ac2130(*param_1, param_2, iVar3);
        FUN_00b3f260(&param_3, param_3, param_4, uVar4, param_3);
        int iVar6 = FUN_00ac2130(iVar1, param_1[1], param_3);
        iVar1 = *param_1;
        if ((iVar1 != 0) && (*(int*)(iVar1 + -4) != 0))
            operator_delete__((void*)iVar1);
        *param_1 = iVar3;
        param_1[1] = iVar6;
        param_1[2] = iVar3 + uVar5 * 0x3c;
    }
}

// @ 0x00b965d0
unsigned S965d0::fn(unsigned param_2, unsigned param_3)
{
    undefined4* param_1 = (undefined4*)this;
    FUN_00b96220((int*)param_2, *param_1, param_1[1], (uint*)param_3, *(undefined1*)(param_1 + 5));
    return param_2;
}

// @ 0x00b96600
void S96600::fn(undefined4* param_2, undefined4* param_3)
{
    int* param_1 = (int*)this;
    undefined4* puVar1 = (undefined4*)param_1[1];
    int local_4;
    if (puVar1 != (undefined4*)param_1[2]) {
        if ((param_2 <= param_3) && (param_3 < puVar1))
            param_3 = param_3 + 1;
        if (puVar1 != 0)
            *puVar1 = puVar1[-1];
        size_t sVar4 = (size_t)((param_1[1] + -4) - (int)param_2);
        memmove((void*)(param_1[1] + ((int)sVar4 >> 2) * -4), param_2, sVar4);
        *param_2 = *param_3;
        param_1[1] = param_1[1] + 4;
        return;
    }
    local_4 = (int)puVar1 - *param_1 >> 2;
    void* _Dst;
    if (local_4 == 0) {
        local_4 = 1;
    } else {
        local_4 = local_4 * 2;
        if (local_4 == 0) {
            _Dst = 0;
            goto LAB_00b966a0;
        }
    }
    _Dst = (void*)operator_new(local_4 * 4, "Simulator", 0, 0, kAllocFile, 0xd1);
LAB_00b966a0:
    size_t sVar4 = (size_t)((int)param_2 - *param_1);
    void* pvVar5 = VectorInsert(_Dst, (void*)*param_1, (unsigned)sVar4);
    puVar1 = (undefined4*)((int)pvVar5 + ((int)sVar4 >> 2) * 4);
    if (puVar1 != 0)
        *puVar1 = *param_3;
    int iVar2 = param_1[1];
    pvVar5 = VectorInsert(puVar1 + 1, param_2, (unsigned)(iVar2 - (int)param_2));
    int iVar3 = *param_1;
    if ((iVar3 != 0) && (*(int*)(iVar3 + -4) != 0))
        operator_delete__((void*)iVar3);
    *param_1 = (int)_Dst;
    param_1[1] = (int)((int)pvVar5 + (iVar2 - (int)param_2 >> 2) * 4);
    param_1[2] = (int)((int)_Dst + local_4 * 4);
}

// @ 0x00b96710
void S96710::fn(undefined4* param_2, undefined4* param_3)
{
    int* param_1 = (int*)this;
    undefined4* puVar3 = (undefined4*)param_1[1];
    if (puVar3 != (undefined4*)param_1[2]) {
        if ((param_2 <= param_3) && (param_3 < puVar3))
            param_3 = param_3 + 4;
        if (puVar3 != 0) {
            *puVar3 = puVar3[-4];
            puVar3[1] = puVar3[-3];
            puVar3[2] = puVar3[-2];
            puVar3[3] = puVar3[-1];
        }
        FUN_00edba80(param_2, param_1[1] + -0x10, param_1[1]);
        *param_2 = *param_3;
        param_2[1] = param_3[1];
        param_2[2] = param_3[2];
        param_2[3] = param_3[3];
        param_1[1] = param_1[1] + 0x10;
        return;
    }
    int iVar1 = (int)puVar3 - *param_1 >> 4;
    int iVar2;
    if (iVar1 == 0) {
        iVar1 = 1;
    } else {
        iVar1 = iVar1 * 2;
        if (iVar1 == 0) {
            iVar2 = 0;
            goto LAB_00b967ba;
        }
    }
    iVar2 = operator_new(iVar1 << 4, "Simulator", 0, 0, kAllocFile, 0xd1);
LAB_00b967ba:
    puVar3 = (undefined4*)FUN_00c7ea30(*param_1, param_2, iVar2);
    if (puVar3 != 0) {
        *puVar3 = *param_3;
        puVar3[1] = param_3[1];
        puVar3[2] = param_3[2];
        puVar3[3] = param_3[3];
    }
    int iVar4 = (int)FUN_00c7ea30((int)param_2, (void*)param_1[1], (int)(puVar3 + 4));
    if (*param_1 != 0)
        operator_delete__((void*)*param_1);
    param_1[1] = iVar4;
    param_1[2] = iVar1 * 0x10 + iVar2;
    *param_1 = iVar2;
}

// @ 0x00b96820
void S96820::fn(undefined4* param_2, int param_3, uint* param_4, char param_5)
{
    int param_1 = (int)this;
    undefined4 uVar2;
    if (((param_5 == '\0') && (param_3 != param_1 + 4)) && (*(uint*)(param_3 + 0x10) <= *param_4))
        uVar2 = 1;
    else
        uVar2 = 0;
    undefined4* puVar1 = *(undefined4**)(param_1 + 0x18);
    if (puVar1 == 0)
        puVar1 = (undefined4*)operator_new(*(undefined4*)(param_1 + 0x28), "Simulator", 0, 0, kAllocFile, 0xd1);
    else
        *(undefined4*)(param_1 + 0x18) = *puVar1;
    if (puVar1 + 4 != 0)
        puVar1[4] = *param_4;
    RBTreeInsert(puVar1, (void*)param_3, (void*)(param_1 + 4), uVar2);
    *(int*)(param_1 + 0x14) = *(int*)(param_1 + 0x14) + 1;
    *param_2 = (int)puVar1;
}

// @ 0x00b96900
undefined4* FUN_00b96900(undefined4* param_1, undefined4* param_2, undefined4* param_3)
{
    if (param_1 != param_2) {
        do {
            if (param_3 != 0) {
                *(float*)param_3 = *(float*)param_1;
                ((S96560*)(param_3 + 1))->ctorFrom(param_1 + 1);
            }
            param_1 = param_1 + 6;
            param_3 = param_3 + 6;
        } while (param_1 != param_2);
    }
    return param_3;
}

// @ 0x00b96940
int FUN_00b96940(int param_1, int param_2, int param_3)
{
    for (; param_1 != param_2; param_1 = param_1 + 0x34) {
        undefined4* puVar2 = *(undefined4**)(param_1 + 0x24);
        SRBTree* tree = (SRBTree*)(param_1 + 0x18);
        while (puVar2 != 0) {
            tree->DoNuke((void*)puVar2[0]);
            undefined4* puVar1 = (undefined4*)puVar2[1];
            operator_delete__(puVar2);
            puVar2 = puVar1;
        }
        param_3 = param_3 + 0x34;
    }
    return param_3;
}

// @ 0x00b969e0
void FUN_00b969e0(void)
{
    char local_94[0x94];
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0x18657795, 0x24a4f5a, local_94);
    FUN_00401090();
    float fVar1 = FUN_00b7ec50();
    FUN_007f25c0("water_fraction", fVar1);
    FUN_007f2500();
    DAT_01688888 = (int)FUN_007f2590("population_min");
    DAT_01688884 = (int)FUN_007f2590("population_max");
    DAT_01688880 = FUN_007f2590("wealth_min");
    DAT_0168887c = FUN_007f2590("wealth_max");
    FUN_007f1d90();
}

// @ 0x00b96aa0
void FUN_00b96aa0(int param_1)
{
    char local_94[0x94];
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0xa1ed6e3c, 0x24a4f5a, local_94);
    FUN_007f2500();
    int iVar1 = (int)FUN_007f2590("num_tribes");
    float fVar4 = FUN_007f2590("tribe_pop");
    float fVar5 = FUN_007f2590("tribe_food");
    if (0 < iVar1) {
        do {
            void* pcVar2 = (void*)operator_new(0x18, "Simulator/cTribeData", 0, 0, 0, 0);
            int uVar3;
            if (pcVar2 == 0)
                uVar3 = 0;
            else
                uVar3 = cTribeData_ctor(pcVar2, (int)fVar4, (int)fVar5);
            FUN_00b8ef00(uVar3);
            iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
    }
    FUN_007f1d90();
}

// @ 0x00b96b80
void FUN_00b96b80(int param_1)
{
    char local_94[0x94];
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0x18657795, 0x24a4f5a, local_94);
    FUN_007f2500();
    int local_a8 = (int)FUN_007f2590("num_cities");
    float fVar7 = FUN_007f2590("wealth_min");
    float fVar8 = FUN_007f2590("wealth_max");
    if (0 < local_a8) {
        int local_9c = (int)ROUND(fVar8 - fVar7);
        do {
            unsigned iVar1 = RandomUint32Uniform(&_sMathRandom_SP__3VRandomLinearCongruential_Random_EA__A, local_9c + 1);
            int iVar2 = operator_new(0x50, "Simulator/cCivData", 0, 0, 0, 0);
            undefined4 uVar3;
            if (iVar2 == 0)
                uVar3 = 0;
            else
                uVar3 = FUN_00ff34c0((float)iVar1 + fVar7);
            iVar1 = operator_new(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
            void* pVVar4;
            if (iVar1 == 0)
                pVVar4 = 0;
            else
                pVVar4 = (void*)FUN_00ff1cb0();
            VideoEncoder_Jpeg_SetWidth(pVVar4, 4);
            unsigned uVar5 = RandomUint32Uniform(&_sMathRandom_SP__3VRandomLinearCongruential_Random_EA__A, 3);
            uVar5 = FUN_00bef920(uVar5);
            FUN_00bfc460(uVar5);
            unsigned uVar6 = RandomUint32Uniform(&_sMathRandom_SP__3VRandomLinearCongruential_Random_EA__A, 3);
            uVar5 = FUN_00bebc90(uVar5, uVar6);
            FUN_00ff0380(uVar5);
            FUN_00ff2c70(pVVar4);
            FUN_00b8eec0((void*)uVar3);
            local_a8 = local_a8 + -1;
        } while (local_a8 != 0);
        FUN_007f1d90();
        return;
    }
    FUN_007f1d90();
}

// @ 0x00b96d40
void FUN_00b96d40(undefined4 param_1)
{
    char local_94[0x94];
    char local_b0[12];
    undefined4 local_a4;
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0x9dd95c4, 0x24a4f5a, local_94);
    FUN_007f2500();
    char cVar1 = FUN_00c6fe50(param_1);
    float fVar8;
    if (cVar1 == '\0')
        fVar8 = FUN_007f2590("num_cities_in_colony");
    else
        fVar8 = FUN_007f2590("num_cities_in_home_planet");
    int local_b4 = (int)fVar8;
    undefined4 uVar9 = 0x100;
    undefined4 uVar2 = (undefined4)FUN_00b8d8f0(0x100);
    FUN_00b3d2a0(uVar2);
    FUN_00ba6d80(uVar2);
    cVar1 = FUN_00bb9af0(uVar9);
    if (cVar1 != '\0')
        local_b4 = 1;
    int iVar3 = operator_new(0x50, "Simulator/cCivData", 0, 0, 0, 0);
    void* pSVar4;
    if (iVar3 == 0)
        pSVar4 = 0;
    else
        pSVar4 = (void*)FUN_00ff3440();
    void* pcVar5 = BioProtectorSort_op();
    uVar2 = (undefined4)cGameNounManager_GetAvatar(pcVar5);
    rw_SList_SetElementSize(pSVar4, uVar2);
    pcVar5 = BioProtectorSort_op();
    if (pcVar5 != 0) {
        uVar2 = (undefined4)cGameNounManager_GetAvatar(pcVar5);
        FUN_00b3d2a0(uVar2);
        iVar3 = FUN_00ba9370(uVar2);
        if (iVar3 != 0) {
            FUN_00c352f0(local_b0);
            FUN_00ff3190(local_b0);
            DoNukeSubtree((void*)local_a4);
        }
    }
    if (0 < local_b4) {
        do {
            iVar3 = operator_new(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
            void* pVVar6;
            if (iVar3 == 0)
                pVVar6 = 0;
            else
                pVVar6 = (void*)FUN_00ff1cb0();
            uVar9 = 0x100;
            uVar2 = (undefined4)FUN_00b8d8f0(0x100);
            FUN_00b3d2a0(uVar2);
            FUN_00ba6d80(uVar2);
            cVar1 = FUN_00bb9af0(uVar9);
            if (cVar1 == '\0') {
                VideoEncoder_Jpeg_SetWidth(pVVar6, 4);
                ((VideoEncoder_Jpeg*)pVVar6)->mFramesPerSecond = 2.10195e-43f;
            } else {
                VideoEncoder_Jpeg_SetWidth(pVVar6, 2);
            }
            pcVar5 = BioProtectorSort_op();
            iVar3 = cGameNounManager_GetAvatar(pcVar5);
            FUN_00b3d2a0(iVar3);
            int iVar7 = FUN_00885c90();
            if (iVar3 == iVar7)
                uVar2 = 0x280852f1;
            else
                uVar2 = 0xfd701f6f;
            FUN_00ff0380(uVar2);
            FUN_00ff2c70(pVVar6);
            local_b4 = local_b4 + -1;
        } while (local_b4 != 0);
    }
    FUN_00b8eec0(pSVar4);
    FUN_007f1d90();
}

// @ 0x00b96f40
void FUN_00b96f40(int param_1, int param_2)
{
    if (param_1 != 0) {
        switch (param_2) {
        case 2:
            FUN_00b96aa0(param_1);
            break;
        case 4:
            FUN_00b96b80(param_1);
            break;
        case 5:
            FUN_00b96d40(param_1);
            break;
        }
        ((S96f40*)param_1)->Notify(1);
    }
}

// @ 0x00b96fa0
void FUN_00b96fa0(void)
{
    char local_94[0x94];
    cArithmeticaProgram_ctor(local_94);
    LoadArithmeticaFile(0x18657795, 0x24a4f5a, local_94);
    FUN_007f2500();
    FUN_007f2590("num_harvesters");
    float fVar7 = FUN_007f2590("num_offensive_vehicles");
    int local_9c = 0;
    int* piVar2 = FUN_00c71000();
    int iVar6 = piVar2[1] - *piVar2 >> 2;
    if (0 < iVar6) {
        do {
            int iVar3 = FUN_00c71030(local_9c);
            if ((*(int*)(iVar3 + 0x40) - *(int*)(iVar3 + 0x3c) & 0xfffffffcU) != 0) {
                undefined4 uVar1 = *(undefined4*)(**(int**)(iVar3 + 0x3c) + 0x34);
                iVar3 = (int)fVar7;
                if (0 < (int)fVar7) {
                    do {
                        int iVar4 = operator_new(0x14, "Simulator/cVehicleData", 0, 0, 0, 0);
                        undefined4 uVar5;
                        if (iVar4 == 0)
                            uVar5 = 0;
                        else
                            uVar5 = FUN_00ff0df0(&DAT_01688890, 2, uVar1);
                        FUN_00ff2d20(uVar5);
                        iVar3 = iVar3 + -1;
                    } while (iVar3 != 0);
                }
            }
            local_9c = local_9c + 1;
        } while (local_9c < iVar6);
    }
    FUN_007f1d90();
}

// @ 0x00b970c0
int S970c0::fn(undefined4 param_2)
{
    undefined4* param_1 = (undefined4*)this;
    int local[2];
    FUN_00b96220(local, *param_1, param_1[1], (uint*)param_2, *(undefined1*)(param_1 + 5));
    return local[1] - local[0] >> 4;
}

// @ 0x00b970f0
void __stdcall FUN_00b970f0(uint param_1, uint param_2)
{
    for (; param_1 < param_2; param_1 = param_1 + 0x34) {
        undefined4* puVar2 = *(undefined4**)(param_1 + 0x24);
        SRBTree* tree = (SRBTree*)(param_1 + 0x18);
        while (puVar2 != 0) {
            tree->DoNuke((void*)puVar2[0]);
            undefined4* puVar1 = (undefined4*)puVar2[1];
            operator_delete__(puVar2);
            puVar2 = puVar1;
        }
    }
}

// @ 0x00b97140
int S97140::fn(undefined4* param_2, undefined4* param_3)
{
    int* param_1 = (int*)this;
    undefined4* puVar1 = (undefined4*)param_1[1];
    int iVar2 = (int)param_2 - *param_1 >> 4;
    if ((param_2 == puVar1) && (puVar1 != (undefined4*)param_1[2])) {
        param_1[1] = (int)(puVar1 + 4);
        if (puVar1 != 0) {
            *puVar1 = *param_3;
            puVar1[1] = param_3[1];
            puVar1[2] = param_3[2];
            puVar1[3] = param_3[3];
            return iVar2 * 0x10 + *param_1;
        }
    } else {
        ((S96710*)param_1)->fn(param_2, param_3);
    }
    return iVar2 * 0x10 + *param_1;
}

// @ 0x00b97240
undefined4* S97240::fn(undefined4* param_2)
{
    Elem97240* dst = (Elem97240*)this;
    Elem97240* src = (Elem97240*)param_2;
    dst->v.a = src->v.a;
    dst->v.b = src->v.b;
    dst->v.c = src->v.c;
    dst->v.d = src->v.d;
    dst->b = src->b;
    dst->i = src->i;
    ((S96560*)((char*)dst + 0x18))->ctorFrom((char*)src + 0x18);
    return (undefined4*)this;
}

// @ 0x00b981a0
void cChildList::Add(u32 value, u32 object)
{
    mValues.push_back(value);
    mObjects.push_back(object);

    mTotal = 0;
    u32 n = mValues.size();
    for (u32 i = 0; i < n; ++i)
        mTotal += mValues.begin()[i];
}

// @ 0x00b98230
InsertResult* cSpawnTable::Insert(InsertResult* out, const Entry* e)
{
    Entry* pos = (Entry*)FUN_00b952e0(mpBegin, mpEnd, e, mbFlag);
    out->mpPos = InsertAt(pos, e);
    out->mbInserted = true;
    return out;
}

// @ 0x00b98270
Node* cSpawnTable::AllocNode(const NodeSource* src)
{
    Node* node = mpFreeList;
    if (node)
        mpFreeList = node->mpFreeNext;
    else
        node = (Node*)operator_new(mpAllocator, "Simulator", 0, 0, kAllocFile_s00b9_81a0, 0xd1);

    if (node)
    {
        const NodeSource* s = src;
        node->mKey = s->mKey;
        ChildVector& children = node->mChildren;
        children.mpBegin = children.mInline;
        children.mpEnd = children.mInline;
        children.mSize = 0;
        children.mpCap = children.mpBegin + 8;
        children.CopyFrom(&s->mChildren);
    }
    node->mpNext = 0;
    return node;
}

// @ 0x00b982e0
void cSpawnTable::DestroyBuckets(Node** buckets, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        Node* node = buckets[i];
        while (node)
        {
            Node* cur = node;
            node = cur->mpNext;
            void** end = cur->mChildren.mpEnd;
            void** p = cur->mChildren.mpBegin;
            while (p < end)
            {
                if (*p)
                    ((Destroyable*)*p)->v01();
                ++p;
            }
            if (cur->mChildren.mpBegin && cur->mChildren.AllocFlagBefore() != 0)
                operator_delete(cur->mChildren.mpBegin);

            if (cur != mpSentinel)
            {
                if (cur < mpPoolBegin || cur >= mpPoolEnd)
                {
                    operator_delete(cur);
                }
                else
                {
                    cur->mpFreeNext = mpFreeList;
                    mpFreeList = cur;
                }
            }
        }
        buckets[i] = 0;
    }
}

// @ 0x00b983b0
void cSpotGrid::FinishRegions()
{
    SortRegions(mpRegionBegin, mpRegionEnd, (RegionPred)RegionLess);

    cRegion** const listEnd = mpRegionEnd;
    for (cRegion** it = mpRegionBegin; it != listEnd; ++it) {
        cRegion* region = *it;
        if (region->mbDone == 0)
            continue;

        const int face = region->mFace;
        int rowMin = region->mRowMin;
        int rowMax = region->mRowMax;
        int colMin = region->mColMin;
        int colMax = region->mColMax;
        bool growLeft = true, growRight = true, growUp = true, growDown = true;
        do {
            // grow the column span: scan the cells left of / right of every row
            int thickLeft = 0, thickRight = 0, thickUp = 0, thickDown = 0;
            int row = rowMin;
            while (growLeft || growRight) {
                if (row > rowMax) {
                    if (growLeft) colMin -= thickLeft;
                    if (growRight) colMax += thickRight;
                    break;
                }
                cRegion* left = CellAt(face, row, colMin - 1).mpRegion;
                cRegion* right = CellAt(face, row, colMax + 1).mpRegion;
                bool okLeft = left && left->mbDone && left->mRowMin >= rowMin && left->mRowMax <= rowMax
                    && (thickLeft == 0 || left->mColMax - left->mColMin + 1 == thickLeft);
                growLeft = growLeft & okLeft;
                if (growLeft && thickLeft == 0)
                    thickLeft = left->mColMax - left->mColMin + 1;
                bool okRight = right && right->mbDone && right->mRowMin >= rowMin && right->mRowMax <= rowMax
                    && (thickRight == 0 || right->mColMax - right->mColMin + 1 == thickRight);
                growRight = growRight & okRight;
                if (growRight && thickRight == 0)
                    thickRight = right->mColMax - right->mColMin + 1;
                row++;
            }
            // grow the row span: scan the cells above / below every column
            int col = colMin;
            while (growUp || growDown) {
                if (col > colMax) {
                    if (growUp) rowMin -= thickUp;
                    if (growDown) rowMax += thickDown;
                    break;
                }
                cRegion* up = CellAt(face, rowMin - 1, col).mpRegion;
                cRegion* down = CellAt(face, rowMax + 1, col).mpRegion;
                bool okUp = up && up->mbDone && up->mColMin >= colMin && up->mColMax <= colMax
                    && (thickUp == 0 || up->mRowMax - up->mRowMin + 1 == thickUp);
                growUp = growUp & okUp;
                if (growUp && thickUp == 0)
                    thickUp = up->mRowMax - up->mRowMin + 1;
                bool okDown = down && down->mbDone && down->mColMin >= colMin && down->mColMax <= colMax
                    && (thickDown == 0 || down->mRowMax - down->mRowMin + 1 == thickDown);
                growDown = growDown & okDown;
                if (growDown && thickDown == 0)
                    thickDown = down->mRowMax - down->mRowMin + 1;
                col++;
            }
        } while (growLeft || growRight || growUp || growDown);

        region->mColMin = (short)colMin;
        region->mRowMin = (short)rowMin;
        region->mRowMax = (short)rowMax;
        region->mColMax = (short)colMax;

        // take over every cell of the grown rectangle
        for (int r = rowMin; r <= rowMax; r++) {
            for (int c = colMin; c <= colMax; c++) {
                cRegion* other = CellAt(face, r, c).mpRegion;
                if (other && other != region) {
                    other->mbDone = 0;
                    CellAt(face, r, c).mpRegion = region;
                }
            }
        }

        // border flags
        region->mSide[0] = 0;
        region->mSide[1] = 0;
        region->mSide[2] = 0;
        region->mSide[3] = 0;
        region->mbAnySide = 0;
        const int leftCol = colMin - 1;
        const int rightCol = colMax + 1;
        int r;
        for (r = rowMin; r <= rowMax; r++) {
            region->mSide[0] |= CellAt(face, r, leftCol).mFlag;
            region->mSide[2] |= CellAt(face, r, rightCol).mFlag;
        }
        int c;
        for (c = colMin; c <= colMax; c++) {
            region->mSide[1] |= CellAt(face, rowMin - 1, c).mFlag;
            region->mSide[3] |= CellAt(face, rowMax + 1, c).mFlag;
        }
        region->mbAnySide = region->mSide[3] | region->mSide[2] | region->mSide[1] | region->mSide[0];
        region->mArea = (colMax - colMin + 1) * (rowMax - rowMin + 1);
    }

    // drop the dead regions (remove_if + erase), then sort again
    cRegion** const first = mpRegionBegin;
    cRegion** const last = mpRegionEnd;
    cRegion** dst = first;
    while (dst != last && (*dst)->mbDone != 0)
        ++dst;
    if (dst != last) {
        for (cRegion** src = dst + 1; src != last; ++src) {
            if ((*src)->mbDone != 0) {
                *dst = *src;
                ++dst;
            }
        }
    }
    memcpy(dst, last, (mpRegionEnd - last) * sizeof(cRegion*));
    mpRegionEnd -= (last - dst);

    cRegion** const sfirst = mpRegionBegin;
    cRegion** const slast = mpRegionEnd;
    if (sfirst != slast) {
        int n = (int)(slast - sfirst);
        int lg = 0;
        for (int m = n; m != 0; m >>= 1)
            lg++;
        introsort(sfirst, slast, lg * 2 - 2, (RegionPred)RegionLess);
        if (n > 28) {
            cRegion** const mid = sfirst + 28;
            insertion_sort(sfirst, mid, (RegionPred)RegionLess);
            for (cRegion** p = mid; p != slast; ++p) {
                cRegion* val = *p;
                cRegion** q = p;
                while (q[-1]->mArea < val->mArea) {
                    *q = q[-1];
                    --q;
                }
                *q = val;
            }
        } else {
            insertion_sort(sfirst, slast, (RegionPred)RegionLess);
        }
    }
}

// @ 0x00b98c00
bool FUN_00b98c00(IOSource* source)
{
    cSPEditorSpeciesManager* mgr = GetSetting9();

    u32 count = 0;
    void* stream = source->GetStreamSource()->GetStream();
    ReadInt32(stream, &count, 1, 0);

    Entry* first = g_SpawnTable.mpBegin;
    Entry* last = g_SpawnTable.mpEnd;
    copy_705250(last, last, first);
    g_SpawnTable.mpEnd -= last - first;
    g_SpawnTable.Realloc(count);

    for (u32 i = 0; i < count; i++)
    {
        u32 key0 = 0;
        u32 key1 = 0;

        stream = source->GetStreamSource()->GetStream();
        ReadInt32(stream, &key0, 1, 0);

        stream = source->GetStreamSource()->GetStream();
        ReadInt32(stream, &key1, 1, 0);

        Key key = { 0, 0, 0 };
        FUN_00ae2ed0(source, &key);

        bool keep;
        stream = source->GetStreamSource()->GetStream();
        ReadBool(stream, &keep);

        const void* profile = mgr->GetProfile(key);
        if (profile)
        {
            Entry entry;
            entry.k0 = key0;
            entry.k1 = key1;
            entry.v2 = (u32)profile;
            entry.v3 = keep;

            Entry* pos = (Entry*)FUN_00b952e0(g_SpawnTable.mpBegin, g_SpawnTable.mpEnd,
                                              &entry, g_SpawnTable.mbFlag);
            if (pos == g_SpawnTable.mpEnd && g_SpawnTable.mpEnd != g_SpawnTable.mpCap)
            {
                Entry* end = g_SpawnTable.mpEnd;
                g_SpawnTable.mpEnd = end + 1;
                *end = entry;
            }
            else
            {
                g_SpawnTable.InsertShift(pos, &entry);
            }
        }
    }
    return true;
}

// @ 0x00b9bed0
void __cdecl FUN_00b9bed0(void* arg)
{
    cGameNounManager_s00b9_bed0* nouns = SP::NounManager();                      // 0xb3d300
    if (nouns == 0) return;
    VecOut<void>* data = nouns->GetGameDataVector(
        &FUN_00cd7d10, &FUN_00d3d420, &FUN_00accbb0, &FUN_00b1e500,
        kTribeTypeTag);                                              // 0xb21340
    int nounCount = (int)(data->mVec.mpEnd - data->mVec.mpBegin);
    cPlanetModel_s00b9_bed0* model = SP::PlanetModel();                          // 0xb3d350
    if (model == 0) return;

    cArithmeticaProgram prog;
    prog.Construct();                                                 // 0x7f1e60
    LoadArithmeticaFile_s00b9_bed0((void*)0xa1ed6e3c, (void*)0x24a4f5a, &prog);   // 0x7f2240
    prog.Reset();                                                     // 0x7f2500
    float numTribes = prog.GetVar(kNumTribesNearWater);               // 0x7f2590
    float minDist   = prog.GetVar(kMinDistToNeighborTribe);
    float maxDist   = prog.GetVar(kMaxDistToNeighborTribe);
    float maxSlope  = prog.GetVar(kMaxTribeLocationSlope);

    cSpawner* spawner = (cSpawner*)arg;
    Range_s00b9_bed0* list = spawner->GetSpawnList();                            // 0xc71010
    void** it = list->mpBegin;
    if (nounCount > 0) ++it;
    if (it != list->mpEnd) {
        do {
            Vec3 v;
            v.x = g_1688890; v.y = g_1688894; v.z = g_1688898;
            int index = (int)(it - list->mpBegin);
            bool found = false;
            for (int trial = 0; trial < 500; trial++) {
                if (found) break;
                float out[3];
                float* p = model->PickPoint(out);                     // 0xb81720
                v.x = p[0]; v.y = p[1]; v.z = p[2];
                bool valid = model->IsPointValid(&v.x);               // 0xb7e3e0
                if (numTribes > (float)index) {
                    if (!valid) { found = false; }
                    else {
                        found = FUN_00b94420(arg, &v.x, kFloatMax,
                                             minDist, maxSlope) != 0;  // 0xb94420
                    }
                } else {
                    if (!valid) { found = false; }
                    else {
                        found = FUN_00b94670(arg, &v.x, kFloatMax,
                                             kFloatMax, minDist, maxDist,
                                             maxSlope);                // 0xb94670
                    }
                }
            }
            if (found) {
                cSpawnHandle* h = spawner->CreateSpawn(index);        // 0xc71110
                h->SetPosition(&v.x);                                 // 0x980c20
            }
            ++it;
        } while (it != list->mpEnd);
    }

    int i = 0;
    int n = spawner->CountSpawns();                                   // 0xc71120
    if (n > 0) {
        do {
            cGameData_s00b9_bed0* d = (cGameData_s00b9_bed0*)list->mpBegin[i];
            float* p = d->GetPos();                                   // 0x6e64f0
            if (p[0] == g_1688890 && p[1] == g_1688894 &&
                p[2] == g_1688898) {
                spawner->RemoveSpawn(i);                              // 0xc71140
            } else {
                ++i;
            }
            n = spawner->CountSpawns();
        } while (i < n);
    }
    prog.Destroy();                                                   // 0x7f1d90
}

// @ 0x00b9c180
int StarTable::Find(const int* src)
{
    Key8 key;
    MakeKey(&key, src);                                               // 0xb95f70
    if (key.m0 == mSlots04[mIndex08]) {
        // Two empty vectors with 8-pointer inline buffers.  The dword just
        // below each buffer is the allocator's "heap block" tag; the retail
        // destructor only frees the buffer when it is non-zero, so it must be
        // zero here (the original zeroes both slots explicitly).
        struct InlineBuf8 { int mHead; void* mVec[8]; };
        InlineBuf8 sb;
        InlineBuf8 sa;
        sb.mHead = 0;
        sa.mHead = 0;
        void* bufB = sb.mVec;
        void* bufA = sa.mVec;
        VecTemp vb;
        VecTemp va;
        vb.mpBegin = bufB; vb.mpEnd = bufB; vb.mpCapacity = sb.mVec + 8;
        vb.mAllocName = 0; vb.mAllocPad = 0;
        va.mpBegin = bufA; va.mpEnd = bufA; va.mpCapacity = sa.mVec + 8;
        va.mAllocName = 0; va.mAllocPad = 0;
        vb.Assign(va);                                                // 0x1011cc0
        Pair8 pair;
        pair.m0 = src[0];
        pair.m4 = src[1];
        key.m0 &= 0xffffff00;
        FindRecord(&key, &pair, key.m0);                              // 0xb98dd0
        vb.Destroy();                                                 // 0xae6970
        va.Destroy();
    }
    return key.m0 + 8;
}

// @ 0x00b9c250
void TObj::FUN_00b9c250(void)
{
    int iVar3 = (int)mBegin;
    int iVar1 = (int)mEnd;
    int uVar2 = FUN_00b969a0(iVar1, iVar1, iVar3);
    F_1023030(uVar2, (int)mEnd);
    mEnd = (int*)((int)mEnd + (-((iVar1 - iVar3) / 0x14)) * 0x14);
}

// @ 0x00b9c5b0
void __cdecl FUN_00b9c5b0(TObj* p)
{
    FUN_00b9bb40((int)p->mSub30);
}

// @ 0x00b9c5c0
void TObj::FUN_00b9c5c0(void)
{
    F_b9a630();
    void* r20 = mRef20;
    if (r20 != 0) {
        unsigned* rc = (unsigned*)((char*)r20 + 4);
        unsigned c = rc[0] + -1;
        rc[0] = c;
        if (c == 0) {
            rc[0] = 1;
            ((void(__thiscall*)(void*, int))VF(r20, 0))(r20, 1);
        }
    }
    void* r1c = mRef1c;
    if (r1c != 0) {
        unsigned* rc = (unsigned*)((char*)r1c + 4);
        unsigned c = rc[0] + -1;
        rc[0] = c;
        if (c == 0) {
            rc[0] = 1;
            ((void(__thiscall*)(void*, int))VF(r1c, 0))(r1c, 1);
        }
    }
    void* a = mArr;
    if (a != 0 && *(int*)((char*)a - 4) != 0) {
        FUN_00f47380(a);
    }
}

// @ 0x00b9c830
void __cdecl FUN_00b9c830(int propList, float* pos, float maxDistSq, int propSpawns, int propArchetypes)
{
    cPlanetModel_s00b9_bed0* model = SP::PlanetModel();                          // 0xb3d350
    int base = FUN_00b3d440();                                        // 0xb3d440
    CharRange* world = (CharRange*)(base + 0x1e5f0);
    int continent = model->GetContinent(pos);                         // 0xb88590

    int countA = 0;
    unsigned* idsA = 0;
    if (GetPropertyAsUint32Array(propList, propSpawns, &countA, &idsA) &&
        countA > 0) {                                                 // 0x6a0840
        for (char* it = world->mpBegin; it != world->mpEnd; it += 0x19a8) {
            float* p = (float*)(it + 8);
            float dx = pos[0] - p[0];
            float dz = pos[2] - p[2];
            float dy = pos[1] - p[1];
            float d = dx * dx + dz * dz + dy * dy;
            if (maxDistSq == kFloatMax || d < maxDistSq) {
                if (model->GetContinent(p) == continent) {            // 0xb88590
                    PlaceSpawnDefinitionsOnPlanet(p, idsA, countA, 0, 1); // 0xb9b090
                }
            }
        }
    }

    int countB = 0;
    unsigned* idsB = 0;
    if (GetPropertyAsUint32Array(propList, propArchetypes,
                                 &countB, &idsB) &&
        countB > 0) {                                                 // 0x6a0840
        for (int k = 0; k < countB; k++) {
            int countC = 0;
            unsigned* idsC = 0;
            if (GetPropertyAsUint32Array(propList, (int)idsB[k],
                                         &countC, &idsC) &&
                countC > 0) {                                         // 0x6a0840
                for (char* it = world->mpBegin; it != world->mpEnd;
                     it += 0x19a8) {
                    float* p = (float*)(it + 8);
                    float dz = pos[2] - p[2];
                    float dy = pos[1] - p[1];
                    float dx = pos[0] - p[0];
                    float d = dz * dz + dy * dy + dx * dx;
                    if (maxDistSq == kFloatMax || d < maxDistSq) {
                        if (model->GetContinent(p) == continent) {    // 0xb88590
                            PlaceArchetypeSubSpawns(p, idsC, countC, 0); // 0xb9aa10
                        }
                    }
                }
            }
        }
    }
}

// @ 0x00b9caa0
void FUN_00b9caa0(void)
{
    NounManager_s00b9_caa0();
    IPropManager* pm = PropertyManager_s00b9_caa0();
    PropertyListPtr list;
    uint32_t listID = g_TribeSetupLists[NounManager_s00b9_caa0()->GetCurrentTerrainSphere()->FUN_00c75420() + 3];
    if (GetPropList(pm, listID, 0x0302a1c9, list)) {
    cPlanetModel_s00b9_caa0* planet = PlanetModel_s00b9_caa0();
    Vector3 pos;
    bool flag;
    bool found = FUN_00b99070(&pos, &flag);
    FUN_00b992c0();
    if (found) {
        PropertyListPtr markers;
        if (pm->GetPropertyList(0x03d7f90a, 0x0302a1c9, markers)) {
            float a = 0.0f;
            float b = 0.0f;
            float c = 0.0f;
            GetFloatProperty(markers.get(), 0x24a02634, &a);
            GetFloatProperty(markers.get(), 0xcbb8d102, &b);
            GetFloatProperty(markers.get(), 0x561c98ac, &c);
            g_PlanetGrid.FUN_00b90ea0(&pos, a, b, c);
            if (markers->HasProperty(0xbb64b481)) {
                Property* p = markers->GetPropertyObject(0xbb64b481);
                FUN_00b9aa10(&pos, PropertyItems(p), PropertyItemCount(p), 0x03d7f90a);
            }
        }
    } else {
        pos = planet->FUN_00b81720();
    }

    FUN_00c99dc0(&pos, g_GameModeState.Get17c(), g_GameModeState.Get178(), 0);

    uint32_t placed = 0;
    uint32_t effects[4] = { 0xe45c5bbb, 0x631674df, 0xf2659f20, 0x99945d8d };
    uint32_t count = 6;
    GetPropertyUInt(list.get(), 0xa6df0147, count);
    uint32_t idx = 0;
    while (placed < count) {
        if (idx >= 4)
            break;
        uint32_t id = effects[idx];
        int n = FUN_00b9b090(&pos, &id, 1, id, 1);
        if (n == 0)
            idx++;
        else
            placed += n;
    }

    bool buildPaths = g_DebugProperties->GetBool(0x04d8f5e6);
    uint32_t maxPaths = GetPropertyIntDefault(list.get(), 0xd914eed2, 3);
    float halfWidth = GetPropertyFloatDefault(list.get(), 0x1d92aa9d, 1.0f) * 0.5f;
    float range = GetPropertyFloatDefault(list.get(), 0x7f8d0f30, 250.0f);
    float rangeSq = range * range;
    float step = GetPropertyFloatDefault(list.get(), 0x78044a34, 30.0f);
    if (buildPaths && maxPaths > 0) {
        SpatialPtrVector sites;
        sites.reserve(placed);
        GameDataPtrVector& data = NounManager_s00b9_caa0()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                        (void*)FUN_00ace070, (void*)FUN_00b1e500,
                                                        0x036be27e)->mData;
        for (cGameData** it = data.mpBegin, **itEnd = data.mpEnd; it != itEnd; ++it) {
            cGameData* gd = *it;
            if (gd->mDefinitionID == 0x57f09e5e)
                sites.push_back(SpatialPtr(&gd->mSpatial));
        }

        uint32_t numSites = sites.size();
        uint32_t n = eastl::min(numSites, maxPaths);
        FUN_00b95fe0(sites.mpBegin, sites.mpBegin + n, sites.mpEnd, DistanceLess(pos));

        cTribeModeStrategy* strategy = cTribeModeStrategy::Instance();
        strategy->mPaths.clear();
        strategy->mPaths.reserve(n);

        GridNodeVector gridPath;
        for (uint32_t i = 0; i < n; i++) {
            const Vector3* p = sites.mpBegin[i]->GetPosition();
            Vector3 d = pos - *p;
            if (!((d.x * d.x + d.z * d.z) + d.y * d.y < rangeSq))
                break;
            gridPath.clear();
            Vector3 off = (*p - pos).Normalized() * step;
            Vector3 start = planet->DirectionToSurfacePosition(pos + off);
            Vector3 end = planet->DirectionToSurfacePosition(*p - off);
            if (FUN_00b3d290()->FUN_00ac6960(g_1565b18, start, end, &gridPath, 0.0f, 1.0f)) {
                strategy->mPaths.push_back();
                TribePath& path = strategy->mPaths.back();
                path.mPoints.reserve(gridPath.size() + 1);
                path.mPoints.push_back(start);
                for (GridNode* g = gridPath.mpBegin, *gEnd = gridPath.mpEnd; g != gEnd; ++g)
                    path.mPoints.push_back(planet->DirectionToSurfacePosition(g->mPos));
                FUN_00b922c0(&path, halfWidth);
            }
        }
    }

    if (list->HasProperty(0xa1d6248e)) {
        Property* p = list->GetPropertyObject(0xa1d6248e);
        FUN_00b9aa10(&pos, PropertyItems(p), PropertyItemCount(p), listID);
    }
    if (list->HasProperty(0xf7084224)) {
        Property* p = list->GetPropertyObject(0xf7084224);
        FUN_00b9b090(&pos, PropertyItems(p), PropertyItemCount(p), 0, 1);
    }

    float radiusSq = 40000.0f;
    float radius;
    if (GetPropertyFloat(list.get(), 0xf64f11be, radius))
        radiusSq = radius * radius;
    FUN_00b9c830(list.get(), &pos, radiusSq, 0x204e6edd, 0x73cc6df5);

    eastl::fixed_set_uint8 continents;
    uint32_t continent = planet->GetContinent(pos);
    continents.insert(continent);
    GameDataPtrVector& sites = NounManager_s00b9_caa0()->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                                (void*)FUN_00ace070, (void*)FUN_00b1e500,
                                                                0x036be27e)->mData;
    for (cGameData** it = sites.mpBegin, **itEnd = sites.mpEnd; it != itEnd; ++it) {
        cGameData* gd = *it;
        if (gd->mDefinitionID == 0x91fe517b &&
            (gd->mSubType == 0xaed08dd4 || gd->mSubType == 0xd8c67022)) {
            const Vector3* p = gd->mSpatial.GetPosition();
            continent = planet->GetContinent(*p);
            if (continents.find(continent) == continents.end()) {
                continents.insert(continent);
                FUN_00b9c830(list.get(), p, 3.402823466e+38F, 0x84f2454a, 0x242811c2);
            }
        }
    }
    }
}

// @ 0x00b9d640
int FUN_00b9d640(cSpawnDefinition* def, const uint32_t& key, int* pBelow, int* pAbove)
{
    if (def->mbEnabled && def->mPlaced.find(key).mpNode != def->mPlaced.end()) {
        int placed = FUN_00b9b090((const Vector3*)def, &key, 1, key, 1);
        if (placed != 0) {
            if (pBelow)
                *pBelow += placed;
            if (pAbove)
                *pAbove -= placed;
        } else {
            SpawnRecord record;
            record.mbFlag = (uint8_t)placed;
            def->mPlaced.insert(key, record);
        }
        return placed;
    }
    return 0;
}

// @ 0x00b9d6d0
void FUN_00b9d6d0(void* target, cSpawnPropertyList* list)
{
    float offsetX = 0.0f, offsetY = 0.0f, offsetZ = 0.0f;
    if (list) {
        GetSpawnFloat(list, 0x24a02634, offsetX);
        GetSpawnFloat(list, 0xcbb8d102, offsetY);
        GetSpawnFloat(list, 0x561c98ac, offsetZ);
    }
    Vector3 pos(offsetX, offsetY, offsetZ);
    g_PlanetGrid.FUN_00b90ea0(target, pos);

    if (list->HasProperty(0xbb64b481)) {
        Property* p = list->GetPropertyObject(0xbb64b481);
        FUN_00b9aa10((const Vector3*)target, PropertyItems(p), PropertyItemCount(p), list->mGroupId);
    }
}

// @ 0x00b9ff80
void FUN_00b9ff80(StarWorld* p)
{
    FUN_00bf55d0();
    FUN_00b9fa40();
    FUN_00b9a4d0(p);
    StarVec* v = p->getVec();
    int i = 0;
    int n = p->count();
    while (i < n)
    {
        Vector3_s00b9_f9b0* pos = ((Vector3_s00b9_f9b0*)v->mpBegin[i]->mChildren.mpBegin[0])->Self();
        if (pos->x == g_starPos.x && pos->y == g_starPos.y && pos->z == g_starPos.z)
            p->remove(i);
        else
            i++;
        n = p->count();
    }
    StarVec* w = p->getVec();
    if (w->mpBegin != w->mpEnd)
    {
        unsigned cnt = (unsigned)p->count();
        unsigned r = g_random.RandomUint32Uniform(cnt, (unsigned)p);
        FUN_00b93750(r, p);
    }
    i = 0;
    n = p->count();
    while (i < n)
    {
        StarRec* e = v->mpBegin[i];
        if (e->mChildren.size() == 0)
            p->remove(i);
        else
            i++;
        n = p->count();
    }
    FUN_00b96fa0(p);
}
