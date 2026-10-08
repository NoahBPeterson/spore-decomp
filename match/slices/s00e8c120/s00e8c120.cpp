// Slice s00e8c120: SP::cCreatureView::HandleSimulationUpdate (0x00E8C120, 2171 bytes, __thiscall, ret 8).
// Per-step update of a creature's view: mirrors the creature's overhead effect, fades it with the
// distance to the reference point (avatar/camera), pushes the creature's state flags into the
// animation component (LOD, selection/"hover" effect messages) and, for plain creatures, writes the
// position/orientation back to the component when it is marked dirty.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (MSVC 2008 SP1).
#include <math.h>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;

// 3-vector; the user copy ctor makes copy-construction go through the FPU/SSE regs (movss) while the
// implicit assignment stays a plain dword copy, as in the original.
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Mat3 { float m[9]; };

// Message sent to effects / the animation component (0x38 bytes); u16 mask, u16 count of set fields.
struct XformMsg {
    u16   flags;      // +0x00  |2 = rotation, |4 = position
    u16   count;      // +0x02
    Vec3  pos;        // +0x04
    float scale;      // +0x10
    Mat3  rot;        // +0x14
    XformMsg();       // 0x00434040
};
struct Transform {
    u16   flags;
    u16   count;
    Vec3  pos;
    float scale;
    Mat3  rot;
    Transform();                                  // 0x00409930
    void SetB(const Vec3& up, const Vec3& dir);   // 0x006ba840 (MatOwner::SetB)
    void SetPosition(const Vec3& v) { flags |= 4; ++count; pos = v; }
    void SetScale(float s) { scale = s; ++count; }
};

struct cPlanetModel {
    void FUN_00b7e3b0(Vec3* out, const Vec3* in);          // 0x00b7e3b0
    const Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* in);   // 0x00b815a0
};
cPlanetModel* PlanetModel();                      // 0x00b3d350
int  GetCurrentGameMode();                        // 0x00b5b800
bool Vector3Equal(const Vec3* a, const Vec3* b);  // 0x004232c0 (cdecl)
float* Matrix3FromQuaternion(float* out, const void* q);   // 0x0059c190 (cdecl)
bool GetFloatProperty(const void* obj, u32 id, float* out); // 0x0040cf10 (cdecl)

// ---- globals ---------------------------------------------------------------------------------
extern Vec3  gReferencePos;       // 0x0167ea30
extern float gFadeFarSq;          // 0x015a87fc
extern float gFadeNearSq;         // 0x015a8800
extern float gLodNearSq;          // 0x015a8804
extern float gLodMidSq;           // 0x015a8808
extern int   gTerrainPropVersion; // 0x016c4bcc
extern Vec3  gZeroVec;            // 0x016c4bd8

struct cPropertyList {
    int GetModificationCount();       // 0x006237a0
};
struct cTerrainRecord {
    char pad[0x30];
    cPropertyList* mpProps;   // +0x30
    int  mVersion;            // +0x34
};
struct cTerrainMgr {
    cTerrainRecord* Fn2();            // 0x00b1de80
};
cTerrainMgr* GetTerrainMgr();                               // 0x00b3d320

struct cGameState { char pad[0xcc]; int mMode; };
extern cGameState* gGameState;                              // 0x016c7aa4

// Swarm visual effect (ref-counted); mOverheadEffect.
struct cIVisualEffect {
    void AddRef();                    // 0x00a02c30
    void Release();                   // 0x00a05270
    char pad[0x80];
    float mAlpha;                     // +0x80
    char pad2[0x180 - 0x84];
    struct cEffectState* mpState;     // +0x180
    void SetShown(int b);             // 0x00a047d0
    int  GetLevel();                  // 0x00a02bd0
};
struct cEffectState { int pad; u32 mFlags; };   // +4: bit0 "interactable", bit14, bit18

// Effects manager singleton (0x00b3d370).
struct cEffectsMgr {
    char pad[0x20];
    bool mEnabled;
    void Place(Transform* t, float f);   // 0x00ac7680
};
cEffectsMgr* GetEffectsMgr();            // 0x00b3d370

struct cCreatureBase;
// Receiver of effect messages.
struct cMsgTarget {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void Send(XformMsg* m);      // slot 6 (+0x18)
    virtual void s7();
    virtual void Prepare(XformMsg* m);   // slot 8 (+0x20)
};

// Animation component embedded at +0xc0 of the creature.
struct cAnimComp {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const Vec3* GetPosition();            // slot 11 (+0x2c)
    virtual const void* GetOrientation();         // slot 12 (+0x30)
    virtual float GetScale();                     // slot 13 (+0x34)
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual bool IsReady();                       // slot 18 (+0x48)
    virtual void SetFlag(bool b);                 // slot 19 (+0x4c)
    virtual void s20(); virtual void s21();
    virtual bool IsActive();                      // slot 22 (+0x58)
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual float GetHeight();                    // slot 28 (+0x70)
    virtual float GetRadius();                    // slot 29 (+0x74)
    char pad0[0x50 - 4];
    u32  mStateFlags;                             // +0x50 (creature +0x110); bit 11 = "needs name effect"
    char pad1[0x68 - 0x54];
    float mViewDistance;                          // +0x68 (creature +0x128)
    char pad2[0x74 - 0x6c];
    bool mDirty;                                  // +0x74 (creature +0x134)
    bool mHasView;                                // +0x75 (creature +0x135)
    bool pad3;
    bool mOnPlanet;                               // +0x77 (creature +0x137)
    bool IsDirty() const { return mDirty; }
    bool ConsumeDirty() { if (mDirty) { mDirty = false; return true; } return false; }
    void ClearNeedsNameEffect() { mStateFlags &= ~0x800u; }
    bool NeedsNameEffect() const { return (mStateFlags & 0x800) != 0; }
    void FUN_00c89d60(Transform* t);              // 0x00c89d60
    void FUN_00c8aa60();                          // 0x00c8aa60
};

struct cCreatureState { char pad[0x648]; int mCount648; char pad2[0x694 - 0x64c]; u32 mCount694; char pad3[0x69c - 0x698]; u32 mCount69c; };

// The animating creature (this->mpCreature).
class cAnimatingBase {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual u32  GetType();                       // slot 8 (+0x20)
    char pad0[0xc0 - 4];
};
class cAnimatingCreature : public cAnimatingBase, public cAnimComp {   // cAnimComp subobject at +0xc0
public:
    char pad1[0x330 - 0x138];
    int  m330;                                    // +0x330
    char pad2[0xb20 - 0x334];
    cCreatureState* mpState;                      // +0xb20
    char pad3[0xb54 - 0xb24];
    cIVisualEffect* mpOverheadEffect;             // +0xb54
    u32  mFlagsB58;                               // +0xb58 (bit 9 = fixed LOD)
    char pad4[0xb5d - 0xb5c];
    bool mbB5D;                                   // +0xb5d
    bool mbB5E;                                   // +0xb5e
    char pad5[0xbb0 - 0xb5f];
    bool mbBB0;                                   // +0xbb0
    char pad6[0xe58 - 0xbb1];
    float mfE58;                                  // +0xe58
    char pad7[0xe68 - 0xe5c];
    bool mbE68;                                   // +0xe68
    char pad8[0xf90 - 0xe69];
    bool mbF90;                                   // +0xf90

    void SetLOD(int lod);                         // 0x00c0c300
    const Vec3* GetBasePosition();                // 0x00c0e580
    bool FUN_00c0c130();                          // 0x00c0c130
    void SetEffectParam(bool v, u32 hash, u32 id);   // 0x00c201a0
    cMsgTarget* FindEffect(u32 id);               // 0x00c14e70
    void KillEffect(u32 id, int flag);            // 0x00c17350
    void CreateEffect(u32 hash, u32 id);          // 0x00c1d400
};

namespace SP {

class cCreatureView {
public:
    virtual void v0();
    virtual void HandleSimulationUpdate(int a, int b);   // slot 1 (+4)
    virtual void v2(); virtual void v3();
    virtual void SetOverheadShown(bool b);        // slot 4 (+0x10)
    virtual void v5();
    virtual void SetOverheadActive(bool b);       // slot 6 (+0x18)
    virtual bool IsOverheadActive();              // slot 7 (+0x1c)

    char pad0[8];
    cAnimatingCreature* mpCreature;               // +0x0c
    cIVisualEffect* mpOverheadEffect;             // +0x10
    bool mbShowOverhead;                          // +0x14

    void UpdateMotiveEffects();                   // 0x00e8bf20
    void CreatureCitizenUpdate(cAnimatingCreature* c);   // 0x00e8c070
};

}  // namespace SP

static __forceinline bool Bit(u32 v, int n) { u8 b = (u8)(v >> n); return (b & 1) != 0; }

// Smart-pointer assignment of the overhead effect (AutoRefCount operator=).
static __forceinline void AssignEffect(cIVisualEffect*& dst, cIVisualEffect* src)
{
    cIVisualEffect* old = dst;
    if (src != old) {
        if (src) src->AddRef();
        dst = src;
        if (old) old->Release();
    }
}

// Sends the animation-scale message to an effect target.
#define SEND_SCALE(T, C, GETTER) do { \
        XformMsg m; \
        (T)->Prepare(&m); \
        m.scale = (C)->GETTER(); \
        m.count += 1; \
        (T)->Send(&m); } while (0)

// @ 0x00E8C120
void SP::cCreatureView::HandleSimulationUpdate(int a, int b)
{
    if (!mpCreature->mHasView)
        return;

    AssignEffect(mpOverheadEffect, mpCreature->mpOverheadEffect);
    if (!mpOverheadEffect)
        return;

    // Refresh the squared LOD radii when the terrain property list changed.
    cTerrainRecord* terrain = GetTerrainMgr()->Fn2();
    if (terrain) {
        int mods = terrain->mpProps ? terrain->mpProps->GetModificationCount() : 0;
        int version = terrain->mVersion + mods;
        if (version != gTerrainPropVersion) {
            gTerrainPropVersion = version;
            GetFloatProperty(terrain, 0x52583bc, &gLodNearSq);
            gLodNearSq = gLodNearSq * gLodNearSq;
            GetFloatProperty(terrain, 0x52583d4, &gLodMidSq);
            gLodMidSq = gLodMidSq * gLodMidSq;
        }
    }

    // Squared distance to the reference point and the overhead-effect fade factor.
    const Vec3* pos = mpCreature->GetPosition();
    float dy = gReferencePos.y - pos->y;
    float dz = gReferencePos.z - pos->z;
    float dx = gReferencePos.x - pos->x;
    float distSq = dx * dx + dz * dz + dy * dy;
    mpCreature->mViewDistance = (float)sqrt(distSq);
    float alpha = 1.0f;
    if (distSq > gFadeFarSq)
        alpha = 0.0f;
    else if (distSq > gFadeNearSq)
        alpha = 1.0f - (distSq - gFadeNearSq) / (gFadeFarSq - gFadeNearSq);

    if (GetCurrentGameMode() != 0x1654c10 || gGameState->mMode != 1) {
        if (!IsOverheadActive())
            SetOverheadActive(true);
        SetOverheadShown(alpha > 0.0f);
    }

    int mode = GetCurrentGameMode();
    if (mode >= 0x1654c01 && (mode <= 0x1654c02 || mode == 0x1654c10))
        mbShowOverhead = false;

    if (mbShowOverhead && mpOverheadEffect->mAlpha > alpha)
        mpOverheadEffect->mAlpha = alpha;

    if (mpCreature->mbB5D) {
        mpOverheadEffect->SetShown(1);
        mpCreature->mbB5D = false;
        mpCreature->m330 = 0;
    }

    cEffectState* st = mpOverheadEffect->mpState;
    if (st) {
        bool lit = mpOverheadEffect->GetLevel() != 0;
        mpCreature->SetFlag(lit);
        if (mpCreature->mbF90)
            st->mFlags |= 1;
        else
            st->mFlags &= ~1u;
    }

    if (!Bit(mpCreature->mFlagsB58, 9)) {
        int lod = 2;
        if (distSq > gLodNearSq)
            lod = 0;
        else if (distSq > gLodMidSq)
            lod = 1;
        mpCreature->SetLOD(lod);
    }

    // Ground-contact effect for selected / interactable creatures.
    cEffectsMgr* fx = GetEffectsMgr();
    if (fx->mEnabled) {
        cEffectState* es = mpOverheadEffect->mpState;
        if (es && Bit(es->mFlags, 14) && !Bit(es->mFlags, 18)
            && mpCreature->IsReady() && mpCreature->mbF90) {
            Transform tr;
            Vec3 p = *mpCreature->GetBasePosition();
            if (Vector3Equal(&p, &gZeroVec))
                p = *mpCreature->GetPosition();
            Vec3 dir;
            PlanetModel()->FUN_00b7e3b0(&dir, &p);
            tr.SetB(Vec3(0.0f, 0.0f, 1.0f), dir);
            const Vec3* w = &p;
            Vec3 surf;
            if (!mpCreature->mOnPlanet)
                w = PlanetModel()->DirectionToSurfacePosition(&surf, &p);
            tr.SetPosition(Vec3(*w));
            tr.SetScale(mpCreature->GetHeight() * 2.0f);
            fx->Place(&tr, 1.0f);
        }
    }

    if (mpCreature->IsActive())
        UpdateMotiveEffects();

    cCreatureState* cs = mpCreature->mpState;
    if (cs->mCount648 > 0) {
        bool v = mpCreature->mfE58 > 0.0f;
        mpCreature->SetEffectParam(v, 0x5e361462, 0x73e4cdf);
        cMsgTarget* t = mpCreature->FindEffect(0x73e4cdf);
        if (t) SEND_SCALE(t, mpCreature, GetScale);
    } else {
        if (mpCreature->FindEffect(0x73e4cdf))
            mpCreature->KillEffect(0x73e4cdf, 0);
    }

    if (mpCreature->mpState->mCount69c > 0) {
        bool v = mpCreature->FUN_00c0c130();
        mpCreature->SetEffectParam(v, 0xdca300c0, 0x77492d8);
        cMsgTarget* t = mpCreature->FindEffect(0x77492d8);
        if (t) SEND_SCALE(t, mpCreature, GetScale);
    }

    if (mpCreature->mpState->mCount694 > 0) {
        mpCreature->SetEffectParam(mpCreature->mbBB0, 0xdaee4c72, 0x7e2fedf);
        cMsgTarget* t = mpCreature->FindEffect(0x7e2fedf);
        if (t) SEND_SCALE(t, mpCreature, GetScale);
    } else {
        if (mpCreature->FindEffect(0x7e2fedf))
            mpCreature->KillEffect(0x7e2fedf, 0);
    }

    {
        bool v = mpCreature->mbE68 && !mpCreature->mbB5E;
        mpCreature->SetEffectParam(v, 0xc29a026f, 0x7a16140);
        cMsgTarget* t = mpCreature->FindEffect(0x7a16140);
        if (t) SEND_SCALE(t, mpCreature, GetScale);
    }

    cAnimatingCreature* c = mpCreature;
    if (c && c->GetType() == 0x18eb4b7) {
        CreatureCitizenUpdate(c);
    } else if (mpCreature->mStateFlags & 0x800) {
        if (!mpCreature->FindEffect(0x6452ca4)) {
            mpCreature->CreateEffect(0x56192017, 0x6452ca4);
            cMsgTarget* t = mpCreature->FindEffect(0x6452ca4);
            if (t) SEND_SCALE(t, mpCreature, GetRadius);
        }
        mpCreature->ClearNeedsNameEffect();
    } else {
        if (mpCreature->FindEffect(0x6452ca4))
            mpCreature->KillEffect(0x6452ca4, 0);
    }

    // Write the component's position / orientation back when it was marked dirty.
    if (mpCreature->ConsumeDirty()) {
        Transform tr;
        const Vec3* p = mpCreature->GetPosition();
        tr.pos = *p;
        tr.flags |= 4;
        tr.count += 1;
        tr.scale = mpCreature->GetScale();
        tr.count += 1;
        Mat3 m;
        Matrix3FromQuaternion(m.m, mpCreature->GetOrientation());
        tr.rot = m;
        tr.flags |= 2;
        tr.count += 1;
        mpCreature->FUN_00c89d60(&tr);
    }
    mpCreature->FUN_00c8aa60();
}
