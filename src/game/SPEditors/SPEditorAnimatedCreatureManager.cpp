// src/game/SPEditors/SPEditorAnimatedCreatureManager.cpp -- migrated from slice(s) s0059c4c0, s0059b4b0, s0059acb0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorAnimatedCreatureManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAnimatingCreature.h"

// unnamed retail callees and globals (address in the comment)
extern char gAnimVtblA[];   // 0x013f64b4
extern float gAnimVecX;     // 0x015e590c
extern float gAnimVecY;     // 0x015e5910
extern float gAnimVecZ;     // 0x015e5914
extern float gAnimScale;    // 0x015e5984
extern float gAnimHalf;     // 0x01471064
extern float gAnim2_5;      // 0x013f6488
#include <math.h>
#include <intrin.h>
#include "SP/cAnimInfo.h"
#include "SP/cIModelManager.h"
#include "EA/Swarm/cIComponent.h"
#include "EA/Audio/ConfigurationAggregate.h"
#include "SP/cSPEditorAnimatedCreatureData.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorAnimationManager.h"
#include "cSPMatrix3.h"
#include "cSPQuaternion.h"
#include "cSPVector3.h"
#include "SP/cIModelWorld.h"
#include "EA/Sockets/Socket.h"
#include "EA/Audio/FactoryBinarySampleData.h"

// ---- items of slice s0059acb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
class cAnimatingCreature {
public:
    char pad0[0x70];
    uint32_t mFlags;                // +0x70
    char pad74[0x150 - 0x74];
    uint8_t mByte150;               // +0x150
    void AddRef();                  // 0x00a02c30
    void Release();                 // 0x00a05270
    bool IsSomething(int a);        // 0x00a02b20
};
}
namespace Simulator {
class cAnimatedData {
public:
    virtual void slot0();           // vptr at +0
    int mField04;                   // +0x04
    cAnimatingCreature* mpCreature; // +0x08
    int mField0c;                   // +0x0c
    int mField10, mField14, mField18;   // +0x10..0x18
    int mField1c;                   // +0x1c
    float mVec0[3];                 // +0x20
    float mVec1[3];                 // +0x2c
    float mVec2[3];                 // +0x38
    float mField44, mField48;       // +0x44, +0x48
    float mField4c;                 // +0x4c
    float mField50;                 // +0x50
    bool mField54, mField55;        // +0x54, +0x55
    float mField58, mField5c, mField60;   // +0x58 target
    float mField64, mField68, mField6c;   // +0x64 copy
    bool mField70;                  // +0x70
    float mField74, mField78, mField7c;   // +0x74..0x7c
    float mField80;                 // +0x80
    bool mField84;                  // +0x84

    void FUN_0059ae20(cAnimatingCreature* p, int a);   // 0x0059ae20
    void FUN_0059ae60();                               // 0x0059ae60
    bool FUN_0059ae80();                               // 0x0059ae80
    void FUN_0059aea0(char b);                         // 0x0059aea0
    void* FUN_0059ace0();                              // 0x0059ace0
    void* FUN_0059b0b0(char flags);                    // 0x0059b0b0
    void FUN_0059b2f0(float angle, char update);       // 0x0059b2f0
    void FUN_0059b390();                               // 0x0059b390
    void FUN_0059b420(char b);                         // 0x0059b420
    void FUN_0059aed0(float* out, const float* q, const float* v);  // 0x0059aed0
    void SetTargetPosition(int a, float angle);        // 0x0059b0f0
};
}
extern char gAnimVtblA[];   // 0x013f64b4
extern float gAnimVecX;     // 0x015e590c
extern float gAnimVecY;     // 0x015e5910
extern float gAnimVecZ;     // 0x015e5914
extern float gAnimScale;    // 0x015e5984
extern float gAnimHalf;     // 0x01471064
extern float gAnim2_5;      // 0x013f6488
// ---- items of slice s0059acb0 end

// ---- items of slice s0059b4b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kPi59;      // 0x013f64d4
extern float kTwoPi59;   // 0x0150dff4
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t, void* p) { return p; }
namespace EA {
template <typename T>
class RefCountTemplate_s0059_b4b0 {
public:
    RefCountTemplate_s0059_b4b0() : mnRefCount(0) {}
    virtual ~RefCountTemplate_s0059_b4b0() {}
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
}
namespace EA {
template <typename T>
class AutoRefCount_s0059_b4b0 {
public:
    T* mpObject;
    AutoRefCount_s0059_b4b0() : mpObject(0) {}
    AutoRefCount_s0059_b4b0(const AutoRefCount_s0059_b4b0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0059_b4b0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0059_b4b0& operator=(T* p)
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
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s0059_b4b0 {
    T1 first;
    T2 second;
};
}
namespace eastl {
struct rbtree_node_base_s0059_b4b0 {
    rbtree_node_base_s0059_b4b0* mpNodeRight;    // +0x0
    rbtree_node_base_s0059_b4b0* mpNodeLeft;     // +0x4
    rbtree_node_base_s0059_b4b0* mpNodeParent;   // +0x8
    char              mColor;         // +0xc
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_node_s0059_b4b0 : public rbtree_node_base_s0059_b4b0 {
    pair_s0059_b4b0<K, V> mValue;                // +0x10
};
}
namespace eastl {
template <typename K, typename V>
struct rbtree_iterator_s0059_b4b0 {
    rbtree_node_s0059_b4b0<K, V>* mpNode;
    rbtree_iterator_s0059_b4b0() : mpNode(0) {}
    explicit rbtree_iterator_s0059_b4b0(rbtree_node_s0059_b4b0<K, V>* p) : mpNode(p) {}
    rbtree_iterator_s0059_b4b0(const rbtree_iterator_s0059_b4b0& x) : mpNode(x.mpNode) {}
    rbtree_iterator_s0059_b4b0& operator++() { mpNode = (rbtree_node_s0059_b4b0<K, V>*)RBTreeIncrement(mpNode); return *this; }
    bool operator==(const rbtree_iterator_s0059_b4b0& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator_s0059_b4b0& x) const { return mpNode != x.mpNode; }
    K& operator*() const { return mpNode->mValue.first; }
};
}
extern "C++" void RBTreeInsert(eastl::rbtree_node_base_s0059_b4b0* pNode, eastl::rbtree_node_base_s0059_b4b0* pNodeParent,
                               eastl::rbtree_node_base_s0059_b4b0* pNodeAnchor, int insertionSide);  // 0x009216a0
eastl::rbtree_node_base_s0059_b4b0* RBTreeIncrement(const eastl::rbtree_node_base_s0059_b4b0* pNode);       // 0x00921580
void RBTreeErase(eastl::rbtree_node_base_s0059_b4b0* pNode, eastl::rbtree_node_base_s0059_b4b0* pNodeAnchor);  // 0x00921880
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                               const char* file, int line);                            // 0x00f473a0
void EASTL_allocator_deallocate(void* p);                                              // 0x00f47380
namespace eastl {
template <typename K, typename V>
class rbtree_s0059_b4b0 {
public:
    typedef rbtree_node_s0059_b4b0<K, V> node_type;
    typedef rbtree_iterator_s0059_b4b0<K, V> iterator;
    typedef pair_s0059_b4b0<K, V> value_type;

    int mCompare;               // +0x0 (empty less<K>)
    rbtree_node_base_s0059_b4b0 mAnchor;   // +0x4
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

    iterator DoInsertValueImpl(rbtree_node_base_s0059_b4b0* pNodeParent, const value_type& value, bool bForceToLeft)
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
};  // namespace eastl
}
namespace SP {
class cSPEditorAnimatedCreatureData_s0059_b4b0;
}
namespace SP {
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
}
namespace SP {
struct cSPQuaternion {
    float x, y, z, w;
    cSPQuaternion() {}
    cSPQuaternion(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};
}
namespace SP {
struct cSPMatrix3 {
    cSPVector3 mRow[3];
};
}
namespace SP {
inline cSPVector3 operator*(const cSPVector3& v, const cSPMatrix3& m)
{
    return cSPVector3(m.mRow[0].x * v.x + m.mRow[1].x * v.y + m.mRow[2].x * v.z,
                      m.mRow[0].y * v.x + m.mRow[1].y * v.y + m.mRow[2].y * v.z,
                      m.mRow[0].z * v.x + m.mRow[1].z * v.y + m.mRow[2].z * v.z);
}
}
namespace SP {
struct cCreatureAnimData {
    char pad000[0x2d4];
    bool mbOrientIdle;      // +0x2d4
};
}
namespace SP {
class cAnimatingCreature_s0059_b4b0 {
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
}
namespace SP {
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
}
namespace SP {
class cIModelWorld_s0059_b4b0 {
public:
    virtual void AddRef();     // +0x0
    virtual void Release();    // +0x4
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08();
    virtual void* FindFirstModelAlongLine(const cSPVector3& p1, const cSPVector3& p2, float* factorDst,
                                          cSPVector3* dstPoint, cSPVector3* dstNormal,
                                          FilterSettings& settings, int* a, int* b);   // +0x24
};
}
namespace SP {
class cISPCreatureAnimWorld_s0059_b4b0 {
public:
    virtual void AddRef();     // +0x00
    virtual void Release();    // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void SetWorld(cIModelWorld_s0059_b4b0* world, int a, int b, int c, int d);   // slot +0x1c
};
}
namespace SP {
class cSPEditorAnimationManager_s0059_b4b0 : public EA::RefCountTemplate_s0059_b4b0<int> {
public:
    cSPEditorAnimationManager_s0059_b4b0();   // 0x0059dac0 (out of line)
    void Init();                   // 0x0059db40
    // Original vtable order: destructor / AddRef / Release at slots 0/4/8.
    virtual int AddRef() { return EA::RefCountTemplate_s0059_b4b0<int>::AddRef(); }
    virtual int Release() { return EA::RefCountTemplate_s0059_b4b0<int>::Release(); }
    char pad_8[0x20 - 0x8];
};
}
namespace SP {
class cSPEditorAnimatedEventInfo_s0059_b4b0 {
public:
    virtual ~cSPEditorAnimatedEventInfo_s0059_b4b0() {}
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
}
namespace SP {
class cSPEditorAnimatedCreatureData_s0059_b4b0 : public EA::RefCountTemplate_s0059_b4b0<int> {
public:
    void Update(unsigned int milliseconds);                    // 0x0059b4b0
    void RefreshTargetPosition();                              // 0x0059b390
    EA::AutoRefCount_s0059_b4b0<cAnimatingCreature_s0059_b4b0> mAnimatingCreature;   // +0x8
    cIModelWorld_s0059_b4b0* mModelWorld;                                 // +0xc
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
}
namespace SP {
class cSPEditorAnimatedCreatureManager_s0059_b4b0 : public EA::RefCountTemplate_s0059_b4b0<int> {
public:
    void Init(cIModelWorld_s0059_b4b0* pModelWorld, bool flag);  // 0x0059c060 (SP::cSPEditorAnimatedCreatureManager::Init)

    // rbtree members laid out from +0x8..+0x24, vector +0x24..+0x38
    char pad_08[0x38 - 0x8];
    EA::AutoRefCount_s0059_b4b0<cISPCreatureAnimWorld_s0059_b4b0>     mAnimWorld;     // +0x38
    EA::AutoRefCount_s0059_b4b0<cSPEditorAnimationManager_s0059_b4b0> mAnimManager;   // +0x3c
    EA::AutoRefCount_s0059_b4b0<cIModelWorld_s0059_b4b0>              mModelWorld;    // +0x40
    unsigned int                                mCurrentID;     // +0x44
};
}
void* FUN_0067cb20();   // 0x0067cb20
struct Vector3M { float x, y, z; Vector3M() {} Vector3M(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Matrix33T {
    Vector3M xAxis, yAxis, zAxis;                 // 9 floats
    Matrix33T() {}
    Matrix33T& operator=(const Matrix33T& o);     // out of line @ 0x0041cb40
};
struct Quaternion { float x, y, z, w; };
typedef eastl::rbtree_s0059_b4b0<unsigned int, EA::AutoRefCount_s0059_b4b0<SP::cSPEditorAnimatedCreatureData_s0059_b4b0> > CreatureMap;
typedef EA::AutoRefCount_s0059_b4b0<SP::cSPEditorAnimatedEventInfo_s0059_b4b0> EventRef;
SP::cSPVector3 Normalize(const SP::cSPVector3& v);                                          // 0x00436ce0
// ---- items of slice s0059b4b0 end

// ---- items of slice s0059c4c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float      kIdentityQuat[4]; // 0x0150E1C8
void  operator delete[](void* p);
struct cSPVector3_s0059_c4c0 {
    float x, y, z;
    cSPVector3_s0059_c4c0() {}
    cSPVector3_s0059_c4c0(const cSPVector3_s0059_c4c0& o) : x(o.x), y(o.y), z(o.z) {}
};
extern const cSPVector3_s0059_c4c0 kZeroVector;      // 0x015E5B8C
namespace EA {
template <typename T>
class RefCountTemplate_s0059_c4c0 {
public:
    RefCountTemplate_s0059_c4c0() : mnRefCount(0) {}
    virtual ~RefCountTemplate_s0059_c4c0() {}
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        // volatile read-modify-write gives the load / add -1 / store shape
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
}
namespace EA {
template <typename T>
class AutoRefCount_s0059_c4c0 {
public:
    T* mpObject;
    AutoRefCount_s0059_c4c0() : mpObject(0) {}
    AutoRefCount_s0059_c4c0(const AutoRefCount_s0059_c4c0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0059_c4c0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0059_c4c0& operator=(T* p);   // out of line (0x00572680 for cSPEditorAnimatedCreatureData)
    void Reset()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace eastl {
struct allocator_s0059_c4c0 {};
}
namespace eastl {
struct sp_vector_allocator_s0059_c4c0 { uint32_t pad[2]; sp_vector_allocator_s0059_c4c0() {} };
}
namespace eastl {
struct true_type {};
}
namespace eastl {
template <typename T>
struct less_s0059_c4c0 { bool operator()(const T& a, const T& b) const { return a < b; } };
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s0059_c4c0 {
    T1 first;
    T2 second;
    pair_s0059_c4c0(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
struct rbtree_node_base_s0059_c4c0 {
    rbtree_node_base_s0059_c4c0* mpNodeRight;    // +0x0
    rbtree_node_base_s0059_c4c0* mpNodeLeft;     // +0x4
    rbtree_node_base_s0059_c4c0* mpNodeParent;   // +0x8
    char              mColor;         // +0xc
};
}
namespace eastl {
rbtree_node_base_s0059_c4c0* RBTreeIncrement_s0059_c4c0(const rbtree_node_base_s0059_c4c0* pNode);   // 0x00921580
}
namespace eastl {
template <typename T>
struct rbtree_node_s0059_c4c0 : public rbtree_node_base_s0059_c4c0 {
    T mValue;   // +0x10
};
}
namespace eastl {
template <typename T>
struct rbtree_iterator_s0059_c4c0 {
    typedef rbtree_node_s0059_c4c0<T> node_type;
    node_type* mpNode;
    rbtree_iterator_s0059_c4c0() : mpNode(0) {}
    explicit rbtree_iterator_s0059_c4c0(const node_type* pNode) : mpNode((node_type*)pNode) {}
    rbtree_iterator_s0059_c4c0(const rbtree_iterator_s0059_c4c0& x) : mpNode(x.mpNode) {}
    T* operator->() const { return &mpNode->mValue; }
    rbtree_iterator_s0059_c4c0& operator++() { mpNode = (node_type*)RBTreeIncrement_s0059_c4c0(mpNode); return *this; }
    bool operator==(const rbtree_iterator_s0059_c4c0& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator_s0059_c4c0& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template <typename Key, typename T>
class map_s0059_c4c0 {
public:
    typedef pair_s0059_c4c0<const Key, T>           value_type;
    typedef rbtree_node_s0059_c4c0<value_type>      node_type;
    typedef rbtree_iterator_s0059_c4c0<value_type>  iterator;

    less_s0059_c4c0<Key>        mCompare;   // +0x0
    rbtree_node_base_s0059_c4c0 mAnchor;    // +0x4
    uint32_t         mnSize;     // +0x14
    allocator_s0059_c4c0        mAllocator; // +0x18

    map_s0059_c4c0() : mAnchor(), mnSize(0) { reset(); }
    ~map_s0059_c4c0() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }

    iterator begin() { return iterator((node_type*)mAnchor.mpNodeLeft); }
    iterator end() { return iterator((node_type*)&mAnchor); }

    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear()
    {
        DoNukeSubtree((node_type*)mAnchor.mpNodeParent);
        reset();
    }

    iterator find(const Key& key);                                                    // 0x00E5C780 (folded)
    iterator erase(iterator position);                                                // 0x0059C460
    iterator DoInsertValue(iterator position, const value_type& value, true_type);   // 0x0059C520
    iterator insert(iterator position, const value_type& value)
    {
        return DoInsertValue(position, value, true_type());
    }
    iterator lower_bound(const Key& key)
    {
        node_type*        pCurrent  = (node_type*)mAnchor.mpNodeParent;
        rbtree_node_base_s0059_c4c0* pRangeEnd = &mAnchor;
        while (pCurrent) {
            if (!mCompare(pCurrent->mValue.first, key)) {
                pRangeEnd = pCurrent;
                pCurrent  = (node_type*)pCurrent->mpNodeLeft;
            } else
                pCurrent = (node_type*)pCurrent->mpNodeRight;
        }
        return iterator((node_type*)pRangeEnd);
    }
    T& operator[](const Key& key);
    void DoFreeNode(node_type* pNode)
    {
        pNode->~node_type();
        operator delete[](pNode);
    }
    void DoNukeSubtree(node_type* pNode);
};
}
namespace eastl {
template <typename T, typename Allocator>
class vector_s0059_c4c0 {
public:
    T*        mpBegin;
    T*        mpEnd;
    T*        mpCapacity;
    Allocator mAllocator;
    vector_s0059_c4c0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector_s0059_c4c0();                                                  // out of line (0x005C7F10, folded)
    T* DoInsertValue(T* position, const T& value);              // 0x005C8480
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace SP {
class cIAnimWorldCreatureHelper {
public:
    void OnAnimationStarted(int anim);                   // 0x00A006F0
};
}
namespace SP {
class cAnimatingCreature_s0059_c4c0 {
public:
    virtual void Unk0();
    virtual int  PlayAnimation(uint32_t animID, int flags);   // slot 1
    virtual void Unk2(); virtual void Unk3(); virtual void Unk4(); virtual void Unk5();
    virtual void Unk6(); virtual void Unk7(); virtual void Unk8(); virtual void Unk9();
    virtual void Unk10(); virtual void Unk11(); virtual void Unk12(); virtual void Unk13();
    virtual void Unk14(); virtual void Unk15(); virtual void Unk16(); virtual void Unk17();
    virtual void Unk18(); virtual void Unk19(); virtual void Unk20(); virtual void Unk21();
    virtual void GetCurrentAnimation(uint32_t* pAnimID, int a, int* pCount, int b);   // slot 22
    void AddRef();
    void Release();  // 0x00a05270 (SP::cAnimatingCreature::Release)

    void SetIdle(int);                                 // 0x00A02AB0
    bool IsAnimationDone(int);                         // 0x00A02B20
    bool IsAnimationQueued(uint32_t animID);           // 0x00A02B40
    bool IsAnimationLooping(int);                      // 0x00A04940
    void SetTurnRate(int);                             // 0x00A04C80
    void SetMoving(bool);                              // 0x00A04CA0

    cSPVector3_s0059_c4c0 mPosition;                              // +0x4
    char pad_10[0x54 - 0x10];
    int mState;                                        // +0x54
    char pad_58[0x88 - 0x58];
    uint32_t mFlags;                                   // +0x88
    char pad_8c[0x184 - 0x8c];
    cIAnimWorldCreatureHelper* mpHelper;               // +0x184
};
}
namespace SP {
class cIModelWorld_s0059_c4c0 {
public:
    virtual void AddRef();
    virtual void Release();
};
}
namespace SP {
class cSPEditorAnimationManager_s0059_c4c0 {
public:
    virtual void Unk0();
    virtual void AddRef();
    virtual void Release();
    void Shutdown();                                   // 0x00C2E4E0
};
}
namespace SP {
class cSPEditorAnimatedEventInfo_s0059_c4c0 {
public:
    virtual void Unk0();
    virtual void AddRef();
    virtual void Release();
};
}
namespace SP {
struct cCreatureBlock;
}
namespace SP {
class cISPCreatureAnimWorld_s0059_c4c0 {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void Unk2(); virtual void Unk3(); virtual void Unk4(); virtual void Unk5();
    virtual void Unk6(); virtual void Unk7();
    virtual void Update();                                                                      // slot 8
    virtual void Unk9(); virtual void Unk10(); virtual void Unk11();
    virtual cAnimatingCreature_s0059_c4c0* CreateCreature(cCreatureBlock* block, int lod, const cSPVector3_s0059_c4c0* pos,
                                               const float* orient, bool visible);            // slot 13 (MSVC lists overloads in reverse)
    virtual cAnimatingCreature_s0059_c4c0* CreateCreature(const void* key, int lod, const cSPVector3_s0059_c4c0* pos,
                                               const float* orient, bool visible);            // slot 12
    virtual void Unk14();
    virtual void RemoveCreature(cAnimatingCreature_s0059_c4c0* creature);                                  // slot 15
};
}
namespace SP {
class cSPEditorAnimatedCreatureData_s0059_c4c0 : public EA::RefCountTemplate_s0059_c4c0<int> {
public:
    cSPEditorAnimatedCreatureData_s0059_c4c0();                                         // 0x0059ACE0
    void Init(cAnimatingCreature_s0059_c4c0* creature, cIModelWorld_s0059_c4c0* modelWorld);       // 0x0059AE20
    void Shutdown();                                                         // 0x0059AE60
    bool IsAnimInterruptible();                                              // 0x0059AE80
    void SetPreserveHeight(bool preserve);                                   // 0x0059AC50
    void SetLookAtTarget(const cSPVector3_s0059_c4c0& target, bool immediate);          // 0x0059AC60
    void SetTargetPosition(const cSPVector3_s0059_c4c0& pos, bool immediate, bool raw); // 0x0059B0F0
    void SetTargetAngle(float angle, bool immediate);                        // 0x0059B2F0
    void SetLookAtEnabled(int enabled);                                      // 0x0059B420
    void SetLastAnimationPlayed(uint32_t animID);                            // 0x007CD950 (folded)

    EA::AutoRefCount_s0059_c4c0<cAnimatingCreature_s0059_c4c0> mAnimatingCreature;   // +0x8
    cIModelWorld_s0059_c4c0* mModelWorld;                                 // +0xc
    char pad_10[0x4c - 0x10];
    float mMovementSpeed;                                      // +0x4c
    float mRotationSpeed;                                      // +0x50
    char pad_54[0x84 - 0x54];
    bool mIsTurning;                                           // +0x84
};
}
namespace SP {
struct cCreatureBlockData { char pad_0[0x38]; cSPVector3_s0059_c4c0 mBounds[3]; };
}
namespace SP {
struct cCreatureRigData { void Assign(const void* src); };            // 0x006DF280
}
namespace SP {
struct RefVector { RefVector& operator=(const void* src); };          // 0x0041EBE0
}
namespace SP {
struct cCreatureBlock {
    cCreatureBlockData* mpData;   // +0x0
    uint32_t pad_4;
    cCreatureRigData mRig;        // +0x8
    uint32_t pad_c[5];
    RefVector mRefs;              // +0x20
    uint32_t pad_24[5];
    cCreatureBlock();
    ~cCreatureBlock();
};
}
namespace SP {
struct cEditorModel { char pad_0[0xb8]; char mRig[0xe4 - 0xb8]; char mRefs[0xfc - 0xe4]; int mFC; int m100; };
}
namespace SP {
struct cEditorSkin {
    char pad_0[0x10]; int m10;
    cSPVector3_s0059_c4c0* GetBound(cSPVector3_s0059_c4c0* out, int index);                   // 0x004ADCA0
};
}
namespace SP {
void BuildCreatureBlock(cEditorModel* model, cCreatureBlock* block, bool skinned, int flags);   // 0x0046AAC0
}
namespace SP {
void BuildCreatureRig(cEditorModel* model, int skin, int a, int b);                            // 0x0046DAD0
}
namespace SP {
void FinalizeCreatureBlock(cCreatureBlock* block);                                             // 0x0046B460
}
namespace SP {
class cSPEditorAnimatedCreatureManager_s0059_c4c0 : public EA::RefCountTemplate_s0059_c4c0<int> {
public:
    cSPEditorAnimatedCreatureManager_s0059_c4c0();
    virtual ~cSPEditorAnimatedCreatureManager_s0059_c4c0();

    void Shutdown();
    void RemoveCreature(uint32_t id);
    uint32_t AddCreature(cEditorSkin* skin, cEditorModel* model, bool fromModel, bool skinned);
    uint32_t AddCreature(const void* key);
    cAnimatingCreature_s0059_c4c0* GetCreature(uint32_t id);  // 0x0059ca70 (SP::cSPEditorAnimatedCreatureManager::GetCreature)
    cSPEditorAnimatedCreatureData_s0059_c4c0* GetCreatureStructure(uint32_t id);  // 0x0059cac0 (SP::cSPEditorAnimatedCreatureManager::GetCreatureStructure)
    void PlayAnimation(uint32_t id, uint32_t animID);
    void AddDelayedEvent(EA::AutoRefCount_s0059_c4c0<cSPEditorAnimatedEventInfo_s0059_c4c0> event);
    void SetCreatureIdle(uint32_t id);
    bool IsAnimationPlaying(uint32_t id, uint32_t animID);  // 0x0059cc40 (SP::cSPEditorAnimatedCreatureManager::IsAnimationPlaying)
    bool IsPlayingAnimation(uint32_t id);  // 0x0059cd20 (SP::cSPEditorAnimatedCreatureManager::IsPlayingAnimation)
    bool IsAnimationDone(uint32_t id);
    void SetCreatureVisible(uint32_t id, bool visible);
    void SetCreatureTargetAngle(uint32_t id, float angle, bool immediate);
    void SetCreatureTargetPosition(uint32_t id, cSPVector3_s0059_c4c0 pos, bool immediate, bool raw);
    void SetCreaturePreserveHeight(uint32_t id, bool preserve);
    void SetCreatureLookAtTarget(uint32_t id, const cSPVector3_s0059_c4c0 pos, bool immediate);
    void SetCreatureIsTurning(uint32_t id, bool turning);  // 0x0059d010 (SP::cSPEditorAnimatedCreatureManager::SetCreatureIsTurning)
    void SetCreatureLookAtEnabled(uint32_t id, int enabled);
    void SetCreatureSpeeds(uint32_t id, float movementSpeed, float rotationSpeed);  // 0x0059d0b0 (SP::cSPEditorAnimatedCreatureManager::SetCreatureSpeeds)
    bool GetCreaturePosition(uint32_t id, cSPVector3_s0059_c4c0& pos);
    void SetCreatureTurnRate(uint32_t id, int rate);
    void SetCreatureMoving(uint32_t id, bool moving);
    void ResetCreature(uint32_t id);  // 0x0059d240 (SP::cSPEditorAnimatedCreatureManager::ResetCreature)

    typedef eastl::map_s0059_c4c0<uint32_t, EA::AutoRefCount_s0059_c4c0<cSPEditorAnimatedCreatureData_s0059_c4c0> > CreatureMap;
    CreatureMap mAnimatedCreatures;                                                                  // +0x8
    eastl::vector_s0059_c4c0<EA::AutoRefCount_s0059_c4c0<cSPEditorAnimatedEventInfo_s0059_c4c0>, eastl::sp_vector_allocator_s0059_c4c0> mDelayedAnimatedEvents;  // +0x24
    EA::AutoRefCount_s0059_c4c0<cISPCreatureAnimWorld_s0059_c4c0>     mAnimWorld;     // +0x38
    EA::AutoRefCount_s0059_c4c0<cSPEditorAnimationManager_s0059_c4c0> mAnimManager;   // +0x3c
    EA::AutoRefCount_s0059_c4c0<cIModelWorld_s0059_c4c0>              mModelWorld;    // +0x40
    uint32_t                                    mCurrentID;     // +0x44
};
}
template class eastl::map_s0059_c4c0<uint32_t, EA::AutoRefCount_s0059_c4c0<SP::cSPEditorAnimatedCreatureData_s0059_c4c0> >;
// ---- items of slice s0059c4c0 end

// @ 0x0059ace0
void* Simulator::cAnimatedData::FUN_0059ace0()
{
    *(void**)this = (void*)gAnimVtblA;
    mField04 = 0;
    mpCreature = 0;
    mField0c = 0;
    mField10 = 0;
    mField14 = 0;
    mField18 = 0;
    mField1c = 0;
    mVec0[0] = gAnimVecX; mVec0[1] = gAnimVecY; mVec0[2] = gAnimVecZ;
    mVec1[0] = gAnimVecX; mVec1[1] = gAnimVecY; mVec1[2] = gAnimVecZ;
    mVec2[0] = gAnimVecX; mVec2[1] = gAnimVecY; mVec2[2] = gAnimVecZ;
    mField44 = 0.0f;
    mField48 = 0.0f;
    mField4c = gAnim2_5;
    mField50 = gAnimScale;
    mField54 = false;
    mField55 = false;
    mField58 = gAnimVecX; mField5c = gAnimVecY; mField60 = gAnimVecZ;
    mField64 = gAnimVecX; mField68 = gAnimVecY; mField6c = gAnimVecZ;
    mField74 = 0.0f;
    mField78 = 0.0f;
    mField7c = 0.0f;
    mField70 = true;
    mField80 = gAnimHalf;
    mField84 = false;
    return this;
}



// @ 0x0059ae60
void Simulator::cAnimatedData::FUN_0059ae60()
{
    mField0c = 0;
    _ReadWriteBarrier();
    if (mpCreature) {
        Simulator::cAnimatingCreature* p = mpCreature;
        mpCreature = 0;
        p->Release();
    }
}


// @ 0x0059c030
float WrapAngleToPi(float angle)
{
    float r = fmodf(angle, kTwoPi59);
    if (r >= kPi59)
        return r - kTwoPi59;
    return r;
}


// @ 0x0059c060
void SP::cSPEditorAnimatedCreatureManager_s0059_b4b0::Init(SP::cIModelWorld_s0059_b4b0* pModelWorld, bool flag)
{
    mModelWorld = pModelWorld;
    void* pProps = FUN_0067cb20();
    typedef void* (__thiscall* GetEditorFn)(void*, const wchar_t*);
    GetEditorFn getEditor = *(GetEditorFn*)(*(char**)pProps + 0x20);
    mAnimWorld = (SP::cISPCreatureAnimWorld_s0059_b4b0*)getEditor(pProps, L"Editor");
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
        SP::cSPEditorAnimationManager_s0059_b4b0* pMgr =
            new ("Editor", 0, 0, 0, 0) SP::cSPEditorAnimationManager_s0059_b4b0();
        mAnimManager = pMgr;
        if (mAnimManager)
            mAnimManager->Init();
    } else {
        mAnimWorld->SetWorld(pModelWorld, 1, 0, 0, 0);
    }
}


// @ 0x0059c190
Matrix33T& Matrix3FromQuaternion(Matrix33T& result, const Quaternion& q)
{
    float x = q.x, y = q.y, z = q.z, w = q.w;
    Matrix33T tmp;
    tmp.xAxis = Vector3M(1.0f - (z * z + y * y) * 2.0f, (w * z + y * x) * 2.0f, (z * x - w * y) * 2.0f);
    tmp.yAxis = Vector3M((y * x - w * z) * 2.0f, 1.0f - (z * z + x * x) * 2.0f, (w * x + z * y) * 2.0f);
    tmp.zAxis = Vector3M((w * y + z * x) * 2.0f, (z * y - w * x) * 2.0f, 1.0f - (y * y + x * x) * 2.0f);
    return result = tmp;
}


// @ 0x0059c2f0
template CreatureMap::iterator CreatureMap::DoInsertValueImpl( eastl::rbtree_node_base_s0059_b4b0*, const CreatureMap::value_type&, bool)
;


// @ 0x0059c410
void __stdcall ReleaseAutoRefRange(EventRef* first, EventRef* last)
{
    for (; first < last; ++first)
        first->~EventRef();
}


// @ 0x0059c460
template CreatureMap::iterator CreatureMap::erase(CreatureMap::iterator)
;

// @ 0x0059c4c0
template <typename Key, typename T> void eastl::map_s0059_c4c0<Key, T>::DoNukeSubtree(node_type* pNode)
{
    while (pNode) {
        DoNukeSubtree((node_type*)pNode->mpNodeRight);
        node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}

// @ 0x0059c5f0
SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::~cSPEditorAnimatedCreatureManager_s0059_c4c0()
{
}

// @ 0x0059c640
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::Shutdown()
{
    if (mAnimWorld) {
        for (CreatureMap::iterator it = mAnimatedCreatures.begin(); it != mAnimatedCreatures.end(); ++it) {
            mAnimWorld->RemoveCreature(it->second->mAnimatingCreature);
            it->second->Shutdown();
        }
        mAnimatedCreatures.clear();
        mAnimWorld->Update();
        mAnimWorld.Reset();
    }
    if (mAnimManager) {
        mAnimManager->Shutdown();
        mAnimManager.Reset();
    }
}

// @ 0x0059c6e0
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::RemoveCreature(uint32_t id)
{
    CreatureMap::iterator it;
    it = mAnimatedCreatures.find(id);
    if (mAnimWorld && it != mAnimatedCreatures.end()) {
        mAnimWorld->RemoveCreature(it->second->mAnimatingCreature);
        it->second->Shutdown();
        mAnimatedCreatures.erase(it);
    }
}

// @ 0x0059c740
template <typename Key, typename T> T& eastl::map_s0059_c4c0<Key, T>::operator[](const Key& key)
{
    iterator itLower(lower_bound(key));
    if ((itLower == end()) || mCompare(key, itLower->first))
        itLower = insert(itLower, value_type(key, T()));
    return itLower->second;
}

// @ 0x0059c7c0
SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::cSPEditorAnimatedCreatureManager_s0059_c4c0()
: mCurrentID(1)
{
}

// @ 0x0059c830
uint32_t SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::AddCreature(cEditorSkin* skin, cEditorModel* model, bool fromModel, bool skinned)
{
    uint32_t id = 0;
    if (mAnimWorld && skin && model) {
        id = mCurrentID;
        SP::cCreatureBlock block;
        if (fromModel) {
            SP::BuildCreatureBlock(model, &block, skinned, 0);
            SP::BuildCreatureRig(model, skin->m10, model->mFC, model->m100);
            block.mRig.Assign(model->mRig);
            block.mRefs = model->mRefs;
        } else
            SP::BuildCreatureBlock(model, &block, skinned, 0);
        if (skinned)
            SP::FinalizeCreatureBlock(&block);
        if (block.mpData) {
            for (int i = 0; i < 3; i++)
                block.mpData->mBounds[i] = *skin->GetBound(&cSPVector3_s0059_c4c0(), i);
        }
        SP::cAnimatingCreature_s0059_c4c0* creature = mAnimWorld->CreateCreature(&block, 2, &kZeroVector, kIdentityQuat, true);
        if (creature) {
            SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = new ("Editor", 0, 0, 0, 0) SP::cSPEditorAnimatedCreatureData_s0059_c4c0();
            mAnimatedCreatures[id] = data;
            data->Init(creature, mModelWorld);
            creature->mFlags |= 1;
            creature->mState = 2;
            mCurrentID++;
        }
    }
    return id;
}

// @ 0x0059c9c0
uint32_t SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::AddCreature(const void* key)
{
    uint32_t id = 0;
    if (mAnimWorld && key) {
        id = mCurrentID;
        SP::cAnimatingCreature_s0059_c4c0* creature = mAnimWorld->CreateCreature(key, 2, &kZeroVector, kIdentityQuat, true);
        if (creature) {
            SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = new ("Editor", 0, 0, 0, 0) SP::cSPEditorAnimatedCreatureData_s0059_c4c0();
            mAnimatedCreatures[id] = data;
            data->Init(creature, mModelWorld);
            creature->mFlags |= 1;
            creature->mState = 2;
            mCurrentID++;
        }
    }
    return id;
}

// @ 0x0059ca70
SP::cAnimatingCreature_s0059_c4c0* SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::GetCreature(uint32_t id)
{
    if (mAnimWorld && mAnimatedCreatures.find(id) != mAnimatedCreatures.end())
        return mAnimatedCreatures[id]->mAnimatingCreature;
    return 0;
}

// @ 0x0059cac0
SP::cSPEditorAnimatedCreatureData_s0059_c4c0* SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::GetCreatureStructure(uint32_t id)
{
    if (mAnimWorld && mAnimatedCreatures.find(id) != mAnimatedCreatures.end())
        return mAnimatedCreatures[id];
    return 0;
}

// @ 0x0059cb10
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::PlayAnimation(uint32_t id, uint32_t animID)
{
    SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
    if (mAnimManager && data && data->mAnimatingCreature) {
        data->mAnimatingCreature->PlayAnimation(animID, 0);
        data->SetLastAnimationPlayed(animID);
    }
}

// @ 0x0059cb80
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::AddDelayedEvent(EA::AutoRefCount_s0059_c4c0<cSPEditorAnimatedEventInfo_s0059_c4c0> event)
{
    if (mAnimManager)
        mDelayedAnimatedEvents.push_back(event);
}

// @ 0x0059cbd0
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureIdle(uint32_t id)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (mAnimManager && creature)
        creature->SetIdle(0);
}

// @ 0x0059cc40
bool SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::IsAnimationPlaying(uint32_t id, uint32_t animID)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (creature) {
        int count = 0;
        creature->GetCurrentAnimation(0, 0, &count, 0);
        if (count < 1 && !creature->IsAnimationDone(0)) {
            uint32_t currentID = 0;
            creature->GetCurrentAnimation(&currentID, 0, 0, 0);
            if (currentID == animID)
                return !creature->IsAnimationLooping(0);
            return creature->IsAnimationQueued(animID) != 0;
        }
    }
    return false;
}

// @ 0x0059cd20
bool SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::IsPlayingAnimation(uint32_t id)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (creature) {
        int count = 0;
        creature->GetCurrentAnimation(0, 0, &count, 0);
        if (count < 1 && !creature->IsAnimationDone(0))
            return true;
    }
    return false;
}

// @ 0x0059cdb0
bool SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::IsAnimationDone(uint32_t id)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (creature && !creature->IsAnimationDone(0)) {
        SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
        if (data)
            return data->IsAnimInterruptible();
    }
    return true;
}

// @ 0x0059ce30
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureVisible(uint32_t id, bool visible)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (creature) {
        if (visible)
            creature->mFlags |= 1;
        else
            creature->mFlags &= ~1;
    }
}

// @ 0x0059cea0
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureTargetAngle(uint32_t id, float angle, bool immediate)
{
    SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
    if (data)
        data->SetTargetAngle(angle, immediate);
}

// @ 0x0059cf00
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureTargetPosition(uint32_t id, cSPVector3_s0059_c4c0 pos, bool immediate, bool raw)
{
    SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
    if (data)
        data->SetTargetPosition(pos, immediate, raw);
}

// @ 0x0059cf60
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreaturePreserveHeight(uint32_t id, bool preserve)
{
    SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
    if (data)
        data->SetPreserveHeight(preserve);
}

// @ 0x0059cfb0
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureLookAtTarget(uint32_t id, const cSPVector3_s0059_c4c0 pos, bool immediate)
{
    SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
    if (data)
        data->SetLookAtTarget(pos, immediate);
}

// @ 0x0059d010
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureIsTurning(uint32_t id, bool turning)
{
    SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
    if (data)
        data->mIsTurning = turning;
}

// @ 0x0059d060
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureLookAtEnabled(uint32_t id, int enabled)
{
    SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
    if (data)
        data->SetLookAtEnabled(enabled);
}

// @ 0x0059d0b0
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureSpeeds(uint32_t id, float movementSpeed, float rotationSpeed)
{
    SP::cSPEditorAnimatedCreatureData_s0059_c4c0* data = GetCreatureStructure(id);
    if (data) {
        data->mMovementSpeed = movementSpeed;
        data->mRotationSpeed = rotationSpeed;
    }
}

// @ 0x0059d110
bool SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::GetCreaturePosition(uint32_t id, cSPVector3_s0059_c4c0& pos)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (creature) {
        pos = creature->mPosition;
        return true;
    }
    return false;
}

// @ 0x0059d180
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureTurnRate(uint32_t id, int rate)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (creature)
        creature->SetTurnRate(rate);
}

// @ 0x0059d1e0
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::SetCreatureMoving(uint32_t id, bool moving)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (creature)
        creature->SetMoving(moving);
}

// @ 0x0059d240
void SP::cSPEditorAnimatedCreatureManager_s0059_c4c0::ResetCreature(uint32_t id)
{
    SP::cAnimatingCreature_s0059_c4c0* creature = GetCreature(id);
    if (mAnimManager && creature) {
        SetCreatureTargetPosition(id, kZeroVector, true, true);
        int anim = creature->PlayAnimation(0x4330667, 0);
        if (creature->mpHelper)
            creature->mpHelper->OnAnimationStarted(anim);
    }
}
