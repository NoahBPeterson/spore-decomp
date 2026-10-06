// Slice s00933320: EA::IO::IniFile + its StackArray/string/EASTL helpers (MSVC 2008 SP1, /O2).
// Real names from the 2008 dev-build PDB are used where known; the IniFile virtual slots are called
// through the vtable by byte offset (0x1c/0x20/0x24/0x28/0x2c/0x30/0x38/0x50/0x54/0x58/0x5c).
#include "types.h"

typedef unsigned short char16_t;
typedef unsigned int uint32_t;

char gEmptyString16;
char gEmptyString16B;

void* operator new[](unsigned, const char*, int, int, int, int);
void  operator delete[](void*);
extern "C" void* __cdecl operator_new_ea(unsigned, const char*, int, int, const char*, int);
extern "C" void  __cdecl operator_delete_ea(void*);
extern "C" void* __cdecl memcpy_f(void*, const void*, unsigned);
extern "C" wchar_t* __cdecl wcsncpy_f(wchar_t*, const wchar_t*, unsigned);
extern "C" void  __cdecl FUN_004228e0(void*, unsigned);

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
    void DeallocateSelf();
    WString* Assign(const WString& s);
    void Reset();
};

// @ 0x00933960  (lib_eatext::basic_string<wchar_t>::DeallocateSelf)
void WString::DeallocateSelf() {
    char16_t* p = mpBegin;
    if ((int)((int)mpCapacity - (int)p & 0xfffffffeU) > 2 && p != 0) {
        operator delete[](p);
    }
}

// @ 0x00933850  EA::IO::IniFile::ReadEntry
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

    int   ReadEntryRaw(void* a, wchar_t* b);
    bool  WriteEntryFormatted(void* a, unsigned n, void* args);
    int   ReadBinary(void* a, void* b);
    bool  WriteBinary(void* a, unsigned n, void* b);
    bool  ConvertAndWriteStream(void* a, int n);
    bool  GetFileLine(WString* out);
    bool  GetFileLine8To8(WString* out);
    bool  GetFileLine16To16(WString* out);
    int   ReadEntry(void* a, void* b, WString* c);
    bool  SectionExists(wchar_t* name);
};

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
int IniFile::ReadBinary(void* a, void* b) {
    StackArray<wchar_t, 256> wb;
    wb.mpData = wb.mData; wb.mpDataEnd = 0; wb.mCapacity = 0x100;
    int n = ((int(__fastcall*)(void*, void*, void*, int))V(0x20))(this, a, b, 0x100);
    if (n > (int)wb.mCapacity) {
        wb.Resize(n + 1);
        ((int(__fastcall*)(void*, void*, void*, int))V(0x20))(this, a, b, n);
    }
    StackArray<char, 256> cb;
    cb.mpData = cb.mData; cb.mpDataEnd = 0; cb.mCapacity = 0x100;
    return n;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933640  EA::IO::IniFile::WriteBinary
// ---------------------------------------------------------------------------------------------
extern "C" int EA_Text_ConvertBinaryDataToASCIIArray(void*, unsigned, void*);

bool IniFile::WriteBinary(void* a, unsigned n, void* b) {
    StackArray<wchar_t, 256> buf;
    buf.mpData = buf.mData; buf.mpDataEnd = 0; buf.mCapacity = 0x100;
    unsigned need = n * 2 + 1;
    if (need > buf.mCapacity) buf.Resize(need);
    EA_Text_ConvertBinaryDataToASCIIArray(a, n, buf.mpData);
    bool r = ((bool(__fastcall*)(void*, void*, void*))V(0x2c))(this, buf.mpData, b) != 0;
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

int IniFile::ReadEntryRaw(void* a, wchar_t* b) {
    void* loc[3];
    loc[0] = &gEmptyString16; loc[1] = &gEmptyString16; loc[2] = &gEmptyString16B;
    int r = ((int(__fastcall*)(void*, void*, void*, void*))V(0x24))(this, a, b, loc);
    if (r >= 0) {
        int n = (int)(size_t)a;
        if (n > r) n = r;
        wcsncpy_f(b, (const wchar_t*)a, n);
        b[n - 1] = 0;
    }
    if ((int)((int)loc[1] - (int)loc[0] & 0xfffffffeU) > 2 && loc[0]) operator delete[](loc[0]);
    return r;
}

// ---------------------------------------------------------------------------------------------
// @ 0x009338E0  EA::IO::IniFile::ReadEntryFormatted
// ---------------------------------------------------------------------------------------------
extern "C" int Vsscanf16(void*, void*, void*);

int IniFile::ReadEntry(void* a, void* b, WString* c) {
    (void)c;
    void* loc[3];
    loc[0] = &gEmptyString16; loc[1] = &gEmptyString16; loc[2] = &gEmptyString16B;
    int r = 0;
    int rv = ((int(__fastcall*)(void*, void*, void*))V(0x24))(this, a, loc);
    if (rv != 0) {
        r = Vsscanf16(loc[0], this, b);
    }
    if ((int)((int)loc[1] - (int)loc[0] & 0xfffffffeU) > 2 && loc[0]) operator delete[](loc[0]);
    return r;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933980  EA::IO::IniFile::GetFileLine
// ---------------------------------------------------------------------------------------------
extern "C" void WString_RangeInitialize(WString*, const wchar_t*);
extern "C" int  WString_makeLower(WString*);
extern "C" int  EA_Text_ConvertEncoding8(void*, int, int, void*);

bool IniFile::GetFileLine(WString* out) {
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    int cs = EA_Text_GetCharacterSize(mEncoding);
    if (cs == 2) {
        return ((bool(__fastcall*)(void*, WString*))V(0x58))(this, out) != 0;
    }
    void* loc[3];
    loc[0] = &gEmptyString16; loc[1] = &gEmptyString16; loc[2] = &gEmptyString16B;
    char ok = (char)((int(__fastcall*)(void*, void*))V(0x54))(this, loc);
    if (ok) {
        EA_Text_ConvertEncoding8(loc[0], (int)((char*)loc[1] - (char*)loc[0]), 8, out);
        if ((int)((int)loc[1] - (int)loc[0]) > 1 && loc[0]) operator delete[](loc[0]);
        return true;
    }
    if ((int)((int)loc[1] - (int)loc[0]) > 1 && loc[0]) operator delete[](loc[0]);
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
extern "C" void CharString_append(void*, const char*, const char*);

bool IniFile::GetFileLine8To8(WString* out) {
    char buf[0x44];
    int pos = ((int(__fastcall*)(void*, int))V(0x24))(this, 0);
    bool done = false;
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    for (;;) {
        int n = ((int(__fastcall*)(void*, void*, int))V(0x30))(this, buf, 0x40);
        if (n == 0 || n == -1) break;
        int i = 0;
        for (; i < n; ++i) {
            if (buf[i] == '\r' || buf[i] == '\n') {
                done = true;
                ((void(__fastcall*)(void*, int, int))V(0x28))(this, pos + i, 0);
                for (;;) {
                    char c;
                    if (((int(__fastcall*)(void*, void*, int))V(0x30))(this, &c, 1) != 1) goto append;
                    if (c != '\r' && c != '\n') break;
                }
                ((void(__fastcall*)(void*, int, int))V(0x28))(this, -1, 1);
                goto append;
            }
        }
    append:
        CharString_append(buf, buf, buf + i);
        pos = ((int(__fastcall*)(void*, int))V(0x24))(this, 0);
        if (done) break;
    }
    return done;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933C80  EA::IO::IniFile::GetFileLine16To16
// ---------------------------------------------------------------------------------------------
extern "C" void WStr_Append(WString*, const char16_t*, const char16_t*);

bool IniFile::GetFileLine16To16(WString* out) {
    char16_t buf[0x80];
    int pos = ((int(__fastcall*)(void*, int))V(0x24))(this, 0);
    bool done = false;
    if (out->mpBegin != out->mpEnd) { *out->mpBegin = 0; out->mpEnd = out->mpBegin; }
    for (;;) {
        int n = ((int(__fastcall*)(void*, void*, int))V(0x30))(this, buf, 0x100);
        if (n == 0 || n == -1) break;
        int i = 0;
        for (; i < n; ++i) {
            if (buf[i] == '\r' || buf[i] == '\n') {
                done = true;
                ((void(__fastcall*)(void*, int, int))V(0x28))(this, pos + i, 0);
                for (;;) {
                    char16_t c;
                    if (((int(__fastcall*)(void*, void*, int))V(0x30))(this, &c, 2) != 2) goto append;
                    if (c != '\r' && c != '\n') break;
                }
                ((void(__fastcall*)(void*, int, int))V(0x28))(this, -2, 1);
                goto append;
            }
        }
    append:
        WStr_Append(out, buf, buf + i);
        pos = ((int(__fastcall*)(void*, int))V(0x24))(this, 0);
        if (done) break;
        if (mEncoding == 0x4b0) continue;
        int cnt = (int)(out->mpEnd - out->mpBegin) >> 1;
        unsigned short* q = out->mpBegin;
        for (int k = 0; k < cnt; ++k) { q[k] = (unsigned short)((q[k] >> 8) | (q[k] << 8)); }
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
extern "C" int  WString_compare(const void*, const void*);
extern "C" void* RBTreeInsert(void*, void*, void*, int);

void RbtreeInsertHelper(char* tree, void** out, char* hint, WString* key, char flag) {
    int less = 0;
    if (flag == 0 && hint != tree + 4) {
        if (WString_compare(key, hint + 0x10) >= 0) less = 1;
    }
    void* node = operator_new_ea(0x24, "EASTL", 0, 0, "EASTL/allocator.h", 0xd1);
    if (node) WString_ctor((WString*)((char*)node + 0x10), key);
    RBTreeInsert(tree + 4, hint, node, less);
    ++*(int*)(tree + 0x14);
    *out = node;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00933EF0  EA::IO::IniFile::ReadEntry
// ---------------------------------------------------------------------------------------------
int IniFile_ReadEntry(IniFile* self, WString* key, WString* out) {
    if (self->mpEncodingSrc == 0 || key == 0 || key->mpBegin == 0 || *key->mpBegin == 0) return -1;
    if (out == 0 || out->mpBegin == 0 || *out->mpBegin == 0) return -1;
    if (self->m_b442 == 0) {
        char c = (char)((int(__fastcall*)(void*, int))self->V(0x50))(self, 1);
        if (c == 0) {
            if (self->m_b441 == 0) ((void(__fastcall*)(void*))self->V(0x1c))(self);
            return -1;
        }
    }
    ((void(__fastcall*)(void*))self->V(0x1c))(self);
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

