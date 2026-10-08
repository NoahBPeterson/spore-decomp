// Slice s00ca6630 -- SP::cVehicle::Init (0x00ca6630, 1917 bytes; ret 0x14).
//
// Init(locomotion, purpose, ResourceKey model): resets the behavior-tree flags and combat timers,
// reads the vehicle-type property list (turn/cycle values), loads the model (the given key, or the
// first ObjectTemplateDB match for the locomotion/purpose pair), sets the purpose/stance flag bits,
// builds the default tool, attaches a hit sphere (non-0x1654c10 modes) and, in game mode 0x1654c10,
// loads ten tunables from a property list plus a second attached object.
// Retail layout per ModAPI cVehicle: 0xaf0 mpBehaviorTreeData, 0xb1c mLocomotion, 0xb20 mPurpose,
// 0xb24 mStance, 0xc7c mDefaultWeaponCycleTimeMS, 0xc88/0xca8 timers, 0xcfc mpHitSphere.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no EH frame in the original).
#include "types.h"

struct Vec3 {
    float x, y, z;
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };

struct RefObj {
    virtual void AddRef();     // +0
    virtual void Release();    // +4
};
struct Noun : RefObj {
    virtual void s2();
    virtual RefObj* Cast(uint32_t id);   // +0xc
};

struct Property {
    char pad[0x12];
    uint16_t type;                       // +0x12 (10 = uint, 13 = float)
    float*    GetFloat();                // 0x0041ea70
    uint32_t* GetUInt();                 // 0x0041ea00
};
struct PropertyList {
    virtual void AddRef();
    virtual void Release();              // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& prop);   // +0x24
};
struct PropertyMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, PropertyList** ppList);                     // +0x30
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppList);   // +0x2c
};

// EA::AutoRefCount<PropertyList> as used for a local: taking its address releases and clears it.
struct PropRef {
    PropertyList* p;
    PropRef() : p(0) {}
    ~PropRef() { if (p) p->Release(); }
    PropertyList** Out() {
        if (p) { PropertyList* t = p; p = 0; t->Release(); }
        return &p;
    }
};

// Functional-match constraint (see s005580e0): 0x24 bytes, child vector at +0x10.
void operator_delete_arr(void* p);                              // 0x00f47380 (cdecl)

namespace FM {
enum Sentinel { kEndConstraint = 0 };
enum EqualConstraint { kEquals = 0 };
struct Constraint {
    uint32_t mParameter, mType, mA, mB;
    Constraint* mpBegin;
    Constraint* mpEnd;
    Constraint* mpCapacity;
    const char* mpName;
    uint32_t mFlags;
    Constraint(Sentinel);                                       // 0x00558830
    Constraint(uint32_t param, EqualConstraint, int value);     // 0x00558960
    ~Constraint()                                               // out-of-line copy at 0x006066f0
    {
        for (Constraint* c = mpBegin; c < mpEnd; ++c)
            c->~Constraint();
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete_arr(mpBegin);
    }
};
}

struct KeyVec {                                                 // eastl::vector<ResourceKey>
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    KeyVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~KeyVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete_arr(mpBegin); }
};

struct TemplateDB {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void __cdecl Find(KeyVec* out, int one, FM::Constraint a, FM::Constraint b);   // +0x28
    virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21();
    virtual void Register(ResourceKey* key, int one);                                      // +0x58
};

struct NounMgr {
    Noun* CreateNoun(uint32_t id);                              // 0x00b20c60, ret 4
};

struct LocoTable {
    void Lookup(uint32_t loco, Vec3 zero, float* c, float* b, float* a);   // 0x00ceec10, ret 0x1c
};

struct Sub34 {                                                  // spatial sub-object at vehicle+0x34
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual Vec3* GetPosition();                                // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual bool IsPlayerOwned();                               // +0x58
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual float GetBoundingRadius();                          // +0x70
    virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36();
    virtual void LoadModel(ResourceKey* key);                   // +0x94
};

struct Vehicle;
struct HitSphere : RefObj {
    void SetPositionRadius(Vec3* pos, float radius);            // 0x00c3f160, ret 8
    void SetRange(float lo, float hi);                          // 0x00c3f1b0, ret 8
    void Attach(Vehicle* v);                                    // 0x00c3f2d0, ret 4
};

struct Timer {
    uint32_t pad[8];
    void Restart();                                             // 0x00bc3130
};

struct BtData { char pad[0x5fc]; uint32_t flags; };

struct Vehicle {
    char pad0[0x34];
    Sub34 sub34;                                                // +0x34
    char pad38[0x218 - 0x38];
    float f218;
    char pad21c[0x2a0 - 0x21c];
    float f2a0;
    char pad2a4[0xaf0 - 0x2a4];
    BtData* mpBehaviorTreeData;                                 // +0xaf0
    char padaf4[0xb1c - 0xaf4];
    uint32_t mLocomotion;                                       // +0xb1c
    uint32_t mPurpose;                                          // +0xb20
    uint32_t mStance;                                           // +0xb24
    char padb28[0xc7c - 0xb28];
    uint32_t mDefaultWeaponCycleTimeMS;                         // +0xc7c
    char padc80[0xc88 - 0xc80];
    Timer mCombatStatusTimer;                                   // +0xc88
    Timer mCombatVoxTimer;                                      // +0xca8
    char padcc8[0xcfc - 0xcc8];
    HitSphere* mpHitSphere;                                     // +0xcfc
    char padd00[0xd6c - 0xd00];
    uint32_t mTunable[8];                                       // +0xd6c .. +0xd88
    float mTunableF[2];                                         // +0xd8c, +0xd90
    RefObj* mpExtra;                                            // +0xd94

    void CreateDefaultTool();                                   // 0x00ca2ae0
    void SetupFlags();                                          // 0x00ca2e80

    __forceinline void SetStance(uint32_t stance)
    {
        mStance = stance;
        mpBehaviorTreeData->flags &= 0xfffffcff;
        if (mStance == 0)
            mpBehaviorTreeData->flags |= 0x100;
        else if (mStance == 1)
            mpBehaviorTreeData->flags |= 0x200;
    }

    void Init(uint32_t locomotion, uint32_t purpose, ResourceKey model);    // @ 0x00ca6630
};

extern unsigned     GetCurrentGameMode();                       // 0x00b5b800
extern NounMgr*     NounManager();                              // 0x00b3d300
extern PropertyMgr* GetPropertyManager();                       // 0x0067de30
extern TemplateDB*  ObjectTemplateDB();                         // 0x0067cb40
extern void         Attach_dc4b70(Vehicle* v);                  // 0x00dc4b70 (cdecl)
extern LocoTable    gLocoTable;                                 // 0x0169c9c8
extern uint32_t     gTemplateIDsByLoco[];                       // 0x01474a28 (mode 0x1654c05)
extern uint32_t     gTemplateIDs[];                             // 0x014749ec ([loco + 3 * purpose])
extern uint32_t     gTunablesGroup;                             // 0x0157c904

static __forceinline uint32_t FistpToUInt(float f)   // asm helper in the original: fld; fistp qword
{
    __int64 r;
    __asm { fld f
            fistp r }
    return (uint32_t)r;
}
static __forceinline void ReadUInt(PropRef& l, uint32_t id, uint32_t& out)
{
    Property* p;
    if (l.p && l.p->GetProperty(id, p) && p->type == 10)
        out = *p->GetUInt();
}
static __forceinline void ReadFloat(PropRef& l, uint32_t id, float& out)
{
    Property* p;
    if (l.p && l.p->GetProperty(id, p) && p->type == 13)
        out = *p->GetFloat();
}

// @ 0x00ca6630
void Vehicle::Init(uint32_t locomotion, uint32_t purpose, ResourceKey model)
{
    mPurpose = purpose;
    mLocomotion = locomotion;
    mpBehaviorTreeData->flags = 0;
    mCombatStatusTimer.Restart();
    mCombatVoxTimer.Restart();

    PropRef list;
    if (GetPropertyManager()->GetPropertyList(0xb6a5c63d, list.Out())) {
        float a, b, c;
        gLocoTable.Lookup(mLocomotion, Vec3(0.0f, 0.0f, 0.0f), &c, &b, &a);
        f218 = a;
        float cycle = 2.0f;
        if (list.p) {
            Property* p;
            if (list.p->GetProperty(0x3a36e7c, p) && p->type == 13)
                cycle = *p->GetFloat();
        }
        mDefaultWeaponCycleTimeMS = FistpToUInt(cycle * 1000.0f);
    }

    if (model.instanceID != 0xffffffff && model.instanceID != 0) {
        sub34.LoadModel(&model);
    } else {
        uint32_t loco = mLocomotion;
        uint32_t purp = mPurpose;
        uint32_t templateID;
        if (GetCurrentGameMode() == 0x1654c05)
            templateID = gTemplateIDsByLoco[loco];
        else
            templateID = gTemplateIDs[loco + purp * 3];
        KeyVec keys;
        TemplateDB* db = ObjectTemplateDB();
        db->Find(&keys, 1, FM::Constraint(0x2dc9d1e, FM::kEquals, templateID), FM::Constraint(FM::kEndConstraint));
        if (keys.mpBegin != keys.mpEnd) {
            model = *keys.mpBegin;
            sub34.LoadModel(&model);
            ObjectTemplateDB()->Register(&model, 1);
        }
    }

    if (mPurpose == 0)
        mpBehaviorTreeData->flags |= 1;
    else if (mPurpose == 1)
        mpBehaviorTreeData->flags |= 2;
    else if (mPurpose == 2)
        mpBehaviorTreeData->flags |= 4;
    else
        mpBehaviorTreeData->flags |= 8;

    CreateDefaultTool();
    f2a0 = 32.0f;
    SetStance(0);
    if (!sub34.IsPlayerOwned()) {
        mpBehaviorTreeData->flags |= 0x10;
        if (mPurpose == 2)
            SetStance(1);
    }
    SetupFlags();

    if (GetCurrentGameMode() != 0x1654c10) {
        NounMgr* nm = NounManager();
        Noun* n = nm->CreateNoun(0x2e72cae);
        HitSphere* hs = n ? (HitSphere*)n->Cast(0x2e71a5a) : 0;
        HitSphere* old = mpHitSphere;
        if (hs != old) {
            if (hs) hs->AddRef();
            mpHitSphere = hs;
            if (old) old->Release();
        }
        mpHitSphere->SetPositionRadius(sub34.GetPosition(), sub34.GetBoundingRadius());
        mpHitSphere->SetRange(0.0f, 3.402823466e+38f);
        mpHitSphere->Attach(this);
    }
    Attach_dc4b70(this);

    if (GetCurrentGameMode() == 0x1654c10) {
        PropRef tun;
        if (GetPropertyManager()->GetPropertyList(0xf14790c7, gTunablesGroup, tun.Out()) && tun.p) {
            ReadUInt(tun, 0xbf5cb754, mTunable[0]);
            ReadUInt(tun, 0x56a51680, mTunable[1]);
            ReadUInt(tun, 0x28dc8e73, mTunable[2]);
            ReadUInt(tun, 0xdc7e88d7, mTunable[3]);
            ReadUInt(tun, 0x302f343d, mTunable[4]);
            ReadUInt(tun, 0x54c2dd99, mTunable[5]);
            ReadUInt(tun, 0x3170db50, mTunable[6]);
            ReadUInt(tun, 0x4dfb4144, mTunable[7]);
            ReadFloat(tun, 0x5d43cab4, mTunableF[0]);
            ReadFloat(tun, 0x44aeb188, mTunableF[1]);
        }
        Noun* n = NounManager()->CreateNoun(0x21ffa3f);
        RefObj* extra = n ? n->Cast(0xb075dec5) : 0;
        RefObj* old = mpExtra;
        if (extra != old) {
            if (extra) extra->AddRef();
            mpExtra = extra;
            if (old) old->Release();
        }
    }
}
