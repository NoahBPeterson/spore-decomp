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
    void Assign(const Matrix3& src);                  // 0x0041cb40  (cSPMatrix3::Assign)
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
    virtual void* GetComponent(unsigned id);       // +0x5c
};

// Mover component (SP::cSPGameDataUFO in this instantiation).
struct Mover {
    unsigned mData[0x714 / 4];                     // +0x000
    int      state;                                // +0x714 mUFOType: 0 / 3 = parked
    void ApplyVelocity(const Vec3& dir, float scale);   // 0x00c37f70
    float GetHeight();                                  // 0x00c3be10
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
    void CreateToolEffect(ICombatant* target, float scale);   // 0x00ebc2f0
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

// ---------------------------------------------------------------------------------------------
// 0x00ebc2f0 -- effects for a tool being used on an object
//
// arg 1 is the object the tool acts on, arg 2 the tool's strength.  Four named components are
// fetched from the object (two of the lookups are the same interface), the surface anchor points
// inside the component's box are collected through a model-manager query, and for every anchor a
// feedback event is spawned or refreshed.  Per-anchor property values from the anchor's property
// list scale the magnitude and, for UFOs, drive an extra velocity kick; creatures additionally get
// their own effect set spawned.
// ---------------------------------------------------------------------------------------------

// A property-list value (0x14 bytes): the payload lives inline at +0x00 unless bit 0x30 of the
// flags says +0x00 holds a pointer to it.  Type ids used here: 0x0d = float, 0x01 = byte.
struct Variant {
    int            mData0;    // +0x00 inline payload, or pointer to it
    int            mData4;    // +0x04
    int            mData8;    // +0x08
    int            mDataC;    // +0x0c
    unsigned short mFlags;    // +0x10
    unsigned short mTypeId;   // +0x12
    float* GetFloat();        // 0x0041ea70
};

// The float/byte payload of a variant, whether stored inline or behind +0x00.
inline void* VariantPayload(Variant* value)
{
    return (value->mFlags & 0x30) ? *(void**)&value->mData0 : (void*)value;
}

// Named property table (cNamedPropertyList); slot +0x24 fetches the variant for an id.
struct PropertyList {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetVariant(unsigned id, Variant** out);        // +0x24
};

// Axis-aligned box: min +0x00, max +0x0c.
struct Box {
    Vec3 min;   // +0x00
    Vec3 max;   // +0x0c
};

// Component returned by ICombatant::GetComponent(0x1186577); supplies the anchor box.
struct IEffectSource {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21) PV(22) PV(23) PV(24) PV(25)
    virtual const Box* GetCapsule();                // +0x68
    virtual Box* GetBox(Box* out);                  // +0x6c
};

// One anchor point produced by the query (+0x0c world position, +0x90 property list).
struct ICandidate {
    unsigned      mPad00[3];                    // +0x00
    Vec3          pos;                          // +0x0c
    unsigned      mPad18[(0x90 - 0x18) / 4];    // +0x18
    PropertyList* mpProperties;                 // +0x90
};

// Bit filter handed to the query: 0x40 bits plus two one-byte flags.
struct ObjectFilter {
    unsigned      mBits[5];       // +0x00
    unsigned char mB14;           // +0x14
    unsigned char mB15;           // +0x15
};

// 16-entry vector of anchors: header +0x00, inline storage +0x18.
struct CandidateVec {
    ICandidate** mpBegin;         // +0x00
    ICandidate** mpEnd;           // +0x04
    ICandidate** mpCap;           // +0x08
    unsigned     mPad0c;          // +0x0c
    ICandidate** mpBuffer;        // +0x10
    unsigned     mPad14;          // +0x14
    ICandidate*  mInline[16];     // +0x18
};

// In/out context handed to the query (the key instance out slot is reused afterwards).
struct QueryContext {
    void*    mpKeyInstance;       // +0x00
    unsigned mKey;                // +0x04 : rbtree key = the anchor pointer
    void*    mpCreature;          // +0x08
    void*    mpUfo;               // +0x0c
};

struct ICandidateQuery {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13)
    virtual void Query(QueryContext* ctx, float height, CandidateVec* out,
                       const ObjectFilter* filter);           // +0x38
};

struct ModelManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual ICandidateQuery* GetQuery(unsigned id);                  // +0x1c
    PV(8) PV(9)
    virtual unsigned GetFilterIndex(unsigned id, int param);         // +0x28
};
ModelManager* GetModelManager();                                     // 0x0067dd80

// Creature component returned by ICombatant::GetComponent(0xce9f6639).
struct Creature {
    unsigned char mPad000[0x137];              // +0x000
    unsigned char mB137;                       // +0x137
    unsigned char mPad138[0xb58 - 0x138];      // +0x138
    unsigned      mB58;                        // +0xb58
    void SpawnEffects(int a, int b, int c, int d, float e, int f, int g, void* h,
                      int i, int j, int k);                        // 0x00c0bf10
};

// Resolves a property id to a key instance (free function: property list is a stack argument).
void GetPropertyAsKeyInstance(PropertyList* props, unsigned id, void** out);  // 0x006a12a0

// EARTL / EASTL allocator deallocate (operator delete).
void EASTL_allocator_deallocate(void* p);                                     // 0x00f47380

// Vectors the transform message's inlined constructor copies (runtime-initialised globals).
extern Vec3    g_16c7440;    // 0x016c7440  zero vector
extern Matrix3 g_16c741c;    // 0x016c741c  identity matrix

// Same layout as XformMsg, but without the out-of-line constructor: 0x00ebc2f0 builds the default
// message inline instead of calling 0x00434040.
struct XformMessage {
    unsigned short flags;      // +0x00
    unsigned short count;      // +0x02
    Vec3           pos;        // +0x04
    float          scale;      // +0x10
    Matrix3        rot;        // +0x14
    void SetPos(const Vec3& v) { pos = v; flags |= 4; ++count; }
    void SetRot(const Matrix3& m) { rot = m; flags |= 2; ++count; }
};

// ---------------------------------------------------------------------------------------------
// @ 0x00ebc2f0
void Effects::CreateToolEffect(ICombatant* target, float scale)
{
    IEffectSource* source = 0;
    Mover*         ufo = 0;
    Creature*      creature = 0;

    if (target != 0)
    {
        target->GetComponent(0x1186577);                       // interface is claimed twice
        ufo = (Mover*)target->GetComponent(0xb033b403);
        creature = (Creature*)target->GetComponent(0xce9f6639);
        source = (IEffectSource*)target->GetComponent(0x1186577);
    }

    // Centre of the source box.
    Box box;
    source->GetBox(&box);
    Vec3 mid;
    mid.x = (box.min.x + box.max.x) * 0.5f;
    mid.y = (box.min.y + box.max.y) * 0.5f;
    mid.z = (box.min.z + box.max.z) * 0.5f;

    // Half the capsule height above the surface.
    const Box* capsule = source->GetCapsule();
    float height = (capsule->max.z - capsule->min.z) * 0.5f;

    bool isZero = false;
    bool parked = false;
    if (ufo != 0)
    {
        int state = ufo->state;
        isZero = (state == 0);
        parked = (state == 0 || state == 3);
        height = ufo->GetHeight();
    }

    if (creature != 0)
    {
        if (creature->mB137 == 0)
            return;
        unsigned flags = creature->mB58;
        isZero = (flags >> 9) & 1;
        parked = isZero || ((flags >> 8) & 1) != 0;
    }

    ModelManager* modelMgr = GetModelManager();
    unsigned filterIndex = modelMgr->GetFilterIndex(0x6086e65, 0);
    ICandidateQuery* query = modelMgr->GetQuery(0x3fbae24);

    ObjectFilter filter;
    filter.mBits[0] = 0;
    filter.mBits[1] = 0;
    filter.mBits[2] = 0;
    filter.mBits[3] = 0;
    filter.mBits[4] = 0;
    filter.mB14 = 1;
    filter.mB15 = 0;
    if (filterIndex < 0x40)
        filter.mBits[filterIndex >> 5] |= 1u << (filterIndex & 0x1f);

    CandidateVec vec;
    vec.mpBegin = vec.mInline;
    vec.mpEnd = vec.mInline;
    vec.mpCap = vec.mInline + 16;
    vec.mpBuffer = vec.mInline;

    QueryContext ctx;
    ctx.mpKeyInstance = 0;
    ctx.mKey = 0;
    ctx.mpCreature = creature;
    ctx.mpUfo = ufo;

    query->Query(&ctx, height, &vec, &filter);

    if (vec.mpBegin != vec.mpEnd)
    {
        Quat quat;
        Quat* orient = GetPlanetModel()->BuildSurfaceOrientation(&quat, &mid);
        Matrix3 rot;
        Matrix3FromQuaternion(&rot, orient);

        // Tool effects come in a parked and an active flavour.
        unsigned keyId = isZero ? 0x0687b789u : 0x06932a26u;

        for (ICandidate** it = vec.mpBegin; it != vec.mpEnd; ++it)
        {
            ICandidate* cand = *it;

            // Record the anchor in the touched set.
            WorldMap::InsertResult touched;
            ctx.mKey = (unsigned)cand;
            mWorlds.InsertUnique(&touched, &ctx.mKey, 0);

            // Direction from the box centre towards the anchor (or away from the planet when the
            // anchor sits on the centre itself).
            Vec3 delta;
            delta.x = cand->pos.x - mid.x;
            delta.y = cand->pos.y - mid.y;
            delta.z = cand->pos.z - mid.z;
            // The original evaluates this in x87 (double) and rounds once to float.
            float distance = (float)sqrt(delta.x * delta.x + delta.y * delta.y
                                         + delta.z * delta.z);

            Vec3 dir;
            if (distance <= 0.0000152587890625f)          // 2^-16
            {
                float inv = (float)(1.0 / sqrt(mid.x * mid.x + mid.y * mid.y
                                               + mid.z * mid.z));
                dir.x = -(mid.x * inv);
                dir.y = -(mid.y * inv);
                dir.z = -(mid.z * inv);
            }
            else
            {
                float inv = 1.0f / distance;
                dir.x = delta.x * inv;
                dir.y = delta.y * inv;
                dir.z = delta.z * inv;
            }

            float objectScale = target->GetScale();

            // Per-anchor tuning values.
            unsigned char scaleByInput = 0;        // 0x7a143d4
            unsigned char scaleByObject = 0;       // 0x7a143d8
            float noParkMul = 1.0f;                // 0x7a143db
            float creatureMul = 1.0f;              // 0x7a14405
            float magnitude = 0.0f;                // 0x61329ab

            PropertyList* props = cand->mpProperties;
            Variant* value;
            if (props != 0 && props->GetVariant(0x61329ab, &value) && value->mTypeId == 0x0d)
                magnitude = *(float*)VariantPayload(value);
            if (props != 0 && props->GetVariant(0x7a143d4, &value) && value->mTypeId == 0x01)
                scaleByInput = *(unsigned char*)VariantPayload(value);
            if (props != 0 && props->GetVariant(0x7a143d8, &value) && value->mTypeId == 0x01)
                scaleByObject = *(unsigned char*)VariantPayload(value);
            if (props != 0 && props->GetVariant(0x7a143db, &value) && value->mTypeId == 0x0d)
                noParkMul = *(float*)VariantPayload(value);
            if (props != 0 && props->GetVariant(0x7a14405, &value) && value->mTypeId == 0x0d)
                creatureMul = *(float*)VariantPayload(value);

            if (scaleByInput)
                magnitude *= scale;
            if (scaleByObject)
                magnitude *= objectScale;
            if (!parked)
                magnitude *= noParkMul;
            if (creature != 0)
                magnitude *= creatureMul;

            if (scaleByInput && magnitude != 0.0f)
                target->ApplyImpulse(magnitude, -1, 8, &dir, 0);

            // UFOs also get a velocity kick scaled by their own property.
            if (ufo != 0 && props != 0)
            {
                if (props->GetVariant(0x60b0498, &value) && value->mTypeId == 0x0d)
                {
                    float kick = *value->GetFloat();
                    if (kick != 0.0f)
                    {
                        Vec3 vel;
                        kick = -kick;
                        vel.x = dir.x * kick;
                        vel.y = dir.y * kick;
                        vel.z = dir.z * kick;
                        ufo->ApplyVelocity(vel, scale);
                    }
                }
            }

            // Creatures spawn their own effect set at the anchor.
            if (creature != 0)
            {
                void* keyInstance = 0;
                GetPropertyAsKeyInstance(props, 0x7a13cca, &keyInstance);
                if (keyInstance != 0)
                    creature->SpawnEffects(0, 0x20000, 0x1000, 0, 1.0f, 0, 0x4000000,
                                           keyInstance, 0, 0, 0);
            }

            GetPropertyAsKeyInstance(props, keyId, &ctx.mpKeyInstance);
            if (ctx.mpKeyInstance == 0)
                continue;

            // Look the feedback event up; a miss plays a new effect and registers it.
            cFeedbackEvent* ev = 0;
            FeedbackNode* node;
            mEvents.Find(&node, &ctx.mKey);
            if (node != mEvents.End())
            {
                ev = node->mpEvent;
                if (ev)
                    ev->AddRef();
            }
            else
            {
                EffectsManager* effects = GetEffectsManager();

                AutoRefCount<cFeedbackEvent> created;
                created.mpObject = 0;

                if (effects->PlayEffect((unsigned)ctx.mpKeyInstance, 0, &created.mpObject))
                {
                    AutoRefCount<cFeedbackEvent>* slot = mEvents.Insert(&ctx.mKey, &created);
                    *slot = created;
                }

                if (!scaleByInput && magnitude != 0.0f)
                    target->ApplyImpulse(magnitude, -1, 8, &dir, 0);

                ev = created.mpObject;
                if (!ev)
                    continue;
            }

            if (!ev->IsValid())
                ev->Stop(0);

            XformMessage xf;
            xf.flags = 0;
            xf.count = 0;
            xf.pos = g_16c7440;
            xf.scale = 1.0f;
            xf.rot.Assign(g_16c741c);
            xf.SetPos(mid);
            xf.SetRot(rot);

            ev->SetTransform(&xf);
            ev->Release();
        }
    }

    if (vec.mpBegin != 0 && vec.mpBegin != vec.mpBuffer)
        EASTL_allocator_deallocate(vec.mpBegin);
}
