// Slice s00b8c330 — planet minimap/route overlay rebuild (SP::cPlanetModel, retail layout).
// PDB name guess for 0x00b8c330 is "sInitMinimap" (callee-scored, unconfirmed).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no EH frame although vectors are destroyed).
#include "types.h"
#include <xmmintrin.h>

inline void* operator new(unsigned int, void* p) throw() { return p; }

void __cdecl operator_delete__(void* p);                  // 0xf47380 (operator delete[])

// ---- math -------------------------------------------------------------
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

namespace SP { Vector3 __cdecl normalized_safe(const Vector3& v); }   // 0x449c20

// ColorRGB (0..1 floats) -> 0x00RRGGBB
extern const float kColorScale;                      // 0x1465434 = 255.0f
// The original's float->byte helper is an SSE asm helper (maxss/mulss/minss/cvtss2si, result in eax).
#pragma warning(disable: 4035)
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
#pragma warning(default: 4035)
__forceinline uint32_t ToColor(const Vector3& c)
{
    uint8_t r = UnitToByte(c.x);
    uint8_t g = UnitToByte(c.y);
    uint8_t b = UnitToByte(c.z);
    return ((uint32_t)r << 8 | g) << 8 | b;
}

// ---- eastl::vector with sp_vector_allocator ------------------------------
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

// out-of-line template instances (addresses in the original)
template <> cCurvePoint* CurveVector::erase(cCurvePoint* first, cCurvePoint* last);   // 0xac4570
template <> Vector3* Vec3Vector::erase(Vector3* first, Vector3* last);               // 0x50f740
template <> void Vec3Vector::resize(int n);                                          // 0x473810
template <> Vec3Vector& Vec3Vector::operator=(const Vec3Vector& x);                  // 0x473500
template <> Vector3* Vec3Vector::insert(Vector3* pos, const Vector3& v);             // 0xb85d40
template <> void Vec3Vector::DoInsertValue(Vector3* pos, const Vector3& v);          // 0x4b5ad0

void __cdecl reverse_impl(Vector3* first, Vector3* last, random_access_iterator_tag); // 0xb85570
inline void reverse(Vector3* first, Vector3* last) { reverse_impl(first, last, random_access_iterator_tag()); }

// ---- game objects ----------------------------------------------------------
struct cCity {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual void GetPosition(Vector3* out);          // +0x5c

    const Vector3& GetColor();                       // 0xbd99e0
    const Vector3& GetLocation();                    // 0xfa0e00
    Vector3 GetPlanetCenter();                       // 0xbd9480
};

struct CityPair { cCity* first; cCity* second; };

struct cLandRoute {           // 0x1c bytes
    cCity* city1;
    cCity* city2;
    Vec3Vector mPath;
};

struct cStaticBuffer {
    virtual void v00(); virtual void v04();
    virtual void Release();                          // +0x08
    void Flush();                                    // 0x7a4710
};
struct cStaticBufferDraw { cStaticBuffer* mpBuffer; };
extern cStaticBufferDraw* g_StaticBufferDraw;         // 0x15ddc84 (SingletonBase<cStaticBufferDraw>::spInstance)

struct StaticBufferRef {
    cStaticBuffer* mpObject;
    void Reset()
    {
        cStaticBuffer* p = mpObject;
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
        cStaticBufferDraw* draw = g_StaticBufferDraw;
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

struct cTerrainSphere {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual bool IsReady();                          // +0x50
    virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98();
    virtual void Update(int a, int b);               // +0x9c
};

struct IGameMode {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual int GetModeID();                         // +0x1c
};
struct IApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual IGameMode* GetGameModeManager();         // +0x50
};
namespace SP { IApp* __cdecl App(); }                 // 0x67dd10

struct cPlanet { float GetTemperature(); };           // 0xc70a20
struct cTerraformTuning { float GetIceThreshold(); }; // 0x1049c40
cPlanet* __cdecl GetActivePlanet();                   // 0x1021260
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

struct cPlanetModel {
    uint32_t pad00[8];
    cTerrainSphere* mpSphere;     // +0x20
    cTerrainSphere* mpISphere;    // +0x24
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

// @ 0x00b8c330
void cPlanetModel::UpdateMinimap(int arg0, int arg1, int modeOverride)
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
