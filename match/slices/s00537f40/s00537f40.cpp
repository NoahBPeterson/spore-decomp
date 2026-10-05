// Slice s00537f40: Swarm skin-paint particle effect (transform copy, refcount) and its
// ArgScript command. Large/algorithmic functions are stubs (partial.txt). Unoptimized
// module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* GetPaintSystem();                                                     // 0x00401080

// ---------------------------------------------------------------- cSPTransform (0x38)
struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModCount;
    float mTranslation[3];
    float mScale;
    float mRotation[9];
    cSPTransform();
    cSPTransform(const cSPTransform& x);    // @ 0x00538000
    cSPTransform& operator=(const cSPTransform& x);
    void Compound(const cSPTransform& x);   // @ 0x00537f40
};
void Matrix3Assign(float* dst, const float* src);   // 0x0041cb40

// @ 0x00538000
cSPTransform::cSPTransform(const cSPTransform& x)
{
    mFlags = x.mFlags;
    mModCount = x.mModCount;
    mTranslation[0] = x.mTranslation[0];
    mTranslation[1] = x.mTranslation[1];
    mTranslation[2] = x.mTranslation[2];
    mScale = x.mScale;
    Matrix3Assign(mRotation, x.mRotation);
}

// ---------------------------------------------------------------- @ 0x00538420
void Wrapper538420Impl(void* p, void* q);   // 0x0053aea0
void Wrapper538420(void* a, void* b)
{
    Wrapper538420Impl(b, a);
}

// ---------------------------------------------------------------- refcount adjustors
struct RefCountBase {
    virtual int AddRef();
    virtual int Release();
    int mRefCount;
};
void RefCountBase_Release(RefCountBase* p);   // 0x00453540

struct Host538380 {
    int AddRef();
};
// @ 0x00538380
int Host538380::AddRef()
{
    int* p = (int*)((char*)this - 4);
    int n = *p;
    *p = n + 1;
    return n + 1;
}

struct Host5383c0 {
    void Release();
};
// @ 0x005383c0
void Host5383c0::Release()
{
    RefCountBase_Release((RefCountBase*)((char*)this - 8));
}

// ---------------------------------------------------------------- stubs (partial)
// @ 0x00537f40
void TransformCompoundStub() {}
// @ 0x00538080
void EffectUpdateStub() {}
// @ 0x00538180
void EffectDtorStub() {}
// @ 0x00538200
void EffectCreateStub() {}
// @ 0x00538260
void EffectCtorStub() {}
// @ 0x00538320
void EvalListDtorStub() {}
// @ 0x00538440
void ParticleEffectBlockOnRegisterStub() {}
// @ 0x00538a00
void ParticlebrushExecuteStub() {}
// @ 0x00538b80
void ParticleCommandStub() {}
