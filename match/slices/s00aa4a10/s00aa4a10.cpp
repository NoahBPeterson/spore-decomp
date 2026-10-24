// Slice s00aa4a10: ArgScript particle-effect command registration (one function, 0x00aa4e50, 2484 B).
// Ghidra names it anonymous_namespace'::cParticleEffectCommand::OnRegister. The body is a chain of
// `AddCommand(keyword, new ("ArgScript/<name>", 0, 0, 0, 0) <command>())` blocks followed by
// RegisterPathCommand. Each command class is a cCommandT subclass with its own vtable. Only the
// vtable address (class identity) is visible in the asm, so each class is a template slot
// cParticleCmdT<N>, where N is the index of its vtable in the list below.
#include "types.h"

namespace EA { namespace ArgScript {
struct cIParser;
struct cState;
struct cArguments;
class cICommand { public:
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
class cCommandBase : public cICommand { public:
    cIParser* mParser;
    int mRefCount;
    cCommandBase();                                     // 0x0083c800
};
class cBlockCommandBase : public cICommand { public:
    cIParser* mParser;                                  // +0x04
    int mRefCount;                                      // +0x08
    cState* mChildState;                                // +0x0c
    uint32_t mCommands[8];                              // +0x10 hash map
    void OnRegister(cIParser* parser, cState* state);   // 0x0083c780
    void SetChildState(cState* state);                  // 0x00fd9450
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void AddCommand(const char* name, cICommand* command);      // +0x18
};
template <typename T, typename Base> struct cCommandStateT : Base {
    T* mState;                                          // +0x30 in a block command
    cCommandStateT() {}
};
template <typename T> class cCommandT : public cCommandStateT<T, cCommandBase> { public:
    cCommandT() {}
};
template <typename T> class cBlockCommandT : public cCommandStateT<T, cBlockCommandBase> { public:
    cBlockCommandT() {}
};
}}  // namespace EA::ArgScript

namespace EA { namespace Swarm {
struct cEffectsParser;
void RegisterPathCommand(void* owner, void* a, void* b, void* c);   // 0x00a7a8d0, cdecl
}}

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                 // 0x00f473a0

// Keyword globals (pointers to name strings), read by value from the data VAs in the asm.
extern const char* kKeyword_015654d0;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654d8;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654d4;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654dc;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654e0;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654e4;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654e8;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654ec;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654f0;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654f4;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654f8;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_015654fc;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565500;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565504;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565508;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156550c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565510;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565514;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565518;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156551c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565520;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565524;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565528;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156552c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565530;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565534;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565538;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156553c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565540;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565544;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565548;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156554c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565550;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565554;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565558;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_0156555c;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565560;   // keyword string pointer (data VA in the name)
extern const char* kKeyword_01565564;   // keyword string pointer (data VA in the name)

// ---------------------------------------------------------------- vtable identities
// Vtable VA -> index. 0 = 0x01458e20 ... 30 = 0x01459108 (values from the asm).
namespace {
template <int N> struct cParticleCmdT : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    cParticleCmdT() {}
    virtual void Execute(EA::ArgScript::cArguments& args);
};
}  // namespace

namespace {
struct cParticleEffectCommand : EA::ArgScript::cBlockCommandT<EA::Swarm::cEffectsParser> {
    char mPad34[4];                 // +0x34
    char mChildStateBase[0x2b0 - 0x38];   // +0x38 cState subobject (SetChildState target)
    void* mStateCopy;               // +0x2b0 copy of mState
    void OnRegister(EA::ArgScript::cIParser* parser, EA::ArgScript::cState* state);
};
}  // namespace

// @ 0x00aa4e50 anonymous_namespace'::cParticleEffectCommand::OnRegister
namespace {
void cParticleEffectCommand::OnRegister(EA::ArgScript::cIParser* parser, EA::ArgScript::cState* state)
{
    mState = state ? (EA::Swarm::cEffectsParser*)((char*)state - 0xc) : 0;
    EA::ArgScript::cBlockCommandBase::OnRegister(parser, state);
    SetChildState((EA::ArgScript::cState*)((char*)this + 0x38));
    mStateCopy = mState;
    AddCommand(kKeyword_015654d0, new ("ArgScript/ParticleColor", 0, 0, 0, 0) cParticleCmdT<0>());
    AddCommand(kKeyword_015654d8, new ("ArgScript/ParticleColor255", 0, 0, 0, 0) cParticleCmdT<0>());
    AddCommand(kKeyword_015654d4, new ("ArgScript/ParticleColour", 0, 0, 0, 0) cParticleCmdT<0>());
    AddCommand(kKeyword_015654dc, new ("ArgScript/ParticleColour255", 0, 0, 0, 0) cParticleCmdT<0>());
    AddCommand(kKeyword_015654e0, new ("ArgScript/ParticleAlpha", 0, 0, 0, 0) cParticleCmdT<1>());
    AddCommand(kKeyword_015654e4, new ("ArgScript/ParticleAlpha255", 0, 0, 0, 0) cParticleCmdT<1>());
    AddCommand(kKeyword_015654e8, new ("ArgScript/ParticleSize", 0, 0, 0, 0) cParticleCmdT<2>());
    AddCommand(kKeyword_015654ec, new ("ArgScript/ParticleAspect", 0, 0, 0, 0) cParticleCmdT<3>());
    AddCommand(kKeyword_015654f0, new ("ArgScript/ParticleRotate", 0, 0, 0, 0) cParticleCmdT<4>());
    AddCommand(kKeyword_015654f4, new ("ArgScript/ParticleSource", 0, 0, 0, 0) cParticleCmdT<5>());
    AddCommand(kKeyword_015654f8, new ("ArgScript/ParticleEmit", 0, 0, 0, 0) cParticleCmdT<6>());
    AddCommand(kKeyword_015654fc, new ("ArgScript/ParticleForce", 0, 0, 0, 0) cParticleCmdT<7>());
    AddCommand(kKeyword_01565500, new ("ArgScript/ParticleWarp", 0, 0, 0, 0) cParticleCmdT<8>());
    AddCommand(kKeyword_01565504, new ("ArgScript/ParticleDirectedWalk", 0, 0, 0, 0) cParticleCmdT<9>());
    AddCommand(kKeyword_01565508, new ("ArgScript/ParticleRandomWalk", 0, 0, 0, 0) cParticleCmdT<10>());
    AddCommand(kKeyword_0156550c, new ("ArgScript/ParticleStretch", 0, 0, 0, 0) cParticleCmdT<11>());
    AddCommand(kKeyword_01565510, new ("ArgScript/ParticleLife", 0, 0, 0, 0) cParticleCmdT<12>());
    AddCommand(kKeyword_01565514, new ("ArgScript/ParticleRate", 0, 0, 0, 0) cParticleCmdT<13>());
    AddCommand(kKeyword_01565518, new ("ArgScript/ParticleInject", 0, 0, 0, 0) cParticleCmdT<14>());
    AddCommand(kKeyword_0156551c, new ("ArgScript/ParticleMaintain", 0, 0, 0, 0) cParticleCmdT<15>());
    AddCommand(kKeyword_01565528, new ("ArgScript/ParticleMaterial", 0, 0, 0, 0) cParticleCmdT<16>());
    AddCommand(kKeyword_01565520, new ("ArgScript/ParticleTexture", 0, 0, 0, 0) cParticleCmdT<17>());
    AddCommand(kKeyword_01565524, new ("ArgScript/ParticleModel", 0, 0, 0, 0) cParticleCmdT<18>());
    AddCommand(kKeyword_0156552c, new ("ArgScript/ParticleFrames", 0, 0, 0, 0) cParticleCmdT<19>());
    AddCommand(kKeyword_01565530, new ("ArgScript/ParticleAlignment", 0, 0, 0, 0) cParticleCmdT<20>());
    AddCommand(kKeyword_01565534, new ("ArgScript/ParticleLoopBoxColor", 0, 0, 0, 0) cParticleCmdT<21>());
    AddCommand(kKeyword_0156553c, new ("ArgScript/ParticleLoopBoxColor255", 0, 0, 0, 0) cParticleCmdT<21>());
    AddCommand(kKeyword_01565538, new ("ArgScript/ParticleLoopBoxAlpha", 0, 0, 0, 0) cParticleCmdT<22>());
    AddCommand(kKeyword_01565540, new ("ArgScript/ParticleLoopBoxAlpha255", 0, 0, 0, 0) cParticleCmdT<22>());
    AddCommand(kKeyword_01565544, new ("ArgScript/ParticleSurface", 0, 0, 0, 0) cParticleCmdT<23>());
    AddCommand(kKeyword_01565548, new ("ArgScript/ParticleMapEmit", 0, 0, 0, 0) cParticleCmdT<24>());
    AddCommand(kKeyword_0156554c, new ("ArgScript/ParticleMapEmitColor", 0, 0, 0, 0) cParticleCmdT<25>());
    AddCommand(kKeyword_01565550, new ("ArgScript/ParticleMapEmitColour", 0, 0, 0, 0) cParticleCmdT<25>());
    AddCommand(kKeyword_01565554, new ("ArgScript/ParticleMapCollide", 0, 0, 0, 0) cParticleCmdT<26>());
    AddCommand(kKeyword_01565558, new ("ArgScript/ParticleMapRepel", 0, 0, 0, 0) cParticleCmdT<27>());
    AddCommand(kKeyword_0156555c, new ("ArgScript/ParticleMapAdvect", 0, 0, 0, 0) cParticleCmdT<28>());
    AddCommand(kKeyword_01565560, new ("ArgScript/ParticleMapForce", 0, 0, 0, 0) cParticleCmdT<29>());
    AddCommand(kKeyword_01565564, new ("ArgScript/ParticlePhysics", 0, 0, 0, 0) cParticleCmdT<30>());
    EA::Swarm::RegisterPathCommand(this, (char*)this + 0x2c8, (char*)this + 0x2c9, (char*)this + 0x29c);
}
}  // namespace

extern const float HK_REAL_ONE;     // 0x01485720 Havok hkReal 1.0, the default option value

// ---------------------------------------------------------------------------------------------
// Execute bodies of the particle commands (0x00aa4a10 .. 0x00aa5810).
//
// Every Execute unpacks its positional arguments with cArguments::MainArguments, stores the
// effects-map id resolved for the first argument into the command state (mState, located at
// +0x0c for these non-block commands), turns on the feature bits for the command and reads its
// optional arguments, converting them with the parser's float/vector parsers (vtable +0x98 and
// +0xb0).
namespace EA { namespace ArgScript {

// Argument list handed to an Execute.
struct cArguments {
    const char** MainArguments(int count);                                  // 0x00838320
    const char** MainArguments(int* outCount, int minArgs, int maxArgs);    // 0x00838020
    bool HasFlag(const char* name);                                         // 0x008380b0
    const char** OptionArguments(const char* name, int minArgs);            // 0x00838330
    const char* operator[](int index);                                      // 0x00837f20
};

#define PARSER_CAT2(a, b) a##b
#define PARSER_CAT(a, b) PARSER_CAT2(a, b)
#define PARSER_SLOT() virtual void PARSER_CAT(slot, __COUNTER__)();

// The parser interface as seen by the particle commands: only the string-to-float slot (+0x98)
// and the string-to-vector slot (+0xb0) are used here.
struct cIParser {
    PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT()
    PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT()
    PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT()
    PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT()
    PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT()
    PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT()
    PARSER_SLOT() PARSER_SLOT()
    virtual float ParseFloat(const char* text);                     // +0x98
    PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT() PARSER_SLOT()
    virtual float* ParseVector(float* out, const char* text);       // +0xb0
};
#undef PARSER_SLOT
#undef PARSER_CAT
#undef PARSER_CAT2

}}  // namespace EA::ArgScript

namespace EA { namespace Swarm {

// Minimal view of the eastl vector that stores the particle curves (erase / push_back).
struct Vec0C {
    void* mBegin;            // +0x00
    void* mEnd;              // +0x04
    void* mEndCapacity;      // +0x08
    void* erase(void* first, void* last);    // 0x009e0480
};

// The effect state the particle commands configure (the command's mState).
struct cEffectsParser {
    char     pad000[0x10];
    uint32_t mFlags;             // +0x10  feature bits
    char     pad014[0xc8];
    Vec0C    mCurves;            // +0xdc  alpha/colour curves
    char     pad0e8[0x08];
    float    mVary[3];           // +0xf0  "vary" range
    char     pad0fc[0xcc];
    float    mBounce;            // +0x1c8 "bounce"
    float    mInterval;          // +0x1cc emit interval
    float    mStrength;          // +0x1d0 force/warp strength
    float    mScout;             // +0x1d4 "scout"
    float    mVertical;          // +0x1d8 "vertical"
    float    mKillHeight;        // +0x1dc "killHeight"
    float    mDeath;             // +0x1e0 "death"
    char     pad1e4[0x0c];
    int64_t  mPinToMapID;        // +0x1f0 effects map id the effect is pinned to
    char     pad1f8[0x08];
    int64_t  mMapID;             // +0x200 effects map id of the effect
    char     pad208[0x70];
    cEffectsParser* mpParser;    // +0x278 owning parser
    int64_t EffectsMapID(const char* name);     // 0x00a6e600
};

}}  // namespace EA::Swarm

extern "C" float __cdecl ParseRangedFloat(void* parser, const char* text, float lo, float hi);      // 0x00840d50
extern "C" float* __cdecl ParseRangedVector3(float* out, void* parser, const char* text, float lo,
                                             float hi);                                            // 0x00840e10
void __stdcall ScaleCurve(void* dst, const void* src);                                             // 0x007ed1b0
void __cdecl FUN_007ecc30(EA::Swarm::Vec0C* curves, float scale);                                  // 0x007ecc30
extern "C" char* __cdecl strstr(const char* text, const char* find);

namespace {
struct cParticleModelCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments& args);
};
struct cParticleSourceCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments& args);
};
struct cParticleEmitCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments& args);
};
struct cParticleForceCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments& args);
};
struct cParticleWarpCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments& args);
};
struct cParticleAlphaCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments& args);
};
}  // namespace

// @ 0x00aa4a10 cParticleModelCommand::Execute: "ParticleModel <mapid>"
namespace {
void cParticleModelCommand::Execute(EA::ArgScript::cArguments& args)
{
    const char** argv = args.MainArguments(1);
    mState->mMapID = mState->mpParser->EffectsMapID(argv[0]);
}
}  // namespace

// @ 0x00aa4a50 cParticleSourceCommand::Execute: "ParticleSource [mapid] [bounce=..] [death=..]"
namespace {
void cParticleSourceCommand::Execute(EA::ArgScript::cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 0, 1);
    if (count < 1)
        mState->mPinToMapID = 0;
    else
        mState->mPinToMapID = mState->mpParser->EffectsMapID(argv[0]);
    mState->mFlags |= 0x2000;
    if (args.HasFlag("pinToMap")) {
        mState->mFlags |= 0x40000;
        mState->mBounce = 0.0f;
    } else {
        const char** bounce = args.OptionArguments("bounce", 1);
        if (bounce)
            mState->mBounce = (float)mParser->ParseFloat(bounce[0]);
    }
    if (args.HasFlag("killOutsideMap"))
        mState->mFlags |= 0x20000;
    const char** death = args.OptionArguments("death", 1);
    if (death)
        mState->mDeath = (float)ParseRangedFloat(mParser, death[0], 0.0f, 1.0f);
}
}  // namespace

// @ 0x00aa4b60 cParticleEmitCommand::Execute: "ParticleEmit <mapid> <interval> <strength> ..."
namespace {
void cParticleEmitCommand::Execute(EA::ArgScript::cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 2, 3);
    const char* strength;
    if (count < 3) {
        mState->mPinToMapID = 0;
        mState->mInterval = (float)mParser->ParseFloat(argv[0]);
        strength = argv[1];
    } else {
        mState->mPinToMapID = mState->mpParser->EffectsMapID(argv[0]);
        mState->mInterval = (float)mParser->ParseFloat(argv[1]);
        strength = argv[2];
    }
    mState->mStrength = (float)mParser->ParseFloat(strength);
    mState->mFlags |= 0x2000;
    mState->mFlags |= 0x4000;
    const char** scout = args.OptionArguments("scout", 1);
    if (scout)
        mState->mScout = (float)mParser->ParseFloat(scout[0]);
    const char** vertical = args.OptionArguments("vertical", 1);
    if (vertical)
        mState->mVertical = (float)mParser->ParseFloat(vertical[0]);
    const char** killHeight = args.OptionArguments("killHeight", 1);
    if (killHeight)
        mState->mKillHeight = (float)mParser->ParseFloat(killHeight[0]);
    if (args.HasFlag("killOutsideMap"))
        mState->mFlags |= 0x20000;
}
}  // namespace

// @ 0x00aa4cc0 cParticleForceCommand::Execute: "ParticleForce <mapid> [strength=..]"
namespace {
void cParticleForceCommand::Execute(EA::ArgScript::cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mPinToMapID = mState->mpParser->EffectsMapID(argv[0]);
    mState->mFlags |= 0x2000;
    mState->mFlags |= 0x8000;
    const char** strength = args.OptionArguments("strength", 1);
    if (strength)
        mState->mStrength = mParser->ParseFloat(strength[0]);
    else
        mState->mStrength = HK_REAL_ONE;
    if (args.HasFlag("killOutsideMap"))
        mState->mFlags |= 0x20000;
}
}  // namespace

// @ 0x00aa4d70 cParticleWarpCommand::Execute: "ParticleWarp <mapid> [strength=..]"
namespace {
void cParticleWarpCommand::Execute(EA::ArgScript::cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mPinToMapID = mState->mpParser->EffectsMapID(argv[0]);
    mState->mFlags |= 0x2000;
    mState->mFlags |= 0x10000;
    const char** strength = args.OptionArguments("strength", 1);
    if (strength)
        mState->mStrength = mParser->ParseFloat(strength[0]);
    else
        mState->mStrength = HK_REAL_ONE;
    if (args.HasFlag("killOutsideMap"))
        mState->mFlags |= 0x20000;
}
}  // namespace

// @ 0x00aa5810 cParticleAlphaCommand::Execute: "ParticleAlpha <curve>... [vary=..]"
namespace {
void cParticleAlphaCommand::Execute(EA::ArgScript::cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mCurves.erase(mState->mCurves.mBegin, mState->mCurves.mEnd);
    for (int i = 0; i < count; ++i) {
        float curve[3];
        float* src = mParser->ParseVector(curve, argv[i]);
        float* end = (float*)mState->mCurves.mEnd;
        if (end < (float*)mState->mCurves.mEndCapacity) {
            mState->mCurves.mEnd = end + 3;
            if (end) {
                end[0] = src[0];
                end[1] = src[1];
                end[2] = src[2];
            }
        } else {
            ScaleCurve(end, src);
        }
    }
    const char** vary = args.OptionArguments("vary", 1);
    if (vary) {
        float range[3];
        float* src = ParseRangedVector3(range, mParser, vary[0], 0.0f, 1.0f);
        mState->mVary[0] = src[0];
        mState->mVary[1] = src[1];
        mState->mVary[2] = src[2];
    }
    const char* name = args[0];
    if (strstr(name, "255"))
        FUN_007ecc30(&mState->mCurves, 0.0039215689f);
}
}  // namespace
