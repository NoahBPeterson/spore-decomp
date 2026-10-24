// Slice s00fe68a0 -- SP::cCachedEventData (the "cached event data" message handler)
// plus a small cluster of neighbouring UI refresh helpers.
//
//  0x00fe68a0  SP::cCachedEventData::cCachedEventData             (ret)
//  0x00fe6a00  SP::cCachedEventData::~cCachedEventData            (ret)
//  0x00fe6ad0  SP::cCachedEventData::InsertRange                  (ret 8)
//  0x00fe6b20  SP::cCachedEventData::RebuildInactivePlayersCache  (ret)
//  0x00fe6bc0  SP::cCachedEventData::RebuildNearbyEmpireStarsCache(ret)
//  0x00fe6dc0  SP::cCachedEventData::RebuildAllyColonyPlanetCache (ret)
//  0x00fe6e40  SP::cCachedEventData::RebuildPlayerColonyPlanetCache(ret)
//  0x00fe6fb0  SP::cCachedEventData::HandleMessage                (ret 8)
//  0x00fe7020  SP::cCachedEventData::Flush                        (ret)
//  0x00fe7100  SP::cCachedEventData::Prime                        (ret)
//  0x00fe7160  SP::cCachedEventData::Init                         (ret)
//  0x00fe71c0  SP::cCachedEventData::Shutdown                     (ret)
//  0x00fe7210  HandleEvent7210                                    (ret 8)
//  0x00fe72b0  RefreshNumbers_72b0                               (cdecl)
//  0x00fe73c0  RefreshNumbers_73c0                               (cdecl)
//  0x00fe74a0  RefreshPips_74a0                                  (cdecl)
//  0x00fe7590  ForwardWindowMessage_7590                         (cdecl)
//  0x00fe75d0  cSimOwner::cSimOwner                              (ret)
//  0x00fe7680  cSimOwner::Destroy                                (ret 4)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (MSVC 2008 SP1).
#include "types.h"

typedef unsigned int uintptr_t;

// ---- plain cdecl callees ---------------------------------------------------
void*  __cdecl FUN_01021300(void);                               // 0x01021300
void*  __cdecl FUN_01021230(void);                               // 0x01021230
void*  __cdecl FUN_010666a0(void);                               // 0x010666a0
void*  __cdecl FUN_00b3d2a0(void);                               // 0x00b3d2a0
void*  __cdecl FUN_0067dcc0(void);                               // 0x0067dcc0
void*  __cdecl FUN_00b3d380(void);                               // 0x00b3d380
void*  __cdecl FUN_00fd9c60(void);                               // 0x00fd9c60
void*  __cdecl FUN_00921580(void* node);                         // 0x00921580
void   __cdecl FUN_00571db0(void*, void*, void*, void*, void*);  // 0x00571db0
void*  __stdcall FUN_00401090(void* key);                        // 0x00401090
float  __cdecl FUN_004d12a0(void* a);                            // 0x004d12a0
void*  __cdecl FUN_00c028b0(void* a, int b);                     // 0x00c028b0
void   __cdecl FUN_00881ea0(double v, void* buf, int a, int b);  // 0x00881ea0
void   __cdecl FUN_00fe3b90(void* a);                            // 0x00fe3b90
float* __cdecl FUN_0041ea70(void);                               // 0x0041ea70
void*  __cdecl operator_new_sp(unsigned size, const char* name,
                               int a, int b, int c, int d);       // 0x00f473a0
void   __cdecl operator_delete(void* p);                         // 0x00f47380

// ---- member-style external callees ----------------------------------------
// The originals are __thiscall.  Modelling them as member functions of a stub
// class makes the compiler emit `mov ecx,<this>; call`, which is the exact
// original encoding.  Nothing is linked, so the stub symbols are just
// relocations (masked by chk.py).
struct MC {
    void* f_00c30f90();                  // 0x00c30f90
    void* f_004df550();                  // 0x004df550
    void* f_00fdf5f0();                  // 0x00fdf5f0
    void* f_0108db30();                  // 0x0108db30
    void* f_00ba6430();                  // 0x00ba6430
    void* f_00ba93b0();                  // 0x00ba93b0
    void* f_00b1fdb0();                  // 0x00b1fdb0
    bool  f_00bb9c00();                  // 0x00bb9c00
    bool  f_00bb9bd0();                  // 0x00bb9bd0
    void  f_00b962d0(void* src);         // 0x00b962d0
    void  f_00bb1080();                  // 0x00bb1080
    void  f_00c344f0(void* a, int b);    // 0x00c344f0
    void  f_00ae6970();                  // 0x00ae6970  vector dtor
    void  f_009a9600(void* root);        // 0x009a9600  rbtree nuke
    void  f_00e25bd0(void* first, void* last);   // 0x00e25bd0  vector::erase
    void  f_00a17a70(void* a, void* b, void* c);// 0x00a17a70  rbtree insert
    void* f_00d01790(int n);             // 0x00d01790
    void* f_00e012b0(unsigned id);       // 0x00e012b0
    void  f_00f13890();                  // 0x00f13890
    void  f_00f138c0();                  // 0x00f138c0
    void* f_00f13810();                  // 0x00f13810
    void  f_0093a560(int a, int b);      // 0x0093a560  Stopwatch ctor
    void  f_0093a1a0(int units);         // 0x0093a1a0  Stopwatch::SetUnits
    void  f_00b32250(unsigned id);       // 0x00b32250  DecPauseGate
    void* f_008105b0(unsigned id, int b);// 0x008105b0  FindWindowByID
    void* f_00c8b360(void* a, void* b);  // 0x00c8b360  StarManager::Query
};

// ---- globals used verbatim ------------------------------------------------
extern float    g_14853bc;      // 0x014853bc
extern float    g_13eb1bc;      // 0x013eb1bc
extern uint32_t g_16dc798;      // 0x016dc798  (gSimUniverse)
extern uint32_t g_16da84c;      // 0x016da84c
extern uint32_t g_16da858;      // 0x016da858
extern uint32_t g_3f10658;      // 0x03f10658

// ---- vtable slot helper ---------------------------------------------------
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))

// ---- a 12-byte resource key ------------------------------------------------
struct Key { uint32_t a, b, c; };

// ===========================================================================
// cCachedEventData layout (retail object is 0x108 bytes; the shipped PDB is a
// slightly older revision -- in retail the eastl vectors are 0x14-byte objects
// with a stateful sp_vector_allocator and everything downstream shifts +0x18).
// ===========================================================================
struct Vec {                    // eastl vector header
    void*    mBegin;            // +0x00
    void*    mEnd;              // +0x04
    void*    mCapacity;         // +0x08
    uint32_t mPad0c;            // +0x0c
    uint32_t mPad10;            // +0x10
};

struct Rbtree {                 // eastl set header
    uint32_t mField00;          // +0x00
    void*    mNode;             // +0x04  (self-referential anchor)
    void*    mNode2;            // +0x08
    void*    mRoot;             // +0x0c
    union {
        uint32_t mSize;         // +0x10
        uint8_t  mSizeByte;     // +0x10
    };
    uint32_t mField14;          // +0x14
    uint32_t mField18;          // +0x18
};

struct cCachedEventData {
    void*    mpVtbl;            // +0x00
    void*    mHandler;          // +0x04  (EA::Messaging::AutoHandler)
    void*    mArg08;            // +0x08
    uint32_t mArg0c;            // +0x0c
    uint32_t mArg10;            // +0x10
    uint32_t mArg14;            // +0x14
    Vec      mPlayerAllyColonyPlanets;   // +0x18
    Vec      mColonizedPlanetList;       // +0x2c
    Vec      mGrobPlanetList;            // +0x40
    Vec      mHomeworldStarsList;        // +0x54
    Vec      mNearbyEmpireStars;         // +0x68
    Vec      mNearbyKnownEmpireStars;    // +0x7c
    Rbtree   mNearbyEmpires;             // +0x90
    Rbtree   mLocalEmpires;              // +0xac
    Rbtree   mActiveEmpires;             // +0xc8
    Rbtree   mInactivePlayers;           // +0xe4
    int      mBioProtectedPlanetCount;   // +0x100
    int      mLoyaltyBoostedPlanetCount; // +0x104

    cCachedEventData();                                  // 0x00fe68a0
    ~cCachedEventData();                                 // 0x00fe6a00
    void InsertRange(void* first, void* last);           // 0x00fe6ad0
    void RebuildInactivePlayersCache();                  // 0x00fe6b20
    void RebuildNearbyEmpireStarsCache();                // 0x00fe6bc0
    void RebuildAllyColonyPlanetCache();                 // 0x00fe6dc0
    void RebuildPlayerColonyPlanetCache();               // 0x00fe6e40
    bool HandleMessage(unsigned int msg, void* arg);     // 0x00fe6fb0
    void Flush();                                        // 0x00fe7020
    void Prime();                                        // 0x00fe7100
    void Init();                                         // 0x00fe7160
    void Shutdown();                                     // 0x00fe71c0
};

// ===========================================================================
// 0x00fe68a0 -- constructor
// ===========================================================================
// @ 0x00fe68a0
cCachedEventData::cCachedEventData()
{
    mpVtbl  = (void*)0x1494390;
    mHandler = 0;
    mArg08 = 0;
    mArg0c = 0;
    mArg10 = 0;
    mArg14 = 0;

    mPlayerAllyColonyPlanets.mBegin = 0;
    mPlayerAllyColonyPlanets.mEnd = 0;
    mPlayerAllyColonyPlanets.mCapacity = 0;

    mColonizedPlanetList.mBegin = 0;
    mColonizedPlanetList.mEnd = 0;
    mColonizedPlanetList.mCapacity = 0;

    mGrobPlanetList.mBegin = 0;
    mGrobPlanetList.mEnd = 0;
    mGrobPlanetList.mCapacity = 0;

    mHomeworldStarsList.mBegin = 0;
    mHomeworldStarsList.mEnd = 0;
    mHomeworldStarsList.mCapacity = 0;

    mNearbyEmpireStars.mBegin = 0;
    mNearbyEmpireStars.mEnd = 0;
    mNearbyEmpireStars.mCapacity = 0;

    mNearbyKnownEmpireStars.mBegin = 0;
    mNearbyKnownEmpireStars.mEnd = 0;
    mNearbyKnownEmpireStars.mCapacity = 0;

    mNearbyEmpires.mNode2 = 0;
    mNearbyEmpires.mRoot = 0;
    mNearbyEmpires.mSize = 0;
    mNearbyEmpires.mRoot = 0;
    mNearbyEmpires.mSizeByte = 0;
    mNearbyEmpires.mField14 = 0;
    mNearbyEmpires.mNode = &mNearbyEmpires.mNode;
    mNearbyEmpires.mNode2 = &mNearbyEmpires.mNode;

    mLocalEmpires.mNode2 = 0;
    mLocalEmpires.mRoot = 0;
    mLocalEmpires.mSize = 0;
    mLocalEmpires.mRoot = 0;
    mLocalEmpires.mSizeByte = 0;
    mLocalEmpires.mField14 = 0;
    mLocalEmpires.mNode = &mLocalEmpires.mNode;
    mLocalEmpires.mNode2 = &mLocalEmpires.mNode;

    mActiveEmpires.mRoot = 0;
    mActiveEmpires.mSize = 0;
    mActiveEmpires.mNode = &mActiveEmpires.mNode;
    mActiveEmpires.mNode2 = &mActiveEmpires.mNode;
    mActiveEmpires.mRoot = 0;
    mActiveEmpires.mSizeByte = 0;
    mActiveEmpires.mField14 = 0;

    mInactivePlayers.mNode2 = 0;
    mInactivePlayers.mSize = 0;
    mInactivePlayers.mField14 = 0;
    mInactivePlayers.mNode = &mInactivePlayers.mNode;
    mInactivePlayers.mNode2 = &mInactivePlayers.mNode;
    mInactivePlayers.mSize = 0;
    mInactivePlayers.mSizeByte = 0;
    mInactivePlayers.mField18 = 0;

    ((MC*)this)->f_00d01790(0xa);
    ((MC*)&mPlayerAllyColonyPlanets)->f_00d01790(0x14);
    ((MC*)&mHomeworldStarsList)->f_00d01790(0x352);
}

// ===========================================================================
// 0x00fe6a00 -- destructor body
// ===========================================================================
// @ 0x00fe6a00
cCachedEventData::~cCachedEventData()
{
    ((MC*)&mInactivePlayers)->f_009a9600(mInactivePlayers.mRoot);
    ((MC*)&mActiveEmpires)->f_009a9600(mActiveEmpires.mRoot);
    ((MC*)&mLocalEmpires)->f_009a9600(mLocalEmpires.mRoot);
    ((MC*)&mNearbyEmpires)->f_009a9600(mNearbyEmpires.mRoot);

    ((MC*)&mNearbyKnownEmpireStars)->f_00ae6970();
    ((MC*)&mNearbyEmpireStars)->f_00ae6970();
    ((MC*)&mHomeworldStarsList)->f_00ae6970();
    ((MC*)&mGrobPlanetList)->f_00ae6970();
    ((MC*)&mColonizedPlanetList)->f_00ae6970();
    ((MC*)&mPlayerAllyColonyPlanets)->f_00ae6970();

    if (mHandler != 0) {
        void* h = mHandler;
        mHandler = 0;
        FUN_00571db0(h, (void*)(uintptr_t)mArg08, (void*)(uintptr_t)mArg0c,
                     (void*)(uintptr_t)mArg10, (void*)(uintptr_t)mArg14);
    }
    mpVtbl = (void*)0x13eb394;
}

// ===========================================================================
// 0x00fe6ad0 -- rbtree range insert (helper for the cache rebuilds)
// ===========================================================================
// @ 0x00fe6ad0
void cCachedEventData::InsertRange(void* first, void* last)
{
    while (first != last) {
        void* local = 0;
        ((MC*)this)->f_00a17a70(&local, (char*)first + 0x10, 0);
        first = FUN_00921580(first);
    }
}

// ===========================================================================
// 0x00fe6b20 -- rebuild the inactive-player set
// ===========================================================================
// @ 0x00fe6b20
void cCachedEventData::RebuildInactivePlayersCache()
{
    Rbtree* s = &mInactivePlayers;
    ((MC*)s)->f_009a9600(s->mRoot);
    s->mNode  = &s->mNode;
    s->mNode2 = &s->mNode;
    s->mRoot  = 0;
    s->mSizeByte = 0;
    s->mField14 = 0;

    void* cur = FUN_01021300();
    void* sm  = FUN_00b3d2a0();
    void* all = ((MC*)sm)->f_00ba6430();

    char* it  = *(char**)((char*)all + 8);
    char* end = (char*)all + 4;
    while (it != end) {
        void* rec = *(void**)(it + 0x14);
        void* id  = *(void**)(it + 0x10);
        if (rec != cur) {
            uint32_t flags = *(uint32_t*)((char*)rec + 0x50);
            if ((flags >> 6) & 1)
                ((MC*)s)->f_00a17a70(&id, &id, 0);
        }
        it = (char*)FUN_00921580(it);
    }
}

// ===========================================================================
// 0x00fe6bc0 -- rebuild the nearby-empire star cache
// ===========================================================================
// @ 0x00fe6bc0
void cCachedEventData::RebuildNearbyEmpireStarsCache()
{
    {
        Vec* v = &mNearbyEmpireStars;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }
    {
        Vec* v = &mNearbyKnownEmpireStars;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }
    {
        Rbtree* s = &mNearbyEmpires;
        ((MC*)s)->f_009a9600(s->mRoot);
        s->mNode  = &s->mNode;
        s->mNode2 = &s->mNode;
        s->mRoot  = 0;
        s->mSizeByte = 0;
        s->mField14 = 0;
    }

    void* empire = FUN_01021230();
    if (empire == 0)
        return;

    void* sm = FUN_00b3d2a0();

    float radius = g_14853bc;
    void* u = *(void**)(g_16dc798 + 0x10);
    if (u != 0) {
        if (((bool(__thiscall*)(void*, void*, uint32_t))VF(u, 0x24))(u, &radius, g_3f10658)) {
            void* val = 0;
            (void)val;
        } else {
            radius = g_14853bc;
        }
    }

    // query the star manager for stars within `radius`
    struct Query {
        uint32_t mField00;      // 0x1fff
        uint32_t mField04;      // 0x20
        uint32_t mField08;
        float    mField0c;      // g_13eb1bc
        float    mField10;      // radius
        float    mField14;      // g_13eb1bc
        uint32_t mField18;
    } q;
    q.mField00 = 0x1fff;
    q.mField08 = 0;
    q.mField18 = 0;
    q.mField04 = 0x20;
    q.mField0c = g_13eb1bc;
    q.mField14 = g_13eb1bc;
    q.mField10 = radius;

    void* found = ((MC*)sm)->f_00c8b360(&q, &mNearbyEmpireStars);
    if (found != 0)
        ((MC*)found)->f_00bb1080();
}

// ===========================================================================
// 0x00fe6dc0 -- rebuild the player-ally colony planet cache
// ===========================================================================
// @ 0x00fe6dc0
void cCachedEventData::RebuildAllyColonyPlanetCache()
{
    Vec* v = &mPlayerAllyColonyPlanets;
    ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);

    void* empire = FUN_01021300();
    if (empire == 0)
        return;

    void* list = ((MC*)empire)->f_0108db30();
    int count = (int)((*(void***)((char*)list + 4) - *(void***)list));
    for (int i = 0; i < count; ++i) {
        void* e = (*(void***)list)[i];
        if (e == 0)
            continue;
        void* sm = FUN_00b3d2a0();
        if (e == ((MC*)sm)->f_00ba93b0())
            continue;
        ((MC*)e)->f_00c344f0(v, 0);
    }
}

// ===========================================================================
// 0x00fe6e40 -- rebuild the player colony planet cache
// ===========================================================================
// @ 0x00fe6e40
void cCachedEventData::RebuildPlayerColonyPlanetCache()
{
    void* empire = FUN_01021300();
    if (empire == 0)
        return;

    Vec* v = &mColonizedPlanetList;
    ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    ((MC*)empire)->f_00c344f0(v, 0);

    Rbtree* s = &mLocalEmpires;
    ((MC*)s)->f_009a9600(s->mRoot);
    s->mNode  = &s->mNode;
    s->mNode2 = &s->mNode;
    s->mRoot  = 0;
    s->mSizeByte = 0;
    s->mField14 = 0;

    FUN_00b3d2a0();
    void* u = *(void**)(g_16dc798 + 0x10);
    if (u != 0) {
        void* val = 0;
        ((bool(__thiscall*)(void*, void*, uint32_t))VF(u, 0x24))(u, &val, g_3f10658);
    }

    mLoyaltyBoostedPlanetCount = 0;
    mBioProtectedPlanetCount = 0;

    // walk the colonized planets and count loyalty-boosted / bio-protected ones
    {
        void** begin = *(void***)((char*)v + 0x00);
        int count = (int)((*(void***)((char*)v + 4) - begin));
        if (count > 0) {
            for (int i = 0; i < count; ++i) {
                void* planet = begin[i];
                __int64 n = 0;
                void* p = *(void**)((char*)planet + 0x134);
                n = (*(uint32_t*)((char*)planet + 0x138) - *(uint32_t*)((char*)planet + 0x134));
                (void)n;
                int cnt2 = (int)(n / 0x2c);
                for (int j = 0; j < cnt2; ++j) {
                    uint32_t vv = *(uint32_t*)((char*)p + j * 0x2c);
                    if (vv == g_16da84c)
                        mLoyaltyBoostedPlanetCount += 1;
                    else if (vv == g_16da858)
                        mBioProtectedPlanetCount += 1;
                }
            }
        }
    }

    // rebuild the nearby-star / player set tail
    {
        Vec* nv = &mNearbyEmpireStars;
        for (char* it = (char*)nv->mBegin; it != (char*)nv->mEnd; it += 4) {
            void* id = ((MC*)*(void**)it)->f_00b1fdb0();
            ((MC*)s)->f_00a17a70(&id, &id, 0);
        }
    }
    {
        Rbtree* act = &mActiveEmpires;
        ((MC*)act)->f_00b962d0(s);
        ((MC*)act)->f_00b962d0(s);
    }
}

// ===========================================================================
// 0x00fe6fb0 -- HandleMessage (message pump)
// ===========================================================================
// @ 0x00fe6fb0
bool cCachedEventData::HandleMessage(unsigned int msg, void* arg)
{
    (void)arg;
    switch (msg) {
    case 0x043f2586u: {
        Vec* v = &mHomeworldStarsList;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
        FUN_00fe3b90(&mHomeworldStarsList);
        return true;
    }
    case 0x043f2583u:
    case 0x055bd8f7u:
        RebuildNearbyEmpireStarsCache();
        RebuildPlayerColonyPlanetCache();
        return true;
    case 0x043f2585u:
        RebuildAllyColonyPlanetCache();
        return true;
    default:
        return false;
    }
}

// ===========================================================================
// 0x00fe7020 -- Flush
// ===========================================================================
// @ 0x00fe7020
void cCachedEventData::Flush()
{
    {
        Vec* v = &mColonizedPlanetList;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }
    {
        Vec* v = &mPlayerAllyColonyPlanets;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }
    {
        Vec* v = &mHomeworldStarsList;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }
    {
        Vec* v = &mGrobPlanetList;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }
    {
        Vec* v = &mNearbyEmpireStars;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }
    {
        Vec* v = &mNearbyKnownEmpireStars;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }
    {
        Rbtree* s = &mNearbyEmpires;
        ((MC*)s)->f_009a9600(s->mRoot);
        s->mNode  = &s->mNode;
        s->mNode2 = &s->mNode;
        s->mRoot  = 0;
        s->mSizeByte = 0;
        s->mField14 = 0;
    }
    {
        Rbtree* s = &mLocalEmpires;
        ((MC*)s)->f_009a9600(s->mRoot);
        s->mNode  = &s->mNode;
        s->mNode2 = &s->mNode;
        s->mRoot  = 0;
        s->mSizeByte = 0;
        s->mField14 = 0;
    }
    {
        Rbtree* s = &mInactivePlayers;
        ((MC*)s)->f_009a9600(s->mRoot);
        s->mNode  = &s->mNode;
        s->mNode2 = &s->mNode;
        s->mRoot  = 0;
        s->mSizeByte = 0;
        s->mField14 = 0;
    }
}

// ===========================================================================
// 0x00fe7100 -- Prime
// ===========================================================================
// @ 0x00fe7100
void cCachedEventData::Prime()
{
    FUN_00fe3b90(&mHomeworldStarsList);
    RebuildPlayerColonyPlanetCache();
    RebuildAllyColonyPlanetCache();

    {
        Vec* v = &mGrobPlanetList;
        ((MC*)v)->f_00e25bd0(v->mBegin, v->mEnd);
    }

    void* sm = FUN_00b3d2a0();
    void* o  = ((MC*)sm)->f_00ba93b0();
    if (o != 0)
        ((MC*)o)->f_00c344f0(&mGrobPlanetList, 0);

    RebuildNearbyEmpireStarsCache();
    RebuildInactivePlayersCache();
}

// ===========================================================================
// 0x00fe7160 -- Init
// ===========================================================================
// @ 0x00fe7160
void cCachedEventData::Init()
{
    Flush();
    Prime();

    void* server = FUN_0067dcc0();
    cCachedEventData* p = this;
    p->mHandler = server;
    p->mArg08 = (void*)p;
    p->mArg0c = 0x1494378;
    p->mArg10 = 5;
    p->mArg14 = 0;

    typedef void (__thiscall* Fn)(void*, void*, uint32_t);
    if (server != 0 && p != 0) {
        for (int i = 0; i < 0x14; i += 4) {
            uint32_t fn = *(uint32_t*)(0x1494378 + i);
            ((Fn)VF(server, 0x24))(server, p, fn);
        }
    }
}

// ===========================================================================
// 0x00fe71c0 -- Shutdown
// ===========================================================================
// @ 0x00fe71c0
void cCachedEventData::Shutdown()
{
    Flush();
    if (mHandler != 0) {
        void* h = mHandler;
        mHandler = 0;
        FUN_00571db0(h, (void*)(uintptr_t)mArg08, (void*)(uintptr_t)mArg0c,
                     (void*)(uintptr_t)mArg10, (void*)(uintptr_t)mArg14);
    }
}

// ===========================================================================
// 0x00fe7210 -- event handler (separate small helper object)
// ===========================================================================
struct cHelper7210 {
    uint8_t mPad00[0xb8];
    uint8_t mbFieldB8;          // +0xb8

    bool HandleEvent(uint32_t msg, int* arg);   // 0x00fe7210
};

// @ 0x00fe7210
bool cHelper7210::HandleEvent(uint32_t msg, int* arg)
{
    if (msg == 0xcc0bf723u && mbFieldB8 != 0) {
        if (*arg == 2) {
            void* a = FUN_00fd9c60();
            ((MC*)a)->f_00fdf5f0();
        }
        ((MC*)FUN_00b3d380())->f_00b32250(0x7e9e4b7u);

        uint32_t self = (uint32_t)(uintptr_t)this;
        uint32_t handler = (self != 4) ? self : 0;
        mbFieldB8 = 0;

        void* server = FUN_0067dcc0();
        typedef void (__thiscall* Fn)(void*, uint32_t, uint32_t, uint32_t);
        ((Fn)VF(server, 0x2c))(server, handler, 0xcc0bf723u, 0xffffd8f1u);
    }
    return false;
}

// ===========================================================================
// 0x00fe72b0 -- refresh two numeric UI fields
// ===========================================================================
// @ 0x00fe72b0
void __cdecl RefreshNumbers_72b0()
{
    void* p = FUN_01021300();
    void* q = ((MC*)p)->f_00c30f90();

    Key key;
    key.a = ((uint32_t*)q)[0];
    key.b = ((uint32_t*)q)[1];
    key.c = ((uint32_t*)q)[2];

    void* prof = ((MC*)FUN_00401090(&key))->f_004df550();
    void* layout = *(void**)((char*)FUN_010666a0() + 0x258);

    float sum = FUN_004d12a0(FUN_00c028b0(prof, 1)) + *(float*)((char*)prof + 0x56c);
    int n = (int)sum;
    if ((float)n < sum)
        n += 1;

    {
        void* w = ((MC*)layout)->f_008105b0(0x797ec68u, 1);
        char buf[0x40];
        FUN_00881ea0((double)n, buf, 0x40, 0);
        ((void(__thiscall*)(void*, void*))VF(w, 0x80))(w, buf);
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x7fdbb88u, 1);
        char buf[0x40];
        FUN_00881ea0((double)*(float*)((char*)prof + 0x66c), buf, 0x40, 0);
        ((void(__thiscall*)(void*, void*))VF(w, 0x80))(w, buf);
    }
}

// ===========================================================================
// 0x00fe73c0 -- refresh two more numeric UI fields
// ===========================================================================
// @ 0x00fe73c0
void __cdecl RefreshNumbers_73c0()
{
    char buf[0x80];

    void* p = FUN_01021300();
    void* q = ((MC*)p)->f_00c30f90();

    Key key;
    key.a = ((uint32_t*)q)[0];
    key.b = ((uint32_t*)q)[1];
    key.c = ((uint32_t*)q)[2];

    void* prof = ((MC*)FUN_00401090(&key))->f_004df550();
    void* colLayout = FUN_010666a0();

    float f1 = *(float*)((char*)prof + 0x644);
    void* layout = *(void**)((char*)colLayout + 0x258);

    {
        void* w = ((MC*)layout)->f_008105b0(0x7edc860u, 1);
        FUN_00881ea0((double)f1, buf, 0x40, 0);
        ((void(__thiscall*)(void*, void*))VF(w, 0x80))(w, buf);
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x7d0ede8u, 1);
        FUN_00881ea0((double)*(float*)((char*)prof + 0x640), buf, 0x40, 0);
        ((void(__thiscall*)(void*, void*))VF(w, 0x80))(w, buf);
    }
}

// ===========================================================================
// 0x00fe74a0 -- refresh the "colonized planets" pip indicators
// ===========================================================================
// @ 0x00fe74a0
void __cdecl RefreshPips_74a0()
{
    void* p = FUN_01021300();
    void* q = ((MC*)p)->f_00c30f90();

    Key key;
    key.a = ((uint32_t*)q)[0];
    key.b = ((uint32_t*)q)[1];
    key.c = ((uint32_t*)q)[2];

    void* prof = ((MC*)FUN_00401090(&key))->f_004df550();

    int n = *(int*)((char*)prof + 0x668) + *(int*)((char*)prof + 0x664)
          + *(int*)((char*)prof + 0x660) + *(int*)((char*)prof + 0x648);

    void* layout = *(void**)((char*)FUN_010666a0() + 0x258);

    typedef void (__thiscall* Fn)(void*, int, unsigned char);
    {
        void* w = ((MC*)layout)->f_008105b0(0x797f4f3u, 1);
        ((Fn)VF(w, 0x7c))(w, 1, (unsigned char)(n > 0));
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x797f4f2u, 1);
        ((Fn)VF(w, 0x7c))(w, 1, (unsigned char)(n > 1));
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x797f4f1u, 1);
        ((Fn)VF(w, 0x7c))(w, 1, (unsigned char)(n > 2));
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x797f4f0u, 1);
        ((Fn)VF(w, 0x7c))(w, 1, (unsigned char)(n > 3));
    }
}

// ===========================================================================
// 0x00fe7590 -- forward a message to a nested window's v28 slot
// ===========================================================================
// @ 0x00fe7590
void __cdecl ForwardWindowMessage_7590(uint32_t a1, uint32_t a2)
{
    void* w = ((MC*)*(void**)((char*)FUN_010666a0() + 0x224))->f_00e012b0(0x7bb7790u);
    if (w != 0) {
        void* o = ((void*(__thiscall*)(void*, uint32_t))VF(w, 0xc))(w, 0x8ed27e7au);
        if (o != 0)
            ((void(__thiscall*)(void*, uint32_t, uint32_t))VF(o, 0x28))(o, a1, a2);
    }
}

// ===========================================================================
// 0x00fe75d0 -- ctor of a small listener / simulator-owner object
// ===========================================================================
struct cSimOwner {
    void*   mpVtbl;             // +0x00
    void*   mpVtbl2;            // +0x04
    void*   mField08;           // +0x08
    uint8_t pad0c[0x04];        // +0x0c
    uint8_t mStopwatch[0x18];   // +0x10  (EA::Stopwatch)
    uint8_t mbField28;          // +0x28
    uint8_t pad29[0x03];
    cSimOwner* mpField2c;       // +0x2c
    void*   mField30;           // +0x30
    uint8_t pad34[0x88];
    uint8_t mbFieldBC;          // +0xbc

    cSimOwner();                            // 0x00fe75d0
    void* Destroy(int flags);               // 0x00fe7680
};

// @ 0x00fe75d0
cSimOwner::cSimOwner()
{
    mpVtbl2  = (void*)0x13eb384;
    mpVtbl   = (void*)0x14943d0;
    mpVtbl2  = (void*)0x14943c0;
    mField08 = 0;
    ((MC*)((char*)this + 0x10))->f_0093a560(0, 0);
    mbField28 = 0;
    mpField2c = 0;
    ((MC*)((char*)this + 0x30))->f_00f13890();
    mbFieldBC = 0;
    ((MC*)((char*)this + 0x10))->f_0093a1a0(4);

    cSimOwner* p = (cSimOwner*)operator_new_sp(0x5c, "Simulator", 0, 0, 0, 0);
    if (p == 0)
        p = 0;
    else
        p = (cSimOwner*)((MC*)p)->f_00f13810();

    cSimOwner* old = mpField2c;
    if (p != old) {
        if (p != 0) {
            cSimOwner* o = (cSimOwner*)((char*)p + 4);
            ((void(__thiscall*)(void*))VF(o, 4))(o);
        }
        mpField2c = p;
        if (old != 0) {
            cSimOwner* o = (cSimOwner*)((char*)old + 4);
            ((void(__thiscall*)(void*))VF(o, 8))(o);
        }
    }
}

// ===========================================================================
// 0x00fe7680 -- dtor of the small listener / simulator-owner object
// ===========================================================================
// @ 0x00fe7680
void* cSimOwner::Destroy(int flags)
{
    mpVtbl  = (void*)0x14943d0;
    mpVtbl2 = (void*)0x14943c0;
    ((MC*)((char*)this + 0x30))->f_00f138c0();
    if (mpField2c != 0) {
        cSimOwner* o = (cSimOwner*)((char*)mpField2c + 4);
        ((void(__thiscall*)(void*))VF(o, 8))(o);
    }
    mpVtbl2 = (void*)0x13eb394;
    mpVtbl  = (void*)0x13eb938;
    if (flags & 1)
        operator_delete(this);
    return this;
}