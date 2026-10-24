// Slice s00f54af0: anonymous-namespace swarm effect command handlers.
//   00f54af0 / 00f54c00 / 00f54d60 / 00f54e10  cXxxCommand::ParseLine (thiscall, ret 4)
//   00f558b0                                   cCloudAlphaCommand::Execute (thiscall, ret 4)
// Every handler reads the command's cArguments through MainArguments/OptionArguments/HasFlag and
// writes the parsed values into the shared swarm effect object at this+0xc.
#include "types.h"
#include <stddef.h>

extern "C" char* __cdecl strstr(const char* haystack, const char* needle);

namespace EA {
namespace ArgScript {

struct cArguments;

struct Vector3 {
    float x, y, z;
};

// Parser: only the two virtuals these handlers call are named; they sit at +0x98 (slot 38) and
// +0xb0 (slot 44).
struct cParser {
    virtual void v00() {} virtual void v01() {} virtual void v02() {} virtual void v03() {}
    virtual void v04() {} virtual void v05() {} virtual void v06() {} virtual void v07() {}
    virtual void v08() {} virtual void v09() {} virtual void v10() {} virtual void v11() {}
    virtual void v12() {} virtual void v13() {} virtual void v14() {} virtual void v15() {}
    virtual void v16() {} virtual void v17() {} virtual void v18() {} virtual void v19() {}
    virtual void v20() {} virtual void v21() {} virtual void v22() {} virtual void v23() {}
    virtual void v24() {} virtual void v25() {} virtual void v26() {} virtual void v27() {}
    virtual void v28() {} virtual void v29() {} virtual void v30() {} virtual void v31() {}
    virtual void v32() {} virtual void v33() {} virtual void v34() {} virtual void v35() {}
    virtual void v36() {} virtual void v37() {}
    virtual float Evaluate(const char* text);          // +0x98
    virtual void v39() {} virtual void v40() {} virtual void v41() {} virtual void v42() {}
    virtual void v43() {}
    virtual Vector3 EvaluateVector(const char* text);  // +0xb0
};

struct cEffectsParser {
    int64_t EffectsMapID(const char* name);            // 0x00a6e600
};

struct cArguments {
    const char** MainArguments(int* count, int minArgs, int maxArgs) const;   // 0x00838020
    bool HasFlag(const char* name) const;                                     // 0x008380b0
    const char** OptionArguments(const char* name, int minArgs) const;        // 0x00838330
    const char* operator[](int index) const;                                  // 0x00837f20
};

// eastl vector of 12-byte vectors
struct Vec0C {
    Vector3* mpBegin;       // +0
    Vector3* mpEnd;         // +4
    Vector3* mpCapacity;    // +8
    Vector3* erase(Vector3* first, Vector3* last);           // 0x009e0480
    void ScaleCurve(Vector3* end, const Vector3* value);     // 0x007ed1b0
    void push_back(const Vector3& value) {
        if (mpEnd < mpCapacity) {
            Vector3* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot) {
                slot->x = value.x;
                slot->y = value.y;
                slot->z = value.z;
            }
        } else {
            ScaleCurve(mpEnd, &value);
        }
    }
};

} // namespace ArgScript

namespace ArgScript {

extern float g_cloudAlphaValue;    // 0x013eecd4

// The shared swarm effect object the commands configure.
struct cEffect {
    uint32_t pad00[4];          // +0x00
    uint32_t mFlags;            // +0x10
    uint32_t pad14[0x31];       // +0x14 .. +0xd7
    Vec0C    mCurve;            // +0xd8
    uint32_t padE4[2];          // +0xe4
    Vector3  mVary;             // +0xec
    uint32_t padF8[0x33];       // +0xf8 .. +0x1c3
    float    mPinDistance;      // +0x1c4
    float    mValue1;           // +0x1c8
    float    mStrength;         // +0x1cc
    float    mScout;            // +0x1d0
    float    mVertical;         // +0x1d4
    float    mKillHeight;       // +0x1d8
    float    mDeathTime;        // +0x1dc
    uint32_t pad1E0[2];         // +0x1e0
    int64_t  mId;               // +0x1e8
    uint32_t pad1F0[0x20];      // +0x1f0 .. +0x26f
    cEffectsParser* mpEffectsParser;   // +0x270
};
#define CHK(cls, name, off) typedef char chk_##cls##_##name[(offsetof(cls, name) == (off)) ? 1 : -1]
CHK(cEffect, mFlags, 0x10);
CHK(cEffect, mCurve, 0xd8);
CHK(cEffect, mVary, 0xec);
CHK(cEffect, mPinDistance, 0x1c4);
CHK(cEffect, mValue1, 0x1c8);
CHK(cEffect, mStrength, 0x1cc);
CHK(cEffect, mScout, 0x1d0);
CHK(cEffect, mVertical, 0x1d4);
CHK(cEffect, mKillHeight, 0x1d8);
CHK(cEffect, mDeathTime, 0x1dc);
CHK(cEffect, mId, 0x1e8);
CHK(cEffect, mpEffectsParser, 0x270);

// command base: vtable +0, parser +4, effect +0xc
struct cEffectCommandBase {
    void*    mpVtable;      // +0
    cParser* mParser;       // +4
    uint32_t mPad08;        // +8
    cEffect* mEffect;       // +0xc
};
CHK(cEffectCommandBase, mParser, 4);
CHK(cEffectCommandBase, mEffect, 0xc);
#undef CHK

// ranged-argument helpers (cdecl)
float ParseRangedFloat(cParser* parser, const char* text, float minValue, float maxValue);                 // 0x00840d50
Vector3* ParseRangedVector3(Vector3* out, cParser* parser, const char* text, float minValue, float maxValue); // 0x00840e10
void ApplyCurveAlpha(float value, Vec0C* curve);                                                          // 0x007ecc30

// ---- commands --------------------------------------------------------------------------------
struct cPinCommand : cEffectCommandBase {
    void ParseLine(const cArguments& args);        // 0x00f54af0
};
struct cScoutCommand : cEffectCommandBase {
    void ParseLine(const cArguments& args);        // 0x00f54c00
};
struct cStrengthCommand : cEffectCommandBase {
    void ParseLine(const cArguments& args);        // 0x00f54d60
};
struct cStrengthExCommand : cEffectCommandBase {
    void ParseLine(const cArguments& args);        // 0x00f54e10
};
struct cCloudAlphaCommand : cEffectCommandBase {
    void Execute(const cArguments& args);          // 0x00f558b0
};

// @ 0x00f54af0
void cPinCommand::ParseLine(const cArguments& args)
{
    int count;
    const char** main = args.MainArguments(&count, 0, 1);
    if (count > 0) {
        mEffect->mId = mEffect->mpEffectsParser->EffectsMapID(main[0]);
    } else {
        mEffect->mId = 0;
    }
    mEffect->mFlags |= 0x2000;
    if (args.HasFlag("pinToMap")) {
        mEffect->mFlags |= 0x40000;
        mEffect->mPinDistance = 0.0f;
    } else {
        const char** option = args.OptionArguments("bounce", 1);
        if (option)
            mEffect->mPinDistance = mParser->Evaluate(option[0]);
    }
    if (args.HasFlag("killOutsideMap"))
        mEffect->mFlags |= 0x20000;
    const char** death = args.OptionArguments("death", 1);
    if (death)
        mEffect->mDeathTime = ParseRangedFloat(mParser, death[0], 0.0f, 1.0f);
}

// @ 0x00f54c00
void cScoutCommand::ParseLine(const cArguments& args)
{
    int count;
    const char** main = args.MainArguments(&count, 2, 3);
    const char* third;
    if (count > 2) {
        mEffect->mId = mEffect->mpEffectsParser->EffectsMapID(main[0]);
        mEffect->mValue1 = mParser->Evaluate(main[1]);
        third = main[2];
    } else {
        mEffect->mId = 0;
        mEffect->mValue1 = mParser->Evaluate(main[0]);
        third = main[1];
    }
    mEffect->mStrength = mParser->Evaluate(third);
    mEffect->mFlags |= 0x2000;
    mEffect->mFlags |= 0x4000;
    const char** option = args.OptionArguments("scout", 1);
    if (option)
        mEffect->mScout = mParser->Evaluate(option[0]);
    const char** vertical = args.OptionArguments("vertical", 1);
    if (vertical)
        mEffect->mVertical = mParser->Evaluate(vertical[0]);
    const char** killHeight = args.OptionArguments("killHeight", 1);
    if (killHeight)
        mEffect->mKillHeight = mParser->Evaluate(killHeight[0]);
    if (args.HasFlag("killOutsideMap"))
        mEffect->mFlags |= 0x20000;
}

// @ 0x00f54d60
void cStrengthCommand::ParseLine(const cArguments& args)
{
    int count;
    const char** main = args.MainArguments(&count, 1, 0x7fffffff);
    mEffect->mId = mEffect->mpEffectsParser->EffectsMapID(main[0]);
    mEffect->mFlags |= 0x2000;
    mEffect->mFlags |= 0x8000;
    const char** option = args.OptionArguments("strength", 1);
    if (option) {
        mEffect->mStrength = mParser->Evaluate(option[0]);
    } else {
        mEffect->mStrength = 1.0f;
    }
    if (args.HasFlag("killOutsideMap"))
        mEffect->mFlags |= 0x20000;
}

// @ 0x00f54e10
void cStrengthExCommand::ParseLine(const cArguments& args)
{
    int count;
    const char** main = args.MainArguments(&count, 1, 0x7fffffff);
    mEffect->mId = mEffect->mpEffectsParser->EffectsMapID(main[0]);
    mEffect->mFlags |= 0x2000;
    mEffect->mFlags |= 0x10000;
    const char** option = args.OptionArguments("strength", 1);
    if (option) {
        mEffect->mStrength = mParser->Evaluate(option[0]);
    } else {
        mEffect->mStrength = 1.0f;
    }
    if (args.HasFlag("killOutsideMap"))
        mEffect->mFlags |= 0x20000;
}

// @ 0x00f558b0
void cCloudAlphaCommand::Execute(const cArguments& args)
{
    int count;
    const char** main = args.MainArguments(&count, 1, 0x7fffffff);
    mEffect->mCurve.erase(mEffect->mCurve.mpBegin, mEffect->mCurve.mpEnd);
    for (int i = 0; i < count; ++i) {
        Vector3 value = mParser->EvaluateVector(main[i]);
        mEffect->mCurve.push_back(value);
    }
    const char** option = args.OptionArguments("vary", 1);
    if (option) {
        Vector3 temp;
        mEffect->mVary = *ParseRangedVector3(&temp, mParser, option[0], 0.0f, 1.0f);
    }
    if (strstr(args[0], "255"))
        ApplyCurveAlpha(g_cloudAlphaValue, &mEffect->mCurve);
}

} // namespace ArgScript
} // namespace EA
