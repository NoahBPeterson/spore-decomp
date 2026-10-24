// Slice s010317d0 -- SP::cAbductionBeamLocomotion::Update (0x010317d0): per-tick movement of an object
// held in a UFO abduction beam. Moves the object along the beam (tractor: toward the UFO, otherwise
// drops away from it), reorients it toward the beam direction, rescales it and writes its velocity.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no EH frame in the original).
#include "types.h"

typedef unsigned int uint;
typedef void *P;

struct Vec3 { float x, y, z; };

// Inline SSE clamp helper used by this module (maxss/minss with SSE NaN semantics).
inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}
template <class T> inline const T &Max(const T &a, const T &b) { return (a < b) ? b : a; }

#include <math.h>
#pragma intrinsic(sqrt)

inline float Length(const Vec3 *v)
{
    float sq = (v->z * v->z + v->y * v->y) + v->x * v->x;
    return sqrtf(sq);
}

// ---------------------------------------------------------------- external classes (stubs)
struct PlantIface {
    char  pad[0x660];
    float mScale;                              // +0x660 (plant growth scale)
    P GetSpeciesKey();                         // 0x00c3e290 (ecx+0x650)
};
struct Species {
    P GetScaleKey();                           // 0x00b8f860
};
struct PlantSpeciesMgr {
    Species *GetSpeciesFromID(P id);           // 0x00b90410 (ret 4)
};

struct Matrix3;
struct PlanetModelT {
    float GetRadiusAt(const Vec3 *pos);                                  // 0x00b7ef70 (ret 4)
    void  Func_b81630(Vec3 *out, const Vec3 *in);                        // 0x00b81630 (ret 8)
    Vec3 *Func_b82110(Vec3 *out, const Vec3 *from, const Vec3 *dir);     // 0x00b82110 (ret 0xc)
    float GetWaterHeight();                                              // 0x00b7e390
    P     BuildSurfaceOrientation2(Matrix3 *out, const Vec3 *pos,
                                   const Vec3 *up);                      // 0x00b7f250 (ret 0xc)
};

struct Tuning {
    char  pad[0x198];
    float tractorLo, tractorHi;   // +0x198, +0x19c
    float dropLo, dropHi;         // +0x1a0, +0x1a4
};

struct UFOData { char pad[0x714]; int mode; };               // cSPGameDataUFO (mode at +0x714)
struct BeamOwner { char pad[0x114]; P mpRef; };              // +0x114: AutoRefCount to the spatial object

struct cLocomotionRequest;

struct SpatialObj {
    char pad04[0x77 - 4];
    uint8_t  b77;
    char pad78[0x1f0 - 0x78];
    uint32_t f1f0;
    virtual void AddRef();                     // slot 0x00
    virtual void Release();                    // slot 0x04
    virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual Vec3 *GetPosition();               // slot 0x2c
    virtual void v0c();
    virtual float GetScale();                  // slot 0x34
    virtual void SetPosition(Vec3 *pos);       // slot 0x38
    virtual void SetOrientation(P q);          // slot 0x3c
    virtual void SetScale(float s);            // slot 0x40
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16();
    virtual Vec3 *GetUp(Vec3 *out);            // slot 0x5c
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d();
    virtual P QueryInterface(uint id);         // slot 0xb8
    virtual void v2e(); virtual void v2f(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void ApplyLocomotion(cLocomotionRequest *request);   // slot 0xdc
    void SetLocomotion(P loco);                // 0x00c421b0 (ret 4)
    Vec3 *GetVelocity();                       // 0x00d20610
};

struct Beam {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual bool IsFinished();                 // slot 0x2c
    char pad[0x134 - 4];
    BeamOwner *mpOwner;                        // +0x134
    void GetEndPoints(Vec3 *a, Vec3 *b);       // 0x00cb8ba0 (ret 8)
};

struct LocoCtx {
    Vec3  vel;
    float f0c;
    float dt;           // +0x10
    SpatialObj *obj;    // +0x14
};

struct Matrix3 { float m[9]; };
struct Quat4 { float q[4]; };

// ---- callees (calling conventions checked against the callers / callee epilogues)
PlantSpeciesMgr *PlantSpeciesManager();          // 0x00b3d420 (cdecl, no args)
float    FUN_01030d50(P key);                    // cdecl, 1 stack arg
PlanetModelT *PlanetModel();                     // 0x00b3d350
Tuning  *GetTuning();                            // 0x00c37360
uint     GetCurrentGameMode();                   // 0x00b5b800
UFOData *interface_cast_UFO(P *ref);             // 0x00c9f040 EA::COM::interface_cast<cSPGameDataUFO*,...>
void     normalized_safe(Vec3 *out, const Vec3 *v);   // 0x00449c20 (cdecl)
void     FUN_00afa0c0(Matrix3 *out, const Vec3 *a, const Vec3 *b, const Vec3 *c);   // cdecl, 4 args
P        FUN_0046d660(const Vec3 *a, const Matrix3 *m);     // cdecl, 2 args
P        FUN_00c64ad0(Quat4 *out, P in);                    // cdecl, 2 args
P        FUN_01030e20(SpatialObj *o);                       // cdecl, 1 arg
void *   operator_new(uint size, const char *name, int a, int b, int c, int d);   // 0x00f473a0

extern Vec3  g_016ded38;
extern float g_015b7668;

struct AbductionBeamLoco {
    void  *vptr0, *vptr4;
    P      pad8, padc;
    Beam  *mpBeam;          // +0x10
    float  mDistance;       // +0x14
    bool   mbTractor;       // +0x18
    float  mOriginalScale;  // +0x1c
    bool   mFirstUpdate;    // +0x20
    float  mSpeed;          // +0x24

    void Update(LocoCtx *ctx);    // ret 4
};

// SP::cAbductionBeamLocomotion::Update @ 0x010317d0
void AbductionBeamLoco::Update(LocoCtx *ctx)
{
    if (mFirstUpdate) {
        mOriginalScale = ctx->obj->GetScale();
        if (!mbTractor && ctx->obj) {
            PlantIface *plant = (PlantIface *)ctx->obj->QueryInterface(0xaeb336b4);
            if (plant) {
                P id = plant->GetSpeciesKey();
                Species *sp = PlantSpeciesManager()->GetSpeciesFromID(id);
                mOriginalScale = FUN_01030d50(sp->GetScaleKey());
            }
        }
        mFirstUpdate = false;
    }

    if (mpBeam == 0 || mpBeam->IsFinished()) {
        P *loco = (P *)operator_new(0x14, "Simulator/cDropToGroundLocomotion", 0, 0, 0, 0);
        if (loco == 0) {
            ctx->obj->SetLocomotion(0);
            return;
        }
        loco[2] = (P)0x013ec458;
        loco[3] = 0;
        loco[0] = (P)0x01499590;
        loco[2] = (P)0x01499580;
        loco[4] = 0;
        ctx->obj->SetLocomotion(loco);
        return;
    }

    ctx->obj->f1f0 = 4;
    ctx->obj->b77 = 0;
    Vec3 a, b;
    mpBeam->GetEndPoints(&a, &b);
    Vec3 *cur = ctx->obj->GetPosition();

    if (mDistance < 0.0f) {
        if (mbTractor) {
            float dx = a.x - cur->x, dy = a.y - cur->y, dz = a.z - cur->z;
            mDistance = (float)sqrt((double)(dy * dy + (dx * dx + dz * dz)));
        } else {
            mDistance = 0.0f;
        }
    }

    float len0 = Length(cur);
    float height = len0 - PlanetModel()->GetRadiusAt(cur);
    float t = Clamp(height, 0.0f, 500.0f) * 0.002f;
    float smooth = (3.0f - t * 2.0f) * t * t;

    Tuning *tune = GetTuning();
    if (mbTractor) {
        float v = (tune->tractorHi - tune->tractorLo) * smooth + tune->tractorLo;
        if (GetCurrentGameMode() != 0x1654c05)
            v = v * 0.5f;
        float spd = v;
        BeamOwner *owner = mpBeam->mpOwner;
        if (owner && owner->mpRef) {
            UFOData *ufo = interface_cast_UFO(&owner->mpRef);
            if (ufo && ufo->mode == 5)
                spd = g_015b7668 * v;
        }
        mDistance = mDistance - spd * ctx->dt;
        if (mDistance < 0.0f)
            mDistance = 0.0f;
    } else {
        mDistance = ((tune->dropHi - tune->dropLo) * smooth + tune->dropLo) * ctx->dt + mDistance;
    }

    if (mDistance < 1.5258789e-05f)
        return;

    Vec3 d;
    d.x = b.x - a.x; d.y = b.y - a.y; d.z = b.z - a.z;
    Vec3 dir;
    normalized_safe(&dir, &d);
    Vec3 p2;
    p2.x = mDistance * dir.x + a.x;
    p2.y = dir.y * mDistance + a.y;
    p2.z = dir.z * mDistance + a.z;
    PlanetModelT *model = PlanetModel();
    if (model) {
        model->Func_b81630(&d, &p2);
        float lenD = (float)sqrt((double)((d.y * d.y + d.z * d.z) + d.x * d.x));
        float lenP = (float)sqrt((double)((p2.z * p2.z + p2.y * p2.y) + p2.x * p2.x));
        if (lenP < lenD) {
            Vec3 tmp;
            p2 = *model->Func_b82110(&tmp, &a, &dir);
            float dx = a.x - p2.x, dy = a.y - p2.y, dz = a.z - p2.z;
            mDistance = (float)sqrt((double)((dz * dz + dy * dy) + dx * dx));
        }
    }

    float inv = 1.0f / ctx->dt;
    ctx->vel.x = inv * (p2.x - cur->x);
    ctx->vel.y = (p2.y - cur->y) * inv;
    ctx->vel.z = (p2.z - cur->z) * inv;

    d.x = -dir.x; d.y = -dir.y; d.z = -dir.z;
    Vec3 n = d;
    if (d.x != g_016ded38.x || d.y != g_016ded38.y || d.z != g_016ded38.z) {
        Vec3 u;
        ctx->obj->GetUp(&u);
        Vec3 c;
        c.x = u.y * d.z - u.z * d.y;
        c.y = u.z * d.x - d.z * u.x;
        c.z = d.y * u.x - u.y * d.x;
        Vec3 w;
        w.x = d.y * c.z - c.y * d.z;
        w.y = d.z * c.x - d.x * c.z;
        w.z = c.y * d.x - d.y * c.x;
        Matrix3 m;
        FUN_00afa0c0(&m, &w, &n, &c);
        SpatialObj *o = ctx->obj;
        Quat4 q;
        o->SetOrientation(FUN_00c64ad0(&q, FUN_0046d660(&n, &m)));
    }

    float ratio = 0.0f;
    {
        float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
        float len = (float)sqrt((double)((dz * dz + dy * dy) + dx * dx));
        if (1.5258789e-05f < len)
            ratio = mDistance / len;
    }

    if (ctx->obj && ctx->obj->QueryInterface(0xaeb336b4)) {
        float s = mOriginalScale * ratio;
        ctx->obj->SetScale(Max(0.2f, s));
        return;
    }
    P p = FUN_01030e20(ctx->obj);
    if (p)
        ((PlantIface *)p)->mScale = ratio;
}

// ---------------------------------------------------------------------------
// SP::cSPSpaceGameBehaviorAbducted -- the "held by a UFO abduction beam"
// space-game behaviour.  It caches the abducted object in mAgent, looks the
// active beam up through the entity table (mEntityId at +0x24), and keeps an
// eastl rbtree of per-object bookkeeping at +0x80.
// ---------------------------------------------------------------------------

struct AllocBlockHeader { uint32_t mRefCount; };   // EA allocator header (word before a block)

void FreeAllocBlock(void *block);                  // 0x00f47380 operator delete

// AutoRefCount<T> released through the EA allocator (header refcount checked first).
struct AllocRef {
    void *mpObject;
    ~AllocRef()
    {
        void *p = mpObject;
        if (p != 0 && ((AllocBlockHeader *)p)[-1].mRefCount != 0)
            FreeAllocBlock(p);
    }
};

// eastl::rbtree<unsigned int, pair<unsigned int const, cWorld>, ...> header.
struct RBNodeBase {
    RBNodeBase *mpNodeRight;      // +0x00
    RBNodeBase *mpNodeLeft;       // +0x04
    RBNodeBase *mpNodeParent;     // +0x08
    union {
        uint32_t mColorWord;      // colour + padding, zeroed as one word
        struct {
            uint8_t mColor;
            uint8_t mPad[3];
        };
    };
};

// The container at +0x80: four bytes of padding/state in front of the anchor.
struct AgentMap {
    uint32_t   mField80;          // +0x00  (container state, zeroed with the object)
    RBNodeBase mAnchor;           // +0x04
    uint32_t   mnSize;            // +0x14
    uint32_t   mField98;          // +0x18

    void Init();
    void DoNukeSubtree(RBNodeBase *node);        // 0x009a9600
    ~AgentMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
};

void AgentMap::Init()
{
    mAnchor.mpNodeLeft = 0;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColorWord = 0;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
}

// Paged entity table: EntityTable::mpBlocks[id >> 7][id & 0x7f].
struct EntitySlot {
    uint32_t mFlags;              // +0x00
    void    *mpObject;            // +0x04
};

// Paged entity table: mpEntityBlocks[id >> 7] is a 128-entry block of slots.

// The object stored in the entity table, queried for the beam interface.
struct IEntity {
    virtual void v00();
    virtual void *GetInterface(uint id);         // slot 1 (+0x04)
};

// SP::cInteraction -- base class of the space-game behaviours.
struct cInteraction {
    cInteraction();                              // 0x00abf320
    virtual void AddRef();
    virtual void Release();
    virtual ~cInteraction();                     // 0x00abf190
    bool AttachTarget(void *target);             // 0x00abf640 (ret 4)
};

// AutoRefCount<SpatialObj> -- releases the held interface on destruction.
struct AgentRef {
    SpatialObj *mpObject;
    ~AgentRef()
    {
        if (mpObject != 0)
            mpObject->Release();
    }
};

// Simulator::cLocomotionRequest -- request struct applied through vt[0xdc].
struct cLocomotionRequest {
    AllocRef  mRef;               // +0x00
    uint32_t  mField04;           // +0x04
    uint32_t  mField08;           // +0x08
    uint32_t  mField0c;           // +0x0c
    uint32_t  mField10;           // +0x10
    Vec3      mOffset;            // +0x14
    float     mField20;           // +0x20
    uint32_t  mField24;           // +0x24
    uint8_t   mPad28[0x24];       // +0x28
    uint8_t   mField4c;           // +0x4c
    uint8_t   mPad4d[3];
    float     mField50;           // +0x50
    float     mField54;           // +0x54
    float     mField58;           // +0x58
    uint32_t  mField5c;           // +0x5c
    float     mField60;           // +0x60
    float     mField64;           // +0x64
    float     mField68;           // +0x68
    float     mField6c;           // +0x6c
    uint32_t  mField70;           // +0x70

    cLocomotionRequest();                        // 0x00ac9850
};

// The locomotion sub-object a creature/plant owns: SetLocomotion installs a
// cLocomotion-derived object, vt[0xdc] pushes a request into it.
struct LocomotionHolder {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38(); virtual void v39(); virtual void v3a(); virtual void v3b();
    virtual void v3c(); virtual void v3d();
    virtual void ApplyRequest(cLocomotionRequest *request);   // slot 0xdc
    void SetLocomotion(void *loco);              // 0x00c421b0 (ret 4)
    void FUN_00c44040();                         // 0x00c44040
};

// Simulator::cAbductionBeamLocomotion -- the locomotion installed on an abductee.
struct cAbductionBeamLocomotion {
    cAbductionBeamLocomotion(Beam *beam, bool tractor);   // 0x01030e80
    void *operator new(uint size, const char *name)
    {
        return operator_new(size, name, 0, 0, 0, 0);
    }
    void *Construct(Beam *beam, bool tractor);   // 0x01030e80 (ret 8)
};

// cSPCreatureBase: the abductee when it is a creature (locomotion holder at +0xc0).
struct cSPCreatureBase {
    uint8_t mPad04[0xbc];                        // +0x04
    LocomotionHolder mLoco;                      // +0xc0
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
    virtual void v38();
    virtual void Detach(int mode);               // slot 0x9c
    void InterruptAnimation(uint anim, int a, int b);   // 0x00c12310 (ret 0xc)
    void PlayAnimation(uint anim, int a, int b);        // 0x00c12190 (ret 0xc)
};

// A plant-like abductee (locomotion holder at +0x34).
struct cSPPlantAgent {
    uint8_t mPad04[0x30];                        // +0x04
    LocomotionHolder mLoco;                      // +0x34
    uint8_t mPad38[0x528 - 0x38];                // +0x38
    uint8_t mbAbducted;                          // +0x528
};

extern void *g_vtbl4_cSPSpaceGameBehaviorAbducted;   // 0x01499724 second interface vftable
extern Vec3  g_016ded38;                             // (already declared above)
extern float g_1_5f;            // 0x01485548
extern float g_2_0f;            // 0x01470f1c
extern float g_kScaleUnset;     // 0x013eb1bc (-1.0f)
extern float g_kStepScale;      // 0x013eecd8 (20.0f)
extern float g_kEpsilon;        // 0x013ec4b8 (1e-8f)
extern float g_kAnimRate;       // 0x013ec4b4
extern float g_kRequestRate;    // 0x014996fc
extern float g_kGrowRate;       // 0x01470f1c
extern float g_kWaterScale;     // 0x01485548

void FUN_00c41d60(SpatialObj *obj, Vec3 *v);         // 0x00c41d60 (ret 4)

// EA::Audio mixer handle; vt[0x20] gives the handle killed by the UI effects.
struct IAudioSystem {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void *GetEffectHandle();             // slot 0x20
};

IAudioSystem *GetSystemAT();                     // 0x00a206f0 EA::Audio::GetSystemAT
void KillSetiEffects(uint id, void *handle);     // 0x00435ed0 SP::cSPUISpace::KillSetiEffects

struct cSPSpaceGameBehaviorAbducted : cInteraction {
    void        *mpVtbl4;        // +0x04  second interface vftable
    uint32_t     mField08;       // +0x08
    EntitySlot **mpEntityBlocks; // +0x0c  paged entity table
    uint32_t     mPad10[5];      // +0x10
    uint32_t     mEntityId;      // +0x24  current entity (0x3fffffff = none)
    uint32_t     mPad28[(0x74 - 0x28) / 4];
    uint8_t      mState;         // +0x74
    uint8_t      mPad75[3];
    uint32_t     mField78;       // +0x78
    uint32_t     mField7c;       // +0x7c
    AgentMap     mMap;           // +0x80
    AgentRef     mAgent;         // +0x9c  abducted object

    cSPSpaceGameBehaviorAbducted();              // 0x010326d0
    virtual ~cSPSpaceGameBehaviorAbducted();     // 0x01032730 (scalar deleting dtor)

    void  RefreshAgent();                        // 0x01032330
    bool  AddAgent(void *agent);                 // 0x010323d0 (ret 4)
};

static const uint32_t kInvalidEntity = 0x3fffffff;

// @ 0x010326d0
cSPSpaceGameBehaviorAbducted::cSPSpaceGameBehaviorAbducted()
    : mpVtbl4(&g_vtbl4_cSPSpaceGameBehaviorAbducted),
      mState(1),
      mField78(0),
      mField7c(0)
{
    mMap.Init();
    mAgent.mpObject = 0;
}

// @ 0x01032730
cSPSpaceGameBehaviorAbducted::~cSPSpaceGameBehaviorAbducted()
{
    mpVtbl4 = &g_vtbl4_cSPSpaceGameBehaviorAbducted;
}

// @ 0x01032330
void cSPSpaceGameBehaviorAbducted::RefreshAgent()
{
    if (mEntityId == kInvalidEntity)
        return;

    EntitySlot *slot = &mpEntityBlocks[mEntityId >> 7][mEntityId & 0x7f];
    IEntity *entity = (IEntity *)slot->mpObject;
    if (entity == 0)
        return;

    Beam *beam = (Beam *)entity->GetInterface(0x24630ce);
    if (beam == 0 || beam->mpOwner == 0)
        return;

    SpatialObj *agent;
    void *ownerRef = beam->mpOwner->mpRef;
    if (ownerRef != 0)
        agent = (SpatialObj *)((SpatialObj *)ownerRef)->QueryInterface(0xb033b403);
    else
        agent = 0;

    SpatialObj *old = mAgent.mpObject;
    if (agent == old)
        return;
    if (agent != 0)
        agent->AddRef();
    mAgent.mpObject = agent;
    if (old != 0)
        old->Release();
}

// @ 0x010323d0
bool cSPSpaceGameBehaviorAbducted::AddAgent(void *agent)
{
    bool result = AttachTarget(agent);
    if (mEntityId == kInvalidEntity)
        return result;

    EntitySlot *slot = &mpEntityBlocks[mEntityId >> 7][mEntityId & 0x7f];
    IEntity *entity = (IEntity *)slot->mpObject;
    if (entity == 0)
        return result;

    Beam *beam = (Beam *)entity->GetInterface(0x24630ce);
    if (beam == 0)
        return result;

    bool fadeIn = (mField7c != 1);

    if (agent != 0) {
        cSPCreatureBase *creature = (cSPCreatureBase *)((IEntity *)agent)->GetInterface(0xce9f6639);
        if (creature != 0) {
            creature->InterruptAnimation(0x3cc7eab, -1, 0);
            creature->PlayAnimation(0x3cc7eb4, 1, -1);
            creature->mLoco.FUN_00c44040();
            creature->mLoco.SetLocomotion(new ("Simulator/cAbductionBeamLocomotion")
                                           cAbductionBeamLocomotion(beam, fadeIn));

            cLocomotionRequest request;
            request.mOffset = g_016ded38;
            request.mField20 = 1.0f;
            request.mField60 = g_kGrowRate;
            request.mField64 = g_kAnimRate;
            request.mField68 = g_kRequestRate;
            creature->mLoco.ApplyRequest(&request);

            creature->Detach(1);
            return result;
        }

        cSPPlantAgent *plant = (cSPPlantAgent *)((IEntity *)agent)->GetInterface(0xaeb336b4);
        if (plant == 0) {
            plant = (cSPPlantAgent *)((IEntity *)agent)->GetInterface(0x283d961);
            if (plant == 0)
                goto effects;
            plant->mLoco.SetLocomotion(new ("Simulator/cAbductionBeamLocomotion")
                                        cAbductionBeamLocomotion(beam, fadeIn));
        } else {
            plant->mbAbducted = 1;
            plant->mLoco.FUN_00c44040();
            plant->mLoco.SetLocomotion(new ("Simulator/cAbductionBeamLocomotion")
                                        cAbductionBeamLocomotion(beam, fadeIn));
        }

        {
            cLocomotionRequest request;
            plant->mLoco.ApplyRequest(&request);
        }
    }

effects:
    if (!fadeIn)
        return result;

    IAudioSystem *audio = GetSystemAT();
    if (audio != 0)
        KillSetiEffects(0x66f9a5ae, audio->GetEffectHandle());
    else
        KillSetiEffects(0x66f9a5ae, 0);
    return result;
}

// ---------------------------------------------------------------------------
// SP::cDropToGroundLocomotion::Execute -- slides the owned object towards the
// ground, keeping its scale inside [0, 1] and switching the locomotion off once
// the object is under the water / planet surface.
// ---------------------------------------------------------------------------

struct cDropToGroundLocomotion {
    void Execute(LocoCtx *ctx);        // ret 4
};

// @ 0x01031ef0
void cDropToGroundLocomotion::Execute(LocoCtx *ctx)
{
    SpatialObj *obj = ctx->obj;
    Vec3 *pos = obj->GetPosition();
    Vec3 *vel = obj->GetVelocity();

    float inv = 1.0f / sqrtf(((pos->z * pos->z + pos->y * pos->y) + pos->x * pos->x) + g_kEpsilon);
    float step = ctx->dt * g_kStepScale;
    ctx->vel.x = vel->x - pos->x * inv * step;
    ctx->vel.y = vel->y - pos->y * inv * step;
    ctx->vel.z = vel->z - pos->z * inv * step;

    PlanetModelT *pm = PlanetModel();
    if (pm != 0) {
        Matrix3 orient;
        Vec3 up;
        obj->SetOrientation(pm->BuildSurfaceOrientation2(&orient, pos, obj->GetUp(&up)));
    }

    PlantIface *plant = 0;
    if (obj != 0) {
        plant = (PlantIface *)obj->QueryInterface(0x2dd8c33);
        if (plant != 0) {
            float s = plant->mScale;
            if (s <= 0.0f || 1.0f <= s) {
                plant->mScale = g_kScaleUnset;
            } else {
                float grown = ctx->dt + s;
                plant->mScale = (grown > 1.0f) ? 1.0f : grown;
            }
            goto afterScale;
        }
    }

    if (obj != 0) {
        PlantIface *other = (PlantIface *)obj->QueryInterface(0xaeb336b4);
        if (other != 0) {
            Species *species = PlantSpeciesManager()->GetSpeciesFromID(other->GetSpeciesKey());
            float target = 1.0f;
            P scaleKey = species->GetScaleKey();
            if (scaleKey == (P)0x29c388a)
                target = g_kWaterScale;
            else if (scaleKey == (P)0x3a8be428)
                target = g_2_0f;

            float current = obj->GetScale();
            if (current != target) {
                float grown = ctx->dt * target + current;
                obj->SetScale((grown > target) ? target : grown);
            }
        }
    }

afterScale:
    float water = PlanetModel()->GetWaterHeight();
    Vec3 *cur = obj->GetPosition();
    float radius = PlanetModel()->GetRadiusAt(cur);
    float dist = sqrtf((cur->x * cur->x + cur->y * cur->y) + cur->z * cur->z);

    if (radius > dist) {
        obj->f1f0 = 0;
    } else if (water > dist) {
        obj->f1f0 = 6;
    } else {
        return;
    }

    obj->SetLocomotion(0);
    {
        Vec3 snapped;
        Vec3 *here = obj->GetPosition();
        PlanetModel()->Func_b81630(&snapped, here);
        obj->SetPosition(&snapped);
    }
    {
        cLocomotionRequest request;
        request.mOffset = g_016ded38;
        request.mField20 = 1.0f;
        request.mField60 = g_kGrowRate;
        request.mField64 = g_kAnimRate;
        request.mField68 = g_kRequestRate;
        obj->ApplyLocomotion(&request);
    }
    FUN_00c41d60(obj, &g_016ded38);

    if (plant != 0)
        plant->mScale = g_kScaleUnset;
}
