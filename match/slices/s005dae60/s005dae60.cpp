#include "types.h"
#include <math.h>

extern "C" void* memcpy(void* dst, const void* src, unsigned int n);
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);
void FreeRawBlock(void* p);                       // 0x00F47380
extern const char kEditorAllocName[];             // 0x013EB430

// Slice s005dae60: SP editor subsystem widgets / Eastl map-operator[] instantiations.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (this module has no /EHsc; confirmed by chk).
//
//   005dae60  eastl::map<AutoRefCount<cMWModel>, vector<cSPEditorTactileComponent*>>::operator[]
//   005daf10  ... (second instantiation)
//   005daff0  ... (third)
//   005db0a0  ... (fourth)
//   005db150  editor feedback-event registration (rbtree + vector push)
//   005db270  ...
//   005db390  ...
//   005db580  ...
//   005db650  ...
//   005dbb50  small UI helper
//   005dbb60  small UI widget create (2 values)
//   005dbbb0  small UI widget create (3 values, mode 4)
//   005dbc10  small UI widget create (3 values, mode 0)
//   005dbc70  UTFInternet::HTTPRequest ctor

// ---------------------------------------------------------------------------------------------
// external callees (signatures chosen so the call sites reproduce the original stack traffic)
void* __cdecl FUN_0067de90();                 // global getter
struct Handler7ebce0 { void f(int); };        // 0x7ebce0
struct Handler7ec160 { void* f(int, int); };  // 0x7ec160
struct Handler7eb820 { void f(int); };        // 0x7eb820

struct Editor {
    void* FUN_005dbb60(int p2);
    void FUN_005dbbb0(int p2);
    void FUN_005dbc10(int p2);
};

// @ 0x005dbb50
void FUN_005dbb50()
{
    ((Handler7ebce0*)FUN_0067de90())->f(-1);
}

// @ 0x005dbb60
void* Editor::FUN_005dbb60(int p2)
{
    void* o = ((Handler7ec160*)FUN_0067de90())->f(5, p2);
    if (o) {
        ((Handler7eb820*)o)->f(2);
        *(uint32_t*)*(uint32_t*)((char*)o + 0xc) = *(uint32_t*)((char*)this + 0x448);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 4) =
            *(uint32_t*)(*(uint32_t*)((char*)this + 0x98) + 0x58);
    }
    return o;
}

// @ 0x005dbbb0
void Editor::FUN_005dbbb0(int p2)
{
    void* o = ((Handler7ec160*)FUN_0067de90())->f(5, 4);
    if (o) {
        ((Handler7eb820*)o)->f(2);
        *(uint32_t*)*(uint32_t*)((char*)o + 0xc) = *(uint32_t*)((char*)this + 0x448);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 4) =
            *(uint32_t*)(*(uint32_t*)((char*)this + 0x98) + 0x58);
        ((Handler7eb820*)o)->f(3);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 8) = (uint32_t)p2;
    }
}

// @ 0x005dbc10
void Editor::FUN_005dbc10(int p2)
{
    void* o = ((Handler7ec160*)FUN_0067de90())->f(5, 0);
    if (o) {
        ((Handler7eb820*)o)->f(2);
        *(uint32_t*)*(uint32_t*)((char*)o + 0xc) = *(uint32_t*)((char*)this + 0x448);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 4) =
            *(uint32_t*)(*(uint32_t*)((char*)this + 0x98) + 0x58);
        ((Handler7eb820*)o)->f(3);
        *(uint32_t*)(*(uint32_t*)((char*)o + 0xc) + 8) = (uint32_t)p2;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x005dbc70  UTFInternet::HTTPRequest::HTTPRequest
// Complete, but 24 bytes off: cl schedules the 0.2f constant load late (in the zero-fill
// loop) where the original hoisted it right after the +0x1c store.
namespace UTFInternet {
struct HTTPRequest {
    virtual ~HTTPRequest();
    uint32_t pad04[3];       // +0x04
    float m10;               // +0x10
    float m14;               // +0x14
    float m18;               // +0x18
    float m1c;               // +0x1c
    uint32_t pad20[0x10];    // +0x20 .. +0x5f
    uint32_t m60[21];        // +0x60 .. +0xb3
    float mB4;               // +0xb4
    HTTPRequest();
};
HTTPRequest::HTTPRequest()
{
    m10 = 1.0f;
    m14 = 1.0f;
    m18 = 0.25f;
    m1c = 1.0f;
    for (int i = 0; i < 21; ++i)
        m60[i] = 0;
    mB4 = 0.2f;
}
}

// ---------------------------------------------------------------------------------------------
// Behavioural reconstruction of the editor's tactile-component maps.  Retail instantiates a
// newer EASTL rbtree than the bundled one (its map::operator[] runs through DoInsertKey /
// DoCreateNodeFromKey), so the four operator[] entry points below and the three registration
// methods that use them are not byte-reproducible; they are recorded in nonmatching.txt.

inline void* operator new(unsigned int, void* p) throw() { return p; }
void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);   // 0x00F473A0
void operator delete(void* p) throw();      // 0x00F47380
void operator delete[](void* p) throw();    // 0x00F47380
inline float asinf_(float x) { return (float)asin((double)x); }

// ---- math types -----------------------------------------------------------------------------
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

// ---- ref-counted handles --------------------------------------------------------------------
namespace EA {
namespace UTFWin {
class IWindow { public:
    virtual int AddRef();
    virtual int Release();
};
}
template <class T> class AutoRefCount { public:
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
class cIModelWorld;
struct cMWModel {
    cIModelWorld* mWorld;    // +0x0
    uint32_t mFlags;         // +0x4 (bit 31: allocated by the world)
    char pad08[0x40 - 8];    // +0x8
    int mRefCount;           // +0x40
    char pad44[0x58 - 0x44]; // +0x44
    float mColorAlpha;       // +0x58
    void AddRef() { ++mRefCount; }
    void Release();
};
class cIModelWorld { public:
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
class cSPEditorBlock { public:
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    char pad08[0x10 - 8];               // +0x8
    EA::AutoRefCount<cMWModel> mModel;  // +0x10
    char pad14[0x48 - 0x14];            // +0x14
    cSPVector3 mPosition;               // +0x48
    char pad54[0x60 - 0x54];            // +0x54
    cSPMatrix3 mOrientation;            // +0x60
    char pad84[0x1d8 - 0x84];           // +0x84
    float mUniformScale;                // +0x1d8
};
}
template <> inline EA::AutoRefCount<SP::cMWModel>::~AutoRefCount()
{
    if (mpObject)
        mpObject->Release();
}

// ---- EASTL pieces ---------------------------------------------------------------------------
namespace eastl {
class allocator { public:
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
template <class T, class A> class vector : public VectorBase<T, A> { public:
    typedef VectorBase<T, A> base_type;
    vector();
    ~vector() {}
    vector(const vector& x) : base_type(x.size(), x.mAllocator) {
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
            DoInsertValue(this->mpEnd, value);
        }
    }
    void DoInsertValue(T* position, const T& value);   // 0x00630B30
    vector& operator=(const vector& x) {
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
}

// ---- editor tactile types -------------------------------------------------------------------
namespace SP {
enum eEditorTactileType {
    kTactileTypeNone = 0,
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
enum eEditorTactileLerp {
    kTactileLerpFromCurrent = 0,
    kTactileLerpFromHistory = 1,
    kTactileSpringFromCurrent = 2,
    kTactileSineSpringFromHistory = 3,
};

struct cSPEditorTactileComponent {
    eEditorTactileType mType;   // +0x00
    eEditorTactileLerp mLerp;   // +0x04
    float mHistoryValue;        // +0x08
    float mFinalValue;          // +0x0c
    float mTimeRemaining;       // +0x10
    float mTimeTotal;           // +0x14
    float mVelocity;            // +0x18
    float mOverShootX;          // +0x1c
    float mOverShootScale;      // +0x20
    unsigned int mAnimationID;  // +0x24
};

typedef eastl::vector<cSPEditorTactileComponent*, eastl::sp_vector_allocator> ComponentList;

// Transform-valued tactile animation (retail layout: 0xd4, mPileList at +0xc0).
struct cSPEditorTactileTransformComponent {
    char pad00[0xc0];
    eastl::vector<EA::AutoRefCount<cSPEditorBlock>, eastl::sp_vector_allocator> mPileList;  // +0xc0
};

class cISPEditorTactilityManager {
public:
    virtual bool Init();
    virtual bool Shutdown();
};

class cSPEditorTactilityManager : public cISPEditorTactilityManager {
public:
    void SetTargetValue(EA::AutoRefCount<cSPEditorBlock> block, eEditorTactileType type, float arg3, float arg4, eEditorTactileLerp lerp);
    void LerpBlockValue(EA::AutoRefCount<cSPEditorBlock> block, eEditorTactileType type, float arg3, float arg4, eEditorTactileLerp lerp);
    void LerpBlockTransform(EA::AutoRefCount<cSPEditorBlock> block,
                            eastl::vector<EA::AutoRefCount<cSPEditorBlock>, eastl::sp_vector_allocator> blocks,
                            cSPTransform transform, float time, eEditorTactileLerp lerp);
    void LerpFloat(float* pValue, float finalValue, float time, eEditorTactileLerp lerp);
    void InitComponent(cSPEditorTactileTransformComponent* pComponent, eEditorTactileType type, eEditorTactileLerp lerp,
                       cSPTransform historyValue, cSPTransform finalValue, float time, unsigned int animationID);   // 0x005d8c20

    eastl::map<EA::AutoRefCount<cSPEditorBlock>, ComponentList> mBlockComponentList;                     // +0x04
    eastl::map<EA::AutoRefCount<cMWModel>, ComponentList> mModelComponentList;                           // +0x20
    eastl::map<EA::AutoRefCount<EA::UTFWin::IWindow>, ComponentList> mWindowComponentList;               // +0x3c
    eastl::map<EA::AutoRefCount<cMWModel>, EA::AutoRefCount<cIModelWorld> > mModelWorldList;             // +0x58
    eastl::map<float*, ComponentList> mFloatComponentList;                                               // +0x74
    cSPEditorTactileComponent mCursorAnimation;                                                          // +0x90
};
}

// ---- the four map::operator[] entry points --------------------------------------------------
namespace eastl {
// @ 0x005dae60
template <>
SP::ComponentList& map<EA::AutoRefCount<SP::cSPEditorBlock>, SP::ComponentList>::operator[](const EA::AutoRefCount<SP::cSPEditorBlock>& key)
{
    iterator itLower = lower_bound(key);
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, SP::ComponentList()));
    return itLower.mpNode->mValue.second;
}

// @ 0x005daf10
template <>
SP::ComponentList& map<EA::AutoRefCount<SP::cMWModel>, SP::ComponentList>::operator[](const EA::AutoRefCount<SP::cMWModel>& key)
{
    iterator itLower = lower_bound(key);
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, SP::ComponentList()));
    return itLower.mpNode->mValue.second;
}

// @ 0x005daff0
template <>
SP::ComponentList& map<EA::AutoRefCount<EA::UTFWin::IWindow>, SP::ComponentList>::operator[](const EA::AutoRefCount<EA::UTFWin::IWindow>& key)
{
    iterator itLower = lower_bound(key);
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, SP::ComponentList()));
    return itLower.mpNode->mValue.second;
}

// @ 0x005db0a0
template <>
SP::ComponentList& map<float*, SP::ComponentList>::operator[](float* const& key)
{
    iterator itLower = lower_bound(key);
    if ((itLower == end()) || mCompare(key, itLower.mpNode->mValue.first))
        itLower = insert(itLower, value_type(key, SP::ComponentList()));
    return itLower.mpNode->mValue.second;
}
}

// ---- cSPEditorTactilityManager registration entry points ------------------------------------
// Each one allocates a 0x28-byte tactile component with the editor's operator new, fills it with
// the retail defaults (velocity/overshoot/animation id) and appends it to the per-key list.
namespace SP {
// @ 0x005db150
void cSPEditorTactilityManager::SetTargetValue(EA::AutoRefCount<cSPEditorBlock> block, eEditorTactileType type,
                                               float arg3, float arg4, eEditorTactileLerp lerp)
{
    float value = (type == kTactileTypeUniformScale) ? block.mpObject->mUniformScale : 0.0f;
    cSPEditorTactileComponent* c = (cSPEditorTactileComponent*)operator new(0x28, kEditorAllocName, 0, 0, 0, 0);
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

    eastl::map<EA::AutoRefCount<cSPEditorBlock>, ComponentList>::iterator it = mBlockComponentList.find(block);
    if (it != mBlockComponentList.end())
        mBlockComponentList.erase(it);
    mBlockComponentList[block].push_back(c);
}

// @ 0x005db270
void cSPEditorTactilityManager::LerpBlockValue(EA::AutoRefCount<cSPEditorBlock> block, eEditorTactileType type,
                                               float arg3, float arg4, eEditorTactileLerp lerp)
{
    float value;
    switch (type) {
    case kTactileTypeColorAlpha: value = block.mpObject->mModel.mpObject->mColorAlpha; break;
    case kTactileTypePositionX:  value = block.mpObject->mPosition.x; break;
    case kTactileTypePositionY:  value = block.mpObject->mPosition.y; break;
    case kTactileTypePositionZ:  value = block.mpObject->mPosition.z; break;
    default: break;
    }
    cSPEditorTactileComponent* c = (cSPEditorTactileComponent*)operator new(0x28, kEditorAllocName, 0, 0, 0, 0);
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

// @ 0x005db390
void cSPEditorTactilityManager::LerpBlockTransform(EA::AutoRefCount<cSPEditorBlock> block,
                                                   eastl::vector<EA::AutoRefCount<cSPEditorBlock>, eastl::sp_vector_allocator> blocks,
                                                   cSPTransform transform, float time, eEditorTactileLerp lerp)
{
    cSPEditorTactileTransformComponent* c =
        (cSPEditorTactileTransformComponent*)operator new(0xd4, kEditorAllocName, 0, 0, 0, 0);
    cSPTransform history;
    history.SetTranslation(block.mpObject->mPosition);
    history.SetRotation(block.mpObject->mOrientation);
    history.mScale = block.mpObject->mUniformScale;
    InitComponent(c, kTactileTypeTransform, lerp, history, transform, time, 0);
    c->mPileList = blocks;
    mBlockComponentList[block].push_back(reinterpret_cast<cSPEditorTactileComponent*>(c));
}

// @ 0x005db580
void cSPEditorTactilityManager::LerpFloat(float* pValue, float finalValue, float time, eEditorTactileLerp lerp)
{
    cSPEditorTactileComponent* c = (cSPEditorTactileComponent*)operator new(0x28, kEditorAllocName, 0, 0, 0, 0);
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
}


#define PV(n) virtual void pv##n();

// Source object (arg0): a ref-counted handle.  Its first field points at the
// actual component, whose vtable slot +0x170 is the release function.
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

// The actual component behind the handle; 0x005db650 releases it through
// vtable slot +0x170, passing the handle and the destructor flag.
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

// Element stored in the per-source vector (allocated with size 0x28).
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
    void Construct(int count, void* allocator);    // 0x0066aec0
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
