// src/game/SPCreatureAnim/context.cpp -- migrated from slice(s) s009afda0 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/context.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/context_target.h"

// ---- items of slice s009afda0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace nSPCreatureAnim {
void MirrorSagittalContextTarget(uint32_t* src, uint32_t* dst);
}
// ---- items of slice s009afda0 end

// @ 0x009b0280
void __cdecl nSPCreatureAnim::MirrorSagittalContextTarget(uint32_t* src, uint32_t* dst)
{
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  dst[3] = src[3];

  uint32_t f = src[0] & 0x2000c;
  if (f > 0x20000) {
    if (f == 0x20004)
      f = 0x20000;
  } else {
    if (f == 0x20000)
      f = 0x20004;
    else if (f == 4)
      f = 8;
    else if (f == 8)
      f = 4;
  }
  uint32_t v = (dst[0] & 0xfffdfff3) | f;

  uint32_t g = src[0] & 0xe000;
  if (g == 0x2000)
    g = 0x4000;
  else if (g == 0x4000)
    g = 0x2000;

  dst[0] = (v & 0xffff1fff) | g;
}
