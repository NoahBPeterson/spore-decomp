// Slice s00837820 (w2g7 #40), 32-bit MSVC 2008 SP1.
// EA::ArgScript::cArguments plus cDataURI stream helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
__declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
__declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, unsigned int);
extern "C" __declspec(dllimport) int __cdecl isspace(int);
extern "C" __declspec(dllimport) int __cdecl isalpha(int);
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)
void* __cdecl EASTL_memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744
struct cOptionArgInfo;
cOptionArgInfo* __cdecl CopyOptionArgInfo(const cOptionArgInfo* first, const cOptionArgInfo* last, cOptionArgInfo* dest);   // 0x00705250
inline void CopyElems(const char** first, const char** last, const char** dest) {
    EASTL_memmove(dest, first, (unsigned)((char*)last - (char*)first));
}
inline void CopyElems(cOptionArgInfo* first, cOptionArgInfo* last, cOptionArgInfo* dest) {
    CopyOptionArgInfo(first, last, dest);
}

struct cError {
    uint32_t m0, m1, m2, m3;
    cError(const char* fmt, ...);   // 0x0052df30 (cdecl, this pushed)
    cError(const cError&);
};
void  __cdecl FUN_0092dc50(int, void*);
void  __cdecl FUN_00690b80(void*, void*);
void  __cdecl FUN_0052df30(void*, const char*, ...);
void  __cdecl CxxThrow(void*, void*);
void  __cdecl ThrowError(const char* fmt, ...);

// ---------------------------------------------------------------------------
struct cOptionArgInfo {
    char* mName;                 // +0
    int   mFirstArgumentIndex;   // +4
    int   mNumArguments;         // +8
    bool  mProcessed;            // +0xc
    char  pad[3];
};

template <class T>
struct sp_vector {
    T*   mpBegin;      // +0
    T*   mpEnd;        // +4
    T*   mpCapacity;   // +8
    char mAlloc[8];    // +0xc
    void resize(unsigned n);                       // 0x006b73e0 (char)
    void DoInsertValueP(T* pos, const T& v);       // 0x00690b80 (thiscall ret 8; pointer vector)
    void DoInsertValueO(T* pos, const T& v);       // 0x00838200 (thiscall ret 8; option vector)
    void erase(T* first, T* last) {
        CopyElems(last, mpEnd, first);
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& v) {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(this, mpEnd, v);
        }
    }
};

inline void DoInsertValue(sp_vector<const char*>* vec, const char** pos, const char* const& v) { vec->DoInsertValueP(pos, v); }
inline void DoInsertValue(sp_vector<cOptionArgInfo>* vec, cOptionArgInfo* pos, const cOptionArgInfo& v) { vec->DoInsertValueO(pos, v); }

struct cArguments {
    sp_vector<char>            mArgStorage;      // +0
    sp_vector<const char*>     mArguments;       // +0x14
    sp_vector<cOptionArgInfo>  mOptionArguments; // +0x28
    int mMainArgumentsStart;                     // +0x3c
    int mNumMainArguments;                       // +0x40

    cArguments();
    cArguments(int text);
    ~cArguments();
    void  Advance();                                   // 0x837ed0
    bool  HasArgument(const char* p);                  // 0x837ee0
    bool  HasFlag(const char* label);                  // 0x8380b0
    void  FindUnprocessed();                           // 0x837f40
    void  MarkAllProcessed();                          // 0x837f60
    void  GetArguments(int* count, char*** begin);     // 0x837f80
    __declspec(noinline) char** MainArguments(int* count, int min, int max);     // 0x838020
    char** OptionArguments(const char* label, int* count, int min, int max); // 0x838130
    void  MainArguments(int n);                        // 0x838320
    void  OptionArguments(const char* label, int n);   // 0x838330
    void  SplitIntoArguments(const char* text);        // 0x8383c0
};

// @ 0x00837ed0
void cArguments::Advance() {
    if (mNumMainArguments > 0) {
        --mNumMainArguments;
        ++mMainArgumentsStart;
    }
}

// @ 0x00837ee0
bool cArguments::HasArgument(const char* p) {
    cOptionArgInfo* it = mOptionArguments.mpBegin;
    if (it != mOptionArguments.mpEnd) {
        do {
            if (_stricmp(it->mName, p) == 0) return true;
            ++it;
        } while (it != mOptionArguments.mpEnd);
    }
    return false;
}

// @ 0x00837f40
void cArguments::FindUnprocessed() {
    for (cOptionArgInfo* it = mOptionArguments.mpBegin;
         it != mOptionArguments.mpEnd && it->mProcessed; ++it) {
    }
}

// @ 0x00837f60
void cArguments::MarkAllProcessed() {
    for (cOptionArgInfo* it = mOptionArguments.mpBegin; it != mOptionArguments.mpEnd; ++it) {
        it->mProcessed = true;
    }
}

// @ 0x00837f80
void cArguments::GetArguments(int* count, char*** begin) {
    *count = (int)(mArguments.mpEnd - mArguments.mpBegin);
    *begin = (char**)mArguments.mpBegin;
}

// @ 0x00837fa0
cArguments::~cArguments() {
    if (mOptionArguments.mpBegin && ((int*)mOptionArguments.mpBegin)[-1] != 0) {
        operator_delete__(mOptionArguments.mpBegin);
    }
    if (mArguments.mpBegin && ((int*)mArguments.mpBegin)[-1] != 0) {
        operator_delete__((void*)mArguments.mpBegin);
    }
    if (mArgStorage.mpBegin && ((int*)mArgStorage.mpBegin)[-1] != 0) {
        operator_delete__(mArgStorage.mpBegin);
    }
}

// @ 0x00837ff0
cArguments::cArguments() {
    mArgStorage.mpBegin = 0;
    mArgStorage.mpEnd = 0;
    mArgStorage.mpCapacity = 0;
    mArguments.mpBegin = 0;
    mArguments.mpEnd = 0;
    mArguments.mpCapacity = 0;
    mOptionArguments.mpBegin = 0;
    mOptionArguments.mpEnd = 0;
    mOptionArguments.mpCapacity = 0;
    mMainArgumentsStart = 0;
    mNumMainArguments = 0;
}

// @ 0x00838020
char** cArguments::MainArguments(int* count, int min, int max) {
    int n = mNumMainArguments;
    if (n < min) ThrowError("Expecting at least %d arguments", min);
    if (n > max) ThrowError("Expecting at most %d arguments", max);
    if (count) *count = n;
    if (mNumMainArguments > 0) {
        return (char**)mArguments.mpBegin + mMainArgumentsStart;
    }
    return 0;
}

// @ 0x008380b0
bool cArguments::HasFlag(const char* label) {
    cOptionArgInfo* it = mOptionArguments.mpBegin;
    if (it != mOptionArguments.mpEnd) {
        do {
            if (!it->mProcessed && _stricmp(it->mName, label) == 0) {
                if (it->mNumArguments == 0) {
                    it->mProcessed = true;
                    return true;
                }
                ThrowError("Not expecting any arguments for option '%s'", label);
            }
            ++it;
        } while (it != mOptionArguments.mpEnd);
    }
    return false;
}

// @ 0x00838130
char** cArguments::OptionArguments(const char* label, int* count, int min, int max) {
    cOptionArgInfo* it = mOptionArguments.mpBegin;
    if (it != mOptionArguments.mpEnd) {
        do {
            if (!it->mProcessed && _stricmp(it->mName, label) == 0) {
                int n = it->mNumArguments;
                if (n < min)
                    ThrowError("Expecting at least %d arguments for option '%s'", min, label);
                if (n <= max) {
                    if (count) *count = n;
                    it->mProcessed = true;
                    return (char**)mArguments.mpBegin + it->mFirstArgumentIndex;
                }
                ThrowError("Expecting at most %d arguments for option '%s'", max, label);
            }
            ++it;
        } while (it != mOptionArguments.mpEnd);
    }
    return 0;
}

// @ 0x00838320
void cArguments::MainArguments(int n) {
    MainArguments(0, n, n);
}

// @ 0x00838330
void cArguments::OptionArguments(const char* label, int n) {
    OptionArguments(label, 0, n, n);
}

// @ 0x00838740
void FUN_00838740(int arg) {
    int local;
    FUN_0092dc50(arg, &local);
}

// @ 0x00838760
bool StrEqualI(const char* a, const char* b) {
    return _stricmp(a, b) == 0;
}

// @ 0x00838780
bool StrNEqualI(const char* a, const char* b, unsigned int n) {
    return _strnicmp(a, b, n) == 0;
}

// @ 0x008387a0
bool StrEqualI2(const char** p, const char* b) {
    return _stricmp(*p, b) == 0;
}

// ---------------------------------------------------------------------------
// complex / partial bodies
// ---------------------------------------------------------------------------
// @ 0x008383c0
void cArguments::SplitIntoArguments(const char* text) {
    mArguments.clear();
    sp_vector<cOptionArgInfo>* opts = &mOptionArguments;
    opts->clear();
    mNumMainArguments = 0;
    mMainArgumentsStart = 0;
    unsigned len = strlen(text) + 1;
    if ((unsigned)(mArgStorage.mpEnd - mArgStorage.mpBegin) < len) mArgStorage.resize(len);
    char* out = mArgStorage.mpBegin;
    const char* p = text;
    for (;;) {
        while (isspace(*(unsigned char*)p)) ++p;
        if (*p == 0) return;
        bool isOption = (*p == '-');
        int depth = 0;
        const char* q = p;
        do {
            unsigned char ch = *q;
            if (ch == '"') {
                if (depth == 0 && p != q) goto done;
                do {
                    ++q;
                    if (*q == 0) throw cError("missing end quote");
                } while (*q != '"');
                if (depth == 0) goto done;
            } else if (ch == '(') {
                if (depth == 0 && p != q) goto done;
                ++depth;
            } else if (ch == ')') {
                if (depth == 0) throw cError("unexpected ')'");
                --depth;
                if (depth == 0) goto done;
            } else if (depth == 0 && isspace(ch)) {
                goto done;
            }
            ++q;
        } while (*q != 0);
        if (depth != 0) throw cError("missing ')'");
    done:
        unsigned n = q - p;
        if (*p == '"' || *p == '(') {
            ++p;
            ++q;
            --n;
        }
        if (isOption && n == 1) throw cError("option has no label");
        if (isalpha((unsigned char)p[1]) && isOption) {
            opts->push_back(cOptionArgInfo());
            cOptionArgInfo* e = mOptionArguments.mpEnd - 1;
            e->mName = out + 1;
            e->mFirstArgumentIndex = (mArguments.mpEnd - mArguments.mpBegin) + 1;
            e->mNumArguments = 0;
            e->mProcessed = false;
        } else {
            if (opts->mpBegin == opts->mpEnd)
                ++mNumMainArguments;
            else
                ++mOptionArguments.mpEnd[-1].mNumArguments;
        }
        mArguments.push_back(out);
        EASTL_memmove(out, p, n);
        out[n] = 0;
        out += n + 1;
        p = q;
    }
}
// The text constructor can throw out of SplitIntoArguments, so the vector members need their
// destructors registered for unwinding (EH frame, states 0..2). The members are modelled by
// sp_vector_d, an sp_vector with the same layout and the vector destructor inline.
template <class T>
struct sp_vector_d {
    T*   mpBegin;
    T*   mpEnd;
    T*   mpCapacity;
    char mAlloc[8];
    sp_vector_d() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector_d() {
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin);
    }
};
struct cArgumentsEH {
    sp_vector_d<char>            mArgStorage;
    sp_vector_d<const char*>     mArguments;
    sp_vector_d<cOptionArgInfo>  mOptionArguments;
    int mMainArgumentsStart;
    int mNumMainArguments;
    cArgumentsEH(int text);
};

// @ 0x008386d0
cArgumentsEH::cArgumentsEH(int text) : mMainArgumentsStart(0), mNumMainArguments(0) {
    ((cArguments*)this)->SplitIntoArguments((const char*)text);
}

void FUN_00838350(int self, void* vec) { (void)self; (void)vec; }
int  FUN_00837820(int* self) { (void)self; return 0; }
int  FUN_00837c90(int self, int msg) { (void)self; (void)msg; return 0; }
