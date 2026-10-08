// s00f1faa0 -- per-frame Update of a mission-intro/"reticle" style UI controller (state machine on +0x90).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//   state 1: fades the avatar's shield-like float (+0x80 of its component) over time, clears flags when done
//   state 3: countdown timers, then ScenarioTutorials_InitPlacement after 1 second
//   states 5/6: after stopwatch thresholds, hide the mission panel, stop the visual effect, release pause gate
//               and post a random trigger from a global list.
#include "types.h"

struct Stopwatch {
    uint64_t start;
    uint64_t elapsed;
    int mode;
    uint64_t GetElapsedTime();   // 0x0093a5e0
    void Stop();                 // 0x0093a2e0
};

struct cGameTimeManager {
    void IncPauseGate(uint32_t gate);   // 0x00b32220
    void DecPauseGate(uint32_t gate);   // 0x00b32250
    bool FUN_00f18ff0();                // 0x00f18ff0 : is gate 0x4bf38a7 held
};

struct AssetBrowserT { char pad[0x1c]; char flag1c; };

struct IVisualEffect {
    virtual void v0();
    virtual void Release();                 // +4
    virtual void v2(int);                   // +8
    virtual void v3(int);                   // +0xc
};
struct EffectRef {
    IVisualEffect* p;
    IVisualEffect** AsPPTypeParam();   // 0x00a16f40
};
struct EffectsManagerT {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4();
    virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9();
    virtual void e10();
    virtual bool GetEffect(uint32_t id, int arg, IVisualEffect** out);   // +0x2c
};

struct TriggerMgr {
    char pad[0x2c];
    int state;
    void FUN_00ad7e90(int);                                                          // 0x00ad7e90
    void PostTrigger(uint32_t id, int a, int b, int c, int d, int e);                // 0x00ae0930
    void FUN_00adde90(uint32_t id, void* data, int z);                               // 0x00adde90
};

struct RandomLCG {
    uint32_t RandomUint32Uniform(uint32_t n);   // 0x00a68fb0
};

struct cUICard { void SetVisible(int);          // 0x00e13360
};
struct cMissionPanel { void FUN_00e16a70(bool); // 0x00e16a70
};
struct PanelMgr {
    char pad0[0x148];
    cUICard* card;
    void FUN_00f0e4a0(int);                      // 0x00f0e4a0
};
struct UIRoot { char pad[0x6c]; PanelMgr* panels; };
extern UIRoot* g_UIRoot;                         // 0x016c7aa4

struct AvatarComp {
    char pad[0x80]; float f80;
    char pad1[0x17c - 0x84]; struct AvatarComp2* sub;   // +0x17c
    char* bits;                                  // +0x180 -> bitset storage at +0x44
};

struct GlyphIterator {
    void* node;
    void** bucket;
    GlyphIterator() {}
    GlyphIterator(const GlyphIterator& o) : node(o.node), bucket(o.bucket) {}
    GlyphIterator& operator++();                 // 0x009a69d0
};
struct GlyphTable {
    uint32_t alloc;
    void** buckets;
    uint32_t nBuckets;
    GlyphIterator begin();                       // 0x00594410
};
struct GlyphNode { void* next; struct GlyphVal* val; };
struct GlyphVal { char pad[0x8c]; struct GlyphObj* obj; };
struct GlyphObj {
    virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3();
    virtual bool IsActive();                     // +0x10
    virtual void g5(); virtual void g6(); virtual void g7(); virtual void g8(); virtual void g9(); virtual void g10();
    virtual void SetA(int);                      // +0x2c
    virtual void SetB(int);                      // +0x30
};

struct ModelManagerT {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual uint32_t GetIndex(uint32_t id, int z);   // +0x28
};

struct AvatarComp2 { char pad[0x17a0]; GlyphTable glyphs; };

struct Avatar {
    char pad[0xb54];
    AvatarComp* comp;       // +0xb54
    uint32_t flags;         // +0xb58
};
struct NounMgr {
    Avatar* GetAvatar();   // 0x00b1fdb0
};

extern "C" AssetBrowserT* FUN_00401030();
extern "C" cGameTimeManager* FUN_00b3d380();
extern "C" NounMgr* FUN_00b3d300();
extern "C" TriggerMgr* FUN_00b3d4d0();
extern "C" EffectsManagerT* FUN_0067ddd0();
extern "C" ModelManagerT* FUN_0067dd80();
extern "C" void FUN_00ef73c0();
extern RandomLCG g_Random;                       // 0x01601760
extern uint32_t g_015ad94c, g_015ad950, g_015ad954;
extern float g_015ad948;
struct TrigEntry { uint32_t id; uint32_t pad[3]; };   // 16-byte list entries
extern TrigEntry* g_016c82d0; extern TrigEntry* g_016c82d4;
extern TrigEntry* g_016c82e4; extern TrigEntry* g_016c82e8;
extern TrigEntry* g_016c82f8; extern TrigEntry* g_016c82fc;

struct TrigData { uint32_t a; uint32_t b; uint32_t c; };

struct Ctl {
    char pad0[0x78 - 0x0]; char f78;
    char pad1[0x90 - 0x79]; int state;
    int f94;
    Stopwatch sw;            // +0x98
    int fb0;
    char fb4;
    char padb5[7];
    int fbc;
    uint32_t fc0;
    char pad2[0xf8 - 0xc4]; float ff8;
    char ffc; char ffd;
    char pad3[2];
    EffectRef eff;   // +0x100

    void FUN_00f1f600();       // 0x00f1f600
    void FUN_00f1f3b0();       // 0x00f1f3b0
    void FUN_00f1b640(int);    // 0x00f1b640
    void FUN_00f1aae0(int);    // 0x00f1aae0
    void Update(uint32_t dt);
};

// @ 0x00f1faa0
void Ctl::Update(uint32_t dt)
{
    char on = FUN_00401030()->flag1c;
    if (on) {
        if (!fb4) {
            cGameTimeManager* g = FUN_00b3d380();
            g->IncPauseGate(0x4bf38a7);
        }
    } else if (fb4) {
        cGameTimeManager* g = FUN_00b3d380();
        g->DecPauseGate(0x4bf38a7);
    }
    fb4 = on;
    FUN_00f1f600();

    switch (state) {
    case 1:
        if (ffc) {
            float fdt = (float)dt;
            ff8 = ff8 - fdt;
            Avatar* av = FUN_00b3d300()->GetAvatar();
            if (av) {
                if (ff8 > 0.0f) {
                    av->comp->f80 = (1.0f / g_015ad948) * (float)dt + av->comp->f80;
                    return;
                }
                av->comp->f80 = 1.0f;
                av->flags &= 0xfffff7ff;
                ModelManagerT* mm = FUN_0067dd80();
                AvatarComp* comp = av->comp;
                uint32_t idx = mm->GetIndex(0x6669387, 0);
                if (idx < 0x40) {
                    uint32_t* w = (uint32_t*)(comp->bits + 0x44) + (idx >> 5);
                    *w &= ~(1u << (idx & 0x1f));
                }
                ffc = 0;
                AvatarComp2* sub = av->comp->sub;
                GlyphTable* tbl = &sub->glyphs;
                GlyphIterator it = tbl->begin();
                void* end = tbl->buckets[tbl->nBuckets];
                while (it.node != end) {
                    GlyphObj* o = ((GlyphNode*)it.node)->val->obj;
                    if (o && o->IsActive()) {
                        o->SetA(0);
                        o->SetB(0);
                    }
                    ++it;
                }
            }
        }
        break;
    case 2:
    case 4:
        break;
    case 3: {
        int st = FUN_00b3d4d0()->state;
        if (st != 1 && st != 2 && !fb4) {
            fc0 += dt;
            if (fbc > 0) {
                int v = fbc - dt;
                fbc = v;
                if (v <= 0) {
                    if (f78) {
                        FUN_00f1b640(1);
                        FUN_00f1aae0(6);
                    } else {
                        FUN_00f1f3b0();
                    }
                } else {
                    cUICard* c = g_UIRoot->panels->card;
                    if (c)
                        ((cMissionPanel*)c)->FUN_00e16a70(true);
                }
            }
        }
        if (!ffd && fc0 > 1000) {
            FUN_00ef73c0();
            ffd = 1;
        }
        break;
    }
    case 5: {
        if (f94 == 0) {
            cGameTimeManager* gtm = FUN_00b3d380();
            if (sw.GetElapsedTime() > (uint64_t)g_015ad94c && eff.p == 0) {
                g_UIRoot->panels->FUN_00f0e4a0(0);
                cUICard* c = g_UIRoot->panels->card;
                if (c) c->SetVisible(0);
                EffectsManagerT* em = FUN_0067ddd0();
                if (em->GetEffect(0x63ef90d9, 0, eff.AsPPTypeParam()))
                    eff.p->v2(1);
            }
            if (sw.GetElapsedTime() > (uint64_t)g_015ad950) {
                if (!gtm->FUN_00f18ff0())
                    gtm->IncPauseGate(0x4bf38a7);
            }
            if (sw.GetElapsedTime() > (uint64_t)g_015ad954) {
                gtm->DecPauseGate(0x4bf38a7);
                if (eff.p) {
                    eff.p->v3(0);
                    IVisualEffect* o = eff.p;
                    if (o) { eff.p = 0; o->Release(); }
                }
                sw.Stop();
                FUN_00b3d4d0()->FUN_00ad7e90(1);
                uint32_t i = g_Random.RandomUint32Uniform(g_016c82d4 - g_016c82d0);
                uint32_t id = g_016c82d0[i].id;
                FUN_00b3d4d0()->PostTrigger(id, 1, 0, 0, 0, 1);
                TrigData d;
                d.a = 0x7be2d40;
                d.b = 0;
                d.c = 0x21851ebe;
                FUN_00b3d4d0()->FUN_00adde90(0x498b0990, &d, 0);
                f94 = 1;
            }
        }
        break;
    }
    case 6: {
        if (f94 == 0) {
            cGameTimeManager* gtm = FUN_00b3d380();
            if (sw.GetElapsedTime() > (uint64_t)g_015ad94c && eff.p == 0) {
                g_UIRoot->panels->FUN_00f0e4a0(0);
                cUICard* c = g_UIRoot->panels->card;
                if (c) c->SetVisible(0);
                EffectsManagerT* em = FUN_0067ddd0();
                if (em->GetEffect(0x63ef90d9, 0, eff.AsPPTypeParam()))
                    eff.p->v2(1);
            }
            if (sw.GetElapsedTime() > (uint64_t)g_015ad950) {
                if (!gtm->FUN_00f18ff0())
                    gtm->IncPauseGate(0x4bf38a7);
            }
            if (sw.GetElapsedTime() > (uint64_t)g_015ad954) {
                gtm->DecPauseGate(0x4bf38a7);
                if (eff.p) {
                    eff.p->v3(0);
                    IVisualEffect* o = eff.p;
                    if (o) { eff.p = 0; o->Release(); }
                }
                sw.Stop();
                FUN_00b3d4d0()->FUN_00ad7e90(1);
                uint32_t id;
                if (fb0 == 0) {
                    uint32_t i = g_Random.RandomUint32Uniform(g_016c82fc - g_016c82f8);
                    id = g_016c82f8[i].id;
                } else {
                    uint32_t i = g_Random.RandomUint32Uniform(g_016c82e8 - g_016c82e4);
                    id = g_016c82e4[i].id;
                }
                FUN_00b3d4d0()->PostTrigger(id, 1, 0, 0, 0, 1);
                TrigData d;
                d.a = 0x7be2d41;
                d.b = 0;
                d.c = 0x21851ebe;
                FUN_00b3d4d0()->FUN_00adde90(0xa93873, &d, 0);
                f94 = 1;
            }
        }
        break;
    }
    }
}
