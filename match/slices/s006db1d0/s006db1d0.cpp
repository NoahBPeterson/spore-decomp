// Slice s006db1d0: per-attribute bake dispatch (two dot-projection variants and
// one acos-len projection), same shape as slice s006da360.
#include "../s006ccf50/s006ccf50.h"

int __cdecl FUN_0071ddc0(void* obj, int code, int a, int b, int c);

unsigned char __cdecl FUN_006d9e30(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9e80(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9ed0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006d9f20(void);
unsigned char __cdecl FUN_006d9f70(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);

unsigned char __cdecl FUN_006d9fc0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006da010(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006da060(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006da0b0(void);
unsigned char __cdecl FUN_006da100(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);

unsigned char __cdecl FUN_006da150(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006da1a0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006da1f0(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);
unsigned char __cdecl FUN_006da240(void);
unsigned char __cdecl FUN_006da290(void*, int, ElemTable*, BakeEntry*, StreamDesc*, float*, ScaleInfo*, int, int, Handle*);

#define DISPATCH_PROLOGUE(TABLE)                                                                 \
    int idxPos = FUN_0071ddc0(TABLE, 9, 0, 0, 0xe);                                              \
    int idxCol = FUN_0071ddc0(TABLE, 0x13, 0, 0xe, 5);                                           \
    if (idxPos < 0 || idxCol < 0)                                                                \
        goto fallback;                                                                           \
    {                                                                                            \
        Handle hA = ((ElemTable*)TABLE)->mBegin[idxCol].handle;                                  \
        int idxType = FUN_0071ddc0(TABLE, 10, 0, 0, 0xe);                                        \
        int type = 0;                                                                            \
        if (idxType < 0)                                                                         \
            type = 1;                                                                            \
        else                                                                                     \
        {                                                                                        \
            int w2 = (int)((ElemTable*)TABLE)->mBegin[idxType].w2;                               \
            type = w2;                                                                           \
            if (!(w2 >= 1 && w2 <= 4))                                                           \
                type = (w2 == 10) ? 4 : 1;                                                       \
        }                                                                                        \
        unsigned char _r;                                                                        \
        switch (type)                                                                            \
        {

// ---------------------------------------------------------------------------
// 0x006db1d0: dot projection, out0 uses component 0, weight uses component 2.
unsigned char FUN_006db1d0(float* out, int count, ElemTable* table, BakeEntry* entries,
                           StreamDesc* pos, float* axis, ScaleInfo* scaleInfo)   // @ 0x006db1d0
{
    DISPATCH_PROLOGUE(table)
        case 1: _r = FUN_006d9e30(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 2: _r = FUN_006d9e80(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 3: _r = FUN_006d9ed0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 4:
            if (type == 10)
                _r = FUN_006d9f20();
            else
                _r = FUN_006d9f70(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
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
            o[0] = (axis[0] * p[0] + axis[2]) * scaleInfo->scale;
            o[1] = (1.0f - (axis[3] + axis[1] * p[2])) * scaleInfo->scale;
            e += 1;
            o += 2;
        } while (--n);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x006db6b0: dot projection, out0 uses component 1, weight uses component 2.
unsigned char FUN_006db6b0(float* out, int count, ElemTable* table, BakeEntry* entries,
                           StreamDesc* pos, float* axis, ScaleInfo* scaleInfo)   // @ 0x006db6b0
{
    DISPATCH_PROLOGUE(table)
        case 1: _r = FUN_006d9fc0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 2: _r = FUN_006da010(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 3: _r = FUN_006da060(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 4:
            if (type == 10)
                _r = FUN_006da0b0();
            else
                _r = FUN_006da100(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
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
            o[0] = (axis[0] * p[1] + axis[2]) * scaleInfo->scale;
            o[1] = (1.0f - (axis[3] + axis[1] * p[2])) * scaleInfo->scale;
            e += 1;
            o += 2;
        } while (--n);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x006dbba0: acos-len projection (weight = axis.y * radius), components (0,1).
unsigned char FUN_006dbba0(float* out, int count, ElemTable* table, BakeEntry* entries,
                           StreamDesc* pos, float* axis, ScaleInfo* scaleInfo)   // @ 0x006dbba0
{
    DISPATCH_PROLOGUE(table)
        case 1: _r = FUN_006da150(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 2: _r = FUN_006da1a0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 3: _r = FUN_006da1f0(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA); goto done;
        case 4:
            if (type == 10)
                _r = FUN_006da240();
            else
                _r = FUN_006da290(out, count, table, entries, pos, axis, scaleInfo, idxPos, idxCol, &hA);
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
            float len = (float)sqrt(dOther * dOther + dNum * dNum);
            float angle = (float)acos(dNum / len);
            o[0] = ((axis[0] * angle) * 1.2732406f) * scaleInfo->scale;
            o[1] = (1.0f - axis[1] * len) * scaleInfo->scale;
            e += 1;
            o += 2;
        } while (--n);
    }
    return 1;
}
