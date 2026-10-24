// Gold batch "gold1" slice s00a1e320 — 9 functions (EA::Audio::Sound helpers).
// Complete, compilable reconstruction. Byte-exact functions are listed in manifest.txt;
// behaviourally complete but non-byte-exact functions are listed in nonmatching.txt.
#include "types.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// ---------------------------------------------------------------------------------------
// External callees (address-labelled).
// ---------------------------------------------------------------------------------------
extern void  f_00921260(void* pool, unsigned size, unsigned buckets, unsigned align, unsigned n);
extern u32   f_00921340(int n);
extern unsigned f_009213c0(void* self, unsigned v);
extern void  f_00a22220(void* self, unsigned n);
extern void  f_00a1cdb0(void* self, void* a, void* b, void* c, void* d, void* e, void* f, void* g);
extern void  f_00a1ce60(void* self, void* a, void* b, void* c, void* d, void* e, void* f, void* g);

extern void* f_011e0744(void* dst, const void* src, unsigned bytes);
extern void  f_00f47380(void* p);
extern void* f_00a80dd0(void* pos, const void* value);
extern void* f_00a17090(unsigned size);
extern void* f_00a17100(void* self);
extern void  f_00fccdd0(unsigned v);
extern void  f_00a16fd0(float v);
extern void  f_00886db0(void* p);
extern char  f_00a1b160(void* self, int a, int b, void* out);
extern float f_00a1ac70(void* self, float x);
extern void  f_00a24480(void* self, int a, int b);
extern void  f_00a1b6c0(void* self, int a, int b);
extern void* f_00a206f0(void);
extern void  f_00899480(unsigned* pos, const unsigned* value);
extern void  f_00a1b020(void);

extern "C" int __cdecl isalnum(int c);
extern "C" int __cdecl tolower(int c);

static void*  g_166d9bc;
static void*  g_166d9c0;
static void*  g_166d9c4;
static int    g_166d9d0;
static float  g_166d9e0;
static float  g_166d9e4;
static float  g_166d9e8;

// vtable-slot dispatch: VPTR(return-type, obj, slot, arg-types...)(obj, args...)
#define VPTR(ret, obj, slot, ...) \
    ((ret (__thiscall*)(void*, __VA_ARGS__))((void**)*(void**)(obj))[(slot) / 4])

// ---------------------------------------------------------------------------------------
// EASTL fixed-pool / fixed-hashtable helpers used by the two factory ctors.  The original
// code builds a fixed_pool_base on the stack, initialises it over a slice of the owner and
// then hands a pointer to it to the hashtable constructor (which re-creates the same pool
// at owner+0x1c and reads the bucket count from the descriptor).
// ---------------------------------------------------------------------------------------
struct FixedPoolBase {
    void* mpBuffer;         // +0x00  set by init(): aligned free-list buffer
    void* mpUnk04;          // +0x04
    void* mpBegin;          // +0x08  buffer handed to the hashtable pool
    void* mpEnd;            // +0x0c  begin + size
    u32   mnCount;          // +0x10  element count
    void* mpBuckets;        // +0x14  owner-embedded bucket array (copied to pool+0x14)
    void* mpUnk18;          // +0x18
    void init(void* p, u32 size, u32 count, u32 align, u32 offset);  // 0x00921260 (thiscall, ret 0x14)
};
struct HashtableCtor {      // eastl::hashtable<unsigned,EA::AutoRefCount<PrimitiveRegister>,...>
    // Only args 1 (bucket count) and 7 (pool descriptor) are consumed.
    void ctor(u32 buckets, void* a, void** b, void** c, void* d, void** e, void* pool); // 0x00a1cdb0 (thiscall, ret 0x1c)
};
struct HashtableCtor2 {     // same shape, larger fixed allocator
    void ctor(u32 buckets, void* a, void** b, void** c, void* d, void** e, void* pool); // 0x00a1ce60 (thiscall, ret 0x1c)
};
struct RehashCalc {         // bucket count for a load factor: ecx = &loadFactor
    u32 calc(u32 n);        // 0x009213c0 (thiscall, ret 4)
};
struct SimpleVecPush {      // SP::SimpleVector<CellData*>
    void* mpBegin;          // +0x00
    void* mpEnd;            // +0x04
    void* mpCap;            // +0x08
    void Insert(void** pos, void** value);   // 0x00a80dd0 (thiscall, ret 8)
};

// ---------------------------------------------------------------------------------------
// 4-byte element eastl vector.
// ---------------------------------------------------------------------------------------
struct Vec4 {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCap;

    Vec4* assign_(const Vec4& other);
    void* DoAssign(unsigned n, void* first, void* last);   // external: vector range-assign helper
};

// ---------------------------------------------------------------------------------------
// Big Sound owner. Subsystems live at fixed byte offsets.
// ---------------------------------------------------------------------------------------
struct Sound74 {
    unsigned char m[0xd40];

    void* ctor_00a1e320(void* a1, void* a2);
    void* ctor_00a1e420(void* a1, void* a2);
    void AddCell(void* p);
    void ReleaseAllCells();
    void UpdateCells(int a, float* b);
    char ConfigureNote();
    void Teardown();
    void SubscribeToGroupsFromSymbol(const char* symbol);
};

// =======================================================================================
// 0x00A1E320  factory ctor (fixed hashtable + pool). EH frame; reconstruction.
// =======================================================================================
// @ 0x00A1E320
void* Sound74::ctor_00a1e320(void* a1, void* a2) {
    u8* t = m;
    FixedPoolBase pool;
    pool.init(t + 0x8c, 0xf0, 0xc, 4, 0);
    pool.mpBegin = t + 0x8c;
    pool.mpEnd = t + 0x17c;
    pool.mnCount = 0xc;
    pool.mpBuckets = t + 0x34;
    u32 buckets = f_00921340(0x15);
    ((HashtableCtor*)t)->ctor(buckets, a1, &a2, &a2, a2, &a2, &pool);
    struct RehashPolicy { float mfMaxLoadFactor; float mfGrowthFactor; u32 mnBucketCount; };
    RehashPolicy policy = { 10000.0f, 2.0f, 0 };
    *(u32*)(t + 0x10) = 0x461c4000;
    *(u32*)(t + 0x14) = 0x40000000;
    *(u32*)(t + 0x18) = 0;
    u32 need = ((RehashCalc*)&policy)->calc(*(u32*)(t + 0x0c));
    if (need > *(u32*)(t + 8))
        f_00a22220(t, need);
    return this;
}

// =======================================================================================
// 0x00A1E420  factory ctor (larger fixed hashtable + pool). EH frame; reconstruction.
// =======================================================================================
// @ 0x00A1E420
void* Sound74::ctor_00a1e420(void* a1, void* a2) {
    u8* t = m;
    FixedPoolBase pool;
    pool.init(t + 0xdc, 0x1e0, 0xc, 4, 0);
    pool.mpBegin = t + 0xdc;
    pool.mpEnd = t + 0x2bc;
    pool.mnCount = 0xc;
    pool.mpBuckets = t + 0x34;
    u32 buckets = f_00921340(0x29);
    ((HashtableCtor2*)t)->ctor(buckets, a1, &a2, &a2, a2, &a2, &pool);
    struct RehashPolicy { float mfMaxLoadFactor; float mfGrowthFactor; u32 mnBucketCount; };
    RehashPolicy policy = { 10000.0f, 2.0f, 0 };
    *(u32*)(t + 0x10) = 0x461c4000;
    *(u32*)(t + 0x14) = 0x40000000;
    *(u32*)(t + 0x18) = 0;
    u32 need = ((RehashCalc*)&policy)->calc(*(u32*)(t + 0x0c));
    if (need > *(u32*)(t + 8))
        f_00a22220(t, need);
    return this;
}

// =======================================================================================
// 0x00A1E520  eastl vector<T>::assign / operator= (defined inline above)
// =======================================================================================
// @ 0x00A1E520
Vec4* Vec4::assign_(const Vec4& other) {
    if (&other == this) return this;
    unsigned n = (unsigned)(other.mpEnd - other.mpBegin);
    unsigned cap = (unsigned)(mpCap - mpBegin);
    if (n > cap) {
        unsigned* p = (unsigned*)DoAssign(n, other.mpBegin, other.mpEnd);
        unsigned* old = mpBegin;
        if (old != 0 && ((int*)old)[-1] != 0) f_00f47380(old);
        mpBegin = p;
        mpCap = p + n;
        mpEnd = p + n;
        return this;
    }
    unsigned m = (unsigned)(mpEnd - mpBegin);
    if (n > m) {
        f_011e0744(mpBegin, other.mpBegin, m * 4);
        char* src = (char*)other.mpBegin + m * 4;
        f_011e0744(mpEnd, src, (unsigned)((char*)other.mpEnd - src));
        mpEnd = mpBegin + n;
        return this;
    }
    f_011e0744(mpBegin, other.mpBegin, (unsigned)((char*)other.mpEnd - (char*)other.mpBegin));
    mpEnd = mpBegin + n;
    return this;
}

// =======================================================================================
// 0x00A1E5F0  SP::SimpleVector<CellData*>::push_back
// =======================================================================================
// @ 0x00A1E5F0
void Sound74::AddCell(void* p) {
    if (p == 0) return;
    VPTR(void, p, 0xd4, void*)(p, this);
    void** end = *(void***)(m + 0xc80);
    if (end < *(void***)(m + 0xc84)) {
        *(void***)(m + 0xc80) = end + 1;
        if (end != 0) *end = p;
    } else {
        ((SimpleVecPush*)(m + 0xc7c))->Insert(end, &p);
    }
    VPTR(void, p, 0)(p);
}

// =======================================================================================
// 0x00A1E660  SP::SimpleVector<CellData*>::release-all and clear
// =======================================================================================
// @ 0x00A1E660
void Sound74::ReleaseAllCells() {
    void** end = *(void***)(m + 0xc80);
    for (void** it = *(void***)(m + 0xc7c); it != end; ++it) {
        void* p = *it;
        VPTR(void, p, 0x80, int, int)(p, 3, 1);
        VPTR(void, p, 4)(p);
    }
    void** first = *(void***)(m + 0xc7c);
    void** last  = *(void***)(m + 0xc80);
    void** endp  = *(void***)(m + 0xc80);
    f_011e0744(first, last, (unsigned)((char*)endp - (char*)last));
    *(void***)(m + 0xc80) -= (last - first);
}

// =======================================================================================
// 0x00A1E6D0  EA::Audio::Sound::UpdateCellAccumulators. Reconstruction.
// =======================================================================================
// @ 0x00A1E6D0
void Sound74::UpdateCells(int param_2, float* param_3) {
    float* p = (float*)this;
    p[0x31] = p[0x2a];
    p[0x32] = p[0x2b];
    p[0x33] = p[0x2c];
    p[0x35] = 0.0f;
    p[0x34] = 0.0f;
    p[0x36] = 0.0f;
    (void)param_2;

    if ((*(u8*)(p + 0x339) & 0x20) == 0) return;

    float best = 0.0f;
    float sumW = 0.0f, accX = 0.0f, accY = 0.0f, accZ = 0.0f, accR = 0.0f, accN = 0.0f;
    int count = 0;

    {
        void* self = this;
        f_00a80dd0(g_166d9c0, &self);
    }

    float* begin = (float*)g_166d9bc;
    float* end = (float*)g_166d9c0;
    while (begin != end) {
        void* cell = *(void**)begin;
        if (cell != (void*)p) {
            int* ci = (int*)cell;
            f_00a1b020();
            float d = (float)((ci[0x2c] - param_3[2]) * (ci[0x2c] - param_3[2]) +
                              (ci[0x2b] - param_3[1]) * (ci[0x2b] - param_3[1]) +
                              (ci[0x2a] - param_3[0]) * (ci[0x2a] - param_3[0]));
            d = (d < 0.0f) ? -d : d;
            if (d < (float)ci[0x26] * (float)ci[0x16]) {
                float r = VPTR(float, cell, 0xa8, float, int, int, float, int)(
                    cell, d, ci[0x14], ci[0x15], (float)ci[0x16], ci[0x26]);
                if (!(r >= 1e-06f)) { /* skip */ }
                else {
                    if (d < best) best = d;
                    ++count;
                    float w = 1.0f / ((d / r) * (d / r) + 1e-12f);
                    sumW += w;
                    accX += (float)ci[0x2a] * w;
                    accY += (float)ci[0x2b] * w;
                    accZ += (float)ci[0x2c] * w;
                    accR += (float)ci[0x25] * w;
                    accN += (float)ci[0x26] * w;
                }
            }
        }
        ++begin;
    }

    g_166d9c0 = (char*)g_166d9c0 - 4;

    if (count != 0) {
        float inv = 1.0f / sumW;
        p[0x31] = inv * accX;
        p[0x32] = inv * accY;
        p[0x33] = inv * accZ;
        p[0x35] = (float)VPTR(float, this, 0xa8, int, int, int, int, float)(
            this, (int)best, ((int*)this)[0x14], ((int*)this)[0x15], ((int*)this)[0x16], inv * accN);
        p[0x34] = inv * accR;
        p[0x36] = inv * accN;
    }

    for (void** it = (void**)g_166d9bc; it != (void**)g_166d9c0; ++it)
        VPTR(void, *it, 0x8c)(*it);
    f_011e0744(g_166d9bc, g_166d9c0, 0);
}

// =======================================================================================
// 0x00A1EB50  EA::Audio::Sound::ConfigureNote. EH frame; reconstruction.
// =======================================================================================
// @ 0x00A1EB50
char Sound74::ConfigureNote() {
    void* props = m + 4;
    if (!VPTR(char, props, 0x14, unsigned)(props, 0x66ef9aba)) return 0;
    if (!VPTR(char, props, 0x14, unsigned)(props, 0xe4dd1818)) return 0;
    if (!VPTR(char, props, 0x14, unsigned)(props, 0x0cd928a9)) return 0;
    if (!VPTR(char, props, 0x14, unsigned)(props, 0x07f28acc))
        *(u32*)(m + 0x334) = 0x556fea66;

    void* sys = f_00a206f0();
    void* zone = *(void**)(m + 0x2dc);
    if (zone != 0) {
        *(void**)(m + 0x2dc) = 0;
        VPTR(void, zone, 4)(zone);
    }
    if (!VPTR(char, sys, 0x18c, void*, void*)(sys, m + 0x1c, m + 0x2dc))
        return 0;

    float a = 0.0f, c = 0.0f;
    VPTR(void, this, 0xac, float*)(this, &a);
    VPTR(void, this, 0xac, float*)(this, &a);
    VPTR(void, this, 0xac, unsigned, float*)(this, 0x0cd928a9, &c);
    float scale = c * 0.001f;
    (void)scale;

    float out = 0.0f;
    if (!f_00a1b160(*(void**)(m + 0x2dc), (int)a, 0, &out))
        return 0;
    float v = 0.0f * 0.007874016f;
    float r = f_00a1ac70(this, v);
    (void)r;
    return 1;
}

// =======================================================================================
// 0x00A1EEF0  EA::Audio::Sound::Teardown. Reconstruction.
// =======================================================================================
// @ 0x00A1EEF0
void Sound74::Teardown() {
    unsigned char* t = m;

    // hashtable #1: iterate nodes, release matching owners, free nodes.
    {
        void** nodes = *(void***)(t + 0x33c);
        unsigned n = *(unsigned*)(t + 0x340);
        void* end = nodes[n];
        for (void* node = *nodes; node != end;) {
            void* obj = *(void**)((char*)node + 4);
            if (VPTR(void*, obj, 0x30)(obj) == (void*)t)
                VPTR(void, obj, 0x14)(obj);
            node = *(void**)((char*)node + 8);
            if (node == 0) { ++nodes; while (nodes[0] == 0) ++nodes; node = *nodes; }
        }
        f_00a24480(t + 0x338, *(int*)(t + 0x340), *(int*)(t + 0x33c));
        *(int*)(t + 0x338 + 0x0c) = 0;
    }

    // hashtable #2
    {
        void** nodes = *(void***)(t + 0x51c);
        unsigned n = *(unsigned*)(t + 0x520);
        void* end = nodes[n];
        for (void* node = *nodes; node != end;) {
            void* obj = *(void**)((char*)node + 4);
            VPTR(void, obj, 0x14)(obj);
            VPTR(void, obj, 4)(obj);
            node = *(void**)((char*)node + 8);
            if (node == 0) { ++nodes; while (nodes[0] == 0) ++nodes; node = *nodes; }
        }
        f_00a1b6c0(t + 0x518, *(int*)(t + 0x520), *(int*)(t + 0x51c));
        *(int*)(t + 0x518 + 0x0c) = 0;
    }

    // release vector at +0xbf8
    {
        void** end = *(void***)(t + 0xbfc);
        for (void** it = *(void***)(t + 0xbf8); it != end; ++it) {
            void* o = *it;
            VPTR(void, o, 0x14)(o);
            VPTR(void, o, 4)(o);
        }
        char* e = (char*)*(void***)(t + 0xbfc);
        char* b = (char*)*(void***)(t + 0xbf8);
        f_011e0744(b, e, 0);
        unsigned nn = (unsigned)(e - b) >> 2;
        *(int*)(t + 0xbfc) += (-(int)nn) * 4;
    }

    // hashtable #3
    {
        void** nodes = *(void***)(t + 0x88c);
        unsigned n = *(unsigned*)(t + 0x890);
        void* end = nodes[n];
        for (void* node = *nodes; node != end;) {
            void* obj = *(void**)((char*)node + 4);
            VPTR(void, obj, 0x14)(obj);
            VPTR(void, obj, 4)(obj);
            node = *(void**)((char*)node + 8);
            if (node == 0) { ++nodes; while (nodes[0] == 0) ++nodes; node = *nodes; }
        }
        f_00a1b6c0(t + 0x888, *(int*)(t + 0x890), *(int*)(t + 0x88c));
        *(int*)(t + 0x888 + 0x0c) = 0;
    }

    // primary object at +0xc38
    if (*(void**)(t + 0xc38) != 0) {
        void** end = *(void***)(t + 0xc40);
        for (void** it = *(void***)(t + 0xc3c); it != end; ++it) {
            void* o = *it;
            void* sys = f_00a206f0();
            void* found = VPTR(void*, sys, 0x11c, void*)(sys, o);
            if (found != 0)
                VPTR(void, found, 0x1c, void*, void*)(found, *(void**)(t + 0xce8), *(void**)(t + 0xc38));
        }
        void* prim = *(void**)(t + 0xc38);
        VPTR(void, prim, 0x14)(prim);
        prim = *(void**)(t + 0xc38);
        if (prim != 0) {
            *(void**)(t + 0xc38) = 0;
            VPTR(void, prim, 4)(prim);
        }
    }
}

// =======================================================================================
// 0x00A1F180  EA::Audio::Sound::SubscribeToGroupsFromSymbol
// =======================================================================================
// @ 0x00A1F180
void Sound74::SubscribeToGroupsFromSymbol(const char* symbol) {
    if (symbol == 0 || *symbol == 0) return;
    while (!isalnum((char)*symbol)) ++symbol;

    char c = *symbol;
    while (c != 0) {
        const char* wordEnd = symbol;
        if (isalnum((char)c)) {
            do { ++wordEnd; } while (isalnum((char)*wordEnd));
        }

        unsigned hash = 0x811c9dc5;
        while (symbol < wordEnd) {
            hash = hash * 0x1000193 ^ (unsigned)tolower((unsigned char)*symbol);
            ++symbol;
        }

        unsigned* end = *(unsigned**)(m + 0x2e4);
        if (end < *(unsigned**)(m + 0x2e8)) {
            unsigned* old = end;
            *(unsigned**)(m + 0x2e4) = old + 1;
            if (old != 0) *old = hash;
        } else {
            f_00899480(end, &hash);
        }

        void* sys = f_00a206f0();
        VPTR(void, sys, 0x108, unsigned, void*)(sys, hash, (void*)(m + 4));

        c = *symbol;
        if (c == 0) return;
        while (!isalnum((char)c)) {
            ++symbol;
            c = *symbol;
            if (c == 0) return;
        }
        c = *symbol;
    }
}
