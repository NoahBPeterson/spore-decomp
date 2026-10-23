// Slice s00dc0b00 — SP::cSPGameDataUFO abduction/tool/destination helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

// ---- external free functions -------------------------------------------------
int         __cdecl FUN_00ffbe50();                       // 0xffbe50  SP::GetUFOSimulator
int         __cdecl FUN_00d998d0(int, int);               // 0xd998d0
int         __cdecl FUN_00d51660();                       // 0xd51660
int         __cdecl FUN_0102bc90(void*, int, int);        // 0x102bc90 SP::GetBestUFOTarget
int         __cdecl FUN_00b3d390();                       // 0xb3d390  getter [0x167eb08]
long double __cdecl FUN_004e1c70(int, int, float);        // 0x4e1c70  SP::GetPropertyT<float>
float*      __cdecl FUN_0059aed0(void*, void*, void*);    // 0x59aed0
void*       __cdecl FUN_00436ce0(void*, void*);           // 0x436ce0  Vector3_Normalize
long double __cdecl FUN_0040ae50(void*);                  // 0x40ae50  VectorLength
int         __cdecl FUN_01029940();                       // 0x1029940 SP::GetSpaceCombatTuning

int   __fastcall FUN_00bddd10(int);                       // 0xbddd10
int   __fastcall FUN_00c38b00(int);                       // 0xc38b00
long double __fastcall FUN_00c37120(int);                 // 0xc37120
int   __fastcall FUN_00d516a0(int);                       // 0xd516a0

// ---- thiscall callees (stub members keep the call direct E8 rel32) -----------
struct Stub {
    bool        __thiscall FUN_00c004c0(int);             // 0xc004c0
    bool        __thiscall FUN_00c37890(int, int);        // 0xc37890
    bool        __thiscall FUN_00c38990(int);             // 0xc38990
    void        __thiscall FUN_00c389c0(int, int);        // 0xc389c0
    void        __thiscall FUN_00c3a930(int, int);        // 0xc3a930
    long double __thiscall FUN_00c3ae70();                // 0xc3ae70
    long double __thiscall FUN_00c387b0(float, float, float); // 0xc387b0
    void        __thiscall FUN_00c3b5c0(int);             // 0xc3b5c0
    void        __thiscall FUN_00c3be70(void*);           // 0xc3be70
    void        __thiscall FUN_00c3daa0(float);           // 0xc3daa0
    void        __thiscall FUN_00c37e60();                // 0xc37e60  PopToDestination
    int         __thiscall FUN_00bc96a0(int, int);        // 0xbc96a0  Play
    void        __thiscall FUN_00bc98f0(int, int);        // 0xbc98f0  ClearAll
    int         __thiscall FUN_00d516d0(int);             // 0xd516d0  GetNumCreaturesToAbduct
    int         __thiscall FUN_00d4cb50(int);             // 0xd4cb50  GetActiveEventTuning
    long double __thiscall FUN_0102a840(float);           // 0x102a840
    long double __thiscall FUN_0102a8f0(float);           // 0x102a8f0
    long double __thiscall FUN_0102a9b0();                // 0x102a9b0
    long double __thiscall FUN_0102aa00();                // 0x102aa00
    void        __thiscall FUN_0104e340(void*, void*);    // 0x104e340  CreateToolFromToolID
    void        __thiscall FUN_01050070(void*, void*, void*, int, int, int, int); // 0x1050070 UseToolStart
    bool        __thiscall FUN_00ac0730(void*, void*);    // 0xac0730
};

#define VTOBJ(o) (*(void***)(o))

// ---- one-line x87 helpers ----------------------------------------------------
static float X87Sin(float a)  { float r; __asm { fld a } __asm { fsin }  __asm { fstp r } return r; }
static float X87Cos(float a)  { float r; __asm { fld a } __asm { fcos }  __asm { fstp r } return r; }
static float X87Sqrt(float a) { float r; __asm { fld a } __asm { fsqrt } __asm { fstp r } return r; }

// ===========================================================================
// @ 0x00dc0b00
// ===========================================================================
bool __cdecl FUN_00dc0b00(void* p1, int a2, int a3, uint32_t p4, int a5,
                              float* p6, int a7, float p8)
{
    char* s = (char*)p1;
    int iVar7 = *(int*)(s + 0x68c);
    if (iVar7 == 0)
        return 0;
    if (*(int*)(s + 0x714) == 3)
    {
        int edi = iVar7 + 0x508;
        int eax = FUN_00ffbe50();
        int r = FUN_00bddd10(eax);
        if (edi != r)
            return 0;
    }
    if (*p6 != *(float*)0x13eb1bc)
    {
        float f = *p6 - p8;
        *p6 = f;
        if (f <= 0.0f)
        {
            int pi = *(int*)(s + 0x68c);
            if (pi != 0)
            {
                *(int*)(s + 0x68c) = 0;
                (*(void(__thiscall*)(int))((*(int*)pi) + 4))(pi);
            }
            (*(void(__thiscall*)(void*))(VTOBJ(s + 0x508)[0x38 / 4]))(s + 0x508);
            return 0;
        }
    }
    int obj = FUN_00c38b00((int)s);
    if (obj != 0)
    {
        int iv = (*(int(__thiscall*)(int, int))(VTOBJ(obj)[0xc / 4]))(obj, 0xee9b2232);
        if (iv != 0)
        {
            float* pf8 = (float*)(*(int(__thiscall*)(int))(VTOBJ(iv + 0x120)[0x2c / 4]))(iv + 0x120);
            float* pf9 = (float*)(*(int(__thiscall*)(int))(VTOBJ(s + 0x34)[0x2c / 4]))((int)(s + 0x34));
            float d1 = pf9[1] - pf8[1];
            float d0 = pf9[2] - pf8[2];
            float d2 = *pf9 - *pf8;
            float dist = X87Sqrt(d1 * d1 + (d0 * d0 + d2 * d2));
            if (*(float*)0x159d5d8 < dist)
            {
                int pi = *(int*)(s + 0x68c);
                if (pi != 0)
                {
                    *(int*)(s + 0x68c) = 0;
                    (*(void(__thiscall*)(int))((*(int*)pi) + 4))(pi);
                }
                (*(void(__thiscall*)(void*))(VTOBJ(s + 0x508)[0x38 / 4]))(s + 0x508);
                return 0;
            }
        }
    }
    if (((Stub*)(*(int*)(s + 0x68c)))->FUN_00c38990(1))
    {
        int pi = *(int*)(s + 0x68c);
        if (pi != 0)
        {
            *(int*)(s + 0x68c) = 0;
            (*(void(__thiscall*)(int))((*(int*)pi) + 4))(pi);
        }
        return 0;
    }

    float* pf8 = (float*)(s + 0x694);
    float ang = *(float*)0x159d624 * p8 * 0.5f;
    float sn = X87Sin(ang);
    float cs = X87Cos(ang);
    float quat[4];
    quat[0] = sn * *(float*)0x169fa0c;
    quat[1] = sn * *(float*)0x169fa10;
    quat[2] = sn * *(float*)0x169fa14;
    quat[3] = cs;
    float nrm[3];
    FUN_00436ce0(nrm, pf8);
    float out[3];
    float* pf9 = (float*)FUN_0059aed0(out, nrm, quat);
    pf8[0] = pf9[0];
    pf8[1] = pf9[1];
    pf8[2] = pf9[2];
    long double fVar11 = ((Stub*)s)->FUN_00c3ae70();
    float fVar13 = *(float*)(p6 + 1);
    float fVar3 = (float)fVar11;
    float fVar1 = pf8[1];
    float pv2 = pf8[2];
    pf8[0] = (fVar13 * pf8[0]) * fVar3;
    pf8[1] = (fVar1 * fVar13) * fVar3;
    pf8[2] = (pv2 * fVar13) * fVar3;

    float* pf9b = (float*)(*(int(__thiscall*)(int))(VTOBJ(*(int*)(s + 0x68c) + 0x34)[0x2c / 4]))(*(int*)(s + 0x68c) + 0x34);
    ((Stub*)s)->FUN_00c3daa0((float)(X87Sqrt(*pf9b * *pf9b + pf9b[1] * pf9b[1] + pf9b[2] * pf9b[2]) + *(float*)(s + 0x6ac)));

    iVar7 = *(int*)(s + 0x68c);
    int uVar10 = (*(int(__thiscall*)(int))(VTOBJ(iVar7 + 0x34)[0x30 / 4]))(iVar7 + 0x34);
    float* pf8b = (float*)FUN_0059aed0(out, pf8, (void*)uVar10);
    float* pf9c = (float*)(*(int(__thiscall*)(int))(VTOBJ(iVar7 + 0x34)[0x2c / 4]))(iVar7 + 0x34);
    float tmp[3];
    tmp[0] = pf9c[0] + pf8b[0];
    tmp[1] = pf9c[1] + pf8b[1];
    tmp[2] = pf9c[2] + pf8b[2];
    ((Stub*)s)->FUN_00c3be70(tmp);
    *(uint8_t*)(s + 0x624) = 1;
    float df0 = *(float*)(s + 0x750) - *(float*)(s + 0x718);
    float df1 = *(float*)(s + 0x754) - *(float*)(s + 0x71c);
    float df2 = *(float*)(s + 0x758) - *(float*)(s + 0x720);
    float dsc = X87Sqrt(df0 * df0 + (df1 * df1 + df2 * df2));
    if (*(float*)(p6 + 1) + *(float*)(p6 + 1) <= dsc)
    {
        *(float*)(s + 0x6b4) = *(float*)0x159d618;
    }
    else
    {
        long double fv = ((Stub*)s)->FUN_00c387b0(*(float*)(s + 0x718), *(float*)(s + 0x71c), *(float*)(s + 0x720));
        *(float*)(s + 0x6b4) = (float)(*(float*)0x159d620 / fv);
    }

    int uVar = FUN_0102bc90(s, (int)((p4 >> 0xc) & 1), 0);
    if (*(int*)(p6 + 3) == 0)
    {
        if (((Stub*)s)->FUN_00c37890(uVar, 3))
            *(int*)(p6 + 3) = 3;
        else if (((Stub*)s)->FUN_00c37890(uVar, 2))
            *(int*)(p6 + 3) = 2;
        else if (((Stub*)s)->FUN_00c37890(uVar, 1))
        {
            *(int*)(p6 + 3) = 1;
            *(uint8_t*)(p6 + 4) = 0;
        }
        else
            goto LAB_00dc0ef1;
        float* pfx = (float*)(*(int(__thiscall*)(int))(VTOBJ(s + 0x34)[0x2c / 4]))((int)(s + 0x34));
        *(float*)(p6 + 5) = pfx[0];
        *(float*)(p6 + 6) = pfx[1];
        *(float*)(p6 + 7) = pfx[2];
        ((Stub*)s)->FUN_00c389c0(8, 1);
    }
LAB_00dc0ef1:
    if (*(int*)(p6 + 3) == 1)
    {
        if (!((Stub*)s)->FUN_00c37890(uVar, 1))
        {
            *(int*)(p6 + 3) = 0;
            *(uint8_t*)(p6 + 4) = 0;
        }
        else
        {
            *(float*)(p6 + 2) = *(float*)(p6 + 2) + p8;
            if (*(uint8_t*)(p6 + 4) == 0)
            {
                ((Stub*)s)->FUN_00c3a930(uVar, 1);
                int t = FUN_01029940();
                long double lim = ((Stub*)t)->FUN_0102a9b0();
                if ((long double)*(float*)(p6 + 2) < lim)
                    return 1;
                *(uint8_t*)(p6 + 4) = 1;
            }
            else
            {
                (*(void(__thiscall*)(void*, int))(VTOBJ(s + 0x508)[0x50 / 4]))(s + 0x508, 0);
                int t = FUN_01029940();
                long double lim = ((Stub*)t)->FUN_0102aa00();
                if ((long double)*(float*)(p6 + 2) < lim)
                    return 1;
                *(uint8_t*)(p6 + 4) = 0;
            }
            *(float*)(p6 + 2) = 0.0f;
        }
        return 1;
    }
    if (1 < (uint32_t)(*(int*)(p6 + 3) - 2))
    {
        *(float*)(p6 + 2) = 0.0f;
        (*(void(__thiscall*)(void*, int))(VTOBJ(s + 0x508)[0x50 / 4]))(s + 0x508, uVar);
        return 1;
    }
    *(float*)(p6 + 2) = *(float*)(p6 + 2) + p8;
    float fLen = (float)FUN_0040ae50(p6 + 5);
    ((Stub*)s)->FUN_00c3daa0(fLen);
    ((Stub*)s)->FUN_00c3be70(p6 + 5);
    *(uint8_t*)(s + 0x624) = 1;
    ((Stub*)s)->FUN_00c37e60();
    float fArg = *(float*)(s + 0x714);
    long double lim2;
    if (*(int*)(p6 + 3) == 2)
    {
        int t = FUN_01029940();
        lim2 = ((Stub*)t)->FUN_0102a840(fArg);
    }
    else
    {
        int t = FUN_01029940();
        lim2 = ((Stub*)t)->FUN_0102a8f0(fArg);
    }
    if ((long double)*(float*)(p6 + 2) < lim2)
        return 1;
    *(float*)(p6 + 2) = 0.0f;
    ((Stub*)s)->FUN_00c3a930(uVar, *(int*)(p6 + 3));
    *(int*)(p6 + 3) = 0;
    return 1;
}

// ===========================================================================
// @ 0x00dc1060
// ===========================================================================
bool __cdecl FUN_00dc1060(void* p1)
{
    char* s = (char*)p1;
    if (*(int*)(s + 0x68c) == 0)
        return 0;
    int obj = *(int*)(s + 0x68c);
    int uVar3 = (*(int(__thiscall*)(int))(VTOBJ(obj + 0x34)[0x30 / 4]))(obj + 0x34);
    float fStack[3];
    float* pf4 = (float*)FUN_0059aed0(fStack, (void*)0x169fa18, (void*)uVar3);
    float* pd = (float*)(s + 0x694);
    float c = *(float*)0x14000fc;
    pd[0] = pf4[0] * c;
    pd[1] = pf4[1] * c;
    pd[2] = pf4[2] * c;
    long double fVar7 = FUN_00c37120(*(int*)(s + 0x68c));
    ((Stub*)s)->FUN_00c3daa0((float)(fVar7 + (long double)*(float*)(s + 0x6ac)));
    int iVar6 = *(int*)(s + 0x68c);
    int uVar3b = (*(int(__thiscall*)(int))(VTOBJ(iVar6 + 0x34)[0x30 / 4]))(iVar6 + 0x34);
    float* pf4b = (float*)FUN_0059aed0(fStack, (float*)(s + 0x694), (void*)uVar3b);
    float* pf5 = (float*)(*(int(__thiscall*)(int))(VTOBJ(iVar6 + 0x34)[0x2c / 4]))(iVar6 + 0x34);
    float v[3];
    v[0] = pf5[0] + pf4b[0];
    v[1] = pf5[1] + pf4b[1];
    v[2] = pf5[2] + pf4b[2];
    ((Stub*)s)->FUN_00c3be70(v);
    *(uint8_t*)(s + 0x624) = 1;
    int arg = (*(int*)(s + 0x68c) == 0) ? 0 : *(int*)(s + 0x68c) + 0x508;
    (*(void(__thiscall*)(void*, int))(VTOBJ(s + 0x508)[0x50 / 4]))(s + 0x508, arg);
    return 1;
}

// ===========================================================================
// @ 0x00dc1190
// ===========================================================================
bool __cdecl FUN_00dc1190(void* p1, int a2, int a3, int a4, int a5, int a6,
                              int a7, float p8)
{
    char* s = (char*)p1;
    int pi4 = FUN_00c38b00((int)s);
    if (pi4 != 0)
    {
        int p = (*(int(__thiscall*)(int, int))(VTOBJ(pi4)[0xc / 4]))(pi4, 0xee9b2232);
        if (p != 0)
        {
            if (!(*(bool(__thiscall*)(int))(VTOBJ(p)[0x2c / 4]))(p))
            {
                if (((Stub*)p)->FUN_00c004c0(0) || 0.0f < *(float*)(p + 0x220))
                {
                    float* pf5 = (float*)(*(int(__thiscall*)(int))(VTOBJ(p + 0x120)[0x2c / 4]))(p + 0x120);
                    float f8 = pf5[0];
                    float* pf1 = (float*)(s + 0x6a0);
                    float f7 = 1.0f / X87Sqrt(f8 * f8 + pf5[1] * pf5[1] + pf5[2] * pf5[2]);
                    float sn = X87Sin(p8 * 0.5f);
                    float cs = X87Cos(p8 * 0.5f);
                    float quat[4];
                    quat[0] = sn * (f8 * f7);
                    quat[1] = (f7 * pf5[1]) * sn;
                    quat[2] = (f7 * pf5[2]) * sn;
                    quat[3] = cs;
                    float out[3];
                    float* pf5b = (float*)FUN_0059aed0(out, pf1, quat);
                    pf1[0] = pf5b[0];
                    pf1[1] = pf5b[1];
                    pf1[2] = pf5b[2];
                    float* pf5c = (float*)(*(int(__thiscall*)(int))(VTOBJ(p + 0x120)[0x2c / 4]))(p + 0x120);
                    float fv2 = pf5c[2] + pf1[2];
                    float fv1 = pf5c[1] + pf1[1];
                    float fv0 = pf1[0] + pf5c[0];
                    float tmp[3];
                    tmp[0] = fv0;
                    tmp[1] = fv1;
                    tmp[2] = fv2;
                    ((Stub*)s)->FUN_00c3daa0((float)X87Sqrt(fv0 * fv0 + (fv1 * fv1 + fv2 * fv2)));
                    ((Stub*)s)->FUN_00c3be70(tmp);
                    (*(void(__thiscall*)(void*, int))(VTOBJ(s + 0x508)[0x50 / 4]))(s + 0x508, 0);
                    *(uint8_t*)(s + 0x624) = 1;
                    float df0 = *(float*)(s + 0x718) - fv0;
                    float df1 = *(float*)(s + 0x71c) - fv1;
                    float df2 = *(float*)(s + 0x720) - fv2;
                    if (X87Sqrt(df0 * df0 + (df1 * df1 + df2 * df2)) < *(float*)0x1473c70)
                    {
                        *(float*)(s + 0x6b4) = *(float*)0x1485720;
                        *(float*)(s + 0x6b8) = *(float*)0x1485720;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00dc13d0
// ===========================================================================
bool __cdecl FUN_00dc13d0(void* p1, int a2, int a3, int a4, int a5, float* p6,
                              int a7, float p8)
{
    char* s = (char*)p1;
    float f = *p6;
    *p6 = f - p8;
    if ((f - p8 <= 0.0f) || *(uint8_t*)(s + 0x74c) != 0)
    {
        if (*(uint8_t*)(s + 0x74c) == 0)
        {
            ((Stub*)s)->FUN_00c3be70(s + 0x718);
            ((Stub*)s)->FUN_00c37e60();
        }
        float f2 = p6[1];
        p6[1] = f2 - p8;
        if (f2 - p8 <= 0.0f)
        {
            if (*(int*)(s + 0x714) != 5)
            {
                void* local = 0;
                int e = FUN_00b3d390();
                ((Stub*)e)->FUN_0104e340((void*)0x169f838, &local);
                ((Stub*)e)->FUN_01050070(local, (void*)(s + 0x34), (void*)0x169f444, -1, 0, 0, 1);
                if (local != 0)
                    (*(void(__thiscall*)(void*))(VTOBJ(local)[8 / 4]))(local);
            }
            return 0;
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00dc14a0
// ===========================================================================
bool __cdecl FUN_00dc14a0(void* p1, int a2, int a3, int a4, int a5, int* out)
{
    char* s = (char*)p1;
    if (out != 0)
        *out = 0;
    int uVar2 = ((Stub*)(*(int*)(s + 0x6c8) + 8))->FUN_00bc96a0(1, 0);
    int* piVar3 = (int*)FUN_00d998d0(uVar2, 0x13f94d4);
    int* piVar1 = (int*)*out;
    if (piVar3 != piVar1)
    {
        if (piVar3 != 0)
            (*(void(__thiscall*)(int))(VTOBJ(piVar3)[0x60 / 4]))((int)piVar3);
        *out = (int)piVar3;
        if (piVar1 != 0)
            (*(void(__thiscall*)(int))(VTOBJ(piVar1)[0x64 / 4]))((int)piVar1);
    }
    if (*out != 0)
    {
        ((Stub*)s)->FUN_00c3b5c0(0x169f574);
        *(float*)(out + 1) = 0.0f;
    }
    ((Stub*)(*(int*)(s + 0x6c8) + 8))->FUN_00bc98f0(1, 0);
    return *out != 0;
}

// ===========================================================================
// @ 0x00dc1540
// ===========================================================================
void __cdecl FUN_00dc1540(void* p1, int a2, int a3, int a4, int a5, int** p6)
{
    char* s = (char*)p1;
    (*(void(__thiscall*)(void*, int))(VTOBJ(s + 0x508)[0x50 / 4]))(s + 0x508, 0);
    if (p6 != 0 && *p6 != 0)
    {
        int* inner = *p6;
        (*(void(__thiscall*)(int*))(VTOBJ(inner)[0x64 / 4]))(inner);
    }
}

// ===========================================================================
// @ 0x00dc1570
// ===========================================================================
bool __cdecl FUN_00dc1570(void* p1, int a2, int a3, int a4, int a5, int* p6,
                              float p7)
{
    char* s = (char*)p1;
    if (*p6 != 0)
    {
        int iVar4 = (*(int(__thiscall*)(int))(VTOBJ(*p6)[8 / 4]))(*p6);
        if (*(char*)(iVar4 + 0x75) != 0)
        {
            int piVar5 = (*(int(__thiscall*)(int))(VTOBJ(*p6)[0xc / 4]))(*p6);
            if (!(*(bool(__thiscall*)(int))(VTOBJ(piVar5)[0x2c / 4]))(piVar5))
            {
                int mgr = FUN_00d51660();
                int tuning = ((Stub*)mgr)->FUN_00d4cb50(2);
                long double fVar9 = FUN_004e1c70(tuning, 0xa58acb11, *(float*)0x13eecd8);
                float fVar2 = (float)fVar9;
                piVar5 = (*(int(__thiscall*)(int))(VTOBJ(*p6)[8 / 4]))(*p6);
                float fVar1 = *(float*)(p6 + 1);
                *(float*)(p6 + 1) = fVar1 - p7;
                if (fVar1 - p7 < 0.0f)
                {
                    *(float*)(p6 + 1) = *(float*)0x14853e0;
                    int pf = (*(int(__thiscall*)(int))(VTOBJ(piVar5)[0x2c / 4]))(piVar5);
                    ((Stub*)s)->FUN_00c3be70((void*)pf);
                    *(uint8_t*)(s + 0x624) = 1;
                    float* pfv = (float*)(*(int(__thiscall*)(int))(VTOBJ(piVar5)[0x2c / 4]))(piVar5);
                    ((Stub*)s)->FUN_00c3daa0((float)(X87Sqrt(pfv[0] * pfv[0] + pfv[1] * pfv[1] + pfv[2] * pfv[2]) + fVar2));
                }
                float* pf7 = (float*)(*(int(__thiscall*)(int))(VTOBJ(s + 0x34)[0x2c / 4]))((int)(s + 0x34));
                float* pf8 = (float*)(*(int(__thiscall*)(int))(VTOBJ(piVar5)[0x2c / 4]))(piVar5);
                float d2 = pf7[2] - pf8[2];
                float d0 = pf7[0] - pf8[0];
                float d1 = pf7[1] - pf8[1];
                float dd = d2 * d2 + d0 * d0 + d1 * d1;
                if (dd <= fVar2 * fVar2 + *(float*)0x13f0e84)
                {
                    (*(void(__thiscall*)(void*, int))(VTOBJ(s + 0x508)[0x50 / 4]))(s + 0x508, *p6);
                }
                return 1;
            }
        }
    }
    int iVar4b = ((Stub*)(*(int*)(s + 0x6c8) + 8))->FUN_00bc96a0(2, 0);
    if (iVar4b != 0)
    {
        int mgr = FUN_00d51660();
        int n = FUN_00d516a0(mgr);
        ((Stub*)mgr)->FUN_00d516d0(n - 1);
    }
    return 0;
}

// ===========================================================================
// @ 0x00dc1710
// ===========================================================================
void __cdecl FUN_00dc1710(int* first, int* last, void* ctx)
{
    int* piVar4 = first;
    if (first != last)
    {
        while (piVar4 = piVar4 + 1, piVar4 != last)
        {
            int* piVar1 = (int*)*piVar4;
            if (piVar1 != 0)
                (*(void(__thiscall*)(int))(VTOBJ(piVar1)[0]))((int)piVar1);
            int* piVar3 = piVar4;
            for (; piVar3 != first; piVar3 = piVar3 - 1)
            {
                int t1 = piVar3[-1];
                int iVar7 = t1 ? (t1 + 0x120) : 0;
                int t2 = (int)piVar1;
                int piVar6 = t2 ? (t2 + 0x120) : 0;
                bool cVar5 = ((Stub*)&ctx)->FUN_00ac0730((void*)piVar6, (void*)iVar7);
                if (!cVar5)
                    break;
                int* pv6 = (int*)piVar3[-1];
                int* piVar2 = (int*)*piVar3;
                if (pv6 != piVar2)
                {
                    if (pv6 != 0)
                        (*(void(__thiscall*)(int))(VTOBJ(pv6)[0]))((int)pv6);
                    *piVar3 = (int)pv6;
                    if (piVar2 != 0)
                        (*(void(__thiscall*)(int))(VTOBJ(piVar2)[1]))((int)piVar2);
                }
            }
            int* pv6 = (int*)*piVar3;
            if (piVar1 != pv6)
            {
                if (piVar1 != 0)
                    (*(void(__thiscall*)(int))(VTOBJ(piVar1)[0]))((int)piVar1);
                *piVar3 = (int)piVar1;
                if (pv6 != 0)
                    (*(void(__thiscall*)(int))(VTOBJ(pv6)[1]))((int)pv6);
            }
            if (piVar1 != 0)
                (*(void(__thiscall*)(int))(VTOBJ(piVar1)[1]))((int)piVar1);
        }
    }
}

// ===========================================================================
// @ 0x00dc1800
// ===========================================================================
void __cdecl FUN_00dc1800(int* first, int* last, void* ctx)
{
    int* p = first;
    for (; p != last; p = p + 1)
    {
        int* piVar1 = (int*)*p;
        int* piVar6 = p;
        if (piVar1 != 0)
            (*(void(__thiscall*)(int))(VTOBJ(piVar1)[0]))((int)piVar1);
        while (true)
        {
            int t1 = piVar6[-1];
            int iVar5 = t1 ? (t1 + 0x120) : 0;
            int t2 = (int)piVar1;
            int piVar4 = t2 ? (t2 + 0x120) : 0;
            bool cVar3 = ((Stub*)&ctx)->FUN_00ac0730((void*)piVar4, (void*)iVar5);
            if (!cVar3)
                break;
            int* pv4 = (int*)piVar6[-1];
            int* piVar2 = (int*)*piVar6;
            if (pv4 != piVar2)
            {
                if (pv4 != 0)
                    (*(void(__thiscall*)(int))(VTOBJ(pv4)[0]))((int)pv4);
                *piVar6 = (int)pv4;
                if (piVar2 != 0)
                    (*(void(__thiscall*)(int))(VTOBJ(piVar2)[1]))((int)piVar2);
            }
            piVar6 = piVar6 - 1;
        }
        int* pv4 = (int*)*piVar6;
        if (piVar1 != pv4)
        {
            if (piVar1 != 0)
                (*(void(__thiscall*)(int))(VTOBJ(piVar1)[0]))((int)piVar1);
            *piVar6 = (int)piVar1;
            if (pv4 != 0)
                (*(void(__thiscall*)(int))(VTOBJ(pv4)[1]))((int)pv4);
        }
        if (piVar1 != 0)
            (*(void(__thiscall*)(int))(VTOBJ(piVar1)[1]))((int)piVar1);
    }
}
