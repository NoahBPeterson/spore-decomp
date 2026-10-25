// Slice s00482670: SP::cSPEditorHandleRotationBall, /Od /Ob1 /arch:SSE.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3 { float x, y, z;                  // rw::math::fpu::Vector3Template<float,0>
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3 {                       // cSPVector3 (12 bytes)
    cSPVector3() {}
    cSPVector3(const Vector3& v) : Vector3(v) {}
    cSPVector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3 { Vector3 xAxis, yAxis, zAxis; }; // 36 bytes, copied with rep movsd

// base-class entry points (defined in other slices; masked relocations)
void* EditorTuning();          // @ 0x00401070

extern Vector3 g_offset;
extern void* g_ballVtbl0;
extern void* g_ballVtbl1;
extern const cSPMatrix3 kMatrix_15d53d8;   // @ 0x15d53d8
extern const cSPVector3 kZeroVec_15d5508;  // @ 0x15d5508

float VectorLength(const Vector3& v);                       // @ 0x40ae50
Vector3 operator*(const Vector3& v, const float& s);        // @ 0x41dca0
Vector3 operator/(const Vector3& v, const float& s);        // @ 0x453880

struct cSPTransform {                               // 0x38 bytes
    uint16_t mFlags;                                // +0x00
    uint16_t mModificationCount;                    // +0x02
    Vector3 mTranslation;                           // +0x04
    float mScale;                                   // +0x10
    cSPMatrix3 mRotation;                           // +0x14
    cSPTransform();                                 // @ 0x409930
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetTranslation(const Vector3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
};
struct cSPBoundingBox {                             // 0x18 bytes
    cSPVector3 mMin, mMax;
    void Transform(const cSPTransform& t);          // @ 0x409dd0
};
bool SegmentBoxIntersect(const Vector3& dir, const Vector3& origin,
                         const cSPBoundingBox& box, float* t);   // @ 0x6989d0

template<int N> struct bitset {                     // eastl::bitset<N>
    uint32_t mWord[(N + 31) / 32];
    __forceinline uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline void set(uint32_t n, bool value) {
        if (n < N) {
            if (value)
                DoGetWord(n) |= 1u << (n % 32);
            else
                DoGetWord(n) &= ~(1u << (n % 32));
        }
    }
};

template<class T> struct AutoRefCount {             // EA::AutoRefCount<T>: one pointer
    T* mpObject;
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct cIModelWorld;                                // only used as a pointer here

struct cSPEditorBlock {
    char pad00[0x18];
    AutoRefCount<cIModelWorld> mModelWorld;         // +0x18
    cSPBoundingBox GetBBox(int mode, bool a, bool b);   // @ 0x44ae00
};

#define PV(n) virtual void _v##n();
struct IModelManager {
    virtual int AddRef(); virtual int Release();
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual unsigned int GetGroupFlag(uint32_t groupID, int arg);   // +0x28
};

struct cMWModel {
    void* mWorld;              // +0x00
    uint32_t mFlags;           // +0x04
    char pad08[0x38];
    int mRefCount;             // +0x40
    bitset<64> mGroups;        // +0x44
};

struct RotationBall {
    void** vptr;               // +0x00
    void** vptr2;              // +0x04
    int    mUnk8;              // +0x08
    void*  mPropList;          // +0x0c
    cSPEditorBlock* mBlock;    // +0x10
    AutoRefCount<cMWModel> mModel;  // +0x14
    cMWModel* mOverdrawModel;  // +0x18
    char   pad1c[0x34];        // +0x1c .. +0x4f
    cSPVector3 mOffset;        // +0x50
    bool   mExists;            // +0x5c
    bool   mIsHidden;          // +0x5d
    char   pad5e[2];
    float  mDistanceFromBoundingBox;  // +0x60

    RotationBall* Construct();
    void Destroy();
    void* AsInterface(uint32_t id);
    void UpdateOffset();
    void CalculateBallOffset();
    void Init(IModelManager* o, cSPEditorBlock* block, cSPVector3 offset, bool flag);
    Vector3* GetTuningOffset(Vector3* out);

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
        *(Vector3*)((char*)(cMWModel*)this->mModel + 0xc) = *(Vector3*)r;
        *(uint16_t*)((char*)(cMWModel*)this->mModel + 8) |= 4;
        ++*(uint16_t*)((char*)(cMWModel*)this->mModel + 0xa);
    }
}

// @ 0x00483140
void RotationBall::CalculateBallOffset()
{
    if (this->mBlock) {
        cSPBoundingBox chunk = this->mBlock->GetBBox(2, false, false);
        cSPTransform p15;
        p15.SetRotation(kMatrix_15d53d8);
        p15.SetTranslation(kZeroVec_15d5508);
        p15.SetScale(1.0f);
        chunk.Transform(p15);
        ScratchSlots<40>();
        float length = VectorLength(this->mOffset);
        cSPVector3 v32 = this->mOffset / length;
        float tmp = 100.0f;
        cSPVector3 n25 = kZeroVec_15d5508;
        cSPVector3 u = v32 * tmp;
        float v4;
        if (SegmentBoxIntersect(u, n25, chunk, &v4))
            this->mDistanceFromBoundingBox = length - (1.0f - v4) * tmp;
        else
            this->mDistanceFromBoundingBox = 0.0f;
    }
}

// @ 0x00483350
void RotationBall::Init(IModelManager* o, cSPEditorBlock* block, cSPVector3 offset, bool flag)
{
    this->BaseInit(block, flag, 0, 0);
    this->mOffset = offset;
    this->CalculateBallOffset();
    this->mExists = true;
    this->mIsHidden = false;
    cIModelWorld* worldConv = this->mBlock->mModelWorld;
    cIModelWorld* world = worldConv;
    (void)world;
    if (flag) {
        cMWModel* modelConv = this->mModel;
        if (modelConv) {
            cMWModel* mpModel = this->mModel;
            uint32_t nID = o->GetGroupFlag(0x31390733, 0);
            bitset<64>& groups = mpModel->mGroups;
            groups.set(nID, true);
        }
    } else {
        this->mExists = false;
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

// ---------------------------------------------------------------------------------------------
// 00482670: SP::cSPEditorHandleDeform::Update (layout by use; the 2008 PDB class is 0x1d8 bytes
// and agrees with retail for +0x10, +0x50 mData (start/end points at +0x90/+0x9c), +0xac pinning
// type, +0xb0 axis to ignore, +0xe8/+0xf4/+0x100, +0x15c, +0x180 mDelta and +0x188 triangle info;
// +0x12c and +0x138 sit inside PDB fields, so they are named by use).
// ---------------------------------------------------------------------------------------------
struct Vector3Dummy;

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
};
struct Vec3R : Vec3 {};                 // cSPVector3R: result type of the out-of-line operators

struct Mat33 {
    float m[9];
    Mat33() {}
    Mat33(const Mat33& o) { *this = o; }
};
struct Mat33R : Mat33 {};              // result type of the out-of-line matrix helpers

Vec3R operator-(const Vec3& a, const Vec3& b);              // 0x0041db10
Vec3R operator+(const Vec3& a, const Vec3& b);              // 0x0041dc10
Vec3R operator*(const Vec3& a, const float& s);             // 0x0041dca0
Vec3R Vec3_MulMat(const Vec3& a, const Mat33& m);           // 0x0041daf0 (operator*)
Mat33R Mat33_Mul(const Mat33& a, const Mat33& b);            // 0x0041de20 (operator*)
Mat33R ConvertRotation(const void* m);                      // 0x0041ded0
float VectorLength(const Vec3* v);                          // 0x0040ae50
void Vec3_Normalize(Vec3* dst, const Vec3* src);            // 0x00436ce0


struct PartTransform {                                      // 0x38 bytes
    char data[0x38];
    PartTransform(const PartTransform& src);                // 0x0040ce80
    void Invert();                                          // 0x0040efa0
    void Apply(Vec3& v);                                    // 0x0044d4f0
};

struct EditorPart {
    char pad00[8];
    PartTransform mTransform;                               // +0x08
};
struct EditorBlock {
    char pad00[0x10];
    EditorPart* mPart;                                      // +0x10
    char pad14[4];
    void* mModel;                                           // +0x18
    void* GetModelPtr() { return mModel; }
    void* GetModel() { return GetModelPtr(); }
    EditorPart* GetPart() { return mPart; }
};

struct TrianglePinningInfo {                                // at +0x188
    void* mTriangleOwner;
    void* mTriangle;                                        // +0x4
    void* GetTriangle() { return mTriangle; }
    void GetPose(Vec3* pos, Mat33* rot);                    // 0x004e95e0
};

static inline float Dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

namespace SP { struct cSPEditorHandleDeform {
    void** vptr;                    // +0x00
    char pad04[0x0c];
    EditorBlock* mBlock;            // +0x10
    char pad14[0x7c];
    Vec3 mStartPt;                  // +0x90
    Vec3 mEndPt;                    // +0x9c
    char padA8[4];
    uint32_t mPinningType;          // +0xac
    uint32_t mAxisToIgnore;         // +0xb0
    char padB4[0x34];
    Vec3 mHandleStartLocal;         // +0xe8
    Vec3 mHandleEndLocal;           // +0xf4
    Vec3 mBlockPosition;            // +0x100
    char pad10c[0x20];
    Vec3 mPlaneNormal;              // +0x12c
    Vec3 mPlanePoint;               // +0x138
    char pad144[0x0c];
    Vec3 mOriginalTrianglePoint;    // +0x150
    Vec3 mStartOffset;              // +0x15c
    char pad168[0x18];
    float mDelta;                   // +0x180
    char pad184[4];
    TrianglePinningInfo mTriangleInfo;  // +0x188

    void Update();                  // 0x00482670
}; }

void SP::cSPEditorHandleDeform::Update()
{
    void* pModel;
    if (this->mBlock && this->mPinningType != 0xc32b1302 && (pModel = this->mBlock->GetModel()) != 0 &&
        this->mBlock->GetPart() && this->mTriangleInfo.GetTriangle()) {
        Vec3 pivotOrigin;
        Vec3 dirVec;
        Mat33 pivotMat;
        this->mTriangleInfo.GetPose(&pivotOrigin, &pivotMat);
        PartTransform partXf(this->mBlock->GetPart()->mTransform);
        partXf.Invert();
        ScratchSlots<17>();
        Mat33 toBlock = Mat33_Mul(pivotMat, ConvertRotation((char*)this->mBlock->GetPart() + 0x1c));
        Vec3 ballCenter = pivotOrigin;
        partXf.Apply(ballCenter);
        ScratchSlots<3>();

        Vec3 span = this->mEndPt - this->mStartPt;
        float segLength = VectorLength(&span);
        ScratchSlots<1>();
        Vec3 dirA = Vec3_MulMat(this->mStartOffset, toBlock);
        Vec3 end = Vec3_MulMat(this->mHandleEndLocal, toBlock);
        Vec3_Normalize(&dirVec, &Vec3(this->mEndPt - this->mStartPt));
        ScratchSlots<5>();

        Vec3 dest;
        if (this->mPinningType == 0x11f10cfa || this->mPinningType == 0x9e6e561c) {
            Vec3 rel = ballCenter - this->mPlanePoint;
            Vec3 startLocal = this->mHandleStartLocal;
            if (this->mPinningType == 0x9e6e561c) {
                switch (this->mAxisToIgnore) {
                case 0x67489dc: rel[0] = 0.0f; break;
                case 0x3bc16bcd: rel[1] = 0.0f; break;
                case 0x1d369ee: rel[2] = 0.0f; break;
                }
                dest = this->mBlockPosition + rel;
            } else {
                float d = Dot(this->mPlaneNormal, rel);
                dirA = this->mPlaneNormal * d;
                dest = this->mBlockPosition + dirA;
            }
        } else {
            dest = ballCenter + end;
        }

        if (this->mPinningType == 0xf647f102) {
            dirVec = Vec3_MulMat(this->mOriginalTrianglePoint, toBlock);
            span = Vec3_MulMat(this->mOriginalTrianglePoint, toBlock) * segLength;
        }

        float len2 = VectorLength(&Vec3(this->mEndPt - this->mStartPt));
        ScratchSlots<1>();
        this->mStartPt = dest - ((dirVec * this->mDelta) * len2);
        this->mEndPt = dest + ((dirVec * (1.0f - this->mDelta)) * len2);
        ((void(__thiscall*)(SP::cSPEditorHandleDeform*))this->vptr[5])(this);
    }
}
