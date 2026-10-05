// Slice s0044ae00: cSPEditorBlock accessors / bounding-box /Od /Ob1 helpers.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
#include "types.h"

struct V3 {
    float x, y, z;
    V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct M3 {
    float m[9];
    M3& operator=(const M3& o);
};

struct Blk {
    char pad0[0x1e8];
    V3 mVec;            // +0x1e8
    M3 mMat;            // +0x1f4
    char pad1[0x434 - 0x218];
    int m434;           // +0x434
    char pad2[0x604 - 0x438];
    int m604;           // +0x604

    void Aae00(void* box, int a, int b, int c);
    V3* B550(V3* out);
    M3* B590(M3* out);
    void B640(int a);
    void B6b0();
    bool B780();
    void B7b0();
    void Ba20();
};

// @ 0x0044b550  (byte-exact)
V3* Blk::B550(V3* out)
{
    *out = mVec;
    return out;
}

// @ 0x0044b590  (near miss: frame 0x30)
M3* Blk::B590(M3* out)
{
    *out = mMat;
    return out;
}

// @ 0x0044b780  (byte-exact)
bool Blk::B780()
{
    if (m604 != 0)
        return true;
    if (m434 != 0)
        return true;
    return false;
}

// @ 0x0044ae00
void Blk::Aae00(void*, int, int, int)
{
}

// @ 0x0044b640
void Blk::B640(int)
{
}

// @ 0x0044b6b0
void Blk::B6b0()
{
}

// @ 0x0044b7b0
void Blk::B7b0()
{
}

// @ 0x0044ba20
void Blk::Ba20()
{
}
