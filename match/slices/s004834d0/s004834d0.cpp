// Slice s004834d0: SP::cSPEditorHandleRotationRing, /Od /Ob1 /arch:SSE.
#include "types.h"

struct Vector3 { float x, y, z; };

struct cSPTransform {
    uint16_t pad0;              // +0x00
    uint16_t mModificationCount;// +0x02
    char     pad4[0x0c];
    float    mScale;            // +0x10
};

struct cMWModel {
    void* mWorld;              // +0x00
    uint32_t mFlags;           // +0x04
    cSPTransform mTransform;   // +0x08
    int mRefCount;             // +0x40
};

struct RotationRing {
    void** vptr;               // +0x00
    void** vptr2;              // +0x04
    int    mUnk8;              // +0x08
    void*  mPropList;          // +0x0c
    void*  mBlock;             // +0x10
    cMWModel* mModel;          // +0x14
    cMWModel* mOverdrawModel;  // +0x18
    char   pad1c[0x34];        // +0x1c .. +0x4f
    int    mUnk50;             // +0x50
    Vector3 mVec54;            // +0x54
    Vector3 mVec60;            // +0x60 (pad +0x6c/0x70 ints)
    int    mUnk6c;             // +0x6c
    int    mUnk70;             // +0x70
    int    mUnk74;             // +0x74
    float  mUnk78;             // +0x78
    char   pad7c[0x0c];
    float  mUnk88;             // +0x88
    float  mUnk8c;             // +0x8c
    uint8_t mUnk90;            // +0x90
    uint8_t mUnk91;            // +0x91

    void SetScale2(float s);   // 0x483cc0
    void Shutdown();           // 0x483d10
    RotationRing* Construct(); // 0x483d40
    void Destroy();            // 0x483e90
    void* AsInterface(uint32_t id); // 0x483ec0
    void Resume();             // 0x4834d0, partial
    void Big();                // 0x4837f0, partial

    void BaseConstruct();                               // @ 0x0047d6a0
    void BaseDestroy();                                 // @ 0x0047d870
    void BaseShutdown();                                // @ 0x0047e2c0
    void RingShutdown();                                // @ 0x004858b0
};

extern Vector3 g_ringVecA;
extern Vector3 g_ringVecB;
extern float  g_negOne;
extern float  g_zeroC;
extern void*  g_ringVtbl0;
extern void*  g_ringVtbl1;

// @ 0x00483cc0
void RotationRing::SetScale2(float s)
{
    if (this->mModel) {
        cSPTransform& x = this->mModel->mTransform;
        x.mScale = s;
        ++x.mModificationCount;
    }
}

// @ 0x00483d10
void RotationRing::Shutdown()
{
    this->BaseShutdown();
    *(uint8_t*)((char*)this + 0x5c) = 0;
}

// @ 0x00483d40
RotationRing* RotationRing::Construct()
{
    this->BaseConstruct();
    this->vptr = &g_ringVtbl0;
    this->vptr2 = &g_ringVtbl1;
    this->mUnk50 = 0;
    Vector3& a = this->mVec54;
    a.x = g_ringVecA.x;
    a.y = g_ringVecA.y;
    a.z = g_ringVecA.z;
    Vector3& b = this->mVec60;
    b.x = g_ringVecB.x;
    b.y = g_ringVecB.y;
    b.z = g_ringVecB.z;
    this->mUnk6c = 0x3bc16bcd;
    this->mUnk70 = 0xe864ba60;
    this->mUnk78 = g_zeroC;
    this->mUnk88 = g_negOne;
    this->mUnk8c = g_negOne;
    this->mUnk90 = 0;
    this->mUnk91 = 0;
    return this;
}

// @ 0x00483e90
void RotationRing::Destroy()
{
    this->vptr = &g_ringVtbl0;
    this->vptr2 = &g_ringVtbl1;
    this->RingShutdown();
    this->BaseDestroy();
}

// @ 0x00483ec0
void* RotationRing::AsInterface(uint32_t id)
{
    switch (id) {
    case 0x050a2ed2: return this;
    case 0x050a1fe5: return this;
    case 0xee3f516e: return this;
    }
    return 0;
}

// @ 0x004834d0 -- PARTIAL: only the transform/scale entry is reproduced.
void RotationRing::Resume()
{
    if (this->mModel) {
        *(float*)((char*)this->mModel + 0x18) = g_zeroC;
        ++*(uint16_t*)((char*)this->mModel + 0xa);
    }
}

// @ 0x004837f0 -- PARTIAL: large ring update; body omitted.
void RotationRing::Big()
{
    (void)this;
}
