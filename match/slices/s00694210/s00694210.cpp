// Slice s00694210: SP::cTypedValue*ToString and the serializer sort helpers
// around 0x694210-0x6950b0.  Compiled /O2 /MD /Gy /EHsc /TP /GS-.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
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
// @ 0x00694440  EA::Variant::Read (stream, variant, endian): the property-list deserializer.
//   Reads the type id and flag words, then a scalar by type (flags & 0x30 == 0), or a
//   counted array (stride, count, then `count` elements read one by one) for flagged
//   variants; flag 0x40 variants are cleared and rejected.
// =====================================================================
struct VStream {                       // IO stream: Read(buf, size) at vtable +0x30
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10();
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c();
    virtual int Read(void* buf, int size);          // +0x30
};

struct Variant {
    char           pad0[4];            // +0 data (pointer / scalar), +4 element size, +8 element count
    int            mElemSize;          // +4
    int            mElemCount;         // +8
    int            padc;
    unsigned short mFlags;             // +0x10
    unsigned short mTypeId;            // +0x12
    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() { if (mFlags & 4) Destruct(0); }
    Variant& operator=(const Variant& v);          // 0x00542b80
    void Destruct(int a);                          // 0x0093db80
};

extern "C" bool FUN_0093a700(VStream* io, void* p, int n, int endian);   // ReadUInt16
extern "C" bool FUN_0093a780(VStream* io, void* p, int n, int endian);   // ReadInt32
extern "C" bool FUN_0093ac80(VStream* io, void* v);                      // ReadBool
// The per-type readers below are separate functions in the original that the linker folded
// (identical code) into three entry points; the distinct names keep their call sites apart.
extern "C" bool R8a(VStream* io, void* v);                      // @ 0x00593840
extern "C" bool R8b(VStream* io, void* v);                      // @ 0x00593840
extern "C" bool R16a(VStream* io, void* v, int endian);         // @ 0x00692720
extern "C" bool R16b(VStream* io, void* v, int endian);         // @ 0x00692720
extern "C" bool R16c(VStream* io, void* v, int endian);         // @ 0x00692720
extern "C" bool R32a(VStream* io, void* v, int endian);         // @ 0x00692740
extern "C" bool R32b(VStream* io, void* v, int endian);         // @ 0x00692740
extern "C" bool R32c(VStream* io, void* v, int endian);         // @ 0x00692740
extern "C" bool R64a(VStream* io, void* v, int endian);         // @ 0x00692760
extern "C" bool R64b(VStream* io, void* v, int endian);         // @ 0x00692760
extern "C" bool R64c(VStream* io, void* v, int endian);         // @ 0x00692760
extern "C" bool FUN_00693c70(VStream* io, void* v);                      // read narrow string
extern "C" bool FUN_00693890(VStream* io, void* v);                      // read wide string
void* operator new(unsigned int size, const char* name, int flags, unsigned int dflags,
                   const char* file, int line);                          // 0x00f473a0
extern "C" char gA[];   // 0x01667bac
extern "C" char gB[];   // 0x01667bae

// @ 0x00694440
bool FUN_00694440(VStream* io, Variant* v, int endian)
{
    if (v->mTypeId != 0) {
        Variant tmp;
        *v = tmp;
    }
    bool ok;
    bool bResult;
    if (FUN_0093a700(io, &v->mTypeId, 1, endian) && FUN_0093a700(io, &v->mFlags, 1, endian))
        ok = true;
    else
        ok = false;

    if ((v->mFlags & 0x30) == 0) {
        switch (v->mTypeId) {
        case 1:
            bResult = ok && FUN_0093ac80(io, v);
            break;
        case 2: case 6:
            bResult = ok && R8a(io, v);
            break;
        case 3: case 8:
            bResult = ok && R16a(io, v, endian);
            break;
        case 5:
            bResult = ok && R8b(io, v);
            break;
        case 7:
            bResult = ok && R16b(io, v, endian);
            break;
        case 9:
            bResult = ok && R32a(io, v, endian);
            break;
        case 10:
            bResult = ok && R32b(io, v, endian);
            break;
        case 11:
            bResult = ok && R64a(io, v, endian);
            break;
        case 12:
            bResult = ok && R64b(io, v, endian);
            break;
        case 13:
            bResult = ok && R32c(io, v, endian);
            break;
        case 14:
            bResult = ok && R64c(io, v, endian);
            break;
        case 18:
            ((void**)v)[0] = gA;
            ((void**)v)[1] = gA;
            ((void**)v)[2] = gA + 1;
            bResult = ok && FUN_00693c70(io, v);
            break;
        case 19:
            ((void**)v)[0] = gA;
            ((void**)v)[1] = gA;
            ((void**)v)[2] = gB;
            bResult = ok && FUN_00693890(io, v);
            break;
        case 17:
            v->mFlags = 0;
            v->mTypeId = 0;
            bResult = false;
            break;
        default:
            if (ok && io->Read(v, 0x10) != 0)
                bResult = true;
            else
                bResult = false;
            v->mFlags &= 0xfff2;
            break;
        }
        return bResult;
    } else {
        if ((v->mFlags & 0x40) == 0) {
            if (ok && FUN_0093a780(io, &v->mElemCount, 1, endian) && FUN_0093a780(io, &v->mElemSize, 1, endian))
                bResult = true;
            else
                bResult = false;
            char* p = (char*)operator new(v->mElemSize * v->mElemCount, "App/PropertyList/Variant/PointerPtr", 0, 0, 0, 0);
            char* end = p + v->mElemCount * v->mElemSize;
            *(char**)v = p;
            if (p < end) {
                do {
                    switch (v->mTypeId) {
                    case 1:
                        if (!bResult || !FUN_0093ac80(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 2: case 6:
                        if (!bResult || !R8a(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 3:
                        if (!bResult || !R16a(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 5:
                        if (!bResult || !R8b(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 7:
                        if (!bResult || !R16b(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 8:
                        if (!bResult || !R16c(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 9:
                        if (!bResult || !R32a(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 10:
                        if (!bResult || !R32b(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 11:
                        if (!bResult || !R64a(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 12:
                        if (!bResult || !R64b(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 13:
                        if (!bResult || !R32c(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 14:
                        if (!bResult || !R64c(io, p, endian)) goto fail;
                        bResult = true;
                        break;
                    case 18:
                        if (p) {
                            ((void**)p)[0] = gA;
                            ((void**)p)[1] = gA;
                            ((void**)p)[2] = gA + 1;
                        }
                        if (!bResult || !FUN_00693c70(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 19:
                        if (p) {
                            ((void**)p)[0] = gA;
                            ((void**)p)[1] = gA;
                            ((void**)p)[2] = gB;
                        }
                        if (!bResult || !FUN_00693890(io, p)) goto fail;
                        bResult = true;
                        break;
                    case 17:
                        v->mFlags = 0;
                        v->mTypeId = 0;
                        operator_delete_arr(*(void**)v);
                    fail:
                        bResult = false;
                        break;
                    case 16:
                        if (!bResult || io->Read(p, v->mElemSize) == 0) goto fail;
                        bResult = true;
                        break;
                    default:
                        if (bResult && io->Read(p, v->mElemSize) != 0)
                            bResult = true;
                        else
                            bResult = false;
                        v->mFlags &= 0xfffe;
                        break;
                    }
                    p += v->mElemSize;
                } while (p < end);
            }
            return bResult;
        }
        v->mFlags = 0;
        v->mTypeId = 0;
    }
    return false;
}

// @ 0x00694bd0  (tail of the 0x00694440 span) assign the "**unsupported type**" text
extern "C" void FUN_00694bd0(CString* str)
{
    static const char kText[] = "**unsupported type**";
    str->assign(kText, kText + 20);
}

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
