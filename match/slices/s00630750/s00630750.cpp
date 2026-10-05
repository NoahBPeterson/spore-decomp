// SP::cSPPlayModePhotoBrowser helpers / EASTL instantiations. Region 0x630750-0x631b90.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

typedef void (__thiscall *TF0)(void*);
typedef void (__thiscall *TF1)(void*, int);

extern "C" void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b, const char* file, int line);
extern "C" void  __cdecl EA_Free(void*);
extern void* gVt13fe518;    // 0x13fe518
extern void* gVt13fe528;    // 0x13fe528
extern void* gVt13ec458;    // 0x13ec458

struct RefObj { virtual void s0(); virtual void s1(); virtual void s2(); };

// @ 0x00630750  basic_string<wchar_t> ctor from [first,last)
struct WStr {
  short* begin; short* end; short* cap;
  void AllocateSelf(int n);
  void Append(const short* first, const short* last);
};
void* __fastcall FUN_00630750(void* self, short* first, short* last, int) {
  WStr* s = (WStr*)self;
  s->begin = 0; s->end = 0; s->cap = 0;
  int n = ((char*)last - (char*)first) >> 1;
  s->AllocateSelf(n + 1);
  short* dst = s->begin;
  memcpy(dst, first, n * 2);
  short* e = dst + n;
  s->end = e;
  *e = 0;
  return self;
}

// @ 0x006307a0
extern "C" void __cdecl RBTreeInsert(void* node, void* pos, void* root, char b);
void __fastcall FUN_006307a0(void* self, int* out, int* pos, unsigned* val, char flag) {
  char* s = (char*)self;
  char b;
  if (flag == 0 && pos != (int*)(s + 4) && *val >= *(unsigned*)((char*)pos + 0x10))
    b = 1;
  else
    b = 0;
  char* node = (char*)EA_Allocate(0x24, "Editor", 0, 0,
                                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  if (node + 0x10 != 0) {
    *(unsigned*)(node + 0x10) = val[0];
    *(unsigned*)(node + 0x14) = val[1];
    *(unsigned*)(node + 0x18) = val[2];
    *(unsigned*)(node + 0x1c) = val[3];
    *(unsigned*)(node + 0x20) = val[4];
  }
  RBTreeInsert(node, pos, s + 4, b);
  ++*(int*)(s + 0x14);
  *out = (int)node;
}

// @ 0x006308d0
struct Job { void GetStatus(); };
void* __fastcall FUN_006308d0(void* self, char flag) {
  char* s = (char*)self;
  *(void**)s = (void*)&gVt13fe518;
  {
    void* p = *(void**)(s + 0x34);
    if (p != 0) ((Job*)p)->GetStatus();
  }
  {
    void* p = *(void**)(s + 0x30);
    if (p != 0) ((Job*)p)->GetStatus();
  }
  {
    void* p = *(void**)(s + 0x20);
    unsigned n = (*(unsigned*)(s + 0x28) - (unsigned)p) & 0xfffffffe;
    if (n > 2 && p != 0) EA_Free(p);
  }
  *(void**)s = (void*)&gVt13ec458;
  if (flag & 1) EA_Free(s);
  return self;
}

// @ 0x00630930
void __fastcall FUN_00630930(void* self) { (void)self; }

// @ 0x006309e0
void* __cdecl FUN_006309e0(void* out, const short* lhs, const WStr* rhs) {
  const short* p = lhs;
  while (*p) ++p;
  int n = (int)(p - lhs);
  int len = (int)(rhs->end - rhs->begin) >> 1;
  WStr* o = (WStr*)out;
  o->begin = 0; o->end = 0; o->cap = 0;
  int total = len + n;
  o->AllocateSelf(total + 1);
  *o->end = 0;
  o->Append(lhs, lhs + n);
  o->Append(rhs->begin, rhs->end);
  return out;
}

// @ 0x00630a50
struct Ent24 { int f0, f4, f8, fc, f10, f14, f18, f1c, f20; };
void __fastcall FUN_00630a50(void* self) {
  char* a = (char*)self;
  *(void**)a = (void*)&gVt13fe528;
  *(int*)(a + 4) = 0;
  *(int*)(a + 8) = 0;
  *(int*)(a + 0xc) = 0;
  *(int*)(a + 0x18) = 0;
  *(unsigned char*)(a + 0x20) = 0;
  *(int*)(a + 0x28) = 0;
  *(int*)(a + 0x2c) = 0;
  *(int*)(a + 0x30) = 0;
  *(int*)(a + 0x50) = 0;
  *(int*)(a + 0x54) = 0;
  *(int*)(a + 0x6c + 4) = 0;
  *(int*)(a + 0x6c + 8) = 0;
  *(int*)(a + 0x6c + 0xc) = 0;
  *(void**)(a + 0x6c) = (void*)(a + 0x6c);
  *(int*)(a + 0x70) = (int)(a + 0x6c);
  *(int*)(a + 0x74) = 0;
  *(unsigned char*)(a + 0x78) = 0;
  *(int*)(a + 0x7c) = 0;
  Ent24* e = (Ent24*)(a + 0x84);
  for (int i = 0x62; i >= 0; --i) {
    e->f0 = 0; e->f4 = 0; e->f8 = 0; e->f14 = 0; e->f18 = 0; e->f1c = 0; e->f20 = 0;
    e = (Ent24*)((char*)e + 0x24);
  }
  *(int*)(a + 0xe70) = 0;
  *(int*)(a + 0xe74) = 4;
  *(int*)(a + 0xe78) = 0;
  *(int*)(a + 0xe7c) = 0;
  *(int*)(a + 0xe80) = 0;
  *(int*)(a + 0xe8c) = 0;
  *(int*)(a + 0xe90) = 0;
  *(int*)(a + 0xe94) = 0;
  *(int*)(a + 0xe98) = 0;
  *(int*)(a + 0xe9c) = 0;
  *(int*)(a + 0xea0) = 0;
  *(int*)(a + 0xea8) = 0;
}

// @ 0x00630b30
void __fastcall FUN_00630b30(void* self, int* pos, int* val) {
  int* v = (int*)self;
  int* end = (int*)v[1];
  if (end != (int*)v[2]) {
    int* src = val;
    if (val >= pos && val < end) src = val + 1;
    if (end != 0) *end = end[-1];
    unsigned n = (unsigned)((char*)(v[1] - 1) - (char*)pos);
    memmove((char*)v[1] - ((int)n >> 2) * 4, pos, n);
    *pos = *src;
    v[1] += 1;
    return;
  }
  int cap = (int)((char*)end - (char*)v[0]) >> 2;
  if (cap == 0) cap = 1; else cap *= 2;
  int* dst;
  if (cap == 0) dst = 0;
  else dst = (int*)EA_Allocate(cap * 4, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  unsigned n1 = (unsigned)((char*)pos - (char*)v[0]);
  int* p = (int*)((char*)dst + ((int)n1 >> 2) * 4);
  if (p != 0) *p = *val;
  int* oldEnd = (int*)v[1];
  memmove(p + 1, pos, (char*)oldEnd - (char*)pos);
  if (v[0] != 0 && *(int*)((char*)v[0] - 4) != 0) EA_Free((void*)v[0]);
  v[0] = (int)dst;
  v[1] = (int)((char*)p + 4 + (((char*)oldEnd - (char*)pos) >> 2) * 4);
  v[2] = (int)((char*)dst + cap * 4);
}

// @ 0x00630d10
void __fastcall FUN_00630d10(void* self) { (void)self; }

// @ 0x00630f20
void __fastcall FUN_00630f20(void* self) { (void)self; }

// @ 0x006312f0
void __fastcall FUN_006312f0(void* self) { (void)self; }
