// slice s00a8c850: EA::Swarm::cDistributeEffect::~cDistributeEffect (0x00a8cb00, 243 bytes), the base-body
// destructor (thiscall, plain `ret`, no deleting wrapper here). It re-sets the four embedded vtable pointers,
// frees the sample and surface buffers (sp_vector-style: a block is freed only when its header word at
// [-4] is non-zero), releases three interface pointers and destroys two embedded sub-objects.
// It ends by re-setting the first two vtables to the base-class ones.
// Retail member offsets (from the asm; they differ from the 2008 PDB layout in a few places, see
// match/slices/s00a8d450/s00a8d450.cpp for the same class). Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef uint32_t uint32;

// 0x00f47380: operator delete (cdecl, one argument).
void operator_delete__(void* p);

// Frees an sp_vector-style block: only when non-null and its header word is non-zero.
static inline void FreeBlock(void* p) {
    if (p != 0 && ((int*)p)[-1] != 0)
        operator_delete__(p);
}

// Interface with Release() in vtable slot 1 (slot 0 is an unused placeholder).
struct cIRefObj {
    virtual void Slot0();
    virtual void Release();
};

// Embedded sub-object at +0xd8 with a parameterless thiscall destructor body (0x00a89da0).
struct cSubObjD {
    uint32 pad00[(0x44) / 4];
    void FUN_00a89da0();
};

// Embedded sub-object at +0x11c with a parameterless thiscall destructor body (0x00a8c440).
struct cSubObjC {
    uint32 pad00[(0x14) / 4];
    void FUN_00a8c440();
};

struct cDistributeEffect {
    volatile uint32 mVtblIComponent;    // +0x00 (cComponentBase cIComponent part; volatile pins the store order)
    volatile uint32 mVtblRefCount;      // +0x04 (RefCountTemplate<int> part)
    uint32 pad08;
    volatile uint32 mVtblTextureStreamer;   // +0x0c (cITextureParticleStreamer)
    volatile uint32 mVtblModelStreamer;     // +0x10 (cIModelParticleStreamer)
    uint32 pad14[(0xa8 - 0x14) / 4];
    void*  mRenderSamplesBegin;     // +0xa8  (sp_vector block)
    uint32 padac[(0xbc - 0xac) / 4];
    void*  mSamplesBegin;           // +0xbc  (sp_vector block)
    uint32 padc0[(0xd8 - 0xc0) / 4];
    cSubObjD mSubD;                 // +0xd8
    cSubObjC mSubC;                 // +0x11c
    void*  mpBlock130;              // +0x130 (sp_vector block)
    uint32 pad134[(0x144 - 0x134) / 4];
    void*  mpBlock144;              // +0x144 (sp_vector block)
    uint32 pad148[(0x15c - 0x148) / 4];
    cIRefObj* mpRef15c;             // +0x15c (released)
    cIRefObj* mpRef160;             // +0x160 (released)
    cIRefObj* mpRef164;             // +0x164 (released)
    uint32 pad168[(0x19c - 0x168) / 4];
    void* volatile mpBlock19c;      // +0x19c (sp_vector block; volatile keeps the load after the vtable stores)

    ~cDistributeEffect();
};

// 0x00a8cb00 (thiscall, no arguments, plain `ret`).
cDistributeEffect::~cDistributeEffect()
{
    mVtblIComponent = 0x1458308;
    mVtblRefCount = 0x1458304;
    mVtblTextureStreamer = 0x1458300;
    mVtblModelStreamer = 0x14582fc;

    FreeBlock(mpBlock19c);

    if (mpRef164)
        mpRef164->Release();
    if (mpRef160)
        mpRef160->Release();
    if (mpRef15c)
        mpRef15c->Release();

    FreeBlock(mpBlock144);
    FreeBlock(mpBlock130);

    mSubC.FUN_00a8c440();
    mSubD.FUN_00a89da0();

    FreeBlock(mSamplesBegin);
    FreeBlock(mRenderSamplesBegin);

    mVtblIComponent = 0x13f21d4;
    mVtblRefCount = 0x13ef094;
}
