// Slice s00b10200 (batch bfs1) — 13 functions.
// Module "Spore"; class SP::cTerrainCameraController.  Each block starts with its
// original address.  Field offsets are retail (from the disassembly).

#include "s00b10200.h"
#include <math.h>

// ---- globals referenced by the original --------------------------------
// lazy-init output vectors
extern unsigned int g_167bd6c;   // +0x167bd6c lazy flag
extern float g_167bd60, g_167bd64, g_167bd68;
extern unsigned int g_167bd7c;   // +0x167bd7c lazy flag
extern float g_167bd70, g_167bd74, g_167bd78;
// float constants kept as globals in the original
extern float g_kMinInterpTime;   // +0x1488874 = 0.1
extern float g_zero;             // +0x1485378 = 0.0
// external functions / interfaces
extern "C" void* DebugDrawGrid_00f48aa0(void*);          // SP::cDistGrid::DebugDrawGrid
extern "C" float FUN_00f987f0(void*);
extern "C" float GetHeightAt_00f927c0(void*, void*);
extern "C" void* GameInputManager_00b3d250();
extern "C" void* g_167bc78;
extern "C" float FUN_007f2590(const char*);
extern "C" void FUN_007f25c0(const char*, float);
extern "C" void FUN_00b0f270(void*, int, int, int, int, int, int);
extern "C" void FUN_0067cab0(int);
extern "C" void CanvasVisibilitySetter(int);
extern "C" void CursorAttachmentLayout_IsSomething(int);
extern "C" void CursorAttachmentLayout_SetEnabled(int);

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }
template<class R> static inline R vcall0(void* p, int off)
{ return ((R(__thiscall*)(void*))g_vfn(p, off))(p); }
template<class R, class A1> static inline R vcall1(void* p, int off, A1 a1)
{ return ((R(__thiscall*)(void*, A1))g_vfn(p, off))(p, a1); }
template<class R, class A1, class A2> static inline R vcall2(void* p, int off, A1 a1, A2 a2)
{ return ((R(__thiscall*)(void*, A1, A2))g_vfn(p, off))(p, a1, a2); }

// ===========================================================================

// @ 0x00b10200
float* cTerrainCameraController::FUN_00b10200()
{
    if ((g_167bd6c & 1) == 0)
        g_167bd6c |= 1;
    float s = m28;
    float x = m54, y = m58, z = m5c;
    g_167bd60 = x * s;
    g_167bd64 = y * s;
    g_167bd68 = z * s;
    return &g_167bd60;
}

// @ 0x00b10260
float* cTerrainCameraController::FUN_00b10260()
{
    if ((g_167bd7c & 1) == 0)
        g_167bd7c |= 1;
    float s = m30;
    g_167bd70 = m6c * s;
    g_167bd74 = m70 * s;
    g_167bd78 = m74 * s;
    return &g_167bd70;
}

// @ 0x00b102c0
void cTerrainCameraController::FUN_00b102c0()
{
    void* grid = DebugDrawGrid_00f48aa0(this);
    if (!grid) return;
    float a = FUN_00f987f0(grid);
    void* set = vcall0<void*>(grid, 0xc);
    float b = GetHeightAt_00f927c0(set, &m6c);
    float v = a;
    if (!(a <= b)) v = b;
    float h = m2b4 + v;
    if (h != m30)
    {
        m30 = h;
        m24 = m28;
        m18 = true;
    }
}

// @ 0x00b10340
void cTerrainCameraController::FUN_00b10340(float a, float b, float c)
{
    if (fabsf(m15c - a) > 0.0f && a != m15c)
    {
        m15c = a;
        m150 = m154;
        m144 = true;
    }
    if (fabsf(m138 - b) > 0.0f)
    {
        float v = b;
        if (v <= m2ac) v = m2ac;
        if (v >= m2b0) v = m2b0;
        if (v != m138)
        {
            m138 = v;
            m12c = m130;
            m120 = true;
        }
    }
    float x = c > g_kMinInterpTime ? c : g_kMinInterpTime;
    if (fabsf(x - m114) > 0.0f && x != m114)
    {
        m114 = x;
        m108 = m10c;
        mfc = true;
    }
}

// @ 0x00b10470
void cTerrainCameraController::FUN_00b10470(float v)
{
    if (fabsf(m15c - v) > 0.0f && v != m15c)
    {
        m15c = v;
        m150 = m154;
        m144 = true;
    }
}

// @ 0x00b104c0
void cTerrainCameraController::FUN_00b104c0(float v)
{
    float x = v > g_kMinInterpTime ? v : g_kMinInterpTime;
    m114 = x;
    m110 = x;
    m10c = x;
    m108 = x;
    m118 = x * g_zero;
    m11c = x * g_zero;
    mfc = false;
    mfd = false;
    m304 = true;
}

// @ 0x00b10540
// Sets distance/pitch/yaw, preserving the old value as the interpolation start
// if the new one is effectively different.
void cTerrainCameraController::FUN_00b10540(float d, float p, float y)
{
    if (fabsf(m154 - d) > g_kMinInterpTime * 1.52587890625e-05f)
    {
        float old = m15c;
        m15c = d; m158 = d; m154 = d; m150 = d;
        m160 = d * 0.0f;
        m164 = d * 0.0f;
        m144 = m145 = false;
        if (old != m15c) { m15c = old; m150 = m154; m144 = true; }
    }
    if (fabsf(m130 - p) > g_kMinInterpTime * 1.52587890625e-05f)
    {
        float old = m138;
        float v = p;
        if (v <= m2ac) v = m2ac;
        if (v >= m2b0) v = m2b0;
        m138 = v; m134 = v; m130 = v; m12c = v;
        m13c = v * 0.0f;
        m140 = v * 0.0f;
        m120 = m121 = false;
        if (old != m138) { m138 = old; m12c = m130; m120 = true; }
    }
    if (fabsf(m10c - y) > 0.0f)
    {
        float old = m114;
        float v = y > g_kMinInterpTime ? y : g_kMinInterpTime;
        m114 = v; m110 = v; m10c = v; m108 = v;
        m118 = v * 0.0f;
        m11c = v * 0.0f;
        mfc = mfd = false;
        if (old != m114) { m114 = old; m108 = m10c; mfc = true; }
    }
    m304 = true;
}

// @ 0x00b10760
// Hard-reset of all three interpolation blocks.
void cTerrainCameraController::FUN_00b10760(float d, float p, float y)
{
    m15c = d; m158 = d; m154 = d; m150 = d;
    m160 = d * 0.0f;
    m164 = d * 0.0f;
    m144 = m145 = false;

    float v = p;
    if (v <= m2ac) v = m2ac;
    if (v >= m2b0) v = m2b0;
    m138 = v; m134 = v; m130 = v; m12c = v;
    m13c = v * 0.0f;
    m140 = v * 0.0f;
    m120 = m121 = false;

    float x = y > g_kMinInterpTime ? y : g_kMinInterpTime;
    m114 = x; m110 = x; m10c = x; m108 = x;
    m118 = x * 0.0f;
    m11c = x * 0.0f;
    mfc = mfd = false;
    m304 = true;
}

// @ 0x00b108b0
void cTerrainCameraController::ReloadZoomProgram()
{
    // Reloads the zoom program from the config VarMap: distance / pitch and the
    // three mouse sensitivities, then sets up the interpolation targets.
    if (!*(int*)((char*)this + 0x314)) return;
    FUN_00b0f270(this, 0, 0, 0, 0, 0, 0);
    float dist = FUN_007f2590("default_distance");
    float dd = dist > g_kMinInterpTime ? dist : g_kMinInterpTime;
    m29c = dd;
    FUN_007f25c0("distance", m29c);
    FUN_007f25c0("height_above_water", m2a4);
    FUN_00b0f270(this, 0, 0, 0, 0, 0, 0);
    float pitch = FUN_007f2590("pitch") * 0.017453292f;
    m294 = pitch;
    m298 = FUN_007f2590("mouse_rotate_sensitivity_x") * 0.017453292f;
    m2a0 = FUN_007f2590("mouse_rotate_sensitivity_y") * 0.17453292f;
    m2a4 = FUN_007f2590("mouse_scroll_sensitivity");
}

// @ 0x00b10a90
void cTerrainCameraController::FUN_00b10a90(float dt)
{
    if (*(char*)((char*)this + 0x390)) return;
    void* input = GameInputManager_00b3d250();
    if (input)
    {
        if (vcall1<char, int>(input, 0x18, 7))
        {
            float v = m138 - (m29c * dt) * 5.0f;
            if (v <= m2ac) v = m2ac;
            if (v >= m2b0) v = m2b0;
            m290 = v;
            if (v != m138) { m12c = m130; m120 = true; m138 = m290; }
        }
        if (vcall1<char, int>(input, 0x18, 8))
        {
            float v = (m29c * dt) * 5.0f + m138;
            if (v <= m2ac) v = m2ac;
            if (v >= m2b0) v = m2b0;
            m290 = v;
            if (v != m138) { m12c = m130; m120 = true; m138 = m290; }
        }
    }
    if (!*(char*)((char*)this + 0x318))
        vcall2<void, float, int>(this, 0x38, *(float*)((char*)this + 0x348),
                                 *(float*)((char*)this + 0x34c));
    *(char*)((char*)this + 0x318) = 0;
}

// @ 0x00b10c40
void cTerrainCameraController::FUN_00b10c40(bool enabled)
{
    *(bool*)((char*)this + 0x319) = !enabled;
    FUN_0067cab0(!enabled);
    CanvasVisibilitySetter(!enabled);
    if (enabled)
    {
        *(int*)((char*)this + 0x388) = *(int*)((char*)this + 0x348);
        *(int*)((char*)this + 0x38c) = *(int*)((char*)this + 0x34c);
        FUN_0067cab0(0x67f5c34);
        CursorAttachmentLayout_IsSomething(0x67f5c34);
        FUN_0067cab0(enabled);
        CursorAttachmentLayout_SetEnabled(enabled);
        return;
    }
    float dt = 0.1f;
    if (0.0f < m14c - m148)
    {
        float v = (m160 * dt) * 0.5f + m154;
        if (v != m15c) { m150 = m154; m15c = v; m144 = true; }
        m158 = m15c;
        m14c = dt;
        m164 = m164 * 0.0f;
        m148 = 0.0f;
        m144 = false;
    }
    if (0.0f < m128 - m124)
    {
        float v = (m13c * dt) * 0.5f + m130;
        if (v != m138) { m12c = m130; m138 = v; m120 = true; }
        m134 = m138;
        m128 = dt;
        m140 = m140 * 0.0f;
        m124 = 0.0f;
        m120 = false;
    }
    FUN_0067cab0(enabled);
    CursorAttachmentLayout_SetEnabled(enabled);
}

// @ 0x00b10de0
void HermiteFloatScratch::FUN_00b10de0(float v)
{
    m08 = v;
    m5c = m5c * 0.0f;
    m60 = m60 * 0.0f;
    m64 = m64 * 0.0f;
    m68 = m68 * 0.0f;
    m2c = m3c;
    m30 = m40;
    m34 = m44;
    m38 = m48;
    *(int*)((char*)this + 4) = 0;
    *(char*)this = 0;
}

// @ 0x00b10e50
// One Hermite/Catmull-Rom spline segment (free __cdecl).
void FUN_00b10e50(float* out, float* p2, float* p3, float* p4, float* p5, float t, float s)
{
    float p1x = p3[0], p1y = p3[1], p1z = p3[2];
    float p5y = p5[1], p5z = p5[2];
    float m1x = p2[0], m1y = p2[1], m1z = p2[2];
    float t2 = t * t;
    float inv = 1.0f / (t2 * t);
    float a = ((m1x * 2.0f - p4[0] * 2.0f) + (p5[0] + p1x) * t) * inv;
    float b = ((m1y * 2.0f - p4[1] * 2.0f) + (p5y + p1y) * t) * inv;
    float c = ((m1z * 2.0f - p4[2] * 2.0f) + (p5z + p1z) * t) * inv;
    float inv2 = 1.0f / (t * 2.0f);
    out[0] = m1x + (p1x + (a * s + (p5[0] + (-p1x - (a * 3.0f) * t2)) * inv2) * s) * s;
    out[1] = m1y + (p1y + (b * s + (p5y + (-p1y - (b * 3.0f) * t2)) * inv2) * s) * s;
    out[2] = m1z + (p1z + (c * s + (p5z + (-p1z - (c * 3.0f) * t2)) * inv2) * s) * s;
}