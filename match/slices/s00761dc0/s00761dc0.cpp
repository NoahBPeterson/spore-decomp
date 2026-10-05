// Slice s00761dc0 : render/global-state helpers, hashtable wrappers and descriptor builders.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast region.
#include "types.h"
#include <new>

struct E8x { int a, b; E8x() {} E8x(int x, int y) : a(x), b(y) {} ~E8x(); };
struct D3 { E8x v[4]; };

extern "C" {
void* __cdecl operator_new(unsigned int size, const char* name, int a, int b, int c, int d);
void  __cdecl operator_delete_(void* p);
void* __cdecl FUN_00928a30(void* a, void* b, int c, int d, int e, int f, int g, int h);
void* __cdecl FUN_011fb220(void* p);
void* __cdecl FUN_011f3220(void* p);
void* __cdecl FUN_011f3580(void* p);
void* __cdecl FUN_011f4e90(void* p);
void* __cdecl FUN_011f3130(void* p);
void* __cdecl FUN_011f1120();
void* __cdecl FUN_011f51d0(void* p, ...);
void* __cdecl FUN_011f36d0(void* p, int a, int b, int c);
void* __cdecl FUN_011f5010(void* p, int a, int b, int c, int d, int e);
void* __cdecl FUN_006ddcc0(int a, int b, int c, int d);
void* __cdecl FUN_006ddd10(int a, void* b);
unsigned int __cdecl SP_ColorRGBAToU32(int a);
void* __cdecl VectorDescr(int n);   // @ 0x761650
}

namespace SP {
struct RefCountedAt8 {
    virtual void v0();
    virtual void v1();
};
struct Alloc16c8b44 {
    void  Free(void* p);
    void* allocate(int a, int b, int c, int d, int e, int f, int g, int h);
};
}
extern SP::Alloc16c8b44* g_alloc;

// ------------------------------------------------------------------- 0x761dc0
extern float g_16f8bec, g_16f8be0, g_16f8bfc, g_16f8bf0;
extern float g_16f8c0c, g_16f8c00, g_16f8c1c, g_16f8c10;
extern float g_16f8c70, g_16f8c74, g_16f8c78, g_16f8c7c;
extern float g_16f8be4, g_16f8bf4, g_16f8c04, g_16f8c14;
extern float g_16f8c80, g_16f8c84, g_16f8c88, g_16f8c8c;
extern float g_13eb1bc, g_1485720;
extern int g_15fd918, g_16fa5b8;
// @ 0x761dc0
void __cdecl FUN_00761dc0()
{
    if (*(int*)(*(int*)(g_15fd918 + 0x3c) + 0x110) != 0 && g_16fa5b8 != 0 &&
        *(int*)(g_16fa5b8 + 0x40) != 0) {
        float f1 = g_13eb1bc / (float)*(unsigned short*)(*(int*)(g_16fa5b8 + 0x40) + 0xc);
        float f2 = g_1485720 / (float)*(unsigned short*)(*(int*)(g_16fa5b8 + 0x40) + 0xe);
        g_16f8be0 = g_16f8bec * f1 + g_16f8be0;
        g_16f8c70 = g_16f8bec * f1 + g_16f8c70;
        g_16f8bf0 = g_16f8bfc * f1 + g_16f8bf0;
        g_16f8c74 = g_16f8bfc * f1 + g_16f8c74;
        g_16f8c00 = g_16f8c0c * f1 + g_16f8c00;
        g_16f8c78 = g_16f8c0c * f1 + g_16f8c78;
        g_16f8c10 = g_16f8c1c * f1 + g_16f8c10;
        g_16f8c7c = g_16f8c1c * f1 + g_16f8c7c;
        g_16f8be4 = g_16f8bec * f2 + g_16f8be4;
        g_16f8c80 = g_16f8bec * f2 + g_16f8c80;
        g_16f8bf4 = g_16f8bfc * f2 + g_16f8bf4;
        g_16f8c84 = g_16f8bfc * f2 + g_16f8c84;
        g_16f8c04 = g_16f8c0c * f2 + g_16f8c04;
        g_16f8c88 = g_16f8c0c * f2 + g_16f8c88;
        g_16f8c14 = g_16f8c1c * f2 + g_16f8c14;
        g_16f8c8c = g_16f8c1c * f2 + g_16f8c8c;
    }
}

// ------------------------------------------------------------------- 0x761f90
extern unsigned int g_16fa38c, g_16f9200, g_1485720b;
extern float g_16077c4, g_16077c8, g_13eb1bcb;
// @ 0x761f90  (partial: overlay/rect upload setup)
void __cdecl FUN_00761f90(int a, unsigned int color, int chunk)
{
    unsigned int saved = g_16f9200;
    g_16fa38c |= 2;
    g_16f9200 = 3;
    int i1 = (int)FUN_011f1120();
    unsigned short w = *(unsigned short*)(*(int*)(i1 + 0x40) + 0xc);
    int i2 = (int)FUN_011f1120();
    unsigned short h = *(unsigned short*)(*(int*)(i2 + 0x40) + 0xe);
    unsigned int rgba = SP_ColorRGBAToU32(color);
    float* out = 0;
    char b[4];
    if (FUN_006ddcc0(2, 4, (int)&out, (int)b)) {
        float fw = (float)w;
        float fh = (float)h;
        out[0] = -1.0f - (g_16077c4 * g_1485720b) / fw;
        out[1] = 0.0f;
        out[2] = -1.0f - (g_16077c8 * g_1485720b) / fh;
        out[6] = 1.0f - (g_16077c4 * g_1485720b) / fw;
        out[7] = 0.0f;
        out[8] = -1.0f - (g_16077c8 * g_1485720b) / fh;
        out[0xc] = 1.0f - (g_16077c4 * g_1485720b) / fw;
        out[0xd] = 0.0f;
        out[0xe] = 1.0f - (g_16077c8 * g_1485720b) / fh;
        out[0x12] = -1.0f - (g_16077c4 * g_1485720b) / fw;
        out[0x13] = 0.0f;
        out[0x14] = 1.0f - (g_16077c8 * g_1485720b) / fh;
        out[4] = 0.0f; out[5] = 1.0f;
        out[10] = 1.0f; out[0xb] = 1.0f;
        out[0x10] = 1.0f; out[0x11] = 0.0f;
        out[0x16] = 0.0f; out[0x17] = 0.0f;
        out[3] = (float)rgba; out[9] = (float)rgba;
        out[0xf] = (float)rgba; out[0x15] = (float)rgba;
        FUN_006ddd10(3, (void*)chunk);
    }
    g_16fa38c |= 2;
    g_16f9200 = saved;
}

// ----------------------------------------------------------- 0x762250 / 0x7622e0
extern void* g_vtA, *g_vtB, *g_vt13ef094, *g_vt13eb938;
struct Obj62250 {
    void* p0;                    // +0x0
    void* p1;                    // +0x4
    int   pad8;                  // +0x8
    int   data[14];              // +0xc .. +0x43
    SP::RefCountedAt8* ref;      // +0x44
    int   state;                 // +0x48
    Obj62250* ctor(const int* src, SP::RefCountedAt8* r);   // @ 0x762250
    void dtor();                                            // @ 0x7622e0
};
// @ 0x762250
Obj62250* Obj62250::ctor(const int* src, SP::RefCountedAt8* r)
{
    p1 = g_vt13ef094;
    pad8 = 0;
    p0 = g_vtA;
    p1 = g_vtB;
    for (int i = 0; i < 14; i++)
        data[i] = src[i];
    ref = r;
    if (r) r->v0();
    state = -1;
    return this;
}
// @ 0x7622e0
void Obj62250::dtor()
{
    p0 = g_vtA;
    p1 = g_vtB;
    if (ref == 0) {
        FUN_011fb220((void*)data[1]);
        g_alloc->Free((void*)data[1]);
    }
    if (ref) ref->v1();
    p1 = g_vt13ef094;
    p0 = g_vt13eb938;
}

// ------------------------------------------------------------------- 0x762380
struct Node2380 { unsigned int key; char pad[0x10 - 4]; };
struct Map2380 {
    char pad0[0x10];
    void* base;                  // +0x10
    char pad14[0x34];
    int cached;                  // +0x48
    int find();                  // @ 0x762380
};
// @ 0x762380
int Map2380::find()
{
    if (cached >= 0) return cached;
    unsigned int* a = *(unsigned int**)((char*)base + 0x34);
    int n = *(int*)(*(int*)((char*)base + 0x3c) + 8);
    unsigned int best = 0;
    unsigned int local = 0;
    if (n > 0) {
        do {
            unsigned int* p = a;
            unsigned int v = *p;
            if (v <= best) { local = v; p = &local; }
            else { local = v; }
            unsigned int v1 = p[1];
            unsigned int b;
            if (v1 <= local) { b = local; }
            else { b = v1; }
            local = b;
            unsigned int v2 = p[2];
            if (v2 <= b) { best = b; }
            else { best = v2; }
            local = best;
            a += 4;
            n--;
        } while (n != 0);
    }
    cached = (int)(best + 1);
    return (int)(best + 1);
}

// ------------------------------------------------------------------- 0x7623f0
D3 __cdecl FUN_00761300(int);   // forward (slice 25)
// @ 0x7623f0
int __cdecl FUN_007623f0(int a, int b, int c, int d, int e, int f)
{
    D3 d3 = FUN_00761300(0);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d3.v[0].a, (void*)d3.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    int o = (int)FUN_011f3220(local);
    *(int*)(o + 0x20) = a;
    *(int*)(o + 0x24) = b;
    *(int*)(o + 0x28) = c;
    *(int*)(o + 0x2c) = a;
    *(int*)(o + 0x10) = d;
    *(int*)(o + 0x14) = e;
    *(int*)(o + 0x18) = f;
    return o;
}

// ------------------------------------------------------------------- 0x7624c0
extern float g_1538fe8b, g_140de58b;
// @ 0x7624c0
int __cdecl FUN_007624c0(int a, int b, int c, int d, int e, int f, float p7)
{
    D3 d3 = FUN_00761300(1);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d3.v[0].a, (void*)d3.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    int o = (int)FUN_011f3220(local);
    *(int*)(o + 0x30) = a;
    *(int*)(o + 0x34) = b;
    *(int*)(o + 0x38) = c;
    *(int*)(o + 0x3c) = a;
    *(int*)(o + 0x10) = d;
    *(int*)(o + 0x14) = e;
    *(int*)(o + 0x18) = f;
    if (p7 > g_1538fe8b) {
        *(float*)(o + 4) = p7;
        *(float*)(o + 8) = g_140de58b / p7;
    } else {
        *(float*)(o + 4) = 0.0f;
        *(float*)(o + 8) = g_140de58b;
    }
    return o;
}

// ------------------------------------------------------------------- 0x7625d0
// @ 0x7625d0  (partial: vertex-declaration parser, jump tables approximated)
void* __cdecl FUN_007625d0(const char* s)
{
    int n = 0;
    const char* p = s;
    while (*p) p++;
    n = (int)(p - (s + 1)) / 3;
    struct Ent { short a; unsigned char b; unsigned char c; int d; } ents[32];
    int count = 0;
    for (int i = 0; i < n; i++) {
        const char* q = s + 1 + i * 3;
        char c0 = q[-1];
        if (c0 == 'S' && q[0] == 'T' && q[1] == 'R') continue;
        ents[count].a = 0;
        ents[count].b = q[0];
        ents[count].c = 0;
        ents[count].d = 0;
        count++;
    }
    void* desc = VectorDescr(count);
    if (desc) {
        *(unsigned char*)((char*)desc + 0xe) |= 2;
        char* dst = (char*)desc + 0x18;
        for (int i = 0; i < count; i++) {
            dst[0] = (char)ents[i].a;
            dst[1] = (char)(ents[i].a >> 8);
            dst[4] = ents[i].b;
            *(int*)(dst + 8) = ents[i].d;
            dst += 0xc;
        }
        FUN_011f3220(desc);
    }
    return desc;
}

// ------------------------------------------------------------------- 0x762890
struct Map262890 {
    char pad0[4];
    void* buckets;               // +0x4
    unsigned int bucketCount;    // +0x8
    unsigned int count;          // +0xc
    int erase(unsigned int* key);   // @ 0x762890
};
// @ 0x762890
int Map262890::erase(unsigned int* key)
{
    unsigned int before = count;
    unsigned int b = *key % bucketCount;
    unsigned int* slot = (unsigned int*)((char*)buckets + b * 4);
    if (*slot != 0) {
        unsigned int* e;
        do {
            e = (unsigned int*)*slot;
            if (*key == *e) break;
            slot = e + 4;
        } while (e[4] != 0);
        while (*slot != 0 && *key == **(unsigned int**)slot) {
            unsigned int* cur = (unsigned int*)*slot;
            *slot = cur[4];
            operator_delete_(cur);
            count--;
        }
    }
    return (int)(before - count);
}

// ------------------------------------------------------------------- 0x762900
struct Map262900 {
    char pad0[4];
    unsigned int* buckets;       // +0x4
    unsigned int bucketCount;    // +0x8
    unsigned int count;          // +0xc
    void insert(void* outIter, unsigned int* key);   // @ 0x762900
};
// @ 0x762900
void Map262900::insert(void* outIter, unsigned int* key)
{
    unsigned int k = *key;
    unsigned int b = k % bucketCount;
    unsigned int* slot = (unsigned int*)((char*)buckets + b * 4);
    unsigned int* e = (unsigned int*)*slot;
    while (true) {
        if (e == 0) {
            unsigned int* node = (unsigned int*)operator_new(0x14, "Graphics", 0, 0, 0, 0);
            if (node) {
                node[0] = key[0]; node[1] = key[1]; node[2] = key[2]; node[3] = key[3];
            }
            node[4] = *(unsigned int*)((char*)buckets + b * 4);
            *(unsigned int**)((char*)buckets + b * 4) = node;
            count++;
            *(unsigned int**)outIter = node;
            *((unsigned char*)outIter + 8) = 1;
            *(unsigned int**)((char*)outIter + 4) = (unsigned int*)((char*)buckets + b * 4);
            return;
        }
        if (k == *e) break;
        e = (unsigned int*)e[4];
    }
    *(unsigned int**)outIter = e;
    *((unsigned char*)outIter + 8) = 0;
    *(unsigned int**)((char*)outIter + 4) = slot;
}

// ------------------------------------------------------------------- 0x762a00/2a30
extern Map262890 g_map1538ff0;
extern Map262890 g_map1539010;
// @ 0x762a00
void __cdecl FUN_00762a00(void* p)
{
    unsigned int key = (unsigned int)p;
    g_map1538ff0.erase(&key);
    FUN_011f3580(p);
    g_alloc->Free(p);
}
// @ 0x762a30
void __cdecl FUN_00762a30(void* p)
{
    unsigned int key = (unsigned int)p;
    g_map1539010.erase(&key);
    FUN_011f4e90(p);
    g_alloc->Free(p);
}

// ------------------------------------------------------------------- 0x762a60
// @ 0x762a60  (partial: nested map cleanup)
void __cdecl FUN_00762a60(void* p, int n)
{
    if (n > 0) {
        void** it = (void**)((char*)p + 0x24);
        do {
            void* q = *it;
            void* r = *(void**)q;
            FUN_011f3130(r);
            g_alloc->Free(r);
            unsigned int key = (unsigned int)q;
            g_map1538ff0.erase(&key);
            FUN_011f3580(q);
            g_alloc->Free(q);
            it++;
            n--;
        } while (n != 0);
    }
}

// ------------------------------------------------------------------- 0x762b00
struct Hash262b00 {
    char pad0[4];
    void* buckets;
    unsigned int bucketCount;
    int findInsert(unsigned int* key);   // @ 0x762b00
};
// @ 0x762b00
int Hash262b00::findInsert(unsigned int* key)
{
    int it[3];
    // eastl hashtable find (external) - write a local sentinel
    it[0] = 0;
    if (it[0] == *(int*)((char*)buckets + bucketCount * 4)) {
        unsigned int k = *key;
        unsigned int loc[4] = { k, 0, 0, 0 };
        ((Map262900*)((char*)this + 4))->insert(it, loc);
    }
    return it[0] + 4;
}

// ------------------------------------------------------------------- 0x762b70 / 0x762c60
// @ 0x762b70
void* __cdecl FUN_00762b70(int a, int b, int c, void* out)
{
    int desc[8];
    FUN_011f51d0(desc, a, b, c);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)desc[0], (void*)desc[4], 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    void* r = FUN_011f36d0(local, a, b, c);
    void* src = out ? out : 0;
    Hash262b00* h = (Hash262b00*)0x1538ff0;
    int* slot = (int*)h->findInsert((unsigned int*)&r);
    if (src) {
        slot[0] = ((int*)src)[0];
        slot[1] = ((int*)src)[1];
        slot[2] = ((int*)src)[2];
    }
    return r;
}
// @ 0x762c60
void* __cdecl FUN_00762c60(int a, int b, int c, int d, int e, void* out)
{
    int desc[8];
    FUN_011f51d0(desc, a, b, c, d, e);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)desc[0], (void*)desc[4], 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    void* r = FUN_011f5010(local, a, b, c, d, e);
    void* src = out ? out : 0;
    Hash262b00* h = (Hash262b00*)0x1539010;
    int* slot = (int*)h->findInsert((unsigned int*)&r);
    if (src) {
        slot[0] = ((int*)src)[0];
        slot[1] = ((int*)src)[1];
        slot[2] = ((int*)src)[2];
    }
    return r;
}
