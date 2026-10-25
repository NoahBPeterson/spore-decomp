// Swarm skin-paint particle "paint variable" commands: registration, vector
// int Read/Write, the paint-variable Execute handlers and a Dot helper.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (unoptimized module).
#include "types.h"

typedef unsigned int size_t;
void* operator new[](size_t, const char*, int, unsigned, const char*, int);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, size_t);

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {}
    float& operator[](int i) { return (&x)[i]; }
};

namespace EA { namespace IO { struct IStream {}; } }
bool ReadInt32(EA::IO::IStream*, int32_t*, size_t, int);           // @ 0x93a780
bool WriteUInt32(EA::IO::IStream*, const uint32_t*, size_t, int);  // @ 0x93aa70

namespace EA { namespace ArgScript {
class cIParser { public:
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void PushBlock(void* cmd);                           // +0x8c
    PV(36) PV(37)
    virtual float GetFloat(const char*);                         // +0x98
    PV(39) PV(40) PV(41)
    virtual cSPVector3* GetVector(cSPVector3* out, const char*); // +0xa8
#undef PV
};
class cArguments { public:
    const char** MainArguments(size_t* pCount, int min, int max);  // 0x838020
    const char** MainArguments(int count);                         // 0x838320
    const char** OptionArguments(const char* name, int count);     // 0x838330
    bool HasFlag(const char* flag);                                // 0x8380b0
    bool HasArgument(const char* name);                            // 0x837ee0
    const char* operator[](int i);                                 // 0x837f20
};
class cICommand { public: virtual void AddRef(); virtual void Release(); virtual void Cast(); };
class cCommandBase : public cICommand { public: cIParser* mParser; int mRefCount; };
} }

namespace EA { namespace Swarm { class cPaintCompat { public: virtual void v0(); virtual void v1(); }; } }

// Stack-frame filler: the original frames reserve slots for locals of inlined
// helpers whose code was optimized away even at /Od.
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

void RegisterPaintVar(EA::ArgScript::cCommandBase* a, const char* name, void* cmd); // vtable +0x18
void* PaintCompatCtor(void*);                                         // 0x53b1f0
void* PaintVarModifierCtor(void*);                                    // 0x83?
void* EASTL_allocator_allocate(size_t, const char*, int, unsigned, const char*, int); // 0xf473a0
void VecResize(void* vec, unsigned n);                                // 0x4cd3c0
float FUN_00532f80(float* v);                                         // @ 0x532f80
void FUN_0041dba0(float* v, float* s);                                // @ 0x41dba0
float FUN_0053c480(const float* a, const float* b);                   // @ 0x53c480

extern const char* kInheritNames[];                                   // 0x13f2e78 (19)
extern const char* kPaintVarNames[];                                  // 0x13f2e44 (19)
extern float kDefaultColor[3];                                        // 0x15e24bc
extern float kAxis[3];                                                // 0x15e21e4

// -------------------------------------------------------------- paint state

// One modifier record (16 bytes): a vector plus a kind byte, an operand byte
// and a 16-bit index into the float curve data.
struct PaintModifier {
    cSPVector3 mVec;            // +0x00
    uint8_t mModType;           // +0x0c
    uint8_t mVarModIdx;         // +0x0d
    uint16_t mDataIdx;          // +0x0e
};

// One entry record (20 bytes): a value range/mapping plus the referenced
// variable, modifier and blend/edge modes.
struct PaintEntry {
    float mRangeMin;            // +0x00
    float mRangeMax;            // +0x04
    float mValueMin;            // +0x08
    float mValueMax;            // +0x0c
    uint8_t mVariable;          // +0x10
    uint8_t mVarModIdx;         // +0x11
    uint8_t mApplyMode;         // +0x12
    uint8_t mEdgeMode;          // +0x13
};

// Engine vector (0x14 bytes) with an inline allocator tail we never touch.
template <typename T> struct sp_vector {
    T* mpBegin;                 // +0x00
    T* mpEnd;                   // +0x04
    T* mpCapacity;              // +0x08
    uint32_t mAllocator[2];     // +0x0c
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    void push_back(const T& value);
    void resize(uint32_t n, const T& value);
};

struct cPaintVarEvalList {
    sp_vector<PaintModifier> mModifiers;  // +0x00
    sp_vector<PaintEntry> mEntries;       // +0x14
    sp_vector<float> mCurveData;          // +0x28
};

// Skin-paint particle block state reached through the command's mState.
struct cPaintParticleState {
    uint8_t pad0[0x4c];
    int mCurrentModifier;                 // +0x4c
    cPaintVarEvalList* mpEvalList;        // +0x50
};

// Command bases (data layout only; the vtable pointer is never used here).
struct cCommandTBase {
    void* mpVtbl;                            // +0x00
    EA::ArgScript::cIParser* mParser;        // +0x04
    int mRefCount;                           // +0x08
    cPaintParticleState* mState;             // +0x0c
    int mVarNum;                             // +0x10
};

struct cBlockCommandTBase {
    void* mpVtbl;                            // +0x00
    EA::ArgScript::cIParser* mParser;        // +0x04
    int mRefCount;                           // +0x08
    void* mChildState;                       // +0x0c
    uint32_t mCommands[8];                   // +0x10
    cPaintParticleState* mState;             // +0x30
};

struct PaintVarCommand : cCommandTBase {
    void Execute(EA::ArgScript::cArguments& args);
    void ExecuteOldStyle(EA::ArgScript::cArguments* args, const char** argv, int count);
};

struct PaintVarModifierCommand : cBlockCommandTBase {
    void Execute(EA::ArgScript::cArguments& args);
};

struct PaintAddVar2Command : cCommandTBase {
    void Execute(EA::ArgScript::cArguments& args);
};

// ================================================================ functions

// @ 0x0053b930
void RegisterPaintEvalCommands(EA::ArgScript::cCommandBase* cmds)
{
    for (int i = 0; i < 0x13; ++i) {
        void* p = EASTL_allocator_allocate(0x14, "ArgScript/PaintVariable", 0, 0, 0, 0);
        void* c = p ? PaintCompatCtor(p) : 0;
        if (c) {
            *(void**)c = (void*)0x13f340c;
            ((int*)c)[4] = i;
        }
        RegisterPaintVar(cmds, kInheritNames[i], c);
    }
    void* m = EASTL_allocator_allocate(0x34, "ArgScript/PaintVarModifier", 0, 0, 0, 0);
    if (m) {
        PaintVarModifierCtor(m);
        *(void**)m = (void*)0x13f33e8;
    }
    RegisterPaintVar(cmds, "modifier", m);

    static const struct { const char* name; int var; } extras[] = {
        { "rotate", 2 }, { "varyHue", 7 }, { "varySat", 8 }, { "varyVal", 9 },
    };
    for (int i = 0; i < 4; ++i) {
        void* p = EASTL_allocator_allocate(0x14, "ArgScript/PaintVariable", 0, 0, 0, 0);
        void* c = p ? PaintCompatCtor(p) : 0;
        if (c) {
            *(void**)c = (void*)0x13f340c;
            ((int*)c)[4] = extras[i].var;
        }
        RegisterPaintVar(cmds, extras[i].name, c);
    }
    void* a = EASTL_allocator_allocate(0x10, "ArgScript/PaintCompat", 0, 0, 0, 0);
    if (a) { PaintCompatCtor(a); *(void**)a = (void*)0x13f33d0; }
    RegisterPaintVar(cmds, "compareNormal", a);
    void* b = EASTL_allocator_allocate(0x10, "ArgScript/PaintCompat", 0, 0, 0, 0);
    if (b) { PaintCompatCtor(b); *(void**)b = (void*)0x13f33b8; }
    RegisterPaintVar(cmds, "comparePosition", b);
}

// @ 0x0053bc90
EA::IO::IStream* ReadIntVec(EA::IO::IStream* s, int** vec)
{
    uint32_t n = 0;
    ReadInt32(s, (int32_t*)&n, 1, 0);
    VecResize(vec, n);
    for (uint32_t i = 0; i < n; ++i)
        ReadInt32(s, (*vec) + i, 1, 0);
    return s;
}

// @ 0x0053bd00
EA::IO::IStream* WriteIntVec(EA::IO::IStream* s, int** vec)
{
    uint32_t n = (uint32_t)(vec[1] - vec[0]) >> 2;
    WriteUInt32(s, &n, 1, 0);
    for (uint32_t i = 0; i < n; ++i) {
        uint32_t v = (uint32_t)(*vec)[i];
        WriteUInt32(s, &v, 1, 0);
    }
    return s;
}

// @ 0x0053bd80
void PaintVarCommand::Execute(EA::ArgScript::cArguments& args)
{
    ScratchSlots<22>();
    int count;
    const char** argv = args.MainArguments((size_t*)&count, 0, 100);
    int modifier = mState->mCurrentModifier;
    if (modifier == 0xff) {
        if (_strnicmp(args[0], "vary", 4) == 0 || count > 1 ||
            args.HasArgument("offset") || args.HasArgument("vary") ||
            args.HasArgument("scaleNorm") || args.HasArgument("scalePos")) {
            ExecuteOldStyle(&args, argv, count);
            return;
        }
    }
    cPaintVarEvalList* list = mState->mpEvalList;
    PaintEntry entry;
    entry.mRangeMin = 0.0f;
    entry.mRangeMax = 1.0f;
    entry.mValueMin = 0.0f;
    entry.mValueMax = 1.0f;
    entry.mVariable = (uint8_t)mVarNum;
    entry.mVarModIdx = (uint8_t)modifier;
    entry.mApplyMode = 0;
    entry.mEdgeMode = 0;

    if (args.HasArgument("add"))
        entry.mApplyMode = 1;
    else if (args.HasArgument("mult"))
        entry.mApplyMode = 2;
    else if (args.HasArgument("div"))
        entry.mApplyMode = 3;

    if (modifier == 0xff) {
        if (count == 1 ||
            (argv = args.OptionArguments("set", 1)) != 0 ||
            (argv = args.OptionArguments("add", 1)) != 0 ||
            (argv = args.OptionArguments("mult", 1)) != 0 ||
            (argv = args.OptionArguments("div", 1)) != 0) {
            entry.mValueMin = mParser->GetFloat(argv[0]);
        } else {
            do { } while (0);   // engine-side assertion stubbed out in release
        }
        args.HasFlag("set");
        args.HasFlag("add");
        args.HasFlag("mult");
        args.HasFlag("div");
    } else {
        if ((argv = args.OptionArguments("range", 2)) != 0) {
            entry.mRangeMin = mParser->GetFloat(argv[0]);
            entry.mRangeMax = mParser->GetFloat(argv[1]);
        } else {
            do { } while (0);   // engine-side assertion stubbed out in release
        }
        if ((argv = args.OptionArguments("set", 2)) != 0 ||
            (argv = args.OptionArguments("mult", 2)) != 0 ||
            (argv = args.OptionArguments("add", 2)) != 0 ||
            (argv = args.OptionArguments("div", 2)) != 0) {
            entry.mValueMin = mParser->GetFloat(argv[0]);
            entry.mValueMax = mParser->GetFloat(argv[1]);
        } else {
            do { } while (0);   // engine-side assertion stubbed out in release
        }
        if (args.HasFlag("open"))
            entry.mEdgeMode = 1;
        else if (args.HasFlag("clamp"))
            entry.mEdgeMode = 2;
        else if (args.HasFlag("wrap"))
            entry.mEdgeMode = 3;
        else if (args.HasFlag("mirror"))
            entry.mEdgeMode = 4;
        else if (args.HasFlag("clamp2"))
            entry.mEdgeMode = 5;
        else if (args.HasFlag("wrap2"))
            entry.mEdgeMode = 6;
        else if (args.HasFlag("mirror2"))
            entry.mEdgeMode = 7;
    }
    list->mEntries.push_back(entry);
}

// @ 0x0053c190
void PaintVarModifierCommand::Execute(EA::ArgScript::cArguments& args)
{
    ScratchSlots<2>();
    PaintModifier modifier;
    cPaintVarEvalList* mod = mState->mpEvalList;
    modifier.mVec.x = kDefaultColor[0];
    modifier.mVec.y = kDefaultColor[1];
    modifier.mVec.z = kDefaultColor[2];
    modifier.mModType = 0xe;
    modifier.mVarModIdx = 0x13;
    modifier.mDataIdx = 0;
    int count = 0;
    const char** argv = args.MainArguments((size_t*)&count, 1, 4);
    if (mState->mCurrentModifier != 0xff) {
        do { } while (0);       // engine-side assertion stubbed out in release
    }
    for (int i = 0; i < modifier.mModType; ++i) {
        if (i != 0xd) {
            if (_stricmp(argv[0], kPaintVarNames[i]) == 0) {
                modifier.mModType = (uint8_t)i;
            }
        } else {
            for (int j = 0; j < modifier.mVarModIdx; ++j) {
                if (_stricmp(argv[0], kInheritNames[j]) == 0) {
                    modifier.mModType = (uint8_t)i;
                    modifier.mVarModIdx = (uint8_t)j;
                }
            }
        }
    }
    switch (modifier.mModType) {
    case 1: case 6: case 7: case 8: case 9: case 10: case 11: case 12: {
        if (count > 1) {
            do { } while (0);   // engine-side assertion stubbed out in release
        }
        break;
    }
    case 0:
    case 0xd: {
        if (count > 1) {
            do { } while (0);   // engine-side assertion stubbed out in release
        }
        modifier.mVec[0] = 0.0f;
        if ((argv = args.OptionArguments("scale", 1)) != 0)
            modifier.mVec[1] = mParser->GetFloat(argv[0]);
        else
            modifier.mVec[1] = 1.0f;
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5: {
        if (count < 2) {
            do { } while (0);   // engine-side assertion stubbed out in release
        }
        if (count > 2) {
            do { } while (0);   // engine-side assertion stubbed out in release
        }
        cSPVector3 vec;
        float s;
        float t;
        cSPVector3* m = mParser->GetVector(&vec, argv[1]);
        modifier.mVec.x = m->x;
        modifier.mVec.y = m->y;
        modifier.mVec.z = m->z;
        if (modifier.mModType != 4) {
            s = 1.0f / (FUN_00532f80(&modifier.mVec.x) + 1.0e-8f);
            FUN_0041dba0(&modifier.mVec.x, &s);
        }
        if (modifier.mModType == 3) {
            t = 1.0f / (FUN_0053c480(&modifier.mVec.x, kAxis) + 1.0e-8f);
            FUN_0041dba0(&modifier.mVec.x, &t);
        }
        break;
    }
    default: {
        do { } while (0);       // engine-side assertion stubbed out in release
        break;
    }
    }
    mod->mModifiers.push_back(modifier);
    mState->mCurrentModifier = (int)mod->mModifiers.size() - 1;
    mParser->PushBlock(this);
}

// @ 0x0053c480
float Dot3(const float* a, const float* b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

// Receiver (ECX) of the thiscall `ret 4` command; the stack argument is unused.
struct PaintResetModifierCmd : cBlockCommandTBase {
    void PaintResetModifier(void* unused);
};

// @ 0x0053c4e0
void PaintResetModifierCmd::PaintResetModifier(void*)
{
    mState->mCurrentModifier = 0xff;
}

// @ 0x0053c500
void PaintAddVar2Command::Execute(EA::ArgScript::cArguments& args)
{
    ScratchSlots<10>();
    const char** argv = args.MainArguments(3);
    cSPVector3 vec;
    cSPVector3* vp = mParser->GetVector(&vec, argv[0]);
    cSPVector3 g;
    g.x = vp->x;
    g.y = vp->y;
    g.z = vp->z;
    float f1 = mParser->GetFloat(argv[1]);
    float f2 = mParser->GetFloat(argv[2]);
    cPaintVarEvalList* list = mState->mpEvalList;
    if (!((list->mModifiers.size() <= 0 || list->mModifiers[0].mModType >= 0xfd) &&
          (list->mModifiers.size() <= 1 || list->mModifiers[1].mModType >= 0xfe))) {
        do { return; } while (0);
    }
    if (list->mModifiers.size() < 2) {
        PaintModifier def;
        def.mVec.x = kDefaultColor[0];
        def.mVec.y = kDefaultColor[1];
        def.mVec.z = kDefaultColor[2];
        def.mModType = 0xff;
        def.mVarModIdx = 0;
        def.mDataIdx = 0;
        list->mModifiers.resize(2, def);
    }
    PaintModifier m;
    m.mVec.x = g.x;
    m.mVec.y = g.y;
    m.mVec.z = g.z;
    m.mModType = 0xfd;
    m.mVarModIdx = 2;
    m.mDataIdx = (uint16_t)list->mCurveData.size();
    list->mModifiers[0] = m;
    list->mCurveData.push_back(f1);
    list->mCurveData.push_back(f2);
}
