// Slice s00d73090 -- 0x00d73350 (1638 bytes): scatter sample points over the planet-surface patch around a
// direction.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc; aligned frame, x87 sqrt, SSE arithmetic).
//
// `obj` holds a vector of 0x1c-byte cells at +0x40 (begin/end/capacity; eastl::vector with the Simulator
// allocator). The function only runs when the vector is empty. It
//   * works out which cube-map face (6 faces of a 256x256 grid) the direction `dir` hits and the grid
//     cell on that face;
//   * asks 0x00685450 for the grid rectangles (per face) that cover `radius` around that cell;
//   * for every grid cell in those rectangles builds the unit direction through the cell centre, keeps it
//     only if it lies within `radius` of `dir`, maps it to the planet surface (DirectionToSurfacePosition),
//     requires the surface point to be above the water, to be on continent `continent`, to have a valid
//     surface frame (0x00b88f60) and a ray result (0x00d72520, FLT_MAX = miss);
//   * and appends {point, ray hit} as a cell unless an existing cell is closer than `spacing` in either.
// Names are Claude-coined (the function has no PDB name).
#include "types.h"

#include <math.h>
#include <float.h>
#include <new>

struct Vector3 {
    float x, y, z;
};

// cell record of 0x1c bytes (7 dwords: flag, surface point, ray hit)
struct Cell {
    uint8_t mFlag;
    uint8_t pad1[3];
    Vector3 mPoint;
    Vector3 mHit;
    Cell() {}
    Cell(const Cell& o) : mFlag(o.mFlag), mPoint(o.mPoint), mHit(o.mHit) {}
};

// grid rectangle returned by 0x00685450: face plus [x0,x1) x [y0,y1)
struct FaceRect {
    int face;
    int x0, y0, x1, y1;
};

// eastl::vector<Cell> with the three non-inlined members at their addresses
struct CellVector {
    Cell* mpBegin;
    Cell* mpEnd;
    Cell* mpCapacity;

    Cell* erase(Cell* first, Cell* last);               // 0x00d73090 (thiscall, ret 8)
    void  reserve(unsigned n);                          // 0x00d72fd0 (thiscall, ret 4)
    void  DoInsertValue(Cell* pos, const Cell& value);  // 0x00d73100 (thiscall, ret 8)

    void clear() { erase(mpBegin, mpEnd); }
    Cell& push_back()
    {
        if (mpEnd < mpCapacity) {
            ++mpEnd;
        } else {
            Cell tmp;
            DoInsertValue(mpEnd, tmp);
        }
        return *(mpEnd - 1);
    }
};

// rounding float->int (cvtss2si)
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

__forceinline int TruncToInt(float f) { __asm cvttss2si eax, f }

extern const uint8_t kFaceAxes[3][4];                   // 0x0147bd6c

namespace SP {

class cPlanetModel { public:
    float    GetWaterHeight();                                          // 0x00b7e390
    Vector3* DirectionToSurfacePosition(Vector3* out, Vector3* dir);    // 0x00b815a0 (thiscall, ret 8)
    int      GetContinent(Vector3* pos);                                // 0x00b88590 (thiscall, ret 4)
    bool     GetSurfaceFrame(Vector3* pos, float radius, Vector3* out); // 0x00b88f60 (thiscall, ret 0xc)
    bool     RayCast(Vector3* pos, float step, Vector3* out,
                     float a, float b, float c);                        // 0x00b88770 (thiscall, ret 0x18)
};
cPlanetModel* PlanetModel();                                            // 0x00b3d350

void* HotSpotSample(uint32_t key, void* dir);                           // 0x00c94430

} // namespace SP

int GatherFaceRects(int size, const int* center, int radius, FaceRect* out);                          // 0x00685450 (cdecl)
float CastRay(const Vector3* pos, const Vector3* dir, float tolerance, float radius, Vector3* out);   // 0x00d72520 (cdecl)

struct cSurfaceSampler {
    char pad00[0x40];
    CellVector mCells;                                  // +0x40
};

// @ 0x00d73350
void PlaceSurfaceSamples(int continent, cSurfaceSampler* obj, Vector3* dir, float radius, float spacing)
{
    if (obj == 0 || obj->mCells.mpBegin != obj->mCells.mpEnd)
        return;
    CellVector* cells = &obj->mCells;

    SP::cPlanetModel* planet = SP::PlanetModel();
    float water = planet->GetWaterHeight();
    float waterSq = water * water;

    cells->clear();
    cells->reserve(RoundToInt(radius / spacing * 2.0f));

    float spacingSq = spacing * spacing;
    float len = sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z);
    float inv = 1.0f / len;
    float rayRadius = len * 0.0078125f * 0.5f + spacing;

    int rad = RoundToInt(inv * 256.0f * radius);

    float ax = fabsf(dir->x);
    float nx = dir->x * inv;
    float ny = dir->y * inv;
    float ay = fabsf(dir->y);
    float az = fabsf(dir->z);
    float nz = dir->z * inv;
    float coneSq = (inv * radius) * (inv * radius);

    FaceRect rects[5];
    int count;
    {
    int cell[3];
    if (az >= ax && az >= ay) {
        cell[0] = TruncToInt((dir->x / dir->z + 1.0f) * 128.0f);
        cell[1] = TruncToInt((dir->y / az + 1.0f) * 128.0f);
        cell[2] = (dir->z >= 0.0f) ? 0 : 1;
    } else if (ay >= ax) {
        cell[0] = TruncToInt((dir->z / dir->y + 1.0f) * 128.0f);
        cell[1] = TruncToInt((dir->x / ay + 1.0f) * 128.0f);
        cell[2] = (dir->y >= 0.0f) ? 4 : 5;
    } else {
        cell[0] = TruncToInt((dir->y / dir->x + 1.0f) * 128.0f);
        cell[1] = TruncToInt((dir->z / ax + 1.0f) * 128.0f);
        cell[2] = (dir->x >= 0.0f) ? 2 : 3;
    }
    if (cell[0] == 0x100)
        cell[0] = 0xff;
    if (cell[1] == 0x100)
        cell[1] = 0xff;

    count = GatherFaceRects(0x100, cell, rad, rects);
    }
    if (count <= 0)
        return;

    FaceRect* r = rects;
    do {
        for (int j = r->y0; j < r->y1; ++j) {
            for (int i = r->x0; i < r->x1; ++i) {
                float sy = ((float)j + 0.5f) * 0.0078125f - 1.0f;
                float sx = ((float)i + 0.5f) * 0.0078125f - 1.0f;
                float rl = 1.0f / sqrtf(sx * sx + sy * sy + 1.0f);
                const uint8_t* axes = kFaceAxes[r->face >> 1];
                float s = (r->face & 1) ? -rl : rl;
                float p[3];
                p[axes[0]] = s * sx;
                p[axes[1]] = rl * sy;
                p[axes[2]] = s;

                float d0 = p[0] - nx;
                float d2 = p[2] - nz;
                float d1 = p[1] - ny;
                if (d0 * d0 + d2 * d2 + d1 * d1 > coneSq)
                    continue;

                Vector3 pos;
                planet->DirectionToSurfacePosition(&pos, (Vector3*)p);
                if (waterSq > pos.x * pos.x + pos.y * pos.y + pos.z * pos.z)
                    continue;
                if (planet->GetContinent(&pos) != continent)
                    continue;
                Vector3 frame;
                if (!planet->GetSurfaceFrame(&pos, rayRadius, &frame))
                    continue;

                Vector3 down;
                down.x = -frame.x;
                down.y = -frame.y;
                down.z = -frame.z;
                Vector3 hit;
                if (CastRay(&pos, &down, 0.1f, rayRadius, &hit) == FLT_MAX)
                    continue;

                bool tooClose = false;
                for (Cell* c = cells->mpBegin; c != cells->mpEnd; ++c) {
                    float ex = c->mPoint.x - pos.x;
                    float ez = c->mPoint.z - pos.z;
                    float ey = c->mPoint.y - pos.y;
                    if (ex * ex + ez * ez + ey * ey < spacingSq) { tooClose = true; break; }
                    float hz = c->mHit.z - hit.z;
                    float hy = c->mHit.y - hit.y;
                    float hx = c->mHit.x - hit.x;
                    if (hz * hz + hy * hy + hx * hx < spacingSq) { tooClose = true; break; }
                }
                if (tooClose)
                    continue;

                Cell& n = cells->push_back();
                n.mFlag = 0;
                n.mPoint = pos;
                n.mHit = hit;
            }
        }
        ++r;
    } while (--count != 0);
}

// =============================================================================================
// CellVector operations (eastl::vector<Cell> with the Simulator allocator).  00d73090 is the
// member erase(first,last) (moves [last, mpEnd) down to first); 00d73100 is DoInsertValue.
// =============================================================================================

void* EAAllocate(unsigned size, const char* name, unsigned a, unsigned b, const char* file, int line); // 0x00f473a0
void  operator delete[](void* p) throw();                                                              // 0x00f47380
Cell* CopyCells(Cell* first, Cell* last, Cell* dest);                                                  // 0x00d72bb0

// @ 0x00d73090
Cell* CellVector::erase(Cell* first, Cell* last)
{
    Cell* dst = first;
    for (Cell* src = last; src != mpEnd; ++src)
        *dst++ = *src;
    mpEnd -= last - first;
    return first;
}

// @ 0x00d73100
void CellVector::DoInsertValue(Cell* pos, const Cell& value)
{
    if (mpEnd != mpCapacity) {
        if (pos >= mpBegin && pos < mpEnd)
            ++pos;
        if (mpEnd != 0)
            ::new ((void*)mpEnd) Cell(*(mpEnd - 1));
        for (Cell* p = mpEnd - 1; p != pos; --p)
            *p = *(p - 1);
        *pos = value;
        mpEnd += 1;
        return;
    }

    unsigned size = (unsigned)(mpEnd - mpBegin);
    unsigned newCap = size * 2;
    if (newCap == 0)
        newCap = 1;

    Cell* mem = (Cell*)EAAllocate(newCap * 0x1c, (const char*)0x013f09b4u, 0, 0,
                                  (const char*)0x013ebb38u, 0xd1);
    Cell* mid = CopyCells(mpBegin, pos, mem);
    if (mid != 0)
        ::new ((void*)mid) Cell(value);
    Cell* newEnd = CopyCells(pos, mpEnd, mid + 1);
    if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
        operator delete[](mpBegin);
    mpBegin = mem;
    mpEnd = newEnd;
    mpCapacity = mem + newCap;
}

// =============================================================================================
// SP::cTribeGameBehaviorFish / cTribeGameBehaviorFeedBaby behaviour methods and the
// AgentInfoMap lookup.  Layouts follow the retail build (base-class +8 shift vs the dev PDB).
// =============================================================================================

namespace SP {

class cTribe;
class cSPCreatureCitizen;

// ---- creature: only the members these functions read ---------------------------------------
class cTribeMember {
public:
    virtual void v00();                                  // +0x00
    virtual void v04();                                  // +0x04
    cTribe* GetTribe();                                  // 0x00c22f50
    void  PerformSocialAction(int target, int a);        // 0x00c23300

    uint8_t  pad08[0x58 - 0x08];                         // +0x08..+0x58
    void*    mAgentKey;                                  // +0x58  agent-map key
    uint8_t  pad5c[0xd0 - 0x5c];                         // +0x5c..+0xd0
};

struct cLocoStub {                                       // the creature's +0xc0 loco base
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector3* GetPosition();                      // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool Slot58();                               // +0x58
};

class cSPCreatureCitizen : public cTribeMember {
public:
    uint8_t  pad_d0[0xb4c - 0xd0];                       // +0xd0..+0xb4c
    void*    mpOrderManager;                             // +0xb4c
    uint8_t  pad_b50[0xb64 - 0xb50];                     // +0xb50..+0xb64
    uint8_t  mFlagB64;                                   // +0xb64

    void  SetToolFacing(float x, float y, float z);      // 0x00c227f0
    uint8_t GetFlagB64();                                // 0x00c0b700  (byte at +0xb64)
    bool  HasSocialAction();                             // 0x00c22850
    void  SetToolArg(int a);                             // 0x00c22860
    void  IsWaitingForTool(int tool);                    // 0x00c26380
};

// engine sub-object at creature+0x34 (handle + shape query)
struct cEngSub34 {
    void* Handle();                                      // 0x00cee330
    float Radius();                                      // 0x00cee380
};

// object returned by AgentVecPush whose Cleanup is 0x00ac79e0
struct cFishSpot {
    void Cleanup(void* a, void* b);                      // 0x00ac79e0 (ecx = this)
};

// vtable stub for objects whose +0x2c slot returns a Vector3*
struct cVt32 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector3* At0x2c();                           // +0x2c
};

// ---- tribe ---------------------------------------------------------------------------------
class cTribe {
public:
    uint8_t  pad_00[0x120];
    cVt32    mLeader;                                    // +0x120  embedded object (vptr at +0x120)
    void FindSpot(int kind, int id);                     // 0x00c98750 (ecx = tribe)
    void TribeSpotRemove(int kind, void* arg);           // 0x00c97d40 (ecx = tribe)
};

// target-slot objects reached through mTargetBlocks
struct cTargetSlot {
    virtual void v00();
    virtual void* Find(int key);                         // +0x04
};

// order manager at citizen+0xb4c
struct cOrderManager {
    void* FirstPending();                                // 0x00bca2c0
};

// the 0x38-byte "Tribe Fish Location" object handed to SetAgent
struct cTribeFishLocation {
    cTribeFishLocation* Init(Vector3* pos, float a, float b);   // 0x00ac06c0 (ret 0xc)
};

// UTFWin::Window query the tribe object answers
struct cWindow {
    bool Initialize();                                   // 0x00b1fbf0
};

// AutoRefCount<T> assignment (ecx = &slot, argument = raw pointer)
struct AutoRefCount {
    void Assign(void* p);                                // 0x00b5f950
};

// base behaviour whose RemoveAgent we forward to
class cBehaviorSpaceTurret {
public:
    void RemoveAgent(void* a1, uint32_t a2, uint32_t a3,
                     uint32_t a4, uint32_t a5, uint32_t a6);   // 0x00d7a020 (ret 0x18)
};

int  __stdcall SetupHotSpot(Vector3* pos, int a);        // 0x00c9afb0 (ret 8)
int  HotSpotGetClosest(Vector3* pos, float a);           // 0x00c8f040
void* AgentOrderFirstPending(void* mgr);                 // 0x00bca2c0
Vector3* AgentOrderNodePos(void* node39);                // 0x00cce910
void  HotSpotGetPos(Vector3* out, int key);              // 0x00c9af80
void* AgentVecPush(int a, void* vec);                    // 0x00b3d2b0
cSurfaceSampler* SamplerFromPos(uint32_t key);           // 0x00c94430
void  ClearSamplerCell(cSurfaceSampler* s, unsigned idx); // 0x00d726e0

float GetPropertyT_float(int owner, int key, float def); // 0x004e1c70

// ---- agent info (retail cAgentInfo, 0x30 bytes; the dev PDB's is 0x68) ----------------------
struct cAgentInfo {
    int32_t  mState;          // +0x00  InteractionState
    int32_t  mStateTime;      // +0x04
    int32_t  mUnk_08;         // +0x08
    int32_t  mUnk_0c;         // +0x0c
    uint32_t mUnk_10;         // +0x10
    uint32_t mUnk_14;         // +0x14
    float    mFishAccum;      // +0x18
    float    mFishRate;       // +0x1c
    int32_t  mHotSpotKey;     // +0x20
    uint32_t mUnk_24;         // +0x24
    uint8_t  mFlag_28;        // +0x28
    uint8_t  mFlag_29;        // +0x29
    uint8_t  mFlag_2a;        // +0x2a
    uint8_t  pad2b[1];        // +0x2b
    uint32_t mUnk_2c;         // +0x2c
    cAgentInfo();                                          // per-field init
};
inline cAgentInfo::cAgentInfo()
{
    mStateTime = -1;
    mUnk_08    = -1;
    mHotSpotKey = -1;
    mState     = 0;
    mUnk_10    = 0;
    mUnk_14    = 0;
    mUnk_24    = 0;
    mFlag_28   = 0;
    mFlag_29   = 0;
    mFishAccum = 0.0f;
    mFishRate  = 0.0f;
    mFlag_2a   = 1;
}

struct AgentNode {
    AgentNode* mpLeft;        // +0x00
    AgentNode* mpRight;       // +0x04
    void*      mpParent;      // +0x08
    uint8_t    mColor;        // +0x0c
    uint8_t    pad0d[3];
    uint32_t   mKey;          // +0x10
    uint8_t    pad14[0x18 - 0x14];
    cAgentInfo mValue;        // +0x18
};

namespace eastl { struct true_type {}; }

struct AgentIterator {
    AgentNode* mpNode;
    AgentIterator(AgentNode* p) : mpNode(p) {}
    AgentIterator(const AgentIterator& x) : mpNode(x.mpNode) {}
};

struct AgentInsertResult {
    AgentIterator first;
    bool second;
};

// eastl::pair<const uint32_t, cAgentInfo>: second is 8-aligned (4 bytes of padding)
struct AgentPair {
    uint32_t   first;
    uint32_t   pad;
    cAgentInfo second;
    AgentPair(uint32_t k, const cAgentInfo& v) : first(k), second(v) {}
};

// eastl::map<agent*, cAgentInfo> as embedded at +0x74 of the behaviour
class cAgentInfoMap {
public:
    uint32_t   mCompare;      // +0x00
    AgentNode* mAnchorRight;  // +0x04  anchor node (mpNodeRight, the "left" link)
    AgentNode* mAnchorLeft;   // +0x08
    AgentNode* mpRoot;        // +0x0c  anchor.mpNodeParent
    uint8_t    mAnchorColor;  // +0x10
    uint8_t    pad11[3];
    uint32_t   mnSize;        // +0x14

    cAgentInfo* FindOrAdd(uint32_t* pKey);                          // 0x00d73bc0
    AgentInsertResult DoInsertValue(AgentIterator position, const AgentPair& value,
                                    eastl::true_type tag);           // 0x00d73280
};

// ---- the behaviour -------------------------------------------------------------------------
// vtbl0 ends at +0x58 with the "current arrangement" query.
class cBehaviorVt {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void* GetArrangement();                          // +0x58
    virtual void SetAgent(void* loc);                        // +0x5c
};

class cTribeGameBehaviorFish : public cBehaviorVt {
public:
    void**   vtbl1;            // +0x04
    uint8_t  pad08[0x0c - 0x08];
    void**   mTargetBlocks;    // +0x0c
    uint8_t  pad10[0x24 - 0x10];
    uint32_t mTargetIndex;     // +0x24
    uint8_t  pad28[0x74 - 0x28];
    cAgentInfoMap mAgentInfoMap;   // +0x74
    float    mTotalFoodFished;     // +0x8c
    uint32_t field_90;             // +0x90
    float    mWaterCheckDistance;  // +0x94
    uint8_t  mbStartedToFish;      // +0x98
    uint8_t  field_99;             // +0x99
    uint8_t  pad9a[0x9c - 0x9a];
    float    mTimeToLook;          // +0x9c
    float    mLuckiness;           // +0xa0
    float    mEatingBoost;         // +0xa4
    float    mFoodEaten;           // +0xa8
    float    mFishIdleMin;         // +0xac
    float    mFishIdleVar;         // +0xb0
    float    mFishPerSecond;       // +0xb4
    float    mFoodPerFish;         // +0xb8
    void*    mpTribe;              // +0xbc  AutoRefCount<cTribe>
    uint64_t mLastTime;            // +0xc0
    Vector3  mClosestLand;         // +0xc8

    void Sub_00c2e4e0();                                     // 0x00c2e4e0  base continuation
    bool CheckAgent(void* agent);                            // 0x00d7a010
    void PreAction_A();                                      // 0x00d739c0
    bool PreAction_B(void* agent);                           // 0x00d73ca0
    void RemoveAgent(void* agentMap, uint32_t idx, uint32_t a,
                     uint32_t b, uint32_t c, uint32_t d);    // 0x00d73ec0
};

} // namespace SP

// ---- the agent->creature cast used everywhere -----------------------------------------------
struct AgentObj {
    virtual void v00();
    virtual void v04();
    virtual void* Cast(int key);        // +0x08
};

// @ 0x00d73bc0
SP::cAgentInfo* SP::cAgentInfoMap::FindOrAdd(uint32_t* pKey)
{
    AgentNode* anchor = (AgentNode*)&mAnchorRight;
    AgentNode* y = anchor;
    AgentNode* x = (AgentNode*)mpRoot;
    while (x != 0) {
        if (x->mKey < *pKey)
            x = x->mpLeft;
        else {
            y = x;
            x = x->mpRight;
        }
    }
    if (y != anchor && *pKey >= y->mKey)
        return &y->mValue;

    cAgentInfo info;
    AgentPair value(*pKey, info);
    AgentInsertResult r = DoInsertValue(AgentIterator(y), value, eastl::true_type());
    return &r.first.mpNode->mValue;
}

// 0x00d73280: eastl rbtree insert-with-hint of a key/value node (declared as a member above)

// ---- behaviour method bodies ----------------------------------------------------------------

extern float DAT_0169eee0;    // 0x0169eee0  fish idle value A
extern float DAT_0169eee4;    // 0x0169eee4  fish idle value B
extern float DAT_0169eee8;    // 0x0169eee8  fish idle value C
extern int   DAT_0158128c;    // 0x0158128c  game-bundle owner used by GetPropertyT
extern float DAT_013ec5b4;    // 0x013ec5b4  closest-hot-spot test distance
extern float DAT_01473c70;    // 0x01473c70  fish-location radius (10.0f)

// @ 0x00d739c0
void SP::cTribeGameBehaviorFish::PreAction_A()
{
    void* arrangement = GetArrangement();                    // vtbl0 +0x58
    if (arrangement != 0) {
        cSPCreatureCitizen* citizen =
            (cSPCreatureCitizen*)((AgentObj*)arrangement)->Cast(0x4f176642);
        if (citizen != 0) {
            mbStartedToFish = ((cLocoStub*)((char*)citizen + 0xc0))->Slot58();
            cTribe* tribe = citizen->GetTribe();

            mFishIdleVar   = DAT_0169eee0;
            mFishPerSecond = DAT_0169eee4;
            mFoodPerFish   = DAT_0169eee8;

            void* slot = 0;
            if (mTargetIndex != 0x3fffffff) {
                void* block = mTargetBlocks[mTargetIndex >> 7];
                slot = *(void**)((char*)block + (mTargetIndex & 0x7f) * 8 + 4);
                if (slot != 0)
                    slot = ((cTargetSlot*)slot)->Find(0xe69e1e);
            }

            Vector3* spotPos = (Vector3*)((char*)slot + 0x24);
            mLastTime = (uint64_t)(uint32_t)SetupHotSpot(spotPos, 0);

            cPlanetModel* planet = PlanetModel();
            float fishRadius  = GetPropertyT_float(DAT_0158128c, (int)0xe87e0b26u, 100.0f);
            float fishSpacing = GetPropertyT_float(DAT_0158128c, (int)0xb8ff9702u, 3.0f);

            if ((uint32_t)mLastTime != 0xffffffffu) {
                Vector3 hit;
                float step = fishRadius >= 15.0f ? fishRadius : 15.0f;
                if (planet->RayCast(spotPos, step, &hit, 0.5f, 0.0f, 0.0f)) {
                    mFishIdleVar   = hit.x;
                    mFishPerSecond = hit.y;
                    mFoodPerFish   = hit.z;

                    Vector3* leaderPos = tribe->mLeader.At0x2c();
                    int continent = PlanetModel()->GetContinent(leaderPos);
                    cSurfaceSampler* sampler = SamplerFromPos((uint32_t)mLastTime);
                    PlaceSurfaceSamples(continent, sampler, &hit, fishRadius, fishSpacing);
                }
            }

            mEatingBoost = GetPropertyT_float(DAT_0158128c, (int)0x8eefcau, 0.07f);
        }
    }
    Sub_00c2e4e0();
}

// @ 0x00d73ca0
bool SP::cTribeGameBehaviorFish::PreAction_B(void* agentRaw)
{
    cSPCreatureCitizen* citizen;
    if (agentRaw == 0) {
        citizen = 0;
    } else {
        citizen = (cSPCreatureCitizen*)((AgentObj*)agentRaw)->Cast(0x4f176642);
        if (citizen != 0) {
            cTribe* tribe = citizen->GetTribe();
            if (tribe != 0) {
                if (!((cWindow*)tribe)->Initialize())
                    return false;
                if (mpTribe == 0)
                    ((AutoRefCount*)&mpTribe)->Assign(tribe);
            }
        }
    }

    bool haveAgent = false;
    if (mTargetIndex != 0x3fffffff) {
        void* block = mTargetBlocks[mTargetIndex >> 7];
        void* slot = *(void**)((char*)block + (mTargetIndex & 0x7f) * 8 + 4);
        if (slot != 0 && ((cTargetSlot*)slot)->Find(0xe69e1e) != 0)
            haveAgent = true;
    }

    if (!haveAgent) {
        cTribeFishLocation* loc;
        void* pending = ((cOrderManager*)citizen->mpOrderManager)->FirstPending();
        if (pending != 0 && *(int*)pending == 1 &&
            *(short*)((char*)pending + 0x4b) != 0) {
            Vector3 pos = *AgentOrderNodePos((char*)pending + 0x39);
            void* mem = EAAllocate(0x38, "Simulator/Tribe Fish Location", 0, 0, 0, 0);
            loc = mem != 0 ? ((cTribeFishLocation*)mem)->Init(&pos, 0.0f, DAT_01473c70) : 0;
        } else {
            Vector3* pos = ((cLocoStub*)((char*)citizen + 0xc0))->GetPosition();
            int spot = HotSpotGetClosest(pos, DAT_013ec5b4);
            if (spot == -1)
                return false;
            Vector3 hit;
            HotSpotGetPos(&hit, spot);
            void* mem = EAAllocate(0x38, "Simulator/Tribe Fish Location", 0, 0, 0, 0);
            loc = mem != 0 ? ((cTribeFishLocation*)mem)->Init(&hit, 0.0f, DAT_01473c70) : 0;
        }
        SetAgent(loc);                                       // vtbl0 +0x5c
    }

    if (!CheckAgent(agentRaw))                               // 0x00d7a010
        return false;

    if (citizen != 0) {
        void** key = &citizen->mAgentKey;
        mAgentInfoMap.FindOrAdd((uint32_t*)&key)->mState = 0;

        key = &citizen->mAgentKey;
        uint8_t flag = citizen->GetFlagB64();
        mAgentInfoMap.FindOrAdd((uint32_t*)&key)->mFlag_2a = flag;

        citizen->mFlagB64 = 0;
        if (((cEngSub34*)((char*)citizen + 0x34))->Handle() == 0)
            citizen->IsWaitingForTool(8);
    }
    return true;
}

// @ 0x00d73ec0
void SP::cTribeGameBehaviorFish::RemoveAgent(void* agentMap, uint32_t idx, uint32_t a,
                                             uint32_t b, uint32_t c, uint32_t d)
{
    void* root  = ((void**)agentMap)[0];
    void* block = ((void**)root)[idx >> 7];
    void* agent = *(void**)((char*)block + (idx & 0x7f) * 8 + 4);

    if (agent != 0) {
        cSPCreatureCitizen* citizen =
            (cSPCreatureCitizen*)((AgentObj*)agent)->Cast(0x4f176642);
        if (citizen != 0) {
            cEngSub34* eng = (cEngSub34*)((char*)citizen + 0x34);
            void* handle = eng->Handle();

            void** key = &citizen->mAgentKey;
            cAgentInfo* info = mAgentInfoMap.FindOrAdd((uint32_t*)&key);
            if ((uint32_t)mLastTime != 0xffffffffu) {
                cSurfaceSampler* sampler = SamplerFromPos((uint32_t)mLastTime);
                ClearSamplerCell(sampler, (unsigned)info->mStateTime);
            }

            uint8_t flag = info->mFlag_2a;
            info->mStateTime = -1;
            citizen->mFlagB64 = flag;

            bool social = citizen->HasSocialAction();
            citizen->SetToolArg(1);
            citizen->SetToolFacing(DAT_0169eee0, DAT_0169eee4, DAT_0169eee8);

            if (handle != 0) {
                if (eng->Radius() == 0.0f) {
                    void* spot = AgentVecPush((int)(size_t)handle, eng);
                    ((cFishSpot*)spot)->Cleanup(handle, eng);
                } else if (!social) {
                    citizen->PerformSocialAction((int)(size_t)handle, -1);
                    mWaterCheckDistance += *(float*)((char*)handle + 0x134);
                }
            }

            int spot = info->mHotSpotKey;
            citizen->GetTribe()->FindSpot(0xd, spot);
            citizen->GetTribe()->TribeSpotRemove(0xd, citizen);
        }
    }

    ((cBehaviorSpaceTurret*)this)->RemoveAgent(agentMap, idx, a, b, c, d);
}



