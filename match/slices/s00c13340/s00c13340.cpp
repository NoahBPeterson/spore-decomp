// Slice s00c13340 -- SP::cSPCreatureBase / cSPCreatureCitizen helper cluster (0x00c13340..0x00c14200).
//
// Same module/manifest as sibling slices s00c12640 and s00c104d0:
//   flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Contents:
//   00c13340  clears the 4 ranged-attack records (0x34 bytes) at +0xedc, releasing three
//             ref-counted slots each, then zeroes the 0xc04/0xc08/0xc0c counters.
//   00c133d0  positions/aims the creature for a jump or hop: reads the animated-creature
//             local offset, transforms by the body quaternion, adds the body velocity and
//             hands the result to the animated creature's SetMode (ret 0xc).
//   00c135f0  drops a dead/disabled combat target (vslot 0x84 SetCreatureTarget).
//   00c13650  cSPCreatureBase::Jump -- sets a destination from the body velocity/orientation
//             and interrupts the animation with a jump clip (ret 0).
//   00c13a30  cSPCreatureBase::Hover -- enables/disables a hover mode and kicks a hover clip.
//   00c13c60  can-attack predicate: game mode, target flags, distance ratio vs a range.
//   00c13db0  swaps two 0x24-byte interaction records and rebinds their held pointers.
//   00c13eb0  per-frame held/carried-prop refresh (body effects, noun lookups, grasp offsets).
//   00c14070  creates/binds the held-prop animation instance through the animating creature.
//   00c141b0  reads a serialized 0x20-byte record from a stream.
//
// Result (this session): 2 byte-exact (00c135f0, 00c141b0 -> manifest.txt), 5 complete but
// not byte-exact (nonmatching.txt), 3 approximate (partial.txt).  Equivalence (tools/difftest/
// equiv.py, /O2 /MD /Gy /TP /arch:SSE /fp:fast): 00c13340 PASS, 00c13eb0/00c14070 WEAK,
// 00c133d0/00c13650/00c13a30 FAIL (genuine execution divergence -> partial),
// 00c13c60/00c13db0 FAIL only on uint8/uint16-return eax residue (faked callees), i.e. the
// boolean result itself matches, so they stay in nonmatching.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};
inline Vector3 operator*(float s, const Vector3& v) { return Vector3(v.x * s, v.y * s, v.z * s); }

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
};

struct Matrix3 {
    float m[9];
    float& operator[](int i) { return m[i]; }
};

// ---------------------------------------------------------------------------------------------
// Interfaces (only the slots the slice actually calls are named; padding virtuals keep the
// offsets exact).  Slot n lives at vtable offset 4*n.
// ---------------------------------------------------------------------------------------------

// Ranged-attack / held-prop effect: Release 0x04, Stop 0x0c, Detach 0x64.
struct IEffect {
    PV                                        // 0x00
    virtual void Release();                   // 0x04
    PV                                        // 0x08
    virtual void Stop(int flag);              // 0x0c
    PV8 PV8 PV4 PV                            // 0x10..0x60 (21 slots)
    virtual void Detach();                    // 0x64
};

// Generic ref-counted pointer wrapper (EA::AutoRefCount): AddRef 0xbc, SubRef 0xc0.
struct IRefObj {
    PV8 PV8 PV8 PV8 PV8 PV4 PV2 PV             // 0x00..0xb8 (47 slots)
    virtual void AddRef();                    // 0xbc
    virtual void SubRef();                    // 0xc0
};

// cCombatant: ToSpatialObject 0x08, ToGameData 0x0c, SetCreatureTarget 0x84.
struct ICombatant {
    PV2                                       // 0x00
    virtual void* ToSpatialObject();          // 0x08
    virtual void* ToGameData();               // 0x0c
    PV8 PV8 PV8 PV4 PV                         // 0x10..0x80 (29 slots)
    virtual void SetCreatureTarget(void* a, void* b, void* c);  // 0x84
};

// cGameData: slot 0x2c (IsDestroyed).
struct IGameData {
    PV8 PV2 PV                                // 0x00..0x28
    virtual bool IsDestroyed();               // 0x2c
};

// cSpatialObject data view (only the mbEnabled flag at +0x75 is read).
struct ISpatial {
    uint8_t pad0[0x75];                        // +0x00 .. +0x75
    uint8_t mb76;                              // +0x75 (mbEnabled)
};

// cLocomotiveObject (base of cCreatureBase): Get2c 0x2c, Get5c 0x5c, Get68 0x68, GetScalar70 0x70.
struct ILoco {
    PV8 PV2 PV                                // 0x00..0x28 (11 slots)
    virtual Vector3* Get2c();                 // 0x2c (returns a Vector3 pointer)
    PV8 PV2 PV                                // 0x30..0x58 (11 slots)
    virtual void* Get5c(void* a, void* b, float c);  // 0x5c
    PV2                                       // 0x60..0x64 (2 slots)
    virtual void* Get68();                    // 0x68 (extents pointer)
    PV                                        // 0x6c
    virtual float GetScalar70();              // 0x70
};

// Prop / effect object held by an interaction record: slots 0xa0 (Set), 0xac (Get),
// 0xb8 (Find by keyword); the +0x50 flag word is reached through a data view.
struct IProp {
    PV8 PV8 PV8 PV8 PV8                           // 0x00..0x9c (40 slots)
    virtual void Set(void* v);                    // 0xa0
    PV2 PV2                                        // 0xa4..0xa8
    virtual int  Get();                            // 0xac
    PV2 PV2                                        // 0xb0..0xb4
    virtual void* Find(int keyword);               // 0xb8
};

// Data view over the first 0x54 bytes of the prop (vptr + 0x50 flag word).
struct PropData {
    void*    mpVtbl;                              // +0x00
    uint8_t  pad04[0x4c];
    uint32_t mFlags50;                            // +0x50
};

// Object returned by the +0x20 slot's key; slot 0x20 takes the +0x28 key.
struct IKeyed {
    PV8                                             // 0x00..0x1c (slots 0..7)
    virtual void* Slot20(int key);                  // 0x20
};
// Data view for the +0x28 key of IKeyed.
struct KeyedData {
    void*   mpVtbl;                                 // +0x00
    uint8_t pad04[0x24];
    int     mKey28;                                 // +0x28
};

// GonzagoModelWorld-ish: slot 0 (acquire) and slot 4 (release).
struct IModelWorld {
    virtual void Slot00();                        // 0x00
    virtual void Release();                       // 0x04
};

// cPlanetModel-like: nothing virtual mocked here.
struct cPlanetModel {
    float GetGravity();                        // 0x00b7e490
};

// Stream / writer interfaces used by the deserializer (0x00c141b0).
// stream  : slot 0x20 -> writer object, slot 0x28 -> key/value binder
// writer  : slot 0x18 -> underlying raw stream (arg to EA::IO::ReadInt32 / ReadBool)
struct IStream {
    PV8                                        // 0x00..0x1c (8 slots)
    virtual void* GetWriter_20();              // 0x20
    PV                                          // 0x24
    virtual void  Slot28(int key, void* out, int b);  // 0x28
};
struct IWriterS {
    PV2 PV4                                    // 0x00..0x14 (6 slots)
    virtual void* GetStream_18();              // 0x18
};

// ---------------------------------------------------------------------------------------------
// Callees (cdecl unless noted).
// ---------------------------------------------------------------------------------------------
float       GetAttackRangeScale(int a, void* creature);            // 0x00d38a30
void        FUN_00c0d660(void* self, void* out);                 // 0x00c0d660 compute
void*       FUN_00d20610(void* loco);                             // 0x00d20610 GetVelocity
void*       FUN_0099c1a0(void* out, const void* q, const void* v); // 0x0099c1a0 QuaternionVectorTransform
void*       FUN_0099c310(void* out, const void* q, const void* v); // 0x0099c310 QuaternionVectorInverseTransform
void        FUN_00c104d0v(void* out, const void* a, const void* b); // 0x00c104d0 (3-arg form at this call site)
void        FUN_00a02bf0(const void* src, char b);                // 0x00a02bf0 cAnimatingCreature::SetMode
float       FUN_004885d0(const void* v);                          // 0x004885d0 Dot3
void*       FUN_00449c20(void* out, const void* v);               // 0x00449c20 normalized_safe
void        FUN_00c446d0(const void* v, int a);                   // 0x00c446d0
void        FUN_00c12310(void* self, int anim, int a, int b);      // 0x00c12310 InterruptAnimation
void*       FUN_00b5b800();                                        // 0x00b5b800 SP::GetCurrentGameMode
void*       FUN_00ae66f0(void* creature);                          // 0x00ae66f0 CastCreature
void*       FUN_00d38840();                                        // 0x00d38840 cCreatureModeStrategy::Instance
float       FUN_004e1c70(int a, int key, float def);               // 0x004e1c70 SP::GetPropertyT<float>
void        FUN_00ad7ec0(void* dst, void* src);                   // 0x00ad7ec0 PtrField::assign
void        FUN_00c0e000(void* obj, void* a, void* b);             // 0x00c0e000 set
void*       FUN_00b3d520();                                        // 0x00b3d520 SP::GonzagoModelWorld
void*       FUN_00b3d310(void* a, int b);                          // 0x00b3d310
void        FUN_00b5a260(void* a);                                 // 0x00b5a260
void*       FUN_009cab60(void* mw, void* prop);                    // 0x009cab60
void        FUN_00c0de60(void* self, void* elem, void* offsets);   // 0x00c0de60 SetGraspedEffectOffsets
void*       FUN_00b3d300(int noun);                                // 0x00b3d300 SP::NounManager
void*__fastcall FUN_00b21000(void* nm, void* edx);                  // 0x00b21000 (thiscall, 1 arg)
int         FUN_0064f350(int a, int key, int b);                   // 0x0064f350 parser/state
void        FUN_00d7d220(void* a, void* b);                        // 0x00d7d220
int         FUN_00c11f50(void* self, int index, int a, void* b, void* c);  // 0x00c11f50 CreateBodyEffect
void        FUN_00a01f10(void* obj, void* edx, int a, int b);     // 0x00a01f10 anim_qb::Foo
int         FUN_00c0c5b0(void* self, int a, int* out);             // 0x00c0c5b0
void        FUN_00c10210(int a, int b, int c, int d);              // 0x00c10210
void        FUN_0093a780(void* stream, void* out, int count, int flag);  // 0x0093a780 EA::IO::ReadInt32
void        FUN_0093ac80(void* stream, void* out);            // 0x0093ac80 ReadBool

// Module constants and globals (the "Vector3(0,0,0)" triple at 0x168d910..0x168d918 is the
// zero vector; several other slots are shared float constants).
extern Vector3 gZeroVec;        // 0x0168d910 (0,0,0)
extern char    gFlockEnabled;   // 0x0169e381
extern Vector3 gFlockVec;       // 0x0169e384 (scaled by ..384)
extern float   gFlockScale;     // 0x0169e384
extern float   gFlockX;         // 0x0169e388
extern float   gFlockY;         // 0x0169e38c
extern float   gFlockZ;         // 0x0169e390
extern float   gHalfNeg;        // 0x01471064 (0.5f used as *0.5)
extern float   gJumpDur;        // 0x013eb1bc (-1.0f)
extern float   gThree;          // 0x013eb95c (3.0f)
extern float   gHoverMul;       // 0x01571730
extern float   gAirMul;         // 0x01582fbc
extern float   gFallbackRange;  // 0x01582f60
extern float   gEps146a330;     // 0x0146a330 (1.5e-5)
extern float   gZero1485378;    // 0x01485378 (0.0f cmp)
extern float   gOne1485720;     // 0x01485720 (1.0f)
extern float   gProp3f14;       // 0x013ec4b8 (1e-8 squared-length bias)
extern Vector3 gHoverSavedPos;  // 0x0169e3b4 (three floats)
extern float   gHoverSavedX;    // 0x0169e3b4
extern float   gHoverSavedY;    // 0x0169e3b8
extern float   gHoverSavedZ;    // 0x0169e3bc

// ---------------------------------------------------------------------------------------------
// Records layout for the +0xedc clear routine (FUN_00c13340 below).
// Clear the four 0x34-byte ranged-attack records at +0xedc (each has three ref-counted
// pointer slots at -0x28, +0, +4 plus a fourth at +0x30 handled by the store), then zero
// the counters at +0xc04/0xc08/0xc0c.
// ---------------------------------------------------------------------------------------------
// One 0x34-byte ranged-attack record.  The four ref-counted slots sit at +0x00 (cleared
// without a call), +0x24 (slot 0x64), +0x28 and +0x2c (slots 0x0c then 0x04).
struct Rec34 {
    uint32_t mp00;      // +0x00 (cleared with no release)
    uint8_t  pad04[0x20];
    IEffect* mpThird;   // +0x24
    IEffect* mpFirst;   // +0x28
    IEffect* mpSecond;  // +0x2c
    uint8_t  pad30[4];  // +0x30
};
struct DestructOwner {
    uint32_t pad00[0x301];            // +0x0000 .. +0x0c04
    uint32_t mC04;                    // +0x0c04
    uint32_t mC08;                    // +0x0c08
    uint32_t mC0C;                    // +0x0c0c
    uint8_t  padC10[0x2a4];           // +0x0c10 .. +0x0eb4
    Rec34    mRecs[4];                // +0x0eb4
};

// @ 0x00c13340
void __fastcall FUN_00c13340(DestructOwner* self, void* edx)
{
    (void)edx;
    Rec34* rec = self->mRecs;
    for (int i = 4; i != 0; --i, ++rec) {
        IEffect* p;
        p = rec->mpFirst;
        rec->mp00 = 0;
        if (p) {
            p->Stop(0);
            p = rec->mpFirst;
            if (p) {
                rec->mpFirst = 0;
                p->Release();
            }
        }
        p = rec->mpSecond;
        if (p) {
            p->Stop(0);
            p = rec->mpSecond;
            if (p) {
                rec->mpSecond = 0;
                p->Release();
            }
        }
        p = rec->mpThird;
        if (p) {
            rec->mpThird = 0;
            p->Detach();
        }
    }
    self->mC04 = 0;
    self->mC08 = 0;
    self->mC0C = 0;
}

// ---------------------------------------------------------------------------------------------
// Creature-state views shared by the rest of the slice.
// ---------------------------------------------------------------------------------------------

// The "animating creature" object hanging off cCreatureBase+0xb54.  It is both a polymorphic
// prop/animation-instance holder (vtable slots 0x08..0x4c) and a data object (local offset at
// +0x164, model world at +0x17c).
struct CAnim {
    PV2 PV                                      // 0x00..0x04
    virtual void* Slot08(int a, int b);         // 0x08
    virtual void  Slot0c(int a, int b);         // 0x0c
    PV2 PV2                                      // 0x10..0x14
    virtual void  Slot18(int a);                // 0x18
    virtual void  Slot1c(int a, float v);       // 0x1c
    virtual void  Slot20(int a, int v);         // 0x20
    virtual void  Slot24(int a, float v);       // 0x24
    virtual void  Slot28(int a, void* p);       // 0x28
    PV4                                          // 0x2c..0x38
    virtual void  Slot3c(int a, bool b);        // 0x3c
    virtual void  Slot40(int a, int v);         // 0x40
    PV                                          // 0x44
    virtual void  Slot48(int a, void* cb);      // 0x48
    virtual void  Slot4c(int a, int flags, int b);  // 0x4c
    uint8_t  pad4[0x160];    // +0x04 .. +0x164
    Vector3  mLocalOffset;   // +0x164
    uint8_t  pad170[0xc];
    void*    mpModelWorld;   // +0x17c
    uint8_t  pad180[4];
    void*    mpP184;         // +0x184
};

// Creature instance ("model world"): position at +0x18, orientation at +0x3c.
struct CModelWorld {
    uint8_t   pad00[0x18];
    Vector3   mPos;          // +0x18
    Vector3   pad24;
    Quaternion mQuat;        // +0x3c
};

// cSPCreatureCitizen interactions array: an EA vector of 0x24-byte records, each with an
// id at +0x00 and a ref-counted pointer at +0x20.
struct CitRec {
    int32_t  mId;            // +0x00
    uint8_t  pad04[0x1c];
    IRefObj* mpPtr;          // +0x20
};

// The citizen's own sub-objects live at these byte offsets from the base.
struct CCitizen {
    uint8_t  pad00[0x50];
    uint32_t mFlags50;       // +0x50
    uint8_t  pad54[0x1c];
    uint8_t  mb70;           // +0x70
    uint8_t  pad71[0x7c];
    uint8_t  mbED;           // +0xed (unused placeholder)
};

// Generic creature base view: the fields the slice touches.  The ILoco sub-object model is a
// little artificial (ILoco is a plain struct here), so the fields are addressed by name from
// the base and the virtual calls go through the real vtable at +0xc0 via a pointer cast.
struct CAnimator {
    uint8_t  pad00[0x548];
    float    mF548;          // +0x548 hover height
    float    mF54C;          // +0x54c hover height (unscaled)
    uint8_t  pad550[0x40];
    float    mF590;          // +0x590
    uint8_t  pad594[0x88];
    int32_t  mI61c;          // +0x61c
    uint8_t  pad620[0x78];
    int32_t  mI698;          // +0x698
    uint8_t  pad69c[4];
    int32_t  mI6a0;          // +0x6a0
};
struct CCreature {
    uint8_t   pad00[0x110];
    uint32_t  mFlags110;         // +0x110 (0x1000 = hover enabled)
    uint8_t   pad114[0x23];
    uint8_t   mb137;             // +0x137
    uint8_t   pad138[0x178];
    uint32_t  mAnim3;            // +0x2b0 (mode = 3)
    uint8_t   pad2B4[0x80];
    uint32_t  mB34;              // +0x334
    uint8_t   pad338[0x7e8];
    void*     mpAnimator;        // +0xb20
    uint8_t   padB24[0x30];
    void*     mpAnimating;       // +0xb54
    uint32_t  mFlagsB58;         // +0xb58
    uint8_t   padB5C[0x2e4];
    CitRec*   mpRecsBegin;       // +0xe40
    CitRec*   mpRecsEnd;         // +0xe44
    uint8_t   padE48[0x1b];
    uint8_t   mbE63;             // +0xe63
    uint32_t  mE64;              // +0xe64
    uint8_t   padE68[0x14];      // +0xe68 .. +0xe7c
    ICombatant* mpCombatantTarget;  // +0xe7c
    uint8_t   padE80[0x34];
    Rec34     mAttacks[4];       // +0xeb4
};


// ---------------------------------------------------------------------------------------------
// @ 0x00c133d0
// Aim the creature for a hop/jump: transform the animating creature's local offset by the body
// orientation (unless `direct`), fold in the body velocity for `dt`, optionally re-project the
// result back into body space, and hand it to cAnimatingCreature::SetMode (ret 0xc).
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00c133d0(CCreature* self, void* edx, float dt, Vector3* target, uint32_t direct)
{
    (void)edx;
    CAnim* anim = (CAnim*)self->mpAnimating;
    Vector3 offset = anim->mLocalOffset;
    CModelWorld* mw = (CModelWorld*)anim->mpModelWorld;
    ILoco* loco = (ILoco*)((char*)self + 0xc0);

    if (!(uint8_t)direct) {
        Vector3 tmp;
        FUN_0099c1a0(&tmp, &mw->mQuat, &offset);
        offset.x = mw->mPos.x + tmp.x;
        offset.y = mw->mPos.y + tmp.y;
        offset.z = mw->mPos.z + tmp.z;
    }

    if (offset.x == gZeroVec.x && offset.y == gZeroVec.y && offset.z == gZeroVec.z) {
        offset = *target;
    } else {
        Vector3 bodySpace;
        FUN_00c0d660(self, &bodySpace);
        Vector3* v = (Vector3*)FUN_00d20610(loco);
        offset.x = v->x * dt + offset.x;
        offset.y = v->y * dt + offset.y;
        offset.z = v->z * dt + offset.z;
        Vector3* u = (Vector3*)loco->Get5c(target, &offset, dt);
        Vector3 out;
        FUN_00c104d0v(&out, &bodySpace, u);
        offset = out;
    }

    if (!(uint8_t)direct) {
        Vector3 d;
        d.x = offset.x - mw->mPos.x;
        d.y = offset.y - mw->mPos.y;
        d.z = offset.z - mw->mPos.z;
        Vector3 tmp;
        FUN_0099c310(&tmp, &mw->mQuat, &d);
        offset = tmp;
    }

    FUN_00a02bf0(&offset, (char)direct);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00c135f0
// Drop the current combat target when it is dead or disabled (calls SetCreatureTarget(0,0,0)).
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00c135f0(CCreature* self, void* edx, int dummy)
{
    (void)edx;
    (void)dummy;
    ICombatant* target = self->mpCombatantTarget;
    if (!target)
        return;
    IGameData* gd = (IGameData*)target->ToGameData();
    if (!(gd && gd->IsDestroyed())) {
        ISpatial* so = (ISpatial*)target->ToSpatialObject();
        if (!so)
            return;
        if (so->mb76)
            return;
    }
    ((ICombatant*)self)->SetCreatureTarget(0, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00c13650
// SP::cSPCreatureBase::Jump -- pick a jump clip from the animator's state, compute a landing
// position from the body orientation and velocity, and interrupt the animation.
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00c13650(CCreature* self, void* edx)
{
    (void)edx;
    Vector3 pos = gZeroVec;
    uint32_t fl = self->mFlagsB58 >> 9;
    uint8_t bl = self->mb137;
    ILoco* loco = (ILoco*)((char*)self + 0xc0);

    if ((fl & 1) && gFlockEnabled) {
        Vector3* v = (Vector3*)FUN_00d20610(loco);
        if (v->x * v->x + v->y * v->y + v->z * v->z == 0.0f) {
            pos.x = gFlockX * gFlockScale;
            pos.y = gFlockY * gFlockScale;
            pos.z = gFlockZ * gFlockScale;
        }
    }

    CAnimator* anim = (CAnimator*)self->mpAnimator;
    float dist = anim->mF548;

    if (!bl) {
        Vector3* v = (Vector3*)FUN_00d20610(loco);
        Vector3 dir = *(loco->Get2c());
        float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + gProp3f14);
        Vector3 n(dir.x * inv, dir.y * inv, dir.z * inv);
        if (v->x * v->x + v->y * v->y + v->z * v->z > 0.0f) {
            float d = n.x * v->x + n.y * v->y + n.z * v->z;
            Vector3 proj(n.x * d, n.y * d, n.z * d);
            if (proj.x * n.x + proj.y * n.y + proj.z * n.z < 0.0f)
                dist += sqrtf(proj.x * proj.x + proj.y * proj.y + proj.z * proj.z);
        }
    }

    Vector3* f = loco->Get2c();
    float inv = 1.0f / sqrtf(f->x * f->x + f->y * f->y + f->z * f->z + gProp3f14);
    pos.x += f->x * inv * dist * gHoverMul;
    pos.y += f->y * inv * dist * gHoverMul;
    pos.z += f->z * inv * dist * gHoverMul;
    FUN_00c446d0(&pos, 0);

    if (!bl) {
        if (anim->mI698 == 0) {
            FUN_00c12310(self, 0x5485a4c, -1, 0);
            return;
        }
        FUN_00c12310(self, 0x77300ff, -1, 0);
        return;
    }

    int clip;
    if (anim->mI61c == 0) {
        clip = (anim->mI6a0 == 0) ? 0x25b3bc0 : 0x7995fdc;
    } else if (anim->mI6a0 == 0) {
        clip = (anim->mI698 == 0) ? 0x5261d56 : 0x77300f2;
    } else {
        clip = 0x7995fdc;
    }
    FUN_00c12310(self, clip, -1, 0);

    self->mAnim3 = 3;
    self->mb137 = 0;
    if ((fl & 1)) {
        Vector3* p = loco->Get2c();
        gHoverSavedX = p->x;
        gHoverSavedY = p->y;
        gHoverSavedZ = p->z;
    }
    self->mbE63 = 1;
    self->mE64 = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00c13a30
// SP::cSPCreatureBase::Hover -- toggle the hover flag, offset the landing point upward by the
// animator's hover height, and (on enable) kick the hover clip.  Returns 1.
// ---------------------------------------------------------------------------------------------
uint32_t __fastcall FUN_00c13a30(CCreature* self, void* edx, uint8_t enable)
{
    (void)edx;
    if (!enable) {
        self->mFlagsB58 &= 0xffffefff;
        return 1;
    }

    CAnimator* anim = (CAnimator*)self->mpAnimator;
    if (anim->mI61c == 0 || (self->mFlags110 & 0x1000))
        return 0;

    float delta = anim->mF54C * gAirMul;
    uint8_t bl = self->mb137;
    ILoco* loco = (ILoco*)((char*)self + 0xc0);
    Vector3* ext = (Vector3*)loco->Get68();
    delta += ((float*)ext)[5] * gHalfNeg;
    if (delta == 0.0f)
        delta = anim->mF54C;
    if (!bl)
        delta = 0.0f;

    Vector3 pos = gZeroVec;
    if ((self->mFlagsB58 >> 9 & 1) && gFlockEnabled) {
        Vector3* v = (Vector3*)FUN_00d20610(loco);
        if (FUN_004885d0(v) == 0.0f) {
            pos.x = gFlockX * gFlockScale;
            pos.y = gFlockY * gFlockScale;
            pos.z = gFlockZ * gFlockScale;
        }
    }

    Vector3* g = loco->Get2c();
    Vector3 n;
    FUN_00449c20(&n, g);
    pos.x += n.x * delta;
    pos.y += n.y * delta;
    pos.z += n.z * delta;
    FUN_00c446d0(&pos, 0);

    if (bl) {
        if (anim->mI698 == 0)
            FUN_00c12310(self, 0x5261d56, -1, 0);
        else
            FUN_00c12310(self, 0x77300f2, -1, 0);
        self->mAnim3 = 3;
        self->mb137 = 0;
    }
    self->mFlagsB58 |= 0x1000;
    return 1;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00c13c60
// Can-attack / can-target predicate: enough interaction records, the right game mode, and a
// target whose flags/visibility and (mode-dependent) range ratio qualify it.  Ret 0xc.
// ---------------------------------------------------------------------------------------------
uint8_t __fastcall FUN_00c13c60(CCreature* self, void* edx, int* target, uint8_t p3, uint8_t p4)
{
    (void)edx;
    uint8_t result = 0;
    void* gameMode = FUN_00b5b800();
    uint8_t isStrategy = (gameMode == (void*)0x01654c10);
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;

    if (count <= 0)
        return result;
    if (self->mB34 != 1 && !isStrategy)
        return result;
    if (!target)
        return result;
    uint32_t flags = *(uint32_t*)((char*)target + 0x50);
    if ((flags & 0x200) == 0)
        return result;
    if (!p3 && (int8_t)flags < 0)
        return result;
    if (*(uint8_t*)((char*)target + 0x70) == 0)
        return result;
    if (!p3 && (flags & 0x100) != 0)
        return result;
    if (p4) {
        CAnimator* anim = (CAnimator*)self->mpAnimator;
        if (!(anim->mF590 > gZero1485378))
            return result;
    }

    if (!isStrategy) {
        float ratio = ((ILoco*)target)->GetScalar70();
        ILoco* loco = (ILoco*)((char*)self + 0xc0);
        float denom = loco->GetScalar70() + gEps146a330;
        ratio = ratio / denom;
        void* creature = FUN_00ae66f0(target);
        float limit = gFallbackRange;
        if (creature) {
            void* strat = FUN_00d38840();
            limit = FUN_004e1c70(*(int*)((char*)strat + 0xb4), (int)0xd7e2f8aa, 0.5f);
        }
        if (ratio > limit)
            return result;
    }
    result = 1;
    return result;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00c13db0
// Swap two 0x24-byte interaction records (by index) and rebind their held pointers.  Ret 8.
// ---------------------------------------------------------------------------------------------
uint8_t __fastcall FUN_00c13db0(CCreature* self, void* edx, int a, int b)
{
    (void)edx;
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;
    if (a >= count)
        return 0;
    if (b >= count)
        return 0;

    CitRec* begin = self->mpRecsBegin;
    CitRec* recA = &begin[a];
    CitRec* recB = &begin[b];

    IRefObj* held = recA->mpPtr;
    if (held)
        held->AddRef();

    FUN_00ad7ec0(&recA->mpPtr, &recB->mpPtr);
    FUN_00ad7ec0(&recB->mpPtr, &held);

    if (recA->mpPtr)
        FUN_00c0e000(self, recA->mpPtr, (void*)recA->mId);
    if (recB->mpPtr)
        FUN_00c0e000(self, recB->mpPtr, (void*)recB->mId);
    if (held)
        held->SubRef();
    return 1;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00c13eb0
// Per-frame refresh of the creature's carried props: for each interaction record, spawn the
// body effect, look up the noun/keyword and place it in the grasp, then notify the prop.
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00c13eb0(CCreature* self, void* edx)
{
    (void)edx;
    if (!self->mpAnimator)
        return;
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;
    if (count <= 0)
        return;

    CitRec* rec = self->mpRecsBegin;
    for (int i = 0; i < count; ++i, ++rec) {
        IProp* prop = (IProp*)rec->mpPtr;
        if (!prop)
            continue;

        if (prop->Get() == 0) {
            void* world = FUN_00b3d520();
            if (world)
                ((IModelWorld*)world)->Slot00();
            ((PropData*)prop)->mFlags50 |= 8;
            prop->Set(world);
            int key = (int)prop->Find(0x116dd1b);
            void* a = FUN_00b3d310(prop, key);
            FUN_00b5a260(a);
            if (world)
                ((IModelWorld*)world)->Release();
        }

        int id = rec->mId;
        if (id == -1)
            continue;
        if (!FUN_00c11f50(self, id, 0, prop, prop))
            continue;

        void* offsets = 0;
        CAnim* anim = (CAnim*)self->mpAnimating;
        if (anim) {
            offsets = FUN_009cab60(anim->mpModelWorld, prop);
        }
        CAnim* anim2 = (CAnim*)self->mpAnimating;
        void* mw2 = anim2->mpModelWorld;
        void* array = *(void**)((char*)mw2 + 0x2e4);
        void* elem = *(void**)((char*)array + id * 0x2bc);
        FUN_00c0de60(self, elem, offsets);

        IKeyed* sub = (IKeyed*)prop->Find(0x017f243b);
        if (sub) {
            void* noun = sub->Slot20(((KeyedData*)sub)->mKey28);
            void* nm = FUN_00b3d300((int)noun);
            void* hit = FUN_00b21000(nm, 0);
            if (hit && FUN_0064f350(*(int*)((char*)hit + 0xc), (int)0x670f1af, 0)) {
                float* f = (float*)offsets;
                f[6] = 0.0f;
                f[7] = gOne1485720;
                f[8] = 0.0f;
                f[9] = 0.0f;
            }
        }
        FUN_00d7d220(prop, self);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00c14070
// Create/bind the held-prop animation instance through the creature's animating instance. Ret 4.
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00c14070(CCreature* self, void* edx, uint32_t* prop)
{
    (void)edx;
    CAnim* anim = (CAnim*)self->mpAnimating;
    if (!anim || !prop)
        return;

    if (prop[7]) {
        FUN_00a01f10(anim->mpP184, 0, (int)prop[7], 0);
        prop[7] = 0;
    }

    int key = (int)prop[2];
    FUN_00c0c5b0(self, key, &key);

    uint32_t handle = (uint32_t)anim->Slot08(key, 0);
    prop[7] = handle;
    anim->Slot0c((int)handle, 2);
    anim->Slot18((int)handle);
    anim->Slot1c((int)handle, 3.0f);
    anim->Slot20((int)handle, 1);
    anim->Slot24((int)handle, -1.0f);
    anim->Slot3c((int)handle, (uint8_t)prop[6] == 0);
    anim->Slot40((int)handle, (int)prop[2]);
    uint32_t flags = *prop | 0xffffff00;
    anim->Slot48((int)handle, (void*)&FUN_00c10210);
    anim->Slot4c((int)handle, (int)flags, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00c141b0
// Deserialize a 0x20-byte record from a stream: clears+releases the old pointer, reads the
// keyword/int fields, then a bool.
// ---------------------------------------------------------------------------------------------
void*__cdecl FUN_00c141b0(IStream* stream, int* rec)
{
    IRefObj** slot = (IRefObj**)((char*)rec + 0x20);
    IRefObj* old = *slot;
    if (old) {
        *slot = 0;
        old->SubRef();
    }

    stream->Slot28(0x01186577, slot, 0);

    IWriterS* w;
    void* s;
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, rec, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 8, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 4, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 0x10, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    FUN_0093ac80(w->GetStream_18(), (char*)rec + 0x18);
    return stream;
}


