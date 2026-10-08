// Slice s009e5070: Anim "gait" table loader (0x009e5070, 1577 bytes, thiscall(Table*, const Src*), ret 4).
//
// Reads a flat, memory-mapped record stream (Src) and builds the in-memory table: for every record
// it fills a default-constructed Inner (scalars, the 12-byte items list and the nested Gait list,
// each Gait with its GaitA/GaitB/GaitC key lists) and inserts a {key, Inner} Entry, keyed by the
// record's float key, into the sorted array at Table+0x18.
// Types/classes shared with the BuildGaits slice (s009e2490). Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

inline void* operator new(unsigned, void* p) { return p; }
void operator delete[](void*);   // 0x00f47380

struct Slot {            // 16 bytes
    float a, b;
    bool c, d;
    short e;
    int pad;
};

struct IdBase { int id; };

struct GaitA : IdBase {  // 0x44, vtable 0x01447cc0
    virtual void f0();
    float x, y, z;
    Slot s[3];
};

struct GaitB : IdBase {  // 0x58, vtable 0x01447cc4
    virtual void f0();
    float a, b, c, d;
    Slot s[4];
};

struct GaitCData {       // copied as one block of dwords
    float x, y, z;
    bool c0, c1;
    short c2;
    int pad;
};

struct GaitC : IdBase {  // 0x1c, vtable 0x01447cc8
    virtual void f0();
    GaitCData d;
};

struct Item { float a, b; int c; };   // 12 bytes

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
    void destroy(T* first, T* last);
    void push_back(const T& v) {
        if (e < cap) { T* p = e++; ::new((void*)p) T(v); }
        else realloc_insert(e, v);
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

template <> inline Vec<Gait>::~Vec() { destroy(b, e); if (b && ((int*)b)[-1]) operator delete[](b); }

struct Inner {           // 0xa0
    int f0;
    float f4;
    int f8;
    Vec<Item> items;     // +0x0c
    Vec<Gait> gaits;     // +0x20
    float p[26];         // +0x34
    bool flag;           // +0x9c
    Inner();                                 // 0x009e1df0
    __declspec(noinline) void __thiscall Assign(const Inner* o);   // 0x009dbc60 scalars (body below: lets cl see ecx survive)
    void __thiscall AssignItems(const Inner* o);   // 0x009e1370 items list
    void __thiscall AssignGaits(const Inner* o);   // 0x009e22f0 gaits list (only if g_AssignGaits)
};

// Same-TU body, as in the original TU (stdcall-like: ret 4, ecx kept).
void __thiscall Inner::Assign(const Inner* o)
{
    f0 = o->f0;
    f4 = o->f4;
    f8 = o->f8;
    for (int i = 0; i < 26; i++) p[i] = o->p[i];
    flag = o->flag;
}

extern int g_AssignGaits;   // 0x015515dc

struct Entry {           // 0xa4
    float key;
    Inner in;
};

struct EntryArr {        // at Table+0x18
    unsigned count;
    Vec<Entry> v;
    void __thiscall Insert(const Entry* e);   // 0x009e4a00
};

struct Src {             // flat resource header
    char pad[0x10];
    int n10;
    unsigned count;      // +0x14
    // records follow at +0x18 + n10 * 8
};

struct RItem { float a, b; };

struct Rec {             // flat input record (variable length)
    float key;           // +0
    float f4;
    int f8;
    float p[26];         // +0x0c
    unsigned nItems;     // +0x74
    unsigned nGaits;     // +0x78
    RItem items[1];      // +0x7c
};

struct GRec {            // flat nested gait header, followed by nA GaitA, nB GaitB, nC GaitC
    unsigned nA, nB, nC;
};

struct Table {
    char pad[0x18];
    EntryArr arr;        // +0x18
    void __thiscall Load(const Src* s);   // 0x009e5070
};

// @ 0x009e5070
void __thiscall Table::Load(const Src* s)
{
    arr.v.reserve(s->count);
    const Rec* r = (const Rec*)((const char*)s + 0x18 + s->n10 * 8);
    for (unsigned i = 0; i < s->count; i++) {
        float key = r->key;
        Inner in;
        in.f4 = r->f4;
        in.p[0] = r->p[0];
        in.p[1] = r->p[1];
        in.p[2] = r->p[2];
        in.p[3] = r->p[3];
        in.p[4] = r->p[4];
        in.p[5] = r->p[5];
        in.p[6] = r->p[6];
        in.p[7] = r->p[7];
        in.p[8] = r->p[8];
        in.p[9] = r->p[9];
        in.p[10] = r->p[10];
        in.p[11] = r->p[11];
        in.p[12] = r->p[12];
        in.p[13] = r->p[13];
        in.p[14] = r->p[14];
        in.p[15] = r->p[15];
        in.p[16] = r->p[16];
        in.p[17] = r->p[17];
        in.p[18] = r->p[18];
        in.p[19] = r->p[19];
        in.p[20] = r->p[20];
        in.p[21] = r->p[21];
        in.p[22] = r->p[22];
        in.p[23] = r->p[23];
        in.p[24] = r->p[24];
        in.p[25] = r->p[25];
        in.f8 = r->f8;
        in.flag = true;
        in.items.reserve(r->nItems);
        const RItem* ri = r->items;
        for (unsigned k = 0; k < r->nItems; k++, ri++) {
            Item it;
            it.a = ri->a;
            it.b = ri->b;
            it.c = 0;
            in.items.push_back(it);
        }
        in.gaits.reserve(r->nGaits);
        const GRec* gr = (const GRec*)ri;
        for (unsigned gi = 0; gi < r->nGaits; gi++) {
            Gait g;
            g.a.reserve(gr->nA);
            const char* q = (const char*)(gr + 1);
            for (unsigned k = 0; k < gr->nA; k++, q += sizeof(GaitA))
                g.a.push_back(*(const GaitA*)q);
            g.b.reserve(gr->nB);
            for (unsigned k = 0; k < gr->nB; k++, q += sizeof(GaitB))
                g.b.push_back(*(const GaitB*)q);
            g.c.reserve(gr->nC);
            for (unsigned k = 0; k < gr->nC; k++, q += sizeof(GaitC))
                g.c.push_back(*(const GaitC*)q);
            in.gaits.push_back(g);
            gr = (const GRec*)q;
        }
        Entry e;
        e.key = key;
        e.in.Assign(&in);
        e.in.AssignItems(&in);
        if (g_AssignGaits) e.in.AssignGaits(&in);
        arr.Insert(&e);
        r = (const Rec*)gr;
    }
}
