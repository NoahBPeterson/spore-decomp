// src/game/SPBake/SPEditorHandleRotationBall.cpp -- migrated from slice(s) s00482670 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorHandleRotationBall.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorHandleRotationBall.h"
#include "SP/cSPEditorTrianglePinningInfo.h"
#include "cSPVector3.h"
#include "SP/cMWModel.h"
#include "SP/cSPEditorHandleDeform.h"

// ---- items of slice s00482670 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 { float x, y, z; };
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

    // base-class entry points (defined in other slices; masked relocations)
    void BaseConstruct();                               // @ 0x0047d6a0
    void BaseDestroy();                                 // @ 0x0047d870
    void BaseInit(void*, bool, uint32_t, uint32_t);     // @ 0x0047db30
    void BallCleanup();                                 // @ 0x00483d10
};
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
};
struct Vec3R : Vec3 {};                 // cSPVector3R: result type of the out-of-line operators
Vec3R operator-(const Vec3& a, const Vec3& b);              // 0x0041db10
Vec3R operator+(const Vec3& a, const Vec3& b);              // 0x0041dc10
Vec3R operator*(const Vec3& a, const float& s);             // 0x0041dca0
// ---- items of slice s00482670 end

// @ 0x00483140
void SP::cSPEditorHandleRotationBall::CalculateBallOffset()
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
    this->mDistanceFromBoundingBox = 0.0f;
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
