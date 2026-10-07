// Slice s00cdbb10: SP::cTribeModeStrategy::HandleUIMessage (retail 0x00cdbd20).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same tribe-mode module as s00cdef00; no /EHsc:
// the Variant/ObjectXform temporaries get inline dtors without an EH frame).
// The handler belongs to the IWinProc base at +4 of cTribeModeStrategy, so asm offsets are
// relative to that subobject and calls on the strategy itself adjust this by -4.
#include "types.h"

#define VSLOT(n) virtual void _v##n();

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
struct Matrix3 { float m[9]; };

// SP::normalized_safe (0x00449c20) / SP::Matrix3FromFacingAndUp (0x0069b440)
Vector3* normalized_safe(Vector3* out, const Vector3& v);
Matrix3 Matrix3FromFacingAndUp(const Vector3& facing, const Vector3& up);

// Transform-update message (0x00434040 ctor).
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vector3  pos;
    float    scale;
    Matrix3  rot;
    XformMsg();
    void SetPosition_00571d40(const Vector3& v);
    void SetRotation(const Matrix3& m) { rot = m; flags |= 2; ++count; }
    void SetScale(float s)             { scale = s; ++count; }
};

// App::Variant-like 0x14-byte value: flags byte at +0x10.
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;
    uint16_t mType;
    Variant(void* p);                    // 0x00b19c80
    Variant(const int& v);               // 0x005bf350
    Variant(const uint32_t* key);        // 0x00b19970 (ResourceKey)
    void Destruct(bool reset);           // 0x0093db80
    ~Variant() { if (mFlags & 4) Destruct(false); }
};

struct ResourceKey { uint32_t instance, type, group; };

// Game object (cGameData-like interface): Cast at +0xb8, AddRef +0xbc, Release +0xc0.
struct cGameObject {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual const Vector3& GetPosition();                                   // +0x2c
    VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31)
    VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35) VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40) VSLOT(41)
    VSLOT(42) VSLOT(43) VSLOT(44) VSLOT(45)
    virtual void* Cast(uint32_t typeID);                                     // +0xb8
    virtual int AddRef();                                                    // +0xbc
    virtual int Release();                                                   // +0xc0
};
template <class T> __forceinline T* object_cast(cGameObject* p) { return p ? (T*)p->Cast(T::TYPE) : 0; }

struct cGameObjectPtr {
    cGameObject* mpObject;
    ~cGameObjectPtr() { if (mpObject) mpObject->Release(); }
};

// eastl::vector<T, sp_vector_allocator>
struct sp_vector_allocator {
    uint32_t mData[2];
    void deallocate(void* p) { if (((uint32_t*)p)[-1]) delete[] (char*)p; }
};
template <class T> struct SPVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    SPVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    static __forceinline void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    __forceinline ~SPVector()
    {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
};

// Object/transform holder handed to the UI layout scripts (0x30 bytes, ctor 0x00ad7a30, dtor 0x00ad7ad0).
__declspec(align(16)) struct cObjectXform {
    float mData[11];
    cGameObject* mpObject;
    cObjectXform(cGameObject* obj, int flags);
    ~cObjectXform();
};

struct cAnimRequest { uint32_t pad[3]; uint32_t mAnimA; uint32_t mAnimB; };
struct cAnimQueue { cAnimRequest* Play_00bc97f0(int a, int b, float blend, int c); };
struct cAnimatedCreature { uint32_t pad[2]; cAnimQueue mQueue; uint32_t pad2[(0x1d8 - 0xc) / 4]; uint32_t mModelType; };

struct cCreatureSub5a8 {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual void SetEnabled(int);                                            // +0x2c
};
struct cCreatureBase0 { virtual void _c0(); uint32_t pad[(0x5a8 - 4) / 4]; };
struct cCreature : cCreatureBase0, cCreatureSub5a8 {
    enum { TYPE = 0x4f176642 };
    uint32_t pad5ac[(0xb4c - 0x5ac) / 4];
    cAnimatedCreature* mpAnimatedCreature;                                   // +0xb4c
    bool IsIdle_00c24560();
    void f_00c26d10();
    void f_00c0b950();
    void f_00c0ba10();
};
void FUN_00c0d3a0(cCreature* c);

struct cTerrainCursor {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20)
    VSLOT(21) VSLOT(22)
    virtual void GetSelection(SPVector<cGameObjectPtr>& out);                // +0x5c
};
cTerrainCursor* GetGameTerrainCursor();                                      // 0x00b30d70

struct cAudioSystem { VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) virtual int GetState(); };
cAudioSystem* GetAudioSystem();                                              // 0x00a206f0
void KillSetiEffects(uint32_t id, int state);                                // 0x00435ed0
int GetRecorderState();                                                      // 0x00435e90

struct cPlanetRecord { uint32_t pad[0x504 / 4]; uint32_t mData504; };

// Hut/home object: spatial base at +0x34.
struct cHutBase0 { virtual void _h0(); uint32_t pad[12]; };
struct cHut : cHutBase0, cGameObject {};

struct cTribe {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20)
    VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24)
    virtual const Vector3& GetPosition();                                    // +0x64
    VSLOT(26) VSLOT(27) VSLOT(28) VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35)
    VSLOT(36) VSLOT(37) VSLOT(38) VSLOT(39) VSLOT(40)
    virtual int GetFoodAmount();                                             // +0xa4
    VSLOT(42)
    virtual cHut* GetTribeHut();                                             // +0xac

    uint32_t pad04[(0x120 - 4) / 4];
    cGameObject mObject120;                                                  // +0x120
    uint32_t pad124[(0x20c - 0x124) / 4];
    uint32_t mTimer20c[9];                                                   // +0x20c
    struct Sub230 { uint32_t mData0; uint32_t mData4; } mSub230;            // +0x230
    Sub230* GetSub230() { return &mSub230; }

    cPlanetRecord* GetRecord_00c8e820(int index);
    bool GetSpawnInfo_00c8eb50(ResourceKey* out);
    cHut* GetToolOfType(int type);                                           // 0x00c8f6e0
    cCreature* GetChieftain();                                               // 0x00c8fd30
    uint32_t GetPopulation_00c8f3a0();
    uint32_t GetMaxPopulation();                                             // 0x00c8eae0
    void AddFood_00c94b50(float amount);
};

struct cTerrainSphere {
    uint32_t pad[0x10f0 / 4];
    float mf10f0;
    float mf10f4;
    uint32_t mKey10f8;
    uint32_t pad10fc[2];
    uint32_t mResult1104;                                                    // +0x1104
    int GetState_00c75420();
};

struct cGameNounManager {
    cTerrainSphere* GetCurrentTerrainSphere();                               // 0x00f67d90
    cTribe* GetPlayerTribe();                                                // 0x00bfc5f0
};
cGameNounManager* NounManager();                                             // 0x00b3d300

struct cUIHints {
    void UpdateHints(int a, int b);                                          // 0x0067c350
    void ShowHint_0067c830(uint32_t id);
};
cUIHints* UIHints();                                                         // 0x0067cac0
struct cHintsB { void Set_0060d860(uint32_t id, ResourceKey* key); };
cHintsB* GetHintsB();                                                        // 0x0067cb30

struct cLayoutScripts {
    void SetObject_00ae09b0(uint32_t id, const cObjectXform& obj);
    void Run_00ae0930(const char* name, int a, int b, int c, int d, int e);
    void Reset_00adf390(int a);
};
cLayoutScripts* LayoutScripts();                                             // 0x00b3d4d0

struct cFoodSource { float Consume_00ac7d10(float amount, void* timer, int flags); };
cFoodSource* GetFoodSource();                                                // 0x00b3d2b0

struct cTerrainSource {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12)
    virtual void* GetTerrainObject();                                        // +0x34
    VSLOT(14)
    virtual void GetKey(ResourceKey* out, int flags);                        // +0x3c
};
cTerrainSource* GetTerrainSource();                                          // 0x00b3d240

struct cPropertyList {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual void SetValue(int index, const Variant& v);                      // +0x20
};
struct cPropListFactory {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void Create(cPropertyList** out);                                // +0x18
    VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16)
    VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20)
    virtual void Submit(uint32_t id, cPropertyList* list, int flags);        // +0x54
};
cPropListFactory* PropListFactory();                                         // 0x006895b0

struct cMessage {
    VSLOT(0)
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
    uint32_t pad04;
    uint32_t mData08;                                                        // +0x08
    uint32_t pad0c[(0x30 - 0xc) / 4];
    uint32_t mMessageID;                                                     // +0x30
    uint32_t pad34[3];
    cMessage(int a);                                                         // 0x00421c80
    void* operator new(size_t n, const char* name, int a, int b, int c, int d);
};
struct cMessagePtr {
    cMessage* mpMessage;
    cMessagePtr(cMessage* p);                                                // 0x0061df40
    ~cMessagePtr() { mpMessage->Release(); }
    cMessage* operator->() const { return mpMessage; }
};
struct cMessageServer {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4)
    virtual void SendMSG(uint32_t id, void* data, void* target);             // +0x14
    virtual void PostMSG(uint32_t id, cMessage* msg, void* a, void* b);      // +0x18
};
cMessageServer* MessageServer();                                             // 0x0067dcc0

struct IVisualEffect {
    VSLOT(0)
    virtual int Release();                                                   // +0x04
    virtual void Start(int flags);                                           // +0x08
    VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void SetTransform(const XformMsg& xf);                           // +0x18
};
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam();                                                     // 0x00a16f40
    T* operator->() const { return mpObject; }
};
struct cEffectsManager {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    virtual bool CreateVisualEffect(uint32_t id, int flags, IVisualEffect** out);  // +0x2c
};
cEffectsManager* EffectsManager();                                           // 0x0067ddd0

// Achievements
struct InsertResult { void* node; void* bucket; bool second; };
struct uint_hash_set {
    InsertResult insert_00675b60(const uint32_t& key);
    void clear();                                                            // 0x00675770
};
struct cAchievementData { uint32_t pad[0x60 / 4]; uint_hash_set mVisited; };
struct cAchievementsController {
    bool IsLocked_006766f0(uint32_t id);
    void AwardAchievement(uint32_t id);                                      // 0x00676710
    cAchievementData* GetData_00675370();
    bool Has_00675e80(uint32_t id);
    void AutoTest(uint32_t id, uint32_t value);                              // 0x00676e90
};
cAchievementsController* AchievementsController();                           // 0x00675250

struct cTribeCamera { void PlayIntro_00cd52e0(int kind, Vector3 pos); };
extern cTribeCamera* g_TribeCamera_0169b2c8;
extern Vector3 g_TribeCameraPos_0169b2cc;

struct cTribePlanner {
    void f_00cc8aa0(int);
    void f_00cc93b0(int);
};

struct cToggleable { VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) virtual void SetActive(int); };

bool IsVerbTrayCommand_00d49820(int cmd);
bool VerbTray_HandleRebuild(void* window, uint32_t data);                    // 0x00d4a570
void sToggleMinimap();                                                       // 0x00cd5200
int GetTribeOutcome_00cdba50();
void PlayEndSequence_00e398e0(uint32_t id, uint32_t* record, ResourceKey* pos, ResourceKey* dir, uint32_t data, int b, int c);
bool IsValidKey_006419f0(ResourceKey* key);
void SummarizeVehicle_00555f70(ResourceKey* key, uint32_t data);

extern float g_DropFoodAmount_0158133c;
extern const float kFoodEpsilon_01477434;
extern const float kAnimBlend_01486110;

struct UTFWinMessage {
    uint32_t pad[2];
    uint32_t mEventType;                                                     // +0x08
    int mCommandID;                                                          // +0x0c
    uint32_t pad10[2];
    uint32_t mData18;                                                        // +0x18
};

struct IWinProc {
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual bool HandleUIMessage(void* window, const UTFWinMessage& message) = 0;
};
struct cStrategyBase0 { virtual void _s0(); };

namespace SP {
class cTribeModeStrategy : public cStrategyBase0, public IWinProc {
public:
    // offsets below are absolute (subobject IWinProc at +4)
    uint32_t pad08[(0x78 - 8) / 4];
    uint32_t mData78;                                                        // +0x78  (IWinProc +0x74)
    uint32_t pad7c[(0x1a8 - 0x7c) / 4];
    struct Timer { uint32_t d[8]; void Stop(); } mTimer;                    // +0x1a8  (IWinProc +0x1a4)
    uint32_t pad1c8[(0x240 - 0x1c8) / 4];
    cTribePlanner* mpPlanner;                                                // +0x240  (IWinProc +0x23c)
    uint32_t pad244[(0x390 - 0x244) / 4];
    int mToolMode;                                                           // +0x390  (IWinProc +0x38c)
    cToggleable* mpToolUI;                                                   // +0x394  (IWinProc +0x390)
    uint32_t pad398[2];
    uint8_t pad3a0[3];
    bool mbFlag3a3;                                                          // +0x3a3  (IWinProc +0x39f)

    void SetMode_00cd6390(int);
    bool IsToolActive_00cd4460(uint32_t id);
    bool HandleUIMessage(void* window, const UTFWinMessage& message);
};
}
using SP::cTribeModeStrategy;

static __forceinline int GetAudioState()
{
    cAudioSystem* audio = GetAudioSystem();
    return audio ? audio->GetState() : 0;
}

// @ 0x00cdbd20
bool cTribeModeStrategy::HandleUIMessage(void* window, const UTFWinMessage& message)
{
    switch (message.mEventType) {
    case 0xd:
        if (VerbTray_HandleRebuild(window, message.mData18) == true)
            return true;
        break;
    case 0x287259f6:
        if (IsVerbTrayCommand_00d49820(message.mCommandID))
            return true;

    switch (message.mCommandID) {
    case 0x4c61b50: {
        KillSetiEffects(0x381d5506, GetAudioState());
        mToolMode = 0;
        if (mpToolUI)
            mpToolUI->SetActive(0);
        cTerrainCursor* cursor = GetGameTerrainCursor();
        if (cursor) {
            SPVector<cGameObjectPtr> selection;
            cursor->GetSelection(selection);
            for (cGameObjectPtr* it = selection.begin(); it != selection.end(); ++it) {
                cCreature* creature = object_cast<cCreature>(it->mpObject);
                if (creature && creature->IsIdle_00c24560()) {
                    cAnimRequest* req = creature->mpAnimatedCreature->mQueue.Play_00bc97f0(0, 8, kAnimBlend_01486110, 0);
                    req->mAnimA = 0x55bb346;
                    req->mAnimB = 0x55bb34b;
                }
            }
        }
        return true;
    }
    case 0x36ad4a4: {
        mTimer.Stop();
        SetMode_00cd6390(0);
        if (IsToolActive_00cd4460(0x64be5ff) && !IsToolActive_00cd4460(0x56d1871))
            return true;
        cMessagePtr msg(new("App", 0, 0, 0, 0) cMessage(0));
        msg->mMessageID = 0xb2699146;
        msg->mData08 = 0;
        MessageServer()->PostMSG(msg->mMessageID, msg.mpMessage, 0, 0);
        return true;
    }
    case 0x4c61dd9: {
        KillSetiEffects(0x99a5b10f, GetAudioState());
        mToolMode = 1;
        if (mpToolUI)
            mpToolUI->SetActive(0);
        cTerrainCursor* cursor = GetGameTerrainCursor();
        if (cursor) {
            SPVector<cGameObjectPtr> selection;
            cursor->GetSelection(selection);
            for (cGameObjectPtr* it = selection.begin(); it != selection.end(); ++it) {
                cCreature* creature = object_cast<cCreature>(it->mpObject);
                if (creature && creature->IsIdle_00c24560()) {
                    cAnimRequest* req = creature->mpAnimatedCreature->mQueue.Play_00bc97f0(0, 8, kAnimBlend_01486110, 0);
                    req->mAnimA = 0x55bb337;
                    req->mAnimB = 0x55bb341;
                }
            }
        }
        return true;
    }
    case 0x53f02b8: {
        cPropListFactory* factory = PropListFactory();
        cPropertyList* list;
        factory->Create(&list);
        Variant terrain(GetTerrainSource()->GetTerrainObject());
        list->SetValue(0, terrain);
        int enable = 1;
        list->SetValue(1, Variant(enable));
        ResourceKey key;
        GetTerrainSource()->GetKey(&key, 0);
        list->SetValue(3, Variant(&key.instance));
        factory->Submit(0x1aedf1e, list, 0);
        return true;
    }
    case 0x53f02c0: {
        cPropListFactory* factory = PropListFactory();
        cPropertyList* list;
        factory->Create(&list);
        Variant terrain(GetTerrainSource()->GetTerrainObject());
        list->SetValue(0, terrain);
        int enable = 0;
        list->SetValue(1, Variant(enable));
        ResourceKey key;
        GetTerrainSource()->GetKey(&key, 0);
        list->SetValue(3, Variant(&key.instance));
        factory->Submit(0x1aedf1e, list, 0);
        return true;
    }
    case 0x562a141:
        sToggleMinimap();
        return true;
    case 0x625cd52: {
        float amount = g_DropFoodAmount_0158133c;
        cTribe* tribe = NounManager()->GetPlayerTribe();
        int needed = (int)amount;
        if (tribe->GetFoodAmount() < needed) {
            UIHints()->ShowHint_0067c830(0x41e5e8bf);
            return true;
        }
        if (tribe->GetPopulation_00c8f3a0() >= tribe->GetMaxPopulation())
            return true;
        if (amount > kFoodEpsilon_01477434) {
            GetFoodSource()->Consume_00ac7d10(amount, tribe->mTimer20c, 0);
            tribe->AddFood_00c94b50(-amount);
        }
        cHut* hut = tribe->GetTribeHut();
        AutoRefCount<IVisualEffect> effect;
        cEffectsManager* effects = EffectsManager();
        if (effects->CreateVisualEffect(0xdb6f2233, 0, effect.AsPPTypeParam())) {
            XformMsg xf;
            xf.SetPosition_00571d40(hut->GetPosition());
            Vector3 up;
            normalized_safe(&up, hut->GetPosition());
            const Vector3& hutPos = hut->GetPosition();
            const Vector3& tribePos = tribe->GetPosition();
            Vector3 facing;
            normalized_safe(&facing, tribePos - hutPos);
            xf.SetRotation(Matrix3FromFacingAndUp(facing, up));
            xf.SetScale(1.0f);
            effect->SetTransform(xf);
            effect->Start(0);
        }
        KillSetiEffects(0x582f38c1, GetRecorderState());
        mbFlag3a3 = false;
        return true;
    }
    case 0x6454b47: {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        const float& a = sphere->mf10f0;
        const float& b = sphere->mf10f4;
        const float& lo = (b < a) ? b : a;
        if (!(lo / sphere->mf10f4 >= 1.0f))
            return true;
        UIHints()->UpdateHints(1, 1);

        uint32_t sequence = 0x8133fb2e;
        switch (GetTribeOutcome_00cdba50()) {
        case 0xcac124d:
            sequence = 0x6a9f2620;
            break;
        case 0x60a78928:
            sequence = 0x2cfa39dd;
            break;
        }
        {
            ResourceKey dir = {0, 0, 0};
            ResourceKey pos = {0, 0, 0};
            PlayEndSequence_00e398e0(sequence,
                                     &NounManager()->GetPlayerTribe()->GetRecord_00c8e820(0)->mData504,
                                     &pos, &dir, NounManager()->GetPlayerTribe()->GetSub230()->mData4, 0, 0);
        }

        cAchievementsController* ach = AchievementsController();
        if (ach->IsLocked_006766f0(0xb598f829))
            ach->AwardAchievement(0xb598f829);
        cAchievementData* data = ach->GetData_00675370();
        if (ach->Has_00675e80(0xa6c22573))
            data->mVisited.clear();
        else if (data->mVisited.insert_00675b60(sphere->mKey10f8).second == true)
            ach->AutoTest(0xa6c22573, 1);
        ach->AwardAchievement(0x4a7480ac);
        ach->AutoTest(0xa784ec4a, mData78);
        if (NounManager()->GetCurrentTerrainSphere()->GetState_00c75420() == 2)
            ach->AwardAchievement(0x8d82fac1);

        g_TribeCamera_0169b2c8->PlayIntro_00cd52e0(5, g_TribeCameraPos_0169b2cc);

        ResourceKey spawn = {0, 0, 0};
        NounManager()->GetPlayerTribe()->GetSpawnInfo_00c8eb50(&spawn);
        GetHintsB()->Set_0060d860(0x8fd1273c, &spawn);
        mpPlanner->f_00cc8aa0(0);
        mpPlanner->f_00cc93b0(0);

        cTribe* tribe = NounManager()->GetPlayerTribe();
        cHut* hut = tribe->GetTribeHut();
        cHut* tool = tribe->GetToolOfType(0xa);
        LayoutScripts()->SetObject_00ae09b0(0x3d7f90a, cObjectXform(&tribe->mObject120, 0));
        LayoutScripts()->SetObject_00ae09b0(0xaa227986, cObjectXform(hut, 0));
        LayoutScripts()->SetObject_00ae09b0(0x60ed02ef, cObjectXform(tool, 0));
        LayoutScripts()->Run_00ae0930("TRG2CVG_PreEditor", 1, 0, 0, 0, 0);
        LayoutScripts()->Reset_00adf390(0);

        cCreature* chief = tribe->GetChieftain();
        if (chief->mpAnimatedCreature->mModelType == 0x5ca7fa7) {
            FUN_00c0d3a0(chief);
            chief->f_00c26d10();
        }
        chief->SetEnabled(1);
        chief->f_00c0b950();
        chief->f_00c0ba10();
        sphere->mResult1104 = GetTribeOutcome_00cdba50();

        ResourceKey key = {0, 0, 0};
        if (!tribe->GetSpawnInfo_00c8eb50(&key))
            return true;
        if (!IsValidKey_006419f0(&key))
            return true;
        if (uint32_t result = NounManager()->GetCurrentTerrainSphere()->mResult1104)
            SummarizeVehicle_00555f70(&key, result);
        MessageServer()->SendMSG(0x73e46f6, &key, 0);
        return true;
    }
    }
        break;
    }
    return false;
}
