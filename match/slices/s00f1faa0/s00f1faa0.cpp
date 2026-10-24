// s00f1faa0 -- per-frame Update of a mission-intro/"reticle" style UI controller (state machine on +0x90).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//   state 1: fades the avatar's shield-like float (+0x80 of its component) over time, clears flags when done
//   state 3: countdown timers, then ScenarioTutorials_InitPlacement after 1 second
//   states 5/6: after stopwatch thresholds, hide the mission panel, stop the visual effect, release pause gate
//               and post a random trigger from a global list.
#include "types.h"
#include <intrin.h>
extern "C" float sqrtf(float);

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

// ===========================================================================
// 0x00f200c0..0x00f20a20 -- scenario / mission-intro UI helpers.
// The objects are UTFWin-style; the vtable slots used here follow
// cSpatialObject's layout: 0x0c interface query, 0x18 positional post,
// 0x2c position (spatial) / is-active (controller), 0x48 on-view,
// 0x5c child lookup, 0x6c bounding box, 0x90 model present, 0xb8 type cast.
// ===========================================================================

struct BoundingBox { float mnX, mnY, mnZ; float mxX, mxY, mxZ; };  // +0x00 min, +0x0c max

struct IVObj {
    virtual void   AddRef();                                            // +0x00
    virtual void   Release();                                           // +0x04
    virtual void   v008();                                              // +0x08
    virtual void*  GetInterface(uint32_t id);                           // +0x0c
    virtual void   v010();
    virtual void   v014();
    virtual void   PostAt(float value, int a, int b, void* data, void* obj); // +0x18
    virtual void   v01c();
    virtual void   v020();
    virtual void   v024();
    virtual void   v028();
    virtual bool   IsActive();                                          // +0x2c
    virtual void   v030();
    virtual void   v034();
    virtual void   v038();
    virtual void   v03c();
    virtual void   v040();
    virtual void   v044();
    virtual void   SetOnView(int on);                                   // +0x48
    virtual void   v04c();
    virtual void   v050();
    virtual void   v054();
    virtual void   v058();
    virtual void*  FindChild(uint32_t id);                              // +0x5c
    virtual void   v060();
    virtual void   v064();
    virtual void   v068();
    virtual BoundingBox* GetBounds(void* out);                          // +0x6c
    virtual void   v070();
    virtual void   v074();
    virtual void   v078();
    virtual void   v07c();
    virtual void   v080();
    virtual void   v084();
    virtual void   v088();
    virtual void   v08c();
    virtual bool   HasModel();                                          // +0x90
    virtual void   v094();
    virtual void   v098();
    virtual void   v09c();
    virtual void   v0a0();
    virtual void   v0a4();
    virtual void   v0a8();
    virtual void   v0ac();
    virtual void   v0b0();
    virtual void   v0b4();
    virtual IVObj* Cast(uint32_t type);                                 // +0xb8
};

// spatial object (creature / prop): slot 0x2c is GetPosition, not IsActive
struct SpatialObj {
    virtual void   AddRef();                                            // +0x00
    virtual void   Release();                                           // +0x04
    virtual void   v008();                                              // +0x08
    virtual void*  GetInterface(uint32_t id);                           // +0x0c
    virtual void   v010();
    virtual void   v014();
    virtual void   PostAt(float value, int a, int b, void* data, void* obj); // +0x18
    virtual void   v01c();
    virtual void   v020();
    virtual void   v024();
    virtual void   v028();
    virtual float* GetPosition();                                       // +0x2c
    virtual void   v030();
    virtual void   v034();
    virtual void   v038();
    virtual void   v03c();
    virtual void   v040();
    virtual void   v044();
    virtual void   v048();
    virtual void   v04c();
    virtual void   v050();
    virtual void   v054();
    virtual void   v058();
    virtual void*  FindChild(uint32_t id);                              // +0x5c
    virtual void   v060();
    virtual void   v064();
    virtual void   v068();
    virtual BoundingBox* GetBounds(void* out);                          // +0x6c
    virtual void   v070();
    virtual void   v074();
    virtual void   v078();
    virtual void   v07c();
    virtual void   v080();
    virtual void   v084();
    virtual void   v088();
    virtual void   v08c();
    virtual bool   HasModel();                                          // +0x90
    virtual void   v094();
    virtual void   v098();
    virtual void   v09c();
    virtual void   v0a0();
    virtual void   v0a4();
    virtual void   v0a8();
    virtual void   v0ac();
    virtual void   v0b0();
    virtual void   v0b4();
    virtual void*  Cast(uint32_t type);                                 // +0xb8
};

// object returned by GetInterface(0x13f94d4): carries a scalar at +0x38
struct PostTarget : IVObj {
    char  pad004[0x38 - 0x04];
    float f38;                                                          // +0x38
};

// controller base behind 00f20900 / 00f20990; slot 0x04 returns the target
struct CtlBase {
    virtual void   AddRef();                                            // +0x00
    virtual IVObj* GetTarget();                                         // +0x04
    virtual void   v008();                                              // +0x08
    virtual void*  GetInterface(uint32_t id);                           // +0x0c
    virtual void   v010();
    virtual void   v014();
    virtual void   PostAt(float value, int a, int b, void* data, void* obj); // +0x18
    virtual void   v01c();
    virtual void   v020();
    virtual void   v024();
    virtual void   v028();
    virtual bool   IsActive();                                          // +0x2c
};

// controller object behind 00f20990 / 00f20a20
struct Ctl2 : CtlBase {
    char   pad004[0x30 - 0x04];
    char   mActive;                                                     // +0x30
    char   pad031[3];
    float  mTimer;                                                      // +0x34
    IVObj* mObj;                                                        // +0x38
};

// component queried with id 0xce9f6639 (creature-ish): two named flags
struct Comp {
    char pad000[0xb10];
    char flagB10;                                                       // +0xb10
    char padb11[0xb18 - 0xb11];
    char flagB18;                                                       // +0xb18
    void SetFlags(int a, int b);                                        // 0x00c0d0c0
    bool Flag388();                                                     // 0x00c0c0e0
};

struct Tele { void Apply(void* target, void* dir, int z); };             // 0x00b452f0

// object returned by the 0x00b3d310 getter; its Apply is 0x00b452f0.
Tele* __cdecl FUN_00b3d310();

// win-proc child configured at the end of 00f20620 (ids 0x116dd1b)
struct ChildCfg {
    char pad000[0x77];
    char f77;                                                           // +0x77
    char pad078[0xa4 - 0x78];
    char fA4;                                                           // +0xa4
    char padA5[0x1f0 - 0xa5];
    int  f1F0;                                                          // +0x1f0
};

// plain thiscall "tick" target (no stack arguments) -- 0x00ca6db0 / 0x00c06f70
struct Ticker { void Tick(); };

struct UIEntry {                        // entry in the global win-proc list
    uint32_t key;                       // +0x00
    IVObj*   obj;                       // +0x04
    float    interval;                  // +0x08
    float    elapsed;                   // +0x0c
    void   (*callback)(UIEntry*);       // +0x10
};

struct WinProcMgr {
    int      FindFirst();                       // 0x00b72160
    UIEntry* GetEntry(int handle);              // 0x00b72210
    UIEntry* NextEntry(uint32_t* key);          // 0x00b72230
    void     RemoveByKey(uint32_t key);         // 0x00b72260
    void     ClearAll();                        // 0x00b72110
    int      GetPriority();                     // 0x00e31100
};
extern WinProcMgr* g_WinProcMgr;                // 0x016c831c

struct ScenarioSub {
    char pad000[0xb8];
    int  fB8;                                   // +0xb8
    int  ByIndex(void* arg);                    // 0x00f19840
    void Attach(void* ctl);                     // 0x00f1a7f0
};
struct UIRoot2 { char pad000[0x78]; ScenarioSub* sub; };
extern char g_16c8328;                          // 0x016c8328
extern float kCtlEps;                           // 0x013ec4b8 (FLT_EPSILON)
extern float kCtlHalf;                          // 0x01471064 (0.5f)
extern const float kCtlOne;                     // 0x01485720 (1.0f)

void __cdecl FUN_00eede20(void* out, int a, int b, float c, int d, int e,
                          int f, int g, int h);                  // 0x00eede20
void __cdecl FUN_00f196f0(void* obj);                            // 0x00f196f0

// @ 0x00f200c0 -- per-object/int "animation speed" lookup table.
float __cdecl FUN_00f200c0(uint32_t obj, int index)
{
    if (obj > 0x3a2511e) {
        if (obj == 0x2399be55) {
            switch (index) {
            case 1: case 2: case 3: case 4: case 5: case 0xf: return 0.2f;
            case 6: case 10: case 0xc: case 0xd: return 0.125f;
            case 7: case 8: case 0x10: return 0.3f;
            }
        } else if (obj == 0x24682294 || obj == 0x476a98c7) {
            switch (index) {
            case 1: case 2: case 3: case 4: case 5: case 0xf: return 0.75f;
            case 6: return 0.2f;
            case 7: case 8: case 0x10: return 0.5f;
            case 10: case 0xc: case 0xd: return 0.125f;
            }
        }
    } else if (obj == 0x3a2511e) {
        switch (index) {
        case 1: case 2: case 3: case 4: case 5: case 0xf: return 2.5f;
        case 6: return 1.5f;
        case 7: case 8: case 0x10: return 5.0f;
        case 0xb: case 0xe: return 10.0f;
        }
    } else if (obj != 0 && (obj == 0x18c88e4 || obj == 0x2a8fb3f)) {
        switch (index) {
        case 1: case 2: case 3: case 4: case 5: case 0xf: return 1.25f;
        case 6: return 0.75f;
        case 7: case 8: case 0x10: return 2.5f;
        case 10: case 0xc: case 0xd: return 0.5f;
        case 0xb: case 0xe: return 5.0f;
        }
    }
    return 1.0f;
}

// @ 0x00f20260 -- queue a scenario progress-bar reveal at a point.
void __cdecl FUN_00f20260(int a, int b, float c)
{
    ScenarioSub* s = ((UIRoot2*)g_UIRoot)->sub;
    int b8 = s->fB8;
    int pt[3];
    pt[0] = 0; pt[1] = 0; pt[2] = 0;
    FUN_00eede20(pt, a, b, c, 0, -1, 0, 0, b8);
}

// @ 0x00f202b0 -- bind the scenario progress bar and tick its children.
void __cdecl FUN_00f202b0(IVObj* ctl, void* arg)
{
    ScenarioSub* s = ((UIRoot2*)g_UIRoot)->sub;
    int v = s->ByIndex(arg);
    _ReadWriteBarrier();
    ctl->SetOnView(v);
    s->Attach(ctl);

    void* q = ctl->GetInterface(0x70704db);
    if (q)
        ((IVObj*)q)->HasModel();

    void* r = ctl->GetInterface(0x137e8e0);
    if (r)
        ((Ticker*)r)->Tick();         // 0x00ca6db0
    void* t = ctl->GetInterface(0xd0036e08);
    if (t)
        ((Ticker*)t)->Tick();         // 0x00c06f70
    void* u = ctl->GetInterface(0x13f94d4);
    if (u)
        FUN_00f196f0(u);
}

// @ 0x00f20350 -- register (or replace) a timed win-proc entry.
bool __cdecl FUN_00f20350(IVObj* obj, float interval, void (*cb)(UIEntry*))
{
    int h = g_WinProcMgr->FindFirst();
    if (!h)
        return false;
    UIEntry* e = g_WinProcMgr->GetEntry(h);
    IVObj* old = e->obj;
    if (obj != old) {
        if (obj)
            obj->AddRef();
        e->obj = obj;
        if (old)
            old->Release();
    }
    e->interval = interval;
    e->callback = cb;
    e->elapsed = 0.0f;
    return true;
}

// @ 0x00f203c0 -- update an existing timed entry, or add it if absent.
bool __cdecl FUN_00f203c0(IVObj* obj, float interval, void (*cb)(UIEntry*))
{
    uint32_t prio = (uint32_t)g_WinProcMgr->GetPriority();
    UIEntry* e = g_WinProcMgr->NextEntry(&prio);
    while (e) {
        if (e->obj == obj && e->callback == cb) {
            e->interval = interval;
            e->elapsed = 0.0f;
            return true;
        }
        e = g_WinProcMgr->NextEntry(&prio);
    }
    return FUN_00f20350(obj, interval, cb);
}

// @ 0x00f20440 -- fire every registered timed entry, then clear the list.
void __cdecl FUN_00f20440()
{
    uint32_t prio = (uint32_t)g_WinProcMgr->GetPriority();
    UIEntry* e = g_WinProcMgr->NextEntry(&prio);
    while (e) {
        e->callback(e);
        IVObj* o = e->obj;
        if (o) {
            e->obj = 0;
            o->Release();
        }
        g_WinProcMgr->RemoveByKey(e->key);
        e = g_WinProcMgr->NextEntry(&prio);
    }
    g_WinProcMgr->ClearAll();
}

// @ 0x00f204c0 -- advance every timed entry and fire the ones whose interval expired.
void __cdecl FUN_00f204c0(float dt)
{
    uint32_t prio = (uint32_t)g_WinProcMgr->GetPriority();
    UIEntry* e = g_WinProcMgr->NextEntry(&prio);
    while (e) {
        float t = e->elapsed + dt;
        e->elapsed = t;
        if (t > e->interval) {
            e->callback(e);
            IVObj* o = e->obj;
            if (o) {
                e->obj = 0;
                o->Release();
            }
            g_WinProcMgr->RemoveByKey(e->key);
        }
        e = g_WinProcMgr->NextEntry(&prio);
    }
}

// @ 0x00f20550 -- clear the +0xb18 flag of the entry's component unless active.
void __cdecl FUN_00f20550(UIEntry* e)
{
    if (e->obj->IsActive() == 1)
        return;
    IVObj* o = e->obj;
    Comp* q;
    if (o)
        q = (Comp*)o->GetInterface(0xce9f6639);
    else
        q = (Comp*)0;
    q->flagB18 = 0;
}

// @ 0x00f20590 -- clear the +0xb10 flag of the entry's component unless active.
void __cdecl FUN_00f20590(UIEntry* e)
{
    if (e->obj->IsActive() == 1)
        return;
    IVObj* o = e->obj;
    Comp* q;
    if (o)
        q = (Comp*)o->GetInterface(0xce9f6639);
    else
        q = (Comp*)0;
    q->flagB10 = 0;
}

// @ 0x00f205d0 -- reset (7,0) on the entry's component unless active.
void __cdecl FUN_00f205d0(UIEntry* e)
{
    if (e->obj->IsActive() == 1)
        return;
    IVObj* o = e->obj;
    Comp* q;
    if (o)
        q = (Comp*)o->GetInterface(0xce9f6639);
    else
        q = (Comp*)0;
    q->SetFlags(7, 0);
}

// @ 0x00f20620 -- aim `target` along a direction and post the positional event.
void __cdecl FUN_00f20620(SpatialObj* parent, SpatialObj* target, float param3, float param4)
{
    float dir[3];

    if (target) {
        float* p = target->GetPosition();
        float inv = 1.0f / sqrtf(p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + kCtlEps);
        dir[0] = p[0] * inv;
        dir[1] = p[1] * inv;
        dir[2] = p[2] * inv;
    }

    char flag;
    if (parent) {
        SpatialObj* q = (SpatialObj*)parent->GetInterface(0x1186577);
        if (!q)
            goto lab_207ef;
        if (!target)
            goto lab_20811;
        {
            BoundingBox b1, b2;
            BoundingBox* pb1 = q->GetBounds(&b1);
            float c1x = (pb1->mnX + pb1->mxX) * kCtlHalf;
            float c1y = (pb1->mnY + pb1->mxY) * kCtlHalf;
            float c1z = (pb1->mnZ + pb1->mxZ) * kCtlHalf;
            BoundingBox* pb2 = target->GetBounds(&b2);
            float dx = (pb2->mnX + pb2->mxX) * kCtlHalf - c1x;
            float dy = (pb2->mnY + pb2->mxY) * kCtlHalf - c1y;
            float dz = (pb2->mnZ + pb2->mxZ) * kCtlHalf - c1z;
            float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + kCtlEps);
            dir[0] = dx * inv;
            dir[1] = dy * inv;
            dir[2] = dz * inv;
        }
    }

lab_207ef:
    if (target) {
        Comp* c = (Comp*)target->Cast(0xce9f6639);
        if (c) {
            flag = c->Flag388() ? 1 : 0;
            goto lab_20813;
        }
    }
lab_20811:
    flag = 0;

lab_20813:
    if (target) {
        if (!flag) {
            float s = sqrtf(param3);
            float v[3];
            v[0] = dir[0] * s * param4;
            v[1] = dir[1] * s * param4;
            v[2] = dir[2] * s * param4;
            FUN_00b3d310()->Apply(target, v, 0);
        }
        PostTarget* pt = (PostTarget*)target->Cast(0x13f94d4);
        if (pt) {
            void* src = parent ? parent->GetInterface(0x13f94d4) : 0;
            pt->PostAt(param3, 0, 0, dir, src);
            ChildCfg* child = (ChildCfg*)target->FindChild(0x116dd1b);
            if (child) {
                child->f77 = 0;
                child->f1F0 = 3;
                child->fA4 = 1;
            }
        }
    }
}

// @ 0x00f20900 -- post the positional event from ctl's interface to obj.
void __cdecl FUN_00f20900(CtlBase* ctl, void* obj)
{
    IVObj* p = ctl->GetTarget();
    PostTarget* q = p ? (PostTarget*)p->GetInterface(0x13f94d4) : (PostTarget*)0;
    q->PostAt(q->f38, 0, 0x13, &g_16c8328, obj);
}

// @ 0x00f20990 -- lazily post the positional event when the controller is armed.
void __cdecl FUN_00f20990(Ctl2* ctl, IVObj* obj)
{
    IVObj* p = ctl->GetTarget();
    if (p->IsActive())
        return;
    if (!ctl->mActive)
        return;
    if (ctl->mObj == obj && ctl->mTimer < kCtlOne)
        return;
    IVObj* q0 = ctl->GetTarget();
    PostTarget* q = q0 ? (PostTarget*)q0->GetInterface(0x13f94d4) : (PostTarget*)0;
    PostTarget* r = obj ? (PostTarget*)obj->GetInterface(0x13f94d4) : (PostTarget*)0;
    q->PostAt(q->f38, 0, 0x13, &g_16c8328, r);
}

// @ 0x00f20a20 -- arm the controller with a new target and reset its timer.
void __cdecl FUN_00f20a20(Ctl2* ctl, IVObj* obj)
{
    IVObj* nv = obj;
    *(volatile char*)&ctl->mActive = 1;
    IVObj* old = *(IVObj* volatile*)&ctl->mObj;
    if (nv != old) {
        if (nv)
            nv->AddRef();
        ctl->mObj = nv;
        if (old)
            old->Release();
    }
    ctl->mTimer = 0.0f;
}
