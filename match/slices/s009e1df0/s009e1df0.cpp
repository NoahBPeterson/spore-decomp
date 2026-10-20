// slice s009e1df0 -- nSPCreatureAnim Inner (gait record aggregate) default constructor and the
// three gait-list copy helpers, all compiled together in the retail TU.
//
//   @ 0x009e1df0  Inner::Inner()                        default ctor: scalars, the 26 tune floats
//                                                       and the empty item / gait lists
//   @ 0x009e1fe0  Inner::AssignGaitsN(const Inner*, u32) copy at most n gaits from another Inner
//   @ 0x009e2140  Inner::AssignGaitsF(const Inner*, u32) copy the gait list (flags & 0x4000000
//                                                       suppresses the element copy)
//   @ 0x009e22f0  Inner::AssignGaits(const Inner*)       copy the gait list
//
// Build: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc)
#include "types.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

inline void* operator new(unsigned, void* p) { return p; }
void  operator delete[](void* p);                                     // 0x00f47380

// tune floats the ctor pulls in (globals, they are loaded, not immediate)
extern float g_1550b20;                                               // 0x01550b20 1.0f
extern float g_1550b24;                                               // 0x01550b24 1.0f
extern float g_1550b2c;                                               // 0x01550b2c 6.0f
extern float g_1550b30;                                               // 0x01550b30 0.8f
extern float g_1550b34;                                               // 0x01550b34 0.02f
extern float g_1550b38;                                               // 0x01550b38 0.25f
extern float g_1550b3c;                                               // 0x01550b3c 0.75f
extern float g_1550b40;                                               // 0x01550b40 0.5f
extern float g_1550b44;                                               // 0x01550b44 0.1f
extern float g_1550b48;                                               // 0x01550b48 0.1f
extern float g_1550b4c;                                               // 0x01550b4c 0.075f
extern float g_1550b50;                                               // 0x01550b50 0.025f
extern float g_1550b54;                                               // 0x01550b54 0.05f
extern float g_1550b58;                                               // 0x01550b58 0.5f
extern float g_1550b5c;                                               // 0x01550b5c 0.15f
extern float g_1550b60;                                               // 0x01550b60 10.0f
extern float g_1550b64;                                               // 0x01550b64 10.0f
extern float g_1550b68;                                               // 0x01550b68 10.0f
extern float g_166c024;                                               // 0x0166c024
extern float g_166c028;                                               // 0x0166c028
extern float g_166c02c;                                               // 0x0166c02c
extern float g_166c030;                                               // 0x0166c030
extern float g_166c034;                                               // 0x0166c034
extern float g_166c038;                                               // 0x0166c038
extern float g_166c03c;                                               // 0x0166c03c
extern float g_166c040;                                               // 0x0166c040
extern float g_166c044;                                               // 0x0166c044
extern int   g_15515dc;                                               // 0x015515dc alloc-debug flag

struct GaitA; struct GaitB; struct GaitC;
struct Gait;

Gait* Copy40(Gait* first, Gait* last, Gait* result);                  // 0x009e0cd0 eastl::copy

// ------------------------------------------------------------------ containers

struct VecA {                                                         // 0x14: begin/end/cap + alloc
    GaitA* b; GaitA* e; GaitA* cap; int alloc[2];
    VecA() : b(0), e(0), cap(0) {}
    ~VecA() { if (b && ((int*)b)[-1]) operator delete[](b); }
    VecA& assign(const VecA& o);                                      // 0x009dfda0
};

struct VecB {
    GaitB* b; GaitB* e; GaitB* cap; int alloc[2];
    VecB() : b(0), e(0), cap(0) {}
    ~VecB() { if (b && ((int*)b)[-1]) operator delete[](b); }
    VecB& assign(const VecB& o);                                      // 0x009dfec0
};

struct VecC {
    GaitC* b; GaitC* e; GaitC* cap; int alloc[2];
    VecC() : b(0), e(0), cap(0) {}
    ~VecC() { if (b && ((int*)b)[-1]) operator delete[](b); }
    VecC& assign(const VecC& o);                                      // 0x009dffe0
};

struct Gait {                                                         // 0x40
    int  id;                                                          // +0x00
    VecA a;                                                           // +0x04
    VecB b;                                                           // +0x18
    VecC c;                                                           // +0x2c
    Gait(const Gait& o) : a(), b(), c()
    {
        id = o.id; a.assign(o.a); b.assign(o.b); c.assign(o.c);
    }
    Gait& operator=(const Gait& o)
    {
        if (this != &o) {
            id = o.id; a.assign(o.a); b.assign(o.b); c.assign(o.c);
        }
        return *this;
    }
};

struct VecG {                                                         // 0x14
    Gait* b; Gait* e; Gait* cap; int alloc[2];
    VecG() : b(0), e(0), cap(0) {}
    ~VecG() { destroy(b, e); if (b && ((int*)b)[-1]) operator delete[](b); }
    void reserve(int n);                                              // 0x009e18f0
    void destroy(Gait* first, Gait* last);                            // 0x009de770
    void realloc_insert(Gait* pos, const Gait& v);                    // 0x009e1990
    void push_back(const Gait& v)
    {
        if (e < cap) { Gait* p = e++; ::new((void*)p) Gait(v); }
        else realloc_insert(e, v);
    }
    void pop_back() { --e; e->~Gait(); }
};

struct Item { float a, b; int c; };                                   // 0x0c

// EASTL min: returns a reference to the smaller of two lvalues.
template <class T> inline const T& emin(const T& a, const T& b) { return b < a ? b : a; }

struct VecI {
    Item* b; Item* e; Item* cap; int alloc[2];
    VecI() : b(0), e(0), cap(0) {}
    ~VecI() { if (b && ((int*)b)[-1]) operator delete[](b); }
    Item* erase(Item* first, Item* last);                             // 0x009e0480
};

struct Inner {                                                        // 0xa0
    int    f0;                                                        // +0x00
    float  f4;                                                        // +0x04
    int    f8;                                                        // +0x08
    VecI   items;                                                     // +0x0c
    VecG   gaits;                                                     // +0x20
    float  p[26];                                                     // +0x34
    bool   flag;                                                      // +0x9c
    Inner();                                                          // 0x009e1df0
    void AssignGaitsN(const Inner* o, uint32 n);                      // 0x009e1fe0
    void AssignGaitsF(const Inner* o, uint32 flags);                  // 0x009e2140
    void AssignGaits(const Inner* o);                                 // 0x009e22f0
};

// ------------------------------------------------------------------ @ 0x009e1df0

// @ 0x009e1df0
Inner::Inner()
    : f0(0), f4(g_1550b20), f8(-1), items(), gaits()
{
    p[0]  = g_1550b24;
    p[1]  = g_166c024;
    p[2]  = g_166c028;
    p[3]  = g_166c02c;
    p[4]  = g_1550b2c;
    p[5]  = g_1550b30;
    p[6]  = g_1550b34;
    p[7]  = g_1550b38;
    p[8]  = g_1550b3c;
    p[9]  = g_166c030;
    p[10] = g_1550b40;
    p[11] = g_166c034;
    p[12] = g_1550b44;
    p[13] = g_166c038;
    p[14] = g_1550b48;
    p[15] = g_1550b4c;
    p[16] = g_166c03c;
    p[17] = g_166c040;
    p[18] = g_1550b50;
    p[19] = g_1550b54;
    p[20] = g_1550b58;
    p[21] = g_1550b5c;
    p[22] = g_166c044;
    p[23] = g_1550b60;
    p[24] = g_1550b64;
    p[25] = g_1550b68;
    flag = true;

    items.erase(items.b, items.e);
    if (g_15515dc) {
        int last = (int)gaits.e;
        int first = (int)gaits.b;
        Gait* t = Copy40(gaits.e, gaits.e, gaits.b);
        gaits.destroy(t, gaits.e);
        gaits.e = (Gait*)((int)gaits.e + ((last - first) >> 6) * -0x40);
    }
}

// ------------------------------------------------------------------ @ 0x009e1fe0

// @ 0x009e1fe0
void Inner::AssignGaitsN(const Inner* o, uint32 n)
{
    VecG& g = gaits;
    uint32 myCount = (uint32)(g.e - g.b);
    uint32 oCount  = (uint32)(o->gaits.e - o->gaits.b);
    uint32 cp  = emin(myCount, oCount);
    uint32 lim = emin(n, oCount);
    for (uint32 i = 0; i < cp; i++)
        g.b[i] = o->gaits.b[i];
    g.reserve((int)lim);
    for (uint32 i = cp; i < lim; i++)
        g.push_back(o->gaits.b[i]);
}

// ------------------------------------------------------------------ @ 0x009e2140

// @ 0x009e2140
void Inner::AssignGaitsF(const Inner* o, uint32 flags)
{
    uint32 myCount = (uint32)(gaits.e - gaits.b);
    uint32 oCount  = (uint32)(o->gaits.e - o->gaits.b);
    uint32 cp = emin(myCount, oCount);
    if (oCount < myCount) {
        for (uint32 i = oCount; i < myCount; i++)
            gaits.pop_back();
    }
    if (!(flags & 0x4000000)) {
        for (uint32 i = 0; i < cp; i++)
            gaits.b[i] = o->gaits.b[i];
    }
    gaits.reserve((int)oCount);
    for (uint32 i = cp; i < oCount; i++)
        gaits.push_back(o->gaits.b[i]);
}

// ------------------------------------------------------------------ @ 0x009e22f0

// @ 0x009e22f0
void Inner::AssignGaits(const Inner* o)
{
    uint32 myCount = (uint32)(gaits.e - gaits.b);
    uint32 oCount  = (uint32)(o->gaits.e - o->gaits.b);
    uint32 cp = emin(myCount, oCount);
    if (oCount < myCount) {
        for (uint32 i = oCount; i < myCount; i++)
            gaits.pop_back();
    }
    for (uint32 i = 0; i < cp; i++)
        gaits.b[i] = o->gaits.b[i];
    gaits.reserve((int)oCount);
    for (uint32 i = cp; i < oCount; i++)
        gaits.push_back(o->gaits.b[i]);
}
