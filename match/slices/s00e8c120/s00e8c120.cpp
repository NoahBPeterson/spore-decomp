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

// Tagged allocation entry point used by the engine (0x00f473a0).
void* operator new(u32 size, u32 tag, int a, int b, int c, int d);

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

// ---- globals used by the effect-mirror view helpers ------------------------------------------
extern float kEffectNearDist;      // 0x01581338
extern float kFadeStep;            // 0x013f26dc
extern float kFadeMul;             // 0x013f9428
extern float kFadeBias;            // 0x013f4fd0
extern float kFadeLow;             // 0x013ec480
extern u32   kFadeTableA;          // 0x01486408
extern u32   kFadeTableB;          // 0x01486498
float FUN_005a6e00(float x);       // 0x005a6e00
u32   FUN_00b3d520(void* p);       // 0x00b3d520
void* FUN_00b3d2b0();              // 0x00b3d2b0
void* FUN_00b3d300();              // 0x00b3d300
void* FUN_00ac79d0(void* p);       // 0x00ac79d0
void* FUN_00bfc5f0(void* p);       // 0x00bfc5f0
bool  FUN_00c0b780(int p);         // 0x00c0b780
bool  FUN_00c8e870(int p);         // 0x00c8e870
void  FUN_00e92af0();              // 0x00e92af0
void* FUN_00e8bca0(void* self, void* tracked);   // 0x00e8bca0
void  FUN_00e8be60(void* self);    // 0x00e8be60
void  FUN_00e92a10(void* c);       // 0x00e92a10
void  FUN_00e92ca0(void* self, int a, int b);    // 0x00e92ca0
extern float kOneF;                // 0x01485720  1.0f
extern u32   kEffectViewVtbl;      // 0x01486518
static u32 kFadeConstLit = 0xb4b1178d;
union Int3 { int i; int v; };

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
    char pad2[0x128 - 0x84];
    struct cEffectParam* mp128;       // +0x128
    int   m12c;                       // +0x12c
    int   m130;                       // +0x130
    char pad3[0x180 - 0x134];
    struct cEffectState* mpState;     // +0x180
    void SetShown(int b);             // 0x00a047d0
    int  GetLevel();                  // 0x00a02bd0
    bool  IsInView();                 // 0x00c35d10
    void  FUN_00c35b60();             // 0x00c35b60
    void  FUN_00c88530(float d);      // 0x00c88530
};
struct cEffectState { int pad; u32 mFlags; };   // +4: bit0 "interactable", bit14, bit18

// Effect parameter block reached through cIVisualEffect::mp128.
struct cEffectParam {
    int  FUN_00c22850();                          // 0x00c22850
    void FUN_00c22870();                          // 0x00c22870
    void FUN_00c23300(const void* c, int f);      // 0x00c23300
};

// Transform owned by the animating creature at +0x34.
struct cTransform34 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void SetDist(float d);                // slot 16 (+0x40)  0x00c88530
    char pad[0x34];
};

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
    bool FUN_00c0c0e0();                          // 0x00c0c0e0
    void SetEffectParam(bool v, u32 hash, u32 id);   // 0x00c201a0
    cMsgTarget* FindEffect(u32 id);               // 0x00c14e70
    void KillEffect(u32 id, int flag);            // 0x00c17350
    void CreateEffect(u32 hash, u32 id);          // 0x00c1d400
    bool IsInView();                              // 0x00c35d10
    void FUN_00c35b60();                          // 0x00c35b60
    float FUN_00c41ec0();                         // 0x00c41ec0
    cTransform34* mp34;                           // +0x34
};

// Ref-counted view object (cCreatureView / cEffectView and friends).
struct cViewBase {
    virtual void s0(); virtual void s1();
    char pad[0x28 - 8];
    void FUN_00b3d520();                          // 0x00b3d520
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
    char pad1[3];
    int  mState;                                  // +0x1c  0/1/2 effect lifecycle state
    float mAccum;                                 // +0x20  accumulated fade accumulator

    void UpdateMotiveEffects();                   // 0x00e8bf20
    void CreatureCitizenUpdate(cAnimatingCreature* c);   // 0x00e8c070
    void HandleUpdate(int a, int b);              // 0x00e8ca10
    void HandleMessage(int a, int b);             // 0x00e8cf50
};

// Object produced by the tracked-effect factory (0x24 bytes, vtable 0x14605e4).
struct cTrackedEffect {
    void* mpVtbl;        // +0x00
    u32   m04;           // +0x04
    u32   m08;           // +0x08
    u32   m0c;           // +0x0c
    u32   m10;           // +0x10
    u8    mb14;          // +0x14
    char  pad[3];
    u32   m18;           // +0x18
    u32   m1c;           // +0x1c
    float m20;           // +0x20
};

// The effect-mirror view (a sibling of cCreatureView sharing the base layout) that owns the
// per-frame opacity update.
class cEffectView {
public:
    virtual void v0();
    virtual void HandleUpdate(int a, int b);      // slot 1 (+4)
    virtual void v2(); virtual void v3();
    virtual void SetShown(bool b);                // slot 4 (+0x10)
    virtual void v5();
    virtual void SetActive(bool b);               // slot 6 (+0x18)
    virtual bool IsActive();                      // slot 7 (+0x1c)

    char pad0[8];
    cAnimatingCreature* mpCreature;               // +0x0c
    cIVisualEffect* mpEffect;                     // +0x10
    bool mbActive;                                // +0x14
    char pad1[3];
    Vec3  mVec;                                   // +0x18
    u32   m24;                                    // +0x24
    u32   m28;                                    // +0x28
    u32   m2c;                                    // +0x2c
    u32   m30;                                    // +0x30
    u32   m34;                                    // +0x34
    u32   m38;                                    // +0x38
    u32   m3c;                                    // +0x3c

    void SetTrackedEffect(cAnimatingCreature* c); // 0x00e8c9a0
    cEffectView* Initialize();                    // 0x00e8cc90
    Vec3* ComputeFade(Vec3* out, int& ok, void* c);   // 0x00e8cd30
    cEffectView* CreateFor(cAnimatingCreature* c);                  // 0x00e8cec0
    void HandleMessage(int a, int b);             // 0x00e8cf50
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

// @ 0x00E8C9A0
void SP::cEffectView::SetTrackedEffect(cAnimatingCreature* c)
{
    // The tracked object is produced by a factory carrying the type key 0xce9f6639; the result
    // (null or not) is handed to the per-view hook together with the freshly built view state.
    cTrackedEffect* tracked = 0;
    if (c)
        tracked = (cTrackedEffect*)((void* (__thiscall*)(void*, u32))((*((void***)c))[3]))(c, 0xce9f6639);

    cTrackedEffect* v = (cTrackedEffect*)operator new(0x24, 0x1460e9c, 0, 0, 0, 0);
    if (v) {
        v->m08 = 0;
        v->m04 = 0;
        v->m0c = 0;
        v->m10 = 0;
        v->mb14 = 1;
        v->m18 = 0;
        v->mpVtbl = (void*)0x14605e4;
    } else {
        v = 0;
    }
    v->m1c = 0;
    v->m20 = 0.0f;
    ((void (__thiscall*)(void*, cTrackedEffect*))FUN_00e8bca0)(v, tracked);
}

// @ 0x00E8CA10
void SP::cCreatureView::HandleUpdate(int a, int b)
{
    cAnimatingCreature* c = mpCreature;
    if (!c || c->GetType() != 0x18eb45e)
        c = 0;

    bool early = GetCurrentGameMode() == 0x1654c01;
    bool r;
    if (early)
        r = !c->IsActive() && !c->mbB5E && !c->FUN_00c0c0e0();
    else
        r = !c->FUN_00c0c0e0();
    mbShowOverhead = r;

    HandleSimulationUpdate(a, b);

    if (GetCurrentGameMode() == 0x1654c10) {
        if (c->IsActive())
            FUN_00e92a10(c);
        if (c->m330 & 1) {
            if (c->FUN_00c41ec0() > kEffectNearDist) {
                if (!c->FindEffect(0x6885174))
                    c->CreateEffect(0x57619fab, 0x6885174);
            }
        } else {
            c->KillEffect(0x6885174, 0);
        }
    } else {
        if (c->IsActive())
            goto done;
        if (mState == 0) {
            if (!c->mHasView)
                goto done;
            mState = 1;
            mAccum = 0.0f;
            c->mFlagsB58 |= 0x800;
            if (c->mpOverheadEffect)
                c->mpOverheadEffect->mAlpha = 0.0f;
            goto done;
        }
        if (mState == 1) {
            if (!c->mHasView) {
                mState = 0;
                goto done;
            }
            c->mFlagsB58 |= 0x800;
            if (!c->mpOverheadEffect)
                goto done;
            float step = (float)b * kFadeMul + kFadeBias;
            float low = c->FUN_00c0c130() ? kFadeLow : 1.0f;
            mAccum += step;
            float scaled = mAccum * kFadeStep;
            float prev = FUN_005a6e00(scaled);
            c->mpOverheadEffect->mAlpha = prev * low;
            if (mAccum <= prev)
                goto done;
            if (!c->FUN_00c0c130())
                c->mFlagsB58 &= ~0x800u;
            mState = 2;
            goto done;
        }
        // mState == 2
        if (!c->mHasView)
            goto done;
        mState = 0;
        goto done;
    }

done:
    if (!early)
        FUN_00e8be60(this);
}

// @ 0x00E8CC90
SP::cEffectView* SP::cEffectView::Initialize()
{
    FUN_00e92af0();
    Vec3 one;
    one.x = kOneF;
    one.y = kOneF;
    one.z = kOneF;
    mVec = one;                // +0x18
    m24 = 0x3f6368f1;          // +0x24
    m28 = 0;                   // +0x28
    *(void**)this = (void*)kEffectViewVtbl;   // +0x00
    m2c = 0x5c4fce4c;          // +0x2c
    m34 = 0;                   // +0x34
    m38 = 1;                   // +0x38
    m3c = 0;                   // +0x3c
    return this;
}

// @ 0x00E8CD30
Vec3* SP::cEffectView::ComputeFade(Vec3* out, int& ok, void* c)
{
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;

    cIVisualEffect* fx = 0;
    if (c) {
        fx = (cIVisualEffect*)((void* (__stdcall*)(void*, u32))((*((void***)c))[3]))(c, 0x4ffcdeda);
        if (fx)
            fx->AddRef();
    }
    if (fx) {
        int a = fx->m12c;
        fx->FUN_00c35b60();
        int b = fx->m130;

        if (m34 == (u32)a && m38 == (u32)b && m3c == 0) {
            out->x = *(float*)&m24;
            out->y = *(float*)&m28;
            out->z = *(float*)&m2c;
        } else {
            m34 = (u32)a;
            m38 = (u32)b;
            m3c = 0;

            cEffectParam* p1 = fx->mp128;
            int v1 = p1 ? (int)((void* (__stdcall*)(cEffectParam*, u32))((*((void***)p1))[5]))(p1, 0x4f176642) : 0;
            cEffectParam* p2 = fx->mp128;
            int v2 = p2 ? (int)((void* (__stdcall*)(cEffectParam*, u32))((*((void***)p2))[5]))(p2, 0x4f396a66) : 0;

            if (fx->mp128 == FUN_00ac79d0(FUN_00b3d2b0()))
                v2 = (int)FUN_00bfc5f0(FUN_00b3d300());

            if ((v1 && FUN_00c0b780(v1)) || (v2 && !FUN_00c8e870(v2)))
                ;   // fall through
            else if (a == 3)
                a = 0;

            int sel;
            if (ok == 1) {
                if (a <= 4 && b <= 6)
                    sel = ((int*)&kFadeTableA)[(a * 7) + b];
                else
                    sel = 0;
            } else {
                sel = ((int*)&kFadeTableB)[b + a * 4];
            }

            out->x = *(float*)&sel;
            out->y = (float)m28;
            out->z = *(float*)&kFadeConstLit;
        }
        fx->Release();
    }
    return out;
}

// @ 0x00E8CEC0
SP::cEffectView* SP::cEffectView::CreateFor(cAnimatingCreature* c)
{
    cEffectView* v = (cEffectView*)operator new(0x40, 0x1460d64, 0, 0, 0, 0);
    if (v)
        v = v->Initialize();

    Vec3 tmp;
    Int3 ok;
    mpCreature = c;
    mVec.x = 1.0f;
    mVec.y = 1.0f;
    mVec.z = 1.0f;
    ok.v = 0;
    ComputeFade(&tmp, ok.i, c);
    m24 = *(u32*)&tmp.x;
    m28 = *(u32*)&tmp.y;
    m2c = *(u32*)&tmp.z;

    int h = FUN_00b3d520(this);
    ((void (__stdcall*)(cEffectView*, void*, int))((*((void***)v))[10]))(v, &m24, h);
    return v;
}

// @ 0x00E8CF50
void SP::cEffectView::HandleMessage(int a, int b)
{
    FUN_00e92ca0(this, a, b);

    cAnimatingCreature* c = mpCreature;
    cIVisualEffect* fx = 0;
    if (c) {
        fx = (cIVisualEffect*)((void* (__stdcall*)(cAnimatingCreature*, u32))((*((void***)c))[3]))(c, 0x4ffcdeda);
        if (fx)
            fx->AddRef();
    }

    bool inView = fx && fx->IsInView();
    SetActive(!inView);

    if (!IsActive()) {
        if (fx)
            fx->Release();
        return;
    }

    Vec3 tmp;
    ComputeFade(&tmp, (int&)b, fx);

    if (!(tmp.x == (float)m24 && tmp.y == (float)m28 && tmp.z == (float)m2c)) {
        cEffectParam* p = fx->mp128;
        cEffectParam* saved = p;
        if (p) {
            p = (cEffectParam*)((void* (__stdcall*)(cEffectParam*, u32))((*((void***)p))[5]))(p, 0x4f176642);
            if (p && p->FUN_00c22850() == 1)
                p->FUN_00c22870();
        }
        if (kEffectNearDist > (float)fx->m130)
            fx->FUN_00c88530(kEffectNearDist);
        else
            c->mp34->SetDist(kEffectNearDist);

        m24 = *(u32*)&tmp.x;
        m28 = *(u32*)&tmp.y;
        m2c = *(u32*)&tmp.z;

        int h = FUN_00b3d520(this);
        ((void (__stdcall*)(cEffectView*, u32*, int))((*((void***)this))[10]))(this, &m24, h);
        ((void (__stdcall*)(cEffectView*, u32*))((*((void***)this))[3]))(this, &m24);

        if (saved && saved->FUN_00c22850() == 1)
            saved->FUN_00c23300(c, -1);
    }

    if (fx)
        fx->Release();
}


