// Slice s004834d0: SP::cSPEditorHandleRotationRing bookkeeping (Shutdown 0x483d10,
// Construct 0x483d40, Destroy 0x483e90, AsInterface 0x483ec0, SetScale2 0x483cc0)
// and the two SP::cSPEditorHandleRotationBall members Resume (0x4834d0) and
// Update (0x4837f0).  Editor module, built /Od /Ob1 /arch:SSE.
#include "types.h"

// Frame filler: reserves N dwords where the original reserved the frame of an
// inline helper cl declined to expand (docs/matching.md, /Od holes).
template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- rw::math::fpu vector / matrix types ----------------------------------
// Vector3T's copy constructor is out of line (0x004098A0) while its copy
// assignment is the implicit, trivial one: struct assignments of it become
// plain integer/rep-movsd block moves in the original.
struct Vector3T {                       // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);        // 0x004098A0, out of line
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
typedef Vector3T Vector3;

// The editor vector derives from Vector3T.  Its converting constructor from
// Vector3T is an inline member, so `cSPVector3 v = <Vector3T expr>;` is the
// three-movss component copy the original shows at every operator result.
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : Vector3T(v) {}
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
};

struct Matrix33T {                      // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m);      // 0x0041CB40, out of line
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& m) : Matrix33T(m) {}
};

Vector3T operator*(const Vector3T& v, const float& s);     // 0x0041DCA0
Vector3T operator/(const Vector3T& v, const float& s);     // 0x00453880
Vector3T operator-(const Vector3T& a, const Vector3T& b);  // 0x0041DB10
Vector3T operator+(const Vector3T& a, const Vector3T& b);  // 0x0041DC10
Vector3T operator*(const Vector3T& v, const Matrix33T& m); // 0x0041DAF0
float VectorLength(const Vector3T& v);                     // 0x0040AE50
cSPVector3 Normalize(const Vector3T& v);                   // 0x00436CE0

// ---- transform / model ----------------------------------------------------
struct cSPTransform {                   // 0x38 bytes
    uint16_t mFlags;                    // +0x00
    uint16_t mModificationCount;        // +0x02
    Vector3T mTranslation;              // +0x04
    float    mScale;                    // +0x10
    cSPMatrix3 mRotation;               // +0x14
    cSPTransform();                                          // 0x00409930
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetTranslation(const Vector3T& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
};

struct cMWModel {
    void*    mWorld;                    // +0x00
    uint32_t mFlags;                    // +0x04
    cSPTransform mTransform;            // +0x08
    int      mRefCount;                 // +0x40
    void AddRef() { mRefCount = mRefCount + 1; }
};

struct cIModelWorld;

// EA::AutoRefCount<T>: its conversion operator is an inline member, so reading the
// wrapped pointer at /Od materialises a temporary (the original's "load member,
// store temp, compare temp" sequence).
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) {}
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct cSPBoundingBox {                 // 0x18 bytes
    cSPVector3 mMin, mMax;
    void Transform(const cSPTransform& t);  // 0x00409DD0
};

struct cSPEditorBlock {
    uint32_t pad00[0x18 / 4];           // +0x00
    AutoRefCount<cIModelWorld> mModelWorld;  // +0x18
    uint32_t pad1c[(0x48 - 0x1c) / 4];  // +0x1c
    Vector3T mPosition;                 // +0x48
    uint32_t pad54[(0x60 - 0x54) / 4];  // +0x54
    cSPMatrix3 mOrientation;            // +0x60
    uint32_t pad84[(0x1d8 - 0x84) / 4]; // +0x84
    float    mScale;                    // +0x1d8
    cSPBoundingBox GetBBox(int mode, bool a, bool b);  // 0x0044AE00
};

namespace SP {
bool SegmentBoxIntersect(const Vector3T& dir, const Vector3T& origin,
                         const cSPBoundingBox& box, float* t);  // 0x006989D0
}
void BuildOrientation(Matrix33T* out, const Vector3T* a, const Vector3T* b);  // 0x004A89E0

extern Vector3T g_zeroVector;            // 0x015D5508
extern const cSPMatrix3 g_ballRotation;  // 0x015D53D8
extern const Vector3T g_ballUp;          // 0x015D5358

// ---- animation manager ----------------------------------------------------
struct ModelRef {                        // EA::AutoRefCount<cMWModel> by value
    cMWModel* p;
    ModelRef(cMWModel* m) : p(m) { if (p) p->AddRef(); }
    ModelRef(const ModelRef& r) : p(r.p) { if (p) p->AddRef(); }
};
struct AnimMgr { void** vptr; };
AnimMgr* GetSetting6();                  // 0x00401060
typedef void (__thiscall *AnimFn)(void*, ModelRef, int, float, float, int);

#define PLAY_ANIM(mgr, model, prop, value, time, flag) \
    ((AnimFn)(*(void***)(mgr))[6])((mgr), ModelRef(model), (prop), (value), (time), (flag))

// ---- cSPEditorHandleRotationRing ------------------------------------------
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

// ---- SP::cSPEditorHandleRotationBall --------------------------------------
// 0x4834d0 and 0x4837f0 sit in the ball primary vtable (0x13EF320) at slots
// +0x24 and +0x2c (see s00482670, which holds the rest of the class).
struct RotationBall {
    void** vptr;                       // +0x00
    void** vptr2;                      // +0x04
    int    mUnk8;                      // +0x08
    void*  mPropList;                  // +0x0c
    cSPEditorBlock* mBlock;            // +0x10
    cMWModel* mModel;                  // +0x14
    cMWModel* mOverdrawModel;          // +0x18
    uint32_t pad1c[(0x28 - 0x1c) / 4]; // +0x1c
    float  mAnimateInTime;             // +0x28
    uint32_t pad2c[(0x50 - 0x2c) / 4]; // +0x2c
    cSPVector3 mOffset;                // +0x50
    bool   mExists;                    // +0x5c
    bool   mIsHidden;                  // +0x5d
    uint8_t pad5e[2];
    float  mDistanceFromBoundingBox;   // +0x60

    cSPVector3 Resume();                   // 0x4834d0 (hidden cSPVector3 return)
    void Update();                         // 0x4837f0
};

// The ball position in the block's frame: project the handle offset (mOffset)
// out to the far side of the block bounding box (or its whole length when the
// ray misses), scale it by the block scale and add it to the block position.
// @ 0x004834d0
cSPVector3 RotationBall::Resume()
{
    cMWModel* model = this->mModel;
    if (model == 0 || this->mBlock == 0) {
        return g_zeroVector;
    }
    cSPBoundingBox box = this->mBlock->GetBBox(2, false, false);
    cSPTransform t;
    t.SetRotation(g_ballRotation);
    t.SetTranslation(g_zeroVector);
    t.SetScale(1.0f);
    box.Transform(t);
    ScratchSlots<40>();
    float len = VectorLength(this->mOffset);
    cSPVector3 dir = this->mOffset / len;
    Vector3T zero(g_zeroVector);
    float hundred = 100.0f;
    cSPVector3 u = dir * hundred;
    float dist = len;
    float tval;
    if (SP::SegmentBoxIntersect(u, zero, box, &tval))
        dist = (1.0f - tval) * hundred;
    float off = (dist + this->mDistanceFromBoundingBox) * this->mBlock->mScale;
    cSPVector3 res = this->mBlock->mPosition + (dir * off) * this->mBlock->mOrientation;
    return res;
}

// @ 0x004837f0
void RotationBall::Update()
{
    cMWModel* model = this->mModel;
    if (model == 0)
        return;
    AnimMgr* mgr = GetSetting6();
    cIModelWorld* world = this->mBlock->mModelWorld;
    if (mgr == 0 || world == 0)
        return;
    cSPMatrix3 orient = this->mBlock->mOrientation;
    float scale = this->mBlock->mScale;
    cSPVector3 pos = this->mBlock->mPosition;
    cSPVector3 dir = Normalize(this->mOffset);
    cSPVector3 v = dir * orient;
    cSPMatrix3 buildOri;
    BuildOrientation(&buildOri, &v, &g_ballUp);
    cSPVector3 out = ((cSPVector3 (__thiscall*)(RotationBall*))this->vptr[0x24 / 4])(this);
    float k = 0.4f;
    cSPVector3 newPos = pos + (this->mOffset - dir * k) * scale * orient;
    this->mModel->mTransform.SetTranslation(newPos);
    this->mModel->mTransform.SetRotation(buildOri);
    PLAY_ANIM(mgr, this->mModel, 5, out.x, this->mAnimateInTime, 3);
    PLAY_ANIM(mgr, this->mModel, 6, out.y, this->mAnimateInTime, 3);
    PLAY_ANIM(mgr, this->mModel, 7, out.z, this->mAnimateInTime, 3);
    float alpha = ((float (__thiscall*)(RotationBall*, int))this->vptr[0x38 / 4])(this, 3);
    PLAY_ANIM(mgr, this->mModel, 4, alpha, this->mAnimateInTime, 1);
}
