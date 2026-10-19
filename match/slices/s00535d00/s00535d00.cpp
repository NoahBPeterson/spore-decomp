// Slice s00535d00: Swarm skin-paint ArgScript paint-variable registration + 16-byte
// element vector copy ctor. The two large registration helpers (00535e40, 005361a0,
// 005365b0, 00536910, 00536b00) are stubbed (partial.txt). Unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);   // 0x0042dee0

// ---------------------------------------------------------------- @ 0x00535d00
struct Elem16 {
    uint32_t d[4];
};
struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    uint32_t mAlloc[2];
    Vec16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Vec16(const Vec16& x);
};
void* uninitialized_copy16(Elem16* first, Elem16* last, Elem16* dest);   // 0x005371a0

// @ 0x00535d00
Vec16::Vec16(const Vec16& x)
{
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    Elem16* p = (n == 0) ? 0 : (Elem16*)EASTL_Allocate(mAlloc, n * 16, 4, 0);
    mpBegin = p;
    mpEnd = p;
    mpCapacity = p + n;
    mpEnd = (Elem16*)uninitialized_copy16(x.mpBegin, x.mpEnd, mpBegin);
}

// ---------------------------------------------------------------- @ 0x005368f0
struct Host5368f0 {
    char pad[0x30];
    char* p;
    void Set(void* a);   // @ 0x005368f0
};
void Host5368f0::Set(void* a)
{
    (void)a;
    *(int*)(p + 0x50) = 0xff;
}

// ---------------------------------------------------------------- stubs (partial)
// ---------------------------------------------------------------- 0x00535e40 classes
// RegisterPaintEvalCommands<cSPSkinPaintFloodEffectBlockCommand>: registers the 19 inherit-style
// PaintVariable commands, "modifier", rotate/varyHue/varySat/varyVal and the two compare commands.
void* operator new(size_t, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

struct PaintCompatB {                       // 0x10 bytes; out-of-line ctor at 0x0053b1f0
    virtual void v0();
    virtual void v1();
    uint32_t pad[3];
    PaintCompatB();                         // 0x0053b1f0
};
struct PaintCompatM : PaintCompatB {        // vtbl 0x013f2424 (ArgScript::PaintCompat)
    PaintCompatM() {}
    virtual void v0();
};
struct PaintVarCmd : PaintCompatM {         // 0x14 bytes, vtbl 0x013f2c74
    int mVar;                               // +0x10
    PaintVarCmd(int v) { mVar = v; }
    virtual void v0();
};
struct PaintCompatNormal : PaintCompatM {   // 0x10 bytes, vtbl 0x013f2bb4
    PaintCompatNormal() {}
    virtual void v0();
};
struct PaintCompatPosition : PaintCompatM { // 0x10 bytes, vtbl 0x013f2b8c
    PaintCompatPosition() {}
    virtual void v0();
};
struct PaintVarModifierB {                  // 0x34 bytes; out-of-line ctor at 0x0053cca0
    virtual void v0();
    virtual void v1();
    uint32_t pad[12];
    PaintVarModifierB();                    // 0x0053cca0
};
struct PaintVarModifierM : PaintVarModifierB {   // vtbl 0x013f2c34 (ArgScript::PaintVarModifier)
    PaintVarModifierM() {}
    virtual void v0();
};
struct PaintVarModifier : PaintVarModifierM {    // vtbl 0x013f2c10
    PaintVarModifier() {}
    virtual void v0();
};
struct PaintRegistry {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void Register(const char* name, void* cmd);    // +0x18 (ret 8)
};
extern const char* const kFloodPaintNames[0x13];            // 0x013f2980

// @ 0x00535e40
void RegisterPaintEvalCommands(PaintRegistry* reg)
{
    for (int i = 0; i < 0x13; ++i)
        reg->Register(kFloodPaintNames[i], new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(i));
    reg->Register("modifier", new("ArgScript/PaintVarModifier", 0, 0, 0, 0) PaintVarModifier());
    reg->Register("rotate", new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(2));
    reg->Register("varyHue", new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(7));
    reg->Register("varySat", new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(8));
    reg->Register("varyVal", new("ArgScript/PaintVariable", 0, 0, 0, 0) PaintVarCmd(9));
    reg->Register("compareNormal", new("ArgScript/PaintCompat", 0, 0, 0, 0) PaintCompatNormal());
    reg->Register("comparePosition", new("ArgScript/PaintCompat", 0, 0, 0, 0) PaintCompatPosition());
}
// ============================================================================
// Swarm skin-paint (flood effect) ArgScript command model.
// ============================================================================
extern const float kZero;                       // 0x01485378
extern const float kOne;                        // 0x01485720
extern const float kEps;                        // 0x013ec4b8 (1e-8f)
extern float gPaintVec[3];                      // 0x015e1bf0 (runtime axis)
extern float gPaintAxis[3];                     // 0x015e18f4
extern const char* const kPaintVarNames[14];    // 0x013f29cc
// kFloodPaintNames (0x013f2980) is declared above: the 19 inherited variable names.
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, size_t);

struct Vector3T {                                // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                // @ 0x4098a0 (out of line)
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
};

struct cIParser {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
    virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24();
    virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29();
    virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34();
    virtual void Notify(void* cmd);                     // +0x8c
    virtual void p36(); virtual void p37();
    virtual float GetFloat(const char* s);              // +0x98
    virtual void p39(); virtual void p40(); virtual void p41();
    virtual Vector3T GetVector(const char* s);          // +0xa8
};

struct cArguments {
    const char** MainArguments(size_t* pCount, int mn, int mx);  // 0x838020
    const char** MainArguments(int n);                           // 0x838320
    const char** OptionArguments(const char* name, int n);       // 0x838330
    bool HasFlag(const char* name);                              // 0x8380b0
    bool HasArgument(const char* name);                          // 0x837ee0
    const char* operator[](int i);                               // 0x837f20
};

struct sp_vec_alloc { uint32_t mData[2]; };
template<class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vec_alloc mAllocator;
    T& operator[](int i) { return mpBegin[i]; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    void push_back(const T& v);
    void resize(size_t n, const T& v);                          // 0x5370b0
};

struct cPaintVarEvalList {
    struct Modifier {
        cSPVector3 mVec;
        uint8_t mModType;
        uint8_t mVarModIdx;
        uint16_t mCurveOffset;
    };
    struct Entry {
        float mRangeMin, mRangeMax, mValueMin, mValueMax;
        uint8_t mVariable, mVarModIdx, mApplyMode, mEdgeMode;
    };
    sp_vector<Modifier> mModifiers;   // +0x00
    sp_vector<Entry> mEntries;        // +0x14  (push_back @ 0x4227f0)
    sp_vector<float> mCurveData;      // +0x28  (push_back @ 0x4547f0)
};

// Out-of-line collection-helper instantiations used by the commands below.
// @ 0x004227f0
template<> void sp_vector<cPaintVarEvalList::Entry>::push_back(const cPaintVarEvalList::Entry& v) { (void)v; }
// @ 0x00537130
template<> void sp_vector<cPaintVarEvalList::Modifier>::push_back(const cPaintVarEvalList::Modifier& v) { (void)v; }
// @ 0x004547f0
template<> void sp_vector<float>::push_back(const float& v) { (void)v; }
// @ 0x005370b0
template<> void sp_vector<cPaintVarEvalList::Modifier>::resize(size_t n, const cPaintVarEvalList::Modifier& v)
{
    (void)n; (void)v;
}

struct cSPSkinPaintFloodEffectBlockCommand {
    uint8_t pad0[0x38];
    void* mpDesc;                       // +0x38
    uint8_t mName[0x10];                // +0x3c
    cPaintVarEvalList* mpEvalList;      // +0x4c
    int mCurrentModifier;               // +0x50
};

struct cCommandBase {
    virtual void v0();
    cIParser* mParser;                                          // +0x04
    int mRefCount;                                              // +0x08
};

struct cPaintVariableCommand : cCommandBase {
    cSPSkinPaintFloodEffectBlockCommand* mState;                // +0x0c
    int mVarNum;                                                // +0x10
    void Execute(cArguments& args);
    void FUN_00536d40(cArguments& a, const char** argv, int n);  // 0x536d40
};

struct cBlockCommandBase {
    virtual void v0();
    cIParser* mParser;                                          // +0x04
    int mRefCount;                                              // +0x08
    uint8_t pad[0x30 - 0x0c];
};

struct cPaintAddVariableCommand : cBlockCommandBase {
    cSPSkinPaintFloodEffectBlockCommand* mState;                // +0x30
    void Execute(cArguments& args);
};

struct cPaintComparePositionCommand : cCommandBase {
    cSPSkinPaintFloodEffectBlockCommand* mState;                // +0x0c
    void Execute(cArguments& args);
};

struct cPaintCompareNormalCommand : cCommandBase {
    cSPSkinPaintFloodEffectBlockCommand* mState;                // +0x0c
    void Execute(cArguments& args);
};

void FUN_0041dba0(float* v, const float* s);                    // 0x41dba0

// @ 0x005361a0
void cPaintVariableCommand::Execute(cArguments& args)
{
    size_t count;
    const char** argv = args.MainArguments(&count, 0, 100);
    cPaintVarEvalList* list;
    int modifier = mState->mCurrentModifier;
    if (modifier == 0xff) {
        if (_strnicmp(args[0], "vary", 4) == 0 || (int)count > 1 ||
            args.HasArgument("offset") || args.HasArgument("vary") ||
            args.HasArgument("scaleNorm") || args.HasArgument("scalePos")) {
            FUN_00536d40(args, argv, (int)count);
            return;
        }
    }
    list = mState->mpEvalList;
    cPaintVarEvalList::Entry e;
    e.mRangeMin = kZero;
    e.mRangeMax = kOne;
    e.mValueMin = kZero;
    e.mValueMax = kOne;
    e.mVariable = (uint8_t)mVarNum;
    e.mVarModIdx = (uint8_t)modifier;
    e.mApplyMode = 0;
    e.mEdgeMode = 0;
    if (args.HasArgument("add"))
        e.mApplyMode = 1;
    else if (args.HasArgument("mult"))
        e.mApplyMode = 2;
    else if (args.HasArgument("div"))
        e.mApplyMode = 3;
    if (modifier == 0xff) {
        const char** o = argv;
        if (count != 1) {
            o = args.OptionArguments("set", 1);
            if (!o) o = args.OptionArguments("add", 1);
            if (!o) o = args.OptionArguments("mult", 1);
            if (!o) o = args.OptionArguments("div", 1);
            if (!o) goto compat_flags;
        }
        e.mValueMin = mParser->GetFloat(o[0]);
    compat_flags:
        args.HasFlag("set");
        args.HasFlag("add");
        args.HasFlag("mult");
        args.HasFlag("div");
    } else {
        const char** o = args.OptionArguments("range", 2);
        if (o) {
            e.mRangeMin = mParser->GetFloat(o[0]);
            e.mRangeMax = mParser->GetFloat(o[1]);
        }
        o = args.OptionArguments("set", 2);
        if (!o) o = args.OptionArguments("mult", 2);
        if (!o) o = args.OptionArguments("add", 2);
        if (!o) o = args.OptionArguments("div", 2);
        if (o) {
            e.mValueMin = mParser->GetFloat(o[0]);
            e.mValueMax = mParser->GetFloat(o[1]);
        }
        if (args.HasFlag("open"))
            e.mEdgeMode = 1;
        else if (args.HasFlag("clamp"))
            e.mEdgeMode = 2;
        else if (args.HasFlag("wrap"))
            e.mEdgeMode = 3;
        else if (args.HasFlag("mirror"))
            e.mEdgeMode = 4;
        else if (args.HasFlag("clamp2"))
            e.mEdgeMode = 5;
        else if (args.HasFlag("wrap2"))
            e.mEdgeMode = 6;
        else if (args.HasFlag("mirror2"))
            e.mEdgeMode = 7;
    }
    list->mEntries.push_back(e);
}

// @ 0x005365b0
void cPaintAddVariableCommand::Execute(cArguments& args)
{
    cPaintVarEvalList* list = mState->mpEvalList;
    cPaintVarEvalList::Modifier mod;
    mod.mVec.x = gPaintVec[0];
    mod.mVec.y = gPaintVec[1];
    mod.mVec.z = gPaintVec[2];
    mod.mModType = 0xe;
    mod.mVarModIdx = 0x13;
    mod.mCurveOffset = 0;
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 4);
    for (int i = 0; i < (int)(uint32_t)mod.mModType; ++i) {
        if (i == 0xd) {
            for (int j = 0; j < (int)(uint32_t)mod.mVarModIdx; ++j) {
                if (_stricmp(argv[0], kFloodPaintNames[j]) == 0) {
                    mod.mModType = (uint8_t)i;
                    mod.mVarModIdx = (uint8_t)j;
                }
            }
        } else {
            if (_stricmp(argv[0], kPaintVarNames[i]) == 0)
                mod.mModType = (uint8_t)i;
        }
    }
    switch (mod.mModType) {
    case 0:
    case 0xd: {
        const char** o;
        mod.mVec.x = kZero;
        o = args.OptionArguments("scale", 1);
        if (!o)
            mod.mVec.y = kOne;
        else
            mod.mVec.y = mParser->GetFloat(o[0]);
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5: {
        cSPVector3 v = mParser->GetVector(argv[1]);
        mod.mVec.x = v.x;
        mod.mVec.y = v.y;
        mod.mVec.z = v.z;
        if (mod.mModType != 4) {
            float s = kOne / (((mod.mVec.x * mod.mVec.x + mod.mVec.y * mod.mVec.y) +
                               mod.mVec.z * mod.mVec.z) + kEps);
            FUN_0041dba0(&mod.mVec.x, &s);
        }
        if (mod.mModType == 3) {
            float s = kOne / (((mod.mVec.x * gPaintAxis[0] + mod.mVec.y * gPaintAxis[1]) +
                               mod.mVec.z * gPaintAxis[2]) + kEps);
            FUN_0041dba0(&mod.mVec.x, &s);
        }
        break;
    }
    default:
        break;
    }
    list->mModifiers.push_back(mod);
    mState->mCurrentModifier = (int)(list->mModifiers.mpEnd - list->mModifiers.mpBegin) - 1;
    mParser->Notify(this);
}

// @ 0x00536910
void cPaintComparePositionCommand::Execute(cArguments& args)
{
    const char** argv = args.MainArguments(3);
    cSPVector3 v = mParser->GetVector(argv[0]);
    float f1 = mParser->GetFloat(argv[1]);
    float f2 = mParser->GetFloat(argv[2]);
    cPaintVarEvalList* list = mState->mpEvalList;
    if ((list->mModifiers.size() == 0 || list->mModifiers[0].mModType >= 0xfd) &&
        (list->mModifiers.size() <= 1 || list->mModifiers[1].mModType >= 0xfe)) {
        if (list->mModifiers.size() < 2) {
            cPaintVarEvalList::Modifier tmp;
            tmp.mVec.x = gPaintVec[0];
            tmp.mVec.y = gPaintVec[1];
            tmp.mVec.z = gPaintVec[2];
            tmp.mModType = 0xff;
            tmp.mVarModIdx = 0;
            tmp.mCurveOffset = 0;
            list->mModifiers.resize(2, tmp);
        }
        cPaintVarEvalList::Modifier mod;
        mod.mVec.x = v.x;
        mod.mVec.y = v.y;
        mod.mVec.z = v.z;
        mod.mModType = 0xfd;
        mod.mVarModIdx = 2;
        mod.mCurveOffset = (uint16_t)list->mCurveData.size();
        list->mModifiers[0] = mod;
        list->mCurveData.push_back(f1);
        list->mCurveData.push_back(f2);
    }
}

// @ 0x00536b00
void cPaintCompareNormalCommand::Execute(cArguments& args)
{
    const char** argv = args.MainArguments(2);
    cSPVector3 v0 = mParser->GetVector(argv[0]);
    cSPVector3 v1 = mParser->GetVector(argv[1]);
    cPaintVarEvalList* list = mState->mpEvalList;
    if ((list->mModifiers.size() == 0 || list->mModifiers[0].mModType >= 0xfd) &&
        (list->mModifiers.size() <= 1 || list->mModifiers[1].mModType >= 0xfe)) {
        if (list->mModifiers.size() < 2) {
            cPaintVarEvalList::Modifier tmp;
            tmp.mVec.x = gPaintVec[0];
            tmp.mVec.y = gPaintVec[1];
            tmp.mVec.z = gPaintVec[2];
            tmp.mModType = 0xff;
            tmp.mVarModIdx = 0;
            tmp.mCurveOffset = 0;
            list->mModifiers.resize(2, tmp);
        }
        cPaintVarEvalList::Modifier mod;
        mod.mVec.x = v0.x;
        mod.mVec.y = v0.y;
        mod.mVec.z = v0.z;
        mod.mModType = 0xfe;
        mod.mVarModIdx = 3;
        mod.mCurveOffset = (uint16_t)list->mCurveData.size();
        list->mModifiers[1] = mod;
        list->mCurveData.push_back(v1.x);
        list->mCurveData.push_back(v1.y);
        list->mCurveData.push_back(v1.z);
    }
}
