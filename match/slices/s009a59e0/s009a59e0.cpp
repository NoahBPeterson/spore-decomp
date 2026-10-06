// nSPCreatureAnim::ComputeEventLocationState (0x009a59e0, 4070 bytes).
// Resolves the world-space position / second position / orientation / scalar / direction that an
// animation event refers to, for a creature (param_6) and one of its 700-byte bone records (param_7),
// or for the anim owner (param_5) when there is no creature. Offsets come from the disassembly; the
// creature / bone / owner layouts are accessed through AT() so no struct has to be guessed.
// Behavior-complete (not byte-exact): helper conventions follow the callees' real signatures.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

#define AT(T, p, off) (*(T*)((char*)(p) + (off)))

namespace EA {
template <typename T> struct RectT {
    T mLeft, mTop, mRight, mBottom;
    RectT& operator=(const RectT& o);                 // 0x00572600
    void RotA(float c, float s);                      // 0x009a4c70 (thiscall, ret 8)
    void RotB(float c, float s);                      // 0x009a4d60
    void RotC(float c, float s);                      // 0x009a4e40
};
namespace Random {
class RandomMersenneTwister { public: double GenerateDouble(); };   // 0x009362d0
}
}
extern EA::Random::RandomMersenneTwister gRandom;     // 0x0166b4b8

struct EvCallback {                                   // *(owner + 0x1688)
    char enabled; char pad[3];
    float (*fn)(int data, int ownerField4, float* pos, float* dir, int flag, int zero);   // +4
    int data;                                         // +8
};

namespace checkerlib {
float* QuaternionVectorTransform(float* out, const float* q, const float* v);          // 0x0099c1a0
float* QuaternionProduct(float* out, const float* a, const float* b);                  // 0x0099c0b0
float* QuaternionVectorTransformInverse(float* out, const float* q, const float* v);   // 0x0099c310
float* matrix_to_quaternion(float* outQ, const float* m3x3);                           // 0x009a4f10
}
float* NormalizeVec3(float* out, const float* v, float* lenOut);   // 0x009a49d0
float  LengthSqVec3(const float* v);                               // 0x009a49b0
void   PerpPair(const float* dir, float* o1, float* o2);           // 0x009a4a70

namespace nSPCreatureAnim {
uint32_t GetEventDataAs32Bits(int a0, void* a1, int a2, int a3, void* creature, uint32_t index,
                              float defaultValue, int a7);         // 0x009a5860 (result is float bits)

static inline void Unit(float* d) { d[0] = 0.0f; d[1] = 0.0f; d[2] = 1.0f; }

// @ 0x009a59e0
bool ComputeEventLocationState(char randomize, int evData, uint32_t flags, int p4, char* owner,
                               char* cr, uint32_t boneIdx, float* pos, float* pos2,
                               EA::RectT<float>* outQuat, float* outScalar, float* outVec,
                               float* dirIn, float* dirIn2, int p15)
{
    char* bone;
    if (cr == 0 || (uint32_t)(((int)(AT(char*, cr, 0x2e8) - AT(char*, cr, 0x2e4))) / 700) <= boneIdx)
        bone = 0;
    else
        bone = AT(char*, cr, 0x2e4) + boneIdx * 700;

    EvCallback* cb = AT(EvCallback*, owner, 0x1688);
    float dirA[3];      // local_94
    float dirB[3];      // local_c8
    float tmp[3];
    float tq[4];

    // ---- scalar output ------------------------------------------------------------------
    if (outScalar) {
        uint32_t k = flags & 0x8180;
        if (k > 0x100) {
            if (k == 0x180) {
                *outScalar = AT(float, owner, 0x70);
            } else if (k == 0x8000) {
                if (bone == 0) {
                    if (cr)
                        *outScalar = AT(float, AT(char*, cr, 0), 0x370) * AT(float, cr, 0x70);
                    else
                        *outScalar = 1.0f;
                } else {
                    char* m = AT(char*, bone, 0);
                    float s = AT(float, cr, 0x70);
                    float vx = s * AT(float, m, 0x138);
                    float vy = AT(float, m, 0x13c) * s;
                    float vz = AT(float, m, 0x140) * s;
                    float len = sqrtf(vx * vx + (vz * vz + vy * vy));
                    *outScalar = len + len;
                }
            } else {
                *outScalar = 1.0f;
            }
        } else if (k == 0x100) {
            uint32_t bits = GetEventDataAs32Bits(evData, &p4, 0, 0, cr, boneIdx, 1.0f, p15);
            *(uint32_t*)outScalar = bits;
        } else if (k == 0 || k != 0x80) {
            *outScalar = 1.0f;
        } else {
            if (cr) *outScalar = AT(float, cr, 0x70);
            else    *outScalar = 1.0f;
        }
    }

    // ---- position / second position / orientation ---------------------------------------
    if (cr != 0) {
        if ((flags & 0xf) - 1 > 7) return false;
        if (bone == 0) {
            if (pos) {
                pos[0] = AT(float, cr, 0x18);
                pos[1] = AT(float, cr, 0x1c);
                pos[2] = AT(float, cr, 0x20);
            }
            if (pos2) {
                pos2[0] = AT(float, cr, 0x74);
                pos2[1] = AT(float, cr, 0x78);
                pos2[2] = AT(float, cr, 0x7c);
            }
            if (outQuat) *outQuat = AT(EA::RectT<float>, cr, 0x3c);
        } else {
            if (pos) {
                float* r = checkerlib::QuaternionVectorTransform(tq, (float*)(cr + 0x3c), (float*)(bone + 0x10));
                float x = AT(float, cr, 0x18), y = AT(float, cr, 0x1c), z = AT(float, cr, 0x20);
                pos[0] = x + r[0];
                pos[1] = y + r[1];
                pos[2] = z + r[2];
            }
            if (pos2) {
                float* r = checkerlib::QuaternionVectorTransform(tq, (float*)(cr + 0x3c), (float*)(bone + 0x2c));
                float x = AT(float, cr, 0x74), y = AT(float, cr, 0x78), z = AT(float, cr, 0x7c);
                pos2[0] = x + r[0];
                pos2[1] = y + r[1];
                pos2[2] = z + r[2];
            }
            if (outQuat) {
                float* q = checkerlib::QuaternionProduct(tq, (float*)(cr + 0x3c), (float*)(bone + 0x1c));
                *outQuat = *(EA::RectT<float>*)q;
            }
        }
    } else {
        switch (flags & 0xf) {
        case 0:
        case 9:
            if (pos) { pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 0.0f; }
            if (pos2) { pos2[0] = 0.0f; pos2[1] = 0.0f; pos2[2] = 0.0f; }
            if (outQuat) {
                outQuat->mLeft = 0.0f; outQuat->mTop = 0.0f; outQuat->mRight = 0.0f; outQuat->mBottom = 1.0f;
            }
            break;
        default:
            return false;
        case 5: case 6: case 7: case 8:
            if (AT(int, owner, 0x274) == 0) {
                if (pos) {
                    float* r = checkerlib::QuaternionVectorTransform(tq, (float*)(owner + 0x3c), (float*)(owner + 0x278));
                    float y = AT(float, owner, 0x1c), z = AT(float, owner, 0x20);
                    pos[0] = r[0] + AT(float, owner, 0x18);
                    pos[1] = r[1] + y;
                    pos[2] = r[2] + z;
                }
                if (outQuat) {
                    float* q = checkerlib::QuaternionProduct(tq, (float*)(owner + 0x3c), (float*)(owner + 0x284));
                    *outQuat = *(EA::RectT<float>*)q;
                }
            } else {
                if (AT(int, owner, 0x274) != 1) return false;
                if (pos) {
                    pos[0] = AT(float, owner, 0x278);
                    pos[1] = AT(float, owner, 0x27c);
                    pos[2] = AT(float, owner, 0x280);
                }
                if (outQuat) *outQuat = AT(EA::RectT<float>, owner, 0x284);
            }
            if (pos2) { pos2[0] = 0.0f; pos2[1] = 0.0f; pos2[2] = 0.0f; }
        }
    }

    // ---- event offset applied to pos ------------------------------------------------------
    bool usedCb = false;
    if (pos) {
        uint32_t k = flags & 0x22000;
        if (k == 0x2000) {
            if (cr) {
                float s = AT(float, cr, 0x70);
                float* r;
                if (bone == 0) {
                    char* m = AT(char*, cr, 0);
                    float f1 = AT(float, m, 0x35c) * s;
                    float f2 = AT(float, m, 0x360) * s;
                    float f0 = s * AT(float, m, 0x358);
                    tmp[0] = ((AT(float, m, 0x364) * s + f0) + f0) * 0.5f;
                    tmp[1] = ((AT(float, m, 0x368) * s + f1) + f1) * 0.5f;
                    tmp[2] = ((AT(float, m, 0x36c) * s + f2) + f2) * 0.5f;
                    r = checkerlib::QuaternionVectorTransform(tq, (float*)(cr + 0x3c), tmp);
                } else {
                    char* m = AT(char*, bone, 0);
                    tmp[0] = s * AT(float, m, 0x144);
                    tmp[1] = AT(float, m, 0x148) * s;
                    tmp[2] = AT(float, m, 0x14c) * s;
                    float qb[4];
                    float* q = checkerlib::QuaternionProduct(qb, (float*)(cr + 0x3c), (float*)(bone + 0x1c));
                    r = checkerlib::QuaternionVectorTransform(tq, q, tmp);
                }
                pos[0] = r[0] + pos[0];
                pos[1] = r[1] + pos[1];
                pos[2] = r[2] + pos[2];
            }
        } else if (k == 0x20000) {
            if (outVec && cr) {
                float rnd[3];
                float* src = outVec;
                if (randomize) {
                    double a = gRandom.GenerateDouble();
                    double b = gRandom.GenerateDouble();
                    float c = (float)gRandom.GenerateDouble();
                    rnd[0] = c;
                    rnd[1] = (float)b;
                    rnd[2] = (float)a;
                    src = rnd;
                }
                float x = src[0], y = src[1], z = src[2];
                float* r;
                if (bone == 0) {
                    if (randomize) {
                        char* m = AT(char*, cr, 0);
                        float s = AT(float, cr, 0x70);
                        x = (s * AT(float, m, 0x364)) * x;
                        y = (AT(float, m, 0x368) * s) * y;
                        z = (AT(float, m, 0x36c) * s) * z;
                        outVec[0] = x; outVec[1] = y; outVec[2] = z;
                    }
                    float s = AT(float, cr, 0x70);
                    char* m = AT(char*, cr, 0);
                    tmp[0] = s * AT(float, m, 0x358) + x;
                    tmp[1] = AT(float, m, 0x35c) * s + y;
                    tmp[2] = AT(float, m, 0x360) * s + z;
                    r = checkerlib::QuaternionVectorTransform(tq, (float*)(cr + 0x3c), tmp);
                } else {
                    if (randomize) {
                        float s = AT(float, cr, 0x70);
                        char* m = AT(char*, bone, 0);
                        x = (x * 2.0f - 1.0f) * (AT(float, m, 0x138) * s);
                        y = (y * 2.0f - 1.0f) * (AT(float, m, 0x13c) * s);
                        z = (z * 2.0f - 1.0f) * (AT(float, m, 0x140) * s);
                        outVec[0] = x; outVec[1] = y; outVec[2] = z;
                    }
                    tmp[0] = x; tmp[1] = y; tmp[2] = z;
                    r = checkerlib::QuaternionVectorTransform(tq, (float*)(bone + 0x1c), tmp);
                }
                pos[0] = r[0] + pos[0];
                pos[1] = r[1] + pos[1];
                pos[2] = r[2] + pos[2];
            }
        } else if (k == 0x22000 && cr && bone) {
            char* m = AT(char*, bone, 0);
            float s = AT(float, cr, 0x70);
            tmp[0] = AT(float, m, 0x330) * s;
            tmp[1] = AT(float, m, 0x334) * s;
            tmp[2] = AT(float, m, 0x338) * s;
            float qb[4];
            float* q = checkerlib::QuaternionProduct(qb, (float*)(cr + 0x3c), (float*)(bone + 0x1c));
            float* r = checkerlib::QuaternionVectorTransform(tq, q, tmp);
            pos[0] = r[0] + pos[0];
            pos[1] = r[1] + pos[1];
            pos[2] = r[2] + pos[2];
        }

        // ---- absolute / relative / callback handling ----
        uint32_t k2 = flags & 0x11000;
        int flagByte = 0;
        bool doCb = false;
        if (k2 == 0x1000) {
            doCb = true;
        } else if (k2 == 0x10000) {
            flagByte = 1;
            doCb = true;
        } else if (k2 == 0x11000 && cr) {
            float ox = pos[0], oy = pos[1], oz = pos[2];
            tmp[0] = ox - AT(float, cr, 0x18);
            tmp[1] = oy - AT(float, cr, 0x1c);
            tmp[2] = oz - AT(float, cr, 0x20);
            float t[4];
            checkerlib::QuaternionVectorTransformInverse(t, (float*)(cr + 0x3c), tmp);
            float q1 = AT(float, cr, 0x40);
            float q0 = AT(float, cr, 0x3c);
            float q3 = AT(float, cr, 0x48);
            float q2 = AT(float, cr, 0x44);
            float s = AT(float, cr, 0x70);
            char* m = AT(char*, cr, 0);
            float d = (AT(float, m, 0x36c) * s + AT(float, m, 0x360) * s) - t[2];
            pos[0] = ((q0 * q2 + q1 * q3) * 2.0f) * d + ox;
            pos[1] = ((q2 * q1 - q0 * q3) * 2.0f) * d + oy;
            pos[2] = (1.0f - (q0 * q0 + q1 * q1) * 2.0f) * d + oz;
        }
        if (doCb) {
            if (cb == 0 || cb->fn == 0) {
                Unit(dirA);
                Unit(dirB);
                pos[2] = 0.0f;
            } else {
                usedCb = true;
                float r = cb->fn(cb->data, AT(int, owner, 4), pos, dirA, flagByte, 0);
                if (cb->enabled == 0) {
                    Unit(dirB);
                    pos[2] = r;
                } else {
                    float* n = NormalizeVec3(tq, pos, 0);
                    dirB[0] = n[0]; dirB[1] = n[1]; dirB[2] = n[2];
                    pos[0] = n[0] * r;
                    pos[1] = n[1] * r;
                    pos[2] = n[2] * r;
                }
            }
        }
    }

    // ---- orientation output ---------------------------------------------------------------
    if (outQuat == 0) return true;
    {
        uint32_t k = flags & 0xe00;
        float m[9];
        float o1[3], o2[3];
        bool haveMat = false;
        if (k == 0x600) {
            if (!usedCb) {
                if (cb == 0 || cb->fn == 0 || cb->enabled == 0) {
                    Unit(dirB);
                } else {
                    float* n = NormalizeVec3(tq, dirIn, 0);
                    dirB[0] = n[0]; dirB[1] = n[1]; dirB[2] = n[2];
                }
            }
            o1[0] = o1[1] = o1[2] = 0.0f;
            o2[0] = o2[1] = o2[2] = 0.0f;
            PerpPair(dirB, o1, o2);
            m[0] = o1[0]; m[1] = o2[0]; m[2] = dirB[0];
            m[3] = o1[1]; m[4] = o2[1]; m[5] = dirB[1];
            m[6] = o1[2]; m[7] = o2[2]; m[8] = dirB[2];
            haveMat = true;
        } else if (k == 0x200) {
            o1[0] = o1[1] = o1[2] = 0.0f;
            o2[0] = o2[1] = o2[2] = 0.0f;
            if (LengthSqVec3(dirIn2) >= 1e-06f) {
                float* n = NormalizeVec3(tq, dirIn2, 0);
                dirB[0] = n[0]; dirB[1] = n[1]; dirB[2] = n[2];
            } else {
                float x = outQuat->mLeft, z = outQuat->mRight;
                dirB[2] = -((z * outQuat->mTop + x * outQuat->mBottom) * 2.0f);
                dirB[1] = -(1.0f - (x * x + z * z) * 2.0f);
                dirB[0] = -((x * outQuat->mTop - z * outQuat->mBottom) * 2.0f);
            }
            PerpPair(dirB, o1, o2);
            m[0] = o1[0]; m[1] = o2[0]; m[2] = dirB[0];
            m[3] = o1[1]; m[4] = o2[1]; m[5] = dirB[1];
            m[6] = o1[2]; m[7] = o2[2]; m[8] = dirB[2];
            haveMat = true;
        } else if (k == 0x400) {
            if (cr) {
                *outQuat = AT(EA::RectT<float>, cr, 0x3c);
            }
        } else if (k == 0x800) {
            if (!usedCb) {
                if (cb == 0 || cb->fn == 0) {
                    Unit(dirA);
                } else {
                    cb->fn(cb->data, AT(int, owner, 4), dirIn, dirA, (flags & 0x11000) == 0x10000, 0);
                }
            }
            o1[0] = o1[1] = o1[2] = 0.0f;
            o2[0] = o2[1] = o2[2] = 0.0f;
            PerpPair(dirA, o1, o2);
            m[0] = o1[0]; m[1] = o2[0]; m[2] = dirA[0];
            m[3] = o1[1]; m[4] = o2[1]; m[5] = dirA[1];
            m[6] = o1[2]; m[7] = o2[2]; m[8] = dirA[2];
            haveMat = true;
        } else if (k == 0xa00) {
            outQuat->mLeft = 0.0f; outQuat->mTop = 0.0f; outQuat->mRight = 0.0f; outQuat->mBottom = 1.0f;
        }
        if (haveMat) {
            float* q = checkerlib::matrix_to_quaternion(tq, m);
            *outQuat = *(EA::RectT<float>*)q;
        }
    }

    // ---- bone-driven rotation of the result -------------------------------------------------
    if (bone != 0 && 0.0f < AT(float, AT(char*, bone, 0), 0x10c)) {
        uint32_t k = flags & 0x70000000;
        if (k == 0x10000000)      outQuat->RotA(0.0f, 1.0f);
        else if (k == 0x20000000) outQuat->RotB(0.0f, 1.0f);
        else if (k == 0x30000000) outQuat->RotC(0.0f, 1.0f);
    }
    return true;
}
}
