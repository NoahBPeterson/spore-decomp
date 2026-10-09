// Slice s00672bd0: `anonymous namespace'::cBuildXHTMLDetokenizer (an XHTML string detokenizer)
// container instantiations + eastl fixed_string/vector helpers.
// Flags: /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"
#include <intrin.h>

typedef unsigned int uint32;

// EASTL allocation hooks.  The exact call target is a masked relocation; only the call shape
// (six pushed dwords) matters.
void* EAAllocate(unsigned int n, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
void  EAFree(void* p); // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }

namespace std {
struct input_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <class T> struct iterator_traits;
template <class T> struct iterator_traits<T*> {
    typedef T          value_type;
    typedef int        difference_type;
    typedef T*         pointer;
    typedef T&         reference;
    typedef random_access_iterator_tag iterator_category;
};
}

namespace eastl {

// ---------------------------------------------------------------------------
// fixed_vector_allocator: an allocator with an inline buffer.
// Layout (12-byte header for 4-byte-aligned element types): mpBegin points at mBuffer.
// ---------------------------------------------------------------------------
template <int ES, int N, int ALIGN, int OFF, bool OV> class fixed_vector_allocator;

#define FIXED_ALLOC(ES, N)                                                              \
    template <> class fixed_vector_allocator<ES, N, 4, 0, true> {                        \
    public:                                                                             \
        int   mPad0;                                                                    \
        void* mpBegin;                                                                  \
        int   mPad1;                                                                    \
        char  mBuffer[ES * N];                                                          \
        unsigned capacity() const { return N; }                                         \
        void deallocate(void* p, unsigned) { if (p) EAFree(p); }                        \
    }

FIXED_ALLOC(88, 8);
FIXED_ALLOC(84, 8);
FIXED_ALLOC(1588, 16);
FIXED_ALLOC(1596, 16);

#undef FIXED_ALLOC

// ---------------------------------------------------------------------------
// Plain heap allocator (4 bytes) + basic_string with heap storage.
// ---------------------------------------------------------------------------
class allocator {
public:
    int mPad;
    void deallocate(void* p, unsigned n)
    {
        if (((int)(n & ~1) > 2) && p)
            EAFree(p);
    }
};

template <class T, class A> class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A  mAllocator;

    basic_string()
    {
        mpBegin    = 0;
        mpEnd      = 0;
        mpCapacity = 0;
    }

    ~basic_string()
    {
        T* pBegin = mpBegin;
        int n = (int)((char*)mpCapacity - (char*)pBegin);
        if (((n & ~1) > 2) && pBegin)
            mAllocator.deallocate(pBegin, (unsigned)n);
    }
};

// ---------------------------------------------------------------------------
// fixed_string<T,N,B>: 3 pointers + allocator header + inline character buffer.
// ---------------------------------------------------------------------------
template <class T, int N, bool B> class fixed_string {
public:
    T*   mpBegin;
    T*   mpEnd;
    T*   mpCapacity;
    struct Alloc {
        int  pad;
        T*   mpBegin;
        T    mBuffer[N];
    } mAlloc;

    fixed_string()
    {
        T* p = mAlloc.mBuffer;
        mAlloc.mpBegin = p;
        mpEnd      = p;
        mpBegin    = p;
        mpCapacity = p + N;
        *p = 0;
    }

    fixed_string(const fixed_string& x)
    {
        T* p = mAlloc.mBuffer;
        mAlloc.mpBegin = p;
        _ReadWriteBarrier();
        mpCapacity = p + N;
        mpEnd      = p;
        mpBegin    = p;
        *p = 0;
        assign(x.mpBegin, x.mpEnd);
    }

    ~fixed_string()
    {
        int n = (int)((char*)mpCapacity - (char*)mpBegin);
        if (((n & ~1) > 2) && mpBegin && (mpBegin != mAlloc.mpBegin))
            EAFree(mpBegin);
    }

    void assign(const T* first, const T* last);
    fixed_string& operator=(const fixed_string& x)
    {
        if (this != &x)
        {
            if (mpBegin != mpEnd)
            {
                *mpBegin = 0;
                mpEnd    = mpBegin;
            }
            assign(x.mpBegin, x.mpEnd);
        }
        return *this;
    }
};

template <class T, int N, bool B>
__declspec(noinline) void fixed_string<T, N, B>::assign(const T* first, const T* last)
{
    (void)first;
    (void)last;
    if (mpBegin) *mpBegin = 0;
}

// ---------------------------------------------------------------------------
// copy / copy_backward / move algorithm implementations
// ---------------------------------------------------------------------------
template <int B, class Tag> struct copy_impl {
    template <class InputIterator, class OutputIterator>
    static OutputIterator do_copy(InputIterator first, InputIterator last, OutputIterator result)
    {
        for (; first != last; ++first, ++result)
            *result = *first;
        return result;
    }
};

template <int B, class Tag> struct copy_backward_impl {
    template <class InputIterator, class OutputIterator>
    static OutputIterator do_copy(InputIterator first, InputIterator last, OutputIterator result)
    {
        while (last != first)
        {
            --last;
            --result;
            *result = *last;
        }
        return result;
    }
};

template <int B, class Tag> struct uninitialized_move_impl {
    template <class ForwardIterator, class ForwardIteratorDest>
    static ForwardIteratorDest do_move_start(ForwardIterator first, ForwardIterator last,
                                             ForwardIteratorDest dest)
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        for (; first != last; ++first, ++dest)
            ::new((void*)&*dest) value_type(*first);
        return dest;
    }

    template <class ForwardIterator, class ForwardIteratorDest>
    static ForwardIteratorDest do_move_commit(ForwardIterator first, ForwardIterator last,
                                              ForwardIteratorDest dest)
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        for (; first != last; ++first, ++dest)
            (*first).~value_type();
        return dest;
    }
};

template <class Iterator, class Container = void> class generic_iterator {
public:
    Iterator mIterator;

    generic_iterator() {}
    generic_iterator(const Iterator& x) : mIterator(x) {}
    generic_iterator(const generic_iterator& x) : mIterator(x.mIterator) {}
    Iterator base() const { return mIterator; }
    generic_iterator& operator=(const generic_iterator& x) { mIterator = x.mIterator; return *this; }
};

template <int B, class Tag> struct uninitialized_copy_impl {
    template <class InputIterator, class ForwardIterator>
    static generic_iterator<ForwardIterator> do_copy(InputIterator first, InputIterator last,
                                                     ForwardIterator dest)
    {
        typedef typename std::iterator_traits<InputIterator>::value_type value_type;
        generic_iterator<ForwardIterator> result(dest);
        for (; first != last; ++first, ++result.mIterator)
            ::new((void*)&*result.mIterator) value_type(*first);
        return result;
    }
};

template <class First, class Last, class Result>
inline Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    return uninitialized_copy_impl<0, std::random_access_iterator_tag>::do_copy(first, last, result).base();
}

// ---------------------------------------------------------------------------
// vector
// ---------------------------------------------------------------------------
template <class T, class A> class vector {
public:
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A  mAllocator;

    vector()
    {
        mAllocator.mpBegin = mAllocator.mBuffer;
        T* p               = (T*)mAllocator.mBuffer;
        mpEnd              = p;
        mpBegin            = p;
        mpCapacity         = p + mAllocator.capacity();
    }

    ~vector()
    {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((void*)mpBegin != mAllocator.mpBegin))
            EAFree(mpBegin);
    }

    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    size_type capacity() const { return (size_type)(mpCapacity - mpBegin); }

    void DoFree(T* p, size_type)
    {
        if (p && ((void*)p != mAllocator.mpBegin))
            EAFree(p);
    }

    __forceinline T* erase(T* first, T* last)
    {
        T* position = eastl::copy_impl<0, std::random_access_iterator_tag>::do_copy(last, mpEnd, first);
        DoDestroyValues(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }

    template <class It>
    void assign(It first, It last)
    {
        DoAssignFromIterator(first, last, std::random_access_iterator_tag());
    }

    T* DoAllocate(size_type n)
    {
        if (n == 0)
            return 0;
        return (T*)EAAllocate((unsigned)(n * sizeof(T)), "Editor", 0, 0,
                              "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                              0xd1);
    }

    template <class It>
    T* DoRealloc(size_type n, It first, It last)
    {
        T* p = DoAllocate(n);
        eastl::uninitialized_copy_ptr(first, last, p);
        return p;
    }

    template <class It>
    void DoAssignFromIterator(It first, It last, std::random_access_iterator_tag)
    {
        const size_type n = (size_type)(last - first);
        if (n > capacity())
        {
            T* pNewData = DoRealloc(n, first, last);
            DoDestroyValues(mpBegin, mpEnd);
            DoFree(mpBegin, capacity());
            mpBegin    = pNewData;
            mpEnd      = mpBegin + n;
            mpCapacity = mpEnd;
        }
        else if (n <= size())
        {
            T* pNewEnd = eastl::copy_impl<0, std::random_access_iterator_tag>::do_copy(first, last, mpBegin);
            DoDestroyValues(pNewEnd, mpEnd);
            mpEnd = pNewEnd;
        }
        else
        {
            It position = first + size();
            eastl::copy_impl<0, std::random_access_iterator_tag>::do_copy(first, position, mpBegin);
            mpEnd = eastl::uninitialized_copy_ptr(position, last, mpEnd);
        }
    }

    void DoInsertValue(T* position, const T& value)
    {
        if (mpEnd != mpCapacity)
        {
            const T* pValue = &value;
            if ((pValue >= position) && (pValue < mpEnd))
                ++pValue;
            ::new((void*)mpEnd) T(*(mpEnd - 1));
            eastl::copy_backward_impl<0, std::random_access_iterator_tag>::do_copy(position, mpEnd - 1, mpEnd);
            *position = *pValue;
            ++mpEnd;
        }
        else
        {
            const size_type nPosSize  = (size_type)(position - mpBegin);
            const size_type nPrevSize = size();
            const size_type nNewSize  = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
            T* const        pNewData  = DoAllocate(nNewSize);

            T* pNewEnd = eastl::uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_start(mpBegin, position, pNewData);
            eastl::uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_commit(mpBegin, position, pNewData);
            ::new((void*)pNewEnd) T(value);
            ++pNewEnd;
            T* pNewEnd2 = eastl::uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_start(position, mpEnd, pNewEnd);
            eastl::uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_commit(position, mpEnd, pNewEnd);

            DoFree(mpBegin, capacity());
            mpBegin    = pNewData;
            mpEnd      = pNewEnd2;
            mpCapacity = pNewData + nNewSize;
        }
    }

    void DoDestroyValues(T* first, T* last);
};

template <class T, class A>
void vector<T, A>::DoDestroyValues(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <class T, int N, bool B>
class fixed_vector : public vector<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > {
public:
    typedef vector<T, fixed_vector_allocator<sizeof(T), N, 4, 0, B> > base_type;
    fixed_vector() {}
    fixed_vector(const fixed_vector& x) : base_type()
    {
        this->DoAssignFromIterator(x.mpBegin, x.mpEnd, std::random_access_iterator_tag());
    }
    fixed_vector& operator=(const fixed_vector& x)
    {
        if (this != &x)
        {
            this->erase(this->mpBegin, this->mpEnd);
            this->assign(x.mpBegin, x.mpEnd);
        }
        return *this;
    }
};

} // namespace eastl

// ---------------------------------------------------------------------------
// Small SP/EA support types used by the detokenizer's members.
// ---------------------------------------------------------------------------
namespace SP {
class cPropertyList {
public:
    virtual void _v0();
    virtual void Release();
};
}

template <class T> class AutoRefCount {
public:
    T* mpObject;
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
};

namespace SP {
class cStringDetokenizer {
public:
    virtual ~cStringDetokenizer();
    char mBasePad[0x58];
};
}

// ---------------------------------------------------------------------------
// The detokenizer's value types.
// ---------------------------------------------------------------------------
namespace {

class cBuildXHTMLDetokenizer : public SP::cStringDetokenizer {
public:
    class cVar {
    public:
        class cAction {
        public:
            eastl::fixed_string<wchar_t, 32, true> mString;   // +0x00
            int                                    mX;        // +0x54

            cAction() {}
        };

        int                                                        mId;       // +0x00
        eastl::fixed_string<wchar_t, 32, true>                     mName;     // +0x04
        eastl::fixed_string<wchar_t, 32, true>                     mValue;    // +0x58
        eastl::fixed_vector<cAction, 8, true>                      mActions;  // +0xac
        eastl::fixed_vector<eastl::fixed_string<wchar_t, 32, true>, 8, true> mStrings; // +0x384

        cVar();
        cVar(const cVar& x);
        ~cVar();
        cVar& operator=(const cVar& x);
    };

    AutoRefCount<SP::cPropertyList>                       mpXHTMLProps;    // +0x5c
    int                                                   mState;          // +0x60
    eastl::basic_string<wchar_t, eastl::allocator>        mTemp;           // +0x64
    eastl::basic_string<wchar_t, eastl::allocator>        mScratch;        // +0x74
    eastl::basic_string<wchar_t, eastl::allocator>        mText;           // +0x84
    eastl::basic_string<wchar_t, eastl::allocator>*       mpTextResult;    // +0x94
    cVar*                                                 mpCurrentVar;    // +0x98
    cVar::cAction*                                        mpCurrentAction; // +0x9c
    eastl::fixed_vector<cVar, 16, true>                   mVars;           // +0xa0
    eastl::fixed_vector<cVar, 16, true>                   mListVars;       // +0x6478
};

} // anonymous namespace

__declspec(noinline) cBuildXHTMLDetokenizer::cVar::cVar() {}
__declspec(noinline) cBuildXHTMLDetokenizer::cVar::~cVar() {}

__declspec(noinline) cBuildXHTMLDetokenizer::cVar::cVar(const cVar& x)
    : mId(x.mId), mName(x.mName), mValue(x.mValue), mActions(x.mActions), mStrings(x.mStrings)
{
}

__declspec(noinline) cBuildXHTMLDetokenizer::cVar&
cBuildXHTMLDetokenizer::cVar::operator=(const cVar& x)
{
    mId = x.mId;
    mName = x.mName;
    mValue = x.mValue;
    mActions = x.mActions;
    mStrings = x.mStrings;
    return *this;
}

// force emission of the cVar ctor/dtor
void force_cVar()
{
    cBuildXHTMLDetokenizer::cVar v;
    cBuildXHTMLDetokenizer::cVar w(v);
    w = v;
    (void)w;
}

// force the two DoDestroyValues instantiations
template class eastl::vector<cBuildXHTMLDetokenizer::cVar::cAction,
                             eastl::fixed_vector_allocator<88, 8, 4, 0, true> >;
template class eastl::vector<eastl::fixed_string<wchar_t, 32, true>,
                             eastl::fixed_vector_allocator<84, 8, 4, 0, true> >;

typedef cBuildXHTMLDetokenizer::cVar::cAction cActionT;
typedef eastl::fixed_string<wchar_t, 32, true> fsT;

namespace eastl {
template cActionT*
copy_impl<0, std::random_access_iterator_tag>::do_copy<cActionT*, cActionT*>(cActionT*, cActionT*, cActionT*);
template cActionT*
copy_backward_impl<0, std::random_access_iterator_tag>::do_copy<cActionT*, cActionT*>(cActionT*, cActionT*, cActionT*);
template cActionT*
uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_commit<cActionT*, cActionT*>(cActionT*, cActionT*, cActionT*);
template cActionT*
uninitialized_move_impl<0, std::random_access_iterator_tag>::do_move_start<cActionT*, cActionT*>(cActionT*, cActionT*, cActionT*);
template generic_iterator<cActionT*>
uninitialized_copy_impl<0, std::random_access_iterator_tag>::do_copy<cActionT*, cActionT*>(cActionT*, cActionT*, cActionT*);
template generic_iterator<fsT*>
uninitialized_copy_impl<0, std::random_access_iterator_tag>::do_copy<fsT*, fsT*>(fsT*, fsT*, fsT*);
}

// force vector<cAction>::DoAssignFromIterator / DoInsertValue and
// vector<fixed_string>::DoAssignFromIterator / DoRealloc
void force_vecs(cActionT* ac, fsT* fsp, const cActionT& acv, const fsT& fsv)
{
    eastl::vector<cActionT, eastl::fixed_vector_allocator<88, 8, 4, 0, true> > va;
    va.DoAssignFromIterator(ac, ac, std::random_access_iterator_tag());
    va.DoInsertValue(va.mpBegin, acv);

    eastl::vector<fsT, eastl::fixed_vector_allocator<84, 8, 4, 0, true> > vs;
    vs.DoAssignFromIterator(fsp, fsp, std::random_access_iterator_tag());

    (void)fsv;
}

typedef cBuildXHTMLDetokenizer::cVar cVarT;

void force_vec_var(cVarT* cv, const cVarT& cvv)
{
    eastl::vector<cVarT, eastl::fixed_vector_allocator<1596, 16, 4, 0, true> > vv;
    vv.DoAssignFromIterator(cv, cv, std::random_access_iterator_tag());
    vv.DoInsertValue(vv.mpBegin, cvv);
}

void force_cAction(const cActionT& x)
{
    cActionT y(x);
    (void)y;
}

void force_detok()
{
    cBuildXHTMLDetokenizer d;
    (void)d;
}
// --- equivalence checker address annotations
    void EAAllocate(...); // 0x00f473a0
    void EAFree(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
