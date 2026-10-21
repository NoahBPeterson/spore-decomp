// Slice s00f559e0 -- SPEngine/SPAppCloudDescription.obj, the ArgScript cloud command family.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };

extern "C" void* __cdecl memcpy(void* dst, const void* src, size_t n);                    // 0x011e0744
extern "C" __declspec(dllimport) char* __cdecl strstr(const char* s, const char* pat);    // 0x013cc538

extern float DAT_016c9230;      // 0x016c9230
extern Vec3  DAT_016c9234;      // 0x016c9234  default gravity / default wiggle direction
extern float DAT_016c92b8;      // 0x016c92b8
extern float DAT_016c92cc;      // 0x016c92cc
extern float DAT_01677840[];    // 0x01677840  16 x { float, float } table

inline void* operator new(size_t, void* p) throw() { return p; }

namespace EA {
namespace ArgScript {

#define PV(n) virtual void pv##n();
class cIParser { public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual float GetFloat(const char* text);              // +0x98
    PV(39) PV(40) PV(41)
    virtual Vec3 GetVector(const char* text);              // +0xa8
};
#undef PV

class cArguments { public:
    const char** MainArguments(int* count, int minCount, int maxCount);                  // 0x00838020
    void         MainArguments(int count);                                               // 0x00838320
    const char** OptionArguments(const char* name, int count);                           // 0x00838330
    const char** OptionArguments(const char* name, int* count, int minCount, int maxCount); // 0x00838130
    bool         HasFlag(const char* flag);                                              // 0x008380b0
    const char*  operator[](int index);                                                  // 0x00837f20
};

class cICommand { public: virtual void AddRef(); virtual void Release(); virtual void Cast(); };
class cCommandBase : public cICommand { public:
    cIParser* mParser;      // +0x4
    int       mRefCount;    // +0x8
};

}  // namespace ArgScript
}  // namespace EA

namespace EA {
namespace Swarm {
float __cdecl ParseRangedFloat(EA::ArgScript::cIParser* parser, const char* text, float lo, float hi);  // 0x00840d50
}  // namespace Swarm
}  // namespace EA

namespace SP {
template <class T> struct SimpleVector {                        // eastl::vector<T, sp_vector_allocator>
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];

    void DoInsertValue(T* pos, const T& value);                  // 0x00455660
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* first, T* last) {
        memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd = mpEnd - (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

template <class T> struct KeyVector {                            // out-of-line push_back
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];

    void push_back(const T& value);                              // 0x00a9a7a0
};
}  // namespace SP

struct WiggleKey { float f0, f1, f2, f3, f4, f5, f6; };          // 0x1c bytes

struct cCloudState {
    char     pad00[0x10];
    uint32_t mFlags;                       // +0x10
    char     pad14[0x8c - 0x14];
    SP::SimpleVector<float> mAspectCurve;  // +0x8c
    float    mAspectVary;                  // +0xa0
    SP::SimpleVector<float> mRotationCurve;// +0xa4
    float    mRotationVary;                // +0xb8
    SP::SimpleVector<float> mColorCurve;   // +0xbc
    float    mColorVary;                   // +0xd0
    float    mColorOffset;                 // +0xd4
    char     padD8[0xf8 - 0xd8];
    SP::SimpleVector<float> mSizeCurve;    // +0xf8
    float    mSizeVary;                    // +0x10c
    char     pad110[0x13c - 0x110];
    Vec3     mGravity;                     // +0x13c
    float    mWorldWind;                   // +0x148
    float    mWorldGravity;                // +0x14c
    float    mBombForce;                   // +0x150
    Vec3     mBombOffset;                  // +0x154
    float    mDrag;                        // +0x160
    char     pad164[0x168 - 0x164];
    float    mScrewRate;                   // +0x168
    SP::KeyVector<WiggleKey> mWiggle;      // +0x16c
    uint8_t  mBloomA1;                     // +0x180
    uint8_t  mBloomA0;                     // +0x181
    uint8_t  mBloomS1;                     // +0x182
    uint8_t  mBloomS0;                     // +0x183
    uint8_t  mBloomRev;                    // +0x184
    char     pad185[0x200 - 0x185];
    float    mDelayMin;                    // +0x200
    float    mDelayMax;                    // +0x204
    float    mStrengthMin;                 // +0x208
    float    mStrengthMax;                 // +0x20c
    float    mTurnMin;                     // +0x210
    float    mTurnMax;                     // +0x214
    float    mMix;                         // +0x218
    SP::SimpleVector<float> mWalkCurve;    // +0x21c
    uint8_t  mWalkMode;                    // +0x230
    char     pad231[0x234 - 0x231];
    Vec3     mAttractor;                   // +0x234
    SP::SimpleVector<float> mAttractorCurve; // +0x240
    float    mAttractorVary;               // +0x254
    float    mKillRange;                   // +0x258
};

namespace {

struct cCloudSizeCommand : EA::ArgScript::cCommandBase {
    cCloudState* mState;                   // +0xc
    void Execute(EA::ArgScript::cArguments& args);
};

struct cCloudAspectCommand : EA::ArgScript::cCommandBase {
    cCloudState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};

struct cCloudRotateCommand : EA::ArgScript::cCommandBase {
    cCloudState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};

struct cCloudColorCommand : EA::ArgScript::cCommandBase {
    cCloudState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};

struct cCloudForceCommand : EA::ArgScript::cCommandBase {
    cCloudState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};

struct cCloudWarpCommand : EA::ArgScript::cCommandBase {
    cCloudState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};

struct cCloudWalkCommand : EA::ArgScript::cCommandBase {
    cCloudState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};

}  // namespace

using EA::ArgScript::cArguments;
using EA::Swarm::ParseRangedFloat;

// @ 0x00f559e0
void cCloudSizeCommand::Execute(cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mSizeCurve.clear();
    for (int i = 0; i < count; ++i)
        mState->mSizeCurve.push_back(mParser->GetFloat(argv[i]));
    const char** opt = args.OptionArguments("vary", 1);
    if (opt)
        mState->mSizeVary = ParseRangedFloat(mParser, opt[0], 0.0f, 1.0f);
    const char* arg0 = args[0];
    if (strstr(arg0, "255")) {
        SP::SimpleVector<float>* v = &mState->mSizeCurve;
        for (uint32_t i = 0; i < v->size(); ++i)
            v->mpBegin[i] *= 0.00392156862745098f;
    }
}

// @ 0x00f55b50
void cCloudAspectCommand::Execute(cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mAspectCurve.clear();
    for (int i = 0; i < count; ++i)
        mState->mAspectCurve.push_back(mParser->GetFloat(argv[i]));
    const char** opt = args.OptionArguments("vary", 1);
    if (opt)
        mState->mAspectVary = ParseRangedFloat(mParser, opt[0], 0.0f, 1.0f);
}

// @ 0x00f55c50
void cCloudRotateCommand::Execute(cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mRotationCurve.clear();
    for (int i = 0; i < count; ++i)
        mState->mRotationCurve.push_back(mParser->GetFloat(argv[i]));
    const char** opt = args.OptionArguments("vary", 1);
    if (opt)
        mState->mRotationVary = ParseRangedFloat(mParser, opt[0], 0.0f, 1.0f);
}

// @ 0x00f55d50
void cCloudColorCommand::Execute(cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mColorCurve.clear();
    for (int i = 0; i < count; ++i)
        mState->mColorCurve.push_back(mParser->GetFloat(argv[i]));
    const char** opt = args.OptionArguments("vary", 1);
    if (opt)
        mState->mColorVary = ParseRangedFloat(mParser, opt[0], 0.0f, 1.0f);
    opt = args.OptionArguments("offset", 2);
    if (opt)
        mState->mColorOffset = mParser->GetFloat(opt[0]);
}

// @ 0x00f55e80
#pragma float_control(precise, off, push)
void cCloudForceCommand::Execute(cArguments& args)
{
    args.MainArguments(0);
    if (args.HasFlag("reset"))
        mState->mGravity = DAT_016c9234;

    const char** opt = args.OptionArguments("gravity", 1);
    if (opt)
        mState->mGravity.z = mState->mGravity.z - mParser->GetFloat(opt[0]);

    int count;
    opt = args.OptionArguments("wind", &count, 1, 0x7fffffff);
    if (opt) {
        Vec3 v = mParser->GetVector(opt[0]);
        float d = 1.0f / (float)sqrt((double)(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f));
        v.x *= d;
        v.y *= d;
        v.z *= d;
        if (count > 1) {
            float s = mParser->GetFloat(opt[1]);
            v.x *= s;
            v.y *= s;
            v.z *= s;
        }
        mState->mGravity.x += v.x;
        mState->mGravity.y += v.y;
        mState->mGravity.z += v.z;
    }

    opt = args.OptionArguments("worldWind", 1);
    if (opt)
        mState->mWorldWind = mParser->GetFloat(opt[0]);

    opt = args.OptionArguments("worldGravity", 1);
    if (opt)
        mState->mWorldGravity = mParser->GetFloat(opt[0]);

    opt = args.OptionArguments("bomb", &count, 1, 2);
    if (opt) {
        mState->mBombForce = mParser->GetFloat(opt[0]);
        if (count > 1)
            mState->mBombOffset = mParser->GetVector(opt[1]);
    }

    opt = args.OptionArguments("drag", 1);
    if (opt)
        mState->mDrag = mParser->GetFloat(opt[0]);

    bool preset = false;
    opt = args.OptionArguments("attractor", &count, 3, 0x7fffffff);
    if (opt) {
        mState->mAttractor = mParser->GetVector(opt[0]);
        --count;
        ++opt;
        preset = true;
        goto common;
    }
    opt = args.OptionArguments("presetAttractor", &count, 2, 0x7fffffff);
    if (!opt)
        return;

common:
    mState->mAttractorVary = mParser->GetFloat(opt[0]);
    mState->mAttractorCurve.clear();
    for (int i = 1; i < count; ++i)
        mState->mAttractorCurve.push_back(mParser->GetFloat(opt[i]));
    mState->mFlags |= 0x800000;
    if (preset)
        mState->mFlags |= 0x1000000;
    else
        mState->mFlags &= 0xfeffffff;

    opt = args.OptionArguments("killRange", 1);
    if (opt)
        mState->mKillRange = mParser->GetFloat(opt[0]);
}
#pragma float_control(pop)

// @ 0x00f56260
void cCloudWarpCommand::Execute(cArguments& args)
{
    args.MainArguments(0);

    const char** opt = args.OptionArguments("screw", 1);
    if (opt)
        mState->mScrewRate = mParser->GetFloat(opt[0]);

    opt = args.OptionArguments("spiral", 1);
    if (opt) {
        mState->mScrewRate = mParser->GetFloat(opt[0]);
        mState->mFlags |= 0x20000000;
    }

    opt = args.OptionArguments("wiggle", 4);
    if (opt) {
        WiggleKey key;
        float phase = mParser->GetFloat(opt[0]);
        key.f0 = mParser->GetFloat(opt[1]);
        key.f1 = 0.0f;
        key.f2 = 0.0f;
        key.f3 = phase;
        float amp = mParser->GetFloat(opt[2]);
        float t = ParseRangedFloat(mParser, opt[3], 0.0f, 1.0f);
        float scaled = DAT_016c92cc * t;
        float rounded = DAT_016c9230 * scaled + 12582912.0f;
        int bits = *(int*)&rounded;
        uint32_t idx = (uint32_t)bits & 0xf;
        float a = DAT_01677840[idx * 2];
        float b = DAT_01677840[idx * 2 + 1];
        float frac = scaled - (float)(bits - 0x4b400000) * DAT_016c92b8;
        key.f4 = (b - (0.5f * b * frac + a) * frac) * amp;
        key.f5 = -(((b - 0.5f * a * frac) * frac + a) * amp);
        key.f6 = 0.0f;
        mState->mWiggle.push_back(key);
    }

    int count;
    opt = args.OptionArguments("wiggleDir", &count, 2, 3);
    if (opt) {
        WiggleKey key;
        key.f0 = mParser->GetFloat(opt[0]);
        Vec3 w = mParser->GetVector(opt[1]);
        key.f4 = w.x;
        key.f5 = w.y;
        key.f6 = w.z;
        Vec3 v = DAT_016c9234;
        if (count > 2)
            v = mParser->GetVector(opt[2]);
        key.f1 = v.x;
        key.f2 = v.y;
        key.f3 = v.z;
        mState->mWiggle.push_back(key);
    }

    opt = args.OptionArguments("bloomAlpha", 2);
    if (opt) {
        float v0 = mParser->GetFloat(opt[0]);
        if (0.0f > v0) v0 = 0.0f;
        v0 *= 255.0f;
        if (v0 > 255.0f) v0 = 255.0f;
        mState->mBloomA0 = (uint8_t)(int)v0;

        float v1 = mParser->GetFloat(opt[1]) * 0.0625f;
        if (0.0f > v1) v1 = 0.0f;
        v1 *= 255.0f;
        if (v1 > 255.0f) v1 = 255.0f;
        mState->mBloomA1 = (uint8_t)(int)v1;

        mState->mBloomRev = 0;
        if (args.OptionArguments("reverseAlpha", 0))
            mState->mBloomRev = 1;
    }

    opt = args.OptionArguments("bloomSize", 2);
    if (opt) {
        float v0 = mParser->GetFloat(opt[0]);
        if (0.0f > v0) v0 = 0.0f;
        v0 *= 255.0f;
        if (v0 > 255.0f) v0 = 255.0f;
        mState->mBloomS0 = (uint8_t)(int)v0;

        float v1 = mParser->GetFloat(opt[1]) * 0.0625f;
        if (0.0f > v1) v1 = 0.0f;
        v1 *= 255.0f;
        if (v1 > 255.0f) v1 = 255.0f;
        mState->mBloomS1 = (uint8_t)(int)v1;
    }
}

// @ 0x00f56660
void cCloudWalkCommand::Execute(cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 0, 0x7fffffff);
    for (uint16_t i = 0; i < count; ++i)
        mState->mWalkCurve.push_back(ParseRangedFloat(mParser, argv[i], -1.0f, 1.0f));
    mState->mFlags |= 0x80000;

    const char** opt = args.OptionArguments("delay", &count, 1, 2);
    if (opt) {
        float a = mParser->GetFloat(opt[0]);
        float b = 0.0f;
        if (count > 1)
            b = mParser->GetFloat(opt[1]);
        float lo = a - b;
        float hi = a + b;
        mState->mDelayMin = lo;
        mState->mDelayMax = hi;
    }

    opt = args.OptionArguments("strength", &count, 1, 2);
    if (opt) {
        float a = mParser->GetFloat(opt[0]);
        float b = 0.0f;
        if (count > 1)
            b = mParser->GetFloat(opt[1]);
        float lo = a - b;
        float hi = a + b;
        mState->mStrengthMin = lo;
        mState->mStrengthMax = hi;
    }

    opt = args.OptionArguments("randomTurn", &count, 1, 0x7fffffff);
    if (opt) {
        mState->mTurnMin = ParseRangedFloat(mParser, opt[0], 0.0f, 1.0f);
        if (count > 1)
            mState->mTurnMax = ParseRangedFloat(mParser, opt[1], 0.0f, 1.0f);
        else
            mState->mTurnMax = 0.0f;
    } else {
        mState->mTurnMin = 0.0f;
        mState->mTurnMax = 0.0f;
    }

    mState->mWalkMode = 2;
    if (args.HasFlag("sustain"))
        mState->mWalkMode = 1;
    if (args.HasFlag("loop"))
        mState->mWalkMode = 0;

    opt = args.OptionArguments("mix", 1);
    if (opt)
        mState->mMix = ParseRangedFloat(mParser, opt[0], 0.0f, 1.0f);

    if (args.HasFlag("wait"))
        mState->mFlags |= 0x100000;
}
