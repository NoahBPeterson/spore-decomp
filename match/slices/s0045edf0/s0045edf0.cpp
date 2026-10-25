// Slice s0045edf0: EA string-buffer (EASTL basic_string storage) helpers and a
// 4x4 matrix * vector transform.  /Od /Ob1 /MD /Gy /TP.
#include "types.h"

extern "C" __declspec(dllimport) void* memmove(void* d, const void* s, unsigned int n);
extern "C" void* memcpy(void* d, const void* s, unsigned int n);
extern "C" void* memset(void* d, int c, unsigned int n);
extern "C" void* EaAlloc(unsigned int n, const char* tag, int a, int b, const char* file, int line);  // 0xf473a0

// Fixed-buffer/overflow allocator subobject held at +0xc.  Its EASTL operator==
// is `return &a == &b;` (fixed_vector_allocator, fixed_pool.h), which is why the
// string's swap compares the subobject addresses.
struct FixedAlloc {
    uint32_t mOverflowAllocator;  // +0xc (empty eastl::allocator, padded)
    char*    mpPoolBegin;         // +0x10

    void* allocate(unsigned int n)
    {
        return EaAlloc(n, "Editor", 0, 0,
                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
};

inline bool operator==(const FixedAlloc& a, const FixedAlloc& b) { return &a == &b; }
inline bool operator!=(const FixedAlloc& a, const FixedAlloc& b) { return &a != &b; }

// eastl::basic_string<char, fixed_vector_allocator<...>>: {begin,end,cap} plus
// the allocator subobject; the fixed buffer pointer lives at +0x10.
struct StrBuf {
    typedef unsigned int size_type;
    enum { npos = -1 };

    char*        begin;      // +0
    char*        end;        // +4
    char*        cap;        // +8
    FixedAlloc   mAllocator; // +0xc

    StrBuf(const StrBuf& o);                                    // 0x45f240
    ~StrBuf() { DeallocateSelf(); }

    char* DoAllocate(size_type n) { char* p = (char*)mAllocator.allocate(n); return p; }
    static char* CharStringUninitializedCopy(const char* pSource, const char* pSourceEnd, char* pDestination)
    {
        memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource));
        return pDestination + (pSourceEnd - pSource);
    }
    // eastl::basic_string::GetNewCapacity
    static size_type GetNewCapacity(size_type currentCapacity)
    {
        return (currentCapacity > 8) ? (2 * currentCapacity) : (size_type)8;
    }

    char* erase(char* first, char* last);                       // 0x45f080
    void  reserve(unsigned int n);                              // 0x45f0e0
    void  reallocate(unsigned int n);                           // 0x45f140
    void  swap(StrBuf& o);                                      // 0x45f2a0
    StrBuf* assign(const char* first, const char* last);        // 0x45f390
    StrBuf& appendGrow(const char* first, const char* last);    // 0x45f430
    void  appendFill(unsigned int n, char c);                   // 0x45efa0
    void  resize(unsigned int n);                               // 0x45ebd0
    void  DeallocateSelf();                                     // 0x429300

    StrBuf& operator=(const StrBuf& o)
    {
        if (&o != this) {
            assign(o.begin, o.end);
        }
        return *this;
    }
};

template <typename T>
static inline void SwapRef(T& a, T& b)
{
    T tmp(a);
    a = b;
    b = tmp;
}

// eastl::max_alt
template <typename T>
static inline const T& MaxRef(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

// =====================================================================
// @ 0x45f080  erase [first,last) from the string buffer
// =====================================================================
char* StrBuf::erase(char* first, char* last)
{
    if (first != last) {
        memmove(first, last, (unsigned int)((end - last) + 1));
        char* newEnd = end - (last - first);
        end = newEnd;
    }
    return first;
}

// =====================================================================
// @ 0x45f0e0  make room for max(n, size)+1 bytes
// =====================================================================
void StrBuf::reserve(unsigned int n)
{
    unsigned int size = (unsigned int)(end - begin);
    unsigned int* chosen;
    if (n < size) {
        chosen = &size;
    } else {
        chosen = &n;
    }
    unsigned int want = *chosen + 1;
    if ((unsigned int)(cap - begin) < want) {
        reallocate(want);
    }
    return;
}

// =====================================================================
// @ 0x45f140  set the buffer capacity to n (shrink-to-fit / realloc)
// =====================================================================
void StrBuf::reallocate(unsigned int n)
{
    if (n == 0xffffffff || n <= (unsigned int)(end - begin)) {
        if (n < (unsigned int)(end - begin)) {
            resize(n);
        }
        StrBuf temp(*this);
        swap(temp);
    } else {
        char* pNewBegin = DoAllocate(n);
        char* pNewEnd = pNewBegin;
        pNewEnd = CharStringUninitializedCopy(begin, end, pNewBegin);
        *pNewEnd = 0;
        DeallocateSelf();
        begin = pNewBegin;
        end = pNewEnd;
        cap = pNewBegin + n;
    }
    return;
}

// =====================================================================
// @ 0x45f2a0  swap two string buffers
// =====================================================================
void StrBuf::swap(StrBuf& o)
{
    if (mAllocator == o.mAllocator) {
        // Same allocator object: swap the three pointers (eastl::swap).
        SwapRef(begin, o.begin);
        SwapRef(end, o.end);
        SwapRef(cap, o.cap);
    } else {
        // Different allocators: swap the contents.
        const StrBuf temp(*this);
        *this = o;
        o = temp;
    }
    return;
}

// =====================================================================
// @ 0x45f390  assign from a byte range
// =====================================================================
StrBuf* StrBuf::assign(const char* first, const char* last)
{
    unsigned int n = (unsigned int)(last - first);
    if ((unsigned int)(end - begin) < n) {
        memcpy(begin, first, (unsigned int)(end - begin));
        appendGrow((const char*)((end - begin) + first), last);
    } else {
        memcpy(begin, first, n);
        erase(begin + n, end);
    }
    return this;
}

// =====================================================================
// @ 0x45f430  append a range, growing if needed
// =====================================================================
StrBuf& StrBuf::appendGrow(const char* pBegin, const char* pEnd)
{
    if (pBegin != pEnd) {
        const size_type nOldSize = (size_type)(end - begin);
        const size_type n = (size_type)(pEnd - pBegin);
        const size_type nCapacity = (size_type)((cap - begin) - 1);
        if ((nOldSize + n) > nCapacity) {
            const size_type nLength = MaxRef(GetNewCapacity(nCapacity), (size_type)(nOldSize + n)) + 1;
            char* const pNewBegin = DoAllocate(nLength);
            char* pNewEnd = pNewBegin;
            pNewEnd = CharStringUninitializedCopy(begin, end, pNewBegin);
            pNewEnd = CharStringUninitializedCopy(pBegin, pEnd, pNewEnd);
            *pNewEnd = 0;
            DeallocateSelf();
            begin = pNewBegin;
            end = pNewEnd;
            cap = pNewBegin + nLength;
        } else {
            const char* pTemp = pBegin;
            ++pTemp;
            CharStringUninitializedCopy(pTemp, pEnd, end + 1);
            end[n] = 0;
            *end = *pBegin;
            end += n;
        }
    }
    return *this;
}

// =====================================================================
// @ 0x45efa0  append n copies of a byte
// =====================================================================
void StrBuf::appendFill(unsigned int n, char c)
{
    int used = (int)(end - begin);
    unsigned int room = (unsigned int)((cap - begin) - 1);
    if (room < (unsigned int)(used + n)) {
        unsigned int want = (unsigned int)(used + n);
        unsigned int newCap = room < 9 ? 8 : room * 2;
        if (newCap < want) {
            newCap = want;
        }
        reserve(newCap);
    }
    if (n != 0) {
        memset(end + 1, (unsigned char)c, n - 1);
        *end = c;
        end = end + n;
        *end = 0;
    }
    return;
}

// =====================================================================
// @ 0x45edf0  out = matrix * vector (4x4 * vec4)
// =====================================================================
void TransformVec4(float* out, const float* v, const float* m)
{
    float v0 = v[0];
    float v1 = v[1];
    float v2 = v[2];
    float v3 = v[3];
    out[0] = m[0] * v0 + m[4] * v1 + m[8] * v2 + m[12] * v3;
    out[1] = m[1] * v0 + m[5] * v1 + m[9] * v2 + m[13] * v3;
    out[2] = m[2] * v0 + m[6] * v1 + m[10] * v2 + m[14] * v3;
    out[3] = m[3] * v0 + m[7] * v1 + m[11] * v2 + m[15] * v3;

    // The retail image's only return-value trace is a dead `mov eax,[ebp+8]` (arg1 = out) placed
    // right before the epilogue; keep the destination in a local so the /Od codegen ends the same.
    float* const pOut = out;
    (void)pOut;
    return;
}
