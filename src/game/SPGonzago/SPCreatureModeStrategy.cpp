// src/game/SPGonzago/SPCreatureModeStrategy.cpp -- migrated from slice(s) s01364b20, s00d47630, s00d463a0, s00d425f0, s00d40930, s00d3f9e0, s00d3d870, s00d3b920, s00d3a830, s00d38930, s00d377f0, s00d2dd20, s00b8c330 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureModeStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "SP/cStaticBuffer.h"
#include "SP/cStaticBufferDraw.h"
#include "SP/cTerrainSphere.h"

// unnamed retail callees and globals (address in the comment)
extern const float kColorScale;                      // 0x1465434 = 255.0f
extern int g_16881e8;                                 // 0x16881e8
extern int g_ResourceNodesDirty;                      // 0x16881ec
#include <xmmintrin.h>
#include "SP/cGameNounManager.h"
#include "cSPUILayout.h"
#include "SP/cSPUINewProgressBar.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>
#include "SP/cSPCreatureBase.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cGameData.h"
#include <intrin.h>
#include "cSPTransform.h"
#include "SP/cSpatialObject.h"
#include "SP/cCollectableItems.h"
#include "SP/cPropertyManager.h"
#pragma warning(disable: 4035)
#pragma warning(default: 4035)

// ---- items of slice s00b8c330 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) throw() { return p; }
void __cdecl operator_delete__(void* p);                  // 0xf47380 (operator delete[])
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline bool operator!=(const Vector3& a, const Vector3& b) { return a.x != b.x || a.y != b.y || a.z != b.z; }
namespace SP {
 Vector3 __cdecl normalized_safe(const Vector3& v);   // 0x449c20
}
extern const float kColorScale;                      // 0x1465434 = 255.0f
__forceinline uint8_t UnitToByte(float v)
{
    __asm {
        xorps    xmm0, xmm0
        maxss    xmm0, v
        mulss    xmm0, kColorScale
        minss    xmm0, kColorScale
        cvtss2si eax, xmm0
    }
}
__forceinline uint32_t ToColor(const Vector3& c)
{
    uint8_t r = UnitToByte(c.x);
    uint8_t g = UnitToByte(c.y);
    uint8_t b = UnitToByte(c.z);
    return ((uint32_t)r << 8 | g) << 8 | b;
}
struct random_access_iterator_tag {};
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
    void deallocate(void* p) {
        if (((uint32_t*)p)[-1])
            operator_delete__(p);
    }
};
template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin) mAllocator.deallocate(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }

    T* erase(T* first, T* last);
    void resize(int n);
    SpVector& operator=(const SpVector& x);
    T* insert(T* pos, const T& v);
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct cCurvePoint {          // 0x3c bytes, produced by the route curve builder
    Vector3 mPos;
    uint32_t pad[12];
};
typedef SpVector<Vector3> Vec3Vector;
typedef SpVector<cCurvePoint> CurveVector;
template <> cCurvePoint* CurveVector::erase(cCurvePoint* first, cCurvePoint* last);   // 0xac4570
template <> Vector3* Vec3Vector::erase(Vector3* first, Vector3* last);               // 0x50f740
template <> void Vec3Vector::resize(int n);                                          // 0x473810
template <> Vec3Vector& Vec3Vector::operator=(const Vec3Vector& x);                  // 0x473500
template <> Vector3* Vec3Vector::insert(Vector3* pos, const Vector3& v);             // 0xb85d40
template <> void Vec3Vector::DoInsertValue(Vector3* pos, const Vector3& v);          // 0x4b5ad0
void __cdecl reverse_impl(Vector3* first, Vector3* last, random_access_iterator_tag); // 0xb85570
inline void reverse(Vector3* first, Vector3* last) { reverse_impl(first, last, random_access_iterator_tag()); }
struct cCity_s00b8_c330 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void GetPosition(Vector3* out);          // +0x5c

    const Vector3& GetColor();                       // 0xbd99e0
    const Vector3& GetLocation();                    // 0xfa0e00
    Vector3 GetPlanetCenter();                       // 0xbd9480
};
struct CityPair { cCity_s00b8_c330* first; cCity_s00b8_c330* second; };
struct cLandRoute {           // 0x1c bytes
    cCity_s00b8_c330* city1;
    cCity_s00b8_c330* city2;
    Vec3Vector mPath;
};
struct cStaticBuffer_s00b8_c330 {
virtual void v00();
virtual void v04();
    virtual void Release();                          // +0x08
    void Flush();                                    // 0x7a4710
};
struct cStaticBufferDraw_s00b8_c330 { cStaticBuffer_s00b8_c330* mpBuffer; };
extern cStaticBufferDraw_s00b8_c330* g_StaticBufferDraw;         // 0x15ddc84 (SingletonBase<cStaticBufferDraw>::spInstance)
struct StaticBufferRef {
    cStaticBuffer_s00b8_c330* mpObject;
    void Reset()
    {
        cStaticBuffer_s00b8_c330* p = mpObject;
        if (p) {
            mpObject = 0;
            p->Release();
        }
    }
};
struct cMinimapLayer {
    uint32_t pad00[2];
    StaticBufferRef mBuffer;                         // +0x08

    void Begin();                                    // 0xb7e6c0
    void AddSegment(const Vector3& a, const Vector3& b, uint32_t color);   // 0xb7f920
    void AddCurve(Vec3Vector& pts, uint32_t color);                       // 0xb86a10
    void AddPath(Vec3Vector& pts, uint32_t color);                        // 0xb872c0

    void ReleaseBuffer() { mBuffer.Reset(); }
    void End()
    {
        StaticBufferRef& buf = mBuffer;
        cStaticBufferDraw_s00b8_c330* draw = g_StaticBufferDraw;
        buf.Reset();
        draw->mpBuffer->Flush();
        buf.mpObject = draw->mpBuffer;
        draw->mpBuffer = 0;
    }
};
struct cMinimapGfx {
    uint32_t pad00[11];
    cMinimapLayer* mpLandLayer;   // +0x2c
    cMinimapLayer* mpSeaLayer;    // +0x30
    cMinimapLayer* mpAirLayer;    // +0x34
};
struct cTerrainSphere_s00b8_c330 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual bool IsReady();                          // +0x50
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
    virtual void Update(int a, int b);               // +0x9c
};
struct IGameMode {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual int GetModeID();                         // +0x1c
};
struct IApp {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual IGameMode* GetGameModeManager();         // +0x50
};
namespace SP {
 IApp* __cdecl App();   // 0x67dd10
}
struct cPlanet_s00b8_c330 { float GetTemperature(); };           // 0xc70a20
struct cTerraformTuning { float GetIceThreshold(); }; // 0x1049c40
cPlanet_s00b8_c330* __cdecl GetActivePlanet();                   // 0x1021260
cTerraformTuning* __cdecl TerraformTuning();          // 0x1049a10
struct cCurveParams {         // 20 bytes, copied from a static default
    const char* mpName;
    void* mpA;
    void* mpFunc;
    void* mpB;
    void* mpC;
};
extern cCurveParams g_WaterCurveParams;               // 0x1565b2c ("water", ...)
void __cdecl FUN_00b836b0();                          // curve callback stored into the params
struct cCurveBuilder {
    void Build(const cCurveParams& params, const Vector3& a, const Vector3& b,
               CurveVector& out, float t0, float t1);  // 0xac6960
};
cCurveBuilder* __cdecl GetCurveBuilder();             // 0xb3d290
extern int g_16881e8;                                 // 0x16881e8
extern int g_ResourceNodesDirty;                      // 0x16881ec
extern Vector3 g_InvalidPosition;                     // 0x16881f0
struct cPlanetModel_s00b8_c330 {
    uint32_t pad00[8];
    cTerrainSphere_s00b8_c330* mpSphere;     // +0x20
    cTerrainSphere_s00b8_c330* mpISphere;    // +0x24
    uint32_t pad28[20];
    bool mObstaclesDirty;         // +0x78
    uint8_t pad79[3];
    uint32_t pad7c[11];
    cMinimapGfx* mpMinimapGfx;    // +0xa8
    SpVector<CityPair> mSeaTradeRoutes;   // +0xac
    SpVector<CityPair> mLandTradeRoutes;  // +0xc0 (straight segments)
    SpVector<cLandRoute> mPathRoutes;     // +0xd4
    bool mSeaRoutesDirty;         // +0xe8
    bool mLandRoutesDirty;        // +0xe9
    bool mPathRoutesDirty;        // +0xea
    uint8_t padeb[5];
    bool mIsFrozen;               // +0xf0

    void RebuildObstacles();                              // 0xb87dc0
    void AddResourceNodes();                              // 0xb8bba0
    float GetWaterHeight();                               // 0xb7e390
    Vector3 SnapToSurface(const Vector3& p);              // 0xb81630

    void UpdateMinimap(int arg0, int arg1, int modeOverride);
};
// ---- items of slice s00b8c330 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cStaticBufferDraw_s00b8_c330* g_StaticBufferDraw;         // 0x15ddc84 (SingletonBase<cStaticBufferDraw>::spInstance)
extern cCurveParams g_WaterCurveParams;               // 0x1565b2c ("water", ...)
extern Vector3 g_InvalidPosition;                     // 0x16881f0

// ---- items of slice s00d2dd20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kRealZero;        // 0x01485378  _HK_REAL_ZERO
extern float kTierMaxHeight;   // 0x01582e54  clamp ceiling for mClampedValue
extern char g_01654c10;            // 0x01654c10  "space" game-mode record
#pragma pack(push, 4)
#pragma pack(pop)
struct Vector3_s00d2_dd20 { float x, y, z; };
struct CreatureModeState {
    int           mSelectedIndex;   // +0x00
    float         mZoom;            // +0x04
    float         mViewScale;       // +0x08
    unsigned char mPad0c[0x24 - 0x0c];
    int           mMode;            // +0x24  (set to 1 by the reset)
    float         mClampedValue;    // +0x28
    unsigned char mPad2c[0x38 - 0x2c];
    unsigned int  mFlags38;         // +0x38
    unsigned int  mFlags3c;         // +0x3c
    float         mPrevX;           // +0x44
    float         mPrevY;           // +0x48
    float         mPrevZ;           // +0x4c
};
extern CreatureModeState g_0169e370;   // 0x0169e370
class cAvatar;
class cTerrainSphere {
public:
    unsigned char mPad00[0x10f0];
    float         mHeight;      // +0x10f0
    float         mHeightMax;   // +0x10f4
};
class cGameNounManager {
public:
    cAvatar*        GetAvatar();                     // 0x00b1fdb0
    cTerrainSphere* GetCurrentTerrainSphere();       // 0x00f67d90
};
cGameNounManager* NounManager();                     // 0x00b3d300
class cAvatarMood {
public:
    double FUN_00bfc490();                           // 0x00bfc490  st0 result
    unsigned char mPad00[4];
};
struct AvatarFlagsB58 {
    unsigned int mFlag0  : 1;
    unsigned int mFlag1  : 1;
    unsigned int mFlag2  : 1;
    unsigned int mFlag3  : 1;
    unsigned int mFlag4  : 1;
    unsigned int mFlag5  : 1;
    unsigned int mFlag6  : 1;
    unsigned int mFlag7  : 1;
    unsigned int mFlag8  : 1;
    unsigned int mFlag9  : 1;
    unsigned int mFlag10 : 1;
    unsigned int mFlag11 : 1;
};
class cLocomotive {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const Vector3_s00d2_dd20* GetPosition();            // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual bool FUN_0048();                         // +0x48
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
    virtual double FUN_0074();                       // +0x74  st0 result
};
class cSpeciesData {
public:
    unsigned char mPad00[0x61c];
    int           mMode;         // +0x61c
};
class cAvatar {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cAvatar* FUN_000C(unsigned int id);                                  // 0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
    virtual void v80();                                                              // 0x80
    virtual void FUN_0084(void* arg);                                                // 0x84
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void vA0();
virtual void vA4();
virtual void vA8();
virtual void vAC();
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
    virtual int  FUN_00D8();                                                         // 0xd8

    void*  FUN_00c04590();                            // 0x00c04590
    double FUN_00c0b9c0();                            // 0x00c0b9c0  st0 result
    void*  FUN_00c0ee60(unsigned char slot, int flag);   // 0x00c0ee60
    cAvatar* FUN_00c0ee70();                          // 0x00c0ee70  GetTargetAsCreature
    cAvatar* FUN_00c0ee90();                          // 0x00c0ee90  ApplyCombatTarget
    bool   FUN_00c0b770();                            // 0x00c0b770
    void   FUN_00c1d400(unsigned int id, unsigned int guid);  // 0x00c1d400
    void*  FUN_00c14e70(unsigned int guid);           // 0x00c14e70

    unsigned char  mPad04[0xc0 - 0x04];
    cLocomotive    mLocomotive;  // +0xc0
    unsigned char  mPadC4[0x137 - 0xc4];
    unsigned char  mField137;    // +0x137
    unsigned char  mPad138[0x5a8 - 0x138];
    cAvatarMood    mMood;        // +0x5a8
    unsigned char  mPad5ac[0x5e0 - 0x5ac];
    float          mMadTimer;    // +0x5e0
    unsigned char  mPad5e4[0xb20 - 0x5e4];
    cSpeciesData*  mpSpecies;    // +0xb20
    unsigned char  mPadB24[0xb28 - 0xb24];
    unsigned char  mCombatDataB28[0xb4c - 0xb28];  // +0xb28  handed to the mode helpers
    void*          mpOwnerB4c;   // +0xb4c  object whose +8 owns the avatar
    unsigned char  mPadB50[0xb58 - 0xb50];
    AvatarFlagsB58 mFlagsB58;    // +0xb58
    unsigned char  mSlotB5c;     // +0xb5c
    unsigned char  mFieldB5e;    // +0xb5e
};
class cSub128 {
public:
    void FUN_00d2d560(float value);              // 0x00d2d560
    void FUN_00d2d0b0(int tick);                 // 0x00d2d0b0
};
class cCreatureModeEventSink {
public:
    __declspec(noinline) void Update(float value);   // 0x00d2e2e0  (this file)

    unsigned char mPad00[0x128];
    cSub128       mSub;      // +0x128
};
class cPropertyList;
class cCreatureModeStrategy {
public:
    static cCreatureModeStrategy* Instance();                 // 0x00d38840
    static void NotifyEvent(float amount);                    // 0x00d2e8a0  (this file)
    void FUN_00d39360(unsigned int id, void* data);           // 0x00d39360

    unsigned char           mPad00[0x68];
    cCreatureModeEventSink* mpSink;       // +0x68
    unsigned char           mPad6c[0xb4 - 0x6c];
    cPropertyList*          mpPropList;   // +0xb4
};
void* GetCurrentGameMode();                              // 0x00b5b800
// ---- items of slice s00d2dd20 end

// ---- items of slice s00d377f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl X_NounManager();                      // 0x00b3d300
extern "C" void* __cdecl X_GameInputManager();                 // 0x00b3d250
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef void  (__thiscall *FnV0)(void*);
typedef int   (__thiscall *FnI0)(void*);
typedef void  (__thiscall *FnVIFFI)(void*, int, float, float, int);
static inline void** VTBL(void* p) { return *(void***)p; }
struct NounVec {                           // cGameNounManager::GetGameDataVector result
    u32   mField00;                        // +0x00
    void** mpBegin;                        // +0x04
    void** mpEnd;                          // +0x08
    u32   mField0c;                        // +0x0c
    u32   mField10;                        // +0x10
};
struct cGameNounManager_s00d3_77f0 {
    void*     GetAvatar();                                     // 0x00b1fdb0
    void*     CreateNoun(u32 typeID);                          // 0x00b20c60
    void      RemoveNoun(void* noun);                          // 0x00b225d0
    NounVec*  GetGameDataVector(u32,u32,u32,u32,u32);          // 0x00b21340
};
struct cTerrainEditor {
    void* GetCurrentTerrainSphere();                           // 0x00f67d90
};
struct cTerrainSphere_s00d3_77f0 {
    u32 mField0000;
    u8  mPad0004[0x10e8 - 4];
    void* mpSomething10e8;                 // +0x10e8
    float FUN_c75680(int which);           // 0x00c75680
    void  FUN_c78420(void* event);         // 0x00c78420
    bool  FUN_00594330();                  // 0x00594330
};
class cCreatureLevelUpScenario {
public:
    u32 mPad00[0xa0 / 4];                  // +0x00
    u32 mFieldA0;                          // +0xa0
    bool HasBrainUpgrade();                // 0x00d38880
};
class cCreatureModeStrategy_s00d3_77f0 {
public:
    void OnMouseWheel();                                   // 0x00d38890
    void OnMouseMove(int a, float b, float c, int d);      // 0x00d388a0
    void OnMouseButton(int a, float b, float c, int d);    // 0x00d388d0
};
// ---- items of slice s00d377f0 end

// ---- items of slice s00d38930 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct TTutorialRef {
  int mNoun;                                              // +0x00
  int mUnused04;                                          // +0x04
  int mMagic;                                             // +0x08
};
namespace SP {
struct cSPUIEventLog;
}
namespace SP {
struct cGameNounManager_s00d3_8930;
}
namespace SP {
struct cGameTimeManager;
}
namespace SP {
struct cTriggerMgr;
}
namespace SP {
struct TSphere;
}
namespace SP {
struct cSPCreatureBase_s00d3_8930;
}
namespace SP {
cSPUIEventLog* __stdcall EventLog(int a, int b, int c);   // 0x00b3d3e0
}
namespace SP {
cGameNounManager_s00d3_8930* NounManager_s00d3_8930();                          // 0x00b3d300
}
namespace SP {
cGameTimeManager* GameTimeManager();                      // 0x00b3d380
}
namespace SP {
cTriggerMgr* GetTriggerMgr();                             // 0x00b3d4d0
}
namespace SP {
struct cSPUIEventLog {
  void RemoveAllEventsOfSameType();                       // 0x00dd7620
};
}
namespace SP {
struct cGameNounManager_s00d3_8930 {
  TSphere*         GetCurrentTerrainSphere();             // 0x00f67d90
  cSPCreatureBase_s00d3_8930* GetAvatar();                           // 0x00b1fdb0
};
}
namespace SP {
struct TSphere {
  void FUN_00c78420(TTutorialRef* ref);                   // 0x00c78420
  char FUN_00c77c50(TTutorialRef* ref);                   // 0x00c77c50
};
}
namespace SP {
struct cGameTimeManager {
  void DecPauseGate(int gate);                            // 0x00b32250
};
}
namespace SP {
struct cTriggerMgr {
  int PostTrigger(int a1, int a2, int a3, int a4, int a5, int a6);  // 0x00ae0930
};
}
namespace SP {
struct cSPCreatureBase_s00d3_8930 {
  void StartIndependentSound(const char* name, int param, int** list);  // 0x00c1db40
  static double GetTime();                                // 0x00c0e480
};
}
struct CAudioSystem {
virtual void mSlot00();
virtual void mSlot01();
virtual void mSlot02();
virtual void mSlot03();
virtual void mSlot04();
virtual void mSlot05();
virtual void mSlot06();
virtual void mSlot07();
virtual void mSlot08();
virtual void mSlot09();
virtual void mSlot10();
virtual void mSlot11();
virtual void mSlot12();
virtual void mSlot13();
  virtual void SetLocatingEvent(int eventId);             // +0x38
  virtual void mSlot15();
  virtual void PostLocatingEvent(int eventId, int param);  // +0x40
virtual void mSlot17();
virtual void mSlot18();
virtual void mSlot19();
virtual void mSlot20();
  virtual void mSlot21();
  virtual void FinishLocatingCall();                      // +0x58
};
namespace EA {
namespace Audio {
 CAudioSystem* GetSystemAT();   // 0x00a206f0
}
}
int*   g_locatingSlotsBegin;                              // 0x0169e2a8
int*   g_locatingSlotsEnd;                                // 0x0169e2ac
double g_locatingCallTime;                                // 0x0169e2c0
int    g_locatingCallDone;                                // 0x0169e2c8
struct CLocatingNode {
  CLocatingNode();
  virtual void mSlot00();
  virtual void AddRef();                                  // +0x04
  virtual void Release();                                 // +0x08
  virtual void mSlot0c();
  virtual void mSlot10();
  virtual void mSlot14();
  virtual void mSlot18();
  virtual void mSlot1c();                                 // +0x1c
  uint8_t mBody[0x7c];                                    // -> sizeof == 0x80
};
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
struct CLocatingOwner {
  uint8_t       mUnused00[0xd0];
  CLocatingNode* mpNode;                                  // +0xd0

  void FUN_00d392f0();
};
struct CStateNode {
  uint8_t mUnused00[0x08];
  int     mField08;                                       // +0x08
  uint8_t mUnused0c[0x08];
  int     mField14;                                       // +0x14

  bool FUN_00d38ec0(int type, void* src);
  void FUN_00d38e60(int reason);
};
struct CSourceRec {
  uint8_t mUnused00[0x08];
  int     mField08;                                       // +0x08
};
struct CPtrRange {
  int* mpBegin;                                           // +0x00
  int* mpEnd;                                             // +0x04
};
struct CKeyedRec {
  uint8_t mUnused00[0x08];
  int     mKey;                                           // +0x08
};
struct CPair8 {
  int mKey;                                               // +0x00
  int mValue;                                             // +0x04
};
struct IRefCounted {
  virtual void mSlot00();
  virtual void AddRef();
  virtual void Release();
};
struct CRefCounted {
  uint8_t     mUnused00[0x3c];
  IRefCounted mRef;                                       // +0x3c
};
struct CRefSlot {
  CRefCounted* mpObj;                                     // +0x00
  CRefSlot*    FUN_00d38b10(CRefCounted* other);
};
struct CGObj {
  virtual void mSlot00();
  virtual void mSlot04();
  virtual void mSlot08();
  virtual void mSlot0c(int value);
};
CGObj* g_pModeObject;                                     // 0x0169e2d0
char   g_modeLatched;                                     // 0x0169e2cc
struct CCollisionNoun {
virtual void mSlot00();
virtual void mSlot04();
virtual void mSlot08();
  virtual void* mSlot0c(int key);                         // +0x0c
virtual void mSlot10();
virtual void mSlot14();
virtual void mSlot18();
virtual void mSlot1c();
  virtual int   mSlot20();                                // +0x20
};
struct CCollisionEntry {
  uint8_t mUnused000[0x164];
  int     mField164;                                      // +0x164
  int     mUnused168;                                     // +0x168
  int     mField16c;                                      // +0x16c
  void*   curEntry();                                     // 0x00b058a0
};
struct CScatterMgr {
  void PlaceIndexed(void* node, int idx, int zero);       // 0x00b09b80 (ret 0xC)
};
CScatterMgr* FUN_00b3d440();                               // 0x00b3d440
float g_collisionRadiusSq;                                 // 0x01582f38
// ---- items of slice s00d38930 end

// ---- items of slice s00d3a830 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtbl_cContentValidationSummarizer_0147abec;   // 0x0147abec
extern void* vtbl_cContentValidationSummarizer_013ec458;   // 0x013ec458
struct Vec3 { float x, y, z; };
class CachedObject                    // vtable: +4 release, +8 set, +0xc stop, +0x10 active
{
public:
    virtual void Unused();
    virtual void Release();                              // +4
    virtual void Set(int on);                            // +8
    virtual void Stop(int on);                           // +0xc
    virtual bool IsActive();                             // +0x10
};
class ResourceFactory                 // vtable: +4 release, +8 get
{
public:
    virtual void Unused();
    virtual void Release();                              // +4
    virtual bool Get(uint32_t id, int flags, void** out); // +8
};
struct cModeWorldSingleton
{
    char          pad00[0x60];
    CachedObject* mpCached;          // +0x60
    char          pad64[0x94 - 0x64];
    ResourceFactory* mpFactory;      // +0x94
};
cModeWorldSingleton* GetModeWorld();              // 0x00b3d470
class cGameNounManager;
class cAvatar_s00d3_a830;
cAvatar_s00d3_a830* GetAvatar(cGameNounManager* mgr);        // 0x00b1fdb0
class cSpatialThing
{
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual float* GetUpVector();                 // vtable +0x2c
};
class cAvatar_s00d3_a830
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void SetModePlaying(int a, int b, int c);   // vtable +0x84
    char  pad04[0xbc];
    cSpatialThing* mpThing_c0;                            // +0xc0
    char  padc4[0xb20 - 0xc4];
    void* mpExtra_b20;                                  // +0xb20
};
class cScenarioEntry                    // dispatch target with a vtable
{
public:
    virtual void Unused0();
    virtual void Unused1();
    virtual void Unused2();
    virtual void Unused3();
    virtual void Unused4();
    virtual void Unused5();
    virtual void HandleEvent(uint32_t id, void* pEvent);   // vtable +0x18
};
class cEditorResultData
{
public:
    char pad00[0x4];
};
class cCreatureModeInputStrategy
{
public:
    char pad00[0x54];
    bool mbFlag54;               // +0x54
    void SetInputPriorityStrategy(int priority);  // 0x00d33ec0
};
class cPropertyList_s00d3_a830
{
public:
    char pad00[0x54];
};
class cTexturePreload : public CachedObject
{
public:
    char pad00[0x2c - 0x4];
};
class cCreatureModeStrategy_s00d3_a830
{
public:
    char  pad00[0x49];
    bool  mbReturningFromEditor;                 // +0x49
    char  pad4a[0x60 - 0x4a];
    cEditorResultData*         mEditorResult;    // +0x60
    cCreatureModeInputStrategy* mpInputStrategy; // +0x64
    char  pad68[0xb0 - 0x68];
    int   mGameMode;                             // +0xb0
    cPropertyList_s00d3_a830* mpCreaturePropList;           // +0xb4
    cPropertyList_s00d3_a830* mpCreatureVerbPropList;       // +0xb8
    cScenarioEntry** mScenariosBegin;            // +0xbc
    cScenarioEntry** mScenariosEnd;              // +0xc0
    char  padc4[0xd8 - 0xc4];
    cTexturePreload* mpTexturePreload;           // +0xd8 (ref-counted)

    void SwitchToMode(int mode);                 // 0x00d3af00
    bool OnKeyDown(int key, int state);          // 0x00d3aff0
    Vec3* CalcVisiblePosition(Vec3* out, const Vec3* in, float maxAngle); // 0x00d3b0c0
};
extern cCreatureModeStrategy_s00d3_a830* spInstance_cCreatureModeStrategy;   // 0x0169e294
struct SortEntry { void* mpObject; int32_t mnKey; };
void HeapAdjustUp(SortEntry* v, int top, int hole, void* value, int key);   // 0x00d38c50
void HeapAdjust(SortEntry* v, int top, int n, int hole, void* value, int key, int cmp); // 0x00d39d50
void HeapMake(SortEntry* begin, SortEntry* end, int cmp);    // 0x00d3b430
void HeapSort(SortEntry* begin, SortEntry* end, int cmp);    // 0x00d3b480
void Shuffle(SortEntry* begin, SortEntry* end, void* rng);   // 0x00d3b520
SortEntry* Partition(SortEntry* begin, SortEntry* end, void* value, int key, int cmp); // 0x00d3b5d0
void QuickSort(SortEntry* begin, SortEntry* mid, SortEntry* end, int cmp); // 0x00d3b620
void  operator_delete_array(void* p);                               // 0x00f47380
class RefObj
{
public:
    virtual void Slot0(int on);      // +0x00 deleting release
    virtual void Slot1();            // +0x04 destructor/free
    virtual void Slot2();            // +0x08
    virtual void Slot3(int on);      // +0x0c stop/clear
    int mnRef;                       // +0x04
};
struct RefPair { void* mpObject; char pad04[0x24]; void* mpExtra; };  // stride 0x2c
struct RandomLinearCongruential { uint32_t RandomUint32Uniform(uint32_t n); }; // 0x00a68fb0
class RbtNode { public: RbtNode* mpLeft; RbtNode* mpRight; };
class RbtreeMap
{
public:
    char      pad00[0x18];
    RbtNode*  mpFreeList;      // +0x18
    char      pad1c[0x20 - 0x1c];
    RbtNode*  mpPoolBegin;     // +0x20
    RbtNode*  mpPoolEnd;       // +0x24

    void DoNukeSubtree(RbtNode* node);
};
class cContentValidationSummarizer
{
public:
    void* mpVtbl;                  // +0x00
    char  pad04[0x08 - 0x04];
    int*  mpArray;                 // +0x08

    void* ScalarDeletingDestructor(unsigned int flags);
};
class cAvatarExtra { public: char pad00[0x618]; int mnFlag618; };
// ---- items of slice s00d3a830 end

// ---- items of slice s00d3b920 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_vtblIModePre[];                  // initial SP::cIModeStrategy vtable
extern "C" char g_vtblHandlerPre[];                // initial IHandler vtable
extern "C" char g_vtblCreatureMode[];              // SP::cCreatureModeStrategy vtable
extern "C" char g_vtblCreatureModeHandler[];       // SP::cCreatureModeStrategy handler vtable
extern "C" char g_vtblCreatureModeRefCount[];      // cRefCount base vtable
extern "C" char g_vtblCreatureModeGonzago[];       // SP::cIGonzagoSubsystem vtable
typedef unsigned short u16;
struct VectorStore {
    void* mpBegin;                                 // 0x00
    void* mpEnd;                                   // 0x04
    void* mpCapacity;                              // 0x08
    void* mpAllocator;                             // 0x0c
    u32   mPad10;                                  // 0x10
    void  CopyFrom(const VectorStore& o);          // 0x00473460
};
struct cSPVector3_s00d3_b920 {
    float       mX;                                // 0x00
    VectorStore mStore;                            // 0x04
};
struct cSPVectorRange {
    cSPVector3_s00d3_b920* mpFirst;                           // 0x00
    cSPVector3_s00d3_b920* mpLast;                            // 0x04
};
struct cCreatureModeStrategy_s00d3_b920 {                     // SP::cCreatureModeStrategy
    void* mpVtblMode;                              // 0x000  SP::cIModeStrategy vtable
    void* mpVtblHandler;                           // 0x004  IHandler vtable
    u8    mSubsystem[0x1c];                        // 0x008  SP::cGonzagoSubsystem (own vtable at +0)
    void* mpField024;                              // 0x024
    u8    mEnterEditorSafetyTimer[0x20];           // 0x028  SP::cGonzagoTimer
    u8    mbField048;                              // 0x048
    u8    mbField049;                              // 0x049
    u8    mPad04a[2];
    void* mpEvoPointArray;                         // 0x04c  freed with operator_delete_array
    void* mpTexturePreload;                        // 0x050  AutoRefCount<TexturePreload>
    void* mpCreatureMissionManager;                // 0x054  AutoRefCount<cSPCreatureMissionManager>
    u8    mPad058[8];
    void* mpCreatureVerbPropList;                  // 0x060  AutoRefCount<cPropertyList>
    void* mpCreaturePropList;                      // 0x064  AutoRefCount<cPropertyList>
    void* mpEditorSession;                         // 0x068  released in FUN_00d3c610
    u8    mbField06c;                              // 0x06c
    u8    mPad06d[3];
    u32   mMessageRegistration;                    // 0x070  handler id (0 = not registered)
    void* mpMsgIdArray;                            // 0x074
    void* mpMsgHandler;                            // 0x078
    void* mpMsgServer;                             // 0x07c
    u32   mMsgIdCount;                             // 0x080
    u8    mPad084[4];
    u8    mFrameStopwatch[0x18];                   // 0x088  EA::Stopwatch
    void* mpInputStrategy;                         // 0x0a0  AutoRefCount<cCreatureModeInputStrategy>
    u32   mField0a4;                               // 0x0a4
    u32   mField0a8;                               // 0x0a8
    void* mpEditorResult;                          // 0x0ac  AutoRefCount<cEditorResultData>
    void* mpEditorResultData;                      // 0x0b0
    void* mpField0b4;                              // 0x0b4
    void* mpField0b8;                              // 0x0b8
    void* mpField0bc;                              // 0x0bc
    void* mpCreaturePaths;                         // 0x0c0  eastl vector payload (first word)
    void* mpField0c4;                              // 0x0c4
    u8    mPad0c8[8];
    void* mpField0d0;                              // 0x0d0
    void* mpField0d4;                              // 0x0d4  released in FUN_00d3c610
    void* mpField0d8;                              // 0x0d8
    u8    mbField0dc;                              // 0x0dc
    u8    mbCheckEvolution;                        // 0x0dd
    u8    mbDelayedTransitionFromCLG;              // 0x0de
    u8    mPad0df[0x0e4 - 0x0df];
    u8    mbField0e4;                              // 0x0e4
    u8    mbField0e5;                              // 0x0e5
    u8    mbField0e6;                              // 0x0e6
    u8    mPad0e7[0xf8 - 0xe7];

    void  Deactivate();                            // 0x00d3c380
    void  dtor();                                  // 0x00d3bb10
};
struct cCreatureModeGlobals {                      // 0x0169e2a8 block
    u32* mpSoundIds;                               // 0x00 (0x0169e2a8)
    u32* mpSoundIdsEnd;                            // 0x04 (0x0169e2ac)
    u8   mPad008[0x18 - 0x08];
    u8   mbField018;                               // 0x18 (0x0169e2c0)
    u8   mPad019[0x20 - 0x19];
    u8   mbNeedsSoundFlush;                        // 0x20 (0x0169e2c8)
    u8   mPad021[0x24 - 0x21];
    u8   mbField024;                               // 0x24 (0x0169e2cc)
    u8   mPad025[0x28 - 0x25];
    void* mpCurrentAudio;                          // 0x28 (0x0169e2d0)
    u16  mPad02c;
    void* mpPreviousAudio;                         // 0x2c (0x0169e2d4)
};
void* __cdecl   FUN_0067caf0();                    // 0x0067caf0
void* __stdcall FUN_00b3d240(int a);               // 0x00b3d240
void  __cdecl   FUN_00d3bea0();                    // 0x00d3bea0
u32   __cdecl   FUN_00b95240(float f, u32 packed); // 0x00b95240
void  __cdecl   FUN_00e0be50();                    // 0x00e0be50
void* __cdecl   EA_Audio_GetSystemAT();            // 0x00a206f0
void* __cdecl   FUN_00b3d300();                    // 0x00b3d300 (SP::NounManager)
void* __cdecl   FUN_00b1fdb0();                    // 0x00b1fdb0 (GetAvatar)
void* __cdecl   FUN_00c04590();                    // 0x00c04590
void* __cdecl   FUN_00d51660();                    // 0x00d51660
void* __cdecl   FUN_00d4d6c0();                    // 0x00d4d6c0
void* __cdecl   FUN_00c6acc0();                    // 0x00c6acc0
void* __cdecl   FUN_00c6ee40();                    // 0x00c6ee40
void* __cdecl   FUN_00bc3130();                    // 0x00bc3130
void  __cdecl   FUN_00e0fc90();                    // 0x00e0fc90
void* __cdecl   FUN_009512c0();                    // 0x009512c0
void* __cdecl   FUN_009512d0();                    // 0x009512d0
void* __cdecl   FUN_01021260();                    // 0x01021260
void* __cdecl   FUN_00c707e0();                    // 0x00c707e0 (cPlanet::GetName)
void* __cdecl   FUN_0093b6c0();                    // 0x0093b6c0 (GetBuffer)
void* __cdecl   FUN_008105b0();                    // 0x008105b0 (FindWindowByID)
struct cGonzagoSubsystemBase { void ctor(); void dtor(); };   // 0x00b5b960 / 0x00b5b9a0
struct cGonzagoTimerBase     { void ctor(); void dtor(); };   // 0x00b63890 / 0x00b638b0
struct cStopwatchBase        { void ctor(int a, bool b); };   // 0x0093a560
struct cVectorBase           { void dtor(); };                // 0x005c7f10
void  __cdecl   FUN_00f47380(void* p);             // 0x00f47380 (operator_delete_array)
void  __cdecl   FUN_00571db0(int a, void* b, void* c, void* d, u32 e);  // 0x00571db0
void  __cdecl   FUN_00594870(void* a, void* b, u32 c);   // 0x00595870
static cCreatureModeGlobals& gModes = *(cCreatureModeGlobals*)0x0169e2a8;
static cCreatureModeStrategy_s00d3_b920* gStrategy = 0;       // _spInstance_cCreatureModeStrategy
static inline void  VT_04_0(void* p) { ((void (__thiscall*)(void*))((void***)p)[1])(p); }
static inline void  VT_08_0(void* p) { ((void (__thiscall*)(void*))((void***)p)[2])(p); }
static inline void  VT_0C_1(void* p, int a) { ((void (__thiscall*)(void*, int))((void***)p)[3])(p, a); }
static inline void  VT_38_1(void* p, u32 a) { ((void (__thiscall*)(void*, u32))((void***)p)[0x38 / 4])(p, a); }
static inline void  VT_40_1(void* p, u32 a, u32 b) { ((void (__thiscall*)(void*, u32, u32))((void***)p)[0x40 / 4])(p, a, b); }
static inline void  VT_58_0(void* p) { ((void (__thiscall*)(void*))((void***)p)[0x58 / 4])(p); }
struct cDeactivateNotifyA { void Notify(); };      // 0x0067a120
struct cDeactivateNotifyB { void Notify(); };      // 0x00b33ce0
struct cDeactivateNotifyC { void Notify(); };      // 0x00b33cf0
// ---- items of slice s00d3b920 end

// ---- items of slice s00d3d870 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const bool     kDefaultBoolValue; // 0x015d115d
extern const int      kDefaultInt32Value; // 0x015d1160
extern const uint32_t kDefaultUInt32Value; // 0x015d1164
extern const float    kDefaultFloatValue;   // 0x015d1168
extern const char kTerrainTuningKeys[];                                // 0x01654c00
extern int64_t g_01582df8;
extern int g_01582e5c;
extern int g_01582ec4, g_01582ec8;
extern float g_01582ecc, g_01582ed0;
extern float g_01550aa8;
extern float g_01550aac;
extern float g_01582df0;
extern bool g_01582df4;
extern bool g_01582df5;
extern bool g_01582df6;
extern float g_01582e00;
extern float g_01582e04;
extern float g_01582e08;
extern float g_01582e0c;
extern float g_01582e10;
extern float g_01582e14;
extern float g_01582e18;
extern float g_01582e1c;
extern uint32_t g_01582e20;
extern uint32_t g_01582e24;
extern float g_01582e28;
extern float g_01582e2c;
extern float g_01582e30;
extern float g_01582e34;
extern float g_01582e38;
extern float g_01582e3c;
extern float g_01582e40;
extern float g_01582e44;
extern float g_01582e48;
extern float g_01582e4c;
extern float g_01582e50;
extern float g_01582e54;
extern int g_01582e58;
extern float g_01582e60;
extern float g_01582e64;
extern float g_01582e68;
extern float g_01582e6c;
extern float g_01582e70;
extern float g_01582e74;
extern float g_01582e78;
extern float g_01582e7c;
extern float g_01582e80;
extern float g_01582e84;
extern float g_01582e88;
extern float g_01582e8c;
extern float g_01582eb0;
extern uint32_t g_01582eb4;
extern uint32_t g_01582eb8;
extern float g_01582ebc;
extern float g_01582ec0;
extern float g_01582ed4;
extern float g_01582ed8;
extern float g_01582edc;
extern float g_01582ee0;
extern float g_01582ee4;
extern uint32_t g_01582ee8;
extern float g_01582eec;
extern float g_01582ef0;
extern float g_01582ef4;
extern float g_01582ef8;
extern float g_01582efc;
extern uint32_t g_01582f00;
extern uint32_t g_01582f04;
extern float g_01582f08;
extern float g_01582f0c;
extern uint32_t g_01582f10;
extern uint32_t g_01582f14;
extern float g_01582f18;
extern float g_01582f1c;
extern float g_01582f20;
extern float g_01582f24;
extern float g_01582f28;
extern float g_01582f2c;
extern float g_01582f30;
extern int g_01582f34;
extern float g_01582f38;
extern float g_01582f3c;
extern float g_01582f40;
extern float g_01582f44;
extern float g_01582f48;
extern uint32_t g_01582f4c;
extern float g_01582f50;
extern float g_01582f54;
extern float g_01582f58;
extern float g_01582f5c;
extern float g_01582f60;
extern float g_01582f64;
extern float g_01582f68;
extern float g_01582f6c;
extern float g_01582f70;
extern float g_01582f74;
extern float g_01582f78;
extern float g_01582f7c;
extern float g_01582f80;
extern float g_01582f84;
extern float g_01582f88;
extern float g_01582f8c;
extern float g_01582f90;
extern uint32_t g_01582f94;
extern uint32_t g_01582f98;
extern float g_01582f9c;
extern float g_01582fa0;
extern float g_01582fa4;
extern float g_01582fa8;
extern int g_01582fac;
extern int g_01582fb0;
extern int g_01582fb4;
extern float g_01582fb8;
extern float g_01582fbc;
extern float g_01582fc0;
extern int g_01582fc4;
extern int g_01582fc8;
extern int g_01582fcc;
extern int g_01582fd0;
extern int g_01582fd4;
extern float g_01582fd8;
extern float g_01582fdc;
extern float g_01582fe0;
extern float g_01582fe4;
extern float g_01582fe8;
extern float g_01582fec;
extern float g_01582ff0;
extern float g_01582ff4;
extern float g_01582ff8;
extern float g_0169e278;
extern float g_0169e27c;
extern float g_0169e280;
extern float g_0169e284;
extern float g_0169e288;
extern float g_0169e28c;
extern bool g_0169e290;
extern bool g_0169e291;
struct Property {
    void*    mpData;      // +0x00 (array data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = array / external data)
    uint16_t mnType;      // +0x12

    uint16_t GetType() const { return mnType; }
    void* GetValuePtr()                                         // 0x00446ff0
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    bool* GetValueBool()                                        // 0x0041e920
    {
        if (mnType == 1 || mnType == 0x10)
            return (bool*)GetValuePtr();
        return (bool*)&kDefaultBoolValue;
    }
    int* GetValueInt32()                                        // 0x0041e990
    {
        if (mnType == 9 || mnType == 0x10)
            return (int*)GetValuePtr();
        return (int*)&kDefaultInt32Value;
    }
    uint32_t* GetValueUInt32()                                  // 0x0041ea00
    {
        if (mnType == 10 || mnType == 0x10)
            return (uint32_t*)GetValuePtr();
        return (uint32_t*)&kDefaultUInt32Value;
    }
    float* GetValueFloat()                                      // 0x0041ea70
    {
        if (mnType == 13 || mnType == 0x10)
            return (float*)GetValuePtr();
        return (float*)&kDefaultFloatValue;
    }
};
class cPropertyList_s00d3_d870 {
public:
    virtual int  AddRef();                                       // 0x00
    virtual int  Release();                                      // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
};
struct PropertyListPtr {
    cPropertyList_s00d3_d870* mpObject;

    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    cPropertyList_s00d3_d870* get() const { return mpObject; }
    operator cPropertyList_s00d3_d870*() const { return mpObject; }
    void reset()
    {
        if (mpObject) {
            cPropertyList_s00d3_d870* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    PropertyListPtr& operator=(cPropertyList_s00d3_d870* pObject)
    {
        if (pObject != mpObject) {
            cPropertyList_s00d3_d870* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    PropertyListPtr& operator=(const PropertyListPtr& x) { return operator=(x.mpObject); }
};
class cPropertyManager_s00d3_d870 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool GetPropertyListRaw(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst); // 0x2c

    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst)
    {
        dst.reset();
        return GetPropertyListRaw(instanceID, groupID, dst);
    }
};
inline bool GetBool(cPropertyList_s00d3_d870* pl, uint32_t id, bool& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 1) { v = *p->GetValueBool(); return true; }
    return false;
}
inline bool GetInt(cPropertyList_s00d3_d870* pl, uint32_t id, int& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 9) { v = *p->GetValueInt32(); return true; }
    return false;
}
inline bool GetUInt(cPropertyList_s00d3_d870* pl, uint32_t id, uint32_t& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->GetType() == 10) { v = *p->GetValueUInt32(); return true; }
    return false;
}
inline bool GetFloat(cPropertyList_s00d3_d870* pl, uint32_t id, float& v)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 13) { v = *p->GetValueFloat(); return true; }
    return false;
}
struct Vector2 { float x, y; };
struct Vector3_s00d3_d870 { float x, y, z; };
bool TryGetUIntProperty(cPropertyList_s00d3_d870* pl, uint32_t id, int& value);        // 0x00410370
bool GetFloatProperty(cPropertyList_s00d3_d870* pl, uint32_t id, float& value);        // 0x0040cf10
bool GetPropertyAsVector2(cPropertyList_s00d3_d870* pl, uint32_t id, Vector2& value);  // 0x006a10c0
bool GetPropertyAsVector3(cPropertyList_s00d3_d870* pl, uint32_t id, Vector3_s00d3_d870& value);  // 0x006a1110
bool GetPropertyAsFloatArray(cPropertyList_s00d3_d870* pl, uint32_t id, int& count, float*& values); // 0x006a08b0
template <typename T> inline const T& min_(const T& a, const T& b) { return (b < a) ? b : a; }
struct FloatVector {                  // eastl::vector<float>
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    void resize(uint32_t n);          // 0x004afc80
    float& operator[](int i) { return mpBegin[i]; }
};
class cTerrainEditor_s00d3_d870 { public: void* GetCurrentTerrainSphere(); };   // 0x00f67d90
cTerrainEditor_s00d3_d870* NounManager_s00d3_d870();                                         // 0x00b3d300 (SP::NounManager)
class TerrainMgr { public: cPropertyList_s00d3_d870* Fn1(const char* key, bool sphere); }; // 0x00b1daf0
TerrainMgr* GetTerrainMgr();                                           // 0x00b3d320
cPropertyManager_s00d3_d870* PropertyManager();                                   // 0x0067de30
struct cCreatureModeStrategy_s00d3_d870 {
    uint32_t pad00[0xb4 / 4];
    PropertyListPtr mpTuning;         // +0xb4
    PropertyListPtr mpTuning2;        // +0xb8
};
extern cCreatureModeStrategy_s00d3_d870* spInstance_cCreatureModeStrategy_s00d3_d870;       // 0x0169e294
void LoadCreatureModeExtraTuning(cPropertyList_s00d3_d870* pl);                   // 0x00d3ca90
namespace cCreatureModeTuning {
 void LoadPrivateTuningVariables(cPropertyList_s00d3_d870* pl);   // 0x00d39a10
}
void ReloadModifierTuning();                                           // 0x00d8b320
extern Vector2 g_01583330;
extern Vector3_s00d3_d870 g_01583338;
extern FloatVector g_0169e35c;
// ---- items of slice s00d3d870 end

// ---- items of slice s00d3f9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*       __cdecl SP_EffectsManager();     // 0x0067ddd0
extern "C" void*       __cdecl SP_MessageServer();      // 0x0067dcc0
extern "C" void*       __cdecl SP_PlanetModel();        // 0x00b3d350
extern "C" void*       __cdecl SP_PosseSimulatorInstance(); // 0x00d539d0
extern "C" void*       __cdecl FUN_00b3d480(int);       // 0x00b3d480
extern "C" void*       __cdecl FUN_00401090();          // 0x00401090 GetSetting9
extern "C" void*       __cdecl FUN_00d2b6e0(int, int);  // 0x00d2b6e0
extern "C" int         __cdecl FUN_00d38800(int);       // 0x00d38800 cCreatureLevelUpScenario::EvaluateEvent
extern "C" void        __cdecl FUN_00ba5e10(void*, int); // 0x00ba5e10
extern "C" void*       __cdecl FUN_00c0bc00(void*, void*, void*); // 0x00c0bc00
extern "C" void        __cdecl FUN_00f924e0(float);     // 0x00f924e0
extern "C" void        __cdecl FUN_00e39710(int, void*); // 0x00e39710
extern "C" int         __cdecl FUN_0040cf10(void*, unsigned, void*); // GetPropertyT<int>
extern "C" void*       __cdecl FUN_004a9b40(void*, void*); // QuaternionToMatrix
extern "C" void*       __cdecl FUN_00472b80(void*, void*, float); // QuaternionFromMatrix33
extern "C" float       __cdecl FUN_011e08c2(float);     // 0x011e08c2 float helper
extern "C" float       __cdecl FUN_00c0b440(int);       // 0x00c0b440 (float result in st0)
extern "C" float       __cdecl FUN_00d2e350();          // 0x00d2e350
extern "C" float       __cdecl FUN_00d2e380(int);       // 0x00d2e380
extern "C" float       __cdecl FUN_00d2e480(float);     // 0x00d2e480
extern "C" void        __cdecl FUN_00d2e720();          // 0x00d2e720
extern "C" float       __cdecl FUN_00d2e800(int);       // 0x00d2e800
extern "C" int         __cdecl FUN_00d2e830();          // 0x00d2e830
extern "C" void* __cdecl op_new(unsigned, const char*, int, int, const char*, int);
extern "C" void  __cdecl op_delete_array(void*);
extern "C" void* __cdecl FUN_00b96900(void* first, void* last, void* dst); // 0x00b96900
extern "C" void  __cdecl FUN_00b93d80(void* first, void* last, void* dst); // 0x00b93d80
extern "C" void  __cdecl FUN_00b97500(void* first, void* last, void* dst); // 0x00b97500
extern "C" void  __cdecl FUN_00d3b920(void* p1, void* p2, void* p3, void* p4, void* p5); // 0x00d3b920
extern "C" void  __cdecl FUN_00d3b970(void* dst, unsigned n, const void* val, void* p4);   // 0x00d3b970
typedef void  (__thiscall* TFnV)(void*);
typedef void  (__thiscall* TFnVI)(void*, int);
typedef void  (__thiscall* TFnVIII)(void*, int, int, int);
typedef void  (__thiscall* TFnVP)(void*, void*);
typedef void  (__thiscall* TFnVPPP)(void*, void*, void*, void*);
typedef void  (__thiscall* TFnVIP)(void*, int, void*, int);
typedef int   (__thiscall* TFnI)(void*);
typedef int   (__thiscall* TFnIIP)(void*, int, int, void*);
typedef float (__thiscall* TFnF)(void*);
typedef float (__thiscall* TFnFI)(void*, int);
typedef void* (__thiscall* TFnPU)(void*);
typedef void  (__thiscall* TC_V)(void*);
typedef void  (__thiscall* TC_VII)(void*, int, int);
typedef void  (__thiscall* TC_VF)(void*, float);
typedef void  (__thiscall* TC_VIFIIII)(void*, int, float, int, int, int, int);
typedef void  (__thiscall* TC_VP)(void*, void*);
typedef void  (__thiscall* TC_VPP)(void*, void*, void*);
typedef void  (__thiscall* TC_VIPIIII)(void*, const char*, int, int, int, int, int);
typedef void* (__thiscall* TC_P)(void*);
typedef void* (__thiscall* TC_PP)(void*, void*);
typedef void* (__thiscall* TC_PPP)(void*, void*, void*);
typedef int   (__thiscall* TC_I)(void*);
typedef int   (__thiscall* TC_II)(void*, int);
#define VT(o, off) (*(void***)(o))[(off) / 4]
struct V3 { float x, y, z; };
struct M33 { float m[9]; };
struct Vec20B {
    int mBegin;      // +0x00
    int mEnd;        // +0x04
    int mCap;        // +0x08
    int mPoolA;      // +0x0c
    int mPoolB;      // +0x10

    void* __thiscall Ctor(const Vec20B* src);   // 0x00473460
    void  __thiscall Assign(const Vec20B* src); // 0x00473500
};
struct Vec18 {
    float  mWeight;    // +0x00
    Vec20B mVectors;   // +0x04
};
struct Vec18Vec {
    Vec18* mpBegin;    // +0x00
    Vec18* mpEnd;      // +0x04
    Vec18* mpCap;      // +0x08

    void __thiscall InsertN(Vec18* pos, unsigned n, const Vec18* val); // 0x00d3fa90
};
struct TransformMsg {
    unsigned short mFlags0;      // +0x00 (bit 2 = translation present)
    unsigned short mCount0;      // +0x02
    V3             mTranslation; // +0x04
    unsigned short mFlags1;      // +0x10 (bit 2 = rotation present)
    unsigned short mCount1;      // +0x12
    M33            mRotation;    // +0x14
};
struct cSPTransform_s00d3_f9e0 {
    TransformMsg mT;             // +0x00
    float        mScale;         // +0x38

    void* __thiscall Assign(const void* msg);  // 0x00537dc0
};
struct NodeBuf {
    int*  mpData;    // +0x00 (new[]-allocated, element count at mpData[-1])
    int   miCount;   // +0x04

    void __thiscall Reset(int* data, int count);  // 0x00d3b320
};
struct Node {
    void*   mpFirst;   // +0x000
    void*   mpRef;     // +0x004 (refcounted, vtable slot 1 = Release)
    NodeBuf mBuf;      // +0x008
    char    pad0[0x184 - 0x010];
    Node*   mpNext;    // +0x184
};
struct NodePool {
    char   pad0[0x1c];
    Node*  mpFreeList;   // +0x1c
    char   pad1[4];
    Node*  mpPoolBegin;  // +0x24
    Node*  mpPoolEnd;    // +0x28
    char   pad2[4];
    Node*  mpSentinel;   // +0x30

    void __thiscall FreeLists(Node** arr, unsigned count);  // 0x00d3f9e0
};
struct NounVec_s00d3_f9e0 {
    int    mUnk0;      // +0x00
    void** mpBegin;    // +0x04
    void** mpEnd;      // +0x08
};
struct NounMgr {
    void*    __thiscall GetAvatar();                       // 0x00b1fdb0
    void*    __thiscall GetCurrentTerrainSphere();         // 0x00f67d90
    NounVec_s00d3_f9e0* __thiscall GetGameDataVector(int a, int b, int c, int d, int e); // 0x00b21340
};
struct TriggerMgr {
    char pad0[0x2c];
    int  miState;      // +0x2c
};
extern "C" NounMgr*    __cdecl SP_NounManager();        // 0x00b3d300
extern "C" TriggerMgr* __cdecl SP_GetTriggerMgr();      // 0x00b3d4d0
struct Scenario {
    void*  mpVtbl;      // +0x00
    int    miUnk4;      // +0x04
    int    miState;     // +0x08
    float  mfTimer;     // +0x0c
    void*  mpEffect;    // +0x10
    int    miTag;       // +0x14

    void __thiscall StartDeathCutScreen(int tag);        // 0x00d38e60
    bool __thiscall EvalTrigger(int event, int* ctx);    // 0x00d400e0
    int  __thiscall EvaluateEvent(float dt);             // 0x00d40230
    int  __thiscall Finish();                            // 0x00d40640
};
// ---- items of slice s00d3f9e0 end

// ---- items of slice s00d40930 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cVec3 {
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
};
struct cHerdObj {
    uint8_t  mPad000[0x34];       // +0x000
    cVec3    mPosition;           // +0x034
    uint8_t  mPad040[0xa4 - 0x40];// +0x040
    uint32_t mProfileId;          // +0x0a4
    uint8_t  mPad0a8[0x120 - 0xa8];// +0x0a8
    int32_t  mRangeMin;           // +0x120
    int32_t  mRangeMax;           // +0x124
    uint8_t  mPad128[0x160 - 0x128];// +0x128
    void*    mNest;               // +0x160
    uint8_t  mPad164[0x1e8 - 0x164];// +0x164
    int32_t  mKind;               // +0x1e8
    uint8_t  mPad1ec[0x1f0 - 0x1ec];// +0x1ec
    int32_t  mField1F0;           // +0x1f0
    uint8_t  mPad1f4[0x218 - 0x1f4];// +0x1f4
    void*    mOwner;              // +0x218
};
struct cAvatarHerd {
    uint8_t  mPad000[0x40];       // +0x000
    void**   mHerdBegin;          // +0x040
    void**   mHerdEnd;            // +0x044
    void**   mHerdCap;            // +0x048
    uint8_t  mPad04c[0x54 - 0x4c];// +0x04c
    void**   mAnimalBegin;        // +0x054
    void**   mAnimalEnd;          // +0x058
    uint8_t  mPad05c[0x84 - 0x5c];// +0x05c
    uint8_t  mFlockFlag;          // +0x084
    uint8_t  mPad085[0x88 - 0x85];// +0x085
    uint32_t mField88;            // +0x088
    uint8_t  mPad08c[0x90 - 0x8c];// +0x08c
    void*    mField90;            // +0x090
    uint8_t  mPad094[0xf0 - 0x94];// +0x094
    uint32_t mFieldF0;            // +0x0f0
    uint8_t  mPad0f4[0x160 - 0xf4];// +0x0f4
    void*    mNest;               // +0x160
};
struct cGameNounManager_s00d4_0930 {
    void* GetSelectedAnimal();                                   // 0x00989360
    void* GetAvatar();                                           // 0x00b1fdb0
    void* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, void* tag); // 0x00b21340
};
void*  NounManager_s00d4_0930();                                            // 0x00b3d300
void*  GetTriggerMgr_s00d4_0930();                                          // 0x00b3d4d0
void   LoadCreatureGameplayTuning(uint32_t id, uint32_t tag);    // 0x00d3d870
void*  GetAvatarHerd(void* avatar);                              // 0x00c04590
int    GetDesiredAvatarHerd(uint8_t includeLoose);               // 0x00d40b40
struct cSubTarget {
    virtual bool IsEligible();                                   // slot +0x58
};
struct cSubObj {
    uint8_t     mPad00[0xc0];                                    // +0x000
    cSubTarget* mTarget;                                         // +0x0c0
};
struct cActionTarget {
    cActionTarget(const void* pos, void* handle);                // 0x00ad7a30
    ~cActionTarget();                                            // 0x00ad7ad0
};
struct cTriggerMgr_s00d4_0930 {
    void* PostTrigger(const char* name, int a, int b, int c, int d, int e); // 0x00ae0930
    void  PostAction(uint32_t id, cActionTarget* target);        // 0x00ae09b0
};
void* GetUIRoot();                                               // 0x00d51660
struct cDOMNode { void* GetParent(); };                          // 0x00ff0420
// ---- items of slice s00d40930 end

// ---- items of slice s00d425f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744
extern int g_169e370;                                                 // 0x0169e370
extern void* __cdecl FUN_00cd7d10();
extern void* __cdecl FUN_00d3d420();
extern void* __cdecl FUN_00bbf9b0();
extern void* __cdecl FUN_00b1e500();
extern uint32_t __cdecl PackARGB(int a, int r, int g, int b);         // 0x0067ac80
extern uint8_t g_flag;                                                // 0x01583344
extern uint8_t g_flag2;                                               // 0x01583345
extern float g_t1;                                                    // 0x01583348
extern float g_t2;                                                    // 0x0158334c
extern float g_t3;                                                    // 0x01583350
static inline int RoundToInt(float v)
{
    int r;
    __asm {
        cvtss2si eax, v
        mov r, eax
    }
    return r;
}
class RefObject {
public:
    virtual int AddRef();
    virtual int Release();
};
struct RefPtr {
    RefObject* p;
    RefPtr() : p(0) {}
    ~RefPtr() { if (p) p->Release(); }
    void Assign(RefObject* n)
    {
        RefObject* old = p;
        if (n != old) {
            n->AddRef();
            p = n;
            if (old) old->Release();
        }
    }
};
struct cIconInfo {                    // size 0x24
    uint32_t mColor;                  // +0x00
    Vec3 mPos;                        // +0x04
    uint32_t mFlags;                  // +0x10
    RefPtr mpObject;                  // +0x14
    float mTimeout;                   // +0x18
    uint32_t mAnimState;              // +0x1c
    uint32_t m20;                     // +0x20
};
class cSpatialObject {
public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s0a();
    virtual const Vec3* GetPosition();            // +0x2c
virtual void s0c();
virtual void s0d();
virtual void s0e();
virtual void s0f();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
    virtual bool IsHidden();                      // +0x58
    virtual uint32_t GetV5c(Vec3* out);           // +0x5c
};
struct cOwner {                       // herd / tribe record (the avatar's, and entries' +0x128)
    char pad0[0xa4];
    int mProfile;                     // +0xa4
    char pad1[0x120 - 0xa8];
    int mRangeMin;                    // +0x120
    int mRangeMax;                    // +0x124
    char pad2[0x160 - 0x128];
    void* mpLead;                     // +0x160
    char pad3[0x190 - 0x164];
    uint8_t mFlag190;                 // +0x190
    uint8_t mFlag191;                 // +0x191
};
class cMiniObj : public RefObject {   // entry of the game-data vector; sub-object at +0x34
public:
    char pad4[0x34 - 4];
    cSpatialObject mSub;              // +0x34 (a polymorphic subobject)
    char pad38[0xa9 - 0x38];
    uint8_t mFlagA9;                  // +0xa9
    char padaa[0x124 - 0xaa];
    uint32_t mFlags124;               // +0x124
    cOwner* mpOwner;                  // +0x128
};
struct cSpeciesData_s00d4_25f0 { char pad[0x4ec]; float mR, mG, mB; };                 // +0x4ec
class cCreatureMain {
public:
    virtual void v00();
    char pad4[0xc0 - 4];
};
class cAvatar_s00d4_25f0 : public cCreatureMain {
public:
    cSpatialObject mSub;              // +0xc0
    char padc4[0xb20 - 0xc4 - 0x00];
    cSpeciesData_s00d4_25f0* mpSpecies;          // +0xb20
    cOwner* GetInfo();                // 0x00c04590
};
class cMinimapWin {
public:
    const Vec3* GetOrigin();                                          // 0x00e0acf0
    void SetCenter(const Vec3* pos);                                  // 0x00e0c1f0
    void SetZoom(float z);                                            // 0x00e0c2a0
    cIconInfo* FindIcon(cMiniObj* o);                                 // 0x00e0df30
    bool UpdateIcon(void* id, const Vec3* pos, int sel);              // 0x00e0df70
    void SetIconColor(const Vec3* pos, uint32_t v);                   // 0x00e0c490
    void Clear(int what);                                             // 0x00e0fb90
    void SetMode(int m);                                              // 0x00e0ad00
    void UpdateMapTexture();                                          // 0x00e0e1a0
    void RemoveIcon(void* id, int removeWindow, int flags);           // 0x00e0f9c0
    void AddIcon(void* id, const cIconInfo* info, int a, int b);      // 0x00e10580
};
extern cMinimapWin* g_minimap;                                        // 0x0169e3e4
struct cPropList;
struct cStrategy { char pad[0xb4]; cPropList* mpProps; };
extern cStrategy* g_strategy;                                         // 0x0169e294
extern float __cdecl GetPropertyT_float(cPropList* p, uint32_t id, float def);   // 0x004e1c70
struct cGameDataResult { uint32_t pad0; void** mpBegin; void** mpEnd; };
typedef void* (__cdecl* GameDataFn)();
struct cGameNounManager_s00d4_25f0 {
    cAvatar_s00d4_25f0* GetAvatar();                                             // 0x00b1fdb0
    cGameDataResult* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, uint32_t typeID);   // 0x00b21340
};
extern cGameNounManager_s00d4_25f0* __cdecl NounManager_s00d4_25f0();                       // 0x00b3d300
struct cProfile;
struct cSpeciesManager { cProfile* GetAvatarProfile(); };             // 0x004df420
extern cSpeciesManager* __cdecl FUN_00401090_s00d4_25f0();                       // 0x00401090
extern cOwner* __cdecl GetDesiredAvatarHerd(int which);               // 0x00d40b40
struct cPlanetModel {
    float GetRadius();                                                // 0x00b7e4d0
    int GetContinent(uint32_t key);                                   // 0x00b88590
};
extern cPlanetModel* __cdecl PlanetModel();                           // 0x00b3d350
struct cQuery { void Run(const Vec3* pos, float radius, void* out, int a, int b); };   // 0x00b09340
extern cQuery* __cdecl FUN_00b3d440_s00d4_25f0();                                // 0x00b3d440
struct cInfoB { uint32_t GetKey(); };                                 // 0x00c6acc0
struct PtrVec {
    void** mpBegin;                   // 0x01583354
    void** mpEnd;                     // 0x01583358
    void** mpCap;                     // 0x0158335c
    void Reserve(uint32_t n);                                         // 0x00d01790
    void DoInsert(void** pos, void* const* value);                    // 0x00b96600
};
extern PtrVec g_list;                                                 // 0x01583354
struct FixedPtrVec {                  // eastl::fixed_vector<void*, 8> on the stack
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    uint32_t mFlag;
    uint32_t mBuf[8];
};
// ---- items of slice s00d425f0 end

// ---- items of slice s00d463a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef          int   s32;
typedef void   (__thiscall *TFv)(void*);
typedef void   (__thiscall *TFv1)(void*, s32);
typedef u8     (__thiscall *TFb)(void*);
typedef u8     (__thiscall *TFbkey)(void*, u32, void*);
typedef void*  (__thiscall *TFp)(void*);
typedef u32    (__thiscall *TFu)(void*);
typedef float  (__thiscall *TFf)(void*);
typedef u8     (__thiscall *TFbeff)(void*, void*, s32, void*);
typedef u8     (__thiscall *TFbmsg)(void*, u32, void*);
typedef void   (__thiscall *TFmsg)(void*, void*);
typedef void   (__thiscall *TFmsgv)(void*, s32);
void  __cdecl FUN_0093a780(void* stream, void* out, s32 count, s32 flag); // 0x0093a780 EA::IO::ReadInt32
void* __cdecl FUN_00b3d3e0(void);             // 0x00b3d3e0 SP::EventLog
void* __cdecl FUN_00d67dd0(void);             // 0x00d67dd0 SP::EffectsManagerPtr
void* __cdecl FUN_00b18e00(void* strat);      // 0x00b18e00
void  __cdecl FUN_00d2e8a0(float f);          // 0x00d2e8a0 cCreatureModeStrategy::NotifyEvent
void  __cdecl FUN_00f924e0(void* self, float f); // 0x00f924e0 (thiscall)
void  __cdecl FUN_00ac9480(void* dst, void* src); // 0x00ac9480
void  __cdecl FUN_0059c190(void* out, u32 quat);  // 0x0059c190 Matrix3FromQuaternion
void  __cdecl FUN_00571d40(void* msgsub, u32 v);  // 0x00571d40
void  __cdecl FUN_00434040(void* msg);            // 0x00434040 XformMsg::XformMsg (thiscall ecx=msg)
void* __cdecl FUN_00921340(u32 n);            // 0x00921340
void  __stdcall FUN_00d47160(void* pos, void* val);  // 0x00d47160
struct PropC {
  u32 m00;
  u32 m04;
  u32 m08;
  u32 m0C;
  u16 m10;
  u16 mType;   // +0x12
  u32*   GetUInt();
  u8*    GetBool();
  s32*   GetInt();
  float* GetFloat();
};
struct TrigInfo {
  void* mRef0;    // +0x00
  u32   mField4;  // +0x04
  u8    mField8;  // +0x08
  u8    mPad09;
  u8    mPad0A;
  u8    mPad0B;
  u32   mFieldC;  // +0x0c
  u32   mField10; // +0x10
  float mField14; // +0x14
  float mField18; // +0x18
  u32   mField1C; // +0x1c
  u32   mField20; // +0x20
  u8    mField24; // +0x24
  u8    mPad25;
  u8    mPad26;
  u8    mPad27;
  void* mRef28;   // +0x28
};
struct TrigVec {
  TrigInfo* mBegin;  // +0x00
  TrigInfo* mEnd;    // +0x04
  TrigInfo* mCap;    // +0x08
  u32       mPadC;   // +0x0c
  u32       mPad10;  // +0x10
  u32       mCount;  // +0x14
  TrigVec*  Assign(TrigVec* src);                          // 0x00d47020
  TrigInfo* Grow(s32 n, TrigInfo* first, TrigInfo* last);  // 0x00d46bd0
  void      DestroyRange(TrigInfo* first, TrigInfo* last); // 0x00d3b320
};
struct UVec3 { u32 x, y, z; };
struct SpVec3 {
  UVec3* mBegin;  // +0x00
  UVec3* mEnd;    // +0x04
  UVec3* mCap;    // +0x08
  u32    mPadC;   // +0x0c
  u32    mPad10;  // +0x10
  void   Resize(s32 n);   // 0x00473810
};
struct GridEntry {
  float  mValue; // +0x00
  SpVec3 mVec;   // +0x04
};
struct GridVec {
  GridEntry* mBegin; // +0x00
  GridEntry* mEnd;   // +0x04
  GridEntry* mCap;   // +0x08
  u32        mPadC;  // +0x0c
  u32        mPad10; // +0x10
  void       Resize(s32 n);  // 0x00d45710
};
struct cVarListSerializer {
  u8   mData[0xa14];
  void Ctor(void* obj, void* list, u32 sig);  // 0x00692f90
  u8   Serialize(void* stream);               // 0x00693e10
};
struct HashMapC {
  u8    pad00[8];
  u32   mField08;  // +0x08
  u32   mField0C;  // +0x0c
  float mField10;  // +0x10
  float mField14;  // +0x14
  u32   mField18;  // +0x18
  u8    pad1C[0x18];
  u32   mField34;       // +0x34 embedded object (address only)
  u8    pad38[0x100];
  u8    mPool138[0x6200]; // +0x138 fixed pool storage
  u32   mField6338;     // +0x6338 embedded object (address only)
  void  Construct(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6); // FUN_00d3b260
  void  Grow(u32 n);          // FUN_00d39c30
};
struct FixedPoolLocal {
  void* mpHead;  // +0x00
  u32   x04;     // +0x04
  void* p08;     // +0x08
  void* p0C;     // +0x0c
  u32   x10;     // +0x10
  void* p14;     // +0x14
};
struct FixedPoolC {
  void* mpHead;
  void Init(void* mem, u32 poolSize, u32 elemSize, u32 align, u32 flags); // 0x00921260
};
struct PoolAllocC {
  u32 Size(u32 v);   // 0x009213c0
};
struct NounMgrC {
  void* GetAvatar();  // 0x00b1fdb0
};
struct AvatarC {
  u8 pad[0xb5e];
  u8 fB5E;            // +0xb5e
};
struct XformMsgC {
  u8  pad00[8];
  u16 mFlags;   // +0x08
  u16 mPad0A;
  u16 mCount;   // +0x0a
  u8  pad0C[0x10];
  u32 mMatrix[9]; // +0x1c
};
struct GlobInstC {
  u8     pad[0xbc];
  void** mBegin;  // +0xbc
  void** mEnd;    // +0xc0
};
struct EventLogC {
  void PostFeedbackEvent(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5); // 0x00dd8640
};
__forceinline void* GetStream(void* reader) {
  void* o = ((TFp)(*(void***)reader)[0x20 / 4])(reader);
  return ((TFp)(*(void***)o)[0x18 / 4])(o);
}
// ---- items of slice s00d463a0 end

// ---- items of slice s00d47630 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef signed   int     i32;
void FUN_00f473a0(void* p);                 // operator delete (0x00f473a0, pool entry)
struct cNodePool {
    u8      pad_00[4];                          // +0x00
    void*   mpTail;                             // +0x04  first detached node
    u32     mCount;                             // +0x08  live node count
    u32     mField_0c;                          // +0x0c  reset to 0 on teardown
    u8      pad_10[0x0c];                       // +0x10
    void*   mpFreeHead;                         // +0x1c  free-list head
    u8      pad_20[4];                          // +0x20
    u8*     mpPoolLo;                           // +0x24  pool range begin
    u8*     mpPoolHi;                           // +0x28  pool range end
    u8      pad_2c[4];                          // +0x2c
    void*   mpSentinel;                         // +0x30
    void  FreeLists(void* first, u32 count);    // 0x00d3f9e0
};
struct cContentValidationSummarizer_s00d4_7630 {
    void*     mVtbl_00;                         // +0x00
    u8        pad_04[4];                        // +0x04
    cNodePool mPool;                            // +0x08

    void FUN_00d47850();                        // 0x00d47850
};
struct cTriggerRef;                             // ref-counted object (declared below)
struct cTriggerRec {
    cTriggerRef* mpRef_00;                      // +0x00  AutoRefCount<cTriggerRef> slot
    u8      pad_04[4];                          // +0x04
    u8      mFlag_08;                           // +0x08
    u8      pad_09[3];                          // +0x09
    u32     mKind_0c;                           // +0x0c  ria id / event id
    u8      pad_10[0x1c];                       // +0x10
};
struct cTriggerOwner {                          // event carrier passed by pointer
    void**  mVtbl_00;                           // +0x00
    u8      pad_04[0x20];                       // +0x04
    u32     mKey_24;                            // +0x24  owner key / event type
    void*   mpObj_28;                           // +0x28  related object
};
struct cTriggerEvent {                          // the event object itself
    void*   mpObject_00;                        // +0x00  object whose +0xb58 flags are read
    void*   mpOwner_04;                         // +0x04
};
struct cNounManager {
    u8* Find(void* key);                        // 0x00b21000
};
struct cPropertyManager {                       // opaque property manager
    void**  mVtbl_00;                           // +0x00
};
struct cTriggerRef {                            // ref-counted object
    void**  mVtbl_00;                           // +0x00
    void AddRef();                              // 0x00 (vtable slot 0x00)
    void Release();                             // 0x00 (vtable slot 0x04)
};
struct cTrigFindCtx {                           // 3-dword context for 0x00d47510
    u32                mKey_00;                 // +0x00
    u32                mZero_04;                // +0x04
    cPropertyManager*  mpManager_08;            // +0x08
};
struct cTrigNodeList {                          // element returned by the map lookup
    u8           pad_00[8];                     // +0x00
    cTriggerRec* mpBegin_08;                    // +0x08
    cTriggerRec* mpEnd_0c;                      // +0x0c
};
struct cTrigSlots {                             // sp_vector<cTriggerRec> at info+0x04
    cTriggerRec* mpBegin_00;                    // +0x00
    cTriggerRec* mpEnd_04;                      // +0x04
    u8           pad_08[4];                     // +0x08
    void Append();                              // 0x00d472a0 (ecx = this)
};
struct cTriggersInfo {
    cTriggerRef* mpOwner_00;                    // +0x000
    cTrigSlots   mSlots;                        // +0x004
    u8           pad_0c[0x170];                 // +0x00c
    u8           mFlag_17c;                     // +0x17c
};
struct cTriggerMap {
    u8      pad_00[4];                          // +0x00
    u8**    mpBegin;                            // +0x04  element pointer table
    u32     mCount;                             // +0x08
    void  Find(u8** ppIter, const u32* key);    // 0x00d46b70
    cTriggersInfo* NewInfo(cTrigFindCtx* ctx);  // 0x00d47510 (ecx = this)
};
void GetPropertyAsUint32Array(void* prop, u32 key, i32* count, u32** array); // 0x006a0840
cNounManager*     SP_NounManager_s00d4_7630();             // 0x00b3d300
cPropertyManager* SP_PropertyManager();         // 0x0067de30
typedef void* (__thiscall *cOwnerVirt20)(cTriggerOwner*, void*);      // slot 0x20
typedef void  (__thiscall *cRefVirt)(cTriggerRef*);                   // slots 0x00 / 0x04
typedef bool  (__thiscall *cPropMgrVirt2c)(cPropertyManager*, u32, u32, cTriggerRef**);
inline void cTriggerRef::AddRef()  { ((cRefVirt)mVtbl_00[0x00 / 4])(this); }
inline void cTriggerRef::Release() { ((cRefVirt)mVtbl_00[0x04 / 4])(this); }
struct cCreatureTriggerSystem {
    u8        pad_00[8];                        // +0x00
    cTriggerMap mMap;                           // +0x08

    cTriggerRec* GetTrigger(u32 eventType, cTriggerOwner* owner);      // 0x00d47630
    bool         EvaluateEvent(u32 eventID, cTriggerEvent* ev);        // 0x00d478b0
    bool         EvaluateTrigger(cTriggerRec* t, void* owner, void* obj); // 0x00d46c30
    void         ReadTrigger(cTriggerRec* rec);                        // 0x00d46730
};
// ---- items of slice s00d47630 end

// ---- items of slice s01364b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00572810();
extern "C" void FUN_00572840();
extern "C" void FUN_0057cde0();
extern "C" void FUN_0057ce00();
extern "C" void FUN_00692ca0();
extern "C" void FUN_00692fb0();
extern "C" void FUN_00692ff0();
extern "C" void FUN_00693090();
extern "C" void FUN_00694ee0();
extern "C" void FUN_00694fa0();
extern "C" void FUN_00ac8750();
extern "C" void FUN_00ac8780();
extern "C" void FUN_00b1fbf0();
extern "C" void FUN_00c2e4e0();
extern "C" void FUN_00d38b50();
extern "C" void FUN_00d38b70();
extern "C" void FUN_00d38b90();
extern "C" void FUN_011874d0();
#pragma warning(disable: 4100)
namespace Simulator {
struct Attribute {
    const char* mpName;                                    // +0x00  attribute name
    uint32_t    mHash;                                     // +0x04  FNV hash of the name
    uint32_t    mLocation;                                 // +0x08  member offset, or a static address
    uint32_t    mUnused0c;                                 // +0x0c  never written
    uint32_t    mUnused10;                                 // +0x10  never written
    uint32_t    mUnused14;                                 // +0x14  never written
    uint32_t    mZero18;                                   // +0x18
    uint32_t    mZero1c;                                   // +0x1c
    void*       mpFn20;                                    // +0x20
    void*       mpFn24;                                    // +0x24
    void*       mpFn28;                                    // +0x28
    void*       mpFn2c;                                    // +0x2c
    void*       mpFn30;                                    // +0x30
    void*       mpFn34;                                    // +0x34
    void*       mpFn38;                                    // +0x38
};  // namespace Simulator
}
using Simulator::Attribute;
extern Attribute g_creatureEditorAttributes[3];            // 0x015833f0
// ---- items of slice s01364b20 end

// @ 0x00b8c330
void cPlanetModel_s00b8_c330::UpdateMinimap(int arg0, int arg1, int modeOverride)
{
    if (GetActivePlanet()) {
        float temperature = GetActivePlanet()->GetTemperature();
        mIsFrozen = temperature < TerraformTuning()->GetIceThreshold();
    }

    if (mpISphere == 0)
        return;

    int mode = SP::App()->GetGameModeManager()->GetModeID();
    if (modeOverride != 0)
        mode = modeOverride;
    mpSphere->Update(mode, arg0);

    if (mObstaclesDirty) {
        mObstaclesDirty = false;
        RebuildObstacles();
    }
    g_16881e8 = 0;
    if (g_ResourceNodesDirty) {
        g_ResourceNodesDirty = 0;
        AddResourceNodes();
    }

    // ---- straight land routes -------------------------------------------
    if (mLandRoutesDirty) {
        mpMinimapGfx->mpLandLayer->ReleaseBuffer();
        if (mLandTradeRoutes.mpBegin != mLandTradeRoutes.mpEnd) {
            mpMinimapGfx->mpLandLayer->Begin();
            int count = mLandTradeRoutes.size();
            for (int i = 0; i < count; ++i) {
                Vector3 posA;
                Vector3 posB;
                mLandTradeRoutes[i].first->GetPosition(&posA);
                mLandTradeRoutes[i].second->GetPosition(&posB);
                const Vector3& colorA = mLandTradeRoutes[i].first->GetColor();
                const Vector3& colorB = mLandTradeRoutes[i].second->GetColor();
                mpMinimapGfx->mpLandLayer->AddSegment(posA, posB, ToColor(colorA));
                mpMinimapGfx->mpLandLayer->AddSegment(posB, posA, ToColor(colorB));
            }
            mpMinimapGfx->mpLandLayer->End();
        }
        mLandRoutesDirty = false;
    }

    // ---- sea routes (curved along the water surface) ----------------------
    if (mSeaRoutesDirty && mpISphere && mpISphere->IsReady()) {
        mpMinimapGfx->mpSeaLayer->ReleaseBuffer();
        if (mSeaTradeRoutes.mpBegin != mSeaTradeRoutes.mpEnd) {
            GetWaterHeight();
            CurveVector curve;
            Vec3Vector points;
            mpMinimapGfx->mpSeaLayer->Begin();
            int count = mSeaTradeRoutes.size();
            for (int i = 0; i < count; ++i) {
                Vector3 posA(mSeaTradeRoutes[i].first->GetLocation());
                Vector3 posB(mSeaTradeRoutes[i].second->GetLocation());
                const Vector3& colorA = mSeaTradeRoutes[i].first->GetColor();
                const Vector3& colorB = mSeaTradeRoutes[i].second->GetColor();
                curve.clear();
                points.clear();
                if (posA != g_InvalidPosition && posB != g_InvalidPosition) {
                    posA = SnapToSurface(posA + SP::normalized_safe(posA - mSeaTradeRoutes[i].first->GetPlanetCenter()) * 20.0f);
                    posB = SnapToSurface(posB + SP::normalized_safe(posB - mSeaTradeRoutes[i].second->GetPlanetCenter()) * 20.0f);

                    cCurveParams params = g_WaterCurveParams;
                    params.mpFunc = (void*)FUN_00b836b0;
                    GetCurveBuilder()->Build(params, posA, posB, curve, 0.0f, 1.0f);

                    points.resize(curve.size());
                    int n = curve.size();
                    for (int k = 0; k < n; ++k)
                        points[k] = curve[k].mPos;

                    if (points.empty()) {
                        points.push_back(posA);
                        points.push_back(posB);
                    }

                    int last = points.size() - 1;
                    for (int j = 0; j < last;) {
                        Vector3 d = points[j] - points[j + 1];
                        if (d.z * d.z + d.y * d.y + d.x * d.x > 100.0f) {
                            Vector3 mid = (points[j] + points[j + 1]) * 0.5f;
                            points.insert(&points[j + 1], mid);
                            ++last;
                        } else {
                            ++j;
                        }
                    }

                    mpMinimapGfx->mpSeaLayer->AddCurve(points, ToColor(colorA));
                    reverse(points.begin(), points.end());
                    mpMinimapGfx->mpSeaLayer->AddCurve(points, ToColor(colorB));
                }
            }
            mpMinimapGfx->mpSeaLayer->End();
        }
        mSeaRoutesDirty = false;
    }

    // ---- land routes along stored paths ------------------------------------
    if (mPathRoutesDirty && mpISphere && mpISphere->IsReady()) {
        mpMinimapGfx->mpAirLayer->ReleaseBuffer();
        if (mPathRoutes.mpBegin != mPathRoutes.mpEnd) {
            Vec3Vector path;
            mpMinimapGfx->mpAirLayer->Begin();
            int count = mPathRoutes.size();
            for (int i = 0; i < count; ++i) {
                path = mPathRoutes[i].mPath;
                Vector3 colorA(mPathRoutes[i].city1->GetColor());
                Vector3 colorB(mPathRoutes[i].city2->GetColor());
                mpMinimapGfx->mpAirLayer->AddPath(path, ToColor(colorA));
                if (path.mpBegin != path.mpEnd)
                    reverse(path.begin(), path.end());
                mpMinimapGfx->mpAirLayer->AddPath(path, ToColor(colorB));
            }
            mpMinimapGfx->mpAirLayer->End();
        }
        mPathRoutesDirty = false;
    }
}

// @ 0x00d2e480
void SetClampedValue(float value)
{
    g_0169e370.mClampedValue = value;
}

// @ 0x00d2e8a0
void cCreatureModeStrategy::NotifyEvent(float amount)
{
    if (amount != kRealZero) {
        float v = g_0169e370.mClampedValue + amount;
        float hi = kTierMaxHeight;
        float* pf = &v;
        if (hi <= v)
            pf = &kTierMaxHeight;
        g_0169e370.mClampedValue = *pf;

        NounManager()->GetCurrentTerrainSphere()->mHeight += amount;

        if (GetCurrentGameMode() != &g_01654c10) {
            cCreatureModeStrategy* inst = Instance();
            if (inst != 0) {
                inst->mpSink->Update(amount);
                struct EventCtx {
                    cAvatar* avatar;    // +0x00
                    int      pad04;     // +0x04
                    int      zero;      // +0x08
                    float    amount;    // +0x0c
                    int      pad10;     // +0x10
                    int      pad14;     // +0x14
                } ctx;
                ctx.avatar = NounManager()->GetAvatar();
                ctx.zero = 0;
                ctx.amount = amount;
                inst->FUN_00d39360(0x45ab96e, &ctx);
            }
        }
    }
}

// @ 0x00d2e980
void ResetCreatureModeState()
{
    memset(&g_0169e370, 0, 0x50);
    g_0169e370.mFlags38 |= 0x40000000;
    g_0169e370.mFlags3c |= 0x20;
    g_0169e370.mMode = 1;
}

// @ 0x00d387c0
void MarkEventAsOccurred(u32 event)
{
    u32 local[3];
    local[0] = event;
    local[1] = 0;
    local[2] = 0x68dd6929;

    cTerrainSphere_s00d3_77f0* ts = (cTerrainSphere_s00d3_77f0*)((cTerrainEditor*)X_NounManager())->GetCurrentTerrainSphere();
    if (ts != 0)
        ts->FUN_c78420(local);
}

// @ 0x00d38800
const char* EvaluateEvent(int event)
{
    const char* name = 0;
    switch (event)
    {
    case 1: return "CRG_BrainUpgrade1";
    case 2: return "CRG_BrainUpgrade2";
    case 3: return "CRG_BrainUpgrade3";
    case 4: name = "CRG_BrainUpgrade4";
    }
    return name;
}

// @ 0x00d38880
bool cCreatureLevelUpScenario::HasBrainUpgrade()
{
    return mFieldA0 != 0xd;
}

// @ 0x00d38890
void cCreatureModeStrategy_s00d3_77f0::OnMouseWheel()
{
    void* m = X_GameInputManager();
    ((FnV0)VTBL(m)[0x48 / 4])(m);
}

// @ 0x00d388a0
void cCreatureModeStrategy_s00d3_77f0::OnMouseMove(int a, float b, float c, int d)
{
    void* m = X_GameInputManager();
    ((FnVIFFI)VTBL(m)[0x58 / 4])(m, a, b, c, d);
}

// @ 0x00d388d0
void cCreatureModeStrategy_s00d3_77f0::OnMouseButton(int a, float b, float c, int d)
{
    void* m = X_GameInputManager();
    ((FnVIFFI)VTBL(m)[0x54 / 4])(m, a, b, c, d);
}

// @ 0x00d38900
bool FUN_00d38900()
{
    cGameNounManager_s00d3_77f0* nm = (cGameNounManager_s00d3_77f0*)X_NounManager();
    void* av = nm->GetAvatar();
    if (av != 0)
        return ((FnI0)VTBL(av)[0xd8 / 4])(av) == 4;
    return false;
}

// @ 0x00d38930
void __stdcall FUN_00d38930(int param_1)
{
  SP::cSPUIEventLog* log = SP::EventLog(param_1, 0, 0);
  log->RemoveAllEventsOfSameType();

  TTutorialRef ref;
  ref.mNoun      = param_1;
  ref.mUnused04  = 0;
  ref.mMagic     = 0x68dd6929;

  SP::cGameNounManager_s00d3_8930* editor = SP::NounManager_s00d3_8930();
  SP::TSphere*         sphere = editor->GetCurrentTerrainSphere();
  if (sphere != 0)
    sphere->FUN_00c78420(&ref);
}

// @ 0x00d38980
int __stdcall FUN_00d38980(int param_1)
{
  SP::cGameNounManager_s00d3_8930* editor = SP::NounManager_s00d3_8930();
  SP::TSphere*        sphere = editor->GetCurrentTerrainSphere();

  TTutorialRef ref;
  ref.mNoun     = param_1;
  ref.mUnused04 = 0;
  ref.mMagic    = 0x68dd6929;

  if (sphere != 0) {
    if (sphere->FUN_00c77c50(&ref) != 0)
      return 1;
  }
  return 0;
}

// @ 0x00d389d0
void __stdcall FUN_00d389d0(int param_1, int param_2)
{
  TTutorialRef ref;
  ref.mNoun     = param_2;
  ref.mUnused04 = 0;
  ref.mMagic    = 0x68dd6929;

  SP::cGameNounManager_s00d3_8930* editor = SP::NounManager_s00d3_8930();
  SP::TSphere*        sphere = editor->GetCurrentTerrainSphere();
  if (sphere != 0)
    sphere->FUN_00c78420(&ref);

  SP::GetTriggerMgr()->PostTrigger(param_1, 1, 1, 0, 0, 0);
}

// @ 0x00d38b10
CRefSlot* CRefSlot::FUN_00d38b10(CRefCounted* other)
{
  CRefCounted* old = mpObj;
  if (other != old) {
    if (other != 0)
      other->mRef.AddRef();
    mpObj = other;
    if (old != 0)
      old->mRef.Release();
  }
  return this;
}

// @ 0x00d38bb0
void FUN_00d38bb0(CPair8* begin, CPair8* end)
{
  if (begin == end)
    return;
  CPair8* cur = begin;
  while ((cur = cur + 1) != end) {
    CPair8  v = *cur;
    CPair8* j = cur;
    while (j != begin && v.mValue > j[-1].mValue) {
      j[0] = j[-1];
      --j;
    }
    *j = v;
  }
}

// @ 0x00d38c00
void FUN_00d38c00(int* begin, int* end)
{
  for (; begin != end; begin += 2) {
    int  k1   = begin[1];
    int  k0   = begin[0];
    int* j    = begin - 1;
    int* hole = begin;
    if (begin[-1] < k1) {
      do {
        hole[0] = hole[-2];
        hole[1] = hole[-1];
        j    -= 2;
        hole -= 2;
      } while (*j < k1);
    }
    hole[0] = k0;
    hole[1] = k1;
  }
}

// @ 0x00d38c50
void HeapAdjustUp(SortEntry* v, int top, int hole, void* value, int key)
{
    int parent = (hole - 1) >> 1;
    while (hole > top && v[parent].mnKey > key)
    {
        v[hole] = v[parent];
        hole = parent;
        parent = (parent - 1) >> 1;
    }
    v[hole].mnKey = key;
    v[hole].mpObject = value;
}

// @ 0x00d38ca0
void FUN_00d38ca0(void)
{
  SP::cGameTimeManager* mgr = SP::GameTimeManager();
  mgr->DecPauseGate(0x4bf38a7);
}

// @ 0x00d38cc0
void FUN_00d38cc0(SP::cSPCreatureBase_s00d3_8930* param_1, int param_2)
{
  if (g_locatingCallDone != 1) {
    uint32_t n = (uint32_t)(g_locatingSlotsEnd - g_locatingSlotsBegin);
    for (uint32_t i = 0; i < n; ++i) {
      int           slot = g_locatingSlotsBegin[i];
      CAudioSystem* sys  = EA::Audio::GetSystemAT();
      if (sys != 0) {
        sys->SetLocatingEvent(0x347536b);
        sys->PostLocatingEvent(0x3475385, slot);
        sys->PostLocatingEvent(0x34753a0, 1);
        sys->FinishLocatingCall();
      }
    }
    param_1->StartIndependentSound("vsoc_matecall_2_loop", param_2, &g_locatingSlotsBegin);
  }
  g_locatingCallDone = 1;
  SP::cGameNounManager_s00d3_8930* manager = SP::NounManager_s00d3_8930();
  manager->GetAvatar();
  g_locatingCallTime = SP::cSPCreatureBase_s00d3_8930::GetTime();
}

// @ 0x00d38d80
void FUN_00d38d80(char param_1)
{
  CGObj* obj = g_pModeObject;
  if (obj != 0) {
    obj->mSlot0c(param_1 != 0);
    if (param_1 != 0) {
      obj = g_pModeObject;
      if (obj != 0) {
        g_pModeObject = 0;
        obj->mSlot04();
      }
    }
  }
  g_modeLatched = 1;
}

// @ 0x00d38dd0
void FUN_00d38dd0(int param_1, CCollisionNoun* param_2, int param_3, int param_4, int param_5, int param_6, float* param_7)
{
  if (param_7[0] * param_7[0] + param_7[1] * param_7[1] + param_7[2] * param_7[2] > g_collisionRadiusSq) {
    if (param_2->mSlot20() == 0x2C9CC91) {
      CCollisionEntry* entry = (CCollisionEntry*)param_2->mSlot0c(0x2C9CC8E);
      if (entry != 0 && entry->mField16c == 0) {
        void* current = entry->curEntry();
        if (current != 0) {
          FUN_00b3d440()->PlaceIndexed(current, entry->mField164, 1);
        }
      }
    }
  }
}

// @ 0x00d38e60
void CStateNode::FUN_00d38e60(int reason)
{
  mField08 = 2;
  if (reason == 5) {
    SP::GetTriggerMgr()->PostTrigger((int)"CRG_AvatarDied_Starvation", 1, 1, 0, 0, 0);
    return;
  }
  if (reason == 9) {
    SP::GetTriggerMgr()->PostTrigger((int)"CRG_AvatarDied_SeaMonster", 1, 1, 0, 0, 0);
    return;
  }
  SP::GetTriggerMgr()->PostTrigger((int)"CRG_AvatarDied", 1, 1, 0, 0, 0);
}

// @ 0x00d38ec0
bool CStateNode::FUN_00d38ec0(int type, void* src)
{
  if ((type == 0x6CA7A75 || type == 0xD3353639) && mField08 != 3) {
    mField08 = 1;
    mField14 = ((CSourceRec*)src)->mField08;
    return true;
  }
  return false;
}

// @ 0x00d392f0
void CLocatingOwner::FUN_00d392f0()
{
  CLocatingNode* node = new ("Simulator", 0, 0, 0, 0) CLocatingNode();
  CLocatingNode* old  = mpNode;
  if (node != old) {
    if (node != 0)
      node->AddRef();
    mpNode = node;
    if (old != 0)
      old->Release();
  }
  mpNode->mSlot1c();
}

// @ 0x00d397c0
bool FUN_00d397c0(int key, CPtrRange* range)
{
  uint32_t count = (uint32_t)(range->mpEnd - range->mpBegin);
  int**    p     = (int**)range->mpBegin;
  for (uint32_t i = 0; i < count; ++i) {
    if (((CKeyedRec*)(*p))->mKey == key)
      return true;
    ++p;
  }
  return false;
}

// @ 0x00d3a830
void StopModeResources()
{
    cModeWorldSingleton* world = GetModeWorld();
    if (world->mpCached != 0)
        world->mpCached->Stop(1);

    cAvatar_s00d3_a830* av = GetAvatar(NounManager());
    if (((cAvatarExtra*)av->mpExtra_b20)->mnFlag618 == 0)
    {
        cCreatureModeStrategy_s00d3_a830* self = spInstance_cCreatureModeStrategy;
        if (self->mpTexturePreload == 0)
        {
            ResourceFactory* factory = GetModeWorld()->mpFactory;
            cTexturePreload* old = self->mpTexturePreload;
            if (old != 0)
            {
                self->mpTexturePreload = 0;
                old->Release();
            }
            if (factory->Get(0xa096a243, 0, (void**)&self->mpTexturePreload))
                self->mpTexturePreload->Set(0);
        }
        ResourceFactory* factory = GetModeWorld()->mpFactory;
        CachedObject* cached = GetModeWorld()->mpCached;
        if (cached != 0)
        {
            GetModeWorld()->mpCached = 0;
            cached->Release();
        }
        factory->Get(0x84665696, 0, (void**)&GetModeWorld()->mpCached);
    }
    else
    {
        ResourceFactory* factory = GetModeWorld()->mpFactory;
        CachedObject* cached = GetModeWorld()->mpCached;
        if (cached != 0)
        {
            GetModeWorld()->mpCached = 0;
            cached->Release();
        }
        factory->Get(0x4cab5702, 0, (void**)&GetModeWorld()->mpCached);
    }
    GetModeWorld()->mpCached->Set(0);
}

// @ 0x00d3a960
void ResetModeResources()
{
    cCreatureModeStrategy_s00d3_a830* self = spInstance_cCreatureModeStrategy;
    if (self->mpTexturePreload != 0)
    {
        self->mpTexturePreload->Stop(1);
        cTexturePreload* old = self->mpTexturePreload;
        if (old != 0)
        {
            self->mpTexturePreload = 0;
            old->Release();
        }
    }

    cModeWorldSingleton* world = GetModeWorld();
    if (world->mpCached == 0)
        return;

    if (world->mpCached->IsActive())   // vtable +0x10
    {
        GetModeWorld()->mpCached->Stop(1);
        ResourceFactory* factory = GetModeWorld()->mpFactory;
        CachedObject* cached = GetModeWorld()->mpCached;
        if (cached != 0)
        {
            GetModeWorld()->mpCached = 0;
            cached->Release();
        }
        factory->Get(0x4cab5702, 0, (void**)&GetModeWorld()->mpCached);
        GetModeWorld()->mpCached->Set(0);
        return;
    }
    ResourceFactory* factory = GetModeWorld()->mpFactory;
    CachedObject* cached = GetModeWorld()->mpCached;
    if (cached != 0)
    {
        GetModeWorld()->mpCached = 0;
        cached->Release();
    }
    factory->Get(0x4cab5702, 0, (void**)&GetModeWorld()->mpCached);
}

// @ 0x00d3b320
void __stdcall ScenarioDestroy(RefPair* begin, RefPair* end)
{
    for (; begin < end; ++begin)
    {
        RefObj* extra = (RefObj*)begin->mpExtra;
        if (extra != 0)
            extra->Slot3(0);
        extra = (RefObj*)begin->mpExtra;
        if (extra != 0)
            extra->Slot1();
        RefObj* obj = (RefObj*)begin->mpObject;
        if (obj != 0)
            obj->Slot1();
    }
}

// @ 0x00d3b370
void RbtreeMap::DoNukeSubtree(RbtNode* node)
{
    if (node == 0)
        return;
    do
    {
        DoNukeSubtree(node->mpLeft);
        RbtNode* right = node->mpRight;
        if (node >= mpPoolBegin && node < mpPoolEnd)
        {
            node->mpLeft = mpFreeList;
            mpFreeList = node;
        }
        else
        {
            operator_delete_array(node);
        }
        node = right;
    } while (node != 0);
}

// @ 0x00d3b3c0
void** CopyRefs(void** begin, void** end, void** out)
{
    while (begin != end)
    {
        void* src = *begin;
        void* old = *out;
        if (src != old)
        {
            if (src != 0)
                ++((RefObj*)src)->mnRef;
            *out = src;
            if (old != 0 && --((RefObj*)old)->mnRef == 0)
            {
                ((RefObj*)old)->mnRef = 1;
                ((RefObj*)old)->Slot0(1);
            }
        }
        ++begin;
        ++out;
    }
    return out;
}

// @ 0x00d3b430
void HeapMake(SortEntry* begin, SortEntry* end, int cmp)
{
    int n = (int)(end - begin);
    if (n < 2)
        return;
    {
        int hole = ((n - 2) >> 1) + 1;
        SortEntry* p = begin + hole;
        do
        {
            --p;
            --hole;
            void* value = p->mpObject;
            int   key = p->mnKey;
            HeapAdjust(begin, hole, n, hole, value, key, cmp);
        } while (hole != 0);
    }
}

// @ 0x00d3b480
void HeapSort(SortEntry* begin, SortEntry* end, int cmp)
{
    int n = (int)(end - begin);
    if (n <= 1)
        return;
    {
        SortEntry* p = end - 1;
        do
        {
            SortEntry tmp = *p;
            *p = *begin;
            HeapAdjust(begin, 0, n - 1, 0, tmp.mpObject, tmp.mnKey, cmp);
            --p;
            n = (int)(p - begin) + 1;
        } while (n > 1);
    }
}

// @ 0x00d3b4e0
void* cContentValidationSummarizer::ScalarDeletingDestructor(unsigned int flags)
{
    mpVtbl = &vtbl_cContentValidationSummarizer_0147abec;
    if (mpArray != 0 && mpArray[-1] != 0)
        operator_delete_array(mpArray);
    mpVtbl = &vtbl_cContentValidationSummarizer_013ec458;
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// @ 0x00d3b520
void Shuffle(SortEntry* begin, SortEntry* end, RandomLinearCongruential* rng)
{
    for (SortEntry* it = begin + 1; it < end; ++it)
    {
        uint32_t idx = rng->RandomUint32Uniform((uint32_t)(it - begin) + 1);
        SortEntry tmp = *it;
        *it = begin[idx];
        begin[idx] = tmp;
    }
}

// @ 0x00d3b5d0
SortEntry* Partition(SortEntry* begin, SortEntry* end, void* value, int key, int cmp)
{
    for (;;)
    {
        while (begin->mnKey > key)
            ++begin;
        --end;
        while (key > end->mnKey)
            --end;
        if (begin >= end)
            return begin;
        SortEntry tmp = *begin;
        *begin = *end;
        *end = tmp;
        ++begin;
    }
}

// @ 0x00d3b620
void QuickSort(SortEntry* begin, SortEntry* mid, SortEntry* end, int cmp)
{
    HeapMake(begin, mid, cmp);
    for (SortEntry* p = mid; p < end; ++p)
    {
        if (begin->mnKey < p->mnKey)
        {
            SortEntry tmp = *p;
            *p = *begin;
            HeapAdjust(begin, 0, (int)(mid - begin), 0, tmp.mpObject, tmp.mnKey, cmp);
        }
    }
    HeapSort(begin, mid, cmp);
}

// @ 0x00d3b920
cSPVector3_s00d3_b920** FUN_00d3b920(cSPVector3_s00d3_b920** cursor, cSPVectorRange range, cSPVector3_s00d3_b920* out)
{
    *cursor = out;
    while (range.mpFirst != range.mpLast) {
        cSPVector3_s00d3_b920* dst = *cursor;
        if (dst) {
            dst->mX = range.mpFirst->mX;
            dst->mStore.CopyFrom(range.mpFirst->mStore);
        }
        *cursor = *cursor + 1;
        range.mpFirst = range.mpFirst + 1;
    }
    return cursor;
}

// @ 0x00d3b970
void FUN_00d3b970(cSPVector3_s00d3_b920* dst, u32 count, const cSPVector3_s00d3_b920* src)
{
    cSPVector3_s00d3_b920* p = dst;
    while (0 < count) {
        if (p) {
            p->mX = src->mX;
            p->mStore.CopyFrom(src->mStore);
        }
        --count;
        ++p;
    }
}

// @ 0x00d3b9b0
cCreatureModeStrategy_s00d3_b920* FUN_00d3b9b0(cCreatureModeStrategy_s00d3_b920* self)
{
    self->mpVtblMode = (void*)g_vtblIModePre;
    self->mpVtblHandler = (void*)g_vtblHandlerPre;
    ((cGonzagoSubsystemBase*)self->mSubsystem)->ctor();
    self->mpVtblMode = (void*)g_vtblCreatureMode;
    self->mpVtblHandler = (void*)g_vtblCreatureModeHandler;
    *(void**)&self->mSubsystem[0] = (void*)g_vtblCreatureModeGonzago;
    *(void**)&self->mSubsystem[4] = (void*)g_vtblCreatureModeRefCount;
    self->mpField024 = 0;
    ((cGonzagoTimerBase*)self->mEnterEditorSafetyTimer)->ctor();
    self->mbField048 = 0;
    self->mbField049 = 0;
    self->mpEvoPointArray = 0;
    self->mpTexturePreload = 0;
    self->mpCreatureMissionManager = 0;
    self->mpCreatureVerbPropList = 0;
    self->mpCreaturePropList = 0;
    self->mpEditorSession = 0;
    self->mbField06c = 0;
    self->mMessageRegistration = 0;
    self->mpMsgIdArray = 0;
    self->mpMsgHandler = 0;
    self->mpMsgServer = 0;
    self->mMsgIdCount = 0;
    ((cStopwatchBase*)self->mFrameStopwatch)->ctor(0, false);
    self->mpInputStrategy = 0;
    self->mpEditorResult = 0;
    self->mField0a4 = 0xffffffff;
    self->mField0a8 = 0xffffffff;
    self->mpEditorResultData = 0;
    self->mpField0b4 = 0;
    self->mpField0b8 = 0;
    self->mpField0bc = 0;
    self->mpCreaturePaths = 0;
    self->mpField0c4 = 0;
    self->mpField0d0 = 0;
    self->mpField0d4 = 0;
    self->mpField0d8 = 0;
    self->mbField0dc = 0;
    self->mbCheckEvolution = 1;
    self->mbDelayedTransitionFromCLG = 0;
    *(u32*)&self->mPad0df[1] = 1;                  // 0x0e0
    self->mbField0e4 = 0;
    self->mbField0e5 = 0;
    self->mbField0e6 = 0;
    gStrategy = self;
    return self;
}

// @ 0x00d3bb10
void cCreatureModeStrategy_s00d3_b920::dtor()
{
    // NOTE: the member offsets are the ones the constructor writes; the releases are
    // the vtable slot-4/8 releases and the typed helpers seen in the original.
    mpVtblMode = (void*)g_vtblCreatureMode;
    mpVtblHandler = (void*)g_vtblCreatureModeHandler;
    *(void**)&mSubsystem[4] = (void*)g_vtblCreatureModeRefCount;
    *(void**)&mSubsystem[0] = (void*)g_vtblCreatureModeGonzago;
    if (mpField024)
        VT_04_0(mpField024);
    if (mpTexturePreload)
        VT_04_0(mpTexturePreload);
    if (mpCreatureMissionManager)
        VT_08_0(mpCreatureMissionManager);
    ((cVectorBase*)&mpCreaturePaths)->dtor();
    if (mpCreatureVerbPropList)
        VT_04_0(mpCreatureVerbPropList);
    if (mpCreaturePropList)
        VT_04_0(mpCreaturePropList);
    if (mMessageRegistration != 0) {
        u32 id = mMessageRegistration;
        void* server = mpMsgServer;
        void* handler = mpMsgHandler;
        void* ids = mpMsgIdArray;
        u32 count = mMsgIdCount;
        mMessageRegistration = 0;
        FUN_00571db0(id, server, handler, ids, count);
    }
    if (mpMsgIdArray)
        VT_04_0(mpMsgIdArray);
    if (mpEditorSession)
        VT_04_0(mpEditorSession);
    if (mpInputStrategy)
        VT_04_0(mpInputStrategy);
    if (mpEditorResult)
        VT_04_0(mpEditorResult);
    FUN_00b95240(0.0f, (u32)mbField0e4 | ((u32)mbField0e5 << 8) | ((u32)mbField0e6 << 16));
    if (mpEvoPointArray)
        FUN_00f47380(mpEvoPointArray);
    if (mpField0d4)
        VT_04_0(mpField0d4);
    ((cGonzagoTimerBase*)mEnterEditorSafetyTimer)->dtor();
    ((cGonzagoSubsystemBase*)mSubsystem)->dtor();
}

// @ 0x00d3bdb0
void FUN_00d3bdb0(char enable)
{
    u32 i = 0;
    if (gModes.mpPreviousAudio != 0) {
        VT_0C_1(gModes.mpPreviousAudio, enable != 0);
        void* p = gModes.mpPreviousAudio;
        gModes.mpPreviousAudio = 0;
        VT_04_0(p);
    }
    if (enable != 0 && gModes.mpSoundIds != gModes.mpSoundIdsEnd) {
        u32 count = (u32)(gModes.mpSoundIdsEnd - gModes.mpSoundIds);
        do {
            u32 id = gModes.mpSoundIds[i];
            void* sys = EA_Audio_GetSystemAT();
            if (sys) {
                VT_38_1(sys, 0x347536b);
                VT_40_1(sys, 0x3475385, id);
                VT_40_1(sys, 0x34753a0, 1);
                VT_58_0(sys);
            }
            ++i;
        } while (i < count);
        u32* begin = gModes.mpSoundIds;
        u32* end = gModes.mpSoundIdsEnd;
        FUN_00594870(begin, end, 0);
        gModes.mpSoundIdsEnd = end - (end - begin);
        gModes.mbNeedsSoundFlush = 0;
    }
}

// @ 0x00d3c380
void cCreatureModeStrategy_s00d3_b920::Deactivate()
{
    void* a = FUN_0067caf0();
    ((cDeactivateNotifyA*)a)->Notify();
    void* b = FUN_00b3d240(0);
    ((cDeactivateNotifyB*)b)->Notify();
    void* c = FUN_00b3d240(0);
    ((cDeactivateNotifyC*)c)->Notify();
    FUN_00d3bea0();
}

// @ 0x00d3c430
void FUN_00d3c430()
{
    // NOTE: the original builds the minimap window and the name banner.  Only the
    // window lookups could be identified; the reconstruction is incomplete.
    FUN_0093b6c0();
    FUN_008105b0();
    FUN_009512c0();
    FUN_009512d0();
    FUN_00e0fc90();
    FUN_00e0be50();
    FUN_01021260();
    FUN_00c707e0();
}

// @ 0x00d3c6a0
void FUN_00d3c6a0()
{
    // NOTE: the original queries the avatar noun, its position and the planet name to
    // build the editor transition request; only the lookup sequence is reproduced.
    FUN_00b3d300();
    FUN_00b1fdb0();
    FUN_00c04590();
    FUN_00d51660();
    FUN_00d4d6c0();
    FUN_00c6acc0();
    FUN_00c6ee40();
    FUN_00bc3130();
}

// @ 0x00d3d870
namespace SP {
void LoadCreatureGameplayTuning(uint32_t groupID, uint32_t instanceID)
{
    PropertyListPtr pl;

    if (groupID == 0xad56080c) {
        pl = GetTerrainMgr()->Fn1(kTerrainTuningKeys + 1, NounManager_s00d3_d870()->GetCurrentTerrainSphere() != 0);
    } else {
        PropertyManager()->GetPropertyList(instanceID, groupID, pl);
    }

    if (pl) {
        int seconds = 0;
        GetInt(pl, 0x9226de4cu, seconds);
        g_01582df8 = seconds * 1000;
        GetFloat(pl, 0xbaf251a1u, g_01582df0);
        GetBool(pl, 0x9040f372u, g_01582df4);
        GetFloat(pl, 0x724289feu, g_01582e00);
        GetFloat(pl, 0xad0d6a72u, g_01582e04);
        GetFloat(pl, 0xd02942aau, g_01582e08);
        GetFloat(pl, 0x2beb6558u, g_01582e0c);
        GetFloat(pl, 0x2acbad8u, g_01582e10);
        GetFloat(pl, 0x9a4955ddu, g_01582e14);
        GetFloat(pl, 0xffca7ffu, g_01582e18);
        GetFloat(pl, 0x511b50d8u, g_01582e1c);
        GetUInt(pl, 0x31d51f1du, g_01582e20);
        GetUInt(pl, 0x723bbffcu, g_01582e24);
        GetFloat(pl, 0xd3d10a58u, g_01582e28);
        GetFloat(pl, 0xd6e7812fu, g_01582e2c);
        GetFloat(pl, 0x31b148ccu, g_01582e30);
        GetFloat(pl, 0x11b148cdu, g_01582e34);
        GetFloat(pl, 0x31d515aeu, g_0169e278);

        int count = 0;
        float* values = 0;
        if (GetPropertyAsFloatArray(pl, 0xe39b27bfu, count, values)) {
            g_0169e35c.resize(count);
            for (int i = 0; i < count; i++)
                g_0169e35c[i] = values[i];
        }

        GetFloat(pl, 0xb67c4f9au, g_01582f88);
        GetFloat(pl, 0xf5c2bf12u, g_01582f8c);
        GetFloat(pl, 0x3964a33du, g_01582f90);
        GetFloat(pl, 0x11074694u, g_01582e38);
        GetFloat(pl, 0x2c73027u, g_01582e3c);
        GetFloat(pl, 0x2c73028u, g_01582e40);
        GetFloat(pl, 0x2c73029u, g_01582e44);
        GetFloat(pl, 0x12292735u, g_0169e27c);
        GetFloat(pl, 0x32292736u, g_01582e48);
        GetFloat(pl, 0x92292737u, g_01582e4c);
        GetFloat(pl, 0x12292738u, g_01582e50);
        GetFloat(pl, 0x8c248961u, g_01582e54);
        GetInt(pl, 0xf15cd7e4u, g_01582e58);
        GetInt(pl, 0x51cbead0u, g_01582e5c);
        g_01582e58 *= 1000;
        g_01582e5c *= 1000;

        GetFloat(pl, 0x7163782eu, g_01582e74);
        GetFloat(pl, 0x48a66eau, g_01582e60);
        GetFloat(pl, 0x48a66eeu, g_01582e64);
        GetFloat(pl, 0x6284c0cu, g_01582e68);
        GetFloat(pl, 0x1269b5b5u, g_0169e280);
        GetFloat(pl, 0x7af7926u, g_01582e6c);
        GetFloat(pl, 0x75bb1b3cu, g_0169e284);
        GetFloat(pl, 0x284e6c1u, g_01582e70);
        GetFloat(pl, 0x523a480eu, g_01582e88);
        GetFloat(pl, 0x1ad0639u, g_01582e78);
        GetFloat(pl, 0x1c2301bu, g_01582e84);
        GetFloat(pl, 0x25476fcu, g_01582e7c);
        GetFloat(pl, 0x95f7ee0cu, g_01582e80);
        GetFloat(pl, 0x967f9546u, g_01582ed4);
        GetFloat(pl, 0x4bc7f666u, g_0169e288);
        GetFloat(pl, 0xad530307u, g_01582ed8);
        GetFloat(pl, 0xb5531079u, g_01582edc);
        GetFloat(pl, 0xeeaa8367u, g_01582ee0);
        GetFloat(pl, 0x8b1fd1f1u, g_01582ee4);
        GetFloat(pl, 0x13138bd2u, g_01582ebc);
        GetFloat(pl, 0xb070eba6u, g_01582ec0);
        GetUInt(pl, 0xff7d4a77u, g_01582ee8);
        GetFloat(pl, 0x3da92194u, g_01582eec);
        GetFloat(pl, 0x687fbcecu, g_01582ef0);
        GetFloat(pl, 0xdf6747c9u, g_01582ef4);
        GetFloat(pl, 0x516e7b63u, g_01582ef8);
        GetBool(pl, 0xa5e247f0u, g_01582df5);
        GetFloat(pl, 0x18ce7bc3u, g_01582efc);
        GetUInt(pl, 0x3194b523u, g_01582f00);
        GetUInt(pl, 0x2f343a3cu, g_01582f04);
        GetFloat(pl, 0xa5b8d733u, g_01582f08);
        GetFloat(pl, 0xe1532d2du, g_01582f0c);
        GetUInt(pl, 0x5c68a779u, g_01582f10);
        GetUInt(pl, 0xfb2020b9u, g_01582f14);
        GetFloat(pl, 0x95e575c6u, g_01582f18);
        GetFloat(pl, 0x770f1ac5u, g_01582f1c);
        GetFloat(pl, 0xa1247843u, g_01582f20);
        GetFloat(pl, 0x93110e94u, g_01582f24);
        GetFloat(pl, 0x3215f0afu, g_01582f28);
        GetFloat(pl, 0x25e6ad1cu, g_01582f2c);
        GetPropertyAsVector2(pl, 0xd0fc1cacu, g_01583330);
        GetFloat(pl, 0xe11cb6ccu, g_01582f30);
        GetInt(pl, 0xdb370fb5u, g_01582f34);
        GetFloat(pl, 0xbf5e5d72u, g_01582f38);
        g_01582f38 = g_01582f38 * g_01582f38;
        GetFloat(pl, 0x65525b4eu, g_01582f3c);
        GetFloat(pl, 0x6459830bu, g_01582f40);
        GetFloat(pl, 0xfd87b588u, g_01582f44);
        g_01582f44 = g_01582f44 * g_01582f44;
        GetFloat(pl, 0xbcf97143u, g_01582f48);
        GetFloat(pl, 0xcff3e974u, g_01550aa8);
        GetFloat(pl, 0x3fbd28e4u, g_01550aac);
        GetPropertyAsVector3(pl, 0x99646e30u, g_01583338);
        GetUInt(pl, 0x37ae622u, g_01582f4c);
        g_01582f4c = min_(g_01582f4c, (uint32_t)2);
        GetFloat(pl, 0x3da2a2d2u, g_01582f50);
        GetFloat(pl, 0xe6f2fce8u, g_01582f54);
        GetFloat(pl, 0xceb65676u, g_01582f58);
        GetFloat(pl, 0xce78e0d8u, g_01582f5c);
        GetFloat(pl, 0x274fc6e0u, g_01582f60);
        GetBool(pl, 0xf7e9bdeeu, g_01582df6);
        GetFloat(pl, 0x5e352b93u, g_01582f64);
        GetFloat(pl, 0xa6a4f0bu, g_0169e28c);
        GetFloat(pl, 0x41752dd5u, g_01582f68);
        GetFloat(pl, 0xda14d908u, g_01582f6c);
        GetFloat(pl, 0x90c1b65cu, g_01582f70);
        GetFloat(pl, 0xa3e580f3u, g_01582f74);
        GetFloat(pl, 0x4e229d3eu, g_01582f78);
        GetFloat(pl, 0x832f6d3du, g_01582f7c);
        GetFloat(pl, 0x553c6e30u, g_01582f80);
        GetFloat(pl, 0x4d5f54b6u, g_01582f84);
        GetFloat(pl, 0x5933f8f4u, g_01582fa4);
        GetFloat(pl, 0x397b295au, g_01582fa8);
        GetBool(pl, 0x42b6c4b6u, g_0169e291);
        GetInt(pl, 0x22e5d26bu, g_01582fac);
        GetInt(pl, 0x22e5d268u, g_01582fb0);
        GetInt(pl, 0x22e5d269u, g_01582fb4);
        GetFloat(pl, 0x94a76e85u, g_01582fb8);
        GetFloat(pl, 0x196c4280u, g_01582fbc);
        GetFloat(pl, 0xdcbc7c1eu, g_01582fc0);
        GetInt(pl, 0xbcfd2a42u, g_01582fc4);
        GetInt(pl, 0xbcfd2a41u, g_01582fc8);
        GetInt(pl, 0xbcfd2a40u, g_01582fcc);
        GetInt(pl, 0xbcfd2a47u, g_01582fd0);
        GetInt(pl, 0xbcfd2a46u, g_01582fd4);
        GetFloat(pl, 0x9efa4612u, g_01582fd8);
        GetFloat(pl, 0x7195edf1u, g_01582eb0);
        GetUInt(pl, 0xac640ba9u, g_01582eb4);
        GetUInt(pl, 0x1d7441c9u, g_01582eb8);
        GetUInt(pl, 0x1810c6e0u, g_01582f94);
        GetUInt(pl, 0x6a86c027u, g_01582f98);
        GetFloat(pl, 0x954f8dccu, g_01582f9c);
        GetFloat(pl, 0xdcd5e42eu, g_01582fa0);
        GetBool(pl, 0xc3fff105u, g_0169e290);
        GetFloat(pl, 0x600e59cdu, g_01582fdc);
        GetFloat(pl, 0xa2433d86u, g_01582fe0);
        GetFloat(pl, 0xdb821babu, g_01582fe4);
        GetFloat(pl, 0x3d73d3b0u, g_01582fe8);
        GetFloat(pl, 0x39697de6u, g_01582fec);
        GetFloat(pl, 0x89e27397u, g_01582e8c);
        GetFloat(pl, 0xdec48a8fu, g_01582ff0);
        GetFloat(pl, 0xdcc9694fu, g_01582ff4);
        GetFloat(pl, 0x7dc0a48au, g_01582ff8);

        LoadCreatureModeExtraTuning(pl);
        cCreatureModeTuning::LoadPrivateTuningVariables(pl);
    }

    spInstance_cCreatureModeStrategy_s00d3_d870->mpTuning = pl;

    if (PropertyManager()->GetPropertyList(0xb2bd78ca, groupID, pl)) {
        TryGetUIntProperty(pl, 0xb136a2d1u, g_01582ec4);
        TryGetUIntProperty(pl, 0xb136a2d2u, g_01582ec8);
        GetFloatProperty(pl, 0xe8ad4f2du, g_01582ecc);
        GetFloatProperty(pl, 0x4453df5du, g_01582ed0);
    }

    spInstance_cCreatureModeStrategy_s00d3_d870->mpTuning2 = pl;
    ReloadModifierTuning();
}
}  // namespace SP

// @ 0x00d3f9e0
void NodePool::FreeLists(Node** arr, unsigned count)
{
    for (unsigned i = 0; i < count; ++i) {
        Node* n = arr[i];
        if (n != 0) {
            do {
                Node* cur = n;
                n = n->mpNext;
                NodeBuf* buf = &cur->mBuf;
                buf->Reset(buf->mpData, buf->miCount);
                if (buf->mpData != 0 && *(int*)((char*)buf->mpData - 4) != 0)
                    op_delete_array(buf->mpData);
                if (cur->mpRef != 0)
                    ((TFnV)VT(cur->mpRef, 4))(cur->mpRef);
                if (cur != this->mpSentinel) {
                    if (cur < this->mpPoolBegin || cur >= this->mpPoolEnd)
                        op_delete_array(cur);
                    else {
                        *(Node**)cur = this->mpFreeList;
                        this->mpFreeList = cur;
                    }
                }
            } while (n != 0);
        }
        arr[i] = 0;
    }
}

// @ 0x00d3fa90
void Vec18Vec::InsertN(Vec18* pos, unsigned n, const Vec18* val)
{
    unsigned have = (unsigned)(this->mpEnd - this->mpBegin);
    if (n > have) {
        unsigned size = have;
        unsigned cap = size * 2;
        if (size == 0)
            cap = 1;
        unsigned want = size + n;
        if (want < cap)
            want = cap;
        Vec18* buf = 0;
        if (want != 0)
            buf = (Vec18*)op_new(want * 0x18, "Simulator", 0, 0, (const char*)0x013ebb38, 0xd1);
        Vec18* dst = (Vec18*)FUN_00b96900(this->mpBegin, pos, buf);
        FUN_00b93d80(this->mpBegin, pos, buf);
        FUN_00d3b970(dst, n, val, dst);
        Vec18* tailDst = dst + n;
        Vec18* oldEnd = this->mpEnd;
        void* newEnd = FUN_00b96900(pos, oldEnd, tailDst);
        FUN_00b93d80(pos, oldEnd, tailDst);
        if (this->mpBegin != 0 && *(int*)((char*)this->mpBegin - 4) != 0)
            op_delete_array(this->mpBegin);
        this->mpBegin = buf;
        this->mpEnd = (Vec18*)newEnd;
        this->mpCap = buf + want;
        return;
    }

    if (n == 0)
        return;

    void* raw = pos;
    unsigned off = (unsigned)(pos - this->mpBegin);
    unsigned avail = have - off;
    Vec18 tmp;
    tmp.mWeight = val->mWeight;
    tmp.mVectors.Ctor(&val->mVectors);

    if (n < avail) {
        FUN_00d3b920(&raw, this->mpEnd - n, this->mpEnd, this->mpEnd, 0);
        this->mpEnd += n;
        FUN_00b97500(pos, this->mpEnd - n, this->mpEnd);
        for (Vec18* e = pos; e != pos + n; ++e) {
            e->mWeight = tmp.mWeight;
            e->mVectors.Assign(&tmp.mVectors);
        }
    } else {
        FUN_00d3b970(this->mpEnd, n - avail, &tmp, this->mpEnd);
        this->mpEnd += n - avail;
        FUN_00d3b920(&raw, pos, this->mpEnd - n + avail, this->mpEnd, 0);
        this->mpEnd += avail;
        for (Vec18* e = pos; e != pos + n; ++e) {
            e->mWeight = tmp.mWeight;
            e->mVectors.Assign(&tmp.mVectors);
        }
    }
    if (tmp.mVectors.mBegin != 0 && *(int*)(tmp.mVectors.mBegin - 4) != 0)
        op_delete_array((void*)tmp.mVectors.mBegin);
}

// @ 0x00d3fcf0
void __cdecl FUN_00d3fcf0()
{
    SP_NounManager()->GetCurrentTerrainSphere();
    void* av = SP_NounManager()->GetAvatar();
    FUN_00d2e380(-1);

    int level = ((TFnI)VT(av, 0xd8))(av);
    int mode = FUN_00d2e830();
    ((TFnVI)VT(av, 0xdc))(av, mode);

    void* ms = SP_MessageServer();
    ((TFnVIII)VT(ms, 0x14))(ms, 0x6579712, 0x24947c07, 0);

    void* ps = SP_PosseSimulatorInstance();
    if (ps != 0) {
        unsigned l = (unsigned)((TFnI)VT(av, 0xd8))(av);
        int* slot = (int*)((char*)ps + 0x18);
        if (l > *(unsigned*)slot)
            *slot = (int)l;
    }

    float fa = FUN_00c0b440(mode);
    float fb = FUN_00c0b440(level);
    float fc = FUN_00d2e800(0);
    FUN_00d2e720();
    float fd = FUN_00d2e800(0);
    float scale = (fa / fb) / fc * fd;

    NounVec_s00d3_f9e0* vec = SP_NounManager()->GetGameDataVector(0x00cd7d10, 0x00d3d420, 0x00ace0f0,
                                                       0x00b1e500, 0x018eb45e);
    unsigned num = (unsigned)(vec->mpEnd - vec->mpBegin);
    for (unsigned i = 0; i < num; ++i) {
        char* n = (char*)vec->mpBegin[i];
        if (n == 0 || n[0x135] == 0)
            continue;
        if (*(int*)(n + 0xb20) != *(int*)((char*)av + 0xb20))
            continue;
        if (n == (char*)av)
            continue;
        float f = ((TFnF)VT(n + 0x5a8, 0x58))(n + 0x5a8);
        FUN_00f924e0(f);
        char* obj = n + 0xc0;
        float a = ((TFnF)VT(obj, 0x34))(obj);
        ((TFnVI)VT(obj, 0x40))(obj, a * scale);
        ((TC_V)0x00c0bbe0)(n);
    }

    char* body = (char*)av + 0x5a8;
    float f0 = ((TFnF)VT(body, 0x58))(body);
    FUN_00f924e0(f0);
    ((TC_VF)0x00c0b9d0)(av, *(float*)0x01687a00);

    ((TC_VIFIIII)0x00c03190)(av, 0x1000, *(float*)0x0147aaa8, level, 0, 0, 0);

    char* obj = (char*)av + 0xc0;
    float f1 = ((TFnFI)VT(av, 0x80))(av, 0);
    ((TFnVI)VT(obj, 0x40))(obj, f1);
    ((TC_V)0x00c0bbe0)(av);

    if (mode != 0) {
        void** it = *(void***)(mode + 0xbc);
        void** end = *(void***)(mode + 0xc0);
        for (; it != end; ++it)
            ((TFnVI)VT(*it, 0x18))(*it, 0x49b56d7);
        if (*(int*)(mode + 0x68) != 0) {
            FUN_00d2b6e0(0x6455b55, 0);
            FUN_00d2b6e0(0x652a628, 0);
        }
    }

    FUN_00ba5e10(av, 7);

    struct { int a, b, c; } m1 = { 0, 0, 0 };
    struct { int a, b, c; } m2 = { 0, 0, 0 };
    void* res = 0;
    void* msg = FUN_00c0bc00(&res, &m1, &m2);
    FUN_00e39710(0xf00048a9, msg);

    const char* trigger = 0;
    switch (level) {
    case 1: trigger = (const char*)0x0147ab14; break;   // "CRG_BrainUpgrade1"
    case 2: trigger = (const char*)0x0147ab00; break;   // "CRG_BrainUpgrade2"
    case 3: trigger = (const char*)0x0147aaec; break;   // "CRG_BrainUpgrade3"
    case 4: trigger = (const char*)0x0147aad8; break;   // "CRG_BrainUpgrade4"
    }
    ((TC_VIPIIII)0x00ae0930)(SP_GetTriggerMgr(), trigger, 1, 1, 0, 0, 0);
}

// @ 0x00d400e0
bool Scenario::EvalTrigger(int event, int* ctx)
{
    bool isAvatar = false;
    if (ctx[0] != 0) {
        void* av = SP_NounManager()->GetAvatar();
        isAvatar = (ctx[0] == (int)(size_t)av);
    }

    int value;
    if (event == 0x053f0369) {
        value = 2;
        void* av = SP_NounManager()->GetAvatar();
        if (av != 0) {
            int level = ((TFnI)VT(av, 0xd8))(av);
            bool atMax = (level == 4);
            value = 1;
            if (!atMax)
                value = 2;
        }
    } else if (event == 0x055a7128) {
        void* sphere = SP_NounManager()->GetCurrentTerrainSphere();
        void* av = SP_NounManager()->GetAvatar();
        if (av == 0 || sphere == 0)
            return false;
        int level = ((TFnI)VT(av, 0xd8))(av);
        if (level <= 0)
            return false;
        int r = FUN_00d38800(level);
        if (((TC_II)0x00ad7db0)(SP_GetTriggerMgr(), r) != ctx[2])
            return false;
        if (level != 4)
            return false;
        value = 1;
        isAvatar = true;
    } else if (event == 0x533535dd) {
        if (*(char*)(0x0169e294 + 0xde) == 0) {
            value = 2;
        } else {
            FUN_00d3fcf0();
            void* sphere = SP_NounManager()->GetCurrentTerrainSphere();
            ((TC_VII)0x00c79f00)(sphere, 0x03a8d77c, 3);
            return true;
        }
    } else {
        return false;
    }

    void* sphere = SP_NounManager()->GetCurrentTerrainSphere();
    if (sphere != 0 && isAvatar)
        ((TC_VII)0x00c79f00)(sphere, 0x03a8d77c, value);
    return true;
}

// @ 0x00d40230
int Scenario::EvaluateEvent(float dt)
{
    void* av = SP_NounManager()->GetAvatar();
    if (av == 0) {
        ((TFnV)VT(this, 0x14))(this);
        return 0;
    }

    if (this->miState == 1) {
        if ((*(unsigned*)((char*)av + 0x110) & 0x100) == 0 &&
            *(int*)(*(int*)((char*)av + 0xb4c) + 0x1d8) != 0x03845d9d) {
            this->StartDeathCutScreen(this->miTag);

            SP_NounManager()->GetAvatar();
            float prop = 1.0f;
            FUN_0040cf10(*(void**)(0x0169e294 + 0xb4), 0x57ae947d, &prop);
            float t = FUN_00d2e350() * prop;
            FUN_00d2e480(t);

            void* sphere = SP_NounManager()->GetCurrentTerrainSphere();
            float one = *(float*)0x01485720;               // 1.0f
            FUN_0040cf10(*(void**)(0x0169e294 + 0xb4), 0x98c83c48, &one);
            float cur = *(float*)((char*)sphere + 0x10f0);
            float d = FUN_011e08c2(one);
            *(float*)((char*)sphere + 0x10f0) = cur - d;
        }
    } else if (this->miState == 2) {
        TriggerMgr* tm = SP_GetTriggerMgr();
        if (tm->miState == 2)
            this->miState = 3;
    } else if (this->miState == 3) {
        TriggerMgr* tm = SP_GetTriggerMgr();
        if (tm->miState != 1 && tm->miState != 2)
            ((TFnV)VT(this, 0x14))(this);
    }

    int st = ((TFnI)VT(av, 0xa4))(av);
    if ((unsigned)(st - 4) <= 1) {
        float old = this->mfTimer;
        this->mfTimer = old - dt;
        if (old - dt < 0.0f) {
            this->mfTimer = *(float*)0x01486110;           // 5.0f

            V3* from = (V3*)((TFnPU)VT((char*)av + 0xc0, 0x2c))((char*)av + 0xc0);
            float best = *(float*)0x0147aaa8;              // FLT_MAX
            float bestObj = 0.0f;
            void* setting = FUN_00401090();
            ((TC_V)0x004df420)(setting);
            NounVec_s00d3_f9e0* vec = (NounVec_s00d3_f9e0*)((TC_P)0x00bc0710)(SP_NounManager());
            void** it = vec->mpBegin;
            void** end = vec->mpEnd;
            if (it != end) {
                do {
                    char* n = (char*)*it;
                    if (n[0xa9] != 0) {
                        V3* p = (V3*)((TFnPU)VT(n + 0x34, 0x2c))(n + 0x34);
                        float dx = from->x - p->x;
                        float dy = from->y - p->y;
                        float dz = from->z - p->z;
                        float d2 = (dz * dz + dy * dy) + dx * dx;
                        if (d2 < best && ((TC_I)0x00c6aa50)(n) != 0) {
                            best = d2;
                            bestObj = (float)(size_t)n;
                        }
                    }
                    ++it;
                } while (it != end);

                if (bestObj != 0.0f) {
                    char* target = (char*)(size_t)bestObj;
                    TransformMsg msg;
                    ((TC_V)0x00434040)(&msg);

                    V3* tpos = (V3*)((TFnPU)VT(target + 0x34, 0x2c))(target + 0x34);
                    ((TC_VPP)0x00d3b0c0)((void*)0x0169e294, &msg.mTranslation, tpos);

                    msg.mFlags0 |= 4;
                    msg.mCount0 += 1;

                    void* rot = ((TFnPU)VT(target + 0x34, 0x30))(target + 0x34);
                    void* m = ((TC_PP)0x0059c190)(&msg.mRotation, rot);
                    for (int k = 0; k < 9; ++k)
                        msg.mRotation.m[k] = ((float*)m)[k];

                    msg.mFlags1 |= 2;
                    msg.mCount1 += 1;

                    if (this->mpEffect != 0) {
                        ((TFnVP)VT(this->mpEffect, 0x18))(this->mpEffect, &msg);
                        return 1;
                    }

                    int flag = *(int*)(*(int*)((char*)av + 0xb20) + 0x618);
                    void* fx = SP_EffectsManager();
                    if (this->mpEffect != 0) {
                        void* oldFx = this->mpEffect;
                        this->mpEffect = 0;
                        ((TFnV)VT(oldFx, 4))(oldFx);
                    }
                    int effectId = (-(int)(flag == 0) & 0x8c9af24f) + 0xbed2ad51;
                    int ok = ((TFnIIP)VT(fx, 0x2c))(fx, effectId, 0, &this->mpEffect);
                    if (ok != 0) {
                        ((TFnVIP)VT(this->mpEffect, 0x44))(this->mpEffect, 5,
                                                           (char*)av + 0xb20 + 0x4ec, 3);
                        ((TFnVP)VT(this->mpEffect, 0x18))(this->mpEffect, &msg);
                        ((TFnVI)VT(this->mpEffect, 8))(this->mpEffect, 0);
                        return 1;
                    }
                }
            }
        }
    } else if (this->mpEffect != 0) {
        void* oldFx = this->mpEffect;
        ((TFnVI)VT(oldFx, 0xc))(oldFx, 1);
        if (this->mpEffect != 0) {
            this->mpEffect = 0;
            ((TFnV)VT(oldFx, 4))(oldFx);
        }
    }
    return 1;
}

// @ 0x00d40640
int Scenario::Finish()
{
    if (this->mpEffect != 0) {
        void* oldFx = this->mpEffect;
        ((TFnVI)VT(oldFx, 0xc))(oldFx, 1);
        if (this->mpEffect != 0) {
            this->mpEffect = 0;
            ((TFnV)VT(oldFx, 4))(oldFx);
        }
    }

    if (this->miState == 3) {
        void* editor = ((TC_P)0x00ac84d0)(FUN_00b3d480(1));
        void* planet = SP_PlanetModel();
        NounVec_s00d3_f9e0* vec = SP_NounManager()->GetGameDataVector(0x00cd7d10, 0x00d3d420, 0x00accc30,
                                                           0x00b1e500, 0x01be418e);
        void** it = vec->mpBegin;
        void** end = vec->mpEnd;
        while (it != end) {
            char* n = (char*)*it;
            if (((TC_I)0x00c6a020)(n) != 0 && *(int*)(n + 0x15c) != 9) {
                TransformMsg msg;
                msg.mFlags0 = 0;
                msg.mCount0 = 0;
                msg.mTranslation.x = *(float*)0x0169e298;
                msg.mTranslation.y = *(float*)0x0169e29c;
                msg.mTranslation.z = *(float*)0x0169e2a0;
                msg.mFlags1 = 0;
                msg.mCount1 = 0;
                ((TC_VP)0x0041cb40)(&msg.mRotation, (void*)0x0169e3c0);

                cSPTransform_s00d3_f9e0 xf;
                xf.mT.mFlags0 = 0;
                xf.mT.mCount0 = 0;
                xf.mT.mTranslation.x = *(float*)0x0169e298;
                xf.mT.mTranslation.y = *(float*)0x0169e29c;
                xf.mT.mTranslation.z = *(float*)0x0169e2a0;
                xf.mT.mFlags1 = 0;
                xf.mT.mCount1 = 0;
                xf.mT.mRotation = msg.mRotation;
                xf.mScale = *(float*)0x01485720;           // 1.0f

                V3* pos = (V3*)((TC_P)0x00c6acc0)(n);
                msg.mTranslation = *pos;
                msg.mFlags0 |= 4;
                msg.mCount0 += 1;

                void* ori = ((TC_PPP)0x00b7f190)(planet, &xf.mT.mRotation, ((TC_P)0x00c6acc0)(n));
                void* q = FUN_004a9b40(&xf.mT.mRotation, ori);
                msg.mFlags1 |= 2;
                msg.mCount1 += 1;
                xf.Assign(&msg);

                int num = (int)((*(char**)(n + 0x44) - *(char**)(n + 0x40)) / 4);
                for (int i = 0; i < num; ++i) {
                    char* sub = *(char**)(*(char**)(n + 0x40) + i * 4);
                    ((TFnVI)VT(sub + 0x5a8, 0x2c))(sub + 0x5a8, 1);
                    if (((TFnI)VT(sub, 0xd0))(sub) != 0)
                        continue;
                    ((TFnVPPP)VT(editor, 0x10))(editor, &msg, &xf, &msg);
                    void* qq = FUN_00472b80(&xf.mT.mRotation, &xf.mT.mTranslation, 0.0f);
                    M33 m;
                    for (int k = 0; k < 9; ++k)
                        m.m[k] = ((float*)qq)[k];
                    ((TFnVP)VT(sub + 0xc0, 0x44))(sub + 0xc0, &m);
                }
            }
            ++it;
        }
    }

    this->miState = 0;
    this->mfTimer = 0.0f;
    return 1;
}

// @ 0x00d40e70
void FUN_00d40e70(void)
{
    cTriggerMgr_s00d4_0930* tm = (cTriggerMgr_s00d4_0930*)GetTriggerMgr_s00d4_0930();
    void* handle = tm->PostTrigger("CRG_SpeciesMigrate", 1, 1, 0, 0, 0);

    cGameNounManager_s00d4_0930* nm = (cGameNounManager_s00d4_0930*)NounManager_s00d4_0930();
    void* avatar = nm->GetAvatar();
    cAvatarHerd* herd = (cAvatarHerd*)GetAvatarHerd(avatar);

    void** end = herd->mAnimalEnd;
    for (void** it = herd->mAnimalBegin; it != end; it++) {
        cHerdObj* obj = (cHerdObj*)*it;
        if (obj->mOwner == 0) {
            continue;
        }
        cSubObj* sub = (cSubObj*)obj->mOwner;
        if (!sub->mTarget->IsEligible()) {
            continue;
        }
        if (obj->mKind != 5) {
            continue;
        }
        obj->mField1F0 = 0x7fffffff;
        if (obj->mOwner != avatar) {
            continue;
        }
        cActionTarget target((const void*)((char*)obj + 0x34), handle);
        tm->PostAction(0x28930a2c, &target);
    }

    cHerdObj* best = (cHerdObj*)GetDesiredAvatarHerd(1);

    void* posA = herd->mNest ? (char*)herd->mNest + 0x34 : 0;
    cActionTarget targetA(posA, handle);
    tm->PostAction(0x6049a108, &targetA);

    void* posB = best->mNest ? (char*)best->mNest + 0x34 : 0;
    cActionTarget targetB(posB, handle);
    tm->PostAction(0x9667d819, &targetB);

    cDOMNode* node = (cDOMNode*)GetUIRoot();
    void* parent = node->GetParent();
    void* posC = parent ? (char*)parent + 0xc0 : 0;
    cActionTarget targetC(posC, handle);
    ((cTriggerMgr_s00d4_0930*)GetTriggerMgr_s00d4_0930())->PostAction(0x927b68d9, &targetC);
}

// @ 0x00d414e0
void __stdcall FUN_00d414e0(uint32_t tuningId)
{
    switch (tuningId - 0x01654c01) {
    case 0: LoadCreatureGameplayTuning(0xad56080c, 0x7c340397); return;
    case 1: LoadCreatureGameplayTuning(0x00000000, 0x7c340397); return;
    case 2: LoadCreatureGameplayTuning(0x02ae0c7e, 0x7c340397); return;
    case 3: LoadCreatureGameplayTuning(0xf71fa311, 0x7c340397); return;
    case 4: return;
    }
}

// @ 0x00d425f0
void __cdecl sUpdateMinimap(float dt)
{
    cAvatar_s00d4_25f0* avatar = NounManager_s00d4_25f0()->GetAvatar();
    if (!avatar || !g_minimap) {
        return;
    }
    const Vec3* pos = avatar->mSub.GetPosition();
    float aggro = GetPropertyT_float(g_strategy->mpProps, 0xf7dc67f7, 100.0f);

    g_t1 = g_t1 - dt;
    bool flag = g_flag != 0;
    if (g_t1 <= 0.0f) {
        g_t1 = 5.0f;
        Vec3 v = *pos;
        float len = sqrtf((v.x * v.x + v.y * v.y) + v.z * v.z);
        if (len > 1.5258789e-05f) {
            float thr = (1.0f / len) * aggro;
            float inv = 1.0f / (len + 1.5258789e-05f);
            float dx = v.x * inv, dy = v.y * inv, dz = v.z * inv;
            const Vec3* o = g_minimap->GetOrigin();
            float ex = o->x - dx, ey = o->y - dy, ez = o->z - dz;
            if (thr * thr < (ez * ez + ey * ey) + ex * ex) {
                flag = true;
                g_minimap->SetCenter(pos);
                g_minimap->SetZoom(GetPropertyT_float(g_strategy->mpProps, 0xde67264f, 0.99f));
            }
        }
    }

    g_t2 = g_t2 - dt;
    if (g_t2 <= 0.0f || flag) {
        g_t2 = 2.5f;
        cProfile* profile = FUN_00401090_s00d4_25f0()->GetAvatarProfile();
        cOwner* herd = GetDesiredAvatarHerd(0);
        float ratio = aggro / PlanetModel()->GetRadius();
        float range2 = ratio * ratio;
        const Vec3* cam = g_minimap->GetOrigin();
        cGameDataResult* list = NounManager_s00d4_25f0()->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00bbf9b0,
                                                                  FUN_00b1e500, 0x52aa6122);
        void** end = list->mpEnd;
        for (void** it = list->mpBegin; it != end; ++it) {
            cMiniObj* e = (cMiniObj*)*it;
            cOwner* owner = e->mpOwner;
            if (owner != avatar->GetInfo()) {
                cOwner* o2 = e->mpOwner;
                if (g_169e370 < o2->mRangeMin || g_169e370 > o2->mRangeMax) {
                    continue;
                }
            }
            cSpatialObject* sp = &e->mSub;
            const Vec3* p = sp->GetPosition();
            float px = p->x, py = p->y, pz = p->z;
            float n = 1.0f / sqrtf(((px * px + py * py) + pz * pz) + 1e-08f);
            float qx = px * n - cam->x, qy = py * n - cam->y, qz = pz * n - cam->z;
            float d2 = (qz * qz + qy * qy) + qx * qx;
            if (!(range2 > d2) && e->mpOwner != herd) {
                if (!e->mFlagA9 || sp->IsHidden()) {
                    g_minimap->RemoveIcon(e, 1, 0);
                    continue;
                }
            }
            uint32_t flags = (e->mFlags124 & 1) ? 0x20 : 0x80020;
            bool sel = false;
            cOwner* ow = e->mpOwner;
            if (ow->mFlag191 || ow->mProfile == (int)profile) {
                flags |= 0x200000;
            }
            if (ow->mFlag190) {
                flags |= 0x100000;
            }
            if (ow == herd || sp->IsHidden()) {
                flags |= 8;
                sel = e->mpOwner == herd;
            }
            cIconInfo* ic = g_minimap->FindIcon(e);
            if (ic && ic->mFlags == flags) {
                if (g_minimap->UpdateIcon(e, sp->GetPosition(), sel)) {
                    continue;
                }
            }
            g_minimap->RemoveIcon(e, 1, 0);
            cIconInfo info;
            info.mColor = 0;
            info.mPos.x = 0.0f;
            info.mPos.y = 0.0f;
            info.mPos.z = -1.0f;
            info.mFlags = flags;
            info.mTimeout = 0.0f;
            info.mAnimState = 0;
            info.m20 = 0;
            if (flags & 8) {
                if (e == herd->mpLead) {
                    cSpeciesData_s00d4_25f0* sd = avatar->mpSpecies;
                    int r = RoundToInt(sd->mR * 255.0f);
                    int g = RoundToInt(sd->mG * 255.0f);
                    int b = RoundToInt(sd->mB * 255.0f);
                    info.mColor = PackARGB(0xff, r, g, b);
                } else {
                    info.mColor = 0x7f000000;
                }
            }
            if ((flags & 0x100000) && !(flags & 0x80000)) {
                info.mColor = 0xffff0000;
            }
            info.mPos = *sp->GetPosition();
            info.mpObject.Assign(e);
            g_minimap->AddIcon(e, &info, 0, sel);
        }
    }

    Vec3 tmp;
    g_minimap->SetIconColor(pos, avatar->mSub.GetV5c(&tmp));
    if (g_flag2 || flag) {
        g_flag2 = 0;
        g_minimap->Clear(0x8000);
        cPlanetModel* pm = PlanetModel();
        int cont = pm->GetContinent(((cInfoB*)avatar->GetInfo())->GetKey());
        FixedPtrVec found;
        found.mpBegin = (void**)found.mBuf;
        found.mpEnd = found.mpBegin;
        found.mpCap = (void**)(found.mBuf + 8);
        found.mFlag = 0;
        FUN_00b3d440_s00d4_25f0()->Run(pos, aggro * 1.5f, &found, 1, 0);
        void** gb = g_list.mpBegin;
        void** ge = g_list.mpEnd;
        memmove(gb, ge, 0);
        g_list.mpEnd = g_list.mpEnd - (ge - gb);
        g_list.Reserve((uint32_t)(found.mpEnd - found.mpBegin));
        for (void** q = found.mpBegin; q != found.mpEnd; ++q) {
            if (pm->GetContinent((uint32_t)*q) == cont) {
                if (g_list.mpEnd < g_list.mpCap) {
                    void** slot = g_list.mpEnd;
                    g_list.mpEnd = slot + 1;
                    if (slot) {
                        *slot = *q;
                    }
                } else {
                    g_list.DoInsert(g_list.mpEnd, q);
                }
            }
        }
        void** lo = g_list.mpBegin;
        void** hi = g_list.mpEnd - 1;
        while (lo < hi) {
            void* t = *lo;
            *lo = *hi;
            *hi = t;
            ++lo;
            --hi;
        }
        if (found.mpBegin && found.mpBegin[-1]) {
            operator delete[](found.mpBegin);
        }
    }

    g_t3 = g_t3 - dt;
    if (g_t3 <= 0.0f) {
        g_t3 = 1.0f;
        for (unsigned int i = 0; i < 1; ++i) {
            if (g_list.mpBegin == g_list.mpEnd) {
                break;
            }
            float* item = (float*)g_list.mpEnd[-1];
            void* kind = *(void**)(item + 4);
            if (!g_minimap->UpdateIcon(kind, (const Vec3*)item, 0)) {
                cIconInfo info;
                info.mColor = 0;
                info.mPos.x = item[0];
                info.mPos.y = item[1];
                info.mPos.z = item[2];
                info.mFlags = 0x8000;
                info.mTimeout = 0.0f;
                info.mAnimState = 0;
                info.m20 = 0;
                g_minimap->AddIcon(kind, &info, 0, 0);
            }
            g_list.mpEnd = g_list.mpEnd - 1;
        }
    }
    if (flag) {
        g_flag = 0;
        g_minimap->SetMode(4);
        g_minimap->UpdateMapTexture();
    }
}

// @ 0x00d463a0
u8 __fastcall FUN_00d463a0(void* self, void* dummy, void* reader)
{
  (void)dummy;
  u32 version = 0;
  FUN_0093a780(GetStream(reader), &version, 1, 0);
  cVarListSerializer ser;
  ser.Ctor((char*)self - 8, (void*)0x15833f0, 0x1a80d26);
  if (version != 0x12191ca) return 0;
  if (!ser.Serialize(reader)) return 0;
  u32 count = 0;
  FUN_0093a780(GetStream(reader), &count, 1, 0);
  GridVec* gv = (GridVec*)((char*)self + 0x44);
  gv->Resize((s32)count);
  u32 ver = ((TFu)(*(void***)reader)[0x3c / 4])(reader);
  if (ver < 0x1e0001) {
    for (u32 i = 0; i < count; i++) {
      char* e = (char*)gv->mBegin + i * 0x18;
      SpVec3* v = (SpVec3*)(e + 4);
      *(float*)e = 1.0f;
      u32 n = 0;
      FUN_0093a780(GetStream(reader), &n, 1, 0);
      v->Resize((s32)n);
      for (u32 j = 0; j < n; j++) {
        FUN_0093a780(GetStream(reader), (char*)v->mBegin + j * 0xc, 3, 0);
      }
    }
  } else {
    for (u32 i = 0; i < count; i++) {
      char* e = (char*)gv->mBegin + i * 0x18;
      SpVec3* v = (SpVec3*)(e + 4);
      u32 n = 0;
      u32 val = 0;
      FUN_0093a780(GetStream(reader), &n, 1, 0);
      FUN_0093a780(GetStream(reader), &val, 1, 0);
      v->Resize((s32)n);
      *(u32*)e = val;
      for (u32 j = 0; j < n; j++) {
        FUN_0093a780(GetStream(reader), (char*)v->mBegin + j * 0xc, 3, 0);
      }
    }
  }
  return 1;
}

// @ 0x00d46610
void* __fastcall FUN_00d46610(HashMapC* self, void* dummy, void* a0, void* a1)
{
  (void)dummy;
  FixedPoolLocal local;
  void* pool = self->mPool138;
  local.mpHead = 0;
  ((FixedPoolC*)&local)->Init(pool, 0x6200, 0x188, 4, 0);
  local.p08 = pool;
  local.p0C = (char*)pool + 0x6200;
  local.x10 = 0x188;
  local.p14 = &self->mField34;
  void* alloc = FUN_00921340(0x40);
  void* pa1 = &a1;
  self->Construct(alloc, a0, pa1, pa1, a1, pa1, &local);
  self->mField10 = 10000.0f;
  self->mField14 = 2.0f;
  self->mField18 = 0;
  u32 n = ((PoolAllocC*)&local)->Size(self->mField0C);
  if (self->mField08 < n) self->Grow(n);
  return self;
}

// @ 0x00d466f0
u8 __fastcall FUN_00d466f0(void* self, void* dummy, void* unused)
{
  (void)dummy;
  (void)unused;
  void* nm = FUN_00b3d300();
  AvatarC* av = (AvatarC*)((NounMgrC*)nm)->GetAvatar();
  if (av != 0 && av->fB5E == 0) return 1;
  ((TFv)(*(void***)self)[0x14 / 4])(self);
  return 0;
}

// @ 0x00d46730
void __stdcall FUN_00d46730(TrigInfo* info)
{
  void* prop;

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xb10f785d, &prop) &&
      ((PropC*)prop)->mType == 10)
    info->mField4 = *((PropC*)prop)->GetUInt();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xe3771a50, &prop) &&
      ((PropC*)prop)->mType == 1)
    info->mField8 = *((PropC*)prop)->GetBool();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xbc6f60af, &prop) &&
      ((PropC*)prop)->mType == 10)
    info->mFieldC = *((PropC*)prop)->GetUInt();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0x1ebc78bf, &prop) &&
      ((PropC*)prop)->mType == 9)
    info->mField10 = *((PropC*)prop)->GetInt();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xef91ad29, &prop) &&
      ((PropC*)prop)->mType == 0xd)
    info->mField14 = *((PropC*)prop)->GetFloat();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0x2e65b70f, &prop) &&
      ((PropC*)prop)->mType == 0xd)
    info->mField18 = *((PropC*)prop)->GetFloat();

  info->mField18 = info->mField18 * info->mField18;

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0x80d91e9e, &prop) &&
      ((PropC*)prop)->mType == 10)
    info->mField1C = *((PropC*)prop)->GetUInt();

  if (info->mRef0 != 0 && ((TFbkey)(*(void***)info->mRef0)[0x24 / 4])(info->mRef0, 0xd411d542, &prop) &&
      ((PropC*)prop)->mType == 10)
    info->mField20 = *((PropC*)prop)->GetUInt();

  info->mField24 = 0;
  if (info->mRef28 != 0) {
    ((TFv1)(*(void***)info->mRef28)[0xc / 4])(info->mRef28, 0);
    void* p = info->mRef28;
    if (p != 0) {
      info->mRef28 = 0;
      ((TFv)(*(void***)p)[4 / 4])(p);
    }
  }
}

// @ 0x00d46c30
u8 __cdecl FUN_00d46c30(TrigInfo* info, void* strat, void* creature)
{
  if (info->mField24 != 0) return 0;
  if (((TFb)(*(void***)strat)[0x2c / 4])(strat)) return 0;

  switch (info->mField4) {
    case 0: {
      float f = ((char*)creature ? *(float*)((char*)creature + 0x5e0) : 0.0f) + info->mField14;
      void* c = (char*)creature + 0x5a8;
      float hi = ((TFf)(*(void***)c)[0x58 / 4])(c);
      f = (f > 0.0f) ? f : 0.0f;
      f = (f < hi) ? f : hi;
      FUN_00f924e0(c, f);
      *(float*)(*(u32*)0x169e3e8 + 0x2c) = (float)fabs(info->mField14);
      break;
    }
    case 2:
      FUN_00d2e8a0(info->mField14);
      *(float*)(*(u32*)0x169e3e8 + 0x2c) = info->mField14;
      break;
    case 3: {
      int local[3];
      local[0] = (int)creature;
      local[1] = 0;
      local[2] = (int)info->mField14;
      GlobInstC* gi = *(GlobInstC**)0x169e294;
      for (void** p = gi->mBegin; p != gi->mEnd; p++) {
        void* obj = *p;
        ((TFbmsg)(*(void***)obj)[0x18 / 4])(obj, 0xd3353635, local);
      }
      *(float*)(*(u32*)0x169e3e8 + 0x2c) = info->mField14;
      break;
    }
    case 4:
      FUN_00f924e0((char*)creature + 0x5a8, 0.0f);
      break;
    case 5: {
      int local[3];
      local[0] = (int)creature;
      local[1] = 0;
      local[2] = 0;
      GlobInstC* gi = *(GlobInstC**)0x169e294;
      for (void** p = gi->mBegin; p != gi->mEnd; p++) {
        void* obj = *p;
        ((TFbmsg)(*(void***)obj)[0x18 / 4])(obj, 0xd335363a, local);
      }
      break;
    }
    case 6: {
      s32 local[3];
      local[0] = (s32)creature;
      local[1] = 0;
      local[2] = (s32)info->mField14;
      GlobInstC* gi = *(GlobInstC**)0x169e294;
      for (void** p = gi->mBegin; p != gi->mEnd; p++) {
        void* obj = *p;
        ((TFbmsg)(*(void***)obj)[0x18 / 4])(obj, 0x5371f11, local);
      }
      break;
    }
    default:
      return 0;
  }

  if (info->mField1C != 0) {
    void* ref = 0;
    void* em = FUN_00d67dd0();
    if (ref != 0) {
      void* o = ref;
      ref = 0;
      ((TFv)(*(void***)o)[4 / 4])(o);
    }
    u8 ok = ((TFbeff)(*(void***)em)[0x2c / 4])(em, (void*)info->mField1C, 0, &ref);
    if (ok) {
      if (info->mRef28 != 0)
        ((TFv1)(*(void***)info->mRef28)[0xc / 4])(info->mRef28, 0);
      FUN_00ac9480(&info->mRef28, &ref);
      void* obj = FUN_00b18e00(strat);
      if (obj == 0) obj = (creature != 0) ? (void*)((char*)creature + 0xc0) : 0;
      XformMsgC msg;
      FUN_00434040(&msg);
      u32 q1 = ((TFu)(*(void***)obj)[0x2c / 4])(obj);
      FUN_00571d40((char*)&msg + 4, q1);
      u32 q2 = ((TFu)(*(void***)obj)[0x30 / 4])(obj);
      u32 mat[9];
      FUN_0059c190(mat, q2);
      for (s32 i = 0; i < 9; i++) msg.mMatrix[i] = mat[i];
      msg.mFlags |= 2;
      msg.mCount++;
      ((TFmsg)(*(void***)ref)[0x18 / 4])(ref, &msg);
      ((TFmsgv)(*(void***)ref)[8 / 4])(ref, 0);
    }
    if (ref != 0) ((TFv)(*(void***)ref)[4 / 4])(ref);
  }

  if (info->mField20 != 0) {
    EventLogC* log = (EventLogC*)FUN_00b3d3e0();
    log->PostFeedbackEvent(info->mField20, 0x68dd6929, 0, 0, 1, 0);
  }

  s32 v = (s32)info->mField10;
  if (v > 0) {
    info->mField10 = (u32)(v - 1);
    if (v == 1) info->mField24 = 1;
  }

  {
    u16 strbuf[8];
    u16* sBegin = strbuf;
    u16* sEnd = strbuf;
    u16* sCap = strbuf;
    sBegin[0] = 0;
    if ((((u32)sEnd - (u32)sBegin) & 0xfffffffe) > 2 && sBegin != 0 && sBegin != sCap)
      FUN_00f47380(sBegin);
  }
  return 1;
}

// @ 0x00d472a0
void __fastcall FUN_00d472a0(TrigVec* self, void* dummy)
{
  (void)dummy;
  TrigInfo* e = self->mEnd;
  if (e < self->mCap) {
    self->mEnd = (TrigInfo*)((char*)e + 0x2c);
    if (e != 0) {
      e->mRef0 = 0;
      e->mRef28 = 0;
    }
    return;
  } else {
    TrigInfo tmp;
    tmp.mRef0 = 0;
    tmp.mRef28 = 0;
    FUN_00d47160(e, &tmp);
    void* r28 = tmp.mRef28;
    if (r28 != 0) {
      ((TFv1)(*(void***)r28)[0xc / 4])(r28, 0);
      ((TFv)(*(void***)r28)[4 / 4])(r28);
    }
    void* r0 = tmp.mRef0;
    if (r0 != 0) ((TFv)(*(void***)r0)[4 / 4])(r0);
  }
}

// @ 0x00d47630
cTriggerRec* cCreatureTriggerSystem::GetTrigger(u32 eventType, cTriggerOwner* owner)
{
    if (owner == 0)
        return 0;

    u32 key = owner->mKey_24;
    u8* it = 0;
    mMap.Find(&it, &key);
    if (it != (u8*)mMap.mpBegin[mMap.mCount]) {
        cTrigNodeList* node = (cTrigNodeList*)it;
        cTriggerRec* p = node->mpBegin_08;
        cTriggerRec* e = node->mpEnd_0c;
        while (p != e) {
            if (p->mKind_0c == 0xa07dde8f)
                return p;
            if (p->mKind_0c == eventType)
                return p;
            p = (cTriggerRec*)((u8*)p + 0x2c);
        }
    }

    u32* array = 0;
    i32 count = 0;
    cNounManager* mgr = SP_NounManager_s00d4_7630();
    if (owner->mpObj_28 != 0) {
        void* v = ((cOwnerVirt20)owner->mVtbl_00[0x20 / 4])(owner, owner->mpObj_28);
        u8* r = (u8*)mgr->Find(v);
        if (r != 0 && *(void**)(r + 0x0c) != 0)
            GetPropertyAsUint32Array(*(void**)(r + 0x0c), 0x3d03b03, &count, &array);
    }
    if (array == 0 || count <= 0)
        return 0;

    cTriggerRec* result = 0;
    cTriggerRef* temp = 0;
    cPropertyManager* manager = SP_PropertyManager();
    cTrigFindCtx ctx;
    ctx.mKey_00 = owner->mKey_24;
    ctx.mZero_04 = 0;
    ctx.mpManager_08 = manager;
    cTriggersInfo* info = mMap.NewInfo(&ctx);

    cTriggerRef* old = info->mpOwner_00;
    if ((cTriggerRef*)owner != old) {
        ((cTriggerRef*)owner)->AddRef();
        info->mpOwner_00 = (cTriggerRef*)owner;
        if (old != 0)
            old->Release();
    }
    info->mFlag_17c = 0;

    for (i32 i = 0; i < count; i++) {
        u32 id = array[i];
        if (id == 0)
            continue;
        if (temp != 0) {
            cTriggerRef* dead = temp;
            temp = 0;
            dead->Release();
        }
        if (((cPropMgrVirt2c)manager->mVtbl_00[0x2c / 4])(manager, id, 0x3cddc79, &temp)) {
            info->mSlots.Append();
            cTriggerRec* slot = info->mSlots.mpEnd_04 - 1;
            cTriggerRef* prev = slot->mpRef_00;
            if (temp != prev) {
                if (temp != 0)
                    temp->AddRef();
                slot->mpRef_00 = temp;
                if (prev != 0)
                    prev->Release();
            }
            ReadTrigger(slot);
            info->mFlag_17c |= (slot->mKind_0c == 0x6ab2cd38);
            if (slot->mKind_0c == 0xa07dde8f || slot->mKind_0c == eventType)
                result = slot;
        }
    }

    if (temp != 0) {
        cTriggerRef* dead = temp;
        temp = 0;
        dead->Release();
    }
    return result;
}

// @ 0x00d47850
void cContentValidationSummarizer_s00d4_7630::FUN_00d47850()
{
    cNodePool* pool = &mPool;
    mVtbl_00 = (void*)0x147adf8;
    pool->FreeLists(pool->mpTail, pool->mCount);
    u8* p = (u8*)pool->mpTail;
    pool->mField_0c = 0;
    if (pool->mCount > 1 && p != (u8*)pool->mpSentinel) {
        if (p >= pool->mpPoolLo && p < pool->mpPoolHi) {
            *(void**)p = pool->mpFreeHead;
            pool->mpFreeHead = p;
            mVtbl_00 = (void*)0x13ec458;
            return;
        }
        FUN_00f473a0(p);
    }
    mVtbl_00 = (void*)0x13ec458;
}

// @ 0x00d478b0
bool cCreatureTriggerSystem::EvaluateEvent(u32 eventID, cTriggerEvent* ev)
{
    void* owner = ev->mpOwner_04;
    if (owner == 0)
        return false;
    switch (eventID) {
    case 0xd335362b:
    case 0xd335362c:
    case 0xd335362d:
    case 0xd335362e:
    case 0xd3353636:
    case 0xd3353638: {
        cTriggerRec* t = GetTrigger(eventID, (cTriggerOwner*)owner);
        if (t == 0)
            return false;
        if (t->mFlag_08 != 0) {
            u32 flags = *(u32*)((u8*)ev->mpObject_00 + 0xb58);
            if (((u8)(flags >> 9) & 1) == 0)
                return false;
        }
        return EvaluateTrigger(t, owner, ev->mpObject_00);
        }
    }
    return false;
}

// @ 0x01364b20
void init_15833f0()
{
    Attribute a;

    a.mpName   = "mbDisplayingEvolutionButton";
    a.mHash    = 0x054aba85;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;   // default-value getter
    a.mpFn24   = (void*)&FUN_00ac8750;
    a.mpFn28   = (void*)&FUN_00ac8780;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694fa0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_0057ce00;
    a.mLocation = 0xdc;
    g_creatureEditorAttributes[0] = a;

    a.mpName   = "sCreatureGameData";
    a.mHash    = 0x061afc2e;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_011874d0;
    a.mpFn24   = (void*)&FUN_00d38b70;
    a.mpFn28   = (void*)&FUN_00d38b90;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00d38b50;
    a.mpFn38   = 0;
    a.mLocation = 0x0169e370;
    g_creatureEditorAttributes[1] = a;

    a.mpName   = "mAllPartsUnlockedColumn";
    a.mHash    = 0x066ce337;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00692ff0;
    a.mpFn30   = (void*)&FUN_00694ee0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_0057cde0;
    a.mLocation = 0xe0;
    g_creatureEditorAttributes[2] = a;
}
