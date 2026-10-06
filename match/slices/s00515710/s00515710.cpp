// Slice s00515710 -- nSPSkinner::cPaintVarEvalList::Apply (0x00515710, 4792 bytes).
//
// Name and signature from the dev-build PDB (SPSkinnerPaintEval.obj):
//   ?Apply@cPaintVarEvalList@nSPSkinner@@QBEXQAMMABUcSPVector3@@1I@Z
//   void cPaintVarEvalList::Apply(float* const values, float age, const cSPVector3& pos,
//                                 const cSPVector3& norm, unsigned int vertIdx) const
// Local names follow the dev twin's S_REGREL32 records (itVar, pPaintSystem, modValue,
// scaledPos, currentModifier, value, dotX, dotZ, curve, scaleNorm, offset, scalePos, vary, x,
// valueWidth, t, intpart).
//
// For every entry of the eval list it evaluates the entry's variable modifier (age, random,
// world angle/position/distance, bone angle/position/offset, torso/limb position, limb type,
// region, paint mask, another variable, or a curve-sampled "compat" modifier), maps the modifier
// value from [mRangeMin, mRangeMax] to [mValueMin, mValueMax] according to the edge mode
// (clip / half-open / clamp / repeat / mirror) and applies it (set, add, multiply, divide) to
// values[mVariable]. Finally four of the variables are clamped to [0, 1].
//
// Retail layout: eastl::vector is 0x14 bytes, so mEntries is at +0x14 and mCurveData at +0x28;
// cMesh::mBounds is at +0x14c and mUserData_V at +0x1a4.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// What the out-of-line vector operators return; locals copy it member-wise (inline, movss).
struct cSPVector3R {
    float x, y, z;
    cSPVector3R() {}
};

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3R& o) : x(o.x), y(o.y), z(o.z) {}
    cSPVector3(float a, float b, float c);                 // 0x00436ca0
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};

// Vector flavour with an out-of-line copy (0x004098a0, ICF-shared with cSPVector3's copy ctor).
struct cSPVector3C {
    float x, y, z;
    cSPVector3C(const cSPVector3R& o);                      // 0x004098a0
};

struct cSPMatrix3 {
    cSPVector3 mRows[3];
    const cSPVector3& operator[](int i) const { return mRows[i]; }
};

struct cSPBoundingBox {
    cSPVector3 mMin;  // +0x0
    cSPVector3 mMax;  // +0xc
};

cSPVector3R operator-(const cSPVector3& a, const cSPVector3& b);         // 0x0041db10
cSPVector3R operator*(const cSPVector3& v, const cSPMatrix3& m);         // 0x0041daf0
cSPVector3R operator*(const cSPVector3& a, const cSPVector3& b);         // 0x004fc510 (per component)

namespace SP {
inline float dot(const cSPVector3& a, const cSPVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
float len(const cSPVector3& v);                                          // 0x0040ae50

// maxss/minss clamp to [0, 1] (an __asm helper in the original).
inline float clamp_unit(float x)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        minss xmm0, one
        movss x, xmm0
    }
    return x;
}
}

#include <math.h>

extern float kSPPi;                                                      // 0x015dd948
extern float kSPMaxFloat;                                                // 0x013f199c

namespace eastl {
struct sp_vector_allocator { uint32_t a, b; };
template <typename T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    const T* begin() const { return mpBegin; }
    const T* end() const { return mpEnd; }
    T* data() { return mpBegin; }
    const T& operator[](unsigned int n) const { return mpBegin[n]; }
    T& operator[](unsigned int n) { return mpBegin[n]; }
};
}

namespace nSPSkinner {

namespace MathHelp {
float FastAcos(float x);                                                 // 0x00513930
float fractionalmod_f(float x, float* intpart);                          // 0x004fa520
}

// cMeshPosition-style table sampler: linear interpolation into n samples, t in [0, 1].
float SampleCurve(const float* values, int n, float t);                  // 0x00516a20

struct cCreatureBone {
    char mParent;           // +0x0
    char mSpine;            // +0x1
    char mNumChildren;      // +0x2
    char mEndType;          // +0x3
    cSPVector3 mPos;        // +0x4
    cSPMatrix3 mRot;        // +0x10
    float mLength;          // +0x34
    float mLimbPosBegin;    // +0x38
    float mLimbPosEnd;      // +0x3c
};

struct cMesh {
    uint32_t pad0[0x14c / 4];
    cSPBoundingBox mBounds;                                // +0x14c
    uint32_t pad164[(0x1a4 - 0x164) / 4];
    eastl::vector<unsigned int> mUserData_V;               // +0x1a4
};

template <typename T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
};

class cPaintSystem {
public:
    uint32_t pad0[0x10 / 4];
    AutoRefCount<cMesh> mpBakedMesh;                       // +0x10

    float NextRandomUnitFloat();                           // 0x005169d0
    const cCreatureBone* GetBone(int i) const;             // 0x005247b0
    const cCreatureBone* GetBoneFromVertex(int vert) const;// 0x005247d0
};

enum tPaintVarModifiers {
    kPaintVarModAge = 0,
    kPaintVarModRandom = 1,
    kPaintVarModWorldAngle = 2,
    kPaintVarModWorldPos = 3,
    kPaintVarModWorldDist = 4,
    kPaintVarModBoneAngle = 5,
    kPaintVarModBonePos = 6,
    kPaintVarModBoneOffset = 7,
    kPaintVarModTorsoPos = 8,
    kPaintVarModLimbPos = 9,
    kPaintVarModLimbType = 10,
    kPaintVarModRegion = 11,
    kPaintVarModPaintMask = 12,
    kPaintVarModVariable = 13,
    kPaintVarModMax = 14,
    kPaintVarModCompatNorm = 253,
    kPaintVarModCompatPos = 254,
    kPaintVarModCompat = 255,
};

struct cPaintVarEvalList {
    struct Entry {
        float mRangeMin;            // +0x0
        float mRangeMax;            // +0x4
        float mValueMin;            // +0x8
        float mValueMax;            // +0xc
        unsigned char mVariable;    // +0x10
        unsigned char mVarModIdx;   // +0x11
        unsigned char mApplyMode;   // +0x12
        unsigned char mEdgeMode;    // +0x13
    };
    struct Modifier {
        cSPVector3 mVec;            // +0x0
        unsigned char mModType;     // +0xc
        unsigned char mVariable;    // +0xd
        unsigned short mCurveBegin; // +0xe
    };

    eastl::vector<Modifier> mModifiers;     // +0x00
    eastl::vector<Entry> mEntries;          // +0x14
    eastl::vector<float> mCurveData;        // +0x28

    void Apply(float* const values, float age, const cSPVector3& pos, const cSPVector3& norm,
               unsigned int vertIdx) const;
};

cPaintSystem* SkinPaintSystem();                                         // 0x00401080

// @ 0x00515710
void cPaintVarEvalList::Apply(float* const values, float age, const cSPVector3& pos,
                              const cSPVector3& norm, unsigned int vertIdx) const
{
    cPaintSystem* pPaintSystem = SkinPaintSystem();
    const cSPBoundingBox& bounds = pPaintSystem->mpBakedMesh->mBounds;
    cSPVector3 rel = pos - bounds.mMin;
    cSPVector3C size = bounds.mMax - bounds.mMin;
    cSPVector3 scaledPos(rel.x / size.x, rel.y / size.y, rel.z / size.z);
    const unsigned int* userData = pPaintSystem->mpBakedMesh->mUserData_V.data();
    unsigned int currentModifier = 0xff;
    float modValue = 0.0f;

    for (const Entry *itVar = mEntries.begin(), *itVarEnd = mEntries.end(); itVar != itVarEnd; ++itVar) {
        float value = itVar->mValueMin;
        if (itVar->mVarModIdx != 0xff) {
            const Modifier& mod = mModifiers[itVar->mVarModIdx];
            if (currentModifier != itVar->mVarModIdx) {
                currentModifier = itVar->mVarModIdx;
                switch (mod.mModType) {
                case kPaintVarModAge:
                    modValue = age;
                    break;
                case kPaintVarModRandom:
                    modValue = pPaintSystem->NextRandomUnitFloat();
                    break;
                case kPaintVarModWorldAngle:
                    modValue = MathHelp::FastAcos(SP::dot(mod.mVec, norm)) * (180.0f / kSPPi);
                    break;
                case kPaintVarModWorldPos:
                    modValue = SP::dot(mod.mVec, scaledPos);
                    break;
                case kPaintVarModWorldDist: {
                    cSPVector3 d = mod.mVec - scaledPos;
                    modValue = SP::len(d);
                    break;
                }
                case kPaintVarModBoneAngle: {
                    modValue = -1.0f;
                    const cCreatureBone* bone = pPaintSystem->GetBoneFromVertex(vertIdx);
                    if (bone) {
                        cSPVector3 dir = mod.mVec * bone->mRot;
                        modValue = MathHelp::FastAcos(SP::dot(dir, norm)) * (180.0f / kSPPi);
                    }
                    break;
                }
                case kPaintVarModBonePos: {
                    modValue = -1.0f;
                    const cCreatureBone* bone = pPaintSystem->GetBoneFromVertex(vertIdx);
                    if (bone && bone->mNumChildren != -1) {
                        cSPVector3 d = bone->mPos - pos;
                        modValue = SP::clamp_unit(SP::dot(d, bone->mRot[1]) / bone->mLength);
                    }
                    break;
                }
                case kPaintVarModBoneOffset: {
                    modValue = -1.0f;
                    const cCreatureBone* bone = pPaintSystem->GetBoneFromVertex(vertIdx);
                    if (bone) {
                        cSPVector3 offset = pos - bone->mPos;
                        float dotZ = SP::dot(offset, bone->mRot[2]);
                        float dotX = SP::dot(offset, bone->mRot[0]);
                        float scale = sqrtf(1.0f / (dotX * dotX + (dotZ * dotZ + 1e-8f)));
                        modValue = MathHelp::FastAcos(dotZ * scale);
                    }
                    break;
                }
                case kPaintVarModTorsoPos: {
                    modValue = 0.0f;
                    const cCreatureBone* bone = pPaintSystem->GetBoneFromVertex(vertIdx);
                    if (bone && bone->mSpine != -1) {
                        const cCreatureBone* spine = pPaintSystem->GetBone(bone->mSpine);
                        if (spine->mLimbPosBegin + spine->mLimbPosEnd > 1.0f)
                            modValue = spine->mLimbPosEnd;
                        else
                            modValue = spine->mLimbPosBegin;
                    }
                    break;
                }
                case kPaintVarModLimbPos: {
                    modValue = -1.0f;
                    const cCreatureBone* bone = pPaintSystem->GetBoneFromVertex(vertIdx);
                    if (bone && bone->mNumChildren != -1) {
                        cSPVector3 d = bone->mPos - pos;
                        modValue = SP::clamp_unit(SP::dot(d, bone->mRot[1]) / bone->mLength);
                        float a = bone->mLimbPosBegin;
                        float delta = bone->mLimbPosEnd - a;
                        delta *= modValue;
                        modValue = a + delta;
                    }
                    break;
                }
                case kPaintVarModLimbType: {
                    modValue = -1.0f;
                    const cCreatureBone* bone = pPaintSystem->GetBoneFromVertex(vertIdx);
                    if (bone) {
                        switch (bone->mEndType) {
                        case 1: modValue = 0.0f; break;
                        case 2: modValue = 1.0f; break;
                        case 3: modValue = 0.5f; break;
                        }
                    }
                    break;
                }
                case kPaintVarModVariable:
                    modValue = (values[mod.mVariable] - mod.mVec[0]) * mod.mVec[1];
                    break;
                case kPaintVarModRegion: {
                    unsigned int region = pPaintSystem->mpBakedMesh->mUserData_V[vertIdx];
                    if (region & 1)
                        modValue = 0.0f;
                    else if (region & 2)
                        modValue = 1.0f;
                    else
                        modValue = 2.0f;
                    break;
                }
                case kPaintVarModPaintMask:
                    if (pPaintSystem->mpBakedMesh->mUserData_V[vertIdx] & 4)
                        modValue = 0.0f;
                    else
                        modValue = 2.0f;
                    break;
                case kPaintVarModCompat:
                    break;
                default:
                    modValue = 0.5f;
                    break;
                }
            }

            if (mod.mModType == kPaintVarModCompat) {
                // legacy curve modifier: sample the curve, randomize it, fade it by the normal
                // angle (modifier 0) and by the distance to a point (modifier 1)
                const float* pCurve = &mCurveData[mod.mCurveBegin];
                float curve = SampleCurve(pCurve, mod.mVariable, age);
                float vary = (1.0f - mod.mVec[0]) + 2.0f * mod.mVec[0] * pPaintSystem->NextRandomUnitFloat();
                float offset = (mod.mVec[2] - mod.mVec[1]) * pPaintSystem->NextRandomUnitFloat() + mod.mVec[1];
                float scaleNorm = 1.0f;
                float scalePos = 1.0f;
                if (itVar->mRangeMin > 0.0f) {
                    float x = mCurveData[mModifiers[0].mCurveBegin + 1]
                              - MathHelp::FastAcos(SP::dot(mModifiers[0].mVec, norm)) * (180.0f / kSPPi);
                    float range = mCurveData[mModifiers[0].mCurveBegin + 1] - mCurveData[mModifiers[0].mCurveBegin];
                    if (range == 0.0f)
                        range = 1e-8f;
                    scaleNorm = SP::clamp_unit(x / range);
                }
                if (itVar->mRangeMax > 0.0f) {
                    const cSPVector3& scale = *(const cSPVector3*)&mCurveData[mModifiers[1].mCurveBegin];
                    cSPVector3 d = mModifiers[1].mVec - scaledPos;
                    cSPVector3 scaled = d * scale;
                    scalePos = SP::clamp_unit(1.0f - SP::len(scaled));
                }
                if (itVar->mApplyMode == 0)
                    value = (values[itVar->mVariable] * curve * vary + offset) * scaleNorm * scalePos;
                else
                    value = (curve * vary + offset) * scaleNorm * scalePos;
            } else {
                int edgeMode = itVar->mEdgeMode;
                if (edgeMode == 0) {
                    if (itVar->mRangeMin > modValue || modValue > itVar->mRangeMax)
                        continue;
                } else if (edgeMode == 1) {
                    if (itVar->mRangeMin > modValue || modValue >= itVar->mRangeMax)
                        continue;
                } else if (edgeMode < 5) {
                    if (itVar->mRangeMin > modValue)
                        continue;
                } else {
                    edgeMode -= 3;
                }
                float rangeWidth = itVar->mRangeMax - itVar->mRangeMin;
                float valueWidth = itVar->mValueMax - itVar->mValueMin;
                if (rangeWidth != 0.0f && valueWidth != 0.0f) {
                    float t = (modValue - itVar->mRangeMin) / rangeWidth;
                    if (edgeMode == 2) {
                        t = SP::clamp_unit(t);
                    } else if (edgeMode > 2) {
                        float intpart;
                        t = MathHelp::fractionalmod_f(t, &intpart);
                        if (edgeMode == 4 && ((int)intpart & 1))
                            t = 1.0f - t;
                    }
                    value += t * valueWidth;
                }
            }
        }

        if (itVar->mApplyMode == 0)
            values[itVar->mVariable] = value;
        else if (itVar->mApplyMode == 1)
            values[itVar->mVariable] = values[itVar->mVariable] + value;
        else if (itVar->mApplyMode == 2)
            values[itVar->mVariable] = values[itVar->mVariable] * value;
        else if (value == 0.0f)
            values[itVar->mVariable] = kSPMaxFloat;
        else
            values[itVar->mVariable] = values[itVar->mVariable] / value;
    }

    values[6] = SP::clamp_unit(values[6]);
    values[10] = SP::clamp_unit(values[10]);
    values[14] = SP::clamp_unit(values[14]);
    values[12] = SP::clamp_unit(values[12]);
}

}  // namespace nSPSkinner
