// src/game/SPEngine/_at_00670000.cpp -- migrated from slice(s) s0067c450 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00670000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_016f6ed0;
extern void* g_016f6eb0;
extern void* g_016f6eb4;
extern float* g_016f6e74;
extern float* g_016f6e7c;
extern float* g_016f6e80;
extern float* g_016f6e98;
extern "C" void FUN_011f4270(int, void*, void*, void*, void*);
extern "C" void FUN_0067cf20();
extern unsigned int g_015fd88c;

// ---- items of slice s0067c450 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (__stdcall *SRegFn)(void*, void*, void*, int);
struct SO { SRegFn* vt; };
extern SO* g_016f89d0;             // D3D9 device object (vtable owner)
extern void* g_016f6ed0;
extern void* g_016f6eb0;
extern void* g_016f6eb4;
extern float* g_016f6e74;
extern float* g_016f6e7c;
extern float* g_016f6e80;
extern float* g_016f6e98;
extern "C" void FUN_011f4270(int, void*, void*, void*, void*);
extern "C" void FUN_0067cf20();
extern unsigned int g_015fd88c;
struct Allocator {
  void* Alloc(unsigned int size, int a, int b, int c, int d, int e);
  void Free(void* p);
};
extern Allocator* g_16c8b44;
// ---- items of slice s0067c450 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern SO* g_016f89d0;             // D3D9 device object (vtable owner)
extern Allocator* g_16c8b44;

// @ 0x0067cc70
void FUN_0067cc70(void* a, void* b, int c)
{
  if (c)
    g_016f89d0->vt[94](g_016f89d0, a, g_016f6ed0, 3);
  else
    g_016f89d0->vt[109](g_016f89d0, a, g_016f6ed0, 3);
}

// @ 0x0067cca0
void FUN_0067cca0(void* a, void* b, int c)
{
  if (g_016f6eb0) {
    if (c)
      g_016f89d0->vt[94](g_016f89d0, a, g_016f6eb0, 4);
    else
      g_016f89d0->vt[109](g_016f89d0, a, g_016f6eb0, 4);
  }
}

// @ 0x0067cce0
void FUN_0067cce0(void* a, void* b, int c)
{
  if (g_016f6eb4) {
    if (c)
      g_016f89d0->vt[94](g_016f89d0, a, g_016f6eb4, 9);
    else
      g_016f89d0->vt[109](g_016f89d0, a, g_016f6eb4, 9);
  }
}

// @ 0x0067cd20
void FUN_0067cd20(void* a, void* b, int c)
{
  if (g_016f6e74) {
    float values[4] = {1.0f, 1.0f, 1.0f, g_016f6e74[0]};
    if (c)
      g_016f89d0->vt[94](g_016f89d0, a, values, 1);
    else
      g_016f89d0->vt[109](g_016f89d0, a, values, 1);
  }
}

// @ 0x0067cd90
void FUN_0067cd90(void* a, void* b, int c)
{
  if (g_016f6e7c) {
    float values[4] = {1.0f, 1.0f, 1.0f, g_016f6e7c[0]};
    if (c)
      g_016f89d0->vt[94](g_016f89d0, a, values, 1);
    else
      g_016f89d0->vt[109](g_016f89d0, a, values, 1);
  }
}

// @ 0x0067ce00
void FUN_0067ce00(void* a, void* b, int c)
{
  float values[12] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  if (g_016f6e98) {
    for (int i = 0; i < 12; ++i) values[i] = g_016f6e98[i];
  }
  if (c)
    g_016f89d0->vt[94](g_016f89d0, a, values, 3);
  else
    g_016f89d0->vt[109](g_016f89d0, a, values, 3);
}

// @ 0x0067d020
void FUN_0067d020(void* a, void* b, int c)
{
  float values[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  if (g_016f6e80) {
    values[0] = g_016f6e80[0];
  }
  if (c)
    g_016f89d0->vt[94](g_016f89d0, a, values, 1);
  else
    g_016f89d0->vt[109](g_016f89d0, a, values, 1);
}

// @ 0x0067d0c0
void FUN_0067d0c0()
{
  FUN_011f4270(0x236, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067d020);
  *(unsigned int*)0x16327c8 = 4;
  FUN_011f4270(0x238, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0);
  *(unsigned int*)0x16327d0 = 1;
  FUN_011f4270(0x233, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cd20);
  *(unsigned int*)0x16327bc = 4;
  FUN_011f4270(0x235, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cd90);
  *(unsigned int*)0x16327c4 = 4;
  FUN_011f4270(0x23c, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067ce00);
  *(unsigned int*)0x16327e0 = 0x30;
  FUN_011f4270(0x241, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cf20);
  *(unsigned int*)0x16327f4 = 0x40;
  FUN_011f4270(0x242, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cca0);
  *(unsigned int*)0x16327f8 = 0x40;
  FUN_011f4270(0x243, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cce0);
  *(unsigned int*)0x16327fc = 0x90;
  FUN_011f4270(0x24a, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)0xc2e4e0, (void*)FUN_0067cc70);
  *(unsigned int*)0x1632818 = 0x30;
}

// @ 0x0067d230
extern "C" void* __cdecl FUN_0067d230(void* opaque, unsigned int items, unsigned int size)
{
  g_015fd88c += size;
  return g_16c8b44->Alloc(items * size, 0, 0, 0, 0, 0);
}

// @ 0x0067d260
extern "C" void __cdecl FUN_0067d260(void* opaque, void* p)
{
  g_16c8b44->Free(p);
}
