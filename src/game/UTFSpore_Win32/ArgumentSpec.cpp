// src/game/UTFSpore_Win32/ArgumentSpec.cpp -- migrated from slice(s) s0083b810, s0083a9f0, s00839950, s008387c0, s00837820 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ArgumentSpec.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "eastl/allocator.h"
#include "EA/ArgScript/cArgInfo.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cEnumParseInfo.h"
#include "EA/ArgScript/cEnumSpec.h"
#include "EA/ArgScript/cOptionsSpec.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cError.h"

// ---- items of slice s00837820 begin (TODO(rewrite): local stubs, replace by canonical classes)
__declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
__declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, unsigned int);
// ---- items of slice s00837820 end

// ---- items of slice s008387c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator_delete__(void*);
void  __cdecl DoInsertValue(char*, const char*, uint32_t);   // 0x11e0744
char* __cdecl SearchStr(void*, void*, void*, void*);         // 0x609d50
template <typename T> static const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
struct RawStr {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;

    void RangeInitialize(uint32_t n);                 // 0x475ab0
    void Assign(const char* first, const char* last); // 0x454cb0
    RawStr(const RawStr& s, uint32_t pos, uint32_t n); // 0x8389f0
    int  Find(const char* p, uint32_t pos);           // 0x838a60
};
struct Ent {                 // 0x20 bytes
    int    field0;           // +0
    RawStr name;             // +4
    int    field14;          // +0x14
    bool   field18;          // +0x18
    char   pad[3];
    int    field1c;          // +0x1c
    Ent* CopyFrom(const Ent* src);
};
struct Ent2 {                // 0x18 bytes
    RawStr name;             // +0
    int    field10;          // +0x10
    int    field14;          // +0x14
};
struct Vec2 {
    float x, y;
    Vec2& operator=(const Vec2& o) { x = o.x; y = o.y; return *this; }
};
// ---- items of slice s008387c0 end

// ---- items of slice s00839950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int, int, const char* file, int line);
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
inline void* operator new(unsigned, void* p) { return p; }
static const char g_allocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char g_allocName[] = "ArgScript";
namespace eastl {
struct allocator_s0083_9950 { unsigned char pad[4]; };
}
namespace eastl {
struct sp_vector_allocator_s0083_9950 : allocator_s0083_9950 {};
}
namespace eastl {
struct string8_s0083_9950 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0083_9950 mAllocator;

    void assign(const char* first, const char* last);   // 0x00454cb0
    void append(const char* first, const char* last);   // 0x00455d60
    void RangeInitialize(unsigned n);                   // 0x00475ab0
    string8_s0083_9950(const string8_s0083_9950& x);                          // 0x0057cb10
};
}
namespace eastl {
template <typename T>
struct vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0083_9950 mAllocator;
};
}
struct cArgInfo {
    int mType;                       // +0x00
    eastl::string8_s0083_9950 mName;            // +0x04
    void* mLocation;                 // +0x14
    bool mIsDependent;               // +0x18
    int mFlagToSet;                  // +0x1c

    cArgInfo(const cArgInfo& x);     // 0x00838ab0
    cArgInfo& operator=(const cArgInfo& x) {
        mType = x.mType;
        if (&mName != &x.mName)
            mName.assign(x.mName.mpBegin, x.mName.mpEnd);
        mLocation = x.mLocation;
        mIsDependent = x.mIsDependent;
        mFlagToSet = x.mFlagToSet;
        return *this;
    }
};
struct cEnumParseInfo { char* mToken; int mValue; };
struct cEnumSpec {
    eastl::string8_s0083_9950 mName;            // +0x00
    cEnumParseInfo* mEnumInfo;       // +0x10
    int mPad14;                      // +0x14

    cEnumSpec(const cEnumSpec& x);   // 0x00e84850
    cEnumSpec& operator=(const cEnumSpec& x) {
        if (this != &x)
            mName.assign(x.mName.mpBegin, x.mName.mpEnd);
        mEnumInfo = x.mEnumInfo;
        mPad14 = x.mPad14;
        return *this;
    }
};
cArgInfo* __cdecl MoveArgRange(cArgInfo* first, cArgInfo* last, cArgInfo* dest);        // 0x00838f20
void      __cdecl UninitCopyArgEH(cArgInfo** pp, cArgInfo* first, cArgInfo* last,
                                  cArgInfo* dest, const void* x);                        // 0x00838bc0
struct VecArgInfo {
    cArgInfo* mpBegin;               // +0x00
    cArgInfo* mpEnd;                 // +0x04
    cArgInfo* mpCapacity;            // +0x08
    eastl::sp_vector_allocator_s0083_9950 mAllocator;  // +0x0c

    VecArgInfo(const VecArgInfo& x);                                    // 0x00839950
    ~VecArgInfo();                                                      // 0x00838d?0 VectorBase dtor
    VecArgInfo& operator=(const VecArgInfo& x);                         // 0x0083a740
    void DoInsertValue(cArgInfo* pos, const cArgInfo& v);               // 0x0083a3c0
    void DoAllocate(unsigned n, const eastl::sp_vector_allocator_s0083_9950& a);   // 0x00838b30
    cArgInfo* DoAllocateCopy(unsigned n, cArgInfo* f, cArgInfo* l);     // 0x00838e20
    void FreeRange(cArgInfo* f, cArgInfo* l);                           // 0x0076e430
};
cEnumSpec* __cdecl UninitCopyEnum(cEnumSpec* first, cEnumSpec* last, cEnumSpec* dest);       // 0x00838cd0
void       __cdecl UninitDestroyEnum(cEnumSpec* first, cEnumSpec* last, cEnumSpec* dest);    // 0x00838ed0
cEnumSpec* __cdecl CopyBackwardEnum(cEnumSpec* first, cEnumSpec* last, cEnumSpec* destEnd);  // 0x00839040
struct VecEnumSpec {
    cEnumSpec* mpBegin;
    cEnumSpec* mpEnd;
    cEnumSpec* mpCapacity;
    eastl::sp_vector_allocator_s0083_9950 mAllocator;

    void DoInsertValue(cEnumSpec* pos, const cEnumSpec& v);             // 0x0083a580
};
struct cOptionsSpec {
    eastl::string8_s0083_9950 mName;            // +0x00
    eastl::string8_s0083_9950 mDescription;     // +0x10
    VecArgInfo     mArguments;       // +0x20
    int            mPad30;           // +0x30
    int            mFlagToSet;       // +0x34

    cOptionsSpec& operator=(const cOptionsSpec& x);
};
typedef eastl::vec<cOptionsSpec> VecOptionsSpec;
struct cArgumentSpec {
    char pad00[0x10];
    eastl::string8_s0083_9950 mBriefDescription;   // +0x10
    eastl::string8_s0083_9950 mFullDescription;    // +0x20
    VecArgInfo     mDefaultArguments;   // +0x30
    char pad40[0x4];                    // +0x40
    VecOptionsSpec mOptions;            // +0x44
    char pad54[0x4];                    // +0x54
    VecEnumSpec    mEnumSpecs;          // +0x58
    char pad68[0xb8 - 0x68];
    eastl::string8_s0083_9950 mErrorString;        // +0xb8

    void NameFromArgType(int type, eastl::string8_s0083_9950* out);                              // 0x008397a0
    void AddArgDocs(eastl::string8_s0083_9950* out, VecArgInfo* args, int style);                // 0x00839c00
    void CreateHelpString(const char* name, eastl::string8_s0083_9950* out, int style);          // 0x00839f90
    const char* HelpString(const char* name, int style);                              // 0x0083a2f0
};
void __cdecl SprintfAppend(eastl::string8_s0083_9950* out, const char* fmt, ...);   // 0x00840c70
void __cdecl Sprintf(eastl::string8_s0083_9950* out, const char* fmt, ...);         // 0x00840c20
void __cdecl AddDocString(eastl::string8_s0083_9950* out, const char* prefix, eastl::string8_s0083_9950 desc);  // 0x008392b0
void __cdecl AddEnumDocs(eastl::string8_s0083_9950* out, const char* prefix, VecEnumSpec* enums, int style);  // 0x008393a0
struct E8 { float x, y; E8(const E8& o) { x = o.x; y = o.y; } };
E8* __cdecl UninitCopy8(E8* first, E8* last, E8* dest) throw();                      // 0x00838b90
struct V8 {
    E8* mpBegin; E8* mpEnd; E8* mpCapacity;
    void push_back(const E8& v);
    void DoInsertValue(E8* pos, const E8& v);
};
struct E16 { float x, y, z, w; E16(const E16& o) { x = o.x; y = o.y; z = o.z; w = o.w; } };
E16* __cdecl UninitCopy16(E16* first, E16* last, E16* dest) throw();                 // 0x00b115c0
E16* __cdecl CopyBackward16(E16* first, E16* last, E16* destEnd) throw();            // 0x00edba80
struct V16 {
    E16* mpBegin; E16* mpEnd; E16* mpCapacity;
    void push_back(const E16& v);
    void DoInsertValue(E16* pos, const E16& v);
};
cArgInfo* __cdecl CopyBackwardArg(cArgInfo* first, cArgInfo* last, cArgInfo* destEnd);  // 0x00838f80
cArgInfo* __cdecl UninitCopyArg(cArgInfo* first, cArgInfo* last, cArgInfo* dest);       // 0x00838c40
void      __cdecl UninitDestroyArg(cArgInfo* first, cArgInfo* last, cArgInfo* dest);    // 0x00838e80
// ---- items of slice s00839950 end

// ---- items of slice s0083a9f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long  __cdecl atol(const char*);
extern "C" __declspec(dllimport) int   __cdecl isalpha(int);
extern char gEmptyString[];
typedef unsigned int   uint32;
namespace eastl {
struct allocator_s0083_a9f0 { unsigned char pad[4]; };
}
namespace eastl {
struct sp_vector_allocator_s0083_a9f0 : allocator_s0083_a9f0 {};
}
namespace eastl {
struct string8_s0083_a9f0 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0083_a9f0 mAllocator;

    string8_s0083_a9f0() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void assign(const char* first, const char* last);   // 0x00454cb0
    void assign(const char* p);                         // 0x006a4380
    void append(const char* first, const char* last);   // 0x00455d60
    void RangeInitialize(unsigned n);                   // 0x00475ab0
    string8_s0083_a9f0(const string8_s0083_a9f0& x);                          // 0x0057cb10
    ~string8_s0083_a9f0();                                         // (inline-free) dtor for EH
};
}
namespace eastl {
template <typename T>
struct vec_s0083_a9f0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0083_a9f0 mAllocator;
    vec_s0083_a9f0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
}
struct cArgInfo_s0083_a9f0 {
    int mType;                       // +0x00
    eastl::string8_s0083_a9f0 mName;            // +0x04
    void* mLocation;                 // +0x14
    bool mIsDependent;               // +0x18
    int mFlagToSet;                  // +0x1c
    cArgInfo_s0083_a9f0(const cArgInfo_s0083_a9f0& x);     // 0x00838ab0
};
struct cEnumSpec_s0083_a9f0 {
    eastl::string8_s0083_a9f0 mName;            // +0x00
    cEnumParseInfo* mEnumInfo;       // +0x10
    int mPad14;                      // +0x14
    cEnumSpec_s0083_a9f0(const cEnumSpec_s0083_a9f0& x);   // 0x00e84850
    ~cEnumSpec_s0083_a9f0();
};
typedef eastl::vec_s0083_a9f0<cArgInfo_s0083_a9f0>  VecArgInfo_s0083_a9f0;
typedef eastl::vec_s0083_a9f0<cEnumSpec_s0083_a9f0> VecEnumSpec_s0083_a9f0;
struct cOptionsSpec_s0083_a9f0 {
    eastl::string8_s0083_a9f0 mName;            // +0x00
    eastl::string8_s0083_a9f0 mDescription;     // +0x10
    VecArgInfo_s0083_a9f0     mArguments;       // +0x20
    int            mPad30;           // +0x30
    int            mFlagToSet;       // +0x34
};
typedef eastl::vec_s0083_a9f0<cOptionsSpec_s0083_a9f0> VecOptionsSpec_s0083_a9f0;
struct cOptionArgInfo {
    char* mName; int mFirstArgumentIndex; int mNumArguments; bool mProcessed;
};
struct cArguments {
    eastl::vec_s0083_a9f0<char>              mArgStorage;         // +0x00
    eastl::vec_s0083_a9f0<char*>             mArguments;          // +0x10
    eastl::vec_s0083_a9f0<cOptionArgInfo>    mOptionArguments;    // +0x20
    int                           mMainArgumentsStart; // +0x30
    int                           mNumMainArguments;   // +0x34

    cArguments();                                                          // 0x00837ff0
    ~cArguments();
    void SplitIntoArguments(const char* s);                                // 0x008383c0
    int  NumArguments();                                                   // 0x00837f30
    char* operator[](int i);                                               // 0x00837f20
};
struct ArgParser { void** vtbl; };
struct cArgumentSpec_s0083_a9f0 {
    eastl::string8_s0083_a9f0 mCommandName;        // +0x00
    eastl::string8_s0083_a9f0 mBriefDescription;   // +0x10
    eastl::string8_s0083_a9f0 mFullDescription;    // +0x20
    VecArgInfo_s0083_a9f0     mDefaultArguments;   // +0x30
    char pad40[0x4];                    // +0x40
    VecOptionsSpec_s0083_a9f0 mOptions;            // +0x44
    char pad54[0x4];                    // +0x54
    VecEnumSpec_s0083_a9f0    mEnumSpecs;          // +0x58
    char pad64[0x4];                    // +0x64
    bool           mRespectHelp;        // +0x6c
    int            mFlags;              // +0x70
    cArguments     mVectorArgs;         // +0x74
    char padac[0xb8 - 0xac];
    eastl::string8_s0083_a9f0 mErrorString;        // +0xb8

    cArgumentSpec_s0083_a9f0(bool respectHelp);                                      // 0x0083a9f0
    int  ParseVectorArgument(cArgInfo_s0083_a9f0* ai, const char* str);              // 0x0083aaa0
    int  ParseVectorArgument(cArgInfo_s0083_a9f0* ai, const char* str, ArgParser* p);// 0x0083ac80
    int  ParseArgument(cArgInfo_s0083_a9f0* ai, const char* str);                    // 0x0083afc0
    int  ParseArgumentEx(cArgInfo_s0083_a9f0* ai, const char* str, ArgParser* p);    // 0x0083b1d0
    int  ParseOptionArgs(cOptionsSpec_s0083_a9f0* opt, int** ppArgs, const char** ppEnd, ArgParser* p);  // 0x0083b580
    int  ParseOption(int** ppArgs, const char** ppEnd, ArgParser* p);     // 0x0083b6d0
};
void __cdecl Sprintf(eastl::string8_s0083_a9f0* out, const char* fmt, ...);          // 0x00840c20
float __cdecl ParseFloatStr(const char* s);                              // 0x00838740
int   __cdecl ParseEnumToken(const char* s, cEnumParseInfo* info, const char** out);  // 0x008407c0
int   __cdecl ParseEnumToken2(const char* s, cEnumParseInfo* info, const char** out); // 0x00840840
void  __cdecl PushByteVec(eastl::vec_s0083_a9f0<char>* v, const char* p);           // 0x00421080
void  __cdecl PushUIntVec(eastl::vec_s0083_a9f0<uint32>* v, const uint32* p);       // 0x00454860
void  __cdecl PushFloatVec(eastl::vec_s0083_a9f0<float>* v, const float* p);        // 0x004547f0
void  __cdecl PushDoubleVec(eastl::vec_s0083_a9f0<double>* v, const double* p);     // 0x005016f0
void  __cdecl PushCStringVec(eastl::vec_s0083_a9f0<const char*>* v, const char** p); // 0x0067f640
void  __cdecl PushStringVec(eastl::vec_s0083_a9f0<eastl::string8_s0083_a9f0>* v, const eastl::string8_s0083_a9f0* p); // 0x00553cc0
void  __cdecl PushVec3(eastl::vec_s0083_a9f0<unsigned>* v, void* p);                // 0x007ed3e0
void  __cdecl PushVec4(eastl::vec_s0083_a9f0<unsigned>* v, void* p);                // 0x00839dc0
inline bool   PBool(ArgParser* p, const char* s) { return ((bool(__thiscall*)(ArgParser*, const char*))((void**)p->vtbl)[0x94 / 4])(p, s); }
inline int    PInt(ArgParser* p, const char* s) { return ((int(__thiscall*)(ArgParser*, const char*))((void**)p->vtbl)[0x9c / 4])(p, s); }
inline long double PFloat(ArgParser* p, const char* s) { return ((long double(__thiscall*)(ArgParser*, const char*))((void**)p->vtbl)[0x98 / 4])(p, s); }
inline void*  PVec2(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xa4 / 4])(p, out, s); }
inline void*  PVec3(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xa8 / 4])(p, out, s); }
inline void*  PVec4(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xac / 4])(p, out, s); }
inline void*  PColor3(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xb0 / 4])(p, out, s); }
inline void*  PColor4(ArgParser* p, void* out, const char* s) { return ((void*(__thiscall*)(ArgParser*, void*, const char*))((void**)p->vtbl)[0xb4 / 4])(p, out, s); }
// ---- items of slice s0083a9f0 end

// ---- items of slice s0083b810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned n);
extern "C" __declspec(dllimport) void* __cdecl memmove(void* dst, const void* src, unsigned n);
extern "C" unsigned __cdecl strlen(const char*);
extern void* __TI1_cError[];
#pragma intrinsic(strlen)
namespace eastl {
struct allocator_s0083_b810 { unsigned char pad[4]; };
}
namespace eastl {
struct sp_vector_allocator_s0083_b810 : allocator_s0083_b810 {};
}
namespace eastl {
template <typename T> inline const T& min_alt_s0083_b810(const T& a, const T& b) { return b < a ? b : a; }
}
namespace eastl {
struct string8_s0083_b810 {
    enum { npos = 0xffffffff };
    char* mpBegin; char* mpEnd; char* mpCapacity; allocator_s0083_b810 mAllocator;
    string8_s0083_b810() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    __forceinline string8_s0083_b810(const char* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + strlen(p)); }
    string8_s0083_b810(const string8_s0083_b810& x);                          // 0x0057cb10
    ~string8_s0083_b810() { DeallocateSelf(); }
    void assign(const char* first, const char* last);   // 0x00454cb0
    void assign(const char* p);                         // 0x006a4380
    void assign(const string8_s0083_b810& x, unsigned position, unsigned n) {
        assign(x.mpBegin + position, x.mpBegin + position + min_alt_s0083_b810(n, x.size() - position));
    }
    void append(const char* first, const char* last);   // 0x00455d60
    string8_s0083_b810& operator=(const string8_s0083_b810& x) { if (&x != this) assign(x.mpBegin, x.mpEnd); return *this; }
    string8_s0083_b810& operator=(const char* p) { assign(p, p + strlen(p)); return *this; }
    string8_s0083_b810& operator+=(const string8_s0083_b810& x) { append(x.mpBegin, x.mpEnd); return *this; }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    const char* c_str() const { return mpBegin; }
    char& operator[](unsigned i) { return mpBegin[i]; }
    char& back() { return *(mpEnd - 1); }
    char* erase(char* pBegin, char* pEnd) {
        if (pBegin != pEnd) {
            memmove(pBegin, pEnd, (unsigned)((mpEnd - pEnd) + 1));
            char* const pNewEnd = (mpEnd - (pEnd - pBegin));
            mpEnd = pNewEnd;
        }
        return pBegin;
    }
    __forceinline string8_s0083_b810& erase(unsigned position, unsigned n) {
        n = min_alt_s0083_b810(n, size() - position);
        erase(mpBegin + position, mpBegin + position + n);
        return *this;
    }
    void AllocateSelf() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void AllocateSelf(unsigned n) {
        if (n > 1) { mpBegin = DoAllocate(n); mpEnd = mpBegin; mpCapacity = mpBegin + n; }
        else AllocateSelf();
    }
    char* DoAllocate(unsigned n) {
        return (char*)EASTL_allocator_allocate(n, g_allocName, 0, 0, g_allocFile, 0xd1);
    }
    void DoFree(char* p, unsigned) { if (p) EASTL_allocator_deallocate(p); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin));
    }
    static char* CharStringUninitializedCopy(const char* pSource, const char* pSourceEnd, char* pDestination) {
        memcpy(pDestination, pSource, (unsigned)(pSourceEnd - pSource));
        return pDestination + (pSourceEnd - pSource);
    }
    __forceinline void RangeInitialize(const char* pBegin, const char* pEnd) {
        const unsigned n = (unsigned)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
};
}
namespace eastl {
template <typename T> T* CopyRange(T* first, T* last, T* dest);
}
namespace eastl {
template <typename T>
struct vec_s0083_b810 {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator_s0083_b810 mAllocator;
    vec_s0083_b810() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    bool empty() const { return mpBegin == mpEnd; }
    T& back() { return *(mpEnd - 1); }
    void DestroyValues(T* first, T* last);          // out of line (0x0076e430 / 0x0076e470)
    void DoInsertValue(T* position, const T& value); // out of line (0x0083a3c0)
    T* erase(T* first, T* last) {
        T* const position = CopyRange(last, mpEnd, first);
        DestroyValues(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
struct cArgInfo_s0083_b810 {
    int mType; eastl::string8_s0083_b810 mName; void* mLocation; bool mIsDependent; int mFlagToSet;
    cArgInfo_s0083_b810() {}
    cArgInfo_s0083_b810(const cArgInfo_s0083_b810& x);   // 0x00838ab0
};
struct cEnumSpec_s0083_b810 {
    eastl::string8_s0083_b810 mName; cEnumParseInfo* mEnumInfo; int mPad14;
    __forceinline cEnumSpec_s0083_b810(const char* name, cEnumParseInfo* info, int x) : mName(name), mEnumInfo(info), mPad14(x) {}
    cEnumSpec_s0083_b810(const cEnumSpec_s0083_b810& x); // 0x00e84850
};
typedef eastl::vec_s0083_b810<cArgInfo_s0083_b810>  VecArgInfo_s0083_b810;
typedef eastl::vec_s0083_b810<cEnumSpec_s0083_b810> VecEnumSpec_s0083_b810;
struct cOptionsSpec_s0083_b810 {
    eastl::string8_s0083_b810 mName;            // +0x00
    eastl::string8_s0083_b810 mDescription;     // +0x10
    VecArgInfo_s0083_b810     mArguments;       // +0x20
    int            mPad30;           // +0x30
    int            mFlagToSet;       // +0x34
    cOptionsSpec_s0083_b810() {}
    cOptionsSpec_s0083_b810(const cOptionsSpec_s0083_b810& x);              // 0x00839e00
    cOptionsSpec_s0083_b810& operator=(const cOptionsSpec_s0083_b810& x);   // 0x0083a8b0
    ~cOptionsSpec_s0083_b810();
};
struct cArguments_s0083_b810 {
    eastl::vec_s0083_b810<char>              mArgStorage;
    eastl::vec_s0083_b810<char*>             mArguments;
    eastl::vec_s0083_b810<cOptionArgInfo>    mOptionArguments;
    int                           mMainArgumentsStart;
    int                           mNumMainArguments;
    cArguments_s0083_b810();                       // 0x00837ff0
    ~cArguments_s0083_b810();
    void SplitIntoArguments(const char* s);   // 0x008383c0
    int  NumArguments();                      // 0x00837f30
    char* operator[](int i);                  // 0x00837f20
};
struct VecOptions {
    cOptionsSpec_s0083_b810* mpBegin; cOptionsSpec_s0083_b810* mpEnd; cOptionsSpec_s0083_b810* mpCapacity;
    eastl::sp_vector_allocator_s0083_b810 mAllocator;
    void DoInsertValue(cOptionsSpec_s0083_b810* pos, const cOptionsSpec_s0083_b810& v);      // 0x0083baa0
    cOptionsSpec_s0083_b810* erase(cOptionsSpec_s0083_b810* first, cOptionsSpec_s0083_b810* last);      // 0x0083ba40
    void DestroyRangeA(cOptionsSpec_s0083_b810* first, cOptionsSpec_s0083_b810* last);       // 0x0076e7a0
    void push_back(const cOptionsSpec_s0083_b810& v);                             // 0x0083bc50
    void clear() { erase(mpBegin, mpEnd); }
};
typedef VecOptions VecOptionsSpec_s0083_b810;
struct cArgumentSpec_s0083_b810 {
    eastl::string8_s0083_b810 mCommandName;        // +0x00
    eastl::string8_s0083_b810 mBriefDescription;   // +0x10
    eastl::string8_s0083_b810 mFullDescription;    // +0x20
    VecArgInfo_s0083_b810     mDefaultArguments;   // +0x30
    char pad40[0x4];                    // +0x40
    VecOptionsSpec_s0083_b810 mOptions;            // +0x44
    char pad54[0x4];                    // +0x54
    VecEnumSpec_s0083_b810    mEnumSpecs;          // +0x58
    char pad64[0x4];                    // +0x64
    bool           mRespectHelp;        // +0x6c
    int            mFlags;              // +0x70
    cArguments_s0083_b810     mVectorArgs;         // +0x74
    char padac[0xb8 - 0xac];
    eastl::string8_s0083_b810 mErrorString;        // +0xb8

    cArgumentSpec_s0083_b810(bool respectHelp);                                       // 0x0083a9f0
    int  Parse(int argc, const char** argv, ArgParser* p);                 // 0x0083b810
    int  ParseVectorArgument(cArgInfo_s0083_b810* ai, const char* str);
    int  ParseVectorArgument(cArgInfo_s0083_b810* ai, const char* str, ArgParser* p);
    int  ParseArgument(cArgInfo_s0083_b810* ai, const char* str);  // 0x0083afc0 (cArgumentSpec::ParseArgument)
    int  ParseArgumentEx(cArgInfo_s0083_b810* ai, const char* str, ArgParser* p);  // 0x0083b1d0 (cArgumentSpec::ParseArgumentEx)
    int  ParseOptionArgs(cOptionsSpec_s0083_b810* opt, int** ppArgs, const char** ppEnd, ArgParser* p);  // 0x0083b580 (cArgumentSpec::ParseOptionArgs)
    int  ParseOption(int** ppArgs, const char** ppEnd, ArgParser* p);  // 0x0083b6d0 (cArgumentSpec::ParseOption)
    void CreateHelpString(const char* name, eastl::string8_s0083_b810* out, int style);  // 0x00839f90
    void FindNameAndTypeFromOption(const eastl::string8_s0083_b810& word, int& type, eastl::string8_s0083_b810& name);  // 0x00839540
    int  ConstructSpec(const char* name, const char* spec, ...);           // 0x0083bcd0
    void ParseThrowing(int argc, const char** argv, ArgParser* p);         // 0x0083b9d0
};
void __cdecl Sprintf(eastl::string8_s0083_b810* out, const char* fmt, ...);   // 0x00840c20
void __cdecl FUN_00837f80(int* out, const void* p);                // 0x00837f80
void __cdecl FUN_00837f60();                                       // 0x00837f60
cOptionsSpec_s0083_b810* __cdecl CopyOptionsRange(cOptionsSpec_s0083_b810* first, cOptionsSpec_s0083_b810* last, cOptionsSpec_s0083_b810* result);     // 0x0083a900
struct cError { cError(const char* s); };
template <> void eastl::vec_s0083_b810<cEnumSpec_s0083_b810>::push_back(const cEnumSpec_s0083_b810& value);   // 0x0083a830
// ---- items of slice s0083b810 end

// @ 0x00838760
bool StrEqualI(const char* a, const char* b)
{
    return _stricmp(a, b) == 0;
}





// @ 0x00838780
bool StrNEqualI(const char* a, const char* b, unsigned int n)
{
    return _strnicmp(a, b, n) == 0;
}





// @ 0x008387a0
bool StrEqualI2(const char** p, const char* b)
{
    return _stricmp(*p, b) == 0;
}




// @ 0x008389f0
RawStr::RawStr(const RawStr& s, uint32_t pos, uint32_t n)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    uint32_t rem = (uint32_t)(s.mpEnd - s.mpBegin) - pos;
    const uint32_t& cnt = min_alt(rem, n);
    char* src = s.mpBegin + pos;
    char* end = src + cnt;
    uint32_t len = (uint32_t)(end - src);
    RangeInitialize(len + 1);
    char* dst = mpBegin;
    DoInsertValue(dst, src, len);
    mpEnd = dst + len;
    *mpEnd = 0;
}




// @ 0x00838a60
int RawStr::Find(const char* p, uint32_t pos)
{
    const char* e = p;
    while (*e) ++e;
    char* begin = mpBegin;
    char* end = mpEnd;
    if (pos < (uint32_t)(end - begin)) {
        char* r = SearchStr(begin + pos, end, (void*)p, (void*)e);
        if (r != end) return (int)(r - begin);
    }
    return -1;
}




// @ 0x00838ab0
Ent* Ent::CopyFrom(const Ent* src)
{
    Ent* dst = this;
    dst->field0 = src->field0;
    dst->name.mpBegin = 0;
    dst->name.mpEnd = 0;
    dst->name.mpCapacity = 0;
    uint32_t size = (uint32_t)(src->name.mpEnd - src->name.mpBegin);
    dst->name.RangeInitialize(size + 1);
    char* dstp = dst->name.mpBegin;
    DoInsertValue(dstp, src->name.mpBegin, size);
    dst->name.mpEnd = dstp + (src->name.mpEnd - src->name.mpBegin);
    *dst->name.mpEnd = 0;
    dst->field14 = src->field14;
    dst->field18 = src->field18;
    dst->field1c = src->field1c;
    return dst;
}




// @ 0x00838b90
Vec2* CopyVec2(Vec2* first, Vec2* last, Vec2* dst)
{
    if (first != last) {
        int off = (int)((char*)first - (char*)dst);
        do {
            if (dst) *dst = *(Vec2*)(off + (char*)dst);
            ++dst;
        } while ((Vec2*)(off + (char*)dst) != last);
    }
    return dst;
}




// @ 0x00838de0
void FUN_00838de0(RawStr* p, uint32_t pos, uint32_t n)
{
    char* begin = p->mpBegin;
    uint32_t rem = (uint32_t)(p->mpEnd - begin) - pos;
    const uint32_t& cnt = min_alt(rem, n);
    p->Assign(begin + pos, begin + pos + cnt);
}




// @ 0x00838e80
Ent* DestroyEnts(Ent* first, Ent* last, Ent* dst)
{
    if (first != last) {
        do {
            char* b = first->name.mpBegin;
            if ((first->name.mpCapacity - b) > 1 && b) operator_delete__(b);
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}




// @ 0x00838f20
Ent* CopyEntsFwd(Ent* first, Ent* last, Ent* dst)
{
    if (first != last) {
        do {
            dst->field0 = first->field0;
            if (&first->name != &dst->name) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field14 = first->field14;
            dst->field18 = first->field18;
            dst->field1c = first->field1c;
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}




// @ 0x00838f80
Ent* CopyEntsBwd(Ent* first, Ent* last, Ent* dst)
{
    if (first != last) {
        do {
            first -= 1;
            dst -= 1;
            dst->field0 = first->field0;
            if (&first->name != &dst->name) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field14 = first->field14;
            dst->field18 = first->field18;
            dst->field1c = first->field1c;
        } while (first != last);
    }
    return dst;
}




// @ 0x00838ff0
Ent2* CopyEnts2Fwd(Ent2* first, Ent2* last, Ent2* dst)
{
    if (first != last) {
        do {
            if (first != dst) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field10 = first->field10;
            dst->field14 = first->field14;
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}




// @ 0x00839040
Ent2* CopyEnts2Bwd(Ent2* first, Ent2* last, Ent2* dst)
{
    if (first != last) {
        do {
            first -= 1;
            dst -= 1;
            if (first != dst) dst->name.Assign(first->name.mpBegin, first->name.mpEnd);
            dst->field10 = first->field10;
            dst->field14 = first->field14;
        } while (first != last);
    }
    return dst;
}



// @ 0x00839950
VecArgInfo::VecArgInfo(const VecArgInfo& x)
{
    DoAllocate((unsigned)(x.mpEnd - x.mpBegin), x.mAllocator);
    cArgInfo* pEnd = x.mpBegin;
    UninitCopyArgEH(&pEnd, x.mpBegin, x.mpEnd, mpBegin, &x);
    mpEnd = pEnd;
}



// @ 0x008399d0
void V8::DoInsertValue(E8* pos, const E8& v)
{
    if (mpEnd != mpCapacity) {
        const E8* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) E8(*(mpEnd - 1));
        E8* d = mpEnd;
        E8* s = mpEnd - 1;
        while (s != pos) { --s; --d; *d = *s; }
        *pos = *pv;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        E8* nb = n ? (E8*)EASTL_allocator_allocate(n * 8, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        E8* np = UninitCopy8(mpBegin, pos, nb);
        if (np) ::new((void*)np) E8(v);
        E8* ne = UninitCopy8(pos, mpEnd, np + 1);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = ne; mpCapacity = nb + n;
    }
}



// @ 0x00839ae0
void V16::DoInsertValue(E16* pos, const E16& v)
{
    if (mpEnd != mpCapacity) {
        const E16* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) E16(*(mpEnd - 1));
        CopyBackward16(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        E16* nb = n ? (E16*)EASTL_allocator_allocate(n * 16, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        E16* beg = mpBegin;
        E16* np = UninitCopy16(beg, pos, nb);
        if (np) ::new((void*)np) E16(v);
        E16* end = mpEnd;
        ++np;
        np = UninitCopy16(pos, end, np);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = np; mpCapacity = nb + n;
    }
}



// @ 0x00839c00
void cArgumentSpec::AddArgDocs(eastl::string8_s0083_9950* out, VecArgInfo* args, int style)
{
    int nDependents = 0;
    if (style == 2)
        out->append("<i>", "<i>" + 3);
    for (int i = 0; i < (int)(args->mpEnd - args->mpBegin); ++i) {
        cArgInfo* a = &args->mpBegin[i];
        if (i != 0)
            out->append(" ", " " + 1);
        if (!a->mIsDependent) {
            out->append("[", "[" + 1);
            ++nDependents;
        }
        if (style == 2)
            out->append("&lt;", "&lt;" + 4);
        else
            out->append("<", "<" + 1);
        if (a->mName.mpBegin != a->mName.mpEnd)
            SprintfAppend(out, "%s:", a->mName.mpBegin);
        NameFromArgType(a->mType, out);
        if (style == 2)
            out->append("&gt;", "&gt;" + 4);
        else
            out->append(">", ">" + 1);
        if (a->mType & 0x8000)
            out->append(" ...", " ..." + 4);
    }
    while (nDependents > 0) {
        out->append("]", "]" + 1);
        --nDependents;
    }
    if (style == 2)
        out->append("</i>", "</i>" + 4);
    out->append("\n", "\n" + 1);
}



// @ 0x00839d80
void V8::push_back(const E8& v)
{
    if (mpEnd < mpCapacity) {
        ::new((void*)mpEnd++) E8(v);
    } else {
        DoInsertValue(mpEnd, v);
    }
}



// @ 0x00839dc0
void V16::push_back(const E16& v)
{
    if (mpEnd < mpCapacity) {
        ::new((void*)mpEnd++) E16(v);
    } else {
        DoInsertValue(mpEnd, v);
    }
}



// @ 0x00839f90
void cArgumentSpec::CreateHelpString(const char* name, eastl::string8_s0083_9950* out, int style)
{
    if (style == 0) {
        Sprintf(out, "%s", mBriefDescription.mpBegin);
        return;
    }
    if (style == 2) {
        Sprintf(out, "<tr><td><a name=\"%s\"></a><b>%s</b> ", name, name);
    } else {
        const char* p = name;
        while (*p) ++p;
        out->assign(name, p);
        out->append(" ", " " + 1);
    }

    AddArgDocs(out, &mDefaultArguments, style);

    if (style == 2) {
        out->append("<br><blockquote><p>", "<br><blockquote><p>" + 18);
        AddDocString(out, "", mFullDescription);
        SprintfAppend(out, " Options:</p>");
    } else {
        AddDocString(out, "    ", mFullDescription);
        SprintfAppend(out, "\n    Options:\n");
    }

    int nOptions = (int)(mOptions.mpEnd - mOptions.mpBegin);
    for (int i = 0; i < nOptions; ++i) {
        cOptionsSpec* opt = &mOptions.mpBegin[i];
        if (style == 2)
            SprintfAppend(out, "<b>-%s</b> ", opt->mName.mpBegin);
        else
            SprintfAppend(out, "    -%s ", opt->mName.mpBegin);
        AddArgDocs(out, &opt->mArguments, style);
        if (style == 2) {
            out->append("<br><blockquote>", "<br><blockquote>" + 15);
            AddDocString(out, "", opt->mDescription);
            out->append("</blockquote>", "</blockquote>" + 13);
        } else {
            AddDocString(out, "        ", opt->mDescription);
        }
    }

    if (mEnumSpecs.mpBegin != mEnumSpecs.mpEnd) {
        if (style == 2)
            out->append("\n<p>Types:</p>", "\n<p>Types:</p>" + 14);
        AddEnumDocs(out, "    ", &mEnumSpecs, style);
    }
    if (style == 2)
        out->append("</blockquote></td></tr>", "</blockquote></td></tr>" + 21);
}



// @ 0x0083a2f0
const char* cArgumentSpec::HelpString(const char* name, int style)
{
    CreateHelpString(name, &mErrorString, style);
    return mErrorString.mpBegin;
}



// @ 0x0083a310
cOptionsSpec* __cdecl DestroyOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* result)
{
    if (first != last) {
        do {
            cArgInfo* end = first->mArguments.mpEnd;
            for (cArgInfo* p = first->mArguments.mpBegin; p < end; ++p) {
                if ((p->mName.mpCapacity - p->mName.mpBegin) > 1 && p->mName.mpBegin)
                    EASTL_allocator_deallocate(p->mName.mpBegin);
            }
            if (first->mArguments.mpBegin && ((int*)first->mArguments.mpBegin)[-1])
                EASTL_allocator_deallocate(first->mArguments.mpBegin);
            if ((first->mDescription.mpCapacity - first->mDescription.mpBegin) > 1 && first->mDescription.mpBegin)
                EASTL_allocator_deallocate(first->mDescription.mpBegin);
            if ((first->mName.mpCapacity - first->mName.mpBegin) > 1 && first->mName.mpBegin)
                EASTL_allocator_deallocate(first->mName.mpBegin);
            ++first;
            ++result;
        } while (first != last);
        return result;
    }
    return result;
}



// @ 0x0083a3c0
void VecArgInfo::DoInsertValue(cArgInfo* pos, const cArgInfo& v)
{
    if (mpEnd != mpCapacity) {
        const cArgInfo* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) cArgInfo(*(mpEnd - 1));
        CopyBackwardArg(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        cArgInfo* nb = n ? (cArgInfo*)EASTL_allocator_allocate(n * 0x20, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        cArgInfo* np = UninitCopyArg(mpBegin, pos, nb);
        UninitDestroyArg(mpBegin, pos, nb);
        if (np) ::new((void*)np) cArgInfo(v);
        cArgInfo* ne = UninitCopyArg(pos, mpEnd, np + 1);
        UninitDestroyArg(pos, mpEnd, np + 1);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = ne; mpCapacity = nb + n;
    }
}



// @ 0x0083a580
void VecEnumSpec::DoInsertValue(cEnumSpec* pos, const cEnumSpec& v)
{
    if (mpEnd != mpCapacity) {
        const cEnumSpec* pv = &v;
        if (pv >= pos && pv < mpEnd) ++pv;
        if (mpEnd) ::new((void*)mpEnd) cEnumSpec(*(mpEnd - 1));
        CopyBackwardEnum(pos, mpEnd - 1, mpEnd);
        if (pos != pv) pos->mName.assign(pv->mName.mpBegin, pv->mName.mpEnd);
        pos->mEnumInfo = pv->mEnumInfo;
        pos->mPad14 = pv->mPad14;
        ++mpEnd;
    } else {
        unsigned cnt = (unsigned)(mpEnd - mpBegin);
        unsigned n = cnt > 0 ? 2 * cnt : 1;
        cEnumSpec* nb = n ? (cEnumSpec*)EASTL_allocator_allocate(n * 0x18, g_allocName, 0, 0, g_allocFile, 0xd1) : 0;
        cEnumSpec* np = UninitCopyEnum(mpBegin, pos, nb);
        UninitDestroyEnum(mpBegin, pos, nb);
        if (np) ::new((void*)np) cEnumSpec(v);
        cEnumSpec* ne = UninitCopyEnum(pos, mpEnd, np + 1);
        UninitDestroyEnum(pos, mpEnd, np + 1);
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
        mpBegin = nb; mpEnd = ne; mpCapacity = nb + n;
    }
}



// @ 0x0083a740
VecArgInfo& VecArgInfo::operator=(const VecArgInfo& x)
{
    if (&x != this) {
        unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCapacity - mpBegin)) {
            cArgInfo* p = DoAllocateCopy(n, x.mpBegin, x.mpEnd);
            FreeRange(mpBegin, mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
            mpBegin = p; mpEnd = p + n; mpCapacity = p + n;
        } else if (n > (unsigned)(mpEnd - mpBegin)) {
            unsigned m = (unsigned)(mpEnd - mpBegin);
            MoveArgRange(x.mpBegin, x.mpBegin + m, mpBegin);
            cArgInfo* tmp = 0;
            UninitCopyArgEH(&tmp, x.mpBegin + m, x.mpEnd, mpEnd, &x);
            mpEnd = mpBegin + n;
        } else {
            cArgInfo* q = MoveArgRange(x.mpBegin, x.mpEnd, mpBegin);
            FreeRange(q, mpEnd);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}



// @ 0x0083a8b0
cOptionsSpec& cOptionsSpec::operator=(const cOptionsSpec& x)
{
    if (this != &x)
        mName.assign(x.mName.mpBegin, x.mName.mpEnd);
    if (&mDescription != &x.mDescription)
        mDescription.assign(x.mDescription.mpBegin, x.mDescription.mpEnd);
    mArguments = x.mArguments;
    mFlagToSet = x.mFlagToSet;
    return *this;
}



// @ 0x0083a900
cOptionsSpec* __cdecl CopyOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* result)
{
    if (first != last) {
        do {
            if (first != result)
                result->mName.assign(first->mName.mpBegin, first->mName.mpEnd);
            if (&first->mDescription != &result->mDescription)
                result->mDescription.assign(first->mDescription.mpBegin, first->mDescription.mpEnd);
            result->mArguments = first->mArguments;
            result->mFlagToSet = first->mFlagToSet;
            ++result, ++first;
        } while (first != last);
        return result;
    }
    return result;
}



// @ 0x0083a970
cOptionsSpec* __cdecl CopyBackwardOptionsRange(cOptionsSpec* first, cOptionsSpec* last, cOptionsSpec* resultEnd)
{
    if (last != first) {
        do {
            last = (cOptionsSpec*)((char*)last - 0x38);
            resultEnd = (cOptionsSpec*)((char*)resultEnd - 0x38);
            if (last != resultEnd)
                resultEnd->mName.assign(last->mName.mpBegin, last->mName.mpEnd);
            if (&last->mDescription != &resultEnd->mDescription)
                resultEnd->mDescription.assign(last->mDescription.mpBegin, last->mDescription.mpEnd);
            resultEnd->mArguments = last->mArguments;
            resultEnd->mFlagToSet = last->mFlagToSet;
        } while (last != first);
        return resultEnd;
    }
    return resultEnd;
}


// @ 0x0083a9f0
EA::ArgScript::cArgumentSpec::cArgumentSpec(bool respectHelp)

: mCommandName(), mBriefDescription(), mFullDescription(), mDefaultArguments(), mOptions(), mEnumSpecs(), mRespectHelp(respectHelp), mFlags(0), mVectorArgs(), mErrorString() {
}


// @ 0x0083aaa0
int cArgumentSpec_s0083_a9f0::ParseVectorArgument(cArgInfo_s0083_a9f0* ai, const char* str)
{
    switch (ai->mType & 0x3fff) {
    case 1:
        if (ai->mLocation) {
            bool b = atol(str) != 0;
            PushByteVec((eastl::vec_s0083_a9f0<char>*)ai->mLocation, (const char*)&b);
        }
        return 0;
    case 2:
        if (ai->mLocation) {
            uint32 v = (uint32)atol(str);
            PushUIntVec((eastl::vec_s0083_a9f0<uint32>*)ai->mLocation, &v);
        }
        return 0;
    case 3:
        if (ai->mLocation) {
            float v = ParseFloatStr(str);
            PushFloatVec((eastl::vec_s0083_a9f0<float>*)ai->mLocation, &v);
        }
        return 0;
    case 4:
        if (ai->mLocation) {
            double v = ParseFloatStr(str);
            PushDoubleVec((eastl::vec_s0083_a9f0<double>*)ai->mLocation, &v);
        }
        return 0;
    case 5:
        if (ai->mLocation)
            PushCStringVec((eastl::vec_s0083_a9f0<const char*>*)ai->mLocation, &str);
        return 0;
    case 6:
        if (ai->mLocation) {
            eastl::string8_s0083_a9f0 tmp;
            tmp.assign(str);
            PushStringVec((eastl::vec_s0083_a9f0<eastl::string8_s0083_a9f0>*)ai->mLocation, &tmp);
        }
        return 0;
    }
    Sprintf(&mErrorString, "Unknown vector arg type %d", ai->mType);
    return 4;
}


// @ 0x0083ac80
int cArgumentSpec_s0083_a9f0::ParseVectorArgument(cArgInfo_s0083_a9f0* ai, const char* str, ArgParser* p)
{
    switch (ai->mType & 0x3fff) {
    case 1:
        if (ai->mLocation && p) {
            bool b = PBool(p, str);
            PushByteVec((eastl::vec_s0083_a9f0<char>*)ai->mLocation, (const char*)&b);
        }
        return 0;
    case 2:
        if (ai->mLocation && p) {
            uint32 v = (uint32)PInt(p, str);
            PushUIntVec((eastl::vec_s0083_a9f0<uint32>*)ai->mLocation, &v);
        }
        return 0;
    case 3:
        if (ai->mLocation && p) {
            float v = (float)PFloat(p, str);
            PushFloatVec((eastl::vec_s0083_a9f0<float>*)ai->mLocation, &v);
        }
        return 0;
    case 4:
        if (ai->mLocation && p) {
            double v = (double)PFloat(p, str);
            PushDoubleVec((eastl::vec_s0083_a9f0<double>*)ai->mLocation, &v);
        }
        return 0;
    case 5:
        if (ai->mLocation)
            PushCStringVec((eastl::vec_s0083_a9f0<const char*>*)ai->mLocation, &str);
        return 0;
    case 6:
        if (ai->mLocation) {
            eastl::string8_s0083_a9f0 tmp;
            tmp.assign(str);
            PushStringVec((eastl::vec_s0083_a9f0<eastl::string8_s0083_a9f0>*)ai->mLocation, &tmp);
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
            PushVec3((eastl::vec_s0083_a9f0<unsigned>*)ai->mLocation, r);
        }
        return 0;
    case 9:
        if (ai->mLocation && p) {
            unsigned out[4];
            void* r = PVec4(p, out, str);
            PushVec4((eastl::vec_s0083_a9f0<unsigned>*)ai->mLocation, r);
        }
        return 0;
    case 10:
        if (ai->mLocation && p) {
            unsigned out[3];
            void* r = PColor3(p, out, str);
            PushVec3((eastl::vec_s0083_a9f0<unsigned>*)ai->mLocation, r);
        }
        return 0;
    case 11:
        if (ai->mLocation && p) {
            unsigned out[4];
            void* r = PColor4(p, out, str);
            PushVec4((eastl::vec_s0083_a9f0<unsigned>*)ai->mLocation, r);
        }
        return 0;
    }
    Sprintf(&mErrorString, "Unknown vector arg type %d", ai->mType);
    return 4;
}


// @ 0x0083afc0
int cArgumentSpec_s0083_a9f0::ParseArgument(cArgInfo_s0083_a9f0* ai, const char* str)
{
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
        if (ai->mLocation) ((eastl::string8_s0083_a9f0*)ai->mLocation)->assign(str);
        return 0;
    }
    if (type >= 0xc) {
        unsigned n = (unsigned)(mEnumSpecs.mpEnd - mEnumSpecs.mpBegin);
        if (type - 0xc < n) {
            cEnumSpec_s0083_a9f0* es = &mEnumSpecs.mpBegin[type - 0xc];
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


// @ 0x0083b1d0
int cArgumentSpec_s0083_a9f0::ParseArgumentEx(cArgInfo_s0083_a9f0* ai, const char* str, ArgParser* p)
{
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
        if (ai->mLocation) ((eastl::string8_s0083_a9f0*)ai->mLocation)->assign(str);
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
            cEnumSpec_s0083_a9f0* es = &mEnumSpecs.mpBegin[type - 0xc];
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


// @ 0x0083b580
int cArgumentSpec_s0083_a9f0::ParseOptionArgs(cOptionsSpec_s0083_a9f0* opt, int** ppArgs, const char** ppEnd, ArgParser* p)
{
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


// @ 0x0083b6d0
int cArgumentSpec_s0083_a9f0::ParseOption(int** ppArgs, const char** ppEnd, ArgParser* p)
{
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

// @ 0x0083b810
int cArgumentSpec_s0083_b810::Parse(int argc, const char** argv, ArgParser* p)
{
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
            cArgInfo_s0083_b810* ai = &mDefaultArguments.mpBegin[i];
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
        cArgInfo_s0083_b810* ai = &mDefaultArguments.mpBegin[nUsed];
        if (ai->mIsDependent && (ai->mType & 0x8000) == 0) {
            mErrorString.assign("Not enough arguments");
            return 2;
        }
    }
    return 0;
}

// @ 0x0083b9d0
void cArgumentSpec_s0083_b810::ParseThrowing(int argc, const char** argv, ArgParser* p)
{
    int n = 0;
    FUN_00837f80(&n, &argc);
    FUN_00837f60();
    int r = Parse(n, argv, p);
    if (r != 0) {
        cError err(mErrorString.mpBegin);
        _CxxThrowException(&err, (_ThrowInfo*)&__TI1_cError);
    }
}

// @ 0x0083ba40
cOptionsSpec_s0083_b810* VecOptions::erase(cOptionsSpec_s0083_b810* first, cOptionsSpec_s0083_b810* last)
{
    cOptionsSpec_s0083_b810* newEnd = CopyOptionsRange(last, mpEnd, first);
    DestroyRangeA(newEnd, mpEnd);
    mpEnd -= (last - first);
    return first;
}
