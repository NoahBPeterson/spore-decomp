// Slice s00b76f10: spawner method at 0x00b76f10 (creates / refreshes Obj instances for a request).
// 32-bit MSVC 2008 SP1.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc: no EH frames in the original)
#include "types.h"

#include <math.h>
#pragma intrinsic(sqrt)

typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t u8;

// vtable call helpers: slot is a byte offset into the vtable
#define VCALL0(p, off) ((void(__thiscall*)(void*))(*(void***)(p))[(off) / 4])(p)
#define VCALL2(p, off, a, b) ((void(__thiscall*)(void*, void*, int))(*(void***)(p))[(off) / 4])(p, a, b)

struct Vec3 {            // plain: copies through integer registers
    float x, y, z;
};
struct Vec3C {           // user copy constructor: loads/stores through xmm0
    float x, y, z;
    Vec3C() {}
    Vec3C(const Vec3C& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vec3A {           // user operator=: x87 fld/fstp copies
    float x, y, z;
    Vec3A& operator=(const Vec3A& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

// Shared model that Objs attach to (vtable slot 13 = AddRef, 14 = Release).
struct Model {
    u32 vt;
    u32 pad[0xa8 / 4 - 1];
    void SetAlpha(int idx, float a);  // 0x00a887b0
    void AddRef()  { VCALL0(this, 0x34); }
    void Release() { VCALL0(this, 0x38); }
};

// Intrusive object with an owner; the owner's vtable releases it.
struct Shared {
    void* mpOwner;     // +0x00 (polymorphic)
    u32   mFlags;      // +0x04
    u32   pad[0x40 / 4 - 2];
    int   mRefCount;   // +0x40
};
static __forceinline void ReleaseShared(Shared*& slot) {
    Shared* old = slot;
    if (old) {
        slot = 0;
        if (old->mRefCount > 1) {
            --old->mRefCount;
        } else {
            VCALL2(old->mpOwner, 0x170, old, (u8)((old->mFlags >> 31) & 1));
        }
    }
}

struct Obj {
    void** vt;          // +0x00
    u32    pad04[0x34 / 4 - 1];
    u32    mFlags;      // +0x34
    Vec3   mPos;        // +0x38
    float  mSize[3];    // +0x44
    u32    mExtra;      // +0x50
    Model* mpModel;     // +0x54
    void*  mpSource;    // +0x58
    int    mIndex;      // +0x5c
    u32    pad60;
    int    mGridSlot;   // +0x64
    float  mScale;      // +0x68
    u32    mId;         // +0x6c
    Shared* mpA;        // +0x70
    u32    mValue;      // +0x74
    Shared* mpB;        // +0x78
    Vec3   mDefPos;     // +0x7c
    u32    mKind;       // +0x88

    void AddRef()  { VCALL0(this, 0x00); }
    void Release() { VCALL0(this, 0x04); }
    void Reset()   { VCALL0(this, 0x54); }
};

struct Elem {            // 0x4c bytes
    u32   pad0;
    Vec3  pos;           // +0x04
    float scale;         // +0x10
    u32   pad[0x4c / 4 - 5];
};

struct SpawnReq {
    u32    count;        // +0x00
    u32    pad04;
    Elem*  elems;        // +0x08
    u32    pad0c;
    Model* ref;          // +0x10
    u32    pad14;
    u32    id;           // +0x18
    u32    pad1c;
    u32    extra;        // +0x20
};

struct Species {
    u32   pad0[0x8c / 4];
    u32   mValue;        // +0x8c
    u32   pad90;
    float mSize0;        // +0x94
    float mSize1;        // +0x98
    float mSize2;        // +0x9c
    u32 GetKind();       // 0x00b8f860
};
struct SpeciesMgr { Species* GetSpecies(float* pos); };   // 0x00b90410 (thiscall, ret 4)
struct PlantMgr   { float* Find(SpawnReq* r); };          // 0x00b2b1e0 (thiscall, ret 4)

struct TableEntry {      // 0x24 bytes
    u32 pad0;
    u32 idA;             // +0x04
    u32 idB;             // +0x08
    u32 pad0c;
    float s0, s1, s2;    // +0x10..
    u32 val;             // +0x1c
    u32 flags;           // +0x20
};
struct RbTree {          // eastl::rbtree<u32, pair<u32, RecA*>>
    u32 mCompare;
    u32 mAnchor;         // +4: header/end node
    void Find(void** out, u32* key);   // 0x00e5c780 thiscall ret 8
};
struct TableMgr {
    u32 pad[0x17c / 4];
    TableEntry* tabBegin;   // +0x17c
    TableEntry* tabEnd;     // +0x180
    u32 pad2[(0x190 - 0x184) / 4];
    RbTree mTree;           // +0x190
};

struct HtNode { u32 lo; u32 hi; Obj* obj; u32 pad; HtNode* next; };
struct HtIter {
    HtNode* node; HtNode** bucket;
    HtIter() {}
    HtIter(const HtIter& o) : node(o.node), bucket(o.bucket) {}
};
struct HtRange { HtIter first; HtIter last; };
struct HtEntry { u32 lo; u32 hi; Obj* obj; };
struct HtResult { HtIter it; };

struct TrueTag {};      // eastl::true_type: no user ctor, so it is stored as a zero byte
struct HashTable {
    u32 pad[2];
    void Insert(HtResult* out, HtEntry* e, TrueTag t);       // 0x00b75240 thiscall ret 0xc
    void Erase(HtResult* out, HtIter first, HtIter last); // 0x00b764e0 thiscall ret 0x14
};

struct Grid {
    u32 pad[0x24 / 4];
    void* mBegin;        // +0x24
    void* mEnd;          // +0x28
    int Add(float r, Vec3* pos, Obj* o);   // 0x00703d50
    void Remove(int slot);                 // 0x00702da0
};

struct RecA { u32 pad[3]; u32* arr; };    // value of the rbtree (array at +0xc)

struct PlanetModel {
    void Mark(Vec3* v, float r, u32 mask, int zero);   // 0x00b83c40 (4 args)
};
struct PropList { bool Has(u32 id); };                 // 0x006a25a0 thiscall ret 4

extern Vec3 g_DefaultPos;     // 0x01687af0
extern PropList* g_pProps;    // 0x015fd918
PlantMgr*   GetPlantMgr();    // 0x00b3d3b0
SpeciesMgr* GetSpeciesMgr();  // 0x00b3d420
TableMgr*   GetTableMgr();    // 0x00b3d3b0 (same global)
struct Global2 { u32 pad[0x55a4 / 4]; Grid* pGrid; };
Global2*    GetGlobal2();     // 0x00b3d3c0
PlanetModel* GetPlanet();     // 0x00b3d350

struct Spawner {
    u32 pad0[0x38 / 4];
    HashTable mAlt;           // +0x38
    u32 pad1[(0x2094 - 0x40) / 4];
    HashTable mMain;          // +0x2094
    u32 pad2[(0x55a4 - 0x209c) / 4];
    Grid* mpGrid;             // +0x55a4

    bool Find(HtRange* out, u32 lo, u32 hi, u32 count, bool alt);  // 0x00b751b0 ret 0x14
    Obj* AllocObj();                                               // 0x00b74370
    void InitGrid();                                               // 0x00b74130

    bool Spawn(SpawnReq* p, u32 hash);                             // 0x00b76f10 ret 8
};

// @ 0x00b76f10
bool Spawner::Spawn(SpawnReq* p, u32 hash)
{
    bool result = false;
    Elem* arr = p->elems;
    Model* ref = p->ref;
    u32 extra = p->extra;
    u32 id = p->id;
    u32 count = p->count;
    bool isPlant = (hash == 0x25630b7 || hash == 0x477c00d || hash == 0x2e9977e);
    bool isOther = (hash == 0x31018b9);
    Vec3 defPos = g_DefaultPos;
    u32 kind = 0;
    if (id == 0) goto done;
    if (id == 0x2ebcd6a6) goto done;

    float sx, sy, sz;
    u32 value;
    u64 key;
    if (isPlant) {
        float* e = GetPlantMgr()->Find(p);
        if (!e) goto done;
        Species* sp = GetSpeciesMgr()->GetSpecies(e);
        if (!sp) goto done;
        defPos.x = e[0]; defPos.y = e[1]; defPos.z = e[2];
        u32 hi = sp->GetKind();
        sx = sp->mSize0;
        value = sp->mValue;
        sy = sp->mSize1;
        key = ((u64)hi << 32) | (u64)extra;
        sz = sp->mSize2;
        switch (sp->GetKind()) {
        case 0x29c388a: kind = 1; break;
        case 0x3a8be428: kind = 0; break;
        case 0x6d60a1cc: kind = 2; break;
        }
    } else {
        if (!isOther) goto done;
        TableMgr* tm = GetTableMgr();
        TableEntry* t = tm->tabBegin;
        u32 n = (u32)(tm->tabEnd - tm->tabBegin);
        u32 i = 0;
        if (n == 0) goto done;
        do {
            if (t->idA == id || t->idB == id) goto foundEntry;
            i++;
            t++;
        } while (i < n);
        goto done;
foundEntry:
        if (!((u8)t->flags & 1)) goto done;
        sx = t->s0;
        sy = t->s1;
        key = (u64)(int)(u32)ref;
        sz = t->s2;
        value = t->val;
        kind = 3;
    }
    if (key == 0) goto done;

    HtRange res;
    res.first.node = 0; res.first.bucket = 0; res.last.node = 0; res.last.bucket = 0;
    bool bMain = true;
    result = true;
    bool found = Find(&res, (u32)key, (u32)(key >> 32), count, false);
    if (!found && hash == 0x2e9977e) {
        bMain = false;
        found = Find(&res, (u32)key, (u32)(key >> 32), count, true);
    }
    if (found)
    {
        HtNode* node = res.first.node;
        HtNode** bucket = res.first.bucket;
        if (node != res.last.node) {
            Elem* e = arr;
            do {
                Obj* o = node->obj;
                if (o) o->AddRef();
                float a = (o->mFlags & 1) ? 0.0f : 1.0f;
                ref->SetAlpha(o->mIndex, a);
                if (bMain) {
                    Model* old = o->mpModel;
                    if (ref != old) {
                        if (ref) ref->AddRef();
                        o->mpModel = ref;
                        if (old) old->Release();
                    }
                    o->mpSource = arr;
                    if (hash == 0x2e9977e) o->mFlags |= 4; else o->mFlags &= ~4u;
                    float scale = e->scale;
                    if (hash == 0x2e9977e) scale = 1.0f;
                    *(Vec3A*)&o->mPos = *(Vec3A*)&e->pos;
                    o->mSize[0] = scale * sx;
                    o->mSize[1] = scale * sy;
                    o->mSize[2] = scale * sz;
                    HtEntry ent;
                    ent.lo = (u32)key; ent.hi = (u32)(key >> 32); ent.obj = o;
                    o->AddRef();
                    HtResult r;
                    mAlt.Insert(&r, &ent, TrueTag());
                    if (ent.obj) ent.obj->Release();
                }
                e++;
                o->Release();
                node = node->next;
                while (!node) node = *++bucket;
            } while (node != res.last.node);
        }
        if (bMain) {
            HtResult r;
            mMain.Erase(&r, res.first, res.last);
        }
    }
    else
    {
        RecA* rec = 0;
        if (isOther) {
            TableMgr* tm = GetTableMgr();
            u32 k = (u32)ref;
            void* it;
            tm->mTree.Find(&it, &k);
            if (it != (void*)&tm->mTree.mAnchor) rec = *(RecA**)((char*)it + 0x14);
        }
        PlanetModel* planet = GetPlanet();
        for (u32 i = 0; i < count; i++) {
            Vec3C pos = *(Vec3C*)&arr[i].pos;
            float scale = arr[i].scale;
            if (hash == 0x2e9977e) scale = 1.0f;
            Obj* o = AllocObj();
            if (o) o->AddRef();
            o->Reset();
            o->mPos = *(Vec3*)&pos;
            o->mSize[0] = scale * sx;
            o->mSize[2] = scale * sz;
            o->mSize[1] = scale * sy;
            o->mScale = 1.0f;
            o->mId = id;
            ReleaseShared(o->mpA);
            o->mValue = value;
            ReleaseShared(o->mpB);
            o->mDefPos = defPos;
            o->mpSource = arr;
            o->mIndex = i;
            o->mExtra = extra;
            {
                Model* old = o->mpModel;
                if (ref != old) {
                    if (ref) ref->AddRef();
                    o->mpModel = ref;
                    if (old) old->Release();
                }
            }
            o->mKind = kind;
            if (hash == 0x2e9977e) o->mFlags |= 4; else o->mFlags &= ~4u;
            if (mpGrid->mBegin == mpGrid->mEnd) InitGrid();
            {
                Grid* g = GetGlobal2()->pGrid;
                if (g && o->mGridSlot < 0 && g->mBegin != g->mEnd)
                    o->mGridSlot = g->Add(o->mSize[1], &o->mPos, o);
            }
            if (rec && rec->arr[i]) {
                o->mFlags |= 1;
                if (o->mpModel) {
                    o->mpModel->SetAlpha(o->mIndex, 0.0f);
                } else if (o->mpA) {
                    o->mpA->mFlags &= ~1u;
                    VCALL2(o->mpA->mpOwner, 0x16c, o->mpA, 0);
                }
                Grid* g = GetGlobal2()->pGrid;
                if (g && o->mGridSlot >= 0) {
                    if (g->mBegin != g->mEnd) g->Remove(o->mGridSlot);
                    o->mGridSlot = -1;
                }
            }
            if (kind == 3 && !rec && g_pProps->Has(0x4233e37)) {
                planet->Mark((Vec3*)&pos, (float)sqrt(pos.x * pos.x + pos.z * pos.z + pos.y * pos.y) * 0.00390625f + o->mSize[0], 0x10000000, 0);
            }
            HtEntry ent;
            ent.lo = (u32)key; ent.hi = (u32)(key >> 32); ent.obj = o;
            o->AddRef();
            HtResult r;
            mAlt.Insert(&r, &ent, TrueTag());
            if (ent.obj) ent.obj->Release();
            o->Release();
        }
    }
done:
    return result;
}
