// SP::cSPPlayMode / cSPPlayMode_Creature helpers. Region 0x62ca80-0x62da05.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

typedef void (__thiscall *TF0)(void*);
typedef void (__thiscall *TF1)(void*, int);

extern void* gThemeMusicVt; // 0x14774b0
extern void* gVt13fe1bc;    // 0x13fe1bc
extern void* gVt13ec458;    // 0x13ec458

struct Vec12 { void* a; void* b; void* c; };

// @ 0x0062ca80
struct BlockPath { void BlockCircle(float x, float y, float z, int one); };
void __fastcall FUN_0062ca80(void* self) {
  char* s = (char*)self;
  char* mgr = *(char**)(s + 0x14);
  int n = (*(int*)(mgr + 0x80) - *(int*)(mgr + 0x7c)) >> 2;
  if (n == 1) return;
  for (int i = 0; i < n; ++i) {
    char* c = *(char**)(*(int*)(mgr + 0x7c) + i * 4);
    if (c == s) continue;
    char* e = *(char**)(*(char**)(c + 8) + 0x180);
    float x = *(float*)(c + 0x20) + *(float*)(s + 0x20);
    ((BlockPath*)*(void**)(s + 0x18))->BlockCircle(*(float*)(e + 0xc), *(float*)(e + 0x10), x, 1);
  }
}

// @ 0x0062cb20
extern "C" void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b, int c, int d);
struct ThemeMusic { int pad[16]; };
void* __stdcall FUN_0062cb20(void* src, float a, char b, float c) {
  char* o = (char*)EA_Allocate(0x2c, "Casual", 0, 0, 0, 0);
  if (o != 0) {
    *(void**)(o + 4) = 0;
    *(void**)o = (void*)&gThemeMusicVt;
  } else {
    o = 0;
  }
  int s0 = ((int*)src)[0];
  int s1 = ((int*)src)[1];
  int s2 = ((int*)src)[2];
  *(int*)(o + 8) = s0;
  *(int*)(o + 0xc) = s1;
  *(int*)(o + 0x10) = s2;
  *(float*)(o + 0x20) = a;
  *(unsigned char*)(o + 0x2a) = 0;
  *(unsigned char*)(o + 0x29) = 0;
  *(unsigned char*)(o + 0x2b) = 0;
  *(unsigned char*)(o + 0x28) = b;
  *(float*)(o + 0x24) = c;
  return o;
}

// @ 0x0062cb90
void __fastcall FUN_0062cb90(void* self) {
  char* s = (char*)self;
  int n = (*(int*)(s + 0x40) - *(int*)(s + 0x3c)) >> 2;
  if (n > 0) {
    do {
      *(int*)(s + 0x40) -= 4;
      int o = **(int**)(s + 0x40);
      if (o != 0) {
        char* vt = *(char**)o;
        ((TF0)(*(void**)(vt + 8)))((void*)o);
      }
      --n;
    } while (n != 0);
  }
}

// @ 0x0062cbc0
int __fastcall FUN_0062cbc0(void* self, float* p) {
  int obj = **(int**)((char*)self + 0x3c);
  if (fabsf(*(float*)(obj + 8) - p[0]) < 1.52587890625e-05f &&
      fabsf(*(float*)(obj + 0xc) - p[1]) < 1.52587890625e-05f)
    return 1;
  return 0;
}

// @ 0x0062cc20
void __fastcall FUN_0062cc20(void* self, float* p) { (void)self; (void)p; }

// @ 0x0062cd30
void* __fastcall FUN_0062cd30(void* self) {
  char* s = (char*)self;
  *(int*)(s + 4) = 0;
  *(void**)s = (void*)&gVt13fe1bc;
  *(int*)(s + 0x18) = 0;
  *(int*)(s + 0x38) = 0;
  Vec12* vec = (Vec12*)(s + 0x3c);
  vec->a = 0; vec->b = 0; vec->c = 0;
  *(int*)(s + 8) = 0;
  *(int*)(s + 0xc) = 0;
  *(int*)(s + 0x10) = 0;
  *(int*)(s + 0x1c) = -1;
  *(float*)(s + 0x20) = 0.0f;
  *(unsigned char*)(s + 0x24) = 0;
  *(float*)(s + 0x28) = 0.0f;
  *(float*)(s + 0x34) = 0.0f;
  return self;
}

// @ 0x0062cdb0
extern void __fastcall VecDtorFn(void*);
extern "C" void __cdecl EASTL_free(void*);
void* __fastcall FUN_0062cdb0(void* self, char flag) {
  char* s = (char*)self;
  *(void**)s = (void*)&gVt13fe1bc;
  VecDtorFn(s + 0x3c);
  {
    void* p = *(void**)(s + 0x38);
    if (p != 0) { ((TF0)(*(void**)(*(char**)p + 8)))(p); }
  }
  {
    void* p = *(void**)(s + 0x18);
    if (p != 0) { ((TF0)(*(void**)(*(char**)p + 8)))(p); }
  }
  *(void**)s = (void*)&gVt13ec458;
  if (flag & 1) {
    EASTL_free(s);
  }
  return self;
}

// @ 0x0062ce00
void __fastcall FUN_0062ce00(void* self, void*, char) { (void)self; }

// @ 0x0062cef0
void __fastcall FUN_0062cef0(void* self) { (void)self; }

// @ 0x0062d0f0
void __fastcall FUN_0062d0f0(void* self) { (void)self; }

// @ 0x0062d8a0
void __fastcall FUN_0062d8a0(void* self, float, float) { (void)self; }
