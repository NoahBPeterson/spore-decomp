// EA::Swarm effects/particles description helpers (state 4 of Spore's Swarm module).
// Recovered from Swarm/ParticlesDescription.obj: the particle-effect command factory, the
// argument parser shared by the particle commands, and the cParticlesDescription object
// itself (constructor / destructor) plus the small keyword-registration and vector-parse
// helpers they use.

#include "types.h"

namespace EA
{
namespace ArgScript
{
// cArguments: the ArgScript argument list a command is executed with (0x00838000 range).
struct cArguments
{
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

void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void* operator new(unsigned int size, const char* name, int flags, int debugFlags,
                   const char* file, int line);

namespace EA
{
namespace Swarm
{
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };

void __cdecl operator delete(void* p) throw();                    // 0x00f47380

struct SimpleVectorF                       // SP::SimpleVector<float>
{
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    SimpleVectorF() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __declspec(nothrow) ~SimpleVectorF();
    void push_back(float value);
    void DoInsertValue(float* pEnd, const float& value);        // grow (0x00455660)
};
struct SimpleVectorV3                      // SP::SimpleVector<Vector3>
{
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    SimpleVectorV3() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __declspec(nothrow) ~SimpleVectorV3();
    void push_back(const Vector3& value);
    void Insert(Vector3* pEnd, const Vector3& value);           // grow (ScaleCurve, 0x007ed1b0)
};
struct SimpleVectorW
{
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    SimpleVectorW() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};

// Runtime-initialised global defaults (0x016792c4 / 0x01679158 in the binary).
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

// ---------------------------------------------------------------------------------------
// Emitted particle (0x50-byte object created by the <effect> factory and filled from a
// stream): two int range pairs, a colour and a few curve handles.
struct cEmittedParticleBase                   // +0x04 reference count, no vtable of its own
{
    int mBase;
    cEmittedParticleBase() : mBase(0) {}
};

struct cIntField                             // plain 4-byte field with a zeroing ctor
{
    int mValue;
    cIntField() : mValue(0) {}
    cIntField(int v) : mValue(v) {}
    operator int() const { return mValue; }
    cIntField& operator=(int v) { mValue = v; return *this; }
};

struct cEmittedParticle : cEmittedParticleBase
{
    virtual ~cEmittedParticle();

    cIntField mf08;                          // +0x08
    int      mf0c;                           // +0x0c
    int      mRangeA[2];                     // +0x10  (-1,-1)
    float    mf18;                           // +0x18
    float    mEmitX, mEmitY, mEmitZ;         // +0x1c
    float    mf28;                           // +0x28
    int      mf2c;                           // +0x2c
    int      mf30;                           // +0x30
    int      mf34;                           // +0x34
    char     mPad38[8];
    int      mRangeB[2];                     // +0x40
    bool     mFlag48;                        // +0x48
    char     mPad49[7];

    __forceinline cEmittedParticle();
};

void ReadEmittedParticle(void* stream, int flags, cEmittedParticle* particle);  // 0x00aa22b0

// ---------------------------------------------------------------------------------------
// The state the particle commands edit: loop mode/time, trigger/delay ranges and the
// scale flag bits (this is the sub-object FUN_00aa3040 fills in).
struct cParticleState
{
    char      mPad000[8];
    uint32_t  mFlags;                        // +0x08
    uint32_t  mFlags2;                       // +0x0c
    float     mf10, mf14, mf18;              // +0x10
    Vector2   mDelay;                        // +0x1c
    Vector2   mTrigger;                      // +0x24
    char      mPad2c[0x7c - 0x2c];
    float     mLoopTime;                     // +0x7c
    uint16_t  mLoopMode;                     // +0x80
    char      mPad82[2];
    float     mSpeedScale;                   // +0x84
};

// ---------------------------------------------------------------------------------------
// cParticlesDescription: full particle description (0x268 bytes), stored in the effect
// command and copied by the command layer.
struct GmeRefCount
{
    virtual void Cast();                     // gives the base a vtable (0x13ef094)
    GmeRefCount() : mRefCount(0) {}
    __declspec(nothrow) ~GmeRefCount() {}
    int mRefCount;                           // +0x04
};

struct cInlineDequeF                          // the +0x1ac vector: frees through a helper
{
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    cInlineDequeF() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void FreeRange(float* pBegin, float* pEnd);   // 0x00a87300 (thiscall)
    __declspec(nothrow) ~cInlineDequeF();
};

struct cParticlesDescription : GmeRefCount
{
    uint32_t         mFlags;                 // +0x008
    uint32_t         mFlags2;                // +0x00c
    float            mMinSize;               // +0x010
    float            mMaxSize;               // +0x014
    float            mf018;                  // +0x018
    Vector2          mEmitDelay;             // +0x01c
    Vector2          mTrigger;               // +0x024
    float            mf02c;                  // +0x02c
    float            mf030;                  // +0x030
    float            mf034;                  // +0x034
    float            mf038;                  // +0x038
    float            mf03c;                  // +0x03c
    float            mf040;                  // +0x040
    float            mf044;                  // +0x044
    float            mf048;                  // +0x048
    float            mf04c;                  // +0x04c
    float            mf050;                  // +0x050
    float            mf054;                  // +0x054
    float            mf058;                  // +0x058
    float            mf05c;                  // +0x05c
    float            mf060;                  // +0x060
    float            mf064;                  // +0x064
    SimpleVectorF    mRateCurve;             // +0x068
    char             mPad074[8];
    float            mf07c;                  // +0x07c
    uint16_t         mMode;                  // +0x080
    char             mPad082[2];
    float            mf084;                  // +0x084
    SimpleVectorF    mSizeCurve;             // +0x088
    char             mPad094[8];
    float            mf09c;                  // +0x09c
    SimpleVectorF    mAspectCurve;           // +0x0a0
    char             mPad0ac[8];
    float            mf0b4;                  // +0x0b4
    SimpleVectorF    mRotationCurve;         // +0x0b8
    char             mPad0c4[8];
    float            mf0cc;                  // +0x0cc
    float            mf0d0;                  // +0x0d0
    SimpleVectorV3   mColorCurve;            // +0x0d4
    char             mPad0e0[8];
    Vector3          mColorVary;             // +0x0e8
    SimpleVectorF    mAlphaCurve;            // +0x0f4
    char             mPad100[8];
    float            mf108;                  // +0x108
    char             mPad10c[4];
    int32_t          mi110;                  // +0x110
    int32_t          mi114;                  // +0x114
    char             mB118[4];               // +0x118
    uint16_t         mW11c;                  // +0x11c
    char             mPad11e[2];
    float            mf120;                  // +0x120
    char             mPad124[4];
    int32_t          mi128;                  // +0x128
    int32_t          mi12c;                  // +0x12c
    uint8_t          mB130, mB131, mB132, mB133, mB134, mB135, mB136, mB137;
    float            mf138;                  // +0x138
    Vector3          mV13c;                  // +0x13c
    float            mf148, mf14c, mf150;    // +0x148
    Vector3          mV154;                  // +0x154
    float            mf160, mf164, mf168;    // +0x160
    SimpleVectorW    mWiggles;               // +0x16c
    char             mPad178[8];
    uint8_t          mB180, mB181, mB182, mB183;   // +0x180
    SimpleVectorV3   mLoopBoxColorCurve;     // +0x184
    char             mPad190[8];
    SimpleVectorF    mLoopBoxAlphaCurve;     // +0x198
    char             mPad1a4[8];
    cInlineDequeF    mCurve1ac;              // +0x1ac
    char             mPad1b8[8];
    float            mf1c0;                  // +0x1c0
    float            mf1c4;
    float            mf1c8;
    float            mf1cc;
    float            mf1d0;
    float            mf1d4;
    float            mf1d8;
    float            mf1dc;
    float            mf1e0;
    char             mPad1e4[4];
    int32_t          mi1e8;                  // +0x1e8
    int32_t          mi1ec;
    int32_t          mi1f0;
    int32_t          mi1f4;
    int32_t          mi1f8;
    int32_t          mi1fc;
    float            mf200;                  // +0x200
    float            mf204;
    float            mf208;
    float            mf20c;
    float            mf210;
    float            mf214;
    float            mf218;
    SimpleVectorF    mCurve21c;              // +0x21c
    char             mPad228[8];
    uint8_t          mB230;                  // +0x230
    char             mPad231[3];
    Vector3          mV234;                  // +0x234
    SimpleVectorF    mCurve240;              // +0x240
    char             mPad24c[8];
    float            mf254;                  // +0x254
    float            mf258;
    SimpleVectorF    mCurve25c;              // +0x25c

    cParticlesDescription();
    virtual ~cParticlesDescription();
};

// cEffectsParser::AddDescription (0x00a6fc30)
struct cEffectsParser
{
    void AddDescription(EA::ArgScript::cArguments* args, const char* name, int flags, bool append);
};

struct cICommand
{
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
struct cCommandBase : cICommand                       // 0x0083c800
{
    cCommandBase();
    void*                    mpParser;                // +0x04
    int                      mRefCount;               // +0x08
};

// The "GroupParticles" command object (0x14 bytes) whose Execute registers a description.
struct cGroupParticlesCommand : cCommandBase
{
    cEffectsParser* mpEffectsParser;                  // +0x0c
    int             mFlags;                           // +0x10
    cGroupParticlesCommand(int flags) : mFlags(flags) {}
    void Execute(EA::ArgScript::cArguments* args);
};

}  // namespace Swarm
}  // namespace EA

using namespace EA::Swarm;

// @ 0x00aa2fd0
void SetKeywordName(int index, const char* name)
{
    ((const char**)0x01565550)[index * 2] = name;
}

// @ 0x00aa2fe0
__declspec(noinline)
float* ParseVector2(float* out, EA::ArgScript::cIArgEvaluator* evaluator,
                    const char*** pArgs, int argCount)
{
    out[0] = evaluator->Float((*pArgs)[0]);
    if (argCount > 1)
        out[1] = evaluator->Float((*pArgs)[1]);
    else
        out[1] = out[0];
    return out;
}

// @ 0x00aa3040
void ParseParticleState(EA::ArgScript::cArguments* args, cParticleState* state,
                        EA::ArgScript::cIArgEvaluator* evaluator)
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

// @ 0x00aa3280
void cGroupParticlesCommand::Execute(EA::ArgScript::cArguments* args)
{
    const char** argv = args->MainArguments(1);
    mpEffectsParser->AddDescription(args, argv[0], mFlags, false);
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

// @ 0x00aa2f00
cEmittedParticle* CreateEmittedParticle(void* stream, int flags)
{
    cEmittedParticle* p = 0;
    cEmittedParticle* o = new ("Swarm", 0, 0, 0, 0) cEmittedParticle();
    if (o)
        p = o;
    ReadEmittedParticle(stream, flags, p);
    return p;
}

// ---------------------------------------------------------------------------------------
// vector helpers (inlined into the description constructor)
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

// @ 0x00aa32f0
cParticlesDescription::~cParticlesDescription()
{
}

cEmittedParticle::cEmittedParticle()
    : mf08(0), mf18(kFloat1)
{
    mRangeA[0] = -1;
    mRangeA[1] = -1;
    mEmitX = gEmitR;
    mEmitY = gEmitG;
    mEmitZ = gEmitB;
    mf28 = kFloat1;
    mf2c = 0;
    mf30 = 0;
    mf34 = 0;
    mFlag48 = false;
    mRangeB[0] = -1;
    mRangeB[1] = -1;
}

SimpleVectorF::~SimpleVectorF()
{
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator delete(mpBegin);
}

SimpleVectorV3::~SimpleVectorV3()
{
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator delete(mpBegin);
}

// The +0x1ac curve frees its storage through a helper (0x00a87300) before releasing it.
cInlineDequeF::~cInlineDequeF()
{
    FreeRange(mpBegin, mpEnd);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator delete(mpBegin);
}