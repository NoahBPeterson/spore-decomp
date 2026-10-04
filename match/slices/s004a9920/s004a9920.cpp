// Slice s004a9920: EditorUtils block searches, ResourceKey match, quaternion->matrix, EASTL vector/deque instances.
// Module flags: /Od /Ob1 /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }

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
    Matrix33T() {}
    Matrix33T(const Matrix33T& m) { xAxis = Vector3T(m.xAxis); yAxis = Vector3T(m.yAxis); zAxis = Vector3T(m.zAxis); }   // emitted out of line @ 0x41cb40
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
    char pad0[0x340 - 4];
    vector<AutoRefCount<cSPEditorBlock> > mSymmetricBlocks;   // +0x340
    char pad1[0xdc8 - 0x354];
    bitset<60> mFlags;                          // +0xdc8
};

namespace EditorUtils {
bool IsSkinnedPart(cSPEditorBlock* block);                   // @ 0x4a96d0

// @ 0x4a9920
cSPEditorBlock* FindSymmetricFoot(cSPEditorBlock* block)
{
    if (!block) return 0;
    if (block->mFlags.test(0x2c)) return block;
    else {
        vector<AutoRefCount<cSPEditorBlock> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            cSPEditorBlock* found = FindSymmetricFoot(syms[i]);
            if (found) return found;
        }
        return 0;
    }
}

// @ 0x4a9a00
cSPEditorBlock* FindSymmetricSkinnedPart(cSPEditorBlock* block)
{
    if (IsSkinnedPart(block)) return block;
    else {
        vector<AutoRefCount<cSPEditorBlock> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            cSPEditorBlock* found = FindSymmetricSkinnedPart(syms[i]);
            if (found) return found;
        }
        return 0;
    }
}
}  // namespace EditorUtils

struct ResourceKey { uint32_t mGroupID, mTypeID, mInstanceID; };

// @ 0x4a9a90
bool KeyMatches(const ResourceKey& key, const ResourceKey& pattern)
{
    if (key.mInstanceID != pattern.mInstanceID) return false;
    if (pattern.mGroupID && key.mGroupID != pattern.mGroupID) return false;
    if (pattern.mTypeID && key.mTypeID != pattern.mTypeID) return false;
    return true;
}

struct DefaultRefCounted { int Release(); };                  // @ 0x453540
struct cRefCountedResource { void* vftable; DefaultRefCounted mRef; };
struct cVirtualRefCounted { virtual int AddRef(); virtual int Release(); };

template<class T> struct AutoRefCountR {        // AutoRefCount over DefaultRefCounted (+4)
    T* mpObject;
    ~AutoRefCountR();
};
// @ 0x4a9ae0
template<> AutoRefCountR<cRefCountedResource>::~AutoRefCountR()
{
    if (mpObject) mpObject->mRef.Release();
    ScratchSlots<3>();
}

template<class T> struct AutoRefCountV {
    T* mpObject;
    ~AutoRefCountV();
};
// @ 0x4a9b10
template<> AutoRefCountV<cVirtualRefCounted>::~AutoRefCountV()
{
    if (mpObject) mpObject->Release();
}

struct Quaternion { float x, y, z, w; };
inline void Set(Vector3T& v, float x, float y, float z) { v.x = x; v.y = y; v.z = z; }

// @ 0x4a9b40
Matrix33T& QuaternionToMatrix(Matrix33T& mat, const Quaternion& q)
{
    // locals named to reproduce the /Od stack-slot order (see tools/matching/od_names.py fit 11)
    float v22 = q.x * q.x;      // xx
    float n32 = q.y * q.y;      // yy
    float t28 = q.z * q.z;      // zz
    float m = q.x * q.y;       // xy
    float v1 = q.x * q.z;       // xz
    float v3 = q.y * q.z;       // yz
    float t33 = q.w * q.x;      // wx
    float idx = q.w * q.y;      // wy
    float v14 = q.w * q.z;      // wz
    float n36 = 1.0f;
    float p20 = 2.0f;
    Set(mat.xAxis, n36 - (n32 + t28) * p20, (m + v14) * p20, (v1 - idx) * p20);
    Set(mat.yAxis, (m - v14) * p20, n36 - (v22 + t28) * p20, (v3 + t33) * p20);
    Set(mat.zAxis, (v1 + idx) * p20, (v3 - t33) * p20, n36 - (v22 + n32) * p20);
    return mat;
}

// @ 0x4a9d20 sym=??_0SP@@YAAAUVector3T
Vector3T& operator/=(Vector3T& v, const float& s)
{
    float inv = 1.0f / s;
    Vector3T r;
    r.x = v.x * inv; r.y = v.y * inv; r.z = v.z * inv;
    v.x = r.x; v.y = r.y; v.z = r.z;
    return v;
}

// ---- EASTL instances ----

void* EASTLAlloc(void* allocator, unsigned int n, unsigned int align, unsigned int flags);   // @ 0x42dee0
void EASTLFree(void* p);                                                                     // @ 0xf47380

struct WeightedPoint { float mWeight; cSPVector3 mPoint; };                 // 0x10
struct OrientedPoint {                                                        // 0x34
    cSPMatrix3 mOrientation; cSPVector3 mPosition; float mScale;
    OrientedPoint(const OrientedPoint& x);
};

// @ 0x4aa2f0 sym=??0OrientedPoint@
inline OrientedPoint::OrientedPoint(const OrientedPoint& x)
    : mOrientation(x.mOrientation), mPosition(x.mPosition), mScale(x.mScale)
{
}
struct cSPTransform {                           // 0x38; implicit copy ctor emitted out of line @ 0x40ce80
    uint16_t mFlags; uint16_t mModificationCount; cSPVector3 mTranslation; float mScale; cSPMatrix3 mRotation;
};
struct KeyedPair { uint32_t first; cSPTransform second; };                    // 0x3c

WeightedPoint* uninitialized_copy_ptr(WeightedPoint* first, WeightedPoint* last, WeightedPoint* dest);   // @ 0x4ab4a0
WeightedPoint* uninitialized_copy_ptr2(WeightedPoint* first, WeightedPoint* last, WeightedPoint* dest);  // @ 0x4ab5b0

template<class T> struct evector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    evector(uint32_t n, const uint32_t& allocator);
    T* DoAllocate(uint32_t n) { return n ? (T*)EASTLAlloc(&mAllocator, n * sizeof(T), 4, 0) : 0; }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity) ::new(mpEnd++) T(value);
        else DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(T* position, const T& value);
};

// @ 0x4a9e40 sym=?push_back@?$evector@UWeightedPoint
template void evector<WeightedPoint>::push_back(const WeightedPoint& value);

// @ 0x4a9f30 sym=?push_back@?$evector@UOrientedPoint
template void evector<OrientedPoint>::push_back(const OrientedPoint& value);

// @ 0x4a9fa0 sym=?push_back@?$evector@UKeyedPair
template void evector<KeyedPair>::push_back(const KeyedPair& value);

// @ 0x4aa080 sym=?push_back@?$evector@UcSPMatrix3@@
template void evector<cSPMatrix3>::push_back(const cSPMatrix3& value);

template<class T> struct DequeIterator {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;
    DequeIterator(const DequeIterator& x);                   // @ 0x420050
    DequeIterator& operator++();                             // @ 0x4ab210
    bool operator!=(const DequeIterator& x) const { return mpCurrent != x.mpCurrent; }
    int operator-(const DequeIterator& x) const {
        return (64 * ((mpCurrentArrayPtr - x.mpCurrentArrayPtr) - 1)) + (mpCurrent - mpBegin) + (x.mpEnd - x.mpCurrent);
    }
};
template<class T> struct deque {
    T** mpPtrArray;
    uint32_t mnPtrArraySize;
    DequeIterator<T> mItBegin;
    DequeIterator<T> mItEnd;
    ~deque();
    void FreeBase();                                         // @ 0x501ef0
    uint32_t size() const { return (uint32_t)(mItEnd - mItBegin); }
    uint32_t GetSize() const;
    T& operator[](uint32_t n);
    void push_front(const T& value);
    void DoPushFront(const T& value);                        // @ 0x4ab130
};
struct cSPEditorPart;

// @ 0x4aa120
template<> deque<cSPEditorPart*>::~deque()
{
    for (DequeIterator<cSPEditorPart*> it(mItBegin); it != mItEnd; ++it) {}
    FreeBase();
}

// @ 0x4aa170
template<> uint32_t deque<cSPEditorPart*>::GetSize() const
{
    return (uint32_t)(mItEnd - mItBegin);
}

// @ 0x4aa1d0
template<> cSPEditorPart*& deque<cSPEditorPart*>::operator[](uint32_t n)
{
    DequeIterator<cSPEditorPart*> it(mItBegin);
    const int subarrayPosition = (it.mpCurrent - it.mpBegin) + (int)n;
    const int subarrayIndex = ((16777216 + subarrayPosition) / 64) - (16777216 / 64);
    return *(*(it.mpCurrentArrayPtr + subarrayIndex) + (subarrayPosition - (subarrayIndex * 64)));
}

// @ 0x4aa230
template<> void deque<cSPEditorPart*>::push_front(cSPEditorPart* const& value)
{
    if (mItBegin.mpCurrent != mItBegin.mpBegin) ::new(--mItBegin.mpCurrent) cSPEditorPart*(value);
    else DoPushFront(value);
}

// @ 0x4aa350
template<> evector<cSPEditorPart*>::evector(uint32_t n, const uint32_t& allocator)
{
    mpBegin = DoAllocate(n);
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
}

// @ 0x4aa3c0
template<> void evector<WeightedPoint>::DoInsertValue(WeightedPoint* position, const WeightedPoint& value)
{
    if (mpEnd != mpCapacity) {
        const WeightedPoint* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd)) ++pValue;
        ::new(mpEnd) WeightedPoint(*(mpEnd - 1));
        {
            WeightedPoint* d = mpEnd;
            WeightedPoint* s = mpEnd - 1;
            while (s != position) *--d = *--s;      // copy_backward
        }
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        WeightedPoint* const pNewData = DoAllocate(nNewSize);
        WeightedPoint* pNewEnd = uninitialized_copy_ptr(mpBegin, position, pNewData);
        ::new(pNewEnd) WeightedPoint(value);
        pNewEnd = uninitialized_copy_ptr2(position, mpEnd, ++pNewEnd);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTLFree(mpBegin);   // DoFree
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

}  // namespace SP
