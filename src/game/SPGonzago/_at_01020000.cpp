// src/game/SPGonzago/_at_01020000.cpp -- migrated from slice(s) s0102f0d0, s0102be20, s01021e50 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01020000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEmpire.h"
#include "SP/cGameData.h"

// ---- items of slice s01021e50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct cVTable {
    void* mpSlots[0x100];                       // 0x000
};
class cDispatchObject {
public:
    void* Call(int nSlot) {
        return ((void* (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    int32_t CallInt(int nSlot) {
        return ((int32_t (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoid(int nSlot) {
        ((void (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    cVTable* mpTable;                           // 0x000
};
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};
class cPlanetList {
public:
    void Erase(void** ppFirst, void** ppLast);

    void** mpBegin;                             // 0x000
    void** mpEnd;                               // 0x004
    void** mpCapacity;                          // 0x008
};
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const char* pName, int32_t nFlags);
    void Serialize(void* pData);

    uint8_t mPad000[0xa14];                     // 0x000
};
class cSPBackgroundSimManager {
public:
    void Read(cVarListSerializer* pSerializer);
    void ActivatePlanet(void* pPlanetKey);
    void Destroy(int32_t nFlags);
    void UpdatePlanetTerraforming(void* pPlanet, int32_t nDelta);

    int32_t mnElapsedTime;                      // 0x000
    cDispatchObject* mpSimulator;               // 0x004
    cDispatchObject* mpStar;                    // 0x008
    cDispatchObject* mpCommObject;              // 0x00c
    int32_t mnState;                            // 0x010
    int32_t mnUnused14;                         // 0x014
    int32_t mnTimeRemaining;                    // 0x018
    cRefCounted* mpRequest;                     // 0x01c
    cPlanetList mPlanets;                       // 0x020
    uint8_t mPad02c[0x1c];                      // 0x02c
};
cSPBackgroundSimManager* g_pBackgroundSim = nullptr;        // 0x16dda8c
class cStar {
public:
    cDispatchObject* GetSolarSystem();
};
class cSolarSystem {
public:
    void Tick(int32_t nDelta);
    void SetStarCharge(float fCharge);
    cDispatchObject* GetPlanet(int32_t nIndex);
};
class cSimPlanetLowLOD {
public:
    void UpdateTerraforming(int32_t nDelta);
    void Tick(int32_t nDelta);
};
void SimulateBackgroundTick(void* pStar, int32_t nDelta);
int32_t GetCurrentGameMode();
float g_fBackgroundTickScale = 0.001f;                      // 0x13f9428
// ---- items of slice s01021e50 end

// ---- items of slice s0102be20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
void* ObjectTemplateDB();
void ConstraintInit(void* pOut, uint32_t nA, int nB, uint32_t nC);
void FilterApply(void* pOut, uint32_t nCount);
void FilterEvaluate(void* pA, void* pB);
void MatchApply(void* pOut, uint32_t nCount);
void MatchEvaluate(void* pA, void* pB);
char BigCatQuery(void* pA, void* pB);
// ---- items of slice s0102be20 end

// ---- items of slice s0102f0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_0;        // 0x01485378
extern int     g_ProtoKeys[7];                         // 0x015b7600
typedef unsigned int uint;
struct GetsProperty {
virtual void q0();
virtual void q1();
virtual void q2();
virtual void q3();
virtual void q4();
virtual void q5();
virtual void q6();
virtual void q7();
    virtual void q8();
    virtual bool GetProperty(uint id, void** out);       // +0x24
};
struct cPropertyList : GetsProperty {};
bool GetPropertyAsFloatArray(cPropertyList* list, uint id, int* count, float** data);   // 0x006a08b0
struct cEmpire;
struct InvMeter {
    char  pad[0x7f4];
    float mfCurrent;                        // +0x7f4
    float mfMax;                            // +0x7f8
};
struct cSPSimulatorSpaceGame {
    InvMeter* GetPlayerInventory();         // 0x00a1ad60
};
void*     GetUFOSimulator();                // 0x00ffbe50
cEmpire*  GetPlayerEmpire();                // 0x01021300
int       GetPlayerEmpire2Int(cEmpire* e);  // 0x00c30cb0
struct RelationshipManager {
    bool CanContact(cEmpire* other);                        // 0x00c31bc0
    int  GetRelationLevel(cEmpire* a, cEmpire* b, int mode);  // 0x00d00a70
};
RelationshipManager* GetRelationshipManager();   // 0x00b3d2c0
struct cStarRecordVec { int* mpBegin; int* mpEnd; int* mpCapacity; };
struct cEmpire {
    char pad[0x84];
    cStarRecordVec mStars;                  // +0x84
    int GetHomePlanet();                    // 0x00c31730
    bool CanContact(cEmpire* other);        // 0x00c31bc0
};
int  GetActivePlanetRecord();               // 0x010212a0
struct Vec3_s0102_f0d0 { float x, y, z; };
struct Triple { uint a, b, c; };                        // 12-byte value, the cached "layout"
struct VtableProto {
virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
virtual void p14();
virtual void p18();
virtual void p1c();
virtual void p20();
virtual void p24();
virtual void p28();
virtual void p2c();
virtual void p30();
virtual void p34();
virtual void p38();
virtual void p3c();
virtual void p40();
virtual void p44();
virtual void p48();
virtual void p4c();
virtual void p50();
virtual void p54();
virtual void p58(void* v, int z);
};
struct VtableCfg {
virtual void c00();
virtual void c04();
virtual void c08();
virtual void c0c();
virtual void c10();
virtual void c14();
virtual void c18();
    virtual bool c1c(void* v, int z);           // +0x1c
virtual void c20();
virtual void c24();
virtual void c28();
virtual void c2c();
virtual void c30();
virtual void c34();
virtual void c38();
    virtual bool c3c(void* v);                  // +0x3c
virtual void c40();
virtual void c44();
virtual void c48();
    virtual void c4c(void* v, void* tag);       // +0x4c
};
struct VtableCfg2 {
virtual void d00();
virtual void d04();
virtual void d08();
virtual void d0c();
virtual void d10();
virtual void d14();
virtual void d18();
virtual void d1c();
virtual void d20();
virtual void d24();
virtual void d28();
virtual void d2c();
virtual void d30();
virtual void d34();
virtual void d38();
virtual void d3c();
    virtual void d40(uint id);
};
struct VtableMsg {
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24(void* handler, uint id);
};
struct KeyNode {
    KeyNode* mpRight;
    KeyNode* mpLeft;
    KeyNode* mpParent;
    uint     mColor;
    uint     mKey;
    Triple   mValue;
};
struct KeyMap {
    uint     mCompare;                       // +0x00
    KeyNode* mpAnchorRight;                  // +0x04
    KeyNode* mpAnchorLeft;                   // +0x08
    KeyNode* mpRoot;                         // +0x0c
    uint     mColor;                         // +0x10
    uint     mnSize;                         // +0x14
    KeyMap();                                // 0x00bf2c60
    void DoNukeSubtree(KeyNode* n);          // 0x009a9600
    Triple* Get(uint key);                   // 0x00bf9700  find-or-insert, returns &value
    void    Set(uint key, const Triple& v);  // 0x00bf4a60
};
void*          ConfigManager();                        // 0x00401010
bool           AppPropertyGetDescription(uint key);    // 0x006a25a0 (cDirectPropertyList::GetDescription)
void           LayoutCreate(int key, Triple* out);     // 0x00bf4a60
void           LayoutSet_dtor(void* s, int z);         // 0x0102c7f0
void           EA_Messaging_RemoveHandler(void* h, int a, int b, int c, int d);  // 0x00571db0
void           operator_delete_(void* p);              // 0x00f47380
void*          MessageServer();                        // 0x0067dcc0
struct cSPSpaceEconomyTuning {
    char pad0[8];
    cPropertyList* mPropList;                             // +8
    int   GetTradeCaptureOfferPrice(int index);           // 0x0102fa30
    int   GetHomeWorldBuildingMultiplier();               // 0x0102fb70
    int   GetEnergyRechargeDelayMS();                     // 0x0102fbf0
    float GetEnergyRechargePerMS();                       // 0x0102fc60
    int   GetTradeCaptureCostForPlanet(int index);        // 0x01030000
    int   CalcAttackRequestCost(float place);             // 0x01030650
    int   GetPeaceOfferPrice(int index, cEmpire* e);      // 0x01030930
    int   GetPeaceBadOfferDelta(cEmpire* e);              // 0x010309c0
    int   GetPeaceVeryBadOfferDelta(cEmpire* e);          // 0x01030a30
    int   GetPeaceGoodOfferDelta(cEmpire* e);             // 0x01030aa0
    float f0102f8c0(int index);                           // 0x0102f8c0
};
// ---- items of slice s0102f0d0 end

// @ 0x010225d0
void SimulateBackground(void* pStar, int32_t nDelta)
{
    if (pStar != nullptr && ((cDispatchObject*)pStar)->CallInt(0x00) != 0) {
        void* pPlanet = ((cDispatchObject*)pStar)->Call(0x00);
        ((cSimPlanetLowLOD*)pPlanet)->UpdateTerraforming(nDelta);
    }

    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    pManager->mnElapsedTime += nDelta;
    if (pManager->mnElapsedTime < 0x3e8)
        return;

    while (pManager->mnElapsedTime >= 0x3e8) {
        pManager->mnElapsedTime -= 0x3e8;
        cSolarSystem* pSystem = (cSolarSystem*)pManager->mpStar->Call(0x00);
        if (pSystem == nullptr)
            continue;
        int32_t nPlanets = (int32_t)(pSystem->GetPlanet(0) != nullptr);
        for (int32_t i = 0; i < nPlanets; ++i) {
            void* pPlanet = pSystem->GetPlanet(i);
            if (((cDispatchObject*)pPlanet)->CallInt(0x00) == 0)
                continue;
            void* pLowLOD = ((cDispatchObject*)pPlanet)->Call(0x00);
            ((cSimPlanetLowLOD*)pLowLOD)->Tick(0x3e8);
        }
    }

    if (pStar != nullptr)
        SimulateBackgroundTick(pStar, nDelta);
}

// @ 0x01022920
void AdvanceBackgroundSim(int32_t nDelta)
{
    if (GetCurrentGameMode() == 0x1654c05) {
        cSPBackgroundSimManager* pManager = g_pBackgroundSim;
        SimulateBackground(pManager->mpSimulator, nDelta);
    }

    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    int32_t nState = pManager->mnState;
    if (nState != 0) {
        if (nState != 1)
            return;
    }

    cStar* pStar = (cStar*)pManager->mpStar;
    if (pStar == nullptr)
        return;
    cSolarSystem* pSystem = (cSolarSystem*)pStar->GetSolarSystem();
    if (pSystem == nullptr)
        return;

    float fCharge = (float)(uint32_t)nDelta * g_fBackgroundTickScale;
    pSystem->SetStarCharge(fCharge);
}

// @ 0x0102c7f0
void ApplyFilterConstraints(void* pUnused, char bSecond)
{
    (void)pUnused;
    Vec3 filter;
    filter.mX = 0.0f;
    filter.mY = 0.0f;
    filter.mZ = 0.0f;

    void* pDatabase = ObjectTemplateDB();
    (void)pDatabase;
    uint8_t constraint[0x30];
    ConstraintInit(constraint, 0x2dd90af, 0, 0x476a98c7);

    if (bSecond != 0) {
        ConstraintInit(constraint, 0x3cc89b1, 0, 0x913b23be);
    }

    FilterApply(&filter, 1);
    if ((void*)0 != (void*)0)
        FilterEvaluate(nullptr, nullptr);
    if (BigCatQuery(nullptr, nullptr) != 0)
        (void)0;
    MatchApply(&filter, 1);
    MatchEvaluate(&filter, nullptr);
}

// @ 0x0102f0d0
bool f0102f0d0(int* planet, int* record)
{
    int  keyA = record[2];
    int  keyB = record[6];
    int* keyC = (int*)record[4];

    if (keyB == (int)0x476a98c7) {
        if (planet[0x57] & 1) {
            if (planet[0x4b] == keyA && planet[0x4c] == keyB && planet[0x4d] == (int)keyC)
                planet[0x54] = 0;
        }
        if (planet[0x57] & 2) {
            if (planet[0x4e] == keyA && planet[0x4f] == keyB && planet[0x50] == (int)keyC)
                planet[0x55] = 0;
        }
        if (planet[0x57] & 4) {
            if (planet[0x51] == keyA && planet[0x52] == keyB && planet[0x53] == (int)keyC)
                planet[0x56] = 0;
        }
        return true;
    }

    int* mask = planet + 0x48;                 // +0x120
    int  base = 3;                             // first entry is planet[3] (byte 0xc)
    for (int slot = 0; slot < 3; ++slot) {
        uint bit = 1u << slot;
        if ((uint)planet[8] & bit) {           // +0x20
            uint b = 1;
            int  idx = 0;
            do {
                if (b & (uint)*mask) {
                    int* e = planet + base + idx * 3;
                    if (e[0] == keyA && e[1] == keyB && e[2] == (int)keyC)
                        *mask = ~(int)b & *mask;
                }
                ++idx;
                b = (b << 1) | (b >> 31);
            } while (idx < 7);
        }
        ++mask;
        base += 7;
    }
    return true;
}

// @ 0x0102f220
void f0102f220(int* self)
{
    *(void**)self = (void*)0x14996a8;
    *(void**)(self + 1) = (void*)0x14996a4;
    int* cache = self + 0x4b;                       // +0x12c
    int* entry = self + 9;                          // +0x24
    for (int slot = 0; slot < 3; ++slot) {
        uint bit = 1u << slot;
        if ((uint)self[8] & bit) {
            int* p = entry;
            for (int i = 7; i != 0; --i) {
                ((VtableProto*)ObjectTemplateDB())->p58(p, 0);
                p += 3;
            }
        }
        if ((uint)self[0x57] & bit)
            ((VtableProto*)ObjectTemplateDB())->p58(cache, 0);
        cache += 3;
        entry += 0x15;
    }
    ((VtableCfg2*)ConfigManager())->d40(0x12375893);
    int h = self[3];
    if (h != 0) {
        self[3] = 0;
        EA_Messaging_RemoveHandler((void*)h, self[4], self[5], self[6], self[7]);
    }
    *(void**)self = (void*)0x13eb394;
    *(void**)(self + 1) = (void*)0x13ef094;
}

// @ 0x0102f340
void f0102f340(int* self)
{
    bool desc = AppPropertyGetDescription(0x60476f2);
    KeyMap set;
    set.KeyMap::KeyMap();
    uint want = ((uint)self[8] + 1) & ~(uint)self[8] & 7;
    if (want != 0) {
        uint idx = (uint)(float)want;                 // the compiler's float->int exponent trick
        self[idx + 0x48] = 0;                         // +0x120
        int* e = (int*)((char*)self + (int)idx * 0x54 + 0x24);
        uint bit = 1;
        for (int i = 0; i < 0x1c; i += 4) {
            Triple* t = set.Get(g_ProtoKeys[i / 4]);
            e[0] = t->a; e[1] = t->b; e[2] = t->c;
            if (!((VtableCfg*)ConfigManager())->c1c(e, 0)) {
                self[idx + 0x48] |= (int)bit;
                if (desc && !((VtableCfg*)ConfigManager())->c3c(e)) {
                    int tag[3];
                    tag[0] = 0x12375893;
                    tag[1] = 0;
                    tag[2] = 7;
                    ((VtableCfg*)ConfigManager())->c4c(e, tag);
                }
            }
            e += 3;
            bit = (bit << 1) | (bit >> 31);
        }
        self[8] |= (int)want;
    }
    KeyNode* n = set.mpRoot;
    while (n) {
        set.DoNukeSubtree(n);
        KeyNode* next = (KeyNode*)n->mpLeft;
        operator_delete_(n);
        n = next;
    }
}

// @ 0x0102f4a0
void f0102f4a0(int* self)
{
    bool desc = AppPropertyGetDescription(0x60476f2);
    KeyMap set;
    set.KeyMap::KeyMap();
    uint want = ((uint)self[0x57] + 1) & ~(uint)self[0x57] & 7;
    if (want != 0) {
        uint idx = (uint)(float)want;
        int* e = (int*)((char*)self + (idx * 3 + 0x4b) * 4);
        self[idx + 0x54] = 0;                         // +0x150
        LayoutSet_dtor(e, 0);
        if (!((VtableCfg*)ConfigManager())->c1c(e, 0)) {
            self[idx + 0x54] = 1;
            if (desc && !((VtableCfg*)ConfigManager())->c3c(e)) {
                int tag[3];
                tag[0] = 0x12375893;
                tag[1] = 0;
                tag[2] = 6;
                ((VtableCfg*)ConfigManager())->c4c(e, tag);
            }
        }
        self[0x57] |= (int)want;
    }
    KeyNode* n = set.mpRoot;
    while (n) {
        set.DoNukeSubtree(n);
        KeyNode* next = (KeyNode*)n->mpLeft;
        operator_delete_(n);
        n = next;
    }
}

// @ 0x0102f5a0
bool f0102f5a0(int* self, int arg)
{
    (void)arg;
    bool found = false;
    uint slot = (uint)self[0x58];                   // +0x160
    for (int i = 0; i < 3; ++i) {
        if (self[0x48 + (int)slot] == 0) {          // +0x120
            found = true;
            break;
        }
        slot = (slot + 1) % 3;
    }
    int* e = (int*)((char*)self + (int)slot * 0x54 + 0x24);
    for (int j = 0; j < 0x1c; j += 4) {
        LayoutCreate(g_ProtoKeys[j / 4], (Triple*)e);
        e += 3;
    }
    self[8] &= ~(1 << (int)slot);
    int cur = self[8];
    if ((int)slot == self[0x58])
        self[0x58] = (self[0x58] + 1) % 3;
    while (cur != 7) {
        f0102f340(self);
        cur = self[8];
    }
    int curB = self[0x57];
    while (curB != 7) {
        f0102f4a0(self);
        curB = self[0x57];
    }
    return found;
}

// @ 0x0102f660
bool f0102f660(int* self, Vec3_s0102_f0d0* out)
{
    bool found = false;
    uint slot = (uint)self[0x59];                   // +0x164
    for (int i = 0; i < 3; ++i) {
        if (self[0x54 + (int)slot] == 0) {          // +0x150
            found = true;
            break;
        }
        slot = (slot + 1) % 3;
    }
    int* e = (int*)((char*)self + ((int)slot * 3 + 0x4b) * 4);
    out->x = *(float*)&e[0];
    out->y = *(float*)&e[1];
    out->z = *(float*)&e[2];
    self[0x57] &= ~(1 << (int)slot);
    if ((int)slot == self[0x59])
        self[0x59] = (self[0x59] + 1) % 3;
    int cur = self[8];
    while (cur != 7) {
        f0102f340(self);
        cur = self[8];
    }
    int curB = self[0x57];
    while (curB != 7) {
        f0102f4a0(self);
        curB = self[0x57];
    }
    return found;
}

// @ 0x0102f710
int* f0102f710(int* self)
{
    *(void**)(self + 1) = (void*)0x13ef094;
    self[2] = 0;
    *(void**)self = (void*)0x14996a8;
    *(void**)(self + 1) = (void*)0x14996a4;
    self[3] = 0;
    self[4] = 0;
    self[5] = 0;
    self[6] = 0;
    self[7] = 0;
    int* p = self + 9;
    for (int i = 0x14; i >= 0; --i) {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p += 3;
    }
    self[0x4b] = 0; self[0x4c] = 0; self[0x4d] = 0;
    self[0x4e] = 0; self[0x4f] = 0; self[0x50] = 0;
    self[0x51] = 0; self[0x52] = 0; self[0x53] = 0;
    self[8] = 0;
    self[0x58] = 0;
    self[0x57] = 0;
    self[0x59] = 0;
    void* server = MessageServer();
    self[3] = (int)server;
    self[4] = (int)self;
    self[5] = (int)(void*)0x149969c;
    self[6] = 1;
    self[7] = 0;
    if (server != 0)
        ((VtableMsg*)server)->m24(self, 0x695e243);
    int cur = self[8];
    while (cur != 7) {
        f0102f340(self);
        cur = self[8];
    }
    int curB = self[0x57];
    while (curB != 7) {
        f0102f4a0(self);
        curB = self[0x57];
    }
    return self;
}

// @ 0x0102f820
int f0102f820(cEmpire* e)
{
    cEmpire* player = GetPlayerEmpire();
    if (e == player) {
        int home = player->GetHomePlanet();
        return GetActivePlanetRecord() != home ? 1 : 0;
    }
    if (e->CanContact(player))
        return 2;
    int* a = (int*)e->mStars.mpBegin;
    int* b = (int*)player->mStars.mpBegin;
    uint level = (uint)GetRelationshipManager()->GetRelationLevel((cEmpire*)a, (cEmpire*)b, 1);
    if (level <= 4) {
        switch (level) {
        case 0:
        case 1:  return 5;
        case 3:
        case 4:  return 3;
        }
    }
    return 4;
}

// @ 0x0102f8c0
float cSPSpaceEconomyTuning::f0102f8c0(int index)
{
    return *(float*)((char*)((int*)this)[3] + index * 4);
}

// @ 0x0102f8d0
int f0102f8d0(cSPSpaceEconomyTuning* self, cEmpire* e, float* out)
{
    int    count = 0;
    float* data = 0;
    float  lo = 0.0f;
    int    result;
    GetPropertyAsFloatArray(self->mPropList, 0x5e8fcdd, &count, &data);
    if (count > 0) {
        int n = f0102f820(e);
        int hi = count - 1;
        int* sel = &n;
        if (hi <= n)
            sel = &hi;
        lo = data[*sel];
    }
    InvMeter* inv = ((cSPSimulatorSpaceGame*)GetUFOSimulator())->GetPlayerInventory();
    float budget = inv->mfMax - inv->mfCurrent;
    float scaled = budget * lo;
    int   base = (int)scaled;                       // cvttss2si + ceil correction
    if ((float)base < scaled)
        ++base;
    result = base;
    if (lo > g_0) {
        int cap = GetPlayerEmpire2Int(GetPlayerEmpire());
        int* sel1 = &base;
        if (base <= cap)
            sel1 = &cap;
        float div = (float)*sel1 / lo;
        float* sel2 = &div;
        if (budget <= div)
            sel2 = &budget;
        float picked = *sel2;
        float m = picked * lo;
        int   r = (int)m;
        if ((float)r < m)
            ++r;
        result = r;
    }
    if (out)
        *out = lo;
    return result;
}
