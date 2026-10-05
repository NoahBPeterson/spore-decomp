// Slice s0044d4f0: /Od /Ob1 bounds/vector helpers.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
#include "types.h"

struct V3 { float x, y, z; V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; } };

// @ 0x0044e410  (byte-exact)
struct V4 {
    float x, y, z, w;
    V4(float a, float b, float c, float d);
};
V4::V4(float a, float b, float c, float d)
{
    x = a;
    y = b;
    z = c;
    w = d;
}

struct Bounds {
    V3 mn;      // +0x00
    V3 mx;      // +0x0c
    int m18;    // +0x18
    bool m1c;   // +0x1c
    Bounds& operator=(const Bounds& o);
};

// @ 0x0044d960  (byte-exact)
Bounds& Bounds::operator=(const Bounds& o)
{
    mn = o.mn;
    mx = o.mx;
    m18 = o.m18;
    m1c = o.m1c;
    return *this;
}

struct Blk {
    char pad[0x234];
    Bounds* mBeg;   // +0x234
    Bounds* mEnd;   // +0x238

    void D4f0(void* out);
    void D570();
    void D8f0(void* out, int index);
    void D9e0();
};

// @ 0x0044d4f0
void Blk::D4f0(void*)
{
}

// @ 0x0044d570
void Blk::D570()
{
}

// @ 0x0044d8f0
void Blk::D8f0(void*, int)
{
}

// @ 0x0044d9e0
void Blk::D9e0()
{
}
