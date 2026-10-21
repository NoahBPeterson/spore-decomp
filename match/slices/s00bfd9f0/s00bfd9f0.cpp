// match/slices/s00bfd9f0/s00bfd9f0.cpp
// Object file: SPCommunity.obj (VS2008 SP1), retail VAs 0x00bfd9f0..
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
//
// Simulator::cCommunity and its simulator-serializable plumbing: the noun id /
// position round trip, the cGonzagoTimer record table, the cSPTimer-backed phase
// clock, the local noun/counter serializers and the star-scenery hookup.  Local
// stub structs carry the retail field offsets and the vtable slots the
// disassembly addresses.  Callees without a name are declared (never defined) so
// a real `call rel32` is emitted and MSVC cannot fold them away.

#include "game/types.h"
#include <string.h>
#include <intrin.h>

// ---- allocator / stream shims (declared only) ----
void* __cdecl Alloc(unsigned size, void* allocator, int a, int b, const char* tag, unsigned n); // 0xf473a0 EAAllocate
void  __cdecl Free(void* p);                                    // 0xf47380 operator delete
void* __cdecl WriteUint32(void* s, void* v, int a, int b);      // 0x93aa70 EA::IO::WriteUint32

void* __cdecl GetFloatProp(unsigned* prop);                     // 0x41ea70

void* __cdecl RandomUint32Uniform(void* rng, int n);            // 0xa68fb0
void* __cdecl RandomDoubleUniform(void* rng);                   // 0x9360d0

// Free (stack-argument, plain ret / ret N) callees.
void* __cdecl FUN_00bfd610();                                    // 0xbfd610
void* __cdecl FUN_00bfd3e0(void*);                               // 0xbfd3e0
void* __cdecl FUN_00bfd490(void*, void*, void*);                 // 0xbfd490
void* __cdecl FUN_00bfd430(void*, void*, void*);                 // 0xbfd430
void* __cdecl FUN_00bfc6e0(void*, void*, void*);                 // 0xbfc6e0
void* __cdecl FUN_00b3d300();                                    // 0xb3d300 SP::NounManager (nullary: mov eax,[g]; ret)
void* __cdecl FUN_00b3d350();                                    // 0xb3d350 SP::PlanetModel
void* __cdecl Matrix3_Assign(void* dst, void* src);              // 0x41cb40 Matrix3::Assign

// __thiscall callees (this in ecx) modelled as stub-struct members, declared
// only, never defined, so MSVC emits a real `call rel32` with the right
// convention.
struct C_THISCALL {
  void* __thiscall FUN_00bfc380(void* id);                       // 0xbfc380 (this = sub-object)
  void* __thiscall FUN_00bfc720();                               // 0xbfc720 (this = sub-object)
  void* __thiscall FUN_00c884f0(void* id);                       // 0xc884f0 (this = sub-object)
  void* __thiscall FUN_00b18460(void* id);                       // 0xb18460
  void* __thiscall FUN_00c3f2d0(void* a);                        // 0xc3f2d0
  void* __thiscall FUN_00c3f160(void* a);                        // 0xc3f160
  void  __thiscall FUN_00c897e0();                               // 0xc897e0 LocalToWorldTransform
  void* __thiscall FUN_00c88670(void* a);                        // 0xc88670 cCommunity::func54h
  void* __thiscall FUN_00b7e3e0(void* a);                        // 0xb7e3e0
  void* __thiscall FUN_00b81630(void* a, void* b);               // 0xb81630
  int   __thiscall FUN_00b88590();                               // 0xb88590 cPlanetModel::GetContinent
  int   __thiscall FUN_00b18590(void* stream);                   // 0xb18590 cGameData::Write
  int   __thiscall FUN_00b183f0(void* arg);                      // 0xb183f0 vtableSlot40
  void* __thiscall FUN_00b25f40(int id);                         // 0xb25f40 (this call takes one stack arg, ret 4)
  void* __thiscall FUN_00b20c60(int id);                         // 0xb20c60 CreateNoun
  void  __thiscall FUN_00b225d0(void* noun);                     // 0xb225d0 RemoveNoun
  int   __thiscall FUN_00c88a90(void* stream);                   // 0xc88a90 cSpatialObject::Write
  unsigned char __thiscall FUN_00c8a550(void* arg);              // 0xc8a550 cSpatialObject::LoadModel
  void  __thiscall FUN_00c899a0(void* a);                        // 0xc899a0 cSpatialObject::func7Ch
  void  __thiscall FUN_00bc3130();                               // 0xbc3130 cSPTimer::Restart
  void* __thiscall FUN_00bc3190();                               // 0xbc3190 cSPTimer::GetElapsedTime
  void  __thiscall FUN_00b63890();                               // 0xb63890 cGonzagoTimer ctor
  void  __thiscall FUN_00b638b0();                               // 0xb638b0 cGonzagoTimer dtor
  void  __thiscall FUN_00c8b2e0();                               // 0xc8b2e0
  void  __thiscall FUN_00ceefd0(float v, float* out1, float* out2); // 0xceefd0 (this = RNG global)
  void  __thiscall FUN_00b83c40(void* pos, float f, int a, int b);  // 0xb83c40
  void* __thiscall FUN_00cVarListSerializer_Construct(void* self, void* g, unsigned n); // 0x692f90 (this = &serializer)
  int   __thiscall FUN_cVarListSerializer_Serialize(void* stream); // 0x692900 (this = &serializer)
};
void* __cdecl FUN_0059aed0(void*, void*, void*);                 // 0x59aed0 (free: obj, key, out)

// 0xbfe230 forwards its `this` (ecx) into 0xc899a0, which reads ecx as `this`
// (its prologue is `mov edi,ecx`).  Both are therefore __thiscall members of
// declaration-only stubs, so the call emits no `add esp` and both return `ret 8`.
struct CStub899a0 {
  void __thiscall FUN_00c899a0(void* a, void* b);                // 0xc899a0
};
struct CStub230 {
  void __thiscall FUN_00bfe230(char* a, char* b);                // 0xbfe230
};

extern unsigned g_1601760[16];                                   // 0x1601760 sMathRandom RNG object
extern float g_168cb6c;                                          // 0x168cb6c
extern float g_168cb70;                                          // 0x168cb70
extern float g_168cb74;                                          // 0x168cb74
extern unsigned char g_168d12c[64];                              // 0x168d12c identity matrix source
extern unsigned char g_168d181;                                  // 0x168d181
extern float g_1485720;                                          // 0x1485720
extern float g_13ec4d0;                                          // 0x13ec4d0
extern float g_13f4fd0;                                          // 0x13f4fd0 2^32
extern float g_169cc08;                                          // 0x169cc08
extern float g_14007f4;                                          // 0x14007f4
extern float g_1471064;                                          // 0x1471064
extern unsigned char g_13ebb38;                                  // 0x13ebb38 allocator
extern char g_13f09b4;                                           // 0x13f09b4 "Simulator"
extern char g_169c253;                                           // 0x169c253
extern void* g_1570a60;                                          // 0x1570a60

// A property record: the ping-pong buffer pair, GetFloat hands back the float slot.
struct PropRec {
  char pad[0x12];
  short m12;                       // +0x12 type tag (0xd == float)
  float* GetFloat();               // 0x41ea70
};

// The cSPTimer / cGonzagoTimer record: a 0x28-byte element whose key sits at +0x20.
struct TimerRec {
  char pad[0x20];
  void* key;                       // +0x20
  // 0x28 bytes total
};

// A ref-counted object with AddRef/Release at vtable +0/+4 (used by the sort helpers).
struct RefObj {
  virtual void AddRef();           // +0x00
  virtual void Release();          // +0x04
};

// A sequential-access "iterator" over a std::vector<RefObj*> pair plus a bucketed
// structure, as the two sort/merge helpers 00bfe7c0/00bfe840 walk it.
struct SeqIter {
  RefObj** cur;                    // +0x00
  RefObj** begin;                  // +0x04
  RefObj** end;                    // +0x08
  RefObj*** bucket;                // +0x0c
};

// A {begin,end,cap} vector viewed through the +0x230 record table.

// The cCommunity object as these functions see it.  Every function in this slice
// takes `this` in ecx (retail `mov esi,ecx` / `mov edi,ecx` / `[ecx+N]`), so the
// whole set is modelled as __thiscall members of this stub.
struct cCommunity {
  char pad000[0x2c];
  RefObj* m2c;                     // +0x2c
  int m30;                         // +0x30
  void* m34;                       // +0x34 cSpatialObject base
  char pad038[0x58 - 0x38];
  int m58;                         // +0x58 noun vector begin
  int m5c;                         // +0x5c noun vector end (0xc-byte stride)
  char pad060[0x6c - 0x60];
  char m6c;                        // +0x6c
  char pad06d[0x9c - 0x6d];
  void* m9c;                       // +0x9c
  char pad0a0[0xd0 - 0xa0];
  void* mD0;                       // +0xd0
  char pad0d4[0x108 - 0xd4];
  char m108[0x9c];                 // +0x108 sub-object (own vector at +0x00)
  void* m1a4;                      // +0x1a4
  char pad1a8[0x1d0 - 0x1a8];
  float m1d0;                      // +0x1d0 phase accumulator
  float m1d4;                      // +0x1d4 phase limit
  void* m1d8;                      // +0x1d8
  void* m1dc;                      // +0x1dc
  RefObj* m1e0;                    // +0x1e0
  unsigned char m1e4;              // +0x1e4 scenery-init guard
  char pad1e5[0x1ec - 0x1e5];
  int m1ec;                        // +0x1ec timer state byte
  char m1f0[0x20];                 // +0x1f0 cSPTimer
  int m210;                        // +0x210
  int m214;                        // +0x214
  char pad218[0x230 - 0x218];
  char m230[0x28];                 // +0x230 timer record table (begin/end/cap)
  char pad258[0x288 - 0x258];
  void* m288;                      // +0x288 shared value object

  // ---- members, retail VAs in the comment above each definition ----
  void  Push(void* lo, void* hi);                       // 0x00bfdc50
  void  EnsureTimer(void* key);                         // 0x00bfddc0
  float ReadPhase(unsigned char save);                  // 0x00bfde50
  float GetPhaseRatio();                                // 0x00bfdea0
  void* ResolveID(int id);                              // 0x00bfdeb0
  float GetScaledFloat();                               // 0x00bfdf00
  void  AdvancePhase(float dt);                         // 0x00bfdf20
  void  SetID(int v);                                   // 0x00bfdf60
  void* GetNoun();                                      // 0x00bfdf80
  void  SetState(int v);                                // 0x00bfdfb0
  float GetProgress();                                  // 0x00bfdff0
  int   HasNoun();                                      // 0x00bfe0c0
  unsigned char Write(void* stream);                    // 0x00bfe0f0
  void* FillPair(char* obj);                            // 0x00bfe260
  void  Activate(int a, RefObj* b);                     // 0x00bfe450
  void  Deactivate();                                   // 0x00bfe4d0
  void  SetupScenery();                                 // 0x00bfe530
  unsigned char Read(void* arg);                        // 0x00bfe5d0
  void  LoadModel(void* arg);                           // 0x00bfe690
  void  ReleaseTable();                                 // 0x00bfe6c0
  void  SpawnAt(float* pos);                            // 0x00bfe900
  void  Teardown();                                     // 0x00bfea10
  void  InitScenery();                                  // 0x00bfeb00
  void* Front();                                        // 0x00bfec10
  void  GetNounID(float* out);                          // 0x00bfd9f0
};

// ------------------------------------------------ heap helpers over 0x28 elements

// @ 0x00bfdc50
// Insert a copy of the 0x28-byte element into the vector at [this] (grow when
// full).  `lo`/`hi` select the insertion slot; the {+0x08..+0x20} region is
// copied verbatim from `hi` to `lo`.
void cCommunity::Push(void* lo, void* hi) {
  char* vec = (char*)this;
  char* end = *(char**)(vec + 4);
  if (end != *(char**)(vec + 8)) {
    if ((char*)hi >= (char*)lo && (char*)hi < end) hi = (char*)hi + 0x28;
    if (end) FUN_00bfd3e0(end - 0x28);
    FUN_00bfd490(lo, *(char**)(vec + 4) - 0x28, *(char**)(vec + 4));
    memcpy((char*)lo + 8, (char*)hi + 8, 0x18);
    *(char**)(vec + 4) += 0x28;
    return;
  }
  {
    int n = (int)(end - *(char**)vec) / 0x28;
    int cap = n ? 2 * n : 1;
    char* mem = 0;
    if (cap) mem = (char*)Alloc(0xd1, &g_13ebb38, 0, 0, &g_13f09b4, cap * 0x28);
    char* begin = *(char**)vec;
    char* e2 = (char*)FUN_00bfd430(0, mem, begin);
    (void)FUN_00bfc6e0(0, mem, begin);
    if (e2) FUN_00bfd3e0(e2);
    char* p1 = mem + 0x28;
    FUN_00bfd430(0, p1, *(char**)vec);
    char* e3 = (char*)FUN_00bfc6e0(0, p1, *(char**)vec);
    char* old = *(char**)vec;
    if (old && *(int*)(old - 4)) Free(old);
    *(char**)(vec + 4) = e3;
    *(char**)vec = mem;
    *(char**)(vec + 8) = mem + cap * 0x28;
  }
}

// @ 0x00bfddc0
// Find the timer record whose key (+0x20) equals `key`; append a default one if
// absent, then Restart it.  The record vector lives at this+0x84.
void cCommunity::EnsureTimer(void* key) {
  char* v = (char*)this + 0x84;
  char* p = *(char**)(v + 0);
  char* e0 = *(char**)(v + 4);
  for (; p != e0; p += 0x28)
    if (*(void**)(p + 0x20) == key) { ((C_THISCALL*)p)->FUN_00bc3130(); return; }
  {
    char* e = *(char**)(v + 4);
    if (e < *(char**)(v + 8)) {
      *(char**)(v + 4) = e + 0x28;
      if (e) ((C_THISCALL*)e)->FUN_00b63890();
    } else {
      uint32_t tmp[0x28 / 4];
      ((C_THISCALL*)tmp)->FUN_00b63890();
      ((cCommunity*)((char*)this + 0x84))->Push(*(void**)(v + 4), tmp);
      ((C_THISCALL*)tmp)->FUN_00b638b0();
    }
    *(void**)(*(char**)(v + 4) - 8) = key;
    ((C_THISCALL*)(*(char**)(v + 4) - 0x28))->FUN_00bc3130();
  }
}

// ------------------------------------------------------------- phase clock bits

// @ 0x00bfde50
// Read the phase, optionally storing it back.  Returns the second out value.
float cCommunity::ReadPhase(unsigned char save) {
  float a, b;
  ((C_THISCALL*)(void*)&g_169c253)->FUN_00ceefd0(this->m1d0, &a, &b);
  if (save) this->m1d0 = a;
  return b;
}

// @ 0x00bfdea0
float cCommunity::GetPhaseRatio() { return this->m1d0 / this->m1d4; }

// @ 0x00bfdeb0
// Three-way id resolve: `this`, the +0x34 sub-object, or the +0x108 sub-object.
void* cCommunity::ResolveID(int id) {
  if (id == 0x403df5f) return this;
  void* r = (void*)((C_THISCALL*)((char*)this + 0x34))->FUN_00c884f0((void*)id);
  if (r) return r;
  r = (void*)((C_THISCALL*)((char*)this + 0x108))->FUN_00bfc380((void*)id);
  if (r) return r;
  return (void*)((C_THISCALL*)this)->FUN_00b18460((void*)id);
}

// @ 0x00bfdf00
// `this->m34` object's +0x34 vtable float method, scaled by [this+0x5c].
float cCommunity::GetScaledFloat() {
  char* o = (char*)this;
  float f = *(float*)(o + 0x5c);
  void** vt = *(void***)o;
  return ((float(__thiscall*)(void*))vt[0x34 / 4])(o) * f;
}

// @ 0x00bfdf20
// Advance the phase by dt*0x169cc08 and clamp to the limit.
void cCommunity::AdvancePhase(float dt) {
  float v = g_169cc08 * dt + this->m1d0;
  this->m1d0 = v;
  if (v > this->m1d4) this->m1d0 = this->m1d4;
}

// @ 0x00bfdf60
void cCommunity::SetID(int v) {
  this->m30 = v;
  void* s = this->m288;
  if (s) *(int*)s = v;
}

// @ 0x00bfdf80
void* cCommunity::GetNoun() {
  int id = ((int(__thiscall*)(void*))(((void**)*(void**)this)[0x4c / 4]))(this);
  void* r = 0;
  if (id != -1) {
    r = (void*)((C_THISCALL*)FUN_00b3d300())->FUN_00b25f40(id);
  }
  return r;
}

// @ 0x00bfdfb0
void cCommunity::SetState(int v) {
  if (this->m1ec != v) {
    this->m1ec = v;
    ((C_THISCALL*)((char*)this + 0x1f0))->FUN_00bc3130();
  }
  void* s = this->m288;
  if (s) *(int*)((char*)s + 4) = v;
}

// @ 0x00bfdff0
// Phase fraction: elapsed ticks / tick budget, clamped into [0, g_13ec4d0].
float cCommunity::GetProgress() {
  long long t = (long long)(size_t)((C_THISCALL*)((char*)this + 0x1f0))->FUN_00bc3190();
  double frac = (double)t / (double)this->m210;
  float f = (float)(frac * g_13ec4d0);
  if (f > g_13ec4d0) f = g_13ec4d0;
  if (f < 0.0f) f = 0.0f;
  return f;
}

// @ 0x00bfe0c0
int cCommunity::HasNoun() {
  int id = ((int(__thiscall*)(void*))(((void**)*(void**)this)[0x4c / 4]))(this);
  void* r = 0;
  if (id != -1) {
    r = (void*)((C_THISCALL*)FUN_00b3d300())->FUN_00b25f40(id);
  }
  return r != 0;
}

// @ 0x00bfe0f0
// Write the community out: noun id + cGameData + cSpatialObject, then the var list.
unsigned char cCommunity::Write(void* stream) {
  void* o = ((void*(__thiscall*)(void*))(((void**)*(void**)stream)[0x20 / 4]))(stream);
  int id = ((int(__thiscall*)(void*))(((void**)*(void**)o)[0x18 / 4]))(o);
  unsigned t = 0x403df5f;
  WriteUint32((void*)id, &t, 1, 0);
  unsigned char ok = 0;
  if (((C_THISCALL*)this)->FUN_00b18590(stream)) {
    if (((C_THISCALL*)((char*)this + 0x34))->FUN_00c88a90(stream)) ok = 1;
  }
  char vs[0x18];
  ((C_THISCALL*)vs)->FUN_00cVarListSerializer_Construct(this, &g_1570a60, 0x1a80d26);
  if (ok) {
    if (((C_THISCALL*)vs)->FUN_cVarListSerializer_Serialize(stream)) return 1;
  }
  return 0;
}

// @ 0x00bfe230 (__thiscall: forwards ecx into 0xc899a0, ret 8)
void CStub230::FUN_00bfe230(char* a, char* b) {
  ((CStub899a0*)this)->FUN_00c899a0(a, b);
  *(float*)(b + 4) = *(float*)(b + 4) - g_14007f4;
}

// @ 0x00bfe260
// Fill the 8-byte {noun pointer-ish, +0x1ec} pair.
void* cCommunity::FillPair(char* obj) {
  int v = ((int(__thiscall*)(void*))(((void**)*(void**)(obj + 0x108))[0x10 / 4]))(obj + 0x108);
  *(int*)((char*)this + 0) = v;
  *(int*)((char*)this + 4) = *(int*)(obj + 0x1ec);
  return this;
}

// @ 0x00bfe310 (free: ptr comes in on the stack, the callee is a __cdecl
// function pointer taking the object as a stack argument -> `push a`, `add esp,4`)
void FUN_00bfe310(char* a) {
  char* r = ((char*(__cdecl*)(void*))(((void**)a)[0x20 / 4]))(a);
  *r = g_168d181;
}

// @ 0x00bfe450
void cCommunity::Activate(int a, RefObj* b) {
  char* s = (char*)this;
  *(int*)(s + 0x210) = 0x1388;
  *(int*)(s + 0x214) = a;
  RefObj* old = this->m1e0;
  if (b != old) {
    if (b) ((void(__thiscall*)(void*))(((void**)*(void**)b)[0]))(b);
    this->m1e0 = b;
    if (old) ((void(__thiscall*)(void*))(((void**)*(void**)old)[1]))(old);
  }
  if (this->m1ec != 1) { this->m1ec = 1; ((C_THISCALL*)(s + 0x1f0))->FUN_00bc3130(); }
  void* sh = this->m288;
  if (sh) *(int*)((char*)sh + 4) = 1;
}

// @ 0x00bfe4d0
void cCommunity::Deactivate() {
  char* s = (char*)this;
  *(int*)(s + 0x210) = 0;
  *(int*)(s + 0x214) = -1;
  _ReadWriteBarrier();
  RefObj* e = this->m1e0;
  if (e) { this->m1e0 = 0; ((void(__thiscall*)(void*))(((void**)*(void**)e)[1]))(e); }
  if (this->m1ec != 0) { this->m1ec = 0; ((C_THISCALL*)(s + 0x1f0))->FUN_00bc3130(); }
  void* sh = this->m288;
  if (sh) *(int*)((char*)sh + 4) = 0;
}

// @ 0x00bfe530
void cCommunity::SetupScenery() {
  void* sub = (char*)this + 0x34;
  void* r = ((void*(__thiscall*)(void*))(((void**)*(void**)sub)[0x98 / 4]))(sub);
  if (*(int*)r != 0) return;
  float one = 1.0f;
  ((void(__thiscall*)(void*, int, float))(((void**)*(void**)sub)[0x40 / 4]))(sub, 0, one);
  void* pm = FUN_00b3d350();
  int cont = ((C_THISCALL*)pm)->FUN_00b88590();
  void* p2 = FUN_00b3d350();
  unsigned char b = *(unsigned char*)(cont + *(int*)((char*)p2 + 0x64));
  if (b) {
    unsigned k = 0x4728435;
    ((void(__thiscall*)(void*, unsigned*))(((void**)*(void**)sub)[0x94 / 4]))(sub, &k);
  } else {
    unsigned k = 0xa6b33a2f;
    ((void(__thiscall*)(void*, unsigned*))(((void**)*(void**)sub)[0x94 / 4]))(sub, &k);
  }
}

// @ 0x00bfe5d0
unsigned char cCommunity::Read(void* arg) {
  unsigned char ok = (unsigned char)((C_THISCALL*)this)->FUN_00b183f0(arg);
  if (!ok) return ok;
  if (*(int*)((char*)this + 0xd0) == 0) return ok;
  int id = ((int(__thiscall*)(void*))(((void**)*(void**)this)[0x4c / 4]))(this);
  void* r = (void*)((C_THISCALL*)FUN_00b3d300())->FUN_00b25f40(id);
  float* src;
  float tmpv[3];
  if (id != -1 && r != 0) {
    src = (float*)((char*)r + 0xc4);
  } else {
    tmpv[0] = tmpv[1] = tmpv[2] = g_1471064;
    src = tmpv;
  }
  void* dst = (char*)this->mD0 + 0x4c;
  ((float*)dst)[0] = src[0];
  ((float*)dst)[1] = src[1];
  ((float*)dst)[2] = src[2];
  return ok;
}

// @ 0x00bfe690
void cCommunity::LoadModel(void* arg) {
  if (((C_THISCALL*)this)->FUN_00c8a550(arg)) {
    void* p = *(void**)((char*)this + 0x9c);
    if (p) *(unsigned*)((char*)p + 4) |= 4;
  }
}

// @ 0x00bfe6c0
// Release every ref-counted element of the +0x230 record table.
void cCommunity::ReleaseTable() {
  char* s = (char*)this;                       // this == &community->m230
  RefObj** a = *(RefObj***)(s + 8);
  if (*(int*)(s + 0x14) == *(int*)(s + 0x24)) {
    RefObj** e = *(RefObj***)(s + 0x18);
    for (; a < e; ++a) { RefObj* p = *a; if (p) p->Release(); }
  } else {
    RefObj** e1 = *(RefObj***)(s + 0x10);
    for (; a < e1; ++a) { RefObj* p = *a; if (p) p->Release(); }
    RefObj** b = *(RefObj***)(s + 0x1c);
    RefObj** e2 = *(RefObj***)(s + 0x18);
    for (; b < e2; ++b) { RefObj* p = *b; if (p) p->Release(); }
    if (*(void**)(s + 0x1c)) Free(*(char**)(s + 0x1c));
  }
  char* b0 = *(char**)(s + 0x14) + 4;
  if (b0 < *(char**)(s + 0x24)) {
    do {
      RefObj*** blk = *(RefObj****)b0;
      RefObj** q = *blk;
      RefObj** qe = q + 0x40;
      for (; q < qe; ++q) { RefObj* p = *q; if (p) p->Release(); }
      if (*blk) Free((char*)*blk);
      b0 += 4;
    } while (b0 < *(char**)(s + 0x24));
  }
  *(void**)(s + 0x18) = *(void**)(s + 8);
  *(void**)(s + 0x1c) = *(void**)(s + 0xc);
  *(void**)(s + 0x20) = *(void**)(s + 0x10);
  *(void**)(s + 0x24) = *(void**)(s + 0x14);
}

// @ 0x00bfe7c0 (free: five stack words + key, plain ret)
// Bucketed-pair walk: find the element equal to *key across the current bucket
// chain, writing the four-word iterator state at `out` = {cur, bucket, end, slot}.
void FUN_00bfe7c0(SeqIter* out, RefObj*** bucketLo, RefObj** cur, RefObj** end, void** key) {
  RefObj*** bl = bucketLo;
  void* k = *key;
  if (cur == end) {
    out->cur = cur;
    out->bucket = (RefObj***)bl;
    return;
  }
  for (;;) {
    if (*cur == (RefObj*)k) break;
    cur++;
    if (cur == end) {
      bl++;
      RefObj** q = *bl;
      end = q + 0x40;
      cur = q;
    }
  }
  out->cur = cur;
  out->begin = (RefObj**)bl;
  out->end = end;
  out->bucket = (RefObj***)(cur);
}

// @ 0x00bfe840 (free: three stack pointers, plain ret)
// Nested four-level iterator walk: for every (ay, by) pair step, swap *ay for *by
// (AddRef the new value, Release the old), releasing the displaced element.
void FUN_00bfe840(SeqIter* out, SeqIter* a, SeqIter* b) {
  RefObj** ay = a->cur;
  RefObj** by = b->cur;
  if (ay == a->begin) goto result;
  for (;;) {
    if (ay == b->cur) {
      RefObj*** bp = a->bucket - 1;
      a->bucket = bp;
      ay = *bp;
      a->begin = ay;
      a->end = ay + 0x40;
    }
    ay = ay - 1;
    a->cur = ay;
    if (by == b->begin) {
      RefObj*** bp = b->bucket - 1;
      b->bucket = bp;
      by = *bp;
      b->begin = by;
      b->end = by + 0x40;
    }
    by = by - 1;
    b->cur = by;
    {
      RefObj* nv = *ay;
      RefObj* ov = *by;
      if (nv != ov) {
        if (nv) nv->AddRef();
        *by = nv;
        if (ov) ov->Release();
      }
    }
    if (ay != a->end) continue;
    break;
  }
result:
  out->cur = by;
  out->begin = a->begin;
  out->end = a->end;
  out->bucket = (RefObj***)by;
}

// @ 0x00bfe900
void cCommunity::SpawnAt(float* pos) {
  float p[3];
  p[0] = pos[0];
  p[1] = pos[1];
  p[2] = pos[2];
  {
    void* pm = FUN_00b3d350();
    if (((C_THISCALL*)pm)->FUN_00b7e3e0(p)) {
      void* r = ((C_THISCALL*)FUN_00b3d350())->FUN_00b81630(p, 0);
      p[0] = ((float*)r)[0];
      p[1] = ((float*)r)[1];
      p[2] = ((float*)r)[2];
    }
  }
  if (*(void**)((char*)this + 0x1a4) == 0) {
    void* nm = FUN_00b3d300();
    void* n = ((C_THISCALL*)nm)->FUN_00b20c60(0x2e72cae);
    void* obj = 0;
    if (n) obj = (void*)((void*(__thiscall*)(void*, int))(((void**)*(void**)n)[0xc / 4]))(n, 0x2e71a5a);
    void* old = *(void**)((char*)this + 0x1a4);
    if (obj != old) {
      if (obj) ((void(__thiscall*)(void*))(((void**)*(void**)obj)[0]))(obj);
      *(void**)((char*)this + 0x1a4) = obj;
      if (old) ((void(__thiscall*)(void*))(((void**)*(void**)old)[1]))(old);
    }
    void* cur = *(void**)((char*)this + 0x1a4);
    if (cur) ((C_THISCALL*)cur)->FUN_00c3f2d0((char*)this - 0x34);
  }
  ((C_THISCALL*)this)->FUN_00c88670(p);
  {
    void* obj = *(void**)((char*)this + 0x1a4);
    void* r = ((void*(__thiscall*)(void*))(((void**)*(void**)this)[0x2c / 4]))(this);
    ((C_THISCALL*)obj)->FUN_00c3f160(r);
  }
}

// @ 0x00bfea10
void cCommunity::Teardown() {
  char* s = (char*)this;
  RefObj* a = *(RefObj**)(s + 0x2c);
  if (a) { *(void**)(s + 0x2c) = 0; ((void(__thiscall*)(void*))(((void**)*(void**)a)[1]))(a); }
  void* d = *(void**)(s + 0x1d8);
  if (d) {
    ((C_THISCALL*)d)->FUN_00c3f2d0(0);
    void* nm = FUN_00b3d300();
    ((C_THISCALL*)nm)->FUN_00b225d0(*(void**)(s + 0x1d8));
    RefObj* x = *(RefObj**)(s + 0x1d8);
    *(void**)(s + 0x1d8) = 0;
    if (x) ((void(__thiscall*)(void*))(((void**)*(void**)x)[1]))(x);
  }
  RefObj* y = *(RefObj**)(s + 0x1dc);
  *(void**)(s + 0x1dc) = 0;
  if (y) {
    int rc = *(int*)((char*)y + 0x40);
    if (rc > 1) { *(int*)((char*)y + 0x40) = rc - 1; }
    else ((void(__thiscall*)(void*, int, int))(((void**)*(void**)y)[0x170 / 4]))(y, (*(unsigned*)((char*)y + 4) >> 31) & 1, (int)y);
  }
  ((cCommunity*)(s + 0x230))->ReleaseTable();
  RefObj* z = *(RefObj**)(s + 0x1e0);
  if (z) { *(void**)(s + 0x1e0) = 0; ((void(__thiscall*)(void*))(((void**)*(void**)z)[1]))(z); }
  ((void(__thiscall*)(void*))(((void**)*(void**)(s + 0x34))[0xa4 / 4]))(s + 0x34);
  ((C_THISCALL*)(s + 0x108))->FUN_00bfc720();
  ((C_THISCALL*)(s + 0x34))->FUN_00c8b2e0();
}

// @ 0x00bfeb00
void cCommunity::InitScenery() {
  char* s = (char*)this;
  if (s[0x1e4]) return;
  void* p = *(void**)(s + 0xd0);
  float v[3];
  if (*(void**)((char*)p + 0x90)) {
    void* pl = *(void**)((char*)p + 0x90);
    FUN_0059aed0(pl, (void*)0x51cae56, v);
    void* pl2 = *(void**)((char*)p + 0x90);
    if (pl2) {
      float* r = 0;
      if (((unsigned char(__thiscall*)(void*, int, float**))(((void**)*(void**)pl2)[0x24 / 4]))(pl2, 0x51cae57, &r)) {
        if (*(short*)((char*)r + 0x12) == 0xd) {
          r = (float*)GetFloatProp((unsigned*)r);
          v[0] = *r;
        }
      }
    }
  }
  {
    void* pm = FUN_00b3d350();
    char* sub = s + 0x34;
    float* a = (float*)((void*(__thiscall*)(void*))(((void**)*(void**)sub)[0x2c / 4]))(sub);
    int b = ((int(__thiscall*)(void*))(((void**)*(void**)sub)[0x30 / 4]))(sub);
    float t[3];
    FUN_0059aed0((void*)b, (void*)0, t);
    float x = a[0] + t[0];
    float y = a[1] + t[1];
    float z = a[2] + t[2];
    float wx = v[0] + x, wy = v[1] + y, wz = v[2] + z;
    ((C_THISCALL*)pm)->FUN_00b83c40(&wx, 0.0f, 0x10000000, 0);
  }
  s[0x1e4] = 1;
}

// @ 0x00bfec10
void* cCommunity::Front() {
  struct View {
    char pad238[0x238];
    int* a;                        // +0x238
    char pad23c[0x248 - 0x23c];
    int* b;                        // +0x248
  };
  View* v = (View*)this;
  int* a = v->a;
  if (a == v->b) return 0;
  return (void*)*a;
}

// @ 0x00bfd9f0 Simulator::ISimulatorSerializable::GetNounID (virtual: this in
// ecx, one stack arg `out`, ret 4).
// Serializable noun-id round trip: write the local origin into `out` unless the
// thing is a valid noun, in which case sample the destination position.
void cCommunity::GetNounID(float* out) {
  char* s = (char*)this;
  if (s != 0) {
    unsigned char ok = ((unsigned char(__thiscall*)(void*, int))(((void**)*(void**)s)[0x5c / 4]))(s, 0x116dd1b);
    if (ok) {
      out[0] = g_168cb6c;
      out[1] = g_168cb70;
      out[2] = g_168cb74;
      return;
    }
  }
  if (*(int*)(s + 0x58) == *(int*)(s + 0x5c) || *(char*)(s + 0x6c) != 0) FUN_00bfd610();
  {
    int n = (*(int*)(s + 0x5c) - *(int*)(s + 0x58)) / 0xc;
    unsigned idx = (unsigned)(size_t)RandomUint32Uniform(g_1601760, n);
    float* e = (float*)(*(int*)(s + 0x58) + idx * 0xc);
    float ax = e[0], ay = e[1], az = e[2];
    float bx = g_168cb6c, by = g_168cb70, bz = g_168cb74;
    char m[0x28];
    memset(m, 0, 0x28);
    *(float*)(m + 0x14) = bx;
    *(float*)(m + 0x18) = by;
    *(float*)(m + 0x1c) = bz;
    Matrix3_Assign(m + 0x18, &g_168d12c);
    {
      void* o = ((void*(__thiscall*)(void*, void*))(((void**)*(void**)s)[8 / 4]))(s, m);
      ((C_THISCALL*)o)->FUN_00c897e0();
    }
    {
      void* o = ((void*(__thiscall*)(void*))(((void**)*(void**)s)[8 / 4]))(s);
      float f = ((float(__thiscall*)(void*))(((void**)*(void**)o)[0x34 / 4]))(o);
      *(float*)(m + 0x20) = f;
    }
    if (*(unsigned char*)(m + 0x10) & 2) {
      float px = *(float*)(m + 0x30) * ax + *(float*)(m + 0x24) * ay + *(float*)(m + 0x3c) * az;
      float py = *(float*)(m + 0x34) * ay + *(float*)(m + 0x28) * ax + *(float*)(m + 0x40) * az;
      float pz = *(float*)(m + 0x38) * ay + *(float*)(m + 0x2c) * ax + *(float*)(m + 0x44) * az;
      ax = px; ay = py; az = pz;
    }
    float q = *(float*)(m + 0x20);
    q = q * ax + *(float*)(m + 0x14);
    float q1 = *(float*)(m + 0x18) + q;
    float q2 = *(float*)(m + 0x1c);
    (void)q1; (void)q2;
    {
      void* o = ((void*(__thiscall*)(void*))(((void**)*(void**)s)[8 / 4]))(s);
      float* p = (float*)((void*(__thiscall*)(void*))(((void**)*(void**)o)[0x2c / 4]))(o);
      out[0] = ax - p[0];
      out[1] = ay - p[1];
      out[2] = az - p[2];
    }
  }
}
