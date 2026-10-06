// Slice s0083b810 (batch w2g7).
// EA::ArgScript::cArgumentSpec::Parse / Parse (throwing) / ConstructSpec, the
// vector<cOptionsSpec> helpers, and cCommandBase-family refcount Release + ctors.
// Compiled /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef int            int32;

extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p);
void* __cdecl memcpy(void* dst, const void* src, unsigned n);
long  __cdecl atol(const char*);
int   __cdecl isalpha(int);
int   __cdecl _stricmp(const char* a, const char* b);
}
inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";

extern char gEmptyString[];

namespace eastl {
struct allocator { unsigned char pad[4]; };
struct sp_vector_allocator : allocator {};

struct string8 {
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator mAllocator;
    string8() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);   // 0x00454cb0
    void assign(const char* p);                         // 0x006a4380
    void append(const char* first, const char* last);   // 0x00455d60
    string8(const string8& x);                          // 0x0057cb10
    ~string8();
};

template <typename T>
struct vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;
    vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
}  // namespace eastl

struct cArgInfo {
    int mType; eastl::string8 mName; void* mLocation; bool mIsDependent; int mFlagToSet;
    cArgInfo(const cArgInfo& x);   // 0x00838ab0
};
struct cEnumParseInfo { char* mToken; int mValue; };
struct cEnumSpec {
    eastl::string8 mName; cEnumParseInfo* mEnumInfo; int mPad14;
    cEnumSpec(const cEnumSpec& x); // 0x00e84850
    ~cEnumSpec();
};
typedef eastl::vec<cArgInfo>  VecArgInfo;
typedef eastl::vec<cEnumSpec> VecEnumSpec;

struct cOptionsSpec {
    eastl::string8 mName;            // +0x00
    eastl::string8 mDescription;     // +0x10
    VecArgInfo     mArguments;       // +0x20
    int            mPad30;           // +0x30
    int            mFlagToSet;       // +0x34
    cOptionsSpec(const cOptionsSpec& x);              // 0x00839e00
    cOptionsSpec& operator=(const cOptionsSpec& x);   // 0x0083a8b0
    ~cOptionsSpec();
};

struct cOptionArgInfo {
    char* mName; int mFirstArgumentIndex; int mNumArguments; bool mProcessed;
};
struct cArguments {
    eastl::vec<char>              mArgStorage;
    eastl::vec<char*>             mArguments;
    eastl::vec<cOptionArgInfo>    mOptionArguments;
    int                           mMainArgumentsStart;
    int                           mNumMainArguments;
    cArguments();                       // 0x00837ff0
    ~cArguments();
    void SplitIntoArguments(const char* s);   // 0x008383c0
    int  NumArguments();                      // 0x00837f30
    char* operator[](int i);                  // 0x00837f20
};

typedef eastl::vec<cOptionsSpec> VecOptionsSpec;

struct ArgParser { void** vtbl; };

struct cArgumentSpec {
    eastl::string8 mCommandName;        // +0x00
    eastl::string8 mBriefDescription;   // +0x10
    eastl::string8 mFullDescription;    // +0x20
    VecArgInfo     mDefaultArguments;   // +0x30
    char pad40[0x4];                    // +0x40
    VecOptionsSpec mOptions;            // +0x44
    char pad54[0x4];                    // +0x54
    VecEnumSpec    mEnumSpecs;          // +0x58
    char pad64[0x4];                    // +0x64
    bool           mRespectHelp;        // +0x6c
    int            mFlags;              // +0x70
    cArguments     mVectorArgs;         // +0x74
    char padac[0xb8 - 0xac];
    eastl::string8 mErrorString;        // +0xb8

    cArgumentSpec(bool respectHelp);                                       // 0x0083a9f0
    int  Parse(int argc, const char** argv, ArgParser* p);                 // 0x0083b810
    int  ParseVectorArgument(cArgInfo* ai, const char* str);
    int  ParseVectorArgument(cArgInfo* ai, const char* str, ArgParser* p);
    int  ParseArgument(cArgInfo* ai, const char* str);
    int  ParseArgumentEx(cArgInfo* ai, const char* str, ArgParser* p);
    int  ParseOptionArgs(cOptionsSpec* opt, int** ppArgs, const char** ppEnd, ArgParser* p);
    int  ParseOption(int** ppArgs, const char** ppEnd, ArgParser* p);
    void CreateHelpString(const char* name, eastl::string8* out, int style);  // 0x00839f90
    int  ConstructSpec(int a, const char* cmd, const char* spec);          // 0x0083bcd0
    void ParseThrowing(int argc, const char** argv, ArgParser* p);         // 0x0083b9d0
};

void __cdecl Sprintf(eastl::string8* out, const char* fmt, ...);   // 0x00840c20
void __cdecl FUN_00837f80(int* out, const void* p);                // 0x00837f80
void __cdecl FUN_00837f60();                                       // 0x00837f60
extern void* __TI1_cError[];

// vector<cOptionsSpec> helpers
cOptionsSpec* __cdecl UninitCopySpec(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* dest);  // 0x00839ef0
cOptionsSpec* __cdecl DestroyOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* result);  // 0x0083a310
cOptionsSpec* __cdecl CopyOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* result);     // 0x0083a900
cOptionsSpec* __cdecl CopyBackwardOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* destEnd); // 0x0083a970
void __cdecl DestroyOptionsRangeV(cOptionsSpec* first, cOptionsSpec* last);  // 0x0076e7a0

// 0083baa0 DoInsertValue<cOptionsSpec> is a member of this concrete vector type
struct VecOptions {
    cOptionsSpec* mpBegin; cOptionsSpec* mpEnd; cOptionsSpec* mpCapacity;
    eastl::sp_vector_allocator mAllocator;
    void DoInsertValue(cOptionsSpec* pos, const cOptionsSpec& v);      // 0x0083baa0
    cOptionsSpec* erase(cOptionsSpec* first, cOptionsSpec* last);      // 0x0083ba40
    void DestroyRangeA(cOptionsSpec* first, cOptionsSpec* last);       // 0x0076e7a0
};

// ---- command base classes (refcounted) ----
extern void* vtbl_SPSkinPaintClear[];
extern void* vtbl_SPSkinPaintDistributeParticles[];

struct cCommandBase {
    void** vtbl;        // +0x00
    void*  mParser;     // +0x04
    int    mRefCount;   // +0x08
    cCommandBase();     // 0x0083c800 (SPSkinPaintClear ctor)
    int Release();      // 0x0083c760
};
struct cBlockCommandBase {
    void** vtbl; void* mParser; int mRefCount;
    int Release();      // 0x0083c7a0
};
struct cMetaCommandBase {
    void** vtbl; void* mParser; int mRefCount;
    cMetaCommandBase(); // 0x0083c840
    int Release();      // 0x0083c7d0
};

struct cError { cError(const char* s); };

// ===========================================================================
// 0x0083b810  EA::ArgScript::cArgumentSpec::Parse
// ===========================================================================
// @ 0x0083b810
int cArgumentSpec::Parse(int argc, const char** argv, ArgParser* p) {
    mErrorString.assign("no error", "");
    const char* prog = argv[0];
    const char** end = argv + argc;
    mFlags = 0;
    const char** cur = argv + 1;
    int nDefaults = (int)(mDefaultArguments.mpEnd - mDefaultArguments.mpBegin);
    int nUsed = 0, i = 0;
    while (cur < end) {
        const char* s = *cur;
        if (s[0] == '-' && isalpha((unsigned char)s[1])) {
            int r = ParseOption((int**)&cur, end, p);
            if (r != 0) {
                if (r == 1)
                    CreateHelpString(prog, &mErrorString, 1);
                return r;
            }
        } else {
            if (nUsed >= nDefaults) {
                Sprintf(&mErrorString, "Too many default arguments (expecting at most %d)\n", nDefaults);
                return 3;
            }
            cArgInfo* ai = &mDefaultArguments.mpBegin[i];
            int r;
            if (nUsed == nDefaults - 1 && (ai->mType & 0x8000)) {
                r = p ? ParseVectorArgument(ai, s, p) : ParseVectorArgument(ai, s);
            } else {
                r = p ? ParseArgumentEx(ai, s, p) : ParseArgument(ai, s);
                ++nUsed; ++i;
            }
            if (r != 0)
                return r;
            ++cur;
        }
    }
    if (nUsed < nDefaults) {
        cArgInfo* ai = &mDefaultArguments.mpBegin[nUsed];
        if (ai->mIsDependent && (ai->mType & 0x8000) == 0) {
            mErrorString.assign("Not enough arguments");
            return 2;
        }
    }
    return 0;
}

// ===========================================================================
// 0x0083b9d0  cArgumentSpec::Parse (throwing overload)
// ===========================================================================
// @ 0x0083b9d0
void cArgumentSpec::ParseThrowing(int argc, const char** argv, ArgParser* p) {
    int n = 0;
    FUN_00837f80(&n, &argc);
    FUN_00837f60();
    int r = Parse(n, argv, p);
    if (r != 0) {
        cError err(mErrorString.mpBegin);
        _CxxThrowException(&err, (_ThrowInfo*)&__TI1_cError);
    }
}

// ===========================================================================
// 0x0083ba40  eastl::vector<cOptionsSpec>::erase(first, last)
// ===========================================================================
// @ 0x0083ba40
cOptionsSpec* VecOptions::erase(cOptionsSpec* first, cOptionsSpec* last) {
    cOptionsSpec* newEnd = CopyOptionsRange(last, mpEnd, first);
    DestroyRangeA(newEnd, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// ===========================================================================
// 0x0083baa0  eastl::vector<cOptionsSpec>::DoInsertValue(pos, v)
// ===========================================================================
// @ 0x0083baa0
void VecOptions::DoInsertValue(cOptionsSpec* pos, const cOptionsSpec& v) {
    if (mpEnd != mpCapacity) {
        const cOptionsSpec* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) cOptionsSpec(*(mpEnd - 1));
        CopyBackwardOptionsRange(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        cOptionsSpec* nb = n ? (cOptionsSpec*)EASTL_allocator_allocate(n * 0x38, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        cOptionsSpec* np = UninitCopySpec(mpBegin, pos, nb);
        DestroyOptionsRange(mpBegin, pos, nb);
        if (np) ::new((void*)np) cOptionsSpec(v);
        cOptionsSpec* ne = UninitCopySpec(pos, mpEnd, np + 1);
        DestroyOptionsRange(pos, mpEnd, np + 1);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = ne; mpCapacity = nb + n;
    }
}

// ===========================================================================
// 0x0083bcd0  EA::ArgScript::cArgumentSpec::ConstructSpec  (partial)
// ===========================================================================
// @ 0x0083bcd0
// This is a 2682-byte command-spec parser (resets the default/options/enum
// vectors, splits the command string, then walks option/enum definitions).
// Not reconstructed here; kept as a compiling stub. See partial.txt.
int cArgumentSpec::ConstructSpec(int a, const char* cmd, const char* spec) {
    (void)a; (void)cmd; (void)spec;
    return 0;
}

// ===========================================================================
// 0x0083c760  EA::ArgScript::cCommandBase::Release
// ===========================================================================
// @ 0x0083c760
int cCommandBase::Release() {
    int n = --mRefCount;
    if (mRefCount == 0) {
        ((void(__thiscall*)(void*, int))vtbl[0x14 / 4])(this, 1);
        n = 0;
    }
    return n;
}

// ===========================================================================
// 0x0083c7a0  EA::ArgScript::cBlockCommandBase::Release
// ===========================================================================
// @ 0x0083c7a0
int cBlockCommandBase::Release() {
    int n = --mRefCount;
    if (mRefCount == 0) {
        ((void(__thiscall*)(void*, int))vtbl[0x20 / 4])(this, 1);
        n = 0;
    }
    return n;
}

// ===========================================================================
// 0x0083c7d0  EA::ArgScript::cMetaCommandBase::Release
// ===========================================================================
// @ 0x0083c7d0
int cMetaCommandBase::Release() {
    int n = --mRefCount;
    if (mRefCount == 0) {
        ((void(__thiscall*)(void*, int))vtbl[0x1c / 4])(this, 1);
        n = 0;
    }
    return n;
}

// ===========================================================================
// 0x0083c800  ArgScript::SPSkinPaintClear::SPSkinPaintClear
// ===========================================================================
// @ 0x0083c800
cCommandBase::cCommandBase() {
    vtbl = vtbl_SPSkinPaintClear;
    mParser = 0;
    mRefCount = 0;
}

// ===========================================================================
// 0x0083c840  ArgScript::SPSkinPaintDistributeParticles::SPSkinPaintDistributeParticles
// ===========================================================================
// @ 0x0083c840
cMetaCommandBase::cMetaCommandBase() {
    vtbl = vtbl_SPSkinPaintDistributeParticles;
    mParser = 0;
    mRefCount = 0;
}
