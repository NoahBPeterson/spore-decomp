// src/game/cmn/fft.cpp.cpp -- migrated from slice(s) s0115de20 by tools/migrate/rewrite.py
// Object file: cmn/fft.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"
#include <math.h>

// ---- items of slice s0115de20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
class System_s0115_de20 {
 public:
    void* Alloc(uint32_t size, const char* name, uint32_t align, uint32_t flags);  // 0x0112c820
    void  Free(void* p, uint32_t flags);                                             // 0x0112c850
};
}
}  // namespace rw::audio::core
}
extern rw::audio::core::System_s0115_de20* gAudioSystem;  // 0x016e61a8
struct FftTable {
    int   log2n;          // +0x00  log2 of the real FFT size, minus one
    int   half;           // +0x04  cos/sin table length (size/2 + 1)
    int   size;           // +0x08  real FFT size / 2
    int   cosOffset;      // +0x0c  float cos[]
    int   sinOffset;      // +0x10  float sin[]
    int   bitrevOffset;   // +0x14  int   bitrev[]
};
struct FftPair {
    FftTable* table;      // +0x00
    unsigned  size;       // +0x04
};
// ---- items of slice s0115de20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern rw::audio::core::System_s0115_de20* gAudioSystem;  // 0x016e61a8

// @ 0x0115e330
int FFT_Alloc(int n, char flag, FftPair* out)
{
    if (!flag)
        --n;
    unsigned size = 1u << n;
    int half = (int)(size / 2) + 1;
    unsigned bytes = (size + 2u * half + 8u) * 4u;
    FftTable* table = (FftTable*)gAudioSystem->Alloc(bytes, "FFT instance", 0x80, 0);
    if (!table) {
        out->table = 0;
        out->size = 0;
        return -1;
    }
    int sinOffset = 0x18 + half * 4;
    table->sinOffset = sinOffset;
    table->size = (int)size;
    table->half = half;
    table->bitrevOffset = sinOffset + half * 4;
    table->log2n = n;
    table->cosOffset = 0x18;
    out->table = table;
    out->size = bytes;
    return 0;
}

// @ 0x0115e3c0
int FFT_Free(FftPair* out)
{
    gAudioSystem->Free(out->table, 0);
    out->table = 0;
    out->size = 0;
    return 0;
}
