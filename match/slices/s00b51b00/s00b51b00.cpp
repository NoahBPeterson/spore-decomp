// Slice s00b51b00: eastl hashtable / resource-cache internals (MSVC 2008 SP1, /O2).
#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ---------------------------------------------------------------------------
// dummy-virtual macros: `struct Vn { G(n-1) virtual R m(...); };` puts m at
// vtable byte offset n*4.
// ---------------------------------------------------------------------------
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
#define G44 G43 virtual void z44();
#define G45 G44 virtual void z45();
#define G46 G45 virtual void z46();
#define G47 G46 virtual void z47();
#define G48 G47 virtual void z48();
#define G49 G48 virtual void z49();
#define G50 G49 virtual void z50();

// vtable slots used by slice-102 callers
struct V10 { G9  virtual float* f2c(); };          // slot 11 (0x2c)
struct V30 { G11 virtual float* f30(); };          // slot 12 (0x30)
struct V38 { G13 virtual void   f38(void*); };     // slot 14 (0x38)
struct V3C { G14 virtual void   f3c(void*); };     // slot 15 (0x3c)
struct VB8 { G45 virtual int    fB8(u32); };       // slot 46 (0xb8)
struct VOB { G2  virtual void   f0c(void*, float, void*); }; // slot 3 (0xc)

// ---------------------------------------------------------------------------
// external (unresolved) callees; hex-names are resolved by tools/difftest.
// ---------------------------------------------------------------------------
struct Ext {
    void  FUN_00921260(u32, u32, u32, u32, u32);   // eastl::fixed_pool_base::init
    u32   FUN_00921360(u32);
    void  FUN_00921440(void*, u32, u32, u32);
    u32   FUN_00c763d0(u32);
    int*  FUN_00b51780(void*, u32);
    void  FUN_00833840(void*, void*);
    void  FUN_00645ed0(void*, void*);
    void  FUN_00b4f930(void*, void*, void*);
    void  FUN_00b4f8a0(void*, void*, void*);
    u32   FUN_00b576d0(void*);
    void  FUN_00b4fbd0(u32);
    void  FUN_007611f0(void*, u32);
    void  FUN_00c41d60(void*);
};

struct Body {
    void FUN_01087820(void*);
    void FUN_01087840(void*);
    void FUN_0108dde0(void*);
};

void __cdecl FUN_00f47380(void*);
int* __cdecl FUN_00b51e30(int*, unsigned);
void __cdecl FUN_00b51e80(unsigned, float);
void __cdecl FUN_00b51040(void*, float);
void __cdecl FUN_00b520a0();
int  __cdecl FUN_00b521f0(void*);
unsigned __cdecl FUN_00b52230(void*, void*);
void __cdecl FUN_00b523e0(void*, void*);
char __cdecl FUN_0059ab70(void*);
void __cdecl FUN_00b4dfe0(void*, void*, void*);
void __cdecl FUN_00b4e0c0(void*, void*, void*);
void __cdecl FUN_00b54000(void*, void*);

// ---------------------------------------------------------------------------
// The object model shared by these helpers.  `Big` is used both for the node
// tables (buckets at +4, count at +8, size at +0xc) and for the larger owner
// object whose embedded table sits at +0x1858.
// ---------------------------------------------------------------------------
struct Big {
    int   M_b51b00(unsigned a0, int a1, int a2, int a3, int a4, int a5, int* a6);
    void** M_b51bb0(void** out, int* key);
    int   M_b51c20(int* key);
    int** M_b51cc0(int** out, int* node, int** slot);
    void  M_b51d50(float dt);
    void  M_b51df0(unsigned a, unsigned b);
    void  M_b51ee0();
    void  M_b52020(int* p);
    void  M_b52120(int** out, int* key, int* extra);
    u32   FUN_00c763d0(u32);
};

// ---------------------------------------------------------------------------
// @ 0x00B51B00
// ---------------------------------------------------------------------------
int Big::M_b51b00(unsigned a0, int a1, int a2, int a3, int a4, int a5, int* a6)
{
    char* self = (char*)this;
    unsigned n = (unsigned)a6[0];

    *(int*)(self + 8) = 0;
    *(int*)(self + 0xc) = 0;
    *(float*)(self + 0x10) = 1.0f;
    *(float*)(self + 0x14) = *(float*)0x1470f1c;
    *(int*)(self + 0x18) = 0;

    *(int*)(self + 0x1c) = 0;
    ((Ext*)(self + 0x1c))->FUN_00921260(n, 0x80, 0x10, 4, 0);
    *(unsigned*)(self + 0x24) = n;
    *(unsigned*)(self + 0x28) = n + 0x80;
    *(int*)(self + 0x2c) = 0x10;
    *(int*)(self + 0x30) = a6[5];

    if (a0 < 2) {
        *(int*)(self + 0xc) = 0;
        *(int*)(self + 0x18) = 0;
        *(int*)(self + 8) = 1;
        *(unsigned*)(self + 4) = 0x154df28u;
        return (int)(size_t)this;
    }

    unsigned u = ((Ext*)(self + 0x10))->FUN_00921360(a0);
    *(unsigned*)(self + 8) = u;
    u = FUN_00c763d0(u);
    *(unsigned*)(self + 4) = u;
    return (int)(size_t)this;
}

// ---------------------------------------------------------------------------
// @ 0x00B51BB0
// ---------------------------------------------------------------------------
void** Big::M_b51bb0(void** out, int* key)
{
    char* self = (char*)this;
    int** buckets = *(int***)(self + 4);
    unsigned nBucket = *(unsigned*)(self + 8);

    unsigned idx = (unsigned)(key[0] + key[1]) % nBucket;
    int** slot = &buckets[idx];
    int* node = *slot;
    for (; node != 0; node = *(int**)((char*)node + 0xc)) {
        if (key[0] == node[0] && key[1] == node[1])
            break;
    }
    if (node == 0) {
        slot = &buckets[nBucket];
        node = *slot;
    }
    out[0] = node;
    out[1] = slot;
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00B51C20
// ---------------------------------------------------------------------------
int Big::M_b51c20(int* key)
{
    char* self = (char*)this;
    int** buckets = *(int***)(self + 4);
    unsigned nBucket = *(unsigned*)(self + 8);
    int cnt0 = *(int*)(self + 0xc);
    int* sentinel = *(int**)(self + 0x30);

    unsigned idx = (unsigned)(key[0] + key[1]) % nBucket;
    int** slot = &buckets[idx];

    if (*slot != 0) {
        int* node = *slot;
        while (node != 0 && !(key[0] == node[0] && key[1] == node[1])) {
            slot = (int**)((char*)node + 0xc);
            node = *slot;
        }
        while (*slot != 0) {
            node = *slot;
            if (key[0] != node[0] || key[1] != node[1])
                break;
            *slot = *(int**)((char*)node + 0xc);
            if (node != sentinel) {
                if (node < *(int**)(self + 0x24) || node >= *(int**)(self + 0x28)) {
                    FUN_00f47380(node);
                } else {
                    node[0] = *(int*)(self + 0x1c);
                    *(int**)(self + 0x1c) = node;
                }
            }
            (*(int*)(self + 0xc))--;
        }
    }
    return cnt0 - *(int*)(self + 0xc);
}

// ---------------------------------------------------------------------------
// @ 0x00B51CC0
// ---------------------------------------------------------------------------
int** Big::M_b51cc0(int** out, int* node, int** slot)
{
    char* self = (char*)this;
    int* sentinel = *(int**)(self + 0x30);

    int* nxt = *(int**)((char*)node + 0xc);
    out[1] = (int*)slot;
    out[0] = nxt;
    while (nxt == 0) {
        slot++;
        nxt = *slot;
        out[0] = nxt;
    }

    if (*slot == node) {
        *slot = *(int**)((char*)node + 0xc);
    } else {
        int* prev = *slot;
        int* cur = *(int**)((char*)prev + 0xc);
        while (cur != node) {
            prev = cur;
            cur = *(int**)((char*)cur + 0xc);
        }
        *(int**)((char*)prev + 0xc) = *(int**)((char*)cur + 0xc);
    }

    if (node != sentinel) {
        if (node < *(int**)(self + 0x24) || node >= *(int**)(self + 0x28)) {
            FUN_00f47380(node);
        } else {
            node[0] = *(int*)(self + 0x1c);
            *(int**)(self + 0x1c) = node;
        }
    }
    (*(int*)(self + 0xc))--;
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00B51D50
// ---------------------------------------------------------------------------
void Big::M_b51d50(float dt)
{
    char* self = (char*)this;
    Big* t = (Big*)(self + 0x1858);

    int** buckets = *(int***)(self + 0x185c);
    unsigned nBucket = *(unsigned*)(self + 0x1860);

    int** pi = buckets;
    int* node = *pi;
    if (node == 0) {
        do {
            pi++;
            node = *pi;
        } while (node == 0);
    }
    int* end = *(int**)((char*)buckets + nBucket * 4);

    while (node != end) {
        float v = *(float*)((char*)node + 8) - dt;
        *(float*)((char*)node + 8) = v;
        if (0.0f < v) {
            node = *(int**)((char*)node + 0xc);
            while (node == 0) {
                pi++;
                node = *pi;
            }
        } else {
            int* r[2];
            t->M_b51cc0((int**)r, node, pi);
            node = r[0];
            pi = (int**)r[1];
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B51DF0
// ---------------------------------------------------------------------------
void Big::M_b51df0(unsigned a, unsigned b)
{
    char* self = (char*)this;
    Big* t = (Big*)(self + 0x1858);

    unsigned lo = a, hi = b;
    if (b < a) {
        lo = b;
        hi = a;
    }
    int pair[2];
    pair[0] = (int)lo;
    pair[1] = (int)hi;
    t->M_b51c20(pair);
}

// ---------------------------------------------------------------------------
// @ 0x00B51E30
// ---------------------------------------------------------------------------
int* __cdecl FUN_00b51e30(int* out, unsigned a)
{
    int local[4];
    int* p = ((Ext*)0x1569c98)->FUN_00b51780(local, a);
    out[0] = p[0];
    out[1] = p[1];
    out[2] = p[2];
    out[3] = p[3];
    out[4] = 0;
    out[5] = 0;
    out[4] = out[0];
    out[5] = out[1];
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00B51E80
// ---------------------------------------------------------------------------
void __cdecl FUN_00b51e80(unsigned a1, float a2)
{
    int local[4];
    int* p = ((Ext*)0x1569c98)->FUN_00b51780(local, a1);
    int s[6];
    s[0] = p[0];
    s[1] = p[1];
    s[2] = p[2];
    s[3] = p[3];
    s[4] = s[0];
    s[5] = s[1];
    FUN_00b51040(s, a2);
}

// ---------------------------------------------------------------------------
// @ 0x00B51EE0
// ---------------------------------------------------------------------------
void Big::M_b51ee0()
{
    char* self = (char*)this;
    int* p18 = *(int**)(self + 0x18);
    int* ref;
    short s;

    if (p18 != 0) {
        ref = p18;
        s = *(short*)((char*)p18 + 6);
    } else {
        ref = *(int**)(self + 0xc);
        s = (ref == 0) ? 0 : *(short*)((char*)ref + 6);
    }
    bool last = (s == 1);

    if (p18 != 0) {
        if (*(short*)((char*)p18 + 4) != 0) {
            (*(short*)((char*)p18 + 6))--;
            if (*(short*)((char*)p18 + 6) == 0) {
                void** vt = *(void***)p18;
                ((void(__thiscall*)(int*, int))vt[0])(p18, 1);
            }
        }
        if (last) {
            *(int**)(self + 0x18) = 0;
            *(int**)(self + 0xc) = 0;
        }
    } else {
        int* p0c = *(int**)(self + 0xc);
        if (*(short*)((char*)p0c + 4) != 0) {
            (*(short*)((char*)p0c + 6))--;
            if (*(short*)((char*)p0c + 6) == 0) {
                void** vt = *(void***)p0c;
                ((void(__thiscall*)(int*, int))vt[0])(p0c, 1);
            }
        }
        if (last)
            *(int**)(self + 0xc) = 0;
    }

    int* p70 = *(int**)(self + 0x70);
    if (p70 != 0) {
        int* r18 = *(int**)((char*)p70 + 0x18);
        short s2;
        if (r18 != 0) {
            s2 = *(short*)((char*)r18 + 6);
        } else {
            int* r0c = *(int**)((char*)p70 + 0xc);
            s2 = (r0c == 0) ? 0 : *(short*)((char*)r0c + 6);
        }
        ((Big*)p70)->M_b51ee0();
        if (s2 == 1)
            *(int**)(self + 0x70) = 0;
    }

    if (last) {
        int it[6];
        FUN_00b51e30(it, (unsigned)(size_t)this);
        int* node = (int*)it[4];
        int* end = (int*)it[2];
        int* slot = (int*)it[3];
        while (*(float*)((char*)node + 0x20) != *(float*)(self + 0x10)) {
            node = *(int**)((char*)node + 0x90);
            while (node == 0) {
                slot++;
                node = (int*)*slot;
            }
            if (node == end)
                return;
        }
        if (node != end && *(float*)((char*)node + 0x20) == *(float*)(self + 0x10))
            ((Ext*)0x1569c98)->FUN_00b4f8a0(it, node, slot);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B52020
// ---------------------------------------------------------------------------
void Big::M_b52020(int* p)
{
    int it[2];
    int key[2];
    key[0] = p[0];
    key[1] = 0;

    ((Ext*)0x1569cb8)->FUN_00833840(it, key);

    int base = *(int*)0x1569cbc;
    int count = *(int*)0x1569cc0;
    if (it[0] != *(int*)(base + count * 4)) {
        ((Big*)(*(int**)(it[0] + 0xc)))->M_b51ee0();
        ((Ext*)0x1569cb8)->FUN_00b4f930(it, (void*)it[0], (void*)it[1]);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00B520A0
// ---------------------------------------------------------------------------
void __cdecl FUN_00b520a0()
{
    int** tbl = *(int***)0x1569cbc;
    int count = *(int*)0x1569cc0;

    int** pi = &tbl[0];
    int* node = *pi;
    if (node == 0) {
        pi = &tbl[1];
        node = *pi;
        while (node == 0) {
            pi++;
            node = *pi;
        }
    }
    int* end = tbl[count];

    while (node != end) {
        ((Big*)(*(int**)((char*)node + 0xc)))->M_b51ee0();
        node = *(int**)((char*)node + 0x10);
        while (node == 0) {
            pi++;
            node = *pi;
        }
    }
    ((Ext*)0x1569cb8)->FUN_007611f0(tbl, (u32)count);
    *(int*)0x1569cc4 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00B52120
// ---------------------------------------------------------------------------
void Big::M_b52120(int** out, int* key, int* extra)
{
    (void)extra;
    char* self = (char*)this;
    unsigned key0 = (unsigned)key[0];
    unsigned key1 = (unsigned)key[1];
    unsigned sum = key0 + key1;

    int** buckets = *(int***)(self + 4);
    unsigned nBucket = *(unsigned*)(self + 8);
    unsigned idx = sum % nBucket;
    int** slot = &buckets[idx];

    int* node = *slot;
    while (node != 0) {
        if (key0 == (unsigned)node[0] && key1 == (unsigned)node[1]) {
            out[0] = node;
            *((char*)out + 8) = 0;
            out[1] = (int*)slot;
            return;
        }
        node = *(int**)((char*)node + 0xc);
    }

    int rb[2];
    ((Ext*)(self + 0x10))->FUN_00921440(rb, nBucket, (u32)*(int*)(self + 0xc), 1);
    int* nn = (int*)(size_t)((Ext*)self)->FUN_00b576d0(key);
    if (*(char*)&rb[0] != 0) {
        unsigned nb = (unsigned)rb[1];
        idx = sum % nb;
        ((Ext*)self)->FUN_00b4fbd0(nb);
    }

    *(int**)((char*)nn + 0xc) = buckets[idx];
    buckets[idx] = nn;
    (*(int*)(self + 0xc))++;
    out[0] = nn;
    out[1] = (int*)&buckets[idx];
    *((char*)out + 8) = 1;
}

// ---------------------------------------------------------------------------
// @ 0x00B521F0
// ---------------------------------------------------------------------------
int __cdecl FUN_00b521f0(void* a)
{
    int it[2];
    void* key = a;
    ((Ext*)0x16852e8)->FUN_00645ed0(it, &key);
    int base = *(int*)0x16852ec;
    int count = *(int*)0x16852f0;
    if (it[0] != *(int*)(base + count * 4))
        return *(int*)(it[0] + 4);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00B52230
// ---------------------------------------------------------------------------
unsigned __cdecl FUN_00b52230(void* a1, void* a2)
{
    int* esi = (int*)a1;
    int* edi = (int*)a2;

    if (edi == 0) {
        int it[2];
        void* key = a1;
        ((Ext*)0x16801a8)->FUN_00645ed0(it, &key);
        int base = *(int*)0x16801ac;
        int count = *(int*)0x16801b0;
        if (it[0] == *(int*)(base + count * 4))
            return 0;
        edi = *(int**)(it[0] + 4);
        if (edi == 0)
            return 0;
    }

    if (esi != 0) {
        int ebx = ((VB8*)esi)->fB8(0x116dd1b);
        if (ebx != 0 && *(char*)((char*)edi + 0x9a) == 0) {
            int p58 = *(int*)((char*)edi + 0x58);
            float v[3];
            v[0] = *(float*)(p58 + 0xd0);
            v[1] = *(float*)(p58 + 0xd4);
            v[2] = *(float*)(p58 + 0xd8);
            void* src = FUN_0059ab70(v) ? (void*)v : (void*)0x167ecf4;
            ((Ext*)(size_t)ebx)->FUN_00c41d60(src);
        }
    }

    float q[4];
    {
        int p58 = *(int*)((char*)edi + 0x58);
        q[0] = *(float*)(p58 + 0x80);
        q[1] = *(float*)(p58 + 0x84);
        q[2] = *(float*)(p58 + 0x88);
        q[3] = *(float*)(p58 + 0x8c);
    }
    float* s = ((V30*)esi)->f30();
    if (!(q[0] == s[0] && q[1] == s[1] && q[2] == s[2] && q[3] == s[3]))
        ((V3C*)esi)->f3c(q);

    float q3[3];
    FUN_00b4dfe0(esi, edi, q3);
    float* t = ((V10*)esi)->f2c();
    if (!(t[0] == q3[0] && t[1] == q3[1] && t[2] == q3[2]))
        ((V38*)esi)->f38(q3);

    return *(u8*)((char*)esi + 0x74);
}

// ---------------------------------------------------------------------------
// @ 0x00B523E0
// ---------------------------------------------------------------------------
void __cdecl FUN_00b523e0(void* a1, void* a2)
{
    int* ebx = (int*)a1;
    int* esi = (int*)a2;

    if (esi == 0) {
        int it[2];
        void* key = a1;
        ((Ext*)0x16801a8)->FUN_00645ed0(it, &key);
        int base = *(int*)0x16801ac;
        int count = *(int*)0x16801b0;
        if (it[0] == *(int*)(base + count * 4))
            return;
        esi = *(int**)(it[0] + 4);
        if (esi == 0)
            return;
    }

    char flag = 0;
    float v[4];
    FUN_00b4e0c0(ebx, esi, v);
    int p58 = *(int*)((char*)esi + 0x58);
    float dx = fabsf(v[0] - *(float*)(p58 + 0x40));
    float dy = fabsf(v[1] - *(float*)(p58 + 0x44));
    float dz = fabsf(v[2] - *(float*)(p58 + 0x48));
    if (dx > 0.001f || dy > 0.001f || dz > 0.001f) {
        ((Body*)esi)->FUN_01087820(v);
        flag = 1;
    }

    float q[4];
    float* r = ((V30*)ebx)->f30();
    q[0] = r[0];
    q[1] = r[1];
    q[2] = r[2];
    q[3] = r[3];
    int p58b = *(int*)((char*)esi + 0x58);
    float ax = fabsf(q[0] - *(float*)(p58b + 0x80));
    float ay = fabsf(q[1] - *(float*)(p58b + 0x84));
    float az = fabsf(q[2] - *(float*)(p58b + 0x88));
    char c = flag;
    if (ax > 0.001f || ay > 0.001f || az > 0.001f) {
        ((Body*)esi)->FUN_01087840(q);
        c = 1;
    }

    if (*(char*)0x1569ab8 != 0 && c != 0 &&
        (*(int*)((char*)ebx + 0x50) & 0x2000) != 0) {
        int iv = FUN_00b521f0(ebx);
        if (iv != 0) {
            int obj = *(int*)((char*)esi + 0x1c);
            float ftmp = *(float*)0x1569ab4;
            ((VOB*)obj)->f0c((void*)(*(int*)((char*)esi + 0x58) + 0x10), ftmp, v);
            ((Body*)iv)->FUN_0108dde0(v);
            FUN_00b54000(ebx, (void*)iv);
        }
    }
}
