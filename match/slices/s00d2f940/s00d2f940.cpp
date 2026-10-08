// slice s00d2f940 -- creature mode: acknowledgement-effect spawner (0x00d2f940) and
// the click-target classifier (0x00d2ffd0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: a smart-pointer local without an EH frame)
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vec3 { float x, y, z; };
struct Matrix3 { float m[9]; };
struct BBox { Vec3 mMin, mMax; };

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModCount;
    Vec3     mOffset;
    float    mScale;
    Matrix3  mRotation;
    cSPTransform();                         // 0x00409930
    void SetOffset(const Vec3& v) { mOffset = v; mFlags |= 4; mModCount++; }
    void SetOffsetOOL(const Vec3* v);       // 0x00571d40 (out-of-line copy)
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mModCount++; }
};

// effect message (same layout as cSPTransform; ctor 0x00434040)
struct XformMsg {
    uint16_t mFlags;
    uint16_t mCount;
    Vec3     mPos;
    float    mScale;
    Matrix3  mRot;
    XformMsg();                             // 0x00434040
    void SetPos(const Vec3& v)  { mPos = v; mFlags |= 4; ++mCount; }
    void SetScale(float s)      { mScale = s; ++mCount; }
    void SetRot(const Matrix3& m) { mRot = m; mFlags |= 2; ++mCount; }
};

// spatial subobject: vptr, GetBBox at slot 0x6c
struct cSpatialObject {
    PV8 PV8 PV4 PV2
    virtual bool VSlot58();                 // 0x58
    PV4
    virtual BBox GetBBox();                 // 0x6c (struct returned through a hidden pointer)
    void LocalToWorldTransform(cSPTransform* out);   // 0x00c897e0
};

struct IVisualEffect {
    virtual void AddRef();
    virtual void Release();
    virtual void Start(int hard);           // 0x08
    virtual void Stop(int hard);            // 0x0c
    virtual void v10(); virtual void v14();
    virtual void SetSourceTransform(XformMsg* m);    // 0x18
};
// intrusive pointer to an effect (inline AddRef / Release as in the original)
struct EffectPtr {
    IVisualEffect* p;
    EffectPtr() : p(0) {}
    EffectPtr(IVisualEffect* q) : p(q) { if (p) p->AddRef(); }
    ~EffectPtr() { if (p) p->Release(); }
    void reset() { IVisualEffect* q = p; if (q) { p = 0; q->Release(); } }
    EffectPtr& operator=(const EffectPtr& o);        // 0x00ac9480
};
struct IEffectsManager {
    PV8 PV2 PV
    virtual bool CreateEffect(uint32_t id, uint32_t group, EffectPtr* out);   // 0x2c
};
IEffectsManager* __cdecl EffectsManager();           // 0x0067ddd0

struct cPlanetModel {
    Vec3* SnapA(Vec3* out, const Vec3* in, int flag);     // 0x00b82b40
    Vec3* SnapB(Vec3* out, const Vec3* in, int flag);     // 0x00b82970
    Vec3* Facing(Vec3* out, const Vec3* in);              // 0x00b7e3b0
};
cPlanetModel* __cdecl PlanetModel();                      // 0x00b3d350
void __cdecl normalized_safe(Vec3* out, const Vec3* in);  // 0x00449c20
void __cdecl OrthogonalVector(Vec3* out, const Vec3* in);         // 0x006985b0
void __cdecl Matrix3FromFacingAndUp(Matrix3* out, const Vec3* f, const Vec3* up);   // 0x0069b440

struct ObjHdr {
    PV PV PV
    virtual void* Query(uint32_t id);       // 0x0c
    PV4
    virtual uint32_t GetTypeID();           // 0x20
    PV2
    virtual bool IsDestroyed();             // 0x2c
};
void* __cdecl ObjCast(ObjHdr* obj, uint32_t typeId);      // 0x00ac80d0

struct cEffectOwner { char pad[0x48]; EffectPtr mEffect; };      // field +0x48 holds the live effect
struct OwnerRef {                           // smart-pointer-like holder at strategy+0x68
    cEffectOwner* mp;
    bool IsNull() const { return mp == 0; }
    cEffectOwner* operator->() const { return mp; }
};
struct VoidRef { void* mp; void* get() const { return mp; } };
struct cCreatureModeStrategy {
    char pad[0x68];
    OwnerRef mOwner;                        // +0x68
    char pad6c[0xb4 - 0x6c];
    VoidRef  mRefB4;                        // +0xb4
    static cCreatureModeStrategy* Instance();           // 0x00d38840
};

// cast targets (same object as the ObjHdr; only the fields used here)
struct ObjSpatial34 : ObjHdr { char pad04[0x34 - 4]; cSpatialObject mSp34; };   // +0x34
struct ObjFlags : ObjHdr { char pad04[0x34 - 4]; cSpatialObject mSp34; char pad38[0x84 - 0x38]; uint32_t mFlags; };   // +0x84
struct ObjWithState : ObjFlags { char pad88[0x16c - 0x88]; int mState; };        // +0x16c
struct ObjWithMode : ObjFlags { char pad88[0x110 - 0x88]; int mMode; };          // +0x110
struct ObjWithSp0 : ObjHdr { char pad04[0xc0 - 4]; cSpatialObject mSpC0; };      // +0xc0

// anonymous namespace in the original
namespace {

// @ 0x00d2f940
void SpawnAcknowledgementEffect(int a1, int a2, ObjHdr* obj)
{
    if (cCreatureModeStrategy::Instance()->mOwner.IsNull()) return;
    EffectPtr effect(cCreatureModeStrategy::Instance()->mOwner->mEffect.p);
    if (effect.p) effect.p->Stop(1);
    effect.reset();
    if (!obj || obj->IsDestroyed()) goto done;
    {
        cSPTransform xform;
        bool orient = false;        // A: build the rotation from the position direction
        bool snapA = false;         // B: snap to planet surface (variant 1)
        bool snapB = false;         // C: snap to planet surface (variant 2)
        bool facing = false;        // D: rotation from planet facing
        uint32_t effectId = 0;
        Vec3 dir;
        switch (obj->GetTypeID()) {
        case 0x2a8fb3f: {
            ObjSpatial34* o = (ObjSpatial34*)ObjCast(obj, 0x2a8fb3f);
            effectId = 0x4ae30884;
            const BBox& bb = o->mSp34.GetBBox();
            const BBox* b = &bb;
            dir.x = (b->mMin.x + b->mMax.x) * 0.5f;
            dir.y = (b->mMax.y + b->mMin.y) * 0.5f;
            dir.z = (b->mMax.z + b->mMin.z) * 0.5f;
            xform.SetOffset(dir);
            facing = true;
            snapB = true;
            break;
        }
        case 0x2a034cd: {
            ObjFlags* o = (ObjFlags*)ObjCast(obj, 0x2a034cd);
            facing = true;
            orient = (o->mFlags & 0x1000) == 0x1000;
            snapA = true;
            effectId = 0x4ae30884;
            const BBox& bb = o->mSp34.GetBBox();
            const BBox* b = &bb;
            dir.x = (b->mMin.x + b->mMax.x) * 0.5f;
            dir.y = (b->mMax.y + b->mMin.y) * 0.5f;
            dir.z = (b->mMax.z + b->mMin.z) * 0.5f;
            xform.SetOffset(dir);
            break;
        }
        case 0x18eb45e: {
            ObjWithSp0* o = (ObjWithSp0*)ObjCast(obj, 0x18eb45e);
            if (!((a1 == 8 && a2 == 0) || (a1 == 0x40000 && a2 == 0))) return;
            effectId = 0x4ae30884;
            o->mSpC0.LocalToWorldTransform(&xform);
            break;
        }
        case 0x2c9cc91: {
            ObjWithState* o = (ObjWithState*)ObjCast(obj, 0x2c9cc91);
            orient = (o->mFlags & 0x1000) == 0x1000;
            const BBox& bb = o->mSp34.GetBBox();
            const BBox* b = &bb;
            dir.x = (b->mMax.x + b->mMin.x) * 0.5f;
            dir.y = (b->mMax.y + b->mMin.y) * 0.5f;
            dir.z = (b->mMax.z + b->mMin.z) * 0.5f;
            xform.SetOffset(dir);
            int st = o->mState;
            if (st == 0 || st == 1 || st == 3) {
                effectId = 0x742deb5b;
            } else {
                facing = true;
                effectId = 0x4ae30884;
                snapA = true;
            }
            break;
        }
        case 0x3a2511e: {
            ObjWithMode* o = (ObjWithMode*)ObjCast(obj, 0x3a2511e);
            switch (o->mMode) {
            case 1:
            case 3:
                orient = (o->mFlags & 0x1000) == 0x1000;
                effectId = 0x4ae30884;
                break;
            case 2:
            case 6:
                effectId = 0x4ae30884;
                break;
            default:
                break;
            }
            facing = true;
            snapA = true;
            const BBox& bb = o->mSp34.GetBBox();
            const BBox* b = &bb;
            dir.x = (b->mMin.x + b->mMax.x) * 0.5f;
            dir.y = (b->mMax.y + b->mMin.y) * 0.5f;
            dir.z = (b->mMax.z + b->mMin.z) * 0.5f;
            xform.SetOffset(dir);
            if (effectId == 0) goto done;
            break;
        }
        case 0x52aa6122: {
            ObjSpatial34* o = (ObjSpatial34*)ObjCast(obj, 0x52aa6122);
            o->mSp34.LocalToWorldTransform(&xform);
            effectId = 0x4ae30884;
            break;
        }
        default:
            goto done;
        }

        cPlanetModel* pm = PlanetModel();
        Vec3 up;
        if (snapA) {
            xform.SetOffsetOOL(pm->SnapA(&up, &xform.mOffset, 0));
        } else if (snapB) {
            xform.SetOffsetOOL(pm->SnapB(&up, &xform.mOffset, 0));
        }
        Matrix3 rot;
        if (orient) {
            normalized_safe(&dir, &xform.mOffset);
            OrthogonalVector(&up, &dir);
            Matrix3FromFacingAndUp(&rot, &up, &dir);
            xform.mRotation = rot;
            xform.mFlags |= 2;
            xform.mModCount++;
        } else if (facing) {
            pm->Facing(&dir, &xform.mOffset);
            OrthogonalVector(&up, &dir);
            Matrix3FromFacingAndUp(&rot, &up, &dir);
            xform.mRotation = rot;
            xform.mFlags |= 2;
            xform.mModCount++;
        }
        XformMsg msg;
        msg.SetRot(xform.mRotation);
        msg.SetPos(xform.mOffset);
        msg.SetScale(1.0f);
        IEffectsManager* em = EffectsManager();
        effect.reset();
        if (em->CreateEffect(effectId, 0, &effect)) {
            effect.p->SetSourceTransform(&msg);
            effect.p->Start(0);
            cCreatureModeStrategy::Instance()->mOwner->mEffect = effect;
        }
    }
done:
    ;
}

}   // namespace

// =============================================================================================
// @ 0x00d2ffd0  Click-target classifier: picks the creature-mode action (0..0x1c) for a target.
// =============================================================================================
struct IUnused {};
struct cSPCreatureBase;
struct cInteractionState {                       // gGlobals->mpState (+0x78)
    int  FUN_00f1a320(cSPCreatureBase* who, ObjHdr* target, char* outFlag);   // 0x00f1a320
    bool FUN_00f1a640(int idx);                  // 0x00f1a640
    bool FUN_00f1a440(int idx, ObjHdr* target);  // 0x00f1a440
};
struct cInteractionGlobals { char pad[0x78]; cInteractionState* mpState; };
extern cInteractionGlobals* gInteraction;        // 0x016c7aa4
extern char gFlag01582df6;                       // 0x01582df6

struct cSPCreatureBase {
    PV8 PV8 PV8 PV8 PV8 PV8 PV4 PV
    virtual bool VSlotD4();                      // 0xd4
    char pad[0xb20 - 4 - 0xd4 - 4];
    int  mB20;
    char padb24[0xb48 - 0xb24];
    struct cSub48* mpB48;
    struct cSub4c* mpB4C;
    char padb50[0xb58 - 0xb50];
    uint32_t mB58;
    char padb5c[0xb5e - 0xb5c];
    char mB5E;
    // methods (all thiscall)
    int   FUN_00c0ee60();                        // returns +0xe7c
    cSPCreatureBase* GetTargetAsCreature();      // 0x00c0ee70
    int   FUN_00c0f620();
    int   FUN_00c0f780();
    int   FUN_00c0f8a0(int idx);
    int   FUN_00c0f8f0(void* o);
    struct cB2* FUN_00c04750();
    float FUN_00c0bb10();
    bool  FUN_00c0b770();
    int   FUN_00c0bc00();
    bool  FUN_00c0c0e0();
    int   GetSocialGoal();                       // 0x00c0e6a0
    bool  FUN_00bfc480();
    bool  FUN_00c13c60(int a, int b, bool c);
    int   FUN_00c6aa30();
};
struct cSub48 { int FUN_00bca0c0(int a, int b, int c, int d); };
struct cSub4c { char pad[0x1d8]; int mState; };
struct cB2 { char pad[2]; char mB2; };

struct cAvatarSystem { int FUN_00ba3f90(int a, void* b, void* c); };
cAvatarSystem* __cdecl FUN_00b3d4c0();           // singleton getter

struct cNounManager {
    cSPCreatureBase* GetAvatar();                // 0x00b1fdb0
    struct cTerrainSphere* GetCurrentTerrainSphere(uint32_t id);   // 0x00f67d90
};
struct cTerrainSphere { bool FUN_00c773d0(); };
cNounManager* __cdecl NounManager();             // 0x00b3d300
int  __cdecl GetCurrentGameMode();               // 0x00b5b800
bool __cdecl FUN_00f0a690(ObjHdr* o);
struct cObjB { char pad[0x38]; int mF38; };
cObjB* __cdecl FUN_00bd8460(ObjHdr* o);
cSPCreatureBase* __cdecl FUN_00ae6740(ObjHdr* o);
ObjHdr* __cdecl FUN_00ae66d0(int h);
int  __cdecl FUN_00d2e490();
int  __cdecl FUN_00d2ec30(int h);
bool __cdecl FUN_00d2ede0(int h);
bool __cdecl FUN_0064f350(void* a, uint32_t id, int b);
struct cObjC { char pad[0x110]; int mF110; };
cObjC* __cdecl FUN_00c0c3c0(void* o);

struct cEvtTarget { char pad[0x50]; uint32_t mF50; char pad54[0x70 - 0x54]; char mF70; };   // result of the +0xc query
struct cObjF4 { char pad[0xa4]; int mA4; };
struct cObjClick2a034cd : ObjHdr { char pad4[0x1e8 - 4]; int mState; char pad1ec[0x1f4 - 0x1ec]; cObjF4* mpF4; };
struct cObjClick2c9cc91 : ObjHdr { char pad4[0xa4 - 4]; char mA4; char pada5[0x16c - 0xa5]; int mState; };
struct cObjSp34 : ObjHdr { char pad4[0x34 - 4]; cSpatialObject mSp34; int FUN_00c6aa30(); };

// @ 0x00d2ffd0
int __cdecl ClassifyTarget(ObjHdr* obj, uint8_t* pHandled)
{
    *pHandled = 1;
    cSPCreatureBase* avatar = NounManager()->GetAvatar();
    bool inGameS;
    char flagS;
    int idxS;
    switch (obj->GetTypeID()) {
    case 0x18c88e4: {
        cObjB* ob = FUN_00bd8460(obj);
        if (GetCurrentGameMode() == 0x1654c10 && FUN_00f0a690(obj)) return 0x12;
        if (ob->mF38 != 0xf) goto notHandled;
        goto head2;
    }
    case 0x70703b3:
    head2:
        inGameS = GetCurrentGameMode() == 0x1654c10;
        if (inGameS && FUN_00f0a690(obj)) return 0x12;
        flagS = 0;
        idxS = inGameS ? gInteraction->mpState->FUN_00f1a320(avatar, obj, &flagS) : avatar->FUN_00c0f780();
        goto haveIdx;
    case 0x18c6de8:
        inGameS = GetCurrentGameMode() == 0x1654c10;
        if (inGameS && FUN_00f0a690(obj)) return 0x12;
        flagS = 0;
        idxS = inGameS ? gInteraction->mpState->FUN_00f1a320(avatar, obj, &flagS) : avatar->FUN_00c0f780();
    haveIdx:
        if (idxS == -1) {
            cSPCreatureBase* cr = FUN_00ae6740(obj);
            if (cr->FUN_00bfc480()) goto notHandled;
            if (avatar->FUN_00c0ee60() != (int)cr) return 7;
            return (FUN_00d2e490() != 0 ? 3 : 0) + 0xe;
        }
        if (FUN_00d2e490() == 0 || flagS) {
            if (avatar->mpB4C->mState == 0x39f6486) goto notHandled;
            if (inGameS && !gInteraction->mpState->FUN_00f1a440(idxS, obj)) goto notHandled;
            return 0xc;
        }
        if (inGameS && !gInteraction->mpState->FUN_00f1a640(idxS)) goto notHandled;
        return 0xd;
    case 0x18eb45e: {
        cSPCreatureBase* c = (cSPCreatureBase*)ObjCast(obj, 0x18eb45e);
        cSPCreatureBase* tgt = avatar->GetTargetAsCreature();
        bool isTarget = (c == tgt);
        bool sameTeam = (c->mB20 == avatar->mB20);
        if (avatar == c) {
            if (GetCurrentGameMode() == 0x1654c10) return 0x1c;
            int idx = avatar->FUN_00c0f780();
            if (idx == -1) return 0;
            ObjHdr* o = FUN_00ae66d0(avatar->FUN_00c0f8a0(idx));
            if (!o) return 0;
            uint32_t t = o->GetTypeID();
            if (t == 0x2a8fb3f || t == 0x3a2511e) return 6;
            return 0;
        }
        bool b = false;
        if (c->FUN_00c04750() && c->FUN_00c04750()->mB2 != 0) b = true;
        bool inGame = GetCurrentGameMode() == 0x1654c10;
        if (inGame && (c->mB5E == 0 || b)) {
            if (FUN_00f0a690(obj)) return 0x12;
        }
        if (c->mB5E != 0) {
            if (gFlag01582df6) {
                int idx = avatar->FUN_00c0f780();
                if (idx != -1 && FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) == 0) return 0x16;
            }
            if (sameTeam) return 0;
            if (!(c->FUN_00c0bb10() > 0.0f)) return 0;
            if (GetCurrentGameMode() == 0x1654c10) return 0;
            return 8;
        }
        char flag = 0;
        int idx = inGame ? gInteraction->mpState->FUN_00f1a320(avatar, obj, &flag) : avatar->FUN_00c0f780();
        if (idx != -1) {
            if (FUN_00d2e490() == 0 || flag) {
                if (c->FUN_00c0b770() && avatar->mpB4C->mState != 0x39f6486) {
                    int h = avatar->FUN_00c0f8a0(idx);
                    if (c->FUN_00c13c60(h, 1, !inGame)) {
                        if (!inGame) return 0xc;
                        if (gInteraction->mpState->FUN_00f1a440(idx, obj)) return 0xc;
                    }
                }
            } else if (!inGame || gInteraction->mpState->FUN_00f1a640(idx)) {
                int h = avatar->FUN_00c0f8a0(idx);
                if (!((c->mB58 >> 8 & 1) && FUN_00d2ede0(h))) return 0xd;
            }
        }
        uint32_t v = c->mB58;
        if (v >> 4 & 1) return 9;
        if (!isTarget) return 7;
        if (v >> 8 & 1) return 0xa;
        if (FUN_00d2e490() == 0) {
            if (avatar->mpB4C->mState == 0x39f6486) return 0xb;
            if (FUN_00b3d4c0()->FUN_00ba3f90(c->FUN_00c0bc00(), c, avatar) == 5 &&
                c->mpB48->FUN_00bca0c0(2, 1, 0, 0) == -1)
                return 0xe;
            if (GetCurrentGameMode() == 0x1654c10 && c->FUN_00c0c0e0()) return 0xe;
            if (c->GetSocialGoal() == 0 && c->VSlotD4()) return 0x10;
            return 0xf;
        }
        if (FUN_0064f350(cCreatureModeStrategy::Instance()->mRefB4.get(), 0x39b674a2, 0) &&
            avatar->FUN_00c13c60((int)((char*)c + 0xc0), 0, 1))
            return 0x19;
        return sameTeam ? 0 : 0x11;
    }
    case 0x18ebadc:
        return 0x1b;
    case 0x2a034cd: {
        cObjClick2a034cd* o = (cObjClick2a034cd*)ObjCast(obj, 0x2a034cd);
        if (o->mpF4 && o->mpF4->mA4 && o->mpF4->mA4 != avatar->mB20 && FUN_00d2e490() == 1 &&
            o->mState != 4 && o->mState != 5 && o->mState != 3) {
            if (FUN_00b3d4c0()->FUN_00ba3f90(o->mpF4->mA4 + 0x504, 0, 0) != 6) return 0x15;
        }
        int idx = avatar->FUN_00c0f780();
        if (idx == -1) goto notHandled;
        if (FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) != 0) goto notHandled;
        return 0x16;
    }
    case 0x2a8fb3f:
    case 0x3a2511e: {
        cEvtTarget* o = (cEvtTarget*)obj->Query(0x1186577);
        if (o->mF50 & 0x100) {
            return avatar->FUN_00c0f8f0(o) != -1 ? 0x18 : 0;
        }
        if (GetCurrentGameMode() == 0x1654c10 && FUN_00f0a690(obj)) return 0x12;
        if (o->mF70 == 0) goto notHandled;
        if (avatar->FUN_00c13c60((int)o, 0, GetCurrentGameMode() != 0x1654c10)) {
            if (avatar->FUN_00c0f620() == -1) {
                int idx = avatar->FUN_00c0f780();
                if (idx != -1 && FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) == 0) return 0x16;
            }
            return 0x19;
        }
        cObjC* t = FUN_00c0c3c0(o);
        if (t && t->mF110 == 2) return 0x1a;
        goto notHandled;
    }
    case 0x2c9cc91: {
        cObjClick2c9cc91* o = (cObjClick2c9cc91*)ObjCast(obj, 0x2c9cc91);
        if (o->mA4 == 0) goto notHandled;
        int st = o->mState;
        if (st == 4) goto notHandled;
        if (st == 0) {
            int idx = avatar->FUN_00c0f780();
            if (idx != -1 && FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) == 0) return 0x16;
        }
        return 0x17;
    }
    case 0x52aa6122: {
        cObjSp34* o = obj->GetTypeID() == 0x52aa6122 ? (cObjSp34*)obj : 0;
        if (o->FUN_00c6aa30() != avatar->mB20) goto notHandled;
        if (!o->mSp34.VSlot58()) {
            if (!NounManager()->GetCurrentTerrainSphere(0x514a219)->FUN_00c773d0()) return 0x14;
        }
        int idx = avatar->FUN_00c0f780();
        if (idx == -1) goto notHandled;
        if (FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) != 0) goto notHandled;
        return 0x13;
    }
    default:
        break;
    }
notHandled:
    *pHandled = 0;
    return 0;
}
