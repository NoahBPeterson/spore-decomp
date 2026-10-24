// Slice s00c97220 -- SP::cTribe::LoadTribeArchetypeData (0x00c97220, static, 1976 bytes).
// Loads three groups (property-list group ids 0xab83a874, 0x27adfe33, 0xf29db649) of tribe archetype
// property lists into the global 3 x 32 archetype table (stride 0xb8): each list has an archetype index
// (property 0x64aaf64e, 1..31) and a set of uint/float/vector2/uint-array fields. Sets a loaded flag.
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc: no EH frame despite RAII locals)
#include "types.h"
#include <string.h>

struct Property {
    void*    mpData;      // +0x00 (array data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = array / external data)
    uint16_t mnType;      // +0x12

    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};

class cPropertyList {
public:
    virtual int  AddRef();                                       // 0x00
    virtual int  Release();                                      // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
};

struct Vec2 { float x, y; };

bool __cdecl GetPropertyAsUint32Array(cPropertyList* pl, uint32_t id, int* count, uint32_t** data);   // 0x006a0840
void __cdecl GetPropertyAsVector2(cPropertyList* pl, uint32_t id, Vec2* out);                        // 0x006a10c0

extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk
extern "C" void* __cdecl FUN_011e073e(void* dst, int c, unsigned n);              // memset thunk
void operator delete[](void* p);                                                 // 0x00f47380

class cPropertyManager {
public:
    virtual int  v00(); virtual int v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** result);   // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44();
    virtual void GetPropertyListIDs(uint32_t groupID, struct SpVec* ids);                          // 0x48
};
cPropertyManager* __cdecl PropertyManager();                                                       // 0x0067de30

// eastl::vector<uint32_t, sp_vector_allocator>
struct SpVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;

    void reserve(uint32_t n);                                    // 0x004e0880 (ret 4)
    void DoInsertValue(uint32_t* pos, const uint32_t& v);        // 0x004558a0 (ret 8)
    void clear()
    {
        uint32_t* first = mpBegin;
        uint32_t* last = mpEnd;
        FUN_011e0744(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd = mpEnd - (last - first);
    }
    void push_back(const uint32_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    void free()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator delete[](mpBegin);
    }
};

struct PLRef {
    cPropertyList* p;
    PLRef& operator=(cPropertyList* rhs)
    {
        if (p != rhs) {
            cPropertyList* old = p;
            if (rhs) rhs->AddRef();
            p = rhs;
            if (old) old->Release();
        }
        return *this;
    }
};

// One archetype record (stride 0xb8)
struct TribeArchetype {
    uint32_t f00, f04, f08;       // +0x00
    uint32_t list[16];            // +0x0c
    uint32_t listCount;           // +0x4c
    uint32_t f50;                 // +0x50
    uint32_t f54;
    float    f58, f5c, f60, f64, f68, f6c, f70, f74, f78;   // +0x58
    uint32_t pad7c[4];            // +0x7c
    uint32_t f8c;                 // +0x8c
    float    f90, f94;            // +0x90
    Vec2     v98;                 // +0x98
    SpVec    textures;            // +0xa0
    uint32_t padb0;
    cPropertyList* mpRef;         // +0xb4

    TribeArchetype()
    {
        f00 = 3;
        f04 = 10;
        f08 = 12;
        f50 = 0xb750af68;
        f8c = 0;
        f90 = 10.0f;
        f94 = 10.0f;
        textures.mpBegin = 0;
        textures.mpEnd = 0;
        textures.mpCapacity = 0;
        mpRef = 0;
        FUN_011e073e(list, 0, 0x40);
        listCount = 0;
        FUN_011e073e(&f54, 0, 0x38);
    }
    ~TribeArchetype()
    {
        if (mpRef) mpRef->Release();
        textures.free();
    }
    TribeArchetype& operator=(const TribeArchetype& o);           // 0x00c96840 (ret 4)
};

extern TribeArchetype gTribeArchetypes[96];                       // 0x01695458
extern bool gTribeArchetypesLoaded;                               // 0x01695371

// ---- tribe instance object model -------------------------------------------------------------
struct Vec3 { float x, y, z; };

extern float kRegionScale;   // 0x01470f1c
extern float kRegionBias;    // 0x01473c2c

// Ref-counted engine object reached through raw pointers in the instance map.
struct cRefObj { virtual void AddRef(); virtual void Release(); virtual void Release2(); };

// One bucket record inside the instance hash map (at cTribe+0x4e4).
struct SlotPair { uint32_t a, b, c, d; };

struct RegionSlot {
    uint32_t  pad00[2];       // +0x00
    uint32_t* mpBegin;        // +0x08  first bucket entry
    uint32_t  m0c;            // +0x0c
    uint32_t* mpBucketEnd;    // +0x10  end of the current bucket
    uint32_t** mpBuckets;     // +0x14  per-bucket start pointers
    uint32_t* mpEnd;          // +0x18  overall end of the value array
    uint32_t* mpValueBase;    // +0x1c  value array base
    uint32_t* mpCapacity;     // +0x20  value array capacity
    uint32_t  m24;            // +0x24

    SlotPair& Lo() { return *(SlotPair*)&mpBegin; }     // +0x08 .. +0x14
    SlotPair& Hi() { return *(SlotPair*)&mpEnd; }       // +0x18 .. +0x24

    void Update(const SlotPair* out, SlotPair value);   // 0x00c95660
    void Insert(void** value);                          // 0x00c92bd0
};

struct TribeMap {             // cTribe+0x4e4
    uint32_t  m00;            // +0x00
    uint32_t  m04;            // +0x04
    uint32_t  m08;            // +0x08
    uint32_t  m0c;            // +0x0c

    RegionSlot* Find(const uint32_t* key);              // 0x00c96950
    void Destroy(uint32_t a, uint32_t b);               // 0x00c95930
};

// Same layout, but torn down by a different helper (the map at cTribe+0x394).
struct TribeMapB {
    uint32_t  m00;
    uint32_t  m04;
    uint32_t  m08;
    uint32_t  m0c;

    void Destroy(uint32_t a, uint32_t b);               // 0x00c93700
};

void SlotRehash(SlotPair* out, SlotPair lo, SlotPair hi, uint32_t** extra);   // 0x00c8ecb0
void RegionSlotUpdate(RegionSlot* slot, const SlotPair* out);   // 0x00c95660

void __fastcall SubDtor_cc7c50(void* p);                  // 0x00cc7c50
void __fastcall SubDtor_b638b0(void* p);                  // 0x00b638b0
void __fastcall SubDtor_afbad0(void* p);                  // 0x00afbad0
void __fastcall SubDtor_ae6970(void* p);                  // 0x00ae6970
void __fastcall SubDtor_ad92d0(void* p);                  // 0x00ad92d0
void __fastcall SubDtor_b6edf0(void* p);                  // 0x00b6edf0
void __fastcall SubDtor_cee7a0(void* p);                  // 0x00cee7a0
void __fastcall SubDtor_ac0520(void* p);                  // 0x00ac0520
void __fastcall SubDtor_c8a420(void* p);                  // 0x00c8a420
void __fastcall SubDtor_c2e4e0(void* p);                  // 0x00c2e4e0
void __fastcall BaseDtor(void* p);                        // 0x00bdd680

// The object embedded at cTribe+0x120 (its vptr lives there as well).
struct cTribeSub120 {
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual void s0c(); virtual void s10(); virtual void s14();
    virtual void s18(); virtual void s1c(); virtual void s20();
    virtual void s24(); virtual void s28();
    virtual bool Query();                                 // slot 0x2c
};

// Vtable of the instance itself; slot 0x24 (+0x90) yields the value list.
typedef SpVec* (__thiscall* cGetValueListFn)(void* self);
struct cTribeVtbl {
    void* mSlots[36];                 // +0x00 .. +0x8c
    cGetValueListFn GetValueList;     // +0x90
};

// Random source used for tribe placement (statically addressed object).
struct cTribeRandCtx { float Next(uint32_t salt); };      // 0x00ce6a40
extern cTribeRandCtx gTribeRandCtx;                       // 0x01581208

// Planet model used by the surface-point projection.
struct cPlanetModel { Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* in); };   // 0x00b815a0
cPlanetModel* PlanetModel();                              // 0x00b3d350

struct cTribe {
    cTribeVtbl* mpVtbl;           // +0x00
    void*       mpVtbl04;         // +0x04
    char        pad08[0x2c];      // +0x08 .. +0x34
    void*       mpVtbl34;         // +0x34
    char        pad38[0xe8];      // +0x38 .. +0x120
    void*       mpVtbl120;        // +0x120
    char        sub124[0xd0];     // +0x124 .. +0x1f4
    void*       mpVtbl1f4;        // +0x1f4
    char        sub1f8[0x14];     // +0x1f8 .. +0x20c
    void*       mpVtbl20c;        // +0x20c
    char        sub210[0x20];     // +0x210 .. +0x230
    void*       mpVtbl230;        // +0x230
    char        pad234[0x2c];     // +0x234 .. +0x260
    void*       mpRef260;         // +0x260
    char        pad264[0xc];      // +0x264 .. +0x270
    char        sub270[0x20];     // +0x270
    void*       mpRef290;         // +0x290
    void*       mpArray294;       // +0x294
    char        pad298[0x10];     // +0x298 .. +0x2a8
    void*       mpArray2a8;       // +0x2a8
    char        pad2ac[0x24];     // +0x2ac .. +0x2d0
    void*       mpRef2d0;         // +0x2d0
    void*       mpRef2d4;         // +0x2d4
    char        pad2d8[0x38];     // +0x2d8 .. +0x310
    void*       mp310;            // +0x310
    void*       mpArray314;       // +0x314
    char        pad318[0x10];     // +0x318 .. +0x328
    uint32_t    m328;             // +0x328
    uint32_t    m32c;             // +0x32c
    float       m330;             // +0x330
    uint8_t     m334;             // +0x334
    uint8_t     pad335[3];
    uint32_t    m338;             // +0x338
    uint8_t     m33c;             // +0x33c
    uint8_t     pad33d[3];        // +0x33d .. +0x340
    char        sub340[0x14];     // +0x340
    char        sub354[0x14];     // +0x354
    void*       mpRef368;         // +0x368
    char        sub36c[0x14];     // +0x36c
    char        sub380[0x14];     // +0x380
    TribeMapB   map394;           // +0x394
    char        pad3a4[0x10];     // +0x3a4 .. +0x3b4
    char        sub3b4[0x64];     // +0x3b4
    void*       mpArray418;       // +0x418
    char        pad41c[0xc8];     // +0x41c .. +0x4e4
    TribeMap    map4e4;           // +0x4e4
    float       m4f4;             // +0x4f4
    float       m4f8;             // +0x4f8
    uint32_t    m4fc;             // +0x4fc
    char        pad500[0x10];     // +0x500 .. +0x510
    char        sub510[0x20];     // +0x510
    char        sub530[0x28];     // +0x530
    char        sub558[0x18c8 - 0x558];   // +0x558 .. +0x18c8
    void*       mpOwned18c8;      // +0x18c8
    uint32_t    m18cc;            // +0x18cc
    char        pad18d0[0x34];    // +0x18d0 .. +0x1904
    void*       mpArray1904;      // +0x1904
    char        pad1908[0xbc];    // +0x1908 .. +0x19c4
    void*       mpRef19c4;        // +0x19c4
    void*       mpRef19c8;        // +0x19c8
    void*       mpRef19cc;        // +0x19cc
    void*       mpRef19d0;        // +0x19d0

    // Frame query for a region: returns the region origin in a and its extent in b.
    void Frame(uint32_t key, Vec3* a, Vec3* b);           // 0x00c905c0

    Vec3*    RandomRegionPoint(Vec3* out, uint32_t key, int);     // 0x00c979e0
    Vec3*    RandomRegionPointAt(int unused, Vec3* out, uint32_t key);   // 0x00c97b10
    int      FindRegionIndex(uint32_t key, int unused);           // 0x00c97c40
    int      InsertRegionValue(uint32_t key, void* obj);          // 0x00c97ca0
    void     UpdateRegionSlot(uint32_t key, uint32_t* extra);     // 0x00c97d40
    void     Destroy();                                           // 0x00c97de0
    bool     Sub120Query();                                       // 0x00c98080
    uint32_t AllocateRegion(uint32_t key);                        // 0x00c98230

    uint32_t Sub120Count();                                       // 0x00c8eae0
    uint32_t Sub120Index(uint32_t key);                           // 0x00c8e5a0
    void     Sub120Set(uint32_t value, int flag);                 // 0x00c95d70
};


static inline void LoadU32(cPropertyList* pl, uint32_t id, uint32_t* dst)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 10)
        *dst = *(uint32_t*)p->GetValuePtr();
}

static inline float PropFloat(Property* p) { return *(float*)p->GetValuePtr(); }

static inline void LoadFloat(cPropertyList* pl, uint32_t id, float* dst)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 13)
        *dst = PropFloat(p);
}

// @ 0x00c97220
bool LoadTribeArchetypeData()
{
    if (gTribeArchetypesLoaded)
        return true;

    bool loadedAny = false;
    cPropertyManager* pm = PropertyManager();
    uint32_t groupIDs[3];
    groupIDs[0] = 0xab83a874;
    groupIDs[1] = 0x27adfe33;
    groupIDs[2] = 0xf29db649;

    int cnt1, cnt2;
    uint32_t* data1;
    uint32_t* data2;
    for (uint32_t g = 0; g < 3; g++) {
        uint32_t groupID = groupIDs[g];
        for (int i = 0; i < 32; i++)
            gTribeArchetypes[g * 32 + i] = TribeArchetype();

        PLRef pl;
        pl.p = 0;
        struct IdVec : SpVec { uint32_t extra; } ids;
        ids.mpBegin = 0;
        ids.mpEnd = 0;
        ids.mpCapacity = 0;
        PropertyManager()->GetPropertyListIDs(groupID, &ids);

        uint32_t* it = ids.mpBegin;
        uint32_t* itEnd = ids.mpEnd;
        if (it == itEnd) {
            ids.free();
            if (pl.p) pl.p->Release();
        } else {
            for (; it != itEnd; it++) {
                uint32_t instanceID = *it;
                if (pl.p) {
                    cPropertyList* old = pl.p;
                    pl.p = 0;
                    old->Release();
                }
                Property* p;
                if (pm->GetPropertyList(instanceID, groupID, &pl.p) && pl.p &&
                    pl.p->GetProperty(0x64aaf64e, p) && p->mnType == 10) {
                    uint32_t idx = *(uint32_t*)p->GetValuePtr();
                    if (idx - 1 <= 0x1e) {
                        TribeArchetype* a = &gTribeArchetypes[(g << 5) + idx];
                        loadedAny = true;
                        {
                            cPropertyList* cur = pl.p;
                            if (cur != a->mpRef) {
                                cPropertyList* old = a->mpRef;
                                if (cur) cur->AddRef();
                                a->mpRef = cur;
                                if (old) old->Release();
                            }
                        }
                        LoadU32(pl.p, 0x2857b21e, &a->f00);
                        LoadU32(pl.p, 0x80fe0f1b, &a->f04);
                        LoadU32(pl.p, 0xb0eb1e38, &a->f08);
                        LoadU32(pl.p, 0x982c7059, &a->f8c);
                        LoadFloat(pl.p, 0xe0be991f, &a->f90);
                        LoadFloat(pl.p, 0x1570506e, &a->f94);
                        GetPropertyAsVector2(pl.p, 0xd164f429, &a->v98);
                        {
                            cnt1 = 0;
                            data1 = 0;
                            if (GetPropertyAsUint32Array(pl.p, 0xa9a2d5e0, &cnt1, &data1)) {
                                a->textures.clear();
                                a->textures.reserve(cnt1);
                                for (int k = 0; k < cnt1; k++)
                                    a->textures.push_back(data1[k]);
                            }
                        }
                        LoadU32(pl.p, 0x91fe517b, &a->f50);
                        a->listCount = 0;
                        {
                            cnt2 = 0;
                            data2 = 0;
                            if (GetPropertyAsUint32Array(pl.p, 0x7862aee7, &cnt2, &data2)) {
                                for (int k = 0; k < cnt2; k++) {
                                    uint32_t v = data2[k];
                                    if (v - 1 <= 9)
                                        a->list[a->listCount++] = v;
                                }
                            }
                        }
                        LoadFloat(pl.p, 0x80a52ac0, &a->f58);
                        LoadFloat(pl.p, 0xd5291551, &a->f5c);
                        LoadFloat(pl.p, 0x58a47b38, &a->f60);
                        LoadFloat(pl.p, 0x27df57be, &a->f64);
                        LoadFloat(pl.p, 0xac245f82, &a->f68);
                        LoadFloat(pl.p, 0x2df9a743, &a->f6c);
                        LoadFloat(pl.p, 0xf74c0eb9, &a->f70);
                        LoadFloat(pl.p, 0xa3102906, &a->f74);
                        LoadFloat(pl.p, 0x2b793112, &a->f78);
                    }
                }
            }
            ids.free();
            if (pl.p) pl.p->Release();
        }
    }

    if (loadedAny)
        gTribeArchetypesLoaded = true;
    return loadedAny;
}

// @ 0x00c979e0
Vec3* cTribe::RandomRegionPoint(Vec3* out, uint32_t key, int)
{
    RegionSlot* slot = this->map4e4.Find(&key);

    Vec3 a, b;
    Frame(key, &a, &b);

    if (slot->mpBegin == slot->mpEnd) {
        out->x = a.x;
        out->y = a.y;
        out->z = a.z;
        return out;
    }

    int d0 = (int)(slot->m24 - (uint32_t)slot->mpBuckets) >> 2;
    int d1 = (int)((uint32_t)slot->mpEnd - (uint32_t)slot->mpValueBase) >> 2;
    int d2 = (int)((uint32_t)slot->mpBucketEnd - (uint32_t)slot->mpBegin) >> 2;
    int n = ((d0 << 6) + d1 + d2) - 0x40;

    float r = gTribeRandCtx.Next(this->m18cc);
    float s = (float)n * (r * kRegionScale + kRegionBias);

    Vec3 t;
    t.x = b.x * s + a.x;
    t.y = b.y * s + a.y;
    t.z = b.z * s + a.z;
    PlanetModel()->DirectionToSurfacePosition(out, &t);
    return out;
}

// @ 0x00c97b10
Vec3* cTribe::RandomRegionPointAt(int, Vec3* out, uint32_t key)
{
    Vec3 a, b;
    Frame(key, &a, &b);

    RegionSlot* slot = this->map4e4.Find(&key);

    uint32_t* it = slot->mpBegin;
    uint32_t* end = slot->mpEnd;
    uint32_t* bucketEnd = slot->mpBucketEnd;
    uint32_t** buckets = slot->mpBuckets;
    int idx = 0;
    if (it != end) {
        do {
            if (*it == key)
                break;
            ++it;
            if (it == bucketEnd) {
                it = buckets[1];
                ++buckets;
                bucketEnd = it + 0x40;
            }
            ++idx;
        } while (it != end);
    }

    if (idx == 0) {
        out->x = a.x;
        out->y = a.y;
        out->z = a.z;
        return out;
    }

    float r = gTribeRandCtx.Next(this->m18cc);
    float s = (2.0f * r + kRegionBias) * (float)idx;

    Vec3 t;
    t.x = b.x * s + a.x;
    t.y = b.y * s + a.y;
    t.z = b.z * s + a.z;
    PlanetModel()->DirectionToSurfacePosition(out, &t);
    return out;
}

// @ 0x00c97c40
int cTribe::FindRegionIndex(uint32_t key, int)
{
    uint32_t k = key;
    RegionSlot* slot = this->map4e4.Find(&k);

    uint32_t* it = slot->mpBegin;
    uint32_t** buckets = slot->mpBuckets;
    uint32_t* bucketEnd = slot->mpBucketEnd;
    uint32_t* end = slot->mpEnd;
    int idx = 0;
    while (it != end) {
        if (*it == k)
            return idx;
        ++it;
        if (it == bucketEnd) {
            it = *++buckets;
            bucketEnd = it + 0x40;
        }
        ++idx;
    }
    return -1;
}

// @ 0x00c97ca0
int cTribe::InsertRegionValue(uint32_t key, void* obj)
{
    uint32_t k = key;
    RegionSlot* slot = this->map4e4.Find(&k);
    cRefObj* o = (cRefObj*)obj;

    if (o)
        o->AddRef();

    uint32_t* pos = slot->mpEnd;
    uint32_t* next = pos + 1;
    if (next != slot->mpCapacity) {
        slot->mpEnd = next;
        if (pos) {
            *pos = (uint32_t)obj;
            if (o)
                o->AddRef();
        }
    } else {
        slot->Insert(&obj);
    }

    if (o)
        o->Release();

    int d0 = (int)(slot->m24 - (uint32_t)slot->mpBuckets) >> 2;
    int d1 = (int)((uint32_t)slot->mpEnd - (uint32_t)slot->mpValueBase) >> 2;
    int d2 = (int)((uint32_t)slot->mpBucketEnd - (uint32_t)slot->mpBegin) >> 2;
    return ((d0 << 6) + d1 + d2) - 0x40;
}

// @ 0x00c97d40
void cTribe::UpdateRegionSlot(uint32_t key, uint32_t* extra)
{
    uint32_t k = key;
    RegionSlot* slot = this->map4e4.Find(&k);

    SlotPair out;
    SlotPair lo = slot->Lo();
    SlotPair hi = slot->Hi();
    SlotRehash(&out, lo, hi, &extra);
    if (out.a != (uint32_t)slot->mpEnd)
        slot->Update(&out, out);
}

// @ 0x00c97de0
void cTribe::Destroy()
{
    void* owned = this->mpOwned18c8;

    this->mpVtbl    = (cTribeVtbl*)0x1473e58;
    this->mpVtbl04  = (void*)0x1473e44;
    this->mpVtbl34  = (void*)0x1469cc0;
    this->mpVtbl120 = (void*)0x1473d80;
    this->mpVtbl1f4 = (void*)0x1473d64;
    this->mpVtbl20c = (void*)0x1473d20;
    this->mpVtbl230 = (void*)0x1473d00;

    if (owned) {
        SubDtor_c2e4e0(owned);
        operator delete[](owned);
    }
    this->mpOwned18c8 = 0;

    if (this->mpRef19d0) ((cRefObj*)this->mpRef19d0)->Release();
    if (this->mpRef19cc) ((cRefObj*)this->mpRef19cc)->Release();
    if (this->mpRef19c8) ((cRefObj*)this->mpRef19c8)->Release();
    if (this->mpRef19c4) ((cRefObj*)this->mpRef19c4)->Release();

    if (this->mpArray1904 && ((int*)this->mpArray1904)[-1])
        operator delete[](this->mpArray1904);

    SubDtor_cc7c50(&this->sub558[0]);
    SubDtor_b638b0(&this->sub530[0]);
    SubDtor_b638b0(&this->sub510[0]);

    this->map4e4.Destroy(this->map4e4.m04, this->map4e4.m08);
    {
        uint32_t cap = this->map4e4.m08;
        this->map4e4.m0c = 0;
        if (cap > 1)
            operator delete[]((void*)this->map4e4.m04);
    }

    if (this->mpArray418 && ((int*)this->mpArray418)[-1])
        operator delete[](this->mpArray418);

    SubDtor_afbad0(&this->sub3b4[0]);

    this->map394.Destroy(this->map394.m04, this->map394.m08);
    {
        uint32_t cap = this->map394.m08;
        this->map394.m0c = 0;
        if (cap > 1)
            operator delete[]((void*)this->map394.m04);
    }

    SubDtor_ae6970(&this->sub380[0]);
    SubDtor_ae6970(&this->sub36c[0]);

    if (this->mpRef368) ((cRefObj*)this->mpRef368)->Release();

    SubDtor_ad92d0(&this->sub354[0]);
    SubDtor_ae6970(&this->sub340[0]);

    if (this->mpArray314 && ((int*)this->mpArray314)[-1])
        operator delete[](this->mpArray314);

    if (this->mpRef2d4) ((cRefObj*)this->mpRef2d4)->Release();
    if (this->mpRef2d0) ((cRefObj*)this->mpRef2d0)->Release();

    if (this->mpArray2a8 && ((int*)this->mpArray2a8)[-1])
        operator delete[](this->mpArray2a8);

    if (this->mpArray294 && ((int*)this->mpArray294)[-1])
        operator delete[](this->mpArray294);

    if (this->mpRef290) ((cRefObj*)this->mpRef290)->Release2();

    SubDtor_b638b0(&this->sub270[0]);

    if (this->mpRef260) ((cRefObj*)this->mpRef260)->Release();

    SubDtor_b6edf0(&this->mpVtbl230);
    SubDtor_cee7a0(&this->mpVtbl20c);
    SubDtor_ac0520(&this->mpVtbl1f4);
    SubDtor_c8a420(&this->mpVtbl120);

    BaseDtor(this);
}

// @ 0x00c98080
bool cTribe::Sub120Query()
{
    return ((cTribeSub120*)&this->mpVtbl120)->Query();
}

// @ 0x00c98230
uint32_t cTribe::AllocateRegion(uint32_t key)
{
    uint32_t count;
    if (this->m334 && !this->m33c) {
        count = this->m338;
    } else {
        SpVec* v = this->mpVtbl->GetValueList(this);
        count = (uint32_t)(((int)(uint32_t)v->mpEnd - (int)(uint32_t)v->mpBegin) >> 2);
    }

    if (count < this->Sub120Count()) {
        uint32_t idx = this->Sub120Index(key);
        this->Sub120Set(idx, 1);
        return idx;
    }
    return 0;
}

