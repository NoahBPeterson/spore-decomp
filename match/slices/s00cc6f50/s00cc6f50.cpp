// Slice s00cc6f50 (0x00cc6f50..0x00cc7ea0): SP::cNpcTribeController::GetStatString,
// the npc-tribe "rebuild resource object list" helper, the SP::cReservationGrid
// grid-resolution maths and the eastl fixed_vector_map growth helpers that share
// this retail region.
//
//  - 00cc6f50  SP::cNpcTribeController::GetStatString
//  - 00cc6fc0  SP::cNpcTribeController::RebuildResourceObjects
//  - 00cc7080  SP::cReservationGrid::RCoordFromPos
//  - 00cc7240  SP::cReservationGrid::ComputeGridSpread
//  - 00cc7830  SP::cReservationGrid::ComputeGridResolution
//  - 00cc78f0  SP::cReservationGrid::PosFromRCoord
//  - 00cc79d0  SP::cReservationGrid::GetClosestInRVector
//  - 00cc7aa0  eastl::vector<pair<u32,cReservedSpot>>::DoInsertValue (grow/middle)
//  - 00cc7c50  SP::cReservationGrid::~cReservationGrid
//  - 00cc7c90  eastl::vector<pair<u32,cReservedSpot>>::insert
//  - 00cc7d20  eastl::vector<pair<u32,cReservedSpot>>::DoAssignFromIterator
//  - 00cc7e10  SP::cReservationGrid::cReservationGrid
//  - 00cc7e60  eastl fixed_vector_map::erase(key)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   s32;
typedef signed   __int64 s64;
typedef wchar_t        wchar;

struct random_access_iterator_tag {};

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void  operator_delete(void* p);                        // 0x00f47380
void* operator_new_eastl(u32 n, const char* pName, u32 a, u32 b, const char* pFile, u32 line); // 0x00f473a0

// lib_eatext byte copy helpers (bodies live in another translation unit; addresses masked)
void* Copy3D(void* first, void* last, void* result);            // 0x00720250
void* Copy3DBackward(void* first, void* last, void* result);    // 0x00cc8b50
void* memcpy(void* dst, const void* src, u32 n);                // 0x011e0744
void* UninitCopy20200(void* first, void* last, void* dst);      // 0x00720200
void  UninitCopyDual(void* dst, void* first, void* last, void* result); // 0x00720d70
void* LowerBoundPairs(void* first, void* last, const u32* key, bool compare); // 0x00612db0

// cNpcTribeController basic_string<wchar_t> (mpBegin/mpEnd/mpCapacity)
struct cTribeString {
    wchar* mpBegin;    // +0x00
    wchar* mpEnd;      // +0x04
    wchar* mpCapacity; // +0x08
    u32    mPad0c;     // +0x0c
    void sprintf(const wchar* fmt, ...);   // 0x0041e050
};

// SP::cNpcTribeController -- retail layout (from sibling slice s00cc4fa0)
struct cGonzagoTimer { u8 mData[0x20]; };
struct cTimerMap     { u8 mData[0x1c]; };

template <class T>
struct SpVec {
    T* mpBegin;    // +0x00
    T* mpEnd;      // +0x04
    T* mpCapacity; // +0x08

    void DoInsertKey4(T* pEnd, const T& value);   // 0x00b96600

    void clear()
    {
        memcpy(mpBegin, mpEnd, 0);
        mpEnd -= (mpEnd - mpBegin);
    }
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
        {
            *mpEnd = v;
            ++mpEnd;
        }
        else
        {
            DoInsertKey4(mpEnd, v);
        }
    }
};

struct ResKey { u32 mPad; u32 mCount; u32 mID; };   // 0x0c resource key

struct cNpcTribeController {
    u8              mPad00[0x10];           // +0x00 vfptr + bases
    cGonzagoTimer   mGrowthUpdateTimer;     // +0x10
    cGonzagoTimer   mGrowthEventTimer;      // +0x30
    cTribeString    mStatusString;          // +0x50
    cTimerMap       mBabyGrowthTimers;      // +0x60
    SpVec<ResKey>   mHerdPoints;            // +0x7c
    u8              mPad88[0x48];           // +0x88
    SpVec<u32>      mResourceObjects;       // +0xd0

    const wchar* GetStatString(int type);   // 0x00cc6f50
    void RebuildResourceObjects();          // 0x00cc6fc0
};

// the "Num Tribes: %d" game-data vector
struct cGameDataVector {
    u32   mCount;    // +0x00
    u32*  mpBegin;   // +0x04
    u32*  mpEnd;     // +0x08
};

struct cGameNounManager {
    cGameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d,
                                       const char* pszName);   // 0x00b21340
};

cGameNounManager* NounManager();                        // 0x00b3d300
void ValidateAllTribes();                               // 0x00cc5f80

struct cSPEditorSpeciesManager {
    void* GetProfile(const ResKey& key);                // 0x004df550
};
cSPEditorSpeciesManager* SpeciesManager();              // 0x00401090

// SPVector<u32>::DoInsertKey4 is a member of SpVec (declared in the template).

// ===========================================================================
// @ 0x00cc6f50
// ===========================================================================
const wchar* cNpcTribeController::GetStatString(int type)
{
    if (type == 2)
        return L"NPCTribe Controller";
    if (type == 0)
    {
        cGameDataVector* pVector = NounManager()->GetGameDataVector(
            (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00accbb0,
            (void*)0x00b1e500, (const char*)0x018c6d19);
        int nCount = (int)(pVector->mpEnd - pVector->mpBegin);
        mStatusString.sprintf(L"Num Tribes: %d", nCount);
    }
    return mStatusString.mpBegin;
}

// ===========================================================================
// @ 0x00cc6fc0
// ===========================================================================
void cNpcTribeController::RebuildResourceObjects()
{
    cSPEditorSpeciesManager* pManager = SpeciesManager();

    // clear the SPVector<u32> of resource objects (erase(begin,end) -> memcpy of 0 bytes)
    u32* pDst = mResourceObjects.mpBegin;
    u32* pSrc = mResourceObjects.mpEnd;
    memcpy(pDst, pSrc, 0);
    mResourceObjects.mpEnd += -(((int)pSrc - (int)pDst) >> 2) * 4;

    int iVar2 = (int)(mHerdPoints.mpEnd - mHerdPoints.mpBegin);
    if (iVar2 != 0)
    {
        int iVar3 = 0;
        do
        {
            u32 profile = (u32)pManager->GetProfile(*(ResKey*)((char*)mHerdPoints.mpBegin + iVar3));
            u32* puVar1 = mResourceObjects.mpEnd;
            if (puVar1 < mResourceObjects.mpCapacity)
            {
                mResourceObjects.mpEnd = puVar1 + 1;
                if (puVar1 != 0)
                    *puVar1 = profile;
            }
            else
            {
                mResourceObjects.DoInsertKey4(puVar1, profile);
            }
            iVar3 += 12;
            --iVar2;
        } while (iVar2 != 0);
    }
    ValidateAllTribes();
}

// ---------------------------------------------------------------------------
// SP::cReservationGrid -- retail layout (map at grid+0x8, map at grid+0x984)
// ---------------------------------------------------------------------------
struct cVector3 {
    float x, y, z;   // +0x00, +0x04, +0x08
    float& operator[](int i) { return (&x)[i]; }
};

struct cReservedSpot {
    u32  mX;            // +0x00
    u32  mY;            // +0x04
    u32  mZ;            // +0x08
    u32  mID;           // +0x0c
    bool mbReserved;    // +0x10
    bool mbHasCitizen;  // +0x11
    u8   mPad12[2];     // +0x12
    cReservedSpot() { mID = 0; mbReserved = false; mbHasCitizen = false; }
};

struct ReservedPair {
    u32           mKey;   // +0x00
    cReservedSpot mSpot;  // +0x04
    ReservedPair() {}
    ReservedPair(u32 key) { mKey = key; }
};

// eastl fixed_vector_map<u32, cReservedSpot, 100, 1, less<u32>>
struct ReservedMap {
    ReservedPair* mpBegin;    // +0x000
    ReservedPair* mpEnd;      // +0x004
    ReservedPair* mpCapacity; // +0x008
    u32           mPad0c;     // +0x00c
    ReservedPair* mpInline;   // +0x010
    u32           mPad14;     // +0x014
    u8            mInline[0x960]; // +0x018 inline storage
    bool          mCompare;   // +0x978
    u8            mPadTail[3];// +0x979

    ReservedMap()
    {
        ReservedPair* p = (ReservedPair*)mInline;
        mpInline = p;
        mpEnd = p;
        mpBegin = p;
        mpCapacity = p + 100;
    }

    ReservedPair* insert(ReservedPair* pos, const ReservedPair& v);       // 0x00cc7c90
    bool          eraseKey(const u32& key);                               // 0x00cc7e60
    void          DoInsertValueGrow(ReservedPair* pos, const ReservedPair& v); // 0x00cc7aa0
    ReservedPair* DoAssignFromIterator(ReservedPair* first, ReservedPair* last, random_access_iterator_tag); // 0x00cc7d20
    ReservedPair* DoReallocateFromIterator(u32 n, ReservedPair* first, random_access_iterator_tag); // 0x00cc7bf0
};

struct cReservationGrid {
    u32         mGridRes;        // +0x000
    float       mSquareSize;     // +0x004
    ReservedMap mReservedSpots;  // +0x008
    ReservedMap mKeepClearSpots; // +0x984
    float       mGridMax;        // +0x1300
    float       mGridMin;        // +0x1304
    float       mGridAvg;        // +0x1308

    u32   RCoordFromPos(cVector3 pos);                              // 0x00cc7080
    float ComputeGridSpread(float& a, float& b, float& c, u32 res); // 0x00cc7240
    float ComputeGridResolution(float a, float b);                  // 0x00cc7830
    void  PosFromRCoord(cVector3& out, u32 rcoord);                 // 0x00cc78f0
    u32   GetClosestInRVector(const ReservedMap& map, cVector3 pos); // 0x00cc79d0
    ~cReservationGrid();                                            // 0x00cc7c50
    cReservationGrid();                                             // 0x00cc7e10
};

extern const u8    kFaceAxis[];  // 0x01476a40  face -> xyz component index table
extern const float kHalf;        // 0x01471064 = 0.5f
extern const float kTwo;         // 0x01470f1c = 2.0f
extern const float kOne;         // 0x01485720 = 1.0f
extern const float kZero;        // 0x01485378 = 0.0f
extern const float kPiOver2;     // 0x0157eba0 = 1.5707964f
extern const float kThirty;      // 0x014853bc = 30.0f
extern const float kEps;         // 0x013ec4b8 = 1e-8f
extern const float kThree;       // 0x013eb95c = 3.0f
extern const float kNegZero;     // 0x013eb8b0 = -0.0f
extern const float kHugeDist;    // 0x01476a5c = 1e7f

struct cPlanetModel {
    float GetWaterHeight();                                                 // 0x00b7e390
    void  DirectionToSurfacePosition(const cVector3& dir, cVector3& out);   // 0x00b815a0
};
cPlanetModel* PlanetModel();  // 0x00b3d350

template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
inline s64 RoundToInt64(float f)
{
    __declspec(align(8)) s64 result;
    __asm { fld  f
            fistp result }
    return result;
}

// ===========================================================================
// @ 0x00cc7080
// ===========================================================================
u32 cReservationGrid::RCoordFromPos(cVector3 pos)
{
    u32 res = mGridRes;
    float fRes = (float)(int)res;
    float fHalf = fRes * 0.5f;
    float f0 = pos.x;
    float f1 = pos.y;
    float f2 = pos.z;
    float a0 = (f0 < 0.0f) ? -f0 : f0;
    float a1 = (f1 < 0.0f) ? -f1 : f1;
    float a2 = (f2 < 0.0f) ? -f2 : f2;

    u32 uX;
    u32 uY;
    int face;
    if (a2 >= a0 && a2 >= a1)
    {
        uX = (u32)((f0 / f2 + 1.0f) * fHalf);
        uY = (u32)((f1 / a2 + 1.0f) * fHalf);
        face = (f2 < 0.0f) ? 1 : 0;
    }
    else if (a0 >= a1)
    {
        uX = (u32)((f1 / f0 + 1.0f) * fHalf);
        uY = (u32)((f2 / a0 + 1.0f) * fHalf);
        face = (f0 < 0.0f) ? 3 : 2;
    }
    else
    {
        uX = (u32)((f2 / f1 + 1.0f) * fHalf);
        uY = (u32)((f0 / a1 + 1.0f) * fHalf);
        face = (f1 < 0.0f) ? 5 : 4;
    }

    if (uX == res)
        --uX;
    if (uY == res)
        --uY;

    return ((uX & 0x1fff) + face * 0x2000) * 0x10000 + (uY & 0xffff);
}

// ===========================================================================
// @ 0x00cc78f0
// ===========================================================================
void cReservationGrid::PosFromRCoord(cVector3& out, u32 rcoord)
{
    float inv = 1.0f / (float)(int)mGridRes;
    float f1 = ((float)(rcoord & 0xffff) + 0.5f) * inv * 2.0f - 1.0f;
    float f2 = ((float)((rcoord >> 16) & 0x1fff) + 0.5f) * inv * 2.0f - 1.0f;
    float s = 1.0f / (float)sqrt((double)(f2 * f2 + f1 * f1 + 1.0f));
    float negs = (rcoord & 0x20000000u) ? -s : s;
    const u8* axis = kFaceAxis + ((rcoord >> 30) * 4);
    out[axis[0]] = negs * f2;
    out[axis[1]] = s * f1;
    out[axis[2]] = negs;
}

// ===========================================================================
// @ 0x00cc79d0
// ===========================================================================
u32 cReservationGrid::GetClosestInRVector(const ReservedMap& map, cVector3 pos)
{
    ReservedPair* it  = map.mpBegin;
    ReservedPair* end = map.mpEnd;
    u32 bestKey = 0xffffffffu;
    float best = kHugeDist;
    if (it == end)
        return bestKey;
    do
    {
        u32 key = it->mKey;
        cVector3 v;
        PosFromRCoord(v, key);
        cVector3 surface;
        PlanetModel()->DirectionToSurfacePosition(v, surface);
        float dx = surface.x - pos.x;
        float dy = surface.y - pos.y;
        float dz = surface.z - pos.z;
        float d = (dz * dz + dy * dy) + dx * dx;
        if (d < best)
        {
            best = d;
            bestKey = key;
        }
        it += 1;
    } while (it != end);
    return bestKey;
}

// ---------------------------------------------------------------------------
// grid-spread sample helpers (inlined by the original)
// ---------------------------------------------------------------------------
static __forceinline cVector3 GridSample(float u, float v, float inv)
{
    float a = u * inv * 2.0f - 1.0f;
    float b = v * inv * 2.0f - 1.0f;
    float s = 1.0f / (float)sqrt((double)(a * a + b * b + 1.0f));
    float a2 = a * s;
    float b2 = b * s;
    float n = 1.0f / (float)sqrt((double)((a2 * a2 + b2 * b2) + s * s + 1e-8f));
    cVector3 r;
    r.x = a2 * n;
    r.y = b2 * n;
    r.z = s * n;
    return r;
}

static __forceinline float SampleDist(const cVector3& p, const cVector3& q, float h)
{
    float dx = p.x * h - q.x * h;
    float dy = p.y * h - q.y * h;
    float dz = p.z * h - q.z * h;
    return (float)sqrt((double)(dx * dx + (dy * dy + dz * dz)));
}

// ===========================================================================
// @ 0x00cc7240
// ===========================================================================
float cReservationGrid::ComputeGridSpread(float& outMin, float& outMax, float& outAvg, u32 res)
{
    u32 r = res ? res : mGridRes;
    float h = PlanetModel()->GetWaterHeight();
    float inv = 1.0f / (float)(int)r;

    float d0 = SampleDist(GridSample(0.5f, 0.5f, inv), GridSample(1.5f, 0.5f, inv), h);
    outMax = d0;
    outMin = d0;

    float u1 = (float)(mGridRes - 1) + 0.5f;
    float u2 = (float)(mGridRes - 2) + 0.5f;
    float d1 = SampleDist(GridSample(u1, u1, inv), GridSample(u1, u2, inv), h);
    if (outMax < d1)
        outMax = d1;
    if (d1 < outMin)
        outMin = d1;

    float c = (float)(mGridRes >> 1) + 0.5f;
    float d2 = SampleDist(GridSample(c, c, inv), GridSample(c + 1.0f, c, inv), h);
    if (outMax < d2)
        outMax = d2;
    if (d2 < outMin)
        outMin = d2;

    outAvg = (d2 + d0) * 0.5f;
    return outAvg;
}

// ===========================================================================
// @ 0x00cc7830
// ===========================================================================
float cReservationGrid::ComputeGridResolution(float a, float b)
{
    float fWater = (b < 1.0f) ? (PlanetModel()->GetWaterHeight() + 30.0f) : b;
    if (a < 0.5f)
        a = 0.5f;
    float fRes = (1.5707963705062866f * fWater) / a;
    s64 lRes = RoundToInt64(fRes);
    u32 nRes = (u32)lRes;
    mGridRes = Min(nRes, 0x80u);
    ComputeGridSpread(mGridMin, mGridMax, mGridAvg, 0);
    return fRes;
}

// ===========================================================================
// @ 0x00cc7c50
// ===========================================================================
cReservationGrid::~cReservationGrid()
{
    if (mKeepClearSpots.mpBegin && mKeepClearSpots.mpBegin != mKeepClearSpots.mpInline)
        operator_delete(mKeepClearSpots.mpBegin);
    if (mReservedSpots.mpBegin && mReservedSpots.mpBegin != mReservedSpots.mpInline)
        operator_delete(mReservedSpots.mpBegin);
}

// ===========================================================================
// @ 0x00cc7e10
// ===========================================================================
cReservationGrid::cReservationGrid() : mGridRes(500)
{
}

// ===========================================================================
// @ 0x00cc7aa0  eastl::vector<pair<u32,cReservedSpot>>::DoInsertValue
// ===========================================================================
void ReservedMap::DoInsertValueGrow(ReservedPair* pos, const ReservedPair& value)
{
    if (mpEnd != mpCapacity)
    {
        const ReservedPair* pValue = &value;
        if (pValue >= pos && pValue < mpEnd)
            pValue += 1;
        if (mpEnd)
            *mpEnd = mpEnd[-1];
        Copy3DBackward(pos, mpEnd - 1, mpEnd);
        *pos = *pValue;
        mpEnd += 1;
        return;
    }

    u32 n = (u32)(mpEnd - mpBegin);
    u32 cap = n ? n * 2 : 1;
    ReservedPair* newBuf = (ReservedPair*)operator_new_eastl(
        cap * 24, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    ReservedPair* pNew = (ReservedPair*)UninitCopy20200(mpBegin, pos, newBuf);
    if (pNew)
        *pNew = value;
    pNew = (ReservedPair*)UninitCopy20200(pos, mpEnd, pNew + 1);
    if (mpBegin && mpBegin != mpInline)
        operator_delete(mpBegin);
    mpBegin = newBuf;
    mpEnd = pNew;
    mpCapacity = newBuf + cap;
}

// ===========================================================================
// @ 0x00cc7c90  eastl::vector<pair<u32,cReservedSpot>>::insert
// ===========================================================================
ReservedPair* ReservedMap::insert(ReservedPair* pos, const ReservedPair& value)
{
    u32 index = (u32)(pos - mpBegin);
    ReservedPair* end = mpEnd;
    if (pos == end && end != mpCapacity)
    {
        mpEnd = end + 1;
        if (end)
            *end = value;
    }
    else
    {
        DoInsertValueGrow(pos, value);
    }
    return mpBegin + index;
}

// ===========================================================================
// @ 0x00cc7d20  eastl::vector<pair<u32,cReservedSpot>>::DoAssignFromIterator
// ===========================================================================
ReservedPair* ReservedMap::DoAssignFromIterator(ReservedPair* first, ReservedPair* last, random_access_iterator_tag tag)
{
    u32 n = (u32)(last - first);
    if ((u32)(mpCapacity - mpBegin) < n)
    {
        ReservedPair* pNew = DoReallocateFromIterator(n, first, tag);
        if (mpBegin && mpBegin != mpInline)
            operator_delete(mpBegin);
        ReservedPair* e = pNew + n;
        mpBegin = pNew;
        mpEnd = e;
        mpCapacity = e;
        return e;
    }

    u32 cur = (u32)(mpEnd - mpBegin);
    if (n <= cur)
    {
        mpEnd = (ReservedPair*)Copy3D(first, last, mpBegin);
        return mpEnd;
    }
    ReservedPair* mid = first + cur;
    Copy3D(first, mid, mpBegin);
    UninitCopyDual(&mpEnd, mid, last, mpEnd);
    return mpEnd;
}

// ===========================================================================
// @ 0x00cc7e60  eastl fixed_vector_map::erase(key)
// ===========================================================================
bool ReservedMap::eraseKey(const u32& key)
{
    ReservedPair* last = mpEnd;
    ReservedPair* it = (ReservedPair*)LowerBoundPairs(mpBegin, last, &key, mCompare);
    if (it == last || key < it->mKey || it == it + 1)
        it = last;
    if (it == last)
        return false;
    if (it + 1 < last)
        Copy3D(it + 1, last, it);
    mpEnd -= 1;
    return true;
}
