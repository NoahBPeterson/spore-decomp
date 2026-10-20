// slice s00fa7450 -- SP::cTerrainSphere::DrawLayer / DrawLayerBackgroundUpdate.
// Object file: SPTerrain/SPTerrainSphere.obj.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
//   0x00fa7450 SP::cTerrainSphere::DrawLayerBackgroundUpdate
//   0x00fa74d0 SP::cTerrainSphere::DrawLayer
#include "types.h"
#include <stddef.h>

// ---------------------------------------------------------------- externals
void* __cdecl FUN_00f48a70();              // 0x00f48a70 SP::TerrainEditor()
void  __stdcall FUN_00f9fe70(void*, void*); // 0x00f9fe70 layer-update tail helper
void  __cdecl FUN_006dd2a0(void*);         // 0x006dd2a0 active-state flush (void*)
void  __cdecl FUN_00777ae0(int, void*, int); // 0x00777ae0 shader binding (int, void*, int)
void  __cdecl FUN_00f97e60();              // 0x00f97e60 layer visibility predicate
void  __cdecl FUN_00fa6870();              // 0x00fa6870 UpdateLightingRegions
void  __cdecl FUN_00f6bd70();              // 0x00f6bd70 cTerrainEditor::UpdateCPUFromGPU
void  __cdecl FUN_00f67580();              // 0x00f67580 cTerrainEditor helper
void  __cdecl FUN_00f6a3a0();              // 0x00f6a3a0 cTerrainEditor predicate
void  __cdecl FUN_00f9bb50();              // 0x00f9bb50 cTerrainSphere helper
void  __cdecl FUN_006a25a0();              // 0x006a25a0 cPropertyList::GetDescription
void  __cdecl FUN_006a17e0();              // 0x006a17e0 cPropertyList::SetBoolProperty
void  __cdecl FUN_00f678a0();              // 0x00f678a0 cTerrainEditor predicate
void  __cdecl FUN_00f9ba40();              // 0x00f9ba40 set active sky state
void  __cdecl FUN_00f98970();              // 0x00f98970 SkyState::Update
void  __cdecl FUN_00fa5cc0();              // 0x00fa5cc0 DrawLayerBackground
void  __cdecl FUN_00f9bd00();              // 0x00f9bd00 DrawLayerTerrain

// ---------------------------------------------------------------- fn-ptr types
typedef void  (__thiscall *TV0)(void*);
typedef char  (__thiscall *TV0c)(void*);
typedef void  (__thiscall *TV1)(void*, void*);
typedef char  (__thiscall *TV1c)(void*, void*);
typedef void  (__thiscall *TV1u)(void*, uint32_t);
typedef void  (__thiscall *TV2ii)(void*, int, int);
typedef void  (__thiscall *TV3u)(void*, void*, void*, void*);

class cTerrainSphere {
 public:
  void DrawLayerBackgroundUpdate(void* unused, void* p1, void* p2);
  void DrawLayer(void* p0, int p1, void* p2, void* p3);
};

#define SELF      ((char*)this)
#define INTV(off) (*(int*)(SELF + (off)))
#define U8V(off)  (*(uint8_t*)(SELF + (off)))

// ================================================================ 0x00fa7450
// @ 0x00fa7450
void cTerrainSphere::DrawLayerBackgroundUpdate(void* unused, void* p1, void* p2) {
  (void)unused;
  if (INTV(0xa48) != 0) return;
  if (!((TV1c)FUN_00f97e60)(this, p1)) return;
  ((TV1u)FUN_00f6bd70)(FUN_00f48a70(), (uint32_t)(uintptr_t)p1);
  ((TV1)FUN_00fa6870)(this, p1);
  if (U8V(0x348) != 0) {
    ((TV2ii)FUN_00f67580)(FUN_00f48a70(), -1, 1);
    if (((TV1c)FUN_00f6a3a0)(FUN_00f48a70(), p1)) U8V(0x348) = 0;
  }
  ((TV0)FUN_00f9bb50)(this);
  FUN_00f9fe70(p1, p2);
}

// ================================================================ 0x00fa74d0
// @ 0x00fa74d0
void cTerrainSphere::DrawLayer(void* p0, int p1, void* p2, void* p3) {
  if (INTV(0xa44) != 0) return;
  void* ap = *(void**)0x15fd918;
  if (((TV1c)FUN_006a25a0)(ap, (void*)0x2955532f))
    ((TV2ii)FUN_006a17e0)(ap, 0x2955532f, 0);
  if (INTV(0x208) == 0) return;
  if (*(int*)(*(char**)((char*)ap + 0x3c) + 0x10) == 0) return;
  char* b = (char*)this - 4;
  ((TV1u)FUN_00f9ba40)(b, *(uint32_t*)p2);
  ((TV0)FUN_00f98970)(b);
  FUN_00777ae0(0x305, (char*)this + 0x4f4, 0);
  FUN_00777ae0(0x306, (char*)this + 0x6c4, 0);
  if (p1 == 0x21) ((cTerrainSphere*)b)->DrawLayerBackgroundUpdate(p2, p3, p0);
  char c = ((TV0c)FUN_00f678a0)(FUN_00f48a70());
  if (!c && U8V(0x4f0) && U8V(0x4f1)) {
    FUN_006dd2a0(*(void**)0x16c9e78);
    if (p1 == 7) { ((TV3u)FUN_00fa5cc0)(b, p2, p3, p0); return; }
    if (p1 == 8) ((TV3u)FUN_00f9bd00)(b, p2, p3, p0);
  }
}
