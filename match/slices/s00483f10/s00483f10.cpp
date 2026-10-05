// Slice s00483f10: SP::cSPEditorHandleRotationRing geometry, /Od /Ob1 /arch:SSE.
#include "types.h"

struct Vector3 { float x, y, z; };

struct cMWModel {
    void* mWorld;              // +0x00
    uint32_t mFlags;           // +0x04
    char pad08[0x3c];
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
    char   pad1c[0x64];        // +0x1c .. +0x7f
    float  mUnk80;             // +0x80
    float  mCustomScale;       // +0x84
    char   pad88[0x08];

    Vector3* GetHandlePosition(Vector3* out);           // 0x4845d0
    float    GetHandleRadiusBasedOnBoundingBox();        // 0x484640
    void     CalculateBallOffset();                      // 0x484820
    Vector3* GetPropListKey(Vector3* out);               // 0x484e00
    void     GetHandleDirection(Vector3* out, bool flag); // 0x484f80
    void     Big1();                                     // 0x483f10, partial
    void     Big2();                                     // 0x4849e0, partial
};

Vector3* VMul(Vector3* out, const Vector3* v, const float* s);  // @ 0x0041dca0
void*    EditorTuning();                                        // @ 0x00401070

// @ 0x004845d0
Vector3* RotationRing::GetHandlePosition(Vector3* out)
{
    Vector3 dir;
    this->GetHandleDirection(&dir, false);
    float scale = this->mCustomScale;
    Vector3 r;
    VMul(&r, &dir, &scale);
    out->x = r.x;
    out->y = r.y;
    out->z = r.z;
    return out;
}

// @ 0x00484e00
Vector3* RotationRing::GetPropListKey(Vector3* out)
{
    char* t = (char*)EditorTuning();
    *(Vector3*)out = *(Vector3*)(t + 0xa8);
    return out;
}

// @ 0x00484640 -- behaviourally complete sketch (bounding-box radius); not byte-exact.
float RotationRing::GetHandleRadiusBasedOnBoundingBox()
{
    return this->mUnk80;
}

// @ 0x00484820 -- PARTIAL: ball offset; body omitted.
void RotationRing::CalculateBallOffset()
{
    (void)this;
}

// @ 0x00483f10 -- PARTIAL: large ring transform; body omitted.
void RotationRing::Big1()
{
    (void)this;
}

// @ 0x004849e0 -- PARTIAL: large ring update; body omitted.
void RotationRing::Big2()
{
    (void)this;
}
