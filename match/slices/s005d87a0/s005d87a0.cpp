// Slice s005d87a0: SP::cSPEditorTactilityManager (editor "tactile" lerp animations for the cursor,
// blocks, models, windows and floats) and the eastl::map instances it owns.
#include "types.h"

inline void* operator new(unsigned int, void* p) throw() { return p; }
void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);   // 0x00F473A0
void operator delete(void* p) throw();     // 0x00F47380
void operator delete[](void* p) throw();   // 0x00F47380
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern "C" double __cdecl asin(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(asin, sin, fabs)
inline float fabsf(float x) { return (float)fabs((double)x); }
inline float asinf_(float x) { return (float)asin((double)x); }

// ---------------------------------------------------------------------------------------------
// Math types
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    cSPVector3 operator-(const cSPVector3& v) const { return cSPVector3(x - v.x, y - v.y, z - v.z); }
    cSPVector3 operator+(const cSPVector3& v) const { return cSPVector3(x + v.x, y + v.y, z + v.z); }
    cSPVector3 operator*(float f) const { return cSPVector3(x * f, y * f, z * f); }
};
struct cSPMatrix3 {
    float m[9];
    cSPMatrix3& Assign(const cSPMatrix3& other);   // 0x0041CB40
    static const cSPMatrix3 IDENTITY;              // 0x015EF16C
};
extern const cSPVector3 kZeroVector3;              // 0x015EF03C
struct cSPQuaternion {
    float x, y, z, w;
    cSPQuaternion() {}
    cSPQuaternion(const cSPQuaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
    cSPQuaternion& operator=(const cSPQuaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
};
namespace rw { namespace math { namespace fpu {
cSPQuaternion QuaternionFromMatrix33(const cSPMatrix3& m, float tolerance);   // 0x00472B80
} } }
cSPQuaternion Slerp(const cSPQuaternion& a, const cSPQuaternion& b, float t);    // 0x005B2500
namespace SP {
cSPMatrix3 Matrix3FromQuaternion(const cSPQuaternion& q);                        // 0x0059C190
}

struct cSPTransform {
    uint16_t mFlags;               // +0x0
    uint16_t mModificationCount;   // +0x2
    cSPVector3 mTranslation;       // +0x4
    float mScale;                  // +0x10
    cSPMatrix3 mRotation;          // +0x14
    cSPTransform() : mFlags(0), mModificationCount(0), mTranslation(kZeroVector3), mScale(1.0f) {
        mRotation.Assign(cSPMatrix3::IDENTITY);
    }
    cSPTransform& operator=(const cSPTransform& x);   // 0x00537DC0
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetTranslation(const cSPVector3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
};

// ---------------------------------------------------------------------------------------------
// Ref-counted key types
namespace EA {
namespace UTFWin {
struct IWindow {
    virtual int AddRef();
    virtual int Release();
};
}
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount() {
        if (mpObject)
            mpObject->Release();
    }
};
}
namespace SP {
struct cIModelWorld;
struct cMWModel {
    cIModelWorld* mWorld;   // +0x0
    uint32_t mFlags;        // +0x4 (bit 31: allocated by the world)
    char pad08[0x40 - 8];
    int mRefCount;          // +0x40
    void AddRef() { ++mRefCount; }
    void Release();
};
struct cIModelWorld {
    virtual int AddRef();
    virtual int Release();
#define PH(n) virtual void ph##n();
    PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10) PH(11) PH(12) PH(13) PH(14)
    PH(15) PH(16) PH(17) PH(18) PH(19) PH(20) PH(21) PH(22) PH(23) PH(24) PH(25) PH(26) PH(27)
    PH(28) PH(29) PH(30) PH(31) PH(32) PH(33) PH(34) PH(35) PH(36) PH(37) PH(38) PH(39) PH(40)
    PH(41) PH(42) PH(43) PH(44) PH(45) PH(46) PH(47) PH(48) PH(49) PH(50) PH(51) PH(52) PH(53)
    PH(54) PH(55) PH(56) PH(57) PH(58) PH(59) PH(60) PH(61) PH(62) PH(63) PH(64) PH(65) PH(66)
    PH(67) PH(68) PH(69) PH(70) PH(71) PH(72) PH(73) PH(74) PH(75) PH(76) PH(77) PH(78) PH(79)
    PH(80) PH(81) PH(82) PH(83) PH(84) PH(85) PH(86) PH(87) PH(88) PH(89) PH(90) PH(91)
#undef PH
    virtual void DestroyModel(cMWModel* pModel, bool bWorldAllocated);   // +0x170
};
inline void cMWModel::Release()
{
    if (mRefCount > 1)
        --mRefCount;
    else
        mWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
struct cSPEditorBlock {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
};
}
template <> inline EA::AutoRefCount<SP::cMWModel>::~AutoRefCount()
{
    if (mpObject)
        mpObject->Release();
}

// ---------------------------------------------------------------------------------------------
// EASTL pieces
namespace eastl {
struct allocator {
    allocator() {}
    void* allocate(uint32_t n, int flags = 0) {
        return new ("Editor", flags, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 209) char[n];
    }
    void deallocate(void* p, uint32_t) { delete[] (char*)p; }
};
struct sp_vector_allocator {
    uint32_t mUnknown[2];
    void deallocate(void* p, uint32_t) {
        if (((int*)p)[-1] != 0)
            delete[] (char*)p;
    }
};
template <class T> inline T* uninitialized_copy_ptr(const T* pFirst, const T* pLast, T* pDest)
{
    return (T*)memcpy(pDest, pFirst, (uint32_t)((const char*)pLast - (const char*)pFirst)) + (pLast - pFirst);
}
template <class T, class A> struct VectorBase {
    T* mpBegin;      // +0x0
    T* mpEnd;        // +0x4
    T* mpCapacity;   // +0x8
    A mAllocator;    // +0xc
    VectorBase(uint32_t n, const A& allocator);   // 0x0066AEC0
    ~VectorBase() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin) * sizeof(T));
    }
};
template <class T, class A> struct vector : public VectorBase<T, A> {
    typedef VectorBase<T, A> base_type;
    vector();
    ~vector() {}
    vector(const vector& x) : base_type(x.size(), x.mAllocator) {
        this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
    }
    uint32_t size() const { return (uint32_t)(this->mpEnd - this->mpBegin); }
    T& back() { return *(this->mpEnd - 1); }
    void pop_back() { --this->mpEnd; }
};

template <class T1, class T2> struct pair {
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
};

template <class T> struct less {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
template <class T> struct less<EA::AutoRefCount<T> > {
    bool operator()(const EA::AutoRefCount<T>& a, const EA::AutoRefCount<T>& b) const { return a.mpObject < b.mpObject; }
};
struct true_type {};

enum RBTreeSide { kRBTreeSideLeft = 0, kRBTreeSideRight = 1 };
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;    // +0x0
    rbtree_node_base* mpNodeLeft;     // +0x4
    rbtree_node_base* mpNodeParent;   // +0x8
    char mColor;                      // +0xc
};
template <class V> struct rbtree_node : public rbtree_node_base {
    V mValue;   // +0x10
};
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);   // 0x00921580
void RBTreeInsert(rbtree_node_base* pNode, rbtree_node_base* pNodeParent, rbtree_node_base* pNodeAnchor, RBTreeSide insertionSide);   // 0x009216A0
void RBTreeErase(rbtree_node_base* pNode, rbtree_node_base* pNodeAnchor);   // 0x00921880

template <class V> struct rbtree_iterator {
    rbtree_node<V>* mpNode;
    rbtree_iterator() : mpNode(0) {}
    explicit rbtree_iterator(const rbtree_node<V>* pNode) : mpNode((rbtree_node<V>*)pNode) {}
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
    V* operator->() const { return &mpNode->mValue; }
    rbtree_iterator& operator++() {
        mpNode = (rbtree_node<V>*)RBTreeIncrement(mpNode);
        return *this;
    }
    bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
};

template <class K, class T> class map {
public:
    typedef pair<const K, T> value_type;
    typedef rbtree_node<value_type> node_type;
    typedef rbtree_iterator<value_type> iterator;
    typedef K key_type;

    less<K> mCompare;                // +0x0
    rbtree_node_base mAnchor;        // +0x4
    uint32_t mnSize;                 // +0x14
    allocator mAllocator;            // +0x18

    map() : mAnchor(), mnSize(0) { reset(); }
    ~map() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
    void reset() {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    iterator begin() { return iterator((node_type*)mAnchor.mpNodeLeft); }
    iterator end() { return iterator((node_type*)&mAnchor); }

    iterator lower_bound(const key_type& key) {
        node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
        node_type* pRangeEnd = (node_type*)&mAnchor;
        while (pCurrent) {
            if (!mCompare(pCurrent->mValue.first, key)) {
                pRangeEnd = pCurrent;
                pCurrent = (node_type*)pCurrent->mpNodeLeft;
            } else {
                pCurrent = (node_type*)pCurrent->mpNodeRight;
            }
        }
        return iterator(pRangeEnd);
    }
    T& operator[](const key_type& key);
    iterator insert(iterator position, const value_type& value) { return DoInsertValue(position, value, true_type()); }
    iterator erase(iterator position);

    iterator DoInsertValue(iterator position, const value_type& value, true_type);   // 0x005D9490 (model-world map)
    iterator DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft);
    node_type* DoCreateNode(const value_type& value) {
        node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type));
        ::new (&pNode->mValue) value_type(value);
        return pNode;
    }
    void DoFreeNode(node_type* pNode) {
        pNode->~node_type();
        mAllocator.deallocate(pNode, sizeof(node_type));
    }
    void DoNukeSubtree(node_type* pNode);
};

template <class K, class T>
void map<K, T>::DoNukeSubtree(node_type* pNode)
{
    while (pNode) {
        DoNukeSubtree((node_type*)pNode->mpNodeRight);
        node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}

template <class K, class T>
typename map<K, T>::iterator map<K, T>::erase(iterator position)
{
    const iterator iErase(position);
    --mnSize;
    ++position;
    RBTreeErase(iErase.mpNode, &mAnchor);
    DoFreeNode(iErase.mpNode);
    return position;
}

template <class K, class T>
typename map<K, T>::iterator map<K, T>::DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft)
{
    RBTreeSide side;
    if (bForceToLeft || (pNodeParent == &mAnchor) || mCompare(value.first, pNodeParent->mValue.first))
        side = kRBTreeSideLeft;
    else
        side = kRBTreeSideRight;
    node_type* const pNodeNew = DoCreateNode(value);
    RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
    mnSize++;
    return iterator(pNodeNew);
}

template <class K, class T>
T& map<K, T>::operator[](const key_type& key)
{
    iterator itLower(lower_bound(key));
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, T()));
    return itLower.mpNode->mValue.second;
}
}

// ---------------------------------------------------------------------------------------------
namespace SP {
enum eEditorTactileType { kTactileTypeNone = 0 };
enum eEditorTactileLerp { kTactileLerpLinear = 0, kTactileLerpSpring = 2, kTactileLerpOvershoot = 3 };

struct cSPEditorTactileComponent {
    eEditorTactileType mType;   // +0x0
    eEditorTactileLerp mLerp;   // +0x4
    float mHistoryValue;        // +0x8
    float mFinalValue;          // +0xc
    float mTimeRemaining;       // +0x10
    float mTimeTotal;           // +0x14
    float mVelocity;            // +0x18
    float mOverShootX;          // +0x1c
    float mOverShootScale;      // +0x20
    unsigned int mAnimationID;  // +0x24
};

// Transform-valued tactile animation (retail-only layout).
struct cSPEditorTactileTransform {
    char pad00[0x28];
    eEditorTactileType mType;     // +0x28
    eEditorTactileLerp mLerp;     // +0x2c
    float mUnknown30;             // +0x30
    float mUnknown34;             // +0x34
    cSPTransform mHistoryValue;   // +0x38
    cSPTransform mFinalValue;     // +0x70
    float mTimeRemaining;         // +0xa8
    float mTimeTotal;             // +0xac
    float mVelocity;              // +0xb0
    float mOverShootX;            // +0xb4
    float mOverShootScale;        // +0xb8
    unsigned int mAnimationID;    // +0xbc
    void* mUnknownC0[3];          // +0xc0
    cSPEditorTactileTransform();
};

typedef eastl::vector<cSPEditorTactileComponent*, eastl::sp_vector_allocator> ComponentList;

class cISPEditorTactilityManager {
public:
    virtual bool Init() = 0;
    virtual bool Shutdown() = 0;
};

class cSPEditorTactilityManager : public cISPEditorTactilityManager {
public:
    cSPEditorTactilityManager();
    virtual ~cSPEditorTactilityManager() {}
    virtual bool Init();
    virtual bool Shutdown();
    void LerpCursor(eEditorTactileType type, float finalValue, float time, eEditorTactileLerp lerp);
    static bool __stdcall UpdateComponent(cSPEditorTactileComponent* pComponent, float* pValue, float currentValue, float deltaTime);
    static bool __stdcall UpdateComponent(cSPEditorTactileTransform* pComponent, cSPTransform* pValue, const cSPTransform& currentValue);
    static void __stdcall InitComponent(cSPEditorTactileTransform* pComponent, eEditorTactileType type, eEditorTactileLerp lerp,
                                        cSPTransform historyValue, cSPTransform finalValue, float time, unsigned int animationID);

    eastl::map<EA::AutoRefCount<cSPEditorBlock>, ComponentList> mBlockComponentList;                    // +0x4
    eastl::map<EA::AutoRefCount<cMWModel>, ComponentList> mModelComponentList;                          // +0x20
    eastl::map<EA::AutoRefCount<EA::UTFWin::IWindow>, ComponentList> mWindowComponentList;              // +0x3c
    eastl::map<EA::AutoRefCount<cMWModel>, EA::AutoRefCount<cIModelWorld> > mModelWorldList;            // +0x58
    eastl::map<float*, ComponentList> mFloatComponentList;                                              // +0x74
    cSPEditorTactileComponent mCursorAnimation;                                                         // +0x90
};
}

using namespace SP;

// @ 0x005D87A0
bool cSPEditorTactilityManager::Init()
{
    mCursorAnimation.mType = kTactileTypeNone;
    return true;
}

// @ 0x005D87B0
bool __stdcall cSPEditorTactilityManager::UpdateComponent(cSPEditorTactileComponent* pComponent, float* pValue, float currentValue, float deltaTime)
{
    float t = (pComponent->mTimeTotal - pComponent->mTimeRemaining) / pComponent->mTimeTotal;
    bool bDone = false;
    if (t >= 1.0f) {
        t = 1.0f;
        bDone = true;
    }
    switch (pComponent->mLerp) {
    case kTactileLerpSpring: {
        const float finalValue = pComponent->mFinalValue;
        bool bArrived = false;
        if (fabsf(currentValue - finalValue) <= 0.005f)
            bArrived = true;
        pComponent->mVelocity = (finalValue - currentValue) + pComponent->mVelocity * 0.9f;
        *pValue = pComponent->mVelocity * deltaTime + currentValue;
        return bArrived;
    }
    case kTactileLerpOvershoot:
        *pValue = (pComponent->mFinalValue - pComponent->mHistoryValue) * ((float)sin(pComponent->mOverShootX * t) * pComponent->mOverShootScale) + pComponent->mHistoryValue;
        return bDone;
    case kTactileLerpLinear:
    case 1:
        *pValue = (pComponent->mFinalValue - pComponent->mHistoryValue) * t + pComponent->mHistoryValue;
        return bDone;
    default:
        *pValue = (pComponent->mFinalValue - pComponent->mHistoryValue) * t + pComponent->mHistoryValue;
        return bDone;
    }
}

// @ 0x005D88B0
void cSPEditorTactilityManager::LerpCursor(eEditorTactileType type, float finalValue, float time, eEditorTactileLerp lerp)
{
    float historyValue;
    switch (type) {
    case 0x1002: historyValue = 0.0f; type = (eEditorTactileType)0xb; break;
    case 0x1012: historyValue = 0.1f; type = (eEditorTactileType)0xb; break;
    case 0x1013: historyValue = 0.2f; type = (eEditorTactileType)0xb; break;
    case 0x1014: historyValue = 0.3f; type = (eEditorTactileType)0xb; break;
    case 0x1015: historyValue = 0.4f; type = (eEditorTactileType)0xb; break;
    case 0x1016: historyValue = 0.5f; type = (eEditorTactileType)0xb; break;
    case 0x1017: historyValue = 0.6f; type = (eEditorTactileType)0xb; break;
    case 0x1018: historyValue = 0.7f; type = (eEditorTactileType)0xb; break;
    case 0x1019: historyValue = 0.8f; type = (eEditorTactileType)0xb; break;
    case 0x101a: historyValue = 0.9f; type = (eEditorTactileType)0xb; break;
    case 0x1005: historyValue = 0.0f; type = (eEditorTactileType)0xc; break;
    case 0x101b: historyValue = 0.1f; type = (eEditorTactileType)0xc; break;
    case 0x101c: historyValue = 0.2f; type = (eEditorTactileType)0xc; break;
    case 0x101d: historyValue = 0.3f; type = (eEditorTactileType)0xc; break;
    case 0x101e: historyValue = 0.4f; type = (eEditorTactileType)0xc; break;
    case 0x101f: historyValue = 0.5f; type = (eEditorTactileType)0xc; break;
    case 0x1020: historyValue = 0.6f; type = (eEditorTactileType)0xc; break;
    case 0x1021: historyValue = 0.7f; type = (eEditorTactileType)0xc; break;
    case 0x1022: historyValue = 0.8f; type = (eEditorTactileType)0xc; break;
    case 0x1023: historyValue = 0.9f; type = (eEditorTactileType)0xc; break;
    default: break;
    }
    mCursorAnimation.mHistoryValue = historyValue;
    mCursorAnimation.mFinalValue = finalValue;
    mCursorAnimation.mTimeRemaining = time;
    mCursorAnimation.mTimeTotal = time;
    mCursorAnimation.mType = type;
    mCursorAnimation.mLerp = lerp;
    mCursorAnimation.mVelocity = 0.0f;
    mCursorAnimation.mOverShootScale = 1.1f;
    mCursorAnimation.mOverShootX = 3.1415927f - asinf_(1.0f / mCursorAnimation.mOverShootScale);
    mCursorAnimation.mAnimationID = 0;
}

// @ 0x005D8B20
bool cSPEditorTactilityManager::Shutdown()
{
    for (eastl::map<EA::AutoRefCount<cSPEditorBlock>, ComponentList>::iterator it = mBlockComponentList.begin(); it != mBlockComponentList.end(); ++it) {
        ComponentList& components = it->second;
        while (components.size() > 0) {
            delete components.back();
            components.pop_back();
        }
    }
    for (eastl::map<EA::AutoRefCount<cMWModel>, ComponentList>::iterator it = mModelComponentList.begin(); it != mModelComponentList.end(); ++it) {
        ComponentList& components = it->second;
        while (components.size() > 0) {
            delete components.back();
            components.pop_back();
        }
    }
    for (eastl::map<float*, ComponentList>::iterator it = mFloatComponentList.begin(); it != mFloatComponentList.end(); ++it) {
        ComponentList& components = it->second;
        while (components.size() > 0) {
            delete components.back();
            components.pop_back();
        }
    }
    return true;
}

// @ 0x005D8C20
void __stdcall cSPEditorTactilityManager::InitComponent(cSPEditorTactileTransform* pComponent, eEditorTactileType type, eEditorTactileLerp lerp,
                                                        cSPTransform historyValue, cSPTransform finalValue, float time, unsigned int animationID)
{
    pComponent->mType = type;
    pComponent->mLerp = lerp;
    pComponent->mUnknown30 = 0.0f;
    pComponent->mUnknown34 = 0.0f;
    pComponent->mHistoryValue = historyValue;
    pComponent->mHistoryValue = finalValue;
    pComponent->mTimeRemaining = time;
    pComponent->mTimeTotal = time;
    pComponent->mVelocity = 0.0f;
    pComponent->mOverShootScale = 1.1f;
    pComponent->mOverShootX = 3.1415927f - asinf_(1.0f / pComponent->mOverShootScale);
    pComponent->mAnimationID = animationID;
}

// @ 0x005D8CC0
cSPEditorTactileTransform::cSPEditorTactileTransform()
{
    mUnknownC0[0] = 0;
    mUnknownC0[1] = 0;
    mUnknownC0[2] = 0;
}

// @ 0x005D8F10
bool __stdcall cSPEditorTactilityManager::UpdateComponent(cSPEditorTactileTransform* pComponent, cSPTransform* pValue, const cSPTransform& currentValue)
{
    float t = (pComponent->mTimeTotal - pComponent->mTimeRemaining) / pComponent->mTimeTotal;
    bool bDone = false;
    if (t >= 1.0f) {
        t = 1.0f;
        bDone = true;
    }
    cSPQuaternion q, qTo;
    q = rw::math::fpu::QuaternionFromMatrix33(pComponent->mHistoryValue.mRotation, 0.0f);
    qTo = rw::math::fpu::QuaternionFromMatrix33(pComponent->mFinalValue.mRotation, 0.0f);
    cSPVector3 pos = pComponent->mHistoryValue.mTranslation;
    const cSPVector3 to = pComponent->mFinalValue.mTranslation;
    q = Slerp(q, qTo, t);
    pos = (to - pos) * t + pos;
    pValue->SetRotation(Matrix3FromQuaternion(q));
    pValue->SetTranslation(pos);
    return bDone;
}

// @ 0x005D96D0
cSPEditorTactilityManager::cSPEditorTactilityManager()
{
}

// @ 0x005D9770 (scalar deleting destructor)

namespace eastl {
// @ 0x005D8D80 map<AutoRefCount<cMWModel>, ComponentList>::DoFreeNode
// @ 0x005D91D0 map<AutoRefCount<cMWModel>, ComponentList>::DoNukeSubtree
// @ 0x005D95C0 pair<const AutoRefCount<cMWModel>, ComponentList>::pair(const pair&)
// @ 0x005D93D0 pair<const AutoRefCount<cMWModel>, ComponentList>::pair(const K&, const V&)
template class map<EA::AutoRefCount<SP::cMWModel>, SP::ComponentList>;
// @ 0x005D9110 map<AutoRefCount<cSPEditorBlock>, ComponentList>::erase
// @ 0x005D9170 map<AutoRefCount<cSPEditorBlock>, ComponentList>::DoNukeSubtree
// @ 0x005D9560 pair<const AutoRefCount<cSPEditorBlock>, ComponentList>::pair(const pair&)
// @ 0x005D9370 pair<const AutoRefCount<cSPEditorBlock>, ComponentList>::pair(const K&, const V&)
template class map<EA::AutoRefCount<SP::cSPEditorBlock>, SP::ComponentList>;
// @ 0x005D9250 map<AutoRefCount<IWindow>, ComponentList>::DoNukeSubtree
// @ 0x005D9620 pair<const AutoRefCount<IWindow>, ComponentList>::pair(const pair&)
// @ 0x005D9430 pair<const AutoRefCount<IWindow>, ComponentList>::pair(const K&, const V&)
template class map<EA::AutoRefCount<EA::UTFWin::IWindow>, SP::ComponentList>;
// @ 0x005D92B0 map<AutoRefCount<cMWModel>, AutoRefCount<cIModelWorld>>::DoNukeSubtree
// @ 0x005D8DF0 map<AutoRefCount<cMWModel>, AutoRefCount<cIModelWorld>>::DoInsertValueImpl
// @ 0x005D9800 map<AutoRefCount<cMWModel>, AutoRefCount<cIModelWorld>>::operator[]
template class map<EA::AutoRefCount<SP::cMWModel>, EA::AutoRefCount<SP::cIModelWorld> >;
// @ 0x005D9320 map<float*, ComponentList>::DoNukeSubtree
// @ 0x005D9680 pair<float* const, ComponentList>::pair(const pair&)
template class map<float*, SP::ComponentList>;
}

// Out-of-line instances of the pair constructors (inlined everywhere else).
typedef eastl::pair<const EA::AutoRefCount<SP::cMWModel>, SP::ComponentList> ModelPair;
typedef eastl::pair<const EA::AutoRefCount<SP::cSPEditorBlock>, SP::ComponentList> BlockPair;
typedef eastl::pair<const EA::AutoRefCount<EA::UTFWin::IWindow>, SP::ComponentList> WindowPair;
typedef eastl::pair<float* const, SP::ComponentList> FloatPair;
namespace eastl {
template struct pair<const EA::AutoRefCount<SP::cMWModel>, SP::ComponentList>;
template struct pair<const EA::AutoRefCount<SP::cSPEditorBlock>, SP::ComponentList>;
template struct pair<const EA::AutoRefCount<EA::UTFWin::IWindow>, SP::ComponentList>;
template struct pair<float* const, SP::ComponentList>;
}

