// Slice s006ec0c0 -- effects/camera helpers and EASTL vector instantiations.
#include <string.h>
#include <intrin.h>
#include <stdlib.h>
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned long long u64;

extern void*  f_f47380(void*);
extern void*  f_f473a0(int size, const char* name, int flags, int align, const char* file, int line);
extern void   f_ac2060(uint*, int, int, int, uint, uint, int);
extern int    f_ac3fa0(uint*, uint*, int);
extern int    f_7c3af0(int);
extern void   f_6ebd20(int, int);
extern void   f_6f66a0(int*);
extern int    f_6ebe50(uint*, int, uint, uint, int);
extern void   f_grow4(void*, int*);

// eastl copy/relocate helpers used by the vector instantiations below.
extern int*   f_42f530(void* first, int* last, void* value);   // erase range
extern void   f_42f5b0(int* dst, int* first, int* last);       // move_backward
extern int*   f_a11310(const void* first, const void* last, void* dst);

#define VFN(p, off)  (*(void***)(p))[((off) >> 2)]

static const char kAllocName[] = "Graphics";
static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// vtable slot 0 = AddRef, slot 1 = Release of the ref-counted objects held by these vectors.
__forceinline void AddRefObj(void* p)
{
    if (p) {
        void** vt = *(void***)p;
        ((void (__thiscall*)(void*))vt[0])(p);
    }
}

__forceinline void ReleaseObj(void* p)
{
    if (p) {
        void** vt = *(void***)p;
        ((void (__thiscall*)(void*))vt[1])(p);
    }
}

__forceinline void CallVtbl8(void* p)   // virtual slot at vtable offset 0x08
{
    void** vt = *(void***)p;
    ((void (__thiscall*)(void*))vt[2])(p);
}

// Shared-reference header of the resource objects: the counter sits 8 bytes in.
struct SharedHead {
    char          m_pad00[8];
    volatile long m_refs;      // +0x08
};

__forceinline void ReleaseShared(SharedHead* r)
{
    volatile long* c = &r->m_refs;
    _InterlockedDecrement(c);
    if (_InterlockedExchangeAdd(c, 0) < 1)
        _InterlockedIncrement(c);
    else
        _InterlockedExchangeAdd(c, 0);
}

// vector<Pair3> -- 3 dwords per element
struct VecC {
    int* b;                    // +0x00
    int* e;                    // +0x04
    int* cap;                  // +0x08
    int* m_spare;              // +0x0c
    int* m_pInline;            // +0x10  inline buffer, not owned
    void DoInsert(int* pos, int* v);   // 0x6ec260
};

// Plain EASTL vector layout shared by the 4-byte and 2-byte instantiations.
template <class T>
struct EaVector {
    T*   m_begin;              // +0x00
    T*   m_end;                // +0x04
    T*   m_cap;                // +0x08
    int* m_pSpare;             // +0x0c
    T*   m_pInline;            // +0x10  inline buffer, not owned
};

// Inline small-string storage helper (thiscall, two int args).
struct SmallStrObj {
    void FUN_006ebd20(int a, int b);   // 0x006ebd20
};

// eastl::vector<unsigned int> (grow path lives in 0x4558a0).
struct VecU32 {
    int* b;
    int* e;
    int* cap;
    void DoInsertValue(int* pos, const int* v);   // 0x004558a0
};

// cVecU16 (end at +4, capacity at +8; this = object+0x5c).
struct VecU16 {
    ushort* b;
    ushort* e;
    ushort* cap;
    void FUN_006f66a0(const ushort* v);   // 0x006f66a0
};

// 0xc0-stride camera/effect record.
struct Eff {
    uchar m_c0;                // +0x00  copies as a single byte
    char  m_pad01[3];
    char  m_str[0x94];         // +0x04  inline string (see m660)
    float m_f98;               // +0x98
    float m_f9C;               // +0x9c
    int   m_iA0;               // +0xa0
    int   m_iA4;               // +0xa4
    float m_fA8;               // +0xa8
    float m_fAC;               // +0xac
    float m_fB0;               // +0xb0
    float m_fB4;               // +0xb4
    float m_fB8;               // +0xb8
    float m_fBC;               // +0xbc
};

// List of payload descriptors hung off a resource record.
struct ResList {
    char  m_pad00[8];
    int** m_begin;             // +0x08
    int** m_end;               // +0x0c
};

// One entry of a ResList: tagged descriptor whose payload starts 8 bytes in.
struct ResItem {
    int    m_i00;              // +0x00
    ushort m_tag;              // +0x04
    char   m_pad06[2];
    int*   m_payload;          // +0x08
};

// 0x70-byte resource record.
struct ResRec {
    int         m_i00;         // +0x00  owner flag (0 = free)
    char        m_pad04[0x24];
    SharedHead* m_p28;         // +0x28
    SharedHead* m_p2C;         // +0x2c
    char        m_pad30[0x18];
    uchar       m_b48;         // +0x48
    char        m_pad49[0x13];
    int         m_i5C;         // +0x5c
    ResList*    m_list;        // +0x60
    int*        m_p64;         // +0x64  graphics payload
    int*        m_p68;         // +0x68  manager-owned resource
    void*       m_p6C;         // +0x6c
};

// Header of the resource table embedded in the big object (offsets from its base).
struct ResTable {
    char     m_pad00[0x48];
    ResRec*  m_begin;          // +0x48
    ResRec*  m_end;            // +0x4c
    char     m_pad50[0x20];
    VecU32   m_freeList;       // +0x70  freed record indices
    char     m_pad7C[0x164];
    void*    m_resMgr;         // +0x1e0
};

struct S8 {
    char m_unk[0x30d80];

    bool m0c0(int a, int idx, int c, int count, void* src);  // 0x6ec0c0
    void m4a0(int* pos, int* v);                             // 0x6ec4a0
    __declspec(noinline) void m660(void* src);               // 0x6ec660
    S8*  m730();                                             // 0x6ec730
    void m840(int a, int b);                                 // 0x6ec840
    void m8a0(int* pos, int* v);                             // 0x6ec8a0
    Eff* maa0(Eff* src);                                     // 0x6ecaa0
    void mb40(ushort* pos, uint n, const ushort* value);     // 0x6ecb40
    void mdd0(int a, int b);                                 // 0x6ecdd0
    void me30(int a, int b, int c);                          // 0x6ece30
    void me90(int n, int* a, int* b);                        // 0x6ece90
    void mf10();                                             // 0x6ecf10
    S8* mfc0(void* src);                                     // 0x6ecfc0 (returns this)
    void md070(int idx);                                     // 0x6ed070
    void md1a0(int idx, char v);                             // 0x6ed1a0
    void md210(int idx);                                     // 0x6ed210
};

// free helpers
int  __cdecl f6d0(int p1, int p2, int p3);     // 0x6ec6d0
void __stdcall fca50(char* p1, char* p2);      // 0x6eca50
void f5b0(uint* p1, int p2, int p3, int p4);   // 0x6ec5b0
// ---------------------------------------------------------------------------
// @ 0x006ec0c0
bool S8::m0c0(int a, int idx, int c, int count, void* src)
{
    ResTable* t = (ResTable*)this;

    if (a != 0)
        return false;
    if (idx < 0)
        return true;
    if (idx >= (int)(t->m_end - t->m_begin))
        return true;

    ResRec* rec = t->m_begin + idx;
    if (rec->m_p64 == 0) {
        int* buf = (int*)f_f473a0(0x100, kAllocName, 0, 0, 0, 0);
        rec->m_p64 = buf;
        memset(buf, 0, 0x100);
        ResList* list = rec->m_list;
        if (list != 0) {
            int n = (int)(list->m_end - list->m_begin);
            for (int i = 0; i < n; i++) {
                ResItem* item = (ResItem*)list->m_begin[i];
                if (item->m_tag == 0x206) {
                    memcpy(rec->m_p64, item->m_payload, 0x100);
                    break;
                }
            }
        }
    }
    memcpy(rec->m_p64, src, count * 4);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006ec260  VecC::DoInsert
void VecC::DoInsert(int* pos, int* v)
{
    int* end = e;

    if (end != cap) {
        if (pos <= v && v < end)
            v += 3;
        if (end) {
            end[0] = end[-3];
            end[1] = end[-2];
            end[2] = end[-1];
        }
        for (int* d = end - 3; d != pos; d -= 3) {
            d[0] = d[-3];
            d[1] = d[-2];
            d[2] = d[-1];
        }
        pos[0] = v[0];
        pos[1] = v[1];
        pos[2] = v[2];
        e = end + 3;
        return;
    }

    int n = (int)(end - b);
    if (n == 0)
        n = 1;
    else
        n = n * 2;

    int* dst = n != 0 ? (int*)f_f473a0(n * 3 * 4, kAllocName, 0, 0, kAllocFile, 0xd1) : 0;
    int* at = f_a11310(b, pos, dst);
    if (at != 0) {
        at[0] = v[0];
        at[1] = v[1];
        at[2] = v[2];
    }
    int* ne = f_a11310(pos, end, at + 3);
    if (b != 0 && b != m_pInline)
        f_f47380(b);
    b = dst;
    e = ne;
    cap = dst + n * 3;
}

// ---------------------------------------------------------------------------
// @ 0x006ec4a0
void S8::m4a0(int* pos, int* v)
{
    EaVector<int>* vec = (EaVector<int>*)this;
    int* end = vec->m_end;

    if (end != vec->m_cap) {
        if (pos <= v && v < end)
            v = v + 1;
        if (end)
            end[0] = end[-1];
        int bytes = (int)end - 4 - (int)pos;
        memmove((char*)end - (bytes >> 2) * 4, pos, bytes);
        pos[0] = v[0];
        vec->m_end += 1;
        return;
    }

    uint cap = (uint)(end - vec->m_begin);
    int* dst;
    if (cap > 0)
        cap = cap * 2;
    else
        cap = 1;
    if (cap != 0)
        dst = (int*)f_f473a0(cap * 4, kAllocName, 0, 0, kAllocFile, 0xd1);
    else
        dst = 0;
    int head = (int)pos - (int)vec->m_begin;
    int* at = (int*)memcpy(dst, vec->m_begin, head) + (head >> 2);
    if (at != 0)
        at[0] = v[0];
    int tail = (int)end - (int)pos;
    int* ne = (int*)memcpy(at + 1, pos, tail) + (tail >> 2);
    if (vec->m_begin != 0 && vec->m_begin[-1] != 0)
        f_f47380(vec->m_begin);
    vec->m_begin = dst;
    vec->m_end = ne;
    vec->m_cap = dst + cap;
}

// ---------------------------------------------------------------------------
// @ 0x006ec5b0
void f5b0(uint* p1, int p2, int p3, int p4)
{
    uint d = p2 - (int)p1;
    while ((int)(d & 0xfffffff8) > 0xe0 && p3 > 0) {
        uint a = *p1;
        int i = (p2 - (int)p1) >> 3;
        i = (i - (i >> 0x1f)) >> 1;
        uint x = p1[i * 2];
        uint y = x;
        uint* m = p1 + i * 2;
        uint* p = p1;
        if (x < a) { y = a; m = p1; p = p1 + i * 2; a = x; }
        if (a <= *(uint*)(p2 - 8) && *(uint*)(p2 - 8) < y)
            p = (uint*)(p2 - 8);
        int r = f_6ebe50(p1, p2, *p, p[1], p4);
        p3--;
        f5b0((uint*)r, p2, p3, p4);
        d = r - (int)p1;
        p2 = r;
    }
    if (p3 == 0)
        f_ac3fa0(p1, (uint*)p2, p4);
}

// ---------------------------------------------------------------------------
// @ 0x006ec660
__declspec(noinline) void S8::m660(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    char* q = d + 0x14;
    *(void**)(d + 0x10) = q;
    *(void**)(d + 4) = q;
    *(void**)d = q;
    *(void**)(d + 8) = d + 0x94;
    *(ushort*)q = 0;
    ((SmallStrObj*)d)->FUN_006ebd20(*(int*)s, *((int*)s + 1));
}

// ---------------------------------------------------------------------------
// @ 0x006ec6d0
int __cdecl f6d0(int p1, int p2, int p3)
{
    if (p1 != p2) {
        do {
            int i = *(int*)(p1 + 4);
            if ((int)((*(int*)(p1 + 0xc) - i) & 0xfffffffe) > 2 && i != 0 &&
                i != *(int*)(p1 + 0x14))
                f_f47380((void*)i);
            p1 += 0xc0;
            p3 += 0xc0;
        } while (p1 != p2);
    }
    return p3;
}

// ---------------------------------------------------------------------------
// @ 0x006ec730
S8* S8::m730()
{
    char* p = (char*)this;
    *(uchar*)p = 0;
    char* q = p + 0x18;
    *(void**)(p + 0x14) = q;
    *(void**)(p + 8) = q;
    *(void**)(p + 4) = q;
    *(void**)(p + 0xc) = p + 0x98;
    *(ushort*)q = 0;
    *(int*)(p + 0x98) = 0;
    *(int*)(p + 0x9c) = 0;
    *(float*)(p + 0xa8) = 12.0f;
    *(int*)(p + 0xa0) = -1;
    *(int*)(p + 0xa4) = -1;
    float one = 1.0f;
    *(float*)(p + 0xac) = one;
    *(float*)(p + 0xb0) = one;
    *(float*)(p + 0xb4) = one;
    *(float*)(p + 0xb8) = one;
    *(float*)(p + 0xbc) = one;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x006ec840
void S8::m840(int a, int b)
{
    EaVector<int>* vec = (EaVector<int>*)this;
    int* it = f_42f530((void*)b, vec->m_end, (void*)a);
    int* end = vec->m_end;

    while (it < end) {
        ReleaseObj((void*)*it);
        it = it + 1;
    }
    vec->m_end = (int*)((char*)vec->m_end - ((b - a) >> 2) * 4);
}

// ---------------------------------------------------------------------------
// @ 0x006ec8a0
void S8::m8a0(int* pos, int* v)
{
    EaVector<int>* vec = (EaVector<int>*)this;
    int* end = vec->m_end;

    if (end != vec->m_cap) {
        if (pos <= v && v < end)
            v = v + 1;
        if (end) {
            end[0] = end[-1];
            AddRefObj((void*)end[0]);
        }
        f_42f5b0(pos, end - 1, end);
        int* src = v;
        int fresh = *src;
        int stale = *pos;
        if (fresh != stale) {
            AddRefObj((void*)fresh);
            *pos = fresh;
            ReleaseObj((void*)stale);
        }
        vec->m_end = end + 1;
        return;
    }

    int n = (int)(end - vec->m_begin);
    if (n == 0)
        n = 1;
    else
        n = n * 2;

    int* dst = n != 0 ? (int*)f_f473a0(n * 4, kAllocName, 0, 0, kAllocFile, 0xd1) : 0;
    int head = (int)pos - (int)vec->m_begin;
    int* at = (int*)memcpy(dst, vec->m_begin, head) + (head >> 2);
    if (at != 0) {
        int fresh = *v;
        at[0] = fresh;
        AddRefObj((void*)fresh);
    }
    int tail = (int)end - (int)pos;
    int* ne = (int*)memcpy(at + 1, pos, tail) + (tail >> 2);
    if (vec->m_begin != 0 && vec->m_begin != vec->m_pInline)
        f_f47380(vec->m_begin);
    vec->m_begin = dst;
    vec->m_end = ne;
    vec->m_cap = dst + n;
}

// ---------------------------------------------------------------------------
// @ 0x006ecaa0
Eff* S8::maa0(Eff* src)
{
    Eff* dst = (Eff*)this;

    dst->m_c0 = src->m_c0;
    ((S8*)dst->m_str)->m660(src->m_str);
    dst->m_f98 = src->m_f98;
    dst->m_f9C = src->m_f9C;
    dst->m_iA0 = src->m_iA0;
    dst->m_iA4 = src->m_iA4;
    dst->m_fA8 = src->m_fA8;
    dst->m_fAC = src->m_fAC;
    dst->m_fB0 = src->m_fB0;
    dst->m_fB4 = src->m_fB4;
    dst->m_fB8 = src->m_fB8;
    dst->m_fBC = src->m_fBC;
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x006ecb40
void S8::mb40(ushort* pos, uint n, const ushort* value)
{
    EaVector<ushort>* vec = (EaVector<ushort>*)this;
    ushort* end = vec->m_end;

    if (n > (uint)(vec->m_cap - end)) {
        // growth: capacity of the new block is max(2 * old, old + n)
        uint cur = (uint)(end - vec->m_begin);
        uint cap = cur * 2;
        if (cur == 0)
            cap = 1;
        uint need = cur + n;
        uint newsize = cap > need ? cap : need;
        ushort* dst = (ushort*)f_f473a0(newsize * 2, kAllocName, 0, 0, kAllocFile, 0xd1);
        int head = (int)((char*)pos - (char*)vec->m_begin);
        ushort* at = (ushort*)memcpy(dst, vec->m_begin, head) + (head >> 1);
        ushort fill = *value;
        for (ushort* p = at; p != (ushort*)((char*)at + n * 2); p = (ushort*)((char*)p + 2))
            *p = fill;
        int tail = (int)((char*)end - (char*)pos);
        ushort* ne = (ushort*)memcpy((char*)at + n * 2, pos, tail) + (tail >> 1);
        if (vec->m_begin != 0 && ((int*)vec->m_begin)[-1] != 0)
            f_f47380(vec->m_begin);
        vec->m_begin = dst;
        vec->m_end = ne;
        vec->m_cap = (ushort*)((char*)dst + newsize * 2);
        return;
    }

    if (n == 0)
        return;

    ushort fill = *value;
    uint avail = (uint)((char*)end - (char*)pos) >> 1;
    if (n < avail) {
        // append the last n elements into the fresh tail, then shift the middle right
        uint bytes = n * 2;
        ushort* src = (ushort*)((char*)end - bytes);
        memcpy(end, src, bytes);
        vec->m_end = (ushort*)((char*)end + bytes);
        uint span = (uint)((char*)src - (char*)pos);
        memmove((ushort*)((char*)end - span), pos, span);
        for (ushort* p = pos; p != (ushort*)((char*)pos + bytes); p = (ushort*)((char*)p + 2))
            *p = fill;
        return;
    }

    // n >= avail: fill the new tail, relocate the old tail, then fill the gap
    uint extra = n - avail;
    if (extra != 0) {
        for (ushort* p = end; p != (ushort*)((char*)end + extra * 2); p = (ushort*)((char*)p + 2))
            *p = fill;
    }
    vec->m_end = (ushort*)((char*)end + extra * 2);
    memcpy(vec->m_end, pos, (int)((char*)end - (char*)pos));
    vec->m_end = (ushort*)((char*)vec->m_end + avail * 2);
    if (pos != end) {
        for (ushort* p = pos; p != end; p = (ushort*)((char*)p + 2))
            *p = fill;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006eca50
void __stdcall fca50(char* p1, char* p2)
{
    for (; p1 < p2; p1 += 0xc0) {
        int i = *(int*)(p1 + 4);
        if (((2 < (int)(*(int*)(p1 + 0xc) - i & 0xfffffffeU)) && (i != 0)) &&
            (i != *(int*)(p1 + 0x14)))
            f_f47380((void*)i);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ecdd0
void S8::mdd0(int a, int b)
{
    int loc[3];
    loc[0] = a; loc[1] = b; loc[2] = 0;
    VecC* v = (VecC*)((char*)this + 8);
    int* p = v->e;
    if (p < v->cap) {
        v->e = p + 3;
        if (p != 0) {
            p[0] = loc[0];
            p[1] = loc[1];
            p[2] = loc[2];
        }
        return;   // the shipped p==0 path still returns without growing
    }
    v->DoInsert(p, loc);
}

// ---------------------------------------------------------------------------
// @ 0x006ece30
void S8::me30(int a, int b, int c)
{
    int loc[3];
    loc[0] = a; loc[1] = b; loc[2] = c;
    VecC* v = (VecC*)((char*)this + 8);
    int* p = v->e;
    if (p < v->cap) {
        v->e = p + 3;
        if (p != 0) {
            p[0] = loc[0];
            p[1] = loc[1];
            p[2] = loc[2];
        }
        return;   // the shipped p==0 path still returns without growing
    }
    v->DoInsert(p, loc);
}

// ---------------------------------------------------------------------------
// @ 0x006ece90
void S8::me90(int n, int* a, int* b)
{
    char* self = (char*)this;
    while (n != 0) {
        int loc[3];
        loc[1] = *b;
        int* p = *(int**)(self + 0xc);
        loc[0] = *a;
        loc[2] = 0;
        n--;
        if (p < *(int**)(self + 0x10)) {
            *(int**)(self + 0xc) = p + 3;
            if (p != 0) {
                p[0] = loc[0]; p[1] = loc[1]; p[2] = 0;
            }
        } else {
            ((VecC*)(self + 8))->DoInsert(p, loc);
        }
        b++;
        a++;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ecf10
void S8::mf10()
{
    char* self = (char*)this;
    for (int i = 0; i < 0x28; i += 4) {
        int r = f_7c3af0(*(int*)(i + 0x1533cd0));
        VecC* v = (VecC*)(self + 0x30d54);
        int* p = v->e;
        if (p < v->cap) {
            v->e = p + 1;
            if (p)
                *p = r;
        } else {
            int loc = r;
            f_grow4(v, &loc);
        }
    }
    for (int i = 0; i < 0x28; i += 4) {
        int r = f_7c3af0(*(int*)(i + 0x1533ca8));
        VecC* v = (VecC*)(self + 0x30d68);
        int* p = v->e;
        if (p < v->cap) {
            v->e = p + 1;
            if (p)
                *p = r;
        } else {
            int loc = r;
            f_grow4(v, &loc);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ecfc0
S8* S8::mfc0(void* src)
{
    char* d = (char*)this;
    char* s = (char*)src;
    *(uchar*)d = *(uchar*)s;
    if (d + 4 != s + 4) {
        int* d4 = *(int**)(d + 4);
        int* d8 = *(int**)(d + 8);
        if (d4 != d8) {
            *(ushort*)d4 = 0;
            *(int**)(d + 8) = d4;
        }
        ((SmallStrObj*)(d + 4))->FUN_006ebd20(*(int*)(s + 4), *(int*)(s + 8));
    }
    *(float*)(d + 0x98) = *(float*)(s + 0x98);
    *(float*)(d + 0x9c) = *(float*)(s + 0x9c);
    *(uint*)(d + 0xa0) = *(uint*)(s + 0xa0);
    *(uint*)(d + 0xa4) = *(uint*)(s + 0xa4);
    *(float*)(d + 0xa8) = *(float*)(s + 0xa8);
    *(float*)(d + 0xac) = *(float*)(s + 0xac);
    *(uint*)(d + 0xb0) = *(uint*)(s + 0xb0);
    *(uint*)(d + 0xb4) = *(uint*)(s + 0xb4);
    *(uint*)(d + 0xb8) = *(uint*)(s + 0xb8);
    *(uint*)(d + 0xbc) = *(uint*)(s + 0xbc);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x006ed070
void S8::md070(int idx)
{
    ResTable* t = (ResTable*)this;

    if (idx < 0)
        return;
    if (idx >= (int)(t->m_end - t->m_begin))
        return;

    ResRec* rec = t->m_begin + idx;
    if (rec->m_i00 == 0)
        return;

    SharedHead* head28 = rec->m_p28;
    rec->m_i00 = 0;
    rec->m_b48 = 0;
    if (head28 != 0) {
        rec->m_p28 = 0;
        ReleaseShared(head28);
    }
    if (rec->m_p2C != 0) {
        SharedHead* head = rec->m_p2C;
        rec->m_p2C = 0;
        ReleaseShared(head);
    }
    if (rec->m_p6C != 0) {
        void* owned = rec->m_p6C;
        rec->m_p6C = 0;
        CallVtbl8(owned);
    }
    if (rec->m_p68 != 0) {
        void* mgr = t->m_resMgr;
        if (mgr != 0)
            ((void (__thiscall*)(void*, void*))VFN(mgr, 0x20))(mgr, (void*)rec->m_p68);
        rec->m_p68 = 0;
    }
    if (rec->m_p64 != 0) {
        f_f47380(rec->m_p64);
        rec->m_p64 = 0;
    }
    rec->m_i5C = 0;
    rec->m_list = 0;

    VecU32* freeList = &t->m_freeList;
    int* slot = freeList->e;
    if (slot < freeList->cap) {
        freeList->e = slot + 1;
        if (slot != 0)
            *slot = idx;
        return;
    }
    freeList->DoInsertValue(slot, &idx);
}

// ---------------------------------------------------------------------------
// @ 0x006ed1a0
void S8::md1a0(int idx, char v)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x4c) - *(int*)(self + 0x48)) / 0x70)
        return;
    int off = idx * 0x70;
    char* p = (char*)(*(int*)(self + 0x48) + 0x48 + off);
    if (*p != v) {
        *p = v;
        if (v != 0 && *(char*)(*(int*)(self + 0x48) + 0x49 + off) == 0) {
            int t = idx & 0xffff;
            ((VecU16*)(self + 0x5c))->FUN_006f66a0((const ushort*)&t);
            *(char*)(*(int*)(self + 0x48) + 0x49 + off) = 1;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006ed210
void S8::md210(int idx)
{
    char* self = (char*)this;
    if (idx < 0)
        return;
    if (idx >= (*(int*)(self + 0x178) - *(int*)(self + 0x174)) / 0x70)
        return;
    int off = idx * 0x70;
    char* e = (char*)(*(int*)(self + 0x174) + off);
    if (*(int*)e == 0)
        return;
    int v = *(int*)(e + 0x64);   // read before the clears, like the emitted code
    *(int*)e = 0;
    *(uchar*)(e + 0x48) = 0;
    if (v != 0) {
        void* h = *(void**)(self + 0x1e0);
        if (h)
            ((void(__thiscall*)(void*, int))VFN(h, 0x20))(h, v);
        *(int*)(e + 0x64) = 0;
    }
    VecU32* vv = (VecU32*)(self + 0x19c);
    int* p = vv->e;
    if (p < vv->cap) {
        vv->e = p + 1;
        if (p)
            *p = idx;
        return;   // the shipped p==0 path still returns without growing
    }
    int loc = idx;
    vv->DoInsertValue(p, &loc);
}
