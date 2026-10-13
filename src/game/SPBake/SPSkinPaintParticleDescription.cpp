// src/game/SPBake/SPSkinPaintParticleDescription.cpp -- migrated from slice(s) s0053b930, s0053acc0, s00539d70, s00538e90 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinPaintParticleDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cIParser.h"
#include "EA/ArgScript/cIBlockCommand.h"
#include "EA/ArgScript/cState.h"

// unnamed retail callees and globals (address in the comment)
extern "C" double __cdecl sqrt(double);
extern const char* kAlphaNames[];      // 0x13f2ed0
#pragma intrinsic(sqrt)

// ---- items of slice s00538e90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s0053_8e90 {
    float x, y, z;
    cSPVector3_s0053_8e90() {}
    cSPVector3_s0053_8e90(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    float& operator[](int i) const { return ((float*)this)[i]; }
};
inline float Sqrt(float x) { volatile float r = (float)sqrt(x); return r; }
void Vector3Divide(cSPVector3_s0053_8e90* out, const cSPVector3_s0053_8e90* in, const float* scalar); // @ 0x453880
namespace EA {
namespace ArgScript {
#define PV(n) virtual void pv##n();
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s0053_8e90 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual float GetFloat(const char* text);          // +0x98
    PV(39) PV(40) PV(41)
    virtual cSPVector3_s0053_8e90 GetVector(const char* text);    // +0xa8
};
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s0053_8e90 {
    const char** MainArguments(size_t* pCount, int minCount, int maxCount);  // 0x838020
    const char** OptionArguments(const char* name, int count);               // 0x838330
    bool HasFlag(const char* flag);                                          // 0x8380b0
};
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s0053_8e90 {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s0053_8e90 : cICommand_s0053_8e90 {
    cIParser_s0053_8e90* mParser;      // +0x4
    int mRefCount;          // +0x8
};
}
}
namespace EA {
namespace Swarm {
uint8_t ParseEnum(const char* value, const char** nameTable);
}
}
namespace EA {
namespace Swarm {
float ParseRangedFloat(EA::ArgScript::cIParser_s0053_8e90* parser, const char* text, float lo, float hi);
}
}
struct BrushDesc {
    char pad0[0x1c];
    uint32_t mFlags;                    // +0x1c
    cSPVector3_s0053_8e90 mUserColorHSV;           // +0x20
    char mUserColorIndex;               // +0x2c
    uint8_t mAlignment;                 // +0x2d
    uint8_t mInitialDirection;          // +0x2e
    uint8_t mAttraction;                // +0x2f
    cSPVector3_s0053_8e90 mAlignTarget;            // +0x30
    cSPVector3_s0053_8e90 mInitialDirTarget;       // +0x3c
    cSPVector3_s0053_8e90 mAttractTarget;          // +0x48
    float mAttractStrength;             // +0x54
    float mDelayMin;                    // +0x58
    float mDelayMax;                    // +0x5c
    float mLifeMin;                     // +0x60
    float mLifeMax;                     // +0x64
    uint32_t mInheritMask;              // +0x68
    char pad1[0xa8 - 0x6c];
    uint8_t mBlend0;                    // +0xa8
    uint8_t mBlend1;                    // +0xa9
    uint8_t mBlend2;                    // +0xaa
};
struct DescriptionBase {
    virtual void d0();
    virtual void d1();
    int mnRefCount;
};
struct cSPSkinPaintParticleDescription_s0053_8e90 : DescriptionBase {
    BrushDesc mBrush;                   // +0x8
};
template <class T>
struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
};
struct cSPSkinPaintParticleEffectBlockCommand {
    char pad0[0x48];
    AutoRefCount<cSPSkinPaintParticleDescription_s0053_8e90> mpDesc;  // +0x48
};
#define BRUSH() \
    cSPSkinPaintParticleDescription_s0053_8e90* A; \
    cSPSkinPaintParticleDescription_s0053_8e90* pDesc; \
    BrushDesc* p; \
    pDesc = A; \
    pDesc = mState->mpDesc; \
    p = pDesc ? &pDesc->mBrush : 0;
namespace {
using EA::ArgScript::cArguments_s0053_8e90;

struct cSPSkinPaintParticledelayCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;   // +0xc
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticlelifeCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticlecurveCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticlealignCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticleinitDirCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticleattractCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticlerestrictCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticlediffuseColorCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticlespecularColorCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
struct cSPSkinPaintParticlebumpColorCommand : EA::ArgScript::cCommandBase_s0053_8e90 {
    cSPSkinPaintParticleEffectBlockCommand* mState;
    void Execute(cArguments_s0053_8e90& args);
};
}  // namespace
// ---- items of slice s00538e90 end



// ---- items of slice s00539d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern char gEmptyString[];                                       // @ 0x1667bac
extern const char* kInheritNames[];                               // 0x13f2e78 (19)
extern const char* kParticleKeyword;                              // 0x13f2ec8
void* operator new[](size_t, const char*, int, unsigned, const char*, int);
inline void* operator new(size_t n, const char* name, int f, unsigned d, const char* file, int line) {
    return operator new[](n, name, f, d, file, line);
}
inline void* operator new(size_t, void* p) { return p; }
extern "C" size_t __cdecl strlen(const char*);
struct Vector16 { void* a; void* b; void* c; void* d; };
void __cdecl EASTL_allocator_deallocate(void* p);                 // 0x00f47380
namespace eastl {
struct allocator_s0053_9d70 { void deallocate(void* p, size_t) { EASTL_allocator_deallocate(p); } };
}
namespace eastl {
struct basic_string_s0053_9d70 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0053_9d70 mAllocator;
    basic_string_s0053_9d70() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~basic_string_s0053_9d70() {
        if ((int)(mpCapacity - mpBegin) > 1)
            mAllocator.deallocate(mpBegin, (size_t)(mpCapacity - mpBegin));
    }
    basic_string_s0053_9d70& assign(const char* first, const char* last);    // @ 0x454cb0
};
}
struct cSPVector3_s0053_9d70 { float x, y, z; cSPVector3_s0053_9d70() {} cSPVector3_s0053_9d70(float a, float b, float c) : x(a), y(b), z(c) {} };
inline cSPVector3_s0053_9d70 Vec3(float a, float b, float c) { return cSPVector3_s0053_9d70(a, b, c); }
namespace EA {
namespace IO {
 struct IStream_s0053_9d70 {}; 
}
}
bool ReadInt32(EA::IO::IStream_s0053_9d70*, int32_t*, size_t, int);          // @ 0x93a780
bool ReadUInt8(EA::IO::IStream_s0053_9d70*, uint8_t*, size_t);               // @ 0x93a6c0
bool ReadUInt16(EA::IO::IStream_s0053_9d70*, uint16_t*, size_t, int);        // @ 0x93a700
bool WriteUInt32(EA::IO::IStream_s0053_9d70*, const uint32_t*, size_t, int); // @ 0x93aa70
void WriteUInt8(EA::IO::IStream_s0053_9d70*, const uint8_t*, size_t);        // operator<< // 0x0093a9a0
bool WriteUInt16(EA::IO::IStream_s0053_9d70*, const uint16_t*, size_t, int);
struct cSPSkinPaintParticleDescription_s0053_9d70;
namespace EA {
namespace ArgScript {
struct cIParser_s0053_9d70 {
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void V35();                                          // +0x8c
    virtual void PushMetaCommand(void* cmd, const char* end);    // +0x90
    PV(37) virtual float GetFloat(const char*);
#undef PV
};
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s0053_9d70 {
    const char** MainArguments(size_t* pCount, int min, int max);  // 0x838020
    const char** MainArguments(int count);                         // 0x838320
    const char** OptionArguments(const char* name, int count);     // 0x838330
    bool HasFlag(const char* flag);                                // 0x8380b0
};
}
}
namespace EA {
namespace ArgScript {
struct cState_s0053_9d70 { uint32_t mStateID; };
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s0053_9d70 { virtual void AddRef(); virtual void Release(); virtual void Cast(); };
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s0053_9d70 : cICommand_s0053_9d70 { cIParser_s0053_9d70* mParser; int mRefCount; };
}
}
namespace EA {
namespace ArgScript {
struct cBlockCommandBase : cICommand_s0053_9d70 {
    cIParser_s0053_9d70* mParser; int mRefCount; cState_s0053_9d70* mChildState; char mCommands[0x20];
};
}
}
namespace EA {
namespace ArgScript {
template <class T, class B> struct cCommandStateT_s0053_9d70 : B { T* mState; };
}
}
namespace EA {
namespace ArgScript {
template <class T> struct cBlockCommandT : cCommandStateT_s0053_9d70<T, cBlockCommandBase> {};
}
}
namespace EA {
namespace Swarm {
struct cSPSkinPaintParticleDescription_s0053_9d70;
}
}
namespace EA {
namespace Swarm {
struct cEffectsParser : EA::ArgScript::cCommandBase_s0053_9d70 {
    cSPSkinPaintParticleDescription_s0053_9d70* GetInheritedDescription(const char** a, size_t n, int t); // 0xa6f090
    void AddDescription(EA::ArgScript::cArguments_s0053_9d70& a, const char* n, int t, int f); // 0xa6fc30
};
}
}
void cBlockCommandBaseCtor(EA::ArgScript::cBlockCommandBase*);    // 0x83c800
void FUN_00a6f9c0(void* parser, int type, void* desc);            // 0xa6f9c0
void* SP_EffectsManager();                                        // 0x67ddd0
void* EASTL_allocator_allocate(size_t, const char*, int, unsigned, const char*, int); // 0xf473a0
void EvalResizeA(void* vec, int n);                               // 0x53b520
void EvalResizeB(void* vec, int n);                               // 0x53b8a0
void EvalResizeC(void* vec, int n);                               // 0x4afc80
void EvalCopyA_(void* dst, const void* src);                      // 0x53b210
void EvalCopyB_(void* dst, const void* src);                      // 0x53b5a0
struct EvalList {
    char m0[0x14];                                                // +0x00
    char m1[0x14];                                                // +0x14
    Vector16 m2;                                                  // +0x28
    char pad[4];
    EvalList& operator=(const EvalList& o);                       // 0x53a420
};
struct BrushDesc_s0053_9d70 {
    char pad0[4];
    Vector16 mHashes;             // +0x04
    char pad1[4];
    int mChainId;                 // +0x18
    uint32_t mFlags;              // +0x1c
    cSPVector3_s0053_9d70 mUserColorHSV;     // +0x20
    char mUserColorIndex;         // +0x2c
    uint8_t mAlignment;           // +0x2d
    uint8_t mInitialDirection;    // +0x2e
    uint8_t mAttraction;          // +0x2f
    cSPVector3_s0053_9d70 mAlignTarget;      // +0x30
    cSPVector3_s0053_9d70 mInitialDirTarget; // +0x3c
    cSPVector3_s0053_9d70 mAttractTarget;    // +0x48
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
    BrushDesc_s0053_9d70& operator=(const BrushDesc_s0053_9d70& o);                     // 0x53a2b0
    struct cSPSkinPaintParticleDescription_s0053_9d70* GetRuntimeDesc();     // 0x53a4a0
};
struct cSPSkinPaintParticleDescription_s0053_9d70 : DescriptionBase { BrushDesc_s0053_9d70 mBrush; };
template <class T> struct AutoRefCount_s0053_9d70 {
    T* mpObject;
    AutoRefCount_s0053_9d70& operator=(T* p) { mpObject = p; return *this; } // @ 0x53b160
    operator T*() const { return mpObject; }
};
class cSPSkinPaintParticleEffectBlockCommand_s0053_9d70
    : public EA::ArgScript::cBlockCommandT<EA::Swarm::cEffectsParser>, public EA::ArgScript::cState_s0053_9d70 {
public:
    eastl::basic_string_s0053_9d70 mName;                                    // +0x38
    AutoRefCount_s0053_9d70<cSPSkinPaintParticleDescription_s0053_9d70> mpDesc;         // +0x48
    int mCurrentModifier;                                         // +0x4c
    EvalList* mpEvalList;                                         // +0x50

    cSPSkinPaintParticleEffectBlockCommand_s0053_9d70();                     // 0x539f90
    ~cSPSkinPaintParticleEffectBlockCommand_s0053_9d70();                    // 0x53a220
    void Parse(EA::ArgScript::cArguments_s0053_9d70& args);                  // @ 0x53a030
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
struct cSPSkinPaintParticleinheritCommand {
    char pad[0xc];
    void* mpState;
    void Execute(EA::ArgScript::cArguments_s0053_9d70& args);
};
struct cSPSkinPaintParticleAddDescCommand {
    char pad[0xc];
    EA::Swarm::cEffectsParser* mpParser;
    void AddDesc(EA::ArgScript::cArguments_s0053_9d70& args);
};
    void WriteUInt8(...); // 0x0093a9a0
// ---- items of slice s00539d70 end

// ---- items of slice s0053acc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t);
void operator delete[](void*);  // 0x00f47380
void operator delete[](void*, size_t);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
namespace EA {
namespace IO {
 struct IStream_s0053_acc0 {}; 
}
}
bool ReadInt32(EA::IO::IStream_s0053_acc0*, int32_t*, size_t, int);           // @ 0x93a780
bool ReadUInt8(EA::IO::IStream_s0053_acc0*, uint8_t*, size_t);                // @ 0x93a6c0
bool WriteUInt32(EA::IO::IStream_s0053_acc0*, const uint32_t*, size_t, int);  // @ 0x93aa70
void WriteUInt8(EA::IO::IStream_s0053_acc0*, const uint8_t*, size_t); // 0x0093a9a0
void ReadEvalList(EA::IO::IStream_s0053_acc0*, char*);                        // @ 0x53a6d0 (slice 31)
void WriteEvalList(EA::IO::IStream_s0053_acc0*, char*);                       // @ 0x53a930 (slice 31)
void ReadDescBase(EA::IO::IStream_s0053_acc0*, char*);                        // @ 0x53bc90
void WriteDescBase(EA::IO::IStream_s0053_acc0*, char*);                       // @ 0x53bd00
struct IStreamV {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual bool ReadBytes(void* p, unsigned n);                   // +0x30
    virtual void v13();
    virtual bool WriteBytes(const void* p, unsigned n);            // +0x38
};
struct BlobVec {
    char* mpBegin; char* mpEnd; char* mpCapacity; char* mpAlloc;
    // thiscall members: the originals take the vector in ECX (ret 4).
    BlobVec* Vector16Assign(const BlobVec* o);
    void Vector16Resize(unsigned n);
    BlobVec* Vector20Assign(const BlobVec* o);
    void Vector20Resize(unsigned n);
};
template <int Stride>
__forceinline void BlobResize(BlobVec* v, unsigned n)
{
    unsigned have = (unsigned)((v->mpEnd - v->mpBegin) / Stride);
    if (have < n) {
        char* nb = (char*)operator new[]((size_t)n * Stride + 4);
        *(uint32_t*)nb = 0;
        nb += 4;
        if (have)
            memcpy(nb, v->mpBegin, (size_t)have * Stride);
        for (unsigned i = have; i < n; ++i)
            for (int b = 0; b < Stride; ++b)
                nb[i * Stride + b] = 0;
        if (v->mpBegin) {
            char* ob = v->mpBegin - 4;
            if (*(uint32_t*)ob != 0)
                operator delete[](ob);
        }
        v->mpBegin = nb;
        v->mpEnd = nb + (size_t)n * Stride;
        v->mpCapacity = v->mpEnd;
    } else {
        v->mpEnd = v->mpBegin + (size_t)n * Stride;
    }
}
template <int Stride>
__forceinline BlobVec* BlobAssign(BlobVec* v, const BlobVec* o)
{
    if (o == v)
        return v;
    unsigned n = (unsigned)((o->mpEnd - o->mpBegin) / Stride);
    if (n > (unsigned)((v->mpEnd - v->mpBegin) / Stride)) {
        BlobResize<Stride>(v, n);
        memcpy(v->mpBegin, o->mpBegin, (size_t)n * Stride);
    } else {
        memcpy(v->mpBegin, o->mpBegin, (size_t)n * Stride);
        v->mpEnd = v->mpBegin + (size_t)n * Stride;
    }
    return v;
}
struct AutoRefSlot {
    void* mp;
    AutoRefSlot* AutoRefCountAssign(void* p);
};
struct PaintCompatA { PaintCompatA* Ctor1b0(); };
struct PaintCompatB { PaintCompatB* Ctor1f0(); };
// ---- items of slice s0053acc0 end

// ---- items of slice s0053b930 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s0053_b930 { float x, y, z; cSPVector3_s0053_b930() {} cSPVector3_s0053_b930(float a, float b, float c) : x(a), y(b), z(c) {} };
namespace EA {
namespace ArgScript {
struct cIParser_s0053_b930 {
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void V35();                                          // +0x8c
    PV(36) virtual float GetFloat(const char*);                  // +0x98
    PV(39) PV(40) PV(41) virtual cSPVector3_s0053_b930 GetVector(const char*); // +0xa8
#undef PV
};
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s0053_b930 { virtual void AddRef(); virtual void Release(); virtual void Cast(); };
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s0053_b930 : cICommand_s0053_b930 { cIParser_s0053_b930* mParser; int mRefCount; };
}
}
void RegisterPaintVar(EA::ArgScript::cCommandBase_s0053_b930* a, const char* name, void* cmd); // vtable +0x18
void* PaintCompatCtor(void*);                                         // 0x53b1f0
void* PaintVarModifierCtor(void*);                                    // 0x83?
// ---- items of slice s0053b930 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
cSPVector3_s0053_8e90* normalized(cSPVector3_s0053_8e90* out, const cSPVector3_s0053_8e90& in);   // defined at 0x00539440, called earlier in the TU

// @ 0x00538e90
void cSPSkinPaintParticledelayCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 2);
    if (count == 2) {
        p->mDelayMin = mParser->GetFloat(argv[0]);
        p->mDelayMax = mParser->GetFloat(argv[1]);
    } else {
        float value = mParser->GetFloat(argv[0]);
        float vary = 0.0f;
        const char** opt = args.OptionArguments("vary", 1);
        if (opt != 0)
            vary = mParser->GetFloat(opt[0]);
        p->mDelayMin = (1.0f - vary) * value;
        p->mDelayMax = (1.0f + vary) * value;
    }
}

// @ 0x00538fe0
void cSPSkinPaintParticlelifeCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 2);
    if (count == 2) {
        p->mLifeMin = mParser->GetFloat(argv[0]);
        p->mLifeMax = mParser->GetFloat(argv[1]);
    } else {
        float value = mParser->GetFloat(argv[0]);
        float vary = 0.0f;
        const char** opt = args.OptionArguments("vary", 1);
        if (opt != 0)
            vary = mParser->GetFloat(opt[0]);
        p->mLifeMin = (1.0f - vary) * value;
        p->mLifeMax = (1.0f + vary) * value;
    }
}

// @ 0x00539130
void cSPSkinPaintParticlecurveCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 0, 500);
    (void)argv;
    if (args.HasFlag("random"))
        p->mFlags |= 4;
}

// @ 0x005391c0
void cSPSkinPaintParticlealignCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    if (_stricmp(argv[0], "inherit") == 0) {
        p->mAlignment = 0;
    } else if (_stricmp(argv[0], "move") == 0) {
        p->mAlignment = 1;
    } else if (_stricmp(argv[0], "dir") == 0) {
        p->mAlignment = 1;
    } else if (_stricmp(argv[0], "attract") == 0) {
        p->mAlignment = 2;
    } else if (_stricmp(argv[0], "aroundbone") == 0) {
        p->mAlignment = 5;
    } else if (_stricmp(argv[0], "alongbone") == 0) {
        p->mAlignTarget = cSPVector3_s0053_8e90(0.0f, 1.0f, 0.0f);
        p->mAlignment = 4;
    } else if (_stricmp(argv[0], "aroundspine") == 0) {
        p->mAlignment = 7;
    } else if (_stricmp(argv[0], "alongspine") == 0) {
        p->mAlignTarget = cSPVector3_s0053_8e90(0.0f, 1.0f, 0.0f);
        p->mAlignment = 6;
    } else {
        cSPVector3_s0053_8e90 v = mParser->GetVector(argv[0]);
        cSPVector3_s0053_8e90 n;
        normalized(&n, v);
        p->mAlignTarget = n;
        if (args.HasFlag("bone"))
            p->mAlignment = 4;
        else
            p->mAlignment = 3;
    }
    if (args.HasFlag("reverse"))
        p->mFlags |= 0x40;
}

// @ 0x00539440
cSPVector3_s0053_8e90* normalized(cSPVector3_s0053_8e90* out, const cSPVector3_s0053_8e90& in)
{
    float len = in[0] * in[0] + in[1] * in[1] + in[2] * in[2];
    float d = Sqrt(len);
    Vector3Divide(out, &in, &d);
    return out;
}

// @ 0x005394e0
void cSPSkinPaintParticleinitDirCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    if (_stricmp(argv[0], "inherit") == 0) {
        p->mInitialDirection = 0;
    } else if (_stricmp(argv[0], "attract") == 0) {
        p->mInitialDirection = 2;
    } else if (_stricmp(argv[0], "aroundbone") == 0) {
        p->mInitialDirection = 5;
    } else if (_stricmp(argv[0], "alongbone") == 0) {
        p->mInitialDirTarget = cSPVector3_s0053_8e90(0.0f, 1.0f, 0.0f);
        p->mInitialDirection = 4;
    } else if (_stricmp(argv[0], "aroundspine") == 0) {
        p->mInitialDirection = 7;
    } else if (_stricmp(argv[0], "alongspine") == 0) {
        p->mInitialDirTarget = cSPVector3_s0053_8e90(0.0f, 1.0f, 0.0f);
        p->mInitialDirection = 6;
    } else {
        cSPVector3_s0053_8e90 v = mParser->GetVector(argv[0]);
        cSPVector3_s0053_8e90 n;
        normalized(&n, v);
        p->mInitialDirTarget = n;
        if (args.HasFlag("bone"))
            p->mInitialDirection = 4;
        else
            p->mInitialDirection = 3;
    }
    if (args.HasFlag("reverse"))
        p->mFlags |= 0x20;
}

// @ 0x00539720
void cSPSkinPaintParticleattractCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 2);
    if (_stricmp(argv[0], "inherit") == 0) {
        p->mAttraction = 0;
    } else if (_stricmp(argv[0], "aroundbone") == 0) {
        p->mAttraction = 5;
    } else if (_stricmp(argv[0], "alongbone") == 0) {
        p->mAttractTarget = cSPVector3_s0053_8e90(0.0f, 1.0f, 0.0f);
        p->mAttraction = 4;
    } else if (_stricmp(argv[0], "aroundspine") == 0) {
        p->mAttraction = 7;
    } else if (_stricmp(argv[0], "alongspine") == 0) {
        p->mAttractTarget = cSPVector3_s0053_8e90(0.0f, 1.0f, 0.0f);
        p->mAttraction = 6;
    } else {
        cSPVector3_s0053_8e90 v = mParser->GetVector(argv[0]);
        cSPVector3_s0053_8e90 n;
        normalized(&n, v);
        p->mAttractTarget = n;
        if (args.HasFlag("bone"))
            p->mAttraction = 4;
        else
            p->mAttraction = 3;
    }
    if (count == 1)
        p->mAttractStrength = 1.0f;
    else
        p->mAttractStrength = EA::Swarm::ParseRangedFloat(mParser, argv[1], 0.0f, 1.0f);
    if (args.HasFlag("reverse"))
        p->mFlags |= 0x10;
}

// @ 0x00539980
void cSPSkinPaintParticlerestrictCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 2);
    p->mFlags |= 8;
    if (_stricmp(argv[0], "inherit") == 0) {
        p->mAttraction = 0;
    } else if (_stricmp(argv[0], "aroundbone") == 0) {
        p->mAttraction = 5;
    } else if (_stricmp(argv[0], "alongbone") == 0) {
        p->mAttractTarget = cSPVector3_s0053_8e90(0.0f, 1.0f, 0.0f);
        p->mAttraction = 4;
    } else if (_stricmp(argv[0], "aroundspine") == 0) {
        p->mAttraction = 7;
    } else if (_stricmp(argv[0], "alongspine") == 0) {
        p->mAttractTarget = cSPVector3_s0053_8e90(0.0f, 1.0f, 0.0f);
        p->mAttraction = 6;
    } else {
        cSPVector3_s0053_8e90 v = mParser->GetVector(argv[0]);
        cSPVector3_s0053_8e90 n;
        normalized(&n, v);
        p->mAttractTarget = n;
        if (args.HasFlag("bone"))
            p->mAttraction = 4;
        else
            p->mAttraction = 3;
    }
    if (count == 1)
        p->mAttractStrength = 1.0f;
    else
        p->mAttractStrength = EA::Swarm::ParseRangedFloat(mParser, argv[1], 0.0f, 1.0f);
    if (args.HasFlag("reverse"))
        p->mFlags |= 0x10;
}

// @ 0x00539bf0
void cSPSkinPaintParticlediffuseColorCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    p->mBlend0 = EA::Swarm::ParseEnum(argv[0], kAlphaNames);
}

// @ 0x00539c70
void cSPSkinPaintParticlespecularColorCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    p->mBlend1 = EA::Swarm::ParseEnum(argv[0], kAlphaNames);
}

// @ 0x00539cf0
void cSPSkinPaintParticlebumpColorCommand::Execute(cArguments_s0053_8e90& args)
{
    BRUSH();
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 1);
    p->mBlend2 = EA::Swarm::ParseEnum(argv[0], kAlphaNames);
}

// @ 0x00539d70
void cSPSkinPaintParticleinheritCommand::Execute(EA::ArgScript::cArguments_s0053_9d70& args)
{
    cSPSkinPaintParticleEffectBlockCommand_s0053_9d70* state =
        (cSPSkinPaintParticleEffectBlockCommand_s0053_9d70*)mpState;
    cSPSkinPaintParticleDescription_s0053_9d70* A;
    cSPSkinPaintParticleDescription_s0053_9d70* pDesc;
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
    void* block = p ? (void*)new (p) cSPSkinPaintParticleEffectBlockCommand_s0053_9d70() : 0;
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
cSPSkinPaintParticleEffectBlockCommand_s0053_9d70::cSPSkinPaintParticleEffectBlockCommand_s0053_9d70()
: mCurrentModifier(0), mpEvalList(0) {
    mStateID = 0x2c96c27;
    mName.mpBegin = gEmptyString;
    mName.mpEnd = mName.mpBegin;
    mName.mpCapacity = mName.mpBegin + 1;
    mpDesc = 0;
}





// @ 0x0053a030
void cSPSkinPaintParticleEffectBlockCommand_s0053_9d70::Parse(EA::ArgScript::cArguments_s0053_9d70& args)
{
    size_t count = 0;
    const char** argv = args.MainArguments(&count, 1, 3);
    const char* s = argv[0];
    mName.assign(s, s + strlen(s));

    cSPSkinPaintParticleDescription_s0053_9d70* d =
        (cSPSkinPaintParticleDescription_s0053_9d70*)EASTL_allocator_allocate(0xb8, "Skinner", 0, 0, 0, 0);
    if (d)
        new (d) cSPSkinPaintParticleDescription_s0053_9d70();
    mpDesc = d;
    d->mBrush.Init();
    mCurrentModifier = 0xff;
    mpEvalList = &d->mBrush.mEvalList;

    if ((int)count > 1) {
        cSPSkinPaintParticleDescription_s0053_9d70* inh =
            (cSPSkinPaintParticleDescription_s0053_9d70*)mState->GetInheritedDescription(argv, count, 0x26);
        if (inh) {
            d->mBrush = inh->mBrush;
            d->mBrush.mRuntimeComponentId = inh->mBrush.mRuntimeComponentId;
        }
    }
    mParser->V35();
}





// @ 0x0053a1a0
void cSPSkinPaintParticleEffectBlockCommand_s0053_9d70::SetChild(int b)
{
    if (b == 0)
        FUN_00a6f9c0(mState, 0x26, mpDesc.mpObject);
    mpDesc = (cSPSkinPaintParticleDescription_s0053_9d70*)0;
}





// @ 0x0053a220
cSPSkinPaintParticleEffectBlockCommand_s0053_9d70::~cSPSkinPaintParticleEffectBlockCommand_s0053_9d70()
{
    if (mpDesc.mpObject) {
        void** vt = *(void***)mpDesc.mpObject;
        ((void(__thiscall*)(char*))vt[2])((char*)mpDesc.mpObject + 8);
    }
}





// @ 0x0053a2b0
BrushDesc_s0053_9d70& BrushDesc_s0053_9d70::operator=(const BrushDesc_s0053_9d70& o)
{
    mHashes = o.mHashes;
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





// @ 0x0053a420
__declspec(noinline) EvalList& EvalList::operator=(const EvalList& o)
{
    EvalCopyA_(this, &o);
    EvalCopyB_((char*)this + 0x14, (const char*)&o + 0x14);
    m2 = o.m2;
    return *this;
}





// @ 0x0053a460
void cSPSkinPaintParticleAddDescCommand::AddDesc(EA::ArgScript::cArguments_s0053_9d70& args)
{
    const char** argv = args.MainArguments(1);
    EA::Swarm::cEffectsParser* parser = mpParser;
    parser->AddDescription(args, argv[0], 0x26, 0);
}





// @ 0x0053a4a0
cSPSkinPaintParticleDescription_s0053_9d70* BrushDesc_s0053_9d70::GetRuntimeDesc()
{
    BrushDesc_s0053_9d70* b = this;
    void** mgr = (void**)SP_EffectsManager();
    if (!mgr || b->mChainId < 0 || b->mRuntimeComponentId < 0)
        return 0;
    char* res = (char*)(*(void*(__thiscall**)(int, int, int))((*(void***)mgr)[0x70 / 4]))(
        0x26, b->mChainId, b->mRuntimeComponentId);
    *(int*)(res + 0xb4) = b->mRuntimeComponentId;
    return (cSPSkinPaintParticleDescription_s0053_9d70*)(res ? res + 8 : 0);
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
EA::IO::IStream_s0053_9d70* ReadEvalList(EA::IO::IStream_s0053_9d70* stream, EvalList* e)
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
EA::IO::IStream_s0053_9d70* WriteEvalList(EA::IO::IStream_s0053_9d70* stream, EvalList* e)
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




// @ 0x0053acc0
void ReadParticleDescription(EA::IO::IStream_s0053_acc0* s, char* d)
{
    ReadDescBase(s, d + 0xc);
    ReadInt32(s, (int32_t*)(d + 0x20), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x24), 1, 0);
    ((IStreamV*)s)->ReadBytes(d + 0x28, 0xc);
    ReadUInt8(s, (uint8_t*)(d + 0x34), 1);
    ReadUInt8(s, (uint8_t*)(d + 0x35), 1);
    ReadUInt8(s, (uint8_t*)(d + 0x36), 1);
    ReadUInt8(s, (uint8_t*)(d + 0x37), 1);
    ((IStreamV*)s)->ReadBytes(d + 0x38, 0xc);
    ((IStreamV*)s)->ReadBytes(d + 0x44, 0xc);
    ((IStreamV*)s)->ReadBytes(d + 0x50, 0xc);
    ReadInt32(s, (int32_t*)(d + 0x5c), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x60), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x64), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x68), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x6c), 1, 0);
    ReadInt32(s, (int32_t*)(d + 0x70), 1, 0);
    ReadEvalList(s, d + 0x74);
    ReadUInt8(s, (uint8_t*)(d + 0xb0), 1);
    ReadUInt8(s, (uint8_t*)(d + 0xb1), 1);
    ReadUInt8(s, (uint8_t*)(d + 0xb2), 1);
}




// @ 0x0053aea0
void WriteParticleDescription(EA::IO::IStream_s0053_acc0* s, char* d)
{
    WriteDescBase(s, d + 0xc);
    uint32_t v;
    v = *(uint32_t*)(d + 0x20); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x24); WriteUInt32(s, &v, 1, 0);
    ((IStreamV*)s)->WriteBytes(d + 0x28, 0xc);
    WriteUInt8(s, (uint8_t*)(d + 0x34), 1);
    WriteUInt8(s, (uint8_t*)(d + 0x35), 1);
    WriteUInt8(s, (uint8_t*)(d + 0x36), 1);
    WriteUInt8(s, (uint8_t*)(d + 0x37), 1);
    ((IStreamV*)s)->WriteBytes(d + 0x38, 0xc);
    ((IStreamV*)s)->WriteBytes(d + 0x44, 0xc);
    ((IStreamV*)s)->WriteBytes(d + 0x50, 0xc);
    v = *(uint32_t*)(d + 0x5c); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x60); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x64); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x68); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x6c); WriteUInt32(s, &v, 1, 0);
    v = *(uint32_t*)(d + 0x70); WriteUInt32(s, &v, 1, 0);
    WriteEvalList(s, d + 0x74);
    WriteUInt8(s, (uint8_t*)(d + 0xb0), 1);
    WriteUInt8(s, (uint8_t*)(d + 0xb1), 1);
    WriteUInt8(s, (uint8_t*)(d + 0xb2), 1);
}




// @ 0x0053b160
AutoRefSlot* AutoRefSlot::AutoRefCountAssign(void* p)
{
    if (p != mp) {
        void* old = mp;
        if (p)
            ((void(__thiscall*)(char*))(*(void***)((char*)p + 8))[0])((char*)p + 8);
        mp = p;
        if (old)
            ((void(__thiscall*)(char*))(*(void***)((char*)old + 8))[1])((char*)old + 8);
    }
    return this;
}




// @ 0x0053b1c0
PaintCompatA* PaintCompatA::Ctor1b0()
{
    *(void**)this = (void*)0x13f4b30;
    *(void**)this = (void*)0x13f4b30;
    return this;
}




// @ 0x0053b1f0
PaintCompatB* PaintCompatB::Ctor1f0()
{
    *(void**)this = (void*)0x13f4b30;
    return this;
}




// @ 0x0053b210
BlobVec* BlobVec::Vector16Assign(const BlobVec* o)
{
    return BlobAssign<0x10>(this, o);
}




// @ 0x0053b520
void BlobVec::Vector16Resize(unsigned n)
{
    BlobResize<0x10>(this, n);
}




// @ 0x0053b5a0
BlobVec* BlobVec::Vector20Assign(const BlobVec* o)
{
    return BlobAssign<0x14>(this, o);
}



// @ 0x0053b930
void RegisterPaintEvalCommands(EA::ArgScript::cCommandBase_s0053_b930* cmds)
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
