// Slice s00694210: SP::cTypedValue*ToString and the serializer sort helpers
// around 0x694210-0x6950b0.  Compiled /O2 /MD /Gy /EHsc /TP /GS-.
#include "types.h"

typedef unsigned int u32;

struct Elem { unsigned int m0; unsigned int mId; unsigned int m2[13]; };
struct CString { char* begin; char* end; char* cap; void assign(const char* b, const char* e); };

extern "C" void operator_delete_arr(void* p);                    // 0xf47380
extern "C" void EA_sprintf(void* dst, const char* fmt, ...);     // 0x472fe0 basic_string::sprintf
extern "C" void  FUN_00693b90(Elem* first, Elem* last, int cmp); // 0x693b90
extern "C" void  FUN_00693c10(Elem* first, Elem* last, int cmp); // 0x693c10
extern "C" void  FUN_00693280(Elem* first, int top, int heapSize, int position, Elem value, int cmp); // 0x693280
extern "C" Elem* FUN_00694210(Elem* first, Elem* last, Elem value); // 0x694210
extern "C" void  FUN_00694270(Elem* first, Elem* mid, Elem* last, int cmp);   // 0x694270
extern "C" void  FUN_00694d00(Elem* first, Elem* last, int depth, int cmp);   // 0x694d00
extern "C" void  FUN_00692cb0(Elem* first, Elem* mid, int cmp);               // 0x692cb0
extern "C" void  FUN_00692d20(Elem* mid, Elem* last, int cmp);                // 0x692d20

// =====================================================================
// typed-value writers
// =====================================================================
// @ 0x00694ec0
extern "C" void FUN_00694ec0(void* dst, unsigned __int64* p) { EA_sprintf(dst, "%I64u", *p); }
// @ 0x00694ee0
extern "C" void FUN_00694ee0(void* dst, unsigned int* p) { EA_sprintf(dst, "%u", *p); }
// @ 0x00694f00
extern "C" void FUN_00694f00(void* dst, int* p) { EA_sprintf(dst, "%d", *p); }
// @ 0x00694f20
extern "C" void FUN_00694f20(void* dst, short* p) { EA_sprintf(dst, "%d", (int)*p); }
// @ 0x00694f40
extern "C" void FUN_00694f40(void* dst, unsigned short* p) { EA_sprintf(dst, "%d", (int)*p); }
// @ 0x00694f60
extern "C" void FUN_00694f60(void* dst, signed char* p) { EA_sprintf(dst, "%d", (int)*p); }
// @ 0x00694f80
extern "C" void FUN_00694f80(void* dst, unsigned char* p) { EA_sprintf(dst, "%d", (int)*p); }
// @ 0x00694fa0
extern "C" void FUN_00694fa0(void* dst, unsigned char* p) { EA_sprintf(dst, "%d", (int)*p); }
// @ 0x00694fc0
extern "C" void FUN_00694fc0(void* dst, float* p) { EA_sprintf(dst, "%f", (double)*p); }
// @ 0x00694fe0
extern "C" void FUN_00694fe0(void* dst, float* p) { EA_sprintf(dst, "%f,%f", (double)p[0], (double)p[1]); }
// @ 0x00695010
extern "C" void FUN_00695010(void* dst, float* p) { EA_sprintf(dst, "%f,%f,%f", (double)p[0], (double)p[1], (double)p[2]); }
// @ 0x00695040
extern "C" void FUN_00695040(void* dst, float* p) { EA_sprintf(dst, "%f,%f,%f,%f", (double)p[0], (double)p[1], (double)p[2], (double)p[3]); }
// @ 0x00695080
extern "C" void FUN_00695080(void* dst, unsigned int* p) { EA_sprintf(dst, "0x%08x,0x%08x,0x%08x", p[0], p[2], p[1]); }

// =====================================================================
// @ 0x00694e00  destroy a [first,last) range of 0x60-byte objects
// =====================================================================
extern "C" char* FUN_00694e00(char* first, char* last, char* out)
{
    while (first != last)
    {
        char* p = *(char**)(first + 0x50);
        if ((*(char**)(first + 0x58) - p) > 1 && p != 0)
            operator_delete_arr(p);
        p = *(char**)(first + 0x40);
        if ((*(char**)(first + 0x48) - p) > 1 && p != 0)
            operator_delete_arr(p);
        first += 0x60;
        out += 0x60;
    }
    return out;
}

// =====================================================================
// @ 0x00694bf0  assign one string field from another
// =====================================================================
extern "C" void FUN_00694bf0(CString* dst, CString* src)
{
    if (src != dst)
        dst->assign(src->begin, src->end);
}

// =====================================================================
// @ 0x00694210  Hoare partition of 0x3c-byte records by mId
// =====================================================================
Elem* FUN_00694210(Elem* first, Elem* last, Elem value)
{
    for (;;)
    {
        while (first->mId < value.mId)
            ++first;
        do { --last; } while (value.mId < last->mId);
        if (first >= last)
            break;
        Elem tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
    return first;
}

// =====================================================================
// @ 0x00694270  partial_sort(first, mid, last)
// =====================================================================
extern "C" void FUN_00692cb0(Elem* first, Elem* mid, int cmp);   // 0x692cb0
extern "C" void FUN_00692d20(Elem* mid, Elem* last, int cmp);    // 0x692d20

void FUN_00694270(Elem* first, Elem* mid, Elem* last, int cmp)
{
    FUN_00693b90(first, mid, cmp);
    for (Elem* i = mid; i < last; ++i)
    {
        if (i->mId < first->mId)
        {
            Elem value = *i;
            *i = *first;
            int n = (int)((char*)mid - (char*)first) / 60;
            FUN_00693280(first, 0, n, 0, value, cmp);
        }
    }
    FUN_00693c10(first, mid, cmp);
}

// =====================================================================
// @ 0x006943b0  move_backward a range of 0x60-byte objects
// =====================================================================
struct Str16 { char* begin; char* end; char* cap; void* pad; void assign(const char* b, const char* e); };
struct Hdr15 { u32 v[15]; };
struct Obj60 { Hdr15 h; u32 x; Str16 s1; Str16 s2; };

extern "C" Obj60* FUN_006943b0(Obj60* first, Obj60* last, Obj60* out)
{
    while (last != first)
    {
        --last;
        --out;
        out->h = last->h;
        out->x = last->x;
        if (&last->s1 != &out->s1)
            out->s1.assign(last->s1.begin, last->s1.end);
        if (&last->s2 != &out->s2)
            out->s2.assign(last->s2.begin, last->s2.end);
    }
    return out;
}

// =====================================================================
// @ 0x006950b0  introsort entry point
// =====================================================================
void FUN_006950b0(Elem* first, Elem* last, int cmp)
{
    if (first == last)
        return;
    int n = (int)((char*)last - (char*)first) / 60;
    int depth = 0;
    for (int t = n; t != 0; t >>= 1)
        ++depth;
    FUN_00694d00(first, last, depth * 2 - 2, cmp);
    if (n > 0x1c)
    {
        FUN_00692cb0(first, first + 0x1c, cmp);
        FUN_00692d20(first + 0x1c, last, cmp);
        return;
    }
    FUN_00692cb0(first, last, cmp);
}

// =====================================================================
// @ 0x00694d00  introsort
// =====================================================================
void FUN_00694d00(Elem* first, Elem* last, int depth, int cmp)
{
    int len = (int)((char*)last - (char*)first) / 60;
    for (;;)
    {
        if (len < 0x1d || depth < 1)
        {
            if (depth == 0)
                FUN_00694270(first, last, last, cmp);
            return;
        }
        Elem* midp = first + len / 2;
        u32 a = first->mId;
        u32 b = midp->mId;
        u32 c = last[-1].mId;
        Elem* piv;
        if (a < b)
            piv = (b < c) ? midp : (a < c ? last - 1 : first);
        else
            piv = (a < c) ? first : (b < c ? last - 1 : midp);
        Elem* cut = FUN_00694210(first, last, *piv);
        --depth;
        FUN_00694d00(cut, last, depth, cmp);
        len = (int)((char*)cut - (char*)first) / 60;
        last = cut;
    }
}

// =====================================================================
// @ 0x00694c10  EA::ConvertToString8 wrapper
// =====================================================================
struct StrBuf { char* begin; char* end; char* cap; void assign(const char* b, const char* e); void dtor(); };
extern "C" StrBuf* EA_ConvertToString8(StrBuf* out, void* v);

extern "C" void FUN_00694c10(StrBuf* dst, void* v)
{
    StrBuf tmp;
    tmp.begin = 0;
    tmp.end = 0;
    tmp.cap = 0;
    StrBuf* r = EA_ConvertToString8(&tmp, v);
    if (r != dst)
        dst->assign(r->begin, r->end);
    tmp.dtor();
}

// =====================================================================
// @ 0x00694440  SP::cUnknownTypedValueToString::Write -- summarised.
// =====================================================================
extern "C" void FUN_00694440(void* self, void* value)
{
    // Dispatches on the runtime kind of *value and formats it into the output
    // string for every scalar/vector/unknown kind.  Body summarised: the exact
    // per-kind branches are not reproduced.
}

extern "C" char gA[];   // 0x01667bac
extern "C" char gB[];   // 0x01667bae

struct Big2 {
    u32 f0;
    u32 f4, f8, fc, f10, f14, f18, f1c, f20, f24, f28;
    void* f2c; void* f30; void* f34; u32 f38;
    void* f3c; void* f40; void* f44; u32 f48;
    void* f4c; void* f50; void* f54; u32 f58;
    u32 f5c, f60, f64, f68, f6c, f70;
    void init(void* a);
};

// @ 0x00694e60
void Big2::init(void* a)
{
    f0 = (u32)a;
    f4 = f8 = fc = 0;
    f18 = f1c = f20 = 0;
    f2c = gA;
    f30 = gA;
    f34 = gB;
    f3c = gA;
    f40 = gA;
    f44 = gB;
    f4c = gA;
    f50 = gA;
    f54 = gB;
    f5c = f60 = f64 = 0;
    f70 = 0;
}
