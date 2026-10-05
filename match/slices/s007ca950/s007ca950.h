// Shared EASTL container framework for the SP::cOption / property-command module.
// Reconstructed from retail disassembly (offline /O2 build, cl 15.00.30729, /EHsc /MD /TP).
//
// Retail layout notes (dev PDB differs in a few sizes):
//   eastl::allocator                 = 8 bytes  (dev PDB says 4)
//   eastl::fixed_vector_allocator<*> = 12 bytes: int, void* mpPoolBegin, void*
//   VectorBase<T,A>                  = 12 + sizeof(A)
//   vector<pair<u64,AR>, allocator>  = 0x14 -> vector_map = 0x18 (mCompare at +0x14)
//   fixed_vector<AR,4,1>             = 0x28 (cOption: +0xc .. +0x34)
//   fixed_vector<vector_map,4,1>     = 0x78 (cOption: +0x34 .. +0xac)

#ifndef SPORE_S007CA950_H
#define SPORE_S007CA950_H

typedef unsigned int uint32;
typedef unsigned __int64 uint64;

inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);

// EASTL allocation hooks (masked relocations).
void* __cdecl EASTL_allocator_allocate(unsigned int size, const char* name, int flags,
                                       int debugFlags, const char* file, int line);  // 0x00f473a0
void  __cdecl EASTL_allocator_deallocate(void* p);                                      // 0x00f47380

#define EASTL_ALLOCATOR_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace std {
struct random_access_iterator_tag {};
struct false_type {};
template <typename T> struct iterator_traits;
template <typename T> struct iterator_traits<T*> { typedef T value_type; };
}

namespace eastl {

// ---------------------------------------------------------------- allocator
struct allocator {              // retail: 8 bytes, trivially copyable
    int mPad0;                  // +0
    void* mpPoolBegin;          // +4
    void deallocate(void* p, unsigned int) { if (p && p != mpPoolBegin) EASTL_allocator_deallocate(p); }
};

template <int NodeSize, int NodeCount, int Alignment, int AlignmentOffset, bool bEnableOverflow>
struct fixed_vector_allocator { // retail: 12 bytes, mpPoolBegin at +4
    int   mOverflowAllocator;   // +0
    void* mpPoolBegin;          // +4
    void* mpPadEnd;             // +8 (uninitialized in retail)
    unsigned int capacity() const { return NodeCount; }
    void deallocate(void* p, unsigned int) {
        if (p && p != mpPoolBegin) EASTL_allocator_deallocate(p);
    }
};

template <typename T> struct less {
    bool operator()(const T& a, const T& b) const { return a < b; }
};

template <typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
    pair() {}
    pair(const T1& a, const T2& b) : first(a), second(b) {}
};

// ---------------------------------------------------------------- copy / fill
template <int B, typename Tag> struct copy_impl {
    template <typename In, typename Out>
    static Out do_copy(In first, In last, Out result) {
        for (; first != last; ++first, ++result)
            *result = *first;
        return result;
    }
};

template <int B, typename Tag> struct copy_backward_impl {
    template <typename In, typename Out>
    static Out do_copy(In first, In last, Out result) {
        while (last != first) {
            --last;
            --result;
            *result = *last;
        }
        return result;
    }
};

template <int B, typename Tag> struct uninitialized_move_impl {
    template <typename F, typename D>
    static D do_move_start(F first, F last, D dest) {
        typedef typename std::iterator_traits<F>::value_type value_type;
        for (; first != last; ++first, ++dest)
            ::new ((void*)&*dest) value_type(*first);
        return dest;
    }
    template <typename F, typename D>
    static D do_move_commit(F first, F last, D dest) {
        typedef typename std::iterator_traits<F>::value_type value_type;
        for (; first != last; ++first, ++dest)
            first->~value_type();
        return dest;
    }
};

template <typename T> T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
    T* d = result;
    for (; first != last; ++first, ++d)
        ::new ((void*)d) T(*first);
    return d;
}

template <typename It, typename T>
void fill(It first, It last, const T& value) {
    for (; first != last; ++first)
        *first = value;
}

// ---------------------------------------------------------------- vector
template <typename T, typename A>
struct VectorBase {
    T* mpBegin;      // +0
    T* mpEnd;        // +4
    T* mpCapacity;   // +8
    A  mAllocator;   // +12
};

template <typename T, typename A>
struct vector : VectorBase<T, A> {
    typedef VectorBase<T, A> base_type;
    typedef unsigned int size_type;
    typedef T value_type;
    typedef T* iterator;

    vector() { this->mpBegin = 0; this->mpEnd = 0; this->mpCapacity = 0; }
    ~vector();

    size_type size() const { return (size_type)(this->mpEnd - this->mpBegin); }
    size_type capacity() const { return (size_type)(this->mpCapacity - this->mpBegin); }

    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first) first->~T();
    }
    T* DoAllocate(size_type n) {
        if (n == 0) return 0;
        return (T*)EASTL_allocator_allocate((unsigned int)(n * sizeof(T)), "App", 0, 0,
                                            EASTL_ALLOCATOR_FILE, 0xd1);
    }
    void DoFree(T* p, size_type) { if (p) EASTL_allocator_deallocate(p); }
    T* DoRealloc(size_type n, const T* first, const T* last) {
        T* p = DoAllocate(n);
        uninitialized_copy_ptr(first, last, p);
        return p;
    }

    void DoInsertValue(T* position, const T& value);            // out of line
    void push_back();                                           // out of line
    T* insert(T* position, const T& value);                     // out of line
    void insert(T* position, size_type n, const T& value);      // out of line
    T* erase(T* first, T* last);                                // out of line
    void resize(size_type n);                                   // out of line

    template <typename It> void DoAssignFromIterator(It first, It last, std::random_access_iterator_tag);
    vector& operator=(const vector& x);
};

// ---------------------------------------------------------------- map_value_compare / vector_map
template <typename Key, typename Value, typename Compare>
struct map_value_compare {
    Compare c;
    bool operator()(const Value& a, const Value& b) const { return c(a.first, b.first); }
    bool operator()(const Key& a, const Value& b) const { return c(a, b.first); }
};

template <typename Key, typename T, typename Compare, typename Allocator, typename RA>
struct vector_map : RA {
    typedef RA base_type;
    typedef typename RA::value_type value_type;
    typedef typename RA::iterator iterator;
    typedef Key key_type;
    typedef map_value_compare<Key, value_type, Compare> value_compare;

    value_compare mValueCompare;

    pair<iterator, bool> insert(const value_type& value);
    iterator insert(iterator position, const value_type& value);
    T& operator[](const key_type& key);
};

// lower_bound: shape-only stub (masked relocation); must take (first,last,value,compare).
template <typename It, typename Key, typename Cmp>
It lower_bound(It first, It last, const Key& key, Cmp compare);

template <typename Key, typename T, typename C, typename A, typename RA>
pair<typename vector_map<Key, T, C, A, RA>::iterator, bool>
vector_map<Key, T, C, A, RA>::insert(const value_type& value) {
    iterator itEnd = this->mpEnd;
    iterator itLB = eastl::lower_bound(this->mpBegin, itEnd, value.first, mValueCompare);
    if ((itLB != itEnd) && !mValueCompare(value, *itLB))
        return pair<iterator, bool>(itLB, false);
    return pair<iterator, bool>(base_type::insert(itLB, value), true);
}

template <typename Key, typename T, typename C, typename A, typename RA>
typename vector_map<Key, T, C, A, RA>::iterator
vector_map<Key, T, C, A, RA>::insert(iterator position, const value_type& value) {
    iterator itEnd = this->mpEnd;
    iterator itLB;
    if ((position != itEnd) && mValueCompare(value, *position))
        itLB = eastl::lower_bound(this->mpBegin, position, value.first, mValueCompare);
    else
        itLB = eastl::lower_bound(position, itEnd, value.first, mValueCompare);
    if ((itLB == itEnd) || mValueCompare(value, *itLB))
        itLB = base_type::insert(itLB, value);
    return itLB;
}

template <typename Key, typename T, typename C, typename A, typename RA>
T& vector_map<Key, T, C, A, RA>::operator[](const key_type& key) {
    iterator itBegin = this->mpBegin;
    iterator itEnd = this->mpEnd;
    iterator it = eastl::lower_bound(itBegin, itEnd, key, mValueCompare);
    if ((it == itEnd) || mValueCompare(key, *it))
        it = base_type::insert(it, value_type(key, T()));
    return it->second;
}

// ---------------------------------------------------------------- fixed_vector
template <int N, int Align> struct aligned_buffer { char mBuffer[N]; };

template <typename T, int N, bool B>
struct fixed_vector : vector<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > {
    typedef vector<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > base_type;
    typedef typename base_type::size_type size_type;
    aligned_buffer<sizeof(T) * N, 4> mBuffer;

    T* buffer() { return (T*)mBuffer.mBuffer; }
    fixed_vector() {
        T* p = buffer();
        this->mAllocator.mpPoolBegin = p;
        this->mpBegin = p;
        this->mpEnd = p;
        this->mpCapacity = p + N;
    }
    fixed_vector(const fixed_vector& x) : base_type() {
        T* p = buffer();
        this->mAllocator.mpPoolBegin = p;
        this->mpBegin = p;
        this->mpEnd = p;
        this->mpCapacity = p + N;
        this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
    }
    fixed_vector& operator=(const fixed_vector& x) {
        if (&x != this) {
            this->erase(this->mpBegin, this->mpEnd);
            this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
        }
        return *this;
    }
};

}  // namespace eastl

// ---------------------------------------------------------------- SP / EA support types
namespace EA {
template <typename T> struct AutoRefCount {
    T* mpObject;   // +0
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x) {
        if (x.mpObject != mpObject) {
            T* pOld = mpObject;
            if (x.mpObject) x.mpObject->AddRef();
            mpObject = x.mpObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* pOld = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

struct Variant {
    unsigned int mData[4];   // +0
    unsigned short mFlags;   // +0x10
    unsigned short mTypeId;  // +0x12
    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() { if (mFlags & 4) Destruct(false); }
    Variant& operator=(const Variant& x);
    template <typename T> Variant& operator=(const T& x);
    void Destruct(bool bReconstruct);
};

namespace ResourceMan {
struct Key { unsigned int mInstance; unsigned int mType; unsigned int mGroup; unsigned int mPad; };
}
}  // namespace EA

namespace SP {

// Polymorphic resource object with AddRef (vtable slot 0) / Release (slot 1).
class cPropertyList {
public:
    virtual void AddRef();                                       // +0x00
    virtual void Release();                                      // +0x04
    virtual void v02(); virtual void v03(); virtual void v04();
    virtual void SetProperty(int id, const EA::Variant& value);  // +0x14
    virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(cPropertyList* p);                          // +0x30
    char pad[0x54 - 0x34];
};

// Stub of the property manager interface: slots 0x18/0x28/0x2c/0x30 used.
class IPropertyManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B();
    virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual bool HasPropertyList(uint32 a, uint32 b);                              // +0x28
    virtual bool GetPropertyList(uint32 a, uint32 b, EA::AutoRefCount<cPropertyList>& out);  // +0x2c
    virtual void v2C(cPropertyList* p);                                            // +0x30
};

IPropertyManager* PropertyManager();   // 0x0067de30

}  // namespace SP

namespace Editor {
class cPropertyList : public SP::cPropertyList {
public:
    cPropertyList();
};
}  // namespace Editor

#endif  // SPORE_S007CA950_H
