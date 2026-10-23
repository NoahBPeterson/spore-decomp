// Slice s00bb9950: SPGonzago/SPPlanetModel.obj star / planet record helpers.
// Mixed module: cStarManager star-index helpers, Simulator::cStarRecord methods
// (ctor / dtor / Read / Write / flag accessors), Simulator::cPlanetRecord
// object-list queries, and cSPSimulatorSpaceGame species/effect helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Retail layouts were read off the disassembly.  cStarRecord.confirmed:
//   mLastObservedTime 0x0c, mPosition 0x3c, mType 0x48, mTechLevel 0x4c,
//   field_50 0x50, mEmpireID 0x54, mStarterWorldID 0x58, mFlags 0x5c,
//   mName 0x60 (string16), mKey 0x70, mCitizenSpeciesKey 0x74,
//   mpSpeciesProfile 0x80, mPlanets 0x84 (vector), field_98 0x98 (vector),
//   mPlanetCount 0xac.  size 0xb0.
// cPlanetRecord.confirmed: mFlags 0x2c, mPlanetObjects 0x134 (vector of
//   0x2c-byte cPlanetObjectData, mFlags at +0x28), mKey 0x184, mTechLevel 0x194.

#include "types.h"
#include <stddef.h>

#pragma warning(disable: 4100)

// ---------------------------------------------------------------------------
// container / value stubs (retail sizes)
// ---------------------------------------------------------------------------
struct Vec {              // eastl::vector, 0x14 bytes (empty allocator tail)
    void*    mpBegin;
    void*    mpEnd;
    void*    mpCapacity;
    uint32_t mAllocator0;
    uint32_t mAllocator1;

    void push_back(void* p);            // inline growth; see 0xaea5d0

    void Dtor();                        // 0xae6970
    void Erase(void* first, void* last);// 0xe25bd0
    void Reserve(int n);                // 0xd01790
    void PushBackGrow(void* p);         // 0xaea5d0
};

struct RefObj {
    int  AddRef();                      // vtable[0]
    int  Release();                     // vtable[1]
    void* AsInterface(uint32_t iid);    // vtable[3]
};

struct String16 {         // eastl::basic_string<wchar_t>, 0x10 bytes
    uint32_t mpBegin;
    uint32_t mpEnd;
    uint32_t mpCapacity;
    uint32_t mAllocator;
};

struct Key {              // EA::ResourceMan::Key, 0xc bytes
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

struct PlanetObjectData { // 0x2c bytes
    uint32_t mObjectType;      // 0x00
    float    mObjectPosition[3];// 0x04
    uint16_t mAmmo;            // 0x10
    uint8_t  mArtifactType;    // 0x12
    float    mHealth;          // 0x14
    uint32_t mLootDropTimeS;   // 0x18
    Key      mKey;             // 0x1c
    uint8_t  mFlags;           // 0x28
};

// ---------------------------------------------------------------------------
// callees (address in the comment)
// ---------------------------------------------------------------------------
void*  SP_PropertyManager();                                   // 0x67de30
void*  GetManager();                                           // 0x67dcd0
void*  SP_NounManager();                                       // 0xb3d300
void*  SP_StarManager();                                       // 0xb3d2a0
void*  SP_TerraformingManager();                               // 0xb3d430
void*  FUN_00b3d450();                                         // 0xb3d450
void*  SP_GetMissionManager();                                 // 0xfeb9f0
void*  FUN_0102f810();                                         // 0x102f810 (space economy tuning)
void*  FUN_01021240();                                         // 0x1021240 (player empire id)
void*  FUN_01021230();                                         // 0x1021230 (player star)
void*  FUN_01021090();                                         // 0x1021090 (player empire id)
void*  FUN_01021240b();                                        // unused
void   SP_GenerateNewStarName(void* starRecord);               // 0xc8bff0
void   SP_GetUiName(void* species, void* wstrOut);             // 0x4da330 (thiscall, ret 4)
uint32_t FNV1_String16(const wchar_t* s, uint32_t basis, int one);// 0x932f30
uint32_t SP_GetSetting9();                                     // 0x401090
void   FUN_00f47380(void* p);                                  // operator delete[]

// thiscall callees are declared as member functions of their owning stub
// classes (see Vec, cStarRecord, cStarManager, ...).

void*  SP_StarManager_GetStar(int key);                        // 0xb3d2a0 thiscall-ish

// ---------------------------------------------------------------------------
// forward decls
// ---------------------------------------------------------------------------
class cStarRecord;
class cPlanetRecord;
class cStarManager;

// ---------------------------------------------------------------------------
// cStarRecord
// ---------------------------------------------------------------------------
class cStarRecord {
public:
    // vtable slot helpers
    int  AddRef();                                             // 0xc6a960
    int  Release();                                            // 0x7b86e0
    bool Write(void* outStream);                               // 0xbb9a70
    bool Read(void* inStream);                                 // 0xbba570
    void* AsInterface(uint32_t iid);                           // 0xbb9c70

    cStarRecord();                                             // 0xbba130
    void Dtor();                                               // 0xbba220

    // flag helpers
    String16* EnsureName();                                    // 0xbb9de0
    void SetFlags(uint32_t mask, bool on);                     // 0xbb9b00
    void SetNoMonolith();                                      // 0xbb9b30  (clear 0x4000, set 0x2000)
    bool HasRare();                                            // 0xbb9c90
    void SetBlownUp(bool on);                                  // 0xbb9c40  (bit 0x40)
    bool UpdateSETI();                                         // 0xbb9eb0
    bool HasMonolith();                                        // 0xbb9fb0
    void SetName(const String16* s);                           // 0xbba4b0
    void* GetCitizenSpecies();                                 // 0xbba500
    void OnBan();                                              // 0xbba2a0

    void CachePlanetRecords();                                 // 0xbba640
    Vec* GetPlanetRecords();                                   // 0xbba790
    bool HasActivePlanets(bool checkMission);                  // 0xbba870
    bool HasUndiscoveredPlanets();                             // 0xbba8c0
    bool HasVisitableObject();                                 // 0xbba900
    int  GetStarSystemPurchaseValue();                         // 0xbba990
    void* GetPlanetRecord(int index);                          // 0xbbaa60
    bool IsOwned();                                            // 0xbb9b70 (calls flag query)

    // data (retail offsets)
    uint32_t pad_000;      // 0x00 vftable0
    uint32_t pad_004;      // 0x04 vftable1
    uint32_t pad_008;      // 0x08
    uint32_t mLastObservedTime;        // 0x0c
    uint32_t mSavedGameVersionMajor;   // 0x10
    uint32_t mSavedGameVersionMinor;   // 0x14
    uint32_t mSavedGameTimeStamp[9];   // 0x18 (TimeStamp)
    float    mPosition[3];             // 0x3c
    int32_t  mType;                    // 0x48
    int32_t  mTechLevel;               // 0x4c
    uint8_t  field_50;                 // 0x50
    uint8_t  pad_51[3];                // 0x51
    uint32_t mEmpireID;                // 0x54
    uint32_t mStarterWorldID;          // 0x58
    uint32_t mFlags;                   // 0x5c
    String16 mName;                    // 0x60
    uint32_t mKey;                     // 0x70
    Key      mCitizenSpeciesKey;       // 0x74
    cStarRecord* mpSpeciesProfile_80;  // 0x80 (cSpeciesProfile*)
    Vec      mPlanets;                 // 0x84 (vector<cPlanetRecord*>)
    Vec      field_98;                 // 0x98
    uint8_t  mPlanetCount;             // 0xac
    uint8_t  pad_ad[3];                // 0xad
};

// ---------------------------------------------------------------------------
// cPlanetRecord
// ---------------------------------------------------------------------------
class cPlanetRecord {
public:
    bool HasPlanetObjectFlag_10();      // 0xbb9d40
    void SetFlagA();                    // 0xbb9b50
    bool HasPlanetObjectFlag_09Tech2(); // 0xbb9d90
    bool ProtectFromBio();              // 0xbb9ff0
    int  NeedsBioProtect();             // 0xbba100

    uint32_t pad_000[0x28 / 4];         // 0x00 vftable + name
    int32_t  mType;                     // 0x28
    uint32_t mFlags;                    // 0x2c
    uint32_t pad_030[0x134 / 4 - 0x30 / 4];
    Vec      mPlanetObjects;            // 0x134
    uint32_t pad_148[0x184 / 4 - 0x148 / 4];
    uint32_t mKey;                      // 0x184
    Key      field_188;                 // 0x188
    int32_t  mTechLevel;                // 0x194
};

// ---------------------------------------------------------------------------
// cStarManager
// ---------------------------------------------------------------------------
struct MapStub {              // eastl::map, 0x1c bytes
    uint32_t pad_00;
    void*    mpSentinel_04;   // 0x188 when the map is at 0x184
    uint32_t pad_08[5];
    void find(void* outIt, const void* key);   // 0xe5c780 thiscall ret 8
};

struct MapNode {
    void*    pad_00[3];
    uint32_t pad_0c;
    uint32_t mKey10;          // 0x10
    void*    mValue14;        // 0x14
};

struct InventoryItem {
    uint32_t GetItemInstanceID();  // 0xc87040 -> returns flags byte
};

class cStarManager {
public:
    void*  GetCachedInventoryItem();      // 0xbb9950
    void*  PickBannerForStar(uint32_t key); // 0xbb99e0

    uint32_t pad_000[0xc8 / 4];
    uint32_t mSquadrons_c8;               // 0xc8 begin
    uint32_t mSquadrons_cc;               // 0xcc end
    uint32_t pad_0d0[3];
    InventoryItem** mItems_dc;            // 0xdc
    InventoryItem** mItems_e0;            // 0xe0
    uint32_t pad_0e4[(0x184 - 0xe4) / 4];
    MapStub  mMap_184;                    // 0x184
    uint32_t pad_1a0[(0x1dc - 0x1a0) / 4];
    void*    mpCached_1dc;                // 0x1dc
};

// ---------------------------------------------------------------------------
// cSPSimulatorSpaceGame
// ---------------------------------------------------------------------------
class cSPSimulatorSpaceGame {
public:
    uint32_t pad_000[0x4c / 4];
    int32_t  mCurrentShoppingModelType;   // 0x4c
    uint32_t pad_050[8];                  // 0x50..0x70
    Key      mCitizenSpeciesKey;          // 0x70
    uint8_t  mIsCapturingImpostor;        // 0x7c
    uint8_t  mImpostorCaptured;           // 0x7d
    uint16_t field_7e;                    // 0x7e
    void*    mpSpeciesProfile_80;         // 0x80  (cSpeciesProfile*)
    uint32_t pad_084[2];
    void*    mpHighLODPlanetSim;          // 0x8c
    uint32_t pad_090[2];
    void*    mpSpaceMusicEffect;          // 0x98
};

// ---------------------------------------------------------------------------
// helper: property manager interface (7-card trick: typed stub with the
// target virtual at the right slot).
// ---------------------------------------------------------------------------
struct IPropertyManager {
    virtual void pad00();  virtual void pad04();  virtual void pad08();
    virtual void pad0c();  virtual void pad10();  virtual void pad14();
    virtual void pad18();  virtual void pad1c();  virtual void pad20();
    virtual void pad24();  virtual void pad28();
    virtual bool GetProperty(uint32_t key, uint32_t hash, void* outPtr);
};

struct IProperty {
    virtual void pad00();  virtual void pad04();  virtual void pad08();
    virtual void pad0c();  virtual void pad10();  virtual void pad14();
    virtual void pad18();  virtual void pad1c();  virtual void pad20();
    virtual bool GetValue(uint32_t hash, void* outPtr);
};

struct IResourceManager {
    virtual void pad00();  virtual void pad04();  virtual void pad08();
    virtual void Create(const uint32_t* key, void** out,
                        uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // slot 3
};

struct ISpeciesManager {
    void* GetProfile(const Key* key);   // 0x4df550 thiscall ret 4
};

struct IStarMgr {
    void* GetBelongingStar(int key);    // 0xb3d2a0-ish
};

// random source
struct RndSource {
    double NextF();                     // 0x9360d0 thiscall
};
extern RndSource gRandom;               // 0x01601760

// ---------------------------------------------------------------------------
// The byte at +0x28 of a cPlanetObjectData is its mFlags; helper to read it.
// ---------------------------------------------------------------------------
static inline PlanetObjectData* objectAt(uint8_t* base, int i)
{
    return (PlanetObjectData*)(base + i * sizeof(PlanetObjectData));
}

// ===========================================================================
// @ 0x00bb9950
// ===========================================================================
void* cStarManager::GetCachedInventoryItem()
{
    if (mpCached_1dc != 0)
        return mpCached_1dc;

    int n = (int)(mSquadrons_cc - mSquadrons_c8) / 0x14;
    if (n == 0) {
        // LoadStarDatabase is a thiscall member of cStarManager at 0xbb8b20
        ((void(__thiscall*)(cStarManager*))0xbb8b20)(this);
    }

    // 0xbb6040(this)
    ((void(__thiscall*)(cStarManager*))0xbb6040)(this);

    int count = (int)((char*)mItems_e0 - (char*)mItems_dc) >> 2;
    for (int i = 0; i < count; ++i) {
        if (!(mItems_dc[i]->GetItemInstanceID() & 2))
            return mItems_dc[i];
    }
    return 0;
}

// ===========================================================================
// @ 0x00bb99e0
// ===========================================================================
void* cStarManager::PickBannerForStar(uint32_t key)
{
    void* ctx = ((void*(__thiscall*)(uint32_t))0xce6950)(key);  // cStarRecordRef::GetCommContext
    void* it = 0;
    mMap_184.find(&it, &ctx);
    MapNode* node = (MapNode*)it;
    if (node == (MapNode*)&mMap_184.mpSentinel_04)
        return 0;

    void* old = node->mValue14;
    // PickRandomAsset(this, &node->mValue14, 0)
    ((void(__thiscall*)(cStarManager*, void*, int))0xbb7940)(this, &node->mValue14, 0);
    if (node->mValue14 != old) {
        // 0xba6dc0(this, node->mKey10)
        uint32_t r = ((uint32_t(__thiscall*)(cStarManager*, uint32_t))0xba6dc0)(this, node->mKey10);
        void* mm = SP_GetMissionManager();
        void* r2 = ((void*(__thiscall*)(void*, uint32_t))0xfee220)(mm, r);
        if (r2 != 0)
            ((void(__thiscall*)(void*, void*))0xc4b240)(r2, node->mValue14);
    }
    return node->mValue14;
}

// ===========================================================================
// @ 0x00bb9a70
// ===========================================================================
bool cStarRecord::Write(void* outStream)
{
    // cVarListSerializer on the stack (0xa14 bytes local)
    char ser[0xa14];
    *(uint32_t*)((char*)this + 0x80) = 0;
    ((void(__thiscall*)(void*, cStarRecord*, uint32_t, uint32_t))0x692f90)(ser, this, 0x156cb70, 0x1a80d26);
    return ((bool(__thiscall*)(void*, void*))0x692900)(ser, outStream);
}

// ===========================================================================
// @ 0x00bb9b00
// ===========================================================================
void cStarRecord::SetFlags(uint32_t mask, bool on)
{
    if (on)
        mFlags |= mask;
    else
        mFlags &= ~mask;
}

// ===========================================================================
// @ 0x00bb9b30
// ===========================================================================
void cStarRecord::SetNoMonolith()
{
    mFlags = (mFlags & 0xffffbfff) | 0x2000;
}

// ===========================================================================
// @ 0x00bb9b50
// ===========================================================================
void cPlanetRecord::SetFlagA()
{
    mFlags = (mFlags & 0xffff7fff) | 0x4000;
}

// ===========================================================================
// @ 0x00bb9b70
// ===========================================================================
int FUN_00b8dab0();                        // 0xb8dab0

bool FUN_00c8b520(int32_t starType);       // 0xc8b520

bool FUN_00b8d970(void* planetRecord);     // 0xb8d970
bool FUN_00b8d9b0(void* planetRecord);     // 0xb8d9b0
bool FUN_00b8d9f0(void* planetRecord);     // 0xb8d9f0

bool StarRecord_IsOwnedByPlayer()
{
    bool owned = FUN_00b8dab0() == 5;
    return owned;
}

// ===========================================================================
// @ 0x00bb9c40
// ===========================================================================
void cStarRecord::SetBlownUp(bool on)
{
    mFlags = (mFlags & 0xffffffbf) | ((on ? 0x40u : 0u));
}

// ===========================================================================
// @ 0x00bb9c90
// ===========================================================================
bool cStarRecord::HasRare()
{
    if (mPlanetCount == 0) {
        if (FUN_00c8b520(mType) && ((mFlags >> 6) & 1) == 0)
            return false;
    }
    return true;
}

// ===========================================================================
// @ 0x00bb9cd0  attribute read helper (cdecl, bool)
// ===========================================================================
bool AttrRead_00bb9cd0(void* pStream, uint8_t* pData)
{
    int* a = (int*)(*(int(__thiscall**)(void*))(*(uint32_t**)pStream + 0x20 / 4))(pStream);
    uint32_t v = (*(uint32_t(__thiscall**)(int*))(*(uint32_t**)a + 0x18 / 4))(a);
    return ((bool(__cdecl*)(uint32_t, uint8_t*, int))0x93a6c0)(v, pData, 1) ? true : false;
}

// ===========================================================================
// @ 0x00bb9d00  attribute write helper (cdecl, bool)
// ===========================================================================
bool AttrWrite_00bb9d00(void* pStream, uint8_t* pData)
{
    uint8_t tmp = *pData;
    int* a = (int*)(*(int(__thiscall**)(void*))(*(uint32_t**)pStream + 0x20 / 4))(pStream);
    uint32_t v = (*(uint32_t(__thiscall**)(int*))(*(uint32_t**)a + 0x18 / 4))(a);
    return ((bool(__cdecl*)(uint32_t, uint8_t*, int))0x93a9a0)(v, &tmp, 1);
}

// ===========================================================================
// @ 0x00bb9d40
// ===========================================================================
bool cPlanetRecord::HasPlanetObjectFlag_10()
{
    int count = (int)((char*)mPlanetObjects.mpEnd - (char*)mPlanetObjects.mpBegin)
              / (int)sizeof(PlanetObjectData);
    PlanetObjectData* p = (PlanetObjectData*)mPlanetObjects.mpBegin;
    for (int i = 0; i < count; ++i, ++p) {
        if (p->mFlags & 0x10)
            return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00bb9d90
// ===========================================================================
bool cPlanetRecord::HasPlanetObjectFlag_09Tech2()
{
    int count = (int)((char*)mPlanetObjects.mpEnd - (char*)mPlanetObjects.mpBegin)
              / (int)sizeof(PlanetObjectData);
    PlanetObjectData* p = (PlanetObjectData*)mPlanetObjects.mpBegin;
    for (int i = 0; i < count; ++i, ++p) {
        if ((p->mFlags & 9) != 0 && p->mArtifactType == 2)
            return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00bb9de0
// ===========================================================================
String16* cStarRecord::EnsureName()
{
    if (mName.mpBegin == mName.mpEnd)
        SP_GenerateNewStarName(this);
    return &mName;
}

// ===========================================================================
// @ 0x00bb9e00
// ===========================================================================
uint32_t StarRecord_GetTerrainScript(uint32_t key)
{
    uint32_t result = 0;
    IPropertyManager* pm = (IPropertyManager*)SP_PropertyManager();
    int* holder = 0;
    if (holder != 0) {
        // release pattern kept for shape
    }
    bool ok = pm->GetProperty(key, 0xe38475d9, &holder);
    if (ok) {
        uint32_t hash = FNV1_String16(L"terrainScript", 0x811c9dc5, 1);
        if (holder != 0) {
            IProperty* prop = 0;
            if (((IProperty*)holder)->GetValue(hash, &prop) && *(uint16_t*)((char*)prop + 0x12) == 0xa) {
                result = *(uint32_t*)((uint32_t(__thiscall*)(IProperty*))0x41ea00)(prop);
            }
        }
    }
    return result;
}

// ===========================================================================
// @ 0x00bb9eb0
// ===========================================================================
bool cStarRecord::UpdateSETI()
{
    if ((mFlags & 0x6000) != 0)
        return (mFlags >> 13) & 1;

    bool ok = true;
    if ((mFlags & 0x30) != 0)
        goto setflag;

    if (!FUN_00c8b520(mType))
        goto setflag;

    if (mEmpireID == (uint32_t)(uintptr_t)FUN_01021090())
        goto setflag;

    {
        uint32_t result = 0;
        IPropertyManager* pm = (IPropertyManager*)SP_PropertyManager();
        void* holder = 0;
        pm->GetProperty(*(uint32_t*)0x1689fe0, 0x30608f0b, &holder);
        if (holder != 0) {
            float v = 0.0f;
            uint32_t hash = (mTechLevel == 5) ? 0x5b07986u : 0x5b07984u;
            ((void(__cdecl*)(void*, uint32_t, float*))0x40cf10)(holder, hash, &v);
            double r = gRandom.NextF();
            if (!((double)v <= r)) {
                mFlags |= 0x4000;
                ok = false;
            }
            ((void(__thiscall*)(void*))(*(uint32_t**)holder)[1])(holder);
            if (!ok)
                return (mFlags >> 13) & 1;
        }
    }

setflag:
    mFlags |= 0x2000;
    return (mFlags >> 13) & 1;
}

// ===========================================================================
// @ 0x00bb9fb0
// ===========================================================================
bool cStarRecord::HasMonolith()
{
    bool t = (mTechLevel == 5);
    if (((mFlags >> 4) & 1) == 0) {
        bool r = UpdateSETI() ? t : !t;
        if (r)
            return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00bb9ff0
// ===========================================================================
bool cPlanetRecord::ProtectFromBio()
{
    if ((mFlags & 0xc000) != 0)
        return (mFlags >> 14) & 1;

    IPropertyManager* pm = (IPropertyManager*)SP_PropertyManager();
    void* holder = 0;
    pm->GetProperty(*(uint32_t*)0x1689fe0, 0x30608f0b, &holder);

    if (holder == 0) {
        goto setflag;
    }

    if (HasPlanetObjectFlag_10()) {
        {
            float v = 0.0f;
            ((void(__cdecl*)(void*, uint32_t, float*))0x40cf10)(holder, 0x5b07982u, &v);
            double r = gRandom.NextF();
            if (!((double)v <= r))
                mFlags |= 0x8000;
        }
    } else {
        void* other = ((void*(__thiscall*)(cPlanetRecord*))0xb8de30)(this);
        if (*(int32_t*)((char*)other + 0x4c) != 5 && mTechLevel == 1) {
            void* nm = SP_NounManager();
            void* sphere = ((void*(__thiscall*)(void*))0xf67d90)(nm);
            if (((bool(__thiscall*)(void*, uint32_t))0xc772c0)(sphere, 0x4ac800c)) {
                float v = 0.0f;
                ((void(__cdecl*)(void*, uint32_t, float*))0x40cf10)(holder, 0x5b0797fu, &v);
                double r = gRandom.NextF();
                if (!((double)v <= r))
                    mFlags |= 0x8000;
            }
        }
    }
    goto release;
setflag:
    mFlags |= 0x4000;
release:
    if (holder != 0)
        ((void(__thiscall*)(void*))(*(uint32_t**)holder)[1])(holder);
    return (mFlags >> 14) & 1;
}

// ===========================================================================
// @ 0x00bba100
// ===========================================================================
int cPlanetRecord::NeedsBioProtect()
{
    bool a = HasPlanetObjectFlag_10();
    if (ProtectFromBio())
        return a;
    return !a;
}

// ===========================================================================
// @ 0x00bba130  Simulator::cStarRecord::cStarRecord
// ===========================================================================
cStarRecord::cStarRecord()
{
    *(uint32_t*)((char*)this + 0x04) = 0x13ec458;
    *(uint32_t*)((char*)this + 0x08) = 0;
    *(uint32_t*)((char*)this + 0x00) = 0x14664c8;
    *(uint32_t*)((char*)this + 0x04) = 0x14664b8;
    mLastObservedTime = 0;
    mPosition[0] = *(float*)0x1689ec8;
    mPosition[1] = *(float*)0x1689ecc;
    mPosition[2] = *(float*)0x1689ed0;
    mType = 0;
    mTechLevel = 0;
    field_50 = 0;
    mEmpireID = 0xffffffff;
    mStarterWorldID = 0;
    mFlags = 0;
    *(uint32_t*)((char*)this + 0x68) = 0x1667bae;
    *(uint32_t*)((char*)this + 0x60) = 0x1667bac;
    *(uint32_t*)((char*)this + 0x64) = 0x1667bac;
    *(uint32_t*)((char*)this + 0x74) = 0;
    *(uint32_t*)((char*)this + 0x78) = 0;
    *(uint32_t*)((char*)this + 0x7c) = 0;
    *(uint32_t*)((char*)this + 0x80) = 0;
    mPlanets.mpBegin = 0;
    mPlanets.mpEnd = 0;
    mPlanets.mpCapacity = 0;
    *(uint32_t*)((char*)this + 0x8c) = 0;
    field_98.mpBegin = 0;
    field_98.mpEnd = 0;
    field_98.mpCapacity = 0;
    mPlanetCount = 0;
}

// ===========================================================================
// @ 0x00bba220
// ===========================================================================
void cStarRecord::Dtor()
{
    *(uint32_t*)((char*)this + 0x00) = 0x14664c8;
    *(uint32_t*)((char*)this + 0x04) = 0x14664b8;
    field_98.Dtor();
    mPlanets.Dtor();
    int n = (int)(mName.mpCapacity - mName.mpBegin) & (int)0xfffffffe;
    if (n > 2 && mName.mpBegin != 0)
        FUN_00f47380((void*)mName.mpBegin);
    *(uint32_t*)((char*)this + 0x04) = 0x13ec458;
    *(uint32_t*)((char*)this + 0x00) = 0x13eb938;
}

// ===========================================================================
// @ 0x00bba2a0
// ===========================================================================
void cStarRecord::OnBan()
{
    int mode = mTechLevel - 2;
    uint32_t key = 0;
    void* empire = 0;
    if (mode == 0) {
        key = 0x876201aa;
    } else if (mode == 2) {
        key = 0xefc33700;
    } else if (mode == 3) {
        void* sm = ((void*(__cdecl*)(uint32_t))0xb3d2a0)(mEmpireID);
        empire = ((void*(__thiscall*)(void*))0xba9370)(sm);
        key = 0xfc5a17bc;
    } else {
        mCitizenSpeciesKey.instanceID = 0;
        mCitizenSpeciesKey.typeID = 0;
        mCitizenSpeciesKey.groupID = 0;
        mpSpeciesProfile_80 = 0;
        return;
    }

    int count = 0x64;
    uint32_t ki = 0;
    uint32_t kj = 0;
    uint32_t kk = 0;
    void* node = 0;
    ((void*(*)())0xb3d450);            // keep source shape
    uint32_t mgr = ((uint32_t(*)())0xb3d450)();

    for (;;) {
        if (ki != 0) {
            if (ki != mCitizenSpeciesKey.instanceID) break;
            if (kj != mCitizenSpeciesKey.typeID) break;
            if (kk != mCitizenSpeciesKey.groupID) break;
        }
        if (--count < 0) break;

        void* species;
        if (node != 0)
            species = ((void*(__cdecl*)(uint32_t))0xac1190)(*(uint32_t*)((char*)node + 0x58));
        else
            species = ((void*(__cdecl*)(void*))0xac10a0)(empire);
        if (species == 0) break;

        String16 name;
        name.mpBegin = 0x1667bac;
        name.mpEnd = 0x1667bac;
        name.mpCapacity = 0x1667bae;
        ((void(__thiscall*)(void*, String16*))0x4da330)(species, &name);

        void* sm = ((void*(__cdecl*)(void*))0xb3d2a0)(&name);
        if (!((bool(__thiscall*)(void*, String16*))0xbaf5d0)(sm, &name)) {
            void* sm2 = ((void*(__cdecl*)(void*))0xb3d2a0)(&name);
            ((void(__thiscall*)(void*, String16*))0xbb5b50)(sm2, &name);
            kk = *(uint32_t*)((char*)species + 0x50c);
            ki = *(uint32_t*)((char*)species + 0x504);
            kj = *(uint32_t*)((char*)species + 0x508);
        }
        int len = (int)(name.mpEnd - name.mpBegin) & 0xfffffffe;
        if (len <= 2) continue;
        if (name.mpBegin == 0) continue;
        FUN_00f47380((void*)name.mpBegin);
    }

    if (ki != 0 && (ki != mCitizenSpeciesKey.instanceID || kj != mCitizenSpeciesKey.typeID
                    || kk != mCitizenSpeciesKey.groupID)) {
        if (node == 0) {
            mCitizenSpeciesKey.instanceID = 0;
            mCitizenSpeciesKey.typeID = 0;
            mCitizenSpeciesKey.groupID = 0;
            mpSpeciesProfile_80 = 0;
            return;
        }
    } else {
        void* species;
        if (node != 0)
            species = ((void*(__cdecl*)(uint32_t))0xac1190)(*(uint32_t*)((char*)node + 0x58));
        else
            species = ((void*(__cdecl*)(void*))0xac10a0)(empire);
        if (species == 0) {
            mCitizenSpeciesKey.typeID = 0;
            mCitizenSpeciesKey.groupID = 0;
            mCitizenSpeciesKey.instanceID = 0;
            mpSpeciesProfile_80 = 0;
            return;
        }
        ki = *(uint32_t*)((char*)species + 0x504);
        kj = *(uint32_t*)((char*)species + 0x508);
        kk = *(uint32_t*)((char*)species + 0x50c);
        node = species;
    }

    bool tech5 = (mTechLevel == 5);
    mCitizenSpeciesKey.instanceID = ki;
    mCitizenSpeciesKey.typeID = kj;
    mCitizenSpeciesKey.groupID = kk;
    mpSpeciesProfile_80 = (cStarRecord*)node;
    (void)tech5; (void)key;
    if (tech5 && empire != 0)
        ((void(__thiscall*)(void*, void*))0xc33690)(empire, node);
}

// ===========================================================================
// @ 0x00bba4b0
// ===========================================================================
void cStarRecord::SetName(const String16* s)
{
    if (s->mpBegin != s->mpEnd) {
        if (this == (cStarRecord*)FUN_01021240()) {
            cStarRecord* star = (cStarRecord*)FUN_01021230();
            if (star != 0) {
                void* solar = ((void*(__thiscall*)(void*))0xc8b770)(star);
                if (solar != 0)
                    ((void(__thiscall*)(void*, const String16*))0xc85200)(solar, s);
            }
        }
        if (s != &mName)
            ((void(__thiscall*)(String16*, uint32_t, uint32_t))0x423650)(&mName, s->mpBegin, s->mpEnd);
    }
}

// ===========================================================================
// @ 0x00bba500
// ===========================================================================
void* cStarRecord::GetCitizenSpecies()
{
    if (mCitizenSpeciesKey.instanceID == 0) {
        if (mTechLevel > 1)
            OnBan();
        return mpSpeciesProfile_80;
    }
    void* prof = mpSpeciesProfile_80;
    if (prof == 0 || *(uint32_t*)((char*)prof + 0x504) != mCitizenSpeciesKey.instanceID) {
        ISpeciesManager* sm = (ISpeciesManager*)SP_GetSetting9();
        prof = sm->GetProfile(&mCitizenSpeciesKey);
        mpSpeciesProfile_80 = (cStarRecord*)prof;
        if (prof == 0) {
            OnBan();
            return mpSpeciesProfile_80;
        }
    }
    return prof;
}

// ===========================================================================
// @ 0x00bba570
// ===========================================================================
bool cStarRecord::Read(void* inStream)
{
    char ser[0xa14];
    ((void(__thiscall*)(void*, cStarRecord*, uint32_t, uint32_t))0x692f90)(ser, this, 0x156cb70, 0x1a80d26);
    bool ok = ((bool(__thiscall*)(void*, void*))0x693e10)(ser, inStream);
    mpSpeciesProfile_80 = 0;
    ISpeciesManager* sm = (ISpeciesManager*)SP_GetSetting9();
    if (sm->GetProfile(&mCitizenSpeciesKey) == 0)
        field_50 = 1;
    if (mName.mpBegin == mName.mpEnd)
        SP_GenerateNewStarName(this);
    const wchar_t* empty = (const wchar_t*)0x151ac94;
    {
        const wchar_t* a = (const wchar_t*)mName.mpBegin;
        while (*a == *empty) {
            if (*a == 0) { a = 0; break; }
            ++a; ++empty;
            if (*a == 0) { a = 0; break; }
        }
        if (a != 0)
            SP_GenerateNewStarName(this);
    }
    if (mName.mpBegin == mName.mpEnd)
        SP_GenerateNewStarName(this);
    SetName(&mName);
    return ok;
}

// ===========================================================================
// @ 0x00bba640
// ===========================================================================
void cStarRecord::CachePlanetRecords()
{
    int count = (int)((char*)mPlanets.mpEnd - (char*)mPlanets.mpBegin) >> 2;
    if (count == mPlanetCount)
        return;

    mPlanets.Erase(mPlanets.mpBegin, mPlanets.mpEnd);
    if (mPlanetCount == 0)
        return;

    uint32_t offset = 0;
    for (int i = 0; i < mPlanetCount; ++i) {
        uint32_t starKey = mKey + offset;

        RefObj* held = 0;
        {
            IResourceManager* rm = (IResourceManager*)GetManager();
            uint32_t key[3];
            key[0] = starKey;
            key[1] = 0x5220cb8;
            key[2] = 1;
            rm->Create(key, (void**)&held, 0, 0, 0, 0);
        }
        RefObj* pr = 0;
        if (held != 0)
            pr = (RefObj*)held->AsInterface(0x3e434e1);
        if (pr != 0)
            pr->AddRef();

        if (mPlanets.mpEnd < mPlanets.mpCapacity) {
            *(void**)mPlanets.mpEnd = pr;
            mPlanets.mpEnd = (char*)mPlanets.mpEnd + 4;
            if (pr != 0)
                pr->AddRef();
        } else {
            mPlanets.PushBackGrow(&pr);
        }

        if (pr != 0)
            pr->Release();
        if (held != 0)
            held->Release();
        offset += 0x1000000;
    }
}

// ===========================================================================
// @ 0x00bba790
// ===========================================================================
Vec* cStarRecord::GetPlanetRecords()
{
    CachePlanetRecords();
    if (((mFlags >> 6) & 1) == 0)
        return &mPlanets;

    field_98.Erase(field_98.mpBegin, field_98.mpEnd);
    int n = (int)((char*)mPlanets.mpEnd - (char*)mPlanets.mpBegin) >> 2;
    field_98.Reserve(n);
    for (int i = 0; i < n; ++i) {
        cPlanetRecord* pr = ((cPlanetRecord**)mPlanets.mpBegin)[i];
        if (!((bool(__thiscall*)(void*))0xb8d970)(pr)) {
            if (field_98.mpEnd < field_98.mpCapacity) {
                *(void**)field_98.mpEnd = pr;
                field_98.mpEnd = (char*)field_98.mpEnd + 4;
                if (pr != 0)
                    ((RefObj*)pr)->AddRef();
            } else {
                field_98.PushBackGrow(&pr);
            }
        }
    }
    return &field_98;
}

// ===========================================================================
// @ 0x00bba870
// ===========================================================================
bool cStarRecord::HasActivePlanets(bool checkMission)
{
    Vec* v = (Vec*)GetPlanetRecords();
    void** begin = (void**)v->mpBegin;
    void** end = (void**)v->mpEnd;
    for (; begin != end; ++begin) {
        cPlanetRecord* pr = (cPlanetRecord*)*begin;
        if (((bool(__thiscall*)(void*))0xb8d9b0)(pr)) {
            if (checkMission) {
                void* mm = SP_GetMissionManager();
                if (((void*(__thiscall*)(void*, cPlanetRecord*))0xfee220)(mm, pr) != 0)
                    return false;
            }
            return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00bba8c0
// ===========================================================================
bool cStarRecord::HasUndiscoveredPlanets()
{
    if (((mFlags >> 3) & 1) != 0)
        return false;
    Vec* v = (Vec*)GetPlanetRecords();
    void** begin = (void**)v->mpBegin;
    void** end = (void**)v->mpEnd;
    for (; begin != end; ++begin) {
        if (((bool(__thiscall*)(void*))0xb8d9f0)(*begin))
            return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00bba900
// ===========================================================================
bool cStarRecord::HasVisitableObject()
{
    if (mPlanetCount == 0)
        return (mFlags >> 12) & 1;

    Vec* v = (Vec*)GetPlanetRecords();
    cPlanetRecord** begin = (cPlanetRecord**)v->mpBegin;
    int n = (int)((char*)v->mpEnd - (char*)v->mpBegin) >> 2;
    for (int i = 0; i < n; ++i) {
        if (begin[i]->HasPlanetObjectFlag_10())
            return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00bba990
// ===========================================================================
int cStarRecord::GetStarSystemPurchaseValue()
{
    Vec* v = (Vec*)GetPlanetRecords();
    void* tf = SP_TerraformingManager();
    int total = 0;
    int turrets = 0;
    int buildings = 0;
    int n = (int)((char*)v->mpEnd - (char*)v->mpBegin) >> 2;
    for (int i = 0; i < n; ++i) {
        cPlanetRecord* pr = ((cPlanetRecord**)v->mpBegin)[i];
        int t = pr->mFlags;
        if (t == 1 || t == 0)
            continue;
        if (((bool(__thiscall*)(void*))0xb8d970)(pr))
            continue;
        void* tm = SP_TerraformingManager();
        void* val = ((void*(__thiscall*)(void*, cPlanetRecord*))0xbbc670)(tm, pr);
        void* econ = FUN_0102f810();
        total += ((int(__thiscall*)(void*, void*))0x1030000)(econ, val);
        ((void(__cdecl*)(cPlanetRecord*, int*, int*))0xc70380)(pr, &turrets, &buildings);
    }
    void* et = FUN_0102f810();
    (void)et;
    void* et2 = FUN_0102f810();
    float f1 = ((float(__thiscall*)(void*))0x10300c0)(et2);
    float acc = (float)turrets * f1;
    void* et3 = FUN_0102f810();
    float f2 = ((float(__thiscall*)(void*))0x1030070)(et3);
    acc = (float)total + (float)buildings * f2 + acc;
    return (int)acc;
}

// ===========================================================================
// @ 0x00bbaa60
// ===========================================================================
void* cStarRecord::GetPlanetRecord(int index)
{
    CachePlanetRecords();
    return ((void**)mPlanets.mpBegin)[index];
}
