// Skin-paint helpers: EASTL vector<pair<int,float>> / vector<float> instantiations, the introsort
// pieces for pair<int,float> ordered by descending .second, and the cSPSkinPaintClear description / command
// factories (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast; the factories with EH
// frames are built with /EHsc as well).
// Inline helpers that cl declined to inline in the original are modelled as out-of-line calls
// preceded by ScratchSlots<N>() (the declined callee's frame, minus its `this`, stays reserved).
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                            // 0x00f473a0
void operator delete(void* p, const char* name, int flags, unsigned debugFlags,
                     const char* file, int line);

struct sp_vector_allocator {
    uint32_t mFlags[2];
    sp_vector_allocator() {}
};
void* EASTL_Allocate(sp_vector_allocator* a, uint32_t n, uint32_t align, uint32_t ofs);  // 0x0042dee0

namespace eastl {

template <typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
};

template <typename T, bool v> struct integral_constant {
    static const bool value = v;
};
typedef integral_constant<bool, false> false_type;
typedef integral_constant<bool, true> true_type;
template <typename T> struct has_trivial_constructor : public false_type {};
template <> struct has_trivial_constructor<float> : public true_type {};

template <typename T> struct generic_iterator {     // eastl::generic_iterator<T*>
    T* mIterator;
    generic_iterator(T* const& x) : mIterator(x) {}
    T& operator*() const { return *mIterator; }
    generic_iterator& operator++()
    {
        ++mIterator;
        return *this;
    }
};

template <typename ForwardIterator, typename T>
void uninitialized_fill_n_impl(ForwardIterator first, uint32_t n, const T& value, false_type);   // 0x0052c8f0

// @ 0x0052c8f0 ??$uninitialized_fill_n_impl@
template <> void uninitialized_fill_n_impl(generic_iterator<pair<int, float> > first, uint32_t n,
                                           const pair<int, float>& value, false_type)
{
    generic_iterator<pair<int, float> > currentDest(first);
    for (; n > 0; --n, ++currentDest)
        ::new (&*currentDest) pair<int, float>(value);
}

template <typename OutputIterator, typename T> OutputIterator fill_n(OutputIterator first, uint32_t n, const T& value);
// fill_n<generic_iterator<float*>> is 0x0042efc0, fill_n<float*> is 0x0042b5b0 (other slices)

template <typename ForwardIterator, typename T>
inline void uninitialized_fill_n_impl(ForwardIterator first, uint32_t n, const T& value, true_type)
{
    fill_n(first, n, value);
}

template <typename T> inline void uninitialized_fill_n_ptr(T* first, uint32_t n, const T& value)
{
    uninitialized_fill_n_impl(generic_iterator<T>(first), n, value, has_trivial_constructor<T>());
}

template <typename T> inline T* fill_n_impl(T* first, uint32_t n, const T& value)
{
    for (; n-- > 0; ++first)
        *first = value;
    return first;
}

// @ 0x0052cbc0 ??$fill_n@
template <> pair<int, float>* fill_n(pair<int, float>* first, uint32_t n, const pair<int, float>& value)
{
    return fill_n_impl(first, n, value);
}

template <typename T> struct is_scalar : public false_type {};
template <> struct is_scalar<float> : public true_type {};

template <bool bIsScalar> struct fill_imp {
    template <typename ForwardIterator, typename T>
    static void do_fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        for (; first != last; ++first)
            *first = value;
    }
};
template <> struct fill_imp<true> {
    template <typename ForwardIterator, typename T>
    static void do_fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        const T temp(value);
        for (; first != last; ++first)
            *first = temp;
    }
};

template <typename ForwardIterator, typename T>
inline void fill(ForwardIterator first, ForwardIterator last, const T& value)
{
    fill_imp<is_scalar<T>::value>::do_fill(first, last, value);
}

// ---------------------------------------------------------------- vectors
template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    VectorBase(uint32_t n, const sp_vector_allocator& allocator)
    {
        mpBegin = DoAllocate(n);
        mpEnd = mpBegin;
        mpCapacity = mpBegin + n;
    }
    ~VectorBase();
    T* DoAllocate(uint32_t n)
    {
        return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), 4, 0) : 0;
    }
};

// @ 0x0052ce90 ??0?$VectorBase@U?$pair@HM@eastl@@@eastl@@
// (emitted out of line where the inline expansion was declined)

template <typename T> struct vector : VectorBase<T> {
    typedef T value_type;
    typedef uint32_t size_type;
    vector(size_type n, const sp_vector_allocator& allocator);
    vector(size_type n, const value_type& value, const sp_vector_allocator& allocator)
        : VectorBase<T>(n, allocator)
    {
        uninitialized_fill_n_ptr(mpBegin, n, value);
        mpEnd = mpBegin + n;
    }
    ~vector();
    void swap(vector& x);
    T* insert(T* position, const value_type& value);
    T* erase(T* first, T* last);
    void DoInsertValue(T* position, const value_type& value);
    void DoAssignValues(size_type n, const value_type& value);
};

// @ 0x0052c230 ??0?$vector@U?$pair@HM@eastl@@@eastl@@
template <> vector<pair<int, float> >::vector(size_type n, const sp_vector_allocator& allocator)
    : VectorBase<pair<int, float> >(n, allocator)
{
    uninitialized_fill_n_ptr(mpBegin, n, value_type());
    mpEnd = mpBegin + n;
}

// @ 0x0052c2e0 ?insert@?$vector@U?$pair@HM@eastl@@@eastl@@
template <> pair<int, float>* vector<pair<int, float> >::insert(pair<int, float>* position, const value_type& value)
{
    const int n = (int)(position - mpBegin);
    if ((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new (mpEnd++) value_type(value);
    return mpBegin + n;
}

template <typename T> struct erase_frame { enum { value = 6 }; };   // erase() frames of the declined
template <> struct erase_frame<float> { enum { value = 4 }; };       // inline expansions

template <typename T> void vector<T>::DoAssignValues(size_type n, const value_type& value)
{
    if (n > (size_type)(mpCapacity - mpBegin)) {
        vector temp(n, value, mAllocator);
        swap(temp);
        ScratchSlots<21>();
    } else if (n > (size_type)(mpEnd - mpBegin)) {
        fill(mpBegin, mpEnd, value);
        uninitialized_fill_n_ptr(mpEnd, n - (size_type)(mpEnd - mpBegin), value);
        mpEnd += n - (size_type)(mpEnd - mpBegin);
    } else {
        fill_n(mpBegin, n, value);
        ScratchSlots<erase_frame<T>::value>();
        erase(mpBegin + n, mpEnd);
    }
}
// @ 0x0052c570 ?DoAssignValues@?$vector@U?$pair@HM@eastl@@@eastl@@
template void vector<pair<int, float> >::DoAssignValues(size_type n, const value_type& value);
// @ 0x0052c380 ?DoAssignValues@?$vector@M@eastl@@
template void vector<float>::DoAssignValues(size_type n, const value_type& value);

// ---------------------------------------------------------------- sorting pair<int,float> by .second (descending)
struct SecondGreater {
    bool operator()(const pair<int, float>& a, const pair<int, float>& b) const { return a.second > b.second; }
};
typedef pair<int, float> PairIF;

const PairIF& median(const PairIF& a, const PairIF& b, const PairIF& c, SecondGreater compare);  // 0x00533ba0

template <typename T> inline void iter_swap(T* a, T* b)
{
    const T temp = *a;
    *a = *b;
    *b = temp;
}

PairIF* get_partition(PairIF* first, PairIF* last, PairIF pivotValue, SecondGreater compare);
void adjust_heap(PairIF* first, int topPosition, int heapSize, int position, PairIF value, SecondGreater compare);
void make_heap(PairIF* first, PairIF* last, SecondGreater compare);
void partial_sort(PairIF* first, PairIF* middle, PairIF* last, SecondGreater compare);
void quick_sort_impl_helper(PairIF* first, PairIF* last, int kRecursionCount, SecondGreater compare);

// @ 0x0052cc10 ?get_partition@eastl@@
PairIF* get_partition(PairIF* first, PairIF* last, PairIF pivotValue, SecondGreater compare)
{
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        iter_swap(first, last);
    }
}

template <typename T> inline void promote_heap(T* first, int topPosition, int position, T value, SecondGreater compare)
{
    for (int parentPosition = (position - 1) >> 1; (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

// @ 0x0052cf80 ?adjust_heap@eastl@@
void adjust_heap(PairIF* first, int topPosition, int heapSize, int position, PairIF value, SecondGreater compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
}

// @ 0x0052cf00 ?make_heap@eastl@@
void make_heap(PairIF* first, PairIF* last, SecondGreater compare)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            const PairIF temp(*(first + parentPosition));
            adjust_heap(first, parentPosition, heapSize, parentPosition, temp, compare);
        } while (parentPosition != 0);
    }
}

inline void sort_heap(PairIF* first, PairIF* last, SecondGreater compare)
{
    for (; (last - first) > 1; --last) {
        const PairIF temp(*(last - 1));
        *(last - 1) = *first;
        adjust_heap(first, 0, (int)(last - first) - 1, 0, temp, compare);
    }
}

// @ 0x0052ccd0 ?partial_sort@eastl@@
void partial_sort(PairIF* first, PairIF* middle, PairIF* last, SecondGreater compare)
{
    make_heap(first, middle, compare);
    for (PairIF* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const PairIF temp(*i);
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    sort_heap(first, middle, compare);
}

// @ 0x0052c950 ?quick_sort_impl_helper@eastl@@
void quick_sort_impl_helper(PairIF* first, PairIF* last, int kRecursionCount, SecondGreater compare)
{
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        PairIF* const position = get_partition(first, last,
            median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
        quick_sort_impl_helper(position, last, --kRecursionCount, compare);
        last = position;
        ScratchSlots<9>();   // frames of the declined median() / get_partition() expansions
    }
    if (kRecursionCount == 0)
        partial_sort(first, last, last, compare);
}

}  // namespace eastl

// ---------------------------------------------------------------- cSPSkinPaintClearDescription
struct Vector3 {    // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3(float x_, float y_, float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};
extern float kDefaultHairAngle;     // 0x015e0574

namespace EA {
struct RefCountTemplateInt {        // EA::RefCountTemplate<int>
    virtual ~RefCountTemplateInt();
    int mRefCount;                  // +0x04
    RefCountTemplateInt() : mRefCount(0) {}
};
namespace Swarm {
struct cDescription : RefCountTemplateInt {
    cDescription() {}
    virtual ~cDescription();
};
}  // namespace Swarm
}  // namespace EA

struct cSPSkinPaintClearDescription : EA::Swarm::cDescription {   // 0x70
    int mDiffuseUserColor;          // +0x08
    Vector3 mDiffuse;               // +0x0c
    Vector3 mSpecBump;              // +0x18
    float mGlossFactor;             // +0x24
    float mPhongFactor;             // +0x28
    float mPartBumpScale;           // +0x2c
    float mPartSpecScale;           // +0x30
    float mHairAngle;               // +0x34
    float mHairLength;              // +0x38
    float mHairWidth;               // +0x3c
    float mHairTaper;               // +0x40
    float mHairCurl;                // +0x44
    float mHairWave;                // +0x48
    float mHairMessiness;           // +0x4c
    float mHairDensity;             // +0x50
    bool mHairFaceCamera;           // +0x54
    uint64_t mHairTextureInstance;  // +0x58
    uint64_t mHairPrintGeomInstance;// +0x60
    uint32_t mBitFlags;             // +0x68
    uint32_t pad6c;
    cSPSkinPaintClearDescription();
    virtual ~cSPSkinPaintClearDescription();
};

// @ 0x0052d160 ??0cSPSkinPaintClearDescription
inline cSPSkinPaintClearDescription::cSPSkinPaintClearDescription()
    : mDiffuseUserColor(-1), mDiffuse(1.0f, 1.0f, 1.0f), mSpecBump(0.0f, 1.0f, 0.5f), mGlossFactor(0.5f),
      mPhongFactor(1.0f), mPartBumpScale(1.0f), mPartSpecScale(1.0f), mHairAngle(kDefaultHairAngle),
      mHairLength(0.0f), mHairWidth(0.03f), mHairTaper(1.0f), mHairCurl(0.0f), mHairWave(0.0f),
      mHairMessiness(0.0f), mHairDensity(1.0f), mHairFaceCamera(true), mHairTextureInstance(0),
      mHairPrintGeomInstance(0), mBitFlags(0)
{
}

struct IStream;
void ReadClearDescription(IStream* stream, int version, cSPSkinPaintClearDescription* params);    // 0x0052e030
void WriteClearDescription(IStream* stream, cSPSkinPaintClearDescription* params);                 // 0x0052e1f0

// @ 0x0052d0d0 ?ReadClearDescriptionCommand
cSPSkinPaintClearDescription* ReadClearDescriptionCommand(IStream* stream, int version)
{
    cSPSkinPaintClearDescription* const p = new ("Swarm", 0, 0, 0, 0) cSPSkinPaintClearDescription();
    ReadClearDescription(stream, version, p);
    return p;
}

// @ 0x0052d310 ?WriteClearDescriptionCommand
void WriteClearDescriptionCommand(cSPSkinPaintClearDescription* params, IStream* stream)
{
    WriteClearDescription(stream, params);
}

// ---------------------------------------------------------------- ArgScript paint commands
namespace ArgScript {
struct cIParser;
struct cICommand {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
struct cCommandBase : cICommand {
    cIParser* mParser;
    int mRefCount;
    cCommandBase();                 // 0x0083c800
};
struct cFormatParser {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual void AddParser(const char* name, cICommand* command);   // +0x18
};
}  // namespace ArgScript

struct cCommandStateT_cEffectsParser : ArgScript::cCommandBase {
    cCommandStateT_cEffectsParser() {}
    virtual void AddRef();
};
struct cCommandT_cEffectsParser : cCommandStateT_cEffectsParser {
    cCommandT_cEffectsParser() {}
    virtual void AddRef();
};
struct cSPSkinPaintClearCommand : cCommandT_cEffectsParser {
    uint32_t pad0c;
    cSPSkinPaintClearCommand() {}
    virtual void ParseLine();
};
extern const char* kSPSkinPaintClearName;       // "spSkinPaintClear"
extern const char* kSPSkinPaintSettingsName;    // "spSkinPaintSettings"

// @ 0x0052d330 ?SWARM_SPSkinPaintClearAddCommands
void SWARM_SPSkinPaintClearAddCommands(ArgScript::cFormatParser* parser)
{
    parser->AddParser(kSPSkinPaintClearName, new ("ArgScript/SPSkinPaintClear", 0, 0, 0, 0) cSPSkinPaintClearCommand());
    parser->AddParser(kSPSkinPaintSettingsName, new ("ArgScript/SPSkinPaintClear", 0, 0, 0, 0) cSPSkinPaintClearCommand());
}
