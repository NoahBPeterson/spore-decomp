// Slice s00548d90: SP::Feed 0x118 / 0x70 / 0x34 / 0x14 element copy ctors,
// assign operators, and lower_bound helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------- externals
void* operator new[](size_t, const char*, int, unsigned, const char*, int);
void  operator_delete__(void*); // 0x00f47380
void* FUN_0042dee0(void* alloc, int size, int align, int flags); // @ 0x42dee0
void  FUN_00423820(void* self, int a, int b);
void  FUN_0047d390(void* self, int a, int b);
void  VariantAssign(void* dst, void* src);
void  WAssign(void* self, const wchar_t* a, const wchar_t* b);
void  AAssign(void* self, const char* a, const char* b);
void  FUN_005498a0(void* a);         // @ 0x5498a0
void  FUN_0054a5d0(void* a);
void  FUN_0054aba0(void* a);
void  FUN_0050d440(void* a);
void  FUN_00549940(void* a);
void  FUN_0054a670(void* a);
void  FUN_0054ac70(void* a);
void  FUN_0054afe0(void* a);
void  FUN_004e4350(void* a);
void  FUN_005477a0(void* self);      // @ 0x5477a0 dtor
int   FUN_0054a4d0(int a, int b, int c);
int   FUN_0054a570(int n, int a, int b);
void  FUN_0054a470(int a);
void  FUN_0054a920(int a, int b);

// ---------------------------------------------------------------- object
struct Obj44 {
    char mPad[0x200];
    int* FUN_00548d90(int* param_2);
    int* FUN_00548e70(int* param_2);
    int* FUN_00548ee0(int* param_2);
    int* FUN_00549250(int* param_2);
    int* FUN_00549500(int* param_2);
    int* FUN_005496a0(int* param_2);
    unsigned* FUN_00549940(unsigned* param_2);
    int  FUN_00549d20(int param_2, int param_3);
};

// @ 0x00548d90
int* Obj44::FUN_00548d90(int* param_2)
{
    int* p = (int*)this;
    p[0] = 0; p[1] = 0; p[2] = 0;
    FUN_00423820(p, param_2[0], param_2[1]);
    p[4] = 0; p[5] = 0; p[6] = 0;
    FUN_00423820(p + 4, param_2[4], param_2[5]);
    *(unsigned short*)(p + 0xc) = 0;
    *(unsigned short*)((char*)p + 0x32) = 0;
    VariantAssign(p + 8, param_2 + 8);
    return p;
}

// @ 0x00548e70
int* Obj44::FUN_00548e70(int* param_2)
{
    int* p = (int*)this;
    if (param_2 != p)
        WAssign(p, (const wchar_t*)param_2[0], (const wchar_t*)param_2[1]);
    if (param_2 + 4 != p + 4)
        WAssign(p + 4, (const wchar_t*)param_2[4], (const wchar_t*)param_2[5]);
    VariantAssign(p + 8, param_2 + 8);
    return p;
}

// @ 0x00548ee0
int* Obj44::FUN_00548ee0(int* param_2)
{
    int* p = (int*)this;
    p[0] = 0; p[1] = 0; p[2] = 0;
    FUN_0047d390(p, param_2[0], param_2[1]);
    p[4] = param_2[4]; p[5] = param_2[5];
    p[6] = 0; p[7] = 0; p[8] = 0;
    FUN_00423820(p + 6, param_2[6], param_2[7]);
    p[10] = param_2[10]; p[0xb] = param_2[0xb]; p[0xc] = param_2[0xc];
    p[0xd] = param_2[0xd]; p[0xe] = param_2[0xe]; p[0xf] = param_2[0xf];
    p[0x10] = param_2[0x10]; p[0x11] = param_2[0x11];
    p[0x12] = 0; p[0x13] = 0; p[0x14] = 0;
    FUN_00423820(p + 0x12, param_2[0x12], param_2[0x13]);
    p[0x16] = param_2[0x16]; p[0x17] = param_2[0x17];
    p[0x18] = param_2[0x18]; p[0x19] = param_2[0x19];
    p[0x1a] = 0; p[0x1b] = 0; p[0x1c] = 0;
    FUN_00423820(p + 0x1a, param_2[0x1a], param_2[0x1b]);
    FUN_005498a0(param_2 + 0x1e);
    FUN_0054a5d0(param_2 + 0x23);
    *(unsigned char*)(p + 0x28) = *(unsigned char*)(param_2 + 0x28);
    int* ref = p + 0x29;
    *ref = param_2[0x29];
    if (*ref != 0) *(int*)(*ref + 4) = *(int*)(*ref + 4) + 1;
    p[0x2a] = 0; p[0x2b] = 0; p[0x2c] = 0;
    FUN_0047d390(p + 0x2a, param_2[0x2a], param_2[0x2b]);
    p[0x2e] = 0; p[0x2f] = 0; p[0x30] = 0;
    FUN_0047d390(p + 0x2e, param_2[0x2e], param_2[0x2f]);
    p[0x32] = param_2[0x32]; p[0x33] = param_2[0x33];
    p[0x34] = 0; p[0x35] = 0; p[0x36] = 0;
    FUN_00423820(p + 0x34, param_2[0x34], param_2[0x35]);
    FUN_0054aba0(param_2 + 0x38);
    FUN_0050d440(param_2 + 0x3e);
    *(unsigned char*)(p + 0x44) = *(unsigned char*)(param_2 + 0x44);
    return p;
}

// @ 0x00549250
int* Obj44::FUN_00549250(int* param_2)
{
    int* p = (int*)this;
    if (param_2 != p)
        AAssign(p, (const char*)param_2[0], (const char*)param_2[1]);
    p[4] = param_2[4]; p[5] = param_2[5];
    if (param_2 + 6 != p + 6)
        WAssign(p + 6, (const wchar_t*)param_2[6], (const wchar_t*)param_2[7]);
    p[10] = param_2[10]; p[0xb] = param_2[0xb]; p[0xc] = param_2[0xc];
    p[0xd] = param_2[0xd]; p[0xe] = param_2[0xe]; p[0xf] = param_2[0xf];
    p[0x10] = param_2[0x10]; p[0x11] = param_2[0x11];
    if (param_2 + 0x12 != p + 0x12)
        WAssign(p + 0x12, (const wchar_t*)param_2[0x12], (const wchar_t*)param_2[0x13]);
    p[0x16] = param_2[0x16]; p[0x17] = param_2[0x17];
    p[0x18] = param_2[0x18]; p[0x19] = param_2[0x19];
    if (param_2 + 0x1a != p + 0x1a)
        WAssign(p + 0x1a, (const wchar_t*)param_2[0x1a], (const wchar_t*)param_2[0x1b]);
    ((Obj44*)(p + 0x1e))->FUN_00549940((unsigned*)(param_2 + 0x1e));
    FUN_0054a670(param_2 + 0x23);
    *(unsigned char*)(p + 0x28) = *(unsigned char*)(param_2 + 0x28);
    FUN_004e4350(param_2 + 0x29);
    if (param_2 + 0x2a != p + 0x2a)
        AAssign(p + 0x2a, (const char*)param_2[0x2a], (const char*)param_2[0x2b]);
    if (param_2 + 0x2e != p + 0x2e)
        AAssign(p + 0x2e, (const char*)param_2[0x2e], (const char*)param_2[0x2f]);
    p[0x32] = param_2[0x32]; p[0x33] = param_2[0x33];
    if (param_2 + 0x34 != p + 0x34)
        WAssign(p + 0x34, (const wchar_t*)param_2[0x34], (const wchar_t*)param_2[0x35]);
    FUN_0054ac70(param_2 + 0x38);
    FUN_0054afe0(param_2 + 0x3e);
    *(unsigned char*)(p + 0x44) = *(unsigned char*)(param_2 + 0x44);
    return p;
}

// @ 0x00549500
int* Obj44::FUN_00549500(int* param_2)
{
    int* p = (int*)this;
    p[0] = 0; p[1] = 0; p[2] = 0;
    FUN_00423820(p, param_2[0], param_2[1]);
    p[4] = param_2[4]; p[5] = param_2[5];
    p[6] = 0; p[7] = 0; p[8] = 0;
    FUN_00423820(p + 6, param_2[6], param_2[7]);
    p[10] = 0; p[0xb] = 0; p[0xc] = 0;
    FUN_00423820(p + 10, param_2[10], param_2[0xb]);
    p[0xe] = param_2[0xe]; p[0xf] = param_2[0xf]; p[0x10] = param_2[0x10];
    p[0x11] = 0; p[0x12] = 0; p[0x13] = 0;
    FUN_0047d390(p + 0x11, param_2[0x11], param_2[0x12]);
    p[0x15] = 0; p[0x16] = 0; p[0x17] = 0;
    FUN_0047d390(p + 0x15, param_2[0x15], param_2[0x16]);
    p[0x19] = param_2[0x19]; p[0x1a] = param_2[0x1a];
    return p;
}

// @ 0x005496a0
int* Obj44::FUN_005496a0(int* param_2)
{
    int* p = (int*)this;
    if (param_2 != p)
        WAssign(p, (const wchar_t*)param_2[0], (const wchar_t*)param_2[1]);
    p[4] = param_2[4]; p[5] = param_2[5];
    if (param_2 + 6 != p + 6)
        WAssign(p + 6, (const wchar_t*)param_2[6], (const wchar_t*)param_2[7]);
    if (param_2 + 10 != p + 10)
        WAssign(p + 10, (const wchar_t*)param_2[10], (const wchar_t*)param_2[0xb]);
    p[0xe] = param_2[0xe]; p[0xf] = param_2[0xf]; p[0x10] = param_2[0x10];
    if (param_2 + 0x11 != p + 0x11)
        AAssign(p + 0x11, (const char*)param_2[0x11], (const char*)param_2[0x12]);
    if (param_2 + 0x15 != p + 0x15)
        AAssign(p + 0x15, (const char*)param_2[0x15], (const char*)param_2[0x16]);
    p[0x19] = param_2[0x19]; p[0x1a] = param_2[0x1a];
    return p;
}

// @ 0x005497e0
short* FUN_005497e0(short* param_1, short* param_2, short* param_3, short* param_4)
{
    for (;;) {
        if (param_1 == param_2) return param_2;
        short* cur = param_3;
        for (; cur != param_4 && *param_1 != *cur; cur = cur + 1) { }
        if (cur == param_4) return param_1;
        param_1 = param_1 + 1;
    }
}

// @ 0x00549840
int FUN_00549840(int param_1, int param_2, short* param_3, short* param_4)
{
    for (;;) {
        if (param_1 == param_2) return param_2;
        short* cur = param_3;
        for (; cur != param_4 && *(short*)(param_1 - 2) != *cur; cur = cur + 1) { }
        if (cur == param_4) return param_1;
        param_1 = param_1 - 2;
    }
}

// @ 0x00549940
unsigned* Obj44::FUN_00549940(unsigned* param_2)
{
    unsigned* p = (unsigned*)this;
    if (param_2 != p) {
        unsigned n = (unsigned)((int)(param_2[1] - *param_2) / 0x34);
        if ((unsigned)((int)(p[2] - *p) / 0x34) < n) {
            unsigned buf = (unsigned)FUN_0054a570((int)n, *param_2, param_2[1]);
            unsigned end = p[1];
            for (unsigned cur = *p; cur < end; cur = cur + 0x34)
                FUN_005477a0((void*)cur);
            unsigned old = *p;
            if (old != 0 && *(int*)(old - 4) != 0) operator_delete__((void*)old);
            *p = buf;
            p[2] = n * 0x34 + *p;
        } else if ((unsigned)((int)(p[1] - *p) / 0x34) < n) {
            unsigned e = p[1];
            unsigned b = *p;
            unsigned srcb = *param_2;
            unsigned dst = p[1];
            for (unsigned src = *param_2;
                 src != (unsigned)(((int)(e - b) / 0x34) * 0x34 + srcb);
                 src = src + 0x34) {
                ((Obj44*)dst)->FUN_00548e70((int*)src);
                dst = dst + 0x34;
            }
            FUN_0054a4d0((int)(((int)(p[1] - *p) / 0x34) * 0x34 + *param_2), param_2[1], p[1]);
        } else {
            unsigned dst = *p;
            unsigned srcEnd = param_2[1];
            for (unsigned src = *param_2; src != srcEnd; src = src + 0x34) {
                ((Obj44*)dst)->FUN_00548e70((int*)src);
                dst = dst + 0x34;
            }
            unsigned e = p[1];
            for (unsigned cur = dst; cur < e; cur = cur + 0x34)
                FUN_005477a0((void*)cur);
        }
        p[1] = n * 0x34 + *p;
    }
    return p;
}

// @ 0x00549d20
int Obj44::FUN_00549d20(int param_2, int param_3)
{
    int* p = (int*)this;
    int base = *p;
    if (param_2 == p[1] && p[1] != p[2]) {
        int e = p[1];
        p[1] = p[1] + 0x14;
        if (e != 0) FUN_0054a470(param_3);
    } else {
        FUN_0054a920(param_2, param_3);
    }
    return ((param_2 - base) / 0x14) * 0x14 + *p;
}

// @ 0x00549dc0
unsigned* FUN_00549dc0(unsigned* param_1, int param_2, unsigned* param_3)
{
    int n = (param_2 - (int)param_1) / 0x14;
    for (;;) {
        int local = n;
        if (local <= 0) break;
        n = local >> 1;
        if (param_1[n * 5] < *param_3) {
            param_1 = param_1 + n * 5 + 5;
            n = local - (n + 1);
        }
    }
    return param_1;
}
// --- equivalence checker address annotations
    void operator_delete__(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
