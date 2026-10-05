// SWARM game-model ArgScript command cluster around 0x7d19c0.
//
// The command objects derive from EA::ArgScript::cCommandT<State>; the state
// pointer sits at +0xc and points at an (anonymous-namespace) cGameModelState
// whose cGameModelDescription member lies at state+4 (retail layout, which has
// grown by 4 bytes per embedded eastl vector compared with the 2008 PDB).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-  (x87 fsin/fcos via the
// double sin/cos intrinsics; no cookie).
#include "types.h"
#include <math.h>
#pragma intrinsic(sin, cos)

// ------------------------------------------------------------ allocators
void* operator new[](size_t size);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

namespace eastl {
extern wchar_t gEmptyString16[2];
template <typename T> struct EmptyStr;
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
struct allocator { void deallocate(void* p) { operator delete[](p); } };
template <typename T, typename Allocator = allocator>
class basic_string {
public:
    T* mpBegin; T* mpEnd; T* mpCapacity; Allocator mAllocator;
    basic_string() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    void DeallocateSelf() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin); }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
typedef basic_string<wchar_t> string16;
}

namespace EA {
eastl::string16 ConvertToString16(const char* p, int length = -1);          // 0x93c5a0
struct ResourceKey { uint32_t a, b, c; };
void __cdecl SPKeyFromName(void* out, const void* name, int a, int b);      // 0x68d840

namespace ArgScript {
class cArguments {
public:
    const char** MainArguments(int n);                          // 0x838320
    const char** MainArguments(int* count, int min, int max);   // 0x838020
    const char** OptionArguments(const char* name, int n);      // 0x838330
    bool HasFlag(const char* name);                             // 0x8380b0
};
struct cIParser {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36();
    virtual char  v37(const char* s);   // +0x94
    virtual float v38(const char* s);   // +0x98
    virtual void  v39();                // +0x9c
    virtual char  v40(const char* s);   // +0xa0
};
uint32_t ParseEnum(const char* value, const char** table);                  // 0x840bb0
struct cCommandBase {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual void c4();
    virtual void AddCommand(void* key, void* cmd);   // +0x18
    cIParser* mParser;   // +0x4
    int mRefCount;       // +0x8
};
struct cBlockCommandBase : cCommandBase {
    void* mChildState;         // +0xc
    char  mCommands[0x20];     // +0x10 (hash_map)
};
}}

namespace EA { namespace IO {
class IStream;
bool ReadInt32(IStream* s, int32_t* p, unsigned n, int endian);   // 0x93a780
}}

// -------------------------------------------------------------- game model
namespace SP {
struct Vec20 { void* p0; void* p1; void* p2; void* p3; void* p4; };

struct cGameModelDescription {
    void*    vtbl;            // +0x00
    int      mRefCount;       // +0x04
    int      mStateID;        // +0x08
    uint32_t mFlags;          // +0x0c
    float    mSize;           // +0x10
    float    mColourX;        // +0x14
    float    mColourY;        // +0x18
    float    mColourZ;        // +0x1c
    float    mAlpha;          // +0x20
    uint32_t mInstanceID;     // +0x24
    uint32_t mGroupID;        // +0x28
    uint32_t mWorldID;        // +0x2c
    Vec20    mAnimationCurves;  // +0x30
    Vec20    mModelSplitters;   // +0x44
    Vec20    mSplitControllers; // +0x58
    Vec20    mGroups;           // +0x6c
    uint32_t mFlagsToSet;     // +0x80
    uint8_t  mPickLevel;      // +0x84
    uint8_t  mOverrideSet;    // +0x85
    uint8_t  pad86[2];        // +0x86
    uint32_t field88;         // +0x88
};

struct cGameModelState {
    void* vtbl;                   // +0x00
    cGameModelDescription mDesc;  // +0x04
};

struct Matrix33 { float m[9]; };
struct cTransform {
    uint16_t mFlags;              // +0x00
    uint16_t mModificationCount;  // +0x02
    float    mTranslation[3];     // +0x04
    float    mScale;              // +0x10
    Matrix33 mRotation;           // +0x14
    void RotateZ(float angle);
};

struct cSplitController { uint32_t mKernel; uint8_t mType; uint8_t mFuzzy; uint16_t pad; };
}  // namespace SP

// ---------------------------------------------------------------- helpers
extern "C" int __cdecl isdigit(int);

struct UVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void* a1;
    void* a2;
    void resize(unsigned n);                             // 0x4afc80
    void DoInsertValue(uint32_t* pos, const uint32_t& v); // 0x4558a0
};

struct SVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* a1;
    void* a2;
    void DoInsertValue(void* pos, const void* v);        // 0x7e1340
};

int  FindModelKernel(const char* name, int type);        // 0xa6ebd0
void EffectCommandInit(void* self, void* a, void* b);    // 0x83c780
void SetUserData(void* self, void* p);                   // 0xfd9450
void EchoError(const char* fmt, ...);                    // 0x52df30 (cError ctor)

extern const char* kVisibleCommands[];                   // 0x153d728
extern const char* kDeformHandleCommands[];              // 0x153d678
extern const char* kModelSplitterTypeCommands[];         // 0x153d7c8
extern const char* kModelSplitterFuzzyModeCommands[];    // 0x153d7e8

// command name globals used by the effect block command
extern void* g_cmdName;      // 0x153d648
extern void* g_cmdSize;      // 0x153d64c
extern void* g_cmdColor;     // 0x153d650
extern void* g_cmdAlpha;     // 0x153d654
extern void* g_cmdAnimate;   // 0x153d658
extern void* g_cmdWorld;     // 0x153d65c
extern void* g_cmdPersist;   // 0x153d660
extern void* g_cmdGroups;    // 0x153d664
extern void* g_cmdOptions;   // 0x153d668
extern void* g_cmdPickLevel; // 0x153d66c
extern void* g_cmdSplitter;  // 0x153d670
extern void* g_cmdSplit;     // 0x153d674
extern void* g_cmdGameModel; // 0x153d644

// =============================================================== commands
struct cGameModelAlphaCommand : EA::ArgScript::cCommandBase {
    SP::cGameModelState* mState;   // +0xc
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007d19c0
void cGameModelAlphaCommand::Execute(EA::ArgScript::cArguments& args) {
    mState->mDesc.mAlpha = mParser->v38(args.MainArguments(1)[0]);
}

struct cGameModelVisibleCommand : EA::ArgScript::cCommandBase {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007d19f0
void cGameModelVisibleCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(1);
    char b = mParser->v37(av[0]);
    uint32_t* p = &mState->mDesc.mFlags;
    if (b) *p |= 8; else *p &= ~8u;
}

struct cGameModelFlagsCommand : EA::ArgScript::cCommandBase {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007d1a30
void cGameModelFlagsCommand::Execute(EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 1, 0x7fffffff);
    for (int i = 0; i < count; ++i) {
        uint32_t e = EA::ArgScript::ParseEnum(av[i], kVisibleCommands);
        if (e < 0x20)
            mState->mDesc.mFlagsToSet |= 1u << (e & 0x1f);
    }
}

// @ 0x007d1ac0
void SP::cTransform::RotateZ(float angle) {
    float s = (float)sin((double)angle);
    float c = (float)cos((double)angle);
    float m0 = mRotation.m[0], m1 = mRotation.m[1], m2 = mRotation.m[2];
    float m3 = mRotation.m[3], m4 = mRotation.m[4], m5 = mRotation.m[5];
    mRotation.m[0] = m0 * c + m3 * s;
    mRotation.m[1] = m1 * c + m4 * s;
    mRotation.m[2] = m2 * c + m5 * s;
    mFlags |= 2;
    mModificationCount++;
    mRotation.m[3] = -m0 * s + m3 * c;
    mRotation.m[4] = -m1 * s + m4 * c;
    mRotation.m[5] = -m2 * s + m5 * c;
}

struct cGameModelNameCommand : EA::ArgScript::cCommandBase {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007d1cc0
void cGameModelNameCommand::Execute(EA::ArgScript::cArguments& args) {
    eastl::string16 s = EA::ConvertToString16(args.MainArguments(1)[0], -1);
    EA::ResourceKey key;
    EA::SPKeyFromName(&key, s.c_str(), 0, 0);
    mState->mDesc.mInstanceID = key.a;
    mState->mDesc.mGroupID = key.c;
    const char** msg = args.OptionArguments("message", 1);
    if (msg) {
        eastl::string16 s2 = EA::ConvertToString16(msg[0], -1);
        EA::ResourceKey key2;
        EA::SPKeyFromName(&key2, s2.c_str(), 0, 0);
        mState->mDesc.field88 = key2.a;
        mState->mDesc.mFlags |= 4;
    }
    const char** ov = args.OptionArguments("overrideSet", 1);
    if (ov)
        mState->mDesc.mOverrideSet = mParser->v40(ov[0]);
    else
        mState->mDesc.mOverrideSet = 0;
    if (args.HasFlag("noAttachments"))
        mState->mDesc.mFlags |= 0x20;
}

struct cGameModelWorldCommand : EA::ArgScript::cCommandBase {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
// @ 0x007d1e40
void cGameModelWorldCommand::Execute(EA::ArgScript::cArguments& args) {
    eastl::string16 s = EA::ConvertToString16(args.MainArguments(1)[0], -1);
    EA::ResourceKey key;
    EA::SPKeyFromName(&key, s.c_str(), 0, 0);
    mState->mDesc.mWorldID = key.a;
}

// ------------------------------------------------------------- sub-commands
#define SUBCOMMAND(Name)                                                        \
    struct Name : EA::ArgScript::cCommandBase { SP::cGameModelState* mState; };
SUBCOMMAND(cGameModelSizeCommand)
SUBCOMMAND(cGameModelColorCommand)
SUBCOMMAND(cGameModelAnimateCommand)
SUBCOMMAND(cGameModelPersistCommand)
SUBCOMMAND(cGameModelOptionsCommand)
SUBCOMMAND(cGameModelPickLevelCommand)
SUBCOMMAND(cGroupGameModelCommand)
#undef SUBCOMMAND

struct cGameModelDeformCommand : EA::ArgScript::cCommandBase {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
struct cGameModelSplitterCommand : EA::ArgScript::cCommandBase {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};

struct cGameModelEffectCommand : EA::ArgScript::cBlockCommandBase {
    uint32_t             field30;          // +0x30
    SP::cGameModelState  mGameModelState;  // +0x34
    eastl::string16      mDescName;        // +0xc8
    void OnRegister(void* parser, void* childState);
    ~cGameModelEffectCommand();
};

void* operator new(size_t size, const char* pName, int a, int b, int c, int d);  // 0xf473a0

// @ 0x007d1f20
void cGameModelEffectCommand::OnRegister(void* parser, void* childState) {
    field30 = childState ? (uint32_t)((char*)childState - 0xc) : 0;
    EffectCommandInit(this, childState, childState);
    SetUserData(this, &mGameModelState);
    AddCommand(g_cmdName,     new ("ArgScript/GameModelName",     0,0,0,0) cGameModelNameCommand());
    AddCommand(g_cmdSize,     new ("ArgScript/GameModelSize",     0,0,0,0) cGameModelSizeCommand());
    AddCommand(g_cmdColor,    new ("ArgScript/GameModelColor",    0,0,0,0) cGameModelColorCommand());
    AddCommand(g_cmdAlpha,    new ("ArgScript/GameModelAlpha",    0,0,0,0) cGameModelAlphaCommand());
    AddCommand(g_cmdAnimate,  new ("ArgScript/GameModelAnimate",  0,0,0,0) cGameModelAnimateCommand());
    AddCommand(g_cmdWorld,    new ("ArgScript/GameModelWorld",    0,0,0,0) cGameModelWorldCommand());
    AddCommand(g_cmdPersist,  new ("ArgScript/GameModelPersist",  0,0,0,0) cGameModelPersistCommand());
    AddCommand(g_cmdGroups,   new ("ArgScript/GameModelGroups",   0,0,0,0) cGameModelFlagsCommand());
    AddCommand(g_cmdOptions,  new ("ArgScript/GameModelOptions",  0,0,0,0) cGameModelOptionsCommand());
    AddCommand(g_cmdPickLevel,new ("ArgScript/GameModelPickLevel",0,0,0,0) cGameModelPickLevelCommand());
    AddCommand(g_cmdSplitter, new ("ArgScript/GameModelSplitter", 0,0,0,0) cGameModelDeformCommand());
    AddCommand(g_cmdSplit,    new ("ArgScript/GameModelSplit",    0,0,0,0) cGameModelSplitterCommand());
}
 
// @ 0x007d2330
void cGameModelDeformCommand::Execute(EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 1, 0x7fffffff);
    for (int i = 0; i < count; ++i) {
        uint32_t v;
        if (isdigit((unsigned char)av[i][0]))
            v = mParser->v40(av[i]);
        else
            v = EA::ArgScript::ParseEnum(av[i], kDeformHandleCommands);
        UVec* g = (UVec*)&mState->mDesc.mGroups;
        uint32_t* end = g->mpEnd;
        if (end < g->mpCapacity) {
            g->mpEnd = end + 1;
            if (end) *end = v;
        } else {
            g->DoInsertValue(end, v);
        }
    }
}

// @ 0x007d23d0
void cGameModelSplitterCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(3);
    int kernel = FindModelKernel(av[0], 0x10);
    if (kernel < 0) {
        EchoError("Unknown split model kernel: %s", av[0]);
        return;
    }
    SP::cSplitController sc;
    sc.mKernel = kernel;
    sc.mType  = (uint8_t)EA::ArgScript::ParseEnum(av[1], kModelSplitterTypeCommands);
    sc.mFuzzy = (uint8_t)EA::ArgScript::ParseEnum(av[2], kModelSplitterFuzzyModeCommands);
    SVec* v = (SVec*)&mState->mDesc.mModelSplitters;
    void* end = v->mpEnd;
    if (end < v->mpCapacity) {
        v->mpEnd = (char*)end + 8;
        if (end) { *(uint32_t*)end = sc.mKernel; *((uint32_t*)end + 1) = *(uint32_t*)&sc; }
    } else {
        v->DoInsertValue(end, &sc);
    }
}

// @ 0x007d2490
cGameModelEffectCommand::~cGameModelEffectCommand() {
}

// vector helpers used by the description copy paths
void VecInit(void* dst, unsigned n, void* alloc);            // 0x7d1c60 / 0x7d1c00
void* VecAssignRange(void* out, void* a, void* b, void* c, void* d);  // 0x7d0dd0

// @ 0x007d2580
void* CopySplitControllerVector(void* self, void* src) {
    if (src == self) return self;
    VecInit(self, (unsigned)(((char*)((void**)src)[1] - (char*)((void**)src)[0]) / 0x68), (char*)src + 0xc);
    void* tmp = 0;
    VecAssignRange(&tmp, ((void**)src)[0], ((void**)src)[1], *(void**)self, src);
    ((void**)self)[1] = tmp;
    return self;
}

void AddGameModelCommands(void* server, void* childState, void* parser);  // fwd
void RegisterEffectCommand(void* self, void* key, void* cmd);            // fwd

// @ 0x007d2670
void SWARM_GameModelAddCommands(void* unused, void* server, int* parserVtbl) {
    cGameModelEffectCommand* effect = 0;
    cGroupGameModelCommand*   group  = 0;
    if (parserVtbl) {
        ((void(__thiscall*)(void*, void*, void*))((*(void***)server)[0x14 / 4]))(server, g_cmdGameModel, effect);
    }
    ((void(__thiscall*)(void*, void*, void*))((*(void***)server)[0x18 / 4]))(server, g_cmdGameModel, group);
}

// @ 0x007d2740
void* CopyAnimationCurveVector(void* self, void* src) {
    if (src == self) return self;
    VecInit(self, (unsigned)(((char*)((void**)src)[1] - (char*)((void**)src)[0]) / 0x2c), (char*)src + 0xc);
    void* tmp = 0;
    VecAssignRange(&tmp, ((void**)src)[0], ((void**)src)[1], *(void**)self, src);
    ((void**)self)[1] = tmp;
    return self;
}

// @ 0x007d27d0
void* ReadIntVector(void* stream, void* vec) {
    int count;
    EA::IO::ReadInt32((EA::IO::IStream*)stream, &count, 1, 0);
    UVec* v = (UVec*)vec;
    v->resize((unsigned)count);
    for (unsigned i = 0; i < (unsigned)count; ++i)
        EA::IO::ReadInt32((EA::IO::IStream*)stream, (int32_t*)&v->mpBegin[i], 1, 0);
    return stream;
}

// @ 0x007d2830
void* CopyGameModelState(void* self, void* src) {
    (void)self; (void)src;
    return self;
}
