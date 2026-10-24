// slice s00a8c850: EA::Swarm::cDistributeEffect::~cDistributeEffect (0x00a8cb00, 243 bytes), the base-body
// destructor (thiscall, plain `ret`, no deleting wrapper here). It re-sets the four embedded vtable pointers,
// frees the sample and surface buffers (sp_vector-style: a block is freed only when its header word at
// [-4] is non-zero), releases three interface pointers and destroys two embedded sub-objects.
// It ends by re-setting the first two vtables to the base-class ones.
// Retail member offsets (from the asm; they differ from the 2008 PDB layout in a few places, see
// match/slices/s00a8d450/s00a8d450.cpp for the same class). Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>

typedef uint32_t uint32;
typedef uint8_t uint8;

// 0x00f47380: operator delete (cdecl, one argument).
void operator_delete__(void* p);

// Frees an sp_vector-style block: only when non-null and its header word is non-zero.
static inline void FreeBlock(void* p) {
    if (p != 0 && ((int*)p)[-1] != 0)
        operator_delete__(p);
}

// Interface with AddRef()/Release() in vtable slots 0 and 1.
struct cIRefObj {
    virtual void AddRef();
    virtual void Release();
};

// The map interface adds the slots used by Init on top of AddRef/Release.
struct cIMap : cIRefObj {
    virtual void Prepare();         // +0x08
    virtual void Slot0c();
    virtual int  GetValue();        // +0x10
    virtual void Slot14();
    virtual void Slot18();
    virtual bool IsEnabled();       // +0x1c
};

// ---------------------------------------------------------------- math
struct Vector2 {
    float x, y;
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};

// rw::math::fpu::Matrix33Template<float,0>: three rows; out-of-line Assign at 0x0041cb40.
struct Matrix3 {
    Vector3 row[3];
    Matrix3* Assign(const void* src);                           // 0x0041cb40
};

extern const Vector3 kVector3Zero;                              // 0x0167827c
extern const Vector3 kSubdivScaleInit;                          // 0x01678230
extern const float kRealOne;                                    // 0x01485720
extern const Matrix3 kMatrix3Identity;                          // 0x01678328
extern const float kAltitudeMin;                                // 0x01418f90 (-10000)
extern const float kAltitudeMax;                                // 0x013f0620 (+10000)
extern const char kAllocatorFile[];                             // 0x013ebb38 (EASTL allocator.h)
extern const char kAllocatorName[];                             // 0x013f2150 ("EASTL")

// cTransform (0x38): flags, modification count, offset, scale, rotation.
struct cTransform {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    Vector3  mOffset;       // +0x04
    float    mScale;        // +0x10
    Matrix3  mRotation;     // +0x14
};

// cSPTransformOps (0x38): a transform plus the out-of-line Assign helper.
struct cSPTransformOps : cTransform {
    cSPTransformOps* Assign(const void* src);                   // 0x00537dc0
};

// Tail of a sample: four colour words and the sample index, copied as a plain block.
struct cSampleTail {
    uint32 mColour[4];              // +0x00
    int    mIndex;                  // +0x10
};

// cDistributeSample (0x4c): transform, then the tail block.
struct cDistributeSample {
    cSPTransformOps mTransform;     // +0x00
    cSampleTail mTail;              // +0x38
    cDistributeSample(const cDistributeSample& s);              // 0x00a89de0
    cDistributeSample& operator=(const cDistributeSample& s) {
        mTransform.Assign(&s);
        mTail = s.mTail;
        return *this;
    }
};

void CopySamples(const cDistributeSample* first, const cDistributeSample* last, cDistributeSample* dst);          // 0x00a8a0a0
void MoveSamplesBack(cDistributeSample* first, cDistributeSample* last, cDistributeSample* dst);                  // 0x00a8a0f0
cDistributeSample* UninitCopySamples(cDistributeSample* first, cDistributeSample* last, cDistributeSample* dst);  // 0x00a89f70
void* operator new(unsigned int size, const char* name, int flags, int align, const char* file, int line);

// eastl::vector<cDistributeSample, sp_vector_allocator>: three pointers plus two allocator words.
struct SampleVector {
    cDistributeSample* mpBegin;     // +0x00
    cDistributeSample* mpEnd;       // +0x04
    cDistributeSample* mpCapacity;  // +0x08
    uint32 mAllocator[2];           // +0x0c
    void insert(cDistributeSample* pos, const cDistributeSample& value);   // 0x00a8ce30
    void erase_all();                                                      // 0x00a8cfe0
};

// sp_vector whose element type is not modelled (at +0x130, +0x144 and +0x19c).
// mpBegin is volatile: the destructor reads it while re-setting the embedded vtable pointers, and
// the loads have to stay in source order instead of being hoisted above those stores.
struct RawVector {
    void* volatile mpBegin;         // +0x00
    void* mpEnd;                    // +0x04
    void* mpCapacity;               // +0x08
    uint32 mAllocator[2];           // +0x0c
    void resize(int count);         // 0x004c0410
};

// Interface released through vtable slot 0 when an effect reference is destroyed.
struct cIEffectRefObj {
    virtual void Release();         // +0x00
};

// Element of the effect-reference vector (0x18 bytes).
struct cEffectRef {
    cIEffectRefObj* mpEffect;       // +0x00
    uint32 pad04[5];
    ~cEffectRef() { if (mpEffect) mpEffect->Release(); }
};

cEffectRef* CopyEffectRefs(cEffectRef* first, cEffectRef* last, cEffectRef* dst);      // 0x00a8c070

struct EffectVector {
    cEffectRef* mpBegin;            // +0x00
    cEffectRef* mpEnd;              // +0x04
    cEffectRef* mpCapacity;         // +0x08
    uint32 mAllocator[2];           // +0x0c
    cEffectRef* erase(cEffectRef* first, cEffectRef* last);         // 0x00a8d020
};

// Embedded sub-object at +0xd8 with a parameterless thiscall destructor body (0x00a89da0).
struct cSubObjD {
    void* mpBegin;                  // +0x00
    void* mpEnd;                    // +0x04
    void* mpCap;                    // +0x08
    uint32 pad0c[2];                // +0x0c
    void FUN_00a89da0();
};

// Embedded sp_vector at +0x11c with a parameterless thiscall destructor body (0x00a8c440).
struct cSubObjC {
    void* mpBegin;                  // +0x00
    void* mpEnd;                    // +0x04
    void* mpCap;                    // +0x08
    uint32 mAllocator[2];           // +0x0c
    void FUN_00a8c440();
};

// Description of the effect; only the offsets this slice touches are named.
struct cDistributeDescription {
    uint32 pad00[2];
    uint32 mFlags;                  // +0x08 (bits 7 and 8 force subdivision)
    uint32 pad0c;
    int    mEffectIndex;            // +0x10 (negative: unbound)
    uint32 pad14[3];
    float  mScale;                  // +0x20
    uint32 pad24[0x38];
    uint32 mSurfaceRecA;            // +0x104
    uint32 mSurfaceRecB;            // +0x108
    uint32 pad10c[3];
    uint32 mMapId0;                 // +0x118
    uint32 mMapId1;                 // +0x11c
    uint32 mMapId2;                 // +0x120
    uint32 mMapId3;                 // +0x124
    uint32 mMapId4;                 // +0x128
    uint32 mMapId5;                 // +0x12c
    Vector2 mAltitudeRange;         // +0x130
    uint32 mDrawIdA;                // +0x138
    uint32 mDrawIdB;                // +0x13c
    uint32 pad140[7];
    uint32 mField15c;               // +0x15c (message id)
};

struct cGlobalParams;

// World interface; GetGlobalParams sits at vtable offset 0x2c.
struct cIEffectsWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual cGlobalParams* GetGlobalParams();                   // +0x2c
};

// Effects manager; CreateMap sits at vtable offset 0x8c.
struct cIEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88();
    virtual cIMap* CreateMap(uint32 idA, uint32 idB);           // +0x8c
};

struct cDistributeEffect;

// Message passed to the effects-streamer when the sample buffers are dropped.
struct cClearSamplesMsg {
    int    mField00;                // +0x00
    uint32 mField04;                // +0x04
    int    mField08;                // +0x08
    uint32 mField0c;                // +0x0c
    cDistributeEffect* mpEffect;    // +0x10
    uint32 mField14;                // +0x14
    uint32 mIdA;                    // +0x18
    uint32 mIdB;                    // +0x1c
    uint32 mField190;               // +0x20
    uint32 mField24;                // +0x24
    uint32 mField194;               // +0x28
    uint32 mField2c;                // +0x2c
    uint32 mForce;                  // +0x30
    uint32 mField34;                // +0x34
    uint32 mField38;                // +0x38
};

// Messaging server; Send sits at vtable offset 0x14.
struct cMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void Send(uint32 id, cClearSamplesMsg* msg, int flags);   // +0x14
};

cMessageServer* GetMessageServer();                             // 0x00883860
void BuildSurfaceRecs(cIEffectsManager* mgr, uint32* rec, void* subObj, int* count, uint32* out, int flags);  // 0x00a7fc10

struct cDistributeEffect {
    volatile uint32 mVtblIComponent;    // +0x000 (cComponentBase cIComponent part; volatile pins the store order)
    volatile uint32 mVtblRefCount;      // +0x004 (RefCountTemplate<int> part)
    int    mRefCount;                   // +0x008
    volatile uint32 mVtblTextureStreamer;   // +0x00c (cITextureParticleStreamer)
    volatile uint32 mVtblModelStreamer;     // +0x010 (cIModelParticleStreamer)
    void*  mDesc;                       // +0x014 (cDistributeDescription*)
    int    mCollectionIndex;            // +0x018
    void*  mWorld;                      // +0x01c (cIEffectsWorld*)
    void*  mGlobalParams;               // +0x020 (cGlobalParams*)
    void*  mChildParams;                // +0x024
    volatile uint32 mFlags;             // +0x028 (volatile pins the read-modify-write flag updates)
    cTransform mSourceTransform;        // +0x02c
    cTransform mRigidTransform;         // +0x064
    int    mRenderCount;                // +0x09c
    Vector2 mParamAltitudeRange;        // +0x0a0
    SampleVector mRenderSamples;        // +0x0a8
    SampleVector mSamples;              // +0x0bc
    uint32 mSampleCount;                // +0x0d0
    uint32 mFieldD4;                    // +0x0d4
    cSubObjD mSubD;                     // +0x0d8
    uint32 mFieldEC;                    // +0x0ec
    uint32 mMapIdA;                     // +0x0f0
    uint32 mMapIdB;                     // +0x0f4
    uint8  mByteF8;                     // +0x0f8
    uint8  padF9[3];                    // +0x0f9
    uint32 mFieldFC;                    // +0x0fc
    Vector3 mSubdivOffset;              // +0x100
    Vector3 mSubdivScale;               // +0x10c
    void*  mSubdivOwner;                // +0x118
    cSubObjC mSubC;                     // +0x11c
    RawVector mVec130;                  // +0x130
    RawVector mVec144;                  // +0x144
    uint32 mField158;                   // +0x158
    cIMap* mEmitMap;                    // +0x15c
    cIMap* mColorMap;                   // +0x160
    cIMap* mPinMap;                     // +0x164
    int    mField168;                   // +0x168
    uint32 mField16c;                   // +0x16c
    float  mField170[8];                // +0x170 (all 1.0)
    uint32 mField190;                   // +0x190
    uint32 mField194;                   // +0x194
    uint32 mField198;                   // +0x198
    RawVector mVec19c;                  // +0x19c

    cDistributeEffect(void* desc, int index);                   // 0x00a8c850
    ~cDistributeEffect();
    void Init(cIEffectsWorld* world, cIEffectsManager* mgr, int unused);   // 0x00a8d090
    void ClearSamples(char force);                              // 0x00a8d350
};

// 0x00a8cb00 (thiscall, no arguments, plain `ret`).
cDistributeEffect::~cDistributeEffect()
{
    mVtblIComponent = 0x1458308;
    mVtblRefCount = 0x1458304;
    mVtblTextureStreamer = 0x1458300;
    mVtblModelStreamer = 0x14582fc;

    FreeBlock((void*)mVec19c.mpBegin);

    if (mPinMap)
        mPinMap->Release();
    if (mColorMap)
        mColorMap->Release();
    if (mEmitMap)
        mEmitMap->Release();

    FreeBlock((void*)mVec144.mpBegin);
    FreeBlock((void*)mVec130.mpBegin);

    mSubC.FUN_00a8c440();
    mSubD.FUN_00a89da0();

    FreeBlock((void*)mSamples.mpBegin);
    FreeBlock((void*)mRenderSamples.mpBegin);

    mVtblIComponent = 0x13f21d4;
    mVtblRefCount = 0x13ef094;
}

// Assigns a map reference counted interface pointer, AddRef'ing the new object before the old one
// is released. A resource id pair of all-ones means "not bound", so the slot is left alone.
static void AssignMapRef(cIMap*& slot, cIEffectsManager* mgr, uint32 idA, uint32 idB)
{
    if ((idA & idB) == 0xffffffff)
        return;
    cIMap* p = mgr->CreateMap(idA, idB);
    cIMap* old = slot;
    if (p == old)
        return;
    if (p)
        p->AddRef();
    slot = p;
    if (old)
        old->Release();
}

// @ 0x00a8c850
cDistributeEffect::cDistributeEffect(void* desc, int index)
{
    mVtblRefCount = 0x13ef094;
    mRefCount = 0;
    mVtblTextureStreamer = 0x140b5a0;
    mVtblModelStreamer = 0x140b5a0;
    mDesc = desc;
    mCollectionIndex = index;
    mVtblIComponent = 0x1458308;
    mVtblRefCount = 0x1458304;
    mVtblTextureStreamer = 0x1458300;
    mVtblModelStreamer = 0x14582fc;

    mWorld = 0;
    mGlobalParams = 0;
    mChildParams = 0;
    mFlags = 0;

    mSourceTransform.mFlags = 0;
    mSourceTransform.mModCount = 0;
    mSourceTransform.mOffset.x = kVector3Zero.x;
    mSourceTransform.mOffset.y = kVector3Zero.y;
    mSourceTransform.mOffset.z = kVector3Zero.z;
    mSourceTransform.mScale = kRealOne;
    mSourceTransform.mRotation.Assign(&kMatrix3Identity);

    mRigidTransform.mFlags = 0;
    mRigidTransform.mModCount = 0;
    mRigidTransform.mOffset.x = kVector3Zero.x;
    mRigidTransform.mOffset.y = kVector3Zero.y;
    mRigidTransform.mOffset.z = kVector3Zero.z;
    mRigidTransform.mScale = kRealOne;
    mRigidTransform.mRotation.Assign(&kMatrix3Identity);

    mRenderCount = 0;
    mParamAltitudeRange.x = kAltitudeMin;
    mRenderSamples.mpBegin = 0;
    mRenderSamples.mpEnd = 0;
    mRenderSamples.mpCapacity = 0;
    mParamAltitudeRange.y = kAltitudeMax;
    mSamples.mpBegin = 0;
    mSamples.mpEnd = 0;
    mSamples.mpCapacity = 0;
    mSampleCount = 0;
    mFieldD4 = 0;
    mSubD.mpBegin = 0;
    mSubD.mpEnd = 0;
    mSubD.mpCap = 0;
    mByteF8 = 0;
    mFieldEC = 0xffffffff;
    mMapIdA = 0xffffffff;
    mMapIdB = 0xffffffff;
    mSubdivOffset.x = kVector3Zero.x;
    mSubdivOffset.y = kVector3Zero.y;
    mSubdivOffset.z = kVector3Zero.z;
    mSubdivScale.x = kSubdivScaleInit.x;
    mSubdivScale.y = kSubdivScaleInit.y;
    mSubdivScale.z = kSubdivScaleInit.z;
    mSubdivOwner = 0;
    mSubC.mpBegin = 0;
    mSubC.mpEnd = 0;
    mSubC.mpCap = 0;
    mVec130.mpBegin = 0;
    mVec130.mpEnd = 0;
    mVec130.mpCapacity = 0;
    mVec144.mpBegin = 0;
    mVec144.mpEnd = 0;
    mVec144.mpCapacity = 0;
    mField158 = 0;
    mEmitMap = 0;
    mColorMap = 0;
    mPinMap = 0;
    mField168 = 0;
    float one = kRealOne;
    mField170[0] = one;
    mField170[1] = one;
    mField170[2] = one;
    mField170[3] = one;
    mField170[4] = one;
    mField170[5] = one;
    mField170[6] = one;
    mField170[7] = one;
    mField190 = 0;
    mField194 = 1;
    mVec19c.mpBegin = 0;
    mVec19c.mpEnd = 0;
    mVec19c.mpCapacity = 0;
}

// @ 0x00a8ce30
void SampleVector::insert(cDistributeSample* pos, const cDistributeSample& value)
{
    if (mpEnd != mpCapacity) {
        const cDistributeSample* pv = &value;
        if (pv >= pos && pv < mpEnd)
            ++pv;
        if (mpEnd)
            ::new ((void*)mpEnd) cDistributeSample(*(mpEnd - 1));
        MoveSamplesBack(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
        return;
    }

    int count = (int)(mpEnd - mpBegin);
    int newCap = (count == 0) ? 1 : count * 2;
    cDistributeSample* buf = 0;
    if (newCap != 0)
        buf = (cDistributeSample*)::operator new((unsigned)(newCap * 0x4c), kAllocatorName, 0, 0,
                                                kAllocatorFile, 0xd1);

    cDistributeSample* newPos = UninitCopySamples(mpBegin, pos, buf);
    if (newPos)
        ::new ((void*)newPos) cDistributeSample(value);
    cDistributeSample* newEnd = UninitCopySamples(pos, mpEnd, newPos + 1);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator_delete__(mpBegin);
    mpBegin = buf;
    mpEnd = newEnd;
    mpCapacity = (cDistributeSample*)((char*)buf + newCap * 0x4c);
}

// @ 0x00a8cfe0
void SampleVector::erase_all()
{
    cDistributeSample* first = mpBegin;
    cDistributeSample* last = mpEnd;
    CopySamples(last, last, first);
    mpEnd -= (last - first);
}

// @ 0x00a8d020
cEffectRef* EffectVector::erase(cEffectRef* first, cEffectRef* last)
{
    cEffectRef* newEnd = CopyEffectRefs(last, mpEnd, first);
    cEffectRef* end = mpEnd;
    for (cEffectRef* p = newEnd; p < end; ++p)
        p->~cEffectRef();
    mpEnd -= (last - first);
    return first;
}

// @ 0x00a8d090
void cDistributeEffect::Init(cIEffectsWorld* world, cIEffectsManager* mgr, int)
{
    mWorld = world;
    mGlobalParams = world->GetGlobalParams();

    mParamAltitudeRange = ((cDistributeDescription*)mDesc)->mAltitudeRange;
    float s = ((cDistributeDescription*)mDesc)->mScale;
    mSubdivScale = Vector3(s, s, s);

    uint32 idA = ((cDistributeDescription*)mDesc)->mMapId0;
    uint32 idB = ((cDistributeDescription*)mDesc)->mMapId1;
    AssignMapRef(mEmitMap, mgr, idA, idB);
    idA = ((cDistributeDescription*)mDesc)->mMapId2;
    idB = ((cDistributeDescription*)mDesc)->mMapId3;
    AssignMapRef(mColorMap, mgr, idA, idB);
    idA = ((cDistributeDescription*)mDesc)->mMapId4;
    idB = ((cDistributeDescription*)mDesc)->mMapId5;
    AssignMapRef(mPinMap, mgr, idA, idB);

    if (mEmitMap) {
        mEmitMap->Prepare();
        if (mEmitMap->IsEnabled())
            mFlags |= 0x80;
        else
            mFlags &= ~0x80u;
        mField168 = mEmitMap->GetValue();
    }
    if (mColorMap) {
        mColorMap->Prepare();
        if (mColorMap->IsEnabled())
            mFlags |= 0x100;
        else
            mFlags &= ~0x100u;
    }
    if (mPinMap) {
        mPinMap->Prepare();
        if (mPinMap->IsEnabled())
            mFlags |= 0x200;
        else
            mFlags &= ~0x200u;
    }

    if (((cDistributeDescription*)mDesc)->mSurfaceRecA !=
        ((cDistributeDescription*)mDesc)->mSurfaceRecB) {
        int count = 0;
        BuildSurfaceRecs(mgr, &((cDistributeDescription*)mDesc)->mSurfaceRecA, &mSubC, &count,
                         &mField158, 0);
        mVec130.resize(count);
    }

    mFlags |= 2;
    if (((cDistributeDescription*)mDesc)->mEffectIndex >= 0)
        mFlags |= 4;
    else
        mFlags &= ~4u;
    if (((cDistributeDescription*)mDesc)->mEffectIndex < 0 &&
        ((((cDistributeDescription*)mDesc)->mFlags >> 8) & 1 ||
         (((cDistributeDescription*)mDesc)->mFlags >> 7) & 1))
        mFlags |= 0x2000;
    else
        mFlags &= ~0x2000u;
}

// @ 0x00a8d350
void cDistributeEffect::ClearSamples(char force)
{
    if (((cDistributeDescription*)mDesc)->mField15c != 0 &&
        (mSamples.mpBegin != mSamples.mpEnd ||
         mRenderSamples.mpBegin != mRenderSamples.mpEnd)) {
        cMessageServer* server = GetMessageServer();
        if (server) {
            uint32 idA = mMapIdA;
            uint32 idB = mMapIdB;
            if ((idA & idB) == 0xffffffff) {
                idA = ((cDistributeDescription*)mDesc)->mDrawIdA;
                idB = ((cDistributeDescription*)mDesc)->mDrawIdB;
            }
            cClearSamplesMsg msg;
            msg.mField00 = 0;
            msg.mField08 = 0;
            msg.mpEffect = this;
            msg.mIdA = idA;
            msg.mIdB = idB;
            msg.mField190 = mField190;
            msg.mField194 = mField194;
            msg.mForce = (force != 0);
            msg.mField38 = 0;
            server->Send(((cDistributeDescription*)mDesc)->mField15c, &msg, 0);
        }
    }

    mSampleCount = 0;
    CopySamples(mSamples.mpEnd, mSamples.mpEnd, mSamples.mpBegin);
    mSamples.mpEnd -= (mSamples.mpEnd - mSamples.mpBegin);
}
