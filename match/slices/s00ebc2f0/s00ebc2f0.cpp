// Slice s00ebc2f0 -- Effects::PostUpdate (0x00ebcc80) and the entry-vector append
// (0x00ebd190).
//
// PostUpdate is the tail half of Effects::Update (0x00ebdc20, slice s00ebdc20).  Given the mover
// component of the object it runs for -- concretely SP::cSPGameDataUFO, slice s00c37a90, whose
// retail layout is cGameData @0, cLocomotiveObject @0x34, cCombatant @0x508, mUFOType @0x714 --
// it walks the global effect-definition table and, for every definition whose climate mask matches
// the active planet at the object's position, spawns or refreshes that object's feedback event,
// pushes the definition's impulse into the mover and orients the running effect to the surface.
//
// The pass is skipped entirely while the planet is being terraformed.
//
// Per definition (0x54 bytes) the values used are: type (+0x14, must be 0), mask (+0x10), the two
// effect ids (+0x04 / +0x08, picked by the mover's state), the surface window radiusOffset (+0x1c),
// magnitude (+0x38), continuous (+0x3c), scaleByObj (+0x3d), mulNoFlagB (+0x40) and moverScale
// (+0x4c).
//
// Feedback events live in Effects::mEvents (eastl::rbtree<unsigned int,
// eastl::pair<unsigned int const, EA::AutoRefCount<cFeedbackEvent> > >, key = the object key the
// locomotion interface reports).  A lookup that misses plays a new effect through the effects
// manager and registers the handle in the map; either way the handle is add-ref'd while it is
// used and released at the end of the definition.
//
// 0x00ebd190 appends one default-constructed entry: the fast path bumps the end pointer and
// constructs in place (the placement-new null check is still in the original), the slow path
// builds the entry in the frame, hands it to the grow routine (0x00ebc1a0) and destroys it again.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-  (x87 sqrt / 1.0f chains, same module as s00ebdc20)
#include "types.h"
#include <math.h>

inline void* operator new(unsigned int, void* p) { return p; }

#define PV(n) virtual void pv##n();

// ---------------------------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------------------------
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3() {}
};
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quat* q);   // 0x0059c190 (cdecl)

// ---------------------------------------------------------------------------------------------
// engine types shared with the neighbouring effect / waypoint slices
// ---------------------------------------------------------------------------------------------

// 0x00b63890 / 0x00b638b0 -- SP::cGonzagoTimer (reconstructed in slice s00b634d0, 0x20 bytes).
struct cGonzagoTimer {
    void*     mpVtbl;      // +0x00  set by the constructor to 0x01464450
    int       mPad04;      // +0x04
    long long mElapsed;    // +0x08
    long long mBase;       // +0x10
    int       mPad18;      // +0x18
    void*     mGetMs;      // +0x1c
    cGonzagoTimer();       // 0x00b63890
    ~cGonzagoTimer();      // 0x00b638b0
};

// Refcounted effect handle (vtable layout as in slice s00ebd220).
struct EffectHandle {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
    virtual void Stop(int);     // +0x08
};

struct EffectDef;                                // 0x54 bytes, defined below

// Owning handle: starts out null and releases through vtable slot +0x04.
struct RefPtr {
    EffectHandle* mpObject;
    RefPtr() : mpObject(0) {}
    ~RefPtr() { if (mpObject) mpObject->Release(); }
};

// One active-effect record: 0x50 bytes, same layout as the entry vector of slice s00ebd220.
// The two handles are the only members the original constructor initialises.
struct Entry {
    EffectDef*    def;         // +0x00
    int           state;       // +0x04
    float         radius;      // +0x08
    Vec3          pos;         // +0x0c
    Vec3          vel;         // +0x18
    unsigned      pad24;       // +0x24
    cGonzagoTimer timer;       // +0x28
    RefPtr        effect1;     // +0x48
    RefPtr        effect2;     // +0x4c
};

// begin / end / capacity of the entry array (grow = 0x00ebc1a0, shared instantiation).
struct EntryVec {
    Entry* mpBegin;   // +0x00
    Entry* mpEnd;     // +0x04
    Entry* mpCap;     // +0x08

    void grow(unsigned end, unsigned element);   // 0x00ebc1a0
    void Append();                               // 0x00ebd190
};

// ---------------------------------------------------------------------------------------------
// planet / effect data
// ---------------------------------------------------------------------------------------------
struct PlanetRecord {
    unsigned char pad[0xb0];
    float humidity;                    // +0xb0
    float temperature;                 // +0xb4
};
PlanetRecord* GetActivePlanetRecord();              // 0x010212a0

struct PlanetModel {
    bool   IsWater(const Vec3* pos);                        // 0x00b7e3e0 (ret 4)
    Vec3*  SnapToSurface(Vec3* out, const Vec3* in);         // 0x00b81630 (ret 8)
    Quat*  BuildSurfaceOrientation(Quat* out, const Vec3* pos);  // 0x00b7f190 (ret 8)
};
PlanetModel* GetPlanetModel();                      // 0x00b3d350

struct TerraformingManager {
    int GetState();                                 // 0x00bbc670
};
TerraformingManager* GetTerraformingManager(PlanetRecord* planet);   // 0x00b3d430

struct EffectDef {                       // 0x54 bytes (names shared with slice s00ebdc20)
    unsigned      pad00;
    unsigned      effectIdA;             // +0x04
    unsigned      effectIdB;             // +0x08
    unsigned      animId;                // +0x0c
    unsigned      mask;                  // +0x10
    int           type;                  // +0x14 : 0 = this pass
    float         radius;                // +0x18
    float         radiusOffset;          // +0x1c : height window above the surface
    float         scale;                 // +0x20
    unsigned      pad24[3];
    float         startDelay;            // +0x30
    float         lifetime;              // +0x34
    float         magnitude;             // +0x38
    unsigned char continuous;            // +0x3c
    unsigned char scaleByObj;            // +0x3d
    unsigned char pad3e[2];
    float         mulNoFlagB;            // +0x40
    float         mulWithAnim;           // +0x44
    float         accel;                 // +0x48
    float         moverScale;            // +0x4c
    unsigned      pad50;
};
struct EffectDefTable {
    unsigned   pad00[6];
    EffectDef* begin;                    // +0x18
    EffectDef* end;                      // +0x1c
};
EffectDefTable* GetEffectDefTable();                // 0x010408b0

// ---------------------------------------------------------------------------------------------
// feedback events
// ---------------------------------------------------------------------------------------------
struct cFeedbackEvent {
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    virtual void Stop(int reason);                // +0x08
    virtual void v3();
    virtual bool IsValid();                       // +0x10
    virtual void v5();
    virtual void SetTransform(const void* xform);  // +0x18
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(const AutoRefCount& rhs);   // 0x00ac9480 (release old, add-ref new)
};

struct EffectsManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool PlayEffect(unsigned id, int flags, cFeedbackEvent** out);   // +0x2c
};
EffectsManager* GetEffectsManager();                // 0x0067ddd0

// eastl red-black tree node: right +0, left +4, parent +8, colour +0xc, payload at +0x10.
struct RbtreeNodeBase {
    RbtreeNodeBase* mpNodeRight;      // +0x00
    RbtreeNodeBase* mpNodeLeft;       // +0x04
    RbtreeNodeBase* mpNodeParent;     // +0x08
    char            mColor;           // +0x0c
    char            pad0d[3];         // +0x0d
};
struct FeedbackNode {
    FeedbackNode*   mpNodeRight;      // +0x00
    FeedbackNode*   mpNodeLeft;       // +0x04
    FeedbackNode*   mpNodeParent;     // +0x08
    char            mColor;           // +0x0c
    char            pad0d[3];         // +0x0d
    unsigned        mnKey;            // +0x10
    cFeedbackEvent* mpEvent;          // +0x14
};

// eastl::rbtree<unsigned int> -- the set of keys touched this frame (shared with Bake).
struct WorldMap {
    unsigned       mCompare;          // +0x00
    RbtreeNodeBase mAnchor;           // +0x04 sentinel
    unsigned       mnSize;            // +0x14
    unsigned       mAllocator;        // +0x18
    struct InsertResult {             // pair<iterator, bool>
        void* mpNode;                 // +0x00
        bool  mbInserted;             // +0x04
        char  pad05[3];
    };
    void InsertUnique(InsertResult* out, const unsigned* key, int reserved);   // 0x00ebbe70
};

// eastl::rbtree<unsigned int, eastl::pair<unsigned int const,
//     EA::AutoRefCount<`anonymous namespace'::cFeedbackEvent> > >
struct FeedbackEventMap {
    unsigned       mCompare;          // +0x00
    RbtreeNodeBase mAnchor;           // +0x04 sentinel
    unsigned       mnSize;            // +0x14
    unsigned       mAllocator;        // +0x18

    FeedbackNode* End() { return (FeedbackNode*)&mAnchor; }
    void Find(FeedbackNode** out, const unsigned* key);                   // 0x00e5c780
    AutoRefCount<cFeedbackEvent>* Insert(const unsigned* key,
                                         const AutoRefCount<cFeedbackEvent>* value);  // 0x00dd85c0
};

// ---------------------------------------------------------------------------------------------
// the object this pass runs for
// ---------------------------------------------------------------------------------------------
// Locomotion interface embedded in the mover at +0x34 (cLocomotiveObject).
struct ILocomotive {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();             // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    virtual unsigned GetEffectKey();               // +0xac
};

// Combat interface embedded in the mover at +0x508 (cCombatant).
struct ICombatant {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void ApplyImpulse(float mag, int a, int b, const Vec3* dir, int c);   // +0x18
    PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    PV(18) PV(19) PV(20) PV(21)
    virtual float GetScale();                      // +0x58
};

// Mover component (SP::cSPGameDataUFO in this instantiation).
struct Mover {
    unsigned mData[0x714 / 4];                     // +0x000
    int      state;                                // +0x714 mUFOType: 0 / 3 = parked
    void ApplyVelocity(const Vec3& dir, float scale);   // 0x00c37f70
};

// Transform-update message (0x38 bytes); the constructor is 0x00434040 (slice s00433800).
struct XformMsg {
    unsigned short flags;      // +0x00
    unsigned short count;      // +0x02
    Vec3           pos;        // +0x04
    float          scale;      // +0x10
    Matrix3        rot;        // +0x14
    XformMsg();                // 0x00434040
    void SetPos(const Vec3& v) { pos = v; flags |= 4; ++count; }
    void SetRot(const Matrix3& m) { rot = m; flags |= 2; ++count; }
};

struct Effects {
    unsigned         pad00[2];     // +0x00
    Entry*           mpBegin;      // +0x08
    Entry*           mpEnd;        // +0x0c
    unsigned         pad10[8];     // +0x10
    WorldMap         mWorlds;      // +0x30
    FeedbackEventMap mEvents;      // +0x4c

    void PostUpdate(Mover* mover, float dt);   // 0x00ebcc80
};

// ---------------------------------------------------------------------------------------------
// @ 0x00ebcc80
void Effects::PostUpdate(Mover* mover, float dt)
{
    // No effects while the planet is being terraformed.
    PlanetRecord* planet = GetActivePlanetRecord();
    if (GetTerraformingManager(planet)->GetState() != 0)
        return;

    ILocomotive* loco = (ILocomotive*)((char*)mover + 0x34);
    ICombatant*  combat = (ICombatant*)((char*)mover + 0x508);

    const Vec3* pos = loco->GetPosition();
    bool water = GetPlanetModel()->IsWater(pos);

    // Climate mask: water band plus the temperature and humidity bands.
    unsigned flags = water ? 0x10 : 0x08;
    flags |= planet->temperature > 0.8f ? 1 : (0.2f > planet->temperature ? 4 : 2);
    flags |= planet->humidity > 0.8f ? 0x20 : (0.2f > planet->humidity ? 0x80 : 0x40);

    bool parked = (mover->state == 0 || mover->state == 3);
    float objScale = combat->GetScale();

    EffectDefTable* table = GetEffectDefTable();
    EffectDef* def = table->begin;
    int count = (int)(table->end - table->begin);

    for (int i = 0; i < count; i++, def++)
    {
        if (def->type != 0 || (def->mask & flags) != flags)
            continue;

        // Height of the object above the planet surface.
        float lenSq = pos->x * pos->x + pos->y * pos->y + pos->z * pos->z;
        Vec3 surface;
        GetPlanetModel()->SnapToSurface(&surface, pos);
        float surfLenSq = surface.x * surface.x
                        + surface.y * surface.y
                        + surface.z * surface.z;
        float dist = sqrtf(lenSq) - sqrtf(surfLenSq);
        if (!(def->radiusOffset > dist))
            continue;

        // Unit direction from the object towards the planet centre.
        float inv = -1.0f / sqrtf(lenSq);
        Vec3 dir;
        dir.x = pos->x * inv;
        dir.y = pos->y * inv;
        dir.z = pos->z * inv;

        float scale = def->magnitude;
        if (def->scaleByObj)
            scale *= objScale;
        if (!parked)
            scale *= def->mulNoFlagB;

        if (def->continuous && scale != 0.0f)
            combat->ApplyImpulse(scale * dt, -1, 8, &dir, 0);

        if (def->moverScale != 0.0f)
        {
            float n = 1.0f / sqrtf(lenSq);
            Vec3 vel;
            vel.x = pos->x * (def->moverScale * n);
            vel.y = pos->y * (def->moverScale * n);
            vel.z = pos->z * (def->moverScale * n);
            mover->ApplyVelocity(vel, dt);
        }

        unsigned key = loco->GetEffectKey();

        // Record the key in the touched-keys set.
        WorldMap::InsertResult touched;
        mWorlds.InsertUnique(&touched, &key, 0);

        // Look the feedback event up; a miss plays a new effect for the object's state.
        cFeedbackEvent* ev = 0;
        FeedbackNode* node;
        mEvents.Find(&node, &key);
        if (node != mEvents.End())
        {
            ev = node->mpEvent;
            if (ev)
                ev->AddRef();
        }
        else
        {
            unsigned id = (mover->state == 0) ? def->effectIdA : def->effectIdB;
            EffectsManager* mgr = GetEffectsManager();

            // The AutoRefCount temporary starts out empty (the compiler keeps its
            // release in the original, where it is always a no-op).
            AutoRefCount<cFeedbackEvent> created;
            created.mpObject = 0;

            if (mgr->PlayEffect(id, 0, &created.mpObject))
            {
                AutoRefCount<cFeedbackEvent>* slot = mEvents.Insert(&key, &created);
                *slot = created;
            }

            // One-shot definitions play once, at full magnitude, when the event is created.
            if (!def->continuous && scale != 0.0f)
                combat->ApplyImpulse(scale, -1, 8, &dir, 0);

            ev = created.mpObject;
            if (!ev)
                continue;
        }

        if (!ev->IsValid())
            ev->Stop(0);

        XformMsg xf;
        xf.SetPos(*pos);

        Quat quat;
        Quat* q = GetPlanetModel()->BuildSurfaceOrientation(&quat, pos);
        Matrix3 rot;
        xf.SetRot(*Matrix3FromQuaternion(&rot, q));

        ev->SetTransform(&xf);
        ev->Release();
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00ebd190
void EntryVec::Append()
{
    Entry* end = mpEnd;
    if (end < mpCap)
    {
        mpEnd = end + 1;
        new (end) Entry();
        return;
    }

    Entry value;
    grow((unsigned)mpEnd, (unsigned)&value);
}
