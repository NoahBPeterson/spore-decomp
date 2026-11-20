// @ 0x00db7d60
// IdleBlock::GetWalkDestination -- pick the spot a tribe member walks to when
// it leaves the idle behaviour: either the caller's hint, or a random world
// position around the tribe tool, then drop already-reserved / keep-clear
// cells from the cluster around it and reserve the closest one.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

struct Vec3_s00db7d60 {
    float x;
    float y;
    float z;

    // Retail copies a whole position one float at a time through the x87
    // (fld/fstp), so the type has a user copy assignment; plain copies of it
    // (the initialisation of a local) stay in dword/SSE form.
    Vec3_s00db7d60& operator=(const Vec3_s00db7d60& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
};

// One entry of a reservation map: cube-map cell + reserver id + flags.
struct ReservedSpot_s00db7d60 {
    unsigned mX;
    unsigned mY;
    unsigned mZ;
    unsigned mID;
    bool     mbReserved;
    bool     mbHasCitizen;
    unsigned char mPad12[2];
};

struct ReservedPair_s00db7d60 {
    unsigned mKey;
    ReservedSpot_s00db7d60 mSpot;
};

void __cdecl FUN_00f47380(void* p);                 // 0x00f47380 operator delete

// The data structures below mirror the retail objects by offset; only the
// members this function touches are named.

// The cluster map returned by cReservationGrid::GetRCluster: a fixed-capacity
// (121) inline vector of ReservedPair with the "is the buffer still inline"
// pointer its teardown uses.
struct ClusterMap_s00db7d60 {
    ReservedPair_s00db7d60* mpBegin;         // +0x00
    ReservedPair_s00db7d60* mpEnd;           // +0x04
    ReservedPair_s00db7d60* mpCapacityEnd;   // +0x08
    void*                   mpUnk0c;         // +0x0c
    ReservedPair_s00db7d60* mpBuffer;        // +0x10
    void*                   mpUnk14;         // +0x14
    ReservedPair_s00db7d60  mData[121];      // +0x18 (size 0xb58)
    unsigned char mbCompare;                 // +0xb70
    unsigned char mPad[3];

    // Written in the order the retail constructor's inlined stores appear.
    ClusterMap_s00db7d60() {
        mpBuffer = mData;
        mpEnd = mData;
        mpBegin = mData;
        mpCapacityEnd = mData + 121;
    }
    // Teardown is written out rather than left to a destructor: retail has no
    // unwind frame, only the two inlined copies of this check.
    void Destroy() {
        if (mpBegin != 0 && mpBegin != mpBuffer)
            FUN_00f47380(mpBegin);
    }
};

struct ReservationGrid_s00db7d60 {
    unsigned mGridRes;                       // +0x0000
    float    mSquareSize;                    // +0x0004
    unsigned char mReservedSpots[0x97c];     // +0x0008
    unsigned char mKeepClearSpots[0x97c];    // +0x0984
    float mGridMax;                          // +0x1300
    float mGridMin;                          // +0x1304
    float mGridAvg;                          // +0x1308

    void* GetReservedSpots();                                        // 0x0098f5a0
    void* GetKeepClearSpots();                                       // 0x00cc7070
    void  GetRCluster(const Vec3_s00db7d60* pos, ClusterMap_s00db7d60* cluster,
                      unsigned face);                                // 0x00cc8670
    void  FilterRCluster(ClusterMap_s00db7d60* dst, void* src);      // 0x00cc7fa0
    unsigned GetClosestInRVector(ClusterMap_s00db7d60* cluster,
                                 const Vec3_s00db7d60* pos);         // 0x00cc79d0
    bool  ReserveRCoord(unsigned rcoord);                            // 0x00cc8140
    Vec3_s00db7d60* PosFromRCoord(Vec3_s00db7d60* out, unsigned rcoord); // 0x00cc78f0
    void  FreeRCoord(unsigned rcoord);                               // 0x00cc7f90
};

struct Tribe_s00db7d60 {
    void* mpVtbl;                            // +0x0000
    unsigned char mPad004[0x558 - 0x004];
    ReservationGrid_s00db7d60 mGrid;         // +0x0558

    void* V_AC() {
        return (*(void* (__thiscall**)(void*))(*(char**)this + 0xac))(this);
    }
    Vec3_s00db7d60* GetToolPosition(Vec3_s00db7d60* out, int kind);  // 0x00c91190
};

struct Tool_s00db7d60 {
    void* mpVtbl;                            // +0x0000

    int V_74() {
        return (*(int (__thiscall**)(void*))(*(char**)this + 0x74))(this);
    }
};

struct Creature_s00db7d60 {
    void* mpVtbl;                            // +0x0000

    void* GetActiveTool();                                           // 0x00c23290
    Tribe_s00db7d60* GetTribe();                                     // 0x00c22f50
};

struct PlanetModel_s00db7d60 {
    void* mpVtbl;                            // +0x0000

    Vec3_s00db7d60* MakeRandomWorldPosition(Vec3_s00db7d60* out,
                                            const Vec3_s00db7d60* toolPos,
                                            float minOffset,
                                            float maxOffset);        // 0x00b81780
    Vec3_s00db7d60* DirectionToSurfacePosition(Vec3_s00db7d60* out,
                                               const Vec3_s00db7d60* dir); // 0x00b815a0
};

PlanetModel_s00db7d60* PlanetModel();        // 0x00b3d350

// Idle behaviour-node persistent block.
struct IdleBlock_s00db7d60 {
    unsigned mState;                         // +0x00
    unsigned mReservedSpot;                  // +0x04
    unsigned mAnimationID;                   // +0x08
    int      mLoopCount;                     // +0x0c
    float    mTimer;                         // +0x10
    Creature_s00db7d60* mpTribeMember;       // +0x14

    Vec3_s00db7d60* FUN_00db7d60(Vec3_s00db7d60* out,
                                 const Vec3_s00db7d60* in);
};

extern float g_radiusScale_00db7d60;         // 0x013eb8c8
extern float g_radiusBias_00db7d60;          // 0x01470f1c

// @ 0x00db7d60
Vec3_s00db7d60* IdleBlock_s00db7d60::FUN_00db7d60(Vec3_s00db7d60* out,
                                                   const Vec3_s00db7d60* in)
{
    PlanetModel_s00db7d60* pm;
    float radius;
    Vec3_s00db7d60 pos;
    Vec3_s00db7d60 scratch;
    Vec3_s00db7d60 surf;

    Tool_s00db7d60* tool = (Tool_s00db7d60*)mpTribeMember->GetActiveTool();
    radius = (float)tool->V_74() * 0.3f;
    Tribe_s00db7d60* tribe = mpTribeMember->GetTribe();
    if (tribe->V_AC() != 0) {
        pm = PlanetModel();

        // The caller's hint wins; otherwise a random spot around the tool.
        // The tool position only exists on that path, in its own scope.
        const Vec3_s00db7d60* src;
        if (in != 0) {
            src = in;
        } else {
            Vec3_s00db7d60 toolPos;
            src = pm->MakeRandomWorldPosition(&scratch,
                                              tribe->GetToolPosition(&toolPos, 0),
                                              0.0f, radius + 2.0f);
        }
        pos.x = src->x;
        pos.y = src->y;
        pos.z = src->z;

        if (mReservedSpot != 0xffffffffu) {
            Tribe_s00db7d60* t = mpTribeMember->GetTribe();
            t->mGrid.FreeRCoord(mReservedSpot);
            mReservedSpot = 0xffffffffu;
        }

        {
            ClusterMap_s00db7d60 cluster;
            ReservationGrid_s00db7d60* grid = &tribe->mGrid;
            grid->GetRCluster(&pos, &cluster, 4);
            grid->FilterRCluster(&cluster, grid->GetReservedSpots());
            grid->FilterRCluster(&cluster, grid->GetKeepClearSpots());

            if (cluster.mpBegin == cluster.mpEnd) {
                if (in != 0) {
                    *out = *in;
                    cluster.Destroy();
                    return out;
                }
            } else {
                unsigned index = grid->GetClosestInRVector(&cluster, &pos);
                if (index != 0xffffffffu && grid->ReserveRCoord(index)) {
                    Vec3_s00db7d60* cell = grid->PosFromRCoord(&scratch, index);
                    Vec3_s00db7d60* s = pm->DirectionToSurfacePosition(&surf, cell);
                    Vec3_s00db7d60 spot = *s;
                    mReservedSpot = index;
                    out->x = spot.x;
                    out->y = spot.y;
                    out->z = spot.z;
                    cluster.Destroy();
                    return out;
                }
            }
            cluster.Destroy();
        }
    }

    tribe->GetToolPosition(out, 0);
    return out;
}
