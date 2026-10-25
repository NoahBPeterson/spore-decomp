// Slice s00837820 (w2g7 #40), 32-bit MSVC 2008 SP1.
// EA::ArgScript::cArguments plus cDataURI stream helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);  // 0x00f473a0
void  __cdecl operator_delete__(void*);                                          // 0x00f47380
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
__declspec(noreturn) void __cdecl CxxThrow(void*, void*);                  // 0x011e0912 _CxxThrowException
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
    void  GatherUnprocessed(void* outList);            // 0x838350
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
    if (n < min) {
        cError err("Expecting at least %d arguments", min);
        CxxThrow(&err, (void*)0x14f9174);
    }
    if (n > max) {
        cError err("Expecting at most %d arguments", max);
        CxxThrow(&err, (void*)0x14f9174);
    }
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
                if (it->mNumArguments != 0) {
                    cError err("Not expecting any arguments for option '%s'", label);
                    CxxThrow(&err, (void*)0x14f9174);
                }
                it->mProcessed = true;
                return true;
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
                if (n < min) {
                    cError err("Expecting at least %d arguments for option '%s'", min, label);
                    CxxThrow(&err, (void*)0x14f9174);
                }
                if (n > max) {
                    cError err("Expecting at most %d arguments for option '%s'", max, label);
                    CxxThrow(&err, (void*)0x14f9174);
                }
                if (count) *count = n;
                it->mProcessed = true;
                return (char**)mArguments.mpBegin + it->mFirstArgumentIndex;
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

// @ 0x00838350
void cArguments::GatherUnprocessed(void* outList) {
    sp_vector<const char*>* out = (sp_vector<const char*>*)outList;
    out->clear();
    for (cOptionArgInfo* it = mOptionArguments.mpBegin; it != mOptionArguments.mpEnd; ++it) {
        if (!it->mProcessed) out->push_back(it->mName);
    }
}

// ---------------------------------------------------------------------------
// data: URI -> memory stream, and the XHTML handler that dispatches it.
// ---------------------------------------------------------------------------
extern "C" char gEmptyString8[];               // 0x01667bac
extern "C" const wchar_t* g_01548788;          // 0x01548788
// stream-name tag (0x013ebacc) and allocation name (0x0141b14c) are immediate constants.

struct MemoryStream {
    virtual void v00();
    virtual void AddRef();                              // +0x04
    virtual void Release();                             // +0x08
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28(int, int);                         // +0x28
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void Write(const void* data, unsigned size); // +0x38
    MemoryStream* Construct(void* a, void* b, const char* name);  // 0x0093c270
    void SetOption(int opt, float value);               // 0x0093bb40
};

// The percent-decoding target: an SSO wide string with a 256-character buffer.
struct WideString256 {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    uint32_t mAllocator;   // +0x0c
    wchar_t* mpBuffer;     // +0x10
    wchar_t  mData[256];   // +0x14

    WideString256() {
        wchar_t* b = mData;
        mpBegin = b;
        mpEnd = b;
        mpCapacity = b + 256;
        mAllocator = 0;
        mpBuffer = b;
        *b = 0;
    }
    ~WideString256() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2) && mpBegin && mpBegin != mpBuffer)
            operator_delete__(mpBegin);
    }
    void set_capacity(unsigned n);                       // 0x004c29c0
    void append(unsigned n, wchar_t c);                  // 0x004c1ff0
};

// Heap-allocated eastl::basic_string<char> (base64 staging buffers).
struct CharString {
    char*    mpBegin;      // +0x00
    char*    mpEnd;        // +0x04
    char*    mpCapacity;   // +0x08
    uint32_t mAllocator;   // +0x0c

    CharString() {
        mpBegin = gEmptyString8;
        mpEnd = gEmptyString8;
        mpCapacity = gEmptyString8 + 1;
        mAllocator = 0;
    }
    ~CharString() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin) operator_delete__(mpBegin);
    }
    void set_capacity(unsigned n);                       // 0x0047d240
    void append(const char* first, const char* last);    // 0x00455d60
};

bool __cdecl Base64DecodeString(int* src, int* dst);     // 0x00941af0

// cDataURI's two SSO wide strings (32-char scheme/mediatype, 1024-char value).
template <int N>
struct WideFixed {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wchar_t* mpBuffer;
    wchar_t  mData[N];
};

struct cDataURI {
    int             mEncoding;   // +0x00
    WideFixed<32>   mScheme;     // +0x04
    WideFixed<1024> mValue;      // +0x58
    bool            mbBase64;    // +0x86c

    cDataURI(const wchar_t* p);  // 0x008371e0
    ~cDataURI() {
        if ((((int)((char*)mValue.mpCapacity - (char*)mValue.mpBegin) & -2) > 2) &&
            mValue.mpBegin && mValue.mpBegin != mValue.mpBuffer)
            operator_delete__(mValue.mpBegin);
        if ((((int)((char*)mScheme.mpCapacity - (char*)mScheme.mpBegin) & -2) > 2) &&
            mScheme.mpBegin && mScheme.mpBegin != mScheme.mpBuffer)
            operator_delete__(mScheme.mpBegin);
    }
    bool GetStream(void** out);
};

static inline unsigned HexVal(wchar_t c) {
    if (c >= L'0' && c <= L'9') return (unsigned)(c - L'0');
    if (c >= L'A' && c <= L'F') return (unsigned)(c - 0x37);
    if (c >= L'a' && c <= L'f') return (unsigned)(c - 0x57);
    return 0;
}

// @ 0x00837820
bool cDataURI::GetStream(void** out) {
    if (mValue.mpBegin == mValue.mpEnd) return false;

    WideString256 decoded;
    unsigned need = (unsigned)(mValue.mpEnd - mValue.mpBegin) + 1;
    if (need > 256) decoded.set_capacity(need);

    bool utf16 = (mEncoding == 0x10 && !mbBase64);
    const wchar_t* p = mValue.mpBegin;
    const wchar_t* end = mValue.mpEnd;
    while (p < end) {
        wchar_t ch = *p++;
        if (ch == L'%') {
            unsigned v;
            if (utf16) {
                v  = HexVal(p[0]) << 12; ++p;
                v |= HexVal(p[0]) << 8;  ++p;
                v |= HexVal(p[0]) << 4;  ++p;
                v |= HexVal(p[0]);       ++p;
            } else {
                v  = HexVal(p[0]) << 4;  ++p;
                v |= HexVal(p[0]);       ++p;
            }
            decoded.append(1, (wchar_t)v);
        } else {
            decoded.append(1, ch);
        }
    }

    MemoryStream* stream = 0;
    void* mem = operator_new6(0x24, (const void*)0x141b14c, 0, 0, 0, 0);
    if (mem) {
        stream = ((MemoryStream*)mem)->Construct(0, 0, (const char*)0x13ebacc);
        if (stream) stream->AddRef();
    }
    stream->SetOption(1, 1.0f);

    if (mbBase64) {
        CharString encoded;
        unsigned n = (unsigned)(decoded.mpEnd - decoded.mpBegin) + 1;
        if (n > 1) encoded.set_capacity(n);
        const wchar_t* q = decoded.mpBegin;
        const wchar_t* qe = decoded.mpEnd;
        while (q < qe) {
            char buf[0x40];
            int i = 0;
            while (q < qe && i < 0x40) {
                buf[i++] = (char)*q;
                ++q;
            }
            encoded.append(buf, buf + i);
        }
        CharString plain;
        if (!Base64DecodeString((int*)&encoded, (int*)&plain)) {
            if (stream) stream->Release();
            return false;
        }
        stream->Write(plain.mpBegin, (unsigned)(plain.mpEnd - plain.mpBegin));
    } else if (mEncoding == 0x10) {
        stream->Write(decoded.mpBegin, (unsigned)(decoded.mpEnd - decoded.mpBegin) * 2);
    } else {
        const wchar_t* q = decoded.mpBegin;
        const wchar_t* qe = decoded.mpEnd;
        while (q < qe) {
            char buf[0x40];
            int i = 0;
            while (q < qe && i < 0x40) {
                buf[i++] = (char)*q;
                ++q;
            }
            buf[i] = 0;
            stream->Write(buf, (unsigned)i);
        }
    }

    stream->v28(0, 0);
    *out = stream;
    stream->AddRef();
    stream->Release();
    return true;
}

// ---------------------------------------------------------------------------
// cSPUInHandler::ProcessRequest
// ---------------------------------------------------------------------------
// Fixed 32-byte char buffer used to hold the byte-sized media type.
struct CharFixed32 {
    char* a;        // +0x00 begin
    char* b;        // +0x04 end
    char* c;        // +0x08 capacity
    char* d;        // +0x0c allocator
    char* e;        // +0x10 inline buffer
    char  mData[32];// +0x14

    CharFixed32() {
        char* p = mData;
        a = p;
        b = p;
        c = p + 32;
        d = 0;
        e = p;
        *p = 0;
    }
    ~CharFixed32() {
        if ((c - a) > 1 && a && a != e) operator_delete__(a);
    }
    void Reserve2(unsigned n);                            // 0x00837230
    CharFixed32* AppendN(unsigned count, unsigned char ch); // 0x00837270
};

// The URI text: an EStr (wide fixed string, layout-compatible with eastl::basic_string).
struct EStr {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    void*    mpAlloc;      // +0x0c
    wchar_t* mpInline;     // +0x10
    wchar_t  mBuf[0x20];   // +0x14

    EStr* Construct(const wchar_t* src);                  // 0x006743f0
    unsigned find(const wchar_t* needle, unsigned pos);   // 0x00608340
    ~EStr() {
        if ((((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2) && mpBegin && mpBegin != mpInline)
            operator_delete__(mpBegin);
    }
};

struct CharAssignString {
    char*    mpBegin;
    char*    mpEnd;
    char*    mpCapacity;
    uint32_t mAllocator;
    void assign(const char* first, const char* last);     // 0x00454cb0
};

struct ResourceRequest {
    char mPad00[0x0c];
    const wchar_t* mPath;    // +0x0c
    CharAssignString mMime;  // +0x10
    void SetStream(void* stream);                         // 0x00836480
};

struct ResourceProvider {
    void FinishRequest(ResourceRequest* req, int status); // 0x008ffb40
};

struct cSPUInHandler {
    char mPad00[8];
    ResourceProvider* mProvider;   // +0x08
    bool ProcessRequest(ResourceRequest* req, int unused);
};

// @ 0x00837c90
bool cSPUInHandler::ProcessRequest(ResourceRequest* req, int unused) {
    (void)unused;
    if (!mProvider) return false;

    EStr uri;
    uri.Construct(req->mPath);
    if (uri.find(g_01548788, 0) == 0xffffffffu) {
        mProvider->FinishRequest(req, 3);
        return false;
    }

    cDataURI data(uri.mpBegin);
    void* stream = 0;
    if (!data.GetStream(&stream)) {
        if (stream) ((MemoryStream*)stream)->Release();
        mProvider->FinishRequest(req, 3);
        return false;
    }

    req->SetStream(stream);

    CharFixed32 mime;
    int n = (int)(data.mScheme.mpEnd - data.mScheme.mpBegin);
    mime.Reserve2((unsigned)n);
    for (int i = 0; i < n; ++i)
        mime.AppendN(1, (unsigned char)data.mScheme.mpBegin[i]);
    req->mMime.assign(mime.a, mime.a + strlen(mime.a));

    mProvider->FinishRequest(req, 2);
    if (stream) ((MemoryStream*)stream)->Release();
    return true;
}
