// Slice s004a1a70: SP editor block/model helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
};
template<class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0x144 - 4];
    cSPVector3 mField144;                        // +0x144
    char pad1[0x3e0 - 0x150];
    AutoRefCount<cSPEditorBlock> mPinTarget;     // +0x3e0
    void FUN_4a1d60(const cSPVector3* p);        // @ 0x4a1d60
};
struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
};
bool FUN_4a1e10(cSPEditorBlock* block);          // @ 0x4a1e10

// @ 0x4a1d60
void cSPEditorBlock::FUN_4a1d60(const cSPVector3* p)
{
    mField144 = *p;
    if (mPinTarget) {
        cSPVector3 v = *p;
        v[0] *= -1.0f;
        mPinTarget->mField144 = v;
    }
}

// @ 0x4a2560
bool FUN_4a2560(cSPEditorModel* model)
{
    bool result = 0;
    if (model) {
        int i = 0;
        int n = model->GetBlockCount();
        for (; i < n; i++) {
            cSPEditorBlock* b = model->GetBlock(i);
            bool block = FUN_4a1e10(b);
            result = block || result;
        }
    }
    return result;
}

// @ 0x4a1a70
void FUN_4a1a70(cSPEditorBlock* block) { (void)block; }

// @ 0x4a1e10
bool FUN_4a1e10(cSPEditorBlock* block) { (void)block; return false; }

// @ 0x4a2060
void FUN_4a2060(cSPEditorBlock* block) { (void)block; }

// @ 0x4a2180
void FUN_4a2180(cSPEditorBlock* block) { (void)block; }

// @ 0x4a2350
void DoSnapReplace(cSPEditorBlock* block) { (void)block; }

// @ 0x4a25f0
void FUN_4a25f0(cSPEditorBlock* block) { (void)block; }
