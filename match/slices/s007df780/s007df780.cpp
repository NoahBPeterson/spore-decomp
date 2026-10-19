// Slice s007df780 (w2g5 slice 25).  Region: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Swarm split-model-kernel description, kernel-storage setters and the
// ArgScript SplitModelKernelEffect command.
#include "types.h"
#include <string.h>
#include <math.h>

struct cSPVector3 { float x, y, z; };

// Error object thrown by the kernel-storage validators.
struct cError { cError(const char*); };

// ---------------------------------------------------------------- framework
namespace EA {
namespace Random {
struct RandomLinearCongruential {
    unsigned mState;
    void   SetSeed(unsigned seed);        // 0x00936090
    double RandomDoubleUniform();         // 0x009360d0
};
}
namespace IO {
bool WriteUint32(void* stream, const void* value, unsigned count, int endian);  // 0x0093aa70
}
namespace Text {
struct Font {
    char mPad[0x34];
    void SetUserData(void* p);            // 0x00fd9450
};
}
namespace ArgScript {
struct cArguments {
    const char** MainArguments(int* count, int lo, int hi);   // 0x00838020
};
struct cCommandBase {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    void Init();                          // 0x0083c800
};
}
namespace Swarm {
struct cEffectsParser {
    void AddDescription(void* args, const char* name, int type, int flag);   // 0x00a6fc30
    void AddAnonDescription(void* args, int type, void* desc, int flag);     // 0x00a6fd40
};
}
}

// base initialiser taking (parser, state).
struct cInitTwo {
    void Init(void* a, int b);            // 0x0083c780
};

// register a description object with the effects parser.
struct cEffectsFactory {
    void Add(void* a, int b, void* c);    // 0x00a6f9c0
};

// registered command-name slots (consecutive dwords).
extern void* gKernelCmdNames[8];          // 0x0153f1b0

void* __cdecl EAllocSwarm(int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

// ===========================================================================
// SP::cSplitModelKernelDescription::cSafeDynamicKernelStorage
// ===========================================================================
struct cSafeDynamicKernelStorage {
    int mKernelType;            // +0x0
    void* mKernelData;          // +0x4
    void* mKernelDataVariation; // +0x8

    void SetKernelType(int type);                              // 007e0340
    void SetNormal(const cSPVector3& a, const cSPVector3& b);  // 007e0420
    void SetOrigin(const cSPVector3& a, const cSPVector3& b);  // 007e0480
    void SetRadius(float a, float b);                          // 007e04f0
    void SetDirection(const cSPVector3& a, const cSPVector3& b);// 007e0570
    cSafeDynamicKernelStorage& operator=(const cSafeDynamicKernelStorage& o);  // 007e05e0

    void* CreateRandomKernel();                                // 007df780
    void  Serialize(void* stream);                             // 007dfac0
    cSafeDynamicKernelStorage* ConstructFrom(const cSafeDynamicKernelStorage& o);  // 007dfc20
};

void EFree2(void*);   // 0x00f47380

void cSafeDynamicKernelStorage::SetNormal(const cSPVector3& a, const cSPVector3& b)
{
    if (mKernelType != 0)
        throw cError("Either type not specified or type does not support this parameter");
    *(cSPVector3*)mKernelData = a;
    *(cSPVector3*)mKernelDataVariation = b;
}

void cSafeDynamicKernelStorage::SetOrigin(const cSPVector3& a, const cSPVector3& b)
{
    if (mKernelType == 1 || mKernelType == 2) {
        *(cSPVector3*)mKernelData = a;
        *(cSPVector3*)mKernelDataVariation = b;
        return;
    }
    throw cError("Either type not specified or type does not support this parameter");
}

void cSafeDynamicKernelStorage::SetRadius(float a, float b)
{
    if (mKernelType == 1) {
        *(float*)((char*)mKernelData + 0xc) = a;
        *(float*)((char*)mKernelDataVariation + 0xc) = b;
        return;
    }
    if (mKernelType == 2) {
        *(float*)((char*)mKernelData + 0x18) = a;
        *(float*)((char*)mKernelDataVariation + 0x18) = b;
        return;
    }
    throw cError("Either type not specified or type does not support this parameter");
}

void cSafeDynamicKernelStorage::SetDirection(const cSPVector3& a, const cSPVector3& b)
{
    if (mKernelType != 2)
        throw cError("Either type not specified or type does not support this parameter");
    *(cSPVector3*)((char*)mKernelData + 0xc) = a;
    *(cSPVector3*)((char*)mKernelDataVariation + 0xc) = b;
}

// ===========================================================================
// 0x007dfbf0  allocate a MapDescription, initialise its vtable.
// ===========================================================================
void* __cdecl EAllocSwarm(int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

void* FUN_007dfbf0()
{
    int* p = (int*)EAllocSwarm(8, "Swarm", 0, 0, 0, 0);
    if (p) {
        p[1] = 0;
        p[0] = 0x1453948;
        return p;
    }
    return 0;
}

// ===========================================================================
// 007df780..007e01a0  split-model-kernel description helpers and commands.
// ===========================================================================

// @ 0x007df780
void* cSafeDynamicKernelStorage::CreateRandomKernel()
{
    EA::Random::RandomLinearCongruential rng;
    rng.SetSeed(0xffffffffu);
    int type = mKernelType;
    if (type == 0) {
        const float* a = (const float*)mKernelData;
        const float* b = (const float*)mKernelDataVariation;
        float* out = (float*)EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        double r;
        r = rng.RandomDoubleUniform(); float x = (float)((r + r - 1.0) * b[0] + a[0]);
        r = rng.RandomDoubleUniform(); float y = (float)((r + r - 1.0) * b[1] + a[1]);
        r = rng.RandomDoubleUniform(); float z = (float)((r + r - 1.0) * b[2] + a[2]);
        float inv = 1.0f / sqrtf(x * x + y * y + z * z);
        out[0] = x * inv; out[1] = y * inv; out[2] = z * inv;
        r = rng.RandomDoubleUniform(); double v = (r + r - 1.0) * b[3] + a[3]; out[3] = (float)(v * v);
        return out;
    }
    if (type == 1) {
        const float* a = (const float*)mKernelData;
        const float* b = (const float*)mKernelDataVariation;
        float* out = (float*)EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        double r;
        r = rng.RandomDoubleUniform(); out[0] = (float)((r + r - 1.0) * b[0] + a[0]);
        r = rng.RandomDoubleUniform(); out[1] = (float)((r + r - 1.0) * b[1] + a[1]);
        r = rng.RandomDoubleUniform(); out[2] = (float)((r + r - 1.0) * b[2] + a[2]);
        r = rng.RandomDoubleUniform(); double v = (r + r - 1.0) * b[3] + a[3]; out[3] = (float)(v * v);
        return out;
    }
    if (type == 2) {
        const float* a = (const float*)mKernelData;
        const float* b = (const float*)mKernelDataVariation;
        float* out = (float*)EAllocSwarm(0x1c, "App", 0, 0, 0, 0);
        double r;
        r = rng.RandomDoubleUniform(); out[0] = (float)((r + r - 1.0) * b[0] + a[0]);
        r = rng.RandomDoubleUniform(); out[1] = (float)((r + r - 1.0) * b[1] + a[1]);
        r = rng.RandomDoubleUniform(); out[2] = (float)((r + r - 1.0) * b[2] + a[2]);
        r = rng.RandomDoubleUniform(); float x = (float)((r + r - 1.0) * b[3] + a[3]);
        r = rng.RandomDoubleUniform(); float y = (float)((r + r - 1.0) * b[4] + a[4]);
        r = rng.RandomDoubleUniform(); float z = (float)((r + r - 1.0) * b[5] + a[5]);
        float inv = 1.0f / sqrtf(x * x + y * y + z * z);
        out[3] = x * inv; out[4] = y * inv; out[5] = z * inv;
        r = rng.RandomDoubleUniform(); double v = (r + r - 1.0) * b[6] + a[6]; out[6] = (float)(v * v);
        return out;
    }
    return 0;
}

// @ 0x007dfac0
void cSafeDynamicKernelStorage::Serialize(void* stream)
{
    unsigned type = (unsigned)mKernelType;
    EA::IO::WriteUint32(stream, &type, 1, 0);
    switch (mKernelType) {
    case 0:
    case 1: {
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, mKernelData, 0xc);
        float v = *(float*)((char*)mKernelData + 0xc);
        EA::IO::WriteUint32(stream, &v, 1, 0);
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, mKernelDataVariation, 0xc);
        v = *(float*)((char*)mKernelDataVariation + 0xc);
        EA::IO::WriteUint32(stream, &v, 1, 0);
        break;
    }
    case 2: {
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, mKernelData, 0xc);
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, (char*)mKernelData + 0xc, 0xc);
        float v = *(float*)((char*)mKernelData + 0x18);
        EA::IO::WriteUint32(stream, &v, 1, 0);
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, mKernelDataVariation, 0xc);
        (*(void(__thiscall**)(void*, void*, int))((char*)(*(void**)stream) + 0x38))(stream, (char*)mKernelDataVariation + 0xc, 0xc);
        v = *(float*)((char*)mKernelDataVariation + 0x18);
        EA::IO::WriteUint32(stream, &v, 1, 0);
        break;
    }
    }
}

// @ 0x007dfbd0
void __cdecl FUN_007dfbd0(void* description, void* stream)
{
    ((cSafeDynamicKernelStorage*)((char*)description + 8))->Serialize(stream);
}

// @ 0x007dfc20
cSafeDynamicKernelStorage* cSafeDynamicKernelStorage::ConstructFrom(const cSafeDynamicKernelStorage& o)
{
    int type = o.mKernelType;
    if (type == 0 || type == 1) {
        float* p = (float*)EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        if (p) {
            const float* s = (const float*)o.mKernelData;
            p[0] = s[0]; p[1] = s[1]; p[2] = s[2]; p[3] = s[3];
        } else {
            p = 0;
        }
        mKernelData = p;
        p = (float*)EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        if (p) {
            const float* s = (const float*)o.mKernelDataVariation;
            p[0] = s[0]; p[1] = s[1]; p[2] = s[2]; p[3] = s[3];
            mKernelDataVariation = p;
            mKernelType = o.mKernelType;
            return this;
        }
    }
    else if (type == 2) {
        float* p = (float*)EAllocSwarm(0x1c, "App", 0, 0, 0, 0);
        if (p) {
            const float* s = (const float*)o.mKernelData;
            for (int i = 0; i < 7; ++i) p[i] = s[i];
        } else {
            p = 0;
        }
        mKernelData = p;
        p = (float*)EAllocSwarm(0x1c, "App", 0, 0, 0, 0);
        if (p) {
            const float* s = (const float*)o.mKernelDataVariation;
            for (int i = 0; i < 7; ++i) p[i] = s[i];
            mKernelDataVariation = p;
            mKernelType = o.mKernelType;
            return this;
        }
    }
    else {
        mKernelData = 0;
        mKernelDataVariation = 0;
        mKernelType = o.mKernelType;
        return this;
    }
    mKernelDataVariation = 0;
    mKernelType = o.mKernelType;
    return this;
}

// ---- 0x007dfd90: description-context command helper ----
struct cDescCtx {
    char  mPad[0xc];
    void* mParser;                       // +0xc

    void FUN_007dfd90(EA::ArgScript::cArguments* args);
};

// @ 0x007dfd90
void cDescCtx::FUN_007dfd90(EA::ArgScript::cArguments* args)
{
    int count = 0;
    const char** av = args->MainArguments(&count, 0, 1);
    if (count == 1) {
        ((EA::Swarm::cEffectsParser*)mParser)->AddDescription(args, av[0], 0x29, 0);
        return;
    }
    void** p = (void**)EAllocSwarm(8, "Swarm", 0, 0, 0, 0);
    if (p) { p[1] = 0; p[0] = (void*)0x1453948; }
    if (p) p[1] = (void*)((int)p[1] + 1);
    ((EA::Swarm::cEffectsParser*)mParser)->AddAnonDescription(args, 0x29, p, 0);
    if (p) {
        int rc = (int)p[1] - 1;
        p[1] = (void*)rc;
        if (rc == 0) {
            p[1] = (void*)1;
            (*(void(__thiscall**)(void*, int))(*(void**)p))(p, 1);
        }
    }
}

// ---- 0x007dfe80 SplitModelKernelEffect constructor ----
namespace EA { namespace ArgScript {
struct AppPropsFields {
    AppPropsFields();                    // 0x0083cdd0
    char mPad[0x34];
};
struct SplitModelKernelEffect : AppPropsFields {
    SplitModelKernelEffect();            // 0x007dfe80
    int   m34;
    void* m38;
    int   m3c;
    int   m40;
    int   m44;
    int   m48;
    void* m4c;
    void* m50;
    void* m54;
};
}}

// @ 0x007dfe80
EA::ArgScript::SplitModelKernelEffect::SplitModelKernelEffect()
{
    *(void**)this = (void*)0x1412d64;
    m34 = 0x30aa211;
    m3c = 0;
    m38 = (void*)0x1453948;
    m44 = 0;
    m48 = 0;
    m40 = -1;
    void* p = (void*)0x1667bac;
    m4c = p;
    m50 = p;
    m54 = (void*)0x1667bad;
}

static void RegisterKernelCommand(void* self, void* name, const char* allocName, void* vtbl)
{
    EA::ArgScript::cCommandBase* cmd = (EA::ArgScript::cCommandBase*)EAllocSwarm(0x10, allocName, 0, 0, 0, 0);
    if (cmd) {
        cmd->Init();
        *(void**)cmd = vtbl;
    } else {
        cmd = 0;
    }
    (*(void(__thiscall**)(void*, void*, void*))((char*)(*(void**)self) + 0x18))(self, name, cmd);
}

// ---- 0x007dfed0 / 0x007e0160 / 0x007e01a0: effect command object ----
struct cEffectCommand {
    void* mVtbl;                         // +0x00
    char  mPad04[0x2c];
    void* m30;                           // +0x30
    void* m34;                           // +0x34
    void* m38;                           // +0x38
    void* m3c;                           // +0x3c
    void* m40;                           // +0x40

    void FUN_007e0160(void* a, int b);          // 0x007e0160
    void FUN_007e01a0(char flag);               // 0x007e01a0
    void FUN_007dfed0(void* server, int state); // 0x007dfed0
};

// @ 0x007dfed0
void cEffectCommand::FUN_007dfed0(void* server, int state)
{
    m30 = state ? (void*)(state - 0xc) : 0;
    ((cInitTwo*)this)->Init(server, state);
    ((EA::Text::Font*)this)->SetUserData(&m34);
    RegisterKernelCommand(this, gKernelCmdNames[0], "ArgScript/SplitModelKernelType", (void*)0x1412d88);
    RegisterKernelCommand(this, gKernelCmdNames[2], "ArgScript/SplitModelKernelOffset", (void*)0x1412da0);
    RegisterKernelCommand(this, gKernelCmdNames[3], "ArgScript/SplitModelKernelRadius", (void*)0x1412db8);
    RegisterKernelCommand(this, gKernelCmdNames[1], "ArgScript/SplitModelKernelNormal", (void*)0x1412dd0);
    RegisterKernelCommand(this, gKernelCmdNames[4], "ArgScript/SplitModelKernelDirection", (void*)0x1412de8);
    RegisterKernelCommand(this, gKernelCmdNames[5], "ArgScript/SplitModelKernelOrigin", (void*)0x1412e00);
}

// ---- 0x007e0110: MapDescription constructor ----
struct cMapDescription {
    void* mVtbl;                         // +0x00
    int   mRef;                          // +0x04
    char  mPad08[4];

    void* FUN_007e0110(int other);       // 0x007e0110
};

// @ 0x007e0110
void* cMapDescription::FUN_007e0110(int other)
{
    mRef = 0;
    mVtbl = (void*)0x1453948;
    ((cSafeDynamicKernelStorage*)((char*)this + 8))->ConstructFrom(*(cSafeDynamicKernelStorage*)(other + 8));
    return this;
}

// @ 0x007e0160
void cEffectCommand::FUN_007e0160(void* a, int b)
{
    m30 = b ? (void*)(b - 0xc) : 0;
    ((cInitTwo*)this)->Init(a, b);
    ((EA::Text::Font*)this)->SetUserData(&m34);
}

// @ 0x007e01a0
void cEffectCommand::FUN_007e01a0(char flag)
{
    if (flag != 0)
        return;
    void** p = (void**)EAllocSwarm(8, "Swarm", 0, 0, 0, 0);
    if (p) {
        p[1] = 0;
        p[0] = (void*)0x1453948;
        ((cEffectsFactory*)m30)->Add(m40, 0x29, p);
    } else {
        ((cEffectsFactory*)m30)->Add(m40, 0x29, p);
    }
}
void FUN_007e0200() { /* 126B */ }                 // 007e0200
void FUN_007e0280() { /* 112B */ }                 // 007e0280
void FUN_007e02f0() { /* 65B  deleting dtor */ }   // 007e02f0

struct KernelData16 { uint32_t v[4]; };
struct KernelData28 { uint32_t v[7]; };
struct cKernelError {
    uint32_t pad[4];
    cKernelError(const char* fmt, ...);        // 0x0052df30 (cdecl, `this` pushed)
    cKernelError(const cKernelError&);
};

// @ 0x007e0340
void cSafeDynamicKernelStorage::SetKernelType(int type)
{
    if (mKernelData != 0) {
        EFree2(mKernelData);
        mKernelData = 0;
    }
    if (mKernelDataVariation != 0) {
        EFree2(mKernelDataVariation);
        mKernelDataVariation = 0;
    }
    switch (type) {
    case 0:
    case 1:
        mKernelData = EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        mKernelDataVariation = EAllocSwarm(0x10, "App", 0, 0, 0, 0);
        break;
    case 2:
        mKernelData = EAllocSwarm(0x1c, "App", 0, 0, 0, 0);
        mKernelDataVariation = EAllocSwarm(0x1c, "App", 0, 0, 0, 0);
        break;
    default:
        if (type < 0) {
            mKernelType = type;
            mKernelData = 0;
            return;
        }
        throw cKernelError("Unknown split model kernel type.");
    }
    mKernelType = type;
}

// @ 0x007e05e0
cSafeDynamicKernelStorage& cSafeDynamicKernelStorage::operator=(const cSafeDynamicKernelStorage& o)
{
    SetKernelType(o.mKernelType);
    int t = o.mKernelType;
    if (t != 0 && t != 1) {
        if (t != 2) {
            if (mKernelData != 0) {
                EFree2(mKernelData);
                mKernelData = 0;
            }
            if (mKernelDataVariation != 0) {
                EFree2(mKernelDataVariation);
                mKernelDataVariation = 0;
            }
            mKernelData = 0;
            mKernelType = -1;
            return *this;
        }
        memcpy(mKernelData, o.mKernelData, 0x1c);
        memcpy(mKernelDataVariation, o.mKernelDataVariation, 0x1c);
        return *this;
    }
    KernelData16* d = (KernelData16*)mKernelData;
    KernelData16* s = (KernelData16*)o.mKernelData;
    d->v[0] = s->v[0];
    d->v[1] = s->v[1];
    d->v[2] = s->v[2];
    d->v[3] = s->v[3];
    d = (KernelData16*)mKernelDataVariation;
    s = (KernelData16*)o.mKernelDataVariation;
    d->v[0] = s->v[0];
    d->v[1] = s->v[1];
    d->v[2] = s->v[2];
    d->v[3] = s->v[3];
    return *this;
}
