// Swarm skin-paint "particle" ArgScript commands (unoptimized /Od /Ob1 module).
// delay / life / curve / align / initDir / attract / restrict + the three
// ParseEnum blend setters, and EA::Swarm::normalized.
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------- math
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    float& operator[](int i) const { return ((float*)this)[i]; }
};

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline float Sqrt(float x) { volatile float r = (float)sqrt(x); return r; }

extern "C" __declspec(dllimport) int __cdecl _stricmp(const char* a, const char* b);
void Vector3Divide(cSPVector3* out, const cSPVector3* in, const float* scalar); // @ 0x453880

cSPVector3* normalized(cSPVector3* out, const cSPVector3& in)
{
    float len = in[0] * in[0] + in[1] * in[1] + in[2] * in[2];
    float d = Sqrt(len);
    Vector3Divide(out, &in, &d);
    return out;
}

// ---------------------------------------------------------------- ArgScript
namespace EA { namespace ArgScript {

#define PV(n) virtual void pv##n();

struct cIParser {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual float GetFloat(const char* text);          // +0x98
    PV(39) PV(40) PV(41)
    virtual cSPVector3 GetVector(const char* text);    // +0xa8
};
#undef PV

struct cArguments {
    const char** MainArguments(size_t* pCount, int minCount, int maxCount);  // 0x838020
    const char** OptionArguments(const char* name, int count);               // 0x838330
    bool HasFlag(const char* flag);                                          // 0x8380b0
};

struct cICommand {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
struct cCommandBase : cICommand {
    cIParser* mParser;      // +0x4
    int mRefCount;          // +0x8
};

} } // namespace EA::ArgScript

namespace EA { namespace Swarm {
// @ 0x840bb0
uint8_t ParseEnum(const char* value, const char** nameTable);
// @ 0x840d50
float ParseRangedFloat(EA::ArgScript::cIParser* parser, const char* text, float lo, float hi);
} }

// ---------------------------------------------------------------- description
struct BrushDesc {
    char pad0[0x1c];
    uint32_t mFlags;                    // +0x1c
    cSPVector3 mUserColorHSV;           // +0x20
    char mUserColorIndex;               // +0x2c
    uint8_t mAlignment;                 // +0x2d
    uint8_t mInitialDirection;          // +0x2e
    uint8_t mAttraction;                // +0x2f
    cSPVector3 mAlignTarget;            // +0x30
    cSPVector3 mInitialDirTarget;       // +0x3c
    cSPVector3 mAttractTarget;          // +0x48
    float mAttractStrength;             // +0x54
    float mDelayMin;                    // +0x58
    float mDelayMax;                    // +0x5c
    float mLifeMin;                     // +0x60
    float mLifeMax;                     // +0x64
    uint32_t mInheritMask;              // +0x68
    char pad1[0xa8 - 0x6c];
    uint8_t mBlend0;                    // +0xa8
    uint8_t mBlend1;                    // +0xa9
    uint8_t mBlend2;                    // +0xaa
};

struct DescriptionBase {
    virtual void d0();
    virtual void d1();
    int mnRefCount;
};
struct cSPSkinPaintParticleDescription : DescriptionBase {
    BrushDesc mBrush;                   // +0x8
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
};

struct cSPSkinPaintParticleEffectBlockCommand {
    char pad0[0x48];
    AutoRefCount<cSPSkinPaintParticleDescription> mpDesc;  // +0x48
};

#define BRUSH() \
    cSPSkinPaintParticleDescription* A; \
    cSPSkinPaintParticleDescription* pDesc; \
    BrushDesc* p; \
    pDesc = A; \
    pDesc = mState->mpDesc; \
    p = pDesc ? &pDesc->mBrush : 0;

namespace {
using EA::ArgScript::cArguments;

struct cSPSkinPaintParticledelayCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;   // +0xc
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticlelifeCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticlecurveCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticlealignCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticleinitDirCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticleattractCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticlerestrictCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticlediffuseColorCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticlespecularColorCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
struct cSPSkinPaintParticlebumpColorCommand : EA::ArgScript::cCommandBase {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments& args);
};
}  // namespace

extern const char* kAlphaNames[];      // 0x13f2ed0

// @ 0x00538e90
void cSPSkinPaintParticledelayCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 2);
    if (count == 2) {
        p->mDelayMin = mParser->GetFloat(argv[0]);
        p->mDelayMax = mParser->GetFloat(argv[1]);
    } else {
        float value = mParser->GetFloat(argv[0]);
        float vary = 0.0f;
        const char** opt = args.OptionArguments("vary", 1);
        if (opt != 0)
            vary = mParser->GetFloat(opt[0]);
        p->mDelayMin = (1.0f - vary) * value;
        p->mDelayMax = (1.0f + vary) * value;
    }
}

// @ 0x00538fe0
void cSPSkinPaintParticlelifeCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 2);
    if (count == 2) {
        p->mLifeMin = mParser->GetFloat(argv[0]);
        p->mLifeMax = mParser->GetFloat(argv[1]);
    } else {
        float value = mParser->GetFloat(argv[0]);
        float vary = 0.0f;
        const char** opt = args.OptionArguments("vary", 1);
        if (opt != 0)
            vary = mParser->GetFloat(opt[0]);
        p->mLifeMin = (1.0f - vary) * value;
        p->mLifeMax = (1.0f + vary) * value;
    }
}

// @ 0x00539130
void cSPSkinPaintParticlecurveCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 0, 500);
    (void)argv;
    if (args.HasFlag("random"))
        p->mFlags |= 4;
}

// @ 0x005391c0
void cSPSkinPaintParticlealignCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    if (_stricmp(argv[0], "inherit") == 0) {
        p->mAlignment = 0;
    } else if (_stricmp(argv[0], "move") == 0) {
        p->mAlignment = 1;
    } else if (_stricmp(argv[0], "dir") == 0) {
        p->mAlignment = 1;
    } else if (_stricmp(argv[0], "attract") == 0) {
        p->mAlignment = 2;
    } else if (_stricmp(argv[0], "aroundbone") == 0) {
        p->mAlignment = 5;
    } else if (_stricmp(argv[0], "alongbone") == 0) {
        p->mAlignTarget = cSPVector3(0.0f, 1.0f, 0.0f);
        p->mAlignment = 4;
    } else if (_stricmp(argv[0], "aroundspine") == 0) {
        p->mAlignment = 7;
    } else if (_stricmp(argv[0], "alongspine") == 0) {
        p->mAlignTarget = cSPVector3(0.0f, 1.0f, 0.0f);
        p->mAlignment = 6;
    } else {
        cSPVector3 v = mParser->GetVector(argv[0]);
        cSPVector3 n;
        normalized(&n, v);
        p->mAlignTarget = n;
        if (args.HasFlag("bone"))
            p->mAlignment = 4;
        else
            p->mAlignment = 3;
    }
    if (args.HasFlag("reverse"))
        p->mFlags |= 0x40;
}

// @ 0x005394e0
void cSPSkinPaintParticleinitDirCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    if (_stricmp(argv[0], "inherit") == 0) {
        p->mInitialDirection = 0;
    } else if (_stricmp(argv[0], "attract") == 0) {
        p->mInitialDirection = 2;
    } else if (_stricmp(argv[0], "aroundbone") == 0) {
        p->mInitialDirection = 5;
    } else if (_stricmp(argv[0], "alongbone") == 0) {
        p->mInitialDirTarget = cSPVector3(0.0f, 1.0f, 0.0f);
        p->mInitialDirection = 4;
    } else if (_stricmp(argv[0], "aroundspine") == 0) {
        p->mInitialDirection = 7;
    } else if (_stricmp(argv[0], "alongspine") == 0) {
        p->mInitialDirTarget = cSPVector3(0.0f, 1.0f, 0.0f);
        p->mInitialDirection = 6;
    } else {
        cSPVector3 v = mParser->GetVector(argv[0]);
        cSPVector3 n;
        normalized(&n, v);
        p->mInitialDirTarget = n;
        if (args.HasFlag("bone"))
            p->mInitialDirection = 4;
        else
            p->mInitialDirection = 3;
    }
    if (args.HasFlag("reverse"))
        p->mFlags |= 0x20;
}

// @ 0x00539720
void cSPSkinPaintParticleattractCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 2);
    if (_stricmp(argv[0], "inherit") == 0) {
        p->mAttraction = 0;
    } else if (_stricmp(argv[0], "aroundbone") == 0) {
        p->mAttraction = 5;
    } else if (_stricmp(argv[0], "alongbone") == 0) {
        p->mAttractTarget = cSPVector3(0.0f, 1.0f, 0.0f);
        p->mAttraction = 4;
    } else if (_stricmp(argv[0], "aroundspine") == 0) {
        p->mAttraction = 7;
    } else if (_stricmp(argv[0], "alongspine") == 0) {
        p->mAttractTarget = cSPVector3(0.0f, 1.0f, 0.0f);
        p->mAttraction = 6;
    } else {
        cSPVector3 v = mParser->GetVector(argv[0]);
        cSPVector3 n;
        normalized(&n, v);
        p->mAttractTarget = n;
        if (args.HasFlag("bone"))
            p->mAttraction = 4;
        else
            p->mAttraction = 3;
    }
    if (count == 1)
        p->mAttractStrength = 1.0f;
    else
        p->mAttractStrength = EA::Swarm::ParseRangedFloat(mParser, argv[1], 0.0f, 1.0f);
    if (args.HasFlag("reverse"))
        p->mFlags |= 0x10;
}

// @ 0x00539980
void cSPSkinPaintParticlerestrictCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 2);
    p->mFlags |= 8;
    if (_stricmp(argv[0], "inherit") == 0) {
        p->mAttraction = 0;
    } else if (_stricmp(argv[0], "aroundbone") == 0) {
        p->mAttraction = 5;
    } else if (_stricmp(argv[0], "alongbone") == 0) {
        p->mAttractTarget = cSPVector3(0.0f, 1.0f, 0.0f);
        p->mAttraction = 4;
    } else if (_stricmp(argv[0], "aroundspine") == 0) {
        p->mAttraction = 7;
    } else if (_stricmp(argv[0], "alongspine") == 0) {
        p->mAttractTarget = cSPVector3(0.0f, 1.0f, 0.0f);
        p->mAttraction = 6;
    } else {
        cSPVector3 v = mParser->GetVector(argv[0]);
        cSPVector3 n;
        normalized(&n, v);
        p->mAttractTarget = n;
        if (args.HasFlag("bone"))
            p->mAttraction = 4;
        else
            p->mAttraction = 3;
    }
    if (count == 1)
        p->mAttractStrength = 1.0f;
    else
        p->mAttractStrength = EA::Swarm::ParseRangedFloat(mParser, argv[1], 0.0f, 1.0f);
    if (args.HasFlag("reverse"))
        p->mFlags |= 0x10;
}

// @ 0x00539bf0
void cSPSkinPaintParticlediffuseColorCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    p->mBlend0 = EA::Swarm::ParseEnum(argv[0], kAlphaNames);
}

// @ 0x00539c70
void cSPSkinPaintParticlespecularColorCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    p->mBlend1 = EA::Swarm::ParseEnum(argv[0], kAlphaNames);
}

// @ 0x00539cf0
void cSPSkinPaintParticlebumpColorCommand::Execute(cArguments& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    p->mBlend2 = EA::Swarm::ParseEnum(argv[0], kAlphaNames);
}
