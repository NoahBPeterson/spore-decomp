// Slice s00d71f80 -- SP Gonzago tribe behaviour helpers and the fish-gathering behaviour
// (00d71f80..00d72fd0).
//
//   00d71f80  baby-food-cry "start" callback (SetCurrentToolEffect + clear a state dword)
//   00d71fa0  SP::TRIBE_BABY_FOOD_CRY_Tick   (behaviour tick state machine)
//   00d72100  SP::TRIBE_BABY_FEAR_Tick       (behaviour tick state machine)
//   00d72520  CastRay -- march a ray until it leaves the water, write the surface point
//   00d726e0  surface-sampler cell: clear a cell's flag by index
//   00d72720  same, over a sampler looked up from a planet position
//   00d72770  surface-sampler cell: get a cell pointer by index
//   00d727b0  surface-sampler cell: find the nearest free cell to two points
//   00d72bb0  CopyCells -- copy a 0x1c-byte cell range
//   00d72c30  SP::cTribeGameBehaviorFish::CanJoin
//   00d72d50  AgentInfoMap rbtree insert helper
//   00d72e70  SP::cTribeGameBehaviorFish::cTribeGameBehaviorFish
//   00d72f50  SP::cTribeGameBehaviorFish::scalar deleting destructor
//   00d72fd0  CellVector::reserve
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc; SSE scalar arithmetic,
// x87 sqrt, no unwind frame on the locals).
#include "types.h"
#include <math.h>
#include <string.h>

typedef unsigned char byte;

void operator delete(void* p) throw();        // 0x00f47380
void operator delete[](void* p) throw();      // 0x00f47380
void* EAAllocate(unsigned size, const char* name, unsigned a, unsigned b,
                 const char* file, int line);   // 0x00f473a0

namespace SP {

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    float LengthSquared() const { return x * x + y * y + z * z; }
};

// ---- planet model (thin stub for the callees this slice uses) ----------------------------
struct cPlanetModel {
    float       GetWaterHeight();                                             // 0x00b7e390
    float       GetRadiusAt(const cSPVector3* pos);                           // 0x00b7ef70
    cSPVector3* DirectionToSurfacePosition(cSPVector3* out, cSPVector3* dir);  // 0x00b815a0
    cSPVector3* MakeRandomWorldPosition(cSPVector3* out, const cSPVector3* dir); // 0x00b81780
};
cPlanetModel* PlanetModel();                                                  // 0x00b3d350
cSPVector3* normalized_safe(cSPVector3* out, const cSPVector3* in);          // 0x00449c20
cSPVector3* SomeRotate(cSPVector3* out, const cSPVector3* a, const cSPVector3* b);   // 0x0059aed0

// ---- generic vtable helpers --------------------------------------------------------------
struct cVt32 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual cSPVector3* AtAngle(float a, float b);   // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual float GetFacingAngle();                  // +0x70
};

// ---- creature / citizen stubs ------------------------------------------------------------
class cLocomotiveObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual cSPVector3* GetPosition();               // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8();
    virtual void GetSteerParams(void* params);       // +0xdc

    char  mTail[0x3e0 - 4];                          // pad the class out to 0x3e0
    bool IsNearGoal();                               // 0x00c42e20
};

class cTribe;
class cSPCreatureCitizen;

class cTribeMember {
public:
    virtual void v00(); virtual void v04();
    cTribe* GetTribe();                                                // 0x00c22f50
    void SetCurrentToolEffect(int tool, unsigned a);                   // 0x00c24f40
    void PlayAnimation(unsigned animID, int a, int b);                 // 0x00c12190
    void MoveToPointAndFacingAtSpeed(int speed, const cSPVector3* pt,
                                     const cSPVector3* facing, float f1, float f2); // 0x00c1c5c0
    void MoveToPointAtSpeed(int speed, const cSPVector3* pt, float f1, float f2);  // 0x00c1c1d0
    bool  QueryFlagB770();                                             // 0x00c0b770
    void  FuncC0CFF0(int a);                                           // 0x00c0cff0
    bool  FuncC0E0C0(int a);                                           // 0x00c0e0c0

    char pad00[0xc0];
    cLocomotiveObject mLoco;            // +0xc0
};

// a tribe object; only the members this slice reads
class cTribe {
public:
    char  pad00[0x120];
    cLocomotiveObject* mpLeader_120;    // +0x120  (GetPosition at vtable+0x2c)
    char  pad_124[0x260 - 0x124];
    void* mpLeader_260;                 // +0x260  (object whose +0x34 is a spatial base)
};

// ---- the surface sampler (cell vector at +0x40, element 0x1c) ----------------------------
struct Cell {
    byte       mFlag;     // +0x00
    char       pad1[3];
    cSPVector3 mPoint;    // +0x04
    cSPVector3 mHit;      // +0x10
    Cell& operator=(const Cell& o)
    {
        mFlag = o.mFlag;
        mPoint = o.mPoint;
        mHit = o.mHit;
        return *this;
    }
};

// eastl vector viewed as byte pointers so size() divides by the 0x1c stride
struct CellVector {
    byte* mpBegin;      // +0x00
    byte* mpEnd;        // +0x04
    byte* mpCapacity;   // +0x08

    int  size() const { return (int)(mpEnd - mpBegin) / 0x1c; }
    void  reserve(unsigned n);                    // 0x00d72fd0
};

// cSurfaceSampler: the cell vector lives at +0x40 of the manager object
struct cSurfaceSampler {
    char pad00[0x40];
    CellVector mCells;    // +0x40
};

cSurfaceSampler* SamplerFromPos(const cSPVector3* pos);    // 0x00c94430

// ---- fish behaviour ----------------------------------------------------------------------
class cInteractionAgent;

// the eastl::map<agent*, cAgentInfo> embedded in the fish behaviour (0x18 bytes)
struct AgentInfoMap {
    void*    field_00;      // +0x00
    void*    mAnchorLeft;   // +0x04  (anchor, self-referential)
    void*    mAnchorParent; // +0x08
    void*    mAllocName;    // +0x0c
    uint32_t mAllocBytes;   // +0x10
    uint32_t mnSize;        // +0x14
    void* InsertNode(void** out, void* parent, uint32_t* key, char side);  // 0x00d72d50
};

class cTribeGameBehaviorFish {
public:
    void**    vtbl0;                                       // +0x00
    void**    vtbl1;                                       // +0x04
    char      pad08[0x04];                                 // +0x08
    void**    mTargetBlocks;                               // +0x0c
    char      pad10[0x14];                                 // +0x10..+0x23
    uint32_t  mTargetIndex;                                // +0x24
    char      pad28[0x4c];                                 // +0x28..+0x73
    AgentInfoMap mAgentInfoMap;                            // +0x74  (0x18 bytes)
    float     mTotalFoodFished;                            // +0x8c
    uint32_t  field_90;                                    // +0x90
    float     mWaterCheckDistance;                         // +0x94
    byte      field_98;                                    // +0x98
    byte      field_99;                                    // +0x99
    char      pad9a[0x02];
    float     mTimeToLook;                                 // +0x9c
    float     mLuckiness;                                  // +0xa0
    float     mEatingBoost;                                // +0xa4
    float     mFoodEaten;                                  // +0xa8
    float     mFishIdleMin;                                // +0xac
    float     mFishIdleVar;                                // +0xb0
    float     mFishPerSecond;                              // +0xb4
    float     mFoodPerFish;                                // +0xb8
    void*     mpTribe;                                     // +0xbc  AutoRefCount<cTribe>
    unsigned long long mLastTime;                          // +0xc0
    cSPVector3 mClosestLand;                               // +0xc8

    bool CanJoin(cInteractionAgent* a, void* b);           // 0x00d72c30
    void* DeleteDtor(unsigned flags);                      // 0x00d72f50
    cTribeGameBehaviorFish();                              // 0x00d72e70
};

class cInteractionAgent {
public:
    virtual void v00();                                   // +0x00
    virtual void v04();                                   // +0x04
    virtual cSPCreatureCitizen* FindCreature(int key);    // +0x08
};

void __cdecl FishDtorBody(void);                          // 0x00d79fd0 (unused)
// external __thiscall helpers (undefined here; ecx carries the object)
struct SPExt {
    void Nuke(void* node);        // 0x009a9600  DoNukeSubtree
    void DtorBody();              // 0x00d79fd0  FishDtorBody
    void BaseCtor();              // 0x00abf320  cTribeGameInteraction ctor
};
extern void* SP_vtbl_Fish;    // 0x0147be30
extern void* SP_vtbl_Fish1;   // 0x0147be1c
void* AgentMapLookup(int a, void* fn, void** key);          // 0x00bc9b00
void* AgentOrderFindNode(void* a, int b, int c);            // 0x00bca620
void* AgentOrderFirstPending(void* a);                      // 0x00bca2c0
cSPVector3* AgentOrderNodePos(void* a);                     // 0x00cce910
void  RBTreeInsert(void* node, void* parent, void* anchor, int side);   // 0x009216a0

// The citizen side of the creature hierarchy (only the members this slice reads).
class cSPCreatureCitizen : public cTribeMember {
public:
    char  pad_b4c[0xb4c - 0xc0 - 0x3e0];
    void* mpOrderManager;   // +0xb4c
};

// a steering/order parameter block filled by the loco's virtual at vtable+0xdc
struct SteerParams {
    char  pad00[0x40];
    void* mpVec;            // +0x40  (a heap vector, released by the caller)
    char  pad44[0x24];
};

}  // namespace SP

// the constants
extern const float kFloatMax;      // 0x0147bd98  FLT_MAX
extern const float kOneF;          // 0x01470f1c  1.0f
extern const float kHalfF;         // 0x01485720  1.0f
extern const float kSqEps;         // 0x013ec4b8  1e-8f
extern const float kHundredF;      // 0x013ec4d0  100.0f
extern const float kEatBoostF;     // 0x013ec4bc  0.07f
extern const float kCfgA;          // 0x013ec4b4
extern const float kCfgB;          // 0x0147bd68
extern float kZeroA;               // 0x0157206c
extern float kZeroB;               // 0x01572070
extern const float kFearScaleF;    // 0x01581340
extern const float kSinHalfF;      // 0x01584190
extern const float kRotConstF;     // 0x01471064
extern const float kEquipPos[3];   // 0x0169eea4
extern const float kFishA;         // 0x0169eee0
extern const float kFishB;         // 0x0169eee4
extern const float kFishC;         // 0x0169eee8

// =========================================================================================
// 00d71f80 : *out = 0; citizen->SetCurrentToolEffect(0, -1); return 1
// =========================================================================================
// @ 0x00d71f80
bool FUN_00d71f80(SP::cTribeMember* citizen, int, int, int, int, unsigned* out)
{
    *out = 0;
    citizen->SetCurrentToolEffect(0, 0xffffffff);
    return true;
}

// =========================================================================================
// 00d71fa0 : SP::TRIBE_BABY_FOOD_CRY_Tick
//   state 0: pick a random world position, aim the citizen at it, advance to state 1.
//   state 1: when the goal is reached, play the food-cry animation and advance to state 2.
// =========================================================================================
// @ 0x00d71fa0
bool SP_FOOD_CRY_Tick(SP::cSPCreatureCitizen* citizen, int, int, int, int, uint32_t* state)
{
    if (*state == 0) {
        SP::cTribe* tribe = citizen->GetTribe();
        void* leader = tribe->mpLeader_260;
        SP::cVt32* sp = (SP::cVt32*)((char*)leader + 0x34);
        float angle = sp->GetFacingAngle();
        SP::cSPVector3* dir = sp->AtAngle(0.0f, angle);
        SP::cSPVector3 buf;
        SP::PlanetModel()->MakeRandomWorldPosition(&buf, dir);
        SP::cSPVector3* pos = ((SP::cLocomotiveObject*)((char*)citizen + 0xc0))->GetPosition();
        SP::cSPVector3 diff(buf.x - pos->x, buf.y - pos->y, buf.z - pos->z);
        float inv = 1.0f / sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z + kSqEps);
        SP::cSPVector3 facing(inv * diff.x, inv * diff.y, inv * diff.z);
        citizen->MoveToPointAndFacingAtSpeed(2, &buf, &facing, kZeroA, kZeroB);
        *state = 1;
    } else if (*state == 1) {
        if (((SP::cLocomotiveObject*)((char*)citizen + 0xc0))->IsNearGoal()) {
            *state = 2;
            citizen->PlayAnimation(0x2fc3666, 1, 0xffffffff);
            return true;
        }
    }
    return true;
}

// =========================================================================================
// 00d72100 : SP::TRIBE_BABY_FEAR_Tick
// =========================================================================================
// @ 0x00d72100
bool SP_FEAR_Tick(SP::cSPCreatureCitizen* citizen, int, int, int, int, uint32_t*)
{
    if (citizen->QueryFlagB770())
        return false;

    void* p = 0;
    if (citizen != 0)
        p = (char*)citizen + 0x5a8;
    void* mgr = SP::AgentMapLookup(0x060995fc, (void*)0x00d995c0, &p);
    void* order = SP::AgentOrderFindNode(mgr, 0, 0);
    if (order != 0) {
        SP::SteerParams s;
        for (unsigned i = 0; i < sizeof(s); ++i)
            ((char*)&s)[i] = 0;
        ((SP::cLocomotiveObject*)((char*)citizen + 0xc0))->GetSteerParams(&s);
        if (s.mpVec != 0 && *(int*)((char*)s.mpVec - 4) != 0)
            operator delete[](s.mpVec);
        citizen->FuncC0CFF0(0);
        if (!citizen->FuncC0E0C0(0x2fc3667))
            citizen->PlayAnimation(0x2fc3667, 1, 0xffffffff);
        return true;
    }

    if ((*(uint32_t*)((char*)citizen->mpOrderManager + 0x1cc) & 0x100) != 0) {
        SP::cLocomotiveObject* loco = (SP::cLocomotiveObject*)((char*)citizen + 0xc0);
        if (loco->IsNearGoal() || ((*(byte*)((char*)citizen + 0x330) & 1) != 0)) {
            SP::cTribe* tribe = citizen->GetTribe();
            float scale = kFearScaleF;
            SP::cSPVector3* tpos = tribe->mpLeader_120->GetPosition();
            SP::cSPVector3* cpos = loco->GetPosition();
            SP::cSPVector3 diff(cpos->x - tpos->x, cpos->y - tpos->y, cpos->z - tpos->z);
            SP::cSPVector3 n1, n2;
            SP::normalized_safe(&n1, &diff);
            SP::normalized_safe(&n2, (SP::cSPVector3*)tpos);
            float sh = sinf(kSinHalfF * kRotConstF);
            float ch = cosf(kSinHalfF * kRotConstF);
            SP::cSPVector3 quat(n2.x * sh, n2.y * sh, n2.z * sh);
            (void)ch;
            SP::cSPVector3 rot;
            SP::SomeRotate(&rot, &n1, &quat);
            SP::cSPVector3* tpos2 = tribe->mpLeader_120->GetPosition();
            SP::cSPVector3 pt(rot.x * scale + tpos2->x,
                              rot.y * scale + tpos2->y,
                              rot.z * scale + tpos2->z);
            SP::cSPVector3 surf;
            SP::PlanetModel()->DirectionToSurfacePosition(&surf, &pt);
            ((SP::cTribeMember*)citizen)->MoveToPointAtSpeed(3, &surf, kOneF, kOneF);
        }
        if (!citizen->FuncC0E0C0(0x2c38d92))
            citizen->PlayAnimation(0x2c38d92, 1, 0xffffffff);
        return true;
    }
    return false;
}

// =========================================================================================
// 00d72520 : CastRay -- march along a ray until it drops below the water, then write the
// surface point to *out and the last dry point back into *pos; return the distance.
// =========================================================================================
// @ 0x00d72520
float SP_CastRay(SP::cSPVector3* pos, SP::cSPVector3* dir, float step, float maxDist,
                 SP::cSPVector3* out)
{
    SP::cPlanetModel* pm = SP::PlanetModel();
    float waterH = pm->GetWaterHeight();
    float cx = pos->x, cy = pos->y, cz = pos->z;
    float t = step;
    for (;;) {
        if (maxDist <= t)
            return kFloatMax;
        SP::cSPVector3 p(pos->x + dir->x * t, pos->y + dir->y * t, pos->z + dir->z * t);
        float r = pm->GetRadiusAt(&p);
        if (r >= waterH) {
            float inv = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z + kSqEps);
            cx = inv * p.x * r;
            cy = inv * p.y * r;
            cz = inv * p.z * r;
            t += step;
            continue;
        }
        float inv = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
        out->x = inv * p.x * waterH;
        out->y = inv * p.y * waterH;
        out->z = inv * p.z * waterH;
        pos->x = cx;
        pos->y = cy;
        pos->z = cz;
        return t;
    }
}

// =========================================================================================
// 00d726e0 : clear one cell's flag, addressed by a sampler and an index.
// =========================================================================================
// @ 0x00d726e0
void SP_ClearCellByIndex(SP::cSurfaceSampler* s, unsigned index)
{
    if (s != 0) {
        if (index < (unsigned)s->mCells.size())
            *((byte*)s->mCells.mpBegin + index * 0x1c) = 0;
    }
}

// =========================================================================================
// 00d72720 : same, but the sampler is looked up from a planet position.
// =========================================================================================
// @ 0x00d72720
void SP_ClearCellAtPos(const SP::cSPVector3* pos, unsigned index)
{
    SP::cSurfaceSampler* s = SP::SamplerFromPos(pos);
    if (s != 0) {
        if (index < (unsigned)s->mCells.size())
            *((byte*)s->mCells.mpBegin + index * 0x1c) = 0;
    }
}

// =========================================================================================
// 00d72770 : cell pointer by index (null when out of range).
// =========================================================================================
// @ 0x00d72770
void* SP_GetCellByIndex(SP::cSurfaceSampler* s, unsigned index)
{
    if (s != 0) {
        if (index < (unsigned)s->mCells.size())
            return (byte*)s->mCells.mpBegin + index * 0x1c;
    }
    return 0;
}

// =========================================================================================
// 00d727b0 : find the free cell nearest (weighted) to two points; mark it used.
// =========================================================================================
// @ 0x00d727b0
int SP_FindNearestCell(SP::cSPVector3* a, SP::cSPVector3* b, SP::cSurfaceSampler* s,
                       unsigned* out)
{
    *out = 0xffffffff;
    unsigned count = (unsigned)s->mCells.size();
    float best = kFloatMax;
    unsigned i = 0;
    byte* base = s->mCells.mpBegin;
    while (i + 4 <= count) {
        for (int k = 0; k < 4; ++k) {
            byte* c = base + (i + k) * 0x1c;
            if (*c == 0) {
                float* pt = (float*)(c + 4);
                float* ht = (float*)(c + 0x10);
                float bx = pt[0] - b->x, by = pt[1] - b->y, bz = pt[2] - b->z;
                float ax = pt[0] - a->x, ay = pt[1] - a->y, az = pt[2] - a->z;
                float d = ((bz * bz + by * by) + bx * bx) * 2.0f
                        + ((ax * ax + az * az) + ay * ay);
                (void)ht;
                if (d < best) { *out = i + k; best = d; }
            }
        }
        i += 4;
    }
    while (i < count) {
        byte* c = base + i * 0x1c;
        if (*c == 0) {
            float* pt = (float*)(c + 4);
            float bx = pt[0] - b->x, by = pt[1] - b->y, bz = pt[2] - b->z;
            float ax = pt[0] - a->x, ay = pt[1] - a->y, az = pt[2] - a->z;
            float d = ((bz * bz + by * by) + bx * bx) * 2.0f
                    + ((ax * ax + az * az) + ay * ay);
            if (d < best) { *out = i; best = d; }
        }
        ++i;
    }
    if (*out == 0xffffffff)
        return 0xffffff00;
    base[*out * 0x1c] = 1;
    return 1;
}

// =========================================================================================
// 00d72bb0 : copy a range of 0x1c-byte cells (first..last) to dest; returns new dest end.
// =========================================================================================
// @ 0x00d72bb0
byte* SP_CopyCells(byte* first, byte* last, byte* dest)
{
    if (first != last) {
        do {
            if (dest != 0) {
                SP::Cell& d = *(SP::Cell*)dest;
                SP::Cell& f = *(SP::Cell*)first;
                d = f;
            }
            first += 0x1c;
            dest += 0x1c;
        } while (first != last);
    }
    return dest;
}

// =========================================================================================
// 00d72c30 : SP::cTribeGameBehaviorFish::CanJoin
// =========================================================================================
// @ 0x00d72c30
bool SP::cTribeGameBehaviorFish::CanJoin(SP::cInteractionAgent* agent, void*)
{
    if (agent == 0)
        return false;
    SP::cSPCreatureCitizen* creature = agent->FindCreature(0x4f176642);
    if (creature == 0)
        return false;
    void* tribe = this->mpTribe;
    if (creature->GetTribe() != (SP::cTribe*)tribe && this->mpTribe != 0)
        return false;
    if (this->mTargetIndex == 0x3fffffff)
        return true;
    void* block = this->mTargetBlocks[this->mTargetIndex >> 7];
    void* slot = *(void**)((char*)block + (this->mTargetIndex & 0x7f) * 8 + 4);
    if (slot == 0)
        return true;
    void* node = (*(void*(**)(void*, int))slot)(slot, 0xe69e1e);
    if (node == 0)
        return true;
    void* pending = SP::AgentOrderFirstPending(*(void**)((char*)creature + 0xb4c));
    if (pending == 0 || *(int*)pending != 1)
        return true;
    if (*(unsigned short*)((char*)pending + 0x4b) == 0)
        return true;
    SP::cSPVector3* p = SP::AgentOrderNodePos((char*)pending + 0x39);
    float dx = *(float*)((char*)node + 0x24) - p->x;
    float dy = *(float*)((char*)node + 0x28) - p->y;
    float dz = *(float*)((char*)node + 0x2c) - p->z;
    if (dz * dz + dy * dy + dx * dx < kOneF)
        return true;
    return false;
}

// =========================================================================================
// 00d72d50 : AgentInfoMap rbtree insert helper (__thiscall; out, parent, key, side)
// =========================================================================================
// @ 0x00d72d50
void* SP::AgentInfoMap::InsertNode(void** out, void* parent, uint32_t* key, char side)
{
    int insertSide;
    if (side != 0 || parent == (char*)this + 4)
        insertSide = 0;
    else if (*key < *(uint32_t*)((char*)parent + 0x10))
        insertSide = 1;
    else
        insertSide = 0;

    void* node = EAAllocate(0x48, (const char*)0x013f09b4u, 0, 0, (const char*)0x013ebb38u, 0xd1);
    if ((char*)node + 0x10 != 0) {
        uint32_t* dst = (uint32_t*)((char*)node + 0x10);
        for (int i = 0xe; i != 0; --i)
            *dst++ = *key++;
    }
    SP::RBTreeInsert(node, parent, (char*)this + 4, insertSide);
    this->mnSize += 1;
    *out = node;
    return node;
}

// =========================================================================================
// 00d72e70 : SP::cTribeGameBehaviorFish::cTribeGameBehaviorFish
// =========================================================================================
// @ 0x00d72e70
SP::cTribeGameBehaviorFish::cTribeGameBehaviorFish()
{
    ((SPExt*)this)->BaseCtor();                            // 0x00abf320
    this->vtbl0 = (void**)&SP::SP_vtbl_Fish;               // 0x0147be30
    this->vtbl1 = (void**)&SP::SP_vtbl_Fish1;              // 0x0147be1c
    this->mAgentInfoMap.mAnchorParent = 0;
    this->mAgentInfoMap.mAllocName = 0;
    this->mAgentInfoMap.mAllocBytes = 0;
    this->mAgentInfoMap.mAllocName = 0;
    this->mAgentInfoMap.mAllocBytes = 0;
    this->mAgentInfoMap.mnSize = 0;
    void* anchor = (char*)&this->mAgentInfoMap + 0x04;
    this->mAgentInfoMap.mAnchorParent = anchor;
    this->mAgentInfoMap.mAnchorLeft = anchor;
    this->mWaterCheckDistance = 0.0f;
    this->mLuckiness = 0.0f;
    this->field_90 = 0;
    this->field_98 = 0;
    this->field_99 = 0;
    this->mTimeToLook = kHundredF;
    this->mEatingBoost = kEatBoostF;
    this->mFoodEaten = 0.0f;
    this->mFishIdleMin = 0.0f;
    this->mFishIdleVar = kFishA;
    this->mFishPerSecond = kFishB;
    this->mFoodPerFish = kFishC;
    this->mpTribe = 0;
    this->mLastTime = ~0ULL;
}

// =========================================================================================
// 00d72f50 : SP::cTribeGameBehaviorFish::`scalar deleting destructor'  (this, flags)
// =========================================================================================
// @ 0x00d72f50
void* SP::cTribeGameBehaviorFish::DeleteDtor(unsigned flags)
{
    this->vtbl0 = (void**)&SP::SP_vtbl_Fish;
    this->vtbl1 = (void**)&SP::SP_vtbl_Fish1;
    void* tribe = this->mpTribe;
    if (tribe != 0) {
        void** vt = *(void***)tribe;
        ((void(__thiscall*)(void*))vt[1])(tribe);
    }
    SPExt* map = (SPExt*)&this->mAgentInfoMap;
    void* node = this->mAgentInfoMap.mAllocName;
    map->Nuke(node);
    ((SPExt*)this)->DtorBody();
    if (flags & 1)
        operator delete[](this);
    return this;
}

// =========================================================================================
// 00d72fd0 : CellVector::reserve
// =========================================================================================
// @ 0x00d72fd0
void SP::CellVector::reserve(unsigned n)
{
    int cap = (int)(mpCapacity - mpBegin) / 0x1c;
    if (n > (unsigned)cap) {
        byte* mem;
        if (n == 0)
            mem = 0;
        else
            mem = (byte*)EAAllocate(n * 0x1c, (const char*)0x013f09b4u, 0, 0,
                                    (const char*)0x013ebb38u, 0xd1);
        SP_CopyCells(mpBegin, mpEnd, mem);
        if (mpBegin != 0 && *(int*)(mpBegin - 4) != 0)
            operator delete[](mpBegin);
        byte* oldBegin = mpBegin;
        mpBegin = mem;
        mpEnd = mem + ((mpEnd - oldBegin) / 0x1c) * 0x1c;
        mpCapacity = mem + n * 0x1c;
    }
}
