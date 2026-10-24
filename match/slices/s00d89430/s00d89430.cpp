// slice s00d89430: FUN_00d896f0 (0x00d896f0, 248 bytes): creature update step. Clears stealth, fills a
// 0x74-byte request record with constants and calls the locomotion sub-object's virtual slot 0x37 (+0xdc)
// with it. The callee fills the record's first word (a vector-style buffer), which is freed here if
// non-null with a non-zero header word. Then the behaviour-tree object (+0xb4c) gets FUN_00bcb430 and the
// creature's Hover(false) runs.
// Free function (cdecl, one stack argument: the creature; the caller pops it).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef uint32_t uint32;

// 0x00f47380: operator delete (cdecl, one argument).
void operator_delete__(void* p);

// Float constants read from the image (addresses in the names).
extern float g_169f03c;
extern float g_169f040;
extern float g_169f044;
extern float g_1485720;
extern float g_1470f1c;
extern float g_13ec4b4;
extern float g_147c030;

// Behaviour-tree object at creature +0xb4c. Only FUN_00bcb430 is used here (0x00bcb430, thiscall).
struct cBehaviorTreeObj {
    void FUN_00bcb430();
};

// Creature (cSPCreatureBase). +0xc0 is the locomotion sub-object (its vptr is the first word there).
struct cSPCreatureBase {
    char pad00[0xb4c];
    cBehaviorTreeObj* mpBehavior;       // +0xb4c

    void SetStealthed(bool a, bool b);  // 0x00c1aed0 (thiscall, ret 8)
    void Hover(bool b);                 // 0x00c13a30 (thiscall, ret 4)
};

// 0x74-byte request record passed by pointer to the locomotion virtual call.
struct cLocoRequest {
    void*  mpBegin;                 // +0x00 (callee fills; buffer freed by the caller)
    void*  mpEnd;                   // +0x04
    void*  mpCapacity;              // +0x08
    uint32 pad0c[(0x14 - 0x0c) / 4];
    float  mfVec0;                  // +0x14
    float  mfVec1;                  // +0x18
    float  mfVec2;                  // +0x1c
    float  mfScalar;                // +0x20
    uint32 pad24;                   // +0x24
    uint32 pad28[(0x4c - 0x28) / 4];
    uint8_t mbFlag;                 // +0x4c
    uint8_t pad4d[3];
    float  mfZero50;                // +0x50
    float  mfZero54;                // +0x54
    float  mfZero58;                // +0x58
    uint32 mZero5c;                 // +0x5c
    float  mf60;                    // +0x60
    float  mf64;                    // +0x64
    float  mf68;                    // +0x68
    float  mfZero6c;                // +0x6c
    uint32 mZero70;                 // +0x70
};

// 0x00d896f0 (cdecl, plain `ret`).
void FUN_00d896f0(cSPCreatureBase* self)
{
    self->SetStealthed(false, false);

    // The original loads the first and fourth constants before the vtable slot is read.
    float cVec0 = g_169f03c;
    float cMf60 = g_1470f1c;

    // Locomotion vtable slot 0x37 (+0xdc), fetched before the record is filled.
    void** vt = *(void***)((char*)self + 0xc0);
    typedef void (__thiscall *FnLocoSlot)(void* self, cLocoRequest* request);
    FnLocoSlot fn = (FnLocoSlot)vt[0x37];

    cLocoRequest req;
    req.mfVec0 = cVec0;
    req.mfVec1 = g_169f040;
    req.mfVec2 = g_169f044;
    req.mf60 = cMf60;
    req.mfScalar = g_1485720;
    req.mf64 = g_13ec4b4;
    req.mpBegin = 0;
    req.mpEnd = 0;
    req.mpCapacity = 0;
    req.pad24 = 0;
    req.mbFlag = 0;
    req.mfZero50 = 0.0f;
    req.mfZero54 = 0.0f;
    req.mfZero58 = 0.0f;
    req.mZero5c = 0;
    req.mf68 = g_147c030;
    req.mfZero6c = 0.0f;
    req.mZero70 = 0;

    // Thiscall on the locomotion object (this = self + 0xc0) with the record pointer.
    fn((char*)self + 0xc0, &req);

    void* buf = req.mpBegin;
    if (buf != 0 && ((int*)buf)[-1] != 0)
        operator_delete__(buf);

    self->mpBehavior->FUN_00bcb430();
    self->Hover(false);
}

// =====================================================================================
// Gold7 functions of this slice: the SP creature behaviour-tree activate/deactivate
// callbacks for FIND_STUFF, nest decoration and the item drop/offer/receive group (retail).
//
// Every entry point is a cdecl behaviour-tree script callback: the creature comes first,
// then the four generic callback slots, then the per-behaviour state block (owned by the
// tree node); FIND_STUFF additionally gets a pointer to the caller's node handle.  The
// block layouts are the retail ones (the dev-build PDB `*_memory_block` types are quoted
// where they still line up).  All constants are referenced through their image addresses.
// =====================================================================================
#include <math.h>

namespace SP {

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

typedef void* AnimHandle_T;             // nSPCreatureAnim::anim_handle_t*

#define PV(n) virtual void pv##n();

// Pad-virtual helper: B's virtual functions first, then N unnamed ones.
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

// ---- constants (.rdata); only the addresses are known, see the disassembly -----------
extern const float  g_1473c70;          // 0x01473c70  10.0
extern const float  g_1486110;          // 0x01486110  20.0
extern const float  g_1485378;          // 0x01485378  0.0
extern const float  g_14853e0;          // 0x014853e0  4.0
extern const float  g_13eb8c8;          // 0x013eb8c8  0.3
extern const float  g_13eb8b0;          // 0x013eb8b0  -0.0 (float negation mask)
extern const float  g_13eecd8;          // 0x013eecd8  20.0
extern const double g_13f5650;          // 0x013f5650  4.0 (double)
extern const double g_13f5628;          // 0x013f5628  3.0 (double)
extern const double g_147c060;          // 0x0147c060  7.0 (double)
// 0x018eb45e is a game-data type token (an id, not a pointer) handed to CreateNode.
const uint32_t      g_orderNodeType = 0x018eb45e;

// ---- random ------------------------------------------------------------------------
class cRandomLC {
public:
    double RandomDoubleUniform();       // 0x009360d0
};
extern cRandomLC g_random;              // 0x01601760

// ---- generic ref-counted / spatial object view --------------------------------------
// Slot offsets used by this slice: +0x00 AddRef, +0x04 Release, +0x2c GetPosition,
// +0x5c GetForward, +0x68 sub-object with a float at +0x10, +0x74 height/radius,
// +0x84 Notify, +0xb8 Query, +0xbc/+0xc0 bundle add-ref/release.
struct RefA {
    virtual void AddRef();                                  // +0x00
    virtual void Release();                                 // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                      // +0x2c
};
struct RefB : VPad<11, RefA> {
    virtual const Vec3* GetForward(Vec3* tmp);              // +0x5c
};

// Object returned by slot 0x68 (a length source, only its +0x10 float is read).
struct cHeightSource {
    uint32_t pad00[4];                                      // +0x00..+0x0f
    float    mfOffset;                                      // +0x10
};

struct RefC : VPad<2, RefB> {
    virtual cHeightSource* GetHeightSource();               // +0x68
};
struct RefD : VPad<2, RefC> {
    virtual float GetHeight();                              // +0x74
};
struct RefE : VPad<3, RefD> {
    virtual void Notify(int a, int b, int c);               // +0x84
};
struct RefF : VPad<12, RefE> {
    virtual void* QueryInterface(uint32_t id);              // +0xb8
};
struct RefObj : RefF {
    virtual void AddRefBundle();                            // +0xbc
    virtual void ReleaseBundle();                           // +0xc0
};

// Intrusive reference holder; assignment is the out-of-line 0x00c70110, the add-ref /
// release pair 0x00c70110 uses is slots +0xbc / +0xc0.
template <class T> struct AutoRefCount {
    T* mpObject;

    void Assign(T* p);                                      // 0x00c70110 (ret 4)

    // Inlined by the original for the creature-typed holders.
    inline void Set(T* p)
    {
        T* old = mpObject;
        if (p != old) {
            if (p != 0)
                p->AddRef();
            mpObject = p;
            if (old != 0)
                old->Release();
        }
    }
};

// ---- creature ----------------------------------------------------------------------
struct nSPBehaviorTree;
class cCreatureAux;
class cForageRadiusSource;

// Locomotion request record handed to the locomotive slot +0xdc (same 0x74 bytes the
// creature update step fills in 0x00d896f0).
struct LocoRequest {
    void*    mpData;                                        // +0x00  owned heap buffer
    void*    mpEnd;                                         // +0x04
    void*    mpCap;                                         // +0x08
    uint32_t m0c;                                           // +0x0c
    uint32_t m10;                                           // +0x10
    Vec3     mDirection;                                    // +0x14
    float    mf20;                                          // +0x20
    uint32_t m24;                                           // +0x24
    uint32_t m28, m2c, m30, m34, m38, m3c, m40, m44, m48;   // +0x28..+0x4b
    uint8_t  mb4c;                                          // +0x4c
    uint8_t  m4d, m4e, m4f;                                 // +0x4d..+0x4f
    float    mf50;                                          // +0x50
    float    mf54;                                          // +0x54
    float    mf58;                                          // +0x58
    uint32_t m5c;                                           // +0x5c
    float    mf60;                                          // +0x60
    float    mf64;                                          // +0x64
    float    mf68;                                          // +0x68
    float    mf6c;                                          // +0x6c
    uint32_t m70;                                           // +0x70
};

struct Loco : VPad<6, RefObj> {
    virtual void NavRequest(LocoRequest* request);           // +0xdc
};

class cCreatureSettings {
public:
    uint32_t pad00[0x590 / 4];                              // +0x000
    float    mf590;                                         // +0x590  (== 0.0 -> "not eaten")
};

class cSPCreatureBase : public RefObj {
public:
    uint32_t pad04[(0xc0 - 4) / 4];                         // +0x004..+0x0bf
    Loco     mLoco;                                         // +0x0c0  locomotion sub-object (4-byte view)
    uint8_t  padC4[0xb20 - 0xc4];                           // +0x0c4..+0xb1f
    cCreatureSettings* mpSettings;                          // +0xb20
    uint32_t padB24[(0xb4c - 0xb24) / 4];                   // +0xb24..+0xb4b
    nSPBehaviorTree* mpBehavior;                            // +0xb4c
    uint32_t padB50[2];                                     // +0xb50..+0xb57
    uint8_t  mbB58;                                         // +0xb58  bit 3 = item in hand
    uint8_t  padB59[0xe40 - 0xb59];                         // +0xb59..+0xe3f
    uint32_t* mpE40;                                        // +0xe40  36-byte-stride table

    char  FUN_00c0e070(AnimHandle_T handle);                // 0x00c0e070
    void  Hover(int b);                                     // 0x00c13a30
    void* PlayAnimation(uint32_t id, int a, int b);         // 0x00c12190
    void  MoveToPointAtSpeed(int mode, const Vec3* pos, float speed, float arg);  // 0x00c1c1d0
    void  MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing,
                                      float speed, float arg);                  // 0x00c1c5c0
    RefObj* GetAt(uint32_t idx);                            // 0x00c0f8a0
    uint32_t FindFirstValid();                              // 0x00c0f780
    int   CountValid();                                     // 0x00c0f570
    cCreatureAux* GetAuxObject();                           // 0x00c04590
    cForageRadiusSource* GetForageRadiusSource();           // 0x00c0c1a0
};

// The object the creature hands out at 0x00c04590: +0x15c is a mode, +0x160 a noun-like
// sub-object (the one whose +0x34 sub-object is spatial).
class cNearNoun {
public:
    uint32_t pad00[0x34 / 4];                               // +0x00..+0x33
    RefObj   mSpatial;                                      // +0x34
};

class cCreatureAux {
public:
    uint32_t    pad00[0x15c / 4];                           // +0x000..+0x15b
    int         mMoveMode;                                  // +0x15c
    cNearNoun*  mpNoun;                                     // +0x160

    const Vec3* GetNounPosition();                          // 0x00c6acc0
};

// ---- behaviour tree ----------------------------------------------------------------
// The stimuli object lives eight bytes into the tree object; Attach / IsSourceAtEnd are
// called on the tree object itself.
class BehaviorStimuli {
public:
    RefObj* Play(uint32_t id, int flags);                   // 0x00bc96a0 (ret 8)
    void    ClearAll(uint32_t a, uint32_t mask);            // 0x00bc98f0 (ret 8)
    void    SetStimulus(uint32_t a, uint32_t b, float f, void* d);   // 0x00bc97f0 (ret 0x10)
};

struct nSPBehaviorTree {
    uint32_t        pad00[2];                               // +0x00..+0x07
    BehaviorStimuli mStimuli;                               // +0x08

    void Attach(void* node, cSPCreatureBase* c, void* block, void* fn);  // 0x00bcb480
    bool IsSourceAtEnd();                                   // 0x00bca280
};

// Record returned by Play(): +0x0c is a node kind tag, +0x10 a per-behaviour value.
class cAnimNode {
public:
    uint32_t pad00[3];                                      // +0x00
    union { int mKind; float mf0c; };                       // +0x0c
    union { float mf10; int mi10; };                        // +0x10  (item value / target index)
};

// ---- order manager -----------------------------------------------------------------
// Node description returned by FindNode / CreateNode; only the spawn position is poked.
class cOrderNodeDesc {
public:
    uint8_t pad00[0x1a4];                                   // +0x000
    Vec3    mSpawnPos;                                      // +0x1a4
};

class cAgentOrderManager {
public:
    cOrderNodeDesc* FindNode(uint32_t id, void* fn, cSPCreatureBase* c);         // 0x00bca620
    cOrderNodeDesc* CreateNode(uint32_t id, int count, uint32_t typeToken,
                               const char* name);                                 // 0x00bcb0b0
};

cAgentOrderManager* GetOrderManager();                      // 0x00bc9b00

// ---- behaviour state blocks --------------------------------------------------------
struct FindStuffBlock {                                     // SP::FIND_STUFF_memory_block
    int   mState;                                           // +0x00
    float mTimer;                                           // +0x04
    float mStopDistance;                                    // +0x08
};

struct DecorateNestBlock {                                  // SP::DECORATE_NEST_memory_block
    uint32_t mState;                                        // +0x00
    bool     mbDroppedItem;                                 // +0x04
    Vec3     mDesiredPos;                                   // +0x08
    AutoRefCount<RefObj> mpObject;                          // +0x14
    bool     mbUseMouthAnim;                                // +0x18
};

struct HitSelfWithItemBlock {                    // SP::HIT_SELF_WITH_ITEM_memory_block
    uint32_t mState;                                        // +0x00
    AutoRefCount<RefObj> mpObject;                          // +0x04
};

struct DropItemsBlock {                                     // SP::DROP_ITEMS_memory_block
    uint32_t mState;                                        // +0x00
    bool     mbDroppedItems;                                // +0x04
    AutoRefCount<RefObj> mpObject;                          // +0x08
};

// Retail OFFER_ITEM / RECEIVE_ITEM blocks: the dev PDB layout shifted by eight bytes
// (two timer floats sit in front of the desired position) and gained a target index
// dword in front of the animation handle.
struct OfferItemBlock {
    uint32_t mState;                                        // +0x00
    float    mOverallOfferTime;                             // +0x04
    float    mHeldOutItemTime;                              // +0x08
    Vec3     mDesiredPos;                                   // +0x0c
    AutoRefCount<cSPCreatureBase> mpRecipient;              // +0x18
    AutoRefCount<RefObj> mpObject;                          // +0x1c
    bool     mbUseMouth;                                    // +0x20
    int      mTargetIndex;                                  // +0x24
    AnimHandle_T mAnimHandle;                               // +0x28
};

struct ReceiveItemBlock {
    uint32_t mState;                                        // +0x00
    float    mOverallReceiveTime;                           // +0x04
    float    mHeldOutItemTime;                              // +0x08
    Vec3     mDesiredPos;                                   // +0x0c
    AutoRefCount<cSPCreatureBase> mpGiver;                  // +0x18
    AutoRefCount<RefObj> mpObject;                          // +0x1c
    bool     mbUseMouth;                                    // +0x20
    int      mTargetIndex;                                  // +0x24
    AnimHandle_T mAnimHandle;                               // +0x28
};

// ---- free functions / other objects -------------------------------------------------
void  FUN_00d7a700();                                       // 0x00d7a700  forage source
void  FUN_00d7be30();                                       // 0x00d7be30  find-food source
void  FUN_00d7bea0();                                       // 0x00d7bea0  food-raid source

// 0x00c04590 (thiscall) returns the creature's creature-aux object; modelled as a
// cSPCreatureBase member so the call is a thiscall like the original.

class cForageRadiusSource {
public:
    uint8_t pad00[0x394];                                   // +0x000
    float   mf394;                                          // +0x394  lower bound
    float   mf398;                                          // +0x398  upper bound
};


RefObj* FUN_00d998d0(const cAnimNode* node, uint32_t id);   // 0x00d998d0
float   FUN_00572a10(float lo, float hi);                   // 0x00572a10  RandomFloatRange
Vec3*   normalized_safe(Vec3* out, const Vec3* in);         // 0x00449c20  cdecl
void*   FUN_00bd8440(void* holder);                         // 0x00bd8440  Query(0x137e8e0)

// The object 0x00bd8440 resolves out of a creature-owned reference: its behaviour tree
// lives at +0xaf0 (the +8 stimuli object is the one that gets the stimulus).
class cCreatureRefTarget {
public:
    uint8_t          pad00[0xaf0];                          // +0x000
    nSPBehaviorTree* mpBehavior;                            // +0xaf0
};

class cPlanetModel {
public:
    const Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* p);   // 0x00b815a0
};
cPlanetModel* PlanetModel(Vec3* out, const Vec3* p);        // 0x00b3d350

// eastl teardown of a buffer the locomotion request may have allocated (the allocation
// header sits four bytes in front of the payload).
inline void FreeOwnedBuffer(void* p)
{
    if (p != 0 && ((int*)p)[-1] != 0)
        operator_delete__(p);
}

template <class T> inline const T& max(const T& a, const T& b) { return a < b ? b : a; }
template <class T> inline const T& min(const T& a, const T& b) { return b < a ? b : a; }

// =====================================================================================
// @ 0x00d89430
// SP::FIND_STUFF_Activate (dev-build anchor 0x0099fc80): pick the forage source for the
// action id, find or create the order node, hand it to the tree and start the walk with
// the node's stop distance (3..7, from the species radius).
// =====================================================================================
bool FIND_STUFF_Activate(cSPCreatureBase* c, int, int, int, uint32_t actionId,
                         FindStuffBlock* st, cOrderNodeDesc** ppNode)
{
    cOrderNodeDesc* node = 0;
    if (ppNode != 0)
        node = *ppNode;

    void* fn = 0;
    const char* name = 0;
    if (actionId == 0x435cfe8) {
        fn = (void*)&FUN_00d7a700;
        name = "Forage";
    }
    else if (actionId == 0x435dd79) {
        fn = (void*)&FUN_00d7be30;
        name = "FindFood";
    }
    else if (actionId == 0x44d4fef) {
        fn = (void*)&FUN_00d7bea0;
        name = "FoodRaid";
    }

    if (node == 0) {
        if (fn != 0)
            node = GetOrderManager()->FindNode(actionId, fn, c);
        if (node == 0) {
            cForageRadiusSource* src = c->GetForageRadiusSource();
            float lo = src != 0 ? src->mf394 : g_1486110;
            float hi = src != 0 ? src->mf398 : g_1473c70;
            int count = max((int)FUN_00572a10(lo, hi), 1);
            node = GetOrderManager()->CreateNode(actionId, count, g_orderNodeType, name);
            node->mSpawnPos = *c->mLoco.GetPosition();
        }
    }

    c->mpBehavior->Attach(node, c, st, fn);
    st->mTimer = g_1473c70;
    st->mState = c->mpBehavior->IsSourceAtEnd() ? 0 : 2;

    double spread = g_random.RandomDoubleUniform() * g_13f5650 + g_13f5628;
    st->mStopDistance = (float)min(max(spread, g_13f5628), g_147c060);

    LocoRequest req;
    req.mDirection.x = g_169f03c;
    req.mDirection.y = g_169f040;
    req.mDirection.z = g_169f044;
    req.mf20 = g_1485720;
    req.mf60 = g_1470f1c;
    req.mf64 = g_13ec4b4;
    req.mpData = 0;
    req.mpEnd = 0;
    req.mpCap = 0;
    req.m24 = 0;
    req.mb4c = 0;
    req.mf50 = 0.0f;
    req.mf54 = 0.0f;
    req.mf58 = 0.0f;
    req.m5c = 0;
    req.mf68 = g_147c030;
    req.mf6c = 0.0f;
    req.m70 = 0;
    c->mLoco.NavRequest(&req);
    FreeOwnedBuffer(req.mpData);

    c->Notify(0, 0, 0);
    c->Hover(1);
    return true;
}

// =====================================================================================
// @ 0x00d897f0
// SP::DECORATE_NEST_Activate (caller-scored): drop the carried object in front of the
// nearest valid creature, otherwise just walk to the spot.
// =====================================================================================
bool DECORATE_NEST_Activate(cSPCreatureBase* c, int, int, int, int, DecorateNestBlock* st)
{
    if (st != 0)
        st->mpObject.mpObject = 0;

    cAnimNode* node = (cAnimNode*)c->mpBehavior->mStimuli.Play(0, 0x8000);
    cCreatureAux* aux = c->GetAuxObject();
    if (node == 0 || aux->mpNoun == 0)
        return false;
    if (c->CountValid() <= 0)
        return false;

    uint32_t idx = c->FindFirstValid();
    RefObj* combatant = c->GetAt(idx);
    if (combatant == 0)
        return false;

    st->mbUseMouthAnim = (c->mpSettings->mf590 == g_1485378);
    st->mpObject.Assign(combatant);

    const Vec3* np = aux->GetNounPosition();
    const Vec3* cp = c->mLoco.GetPosition();
    Vec3 d(cp->x - np->x, cp->y - np->y, cp->z - np->z);
    Vec3 n;
    normalized_safe(&n, &d);

    RefObj* spatial = &aux->mpNoun->mSpatial;
    float h1 = spatial->GetHeight();
    float h2 = spatial->GetHeight();
    float len2 = d.z * d.z + d.y * d.y + d.x * d.x;
    if (len2 > h1 * h2)
        n = Vec3(-n.x, -n.y, -n.z);

    float reach = c->mLoco.GetHeightSource()->mfOffset + spatial->GetHeight();
    Vec3 off(n.x * reach, n.y * reach, n.z * reach);
    const Vec3* np2 = aux->GetNounPosition();
    st->mDesiredPos = Vec3(np2->x + off.x, np2->y + off.y, np2->z + off.z);

    c->MoveToPointAtSpeed(2, &st->mDesiredPos, c->mLoco.GetHeight(), g_1470f1c);
    if (aux->mMoveMode == 3)
        c->PlayAnimation(0x32859f13, 1, -1);

    st->mbDroppedItem = false;
    st->mState = 0;
    return true;
}

// =====================================================================================
// @ 0x00d89a80
// SP::DECORATE_NEST_Deactivate: drop the nest stimulus and the carried object.
// =====================================================================================
void FUN_00d89a80(cSPCreatureBase* c, int, int, int, int, DecorateNestBlock* st)
{
    c->mpBehavior->mStimuli.ClearAll(0, 0x8000);
    if (st != 0) {
        RefObj* p = st->mpObject.mpObject;
        if (p != 0)
            p->ReleaseBundle();
    }
}

// =====================================================================================
// @ 0x00d89ac0
// HIT_SELF_WITH_ITEM activate (the state block is HIT_SELF_WITH_ITEM_memory_block: state
// + the target reference at +4; the node kind 1 record names the item): grab the first
// valid combatant as this action's target.
// =====================================================================================
bool FUN_00d89ac0(cSPCreatureBase* c, int, int, int, int, HitSelfWithItemBlock* st)
{
    if (st != 0)
        st->mpObject.mpObject = 0;

    cAnimNode* node = (cAnimNode*)c->mpBehavior->mStimuli.Play(0, 0x40000);
    if (node == 0 || c->CountValid() <= 0 || node->mKind != 1)
        return false;

    uint32_t idx = c->FindFirstValid();
    RefObj* target = c->GetAt(idx);
    if (target == 0)
        return false;

    st->mpObject.Assign(target);
    st->mState = 0;
    return true;
}

// =====================================================================================
// @ 0x00d89b70
// DROP_ITEMS activate (DROP_ITEMS_memory_block): take the object named by the kind-2 node
// and finish as soon as there is something to look at (a valid creature, the dropped
// object, or the "carrying" flag at creature +0xb58).
// =====================================================================================
bool FUN_00d89b70(cSPCreatureBase* c, int, int, int, int, DropItemsBlock* st)
{
    if (st != 0)
        st->mpObject.mpObject = 0;

    cAnimNode* node = (cAnimNode*)c->mpBehavior->mStimuli.Play(0, 0x40000);
    if (node == 0 || node->mKind != 2)
        return false;

    st->mpObject.Assign(FUN_00d998d0(node, 0x1186577));
    if (c->CountValid() <= 0) {
        if (st->mpObject.mpObject != 0)
            return false;
        if ((c->mbB58 & 8) == 0)
            return false;
    }

    st->mbDroppedItems = false;
    st->mState = 0;
    return true;
}

// =====================================================================================
// @ 0x00d89c00
// DROP_ITEMS deactivate: drop the stimulus and both references.
// =====================================================================================
void FUN_00d89c00(cSPCreatureBase* c, int, int, int, int, DropItemsBlock* st)
{
    c->mpBehavior->mStimuli.ClearAll(0, 0x40000);

    RefObj* old = st->mpObject.mpObject;
    if (old != 0) {
        st->mpObject.mpObject = 0;
        old->ReleaseBundle();
    }
    if (st != 0) {
        RefObj* p = st->mpObject.mpObject;
        if (p != 0)
            p->ReleaseBundle();
    }
}

// =====================================================================================
// @ 0x00d89c50
// SP::OFFER_ITEM_Activate (caller-scored): resolve the recipient named by the kind-6
// node, hold the object out and walk towards the recipient while facing it.
// =====================================================================================
bool OFFER_ITEM_Activate(cSPCreatureBase* c, int, int, int, int, OfferItemBlock* st)
{
    if (st != 0) {
        st->mpRecipient.mpObject = 0;
        st->mpObject.mpObject = 0;
    }

    cAnimNode* node = (cAnimNode*)c->mpBehavior->mStimuli.Play(0, 0x40000);
    if (node == 0 || node->mKind != 6)
        return false;

    int idx = node->mi10;
    cSPCreatureBase* recipient = (cSPCreatureBase*)FUN_00d998d0(node, 0xd0036e08);
    st->mpRecipient.Set(recipient);
    st->mpObject.Assign(c->GetAt(idx));
    st->mTargetIndex = -1;
    if (st->mpRecipient.mpObject == 0 || st->mpObject.mpObject == 0 || idx == -1)
        return false;

    st->mTargetIndex = c->mpE40[idx * 9];

    Loco* rl = &st->mpRecipient.mpObject->mLoco;
    Loco* ll = &c->mLoco;
    const Vec3* cp = ll->GetPosition();
    const Vec3* rp = rl->GetPosition();
    Vec3 d(rp->x - cp->x, rp->y - cp->y, rp->z - cp->z);
    Vec3 n;
    normalized_safe(&n, &d);

    float h1 = ll->GetHeight();
    float h2 = ll->GetHeight();
    float len2 = d.z * d.z + d.y * d.y + d.x * d.x;
    if (len2 > h1 * h2 * g_14853e0) {
        float len = sqrtf(len2);
        const Vec3* lp = ll->GetPosition();
        st->mDesiredPos = Vec3(lp->x + (n.x * len) * g_13eb8c8,
                               lp->y + (n.y * len) * g_13eb8c8,
                               lp->z + (n.z * len) * g_13eb8c8);
    }
    else {
        st->mDesiredPos = *ll->GetPosition();
    }

    c->MoveToPointAndFacingAtSpeed(2, &st->mDesiredPos, &n, ll->GetHeight(), g_1470f1c);
    st->mOverallOfferTime = 0.0f;
    st->mHeldOutItemTime = 0.0f;
    st->mState = 0;
    st->mbUseMouth = (c->mpSettings->mf590 == 0.0f);
    st->mAnimHandle = 0;
    return true;
}

// =====================================================================================
// @ 0x00d89f30
// SP::OFFER_ITEM_Deactivate (caller-scored): stop the hold animation, drop the stimulus
// and release the recipient and the offered object.
// =====================================================================================
void OFFER_ITEM_Deactivate(cSPCreatureBase* c, int, int, int, int, OfferItemBlock* st)
{
    if (c->FUN_00c0e070(st->mAnimHandle))
        st->mAnimHandle = c->PlayAnimation((st->mbUseMouth ? 0x156e127 : 0) + 0x3a0e984, 1, -1);

    c->mpBehavior->mStimuli.ClearAll(0, 0x40000);
    if (st->mpObject.mpObject != 0)
        st->mpObject.mpObject->ReleaseBundle();
    if (st->mpRecipient.mpObject != 0)
        st->mpRecipient.mpObject->Release();
}

// =====================================================================================
// @ 0x00d89fb0
// RECEIVE_ITEM activate: resolve the giver named by the kind-6 node, aim at the point
// in front of it and register the approach, then poke the giver's stimuli.
// =====================================================================================
bool FUN_00d89fb0(cSPCreatureBase* c, int, int, int, int, ReceiveItemBlock* st)
{
    if (st != 0) {
        st->mpGiver.mpObject = 0;
        st->mpObject.mpObject = 0;
    }

    cAnimNode* node = (cAnimNode*)c->mpBehavior->mStimuli.Play(0, 0x40000);
    if (node == 0 || node->mKind != 6)
        return false;

    int idx = node->mi10;
    st->mpGiver.Assign((cSPCreatureBase*)FUN_00d998d0(node, 0x1186577));
    st->mpObject.Assign(c->GetAt(idx));
    st->mTargetIndex = -1;
    if (st->mpGiver.mpObject == 0 || st->mpObject.mpObject == 0 || idx == -1)
        return false;

    st->mTargetIndex = c->mpE40[idx * 9];

    Loco* ll = &c->mLoco;
    cSPCreatureBase* giver = st->mpGiver.mpObject;
    float speed = ll->GetHeight() + giver->GetHeight();

    Vec3 forward;
    const Vec3* fwd = giver->GetForward(&forward);
    Vec3 off(fwd->x * speed, fwd->y * speed, fwd->z * speed);
    const Vec3* gp = giver->GetPosition();
    Vec3 spot(gp->x + off.x, gp->y + off.y, gp->z + off.z);

    Vec3 surf;
    cPlanetModel* planet = PlanetModel(&surf, &spot);
    st->mDesiredPos = *planet->DirectionToSurfacePosition(&surf, &spot);

    Vec3 facing(-fwd->x, -fwd->y, -fwd->z);
    c->MoveToPointAndFacingAtSpeed(2, &st->mDesiredPos, &facing, speed, g_1470f1c);

    st->mOverallReceiveTime = 0.0f;
    st->mHeldOutItemTime = 0.0f;
    st->mState = 0;
    st->mbUseMouth = (c->mpSettings->mf590 == 0.0f);
    st->mAnimHandle = 0;

    cCreatureRefTarget* other = (cCreatureRefTarget*)FUN_00bd8440(&st->mpGiver);
    if (other != 0)
        other->mpBehavior->mStimuli.SetStimulus(0x8000, 0, g_13eecd8, 0);
    return true;
}

// =====================================================================================
// @ 0x00d8a220
// RECEIVE_ITEM deactivate: same as the offer counterpart, both references released
// through the bundle slot.
// =====================================================================================
void FUN_00d8a220(cSPCreatureBase* c, int, int, int, int, ReceiveItemBlock* st)
{
    if (c->FUN_00c0e070(st->mAnimHandle))
        st->mAnimHandle = c->PlayAnimation((st->mbUseMouth ? 0x156e127 : 0) + 0x3a0e984, 1, -1);

    c->mpBehavior->mStimuli.ClearAll(0, 0x40000);
    if (st->mpObject.mpObject != 0)
        st->mpObject.mpObject->ReleaseBundle();
    if (st->mpGiver.mpObject != 0)
        st->mpGiver.mpObject->ReleaseBundle();
}

} // namespace SP
