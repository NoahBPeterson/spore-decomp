// Slice s00ab9220 -- Swarm effect object: ctor/dtor, EASTL vector helpers, static init.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Notes on the shapes found in the original:
//  * 00ab9220 / 00ab9e00 are plain cdecl file-scope helpers.
//  * 00ab9270 / 00ab9720 are the pair dtor/ctor of the 0x6e8-byte Swarm object (__thiscall).
//  * 00ab9410/9550/9e40/9fe0 are eastl::vector<Vector3> members (3 pointers + inline-buffer
//    pointer at +0x10, element stride 12).  00aba040 is the same code for vector<float>.
//  * 00ab9320 / 00ab9a40 are methods on the object whose +0x10 field points at the config block.
#include "types.h"

// ---------------------------------------------------------------------------------------------------
// External helpers referenced by the slice (call targets are relocations; names are ours).
// ---------------------------------------------------------------------------------------------------
void* __cdecl ea_allocate(unsigned size, const char* file, int a, int b, int tag, int line);
void* __cdecl ea_copy(void* first, void* last, void* dst);
void  __cdecl sp_free(void* p);
void  __cdecl operator_new_arr(void* dst, int zero, unsigned size);
void  __cdecl copy_vec12(void* dst, unsigned n, const void* src);
void  __cdecl erase_range(void* first, void* last);
void  __cdecl eastl_vec_fill(void* a, void* b, void* c);
void  __cdecl eastl_vec_shift(void* a, void* b, void* c, void* d, void* e);
void  __cdecl eastl_vec_backward(void* a, void* b, void* c);
void  __cdecl memmove_impl(void* dst, const void* src, unsigned n);
void  __cdecl mat3_assign(void* self, const void* src);
void  __cdecl csp_assign(void* self, int src);
int   __cdecl compose_xform(void* dst, int a, int b);
double __cdecl random_double(void* self);

// Virtual-call helpers: the slot offsets are byte offsets into the vtable.
static __forceinline int vcall_i(void* o, int off)
{
    void** vt = *(void***)o;
    void* f = vt[off / 4];
    return ((int(__thiscall*)(void*))f)(o);
}
static __forceinline int vcall_ii(void* o, int off, int a, int b)
{
    void** vt = *(void***)o;
    void* f = vt[off / 4];
    return ((int(__thiscall*)(void*, int, int))f)(o, a, b);
}
static __forceinline int vcall_iii(void* o, int off, int a, int b, int c)
{
    void** vt = *(void***)o;
    void* f = vt[off / 4];
    return ((int(__thiscall*)(void*, int, int, int))f)(o, a, b, c);
}
static __forceinline int vcall_ptr(void* o, int off, void* a, void* b)
{
    void** vt = *(void***)o;
    void* f = vt[off / 4];
    return ((int(__thiscall*)(void*, void*, void*))f)(o, a, b);
}
static __forceinline int vcall_ptr(void* o, int off, void* a, void* b, void* c)
{
    void** vt = *(void***)o;
    void* f = vt[off / 4];
    return ((int(__thiscall*)(void*, void*, void*, void*))f)(o, a, b, c);
}

// A 12-byte element (Vector3).
struct V3 { float x, y, z; };

// eastl::vector<Vector3> with an inline buffer; the buffer pointer lives at +0x10 and is compared
// against mpBegin before every free (that is the `?? 0 && ?? != mInline` test in every helper).
struct V12
{
    V3*   mBegin;                    // +0x00
    V3*   mEnd;                      // +0x04
    V3*   mCap;                      // +0x08
    int   m01C;                      // +0x0c
    void* mInline;                   // +0x10

    void  reserve(unsigned n);
    void  insert_n(V3* pos, unsigned n, const V3& v);
    V3*   insert_one(V3* pos, const V3& v);
    void  resize(unsigned n, const V3& v);
    V3*   erase(V3* first, V3* last);
};

// eastl::vector<float>, same layout.
struct VF
{
    float* mBegin;                   // +0x00
    float* mEnd;                     // +0x04
    float* mCap;                     // +0x08
    int    m01C;                     // +0x0c
    void*  mInline;                  // +0x10

    void   insert_n(float* pos, unsigned n, const float& v);
};

// The 0x6e8-byte Swarm object.  Only the fields this slice touches are named; everything else is
// reached through byte offsets so the layout stays exact.
struct Big
{
    void* m000;                      // +0x000 vptr
    void* m004;                      // +0x004 vptr (GmeIComponent)
    void* m008;                      // +0x008 vptr (GmeRefCount)
    int   m00C;                      // +0x00c
    char  b010;                      // +0x010
    char  b011;                      // +0x011
    char  b012;                      // +0x012
    char  pad013;
    int   m014;                      // +0x014  (param stored by ctor)
    int   m018;
    char  pad01C[0x134 - 0x01C];
    V12   mVec134;                   // +0x134  vector<Vector3> (0x14 bytes, ends +0x148)
    char  pad148[0x53C - 0x148];
    int   m53C;
    char  pad540[0x54C - 0x540];
    int   m54C;
    char  pad550[0x570 - 0x550];
    int   m570;
    char  pad574[0x580 - 0x574];
    int   m580;
    char  pad584[0x6D4 - 0x584];
    int   m6D4;
    int   m6D8;
    int   m6DC;
    int   m6E0;

    Big*  ctor(int param);
    void  dtor();
    void  Init(int* a2, int* a3);

    // helper accessors for the byte-offset fields used below
    char* base() { return (char*)this; }
};

// The object 00ab9320 / 00ab9a40 are called on: a cSPTransform-ish block whose +0x10 points at the
// shared config record.
struct Cfg
{
    int   m000, m004, m008, m00C, m010, m014, m018, m01C, m020, m024;
    int   m028, m02C, m030, m034, m038, m03C, m040, m044;
    char  pad048[0x0E8 - 0x048];
    int   m0E8, m0EC;
    float m0F0[8];                   // +0x0f0 .. +0x10f
    char  pad110[0x114 - 0x110];
    float m114, m118;
    char  pad11C[0x138 - 0x11C];
    int   m138, m13C, m140, m144;
};

// ===================================================================================================
// 0x00ab9220  one-shot static initialiser: allocate the two 0x80-byte hook tables and patch them.
// ===================================================================================================
// @ 0x00ab9220
void __cdecl FUN_00ab9220(char param_1)
{
    if (param_1 != 0) {
        operator_new_arr((void*)0x01679690, 0, 0x80);
        operator_new_arr((void*)0x01679710, 0, 0x80);
        *(void* volatile*)0x01679710 = (void*)0x00ab7720;
        *(void* volatile*)0x01679730 = (void*)0x00ab86d0;
        *(void* volatile*)0x01679690 = (void*)0x00ab3370;
    }
}

// ===================================================================================================
// 0x00ab9270  destructor of the Swarm object.
// ===================================================================================================
// @ 0x00ab9270
void Big::dtor()
{
    *(void* volatile*)&m000 = (void*)0x01459678;
    *(void* volatile*)&m004 = (void*)0x0145963c;
    *(void* volatile*)&m008 = (void*)0x01459638;

    int o1 = *(int volatile*)&m6DC;
    if (o1 != 0) {
        void* o = (void*)o1;
        void** vt = *(void***)o;
        void* f = vt[1];
        ((void(__thiscall*)(void*))f)(o);
    }
    int o2 = *(int volatile*)&m6D8;
    if (o2 != 0) {
        void* o = (void*)o2;
        void** vt = *(void***)o;
        void* f = vt[1];
        ((void(__thiscall*)(void*))f)(o);
    }
    if (m570 != 0 && m570 != m580)
        sp_free((void*)m570);
    if (m53C != 0 && m53C != m54C)
        sp_free((void*)m53C);
    if (mVec134.mBegin != 0 && (void*)mVec134.mBegin != mVec134.mInline)
        sp_free(mVec134.mBegin);

    m004 = (void*)0x013f21d4;
    m008 = (void*)0x013ef094;
}

// ===================================================================================================
// 0x00ab9e00  factory: allocate a 0x6e8-byte Swarm object, construct it, return its +4 subobject.
// ===================================================================================================
// @ 0x00ab9e00
int* __cdecl FUN_00ab9e00(int param_1)
{
    Big* p = (Big*)ea_allocate(0x6e8, "Swarm", 0, 0, 0, 0);
    if (p != 0) {
        Big* r = p->ctor(param_1);
        if (r != 0)
            return (int*)((char*)r + 4);
    }
    return 0;
}

// ===================================================================================================
// 0x00ab9410  vector<Vector3>::reserve(n)
// ===================================================================================================
// @ 0x00ab9410
void V12::reserve(unsigned n)
{
    if (n > (unsigned)(mCap - mBegin)) {
        V3* p;
        if (n != 0)
            p = (V3*)ea_allocate(n * 12, "EASTL", 0, 0, 0x013ebb38, 0xd1);
        else
            p = 0;
        ea_copy(mBegin, mEnd, p);
        if (mBegin != 0 && (void*)mBegin != mInline)
            sp_free(mBegin);
        unsigned cnt = (unsigned)(mEnd - mBegin);
        mBegin = p;
        mEnd   = p + cnt;
        mCap   = p + n;
    }
}

// ===================================================================================================
// 0x00ab9fe0  vector<Vector3>::resize(n, value)
// ===================================================================================================
// @ 0x00ab9fe0
void V12::resize(unsigned n, const V3& v)
{
    if (n > (unsigned)(mEnd - mBegin))
        insert_n(mEnd, n - (unsigned)(mEnd - mBegin), v);
    else
        erase(mBegin + n, mEnd);
}

// ===================================================================================================
// 0x00ab9e40  vector<Vector3>::insert(pos, value) -- single element.
// ===================================================================================================
// @ 0x00ab9e40
V3* V12::insert_one(V3* pos, const V3& v)
{
    V3* end = mEnd;
    if (end != mCap) {
        V3* src = (V3*)&v;
        if (src >= pos && src < end)
            src = src + 1;
        if (end != 0) {
            end->x = end[-1].x;
            end->y = end[-1].y;
            end->z = end[-1].z;
        }
        V3* p = mEnd - 1;
        while (p != pos) {
            V3* q = p - 1;
            V3* d = p;
            d->x = q->x;
            d->y = q->y;
            d->z = q->z;
            p = q;
        }
        pos->x = src->x;
        pos->y = src->y;
        pos->z = src->z;
        mEnd = mEnd + 1;
        return pos;
    }

    unsigned cnt = (unsigned)(end - mBegin);
    unsigned newCap = cnt * 2;
    if (cnt == 0)
        newCap = 1;
    V3* p = 0;
    if (newCap != 0)
        p = (V3*)ea_allocate(newCap * 12, "EASTL", 0, 0, 0x013ebb38, 0xd1);
    V3* written = pos;
    if (p != 0) {
        ea_copy(mBegin, pos, p);
        written = p + (pos - mBegin);
        *written = v;
    }
    V3* newEnd = (V3*)ea_copy(pos, end, written + 1);
    if (mBegin != 0 && (void*)mBegin != mInline)
        sp_free(mBegin);
    mBegin = p;
    mEnd   = newEnd;
    mCap   = p + newCap;
    return written;
}

// ===================================================================================================
// 0x00ab9550  vector<Vector3>::insert_n(pos, n, value)
// ===================================================================================================
// @ 0x00ab9550
void V12::insert_n(V3* pos, unsigned n, const V3& v)
{
    V3* end = mEnd;
    if ((unsigned)(mCap - end) < n) {
        unsigned have = (unsigned)(end - mBegin);
        unsigned newCap = have * 2;
        if (have == 0)
            newCap = 1;
        unsigned want = have + n;
        if (want < newCap)
            want = newCap;
        V3* p = want ? (V3*)ea_allocate(want * 12, "EASTL", 0, 0, 0x013ebb38, 0xd1) : 0;
        ea_copy(mBegin, pos, p);
        copy_vec12(p + have, n, &v);
        V3* newEnd = (V3*)ea_copy(pos, end, p + have + n);
        if (mBegin != 0 && (void*)mBegin != mInline)
            sp_free(mBegin);
        mBegin = p;
        mEnd   = newEnd;
        mCap   = p + want;
        return;
    }
    if (n == 0)
        return;

    V3 tmp = v;
    V3* e = mEnd;
    unsigned tail = (unsigned)(e - pos);
    if (n < tail) {
        unsigned nbytes = n * 12;
        V3* split = e - n;
        eastl_vec_shift(pos, split, e, e, &tmp);
        mEnd = mEnd + n;
        eastl_vec_backward(pos, split, e);
        eastl_vec_fill(pos, pos + n, &tmp);
        return;
    }
    unsigned extra = n - tail;
    copy_vec12(e, extra, &tmp);
    V3* mid = pos;
    mEnd = mEnd + extra;
    eastl_vec_shift(pos, pos, e, mEnd, &mid);
    mEnd = mEnd + tail;
    eastl_vec_fill(mid, e, &tmp);
}

// ===================================================================================================
// 0x00aba040  vector<float>::insert_n(pos, n, value)
// ===================================================================================================
// @ 0x00aba040
void VF::insert_n(float* pos, unsigned n, const float& v)
{
    float* end = mEnd;
    if ((unsigned)(mCap - end) < n) {
        unsigned have = (unsigned)(end - mBegin);
        unsigned newCap = have * 2;
        if (have == 0)
            newCap = 1;
        unsigned want = have + n;
        if (want < newCap)
            want = newCap;
        float* p = want ? (float*)ea_allocate(want * 4, "EASTL", 0, 0, 0x013ebb38, 0xd1) : 0;
        ea_copy(mBegin, pos, p);
        unsigned i;
        for (i = 0; i < n; i++)
            p[have + i] = v;
        float* newEnd = (float*)ea_copy(pos, end, p + have + n);
        if (mBegin != 0 && (void*)mBegin != mInline)
            sp_free(mBegin);
        mBegin = p;
        mEnd   = newEnd;
        mCap   = p + want;
        return;
    }
    if (n == 0)
        return;

    float tmp = v;
    float* e = mEnd;
    unsigned tail = (unsigned)(e - pos);
    if (n < tail) {
        float* split = e - n;
        memmove_impl(split, pos, (e - split) * 4);
        mEnd = mEnd + n;
        memmove_impl(pos + n, pos, (split - pos) * 4);
        float* q = pos;
        while (q != pos + n)
            *q++ = tmp;
        return;
    }
    unsigned extra = n - tail;
    float* fillEnd = e + extra;
    while (e != fillEnd)
        *e++ = tmp;
    mEnd = mEnd + extra;
    memmove_impl(pos + extra, pos, (tail) * 4);
    float* q = pos;
    while (q != pos + extra)
        *q++ = tmp;
}

// ===================================================================================================
// 0x00ab9320  set the two transforms; when the fast flag is set compose them and reset the state.
// ===================================================================================================
// @ 0x00ab9320
void FUN_00ab9320(char* self, int a2, int a3)
{
    Cfg* cfg = *(Cfg**)(self + 0x10);
    if ((((unsigned)cfg->m008 >> 0xd) & 1) == 0) {
        csp_assign(self + 0x78, a2);
        csp_assign(self + 0xb0, a3);
    } else {
        char local[56];
        void* r = (void*)compose_xform(local, a2, a3);
        csp_assign(self + 0x78, (int)r);
        struct Blob9 { int v[9]; };
        *(Blob9*)(self + 0xc4) = *(Blob9*)0x01679888;
        *(unsigned*)(self + 0xc0) = 0x3f800000;
        *(int*)(self + 0xb4) = *(int*)0x016797dc;
        *(int*)(self + 0xb8) = *(int*)0x016797e0;
        *(int*)(self + 0xbc) = *(int*)0x016797e4;
        *(short*)(self + 0xb0) = 0;
        *(short*)(self + 0xb2) = 0;
    }
    *(int*)(self + 0x60) = *(int*)(self + 0x7c);
    *(int*)(self + 0x64) = *(int*)(self + 0x80);
    *(int*)(self + 0x68) = *(int*)(self + 0x84);
    *(int*)(self + 0x6c) = *(int*)(self + 0x8c);
    *(int*)(self + 0x70) = *(int*)(self + 0x90);
    *(int*)(self + 0x74) = *(int*)(self + 0x94);
}

// ===================================================================================================
// 0x00ab9720  constructor of the Swarm object (0x6e8 bytes).
// ===================================================================================================
// @ 0x00ab9720
Big* Big::ctor(int param)
{
    char* s = base();

    *(void**)(s + 0x008) = (void*)0x013ef094;
    *(int*)(s + 0x00C)   = 0;
    *(void**)(s + 0x004) = (void*)0x013f21d4;
    *(void**)(s + 0x008) = (void*)0x013f2194;
    *(float*)(s + 0x044) = -999.0f;
    *(void**)(s + 0x000) = (void*)0x01459678;
    *(void**)(s + 0x004) = (void*)0x0145963c;
    *(void**)(s + 0x008) = (void*)0x01459638;
    *(char*)(s + 0x010)  = 0;
    *(char*)(s + 0x011)  = 1;
    *(char*)(s + 0x012)  = 0;
    *(int*)(s + 0x014)   = param;
    *(int*)(s + 0x018)   = 0;
    *(int*)(s + 0x01C)   = 0;
    *(float*)(s + 0x028) = 0.0f;
    *(float*)(s + 0x02C) = 0.0f;
    *(float*)(s + 0x030) = 0.0f;
    *(float*)(s + 0x034) = 0.0f;
    *(int*)(s + 0x038)   = 0;
    *(float*)(s + 0x03C) = 0.0f;
    *(float*)(s + 0x040) = 0.0f;
    *(float*)(s + 0x048) = 1.0f;
    *(float*)(s + 0x04C) = 0.0f;
    *(float*)(s + 0x050) = 0.0f;
    *(float*)(s + 0x054) = 0.0f;
    *(float*)(s + 0x058) = 0.0f;
    *(float*)(s + 0x05C) = 0.0f;
    *(float*)(s + 0x060) = 0.0f;
    *(float*)(s + 0x064) = 0.0f;
    *(float*)(s + 0x068) = 0.0f;
    *(float*)(s + 0x06C) = 0.0f;
    *(float*)(s + 0x070) = 1.0f;
    *(float*)(s + 0x074) = 0.0f;
    *(float*)(s + 0x078) = 0.0f;
    *(short*)(s + 0x07C) = 0;
    *(short*)(s + 0x07E) = 0;
    *(int*)(s + 0x080)   = *(int*)0x016797dc;
    *(int*)(s + 0x084)   = *(int*)0x016797e0;
    *(int*)(s + 0x088)   = *(int*)0x016797e4;
    *(float*)(s + 0x08C) = 1.0f;
    mat3_assign(s + 0x090, (void*)0x01679888);
    *(short*)(s + 0x0B6) = 0;
    *(short*)(s + 0x0B4) = 0;
    *(int*)(s + 0x0B8)   = *(int*)0x016797dc;
    *(int*)(s + 0x0BC)   = *(int*)0x016797e0;
    *(int*)(s + 0x0C0)   = *(int*)0x016797e4;
    *(float*)(s + 0x0C4) = 1.0f;
    mat3_assign(s + 0x0C8, (void*)0x01679888);
    *(short*)(s + 0x0EC) = 0;
    *(short*)(s + 0x0EE) = 0;
    *(int*)(s + 0x0F0)   = *(int*)0x016797dc;
    *(int*)(s + 0x0F4)   = *(int*)0x016797e0;
    *(int*)(s + 0x0F8)   = *(int*)0x016797e4;
    *(float*)(s + 0x0FC) = 1.0f;
    *(float*)(s + 0x100) = 1.0f;
    *(int*)(s + 0x104)   = *(int*)0x016797c0;
    *(int*)(s + 0x108)   = *(int*)0x016797c4;
    *(int*)(s + 0x10C)   = *(int*)0x016797c0;
    *(int*)(s + 0x110)   = *(int*)0x016797c4;
    *(float*)(s + 0x114) = 1.0f;
    *(float*)(s + 0x118) = 1.0f;
    *(int*)(s + 0x11C)   = *(int*)0x01679790;
    *(int*)(s + 0x120)   = *(int*)0x01679794;
    *(int*)(s + 0x124)   = *(int*)0x01679798;
    *(char*)(s + 0x130)  = 0;
    *(int*)(s + 0x128)   = -1;

    {
        char* buf = s + 0x14c;
        V12* v = (V12*)(s + 0x134);
        v->mBegin  = (V3*)buf;
        v->mEnd    = (V3*)buf;
        v->mInline = buf;
        v->mCap    = (V3*)(buf + 0x3f0);
    }
    {
        char* buf = s + 0x554;
        V12* v = (V12*)(s + 0x53c);
        v->mBegin  = (V3*)buf;
        v->mEnd    = (V3*)buf;
        v->mInline = buf;
        v->mCap    = (V3*)(buf + 0x18);
    }
    *(float*)(s + 0x56C) = 0.0f;
    {
        char* buf = s + 0x588;
        V12* v = (V12*)(s + 0x570);
        v->mBegin  = (V3*)buf;
        v->mEnd    = (V3*)buf;
        v->mInline = buf;
        v->mCap    = (V3*)(buf + 0x150);
    }
    *(int*)(s + 0x6D8)  = 0;
    *(int*)(s + 0x6DC)  = 0;
    *(char*)(s + 0x6E0) = 0;
    *(char*)(s + 0x6E1) = 0;
    return this;
}

// ===================================================================================================
// 0x00ab9a40  initialise the effect from the two config objects.
// ===================================================================================================
// @ 0x00ab9a40
void Big::Init(int* a2, int* a3)
{
    char* s = base();
    Cfg* cfg;

    *(int*)(s + 0x014) = vcall_i(a2, 0x20);
    *(int*)(s + 0x018) = vcall_i(a2, 0x2c);

    float k = *(float*)0x01565760;
    *(float*)(s + 0x048) = k;
    *(float*)(s + 0x04C) = k;
    *(float*)(s + 0x050) = k;
    float nk = -k;
    *(float*)(s + 0x054) = nk;
    *(float*)(s + 0x058) = nk;
    *(float*)(s + 0x05C) = nk;
    *(float*)(s + 0x024) = 0.0f;

    cfg = *(Cfg**)(s + 0x010);
    float lo = *(float*)((char*)cfg + 0x0c);
    float hi = *(float*)((char*)cfg + 0x10);
    float r = (float)(random_double((void*)0x016778dc) * (double)(hi - lo) + (double)lo);
    if (r > hi)
        r = hi;
    if (r < lo)
        r = lo;
    *(float*)(s + 0x028) = r;
    *(float*)(s + 0x02C) = 1.0f / r;
    *(int*)(s + 0x034) = cfg->m0E8;
    ((V12*)(s + 0x130))->reserve((unsigned)cfg->m0E8 + 1);
    ((V12*)(s + 0x56C))->reserve((unsigned)cfg->m0E8 + 1);
    ((V12*)(s + 0x538))->reserve((((unsigned)cfg->m008 >> 6) & 1) ? (unsigned)cfg->m0E8 + 1 : 2u);

    cfg = *(Cfg**)(s + 0x010);
    *(float*)(s + 0x030) = (float)cfg->m0EC;
    {
        unsigned n = (unsigned)((*(int*)((char*)cfg + 0x2c) - *(int*)((char*)cfg + 0x28)) >> 2);
        unsigned i;
        for (i = 0; i < n; i++) {
            float f = *(float*)(*(int*)((char*)cfg + 0x28) + i * 4);
            if (f > *(float*)(s + 0x030))
                *(float*)(s + 0x030) = f;
        }
    }
    *(float*)(s + 0x030) = *(float*)(s + 0x030) * 0.5f;

    if ((cfg->m140 & cfg->m144) != -1) {
        int r2 = vcall_ii(a3, 0x8c, cfg->m140, cfg->m144);
        int old = *(int*)(s + 0x6D4);
        if (r2 != old) {
            if (r2 != 0)
                vcall_i((int*)r2, 0x00);
            *(int*)(s + 0x6D4) = r2;
            if (old != 0)
                vcall_i((int*)old, 0x04);
        }
    }
    if ((cfg->m138 & cfg->m13C) != -1) {
        int r2 = vcall_ii(a3, 0x8c, cfg->m138, cfg->m13C);
        int old = *(int*)(s + 0x6D8);
        if (r2 != old) {
            if (r2 != 0)
                vcall_i((int*)r2, 0x00);
            *(int*)(s + 0x6D8) = r2;
            if (old != 0)
                vcall_i((int*)old, 0x04);
        }
    }
    if (*(int*)(s + 0x6D4) != 0) {
        vcall_i(*(int**)(s + 0x6D4), 0x08);
        *(char*)(s + 0x6DC) = (char)vcall_i(*(int**)(s + 0x6D4), 0x1c);
    }
    if (*(int*)(s + 0x6D8) != 0) {
        vcall_i(*(int**)(s + 0x6D8), 0x08);
        *(char*)(s + 0x6DD) = (char)vcall_i(*(int**)(s + 0x6D8), 0x1c);
    }

    {
        int* p = (int*)vcall_i(a2, 0x20);
        cfg = *(Cfg**)(s + 0x010);
        float t = cfg->m114;
        if (t == -999.0f) {
            *(float*)(s + 0x040) = -999.0f;
        } else {
            float inv = 1.0f / t;
            *(float*)(s + 0x040) = inv * 30.0f;
        }
        *(float*)(s + 0x044) = (cfg->m118 * 30.0f) / (float)cfg->m0E8;
        *(float*)(s + 0x568) = *(float*)((char*)cfg + 0x44) * 30.0f;
        if (p != 0) {
            int st[8];
            int i;
            for (i = 0; i < 8; i++)
                st[i] = (int)cfg->m0F0[i];
            char flag;
            if ((((unsigned)cfg->m008 >> 0xc) & 1) == 0)
                flag = 0;
            else
                flag = (char)vcall_i((int*)*(int*)(s + 0x014), 0x14);
            if (((char*)st)[1] == 0x0f) {
                int* q = (int*)vcall_i(a3, 0x14);
                flag = (char)vcall_iii(q, 0x24, st[0], st[1], (int)flag);
            }
            vcall_ptr(p, 0x18, s - 4, st, s + 0x124);
            vcall_ptr(p, 0x10, (void*)flag, s + 0x128);
            *(char*)(s + 0x12C) = (char)st[0];
        }
    }
}
