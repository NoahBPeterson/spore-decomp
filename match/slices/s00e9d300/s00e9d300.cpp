// s00e9d300: SP::cSPUFOGfx per-frame update (0x00e9d300, "$E431" in the dev PDB), thiscall ret 8.
// Syncs the UFO view with its game data: visibility, model state flags, transform, empire colour,
// hit/trail/radar/shield effects, ring sounds and the ambient audio source.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100)

extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(fabs)
#pragma intrinsic(sqrt)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vec3POD { float x, y, z; };
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3& Assign(const Matrix3& o);          // 0x0041cb40, thiscall ret 4
};

extern const Vector3 kZero2;                    // 0x016c6350
extern const Matrix3 kIdentity;                 // 0x016c6940
extern const char kUnkE93160[];                 // 0x015a8af4
extern const float kDtScale;                    // 0x015a8b50 (0.01f)

const Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);   // 0x0059c190 (cdecl)

struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;
    __forceinline Transform() : mnFlags(0), mnTransformCount(0), mOffset(kZero2), mfScale(1.0f)
    {
        mRotation.Assign(kIdentity);
    }
    Transform& SetOffset(const Vector3& v) { mOffset = v; mnFlags |= 4; mnTransformCount++; return *this; }
    Transform& SetRotation(const Matrix3& r) { mRotation = r; mnFlags |= 2; mnTransformCount++; return *this; }
    Transform& SetScale(float s) { mfScale = s; mnTransformCount++; return *this; }
};

struct RenderState {                            // returned by vtable slot 0xac of the object and the locomotive
    uint32_t pad0;
    uint32_t flags;                             // +4
    uint32_t pad1[0x4c / 4 - 2];
    Vector3 tint;                               // +0x4c
    float alpha;                                // +0x58
};

static inline void SetTint(RenderState* rs, Vec3POD v) { rs->tint = *(Vector3*)&v; }

struct ViewData {                               // GetViewData() result
    uint32_t pad0;
    uint32_t flags;                             // +4, bit 14 = dirty
    Transform xf;                               // +8
    uint32_t pad1[(0x70 - 0x40) / 4];
    Vector3 effectPos;                          // +0x70
    uint32_t pad2[(0x8c - 0x7c) / 4];
    float f8c;                                  // +0x8c
    bool IsDirty() const { return (flags >> 14) & 1; }
};

struct cSpatialObject {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c();
    virtual float GetScale();                   // +0x34
    virtual void v0e(); virtual void v0f(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual void SetEffectPos(Vector3* pos, float scale);   // +0x64
    virtual void v1a(); virtual void v1b(); virtual void v1c(); virtual void v1d();
    virtual void v1e(); virtual void v1f(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v2a();
    virtual RenderState* GetRenderState();      // +0xac
    virtual void v2c(); virtual void v2d();
    virtual void* Cast(uint32_t typeID);        // +0xb8
    uint32_t pad04[(0x50 - 4) / 4];
    uint32_t mFlags;                            // +0x50
};

struct cLocomotiveIface {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const Vector3* GetPosition();       // +0x2c
    virtual const Quaternion* GetOrientation(); // +0x30
    virtual float GetScale();                   // +0x34
    virtual void v0e(); virtual void v0f(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v1a(); virtual void v1b(); virtual void v1c(); virtual void v1d();
    virtual void v1e(); virtual void v1f(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v2a();
    virtual RenderState* GetRenderState();      // +0xac
    uint32_t pad04[(0x74 - 4) / 4];
    bool mbTransformDirty;                      // +0x74
    void SetTransform(const Transform* t);      // 0x00c89d60 (ret 4)
    void Flush();                               // 0x00c8aa60
    const Vector3* GetVelocity();               // 0x00d20610 (lea eax,[ecx+0x1c8])
};

struct cSpeedSource {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual float GetValue();                   // +0x58
};

struct cSPGameDataUFO {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual int GetEmpireID();                  // +0x4c
    uint32_t pad04[(0x34 - 4) / 4];
    cLocomotiveIface mLoco;                     // +0x34
    uint32_t padAC[(0xd8 - 0xac) / 4];
    uint8_t padD8;
    bool mbColorDirty;                          // +0xd9
    uint8_t padDA[0x508 - 0xda];
    cSpeedSource mSpeed;                        // +0x508
    uint32_t pad50C[(0x540 - 0x50c) / 4];
    float mf540;
    uint32_t pad544[(0x5ec - 0x544) / 4];
    float mf5ec;
    uint32_t pad5F0[(0x714 - 0x5f0) / 4];
    int mMode;                                  // +0x714
    uint32_t pad718[(0x77c - 0x718) / 4];
    bool mbVisible;                             // +0x77c
    bool mbVisibleDirty;                        // +0x77d
    bool mbSnapScale;                           // +0x77e

    bool IsVisibleDirty();                      // 0x00c37160
    bool GetVisible();                          // 0x00c37170
    void ClearVisibleDirty();                   // 0x00c37150
    bool CheckState(int which);                 // 0x00c38990
    bool IsModelDirty();                        // 0x00c37220
    void GetModel(Vector3* pos, uint8_t* flag); // 0x00c37230
    void ClearModelDirty();                     // 0x00c37210
    void Refresh();                             // 0x00c3b3f0
};

struct cEmpire { void GetColor(Vector3* out); };                    // 0x00c32cd0
struct cStarManager { cEmpire* GetEmpireByID(int id); };            // 0x00ba9370
struct cStarMgrB { void Apply(void* what, int flag); };             // 0x00b48770 (ret 8)
struct cTerrainSphere { bool Check(); };                            // 0x00c75650
struct cTerrainEditor { cTerrainSphere* GetCurrentTerrainSphere(); };
struct cNounManager;
struct cModeInfo { uint32_t pad[0x2c / 4]; int mType; };            // +0x2c

namespace SP {
cStarManager* StarManager();                                         // 0x00b3d2a0
cStarMgrB* ObjectManager();                                          // 0x00b3d310
cTerrainEditor* NounManager();                                       // 0x00b3d300 (real type differs)
uint32_t GetCurrentGameMode();                                       // 0x00b5b800
int GetUniverseContext();                                            // 0x01021080
cModeInfo* GetModeInfo();                                            // 0x00b3d4d0
}
void* CastObject(void* const* ref);                                  // 0x00ad2670 (cdecl, AutoRefCount*)
void ApplyAOEEffect(cLocomotiveIface* loco, void* effectRef, int zero);   // 0x01043860
void ApplyRallyEffect(cLocomotiveIface* loco, void* effectRef, int zero); // 0x01043a50
void SetEffectPosition(void* effect, float x, float y, float z);     // 0x009fbc50
void PlayEditorSound(void* effect, uint32_t id, float value, int flag);   // 0x00435f40

struct cAudioSource {
    virtual void v00(); virtual void v01();
    virtual void Start(int arg);                // +8
    virtual void Stop(int arg);                 // +0xc
    virtual bool IsPlaying();                   // +0x10
    virtual void SetPosition(const void* pos);  // +0x14
};

class cSPUFOGfx {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual ViewData* GetViewData();            // +0x2c
    uint32_t pad04[2];
    cSpatialObject* mpObject;                   // +0x0c
    uint32_t pad10[2];
    Vector3 mColor;                             // +0x18
    uint32_t pad24[(0x30 - 0x24) / 4];
    bool mbFlag30;
    bool mbFlag31;
    uint8_t pad32[0x78 - 0x32];
    bool mbEnabled;                             // +0x78
    uint8_t pad79[3];
    void* mRingEffect;                          // +0x7c
    uint32_t pad80[(0x90 - 0x80) / 4];
    void* mAOERepairEffect;                     // +0x90
    void* mRallyCallEffect;                     // +0x94
    uint32_t pad98[(0xb8 - 0x98) / 4];
    cAudioSource* mpAudio;                      // +0xb8
    uint32_t padBC[(0xd4 - 0xbc) / 4];
    int mLastUniverseContext;                   // +0xd4

    void SetVisible(bool v);                    // 0x00e98db0
    void SetUFOModel(const Vector3* pos, uint32_t flag);   // 0x00e9a940 (ret 8)
    void NotifyDirty(int a, const char* b);     // 0x00e93160 (ret 8)
    void CreateHitEffects();                    // 0x00e9bb40
    void UpdateTrail();                         // 0x00e99550
    void UpdateE998D0();                        // 0x00e998d0
    void UpdateE99C50(int dt);                  // 0x00e99c50 (ret 4)
    void UpdateE9B2B0();                        // 0x00e9b2b0
    void UpdateRadarEffect(cSPGameDataUFO* u);  // 0x00e9cf30
    void UpdateAOERepairEffect(cSPGameDataUFO* u);  // 0x00e99f90
    void UpdateRallyCallEffect(cSPGameDataUFO* u);  // 0x00e9a0c0
    void UpdateShieldEffect(cSPGameDataUFO* u);     // 0x00e9a360
    void UpdateCloakEffect(cSPGameDataUFO* u);      // 0x00e9a590
    void UpdateE9A1F0(cSPGameDataUFO* u);
    void UpdateE9A6A0(cSPGameDataUFO* u);
    void UpdateE9A470(cSPGameDataUFO* u);
    void Update(int dt, int unused);            // 0x00e9d300
};

void cSPUFOGfx::Update(int dt, int unused)
{
    cSPGameDataUFO* ufo = mpObject ? (cSPGameDataUFO*)mpObject->Cast(0xb033b403) : 0;

    if (ufo->IsVisibleDirty()) {
        SetVisible(ufo->GetVisible());
        ufo->ClearVisibleDirty();
    }

    Matrix3 tmp;
    cLocomotiveIface* loco = &ufo->mLoco;
    RenderState* rs = loco->GetRenderState();
    if (rs) {
        float alpha;
        if (!(ufo->CheckState(1) || ufo->mMode == 5)) {
            rs->flags &= ~6u;
            alpha = 1.0f;
        } else {
            rs->flags |= 6;
            alpha = 0.3f;
        }
        rs->alpha = alpha;
    }

    if (ufo->IsModelDirty()) {
        uint32_t pos[3] = { 0, 0, 0 };
        union { uint8_t b; uint32_t w; } fl;
        fl.b = 0;
        ufo->GetModel((Vector3*)pos, &fl.b);
        SetUFOModel((Vector3*)pos, fl.w);
        ufo->ClearModelDirty();
        mbFlag31 = false;
    }

    if (loco->mbTransformDirty) {
        loco->mbTransformDirty = false;
        Transform t;
        t.SetOffset(*loco->GetPosition());
        t.SetScale(loco->GetScale());
        Matrix3FromQuaternion(&tmp, loco->GetOrientation());
        t.SetRotation(tmp);
        loco->SetTransform(&t);
    }
    loco->Flush();

    if (!mbEnabled)
        return;
    ViewData* vd = GetViewData();
    if (!vd)
        return;

    if (mbFlag30 && (vd->IsDirty())) {
        mbFlag30 = false;
        mpObject->mFlags &= ~0x10u;
        cSpatialObject* o = mpObject;
        if (!(o->mFlags & 0x20)) {
            o->SetEffectPos(&vd->effectPos, o->GetScale());
            SP::ObjectManager()->Apply(CastObject((void* const*)&mpObject), 1);
        }
    }

    if (ufo->mbColorDirty) {
        ufo->mbColorDirty = false;
        if (ufo->GetEmpireID() != -1 && ufo->mMode != 0 && ufo->mMode != 5) {
            cEmpire* empire = SP::StarManager()->GetEmpireByID(ufo->GetEmpireID());
            if (empire) {
                Vec3POD color;
                empire->GetColor((Vector3*)&color);
                mColor = *(Vector3*)&color;
                mpObject->GetRenderState()->flags |= 4;
                SetTint(mpObject->GetRenderState(), color);
            }
        }
        mbFlag31 = false;
    }

    if (vd->IsDirty()) {
        ufo->Refresh();
        if (vd->f8c > 0.0f)
            NotifyDirty(0, 0);
        else
            NotifyDirty(1, kUnkE93160);
    }

    CreateHitEffects();
    UpdateTrail();
    UpdateE998D0();
    UpdateE99C50(dt);
    UpdateE9B2B0();

    if (ufo->mMode != 0 && SP::GetCurrentGameMode() == 0x1654c05) {
        ApplyAOEEffect(loco, &mAOERepairEffect, 0);
        ApplyRallyEffect(loco, &mRallyCallEffect, 0);
    }

    UpdateRadarEffect(ufo);
    UpdateAOERepairEffect(ufo);
    UpdateRallyCallEffect(ufo);
    UpdateShieldEffect(ufo);
    UpdateCloakEffect(ufo);
    UpdateE9A1F0(ufo);
    UpdateE9A6A0(ufo);
    UpdateE9A470(ufo);

    vd->flags |= 0x10;
    vd->xf.SetOffset(*loco->GetPosition());
    vd->xf.SetRotation(*Matrix3FromQuaternion(&tmp, loco->GetOrientation()));

    bool contextChanged = mLastUniverseContext != SP::GetUniverseContext();
    mLastUniverseContext = SP::GetUniverseContext();
    if (contextChanged)
        ufo->Refresh();

    float target;
    if (ufo->mbSnapScale)
        target = 1.5258789e-05f;
    else
        target = loco->GetScale();

    float cur = vd->xf.mfScale;
    if (!contextChanged && cur != target) {
        float fdt = (float)(uint32_t)dt;
        float t = Clamp(fdt * kDtScale, 0.0f, 1.0f);
        int mode = SP::GetModeInfo()->mType;
        if (mode != 1 && mode != 2)
            target = (target - cur) * t + cur;
    }
    vd->xf.SetScale(target);

    if (mRingEffect) {
        if (!mbEnabled) {
            PlayEditorSound(mRingEffect, 0x8ffebe43, 0.0f, 0);
        } else {
            Vector3 p = *loco->GetPosition();
            SetEffectPosition(mRingEffect, p.x, p.y, p.z);
            PlayEditorSound(mRingEffect, 0x67f9e01f, (float)fabs(ufo->mf5ec), 0);
            float a = ufo->mf540;
            PlayEditorSound(mRingEffect, 0x6a807a1a, a / ufo->mSpeed.GetValue(), 0);
            const Vector3* v = loco->GetVelocity();
            PlayEditorSound(mRingEffect, 0x26341ede,
                            (float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z) / target, 0);
            PlayEditorSound(mRingEffect, 0x8ffebe43, 32767.0f, 0);
        }
    }

    if (ufo->mMode != 0)
        return;
    cTerrainSphere* sphere = SP::NounManager()->GetCurrentTerrainSphere();
    bool b = sphere->Check();
    if (b) {
        if (!mpAudio)
            return;
        if (!mpAudio->IsPlaying())
            mpAudio->Start(0);
        ViewData* v2 = GetViewData();
        if (v2)
            mpAudio->SetPosition((char*)v2 + 8);
    } else {
        if (mpAudio && mpAudio->IsPlaying())
            mpAudio->Stop(0);
    }
}

// ===========================================================================
// SP::Audio::cAmbienceLayerManager -- cube-face lookup, layer bookkeeping and
// the "ambience" cheat command (0x00e9da00 .. 0x00e9e220).
//
// HandleMessage (0x00e9dfa0) is entered with this == manager + 4: the manager
// derives from cMessageSource (vptr at +0x00) and cAmbienceMessageHandler
// (vptr at +0x04), so the handler down-casts back to the manager.
// ===========================================================================
#include <new>

#define VIRT4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();
typedef unsigned int size_t;
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags,
                     const char* file, int line);                     // 0x00f473a0
void operator delete[](void* p);                                      // 0x00f47380

extern const float    kHalfF;                     // 0x01471064 (0.5f)
extern const float    kOneF;                      // 0x01485720 (1.0f)
extern const float    kZeroF;                     // 0x01485378 (0.0f)
extern const uint32_t kAmbienceMsgIds[14];        // 0x01487100
extern void*          g_015a8b70;                 // audio parameter source handle
extern void*          g_015a8b6c;                 // audio parameter expected id
extern void*          g_015a8b74;                 // audio parameter source handle 2

struct cAmbienceTag { uint32_t mFlags; };         // +0x00

struct cAmbienceLayer                              // element of the +0xb0 layer array
{
    virtual void v00();
    virtual void v01();
    virtual void Deactivate();                     // +0x08
    virtual void Release();                        // +0x0c
    virtual void v04();
    virtual void v05();
    int  GetGameMode();                            // 0x00a42730
    void Stop();                                   // 0x00a34eb0
    bool Shutdown();                               // 0x00a35f70
};

struct cAmbienceObject                             // per-cube-face entry (direction at +0x08)
{
    void*     mpVtbl;                              // +0x00
    uint32_t  mId;                                 // +0x04
    Vector3   mDirection;                          // +0x08
};

struct cObjectVector { cAmbienceObject** mpBegin; cAmbienceObject** mpEnd; };
struct cLayerVector
{
    cAmbienceLayer** mpBegin;                      // +0x00
    cAmbienceLayer** mpEnd;                        // +0x04
    void ClearAndFree();                           // 0x00e9ddc0
};

struct ResponseCurve { float GetOutputValue(float in) const; };   // 0x00a1a110 (ret 4)

struct cAudioParamInterface
{
    virtual void v00();
    virtual void Release();                        // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v0a();
    virtual bool GetSourceValue(void* handle, void* out);   // +0x2c
    virtual void v0c(); virtual void v0d();
    virtual bool GetMixValue(void* handle, void* out);      // +0x34
};

struct cPTypeParam;                                // audio type-parameter wrapper
struct cAutoRefSlot
{
    cAudioParamInterface* mpObject;                // +0x00
    cPTypeParam* AsPPTypeParam(uint32_t typeId);   // 0x00a16f40 (ret 4)
};

struct cAudioSystemBase
{
    VIRT4(a) VIRT4(b) VIRT4(c) VIRT4(d) VIRT4(e)
    virtual bool ResolveParam(void* source, cPTypeParam* param);   // +0x14
};
cAudioSystemBase* GetSystemAT();                   // 0x00a206f0

class cAmbienceLayerManager;

struct cAudioSystem
{
    VIRT4(a) VIRT4(b) virtual void v20();
    virtual cAmbienceLayerManager* GetAmbienceLayerManager();      // +0x24 (ret 0)
};
cAudioSystem* AudioSystem();                       // 0x0067cb00

struct cMessageServer
{
    VIRT4(a) VIRT4(b) virtual void v20();
    virtual void Subscribe(void* target, uint32_t id);             // +0x24 (ret 8)
};
namespace EA { namespace Messaging { cMessageServer* GetServer(); } }   // 0x00883860

struct cCheatManager;
cCheatManager* CheatManager();                     // 0x0067de20

class cArguments
{
public:
    bool HasFlag(const char* name);                                    // 0x008380b0 (ret 4)
    bool HasArgument(const char* name);                                // 0x00837ee0 (ret 4)
    void** OptionArguments(const char* name, void* out, int a, int b); // 0x00838130 (ret 0x10)
};
uint32_t FNVHash(const char* text, uint32_t seed, int count);          // 0x00932e80 (ret 0xc)

class cCommandBase
{
public:
    cCommandBase();                                // 0x0083c800
    virtual void Execute(cArguments* args);        // +0x00
};
class cAmbienceCheat : public cCommandBase
{
public:
    void Execute(cArguments* args);                // 0x00e9de00
};

class cMessageSource
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
};

class cAmbienceMessageHandler
{
public:
    virtual bool HandleMessage(uint32_t msgId, void* msg);            // 0x00e9dfa0 (ret 8)
};

class cAmbienceLayerManager : public cMessageSource, public cAmbienceMessageHandler
{
public:
    virtual void Enable(bool enabled);                                // +0x10 (0x00e9da00)
    virtual void OnStartup();                                         // +0x14
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual bool ShowPosition(void* obj, float x, float y, float z, void* owner);   // +0x28
    virtual bool SetTagValue(int value);                              // +0x2c

    uint32_t pad08[3];
    cMessageServer*  mpMsgServer;                 // +0x14
    void*            mpMsgTarget;                 // +0x18  the +0x04 handler sub-object
    const uint32_t*  mpMsgIds;                    // +0x1c
    int              mnMsgIdCount;                // +0x20
    int              mnMsgPriority;               // +0x24
    int              mNumSamplePoints;            // +0x28
    cObjectVector**  mpFaceLists;                 // +0x2c
    uint32_t pad30[0x38 / 4];
    cAmbienceTag**   mTagArrayBegin;              // +0x68
    cAmbienceTag**   mTagArrayEnd;                // +0x6c
    uint32_t pad70[3];
    cAmbienceTag**   mTagIterator;                // +0x7c
    uint32_t pad80[7];
    Vector3          mSamplePosition;             // +0x9c
    uint32_t padA8[1];
    bool             mbPositionChanged;           // +0xac
    uint8_t padAD[3];
    cAmbienceLayer** mLayersBegin;                // +0xb0
    cAmbienceLayer** mLayersEnd;                  // +0xb4
    uint32_t padB8[3];
    cAmbienceTag**   mActiveTagsBegin;            // +0xc4
    cAmbienceTag**   mActiveTagsEnd;              // +0xc8
    uint32_t padCC[3];
    float            mfSampleRadius;              // +0xd8
    uint32_t padDC[4];
    ResponseCurve    mRadiusCurve;                // +0xec
    uint32_t padF0[0x1b2];
    bool             mbDebugDraw;                 // +0x7b8
    uint8_t pad7B9[0x10];
    uint32_t         mEnableFlags;                // +0x7cc
    uint32_t pad7D0[1];
    cAmbienceTag**   mTagRangeBegin;              // +0x7d4
    cAmbienceTag**   mTagRangeEnd;                // +0x7d8

    float GetAmbientSphereRadius();               // 0x00e9da20
    void  SetSamplePosition(const Vector3* p);    // 0x00e9da50
    bool  StopLayerForMode(int mode);             // 0x00e9dac0
    int   GetCubeFace(const Vector3* dir);        // 0x00e9db10
    bool  RemoveObject(cAmbienceObject* obj);     // 0x00e9dcc0
    cAmbienceLayer* FindLayerForMode(int mode);   // 0x00e9dd20
    void  GenerateDynamicAmbienceTagsBegin();     // 0x00e9dd80
    void  DestroyLayers();                        // 0x00e9e220
    bool  Startup();                              // 0x00e9df00
};

struct cPlanetModel
{
    bool IsReady();                                                    // 0x00b7ec40
    void DirectionToSurfacePosition(Vector3* out, const Vector3* dir); // 0x00b815a0 (ret 8)
};
cPlanetModel* PlanetModel();                       // 0x00b3d350

struct cAudioParamPair { void* mpFirst; void* mpSecond; void* mpThird; };
struct cAmbienceMessage                                 // message payload
{
    uint32_t pad00[4];
    void*    mpSource;                             // +0x10
    uint32_t pad14;
    void*    mpOwner;                              // +0x18
    uint32_t pad1c[5];
    float    mfX;                                  // +0x30
    uint32_t pad34;
    float    mfY;                                  // +0x38
    uint32_t pad3c;
    float    mfZ;                                  // +0x40
    uint32_t pad44[(0x88 - 0x44) / 4];
    uint32_t mFlags;                               // +0x88
};

// @ 0x00e9da00
void cAmbienceLayerManager::Enable(bool enabled)
{
    if (enabled)
        mEnableFlags &= ~8u;
    else
        mEnableFlags |= 8u;
}

// @ 0x00e9da20
float cAmbienceLayerManager::GetAmbientSphereRadius()
{
    return mRadiusCurve.GetOutputValue(mfSampleRadius);
}

// @ 0x00e9da50
void cAmbienceLayerManager::SetSamplePosition(const Vector3* p)
{
    mbPositionChanged = mSamplePosition.x != p->x
                     || mSamplePosition.y != p->y
                     || mSamplePosition.z != p->z;
    mSamplePosition = *p;
}

// @ 0x00e9dac0
bool cAmbienceLayerManager::StopLayerForMode(int mode)
{
    cAmbienceLayer** end = mLayersEnd;
    for (cAmbienceLayer** it = mLayersBegin; it != end; ++it)
    {
        cAmbienceLayer* layer = *it;
        if (layer->GetGameMode() == mode)
        {
            layer->Stop();
            return true;
        }
    }
    return false;
}

// @ 0x00e9db10
int cAmbienceLayerManager::GetCubeFace(const Vector3* dir)
{
    int n = mNumSamplePoints;
    float half = (float)n * kHalfF;
    float ax = (float)fabs(dir->x);
    float ay = (float)fabs(dir->y);
    float az = (float)fabs(dir->z);
    int i;
    int j;
    int face;

    if (az < ax || az < ay)
    {
        if (ay < ax)
        {
            i = (int)((dir->y / ax + kOneF) * half);
            j = (int)((dir->z / ax + kOneF) * half);
            face = (dir->x < kZeroF) ? 3 : 2;
        }
        else
        {
            i = (int)((dir->z / ay + kOneF) * half);
            j = (int)((dir->x / ay + kOneF) * half);
            face = (dir->y < kZeroF) ? 5 : 4;
        }
    }
    else
    {
        i = (int)((dir->x / az + kOneF) * half);
        j = (int)((dir->y / az + kOneF) * half);
        face = (dir->z < kZeroF) ? 1 : 0;
    }

    if (i == n)
        i = n - 1;
    if (j == n)
        j = n - 1;
    return (mNumSamplePoints * face + j) * mNumSamplePoints + i;
}

// @ 0x00e9dcc0
bool cAmbienceLayerManager::RemoveObject(cAmbienceObject* obj)
{
    if (obj == 0)
        return false;

    cObjectVector* list = mpFaceLists[GetCubeFace(&obj->mDirection)];
    int count = (int)(list->mpEnd - list->mpBegin);
    for (int i = 0; i < count; i++)
    {
        if (list->mpBegin[i] == obj)
        {
            list->mpBegin[i] = 0;
            return true;
        }
    }
    return false;
}

// @ 0x00e9dd20
cAmbienceLayer* cAmbienceLayerManager::FindLayerForMode(int mode)
{
    cAmbienceLayer** end = mLayersEnd;
    for (cAmbienceLayer** it = mLayersBegin; it != end; ++it)
    {
        cAmbienceLayer* layer = *it;
        if (layer->GetGameMode() == mode)
            return layer;
    }
    return 0;
}

// @ 0x00e9dd80
void cAmbienceLayerManager::GenerateDynamicAmbienceTagsBegin()
{
    cAmbienceTag** it = mTagArrayBegin;
    cAmbienceTag** end = mTagArrayEnd;
    mTagIterator = it;
    while (it != end)
    {
        (*it)->mFlags &= ~1u;
        ++it;
    }
    mTagRangeBegin = mActiveTagsBegin;
    mTagRangeEnd = mActiveTagsEnd;
}

// @ 0x00e9ddc0
void cLayerVector::ClearAndFree()
{
    cAmbienceLayer** end = mpEnd;
    for (cAmbienceLayer** it = mpBegin; it < end; ++it)
    {
        if (*it != 0)
            (*it)->Release();
    }
    if (mpBegin != 0)
        operator delete[](mpBegin);
}

// @ 0x00e9de00
void cAmbienceCheat::Execute(cArguments* args)
{
    if (args->HasFlag("help"))
        return;

    if (args->HasFlag("dbg"))
    {
        cAmbienceLayerManager* mgr = AudioSystem()->GetAmbienceLayerManager();
        mgr->mbDebugDraw = !mgr->mbDebugDraw;
        return;
    }

    if (args->HasArgument("dbglayer"))
    {
        const char* text = *(const char**)args->OptionArguments("dbglayer", &args, 1, 0x7fffffff);
        uint32_t key = FNVHash(text, 0x811c9dc5, 1);
        AudioSystem()->GetAmbienceLayerManager()->StopLayerForMode(key);
        return;
    }

    if (args->HasArgument("enable"))
        AudioSystem()->GetAmbienceLayerManager()->Enable(true);

    if (args->HasArgument("disable"))
        return AudioSystem()->GetAmbienceLayerManager()->Enable(false);
}

// @ 0x00e9df00
bool cAmbienceLayerManager::Startup()
{
    OnStartup();

    cAmbienceMessageHandler* target = static_cast<cAmbienceMessageHandler*>(this);
    cMessageServer* server = EA::Messaging::GetServer();

    mpMsgServer = server;
    mpMsgTarget = target;
    mpMsgIds = kAmbienceMsgIds;
    mnMsgIdCount = 14;
    mnMsgPriority = 0;

    if (server != 0 && target != 0)
    {
        const uint32_t* pId = kAmbienceMsgIds;
        const uint32_t* pEnd = kAmbienceMsgIds + 14;
        while (pId != pEnd)
        {
            server->Subscribe(target, *pId);
            ++pId;
        }
    }

    if (CheatManager() != 0)
    {
        cAmbienceCheat* cheat = (cAmbienceCheat*)operator new[](0x10, "Audio", 0, 0, 0, 0);
        if (cheat != 0)
            new (cheat) cAmbienceCheat();
    }
    return false;
}

// @ 0x00e9e220
void cAmbienceLayerManager::DestroyLayers()
{
    while (mLayersBegin != mLayersEnd)
    {
        cAmbienceLayer* layer = mLayersEnd[-1];
        if (layer != 0)
            layer->Deactivate();
        --mLayersEnd;
        cAmbienceLayer* prev = *mLayersEnd;
        if (prev != 0)
            prev->Release();
        layer->Shutdown();
        if (layer != 0)
            layer->Release();
    }
}

// @ 0x00e9dfa0
bool cAmbienceMessageHandler::HandleMessage(uint32_t msgId, void* msg)
{
    cAmbienceLayerManager* mgr = static_cast<cAmbienceLayerManager*>(this);
    cAmbienceMessage* m = (cAmbienceMessage*)msg;

    if (msgId < 0x279a67d)
    {
        if (msgId != 0x279a67c)
        {
            if (msgId > 0x20c089c)
            {
                if (msgId != 0x279a5da)
                    return false;
                mgr->mEnableFlags &= ~4u;
                return false;
            }
            if (msgId == 0x20c089c)
            {
                cPlanetModel* planet = PlanetModel();
                if (planet == 0)
                    return false;
                if (!planet->IsReady())
                    return false;
                Vector3 dir;
                dir.x = m->mfX;
                dir.y = m->mfY;
                dir.z = m->mfZ;
                Vector3 out;
                planet->DirectionToSurfacePosition(&out, &dir);
                mgr->SetSamplePosition(&out);
                return false;
            }
            if (msgId == 0xff0ec1)
            {
                if (((m->mFlags >> 1) & 1) == 0)
                    return false;

                void* source = m->mpSource;
                if (source == 0)
                    return false;

                cAutoRefSlot slot;
                slot.mpObject = 0;
                cPTypeParam* param = slot.AsPPTypeParam(0x21407ee);
                if (!GetSystemAT()->ResolveParam(source, param))
                {
                    if (slot.mpObject != 0)
                        slot.mpObject->Release();
                    return false;
                }

                cAudioParamInterface* iface = slot.mpObject;
                cAudioParamPair pair;
                pair.mpFirst = 0;
                pair.mpSecond = 0;
                pair.mpThird = 0;
                if (!iface->GetMixValue(g_015a8b70, &pair))
                {
                    if (iface != 0)
                        iface->Release();
                    return false;
                }
                if (pair.mpFirst != g_015a8b6c)
                {
                    if (iface != 0)
                        iface->Release();
                    return false;
                }

                void* value = 0;
                if (!iface->GetSourceValue(g_015a8b74, &value))
                {
                    if (iface != 0)
                        iface->Release();
                    return false;
                }

                bool shown = mgr->ShowPosition(value, m->mfX, m->mfY, m->mfZ, m->mpOwner);
                if (iface != 0)
                    iface->Release();
                return shown;
            }
            if (msgId != 0xff0ed1)
                return false;
            return mgr->SetTagValue(((int*)msg)[2]);
        }
        mgr->mEnableFlags |= 4u;
        return false;
    }

    if (msgId == 0x279a680 || msgId == 0x281d424)
    {
        mgr->mEnableFlags |= 4u;
        return false;
    }
    if (msgId != 0x60e4e46e)
        return false;

    uint32_t mode = SP::GetCurrentGameMode();
    if (mode == 0x1654c01 || mode == 0x1654c10)
        mgr->mfSampleRadius = 0.0f;
    else
        mgr->mfSampleRadius = ((float*)msg)[2] / ((float*)msg)[4];
    return false;
}
