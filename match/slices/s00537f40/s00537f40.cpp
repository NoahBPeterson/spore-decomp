// Slice s00537f40: Swarm skin-paint particle effect (transform copy, refcount) and its
// ArgScript command. Large/algorithmic functions are stubs (partial.txt). Unoptimized
// module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* GetPaintSystem();                                                     // 0x00401080

// ---------------------------------------------------------------- cSPTransform (0x38)
struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModCount;
    float mTranslation[3];
    float mScale;
    float mRotation[9];
    cSPTransform();
    cSPTransform(const cSPTransform& x);    // @ 0x00538000
    cSPTransform& operator=(const cSPTransform& x);
    void Compound(const cSPTransform& x);   // @ 0x00537f40
};
void Matrix3Assign(float* dst, const float* src);   // 0x0041cb40

// @ 0x00538000
cSPTransform::cSPTransform(const cSPTransform& x)
{
    mFlags = x.mFlags;
    mModCount = x.mModCount;
    mTranslation[0] = x.mTranslation[0];
    mTranslation[1] = x.mTranslation[1];
    mTranslation[2] = x.mTranslation[2];
    mScale = x.mScale;
    Matrix3Assign(mRotation, x.mRotation);
}

// ---------------------------------------------------------------- @ 0x00538420
void Wrapper538420Impl(void* p, void* q);   // 0x0053aea0
void Wrapper538420(void* a, void* b)
{
    Wrapper538420Impl(b, a);
}

// ---------------------------------------------------------------- refcount adjustors
struct RefCountBase {
    virtual int AddRef();
    virtual int Release();
    int mRefCount;
};
void RefCountBase_Release(RefCountBase* p);   // 0x00453540

struct Host538380 {
    int AddRef();
};
// @ 0x00538380
int Host538380::AddRef()
{
    int* p = (int*)((char*)this - 4);
    int n = *p;
    *p = n + 1;
    return n + 1;
}

struct Host5383c0 {
    void Release();
};
// @ 0x005383c0
void Host5383c0::Release()
{
    RefCountBase_Release((RefCountBase*)((char*)this - 8));
}

// ---------------------------------------------------------------- stubs (partial)
// @ 0x00537f40
void TransformCompoundStub() {}
// @ 0x00538080
void EffectUpdateStub() {}
// @ 0x00538180
void EffectDtorStub() {}
// @ 0x00538200
void EffectCreateStub() {}
// @ 0x00538260
void EffectCtorStub() {}
// @ 0x00538320
void EvalListDtorStub() {}
// ---------------------------------------------------------------- particle effect block command
// The ArgScript block "SPSkinPaintParticle" (OnRegister) and some of its line commands.
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, size_t);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl isdigit(int);
extern "C" __declspec(dllimport) long __cdecl atol(const char*);

void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }

struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                // @ 0x4098a0 (out of line)
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
};
cSPVector3 RGBToHSV(cSPVector3 rgb);            // @ 0x529d30
// SSE clamp to [0, hi] (maxss/minss against memory params), the original's inline helper.
inline float Clamp(float v, float hi)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, v
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}
uint32_t FNV1_String8(const char* s, uint32_t basis, int flag);   // 0x00932e80

namespace EA { namespace ArgScript {
#define PADV(n) virtual void pv##n();
struct cState { int mID; };
class cIParser { public:
    PADV(0) PADV(1) PADV(2) PADV(3) PADV(4) PADV(5) PADV(6) PADV(7) PADV(8) PADV(9)
    PADV(10) PADV(11) PADV(12) PADV(13) PADV(14) PADV(15) PADV(16) PADV(17) PADV(18) PADV(19)
    PADV(20) PADV(21) PADV(22) PADV(23) PADV(24) PADV(25) PADV(26) PADV(27) PADV(28) PADV(29)
    PADV(30) PADV(31) PADV(32) PADV(33) PADV(34) PADV(35) PADV(36) PADV(37)
    PADV(38) PADV(39) PADV(40) PADV(41) PADV(42) PADV(43)
    virtual Vector3T GetVector(const char* text);     // +0xb0
};
class cArguments { public:
    const char** MainArguments(size_t* pCount, int minCount, int maxCount) const;  // 0x838020
    bool HasFlag(const char* flag) const;                                          // 0x8380b0
};
class cICommand { public:
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
class cCommandBase : public cICommand { public:
    cIParser* mParser;      // +0x4
    int mRefCount;          // +0x8
};
class cBlockCommandBase { public:
    virtual ~cBlockCommandBase();
    PADV(1) PADV(2) PADV(3) PADV(4) PADV(5)
    virtual void AddCommand(const char* name, cICommand* command);       // +0x18
    cIParser* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cState* mChildState;                        // +0x0c
    uint32_t mCommands[8];                      // +0x10
    void OnRegister(cIParser* parser, cState* state);   // 0x0083c780
    void SetChildState(cState* state);                  // 0x00fd9450
};
} }
namespace EA { namespace Swarm {
class cEffectsParser { public:
    uint32_t mBase[3];
    EA::ArgScript::cState mState;                        // +0xc
    int FindComponent(const char* name, int type);       // 0x00a6eb60
};
} }
using EA::ArgScript::cArguments;

struct SimpleVectorU32 {
    uint32_t d[5];
    void push_back(const uint32_t& v);                  // 0x00454860
};
struct BrushDesc538 {
    uint32_t pad0;
    SimpleVectorU32 mChain;             // +0x04
    int mComponent;                     // +0x18
    uint32_t mFlags;                    // +0x1c
    cSPVector3 mUserColorHSV;           // +0x20
    char mUserColorIndex;               // +0x2c
};
struct Description538 {
    virtual void d0();
    virtual void d1();
    int mnRefCount;
    BrushDesc538 mBrush;                // +0x8
};
template <class T> struct AutoRefCount { T* mpObject; operator T*() const { return mpObject; } };

// Command objects are 0x10 bytes: vptr, parser, refcount, state.
struct CommandRootB : EA::ArgScript::cICommand { EA::ArgScript::cIParser* mParser; int mRefCount; CommandRootB(); };   // ctor 0x0053b1f0
struct CommandRootA : EA::ArgScript::cICommand { EA::ArgScript::cIParser* mParser; int mRefCount; CommandRootA(); };   // ctor 0x0053b1c0
struct cSPSkinPaintParticleEffectBlockCommand;
struct PaintCompat : CommandRootB {                                                                  // vtable 0x013f2424
    cSPSkinPaintParticleEffectBlockCommand* mState;     // +0xc
    PaintCompat() {}
    virtual void ParseLine(cArguments& args);
};

struct cBlockCommandStateT : EA::ArgScript::cBlockCommandBase {
    EA::Swarm::cEffectsParser* mState;                  // +0x30
};
struct cSPSkinPaintParticleEffectBlockCommand : cBlockCommandStateT, EA::ArgScript::cState {   // cState at +0x34
    char pad[0x48 - 0x38];
    AutoRefCount<Description538> mpDesc;                // +0x48
    void OnRegister(EA::ArgScript::cIParser* parser, EA::ArgScript::cState* state);
};

namespace {
#define CMD(N) struct N : PaintCompat { N() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticlebrushCommand : PaintCompat {
    cSPSkinPaintParticlebrushCommand() {}
    virtual void ParseLine(cArguments& args);
};
struct cSPSkinPaintParticlecurveCommand : PaintCompat { cSPSkinPaintParticlecurveCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticlechainCommand : PaintCompat { cSPSkinPaintParticlechainCommand() {}
    virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticlealignCommand : PaintCompat { cSPSkinPaintParticlealignCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticleinitDirCommand : PaintCompat { cSPSkinPaintParticleinitDirCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticleattractCommand : PaintCompat { cSPSkinPaintParticleattractCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticlerestrictCommand : PaintCompat { cSPSkinPaintParticlerestrictCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticledelayCommand : PaintCompat { cSPSkinPaintParticledelayCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticlelifeCommand : PaintCompat { cSPSkinPaintParticlelifeCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticlediffuseColorCommand : PaintCompat {
    cSPSkinPaintParticlediffuseColorCommand() {}
    virtual void ParseLine(cArguments& args);
};
struct cSPSkinPaintParticlediffuseBlendCommand : PaintCompat { cSPSkinPaintParticlediffuseBlendCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticlespecularBlendCommand : PaintCompat { cSPSkinPaintParticlespecularBlendCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticlebumpBlendCommand : PaintCompat { cSPSkinPaintParticlebumpBlendCommand() {} virtual void ParseLine(cArguments& args); };
struct cSPSkinPaintParticleinheritCommand : CommandRootA {
    void* mState;                                       // +0xc
    cSPSkinPaintParticleinheritCommand() {}
    virtual void ParseLine(cArguments& args);
};
}  // namespace

// Command-name strings (pointer globals in the original).
extern const char* kNameBrush;          // 0x13f2ecc
extern const char* kNameCurve;          // 0x13f2f20
extern const char* kNameChain;          // 0x13f2f10
extern const char* kNameAlign;          // 0x13f2f24
extern const char* kNameInitDir;        // 0x13f2f28
extern const char* kNameAttract;        // 0x13f2f2c
extern const char* kNameRestrict;       // 0x13f2f30
extern const char* kNameDelay;          // 0x13f2f18
extern const char* kNameLife;           // 0x13f2f1c
extern const char* kNameDiffuseColor;   // 0x13f2f14
extern const char* kNameDiffuseBlend;   // 0x13f2f34
extern const char* kNameSpecularBlend;  // 0x13f2f38
extern const char* kNameBumpBlend;      // 0x13f2f3c
extern const char* kNameInherit;        // 0x13f2f40
template <class T> void RegisterPaintEvalCommands(T* block);    // 0x0053b930

// @ 0x00538440
void cSPSkinPaintParticleEffectBlockCommand::OnRegister(EA::ArgScript::cIParser* parser, EA::ArgScript::cState* state)
{
    mState = (EA::Swarm::cEffectsParser*)(state ? (char*)state - 0xc : 0);
    cBlockCommandBase::OnRegister(parser, state);
    SetChildState(static_cast<EA::ArgScript::cState*>(this));
    AddCommand(kNameBrush, new("ArgScript/SPSkinPaintParticlebrush", 0, 0, 0, 0) cSPSkinPaintParticlebrushCommand());
    AddCommand(kNameCurve, new("ArgScript/SPSkinPaintParticlecurve", 0, 0, 0, 0) cSPSkinPaintParticlecurveCommand());
    AddCommand(kNameChain, new("ArgScript/SPSkinPaintParticlechain", 0, 0, 0, 0) cSPSkinPaintParticlechainCommand());
    AddCommand(kNameAlign, new("ArgScript/SPSkinPaintParticlealign", 0, 0, 0, 0) cSPSkinPaintParticlealignCommand());
    AddCommand(kNameInitDir, new("ArgScript/SPSkinPaintParticleinitDir", 0, 0, 0, 0) cSPSkinPaintParticleinitDirCommand());
    AddCommand(kNameAttract, new("ArgScript/SPSkinPaintParticleattract", 0, 0, 0, 0) cSPSkinPaintParticleattractCommand());
    AddCommand(kNameRestrict, new("ArgScript/SPSkinPaintParticlerestrict", 0, 0, 0, 0) cSPSkinPaintParticlerestrictCommand());
    AddCommand(kNameDelay, new("ArgScript/SPSkinPaintParticledelay", 0, 0, 0, 0) cSPSkinPaintParticledelayCommand());
    AddCommand(kNameLife, new("ArgScript/SPSkinPaintParticlelife", 0, 0, 0, 0) cSPSkinPaintParticlelifeCommand());
    AddCommand(kNameDiffuseColor, new("ArgScript/SPSkinPaintParticlediffuseColor", 0, 0, 0, 0) cSPSkinPaintParticlediffuseColorCommand());
    AddCommand(kNameDiffuseBlend, new("ArgScript/SPSkinPaintParticlediffuseBlend", 0, 0, 0, 0) cSPSkinPaintParticlediffuseBlendCommand());
    AddCommand(kNameSpecularBlend, new("ArgScript/SPSkinPaintParticlespecularBlend", 0, 0, 0, 0) cSPSkinPaintParticlespecularBlendCommand());
    AddCommand(kNameBumpBlend, new("ArgScript/SPSkinPaintParticlebumpBlend", 0, 0, 0, 0) cSPSkinPaintParticlebumpBlendCommand());
    AddCommand(kNameInherit, new("ArgScript/SPSkinPaintParticleinherit", 0, 0, 0, 0) cSPSkinPaintParticleinheritCommand());
    RegisterPaintEvalCommands(this);
}

#define BRUSH538(p) \
    BrushDesc538* p; \
    { \
    Description538* A; \
    Description538* pDesc; \
    pDesc = A; \
    pDesc = mState->mpDesc; \
    p = pDesc ? &pDesc->mBrush : 0; \
    }

// @ 0x00538a00
void cSPSkinPaintParticlebrushCommand::ParseLine(cArguments& args)
{
    BRUSH538(p);
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 0, 100);
    for (int i = 0; i < (int)count; ++i) {
        uint32_t hash = FNV1_String8(argv[i], 0x811c9dc5, 1);
        p->mChain.push_back(hash);
    }
    if (args.HasFlag("random"))
        p->mFlags |= 1;
    else if (args.HasFlag("randomStart"))
        p->mFlags |= 2;
}

// @ 0x00538af0
void cSPSkinPaintParticlechainCommand::ParseLine(cArguments& args)
{
    BrushDesc538* obj;
    {
    Description538* p;
    Description538* brush;
    brush = p;
    brush = mState->mpDesc;
    obj = brush ? &brush->mBrush : 0;
    }
    size_t desc = 0;
    const char** other = args.MainArguments(&desc, 1, 1);
    EA::Swarm::cEffectsParser* src = mState->mState;
    obj->mComponent = src->FindComponent(other[0], 0x26);
    if (obj->mComponent < 0)
        do { } while (0);
}

// @ 0x00538b80
void cSPSkinPaintParticlediffuseColorCommand::ParseLine(cArguments& args)
{
    BRUSH538(p);
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    if (_strnicmp(argv[0], "color", 5) == 0 && isdigit((unsigned char)argv[0][5])) {
        uint32_t index = atol(argv[0] + 5) - 1;
        do { if (index >= 3) return; } while (0);
        p->mUserColorIndex = index;
        p->mUserColorHSV.Set(0.0f, 0.0f, 1.0f);
    } else if (_stricmp(argv[0], "identity") == 0) {
        p->mUserColorIndex = -2;
        p->mUserColorHSV.Set(0.0f, 0.0f, 1.0f);
    } else {
        cSPVector3 color = mParser->GetVector(argv[0]);
        color[0] = Clamp(color[0], 1.0f);
        color[1] = Clamp(color[1], 1.0f);
        color[2] = Clamp(color[2], 1.0f);
        p->mUserColorIndex = -1;
        p->mUserColorHSV = RGBToHSV(color);
    }
    if (args.HasFlag("identity"))
        p->mFlags |= 0x80;
}
