// Reservation grid: two fixed-capacity sorted maps of reserved cube-map spots.
// `Get` returns the existing entry for a key, inserting a default one when absent;
// `FilterRCluster` drops from `dst` every key present in `src`.

#include "game/types.h"

typedef unsigned int u32;
typedef unsigned char u8;
// A spot on the reservation grid: the cube-map cell (mX/mY/mZ are the header's
// cCubeMapIndex mCol/mRow/mFace) plus the reserving id and two flags.
struct cReservedSpot {
    u32 mX;            // +0x00  cube-map column
    u32 mY;            // +0x04  cube-map row
    u32 mZ;            // +0x08  cube-map face
    u32 mID;           // +0x0c  id of the reserver, 0 = none
    bool mbReserved;   // +0x10
    bool mbHasCitizen; // +0x11
    u8 mPad12[2];      // +0x12  tail padding to 0x14

    cReservedSpot() {
        mID = 0;
        mbReserved = false;
        mbHasCitizen = false;
    }
};
// One (key, spot) entry of a fixed-capacity sorted map.
struct ReservedPair {
    u32 mKey;           // +0x00
    cReservedSpot mSpot; // +0x04

    ReservedPair() {}
    ReservedPair(u32 key, const cReservedSpot& spot) : mKey(key), mSpot(spot) {}
};
struct Map100;
struct Map121;
ReservedPair* LowerBound(ReservedPair* first, ReservedPair* last, const u32* key, bool compare); // 0x00612db0
void CopyVertex3D(void* first, void* last, void* result);                                         // 0x00720250

// Backing store of a `spstl::fixed_vector_map<unsigned int, cReservedSpot, N, 1>`: an inline
// array of pairs with a comparator flag. Map100 holds 100 entries, Map121 holds 121.
struct Map100 {
    ReservedPair* mpBegin; // +0x000
    ReservedPair* mpEnd;   // +0x004  one past the last live pair
    u32 mPad08[0x25c];     // +0x008  inline pair storage (100 * 0x14 bytes)
    bool mCompare;         // +0x978  eastl::less comparator state
    u8 mPadTail[3];        // +0x979

    cReservedSpot& Get(const u32& key);
    ReservedPair* find(const u32& key);
    ReservedPair* insert(ReservedPair* pos, const ReservedPair& value); // 0x00cc7ed0
};
struct Map121 {
    ReservedPair* mpBegin; // +0x000
    ReservedPair* mpEnd;   // +0x004  one past the last live pair
    u32 mPad08[0x2da];     // +0x008  inline pair storage (121 * 0x14 bytes)
    bool mCompare;         // +0xb70  eastl::less comparator state
    u8 mPadTail[3];        // +0xb71

    cReservedSpot& Get(const u32& key);
    ReservedPair* find(const u32& key);
    ReservedPair* insert(ReservedPair* pos, const ReservedPair& value); // 0x00cc7f30
    void erase(ReservedPair* it);
    void clear();
};

// The grid's two reservation maps (kept clear / reserved) plus the resolution statistics.
struct cReservationGrid {
    u32 mGridRes;           // +0x000
    float mSquareSize;      // +0x004
    Map100 mReservedSpots;  // +0x008
    Map100 mKeepClearSpots; // +0x984
    float mGridMax;         // +0x1300
    float mGridMin;         // +0x1304
    float mGridAvg;         // +0x1308

    bool ReserveRCoord(u32 rcoord);                           // 0x00cc8140
    u32 RCoordFromPos(void* position);                        // 0x00cc7080
    void GetRClusterByCoord(u32 rcoord, Map121* cluster, u32 face); // 0x00cc81f0
    void GetRCluster(void* position, Map121* cluster, u32 face); // 0x00cc8670
};
// Return the entry for `key`, or mpEnd when absent.
ReservedPair* Map100::find(const u32& key) {
    ReservedPair* last = mpEnd;
    ReservedPair* it = LowerBound(mpBegin, last, &key, mCompare);
    return (it == last || key < it->mKey) ? last : it;
}
ReservedPair* Map121::find(const u32& key) {
    ReservedPair* last = mpEnd;
    ReservedPair* it = LowerBound(mpBegin, last, &key, mCompare);
    return (it == last || key < it->mKey) ? last : it;
}
// Shift the tail down over `it` and shrink the map by one.
void Map121::erase(ReservedPair* it) {
    if (it + 1 < mpEnd)
        CopyVertex3D(it + 1, mpEnd, it);
    mpEnd -= 1;
}
// Drop every live entry.
void Map121::clear() {
    ReservedPair* first = mpBegin;
    ReservedPair* last = mpEnd;
    CopyVertex3D(last, mpEnd, first);
    mpEnd -= last - first;
}

// @ 0x00cc7fa0
void __stdcall FilterRCluster(Map121* dst, const Map100* src)
{
    ReservedPair* p = src->mpBegin;
    ReservedPair* const srcEnd = src->mpEnd;
    while (p != srcEnd) {
        u32 key = p->mKey;
        if (dst->find(key) != dst->mpEnd)
            dst->erase(dst->find(key));
        ++p;
    }
}

// @ 0x00cc8040
cReservedSpot& Map100::Get(const u32& key)
{
    ReservedPair* end = mpEnd;
    ReservedPair* it = LowerBound(mpBegin, end, &key, mCompare);
    if (it == end || key < it->mKey)
        it = insert(it, ReservedPair(key, cReservedSpot()));
    return it->mSpot;
}

// @ 0x00cc80c0
cReservedSpot& Map121::Get(const u32& key)
{
    ReservedPair* end = mpEnd;
    ReservedPair* it = LowerBound(mpBegin, end, &key, mCompare);
    if (it == end || key < it->mKey)
        it = insert(it, ReservedPair(key, cReservedSpot()));
    return it->mSpot;
}

// @ 0x00cc8140
bool cReservationGrid::ReserveRCoord(u32 rcoord)
{
    u32 key = rcoord;
    if (mReservedSpots.find(key) == mReservedSpots.mpEnd) {
        cReservedSpot spot;
        spot.mX = (rcoord >> 16) & 0x1fff;
        spot.mY = rcoord & 0xffff;
        spot.mZ = rcoord >> 29;
        spot.mID = 0;
        mReservedSpots.Get(rcoord) = spot;
        return true;
    }
    return false;
}

// @ 0x00cc8670
void cReservationGrid::GetRCluster(void* position, Map121* cluster, u32 face)
{
    u32 rcoord = RCoordFromPos(position);
    GetRClusterByCoord(rcoord, cluster, face);
}
