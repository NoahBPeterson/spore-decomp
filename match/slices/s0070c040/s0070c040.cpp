// slice s0070c040: SP::cLightingWorld local-light sample creation plus the
// spstl slot-vector `create` helpers.  /O2 + SSE region.
// Flags: /O2 /MD /Gy /TP /GS-
#include <new>
#include <string.h>
#include "types.h"

void __cdecl EastlFree(void* p);                       // 0x00F47380

struct CellInfo { int x, y; };
struct cSPVector3 { float x, y, z; };

// ===========================================================================
// cLocalLightInfo copy constructor
// ===========================================================================
struct FixedCellVector {
    CellInfo* mpBegin;      // +0x00
    CellInfo* mpEnd;        // +0x04
    CellInfo* mpCapacity;   // +0x08
    char pad_c[4];
    CellInfo* mpInline;     // +0x10
    FixedCellVector(const FixedCellVector& x);                           // 0x70c3a0
    void assign(const CellInfo* first, const CellInfo* last, int tag);   // 0x708340
};

struct cLocalLightInfo {
    cSPVector3 mColour;     // +0x00
    float mSize;            // +0x0c
    cSPVector3 mPosition;   // +0x10
    float mStrength;        // +0x1c
    void* mDecal;           // +0x20
    bool mGlobal;           // +0x24
    FixedCellVector mCells; // +0x28
    cLocalLightInfo(const cLocalLightInfo& x);
};

// @ 0x0070c7c0
cLocalLightInfo::cLocalLightInfo(const cLocalLightInfo& x)
    : mColour(x.mColour), mSize(x.mSize), mPosition(x.mPosition), mStrength(x.mStrength),
      mDecal(x.mDecal), mGlobal(x.mGlobal), mCells(x.mCells)
{
}

// ===========================================================================
// cLightingWorld sample entry points
// ===========================================================================
struct SlotVecCell {
    int* mpBlocks;          // +0x00
    char pad4[0x14];
    uint32_t mField18;
    uint32_t mField1c;
    uint32_t create(const void* init);   // 0x70c200
};

struct cLightingWorld {
    void CreateLocalLightSample(int info);
    void UpdateLocalLightSample(int info);     // 0x707370
    void UpdateLightingInfo(void* cfg);        // 0x70cab0
    void CreateEnvLightSampleEx(void* a, void* b, void* c);
};

// Local light cell initialiser handed to the slot-vector create call: only the head
// fields are cleared, the 12 alignment bytes at +0x14 and the cell storage at +0x30
// are left untouched by the original.
struct cLocalLightCellInit {
    bool mGlobal;            // +0x00
    bool mInUse;             // +0x01
    short mType;             // +0x02
    cSPVector3 mColour;      // +0x04
    float mSize;             // +0x10
    uint8_t mPad14[0x0c];    // +0x14 (alignment padding before the 16-byte member)
    uint32_t mExtra[4];      // +0x20
    uint8_t mCells[0x1a0];   // +0x30
};

// @ 0x0070c410
void cLightingWorld::CreateLocalLightSample(int info)
{
    cLocalLightCellInit init;
    init.mGlobal = false;
    init.mInUse = false;
    init.mType = 0;
    init.mColour.x = 0.0f;
    init.mColour.y = 0.0f;
    init.mColour.z = 0.0f;
    init.mSize = 0.0f;
    init.mExtra[0] = 0;
    init.mExtra[1] = 0;
    init.mExtra[2] = 0;
    init.mExtra[3] = 0;
    uint32_t id = ((SlotVecCell*)((char*)this + 0x608))->create(&init);
    *(uint32_t*)((char*)info + 0x24) = id;
    int base = *(int*)(*(int*)((char*)this + 0x608) + ((uint32_t)id >> 7) * 4);
    *(int*)(base + 0x1d0 + (id & 0x7f) * 0x1e0) = info;
    UpdateLocalLightSample(info);
}

// ===========================================================================
// remaining slice functions (not reconstructed; see partial.txt)
// ===========================================================================
// @ 0x0070c040
void SimpleDequeDtor(void* self)
{
    (void)self;
}

// @ 0x0070c090
void SlotVecCreateEnv(void* self, const void* init)
{
    (void)self;
    (void)init;
}

// @ 0x0070c200
uint32_t SlotVecCellCreate(SlotVecCell*, const void*)
{
    return 0;
}

// @ 0x0070c3a0
void FixedCellVectorCtor(void* self)
{
    (void)self;
}

// @ 0x0070c4b0
void SlotVectorHelperA(void* self)
{
    (void)self;
}

// @ 0x0070c5e0
void SlotVectorHelperB(void* self)
{
    (void)self;
}

// @ 0x0070c830
void SlotVectorHelperC(void* self)
{
    (void)self;
}

// @ 0x0070cab0
void cLightingWorld::UpdateLightingInfo(void*)
{
}

// @ 0x0070cce0
void SlotVecCreateLocal(void* self, const void* init)
{
    (void)self;
    (void)init;
}
