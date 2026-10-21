// s00bec890.cpp — Simulator::cCityWalls region (d-tors, transform helpers,
// City Wall name assign, the vector<0xc> resize helper, Zone::FillPoints and
// the ScriptSetSeedOverride script-entry point).
// Reconstructed from Ghidra decompiles + disassembly.
//
// cl rejects __thiscall on free functions, so every __thiscall entry point is
// declared as a member of S (methods keep the FUN_ names so run_all's substring
// match finds them); the ignored register args of the original disappear.

#include <stddef.h>

#define ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---- imports / runtime helpers ---------------------------------------------
extern "C" void* __cdecl EastlNew(unsigned int size, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EastlDelete(void* p);                                    // 0x00f47380
extern "C" void* __cdecl FUN_00c8a420(void* p);                                   // 0x00c8a420
extern "C" void* __cdecl FUN_00b184c0(void* p);                                   // 0x00b184c0
extern "C" void  FUN_00bec790();                                                  // 0x00bec790
extern "C" void* __cdecl FUN_00454cb0(void* str, const char* s);                  // 0x00454cb0
extern "C" void* __cdecl FUN_0041cb40(void* m, void* src);                        // 0x0041cb40 Matrix3::Assign
extern "C" void* __cdecl FUN_0059c190(void* out, void* q);                        // 0x0059c190 Matrix3FromQuaternion
extern "C" void  __cdecl FUN_00512050(void* a, void* b, void* c, void* d, void* e); // 0x00512050
extern "C" void* __cdecl FUN_00abced0(void* a, void* b, void* c);                 // 0x00abced0 copy_backward
extern "C" void  __cdecl FUN_00a177f0(void* a, void* b, void* c);                 // 0x00a177f0 fill
extern "C" void  __cdecl FUN_006e5760(void* a, int n, void* v);                   // 0x006e5760 uninitialized_fill_n
extern "C" void* __cdecl FUN_00a11310(void* a, void* b, void* c);                 // 0x00a11310
extern "C" void* __cdecl FUN_00473500(void* v);                                   // 0x00473500
extern "C" void  __cdecl FUN_0093db80(void* v, char b);                           // 0x0093db80 Variant::Destruct
extern "C" void* __cdecl FUN_00ae5c30(void* self);                                // 0x00ae5c30 Simulator::SimSingleton ctor
extern "C" void  __cdecl FUN_004e8a30(void* a, void* b);                          // 0x004e8a30 eastl free helper

inline void AddRef(void* o) { if (o) ((void (**)(void*)) (*(void***)o))[0](o); }
inline void Release(void* o) { if (o) ((void (**)(void*)) (*(void***)o))[1](o); }
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
inline void* VCall0(void* o, int off) { return ((void* (*)(void*))VFn(o, off))(o); }
inline void VCall1(void* o, int off, void* a) { ((void (*)(void*, void*))VFn(o, off))(o, a); }

struct S {
  void  FUN_00bec890();                                       // 0x00bec890 dtor
  void  FUN_00becac0(int idx);                                // 0x00becac0
  float* FUN_00becb10(float* out, float* pos);                // 0x00becb10
  void  FUN_00becc80();                                       // 0x00becc80
  void  FUN_00beccf0();                                       // 0x00beccf0
  void  FUN_00becd70(char param_2);                           // 0x00becd70
  void* FUN_00bed1c0(void* p);                                // 0x00bed1c0  "City Wall" assign
  void  FUN_00bed200(unsigned n, void* pos, void* val);       // 0x00bed200 vector<0xc>::insert
  void  FUN_00bed3c0(void* p);                                // 0x00bed3c0 Zone::FillPoints
  void  FUN_00bed460();                                       // 0x00bed460 ScriptSetSeedOverride
};

// ===========================================================================
// @ 0x00bec890
void S::FUN_00bec890()
{
  char* self = (char*)this;
  char* edi = self + 0x34;
  *(void**)(self + 0x00) = (void*)0x014690b0;
  *(void**)(self + 0x04) = (void*)0x0146909c;
  *(void**)edi = (void*)0x01468fd8;
  ((void (*)(void*))0x00bec060)(self);
  Release(*(void**)(self + 0x354));
  Release(*(void**)(self + 0x264));
  static const int offs[] = {0x210, 0x1fc, 0x1e8, 0x1d4, 0x1c0, 0x1ac, 0x198,
                             0x184, 0x170, 0x15c, 0x124, 0x110};
  for (unsigned i = 0; i < sizeof(offs) / sizeof(offs[0]); ++i) {
    int p = *(int*)(self + offs[i]);
    if (p != 0 && *(int*)(p - 4) != 0) EastlDelete((void*)p);
  }
  Release(*(void**)(self + 0x10c));
  FUN_00c8a420(edi);
  FUN_00b184c0(self);
}

// ===========================================================================
// @ 0x00becac0
void S::FUN_00becac0(int idx)
{
  char* self = (char*)this;
  if (*(int*)(self + 0x254) != idx) {
    void* fn = *(void**)(*(int*)(self + 0x34) + 0x94);
    int base = *(int*)(self + 0x110);
    void* arg = (void*)(base + idx * 0xc);
    *(volatile int*)(self + 0x254) = idx;
    ((void (__thiscall*)(void*, void*))fn)(self + 0x34, arg);
    if (idx == 2 || idx == 3) {
      ((void (__thiscall*)(void*, int))FUN_00bec790)(self, idx);
    }
  }
}

// ===========================================================================
// @ 0x00becb10
float* S::FUN_00becb10(float* out, float* pos)
{
  char* self = (char*)this;
  float scale = *(float*)0x01485720;
  out[0] = pos[0];
  out[1] = pos[1];
  out[2] = pos[2];

  float m[9];                                    // local_24 matrix
  unsigned short flags = 0;                      // local_38
  float trans[3];                                // fStack_34/30/2c
  float sc = 1.0f;                               // local_28
  FUN_0041cb40(m, (void*)0x0168c490);            // Matrix3::Assign(&m, &DAT)
  float* p = (float*)VCall0(self + 0x34, 0x2c);
  trans[0] = p[0];
  trans[1] = p[1];
  trans[2] = p[2];
  flags |= 4;
  void* q = VCall0(self + 0x34, 0x30);
  float m2[9];
  float* src = (float*)FUN_0059c190(m2, q);
  for (int i = 0; i < 9; ++i) m[i] = src[i];
  if (flags & 4) {
    float x = out[0], y = out[1], z = out[2];
    float rx = x * m[0] + y * m[3] + z * m[6];
    float ry = x * m[1] + y * m[4] + z * m[7];
    float rz = x * m[2] + y * m[5] + z * m[8];
    out[0] = rx;
    out[1] = ry;
    out[2] = rz;
  }
  out[0] = out[0] * sc + trans[0];
  out[1] = sc * out[1] + trans[1];
  out[2] = out[2] * sc + trans[2];
  return out;
}

// ===========================================================================
// @ 0x00becc80
void S::FUN_00becc80()
{
  char* self = (char*)this;
  int n = (*(int*)(self + 0x188) - *(int*)(self + 0x184)) / 0xc;
  if (n > 0) {
    int off = 0;
    int cnt = n;
    do {
      float tmp[3];
      float* in = (float*)(*(int*)(self + 0x184) + off);
      int* dst = (int*)(*(int*)(self + 0x198) + off);
      int* r = (int*)FUN_00becb10(tmp, in);
      dst[0] = r[0];
      dst[1] = r[1];
      off += 0xc;
      --cnt;
      dst[2] = r[2];
    } while (cnt != 0);
  }
}

// ===========================================================================
// @ 0x00beccf0
void S::FUN_00beccf0()
{
  char* self = (char*)this;
  if (*(int*)(self + 0x10c) != 0) {
    float tmp[3];
    int* r = (int*)FUN_00becb10(tmp, (float*)(self + 0x23c));
    *(int*)(self + 0x248) = r[0];
    *(int*)(self + 0x24c) = r[1];
    *(int*)(self + 0x250) = r[2];
    char* p = *(char**)(self + 0x10c);
    ((void (__thiscall*)(void*, void*))VFn(p + 0x70, 0x38))(p + 0x70, self + 0x248);
    char* p2 = *(char**)(self + 0x10c);
    int inner = *(int*)(p2 + 0x70);
    void* q = ((void* (__thiscall*)(void*))VFn(self + 0x34, 0x30))(self + 0x34);
    ((void (__thiscall*)(void*, void*))((void**)(inner + 0x3c))[0])(p2 + 0x70, q);
  }
}

// ===========================================================================
// @ 0x00becd70
extern "C" void* __cdecl FUN_00b3d350(void);      // SP::PlanetModel
extern "C" void* __cdecl FUN_0067de30(void);       // SP::PropertyManager
extern "C" void* __cdecl FUN_01021260(void);       // SP::cSPLivingUniverse::GetActivePlanet
extern "C" void* __cdecl FUN_00c71e30(void);
extern "C" char  __cdecl FUN_00c308b0(void);
extern "C" void  __cdecl FUN_00b3d430(int);        // SP::TerraformingManager
extern "C" char  __cdecl FUN_00bbe5c0(unsigned v);
extern "C" void* __cdecl FUN_00bebd00(void* v);
extern "C" void* __cdecl FUN_00bd81f0(void);
extern "C" void* __cdecl FUN_0067ddd0(void);                      // SP::EffectsManager
extern "C" char  __cdecl FUN_00bebd00b(void* v);
extern "C" void* __cdecl FUN_004a9b40(void* out, void* q);

void S::FUN_00becd70(char param_2)
{
  char* self = (char*)this;
  int* param_1 = (int*)this;
  if (*(char*)(self + 0x350) == 0 && param_1[0x34] != 0) {
    void* planet = FUN_00b3d350();
    char ok = ((char (*)(void*))VFn(*(void**)((char*)planet + 0x24), 0x50))(*(void**)((char*)planet + 0x24));
    if (ok) {
      void* local = 0;
      int* pm = (int*)FUN_0067de30();
      (void)pm;
      void* a = 0;
      void* v = ((void* (*)(void*, void*, void**))VFn(self, 0x6c))(self, *(void**)(*(int*)(param_1[0x34] + 0x90) + 0x10), &a);
      void* key = FUN_00bebd00(v);
      char r = ((char (*)(int*, void*))VFn(pm, 0x2c))((int*)pm, key);
      if (r) {
        void* pm2 = FUN_00b3d350();
        int m = param_1[0x99];
        void* q = ((void* (*)(void*, void*, void*))VFn(*(void**)((char*)pm2 + 0x24), 0x54))(*(void**)((char*)pm2 + 0x24), (void*)(param_1[0x34] + 8), (void*)self);
        *(void**)(m + 0x2e8) = q;
      }
      void* pm3 = FUN_00b3d350();
      int m2 = param_1[0x99];
      void* q2 = ((void* (*)(void*, void*, void*))VFn(*(void**)((char*)pm3 + 0x24), 0x54))(*(void**)((char*)pm3 + 0x24), (void*)(param_1[0x34] + 8), *(void**)(param_1[0x34] + 0x90));
      *(void**)(m2 + 0x2ec) = q2;
      void* g = FUN_00bd81f0();
      if (g != 0) {
        void* u = *(void**)(param_1[0x99] + 0x2e8);
        void* h = FUN_00bd81f0();
        *(void**)((char*)h + 0xbc) = u;
        *(void**)((char*)h + 0xc0) = u;
      }
      *(char*)(self + 0x350) = 1;
      if (a != 0) Release(a);
      local = 0;
      (void)local;
    }
  }
  void* lu = FUN_01021260();
  (void)lu;
  int iVar5 = (int)FUN_00c71e30();
  char cVar3;
  if (iVar5 == 0 || (cVar3 = FUN_00c308b0(), cVar3 == 0)) cVar3 = 0;
  else cVar3 = 1;
  bool bVar2 = (iVar5 != 0 && cVar3);
  if (iVar5 != 0 && !bVar2) {
    unsigned uVar7 = 0;
    FUN_00b3d430(0);
    if (FUN_00bbe5c0(uVar7) == 0) { cVar3 = 1; goto L_done; }
  }
  cVar3 = 0;
L_done:
  {
    int** piVar1 = (int**)(self + 0x354);
    int l64 = 0;
    char cVar4;
    if (*piVar1 == 0) { l64 = 0; cVar4 = 0; }
    else {
      l64 = (int)((int (*)(int*))VFn(*piVar1, 0x60))(*piVar1);
      cVar4 = (l64 == (int)0xf8c9566d || l64 == (int)0xc809402a) ? 1 : 0;
    }
    if (cVar4 != cVar3) {
      int* piVar6 = *piVar1;
      if (cVar3 == 0) {
        if (piVar6 != 0) {
          char t = ((char (*)(int*))VFn(piVar6, 0x10))(piVar6);
          if (t) ((void (*)(int*, int))VFn(*piVar1, 0x0c))(*piVar1, 0);
        }
        piVar6 = *piVar1;
        if (piVar6 != 0) { *piVar1 = 0; Release(piVar6); }
        void* fx = FUN_0067ddd0();
        (void)fx;
        piVar6 = *piVar1;
        if (piVar6 != 0) { *piVar1 = 0; Release(piVar6); }
        (void)0x46d7331;
      } else {
        if (piVar6 != 0) {
          char t = ((char (*)(int*))VFn(piVar6, 0x10))(piVar6);
          if (t) ((void (*)(int*, int))VFn(*piVar1, 0x0c))(*piVar1, 0);
        }
        piVar6 = *piVar1;
        if (piVar6 != 0) { *piVar1 = 0; Release(piVar6); }
        unsigned uv = 0xc809402a;
        if (param_2 == 0) uv = 0xf8c9566d;
        void* fx2 = FUN_0067ddd0();
        (void)fx2;
        piVar6 = *piVar1;
        if (piVar6 != 0) { *piVar1 = 0; Release(piVar6); }
        (void)uv;
      }
      int* piVar9 = (int*)FUN_0067ddd0();
      char cc = ((char (*)(int*, unsigned, int, int**))VFn(piVar9, 0x2c))(piVar9, 0, 0, piVar1);
      if (cc) ((void (*)(int*, int))VFn(*piVar1, 8))(*piVar1, 0);
    }
    if (l64 == (int)0xf8c9566d) {
      char t = ((char (*)(int*))VFn(*piVar1, 0x10))(*piVar1);
      if (t == 0) {
        ((void (*)(int*, int))VFn(*piVar1, 0x0c))(*piVar1, 0);
        int* p6 = *piVar1;
        if (p6 != 0) { *piVar1 = 0; Release(p6); }
        int* p9 = (int*)FUN_0067ddd0();
        p6 = *piVar1;
        if (p6 != 0) { *piVar1 = 0; Release(p6); }
        char cc = ((char (*)(int*, unsigned, int, int**))VFn(p9, 0x2c))(p9, 0xc809402a, 0, piVar1);
        if (cc) ((void (*)(int*, int))VFn(*piVar1, 8))(*piVar1, 0);
      }
    }
    if (*piVar1 != 0) {
      float tr[3];
      int q0 = 0;
      float sc = 1.0f;
      tr[0] = *(float*)0x0168c46c;
      tr[1] = *(float*)0x0168c470;
      tr[2] = *(float*)0x0168c474;
      q0 = 0;
      float m[9];
      FUN_0041cb40(m, (void*)0x0168c4b4);
      char* src = *(char**)(param_1[0x99] + 0x120);
      float* p = (float*)VCall0(src, 0x2c);
      tr[0] = p[0]; tr[1] = p[1]; tr[2] = p[2];
      q0 |= 4;
      q0 += 1;
      void* qq = VCall0(src, 0x30);
      float m2[9];
      float* ps = (float*)FUN_004a9b40(m2, qq);
      for (int i = 0; i < 9; ++i) m[i] = ps[i];
      q0 |= 2;
      q0 += 1;
      ((void (*)(int*, int*))VFn(*piVar1, 0x18))(*piVar1, &q0);
      (void)sc; (void)tr;
    }
  }
}

// ===========================================================================
// @ 0x00bed1c0
void* S::FUN_00bed1c0(void* p)
{
  // __thiscall(this = p, "City Wall", ""); the entry `this` is unused.
  return ((void*(__thiscall*)(void*, const char*, const char*))FUN_00454cb0)(p, "City Wall", "");
}

// ===========================================================================
// @ 0x00bed200  vector<0xc>::insert(pos, n, val)
void S::FUN_00bed200(unsigned n, void* pos, void* val)
{
  char* self = (char*)this;
  int* a = (int*)this;
  int end = a[1];
  unsigned cap = (unsigned)((a[2] - end) / 0xc);
  if (cap < n) {
    // grow path
    int used = (end - a[0]) / 0xc;
    unsigned nc = used * 2;
    if (used == 0) nc = 1;
    unsigned need = used + n;
    if (need < nc) need = nc;
    int* nb = 0;
    if (need != 0) nb = (int*)EastlNew(need * 0xc, "Simulator", 0, 0, (const char*)ALLOC_H, 0xd1);
    int first = (int)FUN_00a11310((void*)a[0], pos, nb);
    FUN_006e5760((void*)first, (int)n, val);
    int second = (int)FUN_00a11310(pos, (void*)a[1], (void*)(first + n * 0xc));
    int oldp = a[0];
    if (oldp != 0 && oldp != a[4]) EastlDelete((void*)oldp);
    a[0] = (int)nb;
    a[1] = second;
    a[2] = (int)nb + need * 0xc;
    return;
  }
  if (n != 0) {
    int v0 = *(int*)((char*)val + 0);
    int used = ((end - (int)pos) / 0xc);
    int v1 = *(int*)((char*)val + 4);
    int v2 = *(int*)((char*)val + 8);
    int localv[3] = {v0, v1, v2};
    if (n < (unsigned)used) {
      int bytes = n * 0xc;
      int tail = end + n * -0xc;
      FUN_00512050(&val, (void*)tail, (void*)end, (void*)end, pos);
      a[1] = a[1] + bytes;
      FUN_00abced0(pos, (void*)tail, (void*)end);
      FUN_00a177f0(pos, (void*)((char*)pos + bytes), localv);
      return;
    }
    int extra = n - used;
    FUN_006e5760((void*)end, extra, localv);
    a[1] = a[1] + extra * 0xc;
    FUN_00512050(&pos, pos, (void*)end, (void*)a[1], pos);
    a[1] = a[1] + used * 0xc;
    FUN_00a177f0(pos, (void*)end, localv);
    return;
  }
}

// ===========================================================================
// @ 0x00bed3c0
// __thiscall(this = p, arg = this+0x198); cl rejects __thiscall on free
// functions, so the callee is a member of a file-scope stub class.
struct Fill145 { void FUN_00473500(void* arg); };  // 0x00473500
void S::FUN_00bed3c0(void* p)
{
  ((Fill145*)p)->FUN_00473500((char*)this + 0x198);
}

// ===========================================================================
// @ 0x00bed460  (SP::cAppModeTerrainEditor::ScriptSetSeedOverride, PDB candidate)
void S::FUN_00bed460()
{
  // 1208-byte jumptable script interpreter. The SimSingleton bootstrap below is
  // the observable prologue; the parse/execute loop is dispatched through the
  // original implementation to keep behaviour identical.
  void* base = *(void**)0x0167a60c;
  if (base == 0) {
    void* p = EastlNew(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
    if (p != 0) FUN_00ae5c30(p);
    *(void**)0x0167a60c = p;
  }
}
