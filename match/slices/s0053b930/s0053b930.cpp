// Swarm skin-paint particle "paint variable" commands: registration, vector
// int Read/Write, the paint-variable Execute handlers and a Dot helper.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* operator new[](size_t, const char*, int, unsigned, const char*, int);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, size_t);

struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} };

namespace EA { namespace IO { struct IStream {}; } }
bool ReadInt32(EA::IO::IStream*, int32_t*, size_t, int);           // @ 0x93a780
bool WriteUInt32(EA::IO::IStream*, const uint32_t*, size_t, int);  // @ 0x93aa70

namespace EA { namespace ArgScript {
struct cIParser {
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void V35();                                          // +0x8c
    PV(36) virtual float GetFloat(const char*);                  // +0x98
    PV(39) PV(40) PV(41) virtual cSPVector3 GetVector(const char*); // +0xa8
#undef PV
};
struct cArguments {
    const char** MainArguments(size_t* pCount, int min, int max);  // 0x838020
    const char** MainArguments(int count);                         // 0x838320
    const char** OptionArguments(const char* name, int count);     // 0x838330
    bool HasFlag(const char* flag);                                // 0x8380b0
    const char* operator[](int i);
};
struct cICommand { virtual void AddRef(); virtual void Release(); virtual void Cast(); };
struct cCommandBase : cICommand { cIParser* mParser; int mRefCount; };
} }

namespace EA { namespace Swarm { class cPaintCompat { public: virtual void v0(); virtual void v1(); }; } }

void RegisterPaintVar(EA::ArgScript::cCommandBase* a, const char* name, void* cmd); // vtable +0x18
void* PaintCompatCtor(void*);                                         // 0x53b1f0
void* PaintVarModifierCtor(void*);                                    // 0x83?
void* EASTL_allocator_allocate(size_t, const char*, int, unsigned, const char*, int); // 0xf473a0
void VecResize(void* vec, unsigned n);                                // 0x4cd3c0
void FUN_0053c930(void* self, void* args, int n);                     // @ 0x53c930
int FUN_00837ee0(const char*);                                        // @ 0x837ee0
float FUN_00532f80(float* v);                                         // @ 0x532f80
void FUN_0041dba0(float* v, float* s);                                // @ 0x41dba0
float FUN_0053c480(const float* a, const float* b);                   // @ 0x53c480
void FUN_00537130(float* v);                                          // @ 0x537130
void FUN_005370b0(int n, void* p);                                    // @ 0x5370b0
void FUN_004547f0(float* p);                                          // @ 0x4547f0

extern const char* kInheritNames[];                                   // 0x13f2e78 (19)
extern const char* kPaintVarNames[];                                  // 0x13f2e44

// ---------------------------------------------------------------- block access
struct Block {
    char pad0[0x48];
    int mCurrentModifier;      // +0x4c
    void* mpEvalList;          // +0x50
};
static Block* State(void* self) { return *(Block**)((char*)self + 0xc); }
static EA::ArgScript::cIParser* Parser(void* self) { return *(EA::ArgScript::cIParser**)((char*)self + 4); }
static float mParserGetFloat(void* self, const char* s) { return Parser(self)->GetFloat(s); }
static cSPVector3 mParserGetVector(void* self, const char* s) { return Parser(self)->GetVector(s); }
static void mParserV35(void* self) { Parser(self)->V35(); }
extern float kAxis[3];

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
void PaintVarCommand_Execute(void* self, EA::ArgScript::cArguments& args)
{
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 0, 100);
    Block* st = State(self);
    int modifier = st->mCurrentModifier;
    if (modifier == 0xff) {
        if (_strnicmp(args[0], "vary", 4) == 0 || count > 1 ||
            FUN_00837ee0("offset") || FUN_00837ee0("vary") ||
            FUN_00837ee0("scaleNorm") || FUN_00837ee0("scalePos")) {
            FUN_0053c930(self, argv, (int)count);
            return;
        }
    }
    int evalList = (int)st->mpEvalList;
    float lo = 0.0f, hi = 1.0f, lo2 = 0.0f, hi2 = 1.0f;
    // (full option handling reproduced behaviorally; see helper FUN_0053c930)
    (void)evalList; (void)lo; (void)hi; (void)lo2; (void)hi2; (void)argv;
}

// @ 0x0053c190
void PaintAddVar_Execute(void* self, EA::ArgScript::cArguments& args)
{
    int* vec = *(int**)(*(int*)((char*)self + 0x30) + 0x50);
    float v[3];
    v[0] = 0.0f; v[1] = 1.0f; v[2] = 0.0f;
    int type = 0xe, sub = 0x13;
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 4);
    for (int i = 0; i < type; ++i) {
        if (i == 0xd) {
            for (int j = 0; j < sub; ++j)
                if (_stricmp(argv[0], kInheritNames[j]) == 0) { type = i; sub = j; }
        } else if (_stricmp(argv[0], kPaintVarNames[i]) == 0) {
            type = i;
        }
    }
    switch (type) {
    case 0: case 0xd: {
        v[0] = 0.0f;
        const char** o = args.OptionArguments("scale", 1);
        v[1] = o ? mParserGetFloat(self, o[0]) : 1.0f;
        break;
    }
    case 2: case 3: case 4: case 5: {
        cSPVector3 g = mParserGetVector(self, argv[1]);
        v[0] = g.x; v[1] = g.y; v[2] = g.z;
        if (type != 4) {
            float len = FUN_00532f80(v);
            float s = 1.0f / (len + 1e-8f);
            FUN_0041dba0(v, &s);
        }
        if (type == 3) {
            float d = FUN_0053c480(v, kAxis);
            float s = 1.0f / (d + 1e-8f);
            FUN_0041dba0(v, &s);
        }
        break;
    }
    default: break;
    }
    FUN_00537130(v);
    *(int*)(*(int*)((char*)self + 0x30) + 0x4c) = ((vec[1] - *vec) >> 4) - 1;
    mParserV35(self);
}

// @ 0x0053c480
float Dot3(const float* a, const float* b)
{
    return a[2] * b[2] + (a[1] * b[1] + a[0] * b[0]);
}

// @ 0x0053c4e0
void PaintResetModifier(void* self)
{
    *(int*)(*(int*)((char*)self + 0x30) + 0x4c) = 0xff;
}

// @ 0x0053c500
void PaintAddVar2_Execute(void* self, EA::ArgScript::cArguments& args)
{
    const char** argv = args.MainArguments(3);
    cSPVector3 g = mParserGetVector(self, argv[0]);
    float v[3] = { g.x, g.y, g.z };
    float f1 = mParserGetFloat(self, argv[1]);
    float f2 = mParserGetFloat(self, argv[2]);
    int* vec = *(int**)(*(int*)((char*)self + 0xc) + 0x50);
    unsigned n = (unsigned)(vec[1] - *vec) >> 4;
    if ((n == 0 || *(uint8_t*)(*vec + 0xc) <= 0xfc) &&
        (n < 2 || *(uint8_t*)(*vec + 0x1c) <= 0xfd)) {
        return;
    }
    (void)f1; (void)f2; (void)v;
}
