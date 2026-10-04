// Slice s004d06e0: EASTL algorithm/vector template instances used by the creature-editor skin code
// (uninitialized_copy/fill_n/move helpers, copy_backward, vector<uint8_t>::DoAssignFromIterator),
// one fixed hashtable node free, and a few small editor helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

template <int N> inline void ScratchSlots() { uint32_t s[N]; }

inline void* operator new(unsigned int, void* p) { return p; }

void EASTLFree(void* p);                                             // 0x00F47380
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // 0x011E0744 (static CRT)

namespace eastl {

struct false_type {};
struct is_integral_false : public false_type { is_integral_false() {} };
struct true_type {};
struct random_access_iterator_tag { random_access_iterator_tag() {} };

// ---------------------------------------------------------------------------
// element types
// ---------------------------------------------------------------------------
template <class T1, class T2> struct pair {
    T1 first;
    T2 second;
};
typedef pair<int, int> IntPair;

struct Word32 { uint32_t mValue; };   // 4-byte POD element

struct Vector3 {
    float x, y, z;
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Vec4 {
    float x, y, z, w;
    Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    Vec4& operator=(const Vec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
};

struct Rec14 {                          // 0x14: key + Vec4
    uint32_t mKey;
    Vec4 mValue;
};

struct EASTLAllocator { const char* mpName; EASTLAllocator() {} };

struct fixed_vector_allocator : public EASTLAllocator {
    void* mpPoolBegin;
    fixed_vector_allocator(void* pNodeBuffer) : mpPoolBegin(pNodeBuffer) {}
    fixed_vector_allocator(const fixed_vector_allocator& x) { mpPoolBegin = x.mpPoolBegin; }
};

template <class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    fixed_vector_allocator mAllocator;
    VectorBase(const fixed_vector_allocator& allocator) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {}
};

// fixed_vector<uint32_t, 4>
struct FixedU32Vector : public VectorBase<uint32_t> {
    uint32_t mUnknown14;                // +0x14
    uint32_t mBuffer[4];                // +0x18
    // 0x004D08C0. cl declines to inline it, so callers reserve its 6-dword frame (the holes in the copy loops).
    FixedU32Vector(const FixedU32Vector& x)
        : VectorBase<uint32_t>(fixed_vector_allocator(mBuffer))
    {
        mpEnd = mBuffer;
        mpBegin = mpEnd;
        mpCapacity = mpBegin + 4;
        assign(x.begin(), x.end());
    }
    ~FixedU32Vector()
    {
        for (uint32_t* p = mpBegin; p < mpEnd; ++p)
            ;
        ScratchSlots<3>();
        DoFree();
    }
    __forceinline FixedU32Vector& operator=(const FixedU32Vector& x)
    {
        ScratchSlots<4>();
        if (this != &x) {
            erase(mpBegin, mpEnd);
            assign(x.begin(), x.end());
        }
        return *this;
    }
    void assign(const uint32_t* first, const uint32_t* last) { DoAssign(first, last, is_integral_false()); }
    void DoAssign(const uint32_t* first, const uint32_t* last, false_type) { DoAssignFromIterator(first, last, random_access_iterator_tag()); }
    const uint32_t* begin() const { return mpBegin; }
    const uint32_t* end() const { return mpEnd; }
    uint32_t* erase(uint32_t* first, uint32_t* last);                // 0x004769B0
    void DoAssignFromIterator(const uint32_t* first, const uint32_t* last, random_access_iterator_tag);  // 0x0042C750
    void DoFree();                                                   // 0x004C0B80
    static void operator delete(void* p) { EASTLFree(p); }
};

struct Elem34 {                         // 0x34: Vector3 + fixed_vector<uint32_t, 4>
    Vector3 mHeader;
    FixedU32Vector mValues;             // +0x0c
    Elem34& operator=(const Elem34& x);
};

// @ 0x4d1030
Elem34& Elem34::operator=(const Elem34& x)
{
    mHeader = x.mHeader;
    mValues = x.mValues;
    return *this;
}

// ---------------------------------------------------------------------------
// iterators
// ---------------------------------------------------------------------------
template <class I> struct iterator_traits;
template <class T> struct iterator_traits<T*> { typedef T value_type; typedef T& reference; };
template <class T> struct iterator_traits<const T*> { typedef T value_type; typedef const T& reference; };

template <class Iterator, class Container = void>
class generic_iterator {
public:
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::reference reference;
    Iterator mIterator;
    explicit generic_iterator(const Iterator& x) : mIterator(x) {}
    reference operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
    const Iterator& base() const { return mIterator; }
};
template <class I, class C> struct iterator_traits<generic_iterator<I, C> > { typedef typename iterator_traits<I>::value_type value_type; };

template <class IL, class IR, class C>
inline bool operator!=(const generic_iterator<IL, C>& lhs, const generic_iterator<IR, C>& rhs)
{
    return lhs.base() != rhs.base();
}

template <class T> struct has_trivial_relocate : public false_type {};

// ---------------------------------------------------------------------------
// uninitialized_copy
// ---------------------------------------------------------------------------
template <class InputIterator, class ForwardIterator>
inline ForwardIterator uninitialized_copy_impl(InputIterator first, InputIterator last, ForwardIterator dest, false_type)
{
    typedef typename iterator_traits<ForwardIterator>::value_type value_type;
    ForwardIterator currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        ::new (&*currentDest) value_type(*first);
    return currentDest;
}

template <class First, class Last, class Result>
inline Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    typedef typename iterator_traits<generic_iterator<Result, void> >::value_type value_type;
    const generic_iterator<Result, void> i(uninitialized_copy_impl(generic_iterator<First, void>(first),
                                                                   generic_iterator<Last, void>(last),
                                                                   generic_iterator<Result, void>(result),
                                                                   has_trivial_relocate<value_type>()));
    return i.base();
}

// @ 0x4d0960
template IntPair* uninitialized_copy_ptr<IntPair*, IntPair*, IntPair*>(IntPair*, IntPair*, IntPair*);
// @ 0x4d0b90
template Word32* uninitialized_copy_ptr<Word32*, Word32*, Word32*>(Word32*, Word32*, Word32*);
// @ 0x4d0c90
template generic_iterator<Elem34*> uninitialized_copy_impl(generic_iterator<const Elem34*>, generic_iterator<const Elem34*>, generic_iterator<Elem34*>, false_type);
// @ 0x4d0dd0
template generic_iterator<Rec14*> uninitialized_copy_impl(generic_iterator<const Rec14*>, generic_iterator<const Rec14*>, generic_iterator<Rec14*>, false_type);
// @ 0x4d0f60
template generic_iterator<Word32*> uninitialized_copy_impl(generic_iterator<const Word32*>, generic_iterator<const Word32*>, generic_iterator<Word32*>, false_type);

// ---------------------------------------------------------------------------
// uninitialized_fill_n
// ---------------------------------------------------------------------------
template <class ForwardIterator, class Count, class T>
inline void uninitialized_fill_n_impl(ForwardIterator first, Count n, const T& value, false_type)
{
    typedef typename iterator_traits<ForwardIterator>::value_type value_type;
    ForwardIterator currentDest(first);
    for (; n > 0; --n, ++currentDest)
        ::new (&*currentDest) value_type(value);
}

// @ 0x4d0d40
template void uninitialized_fill_n_impl(generic_iterator<Elem34*>, uint32_t, const Elem34&, false_type);
// @ 0x4d0e90
template void uninitialized_fill_n_impl(generic_iterator<Rec14*>, uint32_t, const Rec14&, false_type);
// @ 0x4d0fd0
template void uninitialized_fill_n_impl(generic_iterator<Word32*>, uint32_t, const Word32&, false_type);

// ---------------------------------------------------------------------------
// uninitialized_move (relocate) start / commit
// ---------------------------------------------------------------------------
template <bool bHasTrivialMove, class ForwardIterator, class ForwardIteratorDest>
struct uninitialized_move_impl {
    static ForwardIteratorDest do_move_start(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest)
    {
        typedef typename iterator_traits<ForwardIterator>::value_type value_type;
        for (; first != last; ++first, ++dest)
            ::new (&*dest) value_type(*first);
        return dest;
    }
    static ForwardIteratorDest do_move_commit(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest)
    {
        typedef typename iterator_traits<ForwardIterator>::value_type value_type;
        for (; first != last; ++first, ++dest)
            (*first).~value_type();
        return dest;
    }
};

template <class ForwardIterator, class ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move_start(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest)
{
    const bool bHasTrivialMove = false;
    return uninitialized_move_impl<false, ForwardIterator, ForwardIteratorDest>::do_move_start(first, last, dest);
}

template <class ForwardIterator, class ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move_commit(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest)
{
    const bool bHasTrivialMove = false;
    return uninitialized_move_impl<false, ForwardIterator, ForwardIteratorDest>::do_move_commit(first, last, dest);
}

template <class ForwardIterator, class ForwardIteratorDest>
inline ForwardIteratorDest uninitialized_move(ForwardIterator first, ForwardIterator last, ForwardIteratorDest dest)
{
    ForwardIteratorDest result = uninitialized_move_start(first, last, dest);
    uninitialized_move_commit(first, last, dest);
    return result;
}

// @ 0x4d0a40
template Elem34* uninitialized_move(Elem34*, Elem34*, Elem34*);
// @ 0x4d0ac0
template Rec14* uninitialized_move(Rec14*, Rec14*, Rec14*);
// @ 0x4d0f30
template Rec14* uninitialized_move_start(Rec14*, Rec14*, Rec14*);
// @ 0x4d10b0
template struct uninitialized_move_impl<false, Elem34*, Elem34*>;
// @ 0x4d1130  (do_move_commit of the same instance)
// @ 0x4d11a0
template Rec14* uninitialized_move_impl<false, Rec14*, Rec14*>::do_move_start(Rec14*, Rec14*, Rec14*);

// ---------------------------------------------------------------------------
// copy / copy_backward
// ---------------------------------------------------------------------------
template <class Bi1, class Bi2>
inline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}

template <class Bi1, class Bi2>
inline Bi2 copy_backward(Bi1 first, Bi1 last, Bi2 resultEnd)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_backward_impl(first, last, resultEnd);
}

// @ 0x4d0b20
template Vec4* copy_backward(Vec4*, Vec4*, Vec4*);

template <class T>
inline T* copy_memmove(const T* first, const T* last, T* result)
{
    const bool bCanMemmove = true;
    return (T*)memmove(result, first, (unsigned int)((uint32_t)last - (uint32_t)first)) + (last - first);
}

template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    return OutputIterator(copy_memmove(first.base(), last.base(), result.base()));
}

// @ 0x4d1240
template generic_iterator<Word32*> copy(generic_iterator<const Word32*>, generic_iterator<const Word32*>, generic_iterator<Word32*>);

// ---------------------------------------------------------------------------
// vector<uint8_t>::DoAssignFromIterator
// ---------------------------------------------------------------------------
template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    fixed_vector_allocator mAllocator;

    T* DoRealloc(uint32_t n, const T* first, const T* last);         // 0x00426950
    void DoFree(T* p, uint32_t n) { if (p) deallocate(p, n * sizeof(T)); }
    static void deallocate(void* p, uint32_t) { if (*((uint32_t*)p - 1)) FreeBlock(p); }
    static void FreeBlock(void* p) { void* pBlock = p; EASTLFree(pBlock); }
    template <class II> void DoAssignFromIterator(II first, II last, random_access_iterator_tag);
};

uint8_t* uninitialized_copy_ptr(const uint8_t* first, const uint8_t* last, uint8_t* result);   // 0x00475BD0

template <class T> __forceinline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        ;
}

__forceinline uint8_t* copy(const uint8_t* first, const uint8_t* last, uint8_t* result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = true;
    return (uint8_t*)memmove(result, first, (unsigned int)(last - first)) + (last - first);
}

// @ 0x4d06e0
template <> template <> void vector<uint8_t>::DoAssignFromIterator<const uint8_t*>(const uint8_t* first, const uint8_t* last, random_access_iterator_tag)
{
    const uint32_t n = (uint32_t)(last - first);
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        uint8_t* const pNewData = DoRealloc(n, first, last);
        ScratchSlots<14>();   // frame of the out-of-line DoRealloc
        eastl::destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    } else if (n <= (uint32_t)(mpEnd - mpBegin)) {
        uint8_t* const position = eastl::copy(first, last, mpBegin);
        eastl::destruct(position, mpEnd);
        mpEnd = position;
    } else {
        const uint8_t* position = first + (mpEnd - mpBegin);
        eastl::copy(first, position, mpBegin);
        mpEnd = eastl::uninitialized_copy_ptr(position, last, mpEnd);
        ScratchSlots<17>();   // frame of the out-of-line uninitialized_copy_ptr
    }
}

// ---------------------------------------------------------------------------
// fixed hashtable node free
// ---------------------------------------------------------------------------
struct Link { Link* mpNext; };

struct fixed_pool_with_overflow {
    Link* mpHead;
    Link* mpNext;
    void* mpPoolBegin;
    void* mpCapacity;
    uint32_t mnNodeSize;
    static void OverflowFree(void* p, uint32_t n) { (void)&n; void* const pMemory = p; EASTLFree(pMemory); }
};

struct fixed_hashtable_allocator {
    fixed_pool_with_overflow mPool;
    void* mpBucketBuffer;
    void deallocate(void* p, uint32_t)
    {
        if (p != mpBucketBuffer) {
            if ((p >= mPool.mpPoolBegin) && (p < mPool.mpCapacity)) {
                ((Link*)p)->mpNext = mPool.mpHead;
                mPool.mpHead = (Link*)p;
            } else
                fixed_pool_with_overflow::OverflowFree(p, mPool.mnNodeSize);
        }
    }
};

struct HashNode;

class hashtable {
public:
    uint32_t mFunctors;                              // 0x00
    HashNode** mpBucketArray;                        // 0x04
    uint32_t mnBucketCount;                          // 0x08
    uint32_t mnElementCount;                         // 0x0C
    uint32_t mRehashPolicy[3];                       // 0x10
    fixed_hashtable_allocator mAllocator;            // 0x1C
    void DoFreeNode(HashNode* pNode);
};

// @ 0x4d0c20
void hashtable::DoFreeNode(HashNode* pNode)
{
    mAllocator.deallocate(pNode, 0x10);
}

} // namespace eastl

// ---------------------------------------------------------------------------
// editor helpers
// ---------------------------------------------------------------------------
extern const float kSkinLevelValues[7];                             // 0x0150C890

// @ 0x4d12a0
float GetSkinLevelValue(int level)
{
    level &= (level < 0) - 1;
    float value = 100.0f;
    switch (level) {
    case 0: value = kSkinLevelValues[0]; break;
    case 1: value = kSkinLevelValues[1]; break;
    case 2: value = kSkinLevelValues[2]; break;
    case 3: value = kSkinLevelValues[3]; break;
    case 4: value = kSkinLevelValues[4]; break;
    case 5: value = kSkinLevelValues[5]; break;
    case 6: value = kSkinLevelValues[6]; break;
    }
    return value;
}

namespace App {
class Property {
public:
    char pad0[0x12];
    uint16_t mnType;                            // +0x12
    uint32_t* GetValueUInt32();                                      // 0x0041E990
};
class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void _v08(); virtual void _v0c(); virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c(); virtual void _v20();
    virtual bool GetProperty(uint32_t propertyID, Property*& result) const;   // 0x24
};
inline void intrusive_ptr_release(PropertyList* p) { p->Release(); }
template <class T> class intrusive_ptr {
public:
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T** reset_get()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
typedef intrusive_ptr<PropertyList> PropertyListPtr;
class cPropertyManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1c(); virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** result);   // 0x2c
};
inline bool GetUInt32(const PropertyList* pPropList, uint32_t propertyID, uint32_t& value)
{
    ScratchSlots<1>();
    Property* prop;
    if (pPropList && pPropList->GetProperty(propertyID, prop) && prop->mnType == 9) {
        value = *prop->GetValueUInt32();
        return true;
    }
    return false;
}
}
App::cPropertyManager* PropertyManager();                            // 0x0067DE30
uint32_t RemapTypeId(uint32_t modelType);                            // 0x00432F10
extern uint32_t gEditorConfigGroup;                                  // 0x015D9950

// @ 0x4d1370
uint32_t GetEditorConfigValue(uint32_t modelType)
{
    uint32_t nID = RemapTypeId(modelType);
    App::PropertyListPtr pProp;
    PropertyManager()->GetPropertyList(nID, gEditorConfigGroup, pProp.reset_get());
    if (pProp) {
        const uint32_t kID = 0x5deb6a5;
        uint32_t val;
        if (App::GetUInt32(pProp.get(), kID, val))
            return val;
    }
    return 0;
}

struct Vector2 {
    float x, y;
    Vector2(const Vector2& v) { x = v.x; y = v.y; }
    float& operator[](int i) { return (&x)[i]; }
};
struct cSkinPaintEntry { const Vector2& GetUV(); };                 // 0x004E1A20
struct cSkinPaintTable {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual bool HasEntry(uint32_t id);                              // 0x1c
    virtual void _v20(); virtual void _v24();
    virtual cSkinPaintEntry* GetEntry(uint32_t id);                  // 0x28
};

// @ 0x4d1470
bool GetPaintUV(cSkinPaintTable* table, uint32_t id, float* u, float* v)
{
    if (table->HasEntry(id)) {
        ScratchSlots<1>();
        Vector2 uv = table->GetEntry(id)->GetUV();
        *u = uv[0];
        *v = uv[1];
        return true;
    }
    *v = 0.0f;
    *u = 0.0f;
    return false;
}

struct Vector3i { int x, y, z; };
struct BBox { Vector3i mMin; Vector3i mMax; };
bool GetBoundsPoints(uint32_t a, uint32_t b, int* count, Vector3i** points);   // 0x006A0990

// @ 0x4d1510
bool GetBounds(uint32_t a, uint32_t b, BBox* box)
{
    int pointCount = 0;
    Vector3i* pointList = 0;
    if (GetBoundsPoints(a, b, &pointCount, &pointList)) {
        if (pointCount == 1) {
            box->mMin = pointList[0];
            box->mMax = pointList[0];
            return true;
        } else if (pointCount > 1) {
            box->mMin = pointList[0];
            box->mMax = pointList[1];
            return true;
        }
    }
    return false;
}

#pragma pack(pop)
