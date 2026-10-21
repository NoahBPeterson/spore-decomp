// Slice s00f9c470 -- SP::cTerrainSphere surface-orientation builders and the terrain
// face basis/material loop (0x00f9c470 .. 0x00f9cd70).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE float, x87 for sqrt / reductions)
#include "types.h"
#include <math.h>
#include <string.h>

// ---- generic types ---------------------------------------------------------------------
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Quat { float x, y, z, w; };
struct Mat33 { float m0, m1, m2, m3, m4, m5, m6, m7, m8; };

// ---- globals referenced by absolute address -------------------------------------------
extern void*  g_sAppProperties;   // 0x015fd918
extern int*   g_p16c9f5c;         // 0x016c9f5c
extern const float g_e8c;         // 0x016c9e8c
extern const float g_e90;         // 0x016c9e90
extern const float g_e94;         // 0x016c9e94
extern const float g_f24;         // 0x016c9f24
extern const float g_f28;         // 0x016c9f28
extern const float g_f2c;         // 0x016c9f2c
extern const float g_f30;         // 0x016c9f30
extern const float g_f34;         // 0x016c9f34
extern const float g_f38;         // 0x016c9f38
extern const float g_f3c;         // 0x016c9f3c
extern const float g_f40;         // 0x016c9f40
extern const float g_f44;         // 0x016c9f44
extern const float g_8d4;         // 0x016ca584
extern const float g_8d8;         // 0x016ca588
extern const float g_8dc;         // 0x016ca58c
extern const float g_1c8;         // 0x015b11c8
extern const float g_1cc;         // 0x015b11cc
extern const float g_1d0;         // 0x015b11d0
extern const float g_1d4;         // 0x015b11d4
extern uint8_t g_faceRecs[6 * 0x40];  // 0x015b1340

// ---- external helpers ------------------------------------------------------------------
void*  __cdecl SP_App();                                          // 0x0067dd10
void*  __cdecl FUN_0067dd50();                                    // 0x0067dd50
Mat33* __cdecl Matrix3FromQuaternion(Mat33* out, const Quat* q);  // 0x0059c190
void*  __cdecl QuaternionFromMatrix33(Quat* out, const Mat33* m, float eps); // 0x00472b80
float* __cdecl FUN_0046d660(float* out, const float* m);          // 0x0046d660
Vec3*  __cdecl OrthogonalVector(Vec3* out, const Vec3* in);       // 0x006985b0
float* __cdecl normalized_safe(float* out, const float* in);      // 0x00449c20
struct cTerrainMapSet {
    float GetHeightAt(const void* pos);      // 0x00f927c0
};

// ---- property list / viewer ------------------------------------------------------------
struct cPropList {
    bool GetDescription(uint32_t id);        // 0x006a25a0
};
struct cViewerS {
    void Clear(uint32_t layer);              // 0x007c3c50
    void SetBasis(void* basis);              // 0x007c4d00
};
struct Basis3 {
    uint32_t flags;      // +0x00
    Vec4     vec;        // +0x04
    Mat33    mat;        // +0x14
    void Normalize(const void* rec);         // 0x006b92d0
};
struct AppArg { void* p0; void* p1; void* p2; void* p3; };

typedef void* (__thiscall *FnV)(void*);
typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnCall)(void*, int, int, int, void*, int, int);

// ---- cTerrainSphere surface-orientation API --------------------------------------------
struct cTS143 {
    Quat BuildSurfaceOrientation(const Vec3& a, const Vec3& b);              // 0x00f9c660
    Quat BuildSurfaceOrientationV(const Vec3& up, const Quat& q);            // 0x00f9c960
    Quat BuildPitchedSurfaceOrientation(const Vec3* pos, const Quat* q, float pitch); // 0x00f9cc50
};

extern const float kEps;          // 0x014904d0 = 1.5258789e-05f

// @ 0x00f9c470
void __stdcall FUN_00f9c470(int param_1, int param_2)
{
    void* appProps = g_sAppProperties;
    int i = 0;
    if (param_1 == 0) {
        void* app = SP_App();
        void* v = ((FnV)(*(void***)app)[0x50 / 4])(app);
        ((FnVoid)(*(void***)v)[0x1c / 4])(v);
    }
    int target = *g_p16c9f5c;
    bool has = ((cPropList*)appProps)->GetDescription(0x8a3a24da);
    int p2 = param_2;
    const uint8_t* rec = g_faceRecs;
    do {
        *(uint8_t*)(target + 0x12) = (uint8_t)i;
        ((cViewerS*)0x16ca260)->Clear(7);
        float mm[9] = { g_f24, g_f28, g_f2c, g_f30, g_f34, g_f38, g_f3c, g_f40, g_f44 };
        Basis3 s;
        s.flags = 0;
        s.vec.x = g_e8c; s.vec.y = g_e90; s.vec.z = g_e94; s.vec.w = 1.0f;
        memcpy(&s.mat, mm, sizeof(mm));
        s.Normalize(rec);
        ((cViewerS*)0x16ca260)->SetBasis(&s);
        AppArg a;
        a.p0 = (void*)0x16ca260; a.p1 = 0; a.p2 = 0; a.p3 = 0;
        void* o = FUN_0067dd50();
        int v7, v8;
        if (has) { v7 = 0x12; v8 = 0x12; } else { v7 = 5; v8 = 5; }
        ((FnCall)(*(void***)o)[0x40 / 4])(o, p2, v7, v8, &a, 0, 0);
        rec += 0x40;
        ++i;
    } while ((int)rec < 0x15b14c0);
}

// @ 0x00f9c660
Quat cTS143::BuildSurfaceOrientation(const Vec3& a, const Vec3& b)
{
    float ax = a.x;
    Quat out;
    if ((a.y * a.y + a.z * a.z) + ax * ax < kEps) goto degenerate;
    {
        float bx = b.x;
        if ((bx * bx + b.y * b.y) + b.z * b.z < kEps) goto degenerate;
        float inv = 1.0f / sqrtf((a.y * a.y + a.z * a.z) + ax * ax);
        float x1 = ax * inv;
        float z1 = inv * a.z;
        float y1 = inv * a.y;
        Vec3 na; na.x = x1; na.y = y1; na.z = z1;
        float c0 = b.y * z1 - b.z * y1;
        float c1 = b.z * x1 - bx * z1;
        float c2 = y1 * bx - b.y * x1;
        float len = sqrtf(c0 * c0 + (c2 * c2 + c1 * c1));
        if (len < kEps) {
            Vec3 ortho;
            Vec3* o = OrthogonalVector(&ortho, &na);
            float* p = normalized_safe((float*)&ortho, (const float*)o);
            c0 = p[0]; c1 = p[1]; c2 = p[2];
        } else {
            float f = 1.0f / len;
            c0 *= f; c1 *= f; c2 *= f;
        }
        float d0 = c2 * y1 - c1 * z1;
        float d1 = z1 * c0 - c2 * x1;
        float d2 = c1 * x1 - y1 * c0;
        float dl = sqrtf(d2 * d2 + (d1 * d1 + d0 * d0));
        if (dl < kEps) goto degenerate;
        float f = 1.0f / dl;
        Mat33 M;
        M.m0 = c0;    M.m1 = c1;    M.m2 = c2;
        M.m3 = d0 * f; M.m4 = d1 * f; M.m5 = d2 * f;
        M.m6 = x1;    M.m7 = y1;    M.m8 = z1;
        FUN_0046d660((float*)&out, (const float*)&M);
        return out;
    }
degenerate:
    out.x = g_1c8; out.y = g_1cc; out.z = g_1d0; out.w = g_1d4;
    return out;
}
// @ 0x00f9c960
Quat cTS143::BuildSurfaceOrientationV(const Vec3& a, const Quat& q)
{
    Mat33 M;
    Matrix3FromQuaternion(&M, &q);
    float ax = a.x, ay = a.y, az = a.z;
    float inv = 1.0f / sqrtf((ax * ax + ay * ay) + az * az);
    float x1 = ax * inv;
    float y1 = ay * inv;
    float z1 = az * inv;
    float f4 = (M.m3 * g_8d8 + M.m6 * g_8dc) + M.m0 * g_8d4;
    float f5 = M.m7 * g_8dc + (M.m1 * g_8d4 + M.m4 * g_8d8);
    float f6 = (M.m5 * g_8d8 + M.m2 * g_8d4) + M.m8 * g_8dc;
    if (0.999f < fabsf(f4 * x1 + (f6 * z1 + f5 * y1))) {
        return q;
    }
    float e0 = f5 * z1 - f6 * y1;
    float e1 = f6 * x1 - f4 * z1;
    float e2 = y1 * f4 - f5 * x1;
    float t = 1.0f / sqrtf(e1 * e1 + (e2 * e2 + e0 * e0));
    float e0n = e0 * t;
    float e1n = e1 * t;
    float e2n = e2 * t;
    float g0 = e2n * y1 - e1n * z1;
    float g1 = e1n * x1 - y1 * e0n;
    float g2 = e0n * z1 - e2n * x1;
    float u = 1.0f / sqrtf(g2 * g2 + (g1 * g1 + g0 * g0));
    Mat33 M2;
    M2.m0 = e0n; M2.m1 = e1n; M2.m2 = e2n;
    M2.m3 = g0 * u; M2.m4 = g2 * u; M2.m5 = g1 * u;
    M2.m6 = x1; M2.m7 = y1; M2.m8 = z1;
    Quat out;
    QuaternionFromMatrix33(&out, &M2, 0.0f);
    return out;
}

// @ 0x00f9cc50
Quat cTS143::BuildPitchedSurfaceOrientation(const Vec3* pos, const Quat* q, float pitch)
{
    Mat33 M;
    Matrix3FromQuaternion(&M, q);
    float px = pos->x, py = pos->y, pz = pos->z;
    float p70 = px + M.m3 * pitch;
    float p68 = M.m5 * pitch + pz;
    float p6c = py + M.m4 * pitch;
    Vec3 v; v.x = p70; v.y = p6c; v.z = p68;
    float h = (*(cTerrainMapSet**)((uint8_t*)this + 0x2c))->GetHeightAt(&v);
    float inv = 1.0f / sqrtf((p70 * p70 + (p68 * p68 + p6c * p6c)) + 1e-08f);
    float q6c = (p6c * inv) * h - py;
    float q70 = (inv * p70) * h - px;
    float q68 = (p68 * inv) * h - pz;
    float f8 = (M.m1 * pitch + py) - py;
    float f6 = (M.m0 * pitch + px) - px;
    float f7 = (M.m2 * pitch + pz) - pz;
    float c58 = f8 * q68 - f7 * q6c;
    float c54 = f7 * q70 - q68 * f6;
    float c50 = q6c * f6 - f8 * q70;
    float len1 = (c58 * c58 + c50 * c50) + c54 * c54;
    if (kEps <= len1) {
        float g7 = c50 * q6c - c54 * q68;
        float g9 = q68 * c58 - c50 * q70;
        float g8 = c54 * q70 - q6c * c58;
        float len2 = (g7 * g7 + g8 * g8) + g9 * g9;
        if (kEps <= len2) {
            float a = 1.0f / sqrtf(len1);
            float n50 = c50 * a;
            float n58 = a * c58;
            float n54 = c54 * a;
            float b = 1.0f / sqrtf(len2);
            float m0 = b * g7;
            float m1 = g9 * b;
            float m2 = g8 * b;
            float c = 1.0f / sqrtf(q6c * q6c + (q68 * q68 + q70 * q70));
            float r6c = q6c * c;
            float r70 = c * q70;
            float r68 = q68 * c;
            Mat33 M2;
            M2.m0 = m0;  M2.m1 = m1;  M2.m2 = m2;
            M2.m3 = r70; M2.m4 = r6c; M2.m5 = r68;
            M2.m6 = n58; M2.m7 = n54; M2.m8 = n50;
            Quat tmp;
            QuaternionFromMatrix33(&tmp, &M2, 0.0f);
            return tmp;
        }
    }
    return *q;
}
