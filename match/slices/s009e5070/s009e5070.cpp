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

// ==================================================================
// gold7 batch id "s009e5070" -- the nSPCreatureAnim "gcmdst" cluster:
//
//   009e56a0  Gcmdst constructor (zero + VecEntry + ResetDefault)
//   009e56d0  guild-gait builder: sample the walk table into a fresh Gcmdst
//   009e59b0  nSPCreatureAnim::ReadGaitRecordStaticDataFromStreamWrapper
//   009e5b40  gait-record lookup-or-build from the global name tree
//   009e5c00  Quake fast inverse-sqrt (0x5f375a86 seed)
//   009e5c30  Matrix33Template<float,0>::Multiply (3x3 basis product)
// ==================================================================

void  EAAllocateEx(void);   // declared only to keep the tag strings below reachable

typedef unsigned int uint32;

// RandomLinearCongruential state (0x0c) used by the animation sampler.
struct Rng { int a, b, c; };

// The game's random-bytes request: fills the 4-byte {min,max} delta range.
struct RandRange { int m0; int m1; };
RandRange RandomBytes(RandRange r);      // 0x00936050, C++ mangled wrapper

int*  GameData_AnimItemBegin(void* gameData);    // 0x009ce420 (returns &vec)
int*  GameData_AnimItemEnd(void* gameData);
float GameData_AnimSampleRange(void* gameData);  // 0x00c370d0
int*  GetAnimWalkTable(void* gameData);          // 0x00ff3ba0

uint32 HashName(const char* s, uint32 basis, int one);                   // 0x00932e80 FNV-1a
void   LCG_SetSeed(Rng* lcg, uint32 seed);                               // 0x00936090
float  LCG_RandomDoubleUniform(Rng* lcg);                                // 0x009360d0
extern "C" double iat_floor(double);                                     // 0x011e0906
void*  EAAllocate(unsigned size, const char* tag, int a, int b, int* allocator, int line); // 0x00f473a0
int    FUN_009d0c80(int a, int b);                                       // 0x009d0c80

extern void* g_name_map;        // 0x0166c06c name -> object map

// ------------------------------------------------------------------ Entry vector + gcmdst

struct Elem0C;   // defined with Vec0C below

struct VecEntry {           // 0x14 (POD: the 2-arg Construct does the real init)
    Entry* b;
    Entry* e;
    Entry* cap;
    int    alloc[2];
    VecEntry() {}
    VecEntry(unsigned n, const Entry* v);                        // 0x009e4630
    ~VecEntry() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void __thiscall DoInsertValue(Entry* pos, const Entry& v);   // 0x009e04e0
    void __thiscall Construct(unsigned n, const Entry* v);       // 0x009e4630
};

struct EntryArrG {          // at Gcmdst+0x18 (same layout as EntryArr)
    unsigned count;
    VecEntry v;
    void __thiscall Insert(const Entry* e);   // 0x009e4a00
};

struct Elem0C { float a, b; int c; };                            // 0x0c

struct Vec0C {              // 0x14
    Elem0C* b;
    Elem0C* e;
    Elem0C* cap;
    int     alloc[2];
    Vec0C() : b(0), e(0), cap(0) {}
    ~Vec0C() { if (b && ((int*)b)[-1]) operator delete[](b); }
    void __thiscall AddElem(const Elem0C* e);   // 0x009e1610
};

// One frame's worth of sampled gait state: phase/duration pair plus a "started" flag.
struct GaitState { float phase; float duration; int started; };   // 0x0c

struct Gcmdst {             // 0x30
    unsigned  count;        // +0x00
    Vec0C     v;            // +0x04   sampled list
    EntryArrG arr;          // +0x18
    Gcmdst();                                                       // 0x009e56a0
    void __thiscall ResetDefault();                                // 0x009e4aa0
    void __thiscall ReadFromText(void* buf, int n);                // 0x009e4e30
};

// The per-motion walk element list: three vector-of-int slots followed by padding.
struct MtSlot { int* b; int* e; int* cap; int alloc[2]; };        // 0x14

struct MtRecord {           // 0x38
    MtSlot a;               // +0x00
    MtSlot b;               // +0x14
    int    pad[4];          // +0x28
};

struct MtTable {            // begin/end/cap of 0x38-byte motion records
    MtRecord* b;
    MtRecord* e;
    MtRecord* cap;
};

// The raw gait-record buffer read from a stream (header + payload bytes).
struct SrcBuf {
    unsigned size;          // +0x00 (this is the requested byte count)
    char     data[1];
};

void GaitRecordReadFromText(SrcBuf* buf);   // 0x009e4e30

void*  GcmdstBuild(void* gameData, const void* src);            // 0x009e56d0
void*  BuildGaits(void* self, void* g);                         // 0x009e2490
void   StreamReset(Src* stream, int a, int b);                  // 0x009e1760

// stream vtable helpers used by 009e59b0
int    StreamRead(Src* s, void* dst, int n);                    // (*(*s + 8))(dst, n)
int    StreamReadCount(Src* s);                                 // (*(*s + 4))()
void   Gcmdst_dtor_1(Gcmdst* g);                                // 0x009a95e0

struct DummyGcmdstBuildDecl {};

// ------------------------------------------------------------------ rbtree name map

struct RBNode {
    RBNode* c0;
    RBNode* c4;
    RBNode* par;
    int     color;
    uint32  key;
    void*   value;
};

struct RBTree {
    int      f00;
    RBNode*  sentinel;
    int      f08;
    RBNode*  root;
    RBNode** Find(RBNode** out, const uint32* key);          // 0x00e5c780
    void**   find_or_insert(volatile const uint32* key);     // 0x009e17d0
};

// @ 0x009e56a0
Gcmdst::Gcmdst()
{
    char tmp;                    // stack temp whose address is handed to the ctor
    count = 0;
    v.b = 0;
    v.cap = 0;
    v.e = 0;
    arr.count = 0;
    arr.v.Construct(0, (const Entry*)&tmp);
    ResetDefault();
}

// @ 0x009e5c00
// Quake "magic number" fast inverse square root, evaluated in x87.
float FastInvSqrt(float x)
{
    float y = (float)(0x5f375a86 - (*(int*)&x >> 1));
    return (float)((double)y * (1.5 - (double)x * 0.5 * (double)y * (double)y));
}

// @ 0x009e5c30
void Matrix33_Multiply(float* out, const float* a, const float* b)
{
    float a0 = a[0], a1 = a[1], a2 = a[2];
    float a3 = a[3], a4 = a[4], a5 = a[5];
    float a6 = a[6], a7 = a[7], a8 = a[8];
    float b0 = b[0], b1 = b[1], b2 = b[2];
    float b3 = b[3], b4 = b[4], b5 = b[5];
    float b6 = b[6], b7 = b[7], b8 = b[8];

    float c0 = (b8 * a6 + a0 * b2) + b5 * a3;
    float c1 = (b1 * a0 + b4 * a3) + b7 * a6;
    float c2 = (b0 * a0 + b3 * a3) + b6 * a6;

    out[0] = (c0 * a2 + c2 * a0) + c1 * a3;
    out[1] = (a1 * c2 + a4 * c1) + a7 * c0;
    out[2] = (a2 * c2 + a5 * c1) + a8 * c0;

    float d0 = (a1 * b2 + a4 * b5) + a7 * b8;
    float d1 = (a1 * b1 + a4 * b4) + a7 * b7;
    float d2 = (a1 * b0 + a4 * b3) + a7 * b6;

    out[3] = (d2 * a0 + d1 * a3) + d0 * a2;
    out[4] = (d2 * a1 + d1 * a4) + d0 * a7;
    out[5] = (d2 * a2 + d1 * a5) + d0 * a8;

    float e0 = (a2 * b2 + a5 * b5) + a8 * b8;
    float e1 = (a2 * b1 + a5 * b4) + a8 * b7;
    float e2 = (a2 * b0 + a5 * b3) + a8 * b6;

    out[6] = (e2 * a0 + e1 * a3) + e0 * a2;
    out[7] = (e2 * a1 + e1 * a4) + e0 * a7;
    out[8] = (e2 * a2 + e1 * a5) + e0 * a8;
}

// @ 0x009e5b40
int GaitRecordLookupOrBuild(int self, unsigned nameHash, void* src)
{
    RBTree* map = (RBTree*)g_name_map;
    unsigned key = nameHash;

    RBNode* node;
    map->Find(&node, &key);

    int result = 0;
    if (node != (RBNode*)((char*)map + 4) && node->value != 0) {
        // already built and complete enough: reuse it
        int inner = *(int*)((char*)node->value + 0x1c);
        unsigned have = ((*(int*)((char*)inner + 0x14) - *(int*)((char*)inner + 0x10)) / 12) & 0xffffffff;
        unsigned want = (unsigned)FUN_009d0c80((int)(size_t)&node, 0);
        if (want >= have)
            goto done;
    }

    result = (int)GcmdstBuild((void*)self, src);
    if (result != 0) {
        void** slot = map->find_or_insert(&key);
        *slot = (void*)result;
    }
done:
    BuildGaits((void*)self, (void*)result);
    return result;
}

// @ 0x009e56d0
void* GcmdstBuild(void* gameData, const void* src)
{
    Inner in;                       // results built from the sampled walk data
    MtTable* recs;                  // the per-motion walk table
    float duration;
    Gcmdst* g;

    in.f4 = 0.8f;
    in.f8 = 0;

    // size the sampled list to the walk item count, then seed the RNG.
    in.items.reserve((GameData_AnimItemEnd(gameData) - GameData_AnimItemBegin(gameData)) >> 2);
    Rng rng;
    RandRange seed = RandomBytes(RandRange());
    LCG_SetSeed(&rng, seed.m0);

    recs = (MtTable*)GetAnimWalkTable(gameData);
    int nMotions = (int)((char*)recs->e - (char*)recs->b) / 0x38;
    if (nMotions > 0) {
        MtRecord* cur = recs->b;
        do {
            int count = (int)((char*)cur->a.e - (char*)cur->a.b) / 4;
            while (count > 0) {
                float r = LCG_RandomDoubleUniform(&rng) - 0.5f;
                r = r * GameData_AnimSampleRange(gameData) * 0.8f;
                GaitState st;
                st.started = 0;
                st.phase = r - (float)iat_floor(r);
                duration = GameData_AnimSampleRange(gameData);
                st.duration = duration;
                in.items.push_back(*(const Item*)&st);   // sampled vector grows here
                count--;
            }
            cur = (MtRecord*)((char*)cur + 0x38);
        } while (--nMotions);
    }

    g = (Gcmdst*)EAAllocate(0x30, "Anim/grsd", 0, 0, 0, 0);
    if (g) {
        g->count = 0;
        g->v.b = g->v.e = g->v.cap = 0;
        g->arr.count = 0;
        g->arr.v.b = g->arr.v.e = g->arr.v.cap = 0;
        new (&g->arr.v) VecEntry(0, (const Entry*)0);
        g->ResetDefault();
    }

    Elem0C elem;
    elem.a = 0.0f;
    elem.b = in.f4;
    elem.c = in.f8;
    g->v.AddElem(&elem);

    Inner built;
    built.f8 = 0;
    built.Assign(&in);
    built.AssignItems(&in);
    if (g_AssignGaits) built.AssignGaits(&in);

    Entry e;
    e.key = 0.0f;
    e.in = built;
    g->arr.Insert(&e);

    (void)src;
    return g;
}

// @ 0x009e59b0
// Reads a gait record from a virtual stream: peeks the 12-byte header, and either
// parses a "GAIT" record (magic 0x54494147) into a fresh Gcmdst, or a "vers"/"verS"
// record (0x73726576 / 0x76657273) into a TypeBuilder-backed dynamic object.
// (Register-ABI in the original: the tag arrives in ebp, the stream in ecx/esi.)
void* ReadGaitRecordStaticDataFromStreamWrapper(Src* stream, int tag)
{
    unsigned char hdr[12];
    StreamRead(stream, hdr, 12);                 // (*(*stream + 8))(hdr, 12)

    if (tag == 0x54494147) {                     // "GAIT"
        if (*(int*)hdr == 0xb) {
            SrcBuf* buf = (SrcBuf*)EAAllocate(0x24, "Anim/bingr", 0, 0, 0, 0);
            Gcmdst* g = (Gcmdst*)EAAllocate(0x30, "Anim/grsd", 0, 0, 0, 0);
            if (g) new (g) Gcmdst();

            StreamReset(stream, 0, 0);
            if (StreamRead(stream, buf, (int)(size_t)buf) != 0xc) {
                if (g) Gcmdst_dtor_1(g);
                operator delete[](buf);
                return 0;
            }
            GaitRecordReadFromText(buf);                     // 0x009e4e30
            return g;
        }
    } else if (tag == 0x73726576 || tag == 0x76657273) {     // "vers" / "verS"
        StreamReset(stream, 0, 2);
        int n = StreamReadCount(stream);                     // (*(*stream + 4))()
        SrcBuf* buf = (SrcBuf*)EAAllocate(n, (const char*)0, 0, 0, 0, 0);
        StreamReset(stream, 0, 0);
        StreamRead(stream, buf, n);
        Gcmdst* g = (Gcmdst*)EAAllocate(0x30, "Anim/grsd", 0, 0, 0, 0);
        if (g) new (g) Gcmdst();
        if (g) g->ReadFromText(buf, n);                      // 0x009e4e30
        if (buf && ((int*)buf)[-1]) operator delete[](buf);
        return g;
    }
    return 0;
}
