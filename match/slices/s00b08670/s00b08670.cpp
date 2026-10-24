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
#include <string.h>

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
    PV                                                 // slot 15 (+0x3c)
    virtual void SetF40(float v);                      // +0x40
    PV8 PV2                                            // slots 17..26
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

struct Model { char pad[0x20]; int mMode; void FUN_00b452f0(cSpatialObject* s, const Vector3* v, int flag); void FUN_00b453a0(cSpatialObject* s); };   // 0x00b452f0 (ret 0xc), 0x00b453a0 (ret 4)
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
    char pad000[0x1b8f44];
    Item** mpPendingBegin;                             // +0x1b8f44
    Item** mpPendingEnd;                               // +0x1b8f48
    char pad18f4c[0x1b905c - 0x1b8f4c];
    Item** mpBegin;                                    // +0x1b905c
    Item** mpEnd;                                      // +0x1b9060
    Item** FUN_00b06a40(Item** it, bool erase);        // 0x00b06a40 (ret 8)
    Item*  FUN_00b08e90();                             // 0x00b08e90
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

// ===================================================================================================================
// Remaining functions of this slice (gold7): model-instance spawn/acquire, spatial query, hit-box model init,
// bounding-sphere query and the effect-pool init.
// ===================================================================================================================

extern uint32_t g_167afa8;                 // 0x0167afa8
extern const float g_1485720;              // 0x01485720 (_HK_REAL_ONE)
struct Data9 { uint32_t d[9]; };
extern const Data9 g_167b554;              // 0x0167b554
void __cdecl ea_delete(void* p);           // 0x00f47380

// ---------------- 0x00b08e90 ---------------------------------------------------------------------------------------

struct Viewer { PV4 PV2 PV virtual void* v1c(); };                    // +0x1c
struct AppObj { PV8 PV8 PV4 virtual void* v50(); };                   // +0x50
AppObj* __cdecl App();                                                // 0x0067dd10

struct Camera
{
    void GetCameraLocationInfo(Vector3* a, Vector3* b, Vector3* c, Vector3* d) const;   // 0x007c3d30 (ret 0x10)
};

// @ 0x00b08e90
Item* ItemManager::FUN_00b08e90()
{
    Item* result = 0;
    if ((uint32_t)(mpPendingEnd - mpPendingBegin) > 0)
    {
        Item* item = mpPendingEnd[-1];
        if (item)
        {
            item->AddRef();
            result = item;
        }
        --mpPendingEnd;
        Item* popped = *mpPendingEnd;
        if (popped)
            popped->Release();
    }
    else
    {
        Camera* cam = (Camera*)((Viewer*)App()->v50())->v1c();
        Vector3 camPos = g_167af5c;
        Vector3 camUp = g_167af5c;
        if (cam)
            cam->GetCameraLocationInfo(&camPos, &camUp, 0, 0);
        Item** end = mpEnd;
        Item** best = end;
        float bestDist = 0.0f;
        for (Item** it = mpBegin; it != end; ++it)
        {
            Item* item = *it;
            if (!item)
                continue;
            if (item->mState == 3)
                continue;
            if (item->mFlags148 & 1)
                continue;
            if (item->mpEffect)
                continue;
            const Vector3* p = item->mSpatial.GetPosition();
            const float dy = p->y - camPos.y;
            const float dx = p->x - camPos.x;
            const float dz = p->z - camPos.z;
            const float d = dz * dz + dy * dy + dx * dx;
            if (d > bestDist)
            {
                best = it;
                bestDist = d;
            }
        }
        if (best == end)
            return 0;
        Item* item = *best;
        if (item)
        {
            item->AddRef();
            result = item;
        }
        FUN_00b06a40(best, false);
    }
    if (result)
    {
        result->mSpatial.SetF40(1.0f);
        if (FUN_00b3d310())
            FUN_00b3d310()->FUN_00b453a0(&result->mSpatial);
        result->Release();
    }
    return result;
}

// ---------------- 0x00b09070 ---------------------------------------------------------------------------------------

struct ResObj
{
    virtual void AddRef();                                        // +0x00
    virtual void Release();                                       // +0x04
    PV                                                            // +0x08
    virtual ResObj* v0c(uint32_t a, uint32_t b, uint32_t c);      // +0x0c
    void FUN_00b79c30();                                          // 0x00b79c30
};

struct SPVec
{
    uint32_t* mpBegin;                                    // +0x00
    uint32_t* mpEnd;                                      // +0x04
    uint32_t* mpCapacity;                                 // +0x08
    uint32_t mPad0c;                                      // +0x0c
    uint32_t mPad10;                                      // +0x10
    uint32_t mAlloc;                                      // +0x14
    void FUN_00d01790(uint32_t n);                        // 0x00d01790 (ret 4)
    void DoInsertKey(uint32_t* pos, const uint32_t& key); // 0x00b96600 (ret 8)
    void erase(uint32_t* first, uint32_t* last)           // eastl::vector::erase, inlined
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
    }
};

template <class T> const T& Min(const T& a, const T& b) { return (a < b) ? a : b; }

ResObj* __stdcall FUN_00b3d3c0(uint32_t a1, SPVec* v, uint32_t n, float f, uint32_t one, uint32_t zero);   // 0x00b3d3c0
void __cdecl FUN_00b062c0(uint32_t* begin, uint32_t* end, int a3);                                          // 0x00b062c0

struct cQueryMgr
{
    uint32_t FindNth(uint32_t key, uint32_t a, uint32_t b);           // 0x00b03320 (ret 0xc)
    void FUN_00b09070(uint32_t a1, float a2, SPVec* out, int a4);
};

// @ 0x00b09070
void cQueryMgr::FUN_00b09070(uint32_t a1, float a2, SPVec* out, int a4)
{
    uint32_t buf[256];
    SPVec local;
    local.mpBegin = buf;
    local.mpEnd = buf;
    local.mpCapacity = buf + 256;
    local.mAlloc = 0;

    out->erase(out->mpBegin, out->mpEnd);

    ResObj* q = FUN_00b3d3c0(a1, &local, 6, a2, 1, 0);
    q->FUN_00b79c30();

    out->FUN_00d01790((uint32_t)(local.mpEnd - local.mpBegin));

    for (uint32_t* it = local.mpBegin; it != local.mpEnd; ++it)
    {
        uint32_t* e = (uint32_t*)*it;
        uint32_t key;
        switch (e[0x88 / 4])
        {
        case 0: key = 0x3a8be428; break;
        case 1: key = 0x29c388a;  break;
        case 2: key = 0x6d60a1cc; break;
        default: continue;
        }
        uint32_t r = FindNth(key, e[0x50 / 4], e[0x5c / 4]);
        if (r)
        {
            if (out->mpEnd < out->mpCapacity)
                *out->mpEnd++ = r;
            else
                out->DoInsertKey(out->mpEnd, r);
        }
    }

    if (a4)
        FUN_00b062c0(out->mpBegin, out->mpEnd, a4);

    struct AllocHeader { uint32_t mFlag; };
    if (local.mpBegin && ((AllocHeader*)local.mpBegin)[-1].mFlag != 0)
        ea_delete(local.mpBegin);
}

// ---------------- 0x00b091d0 ---------------------------------------------------------------------------------------

struct ModelInst
{
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV2 PV      // slots 0..90
    virtual void v16c(int a);                              // +0x16c
    virtual void v170(int a);                              // +0x170
    uint32_t mField04;                                     // +0x04
    uint16_t mWord08;                                      // +0x08
    uint16_t mWord0a;                                      // +0x0a
    Vector3  mPos;                                         // +0x0c
    float    mF18;                                         // +0x18
    Data9    mData1c;                                       // +0x1c
    int32_t  mRefCount;                                    // +0x40
};

struct ModelList
{
    ModelInst** mpBegin;                                   // +0x00
    ModelInst** mpEnd;                                     // +0x04
    ModelInst** mpCapacity;                                // +0x08
    void FUN_00473270(uint32_t n);                         // 0x00473270 (ret 4)
};

struct ModelMgr { PV4 PV2 PV virtual void* v1c(uint32_t id); };   // +0x1c
ModelMgr* __cdecl ModelManager();                                 // 0x0067dd80

struct cCreatureHitBoxes
{
    char pad000[0x16504];
    ModelList mList;                                       // +0x16504
    void FUN_00b06cd0();                                   // 0x00b06cd0
    void FUN_00b091d0();
};

// @ 0x00b091d0
void cCreatureHitBoxes::FUN_00b091d0()
{
    if ((uint32_t)(mList.mpEnd - mList.mpBegin) > 0)
        FUN_00b06cd0();

    ModelMgr* mm = ModelManager();
    ResObj* model = (ResObj*)mm->v1c(0xeb9968);
    if (model)
        model->AddRef();

    mList.FUN_00473270(0x14);

    const uint32_t n = (uint32_t)(mList.mpEnd - mList.mpBegin);
    for (uint32_t i = 0; i < n; ++i)
    {
        if (mList.mpBegin[i] == 0)
        {
            ResObj* made = model->v0c(0x2e81370, g_167afa8, 0x10);
            ModelInst* old = mList.mpBegin[i];
            if (made != (ResObj*)old)
            {
                if (made)
                    ++((ModelInst*)made)->mRefCount;
                mList.mpBegin[i] = (ModelInst*)made;
                if (old)
                {
                    if (old->mRefCount > 1)
                        --old->mRefCount;
                    else
                        old->v170((old->mField04 >> 31) & 1);
                }
            }
            ModelInst* inst = mList.mpBegin[i];
            inst->mData1c = g_167b554;
            inst->mF18 = g_1485720;
            inst->mPos = g_167af5c;
            inst->mWord08 = 0;
            inst->mWord0a = 0;
            inst->mField04 &= ~1u;
            inst->v16c(0);
        }
    }

    if (model)
        model->Release();
}

// ---------------- 0x00b09340 ---------------------------------------------------------------------------------------

struct BigElem
{
    char pad000[0x08];
    Vector3 mPos;                                          // +0x08
    float   mRadius;                                       // +0x14
    char pad018[0x28 - 0x18];
    Vector3 mCmp0;                                         // +0x28
    Vector3 mCmp1;                                         // +0x34
    Vector3 mCmp2;                                         // +0x40
    char pad04c[0x19a8 - 0x4c];
};

struct cBigList
{
    char pad000[0x1e5f0];
    BigElem* mpBegin;                                      // +0x1e5f0
    BigElem* mpEnd;                                        // +0x1e5f4
    void FUN_00b09340(Vector3* p, float radius, SPVec* out, bool full, Vector3* filter);
};

void __cdecl FUN_00b06420(uint32_t* begin, uint32_t* end, Vector3 v);   // 0x00b06420

// @ 0x00b09340
void cBigList::FUN_00b09340(Vector3* p, float radius, SPVec* out, bool full, Vector3* filter)
{
    const int n = (int)(mpEnd - mpBegin);
    if (n == 0)
    {
        out->erase(out->mpBegin, out->mpEnd);
        return;
    }

    out->FUN_00d01790(Min(n, 0x20));

    for (BigElem* e = mpBegin; e != mpEnd; ++e)
    {
        if (filter != 0 &&
            memcmp(filter, &e->mCmp0, sizeof(Vector3)) != 0 &&
            memcmp(filter, &e->mCmp1, sizeof(Vector3)) != 0 &&
            memcmp(filter, &e->mCmp2, sizeof(Vector3)) != 0)
            continue;

        const float dy = e->mPos.y - p->y;
        const float dz = e->mPos.z - p->z;
        const float dx = e->mPos.x - p->x;
        const float rr = e->mRadius + radius;
        const float d = dy * dy + dz * dz + dx * dx;
        if (rr * rr > d)
        {
            if (out->mpEnd < out->mpCapacity)
                *out->mpEnd++ = (uint32_t)&e->mPos;
            else
                out->DoInsertKey(out->mpEnd, (const uint32_t&)e->mPos);
        }
    }

    if (full)
        FUN_00b06420(out->mpBegin, out->mpEnd, *p);
}

// ---------------- 0x00b09510 ---------------------------------------------------------------------------------------

struct FixedPool
{
    void* mpHead;                                          // +0x00
    void* mpNext;                                          // +0x04
    void* mpStart;                                         // +0x08
    void* mpEnd;                                           // +0x0c
    uint32_t mSize;                                        // +0x10
    void init(void* p, uint32_t size, uint32_t itemSize, uint32_t align, uint32_t flags);   // 0x00921260 (ret 0x14)
};

struct cEffectPool
{
    char pad000[0x2c];
    char mBuffer[0xe000];                                  // +0x2c .. +0xe02c
    cEffectPool* FUN_00b09510(int a1);
    void FUN_00b00610(int a1, FixedPool* pool);            // 0x00b00610 (ret 8)
    void FUN_00b05ba0(int a1);                             // 0x00b05ba0 (ret 4)
};

// @ 0x00b09510
cEffectPool* cEffectPool::FUN_00b09510(int a1)
{
    FixedPool pool;
    pool.mpHead = 0;
    pool.init(mBuffer, 0xe000, 0x38, 8, 0);
    pool.mpStart = mBuffer;
    pool.mpEnd = (char*)pool.mpStart + 0xe000;
    pool.mSize = 0x38;
    FUN_00b00610(a1, &pool);
    FUN_00b05ba0(a1);
    return this;
}
