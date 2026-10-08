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

template <int N> inline void ScratchSlots() { uint32_t s[N]; }   // stands in for the frame of a declined inline

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
