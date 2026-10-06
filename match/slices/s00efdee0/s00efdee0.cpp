// slice s00efdee0 -- scenario tutorial / planetary UI helpers (planet camera placement, view
// state, checklist window bridging).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE  (SSE scalar float math, x87 float returns).
#include "types.h"

extern int*  g_016c7b88;               // 0x016c7b88 (checklist singleton)
extern void* gSimulator;               // 0x016c7aa4
extern void* g_15fd918;                // 0x015fd918
extern int*  g_15ad298;                // 0x015ad298
extern float g_16c7b98, g_16c7b9c, g_16c7ba0, g_15ad29c, g_16c7b8c_unused;
extern uint8_t g_16c7b8c, g_16c7b8d, g_15ad344, g_15acb40;
extern float g_148b6e8, g_15ad2ac, g_13ec4b4, g_1471064, g_1488874;

typedef int  (__thiscall *FN0_i)(void*);
typedef void (__thiscall *FN1_i)(void*, int);
typedef void (__thiscall *FN2_ii)(void*, int, int);
typedef void (__thiscall *FN1_p)(void*, void*);
typedef int  (__thiscall *FN1_ir)(void*, int);

void* __cdecl FUN_00b3d230(int);
void  __cdecl FUN_00b5cde0(void*);
void* __cdecl FUN_00b11870(void*);
void  __cdecl FUN_00b10760(float, float, float);
void* __cdecl FUN_00b81630(void*, void*);
void* __cdecl SP_PlanetModel();
void* __cdecl FUN_00b7f190(void*, void*, void*);
void* __cdecl FUN_00b12dd0(void*, void*, int);
void* __cdecl FUN_00ff3f00(void*);
void* __cdecl FUN_00b13bb0(void*, int);
void* __cdecl FUN_00b104c0(float);
void* __cdecl FUN_00b148c0(int, int, int, int);
void* __cdecl FUN_0067dd50();
void* __cdecl SP_App();
void* __cdecl FUN_007c4900(void*, void*);
void* __cdecl FUN_00b82620(void*, void*, void*, int);
void* __cdecl FUN_00b3d350();
void* __cdecl FUN_00b3d280();
void* __cdecl FUN_00eeca30(void*);
void* __cdecl FUN_00eebf80(void*);
void* __cdecl FUN_00b18e00(void*);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);
void* __cdecl FUN_00b159e0(void*, int);
void* __cdecl FUN_00b326d0_v();
void* __cdecl Property_GetBool();
int   __cdecl FUN_00b326d0_v2();
int   __cdecl FUN_00efd970(void*);
int   __cdecl FUN_00efd020();
int   __cdecl FUN_00ebf5b0();
void* __cdecl FUN_00ed54b0(void*);
void* __cdecl FUN_00ed4e90(void*);
bool  __cdecl FUN_00efe5d0(int);
int   __cdecl FUN_00f35f70(void*);
void* __cdecl FUN_00c8ad30(void*, int);
void* __cdecl FUN_00eef570(void*);
void* __cdecl FUN_00eef4b0(void*);
void* __cdecl FUN_00f3d780(void*);
void* __cdecl FUN_00f3b9e0(void*, void*, int);
void* __cdecl FUN_00f41420(void*, void*, int, int);
void  __cdecl FUN_006ffe00(void*);
void  __cdecl FUN_006ffbd0(void*, int);
int   __cdecl FUN_00efc930();
void* __cdecl FUN_00efcbe0(int);
int   __cdecl FUN_00efc570(void*);
int   __cdecl FUN_00efc5f0(int, float);
bool  __stdcall FUN_00efe630(int, void*);
void* __cdecl FUN_00eec3d0(void*, int);
void* __cdecl FUN_00eece20(void*);
void  __cdecl FUN_00efe110();

// @ 0x00efe240
int __cdecl FUN_00efe240()
{
    FUN_00efe110();
    int* p = g_15ad298;
    ((FN0_i)((*(void***)p)[0x10]))(p);
    return FUN_00ebf5b0();
}

// @ 0x00efe5d0
bool __cdecl FUN_00efe5d0(int v)
{
    char* g = (char*)g_016c7b88;
    int n = (*(int*)(g + 0x90) - *(int*)(g + 0x8c)) >> 5;
    if (n > 0) {
        int* p = *(int**)(g + 0x8c);
        for (int i = 0; i < n; i++) {
            if (*p == v)
                return true;
            p += 8;
        }
    }
    return false;
}

// @ 0x00efe610
int __cdecl FUN_00efe610(void* a)
{
    int r = (int)FUN_00eebf80(a);
    return FUN_00efe5d0(r);
}

// @ 0x00efeaa0
int __fastcall FUN_00efeaa0(char* p)
{
    if (*(int*)((char*)g_016c7b88 + 0xc) == 0 && *(char*)(p + 5) == 0)
        return 0;
    return 1;
}

// @ 0x00efeac0
bool __stdcall FUN_00efeac0(int unused)
{
    (void)unused;
    return *(int*)((char*)g_016c7b88 + 4) != 0;
}

// @ 0x00efe630
bool __stdcall FUN_00efe630(int id, void* p)
{
    if (id == (int)0xcf56099a) {
        if (p == 0)
            return false;
        int a = ((FN1_ir)((*(void***)p)[0x2e]))(p, 0x175cdc9);
        if (a == 0 || *(int*)(a + 0x38) == 0) {
            int b = ((FN1_ir)((*(void***)p)[0x2e]))(p, 0x3a25119);
            if (b == 0 || *(int*)(b + 0x134) == 0)
                return false;
        }
        return true;
    }
    if (id == (int)0xe34e8a60)
        return true;
    if (id == 0x5b3d1d0a)  // 0x5b3d1d0d handled below
        return true;
    if (id == 0x5b3d1d0d)
        return true;
    return false;
}

// @ 0x00efe870
int __cdecl FUN_00efe870(int* key)
{
    char* g = (char*)*(void**)((char*)gSimulator + 0x74);
    char* base = *(char**)(g + 0x10);
    int* begin = *(int**)(base + 0x2bf4);
    int* end = *(int**)(base + 0x2bf8);
    int* p = begin;
    while (p != end) {
        if (p[0] == key[0] && p[1] == key[1] && p[2] == key[2])
            return (int)(p - begin);
        p = (int*)((char*)p + 0x27e8);
    }
    return -1;
}

// @ 0x00efe870 (unused alias)

// ---------------------------------------------------------------------------
// remaining functions (approximate bodies; see partial.txt)
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b5cde0_2();
void  __cdecl FUN_00b10760_2();
void* __cdecl FUN_00b12dd0_2();
void* __cdecl FUN_00b10760_3(float, float, float);
void* __cdecl FUN_00b148c0_2(int,int,int,int);
void  __cdecl FUN_007c40c0(void*, void*);
void* __cdecl FUN_007c4010(void*);
void  __cdecl FUN_006ffbd0_2(void*, int);
void* __cdecl FUN_00b326d0_3();
void* __cdecl FUN_00b18e00_2(void*);
void* __cdecl FUN_00b326d0_4();
int   __cdecl FUN_00efd020_2();
void* __cdecl FUN_00f35f70_2(void*);
void  __cdecl FUN_00efe110_v();

// @ 0x00efdee0
void __cdecl FUN_00efdee0()
{
    FUN_00b3d230(0xebb801);
    FUN_00b5cde0((void*)0xebb801);
    void* app = (void*)SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[0x10]))(a);
    (void)b;
    void* base = (void*)*(void**)((char*)gSimulator + 0x74);
    void* p = *(void**)((char*)base + 0x10);
    (void)p;
    FUN_00efcbe0(1);
}

// @ 0x00efe110
void __cdecl FUN_00efe110()
{
    char* g = (char*)g_016c7b88;
    if (*(char*)(g + 0xa5) == 0) {
        void* m = FUN_0067dd50();
        int v = ((FN0_i)((*(void***)m)[7]))(m);
        int dx = *(int*)(g + 0xa8) - *(int*)(v + 8);
        int dy = *(int*)(g + 0xac) - *(int*)(v + 0xc);
        *(char*)(g + 0xa5) = (char)(((dx < 0 ? -dx : dx) > 2) || ((dy < 0 ? -dy : dy) > 2));
    }
    void* app = (void*)SP_App();
    void* v = (void*)((FN0_i)((*(void***)app)[0x16]))(app);
    (void)v;
}

// @ 0x00efe260
void __cdecl FUN_00efe260()
{
    int* p = g_15ad298;
    ((FN0_i)((*(void***)p)[8]))(p);
    char* g = (char*)g_016c7b88;
    void* q = *(void**)(g + 0x10);
    if (q != 0) {
        *(void**)(g + 0x10) = 0;
        ((FN0_i)((*(void***)q)[1]))(q);
    }
    void* r = FUN_00eebf80((void*)0);
    if (r != 0)
        FUN_00ed54b0(r);
    else
        FUN_00ed4e90(0);
}

// @ 0x00efe310
void __cdecl FUN_00efe310(int flag)
{
    void* app = (void*)SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN0_i)((*(void***)b)[3]))(b);
    if (o == 0)
        return;
    void* d4 = *(void**)((char*)gSimulator + 0xd4);
    ((FN2_ii)((*(void***)d4)[4]))(d4, 0xf, 0x10);
    FUN_00b0f950(o, flag);
    if (flag == 0)
        return;
    char* g = (char*)g_016c7b88;
    *(char*)(g + 0xa5) = 0;
    void* m = FUN_0067dd50();
    int v = ((FN0_i)((*(void***)m)[7]))(m);
    *(int*)(g + 0xa8) = *(int*)(v + 8);
    *(int*)(g + 0xac) = *(int*)(v + 0xc);
}

// @ 0x00efe4a0
void __cdecl FUN_00efe4a0(int flag)
{
    void* app = (void*)SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN0_i)((*(void***)b)[3]))(b);
    if (o == 0)
        return;
    if (*(char*)((char*)o + 0x319) == 0 && flag == 0) {
        void* d4 = *(void**)((char*)gSimulator + 0xd4);
        ((FN2_ii)((*(void***)d4)[4]))(d4, 0x13, 0x14);
    }
    FUN_00b10c40(o, flag);
}

// @ 0x00efe510
void __cdecl FUN_00efe510(float f)
{
    void* app = (void*)SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))(app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b == 0)
        return;
    void* o = (void*)((FN0_i)((*(void***)b)[3]))(b);
    if (o == 0)
        return;
    (void)f;
}

// @ 0x00efe6a0
int __cdecl FUN_00efe6a0(int param)
{
    void* o = FUN_00eeca30((void*)param);
    int r = ((FN0_i)((*(void***)o)[0xb]))(o);
    (void)r;
    char* g = (char*)g_016c7b88;
    if (g_16c7b8c != 0 && *(char*)((char*)o + 0x78) != 0)
        return 2;
    return 0;
}

// @ 0x00efe8d0
void __fastcall FUN_00efe8d0(char* p, int pad, int a)
{
    ((FN1_i)((*(void***)p)[6]))(p, a == 1);
    if (a != 2)
        ((FN1_i)((*(void***)p)[8]))(p, (a != 0) ? 1 : 0);
    if (a == 1 && *(int*)((char*)g_016c7b88 + 4) != 0)
        FUN_00efd970(*(void**)((char*)g_016c7b88 + 4));
}

// @ 0x00efe930
void __fastcall FUN_00efe930(int* p, int pad, void* a)
{
    (void)p;
    char* g = (char*)g_016c7b88;
    if (g == 0 || *(int*)(g + 0x20) == 0)
        return;
    if (a != 0)
        FUN_00eef570(*(void**)(g + 4));
    else
        FUN_00eef4b0((void*)(g + 0x8c));
    FUN_00efd020();
}

// @ 0x00efeae0
int __stdcall FUN_00efeae0(int a)
{
    (void)a;
    return 0;
}

// @ 0x00efebb0
int __fastcall FUN_00efebb0(void* p, int a)
{
    (void)p; (void)a;
    return 0;
}

// @ 0x00efec90
void __cdecl FUN_00efec90()
{
}
