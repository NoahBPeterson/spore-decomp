// Slice s00ec6e00 -- SP cell-stage UI: unlocked-cards list + credits/window helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------- globals
extern unsigned char g_16c7574[];      // 0x016c7574 (byte flags array; 0x16c7578 = [4])
extern unsigned char g_015abcd0;       // 0x015abcd0
extern void*         g_16c7aa4;        // 0x016c7aa4
extern void**        g_16c7584;        // 0x016c7584
extern void**        g_16c757c;        // 0x016c757c
extern float         g_16c7580;        // 0x016c7580
extern void*         g_16c7590;        // 0x016c7590 (pool object)
extern void*         g_16c759c;        // 0x016c759c (vector begin)
extern void*         g_16c75a0;        // 0x016c75a0 (vector end)

// ---------------------------------------------------------------- callees
void* __cdecl FUN_00efc520(void);                       // 0x00efc520
void  __cdecl FUN_00ec6e00(void);                       // 0x00ec6e00
int   __cdecl FUN_00830cf0(int);                        // 0x00830cf0
int   __cdecl FUN_00830d10(int);                        // 0x00830d10
int   __cdecl FUN_00830d60(void*, int);                 // 0x00830d60
int   __cdecl FUN_00830d30(void*, int);                 // 0x00830d30
int   __cdecl FUN_00830d20(int);                        // 0x00830d20
void  __cdecl FUN_008311f0(int, int);                   // 0x008311f0
void  __cdecl FUN_008312f0(int, int);                   // 0x008312f0
void  __cdecl FUN_00831270(int, int);                   // 0x00831270
void  __cdecl SPUIHelpers_AutoSizeWindowForText(void*, int, int);  // 0x00806e40
void* __cdecl SP_WindowManager(void);                   // 0x0067caa0
void  __cdecl SP_PropertyManager(void);                 // 0x0067de30
void* __cdecl FUN_00805310(void*, int, void*);          // 0x00805310
void  __cdecl FUN_00806aa0(int, int, int);              // 0x00806aa0
void* __cdecl FUN_00ec6b20(int*, int);                  // 0x00ec6b20
void  __cdecl FUN_00ec6a00(int);                        // 0x00ec6a00
void  __cdecl FUN_00ec6940(void*, float);               // 0x00ec6940
void  __cdecl FUN_008d2f30(void*, void*);               // 0x008d2f30
int   __cdecl FUN_00809970(void);                       // 0x00809970
int   __cdecl FUN_008053b0(void);                       // 0x008053b0
int   __cdecl FUN_00f25730(void*);                      // 0x00f25730
int   __cdecl FUN_00f25680(void*);                      // 0x00f25680
int   __cdecl FUN_00f25670(void*);                      // 0x00f25670
int   __cdecl FUN_00f25720(void*);                      // 0x00f25720
void* __cdecl FUN_00f3e8a0(void*);                      // 0x00f3e8a0
void  __cdecl cSPBoundingBox_AddBoundingBox(void*, int, int);  // 0x0067cad0
void  __cdecl SPUIHelpers_Renderer(void*, void*, void*);       // 0x0080d710
struct ILayout { void* FindWindowByID(unsigned, int); };   // 0x008105b0 (thiscall: this=[g])
void  __cdecl FUN_0081b650(void*, int, int);             // 0x0081b650
void  __cdecl FUN_00f25190(void*, void*);                // 0x00f25190
void  __cdecl FUN_00f28b80(void*);                       // 0x00f28b80
void  __cdecl SPUIHelpers_CreateImageFromResource(void*, void*, int, unsigned, unsigned); // 0x00806230
void  __cdecl FUN_00ac20d0(int, void*);                  // 0x00ac20d0
void  __cdecl eastl_copy(void*, void*, void*, void*);    // 0x0076ffd0
void  __cdecl FUN_0080d520(void*, void*);                // unused placeholder

// virtual-call helpers
typedef void* (__thiscall *FV_1)(void*);
typedef void* (__thiscall *FV_i)(void*, int);
typedef int   (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_v)(void*);
typedef int   (__thiscall *FB_i)(void*, int);
typedef bool  (__thiscall *FBb_i)(void*, int);

// ---------------------------------------------------------------- 0x00ec6e00
void FUN_00ec6e00(void)
{
    *(int*)g_16c7574 = 0;
    g_16c7574[4] = 0;
    int idx = (int)FUN_00efc520();
    void* gg = g_16c7aa4;
    char* pool = *(char**)((char*)gg + 0x74);
    char* p = *(char**)(pool + 0x10);
    char* it = *(char**)(p + 0x2bf4);
    if (it != *(char**)(p + 0x2bf8)) {
        do {
            int v = *(int*)(*(char**)(it + 0x78) + idx * 0x4e0 + 0x4a8);
            if ((unsigned)(v - 2) < 4)
                g_16c7574[v - 1] = 1;
            it += 0x27e8;
        } while (it != *(char**)(*(char**)(*(char**)((char*)g_16c7aa4 + 0x74) + 0x10) + 0x2bf8));
    }
    g_015abcd0 = 0;
}

// ---------------------------------------------------------------- 0x00ec6e70
unsigned char FUN_00ec6e70(int i)
{
    if (g_015abcd0 != 0)
        FUN_00ec6e00();
    return g_16c7574[i];
}

// ---------------------------------------------------------------- 0x00ec6ea0
int FUN_00ec6ea0(int** param_1, int* param_2)
{
    int* piVar3 = (int*)param_1[0];
    if (piVar3 == (int*)param_1[1])
        return -1;
    int iVar2 = (int)(((char*)param_1[1] - (char*)piVar3) >> 3);
    int iVar1 = 0;
    if (iVar2 > 0) {
        do {
            if (*piVar3 == param_2[0] && piVar3[1] == param_2[1])
                return iVar1;
            ++iVar1;
            piVar3 += 2;
        } while (iVar1 < iVar2);
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ec6ee0
struct UIWnd { void* vtbl; };
void FUN_00ec6ee0(int* param_1, int* param_2, char param_3)
{
    char* a = (char*)((FV_i)(*(void***)param_1)[0xa8 / 4])(param_1, 0);
    char* pcVar2 = a ? (char*)((FV_i)(*(void***)a)[0xc / 4])(a, 0x53eb526) : 0;
    char* b = (char*)((FV_i)(*(void***)param_2)[0xa8 / 4])(param_2, 0);
    char* esi = b ? (char*)((FV_i)(*(void***)b)[0xc / 4])(b, 0x53eb526) : 0;
    int u1 = FUN_00830cf0(0);
    ((FV_ii)(*(void***)pcVar2)[0xc / 4])(pcVar2, 0, u1);
    (void)esi;
    int u3 = (param_3 == 0) ? FUN_00830d10(0) : -1;
    FUN_008311f0(0, u3);
    char tmp[8];
    int u4 = FUN_00830d60(tmp, 0);
    ((FV_ii)(*(void***)pcVar2)[0xc / 4])(pcVar2, 0, u4);
    int u5 = FUN_00830d30(tmp, 0);
    FUN_008312f0(0, u5);
    int u6 = FUN_00830d20(0);
    FUN_00831270(0, u6);
    ((FV_v)(*(void***)param_1)[0x90 / 4])(param_1);
}

// ---------------------------------------------------------------- 0x00ec6fc0
void FUN_00ec6fc0(int param_1, int param_2, int* param_3)
{
    char* piVar3 = param_3 ? (char*)((FV_i)(*(void***)param_3)[0xc / 4])(param_3, 0xf15f4bd) : 0;
    char buf[16];
    float f0, f2;
    ((void(__thiscall*)(void*, void*, void*, void*))(*(void***)piVar3)[0x34 / 4])(piVar3, &buf, &f0, &f2);
    (void)f0; (void)f2;
    SPUIHelpers_AutoSizeWindowForText(param_3, 0, 0);
    (void)param_1; (void)param_2;
}

// ---------------------------------------------------------------- 0x00ec70a0
void FUN_00ec70a0(int param)
{
    char* w = (char*)((ILayout*)*g_16c7584)->FindWindowByID(0x8de6960, 1);
    ((FV_ii)(*(void***)w)[0x7c / 4])(w, 0x400, param);
}

// ---------------------------------------------------------------- 0x00ec70d0
struct Row { char used; char pad[3]; int a4; char pad2[0x18]; int a20; };
void FUN_00ec70d0(int param_1, int param_2, int* param_3)
{
    int v0, v1;
    FUN_008d2f30(&v0, &v1);
    (void)v0; (void)v1;
    (void)param_1; (void)param_2;
    char* g = (char*)*g_16c7584;
    for (int i = 0; i < 0x140; i += 0xa0) {
        Row* r = (Row*)(g + 4 + i);
        if (r->used) {
            int cur = *(int*)(g + 0xc + i);
            int* slot = (int*)(g + 0xc + i);
            if (param_2 < cur && param_2 != -1) *slot = cur - 1;
            if (*slot >= param_1 && param_1 != -1) *slot = *slot + 1;
        }
    }
    (void)param_3;
}

// ---------------------------------------------------------------- 0x00ec7320
void FUN_00ec7320(int* param_1)
{
    char* p1 = (char*)((FV_1)(*(void***)param_1)[0x10 / 4])(param_1);
    char* g = (char*)*g_16c7584;
    if (*(int*)(g + 0x14c) != 0 && p1 == *(char**)(*(int*)(g + 0x14c) + 4))
        ((FB_i)(*(void***)p1)[0x5c / 4])(p1, -1);
    char* p2 = (char*)((FV_1)(*(void***)p1)[0x10 / 4])(p1);
    ((FV_v)(*(void***)p2)[0xe8 / 4])(p2);
    (void)p2;
}

// ---------------------------------------------------------------- 0x00ec73c0
bool FUN_00ec73c0(int param_1)
{
    char* g = (char*)*g_16c7584;
    char* esi = g + 4;
    int i = 0;
    while (!(esi[0] != 0 && *(int*)(esi + 4) == param_1)) {
        ++i;
        esi += 0x20;
        if (i > 9)
            return false;
    }
    (void)param_1;
    if (esi == g + 0x14c)
        return false;
    return true;
}

// ---------------------------------------------------------------- 0x00ec7490
bool FUN_00ec7490(int* param_1, int param_2, char param_3)
{
    if (param_1 == 0)
        return false;
    char* wm = (char*)SP_WindowManager();
    char* r = (char*)((FV_i)(*(void***)wm)[0x48 / 4])(wm, param_2);
    if ((int*)r == param_1)
        return true;
    if (param_3 == 0)
        return false;
    if (((FBb_i)(*(void***)param_1)[0xf8 / 4])(param_1, (int)r))
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x00ec74e0
bool FUN_00ec74e0(void)
{
    char* iVar1 = *(char**)(*(char**)((char*)g_16c7aa4 + 0x14) + 0x18);
    char* w = (char*)((ILayout*)*g_16c7584)->FindWindowByID(0x73e6ba0, 1);
    if (FUN_00809970() != 0)
        return false;
    if (FUN_008053b0() != 0)
        return false;
    if (w != 0) {
        char* wm = (char*)SP_WindowManager();
        char* r = (char*)((FV_i)(*(void***)wm)[0x48 / 4])(wm, 0);
        if (w == r)
            return false;
        if (((FB_i)(*(void***)w)[0xf8 / 4])(w, (int)r))
            return false;
    }
    char* p = *(char**)(iVar1 + 0x20);
    if (p == 0)
        return true;
    {
        char* wm = (char*)SP_WindowManager();
        char* r = (char*)((FV_i)(*(void***)wm)[0x48 / 4])(wm, 0);
        if (p != r && !((FB_i)(*(void***)p)[0xf8 / 4])(p, (int)r))
            return true;
    }
    return false;
}

// ---------------------------------------------------------------- 0x00ec7580
bool FUN_00ec7580(int* param_1)
{
    if (FUN_00f25730(param_1) == 0)
        return false;
    return false;
}

// ---------------------------------------------------------------- 0x00ec7640
bool FUN_00ec7640(int* param_1)
{
    int r = (int)FUN_00efc520();
    int v = *(int*)(r * 0x4e0 + 0x4a8 + *(int*)(*g_16c757c == 0 ? 0 : 0));
    (void)v;
    return true;
}

// ---------------------------------------------------------------- 0x00ec76e0
void FUN_00ec76e0(void** out)
{
    (void)out;
}

// ---------------------------------------------------------------- 0x00ec7770
void FUN_00ec7770(int a, int b, int c, int d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
}

// ---------------------------------------------------------------- 0x00ec78e0
void FUN_00ec78e0(int param_1, int param_2)
{
    char* w = (char*)((ILayout*)*g_16c7584)->FindWindowByID(param_2, 1);
    (void)w;
    (void)param_1;
}

// ---------------------------------------------------------------- 0x00ec7950
void FUN_00ec7950(void)
{
}

// ---------------------------------------------------------------- 0x00ec79f0
int* FUN_00ec79f0(int* param_1, int param_2)
{
    char* p = (char*)(param_2 + 4);
    (void)p;
    (void)param_1;
    return 0;
}

// ---------------------------------------------------------------- 0x00ec7a80
void FUN_00ec7a80(void)
{
    g_16c7580 = 0.0f;
}

// ---------------------------------------------------------------- 0x00ec7b90
void FUN_00ec7b90(int param_1, int* param_2)
{
    (void)param_1; (void)param_2;
}

// ---------------------------------------------------------------- 0x00ec7ca0
void* FUN_00ec7ca0(void* param_1, void* param_2)
{
    (void)param_1; (void)param_2;
    return param_1;
}
