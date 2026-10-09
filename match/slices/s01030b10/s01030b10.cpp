// Slice s01030b10 -- SP::cSPSpaceGameBehaviorAbducted::OnAgentHitsGround (0x01030fd0).
// Called when an abducted agent (creature / plant / object) lands. Looks up the agent's
// interfaces by id, classifies the planet (lava / ice / terraform score), decides whether the
// agent was hit by the target, fires up to two feedback events and finally either kills the
// agent (cSpaceGameBehaviorSlowDeath::SetDeathType) or lets it live.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.  Callees are masked relocations: declarations only need
// the right calling convention and argument sizes.
#include <math.h>
typedef unsigned int uint;
typedef unsigned char uchar;

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct Species;                                              // opaque species handle

struct Tuning {
    float GetLavaThreshold();                                // 0x01049bf0 (x87 return)
    float GetIceThreshold();                                 // 0x01049c40
};
Tuning* GetTuning();                                         // 0x01049a10

struct Terrain {
    bool IsInside(Species* s, const Vec3* pos);              // 0x00c7f430 ret 8
    bool IsNear(void* a, Vec3 pos);                          // 0x00c7f300 ret 0x10
};

struct Planet {
    Terrain* GetTerrain();                                   // 0x008414c0
    float    GetValueA();                                    // 0x00c70a20 (x87 return)
    float    GetValueB();                                    // 0x00c709d0
};
Planet* GetActivePlanet();                                   // 0x01021260

struct PlanetRecord { char pad[0x2c]; uint mFlags; };        // +0x2c: bit 0x800
PlanetRecord* GetActivePlanetRecord();                       // 0x010212a0

struct Body {                                                // id 0x116dd1b
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual uint GetModelKey();                              // 0x2c
    virtual void v12(); virtual void v13();
    virtual void GetPosition(Vec3* out);                     // 0x38
};

struct Centered {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10();
    virtual const Vec3* GetCenter();                         // 0x2c
};
struct HitStats { char pad[0x25c]; float mRadius; };
struct Hit {
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4();
    virtual void h5(); virtual void h6(); virtual void h7(); virtual void h8(); virtual void h9();
    virtual void h10(); virtual void h11(); virtual void h12(); virtual void h13(); virtual void h14();
    virtual void h15(); virtual void h16(); virtual void h17(); virtual void h18(); virtual void h19();
    virtual void h20(); virtual void h21(); virtual void h22(); virtual void h23(); virtual void h24();
    virtual void h25(); virtual void h26();
    virtual HitStats* GetStats();                            // 0x6c
    char     pad[0x120 - 4];
    Centered mCenter;                                        // +0x120
};

struct PlanetModelT {
    void  GetPos(Vec3* out, uint key);                       // 0x00b81630 ret 8
    float GetHeight(Vec3* pos, int mode);                    // 0x00b7e430 ret 8 (x87 return)
    Hit*  FindHit(Vec3* pos);                                // 0x00b894a0 ret 4
};
PlanetModelT* PlanetModel();                                 // 0x00b3d350

struct SlowDeath { void SetDeathType(int t); };              // 0x01034260 ret 4
struct Slow {
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual SlowDeath* Find(uint id);                        // 0x0c
};
struct SubObj {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void Notify(uint a, int b, int c);               // 0x0c
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual Slow* GetHandler();                              // 0x20
};

struct Blob { void Flush(); };                               // 0x00bcb3d0

struct FlagBlock { char pad[0x192]; uchar mFlag; };
struct Controller {                                          // id 0xd0036e08
    Species*   GetSpecies();                                 // 0x00c0bc00
    FlagBlock* GetFlags();                                   // 0x00c04590
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual void Refresh();                                  // 0x54
};

struct Creature {                                            // id 0xce9f6639
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void Stop(int a);                                // 0x9c
    char    pad0[0x58 - 4];
    SubObj  mSub;                                            // +0x58
    char    pad1[0xb4c - 0x58 - 4];
    Blob*   mBlob;                                           // +0xb4c
    bool    IsFlagged();                                     // 0x00c0b780
    void    SetPending(int v);                               // 0x00c14750 ret 4
};
void FUN_00c0d3a0(Creature* c);                              // cdecl

struct Trigger { bool IsSet(); };                            // id 0x4f176642: 0x00c232c0
struct Sense   { void* GetObject(Vec3* out); };              // id 0xaeb336b4: 0x00c3e1e0 ret 4

struct Agent {
    virtual void a0(); virtual void a1();
    virtual void* GetInterface(uint id);                     // 0x08
};

struct Profile { char pad[0x608]; uint mA; uint mB; };       // +0x608 / +0x60c
struct SettingsMgr { Profile* GetProfile(Species* s); };     // 0x004df550 ret 4
SettingsMgr* Settings();                                     // 0x00401090

struct TerraMgr {
    int  GetScore(int planet);                               // 0x00bbc670 ret 4
    bool CheckA(Species* s, bool a, bool b, int c, bool* out);   // 0x00bbee30 ret 0x14
    bool CheckB(void* a, void* b, int c, bool* out);             // 0x00bbecc0 ret 0x10
};
TerraMgr* TerraformingManager();                             // 0x00b3d430

struct Spec {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5();
    virtual void* GetKey();                                  // 0x18
    void* GetClass();                                        // 0x00b8f860
};
struct SpeciesMgr { Spec* GetSpeciesFromID(void* id); };     // 0x00b90410 ret 4
SpeciesMgr* FUN_00b3d420();

struct Mgr60 {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14();
    virtual void m15(); virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void Fire(uint id, Vec3* pos, void* extra);      // 0x60
};
Mgr60* FUN_00b3d240();
struct Mgr2 { void Done(Creature* c); };                     // 0x00aca360 ret 4
Mgr2*  FUN_00b3d480();

struct EventLogT { void PostFeedbackEvent(uint id, uint a, int b, int c, int d, int e); };  // ret 0x18
EventLogT* EventLog();                                       // 0x00b3d3e0
int    GetCurrentGameMode();                                 // 0x00b5b800
struct Sim { void* GetPlayerInventory(); };                  // 0x00a1ad60
Sim*   GetUFOSimulator();                                    // 0x00ffbe50
extern uint DAT_016df328;
extern char DAT_016ded38[];

struct Abducted {
    char  pad0[0x9c];
    void* mInventory;                                        // +0x9c
    bool  OnAgentHitsGround(Agent* agent, bool beam, bool flag);
};

// @ 0x01030fd0
bool Abducted::OnAgentHitsGround(Agent* agent, bool beam, bool flag)
{
    (void)beam;
    if (!agent) return true;
    Body* body = (Body*)agent->GetInterface(0x116dd1b);
    if (!body) return true;
    Creature*   creature = (Creature*)agent->GetInterface(0xce9f6639);
    Controller* ctl      = (Controller*)agent->GetInterface(0xd0036e08);
    Trigger*    trigger  = (Trigger*)agent->GetInterface(0x4f176642);
    Sense*      sense    = (Sense*)agent->GetInterface(0xaeb336b4);
    if (!sense && !creature) return true;

    Planet*  planet  = GetActivePlanet();
    Terrain* terrain = planet->GetTerrain();
    if (ctl) ctl->Refresh();

    Vec3 pos;
    PlanetModel()->GetPos(&pos, body->GetModelKey());
    body->GetPosition(&pos);

    int  score = TerraformingManager()->GetScore(0);
    bool noScore = (score == 0);
    bool out13 = noScore;
    bool scored = !noScore;

    float height = PlanetModel()->GetHeight(&pos, 1);
    bool lava;
    if (height > 0.0f && planet->GetValueA() > GetTuning()->GetLavaThreshold())
        lava = true;
    else
        lava = false;
    bool ice;
    if (height > 0.0f && planet->GetValueA() < GetTuning()->GetIceThreshold())
        ice = true;
    else
        ice = false;
    bool hasHeight = (height != 0.0f);

    bool near;
    Hit* hit = PlanetModel()->FindHit(&pos);
    if (hit) {
        const Vec3* c = hit->mCenter.GetCenter();
        Vec3 d;
        d.x = pos.x - c->x;
        d.y = pos.y - c->y;
        d.z = pos.z - c->z;
        near = hit->GetStats()->mRadius > sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
    } else {
        near = false;
    }

    bool hitTarget;
    if (!noScore) {
        if (ctl) {
            Species* sp = ctl->GetSpecies();
            Profile* prof = Settings()->GetProfile(sp);
            if (prof) {
                if (hasHeight && TerraformingManager()->CheckA(sp, prof->mB > 0, prof->mA > 0, 0, &out13))
                    scored = true;
                else
                    scored = false;
            }
        } else {
            if (!sense) goto no_hit;
            {
                Vec3 tmp;
                Spec* sp = FUN_00b3d420()->GetSpeciesFromID(sense->GetObject(&tmp));
                scored = TerraformingManager()->CheckB(sp->GetKey(), sp->GetClass(), 0, &out13);
            }
            goto try_sense;
        }
    }
    if (ctl) {
        if (terrain->IsInside(ctl->GetSpecies(), &pos)) goto hit_yes;
    }
try_sense:
    if (sense) {
        Vec3 tmp;
        if (terrain->IsNear(sense->GetObject(&tmp), pos)) goto hit_yes;
    }
no_hit:
    hitTarget = false;
    goto after_hit;
hit_yes:
    hitTarget = true;
after_hit:

    if (ctl && ctl->GetFlags())
        ctl->GetFlags()->mFlag = !scored;

    if (!hitTarget && !noScore && scored && !lava && hasHeight) {
        if (!flag) return true;
        if (!creature) return true;
    }

    uint evA = 0, evB = 0;
    if (lava) {
        if (creature) evB = 0x6addd9bc;
        else if (!sense) return hitTarget;
        else { evA = 0xe4141994; evB = 0xf8b7cb07; }
    } else if (!hasHeight && !ice) {
        if (creature) evB = 0xd4495c37;
        else if (!sense) return hitTarget;
        else { evA = 0x534a52c0; evB = 0x6843ead6; }
    } else if (flag && creature) {
        evB = 0xf804e08c;
    } else if (scored) {
        if (hitTarget) evB = 0x27d13994;
    } else {
        if (sense) {
            evA = 0x33ce359;
            if (noScore) {
                float da = (float)fabs(planet->GetValueA() - 0.5f);
                float db = (float)fabs(planet->GetValueB() - 0.5f);
                if (da >= db)
                    evA = (0.5f > planet->GetValueA()) ? 0x4fd21bbc : 0xd3520187;
                else
                    evA = (0.5f > planet->GetValueB()) ? 0xf7129557 : 0xed8c1210;
            }
        }
        if (!trigger) {
            if (!out13) {
                if (creature) {
                    if (GetActivePlanetRecord()->mFlags & 0x800)
                        evB = 0xcd46959;
                    else
                        evB = (creature->IsFlagged() ? 0x9d6d92a3 : 0) + 0xca1ad72a;
                } else if (sense) {
                    evB = 0x7e1fde15;
                }
            } else {
                evB = ((uint)(score >= 3) - 1 & 0x45acd817) + 0x99f93d3d;
            }
        }
    }

    if (evA) {
        Mgr60* mgr = FUN_00b3d240();
        float len2 = pos.x * pos.x + pos.z * pos.z + pos.y * pos.y;
        float inv = (float)(1.0 / sqrt(len2 + 1e-8f));
        Vec3 dir;
        dir.x = inv * pos.x;
        dir.y = pos.y * inv;
        dir.z = pos.z * inv;
        mgr->Fire(evA, &pos, &dir);
    }
    if (evB) {
        if (GetCurrentGameMode() == 0x1654c05) {
            void* inv = this->mInventory;
            if (inv == GetUFOSimulator()->GetPlayerInventory())
                EventLog()->PostFeedbackEvent(evB, 0x131a9f54, 0, 0, 1, 0);
        }
    }

    if (!creature) return hitTarget;
    creature->Stop(0);
    if (trigger) {
        if (trigger->IsSet()) {
            FUN_00c0d3a0(creature);
            if (creature->mBlob) creature->mBlob->Flush();
        }
        if (hasHeight && near && !flag) return true;
    }

    int code = 0;
    if (lava) {
        code = 8;
    } else if (!hasHeight && !ice) {
        code = 7;
    } else if (flag) {
        code = 1;
    } else if (noScore) {
        float da = (float)fabs(planet->GetValueA() - 0.5f);
        float db = (float)fabs(planet->GetValueB() - 0.5f);
        if (da >= db)
            code = (0.5f > planet->GetValueA()) ? 2 : 3;
        else
            code = (0.5f > planet->GetValueB()) ? 4 : 5;
    } else if ((!trigger && !scored) || out13) {
        code = 6;
    }

    if (hasHeight && near && !flag) {
        creature->SetPending(1);
        body->GetPosition(&pos);
        FUN_00b3d240()->Fire(0x2818ee0, &pos, DAT_016ded38);
        FUN_00b3d480()->Done(creature);
        return true;
    }
    if (code) {
        SubObj* sub = &creature->mSub;
        sub->Notify(DAT_016df328, 0, 0);
        Slow* h = sub->GetHandler();
        if (h) {
            SlowDeath* sd = h->Find(0x3cdbbe9);
            if (sd) sd->SetDeathType(code);
        }
        return false;
    }
    if (trigger) return true;
    return hitTarget;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EventLogT {
    void PostFeedbackEvent(unsigned int, unsigned int, int, int, int, int); // 0x00dd8640
};
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct Blob {
    void Flush();   // 0x00c0b780 (equiv t3)
};
struct Mgr2 {
    void Done();   // 0x00aca360 (equiv t3)
};
struct SlowDeath {
    void SetDeathType();   // 0x01034260 (equiv t2)
};
}
