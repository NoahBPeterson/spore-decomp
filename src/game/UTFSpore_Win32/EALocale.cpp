// src/game/UTFSpore_Win32/EALocale.cpp -- migrated from slice(s) s00881730, s0087f370, s0087e510, s0087d6d0, s0087bdc0, s0057bfb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EALocale.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cEditorResource.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cSPEditorUI.h"
#include <string.h>
#include <intrin.h>
#include <wchar.h>
#include <stdlib.h>

// ---- items of slice s0057bfb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
namespace eastl {
struct allocator_s0057_bfb0 {
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, 0, 0); }
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
template <typename T> struct EmptyStr;
}
namespace eastl {
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };
}
namespace eastl {
template <typename T>
inline T* CharStringUninitializedCopy(const T* pSource, const T* pEnd, T* pDest)
{
    memcpy(pDest, pSource, (size_t)(pEnd - pSource) * sizeof(T));
    return pDest + (pEnd - pSource);
}
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0057_bfb0>
class basic_string_s0057_bfb0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    basic_string_s0057_bfb0() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string_s0057_bfb0(const basic_string_s0057_bfb0& x);
    struct CtorDoNotInitialize {};
    basic_string_s0057_bfb0(CtorDoNotInitialize, size_t n) : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(n + 1); *mpEnd = 0; }
    basic_string_s0057_bfb0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string_s0057_bfb0() { DeallocateSelf(); }

    basic_string_s0057_bfb0& operator=(const basic_string_s0057_bfb0& x);

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    T* data() { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }

    void AllocateSelf(size_t n);
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    void RangeInitialize(const T* pBegin);
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
    basic_string_s0057_bfb0& assign(const T* pBegin, const T* pEnd);
    basic_string_s0057_bfb0& append(const T* pBegin, const T* pEnd);
    int sprintf(const char* fmt, ...);
};
}
namespace eastl {
struct fixed_vector_allocator {
    allocator_s0057_bfb0 mOverflowAllocator;
    void* mpPoolBegin;
    void deallocate(void* p) { if (p != mpPoolBegin) mOverflowAllocator.deallocate(p); }
};
}
namespace eastl {
template <typename T, int nodeCount, bool bEnableOverflow = true>
class fixed_string : public basic_string_s0057_bfb0<T, fixed_vector_allocator> {
public:
    ~fixed_string();
};
}
// ---- items of slice s0057bfb0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int FUN_0087d5d0(wchar_t* dst, int n, const wchar_t* src, const wchar_t* srcEnd);  // 0x0087d5d0 (stays in the slice: not this object's)

// ---- items of slice s0087d6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) long     __cdecl wcstol(const wchar_t*, wchar_t**, int);
extern "C" __declspec(dllimport) int      __cdecl tolower(int);
extern const wchar_t* g_localeCht[];    // 0x01548ec8
extern const wchar_t* g_localeAus[];    // 0x01548f28
extern wchar_t*       g_grpSepBegin;    // 0x016507b0
int __cdecl LocFieldToken(int idx, const wchar_t* src, wchar_t* dst, int cap, wchar_t sep);
void __cdecl LocFree(void* p);                                    // 0x00f47380
void* __cdecl LocNew(unsigned size, const char* name, int flags, int align,
                     const char* file, int line);                 // 0x00f473a0
void* __cdecl LocVecInsert(void* dst, const void* src, unsigned n);
struct LocBuf {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    LocBuf& AppendElement(const wchar_t* first, const wchar_t* last); // 0x0068cc10
    LocBuf* Assign(const wchar_t* s);                                 // 0x0087e080
};
template <int N>
struct FixedBuf {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mUnk0c;
    wchar_t* mpInline;
    wchar_t  mBuf[N];

    LocBuf& AppendElement(const wchar_t* first, const wchar_t* last);
    void ReleaseHeap()
    {
        wchar_t* p = mpBegin;
        if (((int)((char*)mpCapacity - (char*)p) & ~1) > 2 && p != 0 && p != mpInline)
            LocFree(p);
    }
};
struct LocView { wchar_t* mpBegin; wchar_t* mpEnd; };
LocBuf* LocBuf::Assign(const wchar_t* s)
{
    wchar_t* p = mpBegin;
    if (p != s) {
        if (p != mpEnd) {
            *p = 0;
            mpEnd = mpBegin;
        }
        const wchar_t* e = s;
        while (*e) ++e;
        int n = (int)(e - s);
        AppendElement(s, s + n);
    }
    return this;
}
struct LocFmt : FixedBuf<16> {
    FixedBuf<512> mSecond;   // +0x34
    LocFmt* Assign(const LocFmt* src);
};
// ---- items of slice s0087d6d0 end


// ---- items of slice s0087e510 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" wchar_t*   wcsncpy(wchar_t*, const wchar_t*, unsigned int);
extern "C" wchar_t*   _wcslwr(wchar_t*);
extern wchar_t* g_01549118;
extern wchar_t* g_0154911c;
extern wchar_t* g_0154914c;
extern wchar_t* g_01549150;
extern char    g_sentinel_01549184[];         // end() sentinel node
extern void*   g_root_01549188;               // root node pointer
extern "C" void* RBTreeIncrement(void*);      // eastl::RBTreeIncrement
extern "C" int        iswctype_s0087_e510(int, int);
void operator_delete__(void*);
template <int N>
struct LocT {
    wchar_t* f00;
    wchar_t* f04;
    wchar_t* f08;
    int      f0C;
    wchar_t* f10;
    wchar_t  buf[N];
    void AppendElement(const wchar_t* begin, const wchar_t* end);
};
typedef LocT<16>  Loc16;
typedef LocT<512> Loc512;
struct LangPrefixObj {
    Loc16 m0,  m1,  m2,  m3,  m4,  m5,  m6,  m7;
    Loc16 m8,  m9,  m10, m11, m12, m13, m14, m15;
    Loc16 m16, m17, m18, m19, m20, m21;
    Loc16 m22; char pad22[0x10];
    Loc16 m23;
    Loc512 m24, m25, m26;
};
struct LocaleFormatObj {
    int    f0;
    Loc512 big[3];
    Loc16  small[4];
};
struct RbtIter { void* node; };
struct RbtTree { RbtIter find(int* key); };  // out-of-line, at 0x5e96f0
extern RbtTree g_rbtree_01549180;             // tree object
// ---- items of slice s0087e510 end

// ---- items of slice s0087f370 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int         e_compare(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*); // 0x5e9260
extern void*       e_inc(void*);                    // 0x921580 RBTreeIncrement
extern void*       e_dec(void*);                    // 0x9215c0 RBTreeDecrement
extern void        e_opdel(void*);                  // 0xf47380
extern char        e_fieldparse(const wchar_t*, void*, int*, void*);   // 0x87d6d0
extern void*       e_f210(void*, const wchar_t*);                      // 0x87f210
extern void*       e_edd0(void*, int*);                                // 0x87edd0
extern void*       e_ee50(void*, int*);                                // 0x87ee50
extern void        e_repchar(int, int);                                // 0x68c8c0
extern char       g_end_015491a0;
template<int N>
struct Loc {
    wchar_t* f00;
    wchar_t* f04;
    wchar_t* f08;
    int      f0C;
    wchar_t* f10;
    wchar_t  buf[N];

    void AppendElement(const wchar_t* b, const wchar_t* e);   // 0x68cc10
    void append(const wchar_t* b, const wchar_t* e);          // 0x42f9d0
    void Assign(const wchar_t** key);                         // 0x87e0d0
    void FUN_0087fab0(int c);                                 // 0x87fab0

    void Release() {
        int d = (int)((char*)f08 - (char*)f00);
        if ((d & -2) > 2 && f00 != 0 && f00 != f10)
            e_opdel(f00);
    }

    void InitCap(int n) {
        wchar_t* p = buf;
        f10 = p;
        f04 = p;
        f00 = p;
        f08 = p + n;
        *p = 0;
    }

    // @ 0x0087f550
    void* FUN_0087f550(const Loc* src) {
        if (this != src) {
            if (f00 != f04) {
                *f00 = 0;
                f04 = f00;
            }
            append(src->f00, src->f04);
        }
        return this;
    }
};
template struct Loc<16>;
template struct Loc<512>;
struct Loc16Ex {
    Loc<16> s;              // +0
    int f34, f38, f3c, f40, f44, f48;
    void* FUN_0087f4f0(Loc16Ex* src);
};
struct Loc16x512 {
    Loc<16>  first;         // +0
    Loc<512> second;        // +0x34
    void* FUN_0087f580(const wchar_t** a, const wchar_t** b);
};
struct RbtNode {
    RbtNode* ch0;          // +0
    RbtNode* ch1;          // +4
    int      color;        // +8
    int      padC;         // +0xC
    Loc<16>  key;          // +0x10
    Loc<512> val;          // +0x44
};
struct RbtIter_s0087_f370 { RbtNode* node; };
struct LocaleTree {
    int   f00;             // +0
    void* sent;            // +4   (anchor; its address is the end sentinel)
    void* f08;             // +8
    void* root;            // +0xC
    int   f10;             // +0x10
    int   count;           // +0x14

    void  Clear(RbtNode* n);                                       // 0087fe10
    void  InsertNew(void** out, RbtNode* hint, const wchar_t** key, char flag);  // 0087fb40
    void  FindOrInsert(void** out, const wchar_t** key, unsigned flag);         // 0087fbe0
    void* AddOrFind(void** out, RbtNode* hint, const wchar_t** key, char flag); // 00880040
    RbtIter_s0087_f370 find(const Loc<16>* key);                                          // 0x5e96f0
};
extern LocaleTree g_tree_0154919c;
struct FmtElem {
    Loc<16> s;             // +0
    int f34;
    int f38;
    int f3c;
    int f40;
    int f44;
    int f48;
};
struct NumFmt {
    Loc<16> s;   // +0x00
    int  f34;    // +0x34
    int  f38;    // +0x38
    int  f3c;    // +0x3c
};
// ---- items of slice s0087f370 end


// ---- items of slice s00881730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t* DAT_01650540;
extern const wchar_t* DAT_01650574;
typedef unsigned short u16;
int __cdecl FUN_00881c50(double a, int b, int c, int d, const wchar_t* fmt);
int __cdecl FtoaEnglish16(double a, u16* buf, int n, int radix, int flags);
extern "C" __declspec(dllimport) int __cdecl iswctype_s0088_1730(u16 c, int type);
void __cdecl FUN_00881f30(u16* a, u16* b, int c, int d, int e, int f);
// ---- items of slice s00881730 end

// @ 0x0057cb80
template <> eastl::fixed_string<wchar_t, 16, true>::~fixed_string()
{
}







// @ 0x0087d620
int FUN_0087d620(int limit, const wchar_t* str, wchar_t* dst, int cap, wchar_t sep)
{
    int i = 0;
    short sVar3;
    short* psVar4 = (short*)str - 1;
    short* psVar1 = 0;
    do {
        sVar3 = psVar4[1];
        psVar1 = psVar4 + 1;
        psVar4 = psVar1;
        while (sVar3 != 0 && sVar3 != (short)sep) {
            short* psVar2 = psVar4 + 1;
            psVar4 = psVar4 + 1;
            sVar3 = *psVar2;
        }
        i++;
    } while (*psVar4 != 0 && i <= limit);
    i--;
    if (i != limit) return -1;
    return FUN_0087d5d0(dst, cap, (const wchar_t*)psVar1, (const wchar_t*)psVar4);
}







// @ 0x0087d690
int FUN_0087d690(int limit, const wchar_t* str, wchar_t sep)
{
    wchar_t buf[128];
    FUN_0087d620(limit, str, buf, 0x80, sep);
    return (int)wcstol(buf, 0, 10);
}






// @ 0x0087d9a0
int Locale_MakeLocaleAvailable(const LocView* a, const LocView* b)
{
    const int* pa = (const int*)a->mpBegin;
    const int* pb = (const int*)b->mpBegin;
    int n = (int)(a->mpEnd - a->mpBegin);
    if (n != (int)(b->mpEnd - b->mpBegin))
        return 0;
    unsigned m = (unsigned)n * 2;
    while (m > 3) {
        if (*pa != *pb) return 0;
        m -= 4;
        ++pa;
        ++pb;
    }
    if (m == 0) return 1;
    const char* ca = (const char*)pa;
    const char* cb = (const char*)pb;
    if (ca[0] != cb[0]) return 0;
    if (m <= 1) return 1;
    if (ca[1] != cb[1]) return 0;
    if (m <= 2) return 1;
    if (ca[2] != cb[2]) return 0;
    return 1;
}


// @ 0x0087db80
int Locale_FindInCht(const wchar_t* name, wchar_t* out, int cap)
{
    for (const wchar_t** pp = g_localeCht; *pp; ++pp) {
        wchar_t a[0x20];
        wchar_t b[0x20];
        LocFieldToken(0, *pp, b, 0x20, L'^');
        int n = LocFieldToken(0, b, a, 0x20, L',');
        int i = 0;
        while (n > 0) {
            i++;
            if (_wcsicmp(a, name) == 0)
                return LocFieldToken(1, *pp, out, cap, L'^');
            n = LocFieldToken(i, b, a, 0x20, L',');
        }
    }
    return -1;
}


// @ 0x0087dc40
const wchar_t* Locale_FindByShortName(const wchar_t** table, const LocView* name)
{
    const wchar_t* s = *table;
    for (;;) {
        if (s == 0) return 0;
        wchar_t buf[0x80];
        int n = LocFieldToken(0, s, buf, 0x80, L'^');
        if (n < 0x80) {
            const uint16_t* q = (const uint16_t*)name->mpBegin;
            const uint16_t* p = (const uint16_t*)buf;
            int cmp;
            for (;;) {
                uint16_t c = *p;
                if (c != *q) { cmp = (c < *q) ? -1 : 1; break; }
                if (c == 0)  { cmp = 0; break; }
                c = p[1];
                if (c != q[1]) { cmp = (c < q[1]) ? -1 : 1; break; }
                p += 2;
                q += 2;
                if (c == 0) { cmp = 0; break; }
            }
            if (cmp == 0) return *table;
        }
        s = table[1];
        ++table;
    }
}


// @ 0x0087e080
LocFmt* LocFmt::Assign(const LocFmt* src)
{
    mpInline   = mBuf;
    mpCapacity = mBuf + 16;
    mpBegin    = mBuf;
    mpEnd      = mBuf;
    *mpBegin   = 0;
    AppendElement(src->mpBegin, src->mpEnd);

    mSecond.mpInline   = mSecond.mBuf;
    mSecond.mpCapacity = mSecond.mBuf + 512;
    mSecond.mpBegin    = mSecond.mBuf;
    mSecond.mpEnd      = mSecond.mBuf;
    *mSecond.mpBegin   = 0;
    mSecond.AppendElement(src->mSecond.mpBegin, src->mSecond.mpEnd);
    return this;
}


// @ 0x0087e230
uint32_t Locale_FindLower(const wchar_t* name, wchar_t* out, int cap)
{
    for (const wchar_t** pp = g_localeAus; *pp; ++pp) {
        wchar_t  a[0x20];
        wchar_t  b[0x20];
        LocFieldToken(0, *pp, a, 0x20, L'^');
        int idx = 0;
        int n = LocFieldToken(0, a, b, 0x20, L',');
        while (n > 0) {
            ++idx;
            if (_wcsicmp(b, name) == 0)
                return LocFieldToken(1, *pp, out, cap, L'^');

            wchar_t taiwan[8];
            taiwan[0] = (wchar_t)(0x59d3 ^ 0x59a7);
            taiwan[1] = (wchar_t)(0x59c6 ^ 0x59a7);
            taiwan[2] = (wchar_t)(0x59ce ^ 0x59a7);
            taiwan[3] = (wchar_t)(0x59d0 ^ 0x59a7);
            taiwan[4] = (wchar_t)(0x59c6 ^ 0x59a7);
            taiwan[5] = (wchar_t)(0x59c9 ^ 0x59a7);
            taiwan[6] = 0;

            const wchar_t* e = b;
            while (*e) ++e;
            int blen = (int)(e - b);

            uint16_t* buf;
            uint16_t* bufEnd;
            if ((unsigned)(blen + 1) < 2) {
                buf    = (uint16_t*)g_grpSepBegin; // unused fallback (inline vec)
                bufEnd = (uint16_t*)g_grpSepBegin + 1;
            } else {
                buf = (uint16_t*)LocNew((blen + 1) * 2, "EASTL", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                        0xd1);
                bufEnd = buf + (blen + 1);
            }
            LocVecInsert(buf, b, (unsigned)blen * 2);
            buf[blen] = 0;
            for (uint16_t* q = buf; q < buf + blen; ++q) {
                uint16_t c = *q;
                if (c < 0x100) c = (uint16_t)tolower(c & 0xff);
                *q = c;
            }

            const wchar_t* te = taiwan;
            while (*te) ++te;
            if (blen != 0 && buf != bufEnd) {
                for (uint16_t* q = buf; ; ++q) {
                    for (const uint16_t* t = (const uint16_t*)taiwan;
                         t != (const uint16_t*)te; ++t) {
                        if (*q == *t) {
                            int at = (int)(q - buf);
                            if (at != -1 && _wcsicmp((wchar_t*)(buf + at), name) == 0) {
                                uint32_t r = LocFieldToken(1, *pp, out, cap, L'^');
                                if (((int)((char*)bufEnd - (char*)buf) & ~1) > 2 && buf != 0)
                                    LocFree(buf);
                                return r;
                            }
                            break;
                        }
                    }
                    if (++q == bufEnd) break;
                }
            }
            if (((int)((char*)bufEnd - (char*)buf) & ~1) > 2 && buf != 0)
                LocFree(buf);
            n = LocFieldToken(idx, a, b, 0x20, L',');
        }
    }
    return (uint32_t)-1;
}


// @ 0x0087e510
LangPrefixObj* __fastcall FUN_0087e510(LangPrefixObj* self)
{
    wchar_t* b;
#define INIT16(m) do { b = (m).buf; (m).f10 = b; (m).f04 = b; (m).f00 = b; (m).f08 = b + 16; b[0] = 0; } while (0)
#define INIT512(m) do { b = (m).buf; (m).f10 = b; (m).f04 = b; (m).f00 = b; (m).f08 = b + 512; b[0] = 0; } while (0)
    INIT16(self->m0);  INIT16(self->m1);  INIT16(self->m2);  INIT16(self->m3);
    INIT16(self->m4);  INIT16(self->m5);  INIT16(self->m6);  INIT16(self->m7);
    INIT16(self->m8);  INIT16(self->m9);  INIT16(self->m10); INIT16(self->m11);
    INIT16(self->m12); INIT16(self->m13); INIT16(self->m14); INIT16(self->m15);
    INIT16(self->m16); INIT16(self->m17); INIT16(self->m18); INIT16(self->m19);
    INIT16(self->m20); INIT16(self->m21); INIT16(self->m22); INIT16(self->m23);
    INIT512(self->m24); INIT512(self->m25); INIT512(self->m26);
#undef INIT16
#undef INIT512
    return self;
}





// @ 0x0087e8f0
void __fastcall FUN_0087e8f0(LangPrefixObj* self)
{
#define DESTROY(m) do { wchar_t* s = (m).f00; int d = (int)((char*)(m).f08 - (char*)s); \
        if (2 < (d & -2) && s != 0 && s != (m).f10) operator_delete__(s); } while (0)
    DESTROY(self->m26); DESTROY(self->m25); DESTROY(self->m24);
    DESTROY(self->m23); DESTROY(self->m22);
    DESTROY(self->m21); DESTROY(self->m20); DESTROY(self->m19); DESTROY(self->m18);
    DESTROY(self->m17); DESTROY(self->m16); DESTROY(self->m15); DESTROY(self->m14);
    DESTROY(self->m13); DESTROY(self->m12); DESTROY(self->m11); DESTROY(self->m10);
    DESTROY(self->m9);  DESTROY(self->m8);  DESTROY(self->m7);  DESTROY(self->m6);
    DESTROY(self->m5);  DESTROY(self->m4);  DESTROY(self->m3);  DESTROY(self->m2);
    DESTROY(self->m1);  DESTROY(self->m0);
#undef DESTROY
}





// @ 0x0087ed70
void* FUN_0087ed70(Loc16* dst, int* src)
{
    int iVar2 = src[0];
    int iVar3 = src[1];
    wchar_t* p = dst->buf;
    dst->f10 = p;
    dst->f04 = p;
    dst->f00 = p;
    if ((unsigned)((iVar3 - iVar2) >> 1) >= 2) {
        dst->f08 = p + 16;
        *p = 0;
        dst->AppendElement((const wchar_t*)iVar2, (const wchar_t*)(iVar2 + 4));
        return dst;
    }
    dst->f08 = p + 16;
    *p = 0;
    dst->AppendElement(g_01549118, g_0154911c);
    return dst;
}





// @ 0x0087edd0
void* FUN_0087edd0(Loc16* dst, int* src)
{
    int begin = src[0];
    unsigned len = (unsigned)((src[1] - begin) >> 1);
    wchar_t* p;
    if (len >= 5) {
        p = dst->buf;
        dst->f10 = p;
        begin += 6;
        dst->f04 = p;
        dst->f00 = p;
    } else {
        p = dst->buf;
        dst->f10 = p;
        dst->f04 = p;
        dst->f00 = p;
        if (len < 2) {
            dst->f08 = p + 16;
            *p = 0;
            dst->AppendElement(g_0154914c, g_01549150);
            return dst;
        }
    }
    dst->f08 = p + 16;
    *p = 0;
    dst->AppendElement((const wchar_t*)begin, (const wchar_t*)(begin + 4));
    return dst;
}





// @ 0x0087ee50
namespace EA { namespace Locale {
void* GetClosestLanguageId(void* dst_, int* key)
{
    Loc16* dst = (Loc16*)dst_;
    wchar_t empty[16];
    empty[0] = 0;
    RbtIter it = g_rbtree_01549180.find(key);
    if (it.node == (void*)g_sentinel_01549184) {
        if (((key[1] - key[0]) & -2) == 4) {
            wchar_t* b = dst->buf;
            dst->f10 = b; dst->f04 = b; dst->f00 = b; dst->f08 = b + 16; *b = 0;
            dst->AppendElement((const wchar_t*)key[0], (const wchar_t*)key[1]);
        } else {
            Loc16 tmp;
            FUN_0087ed70(&tmp, key);
            void* node = g_root_01549188;
            while (node != (void*)g_sentinel_01549184) {
                Loc16 s;
                wchar_t* sb = s.buf;
                s.f10 = sb; s.f04 = sb; s.f00 = sb; s.f08 = sb + 16; *sb = 0;
                s.AppendElement((const wchar_t*)((void**)node)[4], (const wchar_t*)((void**)node)[5]);
                if (s.buf[0] == ((wchar_t*)tmp.f00)[0] && s.buf[1] == ((wchar_t*)tmp.f00)[1]) {
                    { int d=(int)((char*)s.f08-(char*)s.f00); if (2<(d&-2)&&s.f00&&s.f00!=s.f10) operator_delete__(s.f00); }
                    if (node != (void*)g_sentinel_01549184) {
                        wchar_t* b = dst->buf;
                        dst->f10 = b; dst->f04 = b; dst->f00 = b; dst->f08 = b + 16; *b = 0;
                        dst->AppendElement((const wchar_t*)((void**)node)[4], (const wchar_t*)((void**)node)[5]);
                        { int d=(int)((char*)tmp.f08-(char*)tmp.f00); if (2<(d&-2)&&tmp.f00&&tmp.f00!=tmp.f10) operator_delete__(tmp.f00); }
                        return dst;
                    }
                    break;
                }
                { int d=(int)((char*)s.f08-(char*)s.f00); if (2<(d&-2)&&s.f00&&s.f00!=s.f10) operator_delete__(s.f00); }
                node = RBTreeIncrement(node);
            }
            wchar_t* b = dst->buf;
            dst->f10 = b; dst->f04 = b; dst->f00 = b; dst->f08 = b + 16; *b = 0;
            dst->AppendElement(empty, empty);
            { int d=(int)((char*)tmp.f08-(char*)tmp.f00); if (2<(d&-2)&&tmp.f00&&tmp.f00!=tmp.f10) operator_delete__(tmp.f00); }
        }
    } else {
        wchar_t* b = dst->buf;
        dst->f10 = b; dst->f04 = b; dst->f00 = b; dst->f08 = b + 16; *b = 0;
        dst->AppendElement((const wchar_t*)key[0], (const wchar_t*)key[1]);
    }
    return dst;
}
}}  // namespace EA::Locale





// @ 0x0087f100
LocaleFormatObj* __fastcall FUN_0087f100(LocaleFormatObj* self)
{
    wchar_t* b;
#define INIT16(m)  do { b = (m).buf; (m).f10 = b; (m).f04 = b; (m).f00 = b; (m).f08 = b + 16;  b[0] = 0; } while (0)
#define INIT512(m) do { b = (m).buf; (m).f10 = b; (m).f04 = b; (m).f00 = b; (m).f08 = b + 512; b[0] = 0; } while (0)
    INIT512(self->big[0]);
    INIT512(self->big[1]);
    INIT512(self->big[2]);
    INIT16(self->small[0]);
    INIT16(self->small[1]);
    INIT16(self->small[2]);
    INIT16(self->small[3]);
#undef INIT16
#undef INIT512
    return self;
}





// @ 0x0087f210
void* FUN_0087f210(Loc16* dst, const wchar_t* src)
{
    wchar_t buf[6] = {0};
    const wchar_t* p = src;
    wchar_t c;
    do { c = *p; p++; } while (c != 0);
    unsigned count = (unsigned)((int)p - (int)(src + 1)) >> 1;
    if (count != 0) {
        if (count == 2 || count == 5) {
            wcsncpy(buf, src, count);
            buf[count] = 0;
        } else if (count > 2) {
            if (src[2] == L'-') {
                if (count > 4 && iswctype_s0087_e510(src[3], 0x103) != 0 &&
                    iswctype_s0087_e510(src[4], 0x103) != 0) {
                    wcsncpy(buf, src, 5);
                    buf[5] = 0;
                }
            } else {
                wcsncpy(buf, src, 2);
                buf[2] = 0;
            }
        }
    }
    if (buf[0] != 0) _wcslwr(buf);
    wchar_t* b = dst->buf;
    dst->f10 = b;
    dst->f04 = b;
    dst->f00 = b;
    dst->f08 = b + 16;
    *b = 0;
    const wchar_t* q = buf;
    while (*q != 0) q++;
    dst->AppendElement(buf, q);
    return dst;
}





// @ 0x0087f350
void* FUN_0087f350(Loc16* dst, wchar_t** src)
{
    FUN_0087f210(dst, *src);
    return dst;
}




// @ 0x0087f370
namespace EA { namespace Locale {
char LocaleFormatter_UpdateFormatElements(FmtElem* dst, int count, const wchar_t* str)
{
    if (str == 0)
        return 1;
    FmtElem arr[16];
    for (int i = 0; i < 16; ++i)
        arr[i].s.InitCap(16);
    int n = 0x10;
    int local4 = 0;
    if (!e_fieldparse(str, arr, &n, &local4)) {
        for (int i = 15; i >= 0; --i)
            arr[i].s.Release();
        return 0;
    }
    if (n > 0) {
        FmtElem* e = arr;
        int cnt = n;
        do {
            if (count > 0) {
                int k = e->f38;
                FmtElem* d = dst;
                int m = count;
                do {
                    if (d->f38 == k) {
                        d->f3c = e->f3c;
                        d->f40 = e->f40;
                        d->f34 = (d->f34 & 0x38) | e->f34;
                    }
                    d = (FmtElem*)((char*)d + 0x4c);
                    --m;
                } while (m != 0);
            }
            e = (FmtElem*)((char*)e + 0x4c);
            --cnt;
        } while (cnt != 0);
        n = 0;
    }
    for (int i = 15; i >= 0; --i)
        arr[i].s.Release();
    return 1;
}
}}  // namespace EA::Locale

// @ 0x0087f4f0
void* Loc16Ex::FUN_0087f4f0(Loc16Ex* src)
{
    wchar_t* p = s.buf;
    s.f10 = p;
    s.f08 = p + 16;
    s.f04 = p;
    s.f00 = p;
    *p = 0;
    s.AppendElement(src->s.f00, src->s.f04);
    f34 = src->f34;
    f38 = src->f38;
    f3c = src->f3c;
    f40 = src->f40;
    f44 = src->f44;
    f48 = src->f48;
    return this;
}

// @ 0x0087f580
void* Loc16x512::FUN_0087f580(const wchar_t** a, const wchar_t** b)
{
    first.InitCap(16);
    first.AppendElement(a[0], a[1]);
    second.InitCap(512);
    second.append(b[0], b[1]);
    return this;
}

// @ 0x0087f5e0
namespace EA { namespace Locale {
bool IsLocaleAvailable(int* param_1)
{
    Loc<16> la;
    Loc<16> lb;
    e_f210(&la, (const wchar_t*)*param_1);
    e_edd0(&lb, (int*)&la);
    RbtIter_s0087_f370 it = g_tree_0154919c.find(&lb);
    bool found = (it.node == (RbtNode*)&g_end_015491a0);
    lb.Release();
    if (found) {
        la.Release();
        return false;
    }
    void* pc = e_ee50(&lb, (int*)&la);
    int i3 = ((int*)pc)[0];
    int i1 = ((int*)pc)[1];
    lb.Release();
    if (i3 != i1) {
        la.Release();
        return true;
    }
    la.Release();
    return false;
}
}}  // namespace EA::Locale

// @ 0x0087fbe0
void LocaleTree::FindOrInsert(void** out, const wchar_t** key, unsigned flag)
{
    (void)flag;
    RbtNode* bEnd = (RbtNode*)((char*)this + 4);
    RbtNode* puVar8 = bEnd;
    bool bVar9 = true;
    RbtNode* rootNode = (RbtNode*)root;
    if (rootNode != 0) {
        int local_8 = (int)((char*)key[1] - (char*)key[0]) >> 1;
        RbtNode* puVar5 = rootNode;
        do {
            puVar8 = puVar5;
            const unsigned short* puVar6 = (const unsigned short*)puVar8->key.f00;
            int local_c = (int)((char*)puVar8->key.f04 - (char*)puVar8->key.f00) >> 1;
            int m = local_8 <= local_c ? local_8 : local_c;
            const unsigned short* puVar3 = (const unsigned short*)key[0];
            unsigned uVar4 = 0;
            int iVar7 = m;
            for (; iVar7 != 0; --iVar7) {
                if (*puVar3 != *puVar6) {
                    uVar4 = (-(unsigned)(*puVar3 < *puVar6) & 0xfffffffe) + 1;
                    if (uVar4 != 0)
                        goto LAB;
                    break;
                }
                ++puVar3;
                ++puVar6;
            }
            uVar4 = (local_8 < local_c) ? 0xffffffffu : (unsigned)(local_c < local_8);
        LAB:
            bVar9 = (int)uVar4 < 0;
            puVar5 = bVar9 ? (RbtNode*)puVar8->ch1 : (RbtNode*)puVar8->ch0;
        } while (puVar5 != 0);
    }
    RbtNode* puVar5b = puVar8;
    if (bVar9) {
        if (puVar8 == (RbtNode*)f08)
            goto LAB2;
        puVar5b = (RbtNode*)e_dec(puVar8);
    }
    if (e_compare(puVar5b->key.f00, puVar5b->key.f04, key[0], key[1]) >= 0) {
        *out = puVar5b;
        ((char*)out)[4] = 0;
        return;
    }
LAB2:
    {
        void* tmp;
        InsertNew(&tmp, puVar8, key, 0);
        *out = tmp;
        ((char*)out)[4] = 1;
    }
}

// @ 0x0087fe10
void LocaleTree::Clear(RbtNode* n)
{
    while (n != 0) {
        Clear(n->ch0);
        RbtNode* next = n->ch1;
        n->val.Release();
        n->key.Release();
        e_opdel(n);
        n = next;
    }
}

// @ 0x0087fe90
Loc<16>* FUN_0087fe90(Loc<16>* param_1, Loc<16>* param_2, Loc<16>* param_3)
{
    Loc<16> local;
    local.InitCap(16);
    local.AppendElement(param_2->f00, param_2->f04);
    if (((int)((char*)param_2->f04 - (char*)param_2->f00) & -2) == 10) {
        param_1->InitCap(16);
        param_1->AppendElement(local.f00, local.f04);
    } else {
        local.FUN_0087fab0(0x2d);
        local.AppendElement(param_3->f00, param_3->f04);
        param_1->f10 = param_1->buf;
        param_1->f08 = param_1->buf + 16;
        param_1->f04 = param_1->buf;
        param_1->f00 = param_1->buf;
        param_1->buf[0] = 0;
        param_1->AppendElement(local.f00, local.f04);
    }
    local.Release();
    return param_1;
}

// @ 0x0087ff90
char FUN_0087ff90(Loc<16>* param_1, NumFmt* param_2)
{
    wchar_t* psVar5 = param_2->s.f00;
    wchar_t* psVar1 = (wchar_t*)((char*)psVar5 + ((int)((char*)param_2->s.f04 - (char*)psVar5) >> 1) * 2);
    if (psVar5 == 0)
        return 0;
    if (param_2->f3c < 0) {
        param_1->AppendElement(psVar5, psVar1);
        return 1;
    }
    if (*psVar5 == 0x2d) {
        e_repchar(1, 0x2d);
        psVar5 += 1;
    }
    unsigned uVar2 = (unsigned)param_2->f3c;
    int iVar4 = (int)uVar2 >> 31;
    unsigned uVar3 = (unsigned)((int)((char*)psVar1 - (char*)psVar5) >> 1);
    wchar_t* end;
    if ((iVar4 < 0) ||
        ((iVar4 == 0 && uVar2 <= uVar3) || ((param_2->f34 & 2) == 0))) {
        end = psVar1;
        if (iVar4 == 0 && uVar2 < uVar3)
            end = psVar5 + uVar2;
    } else {
        e_repchar((int)(uVar2 - uVar3), 0x30);
        end = psVar1;
    }
    param_1->AppendElement(psVar5, end);
    return 1;
}

// @ 0x00880040
void* LocaleTree::AddOrFind(void** out, RbtNode* hint, const wchar_t** key, char flag)
{
    (void)flag;
    RbtNode* bEnd = (RbtNode*)((char*)this + 4);
    RbtNode* e = (RbtNode*)sent;
    if (hint == e || hint == bEnd) {
        if (count != 0 &&
            e_compare(e->key.f00, e->key.f04, key[0], key[1]) < 0) {
            InsertNew(out, e, key, 0);
            return out;
        }
        void* local_8[2];
        FindOrInsert(local_8, key, (unsigned)(size_t)key & 0xffffff00u);
        *out = local_8[0];
        return out;
    }
    RbtNode* nxt = (RbtNode*)e_inc(hint);
    if (e_compare(hint->key.f00, hint->key.f04, key[0], key[1]) < 0 &&
        e_compare(key[0], key[1], nxt->key.f00, nxt->key.f04) < 0) {
        int f = hint->ch0 != 0;
        RbtNode* ins = f ? nxt : hint;
        InsertNew(out, ins, key, (char)f);
        return out;
    }
    void* local_8[2];
    FindOrInsert(local_8, key, (unsigned)(size_t)key & 0xffffff00u);
    *out = local_8[0];
    return out;
}

// @ 0x00881730
__declspec(noinline) int FUN_00881730(void)
{
    return 0;
}



// @ 0x00881ae0
__declspec(noinline) int FUN_00881ae0(void)
{
    return 0;
}



// @ 0x00881c50
__declspec(noinline) int FUN_00881c50(double a, int b, int c, int d, const wchar_t* fmt)
{
    static volatile int sink;
    sink = (int)a + b + c + d + (fmt != 0);
    return sink;
}



// @ 0x00881ea0
void __cdecl FUN_00881ea0(double a, int b, int c, int d)
{
    FUN_00881c50(a, b, c, d, L"%N%?p%?2F");
}



// @ 0x00881ed0
void __cdecl FUN_00881ed0(double a, int b, int c, int d)
{
    FUN_00881c50(a, b, c, d, DAT_01650540);
}



// @ 0x00881f00
void __cdecl FUN_00881f00(double a, int b, int c, int d)
{
    FUN_00881c50(a, b, c, d, DAT_01650574);
}



// @ 0x00881f30
__declspec(noinline) void FUN_00881f30(u16* a, u16* b, int c, int d, int e, int f)
{
    static volatile int sink;
    sink = (a != 0) + (b != 0) + c + d + e + f;
}



// @ 0x008822e0
void __cdecl FUN_008822e0(double a, int p2, int p3, int p4, int p5)
{
    u16 buf[128];
    FtoaEnglish16(a, buf, 0x80, 10, 0);
    u16* p = buf;
    for (;;) {
        u16 c = *p;
        if (c != 0x2d && c != 0x2b) {
            if (iswctype_s0088_1730(c, 4) == 0) {
                u16* q = p + 1;
                if (*p == 0)
                    q = p;
                *p = 0;
                FUN_00881f30(buf, q, p2, p3, p4, p5);
                return;
            }
        }
        ++p;
    }
}



// @ 0x00882380
__declspec(noinline) int FUN_00882380(void* a, int b)
{
    (void)a; (void)b;
    return 0;
}
