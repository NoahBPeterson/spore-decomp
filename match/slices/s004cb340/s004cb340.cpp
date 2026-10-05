// Slice s004cb340: SP::cSkinObject mesh-rebuild helpers in the editor /Od region.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
//
// 0x004CBDF0 is the default constructor of a skin-data object holding six 0x14-byte
// eastl vectors (the first one a node-weight vector whose allocator needs a tag).  Its
// byte-exact reconstruction is below.  The three large mesh builders are transcribed
// only as structural skeletons (their Ghidra decompiles carry lost frame locals), so
// they are listed in partial.txt.
#include "types.h"

#pragma pack(push, 4)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

struct AllocTag { AllocTag() {} };
struct NodeWeightAllocator {
    NodeWeightAllocator(const AllocTag& tag);        // 0x00429360
    uint32_t pad[2];
};
struct NodeWeightVector {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    NodeWeightAllocator mAllocator;
    NodeWeightVector() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(AllocTag()) { ScratchSlots<1>(); }
};
struct PlainVector {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    uint32_t mAlloc[2];
    PlainVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};

// @ 0x004CBDF0  (real class name not recovered; layout: +8,+0x1c,+0x30,+0x44,+0x6c,+0x80)
struct SkinBuildData {
    uint32_t mBase[2];        // +0
    NodeWeightVector v1;      // +8
    PlainVector v2;           // +0x1c
    PlainVector v3;           // +0x30
    PlainVector v4;           // +0x44
    uint32_t mGap[5];         // +0x58 (untouched by the ctor)
    PlainVector v5;           // +0x6c
    PlainVector v6;           // +0x80
    SkinBuildData();
};
SkinBuildData::SkinBuildData() {}

// ---------------------------------------------------------------------------
// Remaining functions: skeletons (see slice header note).
// ---------------------------------------------------------------------------
// @ 0x004CB340  SP::cSkinObject::BuildMesh
bool SkinObject_BuildMesh(uint32_t self) { (void)self; return false; }

// @ 0x004CB820
void SkinObject_BuildBones(uint32_t self) { (void)self; }

// @ 0x004CBF00
void SkinObject_DrawPart(uint32_t self, uint32_t a, uint32_t b, int c)
{
    (void)self; (void)a; (void)b; (void)c;
}
