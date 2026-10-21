// Slice s00bbe5f0: Simulator gameplay helpers -- colony building limits, city-building bookkeeping,
// terraforming/game-mode gate, an intrusive linked list, EASTL heap/sort algorithm internals, and
// the cGonzagoSubsystem-derived cSaveGameSubsystem-like object (0x00bbe5f0..0x00bbf628).
// Flags region: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <math.h>

typedef unsigned int uint;

#pragma pack(push, 4)

// ---------------------------------------------------------------------------------------------
// Externals (game module @ 0x00B...: relocations are masked, so only the call shape matters).
extern "C" void* EAAllocate(uint size, const char* pName, int a, int b, void* site, int d);  // 0x00f473a0
extern "C" void  operator_delete__(void* p);                                             // 0x00f47380
extern "C" void* g_EAAllocSite;                                                          // 0x013ebb38
extern "C" void __stdcall FUN_00bbdff0(int a, float b);                                  // 0x00bbdff0

// Simulator object accessors.
struct cGameNounManager;
void* GetStarManager();                               // 0x00b3d2a0

struct PlanetRecord;
extern "C" PlanetRecord* GetActivePlanetRecord();      // 0x010212a0
extern "C" PlanetRecord* GetActivePlanet();            // 0x01021260
extern "C" void* GetUniverseContext();                 // 0x01021080
extern "C" void* GetPlayerEmpire();                    // 0x01021300
extern "C" void* GetCurrentGameMode();                 // 0x00b5b800
extern "C" void* GetSpaceCombatTuning();               // 0x0102940
extern "C" void* FUN_01049a10();                       // TerraformTuning getter
extern "C" void* TerraformingManager();                // 0x00b3d430

// PlanetRecord (retail) -- the fields touched here.
struct PlanetRecord {
    uint8_t  pad00[0x2c];
    uint32_t flags2c;              // +0x2c
    uint8_t  pad30[0x80];
    uint32_t p_b0;                 // +0xb0
    uint32_t p_b4;                 // +0xb4
    uint32_t p_bc;                 // +0xbc  (array begin)
    uint32_t p_c0;                 // +0xc0  (array end)
    uint8_t  padc4[0xc];
    uint32_t p_d0;                 // +0xd0
    uint32_t p_d4;                 // +0xd4
    uint8_t  pade0[0x5c];
    uint32_t p_13c;                // +0x13c
};

extern "C" int FUN_00fc2080(uint32_t a, uint32_t b);
extern "C" int FUN_00c70e00(void* p);
extern "C" void FUN_00c308e0(void* self, void* arg);
extern "C" void FUN_00c73520(void* self, void** out);
extern "C" int  FUN_00bbd180(void* a, int b, int c, int d, void* e, void* f);
extern "C" void FUN_00bbd1f0(void* a, int b, int c, void* d, void* e, void* f);
extern "C" void FUN_00bbcb10(void* a, void* b);
extern "C" void FUN_00bbcb90(int a, void* b);
extern "C" void* FUN_00bbc870(void* out, int a, uint32_t key, PlanetRecord* r);
extern "C" void FUN_00bbc950(void* out, int a, int b, PlanetRecord* r);
extern "C" void FUN_00bbca30(void* out, int a, PlanetRecord* r);
extern "C" void FUN_00401090(void* a, ...);
extern "C" int  FUN_004df550(void* p);

// Globals.
extern "C" float g_kOne;          // 0x01485720
extern "C" float g_kTwoThirds2;   // 0x01470f1c
extern "C" void* g_0168a488; extern "C" void* g_0168a48c; extern "C" void* g_0168a490;

// The three building/colony limit helpers on a terraform-tuning object.
struct ViewTuning {
    int getT1();   // 0x01049e70
    int getT2();   // 0x01049eb0
    int getT3();   // 0x01049ef0
};

// Stub views used to obtain `mov/lea ecx, subobject; call <ext>` codegen.
#pragma pack(push, 1)
struct ViewVector  { void dtor(); };                       // 0x00ae6970
struct ViewRBTree  { void nuke(void* p); };                // 0x009a9600
struct ViewHash1c  { void* m0; void* m4; uint32_t cnt8; uint32_t n_c;
                     void release(void* a, void* b);       // 0x01068400
                     void find(void* o8, void* o4);        // 0x00a3b2c0
                     void insert(const void* pair8); };    // 0x00bbd0e0
struct ViewGonzago { void ctor();                          // 0x00b5b960
                     void dtor(); };                       // 0x00b5b9a0
struct ViewRefObj  { virtual void addRef(); virtual void release(); };
struct ViewRecord  {                                     // record methods
    void*       getNoun();                 // 0x00b8de30
    int         FUN_00bbce40();            // 0x00bbce40
};
struct ViewStar    { void* FUN_00885c90(); };             // 0x00885c90
struct ViewNoun    { void* GetAvatar(); };                // 0x00b1fdb0
struct ViewCivData { void* GetCities(); };                // 0x005c65e0
struct ViewSCTuning{ float* GetModelOffset(); };          // 0x0102a3e0
struct ViewCity    { int GetNumBuildings();               // 0x00ff0870
                     int GetNumTurrets();                 // 0x00ff0760
                     void ClampBuildings(int a, void* b); };// 0x00ff1da0
struct ViewTerrMgr { int FUN_00bbe5f0(PlanetRecord* r); }; // 0x00bbe5f0 self call
#pragma pack(pop)

// Intrusive intrusive_ptr / ref-count object vcall helper.
struct RefObj { virtual void addRef(); virtual void release(); };
struct RefObj2 { virtual void addRef(); virtual void release(); };

// b3d420 / b90410 / b8f860 species helpers (thiscall, unused return).
struct ViewSpecies {
    void* FUN_00b3d420();     // 0x00b3d420
    void* FUN_00b90410();     // 0x00b90410
    int   FUN_00b8f860();     // 0x00b8f860
};

// The record table helpers.
extern "C" int FUN_00bbcda0(int a, PlanetRecord* r);
extern "C" int FUN_00bbc6a0(int a, PlanetRecord* r);

// -----------------------------------------------------------------------------------------------
// The 'self' object whose vtable dispatches this slice's thiscall entry points.
struct SimSelf {
    int  FUN_00bbe5f0(PlanetRecord* r);
    int  FUN_00bbe740(PlanetRecord* r);
    bool FUN_00bbe850(int n, int t, PlanetRecord* r);
    int  FUN_00bbecc0(int* buildingId, PlanetRecord* r, int key, uint8_t* out);
    int  FUN_00bbee30(int* buildingId, int key, uint8_t flag, PlanetRecord* r, uint8_t* out);
    void FUN_00bbf2b0(PlanetRecord* r);
    void FUN_00bbec40(int a, float b);
};

// @ 0x00bbe5f0
// Max-buildings on the active planet's colony: counts T1/T2/T3 buildable tiers.
int SimSelf::FUN_00bbe5f0(PlanetRecord* record)
{
    if (record == 0)
        record = GetActivePlanetRecord();

    void* noun = ((ViewRecord*)record)->getNoun();
    void* star = GetStarManager();
    void* gang0 = ((ViewStar*)star)->FUN_00885c90();
    void* avatar = ((ViewNoun*)noun)->GetAvatar();

    if (avatar == gang0) {
        void* civ = ((ViewRecord*)record)->getNoun();
        float* cities = (float*)((ViewCivData*)civ)->GetCities();
        float fVar2 = (float)sqrt(cities[0] * cities[0] + cities[1] * cities[1] + cities[2] * cities[2]);
        void* tm = GetStarManager();
        float fVar1 = *(float*)((char*)tm + 0x1bc);
        GetSpaceCombatTuning();
        float* lim = ((ViewSCTuning*)GetSpaceCombatTuning())->GetModelOffset();
        int cVar10 = fVar2 < lim[0] * fVar1;
        if (fVar2 < lim[1] * fVar1)
            cVar10 += 1;
        if (fVar2 < lim[2] * fVar1)
            cVar10 += 1;
        switch (cVar10) {
        case 0: return 1;
        case 1: return ((ViewTuning*)FUN_01049a10())->getT1();
        case 2: return ((ViewTuning*)FUN_01049a10())->getT2();
        case 3: return ((ViewTuning*)FUN_01049a10())->getT3();
        }
    }

    if ((record->flags2c & 0x800) != 0)
        return 1;
    int tier = ((ViewRecord*)record)->FUN_00bbce40();
    if (tier == 1) return ((ViewTuning*)FUN_01049a10())->getT1();
    if (tier == 2) return ((ViewTuning*)FUN_01049a10())->getT2();
    if (tier != 3) return 1;
    return ((ViewTuning*)FUN_01049a10())->getT3();
}

// @ 0x00bbe740
int SimSelf::FUN_00bbe740(PlanetRecord* record)
{
    int total = 0;
    if (record == 0)
        record = GetActivePlanet();

    if (FUN_00c70e00(record) == 5 && GetCurrentGameMode() == (void*)0x01654c05) {
        void* emp = GetPlayerEmpire();
        FUN_00c308e0(emp, (void*)record->p_13c);
        PlanetRecord* active = GetActivePlanet();
        if (record != active || GetUniverseContext() != 0) {
            void* begin = 0; void* end = 0;
            FUN_00c73520(record, &begin);
            for (void** it = (void**)begin; it != (void**)end; ++it) {
                void* city = *it;
                int n = ((ViewCity*)city)->GetNumBuildings();
                int t = ((ViewCity*)city)->GetNumTurrets();
                void* arg = (void*)record->p_13c;
                TerraformingManager();
                int mx = ((ViewTerrMgr*)arg)->FUN_00bbe5f0(arg ? record : record);
                (void)mx;
                if (mx < n + t) {
                    ((ViewCity*)city)->ClampBuildings(mx, (void*)record->p_13c);
                    total += (n + t) - mx;
                }
            }
            if (begin != 0 && ((int*)begin)[-1] != 0)
                operator_delete__(begin);
        }
        return total;
    }
    return 0;
}

// @ 0x00bbe850
bool SimSelf::FUN_00bbe850(int param_1, int param_2, PlanetRecord* record)
{
    if (record == 0)
        record = GetActivePlanetRecord();
    if (param_1 != 1) {
        if (FUN_00bbcda0(param_1 - 1, record) == 0)
            return false;
    }
    if (param_2 < 4)
        return true;
    return param_1 * 3 <= (int)(record->p_c0 - record->p_bc) / 0xc;
}

// -----------------------------------------------------------------------------------------------
// Free-function helpers (cdecl) -- EASTL internals.

// @ 0x00bbe8c0
// A small construct helper: allocate a 0x18 node, copy an int + 4 floats, clear +0x14.
struct Node18 { int a; float b, c, d, e; };
struct SimAllocHelper { void* FUN_00bbe8c0(const Node18* src); };
void* SimAllocHelper::FUN_00bbe8c0(const Node18* src)
{
    Node18* p = (Node18*)EAAllocate(0x18, "Simulator", 0, 0, &g_EAAllocSite, 0xd1);
    if (p != 0) {
        p->a = src->a;
        p->b = src->b;
        p->c = src->c;
        p->d = src->d;
        p->e = src->e;
    }
    *(int*)((char*)p + 0x14) = 0;
    return p;
}

// @ 0x00bbe910
// Allocate a 0x14 list node carrying 3 dwords, and link it in after `head`.
struct SimListHelper { void FUN_00bbe910(int head, int* payload); };
void SimListHelper::FUN_00bbe910(int head, int* payload)
{
    int* node = (int*)EAAllocate(0x14, "Simulator", 0, 0, &g_EAAllocSite, 0xd1);
    int* dst = node + 2;
    if (dst != 0) {
        dst[0] = payload[0];
        dst[1] = payload[1];
        dst[2] = payload[2];
    }
    node[0] = head;
    node[1] = *(int*)(head + 4);
    **(int**)(head + 4) = (int)node;
    *(int**)(head + 4) = node;
}

// @ 0x00bbe970
// EASTL insertion sort over an array of ref-counted pointers with a comparison functor.
void FUN_00bbe970(RefObj** begin, RefObj** end, bool (*cmp)(RefObj*, RefObj*))
{
    for (RefObj** cur = begin + 1; cur != end; ++cur) {
        RefObj* val = *cur;
        if (val != 0)
            val->addRef();
        RefObj** pos = cur;
        while (pos != begin && cmp(val, pos[-1])) {
            RefObj* prev = pos[-1];
            RefObj* here = *pos;
            if (prev != here) {
                if (prev != 0) prev->addRef();
                *pos = prev;
                if (here != 0) here->release();
            }
            --pos;
        }
        RefObj* at = *pos;
        if (val != at) {
            if (val != 0) val->addRef();
            *pos = val;
            if (at != 0) at->release();
        }
        if (val != 0) val->release();
    }
}

// @ 0x00bbea40
// EASTL heap-sift-down (with functor) -- used by make_heap/sort.
void FUN_00bbea40(RefObj2** a, int lo, int hi, int hole, RefObj2* value, bool (*cmp)(void*, void*))
{
    int i = hole;
    for (;;) {
        int child = i * 2 + 2;
        if (hi <= child) break;
        if (cmp(a[child], a[child - 1]))
            --child;
        RefObj2* cur = a[i];
        RefObj2* nxt = a[child];
        if (nxt != cur) {
            if (nxt != 0) nxt->addRef();
            a[i] = nxt;
            if (cur != 0) cur->release();
        }
        i = child;
    }
    if (i == hi) {
        RefObj2* cur = a[i];
        RefObj2* nxt = a[i - 1];
        if (nxt != cur) {
            if (nxt != 0) nxt->addRef();
            a[i] = nxt;
            if (cur != 0) cur->release();
        }
        ++i;
    }
    if (value != 0)
        value->addRef();
    FUN_00bbd1f0(a, lo, i, value, cmp, value);
    if (value != 0)
        value->release();
}

// @ 0x00bbeb20
// EASTL make_heap: sift-down from the middle outward.
void FUN_00bbeb20(RefObj** a, RefObj** end, bool (*cmp)(void*, void*))
{
    int n = (int)((char*)end - (char*)a) >> 2;
    if (1 < n) {
        int i = ((n - 2) >> 1) + 1;
        do {
            int v = (int)a[i - 1];
            --i;
            FUN_00bbd180(a, i, n, i, (void*)v, (void*)cmp);
        } while (i != 0);
    }
}

// @ 0x00bbeb60
// EASTL sort_heap.
void FUN_00bbeb60(RefObj** a, RefObj** end, bool (*cmp)(void*, void*))
{
    int n = (int)((char*)end - (char*)a) >> 2;
    if (1 < n) {
        RefObj** p = end - 1;
        do {
            int v = (int)*p;
            *p = *a;
            FUN_00bbd180(a, 0, n - 1, 0, (void*)v, (void*)cmp);
            --p;
            n = (int)((char*)p - (char*)a) >> 2;
        } while (1 < n);
    }
}

// @ 0x00bbebb0
// cGonzagoSubsystem-derived destructor body.
struct SimSubDtor { void FUN_00bbebb0(); };
void SimSubDtor::FUN_00bbebb0()
{
    ViewHash1c* h = (ViewHash1c*)((char*)this + 0x1c);
    char* p = (char*)this;
    *(void**)p = (void*)0x01466670;
    *(void**)(p + 4) = (void*)0x0146666c;
    ((ViewVector*)(p + 0x68))->dtor();
    ((ViewRBTree*)(p + 0x48))->nuke(*(void**)(p + 0x54));
    h->release(*(void**)(p + 0x20), *(void**)(p + 0x24));
    uint cnt = h->cnt8;
    h->n_c = 0;
    if (cnt > 1)
        operator_delete__(h->m4);
    ((ViewGonzago*)p)->dtor();
}

// @ 0x00bbec40
void SimSelf::FUN_00bbec40(int a, float b)
{
    FUN_00bbdff0(a, b);
}

// @ 0x00bbec60
// hashtable<...>::insert-tracking helper: returns true when a new key was inserted.
struct SimHashOwner { bool FUN_00bbec60(int key); };
bool SimHashOwner::FUN_00bbec60(int key)
{
    char* p = (char*)this;
    int local_8 = 0;
    int local_4 = 0;
    ViewHash1c* ht = (ViewHash1c*)(p + 0x1c);
    ht->find(&local_8, &key);
    if (local_8 == *(int*)(*(int*)(p + 0x20) + *(int*)(p + 0x24) * 4))
        return false;
    struct Pair8 { int a; int b; } pair;
    pair.a = local_8;
    pair.b = local_4;
    ht->insert(&pair);
    *(uint8_t*)(p + 0x3c) = 1;
    return true;
}

// @ 0x00bbecc0
int SimSelf::FUN_00bbecc0(int* buildingId, PlanetRecord* record, int param_2, uint8_t* out)
{
    if (record == 0)
        record = GetActivePlanetRecord();
    PlanetRecord* r2 = record ? record : GetActivePlanetRecord();
    if (FUN_00fc2080(r2->p_b0, r2->p_b4) == 0)
        return 0;

    int count = (int)(record->p_c0 - record->p_bc) / 0xc;
    int i = 0, matches = 0;
    for (int off = 0; i < count; ++i, off += 0xc) {
        int* e = (int*)(record->p_bc + off);
        if (buildingId[0] == e[0] && buildingId[1] == e[1] && buildingId[2] == e[2])
            return 1;
        void* s1 = ((ViewSpecies*)e)->FUN_00b3d420();
        (void)s1;
        ((ViewSpecies*)e)->FUN_00b90410();
        if (((ViewSpecies*)e)->FUN_00b8f860() == param_2)
            ++matches;
    }
    ++matches;

    uint8_t cVar2;
    if (param_2 == 0x6d60a1cc) cVar2 = 1;
    else cVar2 = (uint8_t)((param_2 != 0x29c388a) + 2);

    bool bVar1 = false;
    if (matches < 4) {
        PlanetRecord* r3 = record ? record : GetActivePlanetRecord();
        r3 = r3 ? r3 : GetActivePlanetRecord();
        int lim = FUN_00fc2080(r3->p_b0, r3->p_b4);
        if (matches <= lim) {
            bVar1 = true;
            if (FUN_00bbe850(matches, cVar2, record) != 0)
                return 1;
        }
    }
    if (out) *out = !bVar1;
    return 0;
}

// @ 0x00bbee30
int SimSelf::FUN_00bbee30(int* buildingId, int param_2, uint8_t param_3, PlanetRecord* record, uint8_t* out)
{
    uint8_t flag = param_3;
    if (record == 0)
        record = GetActivePlanetRecord();
    PlanetRecord* r2 = record ? record : GetActivePlanetRecord();
    if (FUN_00fc2080(r2->p_b0, r2->p_b4) == 0) {
        if (out) *out = 1;
        return 0;
    }

    if ((record->flags2c & 0x800) != 0) {
        if (out) *out = 0;
        int limit = 100;
        void* tun = FUN_01049a10();
        void* sub = *(void**)tun;
        if (sub != 0) {
            int ok = (*(int(**)(void*, uint8_t*, int))(*(int*)sub + 0x24))(sub, &flag, 0x05469bf8);
            if (ok && *(short*)((char*)buildingId + 0x12) == 9) {
                int* v = (int*)0;
                (void)v;
                limit = 0;
                if (limit < 1) return 1;
            }
        }
        if ((int)(record->p_d4 - record->p_d0) / 0xc < limit)
            return 1;
        return 0;
    }

    int off = 0, a = 0, b = 0, n = 0;
    FUN_00401090((void*)0);
    int count = (int)(record->p_d4 - record->p_d0) / 0xc;
    int i = 0;
    for (; i < count; ++i, off += 0xc) {
        int* e = (int*)(record->p_d0 + off);
        if (buildingId[0] == e[0] && buildingId[1] == e[1] && buildingId[2] == e[2])
            return 1;
        int o = FUN_004df550(e);
        if (o != 0) {
            if (*(int*)(o + 0x608) == 0) ++a;
            else ++b;
        }
        n = a;
    }
    (void)n;

    if (flag == 0) {
        int half = a / 2 + 1;
        uint urem = (uint)a & 0x80000001u;
        if ((int)urem < 0) urem = (urem - 1 | 0xfffffffeu) + 1;
        if (half < 4 && FUN_00bbc6a0(half, record) != 0) {
            flag = 1;
            if (FUN_00bbe850(half, (int)urem + 4, record) != 0)
                return 1;
        } else {
            flag = 0;
        }
        if (out) *out = (flag == 0);
    } else {
        ++b;
        bool bVar1 = false;
        if (b < 4 && FUN_00bbc6a0(b, record) != 0) {
            bVar1 = true;
            if (FUN_00bbe850(b, 6, record) != 0)
                return 1;
        }
        if (out) { *out = !bVar1; return 0; }
    }
    return 0;
}

// @ 0x00bbf130
// EASTL partial_sort / nth_element composite.
void FUN_00bbf130(RefObj** a, RefObj** mid, RefObj** end, bool (*cmp)(void*, void*))
{
    FUN_00bbeb20(a, mid, cmp);
    for (RefObj** it = mid; it < end; ++it) {
        if (cmp(*it, *a)) {
            RefObj* v = *it;
            *it = *a;
            FUN_00bbd180(a, 0, (int)((char*)mid - (char*)a) >> 2, 0, (void*)v, (void*)cmp);
        }
    }
    FUN_00bbeb60(a, mid, cmp);
}

// @ 0x00bbf1a0
// EASTL make_heap over an array of ref-counted pointers.
void FUN_00bbf1a0(RefObj2** a, RefObj2** end, bool (*cmp)(void*, void*))
{
    int n = (int)((char*)end - (char*)a) >> 2;
    if (1 < n) {
        int i = ((n - 2) >> 1) + 1;
        do {
            --i;
            RefObj2* v = a[i];
            if (v != 0)
                v->addRef();
            FUN_00bbea40(a, i, n, i, v, cmp);
        } while (i != 0);
    }
}

// @ 0x00bbf1f0
// cSaveGameSubsystem-like constructor (cGonzagoSubsystem-derived).
struct SimSaveGame { void* FUN_00bbf1f0(); };
void* SimSaveGame::FUN_00bbf1f0()
{
    char* p = (char*)this;
    ((ViewGonzago*)p)->ctor();
    float kOne = g_kOne;
    float kTwo = g_kTwoThirds2;
    *(void**)p = (void*)0x01466670;
    *(void**)(p + 4) = (void*)0x0146666c;
    *(float*)(p + 0x2c) = kOne;
    *(float*)(p + 0x30) = kTwo;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x34) = 0;
    *(void**)(p + 0x20) = (void*)0x0154df28;
    *(int*)(p + 0x24) = 1;
    *(uint8_t*)(p + 0x3c) = 1;
    *(uint8_t*)(p + 0x44) = 0;
    *(int*)(p + 0x40) = -1;
    *(int*)(p + 0x50) = 0;
    *(int*)(p + 0x54) = 0;
    *(int*)(p + 0x58) = 0;
    *(int*)(p + 0x54) = 0;
    *(uint8_t*)(p + 0x58) = 0;
    *(int*)(p + 0x5c) = 0;
    *(void**)(p + 0x50) = p + 0x4c;
    *(void**)(p + 0x4c) = p + 0x4c;
    *(int*)(p + 0x64) = 0;
    *(int*)(p + 0x68) = 0;
    *(int*)(p + 0x6c) = 0;
    *(int*)(p + 0x70) = 0;
    *(int*)(p + 0x7c) = 0;
    *(int*)(p + 0x80) = 0;
    *(int*)(p + 0x84) = 0;
    *(int*)(p + 0x88) = 0;
    *(int*)(p + 0x8c) = 0;
    *(int*)(p + 0x90) = 0;
    return p;
}

// @ 0x00bbf2b0
// Iterate colony tiers 3..1 and refresh the cached building data.
void SimSelf::FUN_00bbf2b0(PlanetRecord* record)
{
    if (record == 0)
        record = GetActivePlanet();

    PlanetRecord* r0 = (PlanetRecord*)record->p_13c;
    if (r0 == 0)
        r0 = GetActivePlanetRecord();
    int lim = FUN_00fc2080(r0->p_b0, r0->p_b4);
    uint uVar2 = *(uint*)(record->p_13c + 0x2c);

    for (int tier = 3; tier >= 1; --tier) {
        if (lim < tier) {
            FUN_00bbcb90(tier, record);
        } else {
            PlanetRecord* r1 = (PlanetRecord*)record->p_13c;
            if (r1 == 0)
                r1 = GetActivePlanetRecord();
            if (r1 == 0)
                r1 = GetActivePlanetRecord();
            int lim2 = FUN_00fc2080(r1->p_b0, r1->p_b4);
            if (lim2 < tier) {
                FUN_00bbcb90(tier, record);
            } else {
                int tmp[3];
                void* p = FUN_00bbc870(tmp, tier, 0x6d60a1cc, record);
                int uVar10 = (p != 0) ? 1 : 1;
                (void)uVar10;
                FUN_00bbc870(tmp, tier, 0x29c388a, record);
                FUN_00bbc870(tmp, tier, 0x3a8be428, record);
                if (((uVar2 >> 0xb) & 1) == 0) {
                    int out[3];
                    FUN_00bbc950(out, tier, 1, record);
                    FUN_00bbc950(out, tier, 0, record);
                    FUN_00bbca30(out, tier, record);
                }
            }
        }
    }
}
