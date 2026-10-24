// Slice s00b72b60 -- Simulator::cObstacle obstacle math + a family of eastl-style container
// helpers (hashtable iterator advance, unique/adjacent_find over a 0xc element, an intrusive-list
// find, a node allocator, insertion sorts / heap helpers over pointer-to-obstacle by squared
// distance, and element copy/fill of 0x18/0x10-byte elements).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#include <math.h>

typedef unsigned int uint;

// ---------------------------------------------------------------- masked externs
void* __cdecl EAAllocate(uint size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
// 0x00a887b0 is a __thiscall member: it reads [ecx+0xbc]/[ecx+0xc0]/[ecx+0xa8]/[ecx+0xac]
// and takes (int index, float value) on the stack -> modelled as a member call (see cRc54).

// ---------------------------------------------------------------- globals
extern const float g_one;    // 0x01485720 = 1.0f
extern const float g_eps;    // 0x013ec4b8 = 1e-8
extern const float g_fb4;    // 0x0156b3b4
extern const float g_fb8;    // 0x0156b3b8
extern const float g_fbc;    // 0x0156b3bc
extern const float g_fc0;    // 0x0156b3c0
extern int         g_cnt;    // 0x0156b3b0
extern const float g_px;     // 0x01687ad4
extern const float g_py;     // 0x01687ad8
extern const float g_pz;     // 0x01687adc
extern const int   g_i0;     // 0x01687af0
extern const int   g_i1;     // 0x01687af4
extern const int   g_i2;     // 0x01687af8

// ================================================================================================
// 00b72b60 -- obstacle query/segment test.  this (ebx) is the Simulator (scale table at +0x548c).
// ================================================================================================
struct V3 { float x, y, z; };
// Obstacle record: position at +0x38, the distance band it quotes at +0x44/+0x48, its radius at
// +0x4c and its type index at +0x88.
struct Op {
    char  pad[0x38];
    float x, y, z;                           // +0x38, +0x3c, +0x40
    float mDistMin;                          // +0x44
    float mDistMax;                          // +0x48
    float mRadius;                           // +0x4c
    char  pad2[0x88 - 0x50];
    int   mType;                             // +0x88
};

// 0x00b72890 -- segment/obstacle test: (ray origin, ray length, normalized direction, obstacle
// position, normalized obstacle normal, distance limit, radius limit, flag, out distance).  The hit
// result is al; the caller keeps the rest of eax, so the return type stays uint.
uint __cdecl FUN_00b72890(const V3* origin, float len, const V3* dir, const V3* pos,
                          const V3* normal, float dist, float lim, char flag, float* outDist);

struct Sim {
    char  pad[0x548c];
    float mScale[4];                         // +0x548c
    float m5498;                             // +0x5498
    uint FUN_00b72b60(V3* a, V3* b, float c, Op* obj, char flag, float* outDist, bool* outFlag);
};

// @ 0x00b72b60 -- Sim::FUN_00b72b60
uint Sim::FUN_00b72b60(V3* a, V3* b, float c, Op* obj, char flag, float* outDist, bool* outFlag) {
    int   n    = obj->mType;
    float len  = sqrtf(obj->x * obj->x + obj->y * obj->y + obj->z * obj->z) + g_eps;
    float ninv = 1.0f / len;
    V3    nrm;                               // normalized obstacle position
    nrm.x = obj->x * ninv;
    nrm.y = obj->y * ninv;
    nrm.z = obj->z * ninv;

    float bl   = sqrtf(b->x * b->x + b->y * b->y + b->z * b->z);
    float binv = 1.0f / (bl + g_eps);
    V3    dir;                               // normalized query direction
    dir.x = b->x * binv;
    dir.y = b->y * binv;
    dir.z = b->z * binv;

    float al = sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);

    bool  near;                              // the obstacle reaches the query ray
    float pad;
    if (n != 0 || al < obj->mRadius * g_fb4 + len) {
        near = false; pad = g_fc0;
    } else {
        near = true;  pad = g_fbc;
    }

    float scale;
    if (n < 3)
        scale = near ? g_fb8 : mScale[n];
    else
        scale = 0.0f;

    char u8 = (near || flag == 0) ? 0 : 1;

    float dist = ((((obj->mDistMax - obj->mDistMin) * scale) + obj->mDistMin) + pad) + c;
    float lim  = obj->mRadius + pad;

    // the obstacle position doubles as the segment point handed to the test
    uint r = FUN_00b72890(a, bl, &dir, (const V3*)&obj->x, &nrm, dist, lim, u8, outDist);
    if ((char)r == 0) {
        *outDist = 0.0f;
        return r & 0xffffff00u;              // retail only clears al here
    }
    if (al < m5498 * obj->mRadius + len) {
        *outFlag = false;
        return 1;
    }
    *outFlag = true;
    return 1;
}

// ================================================================================================
// 00b72d80 -- hashtable iterator advance (thiscall, ret 8)
// ================================================================================================
struct HashNode { char pad[0x10]; HashNode* mpNext; };
struct HIt {
    HashNode*  mpNode;     // +0
    HashNode** mpBucket;   // +4
    HIt* advance(HIt* out, int);  // 0x00b72d80
};
// advance: the original hands `out` back in eax (it is loaded into eax for the two stores and
// never overwritten), so the callers may use it: declare the return.
// @ 0x00b72d80 -- HIt::advance
HIt* HIt::advance(HIt* out, int) {
    out->mpNode = mpNode;
    out->mpBucket = mpBucket;
    mpNode = mpNode->mpNext;
    while (!mpNode) {
        ++mpBucket;
        mpNode = *mpBucket;
    }
    return out;
}

// ================================================================================================
// 00b72dc0 -- eastl::unique over a 0xc-byte element (cdecl: first,last,pred)
// ================================================================================================
struct K12 { uint a, b, c; };
typedef bool (*Pred12)(const K12*, const K12*);
K12* FUN_00b72430(K12*, K12*, Pred12);   // adjacent_find

// @ 0x00b72dc0 -- FUN_00b72dc0
K12* FUN_00b72dc0(K12* first, K12* last, Pred12 pred) {
    K12* r = FUN_00b72430(first, last, pred);
    if (r != last) {
        K12* result = r;
        while (++r != last) {
            if (!pred(result, r)) {
                ++result;
                *result = *r;
            }
        }
        return ++result;
    }
    return last;
}

// ================================================================================================
// 00b72f10 -- intrusive linked-list find (__stdcall: head, key, unused ; ret 0xc)
// ================================================================================================
struct LNode {
    uint k0, k1, k2;                 // +0x00
    char pad[0xc70 - 0x0c];
    LNode* mpNext;                   // +0xc70
};
// @ 0x00b72f10 -- FUN_00b72f10
LNode* __stdcall FUN_00b72f10(LNode* p, const uint* key, uint) {
    if (p) {
        do {
            if (key[0] == p->k0 && key[1] == p->k1 && key[2] == p->k2) return p;
            p = p->mpNext;
        } while (p);
    }
    return 0;
}

// ================================================================================================
// 00b73010 -- node allocator (__stdcall: src ; ret 4)
// ================================================================================================
struct Key24 { uint v[6]; };
struct Node1c { Key24 key; uint f18; };
// @ 0x00b73010 -- FUN_00b73010
Node1c* __stdcall FUN_00b73010(const Key24* src) {
    Node1c* n = (Node1c*)EAAllocate(0x1c, "Simulator", 0, 0, "allocator.h", 0xd1);
    if (n)
        n->key = *src;
    n->f18 = 0;
    return n;
}

// ================================================================================================
// 00b73200 / 00b732a0 -- insertion_sort (guarded / unguarded) with a comparator over K12
// ================================================================================================
// @ 0x00b73200 -- FUN_00b73200
void FUN_00b73200(K12* first, K12* last, Pred12 pred) {
    if (first == last)
        return;
    K12* iSorted = first + 1;
    if (iSorted == last)
        return;
    do {
        K12 temp = *iSorted;
        K12* iNext = iSorted;
        if (iSorted != first) {
            do {
                if (!pred(&temp, iNext - 1))
                    break;
                *iNext = *(iNext - 1);
                --iNext;
            } while (iNext != first);
        }
        *iNext = temp;
        ++iSorted;
    } while (iSorted != last);
}

// @ 0x00b732a0 -- FUN_00b732a0
void FUN_00b732a0(K12* first, K12* last, Pred12 pred) {
    for (K12* current = first; current != last; ++current) {
        K12* end = current;
        K12* prev = current - 1;
        K12 value = *current;
        while (pred(&value, prev)) {
            *end = *prev;
            --end;
            --prev;
        }
        *end = value;
    }
}

// ================================================================================================
// 00b73350 / 00b73420 -- insertion_sort over OP** by squared distance to (x,y,z)
// ================================================================================================
// @ 0x00b73350 -- FUN_00b73350
void FUN_00b73350(Op** first, Op** last, float x, float y, float z) {
    if (first == last)
        return;
    Op** iSorted = first + 1;
    if (iSorted == last)
        return;
    do {
        Op* value = *iSorted;
        Op** iNext = iSorted;
        if (iSorted != first) {
            float dx = x - value->x;
            float dx2 = dx * dx;
            float dy = y - value->y;
            float dy2 = dy * dy;
            float dz = z - value->z;
            float dv = dy2 + dx2 + dz * dz;
            do {
                Op* prev = *(iNext - 1);
                float ex = x - prev->x;
                float ey = y - prev->y;
                float ez = z - prev->z;
                float ep = ez * ez + ey * ey + ex * ex;
                if (!(ep > dv))
                    break;
                *iNext = prev;
                --iNext;
            } while (iNext != first);
        }
        *iNext = value;
        ++iSorted;
    } while (iSorted != last);
}

// @ 0x00b73420 -- FUN_00b73420
void FUN_00b73420(Op** first, Op** last, float x, float y, float z) {
    for (Op** i = first; i != last; ++i) {
        Op* value = *i;
        Op** end = i;
        Op** prev = i - 1;
        float dx = x - value->x, dy = y - value->y, dz = z - value->z;
        float dv = dy * dy + dx * dx + dz * dz;
        while (1) {
            Op* p = *prev;
            float ex = x - p->x, ey = y - p->y, ez = z - p->z;
            if (ez * ez + ey * ey + ex * ex <= dv)
                break;
            *end = p;
            --end;
            --prev;
        }
        *end = value;
    }
}

// ================================================================================================
// 00b734e0 -- median-of-three of OP** by squared distance
// ================================================================================================
// @ 0x00b734e0 -- FUN_00b734e0
Op** FUN_00b734e0(Op** a, Op** b, Op** c, float x, float y, float z) {
    Op* o1 = *a;
    Op* o2 = *b;
    float d1 = (y - o1->y) * (y - o1->y) + (x - o1->x) * (x - o1->x) + (z - o1->z) * (z - o1->z);
    float d2 = (y - o2->y) * (y - o2->y) + (x - o2->x) * (x - o2->x) + (z - o2->z) * (z - o2->z);
    if (d2 <= d1) {
        Op* o3 = *c;
        float d3 = (y - o3->y) * (y - o3->y) + (x - o3->x) * (x - o3->x) + (z - o3->z) * (z - o3->z);
        if (d1 < d3)
            return a;
        if (d2 < d3)
            return c;
    } else {
        Op* o3 = *c;
        float d3 = (y - o3->y) * (y - o3->y) + (x - o3->x) * (x - o3->x) + (z - o3->z) * (z - o3->z);
        if (d3 <= d2) {
            if (d3 <= d1)
                return a;
            return c;
        }
    }
    return b;
}

// ================================================================================================
// 00b73780 -- copy E18 range (4 floats + bool + uint), guarded dst, returns dst
// ================================================================================================
struct E18 {
    float a, b, c, d;                // +0x00
    bool  f;                         // +0x10
    uint  v;                         // +0x14
    E18& operator=(const E18& o) {
        a = o.a; b = o.b; c = o.c; d = o.d; f = o.f; v = o.v;
        return *this;
    }
};
// @ 0x00b73780 -- FUN_00b73780
E18* FUN_00b73780(E18* first, E18* last, E18* dst) {
    for (; first != last; ++first, ++dst)
        if (dst)
            *dst = *first;
    return dst;
}

// ================================================================================================
// 00b737d0 -- adjust_heap over 0xc-byte elements (promote_heap tail-call)
// ================================================================================================
typedef bool (*Cmp0c)(const void*, const void*);
struct T0c { float a, b, c; };
void __cdecl FUN_00ba6800b(T0c* first, int top, int pos, float a, float b, float c, Cmp0c cmp);
// @ 0x00b737d0 -- FUN_00b737d0
void FUN_00b737d0(T0c* first, int top, int len, int pos, T0c value, Cmp0c cmp) {
    int child = pos * 2 + 2;
    while (child < len) {
        if (cmp(&first[child], &first[child - 1]))
            --child;
        first[pos] = first[child];
        pos = child;
        child = pos * 2 + 2;
    }
    if (child == len) {
        first[pos] = first[child - 1];
        pos = child - 1;
    }
    FUN_00ba6800b(first, top, pos, value.a, value.b, value.c, cmp);
}

// ================================================================================================
// 00b73890 -- copy E10 range with out-pointer (void)
// ================================================================================================
struct E10 {
    float x, y, z;                   // +0x00
    bool  f;                         // +0x0c
    E10& operator=(const E10& o) {
        x = o.x; y = o.y; z = o.z; f = o.f;
        return *this;
    }
};
// copy-range with out-pointer: `out` stays in eax for the whole function (both stores go through
// it) and the original hands it back, so declare the return.
// @ 0x00b73890 -- FUN_00b73890
E10** FUN_00b73890(E10** out, E10* first, E10* last, E10* dst) {
    *out = dst;
    if (first != last) {
        do {
            if (dst)
                *dst = *first;
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// ================================================================================================
// 00b738e0 -- fill_n-like: n copies of E10 from src
// ================================================================================================
// @ 0x00b738e0 -- FUN_00b738e0
void FUN_00b738e0(E10* dst, uint n, const E10* src) {
    for (; n; --n, ++dst)
        if (dst)
            *dst = *src;
}

// ================================================================================================
// 00b73920 -- promote_heap over OP** (by squared distance)
// ================================================================================================
// @ 0x00b73920 -- FUN_00b73920
void FUN_00b73920(Op** first, int top, int pos, Op* value, float x, float y, float z) {
    if (pos <= top) {
        first[pos] = value;
        return;
    }
    float dx = x - value->x, dy = y - value->y, dz = z - value->z;
    float dv = (dz * dz + dy * dy) + dx * dx;
    for (int parent = (pos - 1) >> 1; pos > top; parent = (pos - 1) >> 1) {
        Op* pv = first[parent];
        float ex = x - pv->x, ey = y - pv->y, ez = z - pv->z;
        if (!(dv > (ey * ey + ex * ex) + ez * ez))
            break;
        first[pos] = pv;
        pos = parent;
    }
    first[pos] = value;
}

// ================================================================================================
// 00b739f0 -- copy E10 range (3 floats + bool), guarded dst, returns dst
// ================================================================================================
// @ 0x00b739f0 -- FUN_00b739f0
E10* FUN_00b739f0(E10* first, E10* last, E10* dst) {
    for (; first != last; ++first, ++dst)
        if (dst)
            *dst = *first;
    return dst;
}

// ================================================================================================
// Simulator::cObstacle -- cGameData-derived object
// ================================================================================================
struct cGD0 { virtual void v0(); };
struct cGD1 { virtual void v1(); };
struct cGameData : cGD0, cGD1 {
    cGameData();                         // 0x00b18660
    void SetGameDataOwner(int);          // 0x00b18550
    ~cGameData();                        // 0x00b184c0
    int   m08;                           // +0x08
    void* m0c;                           // +0x0c
    void* m10;                           // +0x10
    bool  m14;                           // +0x14
    int   m18;                           // +0x18
    int   m1c;                           // +0x1c
    char  m20, m21;                      // +0x20
    int   m24;                           // +0x24
    int   m28, m2c, m30;                 // +0x28
};

#define VS(n) virtual void vs##n();
struct IV {
    VS(0)  VS(1)  VS(2)  VS(3)  VS(4)  VS(5)  VS(6)  VS(7)
    VS(8)  VS(9)  VS(10) VS(11) VS(12) VS(13) VS(14) VS(15)
    VS(16) VS(17) VS(18) VS(19) VS(20) VS(21) VS(22) VS(23)
    VS(24) VS(25) VS(26) VS(27) VS(28) VS(29) VS(30) VS(31)
    VS(32) VS(33) VS(34) VS(35) VS(36) VS(37) VS(38) VS(39)
    VS(40) VS(41) VS(42) VS(43) VS(44) VS(45) VS(46) VS(47)
    VS(48) VS(49) VS(50) VS(51) VS(52) VS(53) VS(54) VS(55)
    VS(56) VS(57) VS(58) VS(59) VS(60) VS(61) VS(62) VS(63)
    VS(64) VS(65) VS(66) VS(67) VS(68) VS(69) VS(70) VS(71)
    VS(72) VS(73) VS(74) VS(75) VS(76) VS(77) VS(78) VS(79)
    VS(80) VS(81) VS(82) VS(83) VS(84) VS(85) VS(86) VS(87)
    VS(88) VS(89) VS(90) VS(91) VS(92) VS(93) VS(94) VS(95)
};
#undef VS

// the refcounted object stored at cObstacle::m54 (vtable slot 14 releases it); 0x00a887b0 is
// its non-virtual setter, a __thiscall member with (int index, float value) on the stack.
struct cRc54 : IV {
    void SetValue(int idx, float value);   // 0x00a887b0
};

struct cObstacle : cGameData {
    int    m34;                          // +0x34
    float  m38, m3c, m40;                // +0x38
    float  m44, m48, m4c;                // +0x44
    int    m50;                          // +0x50
    void*  m54;                          // +0x54
    int    m58;                          // +0x58
    int    m5c;                          // +0x5c
    int    m60;                          // +0x60
    int    m64;                          // +0x64
    float  m68;                          // +0x68
    int    m6c;                          // +0x6c
    void*  m70;                          // +0x70
    int    m74;                          // +0x74
    void*  m78;                          // +0x78
    int    m7c, m80, m84;                // +0x7c
    int    m88;                          // +0x88

    cObstacle();                                   // 0x00b73a30
    virtual ~cObstacle();                          // 0x00b73b30
    void  Reset0();                                // 0x00b73bc0
    void  Reset1();                                // 0x00b73cd0
    void  SetFlag(bool);                           // 0x00b73de0
};

// release helper: emulate the inlined refcounted Release() pattern (a two-level "vtable")
struct RcTbl { void* fn[0x100]; };
struct RcVt { RcTbl* tbl; };
struct Rc { RcVt* vt; int f4; char pad[0x40 - 8]; int rc; };

// The call site is entered with ecx = the object's vtable pointer (a leftover of the
// two-level dereference, not an argument: the callee is __stdcall with the object pushed).
// Model it as ecx = the vtable pointer so the register state matches the original.
typedef void (__fastcall* RcFn)(void* vt, int junk, void* obj, unsigned arg);
static inline void RcCall(void* p, int off, unsigned arg) {
    Rc* o = (Rc*)p;
    ((RcFn)o->vt->tbl->fn[off / 4])((void*)o->vt, 0, p, arg);
}

static inline void ReleaseRc(void* p) {
    if (!p)
        return;
    Rc* o = (Rc*)p;
    if (o->rc <= 1) {
        unsigned a = ((unsigned)o->f4 >> 31) & 1u;
        RcCall(p, 0x170, a);
    } else {
        --o->rc;
    }
}

// @ 0x00b73a30 -- Simulator::cObstacle::cObstacle
cObstacle::cObstacle() : cGameData() {
    m34 = 0;
    m38 = g_px; m3c = g_py; m40 = g_pz;
    m44 = 0.0f; m48 = 0.0f; m4c = 0.0f;
    m50 = -1;
    m54 = 0;
    m58 = 0;
    m60 = 0;
    m6c = 0;
    m5c = -1;
    m64 = -1;
    m68 = g_one;
    m70 = 0;
    m74 = 0;
    m78 = 0;
    m7c = g_i0; m80 = g_i1; m84 = g_i2;
    m88 = 0;
}

// @ 0x00b73b30 -- Simulator::cObstacle::~cObstacle
cObstacle::~cObstacle() {
    ReleaseRc(m78);
    ReleaseRc(m70);
    if (m54)
        ((IV*)m54)->vs14();
}

// @ 0x00b73bc0 -- FUN_00b73bc0
void cObstacle::Reset0() {
    SetGameDataOwner(0);
    m60 = g_cnt;
    ++g_cnt;
    m38 = g_px; m3c = g_py; m40 = g_pz;
    m44 = 0.0f; m48 = 0.0f; m4c = 0.0f;
    m68 = g_one;
    m6c = 0;
    m74 = 0;
    if (m70) { void* t = m70; m70 = 0; ReleaseRc(t); }
    if (m78) { void* t = m78; m78 = 0; ReleaseRc(t); }
    m7c = g_i0; m80 = g_i1; m84 = g_i2;
    m50 = -1;
    m5c = -1;
    m58 = 0;
    if (m54) { void* t = m54; m54 = 0; ((IV*)t)->vs14(); }
    m88 = 0;
    m64 = -1;
}

// @ 0x00b73cd0 -- FUN_00b73cd0
void cObstacle::Reset1() {
    if (m2c) { IV* t = (IV*)m2c; m2c = 0; t->vs1(); }
    m60 = 0;
    m38 = g_px; m3c = g_py; m40 = g_pz;
    m44 = 0.0f; m48 = 0.0f; m4c = 0.0f;
    m68 = g_one;
    m6c = 0;
    m74 = 0;
    if (m70) { void* t = m70; m70 = 0; ReleaseRc(t); }
    if (m78) { void* t = m78; m78 = 0; ReleaseRc(t); }
    m7c = g_i0; m80 = g_i1; m84 = g_i2;
    m50 = -1;
    m5c = -1;
    m58 = 0;
    if (m54) { void* t = m54; m54 = 0; ((IV*)t)->vs14(); }
    m88 = 0;
    m64 = -1;
}

// @ 0x00b73de0 -- FUN_00b73de0
void cObstacle::SetFlag(bool b) {
    if (b)
        m34 |= 1;
    else
        m34 &= ~1u;
    if (m54) {
        float f = b ? 0.0f : g_one;
        ((cRc54*)m54)->SetValue(m5c, f);
        return;
    }
    if (m70) {
        if (b) {
            *(int*)((char*)m70 + 4) &= ~1u;
            RcCall(m70, 0x16c, 0);
        } else {
            *(int*)((char*)m70 + 4) |= 1;
            RcCall(m70, 0x16c, 1);
        }
    }
}
