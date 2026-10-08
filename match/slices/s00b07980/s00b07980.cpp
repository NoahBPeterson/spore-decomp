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
    uint32_t pad0c[(0x20 - 0x0c) / 4];
    void*    key;         // +0x20
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
};

struct Bucket { uint32_t first, second; };

struct Mgr
{
    bool     FindExisting(Range* out, void* key, uint32_t kind, uint32_t count, Group* g);          // 0xb034f0 (ret 0x14)
    Bucket*  GetBucket(void* key, uint32_t kind);                                                    // 0xb04ba0 (ret 8)
    Plant*   NewPlant();                                                                             // 0xb02060
    void     InitBook();                                                                             // 0xb02120
    bool     SetupPlant(Plant* p, Species* s, Xform* elem, int isEmpty, int notFlag, int* idx, VfxRef* vfx); // 0xb07560 (ret 0x1c)
    bool     FUN_00b07980(Req* req, bool flag, Group* g4, Group* p5, Group* p6);
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
