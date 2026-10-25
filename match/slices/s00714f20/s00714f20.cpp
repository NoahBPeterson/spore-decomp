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

// raw byte-move primitives masked to the runtime memcpy (0x11e0744) and the
// memmove IAT slot (0x13cc480).  Both return the destination.
void* __cdecl mem_copy(void* dst, const void* src, unsigned n);
void* __cdecl mem_move(void* dst, const void* src, unsigned n);

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
    Vec20& assign(const Vec20& x);
};

// @ 0x00715120
Vec20& Vec20::assign(const Vec20& x)
{
    if (&x == this)
        return *this;

    char* srcBegin = x.mpBegin;
    int count = (int)(x.mpEnd - x.mpBegin) / 0x14;
    int have = (int)(mpCapacity - mpBegin) / 0x14;
    if (have < count) {
        // Not enough room: allocate a fresh block and re-seat all three pointers.
        char* buf = (char*)alloc20(count, x.mpBegin, x.mpEnd);
        ea_del(mpBegin);
        mpCapacity = buf + count * 0x14;
        mpBegin = buf;
        mpEnd = buf + count * 0x14;
        return *this;
    }

    int cur = (int)(mpEnd - mpBegin) / 0x14;
    if (cur < count) {
        // Copy the overlap, then fill the new tail with copies of the source elements.
        copy20(x.mpBegin, x.mpBegin + cur * 0x14, mpBegin);
        uninit20(mpEnd, x.mpBegin + cur * 0x14, x.mpEnd, mpEnd, 0);
        mpEnd = mpBegin + count * 0x14;
        return *this;
    }

    copy20(x.mpBegin, x.mpEnd, mpBegin);
    mpEnd = mpBegin + count * 0x14;
    return *this;
}

// ---- vector<4-byte> ----
void* __cdecl alloc4(int count, const void* first, const void* last);
void* __cdecl copy4(const void* first, const void* last, void* dst);
void* __cdecl uninit4(void* dst, const void* first, const void* last);

struct Vec4 {
    int* mpBegin; int* mpEnd; int* mpCapacity;
    Vec4& assign(const Vec4& x);
    void  insert(int* position, const int* value);
    void  insert_range(int* position, const int* first, const int* last, int unused);
};
// @ 0x00715250
Vec4& Vec4::assign(const Vec4& x)
{
    if (&x == this)
        return *this;

    int* src = x.mpBegin;
    int count = (int)(x.mpEnd - x.mpBegin) / 4;
    int have = (int)(mpCapacity - mpBegin) / 4;
    if (have < count) {
        int* buf = (int*)alloc4(count, x.mpBegin, x.mpEnd);
        ea_del(mpBegin);
        mpBegin = buf;
        mpCapacity = buf + count;
        mpEnd = buf + count;
        return *this;
    }

    int cur = (int)(mpEnd - mpBegin) / 4;
    if (cur < count) {
        copy4(x.mpBegin, x.mpBegin + cur, mpBegin);
        uninit4(mpEnd, x.mpBegin + cur, x.mpEnd);
        mpEnd = mpBegin + count;
        return *this;
    }

    copy4(src, x.mpEnd, mpBegin);
    mpEnd = mpBegin + count;
    return *this;
}

// @ 0x00715350  insert one element
void Vec4::insert(int* position, const int* value)
{
    if (mpEnd != mpCapacity) {
        // Room available: shift [position, mpEnd) right by one slot in place.
        int* v = (int*)value;
        if (v >= position && v < mpEnd)
            v = v + 1;
        if (mpEnd)
            *mpEnd = mpEnd[-1];
        int* w = mpEnd;
        while (w - 1 != position) {
            --w;
            *w = w[-1];
        }
        *position = *v;
        ++mpEnd;
        return;
    }

    // Full: allocate a buffer of twice the element count (or 1) and rebuild.
    int n = (int)(mpEnd - mpBegin);
    int need = n ? n * 2 : 1;
    int* buf = need ? (int*)ea_new(need * 4) : 0;
    int* w = buf;
    for (int* p = mpBegin; p != position; ++p) {
        if (w)
            *w = *p;
        ++w;
    }
    if (w)
        *w = *value;
    ++w;
    for (int* p = position; p != mpEnd; ++p) {
        if (w)
            *w = *p;
        ++w;
    }
    ea_del(mpBegin);
    mpBegin = buf;
    mpEnd = w;
    mpCapacity = buf + need;
}

// @ 0x00715ec0  insert range [first,last)
void Vec4::insert_range(int* position, const int* first, const int* last, int)
{
    if (first == last)
        return;

    int count = (int)(last - first);
    int spare = (int)(mpCapacity - mpEnd);
    if (count <= spare) {
        int tail = (int)(mpEnd - position);
        if (count < tail) {
            // Move the last `count` elements to the very end, then slide the
            // remaining tail right and drop [first,last) into the hole.
            int* moved = mpEnd - count;
            mem_copy(mpEnd, moved, (unsigned)(count * 4));
            mpEnd += count;
            int* dst = mpEnd - count - (int)((char*)moved - (char*)position);
            mem_move(dst, position, (unsigned)((char*)moved - (char*)position));
            mem_copy(position, first, (unsigned)((char*)last - (char*)first));
            return;
        }
        // Tail is shorter than the inserted range: duplicate the tail, copy the
        // new elements in, then memmove the original tail into place.
        int* out = mpEnd + count;
        int* dst = out - count;
        mem_copy(dst, position, (unsigned)((char*)mpEnd - (char*)position));
        mpEnd += count;
        mem_copy(dst + count, first, (unsigned)((char*)last - (char*)first));
        mem_move(mpEnd - count - count, first + count, (unsigned)(count * 4));
        return;
    }

    // Grow: allocate a buffer large enough and copy the three segments.
    int old = (int)(mpEnd - mpBegin);
    unsigned cap = old ? (unsigned)old * 2 : 1;
    unsigned need = (unsigned)old + (unsigned)count;
    if (need < cap)
        need = cap;
    int* buf = need ? (int*)ea_new(need * 4) : 0;
    int* p = (int*)mem_copy(buf, mpBegin, (unsigned)((char*)position - (char*)mpBegin));
    int* q = (int*)mem_copy(p, first, (unsigned)((char*)last - (char*)first));
    q = (int*)mem_copy(q, position, (unsigned)((char*)mpEnd - (char*)position));
    ea_del(mpBegin);
    mpEnd = q;
    mpBegin = buf;
    mpCapacity = buf + need;
}

// ---- vector<48-byte> (Matrix34) ----
void* __cdecl uninit_copy48(const void* first, const void* last, void* dst);
void  __cdecl fill48(void* dst, unsigned n, const void* value, void* arg);
void  __cdecl move48(const void* first, const void* last, void* dst);
void  __cdecl copy48_assign(void* dst, const void* value);   // Matrix34::operator=
void  __cdecl fill48b(void* dst, unsigned n, const void* value, void* arg);
void  __cdecl shift48(void* dst, const void* first, const void* last, void* arg);
void  __cdecl copy48_range(const void* first, const void* last, void* dst);

struct Vec48 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void insert(char* position, unsigned n, const void* value);
};

// @ 0x00715470  insert n copies of value
void Vec48::insert(char* position, unsigned n, const void* value)
{
    if ((unsigned)((mpCapacity - mpEnd) / 0x30) < n) {
        // Grow to max(2 * count, count + n) elements and rebuild the array.
        int old = (int)(mpEnd - mpBegin) / 0x30;
        unsigned cap = old ? (unsigned)old * 2 : 1;
        unsigned need = (unsigned)old + n;
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

    // Materialise `value` into a local Matrix34 first (retail copies it up front).
    char local[0x30];
    copy48_assign(local, value);

    int tail = (int)(mpEnd - position) / 0x30;
    if ((int)n < tail) {
        // Shift the last n elements out of the way, rotate, then stamp value in.
        char* moved = mpEnd - n * 0x30;
        shift48(moved, mpEnd, mpEnd, position);
        mpEnd += n * 0x30;
        move48(position, moved, mpEnd - n * 0x30);
        copy48_range(position, position + n * 0x30, local);
        return;
    }

    // Tail shorter than n: fill the new slots beyond mpEnd, then fill the rest.
    unsigned grow = n - (unsigned)tail;
    fill48b(mpEnd, grow, local, position);
    mpEnd += grow * 0x30;
    shift48(position, mpEnd, mpEnd, position);
    mpEnd += (unsigned)tail * 0x30;
    copy48_range(position, position + (unsigned)tail * 0x30, local);
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

    unsigned count = (unsigned)(last - first) / 8;
    unsigned spare = (unsigned)(mpCapacity - mpEnd) / 8;
    if (count <= spare) {
        unsigned tail = (unsigned)(mpEnd - position) / 8;
        if (count < tail) {
            // Room in the tail: relocate the last `count` elements to the very
            // end, slide the remaining tail right, then drop the range in.
            char* moved = mpEnd - count * 8;
            helper73fe50(mpEnd, moved, (void*)(count * 8));
            mpEnd += count * 8;
            helper73fe50(moved, position, (void*)(moved - position));
            helperac4440(first, last, position);
            return;
        }
        // Tail shorter than the range: copy the tail beyond mpEnd, copy the new
        // elements in, then shift the original tail into place.
        char* dst = position + count * 8;
        helper73fe50(mpEnd, position, (void*)(mpEnd - position));
        mpEnd += count * 8;
        helper73fe50(dst, first, (void*)(tail * 8));
        helperac4440(first, last, dst);
        return;
    }

    // Grow: allocate a new buffer and copy the three segments across.
    int old = (int)(mpEnd - mpBegin) / 8;
    unsigned cap = old ? (unsigned)old * 2 : 1;
    unsigned need = (unsigned)old + count;
    if (need < cap)
        need = cap;
    char* buf = need ? (char*)ea_new(need * 8) : 0;
    char* mid = (char*)helper4763a0(buf, mpBegin, position);
    helper714bc0(mid, first, last, mid, first);
    char* tailEnd = (char*)helper4763a0(mid + count * 8, position, mpEnd);
    ea_del(mpBegin);
    mpBegin = buf;
    mpEnd = tailEnd;
    mpCapacity = buf + need * 8;
}

// ===========================================================================
// SP::cMeshBuilder ctor/dtor (large EH functions)
// ===========================================================================
// Layout recovered from the stores in the constructor/destructor: a vptr at
// +0x00, two sets of five EH-initialised 0x14-byte element arrays at +0x30 and
// +0x80, a set of owned pointers, and a second pair of arrays at +0x1b0 / +0x200.
struct cMeshBuilder {
    void*    mVtbl;        // +0x000
    void*    mp04;         // +0x004
    void*    mp08;         // +0x008
    void*    mp0c;         // +0x00c
    void*    mp10;         // +0x010
    void*    mp14;         // +0x014
    void*    mp18;         // +0x018
    void*    mp1c;         // +0x01c
    void*    mp20;         // +0x020
    void*    mp24;         // +0x024
    u8       pad28[0x08];  // +0x028
    u8       arr30[0x14 * 4];  // +0x030  five-array? (4 elements, 0x14 each)
    u8       arr80[0x14 * 2];  // +0x080  (2 elements, 0x14 each)
    void*    mpa8;         // +0x0a8
    void*    mpac;         // +0x0ac
    void*    mpb0;         // +0x0b0
    void*    mpbc;         // +0x0bc
    void*    mpc0;         // +0x0c0
    void*    mpc4;         // +0x0c4
    void*    mpd0;         // +0x0d0
    void*    mpd4;         // +0x0d4
    void*    mpd8;         // +0x0d8
    void*    mpe4;         // +0x0e4
    void*    mpe8;         // +0x0e8
    void*    mpec;         // +0x0ec
    void*    mpf8;         // +0x0f8
    void*    mpfc;         // +0x0fc
    void*    mp100;        // +0x100
    void*    mp10c;        // +0x10c
    void*    mp110;        // +0x110
    void*    mp114;        // +0x114
    void*    mp120;        // +0x120
    void*    mp124;        // +0x124
    void*    mp128;        // +0x128
    void*    mp134;        // +0x134
    void*    mp138;        // +0x138
    void*    mp13c;        // +0x13c
    void*    mp148;        // +0x148  refcounted object pointer
    u32      m14c;         // +0x14c  magic 0x9f84a565
    u8       m150;         // +0x150
    u8       pad151[3];    // +0x151
    void*    mp154;        // +0x154
    int      m158;         // +0x158  -1
    void*    mp15c;        // +0x15c
    int      m160;         // +0x160  -1
    void*    mp164;        // +0x164
    void*    mp168;        // +0x168
    void*    mp16c;        // +0x16c
    void*    mp170[0x18 / 4]; // +0x170  (through +0x187)
    void*    mp188[0x10 / 4]; // +0x188  (through +0x197)
    void*    mp19c;        // +0x19c
    void*    mp1a0;        // +0x1a0
    void*    mp1a4;        // +0x1a4
    void*    mp1a8;        // +0x1a8
    u8       arr1b0[0x14 * 4]; // +0x1b0
    u8       arr200[0x2 * 0x14]; // +0x200

    cMeshBuilder();
    ~cMeshBuilder();
};

// EH helpers emitted by the compiler for array-of-object construction/destruction.
void __stdcall eh_vector_ctor(void* base, unsigned elemSize, unsigned count,
                              void* ctor, void* dtor);
void __stdcall eh_vector_dtor(void* base, unsigned elemSize, unsigned count, void* dtor);

// out-of-line element ctors/dtors (masked).
void __cdecl elem_ctor_6e5790(void* self);   // shared element constructor
void __cdecl elem_dtor_4cddd0(void* self);
void __cdecl elem_dtor_7a41a0(void* self);
void __cdecl elem_dtor_4e1bf0(void* self);

// helpers used by the destructor for owned nested vectors / refcounted objects.
void __cdecl release_range_714b40(void* first, void* last);
void __cdecl clear_range_714f20(void* first, void* last);
void __cdecl release_vec_714d70(void* self);
void __cdecl clear_vec_714b40(void* self);

// Reference-counted object: [0] = vtable, [1] = refcount.
struct RefObj { void** vtbl; int* refcount; };

// @ 0x00715980  cMeshBuilder::cMeshBuilder
cMeshBuilder::cMeshBuilder()
{
    mVtbl = (void*)0x140cd40;
    mp04 = 0; mp08 = 0; mp0c = 0; mp10 = 0;
    mp1c = 0; mp20 = 0; mp24 = 0;

    // Two EH-constructed arrays of 0x14-byte elements.
    eh_vector_ctor(arr30, 0x14, 4, (void*)elem_ctor_6e5790, (void*)elem_dtor_4cddd0);
    eh_vector_ctor(arr80, 0x14, 2, (void*)elem_ctor_6e5790, (void*)elem_dtor_7a41a0);

    mpa8 = 0; mpac = 0; mpb0 = 0;
    mpbc = 0; mpc0 = 0; mpc4 = 0;
    mpd0 = 0; mpd4 = 0; mpd8 = 0;
    mpe4 = 0; mpe8 = 0; mpec = 0;
    mpf8 = 0; mpfc = 0; mp100 = 0;
    mp10c = 0; mp110 = 0; mp114 = 0;
    mp120 = 0; mp124 = 0; mp128 = 0;
    mp134 = 0; mp138 = 0; mp13c = 0;
    mp148 = 0;

    m14c = 0x9f84a565u;
    m150 = 0;
    mp154 = 0;
    m158 = -1;
    mp15c = 0;
    m160 = -1;
    mp164 = 0; mp168 = 0; mp16c = 0;

    for (int i = 0; i < 0x18 / 4; ++i)
        mp170[i] = 0;
    mp188[0] = 0; mp188[1] = 0; mp188[2] = 0; mp188[3] = 0;
    mp19c = 0; mp1a0 = 0; mp1a4 = 0;

    // Second pair of EH-constructed arrays.
    eh_vector_ctor(arr1b0, 0x14, 4, (void*)elem_ctor_6e5790, (void*)elem_dtor_4e1bf0);
    eh_vector_ctor(arr200, 0x14, 2, (void*)elem_ctor_6e5790, (void*)elem_dtor_4e1bf0);

    // Zero the two trailing run arrays at +0x170..+0x180 and +0x180..+0x188.
    for (void** p = mp170; p != (void**)((char*)this + 0x180); ++p)
        *p = 0;
    for (void** p = (void**)((char*)this + 0x180); p != (void**)((char*)this + 0x188); ++p)
        *p = 0;
}

// @ 0x00715bb0  cMeshBuilder::~cMeshBuilder
cMeshBuilder::~cMeshBuilder()
{
    mVtbl = (void*)0x140cd40;

    // Tear down the trailing EH arrays (in reverse declaration order).
    eh_vector_dtor(arr200, 0x14, 2, (void*)elem_dtor_4e1bf0);
    eh_vector_dtor(arr1b0, 0x14, 4, (void*)elem_dtor_4e1bf0);

    ea_del(mp19c);
    ea_del(mp188[0]);

    // Release the refcounted object at +0x148.
    if (mp148 != 0) {
        RefObj* obj = (RefObj*)mp148;
        int* rc = obj->refcount;
        if (--*rc == 0) {
            *rc = 1;
            ((void (__thiscall*)(RefObj*, int))obj->vtbl[0])(obj, 1);
        }
    }

    release_range_714b40(mp134, mp138);
    ea_del(mp134);

    clear_range_714f20(mp120, mp124);
    ea_del(mp120);

    ea_del(mp10c);
    ea_del(mpf8);
    ea_del(mpe4);

    release_vec_714d70((char*)this + 0xd0);
    ea_del(mpbc);
    ea_del(mpa8);

    eh_vector_dtor(arr80, 0x14, 2, (void*)elem_dtor_7a41a0);
    eh_vector_dtor(arr30, 0x14, 4, (void*)elem_dtor_4cddd0);

    ea_del(mp1c);
    ea_del(mp08);

    mVtbl = (void*)0x13eb938;   // EA::Trace::ITracerBase vtable
}

// ---------------------------------------------------------------------------
// Force emission of the reconstructed out-of-line members so each one keeps a
// distinct body (mirrors the retail symbol layout); nothing calls them.
// ---------------------------------------------------------------------------
void __cdecl force_emit_s00714f20(Vec20* a, Vec20* b, Vec4* c, Vec4* d, Vec8* e, Vec48* f)
{
    a->assign(*b);
    c->assign(*d);
    (void)e; (void)f;
}
