// s00fba330 targets: cTerrainStateMgr helper methods (names are working names).
#include "types.h"
#include <math.h>

typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;

struct IRef {
    virtual void AddRef();                  // +0x00
    virtual void Release();                 // +0x04
};

struct TmpRef {
    IRef* p;
    IRef* Detach() { IRef* v = p; p = 0; return v; }
    void  Reset()  { if (p) { p->Release(); p = 0; } }
    TmpRef& operator=(IRef* n) {
        IRef* old = p;
        if (n != old) {
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
        return *this;
    }
};

struct Vec3 {
    float x, y, z;
};

struct Quaternion {                         // 4 dwords
    float x, y, z, w;
};

struct Matrix33 {                           // 9 dwords, 0x24 bytes
    float m[9];
};

// cSPTransform-shaped local used by the terrain setters.  Observed layout:
//   u16 @+0x00 (flags, bit0x04 and bit0x02 are set during the build)
//   i16 @+0x02 (change counter, incremented on each field update)
//   float @+0x04, @+0x08, @+0x0c (a Vec3: the axis / direction)
//   float @+0x14 (the constant 1.0f)
//   Matrix33 @+0x18
struct Transform {
    uint16_t field00;                       // +0x00
    int16_t  counter02;                     // +0x02
    float    mx04;                          // +0x04
    float    my08;                          // +0x08
    float    mz0c;                          // +0x0c
    uint32_t pad10;                         // +0x10
    float    mOne14;                        // +0x14
    Matrix33 mMat;                          // +0x18..+0x3b
};

// rw::math::fpu::Matrix33Template<float,0>::Matrix33Template (0x41cb40)
//   __thiscall: ecx = the matrix, one stack arg = the source table
struct Matrix33T {
    void Assign(const void* src);           // 0x41cb40
    void Build(const float* pos, const float* dir);  // 0x6bac90
};
// Matrix3FromQuaternion (0x59c190): out-param sret + 2 args
void Matrix3FromQuaternion(Matrix33* out, const Vec3* axis, const Quaternion* q);  // 0x59c190
// cSPTransform::Invert (0x40efa0): __thiscall, no args
struct TransformInv { void Invert(); };     // 0x40efa0
// helpers used by both setters
void FUN_006bac90(const void* matrix, const float* dir);          // 0x6bac90
void Basis3Build(float* out);                                     // 0x6b9440
void FUN_00ac9480(void* dst, int* src);                           // 0xac9480

struct cTerrainStateMgrLite {
    // +0x00 model/transform data copied by FUN_00fbab70
    char     pad00[0x14];
    IRef*    mpRef14;                       // +0x14
    IRef*    mpRef18;                       // +0x18
    IRef*    mpRef1c;                       // +0x1c
    IRef*    mpRef20;                       // +0x20
    char     pad24[0x10];
    Vec3     mPos34;                        // +0x34
    Matrix33 mBasis40;                      // +0x40
};

// ---------------------------------------------------------------------------
// 00fbab70: copy-assign the whole terrain-state record (5 floats, 4 refs, tail).
struct TerrainRecord {
    float    mF[5];                         // +0x00..+0x13
    IRef*    mpRef14;                       // +0x14
    IRef*    mpRef18;                       // +0x18
    IRef*    mpRef1c;                       // +0x1c
    IRef*    mpRef20;                       // +0x20
    uint32_t mTail00;                       // +0x24
    uint32_t mTail01; uint32_t mTail02; uint32_t mTail03; uint32_t mTail04;
    uint32_t mTail05; uint32_t mTail06; uint32_t mTail07; uint32_t mTail08;
    uint32_t mTail09; uint32_t mTail10; uint32_t mTail11; uint32_t mTail12;
    uint32_t mTail13; uint32_t mTail14;
    struct { uint32_t a, b, c; } mVec60;    // +0x60..+0x6b
    TerrainRecord* Assign(const TerrainRecord& src);
};

// @ 0x00fbab70
TerrainRecord* TerrainRecord::Assign(const TerrainRecord& src)
{
    mF[0] = src.mF[0];
    mF[1] = src.mF[1];
    mF[2] = src.mF[2];
    mF[3] = src.mF[3];
    mF[4] = src.mF[4];
    { IRef* n = src.mpRef14; IRef* o = mpRef14; if (n != o) { if (n) n->AddRef(); mpRef14 = n; if (o) o->Release(); } }
    { IRef* n = src.mpRef18; IRef* o = mpRef18; if (n != o) { if (n) n->AddRef(); mpRef18 = n; if (o) o->Release(); } }
    { IRef* n = src.mpRef1c; IRef* o = mpRef1c; if (n != o) { if (n) n->AddRef(); mpRef1c = n; if (o) o->Release(); } }
    { IRef* n = src.mpRef20; IRef* o = mpRef20; if (n != o) { if (n) n->AddRef(); mpRef20 = n; if (o) o->Release(); } }
    mTail00 = src.mTail00;
    mTail01 = src.mTail01; mTail02 = src.mTail02; mTail03 = src.mTail03; mTail04 = src.mTail04;
    mTail05 = src.mTail05; mTail06 = src.mTail06; mTail07 = src.mTail07; mTail08 = src.mTail08;
    mTail09 = src.mTail09; mTail10 = src.mTail10; mTail11 = src.mTail11; mTail12 = src.mTail12;
    mTail13 = src.mTail13; mTail14 = src.mTail14;
    {
        const uint32_t* p = &src.mVec60.a;
        mVec60.a = p[0]; mVec60.b = p[1]; mVec60.c = p[2];
    }
    return this;
}

// ---------------------------------------------------------------------------
// 00fbacb0 / 00fbad70: set the position (+0x34) and rebuild the basis (+0x40).
// Constant matrices used by both: 0x16d6710/0x16d6714/0x16d6718 and 0x1485720 (=1.0f).
struct CfgPtrs {
    float* a;  // 0x16d6710
    float* b;  // 0x16d6714
    float* c;  // 0x16d6718
    float* one;// 0x1485720
};

struct BasisHolder {                        // the four transform building blocks
    Vec3     mPos34;                        // +0x34
    Matrix33 mBasis40;                      // +0x40
};

struct TerrainMgr {
    char        pad00[0x34];
    Vec3        mPos34;                     // +0x34
    Matrix33    mBasis40;                   // +0x40
    char        pad64[0x1f4 - 0x64];
    IRef*       mpRef1f4;                   // +0x1f4
    char        pad1f8[0x5c0 - 0x1f8];
    uint32_t    mSel5c0;                    // +0x5c0
    int         mSel5c4;                    // +0x5c4
    void SetPosition(const Vec3& p);        // 0x00fbacb0
    void SetFromQuaternion(const Vec3& dir, const Quaternion& q);  // 0x00fbad70
    void Select5c0(int idx);                // 0x00fbaf10
    void Select5c4(int idx);                // 0x00fbaf50
};

struct SubAt20c {                           // the +0x20c sub-object FUN_00ac9480 is called on
    void Apply(const int* entry);           // 0xac9480 (__thiscall, 1 arg)
};

static const void* const kMatrixSrc  = (const void*)0x016d6db0;
static const float* const kConstA    = (const float*)0x016d6710;
static const float* const kConstB    = (const float*)0x016d6714;
static const float* const kConstC    = (const float*)0x016d6718;
static const float* const kOne       = (const float*)0x01485720;

// @ 0x00fbacb0
void TerrainMgr::SetPosition(const Vec3& p)
{
    mPos34 = p;

    // cSPTransform local: constant floats, zero flags/counter, one = 1.0f,
    // then a matrix built by Matrix33T::Assign.
    Transform t;
    t.mx04 = *kConstA;
    t.my08 = *kConstB;
    t.mz0c = *kConstC;
    t.field00 = 0;
    t.counter02 = 0;
    t.pad10 = 0;
    t.mOne14 = *kOne;
    ((Matrix33T*)&t.mMat)->Assign(kMatrixSrc);

    float dir[3];
    dir[0] = 0.0f; dir[1] = 0.0f; dir[2] = 1.0f;

    ((Matrix33T*)&t.mMat)->Build((const float*)&mPos34, dir);
    Basis3Build((float*)&mBasis40);
}

// @ 0x00fbad70
void TerrainMgr::SetFromQuaternion(const Vec3& dir, const Quaternion& q)
{
    Transform t;
    t.field00 = 0;
    t.counter02 = 0;
    t.pad10 = 0;
    t.mOne14 = *kOne;
    ((Matrix33T*)&t.mMat)->Assign(kMatrixSrc);

    t.field00 |= 4; ++t.counter02;
    t.mx04 = dir.x; t.my08 = dir.y; t.mz0c = dir.z;
    Matrix33 qm;
    Matrix3FromQuaternion(&qm, (const Vec3*)&t.mx04, &q);

    t.field00 |= 2; ++t.counter02;
    ((TransformInv*)&t)->Invert();

    float inv = 1.0f / sqrtf(t.mx04*t.mx04 + t.my08*t.my08 + t.mz0c*t.mz0c);
    mPos34.x = t.mx04 * inv;
    mPos34.y = t.my08 * inv;
    mPos34.z = t.mz0c * inv;

    Transform t2;
    t2.mx04 = *kConstA;
    t2.my08 = *kConstB;
    t2.mz0c = *kConstC;
    t2.field00 = 0;
    t2.counter02 = 0;
    t2.pad10 = 0;
    t2.mOne14 = *kOne;
    ((Matrix33T*)&t2.mMat)->Assign(kMatrixSrc);

    float d2[3];
    d2[0] = 0.0f; d2[1] = 0.0f; d2[2] = 1.0f;
    ((Matrix33T*)&t2.mMat)->Build((const float*)&mPos34, d2);
    Basis3Build((float*)&mBasis40);

    (void)qm;
}

// @ 0x00fbaf10
void TerrainMgr::Select5c0(int idx)
{
    if (mSel5c0 == (uint32_t)idx)
        return;
    if (idx < 0)
        return;
    const unsigned kMax = 0x10;
    if ((unsigned)idx >= kMax)
        return;
    mSel5c0 = idx;
    ((SubAt20c*)((char*)this + 0x20c))->Apply((int*)((char*)0x016d6d30 + idx * 4));
}

// @ 0x00fbaf50
void TerrainMgr::Select5c4(int idx)
{
    if (mSel5c4 == idx)
        return;
    mSel5c4 = idx;
    IRef* o = mpRef1f4;
    IRef* n = *(IRef**)((char*)0x016d6d70 + idx * 4);
    if (n != o) {
        if (n) n->AddRef();
        mpRef1f4 = n;
        if (o) o->Release();
    }
}

// ---------------------------------------------------------------------------
// 00fbafa0 is recorded as nonmatching (see nonmatching.txt): the nested
// 6x4x4 / 0x80 / 0x20 histogram reduction does not reproduce byte-exactly
// from source shape.
