// Slice s00e8a510: SP::cBuildingView::HandleSimulationUpdate (0x00E8A510, 4747 bytes,
// __thiscall, ret 8).  Per-step update of a building view: drives the damage-state
// swarm effects (smoke / fire), the city-hall shield / stun / cling effects, the
// UFO-abduction ambient effects and the "lightning" cadence in space-stage.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE (MSVC 2008 SP1).
//
// Callees of unknown type are declared with the minimal signature seen in the asm.
// Virtual calls on objects whose class is not recovered use VCn(ret, obj, byteoffset, ...).

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

// ---- raw virtual-call / field helpers -------------------------------------------------
#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))
#define VC4(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4))
#define VC5(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4, T5, a5) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4, T5))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4), (a5))
#define FU8(p, off)   (*(u8*)((char*)(p) + (off)))
#define FI32(p, off)  (*(int*)((char*)(p) + (off)))
#define FU32(p, off)  (*(u32*)((char*)(p) + (off)))
#define FF32(p, off)  (*(float*)((char*)(p) + (off)))
#define FPTR(p, off)  (*(void**)((char*)(p) + (off)))

struct Vec3 { float x, y, z; };

// Transform message sent to swarm effects (size 0x38).
struct XformMsg {
    u16   flags;      // +0x00  |2 = rotation, |4 = position
    u16   count;      // +0x02
    float pos[3];     // +0x04
    float scale;      // +0x10
    float rot[9];     // +0x14
    XformMsg();                           // 0x00434040
    void SetPosition(const float* v);     // 0x00571d40 (ecx = msg)
};

struct cSPTimer {
    u64  GetElapsedTime();                // 0x00bc3190
    void Restart();                       // 0x00bc3130
};

// Combatant sub-object (embedded in the building at +0x120, also reached by QI).
struct cCombatant {
    int   GetDamageState();               // 0x008e7f80
    float GetHealthFraction();            // 0x00bfc490
    bool  IsAlive();                      // 0x00bfc600 (name guess)
};

// The simulation object behind the view (this->mpObject).  Effect helpers.
struct cSpatialObject {
    bool  GetEffect(int id);                          // 0x00c88910
    void* FindEffect(int id);                         // 0x00c888e0
    void  SetEffectParam(int id, float f);            // 0x00c88a00
    void  SetEffectPos(int id, void* p);              // 0x00c88a30
    void  KillEffect(int id, int flag);               // 0x00c8ad30
    void  CreateEffect(int effId, int p3, int id);    // 0x00c8b130
    void  sub_b1a0(int id);                           // 0x00c8b1a0
    void  sub_b210(int id);                           // 0x00c8b210
    bool  sub_b220(int id1, int id2, int arg, int z); // 0x00c8b220
    void  sub_a020(int id, float f);                  // 0x00c8a020
};

// Chain objects returned by the global holders (names unknown).
struct cTribeHolderObj {
    char  pad[0x80];
    struct cOwnerLink* mpLink;                        // +0x80
};
struct cOwnerLink {
    char  pad[0x40];
    void* mpOwner;                                    // +0x40
    bool  Check9660();                                // 0x00d09660
    int   Check9670();                                // 0x00d09670
};
struct cHolder {
    cTribeHolderObj* Get74f0();                       // 0x00cf74f0 (ecx = holder)
};
struct cSpaceGame { char pad[0x20]; cOwnerLink* mpLink; };

struct cGameNounManager;
struct cGameDataVec { int pad0; void** mpBegin; void** mpEnd; };
struct cGameNounManager {
    cGameDataVec* GetGameDataVector(int a, int b, int c, int d, int e);  // 0x00b21340
    void*         sub_b25f40(void* id);                                  // 0x00b25f40
    void*         sub_b25f40b(void* id);
};
struct cNounInfo { void* mpOwner; int pad[3]; int mKind; };           // [0], [0x10]

struct cCity {
    void* GetCivilization();                          // 0x00bd9bf0
    bool  sub_bd8f30();                               // 0x00bd8f30
    bool  sub_bd7df0();                               // 0x00bd7df0
    bool  sub_bd7d60();                               // 0x00bd7d60
};
struct cBuilding {                                    // the QI(0x0E9CB8BA) object
    int   sub_bd1080();                               // 0x00bd1080
};
struct cCamera { void GetRight(Vec3* out); };
struct cCombatantQI { bool sub_c3f540(); };      // 0x00c3f540 (ecx = QI(0xE9CB8BA) obj)         // 0x00b13900 (ret 4)
struct cEntity { void* sub_ca71d0x; };
struct cEntityPtr { cNounInfo* GetInfo(); };          // 0x00ca71d0
struct cNounRef { bool sub_ac8d60(); };               // 0x00ac8d60
struct cEffMgr {};

int            GetCurrentGameMode();                  // 0x00b5b800
cHolder*       GetHolder();                           // 0x00cf74c0
cSpaceGame*    SpaceGameGet();                        // 0x01002bd0
void*          EffectsManager();                      // 0x0067ddd0
void**         AsPPTypeParam(void** ref);             // 0x00a16f40 (ecx = ref)
cGameNounManager* NounManager();                      // 0x00b3d300
cCamera*       GetCamera();                           // 0x00b3d280
cNounRef*      sub_b3d480(void* p);                   // 0x00b3d480 (cdecl)
void*          sub_b3d240();                          // 0x00b3d240
Vec3*          normalized_safe(Vec3* out, const Vec3* in);   // 0x00449c20
Vec3*          Swarm_Normalize(Vec3* out, const Vec3* in);   // 0x006e6df0
float*         Matrix3FromQuaternion(float* out, void* q);   // 0x0059c190
float*         sub_4a9b40(float* out, void* q);              // 0x004a9b40
void           SetKeyKind(void* key, int kind, int z);       // 0x0068c6d0
u32            FNV1_String8(const char* s, u32 seed, int n); // 0x00932e80

namespace SP {

void UpdateCloudTendril(class cBuildingView* v);      // 0x00e87600 (cdecl)

class cSpatialObjectViewBase {
public:
    void HandleSimulationUpdate(int a, int b);        // 0x00e92ca0
    char pad0[0xc];                                   // vtable, ...
    cSpatialObject* mpObject;                         // +0x0c
    char pad1[0x34 - 0x10];
    void* mEffect;                                    // +0x34 (swarm effect ref)
    char pad2[0x40 - 0x38];
};

class cBuildingView : public cSpatialObjectViewBase {
public:
    char  pad3[0x48 - 0x40];
    float mDesiredScale;                              // +0x48
    float mCurrentScale;                              // +0x4c
    float mZoomOutScale;                              // +0x50
    int   mDamageEffectXformIndex0;                   // +0x54
    u8    mDamageFlagsSet;                            // +0x58
    char  pad4[0x60 - 0x59];
    cSPTimer mTimer;                                  // +0x60

    void HandleSimulationUpdate(int a, int b);
    void UpdateSpaceCaptureEffects();                 // 0x00e89060
    void sub_e893a0();                                // 0x00e893a0
    void sub_e87cf0(int id);                          // 0x00e87cf0
    void SpawnAndPlaceDamageEffects(void* c, int a, int b);  // 0x00e89530
};

}  // namespace SP

// ---- shared chain helpers (inlined repeatedly in the original) --------------------------
static cOwnerLink* TribeLink()
{
    if (!GetHolder()) return 0;
    cTribeHolderObj* o = GetHolder()->Get74f0();
    if (!o) return 0;
    cTribeHolderObj* o2 = GetHolder()->Get74f0();
    return o2->mpLink;
}

static cOwnerLink* SpaceLink()
{
    if (GetCurrentGameMode() != 0x1654c05) return 0;
    if (!SpaceGameGet()) return 0;
    if (!SpaceGameGet()->mpLink) return 0;
    return SpaceGameGet()->mpLink;
}

// Tribe-chain: returns true when the owner link matches `city` (the bool flags select
// which of the optional checks run).  Both chains fall back to the space-game link.
static bool LinkMatches(void* city, bool needNo9670)
{
    cOwnerLink* x = TribeLink();
    if (x && x->Check9660() && (!needNo9670 || !x->Check9670()) && x->mpOwner == city)
        return true;
    cOwnerLink* y = SpaceLink();
    if (y && y->Check9660() && (!needNo9670 || !y->Check9670()) && y->mpOwner == city)
        return true;
    return false;
}

// Effect placement shared by the two "static cling" branches.
static void BuildClingMsg(XformMsg* msg, char* H, void* viewEffectObj)
{
    (void)msg; (void)H; (void)viewEffectObj;
}

// @ 0x00E8A510
void SP::cBuildingView::HandleSimulationUpdate(int a, int b)
{
    char* R;          // object returned by this->vtbl[0x2c] (rendering-state block)
    char* C;          // QI(0x0E9CB8BA) result on mpObject
    char* H;          // C->vtbl[0x84]() (owning city)
    bool  zFlag;      // [esp+0x1a]
    bool  isSpace;    // [esp+0x1b]
    bool  hasG;       // first tribe chain (bl at 0xa828)

    cSpatialObjectViewBase::HandleSimulationUpdate(a, b);
    R = (char*)VC0(void*, this, 0x2c);
    if (!R) return;

    if (!mDamageFlagsSet && ((FU32(R, 4) >> 0xe) & 1) && !((FU32(R, 4) >> 0x12) & 1)) {
        void* part = *(void**)R;
        int n = VC1(int, part, 0x64, void*, R);
        for (int i = 0; i < n; ++i)
            VC5(void, part, 0x70, void*, R, int, 0xa502dc0b, int, 0, float, 0.0f, int, i);
        mDamageFlagsSet = 1;
    }

    if (mpObject)
        C = (char*)VC1(void*, mpObject, 0xb8, int, 0xe9cb8ba);
    else
        C = 0;

    if (GetCurrentGameMode() == 0x1654c05) {
        UpdateSpaceCaptureEffects();
        sub_e893a0();
    }

    zFlag = false;
    if (mpObject) {
        cCombatant* cb = (cCombatant*)VC1(void*, mpObject, 0xb8, void*, (void*)0x13f94d4);
        if (cb) {
            int ds = cb->GetDamageState();
            if (ds == 0) {
                if (mEffect) {
                    VC1(void, mEffect, 0xc, int, 0);
                    void* e = mEffect;
                    mEffect = 0;
                    if (e) VC0(void, e, 4);
                }
            } else if (ds == 2) {
                zFlag = true;
                u32* pp = (u32*)VC0(void*, mpObject, 0x98);
                u32 key[3];
                key[0] = pp[0]; key[1] = pp[1]; key[2] = pp[2];
                FU32(R, 0x4c) = 0x3ecccccd;
                FU32(R, 0x50) = 0x3ecccccd;
                FU32(R, 0x54) = 0x3ecccccd;
                bool sticky = ((cCombatantQI*)C)->sub_c3f540();
                if (!sticky && mEffect == 0 && key[0] != 0 && (key[2] & 0xff00) != 0x7e00) {
                    void* em = EffectsManager();
                    VC3(void, em, 0x2c, int, 0xee9148d8, int, 0, void**, AsPPTypeParam(&mEffect));
                    if (mEffect) {
                        u32 buf[2];
                        buf[0] = key[0];
                        buf[1] = key[2];
                        VC3(void, mEffect, 0x48, int, 6, void*, buf, int, 2);
                        XformMsg msg;
                        msg.SetPosition((const float*)VC0(void*, mpObject, 0x2c));
                        msg.scale = VC0(float, mpObject, 0x34);
                        msg.count++;
                        float tmp[9];
                        float* m = Matrix3FromQuaternion(tmp, VC0(void*, mpObject, 0x30));
                        for (int i = 0; i < 9; ++i) msg.rot[i] = m[i];
                        msg.flags |= 2;
                        msg.count++;
                        VC1(void, mEffect, 0x18, void*, &msg);
                        VC1(void, mEffect, 8, int, 0);
                    }
                    SetKeyKind(key, 0x7e, 0);
                    VC1(void, mpObject, 0x94, void*, key);
                }
            }
        }
    }

    if (!VC0(u8, this, 0x1c)) return;

    isSpace = (GetCurrentGameMode() == 0x1654c05);

    {
        cOwnerLink* l = TribeLink();
        hasG = (l != 0) && l->Check9660();
    }

    if (GetCurrentGameMode() != 0x1654c10) {
        if (FU8(mpObject, 0x6e)) {
            FU32(R, 4) |= 8;
            FU8(R, 0x5c) = 1;
        } else if (VC0(u8, mpObject, 0x24)
                   && (!isSpace || VC0(u8, C + 0x34, 0x58))
                   && (!hasG || VC0(u8, C + 0x1e8, 0x10))) {
            FU32(R, 4) |= 8;
            FU8(R, 0x5c) = 2;
        } else {
            FU32(R, 4) &= 0xfffffff7;
        }
    }

    float health = ((cCombatant*)(C + 0x120))->GetHealthFraction();
    bool bl = false, fxB = false, fxC = false, fxD = false;
    if (zFlag || health >= 0.8f) {
        bl = true; fxD = true;
    } else if (health < 0.5f) {
        if (health >= 0.0f) { bl = true; fxC = true; }
    } else {
        fxB = true; fxD = true;
    }

    if ((FI32(C, 0x30c) - FI32(C, 0x308)) / 0x38 == 0) {
        if (bl) {
            mpObject->KillEffect(0x49b925c, 0);
            sub_e87cf0(0x4cad362);
        }
        if (fxD) {
            mpObject->KillEffect(0x49b925d, 0);
            sub_e87cf0(0x4cad3a8);
        }
        if (fxB && !mpObject->GetEffect(0x49b925c))
            mpObject->CreateEffect(0x65c15577, 0, 0x49b925c);
        if (fxC && !mpObject->GetEffect(0x49b925d))
            mpObject->CreateEffect(0x97c0b9bf, 0, 0x49b925d);
    } else {
        if (FU8(C, 0x2f0)) {
            fxD = true;
            bl = true;
            FU8(C, 0x2f0) = 0;
        }
        if (bl) sub_e87cf0(0x4cad362);
        if (fxD) sub_e87cf0(0x4cad3a8);
        if (bl && fxD) {
            FU32(this, 0x48) = 0xffffffff;
            FU32(this, 0x4c) = 0xffffffff;
            FU32(this, 0x50) = 0xffffffff;
            mDamageEffectXformIndex0 = -1;
        }
        if (fxB) SpawnAndPlaceDamageEffects(C, 0x4cad362, 0x4cb1631);
        if (fxC) SpawnAndPlaceDamageEffects(C, 0x4cad3a8, 0x4cb1632);
    }

    H = (char*)VC0(void*, C, 0x84);
    bool r1 = false, r2 = false;
    if (GetCurrentGameMode() != 0x1654c10) {
        r1 = LinkMatches(H, true);
        // second chain has no Check9670 requirement
        r2 = LinkMatches(H, false);
    }

    if (VC1(int, C, 0xc, int, 0x1007ae63) != 0) {
        int d = FI32(C, 0x298) - FI32(C, 0x29c);
        if (d > 0)
            mpObject->sub_b220(0x20186eab, 0xf40652ad, r1, 0);
        else if (d < 0)
            mpObject->sub_b220(0x6794fedd, 0xf40652ae, r1, 0);
    } else {
        bool v1 = r1 && FU8(C, 0x289) && VC1(int, C, 0xc, int, 0x1a55e4d) != 0;
        mpObject->sub_b220(0x20186eab, 0xf40652ad, v1, 0);
        bool v2 = r1 && FU8(C, 0x289) && VC1(int, C, 0xc, int, 0xecade42) != 0;
        mpObject->sub_b220(0x6794fedd, 0xf40652ae, v2, 0);
    }

    cCombatant* cmb = (cCombatant*)(C + 0x120);
    if (VC1(int, C, 0xc, int, 0x1a55e4d) != 0) {
        bool v1 = r1 && !FU8(C, 0x289) && cmb->GetDamageState() != 2 && !FU8(C, 0xa6);
        mpObject->sub_b220(0x70f577f7, 0x13b59ba2, v1, 0);
        bool v2 = !r2 && !FU8(C, 0x289) && cmb->GetDamageState() != 2;
        if (mpObject->sub_b220(0xd84031d7, 0x13bdd20b, v2, 0))
            mpObject->SetEffectParam(0x13bdd20b, 512.0f);
    } else if (VC1(int, C, 0xc, int, 0xecade42) != 0) {
        bool v1 = r1 && !FU8(C, 0x289) && cmb->GetDamageState() != 2 && !FU8(C, 0xa6);
        mpObject->sub_b220(0xa65b1464, 0x13b59ba2, v1, 0);
        bool v2 = !r2 && !FU8(C, 0x289) && cmb->GetDamageState() != 2;
        if (mpObject->sub_b220(0x706665c4, 0x13bdd20b, v2, 0))
            mpObject->SetEffectParam(0x13bdd20b, 512.0f);
    } else if (VC1(int, C, 0xc, int, 0xff10521) != 0) {
        bool v1 = r1 && !FU8(C, 0x289) && cmb->GetDamageState() != 2 && !FU8(C, 0xa6);
        mpObject->sub_b220(0xa8b22b41, 0x13b59ba2, v1, 0);
        bool v2 = !r2 && !FU8(C, 0x289) && cmb->GetDamageState() != 2;
        if (mpObject->sub_b220(0xec727821, 0x13bdd20b, v2, 0))
            mpObject->SetEffectParam(0x13bdd20b, 512.0f);
    }

    if (VC1(int, C, 0xc, int, 0x1a55e4d) != 0) {
        cCity* city = (cCity*)H;
        if (!zFlag && !VC0(u8, C, 0x2c) && FU8(C, 0x289) && !VC0(u8, city, 0x2c)
            && city->sub_bd8f30())
            zFlag = true;
        else
            zFlag = false;
        void* sh = mpObject->FindEffect(0x4acb33b);
        if (zFlag) {
            bool go = true;
            if (!sh) {
                void* civ = city->GetCivilization();
                if (!civ) {
                    go = false;
                } else {
                    float v[3];
                    v[0] = FF32(civ, 0xc4); v[1] = FF32(civ, 0xc8); v[2] = FF32(civ, 0xcc);
                    mpObject->CreateEffect(0xf020ce6, 0, 0x4acb33b);
                    sh = mpObject->FindEffect(0x4acb33b);
                    if (!sh) go = false;
                    else VC3(void, sh, 0x44, int, 5, void*, v, int, 3);
                }
            }
            if (go) {
                u32 fl = FU32(C, 0x84);
                if (!(fl & 0x10) || (fl & 0x20)) {
                    XformMsg msg;
                    float tv[3];
                    float* bb = (float*)VC1(void*, C + 0x34, 0x6c, void*, tv);
                    msg.flags |= 4;
                    msg.count++;
                    float cx = (bb[0] + bb[3]) * 0.5f;
                    float cy = (bb[1] + bb[4]) * 0.5f;
                    float cz = (bb[2] + bb[5]) * 0.5f;
                    msg.pos[0] = cx; msg.pos[1] = cy; msg.pos[2] = cz;
                    float tmp[9];
                    float* m = sub_4a9b40(tmp, VC0(void*, C + 0x34, 0x30));
                    for (int i = 0; i < 9; ++i) msg.rot[i] = m[i];
                    msg.flags |= 2;
                    msg.count++;
                    VC1(void, sh, 0x18, void*, &msg);
                }
            }
        } else if (sh) {
            mpObject->KillEffect(0x4acb33b, 1);
        }
    }

    {
        bool arg = (FI32(C, 0x290) > 0) || ((cCombatant*)(C + 0x120))->IsAlive();
        if (mpObject->sub_b220(0x39ff8e9e, 0x4acb33c, arg, 0)) {
            cGameNounManager* nm = NounManager();
            cGameDataVec* vec = nm->GetGameDataVector(0xcd7d10, 0xd3d420, 0xae72d0, 0xb1e500, 0x18c6de8);
            int count = (int)(vec->mpEnd - vec->mpBegin);
            for (int i = 0; i < count; ++i) {
                void* p = vec->mpBegin[i];
                cNounInfo* info = ((cEntityPtr*)p)->GetInfo();
                if (info->mKind == 1 && info->mpOwner == (void*)C) {
                    void* id = VC0(void*, p, 0x4c);
                    char* r = (char*)NounManager()->sub_b25f40(id);
                    if (r) {
                        mpObject->SetEffectPos(0x4acb33c, r + 0xc4);
                        break;
                    }
                }
            }
        }
    }

    UpdateCloudTendril(this);

    if (!isSpace) {
        while (((cBuilding*)C)->sub_bd1080()) {}
        if (VC0(int, C, 0x20) == 0x18ea1eb && GetCurrentGameMode() != 0x1654c10) {
            bool facing = false;
            if (GetCamera()) {
                Vec3 camv;
                GetCamera()->GetRight(&camv);
                Vec3 t;
                Vec3* n = normalized_safe(&t, (const Vec3*)VC0(void*, C + 0x34, 0x2c));
                facing = ((n->y * camv.y + n->z * camv.z) + n->x * camv.x) > 0.0f;
            }
            cCity* city = (cCity*)H;
            mpObject->sub_b220(0x3e28b6b5, 0x2ca2a9a, city->sub_bd7df0() && !facing, 0);
            mpObject->sub_b220(0xa6e7c82f, 0x2ca38bb, city->sub_bd7d60() && !facing, 0);
        }
    }

    {
        bool arg = (FU32(C, 0x84) & 0x800) == 0x800;
        if (mpObject->sub_b220(0x56192017, 0x30e8811, arg, 0)) {
            mpObject->SetEffectParam(0x30e8811, 512.0f);
            float f = VC0(float, C + 0x34, 0x74);
            mpObject->sub_a020(0x30e8811, f);
        }
    }
    FU32(C, 0x84) &= 0xfffff7ff;
    char* sub34 = C + 0x34;

    if (isSpace && VC1(int, C, 0xc, int, 0x1007ae63) != 0) {
        bool done = false;
        void* eff = 0;
        if (FU8(H, 0x2fc)) {
            if (mpObject->GetEffect(0x47601624)) done = true;
            else {
                mpObject->sub_b1a0(0x47601624);
                mpObject->SetEffectParam(0x47601624, 1000.0f);
                eff = mpObject->FindEffect(0x47601624);
                if (!eff) done = true;
            }
        } else {
            if (!mpObject->GetEffect(0x47601624)) done = true;
            else {
                mpObject->KillEffect(0x47601624, 1);
                mpObject->sub_b210(0x3f056974);
                mpObject->SetEffectParam(0x3f056974, 1000.0f);
                eff = mpObject->FindEffect(0x3f056974);
                if (!eff) done = true;
            }
        }
        if (!done) {
            XformMsg msg;
            const float* pc = (const float*)VC0(void*, sub34, 0x2c);
            char* hs = H + 0x120;
            const float* p2 = (const float*)VC0(void*, hs, 0x2c);
            Vec3 d;
            d.x = p2[0] - pc[0];
            d.y = p2[1] - pc[1];
            d.z = p2[2] - pc[2];
            float r = FF32(H, 0x300);
            Vec3 tmpn;
            Vec3* nn = Swarm_Normalize(&tmpn, (const Vec3*)VC0(void*, hs, 0x2c));
            float x = r * nn->x + d.x;
            float y = nn->y * r + d.y;
            float z = nn->z * r + d.z;
            msg.pos[0] = x; msg.pos[1] = y; msg.pos[2] = z;
            msg.flags |= 4;
            msg.count++;
            VC1(void, eff, 0x14, void*, &msg);
        }
    }

    {
        u32 h = FNV1_String8("SG_ufo_static_cling_stunned_building", 0x811c9dc5, 1);
        bool arg = ((cCombatant*)(C + 0x120))->IsAlive();
        mpObject->sub_b220(h, 0x5f8d750, arg, 0);
    }

    if (VC0(int, C, 0x20) == 0x18ea2cc) {
        void* owner = VC0(void*, C, 0x84);
        if (sub_b3d480(owner)->sub_ac8d60()) {
            int v = FI32(C, 0x294);
            int cap = 0x4b0;
            int* sel = (v > 0x4b0) ? &cap : &v;
            u64 elapsed = mTimer.GetElapsedTime();
            long long thresh = (long long)(((0x4b1 - *sel) * 4000) / 0x4b0 + 2000);
            if (elapsed > (u64)thresh) {
                const float* p = (const float*)VC0(void*, sub34, 0x2c);
                Vec3 v1;
                v1.x = p[0]; v1.y = p[1]; v1.z = p[2];
                const float* q = (const float*)VC0(void*, sub34, 0x68);
                float len = q[5] - q[2];
                Vec3 t;
                Vec3* n = normalized_safe(&t, &v1);
                Vec3 pos;
                pos.x = len * n->x + v1.x;
                pos.y = n->y * len + v1.y;
                pos.z = n->z * len + v1.z;
                void* mgr = sub_b3d240();
                Vec3 out;
                void* r5c = VC1(void*, sub34, 0x5c, void*, &out);
                VC3(void, mgr, 0x60, int, 0x6257fd5 + (isSpace ? 1 : 0), void*, &pos, void*, r5c);
                mTimer.Restart();
            }
        }
    }
}
