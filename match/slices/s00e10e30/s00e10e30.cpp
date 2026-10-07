// Slice s00e10e30: cSPUIMinimapWin::draw_trade_routes (0x00e10e30).
// UI module, /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
//
// Draws the trade-route dots on the minimap. Outside the civilization/space planet modes
// (0x1654c01 / 0x1654c02) it walks every trade-route game object (two dot styles, chosen by
// the route kind at +0x124), projects the route polyline into minimap space and stamps the
// road icon every time the projected point moved far enough. In the planet modes it rebuilds
// the cached dot list (minimap x, y, size) from the planet's trade routes when it is dirty,
// skipping points behind the planet's horizon, and then stamps every cached dot.
//
// Retail layout: the window fields used here sit after the dev-PDB layout (+0x248 road icon
// image, +0x338/+0x344 camera position/direction, +0x350 camera parameter, +0x364 dirty
// flag, +0x368 eastl::vector of cached dots).
#include "types.h"

#include <math.h>

inline void* operator new(unsigned int, void* p) { return p; }

struct Vector2 {
    float x, y;
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};

namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle() {}
    Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
};
}

// eastl::vector<Vector3, sp_vector_allocator> (0x14 bytes in this build).
struct Vector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator[2];

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    Vector3* begin() { return mpBegin; }
    Vector3* end() { return mpEnd; }
    Vector3& operator[](uint32_t i) { return mpBegin[i]; }
    Vector3* erase(Vector3* first, Vector3* last);          // 0x0050f740
    void DoInsertValue(Vector3* position, const Vector3& value);   // 0x004b5ad0
    void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) Vector3(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void clear() { erase(mpBegin, mpEnd); }
};

namespace EA { namespace UTFWin {
class Image;
class Draw2D {
public:
    virtual void v00();
    virtual void SetColor(uint32_t color);                                      // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void DrawImage(const Math::Rectangle& area, Image* image,
                           const Math::Rectangle& uv);                         // +0x58
};
} }

// A trade route on the planet: a polyline of 0x24-byte points.
struct cTradeRoutePoint {
    Vector3 mPosition;
    float mSize;            // +0x0c
    uint32_t pad10[5];
};
struct cTradeRoute {
    uint32_t pad0;
    cTradeRoutePoint* mpPointsBegin;    // +0x04
    cTradeRoutePoint* mpPointsEnd;      // +0x08
    uint32_t NumPoints() const { return (uint32_t)(mpPointsEnd - mpPointsBegin); }
};

class cPlanet {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* GetHorizonSource();                       // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0();
    virtual cTradeRoute* GetTradeRoute(int index);          // +0xc4
    virtual int GetTradeRouteCount();                       // +0xc8
};

struct cPlanetModel {
    uint32_t pad0[9];
    cPlanet* mpPlanet;      // +0x24
};

// Trade-route game objects (cities' road polylines) from the noun manager.
struct cRouteObject {
    uint32_t pad0[0x49];
    int mRouteKind;                     // +0x124 (1 = second dot style)
    Vector3* mpPointsBegin;             // +0x128
    Vector3* mpPointsEnd;               // +0x12c
    uint32_t NumPoints() const { return (uint32_t)(mpPointsEnd - mpPointsBegin); }
};
struct cRouteObjectVector {
    cRouteObject** mpBegin;
    cRouteObject** mpEnd;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cRouteObject* operator[](uint32_t i) { return mpBegin[i]; }
};
struct cGameDataVector {
    uint32_t pad0;
    cRouteObjectVector mData;           // +0x04
};

typedef void (*GameDataFn)();
void GameDataFn_cd7d10();
void GameDataFn_d3d420();
void GameDataFn_e10060();
void GameDataFn_b1e500();

namespace SP {
uint32_t GetCurrentGameMode();          // 0x00b5b800
cPlanetModel* PlanetModel();            // 0x00b3d350
struct cGameNounManager {
    cGameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                       uint32_t nounID);   // 0x00b21340
};
cGameNounManager* NounManager();        // 0x00b3d300
}

// Point on the planet's horizon seen from the camera (cdecl, 0x00e0cea0).
Vector3 GetHorizonPoint(void* source, const Vector2& range, const Vector3& cameraPos,
                        const Vector3& cameraDir, float cameraParam);

struct cDotStyle {
    float mHalfWidth;
    float mHalfHeight;
    uint32_t mColor;
    float mSpacing;
};

class cSPUIMinimapWin {
public:
    uint32_t pad0[0x92];
    EA::UTFWin::Image* mpRoadIconImage;     // +0x248
    uint32_t pad24c[0x3b];
    Vector3 mWorldCameraPos;                // +0x338
    Vector3 mWorldCameraDir;                // +0x344
    float mCameraParam;                     // +0x350
    uint32_t pad354[4];
    bool mbTradeRoutesDirty;                // +0x364
    Vector3Vector mTradeRouteDots;          // +0x368

    bool WorldXYZToMinimapXY(const Vector3& pos, Vector2& out, bool clamp);   // 0x00e0bcb0
    void draw_trade_routes(EA::UTFWin::Draw2D& draw);
};

// @ 0x00e10e30 ?draw_trade_routes@cSPUIMinimapWin@@IAEXAAVDraw2D@UTFWin@EA@@@Z
void cSPUIMinimapWin::draw_trade_routes(EA::UTFWin::Draw2D& draw)
{
    Math::Rectangle uv(0.0f, 0.0f, 1.0f, 1.0f);
    uint32_t mode = SP::GetCurrentGameMode();
    if (mode != 0x1654c01 && mode != 0x1654c02) {
        cDotStyle styles[2] = {
            { 0.5f, 0.5f, 0xffbfbfff, 20.0f },
            { 1.0f, 1.0f, 0xffffffbf, 6.0f },
        };
        cRouteObjectVector& routes = SP::NounManager()->GetGameDataVector(
            (GameDataFn)GameDataFn_cd7d10, (GameDataFn)GameDataFn_d3d420,
            (GameDataFn)GameDataFn_e10060, (GameDataFn)GameDataFn_b1e500, 0x2b8a4e7)->mData;
        for (uint32_t i = 0; i < routes.size(); ++i) {
            cRouteObject* route = routes[i];
            cDotStyle* style = &styles[0];
            if (route->mRouteKind == 1)
                style = &styles[1];
            if (route->NumPoints() > 1) {
                float halfWidth = style->mHalfWidth;
                float halfHeight = style->mHalfHeight;
                float minDistSq = (halfWidth + halfHeight) * style->mSpacing;
                Vector3 prev = route->mpPointsBegin[0];
                Vector2 lastXY;
                WorldXYZToMinimapXY(prev, lastXY, false);
                draw.SetColor(style->mColor);
                draw.DrawImage(Math::Rectangle(lastXY.x - halfWidth, lastXY.y - halfHeight,
                                               lastXY.x + halfWidth, lastXY.y + halfHeight),
                               mpRoadIconImage, uv);
                for (uint32_t j = 1; j < route->NumPoints(); ++j) {
                    Vector3 cur = route->mpPointsBegin[j];
                    float dx = cur.x - prev.x;
                    float dy = cur.y - prev.y;
                    float dz = cur.z - prev.z;
                    float step = 2.0f / sqrtf(dx * dx + dy * dy + dz * dz);
                    float t = 0.0f;
                    do {
                        t = step + t;
                        float s = 1.0f - t;
                        Vector3 p(prev.x * s + cur.x * t, prev.y * s + cur.y * t, prev.z * s + cur.z * t);
                        Vector2 xy;
                        WorldXYZToMinimapXY(p, xy, false);
                        float ex = xy.x - lastXY.x;
                        float ey = xy.y - lastXY.y;
                        if (ex * ex + ey * ey > minDistSq) {
                            lastXY = xy;
                            draw.DrawImage(Math::Rectangle(xy.x - halfWidth, xy.y - halfHeight,
                                                           xy.x + halfWidth, xy.y + halfHeight),
                                           mpRoadIconImage, uv);
                        }
                    } while (t < 1.0f);
                    prev = cur;
                }
            }
        }
        return;
    }

    draw.SetColor(0xffbfbfff);
    cPlanetModel* model = SP::PlanetModel();
    cPlanet* planet = model ? model->mpPlanet : 0;
    if (mbTradeRoutesDirty && planet) {
        mbTradeRoutesDirty = false;
        mTradeRouteDots.clear();

        // Points farther from the camera than the horizon are on the far side.
        Vector2 range = { 0.0f, 1.0f };
        Vector3 horizon = GetHorizonPoint(planet->GetHorizonSource(), range, mWorldCameraPos,
                                          mWorldCameraDir, mCameraParam);
        float inv = 1.0f / sqrtf(horizon.y * horizon.y + horizon.z * horizon.z +
                                 horizon.x * horizon.x + 1e-8f);
        float hx = mWorldCameraPos.x - horizon.x * inv;
        float hy = mWorldCameraPos.y - horizon.y * inv;
        float hz = mWorldCameraPos.z - horizon.z * inv;
        float horizonDistSq = hx * hx + hy * hy + hz * hz;

        int count = planet->GetTradeRouteCount();
        for (int i = 0; i < count; ++i) {
            cTradeRoute* route = planet->GetTradeRoute(i);
            if (route && route->NumPoints() > 1) {
                Vector3 prev = route->mpPointsBegin[0].mPosition;
                Vector2 lastXY;
                WorldXYZToMinimapXY(prev, lastXY, false);
                inv = 1.0f / sqrtf(prev.x * prev.x + prev.y * prev.y + prev.z * prev.z + 1e-8f);
                hx = mWorldCameraPos.x - prev.x * inv;
                hy = mWorldCameraPos.y - prev.y * inv;
                hz = mWorldCameraPos.z - prev.z * inv;
                if (hx * hx + hy * hy + hz * hz < horizonDistSq)
                    mTradeRouteDots.push_back(Vector3(lastXY.x, lastXY.y, route->mpPointsBegin[0].mSize));

                for (uint32_t j = 1; j < route->NumPoints(); ++j) {
                    float size = route->mpPointsBegin[j].mSize;
                    Vector3 cur = route->mpPointsBegin[j].mPosition;
                    inv = 1.0f / sqrtf(cur.y * cur.y + cur.z * cur.z + cur.x * cur.x + 1e-8f);
                    hx = mWorldCameraPos.x - cur.x * inv;
                    hy = mWorldCameraPos.y - cur.y * inv;
                    hz = mWorldCameraPos.z - cur.z * inv;
                    if (hx * hx + hy * hy + hz * hz < horizonDistSq) {
                        float dx = cur.x - prev.x;
                        float dy = cur.y - prev.y;
                        float dz = cur.z - prev.z;
                        float step = 2.0f / sqrtf(dx * dx + dy * dy + dz * dz);
                        float t = 0.0f;
                        do {
                            t = step + t;
                            float s = 1.0f - t;
                            Vector3 p(prev.x * s + cur.x * t, prev.y * s + cur.y * t,
                                      prev.z * s + cur.z * t);
                            Vector2 xy;
                            WorldXYZToMinimapXY(p, xy, false);
                            float ex = xy.x - lastXY.x;
                            float ey = xy.y - lastXY.y;
                            if (ex * ex + ey * ey > 12.0f) {
                                lastXY = xy;
                                mTradeRouteDots.push_back(Vector3(xy.x, xy.y, size));
                            }
                        } while (t < 1.0f);
                    }
                    prev = cur;
                }
            }
        }
    }

    uint32_t n = mTradeRouteDots.size();
    for (uint32_t k = 0; k < n; ++k) {
        Vector3& dot = mTradeRouteDots[k];
        float r = dot.z * 1.5f;
        draw.DrawImage(Math::Rectangle(dot.x - r, dot.y - r, dot.x + r, dot.y + r),
                       mpRoadIconImage, uv);
    }
}
