// Slice s00c84420 -- star display radius helper.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

// Star tuning lookups (defined in the cSolarSystem slice).
void  __cdecl c8b470(int type, int* a, int* b);  // 0x00c8b470
float __cdecl GetStarTuning(int type);           // 0x00c841a0
float __cdecl GetStarRadius(int type);           // 0x00c84120

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
};

// World up axis (0, 0, 1).
extern Vec3  gAxis;       // 0x1579d58
extern float gHeight;     // 0x13ec4d8  90.0f

// Terrain/volume brush math object (layout of the `this` of 0x00fe8450).
struct Brush {
    unsigned char b00, pad01, pad02, pad03;
    Vec3  pos;                 // +0x04
    float f10;                 // +0x10
    Vec3  dir;                 // +0x14
    float f20;                 // +0x20
    float f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;

    // Filled in by the caller: starts at the world up axis, extends `dir`
    // with radius knob `f10` and height `f20`.
    void f8450();              // 0x00fe8450
};

// @ 0x00c84420
float __cdecl StarSpanRadius(int type)
{
    int a, b;
    c8b470(type, &a, &b);

    float ta = GetStarTuning(a);
    float tb = GetStarTuning(b);
    float ra = GetStarRadius(a);
    float t  = tb / ta;
    float f  = (ra + GetStarRadius(b)) * 1.5f / (t + 1.0f) + 10.0f;
    float ft = f * t;

    float v10 = (a == b) ? 0.2f : 0.0f;

    Brush along;
    along.b00 = 0;
    along.pos = gAxis;
    along.f10 = v10;
    along.dir = Vec3(ft, 0.0f, 0.0f);
    along.f20 = gHeight;
    along.f8450();

    Brush against;
    against.b00 = 0;
    against.pos = gAxis;
    against.f10 = v10;
    against.dir = Vec3(-f, 0.0f, 0.0f);
    against.f20 = gHeight;
    against.f8450();

    float up   = against.f24 + f;
    float side = along.f24 + ft;
    const float& best = up > side ? up : side;
    return best;
}
