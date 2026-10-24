// Slice s00faa5c0: SP::cTerrainSphere::SaveModifications @ 0x00faa5c0 (PDB-candidate name from Ghidra; unverified).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as the other cTerrainSphere slices.
//
// If the sphere has a config/property sink (this+0x28), it packs three lists of 0xac-byte "relevel" records
// into (key array, transform array) variants and hands them to the sink:
//   1. list at +0x798 -> properties 0x3ad5568 (keys) / 0x3ad5569 (transforms)
//   2. lists at +0x770 then +0x784 concatenated -> properties 0x43b29e1 / 0x43b29e2
// then calls SetModels() to rebuild the placed models.
#include "types.h"
#include <new>

namespace EA { namespace ResourceMan { struct Key { uint32_t instance, type, group; }; } }
typedef EA::ResourceMan::Key Key;

struct Allocator { const char* mpName; };

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix3 {
    Vector3 row0, row1, row2;
    Matrix3() {}
    Matrix3& Assign(const Matrix3& m);          // 0x0041cb40
};

// Matrix3 with the out-of-line row copy (loop over the +0x798 list) and the same layout with an inline copy.
struct Matrix3I { Vector3 row0, row1, row2; };
struct cSPTransformI {                              // transform as copied by the +0x770/+0x784 loops
    uint16_t mFlags, mModCount;
    float mTx, mTy, mTz, mScale;
    Matrix3I mRot;
};
struct cSPTransform {
    uint16_t mFlags, mModCount;
    float mTx, mTy, mTz, mScale;
    Matrix3 mRot;
    cSPTransform() {}
    __forceinline cSPTransform(const cSPTransform& o) {
        mFlags = o.mFlags; mModCount = o.mModCount;
        mTx = o.mTx; mTy = o.mTy; mTz = o.mTz; mScale = o.mScale;
        mRot.Assign(o.mRot);
    }
    __forceinline cSPTransform(const cSPTransformI& o) {
        mFlags = o.mFlags; mModCount = o.mModCount;
        mTx = o.mTx; mTy = o.mTy; mTz = o.mTz; mScale = o.mScale;
        mRot.row0 = Vector3(o.mRot.row0);
        mRot.row1 = Vector3(o.mRot.row1);
        mRot.row2 = Vector3(o.mRot.row2);
    }
};
struct Rect { float l, t, r, b; };
struct cRelevelI {                                  // same record as cRelevel, other transform flavour
    cSPTransformI mTransform; Rect mBounds[6]; Key mKey; uint32_t mFlagsAndBits; uint32_t mExtra;
};
struct cRelevel {                                   // 0xac bytes in the retail layout
    cSPTransform mTransform;                        // +0x00
    Rect mBounds[6];                                // +0x38
    Key mKey;                                       // +0x98
    uint32_t mFlagsAndBits;                         // +0xa4
    uint32_t mExtra;                                // +0xa8
};

void __cdecl FreeBlock(void* p);                    // 0x00f47380 (operator_delete__)

struct KeyVector {
    Key* mBegin; Key* mEnd; Key* mCap; Allocator mAlloc;
    KeyVector() : mBegin(0), mEnd(0), mCap(0) {}
    void Reserve(int n);                            // 0x0041e4d0 (Vec3Vec_Reserve, 12-byte elements)
    void DoInsertValue(Key* pos, const Key& v);     // 0x004e3e10
    Key* erase(Key* first, Key* last);              // 0x0050f740
    __forceinline void push_back(const Key& v) {
        if (mEnd < mCap) ::new (mEnd++) Key(v);
        else DoInsertValue(mEnd, v);
    }
    ~KeyVector() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};
struct XformVector {
    cSPTransform* mBegin; cSPTransform* mEnd; cSPTransform* mCap; Allocator mAlloc;
    XformVector() : mBegin(0), mEnd(0), mCap(0) {}
    void Reserve(int n);                            // 0x00b04c50
    void DoInsertValue(cSPTransform* pos, const cSPTransform& v);   // 0x00423960
    void DoInsertValue(cSPTransform* pos, const cSPTransformI& v);  // same function; the record is passed by address
    template <class U> __forceinline void push_back(const U& v) {
        if (mEnd < mCap) ::new (mEnd++) cSPTransform(v);
        else DoInsertValue(mEnd, v);
    }
    void erase(cSPTransform* first, cSPTransform* last) { mEnd = mEnd - (last - first); }
    ~XformVector() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};

struct Variant {
    uint32_t data[4]; uint16_t flags; uint16_t type;
    Variant() { flags = 0; type = 0; }
    void Set(int a, int b, void* ptr, int elemSize, int count);     // 0x0093dd80
    void Destruct(int);                                             // 0x0093db80
    ~Variant() { if (flags & 4) Destruct(0); }
};

struct IConfigSink {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProperty(uint32_t id, Variant* v);              // +0x14
};

template <class T> struct RecVec { T* mBegin; T* mEnd; T* mCap; Allocator mAlloc;
    int size() const { return mEnd - mBegin; } };

// Virtual slots of cTerrainSphere that this TU dispatches through (offsets from the vftable).
struct cTerrainSphereVBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual bool v4c(int level);                                // +0x4c
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();                                         // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4();
    virtual bool vd8();                                         // +0xd8
};

struct TerrainConfig;
struct cTerrainSphereQuad;
struct cTerrainSphereRegion;
struct cJob;

#define CHK(cls, name, off) typedef char chk_##cls##_##name[(offsetof(cls, name) == (off)) ? 1 : -1]

struct cTerrainSphere : cTerrainSphereVBase {
    char pad00[0x24];                           // +0x00 (vftable pointer)
    IConfigSink* mSink;                         // +0x28
    TerrainConfig* mConfig;                     // +0x2c
    char pad30[0xfc - 0x30];
    int mFieldFC;                               // +0xfc
    char pad100[0x110 - 0x100];
    uint8_t mFlag110;                           // +0x110  "outside the cull range"
    uint8_t mFlag111;                           // +0x111
    char pad112[0x114 - 0x112];
    int mCounter114;                            // +0x114
    cTerrainSphereQuad* mQuads[6];              // +0x118
    char pad130[0x1d0 - 0x130];
    int mField1d0;                              // +0x1d0
    char pad1d4[0x20c - 0x1d4];
    int mField20c;                              // +0x20c
    cTerrainSphereRegion* mField210;            // +0x210
    char pad214[0x30c - 0x214];
    float mCenterX;                             // +0x30c
    float mCenterY;                             // +0x310
    float mCenterZ;                             // +0x314
    char pad318[0x33d - 0x318];
    uint8_t mFlag33d;                           // +0x33d
    char pad33e[0x360 - 0x33e];
    float mField360;                            // +0x360
    float mField364;                            // +0x364
    char pad368[1];
    uint8_t mFlag369;                           // +0x369
    char pad36a[2];
    int mField36c;                              // +0x36c
    uint8_t mFlag370;                           // +0x370
    char pad371[3];
    float mRects[6 * 6 * 4];                    // +0x374  per-level quad rects, 4 floats each
    char pad5b4[0x770 - 0x5b4];
    RecVec<cRelevelI> mRelevelA;                 // +0x770
    char pad780[4];
    RecVec<cRelevelI> mRelevelB;                 // +0x784
    char pad794[4];
    RecVec<cRelevel> mRelevelC;                 // +0x798
    char pad7a8[0x81c - 0x7a8];
    cJob* mJob;                                 // +0x81c
    char pad820[0x828 - 0x820];
    float mRegions[6][4];                       // +0x828  region of each of the 6 quads
    char pad888[0xa48 - 0x888];
    int mFieldA48;                              // +0xa48  countdown
    void SetModels();                           // 0x00fa96d0
    void SaveModifications();
    void AddToEffectsSystem();                  // 0x00f977c0
    void UpdateQuadsPostCamera(int arg);        // 0x00fa5610
    void UpdatePostCamera(int arg1, int arg2);  // 0x00faad80
    void FUN_00f9b8c0(int* a, int* b, int flag, int zero, float radius);   // 0x00f9b8c0
    void FUN_00f96370();                        // 0x00f96370
    void FUN_00f96f90();                        // 0x00f96f90
    void FUN_00f9ba40(int arg);                 // 0x00f9ba40
};

CHK(cTerrainSphere, mSink, 0x28);
CHK(cTerrainSphere, mConfig, 0x2c);
CHK(cTerrainSphere, mFieldFC, 0xfc);
CHK(cTerrainSphere, mFlag110, 0x110);
CHK(cTerrainSphere, mCounter114, 0x114);
CHK(cTerrainSphere, mQuads, 0x118);
CHK(cTerrainSphere, mField210, 0x210);
CHK(cTerrainSphere, mCenterX, 0x30c);
CHK(cTerrainSphere, mFlag33d, 0x33d);
CHK(cTerrainSphere, mField360, 0x360);
CHK(cTerrainSphere, mFlag369, 0x369);
CHK(cTerrainSphere, mField36c, 0x36c);
CHK(cTerrainSphere, mFlag370, 0x370);
CHK(cTerrainSphere, mRects, 0x374);
CHK(cTerrainSphere, mRelevelA, 0x770);
CHK(cTerrainSphere, mJob, 0x81c);
CHK(cTerrainSphere, mRegions, 0x828);
CHK(cTerrainSphere, mFieldA48, 0xa48);

template <class R> static __forceinline void AppendRelevels(KeyVector& keys, XformVector& xf, const RecVec<R>& v)
{
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        keys.push_back(v.mBegin[i].mKey);
        xf.push_back(v.mBegin[i].mTransform);
    }
}

// @ 0x00faa5c0
void cTerrainSphere::SaveModifications()
{
    if (mSink) {
        KeyVector keys;
        XformVector xf;
        keys.Reserve(mRelevelC.size());
        xf.Reserve(mRelevelC.size());
        AppendRelevels(keys, xf, mRelevelC);
        Variant vKeys;
        vKeys.Set(0x20, 0x98, keys.mBegin, 0xc, keys.mEnd - keys.mBegin);
        Variant vXf;
        int nXf = xf.mEnd - xf.mBegin;
        vXf.Set(0x38, 0x98, xf.mBegin, 0x38, nXf);
        mSink->SetProperty(0x3ad5568, &vKeys);
        mSink->SetProperty(0x3ad5569, &vXf);
        keys.erase(keys.mBegin, keys.mEnd);
        xf.mEnd = xf.mEnd - nXf;

        keys.Reserve(mRelevelA.size() + mRelevelB.size());
        xf.Reserve(mRelevelA.size() + mRelevelB.size());
        AppendRelevels(keys, xf, mRelevelA);
        AppendRelevels(keys, xf, mRelevelB);
        Variant vKeys2;
        vKeys2.Set(0x20, 0x98, keys.mBegin, 0xc, keys.mEnd - keys.mBegin);
        Variant vXf2;
        vXf2.Set(0x38, 0x98, xf.mBegin, 0x38, xf.mEnd - xf.mBegin);
        mSink->SetProperty(0x43b29e1, &vKeys2);
        mSink->SetProperty(0x43b29e2, &vXf2);
        SetModels();
    }
}

// ---------------------------------------------------------------------------
// Terrain/Sphere/cTerrainMapJobInfo registration + the quad-array append.
// ---------------------------------------------------------------------------
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)

struct cJob {
    void* mpFunction;                               // +0x00
    void* mpUserData;                               // +0x04
    char  pad08[0x10];
    int   mPriority;                                // +0x18
    void SetObject(void* obj);                      // 0x0068f9b0
    int  Release();                                 // 0x00690120
    int  GetStatus();                               // 0x006909b0
};

struct cJobManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual bool CanRegister(void* owner);          // +0x10
};

cJobManager* GetJobManager();                       // 0x0068f4d0
extern int gTerrainMapJobFlags;                     // 0x016c9e64
extern void TerrainMapJobCallback();                // 0x00fa9830

struct cILayerI {
    virtual void l0();                              // +0x00 (register callback)
    virtual int Release();                          // +0x04
};
struct IEventModifierI {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
};
struct cTerrainMapJobBase {
    long   mRefCount;                               // +0x08
    cJob** mpOwner;                                 // +0x0c
    __forceinline cTerrainMapJobBase(cJob** owner)
    {
        _InterlockedExchange(&mRefCount, 0);
        mpOwner = owner;
    }
};
struct cTerrainMapJobInfo : cILayerI, IEventModifierI, cTerrainMapJobBase {
    int    mFlags;                                  // +0x10
    __forceinline cTerrainMapJobInfo(cJob** owner) : cTerrainMapJobBase(owner)
    {
        mFlags = gTerrainMapJobFlags;
    }
    virtual void l0();                              // registers the callback
};

void* AllocJobInfo(size_t size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

// @ 0x00faacd0
bool __cdecl CreateTerrainMapJob(cTerrainSphere* unused, cJob** out)
{
    if (GetJobManager()->CanRegister(out)) {
        void* info = AllocJobInfo(
            sizeof(cTerrainMapJobInfo), "Terrain/Sphere/cTerrainMapJobInfo", 0, 0, 0, 0);
        if (info) {
            ::new (info) cTerrainMapJobInfo(out);
            cILayerI* layer = (cILayerI*)info;
            layer->l0();
        } else {
            info = 0;
        }
        (*out)->SetObject(info);
        (*out)->mpFunction = (void*)&TerrainMapJobCallback;
        (*out)->mpUserData = info;
        (*out)->mPriority = (int)0x80000000;
        if (info)
            ((cILayerI*)info)->Release();
        return true;
    }
    return false;
}

struct cQuadElem {                                   // 0x110-byte element
    void*    mpBegin;                                // +0x00
    void*    mpEnd;                                  // +0x04
    void*    mpCap;                                  // +0x08
    uint32_t mPad0c;                                 // +0x0c
    void*    mpInline;                               // +0x10
    uint32_t mPad14;                                 // +0x14
    char     mBuf[0x8c];                             // +0x18
    char     mTail[0x110 - 0xa4];                    // +0xa4
    cQuadElem()
    {
        void* p = mBuf;
        mpInline = p;
        mpEnd = p;
        mpBegin = p;
        mpCap = (char*)p + 0x8c;
    }
    ~cQuadElem()
    {
        if (mpBegin && mpBegin != mpInline)
            FreeBlock(mpBegin);
    }
};

struct cQuadVec {
    cQuadElem* mBegin; cQuadElem* mEnd; cQuadElem* mCap;
    void DoInsertValue(cQuadElem* pos, const cQuadElem& v);   // 0x00fab0e0
    void Append();
};

// @ 0x00fab230
void cQuadVec::Append()
{
    if (mEnd < mCap) {
        cQuadElem* p = mEnd++;
        ::new (p) cQuadElem();
    } else {
        cQuadElem tmp;
        DoInsertValue(mEnd, tmp);
    }
}

// ---------------------------------------------------------------------------
// SP::cTerrainSphere::UpdatePostCamera @ 0x00faad80
// ---------------------------------------------------------------------------
#include <math.h>

struct TerrainConfig {
    char  pad00[0x34];
    float m34;                                  // +0x34  cull radius bias
    float m38;                                  // +0x38  cell scale
    float m3c;                                  // +0x3c  cell size
    float m40;                                  // +0x40  cell size bias
    char  pad44[0x50 - 0x44];
    float m50;                                  // +0x50
    float m54;                                  // +0x54
};
CHK(TerrainConfig, m34, 0x34);
CHK(TerrainConfig, m38, 0x38);
CHK(TerrainConfig, m3c, 0x3c);
CHK(TerrainConfig, m40, 0x40);
CHK(TerrainConfig, m50, 0x50);
CHK(TerrainConfig, m54, 0x54);

struct cModelManagerNodeVBase;
struct cModelManagerVBase {
    virtual void m000(); virtual void m004(); virtual void m008(); virtual void m00c();
    virtual void m010(); virtual void m014(); virtual void m018();
    virtual cModelManagerNodeVBase* v1c(int name);              // +0x1c
};
struct cModelManagerNodeVBase {
    virtual void n000(); virtual void n004(); virtual void n008(); virtual void n00c();
    virtual void n010(); virtual void n014(); virtual void n018(); virtual void n01c();
    virtual void n020(); virtual void n024(); virtual void n028(); virtual void n02c();
    virtual void n030(); virtual void n034(); virtual void n038(); virtual void n03c();
    virtual void n040(); virtual void n044(); virtual void n048(); virtual void n04c();
    virtual void n050(); virtual void n054(); virtual void n058(); virtual void n05c();
    virtual void n060(); virtual void n064(); virtual void n068(); virtual void n06c();
    virtual void n070(); virtual void n074(); virtual void n078(); virtual void n07c();
    virtual void n080(); virtual void n084(); virtual void n088(); virtual void n08c();
    virtual void n090(); virtual void n094(); virtual void n098(); virtual void n09c();
    virtual void n0a0(); virtual void n0a4(); virtual void n0a8(); virtual void n0ac();
    virtual void n0b0(); virtual void n0b4(); virtual void n0b8(); virtual void n0bc();
    virtual void n0c0(); virtual void n0c4(); virtual void n0c8(); virtual void n0cc();
    virtual void n0d0(); virtual void n0d4(); virtual void n0d8(); virtual void n0dc();
    virtual void n0e0(); virtual void n0e4(); virtual void n0e8(); virtual void n0ec();
    virtual void n0f0(); virtual void n0f4(); virtual void n0f8(); virtual void n0fc();
    virtual void n100(); virtual void n104(); virtual void n108(); virtual void n10c();
    virtual void n110(); virtual void n114(); virtual void n118(); virtual void n11c();
    virtual void n120(); virtual void n124(); virtual void n128(); virtual void n12c();
    virtual void n130(); virtual void n134(); virtual void n138(); virtual void n13c();
    virtual void n140(); virtual void n144(); virtual void n148(); virtual void n14c();
    virtual void n150(); virtual void n154(); virtual void n158();
    virtual void v15c(int a, void* b, float c);                 // +0x15c
};
cModelManagerVBase* ModelManager();                             // 0x0067dd80

struct cTerrainSphereQuad {
    void TraverseSubdivided(int level, const float* rect);      // 0x00fb0d20
    void MarkVerticesDirty(int level, const float* rect);       // 0x00faf140
    void MarkIndicesDirty(int level, const float* rect);        // 0x00faf400
};

extern int   g16c9e7c[3];                                       // 0x016c9e7c
extern float g16c9e8c;                                          // 0x016c9e8c
extern void __cdecl FUN_00fbf570(int arg, float radius, int count);             // 0x00fbf570
struct cTerrainSphereRegion {
    void FUN_00fc7b30(int arg);                                 // 0x00fc7b30
};

// @ 0x00faad80
void cTerrainSphere::UpdatePostCamera(int arg1, int arg2)
{
    if (mFieldA48 != 0) {
        if (mFieldA48 > 0 && --mFieldA48 == 0) {
            v80();
            FUN_00f9b8c0(&arg1, &arg1, mFieldFC != 0, 0, 10.0f);
        }
        return;
    }
    if (mFieldFC != 0)
        return;

    if (mField360 != mConfig->m34 ||
        mField364 != mConfig->m3c * mConfig->m38 ||
        mFlag111 != 0) {
        AddToEffectsSystem();
        float vals[3];
        vals[0] = mConfig->m3c * mConfig->m38 + mConfig->m34;
        vals[1] = mConfig->m50;
        vals[2] = mConfig->m54;
        float* radius = (vals[0] > vals[1]) ? &vals[0] : &vals[1];
        ModelManager()->v1c(0x3fbae24)->v15c(0, &g16c9e8c, *radius);
    }

    cTerrainSphere* base = (cTerrainSphere*)((char*)this - mField36c);
    mFlag33d = (mFlag33d != 0) || ((base->mFlag369 & 7) != 0);
    v10();
    g16c9e7c[0] = 0;
    g16c9e7c[1] = 0;
    g16c9e7c[2] = 0;
    int count = mField20c;
    ++mCounter114;
    if (count != 0) {
        int n = mField1d0;
        FUN_00fbf570(arg2, 100.0f, (n != 4) ? n : 0);
    }

    if (mFlag33d != 0 && mFlag370 == 0 && vd8()) {
        FUN_00f96370();
        for (int i = 0; i < 6; ++i) {
            const float* src = &mRects[(i + 6 * mField36c) * 4];
            float rect[4];
            rect[0] = src[0];
            rect[1] = src[1];
            rect[2] = src[2];
            rect[3] = src[3];
            mRegions[i][0] = rect[0];
            mRegions[i][1] = rect[1];
            mRegions[i][2] = rect[2];
            mRegions[i][3] = rect[3];
            if (v4c(8)) {
                rect[0] = 0.0f;
                rect[1] = 0.0f;
                rect[2] = 1.0f;
                rect[3] = 1.0f;
            }
            cTerrainSphereQuad* quad = mQuads[i];
            quad->TraverseSubdivided(i, rect);
            quad->MarkVerticesDirty(i, rect);
            quad->MarkIndicesDirty(i, rect);
        }
        FUN_00f96f90();
        mFlag370 = 1;
        if (mJob) {
            cJob* old = mJob;
            mJob = 0;
            old->Release();
        }
        CreateTerrainMapJob(this, &mJob);
        mJob->GetStatus();
        mFlag33d = 0;
    }

    FUN_00f9ba40(arg2);
    {
        float dx = mCenterX, dy = mCenterY, dz = mCenterZ;
        float dist = sqrtf(dx * dx + dy * dy + dz * dz) - mConfig->m34;
        float limit = (mConfig->m40 + mConfig->m3c) * mConfig->m38 - 1.0f;
        mFlag110 = (limit > dist);
    }
    UpdateQuadsPostCamera(arg2);
    cTerrainSphereRegion* region = mField210;
    if (region)
        region->FUN_00fc7b30(arg2);
}
