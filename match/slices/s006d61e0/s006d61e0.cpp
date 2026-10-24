// Slice s006d61e0: bake evaluators (dot + first acos2).
// Uses a local copy of the s006ccf50 bake macro so the SSE math helpers are
// compiled from this slice's own directory (the shared header is edited by
// other slices concurrently and is not part of this TU's build cache key).
#include "bake.h"

DEFINE_BAKE(Bake_6d61e0, 0, 4, 1, 1, 1)   // @ 0x006d61e0 Bake_6d61e0  uv4u16 / colour4f / dot
DEFINE_BAKE(Bake_6d64f0, 2, 4, 0, 3, 2)   // @ 0x006d64f0 Bake_6d64f0  uv4u8  / const    / acos2
DEFINE_BAKE(Bake_6d6820, 2, 2, 1, 3, 2)   // @ 0x006d6820 Bake_6d6820  uv2u16 / const    / acos2
DEFINE_BAKE(Bake_6d6b10, 2, 4, 1, 3, 2)   // @ 0x006d6b10 Bake_6d6b10  uv4u16 / const    / acos2
