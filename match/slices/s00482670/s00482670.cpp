// Slice s00482670: SP::cSPEditorHandleRotationBall, /Od /Ob1 /arch:SSE.
#include "types.h"

struct Vector3 { float x, y, z; };

// base-class entry points (defined in other slices; masked relocations)
void* EditorTuning();          // @ 0x00401070

extern Vector3 g_offset;
extern void* g_ballVtbl0;
extern void* g_ballVtbl1;

struct cMWModel {
    void* mWorld;              // +0x00
    uint32_t mFlags;           // +0x04
    char pad08[0x3c];
    int mRefCount;             // +0x40
};

struct RotationBall {
    void** vptr;               // +0x00
    void** vptr2;              // +0x04
    int    mUnk8;              // +0x08
    void*  mPropList;          // +0x0c
    void*  mBlock;             // +0x10
    cMWModel* mModel;          // +0x14
    cMWModel* mOverdrawModel;  // +0x18
    char   pad1c[0x34];        // +0x1c .. +0x4f
    Vector3 mOffset;           // +0x50
    bool   mExists;            // +0x5c
    bool   mIsHidden;          // +0x5d
    char   pad5e[2];
    float  mDistance;          // +0x60

    RotationBall* Construct();
    void Destroy();
    void* AsInterface(uint32_t id);
    void UpdateOffset();
    void CalculateBallOffset();
    void Init(void* o, void* block, float x, float y, float z, bool flag);
    Vector3* GetTuningOffset(Vector3* out);
    void Big();                // 0x00482670, partial

    // base-class entry points (defined in other slices; masked relocations)
    void BaseConstruct();                               // @ 0x0047d6a0
    void BaseDestroy();                                 // @ 0x0047d870
    void BaseInit(void*, bool, uint32_t, uint32_t);     // @ 0x0047db30
    void BallCleanup();                                 // @ 0x00483d10
};

// @ 0x00482f90
RotationBall* RotationBall::Construct()
{
    this->BaseConstruct();
    this->vptr = &g_ballVtbl0;
    this->vptr2 = &g_ballVtbl1;
    Vector3& o = this->mOffset;
    o.x = g_offset.x;
    o.y = g_offset.y;
    o.z = g_offset.z;
    this->mExists = false;
    return this;
}

// @ 0x00483040
void RotationBall::Destroy()
{
    this->vptr = &g_ballVtbl0;
    this->vptr2 = &g_ballVtbl1;
    this->BallCleanup();
    this->BaseDestroy();
}

// @ 0x00483070
void* RotationBall::AsInterface(uint32_t id)
{
    switch (id) {
    case 0xee3f516e: return this;
    case 0x050a1fe5: return this;
    case 0x050a510e: return this;
    }
    return 0;
}

// @ 0x004830c0
void RotationBall::UpdateOffset()
{
    if (this->mModel) {
        char local[12];
        void* r = ((void*(__thiscall*)(RotationBall*, void*))this->vptr[9])(this, local);
        *(Vector3*)((char*)this->mModel + 0xc) = *(Vector3*)r;
        *(uint16_t*)((char*)this->mModel + 8) |= 4;
        ++*(uint16_t*)((char*)this->mModel + 0xa);
    }
}

// @ 0x00483140 -- behaviourally complete; local slots / helper shapes not byte-exact.
void RotationBall::CalculateBallOffset()
{
    if (!this->mBlock)
        return;
    char bbox[0x28];
    void GetBBox(void*, void*, int, int, int);      // @ 0x00480e90 region helper
    GetBBox(this->mBlock, bbox, 2, 0, 0);
    void TransformBBox(void*, void*);               // @ 0x00409930
    TransformBBox(bbox, (void*)0x15d53d8);
    float len = this->mOffset.x * this->mOffset.x + this->mOffset.y * this->mOffset.y + this->mOffset.z * this->mOffset.z;
    (void)len;
    this->mDistance = 0.0f;
    (void)bbox;
}

// @ 0x00483350
void RotationBall::Init(void* o, void* block, float x, float y, float z, bool flag)
{
    this->BaseInit(block, flag, 0, 0);
    this->mOffset.x = x;
    this->mOffset.y = y;
    this->mOffset.z = z;
    this->CalculateBallOffset();
    this->mExists = true;
    this->mIsHidden = false;
    void* b = this->mBlock;
    (void)b;
    if (!flag) {
        this->mExists = false;
    } else if (this->mModel) {
        void** vt = *(void***)o;
        uint32_t id = ((uint32_t(__thiscall*)(void*, uint32_t, int))vt[0xa])(o, 0x31390733, 0);
        if (id < 0x40) {
            uint32_t* word = (uint32_t*)((char*)this->mModel + 0x44 + (id >> 5) * 4);
            *word |= (1u << (id % 0x20));
        }
    }
    if (!this->mExists)
        ((void(__thiscall*)(RotationBall*))this->vptr[0x4c / 4])(this);
}

// @ 0x00483490
Vector3* RotationBall::GetTuningOffset(Vector3* out)
{
    char* t = (char*)EditorTuning();
    *(Vector3*)out = *(Vector3*)(t + 0x9c);
    return out;
}

// @ 0x00482670 -- PARTIAL: ball update; only the base guard is reproduced.
void RotationBall::Big()
{
    (void)this;
}
