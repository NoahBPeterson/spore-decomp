// s00b8f230.cpp — Simulator::cPlantCargoInfo / cSpaceInventoryItem /
// cGonzagoSubsystem rbtree region, plus the Simulator package loader.
// Reconstructed from Ghidra decompiles + disassembly.
//
// cl rejects __thiscall on free functions, so every __thiscall entry point is
// declared as a member of S (methods keep the FUN_ names so run_all's substring
// match finds them); the ignored register args of the original disappear.

#include <stddef.h>

#define ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---- cdecl / stdcall runtime helpers ---------------------------------------
extern "C" void* __cdecl EastlNew(unsigned int size, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EastlDelete(void* p);                                             // 0x00f47380
extern "C" void  __cdecl FUN_0093b8e0(void* stream, int len);                              // 0x0093b8e0
extern "C" void* __cdecl EA_ZoneNew(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00926020
extern "C" int   __cdecl FUN_00693cd0(void* db, int a, int b, int c);                      // 0x00693cd0
extern "C" int   __cdecl FUN_00693d60(void* db, int a, int b, int c);                      // 0x00693d60
extern "C" void  __cdecl FUN_00692ea0(void);                                               // 0x00692ea0
extern "C" void  __cdecl FUN_00692ec0(void* p);                                            // 0x00692ec0
extern "C" void  __cdecl FUN_00693900(void);                                               // 0x00693900
extern "C" void* __cdecl PropertyManager(void);                                            // 0x0067de30
extern "C" void  __cdecl FUN_006a1250(void* src, unsigned int id, void* out);              // 0x006a1250
extern "C" int   __cdecl FUN_00c87660(void* self);                                         // 0x00c87660
extern "C" int   __cdecl FUN_00c87770(void* self);                                         // 0x00c87770
extern "C" void* __cdecl FUN_00c870b0(void* dst, void* src);                               // 0x00c870b0
extern "C" char  __cdecl FUN_00c87580(void* stream);                                       // 0x00c87580
extern "C" char  __cdecl FUN_00c879a0(void* stream);                                       // 0x00c879a0
extern "C" void* __cdecl FUN_00401090(void* key);                                          // 0x00401090
extern "C" void* __cdecl FUN_004df440(void* mgr, void* key);                               // 0x004df440
extern "C" void* __cdecl FUN_00ac0d80(void* first, void* last, void* key);                 // 0x00ac0d80
extern "C" void* __cdecl FUN_010212a0(void);                                               // 0x010212a0
extern "C" void* __cdecl FUN_0093aa70(void* stream, void* data, int n, int a);             // 0x0093aa70
extern "C" void* __cdecl FUN_0093a780(void* stream, void* data, int n, int a);             // 0x0093a780
extern "C" void* __cdecl FUN_00692f90(void* self, void* a, void* b, unsigned c);           // 0x00692f90
extern "C" char  __cdecl FUN_00692900(void* self, void* stream);                           // 0x00692900
extern "C" char  __cdecl FUN_00693e10(void* self, void* stream);                           // 0x00693e10
extern "C" void* __cdecl FUN_00d9a1b0(void* self);                                         // (ununsed placeholder)
extern "C" void* __cdecl FUN_00b1f9c0(void* item);                                         // 0x00b1f9c0
extern "C" void  __cdecl FUN_004da3a0(void* key);                                          // 0x004da3a0
extern "C" float* __cdecl FUN_0041ea70(void* prop);                                        // 0x0041ea70
extern "C" void  __cdecl FUN_00b8fc10(void** out, void* pos, void* key, int b);            // 0x00b8fc10 (thiscall-ish; ECX=tree)
extern "C" void  __cdecl FUN_00b8fc80(void* out, void* key, unsigned b);                   // 0x00b8fc80
extern "C" void* __cdecl FUN_00b8e180(void);                                               // 0x00b8e180
extern "C" void  __cdecl FUN_00b8eaa0(void* p);                                            // 0x00b8eaa0
extern "C" void  __cdecl FUN_00b8db70(void* p);                                            // 0x00b8db70

// ---- virtual dispatch helpers ----------------------------------------------
struct RCObj { virtual void AddRef(); virtual void Release(); };
inline void AddRef(void* o) { if (o) ((RCObj*)o)->AddRef(); }
inline void Release(void* o) { if (o) ((RCObj*)o)->Release(); }
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }

struct RBNode { RBNode* pxRight; RBNode* pxLeft; RBNode* pxParent; int mColor; };

static void CopyBytes(void* dst, const void* src, unsigned n) {
  char* d = (char*)dst; const char* s = (const char*)src;
  for (unsigned i = 0; i < n; i++) d[i] = s[i];
}

// eastl rbtree<Key, pair<Key,void*>> model: node { right, left, parent, color,
// =0x10 key.lo, =0x14 key.hi, =0x18 key.group, =0x1c value }
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

// eastl rbtree base layout (see s00b2c980 notes): anchor at +4, root at +0xc,
// size at +0x14.
struct RBTree {
  char pad[4];
  TreeNode anchor;        // +4 .. +0x13 (anchor.left/right used as sentinel)
  TreeNode* root;         // +0xc
  char pad2[4];
  int count;              // +0x14
};

// ---- Simulator::cPlantCargoInfo (size 0xa4) --------------------------------
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

// Simulator package loader (cdecl, 4 stack args).
extern "C" char __cdecl FUN_00b8f230(void* param, void* a, void* b, void* c);   // 0x00b8f230
extern "C" char __cdecl FUN_00b8f470(void* param, void* a, void* b, void* c);   // 0x00b8f470
extern "C" void FUN_00b8fd90();                                                    // 0x00b8fd90
extern "C" void FUN_00b5b960();                                                    // 0x00b5b960
extern "C" void FUN_00b5b9a0();                                                    // 0x00b5b9a0

// ===========================================================================
// @ 0x00b8f230
char __cdecl FUN_00b8f230(void* param, void* a, void* b, void* c)
{
  (void)a; (void)b; (void)c;
  void* buf = EastlNew(50000, "Simulator", 0, 0, 0, 0);
  char* stream = (char*)param;
  char* io = (char*)((void* (*)(void*))VFn(stream, 0x18))(stream);   // param->vfn[0x18]() -> stream
  unsigned readv = 0;
  FUN_0093a780(io, &readv, 1, 0);         // ReadInt32(io, &local, 1, 0)
  int len = (int)((int (*)(void*))VFn(io, 0x1c))(io);
  ((void (*)(void*, int))VFn(io, 0x30))(io, len);

  int zu = 0;
  void* mem = EA_ZoneNew(0x18, "App/memorystream", 0, 0, 0, 0);
  if (mem) { mem = (void*)((void* (*)(void*, int))0x00d9a1b0)(mem, 0); }

  int l2 = (int)((int (*)(void*))VFn(stream, 0x1c))(stream);
  FUN_0093b8e0(buf, l2);
  ((void (*)(void*, int))VFn(mem, 0x28))(mem, 0);
  zu = 0;

  void* dpf = EA_ZoneNew(0x388, "Simulator", 0, 0, 0, 0);
  if (dpf) { dpf = (void*)((void* (*)(void*, int, int))0x008d9f80)(dpf, 0, 0); }

  void* odb = EA_ZoneNew(0x24, "Simulator", 0, 0, 0, 0);
  if (odb) { odb = (void*)((void* (*)(void*, void*))0x0069fa60)(odb, dpf); }

  ((void (*)(void*, void*, int))VFn(dpf, 0x50))(dpf, mem, 0);
  ((void (*)(void*, int, int))VFn(odb, 0x3c))(odb, 1, 0);
  ((void (*)(void*, int))VFn(odb, 0x20))(odb, zu);
  FUN_00693cd0(odb, 1, 1, 1);
  FUN_00692ea0();
  FUN_00692ec0(0);

  void* res = EA_ZoneNew(0x1b0, "Simulator", 0, 0, 0, 0);
  if (res) res = FUN_00b8e180();
  *(void**)b = res;                         // *unaff_EBP = res
  ((void (*)(void*))VFn(res, 0))(res);
  FUN_00b8eaa0(0);
  FUN_00693900();
  ((void (*)(void*))VFn(odb, 0x1c))(odb);
  ((void (*)(void*))VFn(odb, 0x08))(odb);
  EastlDelete(0);
  ((void (*)(void*))VFn(odb, 0x04))(odb);
  ((void (*)(void*))VFn(dpf, 0x04))(dpf);
  ((void (*)(void*))VFn(mem, 0x08))(mem);
  return 1;
}

// ===========================================================================
// @ 0x00b8f470
char __cdecl FUN_00b8f470(void* param, void* a, void* b, void* c)
{
  (void)a; (void)b; (void)c;
  void* buf = EastlNew(50000, "Simulator", 0, 0, 0, 0);
  char* stream = (char*)param;
  int* io = (int*)VFn(stream, 0x18);
  (void)io;

  void* mem = EA_ZoneNew(0x18, "App/memorystream", 0, 0, 0, 0);
  if (mem) { mem = (void*)((void* (*)(void*, int))0x00d9a1b0)(mem, 0); }

  FUN_0093b8e0(buf, 50000);
  ((void (*)(int))VFn(mem, 0x20))(0);
  ((void (*)(int, int))VFn(mem, 0x28))(0, 0);

  void* dpf = EA_ZoneNew(0x388, "Simulator", 0, 0, 0, 0);
  if (dpf) { dpf = (void*)((void* (*)(void*, int, int))0x008d9f80)(dpf, 0, 0); }

  void* odb = EA_ZoneNew(0x24, "Simulator", 0, 0, 0, 0);
  if (odb) { odb = (void*)((void* (*)(void*, void*))0x0069fa60)(odb, dpf); }

  ((void (*)(void*, int))VFn(odb, 0x3c))(odb, 1);
  FUN_00693d60(odb, 1, 1, 1);
  FUN_00692ea0();
  ((void (*)(void*))VFn(odb, 0x2c))(odb);
  ((void (*)(void*))VFn(odb, 0x1c))(odb);
  ((void (*)(void*))VFn(odb, 0x08))(odb);
  FUN_00b8db70(0);

  void* p1 = VFn(mem, 0x18);
  (void)p1;
  int iVar2 = (int)VFn(mem, 0x1c);
  FUN_0093aa70(io, 0, 1, 0);              // WriteUint32(io, &val, 1, 0)
  void* w = VFn(io, 0x18);
  ((void (*)(int, int))VFn(w, 0x38))(iVar2, 0);
  EastlDelete(0);
  ((void (*)(void*))VFn(odb, 0x04))(odb);
  ((void (*)(void*))VFn(dpf, 0x04))(dpf);
  ((void (*)(void*))VFn(mem, 0x08))(mem);
  return 1;
}

// ===========================================================================
// @ 0x00b8f690
cPlantCargoInfo* S::FUN_00b8f690()
{
  cPlantCargoInfo* self = (cPlantCargoInfo*)this;
  ((void (__thiscall*)(void*))0x00c87660)(this);   // Simulator::cAnimalCargoInfo ctor
  self->f90 = *(float*)0x01470f1c;
  self->f7c = 0;
  self->f80 = 0;
  self->f84 = 0;
  self->f88 = 0;
  self->f8c = 0;
  self->fa0 = 0;
  self->vf0 = (void*)0x01465798;
  self->vf1 = (void*)0x01465790;
  self->vf2 = (void*)0x0146576c;
  self->f94 = 0.0f;
  self->f98 = 0.0f;
  self->f9c = 0.0f;
  return self;
}

// ===========================================================================
// @ 0x00b8f730
cPlantCargoInfo* S::FUN_00b8f730(cPlantCargoInfo* other)
{
  char* self = (char*)this;
  ((void (__thiscall*)(void*, void*))0x00c870b0)(this, other);
  if (self != (char*)other) {
    *(int*)(self + 0x7c) = *(int*)((char*)other + 0x7c);
    *(int*)(self + 0x80) = *(int*)((char*)other + 0x80);
    *(int*)(self + 0x84) = *(int*)((char*)other + 0x84);
    *(int*)(self + 0x88) = *(int*)((char*)other + 0x88);
    *(int*)(self + 0x8c) = *(int*)((char*)other + 0x8c);
    *(float*)(self + 0x90) = *(float*)((char*)other + 0x90);
    *(float*)(self + 0x94) = *(float*)((char*)other + 0x94);
    *(float*)(self + 0x98) = *(float*)((char*)other + 0x98);
    *(float*)(self + 0x9c) = *(float*)((char*)other + 0x9c);
    *(int*)(self + 0xa0) = *(int*)((char*)other + 0xa0);
  }
  return (cPlantCargoInfo*)self;
}

// ===========================================================================
// @ 0x00b8f7f0
void S::FUN_00b8f7f0(void** out)
{
  cPlantCargoInfo* p = (cPlantCargoInfo*)EastlNew(0xa4, "Simulator/cPlantCargoInfo", 0, 0, 0, 0);
  if (p == 0) { *out = 0; return; }
  int* q = (int*)((cPlantCargoInfo* (__thiscall*)(void*))0x00b8f690)(p);
  if (q) {
    ((cPlantCargoInfo* (__thiscall*)(void*, cPlantCargoInfo*))0x00b8f730)(q, (cPlantCargoInfo*)this);
    ((void (*)(void*))VFn(q, 0x04))(q);
    *out = q;
    return;
  }
  *out = 0;
}

// ===========================================================================
// @ 0x00b8f860
int S::FUN_00b8f860()
{
  char* self = (char*)this;
  int a0 = *(int*)(self + 0xa0);
  if (a0 != 0) {
    int v = *(int*)(a0 + 0x57c);
    switch (v) {
      case (int)0xb8669ec9: return 0x29c388a;
      case (int)0xbcd73e89: return 0x6d60a1cc;
      case 0x37148141:      return 0x3a8be428;
    }
  }
  return 0x6d60a1cc;
}

// ===========================================================================
// @ 0x00b8f9b0
void S::FUN_00b8f9b0(int* out)
{
  char* self = (char*)this;
  int p = *(int*)(self + 0xa0);
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;
  if (p != 0) {
    int v = *(int*)(p + 0x57c);
    if (v == (int)0xb8669ec9) {
      out[0] = *(int*)0x0156bd20;
      out[1] = *(int*)0x0156bd24;
      out[2] = *(int*)0x0156bd28;
      return;
    }
    if (v != (int)0xbcd73e89 && v == 0x37148141) {
      out[0] = *(int*)0x0156bd14;
      out[1] = *(int*)0x0156bd18;
      out[2] = *(int*)0x0156bd1c;
      return;
    }
  }
  out[0] = *(int*)0x0156bd2c;
  out[1] = *(int*)0x0156bd30;
  out[2] = *(int*)0x0156bd34;
}

// ===========================================================================
// @ 0x00b8fa40
char S::FUN_00b8fa40(void* stream)
{
  unsigned key = 0x70a2863c;
  int* io = (int*)VFn(stream, 0x20);
  void* w = VFn(io, 0x18);
  FUN_0093aa70(w, &key, 1, 0);
  char c1 = FUN_00c87580(stream);
  char buf[0xa14];
  FUN_00692f90(buf, (char*)this - 0xc, (void*)0x0156bd78, 0x1a80d26);
  char c2 = FUN_00692900(buf, stream);
  return (c2 != 0 && c1 != 0) ? 1 : 0;
}

// ===========================================================================
// @ 0x00b8fad0
char S::FUN_00b8fad0(void* stream)
{
  unsigned key = 0;
  int* io = (int*)VFn(stream, 0x20);
  void* r = VFn(io, 0x18);
  FUN_0093a780(r, &key, 1, 0);
  char c1 = FUN_00c879a0(stream);
  char buf[0xa14];
  FUN_00692f90(buf, (char*)this - 0xc, (void*)0x0156bd78, 0x1a80d26);
  char c2 = FUN_00693e10(buf, stream);
  char ok;
  if (c2 != 0 && c1 != 0) ok = 1; else ok = 0;
  char* self = (char*)this;
  void* mgr = FUN_00401090(self + 0x50);
  *(void**)(self + 0x94) = FUN_004df440(mgr, self + 0x50);
  return ok;
}

// ===========================================================================
// @ 0x00b8fb70
char S::FUN_00b8fb70()
{
  char* self = (char*)this;
  char result = 0;
  char* p = (char*)FUN_010212a0();
  if (p != 0) {
    char* first = *(char**)(p + 0xbc);
    char* last = *(char**)(p + 0xc0);
    void* vfn = VFn(self, 0x18);
    void* id = (void*)((void* (__thiscall*)(char*))vfn)(self);
    void* res = FUN_00ac0d80(first, last, id);
    result = (last != res);
  }
  return result;
}

// ===========================================================================
// @ 0x00b8fbb0
int S::FUN_00b8fbb0(void* src)
{
  int node = (int)EastlNew(0x20, "Simulator", 0, 0, (const char*)ALLOC_H, 0xd1);
  char* e = (char*)(node + 0x10);
  if (e != 0) {
    *(int*)(e + 0x0) = *(int*)((char*)src + 0x0);
    *(int*)(e + 0x4) = *(int*)((char*)src + 0x4);
    *(int*)(e + 0x8) = *(int*)((char*)src + 0x8);
    int r = *(int*)((char*)src + 0xc);
    *(int*)(e + 0xc) = r;
    if (r != 0) (*(void(__thiscall*)(void*))((*(void***)r)[1]))((void*)r);
  }
  return node;
}

// ===========================================================================
// @ 0x00b8fdd0
void* S::FUN_00b8fdd0(void** out, TreeNode* pos, int* key)
{
  char* self = (char*)this;
  RBTree* tree = (RBTree*)this;
  char* anchor = self + 4;
  if ((char*)pos != *(char**)anchor || (char*)pos == anchor) {
    // (both "empty" conditions funnel to the fast path below)
  }
  if ((char*)pos == (char*)tree->root) {
    // param_3 == tree->root (== *(int**)(param_1+4)) or == anchor
  }
  {
    char* p4 = (char*)pos;
    TreeNode* inc;
    if ((char*)pos == (char*)tree->root || (char*)pos == anchor) {
      if (tree->count != 0) {
        TreeNode* root = tree->root;
        bool lt = (unsigned)root->k0 < (unsigned)key[0];
        if (root->k0 == key[0] && (lt = (unsigned)root->k2 < (unsigned)key[2], root->k2 == key[2]))
          lt = (unsigned)root->k1 < (unsigned)key[1];
        if (lt) {
          FUN_00b8fc10(out, root, key, 0);
          return out;
        }
      }
      char tmp[8];
      FUN_00b8fc80(tmp, key, 0);
      *out = *(void**)tmp;
      return out;
    }
    inc = ((TreeNode* (*)(void*))0x00921580)(p4);        // RBTreeIncrement
    bool lt = (unsigned)pos->k0 < (unsigned)key[0];
    if (pos->k0 == key[0] && (lt = (unsigned)pos->k2 < (unsigned)key[2], pos->k2 == key[2]))
      lt = (unsigned)pos->k1 < (unsigned)key[1];
    if (lt) {
      bool lt2 = (unsigned)key[0] < (unsigned)inc->k0;
      if (key[0] == inc->k0 && (lt2 = (unsigned)key[2] < (unsigned)inc->k2, key[2] == inc->k2))
        lt2 = (unsigned)key[1] < (unsigned)inc->k1;
      if (lt2) {
        if ((char*)pos != 0) {
          int n = FUN_00b8fbb0(key);
          ((void (*)(int, TreeNode*, char*, int))0x009216a0)(n, inc, anchor, 0);
          tree->count += 1;
          *out = (void*)n;
          return out;
        }
        FUN_00b8fc10(out, pos, key, 0);
        return out;
      }
    }
    char tmp[8];
    FUN_00b8fc80(tmp, key, 0);
    *out = *(void**)tmp;
    return out;
  }
  (void)0;
}

// ===========================================================================
// @ 0x00b8ff60
void S::FUN_00b8ff60()
{
  char* self = (char*)this;
  char* esi = self + 0x1c;
  *(char*)(self + 0x38) = 0;
  char* p = *(char**)(esi + 0xc);
  ((void (__thiscall*)(char*, char*))FUN_00b8fd90)(esi, p);
  char* a = esi + 4;
  *(int*)(esi + 0xc) = 0;
  *(char*)(esi + 0x10) = 0;
  *(int*)(esi + 0x14) = 0;
  *(int*)(esi + 8) = (int)a;
  *(int*)a = (int)a;
}

// ===========================================================================
// @ 0x00b8ff90
void* S::FUN_00b8ff90()
{
  char* self = (char*)this;
  ((void (__thiscall*)(void*))FUN_00b5b960)(self);       // SP::cGonzagoSubsystem ctor
  *(void**)(self + 0x00) = (void*)0x01465858;
  *(void**)(self + 0x04) = (void*)0x01465850;
  char* eax = self + 0x20;
  *(int*)(eax + 4) = 0;
  *(int*)(eax + 8) = 0;
  *(int*)(eax + 0xc) = 0;
  *(int*)(self + 0x24) = (int)eax;
  *(int*)eax = (int)eax;
  *(int*)(self + 0x28) = 0;
  *(char*)(self + 0x2c) = 0;
  *(int*)(self + 0x30) = 0;
  *(char*)(self + 0x38) = 0;
  return self;
}

// ===========================================================================
// @ 0x00b8ffd0
void* S::FUN_00b8ffd0(char del)
{
  char* self = (char*)this;
  char* ecx = self + 0x1c;
  *(void**)(self + 0x00) = (void*)0x01465858;
  *(void**)(self + 0x04) = (void*)0x01465850;
  char* p = *(char**)(ecx + 0xc);
  ((void (__thiscall*)(char*, char*))FUN_00b8fd90)(ecx, p);
  ((void (__thiscall*)(void*))FUN_00b5b9a0)(self);       // SP::cGonzagoSubsystem dtor
  if (del & 1) EastlDelete(self);
  return self;
}

// ===========================================================================
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

// ===========================================================================
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

// ===========================================================================
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
