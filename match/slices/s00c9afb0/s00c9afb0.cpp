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
struct Quaternion { float x, y, z, w; };
struct Matrix33   { float m[9]; };

struct PlanetModelT {
    int     ClassifyPoint(const Vector3* dir);                               // 0x00b82fc0 (ret 4)
    Vector3 SurfacePoint(const Vector3& dir);                                // 0x00b81630 (ret 8, sret)
    bool    IsWaterPoint(const Vector3* pos);                                // 0x00b7e3e0 (ret 4)
    Quaternion BuildSurfaceOrientation(const Vector3& pos);                  // 0x00b7f190 (ret 4, sret)
};
PlanetModelT* __cdecl PlanetModel();                                         // 0x00b3d350
struct GameTimeMgr { uint64_t GetTime(); };                                  // 0x00b316c0
GameTimeMgr* __cdecl GameTimeManager();                                      // 0x00b3d380
struct cSPTimer {
    bool     IsRunning();                                                    // 0x00feba90
    void     Start();                                                        // 0x00bc30f0
    void     Restart();                                                      // 0x00bc3130
    uint64_t GetElapsedTime();                                               // 0x00bc3190
};
extern cSPTimer g_FishTimer;                                                 // 0x016953f8
extern uint64_t g_NextFishTime;                                              // 0x01695368
extern Vector3  g_FishTarget;                                                // 0x01695374 (last water test point)

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

// =====================================================================================
// Engine layout shared by the tribe-hut / food-material cluster.  Offsets are taken from
// the retail disassembly; the base classes are modelled so MSVC emits the same base
// constructor calls and vtable-pointer stores as the original.
// =====================================================================================

// ---- primary ref-counted base -------------------------------------------------------
struct RefCounted {
    virtual int   AddRef();                 // +0x00
    virtual void  Release();                // +0x04
    virtual void  r08();                    // +0x08
    virtual void  r0c();                    // +0x0c
    virtual void  r10();                    // +0x10
    virtual void  r14();                    // +0x14
    virtual void  r18();                    // +0x18
    virtual void  r1c();                    // +0x1c
    virtual void  r20();                    // +0x20
    virtual void  r24();                    // +0x24
    virtual void  r28();                    // +0x28
    virtual void* GetPosition();            // +0x2c
    virtual void  r30();                    // +0x30
    virtual void  r34();                    // +0x34
    virtual void  r38();                    // +0x38
    virtual void  r3c();                    // +0x3c
    virtual void  r40();                    // +0x40
    virtual void  r44();                    // +0x44
    virtual void  r48();                    // +0x48
    virtual void  r4c();                    // +0x4c
    virtual void  r50();                    // +0x50
    virtual void  r54();                    // +0x54
    virtual void* v58();                    // +0x58
    virtual void* v5c(void* out);           // +0x5c
    virtual void  v60();                    // +0x60
};

// Secondary polymorphic base carried at cGameData+4.
struct SimSerializable {
    virtual void  w00();
    virtual void  w04();
    virtual void  w08();
    virtual void  w0c();
};

// ---- game data (0x34 bytes: two vtables + 0x2c payload) -----------------------------
struct cGameData : RefCounted, SimSerializable {
    cGameData();                                        // 0x00b18660
    ~cGameData();                                       // 0x00b184c0
    bool  IsDestroyed(void* ctx);                       // 0x00bfd0d0
    bool  Write(void* io);                              // 0x00b18590
    void  SetGameDataOwner2(void* owner);               // 0x00b18550
    void* Cast(int type);                               // 0x00b18460
    void  Func80();                                     // 0x00c88510
    void  TribalEvent(int arg);                         // 0x00c9be90
    char  mData[0x34 - 8];
};

// ---- small in-place vtable object (spatial sub-object at +0xec) ---------------------
struct CompactObj {
    virtual void  k00();                    // +0x00
    virtual void  k04();                    // +0x04
    virtual void  k08();                    // +0x08
    virtual void  k0c();                    // +0x0c
    virtual void  k10();                    // +0x10
    virtual void  k14();                    // +0x14
    virtual void  k18(float value, int id); // +0x18
    virtual void  k1c();                    // +0x1c
    virtual void  k20();                    // +0x20
    virtual void  k24();                    // +0x24
    virtual void  k28();                    // +0x28
    virtual void* k2c();                    // +0x2c
    char mTail[0x18];                       // total 0x1c
};

// ---- spatial object (0xd4 bytes standalone; embedded at outer+0x34) -----------------
struct cSpatialObject {
    virtual void s00();
    cSpatialObject();                                   // 0x00c89630
    ~cSpatialObject();                                  // 0x00c8a420
    void  SetLocalExtents(void* ext, float radius);     // 0x00c89160
    void* Cast(int type);                               // 0x00c884f0
    bool  Write(void* io);                              // 0x00c88a90
    void  func80h();                                    // 0x00c88510
    void  func54h(void* a);                             // 0x00c88670
    void  func58h(void* a);                             // 0x00c886d0
    void  OnExtentsChanged(void* a, float b);           // 0x00c9be50

    char      mPad004[0x50];                            // +0x004
    int       mMaterialType;                            // +0x054 (abs +0x088)
    char      mPad058[0x38];                            // +0x058
    uint32_t  mModelInstance;                           // +0x090 (abs +0x0c4)
    uint32_t  mPad094;                                  // +0x094
    uint32_t  mModelGroup;                              // +0x098 (abs +0x0cc)
    char      mPad09c[8];                               // +0x09c
    void*     mpTribe;                                  // +0x0a4 (abs +0x0d8)
    char      mPad0a8[0x10];                            // +0x0a8
    CompactObj mSub;                                    // +0x0b8 (abs +0x0ec)
};

// ---- interaction target (0x18 bytes) ------------------------------------------------
struct cInteractionTarget {
    virtual void i00();
    cInteractionTarget();                               // 0x00ac03d0
    ~cInteractionTarget();                              // 0x00ac0520
    void* Cast(int type);                               // 0x00ac0320
    char  mData[0x14];
};

// ---- combatant (0xc8 bytes) ---------------------------------------------------------
struct cCombatant {
    virtual void c00();
    cCombatant();                                       // 0x00bfd4e0
    ~cCombatant();                                      // 0x00bfcd00
    void* Cast(int type);                               // 0x00bfc380
    float mf04;                                         // +0x004 (abs +0x124)
    char  mData[0xc0];
};

// ---- ref-counted smart pointer used for the two hut fields at +0x230/+0x234 --------
template <class T>
struct RefPtr {
    T* p;
    RefPtr() : p(0) {}
    ~RefPtr() { if (p) ((RefCounted*)p)->Release(); }
};

// ---- food material -----------------------------------------------------------------
struct cTribeFoodMat : cGameData, cSpatialObject {
    cTribeFoodMat();                                    // 0x00c9ba80
    virtual ~cTribeFoodMat();                           // 0x00c9bda0 (scalar deleting)
    void SetOwner(void* owner);                         // 0x00c9bb80
    bool Write(void* io);                               // 0x00c9bc00
    bool IsPlayerTribe();                               // 0x00c9bd30
    void Func54h(void* a);                              // 0x00c9bd50
    bool  mFlag108;                                     // +0x108
    char  mPad109[3];
    RefPtr<RefCounted> mpOwner10c;                      // +0x10c
};

struct cGonzagoTimer {
    cGonzagoTimer();                                    // 0x00b63890
    ~cGonzagoTimer();                                   // 0x00b638b0
    char mData[0x10];
};

// ---- tribe hut ---------------------------------------------------------------------
struct cTribeHut : cGameData, cSpatialObject, cInteractionTarget, cCombatant {
    cTribeHut();                                        // 0x00c9bf90
    virtual ~cTribeHut();                               // 0x00c9c120
    void* Cast(int type);                               // 0x00c9bdf0
    void  SetRefCountDelta(char on);                    // 0x00c9bef0
    void  UpdateEmpireColor();                          // 0x00c9bf30

    void* mpModel1e8;                                   // +0x1e8
    void* mpModel1ec;                                   // +0x1ec
    void* mpModel1f0;                                   // +0x1f0
    void* mpModel1f4;                                   // +0x1f4
    void* mpModel1f8;                                   // +0x1f8
    void* mpModel1fc;                                   // +0x1fc
    void* mpModel200;                                   // +0x200
    void* mpModel204;                                   // +0x204
    void* mpModel208;                                   // +0x208
    void* mpModel20c;                                   // +0x20c
    void* mpModel210;                                   // +0x210
    void* mpModel214;                                   // +0x214
    bool  mFlag218;                                     // +0x218
    char  mPad219[3];
    void* mp218;                                        // +0x21c
    bool  mFlag220;                                     // +0x220
    bool  mFlag221;                                     // +0x221
    char  mPad222[2];
    char  mPad224[4];
    void* mp228;                                        // +0x228
    void* mp22c;                                        // +0x22c
    RefPtr<RefCounted> mpTribe230;                      // +0x230
    RefPtr<RefCounted> mpHitSphere234;                  // +0x234
    int   mRef238;                                      // +0x238
    char  mPad23c[4];
    cGonzagoTimer mTimer;                               // +0x240
};

// ---- effect / manager interfaces ---------------------------------------------------
struct XformMsg {
    uint16_t mFlags;            // +0x00
    uint16_t mCount;            // +0x02
    float    mX, mY, mZ;        // +0x04
    char     mPad10[0xc];       // +0x10
    float    mMatrix[9];        // +0x1c
    XformMsg();                                         // 0x00434040
};

struct EffectObj {
    virtual void  f00();                    // +0x00
    virtual void  f04();                    // +0x04
    virtual void  f08(int on);              // +0x08
    virtual void  f0c();                    // +0x0c
    virtual void  f10();                    // +0x10
    virtual void  f14();                    // +0x14
    virtual void  f18(XformMsg* msg);       // +0x18
    virtual void  f1c();                    // +0x1c
    virtual void  f20();                    // +0x20
    virtual void  f24();                    // +0x24
    virtual void  f28();                    // +0x28
    virtual void  f2c();                    // +0x2c
    virtual void  f30(int on);              // +0x30
    virtual void  f34();                    // +0x34
    virtual bool  f38();                    // +0x38
    virtual void  f3c();                    // +0x3c
    virtual void  f40();                    // +0x40
    virtual void  f44(int type, float* value, int flag);   // +0x44
};

struct EffectsMgr {
    virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
    virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
    virtual void g20(); virtual void g24(); virtual void g28();
    virtual bool CreateEffect(int id, int a, EffectObj** out);   // +0x2c
};

struct EventMgr {
    virtual void h00(); virtual void h04(); virtual void h08(); virtual void h0c();
    virtual void h10(); virtual void h14(); virtual void h18(); virtual void h1c();
    virtual void h20(); virtual void h24(); virtual void h28(); virtual void h2c();
    virtual void h30(); virtual void h34(); virtual void h38(); virtual void h3c();
    virtual void h40(); virtual void h44(); virtual void h48(); virtual void h4c();
    virtual void h50(); virtual void h54(); virtual void h58(); virtual void h5c();
    virtual void h60(int id, void* a, void* b);                   // +0x60
};

struct NounMgr {
    void* GetGameDataVector(int a, int b, int c, int d, int e);  // 0x00b21340
    void* GetPlayerTribe();                                      // 0x00bfc5f0
};

struct IOStream {
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual void s0c(); virtual void s10(); virtual void s14();
    virtual void* GetBuffer();                                   // +0x18
};

struct IODevice {
    virtual void d00(); virtual void d04(); virtual void d08(); virtual void d0c();
    virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void* GetStream();                                   // +0x20
};

struct cVarListSerializer {
    cVarListSerializer(void* owner, void* props, int id);        // 0x00692f90
    bool Serialize(void* io);                                    // 0x00692900
    char mData[0xa14];
};

struct TribeVector {
    void*  mPad0;           // +0
    void** mpBegin;         // +4
    void** mpEnd;           // +8
};

// ---- free functions used by the cluster --------------------------------------------
void  __cdecl FUN_00c9ae30(uint32_t key, float amount);          // 0x00c9ae30
void* __cdecl GetCurrentGameMode();                              // 0x00b5b800
extern uint8_t g_TribeGameMode;                                  // 0x01654c02
NounMgr* __cdecl NounManager();                                  // 0x00b3d300
EffectsMgr* __cdecl EffectsManagerPtr();                         // 0x0067ddd0
EventMgr* __cdecl FUN_00b3d240();                                // 0x00b3d240
int   __stdcall GetPlayerEmpireID(int a, void* b, int c);       // 0x01021090
uint32_t __cdecl FNVHash(const char* str, uint32_t basis, int mode);   // 0x00932e80
Matrix33& __cdecl Matrix3FromQuaternion(Matrix33& out, const Quaternion& q);  // 0x0059c190
void  __cdecl WriteUint32(void* stream, uint32_t* value, int count, int flag);  // 0x0093aa70
extern void* g_01699998;                                         // 0x01699998
extern void* g_TribeCullExtents;                                 // 0x0157c3b4
extern void* g_TribeFoodProps;                                   // 0x0157c320

namespace SP {

class cTribe { public:
    static uint32_t SetupHotSpot(const Vector3& dir, int force = 0);
    const Vector3* GetClosestWater();                            // 0x00c8fe20
    void func54h(void* a);                                       // 0x00c88670
    bool IsPlayerTribe();                                        // 0x00c9bd30
    void HandleEvent(void* a);                                   // 0x00c9bd50
    char mPad000[0xd8];
    void* mpTribeD8;                                             // +0x0d8
    char mPad0dc[0x120 - 0x0dc];
    CompactObj mSub120;                                          // +0x120
};

// @ 0x00C9AFB0
uint32_t cTribe::SetupHotSpot(const Vector3& dir, int force)
{
    (void)force;
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

// =====================================================================================
// Functions added for slice s00c9afb0: tribe fishing, hut and food-material cluster.
// =====================================================================================

struct TribeObj { void Notify(int id); };                                // 0x00c987b0

// @ 0x00c9b6d0
void __cdecl FUN_00c9b6d0(SP::cTribe* self)
{
    if (!self)
        return;
    if (!g_FishTimer.IsRunning())
        return;
    const Vector3* p = self->GetClosestWater();
    if (p->x != g_FishTarget.x || p->y != g_FishTarget.y || p->z != g_FishTarget.z)
        SP::cTribe::SetupHotSpot(*p, 1);
}

// @ 0x00c9b740
void __cdecl FUN_00c9b740(float dt)
{
    if (!g_FishTimer.IsRunning()) {
        uint32_t found = 0xffffffff;
        if (PlanetModel()) {
            NounMgr* nm = NounManager();
            TribeVector* v = (TribeVector*)nm->GetGameDataVector(
                0x00cd7d10, 0x00d3d420, 0x00accbb0, 0x00b1e500, 0x018c6d19);
            void** it = v->mpBegin;
            if (it != v->mpEnd) {
                do {
                    SP::cTribe* t = (SP::cTribe*)*it;
                    t->mSub120.k2c();
                    const Vector3* p = t->GetClosestWater();
                    if (p->x != g_FishTarget.x || p->y != g_FishTarget.y ||
                        p->z != g_FishTarget.z)
                        found = SP::cTribe::SetupHotSpot(*p, 1);
                    ++it;
                } while (it != v->mpEnd);
                if (found != 0xffffffff)
                    return;
            }
        }
        g_FishTimer.Restart();
        g_NextFishTime = g_FishTimer.GetElapsedTime() + 10000;
        return;
    }

    uint64_t now = g_FishTimer.GetElapsedTime();
    if (now > g_NextFishTime) {
        g_NextFishTime = g_FishTimer.GetElapsedTime() + 240000;
        return;
    }

    HotSpotElem* it = g_HotSpots.mpBegin;
    HotSpotElem* const end = g_HotSpots.mpEnd;
    if (it == end)
        return;
    for (; it != end; ++it) {
        HotSpot& s = it->value;
        if (!s.mbActive)
            continue;
        FUN_00c9ae30(it->key, s.mResupply * dt);
        if (GetCurrentGameMode() != &g_TribeGameMode)
            continue;
        if (!s.mpOrnament) {
            Vector3 surface = PlanetModel()->SurfacePoint(s.mPos);
            EffectsMgr* em = EffectsManagerPtr();
            if (s.mpOrnament) {                 // always null here; kept for fidelity
                IRef* old = s.mpOrnament;
                s.mpOrnament = 0;
                old->Release();
            }
            if (em->CreateEffect(0x89c75e7f, 0, (EffectObj**)&s.mpOrnament)) {
                XformMsg msg;
                msg.mFlags |= 4;
                ++msg.mCount;
                msg.mX = surface.x;
                msg.mY = surface.y;
                msg.mZ = surface.z;
                Matrix33 mat;
                Matrix3FromQuaternion(mat, PlanetModel()->BuildSurfaceOrientation(surface));
                for (int i = 0; i < 9; ++i)
                    msg.mMatrix[i] = mat.m[i];
                msg.mFlags |= 2;
                ++msg.mCount;
                ((EffectObj*)s.mpOrnament)->f18(&msg);
                ((EffectObj*)s.mpOrnament)->f08(0);
            }
        }
        if (s.mpOrnament) {
            float ratio = s.mFood / s.mMaxFood;
            float value = (ratio > 0.0f) ? ratio : 0.0f;
            ((EffectObj*)s.mpOrnament)->f44(3, &value, 1);
        }
        if (!s.mbRemove) {
            if (((EffectObj*)s.mpOrnament)->f38())
                ((EffectObj*)s.mpOrnament)->f30(0);
        } else {
            if (!((EffectObj*)s.mpOrnament)->f38())
                ((EffectObj*)s.mpOrnament)->f30(1);
        }
    }
}

// @ 0x00c9ba80
cTribeFoodMat::cTribeFoodMat()
{
    mFlag108 = true;
    mMaterialType = 2;
    mModelInstance = FNVHash("trg_sacrifice_altar1", 0x811c9dc5, 1);
    mModelGroup = FNVHash("TribalTools", 0x811c9dc5, 1);
}

// @ 0x00c9bb80
void cTribeFoodMat::SetOwner(void* owner)
{
    SetGameDataOwner2(owner);
    void* old = mpOwner10c.p;
    if (owner != old) {
        if (owner)
            ((RefCounted*)owner)->AddRef();
        mpOwner10c.p = (RefCounted*)owner;
        if (old)
            ((RefCounted*)old)->Release();
    }
}

// @ 0x00c9bc00
bool cTribeFoodMat::Write(void* io)
{
    void* buf = ((IOStream*)((IODevice*)io)->GetStream())->GetBuffer();
    uint32_t value = 0x0629baec;
    WriteUint32(buf, &value, 1, 0);
    bool ok;
    if (cGameData::Write(io) && ((cSpatialObject*)((char*)this + 0x34))->Write(io))
        ok = true;
    else
        ok = false;
    cVarListSerializer ser(this, &g_TribeFoodProps, 0x1a80d26);
    bool result = ok && ser.Serialize(io);
    return result;
}

// @ 0x00c9bd30
bool SP::cTribe::IsPlayerTribe()
{
    void* tribe = mpTribeD8;
    return NounManager()->GetPlayerTribe() == tribe;
}

// @ 0x00c9bd50
void SP::cTribe::HandleEvent(void* a)
{
    func54h(a);
    ((TribeObj*)mpTribeD8)->Notify(0xd);
}

// @ 0x00c9bda0
cTribeFoodMat::~cTribeFoodMat()
{
}

// @ 0x00c9bdf0
void* cTribeHut::Cast(int type)
{
    if (type == 0x00ee02c7)
        return this;
    void* r = cGameData::Cast(type);
    if (r)
        return r;
    r = ((cCombatant*)((char*)this + 0x120))->Cast(type);
    if (r)
        return r;
    r = ((cInteractionTarget*)((char*)this + 0x108))->Cast(type);
    if (r)
        return r;
    return ((cSpatialObject*)((char*)this + 0x34))->Cast(type);
}

// @ 0x00c9be50
void cSpatialObject::OnExtentsChanged(void* a, float b)
{
    SetLocalExtents(a, b);
    RefCounted* outer = (RefCounted*)((char*)this - 0x34);
    void* r = outer->v58();
    if (r)
        ((TribeObj*)r)->Notify(0xc);
}

// @ 0x00c9be90
void cGameData::TribalEvent(int arg)
{
    IsDestroyed((void*)arg);
    char local[12];
    FUN_00b3d240()->h60(0x498ef27,
        ((RefCounted*)((char*)this - 0xec))->GetPosition(),
        ((RefCounted*)((char*)this - 0xec))->v5c(local));
}

// @ 0x00c9bef0
void cTribeHut::SetRefCountDelta(char on)
{
    if (on)
        ++mRef238;
    else
        --mRef238;
}

// @ 0x00c9bf30
void cTribeHut::UpdateEmpireColor()
{
    cGameData::Func80();
    if (GetCurrentGameMode() == &g_TribeGameMode)
        return;
    const Vector3* pos = (const Vector3*)GetPosition();
    if (!PlanetModel()->IsWaterPoint(pos))
        return;
    mSub.k18(mf04, GetPlayerEmpireID(0, &g_01699998, 0));
}

// @ 0x00c9bf90
cTribeHut::cTribeHut()
    : mpModel1e8(0), mpModel1ec(0), mpModel1f0(0), mpModel1f4(0),
      mpModel1f8(0), mpModel1fc(0), mpModel200(0), mpModel204(0),
      mpModel208(0), mpModel20c(0), mpModel210(0), mpModel214(0),
      mFlag218(false), mp218(0), mFlag220(false), mFlag221(false),
      mp228(0), mp22c(0), mRef238(0)
{
    ((cSpatialObject*)this)->func58h(&g_TribeCullExtents);
}

// @ 0x00c9c120
cTribeHut::~cTribeHut()
{
}
