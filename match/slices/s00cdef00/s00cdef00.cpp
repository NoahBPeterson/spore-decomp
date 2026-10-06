// Slice s00cdef00: SP::cTribeModeStrategy::HandleSimulationUpdate (retail 0x00cdef00).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (inline fsqrt needs /fp:fast; x87 for uint->float).
// Retail layout of cTribeModeStrategy differs from the 2008 PDB; offsets below are from the asm.
#include "types.h"
#include <math.h>

// ------------------------------------------------------------------ helpers
// float->int with the current MXCSR rounding (asm helper in the original).
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

// SSE min helper (minss), as used by the /arch:SSE modules.
inline float MinF(float a, float b)
{
    __asm {
        movss xmm0, a
        minss xmm0, b
        movss a, xmm0
    }
    return a;
}

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    void Normalize_00fb8db0();
};
struct Vector4 { float x, y, z, w; };
struct Matrix3 { Vector3 r[3]; };
struct BoundingBox { Vector3 lower, upper; };

// App::Property (0x14 bytes): data union, flags byte at +0x10, type at +0x12.
struct Property {
    uint32_t mData[4];
    uint8_t  mFlags;      // +0x10
    uint8_t  pad11;
    uint16_t mType;       // +0x12
    const char* GetValueBool() const { return (mFlags & 0x30) ? *(const char* const*)mData : (const char*)mData; }
};
struct PropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
extern PropertyList* gDebugProps_01581288;
extern PropertyList* gTribeTuning_0158128c;
float GetPropertyFloat_004e1c70(PropertyList* list, uint32_t id, float def);   // SP::GetPropertyT<float>

inline bool GetDebugBool(uint32_t id, Property*& prop)
{
    return gDebugProps_01581288 && gDebugProps_01581288->GetProperty(id, prop) &&
           prop->mType == 1 && *prop->GetValueBool();
}

struct cSPTimer {
    uint32_t data[8];
    bool IsRunning_00feba90();
    uint64_t GetElapsedTime_00bc3190();
    void Stop_00bc3170();
};

struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};

// Tribe member / citizen (retail cCreatureCitizen).
struct cCitizen {
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool IsDead();                    // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44();
    virtual void SetTarget(int);              // +0x48
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void Update(int ms);              // +0x60

    char pad[0x135 - 4];
    bool mbActive;                            // +0x135
    char pad136[0xb58 - 0x136];
    uint32_t mFlags;                          // +0xb58
    char padb5c[2];
    bool mbBusy;                              // +0xb5e

    void f_00c1d5e0(int, uint32_t, uint32_t);     // 0x00c1d5e0
    void f_00c0b370(int);                         // 0x00c0b370
    void f_00c17350(uint32_t, int);               // 0x00c17350
    void* f_00c04590();                           // 0x00c04590
    void f_00c042e0();                            // 0x00c042e0
    void f_00c14750(int);                         // 0x00c14750
};
void FUN_00c0d3a0(cCitizen* c);

template <class T> struct AutoRefCount {
    T* p;
    void Swap_00ac9480(AutoRefCount& other);
    ~AutoRefCount() { if (p) p->Release(); }
};

struct CitizenVector {   // eastl::vector<AutoRefCount<cCitizen>>
    AutoRefCount<cCitizen>* mpBegin;
    AutoRefCount<cCitizen>* mpEnd;
    AutoRefCount<cCitizen>* mpCapacity;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    void pop_back() { --mpEnd; mpEnd->~AutoRefCount<cCitizen>(); }
    AutoRefCount<cCitizen>* erase_00e25bd0(AutoRefCount<cCitizen>* first, AutoRefCount<cCitizen>* last);
};

template <class T> struct PtrVector {
    T** mpBegin; T** mpEnd; T** mpCapacity;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct cTribeTools { char pad[0x40]; PtrVector<void> mTools; };   // +0x40

struct cTribeSub120 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void* v2c(float a, float b);      // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsDestroyed();               // +0x58
};

struct cSpatialSub {   // object at +0xc0 of a tribe member
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector3* GetDirection();          // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual bool IsVisible();                 // +0x48
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual BoundingBox GetBoundingBox();     // +0x6c
    virtual float GetBoundingRadius();        // +0x70
    Vector3* GetVelocity_00d20610();
};
struct cMember { char pad[0xc0]; cSpatialSub mSpatial; };

struct cTribe {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int GetPoliticalID();             // +0x4c
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual PtrVector<cMember>* GetMembers(); // +0x90

    char pad04[0x120 - 4];
    cTribeSub120 mSub;                        // +0x120
    char pad124[0x2bc - 0x124];
    int   mRelationship;                      // +0x2bc
    float mFoodAccum;                         // +0x2c0
    char pad2c4[0x556 - 0x2c4];
    bool  mbSkipUpdate;                       // +0x556

    cTribeTools* f_00c8fee0();                    // 0x00c8fee0
    cCitizen* GetLeader_00c00650();
    static void HotSpotsUpdate_00c9b740(float dt);
};
void FUN_00ba58e0(cTribe* tribe, int v);

struct cGameDataVector { void* vt; PtrVector<void> mData; };
struct cGameNounManager {
    cTribe* GetPlayerTribe_00bfc5f0();
    cGameDataVector* GetGameDataVector_00b21340(void* f0, void* f1, void* f2, void* f3, uint32_t type);
};
cGameNounManager* NounManager_00b3d300();

extern "C" void FUN_00cd7d10(); extern "C" void FUN_00d3d420(); extern "C" void FUN_00accbb0();
extern "C" void FUN_00b1e500(); extern "C" void FUN_00b1e520(); extern "C" void FUN_00cdb110();
extern "C" void FUN_00accc30(); extern "C" void FUN_00cdb620();

struct cHerd { bool f_00c6a020(); void Update_00c6d7c0(int ms); };
struct cAnimalTrap { void f_00bcc230(int ms); };
struct cRefObj {
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c();
    virtual void Update(int ms);              // +0x60
    char pad[0x135 - 4];
    bool mbActive;                            // +0x135
};

struct cMessageServer { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
                        virtual void PostMessage(uint32_t id, void* a, void* b); };   // +0x14
cMessageServer* MessageServer_0067dcc0();
struct cConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c();
    virtual void* GetSetting(uint32_t id);     // +0x30
};
cConfigManager* ConfigManager_0067dd30();

struct cGameTimeManager {
    char pad[0x48]; uint8_t mFlags;            // +0x48
    void IncPauseGate_00b32220(uint32_t id);
    int  GetPauseGateCount_00b320d0(uint32_t id);
    void DecPauseGate_00b32250(uint32_t id);
    int  f_00b31c60(int ms);                       // 0x00b31c60: scaled game time
};
cGameTimeManager* GameTimeManager_00b3d380();
struct cGameInputManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual bool IsMouseButtonDown(int b);     // +0x18
    char pad[0x110 - 4];
    int mPauseCount;                           // +0x110
};
cGameInputManager* GameInputManager_00b3d250();

struct cCameraController {
    char pad[0x390]; bool field_390;
    Vector3* GetAnchorDirection0_00b10200();
    void f_00b14520(Vector3* dir, Vector3* vel);
};
cCameraController* FUN_00b3d280();
float Dot3_004885d0(const Vector3* v);

struct cSimState { char pad[0x28]; bool mbSkip; };
cSimState* FUN_00b3d320();
struct cGameModeState { char pad[0x2c]; int mState; };
cGameModeState* FUN_00b3d4d0();
struct cSubsysB5e { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
                    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
                    virtual void v28(); virtual void Update2c(int ms); virtual void Update30(int ms);
                    void f_00b5e9a0(int ms); };
cSubsysB5e* FUN_00b3d230();
void* GetCurrentGameMode_00b5b800();
extern char DAT_01654c02;

struct cUIHints { void UpdateHints_0067c350(int a, int b); };
cUIHints* FUN_0067cac0();
struct cMissionLog { void f_00e2f270(int); };
cMissionLog* FUN_00b3d4f0();
struct cMusic { void f_00b700f0(uint32_t id); };
struct cTimeline { void f_00acc700(void* v); };
cTimeline* FUN_00b3d480();
struct cRelationshipManager { int f_00d00a70(int a, int b, int c); };
cRelationshipManager* RelationshipManager_00b3d2c0();
struct cEventLog { void PostFeedbackEvent_00dd8640(uint32_t a, uint32_t b, int c, int d, int e, int f); };
cEventLog* EventLog_00b3d3e0();
struct cTribeHud { char pad[0x1c]; void* mpLastTribe; };
extern cTribeHud* gTribeHud_0169b41c;
void FUN_01022920(int ms);

struct cCastable {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void* Cast(uint32_t id);           // +0x14
};
struct cCastTarget { void f_00c36ae0(float dt); };
struct cB3d2b0 { cCastable* f_00ac79d0(); };
cB3d2b0* FUN_00b3d2b0();

struct cCommunityEditor { void HandleSimulationUpdate_00d124e0(int ms); bool f_00d09660(); };
struct cInputStrategy { char pad[0x5c]; cCommunityEditor* mpEditor; void f_00cceca0(int, int); void f_00ccff40(); };
struct cDisplayStrategy { void UpdateUI_00cc99b0(int ms); void f_00ccdc30(int, int, int); void f_00cc9620(); void f_00cc9cd0(int); };

struct cAudioListener {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void Commit();                     // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void SetUp(const Vector3* v);      // +0x30
    virtual void v34();
    virtual void SetOrientation(const Vector3* dir, const Vector3* n);  // +0x38
    virtual void SetTransform(const Vector4* v);   // +0x3c
};
cAudioListener* FUN_0067ddc0();

struct cCameraTransform { uint16_t a, b; Vector4 pos; Matrix3 rot; };
struct cCamera { void f_007c40f0(cCameraTransform* t); };   // 0x007c40f0
struct cCameraObj { char pad[0x54]; Vector3 mDirection; };
struct cCameraLookup { virtual void v00(); virtual void v04(); virtual void v08();
                       virtual cCameraObj* Find(uint32_t id); };           // +0x0c
struct cCameraMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18();
    virtual cCamera* GetActiveCamera();        // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34();
    virtual cCameraLookup* GetActiveController();  // +0x38
    virtual uint32_t GetActiveControllerID();  // +0x3c
};
struct cApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual cCameraMgr* GetCameraManager();    // +0x50
};
cApp* App_0067dd10();
extern Vector3 gCameraPos_0169b2cc;
extern Matrix3 gCameraRot_0169b378;

struct cPlanetSub { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                    virtual Vector3 GetUp(); };   // +0x10 (sret)
struct cPlanetModel { char pad[0x24]; cPlanetSub* mpSub; };
cPlanetModel* PlanetModel_00b3d350();

struct cHotSpots { void f_00b76d20(const Vector3* pos, float radius, int a, int b, int c); };
cHotSpots* FUN_00b3d3c0();
struct cTerrainSphere { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                        virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
                        virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
                        virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
                        virtual void v40();
                        virtual Vector3 GetCenter(int);   // +0x44 (sret)
};
cTerrainSphere* FUN_00b3d240();
void FUN_00b6dbd0(float dt);

struct cTribeModeStrategy {
    char pad0[0x58];
    cSPTimer mTimerA;                          // +0x58
    int  mGameTimeMs;                          // +0x78
    char pad7c[0x94 - 0x7c];
    CitizenVector mSelected;                   // +0x94
    char pada0[0x1a0 - 0xa0];
    float mSelectTimer;                        // +0x1a0
    bool  mbTutorialHint;                      // +0x1a4
    char  pad1a5[3];
    cSPTimer mTimerB;                          // +0x1a8
    char pad1c8[0x22c - 0x1c8];
    int   mState;                              // +0x22c
    char pad230[0x238 - 0x230];
    int   mWaitFrames;                         // +0x238
    cInputStrategy*   mpInputStrategy;         // +0x23c
    cDisplayStrategy* mpDisplayStrategy;       // +0x240
    char pad244[0x250 - 0x244];
    cCitizen* mpTracked;                       // +0x250 (vtable +0x2c, spatial at +0xc0)
    char pad254[0x394 - 0x254];
    cMusic* mpMusic;                           // +0x394

    void IncrementGoalProgress_00cdab10();
    bool f_00cd4460(uint32_t id);
    static void f_00cd3fb0(uint32_t id);
    void f_00cd6390(int);
    void f_00cd4b70(int);
    void f_00cde660(int ms);
    void HandleSimulationUpdate(float dtReal, float dtGame);
};

// @ 0x00cdef00
void cTribeModeStrategy::HandleSimulationUpdate(float dtReal, float dtGame)
{
    int msGame = RoundToInt(dtGame * 1000.0f);
    int msReal = RoundToInt(dtReal * 1000.0f);

    if (FUN_00b3d320()->mbSkip) {
        FUN_00b3d230()->f_00b5e9a0(msGame);
        return;
    }
    if (GetCurrentGameMode_00b5b800() != &DAT_01654c02)
        return;
    if (mState != 0xb) {
        mWaitFrames++;
        f_00cde660(msGame);
        return;
    }

    if (mTimerA.IsRunning_00feba90() && mTimerA.GetElapsedTime_00bc3190() > 60000) {
        MessageServer_0067dcc0()->PostMessage(0x445f729, 0, 0);
        IncrementGoalProgress_00cdab10();
    }
    if (mTimerB.IsRunning_00feba90() && mTimerB.GetElapsedTime_00bc3190() > 1000) {
        mTimerB.Stop_00bc3170();
        if (ConfigManager_0067dd30()->GetSetting(0x4ea96cb) &&
            ConfigManager_0067dd30()->GetSetting(0x5b5bb5e) && !f_00cd4460(0x56d1871))
            { cGameTimeManager* gtm = GameTimeManager_00b3d380(); gtm->IncPauseGate_00b32220(0x64beb65); }
    }
    if (mpDisplayStrategy)
        mpDisplayStrategy->UpdateUI_00cc99b0(msGame);
    mpInputStrategy->f_00cceca0(0, 0);

    if (!f_00cd4460(0x56d1871)) {
        bool noA = ConfigManager_0067dd30()->GetSetting(0x4ea96cb) == 0;
        if (!ConfigManager_0067dd30()->GetSetting(0x5b5bb5e) || noA) {
            f_00cd3fb0(0x56d1871);
            mbTutorialHint = false;
            FUN_0067cac0()->UpdateHints_0067c350(1, 1);
            f_00cd6390(0);
            if (FUN_00b3d280())
                FUN_00b3d280()->field_390 = false;
            cGameTimeManager* gtm = GameTimeManager_00b3d380();
            if (gtm->GetPauseGateCount_00b320d0(0x64beb65) > 0) {
                gtm = GameTimeManager_00b3d380();
                gtm->DecPauseGate_00b32250(0x64beb65);
                GameInputManager_00b3d250()->mPauseCount--;
            }
            FUN_00b3d4f0()->f_00e2f270(0);
            mpMusic->f_00b700f0(0x11ade9ce);
            mpMusic->f_00b700f0(0x69ba7f0d);
            mpMusic->f_00b700f0(0x391c432);
            mpMusic->f_00b700f0(0x2d99d0b);
            mpMusic->f_00b700f0(0x5312da01);
            mpMusic->f_00b700f0(0x9a44d4ab);
            mpMusic->f_00b700f0(0x7d7315c8);
        }
    }

    cGameInputManager* input = GameInputManager_00b3d250();
    if (input && (input->IsMouseButtonDown(1) || input->IsMouseButtonDown(2) ||
                  input->IsMouseButtonDown(3) || input->IsMouseButtonDown(4)))
        f_00cd4b70(0);

    if (mpTracked) {
        if (mpTracked->IsDead()) {
            f_00cd4b70(0);
        } else {
            cCameraController* cam = FUN_00b3d280();
            if (cam) {
                cSpatialSub* sp = &((cMember*)mpTracked)->mSpatial;
                Vector3* dir = sp->GetDirection();
                if (Dot3_004885d0(dir) > 0.0f)
                    cam->f_00b14520(dir, (&((cMember*)mpTracked)->mSpatial)->GetVelocity_00d20610());
            }
        }
    }

    cGameNounManager* nouns = NounManager_00b3d300();
    cTribe* playerTribe = nouns->GetPlayerTribe_00bfc5f0();
    if (playerTribe)
        FUN_00b3d480()->f_00acc700(playerTribe->mSub.v2c(75.0f, 112.5f));

    int gameMs = GameTimeManager_00b3d380()->f_00b31c60(msGame);
    FUN_00b3d230()->Update2c(msGame);
    float dt = (float)(uint32_t)gameMs * 0.001f;
    playerTribe->GetPoliticalID();

    PtrVector<void>& tribes = nouns->GetGameDataVector_00b21340(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00accbb0, (void*)FUN_00b1e500,
        0x18c6d19)->mData;
    for (void** it = tribes.mpBegin; it != tribes.mpEnd; ++it) {
        cTribe* tribe = (cTribe*)*it;
        if (!tribe->mSub.IsDestroyed() && !tribe->mbSkipUpdate) {
            int rel = RelationshipManager_00b3d2c0()->f_00d00a70(
                tribe->GetPoliticalID(), NounManager_00b3d300()->GetPlayerTribe_00bfc5f0()->GetPoliticalID(), 1);
            if (tribe->mRelationship != rel && tribe->mRelationship != -1) {
                switch (rel) {
                case 0:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1217, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                case 1:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1216, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                case 2:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1215, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                case 3:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1214, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                case 4:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1213, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                }
                if (!tribe->mbSkipUpdate)
                    FUN_00ba58e0(tribe, 5);
            }
            tribe->mRelationship = rel;
        }
        cTribeTools* tools = tribe->f_00c8fee0();
        if (tools && (uint32_t)gameMs > 0) {
            float rate = GetPropertyFloat_004e1c70(gTribeTuning_0158128c, 0x78dcad72, 0.0125f);
            float cap = GetPropertyFloat_004e1c70(gTribeTuning_0158128c, 0xad06ca38, 20.0f);
            uint32_t n = tools->mTools.size();
            float v = (float)n * rate * dt + tribe->mFoodAccum;
            tribe->mFoodAccum = MinF(v, cap);
        }
    }

    if (!(GameTimeManager_00b3d380()->mFlags & 1)) {
        FUN_01022920(gameMs);
        CitizenVector& sel = mSelected;
        if (sel.mpBegin != sel.mpEnd) {
            mSelectTimer -= dt;
            FUN_00b3d480();
            cCitizen* leader = playerTribe->GetLeader_00c00650();
            if (mSelectTimer > 0.0f && !leader->mbBusy) {
                for (uint32_t i = 0; i < sel.size(); i++) {
                    cCitizen* c = sel.mpBegin[i].p;
                    if (!c->mbBusy && c->mbActive && !c->IsDead()) {
                        c->f_00c1d5e0(1, 0xadff412, 0xadff412);
                    } else {
                        c->SetTarget(-1);
                        c->f_00c0b370(-1);
                        sel.mpBegin[i].Swap_00ac9480(sel.mpBegin[sel.size() - 1]);
                        c->mFlags &= ~0x4000;
                        sel.pop_back();
                        c->f_00c17350(0xadff412, 0);
                    }
                }
                leader->f_00c1d5e0(sel.mpBegin != sel.mpEnd, 0x1d491515, 0x1d491515);
            } else {
                void* home = playerTribe->f_00c8fee0();
                for (uint32_t i = 0; i < sel.size(); i++) {
                    cCitizen* c = sel.mpBegin[i].p;
                    if (c->mbActive && !c->IsDead()) {
                        FUN_00c0d3a0(c);
                        if (c->f_00c04590() != home)
                            c->SetTarget(-1);
                        c->mFlags &= ~0x4000;
                        c->f_00c042e0();
                        c->f_00c0b370(-1);
                        c->f_00c14750(1);
                        c->f_00c17350(0xadff412, 0);
                    }
                }
                leader->f_00c17350(0x1d491515, 0);
                sel.erase_00e25bd0(sel.mpBegin, sel.mpEnd);
            }
        } else {
            mSelectTimer = 0.0f;
        }

        nouns = NounManager_00b3d300();
        PtrVector<void>& objs = nouns->GetGameDataVector_00b21340(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00cdb110, (void*)FUN_00b1e520, 0xce9f6639)->mData;
        uint32_t count = objs.size();
        for (uint32_t i = 0; i < count; i++) {
            cRefObj* o = (cRefObj*)objs.mpBegin[i];
            if (o) {
                o->AddRef();
                if (o->mbActive)
                    o->Update(gameMs);
                o->Release();
            }
        }

        nouns = NounManager_00b3d300();
        PtrVector<void>& herds = nouns->GetGameDataVector_00b21340(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00accc30, (void*)FUN_00b1e500, 0x1be418e)->mData;
        for (void** it = herds.mpBegin; it != herds.mpEnd; ++it) {
            cHerd* h = (cHerd*)*it;
            if (h->f_00c6a020())
                h->Update_00c6d7c0(gameMs);
        }

        nouns = NounManager_00b3d300();
        PtrVector<void>& traps = nouns->GetGameDataVector_00b21340(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00cdb620, (void*)FUN_00b1e500, 0x61494be)->mData;
        for (void** it = traps.mpBegin; it != traps.mpEnd; ++it)
            ((cAnimalTrap*)*it)->f_00bcc230(gameMs);

        if (FUN_00b3d2b0()->f_00ac79d0()) {
            cCastable* c = FUN_00b3d2b0()->f_00ac79d0();
            cCastTarget* t = c ? (cCastTarget*)c->Cast(0xeef202b7) : 0;
            t->f_00c36ae0(dt);
        }
        mGameTimeMs += gameMs;
    }

    cCommunityEditor* editor = mpInputStrategy->mpEditor;
    if (editor && editor->f_00d09660())
        mpInputStrategy->mpEditor->HandleSimulationUpdate_00d124e0(msGame);

    if (FUN_0067ddc0()) {
        Vector3 dir;
        bool have = false;
        cCameraController* cam = FUN_00b3d280();
        if (cam) {
            dir = *cam->GetAnchorDirection0_00b10200();
            have = true;
        } else if (App_0067dd10()->GetCameraManager()->GetActiveControllerID() == 0x8916f92d) {
            cCameraLookup* ctl = App_0067dd10()->GetCameraManager()->GetActiveController();
            if (ctl) {
                cCameraObj* o = ctl->Find(0x7ba6612);
                if (o) {
                    dir = o->mDirection;
                    have = true;
                }
            }
        }
        if (have) {
            float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + 1e-08f);
            Vector3 n(inv * dir.x, dir.y * inv, dir.z * inv);
            FUN_0067ddc0()->SetOrientation(&dir, &n);
        }

        cCamera* camera = App_0067dd10()->GetCameraManager()->GetActiveCamera();
        if (camera) {
            cCameraTransform t;
            t.pos.x = gCameraPos_0169b2cc.x;
            t.pos.y = gCameraPos_0169b2cc.y;
            t.pos.z = gCameraPos_0169b2cc.z;
            t.pos.w = 1.0f;
            t.a = 0;
            t.b = 0;
            t.rot.r[0] = gCameraRot_0169b378.r[0];
            t.rot.r[1] = gCameraRot_0169b378.r[1];
            t.rot.r[2] = gCameraRot_0169b378.r[2];
            camera->f_007c40f0(&t);
            FUN_0067ddc0()->SetTransform(&t.pos);
        }
        Vector3 up = PlanetModel_00b3d350()->mpSub->GetUp();
        up.Normalize_00fb8db0();
        FUN_0067ddc0()->SetUp(&up);
        FUN_0067ddc0()->Commit();
    }

    if (mpDisplayStrategy) {
        mpDisplayStrategy->f_00ccdc30(0, msGame, msReal);
        mpDisplayStrategy->f_00cc9620();
        mpDisplayStrategy->f_00cc9cd0(msGame);
    }

    if (FUN_00b3d3c0()) {
        int st = FUN_00b3d4d0()->mState;
        if (st != 1 && st != 2) {
            cHotSpots* hs = FUN_00b3d3c0();
            Property* prop;
            if (GetDebugBool(0x7a3da342, prop)) {
                PtrVector<cMember>* members = (PtrVector<cMember>*)playerTribe->GetMembers();
                uint32_t n = members->size();
                for (uint32_t i = 0; i < n; i++) {
                    cSpatialSub* sp = &members->mpBegin[i]->mSpatial;
                    if (sp->IsVisible()) {
                        BoundingBox bb = sp->GetBoundingBox();
                        Vector3 c((bb.lower.x + bb.upper.x) * 0.5f, (bb.upper.y + bb.lower.y) * 0.5f,
                                  (bb.upper.z + bb.lower.z) * 0.5f);
                        hs->f_00b76d20(&c, sp->GetBoundingRadius(), 1, 1, 0);
                    }
                }
            }
            Vector3 center = gCameraPos_0169b2cc;
            if (GetDebugBool(0x965f10f9, prop))
                center = *FUN_00b3d280()->GetAnchorDirection0_00b10200();
            else
                center = FUN_00b3d240()->GetCenter(1);
            hs->f_00b76d20(&center, 1.0f, 1, 0, 1);
        }
    }

    cTribe::HotSpotsUpdate_00c9b740(dtReal);
    FUN_00b3d230()->Update30(msGame);
    mpInputStrategy->f_00ccff40();
    FUN_00b6dbd0(dtGame);
    FUN_00b3d230()->f_00b5e9a0(msGame);
}
