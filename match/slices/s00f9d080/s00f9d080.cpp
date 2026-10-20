// s00f9d080 -- SP::cTerrainSphere surface / footprint / scatter-texture helpers.
// Object file: SPTerrain/SPTerrainSphere.obj.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
//   0x00f9d080 BuildSurfaceNormalOrientation
//   0x00f9d5c0 DrawFootprint
//   0x00f9d9b0 UpdateScatterTexture
#include "types.h"
#include <math.h>
#include <string.h>

namespace SP {

// ---------------------------------------------------------------- math types
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct Quaternion { float x, y, z, w; };
struct Matrix33 { Vector3 xAxis, yAxis, zAxis; };   // 9 floats

// ---------------------------------------------------------------- externals
Matrix33&   Matrix3FromQuaternion(Matrix33& out, const Quaternion& q);                // 0x0059c190
Quaternion* QuaternionFromMatrix33(Quaternion* out, const Matrix33& m, float w);       // 0x00472b80
int*        CoordToIndex(int* out, int size, float* uv);                               // 0x00684bf0
void*       GetImageResource(void* out, void* stream);                                 // 0x00576650
void*       MemSet(void* dst, int v, unsigned n);                                      // 0x011e073e (memset)
void*       MaterialManager();                                                         // 0x0067dd70
void        ShaderCall(int id, void* data, int flag);                                  // 0x00777ae0
float       SceneQueryA(void* scene);                                                  // 0x00fb7b90
void        RasterStageUpdate(int face);                                               // 0x007c3cb0 (this=0x016c9f60)
bool        RasterViewerUpdate();                                                      // 0x007c4fd0 (this=0x016c9f60)
void        RasterFlushStage();                                                        // 0x007c3c10 (this=0x016c9f60)

struct cTerrainMapSet;

class cTerrainEditor {
 public:
  float GetRandom01();                                                                 // 0x00f678d0
  void  BuildDecal(const Vector3* pos, const Quaternion* orient, float size, void* decal,
                   void* target, void* arg6, uint32_t arg7, uint32_t arg8, void* rects,
                   uint32_t arg10);                                                    // 0x00f6c940
};
cTerrainEditor* TerrainEditor();                                                       // 0x00f48a70

struct cTerrainMapSet {
  float GetHeightAt(const Vector3& v) const;                                           // 0x00f927c0
};

// Default (identity) decal-target descriptor template, .rdata 0x01490428 (0x44 bytes).
static const uint32_t kDecalTargetTemplate[17] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3f800000,
  0x00000007, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000,
};

// Per-face quad corner UV table, .rdata 0x015b1220 (6 faces * 0x30 bytes).
static const uint32_t kFaceUVTable[6][12] = {
  { 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000, 0xbf800000,
    0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000, 0x3f800000 },
  { 0xbf800000, 0xbf800000, 0xbf800000, 0xbf800000, 0xbf800000, 0x3f800000,
    0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000, 0xbf800000 },
  { 0xbf800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
    0x3f800000, 0x3f800000, 0xbf800000, 0xbf800000, 0x3f800000, 0xbf800000 },
  { 0xbf800000, 0xbf800000, 0xbf800000, 0x3f800000, 0xbf800000, 0xbf800000,
    0x3f800000, 0xbf800000, 0x3f800000, 0xbf800000, 0xbf800000, 0x3f800000 },
  { 0xbf800000, 0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000,
    0x3f800000, 0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000 },
  { 0x3f800000, 0xbf800000, 0xbf800000, 0xbf800000, 0xbf800000, 0xbf800000,
    0xbf800000, 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000 },
};

// Scatter-raster dirty bookkeeping (rw graphics global state).
extern uint32_t g_rasterStageDirty;             // 0x016fa3a8
extern void*    g_rasterSlots[17];              // 0x016f9650
extern uint8_t  g_scatterDescFlag;             // 0x016ca5a4
extern char*    g_appProps;                    // 0x015fd918

// ---------------------------------------------------------------- the object
class cTerrainSphere {
 public:
  virtual void  v00(); virtual void v04(); virtual void v08();
  virtual void* GetQuadContainer();                                                    // +0x0c
  virtual void* GetScene();                                                            // +0x10
  virtual void  v14(); virtual void v18(); virtual void v1c(); virtual void v20();
  virtual void  v24(); virtual void v28(); virtual void v2c(); virtual void v30();
  virtual void  v34(); virtual void v38(); virtual void v3c(); virtual void v40();
  virtual void  v44(); virtual void v48(); virtual void v4c(); virtual void v50();
  virtual void  v54(); virtual void v58(); virtual void v5c(); virtual void v60();
  virtual void  v64();

  char  pad00[0x2c];
  cTerrainMapSet* mpMapSet;                                                            // +0x2c
  char  pad30[0x928 - 0x30];
  void* mpScatterRaster;                                                               // +0x928

  Quaternion BuildSurfaceNormalOrientation(const Vector3& pos, const Quaternion& baseQuat,
                                           float pitch) const;
  void DrawFootprint(void* xform, float z, void* img, const Vector2* off, bool flag,
                     void* faceBoxes, void* a3);
  void UpdateScatterTexture(int face, void* raster, const Vector3& dir, void* stats);
};

// ================================================================ 0x00f9d080
// @ 0x00f9d080
Quaternion cTerrainSphere::BuildSurfaceNormalOrientation(const Vector3& pos,
                                                         const Quaternion& baseQuat,
                                                         float pitch) const
{
    Matrix33 mat;
    Matrix3FromQuaternion(mat, baseQuat);

    cTerrainMapSet* mapSet = mpMapSet;
    float h0 = mapSet->GetHeightAt(pos);

    float invLen = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-08f);
    float px = (pos.x * invLen) * h0;
    float py = h0 * (pos.y * invLen);
    float pz = (pos.z * invLen) * h0;

    Vector3 A;
    A.x = mat.yAxis.x * pitch + px;
    A.y = mat.yAxis.y * pitch + py;
    A.z = mat.yAxis.z * pitch + pz;
    Vector3 B;
    B.x = mat.xAxis.x * pitch + px;
    B.y = mat.xAxis.y * pitch + py;
    B.z = mat.xAxis.z * pitch + pz;

    float hA = mapSet->GetHeightAt(A);
    float ilA = 1.0f / sqrtf(A.x * A.x + A.y * A.y + A.z * A.z + 1e-08f);
    float dAx = (ilA * A.x) * hA - px;
    float dAy = (A.y * ilA) * hA - py;
    float dAz = (A.z * ilA) * hA - pz;

    float hB = mapSet->GetHeightAt(B);
    float ilB = 1.0f / sqrtf(B.x * B.x + B.y * B.y + B.z * B.z + 1e-08f);
    float dBx = (ilB * B.x) * hB - px;
    float dBy = (B.y * ilB) * hB - py;
    float dBz = (B.z * ilB) * hB - pz;

    float c0 = dBy * dAz - dBz * dAy;
    float c1 = dBz * dAx - dAz * dBx;
    float c2 = dAy * dBx - dBy * dAx;
    float len2 = (c2 * c2 + c1 * c1) + c0 * c0;

    if (1.5258789e-05f <= len2) {
        float e0 = c2 * dAy - c1 * dAz;
        float e1 = dAz * c0 - c2 * dAx;
        float e2 = c1 * dAx - dAy * c0;
        float len2b = (e2 * e2 + e1 * e1) + e0 * e0;
        if (1.5258789e-05f <= len2b) {
            float n0 = 1.0f / sqrtf(len2);
            float nz = c2 * n0;
            float ny = c1 * n0;
            float nx = n0 * c0;
            float m0 = 1.0f / sqrtf(len2b);
            float ex = e0 * m0;
            float ey = e1 * m0;
            float ez = e2 * m0;
            float s0 = 1.0f / sqrtf(dAx * dAx + dAy * dAy + dAz * dAz);
            float sx = s0 * dAx;
            float sy = dAy * s0;
            float sz = dAz * s0;

            Matrix33 out;
            out.xAxis.x = ex;  out.xAxis.y = ey;  out.xAxis.z = ez;
            out.yAxis.x = sx;  out.yAxis.y = sy;  out.yAxis.z = sz;
            out.zAxis.x = nx;  out.zAxis.y = ny;  out.zAxis.z = nz;

            Quaternion q;
            QuaternionFromMatrix33(&q, out, 0.0f);
            return q;
        }
    }
    return baseQuat;
}

// ================================================================ 0x00f9d5c0
// @ 0x00f9d5c0
void cTerrainSphere::DrawFootprint(void* xform, float z, void* img, const Vector2* off,
                                   bool flag, void* faceBoxes, void* a3)
{
    // image resource holder (0x78 bytes): [0]=refcount/type, [4]=no-image flag, [8]=1.0f
    char imageRes[0x78];
    MemSet(imageRes, 0, 0x78);
    GetImageResource(imageRes, img);
    imageRes[4] = (img == 0) ? 1 : 0;
    imageRes[8] = 1.0f;
    imageRes[5] = 0;
    imageRes[6] = 0;
    *(uint32_t*)(imageRes + 0x3c) = 0;

    float fVar8 = off->x;
    float height;
    int face;

    if (fVar8 == 0.0f && off->y == 0.0f) {
        // pick the cube face from the direction packed into the transform
        float dx = *(float*)((char*)xform + 4);
        float dy = *(float*)((char*)xform + 8);
        float dz = *(float*)((char*)xform + 0xc);
        int map = *(int*)((char*)mpMapSet + 8);
        float ax = fabsf(dx), ay = fabsf(dy), az = fabsf(dz);
        float u, v;
        face = 3;
        if (az < ax || az < ay) {
            if (ay < ax) {
                u = (dy / dx + 1.0f) * 0.5f;
                v = (dz / ax + 1.0f) * 0.5f;
                face = (dx < 0.0f) ? 3 : 2;
            } else {
                u = (dz / dy + 1.0f) * 0.5f;
                v = (dx / ay + 1.0f) * 0.5f;
                face = (dy < 0.0f) ? 5 : 4;
            }
        } else {
            u = (dx / az + 1.0f) * 0.5f;
            v = (dy / az + 1.0f) * 0.5f;
            face = (dz < 0.0f) ? 1 : 0;
        }
        int idx[3];
        CoordToIndex(idx, map, &u);
        int sz = *(int*)(map + 8);
        unsigned short* heights = *(unsigned short**)(map + 0x10);
        int i = ((idx[2] * sz + idx[1]) * sz + idx[0]);
        height = (float)(int)(heights[i] - 0x8000) * 3.051851e-05f;
        if (flag) {
            cTerrainEditor* ed = TerrainEditor();
            float r = (ed->GetRandom01() + ed->GetRandom01()) - 1.0f + 0.03f;
            if (r <= height)
                r = height;
            height = r;
        }
        (void)face;
    } else {
        face = 4;
        float a = fVar8;
        float b = off->y;
        float delta = 0.0f;
        if (flag) {
            cTerrainEditor* ed = TerrainEditor();
            delta = (ed->GetRandom01() + ed->GetRandom01()) - 1.0f;
        }
        fVar8 = delta + a;
        height = delta + b;
        (void)face;
    }

    // decal-target descriptor (0x7c bytes)
    char target[0x7c];
    MemSet(target, 0, 0x7c);
    memcpy(target + 4, kDecalTargetTemplate, sizeof(kDecalTargetTemplate));
    target[0] = 0;
    target[1] = 0;
    *(uint32_t*)(target + 0x48) = 0;
    *(uint32_t*)(target + 0x54) = 0;

    float size = *(float*)((char*)xform + 0x10);

    Quaternion q;
    QuaternionFromMatrix33(&q, *(Matrix33*)((char*)xform + 0x14), 0.0f);

    cTerrainEditor* ed = TerrainEditor();
    ed->BuildDecal((const Vector3*)((char*)xform + 4), &q, size, imageRes, target, a3, 0, 0,
                   faceBoxes, 0);
    (void)z;
    (void)height;
}

// ================================================================ 0x00f9d9b0
// @ 0x00f9d9b0
void cTerrainSphere::UpdateScatterTexture(int face, void* raster, const Vector3& dir, void* stats)
{
    *(char*)((char*)raster + 0x12) = (char)face;

    void** mm = (void**)MaterialManager();
    void* vtbl = *mm;
    int (*getMaterial)(void*, uint32_t) = (int (*)(void*, uint32_t)) * (void**)((char*)vtbl + 0x28);
    int* mat = (int*)getMaterial(mm, 0x1a856cf3);
    if (*(int*)((char*)mat + 4) == 0)
        return;

    // Shader descriptor.  In the original the fields live in a stack block; the
    // 0x00fb7b90 float query sits at scratch+0x00 and the raster lock buffer at
    // scratch+0x2c (0x100 bytes cleared).
    char scratch[0x12c];
    float* d = (float*)scratch;                 // scratch offsets == original +0x10
    MemSet(scratch + 0x2c, 0, 0x100);

    void* scene1 = GetScene();
    void* scene2 = GetScene();
    d[0] = SceneQueryA(scene2);
    float* fs = (float*)((char*)scene1 + 0x2f4);

    d[1] = fs[0x108 / 4];
    d[2] = fs[0x118 / 4];
    d[3] = fs[0x128 / 4];
    d[4] = 0.0f;
    if (g_scatterDescFlag != 0) {
        float c = (d[0] - 0.5f) * 2.0f;
        d[10] = 0.0f;                            // original +0x38
        d[5] = c;                                // original +0x24
        d[0] = (c >= 0.0f) ? c : 0.0f;           // original +0x10
    }
    d[11] = d[1];  d[12] = d[2];  d[13] = d[3];  d[14] = 0.0f;
    d[15] = (fs[0x108 / 4] * fs[0x10c / 4]) * 10.0f;
    d[16] = (fs[0x120 / 4] * fs[0x11c / 4]) * 10.0f;
    d[17] = (fs[0x130 / 4] * fs[0x12c / 4]) * 10.0f;
    d[18] = 0.0f;
    for (int i = 0; i < 11; ++i)
        d[19 + i] = fs[(0xd8 + 4 * i) / 4];
    d[30] = fs[0x104 / 4];                       // original +0x88
    d[7] = 0.0f;
    d[6] = 0.0f;
    d[8] = 1.0f;
    d[9] = d[0];                                 // original +0x34
    d[31] = 0.0f;                                // original +0x8c
    d[32] = 0.0f;                                // original +0x90
    d[33] = 1.0f;                                // original +0x94
    d[34] = d[9];                                // original +0x98

    ShaderCall(0x206, scratch + 0x2c, 0);

    uint32_t bit = 1;
    for (int i = 0; i < 17; ++i) {
        if (g_rasterSlots[i] == raster) {
            g_rasterStageDirty |= bit;
            g_rasterSlots[i] = 0;
        }
        bit <<= 1;
    }

    RasterStageUpdate(face);
    if (!RasterViewerUpdate())
        return;

    // Acquire the scatter raster's lock buffer (vtable +0xc), fill the 4 quad
    // corners with the per-face UV block, then commit (vtable +0x10).
    void* rast = mpScatterRaster;
    void* lock = 0;
    void* rv = *(void**)rast;
    bool ok = ((bool (*)(void*, void**, int, int, int)) * (void**)((char*)rv + 0x8))(
        rast, &lock, 0x1c, 4, 0);
    if (ok) {
        char* dst = (char*)lock;
        MemSet(dst, 0, 0x70);

        float(*c)[7] = (float(*)[7])dst;         // 4 corners, 0x1c bytes apart
        if (*(int*)(*(int*)(g_appProps + 0x3c) + 0x110) == 0) {
            const float unit[4][3] = { { -1.0f, -1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f },
                                       { -1.0f,  1.0f, 0.0f }, { 1.0f,  1.0f, 0.0f } };
            for (int i = 0; i < 4; ++i) { c[i][0] = unit[i][0]; c[i][1] = unit[i][1]; c[i][2] = unit[i][2]; }
        } else {
            const float wide[4][3] = { { -1.03125f, -0.96875f, 0.0f }, { 0.96875f, -0.96875f, 0.0f },
                                       { -1.03125f,  1.03125f, 0.0f }, { 0.96875f,  1.03125f, 0.0f } };
            for (int i = 0; i < 4; ++i) { c[i][0] = wide[i][0]; c[i][1] = wide[i][1]; c[i][2] = wide[i][2]; }
        }

        const uint32_t* uv = kFaceUVTable[face];
        c[0][4] = *(const float*)&uv[0];
        c[0][5] = *(const float*)&uv[1];
        c[0][6] = *(const float*)&uv[2];
        c[1][4] = *(const float*)&uv[3];
        c[1][5] = *(const float*)&uv[4];
        c[1][6] = *(const float*)&uv[5];
        c[2][4] = *(const float*)&uv[9];
        c[2][5] = *(const float*)&uv[10];
        c[2][6] = *(const float*)&uv[11];
        c[3][4] = *(const float*)&uv[6];
        c[3][5] = *(const float*)&uv[7];
        c[3][6] = *(const float*)&uv[8];

        ((void (*)(void*, void*, void*)) * (void**)((char*)rv + 0xc))(rast, mat, stats);
        ((void (*)(void*)) * (void**)((char*)rv + 0x10))(rast);
    }
    RasterFlushStage();
    (void)stats;
    (void)dir;
}

}  // namespace SP
