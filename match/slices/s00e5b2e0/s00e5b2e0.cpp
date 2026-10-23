// Slice s00e5b2e0 -- SPGonzago/SPCellGame.obj (batch spcg1).
// Cell-stage camera / UI helpers: move the avatar cell toward a camera-follow target,
// snap/lerp positions toward extents, build a facing matrix, and update the zoom buttons.
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU, no /EHsc).
//
// Layouts follow the dev-build PDB with retail offsets confirmed against the disassembly.
// gCellGame is cCellGame (mCells pool at +0x1c); gCellUI is the 0x16b3c0c cell UI/controller
// object. Camera forward is (0x16b3c28,0x16b3c2c,0x16b3c30); the world extent box is
// (0x16b3c88..0x16b3c9c) and the three basis vectors live at 0x15a7c28..0x15a7c48.
#include "types.h"
#include <string.h>
#include <math.h>

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

// ---------------------------------------------------------------- globals
extern char*  gCellGame;          // 0x016b3c04
extern char*  gCellUI;            // 0x016b3c0c

extern float  gFwd_16b3c28;       // 0x016b3c28  camera forward
extern float  gFwd_16b3c2c;       // 0x016b3c2c
extern float  gFwd_16b3c30;       // 0x016b3c30

extern float  gExt_16b3c88;       // 0x016b3c88  extent box (xmin,ymin,zmin,xmax,ymax,zmax)
extern float  gExt_16b3c8c;
extern float  gExt_16b3c90;
extern float  gExt_16b3c94;
extern float  gExt_16b3c98;
extern float  gExt_16b3c9c;

extern float  gBasis_15a7c28;     // 0x015a7c28  camera basis vectors (right/left/up)
extern float  gBasis_15a7c2c;
extern float  gBasis_15a7c30;
extern float  gBasis_15a7c34;
extern float  gBasis_15a7c38;
extern float  gBasis_15a7c3c;
extern float  gUp_15a7c40;        // 0x015a7c40  up axis
extern float  gUp_15a7c44;
extern float  gUp_15a7c48;

extern float  gK_14851e8;         // 0x014851e8  FLT_MAX (3.4028235e38) ray-t bound
extern float  gK_14851ec;         // 0x014851ec  1.5258789e-05f (2^-16)
extern float  gK_13ec5b4;         // 0x013ec5b4  1000.0f
extern float  gK_1485720;         // 0x01485720  1.0f
extern float  gK_13ec4b8;         // 0x013ec4b8  1e-08f
extern float  gK_13eb8b0;         // 0x013eb8b0  -0.0f
extern float  gK_1471064;         // 0x01471064  0.5f
extern float  gK_13ec480;         // 0x013ec480  0.2f
extern float  gK_13ec434;         // 0x013ec434  0.4f
extern float  gK_13ec4b0;         // 0x013ec4b0  0.6f
extern float  gK_1486374;         // 0x01486374  0.8f
extern float  gK_1483f64;         // 0x01483f64  8.0f
extern float  gK_13eecd8;         // 0x013eecd8  20.0f

extern float  gLvl_1477fbc;       // 0x01477fbc  level tier thresholds
extern float  gLvl_13f0e84;       // 0x013f0e84
extern float  gLvl_13fdcf8;       // 0x013fdcf8
extern float  gLvl_13fdcf4;       // 0x013fdcf4

extern float  gD_1488874;         // 0x01488874  camera-follow distance lerp constants
extern float  gD_1485544;         // 0x01485544
extern float  gD_13ebc5c;         // 0x013ebc5c
extern float  gD_1486110;         // 0x01486110

// ---------------------------------------------------------------- callees
extern "C" int   __cdecl       FUN_00e84470();                        // 0x00e84470 (returns char)
extern "C" int   __cdecl       FUN_00e50730();                        // 0x00e50730 (config)
extern "C" void* __cdecl       LayerCatalog_ApplyA(void* out);        // 0x00e4ce40
extern "C" void  __cdecl       FUN_00743b50(void* out);               // 0x00743b50
extern "C" void  __cdecl       FUN_00e82130(void* p);                 // 0x00e82130
extern "C" void* __cdecl       QuaternionFromFacingAndUp(void* out, float* facing, float* up); // 0x0069b600
extern "C" void* __cdecl       Matrix3FromFacingAndUp(void* out, float* facing, float* up);    // 0x0069b440
extern "C" unsigned __cdecl    FUN_00e87200(int handle, float* a, float* b, void* c, unsigned d, float e); // 0x00e87200
extern "C" void  __cdecl       FUN_00e836f0(unsigned id, float* a, float* b);                  // 0x00e836f0
extern "C" float __cdecl       FUN_00e513d0(float a, float b, float c, float d, float e);      // 0x00e513d0 (lerp)
extern "C" float __cdecl       FUN_01041cd0(float a, float b, float x);                        // 0x01041cd0
extern "C" void* __cdecl       FUN_00e5b0a0(void* out, void* a, void* b, void* c);             // 0x00e5b0a0
extern "C" void  __cdecl       FUN_00e51060(int zoom);                                         // 0x00e51060 (zoom)

// thiscall callees modelled as members (cl 7.1 rejects __thiscall on free functions)
struct cObjectPool     { void* GetSafe(int id); };                     // 0x00b721d0
struct cViewer         { void  GetCameraRay(float* origin, float* dir); }; // 0x007c4900
struct cSPUILayout     { void* FindWindowByID(unsigned id, int find); };// 0x008105b0
struct cLocalInputState{ void  OnMouseUp(int, float, float, int); };   // 0x00697af0

// The app object (0x0067dd10) is the standard cIApp; slot +0x58 is GetViewer.
struct cViewer;
struct cIApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cViewer* GetViewer();   // +0x58
};
cIApp* SP_App();   // 0x0067dd10

// window objects reached through the layout. Slots used here: +0x0c returns a sub-window
// pointer (takes an id), +0x20 returns a char state, +0x7c takes two ints.
struct cUIWindow {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cUIWindow* SubWindow(unsigned id);   // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual char State();                        // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void v74(); virtual void v78();
    virtual void SetButton(int state, int enable); // +0x7c
};

namespace SP { struct cCellMode { bool OnMouseUp(int, float, float, int); }; }  // 0x00e5c0f0

// ---------------------------------------------------------------- 0x00e5b2e0
// Move the avatar cell's position toward a camera-follow target derived from the four
// directional key states (each adds/subtracts a basis vector), then normalise, push through
// the follow helper 0x00e5b0a0 and offset the cell position by 20 units along the result.
// @ 0x00e5b2e0
void FUN_00e5b2e0(float param)
{
    char* p = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
    if (p == 0) return;

    float dx = gFwd_16b3c28;
    float dy = gFwd_16b3c2c;
    float dz = gFwd_16b3c30;

    // key state 1: bit (FUN_00e84470()? 0x5a : 0x57) of the key dword, or bits 6/8 elsewhere
    {
        unsigned b = FUN_00e84470() ? 0x5a : 0x57;
        if (((*(unsigned*)(gCellUI + ((b >> 5) << 2)) >> (b & 31)) & 1) ||
            ((*(unsigned*)(gCellUI + 4) >> 6) & 1) ||
            ((*(unsigned*)(gCellUI + 0xc) >> 8) & 1)) {
            dx += gBasis_15a7c34; dy += gBasis_15a7c38; dz += gBasis_15a7c3c;
            *(int*)(gCellUI + 0xc4) = 0;
            *(char*)(*(char**)(gCellGame + 0x5190) + 0xe0) = 1;
        }
    }
    {
        if (((*(unsigned*)(gCellUI + 8) >> 0x13) & 1) ||
            ((*(unsigned*)(gCellUI + 4) >> 8) & 1) ||
            ((*(unsigned*)(gCellUI + 0xc) >> 2) & 1)) {
            dx -= gBasis_15a7c34; dy -= gBasis_15a7c38; dz -= gBasis_15a7c3c;
            *(int*)(gCellUI + 0xc4) = 0;
            *(char*)(*(char**)(gCellGame + 0x5190) + 0xe0) = 1;
        }
    }
    {
        unsigned b = FUN_00e84470() ? 0x51 : 0x41;
        if (((*(unsigned*)(gCellUI + ((b >> 5) << 2)) >> (b & 31)) & 1) ||
            ((*(unsigned*)(gCellUI + 4) >> 5) & 1) ||
            ((*(unsigned*)(gCellUI + 0xc) >> 4) & 1)) {
            dx -= gBasis_15a7c28; dy -= gBasis_15a7c2c; dz -= gBasis_15a7c30;
            *(int*)(gCellUI + 0xc4) = 0;
            *(char*)(*(char**)(gCellGame + 0x5190) + 0xe0) = 1;
        }
    }
    {
        if (((*(unsigned*)(gCellUI + 8) >> 4) & 1) ||
            ((*(unsigned*)(gCellUI + 4) >> 7) & 1) ||
            ((*(unsigned*)(gCellUI + 0xc) >> 6) & 1)) {
            dx += gBasis_15a7c28; dy += gBasis_15a7c2c; dz += gBasis_15a7c30;
            *(int*)(gCellUI + 0xc4) = 0;
            *(char*)(*(char**)(gCellGame + 0x5190) + 0xe0) = 1;
        }
    }

    float len2 = dz * dz + dy * dy + dx * dx;
    if (gK_14851ec < len2) {
        float inv = 1.0f / (float)(double)sqrt((double)(len2 + gK_13ec4b8));
        float dir[3];
        dir[0] = dx * inv; dir[1] = dy * inv; dir[2] = dz * inv;
        char scratch[0x18];
        float* q = (float*)FUN_00e5b0a0(scratch, gCellUI + 0xcc, dir, &param);
        *(float*)(gCellUI + 0xcc) = q[0];
        *(float*)(gCellUI + 0xd0) = q[1];
        *(float*)(gCellUI + 0xd4) = q[2];
        float f0 = *(float*)(gCellUI + 0xcc);
        float f1 = *(float*)(gCellUI + 0xd0);
        float f2 = *(float*)(gCellUI + 0xd4);
        *(float*)(p + 8)    = *(float*)(p + 0x4c) + f0 * gK_13eecd8;
        *(float*)(p + 0xc)  = *(float*)(p + 0x50) + f1 * gK_13eecd8;
        *(float*)(p + 0x10) = *(float*)(p + 0x54) + f2 * gK_13eecd8;
        *(char*)(p + 4) = 0;
        *(char*)(gCellUI + 0xc8) = 1;
        return;
    }
    if (*(char*)(gCellUI + 0xc8) == 1) {
        *(char*)(gCellUI + 0xc8) = 0;
        *(char*)(p + 4) = 1;
        *(float*)(gCellUI + 0xcc) = gFwd_16b3c28;
        *(float*)(gCellUI + 0xd0) = gFwd_16b3c2c;
        *(float*)(gCellUI + 0xd4) = gFwd_16b3c30;
    }
}

// ---------------------------------------------------------------- 0x00e5b6b0
// SP::sUpdateZoomButtons(float): read the +/- buttons' pressed state and tail-call the zoom
// helper with a whole number of 1/1000 zoom steps.
// @ 0x00e5b6b0
void SP_sUpdateZoomButtons(float dt)
{
    cUIWindow* w = (cUIWindow*)((cSPUILayout*)*(char**)(gCellUI + 0x90))->FindWindowByID(0x5cab570, 1);
    cUIWindow* btn = w ? w->SubWindow(0x8ed27e7a) : 0;
    char flag1 = btn->State();

    float f = 0.0f;
    if (flag1 & 2) f = gK_1485720;

    cUIWindow* w2 = (cUIWindow*)((cSPUILayout*)*(char**)(gCellUI + 0x90))->FindWindowByID(0x5cab571, 1);
    cUIWindow* btn2 = w2 ? w2->SubWindow(0x8ed27e7a) : 0;
    char flag2 = btn2->State();

    if (flag2 & 2) f = f - gK_1485720;

    float v = f * dt * gK_13ec5b4;
    int n = (int)v;
    if ((float)n < v) n = n + 1;
    FUN_00e51060(n);
}

// ---------------------------------------------------------------- 0x00e5b790
// Follow the avatar cell along the camera ground plane: if the level gate allows, cast the
// camera forward ray onto the up-plane through the avatar and place the cell, then build its
// facing quaternion.
// @ 0x00e5b790
void FUN_00e5b790(float param)
{
    if (*(int*)(gCellGame + 0x5158) != 0) return;
    char* p = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
    if (p == 0) return;

    FUN_00e5b2e0(param);

    char tmp[0x18];
    FUN_00743b50(tmp);
    int lvl = *(int*)((char*)LayerCatalog_ApplyA(tmp) + 0xd4);
    FUN_00e82130(tmp);

    if (lvl >= 0) {
        if (lvl <= 1) {
            if (FUN_00e50730() != 0) goto LAB;
            if (*(char*)(gCellUI + 0x24) != 0) goto LAB;
        } else {
            if (lvl != 2) goto LAB;
            if (FUN_00e50730() != 0) goto LAB;
        }
        if (*(char*)(gCellUI + 0x26) == 0) return;
    }
LAB:
    {
        cViewer* cam = SP_App()->GetViewer();
        float V[3], U[3];
        cam->GetCameraRay(V, U);

        float k = U[1] * gUp_15a7c44 + U[2] * gUp_15a7c48 + U[0] * gUp_15a7c40;
        float t = -((V[1] * gUp_15a7c44 + V[2] * gUp_15a7c48 + V[0] * gUp_15a7c40)
                    - (gFwd_16b3c2c * gUp_15a7c44 + gFwd_16b3c30 * gUp_15a7c48
                       + gUp_15a7c40 * gFwd_16b3c28)) / k;
        if (k != 0.0f && 0.0f <= t) {
            *(char*)(p + 4) = 0;
            *(float*)(p + 8)    = V[0] + U[0] * t;
            *(float*)(p + 0xc)  = V[1] + U[1] * t;
            *(float*)(p + 0x10) = V[2] + U[2] * t;
            *(char*)(*(char**)(gCellGame + 0x5190) + 0xe0) = 1;

            float facing[3];
            facing[0] = -(*(float*)(p + 8) - *(float*)(p + 0x4c));
            facing[1] = -(*(float*)(p + 0xc) - *(float*)(p + 0x50));
            facing[2] = -(*(float*)(p + 0x10) - *(float*)(p + 0x54));
            char scratch[0x18];
            float* q = (float*)QuaternionFromFacingAndUp(scratch, facing, &gUp_15a7c40);
            *(float*)(p + 0x14) = q[0];
            *(float*)(p + 0x18) = q[1];
            *(float*)(p + 0x1c) = q[2];
            *(float*)(p + 0x20) = q[3];
        }
    }
}

// ---------------------------------------------------------------- 0x00e5ba10
// Clamp a point (copy of src) into an axis-aligned box: box = (min0,min1,min2,max0,max1,max2).
// @ 0x00e5ba10
void FUN_00e5ba10(float* out, float* box, float* src)
{
    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    if (box[0] > out[0]) out[0] = box[0];
    else if (out[0] > box[3]) out[0] = box[3];
    if (box[1] > out[1]) out[1] = box[1];
    else if (out[1] > box[4]) out[1] = box[4];
    if (box[2] > out[2]) out[2] = box[2];
    else if (out[2] > box[5]) out[2] = box[5];
}

// ---------------------------------------------------------------- 0x00e5ba90
// Move point p1 toward p2 by (speed*dt); if the remaining distance is already smaller, snap to p2.
// @ 0x00e5ba90
void FUN_00e5ba90(float* p1, float* p2, float speed, float dt)
{
    if (gK_14851ec <= speed) {
        float d = speed * dt;
        float dx = p2[0] - p1[0];
        float dy = p2[1] - p1[1];
        float dz = p2[2] - p1[2];
        float sum = dx * dx + dz * dz + dy * dy;
        if (d * d > sum) {
            p1[0] = p2[0];
            p1[1] = p2[1];
            p1[2] = p2[2];
            return;
        }
        float inv = 1.0f / (float)(double)sqrt((double)(sum + gK_13ec4b8));
        p1[0] = p1[0] + (dx * inv) * d;
        p1[1] = p1[1] + (dy * inv) * d;
        p1[2] = p1[2] + (dz * inv) * d;
    }
}

// ---------------------------------------------------------------- 0x00e5bbc0
// Pull a point back onto the world extent ellipse: scale (p-centre) by half the extent and
// keep it if the result is not farther from the centre than p.
// @ 0x00e5bbc0
float FUN_00e5bbc0(float* p)
{
    float mx = (gExt_16b3c94 + gExt_16b3c88) * gK_1471064;
    float my = (gExt_16b3c98 + gExt_16b3c8c) * gK_1471064;
    float mz = (gExt_16b3c9c + gExt_16b3c90) * gK_1471064;

    float dx = p[0] - mx;
    float dy = p[1] - my;
    float dz = p[2] - mz;
    float sum = dx * dx + (dy * dy + dz * dz);
    float inv = 1.0f / (float)(double)sqrt((double)(sum + gK_13ec4b8));

    float nx = ((gExt_16b3c94 - gExt_16b3c88) * (dx * inv)) * gK_13ec434 + mx;
    float ny = ((gExt_16b3c98 - gExt_16b3c8c) * (dy * inv)) * gK_13ec434 + my;
    float rx = nx - mx;
    float ry = ny - my;
    float rd = (float)(double)sqrt((double)(rx * rx + (ry * ry + 0.0f)));
    if (rd <= (float)(double)sqrt((double)sum)) {
        p[0] = nx; p[1] = ny; p[2] = mz;
    }
    return rd;
}

// ---------------------------------------------------------------- 0x00e5bd30
// Refresh a placed-object record: snap its position onto the extent ellipse, bump the dirty
// counter, then rebuild its facing matrix from the extent centre and store it.
// @ 0x00e5bd30
void FUN_00e5bd30(unsigned short* s)
{
    float pos[3];
    pos[0] = *(float*)((char*)s + 4);
    pos[1] = *(float*)((char*)s + 8);
    pos[2] = *(float*)((char*)s + 0xc);
    FUN_00e5bbc0(pos);
    s[0] = (unsigned short)(s[0] | 4);
    s[1] = (unsigned short)(s[1] + 1);
    *(float*)((char*)s + 4)  = pos[0];
    *(float*)((char*)s + 8)  = pos[1];
    *(float*)((char*)s + 0xc) = pos[2];

    float dx = (gExt_16b3c94 + gExt_16b3c88) * gK_1471064 - pos[0];
    float dy = (gExt_16b3c98 + gExt_16b3c8c) * gK_1471064 - pos[1];
    float dz = (gExt_16b3c9c + gExt_16b3c90) * gK_1471064 - pos[2];
    float inv = 1.0f / (float)(double)sqrt((double)((dx * dx + (dy * dy + dz * dz)) + gK_13ec4b8));

    float facing[3];
    facing[0] = -(dx * inv);
    facing[1] = -(dy * inv);
    facing[2] = -(dz * inv);
    char scratch[0x24];
    void* m = Matrix3FromFacingAndUp(scratch, facing, &gUp_15a7c40);
    memcpy((char*)s + 0x14, m, 36);
    s[0] = (unsigned short)(s[0] | 2);
    s[1] = (unsigned short)(s[1] + 1);
}

// ---------------------------------------------------------------- 0x00e5be80
// Camera follow distance: lerp between a near and a far distance based on the gap between the
// avatar and the tracked cell, then return the larger of that and a second lerp.
// @ 0x00e5be80
float FUN_00e5be80(void)
{
    char* a = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x51b0));
    char* b = (char*)((cObjectPool*)(gCellGame + 0x1c))->GetSafe(*(int*)(gCellGame + 0x411c));
    if (a == 0 || b == 0) return 0.0f;

    float dx = *(float*)(a + 0x4c) - *(float*)(b + 0x4c);
    float dy = *(float*)(a + 0x50) - *(float*)(b + 0x50);
    float dz = *(float*)(a + 0x54) - *(float*)(b + 0x54);
    float dist = (float)(double)sqrt((double)(dy * dy + (dz * dz + dx * dx)));

    float r1, r2;
    if (dist <= gK_1483f64) {
        r1 = FUN_00e513d0(1.0f, gK_1483f64, dist, 1.0f, gD_1485544);
    } else {
        r1 = FUN_00e513d0(gK_1483f64, gD_13ebc5c, dist, gD_1485544, gD_1488874);
    }
    r2 = FUN_00e513d0(gD_1486110, 0.0f, *(float*)(gCellGame + 0x51b8), 1.0f, 0.0f);
    return (r1 > r2) ? r1 : r2;
}

// ---------------------------------------------------------------- 0x00e5bfa0
// Level-tier 0..1 progress: piecewise normalise `level` across 200-step bands.
// @ 0x00e5bfa0
float FUN_00e5bfa0(void)
{
    int lvl = *(int*)(*(char**)(gCellGame + 0x5190) + 0x1c);
    if (lvl < 200)  return FUN_01041cd0(0.0f, gLvl_1477fbc, (float)lvl) * gK_13ec480;
    if (lvl < 400)  return (FUN_01041cd0(gLvl_1477fbc, gLvl_13f0e84, (float)lvl) + gK_1485720) * gK_13ec480;
    if (lvl < 600)  return FUN_01041cd0(gLvl_13f0e84, gLvl_13fdcf8, (float)lvl) * gK_13ec480 + gK_13ec434;
    if (lvl < 800)  return FUN_01041cd0(gLvl_13fdcf8, gLvl_13fdcf4, (float)lvl) * gK_13ec480 + gK_13ec4b0;
    if (lvl < 1000) return FUN_01041cd0(gLvl_13fdcf4, gK_13ec5b4, (float)lvl) * gK_13ec480 + gK_1486374;
    return gK_1485720;
}

// ---------------------------------------------------------------- 0x00e5c0f0
// SP::cCellMode::OnMouseUp: forward to the local input state, then pick the cell under the
// cursor and store its handle plus a zeroed timeout.
// @ 0x00e5c0f0
bool SP::cCellMode::OnMouseUp(int p1, float p2, float p3, int p4)
{
    ((cLocalInputState*)gCellUI)->OnMouseUp(p1, p2, p3, p4);
    cViewer* cam = SP_App()->GetViewer();
    float V[3], U[3];
    cam->GetCameraRay(V, U);
    unsigned h = FUN_00e87200(*(int*)(gCellGame + 0x40fc), V, U, (void*)(gCellUI + 0x100), 0x200, gK_14851e8);
    *(int*)(gCellUI + 0x900) = (int)h;
    *(float*)(gCellUI + 0x904) = 0.0f;
    return true;
}

// ---------------------------------------------------------------- 0x00e5c1a0
// Enable/disable the zoom +/- buttons by comparing the current zoom with two queried values.
// @ 0x00e5c1a0
void FUN_00e5c1a0(void)
{
    float q[2];
    FUN_00e836f0(0x71cb8a60, &q[0], &q[1]);

    int d1 = (*(float*)(gCellUI + 0xf8) != q[0]);
    cUIWindow* w1 = (cUIWindow*)((cSPUILayout*)*(char**)(gCellUI + 0x90))->FindWindowByID(0x5cab571, 1);
    w1->SetButton(2, d1);

    int d2 = (*(float*)(gCellUI + 0xf8) != q[1]);
    cUIWindow* w2 = (cUIWindow*)((cSPUILayout*)*(char**)(gCellUI + 0x90))->FindWindowByID(0x5cab570, 1);
    w2->SetButton(2, d2);
}
