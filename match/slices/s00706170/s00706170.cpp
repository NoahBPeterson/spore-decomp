// Slice s00706170 (batch w2g1, slice 36): lighting-config ctor/dtor,
// slot-vector iterators, EASTL vector allocation/copy helpers.
#include "types.h"
#include <xmmintrin.h>

void  sub_f47380(void*);                          // operator delete
void* sub_f473d0(int, int, int, const char*, int, int, const char*, int);
void* sub_f473a0(unsigned, const char*, int, int, int, int);
void  sub_705b50(void);                           // copy-ctor body (0x00705b50)
void  sub_e5c780(void);                           // rbtree find (0x00e5c780)

struct IVoid { virtual void v0(); virtual void v1(); };

// ==========================================================================
// @ 0x00706870
// ==========================================================================
struct W6870 {
    int* m0;
    int get(unsigned idx);
};
int W6870::get(unsigned idx)
{
    return m0[idx >> 7] + 0x10 + (idx & 0x7f) * 0x1f0;
}

// ==========================================================================
// @ 0x00706890
// ==========================================================================
struct W6890 {
    int* m0;
    int get(unsigned idx);
};
int W6890::get(unsigned idx)
{
    return m0[idx >> 7] + 4 + (idx & 0x7f) * 0x38;
}

// ==========================================================================
// @ 0x00706920 / 00706980 / 007069e0  slot-vector "next" scan
// ==========================================================================
struct W6920 {
    int** m0;
    unsigned next(unsigned idx);
};
unsigned W6920::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0xc4 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0xc4 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

struct W6980 {
    int** m0;
    unsigned next(unsigned idx);
};
unsigned W6980::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0x1f0 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0x1f0 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

struct W69e0 {
    int** m0;
    unsigned next(unsigned idx);
};
unsigned W69e0::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0x1e0 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0x1e0 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

// ==========================================================================
// @ 0x007067f0  SP::cLightingConfig::~cLightingConfig
// ==========================================================================
struct W67f0 {
    char pad0[0xa8];
    void* pA8;              // 0xa8
    char padAC[0x10];
    void* pBC;              // 0xbc
    ~W67f0();
};
W67f0::~W67f0()
{
    void* p = pBC;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        sub_f47380(p);
    p = pA8;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        sub_f47380(p);
    void* q = *(void**)this;
    if (q != 0)
        ((IVoid*)q)->v1();
}

// ==========================================================================
// @ 0x007068c0  copy the shading record plus its tail scalars
// ==========================================================================
struct W68c0 {
    char pad[0x1c0];
    float f1c0, f1c4, f1c8;
    int   f1cc, f1d0;
    W68c0* copyFrom(const W68c0* s);
};
W68c0* W68c0::copyFrom(const W68c0* s)
{
    ((void*(__thiscall*)(void*, const void*))&sub_705b50)(this, s);
    f1c0 = s->f1c0;
    f1c4 = s->f1c4;
    f1c8 = s->f1c8;
    f1cc = s->f1cc;
    f1d0 = s->f1d0;
    return this;
}

// ==========================================================================
// @ 0x00706ab0  forward copy of 16-byte elements keeping a pointer offset
// ==========================================================================
void FUN_00706ab0(__m128* first, __m128* last, __m128* out)
{
    if (first != last) {
        int offset = (int)((char*)first - (char*)out);
        do {
            if (out != 0)
                *(__m128*)out = *(__m128*)((char*)out + offset);
            out = (__m128*)((char*)out + 16);
        } while ((__m128*)((char*)out + offset) != last);
    }
}

// ==========================================================================
// @ 0x00706af0  allocate a vector of 0x20-byte elements
// ==========================================================================
struct Vec20 { void* b; void* e; void* c; Vec20* init(int n, int unused); };
Vec20* Vec20::init(int n, int unused)
{
    (void)unused;
    if (n != 0) {
        void* p = sub_f473d0(n << 5, 0x10, 0, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5);
        b = p;
        e = p;
        c = (char*)p + (n << 5);
    } else {
        b = 0; e = 0; c = 0;
    }
    return this;
}

// ==========================================================================
// @ 0x00706d00  allocate a vector of 0x10-byte elements
// ==========================================================================
struct Vec10 { void* b; void* e; void* c; Vec10* init(int n, int unused); };
Vec10* Vec10::init(int n, int unused)
{
    (void)unused;
    if (n != 0) {
        void* p = sub_f473d0(n << 4, 0x10, 0, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5);
        b = p;
        e = p;
        c = (char*)p + (n << 4);
    } else {
        b = 0; e = 0; c = 0;
    }
    return this;
}

// ==========================================================================
// @ 0x00706c80  forward copy of 9-dword elements (destination nullable)
// ==========================================================================
struct E9 { int a; float b, c, d, e, f, g, h, i; };
void FUN_00706c80(E9** out, E9* first, E9* last, E9* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0) {
                dst->a = first->a;
                dst->b = first->b;
                dst->c = first->c;
                dst->d = first->d;
                dst->e = first->e;
                dst->f = first->f;
                dst->g = first->g;
                dst->h = first->h;
                dst->i = first->i;
            }
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
}

// ==========================================================================
// @ 0x00706d60  run destructors over an array of 0x144-byte records
// ==========================================================================
struct E144 {
    void*  p0;              // 0x00
    char   pad04[0xa4];     // 0x04
    void*  pA8;             // 0xa8
    char   padAC[0x10];     // 0xac
    void*  pBC;             // 0xbc
};
int FUN_00706d60(E144* first, E144* last, int result)
{
    if (first == last)
        return result;
    do {
        void* p = first->pBC;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            sub_f47380(p);
        p = first->pA8;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            sub_f47380(p);
        if (first->p0 != 0)
            ((IVoid*)first->p0)->v1();
        first = (E144*)((char*)first + 0x144);
        result += 0x144;
    } while (first != last);
    return result;
}

// ==========================================================================
// @ 0x00706840  SP::cLightingManager::GetLightingWorld
// ==========================================================================
struct TreeFind { void find(void* result, void* key); };
struct W6840 {
    char pad0[0x2c];        // 0x00
    TreeFind tree;          // 0x2c  (rbtree with anchor at 0x30)
    int GetLightingWorld(int key);
};
int W6840::GetLightingWorld(int key)
{
    void* it;
    tree.find(&it, &key);
    if (it != (char*)this + 0x30)
        return *(int*)((char*)it + 0x14);
    return 0;
}

// ==========================================================================
// @ 0x00706170  PARTIAL: 1657-byte SP::cLightingWorld::UpdateEnvLightSample
// ==========================================================================
void FUN_00706170(void* self, void* a) { (void)self; (void)a; }

// ==========================================================================
// @ 0x00706b50  PARTIAL: vector push_back of 0xb0-byte records
// ==========================================================================
void FUN_00706b50(void* self, void* a) { (void)self; (void)a; }

// ==========================================================================
// @ 0x00706dd0  PARTIAL: 756-byte SP::cLightingConfig constructor
// ==========================================================================
void FUN_00706dd0(void* self) { (void)self; }
