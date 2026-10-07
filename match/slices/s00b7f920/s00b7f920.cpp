// Slice s00b7f920: draws a fading Hermite-curve ribbon (arc over the planet surface) from point a
// to point b through the static debug vertex buffer. Called from the planet minimap/arc code
// near 0x00b8c550 (thiscall, `this` unused).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(memcpy, memset, sqrt)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    Vector3 Normalized() const {
        float f = 1.0f / Length();
        return Vector3(x * f, y * f, z * f);
    }
    Vector3 Cross(const Vector3& v) const {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float x_, float y_) : x(x_), y(y_) {}
};

// Cubic Hermite interpolation (p0 -> p1 with tangents m0, m1).
inline Vector3 Hermite(const Vector3& p0, const Vector3& p1, const Vector3& m0, const Vector3& m1, float t)
{
    float t2 = t * t;
    float t3 = t2 * t;
    float h00 = 2.0f * t3 - 3.0f * t2 + 1.0f;
    float h01 = 3.0f * t2 - 2.0f * t3;
    float h10 = t3 - 2.0f * t2 + t;
    float h11 = t3 - t2;
    return p0 * h00 + p1 * h01 + m0 * h10 + m1 * h11;
}

struct RibbonVertex {
    Vector3 pos;      // +0x00
    Vector3 normal;   // +0x0c
    uint32_t color;   // +0x18
    Vector2 uv;       // +0x1c
};

namespace SP {
class cStaticBuffer {
public:
    int GetVertexBuffer(int count, RibbonVertex** ppVertices, int* pStride);   // 0x007a47c0
    void Unlock();                                                              // 0x007a4650
};
struct cStaticBufferDraw {
    cStaticBuffer* mpBuffer;
    static cStaticBufferDraw* spInstance;   // 0x015ddc84
};

struct cGridInfo { uint32_t pad[0x38 / 4]; float mHeightOffset; };   // +0x38
struct IGrid { virtual void v00(); virtual void v04(); virtual void v08(); virtual cGridInfo* GetInfo(); };
IGrid* DebugDrawGrid();   // 0x00f48aa0

struct cPlanetInfo { uint32_t pad[0x34 / 4]; float mRadius; };      // +0x34
struct IPlanet { virtual void v00(); virtual void v04(); virtual void v08(); virtual cPlanetInfo* GetInfo(); };
struct cPlanetModel { uint32_t pad[0x24 / 4]; IPlanet* mpPlanet; };  // +0x24
cPlanetModel* PlanetModel();   // 0x00b3d350
}

class cArcRibbon {
public:
    void DrawArc(const Vector3& a, const Vector3& b, uint32_t color);
};

// @ 0x00b7f920
void cArcRibbon::DrawArc(const Vector3& a, const Vector3& b, uint32_t color)
{
    RibbonVertex buffer[0x80];
    RibbonVertex* pVertex = buffer;
    SP::cStaticBufferDraw* pDraw = SP::cStaticBufferDraw::spInstance;

    Vector3 startTangent = a.Normalized() * 90.0f;
    Vector3 endTangent = -b.Normalized() * 90.0f;

    float gridOffset = SP::DebugDrawGrid()->GetInfo()->mHeightOffset;
    SP::cPlanetModel* pPlanetModel = SP::PlanetModel();
    float radius;
    if (pPlanetModel->mpPlanet && pPlanetModel->mpPlanet->GetInfo())
        radius = pPlanetModel->mpPlanet->GetInfo()->mRadius;
    else
        radius = 500.0f;
    radius = radius + gridOffset + 5.0f;

    Vector3 middle = (b + a).Normalized() * radius;
    Vector3 dir = (b - a) * 1.2f;
    Vector3 dirN = dir.Normalized();
    Vector3 tangentA = dirN * 50.0f + startTangent;
    Vector3 tangentB = dirN * 50.0f + endTangent;
    Vector3 side = a.Cross(b).Normalized();

    Vector3 prev = Hermite(a, middle, tangentA, dir, 0.1f);
    uint32_t prevColor = color;
    float dist = 0.0f;

    for (int i = 1; i <= 16; i++) {
        Vector3 cur = Hermite(a, middle, tangentA, dir, i * 0.05625f + 0.1f);
        uint32_t curColor = (i < 4) ? (uint32_t)(i << 30) : 0xff000000;
        curColor |= color;

        pVertex->pos = prev - side;
        pVertex->normal = side;
        pVertex->color = prevColor;
        pVertex->uv = Vector2(0.0f, dist);
        pVertex++;
        pVertex->pos = prev + side;
        pVertex->normal = side;
        pVertex->color = prevColor;
        pVertex->uv = Vector2(1.0f, dist);
        pVertex++;
        dist += (cur - prev).Length();
        pVertex->pos = cur + side;
        pVertex->normal = side;
        pVertex->color = curColor;
        pVertex->uv = Vector2(1.0f, dist);
        pVertex++;
        pVertex->pos = cur - side;
        pVertex->normal = side;
        pVertex->color = curColor;
        pVertex->uv = Vector2(0.0f, dist);
        pVertex++;

        prev = cur;
        prevColor = curColor;
    }

    for (int i = 0; i < 16; i++) {
        Vector3 cur = Hermite(middle, b, dir, tangentB, (i + 1) * 0.05625f);
        uint32_t curColor = (i < 12) ? 0xff000000 : (uint32_t)((15 - i) << 30);
        curColor |= color;

        pVertex->pos = prev - side;
        pVertex->normal = side;
        pVertex->color = prevColor;
        pVertex->uv = Vector2(0.0f, dist);
        pVertex++;
        pVertex->pos = prev + side;
        pVertex->normal = side;
        pVertex->color = prevColor;
        pVertex->uv = Vector2(1.0f, dist);
        pVertex++;
        dist += (cur - prev).Length();
        pVertex->pos = cur + side;
        pVertex->normal = side;
        pVertex->color = curColor;
        pVertex->uv = Vector2(1.0f, dist);
        pVertex++;
        pVertex->pos = cur - side;
        pVertex->normal = side;
        pVertex->color = curColor;
        pVertex->uv = Vector2(0.0f, dist);
        pVertex++;

        prev = cur;
        prevColor = curColor;
    }

    int stride;
    int count = pDraw->mpBuffer->GetVertexBuffer(0x80, &pVertex, &stride);
    if (stride == sizeof(RibbonVertex) && count == 0x80)
        memcpy(pVertex, buffer, sizeof(buffer));
    else
        memset(pVertex, 0, stride * count);
    pDraw->mpBuffer->Unlock();
}
