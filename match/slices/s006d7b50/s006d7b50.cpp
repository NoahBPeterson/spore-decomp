// Slice s006d7b50: bake evaluators (core 6c4200 / 6c3b90, acos len tail).
// Local copy of the shared bake template (colour2f reads 3 floats, not white).
#include "s006d7b50.h"

// uv2u16 / colour2f / core FUN_006c3b90 / acos weight (axis.y * len)
DEFINE_BAKE(Bake_6d7b50, 1, 2, 1, 2, 2)   // @ 0x006d7b50
// uv4u16 / colour2f / core FUN_006c3b90 / acos weight (axis.y * len)
DEFINE_BAKE(Bake_6d7e70, 1, 4, 1, 2, 2)   // @ 0x006d7e70
// uv4u8  / colour4u8 / core FUN_006c4200 / acos weight (axis.y * len)
DEFINE_BAKE(Bake_6d81c0, 0, 4, 0, 0, 2)   // @ 0x006d81c0
// uv2u16 / colour4u8 / core FUN_006c4200 / acos weight (axis.y * len)
DEFINE_BAKE(Bake_6d8540, 0, 2, 1, 0, 2)   // @ 0x006d8540
