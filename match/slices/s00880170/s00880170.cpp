// Slice s00880170 (0x880170..0x8808c8) - EA::Locale formatting / locale-data lookups.
//
// 00880610 is an eastl::map<fixed_string<wchar_t,16>,fixed_string<wchar_t,512>>::operator[]
// instantiation: reproduced byte-exact by including the vendored EASTL headers and explicitly
// instantiating the map type.
// 00880750 / 00880830 are the country/language data-string lookups.
// 008804d0 / 00880170 are the format-element renderer and its string-append driver (partial).
//
// Flags: /O2 /MD /GS- /GR- /TP /Iscratch_s00880170_inc (vendored EASTL/EAWebKit headers).

#include "types.h"

// Vendored EAWebKit build configuration (kept in-source so manifest flags stay short).
#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

// ---------------------------------------------------------------------------
// EASTL instantiation for 00880610
// ---------------------------------------------------------------------------
#include <EASTL/fixed_string.h>
#include <EASTL/map.h>

typedef eastl::fixed_string<wchar_t, 16, 1>  LocKey16;
typedef eastl::fixed_string<wchar_t, 512, 1> LocVal512;
template class eastl::map<LocKey16, LocVal512, eastl::less<LocKey16>, eastl::allocator>;

// ---------------------------------------------------------------------------
// Locale helpers (out of slice; relocations are masked by the verifier)
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) wchar_t* __cdecl wcsncpy(wchar_t*, const wchar_t*, size_t);
extern "C" void __cdecl LocFree(void* p);                                            // 0xf47380
extern "C" void __cdecl MakeCountryKey(void* out, const void* view);                 // 0x87edd0
extern "C" void __cdecl MakeLanguageKey(void* out, const void* view);                // 0x87ed70
extern "C" int  __cdecl LocFieldToken(int idx, const wchar_t* src, wchar_t* dst, int cap, wchar_t sep); // 0x87d620
extern "C" void __cdecl LocAppendView(void* out, const void* view);                  // 0x87e060
extern "C" void __cdecl LocFormatGrouped(void* out, void* spec, char noSign);        // 0x87deb0
extern "C" void __cdecl LocFormatRaw(void* out, void* spec);                         // 0x87ff90
extern "C" void __cdecl LocFormatAssign(void* spec);                                 // 0x87f4f0
extern "C" void __cdecl LocNumFormat(void* out, void* spec);                         // 0x87dce0
extern "C" void __cdecl LocFormatField(void* out, void* dst, void* spec, void* prev, void* next); // 0x880170
extern "C" void __cdecl LocFormatInt(void* out, int width);                          // 0x68c8c0
extern "C" void __cdecl LocAppendElem(const wchar_t* first, const wchar_t* last);    // 0x68cc10
extern "C" void __cdecl LocWStrAssign(void* dst, const wchar_t* src);                // 0x696320
extern "C" void __cdecl LocMakeUnsigned(void* dst, const wchar_t* src);              // 0x87dce0

// fixed_string<wchar_t,16,1> storage: basic_string base (0x14) + 16-wchar inline buffer.
struct FixedStr16 {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    void*    mAlloc;       // +0x0c
    wchar_t* mpPoolBegin;  // +0x10
    wchar_t  mBuf[16];     // +0x14

    void ReleaseHeap()
    {
        wchar_t* p = mpBegin;
        if (((int)((char*)mpCapacity - (char*)p) & ~1) > 2 && p != 0 && p != mpPoolBegin)
            LocFree(p);
    }
};

struct LocValView { wchar_t* mpBegin; wchar_t* mpEnd; };
struct LocMapObj {
    LocValView* Get(const FixedStr16* key);   // 0x880610 (map::operator[])
};

extern LocMapObj g_countryMap;   // 0x154919c
extern LocMapObj g_languageMap;  // 0x1549180

// @ 0x00880610
// (emitted by the explicit eastl::map instantiation above)

// @ 0x00880750
int __cdecl EA_Locale_GetCountryDataString(const FixedStr16* src, int field, bool direct,
                                           const void* keyView, wchar_t* out, size_t cap)
{
    if (direct) {
        wcsncpy(out, src->mpBegin, cap);
        out[cap - 1] = L'\0';
        return (int)((char*)src->mpEnd - (char*)src->mpBegin) >> 1;
    }
    FixedStr16 key;
    MakeCountryKey(&key, keyView);
    LocValView* val = g_countryMap.Get(&key);
    if (val->mpBegin != val->mpEnd) {
        int r = LocFieldToken(field, val->mpBegin, out, (int)cap, L'^');
        key.ReleaseHeap();
        return r;
    }
    key.ReleaseHeap();
    return -1;
}

// @ 0x00880830
int __cdecl EA_Locale_GetLanguageDataString(const FixedStr16* src, int field, bool direct,
                                            const void* keyView, wchar_t* out, size_t cap)
{
    if (direct) {
        wcsncpy(out, src->mpBegin, cap);
        out[cap - 1] = L'\0';
        return (int)((char*)src->mpEnd - (char*)src->mpBegin) >> 1;
    }
    FixedStr16 key;
    MakeLanguageKey(&key, keyView);
    LocValView* val = g_languageMap.Get(&key);
    if (val->mpBegin != val->mpEnd) {
        int r = LocFieldToken(field, val->mpBegin, out, (int)cap, L'^');
        key.ReleaseHeap();
        return r;
    }
    key.ReleaseHeap();
    return -1;
}

// ---------------------------------------------------------------------------
// 00880170 / 008804d0: EA::Locale format-element rendering
// ---------------------------------------------------------------------------
struct LocScan { wchar_t* cur; unsigned len; };           // remaining-text cursor (ptr, wchar count)

struct LocElem {                                          // 0x4c-byte format element
    int      f0, f1;
    char     pad0[0x34 - 8];
    unsigned flags;                                       // +0x34
    int      type;                                        // +0x38
    int      pad3c;
    int      width;                                       // +0x40
    wchar_t* limit;                                       // +0x44
    wchar_t* last;                                        // +0x48
};

struct LocStr16 {                                         // fixed_string<wchar_t,16,1>
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; void* mAlloc; wchar_t* mpPool; wchar_t mBuf[16];
    void __thiscall AppendElement(const wchar_t* first, const wchar_t* last);   // 0x68cc10
    void __thiscall FillN(int n, wchar_t c);                                     // 0x68c8c0
    void __thiscall AssignLit(const wchar_t* s);                                 // 0x696320
    void __thiscall DeallocateSelf();                                            // 0x57cb80
    void Free()
    {
        wchar_t* p = mpBegin;
        if (((int)((char*)mpCapacity - (char*)p) & ~1) > 2 && p != 0 && p != mpPool)
            LocFree(p);
    }
};
struct LocState : LocStr16 {                              // built by 0x87f4f0 from an element
    int pad[2];
    int width;                                            // +0x3c
    void __thiscall Init(LocElem* e);                     // 0x87f4f0
    void __thiscall AssignNum(const wchar_t* s);          // 0x87dce0
};
extern "C" void __cdecl LocFmtGrouped(LocStr16* out, LocElem* e, int neg);   // 0x87deb0
extern "C" void __cdecl LocFmtRaw(LocStr16* out, LocElem* e);                // 0x87ff90
extern "C" void __cdecl LocFmtView(LocStr16* out, LocElem* e);               // 0x87e060
extern const wchar_t g_locLit0c[];  // 0x165077c
extern const wchar_t g_locLit0d[];  // 0x16507e4
extern const wchar_t g_locLit0e[];  // 0x14278e0

// @ 0x00880170
bool __cdecl EA_Locale_FormatElement(LocStr16* out, LocScan* v, LocElem* e, LocElem* prev, LocElem* next)
{
    LocState st;
    LocStr16 s;
    unsigned flags = e->flags;
    wchar_t* limit = e->limit;
    wchar_t* cur = v->cur;
    if (flags & 0x20) {
        if (cur < limit) {
            if (!(flags & 0x10))
                out->AppendElement(cur, limit);
            v->len -= (int)((char*)e->last - (char*)v->cur + 2) >> 1;
            v->cur = (wchar_t*)((char*)e->last + 2);
        }
        if (v->len == 0 || *v->cur == 0)
            return true;
        wchar_t* stop;
        if (next)
            stop = next->limit;
        else
            stop = v->cur + v->len;
        if (v->cur >= stop)
            return true;
        if (e->flags & 8) {
            if (next) {
                v->len -= (int)((char*)next->last - (char*)v->cur + 2) >> 1;
                v->cur = (wchar_t*)((char*)next->last + 2);
                return true;
            }
            v->cur = v->cur + v->len;
            v->len = 0;
            return true;
        }
        v->len -= (int)((char*)e->last - (char*)v->cur + 2) >> 1;
        v->cur = (wchar_t*)((char*)e->last + 2);
        return true;
    }
    if (cur < limit) {
        out->AppendElement(cur, limit);
        v->len -= (int)((char*)e->last - (char*)v->cur + 2) >> 1;
        v->cur = (wchar_t*)((char*)e->last + 2);
    }
    switch (e->type) {
    case 1:
        LocFmtGrouped(out, e, 0);
        break;
    case 2: case 3:
        LocFmtGrouped(out, e, 1);
        break;
    case 4: case 5: case 6: case 7: case 0xb:
        LocFmtRaw(out, e);
        break;
    case 8:
        LocFmtView(out, e);
        break;
    case 9: case 10:
        if (e->flags & 0x40)
            LocFmtRaw(out, e);
        else
            LocFmtView(out, e);
        break;
    case 0xc:
        if (e->f0 != e->f1) {
            LocFmtView(out, e);
        } else {
            st.Init(e);
            st.AssignLit(g_locLit0c);
            out->AppendElement(st.mpBegin, st.mpEnd);
            st.DeallocateSelf();
        }
        break;
    case 0xd:
        st.Init(e);
        st.AssignLit(g_locLit0d);
        out->AppendElement(st.mpBegin, st.mpEnd);
        st.DeallocateSelf();
        break;
    case 0xe:
        st.Init(e);
        st.AssignNum(g_locLit0e);
        out->AppendElement(st.mpBegin, st.mpEnd);
        st.DeallocateSelf();
        break;
    default: {
        st.Init(e);
        int w = st.width;
        if (w < 1) w = 5;
        s.mpBegin = s.mBuf; s.mpEnd = s.mBuf; s.mpCapacity = s.mBuf + 16; s.mpPool = s.mBuf;
        s.mBuf[0] = 0;
        s.FillN(w, L'*');
        if (st.mpBegin != st.mpEnd) { *st.mpBegin = 0; st.mpEnd = st.mpBegin; }
        st.AppendElement(s.mpBegin, s.mpEnd);
        s.Free();
        out->AppendElement(st.mpBegin, st.mpEnd);
        st.Free();
        break;
    }
    }
    if (v->cur < e->last) {
        v->len -= (int)((char*)e->last - (char*)v->cur + 2) >> 1;
        v->cur = (wchar_t*)((char*)e->last + 2);
    }
    return true;
}

struct Res {                                          // fixed_string<wchar_t,16,1>, no allocator slot
    wchar_t* b; wchar_t* e; wchar_t* c; wchar_t* pool; wchar_t buf[16];
    void __thiscall AppendElement(const wchar_t* first, const wchar_t* last);   // 0x68cc10
    void Free()
    {
        wchar_t* p = b;
        if (((int)((char*)c - (char*)p) & ~1) > 2 && p != 0 && p != pool)
            LocFree(p);
    }
};
// @ 0x008804d0
int __cdecl EA_Locale_MakeStringFromFormatElements(wchar_t* outBuf, unsigned cap, LocScan* v,
                                                   LocElem* first, int count)
{
    Res r;
    r.buf[0] = 0;
    r.b = r.buf; r.e = r.buf; r.c = r.buf + 16; r.pool = r.buf;
    LocElem* end = first + count;
    LocElem* it = first;
    while (it < end) {
        LocElem* nx = it + 1;
        LocElem* prev = nx - 2;
        if (it == first) prev = 0;
        LocElem* next = nx;
        if (it >= end - 1) next = 0;
        EA_Locale_FormatElement((LocStr16*)&r, v, it, prev, next);
        it = nx;
    }
    if (v->len) {
        r.AppendElement(v->cur, v->cur + v->len);
        v->cur += v->len;
        v->len = 0;
    }
    if (cap < (unsigned)(r.e - r.b)) {
        wcsncpy(outBuf, r.b, cap);
        outBuf[cap - 1] = 0;
    } else {
        wchar_t* p = r.b;
        wchar_t c;
        do { c = *p; *(wchar_t*)((char*)p + ((char*)outBuf - (char*)r.b)) = c; ++p; } while (c);
        outBuf[cap - 1] = 0;
    }
    int n = (int)(r.e - r.b);
    r.Free();
    return n;
}
