// Slice s00dbf0c0 -- SP::UFO_* space-combat behaviour callbacks / goals
// (0x00dbf0c0..0x00dbffae, 25 functions).
//
// The heart of the slice is SP::UFO_STRAFE_ATTACK_TARGET_Tick (0x00dbfad0, the only
// caller-scored PDB candidate) plus the sibling "is this goal applicable / how well does it
// score" predicates of the UFO goal set.  The behaviour object is the entity itself (`this`)
// with its spatial component nested at +0x34, its own component interface at +0x508, the
// current combat target at +0x68c, the communications target at +0x710 and a `kind` tag at
// +0x714 (3 = planet, 4 = ship, 5/6 = other space object kinds).
//
// The behaviour callbacks are entered through runtime function pointers, so their arguments
// arrive in the /GL (LTCG) register ABI rather than in cdecl stack slots; those are recorded
// in nonmatching.txt.  The small leaves match byte-for-byte.
//
// Compiled with: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int uint32;

float MathSqrt(float v);                              // = sqrtf
float MathSin(float v);                               // = sinf
float MathCos(float v);                               // = cosf

struct Behaviour;

// ---------------------------------------------------------------------------
// A polymorphic spatial node: only the vtable slots used by this slice are named.
// ---------------------------------------------------------------------------
struct Spatial {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual const float* Slot2c();                    // +0x2c  position
};

// The "+0x120 ownership handle" object hung off a target; its +0x2c slot returns a position
// (and takes the two placement flags used by 00dbf3c0).
struct Handle120 {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual const float* Pose(int a, int b);          // +0x2c
};

// The combat object returned by Cast(0xee9b2232): a plain object with the interface helpers
// used by 00dbf710/00dbf760 (c004c0) and the hull value at +0x220.
struct CombatObj {
    char pad000[0x220];
    float mHull;                                      // +0x220
    bool DamageTest(int a);                           // 0x00c004c0
};

// The object stored at +0x68c (a live target): 0x00c38990 tests "still valid/active".
struct TargetObj {
    bool Active(int a);                               // 0x00c38990
};

// The space simulator (SP::GetUFOSimulator): 0x01001700 publishes the tracked object.
struct SimObj {
    void SetTracked(void* e);                         // 0x01001700
};

// The entity's component interface (+0x508 on the behaviour object) and the
// generic "castable object" interface the service objects expose.
// Component lives on a plain "root" interface: slot0 (AddRef), slot1 (Release), then the rest
// of the interface in order.  Cast is at +0x0c.
struct Component {
    virtual void slot00();                            // +0x00  AddRef
    virtual void slot04();                            // +0x04  Release
    virtual void slot08();                            // +0x08
    virtual void* Cast(uint32 typeId);                // +0x0c
    virtual void s10b(); virtual void s14b(); virtual void s18b(); virtual void s1cb();
    virtual void* Slot20();                           // +0x20
    virtual void s24b(); virtual void s28b();
    virtual bool IsReady();                           // +0x2c
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48();
    virtual void* Slot4c();                           // +0x4c
    virtual void  Slot50(void* p);                    // +0x50
    virtual void* Slot54();                           // +0x54
    virtual void  s58(); virtual void s5c();

    // 0x00bfc600 -- bounds/validity check on this component (thiscall)
    bool CheckAlive();
    // 0x00bfc490 -- scalar metric of this component (thiscall)
    float Metric();
};

// The root interface of a service object: slot4c used as a generic getter.
struct ServiceRoot {
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48();
    virtual void* Slot20();                           // +0x20
    virtual void* Slot4c();                           // +0x4c
};

// A star system / planet-side object with a "seti" effects hook (thiscall helpers).
struct SystemObj {
    char pad000[0x64c];
    int mSetiId;                                      // +0x64c
};

// Accessors implemented outside this slice but declared as members so the compiler emits the
// original __thiscall frame (the object in ECX).
struct Behaviour;

// The entity's primary interface: the slot at +0x4c is used by 00dbf1c0 and +0x54 by
// 00dbfad0 to publish / fetch the current target handle.
struct EntityRoot {
    virtual void e00(); virtual void e04(); virtual void e08(); virtual void e0c();
    virtual void e10(); virtual void e14(); virtual void e18(); virtual void e1c();
    virtual void e20(); virtual void e24(); virtual void e28(); virtual void e2c();
    virtual void e30(); virtual void e34(); virtual void e38(); virtual void e3c();
    virtual void e40(); virtual void e44(); virtual void e48();
    virtual void* Slot4c(void* a);                    // +0x4c
    virtual void  Slot50(void* p);                    // +0x50
    virtual void* Slot54();                           // +0x54
};

struct Behaviour : EntityRoot {
    char pad004[0x34 - 0x04];
    Spatial mSpatial;                                 // +0x34  (vtable at +0x34)
    char pad038[0x508 - 0x38];
    Component mSelf;                                  // +0x508 (vtable at +0x508)
    char pad50c[0x624 - 0x50c];
    uint8_t flag624;                                  // +0x624
    char pad625[0x68c - 0x625];
    void* mpTarget;                                   // +0x68c
    uint8_t b690;                                     // +0x690
    uint8_t b691;                                     // +0x691
    char pad692[0x6b4 - 0x692];
    float f6b4;                                       // +0x6b4
    float f6b8;                                       // +0x6b8
    char pad6bc[0x710 - 0x6bc];
    void* mpCommTarget;                               // +0x710
    uint32 kind;                                      // +0x714
    float pos[3];                                     // +0x718
    char pad724[0x748 - 0x724];
    float f748;                                       // +0x748
    int i74c;                                         // +0x74c
    char pad750[0x800 - 0x750];

    // helpers implemented outside the slice (thiscall, hence members)
    Component* GetTargetComponent();                  // 0x00c38b00
    void       ReleaseTargetComponent();              // 0x00c38b10
    Component* GetService();                          // 0x00c38b80
    void       SetOrigin(const float* p);             // 0x00c3be70
    void       SetTarget(void* t);                    // 0x00c3b700
    void       SetAltitude(float v);                  // 0x00c3daa0
};

// The per-behaviour scratch/state block (the "result" block of the tick).
struct BehaviourState {
    float f00;                                        // +0x00  angle accumulator
    float f04;                                        // +0x04  radius scale
    float f08;                                        // +0x08  vertical scale
    int   state;                                      // +0x0c  0 = idle, 3 = running
    float timer;                                      // +0x10
};

// Bits of the `flags` bitmask argument.
#define FLAG_BIT12 0x1000u
#define FLAG_BIT14 0x4000u

// ---------------------------------------------------------------------------
// out-of-slice helpers (real addresses)
// ---------------------------------------------------------------------------
bool   __cdecl f_00c004c0(Component* c, int a);      // 0x00c004c0
bool   __cdecl f_00c38990(Component* c, int a);       // 0x00c38990
bool   __cdecl f_00c37890(Behaviour* o, void* t, int a); // 0x00c37890
void*  __cdecl f_00c389c0(Behaviour* o, int a, int b); // 0x00c389c0
void   __cdecl f_00c3a930(Behaviour* o, void* t, int a); // 0x00c3a930
bool   __cdecl f_00ac0730(void* a, void* b);          // 0x00ac0730
void*  __cdecl f_00cc26a0(float x, float y, float z); // 0x00cc26a0
void*  __cdecl f_00d997e0(void* stimuli);             // 0x00d997e0 behaviour_stimuli::GetAny
void*  __cdecl f_0102c340(Behaviour* o, int a);       // 0x0102c340
void*  __cdecl f_01001700(void* sim, void* e);        // 0x01001700
bool   __cdecl f_0102aa50(void* t, Behaviour* o, bool f); // 0x0102aa50 cSPSpaceCommCanTarget
void*  __cdecl f_0102bc90(Behaviour* o, int a, int b);   // 0x0102bc90 SP::GetBestUFOTarget
void*  __cdecl f_01029940(int kind);                  // 0x01029940 GetSpaceCombatTuning
double __cdecl f_0102a8f0(void* tuning);              // 0x0102a8f0 GetLootMoneyChance2
bool   __cdecl f_01029a10(void* planet, void* record);   // 0x01029a10 IsValidSpaceCommTarget
void*  __cdecl f_01021090();                          // 0x01021090 GetPlayerEmpireID
void*  __cdecl f_010212a0();                          // 0x010212a0 GetActivePlanetRecord
void*  __cdecl f_01021300();                          // 0x01021300 GetPlayerEmpire
void*  __cdecl f_00bddd10(void* sim);                 // 0x00bddd10
void*  __cdecl f_00b3d2a0(uint32 empireId);           // 0x00b3d2a0 SP::StarManager
void*  __cdecl f_00ba9370(void* mgr, uint32 empireId);// 0x00ba9370 cStarManager::GetEmpireByID
void*  __cdecl f_00a206f0();                          // 0x00a206f0 EA::Audio::GetSystemAT
void*  __cdecl f_00435ed0(uint32 setId, void* system); // 0x00435ed0 cSPUISpace::KillSetiEffects
void*  __stdcall f_00b3d350(float* p);                // 0x00b3d350 SP::PlanetModel (callee pops)
namespace SP { struct cPlanetModel { float GetRadiusAt(); }; }  // 0x00b7ef70
void   __cdecl f_00436ce0(const float* src, float* dst);      // 0x00436ce0 Vector3_Normalize
void*  __cdecl f_006985b0(const float* src, float* dst);      // 0x006985b0 SP::OrthogonalVector
void*  __cdecl f_00449c20(const float* src, float* dst);      // 0x00449c20 SP::normalized_safe
void*  __cdecl f_00cc15b0(char* entity, void* calc);  // 0x00cc15b0
void*  __cdecl f_00ffbe50();                          // 0x00ffbe50 SP::GetUFOSimulator
void*  __cdecl f_00ffc320(void* sim);                 // 0x00ffc320
double __cdecl f_009360d0(void* rng);                 // 0x009360d0 RandomDoubleUniform

struct Rng { double Uniform(); };
extern Rng g_1601760;                                 // 0x01601760

extern int g_169f754;                                 // 0x0169f754 k_placeembassy_0169f754

// ---------------------------------------------------------------------------
// 00DBF0C0 -- reset the behaviour's animation scales; drop the target if it is gone.
// ---------------------------------------------------------------------------
// @ 0x00DBF0C0
void f_00dbf0c0(Behaviour* self) {
    Component* c = self->GetTargetComponent();
    if (c != 0) {
        if (!c->IsReady())
            self->ReleaseTargetComponent();
    }
    self->f6b4 = 1.0f;
    self->f6b8 = 1.0f;
}

// @ 0x00DBF100
bool f_00dbf100(Behaviour* self) {
    self->ReleaseTargetComponent();
    return false;
}

// @ 0x00DBF110
bool f_00dbf110(Behaviour* self) {
    if (!self->mSelf.CheckAlive())
        return false;
    self->SetOrigin(&self->pos[0]);
    return true;
}

// @ 0x00DBF140
bool f_00dbf140(Behaviour* self, int a1, int a2, int a3, int a4, int a5, int a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5;
    if (a6 != 0)
        self->SetTarget(*(void**)(a6 + 8));
    return false;
}

// @ 0x00DBF160
void f_00dbf160(Behaviour* self) {
    self->f6b4 = 1.0f;
    self->f6b8 = 1.0f;
    self->b690 = 0;
    self->b691 = 0;
    self->SetOrigin(&self->pos[0]);
    self->SetTarget(0);
    self->mSelf.Slot50(0);
}

// @ 0x00DBF1C0
bool f_00dbf1c0(Behaviour* self) {
    if (self->kind == 3) {
        void* e = self->Slot4c(0);
        ((SimObj*)f_00ffbe50())->SetTracked(e);
    }
    return true;
}

// @ 0x00DBF1F0
bool f_00dbf1f0(Behaviour* self) {
    f_0102c340(self, 0);
    return true;
}

// @ 0x00DBF210
bool f_00dbf210(Behaviour* self, int a1, int a2, int a3, int a4, BehaviourState* out) {
    (void)self; (void)a1; (void)a2; (void)a3; (void)a4;
    out->f00 = 2.5f;
    *(unsigned char*)&out->f04 = 0;
    *(uint32*)&out->f08 = 0;
    return true;
}

// ---------------------------------------------------------------------------
// Ordering predicate shared by 00dbf230: compares the +0x120 "priority handle" of two
// objects.  The comparator object itself is a by-value argument of 00dbf230, which is why
// the original passes a pointer to its own argument slot in ECX.
// ---------------------------------------------------------------------------
struct HandleLess {
    char pad[0x120];
};
struct Comparator {
    bool Less(const HandleLess* a, const HandleLess* b);   // 0x00ac0730
};
static inline const HandleLess* prio(const void* p) {
    return p ? (const HandleLess*)((const char*)p + 0x120) : 0;
}

// 00DBF230 -- pick the smallest of three objects by their priority handle.
// @ 0x00DBF230
void* f_00dbf230(const void* a1, const void* a2, const void* a3, Comparator cmp) {
    if (cmp.Less(prio(a1), prio(a2))) {
        if (!cmp.Less(prio(a2), prio(a3)))
            return cmp.Less(prio(a1), prio(a3)) ? (void*)a3 : (void*)a1;
        return (void*)a2;
    }
    if (cmp.Less(prio(a1), prio(a3)))
        return (void*)a1;
    if (cmp.Less(prio(a2), prio(a3)))
        return (void*)a3;
    return (void*)a2;
}

// 00DBF340 -- true when the behaviour's combat target still resolves and is ready.
// @ 0x00DBF340
float f_00dbf340(Behaviour* self) {
    Component* c = self->GetTargetComponent();
    if (c != 0) {
        Component* t = (Component*)c->Cast(0xb033b403);
        if (t != 0) {
            if (t->IsReady()) {
                self->ReleaseTargetComponent();
                return 0.0f;
            }
            if (t->IsReady())
                return 0.0f;
            return 1.0f;
        }
    }
    return 0.0f;
}
// 00DBF390 (leaf inside the same region) -- true when the +0xee9b2232 interface resolves.
float f_00dbf390(Behaviour* self) {
    Component* c = self->GetTargetComponent();
    if (c == 0)
        return 0.0f;
    if (c->Cast(0xee9b2232) == 0)
        return 0.0f;
    return 1.0f;
}

// ---------------------------------------------------------------------------
// 00DBF3C0 -- "attack target" applicability: the best UFO target must be within 1000.
// ---------------------------------------------------------------------------
// @ 0x00DBF3C0
float f_00dbf3c0(Behaviour* self, int a2, int a3, uint32 flags, void* stimuli, uint8_t* out) {
    (void)a2; (void)a3;
    Component* c = self->GetTargetComponent();
    if (c == 0)
        return 0.0f;
    void* obj = c->Cast(0xee9b2232);
    if (obj == 0)
        return 0.0f;

    Handle120* h = (Handle120*)((char*)obj + 0x120);
    const float* mine = h->Pose((flags >> 12) & 1, (flags >> 14) & 1);
    void* target = f_00cc26a0(mine[0], mine[1], mine[2]);
    if (target == 0)
        return 0.0f;

    const float* theirs = ((Spatial*)((char*)target + 0x34))->Slot2c();
    float dx = theirs[0] - mine[0];
    float dy = theirs[1] - mine[1];
    float dz = theirs[2] - mine[2];
    if (MathSqrt(dx * dx + dy * dy + dz * dz) < 1000.0f) {
        if (stimuli != 0)
            f_00d997e0(stimuli);
        *(void**)((char*)stimuli + 4) = (char*)target + 0x508;
        *out = 1;
        return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 00DBF4B0 -- "strafe attack target" applicability for the whole entity.
// ---------------------------------------------------------------------------
// @ 0x00DBF4B0
float f_00dbf4b0(Behaviour* self, int a2, int a3, uint32 flags, void* stimuli, uint8_t* out) {
    (void)a2; (void)a3;
    int bit = (flags & FLAG_BIT12) != 0;
    void* target = (void*)f_0102bc90(self, bit, 0);   /* returns the chosen object */

    float range = 1000.0f;
    if (self->kind == 5)
        range = 230.0f;

    if (target != 0) {
        const float* tpos = ((Spatial*)((char*)target + 8))->Slot2c();
        const float* mpos = self->mSpatial.Slot2c();
        float dx = tpos[0] - mpos[0];
        float dy = tpos[1] - mpos[1];
        float dz = tpos[2] - mpos[2];
        if (MathSqrt(dx * dx + dy * dy + dz * dz) < range) {
            if (stimuli != 0)
                f_00d997e0(stimuli);
            *(void**)((char*)stimuli + 4) = target;
            *out = 1;
            return 1.0f;
        }
    }

    if (self->mpCommTarget != 0) {
        if (f_0102aa50(self->mpCommTarget, self, bit)) {
            if (stimuli != 0)
                f_00d997e0(stimuli);
            void* t = self->mpCommTarget;
            *(void**)((char*)stimuli + 4) = t ? (char*)t + 0x508 : 0;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 00DBF5E0 -- same, but only while the current target is a ship (kind 4).
// ---------------------------------------------------------------------------
// @ 0x00DBF5E0
float f_00dbf5e0(Behaviour* self, int a2, int a3, uint32 flags, void* stimuli, uint8_t* out) {
    (void)a2; (void)a3;
    if (self->mpTarget == 0 || ((Behaviour*)self->mpTarget)->kind != 4)
        return 0.0f;

    int bit = (flags & FLAG_BIT12) != 0;
    void* target = (void*)f_0102bc90(self, bit, 0);

    if (target != 0) {
        Behaviour* owner = (Behaviour*)self->mpTarget;
        const float* tpos = ((Spatial*)((char*)target + 8))->Slot2c();
        const float* mpos = owner->mSpatial.Slot2c();
        float dx = tpos[0] - mpos[0];
        float dy = tpos[1] - mpos[1];
        float dz = tpos[2] - mpos[2];
        if (MathSqrt(dx * dx + dy * dy + dz * dz) < 230.0f) {
            if (stimuli != 0)
                f_00d997e0(stimuli);
            *(void**)((char*)stimuli + 4) = target;
            *out = 1;
            return 1.0f;
        }
    }

    void* comm = ((Behaviour*)self->mpTarget)->mpCommTarget;
    if (comm != 0) {
        if (f_0102aa50(comm, self, bit)) {
            if (stimuli != 0)
                f_00d997e0(stimuli);
            void* t = ((Behaviour*)self->mpTarget)->mpCommTarget;
            *(void**)((char*)stimuli + 4) = t ? (char*)t + 0x508 : 0;
            *out = 1;
            return 1.0f;
        }
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 00DBF710 -- true while the target is undamaged.
// @ 0x00DBF710
float f_00dbf710(Behaviour* self) {
    Component* c = self->GetTargetComponent();
    if (c != 0) {
        CombatObj* o = (CombatObj*)c->Cast(0xee9b2232);
        if (o != 0) {
            if (o->DamageTest(0) || o->mHull > 0.0f)
                return 1.0f;
        }
    }
    return 0.0f;
}

// 00DBF760 -- the negation of the above (the "not damaged" guard).
// @ 0x00DBF760
float f_00dbf760(Behaviour* self) {
    Component* c = self->GetTargetComponent();
    if (c != 0) {
        CombatObj* o = (CombatObj*)c->Cast(0xee9b2232);
        if (o != 0) {
            if (o->DamageTest(0) || 0.0f < o->mHull)
                return 0.0f;
        }
    }
    return 1.0f;
}

// ---------------------------------------------------------------------------
// 00DBF7B0 -- random "keep strafing" gate for non-planet kinds.
// ---------------------------------------------------------------------------
// @ 0x00DBF7B0
float f_00dbf7b0(Behaviour* self) {
    if (self->kind != 4) {
        if (self->mSelf.Metric() <= 0.2f) {
            if (g_1601760.Uniform() < 0.85f)
                return 1.0f;
        }
    }
    return 0.0f;
}
// @ 0x00DBF810
float f_00dbf810(Behaviour* self) {
    return self->mpTarget == 0 ? 1.0f : 0.0f;
}

// @ 0x00DBF840
float f_00dbf840(Behaviour* self) {
    if (self->mpTarget != 0) {
        if (((TargetObj*)self->mpTarget)->Active(1))
            return 0.0f;
    }
    if (self->mpTarget != 0)
        return 1.0f;
    return 0.0f;
}

// @ 0x00DBF890
float f_00dbf890(Behaviour* self) {
    void* t = self->mpTarget;
    if (t != 0) {
        if (((Behaviour*)t)->kind == 4)
            return 1.0f;
    }
    return 0.0f;
}

// 00DBF8B0 -- true in a place (embassy) system.
// @ 0x00DBF8B0
float f_00dbf8b0(Behaviour* self) {
    Component* c = self->GetService();
    if (c != 0) {
        void* o = c->Cast(0x4e3faaf);
        if (o != 0 && *(int*)((char*)o + 0x64c) == g_169f754)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00DBF8F0
float f_00dbf8f0(Behaviour* self, int a2, int a3, uint32 flags) {
    (void)a2; (void)a3;
    void* t = self->mpTarget;
    if (t != 0) {
        if (f_0102aa50(t, self, (flags & FLAG_BIT12) != 0))
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00DBF9A0
float f_00dbf9a0(Behaviour* self) {
    void* t = self->mpTarget;
    if (t != 0) {
        if (((Behaviour*)t)->kind == 0)
            return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 00DBF9C0 -- centre position + orbit parameters for the current kind.
// ---------------------------------------------------------------------------
// @ 0x00DBF9C0
bool f_00dbf9c0(Behaviour* self, int a2, int a3, int a4, int a5, BehaviourState* out) {
    (void)a2; (void)a3; (void)a4; (void)a5;
    out->f00 = 0.0f;
    out->state = 0;
    out->timer = 0.0f;

    const float* centre;
    Component* c = self->GetService();
    if (c != 0) {
        void* o = c->Cast(0x1186577);
        if (o != 0)
            centre = ((Spatial*)o)->Slot2c();
        else
            centre = &self->pos[0];
    } else {
        centre = &self->pos[0];
    }

    float p[3];
    p[0] = centre[0];
    p[1] = centre[1];
    p[2] = centre[2];

    void* pm = f_00b3d350(p);
    float r = ((SP::cPlanetModel*)pm)->GetRadiusAt();
    self->SetAltitude(r + 55.0f);

    switch (self->kind) {
    case 3:
        out->f04 = 4.0f;
        out->f08 = 50.0f;
        break;
    case 4:
        out->f04 = 12.0f;
        out->f08 = 90.0f;
        break;
    case 6:
        out->f04 = 6.0f;
        out->f08 = 70.0f;
        break;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 00DBFAD0 -- SP::UFO_STRAFE_ATTACK_TARGET_Tick
//
// The tick either runs the approach phase (entity kind 4 and state 3: count down the
// re-evaluation timer, then hand the target to the shot handler) or updates the orbit:
// advance the angle, keep the entity at the orbit radius around the planet, and publish
// the resulting target handle on the component interface.
// ---------------------------------------------------------------------------
static inline float MathSqrt(float v) { return v < 0.0f ? 0.0f : v; }

// @ 0x00DBFAD0
bool f_00dbfad0(Behaviour* self, int a2, int a3, uint32 flags, BehaviourState* s,
                int a6, int a7, float dTimer, float dAngle, int a10) {
    (void)a2; (void)a3; (void)a6; (void)a7; (void)a10;

    if (self->kind == 4) {
        void* best = (void*)f_0102bc90(self, (flags & FLAG_BIT12) != 0, 0);

        if (s->state == 0) {
            if (f_00c37890(self, best, 3)) {
                s->timer = 0.0f;
                s->state = 3;
                f_00c389c0(self, 8, 1);
            }
        }

        if (s->state == 3) {
            s->timer = s->timer + dTimer;
            void* tuning = f_01029940(self->kind);
            double chance = f_0102a8f0(tuning);
            if (s->timer >= (float)chance) {
                f_00c3a930(self, best, 3);
                s->timer = 0.0f;
                s->state = 0;
                return true;
            }
            self->mSelf.Slot50(0);
            return true;
        }
    }

    /* ---- keep-updating phase ---- */
    int empireId = 0;
    (void)empireId;

    if (self->kind == 3)
        empireId = (int)f_01021090();
    else
        empireId = (int)((Component*)self)->Slot4c();

    Component* svc = self->GetService();
    if (svc == 0)
        return false;

    void* planet = svc->Cast(0x1186577);
    void* place = svc->Cast(0x4e3faaf);
    void* ship = svc->Cast(0xee9b2232);
    if (svc->IsReady())
        return false;

    if (self->kind == 3) {
        if (ship == 0)
            return false;
        void* sim = f_00ffbe50();
        if (ship != f_00ffc320(sim))
            return false;
    }

    if (ship != 0) {
        void* record = f_010212a0();
        if (f_01029a10(planet, record) && ((Behaviour*)ship)->i74c == empireId
            && ((Behaviour*)ship)->f748 >= 100.0f)
            return false;
    }

    s->f00 = s->f00 + dAngle;

    const float* planetPos = ((Spatial*)planet)->Slot2c();

    float dir[3];
    f_00436ce0(planetPos, dir);

    float phase = -((s->f00 * 1.0f) / (s->f04 * 2.2f));

    float orth[3];
    f_006985b0(dir, orth);
    f_00436ce0(orth, orth);

    /* cross = orth x dir, then normalized */
    float cr[3];
    cr[0] = orth[1] * dir[2] - orth[2] * dir[1];
    cr[1] = orth[2] * dir[0] - orth[0] * dir[2];
    cr[2] = orth[0] * dir[1] - orth[1] * dir[0];

    float side[3];
    f_00449c20(cr, side);

    float sn = MathSin(phase * 2.2f) * s->f08;
    float cs = MathCos(phase);

    float off[3];
    off[0] = dir[0] * sn + orth[0] * cs;
    off[1] = dir[1] * sn + orth[1] * cs;
    off[2] = dir[2] * sn + orth[2] * cs;

    const float* here = self->mSpatial.Slot2c();
    float p[3];
    p[0] = here[0] + off[0];
    p[1] = here[1] + off[1];
    p[2] = here[2] + off[2];
    self->SetOrigin(p);

    self->flag624 = 1;

    void* handle;
    if (ship != 0) {
        handle = (void*)f_00cc15b0((char*)ship, self->mSelf.Slot54());
    } else {
        handle = place != 0 ? (char*)place + 0x508 : 0;
    }
    self->mSelf.Slot50(handle);
    return true;
}

// ---------------------------------------------------------------------------
// 00DBFE80 -- switch the tracked combat target to the best available one.
// ---------------------------------------------------------------------------
static const uint32 kSetiByType[9] = {
    0xef2fc9e8u, 0x94a77229u, 0xe4129110u, 0x6139d767u, 0x6263b501u,
    0x367a1940u, 0x62d3be51u, 0x0199e701u, 0x7aa79140u,
};

// @ 0x00DBFE80
bool f_00dbfe80(Behaviour* self) {
    void* sim = f_00ffbe50();
    void* ufo = f_00bddd10(sim);
    void* best;
    if (ufo == 0)
        best = 0;
    else
        best = ((Component*)ufo)->Cast(0xb033b403);

    sim = f_00ffbe50();
    void* player = f_00ffc320(sim);

    Component* svc = self->GetService();
    uint32 empireId = (uint32)((Component*)self)->Slot4c();

    void* mgr = f_00b3d2a0(empireId);
    void* empire = f_00ba9370(mgr, empireId);
    if (empire != 0) {
        int t = *(int*)((char*)empire + 0x58);
        uint32 setId;
        if ((unsigned)t <= 8)
            setId = kSetiByType[t];
        else
            setId = (void*)empire == f_01021300() ? 0xea351526u : 0u;

        void* aud = f_00a206f0();
        void* audSys = 0;
        if (aud != 0)
            audSys = ((Component*)aud)->Slot20();
        f_00435ed0(setId, audSys);
    }

    if (best != 0) {
        void* old = self->mpTarget;
        if (best != old) {
            ((Component*)best)->slot00();
            self->mpTarget = best;
            if (old != 0)
                ((Component*)old)->slot04();
        }
        return true;
    }
    if (player != 0) {
        self->SetTarget(player);
        return true;
    }
    (void)svc;
    return false;
}
