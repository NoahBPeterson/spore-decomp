// Slice s00714f20: EASTL sort/heap/partition helpers, several eastl::vector
// instantiations, and the SP::cMeshBuilder constructor/destructor.
// Built optimized (/O2 /MD /Gy /EHsc /TP).  This region (SporeEP1_RL) is not in the
// 2008 dev PDB, so stub types are used; callees are masked relocations.
#include <stddef.h>

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// masked external callees
// ---------------------------------------------------------------------------
void* __cdecl ea_alloc(const char* tag, unsigned size, int a, int b, const char* file, int line);
void  __cdecl ea_free(void* p);
void* __cdecl move_ret(void* dst, const void* src, unsigned n);

// comparator functor (operator() out of line, masked).  Empty class passed by value.
struct Cmp4 { bool operator()(int a, int b) const; };

void __cdecl adjust_heap(int* first, int hole, int length, int top, int value, Cmp4 cmp);
int* __cdecl median3(int* a, int* b, int* c, Cmp4 cmp);

static inline void ea_del(void* p)
{
    if (p != 0 && ((int*)p)[-1] != 0)
        ea_free(p);
}
static inline void* ea_new(unsigned size)
{
    return ea_alloc("Graphics", size, 0, 0, "EASTL/allocator.h", 0xd1);
}

// ===========================================================================
// sort / heap helpers (4-byte elements)
// ===========================================================================

// @ 0x00714f20  destroy a range of 0x28-byte elements that own two eastl buffers
struct Elem40 { void* p0; void* pad0[4]; void* p14; void* pad1[4]; };
void __stdcall f714f20(Elem40* first, Elem40* last)
{
    for (Elem40* it = first; it < last; ++it) {
        void* a = it->p14;
        if (a != 0 && ((int*)a)[-1] != 0)
            ea_free(a);
        void* b = it->p0;
        if (b != 0 && ((int*)b)[-1] != 0)
            ea_free(b);
    }
}

// @ 0x00714fa0  eastl::get_partition(first, last, pivot, compare)
int* __cdecl f714fa0(int* first, int* last, int pivot, Cmp4 cmp)
{
    for (;; ++first) {
        int cur;
        while ((cur = *first), cmp(cur, pivot))
            ++first;
        --last;
        while (cmp(pivot, *last))
            --last;
        if (first >= last)
            return first;
        *first = *last;
        *last = cur;
    }
}

// @ 0x00715010  merge two index ranges into out (keys is a pointer-to-pointer)
int* __cdecl f715010(int* first0, int* last0, int* first1, int* last1, int* out, int** keys)
{
    while (first0 != last0 && first1 != last1) {
        if ((*keys)[*first1] < (*keys)[*first0]) {
            *out = *first1;
            ++first1;
        } else {
            *out = *first0;
            ++first0;
        }
        ++out;
    }
    out = (int*)((char*)move_ret(out, first0, (unsigned)((char*)last0 - (char*)first0)) + (last0 - first0) * 4);
    out = (int*)((char*)move_ret(out, first1, (unsigned)((char*)last1 - (char*)first1)) + (last1 - first1) * 4);
    return out;
}

// @ 0x00715090  eastl make_heap
void __cdecl f715090(int* first, int* last, Cmp4 cmp)
{
    int n = (int)(last - first);
    if (n < 2)
        return;
    for (int parent = (n - 2) / 2; parent >= 0; --parent) {
        int value = first[parent];
        adjust_heap(first, parent, n, parent, value, cmp);
    }
}

// @ 0x007150d0  eastl sort_heap
void __cdecl f7150d0(int* first, int* last, Cmp4 cmp)
{
    if (last - first <= 1)
        return;
    for (int* it = last - 1; it > first; --it) {
        int value = *it;
        *it = *first;
        adjust_heap(first, 0, (int)(it - first), 0, value, cmp);
    }
}

// @ 0x00715900  eastl partial_sort(first, middle, last, compare)
void __cdecl f715900(int* first, int* middle, int* last, Cmp4 cmp)
{
    f715090(first, middle, cmp);
    for (int* i = middle; i < last; ++i) {
        if (cmp(*i, *first)) {
            int temp = *i;
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp, cmp);
        }
    }
    f7150d0(first, middle, cmp);
}

// @ 0x00716080  eastl::Internal::quick_sort_impl
void __cdecl f716080(int* first, int* last, int depth, Cmp4 cmp)
{
    while (((char*)last - (char*)first) > 0x70 && depth > 0) {
        int* mid = first + ((last - first) / 2);
        int pivot = *median3(first, mid, last - 1, cmp);
        int* p = f714fa0(first, last, pivot, cmp);
        --depth;
        f716080(p, last, depth, cmp);
        last = p;
    }
    if (depth == 0)
        f715900(first, last, last, cmp);
}

// ===========================================================================
// vector instantiations
// ===========================================================================

// ---- vector<20-byte> ----
void* __cdecl alloc20(int count, const void* first, const void* last);
void* __cdecl copy20(const void* first, const void* last, void* dst);
void  __cdecl uninit20(void* out, const void* first, const void* last, void* end, void* tmp);

struct Vec20 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    Vec20& operator=(const Vec20& x);
};

// @ 0x00715120
Vec20& Vec20::operator=(const Vec20& x)
{
    if (&x != this) {
        char* srcBegin = x.mpBegin;
        int count = (int)(x.mpEnd - x.mpBegin) / 0x14;
        if ((int)(mpCapacity - mpBegin) / 0x14 < count) {
            char* buf = (char*)alloc20(count, x.mpBegin, x.mpEnd);
            ea_del(mpBegin);
            mpCapacity = buf + count * 0x14;
            mpBegin = buf;
            mpEnd = buf + count * 0x14;
            return *this;
        }
        int cur = (int)(mpEnd - mpBegin) / 0x14;
        if (cur < count) {
            copy20(x.mpBegin, x.mpBegin + cur * 0x14, mpBegin);
            uninit20(mpEnd, mpBegin + cur * 0x14, (char*)x.mpBegin + cur * 0x14, x.mpEnd, 0);
            mpEnd = mpBegin + count * 0x14;
            return *this;
        }
        copy20(x.mpBegin, x.mpEnd, mpBegin);
        mpEnd = mpBegin + count * 0x14;
    }
    return *this;
}

// ---- vector<4-byte> ----
void* __cdecl alloc4(int count, const void* first, const void* last);
void* __cdecl copy4(const void* first, const void* last, void* dst);
void* __cdecl uninit4(void* dst, const void* first, const void* last);

struct Vec4 {
    int* mpBegin; int* mpEnd; int* mpCapacity;
    Vec4& operator=(const Vec4& x);
    void  insert(int* position, const int* value);
    void  insert_range(int* position, const int* first, const int* last, int unused);
};

// @ 0x00715250
Vec4& Vec4::operator=(const Vec4& x)
{
    if (&x != this) {
        int* src = x.mpBegin;
        int count = (int)(x.mpEnd - x.mpBegin);
        if ((mpCapacity - mpBegin) < count) {
            int* buf = (int*)alloc4(count, x.mpBegin, x.mpEnd);
            ea_del(mpBegin);
            mpBegin = buf;
            mpCapacity = buf + count;
            mpEnd = buf + count;
            return *this;
        }
        int cur = (int)(mpEnd - mpBegin);
        if (cur < count) {
            copy4(x.mpBegin, x.mpBegin + cur, mpBegin);
            uninit4(mpEnd, x.mpBegin + cur, x.mpEnd);
            mpEnd = mpBegin + count;
            return *this;
        }
        copy4(src, x.mpEnd, mpBegin);
        mpEnd = mpBegin + count;
    }
    return *this;
}

// @ 0x00715350  insert one element
void Vec4::insert(int* position, const int* value)
{
    if (mpEnd == mpCapacity) {
        int n = (int)(mpEnd - mpBegin);
        int need = n ? n * 2 : 1;
        int* buf = need ? (int*)ea_new(need * 4) : 0;
        int* w = buf;
        for (int* p = mpBegin; p != position; ++p)
            *w++ = *p;
        *w++ = *value;
        for (int* p = position; p != mpEnd; ++p)
            *w++ = *p;
        ea_del(mpBegin);
        mpBegin = buf;
        mpEnd = w;
        mpCapacity = buf + need;
        return;
    }
    int* e = mpEnd;
    const int* v = value;
    if (value >= position && value < e)
        v = value + 1;
    *e = e[-1];
    int* p = e - 1;
    while (p != position) {
        *p = p[-1];
        --p;
    }
    *position = *v;
    ++mpEnd;
}

// @ 0x00715ec0  insert range [first,last)
void Vec4::insert_range(int* position, const int* first, const int* last, int)
{
    if (first == last)
        return;
    int count = (int)(last - first);
    if (count > (mpCapacity - mpEnd)) {
        int old = (int)(mpEnd - mpBegin);
        int cap = old ? old * 2 : 1;
        int need = old + count;
        if (need < cap)
            need = cap;
        int* buf = need ? (int*)ea_new(need * 4) : 0;
        int* p = (int*)move_ret(buf, mpBegin, (unsigned)((char*)position - (char*)mpBegin));
        int* q = (int*)move_ret(p, first, (unsigned)((char*)last - (char*)first));
        q = (int*)move_ret(q, position, (unsigned)((char*)mpEnd - (char*)position));
        ea_del(mpBegin);
        mpEnd = q;
        mpBegin = buf;
        mpCapacity = buf + need;
        return;
    }
    int spare = (int)(mpEnd - position);
    if (count > spare) {
        move_ret(mpEnd, position, (unsigned)((char*)mpEnd - (char*)position));
        mpEnd += count - spare;
        move_ret(mpEnd - (count - spare), position, (unsigned)((char*)position + (spare)*4 - (char*)position));
        return;
    }
    int tail = (int)(mpEnd - position);
    move_ret(mpEnd, position, (unsigned)((char*)mpEnd - (char*)position));
    mpEnd += count;
    move_ret(position + count, position, (unsigned)(tail * 4));
    move_ret(position, first, (unsigned)((char*)last - (char*)first));
}

// ---- vector<48-byte> (Matrix34) ----
void* __cdecl uninit_copy48(const void* first, const void* last, void* dst);
void  __cdecl fill48(void* dst, unsigned n, const void* value, void* arg);
void  __cdecl move48(const void* first, const void* last, void* dst);

struct Vec48 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void insert(char* position, unsigned n, const void* value);
};

// @ 0x00715470  insert n copies of value
void Vec48::insert(char* position, unsigned n, const void* value)
{
    if ((unsigned)((mpCapacity - mpEnd) / 0x30) < n) {
        int old = (int)(mpEnd - mpBegin) / 0x30;
        unsigned cap = old ? old * 2 : 1;
        unsigned need = old + n;
        if (need < cap)
            need = cap;
        char* buf = need ? (char*)ea_new(need * 0x30) : 0;
        char* p = (char*)uninit_copy48(mpBegin, position, buf);
        fill48(p, n, value, position);
        char* q = (char*)uninit_copy48(position, mpEnd, p + n * 0x30);
        ea_del(mpBegin);
        mpBegin = buf;
        mpEnd = q;
        mpCapacity = buf + need * 0x30;
        return;
    }
    if (n == 0)
        return;
    int tailCount = (int)(mpEnd - position) / 0x30;
    if (tailCount < (int)n) {
        unsigned grow = n - tailCount;
        fill48(mpEnd, grow, value, position);
        mpEnd += grow * 0x30;
        move48(position, mpEnd - grow * 0x30, position);
        mpEnd += tailCount * 0x30;
        return;
    }
    char* p = mpEnd - n * 0x30;
    move48(p, mpEnd, mpEnd);
    mpEnd += n * 0x30;
    move48(position, p, position + n * 0x30);
}

// ---- vector<8-byte> ----
void* __cdecl helper479c00(void* a, const void* b, const void* c, const void* d, const void* e);
void  __cdecl helper73fe50(void* a, void* b, void* c);
void  __cdecl helperac4440(void* a, void* b, void* c);
void  __cdecl helper714bc0(void* a, const void* b, const void* c, void* d, const void* e);
void* __cdecl helper4763a0(void* a, const void* b, void* c);

struct Vec8 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void insert_range(char* position, char* first, char* last, int unused);
};

// @ 0x00715630  insert range [first,last)
void Vec8::insert_range(char* position, char* first, char* last, int)
{
    if (first == last)
        return;
    if ((unsigned)((last - first) / 8) <= (unsigned)((mpCapacity - mpEnd) / 8)) {
        if ((unsigned)((last - first) / 8) < (unsigned)((mpEnd - position) / 8)) {
            char* p = mpEnd - (last - first);
            helper479c00(mpEnd - 8, p, mpEnd, mpEnd, first);
            mpEnd += (last - first);
            helper73fe50(position, p, mpEnd - (last - first));
            helperac4440(first, last, position);
            return;
        }
        char* p = position + (last - first);
        helper714bc0(p, p, mpEnd, mpEnd, first);
        mpEnd += (mpEnd - p);
        helper479c00(position, p, mpEnd - (mpEnd - p), mpEnd, first);
        mpEnd += (last - first);
        helper73fe50(first, p, position + (last - first));
        return;
    }
    int old = (int)(mpEnd - mpBegin) / 8;
    unsigned cap = old ? (unsigned)old * 2 : 1;
    unsigned need = (unsigned)old + (unsigned)((last - first) / 8);
    if (need < cap)
        need = cap;
    char* buf = need ? (char*)ea_new(need * 8) : 0;
    helper4763a0(mpBegin, position, buf);
    helper714bc0(position, first, last, buf + (position - mpBegin), first);
    helper4763a0(position, mpEnd, buf + (position - mpBegin) + (last - first));
    ea_del(mpBegin);
    mpBegin = buf;
    mpEnd = buf + need * 8;
    mpCapacity = buf + need * 8;
}

// ===========================================================================
// SP::cMeshBuilder ctor/dtor (large EH functions; approximate reconstruction)
// ===========================================================================
struct cMeshBuilderStub {
    char pad[0]; // members unknown; see disassembly stores
    void ctor();
    void dtor();
};

// @ 0x00715980  cMeshBuilder::cMeshBuilder
void cMeshBuilderStub::ctor()
{
    // Full member-by-member initialization lives in the original; reconstructed here
    // only far enough to be a faithful outline (the exact EH vector-ctor calls are
    // compiler-generated).  Marked partial in partial.txt.
    char* self = (char*)this;
    *(void**)self = 0;
    *(void**)(self + 4) = 0;
    *(void**)(self + 8) = 0;
    *(void**)(self + 0xc) = 0;
}

// @ 0x00715bb0  cMeshBuilder::~cMeshBuilder
void cMeshBuilderStub::dtor()
{
    // See partial.txt: the original is dominated by EH destructor-iterator calls.
    char* self = (char*)this;
    *(void**)self = 0;
}
