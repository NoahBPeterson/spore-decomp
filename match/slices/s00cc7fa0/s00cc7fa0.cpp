// SP::cReservationGrid reserved-spot maps (eastl::fixed_vector_map) and the
// SP::cTribeDisplayStrategy helpers that share this retail region
// (0x00cc7fa0..0x00cc8be0).
//
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-

#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// eastl map plumbing (bodies live elsewhere; addresses masked)
// ---------------------------------------------------------------------------

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

// fixed_vector_map<unsigned, cReservedSpot, 100, 1, less<unsigned> >
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

// fixed_vector_map<unsigned, cReservedSpot, 121, 1, less<unsigned> >
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

// @ 0x00cc7fa0
void __stdcall FilterRCluster(Map121* dst, const Map100* src) {
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
cReservedSpot& Map100::Get(const u32& key) {
    ReservedPair* last = mpEnd;
    ReservedPair* it = LowerBound(mpBegin, last, &key, mCompare);
    if (it == last || key < it->mKey)
        it = insert(it, ReservedPair(key, cReservedSpot()));
    return it->mSpot;
}

// @ 0x00cc80c0
cReservedSpot& Map121::Get(const u32& key) {
    ReservedPair* last = mpEnd;
    ReservedPair* it = LowerBound(mpBegin, last, &key, mCompare);
    if (it == last || key < it->mKey)
        it = insert(it, ReservedPair(key, cReservedSpot()));
    return it->mSpot;
}

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

// @ 0x00cc8140
bool cReservationGrid::ReserveRCoord(u32 rcoord) {
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

// ---------------------------------------------------------------------------
// external game helpers / objects
// ---------------------------------------------------------------------------

void* FUN_0067de00(); // 0x0067de00

struct ModelInstanceSet {
    u8 mData[0x60];
    void AddToRenderer(void* p); // 0x006f3df0
    void ReleaseIf();            // 0x006f33d0
};

struct CameraCtl {
    u8 mPad00[0x14]; // +0x00
    u8 m14;          // +0x14
    u8 m15;          // +0x15
    u8 m16;          // +0x16
    u8 m17;          // +0x17

    bool FUN_00cc87f0();
    bool FUN_00cc8810();
};

struct EntityRef {
    u32 FUN_00c22dc0(); // 0x00c22dc0
};

struct Profile8a30 {
    u8 mPad00[0x504];
    u32 m504; // +0x504
    u32 m508; // +0x508
    u32 m50c; // +0x50c
};

struct Citizen8a30 {
    void* GetTribe(int zero); // 0x00c22f50
};

struct Tribe8a30 {
    Profile8a30* GetSlot0(); // 0x00c8e820
};

struct Setting8a30 {
    Profile8a30* GetAvatarProfile(); // 0x004df420
};

Setting8a30* GetSetting9(); // 0x00401090

struct BuffWriter {
    void* GetBuffer(); // 0x0093b6c0
};

struct ModeView {
    u8 mPad00[0x4c];
    BuffWriter* m4C; // +0x04c
};

struct ModeStrategy {
    static ModeStrategy* Instance(); // 0x00cd40b0
};

struct GlobalUI8aa0 {
    void* FindWindowByID(u32 id); // 0x00e012b0
};

struct Vec3u {
    u32 x;
    u32 y;
    u32 z;
};

struct TribeStrategy {
    u8 mPad00[0x08];        // +0x000
    void* mChild[6];        // +0x008
    u8 mPad20[0x4c - 0x20]; // +0x020
    GlobalUI8aa0* m4C;      // +0x04c
    u8 mPad50[0x88 - 0x50]; // +0x050
    Vec3u mVec;             // +0x088
    u8 mPad94[0xb8 - 0x94]; // +0x094
    ModelInstanceSet mInst[2]; // +0x0b8
    u32 mArray178[0x28];    // +0x178
    u32 mArray218[0x28];    // +0x218

    u32 FUN_00cc88e0(u32 key);                // 0x00cc88e0
    void FUN_00cc8940(bool add);              // 0x00cc8940
    u32 FUN_00cc89f0(bool first);             // 0x00cc89f0
    void FUN_00cc8a30(void* pose, Citizen8a30* citizen); // 0x00cc8a30
    void FUN_00cc8aa0(bool show);             // 0x00cc8aa0
    void FUN_00cc8ba0();                      // 0x00cc8ba0
};

// generic virtual dispatch (the vtable is never part of the object layout here)
template <class R>
inline R V0(void* o, int off) {
    return ((R(__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
template <class R, class A>
inline R V1(void* o, int off, A a) {
    return ((R(__thiscall*)(void*, A))(*(void***)o)[off / 4])(o, a);
}
template <class R, class A, class B>
inline R V2(void* o, int off, A a, B b) {
    return ((R(__thiscall*)(void*, A, B))(*(void***)o)[off / 4])(o, a, b);
}

// @ 0x00cc8670
void cReservationGrid::GetRCluster(void* position, Map121* cluster, u32 face) {
    u32 rcoord = RCoordFromPos(position);
    GetRClusterByCoord(rcoord, cluster, face);
}

// @ 0x00cc87f0
bool CameraCtl::FUN_00cc87f0() {
    return m14 || m15;
}

// @ 0x00cc8810
bool CameraCtl::FUN_00cc8810() {
    return m17 || m16;
}

// @ 0x00cc8830
void* FUN_00cc8830(EntityRef* ref) {
    void* result = (void*)0xb;
    if (ref) {
        switch (ref->FUN_00c22dc0()) {
        case 0: result = (void*)10; break;
        case 1: result = (void*)3; break;
        case 2: result = (void*)2; break;
        case 3: result = (void*)4; break;
        case 4: result = (void*)5; break;
        case 5: result = (void*)6; break;
        case 6: result = (void*)7; break;
        case 7: result = (void*)8; break;
        case 8: result = (void*)9; break;
        case 9: result = (void*)1; break;
        case 11: result = (void*)0; break;
        default: break;
        }
    }
    return result;
}

// @ 0x00cc88e0
u32 TribeStrategy::FUN_00cc88e0(u32 key) {
    switch (key) {
    case 11: return 0;
    case 1:
    case 2:
    case 3:
    case 9: return 2;
    case 4:
    case 5:
    case 6: return 1;
    case 7:
    case 8: return 3;
    default: return 4;
    }
}

// @ 0x00cc8940
void TribeStrategy::FUN_00cc8940(bool add) {
    ModelInstanceSet* p = mInst;
    if (add) {
        for (int n = 2; n != 0; ++p, --n)
            p->AddToRenderer(FUN_0067de00());
    } else {
        for (int n = 2; n != 0; ++p, --n)
            p->ReleaseIf();
    }
}

// @ 0x00cc8990
void* FUN_00cc8990() {
    ModeStrategy* inst = ModeStrategy::Instance();
    ModeView* view = (ModeView*)V0<void*>(inst, 0x6c);
    return view->m4C->GetBuffer();
}

// @ 0x00cc89f0
u32 TribeStrategy::FUN_00cc89f0(bool first) {
    u32 best = 0xffffffff;
    int bestValue = 0x7fffffff;
    u32* p = first ? mArray178 : mArray218;
    for (u32 i = 0; i < 0x28; ++i) {
        int v = (int)p[i];
        if (v <= 0)
            return i;
        if (v < bestValue) {
            bestValue = v;
            best = i;
        }
    }
    return best;
}

// @ 0x00cc8a30
void TribeStrategy::FUN_00cc8a30(void* pose, Citizen8a30* citizen) {
    Tribe8a30* tribe = (Tribe8a30*)citizen->GetTribe(0);
    Profile8a30* profile = tribe->GetSlot0();
    if (!profile)
        profile = GetSetting9()->GetAvatarProfile();
    mVec.x = profile->m504;
    mVec.y = profile->m508;
    mVec.z = profile->m50c;
    mVec.y = 0x2f7d0004;
    V2<void, Vec3u*, int>(pose, 0x90, &mVec, 0);
}

// @ 0x00cc8aa0
void TribeStrategy::FUN_00cc8aa0(bool show) {
    if (!m4C)
        return;
    void* w = m4C->FindWindowByID(0x6454b47);
    if (w) V2<void, int, bool>(w, 0x7c, 1, show);
    w = m4C->FindWindowByID(0x652a628);
    if (w) V2<void, int, bool>(w, 0x7c, 1, show);
    w = m4C->FindWindowByID(0x44827b8);
    if (w) V2<void, int, bool>(w, 0x7c, 1, !show);
}

// @ 0x00cc8ba0
void TribeStrategy::FUN_00cc8ba0() {
    void** p = mChild;
    for (int i = 0; i < 6; ++i, ++p) {
        if (*p) {
            V0<void>(*p, 0x88);
            if (*p) {
                void* old = *p;
                *p = 0;
                V0<void>(old, 0x04);
            }
        }
    }
}
