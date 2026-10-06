// SWARM game-model debug commands and the read/description helpers around
// 0x007d3930-0x007d4a33.  Matched functions: ReadAnimationCurves (0x7d40f0),
// Wrapper::Func (0x7d44a0), EffOwner::SetVisible (0x7d4820), VecOut::Allocate
// (0x7d48e0).  Every other function is present in a behaviorally complete or
// approximate form (see nonmatching.txt / partial.txt).
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <intrin.h>

void* operator new[](size_t size);
void  operator delete[](void* p);
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void  operator delete(void* p);

namespace EA {
namespace IO {
bool ReadInt32(void* s, int32_t* p, unsigned n, int endian);   // 0x93a780
}
namespace ArgScript {
class cArguments {
public:
    const char** MainArguments(int n);
    const char** MainArguments(int* count, int min, int max);
    const char** OptionArguments(const char* name, int n);
    const char** OptionArguments(const char* name, int* count, int min, int max);
    bool HasFlag(const char* name);
};
uint32_t ParseEnum(const char* value, const char** table);
}}
bool ReadBytes(void* s, void* p, unsigned n);                  // 0x93a6c0
void* ReadIntVector(void* stream, void* vec);                  // 0x7d27d0
uint32_t FNVHash(const char* s, uint32_t seed, int a);         // 0x932e80

struct IUnknown32 { virtual void AddRef(); virtual void Release(); };

// ----------------------------------------------------- IStream (slot 0x30 Read)
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual int Read(void* dst, uint32_t size);   // +0x30
};

// --------------------------------------------------------------- game model
namespace SP {
struct Vec20 { void* p0; void* p1; void* p2; void* p3; void* p4; };
struct cAnimationCurve {
    float mX, mY;
    Vec20 mCurve;          // +0x08
    float mA, mB, mC;      // +0x1c
    uint8_t mMode;         // +0x28
};
struct cGameModelDescription {
    void* vtbl; int mRefCount; int mStateID; uint32_t mFlags;
    float mSize; float mColourX, mColourY, mColourZ; float mAlpha;
    uint32_t mInstanceID, mGroupID, mWorldID;
    Vec20 mAnimationCurves, mModelSplitters, mSplitControllers, mGroups;
    uint32_t mFlagsToSet; uint8_t mPickLevel, mOverrideSet, pad86[2]; uint32_t field88;
    cGameModelDescription();
};
}

// ============================================================ 0x7d40f0 MATCH
struct AnimVec {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* a1; void* a2;
    void resize(unsigned n);   // 0x7d3770
};
// @ 0x007d40f0
IStream* ReadAnimationCurves(IStream* stream, AnimVec* vec) {
    int count;
    EA::IO::ReadInt32(stream, &count, 1, 0);
    vec->resize((unsigned)count);
    for (unsigned i = 0; i < (unsigned)count; ++i) {
        char* e = (char*)vec->mpBegin + i * 0x2c;
        stream->Read(e, 8);
        ReadIntVector(stream, e + 8);
        EA::IO::ReadInt32(stream, (int32_t*)(e + 0x1c), 1, 0);
        EA::IO::ReadInt32(stream, (int32_t*)(e + 0x20), 1, 0);
        EA::IO::ReadInt32(stream, (int32_t*)(e + 0x24), 1, 0);
        ReadBytes(stream, e + 0x28, 1);
    }
    return stream;
}

// ============================================================ 0x7d44a0 MATCH
struct Comp {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
    virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
    virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
    virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
    virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
    virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
    virtual void v88(); virtual void v89(); virtual void v90();
    virtual void SetOwner(void* owner, int flag);   // +0x16c
};
struct Wrapper { void* mpComp; void Func(); };
// @ 0x007d44a0
void Wrapper::Func() { ((Comp*)mpComp)->SetOwner(this, 1); }

// ============================================================ 0x7d4820 MATCH
struct EffComp {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9();
    virtual void SetFlag(int f);   // +0x28
};
struct EffOwner { void SetVisible(int param); };
// @ 0x007d4820
void EffOwner::SetVisible(int param) {
    *(uint8_t*)((char*)this + 0x15) = (uint8_t)param;
    _ReadWriteBarrier();
    unsigned count = (unsigned)((*(char**)((char*)this + 0xb0) - *(char**)((char*)this + 0xac)) >> 6);
    if (count != 0) {
        for (unsigned i = 0; i < count; ++i) {
            EffComp* c = *(EffComp**)(*(char**)((char*)this + 0xac) + i * 0x40 + 0x3c);
            c->SetFlag(param);
        }
    }
    void* p = *(void**)((char*)this + 0x38);
    if (p) {
        if ((char)param) *(uint32_t*)((char*)p + 4) |= 1;
        else *(uint32_t*)((char*)p + 4) &= ~1u;
    }
}

// ============================================================ 0x7d48e0 MATCH
struct VecOut {
    void* b; void* e; void* c;
    VecOut* Allocate(unsigned n, void* alloc);
};
// @ 0x007d48e0
VecOut* VecOut::Allocate(unsigned n, void* alloc) {
    void* buf = n ? operator new(n * 0x78, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    b = buf;
    e = buf;
    c = (char*)buf + n * 0x78;
    return this;
}

// ====================================================== remaining functions
struct cGameModelState { void* vtbl; SP::cGameModelDescription mDesc; };

// @ 0x007d3930  cGameModelAnimateCommand::Execute
struct cGameModelAnimateCommand {
    void* mParser;         // +0x4
    cGameModelState* mState;   // +0xc
    void Execute(EA::ArgScript::cArguments& args);
};
void cGameModelAnimateCommand::Execute(EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 1, 0x7fffffff);
    SP::cGameModelDescription* d = &mState->mDesc;
    char* curve = (char*)((char**)&d->mAnimationCurves)[0];
    (void)curve;
    SP::cAnimationCurve* c = (SP::cAnimationCurve*)curve;
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            // parser->ParseFloat(av[i]) appended to the curve's float vector
            float f = ((float(__thiscall*)(void*, const char*))((*(void***)mParser)[0x98 / 4]))(mParser, av[i]);
            (void)f;
            (void)c;
        }
    }
    const char** length = args.OptionArguments("length", 1);
    if (length) {
        float f = ((float(__thiscall*)(void*, const char*))((*(void***)mParser)[0x98 / 4]))(mParser, length[0]);
        (void)f;
    }
    const char** channel = args.OptionArguments("channel", 1);
    if (channel)
        *(uint32_t*)(curve + 0x24) = FNVHash(channel[0], 0x811c9dc5, 1);
    if (args.HasFlag("sustain")) *(uint8_t*)(curve + 0x28) = 1;
    else if (args.HasFlag("single")) *(uint8_t*)(curve + 0x28) = 2;
    else if (args.HasFlag("loop")) *(uint8_t*)(curve + 0x28) = 0;
    const char** vary = args.OptionArguments("vary", 1);
    if (vary)
        *(float*)(curve + 0x1c) = ((float(__thiscall*)(void*, const char*))((*(void***)mParser)[0x98 / 4]))(mParser, vary[0]);
    const char** ss = args.OptionArguments("speedScale", 1);
    if (ss)
        *(float*)(curve + 0x20) = ((float(__thiscall*)(void*, const char*))((*(void***)mParser)[0x98 / 4]))(mParser, ss[0]);
}

// @ 0x007d3b60  cGameModelSplitCommand::Execute  (large; skeleton)
void GameModelSplitCommand_Execute(void* self, void* args) {
    (void)self; (void)args;
}

// @ 0x007d41f0  cGameModelEffectCommand::Execute
void EffectCommand_Execute(void* self, EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 1, 3);
    (void)av;
    SP::cGameModelDescription tmp;
    (void)count; (void)tmp;
}

// @ 0x007d4300  SP::ReadDescription  (not fully decoded; skeleton)
void __cdecl ReadDescription(void* stream, void* a, void* desc) {
    (void)stream; (void)a; (void)desc;
}

// @ 0x007d44c0  make a fresh description from a stream
void* MakeState(void* a, void* b) {
    SP::cGameModelDescription* d = new ("Swarm", 0, 0, 0, 0) SP::cGameModelDescription();
    ReadDescription(a, b, d);
    return d;
}

// @ 0x007d4540
uint32_t TestKey(void* unused, const uint32_t* p, uint32_t* out, int n) {
    uint32_t lo = p[0x24 / 4];
    uint32_t hi = p[0x28 / 4];
    if ((lo & hi) != 0xffffffff) {
        if (n > 0) { out[0] = lo; out[1] = hi; out[2] = 0x102; }
        return 1;
    }
    return 0;
}

// @ 0x007d45d0
namespace EA { namespace Random {
class RandomLinearCongruential { public: double RandomDoubleUniform(); };
}}
extern EA::Random::RandomLinearCongruential gRandom;   // 0x16778dc
float __cdecl RandomRange(float a, float b) {
    double r = gRandom.RandomDoubleUniform();
    double lo = (double)a - (double)b;
    double hi = (double)a + (double)b;
    double v = r * (hi - lo) + lo;
    if (v < hi && lo <= v)
        return (float)v;
    return (float)v;
}

// @ 0x007d4620
struct cEffectParams {
    char pad[0xb4];
    IUnknown32* mUnknown[9];
    void UnknownStore(int idx, IUnknown32* p);
};
void cEffectParams::UnknownStore(int idx, IUnknown32* p) {
    IUnknown32* old = mUnknown[idx];
    if (p != old) {
        if (p) p->AddRef();
        mUnknown[idx] = p;
        if (old) old->Release();
    }
}

// @ 0x007d4670
void EffectTick(void* self, void* arg) {
    char* s = (char*)self;
    if (s[0x14]) {
        s[0x14] = 0;
        unsigned n = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
        for (unsigned i = 0; i < n; ++i) {
            void* c = *(void**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
            (*(void(__thiscall**)(void*, void*))((*(void***)c)[0xc / 4]))(c, arg);
        }
        void* p = *(void**)(s + 0x38);
        if (p && *(int*)((char*)p + 0x40) < 2)
            (*(void(__thiscall**)(void*, int))((*(void***)p)[0x16c / 4]))(p, 0);
    }
}

// @ 0x007d4730
char HandleEffectParam(void* self, int kind, float* value, void* extra) {
    char* s = (char*)self;
    char any = 0;
    switch (kind) {
        case 4:
            *(float*)(s + 0x2c) = *(float*)(*(int*)(s + 0xc) + 0x20) * value[0];
            any = 1; break;
        case 5:
            *(float*)(s + 0x20) = *(float*)(*(int*)(s + 0xc) + 0x14) * value[0];
            *(float*)(s + 0x24) = value[1] * *(float*)(*(int*)(s + 0xc) + 0x18);
            *(float*)(s + 0x28) = value[2] * *(float*)(*(int*)(s + 0xc) + 0x1c);
            any = 1; break;
        case 0x101:
            *(float*)(s + 0x80) = value[1];
            *(float*)(s + 0x88) = value[2];
            *(float*)(s + 0x84) = value[4];
            *(float*)(s + 0x8c) = value[5];
            any = 1; break;
        default: break;
    }
    unsigned n = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < n; ++i) {
        void* c = *(void**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = (*(char(__thiscall**)(void*, int, float*, void*))((*(void***)c)[0x1c / 4]))(c, kind, value, extra);
        if (r || any) any = 1;
    }
    return any;
}

// @ 0x007d4980  cSPTransform assignment then per-label loop (skeleton)
void AssignTransforms(void* self, void* src) {
    (void)self; (void)src;
}
