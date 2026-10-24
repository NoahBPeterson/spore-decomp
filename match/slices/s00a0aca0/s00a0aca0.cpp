// Slice s00a0aca0: creature animation world, create a creature animation controller (0x00a0b260, 1597 bytes).
//
// AnimWorld::CreateCreatureController(key, resHolder, blocksName, userData, pos, rot, useCache)
// (thiscall, 7 stack args; name Claude-coined; Ghidra's "cCapCommand::Execute" guess is wrong)
//
//  1. Derives a 64-bit cache key (instance | group << 32 of a ResourceKey, of a resource object, or the
//     FNV hash of a blocks-file name << 16) when the cache is used.
//  2. Looks the key up in the world's static-data cache (an rbtree at world->cache+0x18). A hit gives a shared
//     creature_static_data (AddRef'd); a miss (or a null cached entry) builds a new one from the resource
//     key / resource object / blocks file, stores the key in it and caches it.
//  3. Builds a creature_instance_data (0x1930 bytes), initialises it from the static data, pos and rot and,
//     when the world has resources loaded, attaches a creature-model-instance (cmid) and creates one effect
//     per static-data effect record (id 0x782efd3).
//  4. Wraps it into an "anim creature" (0x19c bytes) that owns a queued blender (0xfd0 bytes) and registers
//     it in the world's creature list, returning it.
//
// Layouts are retail offsets from the disassembly; field names are Claude-coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <stddef.h>

namespace EA { namespace Hash {
uint32_t __cdecl FNV1_String8(const char* pString, uint32_t nInitialValue, int charCase);   // 0x00932e80
} }

void* __cdecl operator_new(size_t, const char*, int, int, int, int);   // 0x00f473a0
void  __cdecl operator_delete__(void*);                                 // 0x00f47380

struct vector_3 {
    float x, y, z;
    vector_3() {}
    vector_3(const vector_3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct vector_4 {
    float x, y, z, w;
    vector_4() {}
    vector_4(const vector_4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

struct ResourceKey { uint32_t instance, type, group; };

// Intrusive reference-counted resource (vtable: AddRef, Release).
struct IResource {
    virtual int AddRef();
    virtual int Release();
};
struct ResourceHolder {                 // arg2: points at a resource object (key at +8)
    IResource* mpObject;
};
struct ResourceObject {
    void*       vtbl;                   // +0x00
    uint32_t    refcount;               // +0x04
    ResourceKey key;                    // +0x08
};

struct AutoRefCount {                   // EA::AutoRefCount<IResource>
    IResource* mpObject;
    void** AsPPTypeParam();             // 0x00a16f40 (releases the held object, returns &mpObject)
};

struct creature_static_data;
struct creature_instance_data;
struct anim_creature;

struct StaticPtr {                      // AutoRefCount<creature_static_data> (inline Reset takes a reference)
    creature_static_data* mp;
    StaticPtr() : mp(0) {}
    void Reset(creature_static_data* const& p);
};

struct SlotRef {                        // AutoRefCount<creature_static_data> slot inside the cache
    SlotRef* assign(creature_static_data** p);              // 0x00a056f0
};
struct CacheNode { uint32_t pad[6]; creature_static_data* value; uint32_t pad2[2]; };   // value at +0x18
struct StaticDataCache {                // rbtree at world->cache + 0x18
    void     find(CacheNode** pResult, const uint64_t* key);   // 0x00a05730
    SlotRef* at(const uint64_t* key);                          // 0x00a0ab90 (operator[])
};
struct CacheHolder {
    uint32_t        pad_000[6];
    StaticDataCache cache;              // +0x18
    // +0x1c: header node, i.e. end()
};

struct effect {
    uint32_t pad_000[3];
    float    f0c, f10, f14, f18, f1c, f20, f24;   // +0x0c .. +0x24
    uint8_t  pad_028;
    uint8_t  active;                    // +0x29
    uint8_t  pad_02a[2];
    float    f2c;                       // +0x2c
    void Init(IResource* res, uint32_t a, uint32_t b);      // 0x009caa40 (ret 0xc)
};

struct effect_record {                  // 0x28 bytes, creature_static_data effect table
    uint32_t key0;                      // +0x00
    uint32_t a;                         // +0x04
    float    f08;                       // +0x08
    float    f0c, f10, f14, f18, f1c, f20, f24;   // +0x0c .. +0x24
};

struct creature_model_inst {            // "cmid" (0x3c bytes)
    bool InitFromResource(creature_instance_data* cid, void* world44, IResource* res, const ResourceKey* key, uint8_t b);   // 0x009c8050 (ret 0x14)
    bool InitFromBlocks(creature_instance_data* cid, void* world44, const ResourceKey* key, uint8_t b);                      // 0x009c8230 (ret 0x10)
    creature_model_inst* Construct();                                                                                         // 0x009c8200
    void Destruct();                                                                                                          // 0x00a0a020
};

struct creature_static_data {
    uint32_t pad_000[0x310 / 4];
    uint64_t cache_key;                 // +0x310
    uint32_t pad_318[(0x348 - 0x318) / 4];
    int      refcount;                  // +0x348
    uint32_t pad_34c[(0x398 - 0x34c) / 4];
    effect_record* effects_begin;       // +0x398
    effect_record* effects_end;         // +0x39c

    creature_static_data* Construct();  // 0x009c1f60
    int  AddRef();                      // 0x009b3450
    int  Release();                     // 0x009c26a0
};

inline void StaticPtr::Reset(creature_static_data* const& p) { if (p) p->AddRef(); mp = p; }

struct creature_instance_data {
    uint32_t pad_000;
    anim_creature* root;                // +0x004
    uint32_t pad_008[3];
    int      refcount;                  // +0x014
    uint32_t pad_018[(0x2c0 - 0x18) / 4];
    creature_model_inst* model;         // +0x2c0

    creature_instance_data* Construct();    // 0x009c56c0
    int  AddRef();                          // 0x00a17060
    void Release();                         // 0x009c4cc0
    effect* AddEffect(uint32_t id, int a, int b);   // 0x009cb300 (ret 0xc)
};

struct BakedAnimManager {
    void* PostFeedback(creature_static_data* csd, int arg);   // 0x009abd10 (ret 8)
};
extern BakedAnimManager* g_pBakedAnimManager;                // 0x0166c084

struct queued_blender {
    queued_blender* Construct();                                         // 0x00a01c10
    void Init(creature_instance_data* cid, BakedAnimManager* mgr);      // 0x00a00910 (ret 8)
};

struct anim_creature {                  // 0x19c bytes
    void*    vtbl;                      // +0x00
    uint32_t pad_004[(0x50 - 4) / 4];
    uint32_t userData;                  // +0x050
    uint32_t pad_054[(0x68 - 0x54) / 4];
    uint32_t slotMask;                  // +0x068
    int      f6c;                       // +0x06c
    int      f70;                       // +0x070
    uint32_t pad_074[(0x88 - 0x74) / 4];
    uint32_t flags;                     // +0x088
    uint32_t pad_08c[(0x17c - 0x8c) / 4];
    creature_instance_data* instance;   // +0x17c
    uint32_t pad_180;
    queued_blender* blender;            // +0x184
    uint32_t f188;                      // +0x188
    uint32_t f18c;                      // +0x18c
    void*    world;                     // +0x190
    uint32_t creatureCount;             // +0x194
    int      f198;                      // +0x198

    anim_creature* Construct(const vector_3* pos, const vector_4* rot);   // 0x00a05d60 (ret 8)
};

struct SimpleVector {                   // SP::SimpleVector<anim_creature*>
    anim_creature** mpBegin;
    anim_creature** mpEnd;
    anim_creature** mpCapacity;
    void DoInsertValue(anim_creature** pos, anim_creature* const* value);   // 0x00a80dd0 (ret 8)
};

bool   __cdecl ResolveResource(const ResourceKey* key, void** pResult);                       // 0x004bafc0
bool   __cdecl InitStaticDataFromResource(creature_static_data* csd, IResource* res);         // 0x009cbee0
bool   __cdecl InitStaticDataFromBlocksFile(creature_static_data* csd, const char* name);     // 0x009cd110
void   __cdecl InitInstance(creature_static_data* csd, creature_instance_data* cid, vector_3 pos,
                            vector_4 rot, void* p);                                           // 0x009c52a0
bool   __cdecl ResolveEffectResource(void* p4c, uint32_t key0, int a, int b, void** pResult); // 0x009fc050
void   __cdecl RegisterCreature(anim_creature* ac);                                           // 0x00a05c20

// Parallel bit extract (the compiler leaves this loop in the code with constant inputs).
static inline uint32_t ExtractBits(uint32_t v, uint32_t mask)
{
    uint32_t result = 0, bit = 1;
    while (mask) {
        uint32_t rest = mask & (mask - 1);
        uint32_t low = rest ^ mask;
        result |= (-(int)((low & v) != 0)) & bit;
        bit <<= 1;
        v &= ~low;
        mask = rest;
        if (!v) break;
    }
    return result;
}

struct AnimWorld {
    uint32_t pad_000[7];
    CacheHolder* cacheHolder;           // +0x01c
    uint32_t pad_020;
    SimpleVector creatures;             // +0x024
    uint32_t pad_030[2];
    uint8_t  data38[8];                 // +0x038 (passed to InitInstance)
    uint32_t pad_040;
    void*    world44;                   // +0x044
    uint8_t  flag48;                    // +0x048
    uint8_t  pad_049[3];
    void*    p4c;                       // +0x04c
    uint8_t  pad_050[0x3039 - 0x50];
    uint8_t  flag3039;                  // +0x3039
    uint8_t  flag303a;                  // +0x303a

    anim_creature* CreateCreatureController(const ResourceKey* key, ResourceObject** pObj, const char* name,
                                            uint32_t userData, const vector_3* pos, const vector_4* rot,
                                            bool useCache);
    anim_creature* CreateCreatureWide(const wchar_t* pName, uint32_t userData, const vector_3* pos,
                                      const vector_4* rot, void* pUnused, bool useCache);
    anim_creature* CreateCreatureFromObject(ResourceObject** pObj, uint32_t userData, const vector_3* pos,
                                            const vector_4* rot, bool useCache);
    anim_creature* CreateCreatureFromKey(const ResourceKey* key, uint32_t userData, const vector_3* pos,
                                         const vector_4* rot, bool useCache);
};

// @ 0x00a0b260
anim_creature* AnimWorld::CreateCreatureController(const ResourceKey* key, ResourceObject** pObj, const char* name,
                                                   uint32_t userData, const vector_3* pos, const vector_4* rot,
                                                   bool useCache)
{
    uint64_t cacheKey = 0;
    CacheNode* it;
    StaticPtr csdRef;                       // the reference owned by this function
    AutoRefCount res;
    bool found;
    if (useCache) {
        if (key) {
            cacheKey = (uint64_t)key->instance | ((uint64_t)key->group << 32);
        } else if (pObj) {
            const ResourceObject* obj = *pObj;
            cacheKey = (uint64_t)obj->key.instance | ((uint64_t)obj->key.group << 32);
        } else if (name) {
            cacheKey = (uint64_t)EA::Hash::FNV1_String8(name, 0x811c9dc5, 1) << 16;
        } else {
            return 0;
        }
    }

    creature_static_data* csd = 0;          // working pointer
    res.mpObject = 0;
    found = false;
    if (useCache) {
        cacheHolder->cache.find(&it, &cacheKey);
        if (it != (CacheNode*)((char*)cacheHolder + 0x1c)) {
            creature_static_data* hit = it->value;
            if (hit) {
                csdRef.Reset(hit);
                csd = hit;
            }
            found = true;
        }
    }
    if (!csd) {
        void* mem = operator_new(0x410, "Anim/World/new_csd", 0, 0, 0, 0);
        if (mem) {
            creature_static_data* fresh = ((creature_static_data*)mem)->Construct();
            if (fresh) {
                csdRef.Reset(fresh);
                csd = fresh;
            }
        }
        bool ok;
        if (key) {
            if (res.mpObject) {
                IResource* old = res.mpObject;
                res.mpObject = 0;
                old->Release();
            }
            if (ResolveResource(key, (void**)&res.mpObject))
                ok = InitStaticDataFromResource(csd, res.mpObject);
            else
                goto tryObject;
        } else {
        tryObject:
            if (pObj)
                ok = InitStaticDataFromResource(csd, (IResource*)*pObj);
            else if (name)
                ok = InitStaticDataFromBlocksFile(csd, name);
            else
                ok = false;
        }
        if (!ok) {
            if (res.mpObject) res.mpObject->Release();
            if (csdRef.mp) csdRef.mp->Release();
            return 0;
        }
        if (useCache) {
            csd->cache_key = cacheKey;
            cacheHolder->cache.at(&cacheKey)->assign(&csdRef.mp);
        } else {
            csd->cache_key = 0;
        }
    }

    creature_instance_data* cid = 0;
    void* cidMem = operator_new(0x1930, "Anim/World/new_cid", 0, 0, 0, 0);
    if (cidMem) {
        cid = ((creature_instance_data*)cidMem)->Construct();
        if (cid) cid->AddRef();
    }
    InitInstance(csd, cid, *pos, *rot, data38);

    bool failed = false;
    if (world44 && flag48) {
        bool ok;
        if (key && (res.mpObject || ResolveResource(key, res.AsPPTypeParam()))) {
            void* m = operator_new(0x3c, "Anim/World/new_cmid", 0, 0, 0, 0);
            creature_model_inst* cmid = m ? ((creature_model_inst*)m)->Construct() : 0;
            cid->model = cmid;
            ok = cmid->InitFromResource(cid, world44, res.mpObject, key, flag303a);
        } else if (pObj) {
            void* m = operator_new(0x3c, "Anim/World/new_cmid", 0, 0, 0, 0);
            creature_model_inst* cmid = m ? ((creature_model_inst*)m)->Construct() : 0;
            cid->model = cmid;
            ok = cmid->InitFromBlocks(cid, world44, (const ResourceKey*)pObj, flag303a);
        } else {
            ok = false;
        }
        if (!ok) {
            creature_model_inst* old = cid->model;
            if (old) {
                old->Destruct();
                operator_delete__(old);
            }
            cid->model = 0;
            failed = true;
        } else {
            uint32_t count = (uint32_t)(csd->effects_end - csd->effects_begin);
            for (uint32_t i = 0; i < count; ++i) {
                effect_record* rec = &csd->effects_begin[i];
                IResource* tmp = 0;
                if (ResolveEffectResource(p4c, rec->key0, 0, 0, (void**)&tmp)) {
                    effect* e = cid->AddEffect(0x782efd3, 1, 0);
                    e->Init(tmp, rec->a, i);
                    e->f0c = rec->f0c; e->f10 = rec->f10; e->f14 = rec->f14; e->f18 = rec->f18;
                    e->f1c = rec->f1c; e->f20 = rec->f20; e->f24 = rec->f24;
                    e->active = 1;
                    e->f2c = rec->f08;
                }
                if (tmp) tmp->Release();
            }
        }
    }

    if (flag3039 && !found && useCache)
        g_pBakedAnimManager->PostFeedback(csd, 1);

    anim_creature* ac = 0;
    void* acMem = operator_new(0x19c, "Anim/World/new_ac", 0, 0, 0, 0);
    if (acMem) ac = ((anim_creature*)acMem)->Construct(pos, rot);
    creature_instance_data* oldInst = ac->instance;
    if (cid != oldInst) {
        if (cid) cid->AddRef();
        ac->instance = cid;
        if (oldInst) oldInst->Release();
    }
    ac->userData = userData;
    ac->world = this;
    void* qbMem = operator_new(0xfd0, "Anim/World/new_qb", 0, 0, 0, 0);
    queued_blender* qb = qbMem ? ((queued_blender*)qbMem)->Construct() : 0;
    ac->blender = qb;
    qb->Init(cid, g_pBakedAnimManager);
    ac->f18c = 0;
    ac->f188 = 0;
    ac->creatureCount = (uint32_t)(creatures.mpEnd - creatures.mpBegin);
    ac->flags |= failed ? 2 : 0;
    const int none = -1;
    ac->f70 = none;
    ac->f6c = none;
    ac->slotMask = 1u << ExtractBits(none + 3, 0x20007);
    ac->f198++;
    if (creatures.mpEnd < creatures.mpCapacity) {
        anim_creature** e = creatures.mpEnd++;
        if (e) *e = ac;
    } else {
        creatures.DoInsertValue(creatures.mpEnd, &ac);
    }
    cid->root = ac;
    RegisterCreature(ac);
    cid->Release();
    if (res.mpObject) res.mpObject->Release();
    if (csdRef.mp) csdRef.mp->Release();
    return ac;
}

// ===========================================================================
// Rest of the slice: the animation-key/clip containers (0x00a0aca0 -
// 0x00a0b110), the three CreateCreature wrappers of SP::cSPCreatureAnimWorld
// (0x00a0b8a0 - 0x00a0b980), the resource constructor 0x00a0b9b0 and the
// async preload/world-creation members of SP::cSPCreatureAnimManager
// (0x00a0ba70, 0x00a0bbd0).
// ===========================================================================

// The sp vector allocator keeps an owner count in the word in front of every
// buffer it hands out; a non-zero count means the buffer is heap memory.
struct saAllocHeader { int32_t mOwnerCount; };

struct saText16 {                       // eastl::vector<uint16_t, sp_vector_allocator> (0x0c)
    uint16_t* mpBegin;                  // +0x00
    uint16_t* mpEnd;                    // +0x04
    uint16_t* mpCapacityEnd;            // +0x08
};

struct saTrackKey {                     // 0x1c: one keyframe of an animation track
    float     mTime;                    // +0x00
    float     mValue;                   // +0x04
    uint32_t  mFlags;                   // +0x08
    saText16  mName;                    // +0x0c (nested 16-bit text)
    uint32_t  mReserved;                // +0x18
};

struct saClip {                         // 0x18: a keyed track plus its timing
    saTrackKey* mpBegin;                // +0x00
    saTrackKey* mpEnd;                  // +0x04
    saTrackKey* mpCapacityEnd;          // +0x08
    float       mStart;                 // +0x0c
    float       mBlend;                 // +0x10
    float       mWeight;                // +0x14
};

extern uint16_t g_saEmptyText16[2];     // eastl::gEmptyString16 (0x01667bac)
extern "C" __declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);   // msvcr90 (0x013cc4a0)
extern "C" void* __cdecl memset(void*, int, size_t);            // msvcr90 (0x011e073e)

namespace EA { namespace Text {
void __cdecl StrncpyUTF8ToUTF16(char* pDest, int destSize, const wchar_t* pSrc, int srcLen);   // 0x0093cf10
} }

// ---------------------------------------------------------------------------
// 0x00a0aca0: destroy a range of clips, releasing every key's text buffer and
// then the clip's own key buffer.
// ---------------------------------------------------------------------------
// @ 0x00a0aca0
void __stdcall saDestroyClipRange(saClip* pFirst, saClip* pLast)
{
    for (; pFirst < pLast; ++pFirst)
    {
        saTrackKey* pKeyEnd = pFirst->mpEnd;
        for (saTrackKey* pKey = pFirst->mpBegin; pKey < pKeyEnd; ++pKey)
        {
            int32_t capacity = (int32_t)((char*)pKey->mName.mpCapacityEnd - (char*)pKey->mName.mpBegin) & ~1;
            if (capacity > 2 && pKey->mName.mpBegin)
                operator_delete__(pKey->mName.mpBegin);
        }
        if (pFirst->mpBegin && ((saAllocHeader*)pFirst->mpBegin)[-1].mOwnerCount != 0)
            operator_delete__(pFirst->mpBegin);
    }
}

// ---------------------------------------------------------------------------
// deep copies shared by the fill/copy helpers
// ---------------------------------------------------------------------------
static void saCopyText16(saText16* pDest, const saText16* pSrc)
{
    uint32_t count = (uint32_t)(pSrc->mpEnd - pSrc->mpBegin);
    if (count != 0 && pSrc->mpBegin)
    {
        uint16_t* pNew = (uint16_t*)operator_new((count + 1) * 2, "EASTL", 0, 0, 0, 0xd1);
        for (uint32_t i = 0; i < count; ++i)
            pNew[i] = pSrc->mpBegin[i];
        pNew[count] = 0;
        pDest->mpBegin = pNew;
        pDest->mpEnd = pNew + count;
        pDest->mpCapacityEnd = pNew + count + 1;
    }
    else
    {
        pDest->mpBegin = g_saEmptyText16;
        pDest->mpEnd = g_saEmptyText16;
        pDest->mpCapacityEnd = g_saEmptyText16 + 1;
    }
}

static void saCopyClip(saClip* pDest, const saClip* pSrc)
{
    uint32_t count = (uint32_t)(pSrc->mpEnd - pSrc->mpBegin);
    if (count != 0 && pSrc->mpBegin)
    {
        saTrackKey* pNew = (saTrackKey*)operator_new(count * sizeof(saTrackKey), "EASTL", 0, 0, 0, 0xd1);
        for (uint32_t i = 0; i < count; ++i)
        {
            pNew[i].mTime = pSrc->mpBegin[i].mTime;
            pNew[i].mValue = pSrc->mpBegin[i].mValue;
            pNew[i].mFlags = pSrc->mpBegin[i].mFlags;
            saCopyText16(&pNew[i].mName, &pSrc->mpBegin[i].mName);
            pNew[i].mReserved = pSrc->mpBegin[i].mReserved;
        }
        pDest->mpBegin = pNew;
        pDest->mpEnd = pNew + count;
        pDest->mpCapacityEnd = pNew + count;
    }
    else
    {
        pDest->mpBegin = 0;
        pDest->mpEnd = 0;
        pDest->mpCapacityEnd = 0;
    }
    pDest->mStart = pSrc->mStart;
    pDest->mBlend = pSrc->mBlend;
    pDest->mWeight = pSrc->mWeight;
}

// ---------------------------------------------------------------------------
// 0x00a0ade0: fill count clips from one source clip (each gets its own copy of
// the source's key array and text buffers).
// ---------------------------------------------------------------------------
// @ 0x00a0ade0
void __cdecl saFillClips(saClip* pDest, uint32_t count, const saClip* pValue)
{
    for (uint32_t i = 0; i < count; ++i, ++pDest)
        saCopyClip(pDest, pValue);
}

// ---------------------------------------------------------------------------
// 0x00a0af70: copy a range of clips into uninitialised storage.
// ---------------------------------------------------------------------------
// @ 0x00a0af70
saClip* __cdecl saCopyClipRange(saClip* pFirst, saClip* pLast, saClip* pDest)
{
    for (; pFirst != pLast; ++pFirst, ++pDest)
        saCopyClip(pDest, pFirst);
    return pDest;
}

// ---------------------------------------------------------------------------
// 0x00a0b110: eastl::vector<saTrackKey, sp_vector_allocator>::operator=
// ---------------------------------------------------------------------------
struct saKeyVector {
    saTrackKey* mpBegin;                // +0x00
    saTrackKey* mpEnd;                  // +0x04
    saTrackKey* mpCapacityEnd;          // +0x08

    uint32_t size() const     { return (uint32_t)(mpEnd - mpBegin); }
    uint32_t capacity() const { return (uint32_t)(mpCapacityEnd - mpBegin); }

    saTrackKey* AllocateCopy(uint32_t count, const saTrackKey* pFirst, const saTrackKey* pLast);   // 0x00a09e10
    void        DestroyRange(saTrackKey* pFirst, saTrackKey* pLast);                               // 0x00a09810
    saTrackKey* CopyRange(saTrackKey* pFirst, saTrackKey* pLast);                                  // 0x00a09680
    void        InsertRange(void** ppOther, saTrackKey* pFirst, saTrackKey* pLast,
                            saTrackKey* pPos, void* pOther);                                       // 0x00a09560
    saKeyVector& operator=(const saKeyVector& other);                                              // 0x00a0b110
};

// @ 0x00a0b110
saKeyVector& saKeyVector::operator=(const saKeyVector& other)
{
    if (this != &other)
    {
        uint32_t count = other.size();
        if (count > capacity())
        {
            saTrackKey* pNew = AllocateCopy(count, other.mpBegin, other.mpEnd);
            DestroyRange(mpBegin, mpEnd);
            if (mpBegin && ((saAllocHeader*)mpBegin)[-1].mOwnerCount != 0)
                operator_delete__(mpBegin);
            mpBegin = pNew;
            mpCapacityEnd = pNew + count;
        }
        else if (count > size())
        {
            CopyRange(other.mpBegin, other.mpBegin + size());
            InsertRange((void**)&other, other.mpBegin + size(), other.mpEnd, mpEnd, (void*)&other);
        }
        else
        {
            saTrackKey* pNewEnd = CopyRange(other.mpBegin, other.mpEnd);
            DestroyRange(pNewEnd, mpEnd);
        }
        mpEnd = mpBegin + count;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// 0x00a0b8a0 / 0x00a0b940 / 0x00a0b980: the three CreateCreature wrappers.
// The wide-name variant converts the name and appends ".blocks", the
// resource-object variant only uses the cache when the object carries a key,
// the key variant forwards the key.
// ---------------------------------------------------------------------------
// @ 0x00a0b8a0
anim_creature* AnimWorld::CreateCreatureWide(const wchar_t* pName, uint32_t userData, const vector_3* pos,
                                             const vector_4* rot, void* pUnused, bool useCache)
{
    char blocksName[0x104];
    if (pName)
    {
        char name[0x104];
        EA::Text::StrncpyUTF8ToUTF16(name, 0x104, pName, -1);
        sprintf(blocksName, "%s.blocks", name);
    }
    else
    {
        sprintf(blocksName, "%s.blocks", "");
    }
    return CreateCreatureController(0, 0, blocksName, userData, pos, rot, useCache);
}

// @ 0x00a0b940
anim_creature* AnimWorld::CreateCreatureFromObject(ResourceObject** pObj, uint32_t userData, const vector_3* pos,
                                                   const vector_4* rot, bool useCache)
{
    return CreateCreatureController(0, pObj, 0, userData, pos, rot,
                                    useCache && (*pObj)->key.instance != 0);
}

// @ 0x00a0b980
anim_creature* AnimWorld::CreateCreatureFromKey(const ResourceKey* key, uint32_t userData, const vector_3* pos,
                                                const vector_4* rot, bool useCache)
{
    return CreateCreatureController(key, 0, 0, userData, pos, rot, useCache);
}

// ---------------------------------------------------------------------------
// 0x00a0b9b0: constructor of a refcounted animation resource that also
// implements a listener and the content-validation summarizer interface
// (three vtables: one per polymorphic base).
// ---------------------------------------------------------------------------
extern float g_saDefaultAnimSpeed;      // 0x015517e4

struct saRefCountedBase {
    virtual int32_t AddRef();
    virtual int32_t Release();
};
struct saListenerBase {
    virtual void ListenerSlot00();
    virtual void ListenerSlot04();
};
struct saContentValidationSummarizer {
    virtual void SummarizerSlot00();
    virtual void SummarizerSlot04();
    int32_t mValidationState;           // +0x0c of the object
};

struct saLoadNode {                     // 0x1c: intrusive list node with a job slot
    saLoadNode* mpNext;                 // +0x00
    saLoadNode* mpPrev;                 // +0x04
    int32_t     mJobState;              // +0x08
    uint8_t     mFlags;                 // +0x0c
    int32_t     mRefCount;              // +0x10
    uint32_t    mPad14[2];              // +0x14
};

struct saAnimResource : saRefCountedBase, saListenerBase, saContentValidationSummarizer {
    float       mSpeed;                 // +0x10
    int32_t     mField14;               // +0x14
    uint32_t    mField18;               // +0x18
    saLoadNode  mLoad;                  // +0x1c
    saLoadNode  mUnload;                // +0x38
    uint32_t    mCounters[9];           // +0x50 .. +0x70
    uint32_t    mField74;               // +0x74 (untouched by the ctor)
    uint32_t    mField78;               // +0x78 (untouched by the ctor)
    uint32_t    mField7c;               // +0x7c
    uint32_t    mField80;               // +0x80
    uint32_t    mField84;               // +0x84

    saAnimResource();
};

// @ 0x00a0b9b0
saAnimResource::saAnimResource()
    : mSpeed(g_saDefaultAnimSpeed), mField14(0)
{
    mLoad.mpNext = &mLoad;
    mLoad.mpPrev = &mLoad;
    mLoad.mJobState = 0;
    mLoad.mFlags = 0;
    mLoad.mRefCount = 0;
    mUnload.mpNext = &mUnload;
    mUnload.mpPrev = &mUnload;
    mUnload.mJobState = 0;
    mUnload.mFlags = 0;
    mUnload.mRefCount = 0;
    for (int i = 0; i < 9; ++i)
        mCounters[i] = 0;
    mField7c = 0;
    mField80 = 0;
    mField84 = 0;
}

// ---------------------------------------------------------------------------
// 0x00a0ba70: finish the animation preload jobs whose stream has arrived and
// cache the animation data they produced.
// ---------------------------------------------------------------------------
struct saStream {
    virtual void Stream00();
    virtual void Stream04();
    virtual void Stream08();
};

struct saJob {
    virtual int32_t ContinueJob();      // 0x0068f970
    void            Wait();             // 0x006926b0
    int32_t         Release();          // 0x00690120
    uint32_t pad_004[7];
    void*    mpStream;                  // +0x20
};

struct saAnimStaticData {
    int32_t mRefCount;                  // +0x00
    int32_t mByteCount;                 // +0x04
};

struct saStreamWrapper {
    virtual void Wrapper00();
    virtual void Wrapper04();
    virtual void Wrapper08();
    void* mpStream;                     // +0x04

    saStreamWrapper() {}
    ~saStreamWrapper() { if (mpStream) ((saStream*)mpStream)->Stream08(); }
};

struct saRBNode {
    saRBNode*   mpParent;               // +0x00
    saRBNode*   mpLeft;                 // +0x04
    saRBNode*   mpRight;                // +0x08
    uint32_t    mColor;                 // +0x0c
    const char* mpName;                 // +0x10
    saJob*      mpJob;                  // +0x14
};

struct saRBTree {                       // eastl::rbtree anchor
    saRBNode* mpNodeParent;             // +0x00
    saRBNode* mpFirst;                  // +0x04 (leftmost node / begin())
    saRBNode* mpNodeRight;              // +0x08
    uint32_t  mColor;                   // +0x0c
};

saRBNode* __cdecl RBTreeIncrement(saRBNode* pNode);                     // 0x00921580
void      __cdecl RBTreeErase(saRBNode* pNode, saRBTree* pTree);        // 0x00921880
bool      __cdecl saHasPreloadedAnimation(const char* pName);           // 0x009a37a0
saAnimStaticData* __cdecl ReadAnimationStaticDataFromStreamWrapper(saStreamWrapper& wrapper, char* pName,
                                                                   const char* pBlocksName);   // 0x0099ed90
saAnimStaticData** __cdecl saFindAnimationSlot(const char* pName);      // 0x009a4310
void      __cdecl saAddRefAnimationData(saAnimStaticData* pData);       // 0x0099c660
void      __cdecl saReleaseAnimationData(saAnimStaticData* pData);      // 0x0099d060
extern int32_t g_saAnimBytes;                                           // 0x0166c060

struct saWorld {
    virtual int32_t AddRef();           // vt[0]
    virtual int32_t Release();          // vt[1]
};
struct saWorldVec {                     // pointer vector used by the manager
    saWorld** mpBegin;                  // +0x00
    saWorld** mpEnd;                    // +0x04
    saWorld** mpCapacityEnd;            // +0x08
    void DoInsertValue(saWorld** pPos, saWorld*& value);   // 0x00a0a360

    void push_back(saWorld*& value)
    {
        if (mpEnd < mpCapacityEnd)
        {
            saWorld** pSlot = mpEnd++;
            if (pSlot)
            {
                *pSlot = value;
                if (value)
                    value->AddRef();
            }
        }
        else
        {
            DoInsertValue(mpEnd, value);
        }
    }
};

struct saAnimManager {
    uint32_t  pad_000[14];              // +0x00
    saRBTree  mAsyncLoads;              // +0x38
    int32_t   mPendingLoads;            // +0x48
    uint32_t  pad_04c[7];               // +0x4c
    saWorldVec mWorlds;                 // +0x68

    void     UpdateAnimationPreloads();          // 0x00a0ba70
    saWorld* CreateWorld(saWorld* pSource);      // 0x00a0bbd0
};

// @ 0x00a0ba70
void saAnimManager::UpdateAnimationPreloads()
{
    saRBNode* pNode = mAsyncLoads.mpFirst;
    while (pNode != (saRBNode*)&mAsyncLoads)
    {
        if (pNode->mpJob && (uint32_t)(pNode->mpJob->ContinueJob() - 7) <= 1)
        {
            pNode->mpJob->Wait();
            saJob* pJob = pNode->mpJob;
            if (pJob->mpStream && !saHasPreloadedAnimation(pNode->mpName))
            {
                saStream* pStream = (saStream*)pJob->mpStream;
                saStreamWrapper wrapper;
                wrapper.mpStream = pStream;
                pStream->Stream04();

                char fileName[0x100];
                fileName[0] = 0;
                memset(fileName, 0, 0xff);

                saAnimStaticData* pData =
                    ReadAnimationStaticDataFromStreamWrapper(wrapper, fileName, pNode->mpName);
                saAnimStaticData** ppSlot = saFindAnimationSlot(pNode->mpName);
                saAnimStaticData* pOld = *ppSlot;
                if (pData != pOld)
                {
                    if (pData) saAddRefAnimationData(pData);
                    *ppSlot = pData;
                    if (pOld) saReleaseAnimationData(pOld);
                }
                if (pData)
                    g_saAnimBytes += pData->mByteCount;

                --mPendingLoads;
                saRBNode* pNext = RBTreeIncrement(pNode);
                RBTreeErase(pNode, &mAsyncLoads);
                if (pNode->mpJob)
                    pNode->mpJob->Release();
                operator_delete__(pNode);
                pNode = pNext;
                continue;
            }
        }
        pNode = RBTreeIncrement(pNode);
    }
}

// ---------------------------------------------------------------------------
// 0x00a0bbd0: create an animation world (0x303c bytes), AddRef it, append it to
// the manager's world vector and hand back the reference held by the vector.
// ---------------------------------------------------------------------------
struct saWorldCtor {                    // the world constructor (ecx = the new world)
    saWorld* Construct(void* pOwner, void* pSource);    // 0x00a09e70
};

// @ 0x00a0bbd0
saWorld* saAnimManager::CreateWorld(saWorld* pSource)
{
    saWorld* pWorld;
    void* pMem = operator_new(0x303c, "Anim/Manager/new_world", 0, 0, 0, 0);
    if (pMem)
        pWorld = ((saWorldCtor*)pMem)->Construct(this, pSource);
    else
        pWorld = 0;
    pSource = pWorld;
    if (pWorld)
        pWorld->AddRef();
    mWorlds.push_back(pSource);
    pWorld = pSource;
    if (pWorld)
        pWorld->Release();
    return pWorld;
}
