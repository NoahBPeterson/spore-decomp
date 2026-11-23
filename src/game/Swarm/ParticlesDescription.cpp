// src/game/Swarm/ParticlesDescription.cpp -- migrated from slice(s) s00aa3a30, s00aa2f00, s00aa5940, s00a9a630, s00a99640, s00a987c0, s00aa7470, s00aa4a10 by tools/migrate/rewrite.py
// Object file: Swarm/ParticlesDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cICommand.h"
#include "EA/ArgScript/cArguments.h"
#include <intrin.h>
#include <string.h>
#include <math.h>
#include "EA/ArgScript/cIParser.h"
#include <xmmintrin.h>
#include "EA/ArgScript/cState.h"

// slice s00aa5940's own sqrtf (the slice defines `static inline float sqrtf(float)`, which clashes with
// <math.h>'s C declaration; the one call in 0x00aa5de0 is renamed to this by a manual edit)
static inline float sqrtf_s00aa_5940(float v) { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(v))); }

// ---- local stubs of slice s00aa2f00 (added by hand: the slice writes `namespace EA` and `{` on separate
// lines, which rewrite.py's preamble parser reads as one item named after its first struct, so the stubs
// the verbatim functions need were pruned; see work/migrate/report_s00aa2f00_ParticlesDescription.md)
extern "C" void operator_delete__(void* p);             // 0x00f47380, the slices' global operator delete declaration
namespace EA {
namespace Swarm {
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };

extern Vector3 gDefaultVector;           // 0x016792c4
extern float gEmitR;                     // 0x01679158
extern float gEmitG;                     // 0x0167915c
extern float gEmitB;                     // 0x01679160
extern const float kFloat2;              // 0x01470f1c
extern const float kFloat1;              // 0x01485720
extern const float kFloatMinus1;         // 0x013eb1bc
extern const float kFloatHundredth;      // 0x013eb960
extern const float kFloat30;             // 0x014853bc
extern const float kFloatNeg1e9;         // 0x01457d54
extern const float kFloatNeg1e4;         // 0x01418f90
extern const float kFloatPos1e4;         // 0x013f0620
extern const float kFloat5;              // 0x01486110
extern const float kFloatQuarter;        // 0x013eb8a0

struct SimpleVectorF
{
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    SimpleVectorF() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __declspec(nothrow) ~SimpleVectorF();        // inlined below: retail 0x00aa32f0 frees it through a `call ext`
    void push_back(float value);
    void DoInsertValue(float* pEnd, const float& value);
};

SimpleVectorF::~SimpleVectorF()
{
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator_delete__(mpBegin);     // global operator delete (0x00f47380); `delete` here needs EH state in the caller
}
struct SimpleVectorV3
{
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    SimpleVectorV3() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __declspec(nothrow) ~SimpleVectorV3();       // inlined below: retail 0x00aa32f0 frees it through a `call ext`
    void push_back(const Vector3& value);
    void Insert(Vector3* pEnd, const Vector3& value);
};
SimpleVectorV3::~SimpleVectorV3()
{
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator_delete__(mpBegin);     // global operator delete (0x00f47380); `delete` here needs EH state in the caller
}
struct SimpleVectorW
{
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    SimpleVectorW() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __declspec(nothrow) ~SimpleVectorW();        // the +0x16c vector: frees through a `call ext` in retail 0x00aa32f0
};
SimpleVectorW::~SimpleVectorW()
{
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator_delete__((void*)mpBegin);
}

struct cParticleState
{
    char      mPad000[8];
    uint32_t  mFlags;
    uint32_t  mFlags2;
    float     mf10, mf14, mf18;
    Vector2   mDelay;
    Vector2   mTrigger;
    char      mPad2c[0x7c - 0x2c];
    float     mLoopTime;
    uint16_t  mLoopMode;
    char      mPad82[2];
    float     mSpeedScale;
};

struct GmeRefCount
{
    virtual void Cast();
    GmeRefCount() : mRefCount(0) {}
    __declspec(nothrow) ~GmeRefCount() {}
    int mRefCount;
};

struct cInlineDequeF
{
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    cInlineDequeF() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void FreeRange(float* pBegin, float* pEnd);
    __declspec(nothrow) ~cInlineDequeF();        // inlined below: retail 0x00aa32f0 frees it through a `call ext`
};
cInlineDequeF::~cInlineDequeF()
{
    FreeRange(mpBegin, mpEnd);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator_delete__(mpBegin);     // global operator delete (0x00f47380); `delete` here needs EH state in the caller
}

struct cParticlesDescription : GmeRefCount
{
    uint32_t         mFlags;
    uint32_t         mFlags2;
    float            mMinSize;
    float            mMaxSize;
    float            mf018;
    Vector2          mEmitDelay;
    Vector2          mTrigger;
    float            mf02c;
    float            mf030;
    float            mf034;
    float            mf038;
    float            mf03c;
    float            mf040;
    float            mf044;
    float            mf048;
    float            mf04c;
    float            mf050;
    float            mf054;
    float            mf058;
    float            mf05c;
    float            mf060;
    float            mf064;
    SimpleVectorF    mRateCurve;
    char             mPad074[8];
    float            mf07c;
    uint16_t         mMode;
    char             mPad082[2];
    float            mf084;
    SimpleVectorF    mSizeCurve;
    char             mPad094[8];
    float            mf09c;
    SimpleVectorF    mAspectCurve;
    char             mPad0ac[8];
    float            mf0b4;
    SimpleVectorF    mRotationCurve;
    char             mPad0c4[8];
    float            mf0cc;
    float            mf0d0;
    SimpleVectorV3   mColorCurve;
    char             mPad0e0[8];
    Vector3          mColorVary;
    SimpleVectorF    mAlphaCurve;
    char             mPad100[8];
    float            mf108;
    char             mPad10c[4];
    int32_t          mi110;
    int32_t          mi114;
    char             mB118[4];
    uint16_t         mW11c;
    char             mPad11e[2];
    float            mf120;
    char             mPad124[4];
    int32_t          mi128;
    int32_t          mi12c;
    uint8_t          mB130, mB131, mB132, mB133, mB134, mB135, mB136, mB137;
    float            mf138;
    Vector3          mV13c;
    float            mf148, mf14c, mf150;
    Vector3          mV154;
    float            mf160, mf164, mf168;
    SimpleVectorW    mWiggles;
    char             mPad178[8];
    uint8_t          mB180, mB181, mB182, mB183;
    SimpleVectorV3   mLoopBoxColorCurve;
    char             mPad190[8];
    SimpleVectorF    mLoopBoxAlphaCurve;
    char             mPad1a4[8];
    cInlineDequeF    mCurve1ac;
    char             mPad1b8[8];
    float            mf1c0;
    float            mf1c4;
    float            mf1c8;
    float            mf1cc;
    float            mf1d0;
    float            mf1d4;
    float            mf1d8;
    float            mf1dc;
    float            mf1e0;
    char             mPad1e4[4];
    int32_t          mi1e8;
    int32_t          mi1ec;
    int32_t          mi1f0;
    int32_t          mi1f4;
    int32_t          mi1f8;
    int32_t          mi1fc;
    float            mf200;
    float            mf204;
    float            mf208;
    float            mf20c;
    float            mf210;
    float            mf214;
    float            mf218;
    SimpleVectorF    mCurve21c;
    char             mPad228[8];
    uint8_t          mB230;
    char             mPad231[3];
    Vector3          mV234;
    SimpleVectorF    mCurve240;
    char             mPad24c[8];
    float            mf254;
    float            mf258;
    SimpleVectorF    mCurve25c;

    cParticlesDescription();
    virtual ~cParticlesDescription();
};

struct cEffectsParser;   // the TU's own definition (slice s00aa4a10) follows below
struct cICommand
{
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
struct cCommandBase : cICommand
{
    cCommandBase();
    void*                    mpParser;
    int                      mRefCount;
};
struct cGroupParticlesCommand : cCommandBase
{
    cEffectsParser* mpEffectsParser;
    int             mFlags;
    cGroupParticlesCommand(int flags) : mFlags(flags) {}
};

void SimpleVectorF::push_back(float value)
{
    if (mpEnd < mpCapacity)
    {
        float* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            *p = value;
    }
    else
    {
        DoInsertValue(mpEnd, value);
    }
}

void SimpleVectorV3::push_back(const Vector3& value)
{
    if (mpEnd < mpCapacity)
    {
        Vector3* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            *p = value;
    }
    else
    {
        Insert(mpEnd, value);
    }
}
}
}
using namespace EA::Swarm;   // the slice's verbatim functions name its stubs unqualified (rewrite.py drops the directive)

// ---- local stubs of slice s00aa3a30 (added by hand: the slice defines its command classes with the
// DECL_CMD macro, which rewrite.py's preamble parser does not expand, so the classes were never emitted
// and the verbatim Execute definitions bound to the TU's anonymous-namespace classes of the same name.
// The classes get a _s00aa_3a30 suffix; the `pragmas` manual entries rename each definition's class.)
struct cEffectsParser_s00aa_3a30;
namespace EA {
namespace Swarm {
struct cParticleState_s00aa_3a30 {
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
    cEffectsParser_s00aa_3a30* mParser;        // +0x278
};
}
}
namespace EA { namespace ArgScript { class cArguments_s00aa_3a30; class cIParser_s00aa_3a30; } }
struct cICommand_s00aa_3a30 {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
struct cCommandBase_s00aa_3a30 : cICommand_s00aa_3a30 {
    EA::ArgScript::cIParser_s00aa_3a30* mParser;     // +0x04
    int mRefCount;                                   // +0x08
};
struct cEffectsParser_s00aa_3a30 {
    unsigned long long GetResourceInstance(int kind, const char* name);
    unsigned long long LookupSurface(const char* name);
    void ParseDrawInfoOptions(EA::ArgScript::cArguments_s00aa_3a30& args,
                              EA::ArgScript::cIParser_s00aa_3a30* parser,
                              unsigned long long* pResource);
};
struct cParticleCommandBase_s00aa_3a30 : cCommandBase_s00aa_3a30 {
    EA::Swarm::cParticleState_s00aa_3a30* mState;     // +0x0c
};
struct cParticleSourceCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };
struct cParticleEmitCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };
struct cParticleForceCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };
struct cParticleLifeCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };
struct cParticleTextureCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };
struct cParticleFramesCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };
struct cParticleModelCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };
struct cParticleRateCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };
struct cParticleSurfaceCommand_s00aa_3a30 : cParticleCommandBase_s00aa_3a30 { virtual void Execute(EA::ArgScript::cArguments_s00aa_3a30& args); };

// unnamed retail callees and globals (address in the comment)
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

// ---- items of slice s00aa4a10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float HK_REAL_ONE;     // 0x01485720 Havok hkReal 1.0, the default option value
extern "C" float __cdecl ParseRangedFloat(void* parser, const char* text, float lo, float hi);      // 0x00840d50
extern "C" float* __cdecl ParseRangedVector3(float* out, void* parser, const char* text, float lo,
                                             float hi);                                            // 0x00840e10
namespace EA {
namespace ArgScript {
struct cIParser_s00aa_4a10;
}
}
namespace EA {
namespace ArgScript {
struct cState_s00aa_4a10;
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s00aa_4a10;
}
}
namespace EA {
namespace ArgScript {
class cICommand_s00aa_4a10 { public:
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
}
}
namespace EA {
namespace ArgScript {
class cCommandBase_s00aa_4a10 : public cICommand_s00aa_4a10 { public:
    cIParser_s00aa_4a10* mParser;
    int mRefCount;
    cCommandBase_s00aa_4a10();                                     // 0x0083c800
};
}
}
namespace EA {
namespace ArgScript {
class cBlockCommandBase : public cICommand_s00aa_4a10 { public:
    cIParser_s00aa_4a10* mParser;                                  // +0x04
    int mRefCount;                                      // +0x08
    cState_s00aa_4a10* mChildState;                                // +0x0c
    uint32_t mCommands[8];                              // +0x10 hash map
    void OnRegister(cIParser_s00aa_4a10* parser, cState_s00aa_4a10* state);   // 0x0083c780
    void SetChildState(cState_s00aa_4a10* state);                  // 0x00fd9450
virtual void v03();
virtual void v04();
virtual void v05();
    virtual void AddCommand(const char* name, cICommand_s00aa_4a10* command);      // +0x18
};
}
}
namespace EA {
namespace ArgScript {
template <typename T, typename Base> struct cCommandStateT_s00aa_4a10 : Base {
    T* mState;                                          // +0x30 in a block command
    cCommandStateT_s00aa_4a10() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> class cCommandT : public cCommandStateT_s00aa_4a10<T, cCommandBase_s00aa_4a10> { public:
    cCommandT() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> class cBlockCommandT : public cCommandStateT_s00aa_4a10<T, cBlockCommandBase> { public:
    cBlockCommandT() {}
};
}
}
namespace EA {
namespace Swarm {
struct cEffectsParser;
}
}
namespace EA {
namespace Swarm {
void RegisterPathCommand(void* owner, void* a, void* b, void* c);   // 0x00a7a8d0, cdecl
}
}
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                 // 0x00f473a0
namespace {
template <int N> struct cParticleCmdT : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    cParticleCmdT() {}
    virtual void Execute(EA::ArgScript::cArguments_s00aa_4a10& args);
};
}  // namespace
namespace {
struct cParticleEffectCommand : EA::ArgScript::cBlockCommandT<EA::Swarm::cEffectsParser> {
    char mPad34[4];                 // +0x34
    char mChildStateBase[0x2b0 - 0x38];   // +0x38 cState subobject (SetChildState target)
    void* mStateCopy;               // +0x2b0 copy of mState
    void OnRegister(EA::ArgScript::cIParser_s00aa_4a10* parser, EA::ArgScript::cState_s00aa_4a10* state);
};
}  // namespace
namespace EA {
namespace ArgScript {
struct cArguments_s00aa_4a10 {
    const char** MainArguments(int count);                                  // 0x00838320
    const char** MainArguments(int* outCount, int minArgs, int maxArgs);    // 0x00838020
    bool HasFlag(const char* name);                                         // 0x008380b0
    const char** OptionArguments(const char* name, int minArgs);            // 0x00838330
    const char* operator[](int index);                                      // 0x00837f20
};
}
}
namespace EA {
namespace ArgScript {
#define PARSER_CAT2(a, b) a##b
}
}
namespace EA {
namespace ArgScript {
#define PARSER_CAT(a, b) PARSER_CAT2(a, b)
}
}
namespace EA {
namespace ArgScript {
#define PARSER_SLOT() virtual void PARSER_CAT(slot, __COUNTER__)();
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s00aa_4a10 {
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
}
}
namespace EA {
namespace Swarm {
struct Vec0C {
    void* mBegin;            // +0x00
    void* mEnd;              // +0x04
    void* mEndCapacity;      // +0x08
    void* erase(void* first, void* last);    // 0x009e0480
};
}
}
namespace EA {
namespace Swarm {
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
}
}
void __stdcall ScaleCurve(void* dst, const void* src);                                             // 0x007ed1b0
void __cdecl FUN_007ecc30(EA::Swarm::Vec0C* curves, float scale);                                  // 0x007ecc30
extern "C" char* __cdecl strstr_s00aa_4a10(const char* text, const char* find);
namespace {
struct cParticleModelCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments_s00aa_4a10& args);
};
struct cParticleSourceCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments_s00aa_4a10& args);
};
struct cParticleEmitCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments_s00aa_4a10& args);
};
struct cParticleForceCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments_s00aa_4a10& args);
};
struct cParticleWarpCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments_s00aa_4a10& args);
};
struct cParticleAlphaCommand : EA::ArgScript::cCommandT<EA::Swarm::cEffectsParser> {
    virtual void Execute(EA::ArgScript::cArguments_s00aa_4a10& args);
};
}  // namespace
// ---- items of slice s00aa4a10 end

// ---- items of slice s00aa7470 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char  DAT_014119cc[];    // "reset"
extern "C" void  operator_delete__(void* p);
extern "C" int   FUN_00a87470(int a, int b, int c);
extern "C" void  FUN_00a7d280(void* a, void* b, void* c, void* d);   // ParseSurfaceOptions
#define VTP(obj, off)   (*(void**)((char*)(*(void**)(obj)) + (off)))
struct CArgs {
    void* MainArguments(int n);              // 0x838320
    void* MainArgumentsX(void* out, int a, int b);  // 0x838020
    char  HasFlag(const char* name);         // 0x8380b0
};
struct StrAssign {
    void FUN_00454cb0(const char* begin, const char* end);  // eastl::basic_string::assign
};
struct CmdObj {
    void* FUN_00aa3460();     // ctor
    void  FUN_00aa32f0();     // dtor
};
struct Parser {
    void* FUN_00a6f090(void* args, int count, void* extra);  // GetInheritedDescription
};
struct XOp {   // generic thiscall helpers (1/2 pointer args) for eastl vectors etc.
    void FUN_0050d4e0(const void* rhs);       // eastl::vector<float,..>::operator=
    void FUN_006f5cd0(const void* rhs);       // vector_operator_assign_c
    void FUN_00a9a3d0(const void* rhs);
    void FUN_00a87b90(const void* rhs);
    void FUN_00a9a500(const void* rhs);
    void FUN_00a87280(const void* src);       // construct element at this
    void FUN_00a87d20(void* end, const void* src);
    void FUN_00a87300(int a, int b);
};
struct Self {
    char raw[0x2e0];
    Self* FUN_00aa7470(const Self* o);
    void  FUN_00aa82e0(char p);
    void  FUN_00aa8370(int p);
    bool  FUN_00aa7fb0(int p2, int* p3, int p4);
    void  FUN_00aa7910(void* args);
    void  FUN_00aa7a80(void* args);
};
// ---- items of slice s00aa7470 end

// ---- items of slice s00a987c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem1C {
    float w[7];
};
// ---- items of slice s00a987c0 end

// ---- items of slice s00a99640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete_arr(void* p);                       // 0x00f47380 operator delete[]
extern float gSentinel_15653e0;                                              // 0x015653e0
struct Rec7 {
    uint32_t w0, w1, w2, w3, w4, w5, w6;    // 0x00..0x18
};
extern "C" Rec7* __cdecl MoveRec7(Rec7* first, Rec7* last, Rec7* out);       // 0x00a7a930
extern "C" Rec7  __cdecl RotateCopy(const Rec7* first, const Rec7* last, Rec7* dst, const Rec7* dstEnd);  // 0x00a99350
extern "C" Rec7  __cdecl RotateCopy2(const Rec7* first, const Rec7* last, Rec7* dst); // 0x00a993b0
struct RecVec {
    Rec7* mpBegin;      // 0x00
    Rec7* mpEnd;        // 0x04
    Rec7* mpCap;        // 0x08

    uint32_t size() const { return (uint32_t)((char*)mpEnd - (char*)mpBegin) / 0x1c; }
    uint32_t capacity() const { return (uint32_t)((char*)mpCap - (char*)mpBegin) / 0x1c; }

    void    reserve(uint32_t n, const void* tag);            // 0x00a05830
    void    UninitialisedFill(Rec7* out, uint32_t n, const Rec7* v); // 0x00a99410
    Rec7*   AllocCopyN(uint32_t n, const Rec7* first, const Rec7* last); // 0x00a9a250
    Rec7*   AllocMoveN(uint32_t n, const Rec7* first, const Rec7* last); // 0x00a9a2b0

    void    insert(Rec7* pos, uint32_t n, const Rec7& v);   // @ 0x00a99640
    void    resize(uint32_t n);                             // @ 0x00a99a10
    void    resizeZero(uint32_t n);                         // @ 0x00a99a90
    RecVec* reserveFill(const RecVec* src);                 // @ 0x00a9a310
    RecVec* reserveFill2(const RecVec* src);                // @ 0x00a9a370
    RecVec* assign(const RecVec& src);                      // @ 0x00a9a3d0
    RecVec* assignMove(const RecVec& src);                  // @ 0x00a9a500
};
static inline void FreeCounted(void* p) {
    if (p) {
        if (((int*)p)[-1] != 0)
            operator_delete_arr(p);
    }
}
struct Float6 {
    float v[6];
    void Shift(float dx, float dy, float dz);        // 0x00a9a1c0
};
// ---- items of slice s00a99640 end

// ---- items of slice s00a9a630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_004aa350(int n, const void* src);                // 0x4aa350
extern "C" void* __cdecl eastl_vector_insert(void* dst, const void* src,
                                             unsigned bytes);                // 0x11e0744
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)
typedef unsigned char byte;
struct cElem {
    float w;        // +0x00
    float m[3];     // +0x04
    float v[3];     // +0x10
};
struct cElemVec {
    cElem* m_begin;     // +0x00
    cElem* m_end;       // +0x04
    cElem* m_cap;       // +0x08

    void Insert(cElem* pos, const cElem* v);
    void push_back(const cElem* v);
};
struct cElemVector {
    cElem     m_elem;               // +0x00
    float*    m_begin;              // +0x1c
    float*    m_end;                // +0x20
    char      m_pad24[0x28 - 0x24];
    void*     m_alloc;              // +0x28
    char      m_pad2c[0x30 - 0x2c];
    byte      m_30;                 // +0x30

    cElemVector* operator=(const cElemVector* src);
};
// ---- items of slice s00a9a630 end

// ---- items of slice s00aa5940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char* strstr_s00aa_5940(const char* s, const char* sub);
namespace SP {
void BitDoInsertFloat(float* begin, float* end, int count);   // 0x011e0744
}
namespace SP {
template <class T> struct SimpleVector {
  T*  mpBegin;
  T*  mpEnd;
  T*  mpCapacity;
  void DoInsertValue(T* end, const T& v);
  void clear()
  {
    T* begin = mpBegin;
    T* end   = mpEnd;
    SP::BitDoInsertFloat((float*)begin, (float*)end, 0);
    int n = (int)end - (int)begin;
    mpEnd += -(n >> 2);
  }
  void push_back(const T& v)
  {
    T* end = mpEnd;
    if (end < mpCapacity) {
      mpEnd = end + 1;
      if (end) *end = v;
    } else {
      DoInsertValue(end, v);
    }
  }
};
}
namespace EA {
namespace ArgScript {
class cArguments_s00aa_5940 { public:
  const char** MainArguments(int* countOut, int minArgs, int maxArgs);  // 0x00838020 (EA::ArgScript::cArguments::MainArguments)
  const char** OptionArguments(const char* name, int minArgs);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
  const char** OptionArguments(const char* name, int* countOut, int minArgs, int maxArgs);  // 0x00838130 (EA::ArgScript::cArguments::OptionArguments)
  bool  HasFlag(const char* name);  // 0x008380b0 (EA::ArgScript::cArguments::HasFlag)
  const char* operator[](int index);
};
}
}
namespace EA {
namespace ArgScript {
struct cArgEval {
virtual void e00();
virtual void e01();
virtual void e02();
virtual void e03();
virtual void e04();
virtual void e05();
virtual void e06();
virtual void e07();
virtual void e08();
virtual void e09();
virtual void e10();
virtual void e11();
virtual void e12();
virtual void e13();
virtual void e14();
virtual void e15();
virtual void e16();
virtual void e17();
virtual void e18();
virtual void e19();
virtual void e20();
virtual void e21();
virtual void e22();
virtual void e23();
virtual void e24();
virtual void e25();
virtual void e26();
virtual void e27();
virtual void e28();
virtual void e29();
virtual void e30();
virtual void e31();
virtual void e32();
virtual void e33();
virtual void e34();
virtual void e35();
virtual void e36();
virtual void e37();
  virtual float Evaluate(const char* text);                    // +0x98
  virtual void  e39();
  virtual void  e40();
  virtual void  e41();
  virtual float* EvaluateVector(float* out, const char* text);// +0xa8
};
}
}
void FUN_00a9a7a0(float* v);         // 0x00a9a7a0 (wiggle transform setup)
float g_piOver180 = 0.017453292f;    // 0x01679348
float g_timeScale = 1.0f;            // 0x016792c0
float g_sinTable[32];                // 0x01677840 (16-entry sin/cos pairs)
float g_defaultGravity[3] = {0.0f, 0.0f, -1.0f};  // 0x016792c4
struct Desc {
  uint8_t p[0x280];

  template <class T> T& at(unsigned off) { return *(T*)(p + off); }
  SP::SimpleVector<float>* vec(unsigned off) { return (SP::SimpleVector<float>*)(p + off); }

  // eastl/SimpleVector<float> push_back: end at endOff, capacity at capOff.
  void pushFloat(unsigned endOff, unsigned capOff, float v)
  {
    (void)capOff;
    ((SP::SimpleVector<float>*)(p + endOff - 4))->push_back(v);
  }
  // Clear the float vector at [off,off+8): eastl::vector<bool>::DoInsertValue(
  // begin,end,0) followed by mpEnd = begin.
  void clearFloat(unsigned off)
  {
    SP::SimpleVector<float>* v = (SP::SimpleVector<float>*)(p + off);
    float* begin = v->mpBegin;
    float* end   = v->mpEnd;
    SP::BitDoInsertFloat(begin, end, 0);
    int n = (int)end - (int)begin;      // byte difference
    v->mpEnd += -(n >> 2);              // == begin
  }
};
struct cCommand {
  uint8_t  pad00[0x04];
  EA::ArgScript::cArgEval* mEval;      // +0x04
  uint8_t  pad08[0x04];
  Desc*    mDesc;       // +0x0c

  void ExecuteColor(EA::ArgScript::cArguments_s00aa_5940* args);
  void cParticleSizeExecute(EA::ArgScript::cArguments_s00aa_5940* args);
  void cParticleAspectExecute(EA::ArgScript::cArguments_s00aa_5940* args);
  void cParticleRotateExecute(EA::ArgScript::cArguments_s00aa_5940* args);
  void cParticleForceExecute(EA::ArgScript::cArguments_s00aa_5940* args);
  void cParticleWarpExecute(EA::ArgScript::cArguments_s00aa_5940* args);
  void cParticleLifeExecute(EA::ArgScript::cArguments_s00aa_5940* args);
};
// ---- items of slice s00aa5940 end

// ---- items of slice s00aa2f00 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA
{
namespace ArgScript
{
// cArguments: the ArgScript argument list a command is executed with (0x00838000 range).
class cArguments_s00aa_2f00
{ public:
    const char** MainArguments(int count);                       // 0x00838320
    const char** OptionArguments(const char* name, int count);    // 0x00838330
    const char** OptionArguments(const char* name, int* pCount, int min, int max);  // 0x00838130
    bool         HasFlag(const char* flag);                      // 0x008380b0
};

// The expression evaluator the parser uses to turn argument text into numbers.
struct cIArgEvaluator
{
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual float Float(const char* text);                       // +0x98
    PV(39)
    virtual int   Int(const char* text);                         // +0xa0
#undef PV
};
}  // namespace ArgScript
}  // namespace EA
void* operator new(unsigned int size, const char* name, int flags, int debugFlags,
                   const char* file, int line);
// ---- items of slice s00aa2f00 end

// ---- items of slice s00aa3a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float gShapeDefault[3];            // 0x016792c4
namespace EA {
namespace ArgScript {
class cIParser_s00aa_3a30 { public:
virtual void pv00();
virtual void pv01();
virtual void pv02();
virtual void pv03();
virtual void pv04();
virtual void pv05();
virtual void pv06();
virtual void pv07();
virtual void pv08();
virtual void pv09();
virtual void pv10();
virtual void pv11();
virtual void pv12();
virtual void pv13();
virtual void pv14();
virtual void pv15();
virtual void pv16();
virtual void pv17();
virtual void pv18();
virtual void pv19();
virtual void pv20();
virtual void pv21();
virtual void pv22();
virtual void pv23();
virtual void pv24();
virtual void pv25();
virtual void pv26();
virtual void pv27();
virtual void pv28();
virtual void pv29();
virtual void pv30();
virtual void pv31();
virtual void pv32();
virtual void pv33();
virtual void pv34();
virtual void pv35();
virtual void pv36();
virtual void pv37();
    virtual float  ParseFloat(const char* text);                    // +0x98
    virtual int    ParseInt(const char* text);                      // +0x9c
    virtual unsigned ParseUInt(const char* text);                   // +0xa0
    virtual float* ParseVector2(float* out, const char* text);      // +0xa4
    virtual float* ParseVector3(float* out, const char* text);      // +0xa8
};
}
}
namespace EA {
namespace ArgScript {
class cArguments_s00aa_3a30 { public:
    const char** MainArguments(int minCount) const;                                 // 0x838320
    const char** MainArguments(int* pCount, int minCount, int maxCount) const;      // 0x838020
    const char** OptionArguments(const char* name, int count) const;                // 0x838330
    const char** OptionArguments(const char* name, int* pCount, int minCount,
                                 int maxCount) const;                               // 0x838130
    bool HasFlag(const char* flag) const;                                           // 0x8380b0
};
}
}
using EA::ArgScript::cArguments_s00aa_3a30;
using EA::ArgScript::cIParser_s00aa_3a30;
struct Vector2_s00aa_3a30 { float x, y; };
struct Vector3_s00aa_3a30 {
    float x, y, z;
    void Set(float a, float b, float c);        // 0x00a9a1c0
    void SetSymmetric(float s);                 // 0x006e9910
    void From(const Vector3_s00aa_3a30& v);                // 0x00a93c60
};
#define FLT_MAX 3.402823466e+38f
// ---- items of slice s00aa3a30 end

// @ 0x00a99350
Elem1C* Elem1C_ctor_range(Elem1C** out, Elem1C* first, Elem1C* last, Elem1C* dst)
{
    *out = dst;
    if (first != last) {
        Elem1C* s = first;
        Elem1C* d = dst;
        do {
            if (d) *d = *s;
            ++s; ++d;
        } while (s != last);
        *out = d;
    }
    return dst;
}

// @ 0x00a993b0
Elem1C* Elem1C_ctor_range_off14(Elem1C** out, Elem1C* first, Elem1C* last, Elem1C* dst)
{
    *out = dst;
    if (first != last) {
        Elem1C* s = first;
        Elem1C* d = dst;
        do {
            if (d) *d = *s;
            ++s; ++d;
        } while (s != last);
        *out = d;
    }
    return dst;
}

// @ 0x00a9a1c0
void Float6::Shift(float dx, float dy, float dz)
{
    const float s = gSentinel_15653e0;
    if (v[0] == s || v[0] == -s)
        return;
    v[0] -= dx; v[1] -= dy; v[2] -= dz;
    v[3] += dx; v[4] += dy; v[5] += dz;
}

// @ 0x00a9a310
RecVec* RecVec::reserveFill(const RecVec* src)
{
    uint32_t n = src->size();
    reserve(n, &src->mpCap);
    RotateCopy(src->mpBegin, src->mpEnd, mpBegin, 0);
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00a9a370
RecVec* RecVec::reserveFill2(const RecVec* src)
{
    uint32_t n = src->size();
    reserve(n, &src->mpCap);
    RotateCopy2(src->mpBegin, src->mpEnd, mpBegin);
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00a9a3d0
RecVec* RecVec::assign(const RecVec& src)
{
    if (&src != this) {
        uint32_t n = src.size();
        if (capacity() < n) {
            Rec7* nw = AllocCopyN(n, src.mpBegin, src.mpEnd);
            FreeCounted(mpBegin);
            mpBegin = nw;
            mpCap = nw + n;
        } else if (size() < n) {
            uint32_t have = size();
            MoveRec7(src.mpBegin, src.mpBegin + have, mpBegin);
            RotateCopy(src.mpBegin + have, src.mpEnd, mpEnd, 0);
        } else {
            MoveRec7(src.mpBegin, src.mpEnd, mpBegin);
        }
        mpEnd = mpBegin + n;
    }
    return this;
}

// @ 0x00a9a500
RecVec* RecVec::assignMove(const RecVec& src)
{
    if (&src != this) {
        uint32_t n = src.size();
        if (capacity() < n) {
            Rec7* nw = AllocMoveN(n, src.mpBegin, src.mpEnd);
            FreeCounted(mpBegin);
            mpBegin = nw;
            mpCap = nw + n;
        } else if (size() < n) {
            uint32_t have = size();
            MoveRec7(src.mpBegin, src.mpBegin + have, mpBegin);
            RotateCopy2(src.mpBegin + have, src.mpEnd, mpEnd);
        } else {
            MoveRec7(src.mpBegin, src.mpEnd, mpBegin);
        }
        mpEnd = mpBegin + n;
    }
    return this;
}

// @ 0x00a9a7a0
void cElemVec::push_back(const cElem* v)
{
    cElem* p = m_end;
    if (p < m_cap) {
        m_end = (cElem*)((char*)p + 0x1c);
        if (p != 0) {
            p->w = v->w;
            p->m[0] = v->m[0];
            p->m[1] = v->m[1];
            p->m[2] = v->m[2];
            p->v[0] = v->v[0];
            p->v[1] = v->v[1];
            p->v[2] = v->v[2];
        }
        return;
    }
    Insert(p, v);
}

// @ 0x00a9a7f0
cElemVector* cElemVector::operator=(const cElemVector* src)
{
    m_elem = src->m_elem;
    FUN_004aa350((int)(src->m_end - src->m_begin) >> 2, src->m_alloc);
    unsigned bytes = (unsigned)((char*)src->m_end - (char*)src->m_begin);
    void* p = eastl_vector_insert(m_begin, src->m_begin, bytes);
    m_end = (float*)((char*)p + (bytes >> 2) * 4);
    m_30 = src->m_30;
    return this;
}

// @ 0x00aa2fe0
__declspec(noinline) float* ParseVector2(float* out, EA::ArgScript::cIArgEvaluator* evaluator, const char*** pArgs, int argCount)
{
    out[0] = evaluator->Float((*pArgs)[0]);
    if (argCount > 1)
        out[1] = evaluator->Float((*pArgs)[1]);
    else
        out[1] = out[0];
    return out;
}

// @ 0x00aa3040
void ParseParticleState(EA::ArgScript::cArguments_s00aa_2f00* args, cParticleState* state, EA::ArgScript::cIArgEvaluator* evaluator)
{
    int          argCount;
    const char** argv;
    uint16_t     mode;

    if ((argv = args->OptionArguments("loop", &argCount, 1, 2)) != 0)
    {
        state->mLoopTime = evaluator->Float(argv[0]);
        mode = (argCount > 1) ? (uint16_t)evaluator->Int(argv[1]) : 0;
    }
    else if ((argv = args->OptionArguments("single", &argCount, 0, 1)) != 0)
    {
        if (argCount <= 0)
            state->mLoopTime = kFloatHundredth;
        else
            state->mLoopTime = evaluator->Float(argv[0]);
        mode = 1;
    }
    else if ((argv = args->OptionArguments("sustain", &argCount, 1, 2)) != 0)
    {
        state->mFlags |= 4;
        state->mLoopTime = evaluator->Float(argv[0]);
        mode = (argCount > 1) ? (uint16_t)evaluator->Int(argv[1]) : 1;
    }
    else if ((argv = args->OptionArguments("hold", &argCount, 1, 2)) != 0)
    {
        state->mFlags |= 0x10000000;
        state->mLoopTime = evaluator->Float(argv[0]);
        mode = (argCount > 1) ? (uint16_t)evaluator->Int(argv[1]) : 1;
    }
    else if ((argv = args->OptionArguments("kill", &argCount, 1, 2)) != 0)
    {
        state->mFlags  |= 0x08000000;
        state->mFlags2 |= 1;
        state->mLoopTime = evaluator->Float(argv[0]);
        mode = (argCount > 1) ? (uint16_t)evaluator->Int(argv[1]) : 1;
    }
    else
    {
        goto flags;
    }
    state->mLoopMode = mode;

flags:
    if (args->HasFlag("sizeScale"))
        state->mFlags |= 0x100;
    if (args->HasFlag("areaScale"))
        state->mFlags |= 0x200;
    if (args->HasFlag("volumeScale"))
        state->mFlags |= 0x400;

    if ((argv = args->OptionArguments("speedScale", 1)) != 0)
        state->mSpeedScale = evaluator->Float(argv[0]);

    if ((argv = args->OptionArguments("delay", &argCount, 1, 0x7fffffff)) != 0)
    {
        float v[2];
        ParseVector2(v, evaluator, &argv, argCount);
        state->mDelay.x = v[0];
        state->mDelay.y = v[1];
    }
    if ((argv = args->OptionArguments("trigger", &argCount, 1, 0x7fffffff)) != 0)
    {
        float v[2];
        ParseVector2(v, evaluator, &argv, argCount);
        state->mTrigger.x = v[0];
        state->mTrigger.y = v[1];
    }
}

// @ 0x00aa32b0
void* CreateParticlesEffectCommand(int flags)
{
    cGroupParticlesCommand* cmd = new ("ArgScript/GroupParticles", 0, 0, 0, 0)
        cGroupParticlesCommand(flags);
    if (cmd)
        return cmd;
    return 0;
}

// @ 0x00aa32f0
cParticlesDescription::~cParticlesDescription()
{
}

// @ 0x00aa3460
cParticlesDescription::cParticlesDescription()
{
    mFlags        = 0;
    mFlags2       = 0;
    mMinSize      = kFloat2;
    mMaxSize      = kFloat2;
    mf018         = 0.0f;
    mEmitDelay.x  = kFloatMinus1;
    mEmitDelay.y  = kFloatMinus1;
    mTrigger.x    = kFloatMinus1;
    mTrigger.y    = kFloatMinus1;
    mf02c         = 0.0f;
    mf030         = 0.0f;
    mf034         = kFloat1;
    mf038         = 0.0f;
    mf03c         = 0.0f;
    mf040         = kFloat1;
    mf044         = 0.0f;
    mf048         = 0.0f;
    mf04c         = 0.0f;
    mf050         = 0.0f;
    mf054         = 0.0f;
    mf058         = 0.0f;
    mf05c         = 0.0f;
    mf060         = 0.0f;
    mf064         = kFloatMinus1;
    mf07c         = kFloat1;
    mMode         = 0;
    mf084         = 0.0f;
    mf09c         = 0.0f;
    mf0b4         = 0.0f;
    mf0cc         = 0.0f;
    mf0d0         = 0.0f;
    mColorVary    = gDefaultVector;
    mf108         = 0.0f;
    mi110         = -1;
    mi114         = -1;
    mB118[0]      = 0;
    mB118[1]      = 0;
    mB118[2]      = 0;
    mB118[3]      = 0;
    mW11c         = 0;
    mf120         = 0.0f;
    mi128         = -1;
    mi12c         = -1;
    mB130         = 0;
    mB131         = 0;
    mB132         = 1;
    mB133         = 1;
    mB134         = 0;
    mB135         = 0;
    mB136         = 0;
    mB137         = 0;
    mf138         = 0.0f;
    mV13c         = gDefaultVector;
    mf148         = 0.0f;
    mf14c         = 0.0f;
    mf150         = 0.0f;
    mV154         = gDefaultVector;
    mf160         = 0.0f;
    mf164         = 0.0f;
    mf168         = 0.0f;
    mB180         = 0;
    mB181         = 0xff;
    mB182         = 0;
    mB183         = 0xff;
    mf1c0         = kFloat1;
    mf1c4         = 0.0f;
    mf1c8         = 0.0f;
    mf1cc         = 0.0f;
    mf1d0         = 0.0f;
    mf1d4         = kFloatNeg1e9;
    mf1d8         = 0.0f;
    mf1dc         = kFloatNeg1e4;
    mf1e0         = kFloatPos1e4;
    mi1e8         = -1;
    mi1ec         = -1;
    mi1f0         = -1;
    mi1f4         = -1;
    mi1f8         = -1;
    mi1fc         = -1;
    mf200         = kFloat5;
    mf204         = kFloat5;
    mf208         = 0.0f;
    mf20c         = 0.0f;
    mf210         = kFloatQuarter;
    mf214         = 0.0f;
    mf218         = 0.0f;
    mB230         = 2;
    mV234         = gDefaultVector;
    mf254         = kFloat1;
    mf258         = 0.0f;

    mRateCurve.push_back(kFloat30);
    mColorCurve.push_back(gDefaultVector);
    mAlphaCurve.push_back(kFloat1);
    mSizeCurve.push_back(kFloat1);
    mAspectCurve.push_back(kFloat1);
    mRotationCurve.push_back(0.0f);
}

// @ 0x00aa3a30
#define cParticleSourceCommand cParticleSourceCommand_s00aa_3a30
void cParticleSourceCommand::Execute(cArguments_s00aa_3a30& args)
{
    args.MainArguments(0);

    Vector3_s00aa_3a30 vMin, vMax;
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
            Vector2_s00aa_3a30 q;
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
        Vector3_s00aa_3a30 o;
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
#undef cParticleSourceCommand

// @ 0x00aa3f30
#define cParticleEmitCommand cParticleEmitCommand_s00aa_3a30
void cParticleEmitCommand::Execute(cArguments_s00aa_3a30& args)
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
        Vector3_s00aa_3a30 d;
        mParser->ParseVector3(&d.x, a[0]);
        Vector3_s00aa_3a30 e;
        e.x = gShapeDefault[0];
        e.y = gShapeDefault[1];
        e.z = gShapeDefault[2];
        if (n > 1)
            e = *(Vector3_s00aa_3a30*)mParser->ParseVector3(&e.x, a[1]);

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
#undef cParticleEmitCommand

// @ 0x00aa4180
#define cParticleForceCommand cParticleForceCommand_s00aa_3a30
void cParticleForceCommand::Execute(cArguments_s00aa_3a30& args)
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
#undef cParticleForceCommand

// @ 0x00aa43c0
#define cParticleLifeCommand cParticleLifeCommand_s00aa_3a30
void cParticleLifeCommand::Execute(cArguments_s00aa_3a30& args)
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
#undef cParticleLifeCommand

// @ 0x00aa44f0
#define cParticleTextureCommand cParticleTextureCommand_s00aa_3a30
void cParticleTextureCommand::Execute(cArguments_s00aa_3a30& args)
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
#undef cParticleTextureCommand

// @ 0x00aa45a0
#define cParticleFramesCommand cParticleFramesCommand_s00aa_3a30
void cParticleFramesCommand::Execute(cArguments_s00aa_3a30& args)
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
#undef cParticleFramesCommand

// @ 0x00aa46e0
#define cParticleModelCommand cParticleModelCommand_s00aa_3a30
void cParticleModelCommand::Execute(cArguments_s00aa_3a30& args)
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
#undef cParticleModelCommand

// @ 0x00aa47e0
#define cParticleRateCommand cParticleRateCommand_s00aa_3a30
void cParticleRateCommand::Execute(cArguments_s00aa_3a30& args)
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
#undef cParticleRateCommand

// @ 0x00aa48e0
#define cParticleSurfaceCommand cParticleSurfaceCommand_s00aa_3a30
void cParticleSurfaceCommand::Execute(cArguments_s00aa_3a30& args)
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
#undef cParticleSurfaceCommand

// @ 0x00aa4a10
void cParticleModelCommand::Execute(EA::ArgScript::cArguments_s00aa_4a10& args)
{
    const char** argv = args.MainArguments(1);
    mState->mMapID = mState->mpParser->EffectsMapID(argv[0]);
}

// @ 0x00aa4a50
namespace
{
void cParticleSourceCommand::Execute(EA::ArgScript::cArguments_s00aa_4a10& args)
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
}

// @ 0x00aa4b60
namespace
{
void cParticleEmitCommand::Execute(EA::ArgScript::cArguments_s00aa_4a10& args)
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
}

// @ 0x00aa4cc0
namespace
{
void cParticleForceCommand::Execute(EA::ArgScript::cArguments_s00aa_4a10& args)
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
}

// @ 0x00aa4d70
namespace
{
void cParticleWarpCommand::Execute(EA::ArgScript::cArguments_s00aa_4a10& args)
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
}

// @ 0x00aa4e50
namespace
{
void cParticleEffectCommand::OnRegister(EA::ArgScript::cIParser_s00aa_4a10* parser, EA::ArgScript::cState_s00aa_4a10* state)
{
    mState = state ? (EA::Swarm::cEffectsParser*)((char*)state - 0xc) : 0;
    EA::ArgScript::cBlockCommandBase::OnRegister(parser, state);
    SetChildState((EA::ArgScript::cState_s00aa_4a10*)((char*)this + 0x38));
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
}

// @ 0x00aa5810
namespace
{
void cParticleAlphaCommand::Execute(EA::ArgScript::cArguments_s00aa_4a10& args)
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
    if (strstr_s00aa_4a10(name, "255"))
        FUN_007ecc30(&mState->mCurves, 0.0039215689f);
}
}

// @ 0x00aa5940
void cCommand::ExecuteColor(EA::ArgScript::cArguments_s00aa_5940* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0xfc);

  for (int i = 0; i < count; ++i)
    d->pushFloat(0x100, 0x104, mEval->Evaluate(main[i]));

  const char** opt = args->OptionArguments("vary", 1);
  if (opt)
    d->at<float>(0x110) = ParseRangedFloat(mEval, *opt, 0.0f, 1.0f);

  const char* a0 = (*args)[0];
  if (a0 && strstr_s00aa_5940(a0, "255")) {
    float* begin = d->at<float*>(0xfc);
    int n = (int)(d->at<float*>(0x100) - begin);
    for (int i = 0; i < n; ++i)
      begin[i] = begin[i] * 0.003921569f;
  }
}

// @ 0x00aa5ab0
void cCommand::cParticleSizeExecute(EA::ArgScript::cArguments_s00aa_5940* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0x90);

  for (int i = 0; i < count; ++i)
    d->vec(0x90)->push_back(mEval->Evaluate(main[i]));

  const char** opt = args->OptionArguments("vary", 1);
  if (opt)
    d->at<float>(0xa4) = ParseRangedFloat(mEval, *opt, 0.0f, 1.0f);
}

// @ 0x00aa5bb0
void cCommand::cParticleAspectExecute(EA::ArgScript::cArguments_s00aa_5940* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0xa8);

  for (int i = 0; i < count; ++i)
    d->pushFloat(0xac, 0xb0, mEval->Evaluate(main[i]));

  const char** opt = args->OptionArguments("vary", 1);
  if (opt)
    d->at<float>(0xbc) = ParseRangedFloat(mEval, *opt, 0.0f, 1.0f);
}

// @ 0x00aa5cb0
void cCommand::cParticleRotateExecute(EA::ArgScript::cArguments_s00aa_5940* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 1, 0x7fffffff);
  Desc* d = mDesc;

  d->clearFloat(0xc0);

  for (int i = 0; i < count; ++i)
    d->pushFloat(0xc4, 0xc8, mEval->Evaluate(main[i]));

  const char** opt = args->OptionArguments("vary", 1);
  if (opt)
    d->at<float>(0xd4) = ParseRangedFloat(mEval, *opt, 0.0f, 1.0f);

  const char** off = args->OptionArguments("offset", 2);
  if (off)
    d->at<float>(0xd8) = mEval->Evaluate(*off);
}

// @ 0x00aa5de0
void cCommand::cParticleForceExecute(EA::ArgScript::cArguments_s00aa_5940* args)
{
  args->MainArguments((int*)0, 0, 0);
  Desc* d = mDesc;

  if (args->HasFlag("reset")) {
    d->at<float>(0x144) = g_defaultGravity[0];
    d->at<float>(0x148) = g_defaultGravity[1];
    d->at<float>(0x14c) = g_defaultGravity[2];
  }

  {
    const char** g = args->OptionArguments("gravity", 1);
    if (g)
      d->at<float>(0x14c) = d->at<float>(0x14c) - mEval->Evaluate(*g);
  }

  {
    int cnt = 0;
    const char** dir = args->OptionArguments("wind", &cnt, 1, 0x7fffffff);
    if (dir) {
      float tmp[3];
      float* v = mEval->EvaluateVector(tmp, *dir);
      float inv = 1.0f / sqrtf_s00aa_5940(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-08f);
      float x = v[0] * inv, y = v[1] * inv, z = v[2] * inv;
      if (cnt > 1) {
        float s = mEval->Evaluate(dir[1]);
        x *= s; y *= s; z *= s;
      }
      d->at<float>(0x144) += x;
      d->at<float>(0x148) += y;
      d->at<float>(0x14c) += z;
    }
  }

  {
    const char** ww = args->OptionArguments("worldWind", 1);
    if (ww)
      d->at<float>(0x150) = mEval->Evaluate(*ww);
  }
  {
    const char** wg = args->OptionArguments("worldGravity", 1);
    if (wg)
      d->at<float>(0x154) = mEval->Evaluate(*wg);
  }
  {
    int cnt = 0;
    const char** air = args->OptionArguments("bomb", &cnt, 1, 2);
    if (air) {
      d->at<float>(0x158) = mEval->Evaluate(*air);
      if (cnt > 1) {
        float tmp[3];
        float* v = mEval->EvaluateVector(tmp, air[1]);
        d->at<float>(0x15c) = v[0];
        d->at<float>(0x160) = v[1];
        d->at<float>(0x164) = v[2];
      }
    }
  }
  {
    int cnt = 0;
    const char** bf = args->OptionArguments("drag", &cnt, 1, 2);
    if (bf)
      d->at<float>(0x168) = mEval->Evaluate(*bf);
  }

  int have = 0;
  const char** rest = 0;
  {
    int cnt = 0;
    const char** at = args->OptionArguments("attractor", &cnt, 3, 0x7fffffff);
    if (at) {
      float tmp[3];
      float* v = mEval->EvaluateVector(tmp, *at);
      d->at<float>(0x23c) = v[0];
      d->at<float>(0x240) = v[1];
      d->at<float>(0x244) = v[2];
      have = cnt - 1;
      rest = at + 1;
    } else {
      int c2 = 0;
      rest = args->OptionArguments("presetAttractor", &c2, 2, 0x7fffffff);
      if (!rest)
        return;
      have = c2;
    }
  }

  d->at<float>(0x25c) = mEval->Evaluate(*rest);
  d->clearFloat(0x248);

  for (int i = 1; i < have; ++i)
    d->pushFloat(0x24c, 0x250, mEval->Evaluate(rest[i]));

  d->at<uint32_t>(0x10) |= 0x800000;
  if (have > 0)
    d->at<uint32_t>(0x10) |= 0x1000000;
  else
    d->at<uint32_t>(0x10) &= ~0x1000000u;

  {
    const char** kr = args->OptionArguments("killRange", 1);
    if (kr)
      d->at<float>(0x260) = mEval->Evaluate(*kr);
  }
}

// @ 0x00aa61c0
void cCommand::cParticleWarpExecute(EA::ArgScript::cArguments_s00aa_5940* args)
{
  args->MainArguments((int*)0, 0, 0);
  Desc* d = mDesc;

  {
    const char** s = args->OptionArguments("screw", 1);
    if (s)
      d->at<float>(0x170) = mEval->Evaluate(*s);
  }
  {
    const char** sp = args->OptionArguments("spiral", 1);
    if (sp) {
      d->at<float>(0x170) = mEval->Evaluate(*sp);
      d->at<uint32_t>(0x10) |= 0x20000000;
    }
  }
  {
    const char** w = args->OptionArguments("wiggle", 4);
    if (w) {
      float amp = mEval->Evaluate(w[0]);
      float freq = mEval->Evaluate(w[1]);
      float phase = mEval->Evaluate(w[2]);
      float rnd = ParseRangedFloat(mEval, w[3], 0.0f, 1.0f);

      float scaled = g_timeScale * (0.5f * rnd) + 12582912.0f;
      uint32_t idx = (uint32_t)scaled & 0xf;
      float sc = g_sinTable[idx * 2];
      float cc = g_sinTable[idx * 2 + 1];
      float frac = 0.5f * rnd - (float)((int)scaled - 0x4b400000) * g_piOver180;

      float w1 = -(((cc - (sc * frac) * 0.5f) * frac + sc) * phase);
      float w2 = (cc - ((cc * frac) * 0.5f + sc) * frac) * phase;

      float wig[5];
      wig[0] = amp;   // amplitude
      wig[1] = freq;  // frequency
      wig[2] = 0.0f;
      wig[3] = w2;
      wig[4] = w1;
      (void)frac;
      FUN_00a9a7a0(wig);
    }
  }
  {
    int cnt = 0;
    const char** wd = args->OptionArguments("wiggleDir", &cnt, 2, 3);
    if (wd) {
      float x = mEval->Evaluate(wd[0]);
      float tmp[3];
      float* v = mEval->EvaluateVector(tmp, wd[1]);
      float dir[3];
      dir[0] = v[0]; dir[1] = v[1]; dir[2] = v[2];
      float axis[3];
      axis[0] = g_defaultGravity[0];
      axis[1] = g_defaultGravity[1];
      axis[2] = g_defaultGravity[2];
      if (cnt > 2) {
        float t2[3];
        float* v2 = mEval->EvaluateVector(t2, wd[2]);
        axis[0] = v2[0]; axis[1] = v2[1]; axis[2] = v2[2];
      }
      (void)x;
      FUN_00a9a7a0(dir);
    }
  }
  {
    const char** ba = args->OptionArguments("bloomAlpha", 2);
    if (ba) {
      float v0 = mEval->Evaluate(ba[0]);
      float c0 = v0 < 0.0f ? 0.0f : v0;
      c0 *= 255.0f;
      if (c0 > 255.0f) c0 = 255.0f;
      d->at<uint8_t>(0x189) = (uint8_t)(int)(c0 + 0.5f);

      float v1 = mEval->Evaluate(ba[1]) * 0.0625f;
      float c1 = v1 < 0.0f ? 0.0f : v1;
      c1 *= 255.0f;
      if (c1 > 255.0f) c1 = 255.0f;
      d->at<uint8_t>(0x188) = (uint8_t)(int)(c1 + 0.5f);
    }
  }
  {
    const char** bs = args->OptionArguments("bloomSize", 2);
    if (bs) {
      float v0 = mEval->Evaluate(bs[0]);
      float c0 = v0 < 0.0f ? 0.0f : v0;
      c0 *= 255.0f;
      if (c0 > 255.0f) c0 = 255.0f;
      d->at<uint8_t>(0x18b) = (uint8_t)(int)(c0 + 0.5f);

      float v1 = mEval->Evaluate(bs[1]) * 0.0625f;
      float c1 = v1 < 0.0f ? 0.0f : v1;
      c1 *= 255.0f;
      if (c1 > 255.0f) c1 = 255.0f;
      d->at<uint8_t>(0x18a) = (uint8_t)(int)(c1 + 0.5f);
    }
  }
}

// @ 0x00aa6590
void cCommand::cParticleLifeExecute(EA::ArgScript::cArguments_s00aa_5940* args)
{
  int count = 0;
  const char** main = args->MainArguments(&count, 0, 0x7fffffff);
  Desc* d = mDesc;

  for (int i = 0; i < count; ++i)
    d->pushFloat(0x228, 0x22c, ParseRangedFloat(mEval, main[i], -1.0f, 1.0f));

  d->at<uint32_t>(0x10) |= 0x80000;

  {
    int cnt = 0;
    const char** dl = args->OptionArguments("delay", &cnt, 1, 2);
    if (dl) {
      float lo = mEval->Evaluate(dl[0]);
      float hi = 0.0f;
      if (cnt > 1)
        hi = mEval->Evaluate(dl[1]);
      d->at<float>(0x208) = lo - hi;
      d->at<float>(0x20c) = lo + hi;
    }
  }
  {
    int cnt = 0;
    const char** st = args->OptionArguments("strength", &cnt, 1, 2);
    if (st) {
      float lo = mEval->Evaluate(st[0]);
      float hi = 0.0f;
      if (cnt > 1)
        hi = mEval->Evaluate(st[1]);
      d->at<float>(0x210) = lo - hi;
      d->at<float>(0x214) = lo + hi;
    }
  }
  {
    int cnt = 0;
    const char** rt = args->OptionArguments("randomTurn", &cnt, 1, 0x7fffffff);
    if (!rt) {
      d->at<uint32_t>(0x218) = 0;
      d->at<uint32_t>(0x21c) = 0;
    } else {
      d->at<float>(0x218) = ParseRangedFloat(mEval, rt[0], 0.0f, 1.0f);
      if (cnt < 2)
        d->at<uint32_t>(0x21c) = 0;
      else
        d->at<float>(0x21c) = ParseRangedFloat(mEval, rt[1], 0.0f, 1.0f);
    }
  }

  d->at<uint8_t>(0x238) = 2;
  if (args->HasFlag("sustain"))
    d->at<uint8_t>(0x238) = 1;
  if (args->HasFlag("loop"))
    d->at<uint8_t>(0x238) = 0;

  {
    const char** ir = args->OptionArguments("mix", 1);
    if (ir)
      d->at<float>(0x220) = ParseRangedFloat(mEval, *ir, 0.0f, 1.0f);
  }

  if (args->HasFlag("wait"))
    d->at<uint32_t>(0x10) |= 0x100000;
}

// @ 0x00aa7470
Self* Self::FUN_00aa7470(const Self* o)
{
    char* t = raw;
    const char* q = o->raw;
    *(int*)(t + 8)   = *(const int*)(q + 8);
    *(int*)(t + 0xc) = *(const int*)(q + 0xc);
    *(int*)(t + 0x10)= *(const int*)(q + 0x10);
    *(int*)(t + 0x14)= *(const int*)(q + 0x14);
    *(float*)(t + 0x18) = *(const float*)(q + 0x18);
    *(int*)(t + 0x1c)= *(const int*)(q + 0x1c);
    *(int*)(t + 0x20)= *(const int*)(q + 0x20);
    *(int*)(t + 0x24)= *(const int*)(q + 0x24);
    *(int*)(t + 0x28)= *(const int*)(q + 0x28);
    *(int*)(t + 0x38)= *(const int*)(q + 0x38);
    *(int*)(t + 0x3c)= *(const int*)(q + 0x3c);
    *(int*)(t + 0x40)= *(const int*)(q + 0x40);
    *(int*)(t + 0x2c)= *(const int*)(q + 0x2c);
    *(int*)(t + 0x30)= *(const int*)(q + 0x30);
    *(int*)(t + 0x34)= *(const int*)(q + 0x34);
    *(int*)(t + 0x44)= *(const int*)(q + 0x44);
    *(int*)(t + 0x48)= *(const int*)(q + 0x48);
    *(int*)(t + 0x58)= *(const int*)(q + 0x58);
    *(int*)(t + 0x5c)= *(const int*)(q + 0x5c);
    *(int*)(t + 0x60)= *(const int*)(q + 0x60);
    *(int*)(t + 0x4c)= *(const int*)(q + 0x4c);
    *(int*)(t + 0x50)= *(const int*)(q + 0x50);
    *(int*)(t + 0x54)= *(const int*)(q + 0x54);
    *(float*)(t + 0x64) = *(const float*)(q + 0x64);
    ((XOp*)(t + 0x68))->FUN_0050d4e0(q + 0x68);
    *(float*)(t + 0x7c) = *(const float*)(q + 0x7c);
    *(short*)(t + 0x80) = *(const short*)(q + 0x80);
    *(float*)(t + 0x84) = *(const float*)(q + 0x84);
    ((XOp*)(t + 0x88))->FUN_0050d4e0(q + 0x88);
    *(float*)(t + 0x9c) = *(const float*)(q + 0x9c);
    ((XOp*)(t + 0xa0))->FUN_0050d4e0(q + 0xa0);
    *(float*)(t + 0xb4) = *(const float*)(q + 0xb4);
    ((XOp*)(t + 0xb8))->FUN_0050d4e0(q + 0xb8);
    *(float*)(t + 0xcc) = *(const float*)(q + 0xcc);
    *(float*)(t + 0xd0) = *(const float*)(q + 0xd0);
    ((XOp*)(t + 0xd4))->FUN_006f5cd0(q + 0xd4);
    *(int*)(t + 0xe8)= *(const int*)(q + 0xe8);
    *(int*)(t + 0xec)= *(const int*)(q + 0xec);
    *(int*)(t + 0xf0)= *(const int*)(q + 0xf0);
    ((XOp*)(t + 0xf4))->FUN_0050d4e0(q + 0xf4);
    *(float*)(t + 0x108) = *(const float*)(q + 0x108);
    {
        struct Blk32 { int v[8]; };
        *(Blk32*)(t + 0x110) = *(const Blk32*)(q + 0x110);
    }
    *(unsigned char*)(t + 0x130) = *(const unsigned char*)(q + 0x130);
    *(unsigned char*)(t + 0x131) = *(const unsigned char*)(q + 0x131);
    *(unsigned char*)(t + 0x132) = *(const unsigned char*)(q + 0x132);
    *(unsigned char*)(t + 0x133) = *(const unsigned char*)(q + 0x133);
    *(unsigned char*)(t + 0x134) = *(const unsigned char*)(q + 0x134);
    *(unsigned char*)(t + 0x135) = *(const unsigned char*)(q + 0x135);
    *(unsigned char*)(t + 0x136) = *(const unsigned char*)(q + 0x136);
    *(unsigned char*)(t + 0x137) = *(const unsigned char*)(q + 0x137);
    *(float*)(t + 0x138) = *(const float*)(q + 0x138);
    *(int*)(t + 0x13c)= *(const int*)(q + 0x13c);
    *(int*)(t + 0x140)= *(const int*)(q + 0x140);
    *(int*)(t + 0x144)= *(const int*)(q + 0x144);
    *(float*)(t + 0x148) = *(const float*)(q + 0x148);
    *(float*)(t + 0x14c) = *(const float*)(q + 0x14c);
    *(float*)(t + 0x150) = *(const float*)(q + 0x150);
    *(int*)(t + 0x154)= *(const int*)(q + 0x154);
    *(int*)(t + 0x158)= *(const int*)(q + 0x158);
    *(int*)(t + 0x15c)= *(const int*)(q + 0x15c);
    *(float*)(t + 0x160) = *(const float*)(q + 0x160);
    *(float*)(t + 0x164) = *(const float*)(q + 0x164);
    *(float*)(t + 0x168) = *(const float*)(q + 0x168);
    ((XOp*)(t + 0x16c))->FUN_00a9a3d0(q + 0x16c);
    *(unsigned char*)(t + 0x180) = *(const unsigned char*)(q + 0x180);
    *(unsigned char*)(t + 0x181) = *(const unsigned char*)(q + 0x181);
    *(unsigned char*)(t + 0x182) = *(const unsigned char*)(q + 0x182);
    *(unsigned char*)(t + 0x183) = *(const unsigned char*)(q + 0x183);
    ((XOp*)(t + 0x184))->FUN_006f5cd0(q + 0x184);
    ((XOp*)(t + 0x198))->FUN_0050d4e0(q + 0x198);
    ((XOp*)(t + 0x1ac))->FUN_00a87b90(q + 0x1ac);
    *(float*)(t + 0x1c0) = *(const float*)(q + 0x1c0);
    *(float*)(t + 0x1c4) = *(const float*)(q + 0x1c4);
    *(float*)(t + 0x1c8) = *(const float*)(q + 0x1c8);
    *(float*)(t + 0x1cc) = *(const float*)(q + 0x1cc);
    *(float*)(t + 0x1d0) = *(const float*)(q + 0x1d0);
    *(float*)(t + 0x1d4) = *(const float*)(q + 0x1d4);
    *(float*)(t + 0x1d8) = *(const float*)(q + 0x1d8);
    *(int*)(t + 0x1dc)= *(const int*)(q + 0x1dc);
    *(int*)(t + 0x1e0)= *(const int*)(q + 0x1e0);
    *(int*)(t + 0x1e8)= *(const int*)(q + 0x1e8);
    *(int*)(t + 0x1ec)= *(const int*)(q + 0x1ec);
    *(int*)(t + 0x1f0)= *(const int*)(q + 0x1f0);
    *(int*)(t + 0x1f4)= *(const int*)(q + 0x1f4);
    *(int*)(t + 0x1f8)= *(const int*)(q + 0x1f8);
    *(int*)(t + 0x1fc)= *(const int*)(q + 0x1fc);
    *(int*)(t + 0x200)= *(const int*)(q + 0x200);
    *(int*)(t + 0x204)= *(const int*)(q + 0x204);
    *(int*)(t + 0x208)= *(const int*)(q + 0x208);
    *(int*)(t + 0x20c)= *(const int*)(q + 0x20c);
    *(float*)(t + 0x210) = *(const float*)(q + 0x210);
    *(float*)(t + 0x214) = *(const float*)(q + 0x214);
    *(float*)(t + 0x218) = *(const float*)(q + 0x218);
    ((XOp*)(t + 0x21c))->FUN_0050d4e0(q + 0x21c);
    *(unsigned char*)(t + 0x230) = *(const unsigned char*)(q + 0x230);
    *(int*)(t + 0x234)= *(const int*)(q + 0x234);
    *(int*)(t + 0x238)= *(const int*)(q + 0x238);
    *(int*)(t + 0x23c)= *(const int*)(q + 0x23c);
    {
        const char* op = q + 0x240;
        char* tp = t + 0x240;
        ((XOp*)tp)->FUN_0050d4e0(op);
        *(float*)(tp + 0x14) = *(const float*)(op + 0x14);
        *(float*)(tp + 0x18) = *(const float*)(op + 0x18);
    }
    ((XOp*)(t + 0x25c))->FUN_00a9a500(q + 0x25c);
    return this;
}

// @ 0x00aa7910
void Self::FUN_00aa7910(void* args)
{
    char* s = raw;
    CArgs* ca = (CArgs*)args;

    // local surface-options block (0x58 bytes)
    union { unsigned int u; float f; } cvt;
    unsigned int opts[0x58 / 4];
    opts[0x00/4] = 0;
    opts[0x08/4] = 0xffffffffu;
    opts[0x0c/4] = 0xffffffffu;
    cvt.f = 1.0f; opts[0x10/4] = cvt.u;
    opts[0x14/4] = cvt.u;
    opts[0x18/4] = 0;
    opts[0x1c/4] = 0;
    opts[0x20/4] = 0;
    opts[0x24/4] = cvt.u;
    opts[0x28/4] = 0;
    opts[0x2c/4] = 0;
    opts[0x30/4] = 0;
    cvt.u = 0xce6e6b28u; opts[0x34/4] = cvt.u;
    opts[0x38/4] = 0xffffffffu;
    opts[0x3c/4] = 0xffffffffu;
    opts[0x40/4] = 0;
    opts[0x44/4] = 0;
    opts[0x48/4] = 0;

    void* mainArgs = ca->MainArguments(1);

    if (ca->HasFlag(DAT_014119cc) != 0) {
        char* iv = *(char**)(s + 0xc);
        int end   = *(int*)(iv + 0x1b8);
        int begin = *(int*)(iv + 0x1b4);
        int r = FUN_00a87470(end, end, begin);
        ((XOp*)(iv + 0x1b4))->FUN_00a87300(r, *(int*)(iv + 0x1b8));
        int diff = end - begin;
        int q = diff / 0x58;
        *(int*)(iv + 0x1b8) += q * 0x58;
    }

    FUN_00a7d280(*(void**)mainArgs, args, opts, *(void**)(*(char**)(s + 0xc) + 0x278));

    {
        char* iv = *(char**)(s + 0xc);
        int  e = *(int*)(iv + 0x1b8);
        int  cap = *(int*)(iv + 0x1bc);
        if ((unsigned)e < (unsigned)cap) {
            *(int*)(iv + 0x1b8) = e + 0x58;
            if (e != 0)
                ((XOp*)e)->FUN_00a87280(opts);
        } else {
            ((XOp*)(iv + 0x1b4))->FUN_00a87d20((void*)e, opts);
        }
        *(unsigned int*)(iv + 0x10) |= 0x1000u;
    }

    {
        int p = (int)opts[0x40/4];
        if (p != 0 && *(int*)(p - 4) != 0)
            operator_delete__((void*)p);
    }
}

// @ 0x00aa7a80
void Self::FUN_00aa7a80(void* args)
{
    char* s = raw;
    CArgs* ca = (CArgs*)args;
    int count = 0;
    char cmdspace[0x260];

    void* puVar2 = ca->MainArgumentsX(&count, 1, 3);

    const char* pcVar1 = *(const char**)puVar2;
    const char* pcVar3;
    do { pcVar3 = pcVar1; pcVar1 = pcVar3 + 1; } while (*pcVar3 != '\0');

    ((StrAssign*)(s + 0x2b8))->FUN_00454cb0(*(const char**)puVar2, pcVar3);

    void* cmd = ((CmdObj*)cmdspace)->FUN_00aa3460();
    ((Self*)(s + 0x40))->FUN_00aa7470((const Self*)cmd);
    ((CmdObj*)cmdspace)->FUN_00aa32f0();

    s[0x2c8] = 0;
    s[0x2c9] = 0;

    if (count > 1) {
        void* desc = ((Parser*)(*(void**)(s + 0x30)))->FUN_00a6f090(puVar2, count, *(void**)(s + 0x34));
        if (desc != 0)
            ((Self*)(s + 0x40))->FUN_00aa7470((const Self*)desc);
    }

    void* o = *(void**)(s + 4);
    ((void(__thiscall*)(void*, void*))VTP(o, 0x8c))(o, this);
}
