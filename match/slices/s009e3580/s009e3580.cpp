// slice s009e3580 -- nSPCreatureAnim gait-command data: the "gcmdd" record (an Anim::gcmdd holds
// four gait key records, a Gait and a gait Inner), the 0xb4-byte animation channel cells used by the
// gait-command table, the table itself, and the Entry (keyed Inner) copy/fill helpers.
//
//   @ 0x009e3580  Anim::gcmdd::gcmdd()                    default ctor of the 0x1c8 record
//   @ 0x009e3740  gcmddHost::Create(int)                  allocate a gcmdd into the host, refresh it
//   @ 0x009e3790  Inner::operator=(const Inner&)          scalar/item/gait field copy
//   @ 0x009e37c0  Inner::Blend(const Inner*, float, const Inner*)   masked per-field lerp
//   @ 0x009e3cf0  Channel::Channel()                      one animation channel cell
//   @ 0x009e3de0  Channel::Reset()                        put a channel cell back to defaults
//   @ 0x009e3ec0  gcmddTable::gcmddTable()                channels + inner + zeroed key grids
//   @ 0x009e3f70  gcmddTable::Reset(int, int)             clear an n x m block of channels and keys
//   @ 0x009e4030  EntryArr::Sample(float, Inner*)         interpolate the entry pair around a key
//   @ 0x009e4120  Entry::Entry(const Entry&)              key + Inner copy
//   @ 0x009e4170  EntryConstructN(Entry*, unsigned, const Entry*)   construct n copies
//   @ 0x009e41e0  EntryAssignRange(Entry*, Entry*, Entry*)          assign a range
//   @ 0x009e4260  EntryCopy(Entry*, Entry*, Entry*)                 forward copy, returns dst end
//   @ 0x009e42d0  EntryCopyBackward(Entry*, Entry*, Entry*)         backward copy
//   @ 0x009e4350  Inner::Inner(int, int)                  keyed Inner with n items / gaits
//
// Build: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

inline void* operator new(unsigned, void* p) { return p; }
void  operator delete[](void* p);                                       // 0x00f47380
void* EAAllocate(unsigned size, const char* tag, int a, int b, int c, int d);  // 0x00f473a0
double WrapRange(float delta, float period);                            // 0x009b3c10
double iat_floor(double x);                                             // 0x011e0906

extern float g_Half;                                                    // 0x01471064 0.5f
extern float g_Eps;                                                     // 0x01447c88 1e-7f
extern float g_OneMinusEps;                                             // 0x01447ccc ~0.99999f
extern float g_ChannelGain;                                             // 0x01447cbc 0.8f
extern int   g_1515dc;                                                  // 0x015515dc

// ------------------------------------------------------------------ tiny records

struct Slot {                                                           // 0x10
    float a, b;
    bool  c, d;
    short e;
    int   pad;                                                          // never written by the ctors
    Slot() : a(0.0f), b(0.0f), c(0), d(0), e(0) {}
};

struct IdBase { int id; IdBase() : id(0) {} };

struct GaitA : IdBase {                                                 // 0x44, vtable 0x01447cc0
    __forceinline GaitA() : x(0.0f), y(0.0f), z(0.0f), s() {}
    virtual void f0();
    float x, y, z;
    Slot  s[3];
};

struct GaitB : IdBase {                                                 // 0x58, vtable 0x01447cc4
    __forceinline GaitB() : a(g_Eps), b(g_Eps), c(g_Eps), d(g_OneMinusEps), s() {}
    virtual void f0();
    float a, b, c, d;
    Slot  s[4];
};

struct GaitCData {                                                      // 0x14
    float x, y, z;
    bool  c0, c1;
    short c2;
    int   pad;                                                          // never written by the ctors
    GaitCData() : x(0.0f), y(0.0f), z(0.0f), c0(0), c1(0), c2(0) {}
    GaitCData(float xv) : x(xv), y(0.0f), z(0.0f), c0(0), c1(0), c2(0) {}
};

struct GaitC {                                                          // 0x18: no vtable of its own
    int id;
    GaitCData d;
    __forceinline GaitC() : id(0), d(g_Half) {}
};

struct Item { float a, b; int c; };                                     // 0x0c

// ------------------------------------------------------------------ vectors

template <class T>
struct Vec {                                                            // 0x14 every T here
    T*   b;
    T*   e;
    T*   cap;
    int  alloc[2];
    Vec() : b(0), e(0), cap(0) {}
    ~Vec() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void reserve(int n);
    void destroy(T* first, T* last);
    void resize(unsigned n, const T& v);                                // Vec<Item> only
};

struct Gait {                                                           // 0x40
    int id;
    Vec<GaitA> a;
    Vec<GaitB> b;
    Vec<GaitC> c;
    Gait();                                                             // 0x009e1030
};

template <> inline Vec<Gait>::~Vec()
{
    destroy(b, e);
    if (b && ((int*)b)[-1]) operator delete[](b);
}

struct Inner;                                                           // 0xa0
struct Entry;                                                           // 0xa4

// ------------------------------------------------------------------ Inner

struct Inner {
    int    f0;                                                          // +0x00 blend flags
    float  f4;                                                          // +0x04
    int    f8;                                                          // +0x08 key index, -1 = unused
    Vec<Item> items;                                                    // +0x0c
    Vec<Gait> gaits;                                                    // +0x20
    float  p[26];                                                       // +0x34 tune values
    bool   flag;                                                        // +0x9c
    Inner();
    Inner(const Inner& o);
    Inner(int index, int count);
    Inner& operator=(const Inner& o);
    void __thiscall Assign(const Inner* o);                             // 0x009dbc60
    void __thiscall AssignItems(const Inner* o);                        // 0x009e1370
    void __thiscall AssignGaits(const Inner* o);                        // 0x009e22f0
    void __thiscall BlendKeys(const Inner* a, float t, const Inner* b); // 0x009e1470
    void __thiscall Blend(const Inner* a, float t, const Inner* b);
};

struct Entry {
    float key;
    Inner in;
    Entry() : key(0.0f) {}
    Entry(const Entry& o);
    Entry& operator=(const Entry& o) { key = o.key; in = o.in; return *this; }
};

struct EntryArr {                                                       // Table + 0x18
    unsigned count;
    Vec<Entry> v;
    void Insert(const Entry* e);                                        // 0x009e4a00
    void Sample(float key, Inner* out);
};

// ------------------------------------------------------------------ channel cell / table

struct ChannelTail { Gait* b; Gait* e; Gait* cap; };                    // +0xa8

struct ChannelHead {                                                    // +0x00 of a channel cell
    float gain;
    bool  on;
    char  pad[3];                                                       // left uninitialised
    ChannelHead() : gain(g_ChannelGain), on(true) {}
};

struct Channel {                                                        // 0xb4
    float       gain;                                                   // +0x00
    bool        on;                                                     // +0x04
    char        pad[3];                                                 // +0x05
    Inner       in;                                                     // +0x08
    ChannelTail tail;                                                   // +0xa8
    Channel();
    void Reset();
};

struct gcmddTable {                                                     // 0x12c0
    int m00;                                                            // +0x00
    int m04[6];                                                         // +0x04
    int   mA[6][4];                                                     // +0x1c integer keys
    float mB[6][4];                                                     // +0x7c
    float mC[6][4];                                                     // +0xdc
    int m13c;                                                           // +0x13c
    Channel channels[24];                                               // +0x140
    Inner   inner;                                                      // +0x1220
    gcmddTable();
    void Reset(int n, int m);
};

struct Path {                                                           // 0x18
    int unknown;                                                        // +0x00 (left alone by the ctor)
    int a;                                                              // +0x04
    int b;                                                              // +0x08
    int c;                                                              // +0x0c
    int d;                                                              // +0x10
    int e;                                                              // +0x14
    Path() : a(0), b(0), c(-1), d(0), e(0) {}
};

namespace Anim {

struct gcmdd : GaitC {                                                  // 0x1c8, vtable 0x01447cc8
    virtual void notify();                                              // vfptr at +0, GaitC base at +4
    GaitB b;                                                            // +0x1c
    GaitA a;                                                            // +0x74
    Path  path;                                                         // +0xb8
    Gait  gait;                                                         // +0xd0
    float f110;                                                         // +0x110
    float f114;                                                         // +0x114
    int   i118;                                                         // +0x118
    Inner inner;                                                        // +0x11c
    float f1bc;                                                         // +0x1bc
    bool  f1c0;                                                         // +0x1c0
    float f1c4;                                                         // +0x1c4
    gcmdd();
};

} // namespace Anim

struct gcmddHost {
    void Create(int unused);
};

// ------------------------------------------------------------------ @ 0x009e3580

void Anim::gcmdd::notify() {}

// @ 0x009e3580
Anim::gcmdd::gcmdd()
    : GaitC(), b(), a(), path(), gait(),
      f110(0.0f), f114(g_Half), i118(0),
      inner(), f1bc(g_ChannelGain), f1c0(true), f1c4(0.0f)
{
}

// ------------------------------------------------------------------ @ 0x009e3740

// @ 0x009e3740
void gcmddHost::Create(int /*unused*/)
{
    void* mem = EAAllocate(0x1c8, "Anim/gcmdd", 0, 0, 0, 0);
    Anim::gcmdd* g = mem ? new (mem) Anim::gcmdd() : 0;
    *(Anim::gcmdd**)((char*)*(void**)((char*)this + 0x30) + 4) = g;
    void* obj = *(void**)((char*)this + 4);
    void** vt = *(void***)obj;
    ((void (__thiscall*)(void*, void*))vt[0x23])(obj, this);
}

// ------------------------------------------------------------------ @ 0x009e3790

// @ 0x009e3790
Inner& Inner::operator=(const Inner& o)
{
    if (this != &o) {
        Assign(&o);
        AssignItems(&o);
        if (g_1515dc) AssignGaits(&o);
    }
    return *this;
}

// ------------------------------------------------------------------ @ 0x009e37c0

// @ 0x009e37c0
void Inner::Blend(const Inner* a, float t, const Inner* b)
{
    if (a->f8 == -1) {
        *this = *b;
        return;
    }
    if (b->f8 == -1) {
        *this = *a;
        return;
    }

    if (!g_1515dc && !(f0 & 0x1))
        f4 = (b->f4 - a->f4) * t + a->f4;

    BlendKeys(a, t, b);

    if (!(f0 & 0x4))       p[0]  = (b->p[0]  - a->p[0])  * t + a->p[0];
    if (!(f0 & 0x8))       p[1]  = (b->p[1]  - a->p[1])  * t + a->p[1];
    if (!(f0 & 0x10))      p[2]  = (b->p[2]  - a->p[2])  * t + a->p[2];
    if (!(f0 & 0x20))      p[3]  = (b->p[3]  - a->p[3])  * t + a->p[3];
    if (!(f0 & 0x40))      p[4]  = (b->p[4]  - a->p[4])  * t + a->p[4];
    if (!(f0 & 0x80))      p[5]  = (b->p[5]  - a->p[5])  * t + a->p[5];
    if (!(f0 & 0x100))     p[6]  = (b->p[6]  - a->p[6])  * t + a->p[6];
    if (!(f0 & 0x200))     p[7]  = (b->p[7]  - a->p[7])  * t + a->p[7];
    if (!(f0 & 0x400))     p[8]  = (b->p[8]  - a->p[8])  * t + a->p[8];
    if (!(f0 & 0x800))     p[9]  = (b->p[9]  - a->p[9])  * t + a->p[9];
    if (!(f0 & 0x1000))    p[10] = (b->p[10] - a->p[10]) * t + a->p[10];
    if (!(f0 & 0x2000000)) p[11] = (b->p[11] - a->p[11]) * t + a->p[11];

    if (!(f0 & 0x2000)) {
        float v = (float)(WrapRange(b->p[12] - a->p[12], 1.0f) * (double)t + (double)a->p[12]);
        p[12] = v - (float)iat_floor((double)v);
    }
    if (!(f0 & 0x4000)) {
        float v = (float)(WrapRange(b->p[13] - a->p[13], 1.0f) * (double)t + (double)a->p[13]);
        p[13] = v - (float)iat_floor((double)v);
    }
    if (!(f0 & 0x8000)) {
        float v = (float)(WrapRange(b->p[14] - a->p[14], 1.0f) * (double)t + (double)a->p[14]);
        p[14] = v - (float)iat_floor((double)v);
    }

    if (!(f0 & 0x10000))     p[15] = (b->p[15] - a->p[15]) * t + a->p[15];
    if (!(f0 & 0x8000000))   p[16] = (b->p[16] - a->p[16]) * t + a->p[16];
    if (!(f0 & 0x10000000))  p[17] = (b->p[17] - a->p[17]) * t + a->p[17];
    if (!(f0 & 0x20000))     p[18] = (b->p[18] - a->p[18]) * t + a->p[18];
    if (!(f0 & 0x40000))     p[19] = (b->p[19] - a->p[19]) * t + a->p[19];

    if (!(f0 & 0x80000)) {
        float v = (float)(WrapRange(b->p[20] - a->p[20], 1.0f) * (double)t + (double)a->p[20]);
        p[20] = v - (float)iat_floor((double)v);
    }
    if (!(f0 & 0x100000)) {
        float v = (float)(WrapRange(b->p[21] - a->p[21], 1.0f) * (double)t + (double)a->p[21]);
        p[21] = v - (float)iat_floor((double)v);
    }
    if (!(f0 & 0x200000)) {
        float v = (float)(WrapRange(b->p[22] - a->p[22], 1.0f) * (double)t + (double)a->p[22]);
        p[22] = v - (float)iat_floor((double)v);
    }

    if (!(f0 & 0x400000))    p[23] = (b->p[23] - a->p[23]) * t + a->p[23];
    if (!(f0 & 0x800000))    p[24] = (b->p[24] - a->p[24]) * t + a->p[24];
    if (!(f0 & 0x1000000))   p[25] = (b->p[25] - a->p[25]) * t + a->p[25];
}

// ------------------------------------------------------------------ @ 0x009e3cf0

// @ 0x009e3cf0
Channel::Channel()
    : gain(g_ChannelGain), on(true), in()
{
    ChannelHead head;
    *(ChannelHead*)this = head;
    Inner def;
    in = def;
    tail.b = 0;
    tail.e = 0;
    tail.cap = 0;
}

// ------------------------------------------------------------------ @ 0x009e3de0

// @ 0x009e3de0
void Channel::Reset()
{
    ChannelHead head;
    *(ChannelHead*)this = head;
    Inner def;
    in = def;
    tail.b = 0;
    if (tail.e) tail.e = 0;
    if (tail.cap) tail.cap = 0;
}

// ------------------------------------------------------------------ @ 0x009e3ec0

// @ 0x009e3ec0
gcmddTable::gcmddTable()
    : m00(0), m13c(0), channels(), inner()
{
    for (int a = 0; a < 6; a++) {
        for (int k = 0; k < 4; k++) {
            mB[a][k] = 0.0f;
            mC[a][k] = 0.0f;
            mA[a][k] = 0;
            channels[a * 4 + k].Reset();
        }
        m04[a] = 0;
    }
}

// ------------------------------------------------------------------ @ 0x009e3f70

// @ 0x009e3f70
void gcmddTable::Reset(int n, int m)
{
    if (n > 0) {
        for (int a = 0; a < n; a++) {
            for (int k = 0; k < m; k++) {
                mB[a][k] = 0.0f;
                mC[a][k] = 0.0f;
                if (mA[a][k] != 0) mA[a][k] = 0;
                channels[a * 4 + k].Reset();
            }
            m04[a] = 0;
        }
    }
    m13c = 0;
}

// ------------------------------------------------------------------ @ 0x009e4030

// @ 0x009e4030
void EntryArr::Sample(float key, Inner* out)
{
    unsigned count = this->count;
    unsigned prev = 0;
    unsigned i = 0;

    if (count != 0) {
        for (; i < count; i++) {
            if (key < v.b[i].key)
                break;
            prev = i;
        }
        if (i != 0 && i != count) {
            Entry* e0 = &v.b[prev];
            Entry* e1 = &v.b[i];
            out->Blend(&e0->in, (key - e0->key) / (e1->key - e0->key), &e1->in);
            goto tail;
        }
    }
    *out = v.b[prev].in;
tail:
    out->flag = key == v.b[prev].key;
}

// ------------------------------------------------------------------ @ 0x009e4120

// @ 0x009e4120
Inner::Inner(const Inner& o)
{
    items.b = items.e = items.cap = 0;
    gaits.b = gaits.e = gaits.cap = 0;
    Assign(&o);
    AssignItems(&o);
    if (g_1515dc) AssignGaits(&o);
}

Entry::Entry(const Entry& o)
    : key(o.key), in(o.in)
{
}

// ------------------------------------------------------------------ @ 0x009e4170

// @ 0x009e4170
void EntryConstructN(Entry* dst, unsigned n, const Entry* src)
{
    for (; n != 0; n--, dst++) {
        if (dst) {
            dst->key = src->key;
            dst->in.items.b = dst->in.items.e = dst->in.items.cap = 0;
            dst->in.gaits.b = dst->in.gaits.e = dst->in.gaits.cap = 0;
            dst->in.Assign(&src->in);
            dst->in.AssignItems(&src->in);
            if (g_1515dc) dst->in.AssignGaits(&src->in);
        }
    }
}

// ------------------------------------------------------------------ @ 0x009e41e0

// @ 0x009e41e0
void EntryAssignRange(Entry* first, Entry* last, Entry* dst)
{
    for (; first != last; first++, dst++) {
        if (dst) {
            dst->key = first->key;
            if (&dst->in != &first->in) {
                dst->in.Assign(&first->in);
                dst->in.AssignItems(&first->in);
                if (g_1515dc) dst->in.AssignGaits(&first->in);
            }
        }
    }
}

// ------------------------------------------------------------------ @ 0x009e4260

// @ 0x009e4260
Entry* EntryCopy(Entry* first, Entry* last, Entry* dst)
{
    for (; first != last; first++, dst++) {
        dst->key = first->key;
        if (&dst->in != &first->in) {
            dst->in.Assign(&first->in);
            dst->in.AssignItems(&first->in);
            if (g_1515dc) dst->in.AssignGaits(&first->in);
        }
    }
    return dst;
}

// ------------------------------------------------------------------ @ 0x009e42d0

// @ 0x009e42d0
Entry* EntryCopyBackward(Entry* first, Entry* last, Entry* dstEnd)
{
    while (last != first) {
        --last;
        --dstEnd;
        dstEnd->key = last->key;
        if (&dstEnd->in != &last->in) {
            dstEnd->in.Assign(&last->in);
            dstEnd->in.AssignItems(&last->in);
            if (g_1515dc) dstEnd->in.AssignGaits(&last->in);
        }
    }
    return dstEnd;
}

// ------------------------------------------------------------------ @ 0x009e4350

// @ 0x009e4350
Inner::Inner(int index, int count)
    : items(), gaits()
{
    *this = Inner();
    f8 = index;
    items.reserve(count);
    Item def = {0.0f, 0.5f, 0};
    items.resize(count, def);
    if (g_1515dc) gaits.reserve(count);
}
