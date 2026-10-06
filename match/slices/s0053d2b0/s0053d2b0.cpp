// Swarm skin-paint particle: constructor that also builds the cube-edge lookup tables.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

namespace {

struct Entry4 { uint16_t mask; uint8_t edge; uint8_t pad; };

struct Corner {                           // 4 bytes: x, y, z, w (stored by FUN_0053e190)
    uint8_t v[4];
    Corner* Set(uint8_t z, uint8_t y, uint8_t x, uint8_t w);
};

struct Face {                             // 0x20 bytes, built by FUN_0053e1d0
    uint8_t idx, idxXor, bitA, bitB;
    uint8_t bits[4];
    uint32_t normal;                      // +8
    uint8_t cornerMask, cornerCount, pad[2];
    uint8_t c[4][4];                      // +0x10 corner coordinates
    Face* Init(uint8_t index, uint32_t* a, uint32_t* b, uint32_t* c_, uint32_t* d, uint32_t* n);
};

// Tables in .data/.rdata (declared extern: relocations are masked).
extern const uint8_t g_edgeCorners[24];   // 0x0150cb8c: 12 edges x 2 corner indices
extern uint16_t g_edgeMaskTable[256];     // 0x015e2658
extern uint8_t g_cornerBit[24];           // 0x015e2858 (12 edges x 2)
extern uint8_t g_edgeIndex[24];           // 0x015e28d0
extern uint8_t g_edgeLut[64];             // 0x015e28e8: [maskA*8+maskB] -> edge id
extern Face g_faces[6];                   // 0x015e2a38
extern uint32_t g_cornerTable[8];         // 0x015e2d08 (8 corners x 4 bytes)
extern Entry4 g_entryA[64];               // 0x015e2928 (+2 = 0x015e292a)
extern Entry4 g_entryB[64];               // 0x015e25f8
extern Entry4 g_entryC[64];               // 0x015e2870

int __cdecl Wrap(int v, int m, int* q);   // 0x0053e120: floor-mod

inline uint8_t Mask3(const uint8_t* p) { return (uint8_t)(p[0] | (p[1] << 1) | (p[2] << 2)); }

struct AllocTag { AllocTag() {} };
struct Alloc1 { Alloc1(const AllocTag& tag); uint32_t pad[4]; };   // FUN_00429360, 0x10 bytes
struct Alloc2 { Alloc2(const AllocTag& tag); uint32_t pad[5]; };   // FUN_00540470, 0x14 bytes

struct VecA {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
    Alloc1 mAlloc;
    VecA(const AllocTag& tag) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(tag) {}
};

struct RefObj { int vtbl; int mRefCount; };
struct RefPtr {
    RefObj* mpObject;
    RefPtr() : mpObject(0) { if (mpObject) mpObject->mRefCount = mpObject->mRefCount + 1; }
};

class cCreatureAbility {
public:
    cCreatureAbility() : mRefCount(0) {}
    virtual void Dummy0();
    virtual void Dummy1();
    int mRefCount;
};

class cSPSkinPaintParticle : public cCreatureAbility {
public:
    cSPSkinPaintParticle(float rate);
    virtual void Dummy0();
    virtual void Dummy1();
    uint32_t pad08[3];
    float mRate;                 // +0x14
    float mInvRate;              // +0x18
    uint32_t pad1c;
    VecA mVec1;                  // +0x20
    Alloc2 mA;                   // +0x3c
    VecA mVec2;                  // +0x50
    Alloc2 mB;                   // +0x68
    Alloc2 mC;                   // +0x7c
    RefPtr mRefA;                // +0x90
    RefPtr mRefB;                // +0x94
};

// @ 0x0053d2b0
cSPSkinPaintParticle::cSPSkinPaintParticle(float rate)
    : mRate(rate), mInvRate(1.0f / rate), mVec1(AllocTag()), mA(AllocTag()), mVec2(AllocTag()),
      mB(AllocTag()), mC(AllocTag())
{
    uint8_t unusedA[4] = { 3, 2, 1, 4 };
    uint8_t unusedB[4] = { 3, 2, 1, 0 };
    uint8_t unusedC[4] = { 1, 2, 3, 0 };

    uint8_t f0a[4] = { 0, 0, 0, 0 }, f0b[4] = { 0, 1, 0, 0 }, f0c[4] = { 0, 1, 1, 0 }, f0d[4] = { 0, 0, 1, 0 }, f0n[4] = { 0xff, 0, 0, 0 };
    uint8_t f1a[4] = { 1, 0, 0, 0 }, f1b[4] = { 1, 1, 0, 0 }, f1c[4] = { 1, 1, 1, 0 }, f1d[4] = { 1, 0, 1, 0 }, f1n[4] = { 1, 0, 0, 0 };
    uint8_t f2a[4] = { 0, 0, 0, 0 }, f2b[4] = { 0, 0, 1, 0 }, f2c[4] = { 1, 0, 1, 0 }, f2d[4] = { 1, 0, 0, 0 }, f2n[4] = { 0, 0xff, 0, 0 };
    uint8_t f3a[4] = { 0, 1, 0, 0 }, f3b[4] = { 0, 1, 1, 0 }, f3c[4] = { 1, 1, 1, 0 }, f3d[4] = { 1, 1, 0, 0 }, f3n[4] = { 0, 1, 0, 0 };
    uint8_t f4a[4] = { 0, 0, 0, 0 }, f4b[4] = { 1, 0, 0, 0 }, f4c[4] = { 1, 1, 0, 0 }, f4d[4] = { 0, 1, 0, 0 }, f4n[4] = { 0, 0, 0xff, 0 };
    uint8_t f5a[4] = { 0, 0, 1, 0 }, f5b[4] = { 1, 0, 1, 0 }, f5c[4] = { 1, 1, 1, 0 }, f5d[4] = { 0, 1, 1, 0 }, f5n[4] = { 0, 0, 1, 0 };

    Face faces[6];
    faces[0].Init(0, (uint32_t*)f0a, (uint32_t*)f0b, (uint32_t*)f0c, (uint32_t*)f0d, (uint32_t*)f0n);
    faces[1].Init(1, (uint32_t*)f1a, (uint32_t*)f1b, (uint32_t*)f1c, (uint32_t*)f1d, (uint32_t*)f1n);
    faces[2].Init(2, (uint32_t*)f2a, (uint32_t*)f2b, (uint32_t*)f2c, (uint32_t*)f2d, (uint32_t*)f2n);
    faces[3].Init(3, (uint32_t*)f3a, (uint32_t*)f3b, (uint32_t*)f3c, (uint32_t*)f3d, (uint32_t*)f3n);
    faces[4].Init(4, (uint32_t*)f4a, (uint32_t*)f4b, (uint32_t*)f4c, (uint32_t*)f4d, (uint32_t*)f4n);
    faces[5].Init(5, (uint32_t*)f5a, (uint32_t*)f5b, (uint32_t*)f5c, (uint32_t*)f5d, (uint32_t*)f5n);
    for (int n = 0; n < 6; n++) ((Face*)g_faces)[n] = faces[n];

    Corner corners[8];
    corners[0].v[0] = 0; corners[0].v[1] = 0; corners[0].v[2] = 0; corners[0].v[3] = 0;
    corners[1].v[0] = 1; corners[1].v[1] = 0; corners[1].v[2] = 0; corners[1].v[3] = 0;
    corners[2].v[0] = 0; corners[2].v[1] = 1; corners[2].v[2] = 0; corners[2].v[3] = 0;
    corners[3].v[0] = 1; corners[3].v[1] = 1; corners[3].v[2] = 0; corners[3].v[3] = 0;
    corners[4].Set(1, 0, 0, 0);
    corners[5].Set(1, 0, 1, 0);
    corners[6].Set(1, 1, 0, 0);
    corners[7].Set(1, 1, 1, 0);
    for (int n = 0; n < 8; n++) g_cornerTable[n] = *(uint32_t*)&corners[n];

    uint32_t i;
    for (i = 0; i < 0x40; i++)
        g_edgeLut[i] = 0xff;

    for (i = 0; i < 0xc; i++) {
        uint8_t a = g_edgeCorners[i * 2];
        uint8_t b = g_edgeCorners[i * 2 + 1];
        uint8_t id = (a < b) ? (uint8_t)(i << 1) : (uint8_t)((i << 1) | 1);
        g_edgeLut[a * 8 + b] = id;
        g_edgeLut[b * 8 + a] = id ^ 1;
    }

    for (i = 0; i < 0xc; i++) {
        g_cornerBit[i * 2] = (uint8_t)(1 << g_edgeCorners[i * 2]);
        g_cornerBit[i * 2 + 1] = (uint8_t)(1 << g_edgeCorners[i * 2 + 1]);
    }

    for (i = 0; i < 0x18; i++)
        g_edgeIndex[i] = g_edgeCorners[(i >> 1) * 2 + (i & 1)];

    for (i = 0; i < 6; i++) {
        Face* face = g_faces + i;
        int step = (i & 1) ? 1 : -1;
        for (int j = 0; j < 4; j++) {
            int c0 = Wrap(step * 0 + j, 4, 0);
            int c1 = Wrap(j + step, 4, 0);
            int c2 = Wrap(j + step * 2, 4, 0);
            int c3 = Wrap(step * 3 + j, 4, 0);
            uint8_t e01 = g_edgeLut[Mask3(face->c[c0]) * 8 + Mask3(face->c[c1])];
            uint8_t e21 = g_edgeLut[Mask3(face->c[c2]) * 8 + Mask3(face->c[c1])];
            uint8_t e32 = g_edgeLut[Mask3(face->c[c3]) * 8 + Mask3(face->c[c2])];
            uint8_t e03 = g_edgeLut[Mask3(face->c[c0]) * 8 + Mask3(face->c[c3])];
            g_entryA[e01].edge = e21;
            g_entryA[e01].mask = (uint16_t)(1 << (e21 >> 1));
            g_entryB[e01].edge = e32;
            g_entryB[e01].mask = (uint16_t)(1 << (e32 >> 1));
            g_entryC[e01].edge = e03;
            g_entryC[e01].mask = (uint16_t)(1 << (e03 >> 1));
        }
    }

    for (uint32_t k = 0; k < 0x100; k++) {
        uint16_t acc = 0;
        uint16_t bit = 1;
        for (uint32_t j = 0; j < 0xc; j++, bit = (uint16_t)(bit << 1)) {
            uint8_t b5 = g_cornerBit[j * 2] & k;
            uint8_t b3 = g_cornerBit[j * 2 + 1] & k;
            if ((b5 != 0 && b3 == 0) || (b5 == 0 && b3 != 0))
                acc = acc | bit;
        }
        g_edgeMaskTable[k] = acc;
    }
}

}
