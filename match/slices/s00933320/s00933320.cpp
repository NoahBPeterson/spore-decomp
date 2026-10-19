// Slice s00933320: EA::IO::IniFile + its StackArray/string/EASTL helpers (MSVC 2008 SP1, /O2).
// Real names from the 2008 dev-build PDB are used where known; the IniFile virtual slots are called
// through the vtable by byte offset (0x1c/0x20/0x24/0x28/0x2c/0x30/0x38/0x50/0x54/0x58/0x5c).
#include "types.h"

typedef unsigned short char16_t;
typedef unsigned int uint32_t;

char gEmptyString16;
char gEmptyString16B;
char gEmptyString16C;

void* operator new[](unsigned, const char*, int, int, int, int);    // 0x00f473a0  ??_U@YAPAXIPBDHHHH@Z
void  operator delete[](void*);
extern "C" void* __cdecl operator_new_ea(unsigned, const char*, int, int, const char*, int);  // 0x00f473a0
extern "C" void  __cdecl operator_delete_ea(void*);                                            // 0x00f47380
extern "C" void* __cdecl memcpy_f(void*, const void*, unsigned);
extern "C" wchar_t* __cdecl wcsncpy_f(wchar_t*, const wchar_t*, unsigned);
extern "C" void  __cdecl FUN_004228e0(void*, unsigned);

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---------------------------------------------------------------------------------------------
// anonymous namespace StackArray<T,256> (inline buffer + heap overflow).
// ---------------------------------------------------------------------------------------------
template <typename T, int N>
struct StackArray {
    T mData[N];
    T* mpData;
    T* mpDataEnd;
    unsigned mCapacity;
    void Resize(unsigned n);
    T* Init(T* p, int n);       // 0x009332D0 - out of line in the original
};

// @ 0x00933320  StackArray<wchar_t,256>::Resize
template <typename T, int N>
void StackArray<T, N>::Resize(unsigned n) {
    T* old = mpData;
    if (n > mCapacity) {
        if (old != mData && mpDataEnd != old) {
            operator delete[](old);
            mpData = mData;
        }
        mpData = new ("EAIniFile", 0, 0, 0, 0) T[n];
        mCapacity = n;
    }
}
template struct StackArray<wchar_t, 256>;
// @ 0x00933390  StackArray<char,256>::Resize
template struct StackArray<char, 256>;

// ---------------------------------------------------------------------------------------------
// EASTL-ish wide string (16-byte body + allocator at +0x10, plus a spare slot at +0xc).
// ---------------------------------------------------------------------------------------------
struct WString {
    char16_t* mpBegin;      // +0x00
    char16_t* mpEnd;        // +0x04
    char16_t* mpCapacity;   // +0x08
    void*     mpAlloc;      // +0x0c
    void DeallocateSelf();                                       // 0x00933960
    void Reset() {
        mpBegin = (char16_t*)&gEmptyString16;
        mpEnd   = (char16_t*)&gEmptyString16;
        mpCapacity = (char16_t*)&gEmptyString16B;
    }
    void ctor(const wchar_t* str, const void* dummy);            // 0x0041df50
    void make_lower();                                           // 0x005e8e80
    void ltrim();                                                // 0x00554170
    void rtrim();                                                // 0x005541e0
    void trim();                                                 // 0x0057eda0
    int  find(char16_t c, unsigned pos);                         // 0x004f6ab0
    void erase(unsigned pos, unsigned n);                        // 0x004228e0
    void append(const WString& s, unsigned pos, unsigned n);     // 0x006ab800
    WString* operator=(const WString& s);                        // 0x0057cb60
    WString* Assign(const WString& s);
};

// rbtree<basic_string<wchar_t>>: only the lookup entry point is needed here.
struct RBTreeKeyedByWString {
    void* mpRoot;                                                // +0x00 (header at tree base)
    void* find_iter(void** out, const WString* key);             // 0x005e96f0
};

// @ 0x00933960  (lib_eatext::basic_string<wchar_t>::DeallocateSelf)
void WString::DeallocateSelf() {
    char16_t* p = mpBegin;
    if ((int)((int)mpCapacity - (int)p & 0xfffffffeU) > 2 && p != 0) {
        operator delete[](p);
    }
}

struct CharStr;
struct WStr16;

// IniFile layout (only the fields this slice touches).
// ---------------------------------------------------------------------------------------------
struct IniFile {
    void*   vtbl;           // +0x000
    char    pad[0x434];     // +0x004
    void*   mpEncodingSrc;  // +0x438
    int     mEncoding;      // +0x43c
    char    m_b440;         // +0x440
    char    m_b441;         // +0x441
    char    m_b442;         // +0x442
    char    m_b443;         // +0x443
    void*   mpTree;         // +0x444
    void*   mpTreeEnd;      // +0x448

    void* V(int off) const { return ((void**)vtbl)[off / 4]; }

    int   ReadEntryRaw(void* a, void* b, wchar_t* dst, int maxn);
    bool  WriteEntryFormatted(void* a, unsigned n, void* args);
    int   ReadBinary(void* a, void* b, void* p, int n);
    bool  WriteBinary(void* a1, void* a2, void* src, unsigned n);
    bool  ConvertAndWriteStream(void* a, int n);
    bool  GetFileLine(WString* out);
    bool  GetFileLine8To8(CharStr* out);
    bool  GetFileLine16To16(WStr16* out);
    bool  SectionExists(wchar_t* name);
    int   ReadEntry(const wchar_t* section, const wchar_t* key, WString* out);
};

int ReadEntryFormatted(IniFile* self, void* a, void* b, void* c, void* d);

bool EnsureTrailingPathSeparator(wchar_t*, int);
int  ConcatenatePathComponents(wchar_t*, const wchar_t*, const wchar_t*);

// ---------------------------------------------------------------------------------------------
// @ 0x009333F0  EA::IO::IniFile::WriteEntryFormatted
// ---------------------------------------------------------------------------------------------
extern "C" unsigned Vsnprintf16(wchar_t*, unsigned, const wchar_t*, void*);

bool IniFile::WriteEntryFormatted(void* a, unsigned n, void* args) {
    StackArray<wchar_t, 256> buf;
    buf.mpData = buf.mData;
    buf.mpDataEnd = 0;
    buf.mCapacity = 0x100;
    unsigned len = Vsnprintf16(buf.mpData, 0x100, (const wchar_t*)a, args);
    if (len > buf.mCapacity) {
        buf.Resize(len);
        Vsnprintf16(buf.mpData, buf.mCapacity, (const wchar_t*)a, args);
    }
    bool r = ((bool(__fastcall*)(void*, void*))V(0x2c))(this, buf.mpData) != 0;
    if (buf.mpData != buf.mData && buf.mpDataEnd != buf.mpData) operator delete[](buf.mpData);
    return r;
}

// ---------------------------------------------------------------------------------------------
// @ 0x009334D0  EA::IO::IniFile::ReadBinary
// ---------------------------------------------------------------------------------------------
extern "C" bool EA_Text_ConvertASCIIArrayToBinaryData(const wchar_t*, int, void*);  // 0x0093d280

int IniFile::ReadBinary(void* a, void* b, void* p, int n) {
    // Wide scratch buffer that receives the hex text read off the stream.
    StackArray<wchar_t, 256> wb;
    wb.mpDataEnd = 0;
    wb.mCapacity = 0x100;
    wb.mpData = wb.mData;
    int len = ((int(__thiscall*)(void*, void*, void*, void*, unsigned))V(0x20))(this, a, b, wb.mpData, 0x100);
    if ((int)wb.mCapacity < len) {
        wb.Resize((unsigned)(len + 1));
        ((int(__thiscall*)(void*, void*, void*, void*, unsigned))V(0x20))(this, a, b, wb.mpData, (unsigned)len);
    }
    // Byte scratch buffer.  It takes its own 256-byte inline block, then adopts the wide
    // buffer's storage (twice the bytes we need) via Init once the wide buffer is non-empty.
    StackArray<char, 256> cb;
    cb.mpData = cb.mData;
    cb.mpDataEnd = (char*)p;
    cb.mCapacity = (unsigned)n;
    if (cb.mpDataEnd != 0 && cb.mCapacity != 0)
        cb.Init((char*)p, n);
    unsigned half = (unsigned)(n / 2);
    if (half > cb.mCapacity) cb.Resize(half);
    char* dst = cb.Init((char*)wb.mpData, (int)cb.mCapacity);
    EA_Text_ConvertASCIIArrayToBinaryData((const wchar_t*)cb.mpData, len, dst);
    if (cb.mpDataEnd != cb.mpData) {
        unsigned cnt = cb.mCapacity;
        if (cnt > 0x100) cnt = 0x100;
        memcpy_f(cb.mpDataEnd, cb.mpData, cnt);
    }
    if (cb.mpData != cb.mData && cb.mpDataEnd != cb.mpData) operator delete[](cb.mpData);
    if (wb.mpData != wb.mData && wb.mpDataEnd != wb.mpData) operator delete[](wb.mpData);
    return len;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933640  EA::IO::IniFile::WriteBinary
// ---------------------------------------------------------------------------------------------
extern "C" int EA_Text_ConvertBinaryDataToASCIIArray(const void*, unsigned,
                                                     wchar_t*);  // 0x0093d210

bool IniFile::WriteBinary(void* a1, void* a2, void* src, unsigned n) {
    StackArray<wchar_t, 256> buf;
    buf.mpData = buf.mData; buf.mpDataEnd = 0; buf.mCapacity = 0x100;
    unsigned need = n * 2 + 1;
    if (need > buf.mCapacity) buf.Resize(need);
    EA_Text_ConvertBinaryDataToASCIIArray(src, n, (wchar_t*)buf.mpData);
    bool r = ((bool(__thiscall*)(void*, void*, void*, void*))V(0x2c))(this, a1, a2, buf.mpData) != 0;
    if (buf.mpData != buf.mData && buf.mpDataEnd != buf.mpData) operator delete[](buf.mpData);
    return r;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933700  EA::IO::IniFile::ConvertAndWriteStream
// ---------------------------------------------------------------------------------------------
extern "C" int EA_Text_GetCharacterSize(int);
extern "C" void EA_Text_ConvertEncoding(void*, int, int, void*, int*, int);

bool IniFile::ConvertAndWriteStream(void* a, int n) {
    StackArray<char, 256> buf;
    buf.mpData = buf.mData; buf.mpDataEnd = 0; buf.mCapacity = 0x100;
    int charSize = mEncoding;
    int bytes = n * 2;
    if (charSize != 0x10) {
        charSize = EA_Text_GetCharacterSize(charSize);
        if (buf.mCapacity < (unsigned)(charSize * n)) {
            buf.Resize(charSize * n);
        }
        int outLen = n;
        EA_Text_ConvertEncoding(a, n, 0x10, buf.mpData, &outLen, mEncoding);
        bytes = outLen * charSize;
    }
    if (mpEncodingSrc != 0 && buf.mpData != 0 && bytes != 0) {
        ((void(__fastcall*)(void*, void*, int))V(0x38))(this, buf.mpData, bytes);
    }
    if (buf.mpData != buf.mData && buf.mpDataEnd != buf.mpData) operator delete[](buf.mpData);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x009337F0  WString copy constructor
// ---------------------------------------------------------------------------------------------
extern "C" int WStr_AllocateSelf(WString*, int);
extern "C" void WString_copy(void*, const void*, unsigned);

WString* WString_ctor(WString* dst, const WString* src) {
    dst->mpBegin = 0; dst->mpEnd = 0; dst->mpCapacity = 0;
    int n = (int)((char*)src->mpEnd - (char*)src->mpBegin) >> 1;
    WStr_AllocateSelf(dst, n + 1);
    WString_copy(dst->mpBegin, src->mpBegin, n * 2);
    dst->mpEnd = (char16_t*)((char*)dst->mpBegin + n * 2);
    *dst->mpEnd = 0;
    *(void**)((char*)dst + 0x10) = *(void**)((const char*)src + 0x10);
    return dst;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933850  EA::IO::IniFile::ReadEntry
// ---------------------------------------------------------------------------------------------
extern "C" int WString_InitRange(void*, void*);

int IniFile::ReadEntryRaw(void* a, void* b, wchar_t* dst, int maxn) {
    char16_t* loc[4];
    loc[0] = (char16_t*)&gEmptyString16;
    loc[1] = (char16_t*)&gEmptyString16;
    loc[2] = (char16_t*)&gEmptyString16B;
    int r = ((int(__thiscall*)(void*, void*, void*, void*))V(0x24))(this, a, b, loc);
    if (r >= 0) {
        int n = maxn > r ? r : maxn;
        wcsncpy_f(dst, (const wchar_t*)loc[0], n);
        dst[n - 1] = 0;
    }
    if ((int)(((char*)loc[1] - (char*)loc[0]) & 0xfffffffeU) > 2 && loc[0] != 0)
        operator delete[](loc[0]);
    return r;
}

// ---------------------------------------------------------------------------------------------
extern "C" int Vsscanf16(void*, void*, void*);                          // 0x00939d30

// @ 0x009338E0  ReadEntryFormatted (cdecl free form: self, fmt, src, c, d)
int ReadEntryFormatted(IniFile* self, void* a, void* b, void* c, void* d) {
    char16_t* loc[4];
    loc[0] = (char16_t*)&gEmptyString16;
    loc[1] = (char16_t*)&gEmptyString16;
    loc[2] = (char16_t*)&gEmptyString16B;
    int r = 0;
    if (((int(__thiscall*)(void*, void*, void*, void*))self->V(0x24))(self, a, b, loc) != 0)
        r = Vsscanf16(loc[0], c, &d);
    if ((int)(((char*)loc[1] - (char*)loc[0]) & 0xfffffffeU) > 2 && loc[0] != 0)
        operator delete[](loc[0]);
    return r;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933980  EA::IO::IniFile::GetFileLine
// ---------------------------------------------------------------------------------------------
extern "C" void WString_RangeInitialize(WString*, const wchar_t*);
extern "C" int  WString_makeLower(WString*);
extern "C" int  EA_Text_GetCharacterSize(int);                          // 0x0093c920
extern "C" int  EA_Text_ConvertEncoding8(void*, int, int, void*);       // 0x0093cfb0

bool IniFile::GetFileLine(WString* out) {
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    unsigned cs = EA_Text_GetCharacterSize(mEncoding);
    if (cs == 2) {
        return ((bool(__thiscall*)(void*, WString*))V(0x58))(this, out) != 0;
    }
    char16_t* loc[4];
    loc[0] = (char16_t*)&gEmptyString16;
    loc[1] = (char16_t*)&gEmptyString16;
    loc[2] = (char16_t*)&gEmptyString16C;
    if (((int(__thiscall*)(void*, void*))V(0x54))(this, loc)) {
        EA_Text_ConvertEncoding8(loc[0], (int)((char*)loc[1] - (char*)loc[0]), 8, out);
        if ((int)((char*)loc[2] - (char*)loc[0]) > 1 && loc[0] != 0) operator delete[](loc[0]);
        return true;
    }
    if ((int)((char*)loc[2] - (char*)loc[0]) > 1 && loc[0] != 0) operator delete[](loc[0]);
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933A90  eastl::uninitialized_move_impl<>::do_move_commit (pair<WString,WString>[])
// ---------------------------------------------------------------------------------------------
void* eastl_do_move_commit(WString* first, WString* last, WString* out) {
    if (first != last) {
        do {
            WString* hi = (WString*)((char*)first + 0x10);
            char16_t* p2 = hi->mpBegin;
            if ((int)((int)hi->mpCapacity - (int)p2 & 0xfffffffeU) > 2 && p2 != 0) operator delete[](p2);
            char16_t* p1 = first->mpBegin;
            if ((int)((int)first->mpCapacity - (int)p1 & 0xfffffffeU) > 2 && p1 != 0) operator delete[](p1);
            first += 2;
            out += 2;
        } while (first != last);
        return out;
    }
    return out;
}

// ---------------------------------------------------------------------------------------------
extern "C" void WString_AssignRange(WString*, const char16_t*, const char16_t*);

// @ 0x00933B00  eastl::copy_backward_impl<>::do_copy (pair<WString,WString>[])
// ---------------------------------------------------------------------------------------------
void* eastl_do_copy_backward(WString* first, WString* last, WString* out) {
    if (first == last) return out;
    WString* o = out;
    WString* ol = out + 1;
    WString* l = last;
    WString* ll = last + 1;
    do {
        l = (WString*)((char*)l - 0x20);
        o = (WString*)((char*)o - 0x20);
        ll = (WString*)((char*)ll - 0x20);
        ol = (WString*)((char*)ol - 0x20);
        if (l != o) WString_AssignRange(o, l->mpBegin, l->mpEnd);
        if (ll != ol) WString_AssignRange(ol, ll->mpBegin, ll->mpEnd);
    } while (l != first);
    return o;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933B70  EA::IO::IniFile::GetFileLine8To8
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl memset_f(void*, int, unsigned);             // 0x011e073e

// The transcode object at IniFile+0x438; vtable slots: 0x24 Tell, 0x28 Seek, 0x30 Read.
struct IniStream {
    void* vtbl;
    void* V(int off) const { return ((void**)vtbl)[off / 4]; }
};
typedef int  (__thiscall *T_i_i)(void*, int);
typedef int  (__thiscall *T_i_pi)(void*, void*, int);
typedef void (__thiscall *T_v_ii)(void*, int, int);

// 8-bit and 16-bit eastl character strings (same 3-pointer body as WString).
struct CharStr {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void append(const char* first, const char* last);                // 0x00455d60
};
struct WStr16 {
    char16_t* mpBegin; char16_t* mpEnd; char16_t* mpCapacity;
    void append(const char16_t* first, const char16_t* last);        // 0x00429580
};

bool IniFile::GetFileLine8To8(CharStr* out) {
    char buf[0x40];
    bool done = false;
    char c;
    int i = 0;
    bool found = false;
    int pos = ((T_i_i)((IniStream*)mpEncodingSrc)->V(0x24))((IniStream*)mpEncodingSrc, 0);
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    memset_f(buf, 0, 0x40);
    for (;;) {
        int n = ((T_i_pi)((IniStream*)mpEncodingSrc)->V(0x30))((IniStream*)mpEncodingSrc, buf, 0x40);
        if (n == 0 || n == -1) break;
        done = true;
        i = 0;
        if (n > 0) {
            for (;;) {
                if (i >= n) goto append;
                if (buf[i] == '\r' || buf[i] == '\n') break;
                ++i;
            }
            found = true;
            ((T_v_ii)((IniStream*)mpEncodingSrc)->V(0x28))((IniStream*)mpEncodingSrc, pos + i, 0);
            for (;;) {
                if (((T_i_pi)((IniStream*)mpEncodingSrc)->V(0x30))((IniStream*)mpEncodingSrc, &c, 1) != 1) goto append;
                if (c != '\r' && c != '\n') break;
            }
            ((T_v_ii)((IniStream*)mpEncodingSrc)->V(0x28))((IniStream*)mpEncodingSrc, -1, 1);
        }
    append:
        out->append(buf, buf + i);
        pos = ((T_i_i)((IniStream*)mpEncodingSrc)->V(0x24))((IniStream*)mpEncodingSrc, 0);
        if (found) break;
    }
    return done;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933C80  EA::IO::IniFile::GetFileLine16To16
// ---------------------------------------------------------------------------------------------
extern "C" void WStr_Append(WString*, const char16_t*, const char16_t*);

bool IniFile::GetFileLine16To16(WStr16* out) {
    char16_t buf[0x80];
    char16_t c;
    bool done = false;
    bool found = false;
    int pos = ((T_i_i)((IniStream*)mpEncodingSrc)->V(0x24))((IniStream*)mpEncodingSrc, 0);
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    memset_f(buf, 0, 0x100);
    for (;;) {
        int n = ((T_i_pi)((IniStream*)mpEncodingSrc)->V(0x30))((IniStream*)mpEncodingSrc, buf, 0x100);
        if (n == 0 || n == -1) break;
        int i = 0;
        done = true;
        if (n > 0) {
            for (;;) {
                if (i >= n) goto append;
                if (buf[i] == 0xd || buf[i] == 0xa) break;
                ++i;
            }
            found = true;
            ((T_v_ii)((IniStream*)mpEncodingSrc)->V(0x28))((IniStream*)mpEncodingSrc, pos + i, 0);
            for (;;) {
                if (((T_i_pi)((IniStream*)mpEncodingSrc)->V(0x30))((IniStream*)mpEncodingSrc, &c, 2) != 2) goto append;
                if (c != 0xd && c != 0xa) break;
            }
            ((T_v_ii)((IniStream*)mpEncodingSrc)->V(0x28))((IniStream*)mpEncodingSrc, -2, 1);
        }
    append:
        out->append(buf, buf + i);
        pos = ((T_i_i)((IniStream*)mpEncodingSrc)->V(0x24))((IniStream*)mpEncodingSrc, 0);
        if (found) break;
    }
    if (mEncoding != 0x4b0) {
        int cnt = (int)(out->mpEnd - out->mpBegin) >> 1;
        char16_t* q = out->mpBegin;
        for (int k = 0; k < cnt; ++k) {
            unsigned short w = q[k];
            q[k] = (char16_t)((w >> 8) | (w << 8));
        }
    }
    return done;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933DF0  destroy a range of pair<WString,WString> (0x20 stride)
// ---------------------------------------------------------------------------------------------
void __stdcall DestroyPairRange(WString* first, WString* last) {
    for (; first < last; first += 2) {
        WString* s2 = (WString*)((char*)first + 0x10);
        char16_t* p2 = s2->mpBegin;
        if ((int)((int)s2->mpCapacity - (int)p2 & 0xfffffffeU) > 2 && p2 != 0) operator delete[](p2);
        char16_t* p1 = first->mpBegin;
        if ((int)((int)first->mpCapacity - (int)p1 & 0xfffffffeU) > 2 && p1 != 0) operator delete[](p1);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933E50  rbtree insert helper
// ---------------------------------------------------------------------------------------------
extern "C" int  WString_compare(const char16_t*, const char16_t*, const char16_t*,
                                const char16_t*);                     // 0x005e9260
extern "C" void RBTreeInsert(void*, void*, void*, int);               // 0x009216a0

struct RBTreeHelper {
    void* Insert(void** out, char* hint, WString* key, char flag);
};

// 0x009337F0 is __thiscall (dst in ecx, src on the stack, `ret 4`) even though the PDB spells it
// as a two-argument __cdecl helper.
typedef WString* (__thiscall *WStringCtorThiscall)(WString*, const WString*);

void* RBTreeHelper::Insert(void** out, char* hint, WString* key, char flag) {
    char* tree = (char*)this;
    int side = 0;
    if (flag == 0 && hint != tree + 4) {
        if (WString_compare(key->mpBegin, key->mpEnd,
                            *(char16_t**)(hint + 0x10), *(char16_t**)(hint + 0x14)) >= 0)
            side = 1;
    }
    void* node = operator_new_ea(0x24, "EASTL", 0, 0, ALLOC_FILE, 0xd1);
    if ((char*)node + 0x10 != 0)
        ((WStringCtorThiscall)WString_ctor)((WString*)((char*)node + 0x10), key);
    RBTreeInsert(node, hint, tree + 4, side);
    ++*(int*)(tree + 0x14);
    *out = node;
    return (void*)out;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933EF0  EA::IO::IniFile::ReadEntry
//   bool/int ReadEntry(const wchar_t* section, const wchar_t* key, WString* out)
//   Reads forward from the section's offset looking for "key=value"; returns the value length.
// ---------------------------------------------------------------------------------------------
extern "C" int Locale_MakeLocaleAvailable(const WString*, const WString*);   // 0x0087d9a0
typedef bool (__thiscall *T_b_ii)(void*, int, int);

int IniFile::ReadEntry(const wchar_t* section, const wchar_t* key, WString* out) {
    if (mpEncodingSrc == 0) return -1;
    if (section == 0 || *section == 0) return -1;
    if (key == 0 || *key == 0) return -1;
    if (m_b442 == 0) {
        if ((char)((int(__thiscall*)(void*, int))V(0x50))(this, 1) == 0) {
            if (m_b441 == 0) ((void(__thiscall*)(void*))V(0x1c))(this);
            return -1;
        }
    }
    WString value;      // the line currently being examined
    WString name;       // the key name parsed out of that line
    WString keyLower;   // "key", lowercased
    WString secLower;   // "section", lowercased
    secLower.ctor(section, &section);
    secLower.make_lower();
    keyLower.ctor(key, &section);
    keyLower.make_lower();
    void* node = ((RBTreeKeyedByWString*)((char*)this + 0x444))->find_iter(&node, &secLower);
    if (node == (void*)((char*)this + 0x448)) goto fail;
    if (!((T_b_ii)((IniStream*)mpEncodingSrc)->V(0x28))((IniStream*)mpEncodingSrc,
                                                       *(int*)((char*)node + 0x20), 0)) goto fail;
    value.Reset();
    name.Reset();
    if ((char)((int(__thiscall*)(void*, WString*))V(0x5c))(this, &value) != 0) {
        if ((char)((int(__thiscall*)(void*, WString*))V(0x5c))(this, &value) != 0) {
            for (;;) {
                value.ltrim();
                if ((((int)((char*)value.mpEnd - (char*)value.mpBegin)) & 0xfffffffe) == 0) goto next;
                if (*value.mpBegin == 0x3b) goto next;                  // ';' comment line
                if (*value.mpBegin == 0x5b) {                           // '[' next section
                    if (value.mpBegin != value.mpEnd) { *value.mpBegin = 0; value.mpEnd = value.mpBegin; }
                    goto fail;
                }
                {
                    int eq = value.find(0x3d, 0);                       // '='
                    if (eq != -1) {
                        name.append(value, 0, eq);
                        name.rtrim();
                        name.make_lower();
                        if (Locale_MakeLocaleAvailable(&name, &keyLower) != 0) {
                            value.erase(0, eq + 1);
                            value.trim();
                            out->operator=(value);
                            if (m_b441 == 0) ((void(__thiscall*)(void*))V(0x1c))(this);
                            int len = (int)((char*)value.mpEnd - (char*)value.mpBegin) >> 1;
                            value.DeallocateSelf();
                            name.DeallocateSelf();
                            keyLower.DeallocateSelf();
                            secLower.DeallocateSelf();
                            return len;
                        }
                    }
                }
            next:
                if ((char)((int(__thiscall*)(void*, WString*))V(0x5c))(this, &value) == 0) break;
            }
        }
    }
fail:
    if (m_b441 == 0) ((void(__thiscall*)(void*))V(0x1c))(this);
    value.DeallocateSelf();
    name.DeallocateSelf();
    keyLower.DeallocateSelf();
    secLower.DeallocateSelf();
    return -1;
}

// ---------------------------------------------------------------------------------------------
// @ 0x009341B0  EA::IO::IniFile::SectionExists
// ---------------------------------------------------------------------------------------------
extern "C" void* RbtreeFind(void* tree, const void* key);
extern "C" void  WString_Assign(WString*, const WString*);

bool IniFile::SectionExists(wchar_t* name) {
    if (m_b442 == 0) {
        char c = (char)((int(__fastcall*)(void*, int))V(0x50))(this, 1);
        if (c == 0) return false;
    }
    WString local;
    local.mpBegin = 0; local.mpEnd = 0; local.mpCapacity = 0;
    WString_RangeInitialize(&local, name);
    WString_makeLower(&local);
    if (m_b441 == 0) ((void(__fastcall*)(void*))V(0x1c))(this);
    void** node = (void**)RbtreeFind((char*)this + 0x444, &local);
    bool r = *node != (char*)this + 0x448;
    local.DeallocateSelf();
    return r;
}

