// Slice s0101c780: SP::cSPSpacePlanetCameraController member at 0x0101c780 (2469 bytes, mixed SSE + x87).
// High-level reconstruction of the space-planet camera orbit/target update.
// Thiscall (this = ecx, saved in ebp), 8 stack dwords (ret 0x20).
#include <math.h>
#include "types.h"

#pragma pack(push, 4)

namespace SP {

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Vec4 { float x, y, z, w; Vec4() {} Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };

static inline float Dot3(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline float Len3(const Vec3& a) { return (float)sqrt((double)Dot3(a, a)); }
static inline Vec3 Sub3(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vec3 Cross3(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// Constants referenced by 0x0101c780.
extern float g_1477fbc;  // 0x1477fbc (200.0f)
extern float g_13eb1bc;  // 0x13eb1bc (-1.0f, the card's "g_zero" label is wrong)
extern float g_15b6dbc;  // 0x15b6dbc (solar min-zoom rate)

struct cPlanetModel {
    float GetRadius();  // 0xb7e4d0
};
cPlanetModel* __cdecl PlanetModel();  // 0xb3d350

struct cCameraFrame {
    char data[0x40];
    cCameraFrame* Initialize(void* viewer);  // 0xb16dc0  ?Initialize@cCameraFrame@@QAEPAU1@PAVcViewer@SP@@@Z
};

struct cSPSimulatorSpaceGame {
    void* GetPlayerInventory();  // 0xa1ad60
};

void* __cdecl App();            // 0x67dd10
void* __cdecl GetUFOSimulator();  // 0xffbe50

// Path/water query helpers (free cdecl, caller cleans).
extern "C" char __cdecl FUN_00b182f0(void*, int);                     // 0xb182f0
extern "C" char __cdecl FUN_00b17c10(void*, void*);                   // 0xb17c10
extern "C" char __cdecl FUN_00b17810(void*, void*);                   // 0xb17810
extern "C" char __cdecl FUN_00b181d0(void*, float*);                  // 0xb181d0
extern "C" void __cdecl FUN_00b16490(void*, float);                   // 0xb16490
extern "C" void __cdecl FUN_00b16450(void*, void*);                   // 0xb16450
extern "C" void __cdecl FUN_00b16e50(void*, void*);                   // 0xb16e50

// Vector/quaternion helpers.
extern "C" float* __cdecl FUN_0059aed0(float* out, float* a, float* b);  // 0x59aed0
extern "C" void __cdecl FUN_00799320(float* out, const float* in);       // 0x799320

// Workspace used by the path/water queries; the origin vector is its first field.
struct cShapeQuery {
    Vec3 origin;        // +0x00
    char rest[0x1fc];
    void FUN_00b17790(int enable);  // 0xb17790
};

class cSPSpacePlanetCameraController {
public:
    char pad00[0x6c];
    float mPlanetFarZoomHeight;    // +0x6c
    char pad70[0x78 - 0x70];
    float mSolarMinZoom;           // +0x78
    char pad7c[0x84 - 0x7c];
    float mSolarZoomRateMax;       // +0x84
    char pad88[0x90 - 0x88];
    float mWantDebugSolarPullOut;  // +0x90
    Vec3  mGalaxyZoom;             // +0x94: x = min zoom, y = max zoom, z = rate min
    char padA0[0x198 - 0xa0];
    union { float f; uint32_t u; } mCurrentMatrixYAxisX;  // +0x198 (bit 0 is OR-ed in)
    char pad19c[0x200 - 0x19c];

    void FUN_0101c780(float a1, float* a2, float* a3, float* a4,
                      float a5, int a6, float a7, float a8);
    float* GetUFOPosition();  // 0x1017b70
    void UpdateCameraPitchRotation(float a1, float a8, Vec3* a3, Vec3* a2);  // 0x1019950
};

// Raw vtable dispatch used for the App()->viewer chain (no argument).
static void* VCall0(void* obj, int byte_offset)
{
    void** vt = *(void***)obj;
    typedef void* (__fastcall* Fn)(void*);
    return ((Fn)vt[byte_offset / 4])(obj);
}

// @ 0x0101c780
void cSPSpacePlanetCameraController::FUN_0101c780(float a1, float* a2, float* a3, float* a4,
                                                  float a5, int a6, float a7, float a8)
{
    (void)a5; (void)a6;

    Vec3 P(a2[0], a2[1], a2[2]);
    if (Len3(P) >= PlanetModel()->GetRadius() + g_1477fbc)
        return;

    // Bring up a camera frame for the current viewer.
    void* app = App();
    if (app != 0) {
        void* viewer = VCall0(app, 0x50);
        if (viewer != 0) {
            void* viewer2 = VCall0(viewer, 0x1c);
            cCameraFrame frame;
            frame.Initialize(viewer2);
        }
    }

    Vec3 A(a3[0], a3[1], a3[2]);
    Vec3 B(a4[0], a4[1], a4[2]);

    cShapeQuery query;
    query.origin = P;
    Vec3 savedA = A;

    bool want_debug = (mWantDebugSolarPullOut != 0.0f) || (a7 != 0.0f);
    bool flag = false;
    bool moved = false;

    char hit = FUN_00b182f0(&query, 0x18);
    if (hit == 0) {
        hit = FUN_00b17c10(&query, 0);
        if (hit == 0)
            hit = FUN_00b17810(&query, 0);
    }
    if (hit != 0) {
        flag = true;
        moved = true;
    }

    if (want_debug && flag) {
        cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)GetUFOSimulator();
        if (sim != 0)
            sim->GetPlayerInventory();

        float* ufo = GetUFOPosition();
        if (ufo != 0) {
            Vec3 U(ufo[0], ufo[1], ufo[2]);
            float inv = 1.0f / Len3(U);
            float half = -(mWantDebugSolarPullOut * 0.5f);
            float s = (float)sin((double)half);
            float c = (float)cos((double)half);
            Vec4 rotq(s * inv * U.x, s * inv * U.y, s * inv * U.z, c);

            float rotq_n[4];
            FUN_00799320(rotq_n, &rotq.x);

            Vec4 galres;
            FUN_0059aed0(&galres.x, &mGalaxyZoom.x, rotq_n);
            mGalaxyZoom = Vec3(galres.x, galres.y, galres.z);

            float neg = mPlanetFarZoomHeight * g_13eb1bc;
            Vec3 target(A.x + galres.x * neg, A.y + galres.y * neg, A.z + galres.z * neg);

            Vec3 axis = Cross3(target, A);
            float inv2 = 1.0f / Len3(axis);
            float half2 = -(mSolarZoomRateMax * 0.5f);
            float s2 = (float)sin((double)half2);
            float c2 = (float)cos((double)half2);
            Vec4 rot2(s2 * inv2 * axis.x, s2 * inv2 * axis.y, s2 * inv2 * axis.z, c2);

            float rot2_n[4];
            FUN_00799320(rot2_n, &rot2.x);

            Vec3 delta = Sub3(target, A);
            Vec4 deltaq(delta.x, delta.y, delta.z, 0.0f);
            float out2[4];
            FUN_0059aed0(out2, &deltaq.x, rot2_n);
            Vec3 p3(A.x + out2[0], A.y + out2[1], A.z + out2[2]);

            float solar_min = mSolarMinZoom;
            mCurrentMatrixYAxisX.u |= 1u;
            mSolarMinZoom = solar_min - a7;

            UpdateCameraPitchRotation(a1, a8, &A, &p3);
            savedA = A;
            query.FUN_00b17790(1);
        }
    }

    float clearance = 0.0f;
    if (FUN_00b181d0(&query, &clearance) != 0) {
        FUN_00b16490(&query, clearance);
        query.FUN_00b17790(1);
    }

    char bufA[0x100];
    char bufB[0x40];
    struct PathOut { void* p1; void* p2; void* p3; int pad; } po;
    po.p1 = bufA;
    po.p2 = bufA;
    po.p3 = bufB;
    po.pad = 0;
    if (FUN_00b17c10(&query, &po) != 0) {
        moved = true;
        FUN_00b16450(&query, &po);
        query.FUN_00b17790(1);
    }

    struct AuxOut { int pad; char data[0x80]; } aux;
    aux.pad = 0;
    if (FUN_00b17810(&query, &aux) != 0) {
        moved = true;
        FUN_00b16e50(&query, &aux);
        query.FUN_00b17790(1);
    }

    a2[0] = query.origin.x;
    a2[1] = query.origin.y;
    a2[2] = query.origin.z;
    a3[0] = savedA.x;
    a3[1] = savedA.y;
    a3[2] = savedA.z;

    if (moved)
        mSolarMinZoom = mSolarMinZoom - g_15b6dbc * a1;
}

} // namespace SP

#pragma pack(pop)
