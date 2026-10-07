// Anim gait table builder (allocator tag "Anim/gait/untagged"): for every entry of the
// owner's table, fills one default Gait per 12-byte item with three key lists (A/B/C),
// then renumbers the items.  Built /O2 /arch:SSE.
#include <math.h>
#pragma intrinsic(sqrt)

inline void* operator new(unsigned, void* p) { return p; }
void operator delete[](void*);   // 0x00f47380

struct Slot {            // 16 bytes
    float a, b;
    bool c, d;
    short e;
    int pad;
    Slot() : a(0.0f), b(0.0f), c(false), d(false), e(0) {}
};

struct GaitA {           // 0x44
    virtual void f0();   // 0x009dc410 (vtable 0x01447cc0)
    int id;
    float x, y, z;
    Slot s[3];
    GaitA(int i, float px, float py, float pz) : id(i), x(px), y(py), z(pz) {}
};

struct GaitB {           // 0x58
    virtual void f0();   // 0x009dc4f0 (vtable 0x01447cc4)
    int id;
    float a, b, c, d;
    Slot s[4];
    GaitB(int i, float pa, float pb, float pc, float pd) : id(i), a(pa), b(pb), c(pc), d(pd) {}
};

struct GaitC {           // 0x1c
    virtual void f0();   // 0x009dba20 (vtable 0x01447cc8)
    int id;
    float x, y, z;
    bool c0, c1;
    short c2;
    int pad;
    GaitC(int i, float px) : id(i), x(px), y(0.0f), z(0.0f), c0(false), c1(false), c2(0) {}
};

template <class T> T* vcopy(T* first, T* last, T* dest);   // eastl::copy (cdecl); instances: symbols/slices/s009e2490.txt

template <class T>
struct Vec {             // 0x14 bytes: begin/end/cap + 8-byte allocator
    T* b;
    T* e;
    T* cap;
    int alloc[2];
    Vec() : b(0), e(0), cap(0) {}
    ~Vec() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void realloc_insert(T* pos, const T& v);   // per-instance addresses: symbols/slices/s009e2490.txt
    void reserve(int n);
    void assign(const Vec& o);
    void push_back(const T& v) {
        if (e < cap) { T* p = e++; ::new((void*)p) T(v); }
        else realloc_insert(e, v);
    }
    void clear() {
        T* f = b; T* l = e;
        vcopy(l, e, f);
        e -= (l - f);
    }
    void clear2() {
        T* f = b; T* l = e;
        e -= (l - f);
    }
};

struct Gait {            // 0x40
    int id;
    Vec<GaitA> a;
    Vec<GaitB> b;
    Vec<GaitC> c;
    Gait();   // 0x009e1030
    Gait(const Gait& o) : id(o.id) { a.assign(o.a); b.assign(o.b); c.assign(o.c); }
};

struct Item { int x, y, idx; };

struct Inner {
    int pad1[3];
    Item* ib;            // +0xc
    Item* ie;
    int pad2[3];
    Vec<Gait> gaits;     // +0x20
    int pad3[(0xa0 - 0x20 - 0x14) / 4];
};

struct Entry {           // 0xa4
    int pad0;
    Inner in;
};

struct Table {
    char pad[0x18];
    int count;
    Entry* entries;
};

// @ 0x009E2490
void __stdcall BuildGaits(Table* t)
{
    if (!t) return;
    int count = t->count;
    if (count == 0) return;
    for (int i = 0; i < count; i++) {
        Inner* en = &t->entries[i].in;
        if ((int)((char*)en->gaits.e - (char*)en->gaits.b) & ~0x3f) continue;
        int n = (int)(en->ie - en->ib);
        en->gaits.reserve(n);
        for (int j = 0; j < n; j++) {
            float s84 = (float)sqrt(0.84f);
            float s91 = (float)sqrt(0.91f);
            Gait g;
            g.a.clear2();
            g.a.push_back(GaitA(0, 0.0f, 1.0f, 0.0f));
            g.a.push_back(GaitA(0x19, 0.0f, 0.0f, 1.0f));
            g.a.push_back(GaitA(0x32, 0.0f, -1.0f, 0.0f));
            {
                GaitA* last = g.a.e - 1;
                for (int k = 0; k < 3; k++) { last->s[k].c = true; last->s[k].d = true; last->s[k].e = 1; }
            }
            g.a.push_back(GaitA(100, 0.0f, 1.0f, 0.0f));
            g.b.clear2();
            g.b.push_back(GaitB(0, 1e-6f, 1e-6f, 1e-6f, 0.999999f));
            g.b.push_back(GaitB(0xc, 0.4f, 1e-6f, 1e-6f, s84));
            g.b.push_back(GaitB(0x19, 1e-6f, 1e-6f, 1e-6f, 0.999999f));
            g.b.push_back(GaitB(0x26, -0.3f, 1e-6f, 1e-6f, s91));
            g.b.push_back(GaitB(0x32, 1e-6f, 1e-6f, 1e-6f, 0.999999f));
            g.b.push_back(GaitB(100, 1e-6f, 1e-6f, 1e-6f, 0.999999f));
            g.c.clear();
            g.c.push_back(GaitC(0, 0.5f));
            g.c.push_back(GaitC(5, 0.75f));
            g.c.push_back(GaitC(0x19, 0.05f));
            g.c.push_back(GaitC(0x2d, 0.75f));
            g.c.push_back(GaitC(0x32, 0.5f));
            {
                GaitC* last = g.c.e - 1;
                last->c0 = true; last->c1 = true; last->c2 = 1;
            }
            g.c.push_back(GaitC(100, 0.5f));
            en->gaits.push_back(g);
        }
    }
    for (int i = 0; i < count; i++) {
        Inner* en = &t->entries[i].in;
        int n = (int)(en->ie - en->ib);
        for (int j = 0; j < n; j++) en->ib[j].idx = j;
    }
}
