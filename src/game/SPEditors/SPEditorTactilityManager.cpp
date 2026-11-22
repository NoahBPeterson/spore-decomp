// src/game/SPEditors/SPEditorTactilityManager.cpp -- migrated from slice(s) s0066afd0, s00669f50, s005dae60, s005d87a0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorTactilityManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cIModelWorld.h"
#include "SP/cMWModel.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cString.h"
#include "SP/cSPUIFeedListItem.h"
#include "cSPUILayout.h"
#include <string.h>
#include <intrin.h>
#include <math.h>

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
inline float fabsf_(float x) { return (float)fabs((double)x); }
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
class IWindow_s005d_87a0 { public:
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
template <class T> class AutoRefCount_s005d_87a0 { public:
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
class cIModelWorld_s005d_87a0;
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
class cIModelWorld_s005d_87a0 { public:
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
class cSPEditorBlock_s005d_87a0 { public:
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
class allocator_s005d_87a0 { public:
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
template <class T, class A> class vector_s005d_87a0 : public VectorBase_s005d_87a0<T, A> { public:
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

// ---- items of slice s00669f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { int* begin; int* end; int* cap; void m0066aec0(int count, void* src); };
void FUN_01022c60(void*, void*, void*, void*, int);
struct CtorAf {
  void* vt;              // +0
  int m4;                // +4
  int m8;                // +8
  Vec3 mC;               // +0xc
  char pad18[8];
  bool m20;              // +0x20
  bool m21;              // +0x21
  int m24, m28, m2c, m30;
  CtorAf(int p2, Vec3* p3);
};
// ---- items of slice s00669f50 end

// ---- items of slice s005dae60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kEditorAllocName[];             // 0x013EB430
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);
void FreeRawBlock(void* p);                       // 0x00F47380
struct cSPVector3_s005d_ae60 {
    float x, y, z;
    cSPVector3_s005d_ae60() {}
    cSPVector3_s005d_ae60(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    cSPVector3_s005d_ae60(const cSPVector3_s005d_ae60& v) : x(v.x), y(v.y), z(v.z) {}
    cSPVector3_s005d_ae60 operator-(const cSPVector3_s005d_ae60& v) const { return cSPVector3_s005d_ae60(x - v.x, y - v.y, z - v.z); }
    cSPVector3_s005d_ae60 operator+(const cSPVector3_s005d_ae60& v) const { return cSPVector3_s005d_ae60(x + v.x, y + v.y, z + v.z); }
    cSPVector3_s005d_ae60 operator*(float f) const { return cSPVector3_s005d_ae60(x * f, y * f, z * f); }
};
struct cSPMatrix3_s005d_ae60 {
    float m[9];
    cSPMatrix3_s005d_ae60& Assign(const cSPMatrix3_s005d_ae60& other);   // 0x0041CB40
    static const cSPMatrix3_s005d_ae60 IDENTITY;              // 0x015EF16C
};
extern const cSPVector3_s005d_ae60 kZeroVector3_s005d_ae60;              // 0x015EF03C
struct cSPTransform_s005d_ae60 {
    uint16_t mFlags;               // +0x0
    uint16_t mModificationCount;   // +0x2
    cSPVector3_s005d_ae60 mTranslation;       // +0x4
    float mScale;                  // +0x10
    cSPMatrix3_s005d_ae60 mRotation;          // +0x14
    cSPTransform_s005d_ae60() : mFlags(0), mModificationCount(0), mTranslation(kZeroVector3_s005d_ae60), mScale(1.0f) {
        mRotation.Assign(cSPMatrix3_s005d_ae60::IDENTITY);
    }
    cSPTransform_s005d_ae60& operator=(const cSPTransform_s005d_ae60& x);   // 0x00537DC0
    void SetRotation(const cSPMatrix3_s005d_ae60& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetTranslation(const cSPVector3_s005d_ae60& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
};
namespace EA {
namespace UTFWin {
class IWindow_s005d_ae60 { public:
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
template <class T> class AutoRefCount_s005d_ae60 { public:
    T* mpObject;
    AutoRefCount_s005d_ae60() : mpObject(0) {}
    AutoRefCount_s005d_ae60(const AutoRefCount_s005d_ae60& x) : mpObject(x.mpObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount_s005d_ae60() {
        if (mpObject)
            mpObject->Release();
    }
};
}
namespace SP {
class cIModelWorld_s005d_ae60;
}
namespace SP {
struct cMWModel_s005d_ae60 {
    cIModelWorld_s005d_ae60* mWorld;    // +0x0
    uint32_t mFlags;         // +0x4 (bit 31: allocated by the world)
    char pad08[0x40 - 8];    // +0x8
    int mRefCount;           // +0x40
    char pad44[0x58 - 0x44]; // +0x44
    float mColorAlpha;       // +0x58
    void AddRef() { ++mRefCount; }
    void Release();
};
}
namespace SP {
class cIModelWorld_s005d_ae60 { public:
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
    virtual void DestroyModel(cMWModel_s005d_ae60* pModel, bool bWorldAllocated);   // +0x170
};
}
namespace SP {
inline void cMWModel_s005d_ae60::Release()
{
    if (mRefCount > 1)
        --mRefCount;
    else
        mWorld->DestroyModel(this, (mFlags >> 31) & 1);
}
}
namespace SP {
class cSPEditorBlock_s005d_ae60 { public:
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    char pad08[0x10 - 8];               // +0x8
    EA::AutoRefCount_s005d_ae60<cMWModel_s005d_ae60> mModel;  // +0x10
    char pad14[0x48 - 0x14];            // +0x14
    cSPVector3_s005d_ae60 mPosition;               // +0x48
    char pad54[0x60 - 0x54];            // +0x54
    cSPMatrix3_s005d_ae60 mOrientation;            // +0x60
    char pad84[0x1d8 - 0x84];           // +0x84
    float mUniformScale;                // +0x1d8
};
}
template <> inline EA::AutoRefCount_s005d_ae60<SP::cMWModel_s005d_ae60>::~AutoRefCount_s005d_ae60()
{
    if (mpObject)
        mpObject->Release();
}
namespace eastl {
class allocator_s005d_ae60 { public:
    allocator_s005d_ae60() {}
    void* allocate(uint32_t n, int flags = 0) {
        return new ("Editor", flags, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 209) char[n];
    }
    void deallocate(void* p, uint32_t) { delete[] (char*)p; }
};
}
namespace eastl {
struct sp_vector_allocator_s005d_ae60 {
    uint32_t mUnknown[2];
    void deallocate(void* p, uint32_t) {
        if (((int*)p)[-1] != 0)
            delete[] (char*)p;
    }
};
}
namespace eastl {
template <class T, class A> struct VectorBase_s005d_ae60 {
    T* mpBegin;      // +0x0
    T* mpEnd;        // +0x4
    T* mpCapacity;   // +0x8
    A mAllocator;    // +0xc
    VectorBase_s005d_ae60(uint32_t n, const A& allocator_s005d_ae60);   // 0x0066AEC0
    ~VectorBase_s005d_ae60() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (uint32_t)(mpCapacity - mpBegin) * sizeof(T));
    }
};
}
namespace eastl {
template <class T, class A> class vector_s005d_ae60 : public VectorBase_s005d_ae60<T, A> { public:
    typedef VectorBase_s005d_ae60<T, A> base_type;
    vector_s005d_ae60();
    ~vector_s005d_ae60() {}
    vector_s005d_ae60(const vector_s005d_ae60& x) : base_type(x.size(), x.mAllocator) {
        T* pEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
        this->mpEnd = pEnd;
    }
    uint32_t size() const { return (uint32_t)(this->mpEnd - this->mpBegin); }
    T& back() { return *(this->mpEnd - 1); }
    void pop_back() { --this->mpEnd; }
    void clear() {
        if (this->mpBegin) {
            this->mAllocator.deallocate(this->mpBegin, (uint32_t)(this->mpCapacity - this->mpBegin) * sizeof(T));
            this->mpBegin = 0;
            this->mpEnd = 0;
            this->mpCapacity = 0;
        }
    }
    void push_back(const T& value) {
        if (this->mpEnd < this->mpCapacity) {
            *this->mpEnd = value;
            ++this->mpEnd;
        } else {
            DoInsertValue(this->mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
        }
    }
    void DoInsertValue(T* position, const T& value);   // 0x00630B30
    vector_s005d_ae60& operator=(const vector_s005d_ae60& x) {
        if (this != &x) {
            clear();
            uint32_t n = x.size();
            if (n) {
                this->mpBegin = (T*)operator new(n * sizeof(T), kEditorAllocName, 0, 0, 0, 0);
                uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
                this->mpEnd = this->mpBegin + n;
                this->mpCapacity = this->mpBegin + n;
            }
        }
        return *this;
    }
};
}
namespace eastl {
template <class T1, class T2> struct pair_s005d_ae60 {
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair_s005d_ae60(const T1& x, const T2& y) : first(x), second(y) {}
};
}
namespace eastl {
template <class T> struct less_s005d_ae60 {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
}
namespace eastl {
template <class T> struct less_s005d_ae60<EA::AutoRefCount_s005d_ae60<T> > {
    bool operator()(const EA::AutoRefCount_s005d_ae60<T>& a, const EA::AutoRefCount_s005d_ae60<T>& b) const { return a.mpObject < b.mpObject; }
};
}
namespace eastl {
struct rbtree_node_base_s005d_ae60 {
    rbtree_node_base_s005d_ae60* mpNodeRight;    // +0x0
    rbtree_node_base_s005d_ae60* mpNodeLeft;     // +0x4
    rbtree_node_base_s005d_ae60* mpNodeParent;   // +0x8
    char mColor;                      // +0xc
};
}
namespace eastl {
template <class V> struct rbtree_node_s005d_ae60 : public rbtree_node_base_s005d_ae60 {
    V mValue;   // +0x10
};
}
namespace eastl {
rbtree_node_base_s005d_ae60* RBTreeIncrement(const rbtree_node_base_s005d_ae60* pNode);   // 0x00921580
}
namespace eastl {
void RBTreeInsert(rbtree_node_base_s005d_ae60* pNode, rbtree_node_base_s005d_ae60* pNodeParent, rbtree_node_base_s005d_ae60* pNodeAnchor, RBTreeSide insertionSide);   // 0x009216A0
}
namespace eastl {
void RBTreeErase(rbtree_node_base_s005d_ae60* pNode, rbtree_node_base_s005d_ae60* pNodeAnchor);   // 0x00921880
}
namespace eastl {
template <class V> struct rbtree_iterator_s005d_ae60 {
    rbtree_node_s005d_ae60<V>* mpNode;
    rbtree_iterator_s005d_ae60() : mpNode(0) {}
    explicit rbtree_iterator_s005d_ae60(const rbtree_node_s005d_ae60<V>* pNode) : mpNode((rbtree_node_s005d_ae60<V>*)pNode) {}
    rbtree_iterator_s005d_ae60(const rbtree_iterator_s005d_ae60& x) : mpNode(x.mpNode) {}
    V* operator->() const { return &mpNode->mValue; }
    rbtree_iterator_s005d_ae60& operator++() {
        mpNode = (rbtree_node_s005d_ae60<V>*)RBTreeIncrement(mpNode);
        return *this;
    }
    bool operator==(const rbtree_iterator_s005d_ae60& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator_s005d_ae60& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template <class K, class T> class map_s005d_ae60 {
public:
    typedef pair_s005d_ae60<const K, T> value_type;
    typedef rbtree_node_s005d_ae60<value_type> node_type;
    typedef rbtree_iterator_s005d_ae60<value_type> iterator;
    typedef K key_type;

    less_s005d_ae60<K> mCompare;                // +0x0
    rbtree_node_base_s005d_ae60 mAnchor;        // +0x4
    uint32_t mnSize;                 // +0x14
    allocator_s005d_ae60 mAllocator;            // +0x18

    map_s005d_ae60() : mAnchor(), mnSize(0) { reset(); }
    ~map_s005d_ae60() { DoNukeSubtree((node_type*)mAnchor.mpNodeParent); }
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
    iterator find(const key_type& key) {
        iterator it = lower_bound(key);
        if (it == end() || mCompare(key, it.mpNode->mValue.first))
            return end();
        return it;
    }
    T& operator[](const key_type& key);
    iterator insert(iterator position, const value_type& value) { return DoInsertValue(position, value, true_type()); }
    iterator erase(iterator position);

    iterator DoInsertValue(iterator position, const value_type& value, true_type);
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
void map_s005d_ae60<K, T>::DoNukeSubtree(node_type* pNode)
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
typename map_s005d_ae60<K, T>::iterator map_s005d_ae60<K, T>::erase(iterator position)
{
    const iterator iErase(position);
    --mnSize;
    ++position;
    RBTreeErase(iErase.mpNode, &mAnchor);
    DoFreeNode(iErase.mpNode);
    return position;
}
}
namespace eastl {
template <class K, class T>
typename map_s005d_ae60<K, T>::iterator map_s005d_ae60<K, T>::DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft)
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
}
namespace SP {
enum eEditorTactileType_s005d_ae60 {
    kTactileTypeNone_s005d_ae60 = 0,
    kTactileTypeColorRed = 1,
    kTactileTypeColorGreen = 2,
    kTactileTypeColorBlue = 3,
    kTactileTypeColorAlpha = 4,
    kTactileTypePositionX = 5,
    kTactileTypePositionY = 6,
    kTactileTypePositionZ = 7,
    kTactileTypeUniformScale = 8,
    kTactileTypeAnimation = 9,
    kTactileTypeFloat = 10,
    kTactileTypeLightDirectionX = 11,
    kTactileTypeLightDirectionY = 12,
    kTactileTypeLightDirectionZ = 13,
    kTactileTypeShadowDarkness = 14,
    kTactileTypeCursorDefault = 15,
    kTactileTypeCursorCross = 16,
    kTactileTypeTransform = 17,
};
}
namespace SP {
enum eEditorTactileLerp_s005d_ae60 {
    kTactileLerpFromCurrent = 0,
    kTactileLerpFromHistory = 1,
    kTactileSpringFromCurrent = 2,
    kTactileSineSpringFromHistory = 3,
};
}
namespace SP {
struct cSPEditorTactileComponent_s005d_ae60 {
    eEditorTactileType_s005d_ae60 mType;   // +0x00
    eEditorTactileLerp_s005d_ae60 mLerp;   // +0x04
    float mHistoryValue;        // +0x08
    float mFinalValue;          // +0x0c
    float mTimeRemaining;       // +0x10
    float mTimeTotal;           // +0x14
    float mVelocity;            // +0x18
    float mOverShootX;          // +0x1c
    float mOverShootScale;      // +0x20
    unsigned int mAnimationID;  // +0x24
};
}
namespace SP {
typedef eastl::vector_s005d_ae60<cSPEditorTactileComponent_s005d_ae60*, eastl::sp_vector_allocator_s005d_ae60> ComponentList_s005d_ae60;
}
namespace SP {
struct cSPEditorTactileTransformComponent {
    char pad00[0xc0];
    eastl::vector_s005d_ae60<EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60>, eastl::sp_vector_allocator_s005d_ae60> mPileList;  // +0xc0
};
}
namespace SP {
class cISPEditorTactilityManager_s005d_ae60 {
public:
    virtual bool Init();
    virtual bool Shutdown();
};
}
namespace SP {
class cSPEditorTactilityManager_s005d_ae60 : public cISPEditorTactilityManager_s005d_ae60 {
public:
    void SetTargetValue(EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60> block, eEditorTactileType_s005d_ae60 type, float arg3, float arg4, eEditorTactileLerp_s005d_ae60 lerp);
    void LerpBlockValue(EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60> block, eEditorTactileType_s005d_ae60 type, float arg3, float arg4, eEditorTactileLerp_s005d_ae60 lerp);
    void LerpBlockTransform(EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60> block,
                            eastl::vector_s005d_ae60<EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60>, eastl::sp_vector_allocator_s005d_ae60> blocks,
                            cSPTransform_s005d_ae60 transform, float time, eEditorTactileLerp_s005d_ae60 lerp);
    void LerpFloat(float* pValue, float finalValue, float time, eEditorTactileLerp_s005d_ae60 lerp);
    void InitComponent(cSPEditorTactileTransformComponent* pComponent, eEditorTactileType_s005d_ae60 type, eEditorTactileLerp_s005d_ae60 lerp,
                       cSPTransform_s005d_ae60 historyValue, cSPTransform_s005d_ae60 finalValue, float time, unsigned int animationID);   // 0x005d8c20

    eastl::map_s005d_ae60<EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60>, ComponentList_s005d_ae60> mBlockComponentList;                     // +0x04
    eastl::map_s005d_ae60<EA::AutoRefCount_s005d_ae60<cMWModel_s005d_ae60>, ComponentList_s005d_ae60> mModelComponentList;                           // +0x20
    eastl::map_s005d_ae60<EA::AutoRefCount_s005d_ae60<EA::UTFWin::IWindow_s005d_ae60>, ComponentList_s005d_ae60> mWindowComponentList;               // +0x3c
    eastl::map_s005d_ae60<EA::AutoRefCount_s005d_ae60<cMWModel_s005d_ae60>, EA::AutoRefCount_s005d_ae60<cIModelWorld_s005d_ae60> > mModelWorldList;             // +0x58
    eastl::map_s005d_ae60<float*, ComponentList_s005d_ae60> mFloatComponentList;                                               // +0x74
    cSPEditorTactileComponent_s005d_ae60 mCursorAnimation;                                                          // +0x90
};
}
#define PV(n) virtual void pv##n();
struct TactileSource {
    void* mComponent;                              // +0x00
    int mField4;                                   // +0x04
    int mField8;                                   // +0x08
    float mField0c;                                // +0x0c
    float mField10;                                // +0x10
    float mField14;                                // +0x14
    char mPad18[0x28];                             // +0x18 .. +0x3f
    int mRefCount;                                 // +0x40
    char mPad44[8];                                // +0x44 .. +0x4b
    float mField4c;                                // +0x4c
    float mField50;                                // +0x50
    float mField54;                                // +0x54
    float mField58;                                // +0x58
};
class TactileComponentObject {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33)
    PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44)
    PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55)
    PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66)
    PV(67) PV(68) PV(69) PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77)
    PV(78) PV(79) PV(80) PV(81) PV(82) PV(83) PV(84) PV(85) PV(86) PV(87) PV(88)
    PV(89) PV(90) PV(91)
    virtual void Destroy(TactileSource* source, int flag);  // +0x170
};
struct TactileComponent {
    uint32_t mType;                                // +0x00
    int mID;                                       // +0x04
    float mValue;                                  // +0x08
    float mArgA;                                   // +0x0c
    float mArgB;                                   // +0x10
    float mArgC;                                   // +0x14
    float mZero;                                   // +0x18
    float mPhase;                                  // +0x1c
    float mZero2;                                  // +0x20
    int mZero3;                                    // +0x24
};
struct TactileVector {
    TactileComponent** mpBegin;                    // +0x00
    TactileComponent** mpEnd;                      // +0x04
    TactileComponent** mpCapacity;                 // +0x08
    unsigned int mAllocator;                       // +0x0c
    void Construct(int count, void* allocator_s005d_ae60);    // 0x0066aec0
    void Grow(TactileComponent** end, TactileComponent** value);  // 0x00630b30
};
struct TactileMap {
    TactileVector* Find(TactileSource** key);      // 0x005daf10
};
struct TactileOwner {
    char mPad00[0x20];
    TactileMap mMap;                               // +0x20
    void Add(TactileSource* source, int type, float arg2, float arg3, int arg4);
};
// ---- items of slice s005dae60 end

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
        if (fabsf_(currentValue - finalValue) <= 0.005f)
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
    SP::eEditorTactileType newType;
    switch (type) {
    case 0x1002: historyValue = 0.0f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1012: historyValue = 0.1f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1013: historyValue = 0.2f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1014: historyValue = 0.3f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1015: historyValue = 0.4f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1016: historyValue = 0.5f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1017: historyValue = 0.6f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1018: historyValue = 0.7f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1019: historyValue = 0.8f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x101a: historyValue = 0.9f; newType = (SP::eEditorTactileType)0xb; break;
    case 0x1005: historyValue = 0.0f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x101b: historyValue = 0.1f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x101c: historyValue = 0.2f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x101d: historyValue = 0.3f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x101e: historyValue = 0.4f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x101f: historyValue = 0.5f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x1020: historyValue = 0.6f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x1021: historyValue = 0.7f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x1022: historyValue = 0.8f; newType = (SP::eEditorTactileType)0xc; break;
    case 0x1023: historyValue = 0.9f; newType = (SP::eEditorTactileType)0xc; break;
    default: break;
    }
    mCursorAnimation.mHistoryValue = historyValue;
    mCursorAnimation.mFinalValue = finalValue;
    mCursorAnimation.mTimeRemaining = time;
    mCursorAnimation.mTimeTotal = time;
    mCursorAnimation.mType = newType;
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

// @ 0x005dae60
namespace eastl {
template <> SP::ComponentList_s005d_ae60& map_s005d_ae60<EA::AutoRefCount_s005d_ae60<SP::cSPEditorBlock_s005d_ae60>, SP::ComponentList_s005d_ae60>::operator[](const EA::AutoRefCount_s005d_ae60<SP::cSPEditorBlock_s005d_ae60>& key)
{
    iterator itLower = lower_bound(key);
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, SP::ComponentList_s005d_ae60()));
    return itLower.mpNode->mValue.second;
}
}  // namespace eastl

// @ 0x005daf10
namespace eastl {
template <> SP::ComponentList_s005d_ae60& map_s005d_ae60<EA::AutoRefCount_s005d_ae60<SP::cMWModel_s005d_ae60>, SP::ComponentList_s005d_ae60>::operator[](const EA::AutoRefCount_s005d_ae60<SP::cMWModel_s005d_ae60>& key)
{
    iterator itLower = lower_bound(key);
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, SP::ComponentList_s005d_ae60()));
    return itLower.mpNode->mValue.second;
}
}  // namespace eastl

// @ 0x005daff0
namespace eastl {
template <> SP::ComponentList_s005d_ae60& map_s005d_ae60<EA::AutoRefCount_s005d_ae60<EA::UTFWin::IWindow_s005d_ae60>, SP::ComponentList_s005d_ae60>::operator[](const EA::AutoRefCount_s005d_ae60<EA::UTFWin::IWindow_s005d_ae60>& key)
{
    iterator itLower = lower_bound(key);
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, SP::ComponentList_s005d_ae60()));
    return itLower.mpNode->mValue.second;
}
}  // namespace eastl

// @ 0x005db0a0
namespace eastl {
template <> SP::ComponentList_s005d_ae60& map_s005d_ae60<float*, SP::ComponentList_s005d_ae60>::operator[](float* const& key)
{
    iterator itLower = lower_bound(key);
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, SP::ComponentList_s005d_ae60()));
    return itLower.mpNode->mValue.second;
}
}  // namespace eastl

// @ 0x005db150
namespace SP {
void cSPEditorTactilityManager_s005d_ae60::SetTargetValue(EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60> block, eEditorTactileType_s005d_ae60 type, float arg3, float arg4, eEditorTactileLerp_s005d_ae60 lerp)
{
    float value = (type == kTactileTypeUniformScale) ? block.mpObject->mUniformScale : 0.0f;
    cSPEditorTactileComponent_s005d_ae60* c = (cSPEditorTactileComponent_s005d_ae60*)operator new(0x28, kEditorAllocName, 0, 0, 0, 0);
    c->mHistoryValue = value;
    c->mFinalValue = arg3;
    c->mTimeRemaining = arg4;
    c->mTimeTotal = arg4;
    c->mVelocity = 0.1f;
    c->mType = type;
    c->mLerp = lerp;
    c->mOverShootScale = 1.1f;
    c->mOverShootX = 3.1415927f - asinf_(0.9090908893868948f);
    c->mAnimationID = 0;

    eastl::map_s005d_ae60<EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60>, ComponentList_s005d_ae60>::iterator it = mBlockComponentList.find(block);
    if (it != mBlockComponentList.end())
        mBlockComponentList.erase(it);
    mBlockComponentList[block].push_back(c);
}
}  // namespace SP

// @ 0x005db270
namespace SP {
void cSPEditorTactilityManager_s005d_ae60::LerpBlockValue(EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60> block, eEditorTactileType_s005d_ae60 type, float arg3, float arg4, eEditorTactileLerp_s005d_ae60 lerp)
{
    float value;
    switch (type) {
    case kTactileTypeColorAlpha: value = block.mpObject->mModel.mpObject->mColorAlpha; break;
    case kTactileTypePositionX:  value = block.mpObject->mPosition.x; break;
    case kTactileTypePositionY:  value = block.mpObject->mPosition.y; break;
    case kTactileTypePositionZ:  value = block.mpObject->mPosition.z; break;
    default: break;
    }
    cSPEditorTactileComponent_s005d_ae60* c = (cSPEditorTactileComponent_s005d_ae60*)operator new(0x28, kEditorAllocName, 0, 0, 0, 0);
    c->mHistoryValue = value;
    c->mFinalValue = arg3;
    c->mTimeRemaining = arg4;
    c->mTimeTotal = arg4;
    c->mVelocity = 0.0f;
    c->mType = type;
    c->mLerp = lerp;
    c->mOverShootScale = 1.1f;
    c->mOverShootX = 3.1415927f - asinf_(0.9090908893868948f);
    c->mAnimationID = 0;
    mBlockComponentList[block].push_back(c);
}
}  // namespace SP

// @ 0x005db390
namespace SP {
void cSPEditorTactilityManager_s005d_ae60::LerpBlockTransform(EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60> block, eastl::vector_s005d_ae60<EA::AutoRefCount_s005d_ae60<cSPEditorBlock_s005d_ae60>, eastl::sp_vector_allocator_s005d_ae60> blocks, cSPTransform_s005d_ae60 transform, float time, eEditorTactileLerp_s005d_ae60 lerp)
{
    cSPEditorTactileTransformComponent* c =
        (cSPEditorTactileTransformComponent*)operator new(0xd4, kEditorAllocName, 0, 0, 0, 0);
    cSPTransform_s005d_ae60 history;
    history.SetTranslation(block.mpObject->mPosition);
    history.SetRotation(block.mpObject->mOrientation);
    history.mScale = block.mpObject->mUniformScale;
    InitComponent(c, kTactileTypeTransform, lerp, history, transform, time, 0);
    c->mPileList = blocks;
    mBlockComponentList[block].push_back(reinterpret_cast<cSPEditorTactileComponent_s005d_ae60*>(c));
}
}  // namespace SP

// @ 0x005db580
namespace SP {
void cSPEditorTactilityManager_s005d_ae60::LerpFloat(float* pValue, float finalValue, float time, eEditorTactileLerp_s005d_ae60 lerp)
{
    cSPEditorTactileComponent_s005d_ae60* c = (cSPEditorTactileComponent_s005d_ae60*)operator new(0x28, kEditorAllocName, 0, 0, 0, 0);
    c->mHistoryValue = *pValue;
    c->mFinalValue = finalValue;
    c->mTimeRemaining = time;
    c->mTimeTotal = time;
    c->mVelocity = 0.0f;
    c->mType = kTactileTypeFloat;
    c->mLerp = lerp;
    c->mOverShootScale = 1.1f;
    c->mOverShootX = 3.1415927f - asinf_(0.9090908893868948f);
    c->mAnimationID = 0;
    mFloatComponentList[pValue].push_back(c);
}
}  // namespace SP

// @ 0x005db650
void TactileOwner::Add(TactileSource* source, int type, float arg2, float arg3, int arg4)
{
    float value;
    switch (type) {
    case 1: value = source->mField58; break;
    case 2: value = source->mField4c; break;
    case 3: value = source->mField50; break;
    case 4: value = source->mField54; break;
    case 5: value = source->mField0c; break;
    case 6: value = source->mField10; break;
    case 7: value = source->mField14; break;
    }

    TactileVector* vec = mMap.Find(&source);
    int count = (int)(vec->mpEnd - vec->mpBegin);
    TactileVector temp;
    temp.Construct(count, &vec->mAllocator);
    memcpy(temp.mpBegin, vec->mpBegin,
           (unsigned int)((char*)vec->mpEnd - (char*)vec->mpBegin));

    TactileComponent* found = 0;
    for (int i = 0; i < count; ++i) {
        TactileComponent* c = temp.mpBegin[i];
        if (c != 0 && c->mType == (uint32_t)type) {
            found = c;
            break;
        }
    }

    if (found != 0) {
        found->mType = (uint32_t)type;
        found->mID = arg4;
        found->mValue = value;
        found->mArgA = arg2;
        found->mArgB = arg3;
        found->mArgC = arg3;
        found->mZero = 0.0f;
        found->mZero2 = 0.0f;
        found->mZero3 = 0;
        found->mPhase = (float)(1.0f - asin(0.9090908893868948));
    } else {
        TactileComponent* c =
            (TactileComponent*)operator new(0x28, kEditorAllocName, 0, 0, 0, 0);
        c->mType = (uint32_t)type;
        c->mID = arg4;
        c->mValue = value;
        c->mArgA = arg2;
        c->mArgB = arg3;
        c->mArgC = arg3;
        c->mZero = 0.0f;
        c->mZero2 = 0.0f;
        c->mZero3 = 0;
        c->mPhase = (float)(1.0f - asin(0.9090908893868948));

        vec = mMap.Find(&source);
        if (vec->mpEnd < vec->mpCapacity) {
            *vec->mpEnd = c;
            vec->mpEnd = vec->mpEnd + 1;
        } else {
            vec->Grow(vec->mpEnd, &c);
        }
    }

    if (temp.mpBegin != 0 && *((int*)temp.mpBegin - 1) != 0)
        FreeRawBlock(temp.mpBegin);

    if (source != 0) {
        if (source->mRefCount > 1) {
            source->mRefCount = source->mRefCount - 1;
        } else {
            TactileComponentObject* component =
                (TactileComponentObject*)source->mComponent;
            component->Destroy(source,
                               (int)(((unsigned int)source->mField4 >> 31) & 1));
        }
    }
}

// @ 0x0066af20
CtorAf::CtorAf(int p2, Vec3* p3)
{
  m4 = 0;
  vt = (void*)0x1400620;
  m8 = p2;
  Vec3& c = mC;
  c.m0066aec0((int)(p3->end - p3->begin), (void*)((char*)p3 + 0xc));
  // uninitialized_copy_impl returns the new end through its hidden first argument; the trailing tag
  // argument is a by-value empty false_type, so retail pushes whatever was left in the register
  // (p2, which is dead by then) and never reads it.
  void* out;
  FUN_01022c60(&out, p3->begin, p3->end, c.begin, p2);
  c.end = (int*)out;
  // retail stores mC.end before the flag stores below; without this cl sinks it past them
  _ReadWriteBarrier();
  m20 = false;
  m24 = 0;
  m21 = true;
  m28 = 0;
  m2c = 0;
  m30 = 0;
}

// @ 0x0066b130
void __fastcall FUN_0066b130(void* self)
{
    (void)self;   // large layout/animation builder omitted
}
