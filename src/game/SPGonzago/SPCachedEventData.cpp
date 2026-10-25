// src/game/SPGonzago/SPCachedEventData.cpp -- migrated from slice(s) s00fe68a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCachedEventData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float    g_14853bc;      // 0x014853bc
extern float    g_13eb1bc;      // 0x013eb1bc
extern uint32_t g_16dc798;      // 0x016dc798  (gSimUniverse)
extern uint32_t g_16da84c;      // 0x016da84c
extern uint32_t g_16da858;      // 0x016da858
extern uint32_t g_3f10658;      // 0x03f10658

// ---- items of slice s00fe68a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uintptr_t;
void*  __cdecl FUN_01021300(void);                               // 0x01021300
void*  __cdecl FUN_01021230(void);                               // 0x01021230
void*  __cdecl FUN_00b3d2a0(void);                               // 0x00b3d2a0
void   __cdecl FUN_00571db0(void*, void*, void*, void*, void*);  // 0x00571db0
void   __cdecl FUN_00fe3b90(void* a);                            // 0x00fe3b90
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
extern float    g_14853bc;      // 0x014853bc
extern float    g_13eb1bc;      // 0x013eb1bc
extern uint32_t g_16dc798;      // 0x016dc798  (gSimUniverse)
extern uint32_t g_16da84c;      // 0x016da84c
extern uint32_t g_16da858;      // 0x016da858
extern uint32_t g_3f10658;      // 0x03f10658
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
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
// ---- items of slice s00fe68a0 end

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
