// Slice s00546f80: EASTL template instances and implicit special members used by
// SP::Feed (SPFeedXml.cpp): AtomEntry/Link/FeedDescription destructors, vector
// reserve/push_back/DoInsertValue, vector_map insert, string16 find_*_not_of.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP (no /EHsc).

typedef unsigned int size_type;
template<int N> inline void ScratchSlots() { unsigned int s[N]; }
typedef int ptrdiff_t;

inline void* operator new(unsigned int, void* p) { return p; }
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)

extern wchar_t gEmptyString16[];
void* EASTL_Allocate(void* pAllocator, unsigned int n, unsigned int alignment, unsigned int offset);  // 0x0042dee0

inline size_type CharStrlen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (size_type)(p - s);
}

namespace eastl {

// Allocator used by basic_string (empty) and by containers (8 bytes in retail).
struct allocator {
    allocator() {}
    void deallocate(void* p, size_type) { delete[] (char*)p; }
};
struct container_allocator {
    unsigned int mData[2];
    void deallocate(void* p, size_type) { delete[] (char*)p; }
};
// SP's vector allocator keeps a header word in front of each block.
struct sp_vector_allocator {
    unsigned int mData[2];
    void deallocate(void* p, size_type) {
        if (((unsigned int*)p)[-1])
            delete[] (char*)p;
    }
};

template <typename T> inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }

template <typename T, typename A = allocator>
struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;

    enum { npos = (size_type)-1 };
    basic_string(const A& allocator = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {
        mpBegin = (T*)gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    basic_string(const basic_string& x);
    ~basic_string() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(T* p, size_type n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    basic_string& operator=(const basic_string& x);

    size_type find_first_not_of(const T* p, size_type position, size_type n) const;
    size_type find_last_not_of(const T* p, size_type position, size_type n) const;
};
typedef basic_string<wchar_t> string16;
typedef basic_string<char> string8;

const wchar_t* CharTypeStringFindFirstNotOf(const wchar_t* p1Begin, const wchar_t* p1End,
                                            const wchar_t* p2Begin, const wchar_t* p2End);   // 0x005497e0
const wchar_t* CharTypeStringRFindFirstNotOf(const wchar_t* p1RBegin, const wchar_t* p1REnd,
                                             const wchar_t* p2Begin, const wchar_t* p2End);  // 0x00549840

// @ 0x00547900
template <>
size_type basic_string<wchar_t, allocator>::find_first_not_of(const wchar_t* p, size_type position, size_type n) const {
    if (position <= (size_type)(mpEnd - mpBegin)) {
        const wchar_t* const pResult = CharTypeStringFindFirstNotOf(mpBegin + position, mpEnd, p, p + n);
        if (pResult != mpEnd)
            return (size_type)(pResult - mpBegin);
    }
    return npos;
}

// @ 0x00547970
template <>
size_type basic_string<wchar_t, allocator>::find_last_not_of(const wchar_t* p, size_type position, size_type n) const {
    const size_type nLength = (size_type)(mpEnd - mpBegin);
    if (nLength) {
        const wchar_t* const pEnd = mpBegin + min_alt(nLength - 1, position) + 1;
        const wchar_t* const pResult = CharTypeStringRFindFirstNotOf(pEnd, mpBegin, p, p + n);
        if (pResult != mpBegin)
            return (size_type)((pResult - 1) - mpBegin);
    }
    return npos;
}

template <typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
    pair(const T1& x, const T2& y) : first(x), second(y) {}
};

template <typename T> struct less {
    bool operator()(const T& a, const T& b) const { return a < b; }
};
template <typename Key, typename Value, typename Compare>
struct map_value_compare {
    Compare c;
    bool operator()(const Value& a, const Value& b) const { return c(a.first, b.first); }
};

template <typename T, typename Allocator>
struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    ~VectorBase() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
    }
    T* DoAllocate(size_type n) {
        return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), __alignof(T), 0) : 0;
    }
    void DoFree(T* p, size_type n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    size_type GetNewCapacity(size_type currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
};


template <typename T> T* uninitialized_copy_ptr(T* first, T* last, T* result);

struct random_access_iterator_tag {};
struct false_type {};
template <typename T>
inline T* copy_backward_impl(T* first, T* last, T* resultEnd) {
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
template <typename T>
inline T* copy_backward(T* first, T* last, T* resultEnd) {
    const bool t38 = false, n12 = false, n21 = false;   // type-trait flags (names fix the /Od slot order)
    return copy_backward_impl(first, last, resultEnd);
}

template <typename T, typename Allocator = container_allocator>
struct vector : VectorBase<T, Allocator> {
    typedef VectorBase<T, Allocator> base_type;
    using base_type::mpBegin;
    using base_type::mpEnd;
    using base_type::mpCapacity;
    using base_type::mAllocator;

    ~vector() { DoDestroyValues(mpBegin, mpEnd); }
    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    size_type capacity() const { return (size_type)(mpCapacity - mpBegin); }
    void reserve(size_type n) {
        if (n > (size_type)(mpCapacity - mpBegin)) {
            T* const pNewData = this->DoAllocate(n);
            eastl::uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
            ScratchSlots<8>();   // frame of the (declined) inline uninitialized_copy
            this->DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
            const ptrdiff_t nPrevSize = mpEnd - mpBegin;
            mpBegin = pNewData;
            mpEnd = pNewData + nPrevSize;
            mpCapacity = mpBegin + n;
        }
    }
    void push_back() {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
    }
    T* insert(T* position, const T& value) {
        const ptrdiff_t n = position - mpBegin;
        if ((mpEnd == mpCapacity) || (position != mpEnd))
            DoInsertValue(position, value);
        else
            ::new (mpEnd++) T(value);
        return mpBegin + n;
    }
    void DoInsertValue(T* position, const T& value);
};

template <typename Key, typename T, typename Compare>
struct vector_map : vector<pair<Key, T> > {
    typedef vector<pair<Key, T> > base_type;
    typedef pair<Key, T> value_type;
    typedef value_type* iterator;
    typedef map_value_compare<Key, value_type, Compare> value_compare;
    using base_type::mpBegin;
    using base_type::mpEnd;
    value_compare mValueCompare;

    pair<iterator, bool> insert(const value_type& value);
    iterator insert(iterator position, const value_type& value);
};

template <typename ForwardIterator, typename T, typename Compare>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare);

}  // namespace eastl

namespace EA {
struct Variant {
    struct Generic { unsigned int mData[4]; };
    union {
        Generic mGeneric;
        int mInt32;
    };
    unsigned short mFlags;          // +0x10
    unsigned short mTypeId;         // +0x12
    enum { kFlagAllocated = 4 };
    Variant() : mFlags(0), mTypeId(0) {}
    Variant(const Variant& x);                                     // 0x00548d90 (via Link)
    ~Variant() {
        if (mFlags & kFlagAllocated)
            Destruct(false);
    }
    Variant& operator=(const Variant& x);                          // 0x00542b80
    void Destruct(bool bReconstruct);                              // 0x0093db80
};

template <typename T> struct RefCountTemplate {
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
    T mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    int Release() {
        int count = mRefCount - 1;
        mRefCount = mRefCount - 1;
        if (count)
            return count;
        mRefCount = 1;
        delete this;
        return 0;
    }
};

template <typename T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}  // namespace EA

namespace SP {
namespace Feed {

using eastl::string16;
using eastl::string8;

struct Person : EA::RefCountTemplate<int> {
    string16 mName;
    unsigned __int64 mnID;
};

// @ 0x005476e0 sym=??0Link@Feed@SP@@QAE@XZ
// @ 0x005477a0 sym=??1Link@Feed@SP@@QAE@XZ
// Name/type/value record (0x34 bytes); its constructor and destructor are implicit.
struct Link {
    string16 mName;                 // +0x00
    string16 mType;                 // +0x10
    EA::Variant mValue;             // +0x20
};

// @ 0x00547840 sym=??1FeedDescription@Feed@SP@@QAE@XZ
struct FeedDescription {            // 0x70 bytes; implicit destructor
    FeedDescription();
    string16 mAuthor;               // +0x00
    unsigned __int64 mnAuthorID;    // +0x10
    string16 mTitle;                // +0x18
    string16 mSubtitle;             // +0x28
    __int64 mUpdated;               // +0x38
    unsigned int mnSubCount;        // +0x40
    string8 mLinkURL;               // +0x44
    string8 mID;                    // +0x54
    unsigned int mnIDHash;          // +0x64
    int mFeedType;                  // +0x68
    unsigned int pad6C;
};

typedef eastl::pair<unsigned int, string8> IDString;   // 0x14 bytes

struct AtomEntry {                  // retail: 0x118 bytes
    AtomEntry();
    ~AtomEntry();
    string8 mID;                                    // +0x00
    unsigned __int64 mnAssetID;                     // +0x10
    string16 mTitle;                                // +0x18
    __int64 mUpdated;                               // +0x28
    __int64 mPublished;                             // +0x30
    __int64 mTime38;                                // +0x38
    __int64 mParentAuthorID;                        // +0x40
    string16 mParentScreenName;                     // +0x48
    __int64 mTime58;                                // +0x58
    __int64 mOriginalAuthorID;                      // +0x60
    string16 mOriginalScreenName;                   // +0x68
    eastl::vector<Link, eastl::sp_vector_allocator> mLinkList;   // +0x78
    eastl::vector<IDString> mIDStrings;             // +0x8c
    unsigned int padA0;
    EA::AutoRefCount<Person> mpAuthor;              // +0xa4
    string8 mThumbLink;                             // +0xa8
    string8 mAssetLink;                             // +0xb8
    unsigned int padC8;
    unsigned int mnFlagsCC;                         // +0xcc
    string16 mSummary;                              // +0xd0
    eastl::vector<string16> mTags;                  // +0xe0
    unsigned int padF4;
    eastl::vector<unsigned int> mTagHashes;         // +0xf8
    unsigned int pad10C;
    bool mbFlag110;                                 // +0x110
    unsigned int pad114;
};


}  // namespace Feed
}  // namespace SP

namespace eastl {
using SP::Feed::Link;
using SP::Feed::FeedDescription;
using SP::Feed::IDString;

// @ 0x005471e0 sym=??1?$vector@ULink@Feed@SP@@Usp_vector_allocator@eastl@@@eastl@@QAE@XZ
// (vector<Link>::~vector, emitted from AtomEntry::~AtomEntry)

struct char16less {
    bool operator()(const wchar_t* a, const wchar_t* b) const { return wcscmp(a, b) < 0; }
};

typedef vector_map<const wchar_t*, unsigned int, char16less> NameIDMap;

template <typename Key, typename T, typename Compare>
pair<typename vector_map<Key, T, Compare>::iterator, bool>
vector_map<Key, T, Compare>::insert(const value_type& value) {
    const iterator itLB(lower_bound(this->begin(), this->end(), value.first, mValueCompare));
    if ((itLB != this->end()) && !mValueCompare(value, *itLB))
        return pair<iterator, bool>(itLB, false);
    return pair<iterator, bool>(base_type::insert(itLB, value), true);
}

template <typename Key, typename T, typename Compare>
typename vector_map<Key, T, Compare>::iterator
vector_map<Key, T, Compare>::insert(iterator position, const value_type& value) {
    iterator itLB;
    if ((position != this->end()) && mValueCompare(value, *position))
        itLB = lower_bound(this->begin(), position, value.first, mValueCompare);
    else
        itLB = lower_bound(position, this->end(), value.first, mValueCompare);
    if ((itLB == this->end()) || mValueCompare(value, *itLB))
        itLB = base_type::insert(itLB, value);
    ScratchSlots<2>();   // frame of the declined inline base_type::insert
    return itLB;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::DoInsertValue(T* position, const T& value) {
    if (mpEnd != mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) T(*(mpEnd - 1));
        eastl::copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_type nPrevSize = (size_type)(mpEnd - mpBegin);
        const size_type nNewSize = this->GetNewCapacity(nPrevSize);
        T* const pNewData = this->DoAllocate(nNewSize);
        T* pNewEnd = eastl::uninitialized_copy_ptr(mpBegin, position, pNewData);
        ::new (pNewEnd) T(value);
        pNewEnd = eastl::uninitialized_copy_ptr(position, mpEnd, ++pNewEnd);
        ScratchSlots<27>();   // frame of the declined inline uninitialized_copy_ptr<Link>
        this->DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

struct PtrPair16 { const wchar_t* first; unsigned __int64 second; };   // 16-byte map element
typedef pair<const wchar_t*, unsigned int> NameID;

// Explicit instantiations: one emitted copy per retail function.
// @ 0x00547240 sym=?reserve@?$vector@UPtrPair16@eastl@@
template void vector<PtrPair16>::reserve(size_type);
// @ 0x00547440 sym=?reserve@?$vector@U?$pair@PB_WI@eastl@@
template void vector<NameID>::reserve(size_type);
// @ 0x00547320 sym=?insert@?$vector_map@PB_WIUchar16less@eastl@@@eastl@@QAE?AU?$pair@PAU?$pair@PB_WI
template pair<NameIDMap::iterator, bool> NameIDMap::insert(const NameIDMap::value_type&);
struct MemFn12 { unsigned int mData[3]; };   // mem_fun1_t<void, AtomParser, const wchar_t**>
typedef vector_map<const wchar_t*, MemFn12, char16less> NameFnMap;
// @ 0x00547520 sym=?insert@?$vector_map@PB_WUMemFn12@eastl@@Uchar16less@2@@eastl@@QAE?AU?$pair@PAU?$pair@PB_WUMemFn12
template pair<NameFnMap::iterator, bool> NameFnMap::insert(const NameFnMap::value_type&);
// @ 0x00547640 sym=?push_back@?$vector@UFeedDescription@Feed@SP@@Usp_vector_allocator
template void vector<FeedDescription, sp_vector_allocator>::push_back();
// @ 0x00547a10 sym=?DoInsertValue@?$vector@ULink@Feed@SP@@
template void vector<Link, sp_vector_allocator>::DoInsertValue(Link*, const Link&);
// @ 0x00547cf0 sym=?DoDestroyValues@?$vector@U?$pair@IU?$basic_string
template void vector<IDString>::DoDestroyValues(IDString*, IDString*);
// @ 0x00547d30 sym=??1?$VectorBase@U?$pair@IU?$basic_string
template VectorBase<IDString, container_allocator>::~VectorBase();
// @ 0x00547d80 sym=?insert@?$vector_map@IU?$basic_string
template vector_map<unsigned int, string8, less<unsigned int> >::iterator
vector_map<unsigned int, string8, less<unsigned int> >::insert(iterator, const value_type&);
// @ 0x00547e50 sym=?DoDestroyValues@?$vector@U?$basic_string@_W
template void vector<string16>::DoDestroyValues(string16*, string16*);
// @ 0x005477e0 sym=??1?$pair@IU?$basic_string
template struct pair<unsigned int, string8>;

}  // namespace eastl

// Force emission of implicit special members that the retail build emitted out of line.
void ForceFeedSpecialMembers(SP::Feed::Link* pLink, SP::Feed::FeedDescription* pFeed) {
    ::new (pLink) SP::Feed::Link();
    pLink->~Link();
    pFeed->~FeedDescription();
}

namespace SP { namespace Feed {
// @ 0x00546f80 sym=??1AtomEntry@Feed@SP@@QAE@XZ
AtomEntry::~AtomEntry() {
    mpAuthor = 0;
}
}}
