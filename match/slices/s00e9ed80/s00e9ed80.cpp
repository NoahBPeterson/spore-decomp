// s00e9ed80: 0x00e9ed80 rebuilds a vector of surface sample points laid out in concentric rings
// (spacing mfRingStep) around a centre point, projected onto the planet surface.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <math.h>
#include <new.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// eastl::vector<Vector3> (begin, end, capacity end, allocator)
struct Vector3Vec {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;
    Vector3* erase(Vector3* first, Vector3* last);               // 0x009e0480, thiscall ret 8
    void DoInsertValue(Vector3* pos, const Vector3& v);          // 0x00e9e620, thiscall ret 8
    void push_back(const Vector3& v)
    {
        if (mpEnd < mpCapacity) {
            ::new ((void*)mpEnd) Vector3(v);
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

Vector3 normalized_safe(const Vector3& v);                       // 0x00449c20 (cdecl, sret)

class cPlanetModel {
public:
    void ProjectToSurface(Vector3* out, const Vector3* in);      // 0x00b81630, thiscall ret 8
};
cPlanetModel* PlanetModel();                                     // 0x00b3d350

class cViewer {
public:
    void GetCameraLocationInfo(Vector3* pPosition, Vector3* pDirection, Vector3* pUp, Vector3* pRight);   // 0x007c3d30
};
class cCameraManager {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6();
    virtual cViewer* GetViewer();                                // 0x1c
};
class cApp {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
    virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual cCameraManager* GetCameraManager();                  // 0x50
};
cApp* App();                                                     // 0x0067dd10

extern const float kTwoPi;                                       // 0x016c69c0

struct SamplePoints {
    uint32_t pad0[0x9c / 4];
    Vector3 mCentre;            // 0x9c
    uint32_t pad1[(0xc4 - 0xa8) / 4];
    Vector3Vec mPoints;         // 0xc4
    uint32_t padD4[2];
    int mnPoints;               // 0xdc
    float mfRadius;             // 0xe0
    float mfRingStep;           // 0xe4
    void Rebuild();
};

static const float kEps = 1e-8f;

void SamplePoints::Rebuild()
{
    mPoints.erase(mPoints.mpBegin, mPoints.mpEnd);
    mnPoints = 0;
    cPlanetModel* pm = PlanetModel();
    if (!pm) return;
    cApp* app = App();
    if (!app) return;
    cCameraManager* cm = app->GetCameraManager();
    if (!cm) return;
    cViewer* viewer = cm->GetViewer();
    if (!viewer) return;

    Vector3 dir, up, right;
    viewer->GetCameraLocationInfo(0, &dir, &up, &right);
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + kEps);
    dir = Vector3(dir.x * inv, dir.y * inv, dir.z * inv);
    inv = 1.0f / sqrtf(right.x * right.x + right.y * right.y + right.z * right.z + kEps);
    right = Vector3(right.x * inv, right.y * inv, right.z * inv);

    // Rotation axis: the direction from the planet centre to the sample centre.
    Vector3 axis;
    float len = sqrtf(mCentre.x * mCentre.x + mCentre.y * mCentre.y + mCentre.z * mCentre.z);
    if (len > 0.01f) {
        float k = 1.0f / len;
        axis = Vector3(mCentre.x * k, mCentre.y * k, mCentre.z * k);
    } else {
        axis = normalized_safe(up);
    }

    // First ring direction: axis x right, normalised.
    Vector3 c(axis.y * right.z - axis.z * right.y,
              axis.z * right.x - axis.x * right.z,
              axis.x * right.y - axis.y * right.x);
    float cinv = 1.0f / sqrtf(c.x * c.x + c.y * c.y + c.z * c.z + kEps);

    float ringsF = (float)ceil((double)(mfRadius / mfRingStep));
    float step = mfRadius / ringsF;
    int nRings = (int)ringsF;
    float radius = step;
    for (; nRings > 0; --nRings) {
        float angle = 0.0f;
        int n = (int)((1.0f / step) * kTwoPi * radius);
        float da = kTwoPi / (float)n;
        float vx = c.x * cinv * radius;
        float vy = c.y * cinv * radius;
        float vz = c.z * cinv * radius;
        for (; n > 0; --n) {
            float h = angle * 0.5f;
            float s = sinf(h);
            float w = cosf(h);
            float qx = s * axis.x, qy = s * axis.y, qz = s * axis.z;
            Vector3 p;
            p.x = mCentre.x + ((w * qy + qz * qx) * vz + (qy * qx - w * qz) * vy) * 2.0f
                  + (1.0f - (qz * qz + qy * qy) * 2.0f) * vx;
            p.y = mCentre.y + ((w * qz + qy * qx) * vx + (qz * qy - w * qx) * vz) * 2.0f
                  + (1.0f - (qz * qz + qx * qx) * 2.0f) * vy;
            p.z = mCentre.z + ((qz * qx - w * qy) * vx + (w * qx + qz * qy) * vy) * 2.0f
                  + (1.0f - (qx * qx + qy * qy) * 2.0f) * vz;
            Vector3 out;
            pm->ProjectToSurface(&out, &p);
            mPoints.push_back(out);
            ++mnPoints;
            angle += da;
        }
        radius += step;
    }
}
