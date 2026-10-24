// Slice s005a2600 -- SP::cTerrainUI input/command helpers + EA::Swarm::cTransform::PreRotateX.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>
#include <intrin.h>

typedef unsigned int size_t;

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

struct cLocalInputState {
    char pad[0x40];
    bool OnKeyDown(int key, int x);
    bool OnKeyUp(int key, int x);
    bool OnMouseUp(int a, float x, float y, int b);
    bool OnMouseDown(int a, float x, float y, int b);
    unsigned int OnMouseWheel(int a, int b, float x, float y);
    unsigned int OnMouseWheel2(float x, float y, int delta);
    void Init();   // 0x00697960
};

extern void* sAppProperties;   // 0x015fd918
extern float g_0150f2c8;       // 0x0150f2c8  0.1f  (pan/zoom step scale)
extern float g_014853e0;       // 0x014853e0  4.0f
extern float g_01485720;       // 0x01485720  1.0f  (_HK_REAL_ONE)
extern float g_013f6a28;       // 0x013f6a28  -4.0f
extern float g_015e6a6c[];     // 0x015e6a6c  fixed reference point handed to the viewer transform
void __fastcall FUN_007c4180(void* viewer, int dummy, void* out, void* src);  // 0x007c4180 thiscall, ret 8
void __fastcall FUN_007c4010(void* viewer, int dummy, unsigned* out);         // 0x007c4010 thiscall, ret 4
struct cTerrainUI {
    char pad[0xe8 + 4];
    __declspec(noinline) void FUN_005a2b30(char flag);       // 0x005a2b30
    void ZoomBy(float factor);                              // 0x005a2200
    bool OnMouseDown(int a, float x, float y, int b);       // 0x005a2f20
    bool OnMouseWheel(float x, float y, int delta);         // 0x005a2f80
    void Command(int cmd, float x, float y);                // 0x005a2c00
};

// ===========================================================================
// @ 0x005a2f20
bool cTerrainUI::OnMouseDown(int a, float x, float y, int b)
{
    ((cLocalInputState*)((char*)this + 0xa0))->OnMouseDown(a, x, y, b);
    if (*(char*)((char*)this + 0x90))
        FUN_005a2b30(1);
    *(float*)((char*)this + 0x20) = x;
    *(char*)((char*)this + 0x2c) = 1;
    *(float*)((char*)this + 0x24) = y;
    return true;
}

// ===========================================================================
// @ 0x005a2f80
bool cTerrainUI::OnMouseWheel(float x, float y, int delta)
{
    ((cLocalInputState*)((char*)this + 0xa0))->OnMouseWheel2(x, y, delta);
    if (delta == 0 || *(char*)((char*)this + 0x2c) == 0)
        return false;
    float speed;
    int cmd;
    if (*(int*)(*(int*)((char*)sAppProperties + 0x3c) + 0x114) == 0 ||
        !(delta == 0x11 || delta == 0x12 || delta == 9 || delta == 10 ||
          delta == 0x21 || delta == 0x22)) {
        if (delta == 0x21 || delta == 0x11) {
            speed = *(float*)((char*)this + 0x14);
            cmd = 3;
        } else {
            speed = *(float*)((char*)this + 0x1c);
            cmd = 0;
        }
    } else {
        speed = *(float*)((char*)this + 0x18);
        cmd = 1;
    }
    Command(cmd, ((x - *(float*)((char*)this + 0x20)) * speed) * 0.0025f,
            ((y - *(float*)((char*)this + 0x24)) * speed) * 0.0025f);
    *(float*)((char*)this + 0x20) = x;
    *(float*)((char*)this + 0x24) = y;
    return true;
}

// ===========================================================================
// @ 0x005a2c00
void cTerrainUI::Command(int cmd, float x, float y)
{
    switch (cmd) {
    case 0:
        if (*(char*)((char*)this + 0x90)) {
            FUN_005a2b30(0);
            return;
        }
        *(float*)((char*)this + 0x30) = x * g_0150f2c8 + *(float*)((char*)this + 0x30);
        {
            float v = *(float*)((char*)this + 0x34) - y * g_0150f2c8;
            *(float*)((char*)this + 0x34) = v;
            if (v < *(float*)((char*)this + 0x60))
                *(float*)((char*)this + 0x34) = *(float*)((char*)this + 0x60);
            if (*(float*)((char*)this + 0x64) < *(float*)((char*)this + 0x34))
                *(float*)((char*)this + 0x34) = *(float*)((char*)this + 0x64);
        }
        break;
    case 1:
        *(float*)((char*)this + 0x3c) = x * g_014853e0 + *(float*)((char*)this + 0x3c);
        *(float*)((char*)this + 0x40) = y * g_014853e0 + *(float*)((char*)this + 0x40);
        break;
    case 2: {
        float f = (x * g_014853e0 + g_01485720) * *(float*)((char*)this + 0x38);
        float t = *(float*)((char*)this + 0x5c);
        *(float*)((char*)this + 0x38) = f;
        if (t < f || (t = *(float*)((char*)this + 0x58), f < t))
            *(float*)((char*)this + 0x38) = t;
        *(char*)((char*)this + 0x9c) = 1;
        break;
    }
    case 3: {
        float f = (g_01485720 - y * g_014853e0) * *(float*)((char*)this + 0x38);
        float t = *(float*)((char*)this + 0x5c);
        *(float*)((char*)this + 0x38) = f;
        if (t < f || (t = *(float*)((char*)this + 0x58), f < t))
            *(float*)((char*)this + 0x38) = t;
        *(char*)((char*)this + 0x9c) = 1;
        break;
    }
    case 4:
        if (Abs(x) < Abs(y))
            x = y;
        ZoomBy(x * g_013f6a28);
        break;
    default:
        break;
    }
}

// ===========================================================================
// EA::Swarm::cTransform
namespace EA { namespace Swarm {

struct cTransform {
    uint16_t mFlags;             // +0x0
    uint16_t mModificationCount; // +0x2
    char pad4[0x20 - 0x4];
    float yAxis[3];              // +0x20 (x, y, padding)
    float zAxis[3];              // +0x2c (x, y, padding)
    void PreRotateX(float angle);   // 0x005a2d90
};

// @ 0x005a2d90
void cTransform::PreRotateX(float angle)
{
    float f1 = zAxis[1];
    float f2 = zAxis[2];
    float f3 = yAxis[0];
    float f4 = zAxis[0];
    float f5 = yAxis[1];
    float f6 = yAxis[2];
    float s = (float)sinf(angle);
    float c = (float)cosf(angle);
    yAxis[0] = f3 * c + f4 * s;
    yAxis[1] = f5 * c + f1 * s;
    yAxis[2] = f6 * c + f2 * s;
    s = -s;
    mFlags |= 2;
    mModificationCount++;
    zAxis[0] = f3 * s + f4 * c;
    {
        // The original stages the last two stores through integer registers (it ends with
        // zAxis[1]'s bits in eax and zAxis[2]'s in edx, which its LTCG callers observe).
        union FI { float f; int i; } u1, u2;
        u1.f = f5 * s + f1 * c;
        u2.f = f6 * s + f2 * c;
        *(int*)((char*)this + 0x30) = u1.i;
        *(int*)((char*)this + 0x34) = u2.i;
    }
}

}}  // namespace EA::Swarm

// ===========================================================================
// @ 0x005a2600
void FUN_005a2600(void* self)
{
    (void)self;
}

// @ 0x005a2b30
void cTerrainUI::FUN_005a2b30(char flag)
{
    void* viewer = *(void**)((char*)this + 0xe8);
    if (!viewer)
        return;
    float pt[4];
    unsigned v[4];
    FUN_007c4180(viewer, 0, pt, g_015e6a6c);
    FUN_007c4010(viewer, 0, v);
    int da = (int)v[2] - (int)v[0];
    int db = (int)v[3] - (int)v[1];
    // The original evaluates both atan2 operands in x87 extended precision and rounds once,
    // when the float result is stored; use doubles (x87 under /arch:SSE) to match that rounding.
    double ax = ((double)pt[0] + 1.0) * (double)da * 0.5 - (double)*(float*)((char*)this + 0xcc);
    double ay = (1.0 - (double)pt[1]) * (double)db * 0.5 - (double)*(float*)((char*)this + 0xd0);
    float r = (float)atan2(ax, ay);
    if (flag != 0) {
        *(float*)((char*)this + 0x94) = r;
        *(float*)((char*)this + 0x98) = *(float*)((char*)this + 0x44);
    } else {
        *(float*)((char*)this + 0x30) = (r - *(float*)((char*)this + 0x94)) + *(float*)((char*)this + 0x98);
    }
}

// @ 0x005a2ed0
void* ScalarDeletingDtor_5a2ed0(void* p, unsigned char flags)
{
    (void)flags;
    return p;
}

// @ 0x005a3080 / @ 0x005a3220
void FUN_005a3080(void* self, void* t) { (void)self; (void)t; }
void* FUN_005a3220(void* self, void* arg) { (void)arg; return self; }
