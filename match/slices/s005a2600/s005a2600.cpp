// Slice s005a2600 -- SP::cTerrainUI input/command helpers, config refresh, transform
// composition and scalar deleting destructor + EA::Swarm::cTransform::PreRotateX.
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
extern float g_015e6c58;       // 0x015e6c58  default pitch limit (runtime .data)
extern float g_015e6c30;       // 0x015e6c30  default pitch limit (runtime .data)
extern float g_015d1168;       // 0x015d1168  default property float
void __fastcall FUN_007c4180(void* viewer, int dummy, void* out, void* src);  // 0x007c4180 thiscall, ret 8
void __fastcall FUN_007c4010(void* viewer, int dummy, unsigned* out);         // 0x007c4010 thiscall, ret 4
float* __fastcall Property_GetFloat(void* prop);                              // 0x0041ea70 thiscall, ret 0

// Property-list interface used by all the config lookups below.
struct cPropertyList {
    virtual void AddRef();                               // +0x00
    virtual void Release();                              // +0x04
    virtual void v08();                                  // +0x08
    virtual void v0c();                                  // +0x0c
    virtual void v10();                                  // +0x10
    virtual void v14();                                  // +0x14
    virtual void v18();                                  // +0x18
    virtual bool HasProperty(unsigned id);               // +0x1c
    virtual void v20();                                  // +0x20
    virtual bool QueryProperty(unsigned id, void** out);// +0x24
    virtual void* GetProperty(unsigned id);              // +0x28
};

namespace EA { namespace Swarm {
struct cTransform;
}}

struct cTerrainUI {
    void* mVtbl0;                                          // +0x00
    void* mVtbl1;                                          // +0x04
    void* mVtbl2;                                          // +0x08
    void* mUnk0c;                                          // +0x0c
    cPropertyList* mConfig;                                // +0x10
    char pad14[0xe8 + 4 - 0x14];
    __declspec(noinline) void FUN_005a2b30(char flag);       // 0x005a2b30
    void ZoomBy(float factor);                              // 0x005a2200
    bool OnMouseDown(int a, float x, float y, int b);       // 0x005a2f20
    bool OnMouseWheel(float x, float y, int delta);         // 0x005a2f80
    void Command(int cmd, float x, float y);                // 0x005a2c00
    void ConfigUpdated();                                   // 0x005a2600
    void UpdateTransform(EA::Swarm::cTransform* t);         // 0x005a3080
    cTerrainUI(cPropertyList* config);                      // 0x005a3220
    void* ScalarDelete(unsigned flags);                     // 0x005a2ed0

    __forceinline bool GetConfigFloat(unsigned id, float& out) {
        if (!mConfig->HasProperty(id))
            return false;
        unsigned* rec = (unsigned*)mConfig->GetProperty(id);
        unsigned short t = *(unsigned short*)((char*)rec + 0x12);
        float* p;
        if (t == 0xd || t == 0x10) {
            if (*(unsigned char*)((char*)rec + 0x10) & 0x30)
                p = (float*)(size_t)(*rec);
            else
                p = (float*)(size_t)((t ? 0xffffffffu : 0u) & (unsigned)(size_t)rec);
        } else {
            p = &g_015d1168;
        }
        out = *p;
        return true;
    }
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
    float mOffset[3];            // +0x4
    float mScale;                // +0x10
    float mRotation[9];          // +0x14
    void PreRotateX(float angle);   // 0x005a2d90
    void PreRotateY(float angle);   // 0x004099b0
};

// @ 0x005a2d90
void cTransform::PreRotateX(float angle)
{
    float f1 = mRotation[4];
    float f2 = mRotation[5];
    float f3 = mRotation[3];
    float f4 = mRotation[6];
    float f5 = mRotation[7];
    float f6 = mRotation[8];
    float s = (float)sinf(angle);
    float c = (float)cosf(angle);
    mRotation[3] = f3 * c + f4 * s;
    mRotation[4] = f5 * c + f1 * s;
    mRotation[5] = f6 * c + f2 * s;
    s = -s;
    mFlags |= 2;
    mModificationCount++;
    mRotation[6] = f3 * s + f4 * c;
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
void cTerrainUI::ConfigUpdated()
{
    float f;
    *(char*)((char*)this + 0x9c) = 0;
    if (GetConfigFloat(0xc7c4f8, *(float*)((char*)this + 0x14))) {}
    if (GetConfigFloat(0xc7c4fa, *(float*)((char*)this + 0x18))) {}
    if (GetConfigFloat(0xc7c4f9, *(float*)((char*)this + 0x1c))) {}
    if (GetConfigFloat(0xc7c4fb, f)) {
        *(float*)((char*)this + 0x28) = f;
        *(float*)((char*)this + 0x38) = f;
        *(float*)((char*)this + 0x4c) = f;
    }
    if (GetConfigFloat(0xc7c4fc, f)) {
        float d = f * 0.017453292f;
        *(float*)((char*)this + 0x34) = d;
        *(float*)((char*)this + 0x48) = d;
    }
    if (GetConfigFloat(0xc7c4fd, f)) {
        float d = f * 0.017453292f;
        *(float*)((char*)this + 0x30) = d;
        *(float*)((char*)this + 0x44) = d;
    }
    if (GetConfigFloat(0x6fda2e1c, f)) {
        *(float*)((char*)this + 0x3c) = f;
        *(float*)((char*)this + 0x50) = f;
    }
    if (GetConfigFloat(0x8fda2e23, f)) {
        *(float*)((char*)this + 0x40) = f;
        *(float*)((char*)this + 0x54) = f;
    }
    if (GetConfigFloat(0xfe23b2, *(float*)((char*)this + 0x58))) {}
    if (GetConfigFloat(0xfe2437, *(float*)((char*)this + 0x5c))) {}
    if (GetConfigFloat(0xfe243b, f))
        *(float*)((char*)this + 0x60) = f * 0.017453292f;
    if (GetConfigFloat(0xfe243f, f))
        *(float*)((char*)this + 0x64) = f * 0.017453292f;

    if (mConfig != 0) {
        void* rec;
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0x1102b20, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 0xd)
            *(float*)((char*)this + 0x68) = *Property_GetFloat(rec);
    }
    if (mConfig != 0) {
        void* rec;
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0x1102b2f, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 0xd)
            *(float*)((char*)this + 0x6c) = *Property_GetFloat(rec);
    }
    if (GetConfigFloat(0x44c6220, f))
        *(float*)((char*)this + 0x70) = f * 57.29578f;
    else
        *(float*)((char*)this + 0x70) = 57.29578f;
}

// ===========================================================================
// @ 0x005a2ed0
void* cTerrainUI::ScalarDelete(unsigned flags)
{
    *(void**)((char*)this + 0) = (void*)0x13f69c8;
    *(void**)((char*)this + 4) = (void*)0x13f69b8;
    *(void**)((char*)this + 8) = (void*)0x13f69b4;
    _ReadWriteBarrier();
    cPropertyList* cfg = *(cPropertyList**)((char*)this + 0x10);
    if (cfg)
        ((void(__thiscall*)(void*))(*(void***)cfg)[4 / 4])(cfg);
    *(void**)((char*)this + 8) = (void*)0x13ef094;
    *(void**)((char*)this + 4) = (void*)0x13eb394;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
    if (flags & 1)
        operator delete(this);
    return this;
}

// ===========================================================================
// @ 0x005a3080
void cTerrainUI::UpdateTransform(EA::Swarm::cTransform* t)
{
    EA::Swarm::cTransform* tr = t;
    float k = 0.52f / *(float*)((char*)this + 0x8c);
    float v = *(float*)((char*)this + 0x4c);
    if (v > *(float*)((char*)this + 0x5c))
        v = *(float*)((char*)this + 0x5c);
    else if (*(float*)((char*)this + 0x58) > v)
        v = *(float*)((char*)this + 0x58);
    tr->PreRotateY(-*(float*)((char*)this + 0x44));
    tr->PreRotateX(*(float*)((char*)this + 0x48));
    float ax = -*(float*)((char*)this + 0x50) * v * k;
    float ay = -v;
    float az = *(float*)((char*)this + 0x54) * v * k;
    float s = tr->mScale;
    ax *= s;
    ay *= s;
    az *= s;
    float* m = tr->mRotation;
    tr->mOffset[0] += m[6] * az + m[3] * ay + m[0] * ax;
    tr->mOffset[1] += m[7] * az + m[4] * ay + m[1] * ax;
    tr->mOffset[2] += m[8] * az + m[5] * ay + m[2] * ax;
    tr->mFlags |= 4;
    tr->mModificationCount++;
    tr->mOffset[0] += *(float*)((char*)this + 0x74);
    tr->mOffset[1] += *(float*)((char*)this + 0x78);
    tr->mOffset[2] += *(float*)((char*)this + 0x7c);
    tr->mFlags |= 4;
    tr->mModificationCount++;
}

// ===========================================================================
// @ 0x005a3220
cTerrainUI::cTerrainUI(cPropertyList* config)
{
    *(void**)((char*)this + 4) = (void*)0x13eb384;
    *(void**)((char*)this + 8) = (void*)0x13ef094;
    *(void**)((char*)this + 0xc) = (void*)0;
    *(void**)((char*)this + 0) = (void*)0x13f69c8;
    *(void**)((char*)this + 4) = (void*)0x13f69b8;
    *(void**)((char*)this + 8) = (void*)0x13f69b4;
    *(cPropertyList**)((char*)this + 0x10) = config;
    if (config)
        ((void(__thiscall*)(void*))(*(void***)config)[0 / 4])(config);
    float zero = 0.0f;
    float one = 1.0f;
    float c;
    c = 10.0f;
    *(float*)((char*)this + 0x38) = c;
    c = 5.0f;
    *(float*)((char*)this + 0x58) = c;
    c = 25.0f;
    *(float*)((char*)this + 0x5c) = c;
    c = g_015e6c58;
    *(float*)((char*)this + 0x60) = c;
    c = g_015e6c30;
    *(float*)((char*)this + 0x64) = c;
    c = -1.0f;
    *(float*)((char*)this + 0x68) = c;
    *(float*)((char*)this + 0x6c) = c;
    c = one;
    *(float*)((char*)this + 0x14) = c;
    *(float*)((char*)this + 0x18) = c;
    *(float*)((char*)this + 0x1c) = c;
    c = zero;
    *(float*)((char*)this + 0x20) = c;
    *(float*)((char*)this + 0x24) = c;
    c = one;
    *(float*)((char*)this + 0x28) = c;
    *(char*)((char*)this + 0x2c) = 0;
    c = zero;
    *(float*)((char*)this + 0x30) = c;
    *(float*)((char*)this + 0x34) = c;
    *(float*)((char*)this + 0x3c) = c;
    *(float*)((char*)this + 0x40) = c;
    *(float*)((char*)this + 0x44) = c;
    *(float*)((char*)this + 0x48) = c;
    *(float*)((char*)this + 0x4c) = c;
    *(float*)((char*)this + 0x50) = c;
    *(float*)((char*)this + 0x54) = c;
    c = 57.29578f;
    *(float*)((char*)this + 0x70) = c;
    *(float*)((char*)this + 0x74) = g_015e6a6c[0];
    *(float*)((char*)this + 0x78) = g_015e6a6c[1];
    *(float*)((char*)this + 0x7c) = g_015e6a6c[2];
    *(float*)((char*)this + 0x80) = g_015e6a6c[0];
    *(float*)((char*)this + 0x84) = g_015e6a6c[1];
    *(float*)((char*)this + 0x88) = g_015e6a6c[2];
    c = one;
    *(float*)((char*)this + 0x8c) = c;
    *(char*)((char*)this + 0x90) = 0;
    c = zero;
    *(float*)((char*)this + 0x94) = c;
    *(float*)((char*)this + 0x98) = c;
    *(char*)((char*)this + 0x9c) = 0;
    ((cLocalInputState*)((char*)this + 0xa0))->Init();
    *(void**)((char*)this + 0xe8) = (void*)0;
    if (*(cPropertyList**)((char*)this + 0x10))
        ConfigUpdated();
}

// ===========================================================================
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
