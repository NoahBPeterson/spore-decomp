// Slice s00cc5fe0: SP::cNpcTribeController::DoTribeGrowthSim (0x00cc62c0, 1603 bytes).
// /O2 /arch:SSE module (movss/comiss for plain floats, x87 for the float returns of vcalls/GetPropertyT).
//
// The NPC tribe growth step: when the planet's property list says enough tribe slots are defined for the
// number of existing tribes, pick the nearest herd-type noun (0x36be27e) to the player's tribe, spawn a
// new tribe there (CreateTribe), set its growth parameters from the property list, and remove or
// reassign every nearby herd noun (0x1be418e) depending on how far it is from the new tribe.
#include "types.h"

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- game object stubs
// A spatial subobject (own vtable).
class cSpatial
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual const Vec3* GetPosition();          // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetFloat74();                 // +0x74 (the 0x4000000 pushed before it is b81020's third arg)
};

// Object holding a spatial subobject at +0x34 (returned by the tribe's vtable slot +0xac).
class cSubObj
{
public:
    char pad0[0x34];
    cSpatial mSpatial;                          // +0x34
};

// SP::cTribe (type 0x18c6d19).
class cTribe
{
public:
    virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
    virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
    virtual void t08(); virtual void t09(); virtual void t10(); virtual void t11();
    virtual void t12(); virtual void t13(); virtual void t14(); virtual void t15();
    virtual void t16(); virtual void t17(); virtual void t18(); virtual void t19();
    virtual void t20(); virtual void t21(); virtual void t22(); virtual void t23();
    virtual float GetRadius();                  // +0x60
    virtual void t25(); virtual void t26(); virtual void t27(); virtual void t28(); virtual void t29();
    virtual void t30(); virtual void t31(); virtual void t32(); virtual void t33(); virtual void t34();
    virtual void t35(); virtual void t36(); virtual void t37(); virtual void t38(); virtual void t39();
    virtual void t40(); virtual void t41(); virtual void t42();
    virtual cSubObj* GetModel();                // +0xac

    char pad4[0x120 - 4];
    cSpatial mSpatial;                          // +0x120
    char pad124[0x260 - 0x124];
    cSubObj* mpLinked;                          // +0x260
    char pad264[0x2c4 - 0x264];
    float mGrowthParam;                         // +0x2c4

    void* GetToolOfType(int type);              // 0x00c8f6e0 (ret 4)
    uint32_t GetSlot0();                        // 0x00c8e820 (ret 4): [this + 0x18cc]
    bool FUN_00c8e850();                        // 0x00c8e850
    bool FUN_00c8e870();                        // 0x00c8e870
    void FUN_00c8e820(int x);                   // 0x00c8e820 (ret 4)
};

// herd noun (type 0x36be27e): +0x34 spatial, +0x108 kind, +0x11c terraform id
class cHerdNoun
{
public:
    char pad0[0x34];
    cSpatial mSpatial;                          // +0x34
    char pad38[0x108 - 0x38];
    uint32_t mKind;                             // +0x108
    char pad10c[0x11c - 0x10c];
    uint32_t mTerraformId;                      // +0x11c
};

// noun (type 0x1be418e): virtual +0x2c is a bool query; FUN_00c6acc0 gives its position
class cNearNoun
{
public:
    virtual void n00(); virtual void n01(); virtual void n02(); virtual void n03();
    virtual void n04(); virtual void n05(); virtual void n06(); virtual void n07();
    virtual void n08(); virtual void n09(); virtual void n10();
    virtual bool IsExcluded();                  // +0x2c
    const Vec3* GetPosition();                  // 0x00c6acc0
};

struct PtrVector
{
    void** mpBegin; void** mpEnd; void** mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct GameDataVector { uint32_t pad0; PtrVector mVector; };
void FUN_00cd7d10(); void FUN_00d3d420(); void FUN_00accbb0(); void FUN_00b1e500();
void FUN_00ace070(); void FUN_00accc30();
typedef void (*GameDataFn)();

struct cTerrainSphere;
class cGameNounManager
{
public:
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                      uint32_t type);   // 0x00b21340 (ret 0x14)
    cTribe* GetPlayerTribe();                           // 0x00bfc5f0
    void RemoveNoun(void* noun);                        // 0x00b225d0 (ret 4)
    cTerrainSphere* GetCurrentTerrainSphere();          // 0x00f67d90
};
cGameNounManager* NounManager();                        // 0x00b3d300

class cPropertyList;
bool GetPropertyAsUint32Array(cPropertyList* l, uint32_t id, int* pCount, uint32_t** ppData);  // 0x006a0840
float GetPropertyFloat(cPropertyList* l, uint32_t id, float def);   // 0x004e1c70 SP::GetPropertyT<float>
extern cPropertyList* g_pGameProps;                     // 0x01581288

struct cSettings { void* GetAvatarProfile(); };         // 0x004df420 (thiscall, no args)
cSettings* GetSetting9();                               // 0x00401090

// interface at 0x15d0c04 (FUN_00401010 returns it)
struct cResourceDB
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Has(void* res, int flag);              // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual bool IsPending(void* res);                  // +0x3c
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual void Request(void* res, const void* key);   // +0x4c
};
cResourceDB* FUN_00401010();

struct cObjectTemplateDB
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual void Release(void* res, int flag);          // +0x58
};
cObjectTemplateDB* ObjectTemplateDB();                  // 0x0067cb40

// FUN_00c8ea70(n): record in a 0xb8-byte-per-entry table; first two dwords used here
uint32_t* FUN_00c8ea70(uint32_t n);

// FUN_0104c100 on the global object at 0x1581208 returns its field +0x178
struct cG1581208 { uint32_t GetDefault(); };
extern cG1581208 g_1581208;

// tribe creation
cTribe* CreateTribe(const Vec3* pos, uint32_t a, uint32_t b, uint32_t c, uint32_t d, void* e);   // 0x00c93160
void ValidateHerdLocationsForTribe(cTribe* t);          // 0x00cc5850
void FUN_00cd4770(cNearNoun* n, cTribe* t);             // cdecl

struct cTribeModeStrategy
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual void SetTribe(cTribe* t);                   // +0x54 (ret 4)
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26();
    virtual struct cTribeUI* GetUI();                   // +0x6c
};
cTribeModeStrategy* TribeModeStrategyInstance();        // 0x00cd40b0

struct cTribeUI { void SetVisible(bool v); };           // 0x00cc93b0 (ret 4)

struct cEventLog
{
    void PostFeedbackEvent(uint32_t a, uint32_t b, const Vec3* pos, int c, int d, int e);   // 0x00dd8640 (ret 0x18)
};
cEventLog* EventLog();                                  // 0x00b3d3e0

// FUN_00ad7a30 / FUN_00ad7ad0
struct ActionTargetArg
{
    uint32_t data[12];
    ActionTargetArg(void* obj);                           // 0x00ad7a30 (ret 4)
    ~ActionTargetArg();                                   // 0x00ad7ad0
};

// 0x167eb50 global getter FUN_00b3d4d0
struct cTriggerMgr
{
    void PostAction(uint32_t id, const ActionTargetArg& t, int flag);                       // 0x00ae09b0 (ret 0xc)
    void PostTrigger(const char* name, int a, int b, int c, int d, int e);                // 0x00ae0930 (ret 0x18)
};
cTriggerMgr* FUN_00b3d4d0();

struct cSList
{
    void SetField18(uint32_t v);                        // 0x00fcc200 (ret 4)
};
extern cSList* g_pSList;                                // 0x0169b41c

struct cTerraformingMgr { void Apply(uint32_t id); };   // 0x00bbec60 (ret 4)
cTerraformingMgr* TerraformingManager();                // 0x00b3d430

struct cPlanetModel
{
    void FUN_00b83c40(const Vec3* pos, float f, uint32_t flags, int z);   // ret 0x10
    void FUN_00b81020(const Vec3* pos, float f, uint32_t flags);          // ret 0xc
};
cPlanetModel* PlanetModel();                            // 0x00b3d350

extern float g_fTribeScale;                             // 0x0157e940

struct ResKey { uint32_t id; uint16_t a; uint16_t b; };

template <class T> inline const T& min_ref(const T& a, const T& b) { return (b < a) ? b : a; }

// Retail layout of the controller (the 2008 PDB class is smaller): only the used fields.
class cNpcTribeController
{
public:
    char pad0[0xd0];
    char** mpTribeObjsBegin;                            // +0xd0
    char** mpTribeObjsEnd;                              // +0xd4
    char padd8[0xfc - 0xd8];
    uint32_t mTribePropId;                              // +0xfc

    void DoTribeGrowthSim(int unused);                  // 0x00cc62c0 (ret 4)
};

// @ 0x00cc62c0  SP::cNpcTribeController::DoTribeGrowthSim
void cNpcTribeController::DoTribeGrowthSim(int)
{
    g_fTribeScale = 1.0f;
    cGameNounManager* nm0 = NounManager();
    GameDataVector* tribes = nm0->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, 0x18c6d19);
    PtrVector& tv = tribes->mVector;
    int nTribes = tv.size();
    int count = 0;
    uint32_t* table = 0;
    char* selected = 0;
    if (!GetPropertyAsUint32Array(g_pGameProps, mTribePropId, &count, &table) || count < nTribes * 2)
        return;

    GetSetting9()->GetAvatarProfile();
    cTribe* player = NounManager()->GetPlayerTribe();
    const Vec3* playerPos = player->mSpatial.GetPosition();

    int last = nTribes - 1;
    if (mpTribeObjsBegin != mpTribeObjsEnd)
    {
        int sz = (int)(mpTribeObjsEnd - mpTribeObjsBegin);
        selected = mpTribeObjsBegin[min_ref(last, sz)];
        if (selected)
        {
            cResourceDB* db = FUN_00401010();
            char* res = selected + 0x504;
            if (!db->Has(res, 0))
            {
                if (db->IsPending(res))
                    return;
                ResKey key;
                key.id = 0x609b763;
                key.a = 0;
                key.b = 4;
                db->Request(res, &key);
                return;
            }
            ObjectTemplateDB()->Release(res, 1);
            selected = 0;
        }
    }

    uint32_t sel2 = table[nTribes * 2 - 2];
    FUN_00c8ea70(sel2);
    uint32_t v0 = 5;
    uint32_t v1 = g_1581208.GetDefault();
    if (sel2 > 0)
    {
        uint32_t* rec = FUN_00c8ea70(sel2);
        if (rec[0] > 0)
            v0 = rec[0];
        v1 = rec[1];
    }

    cHerdNoun* best = 0;
    float bestDist = 3.4028234e38f;
    cGameNounManager* nm1 = NounManager();
    GameDataVector* herds = nm1->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00ace070, FUN_00b1e500, 0x36be27e);
    PtrVector& hv = herds->mVector;
    void** it = hv.mpBegin;
    void** end = hv.mpEnd;
    for (; it != end; ++it)
    {
        cHerdNoun* h = (cHerdNoun*)*it;
        if (h->mKind == 0x57f09e5e)
        {
            const Vec3* p = h->mSpatial.GetPosition();
            float dy = playerPos->y - p->y;
            float dx = playerPos->x - p->x;
            float dz = playerPos->z - p->z;
            float d = dz * dz + dy * dy + dx * dx;
            if (bestDist > d)
            {
                best = h;
                bestDist = d;
            }
        }
    }
    if (!best)
        return;

    best->mSpatial.GetPosition();
    cTribe* tribe = CreateTribe(best->mSpatial.GetPosition(), sel2, v0, v1, 0, selected);
    ValidateHerdLocationsForTribe(tribe);
    tribe->mGrowthParam = (float)(int)table[nTribes * 2 - 1];
    TribeModeStrategyInstance()->SetTribe(tribe);
    if (TribeModeStrategyInstance())
    {
        if (TribeModeStrategyInstance()->GetUI())
        {
            EventLog()->PostFeedbackEvent(0xd82d8a26, 0x182cd6ce, tribe->mSpatial.GetPosition(), 0, 1, 0);
            if (nTribes == 1)
            {
                cSubObj* model = tribe->GetModel();
                void* tool = tribe->GetToolOfType(10);
                g_pSList->SetField18(tribe->GetSlot0());
                FUN_00b3d4d0()->PostAction(0xed4cefb6, ActionTargetArg(tool ? (char*)tool + 0x34 : 0), 0);
                FUN_00b3d4d0()->PostAction(0xd749c1, ActionTargetArg(model ? (char*)model + 0x34 : 0), 0);
                FUN_00b3d4d0()->PostAction(0xe44aea33, ActionTargetArg(&tribe->mSpatial), 0);
                TribeModeStrategyInstance()->GetUI()->SetVisible(false);
                FUN_00b3d4d0()->PostTrigger("TRG_PRE_FirstTribeAppears", 1, 0, 0, 0, 0);
            }
        }
    }

    TerraformingManager()->Apply(best->mTerraformId);
    const Vec3* tribePos = tribe->mSpatial.GetPosition();
    float radius = tribe->GetRadius();
    float pa = GetPropertyFloat(g_pGameProps, 0x80e984f, 1.0f);
    float pb = GetPropertyFloat(g_pGameProps, 0x22748972, 0.0f);
    float pc = GetPropertyFloat(g_pGameProps, 0xaf5e325, 10.0f);
    cPlanetModel* planet = PlanetModel();
    planet->FUN_00b83c40(tribePos, pa * radius, 0x4000000, 0);
    planet->FUN_00b81020(tribePos, pb * radius, 0x4000000);
    if (tribe->mpLinked)
        planet->FUN_00b81020(playerPos, tribe->mpLinked->mSpatial.GetFloat74(), 0x4000000);
    planet->FUN_00b83c40(tribe->GetModel()->mSpatial.GetPosition(), pc, 0x10000000, 0);

    cGameNounManager* nm = NounManager();
    nm->RemoveNoun(best);
    float radius2 = radius * radius;
    GameDataVector* nears = nm->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00accc30, FUN_00b1e500, 0x1be418e);
    PtrVector& nv = nears->mVector;
    void** nit = nv.mpBegin;
    void** nend = nv.mpEnd;
    for (; nit != nend; ++nit)
    {
        cNearNoun* n = (cNearNoun*)*nit;
        if (!n->IsExcluded())
        {
            const Vec3* p = n->GetPosition();
            float dx = p->x - tribePos->x;
            float dy = p->y - tribePos->y;
            float dz = p->z - tribePos->z;
            float d = dz * dz + dy * dy + dx * dx;
            if (radius2 > d)
                nm->RemoveNoun(n);
            else
                FUN_00cd4770(n, tribe);
        }
    }
}

// ===========================================================================
// SP::cNpcTribeController::OnTick (0x00cc6910) and the growth-reseed helper
// FUN_00cc5fe0, plus the sibling member 0x00cc5f80 they call.
// ===========================================================================

// ---------------------------------------------------------------------------
// extra globals touched by these two functions
// ---------------------------------------------------------------------------
extern float    g_f158135c;     // 0x0158135c  relationship threshold (class 1)
extern float    g_f1581360;     // 0x01581360  relationship threshold (class 2)
extern float    g_f1581364;     // 0x01581364  relationship threshold (class 3)
extern float    g_f1581378;     // 0x01581378  relationship reset value
extern uint64_t g_t15812c0;     // 0x015812c0  elapsed-time threshold (64-bit)

// ---------------------------------------------------------------------------
// engine helpers whose signatures come from the call sites
// ---------------------------------------------------------------------------
struct cSPTimer
{
    char mStorage[0x20];            // +0x00 real cSPTimer is 0x20 bytes
    bool     IsRunning();           // 0x00feba90 (ret 0)
    void     Restart();             // 0x00bc3130 (ret 0)
    void     Start();               // 0x00bc30f0 (ret 0)
    uint64_t GetElapsedTime();      // 0x00bc3190 (__int64 in edx:eax)
};

// cTerrainEditor::GetCurrentTerrainSphere -> object with a dword at +0x1100
struct cTerrainSphere { char pad0[0x1100]; uint32_t mHandle; };

float  g_f13ebc5c;                              // 0x013ebc5c default timer value
uint32_t* operator_delete(void* p);             // 0x00f47380

// relationship manager
struct cRelationshipManager
{
    float CalculateRelationshipAbsolute(int a, int b);          // 0x00d05a20 (ret 8)
    int   Classify(float f);                                    // 0x00d00780 (ret 4)
    void  RecordEvent(int a, int b, uint32_t id, float f);      // 0x00d06240 (ret 0x10)
};
cRelationshipManager* RelationshipManager();                    // 0x00b3d2c0

// tribe queries (this=tribe)
float FUN_00c8ead0();           // 0x00c8ead0 (this=tribe), returns float

// growth record table entry: 0xb8-byte record, +0x50 is a resource handle
struct cGrowthRecord { char pad0[0x50]; uint32_t mField50; };

// accessor used as the "this" for the archetype lookup; 0x00401090 just
// returns a global, the 2 pushed args belong to the following thiscall.
struct cSettingHost
{
    int GetArchetype(void* h, int b);       // 0x004e0050 (ret 8)
};
cSettingHost* FUN_00401090();   // 0x00401090 (ret 0)

int FUN_004e0050(void* a, int b);                                   // 0x004e0050 (ret 8)
void FUN_004cd3c0(int n);                                           // 0x004cd3c0 (ret 4)
int  FUN_004dfff0(void* a, int b, void* c, int d, int e);           // 0x004dfff0 (ret 0x14)

// small inline container used to build one FillEntry: Init@0x4cd3c0 sizes the
// inline storage, Run@0x4dfff0 fills it (5 stack args, ret 0x14).
struct cInlineVec5
{
    void*    m0;    // +0x00 inline buffer (or heap block)
    void*    m1;    // +0x04
    uint32_t m2;    // +0x08 capacity
    void Init(int n);                       // 0x004cd3c0 (ret 4)
    int  Run(void* obj, int a, int b, int c);   // 0x004dfff0 (ret 0x14)
};

// other indirect helpers
void  memcpy_11e0744(void* dst, void* src, size_t n);   // 0x011e0744

// controller-layout helpers for FUN_00cc5fe0
struct UIntVector { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; };
extern void DoInsertKey4(void* v, uint32_t* where, const uint32_t& value);   // 0x00b96600
extern void FillEntryPushBack(void* v, const void* value);                   // 0x004e19a0

// ---------------------------------------------------------------------------
// the controller as this slice sees it (a wider view than cNpcTribeController)
// ---------------------------------------------------------------------------
struct GonzagoNode
{
    GonzagoNode* mpLeft;    // +0x00
    GonzagoNode* mpRight;   // +0x04
    char         pad8[0x8];
    void*        mpKey;     // +0x10
};

// eastl::map<creature*, cSPTimer>: begin/end sentinel pair at +0x00, root at +0x0c
struct cTimerMap
{
    char        pad0[0x4];
    GonzagoNode* mpEnd;     // +0x04
    char        pad8[0x4];
    GonzagoNode* mpRoot;    // +0x0c
    cSPTimer* operator[](void** key);   // 0x00cc5ee0
};

class cNpcTribeControllerW
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual void SetActiveMode(int x);          // +0x24 (ret 4)
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35();
    virtual void* GetChildList();               // +0x90 (ret 0) returns a vector ptr

    char     pad04[0x0c];                       // +0x04 (vptr occupies +0x00)
    cSPTimer mTimer10;                          // +0x10
    cSPTimer mTimer30;                          // +0x30
    char     pad50[0x10];                       // +0x50
    cTimerMap mMap60;                           // +0x60 (map begin/end pair + root)
    char     pad70[0xc];                        // +0x70
    UIntVector mVec7c;                          // +0x7c
    char     pad88[0xd0 - 0x88];
    UIntVector mVecD0;                          // +0xd0
    char     padDc[0xfc - 0xdc];
    uint32_t mTribePropId;                      // +0xfc

    void FUN_00cc5f80();
    void FUN_00cc5fe0();
    void OnTick(uint64_t dt);
};

// mode-strategy singleton: the +0x40/+0x44 pair is a begin/end vector
struct cModeStrategy
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40();
    virtual int  GetToolPrice();                // +0xa4
};

struct cModeStrategyWide
{
    char pad0[0x40];
    int  mField40;                              // +0x40
    int  mField44;                              // +0x44
};

struct cConfigManager
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual int  GetFlag(uint32_t id);          // +0x30
};
cConfigManager* ConfigManager();                        // 0x0067dd30
bool  TerrainHasKey(uint32_t id);                       // 0x00cd4460 (ret 4), this=strategy
void* FUN_00cd3440();                                   // 0x00cd3440
void  FUN_00b706a0(uint32_t id);                        // 0x00b706a0 (ret 4)
int   GetTutorialToolPrice(cPropertyList* l, uint32_t id, int def);   // 0x004e1c30
int   GetPlayerEmpireOrMinus1();                        // 0x00b1f9d0
void* GameTimeManager();                                // 0x00b3d380

// creature/noun object iterated by the OnTick tail: vtable slots 0 (AddRef),
// 4 (Release), 0x4c (GetEmpire), 0x78, 0x88 (Tick(seconds)), 0x90 (GetChildList)
class cCreature
{
public:
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    virtual void c08(); virtual void c0c(); virtual void c10(); virtual void c14();
    virtual void c18(); virtual void c1c(); virtual void c20(); virtual void c24();
    virtual void c28(); virtual void c2c(); virtual void c30(); virtual void c34();
    virtual void c38(); virtual void c3c(); virtual void c40(); virtual void c44();
    virtual void c48();
    virtual int  GetEmpire(int empire);                 // +0x4c
    virtual void c50(); virtual void c54(); virtual void c58(); virtual void c5c();
    virtual void c60(); virtual void c64(); virtual void c68(); virtual void c6c();
    virtual void c70(); virtual void c74();
    virtual void OnDeath();                             // +0x78
    virtual void c7c(); virtual void c80(); virtual void c84();
    virtual void Tick(float seconds);                   // +0x88
    virtual void* GetChildList();                       // +0x90

    char    pad04[0x2cc - 0x04];                        // +0x04
    float   mField2cc;                                  // +0x2cc
};

// adapters with the creature passed in ecx (kept out of line so the call shape
// matches the original's "mov ecx,esi; call")
float FUN_00c8ead0_of(cCreature* c);                    // 0x00c8ead0
int   FUN_00c0b760_of(cCreature* c);                    // 0x00c0b760

// eastl::map<creature*,timer> helpers
void  MapTimerFind(void* out, void* key);               // 0x00e5c780
void  FUN_00cc5340(void* a, void* node);                // 0x00cc5340

void  SpVectorErase(void* begin, void* end);            // 0x0050f740

extern float g_fTribeScale;     // 0x0157e940 (declared in the block above)

// @ 0x00cc5fe0  FUN_00cc5fe0
void cNpcTribeControllerW::FUN_00cc5fe0()
{
    FUN_00cc5f80();

    if (mVec7c.mpBegin == mVec7c.mpEnd)
    {
        g_fTribeScale = 1.0f;
        SpVectorErase((void*)mVec7c.mpBegin, (void*)mVec7c.mpEnd);

        {
            uint32_t* src = mVecD0.mpEnd;
            uint32_t* dst = mVecD0.mpBegin;
            memcpy_11e0744(dst, src, (size_t)(src - src));
            mVecD0.mpEnd -= src - dst;
        }

        cTribe* tribe = NounManager()->GetPlayerTribe();
        (void)tribe;

        uint32_t k1;
        uint32_t k2;
        if (tribe->FUN_00c8e850())
        {
            if (tribe->FUN_00c8e870())
            {
                k1 = 0x5ece4770;
                k2 = 0xb9de15f2;
            }
            else
            {
                k1 = 0xa8ec6f99;
                k2 = 0xfd159d91;
            }
        }
        else
        {
            k1 = 0xcfb01b93;
            k2 = 0x17e5ef84;
        }

        tribe->FUN_00c8e820(0);
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere->mHandle != 0)
            k2 = sphere->mHandle;

        mTribePropId = 0xf7426b5e;
        if (k1 == 0xa8ec6f99)
        {
            if (k2 == 0xb9de15f2)       mTribePropId = 0x4252b6ff;
            else if (k2 == 0xfd159d91)  mTribePropId = 0x1631b0c3;
            else if (k2 == 0x17e5ef84)  mTribePropId = 0xf7426b5e;
        }
        else if (k1 == 0xcfb01b93)
        {
            if (k2 == 0xb9de15f2)       mTribePropId = 0x8da58d04;
            else if (k2 == 0xfd159d91)  mTribePropId = 0x97a0e4c2;
            else if (k2 == 0x17e5ef84)  mTribePropId = 0xfb43c9a7;
        }
        else if (k1 == 0x5ece4770)
        {
            if (k2 == 0xb9de15f2)       mTribePropId = 0xdb6b9;
            else if (k2 == 0xfd159d91)  mTribePropId = 0xf18a299d;
            else if (k2 == 0x17e5ef84)  mTribePropId = 0x8b4bf474;
        }

        {
            int count = 0;
            uint32_t* data = 0;
            count = 0;
            data = 0;
            if (GetPropertyAsUint32Array(g_pGameProps, mTribePropId, &count, &data) && count > 0)
            {
                int n = count / 2;
                int i = 0;
                if (n != 0)
                {
                    do
                    {
                        cGrowthRecord* rec = (cGrowthRecord*)FUN_00c8ea70(data[i * 2]);
                        uint32_t h = rec->mField50;
                        void* obj = (void*)FUN_00401090()->GetArchetype((void*)h, 0);
                        if (obj)
                        {
                            cInlineVec5 vec;
                            vec.Init(1);
                            int r = vec.Run(obj, 1, 0, 0);
                            if (r > 0)
                            {
                                uint32_t val = *(uint32_t*)vec.m0;
                                if (mVecD0.mpEnd < mVecD0.mpCapacity)
                                {
                                    uint32_t* p = mVecD0.mpEnd;
                                    mVecD0.mpEnd = p + 1;
                                    *p = val;
                                }
                                else
                                {
                                    DoInsertKey4((void*)&mVecD0, mVecD0.mpEnd, val);
                                }
                                FillEntryPushBack((void*)(val + 0x504), (void*)vec.m0);
                            }
                            void* alloc = *(void**)vec.m0;
                            if (alloc != 0 && *(uint32_t*)((char*)alloc - 4) != 0)
                                operator_delete(alloc);
                        }
                        ++i;
                    } while (i < n);
                }
            }
        }
    }
}

extern float g_f13f9428;        // 0x013f9428  seconds->milliseconds scale
extern float g_f13ebc5c;        // 0x013ebc5c  default timer property value

// @ 0x00cc6910  SP::cNpcTribeController::OnTick
void cNpcTribeControllerW::OnTick(uint64_t dt)
{
    {
        cTriggerMgr* tm = FUN_00b3d4d0();
        int mode = *(int*)((char*)tm + 0x2c);
        if (mode == 1)
            return;
        if (mode == 2)
            return;
    }
    {
        char* gt = (char*)GameTimeManager();
        if ((*(unsigned char*)(gt + 0x48) & 1) != 0)
            return;
    }

    cTribe* trib = NounManager()->GetPlayerTribe();
    (void)trib;

    float scale = g_fTribeScale;
    float seconds = (float)(__int64)dt * g_f13f9428;
    scale = scale - seconds;
    g_fTribeScale = scale;

goTail:
    if (scale < 0.0f)
    {
        GameDataVector* tribes = NounManager()->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, 0x18c6d19);
        int n = (int)(tribes->mVector.mpEnd - tribes->mVector.mpBegin);
        int idx = n - 1;
        if ((unsigned)idx <= 4u)
        {
            switch (idx)
            {
            case 0:
            {
                int flag = ConfigManager()->GetFlag(0x4ea96cb);
                bool b3 = (flag == 0);
                bool b1 = TerrainHasKey(0x11ade9ce);
                if (b1 || b3)
                {
                    if (!mTimer10.IsRunning())
                        mTimer10.Restart();
                    float lim = GetPropertyFloat(g_pGameProps, 0x3d346a77, g_f13ebc5c);
                    uint64_t el = mTimer10.GetElapsedTime();
                    b1 = ((double)(unsigned __int64)el * 0.001 < (double)lim);
                }
                bool b2 = TerrainHasKey(0x14363974);
                if (b2 || b3)
                {
                    if (!mTimer30.IsRunning())
                        mTimer30.Restart();
                    float lim = GetPropertyFloat(g_pGameProps, 0x1a09d79e, g_f13ebc5c);
                    uint64_t el = mTimer30.GetElapsedTime();
                    b2 = ((double)lim < (double)(unsigned __int64)el * 0.001);
                }
                if (b1 || b2)
                {
                    SetActiveMode(0);
                    void* p = FUN_00cd3440();
                    if (p)
                        FUN_00b706a0(0xdcdf2f2f);
                }
                break;
            }
            case 1:
            {
                cModeStrategyWide* st = (cModeStrategyWide*)TribeModeStrategyInstance();
                if (st->mField40 == st->mField44)
                {
                    int price = GetTutorialToolPrice(g_pGameProps, 0x4c87e711, 100);
                    int have = ((cModeStrategy*)st)->GetToolPrice();
                    if (have <= price)
                        break;
                }
                SetActiveMode(0);
                break;
            }
            case 2:
            case 3:
                SetActiveMode(0);
                break;
            case 4:
            {
                cModeStrategyWide* st = (cModeStrategyWide*)TribeModeStrategyInstance();
                if ((unsigned)((st->mField44 - st->mField40) >> 4) < 3u)
                    break;
                SetActiveMode(0);
                break;
            }
            default:
                break;
            }
        }
    }

    {
        GameDataVector* tribes = NounManager()->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, 0x18c6d19);
        char** it = (char**)tribes->mVector.mpBegin;
        char** end = (char**)tribes->mVector.mpEnd;
        if (it != end)
        {
            do
            {
                cCreature* obj = (cCreature*)*it;
                if (obj->mField2cc > 0.0f)
                {
                    float v = obj->mField2cc - seconds;
                    obj->mField2cc = v;
                    if (!(v > 0.0f))
                    {
                        int emp = GetPlayerEmpireOrMinus1();
                        obj->GetEmpire(emp);
                        cRelationshipManager* rm = RelationshipManager();
                        float rel = rm->CalculateRelationshipAbsolute(0, 0);
                        (void)rel;
                        int cls = rm->Classify(rel);
                        if (cls == 4)
                        {
                            obj->mField2cc = 0.0f;
                        }
                        else
                        {
                            float self = FUN_00c8ead0_of(obj);
                            int cls2 = rm->Classify(self);
                            float delta = 0.0f;
                            if (cls == 1)      delta = g_f158135c - rel;
                            else if (cls == 2) delta = g_f1581360 - rel;
                            else if (cls == 3) delta = g_f1581364 - rel;
                            if (delta < 0.0f)
                            {
                                int emp2 = GetPlayerEmpireOrMinus1();
                                obj->GetEmpire(emp2);
                                RelationshipManager()->RecordEvent(0, 0, 0x530cf06, delta);
                            }
                            int emp3 = GetPlayerEmpireOrMinus1();
                            obj->GetEmpire(emp3);
                            float rel3 = RelationshipManager()->CalculateRelationshipAbsolute(0, 0);
                            int cls3 = RelationshipManager()->Classify(rel3);
                            obj->mField2cc = (cls3 > cls2) ? g_f1581378 : 0.0f;
                        }
                    }
                }

                {
                    void* childList = obj->GetChildList();
                    char** cit = (char**)childList;
                    char** cend = (char**)((char**)childList)[1];
                    char** cur = (char**)((char**)childList)[0];
                    if (cur != cend)
                    {
                        do
                        {
                            cCreature* child = (cCreature*)*cur;
                            if (FUN_00c0b760_of(child) == 0)
                            {
                                child->AddRef();
                                // lower_bound over mMap60
                                cTimerMap& map = mMap60;
                                GonzagoNode* node = map.mpRoot;
                                GonzagoNode* cand = map.mpEnd;
                                while (node)
                                {
                                    if ((unsigned int)node->mpKey < (unsigned int)child)
                                        node = node->mpLeft;
                                    else { cand = node; node = node->mpRight; }
                                }
                                if (cand != map.mpEnd && (unsigned int)child < (unsigned int)cand->mpKey)
                                    cand = map.mpEnd;
                                bool missing = (cand == map.mpEnd);
                                child->Release();
                                if (missing)
                                {
                                    child->AddRef();
                                    cSPTimer* t = mMap60[(void**)&child];
                                    t->Start();
                                    child->Release();
                                }
                                child->AddRef();
                                cSPTimer* t2 = mMap60[(void**)&child];
                                child->Release();
                                if (t2->IsRunning() && t2->GetElapsedTime() > g_t15812c0)
                                {
                                    child->OnDeath();
                                    child->AddRef();
                                    void* found = 0;
                                    MapTimerFind(&found, &child);
                                    if (found != mMap60.mpEnd)
                                        FUN_00cc5340(0, found);
                                    child->Release();
                                }
                            }
                            child->Tick(seconds);
                            ++cur;
                        } while (cur != cend);
                    }
                }
                ++it;
            } while (it != end);
        }
    }
}
