// Slice s00ba3860 -- Simulator goal-state container / SP::PlayerPlanetData helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned int  size_t;
typedef unsigned char u8;

// ---------------------------------------------------------------- externs
void* __cdecl operator_new(int);                            // 0x00f473a0
void  __cdecl operator_delete__(void*);                     // 0x00f47380

void* __cdecl SP_GetActivePlanet();                         // 0x00b3d240
void* __cdecl SP_NounManager();                             // 0x00b3d300
void* __cdecl SP_GetCurrentGameMode();                      // 0x00b5b800
void* __cdecl SP_AchievementsController();                  // 0x00675250
void* __cdecl FUN_0067cb30();                               // 0x0067cb30
void* __cdecl FUN_00c0bc00();                               // 0x00c0bc00
void* __cdecl FUN_00c04590(void* o);                        // 0x00c04590
void  __cdecl FUN_00ba5e10(void* o, int v);                 // 0x00ba5e10
void* __cdecl FUN_00b21340(void* mgr, int, int, int, int, int); // 0x00b21340
void  __cdecl EA_ConvertToString16(void* out, const char* s, uint n); // 0x0093c5a0
char  __cdecl FUN_00ac8050(void* iface, int a, void* e);    // 0x00ac8050
void* __cdecl UninitCopy16(char* const* dstEnd, const void* src, const void* srcEnd, void* dst, void* tag); // 0x007f1890
void* __cdecl Copy8(char* const* dstEnd, const void* src, const void* srcEnd, void* dst, void* tag);        // 0x0076ffd0

// ---------------------------------------------------------------- data
char  g_1654c10;                                            // 0x01654c10
char  g_1654c01;                                            // 0x01654c01
float g_f1485720 = 1.0f;                                    // 0x01485720
float g_f1470f1c = 2.0f;                                    // 0x01470f1c
void* g_154df28;                                            // 0x0154df28
wchar_t g_wEmpty[];                                         // 0x013f6254

extern void* g_vtbl_PPD1;   // 0x01465d64
extern void* g_vtbl_TimerA; // 0x01465d54
extern void* g_vtbl_TimerB; // 0x01464450
extern void* g_vtbl_GB1a;   // 0x013eb384
extern void* g_vtbl_GB1b;   // 0x01465dc8
extern void* g_vtbl_GB1c;   // 0x01465d78
extern void* g_vtbl_GB1d;   // 0x01465d70

// ---------------------------------------------------------------- foreign classes
struct CGZSub { void __thiscall Ctor(); };                  // 0x00b5b960
void* __fastcall FUN_00c0c1a0(void* o);                     // 0x00c0c1a0
struct ContObj { void __thiscall AutoTest(uint, int); };    // 0x00676e90
struct Ctx2   { void* GetB28(); };                          // 0x00c04590
struct ThingIn  { char pad[0xa4]; int f0a4; void __thiscall Set0x120(); }; // 0x00c6ad30
struct ThingIn2 { char pad[0x191]; u8 f191; void __thiscall Set(u8); };    // 0x00c6a070
struct PropObj  { void __thiscall UpdateProperty(uint, const void*); };    // 0x0060d860
struct ThingMgr { void* __thiscall GetThing(); };           // 0x00f3c0e0
struct AnimCtx  { int f00, f04, f08; };                     // built at +0xb28
struct GameData { char pad[0xb20]; int f0b20; char pad2[4]; int f0b28, f0b2c, f0b30; };

// EASTL-style intrusive hashtable used at Goal+0x20 (key = 3 dwords, node +0x20 = next).
struct HtNode {
    uint k0, k1, k2;                                        // +0x00
    char pad0c[0x14];
    HtNode* next;                                           // +0x20
};
// Find/Insert out-parameter: { node, bucketptr, inserted } (0xc bytes).
struct HIter { HtNode* node; HtNode** bucket; u8 inserted; char pad[3]; };
struct Ht {
    char    pad00[4];
    HtNode** bucket;                                        // +0x04
    uint    bucketCount;                                    // +0x08
    uint    size;                                           // +0x0c
    char    pad10[0x10];

    void Find(HIter* it, const void* key);                  // 0x00ba3040
    void Insert(HIter* it, const void* val, uint tag);      // 0x00ba30c0
    void Insert2(HIter* it, const void* key, uint tag);     // 0x00ba3250
    void* GetOrAdd1(const void* key);                       // 0x00ba39f0
    void* GetOrAdd2(const void* key);                       // 0x00ba3a80
};
void Find645ed0(HIter* it, const void* key);                // 0x00645ed0

// eastl::hashtable variant used at Goal+0x40 (buckets at +0, count at +4, size at +8).
struct Eh {
    HtNode** bucket;                                        // +0x00
    uint     bucketCount;                                   // +0x04
    uint     size;                                          // +0x08
    void Find(HIter* it, const void* key);                  // 0x00645ed0
    void Insert2(HIter* it, const void* key, uint tag);     // 0x00ba3250
    void* GetOrAdd2(const void* key);                       // 0x00ba3a80
};

// Sorted vector block: begin/end/cap + flag at +0x14 (0x18 bytes).
struct VBlk8 {
    char* begin; char* end; char* cap; char pad0c[8]; u8 flag; char pad15[3];
    void* __thiscall Assign(VBlk8* src);                    // 0x00ba3620
    void* __thiscall Reserve(uint n, void* flags);          // 0x00ac20d0
};
// Key stored in the sorted-vector blocks: 3 dwords compared as (k0, k2, k1).
struct WKey { uint k0, k1, k2; };

// Sorted vector block: begin/end/cap + flag at +0x14 (0x18 bytes).
struct VBlk {
    char* begin; char* end; char* cap; char pad0c[8]; u8 flag; char pad15[3];
    void* __thiscall Assign(VBlk* src);                      // 0x00ba3550
    void* __thiscall Reserve(uint n, void* flags);           // 0x00ba2ec0
    __declspec(noinline) void* __thiscall InsertAt(char* pos, const WKey* key);   // 0x00ba43b0
    void* __thiscall FindOrAdd2(const WKey* key);            // 0x00ba4520
};
// insert into a sorted vector of 0x10-byte records (thiscall, 2 args, ret 8),
// returns the inserted 0x10-byte element.
struct Vec16 { void* __thiscall InsertSorted(void* pos, void* val); };        // 0x00b97140

// eastl::wstring (0x10 bytes)
struct WString {
    wchar_t* begin; wchar_t* end; wchar_t* cap; int alloc;
    void __thiscall RangeInitialize(const wchar_t* s);      // 0x00579a90
    void __thiscall CopyFrom(const WString* src);           // 0x0056e2d0
};

// SP::PlayerPlanetData (retail size 0xa4)
struct PPD {
    void* vftbl;                                            // +0x00
    void* f04;                                              // +0x04
    VBlk  b0;                                               // +0x08
    VBlk  b1;                                               // +0x20
    VBlk  b2;                                               // +0x38
    VBlk  b3;                                               // +0x50
    VBlk8 b4;                                               // +0x68
    void* timerVtbl;                                        // +0x80
    void* f84;                                              // +0x84
    int   f88, f8c, f90, f94;                               // +0x88
    u8    f98; char pad99[3];                               // +0x98
    int   f9c;                                              // +0x9c
    u8    fa0, fa1, fa2; char padA3;                        // +0xa0

    PPD* CopyCtor(const PPD& src);                          // 0x00ba3ca0
    PPD* Assign(const PPD& src);                            // 0x00ba4430
};

// Goal state container: two hashtables at +0x20 / +0x40.
struct Goal {
    char pad00[0x20];
    Ht map1;                                                // +0x20
    Eh map2;                                                // +0x40

    int  Field4(const void* key);                           // 0x00ba4270
    int  AddCount(const void* key, void* obj);              // 0x00ba4290
    void Clear0c(const void* key);                          // 0x00ba4330
    void Set10(const void* key, int v);                     // 0x00ba4350
    int  Field8(const void* key);                           // 0x00ba4370
    int  Field0c(const void* key);                          // 0x00ba4390
    int  Resolve(const void* key, void* a, void* b);        // 0x00ba3f90
};

// Element payload stored in map1 nodes (0x20 bytes).
struct Entry { uint k0, k1, k2, f0c, f10, f14, f18, f1c; };

extern void* g_ktData;                                      // 0x00d9a9c0

// ================================================================ 0x00ba3860
// @ 0x00ba3860
void __stdcall FUN_00ba3860(void* self) {
    if (self == 0) return;
    void* ctx = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)self + 0xc))(self, 0xd0036e08);
    if (ctx == 0) return;
    void* planet = SP_GetActivePlanet();
    void* out[9];
    void** vec = out;                       // local vector {begin, end, cap}
    vec[0] = (void*)&out[4];                // begin = inline buffer
    vec[1] = (void*)&out[4];                // end   = inline buffer (empty)
    vec[2] = (void*)&out[8];                // cap   = inline buffer end
    int n = (*(int(__thiscall**)(void*, int, int, void**, int, void*, void*))
             ((char*)*(void**)((char*)ctx + 0xc0) + 0x2c))((char*)ctx + 0xc0, 0x41f00000,
                                                           (int)out, vec + 0, 0,
                                                           (void*)0xd9a9c0, ctx);
    if (!(*(char(__thiscall**)(void*, int))((char*)*(void**)planet + 0x48))(planet, n)) return;
    int count = (int)((char*)vec[1] - (char*)vec[0]) >> 2;
    if (count <= 0) return;
    for (int i = 0; i < count; ++i) {
        void* e = ((void**)vec[0])[i];
        if (e == 0) continue;
        void* o = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)e + 0xb8))(e, 0xd0036e08);
        if (o == 0) continue;
        if (*(int*)((char*)o + 0xb20) == *(int*)((char*)ctx + 0xb20)) {
            FUN_00ac8050(o, 0x10000, (char*)*(void**)((char*)o + 0xb4c) + 8);
            (*(void(__thiscall**)(void*, int))((char*)*(void**)ctx + 4))(ctx, 0);
        }
        (*(void(__thiscall**)(void*))((char*)*(void**)e + 0xc0))(e);
    }
}

// ================================================================ 0x00ba39f0
// @ 0x00ba39f0
void* Ht::GetOrAdd1(const void* key) {
    HIter it;
    Find(&it, key);
    if (it.node == this->bucket[this->bucketCount]) {
        const uint* k = (const uint*)key;
        uint e[8];
        e[0] = k[0]; e[1] = k[1]; e[2] = k[2];
        e[3] = 0; e[4] = 0; e[5] = 0; e[6] = 0; e[7] = 0xffffffff;
        uint tag = (uint)(size_t)key;
        Insert(&it, e, tag);
    }
    return (char*)it.node + 0xc;
}

// ================================================================ 0x00ba3a80
// @ 0x00ba3a80
void* Eh::GetOrAdd2(const void* key) {
    HIter it;
    Find(&it, key);
    if (it.node != this->bucket[this->bucketCount])
        return (char*)it.node + 4;
    void* ref = *(void**)key;
    if (ref) (*(void(__thiscall**)(void*))(*(void**)ref))(ref);
    void* v = (void*)*(const uint*)key;
    uint tag = (uint)(size_t)key;
    Insert2(&it, &v, tag);
    if (ref) (*(void(__thiscall**)(void*))((char*)*(void**)ref + 4))(ref);
    return (char*)it.node + 4;
}

// ================================================================ 0x00ba3b10
// @ 0x00ba3b10
u8 __cdecl FUN_00ba3b10(void* iface, const char* name, Goal* g) {
    u8 result = 1;
    if (g->map1.size == 0) return result;
    Ht* map = &g->map1;
    WString tmp;
    bool converted = false;
    if (name != 0) {
        EA_ConvertToString16(&tmp, name, 0xffffffff);
        converted = true;
    } else {
        tmp.begin = 0; tmp.end = 0; tmp.cap = 0; tmp.alloc = 0;
        tmp.RangeInitialize(0);
    }
    WString dst;
    dst.CopyFrom(&tmp);
    if (converted) {
        if (((int)(tmp.end - tmp.begin) & ~1) > 2 && tmp.begin != 0)
            operator_delete__(tmp.begin);
    } else {
        if (((int)(dst.end - dst.begin) & ~1) > 2 && dst.begin != 0)
            operator_delete__(dst.begin);
    }
    {
        wchar_t* s = dst.begin;
        if (s == dst.end) s = g_wEmpty;
        (*(void(__thiscall**)(void*, wchar_t*))*(void**)iface)(iface, s);
    }
    {
        HtNode* first = map->bucket[0];
        HtNode** slot = map->bucket;
        if (first == 0) {
            slot = map->bucket + 1;
            first = map->bucket[1];
            while (first == 0) { ++slot; first = *slot; }
        }
        HtNode* end = map->bucket[map->bucketCount];
        u8 changed = 0;
        while (first != end) {
            if (changed) {
                changed = FUN_00ac8050(iface, 0, (char*)first + 0xc) ? 1 : 0;
            } else {
                changed = 0;
            }
            first = first->next;
            while (first == 0) { ++slot; first = *slot; }
        }
    }
    {
        wchar_t* s = tmp.begin;
        if (s == dst.begin) s = g_wEmpty;
        (*(void(__thiscall**)(void*, wchar_t*))((char*)*(void**)iface + 4))(iface, s);
    }
    if (((int)(dst.end - dst.begin) & ~1) > 2 && dst.begin != 0)
        operator_delete__(dst.begin);
    return result;
}

// ================================================================ 0x00ba3ca0
// @ 0x00ba3ca0
PPD* PPD::CopyCtor(const PPD& src) {
    PPD* s = this;
    const PPD& o = src;
    s->vftbl = g_vtbl_PPD1;
    s->b0.Reserve((uint)((o.b0.end - o.b0.begin) >> 4), (void*)&o.b0.cap);
    UninitCopy16(&o.b0.begin, o.b0.begin, o.b0.end, s->b0.begin, (void*)&o.b0.begin);
    s->b0.end = o.b0.begin;
    s->b0.flag = o.b0.flag;
    s->b1.Reserve((uint)((o.b1.end - o.b1.begin) >> 4), (void*)&o.b1.cap);
    UninitCopy16(&o.b1.begin, o.b1.begin, o.b1.end, s->b1.begin, (void*)&o.b1.begin);
    s->b1.end = o.b1.begin;
    s->b1.flag = o.b1.flag;
    s->b2.Reserve((uint)((o.b2.end - o.b2.begin) >> 4), (void*)&o.b2.cap);
    UninitCopy16(&o.b2.begin, o.b2.begin, o.b2.end, s->b2.begin, (void*)&o.b2.begin);
    s->b2.end = o.b2.begin;
    s->b2.flag = o.b2.flag;
    s->b3.Reserve((uint)((o.b3.end - o.b3.begin) >> 4), (void*)&o.b3.cap);
    UninitCopy16(&o.b3.begin, o.b3.begin, o.b3.end, s->b3.begin, (void*)&o.b3.begin);
    s->b3.end = o.b3.begin;
    s->b3.flag = o.b3.flag;
    ((VBlk8*)&s->b4)->Reserve((uint)((o.b4.end - o.b4.begin) >> 3), (void*)&o.b4.cap);
    Copy8(&o.b4.begin, o.b4.begin, o.b4.end, s->b4.begin, (void*)&o.b4.begin);
    s->b4.end = o.b4.begin;
    s->b4.flag = o.b4.flag;
    *(void* volatile*)&s->timerVtbl = g_vtbl_TimerA;
    s->f84 = 0;
    s->f88 = o.f88; s->f8c = o.f8c; s->f90 = o.f90; s->f94 = o.f94;
    s->f98 = o.f98;
    s->f9c = o.f9c;
    s->timerVtbl = g_vtbl_TimerB;
    s->fa0 = o.fa0; s->fa1 = o.fa1; s->fa2 = o.fa2;
    return s;
}

// ================================================================ 0x00ba3ef0
// @ 0x00ba3ef0
void* __fastcall FUN_00ba3ef0(void* self_) {
    char* s = (char*)self_;
    *(void**)s = &g_vtbl_GB1a;
    ((CGZSub*)(s + 4))->Ctor();
    float one = g_f1485720;
    float two = g_f1470f1c;
    *(void**)s = &g_vtbl_GB1b;
    *(void**)(s + 4) = &g_vtbl_GB1c;
    *(void**)(s + 8) = &g_vtbl_GB1d;
    *(float*)(s + 0x30) = one;
    *(float*)(s + 0x34) = two;
    *(int*)(s + 0x2c) = 0;
    *(int*)(s + 0x38) = 0;
    *(int*)(s + 0x28) = 1;
    *(void**)(s + 0x24) = &g_154df28;
    *(float*)(s + 0x50) = one;
    *(float*)(s + 0x54) = two;
    *(int*)(s + 0x4c) = 0;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x48) = 1;
    *(void**)(s + 0x44) = &g_154df28;
    return s;
}

// ================================================================ 0x00ba3f90
// @ 0x00ba3f90
int Goal::Resolve(const void* key, void* a_, void* b_) {
    Goal* self = this;
    char* a = (char*)a_;
    char* b = (char*)b_;
    const uint* k = (const uint*)key;
    void* mode = SP_GetCurrentGameMode();
    if (mode == &g_1654c10) {
        if ((a == 0 || ((*(uint*)(a + 0xb58) >> 9) & 1)) &&
            (b == 0 || ((*(uint*)(b + 0xb58) >> 9) & 1)))
            return 6;
        a = 0;
        if (b == 0 || ((*(uint*)(b + 0xb58) >> 9) & 1)) {
            if (a_ == 0) return 0;
            a = (char*)a_;
            if ((*(uint*)(a + 0xb58) >> 9) & 1) return 0;
        }
        if (a == 0) return 0;
        char ok = (*(char(__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
        if (ok == 0 && *(char*)(a + 0xb5e) == 0) {
            HIter it;
            self->map2.Find(&it, &a);
            if (it.node == self->map2.bucket[self->map2.bucketCount]) {
                void* mgr = *(void**)0x016c7aa4;    // cThingManager singleton
                void* thing = (*(void*(__thiscall**)(void*))((char*)*(void**)mgr + 0x74))(mgr);
                int val;
                if (((*(uint*)(a + 0xb58) >> 8) & 1) == 0) {
                    void* gd = ((GameData*(*)(char*, void*))0x00b18530)(a, thing);
                    val = ((int(__cdecl*)(void*, int, void*))0x00ba28a0)(gd, 0, a);
                } else {
                    val = 6;
                }
                void* slot = self->map2.GetOrAdd2(&a);
                *(int*)slot = val;
                (*(void(__thiscall**)(char*))((char*)*(void**)a + 4))(a);
                return val;
            }
            int r = *(int*)((char*)it.node + 4);
            (*(void(__thiscall**)(char*))((char*)*(void**)a + 4))(a);
            return r;
        }
        (*(void(__thiscall**)(char*))((char*)*(void**)a + 4))(a);
        return 0;
    }
    if (a != 0) {
        if (b != 0) {
            char c1 = (*(char(__thiscall**)(char*))((char*)*(void**)a + 0xd0))(a);
            if (c1 == 0) {
                char c2 = (*(char(__thiscall**)(char*))((char*)*(void**)b + 0xd0))(b);
                if (c2 == 0) goto lab_424d;
            }
        }
        if ((*(char(__thiscall**)(char*))((char*)*(void**)a + 0xd0))(a) != 0) {
            if (b == 0) return 6;
            if ((*(char(__thiscall**)(char*))((char*)*(void**)b + 0xd0))(b) != 0) return 6;
        }
    }
    {
        uint local[3];
        local[0] = k[0]; local[1] = k[1]; local[2] = k[2];
        if (a == 0 || (*(char(__thiscall**)(char*))((char*)*(void**)a + 0xd0))(a) != 0) {
            if (b != 0 && (*(char(__thiscall**)(char*))((char*)*(void**)b + 0xd0))(b) == 0) {
                local[0] = *(uint*)(b + 0xb28);
                local[1] = *(uint*)(b + 0xb2c);
                local[2] = *(uint*)(b + 0xb30);
            }
        } else {
            local[0] = *(uint*)(a + 0xb28);
            local[1] = *(uint*)(a + 0xb2c);
            local[2] = *(uint*)(a + 0xb30);
        }
        HIter it;
        self->map1.Find(&it, local);
        if (it.node != self->map1.bucket[self->map1.bucketCount] &&
            *(int*)((char*)it.node + 0xc) != 0)
            return *(int*)((char*)it.node + 0xc);
    }
    {
        if (a != 0 && ((*(uint*)(a + 0xb58) >> 9) & 1) == 0) {
            void* c = FUN_00c0c1a0(a);
            if (c) return *(int*)((char*)c + 0x390);
        }
        if (b != 0 && ((*(uint*)(b + 0xb58) >> 9) & 1) == 0) {
            void* c = FUN_00c0c1a0(b);
            if (c) return *(int*)((char*)c + 0x390);
        }
    }
lab_424d:
    if (a != 0 && b != 0)
        return ((int(__cdecl*)(char*, char*))0x00ba27b0)(a, b);
    return 0;
}

// ================================================================ 0x00ba4270
// @ 0x00ba4270
int Goal::Field4(const void* key) {
    int* e = (int*)this->map1.GetOrAdd1(key);
    return e[1];
}

// ================================================================ 0x00ba4290
// @ 0x00ba4290
int Goal::AddCount(const void* key, void* obj) {
    int* e = (int*)this->map1.GetOrAdd1(key);
    e[2] = e[2] + 1;
    uint n = (uint)e[2];
    if (obj == 0) return 3;
    void* cm = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)obj + 0xc))(obj, 0xd0036e08);
    if (cm == 0) return 3;
    if (n >= *(uint*)((char*)FUN_00c0c1a0(cm) + 0x40c)) return 6;
    if (n >= *(uint*)((char*)FUN_00c0c1a0(cm) + 0x408)) return 4;
    if (n < *(uint*)((char*)FUN_00c0c1a0(cm) + 0x404))
        return this->Resolve(key, obj, 0);
    return 3;
}

// ================================================================ 0x00ba4330
// @ 0x00ba4330
void Goal::Clear0c(const void* key) {
    int* e = (int*)this->map1.GetOrAdd1(key);
    e[3] = 0;
}

// ================================================================ 0x00ba4350
// @ 0x00ba4350
void Goal::Set10(const void* key, int v) {
    int* e = (int*)this->map1.GetOrAdd1(key);
    e[4] = v;
}

// ================================================================ 0x00ba4370
// @ 0x00ba4370
int Goal::Field8(const void* key) {
    int* e = (int*)this->map1.GetOrAdd1(key);
    return e[2];
}

// ================================================================ 0x00ba4390
// @ 0x00ba4390
int Goal::Field0c(const void* key) {
    int* e = (int*)this->map1.GetOrAdd1(key);
    return e[3];
}

// ================================================================ 0x00ba43b0
// Key ordering used by the sorted-vector blocks: (k0, k2, k1).
static inline bool WKeyLess(const WKey* a, const WKey* b) {
    if (a->k0 != b->k0) return a->k0 < b->k0;
    if (a->k2 != b->k2) return a->k2 < b->k2;
    return a->k1 < b->k1;
}

__declspec(noinline) void* __cdecl LowerBound16(void* begin, void* end, const WKey* key, u8 flag); // 0x00ba2e50

// @ 0x00ba43b0
void* __thiscall VBlk::InsertAt(char* pos, const WKey* key) {
    VBlk* self = this;
    char* end = self->end;
    char* at = pos;
    if (pos != end && WKeyLess(key, (const WKey*)pos))
        at = self->begin;
    at = (char*)LowerBound16(at, end, key, self->flag);
    if (at == end || WKeyLess((const WKey*)at, key))
        at = (char*)((Vec16*)self)->InsertSorted(at, (void*)key);
    return at;
}

// ================================================================ 0x00ba4520
// @ 0x00ba4520
void* __thiscall VBlk::FindOrAdd2(const WKey* key) {
    VBlk* self = this;
    char* end = self->end;
    char* at = (char*)LowerBound16(self->begin, end, key, self->flag);
    if (at == end || WKeyLess(key, (const WKey*)at)) {
        WKey tmp = *key;
        at = (char*)self->InsertAt(at, &tmp);
    }
    return at + 0xc;
}

// ================================================================ 0x00ba4430
// @ 0x00ba4430
PPD* PPD::Assign(const PPD& src) {
    PPD* s = this;
    const PPD& o = src;
    s->b0.Assign((VBlk*)&o.b0); s->b0.flag = o.b0.flag;
    s->b1.Assign((VBlk*)&o.b1); s->b1.flag = o.b1.flag;
    s->b2.Assign((VBlk*)&o.b2); s->b2.flag = o.b2.flag;
    s->b3.Assign((VBlk*)&o.b3); s->b3.flag = o.b3.flag;
    s->b4.Assign((VBlk8*)&o.b4); s->b4.flag = o.b4.flag;
    s->f88 = o.f88; s->f8c = o.f8c; s->f90 = o.f90; s->f94 = o.f94;
    s->f98 = o.f98;
    s->f9c = o.f9c;
    s->fa0 = o.fa0; s->fa1 = o.fa1; s->fa2 = o.fa2;
    return s;
}

// ================================================================ 0x00ba45a0
// @ 0x00ba45a0
void* __cdecl FUN_00ba45a0(char* begin, char* end, char* dst) {
    char* d = dst;
    char* e = end;
    if (e != begin) {
        do {
            e -= 0xb0;
            d -= 0xb0;
            *(int*)d = *(int*)(e + 0);
            ((PPD*)(d + 8))->Assign(*(PPD*)(e + 8));
        } while (e != begin);
    }
    return d;
}

// ================================================================ 0x00ba4600
// @ 0x00ba4600
void __cdecl FUN_00ba4600(void* obj) {
    if (obj == 0) return;
    void* o = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)obj + 0xc))(obj, 0xd0036e08);
    if (o == 0) return;
    ((ContObj*)SP_AchievementsController())->AutoTest(0x94f5e078, 1);
    FUN_00ba5e10(obj, 6);
    char* cm = (char*)FUN_00c04590(o);
    ((void(__cdecl*)(int, int, int, int))0x00b97600)(
        *(int*)(cm + 0x8c), *(int*)(cm + 0x88), *(int*)(cm + 0xf0),
        *(int*)((char*)obj + 0xb20));
    void* nm = SP_NounManager();
    AnimCtx* vec = (AnimCtx*)FUN_00b21340(nm, 0xcd7d10, 0xd3d420, 0xaccc30, 0xb1e500, 0x1be418e);
    char** end = (char**)((char*)vec + 8);
    for (char** v = (char**)*(void**)((char*)vec + 4); v != end; ++v) {
        char* e = *v;
        if (*(int*)(e + 0xa4) == *(int*)(cm + 0xa4))
            ((ThingIn*)e)->Set0x120();
    }
    void* k = FUN_00c0bc00();
    ((PropObj*)FUN_0067cb30())->UpdateProperty(0xaba34d01, k);
}

// ================================================================ 0x00ba46f0
// @ 0x00ba46f0
void __cdecl FUN_00ba46f0(void* obj, int flag) {
    if (obj == 0) return;
    void* o = (*(void*(__thiscall**)(void*, uint))((char*)*(void**)obj + 0xc))(obj, 0xd0036e08);
    if (o == 0) return;
    if ((char)flag != 0 && SP_GetCurrentGameMode() == (void*)0x01654c01)
        ((ContObj*)SP_AchievementsController())->AutoTest(0x19d844e6, 1);
    char* cm = (char*)FUN_00c04590(o);
    void* nm = SP_NounManager();
    AnimCtx* vec = (AnimCtx*)FUN_00b21340(nm, 0xcd7d10, 0xd3d420, 0xaccc30, 0xb1e500, 0x1be418e);
    char** end = (char**)((char*)vec + 8);
    for (char** v = (char**)*(void**)((char*)vec + 4); v != end; ++v) {
        char* e = *v;
        if (*(int*)(e + 0xa4) == *(int*)(cm + 0xa4))
            ((ThingIn2*)e)->Set((u8)flag);
    }
}
