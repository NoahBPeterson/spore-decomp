// src/game/SPEditors/SPEditorTactilityManager.cpp -- migrated from slice(s) s005dae60, s005d87a0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorTactilityManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cIModelWorld.h"
#include "SP/cMWModel.h"
#include "SP/cSPEditorBlock.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern "C" double __cdecl asin(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(asin, sin, fabs)

// ---- items of slice s005d87a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) throw() { return p; }
void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);   // 0x00F473A0
void operator delete(void* p) throw();     // 0x00F47380
void operator delete[](void* p) throw();   // 0x00F47380
inline float fabsf(float x) { return (float)fabs((double)x); }
inline float asinf_(float x) { return (float)asin((double)x); }
struct cSPVector3_s005d_87a0 {
    float x, y, z;
    cSPVector3_s005d_87a0() {}
    cSPVector3_s005d_87a0(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    cSPVector3_s005d_87a0(const cSPVector3_s005d_87a0& v) : x(v.x), y(v.y), z(v.z) {}
    cSPVector3_s005d_87a0 operator-(const cSPVector3_s005d_87a0& v) const { return cSPVector3_s005d_87a0(x - v.x, y - v.y, z - v.z); }
    cSPVector3_s005d_87a0 operator+(const cSPVector3_s005d_87a0& v) const { return cSPVector3_s005d_87a0(x + v.x, y + v.y, z + v.z); }
    cSPVector3_s005d_87a0 operator*(float f) const { return cSPVector3_s005d_87a0(x * f, y * f, z * f); }
};
struct cSPMatrix3_s005d_87a0 {
    float m[9];
    cSPMatrix3_s005d_87a0& Assign(const cSPMatrix3_s005d_87a0& other);   // 0x0041CB40
    static const cSPMatrix3_s005d_87a0 IDENTITY;              // 0x015EF16C
};
extern const cSPVector3_s005d_87a0 kZeroVector3;              // 0x015EF03C
struct cSPQuaternion_s005d_87a0 {
    float x, y, z, w;
    cSPQuaternion_s005d_87a0() {}
    cSPQuaternion_s005d_87a0(const cSPQuaternion_s005d_87a0& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
    cSPQuaternion_s005d_87a0& operator=(const cSPQuaternion_s005d_87a0& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
};
namespace rw {
namespace math {
namespace fpu {
cSPQuaternion_s005d_87a0 QuaternionFromMatrix33(const cSPMatrix3_s005d_87a0& m, float tolerance);   // 0x00472B80
}
}
}
cSPQuaternion_s005d_87a0 Slerp(const cSPQuaternion_s005d_87a0& a, const cSPQuaternion_s005d_87a0& b, float t);    // 0x005B2500
namespace SP {
cSPMatrix3_s005d_87a0 Matrix3FromQuaternion(const cSPQuaternion_s005d_87a0& q);                        // 0x0059C190
}
struct cSPTransform_s005d_87a0 {
    uint16_t mFlags;               // +0x0
    uint16_t mModificationCount;   // +0x2
    cSPVector3_s005d_87a0 mTranslation;       // +0x4
    float mScale;                  // +0x10
    cSPMatrix3_s005d_87a0 mRotation;          // +0x14
    cSPTransform_s005d_87a0() : mFlags(0), mModificationCount(0), mTranslation(kZeroVector3), mScale(1.0f) {
        mRotation.Assign(cSPMatrix3_s005d_87a0::IDENTITY);
    }
    cSPTransform_s005d_87a0& operator=(const cSPTransform_s005d_87a0& x);   // 0x00537DC0
    void SetRotation(const cSPMatrix3_s005d_87a0& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetTranslation(const cSPVector3_s005d_87a0& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
};
namespace EA {
namespace UTFWin {
struct IWindow_s005d_87a0 {
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
template <class T> struct AutoRefCount_s005d_87a0 {
    T* mpObject;
    AutoRefCount_s005d_87a0() : mpObject(0) {}
    AutoRefCount_s005d_87a0(const AutoRefCount_s005d_87a0& x) : mpObject(x.mpObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount_s005d_87a0() {
        if (mpObject)
            mpObject->Release();
    }
};
}
namespace SP {
struct cIModelWorld_s005d_87a0;
}
namespace SP {
struct cMWModel_s005d_87a0 {
    cIModelWorld_s005d_87a0* mWorld;   // +0x0
    uint32_t mFlags;        // +0x4 (bit 31: allocated by the world)
    char pad08[0x40 - 8];
    int mRefCount;          // +0x40
    void AddRef() { ++mRefCount; }
    void Release();
};
}
namespace SP {
struct cIModelWorld_s005d_87a0 {
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
    virtual void DestroyModel(cMWModel_s005d_87a0* pModel, bool bWorldAllocated);   // +0x170
};
}
namespace SP {
inline void cMWModel_s005d_87a0::Release()
{
    if (mRefCount > 1)
        --mRefCount;
    else
        mWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
}
namespace SP {
struct cSPEditorBlock_s005d_87a0 {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
};
}
template <> inline EA::AutoRefCount_s005d_87a0<SP::cMWModel_s005d_87a0>::~AutoRefCount_s005d_87a0()
{
    if (mpObject)
        mpObject->Release();
}
namespace eastl {
struct allocator_s005d_87a0 {
    allocator_s005d_87a0() {}
    void* allocate(uint32_t n, int flags = 0) {
        return new ("Editor", flags, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 209) char[n];
    }
    void deallocate(void* p, uint32_t) { delete[] (char*)p; }
};
}
namespace eastl {
struct sp_vector_allocator_s005d_87a0 {
    uint32_t mUnknown[2];
    void deallocate(void* p, uint32_t) {
        if (((int*)p)[-1] != 0)
            delete[] (char*)p;
    }
};
}
namespace eastl {
template <class T> inline T* uninitialized_copy_ptr(const T* pFirst, const T* pLast, T* pDest)
{
    return (T*)memcpy(pDest, pFirst, (uint32_t)((const char*)pLast - (const char*)pFirst)) + (pLast - pFirst);
}
}
namespace eastl {
template <class T, class A> struct VectorBase_s005d_87a0 {
    T* mpBegin;      // +0x0
    T* mpEnd;        // +0x4
    T* mpCapacity;   // +0x8
    A mAllocator;    // +0xc
    VectorBase_s005d_87a0(uint32_t n, const A& allocator_s005d_87a0);   // 0x0066AEC0
    ~VectorBase_s005d_87a0() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin) * sizeof(T));
    }
};
}
namespace eastl {
template <class T, class A> struct vector_s005d_87a0 : public VectorBase_s005d_87a0<T, A> {
    typedef VectorBase_s005d_87a0<T, A> base_type;
    vector_s005d_87a0();
    ~vector_s005d_87a0() {}
    vector_s005d_87a0(const vector_s005d_87a0& x) : base_type(x.size(), x.mAllocator) {
        T* pEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
        this->mpEnd = pEnd;
    }
    uint32_t size() const { return (uint32_t)(this->mpEnd - this->mpBegin); }
    T& back() { return *(this->mpEnd - 1); }
    void pop_back() { --this->mpEnd; }
};
}
namespace eastl {
template <class T1, class T2> struct pair_s005d_87a0 {
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair_s005d_87a0(const T1& x, const T2& y) : first(x), second(y) {}
};
}
namespace eastl {
template <class T> struct less_s005d_87a0 {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template <class T> struct less_s005d_87a0<EA::AutoRefCount_s005d_87a0<T> > {
    bool operator()(const EA::AutoRefCount_s005d_87a0<T>& a, const EA::AutoRefCount_s005d_87a0<T>& b) const { return a.mpObject < b.mpObject; }
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
enum RBTreeSide { kRBTreeSideLeft = 0, kRBTreeSideRight = 1 };
}
namespace eastl {
struct rbtree_node_base_s005d_87a0 {
    rbtree_node_base_s005d_87a0* mpNodeRight;    // +0x0
    rbtree_node_base_s005d_87a0* mpNodeLeft;     // +0x4
    rbtree_node_base_s005d_87a0* mpNodeParent;   // +0x8
    char mColor;                      // +0xc
};
}
namespace eastl {
template <class V> struct rbtree_node_s005d_87a0 : public rbtree_node_base_s005d_87a0 {
    V mValue;   // +0x10
};
}
namespace eastl {
rbtree_node_base_s005d_87a0* RBTreeIncrement(const rbtree_node_base_s005d_87a0* pNode);   // 0x00921580
}
namespace eastl {
void RBTreeInsert(rbtree_node_base_s005d_87a0* pNode, rbtree_node_base_s005d_87a0* pNodeParent, rbtree_node_base_s005d_87a0* pNodeAnchor, RBTreeSide insertionSide);   // 0x009216A0
}
namespace eastl {
template <class V> struct rbtree_iterator_s005d_87a0 {
    rbtree_node_s005d_87a0<V>* mpNode;
    rbtree_iterator_s005d_87a0() : mpNode(0) {}
    explicit rbtree_iterator_s005d_87a0(const rbtree_node_s005d_87a0<V>* pNode) : mpNode((rbtree_node_s005d_87a0<V>*)pNode) {}
    rbtree_iterator_s005d_87a0(const rbtree_iterator_s005d_87a0& x) : mpNode(x.mpNode) {}
    V* operator->() const { return &mpNode->mValue; }
    rbtree_iterator_s005d_87a0& operator++() {
        mpNode = (rbtree_node_s005d_87a0<V>*)RBTreeIncrement(mpNode);
        return *this;
    }
    bool operator==(const rbtree_iterator_s005d_87a0& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator_s005d_87a0& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template <class K, class T> class map_s005d_87a0 {
public:
    typedef pair_s005d_87a0<const K, T> value_type;
    typedef rbtree_node_s005d_87a0<value_type> node_type;
    typedef rbtree_iterator_s005d_87a0<value_type> iterator;
    typedef K key_type;

    less_s005d_87a0<K> mCompare;                // +0x0
    rbtree_node_base_s005d_87a0 mAnchor;        // +0x4
    uint32_t mnSize;                 // +0x14
    allocator_s005d_87a0 mAllocator;            // +0x18

    map_s005d_87a0() : mAnchor(), mnSize(0) { reset(); }
    ~map_s005d_87a0() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
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
}
namespace eastl {
template <class K, class T>
void map_s005d_87a0<K, T>::DoNukeSubtree(node_type* pNode)
{
    while (pNode) {
        DoNukeSubtree((node_type*)pNode->mpNodeRight);
        node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}
}
namespace eastl {
template <class K, class T>
T& map_s005d_87a0<K, T>::operator[](const key_type& key)
{
    iterator itLower(lower_bound(key));
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, T()));
    return itLower.mpNode->mValue.second;
}
}
namespace SP {
enum eEditorTactileType { kTactileTypeNone = 0 };
}
namespace SP {
enum eEditorTactileLerp { kTactileLerpLinear = 0, kTactileLerpSpring = 2, kTactileLerpOvershoot = 3 };
}
namespace SP {
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
}
namespace SP {
struct cSPEditorTactileTransform {
    char pad00[0x28];
    eEditorTactileType mType;     // +0x28
    eEditorTactileLerp mLerp;     // +0x2c
    float mUnknown30;             // +0x30
    float mUnknown34;             // +0x34
    cSPTransform_s005d_87a0 mHistoryValue;   // +0x38
    cSPTransform_s005d_87a0 mFinalValue;     // +0x70
    float mTimeRemaining;         // +0xa8
    float mTimeTotal;             // +0xac
    float mVelocity;              // +0xb0
    float mOverShootX;            // +0xb4
    float mOverShootScale;        // +0xb8
    unsigned int mAnimationID;    // +0xbc
    void* mUnknownC0[3];          // +0xc0
    cSPEditorTactileTransform();
};
}
namespace SP {
typedef eastl::vector_s005d_87a0<cSPEditorTactileComponent*, eastl::sp_vector_allocator_s005d_87a0> ComponentList;
}
namespace SP {
class cISPEditorTactilityManager {
public:
    virtual bool Init() = 0;
    virtual bool Shutdown() = 0;
};
}
namespace SP {
class cSPEditorTactilityManager : public cISPEditorTactilityManager {
public:
    cSPEditorTactilityManager();
    virtual ~cSPEditorTactilityManager() {}
    virtual bool Init();
    virtual bool Shutdown();
    void LerpCursor(eEditorTactileType type, float finalValue, float time, eEditorTactileLerp lerp);
    static bool __stdcall UpdateComponent(cSPEditorTactileComponent* pComponent, float* pValue, float currentValue, float deltaTime);
    static bool __stdcall UpdateComponent(cSPEditorTactileTransform* pComponent, cSPTransform_s005d_87a0* pValue, const cSPTransform_s005d_87a0& currentValue);
    static void __stdcall InitComponent(cSPEditorTactileTransform* pComponent, eEditorTactileType type, eEditorTactileLerp lerp,
                                        cSPTransform_s005d_87a0 historyValue, cSPTransform_s005d_87a0 finalValue, float time, unsigned int animationID);

    eastl::map_s005d_87a0<EA::AutoRefCount_s005d_87a0<cSPEditorBlock_s005d_87a0>, ComponentList> mBlockComponentList;                    // +0x4
    eastl::map_s005d_87a0<EA::AutoRefCount_s005d_87a0<cMWModel_s005d_87a0>, ComponentList> mModelComponentList;                          // +0x20
    eastl::map_s005d_87a0<EA::AutoRefCount_s005d_87a0<EA::UTFWin::IWindow_s005d_87a0>, ComponentList> mWindowComponentList;              // +0x3c
    eastl::map_s005d_87a0<EA::AutoRefCount_s005d_87a0<cMWModel_s005d_87a0>, EA::AutoRefCount_s005d_87a0<cIModelWorld_s005d_87a0> > mModelWorldList;            // +0x58
    eastl::map_s005d_87a0<float*, ComponentList> mFloatComponentList;                                              // +0x74
    cSPEditorTactileComponent mCursorAnimation;                                                         // +0x90
};
}
namespace eastl {
template class map_s005d_87a0<EA::AutoRefCount_s005d_87a0<SP::cSPEditorBlock_s005d_87a0>, SP::ComponentList>;
}
namespace eastl {
template class map_s005d_87a0<EA::AutoRefCount_s005d_87a0<SP::cMWModel_s005d_87a0>, SP::ComponentList>;
}
namespace eastl {
template class map_s005d_87a0<EA::AutoRefCount_s005d_87a0<EA::UTFWin::IWindow_s005d_87a0>, SP::ComponentList>;
}
namespace eastl {
template class map_s005d_87a0<EA::AutoRefCount_s005d_87a0<SP::cMWModel_s005d_87a0>, EA::AutoRefCount_s005d_87a0<SP::cIModelWorld_s005d_87a0> >;
}
namespace eastl {
template struct pair_s005d_87a0<const EA::AutoRefCount_s005d_87a0<SP::cMWModel_s005d_87a0>, SP::ComponentList>;
}
namespace eastl {
template struct pair_s005d_87a0<const EA::AutoRefCount_s005d_87a0<SP::cSPEditorBlock_s005d_87a0>, SP::ComponentList>;
}
namespace eastl {
template struct pair_s005d_87a0<const EA::AutoRefCount_s005d_87a0<EA::UTFWin::IWindow_s005d_87a0>, SP::ComponentList>;
}
namespace eastl {
template struct pair_s005d_87a0<float* const, SP::ComponentList>;
}
namespace eastl {
 template class map_s005d_87a0<float*, SP::ComponentList>; 
}
// ---- items of slice s005d87a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// @ 0x005d87a0
bool SP::cSPEditorTactilityManager::Init()
{
    mCursorAnimation.mType = SP::kTactileTypeNone;
    return true;
}

// @ 0x005d87b0
bool __stdcall SP::cSPEditorTactilityManager::UpdateComponent(SP::cSPEditorTactileComponent* pComponent, float* pValue, float currentValue, float deltaTime)
{
    float t = (pComponent->mTimeTotal - pComponent->mTimeRemaining) / pComponent->mTimeTotal;
    bool bDone = false;
    if (t >= 1.0f) {
        t = 1.0f;
        bDone = true;
    }
    switch (pComponent->mLerp) {
    case SP::kTactileLerpSpring: {
        const float finalValue = pComponent->mFinalValue;
        bool bArrived = false;
        if (fabsf(currentValue - finalValue) <= 0.005f)
            bArrived = true;
        pComponent->mVelocity = (finalValue - currentValue) + pComponent->mVelocity * 0.9f;
        *pValue = pComponent->mVelocity * deltaTime + currentValue;
        return bArrived;
    }
    case SP::kTactileLerpOvershoot:
        *pValue = (pComponent->mFinalValue - pComponent->mHistoryValue) * ((float)sin(pComponent->mOverShootX * t) * pComponent->mOverShootScale) + pComponent->mHistoryValue;
        return bDone;
    case SP::kTactileLerpLinear:
    case 1:
        *pValue = (pComponent->mFinalValue - pComponent->mHistoryValue) * t + pComponent->mHistoryValue;
        return bDone;
    default:
        *pValue = (pComponent->mFinalValue - pComponent->mHistoryValue) * t + pComponent->mHistoryValue;
        return bDone;
    }
}

// @ 0x005d88b0
void SP::cSPEditorTactilityManager::LerpCursor(SP::eEditorTactileType type, float finalValue, float time, SP::eEditorTactileLerp lerp)
{
    float historyValue;
    switch (type) {
    case 0x1002: historyValue = 0.0f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1012: historyValue = 0.1f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1013: historyValue = 0.2f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1014: historyValue = 0.3f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1015: historyValue = 0.4f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1016: historyValue = 0.5f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1017: historyValue = 0.6f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1018: historyValue = 0.7f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1019: historyValue = 0.8f; type = (SP::eEditorTactileType)0xb; break;
    case 0x101a: historyValue = 0.9f; type = (SP::eEditorTactileType)0xb; break;
    case 0x1005: historyValue = 0.0f; type = (SP::eEditorTactileType)0xc; break;
    case 0x101b: historyValue = 0.1f; type = (SP::eEditorTactileType)0xc; break;
    case 0x101c: historyValue = 0.2f; type = (SP::eEditorTactileType)0xc; break;
    case 0x101d: historyValue = 0.3f; type = (SP::eEditorTactileType)0xc; break;
    case 0x101e: historyValue = 0.4f; type = (SP::eEditorTactileType)0xc; break;
    case 0x101f: historyValue = 0.5f; type = (SP::eEditorTactileType)0xc; break;
    case 0x1020: historyValue = 0.6f; type = (SP::eEditorTactileType)0xc; break;
    case 0x1021: historyValue = 0.7f; type = (SP::eEditorTactileType)0xc; break;
    case 0x1022: historyValue = 0.8f; type = (SP::eEditorTactileType)0xc; break;
    case 0x1023: historyValue = 0.9f; type = (SP::eEditorTactileType)0xc; break;
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

// @ 0x005d8b20
bool SP::cSPEditorTactilityManager::Shutdown()
{
    for (eastl::map_s005d_87a0<EA::AutoRefCount_s005d_87a0<SP::cSPEditorBlock_s005d_87a0>, SP::ComponentList>::iterator it = mBlockComponentList.begin(); it != mBlockComponentList.end(); ++it) {
        SP::ComponentList& components = it->second;
        while (components.size() > 0) {
            delete components.back();
            components.pop_back();
        }
    }
    for (eastl::map_s005d_87a0<EA::AutoRefCount_s005d_87a0<SP::cMWModel_s005d_87a0>, SP::ComponentList>::iterator it = mModelComponentList.begin(); it != mModelComponentList.end(); ++it) {
        SP::ComponentList& components = it->second;
        while (components.size() > 0) {
            delete components.back();
            components.pop_back();
        }
    }
    for (eastl::map_s005d_87a0<float*, SP::ComponentList>::iterator it = mFloatComponentList.begin(); it != mFloatComponentList.end(); ++it) {
        SP::ComponentList& components = it->second;
        while (components.size() > 0) {
            delete components.back();
            components.pop_back();
        }
    }
    return true;
}

// @ 0x005d8c20
void __stdcall SP::cSPEditorTactilityManager::InitComponent(SP::cSPEditorTactileTransform* pComponent, SP::eEditorTactileType type, SP::eEditorTactileLerp lerp, cSPTransform_s005d_87a0 historyValue, cSPTransform_s005d_87a0 finalValue, float time, unsigned int animationID)
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

// @ 0x005d8cc0
SP::cSPEditorTactileTransform::cSPEditorTactileTransform()
{
    mUnknownC0[0] = 0;
    mUnknownC0[1] = 0;
    mUnknownC0[2] = 0;
}

// @ 0x005d8df0
namespace eastl {
template <class K, class T> typename map_s005d_87a0<K, T>::iterator map_s005d_87a0<K, T>::DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft)
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
}  // namespace eastl

// @ 0x005d8f10
bool __stdcall SP::cSPEditorTactilityManager::UpdateComponent(SP::cSPEditorTactileTransform* pComponent, cSPTransform_s005d_87a0* pValue, const cSPTransform_s005d_87a0& currentValue)
{
    float t = (pComponent->mTimeTotal - pComponent->mTimeRemaining) / pComponent->mTimeTotal;
    bool bDone = false;
    if (t >= 1.0f) {
        t = 1.0f;
        bDone = true;
    }
    cSPQuaternion_s005d_87a0 q, qTo;
    q = rw::math::fpu::QuaternionFromMatrix33(pComponent->mHistoryValue.mRotation, 0.0f);
    qTo = rw::math::fpu::QuaternionFromMatrix33(pComponent->mFinalValue.mRotation, 0.0f);
    cSPVector3_s005d_87a0 pos = pComponent->mHistoryValue.mTranslation;
    const cSPVector3_s005d_87a0 to = pComponent->mFinalValue.mTranslation;
    q = Slerp(q, qTo, t);
    pos = (to - pos) * t + pos;
    pValue->SetRotation(SP::Matrix3FromQuaternion(q));
    pValue->SetTranslation(pos);
    return bDone;
}

// @ 0x005d96d0
SP::cSPEditorTactilityManager::cSPEditorTactilityManager()
{
}

// @ 0x005db150
void FUN_005db150(void* self)
{ (void)self; }

// @ 0x005db270
void FUN_005db270(void* self)
{ (void)self; }

// @ 0x005db390
void FUN_005db390(void* self)
{ (void)self; }

// @ 0x005db650
void FUN_005db650(void* self)
{ (void)self; }
