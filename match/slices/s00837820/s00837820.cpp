// Slice s00837820 (w2g7 #40), 32-bit MSVC 2008 SP1.
// EA::ArgScript::cArguments plus cDataURI stream helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
__declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
__declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, unsigned int);
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
};

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
void cArguments::SplitIntoArguments(const char* text) { (void)text; }
cArguments::cArguments(int text) { (void)text; }

void FUN_00838350(int self, void* vec) { (void)self; (void)vec; }
int  FUN_00837820(int* self) { (void)self; return 0; }
int  FUN_00837c90(int self, int msg) { (void)self; (void)msg; return 0; }
