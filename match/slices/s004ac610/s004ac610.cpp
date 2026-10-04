// Slice s004ac610: SP::cSPEditorModel block-list management (retail layout).
// Module flags: /Od /Ob1 /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- rw::math / cSP math types ----
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPMatrix3 : Matrix33T {
    static const cSPMatrix3 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPBoundingBox {
    cSPVector3 mMin, mMax;
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
};

Vector3T operator*(const Vector3T& v, const Matrix33T& m);   // @ 0x41daf0
Vector3T operator-(const Vector3T& v);                       // @ 0x422020
Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T& operator+=(Vector3T& a, const Vector3T& b);        // @ 0x41ddb0
float VectorLength(const Vector3T& v);                       // @ 0x40ae50
inline float Length(const Vector3T& v) { return VectorLength(v); }

inline const float& Max(const float& a, const float& b) { return (a > b) ? a : b; }
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform();                                          // @ 0x409930
    const cSPMatrix3& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void PreRotate(const Vector3T& axis, float angle);       // @ 0x6baba0
};

// ---- EASTL-style containers ----
template<class T> struct AutoRefCount {
    T* mpObject;
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// Layout helper: the AutoRefCount vector's inline constructor reserves one unused /Od slot.
template<class T> struct CtorSlots { static void Reserve() {} static void ReserveClear() {} };
template<class T> struct AutoRefCount;
template<class T> struct CtorSlots<AutoRefCount<T> > { static void Reserve() { ScratchSlots<1>(); } static void ReserveClear() { ScratchSlots<3>(); } };

template<class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) { CtorSlots<T>::Reserve(); }
    ~VectorBase();                                           // @ 0x425990 (shared)
};
template<class T> struct vector : VectorBase<T> {
    vector() {}
    ~vector() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* erase(T* first, T* last);                             // @ 0x4769b0 / 0x454280
    T* erase(T* position);                                   // @ 0x454330
    void clear() { erase(mpBegin, mpEnd); ScratchSlots<4>(); CtorSlots<T>::ReserveClear(); }
    bool empty() const;                                      // @ 0x526430
    void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
};

template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

namespace SP {

struct cSPEditorBlock {
    virtual void _v0();
    virtual int Release();
    char pad0[0x33c - 4];
    AutoRefCount<cSPEditorBlock> mParentBlock;  // +0x33c
    vector<AutoRefCount<cSPEditorBlock> > mSymmetricBlocks;   // +0x340
    char pad1[0x3e0 - 0x354];
    int mUIState;                               // +0x3e0
    char pad2[0x5e8 - 0x3e4];
    int mCost;                                  // +0x5e8
    int mComplexity;                            // +0x5ec
    int mPartType;                              // +0x5f0
    float mWeight;                              // +0x5f4
    char pad3[0xdc8 - 0x5f8];
    bitset<60> mFlags;                          // +0xdc8

    cSPEditorBlock* GetParent() const { return mParentBlock; }
    int GetUIState() const { return mUIState; }
    int GetPartType() const { return mPartType; }
    bool IsPaintable();                                      // @ 0x44c030
    void OnRemoved();                                        // @ 0x451ed0
    void OnDeleted();                                        // @ 0x451400
    bool HasAnimation();                                     // @ 0x44b780
    bool IsAnimating(bool b);                                // @ 0x43e8d0
    bool IsPlaying();                                        // @ 0x43e920
    void StopAnimation();                                    // @ 0x43e9c0
    void ResetAnimation(bool b);                             // @ 0x43ea40
    void SetModelFlags(int flags);                           // @ 0x44b7b0
    void SetPhysicsGroup(int group);                         // @ 0x451e20
    void SetIndex(int index);                                // @ 0x451e50
};

}  // namespace SP
namespace EA {
// EA::RefCountTemplate<int>
template<class T> struct RefCountTemplate {
    virtual void _v0();
    T mRefCount;                                // +0x04
    int AddRef() { T r = mRefCount + 1; mRefCount = mRefCount + 1; return r; }
    int Release();                                           // @ 0x453540
};
}
namespace SP {
struct cSPEditorPhysicsWorld : EA::RefCountTemplate<int> {
    int GetGroup();                                          // @ 0x4b91c0
    void AttachModel(struct cSPEditorModel* model);          // @ 0x4b94a0
    void DetachModel(struct cSPEditorModel* model);          // @ 0x4b9570
};
template<class T> struct AutoRefCountP {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCountP& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

extern const uint32_t kDefaultName;                          // @ 0x13ec468

template<class I, class T> inline I find(I first, I last, const T& value)
{
    while ((first != last) && (*first != value)) ++first;
    return first;
}

struct cSPEditorModel {
    virtual void SetName(const uint32_t* name);              // 0x00
    virtual void _v1();
    virtual void SetDescription(const uint32_t* desc);       // 0x08
    char pad0[0x18 - 4];
    vector<AutoRefCount<cSPEditorBlock> > mBlockList;        // +0x18
    bool mbAllBlocksLoaded;                     // +0x2c
    AutoRefCountP<cSPEditorPhysicsWorld> mPhysicsWorld;      // +0x30
    char pad1[0x50 - 0x34];
    bool mSkinNeedsUpdating;                    // +0x50

    cSPEditorBlock* GetRootSpine();
    cSPEditorBlock* GetUnmatchedSpine();
    void RemoveBlock(cSPEditorBlock* block, bool recursive, bool notify);
    bool DeleteBlock(cSPEditorBlock* block, bool recursive);
    cSPEditorBlock* GetBlock(uint32_t index);
    uint32_t GetBlockCount();                                // @ 0x4accf0
    void GetStats(int* cost, int* complexity, int* count, float* weight, int* parts);
    bool IsAnyBlockAnimating();
    bool IsAnyBlockPlaying();
    void StopAnimations();
    void ResetAnimations();
    void SetModelFlags(int flags);
    void ClearBlocks();
    void Clear();
    void SetPhysicsWorld(cSPEditorPhysicsWorld* world);
    void SetIndices(int index);
    void NumberBlocks();
    bool CountsForStats();                                   // @ 0x4adc40
    void SetChanged(bool b);                                 // @ 0x4adfc0
};

// @ 0x4ac610
cSPEditorBlock* cSPEditorModel::GetRootSpine()
{
    for (int tmp = 0, t14 = mBlockList.size(); tmp < t14; tmp++) {
        if (mBlockList[tmp]->mFlags.test(7) && !mBlockList[tmp]->GetParent())
            return mBlockList[tmp];
    }
    return 0;
}

// @ 0x4ac710
cSPEditorBlock* cSPEditorModel::GetUnmatchedSpine()
{
    for (int tmp = 0, t14 = mBlockList.size(); tmp < t14; tmp++) {
        if (mBlockList[tmp]->mFlags.test(7)) {
            bool bFound = false;
            vector<AutoRefCount<cSPEditorBlock> >& symBlocks = mBlockList[tmp]->mSymmetricBlocks;
            for (int j = 0, m = symBlocks.size(); j < m; j++) {
                if (symBlocks[j]->mFlags.test(7)) { bFound = true; break; }
            }
            if (!bFound) return mBlockList[tmp];
        }
    }
    return 0;
}

// @ 0x4ac8b0
void cSPEditorModel::RemoveBlock(cSPEditorBlock* block, bool recursive, bool notify)
{
    if (recursive) {
        vector<AutoRefCount<cSPEditorBlock> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++)
            RemoveBlock(syms[i], recursive, false);
    }
    AutoRefCount<cSPEditorBlock>* it = find(mBlockList.begin(), mBlockList.end(), block);
    if (it != mBlockList.end()) {
        if ((block->mFlags.test(0xb) || block->mFlags.test(7)) && block->IsPaintable() && block->mFlags.test(0xa))
            mSkinNeedsUpdating = true;
        if (notify) block->OnRemoved();
        mBlockList.erase(it);
        ScratchSlots<4>();
        SetChanged(true);
    }
}

// @ 0x4acab0
bool cSPEditorModel::DeleteBlock(cSPEditorBlock* block, bool recursive)
{
    if (recursive) {
        vector<AutoRefCount<cSPEditorBlock> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++)
            DeleteBlock(syms[i], recursive);
    }
    AutoRefCount<cSPEditorBlock>* it = find(mBlockList.begin(), mBlockList.end(), block);
    if (it != mBlockList.end()) {
        if ((block->mFlags.test(0xb) || block->mFlags.test(7)) && block->IsPaintable() && block->mFlags.test(0xa))
            mSkinNeedsUpdating = true;
        block->OnDeleted();
        mBlockList.erase(it);
        ScratchSlots<4>();
        SetChanged(true);
    }
    return true;
}

// @ 0x4accb0
cSPEditorBlock* cSPEditorModel::GetBlock(uint32_t index)
{
    if (index < GetBlockCount()) return mBlockList[index];
    return 0;
}

// @ 0x4acd20
// Local names were picked for their /Od slot order (the slot layout follows a hash of the names):
// where=totalWeight, t24=totalComplexity, offset=totalCount, len=totalCost, p24=totalParts,
// tmp=count, t14=index, nCount=complexity, p15=partCount, t22=weight, hi=parts, t26=cost, item=block.
void cSPEditorModel::GetStats(int* cost, int* complexity, int* count, float* weight, int* parts)
{
    int len = 0;
    int t24 = 0;
    int offset = 0;
    float where = 0.0f;
    int p24 = 0;
    for (int t14 = 0, tmp = mBlockList.size(); t14 < tmp; t14++) {
        cSPEditorBlock* item = mBlockList[t14];
        int t26 = item->mCost;
        int nCount = item->mComplexity;
        int p15;
        if (item->GetPartType() != 2) p15 = 1; else p15 = 0;
        int hi = 1;
        float t22 = item->mWeight;
        if (CountsForStats() && !item->mFlags.test(7) && !item->mFlags.test(0x39) &&
            item->mFlags.test(0xf) && item->GetUIState() == 0) {
            t26 *= 2;
            nCount *= 2;
            p15 *= 2;
            t22 *= 2.0f;
            hi *= 2;
        }
        len += t26;
        t24 += nCount;
        offset += p15;
        where += t22;
        p24 += hi;
    }
    if (cost) *cost = len;
    if (complexity) *complexity = t24;
    if (count) *count = offset;
    if (weight) *weight = where;
    if (parts) *parts = p24;
}

// @ 0x4acfd0
bool cSPEditorModel::IsAnyBlockAnimating()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++) {
        if (mBlockList[i]->HasAnimation() && mBlockList[i]->IsAnimating(true))
            return true;
    }
    return false;
}

// @ 0x4ad070
bool cSPEditorModel::IsAnyBlockPlaying()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++) {
        if (mBlockList[i]->HasAnimation() && mBlockList[i]->IsPlaying())
            return true;
    }
    return false;
}

// @ 0x4ad110
void cSPEditorModel::StopAnimations()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++) {
        if (mBlockList[i]->IsPlaying())
            mBlockList[i]->StopAnimation();
    }
}

// @ 0x4ad1a0
void cSPEditorModel::ResetAnimations()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->ResetAnimation(true);
}

// @ 0x4ad210
void cSPEditorModel::SetModelFlags(int flags)
{
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->SetModelFlags(flags);
}

// @ 0x4ad280
void cSPEditorModel::ClearBlocks()
{
    SetName(&kDefaultName);
    SetDescription(&kDefaultName);
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->OnDeleted();
    mBlockList.clear();
}

// @ 0x4ad330
void cSPEditorModel::Clear()
{
    ClearBlocks();
    if (mPhysicsWorld) mPhysicsWorld->DetachModel(this);
}

// @ 0x4ad370
void cSPEditorModel::SetPhysicsWorld(cSPEditorPhysicsWorld* world)
{
    mPhysicsWorld = world;
    int group = world->GetGroup();
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->SetPhysicsGroup(group);
    mPhysicsWorld->AttachModel(this);
}

// @ 0x4ad470
void cSPEditorModel::SetIndices(int index)
{
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->SetIndex(index);
}

// @ 0x4ad4e0
void cSPEditorModel::NumberBlocks()
{
    for (int i = 0, n = mBlockList.size(); i < n; i++)
        mBlockList[i]->SetIndex(i + 1);
}

}  // namespace SP
