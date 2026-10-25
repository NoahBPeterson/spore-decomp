// Slice s00ac5c00: the cAStar request queue. Contains the byte-exact thin entry points
// (run/findPath/findPathFast), the shadow-manager property helpers and the request queueing /
// one-step search driver (addRequest, step).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Shared declarations for the cAStar request helpers.
// ---------------------------------------------------------------------------

typedef unsigned char u8;
typedef unsigned int  u32;

struct Vec3 { float x, y, z; };
static inline u32 FloatToBits(float f) { return *(u32*)&f; }
static inline float BitsToFloat(u32 b) { float f; *(u32*)&f = b; return f; }

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct LargeInteger { int low; int high; };

struct VTable { void* slots[0x50 / 4]; };
struct Obj    { VTable* vt; };

struct QueueEntry {                 // one open-list entry: {estimated cost, cell key}
    float cost;                     // +0x00
    u32   key;                      // +0x04
};

struct AStarOpenList {                       // eastl::vector<QueueEntry, sp_vector_allocator>
    QueueEntry* begin;              // +0x00
    QueueEntry* end;                // +0x04
    QueueEntry* cap;                // +0x08
    void reserve(u32 n);            // 0xac4280
    void swap(AStarOpenList* other);        // 0xac4d50
    QueueEntry* erase(QueueEntry* first, QueueEntry* last);   // 0xd018d0 (ret 8)
    void resize(u32 n);                                       // 0xac52d0 (ret 4)
    int size() const { return (int)(end - begin); }
    QueueEntry& operator[](int i) { return begin[i]; }
};
struct ListNode { ListNode* next; ListNode* prev; };

struct FixedAllocatorBase {
    char  pad[0x10];
    void* freeList;                 // +0x10
    bool AddCore(void* block, u32 size); // 0x926650
};

struct Request7;

struct PenaltyCounter {             // eastl hashtable of per-cell visit counts
    void* mp00;                     // +0x00
    void* mpNodes;                  // +0x04
    u32   bucketCount;              // +0x08
    u32   size;                     // +0x0c
    void DoFreeNodes(void* nodes, u32 buckets);                  // 0x6b6570 (ret 8)
    int  DoInsertValue(void* scratch, const u32* key, int value); // 0x6758a0 (ret 0xc)
};

struct CAStar {
    char  pad[0x1c];
    void* field1c;                  // +0x1c
    u32*  mpNodes;                  // +0x20  per-cell parent keys
    u32*  mpCostBits;               // +0x24  per-cell best cost, raw float bits
    AStarOpenList  pathVec;                  // +0x28  open list / current path
    char  pad2[0x3c - 0x34];
    FixedAllocatorBase* alloc;      // +0x3c
    ListNode sentinel;              // +0x40  request list
    void* pad48;                    // +0x48
    u32   mUsePenalty;              // +0x4c  non-zero: penalise re-visited cells
    PenaltyCounter penalty;         // +0x50
    void release(void* handle);     // 0xac4ef0
    __declspec(noinline) int step(); // 0xac5c00
    int run(u32 limit);             // 0xac68e0
    u8 findPath(void* a1, void* a2, void* a3, void* a4, float f5, float f6); // 0xac6960
    void findPathFast(void* a1, void* a2, void* a3, void* a4, void* a5,
                      int a6, void* a7); // 0xac6a10
    void addRequest(void* a1, void* a2, void* a3, float f1, float f2,
                    void* a6, Request7* a7, int flag, void* a9); // 0xac65d0
};

struct ShadowMgr {
    char  pad[0x1c];
    void* field1c;                  // +0x1c
    u8    flag;                     // +0x20
    char  pad20[3];
    void* material;                 // +0x24
    float f28;                      // +0x28
    float f2c;                      // +0x2c
    float f30;                      // +0x30
    float f34;                      // +0x34
    void setMaterial();             // 0xac6a50
    void readProperties(int, int);  // 0xac6aa0
};

struct Chunk {
    Chunk* next;                    // +0x00
    Chunk* prev;                    // +0x04
    void*  owner;                   // +0x08
    void*  param6;                  // +0x0c
    u32    a2[3];                   // +0x10
    u32    a3[3];                   // +0x1c
    float  lo;                      // +0x28
    float  hi;                      // +0x2c
    u8     flag;                    // +0x30
    u8     pad[3];
    u32    a1[5];                   // +0x34
    void*  a9;                      // +0x48
};

struct Request7 {
    char   pad[4];
    Chunk* chunk;                   // +0x04
};

struct PathResult {
    void* vt;                       // +0x00
    void* field4;                   // +0x04
    u8    field8;                   // +0x08
};

struct LimitStopwatch {
    char pad[0x18];
    int  endLow;                    // +0x18
    int  endHigh;                   // +0x1c
    void ctor(int type, int start);            // 0x93a560
    void SetTimeLimit(u32 limit, int start);   // 0x93a480
};

struct MemPool {
    void* LockedAligned(u32 a, u32 b, int c, int d, int e, int f, int g, int h); // 0x928a30
    void releaseLight(void* light);                                             // 0x9276c0
};

struct PlanetModelOps {
    int update();                                       // 0xb88420
    Vec3* GetPoint(Vec3* out, const Vec3* dir);         // 0xb81630 (ret 8)
};
struct TerrainOps     { void* getList(); };// 0xb1de80

extern "C" void* __cdecl SP_MaterialManager();                    // 0x67dd70
extern "C" void* __cdecl FUN_0067dd50();                          // 0x67dd50
extern "C" void* __cdecl PlanetModel_0b3d350();                   // 0xb3d350
extern "C" void* __cdecl FUN_00b3d290();                          // 0xb3d290
extern "C" __declspec(dllimport) int __stdcall
QueryPerformanceCounter(LargeInteger*);                           // IAT 0x13cc2b8

void __cdecl Free_47380(void* p);                                 // 0xf47380
void* __cdecl FUN_00b3d320();                                     // 0xb3d320
bool __cdecl GetPropertyAsVector2(void* list, u32 key, float* out); // 0x6a10c0

struct cProperty {
    char  pad[0x12];
    short kind;                     // +0x12
    bool* __thiscall GetBool();     // 0x41e920
};

extern Obj*     g_appProperties_15fd918;   // 0x15fd918
extern MemPool* g_16c8b44;                 // 0x16c8b44

extern u32 g_167a220;                      // 0x167a220
extern u32 g_167a224;                      // 0x167a224
extern u32 g_167a228;                      // 0x167a228
extern u32 g_167a22c;                      // 0x167a22c
extern u32 g_167a230;                      // 0x167a230
extern u32* g_167a298;                     // 0x167a298
extern u32* g_167a2a0;                     // 0x167a2a0
extern u8  g_1565b14;                      // 0x1565b14
extern u8  g_1565bf8;                      // 0x1565bf8

struct SnapshotList {
    int push_back(void* value);            // 0xac4390 (ret 4)
};
extern SnapshotList g_167a280;             // 0x167a280

extern float kf_1471064;                   // 0x1471064 = 0.5f
extern float kf_1459e18;                   // 0x1459e18 = 7.04f
extern float kf_1485378;                   // 0x1485378 = 0.0f
extern float kf_1485720;                   // 0x1485720 = 1.0f
extern float kf_140f334;                   // 0x140f334 = 64.0f

// ---------------------------------------------------------------------------
// Search/path helpers used by step().
// ---------------------------------------------------------------------------

static const u32 kVisitedBit     = 0x10000;
static const u32 kRootParentKey  = 0x000c0000;
static const u32 kNoNeighbourKey = 0x000e0000;

static inline int CellIndex(u32 key)
{
    return (int)((((key >> 8) & 0xff) + (key >> 17) * 0x80) * 0x80 + (key & 0xff));
}

struct CurvePoint {                 // eastl vector element, 0x3c bytes
    float x, y, z, w;               // +0x00..+0x0c
    u32   field10;                  // +0x10
    u32   pad14[9];                 // +0x14..+0x37
    u8    field38;                  // +0x38
    u8    pad39[3];
    void ctor(const Vec3* src);     // 0xac21d0 (ret 4)
};

struct CurveVec {                   // eastl::vector<cCurvePoint>
    CurvePoint* mpBegin;            // +0x00
    CurvePoint* mpEnd;              // +0x04
    CurvePoint* mpCapacity;         // +0x08
    CurvePoint* erase(CurvePoint* first, CurvePoint* last);   // 0xac4570 (ret 8)
    void push_back(const CurvePoint* value);                  // 0xac4de0 (ret 4)
};

struct FixedKeyVec {                // eastl::fixed_vector<u32, 256>
    u32* mpBegin;                   // +0x00
    u32* mpEnd;                     // +0x04
    u32* mpCapacity;                // +0x08
    void* mPad0;                    // +0x0c
    u32* mpPoolBegin;               // +0x10
    void* mPad1;                    // +0x14
    u32  mBuffer[257];              // +0x18 (256 inline slots plus the one-past slot the original reads)
    FixedKeyVec() {
        mpPoolBegin = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + 256;
    }
    void DoAssignValues(u32* position, const u32* value);     // 0xac4850 (ret 8)
};

void __cdecl FillDwords(void* dst, u32 value, u32 count);                  // 0xac1490
void __cdecl GetCellNeighbours(u32 cellKey, float out[8]);                 // 0xac12f0
void __cdecl DirToVec3(u32 face, u32 u, u32 v, Vec3* out);                 // 0xac1510
int  __cdecl Heapify(QueueEntry* begin, QueueEntry* end, u32 ctx);         // 0xac3fa0
void __cdecl ReverseCurve(CurvePoint* begin, CurvePoint* end);             // 0xac4970
void __cdecl RelaxPath(void* points, void* callbacks);                     // 0xac5590
int  __fastcall ExpandRequest(CAStar* self);                               // 0xac4ff0

extern char VT_1459ed0[];              // 0x1459ed0
extern char VT_1459e50[];              // 0x1459e50

// @ 0x00ac68e0
// Run the A* request queue until the stopwatch expires.
int CAStar::run(u32 limit)
{
    LimitStopwatch sw;
    sw.ctor(4, 0);
    sw.SetTimeLimit(limit, 1);
    void* pm = PlanetModel_0b3d350();
    int result = ((PlanetModelOps*)pm)->update();
    ListNode* sentinel = &this->sentinel;
    if (sentinel->prev == sentinel)
        return result;
    do {
        LargeInteger now;
        QueryPerformanceCounter(&now);
        long long diff = *(long long*)&sw.endLow - *(long long*)&now;
        if (diff < 0)
            return (int)diff;
        result = this->step();
    } while (sentinel->prev != sentinel);
    return result;
}

// @ 0x00ac6960
// Build one request, drain it, release the temporary path.
u8 CAStar::findPath(void* a1, void* a2, void* a3, void* a4, float f5, float f6)
{
    PathResult result;
    result.field4 = 0;
    result.vt = VT_1459ed0;
    result.field8 = 0;
    void* pm = PlanetModel_0b3d350();
    ((PlanetModelOps*)pm)->update();
    this->addRequest(a1, a2, a3, f5, f6, a4, (Request7*)&result, 1, 0);
    int count = (int)result.field4;
    if (count != 0) {
        do {
            this->step();
            count = (int)result.field4;
        } while (count != 0);
    }
    u8 ret = result.field8;
    result.vt = VT_1459e50;
    if (count != 0) {
        void* p = FUN_00b3d290();
        if (result.field4 != 0 && p != 0)
            ((CAStar*)p)->release(&result);
    }
    return ret;
}

// @ 0x00ac6a10
// Forward a request with a zero-width band.
void CAStar::findPathFast(void* a1, void* a2, void* a3, void* a4, void* a5,
                          int a6, void* a7)
{
    this->addRequest(a1, a2, a3, 0.0f, 0.0f, a4, (Request7*)a5, a6, a7);
}

// @ 0x00ac6a50
// Attach a material and register the light slot.
void ShadowMgr::setMaterial()
{
    ShadowMgr* self = this;
    int* piVar1 = (int*)SP_MaterialManager();
    typedef u32 (__thiscall* Fn1)(int*, u32);
    u32 uVar2 = (*(Fn1*)(*piVar1 + 0x28))(piVar1, 0x605e24f5u);
    *(u32*)((char*)self + 0x24) = uVar2;
    self = (ShadowMgr*)((char*)self + 0x1c);
    _ReadWriteBarrier();
    piVar1 = (int*)FUN_0067dd50();
    typedef void (__thiscall* Fn2)(int*, void*, int, int);
    (*(Fn2*)(*piVar1 + 0x4c))(piVar1, self, 0xb, 0);
}

// @ 0x00ac6aa0
// Read the shadow/light properties.
void ShadowMgr::readProperties(int, int)
{
    this->flag = 1;
    if (g_appProperties_15fd918 != 0) {
        cProperty* prop;
        typedef bool (__thiscall* Fn)(void*, u32, cProperty**);
        Fn fn = *(Fn*)((char*)g_appProperties_15fd918->vt + 0x24);
        if (fn(g_appProperties_15fd918, 0x539d9e5u, &prop) && prop->kind == 1) {
            u8 v = *(u8*)prop->GetBool();
            this->flag = v;
        }
    }
    if (this->flag != 0) {
        void* x = FUN_00b3d320();
        void* list = ((TerrainOps*)x)->getList();
        struct Vector2 { float x; float y; };
        Vector2 v;
        float y;
        if (GetPropertyAsVector2(list, 0x539d9e6u, &v.x)) {
            this->f30 = v.x;
            y = v.y;
        } else {
            this->f30 = 0.0f;
            y = 0.0f;
        }
        this->f34 = y;
        if (GetPropertyAsVector2(list, 0x539d9e7u, &v.x)) {
            this->f2c = v.x;
            this->f28 = v.y;
        } else {
            extern float kf_13ec4d0;    // 0x13ec4d0 = 100.0f
            extern float kf_14763b8;    // 0x14763b8 = 150.0f
            this->f2c = kf_13ec4d0;
            this->f28 = kf_14763b8;
        }
    }
}

// @ 0x00ac65d0
// Queue (or immediately execute) one A* request.
void CAStar::addRequest(void* a1, void* a2, void* a3, float f1, float f2,
                        void* a6, Request7* a7, int flag, void* a9)
{
    if (a7->chunk != 0)
        this->release(a7);

    float center = (f1 + f2) * kf_1471064;
    float half = (float)fabs(f2 - f1) * kf_1471064;
    if (half < kf_1459e18)
        half = kf_1459e18;

    FixedAllocatorBase* alloc = this->alloc;
    Chunk* chunk;
    for (;;) {
        if (alloc->freeList != 0) {
            chunk = (Chunk*)alloc->freeList;
            alloc->freeList = chunk->next;
            chunk->prev = 0;
            chunk->next = 0;
            break;
        }
        if (!alloc->AddCore(0, 0)) {
            chunk = 0;
            break;
        }
    }

    a7->chunk = chunk;
    chunk->owner = a7;
    chunk->param6 = a6;
    u32* s2 = (u32*)a2;
    chunk->a2[0] = s2[0];
    chunk->a2[1] = s2[1];
    chunk->a2[2] = s2[2];
    u32* s3 = (u32*)a3;
    chunk->a3[0] = s3[0];
    chunk->a3[1] = s3[1];
    chunk->a3[2] = s3[2];
    chunk->lo = center - half;
    chunk->hi = half + center;
    u32* s1 = (u32*)a1;
    chunk->a1[0] = s1[0];
    chunk->a1[1] = s1[1];
    chunk->a1[2] = s1[2];
    chunk->a1[3] = s1[3];
    chunk->a1[4] = s1[4];
    chunk->flag = (f1 == kf_1485378);
    chunk->a9 = a9;

    if ((char)flag != 0) {
        void* old1 = this->mpNodes;
        void* old2 = this->mpCostBits;
        this->mpNodes = (u32*)g_16c8b44->LockedAligned(0x60000, 0x10, 0, 0, 0, 0, 0, 0);
        this->mpCostBits = (u32*)g_16c8b44->LockedAligned(0x60000, 0x10, 0, 0, 0, 0, 0, 0);
        u32 g0, g1, g2, g3, g4;
        AStarOpenList oldPath;
        oldPath.begin = 0;
        oldPath.end = 0;
        oldPath.cap = 0;
        oldPath.swap(&this->pathVec);
        this->pathVec.reserve((u32)(((char*)oldPath.end - (char*)oldPath.begin) >> 3));
        g0 = g_167a220;
        g1 = g_167a224;
        g2 = g_167a228;
        g3 = g_167a22c;
        g4 = g_167a230;
        void* pm = PlanetModel_0b3d350();
        ((PlanetModelOps*)pm)->update();
        Chunk* head2 = (Chunk*)&this->sentinel;
        chunk->next = head2->next;
        chunk->prev = head2;
        head2->next = chunk;
        chunk->next->prev = chunk;
        while (a7->chunk != 0)
            this->step();
        g_16c8b44->releaseLight(this->mpNodes);
        g_16c8b44->releaseLight(this->mpCostBits);
        this->mpNodes = (u32*)old1;
        this->mpCostBits = (u32*)old2;
        this->pathVec.swap(&oldPath);
        g_167a220 = g0;
        g_167a224 = g1;
        g_167a228 = g2;
        g_167a22c = g3;
        g_167a230 = g4;
        if (oldPath.begin != 0 && *(int*)((char*)oldPath.begin - 4) != 0)
            Free_47380(oldPath.begin);
    } else {
        Chunk* head = (Chunk*)&this->sentinel;
        if (a9 == 0) {
            chunk->prev = head->prev;
            chunk->next = head;
            head->prev = chunk;
            chunk->prev->next = chunk;
            return;
        }
        Chunk* node = head->next;
        while (node != head) {
            if (node->a9 == a9) {
                Chunk* prev = node->prev;
                node->prev = chunk;
                prev->next = chunk;
                chunk->prev = prev;
                chunk->next = node;
                return;
            }
            node = node->next;
        }
        chunk->prev = head->prev;
        chunk->next = head;
        head->prev = chunk;
        chunk->prev->next = chunk;
    }
}

// Push the current search counters into the recorded-results block, growing it when full. Returns
// the value the original leaves in eax (the recorded flag, the new block end, or push_back's
// result). The block base is 0x167a280, the write cursor 0x167a298, the block end 0x167a2a0.
static __forceinline int PushSnapshot()
{
    u32* p = g_167a298;
    u32* np = p + 5;
    if (np == g_167a2a0)
        return g_167a280.push_back(&g_167a220);
    g_167a298 = np;
    if (p == 0)
        return (int)np;
    p[0] = g_167a220;
    p[1] = g_167a224;
    p[2] = g_167a228;
    p[3] = g_167a22c;
    p[4] = g_167a230;
    return (int)g_167a230;
}

// @ 0x00ac5c00
// Advance one A* request. With an empty open list this seeds the search from the request's start /
// target band; otherwise it expands the cheapest node, walks the parent chain back to the start,
// turns it into a curve of surface points and relaxes it. Finally the request is released and its
// owning handle is told whether a path was produced.
int CAStar::step()
{
    if (g_1565b14 != 0)
        g_1565b14 = 0;

    ((PlanetModelOps*)PlanetModel_0b3d350())->update();

    Chunk* chunk = (Chunk*)this->sentinel.next;

    if (this->pathVec.begin == this->pathVec.end) {
        // ---------------------------------------------------------------- seed the open list
        g_167a228 = 0;
        g_167a22c = 0;
        *(u8*)&g_167a230 = 0;
        g_167a224 = 0;

        typedef bool (__cdecl* ValidateFn)(void*, void*, float, float);
        ValidateFn validate = (ValidateFn)(void*)chunk->a1[1];
        if (!validate(chunk->a2, chunk->a3, chunk->lo, chunk->hi)) {
            *(u8*)&g_167a230 = 0;
            PushSnapshot();
            CurveVec* curve = (CurveVec*)chunk->param6;
            if (curve != 0)
                curve->erase(curve->mpBegin, curve->mpEnd);
            void* owner = chunk->owner;
            this->release(owner);
            typedef int (__thiscall* OwnerFn)(void*, int);
            OwnerFn fn = (OwnerFn)(*(void***)owner)[1];
            return fn(owner, 0);
        }

        u32 a9 = (u32)chunk->a9;
        if (a9 != this->mUsePenalty) {
            this->mUsePenalty = a9;
            this->penalty.DoFreeNodes(this->penalty.mpNodes, this->penalty.bucketCount);
            this->penalty.size = 0;
        }

        FillDwords(this->mpNodes, kNoNeighbourKey, 0x18000);
        FillDwords(this->mpCostBits, 0x7f7fffff, 0x18000);

        this->pathVec.erase(this->pathVec.begin, this->pathVec.end);
        this->pathVec.resize(9);

        // direction code for the request's start point: pick the dominant axis, quantise the other
        // two, and pack (v, face, u) with one float mantissa bit above bit 16.
        const Vec3* start = (const Vec3*)chunk->a2;
        float px = start->x, py = start->y, pz = start->z;
        float ax = fabsf(px), ay = fabsf(py), az = fabsf(pz);
        float uf, vf, auxf;
        int face;
        if (az < ax || az < ay) {
            if (ay < ax) {
                uf = (py / px + kf_1485720) * kf_140f334;
                vf = (pz / ax + kf_1485720) * kf_140f334;
                face = (px < kf_1485378) ? 3 : 2;
                auxf = vf;
            } else {
                uf = (pz / py + kf_1485720) * kf_140f334;
                vf = (px / ay + kf_1485720) * kf_140f334;
                face = (py < kf_1485378) ? 5 : 4;
                auxf = vf;
            }
        } else {
            uf = (px / pz + kf_1485720) * kf_140f334;
            vf = (py / az + kf_1485720) * kf_140f334;
            face = (pz < kf_1485378) ? 1 : 0;
            auxf = ax;
        }
        int u = (int)uf;
        int v = (int)vf;
        if (u == 0x80) u = 0x7f;
        if (v == 0x80) v = 0x7f;
        u32 auxBits = FloatToBits(auxf);
        u32 key = (((u32)(v & 0xff) | ((u32)face << 9)) << 8)
                | (auxBits & 0x10000)
                | (u32)(u & 0xff);

        u32 keys[9];
        keys[0] = key;
        GetCellNeighbours(key, (float*)&keys[1]);

        typedef float (__cdecl* StepCostFn)(void*, u32);
        typedef float (__cdecl* HeuristicFn)(u32, void*, float, float);
        StepCostFn stepCost = (StepCostFn)(void*)chunk->a1[3];
        HeuristicFn heuristic = (HeuristicFn)(void*)chunk->a1[4];

        int hole = -1;
        u32 s10 = auxBits;
        for (int i = 0; i < 9; i++) {
            u32 k = keys[i];
            if (k == kNoNeighbourKey) {
                hole = i;
                continue;
            }
            int cell = CellIndex(k);
            float g = stepCost(chunk->a2, k);
            this->mpNodes[cell] = kRootParentKey;
            this->mpCostBits[cell] = FloatToBits(g);
            float f = heuristic(k, chunk->a3, chunk->lo, chunk->hi) + g;
            if (i > 4) {
                // first four neighbours share the cell's row: keep f at least the cost of the
                // cheaper of the two already-seeded predecessors.
                u32 cb = FloatToBits(this->pathVec[(i & 3) + 1].cost);
                u32 pb = FloatToBits(this->pathVec[((i - 1) & 3) + 1].cost);
                if (cb < pb)
                    pb = cb;
                s10 = pb;
                float mn = BitsToFloat(pb);
                if (mn > f)
                    f = mn;
            }
            this->pathVec[i].cost = f;
            this->pathVec[i].key = k;
        }
        if (hole != -1) {
            QueueEntry* last = this->pathVec.end - 1;
            this->pathVec.begin[hole].cost = last->cost;
            this->pathVec.begin[hole].key = last->key;
            this->pathVec.end = last;
        }
        return Heapify(this->pathVec.begin, this->pathVec.end, s10 & 0xffffff00);
    }

    // ---------------------------------------------------------------- expand the search
    QueueEntry* root = this->pathVec.begin;
    if (FloatToBits(root->cost) > this->mpCostBits[CellIndex(root->key)]) {
        int expandResult = ExpandRequest(this);
        if (this->pathVec.begin != this->pathVec.end)
            return expandResult;
    }

    u8 nonEmpty = (this->pathVec.begin != this->pathVec.end) ? 1 : 0;

    if (nonEmpty != 0) {
        CurveVec* curve = (CurveVec*)chunk->param6;
        if (curve != 0) {
            curve->erase(curve->mpBegin, curve->mpEnd);

            FixedKeyVec path;
            u32 k = this->pathVec.begin->key & ~kVisitedBit;
            if (chunk->flag != 0) {
                CurvePoint cp;
                cp.ctor((const Vec3*)chunk->a3);
                curve->push_back(&cp);
            }
            while (k != kRootParentKey) {
                if (path.mpEnd < path.mpCapacity) {
                    *path.mpEnd++ = k;
                } else {
                    path.DoAssignValues(path.mpEnd, &k);
                }
                if (this->mUsePenalty != 0) {
                    u8 zero = 0;
                    int value;
                    *(u8*)&value = zero;
                    u8 scratch[12];
                    this->penalty.DoInsertValue(scratch, &k, value);
                }
                k = this->mpNodes[CellIndex(k)] & ~kVisitedBit;
            }

            int count = (int)(path.mpEnd - path.mpBegin);
            int prev = 0;
            if (count > 0) {
                // first stored cell
                u32 k0 = path.mpBegin[0];
                Vec3 dir;
                DirToVec3(k0 >> 17, k0 & 0xff, (k0 >> 8) & 0xff, &dir);
                Vec3 pos;
                Vec3* got = ((PlanetModelOps*)PlanetModel_0b3d350())->GetPoint(&pos, &dir);
                CurvePoint cp;
                cp.ctor(got);
                curve->push_back(&cp);

                // interior cells, dropping runs that are straight on one cube face
                int i = 2;
                if (count > 2) {
                    do {
                        u32 kprev = path.mpBegin[prev];
                        u32 kcur = path.mpBegin[i];
                        u32 knext = path.mpBegin[i + 1];
                        bool collinear;
                        if (i - prev < 5
                            && (kprev >> 17) == (kcur >> 17)
                            && (kcur >> 17) == (knext >> 17)) {
                            u32 uprev = kprev & 0xff;
                            u32 ucur = kcur & 0xff;
                            u32 unext = knext & 0xff;
                            if (uprev == ucur && ucur == unext) {
                                collinear = true;
                            } else {
                                u32 vprev = (kprev >> 8) & 0xff;
                                u32 vcur = (kcur >> 8) & 0xff;
                                u32 vnext = (knext >> 8) & 0xff;
                                if (vprev == vcur && vcur == vnext) {
                                    collinear = true;
                                } else {
                                    collinear = ((int)uprev - (int)ucur == (int)ucur - (int)unext)
                                             && ((int)vprev - (int)vcur == (int)vcur - (int)vnext);
                                }
                            }
                        } else {
                            collinear = false;
                        }
                        if (!collinear) {
                            prev = i - 1;
                            Vec3 mdir;
                            DirToVec3(kcur >> 17, kcur & 0xff, (kcur >> 8) & 0xff, &mdir);
                            Vec3 mpos;
                            Vec3* mgot = ((PlanetModelOps*)PlanetModel_0b3d350())->GetPoint(&mpos, &mdir);
                            CurvePoint mcp;
                            mcp.ctor(mgot);
                            curve->push_back(&mcp);
                        }
                        i++;
                    } while (i < count);
                }

                // last stored cell
                if (count > 1) {
                    u32 klast = path.mpBegin[count - 1];
                    Vec3 ldir;
                    DirToVec3(klast >> 17, klast & 0xff, (klast >> 8) & 0xff, &ldir);
                    Vec3 lpos;
                    Vec3* lgot = ((PlanetModelOps*)PlanetModel_0b3d350())->GetPoint(&lpos, &ldir);
                    CurvePoint lcp;
                    lcp.ctor(lgot);
                    curve->push_back(&lcp);
                }
            }

            ReverseCurve(curve->mpBegin, curve->mpEnd);
            g_167a22c = (u32)(curve->mpEnd - curve->mpBegin);
            if (g_1565bf8 != 0)
                RelaxPath(chunk->param6, chunk->a1);
            if (path.mpBegin != 0 && path.mpBegin != path.mpPoolBegin)
                Free_47380(path.mpBegin);
        }
        *(u8*)&g_167a230 = 1;
    } else {
        CurveVec* curve = (CurveVec*)chunk->param6;
        if (curve != 0)
            curve->erase(curve->mpBegin, curve->mpEnd);
        *(u8*)&g_167a230 = 0;
    }

    int nonEmptyArg;
    *(u8*)&nonEmptyArg = nonEmpty;
    void* owner = chunk->owner;
    this->release(owner);
    typedef int (__thiscall* OwnerFn)(void*, int);
    OwnerFn fn = (OwnerFn)(*(void***)owner)[1];
    fn(owner, nonEmptyArg);
    return PushSnapshot();
}
