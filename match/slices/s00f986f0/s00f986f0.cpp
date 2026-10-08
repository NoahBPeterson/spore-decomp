// Slice s00f986f0 -- 0x00f98970: per-frame lighting / sky parameter snapshot (2402 bytes, thiscall, no args).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Pulls the current environment record (virtual slot 4 of `this`) and the active light vector
// (virtual slot 70), copies ~26 blocks of colour/direction/matrix data from the record into this
// object's render snapshot, derives the cone factors from the cosines of four angles (degrees to
// radians), applies the per-frame accumulated deltas (+0xa1c .. +0xa34) to a few of the copied
// values, and, if the blend factor in +0xa44 is below 1, linearly blends six colour vectors
// (record value -> the target vector at +0xa38) by (1 - factor).
#include "types.h"
#include <math.h>

union W {
    uint32_t u;
    float f;
};

struct Vec4 {
    float x, y, z, w;
};
inline Vec4 operator-(const Vec4& a, const Vec4& b)
{
    Vec4 r = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    return r;
}
inline Vec4 operator*(const Vec4& a, float s)
{
    Vec4 r = {a.x * s, a.y * s, a.z * s, a.w * s};
    return r;
}
inline Vec4 operator+(const Vec4& a, const Vec4& b)
{
    Vec4 r = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    return r;
}

#define VSLOTS10(n) \
    virtual void pad##n##0(); virtual void pad##n##1(); virtual void pad##n##2(); \
    virtual void pad##n##3(); virtual void pad##n##4(); virtual void pad##n##5(); \
    virtual void pad##n##6(); virtual void pad##n##7(); virtual void pad##n##8(); \
    virtual void pad##n##9();

// Only the two virtuals this function calls are meaningful; the rest pad the vtable layout.
struct SkyState {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual char* GetRecord();  // vtable +0x10
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    VSLOTS10(1) VSLOTS10(2) VSLOTS10(3) VSLOTS10(4) VSLOTS10(5) VSLOTS10(6)
    virtual uint32_t* GetLightVector();  // vtable +0x118

    void Update();
};

#define SRC(off) (*(W*)(rec + (off)))

// @ 0x00f98970
void SkyState::Update()
{
    W* d = (W*)this;
    char* rec = GetRecord();

    d[0x142].u = SRC(0x42c).u;
    d[0x143].u = SRC(0x430).u;
    d[0x144].u = SRC(0x434).u;
    d[0x145].u = SRC(0x438).u;
    d[0x146].u = SRC(0x43c).u;
    d[0x147].u = SRC(0x440).u;
    d[0x148].u = SRC(0x444).u;
    d[0x149].u = SRC(0x448).u;
    uint32_t* light = GetLightVector();
    d[0x14a].u = light[0];
    d[0x14b].u = light[1];
    d[0x14c].u = light[2];
    d[0x14d].u = light[3];
    d[0x14e].u = SRC(0x4bc).u;
    d[0x14f].u = SRC(0x4c0).u;
    d[0x150].u = SRC(0x4c4).u;
    d[0x151].u = SRC(0x4c8).u;
    d[0x152].u = SRC(0x4cc).u;
    d[0x153].u = SRC(0x4d0).u;
    d[0x154].u = SRC(0x4d4).u;
    d[0x155].u = SRC(0x4d8).u;
    d[0x156].u = SRC(0x4dc).u;
    d[0x157].u = SRC(0x4e0).u;
    d[0x158].u = SRC(0x4e4).u;
    d[0x159].u = SRC(0x4e8).u;
    d[0x15a].u = SRC(0x4ec).u;
    d[0x15b].u = SRC(0x4f0).u;
    d[0x15c].u = SRC(0x4f4).u;
    d[0x15d].u = SRC(0x4f8).u;
    d[0x15e].u = SRC(0x34c).u;
    d[0x15f].u = SRC(0x350).u;
    d[0x160].u = SRC(0x354).u;
    d[0x161].u = SRC(0x358).u;
    d[0x16a].u = SRC(0x35c).u;
    d[0x16b].u = SRC(0x360).u;
    d[0x16c].u = SRC(0x364).u;
    d[0x16d].u = SRC(0x368).u;
    d[0x166].u = SRC(0x36c).u;
    d[0x167].u = SRC(0x370).u;
    d[0x168].u = SRC(0x374).u;
    d[0x169].u = SRC(0x378).u;
    d[0x162].u = SRC(0x37c).u;
    d[0x163].u = SRC(0x380).u;
    d[0x164].u = SRC(0x384).u;
    d[0x165].u = SRC(0x388).u;
    d[0x176].u = SRC(0x38c).u;
    d[0x177].u = SRC(0x390).u;
    d[0x178].u = SRC(0x394).u;
    d[0x179].u = SRC(0x398).u;
    d[0x172].u = SRC(0x39c).u;
    d[0x173].u = SRC(0x3a0).u;
    d[0x174].u = SRC(0x3a4).u;
    d[0x175].u = SRC(0x3a8).u;
    d[0x16e].u = SRC(0x3ac).u;
    d[0x16f].u = SRC(0x3b0).u;
    d[0x170].u = SRC(0x3b4).u;
    d[0x171].u = SRC(0x3b8).u;

    const float kDegToRad = 0.017453292f;
    float c1 = cosf(SRC(0x3c0).f * kDegToRad);
    float c2 = cosf(SRC(0x3c4).f * kDegToRad);
    float c3 = cosf(SRC(0x3c8).f * kDegToRad);
    float invA = 1.0f / (c2 - c3);
    float c0 = cosf(SRC(0x3bc).f * kDegToRad);
    d[0x13e].u = d[0xcb].u;
    float invB = 1.0f / (c0 - c1);
    d[0x13f].u = d[0xcc].u;
    d[0x140].u = d[0xcd].u;
    d[0x141].f = c2;
    d[0x17a].f = invB;
    d[0x17b].f = invA;
    d[0x17c].f = -(invB * c1);
    d[0x17d].f = -(invA * c3);

    for (int i = 0; i < 16; ++i)
        d[0x17e + i].u = SRC(0x47c + i * 4).u;

    d[0x1b2].u = d[0x146].u;
    d[0x1b3].u = d[0x147].u;
    d[0x1b4].u = d[0x148].u;
    d[0x1b5].u = d[0x149].u;

    d[0x14e].f = d[0x287].f + d[0x14e].f;
    d[0x149].f = d[0x288].f + d[0x149].f;
    d[0x1b5].f = d[0x1b5].f + d[0x288].f;
    d[0x15a].f = d[0x15a].f - d[0x289].f;
    d[0x156].f = d[0x28a].f + d[0x156].f;
    d[0x157].f = d[0x28b].f + d[0x157].f;
    d[0x159].f = d[0x28c].f + d[0x159].f;
    d[0x150].f = d[0x28d].f + d[0x150].f;

    float blend = d[0x291].f;
    if (blend < 1.0f) {
        float inv = 1.0f - blend;
        const Vec4& target = *(const Vec4*)&d[0x28e];
        static const int srcOff[6] = {0x35c, 0x36c, 0x37c, 0x38c, 0x39c, 0x3ac};
        static const int dstIdx[6] = {0x16a, 0x166, 0x162, 0x176, 0x172, 0x16e};
        for (int g = 0; g < 6; ++g) {
            const Vec4& a = *(const Vec4*)(rec + srcOff[g]);
            Vec4 r = a + (target - a) * inv;
            *(Vec4*)&d[dstIdx[g]] = r;
        }
    }
}
