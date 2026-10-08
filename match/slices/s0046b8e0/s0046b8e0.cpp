// s0046b8e0: editor model center / offset computation (0x0046b8e0, 1774 bytes, /Od /Ob1 /arch:SSE).
//
// Walks the editor model's block list. Blocks for which BlockOrAncestorHasFlag (0x0046b7b0) holds
// contribute: depending on the mode bits in `flags` either their bounding-box volume weighted
// center (modes 1..8) or the position of the lowest block carrying flag 7 (mode 0x10) is
// accumulated, together with the lowest bounding-box z. The result is a position (global zero
// vector plus the weighted center on the selected axes, lowered by the minimum z for mode 1).
#include "types.h"

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Fabs(float x) { return (float)fabs(x); }
inline float Abs(float x) { return Fabs(x); }

struct Vector3T {                                                        // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3(const cSPVector3& o);                                     // 0x004098a0
};
struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
    Vector3T* GetCenter(Vector3T* out) const;                            // 0x00409b90 (thiscall, returns out)
};

Vector3T* Vector3_Add(Vector3T* a, const Vector3T* b);                   // 0x0041ddb0 (a += b)
Vector3T* Vector3_Negate(Vector3T* out, const Vector3T* v);              // 0x00422020
Vector3T* Vector3_Div(Vector3T* out, const Vector3T* v, const float* s); // 0x00453880
Vector3T* Vector3_Scale(Vector3T* out, const Vector3T* a, const float* s); // 0x0041dca0

extern const cSPVector3 kZeroPos;                                        // 0x015d4034
extern const float kFltMax;                                              // 0x013eec70
extern const float kZero;                                                // 0x01485378
extern const float kOne;                                                 // 0x01485720

template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(unsigned i) const
    {
        uint32_t w;
        bool r;
        if (i < N) {
            w = mWord[i >> 5];
            r = (w & (1u << (i % 32))) != 0;
        } else {
            r = false;
        }
        return r;
    }
};

struct cSPEditorBlock {
    char pad0[0x48];
    cSPVector3 mPosition;                                                // +0x48
    char pad54[0xdc8 - 0x54];
    bitset<60> mFlags;                                                   // +0xdc8
    cSPBoundingBox GetBBox(int type, bool a, bool b);                    // 0x0044ae00
};

bool BlockOrAncestorHasFlag(cSPEditorBlock* b);                          // 0x0046b7b0 (cdecl)

struct cSPEditorModel {
    char pad0[0x18];
    cSPEditorBlock** mpBegin;                                            // +0x18
    cSPEditorBlock** mpEnd;
    int GetCount();                                                      // 0x004accf0
    cSPEditorBlock* GetBlock(int i);                                     // 0x004accb0
};

// @ 0x0046b8e0
extern "C" Vector3T* FUN_0046b8e0(Vector3T* out, cSPEditorModel* model, int flags)
{
    float vSum = kZero;
    cSPVector3 sumC(kZeroPos);
    float best = kFltMax;
    float lowZ = kFltMax;
    bool useAlt = false;
    float bottom2 = lowZ;
    for (int i = 0, num = model->GetCount(); i < num; i++) {
        cSPEditorBlock* block = model->GetBlock(i);
        if (BlockOrAncestorHasFlag(block)) {
            cSPBoundingBox bb = block->GetBBox(0, true, false);
            bool isD = block->mFlags.test(7);
            bool isE = block->mFlags.test(8);
            bool f0 = block->mFlags.test(0);
            bool f23 = block->mFlags.test(0x23);
            bool a = block->mFlags.test(0x2d);
            useAlt = useAlt || a;
            bool add = false;
            if (flags & 0x10) {
                if (isD) {
                    float y = block->mPosition[1];
                    if (best > y) {
                        best = y;
                        sumC = block->mPosition;
                        vSum = kOne;
                    }
                }
            } else if (flags & 0x20) {
                if (isD || isE || f23)
                    add = true;
            } else {
                add = true;
            }
            if (add) {
                float sx = Abs(bb.mMax[0] - bb.mMin[0]);
                float ly = Abs(bb.mMax[1] - bb.mMin[1]);
                float lz = Abs(bb.mMax[2] - bb.mMin[2]);
                float v = sx * ly * lz;
                vSum += v;
                                Vector3T t1, t2;
                Vector3_Add(&sumC, Vector3_Scale(&t2, bb.GetCenter(&t1), &v));
            }
            if (lowZ > bb.mMin[2])
                lowZ = bb.mMin[2];
            if (a) {
                if (bottom2 > bb.mMin[2])
                    bottom2 = bb.mMin[2];
            }
        }
    }
    cSPVector3 result((const Vector3T&)kZeroPos);
    if (vSum > kZero) {
                Vector3T t3, t4;
        cSPVector3 center(*Vector3_Div(&t3, &sumC, &vSum));
        cSPVector3 off(*Vector3_Negate(&t4, &center));
        float lift = -(useAlt ? bottom2 : lowZ);
        if ((flags & 1) && kZero >= lift)
            result[2] += lift;
        if (flags & 2)
            result[0] += off[0];
        if (flags & 4)
            result[1] += off[1];
        if (flags & 8)
            result[2] += off[2];
        if (flags & 0x10) {
            result = off;
        }
    }
    out->x = result.x;
    out->y = result.y;
    out->z = result.z;
    return out;
}

struct Tbfd {
    int m();
};

// @ 0x0046bfd0
int FUN_0046bfd0(int a, int b)
{
    FUN_0046b8e0((Vector3T*)a, (cSPEditorModel*)b, ((Tbfd*)b)->m());
    return a;
}
