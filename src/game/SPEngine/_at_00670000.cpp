// src/game/SPEngine/_at_00670000.cpp
// Object file: SPEngine/_at_00670000.obj.
// D3D9 register helpers and the register-table setup that feeds them.
// Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" void FUN_00c2e4e0();
extern "C" char g_16327bc[];

// Retail globals used by this module. The name is the slice's own unnamed
// name; the address is in each comment.
extern void* g_016f6ed0;   // 0x016f6ed0: constant block (role is a guess)
extern void* g_016f6eb0;   // 0x016f6eb0
extern void* g_016f6eb4;   // 0x016f6eb4
extern float* g_016f6e74;  // 0x016f6e74
extern float* g_016f6e7c;  // 0x016f6e7c
extern float* g_016f6e80;  // 0x016f6e80
extern float* g_016f6e98;  // 0x016f6e98: 12-float constant block
extern unsigned int g_015fd88c;  // 0x015fd88c: running byte total for FUN_0067d230

// Retail callees (addresses in the names).
extern "C" void FUN_011f4270(int, void*, void*, void*, void*);  // register-table insert
extern "C" void FUN_0067cf20();                                  // register-table callback for key 0x241

// Local stand-ins until canonical classes exist for these objects.
// TODO: replace with the canonical D3D9 device class if one is added to src/game/include.
typedef void (__stdcall *SRegFn)(void*, void*, void*, int);
struct D3D9Device {  // name is a guess; only the vtable layout is known
  SRegFn* vt;
};
extern D3D9Device* g_016f89d0;  // 0x016f89d0: D3D9 device object (vtable owner)

struct Allocator {  // name is a guess
  void* Alloc(unsigned int size, int a, int b, int c, int d, int e);
  void Free(void* p);
};
extern Allocator* g_16c8b44;  // 0x016c8b44

// @ 0x0067cc70
void FUN_0067cc70(void* a, void* b, int c)
{  void* constants = g_016f6ed0;
  if (c)
    g_016f89d0->vt[94](g_016f89d0, a, constants, 3);
  else
    g_016f89d0->vt[109](g_016f89d0, a, constants, 3);
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
  struct Float4 {
    float x, y, z, w;
    Float4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
  };
  Float4 v(0.0f, 0.0f, 0.0f, 0.0f);
  if (g_016f6e80)
    v = Float4(g_016f6e80[0], 0.0f, 0.0f, 0.0f);
  float* values = &v.x;
  if (c)
    g_016f89d0->vt[94](g_016f89d0, a, values, 1);
  else
    g_016f89d0->vt[109](g_016f89d0, a, values, 1);
}

// Argument block passed as the three pointer slots of every register-table insert.
#define kZeroBlock ((void*)FUN_00c2e4e0)   // 0x00c2e4e0 (a #define: a function address is no constant initializer to cl)

// @ 0x0067d0c0
void FUN_0067d0c0()
{
  FUN_011f4270(0x236, kZeroBlock, kZeroBlock, kZeroBlock, (void*)FUN_0067d020);
  *(unsigned int*)((char*)&g_16327bc + 0xc) = 4;
  FUN_011f4270(0x238, kZeroBlock, kZeroBlock, kZeroBlock, (void*)0);
  *(unsigned int*)((char*)&g_16327bc + 0x14) = 1;
  FUN_011f4270(0x233, kZeroBlock, kZeroBlock, kZeroBlock, (void*)FUN_0067cd20);
  *(unsigned int*)g_16327bc = 4;
  FUN_011f4270(0x235, kZeroBlock, kZeroBlock, kZeroBlock, (void*)FUN_0067cd90);
  *(unsigned int*)((char*)&g_16327bc + 0x8) = 4;
  FUN_011f4270(0x23c, kZeroBlock, kZeroBlock, kZeroBlock, (void*)FUN_0067ce00);
  *(unsigned int*)((char*)&g_16327bc + 0x24) = 0x30;
  FUN_011f4270(0x241, kZeroBlock, kZeroBlock, kZeroBlock, (void*)FUN_0067cf20);
  *(unsigned int*)((char*)&g_16327bc + 0x38) = 0x40;
  FUN_011f4270(0x242, kZeroBlock, kZeroBlock, kZeroBlock, (void*)FUN_0067cca0);
  *(unsigned int*)((char*)&g_16327bc + 0x3c) = 0x40;
  FUN_011f4270(0x243, kZeroBlock, kZeroBlock, kZeroBlock, (void*)FUN_0067cce0);
  *(unsigned int*)((char*)&g_16327bc + 0x40) = 0x90;
  FUN_011f4270(0x24a, kZeroBlock, kZeroBlock, kZeroBlock, (void*)FUN_0067cc70);
  *(unsigned int*)((char*)&g_16327bc + 0x5c) = 0x30;
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
