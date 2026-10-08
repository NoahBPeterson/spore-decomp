// Slice s00c9afb0 -- SP::cTribe::SetupHotSpot (0x00C9AFB0, 1810 bytes).
// Tribe-mode module: /O2 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc.
//
// Picks a fishing hot spot for the tribe stage.  The view direction is mapped onto the cube-map
// face it hits (six faces, major axis + sign), converted to a cube-map cell, and the 8x8 block of
// cells around it is scanned:
//   * a cell that already holds a hot spot (global sorted map at 0x157abb0) ends the scan, its
//     start time is refreshed and its key is returned;
//   * otherwise the cell centre is projected to a unit direction and, when the planet model
//     classifies the point as water (3), its surface position is remembered.
// With no existing hot spot but a water cell found, a new hot spot is built from two tuning
// properties (food 15.0 default, resupply 0.05 default), stored in the map and given a 10.0
// radius area.  Finally the fish timer is (re)started and the next-spawn delay is set to 240000.
// Member and type names are Claude-coined; layouts come from the retail disassembly.
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);

void __cdecl operator_delete__(void* p);                                   // 0x00f47380

struct Vector3 { float x, y, z; };
struct CubeIndex { int x, y, face; };
struct CubeCoord { float u, v; int face; };

CubeIndex* __cdecl CoordToIndex(CubeIndex* out, int res, const CubeCoord* in);   // 0x00684bf0
CubeCoord* __cdecl IndexToCoord(CubeCoord* out, int res, const CubeIndex* in);   // 0x00684c50
void __cdecl WrapCubeFace(int res, int* face, int* x, int* y, int a, int b);     // 0x00684ca0

extern const uint8_t kFaceAxes[3][4];                                            // 0x01473bc0

// ---------------------------------------------------------------- property list
struct Property {
    void*    mpData;       // +0x00
    uint32_t pad04[3];
    uint16_t mnFlags;      // +0x10
    uint16_t mnType;       // +0x12
};
struct PropertyList {
    virtual int  AddRef();
    virtual int  Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& prop);                      // +0x24
};
extern PropertyList* g_pTribeTuning;                                             // 0x0158128c
extern float g_DefaultFloat;                                                     // 0x015d9c6c

struct IRef { virtual void v0(); virtual void Release(); };

// ---------------------------------------------------------------- hot spot
struct HotSpot {
    Vector3   mPos;          // +0x00
    float     mFood;         // +0x0c
    float     mMaxFood;      // +0x10
    float     mResupply;     // +0x14
    CubeIndex mCube;         // +0x18
    IRef*     mpEffect;      // +0x24
    IRef*     mpHitSphere;   // +0x28
    uint32_t  pad2c;
    uint64_t  mStartTime;    // +0x30
    bool      mbActive;      // +0x38
    bool      mbRemove;      // +0x39
    IRef*     mpOrnament;    // +0x3c
    void*     mpArray;       // +0x40
    uint32_t  pad44, pad48, pad4c;

    HotSpot()
        : mFood(30.0f), mMaxFood(30.0f), mResupply(0.0f), mpEffect(0), mpHitSphere(0),
          mStartTime(0), mbActive(false), mbRemove(false), mpOrnament(0), mpArray(0)
    {
        pad44 = 0; pad48 = 0; pad4c = 0;
        mPos.x = 0; mPos.y = 0; mPos.z = 0;
    }
    ~HotSpot()
    {
        if (mpArray && ((int*)mpArray)[-1] != 0)
            operator_delete__(mpArray);
        if (mpOrnament) mpOrnament->Release();
        if (mpHitSphere) mpHitSphere->Release();
        if (mpEffect) mpEffect->Release();
    }
    void Assign(const HotSpot& o);                       // 0x00c95010 (ret 4)
    void SetupArea(const Vector3& pos, float radius);    // 0x00c91030 (ret 8)
};

struct HotSpotElem { uint32_t key; uint32_t pad; HotSpot value; };   // stride 0x60
struct HotSpotMap {
    HotSpotElem* mpBegin;      // +0
    HotSpotElem* mpEnd;        // +4
    uint32_t     pad[0x3040 / 4 - 2];   // up to the flag at +0xc18 (kept symbolic below)
};
extern HotSpotMap g_HotSpots;                                                // 0x0157abb0
extern uint8_t g_HotSpotsFlag;                                               // 0x0157b7c8
HotSpotElem* __cdecl HotSpotLowerBound(HotSpotElem* first, HotSpotElem* last, const uint32_t* key, uint8_t flag);   // 0x00c92d50

struct HotSpotMapRef {
    HotSpot* at(const uint32_t* key);                                        // 0x00c9aa10 (thiscall, ret 4)
};

// ---------------------------------------------------------------- planet / time / timer
struct PlanetModelT {
    int     ClassifyPoint(const Vector3* dir);                               // 0x00b82fc0 (ret 4)
    Vector3 SurfacePoint(const Vector3& dir);                                // 0x00b81630 (ret 8, sret)
};
PlanetModelT* __cdecl PlanetModel();                                         // 0x00b3d350
struct GameTimeMgr { uint64_t GetTime(); };                                  // 0x00b316c0
GameTimeMgr* __cdecl GameTimeManager();                                      // 0x00b3d380
struct cSPTimer {
    bool     IsRunning();                                                    // 0x00feba90
    void     Start();                                                        // 0x00bc30f0
    uint64_t GetElapsedTime();                                               // 0x00bc3190
};
extern cSPTimer g_FishTimer;                                                 // 0x016953f8
extern uint64_t g_NextFishTime;                                              // 0x01695368

inline float ReadFloatProperty(uint32_t id, float def)
{
    Property* p;
    if (g_pTribeTuning && g_pTribeTuning->GetProperty(id, p)) {
        uint16_t t = p->mnType;
        if (t == 0xd || t == 0x10) {
            if (p->mnFlags & 0x30)
                return **(float**)p;
            return *(float*)(t ? (void*)p : (void*)0);
        }
        return g_DefaultFloat;
    }
    return def;
}

namespace SP {

struct cTribe {
    static uint32_t SetupHotSpot(const Vector3& dir);
};

// @ 0x00C9AFB0
uint32_t cTribe::SetupHotSpot(const Vector3& dir)
{
    float x = dir.x, y = dir.y, z = dir.z;
    float ax = (float)fabs(x), ay = (float)fabs(y), az = (float)fabs(z);
    CubeCoord coord;
    if (ax > az || ay > az) {
        if (ax > ay) {
            coord.u = (y / x + 1.0f) * 0.5f;
            coord.v = (z / ax + 1.0f) * 0.5f;
            coord.face = 2;
            if (x < 0.0f) coord.face = 3;
        } else {
            coord.u = (z / y + 1.0f) * 0.5f;
            coord.v = (x / ay + 1.0f) * 0.5f;
            if (y < 0.0f) coord.face = 5;
            else coord.face = 4;
        }
    } else {
        coord.u = (x / z + 1.0f) * 0.5f;
        coord.v = (y / az + 1.0f) * 0.5f;
        if (z < 0.0f) coord.face = 1;
        else coord.face = 0;
    }

    CubeIndex idx;
    CoordToIndex(&idx, 0x80, &coord);
    int xStart = idx.x - 4, xEnd = idx.x + 4;
    int yStart = idx.y - 4, yEnd = idx.y + 4;

    HotSpot spot;
    bool bFound = false;
    bool bWater = false;
    uint32_t result = 0xffffffff;
    Vector3 d;
    uint64_t now = GameTimeManager()->GetTime();

    for (int i = xStart; i < xEnd; ++i) {
        if (bFound) goto done;
        for (int j = yStart; j < yEnd; ++j) {
            if (bFound) break;
            int face = idx.face, wx = i, wy = j;
            WrapCubeFace(0x80, &face, &wx, &wy, 0, 0);
            CubeIndex cell;
            cell.x = wx; cell.y = wy; cell.face = face;
            uint32_t key = (((wx & 0xffff8fff) + (face << 13)) << 16) + wy;
            HotSpotElem* it = HotSpotLowerBound(g_HotSpots.mpBegin, g_HotSpots.mpEnd, &key, g_HotSpotsFlag);
            if (it != g_HotSpots.mpEnd && key >= it->key) {
                bFound = true;
                result = key;
                d = ((HotSpotMapRef*)&g_HotSpots)->at(&key)->mPos;
                ((HotSpotMapRef*)&g_HotSpots)->at(&key)->mStartTime = now;
            } else {
                CubeCoord uv;
                IndexToCoord(&uv, 0x80, &cell);
                float up = (float)((double)uv.u * 2.0 - 1.0);
                float vp = (float)((double)uv.v * 2.0 - 1.0);
                float k = (float)(1.0 / sqrt((double)(vp * vp + up * up) + 1.0));
                float kn = (uv.face & 1) ? -k : k;
                const uint8_t* axes = kFaceAxes[uv.face >> 1];
                float* dv = &d.x;
                dv[axes[0]] = kn * up;
                dv[axes[1]] = k * vp;
                dv[axes[2]] = kn;
                if (PlanetModel()->ClassifyPoint(&d) == 3) {
                    spot.mCube = cell;
                    spot.mPos = PlanetModel()->SurfacePoint(d);
                    bWater = true;
                }
            }
        }
    }
    if (!bFound && bWater) {
        float food = ReadFloatProperty(0xd1e9eaf0, 15.0f);
        float resupply = ReadFloatProperty(0x3c8e6fb2, 0.05f);
        spot.mbActive = true;
        float v = (food > 1.0f) ? food : 1.0f;
        spot.mFood = v;
        spot.mMaxFood = v;
        spot.mResupply = resupply;
        result = (((spot.mCube.x & 0xffff8fff) + (spot.mCube.face << 13)) << 16) + spot.mCube.y;
        spot.mStartTime = now;
        ((HotSpotMapRef*)&g_HotSpots)->at(&result)->Assign(spot);
        ((HotSpotMapRef*)&g_HotSpots)->at(&result)->SetupArea(spot.mPos, 10.0f);
    }
done:
    if (!g_FishTimer.IsRunning()) {
        g_FishTimer.Start();
        g_NextFishTime = 240000;
    } else {
        g_NextFishTime = g_FishTimer.GetElapsedTime() + 240000;
    }
    return result;
}

}  // namespace SP
