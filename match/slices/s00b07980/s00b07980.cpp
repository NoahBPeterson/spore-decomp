// FUN_00b07980 @ 0x00B07980 (1564 bytes, __thiscall, ret 0x14, 5 stack args).
//
// Places the plants of one spawn request on a planet (Claude-coined names; the manager class is unrecovered,
// it is the same one as in s00b08670 with the object list at +0x1b905c). Flow:
//   - bail out unless both low bits of the manager's mode word (+0x1ba18c) are set;
//   - resolve the request to a species (GetA()->Lookup(req), GetB()->GetSpeciesFromID) and refuse the
//     0x3a8be428 kind (species->GetKind());
//   - optionally (flag) spawn a visual effect and queue a 0x20-byte effect record in the manager's vector;
//   - FindExisting(range, key, kind, count, p5) (then p6) looks for already-placed plants; if some exist the
//     loop re-seats each of them (snap to the planet surface, push the position to the object's
//     transform listener, number its slots), otherwise a fresh object is created per element and set up
//     with FUN_00b07560 (on failure the noun is removed again);
//   - the new/reseated objects are reported to param_4 (Group::Add) or, for the whole range, to the
//     last tried group (Group::AddRange).
// Returns 1 when the species was valid.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
#include "types.h"

struct Vector3 { float x, y, z; };

template<class T> inline T& At(void* p, int off) { return *(T*)((char*)p + off); }

struct Req            // param_2 (spawn request)
{
    uint32_t count;       // +0x00
    uint32_t pad4;
    uint8_t* elems;       // +0x08  array of count 0x4c-byte transforms
    uint32_t pad0c;       // +0x0c
    void*    target10;    // +0x10  object that receives the range key at +0xd4
    uint32_t pad14[3];    // +0x14
    void*    key;         // +0x20
    uint32_t pad24[3];    // +0x24
    uint32_t field30;     // +0x30
};

// cSPTransform (0x4c bytes per request element)
struct Xform
{
    uint16_t flags;
    uint16_t counter;
    Vector3  pos;
    uint32_t pad[0x4c / 4 - 5];
    Xform& operator=(const Xform&);                  // 0x537dc0 (thiscall, ret 4)
};

struct XformMsg                                      // ctor 0x434040
{
    uint16_t flags;
    uint16_t counter;
    Vector3  pos;
    uint32_t pad[10];
    XformMsg();
};

struct IVisualEffect
{
    virtual int AddRef();
    virtual int Release();
    virtual void Slot2(int);                         // +0x08
};

struct VfxRef                                        // EA::AutoRefCount<cIVisualEffect>
{
    IVisualEffect* p;
    IVisualEffect** AsPPTypeParam();                 // 0xa16f40
    VfxRef& assign(VfxRef*);                         // 0xac9480 (this = dst, arg = &src, ret 4)
};

struct EffectsManager
{
    virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
    virtual void pv4(); virtual void pv5(); virtual void pv6(); virtual void pv7();
    virtual void pv8(); virtual void pv9(); virtual void pv10();
    virtual bool CreateEffect(uint32_t a, uint32_t b, IVisualEffect** out);   // +0x2c
};

struct Model                                         // species->+0xa0
{
    uint32_t GetCount();                             // 0x4d9070 (end-begin of the vector at +0x810)
};

struct Species
{
    virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
    virtual void pv4(); virtual void pv5();
    virtual const Vector3* GetPosition();            // +0x18
    uint32_t GetKind();                              // 0xb8f860
    Model* GetModelWorld();                          // 0xad2830 (returns [this+0xa0])
};

struct SpeciesMgr { Species* GetSpeciesFromID(uint32_t id); };   // 0xb90410 (ret 4)
struct IdLookup   { uint32_t Lookup(Req* req); };                // 0xb2b1e0 (ret 4)

struct XformListener
{
    virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
    virtual void pv4(); virtual void pv5();
    virtual void Slot6(XformMsg*);                   // +0x18
    virtual void pv7();
    virtual void Slot8(XformMsg*);                   // +0x20
};

struct Plant                                         // object created by Mgr::NewPlant (0xb02060)
{
    virtual int AddRef();
    virtual int Release();
};

struct Item                                          // result of FUN_00afff30
{
    // +0x0c Xform, +0x10 Vector3, +0x48/+0x4c ints, +0x6c float, +0x78 int
    uint32_t pad[0xc / 4];
};

struct PlanetModel
{
    Vector3* DirectionToSurfacePosition(Vector3* out, const Vector3* in);   // 0xb815a0 (ret 8)
    void     FUN_00b88420();                                                 // 0xb88420
    uint32_t GetAverageRadius(const Vector3* v);                             // 0xb7e840 (ret 4)
};

struct NounManager { void RemoveNoun(Plant* p); };   // 0xb225d0 (ret 4)

struct RBNode { uint32_t pad[6]; Plant* value; };    // value at +0x18
struct Range  { RBNode* begin; RBNode* end; };

struct Triple { void* key; uint32_t kind; Plant* plant; };

struct Group
{
    void Add(uint32_t* out, Triple* t, bool b);                // 0xb04f70 (ret 0xc)
    void AddRange(uint32_t* out, RBNode* first, RBNode* last); // 0xb04ed0 (ret 0xc)
};

struct EffectRec                                     // 0x20-byte record queued at manager +0x160e8
{
    uint32_t total;
    uint32_t pad04;
    void*    key;
    uint32_t kind;
    VfxRef   vfx;
    uint32_t z14, z18, pad1c;
    void Reset();                                    // 0xb00150
};
struct EffectVec
{
    void push_back(EffectRec* r);                    // 0xb06de0 (ret 4)
};
struct EffectBook                                    // *(mgr+0x16500)
{
    uint32_t pad[0x24 / 4];
    uint32_t f24, f28;
    uint32_t FUN_00703d50(float f, void* a, void* b);   // 0x703d50 (ret 0xc)
    void     Remove(uint32_t id);                       // 0x702da0 (ret 4)
};

struct Bucket { uint32_t first, second; };

// ---- the plant event handlers (0x00b07fa0 / 0x00b08260) ----

struct SlotBits {                                    // per-slot mask of a placed object (0xb04c20 result)
    char     pad00[0x48];
    uint32_t mMaskLo;                                // +0x48
    uint32_t mMaskHi;                                // +0x4c
};

struct FeatureLookup {                               // one 0x5c-byte feature entry of an effect
    uint32_t mSlotId38;                              // +0x38
    char     pad3c[0x5c - 0x3c];
};
struct FeatureVec {                                  // the feature vector at effect+0x144
    FeatureLookup* mBegin;                           // +0x00
    uint32_t Size();                                 // 0x00a70310
};

struct VfxOwner {                                    // the visual effect behind EffectRec::vfx.p
    virtual int  AddRef();                           // +0x00
    virtual int  Release();                          // +0x04
    virtual void Slot2(int);                         // +0x08
    virtual void Slot3(int);                         // +0x0c
};

struct PlantObject {                                 // a placed plant (RBNode::value)
    virtual int  AddRef();                           // +0x00
    virtual int  Release();                          // +0x04
    char     pad04[0x4c - 4];
    void*    mpKey;                                  // +0x4c
    uint32_t mField50;                               // +0x50
    uint32_t mIndex54;                               // +0x54
    Xform    mXform58;                               // +0x58
    char     padA0[0xa4 - 0x58 - sizeof(Xform)];
    void*    mpMatrixA4;                             // +0xa4  array of 0x38-byte world matrices
    char     padA8[0x19c - 0xa8];
    uint32_t* mpSlotIds;                             // +0x19c
    uint32_t* mpSlotIdsEnd;                          // +0x1a0
    char     pad1a4[0x1c4 - 0x1a4];
    VfxOwner* mpVfx;                                 // +0x1c4
    uint32_t mField1c8;                              // +0x1c8
    uint32_t CurEntryBits();                         // 0x00b058f0
};

struct PlantRange {                                  // the container at Mgr+0x34 (count at +0x14)
    char     pad00[0x14];
    uint32_t mCount;                                 // +0x14
    void     FindRange(Range* out, void** key);      // 0x00b02430 (ret 8)
    void     AddRange(uint32_t* out, RBNode* first, RBNode* last);   // 0x00b04ed0 (ret 0xc)
};

struct MapNode {                                     // a node of the map at Mgr+0x8080
    char     pad00[0x18];
    void*    mpKey;                                  // +0x18
    char     pad1c[0xc];
    VfxOwner* mpValue;                               // +0x28
    char     pad2c[4];
    void*    mpField30;                              // +0x30
};
struct KeyMap {                                      // eastl::rbtree<key, AutoRefCount<...>>
    uint32_t pad00;                                  // +0x00
    void     find(MapNode** out, void** key);        // 0x00e5c780 (ret 8)
    void     F05c30(void* out, void* value);         // 0x00b05c30 (ret 8)
    MapNode* end() { return (MapNode*)((char*)this + 4); }
};

struct HolderObject {                                // a sim object holding the slot shadow at +0x64
    virtual int  AddRef();                           // +0x00
    virtual int  Release();                          // +0x04
    char     pad04[0x64 - 4];
    VfxOwner* mpField64;                             // +0x64
};
struct PtrVec { void** mBegin; void** mEnd; };       // the pointer vector at Mgr+0x16504

struct BucketObject {                                // an entry scanned in GetBucket's bucket
    char pad00[0x78];
    int  mSlot78;                                    // +0x78
};

void __cdecl FUN_00b057b0(Bucket* b);                // 0xb057b0

struct PlantEffectVec {                              // the effect-record vector at Mgr+0x160e8
    EffectRec* mBegin;                               // +0x00
    EffectRec* mEnd;                                 // +0x04
    void F05d50(EffectRec* rec);                     // 0x00b05d50 (ret 4)
};

struct SimEvent {                                    // the record handed to the handlers
    uint32_t mKey;                                   // +0x00  key / slot limit
    uint32_t mField04;                               // +0x04
    void*    mpTransforms;                           // +0x08  array of 0x4c-byte cSPTransform records
    uint32_t mField0c;                               // +0x0c
    void*    mpTarget;                               // +0x10  object receiving the range key
};
struct SimTarget {                                   // *SimEvent::mpTarget
    char     pad00[0xd4];
    uint32_t mRangeKey;                              // +0xd4
};

struct RecordBuilder {                               // the 0x20-byte temporary map record
    uint32_t mField00;                               // +0x00  key
    char     pad04[0x1c];
    void*    Build(void* key, void* arg);            // 0x00b02480 (ret 8)
    void     Reset();                                // 0x00b00150
};

struct RefCollector {                                // the 0x18-byte temporary that keeps references
    void* mpData[6];
    void Add(void* p);                               // 0x00b01d30 (ret 4)
};

struct SlotOwner {                                   // the object behind the slot shadow
    void SetShadow(uint32_t id, float z);            // 0x00a887b0 (ret 8)
};
struct RecordTail {                                  // EffectRec+0x14
    void  F07d4590(void* key);                       // 0x007d4590 (ret 4)
};

struct XformOps { Xform* Assign(const void* src); };  // 0x537dc0

void* __cdecl translateTransform(void* out, void* src, void* xform);   // 0x6271a0
void  __cdecl FUN_00b043b0(void* out, MapNode* node);                  // 0x00b043b0
uint64_t __cdecl __allshl(uint64_t value, uint32_t count);             // 0x11e06e0

struct Mgr
{
    bool     FindExisting(Range* out, void* key, uint32_t kind, uint32_t count, Group* g);          // 0xb034f0 (ret 0x14)
    Bucket*  GetBucket(void* key, uint32_t kind);                                                    // 0xb04ba0 (ret 8)
    Plant*   NewPlant();                                                                             // 0xb02060
    void     InitBook();                                                                             // 0xb02120
    bool     SetupPlant(Plant* p, Species* s, Xform* elem, int isEmpty, int notFlag, int* idx, VfxRef* vfx); // 0xb07560 (ret 0x1c)
    bool     FUN_00b07980(Req* req, bool flag, Group* g4, Group* p5, Group* p6);
    bool     FUN_00b07fa0(SimEvent* ev, bool flag, PlantRange* range, Group* group);
    bool     FUN_00b08260(uint32_t eventId, SimEvent* ev);
    void     F06810(void* vfx);                                                      // 0x00b06810 (ret 4)
    void     F068c0(Group* group, void* key, uint32_t kind);                         // 0x00b068c0 (ret 0xc)
    void     fillSlot(SimEvent* ev);                                                 // 0x00b04aa0 (ret 4)
    SlotBits* slotAt(void* key, uint32_t a, uint32_t b);                             // 0x00b04c20 (ret 0xc)

    char           pad00[0x34];
    PlantRange     mRange34;                                                         // +0x34
    char           pad4c[0x8080 - 0x4c];
    KeyMap         mMap8080;                                                         // +0x8080
    char           pad8088[0x160e8 - 0x8084];
    PlantEffectVec mEffects;                                                         // +0x160e8
    char           pad160f0[0x16500 - 0x160f0];
    EffectBook*    mpBook;                                                           // +0x16500
    PtrVec         mVec16504;                                                        // +0x16504
    char           pad1650c[0x165a0 - 0x1650c];
    Group          mGroup165a0;                                                      // +0x165a0
    char           pad165a4[0x1ba18c - 0x165a4];
    uint32_t       mMode;                                                            // +0x1ba18c
    int            mField1ba190;                                                     // +0x1ba190
};

extern "C" {
    IdLookup*       GetIdLookup(void);        // 0xb3d3b0
    SpeciesMgr*     GetSpeciesMgr(void);      // 0xb3d420
    EffectsManager* GetEffectsManager(void);  // 0x67ddd0
    PlanetModel*    GetPlanetModel(void);     // 0xb3d350
    NounManager*    GetNounManager(void);     // 0xb3d300
}
Item* __cdecl FUN_00afff30(Bucket* b, uint32_t i);      // 0xafff30
RBNode* __cdecl RBTreeIncrement(RBNode* n);             // 0x921580

extern uint32_t g_15673a8;     // 0x015673a8
extern uint32_t g_15673ac;     // 0x015673ac

// @ 0x00b07980
bool Mgr::FUN_00b07980(Req* req, bool flag, Group* g4, Group* p5, Group* p6)
{
    bool result = false;
    uint32_t mode = At<uint32_t>(this, 0x1ba18c);
    if ((mode & 1) == 0) return false;
    if (((mode >> 1) & 1) == 0) return false;

    uint8_t* elems = req->elems;
    void*    key   = req->key;
    uint32_t count = req->count;

    uint32_t id = GetIdLookup()->Lookup(req);
    if (!id) return false;
    Species* species = GetSpeciesMgr()->GetSpeciesFromID(id);
    if (!species) return false;
    if (species->GetKind() == 0x3a8be428) return false;
    result = true;

    uint32_t kind = species->GetKind();
    Triple pair = { key, kind, 0 };
    Model* model = species->GetModelWorld();

    VfxRef vfx;
    vfx.p = 0;
    if (flag && model && model->GetCount() != 0 && count != 0) {
        EffectsManager* em = GetEffectsManager();
        if (em->CreateEffect(g_15673a8, g_15673ac, vfx.AsPPTypeParam())) {
            EffectRec rec;
            rec.z14 = 0; rec.z18 = 0;
            rec.vfx.p = 0;
            rec.total = model->GetCount() * count;
            rec.key = key;
            rec.kind = kind;
            rec.vfx.assign(&vfx);
            vfx.p->Slot2(0);
            ((EffectVec*)((char*)this + 0x160e8))->push_back(&rec);
            rec.Reset();
        }
    }

    Range range = { 0, 0 };
    Group* last = p5;
    bool found = FindExisting(&range, key, kind, count, p5);
    if (!found) {
        if (p6) {
            found = FindExisting(&range, key, kind, count, p6);
            last = p6;
        }
    }
    uint32_t outTmp[2];

    if (found) {
        Bucket* bucket = GetBucket(key, species->GetKind());
        int idx = -1;
        uint32_t i = 0;
        RBNode* it = range.begin;
        uint8_t* cursor = elems + 0xc;
        if (it != range.end) {
            do {
                if (i >= count) break;
                Item* item = FUN_00afff30(bucket, i);
                Plant* o = it->value;
                At<uint32_t>(o, 0x54) = i;
                Xform* xf = &At<Xform>(o, 0x58);
                *xf = *(Xform*)(cursor - 0xc);
                Vector3 v;
                v.x = *(float*)(cursor - 8);
                v.y = *(float*)(cursor - 4);
                v.z = *(float*)cursor;
                Vector3 tmp;
                Vector3* r = GetPlanetModel()->DirectionToSurfacePosition(&tmp, &v);
                v = *r;
                xf->pos = *r;
                xf->flags |= 4;
                xf->counter++;
                XformListener* lst = At<XformListener*>(o, 0x1d0);
                if (lst) {
                    XformMsg m;
                    lst->Slot8(&m);
                    m.flags |= 4;
                    m.counter++;
                    m.pos = v;
                    lst->Slot6(&m);
                }
                GetPlanetModel()->FUN_00b88420();
                uint32_t rad = GetPlanetModel()->GetAverageRadius(&v);
                if ((rad & 0x18000000) && item) {
                    At<uint32_t>(item, 0x48) = 0;
                    At<uint32_t>(item, 0x4c) = 0;
                }
                if (item && flag)
                    At<Xform>(item, 0xc) = *xf;
                At<VfxRef>(o, 0x1c4).assign(&vfx);
                uint32_t n = model->GetCount();
                for (uint32_t j = 0; j < n; ++j) {
                    ++idx;
                    At<int*>(o, 0x19c)[j] = idx;
                }
                if (item) {
                    EffectBook* book = At<EffectBook*>(this, 0x16500);
                    if (book) {
                        if (book->f24 == book->f28) InitBook();
                        if (At<int>(item, 0x78) == -1) {
                            EffectBook* b2 = At<EffectBook*>(this, 0x16500);
                            if (b2->f24 != b2->f28)
                                At<int>(item, 0x78) = b2->FUN_00703d50(At<float>(item, 0x6c), &At<uint32_t>(item, 0x10), item);
                        }
                    }
                }
                if (last != p6) {
                    o->AddRef();
                    Triple t = { pair.key, pair.kind, o };
                    o->AddRef();
                    g4->Add(outTmp, &t, false);
                    o->Release();
                    o->Release();
                }
                it = RBTreeIncrement(it);
                ++i;
                cursor += 0x4c;
            } while (it != range.end);
        }
        if (last != p6)
            last->AddRange(outTmp, range.begin, range.end);
    } else {
        int idx = -1;
        Bucket* bucket = GetBucket(key, species->GetKind());
        bool isEmpty = (bucket == 0) || (bucket->first == bucket->second);
        if (count > 0) {
            bool notFlag = !flag;
            Xform* cursor = (Xform*)elems;
            uint32_t i = 0;
            do {
                Plant* o = NewPlant();
                if (o) o->AddRef();
                At<void*>(o, 0x4c) = key;
                At<uint32_t>(o, 0x54) = i;
                const Vector3* sp = species->GetPosition();
                At<float>(o, 0x94) = sp->x;
                At<float>(o, 0x98) = sp->y;
                At<float>(o, 0x9c) = sp->z;
                if (SetupPlant(o, species, cursor, isEmpty, notFlag, &idx, &vfx)) {
                    o->AddRef();
                    Triple t = { pair.key, pair.kind, o };
                    g4->Add(outTmp, &t, false);
                    o->Release();
                } else {
                    GetNounManager()->RemoveNoun(o);
                }
                o->Release();
                cursor = (Xform*)((char*)cursor + 0x4c);
                ++i;
            } while (i < count);
        }
    }
    if (vfx.p) vfx.p->Release();
    return result;
}

// ---------------------------------------------------------------------------------------------------
// The two handlers of the plant sim object: 0x00b07fa0 re-seats the already placed objects of a
// request on the planet (snap the transforms, renumber the slots, hand them to the groups) and
// 0x00b08260 reacts to the plant events (drop / update / place).  Names are Claude-coined; the
// event records are handed over as different structs, so the spawn-request view (Req) and the
// element view (SimEvent) are cast into each other.
// ---------------------------------------------------------------------------------------------------

// @ 0x00b07fa0
bool Mgr::FUN_00b07fa0(SimEvent* ev, bool flag, PlantRange* range, Group* group)
{
    bool result = false;
    if (range->mCount == 0)
        return false;

    Req* req = (Req*)ev;
    void* key = req->key;
    uint32_t count = req->field30;

    uint32_t id = GetIdLookup()->Lookup(req);
    if (!id)
        return result;
    Species* species = GetSpeciesMgr()->GetSpeciesFromID(id);
    if (!species)
        return result;

    uint32_t kind = species->GetKind();
    Range found = { 0, 0 };
    int idx = -1;
    uint32_t out[2];
    range->FindRange(&found, &key);

    uint32_t n = 0;
    for (RBNode* it = found.begin; it != found.end; it = RBTreeIncrement(it))
        ++n;
    if (n == 0)
        return result;

    uint32_t skip = count & 1;
    result = true;
    for (RBNode* it = found.begin; it != found.end; it = RBTreeIncrement(it)) {
        PlantObject* o = (PlantObject*)it->value;
        if (o)
            o->AddRef();
        if (flag)
            F06810(o->mpVfx);
        if (o->mpVfx) {
            o->mpVfx->Slot3(1);
            if (o->mpVfx) {
                VfxOwner* old = o->mpVfx;
                o->mpVfx = 0;
                old->Release();
            }
        }
        o->mIndex54 = ++idx;
        o->mField1c8 = 0;
        int slots = (int)(o->mpSlotIdsEnd - o->mpSlotIds);
        for (int j = 0; j < slots; ++j)
            o->mpSlotIds[j] = 0xffffffff;
        if (skip == 0) {
            Triple t = { key, kind, (Plant*)o };
            o->AddRef();
            group->Add(out, &t, false);
            o->Release();
        }
        o->Release();
    }
    if (skip == 0) {
        range->AddRange(out, found.begin, found.end);
        return result;
    }

    // the request carries pit objects: drop the slot shadows and the queued effects
    F068c0(group, key, kind);
    for (void** p = mVec16504.mBegin; p != mVec16504.mEnd; ++p) {
        HolderObject* h = (HolderObject*)*p;
        VfxOwner* ref = h->mpField64;
        if (ref) {
            h->mpField64 = 0;
            ref->Release();
        }
    }
    Bucket* bucket = GetBucket(key, species->GetKind());
    if (bucket) {
        for (BucketObject** p = (BucketObject**)bucket->first; p != (BucketObject**)bucket->second; ++p) {
            BucketObject* item = *p;
            if (!item)
                continue;
            EffectBook* book = mpBook;
            if (!book)
                continue;
            if (book->f24 == book->f28)
                InitBook();
            if (item->mSlot78 < 0)
                continue;
            book = mpBook;
            if (book->f24 != book->f28)
                book->Remove(item->mSlot78);
            item->mSlot78 = -1;
        }
        FUN_00b057b0(bucket);
    }
    return result;
}

// @ 0x00b08260
bool Mgr::FUN_00b08260(uint32_t eventId, SimEvent* ev)
{
    bool result = false;
    MapNode* node;
    RecordBuilder built;
    RefCollector collector;

    switch (eventId) {
    case 0x2f3fc35: {
        uint32_t key0 = ev->mKey;
        void*    transforms = ev->mpTransforms;
        void*    target = ev->mpTarget;
        uint32_t targetId = (uint32_t)target;
        if (transforms == 0) {
            // the object went away: drop its map entry
            void* key = target;
            mMap8080.find(&node, &key);
            if (node != mMap8080.end()) {
                if (node->mpValue)
                    node->mpValue->Slot3(1);
                FUN_00b043b0(&node, node);
            }
            return true;
        }
        if ((mMode & 1) == 0)
            return true;
        if ((mMode >> 1 & 1) == 0)
            return true;

        bool matched = false;
        for (int i = 0; i < 6; ++i)
            collector.mpData[i] = 0;
        built.mField00 = 0;
        void* mapKey = target;
        mMap8080.find(&node, &mapKey);
        if (node != mMap8080.end()) {
            matched = true;
            if (node->mpKey == (void*)key0)
                node->mpField30 = transforms;
            collector.Add(&node->mpKey);
        }
        for (EffectRec* rec = mEffects.mBegin; rec != mEffects.mEnd; ++rec) {
            if (matched)
                break;
            VfxOwner* fx = (VfxOwner*)rec->vfx.p;
            if (!fx)
                continue;
            FeatureVec* vec = (FeatureVec*)((char*)fx + 0x144);
            uint32_t count = vec->Size();
            FeatureLookup* f = vec->mBegin;
            for (uint32_t i = 0; i < count; ++i, f = (FeatureLookup*)((char*)f + 0x5c)) {
                if (f->mSlotId38 != targetId)
                    continue;
                matched = true;
                ((RecordTail*)&rec->z14)->F07d4590(target);
                if (key0 == rec->total)
                    rec->z18 = (uint32_t)transforms;
                collector.Add(rec);
                void* bkey = target;
                void* value = built.Build(&bkey, &collector);
                mMap8080.F05c30(&collector, value);
                built.Reset();
                mEffects.F05d50(rec);
                break;
            }
        }
        if (matched) {
            if (key0 == built.mField00) {
                // re-seat the objects of the range on the transforms of the event
                Range found = { 0, 0 };
                void* rkey = target;
                mRange34.FindRange(&found, &rkey);
                for (RBNode* it = found.begin; it != found.end; it = RBTreeIncrement(it)) {
                    PlantObject* o = (PlantObject*)it->value;
                    if (!o)
                        continue;
                    o->mField1c8 = targetId;
                    SlotBits* bits = slotAt(o->mpKey, o->mField50, o->mIndex54);
                    uint32_t slots = o->CurEntryBits();
                    for (uint32_t i = 0; i < slots; ++i) {
                        uint32_t slot = o->mpSlotIds[i];
                        if (slot >= key0)
                            continue;
                        Xform tmp;
                        translateTransform(&tmp, (char*)o->mpMatrixA4 + i * 0x38, &o->mXform58);
                        ((XformOps*)((char*)transforms + slot * 0x4c))->Assign(&tmp);
                        if (bits) {
                            uint64_t mask = __allshl(1, i);
                            if ((bits->mMaskLo & (uint32_t)mask) == 0 &&
                                (bits->mMaskHi & (uint32_t)(mask >> 32)) == 0)
                                ((SlotOwner*)this)->SetShadow(slot, 0.0f);
                        }
                    }
                }
            }
            else {
                ((SimTarget*)target)->mRangeKey = built.mField00;
            }
        }
        built.Reset();
        return true;
    }
    case 0x25630b7:
        result = true;
        break;
    case 0x2e9977e:
        break;
    case 0x477c00d:
        result = true;
        break;
    default:
        return false;
    }

    // place / update the objects of the request
    void* id08 = ev->mpTransforms;
    Req* req = (Req*)ev;
    fillSlot(ev);
    if (id08 != 0) {
        Group* p5 = (mField1ba190 > 0) ? (Group*)&mRange34 : 0;
        FUN_00b07980(req, result, (Group*)&mRange34, &mGroup165a0, p5);
    }
    else {
        FUN_00b07fa0(ev, result, &mRange34, &mGroup165a0);
    }
    return true;
}
