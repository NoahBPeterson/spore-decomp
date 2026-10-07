// Slice s0059b4b0 -- SP::cSPEditorAnimatedCreatureData / manager helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc, same region as s0059c4c0).
#include "types.h"
#include <math.h>
#include <intrin.h>

typedef unsigned int size_t;

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) { return p; }

// ---------------------------------------------------------------------------
// EA refcounting
// ---------------------------------------------------------------------------
namespace EA {

template <typename T>
class RefCountTemplate {
public:
    RefCountTemplate() : mnRefCount(0) {}
    virtual ~RefCountTemplate() {}
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
protected:
    T mnRefCount;   // +0x4
};

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        T* const pOld = mpObject;
        if (p != pOld) {
            if (p) p->AddRef();
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    void Reset()
    {
        if (mpObject) { T* const pTemp = mpObject; mpObject = 0; pTemp->Release(); }
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef() { return _InterlockedIncrement((volatile long*)&mnRefCount); }
    virtual int Release()
    {
        int n = _InterlockedDecrement((volatile long*)&mnRefCount);
        if (n == 0) {
            _InterlockedExchange((volatile long*)&mnRefCount, 1);
            delete this;
        }
        return n;
    }
protected:
    T mnRefCount;   // +0x4
};

}  // namespace EA

// ---------------------------------------------------------------------------
// eastl::rbtree used for eastl::map<unsigned int, AutoRefCount<...> >
// ---------------------------------------------------------------------------
namespace eastl {

template <typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;    // +0x0
    rbtree_node_base* mpNodeLeft;     // +0x4
    rbtree_node_base* mpNodeParent;   // +0x8
    char              mColor;         // +0xc
};

template <typename K, typename V>
struct rbtree_node : public rbtree_node_base {
    pair<K, V> mValue;                // +0x10
};

template <typename K, typename V>
struct rbtree_iterator {
    rbtree_node<K, V>* mpNode;
    rbtree_iterator() : mpNode(0) {}
    explicit rbtree_iterator(rbtree_node<K, V>* p) : mpNode(p) {}
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
    rbtree_iterator& operator++() { mpNode = (rbtree_node<K, V>*)RBTreeIncrement(mpNode); return *this; }
    bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
    K& operator*() const { return mpNode->mValue.first; }
};

}  // namespace eastl

extern "C++" void RBTreeInsert(eastl::rbtree_node_base* pNode, eastl::rbtree_node_base* pNodeParent,
                               eastl::rbtree_node_base* pNodeAnchor, int insertionSide);  // 0x009216a0
eastl::rbtree_node_base* RBTreeIncrement(const eastl::rbtree_node_base* pNode);       // 0x00921580
void RBTreeErase(eastl::rbtree_node_base* pNode, eastl::rbtree_node_base* pNodeAnchor);  // 0x00921880
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                               const char* file, int line);                            // 0x00f473a0
void EASTL_allocator_deallocate(void* p);                                              // 0x00f47380

namespace eastl {

template <typename K, typename V>
class rbtree {
public:
    typedef rbtree_node<K, V> node_type;
    typedef rbtree_iterator<K, V> iterator;
    typedef pair<K, V> value_type;

    int mCompare;               // +0x0 (empty less<K>)
    rbtree_node_base mAnchor;   // +0x4
    unsigned int mnSize;        // +0x14
    const char* mAllocator;     // +0x18

    iterator end() { return iterator((node_type*)&mAnchor); }

    node_type* DoCreateNode(const value_type& value)
    {
        node_type* const pNode = (node_type*)EASTL_allocator_allocate(
            sizeof(node_type), "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        ::new (&pNode->mValue) value_type(value);
        return pNode;
    }
    void DoFreeNode(node_type* pNode)
    {
        pNode->mValue.~value_type();
        EASTL_allocator_deallocate(pNode);
    }

    iterator DoInsertValueImpl(rbtree_node_base* pNodeParent, const value_type& value, bool bForceToLeft)
    {
        int side;
        if (bForceToLeft || (pNodeParent == &mAnchor) ||
            (value.first < ((node_type*)pNodeParent)->mValue.first))
            side = 0;
        else
            side = 1;
        node_type* const pNodeNew = DoCreateNode(value);
        RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
        mnSize++;
        return iterator(pNodeNew);
    }

    iterator erase(iterator position)
    {
        const iterator iErase(position);
        --mnSize;
        ++position;
        RBTreeErase(iErase.mpNode, &mAnchor);
        DoFreeNode(iErase.mpNode);
        return position;
    }
};

}  // namespace eastl

// ---------------------------------------------------------------------------
// SP types
// ---------------------------------------------------------------------------
namespace SP {

class cSPEditorAnimatedCreatureData;

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { return (float)fabs(x); }

// Clamp: the original uses the SSE max/min asm helper (maxss/minss on memory operands).
inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
    cSPVector3 operator-(const cSPVector3& o) const { return cSPVector3(x - o.x, y - o.y, z - o.z); }
    cSPVector3 operator+(const cSPVector3& o) const { return cSPVector3(x + o.x, y + o.y, z + o.z); }
    cSPVector3 operator*(float s) const { return cSPVector3(x * s, y * s, z * s); }
    cSPVector3 operator-() const { return cSPVector3(-x, -y, -z); }
    bool operator!=(const cSPVector3& o) const { return x != o.x || y != o.y || z != o.z; }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    __forceinline cSPVector3 Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + (y * y + z * z));
        return cSPVector3(x * inv, y * inv, z * inv);
    }
    __forceinline cSPVector3 Normalize() const
    {
        float ax = x, ay = y, az = z;
        float inv = 1.0f / (float)sqrt(ax * ax + ay * ay + az * az);
        return cSPVector3(ax * inv, ay * inv, az * inv);
    }
    cSPVector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};

struct cSPQuaternion {
    float x, y, z, w;
    cSPQuaternion() {}
    cSPQuaternion(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};

struct cSPMatrix3 {
    cSPVector3 mRow[3];
};

// row vector times matrix (inlined in the original)
inline cSPVector3 operator*(const cSPVector3& v, const cSPMatrix3& m)
{
    return cSPVector3(m.mRow[0].x * v.x + m.mRow[1].x * v.y + m.mRow[2].x * v.z,
                      m.mRow[0].y * v.x + m.mRow[1].y * v.y + m.mRow[2].y * v.z,
                      m.mRow[0].z * v.x + m.mRow[1].z * v.y + m.mRow[2].z * v.z);
}

inline cSPQuaternion QuaternionFromAxisAngle(const cSPVector3& axis, float angle)
{
    float half = angle * 0.5f;
    float s = sinf(half);
    float c = cosf(half);
    return cSPQuaternion(axis.x * s, axis.y * s, axis.z * s, c);
}

struct cAnimInfo {
    char pad00[0x1d];
    bool mbNoOrientation;   // +0x1d
};

class cAnimManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual cAnimInfo* GetAnimInfo(uint32_t animID);   // +0x40
};

struct cCreatureAnimData {
    char pad000[0x2d4];
    bool mbOrientIdle;      // +0x2d4
};

class cAnimatingCreature {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual int GetCurrentAnimation(uint32_t* dstAnimID, float* dstTime, int* p3, int* dstAnimIndex);  // +0x58
    virtual bool GetAnimationProgress(int animIndex, float* pLength, float* pTime);                    // +0x5c

    bool IsOrientStartAnim(uint32_t animID);   // 0x00a02710
    bool IsOrientIdleAnim(uint32_t animID);    // 0x00a027a0
    void AddRef();                             // 0x00a02c30
    void Release();                            // 0x00a05270

    cSPVector3 mPosition;                      // +0x04
    cSPQuaternion mOrientation;                // +0x10
    char pad20[0x164 - 0x20];
    cSPVector3 mLookAtPosition;                // +0x164
    char pad170[0x17c - 0x170];
    cCreatureAnimData* mpAnimData;             // +0x17c
};

struct FilterSettings {
    unsigned __int64 requiredGroupFlags;   // +0x00
    unsigned __int64 excludedGroupFlags;   // +0x08
    void* filterFunction;                  // +0x10
    uint8_t collisionMode;                 // +0x14
    uint8_t flags;                         // +0x15
    FilterSettings() : requiredGroupFlags(), excludedGroupFlags(), filterFunction(0), collisionMode(4), flags(0) {}
    void SetRequiredGroup(uint32_t group)
    {
        if (group < 64)
            ((uint32_t*)&requiredGroupFlags)[group >> 5] |= 1 << (group & 31);
    }
};

class cIModelManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09();
    virtual uint32_t GetGroupFlag(uint32_t groupID, int a);   // +0x28
};

class cIModelWorld {
public:
    virtual void AddRef();     // +0x0
    virtual void Release();    // +0x4
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual void* FindFirstModelAlongLine(const cSPVector3& p1, const cSPVector3& p2, float* factorDst,
                                          cSPVector3* dstPoint, cSPVector3* dstNormal,
                                          FilterSettings& settings, int* a, int* b);   // +0x24
};

class cISPCreatureAnimWorld {
public:
    virtual void AddRef();     // +0x00
    virtual void Release();    // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void SetWorld(cIModelWorld* world, int a, int b, int c, int d);   // slot +0x1c
};

class cSPEditorAnimationManager : public EA::RefCountTemplate<int> {
public:
    cSPEditorAnimationManager();   // 0x0059dac0 (out of line)
    void Init();                   // 0x0059db40
    char pad_8[0x20 - 0x8];
};

class cSPEditorAnimatedEventInfo {
public:
    virtual ~cSPEditorAnimatedEventInfo() {}
    int AddRef() { return _InterlockedIncrement((volatile long*)&mnRefCount); }
    int Release()
    {
        int n = _InterlockedDecrement((volatile long*)&mnRefCount);
        if (n == 0) {
            _InterlockedExchange((volatile long*)&mnRefCount, 1);
            delete this;
        }
        return n;
    }
private:
    int mnRefCount;              // +0x4
    char pad_8[0x30 - 0x8];
};

class cSPEditorAnimatedCreatureData : public EA::RefCountTemplate<int> {
public:
    void Update(unsigned int milliseconds);                    // 0x0059b4b0
    void RefreshTargetPosition();                              // 0x0059b390
    EA::AutoRefCount<cAnimatingCreature> mAnimatingCreature;   // +0x8
    cIModelWorld* mModelWorld;                                 // +0xc
    uint32_t mKeyToUnregister[3];                              // +0x10
    unsigned int mLastAnimationPlayed;                         // +0x1c
    cSPVector3 mRawTargetPosition;                             // +0x20
    cSPVector3 mTargetPosition;                                // +0x2c
    cSPVector3 mActualPosition;                                // +0x38
    float mTargetAngle;                                        // +0x44
    float mActualAngle;                                        // +0x48
    float mMovementSpeed;                                      // +0x4c
    float mRotationSpeed;                                      // +0x50
    bool mPreserveHeight;                                      // +0x54
    bool mLookAtTarget;                                        // +0x55
    cSPVector3 mTargetLookAtPosition;                          // +0x58
    cSPVector3 mActualLookAtPosition;                          // +0x64
    bool mAnimInterruptible;                                   // +0x70
    float mHeightOffset;                                       // +0x74
    float mHeightOffsetTarget;                                 // +0x78
    float mHeightDropWaitTime;                                 // +0x7c
    float mHeightDropSpeed;                                    // +0x80
    bool mIsTurning;                                           // +0x84
};

class cSPEditorAnimatedCreatureManager : public EA::RefCountTemplate<int> {
public:
    void Init(cIModelWorld* pModelWorld, bool flag);

    // rbtree members laid out from +0x8..+0x24, vector +0x24..+0x38
    char pad_08[0x38 - 0x8];
    EA::AutoRefCount<cISPCreatureAnimWorld>     mAnimWorld;     // +0x38
    EA::AutoRefCount<cSPEditorAnimationManager> mAnimManager;   // +0x3c
    EA::AutoRefCount<cIModelWorld>              mModelWorld;    // +0x40
    unsigned int                                mCurrentID;     // +0x44
};

}  // namespace SP

using namespace SP;

// property / app manager accessor
void* FUN_0067cb20();   // 0x0067cb20

// ===========================================================================
// @ 0x0059c010
float* MinFloatPtr(float* p1, float* p2)
{
    return (*p1 > *p2) ? p2 : p1;
}

// ===========================================================================
// @ 0x0059c030
extern float kPi59;      // 0x013f64d4
extern float kTwoPi59;   // 0x0150dff4
float WrapAngleToPi(float angle)
{
    float r = fmodf(angle, kTwoPi59);
    if (r >= kPi59)
        return r - kTwoPi59;
    return r;
}

// ===========================================================================
// @ 0x0059c060
void SP::cSPEditorAnimatedCreatureManager::Init(cIModelWorld* pModelWorld, bool flag)
{
    mModelWorld = pModelWorld;
    void* pProps = FUN_0067cb20();
    typedef void* (__thiscall* GetEditorFn)(void*, const wchar_t*);
    GetEditorFn getEditor = *(GetEditorFn*)(*(char**)pProps + 0x20);
    mAnimWorld = (cISPCreatureAnimWorld*)getEditor(pProps, L"Editor");
    if (!mAnimWorld)
        return;
    if (*(int*)(*(int*)(*(int*)0x015fd918 + 0x3c) + 0x118) != 0) {
        void* p2 = FUN_0067cb20();
        typedef void (__thiscall* NotifyFn)(void*, unsigned int);
        NotifyFn notify = *(NotifyFn*)(*(char**)p2 + 0x3c);
        notify(p2, 0x4373c4f);
    }
    if (flag) {
        mAnimWorld->SetWorld(pModelWorld, 1, 1, 0, 1);
        cSPEditorAnimationManager* pMgr =
            new ("Editor", 0, 0, 0, 0) cSPEditorAnimationManager();
        mAnimManager = pMgr;
        if (mAnimManager)
            mAnimManager->Init();
    } else {
        mAnimWorld->SetWorld(pModelWorld, 1, 0, 0, 0);
    }
}

// ===========================================================================
// @ 0x0059c190
struct Vector3M { float x, y, z; Vector3M() {} Vector3M(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Matrix33T {
    Vector3M xAxis, yAxis, zAxis;                 // 9 floats
    Matrix33T() {}
    Matrix33T& operator=(const Matrix33T& o);     // out of line @ 0x0041cb40
};
struct Quaternion { float x, y, z, w; };

Matrix33T& Matrix3FromQuaternion(Matrix33T& result, const Quaternion& q)
{
    float x = q.x, y = q.y, z = q.z, w = q.w;
    Matrix33T tmp;
    tmp.xAxis = Vector3M(1.0f - (z * z + y * y) * 2.0f, (w * z + y * x) * 2.0f, (z * x - w * y) * 2.0f);
    tmp.yAxis = Vector3M((y * x - w * z) * 2.0f, 1.0f - (z * z + x * x) * 2.0f, (w * x + z * y) * 2.0f);
    tmp.zAxis = Vector3M((w * y + z * x) * 2.0f, (z * y - w * x) * 2.0f, 1.0f - (y * y + x * x) * 2.0f);
    return result = tmp;
}

// ===========================================================================
// @ 0x0059c2f0
typedef eastl::rbtree<unsigned int, EA::AutoRefCount<cSPEditorAnimatedCreatureData> > CreatureMap;

template CreatureMap::iterator CreatureMap::DoInsertValueImpl(
    eastl::rbtree_node_base*, const CreatureMap::value_type&, bool);

// @ 0x0059c460
template CreatureMap::iterator CreatureMap::erase(CreatureMap::iterator);

// ===========================================================================
// @ 0x0059c410
typedef EA::AutoRefCount<cSPEditorAnimatedEventInfo> EventRef;
void __stdcall ReleaseAutoRefRange(EventRef* first, EventRef* last)
{
    for (; first < last; ++first)
        first->~EventRef();
}

// ===========================================================================
// @ 0x0059b4b0
cAnimManager* AnimManager();                                                        // 0x0067cb20
cIModelManager* ModelManager();                                                     // 0x0067dd80
cSPVector3 MoveTowards(const cSPVector3& from, const cSPVector3& to, float step);    // 0x00699600
float ApproachAngle(float current, float target, float step);                       // 0x0069b840
float SignedAngle(const cSPVector3* a, const cSPVector3* b, const cSPVector3* axis); // 0x0069b760
float WrapAngle(float angle);                                                       // 0x0059ac00
cSPMatrix3 RotationMatrix(const cSPVector3& axis, float angle);                     // 0x00576b00
cSPVector3 RotateVector(const cSPVector3& v, const cSPQuaternion& q);               // 0x0059aed0
bool IsFiniteVector(const cSPVector3& v);                                           // 0x0059ab70
cSPVector3 Normalize(const cSPVector3& v);                                          // 0x00436ce0

extern cSPVector3 kZeroVector;   // 0x015e590c
extern cSPVector3 kAxisY;        // 0x015e5a88
extern cSPVector3 kAxisZ;        // 0x015e5a0c
extern float kLookAtDistance;    // 0x0150dfe4 (10.0)
extern float kLookAtTurnSpeed;   // 0x0150dfe8 (5.0)
extern float kMinLookDistance;   // 0x0150dfe0 (0.1)
extern float kLookAtSmoothing;   // 0x0150dfdc (0.85)
extern float kQuarterPi;         // 0x0150de50

void SP::cSPEditorAnimatedCreatureData::Update(unsigned int milliseconds)
{
    if (!mAnimatingCreature || !mModelWorld)
        return;

    float dt = (float)milliseconds * 0.001f;
    uint32_t animID;
    int animIndex = 0;
    float moveScale = 1.0f;
    float turnScale = 1.0f;
    mAnimatingCreature->GetCurrentAnimation(&animID, 0, 0, &animIndex);

    cAnimInfo* pInfo = AnimManager()->GetAnimInfo(animID);
    if (pInfo && !pInfo->mbNoOrientation) {
        moveScale = 0.0f;
        turnScale = 0.0f;
        RefreshTargetPosition();
    }

    if (mAnimatingCreature->IsOrientStartAnim(animID)) {
        float length = 0.0f;
        float time = 0.0f;
        if (mAnimatingCreature->GetAnimationProgress(animIndex, &length, &time)) {
            moveScale = Clamp(time / length, 0.0f, 1.0f);
            turnScale = moveScale;
        } else {
            turnScale = 0.0f;
            moveScale = 0.0f;
        }
    }

    mActualPosition = MoveTowards(mActualPosition, mTargetPosition, mMovementSpeed * moveScale * dt);
    if (mActualPosition.Length() > 5.0f)
        mActualPosition = mActualPosition.Normalize() * 5.0f;

    mActualAngle = ApproachAngle(mActualAngle, mTargetAngle, mRotationSpeed * turnScale * dt);

    cSPVector3 toTarget = mTargetLookAtPosition - mActualPosition;
    cSPVector3 toLook = mActualLookAtPosition - mActualPosition;
    cSPVector3 targetDir = toTarget;
    if (toTarget != kZeroVector)
        targetDir = toTarget.Normalized();
    cSPVector3 lookDir = toLook;
    if (toLook != kZeroVector)
        lookDir = toLook.Normalized();

    if (mIsTurning) {
        float targetAngle = SignedAngle(&targetDir, &kAxisY, &kAxisZ);
        float lookAngle = SignedAngle(&lookDir, &kAxisY, &kAxisZ);
        float angle = ApproachAngle(lookAngle, targetAngle, kLookAtTurnSpeed * dt);
        mActualLookAtPosition = mActualPosition + cSPVector3(sinf(angle), cosf(angle), 0.0f) * kLookAtDistance;
    } else {
        mActualLookAtPosition = mActualPosition + MoveTowards(lookDir, targetDir, dt * 2.0f) * kLookAtDistance;
    }

    if (mLookAtTarget) {
        targetDir.z = 0.0f;
        cSPVector3 back = -kAxisY;
        float targetAngle = -SignedAngle(&targetDir, &back, &kAxisZ);
        float actualAngle = mActualAngle;
        float diff = WrapAngle(WrapAngle(actualAngle) - WrapAngle(targetAngle));
        if (Abs(diff) > kQuarterPi) {
            float sign = (diff < 0.0f) ? -1.0f : 1.0f;
            cSPMatrix3 rot = RotationMatrix(kAxisZ, actualAngle - sign * kQuarterPi);
            mActualLookAtPosition = mAnimatingCreature->mPosition + cSPVector3(0.0f, -1.5f, 0.5f) * rot;
        }
    }

    mAnimatingCreature->mPosition = mActualPosition;
    mAnimatingCreature->mOrientation = QuaternionFromAxisAngle(kAxisZ, mActualAngle);

    if (mAnimatingCreature->IsOrientIdleAnim(animID) && mAnimatingCreature->mpAnimData->mbOrientIdle) {
        cAnimatingCreature* pCreature = mAnimatingCreature;
        if (mIsTurning) {
            pCreature->mLookAtPosition = mActualLookAtPosition;
        } else {
            cSPVector3 toTarget = mRawTargetPosition - mActualPosition;
            toTarget.z = 0.0f;
            cSPVector3 dir;
            if (toTarget.Length() > kMinLookDistance) {
                dir = Normalize(toTarget);
            } else {
                cSPVector3 fallback = -kAxisY;
                cSPVector3 v = fallback;
                v = RotateVector(v, pCreature->mOrientation);
                if (!IsFiniteVector(v))
                    v = fallback;
                dir = v;
            }
            cSPVector3 target = mActualPosition + dir * kLookAtDistance;
            pCreature->mLookAtPosition = pCreature->mLookAtPosition * kLookAtSmoothing + target * (1.0f - kLookAtSmoothing);
            if (Abs(mAnimatingCreature->mLookAtPosition.z) < 1.5258789e-05f)
                mAnimatingCreature->mLookAtPosition.z = 0.0f;
            mActualLookAtPosition = mAnimatingCreature->mLookAtPosition;
            mTargetLookAtPosition = mAnimatingCreature->mLookAtPosition;
        }
    } else {
        mAnimatingCreature->mLookAtPosition = mActualLookAtPosition;
    }

    if (!mPreserveHeight) {
        const cSPVector3& pos = mAnimatingCreature->mPosition;
        cSPVector3 start(pos.x, pos.y, 500.0f);
        FilterSettings settings;
        settings.SetRequiredGroup(ModelManager()->GetGroupFlag(0x26f3933, 0));
        cSPVector3 end(start.x, start.y, start.z - 1000.0f);
        cSPVector3 hit;
        if (mModelWorld->FindFirstModelAlongLine(start, end, 0, &hit, 0, settings, 0, 0)) {
            if (mHeightDropWaitTime > 0.0f) {
                mHeightDropWaitTime -= dt;
                return;
            }
            mAnimatingCreature->mPosition.z = mHeightOffset + hit.z;
            float cur = mHeightOffset;
            float target = mHeightOffsetTarget;
            if (target > cur) {
                cur = mHeightDropSpeed * dt + cur;
                mHeightOffset = cur;
                if (cur > target)
                    mHeightOffset = target;
            } else if (cur > target) {
                cur = cur - mHeightDropSpeed * dt;
                mHeightOffset = cur;
                if (target > cur)
                    mHeightOffset = target;
            }
        }
    }
}
