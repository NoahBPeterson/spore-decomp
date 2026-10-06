// Slice s00ecad70 -- SP cell-stage UI: ban/palette item rows and slider helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- globals
extern void*         g_16c7584;      // 0x016c7584 (object pointer; [g] = layout)
extern void**        g_16c757c;      // 0x016c757c
extern unsigned int  g_15abd00;      // 0x015abd00
extern unsigned int  g_15abcfc;      // 0x015abcfc
extern unsigned char g_16c7574[];

// ---------------------------------------------------------------- callees
void* __cdecl FUN_00efc520(void);                       // 0x00efc520
void  __cdecl FUN_00eca920(void*);                      // 0x00eca920
void  __cdecl FUN_00ec9c70(void*, void*);               // 0x00ec9c70
void  __cdecl FUN_00eca9c0(void);                       // 0x00eca9c0
void  __cdecl FUN_00eca1d0(void);                       // 0x00eca1d0
void  __cdecl FUN_00eca2f0(void);                       // 0x00eca2f0
void  __cdecl FUN_00ec7e90(void);                       // 0x00ec7e90
void  __cdecl FUN_00ec70a0(int);                        // 0x00ec70a0
void  __cdecl FUN_00ec7320(int*);                       // 0x00ec7320
bool  __cdecl FUN_00ec73c0(int, void*);                 // 0x00ec73c0
int   __cdecl FUN_00ec74e0(void);                       // 0x00ec74e0
void  __cdecl FUN_00ecb520(int, int);                   // 0x00ecb520
void  __cdecl FUN_00ecad70(void);                       // 0x00ecad70
void  __cdecl FUN_00ecb010(int, int);                   // 0x00ecb010
void  __cdecl FUN_00ecb090(int, int);                   // 0x00ecb090
void  __cdecl FUN_00ecb0d0(int, int);                   // 0x00ecb0d0
void  __cdecl FUN_00ecb110(int, int);                   // 0x00ecb110
void  __cdecl FUN_00ecb150(int, int);                   // 0x00ecb150
void  __cdecl FUN_0080d710(void*, void*, void*);        // 0x0080d710
void  __cdecl FUN_0067cad0(void*, int, int);            // 0x0067cad0
void  __cdecl FUN_00ecaab0(void*);                      // 0x00ecaab0
void  __cdecl FUN_00ecabc0(void*);                      // 0x00ecabc0
int   __cdecl FUN_008d3200(int, int);                   // 0x008d3200
int   __cdecl FUN_008d2fb0(int);                        // 0x008d2fb0

typedef void* (__thiscall *FV_1)(void*);
typedef void* (__thiscall *FV_i)(void*, int);
typedef int   (__thiscall *FV_ii)(void*, int, int);
typedef bool  (__thiscall *FB_1)(void*);
typedef int   (__thiscall *FI_1)(void*);

struct ILayout { void* FindWindowByID(unsigned, int); };   // 0x008105b0

// ---------------------------------------------------------------- 0x00ecb090
void FUN_00ecb090(int param_1, int param_2)
{
    int i = 0;
    char* p = (char*)g_16c7584 + 4;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    *(int*)(p + 0x10) = param_2;
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb0d0
void FUN_00ecb0d0(int param_1, int param_2)
{
    int i = 0;
    char* p = (char*)g_16c7584 + 4;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    *(int*)(p + 0x14) = param_2;
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb110
void FUN_00ecb110(int param_1, int param_2)
{
    int i = 0;
    char* p = (char*)g_16c7584 + 4;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    *(int*)(p + 0x1c) = param_2;
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb010
void FUN_00ecb010(int param_1, int param_2)
{
    int i = 0;
    char* p = (char*)g_16c7584 + 4;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    int local[5];
    local[0] = *(int*)(p + 0xc);
    local[1] = *(int*)(p + 0x10);
    local[2] = *(int*)(p + 0x14);
    local[3] = *(int*)(p + 0x18);
    local[4] = *(int*)(p + 0x1c);
    *(int*)(p + 0x18) = param_2;
    FUN_00ec9c70(local, p + 0xc);
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb150
void FUN_00ecb150(int param_1, int param_2)
{
    char* g = (char*)g_16c7584;
    char* p = g + 4;
    int i = 0;
    do {
        if (p[0] != 0 && *(int*)(p + 4) == param_1)
            goto found;
        ++i;
        p += 0x20;
    } while (i < 10);
    p = 0;
found:
    if (p == *(char**)(g + 0x14c)) {
        *(int*)(g + 0x14c) = 0;
        FUN_00eca9c0();
        *(int*)(p + 0xc) = -1;
    }
    int local[5];
    local[0] = *(int*)(p + 0xc);
    local[1] = *(int*)(p + 0x10);
    local[2] = *(int*)(p + 0x14);
    local[3] = *(int*)(p + 0x18);
    local[4] = *(int*)(p + 0x1c);
    *(int*)(p + 0xc) = param_2;
    FUN_00ec9c70(local, p + 0xc);
    FUN_00eca920(p);
}

// ---------------------------------------------------------------- 0x00ecb690
void FUN_00ecb690(float f)
{
    if (*g_16c757c != 0)
        FUN_00ecad70();
    (void)f;
}

// ---------------------------------------------------------------- 0x00ecb730
void FUN_00ecb730(void)
{
    char* w = (char*)((ILayout*)g_16c7584)->FindWindowByID(0x8de6958, 1);
    if (((FI_1)(*(void***)w)[0x28 / 4])(w) & 1)
        FUN_00eca2f0();
}

// ---------------------------------------------------------------- 0x00ecb6b0
unsigned char FUN_00ecb6b0(int param_1)
{
    int idx = (int)FUN_00efc520();
    char bl = *(char*)(*(int*)(param_1 + 0x70) + idx * 0x4e0 + 0x4c8);
    char* w = (char*)((ILayout*)g_16c7584)->FindWindowByID(0x8de6958, 1);
    if ((((FI_1)(*(void***)w)[0x28 / 4])(w) & 1) && param_1 != (int)*g_16c757c) {
        if (*(char*)(*(int*)(param_1 + 0x70) + idx * 0x4e0 + 0x4c8) == 1) {
            FUN_00eca2f0();
            FUN_00ecb520(param_1, 0);
        } else {
            FUN_00eca2f0();
        }
    }
    return (unsigned char)bl;
}

// ---------------------------------------------------------------- 0x00ecb7a0
inline float ClampF(float v, float lo, float hi)
{
    v = (v > lo) ? v : lo;
    v = (v < hi) ? v : hi;
    return v;
}

struct CItem {
    char pad[0x58];
    float f58;      // +0x58
    float f5c;      // +0x5c
    float f60;      // +0x60
    float f64;      // +0x64
    float FUN_A(float);
    float FUN_B(float);
};

float CItem::FUN_A(float param)
{
    float f = f58;
    if (f < f5c) {
        f = (param - f) / (f5c - f);
        return ClampF(f, 0.0f, 1.0f);
    }
    return 0.5f;
}

float CItem::FUN_B(float param)
{
    float f = f60;
    if (f < f64) {
        f = (param - f) / (f64 - f);
        return ClampF(f, 0.0f, 1.0f);
    }
    return 0.5f;
}

// ---------------------------------------------------------------- 0x00ecb8c0
struct PaletteItem {
    void* vt0;
    char pad[0x20 - 4];
    void* vt20;     // +0x20
    void* p24;      // +0x24
    void* p28;      // +0x28
    void* p2c;      // +0x2c
    void dtor();
};
void PaletteItem::dtor()
{
    vt0 = (void*)0x1489350;
    *(void**)((char*)this + 0xc) = (void*)0x1489334;
    *(void**)((char*)this + 0x10) = (void*)0x1489324;
    *(void**)((char*)this + 0x20) = (void*)0x1489314;
    if (p2c) (*(void(__thiscall**)(void*))((*(void***)p2c)[2]))(p2c);
    if (p28) (*(void(__thiscall**)(void*))((*(void***)p28)[2]))(p28);
    if (p24) (*(void(__thiscall**)(void*))((*(void***)p24)[1]))(p24);
    *(void**)((char*)this + 0x20) = (void*)0x13eb394;
}
// ================================================================ remaining (best-effort / incomplete)
void FUN_00ecad70(void) {}
void FUN_00ecb1f0(int a, int* b) { (void)a; (void)b; }
void FUN_00ecb520(int a, int b) { (void)a; (void)b; }
void FUN_00ecb950(void) {}
void FUN_00ecb9a0(void) {}
void FUN_00ecba50(void) {}
