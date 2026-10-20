// Slice s00aa3a30: EA::Swarm ArgScript particle-effect line commands (Execute bodies).
//  0x00aa3a30  cParticleSourceCommand::Execute   (PDB)
//  0x00aa3f30  cParticleEmitCommand::Execute
//  0x00aa4180  cParticleForceCommand::Execute
//  0x00aa43c0  cParticleLifeCommand::Execute     (PDB)
//  0x00aa44f0  cParticleTextureCommand::Execute
//  0x00aa45a0  cParticleFramesCommand::Execute
//  0x00aa46e0  cParticleModelCommand::Execute
//  0x00aa47e0  cParticleRateCommand::Execute
//  0x00aa48e0  cParticleSurfaceCommand::Execute
// Command objects are 0x10 bytes: vptr, mParser(+4), mRefCount(+8), mState(+0xc).
// mState points at the particle-effect component (the "draw info" block whose parser
// back-pointer lives at +0x278).  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned long long uint64_t;

// ------------------------------------------------------------------ ArgScript
namespace EA { namespace ArgScript {
struct cState { int mID; };

struct cIParser {
    virtual void pv00(); virtual void pv01(); virtual void pv02(); virtual void pv03();
    virtual void pv04(); virtual void pv05(); virtual void pv06(); virtual void pv07();
    virtual void pv08(); virtual void pv09(); virtual void pv10(); virtual void pv11();
    virtual void pv12(); virtual void pv13(); virtual void pv14(); virtual void pv15();
    virtual void pv16(); virtual void pv17(); virtual void pv18(); virtual void pv19();
    virtual void pv20(); virtual void pv21(); virtual void pv22(); virtual void pv23();
    virtual void pv24(); virtual void pv25(); virtual void pv26(); virtual void pv27();
    virtual void pv28(); virtual void pv29(); virtual void pv30(); virtual void pv31();
    virtual void pv32(); virtual void pv33(); virtual void pv34(); virtual void pv35();
    virtual void pv36(); virtual void pv37();
    virtual float  ParseFloat(const char* text);                    // +0x98
    virtual int    ParseInt(const char* text);                      // +0x9c
    virtual unsigned ParseUInt(const char* text);                   // +0xa0
    virtual float* ParseVector2(float* out, const char* text);      // +0xa4
    virtual float* ParseVector3(float* out, const char* text);      // +0xa8
};

struct cArguments {
    const char** MainArguments(int minCount) const;                                 // 0x838320
    const char** MainArguments(int* pCount, int minCount, int maxCount) const;      // 0x838020
    const char** OptionArguments(const char* name, int count) const;                // 0x838330
    const char** OptionArguments(const char* name, int* pCount, int minCount,
                                 int maxCount) const;                               // 0x838130
    bool HasFlag(const char* flag) const;                                           // 0x8380b0
};

struct cICommand {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
struct cCommandBase : cICommand {
    cIParser* mParser;      // +0x04
    int mRefCount;          // +0x08
};
}}  // namespace EA::ArgScript

using EA::ArgScript::cArguments;
using EA::ArgScript::cIParser;

// ------------------------------------------------------------------ helpers
struct Vector2 { float x, y; };
struct Vector3 {
    float x, y, z;
    void Set(float a, float b, float c);        // 0x00a9a1c0
    void SetSymmetric(float s);                 // 0x006e9910
    void From(const Vector3& v);                // 0x00a93c60
};

float ParseRangedFloat(cIParser* parser, const char* text, float min, float max);   // 0x00840d50

// Default shape corner vector (zero-initialised global).
extern const float gShapeDefault[3];            // 0x016792c4

namespace EA { namespace Swarm {
struct cEffectsParser {
    unsigned long long GetResourceInstance(int kind, const char* name);             // 0x00a6ec40
    unsigned long long LookupSurface(const char* name);                             // 0x00a6e600
    void ParseDrawInfoOptions(cArguments& args, cIParser* parser,
                              unsigned long long* pResource);                       // 0x00a6ed80
};

// Particle-effect component: only the fields these commands touch.
struct cParticleState {
    uint8_t  pad00[0x10];
    uint32_t mFlags;                // +0x10
    uint32_t mFlags2;               // +0x14
    float    mLifeMin;              // +0x18
    float    mLifeMax;              // +0x1c
    float    mPreroll;              // +0x20
    uint8_t  pad24[0x34 - 0x24];
    float    mDir[6];               // +0x34
    float    mSpeedMin;             // +0x4c
    float    mSpeedMax;             // +0x50
    float    mShape[6];             // +0x54
    float    mRingThickness;        // +0x6c
    uint8_t  pad70[0x118 - 0x70];
    uint64_t mTexture;              // +0x118
    uint8_t  mField120;             // +0x120
    uint8_t  mDrawInfoType;         // +0x121
    uint8_t  mField122;             // +0x122
    uint8_t  pad123[0x130 - 0x123];
    uint64_t mMaterial;             // +0x130
    uint8_t  pad138;
    uint8_t  mOverrideSet;          // +0x139
    uint8_t  mTileX;                // +0x13a
    uint8_t  mTileY;                // +0x13b
    uint8_t  pad13c;
    uint8_t  mStart;                // +0x13d
    uint8_t  mCount;                // +0x13e
    uint8_t  mRandom;               // +0x13f
    float    mRateSpeed;            // +0x140
    uint8_t  pad144[0x1e4 - 0x144];
    float    mAboveHeight;          // +0x1e4
    float    mBelowHeight;          // +0x1e8
    uint8_t  pad1ec[0x1f8 - 0x1ec];
    uint64_t mSurface;              // +0x1f8
    uint8_t  pad200[0x208 - 0x200];
    float    mDelayMin;             // +0x208
    float    mDelayMax;             // +0x20c
    float    mStrengthMin;          // +0x210
    float    mStrengthMax;          // +0x214
    float    mTurnMin;              // +0x218
    float    mTurnMax;              // +0x21c
    float    mMix;                  // +0x220
    uint8_t  pad224[0x278 - 0x224];
    cEffectsParser* mParser;        // +0x278
};
}}  // namespace EA::Swarm

using EA::Swarm::cEffectsParser;
using EA::Swarm::cParticleState;

struct cParticleCommandBase : EA::ArgScript::cCommandBase {
    cParticleState* mState;     // +0x0c
};

#define DECL_CMD(NAME) \
    struct NAME : cParticleCommandBase { virtual void Execute(cArguments& args); };

DECL_CMD(cParticleSourceCommand)
DECL_CMD(cParticleEmitCommand)
DECL_CMD(cParticleForceCommand)
DECL_CMD(cParticleLifeCommand)
DECL_CMD(cParticleTextureCommand)
DECL_CMD(cParticleFramesCommand)
DECL_CMD(cParticleModelCommand)
DECL_CMD(cParticleRateCommand)
DECL_CMD(cParticleSurfaceCommand)

#define FLT_MAX 3.402823466e+38f

// @ 0x00aa3a30
void cParticleSourceCommand::Execute(cArguments& args)
{
    args.MainArguments(0);

    Vector3 vMin, vMax;
    vMin.x = gShapeDefault[0];
    vMin.y = gShapeDefault[1];
    vMin.z = gShapeDefault[2];
    vMax.x = gShapeDefault[0];
    vMax.y = gShapeDefault[1];
    vMax.z = gShapeDefault[2];

    mState->mFlags &= ~0x10u;

    if (!args.HasFlag("point")) {
        const char** a;
        if ((a = args.OptionArguments("square", 1)) != 0) {
            float f = mParser->ParseFloat(a[0]);
            if (vMin.x != FLT_MAX && vMin.x != -FLT_MAX) {
                vMin.x -= f;
                vMin.y -= f;
                vMax.x += f;
                vMax.y += f;
            }
        } else if ((a = args.OptionArguments("quad", 1)) != 0) {
            Vector2 q;
            mParser->ParseVector2(&q.x, a[0]);
            if (vMin.x != FLT_MAX && vMin.x != -FLT_MAX) {
                vMin.x -= q.x;
                vMin.y -= q.y;
                vMax.x += q.x;
                vMax.y += q.y;
            }
        } else if ((a = args.OptionArguments("cube", 1)) != 0) {
            float f = mParser->ParseFloat(a[0]);
            vMin.SetSymmetric(f);
        } else if ((a = args.OptionArguments("box", 1)) != 0) {
            mParser->ParseVector3(&vMin.x, a[0]);
            vMax.From(vMin);
        } else if ((a = args.OptionArguments("circle", 1)) != 0) {
            mState->mFlags |= 0x10u;
            float f = mParser->ParseFloat(a[0]);
            vMin.Set(f, f, 0.0f);
        } else if ((a = args.OptionArguments("sphere", 1)) != 0) {
            mState->mFlags |= 0x10u;
            float f = mParser->ParseFloat(a[0]);
            vMin.SetSymmetric(f);
        } else if ((a = args.OptionArguments("ellipse", 1)) != 0) {
            mState->mFlags |= 0x10u;
            mParser->ParseVector3(&vMin.x, a[0]);
            vMax.From(vMin);
        } else if ((a = args.OptionArguments("ellipsoid", 1)) != 0) {
            mState->mFlags |= 0x10u;
            mParser->ParseVector3(&vMin.x, a[0]);
            vMax.From(vMin);
        } else if ((a = args.OptionArguments("ring", 2)) != 0) {
            float f = mParser->ParseFloat(a[0]);
            mState->mRingThickness = ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
            vMin.Set(f, f, 0.0f);
        } else if ((a = args.OptionArguments("torus", 2)) != 0) {
            mParser->ParseVector3(&vMin.x, a[0]);
            mState->mRingThickness = ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
            vMax.From(vMin);
        }
    }

    const char** off = args.OptionArguments("offset", 1);
    if (off != 0) {
        Vector3 o;
        mParser->ParseVector3(&o.x, off[0]);
        if (vMin.x != FLT_MAX && vMin.x != -FLT_MAX) {
            vMin.x += o.x;
            vMin.y += o.y;
            vMin.z += o.z;
            vMax.x += o.x;
            vMax.y += o.y;
            vMax.z += o.z;
        }
    }

    mState->mShape[0] = vMin.x;
    mState->mShape[1] = vMin.y;
    mState->mShape[2] = vMin.z;
    mState->mShape[3] = vMax.x;
    mState->mShape[4] = vMax.y;
    mState->mShape[5] = vMax.z;

    if (args.HasFlag("scaleParticles"))
        mState->mFlags |= 0x800u;
    if (args.HasFlag("resetIncoming"))
        mState->mFlags |= 0x4000000u;
}

// @ 0x00aa3f30
void cParticleEmitCommand::Execute(cArguments& args)
{
    args.MainArguments(0);

    int n;
    const char** a = args.OptionArguments("speed", &n, 1, 0x7fffffff);
    if (a != 0) {
        float w = 0.0f;
        float v = mParser->ParseFloat(a[0]);
        if (n > 1)
            w = mParser->ParseFloat(a[1]);
        mState->mSpeedMin = v - w;
        mState->mSpeedMax = v + w;
    }

    a = args.OptionArguments("dir", &n, 1, 2);
    if (a != 0) {
        Vector3 d;
        mParser->ParseVector3(&d.x, a[0]);
        Vector3 e;
        e.x = gShapeDefault[0];
        e.y = gShapeDefault[1];
        e.z = gShapeDefault[2];
        if (n > 1)
            e = *(Vector3*)mParser->ParseVector3(&e.x, a[1]);

        float len = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
        float nx = d.x * len;
        float ny = d.y * len;
        float nz = d.z * len;
        mState->mDir[0] = nx;
        mState->mDir[1] = ny;
        mState->mDir[2] = nz;
        mState->mDir[3] = nx;
        mState->mDir[4] = ny;
        mState->mDir[5] = nz;

        if (mState->mDir[0] != FLT_MAX && mState->mDir[0] != -FLT_MAX) {
            mState->mDir[0] -= e.x;
            mState->mDir[1] -= e.y;
            mState->mDir[2] -= e.z;
            mState->mDir[3] += e.x;
            mState->mDir[4] += e.y;
            mState->mDir[5] += e.z;
        }
    }

    if (args.HasFlag("base"))
        mState->mFlags |= 0x8u;
    if (args.HasFlag("scaleExisting"))
        mState->mFlags |= 0x2000000u;
}

// @ 0x00aa4180
void cParticleForceCommand::Execute(cArguments& args)
{
    args.MainArguments(0);
    mState->mFlags |= 0x80000u;

    int n;
    const char** a = args.OptionArguments("delay", &n, 1, 2);
    if (a != 0) {
        float v = mParser->ParseFloat(a[0]);
        float w = 0.0f;
        if (n > 1)
            w = mParser->ParseFloat(a[1]);
        mState->mDelayMin = v - w;
        mState->mDelayMax = v + w;
    }

    a = args.OptionArguments("strength", &n, 1, 2);
    if (a != 0) {
        float v = mParser->ParseFloat(a[0]);
        float w = 0.0f;
        if (n > 1)
            w = mParser->ParseFloat(a[1]);
        mState->mStrengthMin = v - w;
        mState->mStrengthMax = v + w;
    }

    a = args.OptionArguments("turn", &n, 1, 0x7fffffff);
    if (a != 0) {
        mState->mTurnMin = ParseRangedFloat(mParser, a[0], 0.0f, 1.0f);
        if (n > 1)
            mState->mTurnMax = ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
        else
            mState->mTurnMax = 0.0f;
    }

    a = args.OptionArguments("mix", 1);
    if (a != 0)
        mState->mMix = ParseRangedFloat(mParser, a[0], 0.0f, 1.0f);

    if (args.HasFlag("wait"))
        mState->mFlags |= 0x100000u;
}

// @ 0x00aa43c0
void cParticleLifeCommand::Execute(cArguments& args)
{
    int n;
    const char** a = args.MainArguments(&n, 1, 0x7fffffff);
    float w = 0.0f;
    float v = mParser->ParseFloat(a[0]);
    if (n > 1)
        w = mParser->ParseFloat(a[1]);
    mState->mLifeMin = v - w;
    mState->mLifeMax = v + w;

    const char** p = args.OptionArguments("preroll", 1);
    if (p != 0) {
        mState->mPreroll = mParser->ParseFloat(p[0]);
    } else {
        mState->mPreroll = (v > 0.5f) ? v : 0.5f;
    }

    if (args.HasFlag("propagateAlways"))
        mState->mFlags2 |= 1u;
    else
        mState->mFlags2 &= ~1u;
    if (args.HasFlag("propagateIfKilled"))
        mState->mFlags2 |= 2u;
    else
        mState->mFlags2 &= ~2u;
}

// @ 0x00aa44f0
void cParticleTextureCommand::Execute(cArguments& args)
{
    mState->mDrawInfoType = 0xf;
    mState->mFlags &= ~0x200000u;

    int n;
    const char** a = args.MainArguments(&n, 0, 1);
    if (n > 0)
        mState->mTexture = mState->mParser->GetResourceInstance(1, a[0]);

    const char** p = args.OptionArguments("overrideSet", 1);
    if (p != 0)
        mState->mOverrideSet = (uint8_t)mParser->ParseUInt(p[0]);
    else
        mState->mOverrideSet = 0;

    mState->mParser->ParseDrawInfoOptions(args, mParser, &mState->mTexture);
}

// @ 0x00aa45a0
void cParticleFramesCommand::Execute(cArguments& args)
{
    mState->mDrawInfoType = 0;
    mState->mFlags &= ~0x200000u;

    int n;
    const char** a = args.MainArguments(&n, 0, 1);
    if (n > 0)
        mState->mTexture = mState->mParser->GetResourceInstance(0, a[0]);

    const char** t = args.OptionArguments("tile", &n, 1, 2);
    if (t != 0) {
        mState->mTileX = (uint8_t)mParser->ParseUInt(t[0]);
        if (n > 1)
            mState->mTileY = (uint8_t)mParser->ParseUInt(t[1]);
        else
            mState->mTileY = 1;
    }

    mState->mParser->ParseDrawInfoOptions(args, mParser, &mState->mTexture);

    const char** p = args.OptionArguments("overrideSet", 1);
    if (p != 0)
        mState->mOverrideSet = (uint8_t)mParser->ParseUInt(p[0]);
    else
        mState->mOverrideSet = 0;

    if (args.HasFlag("acceptComposite"))
        mState->mFlags |= 0x400000u;
    else
        mState->mFlags &= ~0x400000u;
}

// @ 0x00aa46e0
void cParticleModelCommand::Execute(cArguments& args)
{
    mState->mDrawInfoType = 0;
    mState->mFlags |= 0x200000u;

    int n;
    const char** a = args.MainArguments(&n, 0, 1);
    if (n > 0)
        mState->mTexture = mState->mParser->GetResourceInstance(2, a[0]);

    const char** p = args.OptionArguments("material", 1);
    if (p != 0) {
        mState->mMaterial = mState->mParser->GetResourceInstance(1, p[0]);
        mState->mDrawInfoType = 0xf;
    }

    const char** q = args.OptionArguments("overrideSet", 1);
    if (q != 0)
        mState->mOverrideSet = (uint8_t)mParser->ParseUInt(q[0]);
    else
        mState->mOverrideSet = 0;

    mState->mField122 |= 8;
    mState->mParser->ParseDrawInfoOptions(args, mParser, &mState->mTexture);
}

// @ 0x00aa47e0
void cParticleRateCommand::Execute(cArguments& args)
{
    args.MainArguments(0);

    const char** p = args.OptionArguments("speed", 1);
    if (p != 0)
        mState->mRateSpeed = mParser->ParseFloat(p[0]);

    p = args.OptionArguments("count", 1);
    if (p != 0)
        mState->mCount = (uint8_t)mParser->ParseUInt(p[0]);

    p = args.OptionArguments("start", 1);
    if (p != 0)
        mState->mStart = (uint8_t)mParser->ParseUInt(p[0]);

    p = args.OptionArguments("random", 1);
    if (p != 0)
        mState->mRandom = (uint8_t)mParser->ParseUInt(p[0]);
}

// @ 0x00aa48e0
void cParticleSurfaceCommand::Execute(cArguments& args)
{
    const char** a = args.MainArguments(1);
    mState->mSurface = mState->mParser->LookupSurface(a[0]);

    if (args.HasFlag("pinToSurface"))
        mState->mFlags |= 0x20u;

    const char** p = args.OptionArguments("belowHeight", 1);
    if (p != 0) {
        mState->mFlags |= 0x40u;
        mState->mBelowHeight = mParser->ParseFloat(p[0]);
    }

    p = args.OptionArguments("aboveHeight", 1);
    if (p != 0) {
        mState->mFlags |= 0x40u;
        mState->mAboveHeight = mParser->ParseFloat(p[0]);
    }

    const char** q = args.OptionArguments("heightRange", 2);
    if (q != 0) {
        mState->mFlags |= 0x40u;
        mState->mAboveHeight = mParser->ParseFloat(q[0]);
        mState->mBelowHeight = mParser->ParseFloat(q[1]);
    }

    if (args.HasFlag("density"))
        mState->mFlags |= 0x80u;
}
