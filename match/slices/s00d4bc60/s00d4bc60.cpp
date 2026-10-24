// Slice s00d4bc60 -- SP drama-event instance data plus the rain-storm / sea-monster /
// night-predator / UFO-abduction events and the SP::cSPDramaManager event multimap.
//
// Layouts are the retail ones read from the disassembly (the 2008 dev PDB has moved a few
// members, so the retail offsets below are the authoritative ones):
//   * cDramaEventInstanceData keeps two vtable pointers (+0x00/+0x04), a flag byte at +0x0c, the
//     drama-event type index at +0x14, the countdown at +0x18, a vector2 at +0x20, the frequency
//     at +0x28, the activation type float at +0x2c, a flag at +0x30, tuning pointers at
//     +0x34/+0x3c, the property-list AutoRefCount at +0x40, a vector_map<u32,u32> at +0x44, the
//     game-data vector_map at +0x5c (its eastl::less<u32> comparator byte at +0x70) and the
//     storm/nest position Vector3 at +0x74.
//   * cSPDramaManager stores the drama-event multimap at +0x50 and the active-event bitmask at
//     +0x6c.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef unsigned int   size_t;

struct Vec3 { float x, y, z; };
struct cSPVector2 { float x, y; };

struct IInterface {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* AsInterface(u32 ifaceId);            // +0x0c
};

struct Property {
    void*  mpValue;   // +0x00
    u8     pad04[0x0c];
    u8     m_flags10; // +0x10
    u8     pad11;
    u16    m_type12;  // +0x12
    float* GetFloat();                                 // 0x0041ea70
    u32*   GetUInt();                                  // 0x0041ea00
};

struct cPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool FindProperty(u32 id, Property** ppOut);  // +0x24
};

// ------------------------------------------------------------------- eastl map storage
struct PairUR { u32 mKey; void* mValue; };                  // 8-byte vector_map entry

struct VecMapU32 { u32* mpBegin; u32* mpEnd; u32* mpCap; }; // eastl::vector_map<u32,u32>

PairUR* __cdecl LowerBound(PairUR* first, PairUR* last, const u32* key, bool flag); // 0x00d01260
extern "C" void  __cdecl operator_delete_array(void* p);     // 0x00f47380
void* __cdecl operator_new(u32 n, const char* pName, int a, int b,
                           const char* pFile, u32 line);      // 0x00f473a0

// eastl::vector_map<u32, AutoRefCount<cGameData>> as laid out in the retail build.
struct RefMap {
    PairUR* mpBegin;                 // +0x00
    PairUR* mpEnd;                   // +0x04
    u8      pad08[0xc];              // +0x08
    bool    mbFlag;                  // +0x14  (eastl::less<u32> comparator)
    u8      pad15[3];

    __forceinline PairUR* find(u32 keyIn)
    {
        const u32 key = keyIn;
        PairUR* const e = mpEnd;
        PairUR* it = LowerBound(mpBegin, e, &key, mbFlag);
        if (it == e || keyIn < it->mKey) it = e;
        else if (it == it + 1) it = e;
        return it;
    }
    void DestroyMembers();           // 0x00d4b4b0
};

// --------------------------------------------------------------- event-instance vtables
struct IEventVtbl {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void v28(int flag);                       // +0x28
    virtual void v2c();
    virtual void v30();                               // +0x30
};

namespace SP {

struct cDramaEventInstanceData {
    void** m_vtbl00;              // +0x00
    void** m_vtbl04;              // +0x04
    u8     pad08[4];              // +0x08
    u8     mFlag0c;               // +0x0c
    u8     pad0d[3];              // +0x0d
    u32    mEventMask10;          // +0x10
    i32    mEventType14;          // +0x14  index into sDramaEventToBitArray
    u32    mCountdown18;          // +0x18
    i32    mField1c;              // +0x1c
    cSPVector2 mVec20;            // +0x20
    float  mFreq28;               // +0x28
    float  mActivationType2c;     // +0x2c
    u8     mFlag30;               // +0x30
    u8     pad31[3];
    void*  mStream34;             // +0x34
    void*  mField38;              // +0x38
    void*  mTuning3c;             // +0x3c
    cPropertyList* mpPropList40;  // +0x40
    VecMapU32 mData44;            // +0x44
    u8     pad50[0xc];            // +0x50 .. +0x5c
    RefMap mGameDataMap5c;        // +0x5c
    Vec3   mPos74;                // +0x74

    __forceinline void* GetGameData(u32 key, u32 ifaceId)
    {
        PairUR* const e = mGameDataMap5c.mpEnd;
        PairUR* it = mGameDataMap5c.find(key);
        if (it == e) return 0;
        void* v = it->mValue;
        if (v == 0) return 0;
        return ((IInterface*)v)->AsInterface(ifaceId);
    }

    cDramaEventInstanceData* FUN_00d4ca70(u8 flags);      // 0x00d4ca70  destructor
    Vec3* FUN_00d4bbd0(Vec3* out);                         // 0x00d4bbd0  GetNestPosition
    u8    FUN_00d4bd10();                                  // 0x00d4bd10
    void  FUN_00d4cf70();                                  // 0x00d4cf70
    __declspec(noinline) void* FUN_00d4cf10(u32 a, u32 b);      // 0x00d4cf10
    u8    GetGameDataIsUsable();                           // 0x00d4d030
    u8    PlayIdleIfFlagged();                             // 0x00d4d220
    void  PostLoadEvent(void* arg);                        // 0x00d4d180
    void  ReleaseGameDataObject(int arg);                  // 0x00d4d2b0
    u8    AnyGameDataFlagged();                            // 0x00d4d340
};

struct cRainStormEvent : cDramaEventInstanceData {
    void TriggerEvent();                                   // 0x00d4bc60
};

struct cSeaMonsterEvent : cDramaEventInstanceData {
    bool ShouldActivate();                                 // 0x00d4c650
};

struct cNightPredatorEvent : cDramaEventInstanceData {
    bool ShouldActivate();                                 // 0x00d4d0b0
};

// cGameData-derived object whose noun array and creature link are read by this cluster.
struct cGameDataInfo {
    u8     pad00[0x40];
    void** mpArray40;             // +0x40  begin of a noun array
    void** mpArray44;             // +0x44  end
    u8     pad48[0x2c];           // +0x48 .. +0x74
    u8     mFlag74;               // +0x74
    u8     pad75[0x1b];
    u8     mFlag190;              // +0x190
    u8     pad191[0x4b7];
    void*  mCreature6c8;          // +0x6c8
};

// ---------------------------------------------------------------- cSPDramaManager
struct MMRange { void* mFirst; void* mSecond; };

struct RBTreeMM {
    u8 pad00[4];
    void equal_range(MMRange* out, const u32* key);        // 0x00f21cd0
};
void* __cdecl RBTreeIncrement(void* node);                  // 0x00921580

struct cSPDramaManager {
    u8       pad00[0x50];
    RBTreeMM mDramaEvents;             // +0x50
    u32      mActiveDramaEventMask;    // +0x6c

    cDramaEventInstanceData* GetActiveEvent(u32 type, bool onlyActive); // 0x00d4cad0
    bool  IsDramaEventActive(u32 type);                                // 0x00d4cb30
    void* GetActiveEventTuning(u32 type);                              // 0x00d4cb50
    void  HandleMeteorImpact(void* impact);                            // 0x00d4cb70
    void  TriggerEvent(cDramaEventInstanceData* e, int a2);            // 0x00d4d530
};

} // namespace SP

// ----------------------------------------------------------------------------- externs
void* __cdecl SP_PlanetModel();               // 0x00b3d350
void* __cdecl SP_NounManager();               // 0x00b3d300
void* __cdecl SP_StarManager();               // 0x00b3d2a0
void* __cdecl SP_GetCurrentGameMode();        // 0x00b5b800
void* __cdecl SP_PropertyManager();           // 0x0067de30
void* __cdecl SP_TriggerManager();            // 0x00b3d4d0
void* __cdecl SP_EventLog();                  // 0x00b3d3e0
void* __cdecl FUN_00b3d240();                 // 0x00b3d240
void* __cdecl FUN_00b3d480();                 // 0x00b3d480
void  __cdecl SetGlobalProperty(u32 id, float v);           // 0x005ca880
void* __cdecl CreateUFO(u32 type, void* a, void* b);        // 0x0102acb0
void  __cdecl ApplyFilterConstraints(void* a, char b);      // 0x0102c7f0
void  __cdecl WriteUint32(void* stream, const u32* v, int n, int endian); // 0x0093aa70
void  __fastcall FUN_00fc6f00(void* self, Vec3 pos, float a);// 0x00fc6f00
void  __cdecl FUN_00aca360(void* self, void* o);            // 0x00aca360

extern "C" double __cdecl sqrt(double);

struct RandomLCG {
    double RandomDoubleUniform();                 // 0x009360d0
};
RandomLCG gRand;                                  // 0x01601760

extern const float kOne;                          // 0x01485720  1.0f
extern const float kF_13ec4d0;                    // 0x013ec4d0
extern const float kF_147b4bc;                    // 0x0147b4bc
extern const float kF_13ebc5c;                    // 0x013ebc5c
extern const float gVec0169e440[3];               // 0x0169e440
extern u8     gGameModeA;                         // 0x01654c01
extern u8     gVec147aed8;                        // 0x0147aed8
extern u32    sDramaEventToBitArray[];            // 0x0147aef4

// ------------------------------------------------------------------ supporting types
struct IStormAnchor {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void* GetStormTarget();                  // +0x14
};

struct cPlanetModel {
    u8     pad00[0x24];
    IStormAnchor* mpAnchor24;            // +0x24
    u8     pad28[0x3c];
    void*  mpVisited64;                  // +0x64
    u8     pad68[0x28];
    void BuildSurfaceOrientation(Vec3* orient, Vec3* pos);              // 0x00b7f190
    void FUN_00b81630(Vec3* out, const Vec3* in);                      // 0x00b81630
    i32  GetContinent(const Vec3* pos);                                // 0x00b88590
    bool RayCast(const Vec3* dir, float radius, Vec3* out, float a,
                 u32 b, u32 c);                                        // 0x00b88770
    i32  FUN_00b7ea00(i32 continent);                                  // 0x00b7ea00
};

struct cUFO {
    u8    pad00[0x6c8];
    void* mCreature6c8;                                          // +0x6c8
    void FUN_00c3daa0(float a);                                  // 0x00c3daa0
    void FUN_00c3aa40(Vec3* n, Vec3* m);                         // 0x00c3aa40
};

struct cGameNounManager {
    void* GetAvatar();                                          // 0x00b1fdb0
};

struct cAvatarAnchor {                 // the sub-object embedded at avatar+0xc0
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vec3* GetPos();                                     // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8();
    virtual void vec();                                         // +0xec
};

struct cStarManager {
    void* FUN_00ba93b0();                                       // 0x00ba93b0
    float FUN_00885c90();                                       // 0x00885c90
};
struct cEmpire {
    u32 GetUFOKey();                                            // 0x00c326b0
};

struct cCreatureModeStrategy {
    static cCreatureModeStrategy* Instance();                   // 0x00d38840
    void FUN_00d39360(u32 a, void* ctx);                        // 0x00d39360
    void SignalCreatureEvent(u32 a);                            // 0x00d3cdc0
};

struct cTimeOfDay {
    static cTimeOfDay* Instance();                              // 0x00bc30b0
    float FUN_00bc2b30(const Vec3* pos);                        // 0x00bc2b30
    i32   FUN_00bc24c0(float t);                                // 0x00bc24c0
};

struct cSPUIEventLog {
    void RemoveEvent(u32 id, u32 b);                            // 0x00dd6d10
};

struct cSPCreatureBase {              // sub-object embedded at creature+8
    u8   Play(u32 a, u32 b);                                    // 0x00bc96a0
    void PlayWith(u32 a, u32 b, float c, void* d);              // 0x00bc97f0
    void ClearAll(u32 a, u32 b);                                // 0x00bc98f0
};

struct cCreatureCore {                // a creature / noun
    void* mpBehaviorsB4C;             // +0xb4c
    u8    FUN_00c0b770();                                       // 0x00c0b770
    void* FUN_00c04590();                                       // 0x00c04590
};

struct cNearNoun {
    void* GetPosition(float a, float b);                        // 0x00c6acc0
};

struct cNounContainer {
    void FUN_00aca360(void* o);                                 // 0x00aca360
    void FUN_00acc700(void* o);                                 // 0x00acc700
};

// --------------------------------------------------- eastl vector<ControlDrawable>
struct DElem { void* mpDrawable; void* mpRef; };

struct DElemVec {
    DElem* mpBegin;                       // +0x00
    DElem* mpEnd;                         // +0x04
    DElem* mpCap;                         // +0x08
    void insert(DElem* pos, const DElem* value);   // 0x00d4cda0
};

// ----------------------------------------------------------- eastl serialiser helpers
struct ISerializer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void* v18();                   // +0x18  stream
    virtual void  v1c();                   // +0x1c
    virtual ISerializer* v20();            // +0x20
    virtual void v24(); virtual void v28();
    virtual void v2c(void* v);             // +0x2c
};
struct VecMapGD { PairUR* mpBegin; PairUR* mpEnd; PairUR* mpCap; };

// =====================================================================================
// @ 0x00d4bc60
void SP::cRainStormEvent::TriggerEvent()
{
    cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
    void* target = pm->mpAnchor24->GetStormTarget();
    if (mpPropList40 != 0) {
        Property* p = 0;
        mpPropList40->FindProperty(0x8de8a7c2, &p);
    }
    Vec3 nest;
    mPos74 = *FUN_00d4bbd0(&nest);
    if (mPos74.x != gVec0169e440[0] || mPos74.y != gVec0169e440[1]
        || mPos74.z != gVec0169e440[2]) {
        FUN_00fc6f00(target, mPos74, mActivationType2c);
    }
}

// =====================================================================================
// @ 0x00d4bd10
u8 SP::cDramaEventInstanceData::FUN_00d4bd10()
{
    Vec3 nest;
    FUN_00d4bbd0(&nest);
    if (nest.x != gVec0169e440[0] || nest.y != gVec0169e440[1]
        || nest.z != gVec0169e440[2]) {
        float t = cTimeOfDay::Instance()->FUN_00bc2b30(&nest);
        if (cTimeOfDay::Instance()->FUN_00bc24c0(t) == 2) return 1;
    }
    return 0;
}

// =====================================================================================
// @ 0x00d4c1b0
void* __stdcall FUN_00d4c1b0(Vec3* pos, float scale, char flag)
{
    cUFO* ufo;
    if (flag == 0) {
        Vec3 c; c.x = 0.0f; c.y = 0.0f; c.z = 0.0f;
        ApplyFilterConstraints(&c, 0);
        ufo = (cUFO*)CreateUFO(7, &gVec147aed8, &c);
    } else {
        void* empire = ((cStarManager*)SP_StarManager())->FUN_00ba93b0();
        u32 key = ((cEmpire*)empire)->GetUFOKey();
        float dist = ((cStarManager*)SP_StarManager())->FUN_00885c90();
        ufo = (cUFO*)CreateUFO(7, &dist, (void*)key);
    }

    Vec3 orient;
    cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
    pm->BuildSurfaceOrientation(&orient, pos);

    float x = pos->x, y = pos->y, z = pos->z;
    float len = (float)sqrt((double)(x * x + (y * y + z * z)));
    float inv = 1.0f / len;
    len = len + scale;
    x *= inv; y *= inv; z *= inv;
    ufo->FUN_00c3daa0(len);
    x *= len; y *= len; z *= len;
    Vec3 n; n.x = x; n.y = y; n.z = z;
    ufo->FUN_00c3aa40(&n, &orient);

    if (SP_GetCurrentGameMode() == &gGameModeA) {
        *(u32*)((u8*)ufo->mCreature6c8 + 0x5fc) |= 1u;
    }
    return ufo;
}

// =====================================================================================
// @ 0x00d4c470
void FUN_00d4c470()
{
    cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
    cCreatureCore* avatar = (cCreatureCore*)nm->GetAvatar();
    avatar->FUN_00c0b770();
}

// =====================================================================================
// @ 0x00d4c5e0
struct StrategyCtx { void* mObject; u32 mField04; u32 mField08; u32 mPad0c; u32 mPad10; u32 mPad14; };

void FUN_00d4c5e0()
{
    cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
    void* avatar = nm->GetAvatar();
    ((cAvatarAnchor*)((u8*)avatar + 0xc0))->vec();
    StrategyCtx ctx;
    ctx.mObject = avatar;
    ctx.mField04 = 0;
    ctx.mField08 = 9;
    cCreatureModeStrategy::Instance()->FUN_00d39360(0xd3353639, &ctx);
    cCreatureModeStrategy::Instance()->SignalCreatureEvent(0xd3353639);
}

// =====================================================================================
// @ 0x00d4c650
bool SP::cSeaMonsterEvent::ShouldActivate()
{
    cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
    void* avatar = nm->GetAvatar();
    cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();

    Vec3 avatarPos = *((cAvatarAnchor*)((u8*)avatar + 0xc0))->GetPos();
    void* holder = ((cCreatureCore*)avatar)->FUN_00c04590();
    Vec3* otherPos = (Vec3*)((cNearNoun*)holder)->GetPosition(0.0f, 0.0f);

    i32 contA = pm->GetContinent(&avatarPos);
    i32 contB = pm->GetContinent(otherPos);
    if (contA == contB) return false;

    if (*((u8*)pm->mpVisited64 + contA) != 0) {
        i32 count = pm->FUN_00b7ea00(contA);
        u32 threshold = 100;
        if (mpPropList40 != 0) {
            Property* p = 0;
            if (mpPropList40->FindProperty(0x58d4cf9a, &p) && p->m_type12 == 10)
                threshold = *p->GetUInt();
        }
        return (u32)count > threshold;
    }

    Vec3 dir;
    pm->FUN_00b81630(&dir, &avatarPos);
    float radius = kF_13ec4d0;
    if (mpPropList40 != 0) {
        Property* p = 0;
        if (mpPropList40->FindProperty(0x9388b444, &p) && p->m_type12 == 13)
            radius = *p->GetFloat();
    }
    Vec3 hit;
    return !pm->RayCast(&avatarPos, radius, &hit, 1.0f, 0, 0);
}

// =====================================================================================
// @ 0x00d4ca70
SP::cDramaEventInstanceData* SP::cDramaEventInstanceData::FUN_00d4ca70(u8 flags)
{
    m_vtbl00 = (void**)0x147b090;
    m_vtbl04 = (void**)0x147b278;
    mGameDataMap5c.DestroyMembers();
    if (mData44.mpBegin != 0) operator_delete_array(mData44.mpBegin);
    if (mpPropList40 != 0) {
        void* old = mpPropList40;
        ((IInterface*)old)->v04();
    }
    m_vtbl04 = (void**)0x13ec458;
    m_vtbl00 = (void**)0x13eb938;
    if ((flags & 1) != 0) operator_delete_array(this);
    return this;
}

// =====================================================================================
// @ 0x00d4cad0
SP::cDramaEventInstanceData* SP::cSPDramaManager::GetActiveEvent(u32 type, bool onlyActive)
{
    u32 key = type;
    MMRange out;
    mDramaEvents.equal_range(&out, &key);
    void* it = out.mFirst;
    void* end = out.mSecond;
    while (it != end) {
        void* v = *(void**)((u8*)it + 0x14);
        if (!onlyActive || *(u8*)((u8*)v + 0xc) != 0) return (cDramaEventInstanceData*)v;
        it = RBTreeIncrement(it);
    }
    return 0;
}

// =====================================================================================
// @ 0x00d4cb30
bool SP::cSPDramaManager::IsDramaEventActive(u32 type)
{
    return GetActiveEvent(type, true) != 0;
}

// =====================================================================================
// @ 0x00d4cb50
void* SP::cSPDramaManager::GetActiveEventTuning(u32 type)
{
    cDramaEventInstanceData* e = GetActiveEvent(type, true);
    if (e != 0) return e->mpPropList40;
    return 0;
}

// =====================================================================================
// @ 0x00d4cb70
void SP::cSPDramaManager::HandleMeteorImpact(void* impact)
{
    if (impact == 0) return;
    cDramaEventInstanceData* e = GetActiveEvent(3, true);
    if (e == 0) return;
    void* gd = ((IInterface*)e)->AsInterface(0x5599ef6);
    if (gd == 0) return;
    if (*((u8*)gd + 0x74) == 0) return;

    void* tm = SP_TriggerManager();
    if (*(u32*)((u8*)tm + 0x2c) == 1) return;
    if (*(u32*)((u8*)tm + 0x2c) == 2) return;

    Vec3 pos = *(Vec3*)((u8*)(*(void**)((u8*)impact + 0x28)) + 4);
    float radius = *(float*)((u8*)gd + 0xbc);
    float f0c4 = *(float*)((u8*)gd + 0xc4);
    Vec3 zero; zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;

    void* gather = FUN_00b3d240();
    void* resBegin = 0;
    void* resEnd = 0;
    ((void (__thiscall*)(void*, Vec3*, float, Vec3*, u32, u32, u32))
        (*(void***)gather)[0x48 / 4])(gather, &pos, radius, &zero, 0, 0, 0);
    (void)resBegin; (void)resEnd;

    i32 count = (i32)(((u8*)resEnd - (u8*)resBegin) >> 2);
    (void)count; (void)f0c4;
}

// =====================================================================================
// @ 0x00d4cce0
void WriteSTLMapT(ISerializer* pIO, VecMapGD* pMap)
{
    int n = (int)(pMap->mpEnd - pMap->mpBegin);
    void* stream = pIO->v20()->v18();
    WriteUint32(stream, (const u32*)&n, 1, 0);

    for (PairUR* it = pMap->mpBegin; it != pMap->mpEnd; ++it) {
        void* s = pIO->v20()->v18();
        u32 key = it->mKey;
        WriteUint32(s, &key, 1, 0);
        pIO->v1c();
        void* v = 0;
        if (it->mValue != 0) v = ((IInterface*)it->mValue)->AsInterface(0x179c807);
        pIO->v2c(v);
        pIO->v1c();
    }
    pIO->v1c();
}

// =====================================================================================
// @ 0x00d4cda0
void DElemVec::insert(DElem* pos, const DElem* value)
{
    if (mpEnd == mpCap) {
        int n = (int)(mpEnd - mpBegin);
        int cap = (n > 0) ? n * 2 : 1;
        DElem* buf = (cap != 0)
            ? (DElem*)operator_new((u32)(cap * 8), "Simulator", 0, 0, "eastl/allocator.h", 0xd1)
            : 0;
        int idx = (int)(pos - mpBegin);
        for (int i = 0; i < idx; ++i) buf[i] = mpBegin[i];
        buf[idx] = *value;
        for (int i = idx; i < n; ++i) buf[i + 1] = mpBegin[i];
        if (mpBegin != 0) operator_delete_array(mpBegin);
        mpBegin = buf;
        mpEnd = buf + n + 1;
        mpCap = buf + cap;
        return;
    }

    if (pos >= mpBegin && pos < mpEnd) ++pos;
    if (mpEnd != 0) {
        *mpEnd = *(mpEnd - 1);
        if (mpEnd->mpRef != 0) {
            void** vt = *(void***)mpEnd->mpRef;
            ((void (__thiscall*)(void*))vt[0])(mpEnd->mpRef);
        }
    }
    for (DElem* d = mpEnd - 1; d != pos; --d) *d = *(d - 1);
    {
        void* nref = value->mpRef;
        void* oref = pos->mpRef;
        pos->mpDrawable = value->mpDrawable;
        if (nref != oref) {
            if (nref != 0) {
                void** vt = *(void***)nref;
                ((void (__thiscall*)(void*))vt[0])(nref);
            }
            pos->mpRef = nref;
            if (oref != 0) {
                void** vt = *(void***)oref;
                ((void (__thiscall*)(void*))vt[1])(oref);
            }
        }
    }
    mpEnd = mpEnd + 1;
}

// =====================================================================================
// @ 0x00d4cf10
void* SP::cDramaEventInstanceData::FUN_00d4cf10(u32 a, u32 b)
{
    PairUR* const e = mGameDataMap5c.mpEnd;
    PairUR* it = LowerBound(mGameDataMap5c.mpBegin, e, &a, mGameDataMap5c.mbFlag);
    if (it == e || a < it->mKey) it = e;
    else if (it == it + 1) it = e;
    if (it == e) return 0;
    void* v = it->mValue;
    if (v == 0) return 0;
    return ((IInterface*)v)->AsInterface(b);
}

// =====================================================================================
// @ 0x00d4cf70
void SP::cDramaEventInstanceData::FUN_00d4cf70()
{
    void* gd = GetGameData(0, 0x52aa6117);
    if (gd != 0) {
        cNounContainer* mgr = (cNounContainer*)FUN_00b3d480();
        void** it = *(void***)((u8*)gd + 0x40);
        void** end = *(void***)((u8*)gd + 0x44);
        for (; it != end; ++it) {
            void* creature = *it;
            void* bt = *(void**)((u8*)creature + 0xb4c);
            if (bt != 0) ((cSPCreatureBase*)((u8*)bt + 8))->ClearAll(0, 0x100);
            mgr->FUN_00aca360(creature);
        }
    }
    ((cSPUIEventLog*)SP_EventLog())->RemoveEvent(0xe2def8b4, 1);
}

// =====================================================================================
// @ 0x00d4d030
u8 SP::cDramaEventInstanceData::GetGameDataIsUsable()
{
    void* gd = GetGameData(0, 0x52aa6117);
    if (mActivationType2c < 0.0f) return 1;
    if (gd == 0) return 1;
    if (((cGameDataInfo*)gd)->mpArray40 == ((cGameDataInfo*)gd)->mpArray44) return 1;
    return 0;
}

// =====================================================================================
// @ 0x00d4d0b0
bool SP::cNightPredatorEvent::ShouldActivate()
{
    void* gd = GetGameData(0, 0x52aa6117);
    if (gd != 0 && *((u8*)gd + 0x190) != 0) return false;

    float chance = 0.0f;
    if (mpPropList40 != 0) {
        Property* p = 0;
        if (mpPropList40->FindProperty(0x360b94a0, &p) && p->m_type12 == 13)
            chance = *p->GetFloat();
    }
    if (gRand.RandomDoubleUniform() < chance) return true;
    return false;
}

// =====================================================================================
// @ 0x00d4d180
void SP::cDramaEventInstanceData::PostLoadEvent(void* arg)
{
    void* pm = SP_PropertyManager();
    if (mpPropList40 != 0) {
        void* old = mpPropList40;
        mpPropList40 = 0;
        ((IInterface*)old)->v04();
    }
    ((void (__thiscall*)(void*, void*, void*, cPropertyList**))
        (*(void***)pm)[0x2c / 4])(pm, mStream34, mTuning3c, &mpPropList40);
    ((IEventVtbl*)this)->v28(1);

    if (mFlag0c != 0) {
        void* gd = FUN_00d4cf10(0, 0xb033b403);
        if (gd != 0) {
            if (SP_GetCurrentGameMode() == &gGameModeA) SetGlobalProperty(0xdca3b514, 1.0f);
            void* obj = *(void**)((u8*)gd + 0x6c8);
            ((cSPCreatureBase*)((u8*)obj + 8))->PlayWith(2, 0, mActivationType2c, 0);
        }
    }
    (void)arg;
}

// =====================================================================================
// @ 0x00d4d220
u8 SP::cDramaEventInstanceData::PlayIdleIfFlagged()
{
    void* gd = GetGameData(0, 0xb033b403);
    if (gd != 0 && mActivationType2c >= 0.0f) {
        void* obj = *(void**)((u8*)gd + 0x6c8);
        if ((*(u8*)((u8*)obj + 0x5fc) & 2) == 0) return 0;
        if (((cSPCreatureBase*)((u8*)obj + 8))->Play(2, 0) == 0) return 1;
        return 0;
    }
    return 1;
}

// =====================================================================================
// @ 0x00d4d2b0
void SP::cDramaEventInstanceData::ReleaseGameDataObject(int arg)
{
    void* gd = GetGameData(0x5f115ab, 0x52aa6117);
    if (gd != 0) {
        void* p = ((cNearNoun*)gd)->GetPosition(kF_13ebc5c, kF_147b4bc);
        ((cNounContainer*)FUN_00b3d480())->FUN_00acc700(p);
    }
    (void)arg;
}

// =====================================================================================
// @ 0x00d4d340
u8 SP::cDramaEventInstanceData::AnyGameDataFlagged()
{
    void* gd = GetGameData(0x609f2f8, 0x52aa6117);
    if (gd == 0) return 1;
    void** it = ((cGameDataInfo*)gd)->mpArray40;
    void** end = ((cGameDataInfo*)gd)->mpArray44;
    u8 r = 1;
    while (it != end) {
        if (*(u8*)((u8*)(*it) + 0x135) != 0) { r = 0; break; }
        ++it;
    }
    return r;
}

// =====================================================================================
// @ 0x00d4d530
void SP::cSPDramaManager::TriggerEvent(cDramaEventInstanceData* e, int a2)
{
    e->mFlag0c = 1;
    if (e->mCountdown18 != 0xffffffffu && e->mCountdown18 != 0)
        e->mCountdown18 = e->mCountdown18 - 1;

    if (e->mpPropList40 != 0) {
        Property* p = 0;
        if (e->mpPropList40->FindProperty(0xb1f42539, &p) && p->m_type12 == 13)
            e->mActivationType2c = *p->GetFloat();
    }
    ((IEventVtbl*)e)->v30();

    i32 type = e->mEventType14;
    u32 bit = sDramaEventToBitArray[type];
    if (GetActiveEvent((u32)type, true) != 0)
        mActiveDramaEventMask |= bit;
    else
        mActiveDramaEventMask &= ~bit;
    (void)a2;
}