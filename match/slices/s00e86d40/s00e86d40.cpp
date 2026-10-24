// Slice s00e86d40: 0x00E86D40..0x00E87BE0.  The effect-locator binary tree used by the
// spatial-object views (ordered tree of bounding-sphere records over a free list), the two
// "collect records inside a sphere / inside a cylinder" queries built on top of it, and the
// ctor / dtor of Simulator::cBuildingView plus the cloud-tendril effect.
//
//   0x00e86d40  treePush          (128 B)  allocate a record and link two children under it
//   0x00e86dc0  treeNearest       (192 B)  walk down the tree to the closest descendant
//   0x00e86e80  treeRefit         (232 B)  re-fit the spheres of the ancestors
//   0x00e86f70  treeInsert        (133 B)  insert every node of the pending list
//   0x00e87000  treeInsertPending ( 61 B)  drain the global pending list
//   0x00e87040  treeRemove        (185 B)  detach one record and free it
//   0x00e87100  collectSphereRec  (241 B)  recursive sphere query
//   0x00e87200  collectSphere     ( 84 B)  sphere query entry (returns the count)
//   0x00e87260  collectSphereBFS  (251 B)  breadth-first sphere query
//   0x00e87360  collectCylinder   (500 B)  capsule/cylinder query
//   0x00e87560  view Init override          ( 21 B)
//   0x00e87580  view Init override B        ( 38 B)
//   0x00e875b0  cBuildingView::SetVisible   ( 64 B)
//   0x00e87600  SP::UpdateCloudTendril      (1391 B)
//   0x00e87b70  Simulator::cBuildingView::cBuildingView ( 97 B)
//   0x00e87be0  Simulator::cBuildingView::~cBuildingView (264 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (MSVC 2008 SP1).
#include "types.h"
#include <math.h>
#include <string.h>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

// ---------------------------------------------------------------------------
// Raw virtual-call / field helpers.
// ---------------------------------------------------------------------------
#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))
#define VC4(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4))
#define FI32(p, off)   (*(int*)((char*)(p) + (off)))
#define FU8(p, off)    (*(u8*)((char*)(p) + (off)))
#define FU32(p, off)   (*(u32*)((char*)(p) + (off)))
#define FF32(p, off)   (*(float*)((char*)(p) + (off)))

// ---------------------------------------------------------------------------
// Float constants (real .rdata addresses, so the relocation resolves).
// ---------------------------------------------------------------------------
extern const float kHalf;          // 0x01471064 (0.5f)
extern const float kForty;         // 0x013f08c0 (40.0f)
extern const float kTiny;          // 0x013ec4b8 (1e-08f)
extern const float kTenth;         // 0x01488874 (0.1f)
extern const float kNegZero4[4];   // 0x013eb8b0 (xorps sign mask)
extern const float kSpacing1;      // 0x01470f1c (2.0f)
extern const float kSpacing2;      // 0x013eb95c (3.0f)
extern const float kSpacing3;      // 0x014853e0 (4.0f)
extern const float kSpacing4;      // 0x01486110 (5.0f)
extern const float kSpacing5;      // 0x0147b9f0 (6.0f)
extern const float kSpacing6;      // 0x013f8698 (7.0f)
extern const float kSpacing7;      // 0x013eeda0 (8.0f)
extern const float kOne;           // 0x01485720 (1.0f)
extern const float kOneAndAHalf;   // 0x01485548 (1.5f)

// ---------------------------------------------------------------------------
// Layouts.
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

// One record of the locator tree (0x1c bytes).  The first dword is the sphere
// centre's x while the record is live, and the free-list link while it is free
// (the pool chains free records through +0x00); hence the union.
struct EffRec {
    union {
        float   mCenter[3];  // +0x00  bounding-sphere centre
        EffRec* mpFreeNext;  // +0x00  free-list link (overlaps mCenter[0])
    };
    float   mRadius;         // +0x0c  bounding-sphere radius
    EffRec* mParent;         // +0x10  parent / free-list link
    EffRec* mChildA;         // +0x14  tree child A
    EffRec* mChildB;         // +0x18  tree child B
};

// The pool of records (reached through the container's +0x04 pointer).
struct EffPool {
    int     mCount;          // +0x00  live records
    int     mNextUnused;     // +0x04  next never-used slot index
    EffRec* mpFreeList;      // +0x08  free list (linked through +0x14)
    u8*     mpBase;          // +0x0c
    int     mStride;         // +0x10
    int     mCapacity;       // +0x14
};

// The container: the tree root, a pointer to the count and two pending lists.
struct EffTree {
    EffRec*   mpRoot;        // +0x00
    EffPool*  mpPool;        // +0x04
    EffRec*   mpPending;     // +0x08  list of records to insert (linked through +0x10)
    EffRec*   mpToRemove;    // +0x0c  list of records to remove (linked through +0x14)
};

// cGonzagoTimer (0x20 bytes): ctor/dtor are thiscall members taking no arguments.
struct cGonzagoTimer {
    void Construct();                                // 0x00b63890
    void Destruct();                                 // 0x00b638b0
    u32 mData[8];                                    // +0x00 .. +0x1f
};

// cSpatialObjectView (retail size 0x34, ctor 0x00e92af0).  Layout established by the
// neighbouring slices s00e92ca0 / s00e956f0.
class cSpatialObjectView {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void v28(void*);
    virtual void* GetModel();                            // +0x2c
    virtual void* GetTransform();                        // +0x30

    cSpatialObjectView();                                // 0x00e92af0
    ~cSpatialObjectView();                               // 0x00e92660
    void Init(void* gameData);                           // 0x00e92910
    void Init(void* a, void* b, void* c, void* d);       // 0x00e92740

    u32     mField04;                                    // +0x04
    u32     mField08;                                    // +0x08
    void*   mpObject;                                    // +0x0c
    void*   mpObjectCombatant;                           // +0x10
    u8      mField14;                                    // +0x14
    char    pad_15[3];
    Vec3    mColor;                                      // +0x18
    u32     mField24;                                    // +0x24
    u32     mField28;                                    // +0x28
    u32     mField2c;                                    // +0x2c
    u8      mbField30;                                   // +0x30
    u8      mbDamageState;                               // +0x31
    u8      mbField32;                                   // +0x32
    char    pad_33[1];
};

// Simulator::cBuildingView (retail size 0x88, ctor 0x00e87b70).
// Retail layout is shifted from the 2008 PDB (0x70), so members are named by
// role and offset.  +0x34/+0x80/+0x84 hold refcounted visual effects (release via
// virtual slot +0x04, stop via +0x0c); +0x3c..+0x54 are float scales/states;
// +0x58 is a visibility flag; +0x60 is a cGonzagoTimer (0x20).
class cBuildingView : public cSpatialObjectView {
public:
    void*   mpEffect_34;                                 // +0x34  refcounted effect
    union {
        int     mState_38;                               // +0x38  visibility/state word
        u8      mbVisible_38;                            // +0x38  low byte (SetVisible)
    };
    float   mScale_3c;                                   // +0x3c
    float   mScale_40;                                   // +0x40
    float   mScale_44;                                   // +0x44
    int     mXformIndices[4];                            // +0x48  sentinel -1 each
    u8      mbFlag_58;                                   // +0x58
    char    pad_59[7];
    cGonzagoTimer mTimer;                                // +0x60  cGonzagoTimer (0x20)
    void*   mpEffect_80;                                 // +0x80  refcounted effect
    void*   mpEffect_84;                                 // +0x84  refcounted effect

    void SetVisible(u8 b);                               // 0x00e875b0
    void ViewInit1(void* gameData);                      // 0x00e87560
    void ViewInit4(void* a, void* b, void* c, void* d);  // 0x00e87580
    cBuildingView();                                     // 0x00e87b70
    ~cBuildingView();                                    // 0x00e87be0
};

// ---------------------------------------------------------------------------
// Callees.
// ---------------------------------------------------------------------------
void cSpatialObjectView_DestroyAllEffects(void* obj, int flag);                 // 0x00c8b0a0

void  FUN_00e86930(EffTree* t, EffRec* n);                                      // 0x00e86930
void  FUN_00e86bb0(const float* a, float aR, const float* b, float bR,
                   float* out, float* outR);                                    // 0x00e86bb0
bool  IntersectRaySphere(const float* a, const float* b, const float* c,
                         float r, float* out);                                  // 0x005a9c40
void  FUN_00c8b220(u32 key, u32 id, int flag, float* out);                      // 0x00c8b220
void  FUN_00bd9480(void* self, float* out);                                     // 0x00bd9480
bool  FUN_00bd8240(void* self);                                                 // 0x00bd8240
bool  FUN_00bfc600(void* self);                                                 // 0x00bfc600
void* FUN_00bce5c0(void* self);                                                 // 0x00bce5c0
void* FUN_00fc7e50(void* self);                                                 // 0x00fc7e50

// The minimap-window helpers used by the dtor.
void* FUN_010666a0();                                             // 0x010666a0 (cdecl, no args)
struct MinimapHost { void* GetPanel(); };                         // 0x01067e60 (this=host, +0x31c)
struct cMinimapWin { void RemoveIcon(void* view, int a, int b); };// 0x00e0f9c0 (thiscall on the window)

// The AML window that owns the pending locator records (0x016c45b4).
struct cEffectWindow {
    int   GetPriority();                                  // 0x00e31100
    void* Remove(int* key);                               // 0x00b72230
};
extern cEffectWindow g_EffectWindow;                      // 0x016c45b4

// ---------------------------------------------------------------------------
// The locator tree.
// ---------------------------------------------------------------------------

// @ 0x00e86d40
EffRec* treePush(EffTree* t, EffRec* a, EffRec* b)
{
    EffPool* p = t->mpPool;
    EffRec* n;
    if (p->mCount == p->mCapacity) {
        n = 0;
    } else {
        if (p->mCount == p->mNextUnused) {
            n = (EffRec*)(p->mpBase + p->mCount * p->mStride);
            p->mCount++;
            p->mNextUnused++;
        } else {
            n = p->mpFreeList;
            p->mpFreeList = n->mpFreeNext;
            p->mCount++;
        }
    }

    FUN_00e86bb0(a->mCenter, a->mRadius, b->mCenter, b->mRadius, n->mCenter, &n->mRadius);
    n->mChildA = a;
    n->mRadius *= 1.1f;
    a->mParent = n;
    n->mChildB = b;
    b->mParent = n;
    return n;
}

// @ 0x00e86dc0
EffRec* treeNearest(const float* pos, float radius, EffRec* n)
{
    EffRec* childA = n->mChildA;
    if (childA == 0)
        return n;
    float px = pos[0], py = pos[1], pz = pos[2];
    for (;;) {
        EffRec* childB = n->mChildB;
        float a0 = childA->mCenter[0] - px;
        float a1 = childA->mCenter[1] - py;
        float a2 = childA->mCenter[2] - pz;
        float b0 = childB->mCenter[0] - px;
        float b1 = childB->mCenter[1] - py;
        float b2 = childB->mCenter[2] - pz;
        float da = a1 * a1 + a0 * a0 + a2 * a2;
        float db = b2 * b2 + b1 * b1 + b0 * b0;
        if (db > da)
            n = childA;
        else
            n = childB;
        childA = n->mChildA;
        if (childA == 0)
            return n;
    }
}

// @ 0x00e86e80
void treeRefit(EffRec* n)
{
    while (true) {
        EffRec* a = n->mChildA;
        float dx = a->mCenter[0] - n->mCenter[0];
        float dy = a->mCenter[1] - n->mCenter[1];
        float dz = a->mCenter[2] - n->mCenter[2];
        if (sqrtf(dx * dx + (dy * dy + dz * dz)) + a->mRadius <= n->mRadius) {
            EffRec* b = n->mChildB;
            float ex = b->mCenter[0] - n->mCenter[0];
            float ey = b->mCenter[1] - n->mCenter[1];
            float ez = b->mCenter[2] - n->mCenter[2];
            if (sqrtf((ez * ez + ey * ey) + ex * ex) + b->mRadius <= n->mRadius)
                break;
        }
        FUN_00e86bb0(n->mChildA->mCenter, n->mChildA->mRadius,
                     n->mChildB->mCenter, n->mChildB->mRadius,
                     n->mCenter, &n->mRadius);
        n = n->mParent;
        if (n == 0)
            return;
    }
}

// @ 0x00e86f70
void treeInsert(EffTree* t)
{
    while (t->mpToRemove != 0) {
        EffRec* n = t->mpToRemove;
        t->mpToRemove = n->mChildA;
        n->mChildA = 0;
        EffRec* root = t->mpPending;
        if (root == 0) {
            t->mpPending = n;
            n->mParent = 0;
        } else if (root->mChildA == 0) {
            n = treePush(t, n, root);
            t->mpPending = n;
            n->mParent = 0;
        } else {
            EffRec* best = treeNearest(n->mCenter, n->mRadius, root);
            EffRec* parent = best->mParent;
            EffRec** slot;
            if (parent->mChildA == best)
                slot = &parent->mChildA;
            else
                slot = &parent->mChildB;
            n = treePush(t, n, best);
            *slot = n;
            n->mParent = parent;
            treeRefit(parent);
        }
    }
}

// @ 0x00e87000
void treeInsertPending()
{
    int key = g_EffectWindow.GetPriority();
    EffRec* n;
    while ((n = (EffRec*)g_EffectWindow.Remove(&key)) != 0)
        treeInsert((EffTree*)n);
}

// @ 0x00e87040
void treeRemove(EffTree* t, EffRec* n, const float* pos, float radius)
{
    memcpy(n->mCenter, pos, sizeof(float) * 3);
    n->mRadius = radius;
    EffRec* old = n->mParent;
    if (old == 0)
        return;
    float dx = n->mCenter[0] - old->mCenter[0];
    float dy = n->mCenter[1] - old->mCenter[1];
    float dz = n->mCenter[2] - old->mCenter[2];
    if (!(old->mRadius < sqrtf(dx * dx + dy * dy + dz * dz) + radius))
        return;

    if (old == t->mpPending) {
        EffRec* sib = old->mChildA;
        if (sib == n)
            sib = old->mChildB;
        EffPool* p = t->mpPool;
        p->mCount--;
        old->mpFreeNext = p->mpFreeList;
        p->mpFreeList = old;
        t->mpPending = sib;
        sib->mParent = 0;
        n->mParent = 0;
        n->mChildA = t->mpToRemove;
        t->mpToRemove = n;
        return;
    }
    FUN_00e86930(t, n);
    n->mParent = 0;
    n->mChildA = t->mpToRemove;
    t->mpToRemove = n;
}

// ---------------------------------------------------------------------------
// Queries.
// ---------------------------------------------------------------------------

// @ 0x00e87100
void collectSphereRec(EffRec* n, const float* a, const float* b, void** out, int* count,
                      int max, float segLen)
{
    int i = *count;
    if (i == max)
        return;
    float dx = n->mCenter[0] - a[0];
    float dy = n->mCenter[1] - a[1];
    float dz = n->mCenter[2] - a[2];
    if (!(dx * dx + dy * dy + dz * dz <= n->mRadius * n->mRadius)) {
        float hit;
        if (!IntersectRaySphere(a, b, n->mCenter, n->mRadius, &hit))
            return;
        if (hit > segLen)
            return;
    }
    if (n->mChildA == 0) {
        out[i] = n->mChildB;
        *count = i + 1;
        return;
    }
    EffRec** p = &n->mChildA;
    for (int k = 2; k != 0; k--) {
        collectSphereRec(*p, a, b, out, count, max, segLen);
        p++;
    }
}

// @ 0x00e87200
int collectSphere(EffTree* t, const float* a, const float* b, void** out, int max, float segLen)
{
    if (t->mpToRemove != 0)
        treeInsert(t);
    if (t->mpPending == 0)
        return 0;
    int count = 0;
    collectSphereRec(t->mpPending, a, b, out, &count, max, segLen);
    return count;
}

// @ 0x00e87260
int collectSphereBFS(EffTree* t, float* pos, float radius, void** out, int max, EffRec** out2)
{
    if (t->mpToRemove != 0)
        treeInsert(t);
    EffRec* root = t->mpPending;
    if (root == 0)
        return 0;

    EffRec* queue[256];
    queue[0] = root;
    int n = 1;
    int k = 0;
    for (;;) {
        EffRec* node = queue[n - 1];
        n--;
        float dx = pos[0] - node->mCenter[0];
        float dy = pos[1] - node->mCenter[1];
        float dz = pos[2] - node->mCenter[2];
        float r = node->mRadius + radius;
        if (dx * dx + dy * dy + dz * dz < r * r) {
            if (node->mChildA == 0) {
                out[k] = node->mChildB;
                if (out2 != 0)
                    out2[k] = node;
                k++;
                if (k == max)
                    break;
            } else {
                queue[n] = node->mChildA;
                n++;
                queue[n] = node->mChildB;
                n++;
            }
        }
        if (n <= 0)
            break;
    }
    return k;
}

// @ 0x00e87360
int collectCylinder(EffTree* t, const float* a, const float* b, float r1, float r2,
                    void** out, int max)
{
    if (t->mpToRemove != 0)
        treeInsert(t);
    if (t->mpPending == 0)
        return 0;

    float mid[3];
    mid[0] = a[0] + b[0] * kHalf;
    mid[1] = a[1] + b[1] * kHalf;
    mid[2] = a[2] + b[2] * kHalf;

    EffRec* list[513];
    int count = collectSphereBFS(t, mid, sqrtf(r2 * r2 + r1 * r1), out, max, list + 1);
    for (int i = 0; i < count; i++) {
        EffRec* node = list[i + 1];
        float nr = node->mRadius;
        float d = (node->mCenter[2] - a[2]) * b[2]
                + (node->mCenter[1] - a[1]) * b[1]
                + (node->mCenter[0] - a[0]) * b[0];
        float e0 = (node->mCenter[2] - a[2]) - b[2] * d;
        float e1 = (node->mCenter[1] - a[1]) - b[1] * d;
        float e2 = (node->mCenter[0] - a[0]) - b[0] * d;
        if (!(d < -nr) && !(nr + r1 < d) && nr + r2 >= sqrtf(e2 * e2 + (e1 * e1 + e0 * e0)))
            continue;
        out[i] = out[count - 1];
        list[i + 1] = list[count];
        count--;
        i--;
    }
    return count;
}

// ---------------------------------------------------------------------------
// View overrides.
// ---------------------------------------------------------------------------

// @ 0x00e87560
void cBuildingView::ViewInit1(void* gameData)
{
    Init(gameData);
    mbFlag_58 = 0;
}

// @ 0x00e87580
void cBuildingView::ViewInit4(void* a, void* b, void* c, void* d)
{
    Init(a, b, c, d);
    mbFlag_58 = 0;
}

// @ 0x00e875b0
void cBuildingView::SetVisible(u8 b)
{
    mbVisible_38 = b;
    void* o = GetModel();
    if (b) {
        if (o) {
            void* p = *(void**)o;
            VC2(void, p, 0x16c, void*, o, int, 1);
        }
    } else {
        if (o) {
            void* p = *(void**)o;
            VC2(void, p, 0x16c, void*, o, int, 0);
        }
    }
}

// @ 0x00e87600
void UpdateCloudTendril(cBuildingView* view)
{
    void* obj = FUN_00fc7e50(view);
    if (obj == 0)
        return;

    void* building = (void*)VC1(void*, obj, 0xb8, u32, 0xe9cb8ba);
    bool alive;
    void* body;
    if (building != 0) {
        if (VC1(void*, building, 0xc, u32, 0x1a55e4d) == 0)
            return;
        alive = FUN_00bfc600((char*)building + 0x120);
        body = (void*)VC0(void*, building, 0x84);
    } else {
        building = (void*)VC1(void*, obj, 0xb8, u32, 0x436f315);
        if (building == 0)
            return;
        alive = FUN_00bfc600((char*)building + 0x588);
        body = FUN_00bce5c0(building);
    }

    void* span = body;
    bool ok = FUN_00bd8240(span);

    float length = 0.0f;
    int flag;
    if (alive && ok)
        flag = 1;
    else
        flag = 0;
    FUN_00c8b220(0x487eb45b, 0x5de3055, flag, &length);
    if (length == 0.0f)
        return;

    float dir[3];
    FUN_00bd9480(span, dir);

    float inv = 1.0f / sqrtf(dir[0] * dir[0] + (dir[1] * dir[1] + dir[2] * dir[2]) + kTiny);
    dir[0] = dir[0] * inv * kForty + dir[0];
    dir[1] = dir[1] * inv * kForty + dir[1];
    dir[2] = dir[2] * inv * kForty + dir[2];

    float* ext = (float*)VC0(void*, obj, 0x6c);
    float centre[3];
    centre[0] = (ext[3] + ext[0]) * kHalf;
    centre[1] = (ext[1] + ext[4]) * kHalf;
    centre[2] = (ext[2] + ext[5]) * kHalf;

    Vec3 pts[10];
    float stepX = (centre[0] - dir[0]) * kTenth;
    float stepY = (centre[1] - dir[1]) * kTenth;
    float stepZ = (centre[2] - dir[2]) * kTenth;
    for (int i = 0; i < 10; i++) {
        pts[i].x = dir[0] + stepX * (float)i;
        pts[i].y = dir[1] + stepY * (float)i;
        pts[i].z = dir[2] + stepZ * (float)i;
    }
    VC3(void, obj, 0x44, int, 0xd, float*, (float*)pts, int, 0x1e);
}

// @ 0x00e87b70
cBuildingView::cBuildingView()
{
    mpEffect_34 = 0;
    float one = kOne;
    mScale_3c = one;
    mScale_40 = one;
    mState_38 = 0;
    mScale_44 = kOneAndAHalf;
    mbFlag_58 = 0;
    mTimer.Construct();
    mXformIndices[0] = mXformIndices[1] = mXformIndices[2] = mXformIndices[3] = -1;
    mpEffect_80 = 0;
    mpEffect_84 = 0;
}

// @ 0x00e87be0
cBuildingView::~cBuildingView()
{
    if (mpEffect_34 != 0) {
        if (mpObject == 0 || VC1(void*, mpObject, 0xb8, u32, 0x70704db) != 0)
            VC1(void, mpEffect_34, 0xc, int, 0);
        if (mpEffect_34 != 0) {
            mpEffect_34 = 0;
            VC0(void, mpEffect_34, 4);
        }
    }

    if (mpEffect_80 != 0) {
        VC1(void, mpEffect_80, 0xc, int, 1);
        if (mpEffect_80 != 0) {
            mpEffect_80 = 0;
            VC0(void, mpEffect_80, 4);
        }
        MinimapHost* host = (MinimapHost*)FUN_010666a0();
        ((cMinimapWin*)host->GetPanel())->RemoveIcon(this, 1, 0);
    }

    if (mpEffect_84 != 0) {
        VC1(void, mpEffect_84, 0xc, int, 0);
        if (mpEffect_84 != 0) {
            mpEffect_84 = 0;
            VC0(void, mpEffect_84, 4);
        }
    }

    cSpatialObjectView_DestroyAllEffects(mpObject, 1);
    if (mpEffect_84 != 0)
        VC0(void, mpEffect_84, 4);
    if (mpEffect_80 != 0)
        VC0(void, mpEffect_80, 4);
    mTimer.Destruct();
    if (mpEffect_34 != 0)
        VC0(void, mpEffect_34, 4);
}

