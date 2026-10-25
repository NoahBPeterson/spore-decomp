// src/game/SPGonzago/SPReservationGrid.cpp -- migrated from slice(s) s00cc7fa0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPReservationGrid.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cReservationGrid.h"

// ---- items of slice s00cc7fa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
struct cReservedSpot {
    u32 mX;            // +0x00
    u32 mY;            // +0x04
    u32 mZ;            // +0x08
    u32 mID;           // +0x0c
    bool mbReserved;   // +0x10
    bool mbHasCitizen; // +0x11
    u8 mPad12[2];      // +0x12

    cReservedSpot() {
        mID = 0;
        mbReserved = false;
        mbHasCitizen = false;
    }
};
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
struct Map100 {
    ReservedPair* mpBegin; // +0x000
    ReservedPair* mpEnd;   // +0x004
    u32 mPad08[0x25c];     // +0x008
    bool mCompare;         // +0x978
    u8 mPadTail[3];        // +0x979

    cReservedSpot& Get(const u32& key);
    ReservedPair* find(const u32& key);
    ReservedPair* insert(ReservedPair* pos, const ReservedPair& value); // 0x00cc7ed0
};
struct Map121 {
    ReservedPair* mpBegin; // +0x000
    ReservedPair* mpEnd;   // +0x004
    u32 mPad08[0x2da];     // +0x008
    bool mCompare;         // +0xb70
    u8 mPadTail[3];        // +0xb71

    cReservedSpot& Get(const u32& key);
    ReservedPair* find(const u32& key);
    ReservedPair* insert(ReservedPair* pos, const ReservedPair& value); // 0x00cc7f30
    void erase(ReservedPair* it);
    void clear();
};
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
void Map121::erase(ReservedPair* it) {
    if (it + 1 < mpEnd)
        CopyVertex3D(it + 1, mpEnd, it);
    mpEnd -= 1;
}
void Map121::clear() {
    ReservedPair* first = mpBegin;
    ReservedPair* last = mpEnd;
    CopyVertex3D(last, mpEnd, first);
    mpEnd -= last - first;
}
// ---- items of slice s00cc7fa0 end

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
    ReservedPair* last = mpEnd;
    ReservedPair* it = LowerBound(mpBegin, last, &key, mCompare);
    if (it == last || key < it->mKey)
        it = insert(it, ReservedPair(key, cReservedSpot()));
    return it->mSpot;
}

// @ 0x00cc80c0
cReservedSpot& Map121::Get(const u32& key)
{
    ReservedPair* last = mpEnd;
    ReservedPair* it = LowerBound(mpBegin, last, &key, mCompare);
    if (it == last || key < it->mKey)
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
