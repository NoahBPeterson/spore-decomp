// Slice s0044bcf0: /Od /Ob1 cSPEditorBlock helpers.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
#include "types.h"

extern const float g_eps;   // 0.001f
struct Vec1 { float x, y, z; float& operator[](int i) { return (&x)[i]; } };
struct M3 { float m[9]; M3& operator=(const M3&); };

struct Blk {
    char pad0[0x48];
    Vec1 mVec;          // +0x48
    char gap1[0xc];
    M3 mMat;            // +0x60
    char pad1[0x1c4 - 0x84];
    int m1c4;           // +0x1c4
    char pad2[0x3e0 - 0x1c8];
    Blk* m3e0;          // +0x3e0

    Blk* Child() { return m3e0; }

    void Abcf0();
    int C050();
    void C0e0();
    void C270();
    int C450();
    void C480(int v);
    void C4d0(int a);
    void C5a0(int a);
};

// @ 0x0044c480  (byte-exact)
void Blk::C480(int v)
{
    m1c4 = v;
    if (Child() != 0)
        Child()->m1c4 = v;
}

// @ 0x0044c050  (near miss: 5 diff, only the this/frame slot vs result slot swapped)
int Blk::C050()
{
    float f = mVec[0];
    float r;
    if (f < -g_eps) {
        r = -1.0f;
    } else {
        r = (f > g_eps) ? 1.0f : 0.0f;
    }
    int n = (int)r;
    return n;
}

// @ 0x0044bcf0
void Blk::Abcf0()
{
}

// @ 0x0044c0e0
void Blk::C0e0()
{
}

// @ 0x0044c270
void Blk::C270()
{
}

// @ 0x0044c450
int Blk::C450()
{
    return 0;
}

// @ 0x0044c4d0
void Blk::C4d0(int)
{
}

// @ 0x0044c5a0
void Blk::C5a0(int)
{
}
