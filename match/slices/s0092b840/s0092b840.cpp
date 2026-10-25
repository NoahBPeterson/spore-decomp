// Slice s0092b840: EA string-splitting helpers and RefPack decompression.
#include <intrin.h>
#include <ctype.h>

// EASTL empty-string sentinels (addresses relocated away by chk).
extern wchar_t gEmptyString[];          // 0x01667BAC empty string buffer
extern wchar_t gEmptyStringCapacity[];  // 0x01667BAE empty string + 2

// EASTL basic_string<wchar_t>: three pointers plus an empty allocator member,
// which pads the object to 16 bytes (the vector's element stride).
struct WString {
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    char mAllocator;        // +0x0c (empty allocator, padding)
    WString() : mpBegin(gEmptyString), mpEnd(gEmptyString),
                mpCapacity(gEmptyStringCapacity) {}
    void Construct(const WString& other);                     // 0x0056E2D0 copy ctor (placement)
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650 do_assign
    void resize(unsigned count);                              // 0x00429520 resize
    void erase(unsigned pos, unsigned count);                 // 0x004228E0 erase(pos,count)
    void make_lower();                                        // 0x005E8E80 make_lower
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    wchar_t& operator[](unsigned i) { return mpBegin[i]; }
};

// EASTL sp_vector<WString>: begin/end/capacity plus allocator padding (16 bytes).
struct WStringVec {
    WString* mpBegin;       // +0x00
    WString* mpEnd;         // +0x04
    WString* mpCapacity;    // +0x08
    int mAllocator;         // +0x0c
    WStringVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    WString* erase(WString* pos);                          // 0x0092B700
    void DoInsertValue(WString* pos, const WString& value); // 0x00554C30
};

// EASTL vector helpers used by basic_string clear().
WString* CopyWStrings(WString* first, WString* last, WString* dst);  // 0x0084AB40
void DoDestroyValues(WString* first, WString* last);                 // 0x0084AAD0
const wchar_t* FindLastOf(const wchar_t* end, const wchar_t* begin,
                          const wchar_t* patBegin, const wchar_t* patEnd); // 0x005728F0
int MakeLocaleAvailable(const void* a, const void* b);               // 0x0087D9A0
int GetCurrentAppPath(WString* out);                                 // 0x0092B5F0

// Common command-line splitter base. Polymorphic (virtual destructor), which
// puts the implicit vptr at +0x00.
struct SplitBase {
    WStringVec mArgs;       // +0x04
    int mUnknown14;         // +0x14
    WString mText;          // +0x18
    WString mEmpty;         // +0x28
    virtual ~SplitBase();
    void Set(const short* s);
    void Set(const char* s);
    void InsertArgument(const wchar_t* arg, int index);    // 0x0092B7B0
    __forceinline SplitBase(const char* s) { Set(s); }
    __forceinline SplitBase(const short* s) { Set(s); }
};

__declspec(noinline, nothrow) void Split(WString* text, WStringVec* args);
__declspec(noinline, nothrow) void FixCommandLine(SplitBase* cmdline, const wchar_t* arg);

struct Splitable3 : SplitBase {
    Splitable3(const char* s);
};
struct Splitable4 : SplitBase {
    Splitable4(const short* s);
};

// @ 0x0092C2D0  WriteToBigEndian
void WriteToBigEndian(void* dst, unsigned value, int size) {
    if (size == 1) { *(unsigned char*)dst = (unsigned char)value; return; }
    if (size == 4) { *(unsigned*)dst = _byteswap_ulong(value); return; }
    unsigned char hi = (unsigned char)(value >> 8);
    if (size == 2) { *(unsigned short*)dst = _byteswap_ushort((unsigned short)value); return; }
    if (size == 3) {
        ((unsigned char*)dst)[0] = (unsigned char)(value >> 16);
        ((unsigned char*)dst)[1] = hi;
        ((unsigned char*)dst)[2] = (unsigned char)value;
    }
}

// @ 0x0092C0C0  SplitBase::Set
__declspec(noinline) void SplitBase::Set(const short* s) {
    if (s != 0) {
        const short* p = s;
        while (*p) ++p;
        mText.assign((const wchar_t*)s, (const wchar_t*)s + (p - s));
        Split(&mText, &mArgs);
        return;
    }
    if (mText.mpBegin != mText.mpEnd) {
        *mText.mpBegin = 0;
        mText.mpEnd = mText.mpBegin;
    }
    Split(&mText, &mArgs);
}

// @ 0x0092C130  SplitBase::Set
__declspec(noinline) void SplitBase::Set(const char* s) {
    if (s != 0) {
        WString* text = &mText;
        const char* q = s + 1;
        const char* p = s;
        char c;
        do { c = *p++; } while (c);
        unsigned len = (unsigned)(p - q);
        text->resize(len);
        if (len > 0) {
            unsigned i = 0;
            do {
                text->mpBegin[i] = (unsigned char)s[i];
                ++i;
            } while (i < len);
        }
        Split(text, &mArgs);
        return;
    }
    if (mText.mpBegin != mText.mpEnd) {
        *mText.mpBegin = 0;
        mText.mpEnd = mText.mpBegin;
    }
    Split(&mText, &mArgs);
}

// @ 0x0092C1B0  Splitable3::Splitable3
__declspec(noinline) Splitable3::Splitable3(const char* s) : SplitBase(s) {
    FixCommandLine(this, 0);
}

// @ 0x0092C210  Splitable4::Splitable4
__declspec(noinline) Splitable4::Splitable4(const short* s) : SplitBase(s) {
    FixCommandLine(this, 0);
}

// ================================================================== implementations
namespace {

inline bool IsSpaceW(wchar_t c) {
    return c == L' ' || c == L'\t' || c == L'\n' || c == L'\r';
}

// Index of the last occurrence of any character of `pat` in `s`, or -1.
int LastIndexOf(const WString& s, const wchar_t* pat) {
    const wchar_t* end = s.mpBegin + s.size();
    const wchar_t* p = FindLastOf(end, s.mpBegin, pat, pat + 1);
    return (int)(p - s.mpBegin) - 1;
}

unsigned WStrLen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (unsigned)(p - s);
}

// Push one token onto the argument vector, trimming a pair of surrounding quotes.
void PushToken(WStringVec* args, const WString& token, unsigned start, unsigned end) {
    WString piece;
    piece.assign(token.mpBegin + start, token.mpBegin + end);
    if (piece.size() != 0 && piece[0] == L'"' && piece[piece.size() - 1] == L'"') {
        piece.erase(piece.size() - 1, 1);
        if (piece.size() != 0)
            piece.erase(0, 1);
    }
    if (args->mpEnd < args->mpCapacity) {
        WString* slot = args->mpEnd;
        args->mpEnd = slot + 1;
        if (slot)
            slot->Construct(piece);
    } else {
        args->DoInsertValue(args->mpEnd, piece);
    }
}

}  // namespace

// @ 0x0092B840  Split (EA::CommandLine::ConvertStringToStringArray)
__declspec(noinline, nothrow) void Split(WString* text, WStringVec* args) {
    WString token;
    token.assign(text->mpBegin, text->mpEnd);

    // args.clear(): copy nothing, destroy every element, reset the end pointer.
    WString* firstDestroyed = CopyWStrings(args->mpEnd, args->mpEnd, args->mpBegin);
    DoDestroyValues(firstDestroyed, args->mpEnd);
    args->mpEnd = args->mpBegin;

    // trim trailing then leading whitespace
    while (token.size() != 0 && IsSpaceW(token[token.size() - 1]))
        token.erase(token.size() - 1, 1);
    while (token.size() != 0 && IsSpaceW(token[0]))
        token.erase(0, 1);

    const unsigned len = token.size();
    if (len == 0)
        return;

    unsigned start = 0;
    unsigned i = 0;
    unsigned quotes = 0;
    while (i < len) {
        const wchar_t c = token[i];
        if (!IsSpaceW(c)) {
            if (c == L'"')
                ++quotes;
            ++i;
            continue;
        }
        if (quotes & 1) {          // inside a quoted span: not a separator
            ++i;
            continue;
        }
        quotes = 0;
        PushToken(args, token, start, i);
        while (i + 1 < len && IsSpaceW(token[i + 1]))
            ++i;
        start = i + 1;
        ++i;
    }
    PushToken(args, token, start, len);
}

// @ 0x0092BBE0  FixCommandLine (EA::AppCommandLine::FixCommandLine)
__declspec(noinline, nothrow) void FixCommandLine(SplitBase* cmdline, const wchar_t* arg) {
    const bool hasArgs = (cmdline->mArgs.mpEnd != cmdline->mArgs.mpBegin);

    WString firstArg;
    if (hasArgs) {
        WString* src = (cmdline->mArgs.mpEnd == cmdline->mArgs.mpBegin)
                           ? &cmdline->mEmpty
                           : cmdline->mArgs.mpBegin;
        if (src != &firstArg)
            firstArg.assign(src->mpBegin, src->mpEnd);
    }

    wchar_t buffer[512];
    buffer[0] = 0;
    for (int k = 1; k < 512; ++k)
        buffer[k] = 0;

    WString appPath;
    if (arg != 0) {
        wchar_t* d = buffer;
        const wchar_t* s = arg;
        wchar_t c;
        do { c = *s++; *d++ = c; } while (c);
    } else {
        GetCurrentAppPath(&appPath);
        wchar_t* d = buffer;
        const wchar_t* s = appPath.mpBegin;
        wchar_t c;
        do { c = *s++; *d++ = c; } while (c);
    }

    if (hasArgs) {
        if (appPath.size() == 0)
            appPath.assign(buffer, buffer + WStrLen(buffer));

        // Directory portion of the application path, made lower case.
        WString exeDir;
        exeDir.assign(appPath.mpBegin, appPath.mpEnd);
        int slash = LastIndexOf(exeDir, L"/");
        if (slash >= 0)
            exeDir.erase(0, (unsigned)slash + 1);
        slash = LastIndexOf(exeDir, L"\\");
        if (slash >= 0)
            exeDir.erase((unsigned)slash, (unsigned)-1);
        exeDir.make_lower();

        // Directory portion of the first argument, made lower case.
        WString argDir;
        argDir.assign(firstArg.mpBegin, firstArg.mpEnd);
        slash = LastIndexOf(argDir, L"/");
        if (slash >= 0 &&
            ((isalpha((unsigned char)argDir[0]) && argDir[1] == L':') ||
             argDir[0] == L'\\' || argDir[0] == L'/'))
            argDir.erase(0, (unsigned)slash + 1);
        slash = LastIndexOf(argDir, L"\\");
        if (slash >= 0)
            argDir.erase((unsigned)slash, (unsigned)-1);
        argDir.make_lower();

        if (MakeLocaleAvailable(&exeDir, &argDir)) {
            if (cmdline->mArgs.mpEnd != cmdline->mArgs.mpBegin) {
                cmdline->mArgs.erase(cmdline->mArgs.mpBegin);
                if (cmdline->mText.mpBegin != cmdline->mText.mpEnd) {
                    *cmdline->mText.mpBegin = 0;
                    cmdline->mText.mpEnd = cmdline->mText.mpBegin;
                }
            }
            cmdline->InsertArgument(appPath.mpBegin, 0);
        } else {
            appPath.assign(buffer, buffer + WStrLen(buffer));
            if (appPath.size() != 0)
                cmdline->InsertArgument(appPath.mpBegin, 0);
        }
    } else {
        appPath.assign(buffer, buffer + WStrLen(buffer));
        if (appPath.size() != 0)
            cmdline->InsertArgument(appPath.mpBegin, 0);
    }
}

// @ 0x0092C340  DecodeUnchecked
int DecodeUnchecked(unsigned char* dst, unsigned hint, unsigned char* src) {
    (void)hint;
    int size = 0;
    if (src == 0) return 0;
    unsigned flags = src[0];
    ++src;
    if (flags & 0x80) {
        if (flags & 1) src += 4;
        size = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
        src += 4;
    } else {
        if (flags & 1) src += 3;
        size = (src[0] << 16) | (src[1] << 8) | src[2];
        src += 3;
    }
    for (;;) {
        unsigned cmd = *src++;
        if ((cmd & 0x80) == 0) {
            unsigned off = *src++;
            unsigned count = cmd & 3;
            while (count--) *dst++ = *src++;
            unsigned offset = ((cmd & 0x60) << 3) + off + 1;
            unsigned len = ((cmd >> 2) & 7) + 2;
            unsigned char* from = dst - offset;
            do { *dst++ = *from++; } while (--len);
        } else if ((cmd & 0x40) == 0) {
            unsigned b0 = src[0];
            unsigned b1 = src[1];
            src += 2;
            unsigned count = b0 >> 6;
            while (count--) *dst++ = *src++;
            unsigned offset = ((b0 & 0x3f) << 8) + b1 + 1;
            unsigned len = (cmd & 0x3f) + 3;
            unsigned char* from = dst - offset;
            do { *dst++ = *from++; } while (--len);
        } else if ((cmd & 0x20) == 0) {
            unsigned b0 = src[0];
            unsigned b1 = src[1];
            unsigned b2 = src[2];
            src += 3;
            unsigned count = cmd & 3;
            while (count--) *dst++ = *src++;
            unsigned offset = ((cmd & 0x10) << 12) + (b0 << 8) + b1 + 1;
            unsigned len = ((cmd & 0x0c) << 6) + b2 + 4;
            unsigned char* from = dst - offset;
            do { *dst++ = *from++; } while (--len);
        } else {
            unsigned count = (cmd & 0x1f) * 4 + 4;
            if (count > 0x70) {
                count = cmd & 3;
                while (count--) *dst++ = *src++;
                return size;
            }
            while (count--) *dst++ = *src++;
        }
    }
}
