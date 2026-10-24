// Slice s00dc7eb0: SP::cCulturalConvertCityOrder::OnTick (0x00dc7eb0).
// Civ-stage culture vehicles converting a city: pick the vehicle closest to the
// cultural target, spawn a hologram creature + visual effect over it, and keep
// the hologram/effect following the converting vehicles.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <intrin.h>

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

#define PV(n) virtual void pad##n();

struct Vector3 {
    float x, y, z;

    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    Vector3 Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-8f);
        return Vector3(x * inv, y * inv, z * inv);
    }
};
struct Quaternion {
    float x, y, z, w;
};
struct Matrix3 {
    float m[9];
};
struct BoundingBox {
    Vector3 lower;
    Vector3 upper;
};

// Transform (flags, change count, offset, scale, rotation): 0x38 bytes
struct Transform {
    uint16_t mFlags;
    uint16_t mnChanges;
    Vector3  mOffset;
    float    mScale;
    Matrix3  mRotation;

    Transform();                                     // 0x00434040
    void Reset();                                    // 0x00832dc0

    void SetOffset(const Vector3& v)
    {
        mOffset = v;
        mFlags |= 4;
        mnChanges++;
    }
    void SetRotation(const Matrix3& m)
    {
        mRotation = m;
        mFlags |= 2;
        mnChanges++;
    }
};

Vector3 normalized_safe(const Vector3& v);                           // 0x00449c20
Matrix3 Matrix3FromQuaternion(const Quaternion& q);                  // 0x0059c190
Vector3 QuaternionVectorTransform(const Quaternion& q, const Vector3& v);   // 0x0099c1a0

struct cSpatialObject {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13)
    virtual bool Vf50();                                           // +0x50
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a)
    virtual BoundingBox GetBoundingBox();                          // +0x6c
    PV(1c) PV(1d) PV(1e) PV(1f)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d)
    virtual void* IsType(uint32_t typeID);                         // +0xb8
};

struct cCity {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
    uint32_t pad4[0x16c / 4];
    uint32_t mFlags;                                               // +0x170
};

struct cGameDataObj {
    PV(00) PV(01) PV(02)
    virtual void* Cast(uint32_t typeID);                           // +0x0c
};

struct cCulturalTarget {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    virtual cGameDataObj* GetOwner();                              // +0x30
    uint32_t pad4[0xfc / 4];
    cSpatialObject mSpatial;                                       // +0x100

    void StopConversion(uint32_t arg);                             // 0x00be3230
};

struct cPoliticalSub {                                             // cVehicle +0x508
    PV(00) PV(01) PV(02) PV(03)
    virtual uint32_t GetPoliticalID();                             // +0x10
    float GetRange();                                              // 0x00bfc400
};

struct cVehicle {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    uint32_t pad4[0x30 / 4];
    cSpatialObject mSpatial;                                       // +0x34
    uint32_t pad38[(0x508 - 0x38) / 4];
    cPoliticalSub mPolitical;                                      // +0x508

    cSpatialObject* GetTarget();                                   // 0x00c9fee0
};

struct cVehicleRef {                                               // EA::AutoRefCount<cVehicle>
    cVehicle* mpObject;
    cVehicleRef& operator=(cVehicle* p);                           // 0x00b5f950
    void Fdc4c60();                                                // 0x00dc4c60
};

struct cAnimModel {
    uint32_t pad0[0x18 / 4];
    Vector3 mPosition;                                             // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    Quaternion mOrientation;                                       // +0x3c
    uint32_t pad4c[(0x2e4 - 0x4c) / 4];
    char* mpRig;                                                   // +0x2e4 (Vector3 at +0x10)
};

struct cAnimatingCreature {
    virtual void v0();
    virtual void PlayAnimation(uint32_t id, int a);                // +0x04
    virtual uint32_t LoadAnimation(uint32_t id, int a);            // +0x08
    virtual void SetAnimation(uint32_t anim, int a);               // +0x0c
    PV(04) PV(05)
    virtual void Vf18(uint32_t anim);                              // +0x18
    Vector3 mPosition;                                             // +0x04
    Quaternion mOrientation;                                       // +0x10
    uint32_t pad20[(0x3c - 0x20) / 4];
    float mf3c;                                                    // +0x3c
    uint32_t pad40[(0x74 - 0x40) / 4];
    float mColor[4];                                               // +0x74
    bool mb84;                                                     // +0x84
    uint32_t pad88[(0x170 - 0x88) / 4];
    uint32_t mf170;                                                // +0x170
    uint32_t pad174[2];
    cAnimModel* mpModel;                                           // +0x17c
    uint32_t pad180;
    uint32_t mf184;                                                // +0x184

    void AddRef();                                                 // 0x00a02c30
    void Release();                                                // 0x00a05270
    float GetAnimProgress(uint32_t anim);                          // 0x00a049f0
    void Fa04c80(int n);                                           // 0x00a04c80
};

struct IVisualEffect {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    virtual void Start(int flags);                                 // +0x08
    PV(03) PV(04) PV(05)
    virtual void SetTransform(const Transform& xf);                // +0x18
    PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10)
    virtual void SetParams(int id, const void* data, int count);   // +0x44
};

struct IEffectsManager {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect*& dst);   // +0x2c
};
IEffectsManager* EffectsManager();                                 // 0x0067ddd0

struct cCreatureFactory {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    virtual cAnimatingCreature* CreateCreature(void* desc);        // +0x30
};
struct cFactoryOwner {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    PV(18) PV(19) PV(1a) PV(1b) PV(1c)
    virtual cCreatureFactory* GetFactory();                        // +0x74
};
cFactoryOwner* FUN_00b3d240();                                     // 0x00b3d240

struct cEmpire {
    uint32_t pad0[0x40 / 4];
    uint32_t mf40;                                                 // +0x40
    uint32_t pad44[(0x88 - 0x44) / 4];
    uint8_t  pad88;
    bool     mb89;                                                 // +0x89
    char* GetCreatureDesc(int a, void* b, void* c, int d);         // 0x00bef950
};
struct cNounManager {
    cEmpire* GetEmpire(uint32_t politicalID);                      // 0x00b25f40
};
cNounManager* NounManager();                                       // 0x00b3d300

struct cPlanetModel {
    Quaternion BuildSurfaceOrientation(const Vector3& pos, const Vector3& dir);   // 0x00b7f250
    Quaternion BuildSurfaceOrientation(const Vector3& pos);                       // 0x00b7f190
};
cPlanetModel* PlanetModel();                                       // 0x00b3d350

extern char g_169fa68;                                             // 0x0169fa68
extern char g_15a2674;                                             // 0x015a2674
const Vector3* FUN_00b6f0c0(uint32_t id);                          // 0x00b6f0c0 (empire color)
void* FUN_009ff6f0(uint32_t a, uint32_t anim);                     // 0x009ff6f0

struct cVehicleVector {                                            // eastl::vector<AutoRefCount<cVehicle>>
    cVehicle** mpBegin;
    cVehicle** mpEnd;
    cVehicle** mpCapacity;
    uint32_t   mAllocator[2];
    bool empty() const { return mpBegin == mpEnd; }
    cVehicle** begin() { return mpBegin; }
    cVehicle** end() { return mpEnd; }
};
bool ContainsVehicle(cVehicleVector* v, cVehicleRef* p);                       // 0x00bda6a0
cVehicle* FindClosestVehicle(cVehicleVector* v, const Vector3* pos);           // 0x00dc7780

template <class T> static inline void ResetRef(T*& p)
{
    T* pTemp = p;
    p = 0;
    if (pTemp)
        pTemp->Release();
}

template <class T> static inline void ClearRef(T*& p)
{
    // intrusive_ptr = NULL
    T* const pTemp = p;
    if (pTemp) {
        p = 0;
        pTemp->Release();
    }
}

namespace SP {

class cCulturalConvertCityOrder {
public:
    uint32_t pad0[0x50 / 4];
    cVehicleVector mActiveVehicles;                                // +0x50
    cVehicleRef m64;                                               // +0x64
    uint32_t pad68[(0x78 - 0x68) / 4];
    uint32_t m78;                                                  // +0x78
    uint32_t pad7c[(0x94 - 0x7c) / 4];
    cCulturalTarget* mpCulturalTarget;                             // +0x94
    uint32_t mAttackerId;                                          // +0x98
    cAnimatingCreature* mpHologram;                                // +0x9c
    cVehicleRef mpHoloVehicle;                                     // +0xa0
    IVisualEffect* mpHoloEffect;                                   // +0xa4
    uint32_t mHoloAnim;                                            // +0xa8
    bool mbHoloAnimPending;                                        // +0xac

    void Fdc6530();                                                // 0x00dc6530
    void Fdc65b0();                                                // 0x00dc65b0
    bool OnTick(float deltaTime);
};

// @ 0x00dc7eb0
bool cCulturalConvertCityOrder::OnTick(float deltaTime)
{
    if (!mpCulturalTarget || mpCulturalTarget->IsDestroyed())
        return false;

    if (mbHoloAnimPending && mpHologram) {
        if (mpHologram->GetAnimProgress(mHoloAnim) >= 1.0f) {
            Fdc6530();
            mbHoloAnimPending = false;
        }
    }

    if (mActiveVehicles.empty()) {
        if (mpHologram) {
            if (!mbHoloAnimPending) {
                Fdc65b0();
                m64.Fdc4c60();
                if (mpCulturalTarget && !mpCulturalTarget->IsDestroyed())
                    mpCulturalTarget->StopConversion(m78);
                ClearRef(mpCulturalTarget);
            }
            return true;
        }
        return false;
    }

    cCity* city = 0;
    cGameDataObj* owner = mpCulturalTarget->GetOwner();
    if (owner)
        city = (cCity*)owner->Cast(0xee9b2232);
    uint32_t attackerId = mAttackerId;
    bool bConverted = attackerId == city->GetPoliticalID();

    if (NounManager()->GetEmpire(attackerId)->mb89) {
        for (cVehicle** it = mActiveVehicles.begin(), **itEnd = mActiveVehicles.end(); it != itEnd; ++it) {
            if ((*it)->mSpatial.Vf50()) {
                city->mFlags |= 0x800;
                break;
            }
        }
    }

    if (!mpHologram) {
        float fBestDist = 3.402823466e+38f;
        cVehicle* pBest = 0;
        for (cVehicle** it = mActiveVehicles.begin(), **itEnd = mActiveVehicles.end(); it != itEnd; ++it) {
            cVehicle* pVehicle = *it;
            cSpatialObject* pTarget = pVehicle->GetTarget();
            if (pTarget && pTarget->IsType(0x3d5c477)) {
                const Vector3& tp = pVehicle->GetTarget()->GetPosition();
                float fDist = (pVehicle->mSpatial.GetPosition() - tp).Length();
                if (fDist < fBestDist) {
                    fBestDist = fDist;
                    pBest = pVehicle;
                }
            }
        }
        if (pBest && fBestDist < pBest->mPolitical.GetRange()) {
            cCreatureFactory* factory = FUN_00b3d240()->GetFactory();
            cEmpire* empire = NounManager()->GetEmpire(pBest->mPolitical.GetPoliticalID());
            cAnimatingCreature* pHolo = factory->CreateCreature(empire->GetCreatureDesc(2, &g_169fa68, &g_15a2674, 1) + 0x504);
            cAnimatingCreature* pOld = mpHologram;
            if (pHolo != pOld) {
                if (pHolo)
                    pHolo->AddRef();
                mpHologram = pHolo;
                if (pOld)
                    pOld->Release();
            }
            mpHologram->Fa04c80(6);
            mpHologram->mf170 = 0x52594c50;
            if (mpHologram) {
                Vector3 pos(pBest->mSpatial.GetPosition());
                pos += pos.Normalized() * 15.0f;
                mpHologram->mPosition = pos;

                if (pBest->GetTarget()) {
                    const Vector3& tp = pBest->GetTarget()->GetPosition();
                    cAnimatingCreature* holo = mpHologram;
                    holo->mOrientation = PlanetModel()->BuildSurfaceOrientation(pos, normalized_safe(pos - tp));
                } else {
                    cAnimatingCreature* holo = mpHologram;
                    holo->mOrientation = PlanetModel()->BuildSurfaceOrientation(-holo->mPosition);
                }

                mpHologram->mf3c = 1.0f;
                Vector3 color(*FUN_00b6f0c0(empire->mf40));
                mpHologram->mColor[0] = color.x;
                mpHologram->mColor[1] = color.y;
                mpHologram->mColor[2] = color.z;
                mpHologram->mColor[3] = 1.0f;
                mpHologram->mb84 = false;
                mHoloAnim = mpHologram->LoadAnimation(0x8bff672a, 0);
                mpHologram->SetAnimation(mHoloAnim, 1);
                mpHologram->Vf18(mHoloAnim);
                mpHologram->PlayAnimation(0x564fb23, 0);
                mpHoloVehicle = pBest;

                IEffectsManager* em = EffectsManager();
                ClearRef(mpHoloEffect);
                if (em->CreateVisualEffect(0xc2670644, 0, mpHoloEffect)) {
                    Transform xf;
                    xf.Reset();
                    xf.SetOffset(mpHoloVehicle.mpObject->mSpatial.GetPosition());
                    mpHoloEffect->SetTransform(xf);
                    mpHoloEffect->SetParams(5, &color, 3);
                    mpHoloEffect->Start(0);
                }
            }
        }
    } else if (mpHoloVehicle.mpObject) {
        if (!ContainsVehicle(&mActiveVehicles, &mpHoloVehicle)) {
            ResetRef(mpHoloVehicle.mpObject);
            if (!mActiveVehicles.empty()) {
                Vector3 holoPos(mpHologram->mPosition);
                mpHoloVehicle = FindClosestVehicle(&mActiveVehicles, &holoPos);
                const Vector3& tp = mpCulturalTarget->mSpatial.GetPosition();
                const Vector3& vp = mpHoloVehicle.mpObject->mSpatial.GetPosition();
                float dx = vp.x - tp.x;
                float dy = vp.y - tp.y;
                float dz = vp.z - tp.z;
                float fDist = (float)sqrt(dx * dx + dy * dy + dz * dz);
                if (fDist > mpHoloVehicle.mpObject->mPolitical.GetRange()) {
                    mpHoloVehicle.Fdc4c60();
                    Fdc65b0();
                }
            }
        }

        if (mpHoloVehicle.mpObject) {
            if (mHoloAnim) {
                char* anim = (char*)FUN_009ff6f0(mpHologram->mf184, mHoloAnim);
                if (anim && *(uint32_t*)(anim + 0xc0))
                    mpHologram->mf3c = 20.0f;
            }

            if (mpHoloEffect && mpHoloVehicle.mpObject) {
                Transform xf;
                xf.Reset();
                const BoundingBox& bbox = mpHoloVehicle.mpObject->mSpatial.GetBoundingBox();
                Vector3 center((bbox.lower + bbox.upper) * 0.5f);
                xf.SetOffset(center);
                xf.SetRotation(Matrix3FromQuaternion(mpHologram->mOrientation));
                mpHoloEffect->SetTransform(xf);

                Vector3 points[11];
                points[0] = center;
                cAnimModel* model = mpHologram->mpModel;
                Vector3 dir = QuaternionVectorTransform(model->mOrientation, *(Vector3*)(model->mpRig + 0x10)) + model->mPosition - center;
                float len = dir.Length();
                Vector3 step = dir * (1.0f / len) * (len * 0.1f);
                for (int i = 1; i < 11; i++) {
                    points[i].x = step.x + points[i - 1].x;
                    points[i].y = step.y + points[i - 1].y;
                    points[i].z = step.z + points[i - 1].z;
                }
                mpHoloEffect->SetParams(0xd, points, 0x21);
            }
        }
    }
    return !bConverted;
}

}  // namespace SP

// ---------------------------------------------------------------------------------------
// Copy constructor for an EASTL-style hash container (bucket array of linked lists):
// 0x00dc8a60.  The node payload is 0x20 bytes (one integer followed by seven floats),
// the chain pointer sits at +0x20.  The bucket array has mBucketCount entries plus a
// 0xffffffff terminator.
struct CultureHashPayload {
    uint32_t mField00;              // +0x00
    float mField04;                 // +0x04
    float mField08;                 // +0x08
    float mField0c;                 // +0x0c
    float mField10;                 // +0x10
    float mField14;                 // +0x14
    float mField18;                 // +0x18
    float mField1c;                 // +0x1c

    CultureHashPayload& operator=(const CultureHashPayload& src)
    {
        mField04 = src.mField04;
        mField00 = src.mField00;
        mField08 = src.mField08;
        mField0c = src.mField0c;
        mField10 = src.mField10;
        mField14 = src.mField14;
        mField18 = src.mField18;
        mField1c = src.mField1c;
        return *this;
    }
};

struct CultureHashNode {
    CultureHashPayload mPayload;    // +0x00
    CultureHashNode* mpNext;        // +0x20
};

struct CultureHashTail {
    uint32_t a, b, c;               // +0x00..+0x0b
};

struct CultureHash {
    uint32_t mField00;              // +0x00
    CultureHashNode** mBuckets;     // +0x04
    uint32_t mBucketCount;          // +0x08
    uint32_t mElementCount;         // +0x0c
    CultureHashTail mTail;          // +0x10..+0x1b

    CultureHash(const CultureHash& src);
    void Swap(CultureHash& other);
};

extern "C" void* __cdecl FUN_00f473a0(uint32_t size, const char* name, uint32_t flags,
                                      uint32_t align, void* allocator, uint32_t line);
extern "C" void* __cdecl memset(void*, int, unsigned int);

// @ 0x00dc8a60
CultureHash::CultureHash(const CultureHash& src)
{
    mField00 = src.mField00;
    mBucketCount = src.mBucketCount;
    mElementCount = src.mElementCount;
    mTail.a = src.mTail.a;
    mTail.b = src.mTail.b;
    mTail.c = src.mTail.c;

    if (mElementCount != 0) {
        uint32_t count = mBucketCount;
        uint32_t byteSize = count * 4;
        CultureHashNode** buckets = (CultureHashNode**)FUN_00f473a0(
            byteSize + 4, (const char*)0x13f09b4, 0, 0, (void*)0x13ebb38, 0xd1);
        memset(buckets, 0, byteSize);
        buckets[count] = (CultureHashNode*)0xffffffff;
        mBuckets = buckets;

        uint32_t i = 0;
        if (src.mBucketCount > 0) {
            do {
                CultureHashNode* srcNode = src.mBuckets[i];
                CultureHashNode** dstSlot = &mBuckets[i];
                while (srcNode) {
                    CultureHashNode* newNode = (CultureHashNode*)FUN_00f473a0(
                        sizeof(CultureHashNode), (const char*)0x13f09b4, 0, 0,
                        (void*)0x13ebb38, 0xd1);
                    if (newNode) {
                        newNode->mPayload = srcNode->mPayload;
                    }
                    newNode->mpNext = 0;
                    *dstSlot = newNode;
                    srcNode = srcNode->mpNext;
                    dstSlot = &newNode->mpNext;
                }
                ++i;
            } while (i < src.mBucketCount);
        }
    } else {
        mBucketCount = 1;
        mBuckets = (CultureHashNode**)0x154df28;
        mElementCount = 0;
        mTail.c = 0;
    }
}

// @ 0x00dc8ba0
void CultureHash::Swap(CultureHash& other)
{
    CultureHashTail t = mTail;
    mTail = other.mTail;
    other.mTail = t;
    _ReadWriteBarrier();

    CultureHashNode** bp = mBuckets;
    mBuckets = other.mBuckets;
    other.mBuckets = bp;
    _ReadWriteBarrier();

    uint32_t bc = mBucketCount;
    mBucketCount = other.mBucketCount;
    other.mBucketCount = bc;
    _ReadWriteBarrier();

    uint32_t ec = mElementCount;
    mElementCount = other.mElementCount;
    other.mElementCount = ec;
}

// ---------------------------------------------------------------------------------------
// 0x00dc8c00: intrusive-pointer protected map lookup.  The map lives at this+0x34; the
// key passed to the tree is the pointer with its low byte cleared (tag bits removed).
struct DecalMapTree {
    uint32_t mPad[0x1c / 4];
    void Find(void* out, const void* key, uint32_t hash);
};

struct Removable {
    virtual void AddRef();
    virtual void Release();
};

union TaggedPtr {
    uint32_t mValue;                // +0x00
    Removable* mPtr;                // +0x00
    struct {
        uint8_t mTag;               // +0x00
        uint8_t mRest[3];           // +0x01
    } mBytes;
};

struct DecalRemover {
    uint32_t mPad[0x34 / 4];        // +0x00..0x33
    DecalMapTree mMap;              // +0x34
    void Remove(Removable* p);
};

struct RemoveLocals {
    Removable* key;                 // +0x00
    uint32_t it[2];                 // +0x04
};

// @ 0x00dc8c00
void DecalRemover::Remove(Removable* p)
{
    RemoveLocals locals;
    locals.key = p;
    if (p)
        p->AddRef();
    TaggedPtr key;
    key.mBytes.mTag = 0;
    mMap.Find(locals.it, &locals.key, key.mValue);
    if (p)
        p->Release();
}

// ---------------------------------------------------------------------------------------
// 0x00dc8c50: remove a decal owner from the +0x50 pointer vector and notify every
// 0x178-byte entry in the +0x7c vector.
struct RemoveArg : Removable {
    uint32_t mPad04[(0x34 - 0x04) / 4]; // +0x04..0x33
    uint32_t mField34;                  // +0x34
    void Method(int);                   // 0x00ca0000
};

struct DecalEntry {
    uint8_t mData[0x178];
    void RemoveDecal(void* arg);        // 0x00afedf0
};

struct DecalManager {
    virtual void pad00();
    virtual void pad04();
    virtual void pad08();
    virtual void pad0c();
    virtual void pad10();
    virtual void pad14();
    virtual void pad18();
    virtual void pad1c();
    virtual void pad20();
    virtual void pad24();
    virtual void pad28();
    virtual bool Skip();                // +0x2c
    uint32_t mPad04[(0x50 - 0x04) / 4]; // +0x04..0x4f
    Removable** mVec50Begin;            // +0x50
    Removable** mVec50End;              // +0x54
    uint32_t mPad58[(0x7c - 0x58) / 4]; // +0x58..0x7b
    DecalEntry* mDecalBegin;            // +0x7c
    DecalEntry* mDecalEnd;              // +0x80
    void Remove(RemoveArg* arg);
};

extern "C" void __cdecl CopyImpl_do_copy(void* src, void* end, void* dst);

// @ 0x00dc8c50
void DecalManager::Remove(RemoveArg* arg)
{
    arg->Method(0);
    if (!Skip()) {
        Removable** it = mVec50Begin;
        while (it != mVec50End && *it != arg)
            ++it;
        if (it != mVec50End) {
            if (it + 1 < mVec50End)
                CopyImpl_do_copy(it + 1, mVec50End, it);
            --mVec50End;
            Removable* last = *mVec50End;
            if (last)
                last->Release();
        }

        int count = (int)(mDecalEnd - mDecalBegin);
        if (count > 0) {
            uint32_t off = 0;
            int n = count;
            do {
                DecalEntry* e = (DecalEntry*)((uint8_t*)mDecalBegin + off);
                void* target = arg ? (void*)&arg->mField34 : 0;
                e->RemoveDecal(target);
                off += 0x178;
                --n;
            } while (n != 0);
        }
    }
}
