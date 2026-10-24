// Slice s00d3a830 (SporeApp.exe, 32-bit x86, MSVC 2008 SP1).
// Creature-mode gameplay helpers plus a family of generic heap/quick-sort
// primitives over 8-byte {void*;int key} entries.
// /O2 /Ob1 /arch:SSE module.
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };

// ===========================================================================
// module globals / singletons
// ===========================================================================
// FUN_00b3d470 returns a process-wide singleton; its +0x60 field is a cached
// ref-counted object and its +0x94 field is the resource factory.
class CachedObject                    // vtable: +4 release, +8 set, +0xc stop, +0x10 active
{
public:
    virtual void Unused();
    virtual void Release();                              // +4
    virtual void Set(int on);                            // +8
    virtual void Stop(int on);                           // +0xc
    virtual bool IsActive();                             // +0x10
};

class ResourceFactory                 // vtable: +4 release, +8 get
{
public:
    virtual void Unused();
    virtual void Release();                              // +4
    virtual bool Get(uint32_t id, int flags, void** out); // +8
};

struct cModeWorldSingleton
{
    char          pad00[0x60];
    CachedObject* mpCached;          // +0x60
    char          pad64[0x94 - 0x64];
    ResourceFactory* mpFactory;      // +0x94
};
cModeWorldSingleton* GetModeWorld();              // 0x00b3d470

class cGameNounManager;
cGameNounManager* NounManager();                  // 0x00b3d300
class cAvatar;
cAvatar* GetAvatar(cGameNounManager* mgr);        // 0x00b1fdb0

class cSpatialThing
{
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual float* GetUpVector();                 // vtable +0x2c
};

class cAvatar
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void SetModePlaying(int a, int b, int c);   // vtable +0x84
    char  pad04[0xbc];
    cSpatialThing* mpThing_c0;                            // +0xc0
    char  padc4[0xb20 - 0xc4];
    void* mpExtra_b20;                                  // +0xb20
};

class cPlanetModel
{
public:
    float* GetUpVector();                         // vtable +0x2c
    void   ArcPosition(Vec3* out, const float* a, const Vec3* b, float s); // 0x00b81c80
};
cPlanetModel* PlanetModel();                      // 0x00b3d350

// ===========================================================================
// the creature-mode strategy singleton
// ===========================================================================
class cScenarioEntry                    // dispatch target with a vtable
{
public:
    virtual void Unused0();
    virtual void Unused1();
    virtual void Unused2();
    virtual void Unused3();
    virtual void Unused4();
    virtual void Unused5();
    virtual void HandleEvent(uint32_t id, void* pEvent);   // vtable +0x18
};

class cEditorResultData
{
public:
    char pad00[0x4];
};

class cCreatureModeInputStrategy
{
public:
    char pad00[0x54];
    bool mbFlag54;               // +0x54
    void SetInputPriorityStrategy(int priority);  // 0x00d33ec0
};

class cPropertyList
{
public:
    char pad00[0x54];
};

class cTexturePreload : public CachedObject
{
public:
    char pad00[0x2c - 0x4];
};

class cCreatureModeStrategy
{
public:
    char  pad00[0x49];
    bool  mbReturningFromEditor;                 // +0x49
    char  pad4a[0x60 - 0x4a];
    cEditorResultData*         mEditorResult;    // +0x60
    cCreatureModeInputStrategy* mpInputStrategy; // +0x64
    char  pad68[0xb0 - 0x68];
    int   mGameMode;                             // +0xb0
    cPropertyList* mpCreaturePropList;           // +0xb4
    cPropertyList* mpCreatureVerbPropList;       // +0xb8
    cScenarioEntry** mScenariosBegin;            // +0xbc
    cScenarioEntry** mScenariosEnd;              // +0xc0
    char  padc4[0xd8 - 0xc4];
    cTexturePreload* mpTexturePreload;           // +0xd8 (ref-counted)

    void SwitchToMode(int mode);                 // 0x00d3af00
    bool OnKeyDown(int key, int state);          // 0x00d3aff0
    Vec3* CalcVisiblePosition(Vec3* out, const Vec3* in, float maxAngle); // 0x00d3b0c0
};
extern cCreatureModeStrategy* spInstance_cCreatureModeStrategy;   // 0x0169e294

// broadcast helper: send id to every scenario, passing an event payload
struct cBroadcastPayload { void* mpAvatar; uint32_t pad; uint32_t pad2; };

// ===========================================================================
// imported helpers used by this slice
// ===========================================================================

// game input manager
class cGameInputManager
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual bool IsKeyHandled(int key, int state);   // vtable +0x44
    virtual void v18();
    virtual int  HandleKey(int key, int state);      // vtable +0x4c
};
cGameInputManager* GameInputManager();            // 0x00b3d250
bool VerbTray_HandleKeyPress(int key);            // 0x00d4a4a0

// ===========================================================================
// generic 8-byte sorted-entry container primitives
// ===========================================================================
struct SortEntry { void* mpObject; int32_t mnKey; };

void HeapAdjustUp(SortEntry* v, int top, int hole, void* value, int key);   // 0x00d38c50
void HeapAdjust(SortEntry* v, int top, int n, int hole, void* value, int key, int cmp); // 0x00d39d50
void HeapMake(SortEntry* begin, SortEntry* end, int cmp);    // 0x00d3b430
void HeapSort(SortEntry* begin, SortEntry* end, int cmp);    // 0x00d3b480
void Shuffle(SortEntry* begin, SortEntry* end, void* rng);   // 0x00d3b520
SortEntry* Partition(SortEntry* begin, SortEntry* end, void* value, int key, int cmp); // 0x00d3b5d0
void QuickSort(SortEntry* begin, SortEntry* mid, SortEntry* end, int cmp); // 0x00d3b620
void HeapSortIntro(SortEntry* begin, SortEntry* end, int depth, int cmp);  // 0x00d3b7c0

// ---- map / rbtree helpers (0x00d3b690, 0x00d3b880) ----------------------------
struct Key { uint32_t mLow; uint32_t mHigh; };

class cMapBase
{
public:
    char pad00[0x14];
    int  mnSize;                  // +0x14
    void* mpFreeList;             // +0x18
    char pad1c[0x20 - 0x1c];
    void* mpPoolBegin;            // +0x20
    void* mpPoolEnd;              // +0x24
    void* mpPoolAlloc;            // +0x28

    void InsertNode(void** out, void* parent, const Key* key, char allowDup);
};
void MapCollect(cMapBase* self, void* vec, uint32_t id);            // 0x00596fc0
void MapErase(cMapBase* self, uint32_t low, uint32_t high);         // 0x00596d70
int  PropMask(uint32_t key, uint32_t key2);                         // 0x00d3a710
void RBTreeInsert(void* node, void* parent, void* header, int side); // 0x009216a0
void* AllocSimulatorNode(void* size, const char* name, int flags, int align,
                         const char* file, int line);               // 0x00f473a0
void  operator_delete_array(void* p);                               // 0x00f47380

// ===========================================================================
// generic heap / quick-sort primitives over SortEntry arrays
// ===========================================================================
// A ref-counted object as seen through its vtable.  The vptr sits at +0 and the
// reference count at +4, so every slot call passes the object in ecx.
class RefObj
{
public:
    virtual void Slot0(int on);      // +0x00 deleting release
    virtual void Slot1();            // +0x04 destructor/free
    virtual void Slot2();            // +0x08
    virtual void Slot3(int on);      // +0x0c stop/clear
    int mnRef;                       // +0x04
};

struct RefPair { void* mpObject; char pad04[0x24]; void* mpExtra; };  // stride 0x2c

// @ 0x00d3b320
void __stdcall ScenarioDestroy(RefPair* begin, RefPair* end)
{
    for (; begin < end; ++begin)
    {
        RefObj* extra = (RefObj*)begin->mpExtra;
        if (extra != 0)
            extra->Slot3(0);
        extra = (RefObj*)begin->mpExtra;
        if (extra != 0)
            extra->Slot1();
        RefObj* obj = (RefObj*)begin->mpObject;
        if (obj != 0)
            obj->Slot1();
    }
}

// @ 0x00d3b3c0
void** CopyRefs(void** begin, void** end, void** out)
{
    while (begin != end)
    {
        void* src = *begin;
        void* old = *out;
        if (src != old)
        {
            if (src != 0)
                ++((RefObj*)src)->mnRef;
            *out = src;
            if (old != 0 && --((RefObj*)old)->mnRef == 0)
            {
                ((RefObj*)old)->mnRef = 1;
                ((RefObj*)old)->Slot0(1);
            }
        }
        ++begin;
        ++out;
    }
    return out;
}

// sift-up: place (value,key) at index hole, percolate toward the root of a
// min-heap keyed on SortEntry::mnKey.
// @ 0x00d38c50
void HeapAdjustUp(SortEntry* v, int top, int hole, void* value, int key)
{
    int parent = (hole - 1) >> 1;
    while (hole > top && v[parent].mnKey > key)
    {
        v[hole] = v[parent];
        hole = parent;
        parent = (parent - 1) >> 1;
    }
    v[hole].mnKey = key;
    v[hole].mpObject = value;
}

// sift-down then push up: restore the min-heap below index `hole`.
// @ 0x00d39d50
void HeapAdjust(SortEntry* v, int top, int n, int hole, void* value, int key, int cmp)
{
    int child = 2 * hole + 2;
    while (child < n)
    {
        if (v[child].mnKey > v[child - 1].mnKey)
            --child;
        v[hole] = v[child];
        hole = child;
        child = 2 * child + 2;
    }
    if (child == n)
    {
        v[hole] = v[child - 1];
        hole = child - 1;
    }
    HeapAdjustUp(v, top, hole, value, key);
}

// @ 0x00d3b430
void HeapMake(SortEntry* begin, SortEntry* end, int cmp)
{
    int n = (int)(end - begin);
    if (n < 2)
        return;
    {
        int hole = ((n - 2) >> 1) + 1;
        SortEntry* p = begin + hole;
        do
        {
            --p;
            --hole;
            void* value = p->mpObject;
            int   key = p->mnKey;
            HeapAdjust(begin, hole, n, hole, value, key, cmp);
        } while (hole != 0);
    }
}

// @ 0x00d3b480
void HeapSort(SortEntry* begin, SortEntry* end, int cmp)
{
    int n = (int)(end - begin);
    if (n <= 1)
        return;
    {
        SortEntry* p = end - 1;
        do
        {
            SortEntry tmp = *p;
            *p = *begin;
            HeapAdjust(begin, 0, n - 1, 0, tmp.mpObject, tmp.mnKey, cmp);
            --p;
            n = (int)(p - begin) + 1;
        } while (n > 1);
    }
}

// ===========================================================================
// 00d3aea0 -- SkipToGame: broadcast "skip to game" to every scenario
// ===========================================================================
// @ 0x00d3aea0
void SkipToGame()
{
    cBroadcastPayload ev;
    ev.mpAvatar = GetAvatar(NounManager());
    ev.pad = 0;
    ev.pad2 = 0;
    cCreatureModeStrategy* self = spInstance_cCreatureModeStrategy;
    for (cScenarioEntry** it = self->mScenariosBegin; it != self->mScenariosEnd; ++it)
        (*it)->HandleEvent(0x533535dd, &ev);
}

// ===========================================================================
// 00d3af00 -- cCreatureModeStrategy::SwitchToMode
// ===========================================================================
// @ 0x00d3af00
void cCreatureModeStrategy::SwitchToMode(int mode)
{
    if (mGameMode == mode)
        return;

    if (mode == 0)   // kMODE_PLAYING
    {
        cBroadcastPayload ev;
        ev.mpAvatar = 0;
        ev.pad = 0;
        ev.pad2 = 0;
        for (cScenarioEntry** it = mScenariosBegin; it != mScenariosEnd; ++it)
            (*it)->HandleEvent(0xd3353633, &ev);

        cAvatar* av = GetAvatar(NounManager());
        if (av != 0)
            av->SetModePlaying(0, 0, 0);       // vtable +0x84

        if (mpInputStrategy != 0)
        {
            mpInputStrategy->SetInputPriorityStrategy(0);
            mpInputStrategy->mbFlag54 = true;
        }
    }
    else if (mode == 1)   // kMODE_ENDING
    {
        mpInputStrategy->SetInputPriorityStrategy(1);
        mGameMode = mode;
        return;
    }
    else if (mode == 4)   // kMODE_DEFAULT
    {
        mpInputStrategy->mbFlag54 = true;
        mGameMode = mode;
        return;
    }
    mGameMode = mode;
}

// ===========================================================================
// 00d3b520 -- Shuffle (Fisher-Yates over SortEntry array)
// ===========================================================================
struct RandomLinearCongruential { uint32_t RandomUint32Uniform(uint32_t n); }; // 0x00a68fb0

// @ 0x00d3b520
void Shuffle(SortEntry* begin, SortEntry* end, RandomLinearCongruential* rng)
{
    for (SortEntry* it = begin + 1; it < end; ++it)
    {
        uint32_t idx = rng->RandomUint32Uniform((uint32_t)(it - begin) + 1);
        SortEntry tmp = *it;
        *it = begin[idx];
        begin[idx] = tmp;
    }
}

// ===========================================================================
// 00d3b5d0 -- Hoare partition by SortEntry::mnKey (descending scan)
// ===========================================================================
// @ 0x00d3b5d0
SortEntry* Partition(SortEntry* begin, SortEntry* end, void* value, int key, int cmp)
{
    for (;;)
    {
        while (begin->mnKey > key)
            ++begin;
        --end;
        while (key > end->mnKey)
            --end;
        if (begin >= end)
            return begin;
        SortEntry tmp = *begin;
        *begin = *end;
        *end = tmp;
        ++begin;
    }
}

// ===========================================================================
// 00d3b620 -- QuickSort: heap-make, then scan + sift, then heap-sort
// ===========================================================================
// @ 0x00d3b620
void QuickSort(SortEntry* begin, SortEntry* mid, SortEntry* end, int cmp)
{
    HeapMake(begin, mid, cmp);
    for (SortEntry* p = mid; p < end; ++p)
    {
        if (begin->mnKey < p->mnKey)
        {
            SortEntry tmp = *p;
            *p = *begin;
            HeapAdjust(begin, 0, (int)(mid - begin), 0, tmp.mpObject, tmp.mnKey, cmp);
        }
    }
    HeapSort(begin, mid, cmp);
}

// ===========================================================================
// 00d3b7c0 -- HeapSortIntro: introspective quicksort
// ===========================================================================
// @ 0x00d3b7c0
void HeapSortIntro(SortEntry* begin, SortEntry* end, int depth, int cmp)
{
    for (;;)
    {
        if (((int)((char*)end - (char*)begin) & 0xfffffff8) <= 0xe0)
            break;
        if (depth <= 0)
            break;

        int   iVar1 = begin->mnKey;
        int   n = (int)(end - begin);
        SortEntry* mid = begin + n / 2;
        int   iVar7 = mid->mnKey;
        int   iVar2 = iVar7;
        SortEntry* puVar3 = mid;
        SortEntry* puVar6 = begin;
        if (iVar7 < iVar1)
        {
            iVar2 = iVar1;
            puVar3 = begin;
            puVar6 = mid;
            iVar1 = iVar7;
        }
        if (iVar1 <= (end - 1)->mnKey)
        {
            puVar6 = puVar3;
            if ((end - 1)->mnKey < iVar2)
                puVar6 = end - 1;
        }
        SortEntry* pivot = puVar6;

        SortEntry* pos = Partition(begin, end, pivot->mpObject, pivot->mnKey, cmp);
        --depth;
        HeapSortIntro(pos, end, depth, cmp);
        end = pos;
    }
    if (depth == 0)
        QuickSort(begin, end, end, cmp);
}

// ===========================================================================
// 00d3b370 -- eastl rbtree<...>::DoNukeSubtree
// ===========================================================================
class RbtNode { public: RbtNode* mpLeft; RbtNode* mpRight; };

class RbtreeMap
{
public:
    char      pad00[0x18];
    RbtNode*  mpFreeList;      // +0x18
    char      pad1c[0x20 - 0x1c];
    RbtNode*  mpPoolBegin;     // +0x20
    RbtNode*  mpPoolEnd;       // +0x24

    void DoNukeSubtree(RbtNode* node);
};

// @ 0x00d3b370
void RbtreeMap::DoNukeSubtree(RbtNode* node)
{
    if (node == 0)
        return;
    do
    {
        DoNukeSubtree(node->mpLeft);
        RbtNode* right = node->mpRight;
        if (node >= mpPoolBegin && node < mpPoolEnd)
        {
            node->mpLeft = mpFreeList;
            mpFreeList = node;
        }
        else
        {
            operator_delete_array(node);
        }
        node = right;
    } while (node != 0);
}

// ===========================================================================
// 00d3b4e0 -- Simulator::cContentValidationSummarizer deleting destructor
// ===========================================================================
struct ContentValidationSummarizerVtbl { void* slots[1]; };
extern void* vtbl_cContentValidationSummarizer_0147abec;   // 0x0147abec
extern void* vtbl_cContentValidationSummarizer_013ec458;   // 0x013ec458

class cContentValidationSummarizer
{
public:
    void* mpVtbl;                  // +0x00
    char  pad04[0x08 - 0x04];
    int*  mpArray;                 // +0x08

    void* ScalarDeletingDestructor(unsigned int flags);
};

// @ 0x00d3b4e0
void* cContentValidationSummarizer::ScalarDeletingDestructor(unsigned int flags)
{
    mpVtbl = &vtbl_cContentValidationSummarizer_0147abec;
    if (mpArray != 0 && mpArray[-1] != 0)
        operator_delete_array(mpArray);
    mpVtbl = &vtbl_cContentValidationSummarizer_013ec458;
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// ===========================================================================
// 00d3b690 -- cEventHandler-ish: erase map entries selected by a property mask
// ===========================================================================
struct EntryVec { SortEntry* mpBegin; SortEntry* mpEnd; SortEntry* mpCapacity;
                  void Reserve(uint32_t n); };   // 0x004756f0

class cMaskMap : public cMapBase
{
public:
    void RemoveByMask(unsigned int mask);
};

// @ 0x00d3b690
void cMaskMap::RemoveByMask(unsigned int mask)
{
    EntryVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCapacity = 0;
    vec.Reserve(0x20);
    MapCollect(this, &vec, 0x887c91bb);

    uint32_t count = (uint32_t)((char*)vec.mpEnd - (char*)vec.mpBegin) >> 3;
    for (uint32_t i = 0; i < count; ++i)
    {
        SortEntry* p = vec.mpBegin + i;
        uint32_t low  = (uint32_t)p->mpObject;
        uint32_t high = (uint32_t)(((uint64_t)(uint32_t)p->mpObject) >> 32);
        if (low == 0x32ac9620 || low == 0x3a3c49a5 || low == 0xfe534766)
            continue;
        int m = PropMask(low, high);
        if (((uint32_t)m & mask) != 0)
            MapErase(this, (uint32_t)p->mpObject, high);
    }
    if (vec.mpBegin != 0 && ((int*)vec.mpBegin)[-1] != 0)
        operator_delete_array(vec.mpBegin);
}

// ===========================================================================
// 00d3b880 -- eastl map node insert
// ===========================================================================
// @ 0x00d3b880
void cMapBase::InsertNode(void** out, void* parent, const Key* key, char allowDup)
{
    int side;
    if (!allowDup && parent != (void*)((char*)this + 4) &&
        !(key->mHigh < *(uint32_t*)((char*)parent + 0x14) ||
          (key->mHigh == *(uint32_t*)((char*)parent + 0x14) &&
           key->mLow < *(uint32_t*)((char*)parent + 0x10))))
        side = 1;
    else
        side = 0;

    char* node = (char*)mpFreeList;
    if (node != 0)
        mpFreeList = *(void**)node;
    else
        node = (char*)AllocSimulatorNode(mpPoolAlloc, "Simulator", 0, 0,
                                         "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    char* slot = node + 0x10;
    if (slot != 0)
    {
        *(uint32_t*)slot = key->mLow;
        *(uint32_t*)(slot + 4) = key->mHigh;
    }
    RBTreeInsert(node, parent, (char*)this + 4, side);
    ++mnSize;
    *out = node;
}

// ===========================================================================
// 00d3a830 -- stop the avatar's mode resources / cache the fallback resource
// ===========================================================================
class cAvatarExtra { public: char pad00[0x618]; int mnFlag618; };

// @ 0x00d3a830
void StopModeResources()
{
    cModeWorldSingleton* world = GetModeWorld();
    if (world->mpCached != 0)
        world->mpCached->Stop(1);

    cAvatar* av = GetAvatar(NounManager());
    if (((cAvatarExtra*)av->mpExtra_b20)->mnFlag618 == 0)
    {
        cCreatureModeStrategy* self = spInstance_cCreatureModeStrategy;
        if (self->mpTexturePreload == 0)
        {
            ResourceFactory* factory = GetModeWorld()->mpFactory;
            cTexturePreload* old = self->mpTexturePreload;
            if (old != 0)
            {
                self->mpTexturePreload = 0;
                old->Release();
            }
            if (factory->Get(0xa096a243, 0, (void**)&self->mpTexturePreload))
                self->mpTexturePreload->Set(0);
        }
        ResourceFactory* factory = GetModeWorld()->mpFactory;
        CachedObject* cached = GetModeWorld()->mpCached;
        if (cached != 0)
        {
            GetModeWorld()->mpCached = 0;
            cached->Release();
        }
        factory->Get(0x84665696, 0, (void**)&GetModeWorld()->mpCached);
    }
    else
    {
        ResourceFactory* factory = GetModeWorld()->mpFactory;
        CachedObject* cached = GetModeWorld()->mpCached;
        if (cached != 0)
        {
            GetModeWorld()->mpCached = 0;
            cached->Release();
        }
        factory->Get(0x4cab5702, 0, (void**)&GetModeWorld()->mpCached);
    }
    GetModeWorld()->mpCached->Set(0);
}

// ===========================================================================
// 00d3a960 -- leave the creature game mode / clear cached resources
// ===========================================================================
// @ 0x00d3a960
void ResetModeResources()
{
    cCreatureModeStrategy* self = spInstance_cCreatureModeStrategy;
    if (self->mpTexturePreload != 0)
    {
        self->mpTexturePreload->Stop(1);
        cTexturePreload* old = self->mpTexturePreload;
        if (old != 0)
        {
            self->mpTexturePreload = 0;
            old->Release();
        }
    }

    cModeWorldSingleton* world = GetModeWorld();
    if (world->mpCached == 0)
        return;

    if (world->mpCached->IsActive())   // vtable +0x10
    {
        GetModeWorld()->mpCached->Stop(1);
        ResourceFactory* factory = GetModeWorld()->mpFactory;
        CachedObject* cached = GetModeWorld()->mpCached;
        if (cached != 0)
        {
            GetModeWorld()->mpCached = 0;
            cached->Release();
        }
        factory->Get(0x4cab5702, 0, (void**)&GetModeWorld()->mpCached);
        GetModeWorld()->mpCached->Set(0);
        return;
    }
    ResourceFactory* factory = GetModeWorld()->mpFactory;
    CachedObject* cached = GetModeWorld()->mpCached;
    if (cached != 0)
    {
        GetModeWorld()->mpCached = 0;
        cached->Release();
    }
    factory->Get(0x4cab5702, 0, (void**)&GetModeWorld()->mpCached);
}

// ===========================================================================
// 00d3aff0 -- cCreatureModeStrategy::OnKeyDown
// ===========================================================================
// @ 0x00d3aff0
bool cCreatureModeStrategy::OnKeyDown(int key, int state)
{
    if (GameInputManager()->IsKeyHandled(key, state))
        return true;

    bool handled;
    switch (state)
    {
    case 0:  handled = true;              break;
    case 1:  handled = (key == 0x10);     break;
    case 2:  handled = (key == 0x11);     break;
    case 4:  handled = (key == 0x12);     break;
    default: handled = false;             break;
    }
    if (handled && VerbTray_HandleKeyPress(key))
        return true;

    if (state == 0 && key == 0x1b)
    {
        cBroadcastPayload ev;
        ev.mpAvatar = 0;
        ev.pad = 0;
        ev.pad2 = 0;
        for (cScenarioEntry** it = mScenariosBegin; it != mScenariosEnd; ++it)
            (*it)->HandleEvent(0xd3353632, &ev);
    }
    return GameInputManager()->HandleKey(key, state) != 0;
}

// ===========================================================================
// 00d3b0c0 -- cCreatureModeStrategy::CalcVisiblePosition
// ===========================================================================
float GetPropertyFloat(cPropertyList* pl, uint32_t id, float def);   // 0x004e1c70
float Acos(float x);                                                 // 0x011e08c8

// @ 0x00d3b0c0
Vec3* cCreatureModeStrategy::CalcVisiblePosition(Vec3* out, const Vec3* in, float maxAngle)
{
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;

    cAvatar* av = GetAvatar(NounManager());
    if (av == 0)
        return out;

    cPlanetModel* pm = PlanetModel();
    float* up = av->mpThing_c0->GetUpVector();

    float f1 = up[0];
    float f2 = up[1];
    float f3 = up[2];

    Vec3 dir;
    dir.x = f1 * (1.0f / sqrtf((f2 * f2 + f3 * f3) + f1 * f1));

    float angle = Acos(dir.x);

    float limit;
    if (maxAngle <= 1.5258789e-05f)
        limit = GetPropertyFloat(mpCreaturePropList, 0x58cc10b4, 30.0f);
    else
        limit = maxAngle;
    (void)limit;

    float angle2 = Acos(f2 * (1.0f / sqrtf(f3 * f3 + (f2 * f2 + f1 * f1))));

    if (angle2 < angle)
    {
        float s = angle2 * sqrtf((f2 * f2 + f3 * f3) + f1 * f1);
        pm->ArcPosition(&dir, up, in, s);
        out->x = dir.x;
        out->y = dir.y;
        out->z = dir.z;
    }
    return out;
}

// ===========================================================================
// 00d3aa70 -- cSPPlanetGfx::HandleSimulationUpdate
// ===========================================================================
// Model-space camera/avatar update: normalises the avatar heading, derives the
// planet-surface direction, and (when it moved) rebuilds a render-instance
// transform from the planet orientation matrix and pushes it to the cached
// planet-gfx object.
struct Matrix33 { float m[9]; float& operator[](int i) { return m[i]; } };

extern float gPlanetFocusX;      // 0x0167ea30
extern float gPlanetFocusY;      // 0x0167ea34
extern float gPlanetFocusZ;      // 0x0167ea38
extern float gLastSurfaceX;      // 0x0169e298
extern float gLastSurfaceY;      // 0x0169e29c
extern float gLastSurfaceZ;      // 0x0169e2a0

class cPlanetGfx
{
public:
    virtual void g00();
    virtual void g01();
    virtual void g02();
    virtual void g03();
    virtual void g04();
    virtual void g05();
    virtual int  g06();
    virtual void g07();
    virtual void g08();
    virtual void g09();
    virtual void g10();
    virtual void g11();
    virtual void g12();
    virtual void g13();
    virtual void g14();
    virtual void g15();
    virtual void g16();
    virtual void g17();
    virtual void g18();
    virtual void g19();
    virtual void g20();
    virtual void g21();
    virtual void g22();
    virtual void g23();
    virtual void g24();
    virtual void g25();
    virtual void g26();
    virtual void g27();
    virtual void g28();
    virtual void g29();
    virtual void g30();
    virtual void g31();
    virtual void g32();
    virtual void g33();
    virtual void g34();
    virtual void g35();
    virtual void g36();
    virtual void g37();
    virtual void g38();
    virtual void g39();
    virtual void g40();
    virtual void g41();
    virtual void g42();
    virtual void g43();
    virtual void g44();
    virtual void g45();
    virtual void g46();
    virtual void g47();
    virtual void g48();
    virtual void g49();
    virtual void g50();
    virtual void g51();
    virtual void g52();
    virtual void g53();
    virtual void Transform(int* inst);   // vtable +0x18
};

float* AvatarForward(cAvatar* av);                        // 0x00c0e580
int  GetRenderInstance(int obj);                          // placeholder
void Matrix3FromQuaternion(float* out, void* quat);       // 0x006ba620 region
void BuildRotation(float* out, const Vec3* axis, float angle); // 0x00453b20
float LastUpdateTime();                                   // 0x00c0b440

// @ 0x00d3aa70
void HandleSimulationUpdate()
{
    cCreatureModeStrategy* self = spInstance_cCreatureModeStrategy;
    if (self->mpTexturePreload == 0)
        return;

    cAvatar* av = GetAvatar(NounManager());
    float* fwd = AvatarForward(av);

    float f15 = fwd[0];
    float f17 = fwd[1];
    float f10 = fwd[2];
    float inv = 1.0f / sqrtf((f15 * f15 + (f10 * f10 + f17 * f17)) + 1e-08f);
    float nx = inv * f15;
    float ny = f17 * inv;
    float nz = f10 * inv;

    int bounds = GetRenderInstance((int)av->mpThing_c0);
    float span = *(float*)((char*)bounds + 0x14) - *(float*)((char*)bounds + 8);
    float px = (span * nx) * 0.5f + f15;
    float py = (span * nz) * 0.5f + f17;
    float pz = (span * ny) * 0.5f + f10;

    float dx = gPlanetFocusX - px;
    float dz = gPlanetFocusZ - pz;
    float dy = gPlanetFocusY - py;
    float dInv = 1.0f / (sqrtf(dy * dy + (dz * dz + dx * dx)) + 1.5258789e-05f);
    dx *= dInv;
    dz *= dInv;
    dy *= dInv;

    if (dx == gLastSurfaceX && dz == gLastSurfaceZ && dy == gLastSurfaceY)
        return;

    float basis[9];
    Matrix33 orient;
    Matrix3FromQuaternion(basis, 0);   // avatar orientation quaternion
    orient[0] = -dy * nz - -dz * ny;
    orient[1] = ny * -dx - -dy * nx;
    orient[2] = -dz * nx - nz * -dx;

    float dot = (dx * nx + dy * ny) + dz * nz;
    float limit = GetPropertyFloat(self->mpCreaturePropList, 0xc1fe457d, 0.7f);
    if (dot < limit)
    {
        float ang = Acos(dot);
        (void)ang;
        Matrix33 extra;
        BuildRotation(extra.m, (Vec3*)&orient, -(ang - 0.0f));
        // (rotate basis by extra)
    }

    (void)basis;
    return;
}
