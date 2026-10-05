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
struct cTerrainUI {
    char pad[0xe8 + 4];
    __declspec(noinline) void FUN_005a2b30(int flag);       // 0x005a2b30
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
        *(float*)((char*)this + 0x30) = 0.1f * x + *(float*)((char*)this + 0x30);
        {
            float v = *(float*)((char*)this + 0x34) - 0.1f * y;
            *(float*)((char*)this + 0x34) = v;
            if (v < *(float*)((char*)this + 0x60))
                *(float*)((char*)this + 0x34) = *(float*)((char*)this + 0x60);
            if (*(float*)((char*)this + 0x64) < *(float*)((char*)this + 0x34))
                *(float*)((char*)this + 0x34) = *(float*)((char*)this + 0x64);
        }
        break;
    case 1:
        *(float*)((char*)this + 0x3c) = x * 4.0f + *(float*)((char*)this + 0x3c);
        *(float*)((char*)this + 0x40) = y * 4.0f + *(float*)((char*)this + 0x40);
        break;
    case 2: {
        float f = (x * 4.0f + 1.0f) * *(float*)((char*)this + 0x38);
        float t = *(float*)((char*)this + 0x5c);
        *(float*)((char*)this + 0x38) = f;
        if (t < f || (t = *(float*)((char*)this + 0x58), f < t))
            *(float*)((char*)this + 0x38) = t;
        *(char*)((char*)this + 0x9c) = 1;
        break;
    }
    case 3: {
        float f = (1.0f - y * 4.0f) * *(float*)((char*)this + 0x38);
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
        ZoomBy(x * -4.0f);
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
    zAxis[1] = f5 * s + f1 * c;
    zAxis[2] = f6 * s + f2 * c;
}

}}  // namespace EA::Swarm

// ===========================================================================
// @ 0x005a2600
void FUN_005a2600(void* self)
{
    (void)self;
}

// @ 0x005a2b30
void cTerrainUI::FUN_005a2b30(int flag)
{
    *(int volatile*)&flag = flag;
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
