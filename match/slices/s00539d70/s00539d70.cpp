// Swarm skin-paint "particle" effect block: ctor/dtor, registration, the brush
// description init/copy and the eval-list serialization.
// Unoptimized module. Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS- /EHsc
#include "types.h"

typedef unsigned int size_t;

void* operator new[](size_t, const char*, int, unsigned, const char*, int);
inline void* operator new(size_t n, const char* name, int f, unsigned d, const char* file, int line) {
    return operator new[](n, name, f, d, file, line);
}
inline void* operator new(size_t, void* p) { return p; }
extern "C" size_t __cdecl strlen(const char*);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);

extern char gEmptyString[];                                       // @ 0x1667bac

// A four-pointer eval vector.  Its assign is a thiscall (ret 4) on the destination, matching
// ?Vector16Assign@BlobVec@@QAEPAU1@PBU1@@Z (the same shape as the other two eval assigns).
struct Vector16 {
    void* a; void* b; void* c; void* d;
    Vector16* VectorAssign(const Vector16* src);                   // 0x50d4e0
};

void __cdecl EASTL_allocator_deallocate(void* p);                 // 0x00f47380

namespace eastl {
class allocator { public: void deallocate(void* p, size_t) { EASTL_allocator_deallocate(p); } };
struct basic_string {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator mAllocator;
    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~basic_string() {
        if ((int)(mpCapacity - mpBegin) > 1)
            mAllocator.deallocate(mpBegin, (size_t)(mpCapacity - mpBegin));
    }
    basic_string& assign(const char* first, const char* last);    // @ 0x454cb0
};
}  // namespace eastl

struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} };
inline cSPVector3 Vec3(float a, float b, float c) { return cSPVector3(a, b, c); }

namespace EA { namespace IO { struct IStream {}; } }
bool ReadInt32(EA::IO::IStream*, int32_t*, size_t, int);          // @ 0x93a780
bool ReadUInt8(EA::IO::IStream*, uint8_t*, size_t);               // @ 0x93a6c0
bool ReadUInt16(EA::IO::IStream*, uint16_t*, size_t, int);        // @ 0x93a700
bool WriteUInt32(EA::IO::IStream*, const uint32_t*, size_t, int); // @ 0x93aa70
void WriteUInt8(EA::IO::IStream*, const uint8_t*, size_t);        // operator<< // 0x0093a9a0
bool WriteUInt16(EA::IO::IStream*, const uint16_t*, size_t, int);

// ---------------------------------------------------------------- ArgScript
struct cSPSkinPaintParticleDescription;

namespace EA { namespace ArgScript {
class cIParser { public:
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void V35();                                          // +0x8c
    virtual void PushMetaCommand(void* cmd, const char* end);    // +0x90
    PV(37) virtual float GetFloat(const char*);
#undef PV
};
class cArguments { public:
    const char** MainArguments(size_t* pCount, int min, int max);  // 0x838020
    const char** MainArguments(int count);                         // 0x838320
    const char** OptionArguments(const char* name, int count);     // 0x838330
    bool HasFlag(const char* flag);                                // 0x8380b0
};
struct cState { uint32_t mStateID; };
class cICommand { public: virtual void AddRef(); virtual void Release(); virtual void Cast(); };
class cCommandBase : public cICommand { public: cIParser* mParser; int mRefCount; };
class cBlockCommandBase : public cICommand { public:
    cIParser* mParser; int mRefCount; cState* mChildState; char mCommands[0x20];
    ~cBlockCommandBase();                                        // 0x0083cd90
};
template <class T, class B> struct cCommandStateT : B { T* mState; };
template <class T> class cBlockCommandT : public cCommandStateT<T, cBlockCommandBase> { public:};
} }  // namespace EA::ArgScript

namespace EA { namespace Swarm {
struct cSPSkinPaintParticleDescription;
class cEffectsParser : public EA::ArgScript::cCommandBase { public:
    cSPSkinPaintParticleDescription* GetInheritedDescription(const char** a, size_t n, int t); // 0xa6f090
    void AddDescription(EA::ArgScript::cArguments& a, const char* n, int t, int f); // 0xa6fc30
};
} }

void cBlockCommandBaseCtor(EA::ArgScript::cBlockCommandBase*);    // 0x83c800
void FUN_00a6f9c0(void* parser, int type, void* desc);            // 0xa6f9c0
void* SP_EffectsManager();                                        // 0x67ddd0
void* EASTL_allocator_allocate(size_t, const char*, int, unsigned, const char*, int); // 0xf473a0
void EvalResizeA(void* vec, int n);                               // 0x53b520
void EvalResizeB(void* vec, int n);                               // 0x53b8a0
void EvalResizeC(void* vec, int n);                               // 0x4afc80

// ---------------------------------------------------------------- description
struct cSPSkinPaintParticleDescription;

struct EvalVec16 {
    char mItems[0x14];                                            // +0x00
    EvalVec16* Vector16Assign(const EvalVec16* src);               // 0x53b210
};
struct EvalVec20 {
    char mItems[0x14];                                            // +0x00
    EvalVec20* Vector20Assign(const EvalVec20* src);               // 0x53b5a0
};
struct EvalList {
    EvalVec16 m0;                                                 // +0x00
    EvalVec20 m1;                                                 // +0x14
    Vector16 m2;                                                  // +0x28
    char pad[4];
    EvalList& operator=(const EvalList& o);                       // 0x53a420
};

// @ 0x0053a420
__declspec(noinline) EvalList& EvalList::operator=(const EvalList& o)
{
    m0.Vector16Assign(&o.m0);
    m1.Vector20Assign(&o.m1);
    m2.VectorAssign(&o.m2);
    return *this;
}

// The brush block is polymorphic: its vptr sits at +0x00 (the description ctor stores it there and
// operator= starts at +0x04, so the copy never touches it).  The block destructor releases the
// brush, i.e. slot 1 (Release) of that vptr, with the brush block itself as the receiver.
struct IBrushRef { virtual void AddRef(); virtual void Release(); };
struct BrushDesc_s0053_9d70 {
    void** mpVtbl;                // +0x00
    Vector16 mHashes;             // +0x04
    char pad1[4];
    int mChainId;                 // +0x18
    uint32_t mFlags;              // +0x1c
    cSPVector3 mUserColorHSV;     // +0x20
    char mUserColorIndex;         // +0x2c
    uint8_t mAlignment;           // +0x2d
    uint8_t mInitialDirection;    // +0x2e
    uint8_t mAttraction;          // +0x2f
    cSPVector3 mAlignTarget;      // +0x30
    cSPVector3 mInitialDirTarget; // +0x3c
    cSPVector3 mAttractTarget;    // +0x48
    float mAttractStrength;       // +0x54
    float mDelayMin;              // +0x58
    float mDelayMax;              // +0x5c
    float mLifeMin;               // +0x60
    float mLifeMax;               // +0x64
    uint32_t mInheritMask;        // +0x68
    EvalList mEvalList;           // +0x6c
    uint8_t mBlend0;              // +0xa8
    uint8_t mBlend1;              // +0xa9
    uint8_t mBlend2;              // +0xaa
    int mRuntimeComponentId;      // +0xac

    void Init();                                                  // @ 0x53a530
    BrushDesc_s0053_9d70& operator=(const BrushDesc_s0053_9d70& o); // 0x53a2b0
    struct cSPSkinPaintParticleDescription* GetRuntimeDesc();     // 0x53a4a0
};

struct DescriptionBase { virtual void d0(); virtual void d1(); int mnRefCount; };
struct cSPSkinPaintParticleDescription : DescriptionBase { BrushDesc_s0053_9d70 mBrush; };

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p) { mpObject = p; return *this; } // @ 0x53b160
    operator T*() const { return mpObject; }
};

// ---------------------------------------------------------------- block command
class cSPSkinPaintParticleEffectBlockCommand
    : public EA::ArgScript::cBlockCommandT<EA::Swarm::cEffectsParser>, public EA::ArgScript::cState {
public:
    eastl::basic_string mName;                                    // +0x38
    AutoRefCount<cSPSkinPaintParticleDescription> mpDesc;         // +0x48
    int mCurrentModifier;                                         // +0x4c
    EvalList* mpEvalList;                                         // +0x50

    cSPSkinPaintParticleEffectBlockCommand();                     // 0x539f90
    ~cSPSkinPaintParticleEffectBlockCommand();                    // 0x53a220
    void Parse(EA::ArgScript::cArguments& args);                  // @ 0x53a030
    void SetChild(int b);                                         // @ 0x53a1a0
};

struct IRegA {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void AddBlock(const char* name, void* cmd);           // +0x14
};
struct IRegB {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5();
    virtual void AddCommand(const char* name, void* cmd);         // +0x18
};

extern const char* kInheritNames[];                               // 0x13f2e78 (19)
extern const char* kParticleKeyword;                              // 0x13f2ec8

// ================================================================ functions

// Stub receiver: the "inherit" command object arrives in ECX; its cState pointer is at +0xc.
struct cSPSkinPaintParticleinheritCommand {
    char pad[0xc];
    void* mpState;
    void Execute(EA::ArgScript::cArguments& args);
};

// @ 0x00539d70
void cSPSkinPaintParticleinheritCommand::Execute(EA::ArgScript::cArguments& args)
{
    cSPSkinPaintParticleEffectBlockCommand* state =
        (cSPSkinPaintParticleEffectBlockCommand*)mpState;
    cSPSkinPaintParticleDescription* A;
    cSPSkinPaintParticleDescription* pDesc;
    pDesc = A;
    pDesc = state->mpDesc;
    BrushDesc_s0053_9d70* p = pDesc ? &pDesc->mBrush : 0;
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 0x32);
    for (size_t i = 0; i < count; ++i) {
        if (_stricmp(argv[i], "diffuseColor") == 0) {
            p->mInheritMask |= 0x80;
            p->mInheritMask |= 0x100;
            p->mInheritMask |= 0x200;
        } else {
            for (int j = 0; j < 0x13; ++j) {
                if (_stricmp(argv[i], kInheritNames[j]) == 0) {
                    p->mInheritMask |= 1u << j;
                    break;
                }
            }
        }
    }
}

// @ 0x00539ed0
void SWARM_SPSkinPaintParticleAddCommands(IRegB* a, IRegA* b)
{
    void* p = EASTL_allocator_allocate(0x54, "ArgScript/SPSkinPaintParticleEffectBlock", 0, 0, 0, 0);
    void* block = p ? (void*)new (p) cSPSkinPaintParticleEffectBlockCommand() : 0;
    b->AddBlock(kParticleKeyword, block);

    void* q = EASTL_allocator_allocate(0x10, "ArgScript/SPSkinPaintParticleEffect", 0, 0, 0, 0);
    if (q) {
        cBlockCommandBaseCtor((EA::ArgScript::cBlockCommandBase*)q);
        *(void**)q = (void*)0x13f1ffc;
        *(void**)q = (void*)0x13f1ffc;
        *(void**)q = (void*)0x13f332c;
    }
    a->AddCommand(kParticleKeyword, q);
}

// @ 0x00539f90
cSPSkinPaintParticleEffectBlockCommand::cSPSkinPaintParticleEffectBlockCommand()
    : mCurrentModifier(0), mpEvalList(0) {
    mStateID = 0x2c96c27;
    mName.mpBegin = gEmptyString;
    mName.mpEnd = mName.mpBegin;
    mName.mpCapacity = mName.mpBegin + 1;
    mpDesc = 0;
}

// @ 0x0053a030
void cSPSkinPaintParticleEffectBlockCommand::Parse(EA::ArgScript::cArguments& args)
{
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 3);
    const char* s = argv[0];
    mName.assign(s, s + strlen(s));

    cSPSkinPaintParticleDescription* d =
        (cSPSkinPaintParticleDescription*)EASTL_allocator_allocate(0xb8, "Skinner", 0, 0, 0, 0);
    if (d)
        new (d) cSPSkinPaintParticleDescription();
    mpDesc = d;
    d->mBrush.Init();
    mCurrentModifier = 0xff;
    mpEvalList = &d->mBrush.mEvalList;

    if ((int)count > 1) {
        cSPSkinPaintParticleDescription* inh =
            (cSPSkinPaintParticleDescription*)mState->GetInheritedDescription(argv, count, 0x26);
        if (inh) {
            d->mBrush = inh->mBrush;
            d->mBrush.mRuntimeComponentId = inh->mBrush.mRuntimeComponentId;
        }
    }
    mParser->V35();
}

// @ 0x0053a1a0
void cSPSkinPaintParticleEffectBlockCommand::SetChild(int b)
{
    if (b == 0)
        FUN_00a6f9c0(mState, 0x26, mpDesc.mpObject);
    mpDesc = (cSPSkinPaintParticleDescription*)0;
}

// @ 0x0053a220
cSPSkinPaintParticleEffectBlockCommand::~cSPSkinPaintParticleEffectBlockCommand()
{
    if (mpDesc.mpObject) {
        IBrushRef* brush = (IBrushRef*)&mpDesc.mpObject->mBrush;
        brush->Release();
    }
}

// @ 0x0053a2b0
BrushDesc_s0053_9d70& BrushDesc_s0053_9d70::operator=(const BrushDesc_s0053_9d70& o)
{
    mHashes.VectorAssign(&o.mHashes);
    mChainId = o.mChainId;
    mFlags = o.mFlags;
    mUserColorHSV = o.mUserColorHSV;
    mUserColorIndex = o.mUserColorIndex;
    mAlignment = o.mAlignment;
    mInitialDirection = o.mInitialDirection;
    mAttraction = o.mAttraction;
    mAlignTarget = o.mAlignTarget;
    mInitialDirTarget = o.mInitialDirTarget;
    mAttractTarget = o.mAttractTarget;
    mAttractStrength = o.mAttractStrength;
    mDelayMin = o.mDelayMin;
    mDelayMax = o.mDelayMax;
    mLifeMin = o.mLifeMin;
    mLifeMax = o.mLifeMax;
    mInheritMask = o.mInheritMask;
    mEvalList = o.mEvalList;
    mBlend0 = o.mBlend0;
    mBlend1 = o.mBlend1;
    mBlend2 = o.mBlend2;
    return *this;
}

// Stub receiver: the AddDesc command object arrives in ECX; its parser pointer is at +0xc.
struct cSPSkinPaintParticleAddDescCommand {
    char pad[0xc];
    EA::Swarm::cEffectsParser* mpParser;
    void AddDesc(EA::ArgScript::cArguments& args);
};

// @ 0x0053a460
void cSPSkinPaintParticleAddDescCommand::AddDesc(EA::ArgScript::cArguments& args)
{
    const char** argv = args.MainArguments(1);
    EA::Swarm::cEffectsParser* parser = mpParser;
    parser->AddDescription(args, argv[0], 0x26, 0);
}

// @ 0x0053a4a0
// The original receives the BrushDesc (chain id at +0x18, runtime component id at +0xac) in ECX.
cSPSkinPaintParticleDescription* BrushDesc_s0053_9d70::GetRuntimeDesc()
{
    BrushDesc_s0053_9d70* b = this;
    void** mgr = (void**)SP_EffectsManager();
    if (!mgr || b->mChainId < 0 || b->mRuntimeComponentId < 0)
        return 0;
    char* res = (char*)(*(void*(__thiscall**)(int, int, int))((*(void***)mgr)[0x70 / 4]))(
        0x26, b->mChainId, b->mRuntimeComponentId);
    *(int*)(res + 0xb4) = b->mRuntimeComponentId;
    return (cSPSkinPaintParticleDescription*)(res ? res + 8 : 0);
}

// @ 0x0053a530
void BrushDesc_s0053_9d70::Init()
{
    mFlags = 0;
    mChainId = -1;
    mInheritMask = 0;
    mAlignment = 0;
    mAlignTarget = Vec3(0.0f, 1.0f, 0.0f);
    mInitialDirection = 0;
    mInitialDirTarget = Vec3(0.0f, 1.0f, 0.0f);
    mAttraction = 0;
    mAttractTarget = Vec3(0.0f, 1.0f, 0.0f);
    mAttractStrength = 0.0f;
    mDelayMax = 0.0f;
    mDelayMin = 0.0f;
    mLifeMax = 0.0f;
    mLifeMin = 0.0f;
    mUserColorHSV = Vec3(0.0f, 0.0f, 1.0f);
    mUserColorIndex = (char)0xff;
    mBlend0 = 0;
    mBlend1 = 0;
    mBlend2 = 0;
}

// @ 0x0053a6d0
EA::IO::IStream* ReadEvalList(EA::IO::IStream* stream, EvalList* e)
{
    int32_t n = 0;
    char* begin;
    ReadInt32(stream, &n, 1, 0);
    EvalResizeA(e, n);
    begin = *(char**)e;
    for (int i = 0; i < n; ++i) {
        char* p = begin + (size_t)i * 0x10;
        ReadInt32(stream, (int32_t*)p, 1, 0);
        ReadInt32(stream, (int32_t*)(p + 4), 1, 0);
        ReadInt32(stream, (int32_t*)(p + 8), 1, 0);
        ReadUInt8(stream, (uint8_t*)(p + 0xc), 1);
        ReadUInt8(stream, (uint8_t*)(p + 0xd), 1);
        ReadUInt16(stream, (uint16_t*)(p + 0xe), 1, 0);
    }
    ReadInt32(stream, &n, 1, 0);
    EvalResizeB((char*)e + 0x14, n);
    begin = *(char**)((char*)e + 0x14);
    for (int i = 0; i < n; ++i) {
        char* p = begin + (size_t)i * 0x14;
        ReadInt32(stream, (int32_t*)p, 1, 0);
        ReadInt32(stream, (int32_t*)(p + 4), 1, 0);
        ReadInt32(stream, (int32_t*)(p + 8), 1, 0);
        ReadInt32(stream, (int32_t*)(p + 0xc), 1, 0);
        ReadUInt8(stream, (uint8_t*)(p + 0x10), 1);
        ReadUInt8(stream, (uint8_t*)(p + 0x11), 1);
        ReadUInt8(stream, (uint8_t*)(p + 0x12), 1);
        ReadUInt8(stream, (uint8_t*)(p + 0x13), 1);
    }
    ReadInt32(stream, &n, 1, 0);
    EvalResizeC((char*)e + 0x28, n);
    int* ivec = *(int**)((char*)e + 0x28);
    for (int i = 0; i < n; ++i)
        ReadInt32(stream, ivec + i, 1, 0);
    return stream;
}

// @ 0x0053a930
EA::IO::IStream* WriteEvalList(EA::IO::IStream* stream, EvalList* e)
{
    uint32_t n = (uint32_t)(((char**)((char*)e + 4))[0] - *(char**)e) >> 4;
    WriteUInt32(stream, &n, 1, 0);
    for (uint32_t i = 0; i < n; ++i) {
        int* p = (int*)(*(char**)e + (size_t)i * 0x10);
        uint32_t v;
        v = p[0]; WriteUInt32(stream, &v, 1, 0);
        v = p[1]; WriteUInt32(stream, &v, 1, 0);
        v = p[2]; WriteUInt32(stream, &v, 1, 0);
        uint8_t b = *(uint8_t*)(p + 3) & 0xff; WriteUInt8(stream, &b, 1);
        b = *(uint8_t*)((char*)p + 0xd); WriteUInt8(stream, &b, 1);
        uint16_t w = *(uint16_t*)((char*)p + 0xe); WriteUInt16(stream, &w, 1, 0);
    }
    n = (uint32_t)(((char**)((char*)e + 0x18))[0] - *(char**)((char*)e + 0x14)) / 0x14;
    WriteUInt32(stream, &n, 1, 0);
    for (uint32_t i = 0; i < n; ++i) {
        int* p = (int*)(*(char**)((char*)e + 0x14) + (size_t)i * 0x14);
        uint32_t v;
        v = p[0]; WriteUInt32(stream, &v, 1, 0);
        v = p[1]; WriteUInt32(stream, &v, 1, 0);
        v = p[2]; WriteUInt32(stream, &v, 1, 0);
        v = p[3]; WriteUInt32(stream, &v, 1, 0);
        uint8_t b = *(uint8_t*)(p + 4); WriteUInt8(stream, &b, 1);
        b = *(uint8_t*)((char*)p + 0x11); WriteUInt8(stream, &b, 1);
        b = *(uint8_t*)((char*)p + 0x12); WriteUInt8(stream, &b, 1);
        b = *(uint8_t*)((char*)p + 0x13); WriteUInt8(stream, &b, 1);
    }
    n = (uint32_t)(((int**)((char*)e + 0x2c))[0] - *(int**)((char*)e + 0x28)) >> 2;
    WriteUInt32(stream, &n, 1, 0);
    for (uint32_t i = 0; i < n; ++i) {
        uint32_t v = (uint32_t)(*(int**)((char*)e + 0x28))[i];
        WriteUInt32(stream, &v, 1, 0);
    }
    return stream;
}
// --- equivalence checker address annotations
    void WriteUInt8(...); // 0x0093a9a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
