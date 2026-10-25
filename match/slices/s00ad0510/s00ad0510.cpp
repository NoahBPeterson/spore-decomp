// Slice s00ad0510 - SP city visualizer helpers.
//
// The object worked on here is the city visualizer.  It owns a sorted vector of
// 0x20-byte registry records at +0x88.  Each record is
//
//     +0x00  int         key
//     +0x04  void*       record vtable        (0x0145a164)
//     +0x08  u8          flagA
//     +0x09  u8          flagB
//     +0x0c  vector      0x0c-byte entries    (begin/end/cap + allocator)
//
// The 0x0c-byte entries are polymorphic nodes with the vtable at +0 and an
// optional payload at +0x08.
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  uint;

// ------------------------------------------------------------------ 0x00ad0510 companions
class cPlanetModel;
struct NounThing;

extern "C" {
    void* __stdcall PlanetModel(void* out, int a, int b, int c, int d, int e, int f); // 0xb3d350
    void* __stdcall AudioNounManager(int x);                                        // 0xb3d300
    int   __fastcall FUN_b23940(void* self);                                        // 0xb23940
    int   __cdecl FUN_c099e0(int a, int b, int c, int d, int e, int f);             // 0xc099e0
}

class cPlanetModel {
public:
    int DirectionToSurfacePosition();   // 0xb815a0
};

class CityVisualizer {
public:
    int FuncACEBD0(int a, int b);       // 0xacebd0
    int Ad0510(int param1, int param2); // @ 0xad0510
};

int CityVisualizer::Ad0510(int param1, int param2)
{
    uint32_t local[3];
    cPlanetModel* m = (cPlanetModel*)PlanetModel(local, param2, param1, 1, 0, 0, 0);
    int r = m->DirectionToSurfacePosition();
    void* n = AudioNounManager(r);
    int esi = FUN_b23940(n);
    if (!esi)
        return 0;
    int edi = FUN_c099e0(param2, param1, 1, esi, 0, 1);
    FuncACEBD0(esi, 0);
    return edi;
}

// ------------------------------------------------------------------ callable slots
typedef void  (__thiscall *TC_v0)(void*);
typedef void* (__thiscall *TC_p0)(void*);
typedef void  (__thiscall *TC_v1)(void*, void*);
typedef void* (__thiscall *TC_p1)(void*, void*);
typedef void  (__thiscall *TC_v3)(void*, void*, void*, void*);

#define VTC(obj, off, type) ((type)(*(void***)(obj))[((off) >> 2)])

// ------------------------------------------------------------------ the registry record
struct RegElem {              // 0x0c-byte entry of a record's vector
    void* vt;                 // +0x00
    u8    flag4;              // +0x04
    char  pad5[3];            // +0x05
    void* ptr8;               // +0x08
};

struct RegVec {               // eastl vector of RegElem (0x14 bytes)
    RegElem* begin;           // +0x00
    RegElem* end;             // +0x04
    RegElem* cap;             // +0x08
    int      alloc0;          // +0x0c
    int      alloc1;          // +0x10

    void FUN_00aca9d0(const RegVec* src);   // 0x00aca9d0 (copy-construct)
    void FUN_00acbd90(const RegVec* src);   // 0x00acbd90 (copy-assign)
    void FUN_00ac8ec0();                    // 0x00ac8ec0 (destructor)
};

struct RegList {              // record payload, starts at element+4
    void*   vt;               // +0x04  (0x0145a164)
    u8      b8;               // +0x08
    u8      b9;               // +0x09
    char    pad0a[2];         // +0x0a
    RegVec  vec;              // +0x0c  (0x14 bytes)
};

struct Elem20 {               // 0x20-byte sorted-vector element
    int     key;              // +0x00
    RegList list;             // +0x04
};

struct ElemVec {              // sorted registry vector header (0x18 bytes)
    Elem20* begin;            // +0x00
    Elem20* end;              // +0x04
    Elem20* cap;              // +0x08
    char    pad0c[8];         // +0x0c
    u8      less;             // +0x14
    char    pad15[3];         // +0x15

    RegList* get(int* key);   // 0x00ad0ca0
    Elem20* FUN_00ad0890(Elem20* pos, Elem20* val);  // 0x00ad0890 (insert)
};

struct AutoRef {              // 0x04-byte intrusive reference
    void* p;
};
struct AutoRefVec {           // eastl vector of AutoRef (0x14 bytes)
    AutoRef* begin;
    AutoRef* end;
    AutoRef* cap;
    int      alloc0;
    int      alloc1;
};
struct TribeEntry {           // 0x18-byte entry of the +0xa8 vector
    AutoRef    primary;       // +0x00
    AutoRefVec refs;          // +0x04
};
struct TribeVec {             // eastl vector of TribeEntry
    TribeEntry* begin;
    TribeEntry* end;
    TribeEntry* cap;
};

struct Rec20 {                // 0x14-byte element of the +0x20 vector
    int v[5];
};
struct RecVec {
    Rec20* begin;
    Rec20* end;
    Rec20* cap;
};

struct FieldC0 {              // auxiliary record at +0xc0
    int   a0;
    void* a4;
    void* a8;
    int   ac;
};
struct FieldE0 {              // eastl hashtable at +0xe0
    void* a0;
    void* a4;
    void* a8;
    int   ac;
};

struct cCityVisualizer;
struct VignetteObj {          // object reached from tag 0x116dd1b
    char pad00[0x71];
    u8   f71;                 // +0x71
    char pad72[3];
    u8   f75;                 // +0x75
};

struct cCityVisualizer {
    char        pad00[0x1c];
    void*       msg1c;        // +0x1c
    RecVec      rec;          // +0x20
    char        pad2c[0x88 - 0x2c];
    ElemVec     registry;     // +0x88
    int         f_a0;         // +0xa0
    void*       mp_city;      // +0xa4
    TribeVec    tribes;       // +0xa8
    char        pad_b4[8];
    void*       p_bc;         // +0xbc
    FieldC0     field_c0;     // +0xc0
    char        pad_d0[0xe0 - 0xd0];
    FieldE0     hash_e0;      // +0xe0
    u8          f_100;        // +0x100

    void* UpdateVignettes(void* tag);   // 0x00ad11f0
};

// Original __thiscall helpers are called as members so the first argument lands in ECX
// without an extra fastcall dummy register.
struct CityOps {
    void FUN_00ad1000(void* tag, int count);   // 0x00ad1000
    void FUN_00ac8a80(RegList* list, int i);   // 0x00ac8a80
    void FUN_00d60f00(void* city);             // 0x00d60f00
    void FUN_00d5bb30();                       // 0x00d5bb30
    void FUN_00ad08f0();                       // 0x00ad08f0
};

// ------------------------------------------------------------------ original helpers
extern "C" {
void*  __cdecl NounManager();                                    // 0x00b3d300
void*  __fastcall CreateNoun(void*, int, void*);                 // 0x00b20c60
void   __fastcall RemoveNoun(void*, int, void*);                 // 0x00b225d0
void   __fastcall FUN_00c8fc50(void*, int, int);                 // 0x00c8fc50
void   __fastcall FUN_00c0bf00(void*, int, int);                 // 0x00c0bf00
void*  __cdecl MessageServer();                                  // 0x0067dcc0
void   __fastcall FUN_00d60f00(void*, int, void*);               // 0x00d60f00 (SetCity)
void   __fastcall FUN_00d5bb30(void*, int);                      // 0x00d5bb30
void*  __cdecl FUN_00copy_Rec20(void*, void*, void*);            // 0x00951bf0
int    __cdecl ReadInt32(void*, int*, int, int);                 // 0x0093a780
int    __cdecl FUN_00b98c00(void*);                              // 0x00b98c00

void*  __cdecl FUN_00f473a0(uint, const char*, int, int, const char*, int); // operator new
void   __cdecl FUN_00f47380(void*);                              // operator delete

Elem20* __cdecl FUN_00aca1f0(Elem20*, Elem20*, int*, u8);        // lower_bound
Elem20* __fastcall FUN_00ad0890(void*, int, Elem20*, Elem20*);   // record insert
void   __cdecl FUN_00accf20(Elem20*, Elem20*, Elem20*);          // move-assign range
Elem20* __cdecl FUN_00acbb20(Elem20*, Elem20*, Elem20*);         // move-construct range
void   __cdecl FUN_00aca2f0(Elem20*, Elem20*, Elem20*);          // destroy moved-from range
void   __fastcall FUN_00aca9d0(RegVec*, int, const RegVec*);     // vector copy-construct
void   __fastcall FUN_00acbd90(RegVec*, int, const RegVec*);     // vector copy-assign
void   __fastcall FUN_00ac8ec0(RegVec*, int);                    // vector destructor

void*  __cdecl FUN_00acc2d0(void*, void*, void*);                // clear helper (tribe)
void   __fastcall FUN_00aca820(void*, int, void*, void*);        // clear helper (tribe)
void*  __cdecl FUN_00accec0(void*, void*, void*);                // clear helper (record)
void   __fastcall FUN_00aca7b0(void*, int, void*, void*);        // clear helper (record)
void   __fastcall FUN_00acccb0(TribeVec*, int, int);             // reserve
void*  __cdecl FUN_00ac9740(void*, void*, void*);                // destroy range
void   __fastcall FUN_00aca970(TribeEntry*, int, const TribeEntry*); // copy-construct entry
void   __fastcall FUN_00acf0b0(TribeVec*, int, const TribeEntry*);   // push_back (grow)
void   __fastcall FUN_00acd920(RegVec*, int, int);               // resize record vector
void   __fastcall FUN_00ad0590(ElemVec*, int, Elem20*, Elem20*); // record insert

void   __fastcall FUN_00ad08f0(cCityVisualizer*, int);           // full reset
void   __fastcall FUN_00ad1000(cCityVisualizer*, int, void*, int); // resize record entries
void   __fastcall FUN_00ac8a80(cCityVisualizer*, int, RegList*, int); // erase entry
void   __fastcall FUN_00acd4a0(cCityVisualizer*, int);           // reset action circle
void   __fastcall FUN_00accf80(cCityVisualizer*, int, void*);    // SetupCultureStages
void   __fastcall FUN_00accd70(FieldC0*, int, void*, void*);     // clear field at +0xc0
void   __fastcall FUN_00acc770(cCityVisualizer*, int);           // reset field at +0xc0
void   __fastcall FUN_00693230(FieldE0*, int, void*, void*);     // hashtable free buckets
}

extern u8   g_1565cfc;        // 0x01565cfc
extern int  g_167a378;        // 0x0167a378
extern char g_167a390;        // 0x0167a390

struct CVarListSerializer {
    char pad[0xa10];
    void ctor(const void* owner, void* descriptor, uint tag);    // 0x00692f90
    bool Read(void* stream);                                     // 0x00693e10
};

// ------------------------------------------------------------------ local helpers
static void destroyRegVec(RegVec* v)
{
    for (RegElem* p = v->begin; p != v->end; ++p)
        VTC(p, 0x00, TC_v1)(p, 0);
    if (v->begin)
        FUN_00f47380(v->begin);
    v->begin = 0;
    v->end = 0;
    v->cap = 0;
}

static void destroyTribeEntry(TribeEntry* e)
{
    if (e->primary.p)
        VTC(e->primary.p, 0x04, TC_v0)(e->primary.p);
    for (AutoRef* p = e->refs.begin; p != e->refs.end; ++p)
        if (p->p)
            VTC(p->p, 0x04, TC_v0)(p->p);
    if (e->refs.begin && ((int*)e->refs.begin)[-1] != 0)
        FUN_00f47380(e->refs.begin);
}

// ================================================================================================
// 0x00ad0590 -- insert one 0x20-byte record at pos.
__declspec(noinline)
// @ 0x00ad0590
void __fastcall FUN_00ad0590(ElemVec* self, int, Elem20* pos, Elem20* val)
{
    Elem20* last = self->end;
    if (last != self->cap) {
        if (pos <= val && val < last)
            ++val;
        if (last) {
            last->key       = last[-1].key;
            last->list.vt   = (void*)0x0145a164;
            last->list.b8   = last[-1].list.b8;
            last->list.b9   = last[-1].list.b9;
            FUN_00aca9d0(&last->list.vec, 0, &last[-1].list.vec);
        }
        FUN_00accf20(pos, last - 1, last);
        pos->key     = val->key;
        pos->list.b8 = val->list.b8;
        pos->list.b9 = val->list.b9;
        FUN_00acbd90(&pos->list.vec, 0, &val->list.vec);
        self->end = last + 1;
        return;
    }

    int n = (int)(last - self->begin);
    int newcap;
    if (n == 0)
        newcap = 1;
    else
        newcap = n * 2;

    Elem20* buf = 0;
    if (newcap) {
        buf = (Elem20*)FUN_00f473a0((uint)newcap * 0x20, "Simulator", 0, 0,
                                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                    0xd1);
    }

    Elem20* mid = FUN_00acbb20(self->begin, pos, buf);
    FUN_00aca2f0(self->begin, pos, buf);
    if (mid) {
        mid->key     = val->key;
        mid->list.vt = (void*)0x0145a164;
        mid->list.b8 = val->list.b8;
        mid->list.b9 = val->list.b9;
        FUN_00aca9d0(&mid->list.vec, 0, &val->list.vec);
    }
    Elem20* newEnd = FUN_00acbb20(pos, last, mid + 1);
    FUN_00aca2f0(pos, last, mid + 1);
    if (self->begin)
        FUN_00f47380(self->begin);
    self->end   = newEnd;
    self->begin = buf;
    self->cap   = buf + newcap;
}

// ================================================================================================
// 0x00ad0710 -- deserialize a vector of 0x18-byte tribe entries.
// @ 0x00ad0710
void __cdecl FUN_00ad0710(void* stream, TribeVec* vec)
{
    TribeEntry* b = vec->begin;
    TribeEntry* e = vec->end;
    void* cleared = FUN_00acc2d0(e, e, b);
    FUN_00aca820(vec, 0, cleared, vec->end);
    vec->end = vec->begin;

    int count = 0;
    void* obj = VTC(stream, 0x20, TC_p0)(stream);
    void* io  = VTC(obj, 0x18, TC_p0)(obj);
    ReadInt32(io, &count, 1, 0);
    FUN_00acccb0(vec, 0, count);

    for (int i = 0; i < count; ++i) {
        TribeEntry tmp;
        tmp.primary.p   = 0;
        tmp.refs.begin  = 0;
        tmp.refs.end    = 0;
        tmp.refs.cap    = 0;
        tmp.refs.alloc0 = 0;
        tmp.refs.alloc1 = 0;

        CVarListSerializer ser;
        ser.ctor(&tmp, (void*)0x015660f0, 0x1a80d26);
        ser.Read(stream);

        if (vec->end < vec->cap) {
            TribeEntry* slot = vec->end;
            vec->end = slot + 1;
            if (slot)
                FUN_00aca970(slot, 0, &tmp);
        } else {
            FUN_00acf0b0(vec, 0, &tmp);
        }
        destroyTribeEntry(&tmp);
    }

    VTC(stream, 0x1c, TC_v0)(stream);
}

// ================================================================================================
// 0x00ad08f0 -- reset every registry record, the tribe list and the aux tables.
__declspec(noinline)
// @ 0x00ad08f0
void __fastcall FUN_00ad08f0(cCityVisualizer* self, int)
{
    void* nouns = NounManager();
    g_1565cfc = 0;
    g_167a378 = 0;
    FUN_00acd4a0(self, 0);
    FUN_00accd70(&self->field_c0, 0, self->field_c0.a4, self->field_c0.a8);
    self->field_c0.ac = 0;

    int tribeCount = (int)(self->tribes.end - self->tribes.begin);
    for (int i = 0; i < tribeCount; ++i)
        FUN_00c8fc50(&self->tribes.begin[i], 0, 0);

    TribeEntry* tb = self->tribes.begin;
    TribeEntry* te = self->tribes.end;
    void* cleared = FUN_00acc2d0(te, te, tb);
    FUN_00aca820(&self->tribes, 0, cleared, self->tribes.end);
    self->tribes.end = (TribeEntry*)((char*)self->tribes.end - tribeCount * 0x18);

    for (Elem20* rec = self->registry.begin; rec != self->registry.end; ++rec) {
        int n = (int)(rec->list.vec.end - rec->list.vec.begin);
        for (int i = 0; i < n; ++i) {
            RegElem* r = &rec->list.vec.begin[i];
            if (r->flag4)
                FUN_00accf80(self, 0, r->ptr8);
            if (r->ptr8) {
                void* v = VTC(r->ptr8, 0x0c, TC_p1)(r->ptr8, (void*)0xce9f6639);
                if (v)
                    VTC(v, 0x44, TC_v0)(v);
            }
            if (nouns)
                RemoveNoun(nouns, 0, r->ptr8);
        }
        RegElem* rb = rec->list.vec.begin;
        RegElem* re = rec->list.vec.end;
        RegElem* ri = (RegElem*)FUN_00ac9740(re, re, rb);
        while (ri < re) {
            VTC(ri, 0x00, TC_v1)(ri, 0);
            ++ri;
        }
        rec->list.vec.end = (RegElem*)((char*)rec->list.vec.end - (int)(re - rb) * 0x0c);
    }

    Elem20* eb = self->registry.begin;
    Elem20* ee = self->registry.end;
    void* ec = FUN_00accec0(ee, ee, eb);
    FUN_00aca7b0(&self->registry, 0, ec, self->registry.end);
    self->registry.end = (Elem20*)((char*)self->registry.end - (int)(ee - eb) * 0x20);

    FUN_00693230(&self->hash_e0, 0, self->hash_e0.a4, self->hash_e0.a8);
    self->hash_e0.ac = 0;
    FUN_00acc770(self, 0);
    self->f_100 = 0;
}

// ================================================================================================
// 0x00ad0b30 -- clear the registry, then read the var list.
// @ 0x00ad0b30
bool __fastcall FUN_00ad0b30(cCityVisualizer* self, int, void* stream)
{
    if (self->registry.begin != self->registry.end)
        FUN_00ad08f0(self, 0);

    void* obj = VTC(stream, 0x20, TC_p0)(stream);
    void* io  = VTC(obj, 0x18, TC_p0)(obj);
    int count = 0;
    ReadInt32(io, &count, 1, 0);

    CVarListSerializer ser;
    ser.ctor(self, (void*)0x01565d68, 0x1a80d26);
    if (!ser.Read(stream))
        return false;
    return FUN_00b98c00(stream) != 0;
}

// ================================================================================================
// 0x00ad0bd0 -- tear the visualizer's city state down.
// @ 0x00ad0bd0
void __fastcall FUN_00ad0bd0(cCityVisualizer* self, int)
{
    void* ms = MessageServer();
    if (ms) {
        VTC(ms, 0x2c, TC_v3)(ms, self ? &self->msg1c : 0, (void*)0x1a0219e, (void*)-0x270f);
        VTC(ms, 0x2c, TC_v3)(ms, self ? &self->msg1c : 0, (void*)0x6130eb9, (void*)-0x270f);
    }
    if (self->mp_city)
        ((CityOps*)self->mp_city)->FUN_00d60f00(0);
    if (self->p_bc)
        ((CityOps*)self->p_bc)->FUN_00d5bb30();
    ((CityOps*)self)->FUN_00ad08f0();

    Rec20* rb = self->rec.begin;
    Rec20* re = self->rec.end;
    FUN_00copy_Rec20(re, re, rb);
    self->rec.end = (Rec20*)((char*)self->rec.end - (int)(re - rb) * 0x14);
    self->f_a0 = -1;
}

// ================================================================================================
// 0x00ad0ca0 -- find a record by key, inserting an empty one when missing.
__declspec(noinline)
// @ 0x00ad0ca0
RegList* ElemVec::get(int* key)
{
    Elem20* last = end;
    Elem20* it = FUN_00aca1f0(begin, last, key, less);
    if (it == last || *key < it->key) {
        RegVec empty;
        empty.begin = 0;
        empty.end   = 0;
        empty.cap   = 0;

        Elem20 value;
        value.key     = *key;
        value.list.vt = (void*)0x0145a164;
        value.list.b8 = 0;
        value.list.b9 = 0;
        value.list.vec.FUN_00aca9d0(&empty);

        Elem20* e = end;
        Elem20* lo;
        Elem20* hi;
        if (it != e && value.key < it->key) {
            lo = begin;
            hi = it;
        } else {
            lo = it;
            hi = e;
        }
        it = FUN_00aca1f0(lo, hi, &value.key, less);
        if (it == end || value.key < it->key)
            it = FUN_00ad0890(it, &value);
        value.list.vec.FUN_00ac8ec0();
        empty.FUN_00ac8ec0();
    }
    return &it->list;
}

// ================================================================================================
// 0x00ad0d90 -- deserialize the record vector, merging equal keys.
// @ 0x00ad0d90
void __cdecl FUN_00ad0d90(void* stream, ElemVec* vec)
{
    Elem20* vb = vec->begin;
    Elem20* ve = vec->end;
    void* cleared = FUN_00accec0(ve, ve, vb);
    FUN_00aca7b0(vec, 0, cleared, vec->end);
    vec->end = vec->begin;

    int count = 0;
    void* obj = VTC(stream, 0x20, TC_p0)(stream);
    void* io  = VTC(obj, 0x18, TC_p0)(obj);
    ReadInt32(io, &count, 1, 0);

    for (int i = 0; i < count; ++i) {
        Elem20 entry;
        entry.list.vt = (void*)0x0145a164;
        entry.list.b8 = 0;
        entry.list.b9 = 0;
        entry.list.vec.begin  = 0;
        entry.list.vec.end    = 0;
        entry.list.vec.cap    = 0;
        entry.list.vec.alloc0 = 0;
        entry.list.vec.alloc1 = 0;

        void* o2 = VTC(stream, 0x20, TC_p0)(stream);
        void* i2 = VTC(o2, 0x18, TC_p0)(o2);
        ReadInt32(i2, &entry.key, 1, 0);
        VTC(stream, 0x1c, TC_v0)(stream);

        CVarListSerializer ser;
        ser.ctor(&entry, (void*)0x01566000, 0x1a80d26);
        ser.Read(stream);
        VTC(stream, 0x1c, TC_v0)(stream);

        Elem20 value;
        value.key     = entry.key;
        value.list.vt = (void*)0x0145a164;
        value.list.b8 = entry.list.b8;
        value.list.b9 = entry.list.b9;
        value.list.vec.begin  = 0;
        value.list.vec.end    = 0;
        value.list.vec.cap    = 0;
        value.list.vec.alloc0 = 0;
        value.list.vec.alloc1 = 0;
        FUN_00aca9d0(&value.list.vec, 0, &entry.list.vec);

        Elem20* last = vec->end;
        Elem20* it = FUN_00aca1f0(vec->begin, last, &value.key, vec->less);
        bool fresh;
        Elem20* slot;
        if (it != last && value.key >= it->key) {
            fresh = false;
            slot  = it;
        } else {
            if (it == last && last != vec->cap) {
                Elem20* e = last;
                vec->end = e + 1;
                if (e) {
                    e->key     = value.key;
                    e->list.vt = (void*)0x0145a164;
                    e->list.b8 = value.list.b8;
                    e->list.b9 = value.list.b9;
                    FUN_00aca9d0(&e->list.vec, 0, &value.list.vec);
                }
            } else {
                FUN_00ad0590(vec, 0, it, &value);
            }
            slot  = vec->begin + (int)(it - vec->begin);
            fresh = true;
        }

        destroyRegVec(&value.list.vec);
        if (!fresh) {
            slot->list.b8 = entry.list.b8;
            slot->list.b9 = entry.list.b9;
            FUN_00acbd90(&slot->list.vec, 0, &entry.list.vec);
        }
        destroyRegVec(&entry.list.vec);
    }

    VTC(stream, 0x1c, TC_v0)(stream);
}

// ================================================================================================
// 0x00ad1000 -- grow or shrink a record's entry vector to `count`.
__declspec(noinline)
// @ 0x00ad1000
void __fastcall FUN_00ad1000(cCityVisualizer* self, int, void* tag, int count)
{
    if (count <= 0)
        return;

    RegList* list = self->registry.get((int*)&tag);
    int have = (int)(list->vec.end - list->vec.begin);
    void* nouns = NounManager();

    if (have < count) {
        FUN_00acd920(&list->vec, 0, count);
        for (int i = have; i < count; ++i) {
            RegElem* r = &list->vec.begin[i];
            void* noun = CreateNoun(nouns, 0, tag);
            void* old  = r->ptr8;
            if (noun != old) {
                if (noun)
                    VTC(noun, 0x00, TC_v0)(noun);
                r->ptr8 = noun;
                if (old)
                    VTC(old, 0x04, TC_v0)(old);
            }
            r->flag4 = 0;
        }
    } else if (count < have) {
        for (int i = count; i < have; ++i)
            RemoveNoun(nouns, 0, list->vec.begin[i].ptr8);
        FUN_00acd920(&list->vec, 0, count);
    }

    void* first = list->vec.begin[0].ptr8;
    list->b8 = VTC(first, 0x0c, TC_p1)(first, (void*)0x116dd1b) != 0;
    if (list->b8 && have < count) {
        for (int i = have; i < count; ++i) {
            void* o = list->vec.begin[i].ptr8;
            if (!o)
                continue;
            void* v = VTC(o, 0x0c, TC_p1)(o, (void*)0x116dd1b);
            if (!v)
                continue;
            VignetteObj* vo = (VignetteObj*)v;
            vo->f75 = 0;
            VTC(v, 0x38, TC_v1)(v, &g_167a390);
            vo->f71 = 1;
        }
    }

    list->b9 = VTC(first, 0x0c, TC_p1)(first, (void*)0x11c0ba3) != 0;
    void* third = VTC(first, 0x0c, TC_p1)(first, (void*)0xce9f6639);
    if (third && have < count) {
        for (int i = have; i < count; ++i) {
            void* o = list->vec.begin[i].ptr8;
            if (!o)
                continue;
            void* v = VTC(o, 0x0c, TC_p1)(o, (void*)0xce9f6639);
            if (v)
                FUN_00c0bf00(v, 0, 1);
        }
    }
}

// ================================================================================================
// 0x00ad11f0 -- SP::cCityVisualizer::UpdateVignettes.
// @ 0x00ad11f0
__declspec(noinline) void* cCityVisualizer::UpdateVignettes(void* tag)
{
    RegList* list = registry.get((int*)&tag);
    int count = (int)(list->vec.end - list->vec.begin);
    for (int i = 0; i < count; ++i) {
        if (list->vec.begin[i].flag4 == 0) {
            ((CityOps*)this)->FUN_00ac8a80(list, i);
            return list->vec.begin[i].ptr8;
        }
    }
    if (tag == (void*)0x18eb45e) {
        ((CityOps*)this)->FUN_00ad1000((void*)0x18eb45e, count * 2);
        ((CityOps*)this)->FUN_00ac8a80(list, count);
        return list->vec.begin[count].ptr8;
    }
    return 0;
}
