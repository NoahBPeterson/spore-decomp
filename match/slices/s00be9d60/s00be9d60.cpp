// Slice s00be9d60: the single function in this slice is
//   0x00BE9D60  SP::cCity::UpdateLanes  (3021 bytes, __thiscall, no args)
//   (name from the 2008 dev PDB: SP::cCity::UpdateLanes, SPCity.obj; layout from the ModAPI
//    cCity/cCommunity/cCityWalls/cCommunityLayout headers: mLanes (vector<cLaneInfo>) +0x84,
//    cSpatialObject +0x120, mpCityHall +0x320, mpCityWalls +0x324, mBuildings +0x340,
//    building layout +0x3ec; cCityWalls::mInnerRadius +0x258, mBuildingLinks[14][14] +0x274.)
//
// What it does (rebuilds the city's pedestrian lane graph):
//   1. clears mLanes;
//   2. for every building: records its centre and a radius (15 for the city hall, else the
//      footprint radius capped at 8), lays a 6-slot ring around it with a static
//      cCommunityLayout and adds the 6 slot positions as lane points (inside = within the
//      walls' inner radius of the city centre);
//   3. pushes every point out of the other buildings' radius + 8 (4 relaxation passes) and
//      recomputes "inside";
//   4. merges points of later rings that are closer than g_LaneMergeDistance (averaging);
//   5. for every pair of buildings the walls link (mBuildingLinks by layout slot) and that
//      are not already merged, links the closest free point of each ring;
//   6. creates one cLaneInfo per unmerged inside point, then connects each point to its two
//      ring neighbours and its link (no duplicate connections).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as s00be7bf0 cCity::Initialize).
#include "types.h"
#include <math.h>

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) throw() { return p; }
void operator delete[](void* p);                                         // 0x00f47380

namespace SP {

// ---------------------------------------------------------------------------------------
// Math
struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    __forceinline Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    __forceinline Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    __forceinline Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    __forceinline float Length() const { return sqrtf(x * x + y * y + z * z); }
};

template <class T> __forceinline const T& min_alt(const T& a, const T& b) { return (b < a) ? b : a; }

template <class It, class T> __forceinline It find(It first, It last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

// ---------------------------------------------------------------------------------------
// EASTL vector with Spore's sp_vector_allocator (8 bytes; a header word before each block).
struct sp_vector_allocator {
    uint32_t mData[2];
};
__forceinline void SpFree(void* p)
{
    if (((uint32_t*)p)[-1] != 0)
        operator delete[](p);
}

struct UintVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    sp_vector_allocator mAllocator;

    __forceinline UintVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~UintVector() { if (mpBegin) SpFree(mpBegin); }
    void DoInsertValue(uint32_t* position, const uint32_t& value);       // 0x004558a0
    __forceinline void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) uint32_t(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct cLaneInfo {
    Vector3 mPosition;              // +0x0
    UintVector mConnections;        // +0xc
};

cLaneInfo* CopyLanes(cLaneInfo* first, cLaneInfo* last, cLaneInfo* dest);  // 0x00be0e80 (eastl::copy)

struct LaneVector {
    cLaneInfo* mpBegin;
    cLaneInfo* mpEnd;
    cLaneInfo* mpCapacity;
    sp_vector_allocator mAllocator;

    void DestroyValues(cLaneInfo* first, cLaneInfo* last);               // 0x00bdc770
    void DoInsertValue(cLaneInfo* position, const cLaneInfo& value);     // 0x00be7aa0
    __forceinline cLaneInfo* erase(cLaneInfo* first, cLaneInfo* last)
    {
        cLaneInfo* const pNewEnd = CopyLanes(last, mpEnd, first);
        DestroyValues(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    __forceinline void clear() { erase(mpBegin, mpEnd); }
    __forceinline cLaneInfo& push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) cLaneInfo();
        else
            DoInsertValue(mpEnd, cLaneInfo());
        return *(mpEnd - 1);
    }
    __forceinline cLaneInfo& back() { return *(mpEnd - 1); }
};

// ---------------------------------------------------------------------------------------
// Local fixed_vectors (EASTL fixed_vector: begin/end/capacity, overflow allocator,
// mpPoolBegin, then the in-place buffer).
struct LaneCenter {                 // building centre and keep-out radius
    Vector3 mPosition;
    float mRadius;
    __forceinline LaneCenter() {}
};

struct LanePoint {                  // one of the 6 ring points around a building
    Vector3 mPosition;              // +0x0
    int mMergedInto;                // +0xc  index of the point this one was merged into, or -1
    int mLaneIndex;                 // +0x10 index into mLanes
    int mLink;                      // +0x14 linked point of another ring, or -1
    bool mbInside;                  // +0x18 inside the walls' inner radius
    __forceinline LanePoint() {}
};

struct CenterFixedVector {
    LaneCenter* mpBegin;
    LaneCenter* mpEnd;
    LaneCenter* mpCapacity;
    uint32_t mOverflowAllocator;
    void* mpPoolBegin;
    uint32_t mPad;
    LaneCenter mBuffer[32];

    __forceinline CenterFixedVector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 32;
    }
    __forceinline ~CenterFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(LaneCenter* position, const LaneCenter& value);   // 0x00bded00
    __forceinline LaneCenter& push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) LaneCenter();
        else
            DoInsertValue(mpEnd, LaneCenter());
        return *(mpEnd - 1);
    }
};

struct PointFixedVector {
    LanePoint* mpBegin;
    LanePoint* mpEnd;
    LanePoint* mpCapacity;
    uint32_t mOverflowAllocator;
    void* mpPoolBegin;
    uint32_t mPad;
    LanePoint mBuffer[192];

    __forceinline PointFixedVector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 192;
    }
    __forceinline ~PointFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    void DoInsertValue(LanePoint* position, const LanePoint& value);     // 0x00bdee20
    __forceinline LanePoint& push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) LanePoint();
        else
            DoInsertValue(mpEnd, LanePoint());
        return *(mpEnd - 1);
    }
    __forceinline LanePoint& back() { return *(mpEnd - 1); }
};

// ---------------------------------------------------------------------------------------
// Simulator
class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                                // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual Vector3 GetDirection(float f);                               // 0x5c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70();
    virtual float GetFootprintRadius();                                  // 0x74
};

class cBuilding {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88();
    virtual const Vector3& func8Ch();                                    // 0x8c (ModAPI cBuilding)

    uint32_t mGameData[0x34 / 4 - 1];
    cSpatialObject mSpatial;                                             // +0x34
};

class cCityWalls {
public:
    uint32_t pad0[0x258 / 4];
    float mInnerRadius;                                                  // +0x258
    uint32_t pad25c[(0x274 - 0x25c) / 4];
    bool mBuildingLinks[14][14];                                         // +0x274
};

struct cLayoutSlot {
    bool mIsOccupied;
    void* mpObject;
    int field_8;
    Vector3 mPosition;                                                   // +0xc
};

class cCommunityLayout {
public:
    cCommunityLayout();                                                  // 0x00afba10
    ~cCommunityLayout();                                                 // (atexit stub 0x013c31e0)
    void SetCenter(const Vector3& pos, float radius, const Vector3& dir);   // 0x00af9cf0
    void GenerateSlots(float a, float b, int count);                     // 0x00afd6d0
    int GetSlotIndex(cBuilding* object);                                 // 0x00afad30

    uint32_t pad0[0x50 / 4];
    cLayoutSlot* mSlotsBegin;                                            // +0x50 (mSlots.mpBegin)
    uint32_t pad54[(0x64 - 0x54) / 4];
};

extern float g_LaneMergeDistance;    // 0x0156e140 (8.0)
extern float g_LanePushStrength;     // 0x0156e144 (0.2)

class cCity {
public:
    void UpdateLanes();

    uint32_t pad0[0x84 / 4];
    LaneVector mLanes;                                                   // +0x84
    uint32_t pad98[(0x120 - 0x98) / 4];
    cSpatialObject mSpatial;                                             // +0x120
    uint32_t pad124[(0x320 - 0x124) / 4];
    cBuilding* mpCityHall;                                               // +0x320
    cCityWalls* mpCityWalls;                                             // +0x324
    uint32_t pad328[(0x340 - 0x328) / 4];
    cBuilding** mBuildingsBegin;                                         // +0x340 (mBuildings)
    cBuilding** mBuildingsEnd;                                           // +0x344
    uint32_t pad348[(0x3ec - 0x348) / 4];
    cCommunityLayout mBuildingLayout;                                    // +0x3ec
};

__forceinline void AddConnection(UintVector& connections, uint32_t id)
{
    if (find(connections.mpBegin, connections.mpEnd, id) == connections.mpEnd)
        connections.push_back(id);
}

// @ 0x00be9d60
void cCity::UpdateLanes()
{
    mLanes.clear();

    const int numBuildings = (int)(mBuildingsEnd - mBuildingsBegin);
    const int numPoints = numBuildings * 6;

    CenterFixedVector centers;
    PointFixedVector points;

    const float innerRadius = mpCityWalls->mInnerRadius;

    // 2. building centres and their 6-point rings
    for (int i = 0; i < numBuildings; ++i) {
        LaneCenter& center = centers.push_back();
        center.mPosition = mBuildingsBegin[i]->func8Ch();
        if (mBuildingsBegin[i] == mpCityHall)
            center.mRadius = 15.0f;
        else
            center.mRadius = min_alt(mBuildingsBegin[i]->mSpatial.GetFootprintRadius(), 8.0f);

        static cCommunityLayout sLayout;
        sLayout.SetCenter(center.mPosition, center.mRadius, mSpatial.GetDirection(0.0f));
        sLayout.GenerateSlots(1.0f, 1.0f, 6);

        for (int k = 0; k < 6; ++k) {
            points.push_back().mPosition = sLayout.mSlotsBegin[k].mPosition;
            points.back().mMergedInto = -1;
            points.back().mLaneIndex = -1;
            points.back().mLink = -1;
            points.back().mbInside = (sLayout.mSlotsBegin[k].mPosition - mSpatial.GetPosition()).Length() < innerRadius;
        }
    }

    // 3. push the points out of the buildings
    const float pushStrength = g_LanePushStrength;
    for (int pass = 0; pass < 4; ++pass) {
        for (int p = 0; p < numPoints; ++p) {
            const Vector3 pos = points.mpBegin[p].mPosition;
            for (int b = 0; b < numBuildings; ++b) {
                const Vector3 d = pos - centers.mpBegin[b].mPosition;
                const float len = d.Length();
                float depth = len - centers.mpBegin[b].mRadius;
                if (depth < 8.0f) {
                    const Vector3 dir = d * (1.0f / len);
                    if (depth < 1.52587890625e-05f)
                        depth = 0.01f;
                    points.mpBegin[p].mPosition += dir * ((8.0f - depth) * pushStrength);
                }
            }
        }
    }

    for (int p = 0; p < numPoints; ++p)
        points.mpBegin[p].mbInside = (points.mpBegin[p].mPosition - mSpatial.GetPosition()).Length() < innerRadius;

    // 4. merge close points of later rings
    const int numMergeable = numPoints - 6;
    int nextRing = 6;
    const float mergeDistance = g_LaneMergeDistance;
    for (int i = 0; i < numMergeable; ++i) {
        if (points.mpBegin[i].mbInside && points.mpBegin[i].mMergedInto == -1) {
            Vector3 pos = points.mpBegin[i].mPosition;
            for (int j = i + nextRing; j < numPoints; ++j) {
                LanePoint& other = points.mpBegin[j];
                if (other.mbInside && other.mMergedInto == -1) {
                    const Vector3 d = pos - other.mPosition;
                    if (d.Length() < mergeDistance) {
                        other.mMergedInto = i;
                        pos = (other.mPosition + pos) * 0.5f;
                    }
                }
            }
            points.mpBegin[i].mPosition = pos;
        }
        if (nextRing == 1)
            nextRing = 6;
        else
            --nextRing;
    }

    // 5. link the rings of buildings the walls connect
    int slots[14];
    for (int i = 0; i < numBuildings; ++i)
        slots[i] = mBuildingLayout.GetSlotIndex(mBuildingsBegin[i]);

    for (int i = 0; i < numBuildings; ++i) {
        const int iBase = i * 6;
        for (int j = i + 1; j < numBuildings; ++j) {
            const int jBase = j * 6;
            if (!mpCityWalls->mBuildingLinks[slots[i]][slots[j]])
                continue;

            int k;
            for (k = 0; k < 6; ++k) {
                const int merged = points.mpBegin[jBase].mMergedInto;
                if (merged >= iBase && merged < iBase + 6)
                    break;
            }
            if (k != 6)
                continue;

            int bestI = -1;
            int bestJ = -1;
            float bestDistI = 3.4028234663852886e+38f;
            float bestDistJ = 3.4028234663852886e+38f;
            for (int m = 0; m < 6; ++m) {
                const LanePoint& a = points.mpBegin[iBase + m];
                if (a.mbInside && a.mLink == -1) {
                    const float dist = (a.mPosition - centers.mpBegin[j].mPosition).Length();
                    if (dist < bestDistI) {
                        bestDistI = dist;
                        bestI = iBase + m;
                    }
                }
                const LanePoint& b = points.mpBegin[jBase + m];
                if (b.mbInside && b.mLink == -1) {
                    const float dist = (b.mPosition - centers.mpBegin[i].mPosition).Length();
                    if (dist < bestDistJ) {
                        bestDistJ = dist;
                        bestJ = jBase + m;
                    }
                }
            }
            if (bestI != -1 && bestJ != -1) {
                points.mpBegin[bestI].mLink = bestJ;
                points.mpBegin[bestJ].mLink = bestI;
            }
        }
    }

    // 6. one lane per unmerged inside point
    int numLanes = 0;
    for (int p = 0; p < numPoints; ++p) {
        LanePoint& pt = points.mpBegin[p];
        if (pt.mbInside) {
            if (pt.mMergedInto == -1) {
                mLanes.push_back();
                mLanes.back().mPosition = pt.mPosition;
                pt.mLaneIndex = numLanes++;
            } else {
                pt.mLaneIndex = points.mpBegin[pt.mMergedInto].mLaneIndex;
            }
        }
    }

    // connect each point's lane to its ring neighbours and to its link
    int corner = 0;
    for (int p = 0; p < numPoints; ++p) {
        const LanePoint& pt = points.mpBegin[p];
        if (pt.mbInside) {
            cLaneInfo& lane = mLanes.mpBegin[pt.mLaneIndex];
            const LanePoint& next = points.mpBegin[(corner == 5) ? p - 5 : p + 1];
            if (next.mbInside)
                AddConnection(lane.mConnections, next.mLaneIndex);
            const LanePoint& prev = points.mpBegin[(corner == 0) ? p + 5 : p - 1];
            if (prev.mbInside)
                AddConnection(lane.mConnections, prev.mLaneIndex);
            if (pt.mLink != -1)
                AddConnection(lane.mConnections, points.mpBegin[pt.mLink].mLaneIndex);
        }
        if (corner == 5)
            corner = 0;
        else
            ++corner;
    }
}

} // namespace SP
