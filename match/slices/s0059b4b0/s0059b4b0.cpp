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

struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {} };

class cAnimatingCreature {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
};

class cIModelWorld {
public:
    virtual void AddRef();     // +0x0
    virtual void Release();    // +0x4
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
    void Update(int milliseconds);                             // 0x0059b4b0
    EA::AutoRefCount<cAnimatingCreature> mAnimatingCreature;   // +0x8
    cIModelWorld* mModelWorld;                                 // +0xc
    char pad_10[0x88 - 0x10];
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
void SP::cSPEditorAnimatedCreatureData::Update(int milliseconds)
{
    (void)milliseconds;
}
