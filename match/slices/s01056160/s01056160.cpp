// Recovered from SporeApp.exe (retail).
// Batch gold7 / worker 0 / slice s01056160.
//
// cSPToolStrategy / cSPDefaultAoETool family: tool-validity checks, tool
// activation and the scan / repair / AoE strategy start paths.

typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
#define nullptr 0

struct Vec3 { float mX; float mY; float mZ; };

// ---------------------------------------------------------------------------
// Generic object model
// ---------------------------------------------------------------------------

class IRefCounted {
public:
    virtual void v00();
    virtual void AddRef();                        // 0x04
    virtual void Release();                       // 0x08
    virtual void SetEnabled(int bEnabled);        // 0x0c
    virtual bool IsAlive();                       // 0x10
    virtual void* Query(const void* pType);       // 0x14
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v2c();
    virtual Vec3* GetPosition(Vec3* pOut);        // 0x30
    virtual Vec3* GetDirection(Vec3* pOut);       // 0x30
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual float v58();                          // 0x58
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void* vb8(const void* pType);         // 0xb8  cached interface lookup
};

class cSPTimer {
public:
    void Stop();
    uint32_t mPad00[4];
};

// ---------------------------------------------------------------------------
// Planet / inventory / universe model
// ---------------------------------------------------------------------------

class cPlanetSpecies {
public:
    bool IsSpeciesScanned();
    void SetSpeciesAsScanned();
    bool IsColonyScanned();
    void SetColonyScanned();
    bool IsTribeScanned();
    void SetTribeAsScanned();
};

class cPlanet {
public:
    Vec3* GetPosition(Vec3* pOut);
    uint8_t mPad00[0x98];
};

// A tool-carrying object referenced through offset 0x114 of a strategy.
class cSPSpaceInventoryItem : public IRefCounted {
public:
    uint8_t mPad04[0x34];        // 0x04..0x38
    float mValue38;              // 0x38  comparison value (scan/repair progress)
    uint8_t mPad3c[0x6d8];       // 0x3c..0x714
    uint32_t mFlags714;          // 0x714
    uint8_t mPad718[0xdc];       // 0x718..0x7f4
    float mEnergyMax;            // 0x7f4
    float mEnergyCurrent;        // 0x7f8
};

// Interactable-object header reached through FUN_00ff3f10.
class cSPInteractableObject {
public:
    uint8_t mPad00[0x14];        // 0x00..0x14
    int mObjectType;             // 0x14  eInteractableObjectType
};
class cSPSpaceInventory {
public:
    uint8_t mPad00[0x34];
    IRefCounted* mpHeldItem;     // 0x34
    uint8_t mPad38[0x4d0];
    IRefCounted* mpShipItem;     // 0x508
    uint8_t mPad50c[0x34];
    float mCargoMax;             // 0x540
    uint8_t mPad544[0x2b0];
    float mEnergyCurrent;        // 0x7f4
    float mEnergyMax;            // 0x7f8
};

class cSPSimulatorSpaceGame {
public:
    void* GetPlayerInventory();
    void* GetPlayerUFO();
    void* GetPlayerEmpire();
    uint8_t mPad00[0x20];
};

void* GetUFOSimulator();                 // 0x00ffbe50
void* SpaceGameGetRaw();                 // 0x01002bd0
void* GetUniverseContext();              // 0x01021080
void* FUN_01021260();                    // 0x01021260
void* FUN_01021230();                    // 0x01021230
void* FUN_010212a0();                    // 0x010212a0
char  FUN_010052b0();                    // 0x010052b0
char  FUN_010052d0(void* a);             // 0x010052d0
void* GetActivePlanet();                 // cSPLivingUniverse::GetActivePlanet
int   GetPlayerEmpireID();               // cSPLivingUniverse::GetPlayerEmpireID
int   GetPlayerEmpire();                 // cSPLivingUniverse::GetPlayerEmpire
int   GetPlayerHomePlanet();             // cSPLivingUniverse::GetPlayerHomePlanet

void* GetCurrentGameMode();              // 0x00b5b800
void* GameTimeManager();                 // 0x00b3d380
void* __fastcall NounManager();          // 0x00b3d300 (result in eax)
void* __fastcall PlanetModelGet();       // 0x00b3d350 (result in eax)
int __fastcall GameDataBigCountList(void* self, void* pGameData);  // 0x00b20470
void  __fastcall FUN_00f67d90(void* self);   // GetCurrentTerrainSphere (this = NounManager)

// ---------------------------------------------------------------------------
// Tool strategy
// ---------------------------------------------------------------------------

class cSPToolStrategy {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void* GetToolKey();   // 0x18  returns pointer to a 3-dword resource Key
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30(int a, int b, int c, int d);   // 0x30  ShowToolEventLog
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48(int a, int b);   // 0x48
    virtual void v4c();

    // 0x00 vftable
    uint8_t mPad04[0x30];
    void* mpPlanet;                           // 0x34
    uint8_t mPad38[0x28];
    void* mpChargeObject;                     // 0x60
    uint8_t mPad64[0x1c];
    uint8_t mbActive;                         // 0x80
    uint8_t mPad81[0x2f];
    IRefCounted* mpToolEffectA;               // 0xb0
    IRefCounted* mpToolEffectB;               // 0xb4
    uint8_t mPadB8[0x10];
    cSPTimer mTimer;                          // 0xc8
    uint8_t mPadD8[0x3c];
    cSPSpaceInventoryItem* mpTargetItem;      // 0x114
    uint32_t mStrategyClassID;                // 0x118
    uint8_t mPad11c[0x4];
    IRefCounted* mpAreaEffect;                // 0x120
    uint8_t mPad124[0x1c];
    IRefCounted* mpActiveObject;              // 0x140
    uint8_t mPad144[0x2c];
    int mEventType;                           // 0x170
};

class cSPDefaultAoETool : public cSPToolStrategy {
public:
    bool StartTool(int nToolId, int nTarget, int nFlags);   // 0x01056b50
};

class cSPEnergyRepairToolStrategy : public cSPToolStrategy {
public:
};

class cSPRepairAOEToolStrategy : public cSPToolStrategy {
public:
    bool StartTool(int nToolId, int nTarget, int nFlags);   // 0x01056c70
};

// ---------------------------------------------------------------------------
// externals with explicit addresses
// ---------------------------------------------------------------------------
// 0x01056160 bool CanUseTool(strategy*, int nTarget, int* pOut)   (canonical)
bool __stdcall CanUseTool_56160(cSPToolStrategy* self, int nTarget, int* pOut);
// 0x010568b0 bool StartTool(strategy* self, int nTarget, int nFlags)  (free; self on stack)
bool __stdcall StartTool_568b0(cSPToolStrategy* self, int nTarget, int nFlags);
// 0x010527f0 int SetErrorEvent(strategy*, int nEventType, bool bPost)
int __stdcall SetErrorEvent_527f0(cSPToolStrategy* self, int nEventType, int bPost);
// 0x01052880 void AppendScanResult(void* pList, int* pOut)
void __stdcall AppendScanResult_52880(void* pList, int* pOut);
// 0x0104c4f0 int GetTextAt(this=ecx, int id)  -> thiscall wrapper below
// 0x0104c4f0 int GetTextAt(node)  (thiscall: ecx = erase node)
int __fastcall GetTextAt_4c4f0(void* node);
// 0x0104ff10 bool fun(strategy*)
bool __fastcall FUN_0104ff10(cSPToolStrategy* self);
// 0x0104e320 bool NeedsCharges(strategy*)
bool __fastcall FUN_0104e320(cSPToolStrategy* self);
// 0x0104cb70 bool IsInContext(strategy*)
bool __fastcall FUN_0104cb70(cSPToolStrategy* self);
// 0x00ff3f10 void* fun(inventory*)
void* __fastcall FUN_00ff3f10(void* self);
// 0x004eb930 bool fun(void* a, void* b)
bool __cdecl FUN_004eb930(void* a, void* b);
// 0x00b8dab0 int fun(void* self)
int __fastcall FUN_00b8dab0(void* self);
// 0x00b3d2a0 void* StarManager()
void* __fastcall StarManager();
// 0x00ba6490 void fun(void* self)
void __fastcall FUN_00ba6490(void* self);
// 0x00ba9370 void* GetEmpireByID(void* self, uint32_t id)
void* __fastcall FUN_00ba9370(void* self, uint32_t id);
// 0x00c30c60 void* fun()
void* __fastcall FUN_00c30c60();
// 0x0104bd80 int fun()
int __fastcall FUN_0104bd80();
// 0x00c8b5a0 int fun()
int __fastcall FUN_00c8b5a0();
// 0x00c70e00 int fun()
int __fastcall FUN_00c70e00();
// 0x00bbc670 int fun(void* self)
int __fastcall FUN_00bbc670(void* self);
// 0x00b3d510 void fun(void* self)
void __fastcall FUN_00b3d510(void* self);
// 0x00b71510 bool fun(void* self)
bool __fastcall FUN_00b71510(void* self);
// 0x0108db30 void* fun()  (used by CanUseTool)
void* __fastcall FUN_0108db30();
// 0x01037d30 char fun(void* a, void* b)
char __fastcall FUN_01037d30(void* a, void* b);
// 0x00b8d8f0 void* fun(void* a)
void* __fastcall FUN_00b8d8f0(void* a);
// 0x00c389c0 void fun(void* self, int a, int b)
void __fastcall FUN_00c389c0(void* self, int a, int b);
// 0x00bc3110 cSPTimer::Stop(void* self)
void __fastcall FUN_00bc3110(void* self);
// 0x01050640 void* fun(void* self)
void* __fastcall FUN_01050640(void* self);
// 0x00c75630 void fun(void* self)
void __fastcall FUN_00c75630(void* self);
// 0x00c73cf0 void fun(void* self, int a)
void __fastcall FUN_00c73cf0(void* self, int a);
// 0x00c9f040 void fun(void* self, int a)
void __fastcall FUN_00c9f040(void* self, int a);
// 0x00c375d0 float fun(void* a)
float __cdecl FUN_00c375d0(void* a);
// generic float helpers (libm)
double sqrt(double);
float fun_sqrt(float x);
// 0x00c37360 void* fun()
void* __fastcall FUN_00c37360();
// 0x00fb7ba0 float fun(void* self)
float __fastcall FUN_00fb7ba0(void* self);
// 0x00b7e3e0 bool fun(void* self)
bool __fastcall FUN_00b7e3e0(void* self);
// 0x00b81630 Vec3* fun(void* self, Vec3* pOut)
Vec3* __fastcall FUN_00b81630(void* self, Vec3* pOut);
// 0x00b894a0 void* fun(void* self, Vec3* pOut)
void* __fastcall FUN_00b894a0(void* self, Vec3* pOut);
// 0x00bd9c00 bool fun(void* self, Vec3* pOut)
bool __fastcall FUN_00bd9c00(void* self, Vec3* pOut);
// 0x00b3d390 node* erase(int v)  (free)
void* __stdcall FUN_00b3d390(int v);
// 0x0104c4f0 helper returns text via eax from erase node
int __fastcall FUN_0104c4f0(void* node);// 0x00bc3130 cSPTimer::Restart(void* self)
void __fastcall FUN_00bc3130(void* self);
// 0x00bfc470 void fun(void* self, int a)
void __fastcall FUN_00bfc470(void* self, int a);
// 0x00b71fb0 void fun(void* a, int b)
void __fastcall FUN_00b71fb0(void* a, int b);
// 0x0067dcc0 MessageServer()
void* __fastcall MessageServer();
// 0x00421c80 SlotMessage::Construct(this, int)
void __fastcall SlotMessageConstruct(void* self, int id);
// 0x00421cf0 SlotMessage::Destruct(this)
void __fastcall SlotMessageDestruct(void* self);
// 0x00ffbe50 GetUFOSimulator used with ecx (thiscall-like)
void* __fastcall FUN_00ffbe50(void* ecx);

// data
extern float g_1443c8c;
extern void* g_16e1fd0;
extern void* g_16e1fc4;
extern void* g_16e1fa0;
extern void* g_16e1f64;
extern void* g_16e1cdc;
extern void* g_16e1e08;
extern void* g_16e2090;
extern void* g_13f94d4;
extern void* g_16e1f94;
extern void* g_16e1f98;
extern void* g_16e1f9c;
extern void* g_16e1ce8;
extern void* g_16e1cec;
extern void* g_16e1cf0;
extern void* g_16e1e2c;
extern void* g_16e1e30;
extern void* g_16e1e34;
extern void* g_15b7433;
extern void* g_16e1d18;
extern void* g_16e1d90;
extern uint8_t g_15b743d;
extern int   g_1654c05;

// 0x0067dd00 SP::AppSystem() -> pointer (result in eax)
void* __fastcall AppSystem();

// ---------------------------------------------------------------------------
// 0x01056b50  cSPDefaultAoETool::StartTool  (thiscall: ecx = this)
// ---------------------------------------------------------------------------
// @ 0x01056b50
bool cSPDefaultAoETool::StartTool(int nToolId, int nTarget, int nFlags)
{
    cSPToolStrategy* other = (cSPToolStrategy*)nToolId;
    if (StartTool_568b0(other, nTarget, nFlags)) {
        cSPSpaceInventoryItem* mi = other->mpTargetItem;
        if (mi != nullptr) {
            int r = (int)mi->vb8((const void*)&g_13f94d4);
            if (r != 0 && other->mpAreaEffect == nullptr) {
                v48(nToolId, nTarget);
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x01056bb0  cSPToolStrategy::CanUseTool wrapper (free)
// ---------------------------------------------------------------------------
// @ 0x01056bb0
bool __stdcall CanUseTool_56bb0(cSPToolStrategy* self, int nTarget, int* pOut)
{
    if (CanUseTool_56160(self, nTarget, pOut)) {
        cSPSimulatorSpaceGame* game = (cSPSimulatorSpaceGame*)SpaceGameGetRaw();
        void* inv = game->GetPlayerInventory();
        int item = (int)FUN_00ff3f10(inv);
        if (item != 0) {
            cSPInteractableObject* obj = (cSPInteractableObject*)item;
            if (obj->mObjectType != 3)
                return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x01056bf0  cSPEnergyRepairToolStrategy::CanUseTool (free)
// ---------------------------------------------------------------------------
// @ 0x01056bf0
bool __stdcall CanUseTool_56bf0(cSPToolStrategy* self, int nTarget, int* pOut)
{
    if (CanUseTool_56160(self, nTarget, pOut)) {
        cSPSpaceInventoryItem* item = self->mpTargetItem;
        if (item != nullptr) {
            cSPSpaceInventoryItem* obj = (cSPSpaceInventoryItem*)item->vb8((const void*)0xb033b403);
            if (obj != nullptr && obj->mFlags714 == 0) {
                if (obj->mEnergyCurrent > obj->mEnergyMax)
                    return true;
                if (pOut != nullptr)
                    *pOut = GetTextAt_4c4f0(FUN_00b3d390(0x13));
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x01056c70  cSPRepairAOEToolStrategy::StartTool  (thiscall: ecx = this)
// ---------------------------------------------------------------------------
// @ 0x01056c70
bool cSPRepairAOEToolStrategy::StartTool(int nToolId, int nTarget, int nFlags)
{
    if (StartTool_568b0((cSPToolStrategy*)nToolId, nTarget, nFlags)) {
        v30(nToolId, nTarget, 3, 0);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x01056cb0  cSPRepairAOEToolStrategy::CanUseTool (free)
// ---------------------------------------------------------------------------
// @ 0x01056cb0
bool __stdcall CanUseTool_56cb0(cSPToolStrategy* self, int nTarget, int* pOut)
{
    if (CanUseTool_56160(self, nTarget, pOut)) {
        cSPSpaceInventoryItem* item = self->mpTargetItem;
        if (item != nullptr) {
            cSPSpaceInventoryItem* obj = (cSPSpaceInventoryItem*)item->vb8((const void*)&g_13f94d4);
            if (obj != nullptr) {
                float stored = obj->mValue38;
                float other = obj->v58();
                if (stored < other)
                    return true;
                if (pOut != nullptr)
                    *pOut = GetTextAt_4c4f0(FUN_00b3d390(0x14));
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x010568b0  cSPToolStrategy::StartTool  (free __stdcall; self is the first argument)
// ---------------------------------------------------------------------------
// @ 0x010568b0
bool __stdcall StartTool_568b0(cSPToolStrategy* self, int nTarget, int nFlags)
{
    void* key;
    // Stop the charge timer on the held item.
    if (self->mpTargetItem != nullptr) {
        int obj = (int)self->mpTargetItem->vb8((const void*)0xb033b403);
        if (obj != 0) {
            FUN_00c389c0((void*)obj, 1, 0);
            FUN_00bc3110((void*)(obj + 0x6f0));
        }
    }

    // Drop the active object, then start a fresh one.
    GetActivePlanet();
    if (self->mpActiveObject != nullptr) {
        self->mpActiveObject->SetEnabled(0);
        IRefCounted* old = self->mpActiveObject;
        if (old != nullptr) {
            self->mpActiveObject = nullptr;
            old->AddRef();
        }
    }
    if (self->mpActiveObject == nullptr) {
        IRefCounted* fresh = (IRefCounted*)FUN_01050640(self);
        IRefCounted* old = self->mpActiveObject;
        if (fresh != old) {
            if (fresh != nullptr)
                fresh->v00();
            self->mpActiveObject = fresh;
            if (old != nullptr)
                old->AddRef();
        }
    }

    // Terrain / shield tool keys.
    key = self->GetToolKey();
    if (((int*)key)[0] == (int)g_16e1f94 &&
        ((int*)key)[1] == (int)g_16e1f98 &&
        ((int*)key)[2] == (int)g_16e1f9c) {
        void* editor = NounManager();
        FUN_00f67d90(editor);
        FUN_00c75630(editor);
        return true;
    }

    key = self->GetToolKey();
    if (((int*)key)[0] == (int)g_16e1ce8 &&
        ((int*)key)[1] == (int)g_16e1cec &&
        ((int*)key)[2] == (int)g_16e1cf0) {
        if (GetActivePlanet() != nullptr) {
            FUN_00c73cf0(self, 1);
            return true;
        }
    } else {
        key = self->GetToolKey();
        if (((int*)key)[0] == (int)g_16e1e2c &&
            ((int*)key)[1] == (int)g_16e1e30 &&
            ((int*)key)[2] == (int)g_16e1e34) {
            int obj = (int)self->mpTargetItem->vb8((const void*)0xb033b403);
            if (obj != 0) {
                FUN_00c389c0((void*)obj, 1, 1);
                FUN_00bc3130((void*)(obj + 0x6f0));
                return true;
            }
        } else {
            if (*(int*)self->GetToolKey() == (int)g_16e1d18) {
                int obj = (int)self->mpTargetItem->vb8((const void*)0xb033b403);
                if (obj != 0) {
                    FUN_00bfc470((void*)obj, 1);
                    FUN_00bc3130((void*)(obj + 0x6d0));
                    return true;
                }
            } else if (*(int*)self->GetToolKey() == (int)g_16e1d90) {
                void* server = MessageServer();
                int msg[3];
                SlotMessageConstruct(msg, 0x3c5dbc7);
                ((void(__fastcall*)(void*, int*, int))(*(void***)server)[5])(server, msg, 0);
                SlotMessageDestruct(msg);
                return true;
            } else if (*(int*)self->GetToolKey() == (int)g_16e2090) {
                void* obj = self->mpTargetItem;
                FUN_00b3d510(obj);
                FUN_00b71fb0(obj, 0);
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x01056160  cSPToolStrategy::CanUseTool (free; self is first argument)
// ---------------------------------------------------------------------------
// @ 0x01056160
bool __stdcall CanUseTool_56160(cSPToolStrategy* self, int nTarget, int* pOut)
{
    if (self == nullptr)
        return false;

    // Must have the UFO simulator and the player inventory.
    if (GetUFOSimulator() != nullptr) {
        void* game = GetUFOSimulator();
        void* inv = game != nullptr ? ((cSPSimulatorSpaceGame*)game)->GetPlayerInventory() : nullptr;
        if ((void*)(inv != nullptr ? (char*)inv + 0x34 : nullptr) != nullptr &&
            (char*)inv + 0x34 == (char*)self->mpTargetItem)
            ;
        if ((void*)(inv != nullptr ? (char*)inv + 0x34 : nullptr) == (void*)self->mpTargetItem)
            ;
    }

    // Placeholder body: delegate the validity checks to the error-event helpers.
    if (self->mpTargetItem == nullptr) {
        SetErrorEvent_527f0(self, 0xbf808149, nTarget);
        AppendScanResult_52880(pOut, (int*)4);
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x01056d30  cSPGetOutOfUFOToolStrategy::CanUseTool (free)
// ---------------------------------------------------------------------------
// @ 0x01056d30
bool __stdcall CanUseTool_56d30(cSPToolStrategy* self, int nTarget, int* pOut)
{
    if (!CanUseTool_56160(self, nTarget, pOut))
        return false;

    void* ctx = GetUniverseContext();
    void* planet = GetActivePlanet();
    if (ctx != nullptr)
        return false;

    void* game = GetUFOSimulator();
    void* inv = game != nullptr ? ((cSPSimulatorSpaceGame*)game)->GetPlayerInventory() : nullptr;
    if (inv == nullptr)
        return false;

    void* held = *(void**)((char*)inv + 0x34);
    Vec3 pos;
    Vec3* p = ((Vec3*(__fastcall*)(void*))(((void**)*(void**)held)[0xb]))(held);
    float radius = FUN_00c375d0(p);
    (void)planet;
    p = ((Vec3*(__fastcall*)(void*))(((void**)*(void**)held)[0xb]))(held);
    float dx = p->mX, dy = p->mY, dz = p->mZ;
    float dist = (float)fun_sqrt(dx * dx + dy * dy + dz * dz);
    void* gm = FUN_00c37360();
    float range = FUN_00fb7ba0(gm);
    if (GameDataBigCountList(NounManager(), (void*)0x24270c5) != 0)
        return false;

    void* game2 = GetUFOSimulator();
    void* inv2 = game2 != nullptr ? ((cSPSimulatorSpaceGame*)game2)->GetPlayerInventory() : nullptr;
    held = *(void**)((char*)inv2 + 0x34);
    Vec3* q = ((Vec3*(__fastcall*)(void*))(((void**)*(void**)held)[0xb]))(held);
    pos.mX = q->mX;
    pos.mY = q->mY;
    pos.mZ = q->mZ;
    if (FUN_00b7e3e0(PlanetModelGet())) {
        SetErrorEvent_527f0(self, 0x85af2a11, nTarget);
        if (pOut != nullptr) {
            *pOut = FUN_0104c4f0(FUN_00b3d390(0x15));
            return false;
        }
    } else {
        Vec3 r;
        (void)r;
        Vec3* sp = FUN_00b81630(PlanetModelGet(), &pos);
        pos.mX = sp->mX;
        pos.mY = sp->mY;
        pos.mZ = sp->mZ;
        void* child = FUN_00b894a0(PlanetModelGet(), &pos);
        if (child != nullptr && FUN_00bd9c00(child, &pos)) {
            SetErrorEvent_527f0(self, 0xadb2f40, nTarget);
            AppendScanResult_52880(pOut, (int*)0x16);
            return false;
        }
        if (range + 70.0f < dist - radius) {
            SetErrorEvent_527f0(self, 0xe8ee796f, nTarget);
            AppendScanResult_52880(pOut, (int*)0x17);
            return false;
        }
        void* app = AppSystem();
        if (!((bool(__fastcall*)(void*))(((void**)*(void**)app)[0x14]))(app) ||
            g_15b743d != 0) {
            return true;
        }
    }
    return false;
}
