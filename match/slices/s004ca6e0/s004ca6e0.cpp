// Slice s004ca6e0: SP::cSkinObject rebuild of nodes / bones / bone transforms from the
// resource's block array (stride 0x8c).  Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
//
// NOTE: this function is 3153 bytes.  Ghidra's decompile loses several frame locals
// (a block-index array base and the per-node scratch vector live in unnamed slots that
// it prints as uninitialised locals), so a behaviourally complete transcription cannot
// be reconstructed from the decompile alone in this pass.  The skeleton below mirrors
// the recovered high-level structure (clear node/bone/transform vectors, build the
// index map, copy node positions, then rebuild bone transforms) and is kept only so the
// slice compiles; it is listed in partial.txt.
#include "types.h"

#pragma pack(push, 4)

class cSkinObject;

// Recovered callees (masked relocations).
extern "C" int FUN_00455ae0(...);   // clear vector
extern "C" int FUN_004ce110(...);   // clear vector
extern "C" int VecPairErase(...);   // 0x00530c80 erase
extern "C" int FUN_004238c0(...);   // clear vector
extern "C" int FUN_004cd5b0(...);   // reserve
extern "C" int FUN_004cd440(...);   // reserve
extern "C" int FUN_0041e3b0(...);   // resize
extern "C" int FUN_00422740(...);   // resize
extern "C" int FUN_0041dc10(...);
extern "C" int FUN_0041dca0(...);
extern "C" int Unchecked_idl0(...);
extern "C" int FUN_0041ddb0(...);
extern "C" int FUN_00422380(...);
extern "C" int FUN_004c0b80(...);

// @ 0x004CA6E0
bool cSkinObject_RebuildNodes(uint32_t self)
{
    uint8_t* resource = *(uint8_t**)(self + 8);
    uint8_t* blocks   = *(uint8_t**)(resource + 0x98);
    int count = (int)(*(uint32_t*)(resource + 0x9c) - *(uint32_t*)(resource + 0x98)) / 0x8c;
    if (count == 0)
        return false;

    // The full per-node rebuild is not recovered (see header note).
    FUN_00455ae0(*(void**)(self + 0x7c), *(void**)(self + 0x80));
    return true;
}
