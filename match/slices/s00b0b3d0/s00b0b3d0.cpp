// Slice s00b0b3d0 (batch cl2, slice 273) -- 0x00b0b3d0.
// Per-frame update of the "spawner" manager (sibling of ItemManager::Update 0xb08670 and
// BeamMgr2::UpdateBeams 0xb0a6f0, which this function calls).  `this` is the manager's
// secondary-base subobject: the primary object is at this-4.  Names are Claude-coined.
//
// What it does: when the manager is active (bits 0 and 1 of the flag word at +0x1ba188), it works out
// two reference points from the camera (and, if there is an avatar, from the avatar's position and
// heading), asks the spawner for the gathered entities within 75 units, and then walks the manager's
// item vector in step with the gathered list: for each gathered entity it looks up the prototype and,
// for each of the entity's attachment transforms that the prototype's mask enables and that is at
// least 5 units from the camera, it moves the next free item to that transform, switches its light on
// and records which entity/attachment it serves.  Items left over after the gathered list ran out are
// put into state 6 (hidden: effect released, moved to the origin, light off).  Then it runs the
// per-frame helpers and switches off the lights of items that are lit but not active.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

void operator delete(void* p);                                           // 0x00f47380

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
// per-field float copy (movss) instead of the integer copy of a plain POD
struct FVec3 : Vec3 {
    FVec3() {}
    FVec3(const FVec3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Quat { float x, y, z, w; };
struct Mat33 { float m[9]; };
// 0x38-byte transform (translateTransform 0x006271a0 copies its first 0x38 bytes)
struct Xform {
    uint16_t a, b;
    Vec3 pos;           // +4
    float f10;
    Mat33 m;            // +0x14
};

extern FVec3 g_zeroVec;     // 0x0167af5c
extern FVec3 g_axisVec;     // 0x0167b84c

#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Light;
struct LightOwner {
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV2 PV     // slots 0..90
    virtual void Update(Light* l, int flag);                // slot 91 (+0x16c)
};
struct Light {
    LightOwner* owner;   // +0
    uint32_t flags;      // +4
};

// cSpatialObject (the sub-object at item+0x34)
struct Spatial {
    PV8 PV4 PV2                                             // slots 0..13
    virtual void SetPosition(const Vec3* v);                // +0x38
    virtual void SetOrientation(const Quat* q);             // +0x3c
    PV8 PV8 PV8 PV2 PV                                      // slots 16..42
    virtual Light* GetLight();                              // +0xac
};

struct IRefCounted { virtual void AddRef(); virtual void Release(); };

// an item owned by the manager (vectors at +0x1b8e10 / +0x1b8f40)
struct Item {
    char pad000[0x34];
    Spatial spatial;                // +0x34
    char pad038[0xa3 - 0x38];
    uint8_t fA3;                    // +0xa3
    uint8_t fA4;                    // +0xa4
    char padA5[4];
    uint8_t fA9;                    // +0xa9
    char padAA;
    uint8_t fAB;                    // +0xab
    char padAC[0x108 - 0xac];
    IRefCounted* effect;            // +0x108
    char pad10C[0x158 - 0x10c];
    uint32_t id50;                  // +0x158
    uint32_t id4c;                  // +0x15c
    uint32_t id54;                  // +0x160
    uint32_t attachment;            // +0x164
    char pad168[4];
    int state;                      // +0x16c
    void FUN_00c3f8b0(int a, int b);    // 0x00c3f8b0 (ret 8)
};

// prototype looked up from the entity's ids
struct Proto {
    char pad00[0x48];
    uint64_t mask;                  // +0x48
};
struct ProtoVec { Proto** begin; Proto** end; };

// the gathered entity
struct Entity {
    char pad00[0x4c];
    uint32_t id4c;                  // +0x4c
    uint32_t id50;                  // +0x50
    uint32_t id54;                  // +0x54
    Xform base;                     // +0x58
    char pad90[0xa4 - 0x90];
    Xform* attachments;             // +0xa4
    uint32_t FUN_00b058f0();        // 0x00b058f0: number of attachments
};

struct Res { char pad[0x68]; float f68; };   // result of the id lookup
struct IdMgr {
    uint64_t FUN_00b72410(uint32_t hi, uint32_t lo);        // ret 8
    Res* FUN_00b74e90(uint64_t key, uint32_t idx);          // ret 0xc
};
IdMgr* __cdecl GetIdMgr();                                  // 0x00b3d3c0 (returns [0x167eb14])
struct FlagMgr { bool FUN_00f64260(); };                    // 0x00f64260: byte [+0x20] & 1
FlagMgr* __cdecl GetFlagMgr();                              // 0x00b3d3b0 (returns [0x167eb10])

struct Located {
    PV8 PV2 PV                                              // slots 0..10
    virtual const Vec3* GetPosition();                      // +0x2c
    virtual const Quat* GetOrientation();                   // +0x30
};
struct Avatar { char pad[0xc0]; Located loc; };
struct NounManager { Avatar* GetAvatar(); };                // 0x00b1fdb0
NounManager* __cdecl GetNounManager();                      // 0x00b3d300

struct Viewer { void GetCameraLocationInfo(Vec3* a, Vec3* b, Vec3* c, Vec3* d); };   // 0x007c3d30 (ret 0x10)
struct ViewerHolder {
    PV4 PV2 PV
    virtual Viewer* GetViewer();           // +0x1c
};
struct AppSub {
    PV8 PV8 PV4
    virtual ViewerHolder* GetHolder();     // +0x50
};
AppSub* __cdecl App();                                      // 0x0067dd10

struct AimSource {
    PV8 PV4 PV2
    virtual Vec3* GetPoint(Vec3* out, int flag, FVec3 hint);   // +0x38
};
AimSource* __cdecl GetAimSource();                          // 0x00b3d240
Vec3* __cdecl RotateByQuat(Vec3* out, const Vec3* v, const Quat* q);   // 0x0059aed0
Xform* __cdecl translateTransform(Xform* out, const Xform* offs, const Xform* base);   // 0x006271a0
Quat* __cdecl QuatFromMatrix33(Quat* out, const Mat33* m);  // 0x0046d660
void __cdecl NormalizeQuat(Quat* out, const Quat* in);      // 0x00799320

struct PtrVec {
    Entity** begin;
    Entity** end;
    Entity** cap;
    uint32_t alloc[2];
    int header;
    Entity* buf[256];
};

struct RBNode;
RBNode* __cdecl RBTreeIncrement(RBNode* n);                 // 0x00921580
struct Spawn { void FUN_00b02fa0(); };                      // 0x00b02fa0

static inline bool Bit(uint32_t v, int i) { return ((v >> i) & 1) != 0; }

struct Mgr;
// primary object at this-4
struct MgrBase {
    void FUN_00b068c0(void* a, uint32_t lo, uint32_t hi);                         // 0x00b068c0 (ret 0xc)
    void FUN_00b09070(const Vec3* a, float radius, PtrVec* out, const Vec3* b);   // 0x00b09070 (ret 0x10)
    void FUN_00b09bf0(uint32_t t);                                                // 0x00b09bf0 (ret 4)
    ProtoVec* FUN_00b04ba0(uint32_t a, uint32_t b);                               // 0x00b04ba0 (ret 8)
    void ItemUpdate(uint32_t t);                                                  // 0x00b08670 (ret 4)
    void UpdateBeams();                                                           // 0x00b0a6f0
};
struct ItemVec { Item** begin; Item** end; };

struct Mgr {
    char pad000[0x34];
    uint32_t mapAnchor;                  // +0x34
    RBNode* mapBegin;                    // +0x38
    char pad03c[0x1659c - 0x3c];
    uint32_t objMask;                    // +0x1659c
    char pad165a0[0x1b8e0c - 0x165a0];
    int blocked;                         // +0x1b8e0c
    ItemVec itemsA;                      // +0x1b8e10
    char pad1b8e18[0x1b8f40 - 0x1b8e18];
    ItemVec itemsB;                      // +0x1b8f40
    char pad1b8f48[0x1ba188 - 0x1b8f48];
    uint32_t flags;                      // +0x1ba188
    void Update(uint32_t a, uint32_t b);
};

// Mgr::Update @ 0x00b0b3d0  (thiscall, ret 8; the first argument is unused)
void Mgr::Update(uint32_t a, uint32_t b)
{
    MgrBase* base = (MgrBase*)((char*)this - 4);
    base->FUN_00b068c0(&objMask, 0, 0);
    if (!Bit(flags, 0) || !Bit(flags, 1))
        return;
    Viewer* viewer = App()->GetHolder()->GetViewer();
    FVec3 camPos(g_zeroVec);
    FVec3 camDir(g_zeroVec);
    if (viewer)
        viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
    if (blocked == 0) {
        Vec3 pa(camPos.x, camPos.y, camPos.z);
        Vec3 pb(camPos.x, camPos.y, camPos.z);
        if (GetNounManager()->GetAvatar()) {
            pa = *GetNounManager()->GetAvatar()->loc.GetPosition();
            Vec3 axisTmp;
            const Vec3* ax = RotateByQuat(&axisTmp, &g_axisVec, GetNounManager()->GetAvatar()->loc.GetOrientation());
            float d = camDir.x * ax->x + ax->z * camDir.z + ax->y * camDir.y;
            float px = camDir.x - d * ax->x;
            float py = camDir.y - ax->y * d;
            float pz = camDir.z - ax->z * d;
            pb.x = px * 12.0f + pb.x;
            pb.y = py * 12.0f + pb.y;
            pb.z = pz * 12.0f + pb.z;
            pa.x = px * 6.0f + pa.x;
            pa.y = py * 6.0f + pa.y;
            pa.z = pz * 6.0f + pa.z;
        } else {
            Vec3 tmp;
            pb = *GetAimSource()->GetPoint(&tmp, 1, g_zeroVec);
        }
        PtrVec v;
        v.header = 0;
        v.begin = v.buf;
        v.end = v.buf;
        v.cap = v.buf + 256;
        base->FUN_00b09070(&pa, 75.0f, &v, &pb);
        Item** m = itemsA.begin;
        Entity** g = v.begin;
        Entity** gend = v.end;
        if (m != itemsA.end) {
            do {
                if (g == gend)
                    break;
                Entity* e = *g;
                Res* r = GetIdMgr()->FUN_00b74e90(GetIdMgr()->FUN_00b72410(e->id50, e->id4c), e->id54);
                if (r && !(r->f68 >= 0.25f)) {
                    g++;
                    continue;
                }
                uint32_t idx = e->id54;
                ProtoVec* pv = base->FUN_00b04ba0(e->id4c, e->id50);
                Proto* proto;
                if (!(pv && idx < (uint32_t)(pv->end - pv->begin) && (proto = pv->begin[idx]) != 0)) {
                    g++;
                    continue;
                }
                uint32_t count = e->FUN_00b058f0();
                uint32_t off = 0;
                for (uint32_t i = 0; i < count; i++, off += 0x38) {
                    if (m == itemsA.end)
                        break;
                    uint64_t hit = (1ULL << i) & proto->mask;
                    if ((uint32_t)hit != 0 || (uint32_t)(hit >> 32) != 0) {
                        Xform xf;
                        translateTransform(&xf, (const Xform*)((char*)e->attachments + off), &e->base);
                        float dx = camPos.x - xf.pos.x;
                        float dz = camPos.z - xf.pos.z;
                        float dy = camPos.y - xf.pos.y;
                        if (!(25.0f > (dx * dx + dz * dz) + dy * dy)) {
                            Item* it = *m;
                            Spatial* sp = &it->spatial;
                            it->fA9 = 1;
                            if (sp->GetLight()) {
                                sp->GetLight()->flags |= 1;
                                Light* l = sp->GetLight();
                                l->owner->Update(l, 1);
                                it->FUN_00c3f8b0(1, 0);
                            }
                            sp->SetPosition(&xf.pos);
                            Quat q1;
                            Quat q2;
                            NormalizeQuat(&q2, QuatFromMatrix33(&q1, &xf.m));
                            sp->SetOrientation(&q2);
                            m++;
                            it->id50 = e->id50;
                            it->id4c = e->id4c;
                            it->id54 = e->id54;
                            it->attachment = i;
                            it->fA4 = 1;
                            it->fA3 = 1;
                            it->state = 0;
                            it->fAB = 0;
                        }
                    }
                }
                g++;
            } while (m != itemsA.end);
            if (m != itemsA.end) {
                do {
                    Item* it = *m;
                    if (it && it->state != 6) {
                        IRefCounted* fx = it->effect;
                        if (fx) {
                            it->effect = 0;
                            fx->Release();
                        }
                        Spatial* sp = &it->spatial;
                        it->state = 6;
                        sp->SetPosition(&g_zeroVec);
                        if (sp->GetLight()) {
                            sp->GetLight()->flags &= ~1u;
                            Light* l = sp->GetLight();
                            l->owner->Update(l, 0);
                        }
                    }
                    m++;
                } while (m != itemsA.end);
            }
        }
        if (v.begin && ((int*)v.begin)[-1])
            operator delete(v.begin);
    }
    base->FUN_00b09bf0(b);
    if (GetFlagMgr()->FUN_00f64260()) {
        RBNode* end = (RBNode*)&mapAnchor;
        for (RBNode* n = mapBegin; n != end; n = RBTreeIncrement(n)) {
            Spawn* s = *(Spawn**)((char*)n + 0x18);
            if (s)
                s->FUN_00b02fa0();
        }
    }
    base->ItemUpdate(b);
    ItemVec* vecs[2] = { &itemsA, &itemsB };
    for (int i = 0; i < 2; i++) {
        Item** p = vecs[i]->begin;
        Item** e = vecs[i]->end;
        for (; p != e; p++) {
            Item* it = *p;
            if (it) {
                Spatial* sp = &it->spatial;
                if (sp->GetLight() && ((sp->GetLight()->flags >> 15) & 1) && (it->fA9 == 0 || it->state != 0)) {
                    sp->GetLight()->flags &= ~1u;
                    Light* l = sp->GetLight();
                    l->owner->Update(l, 0);
                }
            }
        }
    }
    if (flags & 0x10)
        base->UpdateBeams();
}

// =====================================================================================================
// Second view of the same object, for the constructor/destructor and the scatter-vector helpers that
// gold7 claims (0x00b0bb50, 0x00b0bd10, 0x00b0bdb0, 0x00b0bfa0, 0x00b0c110).  The cl2 body above keeps
// its own offsets; nothing here moves a byte of it.
// =====================================================================================================

inline void* operator new(unsigned int, void* p) { return p; }

void operator delete(void* p);                                              // 0x00f47380

void* __cdecl EaAllocate(unsigned int size, const char* name, int a, int b, int c, int line); // 0x00f473a0
extern char gAllocatorTag[];                                                // 0x013ebb38
extern void* gVtablePaintBase[];                                            // 0x013eb384
extern void* gVtablePaintDtor[];                                            // 0x013eb394
extern void* gVtablePaintSub[];                                             // 0x0145c828
extern void* gVtablePaint[];                                                // 0x0145c878
extern void* gVtablePaint3[];                                               // 0x0145c824

void __cdecl RemoveMessageHandler(void* handler, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00571db0

struct GonzagoSub {                                      // secondary base at +4
    void Construct();                                    // 0x00b5b960
    ~GonzagoSub();                                       // 0x00b5b9a0
};
struct HierGrid {
    HierGrid();                                          // 0x00703ce0
    ~HierGrid();                                         // 0x00750310
};

// A pool owner: its ctor only fills the head, the dtor hands the node chain back to the pool.
struct PaintPool {
    char   mData[0xc];                                   // +0x00
    void*  mpChain;                                      // +0x0c
    void Construct();                                    // 0x00b05a80
    void ConstructAlt();                                 // 0x00b05ae0
    void ReleaseChain(void* chain);                      // 0x00b04350 (ret 4)
    void WalkChain(void* chain);                         // 0x00b04420 (ret 4)
};

// ---------------------------------------------------------------------------------------------------
// 0x19a8-byte scatter element: a dword key, 4 bytes of padding, then the heavy payload.
// ---------------------------------------------------------------------------------------------------
struct __declspec(align(8)) Scatter {
    char mData[0x19a0];                                  // +0x0000
    Scatter();
    Scatter(const Scatter&);
    ~Scatter();
    void AssignFrom(const Scatter&);                     // 0x00b0a3f0 (ret 4)
};
struct ScatterE {
    uint32_t mKey;                                       // +0x0000
    Scatter  mPayload;                                   // +0x0008 (8-byte aligned)
};

void* __cdecl ScatterCopyRange(void* first, void* last, void* dest);        // 0x00b096e0
void* __cdecl ScatterFillRange(void* first, void* last, void* dest);        // 0x00b048f0
void* __cdecl ScatterCopyBackward(ScatterE* first, ScatterE* last, ScatterE* dest); // 0x00b0a530

struct ScatterVec {                                      // sp_vector<ScatterE, 256>
    ScatterE* mpBegin;                                   // +0x0000
    ScatterE* mpEnd;                                     // +0x0004
    ScatterE* mpCap;                                     // +0x0008
    void*     mPad0c;                                    // +0x000c
    ScatterE* mpInline;                                  // +0x0010
    void*     mPad14;                                    // +0x0014
    char      mBuf[0x19a800];                            // +0x0018
    ScatterE* Insert(ScatterE* pos, const ScatterE& v);  // 0x00b0c110 (ret 8)
    void InsertGrow(ScatterE* pos, const ScatterE& v);   // 0x00b0bfa0 (ret 8)
    void DestroyElements(ScatterE* first, ScatterE* last);  // 0x00b051f0 (ret 8)
};

// ---------------------------------------------------------------------------------------------------
// The 0x24-byte grid element: a small polymorphic base plus 0x20 payload bytes.
// ---------------------------------------------------------------------------------------------------
struct ScatterBase {
    ScatterBase();                                       // 0x007cef40
    virtual ~ScatterBase();                              // 0x007ced20
};
struct Elem24 : ScatterBase {
    char mRest[0x20];                                    // +0x0004
};
struct Elem24Vec {
    Elem24* mpBegin;                                     // +0x0000
    Elem24* mpEnd;                                       // +0x0004
    Elem24* mpCap;                                       // +0x0008
    void InsertN(Elem24* pos, unsigned int count, const Elem24& v); // 0x00b0af40 (ret 0xc)
    void DestroyRange(Elem24* first, Elem24* last);      // 0x00b0aee0 (ret 8)
    void DestroyStorage();                               // 0x00b002a0
    void Resize(unsigned int n);                         // 0x00b0bd10 (ret 4)
};

// Inline-buffer vectors of 4-byte references.
struct RefVec {
    void* mpBegin; void* mpEnd; void* mpCap; void* mPad0c; void* mpInline; void* mpAlloc;
    char  mBuf[0x100];                                   // inline buffer
    void Destroy();                                      // 0x00ae6970
};
struct RefVecBig {
    void* mpBegin; void* mpEnd; void* mpCap; void* mPad0c; void* mpInline; void* mpAlloc;
    char  mBuf[0x1000];                                  // inline buffer
    void Destroy();                                      // 0x00ae6970
};

// Spatial-entry vector: the free path walks the range, then frees a heap block through its [-4] header.
struct SpatialVec {
    void*    mpBegin;                                    // +0x00
    void*    mpEnd;                                      // +0x04
    void*    mpCap;                                      // +0x08
    char     mPad0c[8];                                  // +0x0c
    uint32_t mFlag;                                      // +0x14
    char     mBuf[0x400];                                // +0x18 inline buffer
    void ResetRange(void* first, void* last);            // 0x00b006f0 (ret 8)
};

// Gathered-entity vector: destroys its values, then frees through the [-4] header.
struct EntVec {
    void*    mpBegin;                                    // +0x00
    void*    mpEnd;                                      // +0x04
    void*    mpCap;                                      // +0x08
    char     mPad0c[8];                                  // +0x0c
    void*    mpAlloc;                                    // +0x14
    char     mBuf[0x80];                                 // +0x18 inline buffer
    void DestroyValues(void* first, void* last);         // 0x005f3680 (ret 8)
};

struct PaintMgr {
    void*    mVtable;                                    // +0x0000
    void*    mVtableSub;                                 // +0x0004
    void*    mVtable3;                                   // +0x0008
    char     mGonzagoRest[0x14];                         // +0x000c
    uint32_t mHandler;                                   // +0x0020
    uint32_t mHandlerArg0;                               // +0x0024
    uint32_t mHandlerArg1;                               // +0x0028
    uint32_t mHandlerArg2;                               // +0x002c
    uint32_t mHandlerArg3;                               // +0x0030
    char     mPoolA[0x0c];                               // +0x0034
    void*    mpPoolAChain;                               // +0x0040
    char     mPad044[0x8080 - 0x0044];                   // +0x0044
    char     mPoolB[0x0c];                               // +0x8080
    void*    mpPoolBChain;                               // +0x808c
    char     mPad090[0x160e8 - 0x8090];                  // +0x8090
    SpatialVec mSpatial;                                 // +0x160e8
    void*    mpGrid;                                     // +0x16500
    EntVec   mEnt;                                       // +0x16504
    uint32_t mObjMask;                                   // +0x1659c
    char     mPoolC[0x0c];                               // +0x165a0
    void*    mpPoolCChain;                               // +0x165ac
    char     mPad165b0[0x1e5f0 - 0x165b0];               // +0x165b0
    ScatterVec mScatter;                                 // +0x1e5f0
    char     mPad1b8e08[8];                              // +0x1b8e08
    uint32_t mUnk1b8e10;                                 // +0x1b8e10
    RefVec   mVec1;                                      // +0x1b8e14
    int32_t  mUnk1b8f2c;                                 // +0x1b8f2c
    Elem24Vec mItems;                                    // +0x1b8f30
    char     mPad1b8f3c[8];                              // +0x1b8f3c
    RefVec   mVec3;                                      // +0x1b8f44
    RefVec   mVec4;                                      // +0x1b905c
    RefVecBig mVec5;                                     // +0x1b9174
    uint32_t mFlags1;                                    // +0x1ba18c
    uint32_t mUnk1ba190;                                 // +0x1ba190

    PaintMgr();                                          // 0x00b0bdb0
    ~PaintMgr();                                         // 0x00b0bb50
};

// @ 0x00b0bdb0
PaintMgr::PaintMgr()
{
    mVtable = gVtablePaintBase;
    ((GonzagoSub*)&mVtableSub)->Construct();
    mVtableSub = gVtablePaintSub;
    mVtable = gVtablePaint;
    mVtable3 = gVtablePaint3;

    mHandler = 0;
    mHandlerArg0 = 0;
    mHandlerArg1 = 0;
    mHandlerArg2 = 0;
    mHandlerArg3 = 0;

    ((PaintPool*)mPoolA)->Construct();                   // 0x00b05a80
    ((PaintPool*)mPoolB)->ConstructAlt();                // 0x00b05ae0

    void* p = mSpatial.mBuf;
    mSpatial.mpBegin = p;
    mSpatial.mpEnd = p;
    p = (char*)p + 0x400;
    mSpatial.mpCap = p;
    mSpatial.mFlag = 0;

    p = mEnt.mBuf;
    mEnt.mpBegin = p;
    mEnt.mpEnd = p;
    p = (char*)p + 0x80;
    mEnt.mpAlloc = 0;
    mEnt.mpCap = p;

    mObjMask = 0;
    ((PaintPool*)mPoolC)->Construct();                   // 0x00b05a80

    p = mScatter.mBuf;
    mScatter.mpInline = (ScatterE*)p;
    mScatter.mpEnd = (ScatterE*)p;
    mScatter.mpBegin = (ScatterE*)p;
    p = (char*)p + 0x19a800;
    mScatter.mpCap = (ScatterE*)p;

    mUnk1b8e10 = 0;
    mVec1.mpAlloc = 0;
    p = mVec1.mBuf;
    mVec1.mpBegin = p;
    mVec1.mpEnd = p;
    p = (char*)p + 0x100;
    mVec1.mpCap = p;

    mUnk1b8f2c = -1;
    mItems.mpBegin = 0;
    mItems.mpEnd = 0;
    mItems.mpCap = 0;

    mVec3.mpAlloc = 0;
    p = mVec3.mBuf;
    mVec3.mpBegin = p;
    mVec3.mpEnd = p;
    p = (char*)p + 0x100;
    mVec3.mpCap = p;

    p = mVec4.mBuf;
    mVec4.mpBegin = p;
    mVec4.mpEnd = p;
    p = (char*)p + 0x100;
    mVec4.mpCap = p;
    mVec4.mpAlloc = 0;

    p = mVec5.mBuf;
    mVec5.mpBegin = p;
    mVec5.mpEnd = p;
    p = (char*)p + 0x1000;
    mVec5.mpCap = p;
    mVec5.mpAlloc = 0;

    mFlags1 = 0;
    mUnk1ba190 = 0;
    mFlags1 &= ~3u;

    void* mem = EaAllocate(0x84, "Simulator/HierGrid", 0, 0, 0, 0);
    mpGrid = mem ? new (mem) HierGrid() : 0;

    mItems.Resize(1);
}

// @ 0x00b0bb50
PaintMgr::~PaintMgr()
{
    void* grid = mpGrid;
    mVtable = gVtablePaint;
    mVtableSub = gVtablePaintSub;
    mVtable3 = gVtablePaint3;

    if (grid) {
        ((HierGrid*)grid)->~HierGrid();                  // 0x00750310
        operator delete(grid);
    }

    mItems.DestroyRange(mItems.mpBegin, mItems.mpEnd);   // 0x00b0aee0
    mVec5.Destroy();                                     // 0x00ae6970
    mVec4.Destroy();
    mVec3.Destroy();
    mItems.DestroyStorage();                             // 0x00b002a0
    mVec1.Destroy();

    mScatter.DestroyElements(mScatter.mpBegin, mScatter.mpEnd);   // 0x00b051f0
    void* scatterBuf = mScatter.mpBegin;
    if (scatterBuf && scatterBuf != mScatter.mpInline)
        operator delete(scatterBuf);

    ((PaintPool*)mPoolC)->ReleaseChain(mpPoolCChain);    // 0x00b04350

    mEnt.DestroyValues(mEnt.mpBegin, mEnt.mpEnd);        // 0x005f3680
    if (mEnt.mpBegin && ((uint32_t*)mEnt.mpBegin)[-1])
        operator delete(mEnt.mpBegin);

    mSpatial.ResetRange(mSpatial.mpBegin, mSpatial.mpEnd);     // 0x00b006f0
    if (mSpatial.mpBegin && ((uint32_t*)mSpatial.mpBegin)[-1])
        operator delete(mSpatial.mpBegin);

    ((PaintPool*)mPoolB)->WalkChain(mpPoolBChain);       // 0x00b04420
    ((PaintPool*)mPoolA)->ReleaseChain(mpPoolAChain);    // 0x00b04350

    if (mHandler) {
        RemoveMessageHandler((void*)mHandler, mHandlerArg0, mHandlerArg1, mHandlerArg2, mHandlerArg3);
        mHandler = 0;
    }

    ((GonzagoSub*)&mVtableSub)->~GonzagoSub();           // 0x00b5b9a0
    mVtable = gVtablePaintDtor;
}

// @ 0x00b0bd10
void Elem24Vec::Resize(unsigned int n)
{
    if (n > (unsigned int)(mpEnd - mpBegin)) {
        Elem24 tmp;
        InsertN(mpEnd, n - (unsigned int)(mpEnd - mpBegin), tmp);
    } else {
        DestroyRange(mpBegin + n, mpEnd);
    }
}

// @ 0x00b0bfa0
void ScatterVec::InsertGrow(ScatterE* pos, const ScatterE& v)
{
    if (mpEnd != mpCap) {
        ScatterE* src = (ScatterE*)&v;
        if (src >= pos && src < mpEnd)
            src = (ScatterE*)((char*)src + sizeof(ScatterE));
        new ((void*)mpEnd) ScatterE(*(mpEnd - 1));
        ScatterCopyBackward(pos, mpEnd - 1, mpEnd);
        pos->mKey = src->mKey;
        pos->mPayload.AssignFrom(src->mPayload);
        ++mpEnd;
    } else {
        unsigned int count = (unsigned int)(mpEnd - mpBegin);
        unsigned int cap = count ? count * 2 : 1;
        ScatterE* buf = (ScatterE*)EaAllocate(cap * sizeof(ScatterE), "Simulator", 0, 0, 0, 0xd1);
        if (buf) {
            ScatterCopyRange(mpBegin, pos, buf);
            ScatterE* newpos = (ScatterE*)ScatterFillRange(mpBegin, pos, buf);
            if (newpos) {
                newpos->mKey = v.mKey;
                new (newpos) ScatterE(*(ScatterE*)&v);
            }
            ScatterCopyRange(pos, mpEnd, newpos + 1);
            ScatterE* newend = (ScatterE*)ScatterFillRange(pos, mpEnd, newpos + 1);
            if (mpBegin && mpBegin != mpInline)
                operator delete(mpBegin);
            mpBegin = buf;
            mpEnd = newend;
            mpCap = buf + cap;
        }
    }
}

// @ 0x00b0c110
ScatterE* ScatterVec::Insert(ScatterE* pos, const ScatterE& v)
{
    unsigned int index = (unsigned int)(pos - mpBegin);
    if (pos == mpEnd && mpEnd != mpCap) {
        ScatterE* p = mpEnd;
        mpEnd = p + 1;
        new (p) ScatterE(v);
    } else {
        InsertGrow(pos, v);
    }
    return mpBegin + index;
}
