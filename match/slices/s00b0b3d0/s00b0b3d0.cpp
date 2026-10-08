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
