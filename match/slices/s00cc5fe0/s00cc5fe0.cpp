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

class cGameNounManager
{
public:
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                      uint32_t type);   // 0x00b21340 (ret 0x14)
    cTribe* GetPlayerTribe();                           // 0x00bfc5f0
    void RemoveNoun(void* noun);                        // 0x00b225d0 (ret 4)
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
