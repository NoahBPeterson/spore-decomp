// 0x00ace5a0: per-tick update of a noun streaming / visibility manager (class name is a guess).
// Throttled by an accumulated timer (dt in ms * 0.001), then three passes over cGameNounManager data vectors:
//  1. objects of type 0x36be27e: bind/unbind the spawned noun (mpNoun) against the manager's position test
//  2. objects of type 0x18eb45e (skipped in game modes 1 and 2): call vtable slot 50 (activate) when not tracked
//  3. objects of type 0x1be418e: LOD switch by distance against this->mSpheres (5-float entries) and a global point
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (the unsigned->float conversion of dt stays x87).

#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };
struct Quat4 { float x, y, z, w; };
struct Sphere { float x, y, z, r2a, r2b; };   // 0x14 bytes

#define PV(n) virtual void s##n();

struct Ref {   // refcounted noun handle
    PV(0)
    virtual void Release();          // slot 1
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsDead();           // slot 11 (0x2c)
};

struct Placement {   // returned by FUN_00ad7360; slot 11 = position, slot 12 = rotation
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();
    virtual const Quat4* GetRotation();
};

struct SubLock {     // embedded at +0xC0 of the type-2 objects
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();   // 0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual bool IsLocked();             // 0x58
};

struct SubHidden {   // embedded at +0x34 of the LOD object's helper
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual bool IsHidden();             // 0x48
};

struct LodHelper {
    char pad[0x34];
    SubHidden mSub;
    char pad2[0x120 - 0x38];
    uint8_t mbFlag;
};

struct NounObj1 {      // type 0x36be27e
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsRemoved();                // 0x2c
    char pad04[0x84 - 4]; uint32_t mFlags;
    char pad88[0xa9 - 0x88]; uint8_t mbSpawned;
    char padaa[0x10c - 0xaa]; uint32_t mTypeID; uint32_t mField110;
    char pad114[0x1a4 - 0x114]; Ref* mpNoun; Vec3 mPos; Quat4 mRot; uint8_t mbDone;
};

struct NounObj2 {      // type 0x18eb45e
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsRemoved();                // 0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual int GetOwnerID();                // 0x4c
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    virtual void Activate(bool b);           // 0xc8
    bool Func_c0c0e0();   // 0x00c0c0e0
    char pad04[0x24 - 4]; uint32_t mKey;
    char pad28[0xc0 - 0x28]; SubLock mSub;
    char padc4[0x135 - 0xc4]; uint8_t mbFlag135;
    char pad136[0xb67 - 0x136]; uint8_t mbFlagB67;
};

struct NounObj3 {      // type 0x1be418e
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsRemoved();                // 0x2c
    char pad04[0x84 - 4]; uint8_t mbFlag84;
    char pad85[0x88 - 0x85]; uint32_t mOwnerSpeciesKey;    // 0x88
    char pad8c[0xf0 - 0x8c]; uint32_t mUsedFallback;       // 0xf0
    char padf4[0x108 - 0xf4]; float mSpawnTime;            // 0x108
    char pad10c[0x120 - 0x10c]; int mRangeMin; int mRangeMax; uint8_t mbNear;
    char pad129[0x160 - 0x129]; LodHelper* mpHelper;
    bool Func_c6a020();
    void Func_c6ace0(bool b);
    const Vec3* Func_c6acc0();
    bool Func_c6a030();
    void Func_c6b540();
    void UpdateFromArchetype(void* pArchetype, int b);   // 0x00c6e200
    void AddRef();                                       // +0x00 (IRefCounted slot 0)
    void Release();                                      // +0x04 (IRefCounted slot 1)
};

struct Tribe {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual int GetID();   // 0x4c
};

template<class T> struct PtrVec { T** mpBegin; T** mpEnd; T** begin() const { return mpBegin; } T** end() const { return mpEnd; } };
template<class T> struct VecOut { char pad[4]; PtrVec<T> mVec; };

class NounVisibility;
struct NounManager {
    Tribe* GetPlayerTribe();                                       // 0x00bfc5f0
    void* GetGameDataVector(void (*)(), void (*)(), void (*)(), void (*)(), uint32_t);   // 0x00b21340
    void RemoveNoun(Ref* pNoun);                                   // 0x00b225d0
};

struct HIter { void* mpNode; void** mpBucket; HIter() {} HIter(const HIter& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {} };
struct HTable {
    char pad[4]; void** mpBucketArray; uint32_t mnBucketCount;
    void* End() const { return mpBucketArray[mnBucketCount]; }
    HIter find(const uint32_t& key);                               // 0x00645ed0
};

struct ModeInfo { char pad[0x2c]; int mMode; };

NounManager* GetNounManager();            // 0x00b3d300
uint32_t GetCurrentGameMode();            // 0x00b5b800
ModeInfo* GetModeInfo();                  // 0x00b3d4d0
Placement* FindPlacement(Ref** ppNoun);   // 0x00ad7360 (cdecl)
void ActivateObj(NounObj1* p, int a, int b);   // 0x00b931c0 (cdecl)

void F_cd7d10(); void F_d3d420(); void F_b1e500(); void F_ace070(); void F_ace0f0(); void F_accc30();

extern float gTimer;       // 0x0167a490
extern float gThreshold;   // 0x01565ce0
extern int gStat0, gStat1, gStat2;   // 0x0167a37c, 0x0167a380, 0x0167a384
extern int gCurrentID;     // 0x0169e370
extern int gMaxPerTick;    // 0x01565d04
extern Vec3 gPoint;        // 0x0167ea30

class NounVisibility {
public:
    char pad00[0x20];
    Sphere* mpSpheresBegin;      // 0x20
    Sphere* mpSpheresEnd;        // 0x24
    char pad28[0xe0 - 0x28];
    HTable mTable;               // 0xe0
    bool Func_ac8d80(const Vec3* p);   // 0x00ac8d80
    bool Func_ac8df0(const Vec3* p);   // 0x00ac8df0
    void Update(int unused, uint32_t dt);
};

static inline void ReleaseNoun(Ref*& r)
{
    Ref* p = r;
    if (p) { r = 0; p->Release(); }
}

// @ 0x00ace5a0
void NounVisibility::Update(int unused, uint32_t dt)
{
    if (dt > 0) {
        gTimer += (float)dt * 0.001f;
        if (gTimer < gThreshold)
            return;
        gTimer = 0.0f;
    }
    NounManager* pMgr = GetNounManager();
    gStat2 = 0;
    gStat1 = 0;
    gStat0 = 0;
    bool bModeA = GetCurrentGameMode() == 0x1654c01;
    bool bModeB = GetCurrentGameMode() == 0x1654c01;
    int playerID;
    if (pMgr->GetPlayerTribe())
        playerID = pMgr->GetPlayerTribe()->GetID();
    else
        playerID = -1;

    // pass 1
    {
        VecOut<NounObj1>* pVec = (VecOut<NounObj1>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_ace070, F_b1e500, 0x36be27e);
        const PtrVec<NounObj1>& vec = pVec->mVec;
        NounObj1** it = vec.begin();
        NounObj1** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj1* p = *it;
            if (p->IsRemoved() || p->mTypeID == 0 || p->mField110 == 0 || p->mbDone != 0)
                continue;
            Ref** ppNoun = &p->mpNoun;
            if (*ppNoun && (*ppNoun)->IsDead()) {
                p->mbDone = 1;
                ReleaseNoun(*ppNoun);
                continue;
            }
            if (p->mTypeID == 0x1be418e) {
                if (*ppNoun == 0)
                    ActivateObj(p, -1, -1);
                continue;
            }
            if (p->mFlags & 0x100)
                continue;
            if (p->mbSpawned != 0) {
                Placement* pPlace = FindPlacement(ppNoun);
                const Vec3* pPos;
                if (pPlace)
                    pPos = pPlace->GetPosition();
                else
                    pPos = &p->mPos;
                if (Func_ac8d80(pPos)) {
                    if (*ppNoun) {
                        if (pPlace) {
                            const Vec3* v = pPlace->GetPosition();
                            p->mPos = *v;
                            const Quat4* q = pPlace->GetRotation();
                            p->mRot = *q;
                        }
                        pMgr->RemoveNoun(*ppNoun);
                        ReleaseNoun(*ppNoun);
                    }
                    p->mbSpawned = 0;
                } else if (*ppNoun == 0) {
                    if (Func_ac8df0(&p->mPos))
                        ActivateObj(p, -1, -1);
                }
            } else {
                if (Func_ac8df0(&p->mPos)) {
                    p->mbSpawned = 1;
                    if (*ppNoun == 0)
                        ActivateObj(p, -1, -1);
                }
            }
        }
    }

    // pass 2
    ModeInfo* pMode = GetModeInfo();
    int mode = pMode->mMode;
    if (mode != 1 && mode != 2) {
        VecOut<NounObj2>* pVec = (VecOut<NounObj2>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_ace0f0, F_b1e500, 0x18eb45e);
        const PtrVec<NounObj2>& vec = pVec->mVec;
        NounObj2** it = vec.begin();
        NounObj2** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj2* p = *it;
            if (p->IsRemoved() || p->mbFlag135 == 0 || p->mbFlagB67 == 0)
                continue;
            if (!(bModeB == 1 || !p->Func_c0c0e0()))
                continue;
            HTable& tbl = mTable;
            uint32_t key = p->mKey;
            void* pEnd = tbl.End();
            if (tbl.find(key).mpNode != pEnd)
                continue;
            if (p->mSub.IsLocked())
                continue;
            int id = p->GetOwnerID();
            if (id != -1 && id == playerID)
                continue;
            if (Func_ac8d80(p->mSub.GetPosition()))
                p->Activate(true);
        }
    }

    // pass 3
    {
        int nCount = 0;
        VecOut<NounObj3>* pVec = (VecOut<NounObj3>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e);
        const PtrVec<NounObj3>& vec = pVec->mVec;
        NounObj3** it = vec.begin();
        NounObj3** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj3* p = *it;
            if (p->IsRemoved())
                continue;
            if (p->mbFlag84 == 0 && bModeA && gCurrentID >= 0 && (gCurrentID < p->mRangeMin || gCurrentID > p->mRangeMax)) {
                p->Func_c6ace0(false);
                if (p->mpHelper)
                    p->mpHelper->mbFlag = 1;
                continue;
            }
            bool bActivate = false;
            if (p->Func_c6a020()) {
                bool bInside = false;
                if (p->mbFlag84 == 0) {
                    const Vec3* pPos = p->Func_c6acc0();
                    for (Sphere* s = mpSpheresBegin; s != mpSpheresEnd; ++s) {
                        float dx = pPos->x - s->x, dy = pPos->y - s->y, dz = pPos->z - s->z;
                        if (s->r2b > dz * dz + dy * dy + dx * dx) { bInside = true; break; }
                    }
                } else {
                    bInside = true;
                }
                if (!bInside) {
                    p->Func_c6ace0(false);
                } else {
                    const Vec3* pPos = p->Func_c6acc0();
                    float dx = pPos->x - gPoint.x, dy = pPos->y - gPoint.y, dz = pPos->z - gPoint.z;
                    bool bNear = 400.0f > dz * dz + dy * dy + dx * dx;
                    if (p->mpHelper)
                        bNear = p->mpHelper->mSub.IsHidden();
                    p->mbNear = !bNear;
                }
            } else {
                if (p->mbFlag84 != 0) {
                    bActivate = true;
                } else if (nCount < gMaxPerTick) {
                    const Vec3* pPos = p->Func_c6acc0();
                    for (Sphere* s = mpSpheresBegin; s != mpSpheresEnd; ++s) {
                        float dx = pPos->x - s->x, dy = pPos->y - s->y, dz = pPos->z - s->z;
                        if (s->r2a >= dz * dz + dy * dy + dx * dx) {
                            if (p->Func_c6a030())
                                bActivate = true;
                            break;
                        }
                    }
                }
                if (bActivate) {
                    p->Func_c6ace0(true);
                    if (p->mpHelper)
                        p->mpHelper->mbFlag = 1;
                    p->Func_c6b540();
                    ++nCount;
                }
            }
        }
    }
}

// ============================================================================================
// Simulator casting manager (cCastingManager).  Sibling functions of the same class:
//   00acf230 ctor, 00acf0b0 SpVector<cTribeEntry>::DoInsertValue, 00acebd0 / 00acf3e0 members.
// Field/argument names are descriptive guesses chosen to match the retail offsets.
// ============================================================================================

// ---- EASTL-style intrusive refcounting -----------------------------------------------------
struct IRefCounted {
    virtual int AddRef();      // +0x00
    virtual int Release();     // +0x04
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x)
    {
        T* const pObject = x.mpObject;
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

struct sp_vector_allocator { const char* mpName; uint32_t mFlags; };

template <class T> struct SpVector {
    T* mpBegin;                       // +0x00
    T* mpEnd;                         // +0x04
    T* mpCapacity;                    // +0x08
    sp_vector_allocator mAllocator;   // +0x0c
    void DoInsertValue(T* pos, const T& value);
    SpVector& operator=(const SpVector& x);
};

struct cTribeEntry {                                  // 0x18 bytes
    AutoRefCount<IRefCounted> mpTribe;                // +0x00
    SpVector<AutoRefCount<IRefCounted> > mMembers;    // +0x04
};

// out-of-line template instance used by the insertion path
template <> SpVector<AutoRefCount<IRefCounted> >&
    SpVector<AutoRefCount<IRefCounted> >::operator=(const SpVector<AutoRefCount<IRefCounted> >& x);   // 0x1011cc0

// ---- record-level relocation helpers (operate on 0x18-byte cTribeEntry records) -------------
cTribeEntry* __cdecl FUN_00acaab0(cTribeEntry* first, cTribeEntry* last, cTribeEntry* dst);   // 0xacaab0
void         __cdecl FUN_00acab70(cTribeEntry* first, cTribeEntry* last, cTribeEntry* dst);   // 0xacab70
int*         __cdecl FUN_00acc330(int* dstEnd, int* srcEnd, int* srcBegin);                   // 0xacc330

// entry assign/construct (ecx = record, one stack arg = source record)
struct EntryOps { cTribeEntry* FUN_00aca970(cTribeEntry* src); };   // 0xaca970

// ---- allocator -------------------------------------------------------------------------------
void* __cdecl operator_new(size_t size, const char* name, int a, int b, const char* file, int line);   // 0x00f473a0
void  __cdecl operator_delete(void* p);                                                                 // 0x00f47380

extern const char kSimulatorName[];      // 0x013f09b4  "Simulator"
extern const char kAllocatorFile[];      // 0x013ebb38  "allocator.h"
extern const char kCityVisualizerName[]; // 0x0145a270  "Simulator/cCityVisualizer"
extern const char kAbandonedName[];      // 0x0145a248  "Simulator/cAbandonedCitizenVisualizer"

// ---- cube/cell map (hash set) embedded at cCastingManager+0xc0 / +0xe0 ------------------------
struct TileNode {                     // value starts at +0x04
    uint32_t mKey;                    // +0x00
    Vec3     mPos;                    // +0x04
    float    mDist;                   // +0x10
};
struct HFind { void* mpNode; void* mpBucket; };
struct CellMap {                      // 0x20 bytes
    void*    mpUnused00;              // +0x00
    void**   mpBucketArray;           // +0x04  (empty -> g_EmptyBuckets)
    uint32_t mnBucketCount;           // +0x08
    uint32_t mUnused0c;               // +0x0c
    float    mLoadFactor;             // +0x10
    float    mGrowFactor;             // +0x14
    uint32_t mSize;                   // +0x18
    uint32_t mUnused1c;               // +0x1c
    HFind* Find(HFind* out, const uint32_t* key);   // 0x00ac9d30
    TileNode* TileAt(const uint32_t* key);          // 0x00ace170
};

extern void* g_EmptyBuckets;          // 0x0154df28  empty bucket array (1 bucket)
extern const float kOne;              // 0x01485720
extern const float kTwo;              // 0x01470f1c
extern const float kHalf;             // 0x01471064
extern const float kQuarter;          // 0x013eb8a0
extern const float kZero;             // 0x01485378
extern const uint32_t kSignFlip[4];   // 0x013eb8b0
extern uint8_t g_FaceAxes[];          // 0x0145a090  3 axis indices per cube-face pair (stride 4)
extern const wchar_t kEmptyString16[];// 0x01667bac  eastl empty string
extern float g_SpawnTime;             // 0x01565cec

struct PlanetModel {
    float    GetWaterHeight();                          // 0x00b7e390
    float    GetRadiusAt(const Vec3* dir);              // 0x00b7ef70
    Vec3*    SnapToSurface(Vec3* out, const Vec3* dir); // 0x00b81630
};
PlanetModel* SP_PlanetModel();          // 0x00b3d350
void*        GetActivePlanet();         // 0x01021260

struct ResourceKey { uint32_t mA; uint32_t mB; };
struct cSpeciesArchetype { char pad[0x10]; uint32_t mSpeciesKey; };
struct SpeciesManager {
    cSpeciesArchetype* GetSpeciesArchetype(uint32_t id, uint32_t level);   // 0x004e0050
    void*              GetProfile(const ResourceKey* key);                 // 0x004df550
};
SpeciesManager* FUN_00401090();         // 0x00401090 (cdecl, returns the editor species manager)

struct cPollOwner { void UpdateProperty(uint32_t id, const Vec3* key); };   // 0x0060d860
cPollOwner* GetPollinator();                                                // 0x0067cb30

// refcounted handle stored in the tracked list of a cell node
struct Publication { NounObj3* mpObj; };
struct PubVector { void Push(NounObj3** ppRef); };     // 0x00e1c7f0 (thiscall, one stack arg)
struct RawVec3 { uint32_t x, y, z; };
extern RawVec3 g_NoPosition;                          // 0x0167a39c

// sub-object ctors invoked by the cCastingManager ctor (ecx = sub-object)
struct CtorNoArg { void FUN_00b5b960(); void FUN_00b95050(); };             // 0x00b5b960 / 0x00b95050
struct VisCtor   { void* FUN_00d5e730(); void* FUN_00d59580(); };           // 0x00d5e730 / 0x00d59580

class cCastingManager {
public:
    void*    mpVtbl0;              // +0x000
    void*    mpVtbl4;              // +0x004
    char     pad008[0x14];         // +0x008
    void*    mpVtbl1c;             // +0x01c
    void*    mpInlineBegin;        // +0x020
    void*    mpInlineEnd;          // +0x024
    void*    mpInlineCap;          // +0x028
    char     pad02c[0x08];         // +0x02c
    int      mField34;             // +0x034
    char     mInlineBuf[0x50];     // +0x038
    uint32_t mField88;             // +0x088
    uint32_t mField8c;             // +0x08c
    uint32_t mField90;             // +0x090
    char     pad094[0x0c];         // +0x094
    int      mFieldA0;             // +0x0a0
    void*    mpCityVisualizer;     // +0x0a4
    void*    mpTribesBegin;        // +0x0a8
    void*    mpTribesEnd;          // +0x0ac
    void*    mpTribesCapacity;     // +0x0b0
    char     pad0b4[0x08];         // +0x0b4
    void*    mpAbandonedVisualizer;// +0x0bc
    CellMap  mCells;               // +0x0c0
    CellMap  mCells2;              // +0x0e0
    uint8_t  mField100;            // +0x100
    uint8_t  mField101;            // +0x101
    char     pad102[0x02];         // +0x102
    const wchar_t* mpString104;    // +0x104
    const wchar_t* mpString108;    // +0x108
    const wchar_t* mpString10c;    // +0x10c
    char     pad110[0x04];         // +0x110
    uint8_t  mField114;            // +0x114
    char     pad115[0x03];         // +0x115
    void*    mpField118;           // +0x118
    void*    mpField11c;           // +0x11c
    void*    mpField120;           // +0x120
    char     pad124[0x08];         // +0x124
    char     mSub12c[0x34];        // +0x12c
    char     mSub160[0x34];        // +0x160

    cCastingManager* Construct();                                  // 0x00acf230
    void  InsertTribe(cTribeEntry* pos, const cTribeEntry& value);  // (unused helper slot)
    void  CastNoun(NounObj3* pNoun, char bFlag);                   // 0x00acebd0
    void  SpawnHerdFromProfile(Vec3* pPos, void* pMgr);            // 0x00acf3e0
};

struct NounManagerSpawn {
    NounObj3* CreateNoun(float* pPos, void* profile, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00b23940
};

// @ 0x00acf0b0  ?DoInsertValue@?$SpVector@UcTribeEntry@@@@
template <> void SpVector<cTribeEntry>::DoInsertValue(cTribeEntry* pos, const cTribeEntry& value)
{
    if (mpEnd != mpCapacity) {
        cTribeEntry* v = const_cast<cTribeEntry*>(&value);
        if (v >= pos && v < mpEnd)
            v += 1;

        if (mpEnd)
            ((EntryOps*)(void*)mpEnd)->FUN_00aca970(mpEnd - 1);

        FUN_00acc330((int*)pos, (int*)(mpEnd - 1), (int*)mpEnd);

        pos->mpTribe = v->mpTribe;
        pos->mMembers = v->mMembers;

        mpEnd += 1;
        return;
    }

    unsigned n = (unsigned)(mpEnd - mpBegin);
    cTribeEntry* newBuf;
    if (n != 0) {
        n *= 2;
        if (n == 0) {
            newBuf = 0;
            goto L;
        }
    } else {
        n = 1;
    }
    newBuf = (cTribeEntry*)operator_new(n * 0x18, kSimulatorName, 0, 0, kAllocatorFile, 0xd1);
L:
    {
        cTribeEntry* p = mpBegin;
        cTribeEntry* mid = FUN_00acaab0(p, pos, newBuf);
        FUN_00acab70(p, pos, newBuf);

        if (mid)
            ((EntryOps*)(void*)mid)->FUN_00aca970(const_cast<cTribeEntry*>(&value));

        cTribeEntry* pLast = mpEnd;
        cTribeEntry* pNewEnd = FUN_00acaab0(pos, pLast, mid + 1);
        FUN_00acab70(pos, pLast, mid + 1);

        cTribeEntry* pOld = mpBegin;
        if (pOld && ((int*)pOld)[-1] != 0)
            operator_delete(pOld);

        mpEnd = pNewEnd;
        mpBegin = newBuf;
        mpCapacity = (cTribeEntry*)((char*)newBuf + n * 0x18);
    }
}

// @ 0x00acf230  cCastingManager ctor
cCastingManager* cCastingManager::Construct()
{
    ((CtorNoArg*)this)->FUN_00b5b960();
    mpVtbl1c = (void*)0x13eb394;
    mpVtbl0  = (void*)0x145a1c8;
    mpVtbl4  = (void*)0x145a1c4;
    mpVtbl1c = (void*)0x145a1bc;

    mField34 = 0;
    mpInlineBegin = (char*)this + 0x38;
    mpInlineEnd   = (char*)this + 0x38;
    mpInlineCap   = (char*)mpInlineBegin + 0x50;
    mField88 = 0;
    mField8c = 0;
    mField90 = 0;
    mFieldA0 = -1;
    mpCityVisualizer = 0;
    mpTribesBegin = 0;
    mpTribesEnd = 0;
    mpTribesCapacity = 0;
    mpAbandonedVisualizer = 0;

    const float kLoad = kOne;
    const float kGrow = kTwo;
    void** const pEmptyBuckets = (void**)&g_EmptyBuckets;
    mCells.mLoadFactor = kLoad;
    mCells.mGrowFactor = kGrow;
    mCells.mUnused0c = 0;
    mCells.mSize = 0;
    mCells.mnBucketCount = 1;
    mCells.mpBucketArray = pEmptyBuckets;

    mCells2.mLoadFactor = kLoad;
    mCells2.mGrowFactor = kGrow;
    mCells2.mpBucketArray = pEmptyBuckets;
    mCells2.mnBucketCount = 1;
    mCells2.mUnused0c = 0;
    mCells2.mSize = 0;

    mField100 = 0;
    mField101 = 0;
    mpString104 = kEmptyString16;
    mpString108 = kEmptyString16;
    mpString10c = kEmptyString16 + 1;
    mField114 = 0;
    mpField118 = 0;
    mpField11c = 0;
    mpField120 = 0;

    ((CtorNoArg*)&mSub12c)->FUN_00b95050();
    ((CtorNoArg*)&mSub160)->FUN_00b95050();

    void* pVis = operator_new(0xc88, kCityVisualizerName, 0, 0, 0, 0);
    void* pCity = pVis ? ((VisCtor*)pVis)->FUN_00d5e730() : 0;
    mpCityVisualizer = pCity;

    void* pAband = operator_new(0x18, kAbandonedName, 0, 0, 0, 0);
    if (pAband)
        mpAbandonedVisualizer = ((VisCtor*)pAband)->FUN_00d59580();
    else
        mpAbandonedVisualizer = 0;

    return this;
}

// @ 0x00acebd0  cCastingManager::CastNoun
void cCastingManager::CastNoun(NounObj3* pNoun, char bFlag)
{
    PlanetModel* pModel = SP_PlanetModel();
    if (pModel == 0)
        return;

    const Vec3* p = pNoun->Func_c6acc0();
    float nx = p->x;
    float ny = p->y;
    float nz = p->z;
    float ax = fabsf(nx);
    float ay = fabsf(ny);
    float az = fabsf(nz);

    int idxU;
    int idxV;
    unsigned face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            idxU = (int)((ny / nx + kOne) * kTwo);
            idxV = (int)((nz / ax + kOne) * kTwo);
            face = (nx < kZero) ? 3 : 2;
        } else {
            idxU = (int)((nz / ny + kOne) * kTwo);
            idxV = (int)((nx / ay + kOne) * kTwo);
            face = (ny < kZero) ? 5 : 4;
        }
    } else {
        idxU = (int)((nx / nz + kOne) * kTwo);
        idxV = (int)((ny / az + kOne) * kTwo);
        face = (nz < kZero) ? 1 : 0;
    }
    if (idxU == 4)
        idxU = 3;
    if (idxV == 4)
        idxV = 3;

    uint32_t key = (uint32_t)(idxU + (idxV + (int)face * 4) * 4);

    HFind found;
    CellMap* pCells = &mCells;
    pCells->Find(&found, &key);

    if (found.mpNode == pCells->mpBucketArray[pCells->mnBucketCount]) {
        PlanetModel* pModel2 = SP_PlanetModel();
        float water = pModel2->GetWaterHeight();
        float fcU = (float)idxU;
        float fcV = (float)idxV;
        uint32_t cellKey = (uint32_t)idxU + ((uint32_t)idxV + face * 4) * 4;

        TileNode* pNode = pCells->TileAt(&cellKey);

        float u = (fcU + kHalf) * kHalf - kOne;
        float v = (fcV + kHalf) * kHalf - kOne;
        float len = kOne / sqrtf(v * v + u * u + kOne);
        float sl = len;
        if (face & 1)
            sl = -len;
        const uint8_t* ax3 = &g_FaceAxes[(face >> 1) * 4];
        float dir[3];
        dir[ax3[0]] = sl * u;
        dir[ax3[1]] = len * v;
        dir[ax3[2]] = sl;

        float rad = pModel2->GetRadiusAt((Vec3*)dir);
        float r = rad > water ? rad : water;

        float u2 = (fcU * kQuarter) * kTwo - kOne;
        float v2 = (fcV * kQuarter) * kTwo - kOne;
        float len2 = kOne / sqrtf(v2 * v2 + u2 * u2 + kOne);
        float sl2 = len2;
        if (face & 1)
            sl2 = -len2;
        float dir2[3];
        dir2[ax3[0]] = sl2 * u2;
        dir2[ax3[1]] = len2 * v2;
        dir2[ax3[2]] = sl2;

        float other[3];
        pModel2->SnapToSurface((Vec3*)other, (Vec3*)dir2);

        pNode->mPos.x = dir[0] * r;
        pNode->mPos.y = dir[1] * r;
        pNode->mPos.z = dir[2] * r;
        float dx = pNode->mPos.x - other[0];
        float dy = pNode->mPos.y - other[1];
        float dz = pNode->mPos.z - other[2];
        pNode->mDist = sqrtf(dy * dy + (dz * dz + dx * dx));

        pCells->Find(&found, &key);
    }

    if (found.mpNode != pCells->mpBucketArray[pCells->mnBucketCount]) {
        Publication pub;
        pub.mpObj = pNoun;
        if (bFlag == 0) {
            if (pub.mpObj)
                pub.mpObj->AddRef();
            ((PubVector*)((char*)found.mpNode + 0x40))->Push(&pub.mpObj);
        } else {
            if (pub.mpObj)
                pub.mpObj->AddRef();
            ((PubVector*)((char*)found.mpNode + 0x54))->Push(&pub.mpObj);
        }
        if (pub.mpObj)
            pub.mpObj->Release();
    }
}

// @ 0x00acf3e0  cCastingManager::SpawnHerdFromProfile
void cCastingManager::SpawnHerdFromProfile(Vec3* pPos, void* pMgr)
{
    GetActivePlanet();
    cSpeciesArchetype* pArch = FUN_00401090()->GetSpeciesArchetype(0x2615134d, 0);

    const RawVec3* rp = (const RawVec3*)pPos;
    if (rp->x != g_NoPosition.x || rp->y != g_NoPosition.y || rp->z != g_NoPosition.z) {
        void* pProfile = FUN_00401090()->GetProfile((const ResourceKey*)pPos);
        NounObj3* pHerd = ((NounManagerSpawn*)GetNounManager())->CreateNoun(&pPos->x, pProfile, 1, 0, 0, 0);
        if (pHerd) {
            pHerd->Func_c6ace0(1);
            pHerd->mOwnerSpeciesKey = pArch->mSpeciesKey;
            pHerd->mUsedFallback = 0;
            pHerd->UpdateFromArchetype(pArch, 1);
            pHerd->mSpawnTime = g_SpawnTime;
            pHerd->Func_c6b540();
            CastNoun(pHerd, 1);
            GetPollinator()->UpdateProperty(0xef7163ab, pPos);
        }
    }
}
