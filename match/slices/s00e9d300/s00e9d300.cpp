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
