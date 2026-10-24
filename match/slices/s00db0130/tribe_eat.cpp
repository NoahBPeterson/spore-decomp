// Slice s00db0130 (part b) -- the "TribeEat" behaviour-tree task functions:
//   00db09c0  task objective / locomotion setup
//   00db0b80  task bind (create the TribeEat node, idle animation)
//   00db0cb0  task spot re-find / target release
//   00db0d40  task distance probe
//   00db0e30  per-frame target maintenance (bool)
//   00db1030  task deactivate / re-select
//
// All of them operate on the "TribeEat" state block passed in on the stack.
#include <stddef.h>
typedef unsigned int uint32_t;

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct IRef { virtual void AddRef(); virtual void Release(); };

struct Spatial {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual const Vec3* GetPosition();                 // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual bool IsBundle();                           // +0x58
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74
    float __thiscall vf3c();                           // +0x3c
    char* __thiscall BundleQuery();                    // 0x00cee330
};

struct Target {
    virtual void AddRef(); virtual void Release();
    uint32_t pad04[(0x34 - 4) / 4];
    Spatial  mSpatial;                                 // +0x34
    uint32_t pad38[(0x120 - 0x38) / 4];
    IRef*    mpOwner;                                  // +0x120
    uint32_t pad124[(0x128 - 0x124) / 4];
    int      mi128;                                    // +0x128
    uint32_t pad12c[(0x134 - 0x12c) / 4];
    float    mf134;                                    // +0x134
};

struct AutoRef {
    IRef* mp;
    void __thiscall Assign(IRef* p);                   // 0x00b5f950, ret 4
};

struct Tribe {
    uint32_t pad00[(0x120 - 0x00) / 4];
    Spatial  mPos;                                     // +0x120
    uint32_t pad124[(0x260 - 0x124) / 4];
    struct Bundle260* mpObj;                           // +0x260
    uint32_t pad264[(0x268 - 0x264) / 4];
    float    mfRadius;                                 // +0x268
    void __thiscall FindSpot(int type, int spot);      // 0x00c98750, ret 8
    void __thiscall FUN_00c97d40(int a, IRef* b);      // 0x00c97d40, ret 8
};
struct Bundle260 {
    uint32_t pad00[(0x34 - 0x00) / 4];
    Spatial  mSpatial;                                 // +0x34
};

struct SpotOwner {                                     // tribe container
    void __thiscall FindSpot(int type, int spot);      // 0x00c98750, ret 8
    void __thiscall FUN_00c97d40(int a, IRef* b);      // 0x00c97d40, ret 8
};

struct AnimCtl {                                       // citizen +0xb4c
    void* __thiscall PlayIdleAnimation(unsigned id, int a);         // 0x00bc96a0, ret 8
    void  __thiscall FUN_00bc97f0(int a, int b, float c, int d);    // 0x00bc97f0, ret 0x10
    void* __thiscall FUN_00bc9b10();                                // 0x00bc9b10
    void  __thiscall FUN_00bcb430();                                // 0x00bcb430
    void  __thiscall FUN_00bcb480(void* t, void* c, int a, int b);  // 0x00bcb480
};
struct Citizen {
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
    virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
    virtual void c28(); virtual void c29(); virtual void c30(); virtual void c31();
    virtual void c32();
    virtual void vf84(void* part, int a, int b);                   // +0x84
    void __thiscall UpdateLocomotion(int a);                       // 0x00c14750
    void __thiscall FUN_00c25f80();                                // 0x00c25f80
    void __thiscall SetSprinting(int a);                           // 0x00c1ad10
    bool __thiscall FUN_00c0c120();                                // 0x00c0c120
    bool __thiscall FUN_00c0b770();                                // 0x00c0b770
    Tribe* __thiscall GetTribe();                                  // 0x00c22f50
    uint32_t pad04[(0x34 - 4) / 4];
    Spatial  mBundle;                                              // +0x34
    uint32_t pad38[(0xc0 - 0x38) / 4];
    Spatial  mLoco;                                                // +0xc0
    uint32_t padc4[(0xb4c - 0xc4) / 4];
    AnimCtl* mpAnim;                                               // +0xb4c
};

struct PoolEntry { bool mbActive; uint32_t pad1; void* mpObj; uint32_t pad8; };
struct Pool600 {
    uint32_t pad00[(0x10 - 0x00) / 4];
    int      mi10;                                     // +0x10
    uint32_t pad14[(0x18 - 0x14) / 4];
    int      mi18;                                     // +0x18
    uint32_t pad1c;
    PoolEntry* mpEntries;                              // +0x20
    uint32_t pad24[(0x1a4 - 0x24) / 4];
    int      mi1a4;                                    // +0x1a4
    uint32_t pad1a8[(0x1bc - 0x1a8) / 4];
    int      mi1bc;                                    // +0x1bc
    uint32_t pad1c0[(0x1cc - 0x1c0) / 4];
    void*    mp1cc;                                    // +0x1cc
    IRef*    mp1d0;                                    // +0x1d0
    IRef*    mp1d4;                                    // +0x1d4
};

struct EatState {
    int      mPhase;                                   // +0x00
    IRef*    mOwner;                                   // +0x04
    IRef*    mExtra;                                   // +0x08
    AutoRef  mHolderC;                                 // +0x0c
    int      mTenth;                                   // +0x10
    AutoRef  mHolder14;                                // +0x14
    AutoRef  mHolder18;                                // +0x18
    uint32_t pad1c[2];
    Vec3     mPos;                                     // +0x24
    int      mSpot;                                    // +0x30
    float    mRange;                                   // +0x34

    bool FUN_00db0e30(char probe);
    char FUN_00db1030();
};

extern "C" void* g_pProps158128c;                      // 0x0158128c
extern const float g_f169f3b8;
extern const float g_f169f3bc;
extern const float g_f169f3c0;
extern const float g_f13f7670;

struct Container {
    bool __thiscall FUN_00ac7ef0(IRef* owner, IRef* target);   // 0x00ac7ef0, ret 8
    void* __thiscall getContainer();                            // 0x00ac79d0
};
Container* __cdecl FUN_00b3d2b0();                     // 0x00b3d2b0

void  __cdecl FUN_00dac580(EatState* st);              // 0x00dac580
void* __cdecl FUN_00da6270(IRef* a, int b);            // 0x00da6270
float __cdecl GetPropertyT_float(void* props, unsigned id, float def);   // 0x004e1c70
void* __cdecl FUN_00cee4a0(Spatial* v);                // 0x00cee4a0
void* __cdecl FUN_00cee540(Spatial* v, float f);       // 0x00cee540
void* __cdecl FindTool(void* container, float f);      // helper used by 00db0d40

// --- helpers used by the remaining task functions -------------------------
struct Stimuli { uint32_t pad00; float mDuration; };
void* __cdecl FUN_00bc9b00(unsigned id, void* fn, void* a);   // 0x00bc9b00, ret 0xc
void* __cdecl FUN_00bca620(void* self, unsigned id, void* fn, void* a);  // 0x00bca620
void* __cdecl FUN_00bcb0b0(void* self, unsigned id, int n, void* p, const char* name);  // 0x00bcb0b0
void  __cdecl FUN_00bcb480(void* self, void* t, void* c, int a, int b);   // 0x00bcb480
void  __cdecl FUN_00c0b9d0(float f);                    // 0x00c0b9d0
unsigned __cdecl RandomUint32Uniform(unsigned n);       // 0x00a68fb0
void* __cdecl FUN_00d998d0(void* a, unsigned id);      // 0x00d998d0
void  __cdecl FUN_00bc2180(void* a);                    // 0x00bc2180
void  __cdecl TribeModeStrategy_Instance();             // 0x00cd40b0
float __cdecl PlanetModel_DistanceBetweenPoints(const Vec3* a, const Vec3* b);   // 0x00b81470
void  __cdecl GetAny(Stimuli* s);                       // 0x00d997e0
bool  __cdecl F_00dabd10(void* it, void* citizen);      // 0x00dabd10
void  __cdecl RandomUint32UniformAddr();
extern "C" void* g_random1601760;                       // 0x01601760
extern const float g_f13ebc5c;                          // 0x013ebc5c
extern const float g_f13eecd8;                          // 0x013eecd8

float __cdecl FUN_00db0d40(Citizen* c, int, int, int, Stimuli* stim, unsigned char* out);
void __cdecl FUN_00db09c0(Citizen* c, int, int* obj, int, int, EatState* state);
char __cdecl FUN_00db0b80(Citizen* c, int, int, Pool600* pool, int, EatState* state);
void __cdecl FUN_00db0cb0(Citizen* c, int, int, int, int, EatState* state);

// ------------------------------------------------------------------ @ 0x00db0e30
// Per-frame maintenance of the "consumed target" reference, then a distance
// probe that decides whether the order can still be fulfilled.
bool EatState::FUN_00db0e30(char probe)
{
    EatState* st = this;
    Target* tgt = (Target*)st->mHolder14.mp;
    AutoRef* holder = &st->mHolder14;
    bool cleanup = true;

    if (tgt != 0 && tgt->mi128 != 0)
        cleanup = !FUN_00b3d2b0()->FUN_00ac7ef0(st->mOwner, (IRef*)tgt);

    if (cleanup) {
        if (tgt != 0) {
            IRef* o = tgt->mpOwner;
            if (o == st->mOwner && o != 0) {
                tgt->mpOwner = 0;
                o->Release();
            }
        }
        IRef* cur = holder->mp;
        if (cur != 0) {
            holder->mp = 0;
            cur->Release();
        }
    }

    float range = ((Spatial*)((char*)st->mOwner + 0x34))->vf3c();

    if (probe) {
        Target* t = (Target*)holder->mp;
        if (t != 0 && t->mpOwner != st->mOwner && range >= t->mf134)
            FUN_00dac580(st);
    }

    if (holder->mp != 0)
        goto haveTarget;

    if (st->mPos.x == g_f169f3b8 && st->mPos.y == g_f169f3bc && st->mPos.z == g_f169f3c0)
        goto done;

    if (st->mHolderC.mp == 0)
        goto fail;

    if (probe)
        holder->Assign((IRef*)FUN_00cee540((Spatial*)&st->mPos, range));
    else
        holder->Assign((IRef*)FUN_00cee4a0((Spatial*)&st->mPos));

    {
        float prop = GetPropertyT_float(g_pProps158128c, 0x88eae712, g_f13f7670);
        Target* t = (Target*)holder->mp;
        if (t != 0) {
            const Vec3* p = t->mSpatial.GetPosition();
            float dx = p->x - st->mPos.x;
            float dy = p->y - st->mPos.y;
            float dz = p->z - st->mPos.z;
            if (dx * dx + dy * dy + dz * dz > prop * prop)
                goto fail;
        }
    }

    {
        Target* t = (Target*)holder->mp;
        if (t != 0 && probe && t->mpOwner == 0)
            ((AutoRef*)((char*)t + 0x120))->Assign(st->mOwner);
    }
    goto done;

tail:
    {
        Target* t = (Target*)holder->mp;
        if (t != 0 && probe && t->mpOwner == 0)
            ((AutoRef*)((char*)t + 0x120))->Assign(st->mOwner);
    }
    goto done;

haveTarget:
    {
        Target* t = (Target*)holder->mp;
        if (probe && t->mpOwner == 0)
            ((AutoRef*)((char*)t + 0x120))->Assign(st->mOwner);
    }
done:
    return holder->mp != 0;
fail:
    FUN_00dac580(st);
    goto tail;
}

// ------------------------------------------------------------------ @ 0x00db1030
char EatState::FUN_00db1030()
{
    EatState* st = this;
    if (st->mSpot != -1) {
        ((SpotOwner*)st->mHolder18.mp)->FindSpot(0xd, st->mSpot);
        st->mSpot = -1;
        IRef* h = st->mHolder18.mp;
        if (h != 0) {
            st->mHolder18.mp = 0;
            h->Release();
        }
    }

    Target* tgt = (Target*)st->mHolder14.mp;
    if (tgt != 0) {
        IRef* o = tgt->mpOwner;
        if (o == st->mOwner && o != 0) {
            tgt->mpOwner = 0;
            o->Release();
        }
    }
    IRef* cur = st->mHolder14.mp;
    if (cur != 0) {
        st->mHolder14.mp = 0;
        cur->Release();
    }

    if (FUN_00db0e30(1)) {
        st->mPhase = 1;
        return 1;
    }
    return (char)(unsigned)FUN_00da6270(st->mOwner, 0xe);
}

// ------------------------------------------------------------------ @ 0x00db09c0
// Task objective: start locomotion, tell the citizen's base about the order,
// then aim the citizen at the tribe's tool / centre depending on the order.
void __cdecl FUN_00db09c0(Citizen* c, int, int* obj, int, int, EatState* state)
{
    c->UpdateLocomotion(0);
    c->vf84(0, 0, 0);

    if (state->mPhase == 4) {
        c->GetTribe()->FUN_00c97d40(0xd, (IRef*)c);
    } else if (state->mPhase == 5) {
        c->GetTribe()->FindSpot(0xd, state->mSpot);
    } else {
        bool ok = ((Spatial*)((char*)c + 0xc0))->IsBundle();
        if (ok)
            ((SpotOwner*)state->mOwner)->FindSpot(0xd, state->mSpot);
    }

    Pool600* pool = (Pool600*)*(void**)((char*)c->mpAnim + 0x600);
    if (pool != 0) {
        void* anim = c->mpAnim->PlayIdleAnimation(0, 0x80);
        if (anim != 0) {
            for (int i = 0; i < pool->mi18; i++) {
                PoolEntry* e = pool->mpEntries + i;
                if (e->mbActive && e->mpObj != obj) {
                    AnimCtl* src = (AnimCtl*)anim;
                    ((AnimCtl*)((char*)e->mpObj + 0xb4c))->FUN_00bc97f0(
                        0, 0x80, *(float*)((char*)src + 8), *(int*)((char*)src + 0x2c));
                }
            }
            AnimCtl* stopctl = (AnimCtl*)((char*)pool + 0x1a4);
            if (obj == stopctl->FUN_00bc9b10()) {
                TribeModeStrategy_Instance();
                FUN_00bc2180(*(void**)((char*)stopctl + 0x28));
                *(void**)((char*)stopctl + 0x28) = 0;
            }
        }
        if (state->mPhase == 0x12)
            pool->mi1bc -= 1;
        if (pool->mi10 == 1) {
            if (pool->mp1d4 != 0)
                pool->mp1d4->Release();
            if (pool->mp1d0 != 0)
                pool->mp1d0->Release();
        }
        c->mpAnim->FUN_00bcb430();
    }

    if (c->FUN_00c0c120())
        c->SetSprinting(0);

    if (state->mHolder14.mp != 0)
        state->mHolder14.mp->Release();
    if (state->mTenth && ((IRef*)state->mExtra) != 0)
        ((IRef*)state->mExtra)->Release();
    if (state->mHolderC.mp != 0)
        state->mHolderC.mp->Release();
    if (state->mHolder18.mp != 0)
        state->mHolder18.mp->Release();
    if (state->mOwner != 0)
        state->mOwner->Release();
}

// ------------------------------------------------------------------ @ 0x00db0b80
// Task bind: create / fetch the "TribeEat" task object, seed the state block
// from it, play the bind animation and hand the task back to the manager.
char __cdecl FUN_00db0b80(Citizen* c, int, int, Pool600* pool, int, EatState* state)
{
    if (state != 0)
        state->mHolderC.mp = 0;

    void* anim = c->mpAnim->PlayIdleAnimation(8, 0);
    state->mExtra = 0;
    IRef* found = (IRef*)FUN_00d998d0(anim, 0x4ffcdeda);
    if (found != state->mHolderC.mp) {
        if (found != 0)
            found->AddRef();
        state->mHolderC.mp = found;
        IRef* old = state->mHolderC.mp;
        if (old != 0)
            old->Release();
    }

    state->mPhase = 0;
    state->mRange = -1.0f;                       // +0x10 in the original wording
    state->mPhase = -1;
    c->vf84(0, 0, 0);

    if (pool != 0)
        state->mExtra = pool->mi18 != 0 ? (IRef*)1 : 0;

    if (!((Spatial*)((char*)c + 0xc0))->IsBundle()) {
        unsigned r = RandomUint32Uniform(0x14);
        FUN_00c0b9d0((float)r + 20.0f);
    }

    void* task = FUN_00bc9b00(0x67609b9, (void*)F_00dabd10, c);
    void* node = FUN_00bca620(task, 0x67609b9, (void*)F_00dabd10, c);
    if (node == 0) {
        void* t2 = FUN_00bc9b00(0x67609b9, (void*)0x20, (void*)0x18eb4b7);
        node = FUN_00bcb0b0(t2, 0x67609b9, 0x20, (void*)0x18eb4b7, "TribeEat");
        *(int*)((char*)node + 0x1a4) = 0;
    }
    FUN_00bcb480(c->mpAnim, node, c, 0, 0);
    return 1;
}

// ------------------------------------------------------------------ @ 0x00db0cb0
// Post-tick: re-find the spot, clear the "consumed target" and tell the tribe.
void __cdecl FUN_00db0cb0(Citizen* c, int, int, int, int, EatState* state)
{
    c->UpdateLocomotion(0);
    c->FUN_00c25f80();

    c->GetTribe()->FindSpot(0xd, state->mTenth);
    if (state->mPhase != -1)
        c->GetTribe()->FUN_00c97d40(0xd, (IRef*)c);

    c->vf84(0, 0, 0);

    Pool600* pool = (Pool600*)*(void**)((char*)c->mpAnim + 0x600);
    pool->mi1a4 -= 1;
    c->mpAnim->FUN_00bcb430();

    IRef* h = state->mHolderC.mp;
    if (h != 0)
        h->Release();
}

// ------------------------------------------------------------------ @ 0x00db0d40
// Distance probe: if the citizen can reach the target bundle within the
// configured property radius, arm the stimulus and return true.
float __cdecl FUN_00db0d40(Citizen* c, int, int, int, Stimuli* stim, unsigned char* out)
{
    if (!c->FUN_00c0b770())
        return 0.0f;

    if (c->mBundle.BundleQuery() != 0)
        return 0.0f;

    Container* mgr = FUN_00b3d2b0();
    void* container = mgr->getContainer();
    if (container == 0)
        return 0.0f;

    float dist = ((Spatial*)((char*)c + 0x34))->vf3c();
    void* tool = FUN_00cee540((Spatial*)((char*)c + 0xc0), dist);
    Container* mgr2 = FUN_00b3d2b0();
    void* holder = mgr2->getContainer();
    (void)holder;
    void* target = FindTool(tool, dist);
    float prop = GetPropertyT_float(g_pProps158128c, 0x1cd417cf, 0x41c80000);
    if (target == 0)
        return 0.0f;

    void* p1 = FUN_00cee4a0((Spatial*)((char*)c + 0xc0));
    void* p2 = FUN_00cee4a0((Spatial*)((char*)target + 0x34));
    float d = PlanetModel_DistanceBetweenPoints((const Vec3*)p1, (const Vec3*)p2);
    if (d <= prop)
        return 0.0f;

    if (stim != 0)
        GetAny(stim);
    stim->mDuration = dist;
    *out = 1;
    return 1.0f;
}
