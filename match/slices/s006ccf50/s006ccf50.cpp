// Slice s006ccf50: mesh/attribute bake evaluators (acos-angle variants).
#include "s006ccf50.h"

// uv2u16 / colour4u8 / acos(weight res.z)
DEFINE_BAKE(Bake_6ccf50, 0, 2, 1, 0, 0)   // @ 0x006ccf50
// uv4u16 / colour4u8 / acos(weight res.z)
DEFINE_BAKE(Bake_6cd2a0, 0, 4, 1, 0, 0)   // @ 0x006cd2a0
// uv4u8  / colour4f  / acos(weight res.z)
DEFINE_BAKE(Bake_6cd620, 0, 4, 0, 1, 0)   // @ 0x006cd620
// uv2u16 / colour4f  / acos(weight res.z)
DEFINE_BAKE(Bake_6cd980, 0, 2, 1, 1, 0)   // @ 0x006cd980
