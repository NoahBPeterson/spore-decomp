// Slice s00b159e0 (batch bfs1) — 8 functions.
// Module "Spore"; SP::cTerrainCameraController input/scroll handlers + helpers.
// Each block starts with its original address.

#include "s00b159e0.h"
#include <math.h>

extern "C" void* GonzagoModelWorld_00b3d520();
extern "C" float FUN_00b0f880(void*);
extern "C" void FUN_00b14370(void*, unsigned, void*);
extern "C" void* eastl_copy_runinfo(void*, void*, void*);
extern "C" void* DebugDrawGrid_00f48aa0(void*);

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }
template<class R, class A1> static inline R vcall1(void* p, int off, A1 a1)
{ return ((R(__thiscall*)(void*, A1))g_vfn(p, off))(p, a1); }

// @ 0x00b159e0
void cTerrainCameraController::FUN_00b159e0(int n)
{
    FUN_00b148c0(0.0f, 0.0f, (float)n * m2a0, 0.0f);
    m13 = true;
    m294 = m114;
}

// @ 0x00b15a20
// Resizes a vector<RunInfo> (stride 0x10) at this+0: grow via reserve helper, or
// shift the tail down with eastl::copy and shrink the end.
void cTerrainCameraController::FUN_00b15a20(unsigned n)
{
    char* v = (char*)this;
    unsigned cur = (unsigned)((*(char**)(v + 4) - *(char**)v) >> 4);
    if (cur < n)
    {
        char tmp[16];
        FUN_00b14370(*(void**)(v + 4), n - cur, tmp);
        return;
    }
    char* dst = *(char**)v + n * 16;
    char* e = *(char**)(v + 4);
    eastl_copy_runinfo(e, e, dst);
    *(char**)(v + 4) = e + ((e - dst) >> 4) * -16;
}

// @ 0x00b15a80
bool cTerrainCameraController::FUN_00b15a80(int delta, float x, float y, int flag)
{
    mInput.OnMouseWheel(delta, x, y, flag);
    if (flag == 0)
    {
        FUN_00b148c0(0.0f, 0.0f, (float)delta * m2a0, 0.0f);
        m294 = m114;
        m13 = true;
    }
    return false;
}

// @ 0x00b15b00
// Recomputes the camera transform for the current frame (height, spline targets,
// near/far planes).  Large /Od-ish routine; only the opening stages reproduced.
void cTerrainCameraController::FUN_00b15b00()
{
    char* self = (char*)this;
    if (!DebugDrawGrid_00f48aa0(self)) return;
    *(float*)(self + 0x18) = (*(float*)(self + 0xc) + *(float*)(self + 0x14)) * 2.0f;
    *(float*)(self + 0x1c) = (*(float*)(self + 0x30) + *(float*)(self + 0x38)) * 2.0f;
    // ... full spline / transform evaluation omitted (incomplete).
}

// @ 0x00b16270
void cTerrainCameraController::FUN_00b16270()
{
    char* self = (char*)this;
    if (*(char*)(self + 0x390) != 0) return;
    if (*(char*)(self + 0x3c) == 0) return;
    float t = FUN_00b0f880(self);
    *(char*)(self + 0x168) = 1;
    *(float*)(self + 0x44) = t;
    *(float*)(self + 0x84) = *(float*)(self + 0x84) * 0.0f;
    *(float*)(self + 0x88) = *(float*)(self + 0x88) * 0.0f;
    *(float*)(self + 0x8c) = *(float*)(self + 0x8c) * 0.0f;
    *(int*)(self + 0x60) = *(int*)(self + 0x6c);
    *(int*)(self + 0x64) = *(int*)(self + 0x70);
    *(int*)(self + 0x68) = *(int*)(self + 0x74);
    *(float*)(self + 0x40) = 0.0f;
    *(char*)(self + 0x3c) = 0;
    *(float*)(self + 0x104) = t;
    *(int*)(self + 0x110) = *(int*)(self + 0x114);
    *(float*)(self + 0x100) = 0.0f;
    *(char*)(self + 0xfc) = 0;
    *(float*)(self + 0x11c) = *(float*)(self + 0x11c) * 0.0f;
    *(int*)(self + 0x134) = *(int*)(self + 0x138);
    *(float*)(self + 0x128) = t;
    *(float*)(self + 0x124) = 0.0f;
    *(char*)(self + 0x120) = 0;
    *(float*)(self + 0x140) = *(float*)(self + 0x140) * 0.0f;
    *(float*)(self + 0x98) = t;
    *(float*)(self + 0xec) = *(float*)(self + 0xec) * 0.0f;
    *(float*)(self + 0xf0) = *(float*)(self + 0xf0) * 0.0f;
    *(float*)(self + 0xf4) = *(float*)(self + 0xf4) * 0.0f;
    *(float*)(self + 0xf8) = *(float*)(self + 0xf8) * 0.0f;
    *(int*)(self + 0xbc) = *(int*)(self + 0xcc);
    *(int*)(self + 0xc0) = *(int*)(self + 0xd0);
    *(int*)(self + 0xc4) = *(int*)(self + 0xd4);
    *(int*)(self + 0xc8) = *(int*)(self + 0xd8);
    *(float*)(self + 0x94) = 0.0f;
    *(char*)(self + 0x90) = 0;
    FUN_00b15b00();
    if (*(char*)(self + 0x18) != 0)
    {
        *(int*)(self + 0x2c) = *(int*)(self + 0x30);
        *(float*)(self + 0x20) = t;
        *(float*)(self + 0x38) = *(float*)(self + 0x38) * 0.0f;
        *(float*)(self + 0x1c) = 0.0f;
        *(char*)(self + 0x18) = 0;
    }
    *(char*)(self + 0x3d) = 0;
    *(char*)(self + 0x19) = 0;
    *(char*)(self + 0x91) = 0;
}

// @ 0x00b16450
void FUN_00b16450(float* v, int* list)
{
    if (list[0] != list[1])
    {
        float x = *(float*)((char*)list + 0x38);
        float y = *(float*)((char*)list + 0x3c);
        float z = *(float*)((char*)list + 0x40);
        v[0] += x;
        v[1] += y;
        v[2] += z;
    }
}

// @ 0x00b16490
void FUN_00b16490(float* v, float add)
{
    float x = v[0], y = v[1], z = v[2];
    float len = sqrtf(z * z + (y * y + x * x));
    float inv = 1.0f / len;
    float s = len + add;
    v[0] = x * inv * s;
    v[1] = y * inv * s;
    v[2] = z * inv * s;
}

// @ 0x00b16520
bool FUN_00b16520(int* world, float* a, float* b, bool flag, float* out)
{
    void* gw = GonzagoModelWorld_00b3d520();
    if (gw) vcall1<void, int>(gw, 0x0, 0);
    int h = vcall1<int, int>(world, 0xac, 0);
    if (!gw) return false;
    if (h)
    {
        char ok = vcall1<char, int>(gw, 0x44, 0);
        if (ok)
        {
            out[0] = a[0] + (b[0] - a[0]) * (float)h;
            out[1] = a[1] + (b[1] - a[1]) * (float)h;
            out[2] = a[2] + (b[2] - a[2]) * (float)h;
            vcall1<void, int>(gw, 0x4, 0);
            return true;
        }
    }
    vcall1<void, int>(gw, 0x4, 0);
    return false;
}