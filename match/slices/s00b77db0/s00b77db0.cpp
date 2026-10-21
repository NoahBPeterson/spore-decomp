// Slice s00b77db0 (gold4 #127) -- the Spore "Simulator" object: the big object that owns
// the two spawner hash tables (the same class rearranged in slices s00b76f10 / s00b78880),
// a grid, a set of eastl vectors and an obj list, plus the entry dispatcher that turns a
// game-message hash into a spawned/refreshed set of objects.
//
//   00b77db0  the message dispatcher (hash -> spawn / refresh), also used as a helper by
//             00b783b0's property path
//   00b78020/00b78080  constructors (allocate the object and copy the 3-word descriptor,
//             building the embedded sub-object at +0xc)
//   00b780d0  convex-hull / vector post-processing helper
//   00b781d0  full teardown (release every embedded container)
//   00b783b0  the big per-message switch (plant/species/planet/property handling)
//   00b78860  clear the "dirty" flag and the +0x55a0 field, then tail-call the base update
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (matches the neighbouring slice s00b76f10;
//        no /EHsc: no EH frames in the original)
#include "types.h"

#include <math.h>
#pragma intrinsic(sqrt)

typedef uint32_t u32;
typedef uint8_t  u8;
typedef int32_t  i32;

#define PI(p, off) (*(int*)((char*)(p) + (off)))
#define PU(p, off) (*(u32*)((char*)(p) + (off)))
#define PB(p, off) (*(u8*)((char*)(p) + (off)))
#define PF(p, off) (*(float*)((char*)(p) + (off)))
#define PP(p, off) ((void**)((char*)(p) + (off)))
#define PS(p, off) ((char*)(p) + (off))

// ---- external helpers (named FUN_<va> so difftest resolves relocations by hex) ------------
void* EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  FUN_00b746a0(void* out, void* src);        // 0x00b746a0
void  FUN_00b75240(void* out, void* val, u32 flags);  // 0x00b75240
void  FUN_00b764e0(void* a, int b, int c, int d, int e);  // 0x00b764e0
void  FUN_00b77b60(void* self, int a, int b);    // 0x00b77b60
void  FUN_00b759b0(void* a, void* b);            // 0x00b759b0
void  FUN_00b75b80(void* a, void* b);            // 0x00b75b80
void  FUN_00b75bf0(void* a, void* b);            // 0x00b75bf0
void  FUN_00b73070(void* a, void* b);            // 0x00b73070
void  FUN_00a24480(void* a, void* b);            // 0x00a24480
void  FUN_00b72290();                            // 0x00b72290
void  FUN_00b725a0();                            // 0x00b725a0
void  FUN_00b72560();                            // 0x00b72560
void  FUN_00b72580();                            // 0x00b72580
void* FUN_00b77940(void* a, void* b, void* cmp); // 0x00b77940
void* FUN_00b72dc0(void* a, void* b, void* cmp); // 0x00b72dc0
void* FUN_00921240(void* fn);                    // 0x00921240
void  FUN_00b768d0(void* a, void* b, void* fn);  // 0x00b768d0
int   FUN_00699a10(const float* pts, int n, float* out);  // 0x00699a10  ConvexHull2D
void  FUN_00b72d80(void* a, int b);              // 0x00b72d80
void  FUN_00b72640(u32 mode);                    // 0x00b72640
void  FUN_00b76f10(void* p, u32 hash);           // 0x00b76f10
void  FUN_00b83c40(const float* v, float r, u32 mask, int zero);  // 0x00b83c40
float FUN_00c9eb60();                            // 0x00c9eb60
void* FUN_00b3d3b0();                            // 0x00b3d3b0  SP_PlantManager / table mgr
void* FUN_00b3d420(void* x);                     // 0x00b3d420  species mgr
void* FUN_00b3d320();                            // 0x00b3d320
void* FUN_00b2b1e0(void* x);                     // 0x00b2b1e0
void* FUN_00b90410(void* x);                     // 0x00b90410  cPlantSpeciesManager::GetSpeciesFromID
int   FUN_00b8f860();                            // 0x00b8f860
void* FUN_00b1de80();                            // 0x00b1de80
u32   FUN_00b5b800();                            // 0x00b5b800  SP::GetCurrentGameMode
void* FUN_00b3d300(u32 id);                      // 0x00b3d300  SP::NounManager
void  FUN_00b225d0(void* mgr, u32 id);           // 0x00b225d0  cGameNounManager::RemoveNoun
void  FUN_00704060_grid(void* grid);             // 0x00704060  cHierGrid::Shutdown
void* FUN_00b3d350();                            // 0x00b3d350  SP::PlanetModel
u8    SP_cPropertyList_GetDescription(void* self, u32 id);  // 0x006a25a0 thiscall ret 4
// eastl inlined copy/destroy helpers: same VA as their call sites' inlined bodies; named
// FUN_<va>-style so difftest maps them, but they are header-inlined in the original so we
// model them as local no-ops with the right call shape.
void  FUN_00b764e0_copy(void* a, int b);                 // eastl vector DoDestroyValues
void* FUN_00b77aa0();                                    // 0x00b77aa0 (base update / clear)

// eastl <algorithm>/vector value destroy + copy trampolines (inlined in the original)
static inline void  AutoRef_do_copy(int a, int b, int c) { (void)a; (void)b; (void)c; }
static inline void  AutoRef_do_copy(void* a, int b)       { (void)a; (void)b; }
static inline void  Vertex3D_do_copy(int a, int b, int c) { (void)a; (void)b; (void)c; }
static inline void  Hashtable_DoFreeNodes(int a, int b)   { (void)a; (void)b; }
static inline void  ILogReporter_do_copy(int* a, int* b, int* c) { (void)a; (void)b; (void)c; }

// eastl vector<...,sp_vector_allocator> free/destroy helpers modelled as thiscall members
struct ThVec { void FUN_00b73070(void*, void*); };
// sub-object copier at 0x00b778b0: thiscall(ecx=dst), one stack arg (src), callee-pops
struct ThSub { void FUN_00b778b0(void* src); };
// SpVector<UVector3> (element stride 0xc): erase/resize are thiscall members
struct SpVec {
  void* mpBegin;            // +0
  void* mpEnd;              // +4
  void* FUN_0050f740(void* a, void* b);   // 0x0050f740  SpVector<UVector3>::erase
  void  FUN_00473810(int n);              // 0x00473810  SpVector<UVector3>::resize
};
void FUN_006782c0(void* a, void* b, void* c);   // 0x006782c0 eastl copy_impl (ILogReporter)
void FUN_00720250(void* a, void* b, void* c);   // 0x00720250 CopyVertex3D
// Generic 0x10-byte eastl container {?, beg@+4, end@+8, count@+0xc} with thiscall cleanup helpers
struct Cnt {
  u32   mUnk;               // +0
  void* mBeg;               // +4
  void* mEnd;               // +8
  u32   mCount;             // +0xc
  void FUN_00b759b0(void* end, void* beg);  // 0x00b759b0
  void FUN_00b75b80(void* end, void* beg);  // 0x00b75b80
  void FUN_00b75bf0(void* end, void* beg);  // 0x00b75bf0
  void FUN_00b73070(void* end, void* beg);  // 0x00b73070
  void FUN_00a1b6c0(void* end, void* beg);  // 0x00a1b6c0 hashtable DoFreeNodes
  void FUN_00a24480(void* end, void* beg);  // 0x00a24480 PHTable::FreeBuckets
  void FUN_00704060();                      // 0x00704060 cHierGrid::Shutdown
};
// eastl vector (stride 4) with the two inlined template helpers as members
struct EaVec {
  u32   mUnk;               // +0
  void* mBeg;               // +4
  void* mEnd;               // +8
  void* mCap;               // +0xc
  void* FUN_005f4e10(void* a, void* b, void* c);  // 0x005f4e10 copy_impl::do_copy
  void  FUN_005f3680(void* a, void* b);           // 0x005f3680 vector::DoDestroyValues
};
struct GameNounMgr { void FUN_00b225d0(void* noun); };  // 0x00b225d0 RemoveNoun

// The Simulator: a big object. Only the fields this slice touches are named.
struct Sim {
  u32   pad0[0x20 / 4];
  u32   mFlags;                 // +0x20
  u32   pad24[(0x38 - 0x24) / 4];
  void* mAltBeg;                // +0x38   (hash table A begin)
  void* mAltEnd;                // +0x3c
  void* mAltCap;                // +0x40
  void* mAltCount;              // +0x44
  u32   pad48[(0x2094 - 0x48) / 4];
  void* mMainBeg;               // +0x2094 (hash table B begin)
  void* mMainEnd;               // +0x2098
  void* mMainCap;               // +0x209c
  void* mMainCount;             // +0x20a0
  u32   padA4[(0x40f0 - 0x20a4) / 4];
  void* mObjBegin;              // +0x40f0 (vector<AutoRefCount>)
  void* mObjEnd;                // +0x40f4
  u32   padF8[(0x4908 - 0x40f8) / 4];
  void* mVec4908;               // +0x4908 (vector<Vertex3D>)
  void* mVec490c;               // +0x490c
  u32   pad10[(0x49e4 - 0x4910) / 4];
  void* mHash49e4;              // +0x49e4
  void* mHash49e8;              // +0x49e8
  void* mHash49ec;              // +0x49ec
  u32   padF0[(0x4f34 - 0x49f0) / 4];
  void* mVec4f34;               // +0x4f34
  void* mVec4f38;               // +0x4f38
  void* mVec4f3c;               // +0x4f3c
  u32   pad40[(0x54a8 - 0x4f40) / 4];
  void* mV54a8beg;              // +0x54a8
  void* mV54a8end;              // +0x54ac
  void* mV54a8cap;              // +0x54b0
  void* mV54a8cnt;              // +0x54b4
  u32   padB8[(0x54cc - 0x54b8) / 4];
  void* mV54ccbeg;              // +0x54cc
  void* mV54ccend;              // +0x54d0
  void* mV54cccap;              // +0x54d4
  void* mV54ccc;
  void* mV54ecbeg;              // +0x54ec
  void* mV54ecend;              // +0x54f0
  void* mV54eccap;              // +0x54f4
  u32   padF8b[(0x55a0 - 0x54f8) / 4];
  u32   m55a0;                  // +0x55a0
  void* mpGrid;                 // +0x55a4
  void* mV55a8beg;              // +0x55a8
  void* mV55a8end;              // +0x55ac
  u32   padB0[(0x56c4 - 0x55b0) / 4];
  void* mV56c4beg;              // +0x56c4
  void* mV56c4end;              // +0x56c8
  void* mV56c4cap;              // +0x56cc
  // member methods (ecx = this Sim*), declared here so the compiler emits thiscall
  int FUN_00b780d0(int* param_1, int* param_2);
  u8  FUN_00b783b0(u32 param_2, float* param_3);
  void* FUN_00b78020(void* param_1);   // 0xc74-byte ctor copy
  void* FUN_00b78080(void* param_1);   // 0xc6c-byte ctor copy
};
// free helpers that just happen to write into a Sim*
u8  FUN_00b77db0(void* param_1, u32 param_2);

// @ 0x00b77db0
u8 FUN_00b77db0(void* param_1, u32 param_2) {
  int iVar4 = PI(param_1, 0x10);
  u32 local_2c = PU(param_1, 0x30);
  int iVar8 = PI(param_1, 0x18);
  int iVar6 = PI(param_1, 0x20);
  u8 local_35 = 0;
  bool bVar3 = (param_2 == 0x25630b7) || (param_2 == 0x477c00d) || (param_2 == 0x2e9977e);
  u8 cl = (param_2 == 0x31018b9);
  if (iVar8 == 0) return 0;
  if (iVar8 == (int)0x2ebcd6a6) return 0;
  int local_28;
  int local_24;
  if (bVar3) {
    void* pm = FUN_00b3d3b0();
    int x = (int)FUN_00b2b1e0(pm);
    if (x == 0) return 0;
    void* s = FUN_00b3d420((void*)x);
    void* sp = FUN_00b90410(s);
    if (sp == 0) return 0;
    local_24 = FUN_00b8f860();
    iVar4 = iVar6;
  } else {
    if (!cl) return 0;
    void* tm = FUN_00b3d3b0();
    int iVar5 = PI(tm, 0x17c);
    u32 uVar9 = (PI(tm, 0x180) - iVar5) / 0x24;
    u32 uVar7 = 0;
    if (uVar9 == 0) return 0;
    while ((PI(iVar5, 4) != iVar8) && (PI(iVar5, 8) != iVar8)) {
      ++uVar7;
      iVar5 += 0x24;
      if (uVar9 <= uVar7) return 0;
    }
    if ((PU(iVar5, 0x20) & 1) == 0) return 0;
    local_24 = iVar4 >> 0x1f;
  }
  int local_34[2];
  if (iVar4 != 0 || local_24 != 0) {
    local_35 = 1;
    local_28 = iVar4;
    if ((local_2c & 1) == 0) {
      local_34[0] = PI(PP(param_1, 0x18), 0);  // (reconstructed placeholder for the spilled base)
      local_2c = local_34[0] + 0x38;
      FUN_00b746a0(PS(param_1, 0x14), &local_28);
      int iVar6b = PI(param_1, 0x1c);
      int iVar8b = PI(param_1, 0x20);
      if (iVar8b != PI(param_1, 0x24)) {
        do {
          int* piVar1 = *(int**)(iVar8b + 8);
          if (piVar1 != 0) ((void(__thiscall*)(void*))(*(void***)piVar1)[0])(piVar1);
          int* piVar2 = (int*)piVar1[0x15];
          if (piVar2 != 0) {
            piVar1[0x15] = 0;
            ((void(__thiscall*)(void*))(*(void***)piVar2)[0x38 / 4])(piVar2);
          }
          piVar1[0x16] = 0;
          int stk[3];
          stk[0] = local_24;
          stk[1] = iVar4;
          stk[2] = (int)piVar1;
          ((void(__thiscall*)(void*))(*(void***)piVar1)[0])(piVar1);
          FUN_00b75240(local_34, stk, param_2 & 0xffffff00);
          if (stk[2] != 0) ((void(__thiscall*)(void*))(*(void***)stk[2])[1])((void*)stk[2]);
          ((void(__thiscall*)(void*))(*(void***)piVar1)[1])(piVar1);
          iVar8b = PI(iVar8b, 0x10);
          while (iVar8b == 0) {
            iVar6b += 4;
            iVar8b = PI(iVar6b, 0);
          }
        } while (iVar8b != PI(param_1, 0x24));
      }
      FUN_00b764e0(PS(param_1, 0x14), iVar8b, PI(param_1, 0x1c), PI(param_1, 0x24), PI(param_1, 0x18));
      return 1;
    }
    FUN_00b77b60((void*)(local_34[0] + 0x38), iVar4, local_24);
  }
  return local_35;
}

// @ 0x00b78020
void* Sim::FUN_00b78020(void* param_1) {
  void* r = EAAllocate(0xc74, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (r != 0) {
    PU(r, 0) = PU(param_1, 0);
    PU(r, 4) = PU(param_1, 4);
    PU(r, 8) = PU(param_1, 8);
    ((ThSub*)((char*)r + 0xc))->FUN_00b778b0(PS(param_1, 0xc));
  }
  PU(r, 0xc70) = 0;
  return r;
}

// @ 0x00b78080
void* Sim::FUN_00b78080(void* param_1) {
  void* r = EAAllocate(0xc6c, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (r != 0) {
    PU(r, 0) = PU(param_1, 0);
    ((ThSub*)((char*)r + 4))->FUN_00b778b0(PS(param_1, 4));
  }
  PU(r, 0xc68) = 0;
  return r;
}

// @ 0x00b780d0
int Sim::FUN_00b780d0(int* param_1, int* param_2) {
  int iVar5 = (param_1[1] - *param_1) / 0xc;
  if (0 < iVar5) {
    FUN_00b77940((void*)*param_1, (void*)param_1[1], (void*)FUN_00b72290);
    void* uVar4 = FUN_00b72dc0((void*)*param_1, (void*)param_1[1], (void*)FUN_00b725a0);
    ((SpVec*)param_1)->FUN_0050f740(uVar4, (void*)param_1[1]);
    int iVar5b = param_1[1];
    int iVar1 = *param_1;
    void* f1 = FUN_00921240((void*)FUN_00b72560);
    FUN_00b768d0((void*)iVar1, (void*)iVar5b, f1);
    int iVar2 = param_1[1];
    int iVar3 = *param_1;
    void* f2 = FUN_00921240((void*)FUN_00b72580);
    FUN_00b768d0((void*)iVar3, (void*)iVar2, f2);
    ((SpVec*)param_2)->FUN_00473810((iVar5b - iVar1) / 0xc + 1);
    iVar5 = FUN_00699a10((const float*)*param_1, (param_1[1] - *param_1) / 0xc, (float*)*param_2);
  }
  ((SpVec*)param_2)->FUN_00473810(iVar5);
  return (param_2[1] - *param_2) / 0xc;
}

// @ 0x00b781d0
void __fastcall FUN_00b781d0(void* param_1) {
  // two hashtable-like containers at +0x38 / +0x2094, cleared via FUN_00b77b60 then FUN_00b759b0
  FUN_00b77b60(PS(param_1, 0x38), 0, 0);
  FUN_00b77b60(PS(param_1, 0x2094), 0, 0);
  ((Cnt*)((char*)param_1 + 0x38))->FUN_00b759b0(((Cnt*)((char*)param_1 + 0x38))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x38))->mBeg);
  *(int*)((char*)param_1 + 0x44) = 0;
  ((Cnt*)((char*)param_1 + 0x2094))->FUN_00b759b0(((Cnt*)((char*)param_1 + 0x2094))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x2094))->mBeg);
  *(int*)((char*)param_1 + 0x20a0) = 0;
  ((Cnt*)((char*)param_1 + 0x54a8))->FUN_00b75b80(((Cnt*)((char*)param_1 + 0x54a8))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x54a8))->mBeg);
  *(int*)((char*)param_1 + 0x54b4) = 0;
  ((Cnt*)((char*)param_1 + 0x54c8))->FUN_00b75bf0(((Cnt*)((char*)param_1 + 0x54c8))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x54c8))->mBeg);
  *(int*)((char*)param_1 + 0x54d4) = 0;
  ((Cnt*)((char*)param_1 + 0x54e8))->FUN_00b75bf0(((Cnt*)((char*)param_1 + 0x54e8))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x54e8))->mBeg);
  *(int*)((char*)param_1 + 0x54f4) = 0;
  // eastl vector<AutoRefCount<cMWModel>> at +0x55a8: do_copy + DoDestroyValues
  {
    int beg = PI(param_1, 0x55a8);
    int end = PI(param_1, 0x55ac);
    ((EaVec*)PS(param_1, 0x55a8))->FUN_005f4e10((void*)end, (void*)end, (void*)beg);
    ((EaVec*)PS(param_1, 0x55a8))->FUN_005f3680(((EaVec*)PS(param_1, 0x55a8))->mEnd,
                                                 ((EaVec*)PS(param_1, 0x55a8))->mEnd);
    *(int*)((char*)param_1 + 0x55ac) += ((end - beg) >> 2) * -4;
  }
  ((Cnt*)((char*)param_1 + 0x56c0))->FUN_00b73070(((Cnt*)((char*)param_1 + 0x56c0))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x56c0))->mBeg);
  *(int*)((char*)param_1 + 0x56cc) = 0;
  // eastl vector<Vertex3D> at +0x4908 (stride 0x18): CopyVertex3D + shrink
  {
    int beg = PI(param_1, 0x4908);
    int end = PI(param_1, 0x490c);
    FUN_00720250((void*)end, (void*)end, (void*)beg);
    int d = (end - beg) / 0x18;                     // element count (stride 0x18)
    *(int*)((char*)param_1 + 0x490c) -= d * 0x18;   // end -= count * stride
  }
  ((Cnt*)((char*)param_1 + 0x49e0))->FUN_00a1b6c0(((Cnt*)((char*)param_1 + 0x49e0))->mEnd,
                                                    ((Cnt*)((char*)param_1 + 0x49e0))->mBeg);
  *(int*)((char*)param_1 + 0x49ec) = 0;
  ((Cnt*)((char*)param_1 + 0x4f30))->FUN_00a24480(((Cnt*)((char*)param_1 + 0x4f30))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x4f30))->mBeg);
  *(int*)((char*)param_1 + 0x4f3c) = 0;
  ((Cnt*)((char*)param_1 + 0x55a4))->FUN_00704060();
  {
    int* p = (int*)PI(param_1, 0x40f0);
    int* e = (int*)PI(param_1, 0x40f4);
    if (p != e) {
      do {
        u32 id = (u32)*p;
        ((GameNounMgr*)FUN_00b3d300(id))->FUN_00b225d0((void*)id);
        if (p + 1 < (int*)PI(param_1, 0x40f4))
          FUN_006782c0((void*)(p + 1), (void*)PI(param_1, 0x40f4), (void*)p);
        *(int*)((char*)param_1 + 0x40f4) -= 4;
        int* last = *(int**)PI(param_1, 0x40f4);
        if (*last != 0)
          ((void(__thiscall*)(void*))(*(void***)*last)[1])((void*)*last);
      } while (p != (int*)PI(param_1, 0x40f4));
    }
  }
}

// @ 0x00b783b0
u8 Sim::FUN_00b783b0(u32 param_2, float* param_3) {
  void* pwVar3 = (void*)param_2;
  if ((u32)param_2 < 0x31018ba) {
    if (param_2 != 0x31018b9) {
      if ((u32)param_2 < 0x25630b8) {
        if (param_2 != 0x25630b7) {
          if (param_2 == 0xf62def) {
            float fVar9 = param_3[4];
            float fVar1 = param_3[6];
            void* iVar5 = FUN_00b3d320();
            if (iVar5 != 0) {
              u32 gm = FUN_00b5b800();
              switch (gm) {
                case 0x1654c01: case 0x1654c02: case 0x1654c04:
                case 0x1654c05: case 0x1654c06: case 0x1654c08: {
                  FUN_00b3d320();
                  void* p = FUN_00b1de80();
                  if (p != 0 && PF(p, 8) == fVar1 && PF(p, 0x10) == fVar9) {
                    u32 m = FUN_00b5b800();
                    FUN_00b72640(m);
                    return 0;
                  }
                }
              }
            }
          } else if (param_2 == 0x0182c582) {
            float local[4];
            FUN_00b746a0(&local[0], (void*)0x01464fe0);
            float* local_8 = &local[0];
            if (local[0] != local[2]) {
              do {
                int iVar5 = *(int*)(local_8 + 2);
                if (iVar5 != 0) {
                  int iVar7 = PI((void*)iVar5, 0x70);
                  if (iVar7 != 0) {
                    PI((void*)iVar5, 0x38) = PI((void*)iVar7, 0xc);
                    PI((void*)iVar5, 0x3c) = PI((void*)iVar7, 0x10);
                    PI((void*)iVar5, 0x40) = PI((void*)iVar7, 0x14);
                  }
                }
                FUN_00b72d80(&local[0], 0);
              } while (local_8 != &local[2]);
              return 0;
            }
          }
          return 0;
        }
      } else if (param_2 != 0x2e9977e) {
        return 0;
      }
    }
LAB_00b78500:
    if (((PU(this, 0x20) & 1) != 0) &&
        ((param_2 != 0x2e9977e) || (((PU(this, 0x20) >> 1) & 1) != 0))) {
      if (param_3[2] != 0.0f) {
        FUN_00b76f10(param_3, param_2);
        return 1;
      }
      FUN_00b77db0(this, param_2);
    }
    return 1;
  }
  if (param_2 != 0x32f76e7) {
    if (param_2 == 0x477c00d) goto LAB_00b78500;
    if (param_2 != 0x4d80d9e) return 0;
  }
  float local_8 = param_3[2];
  if (local_8 == 0.0f) return 0;
  float fVar9 = param_3[6];
  float local_18 = param_3[0];
  u8 cVar4 = SP_cPropertyList_GetDescription((void*)0x015fd918, 0x4233e37);
  if (cVar4 == 0) return 0;
  float* param_3b = 0;
  float local_24 = 0.0f;
  void* param_2b = 0;
  void* tm = FUN_00b3d3b0();
  int iVar5 = PI(tm, 0x17c);
  u32 uVar2 = (PI(tm, 0x180) - iVar5) / 0x24;
  u32 uVar11 = 0;
  if (3 < (int)uVar2) {
    int iVar7 = ((uVar2 - 4) >> 2) + 1;
    float* pfVar10 = (float*)(iVar5 + 0xc);
    float* pfVar8 = (float*)(iVar5 + 0x30);
    uVar11 = iVar7 * 4;
    do {
      if (pwVar3 == (void*)0x32f76e7) {
        if (pfVar10[-1] == fVar9) {
LAB_00b78630:
          param_3b = (float*)(uintptr_t)*(u32*)&pfVar10[1];
          local_24 = pfVar10[2];
          param_2b = (void*)(uintptr_t)*(u32*)&pfVar10[3];
LAB_00b78651:
          if (pwVar3 == (void*)0x32f76e7) goto LAB_00b78659;
          if (pwVar3 == (void*)0x4d80d9e) goto LAB_00b78668;
          goto LAB_00b7868d;
        }
LAB_00b78659:
        if (pfVar8[-1] == fVar9) goto LAB_00b7866c;
LAB_00b78695:
        if (pfVar8[8] != fVar9) {
LAB_00b786d2: {
          float fVar1 = pfVar8[0x11];
          if (fVar1 == fVar9) {
            param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[0x13];
            local_24 = pfVar8[0x14];
            param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[0x15];
          }
          goto done;
        }
        }
LAB_00b786a9:
        param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[10];
        local_24 = pfVar8[0xb];
        param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[0xc];
LAB_00b786ca:
        if (pwVar3 == (void*)0x32f76e7) goto LAB_00b786d2;
        if (pwVar3 == (void*)0x4d80d9e) {
          float fVar1 = pfVar8[0x12];
          if (fVar1 == fVar9) {
            param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[0x13];
            local_24 = pfVar8[0x14];
            param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[0x15];
          }
        }
      } else {
        if (pwVar3 != (void*)0x4d80d9e) goto LAB_00b78651;
        if (*pfVar10 == fVar9) goto LAB_00b78630;
LAB_00b78668:
        if (*pfVar8 == fVar9) {
LAB_00b7866c:
          param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[1];
          local_24 = pfVar8[2];
          param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[3];
LAB_00b7868d:
          if (pwVar3 == (void*)0x32f76e7) goto LAB_00b78695;
          if (pwVar3 == (void*)0x4d80d9e) goto LAB_00b786a4;
          goto LAB_00b786ca;
        }
LAB_00b786a4:
        if (pfVar8[9] == fVar9) goto LAB_00b786a9;
        {
          float fVar1 = pfVar8[0x12];
          if (fVar1 == fVar9) {
            param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[0x13];
            local_24 = pfVar8[0x14];
            param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[0x15];
          }
        }
      }
done:
      pfVar10 += 0x24;
      pfVar8 += 0x24;
      iVar7 = iVar7 - 1;
    } while (iVar7 != 0);
  }
  if (uVar11 < uVar2) {
    float* pfVar10 = (float*)(iVar5 + 0xc + uVar11 * 0x24);
    int iVar5b = uVar2 - uVar11;
    do {
      if (pwVar3 == (void*)0x32f76e7) {
        float fVar1 = pfVar10[-1];
        if (fVar1 == fVar9) {
          param_3b = (float*)(uintptr_t)*(u32*)&pfVar10[1];
          local_24 = pfVar10[2];
          param_2b = (void*)(uintptr_t)*(u32*)&pfVar10[3];
        }
      } else if (pwVar3 == (void*)0x4d80d9e) {
        float fVar1 = *pfVar10;
        if (fVar1 == fVar9) {
          param_3b = (float*)(uintptr_t)*(u32*)&pfVar10[1];
          local_24 = pfVar10[2];
          param_2b = (void*)(uintptr_t)*(u32*)&pfVar10[3];
        }
      }
      pfVar10 += 9;
      iVar5b = iVar5b - 1;
    } while (iVar5b != 0);
  }
  FUN_00b3d350();
  if ((float)(uintptr_t)param_3b <= 0.0f) return 0;
  if (local_18 == 0.0f) return 0;
  float* pfVar10 = (float*)((int)local_8 + 0xc);
  float fVar9b = local_18;
  do {
    float l18 = pfVar10[-2];
    float l14 = pfVar10[-1];
    float l10 = pfVar10[0];
    float l8 = pfVar10[1];
    FUN_00b83c40(&l18,
                 l8 * (float)(uintptr_t)param_3b +
                 (float)sqrt((double)((l10 * l10 + l14 * l14) + l18 * l18)) * 0.00390625f,
                 0x10000000, 0);
    float fVar12 = FUN_00c9eb60();
    if (fVar12 <= (float)(uintptr_t)param_2b) {
      FUN_00b83c40(&l18, l8 * local_24, 0x20000000, 0);
    }
    pfVar10 += 0x13;
    fVar9b = (float)((int)fVar9b - 1);
  } while (fVar9b != 0.0f);
  return 0;
}

// @ 0x00b78860
void __fastcall FUN_00b78860(void* param_1) {
  PU(param_1, 0x20) = PU(param_1, 0x20) & 0xfffffffb;
  PU(param_1, 0x55a0) = 0;
  FUN_00b77aa0();
}
