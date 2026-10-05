// Slice s005a1920 -- SP::cTerrainUI / cEditorCameraController helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

typedef unsigned int size_t;

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

struct cLocalInputState {
    char pad[0x40];
    bool OnKeyDown(int key, int x);         // 0x00697a50
    bool OnKeyUp(int key, int x);           // 0x00697a80
    bool OnMouseUp(int a, float x, float y, int b);   // 0x00697af0
    unsigned int OnMouseWheel(int a, int b, float x, float y);  // 0x00697b40
};

struct Cam {
    char  pad0[0x14];
    float m14;          // +0x14
    char  pad18[0x2c - 0x18];
    char  m2c;          // +0x2c
    char  pad2d[0x30 - 0x2d];
    float m30;          // +0x30
    char  pad34[0x38 - 0x34];
    float m38;          // +0x38
    float m3c;          // +0x3c
    float m40;          // +0x40
    float m44, m48, m4c, m50, m54;   // +0x44..0x58
    float m58;          // +0x58
    float m5c;          // +0x5c
    char  pad60[0x74 - 0x60];
    Vec3  m74;          // +0x74
    Vec3  m80;          // +0x80
    float m8c;          // +0x8c
    char  pad90[0x9c - 0x90];
    char  m9c;          // +0x9c
    char  pad9d[0xa0 - 0x9d];
    cLocalInputState mInput;   // +0xa0

    void SetSomething(Vec3 v, bool immediate);                       // 0x005a2010
    bool OnKeyDown(int key, int x);                                  // 0x005a2080
    bool OnKeyUp(int key, int x);                                    // 0x005a2120
    bool OnMouseUp(int a, float x, float y, int b);                  // 0x005a21c0
    void ZoomBy(float factor);                                       // 0x005a2200
    void AddAngle(float d);                                          // 0x005a2240
    void ComputeView(float* a, float* b, float* c, float* out);      // 0x005a2260
    void UpdatePitch();                                              // 0x005a22d0
    void ClearVtables();                                             // 0x005a2300
    void OnMouseWheel(int a, int b, float x, float y);               // 0x005a2580
};

extern float kOne_1485720;
extern float kHalf_1471064;
extern float k0_1_1488874;
extern float kDiv_150f2c4;
extern float k0_52_13f69b0;
extern float kSign_13eb8b0;
extern float k0_1_150f2c8;
extern float kMul_13f6a24;

extern char vtbl_5a2300_a;
extern char vtbl_5a2300_b;

// ===========================================================================
// @ 0x005a2010
void Cam::SetSomething(Vec3 v, bool immediate)
{
    m80 = v;
    if (immediate)
        m74 = v;
}

// ===========================================================================
// @ 0x005a2080
bool Cam::OnKeyDown(int key, int x)
{
    switch (key) {
    case 0x6b: case 0x6d: case 0xbb: case 0xbc: case 0xbd: case 0xbe:
        mInput.OnKeyDown(key, x);
        return true;
    default:
        return false;
    }
}

// ===========================================================================
// @ 0x005a2120
bool Cam::OnKeyUp(int key, int x)
{
    switch (key) {
    case 0x6b: case 0x6d: case 0xbb: case 0xbc: case 0xbd: case 0xbe:
        mInput.OnKeyUp(key, x);
        return true;
    default:
        return false;
    }
}

// ===========================================================================
// @ 0x005a21c0
bool Cam::OnMouseUp(int a, float x, float y, int b)
{
    mInput.OnMouseUp(a, x, y, b);
    m2c = 0;
    return true;
}

// ===========================================================================
// @ 0x005a2200
void Cam::ZoomBy(float factor)
{
    float one = kOne_1485720;
    float f = (factor + one) * m38;
    m38 = f;
    float t = m5c;
    if (f > t)
        m38 = t;
    else {
        t = m58;
        if (t > f)
            m38 = t;
    }
    m9c = 1;
}

// ===========================================================================
// @ 0x005a2240
void Cam::AddAngle(float d)
{
    m30 = k0_1_150f2c8 * d + m30;
}

// ===========================================================================
// @ 0x005a2260
void Cam::ComputeView(float* a, float* b, float* c, float* out)
{
    float angle = m4c;
    float scale = k0_52_13f69b0 / m8c;
    *a = m44;
    *b = m48;
    *c = m4c;
    out[0] = -((m50 * scale) * angle);
    out[1] = -angle;
    out[2] = (m54 * scale) * angle;
}

// ===========================================================================
// @ 0x005a22d0
void Cam::UpdatePitch()
{
    m54 = (k0_1_1488874 - (Abs(m48) / kDiv_150f2c4) * kHalf_1471064) * m8c + m40;
}

// ===========================================================================
// @ 0x005a2300
void Cam::ClearVtables()
{
    *(void**)((char*)this + 4) = &vtbl_5a2300_a;
    *(void**)this = &vtbl_5a2300_b;
}

// ===========================================================================
// @ 0x005a2580
void Cam::OnMouseWheel(int a, int b, float x, float y)
{
    mInput.OnMouseWheel(a, b, x, y);
    float f = (((float)a * m14) * kMul_13f6a24 + kOne_1485720) * m38;
    float t = m5c;
    m38 = f;
    if (f > t)
        m38 = t;
    else {
        t = m58;
        if (t > f)
            m38 = t;
    }
    m9c = 1;
}

// ===========================================================================
// @ 0x005a1920
void cTerrainUI_Init(void* self)
{
    (void)self;
}

// @ 0x005a2370
void SetCenterCameraOffset(void* self)
{
    (void)self;
}

// @ 0x005a2400
void SetPartModeCameraOffset(void* self)
{
    (void)self;
}

// @ 0x005a24c0
void SetPaintModeCameraOffset(void* self)
{
    (void)self;
}
