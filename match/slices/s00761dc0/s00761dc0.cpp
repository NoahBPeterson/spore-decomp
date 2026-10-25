// Slice s00761dc0 : render/global-state helpers, hashtable wrappers and descriptor builders.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast region.
#include "types.h"
#include <new>
#include <xmmintrin.h>

struct E8x { int a, b; E8x() {} E8x(int x, int y) : a(x), b(y) {} ~E8x(); };
struct D3 { E8x v[4]; };

extern "C" {
void* __cdecl operator_new(unsigned int size, const char* name, int a, int b, int c, int d);
void  __cdecl operator_delete_(void* p);
void* __cdecl FUN_00928a30(void* a, void* b, int c, int d, int e, int f, int g, int h);
void* __cdecl FUN_011fb220(void* p);
void* __cdecl FUN_011f3220(void* p);
void* __cdecl FUN_011f1120();
void* __cdecl FUN_011f51d0(void* p, ...);
void* __cdecl FUN_011f36d0(void* p, int a, int b, int c);
void* __cdecl FUN_011f5010(void* p, int a, int b, int c, int d, int e);
void* __cdecl FUN_006ddcc0(int a, int b, int c, int d);
void* __cdecl FUN_006ddd10(int a, void* b);
unsigned int __cdecl SP_ColorRGBAToU32(int a);
void* __cdecl VectorDescr(int n);   // @ 0x761650
}

// Release helpers the original invokes with the pointer in ecx (__fastcall first arg).
void __fastcall FUN_011f3580(void* p);  // 0x011f3580
void __fastcall FUN_011f4e90(void* p);  // 0x011f4e90
void __fastcall FUN_011f3130(void* p);  // 0x011f3130

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
extern float g_neg1;         // 0x013eb1bc  == -1.0f
extern float g_two;          // 0x01470f1c  ==  2.0f
extern float g_one;          // 0x01485720  ==  1.0f
// @ 0x761f90  overlay/rect upload setup: build the 4-vertex xy/uv/colour block and submit it
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
    (void)a;
    float* out = 0;
    char b[4];
    if (FUN_006ddcc0(2, 4, (int)&out, (int)b)) {
        float fw = (float)w;
        float fh = (float)h;
        float fc;
        *(unsigned int*)&fc = rgba;
        float dx = (g_16077c4 * g_two) / fw;
        float dy = (g_16077c8 * g_two) / fh;
        out[0]  = g_neg1 - dx;   out[1]  = 0.0f;      out[2]  = g_neg1 - dy;
        out[4]  = 0.0f;          out[5]  = g_one;      out[6]  = g_one - dx;
        out[7]  = 0.0f;          out[8]  = g_neg1 - dy;
        out[0xc] = g_one - dx;   out[0xd] = 0.0f;      out[0xe] = g_one - dy;
        out[0x12] = g_neg1 - dx; out[0x13] = 0.0f;     out[0x14] = g_one - dy;
        out[0x10] = g_one;       out[0x11] = 0.0f;     out[0x16] = 0.0f;
        out[0x17] = 0.0f;        out[10]  = g_one;     out[0xb]  = g_one;
        out[3]  = fc;            out[9]   = fc;
        out[0xf] = fc;           out[0x15] = fc;
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
    void* b = base;
    int n = *(int*)(*(int*)((char*)b + 0x3c) + 8);
    unsigned int* a = *(unsigned int**)((char*)b + 0x34);
    unsigned int local = 0;
    unsigned int* pl = &local;
    if (n > 0) {
        do {
            unsigned int* p;
            if (*pl < a[0]) p = &a[0]; else p = pl;
            *pl = *p;
            if (*pl < a[1]) p = &a[1]; else p = pl;
            *pl = *p;
            if (*pl < a[2]) p = &a[2]; else p = pl;
            *pl = *p;
            a += 4;
        } while (--n != 0);
    }
    cached = (int)(*pl + 1);
    return cached;
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
extern void* __cdecl FUN_011fa2d0(void* out, int one);   // 0x011fa2d0 MeshCompiledStateLinkCreate
// @ 0x7624c0  varyings/descriptor builder (first three args are floats; 7th is a scale)
int __cdecl FUN_007624c0(float a, float b, float c, int d, int e, int f, float p7)
{
    D3 d3 = FUN_00761300(1);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)d3.v[0].a, (void*)d3.v[0].b, 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    int o = (int)FUN_011fa2d0(local, 1);
    // {a, c, b, a} packed as one 16-byte store at +0x30.
    __m128 packed;
    packed = _mm_set_ps(a, b, c, a);
    _mm_storeu_ps((float*)(o + 0x30), packed);
    *(int*)(o + 0x10) = d;
    *(int*)(o + 0x14) = e;
    *(int*)(o + 0x18) = f;
    if (p7 > g_1538fe8b) {
        *(float*)(o + 4) = p7;
        *(float*)(o + 8) = 1.0f / p7;
    } else {
        *(float*)(o + 4) = 0.0f;
        *(float*)(o + 8) = g_140de58b;
    }
    return o;
}

// ------------------------------------------------------------------- 0x7625d0
// Vertex-declaration string parser "SemanticStreamType" triples -> VertexDescription.
// @ 0x7625d0
void* __cdecl FUN_007625d0(const char* s)
{
    struct Ent { short semantic; char type; char pad5; char pad6; char pad7; int value; };
    Ent ents[32];

    const char* p = s;
    do { } while (*p++);
    int n = (int)(p - (s + 1)) / 3;      // number of 3-char groups
    int count = 0;
    int idxTag = n;                      // +0 field tag: starts at n, ++ per STR triple
    int tIndex = 0;                      // T/t value counter
    int cRun = 0;                        // C/c run counter
    if (n > 0) {
        p = s + 1;
        Ent* e = ents;
        do {
            char c = p[-1];
            if (c == 'S' && p[0] == 'T' && p[1] == 'R') {
                ++idxTag;
            } else {
                bool bT = false, bC = false, bV = false, bW = false;
                if (c == 'T' || c == 't') {
                    bT = true;
                    if (p[0] == '0') {
                        ++tIndex;
                        goto next;
                    }
                }
                ++count;
                e->semantic = (short)idxTag;
                e->type = 0;
                e->value = 0;
                switch (c) {
                case 'B': case 'b': e->value = 0x14; break;
                case 'C': case 'c': bC = true; e->value = (cRun != 0 ? 1 : 0) * 2 + 3; ++cRun; break;
                case 'G': case 'g': e->value = 0x13; break;
                case 'I': case 'i': e->value = 0xe;  break;
                case 'N': case 'n': e->value = 2;    break;
                case 'P': case 'p': e->value = 0x10; break;
                case 'T': case 't': e->value = tIndex; ++tIndex; break;
                case 'V': case 'v': e->value = 0;    bV = true; break;
                case 'W': case 'w': e->value = 0xf;  bW = true; break;
                default: break;
                }
                switch (p[1]) {
                case 'B': case 'b':
                    if (bW)          e->type = 8;
                    else if (bC || bT || bV) e->type = 4;
                    else             e->type = 5;
                    break;
                case 'F': case 'f': e->type = (char)(p[0] - 0x31); break;
                case 'S': case 's': e->type = (char)((p[0] != '2') + 6); break;
                default: break;
                }
            }
next:
            p += 3;
            ++e;
        } while (--n != 0);
    }

    void* desc = VectorDescr(count);
    if (desc) {
        *(unsigned char*)((char*)desc + 0xe) |= 2;
        char* dst = (char*)desc + 0x18;
        for (int i = 0; i < count; i++) {
            *(short*)(dst + 0) = ents[i].semantic;
            dst[4] = ents[i].type;
            *(int*)(dst + 8) = ents[i].value;
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
extern void __cdecl FUN_00921440(void* out, unsigned int bucketCount, unsigned int count, int one); // 0x00921440
extern void __cdecl FUN_006f1ab0(unsigned int newBucketCount);                   // 0x006f1ab0
extern void* __cdecl FUN_00f473a0(unsigned int size, const char* name, int f, int df, const char* file, int line);

const char kEastlAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

struct Map262900 {
    char pad0[4];
    unsigned int* buckets;       // +0x4
    unsigned int bucketCount;    // +0x8
    unsigned int count;          // +0xc
    char pad10[4];
    // rehash policy object at +0x10 (its PrepareRehash writes the new bucket count)
    void insert(void* outIter, const unsigned int* hashKey, const unsigned int* payload);   // @ 0x762900
};
// @ 0x762900  eastl hashtable bucket insert (with optional rehash first)
void Map262900::insert(void* outIter, const unsigned int* hashKey, const unsigned int* payload)
{
    unsigned int key = hashKey[0];
    unsigned int b = key % bucketCount;
    unsigned int* slot = (unsigned int*)((char*)buckets + b * 4);
    unsigned int* e = (unsigned int*)*slot;
    while (e) {
        if (key == *e) {
            *(unsigned int**)outIter = e;
            *((unsigned char*)outIter + 8) = 0;
            *(unsigned int**)((char*)outIter + 4) = slot;
            return;
        }
        e = (unsigned int*)e[4];
    }

    // No existing node: let the policy grow the table if needed, then allocate.
    unsigned char didRehash = 0;
    unsigned int newBucketCount = 0;
    FUN_00921440(&didRehash, bucketCount, count, 1);
    unsigned int* node = (unsigned int*)FUN_00f473a0(0x14, "Graphics", 0, 0, kEastlAllocFile, 0xd1);
    if (node) {
        node[0] = payload[0];
        node[1] = payload[1];
        node[2] = payload[2];
        node[3] = payload[3];
    }
    node[4] = 0;
    if (didRehash) {
        b = key % newBucketCount;
        FUN_006f1ab0(newBucketCount);
    }
    slot = (unsigned int*)((char*)buckets + b * 4);
    node[4] = *slot;
    *slot = (unsigned int)node;
    ++count;
    *(unsigned int**)outIter = node;
    *((unsigned char*)outIter + 8) = 1;
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
// @ 0x762a60  nested map cleanup: free each element of the n+0x24 vector, then the entry and n
// (plain __cdecl with one stack argument; the entry `push ecx` only reserves a local)
void __cdecl FUN_00762a60(void* n)
{
    int count = *(int*)((char*)n + 0x10);
    if (count > 0) {
        void** it = (void**)((char*)n + 0x24);
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
        } while (--count != 0);
    }
    void* tail = *(void**)((char*)n + 8);
    unsigned int key2 = (unsigned int)tail;
    g_map1539010.erase(&key2);
    FUN_011f4e90(tail);
    g_alloc->Free(tail);
    g_alloc->Free((void*)n);
}

// ------------------------------------------------------------------- 0x762b00
struct Iter { void* node; void* bucket; unsigned char inserted; char pad[3]; };   // eastl hashtable iterator
struct Hash262b00 {
    char pad0[4];
    void* buckets;               // +0x04
    unsigned int bucketCount;    // +0x08
    void find(Iter* out, const void* key);   // 0x00db4780
    int findInsert(unsigned int* key);       // @ 0x762b00
};
// @ 0x762b00
int Hash262b00::findInsert(unsigned int* key)
{
    Iter it;
    find(&it, key);
    if (it.node == *(void**)((char*)buckets + bucketCount * 4)) {
        unsigned int pair[4] = { 0, 0, 0, 0 };
        pair[0] = *key;
        ((Map262900*)this)->insert(&it, pair, pair);
    }
    return (int)(char*)it.node + 4;
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
    int zeroKey[3] = { 0, 0, 0 };
    int* src = out ? (int*)out : zeroKey;
    Hash262b00* h = (Hash262b00*)0x1538ff0;
    int* slot = (int*)h->findInsert((unsigned int*)&r);
    slot[0] = src[0];
    slot[1] = src[1];
    slot[2] = src[2];
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
    int zeroKey[3] = { 0, 0, 0 };
    int* src = out ? (int*)out : zeroKey;
    Hash262b00* h = (Hash262b00*)0x1539010;
    int* slot = (int*)h->findInsert((unsigned int*)&r);
    slot[0] = src[0];
    slot[1] = src[1];
    slot[2] = src[2];
    return r;
}
