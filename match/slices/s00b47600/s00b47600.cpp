// Slice s00b47600: F_b47730, a physics-object factory (allocates a handle from a pool, fills in
// mass/inertia from the model bounding box, and registers the object in a map).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <float.h>
#include <xmmintrin.h>

struct V3 { float x, y, z; };
static inline V3 MakeV3(float x, float y, float z) { V3 r; r.x = x; r.y = y; r.z = z; return r; }
template<class T> static inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template<class T> static inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
struct Mat3 { float m[9]; };
struct BBox { V3 mn, mx; };
struct PropHolder;
struct Part25c { uint32_t pad[0x25c / 4]; float f25c; };

struct Obj {
    uint32_t m0;
    uint32_t m4;                    // +4
    uint32_t m8;                    // +8
    int state;                      // +0xc
    float f10, f14, f18;            // +0x10..
    uint32_t pad1[6];               // +0x1c..0x33
    uint8_t b34, b35, b36, b37;
    uint32_t m38, m3c;
    Part25c* m40;
    V3 v44, v50;                    // +0x44, +0x50
    Mat3 m5c;                       // +0x5c
    Mat3 m80;                       // +0x80
    uint32_t pad2[9];               // +0xa4..0xc7
    V3 vc8, vd4, ve0, vec;          // +0xc8..
    uint32_t pad3[9];               // +0xf8..0x11b
    float f11c, f120, f124, f128, f12c, f130, f134;
    float F_b3d630();
    void F_b3f420(BBox* b);
    const BBox* F_b3f730(BBox* b);
    void F_b43290();
    void F_b3dbb0();
};
struct Pool {
    int F_b72160();
    Obj* F_b72210(int h);
};
struct Map {
    Obj** F_b474c0(const uint32_t* key);
};
struct Mgr {
    uint32_t m0;
    uint32_t m4;                    // +4
    uint32_t pad0[(0x3c - 8) / 4];
    Pool pool;                      // +0x3c
    uint32_t pad1[(0x58 - 0x40) / 4];
    Map map;                        // +0x58
    uint32_t pad2[(0xb4 - 0x5c) / 4];
    float ratio;                    // +0xb4
};
extern Mgr* g_mgr;                  // 0x0167eb70
extern V3 g_v;                      // 0x0167eb8c

int GetTutorialToolPrice(PropHolder* p, int key, int def);      // 0x004e1c30
float GetPropertyFloat(PropHolder* p, int key, float def);      // 0x004e1c70
int F_ac8fa0(PropHolder* p, int key, int a);
Mat3* F_4fc990(Mat3* out, const Mat3* in, float* det);
int F_bbc300(uint32_t a, int h, V3* mn, V3* mx);

// @ 0x00b47730
Obj* F_b47730(uint32_t key, Part25c* a2, uint32_t a3, int kind, PropHolder* a5, int a6)
{
    BBox box;
    int h = g_mgr->pool.F_b72160();
    if (h != 0) {
        Obj* o = g_mgr->pool.F_b72210(h);
        o->m40 = a2;
        o->m4 = a3;
        o->b35 = 0;
        o->b34 = 1;
        o->b36 = 0;
        o->b37 = 0;
        o->state = GetTutorialToolPrice(a5, 0x2f5ab240, a6);
        o->f10 = GetPropertyFloat(a5, 0xce3f2a3a, 1.0f);
        o->f14 = GetPropertyFloat(a5, 0xc87942af, 1.0f);
        o->m38 = o->m3c = F_ac8fa0(a5, 0x1970f7f8, kind);
        o->f18 = 0.0f;
        float lim = GetPropertyFloat(a5, 0xb20c1347, FLT_MAX);
        if (o->state == 0 && o->F_b3d630() > lim)
            o->f18 = lim;
        if (kind == 5)
            o->f18 = a2->f25c;

        box.mn = MakeV3(FLT_MAX, FLT_MAX, FLT_MAX);
        box.mx = MakeV3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        o->F_b3f420(&box);

        if (o->state == 4) {
            o->state = 0;
            float d[3];
        d[0] = box.mx.x - box.mn.x;
        d[1] = box.mx.y - box.mn.y;
        d[2] = box.mx.z - box.mn.z;
        float hi = Max(Max(d[0], d[1]), d[2]);
        if (hi > g_mgr->ratio * Min(Min(d[0], d[1]), d[2]))
                o->state = 2;
        }

        if (o->state == 1) {
            float k = o->f14;
            float a = (box.mx.x - box.mn.x) * k;
            float b = (box.mx.y - box.mn.y) * k;
            float c = (box.mx.z - box.mn.z) * k;
            float r = o->f10 * 0.5f;
            V3 p, q;
            p.x = g_v.x; p.y = g_v.y; p.z = g_v.z;
            q.x = g_v.x; q.y = g_v.y; q.z = g_v.z;
            float m;
            if (c > b && c > a) {
                float s = sqrtf(a * a + b * b) * r;
                m = Min(s, lim);
                p.z = c * 0.5f - m;
                q.z = -p.z;
            } else if (b > a) {
                float s = sqrtf(a * a + c * c) * r;
                m = Min(s, lim);
                p.y = b * 0.5f - m;
                q.y = -p.y;
            } else {
                float s = sqrtf(b * b + c * c) * r;
                m = Min(s, lim);
                p.x = a * 0.5f - m;
                q.x = -p.x;
            }
            float dx = p.x - q.x, dy = p.y - q.y, dz = p.z - q.z;
            if (1.5258789e-05f <= sqrtf((dz * dz + dy * dy) + dx * dx)) {
                float cy = (box.mx.y + box.mn.y) * 0.5f;
                float cz = (box.mx.z + box.mn.z) * 0.5f;
                float cx = (box.mx.x + box.mn.x) * 0.5f;
                o->f11c = cx + p.x;
                o->f120 = cy + p.y;
                o->f124 = cz + p.z;
                o->f128 = cx + q.x;
                o->f12c = cy + q.y;
                o->f130 = cz + q.z;
                o->f134 = m;
            } else {
                o->state = 0;
            }
        }

        const BBox* bb = o->F_b3f730(&box);
        box.mn = bb->mn;
        box.mx = bb->mx;
        float ex = box.mx.x - box.mn.x;
        float ey = box.mx.y - box.mn.y;
        float ez = box.mx.z - box.mn.z;
        float ex2 = ex * ex, ey2 = ey * ey, ez2 = ez * ez;
        {
            Mat3 inertia;
            inertia.m[0] = (ez2 + ey2) * 0.083333336f;
            inertia.m[1] = 0.0f;
            inertia.m[2] = 0.0f;
            inertia.m[3] = 0.0f;
            inertia.m[4] = (ez2 + ex2) * 0.083333336f;
            inertia.m[5] = 0.0f;
            inertia.m[6] = 0.0f;
            inertia.m[7] = 0.0f;
            inertia.m[8] = (ey2 + ex2) * 0.083333336f;
            o->m80 = inertia;
            o->v44 = g_v;
            o->v50 = g_v;
            o->vc8 = g_v;
            o->vd4 = g_v;
            o->ve0 = g_v;
            o->vec = g_v;
            float det;
            F_4fc990(&inertia, &o->m80, &det);
            o->m5c = inertia;
        }
        o->F_b43290();
        o->m8 = F_bbc300(g_mgr->m4, h, &box.mn, &box.mx);
        *g_mgr->map.F_b474c0(&key) = o;
        o->F_b3dbb0();
        return o;
    }
    return 0;
}
