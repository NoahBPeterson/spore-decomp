// src/game/SPBake/SPSkinPaintDistributeDescription.cpp -- migrated from slice(s) s005300d0, s0052f170, s0052e1f0 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinPaintDistributeDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cError.h"
#include "EA/ArgScript/cICommand.h"
#include "EA/ArgScript/cIParser.h"
#include "nSPSkinner/cPaintMaterial.h"
#include "nSPSkinner/cPaintSystem.h"
#include "nSPSkinner/cRTTBuffer.h"
#include "EA/ArgScript/cState.h"
#include <stdarg.h>

// unnamed retail callees and globals (address in the comment)
extern const char* kDistributeParticleKeyword;      // "particle"
extern const char* kDistributeParticlesKeyword;     // "particleSelect"
extern const char* kDistributeSpacingKeyword;       // "spacing"
extern const char* kDistributeLimitKeyword;         // "limit"
extern const char* kDistributeRegionKeyword;        // "region"

// ---- items of slice s0052e1f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                            // 0x00f473a0
void operator delete(void* p, const char* name, int flags, unsigned debugFlags,
                     const char* file, int line);
void operator delete(void* p);                                             // 0x00f47380
struct sp_vector_allocator {
    uint32_t mFlags[2];
    sp_vector_allocator() {}
};
namespace eastl {
template <typename T1, typename T2> struct pair_s0052_e1f0 {
    T1 first;
    T2 second;
    pair_s0052_e1f0(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
extern char gEmptyString;           // 0x01667bac
}
namespace eastl {
struct allocator_s0052_e1f0 {
    uint32_t mFlags;
    allocator_s0052_e1f0() {}
};
}
namespace eastl {
template <typename T> struct basic_string_s0052_e1f0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s0052_e1f0 mAllocator;
    basic_string_s0052_e1f0() : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        ScratchSlots<1>();
        AllocateSelf();
    }
    ~basic_string_s0052_e1f0()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void AllocateSelf()
    {
        mpBegin = &gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    void DoFree(T* p, uint32_t n)
    {
        if (p) {
            void* q = p;
            ::operator delete(q);
        }
    }
};
}
namespace eastl {
template <typename T> struct VectorBase_s0052_e1f0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    VectorBase_s0052_e1f0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase_s0052_e1f0();                  // 0x0045daf0 (declined inline)
};
}
namespace eastl {
template <typename T> struct vector_s0052_e1f0 : VectorBase_s0052_e1f0<T> {
    vector_s0052_e1f0() {}
    ~vector_s0052_e1f0()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        ScratchSlots<3>();
    }
    T* erase(T* first, T* last);    // 0x00530c80
    void clear()
    {
        ScratchSlots<6>();      // frame of the declined erase() expansion
        erase(mpBegin, mpEnd);
    }
    void push_back(const T& value); // 0x005402c0
};
}
namespace EA {
template <typename T> struct RefCountTemplate_s0052_e1f0 {
    RefCountTemplate_s0052_e1f0() : mRefCount(0) {}
    ~RefCountTemplate_s0052_e1f0() {}
    virtual int AddRef();
    virtual int Release();
    T mRefCount;
};
}
namespace EA {
template struct RefCountTemplate_s0052_e1f0<int>;
}
namespace EA {
namespace Swarm {
struct cDescription_s0052_e1f0 : RefCountTemplate_s0052_e1f0<int> {
    cDescription_s0052_e1f0() {}
};
}
}
namespace EA {
namespace Swarm {
struct cEffectsParser;
}
}
struct cSPSkinPaintDistributeDescription : EA::Swarm::cDescription_s0052_e1f0 {   // 0x54
    eastl::basic_string_s0052_e1f0<char> mEffect;      // +0x08
    int mParticleDescId;                    // +0x18
    float mSpacing;                         // +0x1c
    uint32_t mLimit;                        // +0x20
    uint32_t mRegionFlags;                  // +0x24
    float mBackCutoff;                      // +0x28
    float mBellyCutoff;                     // +0x2c
    float mSpineRange[2];                   // +0x30
    bool mInvertRegions;                    // +0x38
    bool mCenterOnly;                       // +0x39
    bool mExtraCover;                       // +0x3a
    bool mNonRandom;                        // +0x3b
    eastl::vector_s0052_e1f0<eastl::pair_s0052_e1f0<int, float> > mParticleSelect;   // +0x3c
    bool mParticleSelectIndependent;        // +0x50
    cSPSkinPaintDistributeDescription();
    virtual void Dummy();
};
namespace EA {
namespace ArgScript {
struct cIParser_s0052_e1f0 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void PushMetaCommand(void* command, const char* endKeyword);   // +0x90
};
}
}
namespace EA {
namespace ArgScript {
struct cState_s0052_e1f0 {
    uint32_t mStateID;
};
}
}
namespace EA {
namespace ArgScript {
struct Line {
    struct Text {
        const char* mpBegin;
        const char* c_str() const { return mpBegin; }
    } mText;
    const char* GetText() const { return mText.c_str(); }
};
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s0052_e1f0 {
    const char** MainArguments(int count);      // 0x00838320
    bool HasFlag(const char* flag);             // 0x008380b0
};
}
}
namespace EA {
namespace ArgScript {
struct cICommand_s0052_e1f0 {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s0052_e1f0 : cICommand_s0052_e1f0 {
    cIParser_s0052_e1f0* mParser;
    int mRefCount;
    cCommandBase_s0052_e1f0();                             // 0x0083c800
    void OnRegister(cIParser_s0052_e1f0* parser, cState_s0052_e1f0* state);   // 0x0083c7f0
};
}
}
namespace EA {
namespace ArgScript {
struct cIMetaCommand : cICommand_s0052_e1f0 {};
}
}
namespace EA {
namespace ArgScript {
struct cMetaCommandBase : cIMetaCommand {
    cIParser_s0052_e1f0* mParser;
    int mRefCount;
    cMetaCommandBase();                         // 0x0083c840
};
}
}
namespace EA {
namespace ArgScript {
struct cIBlockCommand_s0052_e1f0 : cICommand_s0052_e1f0 {};
}
}
namespace EA {
namespace ArgScript {
struct cBlockCommandBase : cIBlockCommand_s0052_e1f0 {
    cIParser_s0052_e1f0* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cState_s0052_e1f0* mChildState;                        // +0x0c
    uint32_t mCommands[8];                      // +0x10 hash_map
    void OnRegister(cIParser_s0052_e1f0* parser, cState_s0052_e1f0* state);   // 0x0083c780
    void SetChildState(cState_s0052_e1f0* state);          // 0x00fd9450
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void AddCommand(const char* name, cICommand_s0052_e1f0* command);      // +0x18
};
}
}
namespace EA {
namespace ArgScript {
template <typename T, typename Base> struct cCommandStateT_s0052_e1f0 : Base {
    T* mState;
    cCommandStateT_s0052_e1f0() {}
    void OnRegister(cIParser_s0052_e1f0* parser, cState_s0052_e1f0* state);
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> struct cCommandT : cCommandStateT_s0052_e1f0<T, cCommandBase_s0052_e1f0> {
    cCommandT() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> struct cMetaCommandT : cCommandStateT_s0052_e1f0<T, cMetaCommandBase> {
    cMetaCommandT() {}
};
}
}
namespace EA {
namespace ArgScript {
template <typename T> struct cBlockCommandT : cCommandStateT_s0052_e1f0<T, cBlockCommandBase> {
    cBlockCommandT() {}
};
}
}
namespace EA {
namespace Swarm {
struct cEffectsParser : RefCountTemplate_s0052_e1f0<int> {
    int FindComponent(const char* name, int type);  // 0x00a6eb60
};
}
}
namespace {
struct cSPSkinPaintDistributeEffectCommand
    : EA::ArgScript::cBlockCommandT<EA::Swarm::cEffectsParser>, EA::ArgScript::cState_s0052_e1f0 {
    cSPSkinPaintDistributeDescription mDesc;        // +0x38
    eastl::basic_string_s0052_e1f0<char> mDescName;
    void OnRegister(EA::ArgScript::cIParser_s0052_e1f0* parser, EA::ArgScript::cState_s0052_e1f0* state);
};

struct cSPSkinPaintDistributeParticleCommand : EA::ArgScript::cCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeParticleCommand() {}
    virtual void Execute(EA::ArgScript::cArguments_s0052_e1f0& args);
};
struct cSPSkinPaintDistributeParticlesCommand : EA::ArgScript::cMetaCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeParticlesCommand() {}
    virtual void Execute(EA::ArgScript::cArguments_s0052_e1f0& args);
    virtual bool Parse(const EA::ArgScript::Line& line);
};
struct cSPSkinPaintDistributeSpacingCommand : EA::ArgScript::cCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeSpacingCommand() {}
    virtual void Execute(EA::ArgScript::cArguments_s0052_e1f0& args);
};
struct cSPSkinPaintDistributeLimitCommand : EA::ArgScript::cCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeLimitCommand() {}
    virtual void Execute(EA::ArgScript::cArguments_s0052_e1f0& args);
};
struct cSPSkinPaintDistributeRegionCommand : EA::ArgScript::cCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeRegionCommand() {}
    virtual void Execute(EA::ArgScript::cArguments_s0052_e1f0& args);
};
}  // namespace
extern const char* kDistributeParticleKeyword;      // "particle"
extern const char* kDistributeParticlesKeyword;     // "particleSelect"
extern const char* kDistributeSpacingKeyword;       // "spacing"
extern const char* kDistributeLimitKeyword;         // "limit"
extern const char* kDistributeRegionKeyword;        // "region"
// ---- items of slice s0052e1f0 end

// ---- items of slice s0052f170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_TI_cError;                                     // ThrowInfo
namespace EA {
namespace ArgScript {
struct cArguments_s0052_f170 {
    static void* MainArguments(cArguments_s0052_f170* self, ...);
    static void* OptionArguments(cArguments_s0052_f170* self, const char* name, int count);
    static unsigned char HasFlag(cArguments_s0052_f170* self, const char* name);  // 0x008380b0 (EA::ArgScript::cArguments::HasFlag)
};
}
}
namespace EA {
namespace ArgScript {
struct cBlockCommandBase_s0052_f170 { virtual ~cBlockCommandBase_s0052_f170(); };
}
}
using EA::ArgScript::cArguments_s0052_f170;
using EA::ArgScript::cBlockCommandBase_s0052_f170;
void  ErrorString(void* out, const char* fmt, ...);           // 0x0052df30
void  CxxThrowException(void*, void*);                        // _CxxThrowException
void  EastlStringAssign(void* str, const char* first, const char* last); // 0x00454cb0
void  FUN_0047d390(void* first, void* last);
void* FUN_0052ea60();
void  FUN_0052eb40();
struct cSwarmEffect {
    int*  CopyParams(int src);    // 0x0052fb20
    void* Ctor(int src);          // 0x0052fc10
};
struct cDistributeCmd {
    void SpacingExecute(cArguments_s0052_f170* args);   // 0x0052f330
    void LimitExecute(cArguments_s0052_f170* args);     // 0x0052f3a0
    void AddEffect(char param_2);            // 0x0052f9f0
};
void  FUN_00530870(void*);
void  FUN_00530770(void*);
void  FUN_00a6f9c0(void*, int, void*);
int   GetInheritedDescription(void* parser, void* args, int n, int id);
void  AddAnonDescription(void* parser, void* args, int id, void* obj, int flag);
void  AddDescription(void* parser, void* args, void* name, int id, int flag);
void  ReleaseObj(void* p);
int   ParseRangedFloatI(void* self, void* arg, int lo, int hi);   // returns int/float
float ParseRangedFloatF(void* self, void* arg, int lo, int hi);
void  CosI(float x);
float GetCos();
typedef int   (__thiscall *VFnI)(void*, void*);
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s0052f170 end

// ---- items of slice s005300d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);   // 0x00f473a0
extern "C" void EASTL_allocator_deallocate(void* p);                     // 0x00f47380
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags); // 0x0042dee0
struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual int Read(void* data, uint32_t size);                  // +0x30
    virtual void v13();
    virtual bool Write(const void* data, uint32_t size);          // +0x38
};
bool WriteUint32(IStream* s, const uint32_t* p, uint32_t count, int endian); // 0x0093aa70
bool WriteBool8(IStream* s, const bool* p, uint32_t count);           // 0x0093a9a0
struct StrAllocator {
    void* allocate(uint32_t n) { return EASTL_allocator_allocate(n, "Editor", 0, 0, __FILE__, 0xd1); }
};
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    StrAllocator mAllocator;
    ~string();                                                    // @ 0x00530670
    void push_back(char c);                                       // @ 0x005306c0
    void reserve(uint32_t n);                                     // @ 0x0047c600
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(char* p, uint32_t n) { if (p) Deallocate(p, n); }
    void Deallocate(char* p, uint32_t) { char* q = p; EASTL_allocator_deallocate(q); }
};
struct PairIF {
    int first;
    float second;
    PairIF() : first(0), second(0.0f) {}
};
struct VectorIF {
    PairIF* mpBegin;
    PairIF* mpEnd;
    PairIF* mpCapacity;
    uint32_t mAlloc[2];
    VectorIF() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    VectorIF(const VectorIF& x);
    VectorIF& operator=(const VectorIF& x);
    PairIF* erase(PairIF* first, PairIF* last);                   // @ 0x00530c80
    void resize(uint32_t n);                                      // @ 0x00530b70
    PairIF* DoAllocateCopy(uint32_t n, const PairIF* first, const PairIF* last); // @ 0x00530d20
    void DoInsertValues(PairIF* position, uint32_t n, const PairIF& value);      // @ 0x00530db0
};
PairIF* uninitialized_copy(const PairIF* first, const PairIF* last, PairIF* dest, bool tag); // @ 0x005311a0
inline bool WriteValue32(IStream* s, uint32_t value) { return WriteUint32(s, &value, 1, 0); }
inline bool Write(IStream* s, uint32_t value) { return WriteValue32(s, value); }
inline bool Write(IStream* s, int value) { return WriteValue32(s, (uint32_t)value); }
inline bool WriteFloat32(IStream* s, float value) { return WriteUint32(s, (uint32_t*)&value, 1, 0); }
inline bool Write(IStream* s, float value) { return WriteFloat32(s, value); }
inline bool WriteBool(IStream* s, uint8_t value) { return WriteBool8(s, (const bool*)&value, 1); }
inline bool Write(IStream* s, bool value) { return WriteBool(s, value ? 1 : 0); }
string::~string()
{
    DeallocateSelf();
}
void string::push_back(char c)
{
    if (mpEnd + 1 == mpCapacity) {
        uint32_t nRequired = (uint32_t)(mpEnd - mpBegin) + 1;
        uint32_t nCapacity = (uint32_t)(mpCapacity - mpBegin) - 1;
        uint32_t nNewCapacity = (nCapacity > 8) ? nCapacity * 2 : 8;
        reserve(nRequired < nNewCapacity ? nNewCapacity : nRequired);
    }
    *mpEnd = c;
    mpEnd = mpEnd + 1;
    *mpEnd = 0;
}
PairIF* VectorIF::erase(PairIF* first, PairIF* last)
{
    PairIF* pEnd = mpEnd;
    PairIF* p = first;
    for (PairIF* q = last; q != pEnd; ++q, ++p)
        *p = *q;
    for (PairIF* q = p; q < mpEnd; ++q) {
    }
    mpEnd = mpEnd - (last - first);
    return first;
}
void VectorIF::resize(uint32_t n)
{
    if ((uint32_t)(mpEnd - mpBegin) < n) {
        PairIF value;
        DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}
PairIF* VectorIF::DoAllocateCopy(uint32_t n, const PairIF* first, const PairIF* last)
{
    PairIF* p;
    if (n == 0)
        p = 0;
    else
        p = (PairIF*)EASTL_Allocate(mAlloc, n * 8, 4, 0);
    PairIF* result = p;
    uninitialized_copy(first, last, p, false);
    return result;
}
VectorIF::VectorIF(const VectorIF& x)
{
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    PairIF* p;
    if (n == 0)
        p = 0;
    else
        p = (PairIF*)EASTL_Allocate(mAlloc, n * 8, 4, 0);
    mpBegin = p;
    mpEnd = p;
    mpCapacity = p + n;
    mpEnd = uninitialized_copy(x.mpBegin, x.mpEnd, mpBegin, false);
}
VectorIF& VectorIF::operator=(const VectorIF& x)
{
    if (&x != this) {
        uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if ((uint32_t)(mpCapacity - mpBegin) < n) {
            PairIF* p = DoAllocateCopy(n, x.mpBegin, x.mpEnd);
            for (PairIF* q = mpBegin; q < mpEnd; ++q) {
            }
            if (mpBegin != 0 && ((uint32_t*)mpBegin)[-1] != 0)
                EASTL_allocator_deallocate(mpBegin);
            mpBegin = p;
            mpCapacity = mpBegin + n;
        } else if ((uint32_t)(mpEnd - mpBegin) < n) {
            PairIF* pEnd = mpEnd;
            PairIF* pSrc = x.mpBegin + (mpEnd - mpBegin);
            PairIF* pSrcEnd = x.mpBegin;
            PairIF* pDst = mpBegin;
            for (PairIF* q = pSrcEnd; q != pSrc; ++q, ++pDst)
                *pDst = *q;
            uninitialized_copy(pSrc, x.mpEnd, mpEnd, false);
        } else {
            PairIF* pDst = mpBegin;
            for (PairIF* q = x.mpBegin; q != x.mpEnd; ++q, ++pDst)
                *pDst = *q;
            for (PairIF* q = pDst; q < mpEnd; ++q) {
            }
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
struct CMetaCommandBase {
    char pad[0x0c];
    void OnRegister(void* parser, void* state);   // 0x0083c7f0
};
struct CmdStateMeta : CMetaCommandBase {
    void* mState;                                  // +0x0c
    void OnRegister(void* parser, void* state);
};
// ---- items of slice s005300d0 end

// @ 0x0052ea60
inline cSPSkinPaintDistributeDescription::cSPSkinPaintDistributeDescription()
{
}

// @ 0x0052ec40
void cSPSkinPaintDistributeEffectCommand::OnRegister(EA::ArgScript::cIParser_s0052_e1f0* parser, EA::ArgScript::cState_s0052_e1f0* state)
{
    mState = state ? (EA::Swarm::cEffectsParser*)((char*)state - 0xc) : 0;
    cBlockCommandBase::OnRegister(parser, state);
    SetChildState(this);
    AddCommand(kDistributeParticleKeyword,
               new ("ArgScript/SPSkinPaintDistributeParticle", 0, 0, 0, 0) cSPSkinPaintDistributeParticleCommand());
    AddCommand(kDistributeParticlesKeyword,
               new ("ArgScript/SPSkinPaintDistributeParticles", 0, 0, 0, 0) cSPSkinPaintDistributeParticlesCommand());
    AddCommand(kDistributeSpacingKeyword,
               new ("ArgScript/SPSkinPaintDistributeSpacing", 0, 0, 0, 0) cSPSkinPaintDistributeSpacingCommand());
    AddCommand(kDistributeLimitKeyword,
               new ("ArgScript/SPSkinPaintDistributeLimit", 0, 0, 0, 0) cSPSkinPaintDistributeLimitCommand());
    AddCommand(kDistributeRegionKeyword,
               new ("ArgScript/SPSkinPaintDistributeRegion", 0, 0, 0, 0) cSPSkinPaintDistributeRegionCommand());
}

// @ 0x0052f170
void DistributeParticles_OnEndParse(int param_1)
{
    void* cmd = *(void**)(param_1 + 0xc);
    int count = (int)((*(int*)((char*)cmd + 0x78) - *(int*)((char*)cmd + 0x74)) >> 3);
    if (count < 1) {
        char buf[16];
        ErrorString(buf, "no particles specified\n");
        CxxThrowException(buf, &g_TI_cError);
    }
    if (*(char*)((char*)cmd + 0x88) == 0) {
        float total = 0.0f;
        int nNeg = 0;
        for (int i = 0; i < count; i++) {
            float p = *(float*)(*(int*)((char*)cmd + 0x74) + 4 + i * 8);
            if (p < 0.0f) nNeg++;
            else total += p;
        }
        if (1.0001f < total) {
            char buf[16];
            ErrorString(buf, "total selection probability is greater than 1.0\n");
            CxxThrowException(buf, &g_TI_cError);
        }
        for (int i = 0; i < count; i++) {
            float* p = (float*)(*(int*)((char*)cmd + 0x74) + 4 + i * 8);
            if (*p <= 0.0f && *p != 0.0f)
                *p = (1.0f - total) / (float)nNeg;
        }
        float acc = 0.0f;
        for (int i = 0; i < count; i++) {
            acc += *(float*)(*(int*)((char*)cmd + 0x74) + 4 + i * 8);
            *(float*)(*(int*)((char*)cmd + 0x74) + 4 + i * 8) = acc;
        }
    }
}

// @ 0x0052f330
void cDistributeCmd::SpacingExecute(cArguments_s0052_f170* args)
{
    int param_1 = (int)this;
    void** p = (void**)cArguments_s0052_f170::MainArguments(args, 1);
    VFnI fn = *(VFnI*)(*(int*)(param_1 + 4) + 0x98);
    float v = (float)fn((void*)*(int*)(param_1 + 4), *p);
    *(float*)(*(int*)(param_1 + 0xc) + 0x54) = v;
    *(unsigned char*)(*(int*)(param_1 + 0xc) + 0x72) = cArguments_s0052_f170::HasFlag(args, "cover");
    *(unsigned char*)(*(int*)(param_1 + 0xc) + 0x73) = cArguments_s0052_f170::HasFlag(args, "ordered");
}

// @ 0x0052f3a0
void cDistributeCmd::LimitExecute(cArguments_s0052_f170* args)
{
    int param_1 = (int)this;
    void** p = (void**)cArguments_s0052_f170::MainArguments(args, 1);
    VFnI fn = *(VFnI*)(*(int*)(param_1 + 4) + 0x9c);
    int v = fn((void*)*(int*)(param_1 + 4), *p);
    *(int*)(*(int*)(param_1 + 0xc) + 0x58) = v;
}

// @ 0x0052f3f0
void DistributeRegion_Execute(int param_1, cArguments_s0052_f170* args)
{
    cArguments_s0052_f170::MainArguments(args, 0);
    int cmd = *(int*)(param_1 + 0xc);
    *(uint32_t*)(cmd + 0x5c) = 0;
    if (cArguments_s0052_f170::HasFlag(args, "torso")) *(uint32_t*)(cmd + 0x5c) |= 1;
    if (cArguments_s0052_f170::HasFlag(args, "limbs")) *(uint32_t*)(cmd + 0x5c) |= 2;
    if (cArguments_s0052_f170::HasFlag(args, "parts")) *(uint32_t*)(cmd + 0x5c) |= 4;
    if (cArguments_s0052_f170::HasFlag(args, "joints")) *(uint32_t*)(cmd + 0x5c) |= 0x20;
    void** o = (void**)cArguments_s0052_f170::OptionArguments(args, (const char*)0x013f251c, 1);
    if (o) {
        *(uint32_t*)(cmd + 0x5c) |= 8;
        ParseRangedFloatI(*(void**)(param_1 + 4), *o, 0, 0x40000000);
        CosI(0);
        *(float*)(cmd + 0x60) = GetCos();
    }
    o = (void**)cArguments_s0052_f170::OptionArguments(args, "belly", 1);
    if (o) {
        *(uint32_t*)(cmd + 0x5c) |= 0x10;
        ParseRangedFloatI(*(void**)(param_1 + 4), *o, 0, 0x40000000);
        CosI(0);
        *(float*)(cmd + 0x64) = -GetCos();
    }
    o = (void**)cArguments_s0052_f170::OptionArguments(args, "bodyRange", 2);
    if (o == 0) {
        *(uint32_t*)(cmd + 0x68) = 0;
        *(uint32_t*)(cmd + 0x6c) = 0x3f800000;
    } else {
        *(float*)(cmd + 0x68) = ParseRangedFloatF(*(void**)(param_1 + 4), *o, 0, 0x3f800000);
        int cmd2 = *(int*)(param_1 + 0xc);
        *(float*)(cmd2 + 0x6c) = ParseRangedFloatF(*(void**)(param_1 + 4), o[1], 0, 0x3f800000);
    }
    *(unsigned char*)(cmd + 0x71) = cArguments_s0052_f170::HasFlag(args, "centerOnly");
    *(unsigned char*)(cmd + 0x70) = cArguments_s0052_f170::HasFlag(args, "inverse");
}

// @ 0x0052f6b0
void SPSkinPaintDistributeAddCommands(int* a, int* b)
{
    void* obj = operator new(0x9c, "ArgScript/SPSkinPaintDistributeEffect", 0, 0, 0, 0);
    void* effect = obj ? (void*)FUN_0052ea60() : 0;
    (*(void(__thiscall**)(int*, void*, void*))(*(int*)b + 0x14))(b, (void*)0x0150cb48, effect);
    void* cmd = operator new(0x10, "ArgScript/SPSkinPaintDistributeInline", 0, 0, 0, 0);
    if (cmd) {
        // cCommandBase ctor + vtable fixes
        *(void**)cmd = (void*)0x013f1ffc;
        *(void**)cmd = (void*)0x013f1ffc;
        *(void**)cmd = (void*)0x013f2544;
    }
    (*(void(__thiscall**)(int*, void*, void*))(*(int*)a + 0x18))(a, (void*)0x0150cb48, cmd);
}

// @ 0x0052f7c0
void* DistributeEffectCommandCtor(void* self)
{
    *(void**)self = (void*)0x013f25ac;
    FUN_0052ea60();
    int* p = (int*)((char*)self + 0x8c);
    p[0] = 0; p[1] = 0; p[2] = 0;
    p[0] = (int)&g_TI_cError;
    p[1] = p[0];
    p[2] = p[0] + 1;
    return self;
}

// @ 0x0052f890
void DistributeBlock_Parse(int param_1, cArguments_s0052_f170* args)
{
    int n = 0;
    void** p = (void**)cArguments_s0052_f170::MainArguments(args, &n, 1, 3);
    char* s = (char*)*p;
    char* e = s;
    while (*e) e++;
    EastlStringAssign((void*)*p, s, e);
    int* str = (int*)(param_1 + 0x40);
    if (*str != *(int*)(param_1 + 0x44)) {
        *(char*)*str = 0;
        *(int*)(param_1 + 0x44) = *str;
    }
    *(uint32_t*)(param_1 + 0x50) = 0xffffffff;
    *(uint32_t*)(param_1 + 0x54) = 0x3e4ccccd;
    *(uint32_t*)(param_1 + 0x58) = 0xffffffff;
    *(uint32_t*)(param_1 + 0x5c) = 0xffffffff;
    *(unsigned char*)(param_1 + 0x70) = 0;
    *(unsigned char*)(param_1 + 0x71) = 0;
    *(unsigned char*)(param_1 + 0x72) = 0;
    *(unsigned char*)(param_1 + 0x73) = 0;
    FUN_0047d390(*(void**)(param_1 + 0x74), *(void**)(param_1 + 0x78));
    *(unsigned char*)(param_1 + 0x88) = 0;
    if (1 < n) {
        int d = GetInheritedDescription(*(void**)(param_1 + 0x30), p, n, 0x23);
        if (d) ((cSwarmEffect*)(param_1 + 0x38))->CopyParams(d);
    }
    (*(void(__thiscall**)(int, int))(*(int*)(*(int*)(param_1 + 4)) + 0x8c))(*(int*)(param_1 + 4), param_1);
}

// @ 0x0052f9f0
void cDistributeCmd::AddEffect(char param_2)
{
    int param_1 = (int)this;
    if (param_2 == 0) {
        int obj = (int)operator new(0x54, "Swarm/SkinPaint", 0, 0, 0, 0);
        void* made = obj ? ((cSwarmEffect*)obj)->Ctor(param_1 + 0x38) : 0;
        FUN_00a6f9c0(*(void**)(param_1 + 0x8c), 0x23, made);
    }
    int* str = (int*)(param_1 + 0x8c);
    if (*str != *(int*)(param_1 + 0x90)) {
        *(char*)*str = 0;
        *(int*)(param_1 + 0x90) = *str;
    }
}

// @ 0x0052fb00
void __fastcall BlockCmdBaseDerivedDtor(cBlockCommandBase_s0052_f170* p)
{
    p->~cBlockCommandBase_s0052_f170();
}

// @ 0x0052fb20
int* cSwarmEffect::CopyParams(int param_2)
{
    int param_1 = (int)this;
    if ((void*)(param_2 + 8) != (void*)(param_1 + 8))
        EastlStringAssign(*(void**)(param_2 + 8), *(const char**)(param_2 + 8), *(const char**)(param_2 + 0xc));
    *(uint32_t*)(param_1 + 0x18) = *(uint32_t*)(param_2 + 0x18);
    *(uint32_t*)(param_1 + 0x1c) = *(uint32_t*)(param_2 + 0x1c);
    *(uint32_t*)(param_1 + 0x20) = *(uint32_t*)(param_2 + 0x20);
    *(uint32_t*)(param_1 + 0x24) = *(uint32_t*)(param_2 + 0x24);
    *(uint32_t*)(param_1 + 0x28) = *(uint32_t*)(param_2 + 0x28);
    *(uint32_t*)(param_1 + 0x2c) = *(uint32_t*)(param_2 + 0x2c);
    *(uint32_t*)(param_1 + 0x30) = *(uint32_t*)(param_2 + 0x30);
    *(uint32_t*)(param_1 + 0x34) = *(uint32_t*)(param_2 + 0x34);
    *(unsigned char*)(param_1 + 0x38) = *(unsigned char*)(param_2 + 0x38);
    *(unsigned char*)(param_1 + 0x39) = *(unsigned char*)(param_2 + 0x39);
    *(unsigned char*)(param_1 + 0x3a) = *(unsigned char*)(param_2 + 0x3a);
    *(unsigned char*)(param_1 + 0x3b) = *(unsigned char*)(param_2 + 0x3b);
    FUN_00530870((void*)(param_2 + 0x3c));
    *(unsigned char*)(param_1 + 0x50) = *(unsigned char*)(param_2 + 0x50);
    return (int*)param_1;
}

// @ 0x0052fc10
void* cSwarmEffect::Ctor(int src)
{
    void* self = this;
    *(void**)self = (void*)0x013f22dc;
    *(uint32_t*)((char*)self + 4) = 0;
    *(uint32_t*)((char*)self + 8) = 0;
    *(uint32_t*)((char*)self + 0xc) = 0;
    *(uint32_t*)((char*)self + 0x10) = 0;
    FUN_0047d390(*(void**)(src + 8), *(void**)(src + 0xc));
    *(uint32_t*)((char*)self + 0x18) = *(uint32_t*)(src + 0x18);
    *(uint32_t*)((char*)self + 0x1c) = *(uint32_t*)(src + 0x1c);
    *(uint32_t*)((char*)self + 0x20) = *(uint32_t*)(src + 0x20);
    *(uint32_t*)((char*)self + 0x24) = *(uint32_t*)(src + 0x24);
    *(uint32_t*)((char*)self + 0x28) = *(uint32_t*)(src + 0x28);
    *(uint32_t*)((char*)self + 0x2c) = *(uint32_t*)(src + 0x2c);
    *(uint32_t*)((char*)self + 0x30) = *(uint32_t*)(src + 0x30);
    *(uint32_t*)((char*)self + 0x34) = *(uint32_t*)(src + 0x34);
    *(unsigned char*)((char*)self + 0x38) = *(unsigned char*)(src + 0x38);
    *(unsigned char*)((char*)self + 0x39) = *(unsigned char*)(src + 0x39);
    *(unsigned char*)((char*)self + 0x3a) = *(unsigned char*)(src + 0x3a);
    *(unsigned char*)((char*)self + 0x3b) = *(unsigned char*)(src + 0x3b);
    FUN_00530770((void*)(src + 0x3c));
    *(unsigned char*)((char*)self + 0x50) = *(unsigned char*)(src + 0x50);
    return self;
}

// @ 0x0052fd80
void __fastcall Distribute_CommandDtor(cBlockCommandBase_s0052_f170* p)
{
    char* s = *(char**)((char*)p + 0x34);
    if (1 < (int)(*(int*)((char*)p + 0x38) - (int)s)) {
        if (s) {
            void* q = s;
            operator delete(q);
        }
    }
    FUN_0052eb40();
    p->~cBlockCommandBase_s0052_f170();
}

// @ 0x0052fe20
void DistributeInline_Execute(int param_1, cArguments_s0052_f170* args)
{
    int n = 0;
    void** p = (void**)cArguments_s0052_f170::MainArguments(args, &n, 0, 1);
    if (n < 1) {
        int obj = (int)operator new(0x54, "Skinner/Swarm", 0, 0, 0, 0);
        void* made = obj ? FUN_0052ea60() : 0;
        if (made) *(int*)((char*)made + 4) = *(int*)((char*)made + 4) + 1;
        void** pp = (void**)cArguments_s0052_f170::OptionArguments(args, "effect", 1);
        if (pp == 0) {
            char buf[16];
            ErrorString(buf, "must specify block name or use inline -effect ... syntax");
            CxxThrowException(buf, &g_TI_cError);
        }
        char* s = (char*)*pp;
        char* e = s;
        while (*e) e++;
        EastlStringAssign((void*)*pp, s, e);
        void** sp = (void**)cArguments_s0052_f170::OptionArguments(args, "spacing", 1);
        if (sp) {
            VFnI fn = *(VFnI*)(*(int*)(param_1 + 4) + 0x98);
            *(float*)((char*)made + 0x34) = (float)fn((void*)*(int*)(param_1 + 4), *sp);
        }
        void** lp = (void**)cArguments_s0052_f170::OptionArguments(args, "limit", 1);
        if (lp) {
            VFnI fn = *(VFnI*)(*(int*)(param_1 + 4) + 0x9c);
            *(int*)((char*)made + 0x38) = fn((void*)*(int*)(param_1 + 4), *lp);
        }
        *(unsigned char*)((char*)made + 0x72) = cArguments_s0052_f170::HasFlag(args, "cover");
        *(unsigned char*)((char*)made + 0x73) = cArguments_s0052_f170::HasFlag(args, "ordered");
        AddAnonDescription(*(void**)(param_1 + 0xc), args, 0x23, made, 0);
        if (made) ReleaseObj(made);
    } else {
        AddDescription(*(void**)(param_1 + 0xc), args, *p, 0x23, 0);
    }
}

// @ 0x005305c0
IStream* WriteString(IStream* stream, string* str)
{
    uint32_t n = (uint32_t)(str->mpEnd - str->mpBegin);
    char* z = str->mpBegin;
    stream->Write(z, n);
    char p = 0;
    stream->Write(&p, 1);
    return stream;
}

// @ 0x00530c40
void CmdStateMeta::OnRegister(void* parser, void* state)
{
    mState = state ? (void*)((char*)state - 0x34) : 0;
    CMetaCommandBase::OnRegister(parser, state);
}
