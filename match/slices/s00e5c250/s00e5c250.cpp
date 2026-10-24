// Slice s00e5c250 (batch bfs0, slice 34). Region 0xe5c250-0xe5ce81.
// Cell-game creature-key random selection, save/load glue, predicate helpers, rb-tree find,
// struct copy and a fluid-particle ray cast. Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>
#include <math.h>

static inline void** Vt(void* p) { return *(void***)p; }

extern void*  gCellGame_16b3c04;
extern void*  gMathRandom_15a83a4;   // EA::Random::RandomLinearCongruential
extern float  gBox_16b3c88, gBox_16b3c8c, gBox_16b3c90, gBox_16b3c94,
              gBox_16b3c98, gBox_16b3c9c;
extern float  gK_1470f1c, gK_13f94f4, gK_13ec4b8, gK_140e964;
extern float  gInvalidKey_15a83a4[3];
extern float  gPollinatedKey_15a7d0c;

// ---- external callees ----
// 0x00743b50 is a thiscall (`mov eax,ecx; mov dword ptr [eax],0; ret`) and 0x00e82130 is the release
// thiscall for the same stack object (`lea ecx,[esp+0x10]; call 0xe82130` on every exit path).
// That object is a list handle: 0x00e4cc40 stores the list at +0 and bumps list->0xc, the release
// drops it again - which is why the field has to be released through the stack object's address.
struct ListHandle {
    int* p;        // +0   list object (set by 0x00e4cc40)
    int  r4;       // +4
    int  r8;       // +8
    int  rC;       // +0xc
    int  pad[2];
    void FUN_00743B50();   // 0x00743b50
    void FUN_00E82130();   // 0x00e82130
};
// 0x009360d0 is a thiscall on the RNG state object at 0x01601760 (reads/writes [ecx]), returning
// the next double in st(0); it takes no stack args.
struct RngState {
    double FUN_009360D0();
};
extern RngState gRng_1601760;
// 0x00b721d0 is a thiscall on the cell-game sub-object at gCellGame+0x1c (ecx), with the id pushed.
struct CellGameSub {
    void* FUN_00B721D0(int id);   // 0x00b721d0
};
extern "C" void* __cdecl thunk_FUN_00e4cc40(int, void*);      // 0xe4cc40 (jmp 0xe823a0)
extern "C" void  __cdecl SP_GetPollinatedCell(float* out, float, float, float, float); // 0xe84f30
extern "C" void* __cdecl FUN_00b72210(void* self, int id);    // thunk, this=ecx
extern "C" void* __cdecl FUN_00b72160_thunk(void* self);
extern "C" int   __cdecl FUN_00e5c4f0_naked_guard();
extern "C" int   __cdecl FUN_00e57340(void* p);
extern "C" float __cdecl FUN_00e4fac0(void* p);
extern int gCfg_16b3c04b;
extern "C" void* __cdecl FUN_00b721d0(void* self, int id);    // thunk, this=ecx
extern "C" void __cdecl EA_IO_ReadInt32(void* stream, void* out, int n, int b);  // 0x93a780
extern "C" void __cdecl EA_IO_WriteUint32(void* stream, void* val, int n, int b); // 0x93aa70
extern "C" void  __cdecl FUN_00e82cf0(int a, int b, int c);
extern "C" void* __cdecl FUN_0067de90(int a, int b);
extern "C" void* __cdecl FUN_007ec160(int a, int b);
extern "C" void  __cdecl FUN_007eb820(int n);
extern "C" void  __cdecl FUN_00e394f0(uint32_t a, void* b, void* c, void* d, void* e);
extern "C" float __cdecl FUN_00e511e0(int a, int b);
extern "C" void* __cdecl FUN_00e4ce40(void* out);
extern "C" void  __cdecl SP_GetRandomDirection3(float* out);   // 0xb7e560
extern "C" int   __cdecl FUN_00e4dbc0(void* fluid, float* aabb, float* dir, float c, float d);
extern "C" bool  __cdecl FUN_00743fb0(void* p, float radius, void* box); // 0x743fb0
extern "C" uint8_t __fastcall FUN_006ffbd0(void* self, void* p, float radius); // 0x6ffbd0

struct cVarListSerializer {
  void Ctor(int a, void* b, uint32_t c);   // 0x692f90
  void Serialize(void* o);                 // 0x692900
  void Read(void* o);                      // 0x693e10
};

// @ 0x00e5c250
float* FUN_00e5c250(float* out, int a) {
  ListHandle local;
  local.FUN_00743B50();
  int* list = (int*)thunk_FUN_00e4cc40(a, &local);
  int idx = -1;
  float total = 0.0f;
  if (*list > 0) {
    int off = 0;
    for (int i = 0; i < *list; ++i) {
      char* e = (char*)list[1] + off;
      total += *(float*)(e + 8);
      double r = gRng_1601760.FUN_009360D0() * total;
      if (r > total) r = total;
      if (r < 0.0) r = 0.0;
      if (r < *(float*)(e + 8)) idx = i;
      off += 0x1c;
    }
    if (idx != -1) {
      char* e = (char*)list[1] + idx * 0x1c;
      int kind = *(int*)e;
      if (kind == 0) {
        out[0] = *(float*)(e + 4);
        out[1] = 0.0740526f;   // the original stores the dword 0x3d97a8e4 as a float constant
        out[2] = gPollinatedKey_15a7d0c;
        local.FUN_00E82130();
        return out;
      } else if (kind == 1) {
        int f18 = *(int*)(e + 0x18);
        int f10 = *(int*)(e + 0x10);
        if (*(char*)((char*)gCellGame_16b3c04 + 0x410c) != 0) {
          int base = *(int*)((char*)gCellGame_16b3c04 + 0x4110);
          f18 = (*(int*)(e + 0x18) >= 0 && base < 10) ? base + *(int*)(e + 0x18) : 10;
          f10 = (*(int*)(e + 0x10) >= 0 && base < 10) ? base + *(int*)(e + 0x10) : 10;
        }
        SP_GetPollinatedCell(out, *(float*)(e + 0x14), (float)f18, *(float*)(e + 0xc), (float)f10);
        local.FUN_00E82130();
        return out;
      }
      out[0] = gInvalidKey_15a83a4[0];
      out[1] = gInvalidKey_15a83a4[1];
      out[2] = gInvalidKey_15a83a4[2];
      local.FUN_00E82130();
      return out;
    }
  }
  out[0] = gInvalidKey_15a83a4[0];
  out[1] = gInvalidKey_15a83a4[1];
  out[2] = gInvalidKey_15a83a4[2];
  local.FUN_00E82130();
  return out;
}

// @ 0x00e5c410
bool FUN_00e5c410(int id, int kind) {
  if (kind == 0) return true;
  char* e = (char*)FUN_00b72210((char*)gCellGame_16b3c04 + 0x1c, id);
  if (*(int*)(e + 0x35c) == *(int*)((char*)gCellGame_16b3c04 + 0x40fc) && kind == 1) return true;
  if (*(int*)(e + 0x35c) == *(int*)((char*)gCellGame_16b3c04 + 0x4100) && kind == 2) return true;
  return false;
}

// @ 0x00e5c460
bool FUN_00e5c460(int id, int kind) {
  if (kind == 0) return true;
  char* e = (char*)FUN_00b72210((char*)gCellGame_16b3c04 + 0x1c, id);
  int t = FUN_00e57340(e);
  float h = *(float*)(e + 0x58);
  if (t == 4 && kind == 3) return true;
  if (h > gK_1470f1c && kind == 2) return true;
  if (h <= gK_1470f1c && kind == 1) return true;
  return false;
}

// @ 0x00e5c4d0
void FUN_00e5c4d0(void* obj) {
  ((void(__thiscall*)(void*, void*))Vt(obj)[0x2c / 4])(obj, *(void**)((char*)gCellGame_16b3c04 + 0x5190));
}

// @ 0x00e5c4f0
int __stdcall FUN_00e5c4f0() {
  char* cg = (char*)gCellGame_16b3c04;
  int n = *(int*)(cg + 0x5164);
  FUN_00e4fac0(*(char**)(cg + 0x5190) + 0x34);
  return n;
}

// @ 0x00e5c520
int FUN_00e5c520() { return *(int*)(*(int*)((char*)gCellGame_16b3c04 + 0x5190) + 0x74); }

// @ 0x00e5c530
float __fastcall FUN_00e5c530(void* self) {
  (void)self;
  char* d = (char*)*(int*)((char*)gCellGame_16b3c04 + 0x5190);
  int a = *(int*)(d + 0x28) - *(int*)(d + 0x20) + *(int*)(d + 0x1c);
  int b = *(int*)(d + 0x24) + *(int*)(d + 0x20);
  float r = FUN_00e511e0(b, a);
  return r;
}

// @ 0x00e5c560
void __fastcall FUN_00e5c560(void* self) {
  (void)self;
  char* g = (char*)gCellGame_16b3c04;
  int id = *(int*)(g + 0x411c);
  char* e = (char*)((CellGameSub*)(g + 0x1c))->FUN_00B721D0(id);
  if (e) *(int*)(e + 0x244) = 6;
}

// @ 0x00e5c5d0
int FUN_00e5c5d0(void* stream, int* out) {
  void* p = (void*)((int(__thiscall*)(void*))Vt(stream)[0x20 / 4])(stream);
  void* io = (void*)((int(__thiscall*)(void*))Vt(p)[0x18 / 4])(p);
  int n;
  EA_IO_ReadInt32(io, &n, 1, 0);
  if (n > 0xd) n = 0xd;
  for (int i = 0; i < n; ++i) {
    void* q = (void*)((int(__thiscall*)(void*))Vt(stream)[0x20 / 4])(stream);
    void* io2 = (void*)((int(__thiscall*)(void*))Vt(q)[0x18 / 4])(q);
    EA_IO_ReadInt32(io2, out, 1, 0);
    ++out;
  }
  return 1;
}

// @ 0x00e5c660
int FUN_00e5c660(void* stream, int* src) {
  uint32_t n = 0xd;
  void* p = (void*)((int(__thiscall*)(void*))Vt(stream)[0x20 / 4])(stream);
  void* io = (void*)((int(__thiscall*)(void*))Vt(p)[0x18 / 4])(p);
  EA_IO_WriteUint32(io, &n, 1, 0);
  for (int i = 0; i < 0xd; ++i) {
    uint32_t v = *src;
    void* q = (void*)((int(__thiscall*)(void*))Vt(stream)[0x20 / 4])(stream);
    void* io2 = (void*)((int(__thiscall*)(void*))Vt(q)[0x18 / 4])(q);
    EA_IO_WriteUint32(io2, &v, 1, 0);
    ++src;
  }
  return 1;
}

// @ 0x00e5c6e0
int FUN_00e5c6e0(void* stream, int a) {
  void* p = (void*)((int(__thiscall*)(void*))Vt(stream)[0x20 / 4])(stream);
  void* io = (void*)((int(__thiscall*)(void*))Vt(p)[0x18 / 4])(p);
  int n;
  EA_IO_ReadInt32(io, &n, 1, 0);
  if (n > 6) n = 6;
  for (int i = 0; i < n; ++i) {
    char buf[0xa00];
    ((cVarListSerializer*)buf)->Ctor(a, (void*)0x15a7d48, 0x1a80d26);
    ((cVarListSerializer*)buf)->Read(stream);
    a += 0x10;
  }
  return 1;
}

// @ 0x00e5c780
// rbtree::find returning an iterator through a hidden return pointer: the original returns that
// pointer in eax on both paths and callers read through eax. Declared void, our not-found path
// returned with eax = 0 (hybrid crash at 0x68ab32, 2026-10-11).
struct RbTreeFind { int* Find(int* out, const uint32_t* key); };
int* RbTreeFind::Find(int* out, const uint32_t* key) {
  char* self = (char*)this;
  char* anchor = self + 4;
  char* n = *(char**)(self + 0xc);
  char* lower = anchor;
  while (n) {
    if (*(uint32_t*)(n + 0x10) < *key) n = *(char**)n;
    else { lower = n; n = *(char**)(n + 4); }
  }
  if (lower != anchor && *key >= *(uint32_t*)(lower + 0x10)) *out = (int)lower;
  else *out = (int)anchor;
  return out;
}

// @ 0x00e5c7d0
struct Elem2c {
  uint32_t f0, f4, f8, fC, f10;
  float    f14, f18, f1c;
  uint8_t  f20;
  uint8_t  pad21[3];
  uint32_t f24, f28;
};
Elem2c* __fastcall FUN_00e5c7d0(Elem2c* dst, int, const Elem2c* src) {
  dst->f0  = src->f0;
  dst->f4  = src->f4;
  dst->f8  = src->f8;
  dst->fC  = src->fC;
  dst->f10 = src->f10;
  dst->f14 = src->f14;
  dst->f18 = src->f18;
  dst->f1c = src->f1c;
  dst->f20 = src->f20;   // the original copies this member as a single byte; pad21 keeps dst's bytes
  dst->f24 = src->f24;
  dst->f28 = src->f28;
  return dst;
}

// @ 0x00e5c860
void* FUN_00e5c860(void* first, void* last, void* dest) {
  char* f = (char*)first;
  char* l = (char*)last;
  char* d = (char*)dest;
  while (f != l) {
    if (d) memcpy(d, f, 0x2c);
    f += 0x2c; d += 0x2c;
  }
  return d;
}

// @ 0x00e5c8e0
void FUN_00e5c8e0(int id) {
  if (*(char*)((char*)gCellGame_16b3c04 + 0x5168) != 0 || id == 0) return;
  FUN_00e82cf0(0xd456d958, 1, 1);
  char* e = (char*)FUN_00b72210((char*)gCellGame_16b3c04 + 0x1c, id);
  void* o = FUN_0067de90(0, 0);
  int r = (int)FUN_007ec160((int)o, 0);
  FUN_007eb820(4);
  void* dst = *(void**)(r + 0xc);
  *(uint32_t*)dst = *(uint32_t*)(*(int*)((char*)gCellGame_16b3c04 + 0x5190) + 0x74);
  *(uint32_t*)((char*)dst + 4) = *(uint32_t*)(*(int*)((char*)gCellGame_16b3c04 + 0x5190) + 0x1c);
  *(uint32_t*)((char*)dst + 0xc) = **(uint32_t**)(e + 0x108);
  int local[6] = {0,0,0,0,0,0};
  FUN_00e394f0(0xaf4f16bc, (void*)(*(int*)((char*)gCellGame_16b3c04 + 0x5190) + 0x10),
               e + 0xfc, &local[0], &local[4]);
}

// @ 0x00e5c9d0
int FUN_00e5c9d0() {
  char* d = (char*)*(int*)((char*)gCellGame_16b3c04 + 0x5190);
  float v = FUN_00e511e0(*(int*)(d + 0x24) + *(int*)(d + 0x20),
                         (*(int*)(d + 0x28) - *(int*)(d + 0x20)) + *(int*)(d + 0x1c));
  ListHandle local;
  local.FUN_00743B50();
  char* r = (char*)FUN_00e4ce40(&local);
  if (v < *(float*)(r + 0xcc)) { local.FUN_00E82130(); return 0xa8ec6f99; }
  if (v > *(float*)(r + 0xc8)) { local.FUN_00E82130(); return 0xcfb01b93; }
  local.FUN_00E82130();
  return 0x5ece4770;
}

// @ 0x00e5ca60
bool __stdcall FUN_00e5ca60(float* p) {
  float x = p[0], y = p[1];
  return x >= gBox_16b3c88 && x <= gBox_16b3c94 &&
         y >= gBox_16b3c8c && y <= gBox_16b3c98 &&
         gBox_16b3c90 <= 0.0f && 0.0f <= gBox_16b3c9c;
}

// @ 0x00e5cac0
void* __stdcall FUN_00e5cac0(void* self, int);

// @ 0x00e5cae0
float* FUN_00e5cae0(float* v) {
  SP_GetRandomDirection3(v);
  float x = v[0], y = v[1];
  float s = 1.0f / sqrtf(x * x + y * y + gK_13ec4b8);
  v[0] = x * s;
  v[1] = y * s;
  v[2] = s * 0.0f;
  return v;
}

// @ 0x00e5cb60
int FUN_00e5cb60(float* m, int a, int b, char* box, int d, char* flags, int e) {
  if (a != d) return 0;
  float hx = m[5] + m[2];
  float hy = m[6] + m[3];
  float hz = m[7] + m[4];
  float half = gK_1470f1c;
  (void)flags; (void)b; (void)e;
  float ox, oy, oz;
  if (box[0] & 2) {
    ox = 0; oy = 0; oz = 0;  // approximate; see partial.txt
    (void)ox; (void)oy; (void)oz;
  } else {
    ox = hx * half; oy = hy * half; oz = hz * half;
  }
  return 0;
}

// @ 0x00e5cd00
bool FUN_00e5cd00(char* e) {
  float x = *(float*)(e + 0x4c);
  float y = *(float*)(e + 0x50);
  float z = *(float*)(e + 0x54);
  float r = (*(float*)(e + 0x58) * gK_13f94f4) * gK_1470f1c;
  float d = 0.0f;
  if (x < gBox_16b3c88) d = (x - gBox_16b3c88) * (x - gBox_16b3c88);
  else if (x > gBox_16b3c94) d = (x - gBox_16b3c94) * (x - gBox_16b3c94);
  if (y < gBox_16b3c8c) d += (y - gBox_16b3c8c) * (y - gBox_16b3c8c);
  else if (y > gBox_16b3c98) d += (y - gBox_16b3c98) * (y - gBox_16b3c98);
  if (z < gBox_16b3c90) d += (z - gBox_16b3c90) * (z - gBox_16b3c90);
  else if (z > gBox_16b3c9c) d += (z - gBox_16b3c9c) * (z - gBox_16b3c9c);
  return d > r * r;
}

// @ 0x00e5cde0
bool FUN_00e5cde0(char* e) {
  if (*(int*)((char*)gCellGame_16b3c04 + 0x51d4) == *(int*)e) return false;
  if (*(int*)e == *(int*)((char*)gCellGame_16b3c04 + 0x411c)) return false;
  float cx = *(float*)(e + 0x4c);
  float cy = *(float*)(e + 0x50);
  float cz = *(float*)(e + 0x54);
  float r = *(float*)(e + 0x58) * gK_13f94f4;
  if (*(int*)(e + 0x35c) == *(int*)((char*)gCellGame_16b3c04 + 0x40fc)) {
    float box[3] = {cx, cy, cz};
    return !FUN_00743fb0(box, r, &gBox_16b3c88);
  }
  float p[3] = {cx, cy, cz};
  p[2] = *(float*)(e + 0x80);
  uint8_t b = FUN_006ffbd0((void*)0x16b3cb8, p, r);
  return (b >> 6) & 1;
}
