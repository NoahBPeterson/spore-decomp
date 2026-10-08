// FUN_00b08670 @ 0x00B08670 (2068 bytes, __thiscall, one uint argument, ret 4).
//
// Per-frame update of a manager that keeps a vector of item pointers at +0x1b905c / +0x1b9060 (the manager
// class is unrecovered; names below are Claude-coined from behaviour). Each item has a cSpatialObject
// sub-object at +0x34 (vtable slots: 0x2c GetPosition, 0x38 SetPosition, 0x6c GetExtents, 0x70
// GetBoundingRadius, 0x94 SetModelKey) and a small state machine at +0x16c:
//   1  walking: damp the motion, snap the centre to the planet, and when it has come to rest (within the
//      radius) switch to state 2, pushing the item out of its target item's bounding sphere on the way
//   2  waiting: insert the item (sorted by distance from the reference position) into a local vector, count
//      the timer up and switch to state 4 (with a model key) once it has run out
//   4  fading: count the timer up, drop the effect object at +0x108 and go to state 5
//   5  erase the item from the manager's vector (the returned iterator replaces the loop iterator)
//   others: ignored.
// Items with a null pointer or flag 0x10 in the byte at +0x84 are skipped.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc; x87 sqrt/fild with SSE arithmetic, like s01019090)
#include "types.h"
#include <math.h>

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };

#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

extern const Vector3 g_167af5c;            // 0x0167af5c
extern const ResourceKey g_1567410;        // 0x01567410
extern uint32_t g_15673a4;                 // 0x015673a4 (state-2 timeout)
extern uint32_t g_167b550;                 // 0x0167b550 (state-4 timeout)

// cSpatialObject interface (ModAPI Simulator::cSpatialObject; slot offsets confirmed in the binary)
struct cSpatialObject
{
    PV8 PV2 PV                                         // slots 0..10
    virtual const Vector3* GetPosition();              // +0x2c
    PV2
    virtual void SetPosition(const Vector3* v);        // +0x38
    PV8 PV4                                            // slots 15..26
    virtual const float* GetExtents(void* tmp);        // +0x6c (min xyz, max xyz)
    virtual float GetBoundingRadius();                 // +0x70
    PV8                                                // slots 29..36
    virtual void SetModelKey(const ResourceKey* key);  // +0x94
};

struct IRefCounted { virtual int AddRef(); virtual int Release(); };

struct Target                                          // the item returned by Item::FUN_00b058a0
{
    char pad000[0x10];
    Vector3 mPos;                                      // +0x10
    char pad01c[0x6c - 0x1c];
    float mRadius;                                     // +0x6c
};

struct Item : public IRefCounted
{
    char pad004[0x34 - 4];
    cSpatialObject mSpatial;                           // +0x34 (own vtable)
    char pad038[0x84 - 0x38];
    uint8_t mFlags84;                                  // +0x84 (0x10 = dead)
    char pad085[0xa3 - 0x85];
    bool mFlagA3;                                      // +0xa3
    bool mFlagA4;                                      // +0xa4
    bool mFlagA5;                                      // +0xa5
    char pad0a6[0x108 - 0xa6];
    IRefCounted* mpEffect;                             // +0x108
    char pad10c[0x148 - 0x10c];
    uint32_t mFlags148;                                // +0x148
    char pad14c[0x168 - 0x14c];
    uint32_t mTimer;                                   // +0x168
    int mState;                                        // +0x16c
    Target* FUN_00b058a0();                            // 0x00b058a0
};

// local eastl::vector<AutoRefCount<Item>, sp_vector_allocator> with a 64-entry inline buffer
struct AutoRef
{
    Item* mp;
    AutoRef(Item* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRef() { if (mp) mp->Release(); }
};
struct ItemVector
{
    Item** mpBegin;
    Item** mpEnd;
    Item** mpCapacity;
    uint32_t mAlloc[2];
    int mHeader;
    Item* mBuf[64];
    ItemVector() { mHeader = 0; mpBegin = mBuf; mpEnd = mBuf; mpCapacity = mBuf + 64; }
    ~ItemVector();                                     // 0x00ae6970
    Item** insert(Item** pos, const AutoRef& v);       // 0x00b05b40 (ret 8)
};

struct Model { char pad[0x20]; int mMode; void FUN_00b452f0(cSpatialObject* s, const Vector3* v, int flag); };   // 0x00b452f0 (ret 0xc)
Model* __cdecl FUN_00b3d310();                         // 0x00b3d310 (mode at +0x20)

struct IReferencePoint
{
    PV8 PV4 PV2
    virtual void GetPos(Vector3* out, int flag, Vector3 v);   // +0x38
};
IReferencePoint* __cdecl FUN_00b3d240();               // 0x00b3d240

struct PlanetModelT
{
    void FUN_00b81630(Vector3* out, const Vector3* in);                        // 0x00b81630 (ret 8)
    Vector3* FUN_00b82b40(Vector3* out, const Vector3* in, bool flag);         // 0x00b82b40 (ret 0xc)
};
PlanetModelT* __cdecl PlanetModel();                   // 0x00b3d350

struct VelHolder { char pad[0xd0]; float vx, vy, vz; };   // +0xd0
struct VelOwner { char pad[0x58]; VelHolder* mp58; };      // +0x58
VelOwner* __cdecl FUN_00b53940(cSpatialObject* s);     // 0x00b53940
bool __cdecl FUN_00b54200(cSpatialObject* s);          // 0x00b54200
Vector3 __cdecl normalized_safe(const Vector3& v);     // 0x00449c20
Vector3 __cdecl Normalize(const Vector3& v);           // 0x00436ce0

struct ItemManager
{
    char pad000[0x1b905c];
    Item** mpBegin;                                    // +0x1b905c
    Item** mpEnd;                                      // +0x1b9060
    Item** FUN_00b06a40(Item** it, bool erase);        // 0x00b06a40 (ret 8)
    void Update(uint32_t dt);
};

void ItemManager::Update(uint32_t dt)   // @ 0x00B08670
{
    ItemVector sorted;
    Vector3 refPos;
    FUN_00b3d240()->GetPos(&refPos, 1, g_167af5c);

    Item** it = mpBegin;
    if (it != mpEnd)
    {
        do
        {
            Item* item = *it;
            if (item == 0 || (item->mFlags84 & 0x10))
            {
                ++it;
                continue;
            }
            const int state = item->mState;
            switch (state)
            {
            case 1:
            {
                if (FUN_00b3d310()->mMode == 0)
                {
                    VelOwner* owner = FUN_00b53940(&item->mSpatial);
                    if (item->mFlagA5 ||
                        (owner && (owner->mp58->vx * owner->mp58->vx + owner->mp58->vy * owner->mp58->vy +
                                   owner->mp58->vz * owner->mp58->vz) < 1.1f))
                    {
                        item->mFlagA5 = false;
                        FUN_00b54200(&item->mSpatial);
                        Vector3 dir = *item->mSpatial.GetPosition();
                        dir = normalized_safe(dir);
                        const float f = (float)dt * -0.0098f;
                        dir.x = dir.x * f;
                        dir.y = dir.y * f;
                        dir.z = dir.z * f;
                        FUN_00b3d310()->FUN_00b452f0(&item->mSpatial, &dir, 1);
                    }
                }
                else if (item->mFlagA5)
                {
                    item->mFlagA5 = false;
                }

                char extentsTmp[24];
                const float* b = item->mSpatial.GetExtents(extentsTmp);
                Vector3 center;
                center.x = (b[3] + b[0]) * 0.5f;
                center.y = (b[4] + b[1]) * 0.5f;
                center.z = (b[5] + b[2]) * 0.5f;
                Vector3 ground;
                PlanetModel()->FUN_00b81630(&ground, &center);
                Vector3 d;
                d.x = center.x - ground.x;
                d.y = center.y - ground.y;
                d.z = center.z - ground.z;
                const float dist2 = d.z * d.z + d.y * d.y + d.x * d.x;
                if (!((item->mSpatial.GetBoundingRadius() + 0.03f) < dist2))
                {
                    if (item->mState != 2)
                    {
                        item->mTimer = 0;
                        item->mState = 2;
                    }
                    Target* t = item->FUN_00b058a0();
                    if (t)
                    {
                        const float tradius = t->mRadius;
                        const float r = item->mSpatial.GetBoundingRadius() + 0.05f;
                        Vector3 v;
                        v.x = center.x - t->mPos.x;
                        v.z = center.z - t->mPos.z;
                        v.y = center.y - t->mPos.y;
                        const float len = sqrtf(v.x * v.x + v.z * v.z + v.y * v.y);
                        const float sum = r + tradius;
                        if (sum > len && len > 1.52587890625e-05f)
                        {
                            const float inv = 1.0f / len;
                            Vector3 p;
                            p.x = inv * v.x * sum + t->mPos.x;
                            p.y = v.y * inv * sum + t->mPos.y;
                            p.z = v.z * inv * sum + t->mPos.z;
                            Vector3 out;
                            const Vector3* snapped = PlanetModel()->FUN_00b82b40(&out, &p, false);
                            p = *snapped;
                            item->mSpatial.SetPosition(&p);
                        }
                    }
                }
                if (FUN_00b3d310()->mMode == 2)
                {
                    const Vector3* pos = item->mSpatial.GetPosition();
                    Vector3 surf;
                    PlanetModel()->FUN_00b81630(&surf, pos);
                    Vector3 w;
                    w.x = surf.x - pos->x;
                    w.y = surf.y - pos->y;
                    w.z = surf.z - pos->z;
                    const float wlen2 = w.x * w.x + w.z * w.z + w.y * w.y;
                    if (wlen2 > 0.1f)
                    {
                        Vector3 target = surf;
                        const float step = (float)dt * 0.0098f;
                        if (step * step < wlen2)
                        {
                            Vector3 n = Normalize(w);
                            target.x = step * n.x + pos->x;
                            target.y = n.y * step + pos->y;
                            target.z = n.z * step + pos->z;
                        }
                        item->mSpatial.SetPosition(&target);
                    }
                    else
                    {
                        item->mSpatial.SetPosition(&surf);
                    }
                }
                ++it;
                break;
            }
            case 2:
            {
                const Vector3* p = item->mSpatial.GetPosition();
                const float dist2 = (p->x - refPos.x) * (p->x - refPos.x) + (p->z - refPos.z) * (p->z - refPos.z) +
                                    (p->y - refPos.y) * (p->y - refPos.y);
                Item** pos = sorted.mpBegin;
                while (pos != sorted.mpEnd)
                {
                    const Vector3* q = (*pos)->mSpatial.GetPosition();
                    const float od2 = (q->x - refPos.x) * (q->x - refPos.x) + (q->z - refPos.z) * (q->z - refPos.z) +
                                      (q->y - refPos.y) * (q->y - refPos.y);
                    if (dist2 <= od2)
                        break;
                    ++pos;
                }
                {
                    AutoRef ref(item);
                    sorted.insert(pos, ref);
                }
                if (item->mTimer == 0 && item->mFlagA5)
                {
                    item->mFlagA5 = false;
                    FUN_00b54200(&item->mSpatial);
                }
                item->mTimer += dt;
                if (!(item->mFlags148 & 1) && item->mTimer > g_15673a4 && item->mpEffect == 0 && item->mState != 4)
                {
                    item->mFlagA4 = false;
                    item->mFlagA3 = false;
                    item->mSpatial.SetModelKey(&g_1567410);
                    ++it;
                    item->mState = 4;
                    break;
                }
                ++it;
                break;
            }
            case 4:
            {
                item->mTimer += dt;
                if (item->mTimer > g_167b550 && state != 5)
                {
                    IRefCounted* effect = item->mpEffect;
                    if (effect)
                    {
                        item->mpEffect = 0;
                        effect->Release();
                    }
                    ++it;
                    item->mState = 5;
                    break;
                }
                ++it;
                break;
            }
            case 5:
                it = FUN_00b06a40(it, true);
                break;
            default:
                ++it;
                break;
            }
        } while (it != mpEnd);
    }
}
