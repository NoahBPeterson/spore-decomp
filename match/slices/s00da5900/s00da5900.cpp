// Slice s00da5900: 0x00da5900..0x00da67c0, the tribe social-band behaviour deciders and their
// helpers from SPGonzago (object file SPGameNounManager.obj).  Covers the cSocialBand object pool
// (slot-vector create / CreateObject / GetObject), SOCIAL_BAND_GROUP_Activate (binds a tribe
// performance through the agent-order manager), the TRIBE_REPAIR decider and its dispatcher, the
// observation/threat deciders that read behaviour stimuli back out of the agent-order blocks, and
// the small stimulus-mask helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the pool code has no EH frame)
#include "types.h"
#include <new>
#include <math.h>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned __int64   u64;

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Quat { float x, y, z, w; };

// ---------------------------------------------------------------------------
// engine free helpers (address in the comment)
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b3d510();                      // 0x00b3d510: returns a global
void* __cdecl FUN_00bc9b00();                      // 0x00bc9b00: returns the global agent-order manager
void* __cdecl FUN_00b3d300();                      // 0x00b3d300: returns the global noun manager
void* __cdecl FUN_00b5b800();                      // 0x00b5b800: GetCurrentGameMode
void* __cdecl FUN_01021080();                      // 0x01021080: GetUniverseContext
void* __cdecl FUN_00d994c0(void* block);           // 0x00d994c0
void* __cdecl FUN_00d999d0(void* block);           // 0x00d999d0: WatchMemoryBlock
void* __cdecl FUN_00d99a10(void* block);           // 0x00d99a10
void* __cdecl FUN_00d998f0(void* block);           // 0x00d998f0
void* __cdecl FUN_00d998d0(void* block, u32 key);  // 0x00d998d0
Vec3* __cdecl FUN_0059aed0(Vec3* out, void* v, void* q);                  // 0x0059aed0 RotateByQuat
void* __cdecl FUN_00b0fd00(void* out, void* v, void* dir, float f);       // 0x00b0fd00 RotateTowards
Quat* __cdecl FUN_0069b600(Quat* out, const Vec3* f, const Vec3* u);      // 0x0069b600 QuaternionFromFacingAndUp
void  __cdecl FUN_00da62d0(void* c, void* tribe, u32 lo, u32 hi);         // 0x00da62d0 (this slice)
void  __cdecl FUN_00da6270(void* c, int order);                           // 0x00da6270 (this slice)
u64   __cdecl FUN_00da6090(u32 index);            // 0x00da6090 (this slice)

// scratch globals addressed by the retail code (uninitialised in the image)
extern const float g_f169f394;                      // 0x0169f394
extern const float g_f169f398;                      // 0x0169f398
extern const float g_f169f39c;                      // 0x0169f39c
extern const float g_f169f3a0;                      // 0x0169f3a0
extern const float g_f169f3a4;                      // 0x0169f3a4
extern const float g_f169f3a8;                      // 0x0169f3a8
extern const float g_f169f3ac;                      // 0x0169f3ac

// shared real constants in the retail .rdata pool
extern const float _HK_REAL_ONE;                    // 0x01485720 = 1.0f

struct cTribe;
struct cSPCreatureCitizen;

// ---------------------------------------------------------------------------
// creature v-table partner objects (stub layouts; the retail classes are unnamed here)
// ---------------------------------------------------------------------------

// result of creature->slot30()->slot0c(hash)
struct HRes {
    virtual void h00(); virtual void h01(); virtual void h02(); virtual void h03();
    virtual void h04(); virtual void h05(); virtual void h06(); virtual void h07();
    virtual void h08(); virtual void h09(); virtual void h10();
    virtual Vec3* GetPos();                        // slot +0x2c
    virtual Vec3* GetDir();                        // slot +0x30
    char  mPad[0x38 - 4];                          // vfptr + pad
    float mf38;                                    // +0x38
};

// result of creature->slot30()
struct AppA {
    virtual void a00(); virtual void a01(); virtual void a02();
    virtual HRes* GetByHash(u32 hash);             // +0x0c
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10();
    virtual bool Available();                      // +0x2c (returns a char)
};

// embedded spatial sub-object at creature+0x34
struct Spat {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual Vec3* GetPos();                        // +0x2c
    virtual void s12();                            // +0x30
    virtual void s13();                            // +0x34
    virtual void SetFacing(Vec3* v);               // +0x38
    virtual void SetOrientation(Quat* q);          // +0x3c
};

// embedded spatial sub-object at creature+0xc0
struct SpatialPos {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10();
    virtual Vec3* GetPos();                        // +0x2c
};

// embedded combat sub-object at creature+0x5a8
struct CombatSub {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21();
    virtual float GetMaxHealth();                  // +0x58
};

// behaviour-stimuli block keyed by hash
struct Res58 {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
    virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
    virtual void r08(); virtual void r09(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15();
    virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
    virtual void r20(); virtual void r21();
    virtual cTribe* GetTribeField();               // +0x58
};

// object with a tribe pointer at +0x1f8 (0x00c9d9e0)
struct ResTribe {
    char    mPad00[0x1f8];
    cTribe* mpTribe;                               // +0x1f8
    cTribe* Get();                                 // 0x00c9d9e0
};

// block reader exposing a tribe pointer at +0xc
struct ResBlock {
    char    mPad00[0xc];
    cTribe* mpTribe;                               // +0xc
};

// object obtained from a behaviour block (FUN_00d998f0): slot 0x0c -> object with slot 0x20 -> id
struct ResId {
    virtual void i00(); virtual void i01(); virtual void i02(); virtual void i03();
    virtual void i04(); virtual void i05(); virtual void i06(); virtual void i07();
    virtual int GetId();                           // +0x20
};
struct ResNode {
    virtual void n00(); virtual void n01(); virtual void n02();
    virtual ResId* GetSub();                       // +0x0c
};

// object embedded at +0x20c of the 4f396a66 block; 0x00cee340 returns its value
struct ResTime {
    int GetValue();                                // 0x00cee340
};
struct Res4f {
    char    mPad00[0x20c];
    ResTime mTime;                                 // +0x20c
};

// ---------------------------------------------------------------------------
// behaviour tree
// ---------------------------------------------------------------------------
struct behavior_stimuli {
    int   mStimulusID;                             // +0x0
    void* mTarget;                                 // +0x4
    int   mValue;                                  // +0x8 (duration)
    char  mPad0c[0x18 - 0xc];
    int   mF18;                                    // +0x18

    void  ClearAll(u32 lo, u32 hi);                // 0x00bc98f0 (ret 8)
    void* Play(u32 lo, u32 hi);                    // 0x00bc96a0 (ret 8)
    void  PlayWith(u32 lo, u32 hi, float duration, void* target);   // 0x00bc97f0 (ret 0x10)
    void  GetAny();                                // 0x00d997e0
};

struct AgentNode;
struct behavior_stimuli;

struct cBehaviorTreeData {
    char             mPad00[8];
    behavior_stimuli mStimuli;                     // +0x08
    char             mPad[0x60c - 0x8 - sizeof(behavior_stimuli)];
    int*   FirstPending();                         // 0x00bca2c0
    void   PopFront();                             // 0x00bcaf40
    void   OrderOp(AgentNode* node, cSPCreatureCitizen* c, void* a, void* fn);  // 0x00bcb480
};

// ---------------------------------------------------------------------------
// creature
// ---------------------------------------------------------------------------
struct cSPCreatureCitizen {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual cSPCreatureCitizen* GetByHash(u32 hash);   // +0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual AppA* GetApp();                        // +0x30

    char               mPad04[0x34 - 4];
    Spat               mSpat;                      // +0x34
    char               mPad34[0xc0 - 0x34 - sizeof(Spat)];
    SpatialPos         mPos;                       // +0xc0
    char               mPadc0[0x5a8 - 0xc0 - sizeof(SpatialPos)];
    CombatSub          mCombat;                    // +0x5a8
    char               mPad5a8[0x5e0 - 0x5a8 - sizeof(CombatSub)];
    float              mF5e0;                      // +0x5e0
    char               mPad5e0[0xb4c - 0x5e0 - 4];
    cBehaviorTreeData* mpBTree;                    // +0xb4c
    char               mPadb4c[0xb5e - 0xb4c - 4];
    bool               mbDead;                     // +0xb5e

    cTribe* GetTribe();                            // 0x00c22f50
    bool    IsLeader();                            // 0x00c232d0
    void    ForceOrdersUpdate();                   // 0x00c26450
    cSPCreatureCitizen* GetTargetAsCreature();     // 0x00c0ee70
    void    SetInteractionTarget(float f);         // 0x00c0b970
};

// ---------------------------------------------------------------------------
// tribe / noun manager
// ---------------------------------------------------------------------------
struct cTribe {
    char  mPad00[0x2c8];
    float mF2c8;                                   // +0x2c8
    char  mPad2cc[0x556 - 0x2cc];
    u8    mF556;                                   // +0x556
    u32   GetAdultPopulation();                    // 0x00c8f370
};

struct cGameNounManager {
    cTribe* GetPlayerTribe();                      // 0x00bfc5f0 (reads +0x70)
};
cGameNounManager* NounManager();                   // returns FUN_00b3d300()

// ---------------------------------------------------------------------------
// cSocialBand pool (spstl::slot_vector<SP::cSocialBand> in cResizableObjectPoolT)
// ---------------------------------------------------------------------------
struct CommunityApproach;                          // == SP::cSocialBand

struct cSocialBand {
    cSocialBand();
    cSocialBand(const cSocialBand&);
    ~cSocialBand();
    void Start(void* a, void* b, void* c, void* d);   // 0x00da1330
    void Bind(void* a);                               // 0x00da1b00
    u32 mData[0x20c / 4];
};

struct cSocialBandEntry {
    u32         mFlags;                            // +0x0
    cSocialBand mItem;                             // +0x4
};

struct cSocialBandPool {
    u8*               mpBegin;                     // +0x0 (byte view of the entry array)
    u8*               mpEnd;                       // +0x4
    char              mPad08[0x14 - 0x8];
    u32               mMinFree;                    // +0x14
    u32               mFreeHead;                   // +0x18

    void DoInsertEntry();                          // 0x00da58a0
    u32  create(const cSocialBand& item);          // 0x00da5900
    u32  CreateObject();                           // 0x00da5a00
    cSocialBand* GetObject(u32 index);             // 0x00d9eb70
};
extern cSocialBandPool gSocialBandPool;            // 0x015935a8

// ---------------------------------------------------------------------------
// agent-order manager
// ---------------------------------------------------------------------------
struct AgentNode {
    char mPad000[0x1a8];
    u32  mBand;                                    // +0x1a8
    char mPad1ac[0x224 - 0x1ac];
    void* mFn224;                                  // +0x224
    void* mFn228;                                  // +0x228
};

struct NodeArgs {
    cTribe* a;
    cTribe* b;
    Vec3    pos;
};

struct cAgentOrderManager {
    AgentNode* FindNode(u32 id, void* fn, NodeArgs* args);              // 0x00bca620 (ret 0xc)
    AgentNode* CreateNode(u32 id, u32 size, void* fn, const char* name); // 0x00bcb0b0 (ret 0x10)
};

cAgentOrderManager* AgentOrderManager();           // returns FUN_00bc9b00()

// registered callback functions (addresses)
void __cdecl FUN_00da05f0();                       // 0x00da05f0
void __cdecl FUN_00d9f130();                       // 0x00d9f130 FindPrimaryAgentForSocialBandGroup
void __cdecl FUN_00d9f0a0();                       // 0x00d9f0a0 FindSocialBandGroup

// 0x00b71af0: object call-through reached from FUN_00da5c80
struct HelperB71 {
    void Run(void* p);                             // 0x00b71af0 (thiscall, ret 4)
};

// tribe-mode strategy
struct cTribeModeStrategy {
    char mPad00[0x94];
    cSPCreatureCitizen** mpBegin;                  // +0x94
    cSPCreatureCitizen** mpEnd;                    // +0x98
    static cTribeModeStrategy* Instance();         // 0x00cd40b0
};

// ---------------------------------------------------------------------------
// implementation
// ---------------------------------------------------------------------------

// @ 0x00da5900
u32 cSocialBandPool::create(const cSocialBand& item)
{
    u32 nIndex = mFreeHead;
    if (nIndex != 0x3fffffff) {
        mFreeHead = ((cSocialBandEntry*)(mpBegin + nIndex * 0x210))->mFlags & 0x3fffffff;
        ((cSocialBandEntry*)(mpBegin + nIndex * 0x210))->mFlags &= 0x7fffffff;
        cSocialBand* pItem = &((cSocialBandEntry*)(mpBegin + nIndex * 0x210))->mItem;
        if (pItem)
            ::new (pItem) cSocialBand(item);
    } else {
        const cSocialBand temp(item);
        nIndex = (u32)((mpEnd - mpBegin) / 0x210);
        DoInsertEntry();
        if (nIndex != 0)
            ((cSocialBandEntry*)(mpBegin + (nIndex - 1) * 0x210))->mFlags &= 0xbfffffff;
        ((cSocialBandEntry*)(mpBegin + nIndex * 0x210))->mFlags |= 0x40000000;
        ((cSocialBandEntry*)(mpBegin + nIndex * 0x210))->mFlags &= 0x7fffffff;
        cSocialBand* pItem = &((cSocialBandEntry*)(mpBegin + nIndex * 0x210))->mItem;
        if (pItem)
            ::new (pItem) cSocialBand(temp);
    }
    if (mMinFree > nIndex)
        mMinFree = nIndex;
    return nIndex;
}

// @ 0x00da5a00
u32 cSocialBandPool::CreateObject()
{
    cSocialBand local;
    u32 index = create(local);
    return index | 0x40000000;
}

// @ 0x00da5a40
bool __cdecl FUN_00da5a40(cSPCreatureCitizen* c)
{
    cSPCreatureCitizen* pcVar3;
    cSPCreatureCitizen* pcVar6;
    cTribe*             playerTribe;
    cTribe*             otherTribe;
    AgentNode*          node;

    if (c == 0) {
        pcVar3 = 0;
    } else {
        pcVar3 = c->GetByHash(0x4f176642);
        c->GetByHash(0xd0036e08);
    }

    void* block = c->mpBTree->mStimuli.Play(0x10000, 0);
    if (block == 0)
        return false;

    pcVar6 = (cSPCreatureCitizen*)FUN_00d994c0(FUN_00d999d0(block));
    if (pcVar6 == 0)
        return false;

    playerTribe = NounManager()->GetPlayerTribe();
    if (pcVar3 != 0)
        playerTribe = pcVar3->GetTribe();
    otherTribe = pcVar6->GetTribe();

    NodeArgs args;
    args.a = playerTribe;
    args.b = otherTribe;
    args.pos = *pcVar6->mPos.GetPos();

    node = AgentOrderManager()->FindNode(0xf445d1cc, (void*)&FUN_00d9f0a0, &args);
    if (node == 0) {
        if (pcVar3 == 0)
            return false;
        node = AgentOrderManager()->CreateNode(0xf445d1cc, 0x20, (void*)0x18eb4b7, "Social");
        node->mFn224 = (void*)&FUN_00da05f0;
        node->mFn228 = (void*)&FUN_00d9f130;
        u32 bandIndex = gSocialBandPool.CreateObject();
        node->mBand = bandIndex;
        gSocialBandPool.GetObject(bandIndex)->Start(playerTribe, otherTribe, pcVar6, pcVar3);
        c->mpBTree->mStimuli.PlayWith(0x200000, 0, 5.0f, c);
    }

    c->mpBTree->OrderOp(node, c, 0, (void*)&FUN_00d9f0a0);
    gSocialBandPool.GetObject(node->mBand)->Bind(c);
    c->SetInteractionTarget(0.0f);

    if (pcVar3 != 0 && pcVar3->IsLeader()) {
        cTribeModeStrategy* st = cTribeModeStrategy::Instance();
        for (cSPCreatureCitizen** it = st->mpBegin; it != st->mpEnd; ++it) {
            cSPCreatureCitizen* member = *it;
            member->mpBTree->mStimuli.PlayWith(0x100000, 0, 3.402823466e+38f, 0);
            member->mpBTree->mStimuli.PlayWith(0x10000, 0, 5.0f, pcVar6);
        }
    }
    return true;
}

// @ 0x00da5c80
bool __cdecl FUN_00da5c80(void* p)
{
    ((HelperB71*)FUN_00b3d510())->Run(p);
    return true;
}

// @ 0x00da5ca0
float __cdecl FUN_00da5ca0(cSPCreatureCitizen* c)
{
    AppA* app = c->GetApp();
    if (app != 0 && !app->Available()) {
        HRes* res = app->GetByHash(0x13f94d4);
        if (res != 0 && 1.5258789e-05f >= res->mf38)
            return 1.0f;
        return 0.0f;
    }
    return 1.0f;
}

// @ 0x00da5cf0
bool __cdecl FUN_00da5cf0(cSPCreatureCitizen* c, void* a, void* b, void* d, void* e, float* out)
{
    AppA* app = c->GetApp();
    if (app != 0)
        app->GetByHash(0x1186577);
    float k = 10.0f;
    out[0] = k;
    float x1 = g_f169f398;
    float x2 = g_f169f39c;
    float x3 = g_f169f3a0;
    out[1] = x1 * k;
    out[2] = x2 * k;
    out[3] = x3 * k;
    return true;
}

// @ 0x00da5d60
bool __cdecl FUN_00da5d60(cSPCreatureCitizen* c, void* a2, void* a3, void* a4, void* a5,
                          float* pOut, void* a7, float angle)
{
    AppA* app = c->GetApp();
    HRes* hres = 0;
    if (app != 0)
        hres = app->GetByHash(0x1186577);
    hres->GetPos();

    float ha = (g_f169f394 * angle) * 0.5f;
    float s  = (float)sin(ha);
    float cq = (float)cos(ha);

    Quat q;
    q.x = s * g_f169f3a4;
    q.y = s * g_f169f3a8;
    q.z = s * g_f169f3ac;
    q.w = cq;

    Vec3 v;
    FUN_0059aed0(&v, pOut + 1, &q);
    pOut[1] = v.x;
    pOut[2] = v.y;
    pOut[3] = v.z;

    Vec3  dir = *hres->GetDir();
    Vec3  r2;
    FUN_0059aed0(&r2, pOut + 1, hres->GetDir());

    Vec3  pos = *hres->GetPos();
    float px = r2.x + pos.x;
    float py = r2.y + pos.y;
    float pz = r2.z + pos.z;

    Vec3  here = *c->mSpat.GetPos();
    float dx = px - here.x;
    float dy = py - here.y;
    float dz = pz - here.z;
    float inv = 1.0f / (float)sqrt(dx * dx + dy * dy + dz * dz);
    dx *= inv;
    dy *= inv;
    dz *= inv;

    hres->GetPos();
    FUN_00b0fd00(&dir, &dir, &dir, 2.0f);

    if ((float)sqrt(dx * dx + dy * dy + dz * dz) > 1.5258789e-05f) {
        if ((float)sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z) > 1.5258789e-05f) {
            if (FUN_01021080() == 0) {
                Vec3 f = *hres->GetPos();
                float n = 1.0f / (float)sqrt(f.x * f.x + f.y * f.y + f.z * f.z);
                dir.x = f.x * n;
                dir.y = f.y * n;
                dir.z = f.z * n;
            }
            Quat out;
            FUN_0069b600(&out, &dir, &dir);
            c->mSpat.SetOrientation(&out);
        }
    }
    return true;
}

// @ 0x00da6090
u64 __cdecl FUN_00da6090(u32 index)
{
    switch (index) {
    case 0:  return 8;
    case 1:  return 0x10;
    case 2:  return 0x20;
    case 3:  return 0x40;
    case 4:  return 0x80;
    case 28: return 0x800000000000000;
    case 5:  return 0x100;
    case 6:  return 0x200;
    case 7:  return 0x400;
    case 8:  return 0x800;
    case 9:  return 0x2000;
    case 10: return 0x8000;
    case 11: return 0x20000;
    case 12: return 0x40000;
    case 13: return 0x80000;
    case 14: return 0x100000;
    case 15: return 0x200000;
    case 20: return 0x8000000;
    case 21: return 0x1000;
    case 22: return 0x10000000;
    case 24: return 0x1000000;
    case 25: return 0x10000000000000;
    case 26: return 0x10000;
    case 27: return 0x4000000;
    default: return 0;
    }
}

// @ 0x00da61e0
void __cdecl FUN_00da61e0(cSPCreatureCitizen* c, int order)
{
    int* p = c->mpBTree->FirstPending();
    if (p != 0 && *p == order) {
        c->mpBTree->PopFront();
        c->mpBTree->mStimuli.ClearAll(0x1d3fbffa, 0x8124080);
        return;
    }
    u64 v = FUN_00da6090((u32)order);
    c->mpBTree->mStimuli.ClearAll((u32)v, (u32)(v >> 32));
}

// @ 0x00da6240
bool __cdecl FUN_00da6240(cSPCreatureCitizen* c, u32 lo, u32 hi)
{
    c->mpBTree->mStimuli.ClearAll(lo, hi);
    c->ForceOrdersUpdate();
    return false;
}

// @ 0x00da6270
bool __cdecl FUN_00da6270(cSPCreatureCitizen* c, int order)
{
    int* p = c->mpBTree->FirstPending();
    if (p != 0 && *p == order) {
        c->mpBTree->PopFront();
        c->mpBTree->mStimuli.ClearAll(0x1d3fbffa, 0x8124080);
    } else {
        u64 v = FUN_00da6090((u32)order);
        c->mpBTree->mStimuli.ClearAll((u32)v, (u32)(v >> 32));
    }
    c->ForceOrdersUpdate();
    return false;
}

// @ 0x00da62d0
void __cdecl FUN_00da62d0(cSPCreatureCitizen* c, cTribe* tribe, u32 lo, u32 hi)
{
    void* block = c->mpBTree->mStimuli.Play(lo, hi);
    if (block == 0)
        return;

    cSPCreatureCitizen* other = (cSPCreatureCitizen*)FUN_00d994c0(FUN_00d999d0(block));
    void* r1 = FUN_00d998d0(block, 0x116d858);
    void* r2 = FUN_00d998d0(block, 0xee02c7);
    void* r3 = FUN_00d998d0(block, 0x4f396a66);

    if ((other != 0 && other->GetTribe() == tribe)
        || (r3 != 0 && (cTribe*)r3 == tribe)
        || (r2 != 0 && ((Res58*)r2)->GetTribeField() == tribe)
        || (r1 != 0 && ((ResTribe*)r1)->Get() == tribe))
    {
        c->mpBTree->mStimuli.ClearAll(lo, hi);
        int* p = c->mpBTree->FirstPending();
        if (p != 0 && FUN_00da6090((u32)*p) == (((u64)hi << 32) | lo)) {
            c->mpBTree->PopFront();
            c->mpBTree->mStimuli.ClearAll(0x1d3fbffa, 0x8124080);
        }
    }
}

// @ 0x00da63e0
void __cdecl FUN_00da63e0(cSPCreatureCitizen* c, cTribe* tribe)
{
    FUN_00da62d0(c, tribe, 0, 0x80);
    FUN_00da62d0(c, tribe, 0x400, 0);
    FUN_00da62d0(c, tribe, 0, 0x2000);
    FUN_00da62d0(c, tribe, 0, 0x20000);
    FUN_00da62d0(c, tribe, 0, 0x4000);
    FUN_00da62d0(c, tribe, 0x800, 0);
    FUN_00da62d0(c, tribe, 0x200000, 0);
    FUN_00da62d0(c, tribe, 0, 0x1000000);
}

// @ 0x00da6470
float __cdecl FUN_00da6470(cSPCreatureCitizen* c)
{
    return (c->mF5e0 <= 1.5258789e-05f) ? _HK_REAL_ONE : 0.0f;
}

// @ 0x00da64b0
float __cdecl FUN_00da64b0(cSPCreatureCitizen* c)
{
    if (c->mF5e0 <= 1.5258789e-05f && !c->mbDead) {
        cTribe* t = c->GetTribe();
        if (t != 0)
            return (t->GetAdultPopulation() < 2) ? _HK_REAL_ONE : 0.0f;
    }
    return 0.0f;
}

// @ 0x00da6510
float __cdecl FUN_00da6510(cSPCreatureCitizen* c)
{
    if (FUN_00b5b800() != (void*)0x1654c02)
        return 0.0f;
    cTribe* t = c->GetTribe();
    if (t == 0)
        return 0.0f;
    return (c->mF5e0 <= 1.5258789e-05f || t->mF2c8 > 0.0f) ? _HK_REAL_ONE : 0.0f;
}

// @ 0x00da6570
float __cdecl FUN_00da6570(cSPCreatureCitizen* c)
{
    void* block = c->mpBTree->mStimuli.Play(0x100000, 0);
    if (block != 0 && ((ResBlock*)block)->mpTribe == c->GetTribe())
        return 1.0f;
    return 0.0f;
}

// @ 0x00da65b0
float __cdecl FUN_00da65b0(cSPCreatureCitizen* c)
{
    void* block = c->mpBTree->mStimuli.Play(0x100000, 0);
    c->GetTargetAsCreature();
    if (block != 0 && ((ResBlock*)block)->mpTribe == c->GetTribe())
        return 1.0f;
    return 0.0f;
}

// @ 0x00da65f0
float __cdecl FUN_00da65f0(cSPCreatureCitizen* c)
{
    c->mpBTree->mStimuli.ClearAll(0x4000, 0);
    return 1.0f;
}

// @ 0x00da6610
float __cdecl FUN_00da6610(cSPCreatureCitizen* c)
{
    return (float)(u8)c->GetTribe()->mF556;
}

// @ 0x00da6630
float __cdecl FUN_00da6630(cSPCreatureCitizen* c, void* a, void* b, void* d,
                           behavior_stimuli* stimuli, u8* out)
{
    void* block = c->mpBTree->mStimuli.Play(0x8000, 0);
    void* n1 = FUN_00d99a10(block);
    if (n1 != 0) {
        ResNode* n2 = (ResNode*)FUN_00d998f0(n1);
        if (n2 != 0) {
            ResId* n3 = n2->GetSub();
            if (n3->GetId() != 0x2a034cd) {
                if (stimuli != 0)
                    stimuli->GetAny();
                stimuli->mTarget = n2;
                *out = 1;
                return 1.0f;
            }
        }
    } else {
        c->mpBTree->mStimuli.ClearAll(0x8000, 0);
    }
    return 0.0f;
}

// @ 0x00da66c0
float __cdecl FUN_00da66c0(cSPCreatureCitizen* c, void* a, void* b, void* d,
                           behavior_stimuli* stimuli, u8* out)
{
    void* block = c->mpBTree->mStimuli.Play(0x100, 0);
    cSPCreatureCitizen* other = (cSPCreatureCitizen*)FUN_00d999d0(block);
    if (other != 0 && !other->mbDead) {
        float val = other->mF5e0;
        float health = other->mCombat.GetMaxHealth();
        if (val < health) {
            if (stimuli != 0)
                stimuli->GetAny();
            stimuli->mTarget = &other->mCombat;
            *out = 1;
            return 1.0f;
        }
    }
    FUN_00da6270(c, 5);
    return 0.0f;
}

// @ 0x00da6750
float __cdecl FUN_00da6750(cSPCreatureCitizen* c, void* a, void* b, void* d,
                           behavior_stimuli* stimuli, u8* out)
{
    void* n1 = FUN_00d99a10(c->mpBTree->mStimuli.Play(0x400, 0));
    void* n2 = FUN_00d998f0(n1);
    if (n2 != 0) {
        if (stimuli != 0)
            stimuli->GetAny();
        stimuli->mTarget = n2;
        stimuli->mF18 = 7;
        *out = 1;
        return 1.0f;
    }
    c->mpBTree->mStimuli.ClearAll(0x400, 0);
    return 0.0f;
}

// @ 0x00da67c0
float __cdecl FUN_00da67c0(cSPCreatureCitizen* c, void* a, void* b, void* d,
                           behavior_stimuli* stimuli, u8* out)
{
    void* r = FUN_00d998d0(c->mpBTree->mStimuli.Play(0x800, 0), 0x4f396a66);
    if (r != 0) {
        int v = ((Res4f*)r)->mTime.GetValue();
        if (v != 0) {
            if (stimuli != 0)
                stimuli->GetAny();
            stimuli->mValue = v;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}