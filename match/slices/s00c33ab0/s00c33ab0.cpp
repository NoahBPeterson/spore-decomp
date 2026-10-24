// Slice s00c33ab0 -- the core of SP::cEmpire (star / enemy / ally registries,
// destruction, construction) plus the eastl template instantiations that were
// laid down alongside them (partial_sort and the generic vector insert/resize).
//
//  0x00c33ab0  eastl::partial_sort<AutoRefCount<cStarRecord>*;DistanceToHome>  (ret)
//  0x00c33cc0  SP::cEmpire::AddAdventure_33cc0        (ret 8)
//  0x00c33da0  EVec::Insert_33da0                     (ret 0xc)
//  0x00c34140  SP::cEmpire::Reset_34140               (ret)
//  0x00c341a0  SP::cEmpire::AddStar                   (ret 4)
//  0x00c34320  SP::cEmpire::Destroy                   (ret)
//  0x00c344f0  SP::cEmpire::CollectColonizable_344f0  (ret 8)
//  0x00c345f0  SP::cEmpire::AddEnemy_345f0            (ret 4)
//  0x00c34680  SP::cEmpire::AddAlly_34680             (ret 4)
//  0x00c34710  EVec::Resize_34710                     (ret 8)
//  0x00c34830  SP::cEmpire::cEmpire                   (ret)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (MSVC 2008 SP1).
#include "types.h"
#include <string.h>
#include <intrin.h>

typedef unsigned int uintptr_t;

// ---- raw (__cdecl / __stdcall) callees -------------------------------------
void* __cdecl operator_new_sp(unsigned size, const char* name,
                              int a, int b, void* c, int d);   // 0x00f473a0
void  __cdecl operator_delete_arr(void* p);                    // 0x00f47380
void* __cdecl FUN_0067dcc0(void);                              // 0x0067dcc0  MessageServer
void* __cdecl FUN_00b3d2a0(void);                              // 0x00b3d2a0  StarManager
void* __cdecl FUN_00b3d2c0(void);                              // 0x00b3d2c0  RelationshipManager
void* __cdecl FUN_00b3d300(void);                              // 0x00b3d300  NounManager
void* __cdecl FUN_00b3d3e0(void);                              // 0x00b3d3e0  EventLog
void* __cdecl FUN_01021300(void);                              // 0x01021300  GetPlayerEmpire
void* __cdecl FUN_01021240(void);                              // 0x01021240
void* __cdecl FUN_01021080(void);                              // 0x01021080  GetUniverseContext
void* __cdecl FUN_01021090(void);                              // 0x01021090  GetPlayerEmpireID
bool  __cdecl FUN_00c70150(void* a, void* b, void* c);         // 0x00c70150
void  __cdecl FUN_00c737a0(void* planet, uint32_t id);         // 0x00c737a0  cPlanet_LoadModuleData
void* __cdecl FUN_00c8c2a0(void* a);                           // 0x00c8c2a0
void* __cdecl FUN_006782c0(void* first, void* last, void* dst); // 0x006782c0  eastl::copy_impl::do_copy
void* __stdcall SpaceGameGet(int a, int b);                    // 0x01002bd0
void* __cdecl FUN_011e0744(void* dst, void* src, unsigned n);  // import thunk -> memcpy

// ---- member-style external callees -----------------------------------------
// The originals are __thiscall; modelling them as member functions of a stub
// class makes the compiler emit `mov ecx,<this>; call`, the exact original
// encoding.  Nothing is linked so the symbols are just (masked) relocations.
struct MC {
    int   f_00ce6950();                       // 0x00ce6950  cStarRecordRef::GetCommContext
    int   f_00ba7280();                       // 0x00ba7280
    void  f_00e25bd0(void* first, void* last);// 0x00e25bd0  vector::erase
    void* f_00bba790();                       // 0x00bba790
    void  f_00aea5d0(void* pos, void* v);     // 0x00aea5d0  DoInsertPtr
    void  f_004b0a10(void* pos, int n, void* value);  // 0x004b0a10  vector insert
    void* f_00bf2c60();                       // 0x00bf2c60  cCultureSet ctor
    void* f_00b63890();                       // 0x00b63890  cGonzagoTimer ctor
    void* f_00ba6d80(unsigned id);            // 0x00ba6d80
    void* f_00bb9b80();                       // 0x00bb9b80
    void* f_00bb9b90(void* a);                // 0x00bb9b90
    int   f_00b8dab0();                       // 0x00b8dab0
    void* f_00885c90();                       // 0x00885c90
    bool  f_00d01f50(void* a, void* b);       // 0x00d01f50
    void* f_00f67d90();                       // 0x00f67d90  cTerrainEditor::GetCurrentTerrainSphere
    void* f_00c78450(void* a);                // 0x00c78450  NoteWarEndedWithPlayer
    void* f_00dd8640(uint32_t a, uint32_t b, uint32_t c,
                     uint32_t d, uint32_t e, uint32_t f);  // 0x00dd8640 PostFeedbackEvent
    void* f_00bfc5f0();                       // 0x00bfc5f0  SetGameDataOwner2 / GetPlayerTribe
    void* f_00fe5430();                       // 0x00fe5430
    void  f_00c327a0(void* a);                // 0x00c327a0
    void  f_00c32830(void* a);                // 0x00c32830
    void* f_01022150(void* planet);           // 0x01022150  ActivatePlanet
    void  f_00b6f280();                       // 0x00b6f280  cSPIdentity ctor
    void  f_00579a90(const wchar_t* s);       // 0x00579a90  wstring::range_initialize
    void* f_005c65e0();                       // 0x005c65e0  cCivData::GetCities
    void  f_00babb70(void* pos, int n, void* value);  // 0x00babb70  vector::DoInsertValueN
};

// ---- globals used verbatim --------------------------------------------------
extern void*    g_16dda8c;   // 0x016dda8c
extern void*    g_16e0d08;   // 0x016e0d08
extern char     g_13ebb38[]; // 0x013ebb38  allocator name
extern void*    g_13eb90c;   // 0x013eb90c
extern float    g_13eb1bc;   // 0x013eb1bc  (-1.0f)

// ---- vtable slot helper -----------------------------------------------------
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
#define ADDREF(o)   ((void(__thiscall*)(void*))VF(o, 0))(o)
#define RELEASE(o)  ((void(__thiscall*)(void*))VF(o, 4))(o)

// Reference-counted temporary: AddRef()s on construction, Release()s on
// destruction, and converts to the raw pointer for the container.
struct AutoRef {
    void* mpObject;
    AutoRef(void* o) : mpObject(o) {
        if (mpObject) ((void(__thiscall*)(void*))VF(mpObject, 0))(mpObject);
    }
    ~AutoRef() {
        if (mpObject) ((void(__thiscall*)(void*))VF(mpObject, 4))(mpObject);
    }
    operator void*() const { return mpObject; }
};

// ---- shared shapes ----------------------------------------------------------
struct EVec {                       // eastl vector header (0x14 bytes in retail)
    void*    mBegin;                // +0x00
    void*    mEnd;                  // +0x04
    void*    mCapacity;             // +0x08
    uintptr_t mPad0c;               // +0x0c
    uintptr_t mPad10;               // +0x10

    void Insert_33da0(void* pos, unsigned n, void* value);  // 0x00c33da0
    void Resize_34710(uint32_t n, void* value);             // 0x00c34710
    uint32_t Size() const { return (uint32_t)(((char*)mEnd - (char*)mBegin) >> 2); }
};

struct Key { uint32_t instanceID, typeID, groupID; };   // 12-byte resource key

struct cSPIdentity {
    void*    mpVtbl;                // +0x00
    uint32_t mIDColorID;            // +0x04
    uint8_t  mRest[0x28];           // +0x08
    void Construct();               // 0x00b6f280
};

struct ListAnchor {
    void* mpNext;                   // +0x00
    void* mpPrev;                   // +0x04
};

// intrusive list node used by cEmpire::mAdventureList
struct ListNode {
    ListNode* mpNext;               // +0x00
    ListNode* mpPrev;               // +0x04
    uint32_t  mValue;               // +0x08
};

// the transient message object posted by cEmpire::Destroy
struct RefMsg {
    void*    mpVtbl;                // +0x00
    uint32_t mRefCount;             // +0x04
    void*    mEmpire;               // +0x08
    uint8_t  pad0c[0x24];           // +0x0c
    uint32_t mId;                   // +0x30
    uint8_t  pad34[0x4];            // +0x34
    uint32_t mField38;              // +0x38
};

namespace SP {

struct cEmpire {
    void*    mpVtbl;                    // +0x00
    void*    mpVtbl2;                   // +0x04
    uint32_t mnRefCount;                // +0x08
    cSPIdentity mIdentity;              // +0x0c
    uint8_t     mEmpireName[0x14];      // +0x3c  eastl::wstring
    uint32_t mFlags;                    // +0x50
    uint32_t mTrait;                    // +0x54
    uint32_t mArchetype;                // +0x58
    EVec     mEnemies;                  // +0x5c
    EVec     mAllies;                   // +0x70
    uint32_t mPoliticalID;              // +0x84
    EVec     mStars;                    // +0x88
    EVec     mNextStarTowardsHome;      // +0x9c
    uint32_t mHomeStar;                 // +0xb0
    uint32_t mHomePlanet;               // +0xb4
    Key      mUFOKey;                   // +0xb8
    Key      mCaptainKey;               // +0xc4
    uint32_t mEmpireMoney;              // +0xd0
    uint8_t  mTravelDistance;           // +0xd4
    uint8_t  pad_d5[0x3];               // +0xd5
    uint32_t mFieldD8;                  // +0xd8
    float    mFieldDC;                  // +0xdc
    float    mFieldE0;                  // +0xe0
    float    mFieldE4;                  // +0xe4
    float    mFieldE8;                  // +0xe8
    float    mFieldEC;                  // +0xec
    EVec     mFieldF0;                  // +0xf0  vector<float>, kept at 12 x -1.0f
    void*    mpCityMusic;               // +0x104
    uint8_t  mCultureSet[0x20];         // +0x108
    uint8_t  mDemandForTribute[0x20];   // +0x128
    ListAnchor mAdventureList;          // +0x148

    cEmpire();                                  // 0x00c34830
    int   AddAdventure_33cc0(void* key, int arg2);        // 0x00c33cc0
    void  Reset_34140();                                   // 0x00c34140
    void  AddStar(void* star);                             // 0x00c341a0
    void  Destroy();                                       // 0x00c34320
    bool  CollectColonizable_344f0(EVec* out, void* arg2); // 0x00c344f0
    void  AddEnemy_345f0(void* p);                         // 0x00c345f0
    void  AddAlly_34680(void* p);                          // 0x00c34680
    void* f_00bba790();                                    // 0x00bba790 (member form)
    void* f_00b8dab0();                                    // 0x00b8dab0 (member form)
    void* f_00bb9b90(void* a);                             // 0x00bb9b90 (member form)
};

} // namespace SP

// ===========================================================================
// 0x00c33ab0 -- eastl::partial_sort<AutoRefCount<cStarRecord>*, DistanceToHome>
// ===========================================================================
struct DistanceToHome { float x, y, z; };

void __cdecl make_heap_stars(void** first, void** middle, DistanceToHome home);   // 0x00c33330
void __cdecl sort_heap_stars(void** first, void** middle, DistanceToHome home);   // 0x00c333a0
void __cdecl adjust_heap_stars(void** first, int a, int b, int c,
                               void* value, DistanceToHome home);                 // 0x00c32a60

// @ 0x00c33ab0
void eastl_partial_sort_stars(void** first, void** middle, void** last, DistanceToHome home)
{
    make_heap_stars(first, middle, home);
    for (void** it = middle; it < last; ++it) {
        void* pfirst = *first;
        float* a = (float*)((MC*)*it)->f_005c65e0();
        float ax = a[0] - home.x, ay = a[1] - home.y, az = a[2] - home.z;
        float* b = (float*)((MC*)pfirst)->f_005c65e0();
        float bx = b[0] - home.x, by = b[1] - home.y, bz = b[2] - home.z;
        float da = ax * ax + ay * ay + az * az;
        float db = bx * bx + by * by + bz * bz;
        if (da < db) {
            void* tmp = *it;
            if (tmp) ADDREF(tmp);
            void* f = *first;
            void* i = *it;
            if (f != i) {
                if (f) ADDREF(f);
                *it = f;
                if (i) RELEASE(i);
            }
            int n = (int)(((char*)middle - (char*)first) >> 2);
            adjust_heap_stars(first, 0, n, 0, tmp, home);
            if (tmp) RELEASE(tmp);
        }
    }
    sort_heap_stars(first, middle, home);
}

// ===========================================================================
// 0x00c33cc0 -- cEmpire::AddAdventure_33cc0
// ===========================================================================
// @ 0x00c33cc0
int SP::cEmpire::AddAdventure_33cc0(void* key, int)
{
    int v = ((MC*)key)->f_00ce6950();
    ListNode* anchor = (ListNode*)&mAdventureList;
    ListNode* node = anchor->mpNext;
    if (node != anchor) {
        do {
            if (node->mValue == (uint32_t)v) break;
            node = node->mpNext;
        } while (node != anchor);
        if (node != anchor) {
            ListNode* del = node->mpNext->mpPrev;
            del->mpPrev->mpNext = del->mpNext;
            del->mpNext->mpPrev = del->mpPrev;
            operator_delete_arr(del);
        }
    }
    ListNode* p = (ListNode*)operator_new_sp(0xc, "Simulator", 0, 0, g_13ebb38, 0xd1);
    if ((char*)p + 8 != 0) *(uint32_t*)((char*)p + 8) = (uint32_t)v;
    p->mpNext = anchor;
    p->mpPrev = anchor->mpPrev;
    anchor->mpPrev->mpNext = p;
    anchor->mpPrev = p;
    int count = 0;
    for (ListNode* q = anchor->mpNext; q != anchor; q = q->mpNext) ++count;
    void* sm = FUN_00b3d2a0();
    int limit = ((MC*)sm)->f_00ba7280();
    if (count > limit) {
        ListNode* first = anchor->mpNext;
        int out = (int)first->mValue;
        first->mpPrev->mpNext = first->mpNext;
        first->mpNext->mpPrev = first->mpPrev;
        operator_delete_arr(first);
        return out;
    }
    return 0;
}

// ===========================================================================
// 0x00c33da0 -- EVec::Insert_33da0  (eastl::vector<T>::insert(pos, n, value))
// ===========================================================================
// @ 0x00c33da0
void EVec::Insert_33da0(void* pos_, unsigned n, void* value_)
{
    char* pos = (char*)pos_;
    char* end = (char*)mEnd;
    unsigned capLeft = (unsigned)(((char*)mCapacity - end) >> 2);
    if (n > capLeft) {
        char* begin = (char*)mBegin;
        unsigned size = (unsigned)((end - begin) >> 2);
        unsigned newCap = size * 2;
        if (size == 0) newCap = 1;
        if (newCap <= size + n) newCap = size + n;
        char* p = (char*)FUN_011e0744(0, begin, (unsigned)(pos - begin));
        unsigned before = (unsigned)((pos - begin) >> 2);
        char* dst = p + before * 4;
        uint32_t v = *(uint32_t*)value_;
        for (unsigned i = 0; i < n; ++i) ((uint32_t*)dst)[i] = v;
        char* p2 = (char*)FUN_011e0744(dst + n * 4, pos, (unsigned)((char*)mEnd - pos));
        uint32_t after = (uint32_t)((end - pos) >> 2);
        mBegin = 0;
        mEnd = p2 + after * 4;
        mCapacity = (void*)(newCap * 4);
        return;
    }
    if (n == 0) return;
    uint32_t v = *(uint32_t*)value_;
    unsigned after = (unsigned)((end - pos) >> 2);
    if (n < after) {
        char* src = end - n * 4;
        memcpy(end, src, n * 4);
        mEnd = (char*)mEnd + n * 4;
        unsigned bytes = (unsigned)((src - pos) >> 2) * 4;
        char* dst = end - bytes;
        memmove(dst, pos, (unsigned)(src - pos));
        for (char* q = pos; q != pos + n * 4; q += 4) *(uint32_t*)q = v;
        return;
    }
    unsigned extra = n - after;
    if (extra != 0) {
        uint32_t* q = (uint32_t*)end;
        for (unsigned i = 0; i < extra; ++i) q[i] = v;
    }
    mEnd = (char*)mEnd + extra * 4;
    memcpy(mEnd, pos, (unsigned)(end - pos));
    mEnd = (char*)mEnd + after * 4;
    for (char* q = pos; q != end; q += 4) *(uint32_t*)q = v;
}

// ===========================================================================
// 0x00c34140 -- cEmpire::Reset_34140
// ===========================================================================
// @ 0x00c34140
void SP::cEmpire::Reset_34140()
{
    ((MC*)&mStars)->f_00e25bd0(mStars.mBegin, mStars.mEnd);
    ((MC*)&mNextStarTowardsHome)->f_00e25bd0(mNextStarTowardsHome.mBegin, mNextStarTowardsHome.mEnd);
    void* p = mpCityMusic;
    if (p != 0) {
        mpCityMusic = 0;
        RELEASE(p);
    }
}

// ===========================================================================
// 0x00c341a0 -- cEmpire::AddStar
// ===========================================================================
// @ 0x00c341a0
void SP::cEmpire::AddStar(void* star)
{
    if (star == 0) return;
    void** first = (void**)mStars.mBegin;
    void** last = (void**)mStars.mEnd;
    for (void** it = first; it != last; ++it) {
        if (*it == star) return;
    }

    void* tmp = star;
    if (tmp) ADDREF(tmp);
    if ((char*)mStars.mEnd < (char*)mStars.mCapacity) {
        void** slot = (void**)mStars.mEnd;
        mStars.mEnd = slot + 1;
        if (slot != 0) {
            *slot = tmp;
            if (tmp) ADDREF(tmp);
        }
    } else {
        ((MC*)&mStars)->f_00aea5d0(mStars.mEnd, &tmp);
    }
    if (tmp) RELEASE(tmp);

    mFlags |= 0x10;
    if (mHomeStar != 0xffffffffu) {
        void* p = ((MC*)FUN_00b3d2a0())->f_00ba6d80(mHomeStar);
        if (p != 0) {
            ((MC*)star)->f_00bb9b90(((MC*)p)->f_00bb9b80());
            void* ms = FUN_01021240();
            if (ms == star && FUN_01021080() == 0) {
                void* srv = FUN_0067dcc0();
                ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))VF(srv, 0x18))
                    (srv, 0x490d429, 0, 0, 0);
            }
        }
    }

    EVec* planets = (EVec*)((MC*)this)->f_00bba790();
    int np = (int)(((char*)planets->mEnd - (char*)planets->mBegin) >> 2);
    for (int i = 0; i < np; ++i) {
        void* planet = ((void**)planets->mBegin)[i];
        if (((MC*)planet)->f_00b8dab0() == 5) {
            FUN_00c737a0(planet, mPoliticalID);
            if (mPoliticalID == (uint32_t)(uintptr_t)FUN_01021090()) {
                ((MC*)g_16dda8c)->f_01022150(planet);
            }
        }
    }

    mFieldD8 = 0xffffffff;
    void* srv = FUN_0067dcc0();
    ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))VF(srv, 0x14))(srv, 0x55bd8f7, 0, 0);
}

// ===========================================================================
// 0x00c34320 -- cEmpire::Destroy
// ===========================================================================
// @ 0x00c34320
void SP::cEmpire::Destroy()
{
    if (((MC*)FUN_00b3d2a0())->f_00885c90() == (void*)mPoliticalID) {
        void* a = SpaceGameGet(0xf, 1);
        void* b = ((MC*)a)->f_00bfc5f0();
        ((MC*)b)->f_00fe5430();
    }

    RefMsg* p = (RefMsg*)operator_new_sp(0x40, "App", 0, 0, 0, 0);
    if (p != 0) {
        p->mId = 0;
        p->mpVtbl = (void*)0x13eb90c;
        _InterlockedExchange((volatile long*)&p->mRefCount, 0);
        p->mpVtbl = (void*)0x13eb844;
        p->mField38 = 0;
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    }
    p->mId = 0x4b33711;
    p->mEmpire = this;
    {
        void* srv = FUN_0067dcc0();
        ((void(__thiscall*)(void*, uint32_t, void*, uint32_t, uint32_t))VF(srv, 0x18))
            (srv, p->mId, p, 0, 0);
    }

    int ne = (int)(((char*)mEnemies.mEnd - (char*)mEnemies.mBegin) >> 2);
    for (int i = 0; i < ne; ++i) {
        void* e = ((void**)mEnemies.mBegin)[i];
        ((MC*)e)->f_00c327a0(this);
    }
    int na = (int)(((char*)mAllies.mEnd - (char*)mAllies.mBegin) >> 2);
    for (int i = 0; i < na; ++i) {
        void* a = ((void**)mAllies.mBegin)[i];
        ((MC*)a)->f_00c32830(this);
    }

    void* player = FUN_01021300();
    if (this != player) {
        void* rm = FUN_00b3d2c0();
        if (((MC*)rm)->f_00d01f50(this, player)) {
            void* nm = FUN_00b3d300();
            void* te = ((MC*)nm)->f_00f67d90();
            ((MC*)te)->f_00c78450(this);
        }
    }

    if (g_16e0d08 != 0) *(void**)((char*)g_16e0d08 + 0x1c) = this;

    {
        void* log = FUN_00b3d3e0();
        ((MC*)log)->f_00dd8640(0x88426556, 0x131a9f54, 0, 0, 1, 0);
    }

    int ns = (int)(((char*)mStars.mEnd - (char*)mStars.mBegin) >> 2);
    for (int i = 0; i < ns; ++i) {
        FUN_00c8c2a0(((void**)mStars.mBegin)[i]);
    }
    {
        char* beg = (char*)mStars.mBegin;
        void** it = (void**)FUN_006782c0(mStars.mEnd, mStars.mEnd, beg);
        void** e = (void**)mStars.mEnd;
        for (; it < e; ++it) {
            if (*it) RELEASE(*it);
        }
        mStars.mEnd = beg;
    }

    ((void(__thiscall*)(void*))VF(p, 8))(p);
}

// ===========================================================================
// 0x00c344f0 -- cEmpire::CollectColonizable_344f0
// ===========================================================================
// @ 0x00c344f0
bool SP::cEmpire::CollectColonizable_344f0(EVec* out, void* arg2)
{
    int ns = (int)(((char*)mStars.mEnd - (char*)mStars.mBegin) >> 2);
    for (int i = 0; i < ns; ++i) {
        void* star = ((void**)mStars.mBegin)[i];
        if (star == 0) continue;
        EVec* list = (EVec*)((MC*)star)->f_00bba790();
        int nm = (int)(((char*)list->mEnd - (char*)list->mBegin) >> 2);
        for (int j = 0; j < nm; ++j) {
            void* item = ((void**)list->mBegin)[j];
            if (item == 0) continue;
            if (FUN_00c70150(item, this, arg2)) {
                if (item) ADDREF(item);
                if ((char*)out->mEnd < (char*)out->mCapacity) {
                    void** slot = (void**)out->mEnd;
                    out->mEnd = slot + 1;
                    if (slot != 0) {
                        *slot = item;
                        if (item) ADDREF(item);
                    }
                } else {
                    ((MC*)out)->f_00aea5d0(out->mEnd, &item);
                }
                if (item) RELEASE(item);
            }
        }
    }
    return out->mBegin != out->mEnd;
}

// ===========================================================================
// 0x00c345f0 -- cEmpire::AddEnemy_345f0
// ===========================================================================
// @ 0x00c345f0
void SP::cEmpire::AddEnemy_345f0(void* p)
{
    EVec* v = &mEnemies;
    int n = (int)(((char*)v->mEnd - (char*)v->mBegin) >> 2);
    void** it = (void**)v->mBegin;
    for (int i = 0; i < n; ++i) {
        if (*it == p) return;
        ++it;
    }
    AutoRef ref(p);
    if ((char*)v->mEnd < (char*)v->mCapacity) {
        void** slot = (void**)v->mEnd;
        v->mEnd = slot + 1;
        if (slot != 0) {
            *slot = ref.mpObject;
            if (ref.mpObject) ADDREF(ref.mpObject);
        }
    } else {
        ((MC*)v)->f_00aea5d0(v->mEnd, &ref);
    }
}

// ===========================================================================
// 0x00c34680 -- cEmpire::AddAlly_34680
// ===========================================================================
// @ 0x00c34680
void SP::cEmpire::AddAlly_34680(void* p)
{
    EVec* v = &mAllies;
    int n = (int)(((char*)v->mEnd - (char*)v->mBegin) >> 2);
    void** it = (void**)v->mBegin;
    for (int i = 0; i < n; ++i) {
        if (*it == p) return;
        ++it;
    }
    AutoRef ref(p);
    if ((char*)v->mEnd < (char*)v->mCapacity) {
        void** slot = (void**)v->mEnd;
        v->mEnd = slot + 1;
        if (slot != 0) {
            *slot = ref.mpObject;
            if (ref.mpObject) ADDREF(ref.mpObject);
        }
    } else {
        ((MC*)v)->f_00aea5d0(v->mEnd, &ref);
    }
}

// ===========================================================================
// 0x00c34710 -- EVec::Resize_34710
// ===========================================================================
// @ 0x00c34710
void EVec::Resize_34710(uint32_t n, void* value)
{
    if (n > Size()) {
        ((MC*)this)->f_00babb70(mEnd, (int)(n - Size()), value);
        return;
    }
    ((MC*)this)->f_00e25bd0((char*)mBegin + n * 4, mEnd);
}

// ===========================================================================
// 0x00c34830 -- cEmpire::cEmpire
// ===========================================================================
// @ 0x00c34830
SP::cEmpire::cEmpire()
{
    mpVtbl = (void*)0x1444434;
    mpVtbl2 = (void*)0x13ef094;
    mnRefCount = 0;
    mIdentity.Construct();
    mpVtbl = (void*)0x146b768;
    mpVtbl2 = (void*)0x146b764;
    mIdentity.mpVtbl = (void*)0x146b748;
    {
        MC* s = (MC*)mEmpireName;
        *(void**)((char*)mEmpireName + 0) = 0;
        *(void**)((char*)mEmpireName + 4) = 0;
        *(void**)((char*)mEmpireName + 8) = 0;
        s->f_00579a90(L"unknown");
    }
    mFlags = 0;
    mTrait = 0;
    mArchetype = 0x11;
    mEnemies.mBegin = 0; mEnemies.mEnd = 0; mEnemies.mCapacity = 0;
    mAllies.mBegin = 0;  mAllies.mEnd = 0;  mAllies.mCapacity = 0;
    mPoliticalID = 0xffffffffu;
    mStars.mBegin = 0; mStars.mEnd = 0; mStars.mCapacity = 0;
    mNextStarTowardsHome.mBegin = 0; mNextStarTowardsHome.mEnd = 0; mNextStarTowardsHome.mCapacity = 0;
    mHomeStar = 0xffffffffu;
    mHomePlanet = 0xffffffffu;
    mUFOKey.instanceID = 0; mUFOKey.typeID = 0; mUFOKey.groupID = 0;
    mCaptainKey.instanceID = 0; mCaptainKey.typeID = 0; mCaptainKey.groupID = 0;
    mEmpireMoney = 0;
    mTravelDistance = 3;
    mFieldD8 = 0xffffffff;
    mFieldDC = g_13eb1bc;
    mFieldE0 = g_13eb1bc;
    mFieldE4 = g_13eb1bc;
    mFieldE8 = g_13eb1bc;
    mFieldEC = g_13eb1bc;
    mFieldF0.mBegin = 0; mFieldF0.mEnd = 0; mFieldF0.mCapacity = 0;
    mpCityMusic = 0;
    ((MC*)mCultureSet)->f_00bf2c60();
    ((MC*)mDemandForTribute)->f_00b63890();
    mAdventureList.mpNext = &mAdventureList;
    mAdventureList.mpPrev = &mAdventureList;

    uint32_t sz = (uint32_t)(((char*)mFieldF0.mEnd - (char*)mFieldF0.mBegin) >> 2);
    float v = -1.0f;
    if (sz < 0xc) {
        ((MC*)&mFieldF0)->f_004b0a10(mFieldF0.mEnd, (int)(0xc - sz), &v);
    } else {
        memcpy((char*)mFieldF0.mBegin + 0x30, mFieldF0.mEnd, 0);
        mFieldF0.mEnd = (char*)mFieldF0.mBegin + 0x30;
    }
    mIdentity.mIDColorID = 0x53dbcf2;
}