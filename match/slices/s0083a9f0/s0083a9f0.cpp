// Slice s0083a9f0 (batch w2g7).
// EA::ArgScript::cArgumentSpec: constructor, argument parsing (with and without a
// parser interface), options parsing. Compiled /O2 /MD /Gy /EHsc /TP /GS-.

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef int            int32;

extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void* __cdecl memcpy(void* dst, const void* src, unsigned n);
long  __cdecl atol(const char*);
int   __cdecl isalpha(int);
unsigned __cdecl strlen(const char*);
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
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;

    string8() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);   // 0x00454cb0
    void assign(const char* p);                         // 0x006a4380
    void append(const char* first, const char* last);   // 0x00455d60
    void RangeInitialize(unsigned n);                   // 0x00475ab0
    string8(const string8& x);                          // 0x0057cb10
    ~string8();                                         // (inline-free) dtor for EH
};

template <typename T>
struct vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
}  // namespace eastl

struct cArgInfo {
    int mType;                       // +0x00
    eastl::string8 mName;            // +0x04
    void* mLocation;                 // +0x14
    bool mIsDependent;               // +0x18
    int mFlagToSet;                  // +0x1c
    cArgInfo(const cArgInfo& x);     // 0x00838ab0
};

struct cEnumParseInfo { char* mToken; int mValue; };

struct cEnumSpec {
    eastl::string8 mName;            // +0x00
    cEnumParseInfo* mEnumInfo;       // +0x10
    int mPad14;                      // +0x14
    cEnumSpec(const cEnumSpec& x);   // 0x00e84850
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
};
typedef eastl::vec<cOptionsSpec> VecOptionsSpec;

struct cOptionArgInfo {
    char* mName; int mFirstArgumentIndex; int mNumArguments; bool mProcessed;
};
struct cArguments {
    eastl::vec<char>              mArgStorage;         // +0x00
    eastl::vec<char*>             mArguments;          // +0x10
    eastl::vec<cOptionArgInfo>    mOptionArguments;    // +0x20
    int                           mMainArgumentsStart; // +0x30
    int                           mNumMainArguments;   // +0x34

    cArguments();                                                          // 0x00837ff0
    ~cArguments();
    void SplitIntoArguments(const char* s);                                // 0x008383c0
    int  NumArguments();                                                   // 0x00837f30
    char* operator[](int i);                                               // 0x00837f20
};

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

    cArgumentSpec(bool respectHelp);                                      // 0x0083a9f0
    int  ParseVectorArgument(cArgInfo* ai, const char* str);              // 0x0083aaa0
    int  ParseVectorArgument(cArgInfo* ai, const char* str, ArgParser* p);// 0x0083ac80
    int  ParseArgument(cArgInfo* ai, const char* str);                    // 0x0083afc0
    int  ParseArgumentEx(cArgInfo* ai, const char* str, ArgParser* p);    // 0x0083b1d0
    int  ParseOptionArgs(cOptionsSpec* opt, int** ppArgs, const char** ppEnd, ArgParser* p);  // 0x0083b580
    int  ParseOption(int** ppArgs, const char** ppEnd, ArgParser* p);     // 0x0083b6d0
};

void __cdecl Sprintf(eastl::string8* out, const char* fmt, ...);          // 0x00840c20
float __cdecl ParseFloatStr(const char* s);                              // 0x00838740
int   __cdecl ParseEnumToken(const char* s, cEnumParseInfo* info, const char** out);  // 0x008407c0
int   __cdecl ParseEnumToken2(const char* s, cEnumParseInfo* info, const char** out); // 0x00840840
void  __cdecl PushByteVec(eastl::vec<char>* v, const char* p);           // 0x00421080
void  __cdecl PushUIntVec(eastl::vec<uint32>* v, const uint32* p);       // 0x00454860
void  __cdecl PushFloatVec(eastl::vec<float>* v, const float* p);        // 0x004547f0
void  __cdecl PushDoubleVec(eastl::vec<double>* v, const double* p);     // 0x005016f0
void  __cdecl PushCStringVec(eastl::vec<const char*>* v, const char** p); // 0x0067f640
void  __cdecl PushStringVec(eastl::vec<eastl::string8>* v, const eastl::string8* p); // 0x00553cc0
void  __cdecl PushVec2(eastl::vec<unsigned>* v, void* p);                // 0x00839d80
void  __cdecl PushVec3(eastl::vec<unsigned>* v, void* p);                // 0x007ed3e0
void  __cdecl PushVec4(eastl::vec<unsigned>* v, void* p);                // 0x00839dc0

// raw vtable helpers for the parser interface (slots are byte offsets into the vtable)
inline bool   PBool(ArgParser* p, const char* s) { return ((bool(__thiscall*)(ArgParser*, const char*))((void**)p->vtbl)[0x94 / 4])(p, s); }
inline int    PInt(ArgParser* p, const char* s) { return ((int(__thiscall*)(ArgParser*, const char*))((void**)p->vtbl)[0x9c / 4])(p, s); }
inline long double PFloat(ArgParser* p, const char* s) { return ((long double(__thiscall*)(ArgParser*, const char*))((void**)p->vtbl)[0x98 / 4])(p, s); }
inline void*  PVec2(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xa4 / 4])(p, out, s); }
inline void*  PVec3(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xa8 / 4])(p, out, s); }
inline void*  PVec4(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xac / 4])(p, out, s); }
inline void*  PColor3(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xb0 / 4])(p, out, s); }
inline void*  PColor4(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xb4 / 4])(p, out, s); }

// ===========================================================================
// 0x0083a9f0  EA::ArgScript::cArgumentSpec::cArgumentSpec
// ===========================================================================
// @ 0x0083a9f0
cArgumentSpec::cArgumentSpec(bool respectHelp)
    : mCommandName(), mBriefDescription(), mFullDescription(),
      mDefaultArguments(), mOptions(), mEnumSpecs(),
      mRespectHelp(respectHelp), mFlags(0), mVectorArgs(), mErrorString() {
}

// ===========================================================================
// 0x0083aaa0  cArgumentSpec::ParseVectorArgument (no parser)
// ===========================================================================
// @ 0x0083aaa0
int cArgumentSpec::ParseVectorArgument(cArgInfo* ai, const char* str) {
    switch (ai->mType & 0x3fff) {
    case 1:
        if (ai->mLocation) {
            bool b = atol(str) != 0;
            PushByteVec((eastl::vec<char>*)ai->mLocation, (const char*)&b);
        }
        return 0;
    case 2:
        if (ai->mLocation) {
            uint32 v = (uint32)atol(str);
            PushUIntVec((eastl::vec<uint32>*)ai->mLocation, &v);
        }
        return 0;
    case 3:
        if (ai->mLocation) {
            float v = ParseFloatStr(str);
            PushFloatVec((eastl::vec<float>*)ai->mLocation, &v);
        }
        return 0;
    case 4:
        if (ai->mLocation) {
            double v = ParseFloatStr(str);
            PushDoubleVec((eastl::vec<double>*)ai->mLocation, &v);
        }
        return 0;
    case 5:
        if (ai->mLocation)
            PushCStringVec((eastl::vec<const char*>*)ai->mLocation, &str);
        return 0;
    case 6:
        if (ai->mLocation) {
            eastl::string8 tmp;
            tmp.assign(str);
            PushStringVec((eastl::vec<eastl::string8>*)ai->mLocation, &tmp);
        }
        return 0;
    }
    Sprintf(&mErrorString, "Unknown vector arg type %d", ai->mType);
    return 4;
}

// ===========================================================================
// 0x0083ac80  cArgumentSpec::ParseVectorArgument (with parser)
// ===========================================================================
// @ 0x0083ac80
int cArgumentSpec::ParseVectorArgument(cArgInfo* ai, const char* str, ArgParser* p) {
    switch (ai->mType & 0x3fff) {
    case 1:
        if (ai->mLocation && p) {
            bool b = PBool(p, str);
            PushByteVec((eastl::vec<char>*)ai->mLocation, (const char*)&b);
        }
        return 0;
    case 2:
        if (ai->mLocation && p) {
            uint32 v = (uint32)PInt(p, str);
            PushUIntVec((eastl::vec<uint32>*)ai->mLocation, &v);
        }
        return 0;
    case 3:
        if (ai->mLocation && p) {
            float v = (float)PFloat(p, str);
            PushFloatVec((eastl::vec<float>*)ai->mLocation, &v);
        }
        return 0;
    case 4:
        if (ai->mLocation && p) {
            double v = (double)PFloat(p, str);
            PushDoubleVec((eastl::vec<double>*)ai->mLocation, &v);
        }
        return 0;
    case 5:
        if (ai->mLocation)
            PushCStringVec((eastl::vec<const char*>*)ai->mLocation, &str);
        return 0;
    case 6:
        if (ai->mLocation) {
            eastl::string8 tmp;
            tmp.assign(str);
            PushStringVec((eastl::vec<eastl::string8>*)ai->mLocation, &tmp);
        }
        return 0;
    case 7:
        if (ai->mLocation && p) {
            unsigned out[2];
            void* r = PVec2(p, out, str);
            ((unsigned*)ai->mLocation)[0] = ((unsigned*)r)[0];
            ((unsigned*)ai->mLocation)[1] = ((unsigned*)r)[1];
        }
        return 0;
    case 8:
        if (ai->mLocation && p) {
            unsigned out[3];
            void* r = PVec3(p, out, str);
            PushVec3((eastl::vec<unsigned>*)ai->mLocation, r);
        }
        return 0;
    case 9:
        if (ai->mLocation && p) {
            unsigned out[4];
            void* r = PVec4(p, out, str);
            PushVec4((eastl::vec<unsigned>*)ai->mLocation, r);
        }
        return 0;
    case 10:
        if (ai->mLocation && p) {
            unsigned out[3];
            void* r = PColor3(p, out, str);
            PushVec3((eastl::vec<unsigned>*)ai->mLocation, r);
        }
        return 0;
    case 11:
        if (ai->mLocation && p) {
            unsigned out[4];
            void* r = PColor4(p, out, str);
            PushVec4((eastl::vec<unsigned>*)ai->mLocation, r);
        }
        return 0;
    }
    Sprintf(&mErrorString, "Unknown vector arg type %d", ai->mType);
    return 4;
}

// ===========================================================================
// 0x0083afc0  EA::ArgScript::cArgumentSpec::ParseArgument
// ===========================================================================
// @ 0x0083afc0
int cArgumentSpec::ParseArgument(cArgInfo* ai, const char* str) {
    int flag = ai->mFlagToSet;
    if (flag >= 0)
        mFlags |= 1 << flag;
    unsigned type = (unsigned)ai->mType;
    if (type & 0x4000) {
        mVectorArgs.SplitIntoArguments(str);
        for (int i = 0; i < mVectorArgs.NumArguments(); ++i) {
            int r = ParseVectorArgument(ai, mVectorArgs[i]);
            if (r) return r;
        }
        return 0;
    }
    switch (type) {
    case 1:
        if (ai->mLocation) *(bool*)ai->mLocation = atol(str) != 0;
        return 0;
    case 2:
        if (ai->mLocation) *(int*)ai->mLocation = (int)atol(str);
        return 0;
    case 3:
        if (ai->mLocation) *(float*)ai->mLocation = ParseFloatStr(str);
        return 0;
    case 4:
        if (ai->mLocation) *(double*)ai->mLocation = ParseFloatStr(str);
        return 0;
    case 5:
        if (ai->mLocation) *(const char**)ai->mLocation = str;
        return 0;
    case 6:
        if (ai->mLocation) ((eastl::string8*)ai->mLocation)->assign(str);
        return 0;
    }
    if (type >= 0xc) {
        unsigned n = (unsigned)(mEnumSpecs.mpEnd - mEnumSpecs.mpBegin);
        if (type - 0xc < n) {
            cEnumSpec* es = &mEnumSpecs.mpBegin[type - 0xc];
            if (ParseEnumToken(str, es->mEnumInfo, &str)) {
                *(const char**)ai->mLocation = str;
                return 0;
            }
            Sprintf(&mErrorString, "Unknown enum '%s' of type %s", str, es->mName.mpBegin);
            return 6;
        }
    }
    Sprintf(&mErrorString, "Unknown arg type %d", type);
    return 4;
}

// ===========================================================================
// 0x0083b1d0  cArgumentSpec::ParseArgumentEx (with parser)
// ===========================================================================
// @ 0x0083b1d0
int cArgumentSpec::ParseArgumentEx(cArgInfo* ai, const char* str, ArgParser* p) {
    int flag = ai->mFlagToSet;
    if (flag >= 0)
        mFlags |= 1 << flag;
    unsigned type = (unsigned)ai->mType;
    if (type & 0x4000) {
        mVectorArgs.SplitIntoArguments(str);
        for (int i = 0; i < mVectorArgs.NumArguments(); ++i) {
            int r = ParseVectorArgument(ai, mVectorArgs[i], p);
            if (r) return r;
        }
        return 0;
    }
    switch (type) {
    case 1:
        if (ai->mLocation) *(bool*)ai->mLocation = PBool(p, str);
        return 0;
    case 2:
        if (ai->mLocation) *(int*)ai->mLocation = PInt(p, str);
        return 0;
    case 3:
        if (ai->mLocation) *(float*)ai->mLocation = (float)PFloat(p, str);
        return 0;
    case 4:
        if (ai->mLocation) *(double*)ai->mLocation = (double)PFloat(p, str);
        return 0;
    case 5:
        if (ai->mLocation) *(const char**)ai->mLocation = str;
        return 0;
    case 6:
        if (ai->mLocation) ((eastl::string8*)ai->mLocation)->assign(str);
        return 0;
    case 7:
        if (ai->mLocation && p) {
            unsigned out[2];
            void* r = PVec2(p, out, str);
            ((unsigned*)ai->mLocation)[0] = ((unsigned*)r)[0];
            ((unsigned*)ai->mLocation)[1] = ((unsigned*)r)[1];
        }
        return 0;
    case 8:
        if (ai->mLocation && p) {
            unsigned out[3];
            void* r = PVec3(p, out, str);
            ((unsigned*)ai->mLocation)[0] = ((unsigned*)r)[0];
            ((unsigned*)ai->mLocation)[1] = ((unsigned*)r)[1];
            ((unsigned*)ai->mLocation)[2] = ((unsigned*)r)[2];
        }
        return 0;
    case 9:
        if (ai->mLocation && p) {
            unsigned out[4];
            void* r = PVec4(p, out, str);
            ((unsigned*)ai->mLocation)[0] = ((unsigned*)r)[0];
            ((unsigned*)ai->mLocation)[1] = ((unsigned*)r)[1];
            ((unsigned*)ai->mLocation)[2] = ((unsigned*)r)[2];
            ((unsigned*)ai->mLocation)[3] = ((unsigned*)r)[3];
        }
        return 0;
    case 10:
        if (ai->mLocation && p) {
            unsigned out[3];
            void* r = PColor3(p, out, str);
            ((unsigned*)ai->mLocation)[0] = ((unsigned*)r)[0];
            ((unsigned*)ai->mLocation)[1] = ((unsigned*)r)[1];
            ((unsigned*)ai->mLocation)[2] = ((unsigned*)r)[2];
        }
        return 0;
    case 11:
        if (ai->mLocation && p) {
            unsigned out[4];
            void* r = PColor4(p, out, str);
            ((unsigned*)ai->mLocation)[0] = ((unsigned*)r)[0];
            ((unsigned*)ai->mLocation)[1] = ((unsigned*)r)[1];
            ((unsigned*)ai->mLocation)[2] = ((unsigned*)r)[2];
            ((unsigned*)ai->mLocation)[3] = ((unsigned*)r)[3];
        }
        return 0;
    }
    if (type >= 0xc) {
        unsigned n = (unsigned)(mEnumSpecs.mpEnd - mEnumSpecs.mpBegin);
        if (type - 0xc < n) {
            cEnumSpec* es = &mEnumSpecs.mpBegin[type - 0xc];
            if ((es->mEnumInfo && ParseEnumToken2(str, es->mEnumInfo, &str)) ||
                (es->mEnumInfo && ParseEnumToken(str, es->mEnumInfo, &str))) {
                *(const char**)ai->mLocation = str;
                return 0;
            }
            Sprintf(&mErrorString, "Unknown enum '%s' of type %s", str, es->mName.mpBegin);
            return 6;
        }
    }
    Sprintf(&mErrorString, "Unknown arg type %d", type);
    return 4;
}

// ===========================================================================
// 0x0083b580  EA::ArgScript::cArgumentSpec::ParseOptionArgs
// ===========================================================================
// @ 0x0083b580
int cArgumentSpec::ParseOptionArgs(cOptionsSpec* opt, int** ppArgs, const char** ppEnd, ArgParser* p) {
    int nArgs = (int)((opt->mArguments.mpEnd - opt->mArguments.mpBegin));
    int nUsed = 0;
    bool bVector = false;
    while ((char*)*ppArgs < (char*)ppEnd) {
        char* s = *(char**)*ppArgs;
        if (nUsed >= nArgs) break;
        if (s[0] == '-' && isalpha((unsigned char)s[1])) break;
        if (nUsed == nArgs - 1 && (opt->mArguments.mpBegin[nUsed].mType & 0x8000)) {
            bVector = true;
            if (p) ParseVectorArgument(&opt->mArguments.mpBegin[nUsed], s, p);
            else   ParseVectorArgument(&opt->mArguments.mpBegin[nUsed], s);
        } else {
            if (p) ParseArgumentEx(&opt->mArguments.mpBegin[nUsed], s, p);
            else   ParseArgument(&opt->mArguments.mpBegin[nUsed], s);
            ++nUsed;
        }
        ++*ppArgs;
    }
    if (!bVector) {
        int i = nUsed;
        if (i >= nArgs) return 0;
        if (!opt->mArguments.mpBegin[i].mIsDependent) return 0;
        while (i < nArgs && opt->mArguments.mpBegin[i].mIsDependent) ++i;
        Sprintf(&mErrorString, "Not enough arguments: expecting at least %d more", i - nUsed);
        return 2;
    }
    return 0;
}

// ===========================================================================
// 0x0083b6d0  EA::ArgScript::cArgumentSpec::ParseOption
// ===========================================================================
// @ 0x0083b6d0
int cArgumentSpec::ParseOption(int** ppArgs, const char** ppEnd, ArgParser* p) {
    const char* name = *(char**)*ppArgs;
    ++name;
    *ppArgs = *ppArgs + 1;
    if (mRespectHelp) {
        if (_stricmp(name, "help") == 0 || _stricmp(name, "h") == 0)
            return 1;
    }
    int count = (int)((mOptions.mpEnd - mOptions.mpBegin));
    for (int i = 0; i < count; ++i) {
        if (_stricmp(mOptions.mpBegin[i].mName.mpBegin, name) == 0) {
            int flag = mOptions.mpBegin[i].mFlagToSet;
            if (flag >= 0)
                mFlags |= 1 << flag;
            int r = ParseOptionArgs(&mOptions.mpBegin[i], ppArgs, ppEnd, p);
            if (r != 0) {
                mErrorString.append(" in -", " in -" + 5);
                const char* q = name;
                while (*q) ++q;
                mErrorString.append(name, q);
            }
            return r;
        }
    }
    Sprintf(&mErrorString, "Unknown option '%s'", name);
    return 5;
}
