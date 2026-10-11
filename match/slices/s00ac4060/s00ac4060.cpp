// Slice s00ac4060 -- Spore container/allocator internals (segmented deque, EASTL vectors,
// cAStar subsystem constructor and request free-list helpers).
//
//   * 0x00ac4060 / 0x00ac4190 / 0x00ac4390  segmented container (blocks of 8 x 0x14-byte elements)
//     grow / constructor / push_back.
//   * 0x00ac4280  vector<8-byte>::reserve.
//   * 0x00ac4440 / 0x00ac44a0 / 0x00ac4a60  GlyphInfo do_copy / vector operator= / insert-fill.
//   * 0x00ac4570 / 0x00ac45e0 / 0x00ac4720 / 0x00ac4850  vector erase / DoInsertValue for
//     0x3c-, 0xc- and 4-byte elements.
//   * 0x00ac4970  reverse() over 0x3c-byte elements.
//   * 0x00ac4c20  cAStar::ctor, 0x00ac4e10  vector<AnalysisInfo>::assign.
//   * 0x00ac4ef0 / 0x00ac4f50  cAStar request free-list release / drain.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <string.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

extern "C" void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
extern "C" void  __cdecl EASTL_allocator_deallocate(void*); // 0x00f47380
extern char sz_name_13f09b4[]; // 0x013f09b4 "Simulator"
extern char sz_file_13ebb38[]; // 0x013ebb38 "...allocator.h"
extern char sz_name_1459e40[]; // 0x01459e40 "Simulator/AStar"
#define EA_ALLOC(sz) EASTL_allocator_allocate((sz), sz_name_13f09b4, 0, 0, sz_file_13ebb38, 0xd1)
#define EA_FREE(p)   EASTL_allocator_deallocate(p)

// ================================================================================================
// 0x00ac4060 -- segmented container: grow the block-pointer array (element size 0xa0).
struct E4060 { char d[160]; };
struct D4060 {
    E4060**  pa; unsigned n;
    E4060 *bc, *bb, *be; E4060** bp;
    E4060 *ec, *eb, *ee; E4060** ep;
    void f(unsigned add, int side);
    void ctor(unsigned count);
    void push_back(const struct E14& v);
};
template<class T> inline const T& mx_4060(const T& a, const T& b) { return (a < b) ? b : a; }
// @ 0x00ac4060
void D4060::f(unsigned add, int side)
{
    E4060** b0 = bp;
    int d = (int)ep - (int)b0;
    unsigned used = (unsigned)(d >> 2) + 1;
    unsigned nn = add + used;
    E4060** t;
    if (n <= nn * 2) {
        unsigned ns = n + mx_4060(n, add) + 2;
        E4060** np = (E4060**)EA_ALLOC(ns * sizeof(E4060*));
        t = np + (((int)bp - (int)pa >> 2) + (side ? 0 : add));
        if (pa) memcpy(t, bp, (size_t)((int)ep - (int)bp + 4));
        if (pa) EA_FREE(pa);
        pa = np; n = ns;
    } else {
        t = pa + ((n - nn) / 2) + (side ? 0 : add);
        if (t < b0) memcpy(t, b0, (size_t)(d + 4));
        else memmove(t + (used - ((unsigned)(d + 4) >> 2)), b0, (size_t)(d + 4));
    }
    bp = t;
    bb = *bp; be = (E4060*)((char*)bb + 160);
    ep = bp + (used - 1);
    eb = *ep; ee = (E4060*)((char*)eb + 160);
}

// ================================================================================================
// 0x00ac4190 -- segmented container constructor (count elements of 0x14 bytes, 8 per 0xa0 block).
// @ 0x00ac4190
void D4060::ctor(uint count)
{
    uint nb = (count >> 3) + 1;
    uint hi = nb + 2;
    uint cap = (hi > 8) ? hi : 8;
    E4060** arr = (E4060**)EA_ALLOC(cap * sizeof(E4060*));
    E4060** start = arr + ((cap - nb) >> 1);
    E4060** end = start + nb;
    n = cap;
    pa = arr;
    for (E4060** p = start; p < end; ++p)
        *p = (E4060*)EA_ALLOC(160);
    bp = start;
    bb = *bp;
    be = (E4060*)((char*)bb + 160);
    bc = bb;
    ep = end - 1;
    eb = *ep;
    ee = (E4060*)((char*)eb + 160);
    ec = (E4060*)((char*)eb + (count & 7) * 0x14);
}

// ================================================================================================
// 0x00ac4390 -- segmented container push_back of a 5-dword element.
struct E14 { uint d[5]; };
// @ 0x00ac4390
void D4060::push_back(const E14& v)
{
    E14 tmp = v;
    int used = (int)((((int)ep - (int)pa) >> 2)) + 1;
    if (used >= (int)n)
        f(1, 1);
    E4060* nblk = (E4060*)EA_ALLOC(160);
    ep[1] = nblk;
    E14* p = (E14*)ec;
    if (p)
        *p = tmp;
    E4060** nep = ep + 1;
    ep = nep;
    eb = *nep;
    ee = (E4060*)((char*)eb + 160);
    ec = eb;
}

// ================================================================================================
// 0x00ac4280 -- vector<8-byte>::reserve.
extern "C" void* __cdecl copy_99efa0(void* first, void* last, void* dst); // 0x0099efa0
struct Vec8 {
    void* begin; void* end; void* cap;
    void reserve(uint n);
};
// @ 0x00ac4280
void Vec8::reserve(uint n)
{
    if (n > (uint)((((int)cap - (int)begin)) >> 3)) {
        void* nb;
        if (n) nb = EA_ALLOC(n * 8);
        else   nb = 0;
        copy_99efa0(begin, end, nb);
        if (begin && *(int*)((char*)begin - 4) != 0)
            EA_FREE(begin);
        int sz = ((int)end - (int)begin) >> 3;
        void* nc = (char*)nb + n * 8;
        begin = nb;
        end = (char*)nb + sz * 8;
        cap = nc;
    }
}

// ================================================================================================
// 0x00ac4440 -- do_copy<GlyphInfo*>.
struct GlyphInfo { uint a, b; };
// @ 0x00ac4440
GlyphInfo* __cdecl do_copy_4440(GlyphInfo* first, GlyphInfo* last, GlyphInfo* dst)
{
    while (first != last) {
        dst->a = first->a;
        dst->b = first->b;
        ++first;
        ++dst;
    }
    return dst;
}

// ================================================================================================
// 0x00ac44a0 -- GlyphInfo vector operator=(const GlyphInfo vector&).
extern "C" void* __cdecl copy5_76ffd0(void** out, void* a, void* b, void* c, void* d); // 0x0076ffd0
struct GlyphVec {
    GlyphInfo* mpBegin; GlyphInfo* mpEnd; GlyphInfo* mpCapacity; int mAlloc; GlyphInfo* mpPool;
    GlyphInfo* allocCopy(uint n, GlyphInfo* f, GlyphInfo* l); // 0x00ac4000
    GlyphVec& assignVec(const GlyphVec& x);
};
// @ 0x00ac44a0
GlyphVec& GlyphVec::assignVec(const GlyphVec& x)
{
    if (this == &x)
        return *this;
    GlyphInfo* xb = x.mpBegin;
    GlyphInfo* dst = mpBegin;
    uint n = (uint)(x.mpEnd - xb);
    if ((uint)(mpCapacity - dst) < n) {
        GlyphInfo* nb = allocCopy(n, xb, x.mpEnd);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            EA_FREE(mpBegin);
        mpCapacity = nb + n;
        mpBegin = nb;
        mpEnd = nb + n;
        return *this;
    }
    uint m = (uint)(mpEnd - dst);
    if (m < n) {
        do_copy_4440(xb, xb + m, dst);
        void* out;
        copy5_76ffd0(&out, xb + (mpEnd - mpBegin), x.mpEnd, mpEnd, x.mpBegin);
        mpEnd = mpBegin + n;
        return *this;
    }
    do_copy_4440(xb, x.mpEnd, dst);
    mpEnd = mpBegin + n;
    return *this;
}

// ================================================================================================
// 0x00ac4570 -- vector<T 0x3c>::erase(first, last).
struct T3c { uint d[15]; };
struct SpVec3c {
    T3c* mpBegin; T3c* mpEnd; T3c* mpCapacity;
    T3c* erase(T3c* first, T3c* last);
};
// @ 0x00ac4570
T3c* SpVec3c::erase(T3c* first, T3c* last)
{
    T3c* d = first;
    T3c* s = last;
    while (s != mpEnd) {
        *d = *s;
        ++d;
        ++s;
    }
    mpEnd -= (last - first);
    return first;
}

// ================================================================================================
// 0x00ac45e0 -- vector<T 0x3c>::DoInsertValue (element has a user copy ctor).
extern "C" T3c* __cdecl copy_2130(T3c* first, T3c* last, T3c* dst); // 0x00ac2130
struct Vec3c {
    T3c* mpBegin; T3c* mpEnd; T3c* mpCapacity; int mAlloc; T3c* mpPool;
    void DoInsertValue(T3c* position, const T3c& value);
};
// @ 0x00ac45e0
void Vec3c::DoInsertValue(T3c* position, const T3c& value)
{
    if (mpEnd != mpCapacity) {
        const T3c* pv = &value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd)
            *mpEnd = *(mpEnd - 1);
        T3c* p = mpEnd - 1;
        while (p != position) {
            *p = *(p - 1);
            --p;
        }
        *position = *pv;
        ++mpEnd;
        return;
    }
    uint oldSize = (uint)(mpEnd - mpBegin);
    uint cap = (oldSize == 0) ? 1 : oldSize * 2;
    T3c* nb;
    if (cap == 0) nb = 0;
    else nb = (T3c*)EA_ALLOC(cap * sizeof(T3c));
    T3c* p = copy_2130(mpBegin, position, nb);
    if (p)
        *p = value;
    ++p;
    p = copy_2130(position, mpEnd, p);
    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
        EA_FREE(mpBegin);
    mpBegin = nb;
    mpEnd = p;
    mpCapacity = nb + cap;
}

// ================================================================================================
// 0x00ac4720 -- vector<Vector3 0xc>::DoAssignValues.
struct Vec3f { float x, y, z; };
struct Vec12 {
    Vec3f* mpBegin; Vec3f* mpEnd; Vec3f* mpCapacity; int mAlloc; Vec3f* mpPool;
    void DoAssignValues(Vec3f* position, const Vec3f& value);
};
// @ 0x00ac4720
void Vec12::DoAssignValues(Vec3f* position, const Vec3f& value)
{
    if (mpEnd != mpCapacity) {
        const Vec3f* pv = &value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd)
            *mpEnd = *(mpEnd - 1);
        Vec3f* p = mpEnd - 1;
        while (p != position) {
            *p = *(p - 1);
            --p;
        }
        *position = *pv;
        ++mpEnd;
        return;
    }
    uint oldSize = (uint)(mpEnd - mpBegin);
    uint cap = (oldSize == 0) ? 1 : oldSize * 2;
    Vec3f* nb;
    if (cap == 0) nb = 0;
    else nb = (Vec3f*)EA_ALLOC(cap * sizeof(Vec3f));
    Vec3f* p = (Vec3f*)copy_2130((T3c*)mpBegin, (T3c*)position, (T3c*)nb);
    if (p)
        *p = value;
    ++p;
    p = (Vec3f*)copy_2130((T3c*)position, (T3c*)mpEnd, (T3c*)p);
    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
        EA_FREE(mpBegin);
    mpBegin = nb;
    mpEnd = p;
    mpCapacity = nb + cap;
}

// ================================================================================================
// 0x00ac4850 -- vector<T 4-byte>::DoAssignValues.
struct E4 { uint d; };
struct Vec4 {
    E4* mpBegin; E4* mpEnd; E4* mpCapacity; int mAlloc; E4* mpPool;
    void DoAssignValues(E4* position, const E4& value);
};
// @ 0x00ac4850
void Vec4::DoAssignValues(E4* position, const E4& value)
{
    if (mpEnd != mpCapacity) {
        const E4* pv = &value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd)
            *mpEnd = *(mpEnd - 1);
        E4* p = mpEnd - 1;
        while (p != position) {
            *p = *(p - 1);
            --p;
        }
        *position = *pv;
        ++mpEnd;
        return;
    }
    uint n = (uint)(mpEnd - mpBegin);
    uint cap = (n == 0) ? 1 : n * 2;
    E4* nb;
    if (cap == 0) nb = 0;
    else nb = (E4*)EA_ALLOC(cap * sizeof(E4));
    E4* p = nb;
    for (E4* q = mpBegin; q != position; ++q) {
        if (p) *p = *q;
        ++p;
    }
    if (p) *p = value;
    E4* d = p + 1;
    for (E4* s = position; s != mpEnd; ++s) {
        if (d) *d = *s;
        ++d;
    }
    if (mpBegin && mpBegin != mpPool)
        EA_FREE(mpBegin);
    mpBegin = nb;
    mpEnd = d;
    mpCapacity = nb + cap;
}

// ================================================================================================
// 0x00ac4970 -- reverse() over 0x3c-byte elements.
// @ 0x00ac4970
void __cdecl reverse_4970(T3c* first, T3c* last)
{
    if (first < last - 1) {
        last -= 1;
        do {
            T3c tmp = *first;
            *first = *last;
            *last = tmp;
            ++first;
            --last;
        } while (first < last);
    }
}

// ================================================================================================
// 0x00ac4a60 -- vector<GlyphInfo>::insert(position, n, value).
extern "C" GlyphInfo* __cdecl filln_6ac440(GlyphInfo* first, uint n, const GlyphInfo* value); // 0x006ac440
extern "C" GlyphInfo* __cdecl copyback_73fe50(GlyphInfo* first, GlyphInfo* last, GlyphInfo* dst); // 0x0073fe50
extern "C" GlyphInfo* __cdecl fill_a52da0(GlyphInfo* first, GlyphInfo* last, const void* value); // 0x00a52da0
struct GlyphVec2 {
    GlyphInfo* mpBegin; GlyphInfo* mpEnd; GlyphInfo* mpCapacity; int mAlloc; GlyphInfo* mpPool;
    void insert(GlyphInfo* position, uint n, const GlyphInfo& value);
};
// @ 0x00ac4a60
void GlyphVec2::insert(GlyphInfo* position, uint n, const GlyphInfo& value)
{
    uint room = (uint)(mpCapacity - mpEnd);
    if (n > room) {
        uint size = (uint)(mpEnd - mpBegin);
        uint newcap = size * 2;
        if (size == 0)
            newcap = 1;
        uint need = size + n;
        if (newcap < need)
            newcap = need;
        GlyphInfo* nb;
        if (newcap) nb = (GlyphInfo*)EA_ALLOC(newcap * 8);
        else nb = 0;
        GlyphInfo* p = (GlyphInfo*)copy_99efa0(mpBegin, position, nb);
        uint cnt = n;
        if (cnt) {
            do {
                if (p) { p->a = value.a; p->b = value.b; }
                p += 1;
                --cnt;
            } while (cnt);
        }
        GlyphInfo* q = (GlyphInfo*)copy_99efa0(position, mpEnd, p);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            EA_FREE(mpBegin);
        mpBegin = nb;
        mpEnd = q;
        mpCapacity = nb + newcap;
        return;
    }
    if (n == 0)
        return;
    GlyphInfo v = value;
    GlyphInfo* oldend = mpEnd;
    uint tail = (uint)(oldend - position);
    if (n < tail) {
        GlyphInfo* newend = oldend + n;
        copyback_73fe50(position, oldend, newend);
        mpEnd = mpEnd + n;
        fill_a52da0(position, newend, &v);
        return;
    }
    uint extra = n - tail;
    filln_6ac440(oldend, extra, &v);
    mpEnd = mpEnd + extra;
    GlyphInfo* p = position;
    GlyphInfo* q = mpEnd;
    while (p != q) {
        *q = *p;
        ++p;
        ++q;
    }
    fill_a52da0(position, oldend, &v);
}

// ================================================================================================
// 0x00ac4c20 -- cAStar constructor (this in ecx, plain return, returns this in eax).
extern char VT_13eb384[]; // 0x013eb384
extern char VT_1459e70[]; // 0x01459e70
extern char VT_1459e60[]; // 0x01459e60
extern char VT_1459e5c[]; // 0x01459e5c
extern char DAT_154df28[]; // 0x0154df28
extern float kf_1485720; // 0x01485720
extern float kf_1470f1c; // 0x01470f1c
struct cSPMemPool {
    void* LockedAligned(uint, uint, int, int, int, int, int, int); // 0x00928a30
};
extern cSPMemPool* g_mempool_16c8b44; // 0x016c8b44
extern "C" void __fastcall cGonzagoSubsystem_ctor_5b5b960(void*); // 0x00b5b960 (this in ecx)
struct FixedAllocatorBase {
    FixedAllocatorBase* ctor(uint, int, int, int, int, void*, void*, int); // 0x00926720
};

// @ 0x00ac4c20
void* __fastcall cAStar_ctor(void* self_)
{
    uchar* p = (uchar*)self_;
    *(void**)p = VT_13eb384;
    cGonzagoSubsystem_ctor_5b5b960(p + 4);
    *(void**)(p + 4) = VT_1459e70;
    *(void**)p = VT_1459e60;
    *(void**)(p + 8) = VT_1459e5c;
    *(uint*)(p + 0x28) = 0;
    *(uint*)(p + 0x2c) = 0;
    *(uint*)(p + 0x30) = 0;
    *(uint*)(p + 0x44) = (uint)(p + 0x40);
    *(uint*)(p + 0x40) = (uint)(p + 0x40);
    *(uint*)(p + 0x4c) = 0;
    *(uint*)(p + 0x48) = 1;
    *(float*)(p + 0x60) = kf_1485720;
    *(float*)(p + 0x64) = kf_1470f1c;
    *(uint*)(p + 0x58) = 1;
    *(void**)(p + 0x54) = DAT_154df28;
    *(uint*)(p + 0x5c) = 0;
    *(uint*)(p + 0x68) = 0;
    void* a = g_mempool_16c8b44->LockedAligned(0x60000, 0x10, 0, 0, 0, 0, 0, 0);
    *(void**)(p + 0x20) = a;
    void* b = g_mempool_16c8b44->LockedAligned(0x60000, 0x10, 0, 0, 0, 0, 0, 0);
    *(void**)(p + 0x24) = b;
    void* fa = EASTL_allocator_allocate(0x20, sz_name_1459e40, 0, 0, 0, 0);
    if (fa)
        fa = ((FixedAllocatorBase*)fa)->ctor(0x4c, 0, 0x80, 0, 0xffffffff,
                                             (void*)0xac12d0, (void*)0x805400, 0);
    *(void**)(p + 0x3c) = fa;
    return self_;
}

// ================================================================================================
// 0x00ac4e10 -- vector<AnalysisInfo 0xc>::assign.
struct EAn { char b[12]; };
extern "C" EAn* __cdecl cp_b84c80(EAn* first, EAn* last, EAn* dst); // 0x00b84c80
extern "C" void __cdecl uc_951740(EAn* volatile* out, EAn* a, EAn* b, EAn* c, EAn* d); // 0x00951740
struct V4e10 {
    EAn *b, *e, *c; int pad; EAn* buf;
    EAn* alloc(uint n, EAn* f, EAn* l); // 0x00d59410
    void assign(EAn* f, EAn* volatile l, int tag);
};
// @ 0x00ac4e10
void V4e10::assign(EAn* f, EAn* volatile l, int tag)
{
    uint n = (uint)(l - f);
    if (n > (uint)(c - b)) {
        EAn* p = alloc(n, f, l);
        if (b && b != buf) EA_FREE(b);
        b = p; e = p + n; c = p + n;
        return;
    }
    uint m = (uint)(e - b);
    if (n <= m) { e = cp_b84c80(f, l, b); return; }
    EAn* mid = f + m;
    cp_b84c80(f, mid, b);
    uc_951740(&l, mid, l, e, l);
    e = l;
}

// ================================================================================================
// 0x00ac4ef0 -- cAStar request free-list release (this in ecx, one arg, ret 4).
struct GVec { GlyphInfo* b; GlyphInfo* e; GlyphInfo* c; void erase(GlyphInfo* first, GlyphInfo* last); // 0x00d018d0
};
struct CAStar {
    char pad_[0x70];
    bool release(void* handle);   // thiscall: this in ecx, handle on the stack
    void drain();
};
// @ 0x00ac4ef0
bool CAStar::release(void* handle)
{
    uchar* s = (uchar*)this;
    int node = *(int*)((char*)handle + 4);
    if (node == 0)
        return false;
    if ((void*)node == *(void**)(s + 0x40))
        ((GVec*)(s + 0x28))->erase(*(GlyphInfo**)(s + 0x28), *(GlyphInfo**)(s + 0x2c));
    *(uint*)((char*)handle + 4) = 0;
    int* prev = *(int**)(node + 4);
    int next = *(int*)node;
    *prev = next;
    *(int**)(next + 4) = prev;
    *(uint*)node = 0;
    *(uint*)(node + 4) = 0;
    int* alloc = *(int**)(s + 0x3c);
    *(int*)node = alloc[4];
    alloc[4] = node;
    return true;
}

// ================================================================================================
// 0x00ac4f50 -- cAStar request queue drain (this in ecx, ret 0).
// @ 0x00ac4f50
void CAStar::drain()
{
    uchar* s = (uchar*)this;
    uchar* anchor = s + 0x40;
    if (*(void**)(anchor + 4) == anchor)
        return;
    for (;;) {
        void* node = *(void**)anchor;                        // first node
        uchar* req = (uchar*)*(void**)((uchar*)node + 8);    // request object
        void* h = *(void**)(req + 4);                        // stored queue node
        if (h != 0) {
            if (h == node) {
                *(uchar**)(s + 0x2c) = *(uchar**)(s + 0x28); // clear vector at +0x28
            }
            *(void**)(req + 4) = 0;
            void* next = *(void**)h;
            void* prev = *(void**)((uchar*)h + 4);
            *(void**)prev = next;
            *(void**)((uchar*)next + 4) = prev;
            *(void**)h = 0;
            *(void**)((uchar*)h + 4) = 0;
            uchar* fl = (uchar*)*(void**)(s + 0x3c);
            *(void**)h = *(void**)(fl + 0x10);
            *(void**)(fl + 0x10) = h;
        }
        anchor = s + 0x40;
        if (*(void**)(anchor + 4) == anchor)
            break;
    }
}
