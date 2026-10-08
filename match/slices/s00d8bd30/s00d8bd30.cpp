// Slice s00d8bd30 -- creature behavior tree: SP::CAN_EAT_FRUIT_Decide (PDB candidate name).
// Returns 1.0 when the creature should eat fruit (an idle animation already targets a free fruit, a held fruit
// exists, a fruit in range is free, or a fruit reachable on the planet surface was found and claimed through the
// stimulus set), 0.0 otherwise. cdecl, float result in st0.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (creature AI module; no /EHsc)
#include "types.h"

// ---------------------------------------------------------------- math
struct Vector3 { float x, y, z; };                    // POD: struct copies use integer registers
struct Matrix3 { float m[9]; };                       // POD
struct Matrix3c {                                     // copy through movss
    float m[9];
    Matrix3c() {}
    Matrix3c(const Matrix3c& o) {
        m[0] = o.m[0]; m[1] = o.m[1]; m[2] = o.m[2];
        m[3] = o.m[3]; m[4] = o.m[4]; m[5] = o.m[5];
        m[6] = o.m[6]; m[7] = o.m[7]; m[8] = o.m[8];
    }
};
struct Quat { float x, y, z, w; };
struct BBox { float minx, miny, minz, maxx, maxy, maxz; };

extern const Matrix3c kMatrix3Identity;               // 0169f08c
extern const float kAvatarRange;                      // 01582e0c  (50.0)
extern const float kHeightScale;                      // 01447a20  (1.75)

struct cSPTransform {                                 // 0x38 bytes
    uint16_t mFlags;                                  // +0x00
    uint16_t mModificationCount;                      // +0x02
    Vector3 mTranslation;                             // +0x04
    float mScale;                                     // +0x10
    Matrix3 mRotation;                                // +0x14
};

#define VPAD(n) virtual void vpad##n()

// Secondary base at +0xc0 of the creature (locomotion / spatial interface).
struct cLocomotive {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual Vector3* GetPosition();                   // +0x2c
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20); VPAD(21);
    virtual bool IsMovingFast();                      // +0x58
    VPAD(23); VPAD(24); VPAD(25);
    virtual BBox* GetBounds();                        // +0x68
};

// A target entity as seen through the idle-animation / cast helpers.
struct cTarget {
    uint32_t pad00[0x84 / 4];
    uint32_t mFlags84;                                // +0x84
    uint32_t pad88[(0x108 - 0x88) / 4];
    void* mpHolder;                                   // +0x108
    uint32_t pad10c[(0x16c - 0x10c) / 4];
    int mKind;                                        // +0x16c
};

struct cSpatial34 {                                   // sub-object at +0x34 of a fruit
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual Vector3* GetPosition();                   // +0x2c
};
struct cFruitObj {                                    // record of the first list (rec->mpObj)
    uint32_t pad00[0x34 / 4];
    cSpatial34 mSpatial;                              // +0x34
    uint32_t pad38[(0x108 - 0x38) / 4];
    void* mpHolder;                                   // +0x108
};
struct cFruitRec1 { uint32_t pad00; uint8_t mEnabled; uint8_t pad05[3]; cFruitObj* mpObj; };   // +0x04 / +0x08

// Held-object list entry (vtable slot 0xb8 casts it to a target)
struct cHeld {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29); VPAD(30);
    VPAD(31); VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39); VPAD(40);
    VPAD(41); VPAD(42); VPAD(43); VPAD(44); VPAD(45);
    virtual cTarget* CastTarget(uint32_t id);         // +0xb8
};

struct cGridCell {                                    // returned by cGrid::GetCell(x, y, z) (FUN_00b04c20)
    uint32_t pad00[0x48 / 4];
    uint32_t mMaskLo;                                 // +0x48
    uint32_t mMaskHi;                                 // +0x4c
};
struct cGrid { cGridCell* GetCell(uint32_t x, uint32_t y, uint32_t z); };      // 00b04c20 (ret 0xc; float bits passed as dwords)

struct cFruitObj2 {                                   // record of the second list (rec->mpObj)
    uint32_t pad00[0x4c / 4];
    Vector3 mPos;                                     // +0x4c
    uint32_t pad58[(0xa0 - 0x58) / 4];
    void* mpHolder;                                   // +0xa0
    uint32_t GetSlotCount();                          // 00b05980 (unsigned; 0 = none)
    uint32_t GetPointCount();                         // 00b058f0
    Vector3* GetPoint(Vector3* out, uint32_t i);      // 00b05a00 (ret 8)
};
struct cFruitRec2 { uint32_t pad00; uint8_t mEnabled; uint8_t pad05[3]; uint32_t pad08; cFruitObj2* mpObj; };   // +0x04 / +0x0c

struct cPlanetModel {
    Vector3* DirectionToSurfacePosition(Vector3* out, const Vector3* dir);   // 00b815a0 (ret 8)
    Quat* BuildSurfaceOrientation(Quat* out, const Vector3* pos);            // 00b7f190 (ret 8)
};

struct cStim { uint32_t pad00[3]; int mIndex; };      // +0x0c
struct cStimSet {                                     // behavior stimuli at creature+0xb4c -> +8
    void* PlayIdleAnimation(uint32_t a, uint32_t b);                  // 00bc96a0 (ret 8)
    cStim* Play(int type, int a, float prio, void* target);          // 00bc97f0 (ret 0x10)
};

struct cBodyStatus { uint32_t pad[0x590 / 4]; float mValue; };         // +0x590

struct cNounManager;
struct cAvatar { uint32_t pad[0xc0 / 4]; cLocomotive mLoco; };         // +0xc0
struct cGameNounManager { cAvatar* GetAvatar(); };                    // 00b1fdb0

struct cPred { bool Test(cFruitRec1* r); };                           // 00c034d0 (thiscall functor, ret 4)
struct FilterIter {
    cFruitRec1** cur;
    cFruitRec1** end;
    cPred pred;
    void SkipToValid() { while (cur != end && !pred.Test(*cur)) ++cur; }
};

struct cCreature {
    uint32_t pad00[0xc0 / 4];
    cLocomotive mLoco;                                // +0xc0 (polymorphic base subobject: pad covers vptr slot)
    uint32_t pad_c4[(0xb20 - 0xc4) / 4];
    cBodyStatus* mpStatus;                            // +0xb20
    uint32_t padb24[(0xb34 - 0xb24) / 4];
    int mMode;                                        // +0xb34
    uint32_t padb38[(0xb4c - 0xb38) / 4];
    void* mpBehavior;                                 // +0xb4c
    uint32_t padb50[(0xb58 - 0xb50) / 4];
    uint32_t mFlagsB58;                               // +0xb58
    uint32_t padb5c[(0xe40 - 0xb5c) / 4];
    uint32_t pade40[(0xf90 - 0xe40) / 4];
    uint8_t mbF90;                                    // +0xf90
    uint8_t padf91[3];
    uint32_t padf94[(0x108c - 0xf94) / 4];
    cFruitRec2** mpRecs2Begin;                        // +0x108c
    cFruitRec2** mpRecs2End;                          // +0x1090
    uint32_t pad1094[(0x133c - 0x1094) / 4];
    cFruitRec1** mpRecs1Begin;                        // +0x133c
    cFruitRec1** mpRecs1End;                          // +0x1340

    uint32_t GetHeldCount();                          // 00c0f4f0
    cHeld* GetHeld(uint32_t i);                       // 00c0f8a0 (ret 4)
    void MoveHeldToFront(uint32_t i, int b);          // 00c13db0 (ret 8)
    bool IsBusyMode();                                // 00c0b770 (mode == 1)
    bool CanReachPointWithBodyPart(cSPTransform* t, const Vector3* pt, int part, int a, int b, int c, float tol);   // 00c175d0 (ret 0x1c)
};

// ---------------------------------------------------------------- free helpers
cTarget* FUN_00d998d0(void* idle, uint32_t id);        // 00d998d0 (cdecl cast)
cNounManager* NounManager();                           // 00b3d300 -> really cGameNounManager*
cPlanetModel* PlanetModel();                           // 00b3d350
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quat* q);   // 0059c190
cGrid* FUN_00b3d440();                                 // 00b3d440

static inline cStimSet* Stim(cCreature* c) { return (cStimSet*)((char*)c->mpBehavior + 8); }

// @ 0x00d8bd30
float __cdecl Decide(cCreature* c, int p2, int p3, uint32_t flags)
{
    void* idle = Stim(c)->PlayIdleAnimation(1, 0);
    if (idle) {
        cTarget* t = FUN_00d998d0(idle, 0x2c9cc8e);
        if (t) {
            int k = t->mKind;
            if (k == 0 || k == 2 || k == 3) {
                if (t->mpHolder == 0 || t->mpHolder == c) {
                    if ((t->mFlags84 & 0x10) == 0)
                        return 1.0f;
                }
            }
        }
    }
    if ((flags & 0x180000) == 0 || (!c->mbF90 && !c->mLoco.IsMovingFast()))
        return 0.0f;

    // (1) fruit currently held by the creature
    uint32_t n = c->GetHeldCount();
    for (uint32_t i = 0; i < n; ++i) {
        cHeld* h = c->GetHeld(i);
        if (h) {
            cTarget* t = h->CastTarget(0x2c9cc8e);
            if (t && t->mKind == 3 && t->mpHolder == c) {
                if (i != 0)
                    c->MoveHeldToFront(i, 0);
                Stim(c)->Play(1, 0, 15.0f, t);
                return 1.0f;
            }
        }
    }

    // (2) first list: registered fruit records (filter iterator: the predicate member sits next to the cursor)
    FilterIter fi;
    fi.cur = c->mpRecs1Begin;
    fi.end = c->mpRecs1End;
    for (fi.SkipToValid(); fi.cur != fi.end; ++fi.cur, fi.SkipToValid()) {
        cFruitRec1* r = *fi.cur;
        if (r->mEnabled) {
            cFruitObj* o = r->mpObj;
            bool near = true;
            if ((c->mFlagsB58 >> 8) & 1) {
                Vector3* p = o->mSpatial.GetPosition();
                cAvatar* av = ((cGameNounManager*)NounManager())->GetAvatar();
                Vector3* a = av->mLoco.GetPosition();
                float dx = a->x - p->x, dy = a->y - p->y, dz = a->z - p->z;
                near = kAvatarRange * kAvatarRange > dx * dx + dy * dy + dz * dz;
            }
            if (near) {
                if (o->mpHolder == 0 || o->mpHolder == c) {
                    Stim(c)->Play(1, 0, 15.0f, o);
                    return 1.0f;
                }
            }
        }
    }

    // (3) second list: fruit on the planet surface
    {
        cPlanetModel* pm = PlanetModel();
        cFruitRec2** rb = c->mpRecs2Begin;
        cFruitRec2** re = c->mpRecs2End;
        for (; rb != re; ++rb) {
            cFruitRec2* r = *rb;
            if (!r->mEnabled)
                continue;
            cFruitObj2* o = r->mpObj;
            if (o->GetSlotCount() == 0)
                continue;
            if (o->mpHolder != 0 && o->mpHolder != c)
                continue;
            cGridCell* cell = FUN_00b3d440()->GetCell(((uint32_t*)&o->mPos)[0], ((uint32_t*)&o->mPos)[1], ((uint32_t*)&o->mPos)[2]);
            uint32_t cnt = o->GetPointCount();
            if (cell == 0)
                continue;
            for (uint32_t i = 0; i < cnt; ++i) {
                Vector3 pt;
                o->GetPoint(&pt, i);
                uint64_t bit = (uint64_t)1 << i;
                if ((((uint32_t)bit & cell->mMaskLo) | ((uint32_t)(bit >> 32) & cell->mMaskHi)) == 0)
                    continue;
                if ((c->mFlagsB58 >> 8) & 1) {
                    cAvatar* av = ((cGameNounManager*)NounManager())->GetAvatar();
                    Vector3* a = av->mLoco.GetPosition();
                    float dz = a->z - pt.z, dy = a->y - pt.y, dx = a->x - pt.x;
                    if (!(kAvatarRange * kAvatarRange > dz * dz + dy * dy + dx * dx))
                        continue;
                }
                Vector3 surf;
                pm->DirectionToSurfacePosition(&surf, &pt);
                float ey = pt.y - surf.y, ex = pt.x - surf.x, ez = pt.z - surf.z;
                float dist2 = ez * ez + ey * ey + ex * ex;
                BBox* bb = c->mLoco.GetBounds();
                float reach = (bb->maxz - bb->minz) * kHeightScale;
                float reach2 = reach * reach;
                cSPTransform t;
                t.mScale = 1.0f;
                Matrix3c ident(kMatrix3Identity);
                t.mRotation = *(Matrix3*)&ident;
                t.mTranslation = surf;
                t.mFlags = 4;
                t.mModificationCount = 1;
                Quat qtmp;
                Quat* qp = pm->BuildSurfaceOrientation(&qtmp, &t.mTranslation);
                Matrix3 mtmp;
                t.mRotation = *Matrix3FromQuaternion(&mtmp, qp);
                t.mFlags |= 2;
                t.mModificationCount++;
                int part;
                if (c->mpStatus->mValue == 0.0f)
                    part = 2;
                else
                    part = c->IsBusyMode() ? 0xb : 2;
                if (reach2 >= dist2 || c->CanReachPointWithBodyPart(&t, &pt, part, -1, 0, 0, 0.2f)) {
                    cStim* st = Stim(c)->Play(1, 0, 5.0f, cell);
                    if (st) {
                        st->mIndex = i;
                        return 1.0f;
                    }
                }
            }
        }
    }
    return 0.0f;
}
