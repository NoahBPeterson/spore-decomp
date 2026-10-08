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
