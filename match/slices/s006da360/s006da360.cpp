// Slice s006da360: per-attribute bake dispatch (10 lookup + element-type switch,
// with a fallback unrolled projection loop when the attribute is absent).
#include "../s006ccf50/s006ccf50.h"

// The original ends each acos tail in fsqrt on the 24-bit device-thread control word: the root is
// the correctly rounded single-precision one, but it is never narrowed to float, so a radicand
// beyond the float range does not overflow to Inf or underflow to 0.  cl15 will not inline a sqrt
// (it calls _CIsqrt and would add an import call the original does not make), and a float/sqrtss
// radicand loses exactly those out-of-range cases, so take the root from the x87 itself.
static inline double BakeSqrtX87(double x)
{
    __asm
    {
        fld qword ptr [x]
        fsqrt
        fstp qword ptr [x]
    }
    return x;
}

// The float tail of every projection runs as scalar SSE in the original (mulss/addss/subss);
// BakeMulSS/BakeAddSS come from the shared header, and the complement step needs the matching
// subss so the intermediates round to single precision exactly where the retail code does.
static inline float BakeSubSS(float a, float b)
{
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

int __cdecl FUN_0071ddc0(void* obj, int code, int a, int b, int c);

typedef unsigned char (__cdecl *BakeCore)(void*, int, ElemTable*, BakeEntry*, StreamDesc*,
                                         float*, ScaleInfo*, int, int, Handle*);

unsigned char __cdecl FUN_006d97f0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9840(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9890(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d98e0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9930(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);

unsigned char __cdecl FUN_006d9980(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d99d0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9a20(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9a70(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9ac0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);

unsigned char __cdecl FUN_006d9b10(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9b60(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9bb0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9c00(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9c50(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);

unsigned char __cdecl FUN_006d9ca0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9cf0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9d40(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9d90(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9de0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);

// Shared prologue: look up the position element (type 9) and the colour element
// (type 0x13), snapshot the colour handle, then pick the core by the type word.
#define DISPATCH_PROLOGUE(TABLE)                                                                 \
    int idxPos = FUN_0071ddc0(TABLE, 9, 0, 0, 0xe);                                              \
    int idxCol = FUN_0071ddc0(TABLE, 0x13, 0, 0xe, 5);                                           \
    if (idxPos < 0 || idxCol < 0)                                                                \
        goto fallback;                                                                           \
    {                                                                                            \
        Handle hA = ((ElemTable*)TABLE)->mBegin[idxCol].handle;                                  \
        int idxType = FUN_0071ddc0(TABLE, 10, 0, 0, 0xe);                                        \
        int w2 = 0;                                                                              \
        int type = 0;                                                                            \
        if (idxType < 0)                                                                         \
            type = 1;                                                                            \
        else                                                                                     \
        {                                                                                        \
            w2 = (int)((ElemTable*)TABLE)->mBegin[idxType].w2;                                   \
            type = w2;                                                                           \
            if (!(w2 >= 1 && w2 <= 4))                                                           \
                type = (w2 == 10) ? 4 : 1;                                                       \
        }                                                                                        \
        unsigned char _r;                                                                        \
        switch (type)                                                                            \
        {

#define DISPATCH_EPILOGUE                                                                        \
        default:                                                                                 \
            return 0;                                                                            \
        }                                                                                        \
    }

// ---------------------------------------------------------------------------
// 0x006da360: projection acos using component 0 as the weight, (1,2) as radius.
// @ 0x006da360
bool FUN_006da360(float* out, int count, ElemTable* table, BakeEntry* entries,
                  StreamDesc* pos, float* axis, ScaleInfo* scaleInfo)
{
    DISPATCH_PROLOGUE(table)
        case 1: _r = FUN_006d97f0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 2: _r = FUN_006d9840(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 3: _r = FUN_006d9890(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 4:
            if (w2 == 10)
                _r = FUN_006d98e0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
            else
                _r = FUN_006d9930(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
            goto done;
        default:
            return 0;
        }
    done:
        return _r;
    }
fallback:
    if (count != 0)
    {
        BakeEntry* e = entries;
        float* o = out;
        int n = count;
        do
        {
            float* p = (float*)(pos->base + pos->stride * e->f0);
            float dOther = p[2] - axis[3];
            float dNum = p[1] - axis[2];
            float x = p[0];
            float scale = scaleInfo->scale;
            double a = acos((double)dNum / BakeSqrtX87((double)dOther * dOther + (double)dNum * dNum));
            float ang = (float)(a * axis[0] * 1.2732406f);
            float w = BakeSubSS(1.0f, BakeMulSS(axis[1], x));
            o[0] = BakeMulSS(ang, scale);
            o[1] = BakeMulSS(w, scale);
            e += 1;
            o += 2;
        } while (--n);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x006da690: projection acos using component 1 as the weight, (2,0) as radius.
// @ 0x006da690
bool FUN_006da690(float* out, int count, ElemTable* table, BakeEntry* entries,
                  StreamDesc* pos, float* axis, ScaleInfo* scaleInfo)
{
    DISPATCH_PROLOGUE(table)
        case 1: _r = FUN_006d9980(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 2: _r = FUN_006d99d0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 3: _r = FUN_006d9a20(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 4:
            if (w2 == 10)
                _r = FUN_006d9a70(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
            else
                _r = FUN_006d9ac0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
            goto done;
        default:
            return 0;
        }
    done:
        return _r;
    }
fallback:
    if (count != 0)
    {
        BakeEntry* e = entries;
        float* o = out;
        int n = count;
        do
        {
            float* p = (float*)(pos->base + pos->stride * e->f0);
            float dOther = p[0] - axis[3];
            float dNum = p[2] - axis[2];
            float x = p[1];
            float scale = scaleInfo->scale;
            double a = acos((double)dNum / BakeSqrtX87((double)dOther * dOther + (double)dNum * dNum));
            float ang = (float)(a * axis[0] * 1.2732406f);
            float w = BakeSubSS(1.0f, BakeMulSS(axis[1], x));
            o[0] = BakeMulSS(ang, scale);
            o[1] = BakeMulSS(w, scale);
            e += 1;
            o += 2;
        } while (--n);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x006da9c0: projection acos using component 2 as the weight, (0,1) as radius.
// @ 0x006da9c0
bool FUN_006da9c0(float* out, int count, ElemTable* table, BakeEntry* entries,
                  StreamDesc* pos, float* axis, ScaleInfo* scaleInfo)
{
    DISPATCH_PROLOGUE(table)
        case 1: _r = FUN_006d9b10(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 2: _r = FUN_006d9b60(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 3: _r = FUN_006d9bb0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 4:
            if (w2 == 10)
                _r = FUN_006d9c00(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
            else
                _r = FUN_006d9c50(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
            goto done;
        default:
            return 0;
        }
    done:
        return _r;
    }
fallback:
    if (count != 0)
    {
        BakeEntry* e = entries;
        float* o = out;
        int n = count;
        do
        {
            float* p = (float*)(pos->base + pos->stride * e->f0);
            float dOther = p[1] - axis[3];
            float dNum = p[0] - axis[2];
            float x = p[2];
            float scale = scaleInfo->scale;
            double a = acos((double)dNum / BakeSqrtX87((double)dOther * dOther + (double)dNum * dNum));
            float ang = (float)(a * axis[0] * 1.2732406f);
            float w = BakeSubSS(1.0f, BakeMulSS(axis[1], x));
            o[0] = BakeMulSS(ang, scale);
            o[1] = BakeMulSS(w, scale);
            e += 1;
            o += 2;
        } while (--n);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x006dacf0: projection dot tail, unrolled 4x by the original.
// @ 0x006dacf0
bool FUN_006dacf0(float* out, int count, ElemTable* table, BakeEntry* entries,
                  StreamDesc* pos, float* axis, ScaleInfo* scaleInfo)
{
    DISPATCH_PROLOGUE(table)
        case 1: _r = FUN_006d9ca0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 2: _r = FUN_006d9cf0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 3: _r = FUN_006d9d40(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 4:
            if (w2 == 10)
                _r = FUN_006d9d90(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
            else
                _r = FUN_006d9de0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
            goto done;
        default:
            return 0;
        }
    done:
        return _r;
    }
fallback:
    if (count != 0)
    {
        BakeEntry* e = entries;
        float* o = out;
        int n = count;
        do
        {
            float* p = (float*)(pos->base + pos->stride * e->f0);
            float scale = scaleInfo->scale;
            float v0 = BakeAddSS(BakeMulSS(axis[0], p[0]), axis[2]);
            float v1 = BakeSubSS(1.0f, BakeAddSS(axis[3], BakeMulSS(axis[1], p[1])));
            o[0] = BakeMulSS(v0, scale);
            o[1] = BakeMulSS(v1, scale);
            e += 1;
            o += 2;
        } while (--n);
    }
    return 1;
}
