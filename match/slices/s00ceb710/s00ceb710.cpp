// Slice s00ceb710: builds camera-facing quads (billboards) for the objects under the terrain cursor
// and streams them into a locked vertex buffer.  /arch:SSE, x87 for float returns/args.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <xmmintrin.h>
#include <math.h>

struct Vector3 { float x, y, z; };
struct Matrix3 { float m[9]; };

// 0x38-byte placement record (flags: 2 = has rotation, 4 = has offset; the word after it counts the fields set).
struct Transform {
    uint16_t m_flags;      // +0
    uint16_t m_count;      // +2
    Vector3  m_offset;     // +4
    float    m_scale;      // +0x10
    Matrix3  m_rot;        // +0x14
};

// Object under the cursor (vtable slots as used here).
struct cSpatialObject {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual const void* GetTypeId();                                   // slot 8  (+0x20)
    virtual void s9();  virtual void s10();
    virtual const Vector3* GetPosition();                              // slot 11 (+0x2c)
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual const Vector3* GetDirection(Vector3* tmp);                 // slot 23 (+0x5c)
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual float GetScale();                                          // slot 29 (+0x74)
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45();
    virtual void* QueryInterface(uint32_t id);                         // slot 46 (+0xb8)
    virtual void s47();
    virtual void Release();                                            // slot 48 (+0xc0)
    uint8_t m_pad[0x73];
    uint8_t m_isPlanetSurface;     // +0x77
    float DistanceToCamera();      // FUN_00c887c0 (thiscall, float in st0)
};

struct cSpatialObjectComponent { uint8_t pad[0xb1c]; int m_state; };   // +0xb1c

struct cViewer {
    void GetCameraLocationInfo(Vector3* pos, Vector3* dir, int a, int b);   // 0x007c3d30
};
struct cPlanetModel {
    const Vector3* FUN_00b7e3b0(Vector3* out, const Vector3* in);          // 0x00b7e3b0
};

struct IViewerSource { virtual cViewer* GetViewer(); };                    // slot 7 below via pads
struct IAppLayer {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6();
    virtual cViewer* GetViewer();                                          // slot 7 (+0x1c)
};
struct cApp {
    virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4();
    virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9();
    virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14();
    virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19();
    virtual IAppLayer* GetLayer();                                         // slot 20 (+0x50)
};

// fixed_vector style containers (storage inline, begin/end/capacity at +0/+4/+8).
struct ObjectVec {
    cSpatialObject** m_begin; cSpatialObject** m_end; cSpatialObject** m_cap;
    int m_pad0, m_pad1, m_zero;
    cSpatialObject* m_buf[64];
};
struct TransformVec {
    Transform* m_begin; Transform* m_end; Transform* m_cap;
    int m_pad; Transform* m_fixed; int m_pad2;
    Transform m_buf[64];
    void push_back_default();                      // FUN_00ceb350
};
struct FloatVec {
    float* m_begin; float* m_end; float* m_cap;
    int m_pad; float* m_fixed;
    float m_buf[64];
    void push_back(const float& v);                // FUN_00a1a4d0
    void grow_push_back(float* pos, const float& v);   // FUN_00a1a1e0
};

struct ITerrainCursor {
    virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4();
    virtual void t5(); virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9();
    virtual void t10(); virtual void t11(); virtual void t12(); virtual void t13(); virtual void t14();
    virtual void t15(); virtual void t16(); virtual void t17(); virtual void t18(); virtual void t19();
    virtual void t20(); virtual void t21(); virtual void t22();
    virtual void GetObjects(ObjectVec* out);                               // slot 23 (+0x5c)
};

struct IVertexSink {
    virtual int  Lock(int count, char** base, int* stride);                // slot 0
    virtual void v1();
    virtual void Unlock();                                                 // slot 2
};

struct GameState { uint8_t pad[0x2c]; int m_mode; };

GameState* FUN_00b3d4d0();                                  // 0x00b3d4d0
cPlanetModel* PlanetModel();                                // SP::PlanetModel 0x00b3d350
const void* GetCurrentGameMode();                           // 0x00b5b800
cApp* App();                                                // SP::App 0x0067dd10
ITerrainCursor* GetGameTerrainCursor();                     // 0x00b30d70
const Vector3* normalized_safe(Vector3* out, const Vector3* in);                       // 0x00449c20
const Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up);   // 0x0069b440

extern Vector3 g_vecDefault;       // 0x0169ba50
extern char g_modeTerrain;         // 0x01654c02
extern char g_typeIdPlanet;        // 0x018c6de8

static inline uint32_t ColorByte(float v)
{
    __m128 k = _mm_set_ss(255.0f);
    return (uint8_t)_mm_cvtss_si32(_mm_min_ss(_mm_mul_ss(_mm_max_ss(_mm_setzero_ps(), _mm_set_ss(v)), k), k));
}

struct cBillboardRenderer {
    uint8_t m_pad0[8];
    uint8_t m_posOffset;       // +8   vertex position offset
    uint8_t m_colorOffset;     // +9   vertex colour offset
    uint8_t m_uvOffset;        // +0xa vertex texcoord offset
    uint8_t m_pad1[5];
    int m_mode;                // +0x10 (2 = alternate set, 1 = half alpha)
    int m_fadeMode;            // +0x14

    void Render(IVertexSink* sink);
};

// @ 0x00ceb710
void cBillboardRenderer::Render(IVertexSink* sink)
{
    GameState* gs = FUN_00b3d4d0();
    if (gs->m_mode == 1 || gs->m_mode == 2)
        return;

    cPlanetModel* planet = PlanetModel();
    bool terrainMode = (GetCurrentGameMode() == &g_modeTerrain);
    bool hasCamera = false;

    TransformVec transforms;
    transforms.m_begin = transforms.m_end = transforms.m_buf;
    transforms.m_cap = transforms.m_buf + 64;
    transforms.m_fixed = transforms.m_buf;

    FloatVec alphas;
    alphas.m_begin = alphas.m_end = alphas.m_buf;
    alphas.m_cap = alphas.m_buf + 64;
    alphas.m_fixed = alphas.m_buf;

    Vector3 camPos = g_vecDefault;
    Vector3 camDir = g_vecDefault;

    cViewer* viewer = App()->GetLayer()->GetViewer();
    if (viewer) {
        viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
        hasCamera = true;
    }

    ObjectVec objects;
    objects.m_begin = objects.m_end = objects.m_buf;
    objects.m_cap = objects.m_buf + 64;
    objects.m_zero = 0;
    GetGameTerrainCursor()->GetObjects(&objects);

    for (cSpatialObject** it = objects.m_begin; it != objects.m_end; ++it) {
        cSpatialObject* obj = *it;
        if (!obj) continue;

        bool alt = false;
        void* q = obj->QueryInterface(0x17f243b);
        if (q && ((cSpatialObject*)q)->GetTypeId() == &g_typeIdPlanet) {
            cSpatialObjectComponent* c = (cSpatialObjectComponent*)obj->QueryInterface(0x137e8e0);
            alt = (c->m_state == 2);
        }
        if (alt != (m_mode == 2)) continue;

        float dist = obj->DistanceToCamera();
        if (m_fadeMode == 0 && dist > 300.0f) continue;
        if (m_fadeMode == 1 && 200.0f > dist) continue;

        if (alt && hasCamera) {
            // Camera-oriented orientation from the object position and camera.
            const Vector3* pp = obj->GetPosition();
            Vector3 pos = *pp;
            Vector3 n1;
            normalized_safe(&n1, &pos);
            if ((n1.x * camDir.x + camDir.y * n1.y) + camDir.z * n1.z > 0.0f) continue;

            transforms.push_back_default();
            Transform* t = transforms.m_end - 1;
            Vector3 d = { camPos.x - pos.x, camPos.y - pos.y, camPos.z - pos.z };
            Vector3 n2;
            normalized_safe(&n2, &d);
            Vector3 c1 = { n1.y * n2.z - n1.z * n2.y, n1.z * n2.x - n1.x * n2.z, n1.x * n2.y - n1.y * n2.x };
            Vector3 c1n;
            normalized_safe(&c1n, &c1);
            Vector3 c2 = { c1n.z * n2.y - c1n.y * n2.z, c1n.x * n2.z - n2.x * c1n.z, n2.x * c1n.y - c1n.x * n2.y };
            Vector3 c2n;
            normalized_safe(&c2n, &c2);
            Matrix3 m;
            const Matrix3* r = Matrix3FromFacingAndUp(&m, &c2n, &n2);
            t->m_rot = *r;
            t->m_flags |= 6;
            t->m_count += 2;
            t->m_offset = pos;
            float sc = obj->GetScale();
            t->m_count += 1;
            t->m_scale = sc;
            float one = 1.0f;
            alphas.push_back(one);
            continue;
        }

        // General case.
        const Vector3* pp = obj->GetPosition();
        Vector3 dirTmp, up;
        const Vector3* dp;
        if (terrainMode && obj->m_isPlanetSurface) {
            dp = planet->FUN_00b7e3b0(&dirTmp, pp);
        } else {
            float x = pp->x, y = pp->y, z = pp->z;
            float inv = (float)(1.0 / sqrt((double)(z * z + (y * y + x * x) + 1e-08f)));
            dirTmp.x = inv * x; dirTmp.y = inv * y; dirTmp.z = inv * z;
            dp = &dirTmp;
        }
        up.x = dp->x; up.y = dp->y; up.z = dp->z;

        Vector3 facing;
        if (!hasCamera) {
            Vector3 tmp2;
            const Vector3* fp = obj->GetDirection(&tmp2);
            facing.x = fp->x; facing.y = fp->y; facing.z = fp->z;
        } else {
            if ((camDir.z * up.z + camDir.y * up.y) + camDir.x * up.x > 0.0f) continue;
            Vector3 d = { camPos.x - pp->x, camPos.y - pp->y, camPos.z - pp->z };
            Vector3 n;
            const Vector3* np = normalized_safe(&n, &d);
            float dd = (np->y * up.y + np->z * up.z) + up.x * np->x;
            facing.x = np->x - dd * up.x;
            facing.y = np->y - dd * up.y;
            facing.z = np->z - dd * up.z;
        }

        transforms.push_back_default();
        Transform* t = transforms.m_end - 1;
        Matrix3 m;
        const Matrix3* r = Matrix3FromFacingAndUp(&m, &facing, &up);
        t->m_rot = *r;
        t->m_flags |= 2;
        t->m_count += 1;

        if (!terrainMode) {
            Vector3 off = { pp->x + up.x * 0.5f, pp->y + up.y * 0.5f, pp->z + up.z * 0.5f };
            t->m_offset = off;
            t->m_flags |= 4;
            t->m_count += 1;
            float sc = obj->GetScale() * 1.5f;
            t->m_count += 1;
            t->m_scale = sc;
        } else {
            float sc = obj->GetScale() * 1.5f;
            t->m_count += 1;
            t->m_scale = sc;
            float s = obj->DistanceToCamera() * 0.010000001f;
            s = _mm_cvtss_f32(_mm_min_ss(_mm_max_ss(_mm_set_ss(s), _mm_set_ss(0.1f)), _mm_set_ss(0.5f)));
            Vector3 off = { pp->x + s * up.x, pp->y + s * up.y, pp->z + s * up.z };
            t->m_flags |= 4;
            t->m_count += 1;
            t->m_offset = off;
        }

        float fade = 1.0f;
        if (m_fadeMode == 0 && dist > 200.0f)
            fade = 1.0f - (dist - 200.0f) * 0.01f;
        else if (m_fadeMode == 1 && 300.0f > dist)
            fade = (dist - 200.0f) * 0.01f;
        if (alphas.m_end < alphas.m_cap) {
            if (alphas.m_end) *alphas.m_end = fade;
            alphas.m_end++;
        } else {
            alphas.grow_push_back(alphas.m_end, fade);
        }
    }

    // ---- emit one quad per transform ----
    if (transforms.m_begin != transforms.m_end) {
        int total = (int)(transforms.m_end - transforms.m_begin);
        int i = 0;
        while (i < total) {
            char* vb;
            int stride;
            int got = sink->Lock(total - i, &vb, &stride);
            if (!got) break;
            int limit = got + i;
            for (; i < limit; ++i) {
                const Transform* t = &transforms.m_begin[i];
                float zero = 0.0f, one = 1.0f;
                Vector3 A = { one, zero, zero };
                Vector3 B = { zero, one, zero };
                if (t->m_flags & 2) {
                    const float* mm = t->m_rot.m;
                    A.y = (mm[7] + mm[4]) * zero + mm[1];
                    A.x = (mm[6] + mm[3]) * zero + mm[0];
                    A.z = (mm[8] + mm[5]) * zero + mm[2];
                    B.x = (mm[6] + mm[0]) * zero + mm[3];
                    B.y = (mm[7] + mm[1]) * zero + mm[4];
                    B.z = (mm[8] + mm[2]) * zero + mm[5];
                }
                float s = t->m_scale;
                A.x *= s; A.y *= s; A.z *= s;
                B.x *= s; B.y *= s; B.z *= s;

                float a = alphas.m_begin[i];
                if (m_mode == 1) a *= 0.5f;
                uint32_t color = (((ColorByte(a) << 8 | ColorByte(1.0f)) << 8 | ColorByte(0.95f)) << 8) | ColorByte(0.6f);

                float px = t->m_offset.x, py = t->m_offset.y, pz = t->m_offset.z;
                float lx = px - A.x, ly = py - A.y, lz = pz - A.z;   // P - A
                float rx = px + A.x, ry = py + A.y, rz = pz + A.z;   // P + A
                static const float uv[4][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
                float vx[4] = { lx - B.x, rx - B.x, rx + B.x, lx + B.x };
                float vy[4] = { ly - B.y, ry - B.y, ry + B.y, ly + B.y };
                float vz[4] = { lz - B.z, rz - B.z, rz + B.z, lz + B.z };
                for (int k = 0; k < 4; ++k) {
                    float* pos = (float*)(vb + m_posOffset);
                    pos[0] = vx[k]; pos[1] = vy[k]; pos[2] = vz[k];
                    *(uint32_t*)(vb + m_colorOffset) = color;
                    ((float*)(vb + m_uvOffset))[0] = uv[k][0];
                    ((float*)(vb + m_uvOffset))[1] = uv[k][1];
                    vb += stride;
                }
            }
            sink->Unlock();
        }
    }

    // ---- cleanup of the three containers ----
    for (cSpatialObject** p = objects.m_begin; p < objects.m_end; ++p)
        if (*p) (*p)->Release();
    if (objects.m_begin && ((int*)objects.m_begin)[-1] != 0)
        operator delete[](objects.m_begin);
    if (alphas.m_begin && alphas.m_begin != alphas.m_fixed)
        operator delete[](alphas.m_begin);
    if (transforms.m_begin && transforms.m_begin != transforms.m_fixed)
        operator delete[](transforms.m_begin);
}
