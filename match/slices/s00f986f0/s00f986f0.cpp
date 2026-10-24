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

// =====================================================================
// SP::cTerrainSphere helpers
// =====================================================================
struct Vec3 {
    float x, y, z;
};

struct cTerrainMapSet {
    char  pad00[0x34];      // +0x00..0x33
    float mRadius34;        // +0x34
    float mRadius38;        // +0x38
    float mRadius3c;        // +0x3c
    float GetHeightAt(Vec3* p);   // 0xf927c0
};

struct TerrainModelObj {
    void** vtbl;            // +0x00
};

struct TerrainModel {
    TerrainModelObj* mpObj;     // +0x00
    unsigned char mFlags;       // +0x04
    char pad05[3];              // +0x05..0x07
    unsigned short mFlags2;     // +0x08
    unsigned short mCounter;    // +0x0a
    float x;                    // +0x0c
    float y;                    // +0x10
    float z;                    // +0x14
};

// Cone / lighting snapshot written by FUN_00f992e0.
struct ConeBlock {
    unsigned mConeCos;      // +0x00 (object +0x638)
    unsigned mConeA;        // +0x04 (object +0x63c)
    unsigned mConeB;        // +0x08 (object +0x640)
    unsigned mConeC;        // +0x0c (object +0x644)
    unsigned mBlockA[4];    // +0x10 (object +0x648)
    unsigned mBlockD[4];    // +0x20 (object +0x658)
    unsigned mBlockC[4];    // +0x30 (object +0x668)
    unsigned mBlockB[4];    // +0x40 (object +0x678)
    unsigned mBlockG[4];    // +0x50 (object +0x688)
    unsigned mBlockF[4];    // +0x60 (object +0x698)
    unsigned mBlockE[4];    // +0x70 (object +0x6a8)
    unsigned mConeInvB;     // +0x80 (object +0x6b8)
    unsigned mConeInvA;     // +0x84 (object +0x6bc)
    unsigned mConeNB;       // +0x88 (object +0x6c0)
    unsigned mConeNA;       // +0x8c (object +0x6c4)
};

struct TerrainSphere {
    char pad000[0x2c];              // +0x000..0x02b
    cTerrainMapSet* mMap;           // +0x02c
    char pad030[0x2b8 - 0x030];     // +0x030..0x2b7
    void** mDecalBegin;             // +0x2b8
    void** mDecalEnd;               // +0x2bc
    char pad2c0[0x32c - 0x2c0];     // +0x2c0..0x32b
    float mConeX;                   // +0x32c
    float mConeY;                   // +0x330
    float mConeZ;                   // +0x334
    char pad338[0x434 - 0x338];     // +0x338..0x433
    float mTrail[24];               // +0x434..0x493
    char pad494[0x638 - 0x494];     // +0x494..0x637
    ConeBlock mCone;                // +0x638..0x6c7
    char pad6c8[0x7d8 - 0x6c8];     // +0x6c8..0x7d7
    TerrainModel** mModels;         // +0x7d8
    TerrainModel** mModelsEnd;      // +0x7dc
    char pad7e0[0x8ac - 0x7e0];     // +0x7e0..0x8ab
    unsigned char mFlag8ac;         // +0x8ac
    char pad8ad[0xa2c - 0x8ad];     // +0x8ad..0xa2b
    Vec4 mTarget;                   // +0xa2c..0xa3b
};

typedef void (__thiscall* RemoveDecalFn)(void* self, int index);
typedef char* (__thiscall* GetRecordFn)(void* self);
typedef void (__thiscall* PinModelFn)(TerrainModelObj* self, TerrainModel* m, int arg);

// @ 0x00f986f0
int __fastcall FUN_00f986f0(TerrainSphere* self, void* dummy, int index)
{
    Vec4 zero = {0.0f, 0.0f, 0.0f, 0.0f};
    if (index < 0) {
        for (int i = 0; i < 6; ++i) {
            self->mTrail[i * 4 + 0] = zero.x;
            self->mTrail[i * 4 + 1] = zero.y;
            self->mTrail[i * 4 + 2] = zero.z;
            self->mTrail[i * 4 + 3] = zero.w;
        }
        return index;
    } else {
        float* p = &self->mTrail[index * 4];
        p[0] = zero.x;
        p[1] = zero.y;
        p[2] = zero.z;
        p[3] = zero.w;
        return (int)p;
    }
}

// @ 0x00f987f0  ?GetRadius@cTerrainSphere@@QAEMXZ
float __fastcall FUN_00f987f0(TerrainSphere* self, void* dummy)
{
    cTerrainMapSet* m = self->mMap;
    return m->mRadius3c * m->mRadius38 + m->mRadius34;
}

// @ 0x00f98800  SP::cTerrainSphere::DirectionToSurfacePosition
void __fastcall FUN_00f98800(TerrainSphere* self, void* dummy, Vec3* out, Vec3* dir)
{
    float h = self->mMap->GetHeightAt(dir);
    float inv = (float)(1.0 / sqrt((double)dir->x * dir->x + (double)dir->y * dir->y + (double)dir->z * dir->z + 1e-8));
    float x = dir->x;
    float y = dir->y;
    float z = dir->z;
    float rx = x * inv;
    float ry = y * inv;
    float rz = z * inv;
    out->x = rx * h;
    out->y = ry * h;
    out->z = rz * h;
}

// @ 0x00f98890
void __fastcall FUN_00f98890(TerrainSphere* self, void* dummy, int unused, Vec3* p, float w)
{
    Vec4 v = {p->x, p->y, p->z, w};
    self->mTarget = v;
}

// @ 0x00f988f0  SP::cTerrainSphere::RemoveDecalSegList
void __fastcall FUN_00f988f0(TerrainSphere* self, void* dummy, int id)
{
    void** p = self->mDecalBegin;
    for (int i = 0; i < (int)((char*)self->mDecalEnd - (char*)self->mDecalBegin) >> 2; ++i, ++p) {
        void* e = *p;
        if (e != 0 && *(int*)e == id) {
            ((RemoveDecalFn)(*(void***)self)[0xc0 / 4])(self, i);
            return;
        }
    }
}

// @ 0x00f992e0
void __fastcall FUN_00f992e0(TerrainSphere* self, void* dummy)
{
    char* rec = ((GetRecordFn)(*(void***)self)[0x10 / 4])(self);
    char* r = rec + 0x2f4;
    const float kDegToRad = 0.017453292f;

    float c1 = (float)cos(*(float*)(r + 0xcc) * kDegToRad);
    float c2 = (float)cos(*(float*)(r + 0xd0) * kDegToRad);
    float c3 = (float)cos(*(float*)(r + 0xd4) * kDegToRad);
    float invA = 1.0f / (c2 - c3);
    float c0 = (float)cos(*(float*)(r + 0xc8) * kDegToRad);

    float cx = self->mConeX;
    self->mCone.mConeCos = *(unsigned*)&cx;
    float invB = 1.0f / (c0 - c1);
    float cy = self->mConeY;
    self->mCone.mConeA = *(unsigned*)&cy;
    float cz = self->mConeZ;
    self->mCone.mConeB = *(unsigned*)&cz;
    self->mCone.mConeC = *(unsigned*)&c2;
    self->mCone.mConeInvB = *(unsigned*)&invB;
    self->mCone.mConeInvA = *(unsigned*)&invA;
    float nb = -(invB * c1);
    self->mCone.mConeNB = *(unsigned*)&nb;
    float na = -(invA * c3);
    self->mCone.mConeNA = *(unsigned*)&na;

    self->mCone.mBlockA[0] = *(unsigned*)(r + 0x58);
    self->mCone.mBlockA[1] = *(unsigned*)(r + 0x5c);
    self->mCone.mBlockA[2] = *(unsigned*)(r + 0x60);
    self->mCone.mBlockA[3] = *(unsigned*)(r + 0x64);
    self->mCone.mBlockB[0] = *(unsigned*)(r + 0x68);
    self->mCone.mBlockB[1] = *(unsigned*)(r + 0x6c);
    self->mCone.mBlockB[2] = *(unsigned*)(r + 0x70);
    self->mCone.mBlockB[3] = *(unsigned*)(r + 0x74);
    self->mCone.mBlockC[0] = *(unsigned*)(r + 0x78);
    self->mCone.mBlockC[1] = *(unsigned*)(r + 0x7c);
    self->mCone.mBlockC[2] = *(unsigned*)(r + 0x80);
    self->mCone.mBlockC[3] = *(unsigned*)(r + 0x84);
    self->mCone.mBlockD[0] = *(unsigned*)(r + 0x88);
    self->mCone.mBlockD[1] = *(unsigned*)(r + 0x8c);
    self->mCone.mBlockD[2] = *(unsigned*)(r + 0x90);
    self->mCone.mBlockD[3] = *(unsigned*)(r + 0x94);
    self->mCone.mBlockE[0] = *(unsigned*)(r + 0x98);
    self->mCone.mBlockE[1] = *(unsigned*)(r + 0x9c);
    self->mCone.mBlockE[2] = *(unsigned*)(r + 0xa0);
    self->mCone.mBlockE[3] = *(unsigned*)(r + 0xa4);
    self->mCone.mBlockF[0] = *(unsigned*)(r + 0xa8);
    self->mCone.mBlockF[1] = *(unsigned*)(r + 0xac);
    self->mCone.mBlockF[2] = *(unsigned*)(r + 0xb0);
    self->mCone.mBlockF[3] = *(unsigned*)(r + 0xb4);
    self->mCone.mBlockG[0] = *(unsigned*)(r + 0xb8);
    self->mCone.mBlockG[1] = *(unsigned*)(r + 0xbc);
    self->mCone.mBlockG[2] = *(unsigned*)(r + 0xc0);
    self->mCone.mBlockG[3] = *(unsigned*)(r + 0xc4);
}

// @ 0x00f99520  SP::cTerrainSphere::PinModelsToTerrain
void __fastcall FUN_00f99520(TerrainSphere* self, void* dummy)
{
    cTerrainMapSet* map = self->mMap;
    float radius = map->mRadius3c * map->mRadius38 + map->mRadius34;
    int count = (int)((char*)self->mModelsEnd - (char*)self->mModels) >> 2;

    for (int i = 0; i < count; ++i) {
        TerrainModel* m = self->mModels[i];
        if (m == 0)
            continue;
        if ((m->mFlags & 1) == 0)
            continue;

        Vec3 v;
        v.x = m->x;
        v.y = m->y;
        v.z = m->z;
        float len = (float)sqrt((double)v.x * v.x + (double)v.y * v.y + (double)v.z * v.z);

        int arg;
        if (len <= 1e-6) {
            arg = 0;
        } else {
            float h = map->GetHeightAt(&v);
            if (self->mFlag8ac == 0 && h < radius) {
                arg = 0;
            } else {
                float s = h / len;
                v.x *= s;
                v.y *= s;
                v.z *= s;
                m->x = v.x;
                m->y = v.y;
                m->z = v.z;
                m->mFlags2 |= 4;
                m->mCounter += 1;
                arg = 1;
            }
        }
        ((PinModelFn)(*(void***)m->mpObj)[0x16c / 4])(m->mpObj, m, arg);
    }
}
