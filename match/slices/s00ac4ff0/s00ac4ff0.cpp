// Slice s00ac4ff0: 0x00AC5590, path relaxation on a planet. Takes an array of 0x3c-byte path points
// (position in the first three floats), copies the positions into three fixed vectors (current,
// next and original), then runs gNumPasses relaxation passes: each interior point is pulled toward
// the closest point on the segment between its neighbours (blend factor gBlend), kept within gMaxMove
// of its original position, and accepted unless the caller's validity callback (cb->fn, keyed by a
// packed cube-face direction code of the new offset) returns the "reject" sentinel. Finally every
// point is projected back onto the planet surface (cPlanetModel method 0x00b81630).
// Names are Claude-coined from usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>
#include <new>

extern void __cdecl operator_delete__(void* p);     // 0x00f47380

typedef unsigned int uint;

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vec3Plain { float x, y, z; };

// inline-storage vector (eastl::fixed_vector); the 0xc00-byte pool follows the six bookkeeping
// words.
template <typename T, int N>
struct fixed_vector {
    T* mpBegin;                         // +0x00
    T* mpEnd;                           // +0x04
    T* mpCapacity;                      // +0x08
    void* mAllocatorPad0;               // +0x0c
    T* mpPoolBegin;                     // +0x10
    void* mAllocatorPad1;               // +0x14
    T mBuffer[N];                       // +0x18

    fixed_vector() {
        mpPoolBegin = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + N;
    }
    ~fixed_vector() {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete__(mpBegin);
    }
    void DoInsertValue(T* position, const T& value);        // 0x00ac4720 (thiscall, ret 8)
    void assign(const T* pFirst, const T* pLast, void* pAllocator);     // 0x00ac4e10 (thiscall, ret 0xc)
    void assign(const T* pFirst, const T* pLast) { assign(pFirst, pLast, mpPoolBegin); }
    T* erase(T* pFirst, T* pLast);                                      // 0x009e0480 (thiscall, ret 8)
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T& operator[](int i) { return mpBegin[i]; }
};
typedef fixed_vector<Vector3, 256> PointVec;
extern void __cdecl SwapPointVecs(PointVec* a, PointVec* b);        // 0x00ac54d0

struct PathPoint {                 // 0x3c bytes
    Vec3Plain pos;
    float rest[12];
};
struct PathPoints {                // eastl::vector<PathPoint>
    PathPoint* mpBegin;
    PathPoint* mpEnd;
};

struct Callbacks {
    uint pad[3];
    float (__cdecl *fn)(Vector3* origPos, uint dirCode);          // +0x0c
};

struct cPlanetModel {
    Vec3Plain* Project(Vec3Plain* out, const Vector3* in);        // 0x00b81630 (thiscall, ret 8)
};
cPlanetModel* PlanetModel();                                      // 0x00b3d350

extern void __cdecl ClosestPointOnSegment(Vector3* out, const Vector3* p, const Vector3* a, const Vector3* b);   // 0x00698e00

extern int   gNumPasses;           // 0x01565bf4
extern float gBlend;               // 0x01565bf0
extern float gMaxMove;             // 0x01565bec
extern float gRejectValue;         // 0x01565ba4
extern const float kOne;           // 0x01485720
extern const float kZero;          // 0x01485378
extern const float kScale64;       // 0x0140f334

// truncating float -> int: the module's asm helper (cvttss2si from the argument's stack slot)
static __forceinline int TruncToInt(float f)
{
    __asm { cvttss2si eax, f }
}
static inline float Quant(float num, float den) { return (num / den + kOne) * kScale64; }

// @ 0x00ac5590
void __cdecl RelaxPath(PathPoints* pts, Callbacks* cb)
{
    uint n = (uint)(pts->mpEnd - pts->mpBegin);
    if (n < 3)
        return;

    PointVec orig;
    PointVec next;
    PointVec cur;

    for (int i = 0; i < (int)n; i++) {
        PathPoint* pp = pts->mpBegin + i;
        Vector3 v(pp->pos.x, pp->pos.y, pp->pos.z);
        cur.push_back(v);
        next.push_back(v);
        orig.push_back(v);
    }

    uint key = n;
    for (int pass = 0; pass < gNumPasses; pass++) {
        for (int i = 1; i < (int)n - 1; i++) {
            Vector3 p = cur[i];
            Vector3 q;
            ClosestPointOnSegment(&q, &p, &cur[i - 1], &cur[i + 1]);
            Vector3 nw((q.x - p.x) * gBlend + p.x,
                       (q.y - p.y) * gBlend + p.y,
                       (q.z - p.z) * gBlend + p.z);
            const Vector3* res = &nw;
            if (!(p.x == nw.x && p.y == nw.y && p.z == nw.z)) {
                Vector3 o = orig[i];
                float dx = nw.x - o.x;
                float dy = nw.y - o.y;
                float dz = nw.z - o.z;
                float len = sqrtf(dx * dx + (dy * dy + dz * dz));
                if (len > gMaxMove) {
                    float s = gMaxMove / len;
                    nw.y = dy * s + o.y;
                    nw.x = dx * s + o.x;
                    nw.z = dz * s + o.z;
                }
                float ax = fabsf(nw.x);
                float ay = fabsf(nw.y);
                float az = fabsf(nw.z);
                int u, v, face;
                if (az < ax || az < ay) {
                    if (ay < ax) {
                        u = TruncToInt(Quant(nw.y, nw.x));
                        v = TruncToInt(Quant(nw.z, ax));
                        face = (nw.x < kZero) ? 3 : 2;
                    } else {
                        u = TruncToInt(Quant(nw.z, nw.y));
                        v = TruncToInt(Quant(nw.x, ay));
                        face = (nw.y < kZero) ? 5 : 4;
                    }
                } else {
                    u = TruncToInt(Quant(nw.x, nw.z));
                    v = TruncToInt(Quant(nw.y, az));
                    face = (nw.z < kZero) ? 1 : 0;
                }
                if (u == 0x80) u = 0x7f;
                if (v == 0x80) v = 0x7f;
                key = (key & 0x10000) | (((v & 0xff) | (face << 9)) << 8) | (u & 0xff);
                if (cb->fn(&o, key) == gRejectValue)
                    res = &p;
            }
            next[i] = *res;
        }
        SwapPointVecs(&cur, &next);
    }

    cPlanetModel* pm = PlanetModel();
    for (int i = 0; i < (int)n; i++) {
        Vec3Plain tmp;
        Vec3Plain* r = pm->Project(&tmp, &cur[i]);
        pts->mpBegin[i].pos = *r;
    }
}

// ---------------------------------------------------------------------------------------------
// A* path finding over the planet's cell graph (0x00ac4ff0 .. 0x00ac54d0).
// A cell key packs the cube-face direction code the relaxation pass above produces: bit 16 marks a
// cell as visited/closed and the remaining bits address one cell of the open list's node array.
// Names are Claude-coined from usage.
// ---------------------------------------------------------------------------------------------

extern uint    gNodeVisits;             // 0x0167a224  number of expand steps performed so far
extern uint    gMaxQueueSize;           // 0x0167a228  high-water mark of the open list
extern uint8_t gAbortSearch;            // 0x01565b14  set by the caller to abandon the search

static inline float BitsToFloat(uint bits) { float f; *(uint*)&f = bits; return f; }
static inline uint  FloatToBits(float f) { return *(uint*)&f; }

// 0x016c8b44: allocation tracker that hands block-sized buffers back to the shared pool.
struct cLocalLightInfo {
    void Release(int pBlock);           // 0x009276c0 (thiscall, pops 4)
};
extern cLocalLightInfo* gBlockPool;     // 0x016c8b44

struct IntrusiveList {                  // eastl::intrusive_list_base (as embedded at +0x40)
    void* mpHead;                       // +0x00
    void* mp04;                         // +0x04
    void* mp08;                         // +0x08
    void Destroy();                     // 0x00620230 (thiscall) -- the list's destructor
};

struct PenaltyCounter {                 // hashed visit counts per cell (see 0x00ac3ef0)
    void* mp00;                         // +0x00
    void* mpNodes;                      // +0x04
    uint  mnBucketCount;                // +0x08
    uint  mnSize;                       // +0x0c
    int  Count(const float* pKey);      // 0x00ac3ef0 (thiscall, pops 4)
    void DoFreeNodes(void* pNodes, uint nBuckets);     // 0x006b6570 (thiscall, pops 8)
    void FreeAll() {                    // the counter's destructor: drop the buckets and the nodes
        DoFreeNodes(mpNodes, mnBucketCount);
        mnSize = 0;
        if (mnBucketCount > 1)
            operator_delete__(mpNodes);
    }
};

struct cGonzagoSubsystemBase {          // SP::cGonzagoSubsystem (0x1c bytes, two vptrs)
    void** mpVtbl;                      // +0x00
    void** mpVtbl04;                    // +0x04
    uint8_t mPad08[0x14];               // +0x08
    void Destroy();                     // 0x00b5b9a0 (thiscall) -- the subsystem's destructor
};

struct QueueEntry {                     // one open-list entry: {estimated cost, cell key}
    float mCost;                        // +0x00
    uint  mKey;                         // +0x04
};
struct QueueVec {                       // eastl::vector<QueueEntry, sp_vector_allocator>
    QueueEntry* mpBegin;                // +0x00
    QueueEntry* mpEnd;                  // +0x04
    QueueEntry* mpCapacity;             // +0x08
    int size() const { return (int)(mpEnd - mpBegin); }
    void DoInsertValue(QueueEntry* pPosition, const QueueEntry& value);   // 0x00b534c0 (thiscall, ret 8)
    void insert(QueueEntry* pPosition, int nCount, const QueueEntry& value);    // 0x00ac4a60 (thiscall, ret 0xc)
    QueueEntry* erase(QueueEntry* pFirst, QueueEntry* pLast);                  // 0x00d018d0 (thiscall, ret 8)
    void push_back(const QueueEntry& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) QueueEntry(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void FreeStorage() {                // the vector's destructor: return a heap block
        if (mpBegin != 0 && ((uint*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
// Binary heap helpers over the open list; the entry being sifted is passed by value and the trailing
// flag is an int word (the callers hand over a bool, so its upper bytes stay as they were).
extern void __cdecl HeapFixDown(QueueEntry* pBase, int nChild, int nLast, int nUnused,
                                float cost, uint key, uint nUnused2);     // 0x00ac2060
extern void __cdecl HeapFixUp(QueueEntry* pBase, int nChild, int nLast,
                              float cost, uint key, uint nUnused2);       // 0x006e6d40

struct CellNode {                       // one cell of the search grid
    uint mKey;                          // +0x00  bit 16 = visited, otherwise the parent's key
};
static const uint kVisitedBit      = 0x10000;
static const uint kNoNeighbourKey  = 0x000e0000;
static inline int CellIndex(uint key)
{
    return (int)((((key >> 8) & 0xff) + (key >> 17) * 0x80) * 0x80 + (key & 0xff));
}
extern void __cdecl GetCellNeighbours(uint cellKey, float out[8]);              // 0x00ac12f0

struct Float2 {
    float x, y;
    Float2(float ax, float ay) : x(ax), y(ay) {}
};

struct PathFinderCallbacks {            // the current search request (head of cPathFinder::mRequests)
    uint8_t m00[0x1c];                  // +0x00
    uint8_t mParams[0x0c];              // +0x1c  per-request parameters, opaque to the finder
    float mBias;                        // +0x28
    float mScale;                       // +0x2c
    uint8_t m30[0x0c];                  // +0x30
    float (__cdecl *mpfnStepCost)(uint fromKey, uint toKey);                        // +0x3c
    uint8_t m40[0x04];                  // +0x40
    float (__cdecl *mpfnHeuristic)(uint cellKey, void* pParams, Float2 bias);       // +0x44
};

struct cSearchVisitor {                 // +0x3c: per-search visitor, freed through 0x00926640
    void Destroy();                     // 0x00926640 (thiscall)
};

struct cPathFinder {
    void** mpVtbl0;                     // +0x00
    cGonzagoSubsystemBase mSubsystem;   // +0x04
    CellNode* mpNodes;                  // +0x20  per-cell keys (bit 16 clear = still open)
    uint* mpCostBits;                   // +0x24  per-cell best cost, as raw float bit patterns
    QueueVec mOpen;                     // +0x28
    uint8_t mPad34[0x08];               // +0x34
    cSearchVisitor* mpVisitor;          // +0x3c
    IntrusiveList mRequests;            // +0x40  pending requests, the first node is the active one
    uint mUsePenalty;                   // +0x4c  non-zero: re-visits of a cell cost four times more
    PenaltyCounter mPenalty;            // +0x50

    void Drain();                       // 0x00ac4f50 (thiscall)
    ~cPathFinder();                     // 0x00ac5350
};
struct cPathManager {                   // pool that owns finder handles (0x00b3d290)
    void Release(void* pHandle);        // 0x00ac4ef0 (thiscall, pops 4)
};
cPathManager* GetPathManager();         // 0x00b3d290 (cdecl)

struct cPathFinderHandle {              // 8-byte handle held by whoever asked for a path
    void** mpVtbl;                      // +0x00
    void*  mpFinder;                    // +0x04
    void Release();                     // 0x00ac5330
    ~cPathFinderHandle();               // 0x00ac5430
    void* DestroyAndFree(uint flags);   // 0x00ac5490 (scalar deleting destructor, ret 4)
};

struct cMessageServer {                 // the global message dispatcher (0x0067dcc0)
    void** mpVtbl;                      // +0x00
    void Post(void* pSender, uint msgID, int param) {       // virtual slot +0x2c
        typedef void (__thiscall *PostFn)(cMessageServer*, void*, uint, int);
        ((PostFn)mpVtbl[0x2c / 4])(this, pSender, msgID, param);
    }
};
cMessageServer* MessageServer();        // 0x0067dcc0 (cdecl)

// @ 0x00ac4ff0
// One A* step: closes the cheapest open cell, relaxes the cost of its neighbours and re-parents
// them. Returns as soon as the open list is exhausted.
void __fastcall FUN_00ac4ff0(cPathFinder* pFinder)
{
    ++gNodeVisits;
    if (gAbortSearch != 0)
        gAbortSearch = 0;

    PathFinderCallbacks* pCallbacks = (PathFinderCallbacks*)pFinder->mRequests.mpHead;
    QueueVec* pOpen = &pFinder->mOpen;
    uint key;
    int cell;
    for (;;) {
        QueueEntry* pRoot = pOpen->mpBegin;
        if (pRoot == pOpen->mpEnd)
            return;
        key = pRoot->mKey;
        cell = CellIndex(key);

        // pop the cheapest entry: move the last one to the root and sift the heap down
        QueueEntry* pOldEnd = pOpen->mpEnd;
        float lastCost = pOldEnd[-1].mCost;
        uint lastKey = pOldEnd[-1].mKey;
        pOldEnd[-1] = *pRoot;
        bool bUnused = false;
        HeapFixDown(pRoot, 0, (int)(pOldEnd - pRoot) - 1, 0, lastCost, lastKey, bUnused);
        pOpen->mpEnd = pOldEnd - 1;
        if ((pFinder->mpNodes[cell].mKey & kVisitedBit) == 0)
            break;
    }

    // close the cell and relax the cost of its neighbours
    pFinder->mpNodes[cell].mKey |= kVisitedBit;
    uint gBits = pFinder->mpCostBits[cell];
    uint neighbours[8];
    GetCellNeighbours(key, (float*)neighbours);
    int cells[8];
    for (int i = 0; i < 8; i++) {
        uint nkey = neighbours[i];
        if (nkey == kNoNeighbourKey)
            continue;
        int ncell = CellIndex(nkey);
        cells[i] = ncell;
        if ((pFinder->mpNodes[ncell].mKey & kVisitedBit) != 0)
            continue;
        if (pFinder->mpCostBits[ncell] <= gBits)
            continue;

        float stepCost = pCallbacks->mpfnStepCost(key, nkey);
        if (pFinder->mUsePenalty != 0 && stepCost != gRejectValue
            && pFinder->mPenalty.Count((const float*)&neighbours[i]) != 0)
            stepCost *= 4.0f;
        float newCost = BitsToFloat(gBits) + stepCost;
        if (i > 3) {
            // the first four neighbours are in the cell's own row: keep the cost at least as high
            // as the cheaper of its two already-relaxed predecessors
            float a = BitsToFloat(pFinder->mpCostBits[cells[(i + 1) & 3]]);
            float b = BitsToFloat(pFinder->mpCostBits[cells[i & 3]]);
            float minCost = (FloatToBits(a) < FloatToBits(b)) ? a : b;
            if (newCost < minCost)
                newCost = minCost;
        }
        if (pFinder->mpCostBits[ncell] <= FloatToBits(newCost)) {
            pFinder->mpCostBits[ncell] = FloatToBits(newCost);
            pFinder->mpNodes[ncell].mKey = key;
            float total = pCallbacks->mpfnHeuristic(
                    nkey, pCallbacks->mParams, Float2(pCallbacks->mBias, pCallbacks->mScale))
                + newCost;
            QueueEntry entry;
            entry.mCost = total;
            entry.mKey = nkey;
            pFinder->mOpen.push_back(entry);
            QueueEntry* pEnd = pFinder->mOpen.mpEnd;
            bool bUnused2 = false;
            HeapFixUp(pFinder->mOpen.mpBegin, 0, (int)(pEnd - pFinder->mOpen.mpBegin) - 1,
                      pEnd[-1].mCost, pEnd[-1].mKey, bUnused2);
        }
    }
    if (gMaxQueueSize < (uint)pFinder->mOpen.size())
        gMaxQueueSize = pFinder->mOpen.size();
}

// Eastl vector element used by the resize() instantiation at 0x00ac52d0.
struct GlyphInfo {
    int mnGlyph;                        // +0x00
    int mnFlags;                        // +0x04
};
struct GlyphVec {                       // eastl::vector<Text::GlyphInfo>
    GlyphInfo* mpBegin;                 // +0x00
    GlyphInfo* mpEnd;                   // +0x04
    GlyphInfo* mpCapacity;              // +0x08
    int size() const { return (int)(mpEnd - mpBegin); }
    void insert(GlyphInfo* pPosition, int nCount, const GlyphInfo& value);     // 0x00ac4a60 (thiscall, ret 0xc)
    GlyphInfo* erase(GlyphInfo* pFirst, GlyphInfo* pLast);                     // 0x00d018d0 (thiscall, ret 8)
    void resize(uint n);                                                       // 0x00ac52d0 (thiscall, ret 4)
};

// @ 0x00ac52d0
void GlyphVec::resize(uint n)
{
    if (n > (uint)size()) {
        GlyphInfo value = {0, 0};
        insert(mpEnd, (int)(n - (uint)size()), value);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00ac5330
// Hands the finder back to the pool when the handle still owns one.
void __fastcall FUN_00ac5330(cPathFinderHandle* pHandle)
{
    cPathManager* pManager = GetPathManager();
    if (pHandle->mpFinder != 0 && pManager != 0)
        pManager->Release(pHandle);
}

// @ 0x00ac5350
cPathFinder::~cPathFinder()
{
    mpVtbl0 = (void**)0x01459e60;
    mSubsystem.mpVtbl = (void**)0x01459e70;
    mSubsystem.mpVtbl04 = (void**)0x01459e5c;
    Drain();
    cSearchVisitor* pVisitor = mpVisitor;
    if (pVisitor != 0) {
        pVisitor->Destroy();
        operator_delete__(pVisitor);
    }
    gBlockPool->Release((int)mpCostBits);
    gBlockPool->Release((int)mpNodes);
    mPenalty.FreeAll();
    mRequests.Destroy();
    mOpen.FreeStorage();
    mSubsystem.Destroy();
    mpVtbl0 = (void**)0x013eb394;       // PaintSystem vtable
}

// @ 0x00ac5400
// Request teardown (this is the cPathFinder's second base): drop the open list and tell the message
// server that the search is over (0x1a0219e, 0xffffd8f1 = "path finding aborted").
void __fastcall FUN_00ac5400(uint8_t* pRequestBase)
{
    cPathFinder* pFinder = (cPathFinder*)(pRequestBase - 4);
    pFinder->Drain();
    MessageServer()->Post(pFinder, 0x01a0219e, 0xffffd8f1);
}

// @ 0x00ac5430
cPathFinderHandle::~cPathFinderHandle()
{
    mpVtbl = (void**)0x01459e50;
    if (mpFinder != 0) {
        cPathManager* pManager = GetPathManager();
        if (mpFinder != 0 && pManager != 0)
            pManager->Release(this);
    }
}

// @ 0x00ac5490
void* cPathFinderHandle::DestroyAndFree(uint flags)
{
    mpVtbl = (void**)0x01459e50;
    if (mpFinder != 0) {
        cPathManager* pManager = GetPathManager();
        if (mpFinder != 0 && pManager != 0)
            pManager->Release(this);
    }
    if ((flags & 1) != 0)
        operator_delete__(this);
    return this;
}

// The scratch vector keeps a leading allocator handle in the retail layout; the inlined
// constructor only writes the vector's own words and every assign() call forwards the handle.
struct PointVecScratch {
    void* mpAllocator;                  // +0x00
    PointVec mVector;                   // +0x04
};

// @ 0x00ac54d0
// Swaps the contents of two point vectors through an inline-storage scratch vector.
void __cdecl SwapPointVecs(PointVec* a, PointVec* b)
{
    PointVecScratch scratch;
    PointVec& tmp = scratch.mVector;
    tmp.assign(a->mpBegin, a->mpEnd, scratch.mpAllocator);
    if (a != b) {
        a->erase(a->mpBegin, a->mpEnd);
        a->assign(b->mpBegin, b->mpEnd, scratch.mpAllocator);
    }
    if (b != &tmp) {
        b->erase(b->mpBegin, b->mpEnd);
        b->assign(tmp.mpBegin, tmp.mpEnd, scratch.mpAllocator);
    }
}
