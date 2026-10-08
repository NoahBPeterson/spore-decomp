// @ 0x00f1d5d0  scenario-play interaction handler: switch over cmd->mType (1..11); each case
// looks up the target object(s), scores/reputation-boosts through AddScore (0xf19270) and
// reports through three out pointers (handled flag, and the two objects' cast pointers).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).

#include "types.h"

typedef unsigned int uint;

struct StatObj                                                  // sub-object at +0x5a8/+0x508/+0x120
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void SetValue(float v);                            // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual float GetValue(int empire, int mode, const void* key, StatObj* avatarStat);   // +0x58
};

struct Entity
{
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual uint Cast(uint iid);                               // +0x0c
    uint32_t pad1[8];
    int  mID;                                                  // +0x24
    uint32_t pad2[4];
    int  mKind;                                                // +0x38
};

struct Info { uint32_t pad[0x14]; uint mFlags; };              // +0x50 & 0x100

struct Creature : Entity
{
    uint32_t pad3[(0x5a8 - 0x3c) / 4];
    StatObj  stat;                                             // +0x5a8
    uint32_t pad4[(0xb58 - 0x5a8 - 4) / 4];
    uint     mFlags;                                           // +0xb58
    bool M_c15d50(Info* i, int a, int b);                      // 0xc15d50 (ret 0xc)
    bool M_c159c0(Info* i, int a, int b);                      // 0xc159c0 (ret 0xc)
};
struct Other : Entity                                          // FUN_00ae6760 result
{
    uint32_t pad3[(0x508 - 0x3c) / 4];
    StatObj  stat;                                             // +0x508
    bool M_ca4320(Entity* e);                                  // 0xca4320 (ret 4)
};
struct Building : Entity                                       // icast<cBuilding>
{
    uint32_t pad3[(0x120 - 0x3c) / 4];
    StatObj  stat;                                             // +0x120
    bool M_bcf490(Entity* e);                                  // 0xbcf490 (ret 4)
};
struct Holder { uint32_t pad[0x108 / 4]; Creature* mOwner; };  // FUN_00ad7380 result, +0x108

struct Iter8 { uint a, b; };
struct Map
{
    void Insert(Iter8* out, uint* key);                        // 0x00a18440 (ret 8)
};

struct Cmd
{
    uint32_t pad[2];
    Map  mMap;                                                 // +0x08
    uint32_t pad2[(0x24 - 0x08 - 4) / 4];
    int  mType;                                                // +0x24
    int  mTarget;                                              // +0x28
    int  mTarget2;                                             // +0x2c
};

struct NounMgr
{
    Creature* GetAvatar();                                     // 0x00b1fdb0
    int GetPlayerEmpireOrMinus1();                             // 0x00b1f9d0
};
NounMgr* NounManager();                                        // 0xb3d300

struct PosseSim
{
    int GetItemCount();                                        // 0x00d52df0
    bool AddPosseMember(Creature* c);                          // 0x00d54330
};
PosseSim* PosseInstance();                                     // 0xd539d0
struct Limit
{
    int GetMax();                                              // 0x00f3bf60
};
struct Root { uint32_t pad[0x74 / 4]; Limit* mLimit; };
extern Root* g_root;                                           // [0x16c7aa4]

extern const uint g_statKey;                                   // 0x016c826c
extern float g_015ad93c;
extern float g_015ad944;

Info*      GetInfo(Entity* e);                                 // 0xb18e00 (cdecl)
Entity*    FUN_00bd8460(Entity* e);                            // cdecl
Entity*    FUN_00f20d20(Entity* e);                            // cdecl
Creature*  icast_Animal(Entity* e);                            // 0xac8960 (cdecl)
Other*     FUN_00ae6760(Entity* e);                            // cdecl
Building*  icast_Building(Entity* e);                          // 0xb67720 (cdecl)
void       AddScore(Entity* a, Entity* b, float f);            // 0xf19270 (cdecl)
void       FUN_00f195a0(Entity* e, Info* i);                   // cdecl
Holder*    FUN_00ad7380(Entity* e);                            // cdecl
Creature*  FUN_00f19200(Entity* avatar);                       // 0xf19200 (cdecl, casts by IID 0xce9f6639)

struct Mgr
{
    uint32_t pad[0xec / 4];
    bool     mFlag;                                            // +0xec
    Entity* Lookup(Cmd* c, int id, Entity* ctx);               // 0xf1b820 (ret 0xc)
    float   Calc(bool b, Info* i);                             // 0xf1aa10 (ret 8)
    void    FUN_f1a120(Cmd* c, Entity* e);                     // 0xf1a120 (ret 8)
    bool    Handle(Cmd* cmd, bool* pHandled, uint* pA, uint* pB);   // 0xf1d5d0
};

static __forceinline void ApplyStat(StatObj* s, int mode, StatObj* avStat)
{
    s->SetValue(s->GetValue(NounManager()->GetPlayerEmpireOrMinus1(), mode, &g_statKey, avStat));
}

static __forceinline StatObj* AvatarStat()
{
    Creature* av = NounManager()->GetAvatar();
    return av ? &av->stat : 0;
}

bool Mgr::Handle(Cmd* cmd, bool* pHandled, uint* pA, uint* pB)
{
    *pHandled = true;
    *pA = 0;
    *pB = 0;
    Limit* lim = g_root->mLimit;
    bool ok = false;
    Entity* obj;
    Entity* other = 0;

    switch (cmd->mType - 1)
    {
    case 0:
    case 6:
    {
        obj = Lookup(cmd, cmd->mTarget, 0);
        if (!obj) return false;
        bool isSeven = cmd->mType == 7;
        AddScore(NounManager()->GetAvatar(), obj, Calc(isSeven, GetInfo(obj)));
        if (isSeven)
            FUN_00f195a0(obj, GetInfo(obj));
        uint key = obj->mID;
        Iter8 it;
        cmd->mMap.Insert(&it, &key);
        ok = true;
        break;
    }
    case 1:
    {
        obj = Lookup(cmd, cmd->mTarget, 0);
        if (!obj) return false;
        AddScore(NounManager()->GetAvatar(), obj, g_015ad93c * 0.75f);
        if (mFlag)
        {
            ok = true;
            *pHandled = true;
        }
        else
        {
            FUN_f1a120(cmd, obj);
            ok = false;
            *pHandled = false;
        }
        break;
    }
    case 2:
    {
        obj = Lookup(cmd, cmd->mTarget, 0);
        if (!obj) return false;
        AddScore(NounManager()->GetAvatar(), obj, 4.0f);
        Entity* w = FUN_00bd8460(obj);
        if (w && w->mKind == 9)
            obj = FUN_00f20d20(w);
        Creature* animal = icast_Animal(obj);
        Other* oth = FUN_00ae6760(obj);
        Building* bld = icast_Building(obj);
        if (animal)
        {
            ApplyStat(&animal->stat, 2, AvatarStat());
            ok = true;
        }
        else if (oth)
        {
            ApplyStat(&oth->stat, 0, AvatarStat());
            ok = true;
        }
        else if (bld)
        {
            ApplyStat(&bld->stat, 0, AvatarStat());
            ok = true;
        }
        *pHandled = false;
        break;
    }
    case 3:
    {
        obj = Lookup(cmd, cmd->mTarget, 0);
        if (!obj) return false;
        AddScore(NounManager()->GetAvatar(), obj, 2.0f);
        Creature* animal = icast_Animal(obj);
        if (animal)
        {
            animal->mFlags |= 0x80;
            uint key = obj->mID;
            Iter8 it;
            cmd->mMap.Insert(&it, &key);
            ok = true;
            *pHandled = true;
        }
        break;
    }
    case 4:
    {
        int cur = PosseInstance()->GetItemCount();
        if (cur >= lim->GetMax())
        {
            *pHandled = false;
            return false;
        }
        obj = Lookup(cmd, cmd->mTarget, 0);
        if (!obj) return false;
        AddScore(NounManager()->GetAvatar(), obj, 2.0f);
        Creature* animal = icast_Animal(obj);
        if (animal)
        {
            ok = PosseInstance()->AddPosseMember(animal);
            *pHandled = false;
        }
        break;
    }
    case 5:
    {
        other = Lookup(cmd, cmd->mTarget2, 0);
        if (!other) return false;
        obj = Lookup(cmd, cmd->mTarget, other);
        if (!obj) goto tail2;
        Entity* a = obj;
        if (icast_Building(obj))
        {
            a = other;
            other = obj;
        }
        if (icast_Building(a))
        {
            *pHandled = false;
        }
        else
        {
            AddScore(NounManager()->GetAvatar(), other, 3.0f);
            AddScore(a, other, g_015ad944 * 0.75f);
            ok = true;
            *pHandled = true;
        }
        obj = a;
        break;
    }
    case 7:
    {
        obj = Lookup(cmd, cmd->mTarget, 0);
        if (!obj) return false;
        AddScore(NounManager()->GetAvatar(), obj, 1.0f);
        Creature* c = FUN_00f19200(NounManager()->GetAvatar());
        if (c)
        {
            Info* info = GetInfo(obj);
            if (info->mFlags & 0x100)
            {
                Holder* h = FUN_00ad7380(obj);
                if (h && h->mOwner)
                    h->mOwner->M_c15d50(info, 1, 0);
            }
            c->M_c159c0(info, 0, 1);
            ok = true;
        }
        break;
    }
    case 8:
    {
        other = Lookup(cmd, cmd->mTarget2, 0);
        if (!other) return false;
        obj = Lookup(cmd, cmd->mTarget, 0);
        if (!obj) goto tail2;
        AddScore(NounManager()->GetAvatar(), other, 3.0f);
        Creature* animal = icast_Animal(other);
        Other* oth = FUN_00ae6760(other);
        Building* bld = icast_Building(other);
        Info* info = GetInfo(obj);
        Creature* av = NounManager()->GetAvatar();
        if (bld)
        {
            av->M_c15d50(info, 1, 0);
            ok = bld->M_bcf490(obj);
            *pHandled = ok;
        }
        else if (oth)
        {
            av->M_c15d50(info, 1, 0);
            ok = oth->M_ca4320(obj);
            *pHandled = ok;
        }
        else if (animal)
        {
            av->M_c15d50(info, 1, 0);
            ok = animal->M_c159c0(info, 0, 1);
            *pHandled = ok;
        }
        else
        {
            *pHandled = false;
        }
        break;
    }
    case 9:
    case 10:
        *pHandled = false;
        return false;
    default:
        return false;
    }

    if (obj)
        *pA = obj->Cast(0x1186577);
tail2:
    if (other)
        *pB = other->Cast(0x1186577);
    return ok;
}
