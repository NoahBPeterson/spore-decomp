// slice s009e4450 -- the gait-key vector family (0xa4-byte Entry), the 0x30 "gcmdst"
// object, the 0x12c0 gait-sample table, and the gait/anim helpers that build them.
//
//   009e4450  GaitTable::Sample(float, int lane, bool first, unsigned mask)  thiscall 4 args ret 0x10
//   009e4600  GaitTable::SampleAt(...)                                      thiscall 7 args ret 0x1c
//   009e4630  VecEntry::VecEntry(unsigned n, const Entry&)                  thiscall 2 args ret 8
//   009e47c0  VecEntry::realloc_insert(Entry*, const Entry&)                thiscall 2 args ret 8
//   009e4940  EntryArr::Reset()                                             thiscall          ret
//   009e4990  VecEntry::insert(Entry*, const Entry&)                        thiscall 2 args ret 8
//   009e4a00  EntryArr::Insert(const Entry*)                                thiscall 1 arg  ret 4
//   009e4aa0  Gcmdst::ResetDefault()                                        thiscall          ret
//   009e4c00  Gcmdst::BuildFromSource(const void*)                          thiscall 1 arg  ret 4
//   009e4e30  gait_record_static_data::ReadFromText()                       thiscall          ret
//
// Normal region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint32;

inline void* operator new(unsigned, void* p) { return p; }
void  operator delete[](void* p);                                       // 0x00f47380
void* EAAllocate(unsigned size, const char* tag, int a, int b, int* allocator, int line);  // 0x00f473a0

extern float g_Half;                                                    // 0x01471064 0.5f
extern float g_Eps;                                                     // 0x01447c88 1e-7f
extern float g_OneMinusEps;                                             // 0x01447ccc ~0.99999f
extern float g_ChannelGain;                                             // 0x01447cbc 0.8f
extern float g_Zero;                                                    // 0x01485378 0.0f
extern float g_One;                                                     // 0x01485720 1.0f
extern int   g_1515dc;                                                  // 0x015515dc
extern int   g_alloc;                                                   // 0x013ebb38 (allocator)

void* ArgScriptCreateParser();                                          // 0x008408d0

// ------------------------------------------------------------------ tiny records

struct Slot {                                                           // 0x10
    float a, b;
    bool  c, d;
    short e;
    int   pad;
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
    int   pad;
    GaitCData() : x(0.0f), y(0.0f), z(0.0f), c0(0), c1(0), c2(0) {}
    GaitCData(float xv) : x(xv), y(0.0f), z(0.0f), c0(0), c1(0), c2(0) {}
};

struct GaitC {                                                          // 0x18
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
    void resize(unsigned n, const T& v);
};

struct Gait {                                                           // 0x40
    int id;
    Vec<GaitA> a;
    Vec<GaitB> b;
    Vec<GaitC> c;
    Gait();
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
    void __thiscall AssignItemsN(const Inner* o, unsigned n);           // 0x009e1160
    void __thiscall AssignGaits(const Inner* o);                        // 0x009e22f0
    void __thiscall AssignGaitsN(const Inner* o, unsigned n);           // 0x009e1fe0
    void __thiscall AssignGaitsF(const Inner* o, unsigned n);           // 0x009e2140
    void __thiscall CopyMasked(const Inner* o, unsigned mask);          // 0x009dba90
    void __thiscall CopyItems(const Inner* o, unsigned mask);           // 0x009e1260
    void __thiscall BlendKeys(const Inner* a, float t, const Inner* b); // 0x009e1470
    void __thiscall Blend(const Inner* a, float t, const Inner* b);     // 0x009e37c0
    bool __thiscall ValidBlocks();                                      // 0x009de630
};

struct Entry {
    float key;
    Inner in;
    Entry() : key(0.0f) {}
    Entry(const Entry& o);                                              // 0x009e4120
};

void  EntryConstructN(Entry* dst, unsigned n, const Entry* src, int extra);   // 0x009e4170
Entry* EntryAssignRange(Entry* first, Entry* last, Entry* result);            // 0x009e41e0
Entry* EntryCopy(Entry* first, Entry* last, Entry* result);                   // 0x009e4260
Entry* EntryCopyBackward(Entry* first, Entry* last, Entry* result);           // 0x009e42d0
Entry* DestroyRangeA4(Entry* first, Entry* last, Entry* result);              // 0x009e07d0

// ------------------------------------------------------------------ the 0x14-byte vector of Entry

struct VecEntry {                                                       // 0x14
    Entry* b;
    Entry* e;
    Entry* cap;
    int    alloc[2];
    VecEntry();
    VecEntry(unsigned n, const Entry& v);                               // 0x009e4630
    ~VecEntry() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void __thiscall reserve(int n);                                     // 0x009e4700
    Entry* __thiscall insert(Entry* pos, const Entry& value);           // 0x009e4990
    void __thiscall realloc_insert(Entry* pos, const Entry& value);     // 0x009e47c0
    void __thiscall destroyRange(Entry* first, Entry* last);            // 0x009e0b90
};

struct EntryArr {                                                       // Table + 0x18
    unsigned count;
    VecEntry v;
    void Insert(const Entry* e);                                        // 0x009e4a00
    void Reset();                                                       // 0x009e4940
    void Sample(float key, Inner* out);                                 // 0x009e4030
    float Lookup(float key, Inner** out);                              // 0x009dd480
};

// ------------------------------------------------------------------ the 0x30 "gcmdst" object

struct Elem0C {                                                         // 0x0c
    float v0;
    float v1;
    bool  flag;
    char  pad[3];
};

struct Vec0C {                                                          // 0x14
    Elem0C* b;
    Elem0C* e;
    Elem0C* cap;
    int     alloc[2];
    Vec0C() : b(0), e(0), cap(0) {}
    ~Vec0C() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void reserve(int n);                                                // 0x009df800
    Elem0C* erase(Elem0C* first, Elem0C* last);                         // 0x009e0480
};

struct Gcmdst {                                                         // 0x30
    unsigned count;                                                     // +0x00
    Vec0C    v;                                                         // +0x04
    EntryArr arr;                                                       // +0x18
    Gcmdst() : count(0) {}
    void __thiscall AddElem(const Elem0C& e);                           // 0x009e1610
    void __thiscall ResetDefault();                                     // 0x009e4aa0
    void __thiscall BuildFromSource(const void* src);                   // 0x009e4c00
};

// ------------------------------------------------------------------ the 0x12c0 gait-sample table

struct CurveOut { float v; bool flag; char pad[3]; };

struct Curve {                                                          // the record's curve part
    void __thiscall Eval(float t, CurveOut* out);                       // 0x009dbf10
};

struct CurveNode {                                                      // what mCurves[][] points at
    char     pad[0x18];                                                 // +0x00 the curve record
    EntryArr arr;                                                       // +0x18 the key list
};

struct ChannelTail {                                                    // +0xa8
    float  gain;
    Inner* a;
    Inner* b;
};

struct Channel {                                                        // 0xb4
    float       gain;                                                   // +0x00
    bool        on;                                                     // +0x04
    char        pad[3];                                                 // +0x05
    Inner       in;                                                     // +0x08
    ChannelTail tail;                                                   // +0xa8
    bool __thiscall ValidBlocks();                                      // 0x009de630
};

struct GaitTable {                                                      // 0x12c0
    int        mGroups;                                                 // +0x00
    int        m04[6];                                                  // +0x04
    CurveNode* mCurves[6][4];                                           // +0x1c
    int        m7c[49];                                                 // +0x7c
    Channel    channels[24];                                            // +0x140
    Inner      inner;                                                   // +0x1220
    void Sample(float t, int lane, bool first, unsigned mask);          // 0x009e4450
    void SampleAt(float, float, float, int, int, int, int lane);        // 0x009e4600
};

float __stdcall CurveClamp2(float* v);                                  // 0x009dc7a0

struct GaitRecordStatic {
    char ReadFromText();                                                // 0x009e4e30
};

// ============================================================================
// definitions
// ============================================================================

// @ 0x009e4600
void GaitTable::SampleAt(float a0, float a1, float a2, int a3, int a4, int a5, int lane)
{
    float v = CurveClamp2(&a0);
    Sample(v, lane, false, 0);
}

// @ 0x009e4630
VecEntry::VecEntry(unsigned n, const Entry& v)
{
    Entry* p;
    if (n != 0) {
        p = (Entry*)EAAllocate(n * 0xa4, "Anim/gait/untagged", 0, 0, &g_alloc, 0xd1);
    } else {
        p = 0;
    }
    cap = p + n;
    b = p;
    e = p;
    {
        Entry def;
        int extra;
        EntryConstructN(b, n, &def, extra);
    }
    e = b + n;
}

// @ 0x009e4940
void EntryArr::Reset()
{
    VecEntry* vec = &v;
    Entry* first = vec->b;
    Entry* last  = vec->e;
    Entry* r = EntryCopy(last, last, first);
    vec->destroyRange(r, vec->e);
    vec->e -= last - first;
    count = 0;
}

// @ 0x009e4990
Entry* VecEntry::insert(Entry* pos, const Entry& value)
{
    unsigned idx = (unsigned)(pos - b);
    Entry* slot = e;
    if (pos == slot && slot != cap) {
        e = slot + 1;
        if (slot) {
            new (slot) Entry(value);
        }
    } else {
        realloc_insert(pos, value);
    }
    return b + idx;
}

// @ 0x009e4a00
void EntryArr::Insert(const Entry* val)
{
    unsigned n = count;
    unsigned i = 0;
    if (n != 0) {
        Entry* p = v.b;
        do {
            if (p->key >= val->key) break;
            i++;
            p++;
        } while (i < n);
    }
    if (i < n) {
        Entry* p = v.b + i;
        float key = val->key;
        if (p->key == key) {
            p->key = key;
            const Inner* src = &val->in;
            if (&p->in != src) {
                p->in.Assign(src);
                p->in.AssignItems(src);
                if (g_1515dc != 0) p->in.AssignGaits(src);
            }
            return;
        }
    }
    v.insert(v.b + i, *val);
    count++;
}

// @ 0x009e47c0
void VecEntry::realloc_insert(Entry* pos, const Entry& value)
{
    if (e != cap) {
        Entry* val = (Entry*)&value;
        if (val >= pos && val < e) {
            val = val + 1;
        }
        if (e != 0) {
            new (e) Entry(*(e - 1));
        }
        EntryCopyBackward(pos, e - 1, e);
        pos->key = val->key;
        Inner* dst = &pos->in;
        const Inner* src = &val->in;
        if (dst != src) {
            dst->Assign(src);
            dst->AssignItems(src);
            if (g_1515dc != 0) dst->AssignGaits(src);
        }
        e = e + 1;
        return;
    }

    int old = (int)(e - b);
    int ncap;
    if (old == 0) {
        ncap = 1;
    } else {
        ncap = old * 2;
    }
    Entry* buf;
    if (ncap == 0) {
        buf = 0;
    } else {
        buf = (Entry*)EAAllocate(ncap * 0xa4, "Anim/gait/untagged", 0, 0, &g_alloc, 0xd1);
    }
    Entry* p = EntryAssignRange(b, pos, buf);
    DestroyRangeA4(b, pos, buf);
    if (p) {
        new (p) Entry(value);
    }
    Entry* q = EntryAssignRange(pos, e, p + 1);
    DestroyRangeA4(pos, e, p + 1);
    if (b && ((int*)b)[-1]) operator delete[](b);
    b = buf;
    e = q;
    cap = buf + ncap;
}

// @ 0x009e4aa0
void Gcmdst::ResetDefault()
{
    v.erase(v.b, v.e);

    Elem0C elem;
    elem.v0 = 0.0f;
    elem.v1 = 0.8f;
    elem.flag = true;

    count = 0;
    AddElem(elem);
    arr.Reset();

    Inner tmpA;
    Entry tmp;
    tmp.in.Assign(&tmpA);
    tmp.in.AssignItems(&tmpA);
    if (g_1515dc != 0) tmp.in.AssignGaits(&tmpA);
    arr.Insert(&tmp);
}

// @ 0x009e4c00
void Gcmdst::BuildFromSource(const void* src)
{
    char* s = (char*)src;

    unsigned n = (unsigned)((*(int*)(s + 0x0c) - *(int*)(s + 0x08)) >> 2);
    v.reserve((int)n);
    for (unsigned i = 0; i < n; i++) {
        char* e = *(char**)(*(int*)(s + 0x08) + i * 4);
        Elem0C elem;
        elem.v0 = *(float*)(e + 0x1c4);
        elem.v1 = *(float*)(e + 0x1bc);
        elem.flag = *(bool*)(e + 0x1c0);
        AddElem(elem);
    }

    unsigned m = (unsigned)((*(int*)(s + 0x20) - *(int*)(s + 0x1c)) >> 2);
    arr.v.reserve((int)m);
    for (unsigned j = 0; j < m; j++) {
        char* e = *(char**)(*(int*)(s + 0x1c) + j * 4);
        float key = *(float*)(e + 0x1c4);
        const Inner* sin = (const Inner*)(e + 0x11c);
        unsigned cnt = (unsigned)((*(int*)(e + 0x12c) - *(int*)(e + 0x128)) / 0xc);

        Inner a;
        a.Assign(sin);
        a.AssignItemsN(sin, cnt);
        if (g_1515dc != 0) a.AssignGaitsN(sin, cnt);

        Entry entry;
        entry.key = key;
        entry.in.Assign(&a);
        entry.in.AssignItems(&a);
        if (g_1515dc != 0) entry.in.AssignGaits(&a);
        arr.Insert(&entry);
    }
}

// @ 0x009e4450
void GaitTable::Sample(float t, int lane, bool first, unsigned mask)
{
    if (!first && mCurves[0][lane] != 0) {
        CurveOut out;
        out.v = g_ChannelGain;
        out.flag = true;
        ((Curve*)mCurves[0][lane])->Eval(t, &out);
        *(CurveOut*)&channels[lane].gain = out;
    }

    if (mGroups <= 0) return;

    CurveNode** pp = &mCurves[0][lane];
    Channel*    ch = channels + lane;
    int k = 0;
    do {
        CurveNode* node = *pp;
        if (node != 0) {
            if ((ch->in.f0 & 0x4000000) == 0) {
                ch->tail.gain = node->arr.Lookup(t, &ch->tail.a);
            }
            if (g_1515dc != 0 && ch->ValidBlocks()) {
                inner.Blend(ch->tail.a, ch->tail.gain, ch->tail.b);
                if (ch->tail.gain == g_Zero || ch->tail.gain == g_One) {
                    inner.flag = true;
                } else {
                    inner.flag = false;
                }
            } else {
                node->arr.Sample(t, &inner);
            }
            if (mask != 0) {
                ch->in.CopyMasked(&inner, mask);
                ch->in.CopyItems(&inner, mask);
                if (g_1515dc != 0) ch->in.AssignGaitsF(&inner, mask);
            } else {
                ch->in.Assign(&inner);
                ch->in.AssignItems(&inner);
                if (g_1515dc != 0) ch->in.AssignGaits(&inner);
            }
            ch->in.f0 = (int)mask;
        }
        pp += 4;
        ch += 4;
        k++;
    } while (k < mGroups);
}

// @ 0x009e4e30
char GaitRecordStatic::ReadFromText()
{
    void* parser;
    Gcmdst* g = (Gcmdst*)EAAllocate(0x30, "Anim/gcmdst", 0, 0, 0, 0);
    if (g) {
        g->count = 0;
        g->v.b = g->v.e = g->v.cap = 0;
        g->arr.count = 0;
        g->arr.v.b = g->arr.v.e = g->arr.v.cap = 0;
    } else {
        g = 0;
    }

    parser = ArgScriptCreateParser();
    if (parser) {
        void** vt = *(void***)parser;
        ((void (__thiscall*)(void*))vt[0])(parser);
        ((void (__thiscall*)(void*))vt[2])(parser);
        ((void (__thiscall*)(void*))vt[0x28 / 4])(parser);

        Gcmdst* k2 = (Gcmdst*)EAAllocate(0x34, "Anim/slkblkcmd", 0, 0, 0, 0);
        if (k2) { k2->count = 0; }
        ((void (__thiscall*)(void*, const char*))vt[0x14 / 4])(parser, "steplengthkey");

        Gcmdst* k3 = (Gcmdst*)EAAllocate(0x34, "Anim/ggkblkcmd", 0, 0, 0, 0);
        if (k3) { k3->count = 0; }
        ((void (__thiscall*)(void*, const char*))vt[0x14 / 4])(parser, "gaitgroupkey");

        ((void (__thiscall*)(void*))vt[0x30 / 4])(parser);
        ((void (__thiscall*)(void*, int))vt[0x34 / 4])(parser, 1);
        ((void (__thiscall*)(void*))vt[3])(parser);
        ((void (__thiscall*)(void*))vt[1])(parser);
    }

    if (g == 0) {
        return 0;
    }
    g->ResetDefault();
    return 0;
}
