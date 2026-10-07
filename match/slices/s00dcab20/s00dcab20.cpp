// slice s00dcab20: SP::VehicleTree::HarvestResourceOrder_Tick (space-stage / civ vehicle behavior tree:
// harvest spice from a geyser (mpMineral) or a tribe hut target (mpTribe)).
// No EH frame although string/AutoRefCount locals have dtors: built without /EHsc.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

#define PV(n) virtual void pad##n();

struct Vector3 {
    float x, y, z;
};
struct Quaternion {
    float x, y, z, w;
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// eastl::basic_string<wchar_t>
extern wchar_t gEmptyString16[];        // 0x01667bac
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      mAllocator;
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();                                       // 0x00933960
    string16& sprintf(const wchar_t* fmt, ...);                  // 0x0041e050
    const wchar_t* c_str() const { return mpBegin; }
};

// Spatial-object interface embedded at +0x34 of nouns/vehicles (cSpatialObject / cLocomotiveObject).
struct cSpatialObject {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
    PV(0c) PV(0d) PV(0e)
    virtual void SetOrientation(const Quaternion& q);              // +0x3c
    virtual void SetScale(float s);                                // +0x40
    PV(11) PV(12) PV(13)
    virtual bool Vf50();                                           // +0x50
    PV(15)
    virtual bool IsPlayerControlled();                             // +0x58
    virtual Vector3 GetVelocity();                                 // +0x5c
    PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38)
    virtual void MoveTo(const Vector3& dst, float speed);                    // +0xe4
    virtual void MoveToRange(const Vector3& dst, float minR, float maxR);    // +0xe8

    bool IsNearGoal();                                             // 0x00c42e20
    void Fc88530(float f);                                         // 0x00c88530
};

struct cPlanetModel {
    Vector3 MakeRandomWorldPosition(const Vector3& center, float minR, float maxR);   // 0x00b81780
    Quaternion BuildSurfaceOrientation(const Vector3& pos);                          // 0x00b7f190
};
struct cSPUIEventLog {
    uint32_t PostFeedbackEvent(uint32_t id, uint32_t group, const Vector3* pos, int a, int b, int c);  // 0x00dd8640
    const string16* GetEventText(uint32_t eventID);                                  // 0x00dd68e0
    void ModifyEventText(uint32_t eventID, const wchar_t* text);                     // 0x00dd6df0
};

struct cAudioSystem {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void PlaySoundAt(uint32_t id, const Vector3& pos, const Vector3& vel);   // +0x60
};

struct cTerrainSphere {
    int Fc75420();                                                 // 0x00c75420
    void Fc78420(const ResourceKey* key);                          // 0x00c78420
};

struct cVehicle;
struct cSpawnedNoun {
    char           pad0[0x34];
    cSpatialObject mSpatial;                                       // +0x34
    void Fca80e0(int n);                                           // 0x00ca80e0
};
struct cCivNoun {
    void Fbefd80(float amount, int b);                             // 0x00befd80
    const ResourceKey* GetModelTypeKey(uint32_t id);               // 0x00bf9770
    cSpawnedNoun* Fbf57b0(int civ, int b, ResourceKey key, const Vector3* pos, bool flag);   // 0x00bf57b0
};
struct cGameNounManager {
    cCivNoun* Fb25f40(int id);                                     // 0x00b25f40
    cTerrainSphere* GetCurrentTerrainSphere();                     // 0x00f67d90
    void RemoveNoun(void* noun);                                   // 0x00b225d0
};
struct cKeyTable {
    const ResourceKey* Fbf9700(int a);                             // 0x00bf9700
};
struct cSomething {
    bool Fae3d40(void* owner);                                     // 0x00ae3d40
};
struct cCameraController {
    const Vector3& GetAnchorDirection1();                          // 0x00b10260
};
struct cRandom {
    uint32_t RandomUint32Uniform(uint32_t n);                      // 0x00a68fb0
};

// Owner returned by the target's virtual +0x58.
struct cHarvestCrew {
    char pad[0xb4c];
    struct Sub { char pad[8]; struct Inner { uint32_t* Fbc97f0(int a, int b, float c, int d); } m8; }* mpB4c;   // +0xb4c (Fbc97f0: 0x00bc97f0)
};
struct CrewVec {
    cHarvestCrew** mpBegin;
    cHarvestCrew** mpEnd;
};
struct cTargetOwner {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23)
    virtual CrewVec* GetCrew();                                    // +0x90
    char  pad4[0x16c];
    int   mFlags170;                                               // +0x170
    char  pad174[0x557 - 0x174];
    bool  mbHarvested;                                             // +0x557
};

// mpTribe target (AutoRefCount at +8 of the memory block)
struct cHarvestTarget {
    virtual int AddRef();
    virtual int Release();                                         // +4
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual cTargetOwner* GetOwner();                              // +0x58
    char           pad4[0x30];
    cSpatialObject mSpatial;                                       // +0x34
    char           pad38[0x220 - 0x38];
    bool           mbCrewAlerted;                                  // +0x220
};

// mpMineral (spice node, AutoRefCount at +4)
struct cCommodityNode {
    char           pad0[0x34];
    cSpatialObject mSpatial;                                       // +0x34
    char           pad38[0x84 - 0x38];
    int            mFlags84;                                       // +0x84
    char           pad88[0x1ec - 0x88];
    int            mState;                                         // +0x1ec
    cVehicle* GetHarvester();                                      // 0x00bfec10
    void Fbfe450(int a, cVehicle* v);                              // 0x00bfe450
    void Fbff140(cVehicle* v);                                     // 0x00bff140
};

struct cGameData {      // embedded at +0x508 of the vehicle
    PV(00) PV(01) PV(02) PV(03)
    virtual int GetNounID();                                       // +0x10
    PV(05)
    virtual void Vf18(float f);                                    // +0x18
    PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual float Vf58(int a, int b, void* c, int d);              // +0x58
};

struct cVehicle {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char           pad4[0x30];
    cSpatialObject mLoco;                                          // +0x34
    char           pad38[0x2a4 - 0x38];
    uint8_t        mPathFlags;                                     // +0x2a4
    char           pad2a5[0x508 - 0x2a5];
    cGameData      mGameData;                                      // +0x508
    char           pad50c[0xb20 - 0x50c];
    int            mCivType;                                       // +0xb20

    void Fcaa900();                                                // 0x00caa900
    void Fca7250(const char* msg);                                 // 0x00ca7250
    void Fdc4d00(cSpatialObject* target);                          // 0x00dc4d00
    void Fc9fb40(Vector3 pos, float a, float b);                   // 0x00c9fb40
};

struct HarvestResourceOrder_memory_block {
    int             mState;     // eState: 0 inactive, 1 heading for resource, 2 waiting in queue
    cCommodityNode* mpMineral;  // AutoRefCount<cCommodityNode>
    cHarvestTarget* mpTribe;    // AutoRefCount<...>
    float           mHarvestTime;
};

// Visual effects
struct Transform {
    uint32_t mData[14];
    Transform();                                                   // 0x00434040
    void SetOffset(const Vector3& v);                              // 0x00571d40
};
struct cRefCounted {
    virtual int AddRef();
    virtual int Release();                                         // +4
};
struct cEffectText : cRefCounted {
    int      pad4[2];
    string16 mText;                                                // +0xc
    cEffectText();                                                 // 0x0057a6d0
};
struct cIVisualEffect : cRefCounted {
    virtual void Start(int flags);                                 // +8
    PV(03) PV(04) PV(05)
    virtual void SetTransform(const Transform& xf);                // +0x18
    PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual void SetObject(int slot, cRefCounted* obj);            // +0x4c
};
struct IEffectsManager {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool CreateVisualEffect(uint32_t id, int flags, cIVisualEffect** ppEffect);   // +0x2c
};
struct EffectRef {      // EA::AutoRefCount<cIVisualEffect>
    cIVisualEffect* mpObject;
    EffectRef() : mpObject(0) {}
    ~EffectRef() { if (mpObject) mpObject->Release(); }
    cIVisualEffect** AsPPTypeParam();                              // 0x00a16f40
};
struct TextRef {        // EA::AutoRefCount<cEffectText>
    cEffectText* mpObject;
    TextRef(cEffectText* p);                                       // 0x00572660
    ~TextRef() { if (mpObject) mpObject->Release(); }
};

extern cPlanetModel*     __cdecl PlanetModel();        // 0x00b3d350
extern cSPUIEventLog*    __cdecl EventLog();           // 0x00b3d3e0
extern cGameNounManager* __cdecl NounManager();        // 0x00b3d300
extern cAudioSystem*     __cdecl AudioSystem();        // 0x00b3d240
extern cCameraController* __cdecl CameraController();  // 0x00b3d280
extern cSomething*       __cdecl Fb26930();            // 0x00b26930
extern IEffectsManager*  __cdecl EffectsManager();     // 0x0067ddd0
extern void*             __cdecl GetCurrentGameMode(); // 0x00b5b800
extern int               __cdecl GetRecorderState();   // 0x00435e90
extern void __cdecl KillSetiEffects(uint32_t id, int state);                 // 0x00435ed0
extern int  __cdecl Fc9e6d0(int civ, int b);                                 // 0x00c9e6d0
extern void __cdecl StandardVehicleMoveTick(cVehicle* v);                    // 0x00dc95b0
extern void __cdecl Fdc95e0(cVehicle* v);                                    // 0x00dc95e0
extern Vector3 __cdecl normalized_safe(const Vector3& v);                    // 0x00449c20
extern float __cdecl Dot3(const Vector3& a, const Vector3& b);               // 0x00455cc0
extern void __cdecl SetNumberString(int64_t value, wchar_t* buf, int bufLen);  // 0x00881ae0 EA::Locale

extern cRandom    g_MathRandom;         // 0x01601760
extern cKeyTable  g_168cb0c;            // 0x0168cb0c
extern char       g_169fa68[];          // 0x0169fa68
extern char       g_GameMode1654c05;    // 0x01654c05
extern uint32_t   g_SetiEffectIDs[];    // 0x0147c68c

static __forceinline void PlaySoundAt(uint32_t id, cSpatialObject* obj)
{
    AudioSystem()->PlaySoundAt(id, obj->GetPosition(), obj->GetVelocity());
}

namespace SP { namespace VehicleTree {

// @ 0x00dcab20
bool HarvestResourceOrder_Tick(cVehicle* self, int, int, int, int, HarvestResourceOrder_memory_block* mem)
{
    if (mem->mpMineral && self->mLoco.Vf50())
        mem->mpMineral->mFlags84 |= 0x800;

    if (mem->mpTribe) {
        cTargetOwner* owner = mem->mpTribe->GetOwner();
        if (!owner || owner->IsDestroyed())
            goto fail;
        if (self->mLoco.Vf50() && mem->mpTribe->GetOwner())
            mem->mpTribe->GetOwner()->mFlags170 |= 0x800;
    }

    switch (mem->mState) {
    case 0:
        if (mem->mpTribe) {
            self->Fdc4d00(&mem->mpTribe->mSpatial);
            Vector3 pos = mem->mpTribe->mSpatial.GetPosition();
            self->Fc9fb40(pos, 4.0f, 8.0f);
            self->mLoco.MoveTo(pos, 1.0f);
            mem->mState = 1;
            return true;
        }
        if (!mem->mpMineral) {
            self->Fca7250("(50) HR: no spice target found");
            self->Fcaa900();
            return false;
        }
        {
            self->Fdc4d00(&mem->mpMineral->mSpatial);
            Vector3 pos = mem->mpMineral->mSpatial.GetPosition();
            self->Fc9fb40(pos, 12.0f, 48.0f);
            self->mLoco.MoveToRange(pos, 12.0f, 24.0f);
            mem->mState = 1;
            return true;
        }

    case 1:
        if (self->mPathFlags & 8) {
            self->Fca7250("(45) HR: path failure");
            self->Fcaa900();
            return false;
        }
        if (self->mLoco.IsNearGoal()) {
            if (mem->mpMineral)
                mem->mpMineral->Fbff140(self);
            mem->mState = 2;
            return true;
        }
        StandardVehicleMoveTick(self);
        if (!mem->mpTribe)
            return true;
        if (mem->mpTribe->IsDestroyed())
            goto fail;
        {
            const Vector3& a = mem->mpTribe->mSpatial.GetPosition();
            const Vector3& b = self->mLoco.GetPosition();
            float dx = b.x - a.x;
            float dy = b.y - a.y;
            float dz = b.z - a.z;
            if (!(sqrt(dx * dx + dy * dy + dz * dz) < 30.0f))
                return true;
        }
        if (mem->mpTribe->mbCrewAlerted)
            return true;
        {
            CrewVec* crew = mem->mpTribe->GetOwner()->GetCrew();
            for (cHarvestCrew** it = crew->mpBegin; it != crew->mpEnd; ++it) {
                if (*it)
                    (*it)->mpB4c->m8.Fbc97f0(0, 0x8000, 10.0f, 0);
            }
        }
        mem->mpTribe->mbCrewAlerted = true;
        return true;

    case 2:
        if (!mem->mpTribe) {
            if (mem->mpMineral->GetHarvester() != self) {
                Fdc95e0(self);
                return true;
            }
            cCommodityNode* node = mem->mpMineral;
            if (node->mState == 0) {
                node->Fbfe450(self->Vf4c(), self);
                return true;
            }
            if (node->mState == 3) {
                self->Fcaa900();
                return false;
            }
            return true;
        }
        if (mem->mpTribe->IsDestroyed())
            goto fail;
        if (mem->mpTribe->GetOwner()->mbHarvested)
            goto fail;
        if (!Fb26930()->Fae3d40(mem->mpTribe->GetOwner())) {
            if (mem->mpTribe->GetOwner()->mbHarvested)
                return true;
            mem->mpTribe->GetOwner()->mbHarvested = true;
            PlaySoundAt(0x674a629, &mem->mpTribe->mSpatial);
            self->mGameData.Vf18(self->mGameData.Vf58(-1, 0, g_169fa68, 0) * 0.5f);
            if (self->mLoco.IsPlayerControlled())
                EventLog()->PostFeedbackEvent(0x7e8864b1, 0xaa9a8ed7, 0, 0, 1, 0);
            self->Fcaa900();
            Vector3 dst = PlanetModel()->MakeRandomWorldPosition(mem->mpTribe->mSpatial.GetPosition(), 20.0f, 20.0f);
            self->mLoco.MoveTo(dst, 1.0f);
            return false;
        }
        PlaySoundAt(0x631456d0, &mem->mpTribe->mSpatial);
        {
            cCivNoun* civNoun = NounManager()->Fb25f40(self->mGameData.GetNounID());
            if (civNoun) {
                if (g_MathRandom.RandomUint32Uniform(2) == 0) {
                    int amount = g_MathRandom.RandomUint32Uniform(400) + g_MathRandom.RandomUint32Uniform(400)
                               + g_MathRandom.RandomUint32Uniform(200) + 400;
                    civNoun->Fbefd80((float)amount, 1);
                    if (self->mLoco.IsPlayerControlled()) {
                        uint32_t eventID = EventLog()->PostFeedbackEvent(0x4b7ae141, 0x2bb7aff,
                                                                         &mem->mpTribe->mSpatial.GetPosition(), 0, 0, 0);
                        const string16* text = EventLog()->GetEventText(eventID);
                        if (text) {
                            string16 s;
                            s.sprintf(text->c_str(), amount);
                            EventLog()->ModifyEventText(eventID, s.c_str());
                        }
                        if (CameraController()) {
                            Vector3 dir = CameraController()->GetAnchorDirection1();
                            if (Dot3(normalized_safe(self->mLoco.GetPosition()), normalized_safe(dir)) > 0.6f) {
                                EffectRef effect;
                                EffectsManager()->CreateVisualEffect(0xdbf1ae1f, 0, effect.AsPPTypeParam());
                                if (effect.mpObject) {
                                    Transform xf;
                                    xf.SetOffset(self->mLoco.GetPosition());
                                    effect.mpObject->SetTransform(xf);
                                    TextRef label(new ("Simulator", 0, 0, 0, 0) cEffectText());
                                    wchar_t buf[64];
                                    SetNumberString(amount, buf, 64);
                                    buf[63] = 0;
                                    label.mpObject->mText.sprintf(L"%lc%lc%ls", 0x268a, 0x2b, buf);
                                    effect.mpObject->SetObject(8, label.mpObject);
                                    effect.mpObject->Start(0);
                                }
                            }
                        }
                        PlaySoundAt(0x5dfc872, &mem->mpTribe->mSpatial);
                    }
                } else {
                    if (self->mLoco.IsPlayerControlled())
                        EventLog()->PostFeedbackEvent(0x9964ae79, 0x2bb7aff, &mem->mpTribe->mSpatial.GetPosition(), 0, 0, 0);
                    int civ = self->mCivType;
                    if (self->mLoco.IsPlayerControlled())
                        civ = g_MathRandom.RandomUint32Uniform(3);
                    uint32_t modelID;
                    switch (civ) {
                    case 0: modelID = 0x7d433fad; break;
                    case 1: modelID = 0x9ad7d4aa; break;
                    case 2: modelID = 0xf670aa43; break;
                    default: modelID = 0xffffffff; break;
                    }
                    ResourceKey key = *civNoun->GetModelTypeKey(modelID);
                    if (key.instanceID == 0)
                        key = *g_168cb0c.Fbf9700(Fc9e6d0(civ, 0));
                    Vector3 pos = PlanetModel()->MakeRandomWorldPosition(mem->mpTribe->mSpatial.GetPosition(), 10.0f, 10.0f);
                    cSpawnedNoun* spawned = civNoun->Fbf57b0(civ, 0, key, &pos, GetCurrentGameMode() == &g_GameMode1654c05);
                    if (spawned) {
                        cSpatialObject* sp = &spawned->mSpatial;
                        sp->SetOrientation(PlanetModel()->BuildSurfaceOrientation(pos));
                        sp->SetScale(0.1f);
                        sp->Fc88530(1.0f);
                        if (self->mLoco.IsPlayerControlled())
                            spawned->Fca80e0(10);
                        if (self->mLoco.IsPlayerControlled())
                            KillSetiEffects(g_SetiEffectIDs[civ], GetRecorderState());
                    }
                    PlaySoundAt(0x5dfc876, &mem->mpTribe->mSpatial);
                    if (self->mLoco.IsPlayerControlled()) {
                        if (NounManager()->GetCurrentTerrainSphere()->Fc75420() >= 1) {
                            ResourceKey k;
                            k.instanceID = 0x521f703;
                            k.typeID = 0;
                            k.groupID = 0xaa9a8ed7;
                            cTerrainSphere* ts = NounManager()->GetCurrentTerrainSphere();
                            if (ts)
                                ts->Fc78420(&k);
                        }
                    }
                }
            }
        }
        NounManager()->RemoveNoun(mem->mpTribe->GetOwner());
        goto fail;

    default:
        return true;
    }

fail:
    // mpTribe = NULL (AutoRefCount assignment)
    if (mem->mpTribe) {
        cHarvestTarget* t = mem->mpTribe;
        mem->mpTribe = 0;
        t->Release();
    }
    self->Fcaa900();
    return false;
}

}}
