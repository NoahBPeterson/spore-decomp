// s00ae73e0: combat/tool manager per-frame update (retail layout; names are working names).
#include "types.h"
#include <math.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
inline Vec3 operator-(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vec3 operator*(const Vec3& a, float s) { return Vec3(s * a.x, a.y * s, a.z * s); }
inline float Len2(const Vec3& a) { return (a.z * a.z + a.y * a.y) + a.x * a.x; }

static inline float InvSqrt(float x) { return 1.0f / sqrtf(x); }

struct NounComp {                        // result of Noun::Query(0x17f243b)
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual bool IsDone();                                   // +0x2c
};

struct Noun {                            // entries of the manager's pending lists
    virtual void v00();
    virtual NounComp* Query(uint32_t id);                    // +0x04
    virtual void Release();                                  // +0x08
    virtual void AddRef();                                   // +0x0c
    virtual void v04();
    virtual bool IsKept();                                   // +0x14
};

struct Timer {
    uint64_t GetElapsedTime();                               // 0xbc3190
    void Restart();                                          // 0xbc3130
};

struct Tool {
    bool FUN_0104bd50();                                     // 0x104bd50
    int FUN_0104be00();                                      // 0x104be00
    uint32_t pad00[0xe8 / 4];
    Timer mTimer;                                            // +0xe8
    uint32_t pad01[(0x11c - 0xec) / 4];
    int mField11c;                                           // +0x11c
};

struct Spatial2 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vec3* GetPosition();                       // +0x2c
};

struct Combat;
struct Tgt {                             // combat target
    virtual void v00(); virtual void v01();
    virtual Spatial2* GetSpatial();                          // +0x08
    virtual void v03();
    virtual void* GetAux();                                  // +0x10
    virtual void v05(); virtual void v06();
    virtual void OnTargeted(Combat* by);                     // +0x1c
    virtual void v08();
    virtual int GetVal();                                    // +0x24
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22();
    virtual NounComp* Query(uint32_t id);                    // +0x5c
    virtual void AddRef();                                   // +0x60
    virtual void Release();                                  // +0x64
    int GetDamageState();                                    // 0x8e7f80
};

struct Combat {
    virtual void v00(); virtual void v01();
    virtual void* GetObj();                                  // +0x08
    virtual void v03(); virtual void v04();
    virtual Tool* GetTool();                                 // +0x14
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual bool CanTarget(Tgt* t);                          // +0x40
    uint32_t pad04[(0x44 - 4) / 4];
    Tgt* mTarget;                                            // +0x44
    Tgt* mNewTarget;                                         // +0x48
    void FUN_00bfcc00();                                     // 0xbfcc00
    void FUN_00bfddc0(void* a);                              // 0xbfddc0
    int GetDamageState();                                    // 0x8e7f80
};

struct ToolMgr {
    void UseToolStop(Tool* t);                               // 0x104fa90
    void UseToolUpdate(Tool* t, const Vec3* pos, int val, int dt);   // 0x10504a0
    void UseToolStart(Tool* t, void* obj, const Vec3* pos, int val, int dt, Spatial2* target, int one);   // 0x1050070
};

struct Effect {                          // embedded effect object (own vtable)
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual void SetValue(float v, int kind, const Vec3* dir, int flags);   // +0x18
    virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21();
    virtual float Compute(int a);                            // +0x58
};

struct Loco;                              // locomotive / spatial (own vtable)
struct Spatial {                          // a neighbour
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vec3* GetPosition();                       // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28();
    virtual float GetRadius();                               // +0x74
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
    virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
    virtual void* GetComponent(uint32_t id);                 // +0xb8
};

struct CompA {                           // component with type tag 0x18c8f0c (effect at +0x120)
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual const void* GetType();                           // +0x20
    virtual void v09(); virtual void v10();
    virtual bool IsDone();                                   // +0x2c
    uint32_t pad04[(0x120 - 4) / 4];
    Effect mEffect;                                          // +0x120
};

struct CreatureComp {                    // component 0xce9f6639 of a creature
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual int GetTeam();                                   // +0x4c
    uint32_t pad04[(0xc0 - 4) / 4];
    Spatial mBody;                                           // +0xc0
    char pad05[0x137 - 0xc4];
    bool mActive;                                            // +0x137
    uint32_t pad07[(0x5a8 - 0x138) / 4];
    Effect mEffect;                                          // +0x5a8
    bool FUN_00c0c0e0();                                     // 0xc0c0e0
};

struct NeighborList { Spatial** mpBegin; Spatial** mpEnd; };

struct Loco {                             // embedded locomotive object (own vtable) of an Ent
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vec3* GetPosition();                       // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual float Slot70();                                  // +0x70
    virtual float GetRadius();                               // +0x74
    const Vec3* GetVelocity();                               // 0xd20610
    NeighborList* GetNeighbors();                            // 0xc420d0
};

struct Combatant { int GetDamageState(); };                  // 0x8e7f80

struct Ent {                              // game-data object holding a Loco at +0x34
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual int GetTeam();                                   // +0x4c
    float FUN_00c9f330(int x);                               // 0xc9f330
    uint32_t pad04[(0x34 - 4) / 4];
    Loco mLoco;                                              // +0x34
    uint32_t pad38[(0x508 - 0x38) / 4];
    Combatant mCombatant;                                    // +0x508
    char pad09[0xb1c - 0x509];
    int mState;                                              // +0xb1c
};

struct GDV { int pad; void** mpBegin; void** mpEnd; void** mpCap; };

struct NounMgr {
    GDV* GetGameDataVector(void (__cdecl *a)(), void (__cdecl *b)(), void (__cdecl *c)(), void (__cdecl *d)(), const void* tag);   // 0xb21340
    void RemoveNoun(NounComp* n);                            // 0xb225d0
};

struct CivStrategy { bool FUN_00cf7a90(); };                 // 0xcf7a90

NounMgr* GetNounMgr();                  // 0xb3d300
ToolMgr* GetToolMgr();                  // 0xb3d390
CivStrategy* GetCivStrategy();          // 0xcf74c0
void* GetUniverseContext();             // 0x1021080
const void* GetCurrentGameMode();       // 0xb5b800
Noun** FUN_00ae67d0(Noun** first, Noun** last, Noun** dest);   // 0xae67d0

void __cdecl FUN_00cd7d10(); void __cdecl FUN_00ae7230(); void __cdecl FUN_00ae7250(); void __cdecl FUN_00b1e520();
void __cdecl FUN_00d3d420(); void __cdecl FUN_00ae72d0(); void __cdecl FUN_00b1e500();
extern const char kTagCombat;           // 0x13f94d4
// Game-data type tag: a fixed address in the image's .bind range, written as a constant.
#define kTagEntPtr ((const void*)0x018c6de8)

struct CombatMgr {
    uint32_t pad00[0x14 / 4];
    Noun** mAbegin;                                          // +0x14
    Noun** mAend;                                            // +0x18
    uint32_t pad1c[(0x28 - 0x1c) / 4];
    Noun** mBbegin;                                          // +0x28
    Noun** mBend;                                            // +0x2c
    uint32_t pad30[(0x3c - 0x30) / 4];
    bool mBusy;                                              // +0x3c
    bool mPending;                                           // +0x3d

    void FUN_00ae7350();                                     // 0xae7350
    void Update(uint64_t dt);
};

static const void* const kTypeCreatureComp = (const void*)0x18c8f0c;
static const void* const kModeA = (const void*)0x1654c04;
static const void* const kModeB = (const void*)0x1654c05;
static const void* const kModeC = (const void*)0x1654c10;

// @ 0x00ae73e0
void CombatMgr::Update(uint64_t dt)
{
    if (mPending)
        FUN_00ae7350();
    if (dt == 0)
        return;

    GDV* gv = GetNounMgr()->GetGameDataVector(FUN_00cd7d10, FUN_00ae7230, FUN_00ae7250, FUN_00b1e520, &kTagCombat);
    Combat** cur = (Combat**)gv->mpBegin;
    Combat** end = (Combat**)gv->mpEnd;
    for (; cur != end; ++cur) {
        Combat* obj = *cur;
        obj->FUN_00bfcc00();
        Tgt* tgt = obj->mTarget;
        Tool* tool = obj->GetTool();
        if (!tool)
            continue;
        bool active = tool->FUN_0104bd50();
        if (obj->GetDamageState() == 2) {
        stopTool:
            if (active)
                GetToolMgr()->UseToolStop(tool);
            continue;
        }
        if (tgt != obj->mNewTarget) {
            if (active) {
                GetToolMgr()->UseToolStop(tool);
                active = false;
            }
            Tgt* nt = obj->mNewTarget;
            Tgt* ot = obj->mTarget;
            if (nt != ot) {
                if (nt)
                    nt->AddRef();
                obj->mTarget = nt;
                if (ot)
                    ot->Release();
            }
            tgt = obj->mTarget;
        }
        if (!tgt)
            continue;
        {
            NounComp* qc = tgt->Query(0x17f243b);
            if (tgt->GetDamageState() == 2 || (qc && qc->IsDone())) {
                if (active)
                    GetToolMgr()->UseToolStop(tool);
                Tgt* t1 = obj->mTarget;
                obj->mTarget = 0;
                if (t1)
                    t1->Release();
                Tgt* t2 = obj->mNewTarget;
                obj->mNewTarget = 0;
                if (t2)
                    t2->Release();
                continue;
            }
            if (!obj->CanTarget(tgt))
                goto stopTool;
            Vec3 pos = *tgt->GetSpatial()->GetPosition();
            if (active && tool->FUN_0104be00() != -1) {
                int val;
                if (tool->mTimer.GetElapsedTime() > 3000) {
                    val = tgt->GetVal();
                    tool->mTimer.Restart();
                    obj->FUN_00bfddc0(tgt->GetAux());
                    tgt->OnTargeted(obj);
                } else {
                    val = tool->mField11c;
                }
                if (GetUniverseContext())
                    val = -1;
                GetToolMgr()->UseToolUpdate(tool, &pos, val, (int)dt);
            } else {
                int val = tgt->GetVal();
                if (GetUniverseContext())
                    val = -1;
                tool->mTimer.Restart();
                GetToolMgr()->UseToolStart(tool, obj->GetObj(), &pos, val, (int)dt, tgt->GetSpatial(), 1);
                tgt->OnTargeted(obj);
                obj->FUN_00bfddc0(tgt->GetAux());
            }
            continue;
        }
    }

    mBusy = true;
    int n = (int)(mAend - mAbegin);
    int idx = 0;
    if (0 < n) {
        do {
            Noun* p = mAbegin[idx];
            NounComp* qc;
            if (p)
                qc = p->Query(0x17f243b);
            else
                qc = 0;
            if (!qc->IsDone()) {
                if (p->IsKept()) {
                    ++idx;
                    continue;
                }
                GetNounMgr()->RemoveNoun(qc);
            }
            {
                Noun* last = mAend[-1];
                Noun** slot = mAbegin + idx;
                Noun* old = *slot;
                if (last != old) {
                    if (last)
                        last->AddRef();
                    *slot = last;
                    if (old)
                        old->Release();
                }
                mAend = mAend - 1;
                Noun* gone = *mAend;
                if (gone)
                    gone->Release();
                --n;
            }
        } while (idx < n);
    }

    int m = (int)(mBend - mBbegin);
    for (int i = 0; i < m; ++i) {
        Noun* p = mBbegin[i];
        NounComp* qc;
        if (p)
            qc = p->Query(0x17f243b);
        else
            qc = 0;
        if (!qc->IsDone())
            GetNounMgr()->RemoveNoun(qc);
    }
    {
        Noun** first = mBbegin;
        Noun** last = mBend;
        Noun** e = FUN_00ae67d0(last, last, first);
        for (Noun** q = e; q < mBend; ++q) {
            if (*q)
                (*q)->Release();
        }
        mBend = mBend - (last - first);
    }
    mBusy = false;

    if (GetCivStrategy()->FUN_00cf7a90())
        return;
    if (GetCurrentGameMode() != kModeA && GetCurrentGameMode() != kModeB)
        return;

    GDV* ev = GetNounMgr()->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00ae72d0, FUN_00b1e500, kTagEntPtr);
    Ent** ecur = (Ent**)ev->mpBegin;
    Ent** eend = (Ent**)ev->mpEnd;
    for (; ecur != eend; ++ecur) {
        Ent* e = *ecur;
        Loco* loco = &e->mLoco;
        const Vec3* vel = loco->GetVelocity();
        if (!(0.1f <= sqrtf(vel->z * vel->z + vel->y * vel->y + vel->x * vel->x)))
            continue;
        if (e->mState == 2 || e->mCombatant.GetDamageState() == 2)
            continue;
        loco->Slot70();
        loco->GetPosition();
        NeighborList* nl = loco->GetNeighbors();
        Spatial** ncur = nl->mpBegin;
        Spatial** nend = nl->mpEnd;
        for (; ncur != nend; ++ncur) {
            Spatial* q = *ncur;
            if (!q)
                continue;
            CompA* comp = (CompA*)q->GetComponent(0x17f243b);
            if (!comp)
                continue;
            if (comp->IsDone())
                continue;
            if (comp->GetType() != kTypeCreatureComp) {
                CreatureComp* cc = (CreatureComp*)q->GetComponent(0xce9f6639);
                if (!cc)
                    continue;
                if (cc->FUN_00c0c0e0())
                    continue;
                const Vec3* pa = loco->GetPosition();
                const Vec3* pb = cc->mBody.GetPosition();
                Vec3 d = *pb - *pa;
                float d2 = Len2(d);
                float rl = loco->GetRadius();
                float rb = cc->mBody.GetRadius();
                float lim = (rb + rl) - 1.0f;
                if (!(lim * lim > d2))
                    continue;
                if (GetCurrentGameMode() != kModeC) {
                    Vec3 dir = d * InvSqrt(d2);
                    Effect* ef = &cc->mEffect;
                    ef->SetValue(ef->Compute(e->GetTeam()), 6, &dir, 0);
                } else {
                    if (!cc->mActive)
                        continue;
                    if (cc->GetTeam() == e->GetTeam())
                        continue;
                    Vec3 dir = d * InvSqrt(d2);
                    Effect* ef = &cc->mEffect;
                    ef->SetValue(e->FUN_00c9f330(e->GetTeam()), 6, &dir, 0);
                }
            } else {
                const Vec3* pa = loco->GetPosition();
                const Vec3* pb = q->GetPosition();
                Vec3 d = *pb - *pa;
                float d2 = Len2(d);
                float rq = q->GetRadius();
                float rl = loco->GetRadius();
                float lim = (rl + rq) - 1.0f;
                if (d2 < lim * lim) {
                    CompA* c = (comp->GetType() == kTypeCreatureComp) ? comp : 0;
                    Effect* ef = &c->mEffect;
                    Vec3 dir = d * InvSqrt(d2);
                    ef->SetValue(ef->Compute(e->GetTeam()) * 0.25f, 6, &dir, 0);
                }
            }
        }
    }
}
