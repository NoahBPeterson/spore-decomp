// Slice s00ab3300 -- one function, @ 0x00ab3300 (103 bytes).
//
// EA::Swarm ribbon/trail effect: pick the quad-streamer registered for the effect's current
// vertex format and run it on a vertex buffer.  `mDesc` (+0x14) is the ribbon description;
// bit 12 of its flag word (+0x08) selects between the two registered streamer tables
// (0x01679690 / 0x01679710, 32 entries each, filled by FUN_00ab9220 @ 0x00ab9220).  The byte
// at +0x130 is the vertex-format index, +0x12c is the start of the packed per-vertex
// attribute offsets (position/colour/uv) handed to the streamer, and +0xec is the running
// count of streams emitted.
//
// The object layout follows the neighbouring slices (s00ab3370 / s00ab7720): the effect keeps
// its position history at +0x134, the emit colour map at +0x6dc, and the description pointer
// at +0x14.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace EA { namespace Swarm {

struct cRibbonDescription {
    char     mPad00[0x08];
    uint32_t mFlags;                        // +0x08
};

class cRibbonEffect {
public:
    char                 mPad00[0x14];
    cRibbonDescription*  mDesc;             // +0x14
    char                 mPad18[0xec - 0x18];
    uint16_t             mStreamCount;      // +0xec
    char                 mPadEE[0x12c - 0xee];
    uint8_t              mPosOffset;        // +0x12c
    uint8_t              mColOffset;        // +0x12d
    uint8_t              mUvOffset;         // +0x12e
    uint8_t              mPad12f;
    uint8_t              mFormat;           // +0x130

    void StreamRibbon(void* buffer);        // 0x00ab3300 (name coined)
};

// 32-entry tables of quad-streamer entry points, registered at run time by FUN_00ab9220.
// Entry 0 is cRibbonEffect_StreamQuads (0x00ab3370) for the first table and
// Trail_FillVertices (0x00ab7720) for the second.
typedef void (*StreamFn)(void* self, void* buffer, void* offsets);
extern StreamFn g_ribbonStreamers[32];      // 0x01679690
extern StreamFn g_ribbonStreamersAlt[32];   // 0x01679710

} } // namespace EA::Swarm

using namespace EA::Swarm;

// 0x00ab3300
// @ 0x00ab3300
void cRibbonEffect::StreamRibbon(void* buffer)
{
    // The bool local keeps the compiler from folding the shift into a single-bit test.
    bool alternate = (mDesc->mFlags >> 12) & 1;
    if (alternate)
        g_ribbonStreamersAlt[mFormat](this, buffer, (char*)this + 0x12c);
    else
        g_ribbonStreamers[mFormat](this, buffer, (char*)this + 0x12c);
    ++mStreamCount;
}
